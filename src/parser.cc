/* A Bison parser, made by GNU Bison 1.875d.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004 Free Software Foundation, Inc.

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
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

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
     T_ASSPLUS = 259,
     T_ASSMINUS = 260,
     T_ASSMULT = 261,
     T_ASSDIV = 262,
     T_ASSMOD = 263,
     T_ASSOR = 264,
     T_ASSAND = 265,
     T_ASSXOR = 266,
     T_ASSLSHIFT = 267,
     T_ASSRSHIFT = 268,
     T_EXCLAM = 269,
     T_INCREMENT = 270,
     T_DECREMENT = 271,
     T_PLUS = 272,
     T_MINUS = 273,
     T_MULT = 274,
     T_DIV = 275,
     T_MIN = 276,
     T_MAX = 277,
     T_MOD = 278,
     T_OR = 279,
     T_XOR = 280,
     T_LSHIFT = 281,
     T_RSHIFT = 282,
     T_BOOL_AND = 283,
     T_BOOL_OR = 284,
     T_KW_AND = 285,
     T_KW_OR = 286,
     T_KW_IMPLY = 287,
     T_KW_NOT = 288,
     T_LT = 289,
     T_LEQ = 290,
     T_EQ = 291,
     T_NEQ = 292,
     T_GEQ = 293,
     T_GT = 294,
     T_FOR = 295,
     T_WHILE = 296,
     T_DO = 297,
     T_BREAK = 298,
     T_CONTINUE = 299,
     T_SWITCH = 300,
     T_IF = 301,
     T_ELSE = 302,
     T_CASE = 303,
     T_DEFAULT = 304,
     T_RETURN = 305,
     T_CHAN_PRIORITY = 306,
     T_PROC_PRIORITY = 307,
     T_TYPEDEF = 308,
     T_STRUCT = 309,
     T_CONST = 310,
     T_OLDCONST = 311,
     T_URGENT = 312,
     T_BROADCAST = 313,
     T_TRUE = 314,
     T_FALSE = 315,
     T_META = 316,
     T_SYSTEM = 317,
     T_PROCESS = 318,
     T_STATE = 319,
     T_COMMIT = 320,
     T_INIT = 321,
     T_TRANS = 322,
     T_ARROW = 323,
     T_GUARD = 324,
     T_SYNC = 325,
     T_ASSIGN = 326,
     T_BEFORE = 327,
     T_AFTER = 328,
     T_PROGRESS = 329,
     T_DEADLOCK = 330,
     T_EF = 331,
     T_EG = 332,
     T_AF = 333,
     T_AG = 334,
     T_LEADSTO = 335,
     T_QUIT = 336,
     T_ERROR = 337,
     T_ID = 338,
     T_TYPENAME = 339,
     T_NAT = 340,
     T_NEW = 341,
     T_NEW_DECLARATION = 342,
     T_NEW_LOCAL_DECL = 343,
     T_NEW_INST = 344,
     T_NEW_SYSTEM = 345,
     T_NEW_PARAMETERS = 346,
     T_NEW_INVARIANT = 347,
     T_NEW_GUARD = 348,
     T_NEW_SYNC = 349,
     T_NEW_ASSIGN = 350,
     T_OLD = 351,
     T_OLD_DECLARATION = 352,
     T_OLD_LOCAL_DECL = 353,
     T_OLD_INST = 354,
     T_OLD_PARAMETERS = 355,
     T_OLD_INVARIANT = 356,
     T_OLD_GUARD = 357,
     T_OLD_ASSIGN = 358,
     T_PROPERTY = 359,
     T_EXPRESSION = 360,
     UOPERATOR = 361
   };
#endif
#define T_ASSIGNMENT 258
#define T_ASSPLUS 259
#define T_ASSMINUS 260
#define T_ASSMULT 261
#define T_ASSDIV 262
#define T_ASSMOD 263
#define T_ASSOR 264
#define T_ASSAND 265
#define T_ASSXOR 266
#define T_ASSLSHIFT 267
#define T_ASSRSHIFT 268
#define T_EXCLAM 269
#define T_INCREMENT 270
#define T_DECREMENT 271
#define T_PLUS 272
#define T_MINUS 273
#define T_MULT 274
#define T_DIV 275
#define T_MIN 276
#define T_MAX 277
#define T_MOD 278
#define T_OR 279
#define T_XOR 280
#define T_LSHIFT 281
#define T_RSHIFT 282
#define T_BOOL_AND 283
#define T_BOOL_OR 284
#define T_KW_AND 285
#define T_KW_OR 286
#define T_KW_IMPLY 287
#define T_KW_NOT 288
#define T_LT 289
#define T_LEQ 290
#define T_EQ 291
#define T_NEQ 292
#define T_GEQ 293
#define T_GT 294
#define T_FOR 295
#define T_WHILE 296
#define T_DO 297
#define T_BREAK 298
#define T_CONTINUE 299
#define T_SWITCH 300
#define T_IF 301
#define T_ELSE 302
#define T_CASE 303
#define T_DEFAULT 304
#define T_RETURN 305
#define T_CHAN_PRIORITY 306
#define T_PROC_PRIORITY 307
#define T_TYPEDEF 308
#define T_STRUCT 309
#define T_CONST 310
#define T_OLDCONST 311
#define T_URGENT 312
#define T_BROADCAST 313
#define T_TRUE 314
#define T_FALSE 315
#define T_META 316
#define T_SYSTEM 317
#define T_PROCESS 318
#define T_STATE 319
#define T_COMMIT 320
#define T_INIT 321
#define T_TRANS 322
#define T_ARROW 323
#define T_GUARD 324
#define T_SYNC 325
#define T_ASSIGN 326
#define T_BEFORE 327
#define T_AFTER 328
#define T_PROGRESS 329
#define T_DEADLOCK 330
#define T_EF 331
#define T_EG 332
#define T_AF 333
#define T_AG 334
#define T_LEADSTO 335
#define T_QUIT 336
#define T_ERROR 337
#define T_ID 338
#define T_TYPENAME 339
#define T_NAT 340
#define T_NEW 341
#define T_NEW_DECLARATION 342
#define T_NEW_LOCAL_DECL 343
#define T_NEW_INST 344
#define T_NEW_SYSTEM 345
#define T_NEW_PARAMETERS 346
#define T_NEW_INVARIANT 347
#define T_NEW_GUARD 348
#define T_NEW_SYNC 349
#define T_NEW_ASSIGN 350
#define T_OLD 351
#define T_OLD_DECLARATION 352
#define T_OLD_LOCAL_DECL 353
#define T_OLD_INST 354
#define T_OLD_PARAMETERS 355
#define T_OLD_INVARIANT 356
#define T_OLD_GUARD 357
#define T_OLD_ASSIGN 358
#define T_PROPERTY 359
#define T_EXPRESSION 360
#define UOPERATOR 361




/* Copy the first part of user declarations.  */
#line 53 "parser.yy"


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
static const char* PE_ALT_TRANS = "alternative edge expected";
static const char* PE_ARGLIST = "argument expression list expected";
static const char* PE_ARGLIST_ = "one more argument expression expected";
static const char* PE_ARROW = "'->' expected";
static const char* PE_ASSIGN = "'=' expected";
static const char* PE_ASSIGN_EXP = "assignment expression expected";
static const char* PE_BANG = "'!' expected";
static const char* PE_BANGQUE = "'!' or '?' expected";
static const char* PE_COLON = "':' expected";
static const char* PE_CONST_EXP = "constant expression expected";
static const char* PE_EXPR = "expression expected";
static const char* PE_GUARD_EXP = "guard expression expected";
static const char* PE_GUARD_EXP_ = "one more guard expression expected";
static const char* PE_INV = "invariant expression expected";
static const char* PE_LBRACE = "'{' expected";
static const char* PE_LBRACES = "'(' or '{' expected";
static const char* PE_LOC_DECL = "location declaration expected";
static const char* PE_LPAREN = "'(' expected";
static const char* PE_MEMBER = "member declarations expected";
static const char* PE_MEMBERID = "member identifier expected";
static const char* PE_MEMBERTYPE = "member type identifier expected";
static const char* PE_PARAM_DECL_ = "one more parameter declaration expected";
static const char* PE_PARAMETERS = "parameters expected";
static const char* PE_PARAMETERS_ = "one more parameter expected";
static const char* PE_PARAMID = "parameter identifier expected";
static const char* PE_PROCID = "process identifiers expected";
static const char* PE_PROCID_ = "one more process identifier expected";
static const char* PE_QUE = "'?' expected";
static const char* PE_RBRACE = "'}' expected";
static const char* PE_RPAREN = "')' expected";
static const char* PE_SEMICOLON = "';' expected";
static const char* PE_STATE_DECL = "state declaration expected";
static const char* PE_STATE_DECL_ = "one more state declaration expected";
static const char* PE_STATEID = "state identifier expected";
static const char* PE_STATEID_ = "one more state identifier expected";
static const char* PE_SYNC_EXP = "synchronization expression expected";
static const char* PE_SYSTEM = "'system' expected";
static const char* PE_TRANS = "'trans' expected";
static const char* PE_TRANS_DECL = "edge declaration expected";
static const char* PE_TRANS_DECL_ = "one more edge declaration expected";
static const char* PE_TYPEID_= "one more type identifier expected";

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

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 246 "parser.yy"
typedef union YYSTYPE {
    bool flag;
    int number;
    kind_t kind;
    char string[MAXLEN];
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 419 "parser.tab.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

#if ! defined (YYLTYPE) && ! defined (YYLTYPE_IS_DECLARED)
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 443 "parser.tab.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

# ifndef YYFREE
#  define YYFREE free
# endif
# ifndef YYMALLOC
#  define YYMALLOC malloc
# endif

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   define YYSTACK_ALLOC alloca
#  endif
# else
#  if defined (alloca) || defined (_ALLOCA_H)
#   define YYSTACK_ALLOC alloca
#  else
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
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
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (defined (YYLTYPE_IS_TRIVIAL) && YYLTYPE_IS_TRIVIAL \
             && defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short int yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short int) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined (__GNUC__) && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
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
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short int yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  79
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3116

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  121
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  122
/* YYNRULES -- Number of rules. */
#define YYNRULES  390
/* YYNRULES -- Number of states. */
#define YYNSTATES  735

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   361

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     120,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   108,   115,
     110,   111,     2,     2,   117,     2,   114,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   107,   116,
       2,     2,     2,   106,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   112,     2,   113,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   118,     2,   119,     2,     2,     2,     2,
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
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   109
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short int yyprhs[] =
{
       0,     0,     3,     6,     9,    12,    15,    18,    21,    24,
      27,    30,    33,    36,    39,    42,    45,    48,    51,    54,
      57,    60,    63,    66,    70,    71,    72,    82,    91,    99,
     106,   111,   116,   117,   121,   122,   126,   128,   132,   136,
     140,   144,   148,   153,   157,   159,   163,   167,   168,   173,
     174,   180,   184,   185,   188,   191,   194,   197,   200,   203,
     206,   211,   216,   217,   226,   232,   235,   239,   243,   245,
     249,   254,   258,   261,   265,   267,   271,   275,   276,   279,
     281,   285,   287,   291,   295,   297,   298,   303,   308,   313,
     317,   319,   323,   327,   330,   334,   340,   346,   348,   350,
     352,   355,   358,   362,   367,   371,   374,   376,   380,   383,
     384,   386,   388,   391,   393,   395,   396,   400,   406,   410,
     411,   419,   420,   427,   433,   434,   437,   440,   443,   447,
     452,   456,   459,   461,   465,   469,   471,   476,   481,   485,
     488,   489,   493,   497,   499,   503,   507,   516,   526,   532,
     537,   541,   549,   558,   563,   567,   569,   570,   574,   579,
     583,   584,   588,   593,   597,   601,   604,   608,   611,   615,
     618,   619,   623,   627,   628,   630,   632,   635,   639,   644,
     648,   652,   655,   659,   664,   668,   672,   675,   677,   681,
     685,   687,   691,   695,   696,   702,   703,   706,   709,   710,
     713,   717,   719,   721,   724,   725,   736,   742,   743,   750,
     756,   757,   766,   767,   775,   778,   781,   782,   791,   795,
     798,   799,   800,   804,   805,   809,   811,   814,   815,   821,
     822,   828,   829,   834,   835,   841,   843,   847,   849,   851,
     853,   855,   856,   862,   863,   869,   874,   879,   883,   887,
     890,   893,   896,   899,   902,   906,   910,   914,   918,   922,
     926,   930,   934,   938,   942,   946,   950,   954,   958,   962,
     966,   970,   974,   980,   984,   987,   989,   990,   995,   999,
    1003,  1006,  1010,  1014,  1016,  1020,  1022,  1024,  1026,  1028,
    1030,  1032,  1034,  1036,  1038,  1040,  1042,  1044,  1046,  1048,
    1049,  1051,  1055,  1059,  1063,  1064,  1067,  1070,  1072,  1073,
    1078,  1082,  1084,  1088,  1092,  1093,  1101,  1102,  1111,  1112,
    1120,  1121,  1128,  1129,  1136,  1139,  1143,  1147,  1149,  1151,
    1155,  1159,  1162,  1166,  1171,  1175,  1180,  1186,  1187,  1190,
    1194,  1197,  1199,  1203,  1207,  1209,  1214,  1216,  1220,  1222,
    1226,  1227,  1231,  1236,  1240,  1244,  1247,  1249,  1251,  1255,
    1259,  1268,  1278,  1287,  1297,  1307,  1315,  1323,  1332,  1341,
    1350,  1358,  1360,  1361,  1365,  1370,  1374,  1377,  1379,  1383,
    1387,  1390,  1391,  1395,  1396,  1398,  1401,  1405,  1407,  1409,
    1411
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short int yyrhs[] =
{
     122,     0,    -1,    86,   123,    -1,    87,   134,    -1,    88,
     165,    -1,    89,   124,    -1,    90,   126,    -1,    90,     1,
      -1,    91,   140,    -1,    92,   203,    -1,    93,   203,    -1,
      94,   176,    -1,    95,   202,    -1,    96,   211,    -1,    97,
     212,    -1,    98,   228,    -1,    99,   124,    -1,   100,   224,
      -1,   101,   232,    -1,   102,   238,    -1,   103,   202,    -1,
     104,   239,    -1,   105,   203,    -1,   134,   124,   126,    -1,
      -1,    -1,   124,    83,     3,    83,   110,   125,   210,   111,
     116,    -1,   124,    83,     3,    83,   110,     1,   111,   116,
      -1,   124,    83,     3,    83,   110,     1,   116,    -1,   124,
      83,     3,    83,     1,   116,    -1,   124,    83,     1,   116,
      -1,   127,   128,   130,   132,    -1,    -1,    51,   129,   116,
      -1,    -1,    52,   129,   116,    -1,    83,    -1,   129,    36,
      83,    -1,   129,    34,    83,    -1,   129,    36,     1,    -1,
     129,    34,     1,    -1,    62,   131,   116,    -1,    62,   131,
       1,   116,    -1,    62,     1,   116,    -1,    83,    -1,   131,
     117,    83,    -1,   131,   117,     1,    -1,    -1,    74,   118,
     133,   119,    -1,    -1,   133,   203,   107,   203,   116,    -1,
     133,   203,   116,    -1,    -1,   134,   137,    -1,   134,   142,
      -1,   134,   150,    -1,   134,   161,    -1,   134,   135,    -1,
     134,   136,    -1,     1,   116,    -1,    72,   118,   202,   119,
      -1,    73,   118,   202,   119,    -1,    -1,   153,   154,   139,
     138,   118,   185,   186,   119,    -1,   153,   154,   110,     1,
     119,    -1,   110,   111,    -1,   110,   140,   111,    -1,   110,
       1,   111,    -1,   141,    -1,   140,   117,   141,    -1,   153,
     108,    83,   149,    -1,   153,    83,   149,    -1,   153,     1,
      -1,   153,   143,   116,    -1,   144,    -1,   143,   117,   144,
      -1,   154,   149,   145,    -1,    -1,     3,   146,    -1,   203,
      -1,   118,   147,   119,    -1,   148,    -1,   147,   117,   148,
      -1,   154,   107,   146,    -1,   146,    -1,    -1,   149,   112,
     203,   113,    -1,   149,   112,     1,   113,    -1,    53,   153,
     151,   116,    -1,    53,     1,   116,    -1,   152,    -1,   151,
     117,   152,    -1,   151,   117,     1,    -1,   154,   149,    -1,
     159,    84,   160,    -1,   159,    54,   118,   155,   119,    -1,
     159,    54,   118,     1,   119,    -1,    83,    -1,    84,    -1,
     156,    -1,   155,   156,    -1,   155,     1,    -1,   153,   157,
     116,    -1,   153,   157,     1,   116,    -1,   153,     1,   116,
      -1,     1,   116,    -1,   158,    -1,   157,   117,   158,    -1,
     154,   149,    -1,    -1,    57,    -1,    58,    -1,    57,    58,
      -1,    55,    -1,    61,    -1,    -1,   112,   203,   113,    -1,
     112,   203,   117,   203,   113,    -1,   112,     1,   113,    -1,
      -1,    63,   154,   139,   118,   162,   164,   119,    -1,    -1,
      63,   154,   118,   163,   164,   119,    -1,   165,   166,   178,
     169,   170,    -1,    -1,   165,   137,    -1,   165,   142,    -1,
     165,   150,    -1,    64,   167,   116,    -1,    64,   167,     1,
     116,    -1,    64,     1,   116,    -1,     1,   116,    -1,   168,
      -1,   167,   117,   168,    -1,   167,   117,     1,    -1,    83,
      -1,    83,   118,   203,   119,    -1,    83,   118,     1,   119,
      -1,    66,    83,   116,    -1,     1,   116,    -1,    -1,    67,
     171,   116,    -1,    67,     1,   116,    -1,   172,    -1,   171,
     117,   173,    -1,   171,   117,     1,    -1,    83,    68,    83,
     118,   174,   175,   177,   119,    -1,    83,    68,    83,   118,
     174,   175,   177,     1,   116,    -1,    83,    68,    83,     1,
     119,    -1,    83,    68,     1,   119,    -1,    83,     1,   119,
      -1,    68,    83,   118,   174,   175,   177,   119,    -1,    68,
      83,   118,   174,   175,   177,     1,   119,    -1,    68,    83,
       1,   119,    -1,    68,     1,   119,    -1,   172,    -1,    -1,
      69,   203,   116,    -1,    69,   203,     1,   116,    -1,    69,
       1,   116,    -1,    -1,    70,   176,   116,    -1,    70,   176,
       1,   116,    -1,    70,   176,     1,    -1,    70,     1,   116,
      -1,   203,    14,    -1,   203,     1,    14,    -1,   203,   106,
      -1,   203,     1,   106,    -1,   203,     1,    -1,    -1,    71,
     202,   116,    -1,    71,     1,   116,    -1,    -1,   179,    -1,
     180,    -1,   179,   180,    -1,    65,   181,   116,    -1,    65,
     181,     1,   116,    -1,    65,   181,     1,    -1,    65,     1,
     116,    -1,    65,     1,    -1,    57,   182,   116,    -1,    57,
     182,     1,   116,    -1,    57,   182,     1,    -1,    57,     1,
     116,    -1,    57,     1,    -1,    83,    -1,   181,   117,    83,
      -1,   181,   117,     1,    -1,    83,    -1,   182,   117,    83,
      -1,   182,   117,     1,    -1,    -1,   118,   184,   185,   186,
     119,    -1,    -1,   185,   142,    -1,   185,   150,    -1,    -1,
     186,   187,    -1,   186,     1,   116,    -1,   183,    -1,   116,
      -1,   203,   116,    -1,    -1,    40,   110,   188,   202,   116,
     202,   116,   202,   111,   187,    -1,    40,   110,     1,   111,
     187,    -1,    -1,    41,   110,   189,   202,   111,   187,    -1,
      41,   110,     1,   111,   187,    -1,    -1,    42,   190,   187,
      41,   110,   202,   111,   116,    -1,    -1,    46,   110,   191,
     202,   111,   187,   193,    -1,    43,   116,    -1,    44,   116,
      -1,    -1,    45,   110,   202,   111,   192,   118,   196,   119,
      -1,    50,   203,   116,    -1,    50,   116,    -1,    -1,    -1,
      47,   194,   187,    -1,    -1,    47,   195,     1,    -1,   197,
      -1,   196,   197,    -1,    -1,    48,   203,   107,   198,   186,
      -1,    -1,    48,     1,   107,   199,   186,    -1,    -1,    49,
     107,   200,   186,    -1,    -1,    49,     1,   107,   201,   186,
      -1,   203,    -1,   202,   117,   203,    -1,    60,    -1,    59,
      -1,    85,    -1,    83,    -1,    -1,    83,   110,   204,   210,
     111,    -1,    -1,    83,   110,   205,     1,   111,    -1,   203,
     112,   203,   113,    -1,   203,   112,     1,   113,    -1,   110,
     203,   111,    -1,   110,     1,   111,    -1,   203,    15,    -1,
      15,   203,    -1,   203,    16,    -1,    16,   203,    -1,   209,
     203,    -1,   203,    34,   203,    -1,   203,    35,   203,    -1,
     203,    36,   203,    -1,   203,    37,   203,    -1,   203,    39,
     203,    -1,   203,    38,   203,    -1,   203,    17,   203,    -1,
     203,    18,   203,    -1,   203,    19,   203,    -1,   203,    20,
     203,    -1,   203,    23,   203,    -1,   203,   108,   203,    -1,
     203,    24,   203,    -1,   203,    25,   203,    -1,   203,    26,
     203,    -1,   203,    27,   203,    -1,   203,    28,   203,    -1,
     203,    29,   203,    -1,   203,   106,   203,   107,   203,    -1,
     203,   114,    83,    -1,   203,   115,    -1,    75,    -1,    -1,
     203,    32,   206,   203,    -1,   203,    30,   203,    -1,   203,
      31,   203,    -1,    33,   203,    -1,   203,    21,   203,    -1,
     203,    22,   203,    -1,   207,    -1,   203,   208,   203,    -1,
       3,    -1,     4,    -1,     5,    -1,     7,    -1,     8,    -1,
       6,    -1,    10,    -1,     9,    -1,    11,    -1,    12,    -1,
      13,    -1,    18,    -1,    17,    -1,    14,    -1,    -1,   203,
      -1,   210,   117,   203,    -1,   210,   117,     1,    -1,   212,
     124,   126,    -1,    -1,   212,   213,    -1,   212,   217,    -1,
     142,    -1,    -1,    56,   214,   215,   116,    -1,    56,     1,
     116,    -1,   216,    -1,   215,   117,   216,    -1,    83,   149,
     146,    -1,    -1,    63,   154,   223,   118,   218,   227,   119,
      -1,    -1,    63,   154,   223,     1,   118,   219,   227,   119,
      -1,    -1,    63,   154,     1,   118,   220,   227,   119,    -1,
      -1,    63,     1,   118,   221,   227,   119,    -1,    -1,    63,
     154,   118,   222,   227,   119,    -1,   110,   111,    -1,   110,
     224,   111,    -1,   110,     1,   111,    -1,   225,    -1,   226,
      -1,   224,   116,   225,    -1,   224,   116,   226,    -1,   224,
     116,    -1,   153,    83,   149,    -1,   225,   117,    83,   149,
      -1,    56,    83,   149,    -1,   226,   117,    83,   149,    -1,
     228,   229,   178,   169,   233,    -1,    -1,   228,   213,    -1,
      64,   230,   116,    -1,     1,   116,    -1,   231,    -1,   230,
     117,   231,    -1,   230,   117,     1,    -1,    83,    -1,    83,
     118,   232,   119,    -1,   203,    -1,   203,     1,   117,    -1,
       1,    -1,   232,   117,   203,    -1,    -1,    67,   234,   116,
      -1,    67,   234,     1,   116,    -1,    67,   234,     1,    -1,
      67,     1,   116,    -1,    67,     1,    -1,     1,    -1,   235,
      -1,   234,   117,   236,    -1,   234,   117,     1,    -1,    83,
      68,    83,   118,   237,   175,   177,   119,    -1,    83,    68,
      83,   118,   237,   175,   177,     1,   119,    -1,    83,    68,
      83,   118,   237,   175,   177,     1,    -1,    83,    68,    83,
       1,   118,   237,   175,   177,   119,    -1,    83,     1,    68,
      83,   118,   237,   175,   177,   119,    -1,    68,    83,   118,
     237,   175,   177,   119,    -1,    68,    83,   118,   237,   175,
     177,     1,    -1,    68,    83,   118,   237,   175,   177,     1,
     119,    -1,    68,    83,     1,   118,   237,   175,   177,   119,
      -1,    68,     1,    83,   118,   237,   175,   177,   119,    -1,
      68,     1,   118,   237,   175,   177,   119,    -1,   235,    -1,
      -1,    69,   238,   116,    -1,    69,   238,     1,   116,    -1,
      69,   238,     1,    -1,    69,     1,    -1,   203,    -1,   238,
     117,   203,    -1,   238,   117,     1,    -1,   240,   241,    -1,
      -1,   240,   241,   120,    -1,    -1,    81,    -1,   242,   203,
      -1,   203,    80,   203,    -1,    76,    -1,    77,    -1,    78,
      -1,    79,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   259,   259,   260,   261,   262,   263,   264,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   285,   288,   290,   290,   295,   298,   301,
     304,   309,   311,   313,   316,   318,   322,   323,   324,   325,
     326,   330,   331,   334,   340,   341,   342,   347,   349,   351,
     353,   356,   360,   362,   363,   364,   365,   366,   367,   368,
     371,   373,   376,   376,   382,   385,   386,   387,   393,   394,
     398,   402,   406,   412,   418,   419,   423,   429,   430,   434,
     435,   441,   442,   446,   449,   455,   456,   457,   465,   468,
     479,   480,   481,   488,   494,   498,   502,   510,   511,   515,
     516,   517,   524,   528,   533,   536,   542,   543,   547,   553,
     554,   555,   556,   557,   558,   562,   563,   564,   565,   575,
     575,   581,   581,   592,   595,   597,   598,   599,   603,   604,
     607,   610,   614,   615,   616,   622,   625,   628,   635,   638,
     641,   643,   644,   650,   651,   652,   658,   662,   667,   670,
     673,   679,   682,   686,   689,   692,   696,   698,   701,   705,
     710,   712,   713,   716,   719,   725,   728,   732,   735,   739,
     745,   747,   750,   755,   757,   758,   759,   763,   764,   767,
     770,   773,   779,   780,   783,   786,   789,   795,   798,   801,
     807,   810,   813,   824,   824,   832,   834,   835,   838,   840,
     841,   845,   846,   849,   852,   852,   858,   859,   859,   865,
     866,   866,   872,   872,   876,   879,   882,   882,   888,   891,
     897,   900,   900,   906,   906,   916,   917,   921,   921,   927,
     927,   934,   934,   940,   940,   950,   951,   956,   959,   962,
     965,   968,   968,   973,   973,   979,   982,   986,   987,   991,
     994,   997,  1000,  1003,  1006,  1009,  1012,  1015,  1018,  1021,
    1024,  1027,  1030,  1033,  1036,  1039,  1042,  1045,  1048,  1051,
    1054,  1057,  1060,  1063,  1066,  1069,  1072,  1072,  1077,  1080,
    1083,  1086,  1089,  1092,  1096,  1102,  1103,  1104,  1105,  1106,
    1107,  1108,  1109,  1110,  1111,  1112,  1117,  1118,  1119,  1124,
    1125,  1129,  1133,  1145,  1148,  1150,  1151,  1155,  1156,  1156,
    1161,  1164,  1165,  1169,  1178,  1178,  1184,  1184,  1191,  1191,
    1198,  1198,  1205,  1205,  1214,  1215,  1216,  1223,  1227,  1231,
    1235,  1239,  1246,  1250,  1257,  1262,  1269,  1272,  1274,  1278,
    1279,  1283,  1284,  1285,  1291,  1294,  1300,  1301,  1304,  1308,
    1313,  1315,  1316,  1319,  1322,  1325,  1328,  1334,  1335,  1336,
    1342,  1346,  1351,  1356,  1361,  1370,  1373,  1377,  1381,  1385,
    1389,  1393,  1396,  1398,  1401,  1405,  1409,  1415,  1416,  1419,
    1426,  1428,  1430,  1432,  1434,  1437,  1440,  1445,  1446,  1447,
    1448
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_ASSIGNMENT", "T_ASSPLUS",
  "T_ASSMINUS", "T_ASSMULT", "T_ASSDIV", "T_ASSMOD", "T_ASSOR", "T_ASSAND",
  "T_ASSXOR", "T_ASSLSHIFT", "T_ASSRSHIFT", "T_EXCLAM", "T_INCREMENT",
  "T_DECREMENT", "T_PLUS", "T_MINUS", "T_MULT", "T_DIV", "T_MIN", "T_MAX",
  "T_MOD", "T_OR", "T_XOR", "T_LSHIFT", "T_RSHIFT", "T_BOOL_AND",
  "T_BOOL_OR", "T_KW_AND", "T_KW_OR", "T_KW_IMPLY", "T_KW_NOT", "T_LT",
  "T_LEQ", "T_EQ", "T_NEQ", "T_GEQ", "T_GT", "T_FOR", "T_WHILE", "T_DO",
  "T_BREAK", "T_CONTINUE", "T_SWITCH", "T_IF", "T_ELSE", "T_CASE",
  "T_DEFAULT", "T_RETURN", "T_CHAN_PRIORITY", "T_PROC_PRIORITY",
  "T_TYPEDEF", "T_STRUCT", "T_CONST", "T_OLDCONST", "T_URGENT",
  "T_BROADCAST", "T_TRUE", "T_FALSE", "T_META", "T_SYSTEM", "T_PROCESS",
  "T_STATE", "T_COMMIT", "T_INIT", "T_TRANS", "T_ARROW", "T_GUARD",
  "T_SYNC", "T_ASSIGN", "T_BEFORE", "T_AFTER", "T_PROGRESS", "T_DEADLOCK",
  "T_EF", "T_EG", "T_AF", "T_AG", "T_LEADSTO", "T_QUIT", "T_ERROR", "T_ID",
  "T_TYPENAME", "T_NAT", "T_NEW", "T_NEW_DECLARATION", "T_NEW_LOCAL_DECL",
  "T_NEW_INST", "T_NEW_SYSTEM", "T_NEW_PARAMETERS", "T_NEW_INVARIANT",
  "T_NEW_GUARD", "T_NEW_SYNC", "T_NEW_ASSIGN", "T_OLD",
  "T_OLD_DECLARATION", "T_OLD_LOCAL_DECL", "T_OLD_INST",
  "T_OLD_PARAMETERS", "T_OLD_INVARIANT", "T_OLD_GUARD", "T_OLD_ASSIGN",
  "T_PROPERTY", "T_EXPRESSION", "'?'", "':'", "'&'", "UOPERATOR", "'('",
  "')'", "'['", "']'", "'.'", "'''", "';'", "','", "'{'", "'}'", "'\\n'",
  "$accept", "Uppaal", "XTA", "Inst", "@1", "System", "ChanPriorityDecl",
  "ProcPriorityDecl", "PriorityOrder", "SysDecl", "ProcessList",
  "Progress", "ProgressMeasureList", "Declaration", "BeforeUpdateDecl",
  "AfterUpdateDecl", "FunctionDecl", "@2", "OptionalParameterList",
  "ParameterList", "Parameter", "VariableDecl", "DeclIdList", "DeclId",
  "VarInit", "Initializer", "FieldInitList", "FieldInit", "ArrayDecl",
  "TypeDecl", "TypeIdList", "TypeId", "Type", "Id", "FieldDeclList",
  "FieldDecl", "FieldDeclIdList", "FieldDeclId", "TypePrefix", "Range",
  "ProcDecl", "@3", "@4", "ProcBody", "ProcLocalDeclList", "States",
  "StateDeclList", "StateDecl", "Init", "Transitions", "TransitionList",
  "Transition", "TransitionOpt", "Guard", "Sync", "SyncExpr", "Assign",
  "LocFlags", "Commit", "Urgent", "CStateList", "UStateList", "Block",
  "@5", "BlockLocalDeclList", "StatementList", "Statement", "@6", "@7",
  "@8", "@9", "@10", "ElsePart", "@11", "@12", "SwitchCaseList",
  "SwitchCase", "@13", "@14", "@15", "@16", "ExprList", "Expression",
  "@17", "@18", "@19", "Assignment", "AssignOp", "UnaryOp", "ArgList",
  "OldXTA", "OldDeclaration", "OldVarDecl", "@20", "OldConstDeclIdList",
  "OldConstDeclId", "OldProcDecl", "@21", "@22", "@23", "@24", "@25",
  "OldProcParams", "OldProcParamList", "OldProcParam", "OldProcConstParam",
  "OldProcBody", "OldVarDeclList", "OldStates", "OldStateDeclList",
  "OldStateDecl", "OldInvariant", "OldTransitions", "OldTransitionList",
  "OldTransition", "OldTransitionOpt", "OldGuard", "OldGuardList",
  "PropertyList", "PropertyList2", "Property", "Quantifier", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short int yytoknum[] =
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
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,    63,    58,    38,   361,
      40,    41,    91,    93,    46,    39,    59,    44,   123,   125,
      10
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,   121,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   123,   124,   125,   124,   124,   124,   124,
     124,   126,   127,   127,   128,   128,   129,   129,   129,   129,
     129,   130,   130,   130,   131,   131,   131,   132,   132,   133,
     133,   133,   134,   134,   134,   134,   134,   134,   134,   134,
     135,   136,   138,   137,   137,   139,   139,   139,   140,   140,
     141,   141,   141,   142,   143,   143,   144,   145,   145,   146,
     146,   147,   147,   148,   148,   149,   149,   149,   150,   150,
     151,   151,   151,   152,   153,   153,   153,   154,   154,   155,
     155,   155,   156,   156,   156,   156,   157,   157,   158,   159,
     159,   159,   159,   159,   159,   160,   160,   160,   160,   162,
     161,   163,   161,   164,   165,   165,   165,   165,   166,   166,
     166,   166,   167,   167,   167,   168,   168,   168,   169,   169,
     170,   170,   170,   171,   171,   171,   172,   172,   172,   172,
     172,   173,   173,   173,   173,   173,   174,   174,   174,   174,
     175,   175,   175,   175,   175,   176,   176,   176,   176,   176,
     177,   177,   177,   178,   178,   178,   178,   179,   179,   179,
     179,   179,   180,   180,   180,   180,   180,   181,   181,   181,
     182,   182,   182,   184,   183,   185,   185,   185,   186,   186,
     186,   187,   187,   187,   188,   187,   187,   189,   187,   187,
     190,   187,   191,   187,   187,   187,   192,   187,   187,   187,
     193,   194,   193,   195,   193,   196,   196,   198,   197,   199,
     197,   200,   197,   201,   197,   202,   202,   203,   203,   203,
     203,   204,   203,   205,   203,   203,   203,   203,   203,   203,
     203,   203,   203,   203,   203,   203,   203,   203,   203,   203,
     203,   203,   203,   203,   203,   203,   203,   203,   203,   203,
     203,   203,   203,   203,   203,   203,   206,   203,   203,   203,
     203,   203,   203,   203,   207,   208,   208,   208,   208,   208,
     208,   208,   208,   208,   208,   208,   209,   209,   209,   210,
     210,   210,   210,   211,   212,   212,   212,   213,   214,   213,
     213,   215,   215,   216,   218,   217,   219,   217,   220,   217,
     221,   217,   222,   217,   223,   223,   223,   224,   224,   224,
     224,   224,   225,   225,   226,   226,   227,   228,   228,   229,
     229,   230,   230,   230,   231,   231,   232,   232,   232,   232,
     233,   233,   233,   233,   233,   233,   233,   234,   234,   234,
     235,   235,   235,   235,   235,   236,   236,   236,   236,   236,
     236,   236,   237,   237,   237,   237,   237,   238,   238,   238,
     239,   240,   240,   241,   241,   241,   241,   242,   242,   242,
     242
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     3,     0,     0,     9,     8,     7,     6,
       4,     4,     0,     3,     0,     3,     1,     3,     3,     3,
       3,     3,     4,     3,     1,     3,     3,     0,     4,     0,
       5,     3,     0,     2,     2,     2,     2,     2,     2,     2,
       4,     4,     0,     8,     5,     2,     3,     3,     1,     3,
       4,     3,     2,     3,     1,     3,     3,     0,     2,     1,
       3,     1,     3,     3,     1,     0,     4,     4,     4,     3,
       1,     3,     3,     2,     3,     5,     5,     1,     1,     1,
       2,     2,     3,     4,     3,     2,     1,     3,     2,     0,
       1,     1,     2,     1,     1,     0,     3,     5,     3,     0,
       7,     0,     6,     5,     0,     2,     2,     2,     3,     4,
       3,     2,     1,     3,     3,     1,     4,     4,     3,     2,
       0,     3,     3,     1,     3,     3,     8,     9,     5,     4,
       3,     7,     8,     4,     3,     1,     0,     3,     4,     3,
       0,     3,     4,     3,     3,     2,     3,     2,     3,     2,
       0,     3,     3,     0,     1,     1,     2,     3,     4,     3,
       3,     2,     3,     4,     3,     3,     2,     1,     3,     3,
       1,     3,     3,     0,     5,     0,     2,     2,     0,     2,
       3,     1,     1,     2,     0,    10,     5,     0,     6,     5,
       0,     8,     0,     7,     2,     2,     0,     8,     3,     2,
       0,     0,     3,     0,     3,     1,     2,     0,     5,     0,
       5,     0,     4,     0,     5,     1,     3,     1,     1,     1,
       1,     0,     5,     0,     5,     4,     4,     3,     3,     2,
       2,     2,     2,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     5,     3,     2,     1,     0,     4,     3,     3,
       2,     3,     3,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       1,     3,     3,     3,     0,     2,     2,     1,     0,     4,
       3,     1,     3,     3,     0,     7,     0,     8,     0,     7,
       0,     6,     0,     6,     2,     3,     3,     1,     1,     3,
       3,     2,     3,     4,     3,     4,     5,     0,     2,     3,
       2,     1,     3,     3,     1,     4,     1,     3,     1,     3,
       0,     3,     4,     3,     3,     2,     1,     1,     3,     3,
       8,     9,     8,     9,     9,     7,     7,     8,     8,     8,
       7,     1,     0,     3,     4,     3,     2,     1,     3,     3,
       2,     0,     3,     0,     1,     2,     3,     1,     1,     1,
       1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned short int yydefact[] =
{
       0,     0,     0,   124,    24,     0,   109,     0,     0,     0,
       0,   304,   304,   337,    24,   109,     0,     0,     0,   381,
       0,     0,     0,     2,    24,   109,   109,     5,     7,     0,
       6,    34,   113,   110,   111,   114,     8,    68,     0,     0,
     298,     0,     0,   297,   296,     0,   238,   237,   275,   240,
     239,     0,     9,   283,     0,    10,    11,     0,    12,   235,
      13,    24,   109,   109,    16,     0,     0,    17,   327,   328,
     348,     0,    18,   377,    19,    20,    21,   383,    22,     1,
      59,     0,     0,     0,     0,    32,    57,    58,    53,    54,
      55,     0,    56,   125,   126,   127,     0,    36,     0,     0,
       0,   112,   109,    72,    85,     0,     0,   115,   250,   252,
     280,   241,     0,     0,   285,   286,   287,   290,   288,   289,
     292,   291,   293,   294,   295,   249,   251,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   276,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   274,     0,   253,   169,   165,   167,     0,
       0,     0,    32,   307,     0,   305,   306,   338,    85,    85,
     331,     0,     0,     0,     0,     0,   387,   388,   389,   390,
     384,     0,   380,     0,     0,     0,    97,    98,     0,     0,
       0,    23,     0,    74,    85,     0,     0,     0,     0,    33,
       0,     0,    47,    69,    71,    85,     0,     0,    94,   299,
       0,   248,   247,   260,   261,   262,   263,   281,   282,   264,
     266,   267,   268,   269,   270,   271,   278,   279,     0,   254,
     255,   256,   257,   259,   258,     0,   265,     0,     0,   273,
     284,   166,   168,   236,     0,     0,     0,     0,   303,    85,
     334,   332,   329,   330,    85,    85,   347,   349,   379,   378,
       0,   382,   385,    89,     0,    90,    85,     0,   121,     0,
       0,     0,    73,     0,     0,    62,    77,    30,     0,    40,
      38,    39,    37,    35,     0,    44,     0,     0,    31,     0,
      70,     0,     0,     0,    99,     0,     0,   300,     0,     0,
     277,     0,   246,   245,   310,    85,     0,   311,   320,     0,
       0,   322,     0,   333,   335,   386,    88,     0,    93,     0,
      65,     0,   124,   119,    60,    61,    75,     0,     0,     0,
      76,     0,     0,    43,     0,    41,     0,    49,     0,     0,
     105,    96,     0,    85,     0,   106,   101,    95,   100,   118,
     116,     0,   242,     0,   244,   272,     0,   309,     0,   337,
     318,     0,   324,     0,   337,     0,   314,    92,    91,    67,
      66,     0,     0,   124,    64,   195,     0,    78,    79,    29,
       0,   299,    42,    46,    45,     0,    87,    86,   104,   108,
       0,   102,     0,     0,   302,   301,   313,   312,     0,     0,
     337,   326,   325,     0,   316,   337,   122,     0,     0,   173,
       0,   198,   240,    84,     0,    81,     0,     0,    28,     0,
      48,     0,   103,   107,   117,   321,     0,     0,   173,     0,
     323,   337,     0,   131,     0,   135,     0,   132,     0,     0,
       0,   174,   175,   120,   196,   197,     0,     0,    80,     0,
      27,     0,     0,    51,   340,   344,     0,   341,     0,   319,
       0,   315,   130,     0,     0,   128,     0,   186,   190,     0,
     181,   187,     0,     0,     0,   140,   176,     0,     0,     0,
     210,     0,     0,     0,     0,     0,   202,   193,    63,   201,
     199,     0,    82,    83,    26,     0,     0,   339,     0,     0,
     317,     0,     0,   129,   134,   133,   185,   184,   182,     0,
     180,   179,   177,     0,   139,     0,     0,   123,   200,     0,
       0,     0,   214,   215,     0,   212,   219,     0,   195,   203,
      50,     0,   343,   342,   356,     0,   336,   137,   136,   183,
     192,   191,   178,   189,   188,   138,     0,     0,     0,   143,
       0,     0,     0,     0,     0,     0,     0,   218,   198,   345,
     355,     0,     0,   357,   142,     0,     0,   141,     0,     0,
       0,     0,     0,     0,   216,     0,     0,   354,     0,     0,
     353,   351,     0,   150,     0,     0,   145,     0,   155,   144,
     206,     0,   209,     0,     0,     0,     0,   194,     0,     0,
     352,   359,     0,   371,   358,   149,     0,   156,     0,     0,
       0,   208,     0,     0,   220,     0,     0,   372,     0,     0,
     148,     0,   160,   154,     0,   156,     0,     0,     0,     0,
       0,   225,   221,   213,   372,   372,     0,   160,     0,   372,
       0,   372,     0,     0,     0,   170,   153,   160,     0,   211,
       0,     0,     0,   231,   217,   226,     0,     0,   160,   160,
     376,     0,   170,   372,   160,   372,   160,   159,     0,   157,
       0,     0,     0,     0,   170,     0,   229,   227,   233,   198,
     222,   224,   170,   170,   375,   373,     0,   160,   170,   160,
     170,   158,   164,   163,   161,     0,     0,     0,   146,     0,
     205,   198,   198,   198,     0,     0,     0,   374,   362,   360,
     170,     0,   170,     0,   162,   172,   171,   147,     0,   151,
       0,     0,     0,   364,   363,   361,     0,   370,     0,   366,
     365,   152,   369,   368,   367
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,    21,    23,    27,   381,    30,    31,   100,    98,   202,
     286,   288,   385,    24,    86,    87,    88,   328,   269,   321,
      37,   163,   192,   193,   330,   413,   414,   415,   276,    90,
     264,   265,   164,   249,   293,   294,   344,   345,    39,   208,
      92,   373,   322,   371,   372,   409,   436,   437,   475,   517,
     548,   549,   589,   622,   645,    56,   673,   440,   441,   442,
     472,   469,   489,   528,   411,   446,   490,   551,   553,   521,
     556,   595,   633,   656,   657,   630,   631,   702,   701,   679,
     703,    58,   491,   209,   210,   228,    53,   154,    54,   298,
      60,    61,   165,   245,   306,   307,   166,   405,   431,   400,
     359,   364,   312,    67,    68,    69,   398,   399,   428,   456,
     457,    72,   536,   562,   563,   604,   637,    74,    76,    77,
     182,   183
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -511
static const short int yypact[] =
{
    1246,  3025,  2343,  -511,  -511,   452,   409,  3006,  3006,  3006,
    3006,  -511,  -511,  -511,  -511,   478,   492,  3006,  3006,  -511,
    3006,    76,   -17,  -511,   992,   865,   422,   -56,  -511,    20,
    -511,    65,  -511,    98,  -511,  -511,   131,  -511,   118,   244,
    -511,  3006,  3006,  -511,  -511,  3006,  -511,  -511,  -511,    -3,
    -511,  2235,  2044,  -511,  3006,  2044,  -511,  1103,   141,  2044,
    -511,  1014,   981,   570,   -56,   228,   254,   175,   236,   255,
    -511,   663,   269,  2044,   319,   141,  -511,  2975,  2044,  -511,
    -511,   511,   112,   247,   257,    -6,  -511,  -511,  -511,  -511,
    -511,   112,  -511,  -511,  -511,  -511,    59,  -511,    48,    20,
     289,  -511,   409,  -511,  -511,   285,   330,   264,   209,   209,
    2194,   459,   352,  1557,  -511,  -511,  -511,  -511,  -511,  -511,
    -511,  -511,  -511,  -511,  -511,  -511,  -511,  3006,  3006,  3006,
    3006,  3006,  3006,  3006,  3006,  3006,  3006,  3006,  3006,  3006,
    3006,  3006,  -511,  3006,  3006,  3006,  3006,  3006,  3006,  3006,
    3006,  2244,   386,  -511,  3006,   209,     7,  -511,  3006,  3006,
      66,    18,    -6,  -511,   112,  -511,  -511,  -511,  -511,  -511,
    1128,   390,   428,   375,  3006,  2265,  -511,  -511,  -511,  -511,
    -511,  1594,   367,  3006,   389,   112,  -511,  -511,   -47,  3006,
    3006,  -511,   286,  -511,   406,   407,   437,   174,   203,  -511,
      78,   204,   463,  -511,   429,  -511,   552,  2272,  -511,  3006,
     542,  -511,  -511,   340,   340,   209,   209,   624,   624,   209,
    2866,  2891,   479,   479,  2807,  2782,  2194,  2157,  3006,   412,
     412,  2949,  2949,   412,   412,  1707,  2916,   448,  1744,  -511,
    2194,  -511,  -511,  2044,   434,   488,   458,    52,  -511,  -511,
     429,   429,   236,   255,  -511,  -511,  -511,  2044,  -511,  2044,
    3006,  -511,  2044,  -511,   355,  -511,  -511,   246,  -511,   470,
     113,   210,  -511,   112,   363,  -511,    46,  -511,    49,  -511,
    -511,  -511,  -511,  -511,   474,  -511,    64,   480,  -511,  2320,
     429,   -41,    22,    31,  -511,   483,  1140,  2044,   -53,   481,
    2157,  3006,  -511,  -511,  -511,  -511,   374,  -511,  -511,   482,
     339,  -511,    42,   429,   429,  2044,  -511,    25,   429,   490,
    -511,   116,  -511,  -511,  -511,  -511,  -511,   -38,   485,   698,
    -511,   489,   260,  -511,   495,  -511,   214,  -511,   491,  1857,
    -511,  -511,   496,  -511,    68,  -511,   500,  -511,  -511,  -511,
    -511,  3006,  -511,  2348,  -511,  2757,   824,  -511,   488,  -511,
    -511,   497,  -511,   -16,  -511,   499,  -511,  -511,  -511,  -511,
    -511,   501,   404,  -511,  -511,  -511,  2619,  -511,  2044,  -511,
     370,  3006,  -511,  -511,  -511,   777,  -511,  -511,  -511,   429,
     502,  -511,   112,  1894,  -511,  2044,  -511,  -511,   503,   208,
    -511,  -511,  -511,   504,  -511,  -511,  -511,   519,   222,   231,
     515,   671,   229,  -511,   270,  -511,   531,   529,  -511,   178,
    -511,  1255,  -511,  -511,  -511,  -511,   530,   565,   231,   534,
    -511,  -511,   535,  -511,   536,   537,    71,  -511,   227,   230,
     207,   592,  -511,  -511,  -511,  -511,   784,  2619,  -511,   698,
    -511,   540,  3006,  -511,  -511,   539,   384,  -511,   207,  -511,
     541,  -511,  -511,  2369,   543,  -511,   233,   546,  -511,    73,
     561,  -511,    82,   580,   575,   636,  -511,   588,   596,   597,
    -511,   593,   594,   598,   601,  2655,  -511,  -511,  -511,  -511,
    -511,  1292,  -511,  -511,  -511,  1406,   492,  -511,   234,    27,
    -511,   604,   948,  -511,  -511,  -511,  -511,   611,  -511,   248,
    -511,   614,  -511,   249,  -511,   617,   250,  -511,  -511,  2376,
    2423,  2582,  -511,  -511,  3006,  -511,  -511,  1443,  -511,  -511,
    -511,   327,  -511,  -511,  -511,   251,  -511,  -511,  -511,  -511,
    -511,  -511,  -511,  -511,  -511,  -511,   618,    28,   402,  -511,
     606,  3006,   629,  3006,   694,   237,  3006,  -511,   671,  -511,
     625,   279,    90,  -511,  -511,   623,   258,  -511,   202,  2582,
     405,  2582,   268,   633,  -511,   287,   831,  -511,   683,   673,
     643,  -511,   216,  -511,   641,    45,  -511,   259,  -511,  -511,
    -511,  3006,  -511,  2582,  3006,   644,  2582,  -511,   678,    53,
    -511,  -511,   307,  -511,  -511,  -511,   646,   697,   648,    55,
     462,  -511,   302,   533,   721,   652,   654,   705,   -59,    56,
    -511,  2452,   706,  -511,   665,   697,  3006,   670,  2459,    54,
     219,  -511,   787,  -511,   705,   705,  2499,   706,   672,   705,
     679,   705,   680,   987,  2506,   732,  -511,   706,   326,  -511,
     699,  2007,   700,  -511,  -511,  -511,  2582,   811,   706,   706,
    -511,   103,   732,   705,   706,   705,   706,  -511,   702,  -511,
     703,    19,  2535,    29,   732,  2582,  -511,  -511,  -511,  -511,
    -511,  -511,   732,   732,   715,  -511,    35,   706,   732,   706,
     732,  -511,  -511,   734,  -511,   735,   469,   737,  -511,    36,
    -511,  -511,  -511,  -511,   196,   696,   736,  -511,   739,  -511,
     732,   742,   732,    38,  -511,  -511,  -511,  -511,   744,  -511,
     366,   514,   704,  -511,  -511,  -511,   747,  -511,   749,   751,
    -511,  -511,  -511,  -511,  -511
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -511,  -511,  -511,    37,  -511,   -52,  -511,  -511,   714,  -511,
    -511,  -511,  -511,   819,  -511,  -511,   -14,  -511,   660,   850,
     776,   -20,  -511,   607,  -511,  -304,  -511,   432,   -89,   -10,
    -511,   568,    16,   -74,  -511,   589,  -511,   494,  -511,  -511,
    -511,  -511,  -511,   516,   885,  -511,  -511,   426,   435,  -511,
    -511,   329,  -511,   273,   393,   261,   518,   467,  -511,   460,
    -511,  -511,  -511,  -511,   376,  -510,  -503,  -511,  -511,  -511,
    -511,  -511,  -511,  -511,  -511,  -511,   278,  -511,  -511,  -511,
    -511,   -11,    -7,  -511,  -511,  -511,  -511,  -511,  -511,   532,
    -511,   898,   -49,  -511,  -511,   553,  -511,  -511,  -511,  -511,
    -511,  -511,  -511,   602,   745,   754,   -39,   904,  -511,  -511,
     421,   425,  -511,  -511,   343,  -511,   170,   291,  -511,  -511,
    -511,  -511
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -351
static const short int yytable[] =
{
      52,    55,    57,    59,    89,    89,    94,    75,   188,    71,
      73,    59,    93,    78,   167,   204,    95,   194,   554,   246,
     693,   241,    38,   342,   638,   377,   367,    96,   534,   565,
     697,    66,   346,   191,   108,   109,   708,   718,   110,   729,
      91,    91,    91,   365,   113,    29,   606,   155,   576,   329,
     331,    64,   396,   309,   616,   652,   624,   640,   352,   639,
     195,    85,   196,   267,   353,   334,   590,   244,   592,   390,
     181,   268,   464,   369,   507,   340,    79,    96,   341,   250,
     251,   374,   197,   511,   198,  -109,    32,   247,    33,    34,
     611,   580,    35,   614,   535,   402,   566,   185,   162,    80,
     170,   186,   187,    97,   684,   186,   187,   111,   186,   187,
     248,   266,   197,   242,   198,  -109,   290,    99,    38,   103,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   694,   229,   230,   231,   232,
     233,   234,   235,   236,   238,   493,  -350,   240,   698,  -308,
     347,   235,   243,   680,   709,   719,   101,   730,   289,   332,
     366,   653,   310,   607,   199,   313,   314,   257,   259,   704,
     311,   617,   700,   625,   641,   279,   262,   318,   270,   271,
     335,   336,    59,    59,   391,   392,    66,   465,   466,   508,
     509,   720,   721,   722,   283,   186,   187,   477,   512,   513,
     296,   104,   297,   586,   281,   284,   581,   582,   473,   426,
      40,    41,    42,    43,    44,   383,   356,   601,   343,   685,
     175,   300,   292,   434,   125,   126,   105,   370,   467,    45,
     159,   470,   324,   102,   504,   532,   478,   479,   480,   481,
     482,   483,   484,   266,  -232,  -232,   485,   319,   102,   540,
     543,   546,   560,   315,   389,    46,    47,   280,   159,   584,
     608,   380,  -109,    32,   160,    33,    34,   628,   629,    35,
     587,    48,   427,   474,   -25,   -25,   -25,   -25,   -25,    49,
     578,    50,   339,    38,   602,   547,   282,   285,   438,   451,
      38,   170,  -109,   -25,   355,   353,   439,   384,   106,   561,
    -109,    32,   416,    33,    34,   435,    51,    35,   618,   292,
     468,   168,   486,   471,   487,  -232,   435,   455,   343,   -25,
     -25,   151,   378,   152,   153,   403,    66,   159,   107,   325,
    -109,   541,   544,   547,   561,   -25,   -97,   169,   654,   111,
     361,   585,   609,   -25,   393,   -25,   395,   579,   574,   378,
     167,   201,    94,   171,   159,   125,   126,   320,    93,   129,
     130,   429,    95,   133,   327,   189,   432,   477,   205,   378,
     -25,   -25,   172,   416,   297,   190,   207,   -25,   421,   593,
      40,    41,    42,    43,    44,   159,   174,   447,    91,   448,
     619,   444,   460,  -109,    32,    65,    33,    34,   596,    45,
      35,   445,   272,   273,   159,   407,   478,   479,   480,   481,
     482,   483,   484,   627,  -230,  -230,   485,  -109,    32,   159,
      33,    34,    -4,  -109,    35,    46,    47,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   175,   675,   136,   137,
     378,    48,   378,   159,   174,   495,   559,  -109,   206,    49,
     362,    50,   151,    28,   152,   153,   502,    81,  -109,    32,
    -243,    33,    34,   211,    32,    35,    33,    34,   408,   239,
      35,   316,   317,   254,   320,    81,    51,    32,   527,    33,
      34,   417,   486,    35,   487,  -230,   418,   261,  -109,    71,
     357,   358,   256,    70,   125,   126,   127,   128,   129,   130,
     497,   498,   133,    29,   -32,   263,    40,    41,    42,    43,
      44,   255,   184,   555,   -32,   477,   274,    59,   567,   568,
     278,   591,   159,   277,   151,    45,   152,   153,    40,    41,
      42,    43,    44,    32,    65,    33,    34,   287,   444,    35,
     570,   289,   572,   299,    59,   575,    59,    45,   445,    59,
     304,    46,    47,   291,   478,   479,   480,   481,   482,   483,
     484,   302,  -228,  -228,   485,  -109,    32,    48,    33,    34,
     -15,   305,    35,    46,    47,    49,   308,    50,   626,   159,
     610,   628,   629,   612,    59,   716,   159,    59,   323,    48,
     333,   151,   354,   152,   153,  -109,   349,    49,   337,    50,
     360,   369,    51,   375,   386,   379,  -109,    32,   401,    33,
      34,   382,   388,    35,   643,   648,   340,   404,   422,    59,
     406,   651,   425,   430,    51,    32,   160,    33,    34,    73,
     486,    35,   487,  -228,   443,   433,  -109,    57,   449,   125,
     126,   127,   128,   129,   130,   450,   454,   133,   455,   438,
     136,   137,   462,   459,   461,   463,   494,   496,   515,   503,
     500,   696,   506,  -346,   173,    59,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   510,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   514,   143,   144,   145,
     146,   147,   148,   516,   518,   477,   519,   520,   524,   522,
     523,   525,    40,    41,    42,    43,    44,   569,    40,    41,
      42,    43,    44,   537,    81,  -109,    32,   539,    33,    34,
     542,    45,    35,   545,   564,   573,   151,    45,   152,   153,
     571,   577,   583,   594,   478,   479,   480,   481,   482,   483,
     484,   598,  -234,  -234,   485,  -109,   599,    46,    47,   600,
     605,   615,   613,    46,    47,   620,   621,   623,   632,   149,
     634,   150,   635,    48,   636,   151,   644,   152,   153,    48,
    -346,    49,  -346,    50,   646,   477,   649,    49,  -223,    50,
     663,    40,    41,    42,    43,    44,   667,   665,    40,    41,
      42,    43,    44,   672,   658,   659,   676,   678,    51,   664,
      45,   666,   681,   200,    51,   723,   376,    45,   691,   692,
     486,    25,   487,  -234,   478,   479,   480,   481,   482,   483,
     484,   707,   477,   687,   485,   689,    46,    47,    40,    41,
      42,    43,    44,    46,    47,    40,    41,    42,    43,    44,
     714,   715,    48,   717,   275,   724,    36,    45,   725,    48,
      49,   727,    50,   731,    45,    -3,   732,    49,   733,    50,
     734,   478,   479,   480,   481,   482,   483,   484,   203,   492,
     326,   485,   348,    46,    47,   368,   423,    51,    26,   410,
      46,    47,   505,   499,    51,   458,   420,   588,   647,    48,
     486,   476,   487,   488,   558,   671,    48,    49,   655,    50,
      62,   397,   363,   419,    49,   252,    50,    63,    81,   533,
      32,   531,    33,    34,   253,   603,    35,   661,    82,     0,
       0,     0,     0,     0,    51,     0,   289,    83,    84,     0,
       0,    51,   376,     0,     0,     0,     0,   486,     0,   487,
     597,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,     0,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   -14,   143,   144,   145,   146,   147,   148,   668,     0,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,     0,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
       0,   143,   144,   145,   146,   147,   148,     0,     0,     0,
     662,     0,     0,     0,     0,     0,    32,   160,    33,    34,
     674,     0,    35,     0,   161,    81,  -109,    32,     0,    33,
      34,   682,   683,    35,   149,    82,   150,   688,     0,   690,
     151,     0,   152,   153,    83,    84,     0,   538,  -109,    32,
     160,    33,    34,     0,     0,    35,  -109,   161,     0,     0,
     710,     0,   712,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   149,     0,   150,     0,     0,  -109,   151,
       0,   152,   153,   669,   156,     0,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   157,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,     0,   143,   144,   145,
     146,   147,   148,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,     0,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,     0,   143,   144,   145,   146,   147,   148,
     686,     0,  -109,    32,    65,    33,    34,     0,     0,    35,
       0,     0,   699,     0,     0,     0,     0,     0,     0,     0,
     705,   706,     0,     0,     0,     0,   711,     0,   713,   158,
       0,   150,  -109,     0,     0,   151,     0,   152,   153,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   726,     0,
     728,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   149,     0,   150,     0,
       0,     0,   151,   350,   152,   153,     0,   351,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,     0,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,     0,   143,
     144,   145,   146,   147,   148,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,     0,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,     0,   143,   144,   145,   146,
     147,   148,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   149,   452,   150,     0,     0,     0,   151,     0,   152,
     153,   453,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   149,     0,
     150,     0,     0,     0,   151,     0,   152,   153,   529,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
       0,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,     0,
     143,   144,   145,   146,   147,   148,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,     0,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,     0,   143,   144,   145,
     146,   147,   148,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   149,     0,   150,     0,     0,     0,   151,     0,
     152,   153,   530,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   149,
       0,   150,     0,     0,     0,   151,     0,   152,   153,   557,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,     0,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
       0,   143,   144,   145,   146,   147,   148,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,     0,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,     0,   143,   144,
     145,   146,   147,   148,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   149,     0,   150,     0,     0,   212,   151,
       0,   152,   153,     0,   260,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     149,     0,   150,     0,     0,     0,   151,     0,   152,   153,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,     0,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
       0,   143,   144,   145,   146,   147,   148,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,     0,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,     0,   143,   144,
     145,   146,   147,   148,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   149,   301,   150,     0,     0,     0,   151,
       0,   152,   153,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     149,     0,   150,     0,     0,     0,   151,   303,   152,   153,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,     0,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
       0,   143,   144,   145,   146,   147,   148,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,     0,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,     0,   143,   144,
     145,   146,   147,   148,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   149,     0,   150,     0,     0,     0,   151,
     387,   152,   153,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     149,     0,   150,     0,     0,     0,   151,   424,   152,   153,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,     0,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
       0,   143,   144,   145,   146,   147,   148,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,     0,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,     0,   143,   144,
     145,   146,   147,   148,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   149,   677,   150,     0,     0,     0,   151,
       0,   152,   153,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     149,     0,   150,     0,     0,     0,   151,     0,   152,   153,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,     0,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,     0,     0,
       0,   143,   144,   145,   146,   147,   148,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,     0,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,     0,     0,     0,     0,   143,   144,
     145,   146,   147,   148,     0,     0,   112,     0,     0,     0,
       0,     0,     0,     0,     0,   237,     0,     0,     0,    40,
      41,    42,    43,    44,     0,     0,     0,     0,    40,    41,
      42,    43,    44,   149,     0,   150,   258,     0,    45,   151,
       0,   152,   153,   295,     0,     0,     0,    45,     0,    40,
      41,    42,    43,    44,     0,     0,    40,    41,    42,    43,
      44,     0,     0,     0,    46,    47,     0,     0,    45,     0,
     149,     0,   150,    46,    47,    45,   151,     0,   152,   153,
      48,     0,     0,     0,     0,     0,     0,     0,    49,    48,
      50,   338,     0,     0,    46,    47,     0,    49,     0,    50,
       0,    46,    47,     0,    40,    41,    42,    43,    44,     0,
      48,     0,     0,   -52,    22,    51,     0,    48,    49,   394,
      50,     0,     0,    45,    51,    49,     0,    50,     0,     0,
       0,     0,    40,    41,    42,    43,    44,     0,     0,     0,
     501,     0,     0,     0,     0,    51,     0,   550,     0,    46,
      47,    45,    51,    40,    41,    42,    43,    44,     0,     0,
    -204,  -204,  -204,  -204,  -204,    48,   -52,   -52,   -52,     0,
     -52,   -52,    45,    49,   -52,    50,   -52,    46,    47,  -204,
       0,     0,     0,     0,     0,   -52,   -52,     0,     0,     0,
       0,     0,     0,    48,   552,     0,     0,   -52,    46,    47,
      51,    49,     0,    50,     0,  -204,  -204,  -207,  -207,  -207,
    -207,  -207,     0,     0,    48,     0,     0,     0,     0,     0,
       0,  -204,    49,   642,    50,     0,  -207,     0,    51,  -204,
     650,  -204,     0,     0,     0,     0,    40,    41,    42,    43,
      44,     0,     0,    40,    41,    42,    43,    44,     0,    51,
       0,     0,  -207,  -207,     0,    45,  -204,     0,     0,     0,
       0,     0,    45,     0,     0,     0,     0,     0,  -207,     0,
     660,     0,     0,     0,     0,     0,  -207,   670,  -207,     0,
       0,    46,    47,    40,    41,    42,    43,    44,    46,    47,
      40,    41,    42,    43,    44,     0,     0,    48,     0,     0,
       0,     0,    45,  -207,    48,    49,   695,    50,     0,    45,
       0,     0,    49,     0,    50,     0,     0,     0,     0,    40,
      41,    42,    43,    44,     0,     0,     0,     0,    46,    47,
       0,     0,    51,     0,     0,    46,    47,     0,    45,    51,
       0,     0,     0,     0,    48,     0,     0,     0,     0,     0,
       0,    48,    49,     0,    50,     0,     0,     0,     0,    49,
       0,    50,     0,     0,    46,    47,    40,    41,    42,    43,
      44,     0,     0,     0,     0,     0,     0,     0,     0,    51,
      48,     0,     0,     0,     0,    45,    51,     0,    49,     0,
      50,     0,   478,   479,   480,   481,   482,   483,   484,     0,
       0,     0,   485,    40,    41,    42,    43,    44,     0,     0,
       0,    46,    47,     0,     0,    51,     0,     0,     0,     0,
       0,     0,    45,     0,     0,     0,     0,    48,     0,     0,
       0,     0,     0,     0,     0,    49,     0,    50,     0,    40,
      41,    42,    43,    44,     0,     0,     0,     0,    46,    47,
       0,     0,     0,     0,     0,     0,     0,     0,    45,     0,
       0,     0,    51,     0,    48,     0,     0,     0,   486,     0,
     487,     0,   412,   187,    50,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    46,    47,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    51,
      48,     0,     0,     0,     0,     0,     0,   376,    49,     0,
      50,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    51,     0,     0,     0,     0,
       0,   526,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,     0,     0,     0,
       0,   143,   144,   145,   146,   147,   148,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,     0,     0,     0,     0,     0,   143,   144,   145,   146,
     147,   148,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,     0,     0,     0,     0,     0,
       0,   143,   144,   145,   146,   147,   148,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   149,     0,   150,     0,     0,     0,   151,
       0,   152,   153,     0,     0,     0,     0,     0,     0,     0,
       0,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     150,   135,   136,   137,   151,     0,   152,   153,     0,     0,
     143,   144,   145,   146,   147,   148,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   150,     0,   136,   137,   151,
       0,   152,   153,     0,     0,   143,   144,   145,   146,   147,
     148,   125,   126,   127,   128,   129,   130,   131,   132,   133,
       0,     0,   136,   137,     0,     0,     0,     0,     0,     0,
     143,   144,   145,   146,   147,   148,     0,     0,     0,     0,
       0,     0,     0,     0,   125,   126,   127,   128,   129,   130,
     131,   132,   133,     0,   150,   136,   137,     0,   151,     0,
     152,   153,     0,   143,   144,     0,     0,   147,   148,    40,
      41,    42,    43,    44,     0,     0,     0,     0,     0,   150,
       0,     0,     0,   151,     0,   152,   153,     0,    45,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      40,    41,    42,    43,    44,     0,    22,     0,   151,     0,
     152,   153,     0,     0,    46,    47,     0,     0,     0,    45,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      48,   176,   177,   178,   179,     0,   180,     0,    49,     0,
      50,   151,     0,   152,   153,    46,    47,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -52,   -52,   -52,   -52,
     -52,    48,   -52,   -52,     0,    51,   -52,   -52,   -52,    49,
       0,    50,     0,     0,     0,     0,     0,   -52,   -52,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -52,   -52,
       0,     0,     0,     0,     0,     0,    51
};

static const short int yycheck[] =
{
       7,     8,     9,    10,    24,    25,    26,    18,    82,    16,
      17,    18,    26,    20,    63,   104,    26,    91,   521,     1,
       1,    14,     6,     1,    83,   329,     1,    83,     1,     1,
       1,    15,     1,    85,    41,    42,     1,     1,    45,     1,
      24,    25,    26,     1,    51,    51,     1,    54,   558,     3,
       1,    14,   356,     1,     1,     1,     1,     1,   111,   118,
       1,    24,     3,   110,   117,     1,   569,     1,   571,     1,
      77,   118,     1,   111,     1,   116,     0,    83,   119,   168,
     169,   119,    34,     1,    36,    54,    55,   161,    57,    58,
     593,     1,    61,   596,    67,   111,    68,    81,    61,   116,
     116,    83,    84,    83,     1,    83,    84,   110,    83,    84,
     162,   185,    34,   106,    36,    84,   205,    52,   102,     1,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   116,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   449,   119,   154,   119,    83,
     119,   158,   159,   656,   119,   119,    58,   119,   112,   110,
     118,   107,   110,   118,   116,   254,   255,   174,   175,   679,
     118,   118,   675,   118,   118,     1,   183,   266,   189,   190,
     116,   117,   189,   190,   116,   117,   170,   116,   117,   116,
     117,   701,   702,   703,   116,    83,    84,     1,   116,   117,
     207,    83,   209,     1,     1,     1,   116,   117,     1,     1,
      14,    15,    16,    17,    18,     1,   305,     1,   292,   116,
     117,   228,   206,     1,    15,    16,   108,   111,     1,    33,
     117,     1,   119,   117,     1,     1,    40,    41,    42,    43,
      44,    45,    46,   317,    48,    49,    50,     1,   117,     1,
       1,     1,     1,   260,   343,    59,    60,    83,   117,     1,
       1,     1,    54,    55,    56,    57,    58,    48,    49,    61,
      68,    75,    64,    66,    14,    15,    16,    17,    18,    83,
       1,    85,   289,   267,    68,    83,    83,    83,    57,   111,
     274,   116,    84,    33,   301,   117,    65,    83,    54,    83,
      54,    55,   376,    57,    58,    83,   110,    61,     1,   293,
      83,    83,   116,    83,   118,   119,    83,    83,   392,    59,
      60,   112,   329,   114,   115,   364,   310,   117,    84,   119,
      84,    83,    83,    83,    83,    75,   107,    83,   119,   110,
       1,    83,    83,    83,   351,    85,   353,    68,   111,   356,
     399,    62,   372,   117,   117,    15,    16,   111,   372,    19,
      20,   400,   372,    23,     1,   118,   405,     1,    83,   376,
     110,   111,   117,   447,   381,   118,   112,   117,   385,   111,
      14,    15,    16,    17,    18,   117,   117,   117,   372,   119,
      83,   411,   431,    54,    55,    56,    57,    58,   111,    33,
      61,   411,   116,   117,   117,     1,    40,    41,    42,    43,
      44,    45,    46,   111,    48,    49,    50,    54,    55,   117,
      57,    58,     0,    84,    61,    59,    60,    15,    16,    17,
      18,    19,    20,    21,    22,    23,   117,   111,    26,    27,
     447,    75,   449,   117,   117,   452,   119,    84,   118,    83,
     111,    85,   112,     1,   114,   115,   463,    53,    54,    55,
       1,    57,    58,   111,    55,    61,    57,    58,    64,    83,
      61,   116,   117,    83,   111,    53,   110,    55,   485,    57,
      58,   111,   116,    61,   118,   119,   116,   120,    84,   496,
     116,   117,   117,     1,    15,    16,    17,    18,    19,    20,
     116,   117,    23,    51,    52,   116,    14,    15,    16,    17,
      18,    83,     1,   524,    62,     1,   110,   524,   116,   117,
      83,   116,   117,   116,   112,    33,   114,   115,    14,    15,
      16,    17,    18,    55,    56,    57,    58,    74,   558,    61,
     551,   112,   553,     1,   551,   556,   553,    33,   558,   556,
     116,    59,    60,     1,    40,    41,    42,    43,    44,    45,
      46,   113,    48,    49,    50,    54,    55,    75,    57,    58,
       0,    83,    61,    59,    60,    83,   118,    85,   116,   117,
     591,    48,    49,   594,   591,   116,   117,   594,   118,    75,
     116,   112,   111,   114,   115,    84,   113,    83,   118,    85,
     118,   111,   110,   118,   113,   116,    54,    55,   111,    57,
      58,   116,   116,    61,   621,   626,   116,   118,   116,   626,
     119,   628,   119,   119,   110,    55,    56,    57,    58,   636,
     116,    61,   118,   119,   119,   116,    84,   644,   107,    15,
      16,    17,    18,    19,    20,   116,   116,    23,    83,    57,
      26,    27,   116,   119,   119,   118,   116,   118,    83,   116,
     119,   672,   116,     0,     1,   672,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,   116,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,   116,    34,    35,    36,
      37,    38,    39,    67,   116,     1,   110,   110,   110,   116,
     116,   110,    14,    15,    16,    17,    18,   111,    14,    15,
      16,    17,    18,   119,    53,    54,    55,   116,    57,    58,
     116,    33,    61,   116,   116,    41,   112,    33,   114,   115,
     111,   116,   119,   110,    40,    41,    42,    43,    44,    45,
      46,    68,    48,    49,    50,    84,    83,    59,    60,   116,
     119,    83,   118,    59,    60,   119,    69,   119,    47,   106,
     118,   108,   118,    75,    69,   112,    70,   114,   115,    75,
     117,    83,   119,    85,   119,     1,   116,    83,     1,    85,
     118,    14,    15,    16,    17,    18,   116,   118,    14,    15,
      16,    17,    18,    71,   634,   635,   107,   107,   110,   639,
      33,   641,     1,    99,   110,   119,   118,    33,   116,   116,
     116,     2,   118,   119,    40,    41,    42,    43,    44,    45,
      46,   116,     1,   663,    50,   665,    59,    60,    14,    15,
      16,    17,    18,    59,    60,    14,    15,    16,    17,    18,
     116,   116,    75,   116,   194,   119,     6,    33,   119,    75,
      83,   119,    85,   119,    33,     0,   119,    83,   119,    85,
     119,    40,    41,    42,    43,    44,    45,    46,   102,   447,
     273,    50,   293,    59,    60,   317,   392,   110,     3,   373,
      59,    60,   466,   458,   110,   428,   119,   568,   625,    75,
     116,   441,   118,   119,   528,   644,    75,    83,   630,    85,
      12,   358,   310,   381,    83,   170,    85,    13,    53,   498,
      55,   496,    57,    58,   170,   582,    61,   636,    63,    -1,
      -1,    -1,    -1,    -1,   110,    -1,   112,    72,    73,    -1,
      -1,   110,   118,    -1,    -1,    -1,    -1,   116,    -1,   118,
     119,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,     0,    34,    35,    36,    37,    38,    39,     1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      -1,    34,    35,    36,    37,    38,    39,    -1,    -1,    -1,
     637,    -1,    -1,    -1,    -1,    -1,    55,    56,    57,    58,
     647,    -1,    61,    -1,    63,    53,    54,    55,    -1,    57,
      58,   658,   659,    61,   106,    63,   108,   664,    -1,   666,
     112,    -1,   114,   115,    72,    73,    -1,   119,    54,    55,
      56,    57,    58,    -1,    -1,    61,    84,    63,    -1,    -1,
     687,    -1,   689,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   106,    -1,   108,    -1,    -1,    84,   112,
      -1,   114,   115,   116,     1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    36,
      37,    38,    39,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    -1,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    -1,    34,    35,    36,    37,    38,    39,
     662,    -1,    54,    55,    56,    57,    58,    -1,    -1,    61,
      -1,    -1,   674,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     682,   683,    -1,    -1,    -1,    -1,   688,    -1,   690,   106,
      -1,   108,    84,    -1,    -1,   112,    -1,   114,   115,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   710,    -1,
     712,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   106,    -1,   108,    -1,
      -1,    -1,   112,   113,   114,   115,    -1,   117,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    34,
      35,    36,    37,    38,    39,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    -1,    34,    35,    36,    37,
      38,    39,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   106,   107,   108,    -1,    -1,    -1,   112,    -1,   114,
     115,   116,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   106,    -1,
     108,    -1,    -1,    -1,   112,    -1,   114,   115,   116,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    -1,
      34,    35,    36,    37,    38,    39,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    -1,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    36,
      37,    38,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   106,    -1,   108,    -1,    -1,    -1,   112,    -1,
     114,   115,   116,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   106,
      -1,   108,    -1,    -1,    -1,   112,    -1,   114,   115,   116,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      -1,    34,    35,    36,    37,    38,    39,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      36,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   106,    -1,   108,    -1,    -1,   111,   112,
      -1,   114,   115,    -1,    80,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     106,    -1,   108,    -1,    -1,    -1,   112,    -1,   114,   115,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      -1,    34,    35,    36,    37,    38,    39,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      36,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   106,   107,   108,    -1,    -1,    -1,   112,
      -1,   114,   115,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     106,    -1,   108,    -1,    -1,    -1,   112,   113,   114,   115,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      -1,    34,    35,    36,    37,    38,    39,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      36,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   106,    -1,   108,    -1,    -1,    -1,   112,
     113,   114,   115,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     106,    -1,   108,    -1,    -1,    -1,   112,   113,   114,   115,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      -1,    34,    35,    36,    37,    38,    39,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      36,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   106,   107,   108,    -1,    -1,    -1,   112,
      -1,   114,   115,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     106,    -1,   108,    -1,    -1,    -1,   112,    -1,   114,   115,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    -1,    -1,
      -1,    34,    35,    36,    37,    38,    39,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    -1,    -1,    -1,    -1,    34,    35,
      36,    37,    38,    39,    -1,    -1,     1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,    14,
      15,    16,    17,    18,    -1,    -1,    -1,    -1,    14,    15,
      16,    17,    18,   106,    -1,   108,     1,    -1,    33,   112,
      -1,   114,   115,     1,    -1,    -1,    -1,    33,    -1,    14,
      15,    16,    17,    18,    -1,    -1,    14,    15,    16,    17,
      18,    -1,    -1,    -1,    59,    60,    -1,    -1,    33,    -1,
     106,    -1,   108,    59,    60,    33,   112,    -1,   114,   115,
      75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    75,
      85,     1,    -1,    -1,    59,    60,    -1,    83,    -1,    85,
      -1,    59,    60,    -1,    14,    15,    16,    17,    18,    -1,
      75,    -1,    -1,     0,     1,   110,    -1,    75,    83,     1,
      85,    -1,    -1,    33,   110,    83,    -1,    85,    -1,    -1,
      -1,    -1,    14,    15,    16,    17,    18,    -1,    -1,    -1,
       1,    -1,    -1,    -1,    -1,   110,    -1,     1,    -1,    59,
      60,    33,   110,    14,    15,    16,    17,    18,    -1,    -1,
      14,    15,    16,    17,    18,    75,    53,    54,    55,    -1,
      57,    58,    33,    83,    61,    85,    63,    59,    60,    33,
      -1,    -1,    -1,    -1,    -1,    72,    73,    -1,    -1,    -1,
      -1,    -1,    -1,    75,     1,    -1,    -1,    84,    59,    60,
     110,    83,    -1,    85,    -1,    59,    60,    14,    15,    16,
      17,    18,    -1,    -1,    75,    -1,    -1,    -1,    -1,    -1,
      -1,    75,    83,     1,    85,    -1,    33,    -1,   110,    83,
       1,    85,    -1,    -1,    -1,    -1,    14,    15,    16,    17,
      18,    -1,    -1,    14,    15,    16,    17,    18,    -1,   110,
      -1,    -1,    59,    60,    -1,    33,   110,    -1,    -1,    -1,
      -1,    -1,    33,    -1,    -1,    -1,    -1,    -1,    75,    -1,
       1,    -1,    -1,    -1,    -1,    -1,    83,     1,    85,    -1,
      -1,    59,    60,    14,    15,    16,    17,    18,    59,    60,
      14,    15,    16,    17,    18,    -1,    -1,    75,    -1,    -1,
      -1,    -1,    33,   110,    75,    83,     1,    85,    -1,    33,
      -1,    -1,    83,    -1,    85,    -1,    -1,    -1,    -1,    14,
      15,    16,    17,    18,    -1,    -1,    -1,    -1,    59,    60,
      -1,    -1,   110,    -1,    -1,    59,    60,    -1,    33,   110,
      -1,    -1,    -1,    -1,    75,    -1,    -1,    -1,    -1,    -1,
      -1,    75,    83,    -1,    85,    -1,    -1,    -1,    -1,    83,
      -1,    85,    -1,    -1,    59,    60,    14,    15,    16,    17,
      18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   110,
      75,    -1,    -1,    -1,    -1,    33,   110,    -1,    83,    -1,
      85,    -1,    40,    41,    42,    43,    44,    45,    46,    -1,
      -1,    -1,    50,    14,    15,    16,    17,    18,    -1,    -1,
      -1,    59,    60,    -1,    -1,   110,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    -1,    -1,    -1,    -1,    75,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    83,    -1,    85,    -1,    14,
      15,    16,    17,    18,    -1,    -1,    -1,    -1,    59,    60,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    -1,
      -1,    -1,   110,    -1,    75,    -1,    -1,    -1,   116,    -1,
     118,    -1,    83,    84,    85,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    59,    60,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   110,
      75,    -1,    -1,    -1,    -1,    -1,    -1,   118,    83,    -1,
      85,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   110,    -1,    -1,    -1,    -1,
      -1,   116,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    -1,    -1,    -1,
      -1,    34,    35,    36,    37,    38,    39,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,    37,
      38,    39,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    -1,    -1,    -1,    -1,    -1,
      -1,    34,    35,    36,    37,    38,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   106,    -1,   108,    -1,    -1,    -1,   112,
      -1,   114,   115,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
     108,    25,    26,    27,   112,    -1,   114,   115,    -1,    -1,
      34,    35,    36,    37,    38,    39,    15,    16,    17,    18,
      19,    20,    21,    22,    23,   108,    -1,    26,    27,   112,
      -1,   114,   115,    -1,    -1,    34,    35,    36,    37,    38,
      39,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      -1,    -1,    26,    27,    -1,    -1,    -1,    -1,    -1,    -1,
      34,    35,    36,    37,    38,    39,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    -1,   108,    26,    27,    -1,   112,    -1,
     114,   115,    -1,    34,    35,    -1,    -1,    38,    39,    14,
      15,    16,    17,    18,    -1,    -1,    -1,    -1,    -1,   108,
      -1,    -1,    -1,   112,    -1,   114,   115,    -1,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      14,    15,    16,    17,    18,    -1,     1,    -1,   112,    -1,
     114,   115,    -1,    -1,    59,    60,    -1,    -1,    -1,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      75,    76,    77,    78,    79,    -1,    81,    -1,    83,    -1,
      85,   112,    -1,   114,   115,    59,    60,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    51,    52,    53,    54,
      55,    75,    57,    58,    -1,   110,    61,    62,    63,    83,
      -1,    85,    -1,    -1,    -1,    -1,    -1,    72,    73,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    84,
      -1,    -1,    -1,    -1,    -1,    -1,   110
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   122,     1,   123,   134,   134,   165,   124,     1,    51,
     126,   127,    55,    57,    58,    61,   140,   141,   153,   159,
      14,    15,    16,    17,    18,    33,    59,    60,    75,    83,
      85,   110,   203,   207,   209,   203,   176,   203,   202,   203,
     211,   212,   212,   228,   124,    56,   153,   224,   225,   226,
       1,   203,   232,   203,   238,   202,   239,   240,   203,     0,
     116,    53,    63,    72,    73,   124,   135,   136,   137,   142,
     150,   153,   161,   137,   142,   150,    83,    83,   129,    52,
     128,    58,   117,     1,    83,   108,    54,    84,   203,   203,
     203,   110,     1,   203,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    34,    35,    36,    37,    38,    39,   106,
     108,   112,   114,   115,   208,   203,     1,    14,   106,   117,
      56,    63,   124,   142,   153,   213,   217,   213,    83,    83,
     116,   117,   117,     1,   117,   117,    76,    77,    78,    79,
      81,   203,   241,   242,     1,   153,    83,    84,   154,   118,
     118,   126,   143,   144,   154,     1,     3,    34,    36,   116,
     129,    62,   130,   141,   149,    83,   118,   112,   160,   204,
     205,   111,   111,   203,   203,   203,   203,   203,   203,   203,
     203,   203,   203,   203,   203,   203,   203,   203,   206,   203,
     203,   203,   203,   203,   203,   203,   203,     1,   203,    83,
     203,    14,   106,   203,     1,   214,     1,   154,   126,   154,
     149,   149,   225,   226,    83,    83,   117,   203,     1,   203,
      80,   120,   203,   116,   151,   152,   154,   110,   118,   139,
     202,   202,   116,   117,   110,   139,   149,   116,    83,     1,
      83,     1,    83,   116,     1,    83,   131,    74,   132,   112,
     149,     1,   153,   155,   156,     1,   203,   203,   210,     1,
     203,   107,   113,   113,   116,    83,   215,   216,   118,     1,
     110,   118,   223,   149,   149,   203,   116,   117,   149,     1,
     111,   140,   163,   118,   119,   119,   144,     1,   138,     3,
     145,     1,   110,   116,     1,   116,   117,   118,     1,   203,
     116,   119,     1,   154,   157,   158,     1,   119,   156,   113,
     113,   117,   111,   117,   111,   203,   149,   116,   117,   221,
     118,     1,   111,   224,   222,     1,   118,     1,   152,   111,
     111,   164,   165,   162,   119,   118,   118,   146,   203,   116,
       1,   125,   116,     1,    83,   133,   113,   113,   116,   149,
       1,   116,   117,   203,     1,   203,   146,   216,   227,   228,
     220,   111,   111,   227,   118,   218,   119,     1,    64,   166,
     164,   185,    83,   146,   147,   148,   154,   111,   116,   210,
     119,   203,   116,   158,   113,   119,     1,    64,   229,   227,
     119,   219,   227,   116,     1,    83,   167,   168,    57,    65,
     178,   179,   180,   119,   142,   150,   186,   117,   119,   107,
     116,   111,   107,   116,   116,    83,   230,   231,   178,   119,
     227,   119,   116,   118,     1,   116,   117,     1,    83,   182,
       1,    83,   181,     1,    66,   169,   180,     1,    40,    41,
      42,    43,    44,    45,    46,    50,   116,   118,   119,   183,
     187,   203,   148,   146,   116,   203,   118,   116,   117,   169,
     119,     1,   203,   116,     1,   168,   116,     1,   116,   117,
     116,     1,   116,   117,   116,    83,    67,   170,   116,   110,
     110,   190,   116,   116,   110,   110,   116,   203,   184,   116,
     116,   232,     1,   231,     1,    67,   233,   119,   119,   116,
       1,    83,   116,     1,    83,   116,     1,    83,   171,   172,
       1,   188,     1,   189,   187,   202,   191,   116,   185,   119,
       1,    83,   234,   235,   116,     1,    68,   116,   117,   111,
     202,   111,   202,    41,   111,   202,   186,   116,     1,    68,
       1,   116,   117,   119,     1,    83,     1,    68,   172,   173,
     187,   116,   187,   111,   110,   192,   111,   119,    68,    83,
     116,     1,    68,   235,   236,   119,     1,   118,     1,    83,
     202,   187,   202,   118,   187,    83,     1,   118,     1,    83,
     119,    69,   174,   119,     1,   118,   116,   111,    48,    49,
     196,   197,    47,   193,   118,   118,    69,   237,    83,   118,
       1,   118,     1,   203,    70,   175,   119,   174,   202,   116,
       1,   203,     1,   107,   119,   197,   194,   195,   237,   237,
       1,   238,   175,   118,   237,   118,   237,   116,     1,   116,
       1,   176,    71,   177,   175,   111,   107,   107,   107,   200,
     187,     1,   175,   175,     1,   116,   177,   237,   175,   237,
     175,   116,   116,     1,   116,     1,   202,     1,   119,   177,
     187,   199,   198,   201,   186,   177,   177,   116,     1,   119,
     175,   177,   175,   177,   116,   116,   116,   116,     1,   119,
     186,   186,   186,   119,   119,   119,   177,   119,   177,     1,
     119,   119,   119,   119,   119
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
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


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
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)		\
   ((Current).first_line   = (Rhs)[1].first_line,	\
    (Current).first_column = (Rhs)[1].first_column,	\
    (Current).last_line    = (Rhs)[N].last_line,	\
    (Current).last_column  = (Rhs)[N].last_column)
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

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

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value, Location);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short int *bottom, short int *top)
#else
static void
yy_stack_print (bottom, top)
    short int *bottom;
    short int *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
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

#if defined (YYMAXDEPTH) && YYMAXDEPTH == 0
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
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;
  (void) yylocationp;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yytype, yyvaluep, yylocationp)
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;
  (void) yylocationp;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short int yyssa[YYINITDEPTH];
  short int *yyss = yyssa;
  register short int *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  YYLTYPE *yylerrsp;

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

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short int *yyss1 = yyss;
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
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short int *yyss1 = yyss;
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

      if (yyss + yystacksize - 1 <= yyssp)
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
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
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

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
  YYLLOC_DEFAULT (yyloc, yylsp - yylen, yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 259 "parser.yy"
    { CALL(yylsp[0], yylsp[0], done()); }
    break;

  case 3:
#line 260 "parser.yy"
    { }
    break;

  case 4:
#line 261 "parser.yy"
    { }
    break;

  case 5:
#line 262 "parser.yy"
    { }
    break;

  case 6:
#line 263 "parser.yy"
    { }
    break;

  case 7:
#line 264 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SYSTEM));
	}
    break;

  case 8:
#line 267 "parser.yy"
    { g_parameter_count = yyvsp[0].number; }
    break;

  case 9:
#line 268 "parser.yy"
    { }
    break;

  case 10:
#line 269 "parser.yy"
    { CALL(yylsp[0], yylsp[0], procGuard()); }
    break;

  case 11:
#line 270 "parser.yy"
    { }
    break;

  case 12:
#line 271 "parser.yy"
    { CALL(yylsp[0], yylsp[0], procUpdate()); }
    break;

  case 13:
#line 272 "parser.yy"
    { CALL(yylsp[0], yylsp[0], done()); }
    break;

  case 14:
#line 273 "parser.yy"
    { }
    break;

  case 15:
#line 274 "parser.yy"
    { }
    break;

  case 16:
#line 275 "parser.yy"
    { }
    break;

  case 17:
#line 276 "parser.yy"
    { g_parameter_count = yyvsp[0].number; }
    break;

  case 18:
#line 277 "parser.yy"
    { }
    break;

  case 19:
#line 278 "parser.yy"
    { CALL(yylsp[0], yylsp[0], procGuard()); }
    break;

  case 20:
#line 279 "parser.yy"
    { CALL(yylsp[0], yylsp[0], procUpdate()); }
    break;

  case 21:
#line 280 "parser.yy"
    {}
    break;

  case 22:
#line 281 "parser.yy"
    {}
    break;

  case 25:
#line 290 "parser.yy"
    {
          CALL(yylsp[-3], yylsp[-1], instantiationBegin(yyvsp[-3].string, yyvsp[-1].string));
	}
    break;

  case 26:
#line 292 "parser.yy"
    {
	  CALL(yylsp[-7], yylsp[0], instantiationEnd(yyvsp[-7].string, yyvsp[-5].string, yyvsp[-2].number));
	}
    break;

  case 27:
#line 295 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_ARGLIST));
	}
    break;

  case 28:
#line 298 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));
	}
    break;

  case 29:
#line 301 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LPAREN));
	}
    break;

  case 30:
#line 304 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_ASSIGN));
	}
    break;

  case 36:
#line 322 "parser.yy"
    { CALL(yylsp[0], yylsp[0], lowPriority(yyvsp[0].string)); }
    break;

  case 37:
#line 323 "parser.yy"
    { CALL(yylsp[0], yylsp[0], samePriority(yyvsp[0].string)); }
    break;

  case 38:
#line 324 "parser.yy"
    { CALL(yylsp[0], yylsp[0], higherPriority(yyvsp[0].string)); }
    break;

  case 42:
#line 331 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 43:
#line 334 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_PROCID));
	}
    break;

  case 44:
#line 340 "parser.yy"
    { CALL(yylsp[0], yylsp[0], process(yyvsp[0].string)); }
    break;

  case 45:
#line 341 "parser.yy"
    { CALL(yylsp[0], yylsp[0], process(yyvsp[0].string)); }
    break;

  case 46:
#line 342 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_PROCID_));
	}
    break;

  case 50:
#line 353 "parser.yy"
    {
            CALL(yylsp[-3], yylsp[-1], declProgress(true));
        }
    break;

  case 51:
#line 356 "parser.yy"
    {
            CALL(yylsp[-1], yylsp[-1], declProgress(false));
        }
    break;

  case 60:
#line 371 "parser.yy"
    { CALL(yylsp[-1], yylsp[-1], beforeUpdate()); }
    break;

  case 61:
#line 373 "parser.yy"
    { CALL(yylsp[-1], yylsp[-1], afterUpdate()); }
    break;

  case 62:
#line 376 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], declFuncBegin(yyvsp[-1].string, yyvsp[0].number));
	}
    break;

  case 63:
#line 379 "parser.yy"
    { 
	  CALL(yylsp[-7], yylsp[-1], declFuncEnd());
	}
    break;

  case 64:
#line 382 "parser.yy"
    {}
    break;

  case 65:
#line 385 "parser.yy"
    { yyval.number = 0; }
    break;

  case 66:
#line 386 "parser.yy"
    { yyval.number = yyvsp[-1].number; }
    break;

  case 67:
#line 387 "parser.yy"
    { 
	  yyval.number = 0; 
	}
    break;

  case 68:
#line 393 "parser.yy"
    { yyval.number = 1; }
    break;

  case 69:
#line 394 "parser.yy"
    { yyval.number = yyvsp[-2].number+1; }
    break;

  case 70:
#line 398 "parser.yy"
    {
          CALL(yylsp[-3], yylsp[0], declParameter(yyvsp[-1].string, true, yyvsp[0].number));
          CALL(yylsp[-3], yylsp[0], declParameterEnd());
	}
    break;

  case 71:
#line 402 "parser.yy"
    {
          CALL(yylsp[-2], yylsp[0], declParameter(yyvsp[-1].string, false, yyvsp[0].number));
          CALL(yylsp[-2], yylsp[0], declParameterEnd());
	}
    break;

  case 72:
#line 406 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_PARAMID));
	}
    break;

  case 73:
#line 412 "parser.yy"
    { 
          CALL(yylsp[-2], yylsp[0], declVarEnd());
	}
    break;

  case 76:
#line 423 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], declVar(yyvsp[-2].string, yyvsp[-1].number, yyvsp[0].flag));
	}
    break;

  case 77:
#line 429 "parser.yy"
    { yyval.flag = false; }
    break;

  case 78:
#line 430 "parser.yy"
    { yyval.flag = true; }
    break;

  case 80:
#line 435 "parser.yy"
    {	
	  CALL(yylsp[-2], yylsp[0], declInitialiserList(yyvsp[-1].number));
	}
    break;

  case 81:
#line 441 "parser.yy"
    { yyval.number = 1; }
    break;

  case 82:
#line 442 "parser.yy"
    { yyval.number = yyvsp[-2].number+1; }
    break;

  case 83:
#line 446 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], declFieldInit(yyvsp[-2].string));
	}
    break;

  case 84:
#line 449 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], declFieldInit(""));
	}
    break;

  case 85:
#line 455 "parser.yy"
    { yyval.number=0; }
    break;

  case 86:
#line 456 "parser.yy"
    { yyval.number=yyvsp[-3].number+1; }
    break;

  case 87:
#line 457 "parser.yy"
    {
	  CALL(yylsp[-1], yylsp[-1], exprNat(1));
	  REPORT_ERROR(last_loc, TypeException(PE_CONST_EXP));
	  yyval.number=yyvsp[-3].number+1; 
	}
    break;

  case 88:
#line 465 "parser.yy"
    {
	  CALL(yylsp[-3], yylsp[0], declTypeDefEnd());
	}
    break;

  case 89:
#line 468 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], declTypeDefEnd());  
	}
    break;

  case 90:
#line 479 "parser.yy"
    { yyval.number = 1; }
    break;

  case 91:
#line 480 "parser.yy"
    { yyval.number = yyvsp[-2].number+1; }
    break;

  case 92:
#line 481 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_TYPEID_));
	  yyval.number = yyvsp[-2].number+1; 
	}
    break;

  case 93:
#line 488 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], declTypeDef(yyvsp[-1].string, yyvsp[0].number));
	}
    break;

  case 94:
#line 494 "parser.yy"
    { 
	    CALL((yyvsp[-2].number == ParserBuilder::PREFIX_NONE ? yylsp[-1] : yylsp[-2]), yylsp[0],
		 typeName(yyvsp[-2].number, yyvsp[-1].string, yyvsp[0].number));
	}
    break;

  case 95:
#line 498 "parser.yy"
    { 
	    CALL((yyvsp[-4].number == ParserBuilder::PREFIX_NONE ? yylsp[-3] : yylsp[-4]), yylsp[0],
	       typeStruct(yyvsp[-4].number, yyvsp[-1].number));
	}
    break;

  case 96:
#line 502 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBER));
	  CALL((yyvsp[-4].number == ParserBuilder::PREFIX_NONE ? yylsp[-3] : yylsp[-4]), yylsp[0],
	       typeStruct(yyvsp[-4].number, 0));
	}
    break;

  case 97:
#line 510 "parser.yy"
    { strncpy(yyval.string, yyvsp[0].string, MAXLEN); }
    break;

  case 98:
#line 511 "parser.yy"
    { strncpy(yyval.string, yyvsp[0].string, MAXLEN); }
    break;

  case 99:
#line 515 "parser.yy"
    { yyval.number=yyvsp[0].number; }
    break;

  case 100:
#line 516 "parser.yy"
    { yyval.number=yyvsp[-1].number+yyvsp[0].number; }
    break;

  case 101:
#line 517 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBER));
	  yyval.number=yyvsp[-1].number; 
	}
    break;

  case 102:
#line 524 "parser.yy"
    {
	  yyval.number = yyvsp[-1].number; 
	  CALL(yylsp[-2], yylsp[0], structFieldEnd());
	}
    break;

  case 103:
#line 528 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));	  
	  yyval.number = yyvsp[-2].number; 
	  CALL(yylsp[-3], yylsp[0], structFieldEnd());
	}
    break;

  case 104:
#line 533 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBERID));	  
	}
    break;

  case 105:
#line 536 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBERTYPE));	  
	}
    break;

  case 106:
#line 542 "parser.yy"
    { yyval.number=1; }
    break;

  case 107:
#line 543 "parser.yy"
    { yyval.number=yyvsp[-2].number+1; }
    break;

  case 108:
#line 547 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], structField(yyvsp[-1].string, yyvsp[0].number));
	}
    break;

  case 109:
#line 553 "parser.yy"
    { yyval.number = ParserBuilder::PREFIX_NONE; }
    break;

  case 110:
#line 554 "parser.yy"
    { yyval.number = ParserBuilder::PREFIX_URGENT; }
    break;

  case 111:
#line 555 "parser.yy"
    { yyval.number = ParserBuilder::PREFIX_BROADCAST; }
    break;

  case 112:
#line 556 "parser.yy"
    { yyval.number = ParserBuilder::PREFIX_URGENT_BROADCAST; }
    break;

  case 113:
#line 557 "parser.yy"
    { yyval.number = ParserBuilder::PREFIX_CONST; }
    break;

  case 114:
#line 558 "parser.yy"
    { yyval.number = ParserBuilder::PREFIX_META; }
    break;

  case 115:
#line 562 "parser.yy"
    { yyval.number = 0; }
    break;

  case 116:
#line 563 "parser.yy"
    { yyval.number = 1; }
    break;

  case 117:
#line 564 "parser.yy"
    { yyval.number = 2; }
    break;

  case 118:
#line 565 "parser.yy"
    {
	    yyval.number = 0;
        }
    break;

  case 119:
#line 575 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[0], procBegin(yyvsp[-2].string, yyvsp[-1].number));
	}
    break;

  case 120:
#line 578 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], procEnd());
	}
    break;

  case 121:
#line 581 "parser.yy"
    {
	  utap_error(TypeException(PE_LPAREN), 
		     yylsp[0].first_line, yylsp[0].first_column, 
		     yylsp[0].last_line, yylsp[0].last_column);
	  CALL(yylsp[-2], yylsp[0], procBegin(yyvsp[-1].string, 0));
	}
    break;

  case 122:
#line 586 "parser.yy"
    {
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;

  case 129:
#line 604 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 130:
#line 607 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATE_DECL));
	}
    break;

  case 134:
#line 616 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATE_DECL_));
	}
    break;

  case 135:
#line 622 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], procState(yyvsp[0].string, false));
	}
    break;

  case 136:
#line 625 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[0], procState(yyvsp[-3].string, true));
	}
    break;

  case 137:
#line 628 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_INV));
	  CALL(yylsp[-3], yylsp[0], procState(yyvsp[-3].string, false));
	}
    break;

  case 138:
#line 635 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], procStateInit(yyvsp[-1].string));
	}
    break;

  case 142:
#line 644 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 145:
#line 652 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS_DECL_));
	}
    break;

  case 146:
#line 658 "parser.yy"
    { 
	  strcpy(rootTransId, yyvsp[-7].string); 
	  CALL(yylsp[-7], yylsp[0], procEdge(yyvsp[-7].string, yyvsp[-5].string));
	}
    break;

  case 147:
#line 662 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  strcpy(rootTransId, yyvsp[-8].string); 
	  CALL(yylsp[-8], yylsp[0], procEdge(yyvsp[-8].string, yyvsp[-6].string));
	}
    break;

  case 148:
#line 667 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	}
    break;

  case 149:
#line 670 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;

  case 150:
#line 673 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_ARROW));
	}
    break;

  case 151:
#line 679 "parser.yy"
    { 
	  CALL(yylsp[-6], yylsp[0], procEdge(rootTransId, yyvsp[-5].string));
	}
    break;

  case 152:
#line 682 "parser.yy"
    { 
	  REPORT_ERROR(yylloc, TypeException(PE_RBRACE));
	  CALL(yylsp[-7], yylsp[0], procEdge(rootTransId, yyvsp[-6].string));
	}
    break;

  case 153:
#line 686 "parser.yy"
    { 
	  REPORT_ERROR(yylloc, TypeException(PE_LBRACE));
	}
    break;

  case 154:
#line 689 "parser.yy"
    { 
	  REPORT_ERROR(yylloc, TypeException(PE_STATEID));
	}
    break;

  case 157:
#line 698 "parser.yy"
    {
	  CALL(yylsp[-1], yylsp[-1], procGuard());
        }
    break;

  case 158:
#line 701 "parser.yy"
    {
	  REPORT_ERROR(yylloc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-2], yylsp[-1], procGuard());
	}
    break;

  case 159:
#line 705 "parser.yy"
    {
	  REPORT_ERROR(yylloc, TypeException(PE_GUARD_EXP));
	}
    break;

  case 162:
#line 713 "parser.yy"
    {
	  REPORT_ERROR(yylloc, TypeException(PE_SEMICOLON));
	}
    break;

  case 163:
#line 716 "parser.yy"
    {
	  REPORT_ERROR(yylloc, TypeException(PE_SEMICOLON));
	}
    break;

  case 164:
#line 719 "parser.yy"
    {
	  REPORT_ERROR(yylloc, TypeException(PE_SYNC_EXP));
	}
    break;

  case 165:
#line 725 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], procSync(SYNC_BANG));
	}
    break;

  case 166:
#line 728 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_BANG));
	  CALL(yylsp[-2], yylsp[-1], procSync(SYNC_QUE));
	}
    break;

  case 167:
#line 732 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], procSync(SYNC_QUE));
	}
    break;

  case 168:
#line 735 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_QUE));
	  CALL(yylsp[-2], yylsp[-1], procSync(SYNC_QUE));
	}
    break;

  case 169:
#line 739 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_BANGQUE));
	  CALL(yylsp[-1], yylsp[0], procSync(SYNC_QUE));
	}
    break;

  case 171:
#line 747 "parser.yy"
    {
	  CALL(yylsp[-1], yylsp[-1], procUpdate());	  
	}
    break;

  case 172:
#line 750 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_ASSIGN_EXP));
	}
    break;

  case 178:
#line 764 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 179:
#line 767 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 180:
#line 770 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;

  case 181:
#line 773 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;

  case 182:
#line 779 "parser.yy"
    {}
    break;

  case 183:
#line 780 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 184:
#line 783 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 185:
#line 786 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;

  case 186:
#line 789 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;

  case 187:
#line 795 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], procStateCommit(yyvsp[0].string));
	}
    break;

  case 188:
#line 798 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], procStateCommit(yyvsp[0].string));
	}
    break;

  case 189:
#line 801 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID_));
	}
    break;

  case 190:
#line 807 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], procStateUrgent(yyvsp[0].string));
	}
    break;

  case 191:
#line 810 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], procStateUrgent(yyvsp[0].string));
	}
    break;

  case 192:
#line 813 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID_));
	}
    break;

  case 193:
#line 824 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], blockBegin());
	}
    break;

  case 194:
#line 827 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[-1], blockEnd());
	}
    break;

  case 202:
#line 846 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], emptyStatement());
	}
    break;

  case 203:
#line 849 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], exprStatement());
	}
    break;

  case 204:
#line 852 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], forBegin());
	}
    break;

  case 205:
#line 855 "parser.yy"
    { 
	    CALL(yylsp[-7], yylsp[-1], forEnd());
	  }
    break;

  case 207:
#line 859 "parser.yy"
    {
	    CALL(yylsp[-1], yylsp[0], whileBegin());
	}
    break;

  case 208:
#line 862 "parser.yy"
    { 
	    CALL(yylsp[-3], yylsp[-2], whileEnd());
	  }
    break;

  case 210:
#line 866 "parser.yy"
    { 
	    CALL(yylsp[0], yylsp[0], doWhileBegin());
	}
    break;

  case 211:
#line 869 "parser.yy"
    { 
	    CALL(yylsp[-6], yylsp[-1], doWhileEnd());
	  }
    break;

  case 212:
#line 872 "parser.yy"
    { 
	    CALL(yylsp[-1], yylsp[0], ifBegin());
	}
    break;

  case 214:
#line 876 "parser.yy"
    { 
	    CALL(yylsp[-1], yylsp[0], breakStatement());
	  }
    break;

  case 215:
#line 879 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], continueStatement());
	}
    break;

  case 216:
#line 882 "parser.yy"
    { 
	    CALL(yylsp[-3], yylsp[0], switchBegin());
	}
    break;

  case 217:
#line 885 "parser.yy"
    { 
	       CALL(yylsp[-3], yylsp[-1], switchEnd());
	   }
    break;

  case 218:
#line 888 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], returnStatement(true));
	}
    break;

  case 219:
#line 891 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], returnStatement(false));
	}
    break;

  case 220:
#line 897 "parser.yy"
    { 
	  CALL(position_t(), position_t(), ifEnd(false));
	}
    break;

  case 221:
#line 900 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], ifElse());
	}
    break;

  case 222:
#line 903 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[-1], ifEnd(true));
	  }
    break;

  case 223:
#line 906 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], ifElse());
	}
    break;

  case 224:
#line 909 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-1], yylsp[-1], ifEnd(true));
	  }
    break;

  case 227:
#line 921 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], caseBegin());
	}
    break;

  case 228:
#line 924 "parser.yy"
    { 
	    CALL(yylsp[-1], yylsp[-1], caseEnd());
	  }
    break;

  case 229:
#line 927 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], caseBegin());
	}
    break;

  case 230:
#line 930 "parser.yy"
    {
	    REPORT_ERROR(last_loc, TypeException(PE_EXPR)); 
	    CALL(yylsp[-1], yylsp[-1], caseEnd());
	  }
    break;

  case 231:
#line 934 "parser.yy"
    { 
	    CALL(yylsp[-1], yylsp[0], defaultBegin());
	}
    break;

  case 232:
#line 937 "parser.yy"
    { 
	    CALL(yylsp[-1], yylsp[-1], defaultEnd());
	  }
    break;

  case 233:
#line 940 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_COLON)); 
	  CALL(yylsp[-2], yylsp[0], defaultBegin());
	}
    break;

  case 234:
#line 944 "parser.yy"
    { 
	    CALL(yylsp[-1], yylsp[-1], defaultEnd());
	  }
    break;

  case 236:
#line 951 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprComma());
	}
    break;

  case 237:
#line 956 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], exprFalse());
	}
    break;

  case 238:
#line 959 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], exprTrue());
	}
    break;

  case 239:
#line 962 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], exprNat(yyvsp[0].number));
	}
    break;

  case 240:
#line 965 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], exprId(yyvsp[0].string));
	}
    break;

  case 241:
#line 968 "parser.yy"
    {
	    CALL(yylsp[-1], yylsp[0], exprCallBegin(yyvsp[-1].string));	    
	  }
    break;

  case 242:
#line 970 "parser.yy"
    { 
	    CALL(yylsp[-4], yylsp[0], exprCallEnd(yyvsp[-1].number));
	}
    break;

  case 243:
#line 973 "parser.yy"
    {
	    CALL(yylsp[-1], yylsp[0], exprCallBegin(yyvsp[-1].string));
	  }
    break;

  case 244:
#line 975 "parser.yy"
    {   
	    REPORT_ERROR(last_loc, TypeException(PE_ARGLIST));
	    CALL(yylsp[-4], yylsp[0], exprCallEnd(0));
	}
    break;

  case 245:
#line 979 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[0], exprArray());
	}
    break;

  case 246:
#line 982 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-3], yylsp[0], exprFalse());
	}
    break;

  case 248:
#line 987 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprFalse());
	}
    break;

  case 249:
#line 991 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], exprPostIncrement());
	}
    break;

  case 250:
#line 994 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], exprPreIncrement());
	}
    break;

  case 251:
#line 997 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], exprPostDecrement());
	}
    break;

  case 252:
#line 1000 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], exprPreDecrement());
	}
    break;

  case 253:
#line 1003 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], exprUnary(yyvsp[-1].kind));
	}
    break;

  case 254:
#line 1006 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(LT));
	}
    break;

  case 255:
#line 1009 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(LE));
	}
    break;

  case 256:
#line 1012 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(EQ));
	}
    break;

  case 257:
#line 1015 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(NEQ));
	}
    break;

  case 258:
#line 1018 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(GT));
	}
    break;

  case 259:
#line 1021 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(GE));
	}
    break;

  case 260:
#line 1024 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(PLUS));
	}
    break;

  case 261:
#line 1027 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(MINUS));
	}
    break;

  case 262:
#line 1030 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(MULT));
	}
    break;

  case 263:
#line 1033 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(DIV));
	}
    break;

  case 264:
#line 1036 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(MOD));
	}
    break;

  case 265:
#line 1039 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_AND));
	}
    break;

  case 266:
#line 1042 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_OR));
	}
    break;

  case 267:
#line 1045 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_XOR));
	}
    break;

  case 268:
#line 1048 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_LSHIFT));
	}
    break;

  case 269:
#line 1051 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_RSHIFT));
	}
    break;

  case 270:
#line 1054 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(AND));
	}
    break;

  case 271:
#line 1057 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(OR));
	}
    break;

  case 272:
#line 1060 "parser.yy"
    { 
	  CALL(yylsp[-4], yylsp[0], exprInlineIf());
	}
    break;

  case 273:
#line 1063 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprDot(yyvsp[0].string));
	}
    break;

  case 274:
#line 1066 "parser.yy"
    {
	    CALL(yylsp[-1], yylsp[0], exprUnary(RATE));
        }
    break;

  case 275:
#line 1069 "parser.yy"
    {
	  CALL(yylsp[0], yylsp[0], exprDeadlock());
	}
    break;

  case 276:
#line 1072 "parser.yy"
    {  
	  CALL(yylsp[-1], yylsp[-1], exprUnary(NOT));
	}
    break;

  case 277:
#line 1074 "parser.yy"
    {
	  CALL(yylsp[-1], yylsp[-1], exprBinary(OR));
	}
    break;

  case 278:
#line 1077 "parser.yy"
    {
	  CALL(yylsp[-2], yylsp[0], exprBinary(AND));
        }
    break;

  case 279:
#line 1080 "parser.yy"
    {
	  CALL(yylsp[-2], yylsp[0], exprBinary(OR));
        }
    break;

  case 280:
#line 1083 "parser.yy"
    {
	  CALL(yylsp[-1], yylsp[0], exprUnary(NOT));
        }
    break;

  case 281:
#line 1086 "parser.yy"
    {
	    CALL(yylsp[-2], yylsp[0], exprBinary(MIN));
        }
    break;

  case 282:
#line 1089 "parser.yy"
    {
	    CALL(yylsp[-2], yylsp[0], exprBinary(MAX));
        }
    break;

  case 284:
#line 1096 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprAssignment(yyvsp[-1].kind));
	}
    break;

  case 285:
#line 1102 "parser.yy"
    { yyval.kind = ASSIGN; }
    break;

  case 286:
#line 1103 "parser.yy"
    { yyval.kind = ASSPLUS; }
    break;

  case 287:
#line 1104 "parser.yy"
    { yyval.kind = ASSMINUS; }
    break;

  case 288:
#line 1105 "parser.yy"
    { yyval.kind = ASSDIV; }
    break;

  case 289:
#line 1106 "parser.yy"
    { yyval.kind = ASSMOD; }
    break;

  case 290:
#line 1107 "parser.yy"
    { yyval.kind = ASSMULT; }
    break;

  case 291:
#line 1108 "parser.yy"
    { yyval.kind = ASSAND; }
    break;

  case 292:
#line 1109 "parser.yy"
    { yyval.kind = ASSOR; }
    break;

  case 293:
#line 1110 "parser.yy"
    { yyval.kind = ASSXOR; }
    break;

  case 294:
#line 1111 "parser.yy"
    { yyval.kind = ASSLSHIFT; }
    break;

  case 295:
#line 1112 "parser.yy"
    { yyval.kind = ASSRSHIFT; }
    break;

  case 296:
#line 1117 "parser.yy"
    { yyval.kind = MINUS; }
    break;

  case 297:
#line 1118 "parser.yy"
    { yyval.kind = PLUS; }
    break;

  case 298:
#line 1119 "parser.yy"
    { yyval.kind = NOT; }
    break;

  case 299:
#line 1124 "parser.yy"
    { yyval.number=0; }
    break;

  case 300:
#line 1125 "parser.yy"
    { 
	    yyval.number=1; 
	    CALL(yylsp[0], yylsp[0], exprArg(0));
	}
    break;

  case 301:
#line 1129 "parser.yy"
    { 
	    yyval.number=yyvsp[-2].number+1; 
	    CALL(yylsp[0], yylsp[0], exprArg(yyvsp[-2].number));
	}
    break;

  case 302:
#line 1133 "parser.yy"
    { 
	  yyval.number=yyvsp[-2].number+1; 
	  REPORT_ERROR(last_loc, TypeException(PE_ARGLIST_));
	  CALL(yylsp[0], yylsp[0], exprArg(yyvsp[-2].number));
	}
    break;

  case 308:
#line 1156 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], typeName(ParserBuilder::PREFIX_CONST, "int", 0));
	}
    break;

  case 309:
#line 1158 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[-1], declVarEnd());
	}
    break;

  case 311:
#line 1164 "parser.yy"
    { yyval.number=1; }
    break;

  case 312:
#line 1165 "parser.yy"
    { yyval.number=yyvsp[-2].number+1; }
    break;

  case 313:
#line 1169 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], declVar(yyvsp[-2].string, yyvsp[-1].number, true));
	}
    break;

  case 314:
#line 1178 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[0], procBegin(yyvsp[-2].string, yyvsp[-1].number));
	}
    break;

  case 315:
#line 1181 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;

  case 316:
#line 1184 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	  CALL(yylsp[-4], yylsp[0], procBegin(yyvsp[-3].string, yyvsp[-2].number));
	}
    break;

  case 317:
#line 1188 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;

  case 318:
#line 1191 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACES));
	  CALL(yylsp[-3], yylsp[0], procBegin(yyvsp[-2].string, 0));
	}
    break;

  case 319:
#line 1195 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;

  case 320:
#line 1198 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_PROCID));
	  CALL(yylsp[-2], yylsp[0], procBegin("_", 0));
	}
    break;

  case 321:
#line 1202 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;

  case 322:
#line 1205 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], procBegin(yyvsp[-1].string, 0));
	}
    break;

  case 323:
#line 1208 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;

  case 324:
#line 1214 "parser.yy"
    { yyval.number = 0; }
    break;

  case 325:
#line 1215 "parser.yy"
    { yyval.number = yyvsp[-1].number; }
    break;

  case 326:
#line 1216 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_PARAMETERS));	  
	  yyval.number = 0; 
	}
    break;

  case 327:
#line 1223 "parser.yy"
    { 
	  yyval.number = yyvsp[0].number; 
	  CALL(yylsp[0], yylsp[0], declParameterEnd());
	}
    break;

  case 328:
#line 1227 "parser.yy"
    {
	  yyval.number = yyvsp[0].number;
	  CALL(yylsp[0], yylsp[0], declParameterEnd());
        }
    break;

  case 329:
#line 1231 "parser.yy"
    { 
	  yyval.number = yyvsp[-2].number + yyvsp[0].number;
	  CALL(yylsp[-2], yylsp[0], declParameterEnd());
	}
    break;

  case 330:
#line 1235 "parser.yy"
    { 
	  yyval.number = yyvsp[-2].number + yyvsp[0].number;
	  CALL(yylsp[-2], yylsp[0], declParameterEnd());
	}
    break;

  case 331:
#line 1239 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_PARAM_DECL_));
          yyval.number = yyvsp[-1].number; 
	}
    break;

  case 332:
#line 1246 "parser.yy"
    {
          CALL(yylsp[-2], yylsp[0], declParameter(yyvsp[-1].string, yyvsp[0].number == 0, yyvsp[0].number));
	  yyval.number = 1;
	}
    break;

  case 333:
#line 1250 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[0], declParameter(yyvsp[-1].string, yyvsp[0].number == 0, yyvsp[0].number));
	  yyval.number = yyvsp[-3].number + 1;
	}
    break;

  case 334:
#line 1257 "parser.yy"
    {
	  CALL(yylsp[-2], yylsp[-2], typeName(ParserBuilder::PREFIX_CONST, "int", false));
	  CALL(yylsp[-1], yylsp[0], declParameter(yyvsp[-1].string, false, yyvsp[0].number));
	  yyval.number = 1;
	}
    break;

  case 335:
#line 1262 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[0], declParameter(yyvsp[-1].string, false, yyvsp[0].number));
	  yyval.number = yyvsp[-3].number + 1;
	}
    break;

  case 343:
#line 1285 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_LOC_DECL));
	}
    break;

  case 344:
#line 1291 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], exprTrue(); ch->procState(yyvsp[0].string, false));
	}
    break;

  case 345:
#line 1294 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[0], procState(yyvsp[-3].string, true));
	}
    break;

  case 347:
#line 1301 "parser.yy"
    {	  
	  REPORT_ERROR(last_loc, TypeException(PE_INV));
	}
    break;

  case 348:
#line 1304 "parser.yy"
    {	  
	  REPORT_ERROR(last_loc, TypeException(PE_INV));
	  CALL(yylsp[0], yylsp[0], exprTrue());
	}
    break;

  case 349:
#line 1308 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(AND));
	}
    break;

  case 352:
#line 1316 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 353:
#line 1319 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 354:
#line 1322 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS_DECL));
	}
    break;

  case 355:
#line 1325 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS_DECL));
	}
    break;

  case 356:
#line 1328 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS));
	}
    break;

  case 359:
#line 1336 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_ALT_TRANS));	  
	}
    break;

  case 360:
#line 1342 "parser.yy"
    { 
	  strcpy(rootTransId, yyvsp[-7].string);
	  CALL(yylsp[-7], yylsp[0], procEdge(yyvsp[-7].string, yyvsp[-5].string));
	}
    break;

  case 361:
#line 1346 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  strcpy(rootTransId, yyvsp[-8].string);
	  CALL(yylsp[-8], yylsp[0], procEdge(yyvsp[-8].string, yyvsp[-6].string));
	}
    break;

  case 362:
#line 1351 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  strcpy(rootTransId, yyvsp[-7].string); 
	  CALL(yylsp[-7], yylsp[0], procEdge(yyvsp[-7].string, yyvsp[-5].string));
	}
    break;

  case 363:
#line 1356 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	  strcpy(rootTransId, yyvsp[-8].string); 
	  CALL(yylsp[-8], yylsp[0], procEdge(yyvsp[-8].string, yyvsp[-6].string));
	}
    break;

  case 364:
#line 1361 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_ARROW));
	  strcpy(rootTransId, yyvsp[-8].string); 
	  CALL(yylsp[-8], yylsp[0], procEdge(yyvsp[-8].string, yyvsp[-5].string));
	}
    break;

  case 365:
#line 1370 "parser.yy"
    { 
	  CALL(yylsp[-6], yylsp[0], procEdge(rootTransId, yyvsp[-5].string));
	}
    break;

  case 366:
#line 1373 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  CALL(yylsp[-6], yylsp[0], procEdge(rootTransId, yyvsp[-5].string));
	}
    break;

  case 367:
#line 1377 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  CALL(yylsp[-7], yylsp[0], procEdge(rootTransId, yyvsp[-6].string));
	}
    break;

  case 368:
#line 1381 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	  CALL(yylsp[-7], yylsp[0], procEdge(rootTransId, yyvsp[-6].string));
	}
    break;

  case 369:
#line 1385 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	  CALL(yylsp[-7], yylsp[0], procEdge(rootTransId, yyvsp[-5].string));
	}
    break;

  case 370:
#line 1389 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	  CALL(yylsp[-6], yylsp[0], procEdge(rootTransId, "_"));
	}
    break;

  case 373:
#line 1398 "parser.yy"
    {
	  CALL(yylsp[-1], yylsp[-1], procGuard());
	}
    break;

  case 374:
#line 1401 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-2], yylsp[-1], procGuard());
	}
    break;

  case 375:
#line 1405 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-1], yylsp[0], procGuard());
	}
    break;

  case 376:
#line 1409 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_GUARD_EXP));
	}
    break;

  case 378:
#line 1416 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(AND));
	}
    break;

  case 379:
#line 1419 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_GUARD_EXP_));
	  CALL(yylsp[-2], yylsp[0], exprBinary(AND));
	}
    break;

  case 384:
#line 1434 "parser.yy"
    {
		ch->quit();	
	}
    break;

  case 385:
#line 1437 "parser.yy"
    {
		ch->property(yyvsp[-1].kind, yylsp[-1].first_line);
	}
    break;

  case 386:
#line 1440 "parser.yy"
    {
		ch->property(LEADSTO, yylsp[-2].first_line);
	}
    break;

  case 387:
#line 1445 "parser.yy"
    { yyval.kind = EF; }
    break;

  case 388:
#line 1446 "parser.yy"
    { yyval.kind = EG; }
    break;

  case 389:
#line 1447 "parser.yy"
    { yyval.kind = AF; }
    break;

  case 390:
#line 1448 "parser.yy"
    { yyval.kind = AG; }
    break;


    }

/* Line 1010 of yacc.c.  */
#line 4568 "parser.tab.c"

  yyvsp -= yylen;
  yyssp -= yylen;
  yylsp -= yylen;

  YY_STACK_PRINT (yyss, yyssp);

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
	  const char* yyprefix;
	  char *yymsg;
	  int yyx;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 0;

	  yyprefix = ", expecting ";
	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
		yycount += 1;
		if (yycount == 5)
		  {
		    yysize = 0;
		    break;
		  }
	      }
	  yysize += (sizeof ("syntax error, unexpected ")
		     + yystrlen (yytname[yytype]));
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yyprefix = ", expecting ";
		  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			yyp = yystpcpy (yyp, yyprefix);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yyprefix = " or ";
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }

  yylerrsp = yylsp;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* If at end of input, pop the error token,
	     then the rest of the stack, then return failure.  */
	  if (yychar == YYEOF)
	     for (;;)
	       {
		 YYPOPSTACK;
		 if (yyssp == yyss)
		   YYABORT;
		 YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
		 yydestruct (yystos[*yyssp], yyvsp, yylsp);
	       }
        }
      else
	{
	  YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
	  yydestruct (yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	  *++yylerrsp = yylloc;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

#ifdef __GNUC__
  /* Pacify GCC when the user code never invokes YYERROR and the label
     yyerrorlab therefore never appears in user code.  */
  if (0)
     goto yyerrorlab;
#endif

  yyvsp -= yylen;
  yyssp -= yylen;
  yystate = *yyssp;
  yylerrsp = yylsp;
  *++yylerrsp = yyloc;
  yylsp -= yylen;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
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

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;
  YYLLOC_DEFAULT (yyloc, yylsp, yylerrsp - yylsp);
  *++yylsp = yyloc;

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


#line 1450 "parser.yy"


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


