/* A Bison parser, made from parser.yy, by GNU bison 1.75.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON	1

/* Pure parsers.  */
#define YYPURE	0

/* Using locations.  */
#define YYLSP_NEEDED 1

/* If NAME_PREFIX is specified substitute the variables and functions
   names.  */
#define yyparse utap_parse
#define yylex   utap_lex
#define yyerror utap_error
#define yylval  utap_lval
#define yychar  utap_char
#define yydebug utap_debug
#define yynerrs utap_nerrs
#define yylloc utap_lloc

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_ASSIGNMENT = 258,
     T_ASSIGNOLD = 259,
     T_ASSPLUS = 260,
     T_ASSMINUS = 261,
     T_ASSMULT = 262,
     T_ASSDIV = 263,
     T_ASSMOD = 264,
     T_ASSOR = 265,
     T_ASSAND = 266,
     T_ASSXOR = 267,
     T_ASSLSHIFT = 268,
     T_ASSRSHIFT = 269,
     T_EXCLAM = 270,
     T_INCREMENT = 271,
     T_DECREMENT = 272,
     T_PLUS = 273,
     T_MINUS = 274,
     T_MULT = 275,
     T_DIV = 276,
     T_MOD = 277,
     T_OR = 278,
     T_XOR = 279,
     T_LSHIFT = 280,
     T_RSHIFT = 281,
     T_BOOL_AND = 282,
     T_BOOL_OR = 283,
     T_BOOL_NOT = 284,
     T_IMPLY = 285,
     T_LT = 286,
     T_LEQ = 287,
     T_EQ = 288,
     T_NEQ = 289,
     T_GEQ = 290,
     T_GT = 291,
     T_FOR = 292,
     T_WHILE = 293,
     T_DO = 294,
     T_BREAK = 295,
     T_CONTINUE = 296,
     T_SWITCH = 297,
     T_IF = 298,
     T_ELSE = 299,
     T_CASE = 300,
     T_DEFAULT = 301,
     T_RETURN = 302,
     T_TYPEDEF = 303,
     T_STRUCT = 304,
     T_CONST = 305,
     T_URGENT = 306,
     T_BROADCAST = 307,
     T_TRUE = 308,
     T_FALSE = 309,
     T_SYSTEM = 310,
     T_PROCESS = 311,
     T_STATE = 312,
     T_COMMIT = 313,
     T_INIT = 314,
     T_TRANS = 315,
     T_ARROW = 316,
     T_GUARD = 317,
     T_SYNC = 318,
     T_ASSIGN = 319,
     T_DEADLOCK = 320,
     T_EF = 321,
     T_EG = 322,
     T_AF = 323,
     T_AG = 324,
     T_LEADSTO = 325,
     T_QUIT = 326,
     T_ERROR = 327,
     T_ID = 328,
     T_TYPENAME = 329,
     T_NAT = 330,
     T_NEW = 331,
     T_NEW_DECLARATION = 332,
     T_NEW_LOCAL_DECL = 333,
     T_NEW_INST = 334,
     T_NEW_SYSTEM = 335,
     T_NEW_PARAMETERS = 336,
     T_NEW_INVARIANT = 337,
     T_NEW_GUARD = 338,
     T_NEW_SYNC = 339,
     T_NEW_ASSIGN = 340,
     T_OLD = 341,
     T_OLD_DECLARATION = 342,
     T_OLD_LOCAL_DECL = 343,
     T_OLD_INST = 344,
     T_OLD_PARAMETERS = 345,
     T_OLD_INVARIANT = 346,
     T_OLD_GUARD = 347,
     T_OLD_ASSIGN = 348,
     T_PROPERTY = 349,
     UOPERATOR = 350
   };
#endif
#define T_ASSIGNMENT 258
#define T_ASSIGNOLD 259
#define T_ASSPLUS 260
#define T_ASSMINUS 261
#define T_ASSMULT 262
#define T_ASSDIV 263
#define T_ASSMOD 264
#define T_ASSOR 265
#define T_ASSAND 266
#define T_ASSXOR 267
#define T_ASSLSHIFT 268
#define T_ASSRSHIFT 269
#define T_EXCLAM 270
#define T_INCREMENT 271
#define T_DECREMENT 272
#define T_PLUS 273
#define T_MINUS 274
#define T_MULT 275
#define T_DIV 276
#define T_MOD 277
#define T_OR 278
#define T_XOR 279
#define T_LSHIFT 280
#define T_RSHIFT 281
#define T_BOOL_AND 282
#define T_BOOL_OR 283
#define T_BOOL_NOT 284
#define T_IMPLY 285
#define T_LT 286
#define T_LEQ 287
#define T_EQ 288
#define T_NEQ 289
#define T_GEQ 290
#define T_GT 291
#define T_FOR 292
#define T_WHILE 293
#define T_DO 294
#define T_BREAK 295
#define T_CONTINUE 296
#define T_SWITCH 297
#define T_IF 298
#define T_ELSE 299
#define T_CASE 300
#define T_DEFAULT 301
#define T_RETURN 302
#define T_TYPEDEF 303
#define T_STRUCT 304
#define T_CONST 305
#define T_URGENT 306
#define T_BROADCAST 307
#define T_TRUE 308
#define T_FALSE 309
#define T_SYSTEM 310
#define T_PROCESS 311
#define T_STATE 312
#define T_COMMIT 313
#define T_INIT 314
#define T_TRANS 315
#define T_ARROW 316
#define T_GUARD 317
#define T_SYNC 318
#define T_ASSIGN 319
#define T_DEADLOCK 320
#define T_EF 321
#define T_EG 322
#define T_AF 323
#define T_AG 324
#define T_LEADSTO 325
#define T_QUIT 326
#define T_ERROR 327
#define T_ID 328
#define T_TYPENAME 329
#define T_NAT 330
#define T_NEW 331
#define T_NEW_DECLARATION 332
#define T_NEW_LOCAL_DECL 333
#define T_NEW_INST 334
#define T_NEW_SYSTEM 335
#define T_NEW_PARAMETERS 336
#define T_NEW_INVARIANT 337
#define T_NEW_GUARD 338
#define T_NEW_SYNC 339
#define T_NEW_ASSIGN 340
#define T_OLD 341
#define T_OLD_DECLARATION 342
#define T_OLD_LOCAL_DECL 343
#define T_OLD_INST 344
#define T_OLD_PARAMETERS 345
#define T_OLD_INVARIANT 346
#define T_OLD_GUARD 347
#define T_OLD_ASSIGN 348
#define T_PROPERTY 349
#define UOPERATOR 350




/* Copy the first part of user declarations.  */
#line 53 "parser.yy"


#include "libparser.hh"

using namespace std;
using namespace UTAP;
using namespace Constants;

typedef struct position_t
{
    int32_t first_line, first_column, last_line, last_column;
    position_t() { reset(); }
    position_t(const position_t &loc): 
	first_line(loc.first_line), first_column(loc.first_column),
	last_line(loc.last_line), last_column(loc.last_column) {};
    ~position_t(){ };
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

#define YYLTYPE position_t

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
static const char* PE_ALT_TRANS = "alternative transition expected";
static const char* PE_ARGLIST = "argument expression list expected";
static const char* PE_ARGLIST_ = "one more argument expression expected";
static const char* PE_ARROW = "'->' expected";
static const char* PE_ASSIGN = "'=' expected";
static const char* PE_ASSIGN_EXP = "assignment expression expected";
static const char* PE_ASSIGN_EXP_ = "one more assignment expression expected";
static const char* PE_ASSIGNOLD = "':=' expected";
static const char* PE_BANG = "'!' expected";
static const char* PE_BANGQUE = "'!' or '?' expected";
static const char* PE_COLON = "':' expected";
static const char* PE_COMMA = "',' expected";
static const char* PE_CONST_EXP = "constant expression expected";
static const char* PE_CONSTID = "constant identifier expected";
static const char* PE_CONSTID_ = "one more constant identifier expected";
static const char* PE_DECL_STAT = "variable declaration or statement expected";
static const char* PE_EXPR = "expression expected";
static const char* PE_EXPR_ = "one more expression expected";
static const char* PE_EXPR_SEMI = "expression or ';' expected";
static const char* PE_GUARD_EXP = "guard expression expected";
static const char* PE_GUARD_EXP_ = "one more guard expression expected";
static const char* PE_ID_ = "one more identifier expected";
static const char* PE_INIT = "'init' expected";
static const char* PE_INITIAL = "initialiser expected";
static const char* PE_INITIAL_ = "one more initialiser expected";
static const char* PE_INV = "invariant expression expected";
static const char* PE_INV_ = "one more invariant expression expected";
static const char* PE_LBRACE = "'{' expected";
static const char* PE_LBRACES = "'(' or '{' expected";
static const char* PE_LOC_DECL = "location declaration expected";
static const char* PE_LPAREN = "'(' expected";
static const char* PE_MEMBER = "member declarations expected";
static const char* PE_MEMBERID = "member identifier expected";
static const char* PE_MEMBERID_ = "one more member identifier expected";
static const char* PE_MEMBERTYPE = "member type identifier expected";
static const char* PE_PARAM_DECL_ = "one more parameter declaration expected";
static const char* PE_PARAMETERS = "parameters expected";
static const char* PE_PARAMETERS_ = "one more parameter expected";
static const char* PE_PARAMID = "parameter identifier expected";
static const char* PE_PROC = "'process' expected";
static const char* PE_PROCID = "process identifiers expected";
static const char* PE_PROCID_ = "one more process identifier expected";
static const char* PE_QUE = "'?' expected";
static const char* PE_RBRACE = "'}' expected";
static const char* PE_RPAREN = "')' expected";
static const char* PE_RSQBRACE = "']' expected";
static const char* PE_SEMICOLON = "';' expected";
static const char* PE_STATE = "'state' expected";
static const char* PE_STATE_DECL = "state declaration expected";
static const char* PE_STATE_DECL_ = "one more state declaration expected";
static const char* PE_STATEID = "state identifier expected";
static const char* PE_STATEID_ = "one more state identifier expected";
static const char* PE_SYNC_EXP = "synchronization expression expected";
static const char* PE_SYSTEM = "'system' expected";
static const char* PE_TRANS = "'trans' expected";
static const char* PE_TRANS_DECL = "transition declaration expected";
static const char* PE_TRANS_DECL_ = "one more transition declaration expected";
static const char* PE_TYPE_DEF = "type definition expected";
static const char* PE_TYPEID = "type identifier expected";
static const char* PE_TYPEID_= "one more type identifier expected";
static const char* PE_VAR_DECL = "variable declaration expected";
static const char* PE_VARID = "variable identifier expected";
static const char* PE_VARID_ ="one more variable identifier expected" ;

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

#define CALL(first,last,call) do { errorHandler->setCurrentPosition(first.first_line, first.first_column, last.last_line, last.last_column); try { ch->call; } catch (TypeException &te) { errorHandler->handleError(te.what()); } } while (0)
//           try { ch->done(); }
// 	  catch(TypeException te) { 
// 	    utap_error(te, @2.first_line, @2.first_column, 
// 			 @2.last_line, @2.last_column); 
// 	  }




/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#ifndef YYSTYPE
#line 266 "parser.yy"
typedef union {
  bool flag;
  int number;
  char string[MAXLEN];
} yystype;
/* Line 193 of /usr/share/bison/yacc.c.  */
#line 419 "parser.tab.c"
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif

#ifndef YYLTYPE
typedef struct yyltype
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} yyltype;
# define YYLTYPE yyltype
# define YYLTYPE_IS_TRIVIAL 1
#endif

/* Copy the second part of user declarations.  */


/* Line 213 of /usr/share/bison/yacc.c.  */
#line 440 "parser.tab.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYLTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAX (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
      + 2 * YYSTACK_GAP_MAX)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];	\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAX;	\
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  75
#define YYLAST   3403

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  109
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  131
/* YYNRULES -- Number of rules. */
#define YYNRULES  487
/* YYNRULES -- Number of states. */
#define YYNSTATES  867

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   350

#define YYTRANSLATE(X) \
  ((unsigned)(X) <= YYMAXUTOK ? yytranslate[X] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     108,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    97,     2,
      99,   100,     2,     2,   105,     2,   103,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    96,   104,
       2,     2,     2,    95,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   101,     2,   102,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   106,     2,   107,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      98
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     6,     9,    12,    15,    18,    21,    24,
      27,    30,    33,    36,    39,    42,    45,    48,    51,    54,
      57,    60,    63,    67,    68,    69,    79,    88,    96,   103,
     108,   112,   117,   121,   123,   127,   131,   132,   135,   138,
     141,   144,   145,   151,   154,   158,   163,   167,   171,   174,
     176,   180,   184,   189,   193,   196,   200,   205,   209,   211,
     215,   219,   223,   224,   227,   230,   232,   236,   241,   245,
     247,   251,   255,   259,   263,   265,   266,   271,   277,   282,
     287,   291,   296,   302,   307,   311,   313,   317,   321,   324,
     328,   334,   340,   345,   349,   351,   353,   355,   358,   361,
     365,   370,   374,   377,   380,   382,   386,   390,   393,   394,
     396,   398,   401,   403,   404,   410,   417,   423,   429,   435,
     436,   443,   444,   452,   457,   461,   464,   465,   473,   481,
     482,   489,   495,   501,   502,   505,   508,   511,   515,   520,
     524,   528,   531,   534,   536,   540,   544,   546,   551,   557,
     562,   567,   571,   575,   580,   584,   587,   589,   590,   594,
     599,   603,   606,   608,   610,   614,   618,   627,   637,   643,
     648,   652,   660,   669,   674,   678,   680,   681,   685,   690,
     694,   695,   699,   704,   708,   712,   715,   719,   722,   726,
     729,   730,   734,   738,   739,   741,   743,   746,   750,   755,
     759,   763,   766,   770,   775,   779,   783,   786,   788,   792,
     796,   798,   802,   806,   807,   813,   814,   819,   820,   823,
     826,   827,   830,   832,   834,   837,   841,   842,   853,   854,
     866,   867,   879,   880,   887,   888,   896,   897,   905,   906,
     915,   916,   924,   927,   931,   934,   938,   939,   948,   949,
     959,   960,   970,   974,   978,   981,   984,   985,   986,   990,
     991,   995,   997,  1000,  1001,  1007,  1008,  1014,  1015,  1020,
    1021,  1027,  1028,  1030,  1032,  1036,  1040,  1042,  1044,  1046,
    1048,  1049,  1055,  1056,  1062,  1067,  1072,  1076,  1080,  1083,
    1086,  1089,  1092,  1096,  1100,  1103,  1107,  1111,  1115,  1119,
    1123,  1127,  1131,  1135,  1139,  1143,  1147,  1151,  1155,  1159,
    1163,  1167,  1171,  1175,  1179,  1183,  1187,  1191,  1195,  1199,
    1203,  1207,  1211,  1215,  1219,  1223,  1227,  1231,  1235,  1239,
    1243,  1247,  1253,  1259,  1264,  1268,  1272,  1274,  1275,  1280,
    1282,  1284,  1286,  1288,  1290,  1292,  1294,  1296,  1298,  1300,
    1302,  1304,  1306,  1308,  1309,  1311,  1315,  1319,  1323,  1324,
    1325,  1335,  1344,  1352,  1359,  1364,  1365,  1368,  1371,  1375,
    1380,  1384,  1387,  1388,  1393,  1397,  1399,  1403,  1407,  1409,
    1414,  1419,  1424,  1428,  1432,  1434,  1438,  1442,  1445,  1448,
    1451,  1454,  1455,  1463,  1464,  1473,  1474,  1482,  1483,  1490,
    1491,  1497,  1498,  1505,  1508,  1512,  1516,  1520,  1522,  1526,
    1530,  1534,  1538,  1541,  1546,  1550,  1556,  1557,  1560,  1564,
    1569,  1573,  1577,  1580,  1582,  1584,  1588,  1592,  1594,  1599,
    1601,  1605,  1607,  1611,  1615,  1616,  1620,  1625,  1629,  1633,
    1636,  1638,  1640,  1644,  1648,  1657,  1667,  1676,  1686,  1696,
    1704,  1712,  1721,  1730,  1739,  1747,  1749,  1750,  1754,  1759,
    1763,  1766,  1768,  1772,  1776,  1777,  1781,  1786,  1790,  1794,
    1797,  1799,  1803,  1807,  1811,  1815,  1819,  1822,  1825,  1826,
    1830,  1831,  1833,  1836,  1840,  1842,  1844,  1846
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short yyrhs[] =
{
     110,     0,    -1,    76,   111,    -1,    77,   116,    -1,    78,
     147,    -1,    79,   112,    -1,    80,   114,    -1,    80,     1,
      -1,    81,   120,    -1,    82,   193,    -1,    83,   193,    -1,
      84,   158,    -1,    85,   192,    -1,    86,   200,    -1,    87,
     203,    -1,    88,   222,    -1,    89,   201,    -1,    90,   219,
      -1,    91,   226,    -1,    92,   232,    -1,    93,   234,    -1,
      94,   236,    -1,   116,   112,   114,    -1,    -1,    -1,   112,
      73,     3,    73,    99,   113,   199,   100,   104,    -1,   112,
      73,     3,    73,    99,     1,   100,   104,    -1,   112,    73,
       3,    73,    99,     1,   104,    -1,   112,    73,     3,    73,
       1,   104,    -1,   112,    73,     1,   104,    -1,    55,   115,
     104,    -1,    55,   115,     1,   104,    -1,    55,     1,   104,
      -1,    73,    -1,   115,   105,    73,    -1,   115,   105,     1,
      -1,    -1,   116,   117,    -1,   116,   122,    -1,   116,   130,
      -1,   116,   143,    -1,    -1,   133,   134,   119,   118,   165,
      -1,    99,   100,    -1,    99,   120,   100,    -1,    99,   120,
       1,   100,    -1,    99,   120,     1,    -1,    99,     1,   100,
      -1,    99,     1,    -1,   121,    -1,   120,   105,   121,    -1,
     120,   105,     1,    -1,   133,    97,    73,   129,    -1,   133,
      73,   129,    -1,   133,     1,    -1,   133,   123,   104,    -1,
     133,   123,     1,   104,    -1,   133,     1,   104,    -1,   124,
      -1,   123,   105,   124,    -1,   123,   105,     1,    -1,   134,
     129,   125,    -1,    -1,     3,   126,    -1,     3,     1,    -1,
     193,    -1,   106,   127,   107,    -1,   106,   127,     1,   107,
      -1,   106,     1,   107,    -1,   128,    -1,   127,   105,   128,
      -1,   127,   105,     1,    -1,   134,    96,   126,    -1,   134,
      96,     1,    -1,   126,    -1,    -1,   129,   101,   193,   102,
      -1,   129,   101,   193,     1,   102,    -1,   129,   101,   193,
       1,    -1,   129,   101,     1,   102,    -1,   129,   101,     1,
      -1,    48,   133,   131,   104,    -1,    48,   133,   131,     1,
     104,    -1,    48,   133,     1,   104,    -1,    48,     1,   104,
      -1,   132,    -1,   131,   105,   132,    -1,   131,   105,     1,
      -1,   134,   129,    -1,   139,    74,   140,    -1,   139,    49,
     106,   135,   107,    -1,   139,    49,   106,     1,   107,    -1,
     139,    49,   106,     1,    -1,   139,    49,     1,    -1,    73,
      -1,    74,    -1,   136,    -1,   135,   136,    -1,   135,     1,
      -1,   133,   137,   104,    -1,   133,   137,     1,   104,    -1,
     133,     1,   104,    -1,   133,     1,    -1,     1,   104,    -1,
     138,    -1,   137,   105,   138,    -1,   137,   105,     1,    -1,
     134,   129,    -1,    -1,    51,    -1,    52,    -1,    51,    52,
      -1,    50,    -1,    -1,   101,   193,   105,   193,   102,    -1,
     101,   193,   105,   193,     1,   102,    -1,   101,   193,   105,
     193,     1,    -1,   101,   193,   105,     1,   102,    -1,   101,
       1,   105,   193,   102,    -1,    -1,   101,     1,   105,   141,
       1,   102,    -1,    -1,   101,   193,     1,   105,   142,   193,
     102,    -1,   101,   193,     1,   102,    -1,   101,   193,     1,
      -1,   101,     1,    -1,    -1,    56,   134,   119,   106,   144,
     146,   107,    -1,    56,   134,   119,     1,   106,   146,   107,
      -1,    -1,    56,   134,   106,   145,   146,   107,    -1,    56,
       1,   106,   146,   107,    -1,   147,   148,   160,   151,   152,
      -1,    -1,   147,   117,    -1,   147,   122,    -1,   147,   130,
      -1,    57,   149,   104,    -1,    57,   149,     1,   104,    -1,
      57,   149,     1,    -1,    57,     1,   104,    -1,    57,     1,
      -1,     1,   104,    -1,   150,    -1,   149,   105,   150,    -1,
     149,   105,     1,    -1,    73,    -1,    73,   106,   193,   107,
      -1,    73,   106,   193,     1,   107,    -1,    73,   106,   193,
       1,    -1,    73,   106,     1,   107,    -1,    73,   106,     1,
      -1,    59,    73,   104,    -1,    59,    73,     1,   104,    -1,
      59,    73,     1,    -1,    59,     1,    -1,     1,    -1,    -1,
      60,   153,   104,    -1,    60,   153,     1,   104,    -1,    60,
     153,     1,    -1,    60,     1,    -1,     1,    -1,   154,    -1,
     153,   105,   155,    -1,   153,   105,     1,    -1,    73,    61,
      73,   106,   156,   157,   159,   107,    -1,    73,    61,    73,
     106,   156,   157,   159,     1,   104,    -1,    73,    61,    73,
       1,   107,    -1,    73,    61,     1,   107,    -1,    73,     1,
     107,    -1,    61,    73,   106,   156,   157,   159,   107,    -1,
      61,    73,   106,   156,   157,   159,     1,   107,    -1,    61,
      73,     1,   107,    -1,    61,     1,   107,    -1,   154,    -1,
      -1,    62,   193,   104,    -1,    62,   193,     1,   104,    -1,
      62,     1,   104,    -1,    -1,    63,   158,   104,    -1,    63,
     158,     1,   104,    -1,    63,   158,     1,    -1,    63,     1,
     104,    -1,   193,    15,    -1,   193,     1,    15,    -1,   193,
      95,    -1,   193,     1,    95,    -1,   193,     1,    -1,    -1,
      64,   192,   104,    -1,    64,     1,   104,    -1,    -1,   161,
      -1,   162,    -1,   161,   162,    -1,    58,   163,   104,    -1,
      58,   163,     1,   104,    -1,    58,   163,     1,    -1,    58,
       1,   104,    -1,    58,     1,    -1,    51,   164,   104,    -1,
      51,   164,     1,   104,    -1,    51,   164,     1,    -1,    51,
       1,   104,    -1,    51,     1,    -1,    73,    -1,   163,   105,
      73,    -1,   163,   105,     1,    -1,    73,    -1,   164,   105,
      73,    -1,   164,   105,     1,    -1,    -1,   106,   166,   168,
     169,   107,    -1,    -1,   106,   167,     1,   107,    -1,    -1,
     168,   122,    -1,   168,   130,    -1,    -1,   169,   170,    -1,
     165,    -1,   104,    -1,   193,   104,    -1,   193,     1,   104,
      -1,    -1,    37,    99,   171,   192,   104,   192,   104,   192,
     100,   170,    -1,    -1,    37,    99,     1,   172,   191,   104,
     191,   104,   191,   100,   170,    -1,    -1,    37,     1,    99,
     173,   191,   104,   191,   104,   191,   100,   170,    -1,    -1,
      38,    99,   174,   192,   100,   170,    -1,    -1,    38,     1,
      99,   175,   192,   100,   170,    -1,    -1,    38,    99,     1,
     176,   192,   100,   170,    -1,    -1,    39,   177,   170,    38,
      99,   192,   100,   104,    -1,    -1,    43,    99,   178,   192,
     100,   170,   182,    -1,    40,   104,    -1,    40,     1,   104,
      -1,    41,   104,    -1,    41,     1,   104,    -1,    -1,    42,
      99,   192,   100,   179,   106,   185,   107,    -1,    -1,    42,
       1,    99,   192,   100,   180,   106,   185,   107,    -1,    -1,
      42,    99,     1,   192,   100,   181,   106,   185,   107,    -1,
      47,   193,   104,    -1,    47,   193,     1,    -1,    47,   104,
      -1,    47,     1,    -1,    -1,    -1,    44,   183,   170,    -1,
      -1,    44,   184,     1,    -1,   186,    -1,   185,   186,    -1,
      -1,    45,   193,    96,   187,   169,    -1,    -1,    45,     1,
      96,   188,   169,    -1,    -1,    46,    96,   189,   169,    -1,
      -1,    46,     1,    96,   190,   169,    -1,    -1,   192,    -1,
     193,    -1,   192,   105,   193,    -1,   192,   105,     1,    -1,
      54,    -1,    53,    -1,    75,    -1,    73,    -1,    -1,    73,
      99,   194,   199,   100,    -1,    -1,    73,    99,   195,     1,
     100,    -1,   193,   101,   193,   102,    -1,   193,   101,     1,
     102,    -1,    99,   193,   100,    -1,    99,     1,   100,    -1,
     193,    16,    -1,    16,   193,    -1,   193,    17,    -1,    17,
     193,    -1,   193,   197,   193,    -1,   193,   197,     1,    -1,
     198,   193,    -1,   193,    31,   193,    -1,   193,    31,     1,
      -1,   193,    32,   193,    -1,   193,    32,     1,    -1,   193,
      33,   193,    -1,   193,    33,     1,    -1,   193,    34,   193,
      -1,   193,    34,     1,    -1,   193,    36,   193,    -1,   193,
      36,     1,    -1,   193,    35,   193,    -1,   193,    35,     1,
      -1,   193,    18,   193,    -1,   193,    18,     1,    -1,   193,
      19,   193,    -1,   193,    19,     1,    -1,   193,    20,   193,
      -1,   193,    20,     1,    -1,   193,    21,   193,    -1,   193,
      21,     1,    -1,   193,    22,   193,    -1,   193,    22,     1,
      -1,   193,    97,   193,    -1,   193,    97,     1,    -1,   193,
      23,   193,    -1,   193,    23,     1,    -1,   193,    24,   193,
      -1,   193,    24,     1,    -1,   193,    25,   193,    -1,   193,
      25,     1,    -1,   193,    26,   193,    -1,   193,    26,     1,
      -1,   193,    27,   193,    -1,   193,    27,     1,    -1,   193,
      28,   193,    -1,   193,    28,     1,    -1,   193,    95,   193,
      96,   193,    -1,   193,    95,   193,    96,     1,    -1,   193,
      95,   193,     1,    -1,   193,   103,    73,    -1,   193,   103,
       1,    -1,    65,    -1,    -1,   193,    30,   196,   193,    -1,
       3,    -1,     5,    -1,     6,    -1,     8,    -1,     9,    -1,
       7,    -1,    11,    -1,    10,    -1,    12,    -1,    13,    -1,
      14,    -1,    19,    -1,    15,    -1,    29,    -1,    -1,   193,
      -1,   199,   105,   193,    -1,   199,   105,     1,    -1,   203,
     201,   114,    -1,    -1,    -1,   201,    73,     4,    73,    99,
     202,   199,   100,   104,    -1,   201,    73,     4,    73,    99,
       1,   100,   104,    -1,   201,    73,     4,    73,    99,     1,
     104,    -1,   201,    73,     4,    73,     1,   104,    -1,   201,
      73,     1,   104,    -1,    -1,   203,   204,    -1,   203,   211,
      -1,   210,   206,   104,    -1,   210,   206,     1,   104,    -1,
     210,     1,   104,    -1,     1,   104,    -1,    -1,    50,   205,
     208,   104,    -1,    50,     1,   104,    -1,   207,    -1,   206,
     105,   207,    -1,   206,   105,     1,    -1,   134,    -1,   134,
     101,   193,   102,    -1,   134,   101,   193,     1,    -1,   134,
     101,     1,   102,    -1,   134,     4,   193,    -1,   134,     4,
       1,    -1,   209,    -1,   208,   105,   209,    -1,   208,   105,
       1,    -1,    73,   193,    -1,    73,     1,    -1,    51,    74,
      -1,    74,   140,    -1,    -1,    56,   134,   218,   106,   212,
     221,   107,    -1,    -1,    56,   134,   218,     1,   106,   213,
     221,   107,    -1,    -1,    56,   134,     1,   106,   214,   221,
     107,    -1,    -1,    56,     1,   106,   215,   221,   107,    -1,
      -1,     1,   106,   216,   221,   107,    -1,    -1,    56,   134,
     106,   217,   221,   107,    -1,    99,   100,    -1,    99,   219,
     100,    -1,    99,   219,     1,    -1,    99,     1,   100,    -1,
     220,    -1,   219,   104,   220,    -1,   219,   104,     1,    -1,
     210,    73,   129,    -1,    50,    73,   129,    -1,    50,     1,
      -1,   220,   105,    73,   129,    -1,   220,   105,     1,    -1,
     222,   223,   160,   151,   227,    -1,    -1,   222,   204,    -1,
      57,   224,   104,    -1,    57,   224,     1,   104,    -1,    57,
     224,     1,    -1,    57,     1,   104,    -1,    57,     1,    -1,
       1,    -1,   225,    -1,   224,   105,   225,    -1,   224,   105,
       1,    -1,    73,    -1,    73,   106,   226,   107,    -1,   193,
      -1,   193,     1,   105,    -1,     1,    -1,   226,   105,   193,
      -1,   226,   105,     1,    -1,    -1,    60,   228,   104,    -1,
      60,   228,     1,   104,    -1,    60,   228,     1,    -1,    60,
       1,   104,    -1,    60,     1,    -1,     1,    -1,   229,    -1,
     228,   105,   230,    -1,   228,   105,     1,    -1,    73,    61,
      73,   106,   231,   157,   233,   107,    -1,    73,    61,    73,
     106,   231,   157,   233,     1,   107,    -1,    73,    61,    73,
     106,   231,   157,   233,     1,    -1,    73,    61,    73,     1,
     106,   231,   157,   233,   107,    -1,    73,     1,    61,    73,
     106,   231,   157,   233,   107,    -1,    61,    73,   106,   231,
     157,   233,   107,    -1,    61,    73,   106,   231,   157,   233,
       1,    -1,    61,    73,   106,   231,   157,   233,     1,   107,
      -1,    61,    73,     1,   106,   231,   157,   233,   107,    -1,
      61,     1,    73,   106,   231,   157,   233,   107,    -1,    61,
       1,   106,   231,   157,   233,   107,    -1,   229,    -1,    -1,
      62,   232,   104,    -1,    62,   232,     1,   104,    -1,    62,
     232,     1,    -1,    62,     1,    -1,   193,    -1,   232,   105,
     193,    -1,   232,   105,     1,    -1,    -1,    64,   234,   104,
      -1,    64,   234,     1,   104,    -1,    64,   234,     1,    -1,
      64,     1,   104,    -1,    64,     1,    -1,   235,    -1,   234,
     105,   235,    -1,   234,   105,     1,    -1,   193,     4,   193,
      -1,   193,     4,     1,    -1,   193,     1,   193,    -1,   193,
       1,    -1,   237,   238,    -1,    -1,   237,   238,   108,    -1,
      -1,    71,    -1,   239,   193,    -1,   193,    70,   193,    -1,
      66,    -1,    67,    -1,    68,    -1,    69,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   277,   277,   279,   280,   281,   282,   283,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   302,   306,   308,   308,   313,   316,   319,   322,
     327,   329,   332,   337,   339,   340,   345,   347,   348,   349,
     350,   354,   353,   362,   364,   365,   369,   373,   377,   388,
     390,   391,   397,   402,   406,   411,   415,   419,   425,   427,
     428,   433,   439,   441,   442,   448,   450,   453,   457,   463,
     465,   466,   472,   476,   479,   484,   486,   487,   491,   495,
     499,   505,   509,   513,   517,   528,   530,   531,   537,   543,
     547,   550,   554,   558,   563,   565,   568,   570,   571,   577,
     582,   587,   590,   593,   598,   600,   601,   607,   613,   615,
     616,   617,   618,   621,   623,   624,   628,   632,   637,   642,
     642,   652,   652,   659,   665,   671,   684,   683,   690,   693,
     693,   701,   710,   714,   716,   717,   718,   721,   723,   726,
     729,   732,   735,   740,   742,   743,   748,   753,   756,   760,
     764,   768,   774,   778,   782,   786,   789,   794,   796,   797,
     800,   803,   806,   811,   813,   814,   819,   824,   829,   832,
     835,   840,   844,   848,   851,   854,   858,   860,   863,   867,
     872,   874,   875,   878,   881,   886,   890,   894,   897,   901,
     907,   909,   912,   917,   919,   920,   921,   924,   926,   929,
     932,   935,   940,   942,   945,   948,   951,   956,   960,   963,
     968,   972,   975,   986,   985,   992,   992,  1001,  1003,  1004,
    1007,  1009,  1012,  1014,  1017,  1020,  1024,  1024,  1030,  1030,
    1038,  1038,  1046,  1046,  1052,  1052,  1059,  1059,  1066,  1066,
    1072,  1072,  1076,  1079,  1083,  1086,  1090,  1090,  1096,  1096,
    1103,  1103,  1110,  1113,  1117,  1120,  1126,  1130,  1130,  1136,
    1136,  1145,  1147,  1151,  1150,  1157,  1157,  1164,  1164,  1170,
    1170,  1179,  1181,  1184,  1186,  1189,  1194,  1198,  1201,  1204,
    1207,  1207,  1212,  1212,  1218,  1221,  1225,  1226,  1229,  1232,
    1235,  1238,  1241,  1244,  1248,  1251,  1254,  1258,  1261,  1265,
    1268,  1272,  1275,  1279,  1282,  1286,  1289,  1293,  1296,  1300,
    1303,  1307,  1310,  1314,  1317,  1321,  1324,  1328,  1331,  1335,
    1338,  1342,  1345,  1349,  1352,  1356,  1359,  1363,  1366,  1370,
    1373,  1377,  1380,  1384,  1388,  1391,  1394,  1397,  1397,  1405,
    1408,  1409,  1410,  1411,  1412,  1413,  1414,  1415,  1416,  1417,
    1420,  1423,  1424,  1427,  1430,  1434,  1438,  1449,  1452,  1454,
    1454,  1459,  1462,  1465,  1468,  1474,  1476,  1477,  1480,  1484,
    1489,  1494,  1498,  1498,  1504,  1509,  1511,  1512,  1518,  1522,
    1525,  1529,  1533,  1536,  1543,  1545,  1546,  1552,  1556,  1563,
    1567,  1576,  1575,  1582,  1582,  1589,  1589,  1596,  1596,  1603,
    1603,  1610,  1610,  1618,  1620,  1621,  1625,  1631,  1636,  1640,
    1647,  1651,  1655,  1658,  1661,  1667,  1671,  1673,  1676,  1678,
    1681,  1684,  1687,  1690,  1695,  1697,  1698,  1703,  1707,  1712,
    1714,  1717,  1721,  1724,  1730,  1732,  1733,  1736,  1739,  1742,
    1745,  1750,  1752,  1753,  1758,  1763,  1768,  1773,  1778,  1786,
    1790,  1794,  1798,  1802,  1806,  1810,  1813,  1815,  1818,  1822,
    1826,  1831,  1833,  1836,  1842,  1844,  1847,  1851,  1855,  1858,
    1863,  1865,  1868,  1873,  1877,  1881,  1885,  1890,  1893,  1895,
    1897,  1899,  1902,  1905,  1909,  1911,  1912,  1913
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_ASSIGNMENT", "T_ASSIGNOLD", "T_ASSPLUS", 
  "T_ASSMINUS", "T_ASSMULT", "T_ASSDIV", "T_ASSMOD", "T_ASSOR", 
  "T_ASSAND", "T_ASSXOR", "T_ASSLSHIFT", "T_ASSRSHIFT", "T_EXCLAM", 
  "T_INCREMENT", "T_DECREMENT", "T_PLUS", "T_MINUS", "T_MULT", "T_DIV", 
  "T_MOD", "T_OR", "T_XOR", "T_LSHIFT", "T_RSHIFT", "T_BOOL_AND", 
  "T_BOOL_OR", "T_BOOL_NOT", "T_IMPLY", "T_LT", "T_LEQ", "T_EQ", "T_NEQ", 
  "T_GEQ", "T_GT", "T_FOR", "T_WHILE", "T_DO", "T_BREAK", "T_CONTINUE", 
  "T_SWITCH", "T_IF", "T_ELSE", "T_CASE", "T_DEFAULT", "T_RETURN", 
  "T_TYPEDEF", "T_STRUCT", "T_CONST", "T_URGENT", "T_BROADCAST", "T_TRUE", 
  "T_FALSE", "T_SYSTEM", "T_PROCESS", "T_STATE", "T_COMMIT", "T_INIT", 
  "T_TRANS", "T_ARROW", "T_GUARD", "T_SYNC", "T_ASSIGN", "T_DEADLOCK", 
  "T_EF", "T_EG", "T_AF", "T_AG", "T_LEADSTO", "T_QUIT", "T_ERROR", 
  "T_ID", "T_TYPENAME", "T_NAT", "T_NEW", "T_NEW_DECLARATION", 
  "T_NEW_LOCAL_DECL", "T_NEW_INST", "T_NEW_SYSTEM", "T_NEW_PARAMETERS", 
  "T_NEW_INVARIANT", "T_NEW_GUARD", "T_NEW_SYNC", "T_NEW_ASSIGN", "T_OLD", 
  "T_OLD_DECLARATION", "T_OLD_LOCAL_DECL", "T_OLD_INST", 
  "T_OLD_PARAMETERS", "T_OLD_INVARIANT", "T_OLD_GUARD", "T_OLD_ASSIGN", 
  "T_PROPERTY", "'?'", "':'", "'&'", "UOPERATOR", "'('", "')'", "'['", 
  "']'", "'.'", "';'", "','", "'{'", "'}'", "'\\n'", "$accept", "Uppaal", 
  "XTA", "Inst", "@1", "System", "IdList", "Declaration", "FunctionDecl", 
  "@2", "OptionalParameterList", "ParameterList", "Parameter", 
  "VariableDecl", "DeclIdList", "DeclId", "VarInit", "Initializer", 
  "FieldInitList", "FieldInit", "ArrayDecl", "TypeDecl", "TypeIdList", 
  "TypeId", "Type", "Id", "FieldDeclList", "FieldDecl", "FieldDeclIdList", 
  "FieldDeclId", "TypePrefix", "Range", "@3", "@4", "ProcDecl", "@5", 
  "@6", "ProcBody", "ProcLocalDeclList", "States", "StateDeclList", 
  "StateDecl", "Init", "Transitions", "TransitionList", "Transition", 
  "TransitionOpt", "Guard", "Sync", "SyncExpr", "Assign", "LocFlags", 
  "Commit", "Urgent", "CStateList", "UStateList", "Block", "@7", "@8", 
  "BlockLocalDeclList", "StatementList", "Statement", "@9", "@10", "@11", 
  "@12", "@13", "@14", "@15", "@16", "@17", "@18", "@19", "ElsePart", 
  "@20", "@21", "SwitchCaseList", "SwitchCase", "@22", "@23", "@24", 
  "@25", "ExprList0", "ExprList", "Expression", "@26", "@27", "@28", 
  "AssignOp", "UnaryOp", "ArgList", "OldXTA", "OldInst", "@29", 
  "OldDeclaration", "OldVarDecl", "@30", "OldDeclIdList", "OldDeclId", 
  "OldConstDeclIdList", "OldConstDeclId", "OldType", "OldProcDecl", "@31", 
  "@32", "@33", "@34", "@35", "@36", "OldProcParams", "OldProcParamList", 
  "OldProcParam", "OldProcBody", "OldVarDeclList", "OldStates", 
  "OldStateDeclList", "OldStateDecl", "OldInvariant", "OldTransitions", 
  "OldTransitionList", "OldTransition", "OldTransitionOpt", "OldGuard", 
  "OldGuardList", "OldAssign", "OldAssignmentList", "OldAssignment", 
  "PropertyList", "PropertyList2", "Property", "Quantifier", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,    63,    58,    38,   350,    40,
      41,    91,    93,    46,    59,    44,   123,   125,    10
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,   109,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   111,   112,   113,   112,   112,   112,   112,   112,
     114,   114,   114,   115,   115,   115,   116,   116,   116,   116,
     116,   118,   117,   119,   119,   119,   119,   119,   119,   120,
     120,   120,   121,   121,   121,   122,   122,   122,   123,   123,
     123,   124,   125,   125,   125,   126,   126,   126,   126,   127,
     127,   127,   128,   128,   128,   129,   129,   129,   129,   129,
     129,   130,   130,   130,   130,   131,   131,   131,   132,   133,
     133,   133,   133,   133,   134,   134,   135,   135,   135,   136,
     136,   136,   136,   136,   137,   137,   137,   138,   139,   139,
     139,   139,   139,   140,   140,   140,   140,   140,   140,   141,
     140,   142,   140,   140,   140,   140,   144,   143,   143,   145,
     143,   143,   146,   147,   147,   147,   147,   148,   148,   148,
     148,   148,   148,   149,   149,   149,   150,   150,   150,   150,
     150,   150,   151,   151,   151,   151,   151,   152,   152,   152,
     152,   152,   152,   153,   153,   153,   154,   154,   154,   154,
     154,   155,   155,   155,   155,   155,   156,   156,   156,   156,
     157,   157,   157,   157,   157,   158,   158,   158,   158,   158,
     159,   159,   159,   160,   160,   160,   160,   161,   161,   161,
     161,   161,   162,   162,   162,   162,   162,   163,   163,   163,
     164,   164,   164,   166,   165,   167,   165,   168,   168,   168,
     169,   169,   170,   170,   170,   170,   171,   170,   172,   170,
     173,   170,   174,   170,   175,   170,   176,   170,   177,   170,
     178,   170,   170,   170,   170,   170,   179,   170,   180,   170,
     181,   170,   170,   170,   170,   170,   182,   183,   182,   184,
     182,   185,   185,   187,   186,   188,   186,   189,   186,   190,
     186,   191,   191,   192,   192,   192,   193,   193,   193,   193,
     194,   193,   195,   193,   193,   193,   193,   193,   193,   193,
     193,   193,   193,   193,   193,   193,   193,   193,   193,   193,
     193,   193,   193,   193,   193,   193,   193,   193,   193,   193,
     193,   193,   193,   193,   193,   193,   193,   193,   193,   193,
     193,   193,   193,   193,   193,   193,   193,   193,   193,   193,
     193,   193,   193,   193,   193,   193,   193,   196,   193,   197,
     197,   197,   197,   197,   197,   197,   197,   197,   197,   197,
     198,   198,   198,   199,   199,   199,   199,   200,   201,   202,
     201,   201,   201,   201,   201,   203,   203,   203,   204,   204,
     204,   204,   205,   204,   204,   206,   206,   206,   207,   207,
     207,   207,   207,   207,   208,   208,   208,   209,   209,   210,
     210,   212,   211,   213,   211,   214,   211,   215,   211,   216,
     211,   217,   211,   218,   218,   218,   218,   219,   219,   219,
     220,   220,   220,   220,   220,   221,   222,   222,   223,   223,
     223,   223,   223,   223,   224,   224,   224,   225,   225,   226,
     226,   226,   226,   226,   227,   227,   227,   227,   227,   227,
     227,   228,   228,   228,   229,   229,   229,   229,   229,   230,
     230,   230,   230,   230,   230,   230,   231,   231,   231,   231,
     231,   232,   232,   232,   233,   233,   233,   233,   233,   233,
     234,   234,   234,   235,   235,   235,   235,   236,   237,   237,
     238,   238,   238,   238,   239,   239,   239,   239
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     3,     0,     0,     9,     8,     7,     6,     4,
       3,     4,     3,     1,     3,     3,     0,     2,     2,     2,
       2,     0,     5,     2,     3,     4,     3,     3,     2,     1,
       3,     3,     4,     3,     2,     3,     4,     3,     1,     3,
       3,     3,     0,     2,     2,     1,     3,     4,     3,     1,
       3,     3,     3,     3,     1,     0,     4,     5,     4,     4,
       3,     4,     5,     4,     3,     1,     3,     3,     2,     3,
       5,     5,     4,     3,     1,     1,     1,     2,     2,     3,
       4,     3,     2,     2,     1,     3,     3,     2,     0,     1,
       1,     2,     1,     0,     5,     6,     5,     5,     5,     0,
       6,     0,     7,     4,     3,     2,     0,     7,     7,     0,
       6,     5,     5,     0,     2,     2,     2,     3,     4,     3,
       3,     2,     2,     1,     3,     3,     1,     4,     5,     4,
       4,     3,     3,     4,     3,     2,     1,     0,     3,     4,
       3,     2,     1,     1,     3,     3,     8,     9,     5,     4,
       3,     7,     8,     4,     3,     1,     0,     3,     4,     3,
       0,     3,     4,     3,     3,     2,     3,     2,     3,     2,
       0,     3,     3,     0,     1,     1,     2,     3,     4,     3,
       3,     2,     3,     4,     3,     3,     2,     1,     3,     3,
       1,     3,     3,     0,     5,     0,     4,     0,     2,     2,
       0,     2,     1,     1,     2,     3,     0,    10,     0,    11,
       0,    11,     0,     6,     0,     7,     0,     7,     0,     8,
       0,     7,     2,     3,     2,     3,     0,     8,     0,     9,
       0,     9,     3,     3,     2,     2,     0,     0,     3,     0,
       3,     1,     2,     0,     5,     0,     5,     0,     4,     0,
       5,     0,     1,     1,     3,     3,     1,     1,     1,     1,
       0,     5,     0,     5,     4,     4,     3,     3,     2,     2,
       2,     2,     3,     3,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     5,     5,     4,     3,     3,     1,     0,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     1,     3,     3,     3,     0,     0,
       9,     8,     7,     6,     4,     0,     2,     2,     3,     4,
       3,     2,     0,     4,     3,     1,     3,     3,     1,     4,
       4,     4,     3,     3,     1,     3,     3,     2,     2,     2,
       2,     0,     7,     0,     8,     0,     7,     0,     6,     0,
       5,     0,     6,     2,     3,     3,     3,     1,     3,     3,
       3,     3,     2,     4,     3,     5,     0,     2,     3,     4,
       3,     3,     2,     1,     1,     3,     3,     1,     4,     1,
       3,     1,     3,     3,     0,     3,     4,     3,     3,     2,
       1,     1,     3,     3,     8,     9,     8,     9,     9,     7,
       7,     8,     8,     8,     7,     1,     0,     3,     4,     3,
       2,     1,     3,     3,     0,     3,     4,     3,     3,     2,
       1,     3,     3,     3,     3,     3,     2,     2,     0,     3,
       0,     1,     2,     3,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned short yydefact[] =
{
       0,    36,    36,   133,    23,     0,   108,     0,     0,     0,
       0,   365,   365,   416,   358,     0,     0,     0,     0,   478,
       0,     2,    23,   108,   108,     5,     7,     0,     6,   112,
     109,   110,     8,    49,     0,     0,   351,     0,     0,   350,
     352,   277,   276,   336,   279,   278,     0,     9,     0,    10,
      11,     0,    12,   273,    13,     0,     0,     0,    16,     0,
       0,   113,     0,    17,   407,   431,     0,    18,   461,    19,
       0,    20,   470,    21,   480,     1,     0,     0,     0,    37,
      38,    39,     0,    40,   134,   135,   136,     0,     0,    33,
       0,   111,     0,    54,    75,     0,     0,   113,   289,   291,
     280,     0,     0,   339,   340,   341,   344,   342,   343,   346,
     345,   347,   348,   349,   288,   290,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   337,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   294,
     189,   185,   187,     0,     0,     0,     0,     0,   366,     0,
     367,     0,   417,     0,   412,    75,   389,     0,   390,    75,
       0,     0,     0,     0,     0,   476,     0,     0,   484,   485,
     486,   487,   481,     0,   477,     0,     0,     0,     0,    94,
      95,     0,    22,     0,     0,    58,    75,     0,     0,    32,
       0,    30,     0,    51,    50,    53,    75,    93,     0,    89,
     353,     0,   287,   286,   308,   307,   310,   309,   312,   311,
     314,   313,   316,   315,   320,   319,   322,   321,   324,   323,
     326,   325,   328,   327,   330,   329,     0,   296,   295,   298,
     297,   300,   299,   302,   301,   306,   305,   304,   303,     0,
     318,   317,     0,     0,   335,   334,   293,   292,   186,   188,
     275,   274,   371,   399,     0,     0,     0,     0,   357,     0,
     378,     0,   375,     0,     0,   411,   125,     0,   410,   409,
     408,   414,    75,   430,   433,   432,   463,   462,   475,   474,
     473,   472,   471,     0,   479,   482,    84,     0,     0,    85,
      75,   133,     0,   129,     0,    57,     0,    55,     0,    41,
      62,    29,     0,    31,    35,    34,     0,    52,    92,     0,
       0,    96,   354,     0,     0,   338,   333,     0,   285,   284,
     416,   374,     0,     0,   384,   397,     0,     0,   401,     0,
     370,     0,     0,     0,   368,     0,   364,     0,   119,   124,
       0,   413,   483,    83,     0,    81,     0,    88,     0,     0,
      48,    43,     0,   133,     0,   126,    56,    60,    59,    75,
       0,     0,    61,     0,     0,    80,     0,   103,    91,   102,
      75,     0,   104,    98,    90,    97,   281,     0,   283,   332,
     331,     0,     0,   388,   387,   373,     0,   416,   395,     0,
     403,     0,   416,     0,   391,   383,   382,     0,     0,   369,
     377,   376,     0,     0,     0,     0,   123,   121,     0,     0,
      82,    87,    86,   131,     0,     0,   193,    47,    46,    44,
       0,   133,   133,   213,    42,    64,     0,    63,    65,    28,
       0,   353,    79,    78,    76,   101,   107,     0,    99,     0,
     356,   355,   400,   423,     0,   193,   386,   385,     0,   416,
     406,   405,   404,     0,   393,   416,   381,   380,   379,   363,
       0,   353,     0,   118,     0,   117,   116,   114,   142,   141,
     146,     0,   143,     0,     0,     0,   194,   195,    45,   130,
       0,     0,   217,     0,     0,   279,    74,     0,    69,     0,
       0,    27,     0,    77,   100,   106,   105,   422,   427,     0,
     424,     0,   398,     0,   402,   416,     0,     0,   362,     0,
     120,     0,   115,   140,     0,   139,   137,     0,   206,   210,
       0,   201,   207,     0,   156,     0,     0,   196,   128,   127,
     220,     0,    68,     0,     0,    66,     0,    26,     0,   421,
       0,   420,   418,     0,     0,   396,     0,   392,   361,     0,
     122,   151,     0,   138,   145,   144,   205,   204,   202,     0,
     200,   199,   197,     0,   155,     0,   162,     0,   132,   218,
     219,     0,     0,   216,    67,    71,    70,    73,    72,    25,
       0,   419,   426,   425,   440,     0,   415,   394,   360,   150,
     149,   147,   203,   212,   211,   198,   209,   208,   154,   152,
     161,     0,     0,   163,     0,     0,   238,     0,     0,     0,
       0,     0,   223,   214,   222,   221,     0,   428,   439,     0,
       0,   441,   148,   153,     0,     0,   160,   158,     0,     0,
       0,     0,     0,     0,     0,   242,     0,   244,     0,     0,
     240,   255,   254,     0,     0,   224,   438,     0,     0,   437,
     435,     0,   170,     0,     0,   159,   165,     0,   175,   164,
     230,   228,     0,   234,   236,     0,     0,   243,   245,     0,
       0,     0,     0,   253,   252,   225,     0,     0,   436,   443,
       0,   455,   442,   169,     0,   176,     0,     0,   271,   271,
       0,     0,     0,     0,     0,     0,     0,   246,     0,     0,
       0,   456,     0,     0,   168,     0,   180,   174,     0,   176,
       0,   272,     0,     0,     0,     0,     0,     0,   248,   250,
       0,     0,   456,   456,     0,   180,     0,   456,     0,   456,
       0,     0,     0,   190,   173,   180,   271,   271,     0,     0,
       0,   233,     0,     0,     0,     0,   256,   180,   180,   460,
       0,   464,   456,   180,   456,   180,   179,     0,   177,     0,
       0,     0,     0,   190,     0,     0,     0,   235,   237,     0,
       0,     0,     0,     0,     0,   261,   257,   241,   464,   464,
     459,   457,     0,     0,   180,   464,   180,   464,   178,   184,
     183,   181,     0,     0,     0,   166,     0,   271,   271,     0,
     239,     0,     0,     0,     0,     0,   267,   247,   262,     0,
       0,     0,     0,   458,   469,     0,   446,   444,   464,     0,
     464,     0,   182,   192,   191,   167,     0,   171,     0,     0,
       0,   249,   251,   265,   263,   269,   220,   258,   260,   448,
     447,   468,   467,   465,   445,     0,   454,     0,   450,   449,
     172,     0,     0,   227,   220,   220,   220,   268,   466,   453,
     452,   451,   231,   229,   266,   264,   270
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,    20,    21,    25,   431,    28,    90,    22,    79,   360,
     294,    32,    33,    80,   184,   185,   362,   486,   487,   488,
     300,    81,   288,   289,    82,   260,   310,   311,   371,   372,
      35,   158,   404,   464,    83,   422,   353,   348,   349,   416,
     471,   472,   526,   568,   602,   603,   659,   706,   733,    50,
     762,   475,   476,   477,   523,   520,   614,   482,   483,   530,
     572,   615,   662,   689,   688,   665,   691,   692,   633,   672,
     720,   743,   744,   777,   809,   810,   774,   775,   855,   854,
     836,   856,   710,   711,    53,   200,   201,   226,   138,    48,
     313,    54,    58,   461,    55,   148,   255,   261,   262,   323,
     324,   149,   150,   455,   505,   449,   387,   320,   392,   329,
      63,    64,   381,   382,   445,   499,   500,    67,   586,   620,
     621,   682,   725,    69,   783,    71,    72,    73,    74,   174,
     175
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -749
static const short yypact[] =
{
    1011,  -749,  -749,  -749,  -749,    33,   717,   689,   689,   689,
     689,  -749,  -749,  -749,  -749,   774,  1841,   689,   689,  -749,
      29,  -749,   944,   770,   812,   136,  -749,   232,  -749,  -749,
       0,  -749,   -31,  -749,   229,    -3,  -749,   689,   689,  -749,
    -749,  -749,  -749,  -749,   126,  -749,  1847,  1801,   689,  1801,
    -749,  1050,   152,  1801,  -749,   679,   468,   452,   213,   272,
      25,   181,   261,   166,   244,  -749,   378,   275,  1801,   302,
    1151,   311,  -749,  -749,  3304,  -749,   578,    21,   -10,  -749,
    -749,  -749,   262,  -749,  -749,  -749,  -749,   458,   316,  -749,
      67,  -749,   670,  -749,  -749,   366,    43,   181,    -1,    -1,
     444,   351,  1459,  -749,  -749,  -749,  -749,  -749,  -749,  -749,
    -749,  -749,  -749,  -749,  -749,  -749,  1864,  1870,  1932,  1937,
    1964,  2005,  2032,  2037,  2098,  2105,  2128,  -749,  2145,  2206,
    2213,  2236,  2253,  2314,   689,  2321,  2344,   282,  2361,    -1,
       3,  -749,   689,  2422,   361,   367,   266,    -4,  -749,   278,
    -749,   368,  -749,   270,  -749,  -749,  -749,  2429,  -749,  -749,
     443,   416,   369,  2452,  2469,   689,  2530,  2537,  -749,  -749,
    -749,  -749,  -749,  1558,   397,   689,   380,   376,   407,  -749,
    -749,   -41,  -749,   421,    69,  -749,   509,   512,   448,  -749,
     535,  -749,   437,  -749,  -749,   521,  -749,  -749,   765,  -749,
     689,   635,  -749,  -749,  -749,   405,  -749,   405,  -749,    -1,
    -749,    -1,  -749,    -1,  -749,  3221,  -749,  3258,  -749,   572,
    -749,   572,  -749,   340,  -749,  3185,   689,  -749,   518,  -749,
     518,  -749,   811,  -749,   811,  -749,   518,  -749,   518,  1187,
    -749,  3279,   548,  1599,  -749,  -749,  -749,  1801,  -749,  -749,
    -749,  1801,  -749,  -749,   538,   573,   552,    46,  -749,   558,
     241,    71,  -749,   561,   596,   521,   567,   773,   521,  -749,
     244,  -749,  -749,  -749,  -749,  1801,  -749,  1801,  1801,  -749,
    1801,  -749,  -749,   689,  -749,  1801,  -749,   587,    90,  -749,
    -749,  -749,   246,  -749,    47,  -749,   597,  -749,   414,  -749,
     187,  -749,   188,  -749,  -749,  -749,  2560,   521,   324,   422,
      56,  -749,  1801,   -45,   576,  3164,  -749,  2577,  -749,  -749,
    -749,  -749,  2638,   636,  -749,  -749,   571,   293,  -749,    48,
    -749,  2645,  2668,   620,  -749,   529,  -749,   207,   689,   353,
    2685,   521,  1801,  -749,   633,  -749,   544,   521,   586,   549,
     599,  -749,    91,  -749,   641,  -749,  -749,  -749,  -749,  -749,
     645,   186,  -749,   652,   447,   659,  1286,  -749,  -749,   667,
    -749,   102,  -749,   669,  -749,  -749,  -749,  2746,  -749,  -749,
    3133,   656,   604,  -749,  1801,  -749,   455,  -749,  -749,   710,
    -749,   219,  -749,   707,  -749,  -749,  1801,   747,  1322,  -749,
    -749,  -749,   715,   595,   837,  1657,  -749,  -749,   753,  1425,
    -749,  -749,  -749,  -749,   752,   459,   197,  -749,   761,  -749,
     758,  -749,  -749,   865,  -749,  -749,   163,  -749,  1801,  -749,
     127,   689,  -749,   767,  -749,  -749,   521,   763,  -749,   608,
    -749,  1801,  -749,   368,   514,   197,  -749,  -749,   764,  -749,
    -749,  -749,  -749,   766,  -749,  -749,  -749,  -749,  -749,  -749,
     160,   689,   787,  -749,   689,  -749,   801,  -749,  -749,   768,
     819,   161,  -749,   540,   547,    16,   888,  -749,  -749,  -749,
     840,   843,  -749,   951,   849,   254,  -749,    32,  -749,   863,
     858,  -749,   -39,  -749,  -749,  -749,  -749,   864,   866,   176,
    -749,    16,  -749,   869,  -749,  -749,   873,   878,  -749,   -15,
    -749,  1700,  -749,  -749,  2753,   880,  -749,   594,   882,  -749,
     196,   883,  -749,   199,  -749,   606,    26,  -749,  -749,  -749,
     915,   884,  -749,   890,   169,  -749,   417,  -749,   894,  -749,
    1841,   895,  -749,   614,    27,  -749,   896,  -749,  -749,   897,
    -749,   899,   550,  -749,  -749,  -749,  -749,   898,  -749,   624,
    -749,   900,  -749,   630,  -749,    77,  -749,   637,  -749,  -749,
    -749,   262,  3033,  -749,  -749,  -749,  -749,  -749,  -749,  -749,
     373,  -749,  -749,  -749,  -749,   639,  -749,  -749,  -749,  -749,
     901,  -749,  -749,  -749,  -749,  -749,  -749,  -749,   905,  -749,
    -749,    20,   203,  -749,   210,   248,  -749,   223,   225,   249,
     871,   673,  -749,  -749,  -749,  -749,   874,  -749,   912,    22,
     209,  -749,  -749,  -749,   922,   640,   939,  -749,    23,   953,
    2776,   955,  2793,  3073,   975,  -749,  1002,  -749,  1008,  2854,
    -749,  -749,  -749,   910,  1004,  -749,  -749,  1049,  1039,  1009,
    -749,   211,  -749,  1007,    49,  -749,  -749,   642,  -749,  -749,
    -749,  -749,   689,  -749,  -749,   689,  1078,  -749,  -749,   689,
     689,   153,   689,  -749,  -749,  -749,  1046,    55,  -749,  -749,
     643,  -749,  -749,  -749,  1013,  1059,  1015,    61,   689,   689,
     730,   689,   689,   330,  1024,   342,   386,  -749,   399,  1018,
    1019,  1064,   148,    63,  -749,  2861,  1065,  -749,  1020,  1059,
    1025,   152,  1026,   689,   449,   532,  3073,   689,  -749,  -749,
    1027,  3073,  1064,  1064,  2884,  1065,  1028,  1064,  1029,  1064,
    1032,  1014,  2901,  1067,  -749,  1065,   689,   689,   736,  3073,
    3073,  -749,   623,  1031,  1033,   806,  1088,  1065,  1065,  -749,
     212,  1074,  1064,  1065,  1064,  1065,  -749,  1036,  -749,  1037,
     228,  2962,    36,  1067,  1038,  1040,   689,  -749,  -749,  1042,
     806,   806,  2969,   245,   589,  -749,  1142,  -749,  1074,  1074,
    1044,  -749,  2992,    37,  1065,  1074,  1065,  1074,  -749,  -749,
    1045,  -749,  1062,   749,  1076,  -749,    39,   689,   689,   631,
    -749,   638,   704,  1054,  1758,  1093,  -749,  -749,  -749,  3073,
    1190,  1095,  1109,  -749,  1120,   217,  1118,  -749,  1074,  1119,
    1074,    41,  -749,  -749,  -749,  -749,  1121,  -749,  1127,  1129,
    3073,  -749,  -749,  -749,  -749,  -749,  -749,  -749,  -749,  -749,
    -749,  -749,  1126,  -749,  -749,  1124,  -749,  1125,  1128,  -749,
    -749,  3073,  3073,  -749,  -749,  -749,  -749,  3073,  -749,  -749,
    -749,  -749,  -749,  -749,  3073,  3073,  3073
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -749,  -749,  -749,  1211,  -749,   -43,  -749,  1232,   -12,  -749,
    1051,   946,  1144,   -21,  -749,   941,  -749,  -353,  -749,   706,
     -58,   -19,  -749,   903,     1,   -57,  -749,   931,  -749,   803,
    -749,  1146,  -749,  -749,  -749,  -749,  -749,    76,  1241,  -749,
    -749,   728,   746,  -749,  -749,   622,  -749,   542,   226,   523,
     490,   813,  -749,   780,  -749,  -749,   902,  -749,  -749,  -749,
     -97,  -574,  -749,  -749,  -749,  -749,  -749,  -749,  -749,  -749,
    -749,  -749,  -749,  -749,  -749,  -749,  -480,  -748,  -749,  -749,
    -749,  -749,  -657,    -6,    -7,  -749,  -749,  -749,  -749,  -749,
    -388,  -749,  1202,  -749,  1247,   -44,  -749,  -749,   925,  -749,
     875,    -9,  -749,  -749,  -749,  -749,  -749,  -749,  -749,  -749,
     936,  1104,  -373,  1252,  -749,  -749,   723,   727,  -749,  -749,
     617,  -749,   231,   545,   170,   488,  1105,  -749,  -749,  -749,
    -749
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, parse error.  */
#define YYTABLE_NINF -435
static const short yytable[] =
{
      47,    49,    51,    85,    52,    86,    62,    34,   427,    66,
      68,    70,    84,   152,   448,   114,   115,   524,   248,   453,
     181,   624,   178,   647,   656,   186,   808,   566,   584,    75,
      98,    99,   712,   533,    26,   182,   195,   794,   816,   102,
     826,   139,   848,   492,   197,    27,    96,   326,   354,   393,
     684,    27,    91,   808,   808,   376,   700,   373,   292,   666,
     377,   538,   708,    87,   728,   293,   377,   173,   190,   153,
     296,    97,   333,   509,    92,   525,   503,   177,   598,   764,
     765,   625,   506,   648,   657,   549,   567,   585,    27,   257,
     377,   344,   418,    34,   179,   180,   601,   265,   249,   156,
     136,   268,   137,   437,   258,  -108,    29,    30,    31,   205,
     207,   209,   211,   213,   215,   217,   219,   221,   223,   225,
     290,   228,   230,   232,   234,   236,   238,   239,   241,   243,
    -108,   247,   546,  -157,  -434,   239,   251,   534,   307,   535,
     828,   829,   741,   795,   817,   327,   827,   746,   849,   198,
     267,    62,   328,   355,   394,   685,   275,   277,   278,   280,
      70,   701,   515,   374,   484,   767,   768,   709,   285,   729,
     575,   191,   192,   297,   298,   334,   335,   541,    36,    37,
      38,   599,    39,   578,    36,    37,    38,   425,    39,   363,
     361,   419,    40,   312,   345,   346,    92,   557,    40,   309,
     561,    36,    37,    38,   626,    39,   438,   439,   402,    87,
     649,   629,   679,   780,   341,    40,    41,    42,   842,   315,
     451,   726,    41,    42,   634,   100,   636,   490,    43,   790,
      93,   491,   347,    88,    43,   837,   485,   180,    45,    41,
      42,   359,   485,   180,    45,   331,   805,   350,   473,   631,
     638,    43,   370,   697,   727,   474,   853,   143,   143,    44,
     507,    45,    46,   183,   508,   516,   517,   256,    46,   426,
     160,   263,   680,   154,   264,   426,   342,   862,   863,   259,
     542,   543,   157,   244,   619,    46,   153,   364,   306,   290,
     801,   802,   426,    34,   389,  -108,    29,    30,    31,   366,
     558,   559,    94,   562,   563,    89,   403,   627,   628,   630,
     380,   309,   436,   650,   651,   384,   781,   164,    62,   452,
    -108,   843,   167,   160,   396,   398,    95,   635,    85,   637,
      86,   405,   791,   409,   159,   179,   180,    84,   152,   179,
     180,   806,   332,    59,    60,   155,   351,   632,   639,   161,
     -94,   179,   180,   100,   428,   245,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,    61,   254,   489,
     441,   128,   129,   130,   131,   132,   133,   287,  -429,   162,
     163,   103,   370,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   390,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   164,   127,   128,
     129,   130,   131,   132,   133,   357,   167,   271,   577,   428,
     189,   114,   115,   369,   312,   118,   119,   120,   367,   420,
     716,   368,    36,    37,    38,   143,    39,   135,   304,   196,
    -372,   136,   718,   137,   269,  -282,    40,   143,   430,   179,
     180,   202,   -15,   151,   312,   406,   446,   511,   407,   187,
     469,   188,   -24,   -24,   -24,   252,   -24,   253,   -14,   144,
      41,    42,   252,   134,   273,   135,   -24,   489,   163,   136,
     617,   137,    43,  -429,   286,  -429,   719,   179,   180,   272,
      44,   143,    45,    59,    60,   179,   180,   480,   481,   721,
     -24,   -24,   145,    60,   143,   284,   136,   552,   137,   569,
     305,   570,   -24,   291,   359,   497,    46,    61,   145,    60,
     -24,   302,   -24,   426,   146,   295,    61,   428,   322,   428,
     400,   571,   470,    66,   114,   115,   116,   117,   118,   119,
     120,   518,    61,   123,   124,   411,   -24,   -24,   521,   739,
     414,   590,   -24,   103,   143,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   616,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   176,
     127,   128,   129,   130,   131,   132,   133,   498,   114,   115,
     116,   117,   118,   119,   120,   554,   460,    76,  -108,    29,
      30,    31,   179,   180,   643,   443,   415,   564,   292,   495,
    -359,  -359,  -359,   519,  -359,   582,   301,   179,   180,   136,
     522,   137,   306,  -108,  -359,   593,   616,  -108,    29,    30,
      31,   596,   740,   671,   772,   773,   314,   143,   600,   303,
     618,   653,   321,   686,   702,   134,   322,   135,  -359,  -359,
     318,   136,  -108,   137,   145,    60,   690,   591,   325,   693,
    -359,   444,   330,   695,   696,   336,   698,   470,  -359,   337,
    -359,   193,   338,   136,   641,   137,   378,   388,    61,   565,
     144,   179,   180,   772,   773,   714,   715,   498,    36,    37,
      38,   343,    39,   413,  -359,  -359,   807,   594,   731,   417,
    -359,   356,    40,   597,    36,    37,    38,   738,    39,   616,
     601,   742,   619,   654,   616,   687,   703,    68,    40,  -108,
      29,    30,    31,   769,   399,    51,    41,    42,   143,   145,
      60,   830,   616,   616,  -358,   146,   143,   410,    43,   857,
     385,   386,    41,    42,  -108,   831,    44,   421,    45,   772,
     773,   423,  -358,    61,    43,   793,   429,   864,   865,   866,
     799,   432,    44,   442,    45,   804,   308,    29,    30,    31,
      -3,   435,    46,   367,   339,    70,   103,   642,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,    46,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   616,   127,   128,   129,   130,   131,   132,   133,
     450,   832,    -4,   454,  -108,    29,    30,    31,    76,   459,
      29,    30,    31,   616,    59,    60,    77,   114,   115,   116,
     117,   118,   119,   120,   713,   143,   123,   124,   462,  -108,
     766,   143,   128,   129,   616,   616,   132,   133,    61,   456,
     616,   772,   773,   824,   143,   465,   468,   616,   616,   616,
      76,   478,    29,    30,    31,   479,  -215,   494,   134,   493,
     135,   502,   513,   504,   136,   644,   137,   103,   340,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   510,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   512,   127,   128,   129,   130,   131,   132,
     133,   673,   136,   103,   137,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   514,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   473,
     127,   128,   129,   130,   131,   132,   133,   528,   811,   812,
     529,   751,   531,   747,   748,   819,   532,   821,   753,   536,
     755,   763,   537,    76,  -108,    29,    30,    31,   539,   134,
     640,   135,   540,   778,   779,   136,   545,   137,   645,   785,
     547,   787,   548,   784,   553,   786,   556,   560,   845,  -108,
     847,   573,    76,  -108,    29,    30,    31,   574,   579,   581,
      77,   588,   592,   587,   595,   134,   589,   135,   622,   623,
     818,   136,   820,   137,   674,   757,   646,   103,  -108,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   652,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   655,   127,   128,   129,   130,   131,   132,
     133,   140,   660,   103,   663,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   141,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   667,
     127,   128,   129,   130,   131,   132,   133,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,   668,   669,   675,   134,
     676,   135,   677,   678,   683,   136,   694,   137,   758,   699,
     704,   705,   707,   717,   722,   723,   724,   734,   732,   736,
     737,   761,   776,   745,   752,   754,   756,   770,   782,   771,
     788,   789,   797,  -259,   798,   142,   800,   135,   813,   822,
     833,   136,   165,   137,   103,   166,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   823,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     825,   127,   128,   129,   130,   131,   132,   133,   316,   835,
     103,   838,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   839,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   840,   127,   128,   129,
     130,   131,   132,   133,   841,   844,   846,   851,   850,   852,
     858,   859,   860,    78,    23,   861,   194,   299,   352,   358,
     576,   375,   496,   199,    24,   555,   134,   544,   135,   412,
     658,   735,   136,   796,   137,   760,   527,   147,   501,    56,
     401,   447,   424,   391,   270,    57,   583,   580,   681,   750,
     815,     0,   282,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   134,   317,   135,     0,     0,   433,   136,   103,
     137,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,     0,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,     0,   127,   128,   129,   130,
     131,   132,   133,   457,     0,   103,     0,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,     0,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,     0,   127,   128,   129,   130,   131,   132,   133,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   134,     0,   135,     0,     0,     0,   136,   434,   137,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   134,     0,   135,
       0,     0,     0,   136,   458,   137,   466,     0,   103,     0,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
       0,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,     0,   127,   128,   129,   130,   131,
     132,   133,   103,     0,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,     0,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,     0,   127,
     128,   129,   130,   131,   132,   133,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     134,     0,   135,     0,     0,     0,   136,   467,   137,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   134,     0,   135,     0,     0,   203,
     136,   103,   137,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,     0,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,     0,   127,   128,
     129,   130,   131,   132,   133,     0,     0,     0,     0,     0,
       0,     0,   103,     0,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,     0,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   283,   127,
     128,   129,   130,   131,   132,   133,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   134,     0,   135,     0,     0,     0,   136,
     103,   137,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,     0,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,     0,   127,   128,   129,
     130,   131,   132,   133,   134,     0,   135,     0,     0,     0,
     136,   319,   137,   103,     0,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,     0,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,     0,
     127,   128,   129,   130,   131,   132,   133,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   134,     0,   135,     0,     0,     0,   136,   463,
     137,   103,     0,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,     0,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,     0,   127,   128,
     129,   130,   131,   132,   133,   134,     0,   135,     0,     0,
       0,   136,   550,   137,   103,     0,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,     0,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
       0,   127,   128,   129,   130,   131,   132,   133,     0,     0,
       0,     0,    65,     0,     0,     0,     0,     0,   101,     0,
       0,     0,     0,   134,   834,   135,    36,    37,    38,   136,
      39,   137,    36,    37,    38,   204,    39,     0,     0,     0,
      40,   206,     0,     0,     0,     0,    40,     0,     0,    36,
      37,    38,     0,    39,     0,    36,    37,    38,     0,    39,
       0,     0,     0,    40,    41,    42,   134,     0,   135,    40,
      41,    42,   136,     0,   137,     0,    43,     0,     0,     0,
       0,     0,    43,     0,    44,     0,    45,    41,    42,     0,
      44,     0,    45,    41,    42,     0,     0,     0,     0,    43,
       0,     0,     0,   208,     0,    43,     0,    44,   210,    45,
      46,     0,     0,    44,     0,    45,    46,    36,    37,    38,
       0,    39,    36,    37,    38,     0,    39,     0,     0,     0,
       0,    40,     0,    46,     0,   212,    40,     0,     0,    46,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    36,
      37,    38,     0,    39,     0,    41,    42,     0,     0,     0,
      41,    42,     0,    40,     0,     0,     0,    43,     0,     0,
       0,     0,    43,     0,     0,    44,   214,    45,     0,     0,
      44,     0,    45,     0,     0,     0,     0,    41,    42,     0,
      36,    37,    38,     0,    39,     0,     0,     0,     0,    43,
       0,    46,     0,   216,    40,     0,    46,    44,   218,    45,
       0,     0,     0,     0,     0,     0,     0,    36,    37,    38,
       0,    39,    36,    37,    38,     0,    39,     0,    41,    42,
       0,    40,     0,    46,     0,     0,    40,     0,     0,     0,
      43,     0,     0,     0,     0,     0,     0,     0,    44,     0,
      45,     0,     0,     0,     0,    41,    42,     0,     0,     0,
      41,    42,     0,     0,     0,     0,     0,    43,     0,   220,
       0,     0,    43,     0,    46,    44,   222,    45,     0,     0,
      44,     0,    45,    36,    37,    38,     0,    39,     0,     0,
      36,    37,    38,     0,    39,     0,     0,    40,     0,   224,
       0,    46,     0,     0,    40,     0,    46,     0,     0,     0,
       0,     0,     0,    36,    37,    38,   227,    39,     0,     0,
       0,    41,    42,     0,     0,     0,     0,    40,    41,    42,
      36,    37,    38,    43,    39,     0,     0,     0,     0,     0,
      43,    44,     0,    45,    40,     0,     0,     0,    44,     0,
      45,    41,    42,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    43,     0,     0,     0,    46,    41,    42,
       0,    44,     0,    45,    46,     0,     0,   229,     0,     0,
      43,     0,     0,     0,   231,     0,     0,     0,    44,     0,
      45,    36,    37,    38,     0,    39,     0,    46,    36,    37,
      38,     0,    39,     0,     0,    40,     0,   233,     0,     0,
       0,     0,    40,     0,    46,     0,     0,     0,     0,     0,
       0,    36,    37,    38,   235,    39,     0,     0,     0,    41,
      42,     0,     0,     0,     0,    40,    41,    42,    36,    37,
      38,    43,    39,     0,     0,     0,     0,     0,    43,    44,
       0,    45,    40,     0,     0,     0,    44,     0,    45,    41,
      42,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    43,     0,     0,     0,    46,    41,    42,     0,    44,
       0,    45,    46,     0,     0,   237,     0,     0,    43,     0,
       0,     0,   240,     0,     0,     0,    44,     0,    45,    36,
      37,    38,     0,    39,     0,    46,    36,    37,    38,     0,
      39,     0,     0,    40,     0,   242,     0,     0,     0,     0,
      40,     0,    46,     0,     0,     0,     0,     0,     0,    36,
      37,    38,   246,    39,     0,     0,     0,    41,    42,     0,
       0,     0,     0,    40,    41,    42,    36,    37,    38,    43,
      39,     0,     0,     0,     0,     0,    43,    44,     0,    45,
      40,     0,     0,     0,    44,     0,    45,    41,    42,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    43,
       0,     0,     0,    46,    41,    42,     0,    44,     0,    45,
      46,     0,     0,   250,     0,     0,    43,     0,     0,     0,
     266,     0,     0,     0,    44,     0,    45,    36,    37,    38,
       0,    39,     0,    46,    36,    37,    38,     0,    39,     0,
       0,    40,     0,   274,     0,     0,     0,     0,    40,     0,
      46,     0,     0,     0,     0,     0,     0,    36,    37,    38,
     276,    39,     0,     0,     0,    41,    42,     0,     0,     0,
       0,    40,    41,    42,    36,    37,    38,    43,    39,     0,
       0,     0,     0,     0,    43,    44,     0,    45,    40,     0,
       0,     0,    44,     0,    45,    41,    42,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    43,     0,     0,
       0,    46,    41,    42,     0,    44,     0,    45,    46,     0,
       0,   279,     0,     0,    43,     0,     0,     0,   281,     0,
       0,     0,    44,     0,    45,    36,    37,    38,     0,    39,
       0,    46,    36,    37,    38,     0,    39,     0,     0,    40,
       0,   365,     0,     0,     0,     0,    40,     0,    46,     0,
       0,     0,     0,     0,     0,    36,    37,    38,   379,    39,
       0,     0,     0,    41,    42,     0,     0,     0,     0,    40,
      41,    42,    36,    37,    38,    43,    39,     0,     0,     0,
       0,     0,    43,    44,     0,    45,    40,     0,     0,     0,
      44,     0,    45,    41,    42,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    43,     0,     0,     0,    46,
      41,    42,     0,    44,     0,    45,    46,     0,     0,   383,
       0,     0,    43,     0,     0,     0,   395,     0,     0,     0,
      44,     0,    45,    36,    37,    38,     0,    39,     0,    46,
      36,    37,    38,     0,    39,     0,     0,    40,     0,   397,
       0,     0,     0,     0,    40,     0,    46,     0,     0,     0,
       0,     0,     0,    36,    37,    38,   408,    39,     0,     0,
       0,    41,    42,     0,     0,     0,     0,    40,    41,    42,
      36,    37,    38,    43,    39,     0,     0,     0,     0,     0,
      43,    44,     0,    45,    40,     0,     0,     0,    44,     0,
      45,    41,    42,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    43,     0,     0,     0,    46,    41,    42,
       0,    44,     0,    45,    46,     0,     0,   440,     0,     0,
      43,     0,     0,     0,   551,     0,     0,     0,    44,     0,
      45,    36,    37,    38,     0,    39,     0,    46,    36,    37,
      38,     0,    39,     0,     0,    40,     0,   661,     0,     0,
       0,     0,    40,     0,    46,     0,     0,     0,     0,     0,
       0,  -226,  -226,  -226,   664,  -226,     0,     0,     0,    41,
      42,     0,     0,     0,     0,  -226,    41,    42,  -232,  -232,
    -232,    43,  -232,     0,     0,     0,     0,     0,    43,    44,
       0,    45,  -232,     0,     0,     0,    44,     0,    45,  -226,
    -226,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -226,     0,     0,     0,    46,  -232,  -232,     0,  -226,
       0,  -226,    46,     0,     0,   670,     0,     0,  -232,     0,
       0,     0,   730,     0,     0,     0,  -232,     0,  -232,    36,
      37,    38,     0,    39,     0,  -226,    36,    37,    38,     0,
      39,     0,     0,    40,     0,   749,     0,     0,     0,     0,
      40,     0,  -232,     0,     0,     0,     0,     0,     0,    36,
      37,    38,   759,    39,     0,     0,     0,    41,    42,     0,
       0,     0,     0,    40,    41,    42,    36,    37,    38,    43,
      39,     0,     0,     0,     0,     0,    43,    44,     0,    45,
      40,     0,     0,     0,    44,     0,    45,    41,    42,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    43,
       0,     0,     0,    46,    41,    42,     0,    44,     0,    45,
      46,     0,     0,   792,     0,     0,    43,     0,     0,     0,
     803,     0,     0,     0,    44,     0,    45,    36,    37,    38,
       0,    39,     0,    46,    36,    37,    38,     0,    39,     0,
       0,    40,     0,   814,     0,     0,     0,     0,    40,     0,
      46,     0,     0,     0,     0,     0,     0,    36,    37,    38,
       0,    39,     0,     0,     0,    41,    42,     0,     0,     0,
       0,    40,    41,    42,     0,     0,     0,    43,     0,     0,
       0,     0,     0,     0,    43,    44,     0,    45,     0,     0,
       0,     0,    44,     0,    45,    41,    42,     0,    36,    37,
      38,     0,    39,     0,     0,     0,     0,    43,     0,     0,
       0,    46,    40,     0,     0,    44,     0,    45,    46,     0,
     604,   605,   606,   607,   608,   609,   610,     0,     0,     0,
     611,     0,     0,     0,     0,     0,    41,    42,    36,    37,
      38,    46,    39,     0,     0,     0,     0,     0,    43,     0,
       0,     0,    40,     0,     0,     0,    44,     0,    45,     0,
     604,   605,   606,   607,   608,   609,   610,     0,     0,     0,
     611,     0,     0,     0,     0,     0,    41,    42,     0,     0,
       0,     0,    46,     0,     0,     0,     0,   612,    43,   423,
     613,     0,     0,     0,     0,     0,    44,     0,    45,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,     0,   127,   128,   129,   130,   131,   132,   133,
       0,     0,    46,     0,     0,     0,     0,   612,     0,   423,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,     0,     0,   128,   129,   130,   131,   132,
     133,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,     0,     0,     0,   128,   129,   130,   131,
     132,   133,     0,     0,     0,     0,     0,     0,   134,     0,
     135,     0,     0,     0,   136,     0,   137,   114,   115,   116,
     117,   118,   119,   120,     0,   122,   123,   124,     0,     0,
       0,     0,   128,   129,   130,   131,   132,   133,     0,     0,
       0,   135,     0,     0,     0,   136,     0,   137,     0,     0,
       0,     0,     0,     0,   114,   115,   116,   117,   118,   119,
     120,     0,   135,   123,   124,     0,   136,     0,   137,   128,
     129,   130,   131,   132,   133,   114,   115,   116,   117,   118,
     119,   120,     0,     0,   123,   124,     0,     0,     0,     0,
     128,   129,   130,   131,   132,   133,     0,     0,   135,    36,
      37,    38,   136,    39,   137,     0,     0,     0,     0,     0,
       0,     0,     0,    40,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   135,     0,    41,    42,   136,
       0,   137,     0,     0,     0,     0,     0,     0,     0,    43,
     168,   169,   170,   171,     0,   172,     0,    44,     0,    45,
     136,     0,   137,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    46
};

static const short yycheck[] =
{
       7,     8,     9,    24,    10,    24,    15,     6,   361,    16,
      17,    18,    24,    57,   387,    16,    17,     1,    15,   392,
      77,     1,     1,     1,     1,    82,   774,     1,     1,     0,
      37,    38,   689,     1,     1,    78,    94,     1,     1,    46,
       1,    48,     1,   431,     1,    55,    49,     1,     1,     1,
       1,    55,    52,   801,   802,   100,     1,     1,    99,   633,
     105,   100,     1,    73,     1,   106,   105,    74,     1,    73,
       1,    74,     1,   461,   105,    59,   449,    76,     1,   736,
     737,    61,   455,    61,    61,   100,    60,    60,    55,   146,
     105,     1,     1,    92,    73,    74,    73,   155,    95,    74,
     101,   159,   103,     1,   147,    49,    50,    51,    52,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     177,   128,   129,   130,   131,   132,   133,   134,   135,   136,
      74,   138,   505,   107,   107,   142,   143,   105,   196,   107,
     797,   798,   716,   107,   107,    99,   107,   721,   107,   106,
     157,   160,   106,   106,   106,   106,   163,   164,   165,   166,
     167,   106,     1,   107,     1,   739,   740,   106,   175,   106,
       1,   104,   105,   104,   105,   104,   105,     1,    15,    16,
      17,   104,    19,   536,    15,    16,    17,     1,    19,     1,
       3,   100,    29,   200,   104,   105,   105,     1,    29,   198,
       1,    15,    16,    17,     1,    19,   104,   105,     1,    73,
       1,     1,     1,     1,   272,    29,    53,    54,     1,   226,
       1,    73,    53,    54,     1,    99,     1,   100,    65,     1,
       1,   104,   290,     1,    65,   809,    73,    74,    75,    53,
      54,   298,    73,    74,    75,     4,     1,     1,    51,     1,
       1,    65,   309,   100,   106,    58,   830,   105,   105,    73,
     100,    75,    99,     1,   104,   104,   105,     1,    99,   106,
     104,     1,    61,     1,     4,   106,   283,   851,   852,     1,
     104,   105,   101,     1,    73,    99,    73,    99,   101,   346,
     770,   771,   106,   292,     1,    49,    50,    51,    52,   306,
     104,   105,    73,   104,   105,    73,    99,   104,   105,    99,
     317,   310,   370,   104,   105,   322,   104,   105,   327,   100,
      74,   104,   105,   104,   331,   332,    97,   104,   349,   104,
     349,   338,   104,   340,    73,    73,    74,   349,   382,    73,
      74,    96,   101,    50,    51,    73,   100,    99,    99,   105,
      96,    73,    74,    99,   361,    73,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    74,     1,   426,
     377,    31,    32,    33,    34,    35,    36,     1,     0,     1,
     105,     3,   439,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,   100,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,   105,    30,    31,
      32,    33,    34,    35,    36,     1,   105,     1,     1,   426,
     104,    16,    17,     1,   431,    20,    21,    22,   104,   353,
     100,   107,    15,    16,    17,   105,    19,    97,     1,    73,
      73,   101,   100,   103,     1,     1,    29,   105,     1,    73,
      74,   100,     0,     1,   461,   102,     1,   464,   105,     1,
       1,     3,    15,    16,    17,   104,    19,   106,     0,     1,
      53,    54,   104,    95,   105,    97,    29,   534,   105,   101,
     107,   103,    65,   105,   104,   107,   100,    73,    74,    73,
      73,   105,    75,    50,    51,    73,    74,   421,   422,   100,
      53,    54,    50,    51,   105,   108,   101,   514,   103,   530,
      73,   530,    65,   106,   571,     1,    99,    74,    50,    51,
      73,    73,    75,   106,    56,   104,    74,   534,    73,   536,
       1,   530,    73,   540,    16,    17,    18,    19,    20,    21,
      22,     1,    74,    25,    26,     1,    99,   100,     1,   100,
       1,     1,   105,     3,   105,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,   572,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,     1,
      30,    31,    32,    33,    34,    35,    36,    73,    16,    17,
      18,    19,    20,    21,    22,     1,     1,    48,    49,    50,
      51,    52,    73,    74,   611,     1,    57,     1,    99,     1,
      15,    16,    17,    73,    19,     1,   104,    73,    74,   101,
      73,   103,   101,    74,    29,     1,   633,    49,    50,    51,
      52,     1,   100,   639,    45,    46,     1,   105,     1,   104,
       1,     1,   104,     1,     1,    95,    73,    97,    53,    54,
     102,   101,    74,   103,    50,    51,   662,   107,   106,   665,
      65,    57,   104,   669,   670,   104,   672,    73,    73,    73,
      75,     1,   105,   101,     1,   103,   100,   106,    74,    73,
       1,    73,    74,    45,    46,   691,   692,    73,    15,    16,
      17,   104,    19,   107,    99,   100,   107,    73,   705,   100,
     105,   104,    29,    73,    15,    16,    17,   713,    19,   716,
      73,   717,    73,    73,   721,    73,    73,   724,    29,    49,
      50,    51,    52,   100,   104,   732,    53,    54,   105,    50,
      51,   100,   739,   740,    55,    56,   105,   104,    65,   836,
     104,   105,    53,    54,    74,   107,    73,   106,    75,    45,
      46,   106,    73,    74,    65,   761,   104,   854,   855,   856,
     766,   102,    73,   107,    75,   772,     1,    50,    51,    52,
       0,   104,    99,   104,     1,   782,     3,   104,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    99,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,   809,    30,    31,    32,    33,    34,    35,    36,
     100,   107,     0,   106,    49,    50,    51,    52,    48,   104,
      50,    51,    52,   830,    50,    51,    56,    16,    17,    18,
      19,    20,    21,    22,   104,   105,    25,    26,     1,    74,
     104,   105,    31,    32,   851,   852,    35,    36,    74,   102,
     857,    45,    46,   104,   105,   102,   104,   864,   865,   866,
      48,   100,    50,    51,    52,   107,     1,   104,    95,   102,
      97,   107,   104,   107,   101,     1,   103,     3,   105,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,   102,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   102,    30,    31,    32,    33,    34,    35,
      36,     1,   101,     3,   103,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,   106,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    51,
      30,    31,    32,    33,    34,    35,    36,   107,   778,   779,
     107,   725,     1,   722,   723,   785,   107,   787,   727,    96,
     729,   735,   104,    48,    49,    50,    51,    52,   104,    95,
      99,    97,   106,   747,   748,   101,   107,   103,   104,   753,
     107,   755,   104,   752,   104,   754,   104,   104,   818,    74,
     820,   107,    48,    49,    50,    51,    52,   107,   104,   104,
      56,   104,   104,   107,   104,    95,   107,    97,   107,   104,
     784,   101,   786,   103,   104,     1,   104,     3,    74,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,   107,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   104,    30,    31,    32,    33,    34,    35,
      36,     1,    99,     3,    99,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,   104,
      30,    31,    32,    33,    34,    35,    36,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,   104,    99,   104,    95,
      61,    97,    73,   104,   107,   101,    38,   103,   104,    73,
     107,    62,   107,    99,   106,   106,    62,   107,    63,   104,
     104,    64,    44,   106,   106,   106,   104,   106,    64,   106,
     104,   104,   104,     1,   104,    95,   104,    97,   104,   104,
      96,   101,     1,   103,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,   104,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
     104,    30,    31,    32,    33,    34,    35,    36,     1,    96,
       3,     1,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,   107,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,   107,    30,    31,    32,
      33,    34,    35,    36,   104,   107,   107,   100,   107,   100,
     104,   107,   107,    22,     2,   107,    92,   186,   292,   298,
     534,   310,   439,    97,     3,   517,    95,   501,    97,   346,
     628,   709,   101,   763,   103,   732,   476,    55,   445,    12,
     335,   386,   360,   327,   160,    13,   543,   540,   651,   724,
     782,    -1,   167,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    95,    96,    97,    -1,    -1,     1,   101,     3,
     103,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    -1,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    -1,    30,    31,    32,    33,
      34,    35,    36,     1,    -1,     3,    -1,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    -1,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    -1,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    95,    -1,    97,    -1,    -1,    -1,   101,   102,   103,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,    -1,    97,
      -1,    -1,    -1,   101,   102,   103,     1,    -1,     3,    -1,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    -1,    30,    31,    32,    33,    34,
      35,    36,     3,    -1,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    -1,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    -1,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      95,    -1,    97,    -1,    -1,    -1,   101,   102,   103,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    95,    -1,    97,    -1,    -1,   100,
     101,     3,   103,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    -1,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    -1,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     3,    -1,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    -1,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    70,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    95,    -1,    97,    -1,    -1,    -1,   101,
       3,   103,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    -1,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    -1,    30,    31,    32,
      33,    34,    35,    36,    95,    -1,    97,    -1,    -1,    -1,
     101,   102,   103,     3,    -1,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    -1,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    -1,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    95,    -1,    97,    -1,    -1,    -1,   101,   102,
     103,     3,    -1,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    -1,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    -1,    30,    31,
      32,    33,    34,    35,    36,    95,    -1,    97,    -1,    -1,
      -1,   101,   102,   103,     3,    -1,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    -1,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,     1,    -1,
      -1,    -1,    -1,    95,    96,    97,    15,    16,    17,   101,
      19,   103,    15,    16,    17,     1,    19,    -1,    -1,    -1,
      29,     1,    -1,    -1,    -1,    -1,    29,    -1,    -1,    15,
      16,    17,    -1,    19,    -1,    15,    16,    17,    -1,    19,
      -1,    -1,    -1,    29,    53,    54,    95,    -1,    97,    29,
      53,    54,   101,    -1,   103,    -1,    65,    -1,    -1,    -1,
      -1,    -1,    65,    -1,    73,    -1,    75,    53,    54,    -1,
      73,    -1,    75,    53,    54,    -1,    -1,    -1,    -1,    65,
      -1,    -1,    -1,     1,    -1,    65,    -1,    73,     1,    75,
      99,    -1,    -1,    73,    -1,    75,    99,    15,    16,    17,
      -1,    19,    15,    16,    17,    -1,    19,    -1,    -1,    -1,
      -1,    29,    -1,    99,    -1,     1,    29,    -1,    -1,    99,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    15,
      16,    17,    -1,    19,    -1,    53,    54,    -1,    -1,    -1,
      53,    54,    -1,    29,    -1,    -1,    -1,    65,    -1,    -1,
      -1,    -1,    65,    -1,    -1,    73,     1,    75,    -1,    -1,
      73,    -1,    75,    -1,    -1,    -1,    -1,    53,    54,    -1,
      15,    16,    17,    -1,    19,    -1,    -1,    -1,    -1,    65,
      -1,    99,    -1,     1,    29,    -1,    99,    73,     1,    75,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    15,    16,    17,
      -1,    19,    15,    16,    17,    -1,    19,    -1,    53,    54,
      -1,    29,    -1,    99,    -1,    -1,    29,    -1,    -1,    -1,
      65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    -1,
      75,    -1,    -1,    -1,    -1,    53,    54,    -1,    -1,    -1,
      53,    54,    -1,    -1,    -1,    -1,    -1,    65,    -1,     1,
      -1,    -1,    65,    -1,    99,    73,     1,    75,    -1,    -1,
      73,    -1,    75,    15,    16,    17,    -1,    19,    -1,    -1,
      15,    16,    17,    -1,    19,    -1,    -1,    29,    -1,     1,
      -1,    99,    -1,    -1,    29,    -1,    99,    -1,    -1,    -1,
      -1,    -1,    -1,    15,    16,    17,     1,    19,    -1,    -1,
      -1,    53,    54,    -1,    -1,    -1,    -1,    29,    53,    54,
      15,    16,    17,    65,    19,    -1,    -1,    -1,    -1,    -1,
      65,    73,    -1,    75,    29,    -1,    -1,    -1,    73,    -1,
      75,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    -1,    -1,    -1,    99,    53,    54,
      -1,    73,    -1,    75,    99,    -1,    -1,     1,    -1,    -1,
      65,    -1,    -1,    -1,     1,    -1,    -1,    -1,    73,    -1,
      75,    15,    16,    17,    -1,    19,    -1,    99,    15,    16,
      17,    -1,    19,    -1,    -1,    29,    -1,     1,    -1,    -1,
      -1,    -1,    29,    -1,    99,    -1,    -1,    -1,    -1,    -1,
      -1,    15,    16,    17,     1,    19,    -1,    -1,    -1,    53,
      54,    -1,    -1,    -1,    -1,    29,    53,    54,    15,    16,
      17,    65,    19,    -1,    -1,    -1,    -1,    -1,    65,    73,
      -1,    75,    29,    -1,    -1,    -1,    73,    -1,    75,    53,
      54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    -1,    -1,    -1,    99,    53,    54,    -1,    73,
      -1,    75,    99,    -1,    -1,     1,    -1,    -1,    65,    -1,
      -1,    -1,     1,    -1,    -1,    -1,    73,    -1,    75,    15,
      16,    17,    -1,    19,    -1,    99,    15,    16,    17,    -1,
      19,    -1,    -1,    29,    -1,     1,    -1,    -1,    -1,    -1,
      29,    -1,    99,    -1,    -1,    -1,    -1,    -1,    -1,    15,
      16,    17,     1,    19,    -1,    -1,    -1,    53,    54,    -1,
      -1,    -1,    -1,    29,    53,    54,    15,    16,    17,    65,
      19,    -1,    -1,    -1,    -1,    -1,    65,    73,    -1,    75,
      29,    -1,    -1,    -1,    73,    -1,    75,    53,    54,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    -1,    -1,    99,    53,    54,    -1,    73,    -1,    75,
      99,    -1,    -1,     1,    -1,    -1,    65,    -1,    -1,    -1,
       1,    -1,    -1,    -1,    73,    -1,    75,    15,    16,    17,
      -1,    19,    -1,    99,    15,    16,    17,    -1,    19,    -1,
      -1,    29,    -1,     1,    -1,    -1,    -1,    -1,    29,    -1,
      99,    -1,    -1,    -1,    -1,    -1,    -1,    15,    16,    17,
       1,    19,    -1,    -1,    -1,    53,    54,    -1,    -1,    -1,
      -1,    29,    53,    54,    15,    16,    17,    65,    19,    -1,
      -1,    -1,    -1,    -1,    65,    73,    -1,    75,    29,    -1,
      -1,    -1,    73,    -1,    75,    53,    54,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,
      -1,    99,    53,    54,    -1,    73,    -1,    75,    99,    -1,
      -1,     1,    -1,    -1,    65,    -1,    -1,    -1,     1,    -1,
      -1,    -1,    73,    -1,    75,    15,    16,    17,    -1,    19,
      -1,    99,    15,    16,    17,    -1,    19,    -1,    -1,    29,
      -1,     1,    -1,    -1,    -1,    -1,    29,    -1,    99,    -1,
      -1,    -1,    -1,    -1,    -1,    15,    16,    17,     1,    19,
      -1,    -1,    -1,    53,    54,    -1,    -1,    -1,    -1,    29,
      53,    54,    15,    16,    17,    65,    19,    -1,    -1,    -1,
      -1,    -1,    65,    73,    -1,    75,    29,    -1,    -1,    -1,
      73,    -1,    75,    53,    54,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    99,
      53,    54,    -1,    73,    -1,    75,    99,    -1,    -1,     1,
      -1,    -1,    65,    -1,    -1,    -1,     1,    -1,    -1,    -1,
      73,    -1,    75,    15,    16,    17,    -1,    19,    -1,    99,
      15,    16,    17,    -1,    19,    -1,    -1,    29,    -1,     1,
      -1,    -1,    -1,    -1,    29,    -1,    99,    -1,    -1,    -1,
      -1,    -1,    -1,    15,    16,    17,     1,    19,    -1,    -1,
      -1,    53,    54,    -1,    -1,    -1,    -1,    29,    53,    54,
      15,    16,    17,    65,    19,    -1,    -1,    -1,    -1,    -1,
      65,    73,    -1,    75,    29,    -1,    -1,    -1,    73,    -1,
      75,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    -1,    -1,    -1,    99,    53,    54,
      -1,    73,    -1,    75,    99,    -1,    -1,     1,    -1,    -1,
      65,    -1,    -1,    -1,     1,    -1,    -1,    -1,    73,    -1,
      75,    15,    16,    17,    -1,    19,    -1,    99,    15,    16,
      17,    -1,    19,    -1,    -1,    29,    -1,     1,    -1,    -1,
      -1,    -1,    29,    -1,    99,    -1,    -1,    -1,    -1,    -1,
      -1,    15,    16,    17,     1,    19,    -1,    -1,    -1,    53,
      54,    -1,    -1,    -1,    -1,    29,    53,    54,    15,    16,
      17,    65,    19,    -1,    -1,    -1,    -1,    -1,    65,    73,
      -1,    75,    29,    -1,    -1,    -1,    73,    -1,    75,    53,
      54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    -1,    -1,    -1,    99,    53,    54,    -1,    73,
      -1,    75,    99,    -1,    -1,     1,    -1,    -1,    65,    -1,
      -1,    -1,     1,    -1,    -1,    -1,    73,    -1,    75,    15,
      16,    17,    -1,    19,    -1,    99,    15,    16,    17,    -1,
      19,    -1,    -1,    29,    -1,     1,    -1,    -1,    -1,    -1,
      29,    -1,    99,    -1,    -1,    -1,    -1,    -1,    -1,    15,
      16,    17,     1,    19,    -1,    -1,    -1,    53,    54,    -1,
      -1,    -1,    -1,    29,    53,    54,    15,    16,    17,    65,
      19,    -1,    -1,    -1,    -1,    -1,    65,    73,    -1,    75,
      29,    -1,    -1,    -1,    73,    -1,    75,    53,    54,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    -1,    -1,    99,    53,    54,    -1,    73,    -1,    75,
      99,    -1,    -1,     1,    -1,    -1,    65,    -1,    -1,    -1,
       1,    -1,    -1,    -1,    73,    -1,    75,    15,    16,    17,
      -1,    19,    -1,    99,    15,    16,    17,    -1,    19,    -1,
      -1,    29,    -1,     1,    -1,    -1,    -1,    -1,    29,    -1,
      99,    -1,    -1,    -1,    -1,    -1,    -1,    15,    16,    17,
      -1,    19,    -1,    -1,    -1,    53,    54,    -1,    -1,    -1,
      -1,    29,    53,    54,    -1,    -1,    -1,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    73,    -1,    75,    -1,    -1,
      -1,    -1,    73,    -1,    75,    53,    54,    -1,    15,    16,
      17,    -1,    19,    -1,    -1,    -1,    -1,    65,    -1,    -1,
      -1,    99,    29,    -1,    -1,    73,    -1,    75,    99,    -1,
      37,    38,    39,    40,    41,    42,    43,    -1,    -1,    -1,
      47,    -1,    -1,    -1,    -1,    -1,    53,    54,    15,    16,
      17,    99,    19,    -1,    -1,    -1,    -1,    -1,    65,    -1,
      -1,    -1,    29,    -1,    -1,    -1,    73,    -1,    75,    -1,
      37,    38,    39,    40,    41,    42,    43,    -1,    -1,    -1,
      47,    -1,    -1,    -1,    -1,    -1,    53,    54,    -1,    -1,
      -1,    -1,    99,    -1,    -1,    -1,    -1,   104,    65,   106,
     107,    -1,    -1,    -1,    -1,    -1,    73,    -1,    75,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    99,    -1,    -1,    -1,    -1,   104,    -1,   106,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    -1,    -1,    31,    32,    33,    34,    35,
      36,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    -1,    -1,    31,    32,    33,    34,
      35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    95,    -1,
      97,    -1,    -1,    -1,   101,    -1,   103,    16,    17,    18,
      19,    20,    21,    22,    -1,    24,    25,    26,    -1,    -1,
      -1,    -1,    31,    32,    33,    34,    35,    36,    -1,    -1,
      -1,    97,    -1,    -1,    -1,   101,    -1,   103,    -1,    -1,
      -1,    -1,    -1,    -1,    16,    17,    18,    19,    20,    21,
      22,    -1,    97,    25,    26,    -1,   101,    -1,   103,    31,
      32,    33,    34,    35,    36,    16,    17,    18,    19,    20,
      21,    22,    -1,    -1,    25,    26,    -1,    -1,    -1,    -1,
      31,    32,    33,    34,    35,    36,    -1,    -1,    97,    15,
      16,    17,   101,    19,   103,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    29,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    97,    -1,    53,    54,   101,
      -1,   103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      66,    67,    68,    69,    -1,    71,    -1,    73,    -1,    75,
     101,    -1,   103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    99
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
     110,   111,   116,   116,   147,   112,     1,    55,   114,    50,
      51,    52,   120,   121,   133,   139,    15,    16,    17,    19,
      29,    53,    54,    65,    73,    75,    99,   193,   198,   193,
     158,   193,   192,   193,   200,   203,   203,   222,   201,    50,
      51,    74,   210,   219,   220,     1,   193,   226,   193,   232,
     193,   234,   235,   236,   237,     0,    48,    56,   112,   117,
     122,   130,   133,   143,   117,   122,   130,    73,     1,    73,
     115,    52,   105,     1,    73,    97,    49,    74,   193,   193,
      99,     1,   193,     3,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    30,    31,    32,
      33,    34,    35,    36,    95,    97,   101,   103,   197,   193,
       1,    15,    95,   105,     1,    50,    56,   201,   204,   210,
     211,     1,   204,    73,     1,    73,    74,   101,   140,    73,
     104,   105,     1,   105,   105,     1,     4,   105,    66,    67,
      68,    69,    71,   193,   238,   239,     1,   133,     1,    73,
      74,   134,   114,     1,   123,   124,   134,     1,     3,   104,
       1,   104,   105,     1,   121,   129,    73,     1,   106,   140,
     194,   195,   100,   100,     1,   193,     1,   193,     1,   193,
       1,   193,     1,   193,     1,   193,     1,   193,     1,   193,
       1,   193,     1,   193,     1,   193,   196,     1,   193,     1,
     193,     1,   193,     1,   193,     1,   193,     1,   193,   193,
       1,   193,     1,   193,     1,    73,     1,   193,    15,    95,
       1,   193,   104,   106,     1,   205,     1,   134,   114,     1,
     134,   206,   207,     1,     4,   129,     1,   193,   129,     1,
     220,     1,    73,   105,     1,   193,     1,   193,   193,     1,
     193,     1,   235,    70,   108,   193,   104,     1,   131,   132,
     134,   106,    99,   106,   119,   104,     1,   104,   105,   119,
     129,   104,    73,   104,     1,    73,   101,   129,     1,   133,
     135,   136,   193,   199,     1,   193,     1,    96,   102,   102,
     216,   104,    73,   208,   209,   106,     1,    99,   106,   218,
     104,     4,   101,     1,   104,   105,   104,    73,   105,     1,
     105,   129,   193,   104,     1,   104,   105,   129,   146,   147,
       1,   100,   120,   145,     1,   106,   104,     1,   124,   134,
     118,     3,   125,     1,    99,     1,   193,   104,   107,     1,
     134,   137,   138,     1,   107,   136,   100,   105,   100,     1,
     193,   221,   222,     1,   193,   104,   105,   215,   106,     1,
     100,   219,   217,     1,   106,     1,   193,     1,   193,   104,
       1,   207,     1,    99,   141,   193,   102,   105,     1,   193,
     104,     1,   132,   107,     1,    57,   148,   100,     1,   100,
     146,   106,   144,   106,   165,     1,   106,   126,   193,   104,
       1,   113,   102,     1,   102,   104,   129,     1,   104,   105,
       1,   193,   107,     1,    57,   223,     1,   209,   221,   214,
     100,     1,   100,   221,   106,   212,   102,     1,   102,   104,
       1,   202,     1,   102,   142,   102,     1,   102,   104,     1,
      73,   149,   150,    51,    58,   160,   161,   162,   100,   107,
     146,   146,   166,   167,     1,    73,   126,   127,   128,   134,
     100,   104,   199,   102,   104,     1,   138,     1,    73,   224,
     225,   160,   107,   221,   107,   213,   221,   100,   104,   199,
     102,   193,   102,   104,   106,     1,   104,   105,     1,    73,
     164,     1,    73,   163,     1,    59,   151,   162,   107,   107,
     168,     1,   107,     1,   105,   107,    96,   104,   100,   104,
     106,     1,   104,   105,   151,   107,   221,   107,   104,   100,
     102,     1,   193,   104,     1,   150,   104,     1,   104,   105,
     104,     1,   104,   105,     1,    73,     1,    60,   152,   122,
     130,   133,   169,   107,   107,     1,   128,     1,   126,   104,
     226,   104,     1,   225,     1,    60,   227,   107,   104,   107,
       1,   107,   104,     1,    73,   104,     1,    73,     1,   104,
       1,    73,   153,   154,    37,    38,    39,    40,    41,    42,
      43,    47,   104,   107,   165,   170,   193,   107,     1,    73,
     228,   229,   107,   104,     1,    61,     1,   104,   105,     1,
      99,     1,    99,   177,     1,   104,     1,   104,     1,    99,
      99,     1,   104,   193,     1,   104,   104,     1,    61,     1,
     104,   105,   107,     1,    73,   104,     1,    61,   154,   155,
      99,     1,   171,    99,     1,   174,   170,   104,   104,    99,
       1,   192,   178,     1,   104,   104,    61,    73,   104,     1,
      61,   229,   230,   107,     1,   106,     1,    73,   173,   172,
     192,   175,   176,   192,    38,   192,   192,   100,   192,    73,
       1,   106,     1,    73,   107,    62,   156,   107,     1,   106,
     191,   192,   191,   104,   192,   192,   100,    99,   100,   100,
     179,   100,   106,   106,    62,   231,    73,   106,     1,   106,
       1,   193,    63,   157,   107,   156,   104,   104,   192,   100,
     100,   170,   192,   180,   181,   106,   170,   231,   231,     1,
     232,   157,   106,   231,   106,   231,   104,     1,   104,     1,
     158,    64,   159,   157,   191,   191,   104,   170,   170,   100,
     106,   106,    45,    46,   185,   186,    44,   182,   157,   157,
       1,   104,    64,   233,   231,   157,   231,   157,   104,   104,
       1,   104,     1,   192,     1,   107,   159,   104,   104,   192,
     104,   185,   185,     1,   193,     1,    96,   107,   186,   183,
     184,   233,   233,   104,     1,   234,     1,   107,   157,   233,
     157,   233,   104,   104,   104,   104,     1,   107,   191,   191,
     100,   107,   107,    96,    96,    96,   189,   170,     1,   107,
     107,   104,     1,   104,   107,   233,   107,   233,     1,   107,
     107,   100,   100,   170,   188,   187,   190,   169,   104,   107,
     107,   107,   170,   170,   169,   169,   169
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrlab1

/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");			\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)           \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */

#define YYLEX	yylex ()

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)
# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)
/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*-----------------------------.
| Print this symbol on YYOUT.  |
`-----------------------------*/

static void
#if defined (__STDC__) || defined (__cplusplus)
yysymprint (FILE* yyout, int yytype, YYSTYPE yyvalue, YYLTYPE yylocation)
#else
yysymprint (yyout, yytype, yyvalue, yylocation)
    FILE* yyout;
    int yytype;
    YYSTYPE yyvalue;
    YYLTYPE yylocation;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvalue;
  (void) yylocation;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyout, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyout, yytoknum[yytype], yyvalue);
# endif
    }
  else
    YYFPRINTF (yyout, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyout, ")");
}
#endif /* YYDEBUG. */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
#if defined (__STDC__) || defined (__cplusplus)
yydestruct (int yytype, YYSTYPE yyvalue, YYLTYPE yylocation)
#else
yydestruct (yytype, yyvalue, yylocation)
    int yytype;
    YYSTYPE yyvalue;
    YYLTYPE yylocation;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvalue;
  (void) yylocation;

  switch (yytype)
    {
      default:
        break;
    }
}



/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
#  define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL
# else
#  define YYPARSE_PARAM_ARG YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
# endif
#else /* !YYPARSE_PARAM */
# define YYPARSE_PARAM_ARG
# define YYPARSE_PARAM_DECL
#endif /* !YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
# ifdef YYPARSE_PARAM
int yyparse (void *);
# else
int yyparse (void);
# endif
#endif


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of parse errors so far.  */
int yynerrs;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;


int
yyparse (YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yychar1 = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
	YYSTACK_RELOCATE (yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with.  */

  if (yychar <= 0)		/* This means end of input.  */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more.  */

      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yychar1 = YYTRANSLATE (yychar);

      /* We have to keep this `#if YYDEBUG', since we use variables
	 which are defined only if `YYDEBUG' is set.  */
      YYDPRINTF ((stderr, "Next token is "));
      YYDSYMPRINT ((stderr, yychar1, yylval, yyloc));
      YYDPRINTF ((stderr, "\n"));
    }

  /* If the proper action on seeing token YYCHAR1 is to reduce or to
     detect an error, take that action.  */
  yyn += yychar1;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yychar1)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %d (%s), ",
	      yychar, yytname[yychar1]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
  *++yylsp = yylloc;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);

#if YYDEBUG
  /* We have to keep this `#if YYDEBUG', since we use variables which
     are defined only if `YYDEBUG' is set.  */
  if (yydebug)
    {
      int yyi;

      YYFPRINTF (stderr, "Reducing via rule %d (line %d), ",
		 yyn - 1, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (yyi = yyprhs[yyn]; yyrhs[yyi] >= 0; yyi++)
	YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
      YYFPRINTF (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif
  switch (yyn)
    {
        case 2:
#line 278 "parser.yy"
    { CALL(yylsp[0], yylsp[0], done()); }
    break;

  case 3:
#line 279 "parser.yy"
    { }
    break;

  case 4:
#line 280 "parser.yy"
    { }
    break;

  case 5:
#line 281 "parser.yy"
    { }
    break;

  case 6:
#line 282 "parser.yy"
    { }
    break;

  case 7:
#line 283 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SYSTEM));
	}
    break;

  case 8:
#line 286 "parser.yy"
    { g_parameter_count = yyvsp[0].number; }
    break;

  case 9:
#line 287 "parser.yy"
    { }
    break;

  case 10:
#line 288 "parser.yy"
    { CALL(yylsp[0], yylsp[0], procGuard()); }
    break;

  case 11:
#line 289 "parser.yy"
    { }
    break;

  case 12:
#line 290 "parser.yy"
    { CALL(yylsp[0], yylsp[0], procUpdate()); }
    break;

  case 13:
#line 291 "parser.yy"
    { CALL(yylsp[0], yylsp[0], done()); }
    break;

  case 14:
#line 292 "parser.yy"
    { }
    break;

  case 15:
#line 293 "parser.yy"
    { }
    break;

  case 16:
#line 294 "parser.yy"
    { }
    break;

  case 17:
#line 295 "parser.yy"
    { g_parameter_count = yyvsp[0].number; }
    break;

  case 18:
#line 296 "parser.yy"
    { }
    break;

  case 19:
#line 297 "parser.yy"
    { CALL(yylsp[0], yylsp[0], procGuard()); }
    break;

  case 20:
#line 298 "parser.yy"
    { CALL(yylsp[0], yylsp[0], procUpdate()); }
    break;

  case 21:
#line 299 "parser.yy"
    {}
    break;

  case 24:
#line 308 "parser.yy"
    {
          CALL(yylsp[-3], yylsp[-1], instantiationBegin(yyvsp[-3].string, yyvsp[-1].string));
	}
    break;

  case 25:
#line 310 "parser.yy"
    { 
	  CALL(yylsp[-7], yylsp[0], instantiationEnd(yyvsp[-7].string, yyvsp[-5].string, yyvsp[-2].number));
	}
    break;

  case 26:
#line 313 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_ARGLIST));
	}
    break;

  case 27:
#line 316 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));
	}
    break;

  case 28:
#line 319 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LPAREN));
	}
    break;

  case 29:
#line 322 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_ASSIGN));
	}
    break;

  case 31:
#line 329 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 32:
#line 332 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_PROCID));
	}
    break;

  case 33:
#line 338 "parser.yy"
    { CALL(yylsp[0], yylsp[0], process(yyvsp[0].string)); }
    break;

  case 34:
#line 339 "parser.yy"
    { CALL(yylsp[0], yylsp[0], process(yyvsp[0].string)); }
    break;

  case 35:
#line 340 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_PROCID_));
	}
    break;

  case 41:
#line 354 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], declFuncBegin(yyvsp[-1].string, yyvsp[0].number));
	}
    break;

  case 42:
#line 357 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[-1], declFuncEnd());
	}
    break;

  case 43:
#line 363 "parser.yy"
    { yyval.number = 0; }
    break;

  case 44:
#line 364 "parser.yy"
    { yyval.number = yyvsp[-1].number; }
    break;

  case 45:
#line 365 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));
	  yyval.number = yyvsp[-2].number; 
	}
    break;

  case 46:
#line 369 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));
	  yyval.number = yyvsp[-1].number; 
	}
    break;

  case 47:
#line 373 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_PARAMETERS));
	  yyval.number = 0; 
	}
    break;

  case 48:
#line 377 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));
	  yyval.number = 0; 
	}
    break;

  case 49:
#line 389 "parser.yy"
    { yyval.number = 1; }
    break;

  case 50:
#line 390 "parser.yy"
    { yyval.number = yyvsp[-2].number+1; }
    break;

  case 51:
#line 391 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_PARAMETERS_));
	  yyval.number = yyvsp[-2].number;
	}
    break;

  case 52:
#line 398 "parser.yy"
    {
          CALL(yylsp[-3], yylsp[0], declParameter(yyvsp[-1].string, true, yyvsp[0].number));
          CALL(yylsp[-3], yylsp[0], declParameterEnd());
	}
    break;

  case 53:
#line 402 "parser.yy"
    {
          CALL(yylsp[-2], yylsp[0], declParameter(yyvsp[-1].string, false, yyvsp[0].number));
          CALL(yylsp[-2], yylsp[0], declParameterEnd());
	}
    break;

  case 54:
#line 406 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_PARAMID));
	}
    break;

  case 55:
#line 412 "parser.yy"
    { 
          CALL(yylsp[-2], yylsp[0], declVarEnd());
	}
    break;

  case 56:
#line 415 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
          CALL(yylsp[-3], yylsp[0], declVarEnd());
	}
    break;

  case 57:
#line 419 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_VARID));
	  CALL(yylsp[-2], yylsp[0], declVarEnd());
	}
    break;

  case 60:
#line 428 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_VARID_));
	}
    break;

  case 61:
#line 434 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], declVar(yyvsp[-2].string, yyvsp[-1].number, yyvsp[0].flag));
	}
    break;

  case 62:
#line 440 "parser.yy"
    { yyval.flag = false; }
    break;

  case 63:
#line 441 "parser.yy"
    { yyval.flag = true; }
    break;

  case 64:
#line 442 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_INITIAL));
	  yyval.flag = false; 
	}
    break;

  case 66:
#line 450 "parser.yy"
    {	
	  CALL(yylsp[-2], yylsp[0], declInitialiserList(yyvsp[-1].number));
	}
    break;

  case 67:
#line 453 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  CALL(yylsp[-3], yylsp[0], declInitialiserList(yyvsp[-2].number));
	}
    break;

  case 68:
#line 457 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_INITIAL));
	  CALL(yylsp[-2], yylsp[0], declInitialiserList(0));
	}
    break;

  case 69:
#line 464 "parser.yy"
    { yyval.number = 1; }
    break;

  case 70:
#line 465 "parser.yy"
    { yyval.number = yyvsp[-2].number+1; }
    break;

  case 71:
#line 466 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_INITIAL_));
	  yyval.number = yyvsp[-2].number+1; 
	}
    break;

  case 72:
#line 473 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], declFieldInit(yyvsp[-2].string));
	}
    break;

  case 73:
#line 476 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_INITIAL));
	}
    break;

  case 74:
#line 479 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], declFieldInit(NULL));
	}
    break;

  case 75:
#line 485 "parser.yy"
    { yyval.number=0; }
    break;

  case 76:
#line 486 "parser.yy"
    { yyval.number=yyvsp[-3].number+1; }
    break;

  case 77:
#line 487 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RSQBRACE));
	  yyval.number=yyvsp[-4].number+1; 
	}
    break;

  case 78:
#line 491 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RSQBRACE));
	  yyval.number=yyvsp[-3].number+1; 
	}
    break;

  case 79:
#line 495 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_CONST_EXP));
	  yyval.number=yyvsp[-3].number+1; 
	}
    break;

  case 80:
#line 499 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_CONST_EXP));
	  yyval.number=yyvsp[-2].number+1; 
	}
    break;

  case 81:
#line 506 "parser.yy"
    {
	  CALL(yylsp[-3], yylsp[0], declTypeDefEnd());
	}
    break;

  case 82:
#line 509 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-4], yylsp[0], declTypeDefEnd());
	}
    break;

  case 83:
#line 513 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_TYPEID));
	  CALL(yylsp[-3], yylsp[0], declTypeDefEnd());  
	}
    break;

  case 84:
#line 517 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_TYPE_DEF));
	  CALL(yylsp[-2], yylsp[0], declTypeDefEnd());  
	}
    break;

  case 85:
#line 529 "parser.yy"
    { yyval.number = 1; }
    break;

  case 86:
#line 530 "parser.yy"
    { yyval.number = yyvsp[-2].number+1; }
    break;

  case 87:
#line 531 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_TYPEID_));
	  yyval.number = yyvsp[-2].number+1; 
	}
    break;

  case 88:
#line 538 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], declTypeDef(yyvsp[-1].string, yyvsp[0].number));
	}
    break;

  case 89:
#line 544 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], declType(yyvsp[-2].number, yyvsp[-1].string, yyvsp[0].flag));
	}
    break;

  case 90:
#line 547 "parser.yy"
    { 
	  CALL(yylsp[-4], yylsp[0], declStruct(yyvsp[-4].number, yyvsp[-1].number));
	}
    break;

  case 91:
#line 550 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBER));
	  CALL(yylsp[-4], yylsp[0], declStruct(yyvsp[-4].number, 0));
	}
    break;

  case 92:
#line 554 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  CALL(yylsp[-3], yylsp[0], declStruct(yyvsp[-3].number, 0));
	}
    break;

  case 93:
#line 558 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	}
    break;

  case 94:
#line 564 "parser.yy"
    { strncpy(yyval.string, yyvsp[0].string, MAXLEN); }
    break;

  case 95:
#line 565 "parser.yy"
    { strncpy(yyval.string, yyvsp[0].string, MAXLEN); }
    break;

  case 96:
#line 569 "parser.yy"
    { yyval.number=yyvsp[0].number; }
    break;

  case 97:
#line 570 "parser.yy"
    { yyval.number=yyvsp[-1].number+yyvsp[0].number; }
    break;

  case 98:
#line 571 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBER));
	  yyval.number=yyvsp[-1].number; 
	}
    break;

  case 99:
#line 578 "parser.yy"
    {
	  yyval.number = yyvsp[-1].number; 
	  CALL(yylsp[-2], yylsp[0], declFieldEnd());
	}
    break;

  case 100:
#line 582 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));	  
	  yyval.number = yyvsp[-2].number; 
	  CALL(yylsp[-3], yylsp[0], declFieldEnd());
	}
    break;

  case 101:
#line 587 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBERID));	  
	}
    break;

  case 102:
#line 590 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBERID));	  
	}
    break;

  case 103:
#line 593 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBERTYPE));	  
	}
    break;

  case 104:
#line 599 "parser.yy"
    { yyval.number=1; }
    break;

  case 105:
#line 600 "parser.yy"
    { yyval.number=yyvsp[-2].number+1; }
    break;

  case 106:
#line 601 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBERID_));
	  yyval.number=yyvsp[-2].number+1; 
	}
    break;

  case 107:
#line 608 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], declField(yyvsp[-1].string, yyvsp[0].number));
	}
    break;

  case 108:
#line 614 "parser.yy"
    { yyval.number = ParserBuilder::PREFIX_NONE; }
    break;

  case 109:
#line 615 "parser.yy"
    { yyval.number = ParserBuilder::PREFIX_URGENT; }
    break;

  case 110:
#line 616 "parser.yy"
    { yyval.number = ParserBuilder::PREFIX_BROADCAST; }
    break;

  case 111:
#line 617 "parser.yy"
    { yyval.number = ParserBuilder::PREFIX_URGENT_BROADCAST; }
    break;

  case 112:
#line 618 "parser.yy"
    { yyval.number = ParserBuilder::PREFIX_CONST; }
    break;

  case 113:
#line 622 "parser.yy"
    { yyval.flag = false; }
    break;

  case 114:
#line 623 "parser.yy"
    { yyval.flag = true; }
    break;

  case 115:
#line 624 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RSQBRACE));
	  yyval.flag = true; 
	}
    break;

  case 116:
#line 628 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RSQBRACE));
	  yyval.flag = true; 
	}
    break;

  case 117:
#line 632 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_CONST_EXP));
	  yyval.flag = true;
	  CALL(yylsp[-4], yylsp[0], exprTrue());
	}
    break;

  case 118:
#line 637 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_CONST_EXP));
	  yyval.flag = true;
	  CALL(yylsp[-4], yylsp[0], exprTrue());
	}
    break;

  case 119:
#line 642 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_CONST_EXP));
	  yyval.flag = true;
	  CALL(yylsp[-2], yylsp[0], exprTrue());
	}
    break;

  case 120:
#line 647 "parser.yy"
    {
	    REPORT_ERROR(last_loc, TypeException(PE_CONST_EXP));
	    yyval.flag = true;
	    CALL(yylsp[-2], yylsp[-1], exprTrue());
	  }
    break;

  case 121:
#line 652 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_COMMA)); 
	  yyclearin; yyerrok;
	}
    break;

  case 122:
#line 656 "parser.yy"
    {
	    yyval.flag = true;
	  }
    break;

  case 123:
#line 659 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_COMMA)); 
	  yyclearin; yyerrok;
	  yyval.flag = true;
	  CALL(yylsp[-3], yylsp[0], exprTrue());
	}
    break;

  case 124:
#line 665 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_COMMA)); 
	  yyclearin; yyerrok;
	  yyval.flag = true;
	  CALL(yylsp[-2], yylsp[0], exprTrue());
	}
    break;

  case 125:
#line 671 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_CONST_EXP)); 
	  yyclearin; yyerrok;
	  yyval.flag = true;
	  CALL(yylsp[-1], yylsp[0], exprTrue());
	}
    break;

  case 126:
#line 684 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[0], procBegin(yyvsp[-2].string, yyvsp[-1].number));
	}
    break;

  case 127:
#line 687 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], procEnd());
	}
    break;

  case 128:
#line 690 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	}
    break;

  case 129:
#line 693 "parser.yy"
    {
	  utap_error(TypeException(PE_LPAREN), 
		     yylsp[0].first_line, yylsp[0].first_column, 
		     yylsp[0].last_line, yylsp[0].last_column);
	  CALL(yylsp[-2], yylsp[0], procBegin(yyvsp[-1].string, 0));
	}
    break;

  case 130:
#line 698 "parser.yy"
    {
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;

  case 131:
#line 701 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_PROCID));	  
	}
    break;

  case 138:
#line 723 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 139:
#line 726 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 140:
#line 729 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATE_DECL));
	}
    break;

  case 141:
#line 732 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATE_DECL));
	}
    break;

  case 142:
#line 735 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATE));
	}
    break;

  case 145:
#line 743 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATE_DECL_));
	}
    break;

  case 146:
#line 749 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], exprTrue());
	  CALL(yylsp[0], yylsp[0], procState(yyvsp[0].string));
	}
    break;

  case 147:
#line 753 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[0], procState(yyvsp[-3].string));
	}
    break;

  case 148:
#line 756 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	  CALL(yylsp[-4], yylsp[0], procState(yyvsp[-4].string));
	}
    break;

  case 149:
#line 760 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	  CALL(yylsp[-3], yylsp[0], procState(yyvsp[-3].string));
	}
    break;

  case 150:
#line 764 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_INV));
	  CALL(yylsp[-3], yylsp[0], procState(yyvsp[-3].string));
	}
    break;

  case 151:
#line 768 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_INV));
	  CALL(yylsp[-2], yylsp[0], procState(yyvsp[-2].string));
	}
    break;

  case 152:
#line 775 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], procStateInit(yyvsp[-1].string));
	}
    break;

  case 153:
#line 778 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-3], yylsp[0], procStateInit(yyvsp[-2].string));
	}
    break;

  case 154:
#line 782 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-2], yylsp[0], procStateInit(yyvsp[-1].string));
	}
    break;

  case 155:
#line 786 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;

  case 156:
#line 789 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_INIT));
	}
    break;

  case 159:
#line 797 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 160:
#line 800 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 161:
#line 803 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS_DECL));
	}
    break;

  case 162:
#line 806 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS));
	}
    break;

  case 165:
#line 814 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS_DECL_));
	}
    break;

  case 166:
#line 820 "parser.yy"
    { 
	  strcpy(rootTransId, yyvsp[-7].string); 
	  CALL(yylsp[-7], yylsp[0], procTransition(yyvsp[-7].string, yyvsp[-5].string));
	}
    break;

  case 167:
#line 824 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  strcpy(rootTransId, yyvsp[-8].string); 
	  CALL(yylsp[-8], yylsp[0], procTransition(yyvsp[-8].string, yyvsp[-6].string));
	}
    break;

  case 168:
#line 829 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	}
    break;

  case 169:
#line 832 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;

  case 170:
#line 835 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_ARROW));
	}
    break;

  case 171:
#line 841 "parser.yy"
    { 
	  CALL(yylsp[-6], yylsp[0], procTransition(rootTransId, yyvsp[-5].string));
	}
    break;

  case 172:
#line 844 "parser.yy"
    { 
	  REPORT_ERROR(yylloc, TypeException(PE_RBRACE));
	  CALL(yylsp[-7], yylsp[0], procTransition(rootTransId, yyvsp[-6].string));
	}
    break;

  case 173:
#line 848 "parser.yy"
    { 
	  REPORT_ERROR(yylloc, TypeException(PE_LBRACE));
	}
    break;

  case 174:
#line 851 "parser.yy"
    { 
	  REPORT_ERROR(yylloc, TypeException(PE_STATEID));
	}
    break;

  case 177:
#line 860 "parser.yy"
    {
	  CALL(yyloc, yyloc, procGuard());
        }
    break;

  case 178:
#line 863 "parser.yy"
    {
	  REPORT_ERROR(yylloc, TypeException(PE_SEMICOLON));
	  CALL(yyloc, yyloc, procGuard());
	}
    break;

  case 179:
#line 867 "parser.yy"
    {
	  REPORT_ERROR(yylloc, TypeException(PE_GUARD_EXP));
	}
    break;

  case 182:
#line 875 "parser.yy"
    {
	  REPORT_ERROR(yylloc, TypeException(PE_SEMICOLON));
	}
    break;

  case 183:
#line 878 "parser.yy"
    {
	  REPORT_ERROR(yylloc, TypeException(PE_SEMICOLON));
	}
    break;

  case 184:
#line 881 "parser.yy"
    {
	  REPORT_ERROR(yylloc, TypeException(PE_SYNC_EXP));
	}
    break;

  case 185:
#line 887 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], procSync(SYNC_BANG));
	}
    break;

  case 186:
#line 890 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_BANG));
	  CALL(yylsp[-2], yylsp[-1], procSync(SYNC_QUE));
	}
    break;

  case 187:
#line 894 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], procSync(SYNC_QUE));
	}
    break;

  case 188:
#line 897 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_QUE));
	  CALL(yylsp[-2], yylsp[-1], procSync(SYNC_QUE));
	}
    break;

  case 189:
#line 901 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_BANGQUE));
	  CALL(yylsp[-1], yylsp[0], procSync(SYNC_QUE));
	}
    break;

  case 191:
#line 909 "parser.yy"
    {
	  CALL(yyloc, yyloc, procUpdate());	  
	}
    break;

  case 192:
#line 912 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_ASSIGN_EXP));
	}
    break;

  case 198:
#line 926 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 199:
#line 929 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 200:
#line 932 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;

  case 201:
#line 935 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;

  case 202:
#line 941 "parser.yy"
    {}
    break;

  case 203:
#line 942 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 204:
#line 945 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 205:
#line 948 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;

  case 206:
#line 951 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;

  case 207:
#line 957 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], procStateCommit(yyvsp[0].string));
	}
    break;

  case 208:
#line 960 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], procStateCommit(yyvsp[0].string));
	}
    break;

  case 209:
#line 963 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID_));
	}
    break;

  case 210:
#line 969 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], procStateUrgent(yyvsp[0].string));
	}
    break;

  case 211:
#line 972 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], procStateUrgent(yyvsp[0].string));
	}
    break;

  case 212:
#line 975 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID_));
	}
    break;

  case 213:
#line 986 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], blockBegin());
	}
    break;

  case 214:
#line 989 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[-1], blockEnd());
	}
    break;

  case 215:
#line 992 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], blockBegin());
	}
    break;

  case 216:
#line 995 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_DECL_STAT));
	  CALL(yylsp[-2], yylsp[-1], blockEnd());
	}
    break;

  case 223:
#line 1014 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], emptyStatement());
	}
    break;

  case 224:
#line 1017 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], exprStatement());
	}
    break;

  case 225:
#line 1020 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-2], yylsp[0], exprStatement());
	}
    break;

  case 226:
#line 1024 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], forBegin());
	}
    break;

  case 227:
#line 1027 "parser.yy"
    { 
	    CALL(yylsp[-7], yylsp[-1], forEnd());
	  }
    break;

  case 228:
#line 1030 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], forBegin());
	}
    break;

  case 229:
#line 1035 "parser.yy"
    { 
	    CALL(yylsp[-7], yylsp[-10], forEnd());
	  }
    break;

  case 230:
#line 1038 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LPAREN));
	  CALL(yylsp[-2], yylsp[0], forBegin());
	}
    break;

  case 231:
#line 1043 "parser.yy"
    { 
	    CALL(yylsp[-7], yylsp[-10], forEnd());
	  }
    break;

  case 232:
#line 1046 "parser.yy"
    {
	    CALL(yylsp[-1], yylsp[0], whileBegin());
	}
    break;

  case 233:
#line 1049 "parser.yy"
    { 
	    CALL(yylsp[-3], yylsp[-2], whileEnd());
	  }
    break;

  case 234:
#line 1052 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));
	  CALL(yylsp[-2], yylsp[0], whileBegin());
	}
    break;

  case 235:
#line 1056 "parser.yy"
    { 
	    CALL(yylsp[-3], yylsp[-1], whileEnd());
	  }
    break;

  case 236:
#line 1059 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], whileBegin());
	}
    break;

  case 237:
#line 1063 "parser.yy"
    { 
	    CALL(yylsp[-6], yylsp[-4], whileEnd());
	  }
    break;

  case 238:
#line 1066 "parser.yy"
    { 
	    CALL(yylsp[0], yylsp[0], doWhileBegin());
	}
    break;

  case 239:
#line 1069 "parser.yy"
    { 
	    CALL(yylsp[-6], yylsp[-1], doWhileEnd());
	  }
    break;

  case 240:
#line 1072 "parser.yy"
    { 
	    CALL(yylsp[-1], yylsp[0], ifBegin());
	}
    break;

  case 242:
#line 1076 "parser.yy"
    { 
	    CALL(yylsp[-1], yylsp[0], breakStatement());
	  }
    break;

  case 243:
#line 1079 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-2], yylsp[0], breakStatement());
	}
    break;

  case 244:
#line 1083 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], continueStatement());
	}
    break;

  case 245:
#line 1086 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-2], yylsp[0], continueStatement());
	}
    break;

  case 246:
#line 1090 "parser.yy"
    { 
	    CALL(yylsp[-3], yylsp[0], switchBegin());
	}
    break;

  case 247:
#line 1093 "parser.yy"
    { 
	       CALL(yylsp[-3], yylsp[-1], switchEnd());
	   }
    break;

  case 248:
#line 1096 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));
	  CALL(yylsp[-4], yylsp[0], switchBegin());
	}
    break;

  case 249:
#line 1100 "parser.yy"
    { 
	    CALL(yylsp[-3], yylsp[-1], switchEnd());
	  }
    break;

  case 250:
#line 1103 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-4], yylsp[0], switchBegin());
	}
    break;

  case 251:
#line 1107 "parser.yy"
    { 
	    CALL(yylsp[-3], yylsp[-1], switchEnd());
	  }
    break;

  case 252:
#line 1110 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], returnStatement(true));
	}
    break;

  case 253:
#line 1113 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-2], yylsp[0], returnStatement(true));
	}
    break;

  case 254:
#line 1117 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], returnStatement(false));
	}
    break;

  case 255:
#line 1120 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR_SEMI));
	  CALL(yylsp[-1], yylsp[0], returnStatement(false));
	}
    break;

  case 256:
#line 1127 "parser.yy"
    { 
	  CALL(yyloc, yyloc, ifEnd(false));
	}
    break;

  case 257:
#line 1130 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], ifElse());
	}
    break;

  case 258:
#line 1133 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[-1], ifEnd(true));
	  }
    break;

  case 259:
#line 1136 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], ifElse());
	}
    break;

  case 260:
#line 1139 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-1], yylsp[-1], ifEnd(true));
	  }
    break;

  case 263:
#line 1151 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], caseBegin());
	}
    break;

  case 264:
#line 1154 "parser.yy"
    { 
	    CALL(yylsp[-1], yylsp[-1], caseEnd());
	  }
    break;

  case 265:
#line 1157 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], caseBegin());
	}
    break;

  case 266:
#line 1160 "parser.yy"
    {
	    REPORT_ERROR(last_loc, TypeException(PE_EXPR)); 
	    CALL(yylsp[-1], yylsp[-1], caseEnd());
	  }
    break;

  case 267:
#line 1164 "parser.yy"
    { 
	    CALL(yylsp[-1], yylsp[0], defaultBegin());
	}
    break;

  case 268:
#line 1167 "parser.yy"
    { 
	    CALL(yylsp[-1], yylsp[-1], defaultEnd());
	  }
    break;

  case 269:
#line 1170 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_COLON)); 
	  CALL(yylsp[-2], yylsp[0], defaultBegin());
	}
    break;

  case 270:
#line 1174 "parser.yy"
    { 
	    CALL(yylsp[-1], yylsp[-1], defaultEnd());
	  }
    break;

  case 274:
#line 1186 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprComma());
	}
    break;

  case 275:
#line 1189 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR_));
	}
    break;

  case 276:
#line 1195 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], exprFalse());
	}
    break;

  case 277:
#line 1198 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], exprTrue());
	}
    break;

  case 278:
#line 1201 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], exprNat(yyvsp[0].number));
	}
    break;

  case 279:
#line 1204 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], exprId(yyvsp[0].string));
	}
    break;

  case 280:
#line 1207 "parser.yy"
    {
	    CALL(yylsp[-1], yylsp[0], exprCallBegin(yyvsp[-1].string));	    
	  }
    break;

  case 281:
#line 1209 "parser.yy"
    { 
	    CALL(yylsp[-4], yylsp[0], exprCallEnd(yyvsp[-1].number));
	}
    break;

  case 282:
#line 1212 "parser.yy"
    {
	    CALL(yylsp[-1], yylsp[0], exprCallBegin(yyvsp[-1].string));
	  }
    break;

  case 283:
#line 1214 "parser.yy"
    {   
	    REPORT_ERROR(last_loc, TypeException(PE_ARGLIST));
	    CALL(yylsp[-4], yylsp[0], exprCallEnd(0));
	}
    break;

  case 284:
#line 1218 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[0], exprArray());
	}
    break;

  case 285:
#line 1221 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-3], yylsp[0], exprArray());
	}
    break;

  case 287:
#line 1226 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	}
    break;

  case 288:
#line 1229 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], exprPostIncrement());
	}
    break;

  case 289:
#line 1232 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], exprPreIncrement());
	}
    break;

  case 290:
#line 1235 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], exprPostDecrement());
	}
    break;

  case 291:
#line 1238 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], exprPreDecrement());
	}
    break;

  case 292:
#line 1241 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprAssignment(yyvsp[-1].number));
	}
    break;

  case 293:
#line 1244 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprAssignment(yyvsp[-1].number));
	}
    break;

  case 294:
#line 1248 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], exprUnary(yyvsp[-1].number));
	}
    break;

  case 295:
#line 1251 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(LT));
	}
    break;

  case 296:
#line 1254 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprBinary(LT));
	}
    break;

  case 297:
#line 1258 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(LE));
	}
    break;

  case 298:
#line 1261 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprBinary(LE));
	}
    break;

  case 299:
#line 1265 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(EQ));
	}
    break;

  case 300:
#line 1268 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprBinary(EQ));
	}
    break;

  case 301:
#line 1272 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(NEQ));
	}
    break;

  case 302:
#line 1275 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprBinary(NEQ));
	}
    break;

  case 303:
#line 1279 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(GT));
	}
    break;

  case 304:
#line 1282 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprBinary(GT));
	}
    break;

  case 305:
#line 1286 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(GE));
	}
    break;

  case 306:
#line 1289 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprTrue(); ch->exprBinary(GE));
	}
    break;

  case 307:
#line 1293 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(PLUS));
	}
    break;

  case 308:
#line 1296 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprTrue(); ch->exprBinary(PLUS));
	}
    break;

  case 309:
#line 1300 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(MINUS));
	}
    break;

  case 310:
#line 1303 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprTrue(); ch->exprBinary(MINUS));
	}
    break;

  case 311:
#line 1307 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(MULT));
	}
    break;

  case 312:
#line 1310 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprTrue(); ch->exprBinary(MULT));
	}
    break;

  case 313:
#line 1314 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(DIV));
	}
    break;

  case 314:
#line 1317 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprTrue(); ch->exprBinary(DIV));
	}
    break;

  case 315:
#line 1321 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(MOD));
	}
    break;

  case 316:
#line 1324 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprTrue(); ch->exprBinary(MOD));
	}
    break;

  case 317:
#line 1328 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_AND));
	}
    break;

  case 318:
#line 1331 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprTrue(); ch->exprBinary(BIT_AND));
	}
    break;

  case 319:
#line 1335 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_OR));
	}
    break;

  case 320:
#line 1338 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprTrue(); ch->exprBinary(BIT_OR));
	}
    break;

  case 321:
#line 1342 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_XOR));
	}
    break;

  case 322:
#line 1345 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprTrue(); ch->exprBinary(BIT_XOR));
	}
    break;

  case 323:
#line 1349 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_LSHIFT));
	}
    break;

  case 324:
#line 1352 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprTrue(); ch->exprBinary(BIT_LSHIFT));
	}
    break;

  case 325:
#line 1356 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_RSHIFT));
	}
    break;

  case 326:
#line 1359 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprTrue(); ch->exprBinary(BIT_RSHIFT));
	}
    break;

  case 327:
#line 1363 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(AND));
	}
    break;

  case 328:
#line 1366 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprTrue(); ch->exprBinary(AND));
	}
    break;

  case 329:
#line 1370 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(OR));
	}
    break;

  case 330:
#line 1373 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprTrue(); ch->exprBinary(OR));
	}
    break;

  case 331:
#line 1377 "parser.yy"
    { 
	  CALL(yylsp[-4], yylsp[-2], exprInlineIf());
	}
    break;

  case 332:
#line 1380 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-4], yylsp[-2], exprTrue(); ch->exprInlineIf());
	}
    break;

  case 333:
#line 1384 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_COLON));
	  CALL(yylsp[-3], yylsp[0], exprTrue(); ch->exprInlineIf());
	}
    break;

  case 334:
#line 1388 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprDot(yyvsp[0].string));
	}
    break;

  case 335:
#line 1391 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBERID));
	}
    break;

  case 336:
#line 1394 "parser.yy"
    {
	  CALL(yyloc, yyloc, exprDeadlock());
	}
    break;

  case 337:
#line 1397 "parser.yy"
    {  
	  CALL(yylsp[-1], yylsp[-1], exprUnary(NOT));
	}
    break;

  case 338:
#line 1399 "parser.yy"
    {
	  CALL(yylsp[-1], yylsp[-1], exprBinary(OR));
	}
    break;

  case 339:
#line 1407 "parser.yy"
    { yyval.number = ASSIGN; }
    break;

  case 340:
#line 1408 "parser.yy"
    { yyval.number = ASSPLUS; }
    break;

  case 341:
#line 1409 "parser.yy"
    { yyval.number = ASSMINUS; }
    break;

  case 342:
#line 1410 "parser.yy"
    { yyval.number = ASSDIV; }
    break;

  case 343:
#line 1411 "parser.yy"
    { yyval.number = ASSMOD; }
    break;

  case 344:
#line 1412 "parser.yy"
    { yyval.number = ASSMULT; }
    break;

  case 345:
#line 1413 "parser.yy"
    { yyval.number = ASSAND; }
    break;

  case 346:
#line 1414 "parser.yy"
    { yyval.number = ASSOR; }
    break;

  case 347:
#line 1415 "parser.yy"
    { yyval.number = ASSXOR; }
    break;

  case 348:
#line 1416 "parser.yy"
    { yyval.number = ASSLSHIFT; }
    break;

  case 349:
#line 1417 "parser.yy"
    { yyval.number = ASSRSHIFT; }
    break;

  case 350:
#line 1422 "parser.yy"
    { yyval.number = MINUS; }
    break;

  case 351:
#line 1423 "parser.yy"
    { yyval.number = NOT; }
    break;

  case 352:
#line 1424 "parser.yy"
    { yyval.number = NOT; }
    break;

  case 353:
#line 1429 "parser.yy"
    { yyval.number=0; }
    break;

  case 354:
#line 1430 "parser.yy"
    { 
	    yyval.number=1; 
	    CALL(yylsp[0], yylsp[0], exprArg(yyval.number));
	}
    break;

  case 355:
#line 1434 "parser.yy"
    { 
	    yyval.number=yyvsp[-2].number+1; 
	    CALL(yylsp[0], yylsp[0], exprArg(yyval.number));
	}
    break;

  case 356:
#line 1438 "parser.yy"
    { 
	  yyval.number=yyvsp[-2].number+1; 
	  REPORT_ERROR(last_loc, TypeException(PE_ARGLIST_));
	  CALL(yylsp[0], yylsp[0], exprArg(yyval.number));
	}
    break;

  case 359:
#line 1454 "parser.yy"
    {
	  CALL(yylsp[-3], yylsp[-1], instantiationBegin(yyvsp[-3].string, yyvsp[-1].string));
        }
    break;

  case 360:
#line 1456 "parser.yy"
    {
	  CALL(yylsp[-7], yylsp[0], instantiationEnd(yyvsp[-7].string, yyvsp[-5].string, yyvsp[-2].number));	    
	}
    break;

  case 361:
#line 1459 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_ARGLIST));
	}
    break;

  case 362:
#line 1462 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));
	}
    break;

  case 363:
#line 1465 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LPAREN));
	}
    break;

  case 364:
#line 1468 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_ASSIGNOLD));
	}
    break;

  case 368:
#line 1481 "parser.yy"
    {
	  CALL(yylsp[-2], yylsp[0], declVarEnd());
	}
    break;

  case 369:
#line 1484 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  yyclearin; yyerrok;
	  CALL(yylsp[-3], yylsp[0], declVarEnd());
	}
    break;

  case 370:
#line 1489 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_VARID));
	  yyclearin; yyerrok;
	  CALL(yylsp[-2], yylsp[0], declVarEnd());
	}
    break;

  case 371:
#line 1494 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_VAR_DECL));
	  yyclearin; yyerrok;
	}
    break;

  case 372:
#line 1498 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], declType(ParserBuilder::PREFIX_CONST, "int", 0));
	}
    break;

  case 373:
#line 1501 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[-1], declVarEnd());
	}
    break;

  case 374:
#line 1504 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_CONSTID));
	}
    break;

  case 375:
#line 1510 "parser.yy"
    { yyval.number=1; }
    break;

  case 376:
#line 1511 "parser.yy"
    { yyval.number=yyvsp[-2].number+1; }
    break;

  case 377:
#line 1512 "parser.yy"
    { 
	  yyval.number=yyvsp[-2].number+1; 
	  REPORT_ERROR(last_loc, TypeException(PE_ID_))
	}
    break;

  case 378:
#line 1519 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], declVar(yyvsp[0].string, 0, false));
	}
    break;

  case 379:
#line 1522 "parser.yy"
    {
	  CALL(yylsp[-3], yylsp[0], declVar(yyvsp[-3].string, 1, false));
	}
    break;

  case 380:
#line 1525 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_RSQBRACE));
	  CALL(yylsp[-3], yylsp[0], declVar(yyvsp[-3].string, 1, false));
	}
    break;

  case 381:
#line 1529 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-3], yylsp[0], declVar(yyvsp[-3].string, 1, false));
	}
    break;

  case 382:
#line 1533 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], declVar(yyvsp[-2].string, 0, true));
	}
    break;

  case 383:
#line 1536 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  yyclearin; yyerrok;
	  CALL(yylsp[-2], yylsp[0], declVar(yyvsp[-2].string, 0, true));
	}
    break;

  case 384:
#line 1544 "parser.yy"
    { yyval.number=1; }
    break;

  case 385:
#line 1545 "parser.yy"
    { yyval.number=yyvsp[-2].number+1; }
    break;

  case 386:
#line 1546 "parser.yy"
    { 
	  yyval.number=yyvsp[-2].number+1; 
	  REPORT_ERROR(last_loc, TypeException(PE_CONSTID_));
	}
    break;

  case 387:
#line 1553 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], declVar(yyvsp[-1].string, 0, true));
	}
    break;

  case 388:
#line 1556 "parser.yy"
    {
	  ch->exprTrue();
	  REPORT_ERROR(last_loc, TypeException(PE_CONST_EXP));	  
	  CALL(yylsp[-1], yylsp[0], declVar(yyvsp[-1].string, 0, true));
	}
    break;

  case 389:
#line 1564 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], declType(ParserBuilder::PREFIX_URGENT, yyvsp[0].string, false));
	}
    break;

  case 390:
#line 1567 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], declType(ParserBuilder::PREFIX_NONE, yyvsp[-1].string, yyvsp[0].flag));
	}
    break;

  case 391:
#line 1576 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[0], procBegin(yyvsp[-2].string, yyvsp[-1].number));
	}
    break;

  case 392:
#line 1579 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;

  case 393:
#line 1582 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	  CALL(yylsp[-4], yylsp[0], procBegin(yyvsp[-3].string, yyvsp[-2].number));
	}
    break;

  case 394:
#line 1586 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;

  case 395:
#line 1589 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACES));
	  CALL(yylsp[-3], yylsp[0], procBegin(yyvsp[-2].string, 0));
	}
    break;

  case 396:
#line 1593 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;

  case 397:
#line 1596 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_PROCID));
	  CALL(yylsp[-2], yylsp[0], procBegin("_", 0));
	}
    break;

  case 398:
#line 1600 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;

  case 399:
#line 1603 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_PROC));
	  CALL(yylsp[-1], yylsp[0], procBegin("_", 0));
	}
    break;

  case 400:
#line 1607 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;

  case 401:
#line 1610 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], procBegin(yyvsp[-1].string, 0));
	}
    break;

  case 402:
#line 1613 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;

  case 403:
#line 1619 "parser.yy"
    { yyval.number = 0; }
    break;

  case 404:
#line 1620 "parser.yy"
    { yyval.number = yyvsp[-1].number; }
    break;

  case 405:
#line 1621 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));	  
	  yyval.number = yyvsp[-1].number; 
	}
    break;

  case 406:
#line 1625 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_PARAMETERS));	  
	  yyval.number = 0; 
	}
    break;

  case 407:
#line 1632 "parser.yy"
    { 
	  yyval.number = 1; 
	  CALL(yylsp[0], yylsp[0], declParameterEnd());
	}
    break;

  case 408:
#line 1636 "parser.yy"
    { 
	  yyval.number = yyvsp[-2].number+1;
	  CALL(yylsp[-2], yylsp[0], declParameterEnd());
	}
    break;

  case 409:
#line 1640 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_PARAM_DECL_));
          yyval.number = yyvsp[-2].number+1; 
	  CALL(yylsp[-2], yylsp[0], declParameterEnd());
	}
    break;

  case 410:
#line 1648 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], declParameter(yyvsp[-1].string, true, yyvsp[0].number));
	}
    break;

  case 411:
#line 1651 "parser.yy"
    {
	  CALL(yylsp[-2], yylsp[-2], declType(ParserBuilder::PREFIX_CONST, "int", false));
	  CALL(yylsp[-1], yylsp[0], declParameter(yyvsp[-1].string, false, yyvsp[0].number));
	}
    break;

  case 412:
#line 1655 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_PARAMID));
	}
    break;

  case 413:
#line 1658 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[0], declParameter(yyvsp[-1].string, true, yyvsp[0].number));
	}
    break;

  case 414:
#line 1661 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_PARAMID));
	  CALL(yylsp[-2], yylsp[0], declParameter("_", true, 0));
	}
    break;

  case 419:
#line 1678 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 420:
#line 1681 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 421:
#line 1684 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATE_DECL));
	}
    break;

  case 422:
#line 1687 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATE_DECL));
	}
    break;

  case 423:
#line 1690 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATE));
	}
    break;

  case 426:
#line 1698 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_LOC_DECL));
	}
    break;

  case 427:
#line 1704 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], exprTrue(); ch->procState(yyvsp[0].string));
	}
    break;

  case 428:
#line 1707 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[0], procState(yyvsp[-3].string));
	}
    break;

  case 430:
#line 1714 "parser.yy"
    {	  
	  REPORT_ERROR(last_loc, TypeException(PE_INV));
	}
    break;

  case 431:
#line 1717 "parser.yy"
    {	  
	  REPORT_ERROR(last_loc, TypeException(PE_INV));
	  CALL(yylsp[0], yylsp[0], exprTrue());
	}
    break;

  case 432:
#line 1721 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(T_BOOL_AND));
	}
    break;

  case 433:
#line 1724 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_INV_));	  
	  CALL(yylsp[-2], yylsp[0], exprTrue(); ch->exprBinary(T_BOOL_AND));
	}
    break;

  case 436:
#line 1733 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 437:
#line 1736 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 438:
#line 1739 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS_DECL));
	}
    break;

  case 439:
#line 1742 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS_DECL));
	}
    break;

  case 440:
#line 1745 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS));
	}
    break;

  case 443:
#line 1753 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_ALT_TRANS));	  
	}
    break;

  case 444:
#line 1759 "parser.yy"
    { 
	  strcpy(rootTransId, yyvsp[-7].string);
	  CALL(yylsp[-7], yylsp[0], procTransition(yyvsp[-7].string, yyvsp[-5].string));
	}
    break;

  case 445:
#line 1763 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  strcpy(rootTransId, yyvsp[-8].string);
	  CALL(yylsp[-8], yylsp[0], procTransition(yyvsp[-8].string, yyvsp[-6].string));
	}
    break;

  case 446:
#line 1768 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  strcpy(rootTransId, yyvsp[-7].string); 
	  CALL(yylsp[-7], yylsp[0], procTransition(yyvsp[-7].string, yyvsp[-5].string));
	}
    break;

  case 447:
#line 1773 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	  strcpy(rootTransId, yyvsp[-8].string); 
	  CALL(yylsp[-8], yylsp[0], procTransition(yyvsp[-8].string, yyvsp[-6].string));
	}
    break;

  case 448:
#line 1778 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_ARROW));
	  strcpy(rootTransId, yyvsp[-8].string); 
	  CALL(yylsp[-8], yylsp[0], procTransition(yyvsp[-8].string, yyvsp[-5].string));
	}
    break;

  case 449:
#line 1787 "parser.yy"
    { 
	  CALL(yylsp[-6], yylsp[0], procTransition(rootTransId, yyvsp[-5].string));
	}
    break;

  case 450:
#line 1790 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  CALL(yylsp[-6], yylsp[0], procTransition(rootTransId, yyvsp[-5].string));
	}
    break;

  case 451:
#line 1794 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  CALL(yylsp[-7], yylsp[0], procTransition(rootTransId, yyvsp[-6].string));
	}
    break;

  case 452:
#line 1798 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	  CALL(yylsp[-7], yylsp[0], procTransition(rootTransId, yyvsp[-6].string));
	}
    break;

  case 453:
#line 1802 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	  CALL(yylsp[-7], yylsp[0], procTransition(rootTransId, yyvsp[-5].string));
	}
    break;

  case 454:
#line 1806 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	  CALL(yylsp[-6], yylsp[0], procTransition(rootTransId, "_"));
	}
    break;

  case 457:
#line 1815 "parser.yy"
    {
	  CALL(yyloc, yyloc, procGuard());
	}
    break;

  case 458:
#line 1818 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yyloc, yyloc, procGuard());
	}
    break;

  case 459:
#line 1822 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yyloc, yyloc, procGuard());
	}
    break;

  case 460:
#line 1826 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_GUARD_EXP));
	}
    break;

  case 462:
#line 1833 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(AND));
	}
    break;

  case 463:
#line 1836 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_GUARD_EXP_));
	  CALL(yylsp[-2], yylsp[0], exprBinary(AND));
	}
    break;

  case 465:
#line 1844 "parser.yy"
    {
	  CALL(yyloc, yyloc, procUpdate());
	}
    break;

  case 466:
#line 1847 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yyloc, yyloc, procUpdate());
	}
    break;

  case 467:
#line 1851 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yyloc, yyloc, procUpdate());
	}
    break;

  case 468:
#line 1855 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_ASSIGN_EXP));
	}
    break;

  case 469:
#line 1858 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_ASSIGN_EXP));
	}
    break;

  case 471:
#line 1865 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprComma());
	}
    break;

  case 472:
#line 1868 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_ASSIGN_EXP_));
	}
    break;

  case 473:
#line 1874 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprAssignment(ASSIGN));
	}
    break;

  case 474:
#line 1877 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprAssignment(ASSIGN));
	}
    break;

  case 475:
#line 1881 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_ASSIGNOLD));
	  CALL(yylsp[-2], yylsp[0], exprAssignment(ASSIGN));
	}
    break;

  case 476:
#line 1885 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_ASSIGNOLD));
	}
    break;

  case 481:
#line 1899 "parser.yy"
    {
		ch->quit();	
	}
    break;

  case 482:
#line 1902 "parser.yy"
    {
		ch->property(yyvsp[-1].number, yylsp[-1].first_line);
	}
    break;

  case 483:
#line 1905 "parser.yy"
    {
		ch->property(LEADSTO, yylsp[-2].first_line);
	}
    break;

  case 484:
#line 1910 "parser.yy"
    { yyval.number = EF; }
    break;

  case 485:
#line 1911 "parser.yy"
    { yyval.number = EG; }
    break;

  case 486:
#line 1912 "parser.yy"
    { yyval.number = AF; }
    break;

  case 487:
#line 1913 "parser.yy"
    { yyval.number = AG; }
    break;


    }

/* Line 1016 of /usr/share/bison/yacc.c.  */
#line 5568 "parser.tab.c"

  yyvsp -= yylen;
  yyssp -= yylen;
  yylsp -= yylen;

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("parse error, unexpected ") + 1;
	  yysize += yystrlen (yytname[yytype]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "parse error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("parse error");
    }
  goto yyerrlab1;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
yyerrlab1:
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        {
	  /* Pop the error token.  */
          YYPOPSTACK;
	  /* Pop the rest of the stack.  */
	  while (yyssp > yyss)
	    {
	      YYDPRINTF ((stderr, "Error: popping "));
	      YYDSYMPRINT ((stderr,
			    yystos[*yyssp],
			    *yyvsp, *yylsp));
	      YYDPRINTF ((stderr, "\n"));
	      yydestruct (yystos[*yyssp], *yyvsp, *yylsp);
	      YYPOPSTACK;
	    }
	  YYABORT;
        }

      YYDPRINTF ((stderr, "Discarding token %d (%s).\n",
		  yychar, yytname[yychar1]));
      yydestruct (yychar1, yylval, yylloc);
      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */

  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      YYDPRINTF ((stderr, "Error: popping "));
      YYDSYMPRINT ((stderr,
		    yystos[*yyssp], *yyvsp, *yylsp));
      YYDPRINTF ((stderr, "\n"));

      yydestruct (yystos[yystate], *yyvsp, *yylsp);
      yyvsp--;
      yystate = *--yyssp;
      yylsp--;

#if YYDEBUG
      if (yydebug)
	{
	  short *yyssp1 = yyss - 1;
	  YYFPRINTF (stderr, "Error: state stack now");
	  while (yyssp1 != yyssp)
	    YYFPRINTF (stderr, " %d", *++yyssp1);
	  YYFPRINTF (stderr, "\n");
	}
#endif
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;
  *++yylsp = yylloc;

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 1915 "parser.yy"


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

int32_t parseXTA(const char *str, ParserBuilder *aParserBuilder,
		 ErrorHandler *err, bool newxta)
{
  return parseXTA(str, aParserBuilder, err, newxta, S_XTA);
}

int32_t parseXTA(const char *str, ParserBuilder *aParserBuilder,
		 ErrorHandler *err, bool newxta, xta_part_t part)
{
  int res = 0;
  syntax = (newxta ? SYNTAX_NEW : SYNTAX_OLD);
  ch = aParserBuilder;
  ch->setErrorHandler(err);

  yylloc.reset();
  errorHandler = err;

  yy_scan_string(str);

  switch (part) { /* convertion from old to new */
  case S_XTA: 
    syntax_token = newxta ? T_NEW : T_OLD;
    if (utap_parse()) {
      res = -1;
    } else res = 0;
    break;
  case S_DECLARATION: 
    syntax_token = newxta ? T_NEW_DECLARATION : T_OLD_DECLARATION;
    if (utap_parse()) {
      res = -1;
    } else res = 0;
    break;
  case S_LOCAL_DECL: 
    syntax_token = newxta ? T_NEW_LOCAL_DECL : T_OLD_LOCAL_DECL; 
    if (utap_parse()) {
      res = -1;
    } else res = 0;
    break;
  case S_INST: 
    syntax_token = newxta ? T_NEW_INST : T_OLD_INST;
    if (utap_parse()) {
      res = -1;
    } else res = 0;
    break;
  case S_SYSTEM: 
    syntax_token = T_NEW_SYSTEM; // the system definition is the same for both
    if (utap_parse()) {
      res = -1;
    } else res = 0;
    break;
  case S_PARAMETERS: 
    syntax_token = newxta ? T_NEW_PARAMETERS : T_OLD_PARAMETERS;
    g_parameter_count = 0;
    if (utap_parse()) {
      res = -1;
    } else res = g_parameter_count;
    break;
  case S_INVARIANT: 
    syntax_token = newxta ? T_NEW_INVARIANT : T_OLD_INVARIANT;
    if (utap_parse()) {
      res = -1;
    } else res = 0;
    break;
  case S_GUARD: 
    syntax_token = newxta ? T_NEW_GUARD : T_OLD_GUARD; 
    if (utap_parse()) {
      res = -1;
    } else res = 0;
    break;
  case S_SYNC: 
    syntax_token = T_NEW_SYNC; // the system definition is the same for both
    if (utap_parse()) {
      res = -1;
    } else res = 0;
    break;
  case S_ASSIGN: 
    syntax_token = newxta ? T_NEW_ASSIGN : T_OLD_ASSIGN;
    if (utap_parse()) {
      res = -1;
    } else res = 0;
    break;
  default: 
    res = -1;
    break;
  }
  yy_delete_buffer(YY_CURRENT_BUFFER);

  return res;
}

int32_t parseXTA(FILE *file, ParserBuilder *aParserBuilder, 
    ErrorHandler *err, bool newxta)
{
  return parseXTA(file, aParserBuilder, err, newxta, S_XTA);
}

int32_t parseXTA(FILE *file, ParserBuilder *aParserBuilder, 
    ErrorHandler *err, bool newxta, xta_part_t part)
{
  int res = 0;
  utap_in = file;
  syntax = (newxta ? SYNTAX_NEW : SYNTAX_OLD);
  ch = aParserBuilder;
  ch->setErrorHandler(err);

  yylloc.reset();
  errorHandler = err;

  yy_switch_to_buffer(yy_create_buffer(file, YY_BUF_SIZE));
  
  switch (part) { /* convertion from old to new */
  case S_XTA: 
    syntax_token = newxta ? T_NEW : T_OLD;
    if (utap_parse()) {
      res = -1;
    } else res = 0;
    break;
  case S_DECLARATION: 
    syntax_token = newxta ? T_NEW_DECLARATION : T_OLD_DECLARATION;
    if (utap_parse()) {
      res = -1;
    } else res = 0;
    break;
  case S_LOCAL_DECL: 
    syntax_token = newxta ? T_NEW_LOCAL_DECL : T_OLD_LOCAL_DECL; 
    if (utap_parse()) {
      res = -1;
    } else res = 0;
    break;
  case S_INST: 
    syntax_token = newxta ? T_NEW_INST : T_OLD_INST;
    if (utap_parse()) {
      res = -1;
    } else res = 0;
    break;
  case S_SYSTEM: 
    syntax_token = T_NEW_SYSTEM; // the system definition is the same for both
    if (utap_parse()) {
      res = -1;
    } else res = 0;
    break;
  case S_PARAMETERS: 
    syntax_token = newxta ? T_NEW_PARAMETERS : T_OLD_PARAMETERS;
    g_parameter_count = 0;
    if (utap_parse()) {
      res = -1;
    } else res = g_parameter_count;
    break;
  case S_INVARIANT: 
    syntax_token = newxta ? T_NEW_INVARIANT : T_OLD_INVARIANT;
    if (utap_parse()) {
      res = -1;
    } else res = 0;
    break;
  case S_GUARD: 
    syntax_token = newxta ? T_NEW_GUARD : T_OLD_GUARD; 
    if (utap_parse()) {
      res = -1;
    } else res = 0;
    break;
  case S_SYNC: 
    syntax_token = T_NEW_SYNC; // the system definition is the same for both
    if (utap_parse()) {
      res = -1;
    } else res = 0;
    break;
  case S_ASSIGN: 
    syntax_token = newxta ? T_NEW_ASSIGN : T_OLD_ASSIGN;
    if (utap_parse()) {
      res = -1;
    } else res = 0;
    break;
  default: 
    res = -1;
    break;
  }

  yy_delete_buffer(YY_CURRENT_BUFFER);

  return res;
}

int32_t parseProperty(const char *str, ParserBuilder *aParserBuilder, 
		      ErrorHandler *err)
{
  syntax = SYNTAX_PROPERTY;
  ch = aParserBuilder;
  ch->setErrorHandler(err);
  errorHandler = err;
  syntax_token = T_PROPERTY;
  yylloc.reset();

  yy_scan_string(str);

  int res = utap_parse();

  yy_delete_buffer(YY_CURRENT_BUFFER);

  return (res ? -1 : 0);
}

int32_t parseProperty(FILE *file, ParserBuilder *aParserBuilder, 
		      ErrorHandler *err)
{
  syntax = SYNTAX_PROPERTY;
  ch = aParserBuilder;
  ch->setErrorHandler(err);
  errorHandler = err;
  syntax_token = T_PROPERTY;
  yylloc.reset();
  utap_in = file;

  yy_switch_to_buffer(yy_create_buffer(file, YY_BUF_SIZE));

  int res = utap_parse();

  yy_delete_buffer(YY_CURRENT_BUFFER);

  return (res ? -1 : 0);
}



