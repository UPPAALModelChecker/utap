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
     T_FORALL = 289,
     T_LT = 290,
     T_LEQ = 291,
     T_EQ = 292,
     T_NEQ = 293,
     T_GEQ = 294,
     T_GT = 295,
     T_FOR = 296,
     T_WHILE = 297,
     T_DO = 298,
     T_BREAK = 299,
     T_CONTINUE = 300,
     T_SWITCH = 301,
     T_IF = 302,
     T_ELSE = 303,
     T_CASE = 304,
     T_DEFAULT = 305,
     T_RETURN = 306,
     T_CHAN_PRIORITY = 307,
     T_PROC_PRIORITY = 308,
     T_TYPEDEF = 309,
     T_STRUCT = 310,
     T_CONST = 311,
     T_OLDCONST = 312,
     T_URGENT = 313,
     T_BROADCAST = 314,
     T_TRUE = 315,
     T_FALSE = 316,
     T_META = 317,
     T_SYSTEM = 318,
     T_PROCESS = 319,
     T_STATE = 320,
     T_COMMIT = 321,
     T_INIT = 322,
     T_TRANS = 323,
     T_SELECT = 324,
     T_GUARD = 325,
     T_SYNC = 326,
     T_ASSIGN = 327,
     T_BEFORE = 328,
     T_AFTER = 329,
     T_PROGRESS = 330,
     T_ARROW = 331,
     T_UNCONTROL_ARROW = 332,
     T_WINNING = 333,
     T_LOSING = 334,
     T_DEADLOCK = 335,
     T_EF = 336,
     T_EG = 337,
     T_AF = 338,
     T_AG = 339,
     T_LEADSTO = 340,
     T_QUIT = 341,
     T_ERROR = 342,
     T_ID = 343,
     T_TYPENAME = 344,
     T_NAT = 345,
     T_NEW = 346,
     T_NEW_DECLARATION = 347,
     T_NEW_LOCAL_DECL = 348,
     T_NEW_INST = 349,
     T_NEW_SYSTEM = 350,
     T_NEW_PARAMETERS = 351,
     T_NEW_INVARIANT = 352,
     T_NEW_GUARD = 353,
     T_NEW_SYNC = 354,
     T_NEW_ASSIGN = 355,
     T_NEW_SELECT = 356,
     T_OLD = 357,
     T_OLD_DECLARATION = 358,
     T_OLD_LOCAL_DECL = 359,
     T_OLD_INST = 360,
     T_OLD_PARAMETERS = 361,
     T_OLD_INVARIANT = 362,
     T_OLD_GUARD = 363,
     T_OLD_ASSIGN = 364,
     T_PROPERTY = 365,
     T_EXPRESSION = 366,
     UOPERATOR = 367
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
#define T_FORALL 289
#define T_LT 290
#define T_LEQ 291
#define T_EQ 292
#define T_NEQ 293
#define T_GEQ 294
#define T_GT 295
#define T_FOR 296
#define T_WHILE 297
#define T_DO 298
#define T_BREAK 299
#define T_CONTINUE 300
#define T_SWITCH 301
#define T_IF 302
#define T_ELSE 303
#define T_CASE 304
#define T_DEFAULT 305
#define T_RETURN 306
#define T_CHAN_PRIORITY 307
#define T_PROC_PRIORITY 308
#define T_TYPEDEF 309
#define T_STRUCT 310
#define T_CONST 311
#define T_OLDCONST 312
#define T_URGENT 313
#define T_BROADCAST 314
#define T_TRUE 315
#define T_FALSE 316
#define T_META 317
#define T_SYSTEM 318
#define T_PROCESS 319
#define T_STATE 320
#define T_COMMIT 321
#define T_INIT 322
#define T_TRANS 323
#define T_SELECT 324
#define T_GUARD 325
#define T_SYNC 326
#define T_ASSIGN 327
#define T_BEFORE 328
#define T_AFTER 329
#define T_PROGRESS 330
#define T_ARROW 331
#define T_UNCONTROL_ARROW 332
#define T_WINNING 333
#define T_LOSING 334
#define T_DEADLOCK 335
#define T_EF 336
#define T_EG 337
#define T_AF 338
#define T_AG 339
#define T_LEADSTO 340
#define T_QUIT 341
#define T_ERROR 342
#define T_ID 343
#define T_TYPENAME 344
#define T_NAT 345
#define T_NEW 346
#define T_NEW_DECLARATION 347
#define T_NEW_LOCAL_DECL 348
#define T_NEW_INST 349
#define T_NEW_SYSTEM 350
#define T_NEW_PARAMETERS 351
#define T_NEW_INVARIANT 352
#define T_NEW_GUARD 353
#define T_NEW_SYNC 354
#define T_NEW_ASSIGN 355
#define T_NEW_SELECT 356
#define T_OLD 357
#define T_OLD_DECLARATION 358
#define T_OLD_LOCAL_DECL 359
#define T_OLD_INST 360
#define T_OLD_PARAMETERS 361
#define T_OLD_INVARIANT 362
#define T_OLD_GUARD 363
#define T_OLD_ASSIGN 364
#define T_PROPERTY 365
#define T_EXPRESSION 366
#define UOPERATOR 367




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
#line 234 "parser.yy"
typedef union YYSTYPE {
    bool flag;
    int number;
    kind_t kind;
    char string[MAXLEN];
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 412 "parser.tab.c"
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
#line 436 "parser.tab.c"

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
#define YYFINAL  83
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3271

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  127
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  137
/* YYNRULES -- Number of rules. */
#define YYNRULES  373
/* YYNRULES -- Number of states. */
#define YYNSTATES  738

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   367

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     126,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   114,   121,
     116,   117,     2,     2,   123,     2,   120,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   113,   122,
       2,     2,     2,   112,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   118,     2,   119,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   124,     2,   125,     2,     2,     2,     2,
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
     105,   106,   107,   108,   109,   110,   111,   115
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
     140,   144,   148,   153,   157,   159,   163,   164,   169,   170,
     176,   180,   181,   184,   187,   190,   193,   196,   199,   202,
     207,   212,   213,   222,   225,   229,   233,   235,   239,   244,
     248,   252,   254,   258,   262,   263,   266,   268,   272,   274,
     278,   282,   284,   285,   290,   295,   300,   304,   306,   310,
     313,   317,   323,   329,   331,   333,   335,   338,   342,   344,
     348,   351,   352,   354,   356,   359,   361,   363,   364,   368,
     374,   378,   379,   384,   388,   389,   398,   399,   406,   412,
     413,   416,   419,   422,   426,   431,   435,   438,   440,   444,
     446,   451,   456,   460,   463,   464,   468,   472,   474,   478,
     479,   490,   491,   502,   503,   513,   514,   524,   526,   527,
     531,   535,   541,   542,   546,   551,   555,   556,   560,   565,
     569,   572,   576,   579,   583,   584,   588,   592,   593,   596,
     599,   602,   605,   609,   614,   618,   622,   627,   631,   635,
     640,   644,   648,   653,   657,   659,   663,   665,   669,   671,
     675,   677,   681,   682,   688,   689,   692,   695,   696,   699,
     703,   705,   707,   710,   711,   722,   723,   732,   738,   739,
     746,   752,   753,   762,   763,   771,   774,   777,   778,   787,
     791,   794,   795,   796,   800,   802,   805,   806,   812,   813,
     819,   820,   825,   826,   832,   834,   838,   840,   842,   844,
     846,   847,   853,   854,   860,   865,   870,   874,   878,   881,
     884,   887,   890,   893,   897,   901,   905,   909,   913,   917,
     921,   925,   929,   933,   937,   941,   945,   949,   953,   957,
     961,   965,   971,   975,   978,   980,   981,   986,   990,   994,
     997,  1001,  1005,  1006,  1015,  1017,  1021,  1023,  1025,  1027,
    1029,  1031,  1033,  1035,  1037,  1039,  1041,  1043,  1045,  1047,
    1049,  1050,  1052,  1056,  1060,  1061,  1064,  1067,  1069,  1070,
    1075,  1079,  1081,  1085,  1089,  1090,  1098,  1099,  1108,  1109,
    1117,  1118,  1125,  1126,  1133,  1136,  1140,  1144,  1146,  1148,
    1152,  1156,  1160,  1165,  1169,  1174,  1180,  1181,  1184,  1188,
    1191,  1193,  1197,  1199,  1204,  1206,  1210,  1214,  1215,  1219,
    1224,  1228,  1230,  1234,  1235,  1245,  1246,  1255,  1257,  1258,
    1262,  1267,  1269,  1273,  1276,  1277,  1281,  1282,  1284,  1287,
    1291,  1293,  1295,  1297
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short int yyrhs[] =
{
     128,     0,    -1,    91,   129,    -1,    92,   140,    -1,    93,
     173,    -1,    94,   130,    -1,    95,   132,    -1,    96,   146,
      -1,    97,   221,    -1,   101,   187,    -1,    98,   221,    -1,
      99,   190,    -1,   100,   220,    -1,   102,   230,    -1,   103,
     231,    -1,   104,   247,    -1,   105,   130,    -1,   106,   243,
      -1,   107,   251,    -1,   108,   259,    -1,   109,   220,    -1,
     110,   260,    -1,   111,   221,    -1,   140,   130,   132,    -1,
      -1,    -1,   130,    88,     3,    88,   116,   131,   229,   117,
     122,    -1,   130,    88,     3,    88,   116,     1,   117,   122,
      -1,   130,    88,     3,    88,   116,     1,   122,    -1,   130,
      88,     3,    88,     1,   122,    -1,   130,    88,     1,   122,
      -1,   133,   134,   136,   138,    -1,    -1,    52,   135,   122,
      -1,    -1,    53,   135,   122,    -1,    88,    -1,   135,    37,
      88,    -1,   135,    35,    88,    -1,   135,    37,     1,    -1,
     135,    35,     1,    -1,    63,   137,   122,    -1,    63,   137,
       1,   122,    -1,    63,     1,   122,    -1,    88,    -1,   137,
     123,    88,    -1,    -1,    75,   124,   139,   125,    -1,    -1,
     139,   221,   113,   221,   122,    -1,   139,   221,   122,    -1,
      -1,   140,   143,    -1,   140,   148,    -1,   140,   156,    -1,
     140,   169,    -1,   140,   141,    -1,   140,   142,    -1,     1,
     122,    -1,    73,   124,   220,   125,    -1,    74,   124,   220,
     125,    -1,    -1,   159,   160,   145,   124,   144,   203,   204,
     125,    -1,   116,   117,    -1,   116,   146,   117,    -1,   116,
       1,   117,    -1,   147,    -1,   146,   123,   147,    -1,   159,
     114,    88,   155,    -1,   159,    88,   155,    -1,   159,   149,
     122,    -1,   150,    -1,   149,   123,   150,    -1,   160,   155,
     151,    -1,    -1,     3,   152,    -1,   221,    -1,   124,   153,
     125,    -1,   154,    -1,   153,   123,   154,    -1,   160,   113,
     152,    -1,   152,    -1,    -1,   155,   118,   221,   119,    -1,
     155,   118,     1,   119,    -1,    54,   159,   157,   122,    -1,
      54,     1,   122,    -1,   158,    -1,   157,   123,   158,    -1,
     160,   155,    -1,   165,    89,   166,    -1,   165,    55,   124,
     161,   125,    -1,   165,    55,   124,     1,   125,    -1,    88,
      -1,    89,    -1,   162,    -1,   161,   162,    -1,   159,   163,
     122,    -1,   164,    -1,   163,   123,   164,    -1,   160,   155,
      -1,    -1,    58,    -1,    59,    -1,    58,    59,    -1,    56,
      -1,    62,    -1,    -1,   118,   221,   119,    -1,   118,   221,
     123,   221,   119,    -1,   118,     1,   119,    -1,    -1,   118,
     168,   119,   167,    -1,    88,   113,   159,    -1,    -1,    64,
     160,   167,   145,   124,   170,   172,   125,    -1,    -1,    64,
     160,   124,   171,   172,   125,    -1,   173,   174,   192,   177,
     178,    -1,    -1,   173,   143,    -1,   173,   148,    -1,   173,
     156,    -1,    65,   175,   122,    -1,    65,   175,     1,   122,
      -1,    65,     1,   122,    -1,     1,   122,    -1,   176,    -1,
     175,   123,   176,    -1,    88,    -1,    88,   124,   221,   125,
      -1,    88,   124,     1,   125,    -1,    67,    88,   122,    -1,
       1,   122,    -1,    -1,    68,   179,   122,    -1,    68,     1,
     122,    -1,   180,    -1,   179,   123,   183,    -1,    -1,    88,
      76,    88,   124,   181,   186,   188,   189,   191,   125,    -1,
      -1,    88,    77,    88,   124,   182,   186,   188,   189,   191,
     125,    -1,    -1,    76,    88,   124,   184,   186,   188,   189,
     191,   125,    -1,    -1,    77,    88,   124,   185,   186,   188,
     189,   191,   125,    -1,   180,    -1,    -1,    69,   187,   122,
      -1,   160,   113,   159,    -1,   187,   123,   160,   113,   159,
      -1,    -1,    70,   221,   122,    -1,    70,   221,     1,   122,
      -1,    70,     1,   122,    -1,    -1,    71,   190,   122,    -1,
      71,   190,     1,   122,    -1,    71,     1,   122,    -1,   221,
      14,    -1,   221,     1,    14,    -1,   221,   112,    -1,   221,
       1,   112,    -1,    -1,    72,   220,   122,    -1,    72,     1,
     122,    -1,    -1,   192,   193,    -1,   192,   194,    -1,   192,
     195,    -1,   192,   196,    -1,    66,   197,   122,    -1,    66,
     197,     1,   122,    -1,    66,     1,   122,    -1,    58,   198,
     122,    -1,    58,   198,     1,   122,    -1,    58,     1,   122,
      -1,    78,   199,   122,    -1,    78,   199,     1,   122,    -1,
      78,     1,   122,    -1,    79,   200,   122,    -1,    79,   200,
       1,   122,    -1,    79,     1,   122,    -1,    88,    -1,   197,
     123,    88,    -1,    88,    -1,   198,   123,    88,    -1,    88,
      -1,   199,   123,    88,    -1,    88,    -1,   200,   123,    88,
      -1,    -1,   124,   202,   203,   204,   125,    -1,    -1,   203,
     148,    -1,   203,   156,    -1,    -1,   204,   205,    -1,   204,
       1,   122,    -1,   201,    -1,   122,    -1,   221,   122,    -1,
      -1,    41,   116,   220,   122,   220,   122,   220,   117,   206,
     205,    -1,    -1,    41,   116,   160,   113,   159,   117,   207,
     205,    -1,    41,   116,     1,   117,   205,    -1,    -1,    42,
     116,   208,   220,   117,   205,    -1,    42,   116,     1,   117,
     205,    -1,    -1,    43,   209,   205,    42,   116,   220,   117,
     122,    -1,    -1,    47,   116,   210,   220,   117,   205,   212,
      -1,    44,   122,    -1,    45,   122,    -1,    -1,    46,   116,
     220,   117,   211,   124,   214,   125,    -1,    51,   221,   122,
      -1,    51,   122,    -1,    -1,    -1,    48,   213,   205,    -1,
     215,    -1,   214,   215,    -1,    -1,    49,   221,   113,   216,
     204,    -1,    -1,    49,     1,   113,   217,   204,    -1,    -1,
      50,   113,   218,   204,    -1,    -1,    50,     1,   113,   219,
     204,    -1,   221,    -1,   220,   123,   221,    -1,    61,    -1,
      60,    -1,    90,    -1,    88,    -1,    -1,   221,   116,   222,
     229,   117,    -1,    -1,   221,   116,   223,     1,   117,    -1,
     221,   118,   221,   119,    -1,   221,   118,     1,   119,    -1,
     116,   221,   117,    -1,   116,     1,   117,    -1,   221,    15,
      -1,    15,   221,    -1,   221,    16,    -1,    16,   221,    -1,
     228,   221,    -1,   221,    35,   221,    -1,   221,    36,   221,
      -1,   221,    37,   221,    -1,   221,    38,   221,    -1,   221,
      40,   221,    -1,   221,    39,   221,    -1,   221,    17,   221,
      -1,   221,    18,   221,    -1,   221,    19,   221,    -1,   221,
      20,   221,    -1,   221,    23,   221,    -1,   221,   114,   221,
      -1,   221,    24,   221,    -1,   221,    25,   221,    -1,   221,
      26,   221,    -1,   221,    27,   221,    -1,   221,    28,   221,
      -1,   221,    29,   221,    -1,   221,   112,   221,   113,   221,
      -1,   221,   120,    88,    -1,   221,   121,    -1,    80,    -1,
      -1,   221,    32,   224,   221,    -1,   221,    30,   221,    -1,
     221,    31,   221,    -1,    33,   221,    -1,   221,    21,   221,
      -1,   221,    22,   221,    -1,    -1,    34,   116,   160,   113,
     159,   117,   225,   221,    -1,   226,    -1,   221,   227,   221,
      -1,     3,    -1,     4,    -1,     5,    -1,     7,    -1,     8,
      -1,     6,    -1,    10,    -1,     9,    -1,    11,    -1,    12,
      -1,    13,    -1,    18,    -1,    17,    -1,    14,    -1,    -1,
     221,    -1,   229,   123,   221,    -1,   231,   130,   132,    -1,
      -1,   231,   232,    -1,   231,   236,    -1,   148,    -1,    -1,
      57,   233,   234,   122,    -1,    57,     1,   122,    -1,   235,
      -1,   234,   123,   235,    -1,    88,   155,   152,    -1,    -1,
      64,   160,   242,   124,   237,   246,   125,    -1,    -1,    64,
     160,   242,     1,   124,   238,   246,   125,    -1,    -1,    64,
     160,     1,   124,   239,   246,   125,    -1,    -1,    64,     1,
     124,   240,   246,   125,    -1,    -1,    64,   160,   124,   241,
     246,   125,    -1,   116,   117,    -1,   116,   243,   117,    -1,
     116,     1,   117,    -1,   244,    -1,   245,    -1,   243,   122,
     244,    -1,   243,   122,   245,    -1,   159,    88,   155,    -1,
     244,   123,    88,   155,    -1,    57,    88,   155,    -1,   245,
     123,    88,   155,    -1,   247,   248,   192,   177,   252,    -1,
      -1,   247,   232,    -1,    65,   249,   122,    -1,     1,   122,
      -1,   250,    -1,   249,   123,   250,    -1,    88,    -1,    88,
     124,   251,   125,    -1,   221,    -1,   221,     1,   123,    -1,
     251,   123,   221,    -1,    -1,    68,   253,   122,    -1,    68,
     253,     1,   122,    -1,    68,     1,   122,    -1,   254,    -1,
     253,   123,   256,    -1,    -1,    88,    76,    88,   124,   255,
     258,   189,   191,   125,    -1,    -1,    76,    88,   124,   257,
     258,   189,   191,   125,    -1,   254,    -1,    -1,    70,   259,
     122,    -1,    70,   259,     1,   122,    -1,   221,    -1,   259,
     123,   221,    -1,   261,   262,    -1,    -1,   261,   262,   126,
      -1,    -1,    86,    -1,   263,   221,    -1,   221,    85,   221,
      -1,    81,    -1,    82,    -1,    83,    -1,    84,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   247,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   271,   274,   276,   276,   281,   284,   287,
     290,   295,   297,   299,   302,   304,   308,   309,   310,   311,
     312,   316,   317,   320,   326,   327,   330,   332,   334,   336,
     339,   343,   345,   346,   347,   348,   349,   350,   351,   354,
     356,   363,   363,   370,   371,   372,   378,   379,   383,   387,
     394,   400,   401,   405,   411,   412,   416,   417,   423,   424,
     428,   431,   437,   438,   439,   447,   450,   456,   457,   461,
     467,   471,   475,   483,   484,   488,   489,   493,   500,   501,
     505,   511,   512,   513,   514,   515,   516,   520,   521,   522,
     523,   533,   534,   537,   542,   542,   548,   548,   559,   562,
     564,   565,   566,   570,   571,   574,   577,   581,   582,   586,
     589,   592,   599,   602,   605,   607,   608,   614,   615,   619,
     619,   625,   625,   634,   634,   639,   639,   644,   647,   649,
     653,   656,   660,   662,   665,   669,   674,   676,   677,   680,
     686,   689,   693,   696,   702,   704,   707,   712,   714,   715,
     716,   717,   721,   722,   725,   731,   732,   735,   741,   742,
     745,   751,   752,   755,   761,   764,   770,   773,   779,   782,
     788,   791,   802,   802,   810,   812,   813,   816,   818,   819,
     823,   824,   827,   830,   830,   836,   836,   842,   843,   843,
     849,   850,   850,   856,   856,   860,   863,   866,   866,   872,
     875,   881,   884,   884,   893,   894,   898,   898,   904,   904,
     911,   911,   917,   917,   927,   928,   933,   936,   939,   942,
     945,   945,   950,   950,   956,   959,   963,   964,   968,   971,
     974,   977,   980,   983,   986,   989,   992,   995,   998,  1001,
    1004,  1007,  1010,  1013,  1016,  1019,  1022,  1025,  1028,  1031,
    1034,  1037,  1040,  1043,  1046,  1049,  1049,  1054,  1057,  1060,
    1063,  1066,  1069,  1069,  1074,  1078,  1084,  1085,  1086,  1087,
    1088,  1089,  1090,  1091,  1092,  1093,  1094,  1099,  1100,  1101,
    1106,  1107,  1111,  1122,  1125,  1127,  1128,  1132,  1133,  1133,
    1138,  1141,  1142,  1146,  1155,  1155,  1161,  1161,  1168,  1168,
    1175,  1175,  1182,  1182,  1191,  1192,  1193,  1200,  1204,  1208,
    1212,  1219,  1223,  1230,  1235,  1242,  1245,  1247,  1251,  1252,
    1256,  1257,  1261,  1264,  1270,  1271,  1274,  1279,  1281,  1282,
    1285,  1291,  1292,  1296,  1296,  1306,  1306,  1311,  1314,  1316,
    1319,  1326,  1327,  1333,  1335,  1337,  1339,  1341,  1344,  1347,
    1352,  1353,  1354,  1355
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
  "T_BOOL_OR", "T_KW_AND", "T_KW_OR", "T_KW_IMPLY", "T_KW_NOT", "T_FORALL",
  "T_LT", "T_LEQ", "T_EQ", "T_NEQ", "T_GEQ", "T_GT", "T_FOR", "T_WHILE",
  "T_DO", "T_BREAK", "T_CONTINUE", "T_SWITCH", "T_IF", "T_ELSE", "T_CASE",
  "T_DEFAULT", "T_RETURN", "T_CHAN_PRIORITY", "T_PROC_PRIORITY",
  "T_TYPEDEF", "T_STRUCT", "T_CONST", "T_OLDCONST", "T_URGENT",
  "T_BROADCAST", "T_TRUE", "T_FALSE", "T_META", "T_SYSTEM", "T_PROCESS",
  "T_STATE", "T_COMMIT", "T_INIT", "T_TRANS", "T_SELECT", "T_GUARD",
  "T_SYNC", "T_ASSIGN", "T_BEFORE", "T_AFTER", "T_PROGRESS", "T_ARROW",
  "T_UNCONTROL_ARROW", "T_WINNING", "T_LOSING", "T_DEADLOCK", "T_EF",
  "T_EG", "T_AF", "T_AG", "T_LEADSTO", "T_QUIT", "T_ERROR", "T_ID",
  "T_TYPENAME", "T_NAT", "T_NEW", "T_NEW_DECLARATION", "T_NEW_LOCAL_DECL",
  "T_NEW_INST", "T_NEW_SYSTEM", "T_NEW_PARAMETERS", "T_NEW_INVARIANT",
  "T_NEW_GUARD", "T_NEW_SYNC", "T_NEW_ASSIGN", "T_NEW_SELECT", "T_OLD",
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
  "OptionalTemplateSetList", "TemplateSet", "ProcDecl", "@3", "@4",
  "ProcBody", "ProcLocalDeclList", "States", "StateDeclList", "StateDecl",
  "Init", "Transitions", "TransitionList", "Transition", "@5", "@6",
  "TransitionOpt", "@7", "@8", "Select", "SelectList", "Guard", "Sync",
  "SyncExpr", "Assign", "LocFlags", "Commit", "Urgent", "Winning",
  "Losing", "CStateList", "UStateList", "WStateList", "LStateList",
  "Block", "@9", "BlockLocalDeclList", "StatementList", "Statement", "@10",
  "@11", "@12", "@13", "@14", "@15", "ElsePart", "@16", "SwitchCaseList",
  "SwitchCase", "@17", "@18", "@19", "@20", "ExprList", "Expression",
  "@21", "@22", "@23", "@24", "Assignment", "AssignOp", "UnaryOp",
  "ArgList", "OldXTA", "OldDeclaration", "OldVarDecl", "@25",
  "OldConstDeclIdList", "OldConstDeclId", "OldProcDecl", "@26", "@27",
  "@28", "@29", "@30", "OldProcParams", "OldProcParamList", "OldProcParam",
  "OldProcConstParam", "OldProcBody", "OldVarDeclList", "OldStates",
  "OldStateDeclList", "OldStateDecl", "OldInvariant", "OldTransitions",
  "OldTransitionList", "OldTransition", "@31", "OldTransitionOpt", "@32",
  "OldGuard", "OldGuardList", "PropertyList", "PropertyList2", "Property",
  "Quantifier", 0
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
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,    63,    58,    38,   367,    40,    41,    91,    93,
      46,    39,    59,    44,   123,   125,    10
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned short int yyr1[] =
{
       0,   127,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   128,   129,   130,   131,   130,   130,   130,   130,
     130,   132,   133,   133,   134,   134,   135,   135,   135,   135,
     135,   136,   136,   136,   137,   137,   138,   138,   139,   139,
     139,   140,   140,   140,   140,   140,   140,   140,   140,   141,
     142,   144,   143,   145,   145,   145,   146,   146,   147,   147,
     148,   149,   149,   150,   151,   151,   152,   152,   153,   153,
     154,   154,   155,   155,   155,   156,   156,   157,   157,   158,
     159,   159,   159,   160,   160,   161,   161,   162,   163,   163,
     164,   165,   165,   165,   165,   165,   165,   166,   166,   166,
     166,   167,   167,   168,   170,   169,   171,   169,   172,   173,
     173,   173,   173,   174,   174,   174,   174,   175,   175,   176,
     176,   176,   177,   177,   178,   178,   178,   179,   179,   181,
     180,   182,   180,   184,   183,   185,   183,   183,   186,   186,
     187,   187,   188,   188,   188,   188,   189,   189,   189,   189,
     190,   190,   190,   190,   191,   191,   191,   192,   192,   192,
     192,   192,   193,   193,   193,   194,   194,   194,   195,   195,
     195,   196,   196,   196,   197,   197,   198,   198,   199,   199,
     200,   200,   202,   201,   203,   203,   203,   204,   204,   204,
     205,   205,   205,   206,   205,   207,   205,   205,   208,   205,
     205,   209,   205,   210,   205,   205,   205,   211,   205,   205,
     205,   212,   213,   212,   214,   214,   216,   215,   217,   215,
     218,   215,   219,   215,   220,   220,   221,   221,   221,   221,
     222,   221,   223,   221,   221,   221,   221,   221,   221,   221,
     221,   221,   221,   221,   221,   221,   221,   221,   221,   221,
     221,   221,   221,   221,   221,   221,   221,   221,   221,   221,
     221,   221,   221,   221,   221,   224,   221,   221,   221,   221,
     221,   221,   225,   221,   221,   226,   227,   227,   227,   227,
     227,   227,   227,   227,   227,   227,   227,   228,   228,   228,
     229,   229,   229,   230,   231,   231,   231,   232,   233,   232,
     232,   234,   234,   235,   237,   236,   238,   236,   239,   236,
     240,   236,   241,   236,   242,   242,   242,   243,   243,   243,
     243,   244,   244,   245,   245,   246,   247,   247,   248,   248,
     249,   249,   250,   250,   251,   251,   251,   252,   252,   252,
     252,   253,   253,   255,   254,   257,   256,   256,   258,   258,
     258,   259,   259,   260,   261,   261,   262,   262,   262,   262,
     263,   263,   263,   263
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     3,     0,     0,     9,     8,     7,     6,
       4,     4,     0,     3,     0,     3,     1,     3,     3,     3,
       3,     3,     4,     3,     1,     3,     0,     4,     0,     5,
       3,     0,     2,     2,     2,     2,     2,     2,     2,     4,
       4,     0,     8,     2,     3,     3,     1,     3,     4,     3,
       3,     1,     3,     3,     0,     2,     1,     3,     1,     3,
       3,     1,     0,     4,     4,     4,     3,     1,     3,     2,
       3,     5,     5,     1,     1,     1,     2,     3,     1,     3,
       2,     0,     1,     1,     2,     1,     1,     0,     3,     5,
       3,     0,     4,     3,     0,     8,     0,     6,     5,     0,
       2,     2,     2,     3,     4,     3,     2,     1,     3,     1,
       4,     4,     3,     2,     0,     3,     3,     1,     3,     0,
      10,     0,    10,     0,     9,     0,     9,     1,     0,     3,
       3,     5,     0,     3,     4,     3,     0,     3,     4,     3,
       2,     3,     2,     3,     0,     3,     3,     0,     2,     2,
       2,     2,     3,     4,     3,     3,     4,     3,     3,     4,
       3,     3,     4,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     0,     5,     0,     2,     2,     0,     2,     3,
       1,     1,     2,     0,    10,     0,     8,     5,     0,     6,
       5,     0,     8,     0,     7,     2,     2,     0,     8,     3,
       2,     0,     0,     3,     1,     2,     0,     5,     0,     5,
       0,     4,     0,     5,     1,     3,     1,     1,     1,     1,
       0,     5,     0,     5,     4,     4,     3,     3,     2,     2,
       2,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     5,     3,     2,     1,     0,     4,     3,     3,     2,
       3,     3,     0,     8,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     1,     3,     3,     0,     2,     2,     1,     0,     4,
       3,     1,     3,     3,     0,     7,     0,     8,     0,     7,
       0,     6,     0,     6,     2,     3,     3,     1,     1,     3,
       3,     3,     4,     3,     4,     5,     0,     2,     3,     2,
       1,     3,     1,     4,     1,     3,     3,     0,     3,     4,
       3,     1,     3,     0,     9,     0,     8,     1,     0,     3,
       4,     1,     3,     2,     0,     3,     0,     1,     2,     3,
       1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned short int yydefact[] =
{
       0,     0,     0,   119,    24,    32,   101,     0,     0,     0,
       0,     0,   304,   304,   336,    24,   101,     0,     0,     0,
     364,     0,     0,     0,     2,    24,   101,   101,     5,     0,
       6,    34,   105,   102,   103,   106,     7,    66,     0,     0,
     299,     0,     0,   298,   297,     0,     0,   237,   236,   274,
     239,   238,     0,     8,   284,     0,    10,    11,     0,    12,
     234,    93,    94,     0,     9,    13,    24,   101,   101,    16,
       0,     0,    17,   327,   328,     0,    18,   361,    19,    20,
      21,   366,    22,     1,    58,     0,     0,     0,     0,    32,
      56,    57,    52,    53,    54,     0,    55,   120,   121,   122,
       0,    36,     0,     0,     0,   104,   101,    82,     0,     0,
     107,   249,   251,   279,     0,     0,     0,   286,   287,   288,
     291,   289,   290,   293,   292,   294,   295,   296,   248,   250,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   275,     0,     0,     0,     0,
       0,     0,     0,     0,   240,     0,     0,   273,     0,   252,
       0,   160,   162,     0,   101,     0,     0,     0,    32,   307,
       0,   305,   306,   337,    82,    82,   101,     0,     0,     0,
       0,     0,   370,   371,   372,   373,   367,     0,   363,     0,
       0,     0,   111,     0,     0,    23,     0,    71,    82,     0,
       0,     0,     0,    33,     0,     0,    46,    67,    69,    82,
       0,     0,    90,     0,   247,   246,   259,   260,   261,   262,
     280,   281,   263,   265,   266,   267,   268,   269,   270,   277,
     278,     0,   253,   254,   255,   256,   258,   257,     0,   264,
     300,     0,     0,     0,   272,   285,   161,   163,   235,   150,
       0,     0,     0,     0,     0,   303,    82,   333,   331,   329,
     330,    82,    82,   345,   346,   362,     0,   365,   368,    86,
       0,    87,    82,     0,   116,     0,     0,     0,    70,     0,
       0,     0,    74,    30,     0,    40,    38,    39,    37,    35,
       0,    44,     0,     0,    31,     0,    68,     0,     0,   101,
      95,     0,     0,   101,   276,     0,   301,     0,     0,   245,
     244,   101,   310,    82,     0,   311,   320,     0,     0,   322,
       0,   332,   334,   369,    85,     0,    89,     0,     0,   119,
       0,    59,    60,    72,     0,    63,     0,    61,     0,    73,
       0,     0,    43,     0,    41,     0,    48,     0,     0,    92,
      82,     0,    98,    91,    96,   110,   108,     0,     0,   271,
     241,     0,   243,   151,     0,   309,     0,   336,   318,     0,
     324,     0,   336,     0,   314,    88,   101,   111,     0,     0,
     114,    65,    64,   194,     0,    75,    76,    29,     0,   300,
      42,    45,     0,    84,    83,   100,    97,     0,     0,   282,
     302,   313,   312,     0,     0,   336,   326,   325,     0,   316,
     336,   113,   112,   117,     0,     0,   167,   119,   197,   239,
      81,     0,    78,     0,     0,    28,     0,    47,     0,    99,
     109,     0,   321,     0,     0,   167,     0,   323,   336,     0,
     126,     0,   129,     0,   127,     0,     0,   195,   196,     0,
       0,    77,     0,    27,     0,     0,    50,   283,   339,   342,
       0,   340,     0,   319,     0,   315,   125,     0,     0,   123,
       0,     0,     0,     0,     0,     0,     0,   134,   168,   169,
     170,   171,   115,     0,     0,     0,   211,     0,     0,     0,
       0,     0,   201,   192,    62,   200,   198,     0,    79,    80,
      26,     0,     0,   338,     0,   347,   317,     0,     0,   124,
     128,   133,     0,   186,     0,     0,   184,     0,     0,     0,
     188,     0,     0,   190,     0,     0,   118,   199,     0,     0,
       0,   215,   216,     0,   213,   220,     0,   194,   202,    49,
       0,   341,     0,   335,   131,   130,   177,     0,   175,     0,
     174,     0,   172,     0,   132,   180,     0,   178,     0,   183,
       0,   181,     0,     0,     0,     0,   137,     0,     0,     0,
       0,     0,     0,     0,     0,   219,   197,   343,     0,     0,
       0,   351,   176,   187,   173,   185,   179,   189,   182,   191,
     136,     0,     0,   135,     0,     0,   101,     0,     0,     0,
       0,   217,     0,     0,   350,     0,     0,   348,     0,     0,
       0,     0,     0,   147,   138,   207,     0,     0,   210,     0,
       0,     0,     0,   193,     0,   349,     0,   357,   352,   139,
     141,     0,     0,   205,     0,   209,     0,     0,   221,   353,
       0,   148,   148,   143,   145,     0,     0,     0,     0,     0,
       0,   224,   222,   214,   358,   355,     0,   152,   152,   148,
     148,   206,   203,   212,     0,     0,     0,   230,   218,   225,
       0,     0,   156,   358,     0,     0,   156,   156,   152,   152,
       0,   228,   226,   232,   197,   223,     0,     0,   164,   156,
     149,     0,     0,   164,   164,   156,   156,   204,   197,   197,
     197,     0,     0,   359,     0,     0,     0,     0,   164,   155,
       0,   153,     0,     0,   164,   164,     0,     0,     0,   360,
     159,     0,   157,     0,     0,   354,     0,   154,   140,   142,
       0,     0,   158,   166,   165,   356,   144,   146
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,    22,    24,    28,   389,    30,    31,   104,   102,   206,
     292,   294,   392,    25,    90,    91,    92,   383,   281,    36,
      37,   169,   196,   197,   339,   420,   421,   422,   282,    94,
     270,   271,   170,    63,   299,   300,   351,   352,    39,   212,
     275,   328,    96,   417,   329,   378,   379,   416,   443,   444,
     477,   526,   565,   566,   641,   642,   614,   659,   660,   657,
      64,   676,   688,    57,   707,   445,   478,   479,   480,   481,
     517,   514,   521,   524,   495,   537,   418,   449,   496,   680,
     645,   571,   530,   574,   621,   653,   670,   650,   651,   699,
     698,   684,   700,    59,   497,   240,   241,   231,   431,    54,
     158,    55,   307,    65,    66,   171,   252,   314,   315,   172,
     410,   438,   405,   367,   372,   320,    72,    73,    74,   403,
     404,   435,   460,   461,    76,   543,   580,   581,   654,   628,
     673,   672,    78,    80,    81,   188,   189
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -627
static const short int yypact[] =
{
    1051,  3182,   687,  -627,  -627,    62,    33,  2914,  2914,  2914,
    2914,   168,  -627,  -627,  -627,  -627,   290,  2914,  2914,  2914,
    -627,  2914,    79,    89,  -627,  1049,   901,   364,   -30,   144,
    -627,   219,  -627,   218,  -627,  -627,   166,  -627,   -48,    -9,
    -627,  2914,  2914,  -627,  -627,  2914,   180,  -627,  -627,  -627,
    -627,  -627,   554,  2162,  -627,  2914,  2162,  -627,  1178,   169,
    2162,  -627,  -627,   224,   230,  -627,   810,   581,   603,   -30,
     263,   272,   248,   255,   280,   697,   283,  2162,   285,   169,
    -627,  3126,  2162,  -627,  -627,   313,   168,   293,   301,   -33,
    -627,  -627,  -627,  -627,  -627,   168,  -627,  -627,  -627,  -627,
     234,  -627,   -13,   144,   350,  -627,    33,  -627,   351,   316,
     323,    96,    96,  2319,   168,   325,  1653,  -627,  -627,  -627,
    -627,  -627,  -627,  -627,  -627,  -627,  -627,  -627,  -627,  -627,
    2914,  2914,  2914,  2914,  2914,  2914,  2914,  2914,  2914,  2914,
    2914,  2914,  2914,  2914,  2914,  -627,  2914,  2914,  2914,  2914,
    2914,  2914,  2914,  2914,   443,  2348,   361,  -627,  2914,    96,
       3,  -627,  2914,  2914,    33,   168,    17,    19,   -33,  -627,
     168,  -627,  -627,  -627,  -627,  -627,   290,   362,   363,   332,
    2914,  2914,  -627,  -627,  -627,  -627,  -627,  1691,   330,  2914,
     335,   168,   -64,  2914,  2914,  -627,   138,  -627,   342,   337,
     380,    22,    31,  -627,    83,    97,   397,  -627,   357,  -627,
     539,  2389,  -627,   365,  -627,  -627,   396,   396,    96,    96,
     289,   289,    96,  2970,  3005,   378,   378,  2944,  2898,  2319,
    2281,  2914,   981,   981,  3112,  3112,   981,   981,  1810,  3077,
    2914,   475,   358,  1848,  -627,  2319,  -627,  -627,  2162,  -627,
     366,   360,   395,   367,    36,  -627,  -627,   357,   357,   255,
     280,  -627,  -627,  -627,  2162,  2162,  2914,  -627,  2162,  -627,
     221,  -627,  -627,   398,  -627,   342,   123,   150,  -627,   168,
     228,   368,    39,  -627,    42,  -627,  -627,  -627,  -627,  -627,
     375,  -627,    27,   381,  -627,  2428,   357,   379,   168,   185,
    -627,   369,  1216,    33,  2281,  2914,  2162,   -56,   370,  -627,
    -627,    33,  -627,  -627,   233,  -627,  -627,   382,   212,  -627,
      29,   357,   357,  2162,  -627,   168,   357,   372,   371,  -627,
     383,  -627,  -627,  -627,   392,  -627,   -21,  -627,  2711,  -627,
     389,   205,  -627,   393,  -627,   401,  -627,   400,  1967,  -627,
    -627,   236,  -627,  -627,  -627,  -627,  -627,  2914,   403,  2837,
    -627,  2914,  -627,  -627,  2674,  -627,   395,  -627,  -627,   405,
    -627,   -46,  -627,   399,  -627,  -627,    33,   406,   402,    28,
    -627,  -627,  -627,  -627,  2706,  -627,  2162,  -627,   -23,  2914,
    -627,  -627,  2594,  -627,  -627,   357,  -627,   168,  2005,  -627,
    2162,  -627,  -627,   407,   277,  -627,  -627,  -627,   409,  -627,
    -627,  -627,  -627,  -627,   415,   100,  -627,  -627,   708,   412,
    -627,   200,  -627,   418,   416,  -627,   111,  -627,  1337,  -627,
    -627,  2914,  -627,   417,   440,  -627,   410,  -627,  -627,   426,
    -627,   419,   429,    48,  -627,   551,   432,  -627,  -627,   532,
    2706,  -627,  2711,  -627,   421,  2914,  -627,  2162,  -627,   430,
     240,  -627,   551,  -627,   435,  -627,  -627,  2440,   439,  -627,
     492,   441,   112,   120,   496,   121,   174,   517,  -627,  -627,
    -627,  -627,  -627,   464,   473,   483,  -627,   469,   478,   486,
     488,  2790,  -627,  -627,  -627,  -627,  -627,  1375,  -627,  -627,
    -627,  1495,  2914,  -627,   440,   538,  -627,   482,  1016,  -627,
    -627,  -627,   489,  -627,    58,   494,  -627,    61,   499,   501,
    -627,    72,   502,  -627,    74,   176,  -627,  -627,   413,  2477,
    2653,  -627,  -627,  2914,  -627,  -627,  1533,  -627,  -627,  -627,
     215,  -627,   206,  -627,  -627,  -627,  -627,   503,  -627,   520,
    -627,   504,  -627,   522,  -627,  -627,   509,  -627,   544,  -627,
     511,  -627,   547,   514,   297,   258,  -627,   529,   534,   261,
     533,  2914,   607,   132,  2914,  -627,   708,  -627,   530,   575,
      76,  -627,  -627,  -627,  -627,  -627,  -627,  -627,  -627,  -627,
    -627,   565,   567,  -627,   -20,  2653,    33,  2914,  2653,   159,
     542,  -627,   196,   893,  -627,   578,   541,  -627,   -35,   543,
     545,   583,   584,  -627,  -627,  -627,   556,   265,  -627,  2653,
    2914,   550,  2653,  -627,   552,  -627,   587,  -627,  -627,  -627,
    -627,   553,   555,  -627,  2914,  -627,   203,   340,   630,  -627,
     557,   613,   613,  -627,  -627,  2653,   207,   561,  2508,    46,
     177,  -627,  -627,  -627,   614,  -627,   168,   615,   615,   613,
     613,  -627,  -627,  -627,   573,  2124,   576,  -627,  -627,  -627,
    2653,  2914,   619,   614,   269,  2545,   619,   619,   615,   615,
    2653,  -627,  -627,  -627,  -627,  -627,    80,  2557,   620,   619,
    -627,   571,  1056,   620,   620,   619,   619,  -627,  -627,  -627,
    -627,   420,   572,  -627,   574,    32,  2569,   570,   620,  -627,
     589,  -627,   605,   606,   620,   620,   739,   790,   842,  -627,
    -627,   616,  -627,   617,   310,  -627,   622,  -627,  -627,  -627,
     623,   625,  -627,  -627,  -627,  -627,  -627,  -627
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -627,  -627,  -627,     6,  -627,   129,  -627,  -627,   641,  -627,
    -627,  -627,  -627,   750,  -627,  -627,   -12,  -627,   484,   485,
     652,   -18,  -627,   490,  -627,  -286,  -627,   318,   -71,   -14,
    -627,   446,     0,     2,  -627,   476,  -627,   377,  -627,  -627,
     424,  -627,  -627,  -627,  -627,   376,   774,  -627,  -627,   308,
     317,  -627,  -627,   193,  -627,  -627,  -627,  -627,  -627,  -406,
     136,  -614,  -626,   107,  -463,   386,  -627,  -627,  -627,  -627,
    -627,  -627,  -627,  -627,  -627,  -627,   259,  -537,  -430,  -627,
    -627,  -627,  -627,  -627,  -627,  -627,  -627,  -627,   145,  -627,
    -627,  -627,  -627,   -15,    -7,  -627,  -627,  -627,  -627,  -627,
    -627,  -627,   414,  -627,   785,   -63,  -627,  -627,   436,  -627,
    -627,  -627,  -627,  -627,  -627,  -627,   498,   634,   636,  -147,
     800,  -627,  -627,   321,   324,  -627,  -627,   220,  -627,  -627,
    -627,   157,   167,  -627,  -627,  -627,  -627
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -345
static const short int yytable[] =
{
      53,    56,    58,    60,    79,   173,    38,    93,    93,    98,
      75,    77,    60,    99,    82,    97,    71,   246,   251,    29,
     253,    69,   201,   285,   202,    95,    95,    95,   343,   414,
     373,    89,   287,   721,   111,   112,   208,   317,   113,   603,
     107,   626,   338,   340,   677,   116,   109,   666,   159,   468,
     693,   694,   385,   579,   273,   100,   611,   612,   100,   547,
     274,   360,   551,   708,   695,   696,   108,   361,   564,   714,
     715,   407,   168,   556,   187,   560,   176,   606,   401,    83,
     110,   702,    85,  -101,    32,   191,    33,    34,   192,    32,
      35,    33,    34,   415,   424,    35,   382,   198,   290,   425,
     572,   441,   106,   257,   258,  -308,    38,    61,    62,   203,
     286,   128,   129,   512,    29,   247,   213,  -101,   201,   288,
     202,   515,   519,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   296,   232,
     233,   234,   235,   236,   237,   238,   239,   701,   243,   344,
     345,   245,   318,   374,   722,   238,   248,   295,   341,   667,
     319,   716,   717,   718,   249,   615,   499,   250,   618,   254,
     469,   470,   256,   264,   265,   522,    71,   563,   276,   277,
     548,   549,   268,   552,   553,   291,    60,    60,   442,   635,
     321,   322,   638,   272,   557,   558,   561,   562,   607,   608,
     513,   326,   703,   181,   302,   289,   388,   578,   516,   520,
     298,    84,   154,   369,   155,   661,   156,   157,   195,   -25,
     -25,   -25,   -25,   -25,   304,   408,   648,   649,   454,   334,
     712,   713,   101,   306,   361,   199,   658,   200,   -25,   -25,
     685,    32,   364,    33,    34,   726,   163,    35,   331,   601,
     697,   730,   731,   678,   679,   163,    61,    62,   436,   323,
     278,   279,   523,   439,   564,   -25,   -25,  -101,    32,    70,
      33,    34,   103,   163,    35,   332,   619,   105,   433,   395,
      38,   256,   163,  -101,    32,   -25,    33,    34,   348,   106,
      35,   464,   163,   -25,   579,   -25,   114,   255,   359,   298,
     350,  -101,   668,   358,   128,   129,   130,   131,   132,   133,
     353,   363,   136,   622,   190,   139,   140,  -101,    71,   163,
     647,   -25,   -25,   450,   662,   451,   163,   272,   -25,   370,
     163,   386,  -101,    32,   166,    33,    34,   164,   180,    35,
     577,   173,   434,   324,   325,   335,    32,    70,    33,    34,
     398,   174,    35,   165,   400,   365,   366,   386,   396,   397,
     175,    98,   503,   504,    -4,    99,  -101,    97,  -101,    32,
     176,    33,    34,   591,   592,    35,   411,   386,   177,    95,
     593,   594,   306,   597,   163,   428,   423,   634,   163,   648,
     649,   690,   165,   128,   129,   130,   131,   132,   133,   350,
     447,   136,  -101,   178,   448,   154,   180,   155,   181,   156,
     157,   128,   129,   205,   567,   132,   133,   193,    85,   136,
      32,   483,    33,    34,   457,   194,    35,    40,    41,    42,
      43,    44,   734,   163,    40,    41,    42,    43,    44,   209,
     210,   211,   214,   386,  -242,   386,    45,    46,   501,   244,
     261,   262,   423,    45,    46,   263,   267,   269,   280,   283,
     508,   484,   485,   486,   487,   488,   489,   490,   284,  -231,
    -231,   491,   293,    47,    48,   295,   308,   309,   303,   311,
      47,    48,   312,   313,   536,   376,   327,   362,   355,   391,
     377,   316,   337,    49,   154,    75,   155,   342,   156,   157,
      49,   419,    62,    51,   349,   346,   368,   380,    50,   381,
      51,   387,   154,   569,   155,   390,   156,   157,   573,   393,
     399,    60,   406,   409,   273,   -93,    60,   413,   459,    52,
     568,   452,   432,   483,   437,   463,    52,   440,   453,   458,
     297,   466,   492,   500,   493,  -231,    40,    41,    42,    43,
      44,   465,   471,   467,   502,   115,   599,   482,   447,   602,
     506,   509,   448,   511,    60,    45,    46,    60,    40,    41,
      42,    43,    44,   484,   485,   486,   487,   488,   489,   490,
     442,   -14,   617,   491,   518,   525,   527,    45,    46,   528,
      60,   531,    47,    48,  -101,    32,   616,    33,    34,   529,
     532,    35,   533,   -15,   534,   636,   542,   544,   583,   472,
     585,   546,    49,    60,    47,    48,   550,   473,   474,   646,
      50,   554,    51,   555,   559,   582,   584,    60,  -101,   475,
     476,   586,   587,   588,    49,   589,   590,    32,   166,    33,
      34,   665,    50,    35,    51,   167,   595,   596,    52,   600,
     598,   605,   604,   609,   492,   610,   493,   494,   620,    32,
     166,    33,    34,   625,    77,    35,   624,   629,   692,   630,
      52,   631,   632,   633,   637,   640,   639,   643,   652,   644,
      58,   655,   656,   663,   671,   675,   681,   -51,    23,   683,
     687,   724,   706,   709,   719,   725,   720,  -344,   179,    60,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   727,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     728,   729,   146,   147,   148,   149,   150,   151,   732,   733,
     483,   -51,   -51,   -51,   204,   -51,   -51,   735,   736,   -51,
     737,   -51,    26,    40,    41,    42,    43,    44,   207,   330,
     -51,   -51,    85,  -101,    32,   336,    33,    34,   498,   333,
      35,   375,    45,    46,   429,   354,   -51,    27,   510,   505,
     484,   485,   486,   487,   488,   489,   490,   613,  -229,  -229,
     491,   483,   674,   446,   705,   669,   576,  -101,    67,    47,
      48,   412,   402,   426,    40,    41,    42,    43,    44,   152,
     259,   153,   260,   154,    68,   155,   371,   156,   157,    49,
    -344,   462,  -344,    45,    46,   541,   540,    50,   627,    51,
     689,   484,   485,   486,   487,   488,   489,   490,   686,  -227,
    -227,   491,     0,   483,     0,     0,     0,     0,     0,     0,
      47,    48,     0,     0,     0,    52,    40,    41,    42,    43,
      44,   492,     0,   493,  -229,  -101,    32,   166,    33,    34,
      49,     0,    35,     0,   167,    45,    46,     0,    50,     0,
      51,     0,     0,   484,   485,   486,   487,   488,   489,   490,
       0,  -233,  -233,   491,   483,     0,     0,     0,     0,  -101,
       0,    -3,    47,    48,     0,     0,    52,    40,    41,    42,
      43,    44,   492,     0,   493,  -227,     0,     0,     0,     0,
       0,     0,    49,     0,     0,     0,    45,    46,     0,     0,
      50,     0,    51,     0,   484,   485,   486,   487,   488,   489,
     490,     0,     0,     0,   491,     0,     0,     0,     0,     0,
       0,     0,     0,    47,    48,    85,     0,    32,    52,    33,
      34,     0,     0,    35,   492,    86,   493,  -233,     0,     0,
       0,     0,     0,    49,    87,    88,     0,     0,     0,     0,
       0,    50,     0,    51,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   128,   129,   130,   131,
     132,   133,   134,   135,   136,     0,     0,   139,   140,    52,
       0,     0,     0,     0,     0,   492,     0,   493,   623,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
       0,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,     0,
       0,   146,   147,   148,   149,   150,   151,   710,     0,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
       0,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,     0,
       0,   146,   147,   148,   149,   150,   151,   154,     0,   155,
       0,   156,   157,    85,  -101,    32,     0,    33,    34,     0,
       0,    35,     0,    86,     0,     0,     0,     0,     0,     0,
       0,     0,    87,    88,     0,     0,     0,     0,   152,     0,
     153,     0,   154,     0,   155,     0,   156,   157,  -101,     0,
       0,   545,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,     0,     0,     0,     0,     0,   152,     0,
     153,     0,   154,     0,   155,     0,   156,   157,   711,   160,
       0,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   161,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,     0,     0,   146,   147,   148,   149,   150,   151,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
       0,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,     0,
       0,   146,   147,   148,   149,   150,   151,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     162,     0,   153,     0,   154,     0,   155,     0,   156,   157,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   152,     0,
     153,     0,   154,     0,   155,   356,   156,   157,     0,   357,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,     0,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
       0,     0,   146,   147,   148,   149,   150,   151,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,     0,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,     0,     0,
     146,   147,   148,   149,   150,   151,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   152,
     455,   153,     0,   154,     0,   155,     0,   156,   157,   456,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   152,     0,   153,
       0,   154,     0,   155,     0,   156,   157,   538,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,     0,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,     0,     0,
     146,   147,   148,   149,   150,   151,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,     0,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,     0,     0,   146,   147,
     148,   149,   150,   151,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   152,     0,   153,
       0,   154,     0,   155,     0,   156,   157,   539,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   152,     0,   153,     0,   154,
       0,   155,     0,   156,   157,   575,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,     0,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,     0,     0,   146,   147,
     148,   149,   150,   151,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,     0,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,     0,     0,   146,   147,   148,   149,
     150,   151,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   152,     0,   153,     0,   154,
     215,   155,     0,   156,   157,     0,   266,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   152,     0,   153,     0,   154,     0,   155,
       0,   156,   157,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,     0,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,     0,     0,   146,   147,   148,   149,   150,
     151,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,     0,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,     0,     0,   146,   147,   148,   149,   150,   151,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   152,   305,   153,     0,   154,     0,   155,     0,
     156,   157,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     152,     0,   153,     0,   154,     0,   155,   310,   156,   157,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,     0,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
       0,     0,   146,   147,   148,   149,   150,   151,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,     0,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,     0,     0,
     146,   147,   148,   149,   150,   151,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   152,
       0,   153,     0,   154,     0,   155,   394,   156,   157,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   152,     0,   153,
       0,   154,     0,   155,   430,   156,   157,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,     0,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,     0,     0,   146,
     147,   148,   149,   150,   151,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,     0,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,     0,     0,   146,   147,   148,
     149,   150,   151,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   152,   682,   153,     0,
     154,     0,   155,     0,   156,   157,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   152,     0,   153,     0,   154,     0,
     155,     0,   156,   157,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,     0,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,     0,     0,     0,     0,   146,   147,   148,   149,
     150,   151,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,     0,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   242,
       0,     0,     0,     0,   146,   147,   148,   149,   150,   151,
       0,     0,    40,    41,    42,    43,    44,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    45,    46,     0,     0,     0,     0,     0,     0,     0,
     301,     0,     0,   152,     0,   153,     0,   154,     0,   155,
       0,   156,   157,    40,    41,    42,    43,    44,    47,    48,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    45,    46,     0,     0,     0,     0,    49,   347,
       0,   152,     0,   153,     0,   154,    50,   155,    51,   156,
     157,   507,    40,    41,    42,    43,    44,     0,     0,    47,
      48,     0,     0,     0,    40,    41,    42,    43,    44,     0,
       0,    45,    46,     0,    52,     0,     0,     0,     0,    49,
       0,     0,     0,    45,    46,     0,     0,    50,   570,    51,
       0,     0,     0,     0,     0,     0,     0,     0,    47,    48,
       0,  -208,  -208,  -208,  -208,  -208,     0,     0,     0,     0,
      47,    48,     0,     0,     0,    52,     0,     0,    49,   664,
    -208,  -208,     0,     0,     0,     0,    50,     0,    51,     0,
      49,     0,    40,    41,    42,    43,    44,     0,    50,     0,
      51,     0,     0,     0,     0,     0,     0,  -208,  -208,     0,
       0,    45,    46,     0,    52,     0,   691,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    52,  -208,   704,    40,
      41,    42,    43,    44,     0,  -208,     0,  -208,    47,    48,
     723,    40,    41,    42,    43,    44,     0,     0,    45,    46,
       0,     0,     0,    40,    41,    42,    43,    44,    49,     0,
      45,    46,     0,  -208,     0,     0,    50,     0,    51,     0,
       0,     0,    45,    46,     0,    47,    48,     0,    40,    41,
      42,    43,    44,     0,     0,     0,     0,    47,    48,     0,
       0,     0,     0,     0,    52,    49,     0,    45,    46,    47,
      48,     0,     0,    50,     0,    51,     0,    49,     0,     0,
       0,     0,     0,     0,     0,    50,     0,    51,     0,    49,
       0,     0,     0,     0,    47,    48,     0,    50,     0,    51,
       0,    52,     0,     0,     0,     0,     0,    40,    41,    42,
      43,    44,     0,    52,    49,     0,     0,     0,     0,     0,
       0,     0,    50,     0,    51,    52,    45,    46,    40,    41,
      42,    43,    44,     0,   484,   485,   486,   487,   488,   489,
     490,     0,     0,     0,   491,     0,     0,    45,    46,     0,
      52,     0,     0,    47,    48,     0,     0,     0,     0,   427,
      40,    41,    42,    43,    44,    40,    41,    42,    43,    44,
       0,     0,     0,    49,    47,    48,     0,     0,     0,    45,
      46,    50,     0,    51,    45,    46,     0,     0,     0,     0,
       0,     0,     0,     0,    49,     0,     0,     0,     0,     0,
       0,     0,    50,     0,    51,     0,    47,    48,     0,    52,
       0,    47,    48,     0,     0,   492,     0,   493,     0,     0,
       0,     0,     0,     0,     0,     0,    49,     0,     0,     0,
      52,    49,   295,     0,   419,    62,    51,     0,   384,    50,
       0,    51,     0,     0,    40,    41,    42,    43,    44,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    52,    45,    46,     0,     0,    52,     0,     0,
     384,     0,     0,     0,     0,   384,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      47,    48,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,     0,     0,     0,
      49,     0,   146,   147,   148,   149,   150,   151,    50,     0,
      51,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    52,     0,     0,     0,
       0,     0,   535,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,     0,    40,    41,
      42,    43,    44,   146,   147,   148,   149,   150,   151,     0,
       0,     0,     0,     0,     0,     0,     0,    45,    46,   152,
       0,   153,     0,   154,     0,   155,     0,   156,   157,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,     0,     0,    47,    48,     0,     0,     0,   146,
     147,   148,   149,   150,   151,   128,   129,   130,   131,   132,
     133,   134,   135,   136,    49,   138,   139,   140,     0,     0,
       0,     0,    50,     0,    51,   146,   147,   148,   149,   150,
     151,     0,   153,     0,   154,     0,   155,     0,   156,   157,
     128,   129,   130,   131,   132,   133,   134,   135,   136,     0,
      52,   139,   140,     0,     0,     0,     0,     0,     0,     0,
     146,   147,   148,   149,   150,   151,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   153,     0,
     154,     0,   155,     0,   156,   157,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   153,     0,   154,     0,   155,     0,
     156,   157,   128,   129,   130,   131,   132,   133,   134,   135,
     136,     0,     0,   139,   140,     0,     0,     0,     0,     0,
       0,     0,   146,   147,   148,   149,   150,   151,     0,   153,
       0,   154,     0,   155,     0,   156,   157,   128,   129,   130,
     131,   132,   133,   134,   135,   136,     0,     0,   139,   140,
      40,    41,    42,    43,    44,     0,     0,   146,   147,     0,
       0,   150,   151,     0,     0,     0,     0,     0,     0,    45,
      46,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    23,     0,     0,    47,    48,     0,     0,
       0,     0,     0,   154,     0,   155,     0,   156,   157,     0,
       0,     0,     0,     0,     0,     0,    49,   182,   183,   184,
     185,     0,   186,     0,    50,     0,    51,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   154,     0,
     155,     0,   156,   157,   -51,   -51,   -51,   -51,   -51,     0,
     -51,   -51,    52,     0,   -51,   -51,   -51,     0,     0,     0,
       0,     0,     0,     0,     0,   -51,   -51,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -51,   -51
};

static const short int yycheck[] =
{
       7,     8,     9,    10,    19,    68,     6,    25,    26,    27,
      17,    18,    19,    27,    21,    27,    16,    14,     1,    52,
       1,    15,    35,     1,    37,    25,    26,    27,     1,     1,
       1,    25,     1,     1,    41,    42,   107,     1,    45,   576,
      88,    76,     3,     1,   658,    52,    55,     1,    55,     1,
     676,   677,   338,    88,   118,    88,    76,    77,    88,     1,
     124,   117,     1,   689,   678,   679,   114,   123,    88,   695,
     696,   117,    66,     1,    81,     1,   122,     1,   364,     0,
      89,     1,    54,    55,    56,    85,    58,    59,    86,    56,
      62,    58,    59,    65,   117,    62,   117,    95,     1,   122,
     530,     1,   123,   174,   175,    88,   106,    88,    89,   122,
      88,    15,    16,     1,    52,   112,   114,    89,    35,    88,
      37,     1,     1,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   209,   146,
     147,   148,   149,   150,   151,   152,   153,   684,   155,   122,
     123,   158,   116,   124,   122,   162,   163,   118,   116,   113,
     124,   698,   699,   700,   164,   595,   452,   165,   598,   167,
     122,   123,   170,   180,   181,     1,   176,     1,   193,   194,
     122,   123,   189,   122,   123,    88,   193,   194,    88,   619,
     261,   262,   622,   191,   122,   123,   122,   123,   122,   123,
      88,   272,   122,   123,   211,   122,     1,     1,    88,    88,
     210,   122,   116,     1,   118,   645,   120,   121,    89,    14,
      15,    16,    17,    18,   231,   372,    49,    50,   117,     1,
     693,   694,    88,   240,   123,     1,   642,     3,    33,    34,
     670,    56,   313,    58,    59,   708,   123,    62,   125,   117,
     680,   714,   715,   659,   660,   123,    88,    89,   405,   266,
     122,   123,    88,   410,    88,    60,    61,    55,    56,    57,
      58,    59,    53,   123,    62,   125,   117,    59,     1,   350,
     280,   279,   123,    55,    56,    80,    58,    59,   295,   123,
      62,   438,   123,    88,    88,    90,   116,   168,   305,   299,
     298,    89,   125,   303,    15,    16,    17,    18,    19,    20,
     125,   311,    23,   117,     1,    26,    27,    89,   318,   123,
     117,   116,   117,   123,   117,   125,   123,   325,   123,   117,
     123,   338,    55,    56,    57,    58,    59,   113,   123,    62,
     125,   404,    65,   122,   123,   117,    56,    57,    58,    59,
     357,    88,    62,   123,   361,   122,   123,   364,   122,   123,
      88,   379,   122,   123,     0,   379,    89,   379,    55,    56,
     122,    58,    59,    76,    77,    62,   376,   384,   123,   379,
     122,   123,   389,   122,   123,   392,   384,   122,   123,    49,
      50,   122,   123,    15,    16,    17,    18,    19,    20,   397,
     418,    23,    89,   123,   418,   116,   123,   118,   123,   120,
     121,    15,    16,    63,     1,    19,    20,   124,    54,    23,
      56,     1,    58,    59,   431,   124,    62,    14,    15,    16,
      17,    18,   122,   123,    14,    15,    16,    17,    18,    88,
     124,   118,   117,   450,     1,   452,    33,    34,   455,    88,
      88,    88,   450,    33,    34,   123,   126,   122,   116,   122,
     467,    41,    42,    43,    44,    45,    46,    47,    88,    49,
      50,    51,    75,    60,    61,   118,     1,   119,   113,   113,
      60,    61,   122,    88,   491,   113,    88,   117,   119,    88,
     119,   124,   124,    80,   116,   502,   118,   122,   120,   121,
      80,    88,    89,    90,   125,   124,   124,   124,    88,   117,
      90,   122,   116,   528,   118,   122,   120,   121,   533,   119,
     117,   528,   117,   124,   118,   113,   533,   125,    88,   116,
     528,   113,   125,     1,   125,   125,   116,   122,   122,   122,
       1,   122,   122,   122,   124,   125,    14,    15,    16,    17,
      18,   125,     1,   124,   124,     1,   571,   125,   576,   574,
     125,   122,   576,   122,   571,    33,    34,   574,    14,    15,
      16,    17,    18,    41,    42,    43,    44,    45,    46,    47,
      88,     0,   597,    51,    88,    68,   122,    33,    34,   116,
     597,   122,    60,    61,    55,    56,   596,    58,    59,   116,
     122,    62,   116,     0,   116,   620,    68,   125,    88,    58,
      88,   122,    80,   620,    60,    61,   122,    66,    67,   634,
      88,   122,    90,   122,   122,   122,   122,   634,    89,    78,
      79,   122,    88,   122,    80,    88,   122,    56,    57,    58,
      59,   648,    88,    62,    90,    64,   117,   113,   116,    42,
     117,    76,   122,    88,   122,    88,   124,   125,   116,    56,
      57,    58,    59,   122,   671,    62,    88,   124,   675,   124,
     116,    88,    88,   117,   124,    88,   124,   124,    48,   124,
     687,   124,    69,   122,    70,    70,   113,     0,     1,   113,
      71,   706,    72,   122,   122,   125,   122,     0,     1,   706,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,   122,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
     125,   125,    35,    36,    37,    38,    39,    40,   122,   122,
       1,    54,    55,    56,   103,    58,    59,   125,   125,    62,
     125,    64,     2,    14,    15,    16,    17,    18,   106,   275,
      73,    74,    54,    55,    56,   280,    58,    59,   450,   279,
      62,   325,    33,    34,   397,   299,    89,     3,   470,   462,
      41,    42,    43,    44,    45,    46,    47,   594,    49,    50,
      51,     1,   656,   417,   687,   650,   537,    89,    13,    60,
      61,   377,   366,   389,    14,    15,    16,    17,    18,   112,
     176,   114,   176,   116,    14,   118,   318,   120,   121,    80,
     123,   435,   125,    33,    34,   504,   502,    88,   608,    90,
     673,    41,    42,    43,    44,    45,    46,    47,   671,    49,
      50,    51,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,
      60,    61,    -1,    -1,    -1,   116,    14,    15,    16,    17,
      18,   122,    -1,   124,   125,    55,    56,    57,    58,    59,
      80,    -1,    62,    -1,    64,    33,    34,    -1,    88,    -1,
      90,    -1,    -1,    41,    42,    43,    44,    45,    46,    47,
      -1,    49,    50,    51,     1,    -1,    -1,    -1,    -1,    89,
      -1,     0,    60,    61,    -1,    -1,   116,    14,    15,    16,
      17,    18,   122,    -1,   124,   125,    -1,    -1,    -1,    -1,
      -1,    -1,    80,    -1,    -1,    -1,    33,    34,    -1,    -1,
      88,    -1,    90,    -1,    41,    42,    43,    44,    45,    46,
      47,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    60,    61,    54,    -1,    56,   116,    58,
      59,    -1,    -1,    62,   122,    64,   124,   125,    -1,    -1,
      -1,    -1,    -1,    80,    73,    74,    -1,    -1,    -1,    -1,
      -1,    88,    -1,    90,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    -1,    -1,    26,    27,   116,
      -1,    -1,    -1,    -1,    -1,   122,    -1,   124,   125,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    -1,
      -1,    35,    36,    37,    38,    39,    40,     1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    -1,
      -1,    35,    36,    37,    38,    39,    40,   116,    -1,   118,
      -1,   120,   121,    54,    55,    56,    -1,    58,    59,    -1,
      -1,    62,    -1,    64,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    73,    74,    -1,    -1,    -1,    -1,   112,    -1,
     114,    -1,   116,    -1,   118,    -1,   120,   121,    89,    -1,
      -1,   125,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,    -1,    -1,    -1,    -1,    -1,   112,    -1,
     114,    -1,   116,    -1,   118,    -1,   120,   121,   122,     1,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    -1,    -1,    35,    36,    37,    38,    39,    40,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    -1,
      -1,    35,    36,    37,    38,    39,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     112,    -1,   114,    -1,   116,    -1,   118,    -1,   120,   121,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   112,    -1,
     114,    -1,   116,    -1,   118,   119,   120,   121,    -1,   123,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      -1,    -1,    35,    36,    37,    38,    39,    40,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    39,    40,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   112,
     113,   114,    -1,   116,    -1,   118,    -1,   120,   121,   122,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   112,    -1,   114,
      -1,   116,    -1,   118,    -1,   120,   121,   122,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    39,    40,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    -1,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    -1,    -1,    35,    36,
      37,    38,    39,    40,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   112,    -1,   114,
      -1,   116,    -1,   118,    -1,   120,   121,   122,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   112,    -1,   114,    -1,   116,
      -1,   118,    -1,   120,   121,   122,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    -1,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    -1,    -1,    35,    36,
      37,    38,    39,    40,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    -1,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    -1,    -1,    35,    36,    37,    38,
      39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   112,    -1,   114,    -1,   116,
     117,   118,    -1,   120,   121,    -1,    85,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   112,    -1,   114,    -1,   116,    -1,   118,
      -1,   120,   121,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    -1,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    -1,    -1,    35,    36,    37,    38,    39,
      40,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    -1,    -1,    35,    36,    37,    38,    39,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   112,   113,   114,    -1,   116,    -1,   118,    -1,
     120,   121,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     112,    -1,   114,    -1,   116,    -1,   118,   119,   120,   121,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      -1,    -1,    35,    36,    37,    38,    39,    40,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    39,    40,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   112,
      -1,   114,    -1,   116,    -1,   118,   119,   120,   121,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   112,    -1,   114,
      -1,   116,    -1,   118,   119,   120,   121,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    -1,    -1,    35,
      36,    37,    38,    39,    40,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    -1,    -1,    35,    36,    37,
      38,    39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   112,   113,   114,    -1,
     116,    -1,   118,    -1,   120,   121,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   112,    -1,   114,    -1,   116,    -1,
     118,    -1,   120,   121,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    -1,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    -1,    -1,    -1,    -1,    35,    36,    37,    38,
      39,    40,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    -1,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,     1,
      -1,    -1,    -1,    -1,    35,    36,    37,    38,    39,    40,
      -1,    -1,    14,    15,    16,    17,    18,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       1,    -1,    -1,   112,    -1,   114,    -1,   116,    -1,   118,
      -1,   120,   121,    14,    15,    16,    17,    18,    60,    61,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    34,    -1,    -1,    -1,    -1,    80,     1,
      -1,   112,    -1,   114,    -1,   116,    88,   118,    90,   120,
     121,     1,    14,    15,    16,    17,    18,    -1,    -1,    60,
      61,    -1,    -1,    -1,    14,    15,    16,    17,    18,    -1,
      -1,    33,    34,    -1,   116,    -1,    -1,    -1,    -1,    80,
      -1,    -1,    -1,    33,    34,    -1,    -1,    88,     1,    90,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,
      -1,    14,    15,    16,    17,    18,    -1,    -1,    -1,    -1,
      60,    61,    -1,    -1,    -1,   116,    -1,    -1,    80,     1,
      33,    34,    -1,    -1,    -1,    -1,    88,    -1,    90,    -1,
      80,    -1,    14,    15,    16,    17,    18,    -1,    88,    -1,
      90,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    -1,
      -1,    33,    34,    -1,   116,    -1,     1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   116,    80,     1,    14,
      15,    16,    17,    18,    -1,    88,    -1,    90,    60,    61,
       1,    14,    15,    16,    17,    18,    -1,    -1,    33,    34,
      -1,    -1,    -1,    14,    15,    16,    17,    18,    80,    -1,
      33,    34,    -1,   116,    -1,    -1,    88,    -1,    90,    -1,
      -1,    -1,    33,    34,    -1,    60,    61,    -1,    14,    15,
      16,    17,    18,    -1,    -1,    -1,    -1,    60,    61,    -1,
      -1,    -1,    -1,    -1,   116,    80,    -1,    33,    34,    60,
      61,    -1,    -1,    88,    -1,    90,    -1,    80,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    90,    -1,    80,
      -1,    -1,    -1,    -1,    60,    61,    -1,    88,    -1,    90,
      -1,   116,    -1,    -1,    -1,    -1,    -1,    14,    15,    16,
      17,    18,    -1,   116,    80,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    88,    -1,    90,   116,    33,    34,    14,    15,
      16,    17,    18,    -1,    41,    42,    43,    44,    45,    46,
      47,    -1,    -1,    -1,    51,    -1,    -1,    33,    34,    -1,
     116,    -1,    -1,    60,    61,    -1,    -1,    -1,    -1,   125,
      14,    15,    16,    17,    18,    14,    15,    16,    17,    18,
      -1,    -1,    -1,    80,    60,    61,    -1,    -1,    -1,    33,
      34,    88,    -1,    90,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    80,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    88,    -1,    90,    -1,    60,    61,    -1,   116,
      -1,    60,    61,    -1,    -1,   122,    -1,   124,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    80,    -1,    -1,    -1,
     116,    80,   118,    -1,    88,    89,    90,    -1,   124,    88,
      -1,    90,    -1,    -1,    14,    15,    16,    17,    18,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   116,    33,    34,    -1,    -1,   116,    -1,    -1,
     124,    -1,    -1,    -1,    -1,   124,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      60,    61,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    -1,    -1,    -1,
      80,    -1,    35,    36,    37,    38,    39,    40,    88,    -1,
      90,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   116,    -1,    -1,    -1,
      -1,    -1,   122,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    -1,    14,    15,
      16,    17,    18,    35,    36,    37,    38,    39,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,   112,
      -1,   114,    -1,   116,    -1,   118,    -1,   120,   121,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    -1,    -1,    60,    61,    -1,    -1,    -1,    35,
      36,    37,    38,    39,    40,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    80,    25,    26,    27,    -1,    -1,
      -1,    -1,    88,    -1,    90,    35,    36,    37,    38,    39,
      40,    -1,   114,    -1,   116,    -1,   118,    -1,   120,   121,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    -1,
     116,    26,    27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    36,    37,    38,    39,    40,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   114,    -1,
     116,    -1,   118,    -1,   120,   121,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   114,    -1,   116,    -1,   118,    -1,
     120,   121,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    -1,    -1,    26,    27,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    36,    37,    38,    39,    40,    -1,   114,
      -1,   116,    -1,   118,    -1,   120,   121,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    -1,    -1,    26,    27,
      14,    15,    16,    17,    18,    -1,    -1,    35,    36,    -1,
      -1,    39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    -1,    60,    61,    -1,    -1,
      -1,    -1,    -1,   116,    -1,   118,    -1,   120,   121,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    80,    81,    82,    83,
      84,    -1,    86,    -1,    88,    -1,    90,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   116,    -1,
     118,    -1,   120,   121,    52,    53,    54,    55,    56,    -1,
      58,    59,   116,    -1,    62,    63,    64,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    73,    74,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    89
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned short int yystos[] =
{
       0,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   128,     1,   129,   140,   140,   173,   130,    52,
     132,   133,    56,    58,    59,    62,   146,   147,   159,   165,
      14,    15,    16,    17,    18,    33,    34,    60,    61,    80,
      88,    90,   116,   221,   226,   228,   221,   190,   221,   220,
     221,    88,    89,   160,   187,   230,   231,   231,   247,   130,
      57,   159,   243,   244,   245,   221,   251,   221,   259,   220,
     260,   261,   221,     0,   122,    54,    64,    73,    74,   130,
     141,   142,   143,   148,   156,   159,   169,   143,   148,   156,
      88,    88,   135,    53,   134,    59,   123,    88,   114,    55,
      89,   221,   221,   221,   116,     1,   221,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    35,    36,    37,    38,
      39,    40,   112,   114,   116,   118,   120,   121,   227,   221,
       1,    14,   112,   123,   113,   123,    57,    64,   130,   148,
     159,   232,   236,   232,    88,    88,   122,   123,   123,     1,
     123,   123,    81,    82,    83,    84,    86,   221,   262,   263,
       1,   159,   160,   124,   124,   132,   149,   150,   160,     1,
       3,    35,    37,   122,   135,    63,   136,   147,   155,    88,
     124,   118,   166,   160,   117,   117,   221,   221,   221,   221,
     221,   221,   221,   221,   221,   221,   221,   221,   221,   221,
     221,   224,   221,   221,   221,   221,   221,   221,   221,   221,
     222,   223,     1,   221,    88,   221,    14,   112,   221,   159,
     160,     1,   233,     1,   160,   132,   160,   155,   155,   244,
     245,    88,    88,   123,   221,   221,    85,   126,   221,   122,
     157,   158,   160,   118,   124,   167,   220,   220,   122,   123,
     116,   145,   155,   122,    88,     1,    88,     1,    88,   122,
       1,    88,   137,    75,   138,   118,   155,     1,   159,   161,
     162,     1,   221,   113,   221,   113,   221,   229,     1,   119,
     119,   113,   122,    88,   234,   235,   124,     1,   116,   124,
     242,   155,   155,   221,   122,   123,   155,    88,   168,   171,
     145,   125,   125,   150,     1,   117,   146,   124,     3,   151,
       1,   116,   122,     1,   122,   123,   124,     1,   221,   125,
     160,   163,   164,   125,   162,   119,   119,   123,   159,   221,
     117,   123,   117,   159,   155,   122,   123,   240,   124,     1,
     117,   243,   241,     1,   124,   158,   113,   119,   172,   173,
     124,   117,   117,   144,   124,   152,   221,   122,     1,   131,
     122,    88,   139,   119,   119,   155,   122,   123,   221,   117,
     221,   152,   235,   246,   247,   239,   117,   117,   246,   124,
     237,   159,   167,   125,     1,    65,   174,   170,   203,    88,
     152,   153,   154,   160,   117,   122,   229,   125,   221,   164,
     119,   225,   125,     1,    65,   248,   246,   125,   238,   246,
     122,     1,    88,   175,   176,   192,   172,   148,   156,   204,
     123,   125,   113,   122,   117,   113,   122,   221,   122,    88,
     249,   250,   192,   125,   246,   125,   122,   124,     1,   122,
     123,     1,    58,    66,    67,    78,    79,   177,   193,   194,
     195,   196,   125,     1,    41,    42,    43,    44,    45,    46,
      47,    51,   122,   124,   125,   201,   205,   221,   154,   152,
     122,   221,   124,   122,   123,   177,   125,     1,   221,   122,
     176,   122,     1,    88,   198,     1,    88,   197,    88,     1,
      88,   199,     1,    88,   200,    68,   178,   122,   116,   116,
     209,   122,   122,   116,   116,   122,   221,   202,   122,   122,
     251,   250,    68,   252,   125,   125,   122,     1,   122,   123,
     122,     1,   122,   123,   122,   122,     1,   122,   123,   122,
       1,   122,   123,     1,    88,   179,   180,     1,   160,   220,
       1,   208,   205,   220,   210,   122,   203,   125,     1,    88,
     253,   254,   122,    88,   122,    88,   122,    88,   122,    88,
     122,    76,    77,   122,   123,   117,   113,   122,   117,   220,
      42,   117,   220,   204,   122,    76,     1,   122,   123,    88,
      88,    76,    77,   180,   183,   205,   159,   220,   205,   117,
     116,   211,   117,   125,    88,   122,    76,   254,   256,   124,
     124,    88,    88,   117,   122,   205,   220,   124,   205,   124,
      88,   181,   182,   124,   124,   207,   220,   117,    49,    50,
     214,   215,    48,   212,   255,   124,    69,   186,   186,   184,
     185,   205,   117,   122,     1,   221,     1,   113,   125,   215,
     213,    70,   258,   257,   187,    70,   188,   188,   186,   186,
     206,   113,   113,   113,   218,   205,   259,    71,   189,   258,
     122,     1,   221,   189,   189,   188,   188,   205,   217,   216,
     219,   204,     1,   122,     1,   190,    72,   191,   189,   122,
       1,   122,   191,   191,   189,   189,   204,   204,   204,   122,
     122,     1,   122,     1,   220,   125,   191,   122,   125,   125,
     191,   191,   122,   122,   122,   125,   125,   125
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
#line 247 "parser.yy"
    { CALL(yylsp[0], yylsp[0], done()); }
    break;

  case 3:
#line 248 "parser.yy"
    { }
    break;

  case 4:
#line 249 "parser.yy"
    { }
    break;

  case 5:
#line 250 "parser.yy"
    { }
    break;

  case 6:
#line 251 "parser.yy"
    { }
    break;

  case 7:
#line 252 "parser.yy"
    { g_parameter_count = yyvsp[0].number; }
    break;

  case 8:
#line 253 "parser.yy"
    { }
    break;

  case 9:
#line 254 "parser.yy"
    { }
    break;

  case 10:
#line 255 "parser.yy"
    { CALL(yylsp[0], yylsp[0], procGuard()); }
    break;

  case 11:
#line 256 "parser.yy"
    { }
    break;

  case 12:
#line 257 "parser.yy"
    { CALL(yylsp[0], yylsp[0], procUpdate()); }
    break;

  case 13:
#line 258 "parser.yy"
    { CALL(yylsp[0], yylsp[0], done()); }
    break;

  case 14:
#line 259 "parser.yy"
    { }
    break;

  case 15:
#line 260 "parser.yy"
    { }
    break;

  case 16:
#line 261 "parser.yy"
    { }
    break;

  case 17:
#line 262 "parser.yy"
    { g_parameter_count = yyvsp[0].number; }
    break;

  case 18:
#line 263 "parser.yy"
    { }
    break;

  case 19:
#line 264 "parser.yy"
    { CALL(yylsp[0], yylsp[0], procGuard()); }
    break;

  case 20:
#line 265 "parser.yy"
    { CALL(yylsp[0], yylsp[0], procUpdate()); }
    break;

  case 21:
#line 266 "parser.yy"
    {}
    break;

  case 22:
#line 267 "parser.yy"
    {}
    break;

  case 25:
#line 276 "parser.yy"
    {
          CALL(yylsp[-3], yylsp[-1], instantiationBegin(yyvsp[-3].string, yyvsp[-1].string));
	}
    break;

  case 26:
#line 278 "parser.yy"
    {
	  CALL(yylsp[-7], yylsp[0], instantiationEnd(yyvsp[-7].string, yyvsp[-5].string, yyvsp[-2].number));
	}
    break;

  case 27:
#line 281 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_ARGLIST));
	}
    break;

  case 28:
#line 284 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));
	}
    break;

  case 29:
#line 287 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LPAREN));
	}
    break;

  case 30:
#line 290 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_ASSIGN));
	}
    break;

  case 36:
#line 308 "parser.yy"
    { CALL(yylsp[0], yylsp[0], lowPriority(yyvsp[0].string)); }
    break;

  case 37:
#line 309 "parser.yy"
    { CALL(yylsp[0], yylsp[0], samePriority(yyvsp[0].string)); }
    break;

  case 38:
#line 310 "parser.yy"
    { CALL(yylsp[0], yylsp[0], higherPriority(yyvsp[0].string)); }
    break;

  case 42:
#line 317 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 43:
#line 320 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_PROCID));
	}
    break;

  case 44:
#line 326 "parser.yy"
    { CALL(yylsp[0], yylsp[0], process(yyvsp[0].string)); }
    break;

  case 45:
#line 327 "parser.yy"
    { CALL(yylsp[0], yylsp[0], process(yyvsp[0].string)); }
    break;

  case 49:
#line 336 "parser.yy"
    {
            CALL(yylsp[-3], yylsp[-1], declProgress(true));
        }
    break;

  case 50:
#line 339 "parser.yy"
    {
            CALL(yylsp[-1], yylsp[-1], declProgress(false));
        }
    break;

  case 59:
#line 354 "parser.yy"
    { CALL(yylsp[-1], yylsp[-1], beforeUpdate()); }
    break;

  case 60:
#line 356 "parser.yy"
    { CALL(yylsp[-1], yylsp[-1], afterUpdate()); }
    break;

  case 61:
#line 363 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[-1], declFuncBegin(yyvsp[-2].string, yyvsp[-1].number));
	}
    break;

  case 62:
#line 365 "parser.yy"
    {
	  CALL(yylsp[-7], yylsp[0], declFuncEnd());
	}
    break;

  case 63:
#line 370 "parser.yy"
    { yyval.number = 0; }
    break;

  case 64:
#line 371 "parser.yy"
    { yyval.number = yyvsp[-1].number; }
    break;

  case 65:
#line 372 "parser.yy"
    { 
	  yyval.number = 0; 
	}
    break;

  case 66:
#line 378 "parser.yy"
    { yyval.number = 1; }
    break;

  case 67:
#line 379 "parser.yy"
    { yyval.number = yyvsp[-2].number+1; }
    break;

  case 68:
#line 383 "parser.yy"
    {
          CALL(yylsp[-3], yylsp[0], declParameter(yyvsp[-1].string, true, yyvsp[0].number));
          CALL(yylsp[-3], yylsp[0], declParameterEnd());
	}
    break;

  case 69:
#line 387 "parser.yy"
    {
          CALL(yylsp[-2], yylsp[0], declParameter(yyvsp[-1].string, false, yyvsp[0].number));
          CALL(yylsp[-2], yylsp[0], declParameterEnd());
	}
    break;

  case 70:
#line 394 "parser.yy"
    { 
          CALL(yylsp[-2], yylsp[0], declVarEnd());
	}
    break;

  case 73:
#line 405 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], declVar(yyvsp[-2].string, yyvsp[-1].number, yyvsp[0].flag));
	}
    break;

  case 74:
#line 411 "parser.yy"
    { yyval.flag = false; }
    break;

  case 75:
#line 412 "parser.yy"
    { yyval.flag = true; }
    break;

  case 77:
#line 417 "parser.yy"
    {	
	  CALL(yylsp[-2], yylsp[0], declInitialiserList(yyvsp[-1].number));
	}
    break;

  case 78:
#line 423 "parser.yy"
    { yyval.number = 1; }
    break;

  case 79:
#line 424 "parser.yy"
    { yyval.number = yyvsp[-2].number+1; }
    break;

  case 80:
#line 428 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], declFieldInit(yyvsp[-2].string));
	}
    break;

  case 81:
#line 431 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], declFieldInit(""));
	}
    break;

  case 82:
#line 437 "parser.yy"
    { yyval.number=0; }
    break;

  case 83:
#line 438 "parser.yy"
    { yyval.number=yyvsp[-3].number+1; }
    break;

  case 84:
#line 439 "parser.yy"
    {
	  CALL(yylsp[-1], yylsp[-1], exprNat(1));
	  REPORT_ERROR(last_loc, TypeException(PE_CONST_EXP));
	  yyval.number=yyvsp[-3].number+1; 
	}
    break;

  case 85:
#line 447 "parser.yy"
    {
	  CALL(yylsp[-3], yylsp[0], declTypeDefEnd());
	}
    break;

  case 86:
#line 450 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], declTypeDefEnd());  
	}
    break;

  case 87:
#line 456 "parser.yy"
    { yyval.number = 1; }
    break;

  case 88:
#line 457 "parser.yy"
    { yyval.number = yyvsp[-2].number+1; }
    break;

  case 89:
#line 461 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], declTypeDef(yyvsp[-1].string, yyvsp[0].number));
	}
    break;

  case 90:
#line 467 "parser.yy"
    { 
	    CALL((yyvsp[-2].number == ParserBuilder::PREFIX_NONE ? yylsp[-1] : yylsp[-2]), yylsp[0],
		 typeName(yyvsp[-2].number, yyvsp[-1].string, yyvsp[0].number));
	}
    break;

  case 91:
#line 471 "parser.yy"
    { 
	    CALL((yyvsp[-4].number == ParserBuilder::PREFIX_NONE ? yylsp[-3] : yylsp[-4]), yylsp[0],
	       typeStruct(yyvsp[-4].number, yyvsp[-1].number));
	}
    break;

  case 92:
#line 475 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBER));
	  CALL((yyvsp[-4].number == ParserBuilder::PREFIX_NONE ? yylsp[-3] : yylsp[-4]), yylsp[0],
	       typeStruct(yyvsp[-4].number, 0));
	}
    break;

  case 93:
#line 483 "parser.yy"
    { strncpy(yyval.string, yyvsp[0].string, MAXLEN); }
    break;

  case 94:
#line 484 "parser.yy"
    { strncpy(yyval.string, yyvsp[0].string, MAXLEN); }
    break;

  case 95:
#line 488 "parser.yy"
    { yyval.number=yyvsp[0].number; }
    break;

  case 96:
#line 489 "parser.yy"
    { yyval.number=yyvsp[-1].number+yyvsp[0].number; }
    break;

  case 97:
#line 493 "parser.yy"
    {
	  yyval.number = yyvsp[-1].number; 
	  CALL(yylsp[-2], yylsp[0], structFieldEnd());
	}
    break;

  case 98:
#line 500 "parser.yy"
    { yyval.number=1; }
    break;

  case 99:
#line 501 "parser.yy"
    { yyval.number=yyvsp[-2].number+1; }
    break;

  case 100:
#line 505 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], structField(yyvsp[-1].string, yyvsp[0].number));
	}
    break;

  case 101:
#line 511 "parser.yy"
    { yyval.number = ParserBuilder::PREFIX_NONE; }
    break;

  case 102:
#line 512 "parser.yy"
    { yyval.number = ParserBuilder::PREFIX_URGENT; }
    break;

  case 103:
#line 513 "parser.yy"
    { yyval.number = ParserBuilder::PREFIX_BROADCAST; }
    break;

  case 104:
#line 514 "parser.yy"
    { yyval.number = ParserBuilder::PREFIX_URGENT_BROADCAST; }
    break;

  case 105:
#line 515 "parser.yy"
    { yyval.number = ParserBuilder::PREFIX_CONST; }
    break;

  case 106:
#line 516 "parser.yy"
    { yyval.number = ParserBuilder::PREFIX_META; }
    break;

  case 107:
#line 520 "parser.yy"
    { yyval.number = 0; }
    break;

  case 108:
#line 521 "parser.yy"
    { yyval.number = 1; }
    break;

  case 109:
#line 522 "parser.yy"
    { yyval.number = 2; }
    break;

  case 110:
#line 523 "parser.yy"
    {
	    yyval.number = 0;
        }
    break;

  case 111:
#line 533 "parser.yy"
    { yyval.number = 0; }
    break;

  case 112:
#line 534 "parser.yy"
    { yyval.number = yyvsp[0].number + 1; }
    break;

  case 113:
#line 537 "parser.yy"
    { 
	    CALL(yylsp[-2], yylsp[0], procTemplateSet(yyvsp[-2].string)); 
	}
    break;

  case 114:
#line 542 "parser.yy"
    { 
	  CALL(yylsp[-4], yylsp[-1], procBegin(yyvsp[-3].string, 0, yyvsp[-2].number));
	}
    break;

  case 115:
#line 545 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;

  case 116:
#line 548 "parser.yy"
    {
	  utap_error(TypeException(PE_LPAREN), 
		     yylsp[0].first_line, yylsp[0].first_column, 
		     yylsp[0].last_line, yylsp[0].last_column);
	  CALL(yylsp[-2], yylsp[0], procBegin(yyvsp[-1].string, 0, 0));
	}
    break;

  case 117:
#line 553 "parser.yy"
    {
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;

  case 124:
#line 571 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 125:
#line 574 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATE_DECL));
	}
    break;

  case 129:
#line 586 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], procState(yyvsp[0].string, false));
	}
    break;

  case 130:
#line 589 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[0], procState(yyvsp[-3].string, true));
	}
    break;

  case 131:
#line 592 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_INV));
	  CALL(yylsp[-3], yylsp[0], procState(yyvsp[-3].string, false));
	}
    break;

  case 132:
#line 599 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], procStateInit(yyvsp[-1].string));
	}
    break;

  case 136:
#line 608 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 139:
#line 619 "parser.yy"
    {
	    CALL(yylsp[-3], yylsp[-1], procEdgeBegin(yyvsp[-3].string, yyvsp[-1].string, true));
	}
    break;

  case 140:
#line 621 "parser.yy"
    { 
	  strcpy(rootTransId, yyvsp[-9].string); 
	  CALL(yylsp[-9], yylsp[-2], procEdgeEnd(yyvsp[-9].string, yyvsp[-7].string));
	}
    break;

  case 141:
#line 625 "parser.yy"
    {
	    CALL(yylsp[-3], yylsp[-1], procEdgeBegin(yyvsp[-3].string, yyvsp[-1].string, false));
	}
    break;

  case 142:
#line 627 "parser.yy"
    { 
	  strcpy(rootTransId, yyvsp[-9].string); 
	  CALL(yylsp[-9], yylsp[-2], procEdgeEnd(yyvsp[-9].string, yyvsp[-7].string));
	}
    break;

  case 143:
#line 634 "parser.yy"
    { 
	    CALL(yylsp[-2], yylsp[-1], procEdgeBegin(rootTransId, yyvsp[-1].string, true)); 
        }
    break;

  case 144:
#line 636 "parser.yy"
    { 
	    CALL(yylsp[-8], yylsp[-2], procEdgeEnd(rootTransId, yyvsp[-7].string));
	}
    break;

  case 145:
#line 639 "parser.yy"
    { 
	    CALL(yylsp[-2], yylsp[-1], procEdgeBegin(rootTransId, yyvsp[-1].string, false)); 
        }
    break;

  case 146:
#line 641 "parser.yy"
    { 
	    CALL(yylsp[-8], yylsp[-2], procEdgeEnd(rootTransId, yyvsp[-7].string));
	}
    break;

  case 150:
#line 653 "parser.yy"
    {
	    CALL(yylsp[-2], yylsp[0], procSelect(yyvsp[-2].string));
	}
    break;

  case 151:
#line 656 "parser.yy"
    {
	    CALL(yylsp[-2], yylsp[0], procSelect(yyvsp[-2].string));
	}
    break;

  case 153:
#line 662 "parser.yy"
    {
	  CALL(yylsp[-1], yylsp[-1], procGuard());
        }
    break;

  case 154:
#line 665 "parser.yy"
    {
	  REPORT_ERROR(yylloc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-2], yylsp[-1], procGuard());
	}
    break;

  case 155:
#line 669 "parser.yy"
    {
	  REPORT_ERROR(yylloc, TypeException(PE_GUARD_EXP));
	}
    break;

  case 158:
#line 677 "parser.yy"
    {
	  REPORT_ERROR(yylloc, TypeException(PE_SEMICOLON));
	}
    break;

  case 159:
#line 680 "parser.yy"
    {
	  REPORT_ERROR(yylloc, TypeException(PE_SYNC_EXP));
	}
    break;

  case 160:
#line 686 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], procSync(SYNC_BANG));
	}
    break;

  case 161:
#line 689 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_BANG));
	  CALL(yylsp[-2], yylsp[-1], procSync(SYNC_QUE));
	}
    break;

  case 162:
#line 693 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], procSync(SYNC_QUE));
	}
    break;

  case 163:
#line 696 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_QUE));
	  CALL(yylsp[-2], yylsp[-1], procSync(SYNC_QUE));
	}
    break;

  case 165:
#line 704 "parser.yy"
    {
	  CALL(yylsp[-1], yylsp[-1], procUpdate());	  
	}
    break;

  case 166:
#line 707 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_ASSIGN_EXP));
	}
    break;

  case 173:
#line 722 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 174:
#line 725 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;

  case 175:
#line 731 "parser.yy"
    {}
    break;

  case 176:
#line 732 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 177:
#line 735 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;

  case 179:
#line 742 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 180:
#line 745 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;

  case 182:
#line 752 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 183:
#line 755 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;

  case 184:
#line 761 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], procStateCommit(yyvsp[0].string));
	}
    break;

  case 185:
#line 764 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], procStateCommit(yyvsp[0].string));
	}
    break;

  case 186:
#line 770 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], procStateUrgent(yyvsp[0].string));
	}
    break;

  case 187:
#line 773 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], procStateUrgent(yyvsp[0].string));
	}
    break;

  case 188:
#line 779 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], procStateWinning(yyvsp[0].string));
	}
    break;

  case 189:
#line 782 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], procStateWinning(yyvsp[0].string));
	}
    break;

  case 190:
#line 788 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], procStateLosing(yyvsp[0].string));
	}
    break;

  case 191:
#line 791 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], procStateLosing(yyvsp[0].string));
	}
    break;

  case 192:
#line 802 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], blockBegin());
	}
    break;

  case 193:
#line 805 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[-1], blockEnd());
	}
    break;

  case 201:
#line 824 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], emptyStatement());
	}
    break;

  case 202:
#line 827 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], exprStatement());
	}
    break;

  case 203:
#line 830 "parser.yy"
    { 
	  CALL(yylsp[-7], yylsp[0], forBegin());
	}
    break;

  case 204:
#line 833 "parser.yy"
    { 
	    CALL(yylsp[-1], yylsp[-1], forEnd());
	}
    break;

  case 205:
#line 836 "parser.yy"
    { 
	    CALL(yylsp[-5], yylsp[0], iterationBegin(yyvsp[-3].string));
	}
    break;

  case 206:
#line 839 "parser.yy"
    { 
	    CALL(yylsp[-1], yylsp[-1], iterationEnd(yyvsp[-5].string));
	}
    break;

  case 208:
#line 843 "parser.yy"
    {
	    CALL(yylsp[-1], yylsp[0], whileBegin());
	}
    break;

  case 209:
#line 846 "parser.yy"
    { 
	    CALL(yylsp[-3], yylsp[-2], whileEnd());
	  }
    break;

  case 211:
#line 850 "parser.yy"
    { 
	    CALL(yylsp[0], yylsp[0], doWhileBegin());
	}
    break;

  case 212:
#line 853 "parser.yy"
    { 
	    CALL(yylsp[-6], yylsp[-1], doWhileEnd());
	  }
    break;

  case 213:
#line 856 "parser.yy"
    { 
	    CALL(yylsp[-1], yylsp[0], ifBegin());
	}
    break;

  case 215:
#line 860 "parser.yy"
    { 
	    CALL(yylsp[-1], yylsp[0], breakStatement());
	  }
    break;

  case 216:
#line 863 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], continueStatement());
	}
    break;

  case 217:
#line 866 "parser.yy"
    { 
	    CALL(yylsp[-3], yylsp[0], switchBegin());
	}
    break;

  case 218:
#line 869 "parser.yy"
    { 
	       CALL(yylsp[-3], yylsp[-1], switchEnd());
	   }
    break;

  case 219:
#line 872 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], returnStatement(true));
	}
    break;

  case 220:
#line 875 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], returnStatement(false));
	}
    break;

  case 221:
#line 881 "parser.yy"
    { 
	  CALL(position_t(), position_t(), ifEnd(false));
	}
    break;

  case 222:
#line 884 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], ifElse());
	}
    break;

  case 223:
#line 887 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[-1], ifEnd(true));
	  }
    break;

  case 226:
#line 898 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], caseBegin());
	}
    break;

  case 227:
#line 901 "parser.yy"
    { 
	    CALL(yylsp[-1], yylsp[-1], caseEnd());
	  }
    break;

  case 228:
#line 904 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], caseBegin());
	}
    break;

  case 229:
#line 907 "parser.yy"
    {
	    REPORT_ERROR(last_loc, TypeException(PE_EXPR)); 
	    CALL(yylsp[-1], yylsp[-1], caseEnd());
	  }
    break;

  case 230:
#line 911 "parser.yy"
    { 
	    CALL(yylsp[-1], yylsp[0], defaultBegin());
	}
    break;

  case 231:
#line 914 "parser.yy"
    { 
	    CALL(yylsp[-1], yylsp[-1], defaultEnd());
	  }
    break;

  case 232:
#line 917 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_COLON)); 
	  CALL(yylsp[-2], yylsp[0], defaultBegin());
	}
    break;

  case 233:
#line 921 "parser.yy"
    { 
	    CALL(yylsp[-1], yylsp[-1], defaultEnd());
	  }
    break;

  case 235:
#line 928 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprComma());
	}
    break;

  case 236:
#line 933 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], exprFalse());
	}
    break;

  case 237:
#line 936 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], exprTrue());
	}
    break;

  case 238:
#line 939 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], exprNat(yyvsp[0].number));
	}
    break;

  case 239:
#line 942 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], exprId(yyvsp[0].string));
	}
    break;

  case 240:
#line 945 "parser.yy"
    {
	    CALL(yylsp[-1], yylsp[0], exprCallBegin());	    
	  }
    break;

  case 241:
#line 947 "parser.yy"
    { 
	    CALL(yylsp[-4], yylsp[0], exprCallEnd(yyvsp[-1].number));
	}
    break;

  case 242:
#line 950 "parser.yy"
    {
	    CALL(yylsp[-1], yylsp[0], exprCallBegin());
	  }
    break;

  case 243:
#line 952 "parser.yy"
    {   
	    REPORT_ERROR(last_loc, TypeException(PE_ARGLIST));
	    CALL(yylsp[-4], yylsp[0], exprCallEnd(0));
	}
    break;

  case 244:
#line 956 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[0], exprArray());
	}
    break;

  case 245:
#line 959 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-3], yylsp[0], exprFalse());
	}
    break;

  case 247:
#line 964 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprFalse());
	}
    break;

  case 248:
#line 968 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], exprPostIncrement());
	}
    break;

  case 249:
#line 971 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], exprPreIncrement());
	}
    break;

  case 250:
#line 974 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], exprPostDecrement());
	}
    break;

  case 251:
#line 977 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], exprPreDecrement());
	}
    break;

  case 252:
#line 980 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], exprUnary(yyvsp[-1].kind));
	}
    break;

  case 253:
#line 983 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(LT));
	}
    break;

  case 254:
#line 986 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(LE));
	}
    break;

  case 255:
#line 989 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(EQ));
	}
    break;

  case 256:
#line 992 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(NEQ));
	}
    break;

  case 257:
#line 995 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(GT));
	}
    break;

  case 258:
#line 998 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(GE));
	}
    break;

  case 259:
#line 1001 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(PLUS));
	}
    break;

  case 260:
#line 1004 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(MINUS));
	}
    break;

  case 261:
#line 1007 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(MULT));
	}
    break;

  case 262:
#line 1010 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(DIV));
	}
    break;

  case 263:
#line 1013 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(MOD));
	}
    break;

  case 264:
#line 1016 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_AND));
	}
    break;

  case 265:
#line 1019 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_OR));
	}
    break;

  case 266:
#line 1022 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_XOR));
	}
    break;

  case 267:
#line 1025 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_LSHIFT));
	}
    break;

  case 268:
#line 1028 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_RSHIFT));
	}
    break;

  case 269:
#line 1031 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(AND));
	}
    break;

  case 270:
#line 1034 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(OR));
	}
    break;

  case 271:
#line 1037 "parser.yy"
    { 
	  CALL(yylsp[-4], yylsp[0], exprInlineIf());
	}
    break;

  case 272:
#line 1040 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprDot(yyvsp[0].string));
	}
    break;

  case 273:
#line 1043 "parser.yy"
    {
	    CALL(yylsp[-1], yylsp[0], exprUnary(RATE));
        }
    break;

  case 274:
#line 1046 "parser.yy"
    {
	  CALL(yylsp[0], yylsp[0], exprDeadlock());
	}
    break;

  case 275:
#line 1049 "parser.yy"
    {  
	  CALL(yylsp[-1], yylsp[-1], exprUnary(NOT));
	}
    break;

  case 276:
#line 1051 "parser.yy"
    {
	  CALL(yylsp[-1], yylsp[-1], exprBinary(OR));
	}
    break;

  case 277:
#line 1054 "parser.yy"
    {
	  CALL(yylsp[-2], yylsp[0], exprBinary(AND));
        }
    break;

  case 278:
#line 1057 "parser.yy"
    {
	  CALL(yylsp[-2], yylsp[0], exprBinary(OR));
        }
    break;

  case 279:
#line 1060 "parser.yy"
    {
	  CALL(yylsp[-1], yylsp[0], exprUnary(NOT));
        }
    break;

  case 280:
#line 1063 "parser.yy"
    {
	    CALL(yylsp[-2], yylsp[0], exprBinary(MIN));
        }
    break;

  case 281:
#line 1066 "parser.yy"
    {
	    CALL(yylsp[-2], yylsp[0], exprBinary(MAX));
        }
    break;

  case 282:
#line 1069 "parser.yy"
    {
	    CALL(yylsp[-5], yylsp[0], exprForAllBegin(yyvsp[-3].string));
        }
    break;

  case 283:
#line 1071 "parser.yy"
    {
	    CALL(yylsp[0], yylsp[0], exprForAllEnd(yyvsp[-5].string));
        }
    break;

  case 285:
#line 1078 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprAssignment(yyvsp[-1].kind));
	}
    break;

  case 286:
#line 1084 "parser.yy"
    { yyval.kind = ASSIGN; }
    break;

  case 287:
#line 1085 "parser.yy"
    { yyval.kind = ASSPLUS; }
    break;

  case 288:
#line 1086 "parser.yy"
    { yyval.kind = ASSMINUS; }
    break;

  case 289:
#line 1087 "parser.yy"
    { yyval.kind = ASSDIV; }
    break;

  case 290:
#line 1088 "parser.yy"
    { yyval.kind = ASSMOD; }
    break;

  case 291:
#line 1089 "parser.yy"
    { yyval.kind = ASSMULT; }
    break;

  case 292:
#line 1090 "parser.yy"
    { yyval.kind = ASSAND; }
    break;

  case 293:
#line 1091 "parser.yy"
    { yyval.kind = ASSOR; }
    break;

  case 294:
#line 1092 "parser.yy"
    { yyval.kind = ASSXOR; }
    break;

  case 295:
#line 1093 "parser.yy"
    { yyval.kind = ASSLSHIFT; }
    break;

  case 296:
#line 1094 "parser.yy"
    { yyval.kind = ASSRSHIFT; }
    break;

  case 297:
#line 1099 "parser.yy"
    { yyval.kind = MINUS; }
    break;

  case 298:
#line 1100 "parser.yy"
    { yyval.kind = PLUS; }
    break;

  case 299:
#line 1101 "parser.yy"
    { yyval.kind = NOT; }
    break;

  case 300:
#line 1106 "parser.yy"
    { yyval.number=0; }
    break;

  case 301:
#line 1107 "parser.yy"
    { 
	    yyval.number = 1; 
	    CALL(yylsp[0], yylsp[0], exprArg(0));
	}
    break;

  case 302:
#line 1111 "parser.yy"
    { 
	    yyval.number = yyvsp[-2].number + 1; 
	    CALL(yylsp[0], yylsp[0], exprArg(yyvsp[-2].number));
	}
    break;

  case 308:
#line 1133 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], typeName(ParserBuilder::PREFIX_CONST, "int", 0));
	}
    break;

  case 309:
#line 1135 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[-1], declVarEnd());
	}
    break;

  case 311:
#line 1141 "parser.yy"
    { yyval.number=1; }
    break;

  case 312:
#line 1142 "parser.yy"
    { yyval.number=yyvsp[-2].number+1; }
    break;

  case 313:
#line 1146 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], declVar(yyvsp[-2].string, yyvsp[-1].number, true));
	}
    break;

  case 314:
#line 1155 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[0], procBegin(yyvsp[-2].string, 0, yyvsp[-1].number));
	}
    break;

  case 315:
#line 1158 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;

  case 316:
#line 1161 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	  CALL(yylsp[-4], yylsp[0], procBegin(yyvsp[-3].string, 0, yyvsp[-2].number));
	}
    break;

  case 317:
#line 1165 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;

  case 318:
#line 1168 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACES));
	  CALL(yylsp[-3], yylsp[0], procBegin(yyvsp[-2].string, 0, 0));
	}
    break;

  case 319:
#line 1172 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;

  case 320:
#line 1175 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_PROCID));
	  CALL(yylsp[-2], yylsp[0], procBegin("_", 0, 0));
	}
    break;

  case 321:
#line 1179 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;

  case 322:
#line 1182 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], procBegin(yyvsp[-1].string, 0, 0));
	}
    break;

  case 323:
#line 1185 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;

  case 324:
#line 1191 "parser.yy"
    { yyval.number = 0; }
    break;

  case 325:
#line 1192 "parser.yy"
    { yyval.number = yyvsp[-1].number; }
    break;

  case 326:
#line 1193 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_PARAMETERS));	  
	  yyval.number = 0; 
	}
    break;

  case 327:
#line 1200 "parser.yy"
    { 
	  yyval.number = yyvsp[0].number; 
	  CALL(yylsp[0], yylsp[0], declParameterEnd());
	}
    break;

  case 328:
#line 1204 "parser.yy"
    {
	  yyval.number = yyvsp[0].number;
	  CALL(yylsp[0], yylsp[0], declParameterEnd());
        }
    break;

  case 329:
#line 1208 "parser.yy"
    { 
	  yyval.number = yyvsp[-2].number + yyvsp[0].number;
	  CALL(yylsp[-2], yylsp[0], declParameterEnd());
	}
    break;

  case 330:
#line 1212 "parser.yy"
    { 
	  yyval.number = yyvsp[-2].number + yyvsp[0].number;
	  CALL(yylsp[-2], yylsp[0], declParameterEnd());
	}
    break;

  case 331:
#line 1219 "parser.yy"
    {
          CALL(yylsp[-2], yylsp[0], declParameter(yyvsp[-1].string, yyvsp[0].number == 0, yyvsp[0].number));
	  yyval.number = 1;
	}
    break;

  case 332:
#line 1223 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[0], declParameter(yyvsp[-1].string, yyvsp[0].number == 0, yyvsp[0].number));
	  yyval.number = yyvsp[-3].number + 1;
	}
    break;

  case 333:
#line 1230 "parser.yy"
    {
	  CALL(yylsp[-2], yylsp[-2], typeName(ParserBuilder::PREFIX_CONST, "int", false));
	  CALL(yylsp[-1], yylsp[0], declParameter(yyvsp[-1].string, false, yyvsp[0].number));
	  yyval.number = 1;
	}
    break;

  case 334:
#line 1235 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[0], declParameter(yyvsp[-1].string, false, yyvsp[0].number));
	  yyval.number = yyvsp[-3].number + 1;
	}
    break;

  case 342:
#line 1261 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], exprTrue(); ch->procState(yyvsp[0].string, false));
	}
    break;

  case 343:
#line 1264 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[0], procState(yyvsp[-3].string, true));
	}
    break;

  case 345:
#line 1271 "parser.yy"
    {	  
	  REPORT_ERROR(last_loc, TypeException(PE_INV));
	}
    break;

  case 346:
#line 1274 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(AND));
	}
    break;

  case 349:
#line 1282 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 350:
#line 1285 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS_DECL));
	}
    break;

  case 353:
#line 1296 "parser.yy"
    {
	    CALL(yylsp[-3], yylsp[-1], procEdgeBegin(yyvsp[-3].string, yyvsp[-1].string, true));
	}
    break;

  case 354:
#line 1298 "parser.yy"
    { 
	    strcpy(rootTransId, yyvsp[-8].string);
	    CALL(yylsp[-8], yylsp[-1], procEdgeEnd(yyvsp[-8].string, yyvsp[-6].string));
	}
    break;

  case 355:
#line 1306 "parser.yy"
    {
	    CALL(yylsp[-2], yylsp[-1], procEdgeBegin(rootTransId, yyvsp[-1].string, true));
	}
    break;

  case 356:
#line 1308 "parser.yy"
    { 
	    CALL(yylsp[-7], yylsp[-1], procEdgeEnd(rootTransId, yyvsp[-6].string));
	}
    break;

  case 359:
#line 1316 "parser.yy"
    {
	  CALL(yylsp[-1], yylsp[-1], procGuard());
	}
    break;

  case 360:
#line 1319 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-2], yylsp[-1], procGuard());
	}
    break;

  case 362:
#line 1327 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(AND));
	}
    break;

  case 367:
#line 1341 "parser.yy"
    {
		ch->quit();	
	}
    break;

  case 368:
#line 1344 "parser.yy"
    {
		ch->property(yyvsp[-1].kind, yylsp[-1].first_line);
	}
    break;

  case 369:
#line 1347 "parser.yy"
    {
		ch->property(LEADSTO, yylsp[-2].first_line);
	}
    break;

  case 370:
#line 1352 "parser.yy"
    { yyval.kind = EF; }
    break;

  case 371:
#line 1353 "parser.yy"
    { yyval.kind = EG; }
    break;

  case 372:
#line 1354 "parser.yy"
    { yyval.kind = AF; }
    break;

  case 373:
#line 1355 "parser.yy"
    { yyval.kind = AG; }
    break;


    }

/* Line 1010 of yacc.c.  */
#line 4394 "parser.tab.c"

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


#line 1357 "parser.yy"


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


