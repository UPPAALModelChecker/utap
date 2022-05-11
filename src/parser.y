// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; -*-

 /* libutap - Uppaal Timed Automata Parser.
	Copyright (C) 2011-2022 Aalborg University.
	Copyright (C) 2002-2011 Uppsala University and Aalborg University.

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public License
	as published by the Free Software Foundation; either version 2.1 of
	the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful, but
	WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
	USA
 */

 /*********************************************************************
  * This bison grammar file contains both grammars for old and new XTA
  * formats plus entry points for various productions used in the XML
  * parser.
  *
  * There are numerous problems with parser error recognition and
  * recovery in general, since the XTA language contains some tricky
  * properties:
  *
  * 1) The entity terminating tokens such as '}' and ';' are used for
  * multiple purposes, thus making it impossible to "skip until the end
  * of current entity".
  *
  * 2) Since entity terminating token is not always clear, there might
  * appear continuous error reports on the same code as no recovery is
  * made. Please report it, this might be corrected.
  */

%code requires {

#include "parser.hpp"
#include "libparser.h"
#include "utap/position.h"

#include <limits>
#include <cstring> // strlen

using namespace UTAP;
using namespace Constants;

#define YYLLOC_DEFAULT(Current, Rhs, N)        		  	        \
	 do        								\
	   if (N)        							\
		 {								\
		   (Current).start        = YYRHSLOC (Rhs, 1).start;	        \
		   (Current).end          = YYRHSLOC (Rhs, N).end;	        \
		 }								\
	   else        							\
		 {								\
		   (Current).start        = (Current).end   =		        \
			 YYRHSLOC (Rhs, 0).end;			  	        \
		 }								\
	 while (0)

#define YYLTYPE position_t
}

%code {
static ParserBuilder *ch;
static syntax_t syntax;
static int syntax_token = 0;

static void utap_error(const char* msg);

static int lexer_flex();

static int utap_lex()
{
   int old;
   if (syntax_token) {
	 old = syntax_token;
	 syntax_token = 0;
	 return old;
   }
   return lexer_flex();
}

static char rootTransId[MAXLEN];

/* Counter used during array parsing. */
static int types = 0;

#define CALL(first,last,call) do { ch->setPosition(first.start, last.end); try { ch->call; } catch (TypeException &te) { ch->handleError(te); } } while (0)

#define YY_(msg) utap_msg(msg)

struct str_entry_t
{
	int len;
	const char* from;
	const char* to;
};

const char* utap_msg(const char *msg)
{
	/* Simple & short log(n) algorithm.
	 */
#define NB_STR 8
	static const str_entry_t table[NB_STR] =
		{
			{ len:12,
			  from:"syntax error",
			  to:"$syntax_error" },
			{ len:16,
			  from:"memory exhausted",
			  to:"$memory_exhausted" },
			{ len:27,
			  from:"syntax error, unexpected %s",
			  to:"$syntax_error: $unexpected %s" },
			{ len:28,
			  from:"syntax error: cannot back up",
			  to:"$syntax_error: $cannot_back_up" },
			{ len:41,
			  from:"syntax error, unexpected %s, expecting %s",
			  to:"$syntax_error: $unexpected %s, $expecting %s" },
			{ len:47,
			  from:"syntax error, unexpected %s, expecting %s or %s",
			  to:"$syntax_error: $unexpected %s, $expecting %s $or %s" },
			{ len:53,
			  from:"syntax error, unexpected %s, expecting %s or %s or %s",
			  to:"$syntax_error: $unexpected %s, $expecting %s $or %s $or %s" },
			{ len:59,
			  from:"syntax error, unexpected %s, expecting %s or %s or %s or %s",
			  to:"$syntax_error: $unexpected %s, $expecting %s $or %s $or %s $or %s" }
		};
	int len = std::strlen(msg);
	int i = NB_STR / 2;
	while(i < NB_STR)
	{
		if (len < table[i].len)
		{
			if (i == 0) return msg;
			i = i/2;
			continue;
		}
		if (len > table[i].len)
		{
			if (i == NB_STR-1) return msg;
			i = (i+NB_STR)/2;
			continue;
		}
		for(;i < NB_STR && len <= table[i].len; ++i)
		{
			if (strcmp(msg, table[i].from) == 0)
			{
				return table[i].to;
			}
		}
		break;
	}
    return msg;
#undef NB_STR
}

}

%require "3.6.0"
%define parse.error detailed

/* Assignments: */
%token T_ASSIGNMENT T_ASSPLUS
%token T_ASSMINUS T_ASSMULT T_ASSDIV T_ASSMOD
%token T_ASSOR T_ASSAND T_ASSXOR
%token T_ASSLSHIFT T_ASSRSHIFT

/* Unary operations: */
%token T_EXCLAM

%token T_INCREMENT T_DECREMENT

/* Binary operations: */
%token T_PLUS T_MINUS T_MULT T_DIV
%token T_MOD T_OR T_XOR T_LSHIFT T_RSHIFT
%token T_BOOL_AND T_BOOL_OR
%token T_KW_AND T_KW_OR T_KW_XOR T_KW_IMPLY T_KW_NOT

/* Special */
%token T_SUP T_INF

/* Math functions */
%token T_ABS T_FABS T_FMOD T_FMA T_FMAX T_FMIN T_FDIM
%token T_EXP T_EXP2 T_EXPM1 T_LN T_LOG T_LOG10 T_LOG2 T_LOG1P
%token T_POW T_SQRT T_CBRT T_HYPOT
%token T_SIN T_COS T_TAN T_ASIN T_ACOS T_ATAN T_ATAN2
%token T_SINH T_COSH T_TANH T_ASINH T_ACOSH T_ATANH
%token T_ERF T_ERFC T_TGAMMA T_LGAMMA
%token T_CEIL T_FLOOR T_TRUNC T_ROUND T_FINT
%token T_LDEXP T_ILOGB T_LOGB T_NEXTAFTER T_NEXTTOWARD T_COPYSIGN
%token T_FPCLASSIFY T_ISFINITE T_ISINF T_ISNAN T_ISNORMAL T_SIGNBIT T_ISUNORDERED
%token T_RANDOM T_RANDOM_ARCSINE T_RANDOM_BETA T_RANDOM_GAMMA T_RANDOM_NORMAL
%token T_RANDOM_POISSON T_RANDOM_TRI T_RANDOM_WEIBULL

/* Quantifiers */
%token T_FORALL T_EXISTS T_FOREACH

 /* Sum of expressions */
%token T_SUM

/* Relation operations:*/
%token T_LT T_LEQ T_EQ T_NEQ T_GEQ T_GT

/* Special statement keywords: */
%token T_FOR T_WHILE T_DO T_BREAK T_CONTINUE T_SWITCH T_IF T_ELSE
%token T_CASE T_DEFAULT T_RETURN T_ASSERT
%token T_PRIORITY

/* Variable type declaration keywords: */
%token T_TYPEDEF T_STRUCT
%token T_CONST T_OLDCONST T_URGENT T_BROADCAST T_TRUE T_FALSE T_META

/* Uppaal keywords */
%token T_SYSTEM T_PROCESS T_STATE T_BRANCHPOINT T_COMMIT T_INIT T_TRANS T_SELECT
%token T_GUARD T_SYNC T_ASSIGN T_PROBABILITY T_BEFORE T_AFTER T_PROGRESS
%token T_ARROW T_UNCONTROL_ARROW T_IO
%token T_QUERY

/* Property tokens */
%token T_DEADLOCK T_EF T_EG T_AF T_AG T_LEADSTO T_RESULTSET
%token T_EF_PLUS T_AG_PLUS T_EF_MULT T_AG_MULT T_SCENARIO

/* Control Synthesis */
%token T_CONTROL T_CONTROL_T T_SIMULATION

/* Expectation optimization */
%token T_MINEXP T_MAXEXP T_MINPR T_MAXPR T_STRATEGY T_LOAD_STRAT T_SAVE_STRAT

/* Strategy subjection */
%token T_SUBJECT

/* Strategy imitation */
%token T_IMITATE

 /* SMC */
%token T_SIMULATE

/* Gantt chart */
%token T_GANTT

/* Prob... */
%token T_PMAX T_PROBA T_DIAMOND T_BOX T_HASH

/* Miscelaneous: */
%token T_ERROR
%token <string>T_ID T_TYPENAME
%token <number>T_NAT
%token <floating> T_FLOATING
%token T_POS_NEG_MAX
%token T_IMPORT
%token <string> T_CHARARR

/* Get the index of the current location of the system */
%token T_LOCATION

/* Types */
%token T_BOOL T_INT T_CHAN T_CLOCK T_VOID T_SCALAR T_DOUBLE T_STRING

/* Syntax switch tokens */
%token T_NEW T_NEW_DECLARATION T_NEW_LOCAL_DECL T_NEW_INST T_NEW_SYSTEM
%token T_NEW_PARAMETERS T_NEW_INVARIANT T_NEW_GUARD T_NEW_SYNC T_NEW_ASSIGN
%token T_NEW_SELECT T_EXPONENTIALRATE
%token T_OLD T_OLD_DECLARATION T_OLD_LOCAL_DECL T_OLD_INST
%token T_OLD_PARAMETERS T_OLD_INVARIANT T_OLD_GUARD T_OLD_ASSIGN
%token T_PROPERTY T_EXPRESSION T_EXPRESSION_LIST T_XTA_PROCESS

/* LSC */
%token T_INSTANCELINE T_MESSAGE T_UPDATE T_CONDITION

/* SMC */
%token T_MITL_AND T_MITL_OR T_MITL_NEXT
%token T_DYNAMIC T_HYBRID
%token T_SPAWN T_EXIT T_NUMOF

%type <kind> ExpQuantifier ExpPrQuantifier
%type <kind> PathType
%type <number> ArgList FieldDeclList FieldDeclIdList FieldDecl
%type <number> ParameterList FieldInitList
%type <number> OptionalInstanceParameterList ExpressionList NonEmptyExpressionList
%type <prefix> Type TypePrefix
%type <string> Id NonTypeId
%type <kind> UnaryOp AssignOp
%type <flag> VarInit
%type <kind> CmpGLE
%type <kind> BuiltinFunction1 BuiltinFunction2 BuiltinFunction3

%left T_LEADSTO
%right T_AF T_AG T_EF T_EG 'A'  'M'
%right T_AG_PLUS T_EF_PLUS T_AG_MULT T_EF_MULT
%right T_PMAX T_SCENARIO
%left 'U' 'W' 'R'
%right T_FORALL T_EXISTS T_SUM
%right T_ASSIGNMENT T_ASSPLUS T_ASSMINUS T_ASSMULT T_ASSDIV T_ASSMOD T_ASSAND T_ASSOR T_ASSLSHIFT T_ASSRSHIFT T_ASSXOR
%right '?' ':'
%left T_BOOL_OR T_KW_OR T_KW_XOR T_KW_IMPLY
%left T_BOOL_AND T_KW_AND
%left T_OR
%left T_XOR
%left '&'
%left T_EQ T_NEQ
%left T_LT T_LEQ T_GEQ T_GT
%left T_MIN T_MAX
%left T_LSHIFT T_RSHIFT
%left T_MINUS T_PLUS
%left T_MULT T_DIV T_MOD
%right T_EXCLAM T_KW_NOT T_INCREMENT T_DECREMENT UOPERATOR
%left '(' ')' '[' ']' '.' '\''

%union {
    bool flag;
    int number;
    ParserBuilder::PREFIX prefix;
    kind_t kind;
    char string[MAXLEN];
    double floating;
}

/* Expect 1 shift/reduce warning in dangling ELSE part of IF statement. */
/* Expect 2 shift/reduce warning between E[ .. ] smc property & NonTypeId E to build expr. */
%expect 2

%%

Uppaal:
          T_NEW XTA { CALL(@2, @2, done()); }
        | T_NEW_DECLARATION Declarations { }
        | T_NEW_LOCAL_DECL ProcLocalDeclList { }
        | T_NEW_INST Declarations { }
        | T_NEW_SYSTEM XTA { }
        | T_NEW_PARAMETERS ParameterList { }
        | T_NEW_INVARIANT Expression { }
        | T_NEW_SELECT SelectList { }
        | T_NEW_GUARD Expression { CALL(@2, @2, procGuard()); }
        | T_NEW_SYNC SyncExpr { }
        | T_NEW_ASSIGN ExprList { CALL(@2, @2, procUpdate()); }
        | T_PROBABILITY Expression { CALL(@2, @2, procProb()); }
        | T_OLD OldXTA { CALL(@2, @2, done()); }
        | T_OLD_DECLARATION OldDeclaration { }
        | T_OLD_LOCAL_DECL OldVarDeclList { }
        | T_OLD_INST Instantiations { }
        | T_OLD_PARAMETERS OldProcParamList { }
        | T_OLD_INVARIANT OldInvariant { }
        | T_OLD_GUARD OldGuardList { CALL(@2, @2, procGuard()); }
        | T_OLD_ASSIGN ExprList { CALL(@2, @2, procUpdate()); }
        | T_PROPERTY PropertyList {}
        | T_EXPRESSION Expression {}
        | T_EXPRESSION_LIST ExprList {}
        | T_XTA_PROCESS ProcDecl {}
        | T_EXPONENTIALRATE ExpRate {}
        /*LSC*/
        | T_MESSAGE MessExpr { }
        | T_UPDATE ExprList { CALL(@2, @2, procLscUpdate()); }
        | T_CONDITION Expression { CALL(@2, @2, procCondition()); }
        | T_INSTANCELINE InstanceLineExpression { }
        ;

XTA:
        Declarations System QueryList
        ;

Instantiations:
        /* empty */
        | Instantiations Instantiation
        | error ';'
        ;

Instantiation:
        NonTypeId OptionalInstanceParameterList T_ASSIGNMENT NonTypeId '(' {
          CALL(@1, @4, instantiationBegin($1, $2, $4));
        } ArgList ')' ';' {
          CALL(@1, @9, instantiationEnd($1, $2, $4, $7));
        };

InstanceLineExpression:
        NonTypeId {
          CALL(@1, @1, instanceName($1, false));
        }
        | NonTypeId '(' {
          CALL(@1, @1, instanceNameBegin($1));
        } ArgList ')' {
          CALL(@1, @5, instanceNameEnd($1, $4));
        };

OptionalInstanceParameterList:
        /* empty */ { $$ = 0; }
        | '(' ')' {
        	$$ = 0;
        }
        | '(' ParameterList ')' {
        	$$ = $2;
        };

System: SysDecl Progress GanttDecl;

PriorityDecl:
        T_CHAN T_PRIORITY ChannelList ';'
        | T_CHAN T_PRIORITY error ';'
        ;

ChannelList:
        ChanElement { CALL(@1, @1, beginChanPriority()); }
        | ChannelList ',' ChanElement  { CALL(@1, @3, addChanPriority(',')); }
        | ChannelList T_LT ChanElement { CALL(@1, @3, addChanPriority('<')); }
        ;

ChanElement:
        /* Cannot use 'Expression', since we use '<' (T_LT) as a separator. */
        ChanExpression
        | T_DEFAULT { CALL(@1, @1, defaultChanPriority()); }
        ;

ChanExpression:
        NonTypeId { CALL(@1, @1, exprId($1)); }
        | ChanExpression '[' Expression ']' { CALL(@1, @4, exprArray()); }
        ;

SysDecl:
        T_SYSTEM ProcessList ';' { CALL(@1, @1, processListEnd()); }
        | T_SYSTEM error ';' { CALL(@1, @1, processListEnd()); }
        ;

ProcessList:
        NonTypeId { CALL(@1, @1, process($1)); }
        | ProcessList ',' NonTypeId { CALL(@3, @3, process($3)); }
        | ProcessList ProcLessThan NonTypeId { CALL(@3, @3, process($3)); }
        ;

ProcLessThan:
        T_LT { CALL(@1, @1, incProcPriority()); };

Progress:
        /* empty */
        | T_PROGRESS '{' ProgressMeasureList  '}';

ProgressMeasureList:
        /* empty */
        | ProgressMeasureList Expression ':' Expression ';' {
            CALL(@2, @4, declProgress(true));
        }
        | ProgressMeasureList Expression ';' {
            CALL(@2, @2, declProgress(false));
        };

GanttDecl:
        /* empty */
        | T_GANTT '{' GanttDef '}'
        ;

GanttDef:
        /* empty */
        | GanttDef NonTypeId              { CALL(@2, @2, ganttDeclStart($2)); }
          GanttArgs ':' GanttExprList ';' { CALL(@2, @6, ganttDeclEnd());
	}
	;

GanttArgs:
        /* empty */
        | '(' GanttDeclSelect ')'
        ;

GanttDeclSelect:
        Id ':' Type {
            CALL(@1, @3, ganttDeclSelect($1));
        }
        | GanttDeclSelect ',' Id ':' Type {
            CALL(@3, @5, ganttDeclSelect($3));
        }
        ;

GanttExprList:
        GanttExpr
        | GanttExprList ',' GanttExpr
	;

GanttExpr:
        Expression T_ARROW Expression {
	    CALL(@1, @3, ganttEntryStart());
	    CALL(@1, @3, ganttEntryEnd());
        }
        | T_FOR                                                  { CALL(@1, @1, ganttEntryStart()); }
          '(' GanttEntrySelect ')' Expression T_ARROW Expression { CALL(@1, @7, ganttEntryEnd()); }
        ;

GanttEntrySelect:
        Id ':' Type {
            CALL(@1, @3, ganttEntrySelect($1));
        }
        | GanttEntrySelect ',' Id ':' Type {
            CALL(@3, @5, ganttEntrySelect($3));
        }
        ;

Declarations:
        /* empty */
        | Declarations FunctionDecl
        | Declarations ExternDecl
        | Declarations VariableDecl
        | Declarations TypeDecl
        | Declarations ProcDecl
        | Declarations BeforeUpdateDecl
        | Declarations AfterUpdateDecl
        | Declarations Instantiation
        | Declarations PriorityDecl
        | Declarations DynamicDeclaration
        | error ';'
        ;

DynamicDeclaration:
T_DYNAMIC NonTypeId OptionalParameterList {CALL(@1,@3,declDynamicTemplate($2));} ';'  ;

BeforeUpdateDecl: T_BEFORE '{' ExprList '}' { CALL(@3, @3, beforeUpdate()); };

AfterUpdateDecl: T_AFTER '{' ExprList '}' { CALL(@3, @3, afterUpdate()); };

FunctionDecl:
        /* Notice that StatementList will catch all errors. Hence we
         * should be able to guarantee, that once declFuncBegin() has
         * been called, we will also call declFuncEnd().
	 * Correction: No it won't.
	 * int f() { if (cond) { return 0; }
	 * will generate an error, not call declFuncEnd, and the builder
	 * will be left in an inconsistent state. EndBlock fixes that.
     *
     * Correction^2: It did not fix it. Discussion continued at
     * StatementBuilder::declFuncBegin definition
         */
        Type Id OptionalParameterList '{' {
          CALL(@1, @2, declFuncBegin($2));
        } BlockLocalDeclList StatementList EndBlock {
          CALL(@8, @8, declFuncEnd());
        }
        ;
        
EndBlock: '}' | error;

ExternDecl: T_IMPORT T_CHARARR
        {
            CALL(@2, @2, dynamicLoadLib($2));
        } FwdDeclBlock;

FwdDeclBlock:     
          '{' FwdDeclList '}' ';'
        | FwdDecl ';';
                
FwdDeclList:
          FwdDecl ';'
        | FwdDeclList FwdDecl ';'
        ;

FwdDecl: Id T_ASSIGNMENT Type Id OptionalParameterList
        {
            CALL(@1, @4, declExternalFunc($4, $1));
        }
        |
        Type Id OptionalParameterList
        {
            CALL(@1, @2, declExternalFunc($2, $2));
        };

OptionalParameterList:
          '(' ')'
        | '(' ParameterList ')'
        | '(' error ')'
        ;

ParameterList:
          Parameter { $$ = 1; }
        | ParameterList ',' Parameter { $$ = $1+1; }
        ;

Parameter:
          Type '&' NonTypeId ArrayDecl {
          CALL(@1, @4, declParameter($3, true));
        }
        | Type NonTypeId ArrayDecl {
          CALL(@1, @3, declParameter($2, false));
        }
        ;

VariableDecl:
        Type DeclIdList ';' {
            CALL(@1, @3, typePop());
        }
        | Type error ';'
        ;

DeclIdList:
        DeclId
        | DeclIdList ',' DeclId
        ;

DeclId:
        Id {
            CALL(@1, @1, typeDuplicate());
        } ArrayDecl VarInit {
            CALL(@1, @4, declVar($1, $4));
        }
        ;

VarInit:
        /* empty */ { $$ = false; }
        | T_ASSIGNMENT Initializer { $$ = true; }
        ;

Initializer:
        Expression
        | '{' FieldInitList '}' {
          CALL(@1, @3, declInitialiserList($2));
        }
        ;

FieldInitList:
        FieldInit { $$ = 1; }
        | FieldInitList ',' FieldInit { $$ = $1+1; }
        ;

FieldInit:
        Id ':' Initializer {
          CALL(@1, @3, declFieldInit($1));
        }
        | Initializer {
          CALL(@1, @1, declFieldInit(""));
        }
        ;

ArrayDecl:
        { types = 0; } ArrayDecl2;

ArrayDecl2:
        /* empty */
        | '[' Expression ']'        ArrayDecl2 { CALL(@1, @3, typeArrayOfSize(types)); }
        | '[' Type ']' { types++; } ArrayDecl2 { CALL(@1, @3, typeArrayOfType(types--)); }
        | '[' error ']' ArrayDecl2
        ;

TypeDecl:
        T_TYPEDEF Type TypeIdList ';' {
          CALL(@1, @4, typePop());
        }
        | T_TYPEDEF error ';'
        ;

TypeIdList:
        TypeId
        | TypeIdList ',' TypeId
        ;

TypeId:
        Id {
            CALL(@1, @1, typeDuplicate());
        } ArrayDecl {
            CALL(@1, @3, declTypeDef($1));
        }
        ;

Type:
        T_TYPENAME {
            CALL(@1, @1, typeName(ParserBuilder::PREFIX_NONE, $1));
        }
        | TypePrefix T_TYPENAME {
            CALL(@1, @2, typeName($1, $2));
        }
        | T_STRUCT '{' FieldDeclList '}' {
            CALL(@1, @4, typeStruct(ParserBuilder::PREFIX_NONE, $3));
        }
        | TypePrefix T_STRUCT '{' FieldDeclList '}' {
            CALL(@1, @5, typeStruct($1, $4));
        }
        | T_STRUCT '{' error '}' {
          CALL(@1, @4, typeStruct(ParserBuilder::PREFIX_NONE, 0));
        }
        | TypePrefix T_STRUCT '{' error '}' {
          CALL(@1, @5, typeStruct(ParserBuilder::PREFIX_NONE, 0));
        }
        | T_BOOL {
          CALL(@1, @1, typeBool(ParserBuilder::PREFIX_NONE));
        }
        | TypePrefix T_BOOL {
          CALL(@1, @2, typeBool($1));
        }
        | T_DOUBLE {
	    CALL(@1, @1, typeDouble(ParserBuilder::PREFIX_NONE));
        }
        | TypePrefix T_DOUBLE {
	    CALL(@1, @2, typeDouble($1));
	}
        | T_STRING {
	    CALL(@1, @1, typeString(ParserBuilder::PREFIX_NONE));
        }
        | TypePrefix T_STRING {
	    CALL(@1, @2, typeString($1));
	}
        | T_INT {
          CALL(@1, @1, typeInt(ParserBuilder::PREFIX_NONE));
        }
        | TypePrefix T_INT {
          CALL(@1, @2, typeInt($1));
        }
        | T_INT '[' Expression ',' Expression ']'
        {
          CALL(@1, @6, typeBoundedInt(ParserBuilder::PREFIX_NONE));
        }
        | TypePrefix T_INT  '[' Expression ',' Expression ']' {
          CALL(@1, @7, typeBoundedInt($1));
        }
        | T_CHAN {
          CALL(@1, @1, typeChannel(ParserBuilder::PREFIX_NONE));
        }
        | TypePrefix T_CHAN {
          CALL(@1, @2, typeChannel($1));
        }
        | T_CLOCK {
	    CALL(@1, @1, typeClock(ParserBuilder::PREFIX_NONE));
        }
        | T_HYBRID T_CLOCK {
	    CALL(@1, @1, typeClock(ParserBuilder::PREFIX_HYBRID));
	}
        | T_VOID {
          CALL(@1, @1, typeVoid());
        }
        | T_SCALAR '[' Expression ']'
        {
          CALL(@1, @4, typeScalar(ParserBuilder::PREFIX_NONE));
        }
        | TypePrefix T_SCALAR  '[' Expression ']' {
          CALL(@1, @5, typeScalar($1));
        }
        ;

Id:
        NonTypeId { strncpy($$, $1, MAXLEN); }
        | T_TYPENAME { strncpy($$, $1, MAXLEN); }
        ;

NonTypeId:
        T_ID  { strncpy($$, $1 , MAXLEN); }
        | 'A' { strncpy($$, "A", MAXLEN); }
        | 'U' { strncpy($$, "U", MAXLEN); }
        | 'W' { strncpy($$, "W", MAXLEN); }
        | 'R' { strncpy($$, "R", MAXLEN); }
        | 'E' { strncpy($$, "E", MAXLEN); }
        | 'M' { strncpy($$, "M", MAXLEN); }
        | T_SUP { strncpy($$, "sup", MAXLEN); }
        | T_INF { strncpy($$, "inf", MAXLEN); }
        | T_SIMULATION { strncpy($$, "simulation", MAXLEN); }
        ;

FieldDeclList:
        FieldDecl { $$=$1; }
        | FieldDeclList FieldDecl { $$=$1+$2; }
        ;

FieldDecl:
        Type FieldDeclIdList ';' {
          $$ = $2;
          CALL(@1, @3, typePop());
        }
        ;

FieldDeclIdList:
        FieldDeclId { $$=1; }
        | FieldDeclIdList ',' FieldDeclId { $$=$1+1; }
        ;

FieldDeclId:
        Id {
            CALL(@1, @1, typeDuplicate());
        } ArrayDecl {
            CALL(@1, @3, structField($1));
        }
        ;

TypePrefix:
          T_URGENT    { $$ = ParserBuilder::PREFIX_URGENT; }
        | T_BROADCAST { $$ = ParserBuilder::PREFIX_BROADCAST; }
        | T_URGENT T_BROADCAST { $$ = ParserBuilder::PREFIX_URGENT_BROADCAST; }
        | T_CONST  { $$ = ParserBuilder::PREFIX_CONST; }
        | T_META { $$ = ParserBuilder::PREFIX_SYSTEM_META; }
        ;

/*********************************************************************
 * Process declaration
 */

ProcDecl:
        T_PROCESS Id OptionalParameterList '{' {
          CALL(@1, @4, procBegin($2));
        }
        ProcBody '}' {
          CALL(@6, @7, procEnd());
        }
        ;

ProcBody:
        ProcLocalDeclList States LocFlags Init Transitions
	| ProcLocalDeclList States Branchpoints LocFlags Init Transitions
	| /* empty */
        ;

ProcLocalDeclList:
        /* empty */
        | ProcLocalDeclList FunctionDecl
        | ProcLocalDeclList VariableDecl
        | ProcLocalDeclList TypeDecl
        ;

States:
        T_STATE StateDeclList ';'
        | T_STATE error ';'
        ;

StateDeclList:
        StateDecl
        | StateDeclList ',' StateDecl
        ;

StateDecl:
          NonTypeId { CALL(@1, @1, procState($1, false, false)); }
        | NonTypeId '{' ';' ExpRate '}' {
	    CALL(@1, @5, procState($1, false, true));
	}
        | NonTypeId '{' Expression '}' {
	    CALL(@1, @4, procState($1, true, false));
        }
        | NonTypeId '{' Expression ';' ExpRate '}' {
	    CALL(@1, @6, procState($1, true, true));
	}
        | NonTypeId '{' error '}' {
	    CALL(@1, @4, procState($1, false, false));
	}
        ;

Branchpoints:
        T_BRANCHPOINT BranchpointDeclList ';'
        | T_BRANCHPOINT error ';'
        ;

BranchpointDeclList:
        BranchpointDecl
        | BranchpointDeclList ',' BranchpointDecl
        ;

BranchpointDecl:
        NonTypeId {
	    CALL(@1, @1, procBranchpoint($1));
        };

Init:
        T_INIT NonTypeId ';' {
          CALL(@1, @3, procStateInit($2));
        }
        | error ';'
        ;

Transitions:
        /* empty */
        | T_TRANS TransitionList ';'
        | T_TRANS error ';'
        ;

TransitionList:
        Transition
        | TransitionList ',' TransitionOpt
        ;

Transition:
        NonTypeId T_ARROW NonTypeId '{' {
            CALL(@1, @3, procEdgeBegin($1, $3, true));
        } Select Guard Sync Assign Probability '}' {
          strcpy(rootTransId, $1);
          CALL(@1, @9, procEdgeEnd($1, $3));
        }
        | NonTypeId T_UNCONTROL_ARROW NonTypeId '{' {
            CALL(@1, @3, procEdgeBegin($1, $3, false));
        } Select Guard Sync Assign Probability '}' {
          strcpy(rootTransId, $1);
          CALL(@1, @9, procEdgeEnd($1, $3));
        }
        ;

TransitionOpt:
        T_ARROW NonTypeId '{' {
            CALL(@1, @2, procEdgeBegin(rootTransId, $2, true));
        } Select Guard Sync Assign '}' {
            CALL(@1, @7, procEdgeEnd(rootTransId, $2));
        }
        | T_UNCONTROL_ARROW NonTypeId '{' {
            CALL(@1, @2, procEdgeBegin(rootTransId, $2, false));
        } Select Guard Sync Assign '}' {
            CALL(@1, @7, procEdgeEnd(rootTransId, $2));
        }
        | Transition
        ;

Select:
        /* empty */
        | T_SELECT SelectList ';'
        ;

SelectList:
        Id ':' Type {
            CALL(@1, @3, procSelect($1));
        }
        | SelectList ',' Id ':' Type {
            CALL(@3, @5, procSelect($3));
        }
        ;

Guard:
        /* empty */
        | T_GUARD Expression ';' {
          CALL(@2, @2, procGuard());
        }
        | T_GUARD Expression error ';' {
          CALL(@2, @3, procGuard());
        }
        | T_GUARD error ';'
        ;

Sync:
        /* empty */
        | T_SYNC SyncExpr ';'
        | T_SYNC error ';'
        ;

SyncExpr:
        Expression {
	    CALL(@1, @1, procSync(SYNC_CSP));
        }
        | Expression T_EXCLAM {
          CALL(@1, @2, procSync(SYNC_BANG));
        }
        | Expression error T_EXCLAM {
          CALL(@1, @2, procSync(SYNC_BANG));
        }
        | Expression '?' {
          CALL(@1, @2, procSync(SYNC_QUE));
        }
        | Expression error '?' {
          CALL(@1, @2, procSync(SYNC_QUE));
        }
        ;

MessExpr:
        Expression {
          CALL(@1, @1, procMessage(SYNC_QUE));
        }
        | Expression error {
          CALL(@1, @1, procMessage(SYNC_QUE));
        }
        ;

Assign:
        /* empty */
        | T_ASSIGN ExprList ';' {
          CALL(@2, @2, procUpdate());
        }
        | T_ASSIGN error ';'
        ;

Probability:
        /* empty */
        | T_PROBABILITY Expression ';' {
          CALL(@2, @2, procProb());
        }
        | T_PROBABILITY error ';'
        ;

LocFlags:
        /* empty */
        | LocFlags Commit
        | LocFlags Urgent
        ;

Commit:
        T_COMMIT CStateList ';'
        | T_COMMIT error ';'
        ;

Urgent:
        T_URGENT UStateList ';'
        | T_URGENT error ';'
        ;

CStateList:
        NonTypeId {
          CALL(@1, @1, procStateCommit($1));
        }
        | CStateList ',' NonTypeId {
          CALL(@1, @3, procStateCommit($3));
        }
        ;

UStateList:
        NonTypeId {
          CALL(@1, @1, procStateUrgent($1));
        }
        | UStateList ',' NonTypeId {
          CALL(@1, @3, procStateUrgent($3));
        }
        ;

ExpRate:
        Expression
	| Expression ':' Expression {
	    CALL(@1,@3, exprBinary(FRACTION));
	};

/**********************************************************************
 * Uppaal C grammar
 */

Block:
        '{' {
          CALL(@1, @1, blockBegin());
        }
        BlockLocalDeclList StatementList '}' {
          CALL(@2, @4, blockEnd());
        }
        ;

BlockLocalDeclList:
        /* empty */
        | BlockLocalDeclList VariableDecl
        | BlockLocalDeclList TypeDecl
        ;

StatementList:
        /* empty */
        | StatementList Statement
        | StatementList error ';'
        ;

Statement: MatchedStatement /* "standard" way of solving if-then-else shift-reduce conflict */
        | UnmatchedStatement
        ;

IfCondition: T_IF '(' { CALL(@1, @2, ifBegin()); } ExprList ')' { CALL(@3, @3, ifCondition()); }
        | T_IF '(' error ')'
        ;

IfConditionThenMatched: IfCondition MatchedStatement T_ELSE { CALL(@1, @3, ifThen()); };

MatchedStatement: IfConditionThenMatched MatchedStatement {
	    CALL(@1, @2, ifEnd(true));
	}
        | OtherStatement
	;

UnmatchedStatement: IfCondition Statement {
            CALL(@2, @2, ifThen());
            CALL(@1, @2, ifEnd(false));
	}
        | IfConditionThenMatched UnmatchedStatement {
	    CALL(@1, @2, ifEnd(true));
	}
        ;

OtherStatement:
        Block
        | ';' {
          CALL(@1, @1, emptyStatement());
        }
        | Expression ';' {
          CALL(@1, @2, exprStatement());
        }
        | ForStatement
	| WhileStatement
        | T_BREAK ';' {
            CALL(@1, @2, breakStatement());
          }
        | T_CONTINUE ';' {
          CALL(@1, @2, continueStatement());
        }
        | T_SWITCH '(' ExprList ')' {
            CALL(@1, @4, switchBegin());
        }
          '{' SwitchCaseList '}' {
               CALL(@5, @7, switchEnd());
          }
        | T_RETURN Expression ';' {
          CALL(@1, @3, returnStatement(true));
        }
        | T_RETURN ';' {
          CALL(@1, @2, returnStatement(false));
        }
        | T_ASSERT Expression ';' {
	    CALL(@1, @2, assertStatement());
	}
        ;

ForStatement: T_FOR '(' ExprList ';' ExprList ';' ExprList ')' {
            CALL(@1, @8, forBegin());
        }
        Statement {
            CALL(@9, @9, forEnd());
        }
        | T_FOR '(' Id ':' Type ')' {
            CALL(@1, @6, iterationBegin($3));
        }
        Statement {
            CALL(@7, @7, iterationEnd($3));
        }
        | T_FOR '(' error ')' Statement
	;

WhileStatement: T_WHILE '(' {
            CALL(@1, @2, whileBegin());
        }
        ExprList ')' Statement {
            CALL(@3, @4, whileEnd());
	}
        | T_WHILE '(' error ')' Statement
        | T_DO {
            CALL(@1, @1, doWhileBegin());
	}
          Statement T_WHILE '(' ExprList ')' ';' {
            CALL(@2, @7, doWhileEnd());
        }
        ;

SwitchCaseList: SwitchCase
        | SwitchCaseList SwitchCase
        ;

SwitchCase:
        T_CASE Expression ':' {
	    CALL(@1, @3, caseBegin());
        }
        StatementList {
            CALL(@4, @4, caseEnd());
	}
        | T_DEFAULT ':' {
            CALL(@1, @2, defaultBegin());
        }
        StatementList {
            CALL(@3, @3, defaultEnd());
        }
        ;

ExprList:
          Expression
        | ExprList ',' Expression {
          CALL(@1, @3, exprComma());
        };

Expression:
        T_FALSE {
	    CALL(@1, @1, exprFalse());
        }
        | T_TRUE {
	    CALL(@1, @1, exprTrue());
        }
        | T_NAT  {
	    CALL(@1, @1, exprNat($1));
        }
        | T_FLOATING {
	    CALL(@1, @1, exprDouble($1));
	}
        | T_CHARARR
        {
            CALL(@1, @1, exprString($1));
        }
        | BuiltinFunction1 '(' Expression ')' {
	    CALL(@1, @4, exprBuiltinFunction1($1));
	}
        | BuiltinFunction2 '(' Expression ',' Expression ')' {
	    CALL(@1, @6, exprBuiltinFunction2($1));
	}
        | BuiltinFunction3 '(' Expression ',' Expression ',' Expression ')' {
	    CALL(@1, @8, exprBuiltinFunction3($1));
	}
        | NonTypeId {
	    CALL(@1, @1, exprId($1));
        }
        | Expression '(' {
            CALL(@1, @2, exprCallBegin());
        } ArgList ')'  {
            CALL(@1, @5, exprCallEnd($4));
        }
        | Expression '(' {
            CALL(@1, @2, exprCallBegin());
        } error ')' {
            CALL(@1, @4, exprCallEnd(0));
        }
        | Expression '[' Expression ']' {
          CALL(@1, @4, exprArray());
        }
        | Expression '[' error ']' {
          CALL(@1, @4, exprFalse());
        }
        | '(' Expression ')'
        | '(' error ')' {
          CALL(@1, @3, exprFalse());
        }
        | Expression T_INCREMENT {
          CALL(@1, @2, exprPostIncrement());
        }
        | T_INCREMENT Expression {
          CALL(@1, @2, exprPreIncrement());
        }
        | Expression T_DECREMENT {
          CALL(@1, @2, exprPostDecrement());
        }
        | T_DECREMENT Expression {
          CALL(@1, @2, exprPreDecrement());
        }
        | T_MINUS T_POS_NEG_MAX {
	  CALL(@1, @2, exprNat(std::numeric_limits<int>::min()));
	}
        | UnaryOp Expression {
          CALL(@1, @2, exprUnary($1));
        } %prec UOPERATOR
        | Expression T_LT Expression {
          CALL(@1, @3, exprBinary(LT));
        }
        | Expression T_LEQ Expression {
          CALL(@1, @3, exprBinary(LE));
        }
        | Expression T_EQ Expression {
          CALL(@1, @3, exprBinary(EQ));
        }
        | Expression T_NEQ Expression {
          CALL(@1, @3, exprBinary(NEQ));
        }
        | Expression T_GT Expression {
          CALL(@1, @3, exprBinary(GT));
        }
        | Expression T_GEQ Expression {
          CALL(@1, @3, exprBinary(GE));
        }
        | Expression T_PLUS Expression {
          CALL(@1, @3, exprBinary(PLUS));
        }
        | Expression T_MINUS Expression {
          CALL(@1, @3, exprBinary(MINUS));
        }
        | Expression T_MULT Expression {
          CALL(@1, @3, exprBinary(MULT));
        }
        | Expression T_DIV Expression {
          CALL(@1, @3, exprBinary(DIV));
        }
        | Expression T_MOD Expression {
          CALL(@1, @3, exprBinary(MOD));
        }
        | Expression '&' Expression {
          CALL(@1, @3, exprBinary(BIT_AND));
        }
        | Expression T_OR Expression {
          CALL(@1, @3, exprBinary(BIT_OR));
        }
        | Expression T_XOR Expression {
          CALL(@1, @3, exprBinary(BIT_XOR));
        }
        | Expression T_LSHIFT Expression {
          CALL(@1, @3, exprBinary(BIT_LSHIFT));
        }
        | Expression T_RSHIFT Expression {
          CALL(@1, @3, exprBinary(BIT_RSHIFT));
        }
        | Expression T_BOOL_AND Expression {
          CALL(@1, @3, exprBinary(AND));
        }
        | Expression T_BOOL_OR Expression {
          CALL(@1, @3, exprBinary(OR));
        }
        | Expression '?' Expression ':' Expression {
          CALL(@1, @5, exprInlineIf());
        } %prec T_ASSIGNMENT
        | Expression '.' T_LOCATION { 
            CALL(@1, @3, exprLocation());
        }
        | Expression '.' NonTypeId {
          CALL(@1, @3, exprDot($3));
        }
        | Expression '\'' {
            CALL(@1, @2, exprUnary(RATE));
        }
        | T_DEADLOCK {
          CALL(@1, @1, exprDeadlock());
        }
        | Expression T_KW_IMPLY {
          CALL(@1, @1, exprUnary(NOT));
        } Expression {
          CALL(@3, @3, exprBinary(OR));
        }
        | Expression T_KW_AND Expression {
          CALL(@1, @3, exprBinary(AND));
        }
        | Expression T_KW_OR Expression {
          CALL(@1, @3, exprBinary(OR));
        }
        | Expression T_KW_XOR Expression {
	    CALL(@1, @3, exprBinary(XOR));
	}
        | Expression T_MIN Expression {
            CALL(@1, @3, exprBinary(MIN));
        }
        | Expression T_MAX Expression {
            CALL(@1, @3, exprBinary(MAX));
        }
        | T_SUM '(' Id ':' Type ')' {
            CALL(@1, @6, exprSumBegin($3));
        } Expression {
            CALL(@1, @8, exprSumEnd($3));
        } %prec T_SUM
	    | T_FORALL '(' Id ':' Type ')' {
            CALL(@1, @6, exprForAllBegin($3));
        } Expression {
            CALL(@1, @8, exprForAllEnd($3));
        } %prec T_FORALL
        | T_EXISTS '(' Id ':' Type ')' {
            CALL(@1, @6, exprExistsBegin($3));
        } Expression {
            CALL(@1, @8, exprExistsEnd($3));
        } %prec T_EXISTS
	| DynamicExpression
	| MITLExpression
        | Assignment
        ;

DynamicExpression:
        T_SPAWN NonTypeId {
	    CALL(@1,@2, exprId($2));
	} '(' ArgList ')' {
	    CALL(@1,@6, exprSpawn($5));
	}
        | T_EXIT '(' ')' {
	    CALL(@1,@3, exprExit());
	}
        | T_NUMOF '(' NonTypeId ')'{
	    CALL(@3,@3, exprId($3));
	    CALL(@1,@4, exprNumOf());
	}
        | T_FORALL '(' Id ':' NonTypeId {
	    CALL(@1,@5, exprId($5));
	    CALL(@1,@5, exprForAllDynamicBegin($3,$5));
	} ')'  '(' Expression ')'   {
	    CALL(@1,@8, exprForAllDynamicEnd($3));
	}
        | T_EXISTS '(' Id ':' NonTypeId {
	    CALL(@1,@5, exprId($5));
	    CALL(@1,@5, exprExistsDynamicBegin($3,$5));
	} ')' '(' Expression ')'  {
	    CALL(@1,@8, exprExistsDynamicEnd($3));
	}
        | T_SUM '(' Id ':' NonTypeId {
	    CALL(@1,@5, exprId($5));
	    CALL(@1,@5, exprSumDynamicBegin($3,$5));
	} ')' Expression   {
	    CALL(@1,@8, exprSumDynamicEnd($3));
	}
        | T_FOREACH '(' Id ':' NonTypeId {
	    CALL(@1,@5, exprId($5));
	    CALL(@1,@5, exprForeachDynamicBegin($3,$5));
	} ')' Expression   {
	    CALL(@1,@8, exprForeachDynamicEnd($3));
	}
        ;


Assignment:
        Expression AssignOp Expression {
          CALL(@1, @3, exprAssignment($2));
        } %prec T_ASSIGNMENT;

AssignOp:
        /* = += -= /= %= &= |= ^= <<= >>= */
          T_ASSIGNMENT { $$ = ASSIGN; }
        | T_ASSPLUS   { $$ = ASSPLUS; }
        | T_ASSMINUS  { $$ = ASSMINUS; }
        | T_ASSDIV    { $$ = ASSDIV; }
        | T_ASSMOD    { $$ = ASSMOD; }
        | T_ASSMULT   { $$ = ASSMULT; }
        | T_ASSAND    { $$ = ASSAND; }
        | T_ASSOR     { $$ = ASSOR; }
        | T_ASSXOR    { $$ = ASSXOR; }
        | T_ASSLSHIFT { $$ = ASSLSHIFT; }
        | T_ASSRSHIFT { $$ = ASSRSHIFT; }
        ;

UnaryOp:
        /* - + ! */
        T_MINUS       { $$ = MINUS; }
        | T_PLUS      { $$ = PLUS; }
        | T_EXCLAM    { $$ = NOT; }
        | T_KW_NOT    { $$ = NOT; }
        ;

BuiltinFunction1:
          T_ABS   { $$ = ABS_F; }
        | T_FABS   { $$ = FABS_F; }
        | T_EXP    { $$ = EXP_F; }
        | T_EXP2   { $$ = EXP2_F; }
        | T_EXPM1  { $$ = EXPM1_F; }
        | T_LN     { $$ = LN_F; }
        | T_LOG    { $$ = LOG_F; }
        | T_LOG10  { $$ = LOG10_F; }
        | T_LOG2   { $$ = LOG2_F; }
        | T_LOG1P  { $$ = LOG1P_F; }
        | T_SQRT   { $$ = SQRT_F; }
        | T_CBRT   { $$ = CBRT_F; }
        | T_SIN    { $$ = SIN_F; }
        | T_COS    { $$ = COS_F; }
        | T_TAN    { $$ = TAN_F; }
        | T_ASIN   { $$ = ASIN_F; }
        | T_ACOS   { $$ = ACOS_F; }
        | T_ATAN   { $$ = ATAN_F; }
        | T_SINH   { $$ = SINH_F; }
        | T_COSH   { $$ = COSH_F; }
        | T_TANH   { $$ = TANH_F; }
        | T_ASINH  { $$ = ASINH_F; }
        | T_ACOSH  { $$ = ACOSH_F; }
        | T_ATANH  { $$ = ATANH_F; }
        | T_ERF    { $$ = ERF_F; }
        | T_ERFC   { $$ = ERFC_F; }
        | T_TGAMMA { $$ = TGAMMA_F; }
        | T_LGAMMA { $$ = LGAMMA_F; }
        | T_CEIL   { $$ = CEIL_F; }
        | T_FLOOR  { $$ = FLOOR_F; }
        | T_TRUNC  { $$ = TRUNC_F; }
        | T_ROUND  { $$ = ROUND_F; }
        | T_FINT   { $$ = FINT_F; }
        | T_ILOGB  { $$ = ILOGB_F; }
        | T_LOGB   { $$ = LOGB_F; }
        | T_FPCLASSIFY { $$ = FPCLASSIFY_F; }
        | T_ISFINITE { $$ = ISFINITE_F; }
        | T_ISINF  { $$ = ISINF_F; }
        | T_ISNAN  { $$ = ISNAN_F; }
        | T_ISNORMAL { $$ = ISNORMAL_F; }
        | T_SIGNBIT { $$ = SIGNBIT_F; }
        | T_ISUNORDERED { $$ = ISUNORDERED_F; }
        | T_RANDOM { $$ = RANDOM_F; }
        | T_RANDOM_POISSON { $$ = RANDOM_POISSON_F; }
        ;

BuiltinFunction2:
          T_FMOD   { $$ = FMOD_F; }
        | T_FMAX   { $$ = FMAX_F; }
        | T_FMIN   { $$ = FMIN_F; }
        | T_FDIM   { $$ = FDIM_F; }
        | T_POW    { $$ = POW_F; }
        | T_HYPOT  { $$ = HYPOT_F; }
        | T_ATAN2  { $$ = ATAN2_F; }
        | T_LDEXP  { $$ = LDEXP_F; }
        | T_NEXTAFTER { $$ = NEXTAFTER_F; }
        | T_COPYSIGN { $$ = COPYSIGN_F; }
        | T_RANDOM_ARCSINE { $$ = RANDOM_ARCSINE_F; }
        | T_RANDOM_BETA    { $$ = RANDOM_BETA_F;    }
        | T_RANDOM_GAMMA   { $$ = RANDOM_GAMMA_F;   }
        | T_RANDOM_NORMAL  { $$ = RANDOM_NORMAL_F;  }
        | T_RANDOM_WEIBULL { $$ = RANDOM_WEIBULL_F; }
        ;

BuiltinFunction3:
          T_FMA    { $$ = FMA_F; }
        | T_RANDOM_TRI { $$ = RANDOM_TRI_F; }
        ;

ArgList:
        /* The result is the number of expressions as parameters */
        /* empty */ { $$=0; }
        | Expression {
            $$ = 1;
        }
        | ArgList ',' Expression {
            $$ = $1 + 1;
        }
        ;

/***********************************************************************
 * Old XTA format grammar
 */

OldXTA:
        OldDeclaration Instantiations System;


OldDeclaration:
        /* empty */
        | OldDeclaration OldVarDecl
        | OldDeclaration OldProcDecl
        ;

OldVarDecl:
        VariableDecl
        | T_OLDCONST {
          CALL(@1, @1, typeInt(ParserBuilder::PREFIX_CONST));
        } OldConstDeclIdList ';' {
          CALL(@1, @3, typePop());
        }
        | T_OLDCONST error ';';

OldConstDeclIdList:
        OldConstDeclId
        | OldConstDeclIdList ',' OldConstDeclId
        ;

OldConstDeclId:
        NonTypeId {
          CALL(@1, @1, typeDuplicate());
        } ArrayDecl Initializer {
          CALL(@1, @4, declVar($1, true));
        }
        ;

/*********************************************************************
 * Old Process declaration
 */
OldProcDecl:
        T_PROCESS Id OldProcParams '{' {
          CALL(@1, @4, procBegin($2));
        }
        OldProcBody '}' {
          CALL(@5, @6, procEnd());
        }
        | T_PROCESS Id OldProcParams error '{' {
          CALL(@1, @5, procBegin($2));
        }
        OldProcBody '}' {
          CALL(@6, @7, procEnd());
        }
        | T_PROCESS Id error '{' {
          CALL(@1, @4, procBegin($2));
        }
        OldProcBody '}' {
          CALL(@5, @6, procEnd());
        }
        | T_PROCESS error '{' {
          CALL(@1, @3, procBegin("_"));
        }
        OldProcBody '}' {
          CALL(@4, @5, procEnd());
        }
        | T_PROCESS Id '{' {
          CALL(@1, @3, procBegin($2));
        }
        OldProcBody '}' {
          CALL(@4, @5, procEnd());
        }
        ;

OldProcParams:
        '(' ')'
        | '(' OldProcParamList ')'
        | '(' error ')'
        ;

OldProcParamList:
        OldProcParam {
          CALL(@1, @1, typePop());
        }
        | OldProcConstParam
        | OldProcParamList ';' OldProcParam {
          CALL(@1, @3, typePop());
        }
        | OldProcParamList ';' OldProcConstParam
        ;

OldProcParam:
        Type {
            CALL(@1, @1, typeDuplicate());
        } NonTypeId ArrayDecl {
            CALL(@1, @4, declParameter($3, true));
        }
        | OldProcParam {
            CALL(@1, @1, typeDuplicate());
        } ',' NonTypeId ArrayDecl {
            CALL(@1, @5, declParameter($4, true));
        }
        ;

OldProcConstParam:
        T_OLDCONST {
            CALL(@1, @1, typeInt(ParserBuilder::PREFIX_CONST));
        } NonTypeId ArrayDecl {
            CALL(@3, @4, declParameter($3, false));
        }
        | OldProcConstParam ',' {
            CALL(@1, @1, typeInt(ParserBuilder::PREFIX_CONST));
        } NonTypeId ArrayDecl {
            CALL(@4, @5, declParameter($4, false));
        }
        ;

OldProcBody:
        OldVarDeclList OldStates LocFlags Init OldTransitions
        ;

OldVarDeclList:
        /* empty */
        | OldVarDeclList OldVarDecl
        ;

OldStates:
        T_STATE OldStateDeclList ';'
        | error ';'
        ;

OldStateDeclList:
        OldStateDecl
        | OldStateDeclList ',' OldStateDecl
        ;

OldStateDecl:
        NonTypeId {
	    CALL(@1, @1, procState($1, false, false));
        }
        | NonTypeId '{' OldInvariant '}' {
	    CALL(@1, @4, procState($1, true, false));
        }
        ;

OldInvariant:
        Expression
        | Expression error ',' {
        }
        | OldInvariant ',' Expression {
          CALL(@1, @3, exprBinary(AND));
        }
        ;

OldTransitions:
        /* empty */
        | T_TRANS OldTransitionList ';'
        | T_TRANS error ';'
        ;

OldTransitionList:
        OldTransition
        | OldTransitionList ',' OldTransitionOpt
        ;

OldTransition:
        NonTypeId T_ARROW NonTypeId '{' {
            CALL(@1, @3, procEdgeBegin($1, $3, true));
        } OldGuard Sync Assign '}' {
            strcpy(rootTransId, $1);
            CALL(@1, @8, procEdgeEnd($1, $3));
        }
        ;


OldTransitionOpt:
        T_ARROW NonTypeId '{' {
            CALL(@1, @2, procEdgeBegin(rootTransId, $2, true));
        } OldGuard Sync Assign '}' {
            CALL(@1, @7, procEdgeEnd(rootTransId, $2));
        }
        | OldTransition
        ;

OldGuard:
        /* empty */
        | T_GUARD OldGuardList ';' {
          CALL(@2, @2, procGuard());
        }
        | T_GUARD OldGuardList error ';' {
          CALL(@2, @3, procGuard());
        }
        ;

OldGuardList:
        Expression
        | OldGuardList ',' Expression {
          CALL(@1, @3, exprBinary(AND));
        }
        ;

/* TIGA-SMC Expanded syntax */
        
ExpQuantifier:
         T_MINEXP { $$ = MIN_EXP;} 
         | T_MAXEXP { $$ = MAX_EXP;};
         
ExpPrQuantifier:
         T_MINPR { $$ = MIN_EXP;} 
         | T_MAXPR { $$ = MAX_EXP;};
        
SubjectionList: // do not allow multiple subjections for the time being
        /*Id ',' SubjectionList {
          CALL(@1, @1, subjection($1));
        }
        |*/ Id {
          CALL(@1, @1, subjection($1));
        };

Subjection: |   // empty for no subjection
         T_SUBJECT SubjectionList;

Imitation: |
         T_IMITATE Id {
            CALL(@1, @2, imitation($2));
        };

PropertyList:
          PropertyList2 Property;

PropertyList2:
        /* empty */
        | PropertyList2 Property '\n'
	;

QueryList:
        /* empty */
	| QueryList Query
	;

Query:
        T_QUERY '{' Property '}'
        | T_QUERY '{' error '}'
	;

BoolOrKWAnd:
        T_KW_AND | T_BOOL_AND;

SubProperty:
        T_AF Expression {
	    CALL(@1, @2, exprUnary(AF));
	}
        | T_AG '(' Expression BoolOrKWAnd T_AF Expression ')' {
            CALL(@5, @6, exprUnary(AF));
            CALL(@3, @6, exprBinary(AND));
            CALL(@1, @7, exprUnary(AG));
        }
        | T_AG Expression {
	    CALL(@1, @2, exprUnary(AG));
        }
	| T_EF Expression {
	    CALL(@1, @2, exprUnary(EF));
        }
	| T_EG Expression {
	    CALL(@1, @2, exprUnary(EG));
        }
	| Expression T_LEADSTO Expression {
	    CALL(@1, @3, exprBinary(LEADSTO));
        }
	| 'A' '[' Expression 'U' Expression ']' {
	    CALL(@1, @6, exprBinary(A_UNTIL));
        }
	| 'A' '[' Expression 'W' Expression ']' {
	    CALL(@1, @6, exprBinary(A_WEAKUNTIL));
        }
;

Features: {
        CALL(@0, @0, exprTrue());
        CALL(@0, @0, exprTrue());
    }
    | BracketExprList T_ARROW BracketExprList;

AssignablePropperty:
    T_CONTROL ':' SubProperty Subjection {
        CALL(@1, @3, exprUnary(CONTROL));
        CALL(@1, @3, property());
    }
    | T_CONTROL_T T_MULT '(' Expression ',' Expression ')' ':' SubProperty {
	CALL(@1, @9, exprTernary(CONTROL_TOPT));
	CALL(@1, @9, property());
    }
    | T_CONTROL_T T_MULT '(' Expression ')' ':' SubProperty {
	CALL(@1, @7, exprBinary(CONTROL_TOPT_DEF1));
	CALL(@1, @7, property());
    }
    | T_CONTROL_T T_MULT ':' SubProperty {
	CALL(@1, @4, exprUnary(CONTROL_TOPT_DEF2));
	CALL(@1, @4, property());
    }
    | T_EF T_CONTROL ':' SubProperty Subjection {
	CALL(@1, @4, exprUnary(EF_CONTROL));
	CALL(@1, @4, property());
    }
    | BracketExprList T_CONTROL ':' SubProperty Subjection {
        CALL(@1, @4, exprBinary(PO_CONTROL));
	CALL(@1, @4, property());
    }
    | ExpQuantifier '(' Expression ')' '[' BoundType ']' Features ':' PathType Expression Subjection Imitation
    {
        CALL(@1, @12, exprMinMaxExp($1,  ParserBuilder::EXPRPRICE, $10));
	CALL(@1, @12, property());
    }
    | ExpQuantifier '[' BoundType ']' Features ':' PathType Expression Subjection Imitation
    {
        CALL(@1, @8, exprMinMaxExp($1, ParserBuilder::TIMEPRICE, $7));
	CALL(@1, @9, property());
    }
    | ExpPrQuantifier '[' BoundType ']' Features ':' PathType Expression Subjection Imitation {
        CALL(@1, @8, exprMinMaxExp($1, ParserBuilder::PROBAPRICE, $7));
	CALL(@1, @9, property());
    }
    | T_LOAD_STRAT Features '(' Expression ')' {
        CALL(@1, @5, exprLoadStrategy());
        CALL(@1, @5, property());
    }
    ;
/**
    | T_MINPR { $$ = MIN_PR;}
    | T_MAXPR { $$ = MAX_PR;}
*/

PropertyExpr:
    SubProperty Subjection {
        CALL(@1, @1, property());
    }
    | T_PMAX Expression {  // Deprecated, comes from old uppaal-prob.
	CALL(@1, @2, exprUnary(PMAX));
        CALL(@1, @2, property());
    }
    | AssignablePropperty
    | T_SCENARIO ':' NonTypeId {
        CALL(@1, @3, scenario($3)); //check if all instances in the scenario
                                    //correspond to TA processes in the system
        CALL(@1, @3, exprScenario($3));
        CALL(@1, @3, property());
    }
    | T_PROBA SMCBounds '(' PathType Expression ')' CmpGLE T_FLOATING Subjection {
	CALL(@1, @9, exprProbaQualitative($4, $7, $8));
        CALL(@1, @9, property());
    }
    | T_PROBA SMCBounds '(' PathType Expression ')' Subjection {
        CALL(@6, @6, exprTrue()); // push a trivial stop-predicate (see next rule)
        CALL(@1, @7, exprProbaQuantitative($4));
	CALL(@1, @7, property());
    }
    | T_PROBA SMCBounds '(' Expression 'U' Expression ')' Subjection {
        CALL(@1, @8, exprProbaQuantitative(DIAMOND));
	CALL(@1, @8, property());
    }
    | T_PROBA SMCBounds '(' PathType Expression ')' T_GEQ
      T_PROBA SMCBounds '(' PathType Expression ')' Subjection {
	CALL(@1, @14, exprProbaCompare($4, $11));
	CALL(@1, @14, property());
    }
    | T_PROBA SMCBounds '(' PathType Expression ')' T_SUBJECT SubjectionList T_GEQ
      T_PROBA SMCBounds '(' PathType Expression ')' Subjection {
	CALL(@1, @16, exprProbaCompare($4, $13));
	CALL(@1, @16, property());
    }//T_SUBJECT SubjectionList
    | T_SIMULATE SMCBounds '{' NonEmptyExpressionList '}' Subjection {
        CALL(@1, @6, exprSimulate($4));
        CALL(@1, @6, property());
    }
    | T_SIMULATE SMCBounds '{' NonEmptyExpressionList '}' ':' Expression Subjection {
	CALL(@1, @8, exprSimulate($4, true));
	CALL(@1, @8, property());
    }
    | T_SIMULATE SMCBounds '{' NonEmptyExpressionList '}' ':' T_NAT ':' Expression Subjection {
        CALL(@1, @10, exprSimulate($4, true, $7));
	CALL(@1, @10, property());
    }
    | 'E' SMCBounds '(' Id ':' Expression ')' Subjection {
        CALL(@1, @8, exprProbaExpected($4));
	CALL(@1, @8, property());
    }
    | T_PROBA Expression Subjection {
	CALL(@1, @3, exprMitlFormula());
	CALL(@1, @3, property());
    }
    | T_SAVE_STRAT '(' Expression ',' Id ')' {
        CALL(@1, @6, subjection($5));
        CALL(@1, @3, exprSaveStrategy());
        CALL(@1, @6, property());
    }
    ;

MITLExpression :
    '(' Expression 'U' '['  T_NAT ',' T_NAT ']' Expression ')' {
	    CALL(@1,@10, exprMitlUntil($5,$7));
    }
    | '(' Expression 'R' '['  T_NAT ',' T_NAT ']' Expression ')' {
        CALL(@1,@10, exprMitlRelease($5,$7));
    }
    | '(' T_MITL_NEXT Expression ')' {
        CALL(@1,@4, exprMitlNext());
    }
    | '(' T_DIAMOND '[' T_NAT ',' T_NAT ']' Expression ')' {
	    CALL(@1,@4, exprMitlDiamond($4,$6));
    }
    | '(' T_BOX '[' T_NAT ',' T_NAT ']' Expression ')' {
        CALL(@1,@4, exprMitlBox($4,$6));
    }
    ;

SMCBounds:
    '[' BoundType ']' {
	CALL(@1, @1, exprNat(-1));
    }
    | '[' BoundType ';' T_NAT ']' {
	CALL(@1, @3, exprNat($4));
    };

BoundType:
          T_HASH T_LEQ { CALL(@1, @2, exprNat(0)); } Expression
        | T_LEQ { CALL(@1, @1, exprNat(1)); } Expression
        | Expression T_LEQ Expression
        ;

CmpGLE:
        T_GEQ { $$ = GE; }
        | T_LEQ { $$ = LE; }
        ;

PathType:
	    T_BOX { $$ = BOX; }
	    | T_DIAMOND { $$ = DIAMOND; }
	    ;

BracketExprList:
	'{' ExpressionList '}' {
	    CALL(@1, @3, exprNary(LIST,$2));
	};

/* There is an ExprList but it's not a list, rather
 * a binary tree built with commas.
 */

ExpressionList:
	/* nothing */ { $$ = 0; }
        | NonEmptyExpressionList
        ;

NonEmptyExpressionList:
        Expression { $$ = 1; }
        | NonEmptyExpressionList ',' Expression { $$ = $1+1; }
        ;

SupPrefix:
        T_SUP ':' {
	    CALL(@1, @2, exprTrue());
	}
        | T_SUP '{' Expression '}' ':'
	;

InfPrefix:
	T_INF ':' {
	    CALL(@1, @2, exprTrue());
	}
        | T_INF '{' Expression '}' ':'
	;
        
            
StrategyAssignment: 
    T_STRATEGY Id T_ASSIGNMENT AssignablePropperty { 
            CALL(@1, @3, strategyDeclaration($2));
        };

Property:
	/* empty */
        | StrategyAssignment
        | PropertyExpr
	| SupPrefix NonEmptyExpressionList Subjection {
	    CALL(@1, @2, exprNary(LIST,$2));
            CALL(@1, @2, exprBinary(SUP_VAR));
	    CALL(@1, @2, property());
        }
	| InfPrefix NonEmptyExpressionList Subjection {
	    CALL(@1, @2, exprNary(LIST,$2));
            CALL(@1, @2, exprBinary(INF_VAR));
	    CALL(@1, @2, property());
        };

%%

#include "lexer.cc"

static void utap_error(const char* msg)
{
    ch->setPosition(yylloc.start, yylloc.end);
    ch->handleError(TypeException{msg});
}

static void setStartToken(xta_part_t part, bool newxta)
{
    switch (part)
    {
    case S_XTA:
        syntax_token = newxta ? T_NEW : T_OLD;
        break;
    case S_DECLARATION:
        syntax_token = newxta ? T_NEW_DECLARATION : T_OLD_DECLARATION;
        break;
    case S_LOCAL_DECL:
        syntax_token = newxta ? T_NEW_LOCAL_DECL : T_OLD_LOCAL_DECL;
        break;
    case S_INST:
        syntax_token = newxta ? T_NEW_INST : T_OLD_INST;
        break;
    case S_SYSTEM:
        syntax_token = T_NEW_SYSTEM;
        break;
    case S_PARAMETERS:
        syntax_token = newxta ? T_NEW_PARAMETERS : T_OLD_PARAMETERS;
        break;
    case S_INVARIANT:
        syntax_token = newxta ? T_NEW_INVARIANT : T_OLD_INVARIANT;
        break;
    case S_EXPONENTIALRATE:
	syntax_token = T_EXPONENTIALRATE;
	break;
    case S_SELECT:
        syntax_token = T_NEW_SELECT;
        break;
    case S_GUARD:
        syntax_token = newxta ? T_NEW_GUARD : T_OLD_GUARD;
        break;
    case S_SYNC:
        syntax_token = T_NEW_SYNC;
        break;
    case S_ASSIGN:
        syntax_token = newxta ? T_NEW_ASSIGN : T_OLD_ASSIGN;
        break;
    case S_EXPRESSION:
        syntax_token = T_EXPRESSION;
        break;
    case S_EXPRESSION_LIST:
        syntax_token = T_EXPRESSION_LIST;
        break;
    case S_PROPERTY:
        syntax_token = T_PROPERTY;
        break;
    case S_XTA_PROCESS:
        syntax_token = T_XTA_PROCESS;
        break;
    case S_PROBABILITY:
        syntax_token = T_PROBABILITY;
        break;
    // LSC
    case S_INSTANCELINE:
        syntax_token = T_INSTANCELINE;
        break;
    case S_MESSAGE:
        syntax_token = T_MESSAGE;
        break;
    case S_UPDATE:
        syntax_token = T_UPDATE;
        break;
    case S_CONDITION:
        syntax_token = T_CONDITION;
        break;
    }
}

static int32_t parseXTA(ParserBuilder *aParserBuilder,
        		bool newxta, xta_part_t part, std::string xpath)
{
    // Select syntax
    syntax = newxta ? syntax_t::NEW_GUIDING : syntax_t::OLD_GUIDING;
    setStartToken(part, newxta);

    // Set parser builder
    ch = aParserBuilder;

    // Reset position tracking
    tracker.setPath(ch, xpath);

    // Parse string
    int res = 0;

    if (utap_parse())
    {
        res = -1;
    }

    ch = NULL;
    return res;
}

static int32_t parseProperty(ParserBuilder *aParserBuilder, const std::string& xpath)
{
    // Select syntax
    syntax = syntax_t::PROPERTY;
    setStartToken(S_PROPERTY, false);

    // Set parser builder
    ch = aParserBuilder;

    // Reset position tracking
    tracker.setPath(ch, xpath);

    return utap_parse() ? -1 : 0;
}

int32_t parseXTA(const char *str, ParserBuilder *builder,
        	 bool newxta, xta_part_t part, std::string xpath)
{
    utap__scan_string(str);
    int32_t res = parseXTA(builder, newxta, part, xpath);
    utap__delete_buffer(YY_CURRENT_BUFFER);
    return res;
}

const char* utap_builtin_declarations() {
return
"const int INT8_MIN   =        -128;\n"
"const int INT8_MAX   =         127;\n"
"const int UINT8_MAX  =         255;\n"
"const int INT16_MIN  =      -32768;\n"
"const int INT16_MAX  =       32767;\n"
"const int UINT16_MAX =       65535;\n"
"const int INT32_MIN  = -2147483648;\n"
"const int INT32_MAX  =  2147483647;\n"
"typedef int[INT8_MIN,INT8_MAX]   int8_t;\n"
"typedef int[0,UINT8_MAX]         uint8_t;\n"
"typedef int[INT16_MIN,INT16_MAX] int16_t;\n"
"typedef int[0,UINT16_MAX]        uint16_t;\n"
"typedef int[INT32_MIN,INT32_MAX] int32_t;\n"
"const double FLT_MIN    = 1.1754943508222875079687365372222456778186655567720875e-38;\n"
"const double FLT_MAX    = 340282346638528859811704183484516925440.0;\n"
"const double DBL_MIN    = 2.2250738585072013830902327173324040642192159804623318e-308;\n"
"const double DBL_MAX    = 1.79769313486231570814527423731704356798070567525845e+308;\n"
"const double M_PI       = 3.141592653589793115997963468544185161590576171875;\n"      // pi
"const double M_PI_2     = 1.5707963267948965579989817342720925807952880859375;\n"     // pi/2
"const double M_PI_4     = 0.78539816339744827899949086713604629039764404296875;\n"    // pi/4
"const double M_E        = 2.718281828459045090795598298427648842334747314453125;\n"   // e
"const double M_LOG2E    = 1.442695040888963387004650940070860087871551513671875;\n"   // log_2(e)
"const double M_LOG10E   = 0.43429448190325181666793241674895398318767547607421875;\n" // log_10(e)
"const double M_LN2      = 0.69314718055994528622676398299518041312694549560546875;\n" // log_e(2)
"const double M_LN10     = 2.30258509299404590109361379290930926799774169921875;\n"    // log_e(10)
"const double M_1_PI     = 0.31830988618379069121644420192751567810773849487304688;\n" // 1/pi
"const double M_2_PI     = 0.63661977236758138243288840385503135621547698974609375;\n" // 2/pi
"const double M_2_SQRTPI = 1.1283791670955125585606992899556644260883331298828125;\n"  // 2/sqrt(pi)
"const double M_SQRT2    = 1.4142135623730951454746218587388284504413604736328125;\n"  // sqrt(2)
"const double M_SQRT1_2  = 0.70710678118654757273731092936941422522068023681640625;\n" // sqrt(1/2)
;
}

int32_t parseXTA(const char *str, ParserBuilder *builder, bool newxta)
{
    if (newxta)
        parseXTA(utap_builtin_declarations(), builder, newxta, S_DECLARATION, "");
    return parseXTA(str, builder, newxta, S_XTA, "");
}

int32_t parseXTA(FILE *file, ParserBuilder *builder, bool newxta)
{
    if (newxta)
        parseXTA(utap_builtin_declarations(), builder, newxta, S_DECLARATION, "");
    utap__switch_to_buffer(utap__create_buffer(file, YY_BUF_SIZE));
    int res = parseXTA(builder, newxta, S_XTA, "");
    utap__delete_buffer(YY_CURRENT_BUFFER);
    return res;
}

int32_t parseProperty(const char *str, ParserBuilder *aParserBuilder, const std::string& xpath)
{
    utap__scan_string(str);
    int32_t res = parseProperty(aParserBuilder, xpath);
    utap__delete_buffer(YY_CURRENT_BUFFER);
    return res;
}

int32_t parseProperty(FILE *file, ParserBuilder *aParserBuilder)
{
    utap__switch_to_buffer(utap__create_buffer(file, YY_BUF_SIZE));
    int32_t res = parseProperty(aParserBuilder, "");
    utap__delete_buffer(YY_CURRENT_BUFFER);
    return res;
}
