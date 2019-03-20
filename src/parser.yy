// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2002-2003 Uppsala University and Aalborg University.
   
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
 * formats plus entry points to separate XTA parts to be used in XML
 * parser.
 * 
 * Location tracking is used from lex file (need bison 1.35 or later).
 * There are numerous problems with parser error recognition and
 * recovery in general, since the XTA language contains some tricky
 * properties:
 *
 * 1) The entity terminating tokens such as '}' and ';' are used for
 * multiple purposes, thus making it imposible to "skip until the end
 * of current entity".
 *
 * 2) Since entity terminating token is not always clear, there might
 * appear continuous error reports on the same code as no recovery is
 * made. Please report it, this might be corrected.
 *
 * 3) It is very hard to forsee the posibly missing terminals.  It is
 * likely that a bison generated message will be reported.
 * E.g. process declaration might be missing the '(' ')' (old XTA).
 * Please report with example if effects are not acceptable.
 *
 * 4) There are errors which could not be classified with current
 * bison restrictions (read only one token ahead) and therefore these
 * errors could not be recovered (manually). E.g. function and
 * variable declarations might contain some garbage before '('
 * (function) or '[' (array declaration) symbol.
 *
 */

%{

#include "libparser.h"

using namespace std;
using namespace UTAP;
using namespace Constants;

struct Position
{
    int32_t first_line, first_column, last_line, last_column;
    char *text;  // Unused - needed for compatibility with bison 1.28
    void reset() {
	first_column = first_line = 1; 
	last_column = last_line = 1; 
    };
    void lines(int32_t num) {
	last_column = 1;
	last_line += num;
    };
    void step() {
	first_column = last_column;       
	first_line = last_line;
    };
};

std::ostream &operator <<(std::ostream &out, const position_t &loc);

#define YYLTYPE Position

static YYLTYPE last_loc; 
static ErrorHandler *errorHandler;
static ParserBuilder *ch;
static syntax_t syntax;
static int syntax_token = 0;

static void utap_error(const char* msg);
static void utap_error(const TypeException& te, int32_t fl, int32_t fc,
		       int32_t ll, int32_t lc);

#define REPORT_ERROR(loc, exc) utap_error(exc, loc.first_line, loc.first_column, loc.last_line, loc.last_column);
  
// List of all parser error messages
static const char* PE_ARGLIST = "argument expression list expected";
static const char* PE_ASSIGN = "'=' expected";
static const char* PE_ASSIGN_EXP = "assignment expression expected";
static const char* PE_BANG = "'!' expected";
static const char* PE_COLON = "':' expected";
static const char* PE_CONST_EXP = "constant expression expected";
static const char* PE_EXPR = "expression expected";
static const char* PE_GUARD_EXP = "guard expression expected";
static const char* PE_INV = "invariant expression expected";
static const char* PE_LBRACE = "'{' expected";
static const char* PE_LBRACES = "'(' or '{' expected";
static const char* PE_LPAREN = "'(' expected";
static const char* PE_MEMBER = "member declarations expected";
static const char* PE_PARAMETERS = "parameters expected";
static const char* PE_PROCID = "process identifiers expected";
static const char* PE_QUE = "'?' expected";
static const char* PE_RPAREN = "')' expected";
static const char* PE_SEMICOLON = "';' expected";
static const char* PE_STATE_DECL = "state declaration expected";
static const char* PE_STATEID = "state identifier expected";
static const char* PE_SYNC_EXP = "synchronization expression expected";
static const char* PE_TRANS_DECL = "edge declaration expected";

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
static int32_t g_parameter_count;

#define YYERROR_VERBOSE 1

//#define CALL(first,last,call) do { ch->call; } while (0)

#define CALL(first,last,call) do { errorHandler->setCurrentPosition(first.first_line, first.first_column, last.last_line, last.last_column); ch->setPosition(position_t(first.first_line, first.first_column, last.last_line, last.last_column)); try { ch->call; } catch (TypeException &te) { errorHandler->handleError(te.what()); } } while (0)
//           try { ch->done(); }
// 	  catch(TypeException te) { 
// 	    utap_error(te, @2.first_line, @2.first_column, 
// 			 @2.last_line, @2.last_column); 
// 	  }


%}


/* Assignments: */
%token T_ASSIGNMENT T_ASSPLUS 
%token T_ASSMINUS T_ASSMULT T_ASSDIV T_ASSMOD 
%token T_ASSOR T_ASSAND T_ASSXOR 
%token T_ASSLSHIFT T_ASSRSHIFT

/* Unary operations: */
%token T_EXCLAM

%token T_INCREMENT T_DECREMENT

/* Binary operations: */
%token T_PLUS T_MINUS T_MULT T_DIV  T_MIN T_MAX
%token T_MOD T_OR T_XOR T_LSHIFT T_RSHIFT 
%token T_BOOL_AND T_BOOL_OR 
%token T_KW_AND T_KW_OR T_KW_IMPLY T_KW_NOT

/* Quantifiers */
%token T_FORALL

/* Relation operations:*/
%token T_LT T_LEQ T_EQ T_NEQ T_GEQ T_GT

/* Special statement keywords: */
%token T_FOR T_WHILE T_DO T_BREAK T_CONTINUE T_SWITCH T_IF T_ELSE 
%token T_CASE T_DEFAULT T_RETURN
%token T_CHAN_PRIORITY T_PROC_PRIORITY

/* Variable type declaration keywords: */
%token T_TYPEDEF T_STRUCT 
%token T_CONST T_OLDCONST T_URGENT T_BROADCAST T_TRUE T_FALSE T_META

/* Uppaal keywords */
%token T_SYSTEM T_PROCESS T_STATE T_COMMIT T_INIT T_TRANS T_SELECT
%token T_GUARD T_SYNC T_ASSIGN T_BEFORE T_AFTER T_PROGRESS
%token T_ARROW T_UNCONTROL_ARROW T_WINNING T_LOSING

/* Property tokens */
%token T_DEADLOCK T_EF T_EG T_AF T_AG T_LEADSTO T_QUIT

/* Miscelanious: */
%token T_ERROR 
%token <string>T_ID T_TYPENAME
%token <number>T_NAT

/* Syntax switch tokens */
%token T_NEW T_NEW_DECLARATION T_NEW_LOCAL_DECL T_NEW_INST T_NEW_SYSTEM 
%token T_NEW_PARAMETERS T_NEW_INVARIANT T_NEW_GUARD T_NEW_SYNC T_NEW_ASSIGN
%token T_NEW_SELECT
%token T_OLD T_OLD_DECLARATION T_OLD_LOCAL_DECL T_OLD_INST 
%token T_OLD_PARAMETERS T_OLD_INVARIANT T_OLD_GUARD T_OLD_ASSIGN
%token T_PROPERTY T_EXPRESSION 

%type <number> ArgList ArrayDecl FieldDeclList FieldDeclIdList FieldDecl
%type <number> OptionalParameterList ParameterList FieldInitList TypeIdList 
%type <number> OldProcParams OldProcParamList OldProcParam OldProcConstParam
%type <number> OptionalTemplateSetList
%type <kind> Quantifier
%type <number> Type TypePrefix Range 
%type <string> Id
%type <number> OldConstDeclIdList
%type <kind> UnaryOp AssignOp
%type <flag> VarInit 

%right T_FORALL
%left T_KW_OR T_KW_IMPLY
%left T_KW_AND
%right T_KW_NOT
%right T_ASSIGNMENT T_ASSPLUS T_ASSMINUS T_ASSMULT T_ASSDIV T_ASSMOD T_ASSAND T_ASSOR T_ASSLSHIFT T_ASSRSHIFT T_ASSXOR
%right '?' ':'
%left T_BOOL_OR
%left T_BOOL_AND 
%left T_OR
%left T_XOR
%left '&'
%left T_EQ T_NEQ 
%left T_LT T_LEQ T_GEQ T_GT
%left T_MIN T_MAX
%left T_LSHIFT T_RSHIFT
%left T_MINUS T_PLUS
%left T_MULT T_DIV T_MOD
%right T_EXCLAM T_INCREMENT T_DECREMENT UOPERATOR
%left '(' ')' '[' ']' '.' '\''

%union {
    bool flag;
    int number;
    kind_t kind;
    char string[MAXLEN];
}

/* Expect 1 shift/reduce warning in dangling ELSE part of IF statement */
%expect 1

%%

Uppaal:
          T_NEW XTA { CALL(@2, @2, done()); }
	| T_NEW_DECLARATION Declaration { }
	| T_NEW_LOCAL_DECL ProcLocalDeclList { }
	| T_NEW_INST Inst { }
	| T_NEW_SYSTEM System { }
	| T_NEW_PARAMETERS ParameterList { g_parameter_count = $2; }
	| T_NEW_INVARIANT Expression { }
        | T_NEW_SELECT SelectList { }
	| T_NEW_GUARD Expression { CALL(@2, @2, procGuard()); }
	| T_NEW_SYNC SyncExpr { }
	| T_NEW_ASSIGN ExprList { CALL(@2, @2, procUpdate()); }
	| T_OLD OldXTA { CALL(@2, @2, done()); }
	| T_OLD_DECLARATION OldDeclaration { }
	| T_OLD_LOCAL_DECL OldVarDeclList { }
	| T_OLD_INST Inst { }
        | T_OLD_PARAMETERS OldProcParamList { g_parameter_count = $2; }
	| T_OLD_INVARIANT OldInvariant { }
	| T_OLD_GUARD OldGuardList { CALL(@2, @2, procGuard()); }
	| T_OLD_ASSIGN ExprList { CALL(@2, @2, procUpdate()); }
        | T_PROPERTY PropertyList {}
        | T_EXPRESSION Expression {}
	;

XTA: 
	Declaration Inst System
	;

Inst:
	/* empty */
	| Inst T_ID T_ASSIGNMENT T_ID '(' {
          CALL(@2, @4, instantiationBegin($2, $4));
	} ArgList ')' ';' {
	  CALL(@2, @9, instantiationEnd($2, $4, $7));
	}
	| Inst T_ID T_ASSIGNMENT T_ID '(' error ')' ';' { 
	  REPORT_ERROR(last_loc, TypeException(PE_ARGLIST));
	}
	| Inst T_ID T_ASSIGNMENT T_ID '(' error ';' { 
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));
	}
	| Inst T_ID T_ASSIGNMENT T_ID error ';' { 
	  REPORT_ERROR(last_loc, TypeException(PE_LPAREN));
	}
	| Inst T_ID error ';' { 
	  REPORT_ERROR(last_loc, TypeException(PE_ASSIGN));
	}
	;

System: ChanPriorityDecl ProcPriorityDecl SysDecl Progress;

ChanPriorityDecl:
        /* empty */
        | T_CHAN_PRIORITY PriorityOrder ';'
        ;

ProcPriorityDecl:
        /* empty */
        | T_PROC_PRIORITY PriorityOrder ';'
        ;

PriorityOrder:
	T_ID { CALL(@1, @1, lowPriority($1)); }
	| PriorityOrder T_EQ T_ID { CALL(@3, @3, samePriority($3)); }
	| PriorityOrder T_LT T_ID { CALL(@3, @3, higherPriority($3)); }
	| PriorityOrder T_EQ error
	| PriorityOrder T_LT error 
	;

SysDecl:
	T_SYSTEM ProcessList ';'
        | T_SYSTEM ProcessList error ';' {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
        | T_SYSTEM error ';' {
	  REPORT_ERROR(last_loc, TypeException(PE_PROCID));
	}
	;

ProcessList:
	T_ID { CALL(@1, @1, process($1)); }
	| ProcessList ',' T_ID { CALL(@3, @3, process($3)); }
	;

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

Declaration:
	/* empty */
	| Declaration FunctionDecl
	| Declaration VariableDecl
	| Declaration TypeDecl
	| Declaration ProcDecl
	| Declaration BeforeUpdateDecl
	| Declaration AfterUpdateDecl
	| error ';'
	;

BeforeUpdateDecl: T_BEFORE '{' ExprList '}' { CALL(@3, @3, beforeUpdate()); };

AfterUpdateDecl: T_AFTER '{' ExprList '}' { CALL(@3, @3, afterUpdate()); };

FunctionDecl:
        /* Notice that StatementList will catch all errors. Hence we
	 * should be able to guarantee, that once declFuncBegin() has
	 * been called, we will also call declFuncEnd().
	 */
	Type Id OptionalParameterList '{' { 
	  CALL(@2, @3, declFuncBegin($2, $3));
	} BlockLocalDeclList StatementList '}' {
	  CALL(@1, @8, declFuncEnd());
	};

OptionalParameterList:
          '(' ')' { $$ = 0; }
        | '(' ParameterList ')' { $$ = $2; }
        | '(' error ')' { 
	  $$ = 0; 
	}
        ;

ParameterList:
	  Parameter { $$ = 1; }
	| ParameterList ',' Parameter { $$ = $1+1; }
	;

Parameter:
	Type '&' T_ID ArrayDecl {
          CALL(@1, @4, declParameter($3, true, $4));
          CALL(@1, @4, declParameterEnd());
	}
	| Type T_ID ArrayDecl {
          CALL(@1, @3, declParameter($2, false, $3));
          CALL(@1, @3, declParameterEnd());
	}
	;

VariableDecl:
	Type DeclIdList ';' { 
          CALL(@1, @3, declVarEnd());
	}
	;

DeclIdList:
	DeclId
	| DeclIdList ',' DeclId
	;

DeclId:
	Id ArrayDecl VarInit { 
	  CALL(@1, @3, declVar($1, $2, $3));
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
	/* empty */ { $$=0; }
	| ArrayDecl '[' Expression ']' { $$=$1+1; }
	| ArrayDecl '[' error ']' {
	  CALL(@3, @3, exprNat(1));
	  REPORT_ERROR(last_loc, TypeException(PE_CONST_EXP));
	  $$=$1+1; 
	}
	;

TypeDecl:
	T_TYPEDEF Type TypeIdList ';' {
	  CALL(@1, @4, declTypeDefEnd());
	}
	| T_TYPEDEF error ';' { 
	  CALL(@1, @3, declTypeDefEnd());  
	}
	;

TypeIdList:
	TypeId { $$ = 1; }
	| TypeIdList ',' TypeId { $$ = $1+1; }
	;

TypeId:
	Id ArrayDecl { 
	  CALL(@1, @2, declTypeDef($1, $2));
	}
	;

Type: 
	TypePrefix T_TYPENAME Range { 
	    CALL(($1 == ParserBuilder::PREFIX_NONE ? @2 : @1), @3,
		 typeName($1, $2, $3));
	}
	| TypePrefix T_STRUCT '{' FieldDeclList '}' { 
	    CALL(($1 == ParserBuilder::PREFIX_NONE ? @2 : @1), @5,
	       typeStruct($1, $4));
	}
	| TypePrefix T_STRUCT '{' error '}' { 
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBER));
	  CALL(($1 == ParserBuilder::PREFIX_NONE ? @2 : @1), @5,
	       typeStruct($1, 0));
	}
	;

Id:
	T_ID { strncpy($$, $1, MAXLEN); }
        | T_TYPENAME { strncpy($$, $1, MAXLEN); }
        ;

FieldDeclList:
	FieldDecl { $$=$1; }
	| FieldDeclList FieldDecl { $$=$1+$2; }
	;

FieldDecl:
	Type FieldDeclIdList ';' {
	  $$ = $2; 
	  CALL(@1, @3, structFieldEnd());
	}
	;

FieldDeclIdList:
	FieldDeclId { $$=1; }
	| FieldDeclIdList ',' FieldDeclId { $$=$1+1; }
	;

FieldDeclId:
	Id ArrayDecl { 
	  CALL(@1, @2, structField($1, $2));
	}
	;

TypePrefix:
          { $$ = ParserBuilder::PREFIX_NONE; }
	| T_URGENT    { $$ = ParserBuilder::PREFIX_URGENT; }
	| T_BROADCAST { $$ = ParserBuilder::PREFIX_BROADCAST; }
        | T_URGENT T_BROADCAST { $$ = ParserBuilder::PREFIX_URGENT_BROADCAST; }
	| T_CONST  { $$ = ParserBuilder::PREFIX_CONST; } 
        | T_META { $$ = ParserBuilder::PREFIX_META; }
        ;

Range:
	/* empty */ { $$ = 0; }
        | '[' Expression ']' { $$ = 1; }
        | '[' Expression ',' Expression ']' { $$ = 2; }
        | '[' error ']' {
	    $$ = 0;
        }
	;
        
/*********************************************************************
 * Process declaration
 */

OptionalTemplateSetList:
	/* empty */ { $$ = 0; }
	| '[' TemplateSet ']' OptionalTemplateSetList { $$ = $4 + 1; };

TemplateSet:
	T_ID ':' Type { 
	    CALL(@1, @3, procTemplateSet($1)); 
	};

ProcDecl:
	T_PROCESS Id OptionalTemplateSetList OptionalParameterList '{' { 
	  CALL(@1, @4, procBegin($2, 0, $3));
	} 
        ProcBody '}' { 
	  CALL(@6, @7, procEnd());
	}
	| T_PROCESS Id '{' {
	  utap_error(TypeException(PE_LPAREN), 
		     @3.first_line, @3.first_column, 
		     @3.last_line, @3.last_column);
	  CALL(@1, @3, procBegin($2, 0, 0));
	} ProcBody '}' {
	  CALL(@4, @5, procEnd());
	}
	;

ProcBody:
	ProcLocalDeclList States LocFlags Init Transitions 
	;

ProcLocalDeclList:
	/* empty */
	| ProcLocalDeclList FunctionDecl
	| ProcLocalDeclList VariableDecl
	| ProcLocalDeclList TypeDecl
	;

States:
	T_STATE StateDeclList ';'
	| T_STATE StateDeclList error ';' {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
	| T_STATE error ';' {
	  REPORT_ERROR(last_loc, TypeException(PE_STATE_DECL));
	}
	| error ';'
	;

StateDeclList:
	StateDecl
	| StateDeclList ',' StateDecl
	;

StateDecl:
	T_ID { 
	  CALL(@1, @1, procState($1, false));
	}
	| T_ID '{' Expression '}' { 
	  CALL(@1, @4, procState($1, true));
	}
	| T_ID '{' error '}' { 
	  REPORT_ERROR(last_loc, TypeException(PE_INV));
	  CALL(@1, @4, procState($1, false));
	}
	;

Init:
	T_INIT T_ID ';' { 
	  CALL(@1, @3, procStateInit($2));
	}
        | error ';' 
	;

Transitions:
	/* empty */
	| T_TRANS TransitionList ';'
	| T_TRANS error ';' {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
	;

TransitionList:
	Transition
	| TransitionList ',' TransitionOpt
	;

Transition:
	T_ID T_ARROW T_ID '{' {
	    CALL(@1, @3, procEdgeBegin($1, $3, true));
	} Select Guard Sync Assign '}' { 
	  strcpy(rootTransId, $1); 
	  CALL(@1, @8, procEdgeEnd($1, $3));
	}
	| T_ID T_UNCONTROL_ARROW T_ID '{' {
	    CALL(@1, @3, procEdgeBegin($1, $3, false));
	} Select Guard Sync Assign '}' { 
	  strcpy(rootTransId, $1); 
	  CALL(@1, @8, procEdgeEnd($1, $3));
	}
	;

TransitionOpt:
	T_ARROW T_ID '{' { 
	    CALL(@1, @2, procEdgeBegin(rootTransId, $2, true)); 
        } Select Guard Sync Assign '}' { 
	    CALL(@1, @7, procEdgeEnd(rootTransId, $2));
	}
	| T_UNCONTROL_ARROW T_ID '{' { 
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

Guard:
	/* empty */ 
        | T_GUARD Expression ';' {
	  CALL(@2, @2, procGuard());
        }
	| T_GUARD Expression error ';' {
	  REPORT_ERROR(yylloc, TypeException(PE_SEMICOLON));
	  CALL(@2, @3, procGuard());
	}
	| T_GUARD error ';' {
	  REPORT_ERROR(yylloc, TypeException(PE_GUARD_EXP));
	}
	;

Sync:
	/* empty */ 
	| T_SYNC SyncExpr ';'
	| T_SYNC SyncExpr error ';' {
	  REPORT_ERROR(yylloc, TypeException(PE_SEMICOLON));
	}
	| T_SYNC error ';' {
	  REPORT_ERROR(yylloc, TypeException(PE_SYNC_EXP));
	}
	;

SyncExpr:
	Expression T_EXCLAM { 
	  CALL(@1, @2, procSync(SYNC_BANG));
	}
	| Expression error T_EXCLAM { 
	  REPORT_ERROR(last_loc, TypeException(PE_BANG));
	  CALL(@1, @2, procSync(SYNC_QUE));
	}
	| Expression '?' { 
	  CALL(@1, @2, procSync(SYNC_QUE));
	}
	| Expression error '?' { 
	  REPORT_ERROR(last_loc, TypeException(PE_QUE));
	  CALL(@1, @2, procSync(SYNC_QUE));
	}
	;

Assign:
	/* empty */ 
	| T_ASSIGN ExprList ';' {
	  CALL(@2, @2, procUpdate());	  
	}
	| T_ASSIGN error ';' {
	  REPORT_ERROR(last_loc, TypeException(PE_ASSIGN_EXP));
	}
	;

LocFlags:
	/* empty */
	| LocFlags Commit
	| LocFlags Urgent
        | LocFlags Winning
        | LocFlags Losing
	;

Commit:
	T_COMMIT CStateList ';'
	| T_COMMIT CStateList error ';' {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
	| T_COMMIT error ';' {
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
	;

Urgent:
	T_URGENT UStateList ';' {}
	| T_URGENT UStateList error ';' {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
	| T_URGENT error ';' {
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
	;

Winning:
	T_WINNING WStateList ';'
	| T_WINNING WStateList error ';' {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
	| T_WINNING error ';' {
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
	;

Losing:
	T_LOSING LStateList ';'
	| T_LOSING LStateList error ';' {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
	| T_LOSING error ';' {
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
	;

CStateList:
	T_ID { 
	  CALL(@1, @1, procStateCommit($1));
	}
	| CStateList ',' T_ID { 
	  CALL(@1, @3, procStateCommit($3));
	}
	;

UStateList:
	T_ID { 
	  CALL(@1, @1, procStateUrgent($1));
	}
	| UStateList ',' T_ID { 
	  CALL(@1, @3, procStateUrgent($3));
	}
	;

WStateList:
	T_ID { 
	  CALL(@1, @1, procStateWinning($1));
	}
	| WStateList ',' T_ID { 
	  CALL(@1, @3, procStateWinning($3));
	}
	;

LStateList:
	T_ID { 
	  CALL(@1, @1, procStateLosing($1));
	}
	| LStateList ',' T_ID { 
	  CALL(@1, @3, procStateLosing($3));
	}
	;


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

Statement:
	Block
	| ';' { 
	  CALL(@1, @1, emptyStatement());
	}
	| Expression ';' { 
	  CALL(@1, @2, exprStatement());
	}
        | T_FOR '(' ExprList ';' ExprList ';' ExprList ')' { 
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
        | T_WHILE '(' {
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
	| T_IF '(' { 
	    CALL(@1, @2, ifBegin());
	}
          ExprList ')' Statement ElsePart
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
	;

ElsePart: 
	/* empty */ { 
	  CALL(position_t(), position_t(), ifEnd(false));
	}
	| T_ELSE { 
	  CALL(@1, @1, ifElse());
	}
	  Statement { 
	  CALL(@2, @2, ifEnd(true));
	  }
        ;

SwitchCaseList:
	SwitchCase
	| SwitchCaseList SwitchCase
	;

SwitchCase:
	T_CASE Expression ':' { 
	  CALL(@1, @3, caseBegin());
	}
	  StatementList { 
	    CALL(@4, @4, caseEnd());
	  }
	| T_CASE error ':' { 
	  CALL(@1, @3, caseBegin());
	}
	  StatementList {
	    REPORT_ERROR(last_loc, TypeException(PE_EXPR)); 
	    CALL(@4, @4, caseEnd());
	  }
	| T_DEFAULT ':' { 
	    CALL(@1, @2, defaultBegin());
	}
	  StatementList { 
	    CALL(@3, @3, defaultEnd());
	  }
	| T_DEFAULT error ':' { 
	  REPORT_ERROR(last_loc, TypeException(PE_COLON)); 
	  CALL(@1, @3, defaultBegin());
	}
	  StatementList { 
	    CALL(@4, @4, defaultEnd());
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
	| T_ID { 
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
	    REPORT_ERROR(last_loc, TypeException(PE_ARGLIST));
	    CALL(@1, @5, exprCallEnd(0));
	}
	| Expression '[' Expression ']' { 
	  CALL(@1, @4, exprArray());
	}
	| Expression '[' error ']' { 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(@1, @4, exprFalse());
	}
	| '(' Expression ')'
	| '(' error ')' {
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
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
	| Expression '&'  Expression { 
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
	}
	| Expression '.' T_ID { 
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
        | T_KW_NOT Expression {
	  CALL(@1, @2, exprUnary(NOT));
        }
        | Expression T_MIN Expression {
	    CALL(@1, @3, exprBinary(MIN));
        }
        | Expression T_MAX Expression {
	    CALL(@1, @3, exprBinary(MAX));
        }
        | T_FORALL '(' Id ':' Type ')' {
	    CALL(@1, @6, exprForAllBegin($3));
        } Expression {
	    CALL(@8, @8, exprForAllEnd($3));
        } %prec T_FORALL
        | Assignment
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
	;

ArgList:
	/* The result is the number of expressions as parameters */
	/* empty */ { $$=0; }
	| Expression { 
	    $$ = 1; 
	    CALL(@1, @1, exprArg(0));
	}
        | ArgList ',' Expression { 
	    $$ = $1 + 1; 
	    CALL(@3, @3, exprArg($1));
	}
	;

/***********************************************************************
 * Old XTA format grammar
 */

OldXTA: 
	OldDeclaration Inst System;


OldDeclaration:
	/* empty */
	| OldDeclaration OldVarDecl
	| OldDeclaration OldProcDecl
	;

OldVarDecl:
	VariableDecl
	| T_OLDCONST { 
	  CALL(@1, @1, typeName(ParserBuilder::PREFIX_CONST, "int", 0));
	} OldConstDeclIdList ';' { 
	  CALL(@1, @3, declVarEnd());
	}
        | T_OLDCONST error ';';

OldConstDeclIdList:
	OldConstDeclId { $$=1; }
	| OldConstDeclIdList ',' OldConstDeclId { $$=$1+1; }
	;

OldConstDeclId:
	T_ID ArrayDecl Initializer { 
	  CALL(@1, @3, declVar($1, $2, true));
	}
	;

/*********************************************************************
 * Old Process declaration
 */
OldProcDecl:
	T_PROCESS Id OldProcParams '{' { 
	  CALL(@1, @4, procBegin($2, 0, $3));
	}
        OldProcBody '}' { 
	  CALL(@5, @6, procEnd());
	} 
	| T_PROCESS Id OldProcParams error '{' { 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	  CALL(@1, @5, procBegin($2, 0, $3));
	}
        OldProcBody '}' { 
	  CALL(@6, @7, procEnd());
	} 
	| T_PROCESS Id error '{' { 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACES));
	  CALL(@1, @4, procBegin($2, 0, 0));
	}
        OldProcBody '}' { 
	  CALL(@5, @6, procEnd());
	} 
	| T_PROCESS error '{' { 
	  REPORT_ERROR(last_loc, TypeException(PE_PROCID));
	  CALL(@1, @3, procBegin("_", 0, 0));
	}
        OldProcBody '}' { 
	  CALL(@4, @5, procEnd());
	} 
	| T_PROCESS Id '{' { 
	  CALL(@1, @3, procBegin($2, 0, 0));
	}
	OldProcBody '}' { 
	  CALL(@4, @5, procEnd());
	}
	;

OldProcParams:
	'(' ')' { $$ = 0; }
	| '(' OldProcParamList ')' { $$ = $2; }
	| '(' error ')' { 
	  REPORT_ERROR(last_loc, TypeException(PE_PARAMETERS));	  
	  $$ = 0; 
	}
	;

OldProcParamList:
        OldProcParam { 
	  $$ = $1; 
	  CALL(@1, @1, declParameterEnd());
	}
        | OldProcConstParam {
	  $$ = $1;
	  CALL(@1, @1, declParameterEnd());
        }
	| OldProcParamList ';' OldProcParam { 
	  $$ = $1 + $3;
	  CALL(@1, @3, declParameterEnd());
	}
	| OldProcParamList ';' OldProcConstParam { 
	  $$ = $1 + $3;
	  CALL(@1, @3, declParameterEnd());
	}
	;

OldProcParam:
	Type T_ID ArrayDecl {
          CALL(@1, @3, declParameter($2, $3 == 0, $3));
	  $$ = 1;
	}
	| OldProcParam ',' T_ID ArrayDecl { 
	  CALL(@1, @4, declParameter($3, $4 == 0, $4));
	  $$ = $1 + 1;
	} 
	;

OldProcConstParam:
	T_OLDCONST T_ID ArrayDecl {
	  CALL(@1, @1, typeName(ParserBuilder::PREFIX_CONST, "int", false));
	  CALL(@2, @3, declParameter($2, false, $3));
	  $$ = 1;
	}
	| OldProcConstParam ',' T_ID ArrayDecl { 
	  CALL(@1, @4, declParameter($3, false, $4));
	  $$ = $1 + 1;
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
	T_ID { 
	  CALL(@1, @1, exprTrue(); ch->procState($1, false));
	}
	| T_ID '{' OldInvariant '}' { 
	  CALL(@1, @4, procState($1, true));
	}
	;

OldInvariant:
	Expression
	| Expression error ',' {	  
	  REPORT_ERROR(last_loc, TypeException(PE_INV));
	}
	| OldInvariant ',' Expression { 
	  CALL(@1, @3, exprBinary(AND));
	}
	;

OldTransitions:
	/* empty */
	| T_TRANS OldTransitionList ';'
	| T_TRANS OldTransitionList error ';' {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
	| T_TRANS error ';' {
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS_DECL));
	}
	;

OldTransitionList:
	OldTransition
	| OldTransitionList ',' OldTransitionOpt
	;

OldTransition:
        T_ID T_ARROW T_ID '{' {
	    CALL(@1, @3, procEdgeBegin($1, $3, true));
	} OldGuard Sync Assign '}' { 
	    strcpy(rootTransId, $1);
	    CALL(@1, @8, procEdgeEnd($1, $3));
	}
	;


OldTransitionOpt:
	T_ARROW T_ID '{' {
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
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(@2, @3, procGuard());
	}
	;

OldGuardList:
	Expression
	| OldGuardList ',' Expression { 
	  CALL(@1, @3, exprBinary(AND));
	}
        ;

PropertyList:
          PropertyList2 Property;

PropertyList2:
	/* empty */
	| PropertyList2 Property '\n';

Property:
	/* empty */
        | T_QUIT {
		ch->quit();	
	}
        | Quantifier Expression {
		ch->property($1, @1.first_line);
	}
	| Expression T_LEADSTO Expression {
		ch->property(LEADSTO, @1.first_line);
	};

Quantifier:
	  T_EF { $$ = EF; }
        | T_EG { $$ = EG; }
        | T_AF { $$ = AF; }
        | T_AG { $$ = AG; };

%%

#include "lexer.cc"

static void utap_error(const char* msg)
{
    errorHandler->setCurrentPosition(
	yylloc.first_line, yylloc.first_column, 
	yylloc.last_line, yylloc.last_column);
    errorHandler->handleError(msg);
    last_loc = yylloc;
}

static void utap_error(
    const TypeException& te, int32_t fl, int32_t fc,
    int32_t ll, int32_t lc)
{
    errorHandler->setCurrentPosition(fl, fc, ll, lc);
    errorHandler->handleError(te.what());
    last_loc = yylloc;
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
    case S_PROPERTY:
	syntax_token = T_PROPERTY;
	break;
    }
}

static int32_t parseXTA(ParserBuilder *aParserBuilder,
		 ErrorHandler *err, bool newxta, xta_part_t part)
{
    // Select syntax
    syntax = (syntax_t)((newxta ? SYNTAX_NEW : SYNTAX_OLD) | SYNTAX_GUIDING);
    setStartToken(part, newxta);

    // Set parser builder and error handler
    ch = aParserBuilder;
    ch->setErrorHandler(err);
    errorHandler = err;
    
    // Reset position tracking
    yylloc.reset();

    // Parse string
    int res = 0;

    g_parameter_count = 0;

    if (utap_parse()) 
    {
	res = -1;
    }
    else 
    {
	res = g_parameter_count;
    }

    ch = NULL;
    errorHandler = NULL;
    return res;
}

static int32_t parseProperty(ParserBuilder *aParserBuilder, ErrorHandler *err)
{
    // Select syntax
    syntax = SYNTAX_PROPERTY;
    setStartToken(S_PROPERTY, false);

    // Set parser builder and error handler
    ch = aParserBuilder;
    ch->setErrorHandler(err);
    errorHandler = err;    
    
    // Reset position tracking
    yylloc.reset();

    return utap_parse() ? -1 : 0;
}

int32_t parseXTA(const char *str, ParserBuilder *builder,
		 ErrorHandler *err, bool newxta, xta_part_t part)
{
    utap__scan_string(str);
    int32_t res = parseXTA(builder, err, newxta, part);
    utap__delete_buffer(YY_CURRENT_BUFFER);
    return res;
}

int32_t parseXTA(FILE *file, ParserBuilder *builder,
    ErrorHandler *err, bool newxta)
{
    utap__switch_to_buffer(utap__create_buffer(file, YY_BUF_SIZE));
    int res = parseXTA(builder, err, newxta, S_XTA);
    utap__delete_buffer(YY_CURRENT_BUFFER);
    return res;
}

int32_t parseProperty(const char *str, ParserBuilder *aParserBuilder, 
		      ErrorHandler *err)
{
    utap__scan_string(str);
    int32_t res = parseProperty(aParserBuilder, err);
    utap__delete_buffer(YY_CURRENT_BUFFER);
    return res;
}

int32_t parseProperty(FILE *file, ParserBuilder *aParserBuilder, 
		      ErrorHandler *err)
{
    utap__switch_to_buffer(utap__create_buffer(file, YY_BUF_SIZE));
    int32_t res = parseProperty(aParserBuilder, err);
    utap__delete_buffer(YY_CURRENT_BUFFER);
    return res;
}
