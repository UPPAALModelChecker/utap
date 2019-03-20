/* A Bison parser, made by GNU Bison 1.875a.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.

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
     T_SYSTEM = 316,
     T_PROCESS = 317,
     T_STATE = 318,
     T_COMMIT = 319,
     T_INIT = 320,
     T_TRANS = 321,
     T_ARROW = 322,
     T_GUARD = 323,
     T_SYNC = 324,
     T_ASSIGN = 325,
     T_RATE = 326,
     T_BEFORE = 327,
     T_AFTER = 328,
     T_COST = 329,
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
#define T_SYSTEM 316
#define T_PROCESS 317
#define T_STATE 318
#define T_COMMIT 319
#define T_INIT 320
#define T_TRANS 321
#define T_ARROW 322
#define T_GUARD 323
#define T_SYNC 324
#define T_ASSIGN 325
#define T_RATE 326
#define T_BEFORE 327
#define T_AFTER 328
#define T_COST 329
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
static const char* PE_PRIORITY_ = "priority ordering expected";
static const char* PE_ALT_TRANS = "alternative transition expected";
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
static const char* PE_INIT = "'init' expected";
static const char* PE_INITIAL = "initialiser expected";
static const char* PE_INV = "invariant expression expected";
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
static const char* PE_VARID = "variable identifier expected";

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
#line 255 "parser.yy"
typedef union YYSTYPE {
    bool flag;
    int number;
    kind_t kind;
    char string[MAXLEN];
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 428 "parser.tab.c"
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
#line 452 "parser.tab.c"

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
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
      + 2 * YYSTACK_GAP_MAXIMUM)

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
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  77
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2934

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  120
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  126
/* YYNRULES -- Number of rules. */
#define YYNRULES  423
/* YYNRULES -- Number of states. */
#define YYNSTATES  760

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   361

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     119,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   108,     2,
     110,   111,     2,     2,   116,     2,   114,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   107,   115,
       2,     2,     2,   106,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   112,     2,   113,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   117,     2,   118,     2,     2,     2,     2,
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
static const unsigned short yyprhs[] =
{
       0,     0,     3,     6,     9,    12,    15,    18,    21,    24,
      27,    30,    33,    36,    39,    42,    45,    48,    51,    54,
      57,    60,    63,    66,    70,    71,    72,    82,    91,    99,
     106,   111,   115,   116,   120,   121,   125,   127,   131,   135,
     139,   143,   147,   152,   156,   158,   162,   166,   167,   170,
     173,   176,   179,   182,   185,   188,   193,   194,   198,   202,
     207,   212,   213,   217,   218,   222,   223,   232,   238,   241,
     245,   250,   254,   258,   261,   263,   267,   271,   276,   280,
     283,   287,   292,   296,   298,   302,   306,   307,   310,   312,
     316,   318,   322,   326,   330,   332,   333,   338,   344,   349,
     354,   358,   363,   369,   374,   378,   380,   384,   388,   391,
     395,   401,   407,   412,   416,   418,   420,   422,   425,   428,
     432,   437,   441,   444,   447,   449,   453,   457,   460,   461,
     463,   465,   468,   470,   471,   477,   481,   482,   490,   491,
     498,   504,   505,   508,   511,   514,   518,   523,   527,   531,
     534,   537,   539,   543,   547,   549,   554,   560,   565,   570,
     574,   578,   583,   587,   590,   592,   593,   597,   602,   606,
     609,   611,   613,   617,   621,   630,   640,   646,   651,   655,
     663,   672,   677,   681,   683,   684,   688,   693,   697,   698,
     702,   707,   711,   715,   718,   722,   725,   729,   732,   733,
     737,   741,   742,   744,   746,   749,   753,   758,   762,   766,
     769,   773,   778,   782,   786,   789,   791,   795,   799,   801,
     805,   809,   810,   816,   817,   820,   823,   824,   827,   831,
     833,   835,   838,   839,   850,   856,   857,   864,   870,   871,
     880,   881,   889,   892,   895,   896,   905,   909,   912,   913,
     914,   918,   919,   923,   925,   928,   929,   935,   936,   942,
     943,   948,   949,   955,   956,   958,   960,   964,   966,   968,
     970,   972,   973,   979,   980,   986,   991,   996,  1000,  1004,
    1007,  1010,  1013,  1016,  1019,  1023,  1027,  1031,  1035,  1039,
    1043,  1047,  1051,  1055,  1059,  1063,  1067,  1071,  1075,  1079,
    1083,  1087,  1091,  1097,  1101,  1103,  1104,  1109,  1113,  1117,
    1120,  1124,  1128,  1130,  1134,  1136,  1138,  1140,  1142,  1144,
    1146,  1148,  1150,  1152,  1154,  1156,  1158,  1160,  1162,  1163,
    1165,  1169,  1173,  1177,  1178,  1181,  1184,  1186,  1187,  1192,
    1196,  1198,  1202,  1206,  1207,  1215,  1216,  1225,  1226,  1234,
    1235,  1242,  1243,  1250,  1253,  1257,  1261,  1263,  1265,  1269,
    1273,  1276,  1280,  1285,  1289,  1294,  1300,  1301,  1304,  1308,
    1313,  1317,  1321,  1324,  1326,  1328,  1332,  1336,  1338,  1343,
    1345,  1349,  1351,  1355,  1356,  1360,  1365,  1369,  1373,  1376,
    1378,  1380,  1384,  1388,  1397,  1407,  1416,  1426,  1436,  1444,
    1452,  1461,  1470,  1479,  1487,  1489,  1490,  1494,  1499,  1503,
    1506,  1508,  1512,  1516,  1519,  1520,  1524,  1525,  1527,  1530,
    1534,  1536,  1538,  1540
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short yyrhs[] =
{
     121,     0,    -1,    86,   122,    -1,    87,   131,    -1,    88,
     167,    -1,    89,   123,    -1,    90,   125,    -1,    90,     1,
      -1,    91,   142,    -1,    92,   206,    -1,    93,   206,    -1,
      94,   178,    -1,    95,   205,    -1,    96,   214,    -1,    97,
     215,    -1,    98,   231,    -1,    99,   123,    -1,   100,   227,
      -1,   101,   235,    -1,   102,   241,    -1,   103,   205,    -1,
     104,   242,    -1,   105,   206,    -1,   131,   123,   125,    -1,
      -1,    -1,   123,    83,     3,    83,   110,   124,   213,   111,
     115,    -1,   123,    83,     3,    83,   110,     1,   111,   115,
      -1,   123,    83,     3,    83,   110,     1,   115,    -1,   123,
      83,     3,    83,     1,   115,    -1,   123,    83,     1,   115,
      -1,   126,   127,   129,    -1,    -1,    51,   128,   115,    -1,
      -1,    52,   128,   115,    -1,    83,    -1,   128,    36,    83,
      -1,   128,    34,    83,    -1,   128,    36,     1,    -1,   128,
      34,     1,    -1,    61,   130,   115,    -1,    61,   130,     1,
     115,    -1,    61,     1,   115,    -1,    83,    -1,   130,   116,
      83,    -1,   130,   116,     1,    -1,    -1,   131,   139,    -1,
     131,   144,    -1,   131,   152,    -1,   131,   163,    -1,   131,
     132,    -1,   131,   135,    -1,   131,   136,    -1,    71,   117,
     133,   118,    -1,    -1,   133,   134,   115,    -1,    74,   107,
     206,    -1,    72,   117,   137,   118,    -1,    73,   117,   138,
     118,    -1,    -1,   137,   210,   115,    -1,    -1,   138,   210,
     115,    -1,    -1,   155,   156,   141,   140,   117,   187,   188,
     118,    -1,   155,   156,   141,     1,   118,    -1,   110,   111,
      -1,   110,   142,   111,    -1,   110,   142,     1,   111,    -1,
     110,   142,     1,    -1,   110,     1,   111,    -1,   110,     1,
      -1,   143,    -1,   142,   116,   143,    -1,   142,   116,     1,
      -1,   155,   108,    83,   151,    -1,   155,    83,   151,    -1,
     155,     1,    -1,   155,   145,   115,    -1,   155,   145,     1,
     115,    -1,   155,     1,   115,    -1,   146,    -1,   145,   116,
     146,    -1,   156,   151,   147,    -1,    -1,     3,   148,    -1,
     206,    -1,   117,   149,   118,    -1,   150,    -1,   149,   116,
     150,    -1,   156,   107,   148,    -1,   156,   107,     1,    -1,
     148,    -1,    -1,   151,   112,   206,   113,    -1,   151,   112,
     206,     1,   113,    -1,   151,   112,   206,     1,    -1,   151,
     112,     1,   113,    -1,   151,   112,     1,    -1,    53,   155,
     153,   115,    -1,    53,   155,   153,     1,   115,    -1,    53,
     155,     1,   115,    -1,    53,     1,   115,    -1,   154,    -1,
     153,   116,   154,    -1,   153,   116,     1,    -1,   156,   151,
      -1,   161,    84,   162,    -1,   161,    54,   117,   157,   118,
      -1,   161,    54,   117,     1,   118,    -1,   161,    54,   117,
       1,    -1,   161,    54,     1,    -1,    83,    -1,    84,    -1,
     158,    -1,   157,   158,    -1,   157,     1,    -1,   155,   159,
     115,    -1,   155,   159,     1,   115,    -1,   155,     1,   115,
      -1,   155,     1,    -1,     1,   115,    -1,   160,    -1,   159,
     116,   160,    -1,   159,   116,     1,    -1,   156,   151,    -1,
      -1,    57,    -1,    58,    -1,    57,    58,    -1,    55,    -1,
      -1,   112,   206,   116,   206,   113,    -1,   112,     1,   113,
      -1,    -1,    62,   156,   141,   117,   164,   166,   118,    -1,
      -1,    62,   156,   117,   165,   166,   118,    -1,   167,   168,
     180,   171,   172,    -1,    -1,   167,   139,    -1,   167,   144,
      -1,   167,   152,    -1,    63,   169,   115,    -1,    63,   169,
       1,   115,    -1,    63,   169,     1,    -1,    63,     1,   115,
      -1,    63,     1,    -1,     1,   115,    -1,   170,    -1,   169,
     116,   170,    -1,   169,   116,     1,    -1,    83,    -1,    83,
     117,   206,   118,    -1,    83,   117,   206,     1,   118,    -1,
      83,   117,   206,     1,    -1,    83,   117,     1,   118,    -1,
      83,   117,     1,    -1,    65,    83,   115,    -1,    65,    83,
       1,   115,    -1,    65,    83,     1,    -1,    65,     1,    -1,
       1,    -1,    -1,    66,   173,   115,    -1,    66,   173,     1,
     115,    -1,    66,   173,     1,    -1,    66,     1,    -1,     1,
      -1,   174,    -1,   173,   116,   175,    -1,   173,   116,     1,
      -1,    83,    67,    83,   117,   176,   177,   179,   118,    -1,
      83,    67,    83,   117,   176,   177,   179,     1,   115,    -1,
      83,    67,    83,     1,   118,    -1,    83,    67,     1,   118,
      -1,    83,     1,   118,    -1,    67,    83,   117,   176,   177,
     179,   118,    -1,    67,    83,   117,   176,   177,   179,     1,
     118,    -1,    67,    83,     1,   118,    -1,    67,     1,   118,
      -1,   174,    -1,    -1,    68,   206,   115,    -1,    68,   206,
       1,   115,    -1,    68,     1,   115,    -1,    -1,    69,   178,
     115,    -1,    69,   178,     1,   115,    -1,    69,   178,     1,
      -1,    69,     1,   115,    -1,   206,    14,    -1,   206,     1,
      14,    -1,   206,   106,    -1,   206,     1,   106,    -1,   206,
       1,    -1,    -1,    70,   205,   115,    -1,    70,     1,   115,
      -1,    -1,   181,    -1,   182,    -1,   181,   182,    -1,    64,
     183,   115,    -1,    64,   183,     1,   115,    -1,    64,   183,
       1,    -1,    64,     1,   115,    -1,    64,     1,    -1,    57,
     184,   115,    -1,    57,   184,     1,   115,    -1,    57,   184,
       1,    -1,    57,     1,   115,    -1,    57,     1,    -1,    83,
      -1,   183,   116,    83,    -1,   183,   116,     1,    -1,    83,
      -1,   184,   116,    83,    -1,   184,   116,     1,    -1,    -1,
     117,   186,   187,   188,   118,    -1,    -1,   187,   144,    -1,
     187,   152,    -1,    -1,   188,   189,    -1,   188,     1,   115,
      -1,   185,    -1,   115,    -1,   206,   115,    -1,    -1,    40,
     110,   190,   204,   115,   204,   115,   204,   111,   189,    -1,
      40,   110,     1,   111,   189,    -1,    -1,    41,   110,   191,
     205,   111,   189,    -1,    41,   110,     1,   111,   189,    -1,
      -1,    42,   192,   189,    41,   110,   205,   111,   115,    -1,
      -1,    46,   110,   193,   205,   111,   189,   195,    -1,    43,
     115,    -1,    44,   115,    -1,    -1,    45,   110,   205,   111,
     194,   117,   198,   118,    -1,    50,   206,   115,    -1,    50,
     115,    -1,    -1,    -1,    47,   196,   189,    -1,    -1,    47,
     197,     1,    -1,   199,    -1,   198,   199,    -1,    -1,    48,
     206,   107,   200,   188,    -1,    -1,    48,     1,   107,   201,
     188,    -1,    -1,    49,   107,   202,   188,    -1,    -1,    49,
       1,   107,   203,   188,    -1,    -1,   205,    -1,   206,    -1,
     205,   116,   206,    -1,    60,    -1,    59,    -1,    85,    -1,
      83,    -1,    -1,    83,   110,   207,   213,   111,    -1,    -1,
      83,   110,   208,     1,   111,    -1,   206,   112,   206,   113,
      -1,   206,   112,     1,   113,    -1,   110,   206,   111,    -1,
     110,     1,   111,    -1,   206,    15,    -1,    15,   206,    -1,
     206,    16,    -1,    16,   206,    -1,   212,   206,    -1,   206,
      34,   206,    -1,   206,    35,   206,    -1,   206,    36,   206,
      -1,   206,    37,   206,    -1,   206,    39,   206,    -1,   206,
      38,   206,    -1,   206,    17,   206,    -1,   206,    18,   206,
      -1,   206,    19,   206,    -1,   206,    20,   206,    -1,   206,
      23,   206,    -1,   206,   108,   206,    -1,   206,    24,   206,
      -1,   206,    25,   206,    -1,   206,    26,   206,    -1,   206,
      27,   206,    -1,   206,    28,   206,    -1,   206,    29,   206,
      -1,   206,   106,   206,   107,   206,    -1,   206,   114,    83,
      -1,    75,    -1,    -1,   206,    32,   209,   206,    -1,   206,
      30,   206,    -1,   206,    31,   206,    -1,    33,   206,    -1,
     206,    21,   206,    -1,   206,    22,   206,    -1,   210,    -1,
     206,   211,   206,    -1,     3,    -1,     4,    -1,     5,    -1,
       7,    -1,     8,    -1,     6,    -1,    10,    -1,     9,    -1,
      11,    -1,    12,    -1,    13,    -1,    18,    -1,    17,    -1,
      14,    -1,    -1,   206,    -1,   213,   116,   206,    -1,   213,
     116,     1,    -1,   215,   123,   125,    -1,    -1,   215,   216,
      -1,   215,   220,    -1,   144,    -1,    -1,    56,   217,   218,
     115,    -1,    56,     1,   115,    -1,   219,    -1,   218,   116,
     219,    -1,    83,   151,   148,    -1,    -1,    62,   156,   226,
     117,   221,   230,   118,    -1,    -1,    62,   156,   226,     1,
     117,   222,   230,   118,    -1,    -1,    62,   156,     1,   117,
     223,   230,   118,    -1,    -1,    62,     1,   117,   224,   230,
     118,    -1,    -1,    62,   156,   117,   225,   230,   118,    -1,
     110,   111,    -1,   110,   227,   111,    -1,   110,     1,   111,
      -1,   228,    -1,   229,    -1,   227,   115,   228,    -1,   227,
     115,   229,    -1,   227,   115,    -1,   155,    83,   151,    -1,
     228,   116,    83,   151,    -1,    56,    83,   151,    -1,   229,
     116,    83,   151,    -1,   231,   232,   180,   171,   236,    -1,
      -1,   231,   216,    -1,    63,   233,   115,    -1,    63,   233,
       1,   115,    -1,    63,   233,     1,    -1,    63,     1,   115,
      -1,    63,     1,    -1,     1,    -1,   234,    -1,   233,   116,
     234,    -1,   233,   116,     1,    -1,    83,    -1,    83,   117,
     235,   118,    -1,   206,    -1,   206,     1,   116,    -1,     1,
      -1,   235,   116,   206,    -1,    -1,    66,   237,   115,    -1,
      66,   237,     1,   115,    -1,    66,   237,     1,    -1,    66,
       1,   115,    -1,    66,     1,    -1,     1,    -1,   238,    -1,
     237,   116,   239,    -1,   237,   116,     1,    -1,    83,    67,
      83,   117,   240,   177,   179,   118,    -1,    83,    67,    83,
     117,   240,   177,   179,     1,   118,    -1,    83,    67,    83,
     117,   240,   177,   179,     1,    -1,    83,    67,    83,     1,
     117,   240,   177,   179,   118,    -1,    83,     1,    67,    83,
     117,   240,   177,   179,   118,    -1,    67,    83,   117,   240,
     177,   179,   118,    -1,    67,    83,   117,   240,   177,   179,
       1,    -1,    67,    83,   117,   240,   177,   179,     1,   118,
      -1,    67,    83,     1,   117,   240,   177,   179,   118,    -1,
      67,     1,    83,   117,   240,   177,   179,   118,    -1,    67,
       1,   117,   240,   177,   179,   118,    -1,   238,    -1,    -1,
      68,   241,   115,    -1,    68,   241,     1,   115,    -1,    68,
     241,     1,    -1,    68,     1,    -1,   206,    -1,   241,   116,
     206,    -1,   241,   116,     1,    -1,   243,   244,    -1,    -1,
     243,   244,   119,    -1,    -1,    81,    -1,   245,   206,    -1,
     206,    80,   206,    -1,    76,    -1,    77,    -1,    78,    -1,
      79,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   268,   268,   269,   270,   271,   272,   273,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   294,   297,   299,   299,   304,   307,   310,
     313,   318,   320,   322,   325,   327,   331,   332,   333,   334,
     337,   343,   344,   347,   353,   354,   355,   360,   362,   363,
     364,   365,   366,   367,   368,   371,   373,   375,   378,   380,
     382,   384,   386,   390,   392,   397,   397,   403,   409,   410,
     411,   415,   419,   423,   435,   436,   437,   444,   448,   452,
     458,   461,   465,   472,   473,   477,   483,   484,   488,   489,
     495,   496,   500,   503,   506,   512,   513,   514,   518,   522,
     527,   535,   538,   542,   546,   558,   559,   560,   567,   573,
     577,   581,   586,   591,   597,   598,   602,   603,   604,   611,
     615,   620,   623,   626,   632,   633,   634,   641,   647,   648,
     649,   650,   651,   655,   656,   657,   667,   667,   673,   673,
     684,   687,   689,   690,   691,   695,   696,   699,   702,   705,
     708,   714,   715,   716,   722,   725,   728,   732,   736,   740,
     747,   750,   754,   758,   761,   766,   768,   769,   772,   775,
     778,   784,   785,   786,   792,   796,   801,   804,   807,   813,
     816,   820,   823,   826,   830,   832,   835,   839,   844,   846,
     847,   850,   853,   859,   862,   866,   869,   873,   879,   881,
     884,   889,   891,   892,   893,   897,   898,   901,   904,   907,
     913,   914,   917,   920,   923,   929,   932,   935,   941,   944,
     947,   958,   958,   966,   968,   969,   972,   974,   975,   979,
     980,   983,   986,   986,   992,   993,   993,   999,  1000,  1000,
    1006,  1006,  1010,  1013,  1016,  1016,  1022,  1025,  1031,  1034,
    1034,  1040,  1040,  1050,  1051,  1055,  1055,  1061,  1061,  1068,
    1068,  1074,  1074,  1083,  1085,  1089,  1090,  1095,  1098,  1101,
    1104,  1107,  1107,  1112,  1112,  1118,  1121,  1125,  1126,  1130,
    1133,  1136,  1139,  1142,  1145,  1148,  1151,  1154,  1157,  1160,
    1163,  1166,  1169,  1172,  1175,  1178,  1181,  1184,  1187,  1190,
    1193,  1196,  1199,  1202,  1205,  1208,  1208,  1213,  1216,  1219,
    1222,  1225,  1228,  1232,  1238,  1239,  1240,  1241,  1242,  1243,
    1244,  1245,  1246,  1247,  1248,  1253,  1254,  1255,  1260,  1261,
    1265,  1269,  1281,  1284,  1286,  1287,  1291,  1292,  1292,  1297,
    1300,  1301,  1305,  1314,  1314,  1320,  1320,  1327,  1327,  1334,
    1334,  1341,  1341,  1350,  1351,  1352,  1359,  1363,  1367,  1371,
    1375,  1382,  1386,  1393,  1398,  1405,  1408,  1410,  1414,  1415,
    1418,  1421,  1424,  1427,  1433,  1434,  1435,  1441,  1444,  1450,
    1451,  1454,  1458,  1463,  1465,  1466,  1469,  1472,  1475,  1478,
    1484,  1485,  1486,  1492,  1496,  1501,  1506,  1511,  1520,  1523,
    1527,  1531,  1535,  1539,  1543,  1546,  1548,  1551,  1555,  1559,
    1565,  1566,  1569,  1576,  1578,  1580,  1582,  1584,  1587,  1590,
    1595,  1596,  1597,  1598
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_ASSIGNMENT", "T_ASSPLUS", "T_ASSMINUS", 
  "T_ASSMULT", "T_ASSDIV", "T_ASSMOD", "T_ASSOR", "T_ASSAND", "T_ASSXOR", 
  "T_ASSLSHIFT", "T_ASSRSHIFT", "T_EXCLAM", "T_INCREMENT", "T_DECREMENT", 
  "T_PLUS", "T_MINUS", "T_MULT", "T_DIV", "T_MIN", "T_MAX", "T_MOD", 
  "T_OR", "T_XOR", "T_LSHIFT", "T_RSHIFT", "T_BOOL_AND", "T_BOOL_OR", 
  "T_KW_AND", "T_KW_OR", "T_KW_IMPLY", "T_KW_NOT", "T_LT", "T_LEQ", 
  "T_EQ", "T_NEQ", "T_GEQ", "T_GT", "T_FOR", "T_WHILE", "T_DO", "T_BREAK", 
  "T_CONTINUE", "T_SWITCH", "T_IF", "T_ELSE", "T_CASE", "T_DEFAULT", 
  "T_RETURN", "T_CHAN_PRIORITY", "T_PROC_PRIORITY", "T_TYPEDEF", 
  "T_STRUCT", "T_CONST", "T_OLDCONST", "T_URGENT", "T_BROADCAST", 
  "T_TRUE", "T_FALSE", "T_SYSTEM", "T_PROCESS", "T_STATE", "T_COMMIT", 
  "T_INIT", "T_TRANS", "T_ARROW", "T_GUARD", "T_SYNC", "T_ASSIGN", 
  "T_RATE", "T_BEFORE", "T_AFTER", "T_COST", "T_DEADLOCK", "T_EF", "T_EG", 
  "T_AF", "T_AG", "T_LEADSTO", "T_QUIT", "T_ERROR", "T_ID", "T_TYPENAME", 
  "T_NAT", "T_NEW", "T_NEW_DECLARATION", "T_NEW_LOCAL_DECL", "T_NEW_INST", 
  "T_NEW_SYSTEM", "T_NEW_PARAMETERS", "T_NEW_INVARIANT", "T_NEW_GUARD", 
  "T_NEW_SYNC", "T_NEW_ASSIGN", "T_OLD", "T_OLD_DECLARATION", 
  "T_OLD_LOCAL_DECL", "T_OLD_INST", "T_OLD_PARAMETERS", "T_OLD_INVARIANT", 
  "T_OLD_GUARD", "T_OLD_ASSIGN", "T_PROPERTY", "T_EXPRESSION", "'?'", 
  "':'", "'&'", "UOPERATOR", "'('", "')'", "'['", "']'", "'.'", "';'", 
  "','", "'{'", "'}'", "'\\n'", "$accept", "Uppaal", "XTA", "Inst", "@1", 
  "System", "ChanPriorityDecl", "ProcPriorityDecl", "PriorityOrder", 
  "SysDecl", "ProcessList", "Declaration", "RateDecl", "RateList", "Rate", 
  "BeforeUpdateDecl", "AfterUpdateDecl", "BeforeAssignmentList", 
  "AfterAssignmentList", "FunctionDecl", "@2", "OptionalParameterList", 
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
  "SwitchCase", "@13", "@14", "@15", "@16", "ExprList0", "ExprList", 
  "Expression", "@17", "@18", "@19", "Assignment", "AssignOp", "UnaryOp", 
  "ArgList", "OldXTA", "OldDeclaration", "OldVarDecl", "@20", 
  "OldConstDeclIdList", "OldConstDeclId", "OldProcDecl", "@21", "@22", 
  "@23", "@24", "@25", "OldProcParams", "OldProcParamList", 
  "OldProcParam", "OldProcConstParam", "OldProcBody", "OldVarDeclList", 
  "OldStates", "OldStateDeclList", "OldStateDecl", "OldInvariant", 
  "OldTransitions", "OldTransitionList", "OldTransition", 
  "OldTransitionOpt", "OldGuard", "OldGuardList", "PropertyList", 
  "PropertyList2", "Property", "Quantifier", 0
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
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,    63,    58,    38,   361,
      40,    41,    91,    93,    46,    59,    44,   123,   125,    10
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,   120,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   122,   123,   124,   123,   123,   123,   123,
     123,   125,   126,   126,   127,   127,   128,   128,   128,   128,
     128,   129,   129,   129,   130,   130,   130,   131,   131,   131,
     131,   131,   131,   131,   131,   132,   133,   133,   134,   135,
     136,   137,   137,   138,   138,   140,   139,   139,   141,   141,
     141,   141,   141,   141,   142,   142,   142,   143,   143,   143,
     144,   144,   144,   145,   145,   146,   147,   147,   148,   148,
     149,   149,   150,   150,   150,   151,   151,   151,   151,   151,
     151,   152,   152,   152,   152,   153,   153,   153,   154,   155,
     155,   155,   155,   155,   156,   156,   157,   157,   157,   158,
     158,   158,   158,   158,   159,   159,   159,   160,   161,   161,
     161,   161,   161,   162,   162,   162,   164,   163,   165,   163,
     166,   167,   167,   167,   167,   168,   168,   168,   168,   168,
     168,   169,   169,   169,   170,   170,   170,   170,   170,   170,
     171,   171,   171,   171,   171,   172,   172,   172,   172,   172,
     172,   173,   173,   173,   174,   174,   174,   174,   174,   175,
     175,   175,   175,   175,   176,   176,   176,   176,   177,   177,
     177,   177,   177,   178,   178,   178,   178,   178,   179,   179,
     179,   180,   180,   180,   180,   181,   181,   181,   181,   181,
     182,   182,   182,   182,   182,   183,   183,   183,   184,   184,
     184,   186,   185,   187,   187,   187,   188,   188,   188,   189,
     189,   189,   190,   189,   189,   191,   189,   189,   192,   189,
     193,   189,   189,   189,   194,   189,   189,   189,   195,   196,
     195,   197,   195,   198,   198,   200,   199,   201,   199,   202,
     199,   203,   199,   204,   204,   205,   205,   206,   206,   206,
     206,   207,   206,   208,   206,   206,   206,   206,   206,   206,
     206,   206,   206,   206,   206,   206,   206,   206,   206,   206,
     206,   206,   206,   206,   206,   206,   206,   206,   206,   206,
     206,   206,   206,   206,   206,   209,   206,   206,   206,   206,
     206,   206,   206,   210,   211,   211,   211,   211,   211,   211,
     211,   211,   211,   211,   211,   212,   212,   212,   213,   213,
     213,   213,   214,   215,   215,   215,   216,   217,   216,   216,
     218,   218,   219,   221,   220,   222,   220,   223,   220,   224,
     220,   225,   220,   226,   226,   226,   227,   227,   227,   227,
     227,   228,   228,   229,   229,   230,   231,   231,   232,   232,
     232,   232,   232,   232,   233,   233,   233,   234,   234,   235,
     235,   235,   235,   236,   236,   236,   236,   236,   236,   236,
     237,   237,   237,   238,   238,   238,   238,   238,   239,   239,
     239,   239,   239,   239,   239,   240,   240,   240,   240,   240,
     241,   241,   241,   242,   243,   243,   244,   244,   244,   244,
     245,   245,   245,   245
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     3,     0,     0,     9,     8,     7,     6,
       4,     3,     0,     3,     0,     3,     1,     3,     3,     3,
       3,     3,     4,     3,     1,     3,     3,     0,     2,     2,
       2,     2,     2,     2,     2,     4,     0,     3,     3,     4,
       4,     0,     3,     0,     3,     0,     8,     5,     2,     3,
       4,     3,     3,     2,     1,     3,     3,     4,     3,     2,
       3,     4,     3,     1,     3,     3,     0,     2,     1,     3,
       1,     3,     3,     3,     1,     0,     4,     5,     4,     4,
       3,     4,     5,     4,     3,     1,     3,     3,     2,     3,
       5,     5,     4,     3,     1,     1,     1,     2,     2,     3,
       4,     3,     2,     2,     1,     3,     3,     2,     0,     1,
       1,     2,     1,     0,     5,     3,     0,     7,     0,     6,
       5,     0,     2,     2,     2,     3,     4,     3,     3,     2,
       2,     1,     3,     3,     1,     4,     5,     4,     4,     3,
       3,     4,     3,     2,     1,     0,     3,     4,     3,     2,
       1,     1,     3,     3,     8,     9,     5,     4,     3,     7,
       8,     4,     3,     1,     0,     3,     4,     3,     0,     3,
       4,     3,     3,     2,     3,     2,     3,     2,     0,     3,
       3,     0,     1,     1,     2,     3,     4,     3,     3,     2,
       3,     4,     3,     3,     2,     1,     3,     3,     1,     3,
       3,     0,     5,     0,     2,     2,     0,     2,     3,     1,
       1,     2,     0,    10,     5,     0,     6,     5,     0,     8,
       0,     7,     2,     2,     0,     8,     3,     2,     0,     0,
       3,     0,     3,     1,     2,     0,     5,     0,     5,     0,
       4,     0,     5,     0,     1,     1,     3,     1,     1,     1,
       1,     0,     5,     0,     5,     4,     4,     3,     3,     2,
       2,     2,     2,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     5,     3,     1,     0,     4,     3,     3,     2,
       3,     3,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     1,
       3,     3,     3,     0,     2,     2,     1,     0,     4,     3,
       1,     3,     3,     0,     7,     0,     8,     0,     7,     0,
       6,     0,     6,     2,     3,     3,     1,     1,     3,     3,
       2,     3,     4,     3,     4,     5,     0,     2,     3,     4,
       3,     3,     2,     1,     1,     3,     3,     1,     4,     1,
       3,     1,     3,     0,     3,     4,     3,     3,     2,     1,
       1,     3,     3,     8,     9,     8,     9,     9,     7,     7,
       8,     8,     8,     7,     1,     0,     3,     4,     3,     2,
       1,     3,     3,     2,     0,     3,     0,     1,     2,     3,
       1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned short yydefact[] =
{
       0,    47,    47,   141,    24,     0,   128,     0,     0,     0,
       0,   333,   333,   366,    24,   128,     0,     0,     0,   414,
       0,     0,     2,    24,   128,   128,     5,     7,     0,     6,
      34,   132,   129,   130,     8,    74,     0,     0,   327,     0,
       0,   326,   325,     0,   268,   267,   304,   270,   269,     0,
       9,   312,     0,    10,    11,     0,    12,   265,    13,    24,
     128,   128,    16,     0,     0,    17,   356,   357,   381,     0,
      18,   410,    19,    20,    21,   416,    22,     1,     0,     0,
       0,     0,     0,    32,    52,    53,    54,    48,    49,    50,
       0,    51,   142,   143,   144,     0,    36,     0,     0,     0,
     131,     0,    79,    95,     0,     0,   133,   280,   282,   309,
     271,     0,     0,   314,   315,   316,   319,   317,   318,   321,
     320,   322,   323,   324,   279,   281,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   305,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   283,   197,   193,   195,     0,     0,     0,
      32,   336,     0,   334,   335,   367,    95,    95,   360,     0,
       0,     0,     0,     0,   420,   421,   422,   423,   417,     0,
     413,     0,     0,     0,   114,   115,     0,    56,    61,    63,
      23,     0,     0,    83,    95,     0,     0,     0,     0,    33,
       0,     0,    31,    76,    75,    78,    95,   113,     0,     0,
     109,   328,     0,   278,   277,   290,   291,   292,   293,   310,
     311,   294,   296,   297,   298,   299,   300,   301,   307,   308,
       0,   284,   285,   286,   287,   289,   288,     0,   295,     0,
       0,   303,   313,   194,   196,   266,     0,     0,     0,     0,
     332,    95,   363,   361,   358,   359,    95,    95,   380,   382,
     412,   411,     0,   415,   418,   104,     0,     0,   105,    95,
       0,   138,     0,     0,     0,     0,    82,     0,    80,     0,
       0,    86,    30,     0,    40,    38,    39,    37,    35,     0,
      44,     0,     0,    77,   112,     0,     0,   116,     0,     0,
     329,     0,     0,   306,     0,   276,   275,   339,    95,     0,
     340,   349,     0,     0,   351,     0,   362,   364,   419,   103,
       0,   101,     0,   108,    73,    68,     0,   141,   136,     0,
      55,     0,    59,     0,   312,    60,   312,    81,    84,     0,
       0,     0,    85,     0,     0,    43,     0,    41,     0,   100,
       0,   123,   111,   122,    95,     0,   124,   118,   110,   117,
     135,     0,   272,     0,   274,   302,     0,   338,     0,   366,
     347,     0,   353,     0,   366,     0,   343,   102,   107,   106,
      72,    71,    69,     0,     0,   141,     0,    57,    62,    64,
      67,   223,     0,    87,    88,    29,     0,   328,    42,    46,
      45,    99,    98,    96,   121,   127,     0,   119,     0,     0,
     331,   330,   342,   341,     0,     0,   366,   355,   354,     0,
     345,   366,    70,   139,     0,     0,   201,     0,    58,   226,
     270,    94,     0,    90,     0,     0,    28,     0,    97,   120,
     126,   125,   134,   350,   373,     0,   201,     0,   352,   366,
       0,   150,   149,   154,     0,   151,     0,     0,     0,   202,
     203,   137,   224,   225,     0,     0,    89,     0,    27,     0,
     372,   377,     0,   374,     0,   348,     0,   344,   148,     0,
     147,   145,     0,   214,   218,     0,   209,   215,     0,   164,
       0,     0,   204,     0,     0,     0,   238,     0,     0,     0,
       0,     0,   230,   221,    66,   229,   227,     0,    91,    93,
      92,    26,   371,     0,   370,   368,     0,     0,   346,   159,
       0,   146,   153,   152,   213,   212,   210,     0,   208,   207,
     205,     0,   163,     0,   170,     0,   140,   228,     0,     0,
       0,   242,   243,     0,   240,   247,     0,   223,   231,     0,
     369,   376,   375,   389,     0,   365,   158,   157,   155,   211,
     220,   219,   206,   217,   216,   162,   160,   169,     0,     0,
     171,     0,   263,     0,     0,     0,     0,     0,   246,   226,
     378,   388,     0,     0,   390,   156,   161,     0,     0,   168,
     166,     0,     0,     0,   264,     0,     0,     0,   244,     0,
       0,   387,     0,     0,   386,   384,     0,   178,     0,     0,
     167,   173,     0,   183,   172,   234,   263,   237,     0,     0,
       0,     0,   222,     0,     0,   385,   392,     0,   404,   391,
     177,     0,   184,     0,     0,     0,   236,     0,     0,   248,
       0,     0,   405,     0,     0,   176,     0,   188,   182,     0,
     184,   263,     0,     0,     0,     0,   253,   249,   241,   405,
     405,     0,   188,     0,   405,     0,   405,     0,     0,     0,
     198,   181,   188,     0,   239,     0,     0,     0,   259,   245,
     254,     0,     0,   188,   188,   409,     0,   198,   405,   188,
     405,   188,   187,     0,   185,     0,     0,     0,     0,   198,
       0,   257,   255,   261,   226,   250,   252,   198,   198,   408,
     406,     0,   188,   198,   188,   198,   186,   192,   191,   189,
       0,     0,     0,   174,     0,   233,   226,   226,   226,     0,
       0,     0,   407,   395,   393,   198,     0,   198,     0,   190,
     200,   199,   175,     0,   179,     0,     0,     0,   397,   396,
     394,     0,   403,     0,   399,   398,   180,   402,   401,   400
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,    21,    22,    26,   397,    29,    30,    99,    97,   202,
     291,    23,    84,   273,   331,    85,    86,   274,   275,    87,
     340,   272,    34,    35,   161,   192,   193,   342,   431,   432,
     433,   281,    89,   267,   268,   162,   251,   296,   297,   355,
     356,    37,   210,    91,   385,   327,   383,   384,   426,   454,
     455,   491,   536,   569,   570,   614,   647,   670,    54,   698,
     458,   459,   460,   488,   485,   505,   547,   429,   464,   506,
     572,   574,   540,   577,   620,   658,   681,   682,   655,   656,
     727,   726,   704,   728,   593,   594,   507,   211,   212,   230,
      51,   152,    52,   301,    58,    59,   163,   247,   309,   310,
     164,   421,   449,   416,   369,   374,   315,    65,    66,    67,
     414,   415,   446,   472,   473,    70,   555,   583,   584,   629,
     662,    72,    74,    75,   180,   181
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -599
static const short yypact[] =
{
    1111,  -599,  -599,  -599,  -599,   735,   484,  2824,  2824,  2824,
    2824,  -599,  -599,  -599,  -599,   549,  2082,  2824,  2824,  -599,
    2824,    52,  -599,   979,   849,   758,   -12,  -599,     7,  -599,
      62,  -599,   218,  -599,   117,  -599,   212,    -8,  -599,  2824,
    2824,  -599,  -599,  2824,  -599,  -599,  -599,   202,  -599,  2093,
    1903,  -599,  2824,  1903,  -599,  1118,   222,  1903,  -599,   697,
     580,   602,   -12,   289,   305,   291,   368,   379,  -599,   415,
     398,  1903,   410,   222,  -599,  2813,  1903,  -599,   428,    24,
     292,   411,   418,   -23,  -599,  -599,  -599,  -599,  -599,  -599,
     239,  -599,  -599,  -599,  -599,    60,  -599,   213,     7,   471,
    -599,   677,  -599,  -599,   455,    34,   432,   235,   235,  2052,
     544,   441,  1456,  -599,  -599,  -599,  -599,  -599,  -599,  -599,
    -599,  -599,  -599,  -599,  -599,  -599,  2824,  2824,  2824,  2824,
    2824,  2824,  2824,  2824,  2824,  2824,  2824,  2824,  2824,  2824,
    2824,  -599,  2824,  2824,  2824,  2824,  2824,  2824,  2824,  2824,
    2102,   507,  2824,   235,    10,  -599,  2824,  2824,   243,   293,
     -23,  -599,   239,  -599,  -599,  -599,  -599,  -599,   842,   508,
     517,   485,  2824,  2130,  -599,  -599,  -599,  -599,  -599,  1568,
     491,  2824,   496,   303,  -599,  -599,   -44,  -599,  -599,  -599,
    -599,   500,    69,  -599,   509,   502,   537,   247,   270,  -599,
     224,   272,  -599,  -599,  -599,   511,  -599,  -599,   692,  2183,
    -599,  2824,   620,  -599,  -599,   219,   219,   235,   235,   376,
     376,   235,  2748,  2773,   345,   345,  2689,  2664,  2052,  2015,
    2824,   482,   482,  2798,  2798,   482,   482,  1605,   648,   513,
    1717,  -599,  2052,  -599,  -599,  1903,   510,   545,   514,    63,
    -599,  -599,   511,   511,   368,   379,  -599,  -599,  -599,  1903,
    -599,  1903,  2824,  -599,  1903,  -599,   518,    83,  -599,  -599,
     287,  -599,   515,   -43,   570,   998,  -599,   519,  -599,    24,
      42,   206,  -599,   211,  -599,  -599,  -599,  -599,  -599,   525,
    -599,    95,  2192,   511,   160,   372,    98,  -599,   528,  1269,
    1903,   -67,   516,  2015,  2824,  -599,  -599,  -599,  -599,   185,
    -599,  -599,   530,   407,  -599,    61,   511,   511,  1903,  -599,
     546,  -599,   396,   511,   541,  -599,    92,  -599,  -599,   565,
    -599,   558,  -599,  1903,   561,  -599,   562,  -599,  -599,   563,
     572,  2529,  -599,   564,   850,  -599,   590,  -599,   286,   629,
    1157,  -599,  -599,   618,  -599,    99,  -599,   628,  -599,  -599,
    -599,  2824,  -599,  2203,  -599,  2639,  2490,  -599,   545,  -599,
    -599,   633,  -599,   -81,  -599,   631,  -599,  -599,  -599,  -599,
    -599,   634,  -599,   639,    25,  -599,  2824,  -599,  -599,  -599,
    -599,  -599,  2501,  -599,  1903,  -599,   121,  2824,  -599,  -599,
    -599,  -599,   657,  -599,  -599,   511,   659,  -599,   409,  1754,
    -599,  1903,  -599,  -599,   661,   412,  -599,  -599,  -599,   662,
    -599,  -599,  -599,  -599,   660,   295,   188,   666,  1903,   462,
     294,  -599,   168,  -599,   670,   673,  -599,   -24,  -599,  -599,
    -599,  -599,  -599,  -599,  -599,   298,   188,   667,  -599,  -599,
     671,  -599,   675,   683,   102,  -599,   301,   331,    26,   744,
    -599,  -599,  -599,  -599,   146,  2501,  -599,   539,  -599,   687,
     689,   690,   109,  -599,    26,  -599,   694,  -599,  -599,  2231,
     699,  -599,   388,   709,  -599,   111,   713,  -599,   174,  -599,
     404,    36,  -599,   714,   720,   724,  -599,   728,   740,   725,
     729,  2538,  -599,  -599,  -599,  -599,  -599,  1306,  -599,  -599,
    -599,  -599,  -599,  2082,   741,  -599,   406,    49,  -599,   732,
     691,  -599,  -599,  -599,  -599,   742,  -599,   447,  -599,   743,
    -599,   475,  -599,    85,  -599,   476,  -599,  -599,  1005,  2293,
    2453,  -599,  -599,  2824,  -599,  -599,  1419,  -599,  -599,   175,
    -599,  -599,  -599,  -599,   477,  -599,  -599,   751,  -599,  -599,
    -599,  -599,  -599,  -599,  -599,   762,  -599,  -599,    22,   221,
    -599,   767,  2824,   768,  2824,   840,   143,  2824,  -599,   462,
    -599,   770,    50,   236,  -599,  -599,  -599,   773,   480,   771,
    -599,    18,  2453,   778,   222,  2453,   154,   791,  -599,   158,
     830,  -599,   821,   820,   793,  -599,   252,  -599,   794,    64,
    -599,  -599,   506,  -599,  -599,  -599,  2824,  -599,  2453,  2824,
     797,  2453,  -599,   833,    66,  -599,  -599,   512,  -599,  -599,
    -599,   799,   851,   800,    76,   812,  -599,   161,   268,   882,
     814,   815,   866,   145,    80,  -599,  2304,   867,  -599,   819,
     851,  2824,   823,  2332,   112,   425,  -599,   938,  -599,   866,
     866,  2341,   867,   824,   866,   825,   866,   828,   964,  2379,
     874,  -599,   867,   835,  -599,   843,  1866,   844,  -599,  -599,
    -599,  2453,   948,   867,   867,  -599,   242,   874,   866,   867,
     866,   867,  -599,   838,  -599,   841,   105,  2417,    39,   874,
    2453,  -599,  -599,  -599,  -599,  -599,  -599,   874,   874,   847,
    -599,    53,   867,   874,   867,   874,  -599,  -599,   848,  -599,
     863,   395,   889,  -599,    54,  -599,  -599,  -599,  -599,   265,
     837,   839,  -599,   846,  -599,   874,   879,   874,    58,  -599,
    -599,  -599,  -599,   887,  -599,   533,   723,   777,  -599,  -599,
    -599,   890,  -599,   891,   892,  -599,  -599,  -599,  -599,  -599
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -599,  -599,  -599,    15,  -599,   -63,  -599,  -599,   860,  -599,
    -599,   957,  -599,  -599,  -599,  -599,  -599,  -599,  -599,   -10,
    -599,   813,   747,   910,   -18,  -599,   739,  -599,  -319,  -599,
     559,   -62,   -17,  -599,   703,    33,   -65,  -599,   730,  -599,
     621,  -599,  -599,  -599,  -599,  -599,   643,  1027,  -599,  -599,
     553,   566,  -599,  -599,   451,  -599,   393,   170,   375,   340,
     599,  -599,   587,  -599,  -599,  -599,  -599,   520,  -558,  -523,
    -599,  -599,  -599,  -599,  -599,  -599,  -599,  -599,  -599,   394,
    -599,  -599,  -599,  -599,  -598,    -6,    -7,  -599,  -599,  -599,
     250,  -599,  -599,   663,  -599,  1042,   -45,  -599,  -599,   688,
    -599,  -599,  -599,  -599,  -599,  -599,  -599,   746,   893,   894,
     148,  1053,  -599,  -599,   552,   556,  -599,  -599,   465,  -599,
     264,   413,  -599,  -599,  -599,  -599
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -384
static const short yytable[] =
{
      50,    53,    55,    57,    56,    88,    88,    93,    94,    69,
      71,    57,    73,    76,   186,    92,   165,   575,   635,   611,
     190,   600,   393,   587,   243,   194,   424,   489,    28,    62,
     418,   329,   107,   108,   168,   207,   109,   534,    83,    36,
     722,   205,   112,   339,   362,   153,   105,   412,    64,   363,
     553,   602,    77,   673,   733,   743,    90,    90,    90,   754,
      95,   195,   375,   196,   312,   631,   270,   641,   179,   615,
     277,    95,   617,   271,   160,   330,   106,   649,    78,  -128,
      31,   665,    32,    33,   320,   612,   565,   469,   425,   588,
      96,   490,   363,   381,   249,   636,   346,   250,   639,   357,
     406,   568,   535,   480,   252,   253,   718,   184,   185,  -128,
     514,   183,   525,   677,    98,   554,   244,   603,   269,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,    36,   231,   232,   233,   234,   235,
     236,   237,   238,   240,   293,   242,   729,   493,   510,   237,
     245,   208,  -128,    31,  -165,    32,    33,   723,   705,   -65,
      38,    39,    40,    41,    42,   259,   261,  -383,   745,   746,
     747,   734,   744,   313,   264,   529,   755,   725,   376,    43,
     314,   632,  -128,   642,   278,   279,   494,   495,   496,   497,
     498,   499,   500,   650,   316,   317,   501,   666,   321,   322,
     566,    64,   299,   382,   300,    44,    45,   323,   101,   341,
     347,   348,   343,   102,   407,   408,   358,   481,   482,   678,
     719,    46,   589,   303,   515,   516,   526,   527,   663,    47,
     354,    48,   435,   101,   124,   125,   436,   604,   128,   129,
     191,   295,   132,   709,   246,   456,   366,   197,   284,   198,
     124,   125,   457,   626,   598,   318,    49,   269,   197,   157,
     198,   502,   664,   503,   504,   618,   493,   333,   333,   621,
     157,   286,   652,   289,   157,   351,   100,   157,   352,    38,
      39,    40,    41,    42,   465,   350,   466,   399,   324,   530,
     531,   172,   405,   580,   248,   103,   452,   365,    43,   470,
     367,   368,   483,    36,   266,   494,   495,   496,   497,   498,
     499,   500,   110,  -260,  -260,   501,   653,   654,   292,   627,
     104,   344,   184,   185,    44,    45,  -337,   434,   199,   295,
     285,   150,   486,   151,   394,   582,   590,   591,   157,   288,
      46,  -128,    31,   354,    32,    33,    64,   150,    47,   151,
      48,   605,   606,   287,   409,   290,   411,   710,   173,   394,
     124,   125,   126,   127,   128,   129,    93,    94,   132,   400,
     165,  -128,   166,   353,    92,    49,   184,   185,   453,   428,
     502,   471,   503,  -260,   484,   394,   184,   185,   167,   522,
     300,   124,   125,   126,   127,   128,   129,   378,   325,   132,
     434,  -114,   135,   136,   110,   532,   168,   551,   371,   187,
     440,   462,   463,   444,   487,  -379,   171,    90,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   182,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   560,   142,
     143,   144,   145,   146,   147,   184,   185,   150,   394,   151,
     394,  -128,    31,    63,    32,    33,  -128,    31,   158,    32,
      33,   453,   520,   653,   654,   445,   563,   567,   581,   184,
     185,   608,  -128,    31,   169,    32,    33,   533,   150,   471,
     151,  -128,   184,   185,   546,   170,  -128,   124,   125,   126,
     127,   128,   129,   130,   131,   132,    69,   633,   135,   136,
     741,   157,  -128,   643,   172,    78,  -128,    31,   372,    32,
      33,   148,   419,   149,   334,   336,   173,   150,   188,   151,
     561,  -379,   201,  -379,   493,   189,    57,   576,   206,    31,
     509,    32,    33,   679,   209,  -273,  -128,    38,    39,    40,
      41,    42,   213,    38,    39,    40,    41,    42,   564,   568,
     582,   462,   463,   609,   447,    57,    43,    57,   596,   450,
      57,   599,    43,   494,   495,   496,   497,   498,   499,   500,
     -14,  -258,  -258,   501,    38,    39,    40,    41,    42,   634,
     241,   256,    44,    45,   150,   644,   151,   476,    44,    45,
     257,   258,   -15,    43,    31,    63,    32,    33,    46,    57,
     263,   265,    57,   637,    46,   276,    47,   282,    48,   270,
     283,   302,    47,   292,    48,   307,   305,   364,   308,    44,
      45,   311,   328,   319,   337,    31,   158,    32,    33,   668,
     345,   360,   159,    49,    57,    46,   676,   370,   502,    49,
     503,  -258,   380,    47,    71,    48,   392,    31,   158,    32,
      33,   377,    55,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   386,   387,   135,   136,   388,   389,   203,   395,
      49,   390,   142,   143,   144,   145,   146,   147,   332,   391,
      57,   721,   557,   294,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   398,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   493,   142,   143,   144,   145,   146,
     147,  -128,    31,   404,    32,    33,    27,    38,    39,    40,
      41,    42,   401,   351,   417,   422,  -128,    31,   420,    32,
      33,  -128,    31,   158,    32,    33,    43,   423,    -4,   159,
     150,  -128,   151,   494,   495,   496,   497,   498,   499,   500,
     438,  -256,  -256,   501,   439,   451,  -128,   467,   493,   443,
     448,  -128,    44,    45,   461,   475,    28,   -32,   468,   477,
     478,    38,    39,    40,    41,    42,   -32,   148,    46,   149,
     479,   456,   511,   150,   512,   151,    47,   513,    48,   558,
      43,    78,   518,    31,   521,    32,    33,   494,   495,   496,
     497,   498,   499,   500,   524,  -262,  -262,   501,   528,   537,
     538,   493,   687,    49,   539,   543,    44,    45,   502,   544,
     503,  -256,   699,   541,    38,    39,    40,    41,    42,    -3,
     556,   396,    46,   707,   708,   542,   550,   559,   562,   713,
      47,   715,    48,    43,   -25,   -25,   -25,   -25,   -25,   585,
     494,   495,   496,   497,   498,   499,   500,   586,   592,   595,
     501,   597,   735,   -25,   737,   601,   610,    49,   623,    44,
      45,   607,   502,   616,   503,  -262,  -128,    31,    63,    32,
      33,   619,    78,   624,    31,    46,    32,    33,   625,   -25,
     -25,    79,   630,    47,   638,    48,   640,   645,   648,   646,
      80,    81,    82,   683,   684,   -25,  -128,   651,   689,   657,
     691,   659,   660,   -25,   661,   -25,   669,   671,   674,  -251,
      49,   688,   690,   692,   697,   502,   700,   503,   622,   706,
     701,   703,   712,   716,   714,   748,   717,   749,   200,    24,
     -25,   -25,   732,   739,   750,   693,   -25,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   740,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   752,   142,   143,
     144,   145,   146,   147,   742,   756,   571,   280,   757,   758,
     759,   204,    38,    39,    40,    41,    42,   326,   338,  -232,
    -232,  -232,  -232,  -232,   508,   379,   359,   711,   427,   441,
      25,    43,    78,  -128,    31,   523,    32,    33,  -232,   724,
     517,    79,   613,   672,   696,   474,   492,   730,   731,   680,
      80,    81,    82,   736,    60,   738,   413,    44,    45,   373,
     437,   254,   255,  -128,  -232,  -232,    61,   579,   552,   549,
     148,   628,   149,    46,   686,   751,   150,   753,   151,   694,
    -232,    47,     0,    48,     0,     0,     0,     0,  -232,     0,
    -232,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    49,     0,
       0,     0,     0,     0,     0,  -232,   335,     0,     0,   154,
    -232,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   155,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,     0,   142,   143,   144,   145,   146,   147,   402,     0,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,     0,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
       0,   142,   143,   144,   145,   146,   147,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,     0,     0,     0,
       0,     0,     0,     0,   156,     0,   149,     0,     0,     0,
     150,     0,   151,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   148,     0,   149,     0,     0,     0,   150,
     403,   151,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,     0,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,     0,   142,   143,   144,   145,   146,   147,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
       0,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,     0,
     142,   143,   144,   145,   146,   147,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   148,     0,   149,     0,     0,
       0,   150,     0,   151,     0,   361,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   148,     0,   149,     0,     0,     0,   150,     0,
     151,   548,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,     0,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,     0,   142,   143,   144,   145,   146,   147,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
       0,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,     0,
     142,   143,   144,   145,   146,   147,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   148,     0,   149,     0,     0,
       0,   150,     0,   151,   578,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   148,     0,   149,     0,     0,   214,   150,     0,
     151,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,     0,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,     0,   142,   143,   144,   145,   146,   147,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,     0,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,     0,   142,
     143,   144,   145,   146,   147,     0,     0,     0,   262,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   148,     0,   149,     0,     0,     0,
     150,     0,   151,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   148,   304,   149,     0,     0,     0,   150,     0,   151,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,     0,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
       0,   142,   143,   144,   145,   146,   147,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,     0,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,     0,   142,   143,
     144,   145,   146,   147,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   148,     0,   149,     0,     0,     0,   150,
     306,   151,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     148,     0,   149,     0,     0,     0,   150,   442,   151,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
       0,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,     0,
     142,   143,   144,   145,   146,   147,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,     0,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,     0,   142,   143,   144,
     145,   146,   147,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   148,   702,   149,     0,     0,     0,   150,     0,
     151,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   148,
       0,   149,     0,     0,     0,   150,     0,   151,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,     0,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,     0,     0,     0,   142,
     143,   144,   145,   146,   147,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,     0,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,     0,    68,     0,     0,   142,   143,   144,   145,
     146,   147,     0,     0,   111,     0,    38,    39,    40,    41,
      42,     0,     0,   239,     0,     0,     0,    38,    39,    40,
      41,    42,     0,     0,     0,    43,    38,    39,    40,    41,
      42,   148,     0,   149,     0,     0,    43,   150,     0,   151,
       0,   260,     0,     0,     0,    43,     0,     0,     0,     0,
       0,    44,    45,     0,    38,    39,    40,    41,    42,     0,
       0,     0,    44,    45,     0,     0,     0,    46,   148,     0,
     149,    44,    45,    43,   150,    47,   151,    48,    46,     0,
       0,     0,     0,     0,     0,     0,    47,    46,    48,     0,
       0,     0,     0,     0,   298,    47,     0,    48,     0,    44,
      45,     0,    49,   349,     0,     0,     0,    38,    39,    40,
      41,    42,     0,    49,   410,    46,    38,    39,    40,    41,
      42,     0,    49,    47,     0,    48,    43,    38,    39,    40,
      41,    42,     0,     0,     0,    43,     0,     0,     0,     0,
       0,     0,   519,     0,     0,     0,    43,     0,     0,     0,
      49,     0,    44,    45,     0,    38,    39,    40,    41,    42,
       0,    44,    45,     0,     0,     0,     0,     0,    46,     0,
       0,     0,    44,    45,    43,     0,    47,    46,    48,     0,
       0,     0,     0,     0,     0,    47,     0,    48,    46,     0,
       0,     0,     0,     0,     0,     0,    47,     0,    48,     0,
      44,    45,     0,    49,   573,     0,     0,     0,     0,     0,
       0,     0,    49,     0,     0,   667,    46,  -235,  -235,  -235,
    -235,  -235,     0,    49,    47,     0,    48,     0,    38,    39,
      40,    41,    42,     0,     0,     0,  -235,     0,     0,     0,
       0,     0,     0,   675,     0,     0,     0,    43,     0,     0,
       0,    49,   685,     0,     0,     0,    38,    39,    40,    41,
      42,     0,  -235,  -235,     0,    38,    39,    40,    41,    42,
       0,     0,     0,    44,    45,    43,     0,     0,  -235,     0,
       0,     0,     0,     0,    43,     0,  -235,     0,  -235,    46,
     695,     0,     0,     0,     0,     0,     0,    47,     0,    48,
       0,    44,    45,    38,    39,    40,    41,    42,     0,     0,
      44,    45,     0,  -235,     0,     0,     0,    46,     0,     0,
       0,     0,    43,     0,    49,    47,    46,    48,   720,     0,
       0,     0,     0,     0,    47,     0,    48,     0,     0,     0,
       0,    38,    39,    40,    41,    42,     0,     0,    44,    45,
       0,     0,    49,     0,     0,     0,     0,     0,     0,     0,
      43,    49,     0,     0,    46,     0,     0,     0,     0,     0,
       0,     0,    47,     0,    48,     0,     0,    38,    39,    40,
      41,    42,     0,     0,     0,     0,    44,    45,     0,     0,
       0,     0,     0,     0,     0,     0,    43,     0,     0,    49,
       0,     0,    46,   494,   495,   496,   497,   498,   499,   500,
      47,     0,    48,   501,    38,    39,    40,    41,    42,     0,
       0,     0,    44,    45,     0,    38,    39,    40,    41,    42,
       0,     0,     0,    43,     0,     0,     0,    49,    46,     0,
       0,     0,     0,     0,    43,     0,    47,     0,    48,     0,
       0,     0,     0,    38,    39,    40,    41,    42,     0,    44,
      45,     0,    38,    39,    40,    41,    42,     0,     0,     0,
      44,    45,    43,    49,     0,    46,     0,     0,   502,     0,
     503,    43,     0,    47,     0,    48,    46,     0,     0,     0,
       0,     0,     0,     0,   430,   185,    48,     0,    44,    45,
       0,     0,     0,     0,     0,     0,     0,    44,    45,     0,
      49,     0,   292,     0,    46,     0,     0,   392,     0,     0,
       0,    49,    47,    46,    48,     0,     0,     0,   392,     0,
       0,    47,     0,    48,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    49,
       0,     0,     0,     0,     0,     0,   392,     0,    49,     0,
       0,     0,     0,   545,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,     0,
       0,     0,     0,   142,   143,   144,   145,   146,   147,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,     0,     0,     0,     0,     0,   142,   143,
     144,   145,   146,   147,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,     0,     0,     0,
       0,     0,     0,   142,   143,   144,   145,   146,   147,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   148,     0,   149,     0,     0,
       0,   150,     0,   151,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   149,   134,   135,   136,   150,     0,   151,     0,
       0,     0,   142,   143,   144,   145,   146,   147,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   149,     0,   135,
     136,   150,     0,   151,     0,     0,     0,   142,   143,   144,
     145,   146,   147,   124,   125,   126,   127,   128,   129,   130,
     131,   132,     0,     0,   135,   136,     0,    38,    39,    40,
      41,    42,   142,   143,     0,     0,   146,   147,    38,    39,
      40,    41,    42,     0,     0,     0,    43,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   149,    43,     0,     0,
     150,     0,   151,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    44,    45,     0,     0,     0,     0,     0,     0,
       0,   149,     0,    44,    45,   150,     0,   151,    46,   174,
     175,   176,   177,     0,   178,     0,    47,     0,    48,    46,
       0,     0,     0,     0,     0,     0,     0,    47,     0,    48,
     150,     0,   151,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    49,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    49
};

static const short yycheck[] =
{
       7,     8,     9,    10,    10,    23,    24,    25,    25,    16,
      17,    18,    18,    20,    79,    25,    61,   540,   616,     1,
      83,   579,   341,     1,    14,    90,     1,     1,    51,    14,
     111,    74,    39,    40,   115,     1,    43,     1,    23,     6,
       1,   103,    49,     1,   111,    52,    54,   366,    15,   116,
       1,     1,     0,   651,     1,     1,    23,    24,    25,     1,
      83,     1,     1,     3,     1,     1,   110,     1,    75,   592,
       1,    83,   595,   117,    59,   118,    84,     1,    53,    54,
      55,     1,    57,    58,     1,    67,     1,   111,    63,    67,
      83,    65,   116,     1,   159,   618,     1,   160,   621,     1,
       1,    83,    66,     1,   166,   167,     1,    83,    84,    84,
       1,    78,     1,     1,    52,    66,   106,    67,   183,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   101,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   206,   152,   704,     1,   467,   156,
     157,   117,    54,    55,   118,    57,    58,   118,   681,   117,
      14,    15,    16,    17,    18,   172,   173,   118,   726,   727,
     728,   118,   118,   110,   181,     1,   118,   700,   117,    33,
     117,   117,    84,   117,   115,   116,    40,    41,    42,    43,
      44,    45,    46,   117,   256,   257,    50,   117,   115,   116,
     115,   168,   209,   111,   211,    59,    60,   269,   116,     3,
     115,   116,     1,     1,   115,   116,   118,   115,   116,   107,
     115,    75,     1,   230,   115,   116,   115,   116,    83,    83,
     295,    85,   111,   116,    15,    16,   115,     1,    19,    20,
       1,   208,    23,     1,     1,    57,   308,    34,     1,    36,
      15,    16,    64,     1,   111,   262,   110,   322,    34,   116,
      36,   115,   117,   117,   118,   111,     1,   274,   275,   111,
     116,     1,   111,     1,   116,   115,    58,   116,   118,    14,
      15,    16,    17,    18,   116,   292,   118,     1,     1,   115,
     116,   116,   354,   118,     1,    83,     1,   304,    33,     1,
     115,   116,     1,   270,     1,    40,    41,    42,    43,    44,
      45,    46,   110,    48,    49,    50,    48,    49,   112,    67,
     108,   110,    83,    84,    59,    60,    83,   392,   115,   296,
      83,   112,     1,   114,   341,    83,   115,   116,   116,   115,
      75,    54,    55,   408,    57,    58,   313,   112,    83,   114,
      85,   115,   116,    83,   361,    83,   363,   115,   116,   366,
      15,    16,    17,    18,    19,    20,   384,   384,    23,    83,
     415,    84,    83,     1,   384,   110,    83,    84,    83,   386,
     115,    83,   117,   118,    83,   392,    83,    84,    83,     1,
     397,    15,    16,    17,    18,    19,    20,     1,   111,    23,
     465,   107,    26,    27,   110,     1,   115,     1,     1,   117,
       1,   429,   429,     1,    83,     0,     1,   384,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,     1,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,     1,    34,
      35,    36,    37,    38,    39,    83,    84,   112,   465,   114,
     467,    54,    55,    56,    57,    58,    54,    55,    56,    57,
      58,    83,   479,    48,    49,    63,     1,     1,     1,    83,
      84,     1,    54,    55,   116,    57,    58,    83,   112,    83,
     114,    84,    83,    84,   501,   116,    84,    15,    16,    17,
      18,    19,    20,    21,    22,    23,   513,     1,    26,    27,
     115,   116,    84,     1,   116,    53,    54,    55,   111,    57,
      58,   106,   374,   108,   274,   275,   116,   112,   117,   114,
      83,   116,    61,   118,     1,   117,   543,   543,    83,    55,
       1,    57,    58,   118,   112,     1,    84,    14,    15,    16,
      17,    18,   111,    14,    15,    16,    17,    18,    83,    83,
      83,   579,   579,    83,   416,   572,    33,   574,   574,   421,
     577,   577,    33,    40,    41,    42,    43,    44,    45,    46,
       0,    48,    49,    50,    14,    15,    16,    17,    18,    83,
      83,    83,    59,    60,   112,    83,   114,   449,    59,    60,
      83,   116,     0,    33,    55,    56,    57,    58,    75,   616,
     119,   115,   619,   619,    75,   115,    83,   115,    85,   110,
      83,     1,    83,   112,    85,   115,   113,   111,    83,    59,
      60,   117,   117,   115,   115,    55,    56,    57,    58,   646,
     115,   113,    62,   110,   651,    75,   653,   117,   115,   110,
     117,   118,   111,    83,   661,    85,   117,    55,    56,    57,
      58,   115,   669,    15,    16,    17,    18,    19,    20,    21,
      22,    23,   107,   115,    26,    27,   115,   115,     1,   115,
     110,   118,    34,    35,    36,    37,    38,    39,   118,   117,
     697,   697,     1,     1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,   115,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,     1,    34,    35,    36,    37,    38,
      39,    54,    55,   115,    57,    58,     1,    14,    15,    16,
      17,    18,   113,   115,   111,   111,    54,    55,   117,    57,
      58,    54,    55,    56,    57,    58,    33,   118,     0,    62,
     112,    84,   114,    40,    41,    42,    43,    44,    45,    46,
     113,    48,    49,    50,   115,   115,    84,   107,     1,   118,
     118,    84,    59,    60,   118,   118,    51,    52,   115,   118,
     115,    14,    15,    16,    17,    18,    61,   106,    75,   108,
     117,    57,   115,   112,   115,   114,    83,   117,    85,   118,
      33,    53,   118,    55,   115,    57,    58,    40,    41,    42,
      43,    44,    45,    46,   115,    48,    49,    50,   115,   115,
     110,     1,   662,   110,   110,   110,    59,    60,   115,   110,
     117,   118,   672,   115,    14,    15,    16,    17,    18,     0,
     118,     1,    75,   683,   684,   115,   115,   115,   115,   689,
      83,   691,    85,    33,    14,    15,    16,    17,    18,   118,
      40,    41,    42,    43,    44,    45,    46,   115,   111,   111,
      50,    41,   712,    33,   714,   115,   115,   110,    67,    59,
      60,   118,   115,   115,   117,   118,    54,    55,    56,    57,
      58,   110,    53,    83,    55,    75,    57,    58,   115,    59,
      60,    62,   118,    83,   117,    85,    83,   118,   118,    68,
      71,    72,    73,   659,   660,    75,    84,   115,   664,    47,
     666,   117,   117,    83,    68,    85,    69,   118,   115,     1,
     110,   117,   117,   115,    70,   115,   111,   117,   118,     1,
     107,   107,   688,   115,   690,   118,   115,   118,    98,     2,
     110,   111,   115,   115,   118,     1,   116,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,   115,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,   118,    34,    35,
      36,    37,    38,    39,   115,   118,     1,   194,   118,   118,
     118,   101,    14,    15,    16,    17,    18,   270,   279,    14,
      15,    16,    17,    18,   465,   322,   296,   687,   385,   408,
       3,    33,    53,    54,    55,   482,    57,    58,    33,   699,
     474,    62,   591,   650,   669,   446,   459,   707,   708,   655,
      71,    72,    73,   713,    12,   715,   368,    59,    60,   313,
     397,   168,   168,    84,    59,    60,    13,   547,   516,   513,
     106,   606,   108,    75,   661,   735,   112,   737,   114,   115,
      75,    83,    -1,    85,    -1,    -1,    -1,    -1,    83,    -1,
      85,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   110,    -1,
      -1,    -1,    -1,    -1,    -1,   110,   118,    -1,    -1,     1,
     115,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    -1,    34,    35,    36,    37,    38,    39,     1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      -1,    34,    35,    36,    37,    38,    39,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   106,    -1,   108,    -1,    -1,    -1,
     112,    -1,   114,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   106,    -1,   108,    -1,    -1,    -1,   112,
     113,   114,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    -1,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    -1,    34,    35,    36,    37,    38,    39,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    -1,
      34,    35,    36,    37,    38,    39,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   106,    -1,   108,    -1,    -1,
      -1,   112,    -1,   114,    -1,   116,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   106,    -1,   108,    -1,    -1,    -1,   112,    -1,
     114,   115,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    -1,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    -1,    34,    35,    36,    37,    38,    39,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    -1,
      34,    35,    36,    37,    38,    39,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   106,    -1,   108,    -1,    -1,
      -1,   112,    -1,   114,   115,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   106,    -1,   108,    -1,    -1,   111,   112,    -1,
     114,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    -1,    34,    35,    36,    37,    38,    39,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    34,
      35,    36,    37,    38,    39,    -1,    -1,    -1,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   106,    -1,   108,    -1,    -1,    -1,
     112,    -1,   114,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   106,   107,   108,    -1,    -1,    -1,   112,    -1,   114,
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
     113,   114,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     106,    -1,   108,    -1,    -1,    -1,   112,   113,   114,     3,
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
      -1,    -1,   106,   107,   108,    -1,    -1,    -1,   112,    -1,
     114,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   106,
      -1,   108,    -1,    -1,    -1,   112,    -1,   114,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    -1,    -1,    -1,    34,
      35,    36,    37,    38,    39,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    -1,     1,    -1,    -1,    34,    35,    36,    37,
      38,    39,    -1,    -1,     1,    -1,    14,    15,    16,    17,
      18,    -1,    -1,     1,    -1,    -1,    -1,    14,    15,    16,
      17,    18,    -1,    -1,    -1,    33,    14,    15,    16,    17,
      18,   106,    -1,   108,    -1,    -1,    33,   112,    -1,   114,
      -1,     1,    -1,    -1,    -1,    33,    -1,    -1,    -1,    -1,
      -1,    59,    60,    -1,    14,    15,    16,    17,    18,    -1,
      -1,    -1,    59,    60,    -1,    -1,    -1,    75,   106,    -1,
     108,    59,    60,    33,   112,    83,   114,    85,    75,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    83,    75,    85,    -1,
      -1,    -1,    -1,    -1,     1,    83,    -1,    85,    -1,    59,
      60,    -1,   110,     1,    -1,    -1,    -1,    14,    15,    16,
      17,    18,    -1,   110,     1,    75,    14,    15,    16,    17,
      18,    -1,   110,    83,    -1,    85,    33,    14,    15,    16,
      17,    18,    -1,    -1,    -1,    33,    -1,    -1,    -1,    -1,
      -1,    -1,     1,    -1,    -1,    -1,    33,    -1,    -1,    -1,
     110,    -1,    59,    60,    -1,    14,    15,    16,    17,    18,
      -1,    59,    60,    -1,    -1,    -1,    -1,    -1,    75,    -1,
      -1,    -1,    59,    60,    33,    -1,    83,    75,    85,    -1,
      -1,    -1,    -1,    -1,    -1,    83,    -1,    85,    75,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    83,    -1,    85,    -1,
      59,    60,    -1,   110,     1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   110,    -1,    -1,     1,    75,    14,    15,    16,
      17,    18,    -1,   110,    83,    -1,    85,    -1,    14,    15,
      16,    17,    18,    -1,    -1,    -1,    33,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    -1,    -1,    33,    -1,    -1,
      -1,   110,     1,    -1,    -1,    -1,    14,    15,    16,    17,
      18,    -1,    59,    60,    -1,    14,    15,    16,    17,    18,
      -1,    -1,    -1,    59,    60,    33,    -1,    -1,    75,    -1,
      -1,    -1,    -1,    -1,    33,    -1,    83,    -1,    85,    75,
       1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    -1,    85,
      -1,    59,    60,    14,    15,    16,    17,    18,    -1,    -1,
      59,    60,    -1,   110,    -1,    -1,    -1,    75,    -1,    -1,
      -1,    -1,    33,    -1,   110,    83,    75,    85,     1,    -1,
      -1,    -1,    -1,    -1,    83,    -1,    85,    -1,    -1,    -1,
      -1,    14,    15,    16,    17,    18,    -1,    -1,    59,    60,
      -1,    -1,   110,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      33,   110,    -1,    -1,    75,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    83,    -1,    85,    -1,    -1,    14,    15,    16,
      17,    18,    -1,    -1,    -1,    -1,    59,    60,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    -1,    -1,   110,
      -1,    -1,    75,    40,    41,    42,    43,    44,    45,    46,
      83,    -1,    85,    50,    14,    15,    16,    17,    18,    -1,
      -1,    -1,    59,    60,    -1,    14,    15,    16,    17,    18,
      -1,    -1,    -1,    33,    -1,    -1,    -1,   110,    75,    -1,
      -1,    -1,    -1,    -1,    33,    -1,    83,    -1,    85,    -1,
      -1,    -1,    -1,    14,    15,    16,    17,    18,    -1,    59,
      60,    -1,    14,    15,    16,    17,    18,    -1,    -1,    -1,
      59,    60,    33,   110,    -1,    75,    -1,    -1,   115,    -1,
     117,    33,    -1,    83,    -1,    85,    75,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    83,    84,    85,    -1,    59,    60,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,    60,    -1,
     110,    -1,   112,    -1,    75,    -1,    -1,   117,    -1,    -1,
      -1,   110,    83,    75,    85,    -1,    -1,    -1,   117,    -1,
      -1,    83,    -1,    85,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   110,
      -1,    -1,    -1,    -1,    -1,    -1,   117,    -1,   110,    -1,
      -1,    -1,    -1,   115,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    -1,
      -1,    -1,    -1,    34,    35,    36,    37,    38,    39,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    -1,    -1,    -1,    -1,    -1,    34,    35,
      36,    37,    38,    39,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    -1,    -1,    -1,
      -1,    -1,    -1,    34,    35,    36,    37,    38,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   106,    -1,   108,    -1,    -1,
      -1,   112,    -1,   114,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    15,    16,    17,    18,    19,    20,    21,
      22,    23,   108,    25,    26,    27,   112,    -1,   114,    -1,
      -1,    -1,    34,    35,    36,    37,    38,    39,    15,    16,
      17,    18,    19,    20,    21,    22,    23,   108,    -1,    26,
      27,   112,    -1,   114,    -1,    -1,    -1,    34,    35,    36,
      37,    38,    39,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    -1,    -1,    26,    27,    -1,    14,    15,    16,
      17,    18,    34,    35,    -1,    -1,    38,    39,    14,    15,
      16,    17,    18,    -1,    -1,    -1,    33,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   108,    33,    -1,    -1,
     112,    -1,   114,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    59,    60,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   108,    -1,    59,    60,   112,    -1,   114,    75,    76,
      77,    78,    79,    -1,    81,    -1,    83,    -1,    85,    75,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    -1,    85,
     112,    -1,   114,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   110,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   110
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   121,   122,   131,   131,   167,   123,     1,    51,   125,
     126,    55,    57,    58,   142,   143,   155,   161,    14,    15,
      16,    17,    18,    33,    59,    60,    75,    83,    85,   110,
     206,   210,   212,   206,   178,   206,   205,   206,   214,   215,
     215,   231,   123,    56,   155,   227,   228,   229,     1,   206,
     235,   206,   241,   205,   242,   243,   206,     0,    53,    62,
      71,    72,    73,   123,   132,   135,   136,   139,   144,   152,
     155,   163,   139,   144,   152,    83,    83,   128,    52,   127,
      58,   116,     1,    83,   108,    54,    84,   206,   206,   206,
     110,     1,   206,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    34,    35,    36,    37,    38,    39,   106,   108,
     112,   114,   211,   206,     1,    14,   106,   116,    56,    62,
     123,   144,   155,   216,   220,   216,    83,    83,   115,   116,
     116,     1,   116,   116,    76,    77,    78,    79,    81,   206,
     244,   245,     1,   155,    83,    84,   156,   117,   117,   117,
     125,     1,   145,   146,   156,     1,     3,    34,    36,   115,
     128,    61,   129,     1,   143,   151,    83,     1,   117,   112,
     162,   207,   208,   111,   111,   206,   206,   206,   206,   206,
     206,   206,   206,   206,   206,   206,   206,   206,   206,   206,
     209,   206,   206,   206,   206,   206,   206,   206,   206,     1,
     206,    83,   206,    14,   106,   206,     1,   217,     1,   156,
     125,   156,   151,   151,   228,   229,    83,    83,   116,   206,
       1,   206,    80,   119,   206,   115,     1,   153,   154,   156,
     110,   117,   141,   133,   137,   138,   115,     1,   115,   116,
     141,   151,   115,    83,     1,    83,     1,    83,   115,     1,
      83,   130,   112,   151,     1,   155,   157,   158,     1,   206,
     206,   213,     1,   206,   107,   113,   113,   115,    83,   218,
     219,   117,     1,   110,   117,   226,   151,   151,   206,   115,
       1,   115,   116,   151,     1,   111,   142,   165,   117,    74,
     118,   134,   118,   206,   210,   118,   210,   115,   146,     1,
     140,     3,   147,     1,   110,   115,     1,   115,   116,     1,
     206,   115,   118,     1,   156,   159,   160,     1,   118,   158,
     113,   116,   111,   116,   111,   206,   151,   115,   116,   224,
     117,     1,   111,   227,   225,     1,   117,   115,     1,   154,
     111,     1,   111,   166,   167,   164,   107,   115,   115,   115,
     118,   117,   117,   148,   206,   115,     1,   124,   115,     1,
      83,   113,     1,   113,   115,   151,     1,   115,   116,   206,
       1,   206,   148,   219,   230,   231,   223,   111,   111,   230,
     117,   221,   111,   118,     1,    63,   168,   166,   206,   187,
      83,   148,   149,   150,   156,   111,   115,   213,   113,   115,
       1,   160,   113,   118,     1,    63,   232,   230,   118,   222,
     230,   115,     1,    83,   169,   170,    57,    64,   180,   181,
     182,   118,   144,   152,   188,   116,   118,   107,   115,   111,
       1,    83,   233,   234,   180,   118,   230,   118,   115,   117,
       1,   115,   116,     1,    83,   184,     1,    83,   183,     1,
      65,   171,   182,     1,    40,    41,    42,    43,    44,    45,
      46,    50,   115,   117,   118,   185,   189,   206,   150,     1,
     148,   115,   115,   117,     1,   115,   116,   171,   118,     1,
     206,   115,     1,   170,   115,     1,   115,   116,   115,     1,
     115,   116,     1,    83,     1,    66,   172,   115,   110,   110,
     192,   115,   115,   110,   110,   115,   206,   186,   115,   235,
     115,     1,   234,     1,    66,   236,   118,     1,   118,   115,
       1,    83,   115,     1,    83,     1,   115,     1,    83,   173,
     174,     1,   190,     1,   191,   189,   205,   193,   115,   187,
     118,     1,    83,   237,   238,   118,   115,     1,    67,     1,
     115,   116,   111,   204,   205,   111,   205,    41,   111,   205,
     188,   115,     1,    67,     1,   115,   116,   118,     1,    83,
     115,     1,    67,   174,   175,   189,   115,   189,   111,   110,
     194,   111,   118,    67,    83,   115,     1,    67,   238,   239,
     118,     1,   117,     1,    83,   204,   189,   205,   117,   189,
      83,     1,   117,     1,    83,   118,    68,   176,   118,     1,
     117,   115,   111,    48,    49,   198,   199,    47,   195,   117,
     117,    68,   240,    83,   117,     1,   117,     1,   206,    69,
     177,   118,   176,   204,   115,     1,   206,     1,   107,   118,
     199,   196,   197,   240,   240,     1,   241,   177,   117,   240,
     117,   240,   115,     1,   115,     1,   178,    70,   179,   177,
     111,   107,   107,   107,   202,   189,     1,   177,   177,     1,
     115,   179,   240,   177,   240,   177,   115,   115,     1,   115,
       1,   205,     1,   118,   179,   189,   201,   200,   203,   188,
     179,   179,   115,     1,   118,   177,   179,   177,   179,   115,
     115,   115,   115,     1,   118,   188,   188,   188,   118,   118,
     118,   179,   118,   179,     1,   118,   118,   118,   118,   118
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
#define YYERROR		do				\
			  {				\
			    yylerrsp = yylsp;		\
			    *++yylerrsp = yyloc;	\
			    goto yyerrlab1;		\
			  }				\
			while (0)


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
# define YYLLOC_DEFAULT(Current, Rhs, N)         \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;
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
| TOP (cinluded).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
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
  unsigned int yylineno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylineno);
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
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
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
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 268 "parser.yy"
    { CALL(yylsp[0], yylsp[0], done()); }
    break;

  case 3:
#line 269 "parser.yy"
    { }
    break;

  case 4:
#line 270 "parser.yy"
    { }
    break;

  case 5:
#line 271 "parser.yy"
    { }
    break;

  case 6:
#line 272 "parser.yy"
    { }
    break;

  case 7:
#line 273 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SYSTEM));
	}
    break;

  case 8:
#line 276 "parser.yy"
    { g_parameter_count = yyvsp[0].number; }
    break;

  case 9:
#line 277 "parser.yy"
    { }
    break;

  case 10:
#line 278 "parser.yy"
    { CALL(yylsp[0], yylsp[0], procGuard()); }
    break;

  case 11:
#line 279 "parser.yy"
    { }
    break;

  case 12:
#line 280 "parser.yy"
    { CALL(yylsp[0], yylsp[0], procUpdate()); }
    break;

  case 13:
#line 281 "parser.yy"
    { CALL(yylsp[0], yylsp[0], done()); }
    break;

  case 14:
#line 282 "parser.yy"
    { }
    break;

  case 15:
#line 283 "parser.yy"
    { }
    break;

  case 16:
#line 284 "parser.yy"
    { }
    break;

  case 17:
#line 285 "parser.yy"
    { g_parameter_count = yyvsp[0].number; }
    break;

  case 18:
#line 286 "parser.yy"
    { }
    break;

  case 19:
#line 287 "parser.yy"
    { CALL(yylsp[0], yylsp[0], procGuard()); }
    break;

  case 20:
#line 288 "parser.yy"
    { CALL(yylsp[0], yylsp[0], procUpdate()); }
    break;

  case 21:
#line 289 "parser.yy"
    {}
    break;

  case 22:
#line 290 "parser.yy"
    {}
    break;

  case 25:
#line 299 "parser.yy"
    {
          CALL(yylsp[-3], yylsp[-1], instantiationBegin(yyvsp[-3].string, yyvsp[-1].string));
	}
    break;

  case 26:
#line 301 "parser.yy"
    {
	  CALL(yylsp[-7], yylsp[0], instantiationEnd(yyvsp[-7].string, yyvsp[-5].string, yyvsp[-2].number));
	}
    break;

  case 27:
#line 304 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_ARGLIST));
	}
    break;

  case 28:
#line 307 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));
	}
    break;

  case 29:
#line 310 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LPAREN));
	}
    break;

  case 30:
#line 313 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_ASSIGN));
	}
    break;

  case 36:
#line 331 "parser.yy"
    { CALL(yylsp[0], yylsp[0], lowPriority(yyvsp[0].string)); }
    break;

  case 37:
#line 332 "parser.yy"
    { CALL(yylsp[0], yylsp[0], samePriority(yyvsp[0].string)); }
    break;

  case 38:
#line 333 "parser.yy"
    { CALL(yylsp[0], yylsp[0], higherPriority(yyvsp[0].string)); }
    break;

  case 39:
#line 334 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_PRIORITY_));
	}
    break;

  case 40:
#line 337 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_PRIORITY_));
	}
    break;

  case 42:
#line 344 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 43:
#line 347 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_PROCID));
	}
    break;

  case 44:
#line 353 "parser.yy"
    { CALL(yylsp[0], yylsp[0], process(yyvsp[0].string)); }
    break;

  case 45:
#line 354 "parser.yy"
    { CALL(yylsp[0], yylsp[0], process(yyvsp[0].string)); }
    break;

  case 46:
#line 355 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_PROCID_));
	}
    break;

  case 62:
#line 386 "parser.yy"
    {
	  CALL(yylsp[-1], yylsp[-1], beforeUpdate());
        }
    break;

  case 64:
#line 392 "parser.yy"
    {
	  CALL(yylsp[-1], yylsp[-1], afterUpdate());
        }
    break;

  case 65:
#line 397 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], declFuncBegin(yyvsp[-1].string, yyvsp[0].number));
	}
    break;

  case 66:
#line 400 "parser.yy"
    { 
	  CALL(yylsp[-7], yylsp[-1], declFuncEnd());
	}
    break;

  case 67:
#line 403 "parser.yy"
    {
	    CALL(yylsp[-4], yylsp[0], declFuncEnd());
	}
    break;

  case 68:
#line 409 "parser.yy"
    { yyval.number = 0; }
    break;

  case 69:
#line 410 "parser.yy"
    { yyval.number = yyvsp[-1].number; }
    break;

  case 70:
#line 411 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));
	  yyval.number = yyvsp[-2].number; 
	}
    break;

  case 71:
#line 415 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));
	  yyval.number = yyvsp[-1].number; 
	}
    break;

  case 72:
#line 419 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_PARAMETERS));
	  yyval.number = 0; 
	}
    break;

  case 73:
#line 423 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));
	  yyval.number = 0; 
	}
    break;

  case 74:
#line 435 "parser.yy"
    { yyval.number = 1; }
    break;

  case 75:
#line 436 "parser.yy"
    { yyval.number = yyvsp[-2].number+1; }
    break;

  case 76:
#line 437 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_PARAMETERS_));
	  yyval.number = yyvsp[-2].number;
	}
    break;

  case 77:
#line 444 "parser.yy"
    {
          CALL(yylsp[-3], yylsp[0], declParameter(yyvsp[-1].string, true, yyvsp[0].number));
          CALL(yylsp[-3], yylsp[0], declParameterEnd());
	}
    break;

  case 78:
#line 448 "parser.yy"
    {
          CALL(yylsp[-2], yylsp[0], declParameter(yyvsp[-1].string, false, yyvsp[0].number));
          CALL(yylsp[-2], yylsp[0], declParameterEnd());
	}
    break;

  case 79:
#line 452 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_PARAMID));
	}
    break;

  case 80:
#line 458 "parser.yy"
    { 
          CALL(yylsp[-2], yylsp[0], declVarEnd());
	}
    break;

  case 81:
#line 461 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
          CALL(yylsp[-3], yylsp[0], declVarEnd());
	}
    break;

  case 82:
#line 465 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_VARID));
	  CALL(yylsp[-2], yylsp[0], declVarEnd());
	}
    break;

  case 85:
#line 477 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], declVar(yyvsp[-2].string, yyvsp[-1].number, yyvsp[0].flag));
	}
    break;

  case 86:
#line 483 "parser.yy"
    { yyval.flag = false; }
    break;

  case 87:
#line 484 "parser.yy"
    { yyval.flag = true; }
    break;

  case 89:
#line 489 "parser.yy"
    {	
	  CALL(yylsp[-2], yylsp[0], declInitialiserList(yyvsp[-1].number));
	}
    break;

  case 90:
#line 495 "parser.yy"
    { yyval.number = 1; }
    break;

  case 91:
#line 496 "parser.yy"
    { yyval.number = yyvsp[-2].number+1; }
    break;

  case 92:
#line 500 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], declFieldInit(yyvsp[-2].string));
	}
    break;

  case 93:
#line 503 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_INITIAL));
	}
    break;

  case 94:
#line 506 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], declFieldInit(NULL));
	}
    break;

  case 95:
#line 512 "parser.yy"
    { yyval.number=0; }
    break;

  case 96:
#line 513 "parser.yy"
    { yyval.number=yyvsp[-3].number+1; }
    break;

  case 97:
#line 514 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RSQBRACE));
	  yyval.number=yyvsp[-4].number+1; 
	}
    break;

  case 98:
#line 518 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RSQBRACE));
	  yyval.number=yyvsp[-3].number+1; 
	}
    break;

  case 99:
#line 522 "parser.yy"
    {
	  CALL(yylsp[-1], yylsp[-1], exprNat(1));
	  REPORT_ERROR(last_loc, TypeException(PE_CONST_EXP));
	  yyval.number=yyvsp[-3].number+1; 
	}
    break;

  case 100:
#line 527 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], exprNat(1));
	  REPORT_ERROR(last_loc, TypeException(PE_CONST_EXP));
	  yyval.number=yyvsp[-2].number+1; 
	}
    break;

  case 101:
#line 535 "parser.yy"
    {
	  CALL(yylsp[-3], yylsp[0], declTypeDefEnd());
	}
    break;

  case 102:
#line 538 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-4], yylsp[0], declTypeDefEnd());
	}
    break;

  case 103:
#line 542 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_TYPEID));
	  CALL(yylsp[-3], yylsp[0], declTypeDefEnd());  
	}
    break;

  case 104:
#line 546 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_TYPE_DEF));
	  CALL(yylsp[-2], yylsp[0], declTypeDefEnd());  
	}
    break;

  case 105:
#line 558 "parser.yy"
    { yyval.number = 1; }
    break;

  case 106:
#line 559 "parser.yy"
    { yyval.number = yyvsp[-2].number+1; }
    break;

  case 107:
#line 560 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_TYPEID_));
	  yyval.number = yyvsp[-2].number+1; 
	}
    break;

  case 108:
#line 567 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], declTypeDef(yyvsp[-1].string, yyvsp[0].number));
	}
    break;

  case 109:
#line 573 "parser.yy"
    { 
	    CALL((yyvsp[-2].number == ParserBuilder::PREFIX_NONE ? yylsp[-1] : yylsp[-2]), yylsp[0],
		 typeName(yyvsp[-2].number, yyvsp[-1].string, yyvsp[0].number));
	}
    break;

  case 110:
#line 577 "parser.yy"
    { 
	    CALL((yyvsp[-4].number == ParserBuilder::PREFIX_NONE ? yylsp[-3] : yylsp[-4]), yylsp[0],
	       typeStruct(yyvsp[-4].number, yyvsp[-1].number));
	}
    break;

  case 111:
#line 581 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBER));
	  CALL((yyvsp[-4].number == ParserBuilder::PREFIX_NONE ? yylsp[-3] : yylsp[-4]), yylsp[0],
	       typeStruct(yyvsp[-4].number, 0));
	}
    break;

  case 112:
#line 586 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  CALL((yyvsp[-3].number == ParserBuilder::PREFIX_NONE ? yylsp[-2] : yylsp[-3]), yylsp[0],
	       typeStruct(yyvsp[-3].number, 0));
	}
    break;

  case 113:
#line 591 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	}
    break;

  case 114:
#line 597 "parser.yy"
    { strncpy(yyval.string, yyvsp[0].string, MAXLEN); }
    break;

  case 115:
#line 598 "parser.yy"
    { strncpy(yyval.string, yyvsp[0].string, MAXLEN); }
    break;

  case 116:
#line 602 "parser.yy"
    { yyval.number=yyvsp[0].number; }
    break;

  case 117:
#line 603 "parser.yy"
    { yyval.number=yyvsp[-1].number+yyvsp[0].number; }
    break;

  case 118:
#line 604 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBER));
	  yyval.number=yyvsp[-1].number; 
	}
    break;

  case 119:
#line 611 "parser.yy"
    {
	  yyval.number = yyvsp[-1].number; 
	  CALL(yylsp[-2], yylsp[0], structFieldEnd());
	}
    break;

  case 120:
#line 615 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));	  
	  yyval.number = yyvsp[-2].number; 
	  CALL(yylsp[-3], yylsp[0], structFieldEnd());
	}
    break;

  case 121:
#line 620 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBERID));	  
	}
    break;

  case 122:
#line 623 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBERID));	  
	}
    break;

  case 123:
#line 626 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBERTYPE));	  
	}
    break;

  case 124:
#line 632 "parser.yy"
    { yyval.number=1; }
    break;

  case 125:
#line 633 "parser.yy"
    { yyval.number=yyvsp[-2].number+1; }
    break;

  case 126:
#line 634 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBERID_));
	  yyval.number=yyvsp[-2].number+1; 
	}
    break;

  case 127:
#line 641 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], structField(yyvsp[-1].string, yyvsp[0].number));
	}
    break;

  case 128:
#line 647 "parser.yy"
    { yyval.number = ParserBuilder::PREFIX_NONE; }
    break;

  case 129:
#line 648 "parser.yy"
    { yyval.number = ParserBuilder::PREFIX_URGENT; }
    break;

  case 130:
#line 649 "parser.yy"
    { yyval.number = ParserBuilder::PREFIX_BROADCAST; }
    break;

  case 131:
#line 650 "parser.yy"
    { yyval.number = ParserBuilder::PREFIX_URGENT_BROADCAST; }
    break;

  case 132:
#line 651 "parser.yy"
    { yyval.number = ParserBuilder::PREFIX_CONST; }
    break;

  case 133:
#line 655 "parser.yy"
    { yyval.number = 0; }
    break;

  case 134:
#line 656 "parser.yy"
    { yyval.number = 2; }
    break;

  case 135:
#line 657 "parser.yy"
    {
	    yyval.number = 0;
        }
    break;

  case 136:
#line 667 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[0], procBegin(yyvsp[-2].string, yyvsp[-1].number));
	}
    break;

  case 137:
#line 670 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], procEnd());
	}
    break;

  case 138:
#line 673 "parser.yy"
    {
	  utap_error(TypeException(PE_LPAREN), 
		     yylsp[0].first_line, yylsp[0].first_column, 
		     yylsp[0].last_line, yylsp[0].last_column);
	  CALL(yylsp[-2], yylsp[0], procBegin(yyvsp[-1].string, 0));
	}
    break;

  case 139:
#line 678 "parser.yy"
    {
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;

  case 146:
#line 696 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 147:
#line 699 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 148:
#line 702 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATE_DECL));
	}
    break;

  case 149:
#line 705 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATE_DECL));
	}
    break;

  case 150:
#line 708 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATE));
	}
    break;

  case 153:
#line 716 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATE_DECL_));
	}
    break;

  case 154:
#line 722 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], procState(yyvsp[0].string, false));
	}
    break;

  case 155:
#line 725 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[0], procState(yyvsp[-3].string, true));
	}
    break;

  case 156:
#line 728 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	  CALL(yylsp[-4], yylsp[0], procState(yyvsp[-4].string, true));
	}
    break;

  case 157:
#line 732 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	  CALL(yylsp[-3], yylsp[0], procState(yyvsp[-3].string, true));
	}
    break;

  case 158:
#line 736 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_INV));
	  CALL(yylsp[-3], yylsp[0], procState(yyvsp[-3].string, false));
	}
    break;

  case 159:
#line 740 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_INV));
	  CALL(yylsp[-2], yylsp[0], procState(yyvsp[-2].string, false));
	}
    break;

  case 160:
#line 747 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], procStateInit(yyvsp[-1].string));
	}
    break;

  case 161:
#line 750 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-3], yylsp[0], procStateInit(yyvsp[-2].string));
	}
    break;

  case 162:
#line 754 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-2], yylsp[0], procStateInit(yyvsp[-1].string));
	}
    break;

  case 163:
#line 758 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;

  case 164:
#line 761 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_INIT));
	}
    break;

  case 167:
#line 769 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 168:
#line 772 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 169:
#line 775 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS_DECL));
	}
    break;

  case 170:
#line 778 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS));
	}
    break;

  case 173:
#line 786 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS_DECL_));
	}
    break;

  case 174:
#line 792 "parser.yy"
    { 
	  strcpy(rootTransId, yyvsp[-7].string); 
	  CALL(yylsp[-7], yylsp[0], procTransition(yyvsp[-7].string, yyvsp[-5].string));
	}
    break;

  case 175:
#line 796 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  strcpy(rootTransId, yyvsp[-8].string); 
	  CALL(yylsp[-8], yylsp[0], procTransition(yyvsp[-8].string, yyvsp[-6].string));
	}
    break;

  case 176:
#line 801 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	}
    break;

  case 177:
#line 804 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;

  case 178:
#line 807 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_ARROW));
	}
    break;

  case 179:
#line 813 "parser.yy"
    { 
	  CALL(yylsp[-6], yylsp[0], procTransition(rootTransId, yyvsp[-5].string));
	}
    break;

  case 180:
#line 816 "parser.yy"
    { 
	  REPORT_ERROR(yylloc, TypeException(PE_RBRACE));
	  CALL(yylsp[-7], yylsp[0], procTransition(rootTransId, yyvsp[-6].string));
	}
    break;

  case 181:
#line 820 "parser.yy"
    { 
	  REPORT_ERROR(yylloc, TypeException(PE_LBRACE));
	}
    break;

  case 182:
#line 823 "parser.yy"
    { 
	  REPORT_ERROR(yylloc, TypeException(PE_STATEID));
	}
    break;

  case 185:
#line 832 "parser.yy"
    {
	  CALL(yylsp[-1], yylsp[-1], procGuard());
        }
    break;

  case 186:
#line 835 "parser.yy"
    {
	  REPORT_ERROR(yylloc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-2], yylsp[-1], procGuard());
	}
    break;

  case 187:
#line 839 "parser.yy"
    {
	  REPORT_ERROR(yylloc, TypeException(PE_GUARD_EXP));
	}
    break;

  case 190:
#line 847 "parser.yy"
    {
	  REPORT_ERROR(yylloc, TypeException(PE_SEMICOLON));
	}
    break;

  case 191:
#line 850 "parser.yy"
    {
	  REPORT_ERROR(yylloc, TypeException(PE_SEMICOLON));
	}
    break;

  case 192:
#line 853 "parser.yy"
    {
	  REPORT_ERROR(yylloc, TypeException(PE_SYNC_EXP));
	}
    break;

  case 193:
#line 859 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], procSync(SYNC_BANG));
	}
    break;

  case 194:
#line 862 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_BANG));
	  CALL(yylsp[-2], yylsp[-1], procSync(SYNC_QUE));
	}
    break;

  case 195:
#line 866 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], procSync(SYNC_QUE));
	}
    break;

  case 196:
#line 869 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_QUE));
	  CALL(yylsp[-2], yylsp[-1], procSync(SYNC_QUE));
	}
    break;

  case 197:
#line 873 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_BANGQUE));
	  CALL(yylsp[-1], yylsp[0], procSync(SYNC_QUE));
	}
    break;

  case 199:
#line 881 "parser.yy"
    {
	  CALL(yylsp[-1], yylsp[-1], procUpdate());	  
	}
    break;

  case 200:
#line 884 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_ASSIGN_EXP));
	}
    break;

  case 206:
#line 898 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 207:
#line 901 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 208:
#line 904 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;

  case 209:
#line 907 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;

  case 210:
#line 913 "parser.yy"
    {}
    break;

  case 211:
#line 914 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 212:
#line 917 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 213:
#line 920 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;

  case 214:
#line 923 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;

  case 215:
#line 929 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], procStateCommit(yyvsp[0].string));
	}
    break;

  case 216:
#line 932 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], procStateCommit(yyvsp[0].string));
	}
    break;

  case 217:
#line 935 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID_));
	}
    break;

  case 218:
#line 941 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], procStateUrgent(yyvsp[0].string));
	}
    break;

  case 219:
#line 944 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], procStateUrgent(yyvsp[0].string));
	}
    break;

  case 220:
#line 947 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID_));
	}
    break;

  case 221:
#line 958 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], blockBegin());
	}
    break;

  case 222:
#line 961 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[-1], blockEnd());
	}
    break;

  case 230:
#line 980 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], emptyStatement());
	}
    break;

  case 231:
#line 983 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], exprStatement());
	}
    break;

  case 232:
#line 986 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], forBegin());
	}
    break;

  case 233:
#line 989 "parser.yy"
    { 
	    CALL(yylsp[-7], yylsp[-1], forEnd());
	  }
    break;

  case 235:
#line 993 "parser.yy"
    {
	    CALL(yylsp[-1], yylsp[0], whileBegin());
	}
    break;

  case 236:
#line 996 "parser.yy"
    { 
	    CALL(yylsp[-3], yylsp[-2], whileEnd());
	  }
    break;

  case 238:
#line 1000 "parser.yy"
    { 
	    CALL(yylsp[0], yylsp[0], doWhileBegin());
	}
    break;

  case 239:
#line 1003 "parser.yy"
    { 
	    CALL(yylsp[-6], yylsp[-1], doWhileEnd());
	  }
    break;

  case 240:
#line 1006 "parser.yy"
    { 
	    CALL(yylsp[-1], yylsp[0], ifBegin());
	}
    break;

  case 242:
#line 1010 "parser.yy"
    { 
	    CALL(yylsp[-1], yylsp[0], breakStatement());
	  }
    break;

  case 243:
#line 1013 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], continueStatement());
	}
    break;

  case 244:
#line 1016 "parser.yy"
    { 
	    CALL(yylsp[-3], yylsp[0], switchBegin());
	}
    break;

  case 245:
#line 1019 "parser.yy"
    { 
	       CALL(yylsp[-3], yylsp[-1], switchEnd());
	   }
    break;

  case 246:
#line 1022 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], returnStatement(true));
	}
    break;

  case 247:
#line 1025 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], returnStatement(false));
	}
    break;

  case 248:
#line 1031 "parser.yy"
    { 
	  CALL(position_t(), position_t(), ifEnd(false));
	}
    break;

  case 249:
#line 1034 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], ifElse());
	}
    break;

  case 250:
#line 1037 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[-1], ifEnd(true));
	  }
    break;

  case 251:
#line 1040 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], ifElse());
	}
    break;

  case 252:
#line 1043 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-1], yylsp[-1], ifEnd(true));
	  }
    break;

  case 255:
#line 1055 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], caseBegin());
	}
    break;

  case 256:
#line 1058 "parser.yy"
    { 
	    CALL(yylsp[-1], yylsp[-1], caseEnd());
	  }
    break;

  case 257:
#line 1061 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], caseBegin());
	}
    break;

  case 258:
#line 1064 "parser.yy"
    {
	    REPORT_ERROR(last_loc, TypeException(PE_EXPR)); 
	    CALL(yylsp[-1], yylsp[-1], caseEnd());
	  }
    break;

  case 259:
#line 1068 "parser.yy"
    { 
	    CALL(yylsp[-1], yylsp[0], defaultBegin());
	}
    break;

  case 260:
#line 1071 "parser.yy"
    { 
	    CALL(yylsp[-1], yylsp[-1], defaultEnd());
	  }
    break;

  case 261:
#line 1074 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_COLON)); 
	  CALL(yylsp[-2], yylsp[0], defaultBegin());
	}
    break;

  case 262:
#line 1078 "parser.yy"
    { 
	    CALL(yylsp[-1], yylsp[-1], defaultEnd());
	  }
    break;

  case 266:
#line 1090 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprComma());
	}
    break;

  case 267:
#line 1095 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], exprFalse());
	}
    break;

  case 268:
#line 1098 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], exprTrue());
	}
    break;

  case 269:
#line 1101 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], exprNat(yyvsp[0].number));
	}
    break;

  case 270:
#line 1104 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], exprId(yyvsp[0].string));
	}
    break;

  case 271:
#line 1107 "parser.yy"
    {
	    CALL(yylsp[-1], yylsp[0], exprCallBegin(yyvsp[-1].string));	    
	  }
    break;

  case 272:
#line 1109 "parser.yy"
    { 
	    CALL(yylsp[-4], yylsp[0], exprCallEnd(yyvsp[-1].number));
	}
    break;

  case 273:
#line 1112 "parser.yy"
    {
	    CALL(yylsp[-1], yylsp[0], exprCallBegin(yyvsp[-1].string));
	  }
    break;

  case 274:
#line 1114 "parser.yy"
    {   
	    REPORT_ERROR(last_loc, TypeException(PE_ARGLIST));
	    CALL(yylsp[-4], yylsp[0], exprCallEnd(0));
	}
    break;

  case 275:
#line 1118 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[0], exprArray());
	}
    break;

  case 276:
#line 1121 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-3], yylsp[0], exprFalse());
	}
    break;

  case 278:
#line 1126 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprFalse());
	}
    break;

  case 279:
#line 1130 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], exprPostIncrement());
	}
    break;

  case 280:
#line 1133 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], exprPreIncrement());
	}
    break;

  case 281:
#line 1136 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], exprPostDecrement());
	}
    break;

  case 282:
#line 1139 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], exprPreDecrement());
	}
    break;

  case 283:
#line 1142 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], exprUnary(yyvsp[-1].kind));
	}
    break;

  case 284:
#line 1145 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(LT));
	}
    break;

  case 285:
#line 1148 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(LE));
	}
    break;

  case 286:
#line 1151 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(EQ));
	}
    break;

  case 287:
#line 1154 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(NEQ));
	}
    break;

  case 288:
#line 1157 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(GT));
	}
    break;

  case 289:
#line 1160 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(GE));
	}
    break;

  case 290:
#line 1163 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(PLUS));
	}
    break;

  case 291:
#line 1166 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(MINUS));
	}
    break;

  case 292:
#line 1169 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(MULT));
	}
    break;

  case 293:
#line 1172 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(DIV));
	}
    break;

  case 294:
#line 1175 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(MOD));
	}
    break;

  case 295:
#line 1178 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_AND));
	}
    break;

  case 296:
#line 1181 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_OR));
	}
    break;

  case 297:
#line 1184 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_XOR));
	}
    break;

  case 298:
#line 1187 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_LSHIFT));
	}
    break;

  case 299:
#line 1190 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_RSHIFT));
	}
    break;

  case 300:
#line 1193 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(AND));
	}
    break;

  case 301:
#line 1196 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(OR));
	}
    break;

  case 302:
#line 1199 "parser.yy"
    { 
	  CALL(yylsp[-4], yylsp[0], exprInlineIf());
	}
    break;

  case 303:
#line 1202 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprDot(yyvsp[0].string));
	}
    break;

  case 304:
#line 1205 "parser.yy"
    {
	  CALL(yylsp[0], yylsp[0], exprDeadlock());
	}
    break;

  case 305:
#line 1208 "parser.yy"
    {  
	  CALL(yylsp[-1], yylsp[-1], exprUnary(NOT));
	}
    break;

  case 306:
#line 1210 "parser.yy"
    {
	  CALL(yylsp[-1], yylsp[-1], exprBinary(OR));
	}
    break;

  case 307:
#line 1213 "parser.yy"
    {
	  CALL(yylsp[-2], yylsp[0], exprBinary(AND));
        }
    break;

  case 308:
#line 1216 "parser.yy"
    {
	  CALL(yylsp[-2], yylsp[0], exprBinary(OR));
        }
    break;

  case 309:
#line 1219 "parser.yy"
    {
	  CALL(yylsp[-1], yylsp[0], exprUnary(NOT));
        }
    break;

  case 310:
#line 1222 "parser.yy"
    {
	    CALL(yylsp[-2], yylsp[0], exprBinary(MIN));
        }
    break;

  case 311:
#line 1225 "parser.yy"
    {
	    CALL(yylsp[-2], yylsp[0], exprBinary(MAX));
        }
    break;

  case 313:
#line 1232 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprAssignment(yyvsp[-1].kind));
	}
    break;

  case 314:
#line 1238 "parser.yy"
    { yyval.kind = ASSIGN; }
    break;

  case 315:
#line 1239 "parser.yy"
    { yyval.kind = ASSPLUS; }
    break;

  case 316:
#line 1240 "parser.yy"
    { yyval.kind = ASSMINUS; }
    break;

  case 317:
#line 1241 "parser.yy"
    { yyval.kind = ASSDIV; }
    break;

  case 318:
#line 1242 "parser.yy"
    { yyval.kind = ASSMOD; }
    break;

  case 319:
#line 1243 "parser.yy"
    { yyval.kind = ASSMULT; }
    break;

  case 320:
#line 1244 "parser.yy"
    { yyval.kind = ASSAND; }
    break;

  case 321:
#line 1245 "parser.yy"
    { yyval.kind = ASSOR; }
    break;

  case 322:
#line 1246 "parser.yy"
    { yyval.kind = ASSXOR; }
    break;

  case 323:
#line 1247 "parser.yy"
    { yyval.kind = ASSLSHIFT; }
    break;

  case 324:
#line 1248 "parser.yy"
    { yyval.kind = ASSRSHIFT; }
    break;

  case 325:
#line 1253 "parser.yy"
    { yyval.kind = MINUS; }
    break;

  case 326:
#line 1254 "parser.yy"
    { yyval.kind = PLUS; }
    break;

  case 327:
#line 1255 "parser.yy"
    { yyval.kind = NOT; }
    break;

  case 328:
#line 1260 "parser.yy"
    { yyval.number=0; }
    break;

  case 329:
#line 1261 "parser.yy"
    { 
	    yyval.number=1; 
	    CALL(yylsp[0], yylsp[0], exprArg(0));
	}
    break;

  case 330:
#line 1265 "parser.yy"
    { 
	    yyval.number=yyvsp[-2].number+1; 
	    CALL(yylsp[0], yylsp[0], exprArg(yyvsp[-2].number));
	}
    break;

  case 331:
#line 1269 "parser.yy"
    { 
	  yyval.number=yyvsp[-2].number+1; 
	  REPORT_ERROR(last_loc, TypeException(PE_ARGLIST_));
	  CALL(yylsp[0], yylsp[0], exprArg(yyvsp[-2].number));
	}
    break;

  case 337:
#line 1292 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], typeName(ParserBuilder::PREFIX_CONST, "int", 0));
	}
    break;

  case 338:
#line 1294 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[-1], declVarEnd());
	}
    break;

  case 340:
#line 1300 "parser.yy"
    { yyval.number=1; }
    break;

  case 341:
#line 1301 "parser.yy"
    { yyval.number=yyvsp[-2].number+1; }
    break;

  case 342:
#line 1305 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], declVar(yyvsp[-2].string, yyvsp[-1].number, true));
	}
    break;

  case 343:
#line 1314 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[0], procBegin(yyvsp[-2].string, yyvsp[-1].number));
	}
    break;

  case 344:
#line 1317 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;

  case 345:
#line 1320 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	  CALL(yylsp[-4], yylsp[0], procBegin(yyvsp[-3].string, yyvsp[-2].number));
	}
    break;

  case 346:
#line 1324 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;

  case 347:
#line 1327 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACES));
	  CALL(yylsp[-3], yylsp[0], procBegin(yyvsp[-2].string, 0));
	}
    break;

  case 348:
#line 1331 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;

  case 349:
#line 1334 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_PROCID));
	  CALL(yylsp[-2], yylsp[0], procBegin("_", 0));
	}
    break;

  case 350:
#line 1338 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;

  case 351:
#line 1341 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], procBegin(yyvsp[-1].string, 0));
	}
    break;

  case 352:
#line 1344 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;

  case 353:
#line 1350 "parser.yy"
    { yyval.number = 0; }
    break;

  case 354:
#line 1351 "parser.yy"
    { yyval.number = yyvsp[-1].number; }
    break;

  case 355:
#line 1352 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_PARAMETERS));	  
	  yyval.number = 0; 
	}
    break;

  case 356:
#line 1359 "parser.yy"
    { 
	  yyval.number = yyvsp[0].number; 
	  CALL(yylsp[0], yylsp[0], declParameterEnd());
	}
    break;

  case 357:
#line 1363 "parser.yy"
    {
	  yyval.number = yyvsp[0].number;
	  CALL(yylsp[0], yylsp[0], declParameterEnd());
        }
    break;

  case 358:
#line 1367 "parser.yy"
    { 
	  yyval.number = yyvsp[-2].number + yyvsp[0].number;
	  CALL(yylsp[-2], yylsp[0], declParameterEnd());
	}
    break;

  case 359:
#line 1371 "parser.yy"
    { 
	  yyval.number = yyvsp[-2].number + yyvsp[0].number;
	  CALL(yylsp[-2], yylsp[0], declParameterEnd());
	}
    break;

  case 360:
#line 1375 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_PARAM_DECL_));
          yyval.number = yyvsp[-1].number; 
	}
    break;

  case 361:
#line 1382 "parser.yy"
    {
          CALL(yylsp[-2], yylsp[0], declParameter(yyvsp[-1].string, yyvsp[0].number == 0, yyvsp[0].number));
	  yyval.number = 1;
	}
    break;

  case 362:
#line 1386 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[0], declParameter(yyvsp[-1].string, yyvsp[0].number == 0, yyvsp[0].number));
	  yyval.number = yyvsp[-3].number + 1;
	}
    break;

  case 363:
#line 1393 "parser.yy"
    {
	  CALL(yylsp[-2], yylsp[-2], typeName(ParserBuilder::PREFIX_CONST, "int", false));
	  CALL(yylsp[-1], yylsp[0], declParameter(yyvsp[-1].string, false, yyvsp[0].number));
	  yyval.number = 1;
	}
    break;

  case 364:
#line 1398 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[0], declParameter(yyvsp[-1].string, false, yyvsp[0].number));
	  yyval.number = yyvsp[-3].number + 1;
	}
    break;

  case 369:
#line 1415 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 370:
#line 1418 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 371:
#line 1421 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATE_DECL));
	}
    break;

  case 372:
#line 1424 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATE_DECL));
	}
    break;

  case 373:
#line 1427 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATE));
	}
    break;

  case 376:
#line 1435 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_LOC_DECL));
	}
    break;

  case 377:
#line 1441 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], exprTrue(); ch->procState(yyvsp[0].string, false));
	}
    break;

  case 378:
#line 1444 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[0], procState(yyvsp[-3].string, true));
	}
    break;

  case 380:
#line 1451 "parser.yy"
    {	  
	  REPORT_ERROR(last_loc, TypeException(PE_INV));
	}
    break;

  case 381:
#line 1454 "parser.yy"
    {	  
	  REPORT_ERROR(last_loc, TypeException(PE_INV));
	  CALL(yylsp[0], yylsp[0], exprTrue());
	}
    break;

  case 382:
#line 1458 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(AND));
	}
    break;

  case 385:
#line 1466 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 386:
#line 1469 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 387:
#line 1472 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS_DECL));
	}
    break;

  case 388:
#line 1475 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS_DECL));
	}
    break;

  case 389:
#line 1478 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS));
	}
    break;

  case 392:
#line 1486 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_ALT_TRANS));	  
	}
    break;

  case 393:
#line 1492 "parser.yy"
    { 
	  strcpy(rootTransId, yyvsp[-7].string);
	  CALL(yylsp[-7], yylsp[0], procTransition(yyvsp[-7].string, yyvsp[-5].string));
	}
    break;

  case 394:
#line 1496 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  strcpy(rootTransId, yyvsp[-8].string);
	  CALL(yylsp[-8], yylsp[0], procTransition(yyvsp[-8].string, yyvsp[-6].string));
	}
    break;

  case 395:
#line 1501 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  strcpy(rootTransId, yyvsp[-7].string); 
	  CALL(yylsp[-7], yylsp[0], procTransition(yyvsp[-7].string, yyvsp[-5].string));
	}
    break;

  case 396:
#line 1506 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	  strcpy(rootTransId, yyvsp[-8].string); 
	  CALL(yylsp[-8], yylsp[0], procTransition(yyvsp[-8].string, yyvsp[-6].string));
	}
    break;

  case 397:
#line 1511 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_ARROW));
	  strcpy(rootTransId, yyvsp[-8].string); 
	  CALL(yylsp[-8], yylsp[0], procTransition(yyvsp[-8].string, yyvsp[-5].string));
	}
    break;

  case 398:
#line 1520 "parser.yy"
    { 
	  CALL(yylsp[-6], yylsp[0], procTransition(rootTransId, yyvsp[-5].string));
	}
    break;

  case 399:
#line 1523 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  CALL(yylsp[-6], yylsp[0], procTransition(rootTransId, yyvsp[-5].string));
	}
    break;

  case 400:
#line 1527 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  CALL(yylsp[-7], yylsp[0], procTransition(rootTransId, yyvsp[-6].string));
	}
    break;

  case 401:
#line 1531 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	  CALL(yylsp[-7], yylsp[0], procTransition(rootTransId, yyvsp[-6].string));
	}
    break;

  case 402:
#line 1535 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	  CALL(yylsp[-7], yylsp[0], procTransition(rootTransId, yyvsp[-5].string));
	}
    break;

  case 403:
#line 1539 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	  CALL(yylsp[-6], yylsp[0], procTransition(rootTransId, "_"));
	}
    break;

  case 406:
#line 1548 "parser.yy"
    {
	  CALL(yylsp[-1], yylsp[-1], procGuard());
	}
    break;

  case 407:
#line 1551 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-2], yylsp[-1], procGuard());
	}
    break;

  case 408:
#line 1555 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-1], yylsp[0], procGuard());
	}
    break;

  case 409:
#line 1559 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_GUARD_EXP));
	}
    break;

  case 411:
#line 1566 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(AND));
	}
    break;

  case 412:
#line 1569 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_GUARD_EXP_));
	  CALL(yylsp[-2], yylsp[0], exprBinary(AND));
	}
    break;

  case 417:
#line 1584 "parser.yy"
    {
		ch->quit();	
	}
    break;

  case 418:
#line 1587 "parser.yy"
    {
		ch->property(yyvsp[-1].kind, yylsp[-1].first_line);
	}
    break;

  case 419:
#line 1590 "parser.yy"
    {
		ch->property(LEADSTO, yylsp[-2].first_line);
	}
    break;

  case 420:
#line 1595 "parser.yy"
    { yyval.kind = EF; }
    break;

  case 421:
#line 1596 "parser.yy"
    { yyval.kind = EG; }
    break;

  case 422:
#line 1597 "parser.yy"
    { yyval.kind = AF; }
    break;

  case 423:
#line 1598 "parser.yy"
    { yyval.kind = AG; }
    break;


    }

/* Line 999 of yacc.c.  */
#line 4818 "parser.tab.c"

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
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("syntax error, unexpected ") + 1;
	  yysize += yystrlen (yytname[yytype]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
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

      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        {
	  /* Pop the error token.  */
          YYPOPSTACK;
	  /* Pop the rest of the stack.  */
	  while (yyss < yyssp)
	    {
	      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
	      yydestruct (yystos[*yyssp], yyvsp, yylsp);
	      YYPOPSTACK;
	    }
	  YYABORT;
        }

      YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
      yydestruct (yytoken, &yylval, &yylloc);
      yychar = YYEMPTY;
      *++yylerrsp = yylloc;
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
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
      yyvsp--;
      yystate = *--yyssp;
      yylsp--;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;
  YYLLOC_DEFAULT (yyloc, yylsp, (yylerrsp - yylsp));
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


#line 1600 "parser.yy"


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
    syntax = (syntax_t)(newxta ? SYNTAX_NEW : SYNTAX_OLD);
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


