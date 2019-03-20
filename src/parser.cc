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
     T_TYPEDEF = 306,
     T_STRUCT = 307,
     T_CONST = 308,
     T_OLDCONST = 309,
     T_URGENT = 310,
     T_BROADCAST = 311,
     T_TRUE = 312,
     T_FALSE = 313,
     T_SYSTEM = 314,
     T_PROCESS = 315,
     T_STATE = 316,
     T_COMMIT = 317,
     T_INIT = 318,
     T_TRANS = 319,
     T_ARROW = 320,
     T_GUARD = 321,
     T_SYNC = 322,
     T_ASSIGN = 323,
     T_RATE = 324,
     T_BEFORE = 325,
     T_AFTER = 326,
     T_COST = 327,
     T_DEADLOCK = 328,
     T_EF = 329,
     T_EG = 330,
     T_AF = 331,
     T_AG = 332,
     T_LEADSTO = 333,
     T_QUIT = 334,
     T_ERROR = 335,
     T_ID = 336,
     T_TYPENAME = 337,
     T_NAT = 338,
     T_NEW = 339,
     T_NEW_DECLARATION = 340,
     T_NEW_LOCAL_DECL = 341,
     T_NEW_INST = 342,
     T_NEW_SYSTEM = 343,
     T_NEW_PARAMETERS = 344,
     T_NEW_INVARIANT = 345,
     T_NEW_GUARD = 346,
     T_NEW_SYNC = 347,
     T_NEW_ASSIGN = 348,
     T_OLD = 349,
     T_OLD_DECLARATION = 350,
     T_OLD_LOCAL_DECL = 351,
     T_OLD_INST = 352,
     T_OLD_PARAMETERS = 353,
     T_OLD_INVARIANT = 354,
     T_OLD_GUARD = 355,
     T_OLD_ASSIGN = 356,
     T_PROPERTY = 357,
     UOPERATOR = 358
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
#define T_TYPEDEF 306
#define T_STRUCT 307
#define T_CONST 308
#define T_OLDCONST 309
#define T_URGENT 310
#define T_BROADCAST 311
#define T_TRUE 312
#define T_FALSE 313
#define T_SYSTEM 314
#define T_PROCESS 315
#define T_STATE 316
#define T_COMMIT 317
#define T_INIT 318
#define T_TRANS 319
#define T_ARROW 320
#define T_GUARD 321
#define T_SYNC 322
#define T_ASSIGN 323
#define T_RATE 324
#define T_BEFORE 325
#define T_AFTER 326
#define T_COST 327
#define T_DEADLOCK 328
#define T_EF 329
#define T_EG 330
#define T_AF 331
#define T_AG 332
#define T_LEADSTO 333
#define T_QUIT 334
#define T_ERROR 335
#define T_ID 336
#define T_TYPENAME 337
#define T_NAT 338
#define T_NEW 339
#define T_NEW_DECLARATION 340
#define T_NEW_LOCAL_DECL 341
#define T_NEW_INST 342
#define T_NEW_SYSTEM 343
#define T_NEW_PARAMETERS 344
#define T_NEW_INVARIANT 345
#define T_NEW_GUARD 346
#define T_NEW_SYNC 347
#define T_NEW_ASSIGN 348
#define T_OLD 349
#define T_OLD_DECLARATION 350
#define T_OLD_LOCAL_DECL 351
#define T_OLD_INST 352
#define T_OLD_PARAMETERS 353
#define T_OLD_INVARIANT 354
#define T_OLD_GUARD 355
#define T_OLD_ASSIGN 356
#define T_PROPERTY 357
#define UOPERATOR 358




/* Copy the first part of user declarations.  */
#line 53 "parser.yy"


#include "libparser.hh"

using namespace std;
using namespace UTAP;
using namespace Constants;

struct Position
{
    int32_t first_line, first_column, last_line, last_column;
    char *text;   // Unused - needed for compatibility with bison 1.28
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
#line 253 "parser.yy"
typedef union YYSTYPE {
    bool flag;
    int number;
    kind_t kind;
    char string[MAXLEN];
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 421 "parser.tab.c"
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
#line 445 "parser.tab.c"

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
#define YYFINAL  74
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2904

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  117
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  122
/* YYNRULES -- Number of rules. */
#define YYNRULES  416
/* YYNRULES -- Number of states. */
#define YYNSTATES  753

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   358

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     116,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   105,     2,
     107,   108,     2,     2,   113,     2,   111,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   104,   112,
       2,     2,     2,   103,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   109,     2,   110,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   114,     2,   115,     2,     2,     2,     2,
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
      95,    96,    97,    98,    99,   100,   101,   102,   106
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
     141,   144,   147,   150,   153,   158,   159,   163,   167,   172,
     177,   178,   182,   183,   187,   188,   197,   203,   206,   210,
     215,   219,   223,   226,   228,   232,   236,   241,   245,   248,
     252,   257,   261,   263,   267,   271,   272,   275,   277,   281,
     283,   287,   291,   295,   297,   298,   303,   309,   314,   319,
     323,   328,   334,   339,   343,   345,   349,   353,   356,   360,
     366,   372,   377,   381,   383,   385,   387,   390,   393,   397,
     402,   406,   409,   412,   414,   418,   422,   425,   426,   428,
     430,   433,   435,   436,   442,   449,   455,   459,   460,   468,
     476,   477,   484,   490,   496,   497,   500,   503,   506,   510,
     515,   519,   523,   526,   529,   531,   535,   539,   541,   546,
     552,   557,   562,   566,   570,   575,   579,   582,   584,   585,
     589,   594,   598,   601,   603,   605,   609,   613,   622,   632,
     638,   643,   647,   655,   664,   669,   673,   675,   676,   680,
     685,   689,   690,   694,   699,   703,   707,   710,   714,   717,
     721,   724,   725,   729,   733,   734,   736,   738,   741,   745,
     750,   754,   758,   761,   765,   770,   774,   778,   781,   783,
     787,   791,   793,   797,   801,   802,   808,   809,   812,   815,
     816,   819,   823,   825,   827,   830,   831,   842,   848,   849,
     856,   862,   863,   872,   873,   881,   884,   887,   888,   897,
     901,   904,   905,   906,   910,   911,   915,   917,   920,   921,
     927,   928,   934,   935,   940,   941,   947,   948,   950,   952,
     956,   958,   960,   962,   964,   965,   971,   972,   978,   983,
     988,   992,   996,   999,  1002,  1005,  1008,  1011,  1015,  1019,
    1023,  1027,  1031,  1035,  1039,  1043,  1047,  1051,  1055,  1059,
    1063,  1067,  1071,  1075,  1079,  1083,  1089,  1093,  1095,  1096,
    1101,  1105,  1109,  1112,  1116,  1120,  1122,  1126,  1128,  1130,
    1132,  1134,  1136,  1138,  1140,  1142,  1144,  1146,  1148,  1150,
    1152,  1154,  1155,  1157,  1161,  1165,  1169,  1170,  1173,  1176,
    1178,  1179,  1184,  1188,  1190,  1194,  1198,  1199,  1207,  1208,
    1217,  1218,  1226,  1227,  1234,  1235,  1242,  1245,  1249,  1253,
    1257,  1259,  1261,  1265,  1269,  1273,  1278,  1282,  1287,  1293,
    1294,  1297,  1301,  1306,  1310,  1314,  1317,  1319,  1321,  1325,
    1329,  1331,  1336,  1338,  1342,  1344,  1348,  1349,  1353,  1358,
    1362,  1366,  1369,  1371,  1373,  1377,  1381,  1390,  1400,  1409,
    1419,  1429,  1437,  1445,  1454,  1463,  1472,  1480,  1482,  1483,
    1487,  1492,  1496,  1499,  1501,  1505,  1509,  1512,  1513,  1517,
    1518,  1520,  1523,  1527,  1529,  1531,  1533
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short yyrhs[] =
{
     118,     0,    -1,    84,   119,    -1,    85,   124,    -1,    86,
     160,    -1,    87,   120,    -1,    88,   122,    -1,    88,     1,
      -1,    89,   135,    -1,    90,   199,    -1,    91,   199,    -1,
      92,   171,    -1,    93,   198,    -1,    94,   207,    -1,    95,
     208,    -1,    96,   224,    -1,    97,   120,    -1,    98,   220,
      -1,    99,   228,    -1,   100,   234,    -1,   101,   198,    -1,
     102,   235,    -1,   124,   120,   122,    -1,    -1,    -1,   120,
      81,     3,    81,   107,   121,   206,   108,   112,    -1,   120,
      81,     3,    81,   107,     1,   108,   112,    -1,   120,    81,
       3,    81,   107,     1,   112,    -1,   120,    81,     3,    81,
       1,   112,    -1,   120,    81,     1,   112,    -1,    59,   123,
     112,    -1,    59,   123,     1,   112,    -1,    59,     1,   112,
      -1,    81,    -1,   123,   113,    81,    -1,   123,   113,     1,
      -1,    -1,   124,   132,    -1,   124,   137,    -1,   124,   145,
      -1,   124,   156,    -1,   124,   125,    -1,   124,   128,    -1,
     124,   129,    -1,    69,   114,   126,   115,    -1,    -1,   126,
     127,   112,    -1,    72,   104,   199,    -1,    70,   114,   130,
     115,    -1,    71,   114,   131,   115,    -1,    -1,   130,   203,
     112,    -1,    -1,   131,   203,   112,    -1,    -1,   148,   149,
     134,   133,   114,   180,   181,   115,    -1,   148,   149,   134,
       1,   115,    -1,   107,   108,    -1,   107,   135,   108,    -1,
     107,   135,     1,   108,    -1,   107,   135,     1,    -1,   107,
       1,   108,    -1,   107,     1,    -1,   136,    -1,   135,   113,
     136,    -1,   135,   113,     1,    -1,   148,   105,    81,   144,
      -1,   148,    81,   144,    -1,   148,     1,    -1,   148,   138,
     112,    -1,   148,   138,     1,   112,    -1,   148,     1,   112,
      -1,   139,    -1,   138,   113,   139,    -1,   149,   144,   140,
      -1,    -1,     3,   141,    -1,   199,    -1,   114,   142,   115,
      -1,   143,    -1,   142,   113,   143,    -1,   149,   104,   141,
      -1,   149,   104,     1,    -1,   141,    -1,    -1,   144,   109,
     199,   110,    -1,   144,   109,   199,     1,   110,    -1,   144,
     109,   199,     1,    -1,   144,   109,     1,   110,    -1,   144,
     109,     1,    -1,    51,   148,   146,   112,    -1,    51,   148,
     146,     1,   112,    -1,    51,   148,     1,   112,    -1,    51,
       1,   112,    -1,   147,    -1,   146,   113,   147,    -1,   146,
     113,     1,    -1,   149,   144,    -1,   154,    82,   155,    -1,
     154,    52,   114,   150,   115,    -1,   154,    52,   114,     1,
     115,    -1,   154,    52,   114,     1,    -1,   154,    52,     1,
      -1,    81,    -1,    82,    -1,   151,    -1,   150,   151,    -1,
     150,     1,    -1,   148,   152,   112,    -1,   148,   152,     1,
     112,    -1,   148,     1,   112,    -1,   148,     1,    -1,     1,
     112,    -1,   153,    -1,   152,   113,   153,    -1,   152,   113,
       1,    -1,   149,   144,    -1,    -1,    55,    -1,    56,    -1,
      55,    56,    -1,    53,    -1,    -1,   109,   199,   113,   199,
     110,    -1,   109,   199,   113,   199,     1,   110,    -1,   109,
     199,   113,   199,     1,    -1,   109,     1,   110,    -1,    -1,
      60,   149,   134,   114,   157,   159,   115,    -1,    60,   149,
     134,     1,   114,   159,   115,    -1,    -1,    60,   149,   114,
     158,   159,   115,    -1,    60,     1,   114,   159,   115,    -1,
     160,   161,   173,   164,   165,    -1,    -1,   160,   132,    -1,
     160,   137,    -1,   160,   145,    -1,    61,   162,   112,    -1,
      61,   162,     1,   112,    -1,    61,   162,     1,    -1,    61,
       1,   112,    -1,    61,     1,    -1,     1,   112,    -1,   163,
      -1,   162,   113,   163,    -1,   162,   113,     1,    -1,    81,
      -1,    81,   114,   199,   115,    -1,    81,   114,   199,     1,
     115,    -1,    81,   114,   199,     1,    -1,    81,   114,     1,
     115,    -1,    81,   114,     1,    -1,    63,    81,   112,    -1,
      63,    81,     1,   112,    -1,    63,    81,     1,    -1,    63,
       1,    -1,     1,    -1,    -1,    64,   166,   112,    -1,    64,
     166,     1,   112,    -1,    64,   166,     1,    -1,    64,     1,
      -1,     1,    -1,   167,    -1,   166,   113,   168,    -1,   166,
     113,     1,    -1,    81,    65,    81,   114,   169,   170,   172,
     115,    -1,    81,    65,    81,   114,   169,   170,   172,     1,
     112,    -1,    81,    65,    81,     1,   115,    -1,    81,    65,
       1,   115,    -1,    81,     1,   115,    -1,    65,    81,   114,
     169,   170,   172,   115,    -1,    65,    81,   114,   169,   170,
     172,     1,   115,    -1,    65,    81,     1,   115,    -1,    65,
       1,   115,    -1,   167,    -1,    -1,    66,   199,   112,    -1,
      66,   199,     1,   112,    -1,    66,     1,   112,    -1,    -1,
      67,   171,   112,    -1,    67,   171,     1,   112,    -1,    67,
     171,     1,    -1,    67,     1,   112,    -1,   199,    14,    -1,
     199,     1,    14,    -1,   199,   103,    -1,   199,     1,   103,
      -1,   199,     1,    -1,    -1,    68,   198,   112,    -1,    68,
       1,   112,    -1,    -1,   174,    -1,   175,    -1,   174,   175,
      -1,    62,   176,   112,    -1,    62,   176,     1,   112,    -1,
      62,   176,     1,    -1,    62,     1,   112,    -1,    62,     1,
      -1,    55,   177,   112,    -1,    55,   177,     1,   112,    -1,
      55,   177,     1,    -1,    55,     1,   112,    -1,    55,     1,
      -1,    81,    -1,   176,   113,    81,    -1,   176,   113,     1,
      -1,    81,    -1,   177,   113,    81,    -1,   177,   113,     1,
      -1,    -1,   114,   179,   180,   181,   115,    -1,    -1,   180,
     137,    -1,   180,   145,    -1,    -1,   181,   182,    -1,   181,
       1,   112,    -1,   178,    -1,   112,    -1,   199,   112,    -1,
      -1,    40,   107,   183,   197,   112,   197,   112,   197,   108,
     182,    -1,    40,   107,     1,   108,   182,    -1,    -1,    41,
     107,   184,   198,   108,   182,    -1,    41,   107,     1,   108,
     182,    -1,    -1,    42,   185,   182,    41,   107,   198,   108,
     112,    -1,    -1,    46,   107,   186,   198,   108,   182,   188,
      -1,    43,   112,    -1,    44,   112,    -1,    -1,    45,   107,
     198,   108,   187,   114,   191,   115,    -1,    50,   199,   112,
      -1,    50,   112,    -1,    -1,    -1,    47,   189,   182,    -1,
      -1,    47,   190,     1,    -1,   192,    -1,   191,   192,    -1,
      -1,    48,   199,   104,   193,   181,    -1,    -1,    48,     1,
     104,   194,   181,    -1,    -1,    49,   104,   195,   181,    -1,
      -1,    49,     1,   104,   196,   181,    -1,    -1,   198,    -1,
     199,    -1,   198,   113,   199,    -1,    58,    -1,    57,    -1,
      83,    -1,    81,    -1,    -1,    81,   107,   200,   206,   108,
      -1,    -1,    81,   107,   201,     1,   108,    -1,   199,   109,
     199,   110,    -1,   199,   109,     1,   110,    -1,   107,   199,
     108,    -1,   107,     1,   108,    -1,   199,    15,    -1,    15,
     199,    -1,   199,    16,    -1,    16,   199,    -1,   205,   199,
      -1,   199,    34,   199,    -1,   199,    35,   199,    -1,   199,
      36,   199,    -1,   199,    37,   199,    -1,   199,    39,   199,
      -1,   199,    38,   199,    -1,   199,    17,   199,    -1,   199,
      18,   199,    -1,   199,    19,   199,    -1,   199,    20,   199,
      -1,   199,    23,   199,    -1,   199,   105,   199,    -1,   199,
      24,   199,    -1,   199,    25,   199,    -1,   199,    26,   199,
      -1,   199,    27,   199,    -1,   199,    28,   199,    -1,   199,
      29,   199,    -1,   199,   103,   199,   104,   199,    -1,   199,
     111,    81,    -1,    73,    -1,    -1,   199,    32,   202,   199,
      -1,   199,    30,   199,    -1,   199,    31,   199,    -1,    33,
     199,    -1,   199,    21,   199,    -1,   199,    22,   199,    -1,
     203,    -1,   199,   204,   199,    -1,     3,    -1,     4,    -1,
       5,    -1,     7,    -1,     8,    -1,     6,    -1,    10,    -1,
       9,    -1,    11,    -1,    12,    -1,    13,    -1,    18,    -1,
      17,    -1,    14,    -1,    -1,   199,    -1,   206,   113,   199,
      -1,   206,   113,     1,    -1,   208,   120,   122,    -1,    -1,
     208,   209,    -1,   208,   213,    -1,   137,    -1,    -1,    54,
     210,   211,   112,    -1,    54,     1,   112,    -1,   212,    -1,
     211,   113,   212,    -1,    81,   144,   141,    -1,    -1,    60,
     149,   219,   114,   214,   223,   115,    -1,    -1,    60,   149,
     219,     1,   114,   215,   223,   115,    -1,    -1,    60,   149,
       1,   114,   216,   223,   115,    -1,    -1,    60,     1,   114,
     217,   223,   115,    -1,    -1,    60,   149,   114,   218,   223,
     115,    -1,   107,   108,    -1,   107,   220,   108,    -1,   107,
     220,     1,    -1,   107,     1,   108,    -1,   221,    -1,   222,
      -1,   220,   112,   221,    -1,   220,   112,     1,    -1,   148,
      81,   144,    -1,   221,   113,    81,   144,    -1,    54,    81,
     144,    -1,   222,   113,    81,   144,    -1,   224,   225,   173,
     164,   229,    -1,    -1,   224,   209,    -1,    61,   226,   112,
      -1,    61,   226,     1,   112,    -1,    61,   226,     1,    -1,
      61,     1,   112,    -1,    61,     1,    -1,     1,    -1,   227,
      -1,   226,   113,   227,    -1,   226,   113,     1,    -1,    81,
      -1,    81,   114,   228,   115,    -1,   199,    -1,   199,     1,
     113,    -1,     1,    -1,   228,   113,   199,    -1,    -1,    64,
     230,   112,    -1,    64,   230,     1,   112,    -1,    64,   230,
       1,    -1,    64,     1,   112,    -1,    64,     1,    -1,     1,
      -1,   231,    -1,   230,   113,   232,    -1,   230,   113,     1,
      -1,    81,    65,    81,   114,   233,   170,   172,   115,    -1,
      81,    65,    81,   114,   233,   170,   172,     1,   115,    -1,
      81,    65,    81,   114,   233,   170,   172,     1,    -1,    81,
      65,    81,     1,   114,   233,   170,   172,   115,    -1,    81,
       1,    65,    81,   114,   233,   170,   172,   115,    -1,    65,
      81,   114,   233,   170,   172,   115,    -1,    65,    81,   114,
     233,   170,   172,     1,    -1,    65,    81,   114,   233,   170,
     172,     1,   115,    -1,    65,    81,     1,   114,   233,   170,
     172,   115,    -1,    65,     1,    81,   114,   233,   170,   172,
     115,    -1,    65,     1,   114,   233,   170,   172,   115,    -1,
     231,    -1,    -1,    66,   234,   112,    -1,    66,   234,     1,
     112,    -1,    66,   234,     1,    -1,    66,     1,    -1,   199,
      -1,   234,   113,   199,    -1,   234,   113,     1,    -1,   236,
     237,    -1,    -1,   236,   237,   116,    -1,    -1,    79,    -1,
     238,   199,    -1,   199,    78,   199,    -1,    74,    -1,    75,
      -1,    76,    -1,    77,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   266,   266,   267,   268,   269,   270,   271,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   291,   294,   296,   296,   301,   304,   307,   310,
     316,   317,   320,   326,   327,   328,   333,   335,   336,   337,
     338,   339,   340,   341,   344,   346,   348,   351,   353,   355,
     357,   359,   363,   365,   370,   370,   376,   382,   383,   384,
     388,   392,   396,   408,   409,   410,   417,   421,   425,   431,
     434,   438,   445,   446,   450,   456,   457,   461,   462,   468,
     469,   473,   476,   479,   485,   486,   487,   491,   495,   500,
     508,   511,   515,   519,   531,   532,   533,   540,   546,   550,
     554,   559,   564,   570,   571,   575,   576,   577,   584,   588,
     593,   596,   599,   605,   606,   607,   614,   620,   621,   622,
     623,   624,   628,   629,   630,   634,   638,   648,   648,   654,
     657,   657,   665,   675,   678,   680,   681,   682,   686,   687,
     690,   693,   696,   699,   705,   706,   707,   713,   716,   719,
     723,   727,   731,   738,   741,   745,   749,   752,   757,   759,
     760,   763,   766,   769,   775,   776,   777,   783,   787,   792,
     795,   798,   804,   807,   811,   814,   817,   821,   823,   826,
     830,   835,   837,   838,   841,   844,   850,   853,   857,   860,
     864,   870,   872,   875,   880,   882,   883,   884,   888,   889,
     892,   895,   898,   904,   905,   908,   911,   914,   920,   923,
     926,   932,   935,   938,   949,   949,   957,   959,   960,   963,
     965,   966,   970,   971,   974,   977,   977,   983,   984,   984,
     990,   991,   991,   997,   997,  1001,  1004,  1007,  1007,  1013,
    1016,  1022,  1025,  1025,  1031,  1031,  1041,  1042,  1046,  1046,
    1052,  1052,  1059,  1059,  1065,  1065,  1074,  1076,  1080,  1081,
    1086,  1089,  1092,  1095,  1098,  1098,  1103,  1103,  1109,  1112,
    1116,  1117,  1121,  1124,  1127,  1130,  1133,  1136,  1139,  1142,
    1145,  1148,  1151,  1154,  1157,  1160,  1163,  1166,  1169,  1172,
    1175,  1178,  1181,  1184,  1187,  1190,  1193,  1196,  1199,  1199,
    1204,  1207,  1210,  1213,  1216,  1219,  1223,  1229,  1230,  1231,
    1232,  1233,  1234,  1235,  1236,  1237,  1238,  1239,  1244,  1245,
    1246,  1251,  1252,  1256,  1260,  1272,  1275,  1277,  1278,  1282,
    1283,  1283,  1288,  1291,  1292,  1296,  1305,  1305,  1311,  1311,
    1318,  1318,  1325,  1325,  1332,  1332,  1341,  1342,  1343,  1347,
    1354,  1358,  1362,  1366,  1373,  1377,  1384,  1389,  1396,  1399,
    1401,  1405,  1406,  1409,  1412,  1415,  1418,  1424,  1425,  1426,
    1432,  1435,  1441,  1442,  1445,  1449,  1454,  1456,  1457,  1460,
    1463,  1466,  1469,  1475,  1476,  1477,  1483,  1487,  1492,  1497,
    1502,  1511,  1514,  1518,  1522,  1526,  1530,  1534,  1537,  1539,
    1542,  1546,  1550,  1556,  1557,  1560,  1567,  1569,  1571,  1573,
    1575,  1578,  1581,  1586,  1587,  1588,  1589
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
  "T_RETURN", "T_TYPEDEF", "T_STRUCT", "T_CONST", "T_OLDCONST", 
  "T_URGENT", "T_BROADCAST", "T_TRUE", "T_FALSE", "T_SYSTEM", "T_PROCESS", 
  "T_STATE", "T_COMMIT", "T_INIT", "T_TRANS", "T_ARROW", "T_GUARD", 
  "T_SYNC", "T_ASSIGN", "T_RATE", "T_BEFORE", "T_AFTER", "T_COST", 
  "T_DEADLOCK", "T_EF", "T_EG", "T_AF", "T_AG", "T_LEADSTO", "T_QUIT", 
  "T_ERROR", "T_ID", "T_TYPENAME", "T_NAT", "T_NEW", "T_NEW_DECLARATION", 
  "T_NEW_LOCAL_DECL", "T_NEW_INST", "T_NEW_SYSTEM", "T_NEW_PARAMETERS", 
  "T_NEW_INVARIANT", "T_NEW_GUARD", "T_NEW_SYNC", "T_NEW_ASSIGN", "T_OLD", 
  "T_OLD_DECLARATION", "T_OLD_LOCAL_DECL", "T_OLD_INST", 
  "T_OLD_PARAMETERS", "T_OLD_INVARIANT", "T_OLD_GUARD", "T_OLD_ASSIGN", 
  "T_PROPERTY", "'?'", "':'", "'&'", "UOPERATOR", "'('", "')'", "'['", 
  "']'", "'.'", "';'", "','", "'{'", "'}'", "'\\n'", "$accept", "Uppaal", 
  "XTA", "Inst", "@1", "System", "ProcessList", "Declaration", "RateDecl", 
  "RateList", "Rate", "BeforeUpdateDecl", "AfterUpdateDecl", 
  "BeforeAssignmentList", "AfterAssignmentList", "FunctionDecl", "@2", 
  "OptionalParameterList", "ParameterList", "Parameter", "VariableDecl", 
  "DeclIdList", "DeclId", "VarInit", "Initializer", "FieldInitList", 
  "FieldInit", "ArrayDecl", "TypeDecl", "TypeIdList", "TypeId", "Type", 
  "Id", "FieldDeclList", "FieldDecl", "FieldDeclIdList", "FieldDeclId", 
  "TypePrefix", "Range", "ProcDecl", "@3", "@4", "ProcBody", 
  "ProcLocalDeclList", "States", "StateDeclList", "StateDecl", "Init", 
  "Transitions", "TransitionList", "Transition", "TransitionOpt", "Guard", 
  "Sync", "SyncExpr", "Assign", "LocFlags", "Commit", "Urgent", 
  "CStateList", "UStateList", "Block", "@5", "BlockLocalDeclList", 
  "StatementList", "Statement", "@6", "@7", "@8", "@9", "@10", "ElsePart", 
  "@11", "@12", "SwitchCaseList", "SwitchCase", "@13", "@14", "@15", 
  "@16", "ExprList0", "ExprList", "Expression", "@17", "@18", "@19", 
  "Assignment", "AssignOp", "UnaryOp", "ArgList", "OldXTA", 
  "OldDeclaration", "OldVarDecl", "@20", "OldConstDeclIdList", 
  "OldConstDeclId", "OldProcDecl", "@21", "@22", "@23", "@24", "@25", 
  "OldProcParams", "OldProcParamList", "OldProcParam", 
  "OldProcConstParam", "OldProcBody", "OldVarDeclList", "OldStates", 
  "OldStateDeclList", "OldStateDecl", "OldInvariant", "OldTransitions", 
  "OldTransitionList", "OldTransition", "OldTransitionOpt", "OldGuard", 
  "OldGuardList", "PropertyList", "PropertyList2", "Property", 
  "Quantifier", 0
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
     355,   356,   357,    63,    58,    38,   358,    40,    41,    91,
      93,    46,    59,    44,   123,   125,    10
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,   117,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   119,   120,   121,   120,   120,   120,   120,   120,
     122,   122,   122,   123,   123,   123,   124,   124,   124,   124,
     124,   124,   124,   124,   125,   126,   126,   127,   128,   129,
     130,   130,   131,   131,   133,   132,   132,   134,   134,   134,
     134,   134,   134,   135,   135,   135,   136,   136,   136,   137,
     137,   137,   138,   138,   139,   140,   140,   141,   141,   142,
     142,   143,   143,   143,   144,   144,   144,   144,   144,   144,
     145,   145,   145,   145,   146,   146,   146,   147,   148,   148,
     148,   148,   148,   149,   149,   150,   150,   150,   151,   151,
     151,   151,   151,   152,   152,   152,   153,   154,   154,   154,
     154,   154,   155,   155,   155,   155,   155,   157,   156,   156,
     158,   156,   156,   159,   160,   160,   160,   160,   161,   161,
     161,   161,   161,   161,   162,   162,   162,   163,   163,   163,
     163,   163,   163,   164,   164,   164,   164,   164,   165,   165,
     165,   165,   165,   165,   166,   166,   166,   167,   167,   167,
     167,   167,   168,   168,   168,   168,   168,   169,   169,   169,
     169,   170,   170,   170,   170,   170,   171,   171,   171,   171,
     171,   172,   172,   172,   173,   173,   173,   173,   174,   174,
     174,   174,   174,   175,   175,   175,   175,   175,   176,   176,
     176,   177,   177,   177,   179,   178,   180,   180,   180,   181,
     181,   181,   182,   182,   182,   183,   182,   182,   184,   182,
     182,   185,   182,   186,   182,   182,   182,   187,   182,   182,
     182,   188,   189,   188,   190,   188,   191,   191,   193,   192,
     194,   192,   195,   192,   196,   192,   197,   197,   198,   198,
     199,   199,   199,   199,   200,   199,   201,   199,   199,   199,
     199,   199,   199,   199,   199,   199,   199,   199,   199,   199,
     199,   199,   199,   199,   199,   199,   199,   199,   199,   199,
     199,   199,   199,   199,   199,   199,   199,   199,   202,   199,
     199,   199,   199,   199,   199,   199,   203,   204,   204,   204,
     204,   204,   204,   204,   204,   204,   204,   204,   205,   205,
     205,   206,   206,   206,   206,   207,   208,   208,   208,   209,
     210,   209,   209,   211,   211,   212,   214,   213,   215,   213,
     216,   213,   217,   213,   218,   213,   219,   219,   219,   219,
     220,   220,   220,   220,   221,   221,   222,   222,   223,   224,
     224,   225,   225,   225,   225,   225,   225,   226,   226,   226,
     227,   227,   228,   228,   228,   228,   229,   229,   229,   229,
     229,   229,   229,   230,   230,   230,   231,   231,   231,   231,
     231,   232,   232,   232,   232,   232,   232,   232,   233,   233,
     233,   233,   233,   234,   234,   234,   235,   236,   236,   237,
     237,   237,   237,   238,   238,   238,   238
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     3,     0,     0,     9,     8,     7,     6,     4,
       3,     4,     3,     1,     3,     3,     0,     2,     2,     2,
       2,     2,     2,     2,     4,     0,     3,     3,     4,     4,
       0,     3,     0,     3,     0,     8,     5,     2,     3,     4,
       3,     3,     2,     1,     3,     3,     4,     3,     2,     3,
       4,     3,     1,     3,     3,     0,     2,     1,     3,     1,
       3,     3,     3,     1,     0,     4,     5,     4,     4,     3,
       4,     5,     4,     3,     1,     3,     3,     2,     3,     5,
       5,     4,     3,     1,     1,     1,     2,     2,     3,     4,
       3,     2,     2,     1,     3,     3,     2,     0,     1,     1,
       2,     1,     0,     5,     6,     5,     3,     0,     7,     7,
       0,     6,     5,     5,     0,     2,     2,     2,     3,     4,
       3,     3,     2,     2,     1,     3,     3,     1,     4,     5,
       4,     4,     3,     3,     4,     3,     2,     1,     0,     3,
       4,     3,     2,     1,     1,     3,     3,     8,     9,     5,
       4,     3,     7,     8,     4,     3,     1,     0,     3,     4,
       3,     0,     3,     4,     3,     3,     2,     3,     2,     3,
       2,     0,     3,     3,     0,     1,     1,     2,     3,     4,
       3,     3,     2,     3,     4,     3,     3,     2,     1,     3,
       3,     1,     3,     3,     0,     5,     0,     2,     2,     0,
       2,     3,     1,     1,     2,     0,    10,     5,     0,     6,
       5,     0,     8,     0,     7,     2,     2,     0,     8,     3,
       2,     0,     0,     3,     0,     3,     1,     2,     0,     5,
       0,     5,     0,     4,     0,     5,     0,     1,     1,     3,
       1,     1,     1,     1,     0,     5,     0,     5,     4,     4,
       3,     3,     2,     2,     2,     2,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     5,     3,     1,     0,     4,
       3,     3,     2,     3,     3,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     1,     3,     3,     3,     0,     2,     2,     1,
       0,     4,     3,     1,     3,     3,     0,     7,     0,     8,
       0,     7,     0,     6,     0,     6,     2,     3,     3,     3,
       1,     1,     3,     3,     3,     4,     3,     4,     5,     0,
       2,     3,     4,     3,     3,     2,     1,     1,     3,     3,
       1,     4,     1,     3,     1,     3,     0,     3,     4,     3,
       3,     2,     1,     1,     3,     3,     8,     9,     8,     9,
       9,     7,     7,     8,     8,     8,     7,     1,     0,     3,
       4,     3,     2,     1,     3,     3,     2,     0,     3,     0,
       1,     2,     3,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned short yydefact[] =
{
       0,    36,    36,   134,    23,     0,   117,     0,     0,     0,
       0,   326,   326,   359,    23,   117,     0,     0,     0,   407,
       0,     2,    23,   117,   117,     5,     7,     0,     6,   121,
     118,   119,     8,    63,     0,     0,   320,     0,     0,   319,
     318,     0,   261,   260,   297,   263,   262,     0,     9,   305,
       0,    10,    11,     0,    12,   258,    13,    23,   117,   117,
      16,     0,     0,    17,   350,   351,   374,     0,    18,   403,
      19,    20,    21,   409,     1,     0,     0,     0,     0,     0,
       0,    41,    42,    43,    37,    38,    39,     0,    40,   135,
     136,   137,     0,     0,    33,     0,   120,     0,    68,    84,
       0,     0,   122,   273,   275,   302,   264,     0,     0,   307,
     308,   309,   312,   310,   311,   314,   313,   315,   316,   317,
     272,   274,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   298,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   276,
     190,   186,   188,     0,     0,     0,     0,   329,     0,   327,
     328,   360,    84,    84,     0,     0,     0,     0,     0,     0,
     413,   414,   415,   416,   410,     0,   406,     0,     0,     0,
       0,   103,   104,     0,    45,    50,    52,    22,     0,     0,
      72,    84,     0,     0,    32,     0,    30,     0,    65,    64,
      67,    84,   102,     0,     0,    98,   321,     0,   271,   270,
     283,   284,   285,   286,   303,   304,   287,   289,   290,   291,
     292,   293,   294,   300,   301,     0,   277,   278,   279,   280,
     282,   281,     0,   288,     0,     0,   296,   306,   187,   189,
     259,     0,     0,     0,     0,   325,    84,   356,   354,   353,
     352,    84,    84,   373,   375,   405,   404,     0,   408,   411,
      93,     0,     0,    94,    84,   134,     0,   130,     0,     0,
       0,     0,    71,     0,    69,     0,     0,    75,    29,     0,
      31,    35,    34,     0,    66,   101,     0,     0,   105,     0,
       0,   322,     0,     0,   299,     0,   269,   268,   332,    84,
       0,   333,   342,     0,     0,   344,     0,   355,   357,   412,
      92,     0,    90,     0,    97,     0,     0,    62,    57,     0,
     134,     0,   127,     0,    44,     0,    48,     0,   305,    49,
     305,    70,    73,     0,     0,     0,    74,     0,     0,    89,
       0,   112,   100,   111,    84,     0,   113,   107,    99,   106,
     126,     0,   265,     0,   267,   295,     0,   331,     0,   359,
     340,     0,   346,     0,   359,     0,   336,    91,    96,    95,
     132,     0,     0,   194,    61,    60,    58,     0,   134,   134,
       0,    46,    51,    53,    56,   216,     0,    76,    77,    28,
       0,   321,    88,    87,    85,   110,   116,     0,   108,     0,
       0,   324,   323,   335,   334,     0,     0,   359,   349,   348,
     347,     0,   338,   359,   143,   142,   147,     0,   144,     0,
       0,     0,   195,   196,    59,   131,     0,     0,    47,   219,
     263,    83,     0,    79,     0,     0,    27,     0,    86,   109,
     115,   114,   125,   123,   343,   366,     0,   194,     0,   345,
     359,     0,   141,     0,   140,   138,     0,   207,   211,     0,
     202,   208,     0,   157,     0,     0,   197,   129,   128,   217,
     218,     0,     0,    78,     0,    26,     0,   124,   365,   370,
       0,   367,     0,   341,     0,   337,   152,     0,   139,   146,
     145,   206,   205,   203,     0,   201,   200,   198,     0,   156,
       0,   163,     0,   133,     0,     0,     0,   231,     0,     0,
       0,     0,     0,   223,   214,    55,   222,   220,     0,    80,
      82,    81,    25,   364,     0,   363,   361,     0,     0,   339,
     151,   150,   148,   204,   213,   212,   199,   210,   209,   155,
     153,   162,     0,     0,   164,   221,     0,     0,     0,   235,
     236,     0,   233,   240,     0,   216,   224,     0,   362,   369,
     368,   382,     0,   358,   149,   154,     0,     0,   161,   159,
       0,     0,   256,     0,     0,     0,     0,     0,   239,   219,
     371,   381,     0,     0,   383,   171,     0,     0,   160,   166,
       0,   176,   165,     0,     0,   257,     0,     0,     0,   237,
       0,     0,   380,     0,     0,   379,   377,     0,   170,     0,
     177,     0,     0,   227,   256,   230,     0,     0,     0,     0,
     215,     0,     0,   378,   385,     0,   397,   384,   169,     0,
     181,   175,     0,   177,     0,   229,     0,     0,   241,     0,
       0,   398,     0,     0,     0,     0,     0,   191,   174,   181,
     256,     0,     0,     0,     0,   246,   242,   234,   398,   398,
       0,   181,     0,   398,     0,   398,   180,     0,   178,     0,
       0,     0,     0,   191,     0,   232,     0,     0,     0,   252,
     238,   247,     0,     0,   181,   181,   402,     0,   191,   398,
     181,   398,   181,   179,   185,   184,   182,     0,     0,     0,
     167,     0,     0,   250,   248,   254,   219,   243,   245,   191,
     191,   401,   399,     0,   181,   191,   181,   191,   183,   193,
     192,   168,     0,   172,   226,   219,   219,   219,     0,     0,
       0,   400,   388,   386,   191,     0,   191,     0,   173,     0,
       0,     0,   390,   389,   387,     0,   396,     0,   392,   391,
     395,   394,   393
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,    20,    21,    25,   391,    28,    95,    22,    81,   269,
     325,    82,    83,   270,   271,    84,   334,   268,    32,    33,
     157,   189,   190,   336,   431,   432,   433,   277,    86,   262,
     263,   158,   246,   287,   288,   345,   346,    35,   205,    88,
     379,   320,   315,   316,   373,   417,   418,   465,   503,   543,
     544,   592,   630,   647,    52,   672,   421,   422,   423,   462,
     459,   516,   555,   429,   471,   517,   572,   574,   548,   577,
     618,   657,   682,   683,   654,   655,   726,   725,   706,   727,
     594,   595,   518,   206,   207,   225,    49,   148,    50,   292,
      56,    57,   159,   242,   300,   301,   160,   413,   450,   407,
     359,   364,   306,    63,    64,    65,   405,   406,   447,   480,
     481,    68,   563,   583,   584,   627,   661,    70,    72,    73,
     176,   177
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -595
static const short yypact[] =
{
    1120,  -595,  -595,  -595,  -595,    49,   545,  2797,  2797,  2797,
    2797,  -595,  -595,  -595,  -595,   478,   705,  2797,  2797,  -595,
      29,  -595,  1121,  1885,   840,    -1,  -595,   212,  -595,  -595,
     -33,  -595,    -3,  -595,   248,   -25,  -595,  2797,  2797,  -595,
    -595,  2797,  -595,  -595,  -595,   103,  -595,   827,  1817,  -595,
    2797,  1817,  -595,   975,   120,  1817,  -595,   999,   459,   606,
      -1,   156,   201,   177,   227,   241,  -595,   472,   251,  1817,
     255,   120,  -595,  2769,  -595,   672,    23,   224,   247,   258,
     -34,  -595,  -595,  -595,  -595,  -595,  -595,    31,  -595,  -595,
    -595,  -595,    70,   281,  -595,    71,  -595,   794,  -595,  -595,
     334,    34,   355,   230,   230,  1963,   467,   427,  1416,  -595,
    -595,  -595,  -595,  -595,  -595,  -595,  -595,  -595,  -595,  -595,
    -595,  -595,  2797,  2797,  2797,  2797,  2797,  2797,  2797,  2797,
    2797,  2797,  2797,  2797,  2797,  2797,  2797,  -595,  2797,  2797,
    2797,  2797,  2797,  2797,  2797,  2797,  1992,   460,  2797,   230,
       4,  -595,  2797,  2797,   264,   223,   -34,  -595,    31,  -595,
    -595,  -595,  -595,  -595,   968,   461,   479,   430,  2797,  2003,
    -595,  -595,  -595,  -595,  -595,  1525,   443,  2797,   452,   238,
     458,  -595,  -595,   127,  -595,  -595,  -595,  -595,   466,    73,
    -595,   475,   476,   493,  -595,   487,  -595,   285,  -595,  -595,
     477,  -595,  -595,   976,  2012,  -595,  2797,   583,  -595,  -595,
     689,   689,   230,   230,  1056,  1056,   230,  2662,  2687,   660,
     660,  2606,  2581,  1963,  1854,  2797,   531,   531,  2742,  2742,
     531,   531,  1562,  2712,   502,  1671,  -595,  1963,  -595,  -595,
    1817,   501,   533,   513,    64,  -595,  -595,   477,   477,  -595,
     227,  -595,  -595,  -595,  1817,  -595,  1817,  2797,  -595,  1817,
    -595,   523,    75,  -595,  -595,  -595,   280,  -595,    40,   -21,
    2297,  2302,  -595,   525,  -595,   166,    52,    89,  -595,    95,
    -595,  -595,  -595,  2023,   477,   -63,   266,    32,  -595,   534,
    1232,  1817,   257,   538,  1854,  2797,  -595,  -595,  -595,  -595,
     296,  -595,  -595,   527,   261,  -595,    54,   477,   477,  1817,
    -595,   535,  -595,   274,   477,   536,   868,   541,  -595,    81,
    -595,   549,  -595,   546,  -595,   540,  -595,  1817,   554,  -595,
     560,  -595,  -595,   559,   567,  2431,  -595,   572,   294,   578,
    1084,  -595,  -595,   573,  -595,    88,  -595,   579,  -595,  -595,
    -595,  2797,  -595,  2099,  -595,  2556,  2385,  -595,   533,  -595,
    -595,   584,  -595,   195,  -595,   593,  -595,  -595,  -595,  -595,
    -595,   617,   295,   225,  -595,   610,  -595,   615,  -595,  -595,
    2797,  -595,  -595,  -595,  -595,  -595,  2420,  -595,  1817,  -595,
     -50,  2797,  -595,   621,  -595,  -595,   477,   623,  -595,   276,
    1123,  -595,  1817,  -595,  -595,   618,   749,  -595,  -595,  -595,
    -595,   622,  -595,  -595,  -595,   634,   637,    92,  -595,   297,
     301,    18,   697,  -595,  -595,  -595,   638,   640,  1817,   474,
     462,  -595,    80,  -595,   654,   647,  -595,   272,  -595,  -595,
    -595,  -595,   651,  -595,  -595,  -595,   323,   225,   649,  -595,
    -595,   655,  -595,  2106,   661,  -595,   329,   662,  -595,    94,
     663,  -595,    96,  -595,   330,    27,  -595,  -595,  -595,  -595,
    -595,   775,  2420,  -595,   159,  -595,   665,  -595,   667,   652,
     102,  -595,    18,  -595,   666,  -595,   668,   413,  -595,  -595,
    -595,  -595,   673,  -595,   380,  -595,   675,  -595,   382,  -595,
      45,  -595,   385,  -595,   682,   677,   690,  -595,   684,   687,
     700,   702,  2458,  -595,  -595,  -595,  -595,  -595,  1269,  -595,
    -595,  -595,  -595,  -595,   705,   711,  -595,   388,    35,  -595,
    -595,   709,  -595,  -595,  -595,  -595,  -595,  -595,  -595,   714,
    -595,  -595,   362,   108,  -595,  -595,   522,  2111,  2348,  -595,
    -595,  2797,  -595,  -595,  1379,  -595,  -595,   284,  -595,  -595,
    -595,  -595,   389,  -595,  -595,  -595,   712,   390,   717,  -595,
      25,   722,  2797,   726,  2797,   810,   290,  2797,  -595,   474,
    -595,   740,   391,   110,  -595,  -595,   738,    58,  -595,  -595,
     393,  -595,  -595,  2348,   743,   120,  2348,   292,   750,  -595,
     345,   821,  -595,   803,   778,   758,  -595,   269,  -595,   757,
     807,   759,    66,  -595,  2797,  -595,  2348,  2797,   761,  2348,
    -595,   796,    67,  -595,  -595,   405,  -595,  -595,  -595,  2144,
     813,  -595,   766,   807,   771,  -595,   349,   406,   839,   774,
     783,   826,   -60,    68,   786,   936,  2182,   831,  -595,   813,
    2797,   789,  2215,    47,   182,  -595,   902,  -595,   826,   826,
    2220,   813,   791,   826,   792,   826,  -595,   795,  -595,   797,
      99,  2227,    38,   831,   804,  -595,   809,  1708,   811,  -595,
    -595,  -595,  2348,   910,   813,   813,  -595,   178,   831,   826,
     813,   826,   813,  -595,  -595,   802,  -595,   805,   408,   806,
    -595,    41,  2348,  -595,  -595,  -595,  -595,  -595,  -595,   831,
     831,   814,  -595,    43,   813,   831,   813,   831,  -595,  -595,
    -595,  -595,   801,  -595,  -595,  -595,  -595,  -595,   211,   812,
     815,  -595,   816,  -595,   831,   817,   831,    44,  -595,   575,
     653,   699,  -595,  -595,  -595,   823,  -595,   893,   900,  -595,
    -595,  -595,  -595
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -595,  -595,  -595,   221,  -595,   -58,  -595,   920,  -595,  -595,
    -595,  -595,  -595,  -595,  -595,   -10,  -595,   734,   751,   919,
     -17,  -595,   744,  -595,  -319,  -595,   550,   -61,   -16,  -595,
     713,    55,   -12,  -595,   731,  -595,   626,  -595,  -595,  -595,
    -595,  -595,    17,  1024,  -595,  -595,   574,   553,  -595,  -595,
     473,  -595,   403,   -88,   396,   -79,   590,  -595,   624,  -595,
    -595,  -595,  -595,   489,  -562,  -533,  -595,  -595,  -595,  -595,
    -595,  -595,  -595,  -595,  -595,   395,  -595,  -595,  -595,  -595,
    -594,    -6,    -7,  -595,  -595,  -595,     1,  -595,  -595,   669,
    -595,  1044,   -46,  -595,  -595,   703,  -595,  -595,  -595,  -595,
    -595,  -595,  -595,   753,   898,  -595,  -128,  1050,  -595,  -595,
     542,   543,  -595,  -595,   463,  -595,   375,   417,  -595,  -595,
    -595,  -595
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -377
static const short yytable[] =
{
      48,    51,    53,    55,    54,    85,    85,    90,    91,    67,
      69,    55,    71,   161,    89,   575,   387,   601,   238,   463,
     634,   662,   187,    96,   180,    27,   589,   101,   501,    74,
     103,   104,   188,   347,   105,   202,   561,   403,   200,   699,
     108,   321,   722,   149,   732,   748,   539,    92,   678,   341,
      26,   323,   342,   333,   663,   365,   674,   102,   435,   609,
     613,    34,   436,   615,   183,   303,   175,   632,   640,   664,
      62,   192,   195,   193,   273,   191,   311,    87,    87,    87,
      92,   464,   375,   635,  -117,    29,   638,    30,    31,   397,
     590,   502,   335,   454,   324,   492,   337,   496,   245,   562,
     695,   247,   248,   525,   181,   182,   542,   239,    27,   568,
      97,   605,   181,   182,  -117,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     179,   226,   227,   228,   229,   230,   231,   232,   233,   235,
     284,   237,  -158,   244,   728,   232,   240,   348,   203,   707,
    -376,   679,    34,   700,   322,   521,   723,   540,   733,   749,
     520,   254,   256,   739,   740,   741,   -54,   264,   366,   724,
     259,   304,   610,    36,    37,    38,    39,    40,   305,   711,
     633,   641,   665,   196,   197,   274,   275,   312,   313,   376,
     307,   308,    41,   472,    97,   473,   409,   290,   283,   291,
     398,   399,   338,   314,   455,   456,   493,   494,   497,   498,
     106,   696,   504,    93,   526,   527,    42,    43,   294,    62,
     569,   570,   606,   607,   243,    36,    37,    38,    39,    40,
     652,   653,    44,   153,   266,    60,   411,   162,   356,   261,
      45,   267,    46,    80,    41,   120,   121,   181,   182,    98,
     309,   505,   506,   507,   508,   509,   510,   511,   286,  -253,
    -253,   512,   361,   327,   327,   241,    47,   343,    42,    43,
     624,   328,   330,   386,   344,   368,   340,   440,   156,   448,
     419,   317,   163,   396,    44,   451,   281,   420,   355,   164,
     712,   169,    45,    94,    46,   390,   415,   680,   457,    90,
      91,   264,   460,   410,   181,   182,    89,   164,   -24,   -24,
     -24,   -24,   -24,  -117,    29,    61,    30,    31,    47,   181,
     182,    34,   484,   513,   478,   514,  -253,   -24,   388,    99,
     489,   499,  -117,    29,   625,    30,    31,   377,   184,   146,
     165,   147,   286,  -117,   400,  -330,   402,   181,   182,   388,
     582,   -24,   -24,   100,   166,   181,   182,   181,   182,    62,
     161,   185,  -117,   566,   168,   352,   282,   -24,   169,   362,
     353,    87,   186,   428,   434,   -24,   416,   -24,   458,   388,
     476,   534,   461,   537,   291,   353,   541,   344,   318,   559,
     581,   586,   603,   194,   611,   426,   427,   168,   599,   580,
     616,   -24,   -24,   153,   479,   153,   642,   -24,   357,   358,
     416,   500,   469,   470,   531,   201,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   567,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   487,   138,   139,   140,
     141,   142,   143,   619,   652,   653,   604,   651,   153,   -14,
     434,   535,   153,   538,   204,   388,   542,   388,  -266,   479,
     582,   587,  -372,   167,   612,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   643,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   554,   138,   139,   140,   141,
     142,   143,    29,   154,    30,    31,   144,    67,   145,   155,
     720,   153,   146,   571,   147,    75,  -117,    29,   532,    30,
      31,    29,    61,    30,    31,   208,  -225,  -225,  -225,  -225,
    -225,   236,   251,   253,    55,   576,   120,   121,   122,   123,
     124,   125,   126,   127,   128,  -225,  -117,   131,   132,   258,
     252,   673,   469,   470,   260,    55,  -103,    55,   597,   106,
      55,   600,   265,   688,   279,   144,   504,   145,   272,  -225,
    -225,   146,   266,   147,   293,  -372,   283,  -372,   278,    36,
      37,    38,    39,    40,   701,  -225,   709,   710,    29,   280,
      30,    31,   715,  -225,   717,  -225,   -15,    55,    41,   713,
      55,   636,   296,   298,   299,   505,   506,   507,   508,   509,
     510,   511,   645,  -251,  -251,   512,   734,   302,   736,  -225,
     729,   730,    42,    43,  -225,   310,   735,   331,   737,    53,
     146,   360,   147,    55,   350,   677,   354,   367,    44,   374,
     380,   370,   381,    69,   504,   745,    45,   747,    46,    29,
     154,    30,    31,   378,    55,   698,   382,    36,    37,    38,
      39,    40,   383,   178,   384,   120,   121,   122,   123,   124,
     125,   385,    47,   128,   389,   395,    41,   513,   392,   514,
    -251,   341,   408,   505,   506,   507,   508,   509,   510,   511,
     504,  -249,  -249,   512,   120,   121,    66,   412,   124,   125,
      42,    43,   128,    36,    37,    38,    39,    40,   424,    36,
      37,    38,    39,    40,  -117,    29,    44,    30,    31,   414,
     425,   438,    41,   444,    45,   439,    46,   449,    41,   505,
     506,   507,   508,   509,   510,   511,   452,  -255,  -255,   512,
     445,   453,   419,   467,  -117,   468,    42,    43,   474,   475,
      47,   477,    42,    43,   483,   513,   524,   514,  -249,   146,
     485,   147,    44,   488,   491,   495,   504,   522,    44,   523,
      45,   529,    46,   530,   546,   533,    45,   536,    46,    36,
      37,    38,    39,    40,   545,   198,   549,   547,   146,   550,
     147,  -117,    29,   154,    30,    31,    47,   551,    41,   552,
     446,   513,    47,   514,  -255,   505,   506,   507,   508,   509,
     510,   511,   504,   558,   564,   512,   565,   585,   107,   588,
     593,  -117,    42,    43,   596,    36,    37,    38,    39,    40,
      -4,    36,    37,    38,    39,    40,  -117,    29,    44,    30,
      31,   598,   602,   608,    41,   614,    45,   617,    46,   622,
      41,   505,   506,   507,   508,   509,   510,   511,   621,   371,
     623,   512,   628,   629,   631,   637,  -117,   639,    42,    43,
     646,   648,    47,   650,    42,    43,   656,   513,   658,   514,
     515,    75,   660,    29,    44,    30,    31,   659,   666,   671,
      44,   675,    45,  -244,    46,   689,   691,   693,    45,   694,
      46,   708,   702,   703,   718,   705,   738,   719,   721,    75,
    -117,    29,    23,    30,    31,   276,   731,   742,    47,   372,
     743,   744,   746,   513,    47,   514,   620,   667,   750,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
    -117,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   249,
     138,   139,   140,   141,   142,   143,   150,   285,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   151,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   751,   138,
     139,   140,   141,   142,   143,   752,   199,   319,   349,   332,
    -117,    29,   519,    30,    31,   441,   369,    24,  -117,    29,
     490,    30,    31,   684,   685,   528,   649,   482,   690,   144,
     692,   145,   670,   591,   579,   146,   466,   147,   668,   681,
    -117,  -117,    29,   154,    30,    31,    58,   363,  -117,   155,
     437,   404,   250,    59,   714,     0,   716,   557,     0,   560,
     626,   120,   121,   122,   123,   124,   125,   687,   152,   128,
     145,  -117,   131,   132,   146,   393,   147,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,     0,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,     0,   138,   139,
     140,   141,   142,   143,   442,     0,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,     0,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,     0,   138,   139,   140,
     141,   142,   143,     0,     0,   146,     0,   147,     0,     0,
       0,     0,    75,  -117,    29,     0,    30,    31,     0,     0,
       0,    76,     0,     0,     0,     0,     0,   144,     0,   145,
      77,    78,    79,   146,   394,   147,     0,     0,     0,     0,
       0,     0,     0,  -117,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     0,     0,     0,   144,     0,   145,     0,
       0,     0,   146,   443,   147,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,     0,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,     0,   138,   139,   140,   141,
     142,   143,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,     0,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,     0,   138,   139,   140,   141,   142,   143,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   144,     0,   145,     0,     0,
       0,   146,     0,   147,     0,   351,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   144,     0,   145,     0,     0,     0,   146,     0,
     147,   556,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,     0,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,     0,   138,   139,   140,   141,   142,   143,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
       0,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,     0,
     138,   139,   140,   141,   142,   143,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   144,     0,   145,     0,     0,     0,   146,     0,
     147,   578,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   144,
       0,   145,     0,     0,   209,   146,     0,   147,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,     0,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,     0,   138,
     139,   140,   141,   142,   143,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,     0,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,     0,   138,   139,   140,   141,
     142,   143,     0,   257,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   144,     0,
     145,     0,     0,     0,   146,     0,   147,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   144,   295,   145,     0,     0,
       0,   146,     0,   147,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,     0,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,     0,   138,   139,   140,   141,   142,
     143,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,     0,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,     0,   138,   139,   140,   141,   142,   143,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   144,     0,   145,     0,     0,     0,
     146,   297,   147,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   144,   704,   145,     0,     0,     0,   146,     0,   147,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,     0,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
       0,   138,   139,   140,   141,   142,   143,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,     0,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,    -3,     0,     0,   138,   139,
     140,   141,   142,   143,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     144,     0,   145,     0,     0,     0,   146,     0,   147,     0,
       0,     0,     0,     0,     0,     0,    75,     0,    29,     0,
      30,    31,     0,     0,     0,    76,     0,     0,     0,     0,
       0,     0,     0,     0,    77,    78,    79,   144,     0,   145,
       0,     0,     0,   146,     0,   147,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,     0,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   234,     0,     0,     0,   138,   139,   140,
     141,   142,   143,     0,   255,     0,    36,    37,    38,    39,
      40,     0,     0,   289,     0,     0,     0,    36,    37,    38,
      39,    40,     0,     0,   339,    41,    36,    37,    38,    39,
      40,     0,     0,     0,     0,     0,    41,    36,    37,    38,
      39,    40,     0,     0,     0,    41,     0,     0,     0,    42,
      43,     0,     0,     0,     0,     0,    41,     0,     0,     0,
      42,    43,     0,     0,     0,    44,   144,     0,   145,    42,
      43,     0,   146,    45,   147,    46,    44,     0,     0,     0,
      42,    43,     0,     0,    45,    44,    46,     0,     0,     0,
       0,     0,     0,    45,     0,    46,    44,     0,     0,    47,
     401,     0,     0,     0,    45,     0,    46,   486,     0,     0,
      47,     0,   573,    36,    37,    38,    39,    40,     0,    47,
      36,    37,    38,    39,    40,  -228,  -228,  -228,  -228,  -228,
      47,     0,    41,     0,     0,     0,     0,     0,     0,    41,
       0,     0,     0,     0,  -228,   644,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    42,    43,    36,    37,
      38,    39,    40,    42,    43,     0,     0,     0,  -228,  -228,
       0,     0,    44,     0,     0,     0,     0,    41,     0,    44,
      45,     0,    46,   669,  -228,     0,     0,    45,     0,    46,
       0,     0,  -228,     0,  -228,     0,    36,    37,    38,    39,
      40,    42,    43,     0,     0,     0,    47,     0,     0,     0,
       0,     0,     0,    47,     0,    41,   676,    44,  -228,     0,
       0,   686,     0,     0,     0,    45,     0,    46,   697,    36,
      37,    38,    39,    40,    36,    37,    38,    39,    40,    42,
      43,    36,    37,    38,    39,    40,     0,     0,    41,     0,
       0,    47,     0,    41,     0,    44,     0,     0,     0,     0,
      41,     0,     0,    45,     0,    46,     0,     0,     0,     0,
       0,     0,    42,    43,     0,     0,     0,    42,    43,     0,
       0,     0,     0,     0,    42,    43,     0,     0,    44,    47,
       0,     0,     0,    44,     0,     0,    45,     0,    46,     0,
      44,    45,     0,    46,     0,     0,     0,     0,    45,     0,
      46,    36,    37,    38,    39,    40,    36,    37,    38,    39,
      40,     0,    47,     0,     0,     0,     0,    47,     0,     0,
      41,     0,     0,     0,    47,    41,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    42,    43,     0,     0,     0,    42,
      43,     0,    36,    37,    38,    39,    40,     0,     0,     0,
      44,     0,     0,     0,     0,    44,     0,     0,    45,     0,
      46,    41,     0,    45,     0,    46,     0,     0,   505,   506,
     507,   508,   509,   510,   511,     0,     0,     0,   512,    36,
      37,    38,    39,    40,    47,    42,    43,     0,     0,    47,
       0,     0,   326,     0,     0,     0,     0,   329,    41,     0,
       0,    44,     0,     0,     0,     0,     0,     0,     0,    45,
       0,    46,     0,     0,    36,    37,    38,    39,    40,     0,
       0,     0,    42,    43,     0,    36,    37,    38,    39,    40,
       0,     0,     0,    41,     0,    47,     0,     0,    44,     0,
     513,     0,   514,     0,    41,     0,    45,     0,    46,     0,
       0,     0,    36,    37,    38,    39,    40,    42,    43,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    42,    43,
       0,    41,    47,    44,   283,     0,     0,     0,     0,   386,
       0,   430,   182,    46,    44,     0,     0,     0,     0,     0,
       0,     0,    45,     0,    46,    42,    43,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    47,     0,     0,
       0,    44,     0,     0,   386,     0,     0,     0,    47,    45,
       0,    46,     0,     0,     0,   386,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    47,     0,     0,     0,     0,
     553,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,     0,     0,     0,     0,
     138,   139,   140,   141,   142,   143,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
       0,     0,     0,     0,     0,   138,   139,   140,   141,   142,
     143,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,     0,     0,     0,     0,     0,     0,
     138,   139,   140,   141,   142,   143,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   144,
       0,   145,     0,     0,     0,   146,     0,   147,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   145,   130,   131,   132,
     146,     0,   147,     0,     0,     0,   138,   139,   140,   141,
     142,   143,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   145,     0,   131,   132,   146,     0,   147,     0,     0,
       0,   138,   139,   140,   141,   142,   143,   120,   121,   122,
     123,   124,   125,   126,   127,   128,     0,     0,   131,   132,
       0,     0,     0,     0,     0,     0,   138,   139,   140,   141,
     142,   143,     0,     0,     0,     0,     0,   120,   121,   122,
     123,   124,   125,   126,   127,   128,     0,   145,   131,   132,
       0,   146,     0,   147,     0,     0,   138,   139,     0,     0,
     142,   143,     0,    36,    37,    38,    39,    40,     0,     0,
       0,     0,   145,     0,     0,     0,   146,     0,   147,     0,
       0,     0,    41,     0,     0,     0,     0,     0,     0,     0,
       0,    36,    37,    38,    39,    40,     0,     0,     0,     0,
       0,   146,     0,   147,     0,     0,    42,    43,     0,     0,
      41,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    44,   170,   171,   172,   173,     0,   174,     0,
      45,   146,    46,   147,    42,    43,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      44,     0,     0,     0,     0,     0,    47,     0,    45,     0,
      46,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    47
};

static const short yycheck[] =
{
       7,     8,     9,    10,    10,    22,    23,    24,    24,    16,
      17,    18,    18,    59,    24,   548,   335,   579,    14,     1,
     614,    81,    80,    56,     1,    59,     1,    52,     1,     0,
      37,    38,     1,     1,    41,     1,     1,   356,    99,     1,
      47,     1,     1,    50,     1,     1,     1,    81,     1,   112,
       1,    72,   115,     1,   114,     1,   650,    82,   108,     1,
     593,     6,   112,   596,    76,     1,    73,     1,     1,     1,
      15,     1,     1,     3,     1,    87,     1,    22,    23,    24,
      81,    63,     1,   616,    52,    53,   619,    55,    56,     1,
      65,    64,     3,     1,   115,     1,     1,     1,   156,    64,
       1,   162,   163,     1,    81,    82,    81,   103,    59,     1,
     113,     1,    81,    82,    82,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
      75,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     201,   148,   115,   155,   706,   152,   153,   115,   114,   682,
     115,   104,    97,   115,   114,   474,   115,   112,   115,   115,
       1,   168,   169,   725,   726,   727,   114,   179,   114,   702,
     177,   107,   114,    14,    15,    16,    17,    18,   114,     1,
     114,   114,   114,   112,   113,   112,   113,   112,   113,   108,
     251,   252,    33,   113,   113,   115,     1,   204,   109,   206,
     112,   113,   107,   264,   112,   113,   112,   113,   112,   113,
     107,   112,     1,     1,   112,   113,    57,    58,   225,   164,
     112,   113,   112,   113,     1,    14,    15,    16,    17,    18,
      48,    49,    73,   113,   107,    14,   364,    81,   299,     1,
      81,   114,    83,    22,    33,    15,    16,    81,    82,     1,
     257,    40,    41,    42,    43,    44,    45,    46,   203,    48,
      49,    50,     1,   270,   271,     1,   107,     1,    57,    58,
       1,   270,   271,   114,   286,     1,   283,     1,    57,   407,
      55,     1,    81,   344,    73,   413,     1,    62,   295,   112,
     112,   113,    81,    81,    83,     1,     1,   115,     1,   316,
     316,   313,     1,   108,    81,    82,   316,   112,    14,    15,
      16,    17,    18,    52,    53,    54,    55,    56,   107,    81,
      82,   266,   450,   112,     1,   114,   115,    33,   335,    81,
       1,     1,    52,    53,    65,    55,    56,   320,   114,   109,
     113,   111,   287,    82,   351,    81,   353,    81,    82,   356,
      81,    57,    58,   105,   113,    81,    82,    81,    82,   304,
     406,   114,    82,     1,   113,   108,    81,    73,   113,   108,
     113,   316,   114,   380,   386,    81,    81,    83,    81,   386,
     108,     1,    81,     1,   391,   113,     1,   399,   108,     1,
       1,     1,     1,   112,     1,   378,   379,   113,   108,   115,
     108,   107,   108,   113,    81,   113,     1,   113,   112,   113,
      81,    81,   429,   429,     1,    81,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    65,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,   453,    34,    35,    36,
      37,    38,    39,   108,    48,    49,    65,   108,   113,     0,
     472,    81,   113,    81,   109,   472,    81,   474,     1,    81,
      81,    81,     0,     1,    81,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    81,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,   512,    34,    35,    36,    37,
      38,    39,    53,    54,    55,    56,   103,   524,   105,    60,
     112,   113,   109,     1,   111,    51,    52,    53,   115,    55,
      56,    53,    54,    55,    56,   108,    14,    15,    16,    17,
      18,    81,    81,   113,   551,   551,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    33,    82,    26,    27,   116,
      81,   649,   579,   579,   112,   572,   104,   574,   574,   107,
     577,   577,   114,   661,    81,   103,     1,   105,   112,    57,
      58,   109,   107,   111,     1,   113,   109,   115,   112,    14,
      15,    16,    17,    18,   673,    73,   684,   685,    53,   112,
      55,    56,   690,    81,   692,    83,     0,   614,    33,   688,
     617,   617,   110,   112,    81,    40,    41,    42,    43,    44,
      45,    46,   629,    48,    49,    50,   714,   114,   716,   107,
     709,   710,    57,    58,   112,   112,   715,   112,   717,   646,
     109,   114,   111,   650,   110,   652,   108,   112,    73,   108,
     104,   115,   112,   660,     1,   734,    81,   736,    83,    53,
      54,    55,    56,   114,   671,   671,   112,    14,    15,    16,
      17,    18,   112,     1,   115,    15,    16,    17,    18,    19,
      20,   114,   107,    23,   112,   112,    33,   112,   110,   114,
     115,   112,   108,    40,    41,    42,    43,    44,    45,    46,
       1,    48,    49,    50,    15,    16,     1,   114,    19,    20,
      57,    58,    23,    14,    15,    16,    17,    18,   108,    14,
      15,    16,    17,    18,    52,    53,    73,    55,    56,   112,
     115,   110,    33,   115,    81,   112,    83,   115,    33,    40,
      41,    42,    43,    44,    45,    46,   112,    48,    49,    50,
       1,   114,    55,   115,    82,   115,    57,    58,   104,   112,
     107,   110,    57,    58,   115,   112,   114,   114,   115,   109,
     115,   111,    73,   112,   112,   112,     1,   112,    73,   112,
      81,   115,    83,   115,   107,   112,    81,   112,    83,    14,
      15,    16,    17,    18,   112,     1,   112,   107,   109,   112,
     111,    52,    53,    54,    55,    56,   107,   107,    33,   107,
      61,   112,   107,   114,   115,    40,    41,    42,    43,    44,
      45,    46,     1,   112,   115,    50,   112,   115,     1,   112,
     108,    82,    57,    58,   108,    14,    15,    16,    17,    18,
       0,    14,    15,    16,    17,    18,    52,    53,    73,    55,
      56,    41,   112,   115,    33,   112,    81,   107,    83,    81,
      33,    40,    41,    42,    43,    44,    45,    46,    65,     1,
     112,    50,   115,    66,   115,   114,    82,    81,    57,    58,
      67,   115,   107,   112,    57,    58,    47,   112,   114,   114,
     115,    51,    66,    53,    73,    55,    56,   114,   112,    68,
      73,   112,    81,     1,    83,   114,   114,   112,    81,   112,
      83,     1,   108,   104,   112,   104,   115,   112,   112,    51,
      52,    53,     2,    55,    56,   191,   112,   115,   107,    61,
     115,   115,   115,   112,   107,   114,   115,     1,   115,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      82,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,     1,
      34,    35,    36,    37,    38,    39,     1,     1,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,   115,    34,
      35,    36,    37,    38,    39,   115,    97,   266,   287,   275,
      52,    53,   472,    55,    56,   399,   313,     3,    52,    53,
     456,    55,    56,   658,   659,   482,   633,   447,   663,   103,
     665,   105,   646,   570,   555,   109,   422,   111,   112,   654,
      82,    52,    53,    54,    55,    56,    12,   304,    82,    60,
     391,   358,   164,    13,   689,    -1,   691,   524,    -1,   527,
     607,    15,    16,    17,    18,    19,    20,   660,   103,    23,
     105,    82,    26,    27,   109,     1,   111,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      36,    37,    38,    39,     1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    -1,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    36,
      37,    38,    39,    -1,    -1,   109,    -1,   111,    -1,    -1,
      -1,    -1,    51,    52,    53,    -1,    55,    56,    -1,    -1,
      -1,    60,    -1,    -1,    -1,    -1,    -1,   103,    -1,   105,
      69,    70,    71,   109,   110,   111,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    82,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,    -1,    -1,    -1,   103,    -1,   105,    -1,
      -1,    -1,   109,   110,   111,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    -1,    34,    35,    36,    37,
      38,    39,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    -1,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    -1,    34,    35,    36,    37,    38,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   103,    -1,   105,    -1,    -1,
      -1,   109,    -1,   111,    -1,   113,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   103,    -1,   105,    -1,    -1,    -1,   109,    -1,
     111,   112,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    -1,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    -1,    34,    35,    36,    37,    38,    39,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    -1,
      34,    35,    36,    37,    38,    39,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   103,    -1,   105,    -1,    -1,    -1,   109,    -1,
     111,   112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   103,
      -1,   105,    -1,    -1,   108,   109,    -1,   111,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    34,
      35,    36,    37,    38,    39,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    -1,    34,    35,    36,    37,
      38,    39,    -1,    78,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   103,    -1,
     105,    -1,    -1,    -1,   109,    -1,   111,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   103,   104,   105,    -1,    -1,
      -1,   109,    -1,   111,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    -1,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    -1,    34,    35,    36,    37,    38,
      39,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    -1,    34,    35,    36,    37,    38,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   103,    -1,   105,    -1,    -1,    -1,
     109,   110,   111,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   103,   104,   105,    -1,    -1,    -1,   109,    -1,   111,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      -1,    34,    35,    36,    37,    38,    39,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,     0,    -1,    -1,    34,    35,
      36,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     103,    -1,   105,    -1,    -1,    -1,   109,    -1,   111,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    51,    -1,    53,    -1,
      55,    56,    -1,    -1,    -1,    60,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    69,    70,    71,   103,    -1,   105,
      -1,    -1,    -1,   109,    -1,   111,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    -1,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,     1,    -1,    -1,    -1,    34,    35,    36,
      37,    38,    39,    -1,     1,    -1,    14,    15,    16,    17,
      18,    -1,    -1,     1,    -1,    -1,    -1,    14,    15,    16,
      17,    18,    -1,    -1,     1,    33,    14,    15,    16,    17,
      18,    -1,    -1,    -1,    -1,    -1,    33,    14,    15,    16,
      17,    18,    -1,    -1,    -1,    33,    -1,    -1,    -1,    57,
      58,    -1,    -1,    -1,    -1,    -1,    33,    -1,    -1,    -1,
      57,    58,    -1,    -1,    -1,    73,   103,    -1,   105,    57,
      58,    -1,   109,    81,   111,    83,    73,    -1,    -1,    -1,
      57,    58,    -1,    -1,    81,    73,    83,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    -1,    83,    73,    -1,    -1,   107,
       1,    -1,    -1,    -1,    81,    -1,    83,     1,    -1,    -1,
     107,    -1,     1,    14,    15,    16,    17,    18,    -1,   107,
      14,    15,    16,    17,    18,    14,    15,    16,    17,    18,
     107,    -1,    33,    -1,    -1,    -1,    -1,    -1,    -1,    33,
      -1,    -1,    -1,    -1,    33,     1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    57,    58,    14,    15,
      16,    17,    18,    57,    58,    -1,    -1,    -1,    57,    58,
      -1,    -1,    73,    -1,    -1,    -1,    -1,    33,    -1,    73,
      81,    -1,    83,     1,    73,    -1,    -1,    81,    -1,    83,
      -1,    -1,    81,    -1,    83,    -1,    14,    15,    16,    17,
      18,    57,    58,    -1,    -1,    -1,   107,    -1,    -1,    -1,
      -1,    -1,    -1,   107,    -1,    33,     1,    73,   107,    -1,
      -1,     1,    -1,    -1,    -1,    81,    -1,    83,     1,    14,
      15,    16,    17,    18,    14,    15,    16,    17,    18,    57,
      58,    14,    15,    16,    17,    18,    -1,    -1,    33,    -1,
      -1,   107,    -1,    33,    -1,    73,    -1,    -1,    -1,    -1,
      33,    -1,    -1,    81,    -1,    83,    -1,    -1,    -1,    -1,
      -1,    -1,    57,    58,    -1,    -1,    -1,    57,    58,    -1,
      -1,    -1,    -1,    -1,    57,    58,    -1,    -1,    73,   107,
      -1,    -1,    -1,    73,    -1,    -1,    81,    -1,    83,    -1,
      73,    81,    -1,    83,    -1,    -1,    -1,    -1,    81,    -1,
      83,    14,    15,    16,    17,    18,    14,    15,    16,    17,
      18,    -1,   107,    -1,    -1,    -1,    -1,   107,    -1,    -1,
      33,    -1,    -1,    -1,   107,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    57,    58,    -1,    -1,    -1,    57,
      58,    -1,    14,    15,    16,    17,    18,    -1,    -1,    -1,
      73,    -1,    -1,    -1,    -1,    73,    -1,    -1,    81,    -1,
      83,    33,    -1,    81,    -1,    83,    -1,    -1,    40,    41,
      42,    43,    44,    45,    46,    -1,    -1,    -1,    50,    14,
      15,    16,    17,    18,   107,    57,    58,    -1,    -1,   107,
      -1,    -1,   115,    -1,    -1,    -1,    -1,   115,    33,    -1,
      -1,    73,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      -1,    83,    -1,    -1,    14,    15,    16,    17,    18,    -1,
      -1,    -1,    57,    58,    -1,    14,    15,    16,    17,    18,
      -1,    -1,    -1,    33,    -1,   107,    -1,    -1,    73,    -1,
     112,    -1,   114,    -1,    33,    -1,    81,    -1,    83,    -1,
      -1,    -1,    14,    15,    16,    17,    18,    57,    58,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,    58,
      -1,    33,   107,    73,   109,    -1,    -1,    -1,    -1,   114,
      -1,    81,    82,    83,    73,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    -1,    83,    57,    58,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   107,    -1,    -1,
      -1,    73,    -1,    -1,   114,    -1,    -1,    -1,   107,    81,
      -1,    83,    -1,    -1,    -1,   114,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   107,    -1,    -1,    -1,    -1,
     112,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    -1,    -1,    -1,    -1,
      34,    35,    36,    37,    38,    39,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      -1,    -1,    -1,    -1,    -1,    34,    35,    36,    37,    38,
      39,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    -1,    -1,    -1,    -1,    -1,    -1,
      34,    35,    36,    37,    38,    39,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   103,
      -1,   105,    -1,    -1,    -1,   109,    -1,   111,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    15,    16,    17,
      18,    19,    20,    21,    22,    23,   105,    25,    26,    27,
     109,    -1,   111,    -1,    -1,    -1,    34,    35,    36,    37,
      38,    39,    15,    16,    17,    18,    19,    20,    21,    22,
      23,   105,    -1,    26,    27,   109,    -1,   111,    -1,    -1,
      -1,    34,    35,    36,    37,    38,    39,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    -1,    -1,    26,    27,
      -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,    37,
      38,    39,    -1,    -1,    -1,    -1,    -1,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    -1,   105,    26,    27,
      -1,   109,    -1,   111,    -1,    -1,    34,    35,    -1,    -1,
      38,    39,    -1,    14,    15,    16,    17,    18,    -1,    -1,
      -1,    -1,   105,    -1,    -1,    -1,   109,    -1,   111,    -1,
      -1,    -1,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    14,    15,    16,    17,    18,    -1,    -1,    -1,    -1,
      -1,   109,    -1,   111,    -1,    -1,    57,    58,    -1,    -1,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    73,    74,    75,    76,    77,    -1,    79,    -1,
      81,   109,    83,   111,    57,    58,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      73,    -1,    -1,    -1,    -1,    -1,   107,    -1,    81,    -1,
      83,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   107
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     118,   119,   124,   124,   160,   120,     1,    59,   122,    53,
      55,    56,   135,   136,   148,   154,    14,    15,    16,    17,
      18,    33,    57,    58,    73,    81,    83,   107,   199,   203,
     205,   199,   171,   199,   198,   199,   207,   208,   208,   224,
     120,    54,   148,   220,   221,   222,     1,   199,   228,   199,
     234,   198,   235,   236,     0,    51,    60,    69,    70,    71,
     120,   125,   128,   129,   132,   137,   145,   148,   156,   132,
     137,   145,    81,     1,    81,   123,    56,   113,     1,    81,
     105,    52,    82,   199,   199,   199,   107,     1,   199,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    34,    35,
      36,    37,    38,    39,   103,   105,   109,   111,   204,   199,
       1,    14,   103,   113,    54,    60,   120,   137,   148,   209,
     213,   209,    81,    81,   112,   113,   113,     1,   113,   113,
      74,    75,    76,    77,    79,   199,   237,   238,     1,   148,
       1,    81,    82,   149,   114,   114,   114,   122,     1,   138,
     139,   149,     1,     3,   112,     1,   112,   113,     1,   136,
     144,    81,     1,   114,   109,   155,   200,   201,   108,   108,
     199,   199,   199,   199,   199,   199,   199,   199,   199,   199,
     199,   199,   199,   199,   199,   202,   199,   199,   199,   199,
     199,   199,   199,   199,     1,   199,    81,   199,    14,   103,
     199,     1,   210,     1,   149,   122,   149,   144,   144,     1,
     221,    81,    81,   113,   199,     1,   199,    78,   116,   199,
     112,     1,   146,   147,   149,   114,   107,   114,   134,   126,
     130,   131,   112,     1,   112,   113,   134,   144,   112,    81,
     112,     1,    81,   109,   144,     1,   148,   150,   151,     1,
     199,   199,   206,     1,   199,   104,   110,   110,   112,    81,
     211,   212,   114,     1,   107,   114,   219,   144,   144,   199,
     112,     1,   112,   113,   144,   159,   160,     1,   108,   135,
     158,     1,   114,    72,   115,   127,   115,   199,   203,   115,
     203,   112,   139,     1,   133,     3,   140,     1,   107,     1,
     199,   112,   115,     1,   149,   152,   153,     1,   115,   151,
     110,   113,   108,   113,   108,   199,   144,   112,   113,   217,
     114,     1,   108,   220,   218,     1,   114,   112,     1,   147,
     115,     1,    61,   161,   108,     1,   108,   159,   114,   157,
     104,   112,   112,   112,   115,   114,   114,   141,   199,   112,
       1,   121,   110,     1,   110,   112,   144,     1,   112,   113,
     199,     1,   199,   141,   212,   223,   224,   216,   108,     1,
     108,   223,   114,   214,   112,     1,    81,   162,   163,    55,
      62,   173,   174,   175,   108,   115,   159,   159,   199,   180,
      81,   141,   142,   143,   149,   108,   112,   206,   110,   112,
       1,   153,     1,   110,   115,     1,    61,   225,   223,   115,
     215,   223,   112,   114,     1,   112,   113,     1,    81,   177,
       1,    81,   176,     1,    63,   164,   175,   115,   115,   137,
     145,   181,   113,   115,   104,   112,   108,   110,     1,    81,
     226,   227,   173,   115,   223,   115,     1,   199,   112,     1,
     163,   112,     1,   112,   113,   112,     1,   112,   113,     1,
      81,     1,    64,   165,     1,    40,    41,    42,    43,    44,
      45,    46,    50,   112,   114,   115,   178,   182,   199,   143,
       1,   141,   112,   112,   114,     1,   112,   113,   164,   115,
     115,     1,   115,   112,     1,    81,   112,     1,    81,     1,
     112,     1,    81,   166,   167,   112,   107,   107,   185,   112,
     112,   107,   107,   112,   199,   179,   112,   228,   112,     1,
     227,     1,    64,   229,   115,   112,     1,    65,     1,   112,
     113,     1,   183,     1,   184,   182,   198,   186,   112,   180,
     115,     1,    81,   230,   231,   115,     1,    81,   112,     1,
      65,   167,   168,   108,   197,   198,   108,   198,    41,   108,
     198,   181,   112,     1,    65,     1,   112,   113,   115,     1,
     114,     1,    81,   182,   112,   182,   108,   107,   187,   108,
     115,    65,    81,   112,     1,    65,   231,   232,   115,    66,
     169,   115,     1,   114,   197,   182,   198,   114,   182,    81,
       1,   114,     1,    81,     1,   199,    67,   170,   115,   169,
     112,   108,    48,    49,   191,   192,    47,   188,   114,   114,
      66,   233,    81,   114,     1,   114,   112,     1,   112,     1,
     171,    68,   172,   170,   197,   112,     1,   199,     1,   104,
     115,   192,   189,   190,   233,   233,     1,   234,   170,   114,
     233,   114,   233,   112,   112,     1,   112,     1,   198,     1,
     115,   172,   108,   104,   104,   104,   195,   182,     1,   170,
     170,     1,   112,   172,   233,   170,   233,   170,   112,   112,
     112,   112,     1,   115,   182,   194,   193,   196,   181,   172,
     172,   112,     1,   115,   170,   172,   170,   172,   115,   181,
     181,   181,   115,   115,   115,   172,   115,   172,     1,   115,
     115,   115,   115
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
#line 266 "parser.yy"
    { CALL(yylsp[0], yylsp[0], done()); }
    break;

  case 3:
#line 267 "parser.yy"
    { }
    break;

  case 4:
#line 268 "parser.yy"
    { }
    break;

  case 5:
#line 269 "parser.yy"
    { }
    break;

  case 6:
#line 270 "parser.yy"
    { }
    break;

  case 7:
#line 271 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SYSTEM));
	}
    break;

  case 8:
#line 274 "parser.yy"
    { g_parameter_count = yyvsp[0].number; }
    break;

  case 9:
#line 275 "parser.yy"
    { }
    break;

  case 10:
#line 276 "parser.yy"
    { CALL(yylsp[0], yylsp[0], procGuard()); }
    break;

  case 11:
#line 277 "parser.yy"
    { }
    break;

  case 12:
#line 278 "parser.yy"
    { CALL(yylsp[0], yylsp[0], procUpdate()); }
    break;

  case 13:
#line 279 "parser.yy"
    { CALL(yylsp[0], yylsp[0], done()); }
    break;

  case 14:
#line 280 "parser.yy"
    { }
    break;

  case 15:
#line 281 "parser.yy"
    { }
    break;

  case 16:
#line 282 "parser.yy"
    { }
    break;

  case 17:
#line 283 "parser.yy"
    { g_parameter_count = yyvsp[0].number; }
    break;

  case 18:
#line 284 "parser.yy"
    { }
    break;

  case 19:
#line 285 "parser.yy"
    { CALL(yylsp[0], yylsp[0], procGuard()); }
    break;

  case 20:
#line 286 "parser.yy"
    { CALL(yylsp[0], yylsp[0], procUpdate()); }
    break;

  case 21:
#line 287 "parser.yy"
    {}
    break;

  case 24:
#line 296 "parser.yy"
    {
          CALL(yylsp[-3], yylsp[-1], instantiationBegin(yyvsp[-3].string, yyvsp[-1].string));
	}
    break;

  case 25:
#line 298 "parser.yy"
    {
	  CALL(yylsp[-7], yylsp[0], instantiationEnd(yyvsp[-7].string, yyvsp[-5].string, yyvsp[-2].number));
	}
    break;

  case 26:
#line 301 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_ARGLIST));
	}
    break;

  case 27:
#line 304 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));
	}
    break;

  case 28:
#line 307 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LPAREN));
	}
    break;

  case 29:
#line 310 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_ASSIGN));
	}
    break;

  case 31:
#line 317 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 32:
#line 320 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_PROCID));
	}
    break;

  case 33:
#line 326 "parser.yy"
    { CALL(yylsp[0], yylsp[0], process(yyvsp[0].string)); }
    break;

  case 34:
#line 327 "parser.yy"
    { CALL(yylsp[0], yylsp[0], process(yyvsp[0].string)); }
    break;

  case 35:
#line 328 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_PROCID_));
	}
    break;

  case 51:
#line 359 "parser.yy"
    {
	  CALL(yylsp[-1], yylsp[-1], beforeUpdate());
        }
    break;

  case 53:
#line 365 "parser.yy"
    {
	  CALL(yylsp[-1], yylsp[-1], afterUpdate());
        }
    break;

  case 54:
#line 370 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], declFuncBegin(yyvsp[-1].string, yyvsp[0].number));
	}
    break;

  case 55:
#line 373 "parser.yy"
    { 
	  CALL(yylsp[-7], yylsp[-1], declFuncEnd());
	}
    break;

  case 56:
#line 376 "parser.yy"
    {
	    CALL(yylsp[-4], yylsp[0], declFuncEnd());
	}
    break;

  case 57:
#line 382 "parser.yy"
    { yyval.number = 0; }
    break;

  case 58:
#line 383 "parser.yy"
    { yyval.number = yyvsp[-1].number; }
    break;

  case 59:
#line 384 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));
	  yyval.number = yyvsp[-2].number; 
	}
    break;

  case 60:
#line 388 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));
	  yyval.number = yyvsp[-1].number; 
	}
    break;

  case 61:
#line 392 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_PARAMETERS));
	  yyval.number = 0; 
	}
    break;

  case 62:
#line 396 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));
	  yyval.number = 0; 
	}
    break;

  case 63:
#line 408 "parser.yy"
    { yyval.number = 1; }
    break;

  case 64:
#line 409 "parser.yy"
    { yyval.number = yyvsp[-2].number+1; }
    break;

  case 65:
#line 410 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_PARAMETERS_));
	  yyval.number = yyvsp[-2].number;
	}
    break;

  case 66:
#line 417 "parser.yy"
    {
          CALL(yylsp[-3], yylsp[0], declParameter(yyvsp[-1].string, true, yyvsp[0].number));
          CALL(yylsp[-3], yylsp[0], declParameterEnd());
	}
    break;

  case 67:
#line 421 "parser.yy"
    {
          CALL(yylsp[-2], yylsp[0], declParameter(yyvsp[-1].string, false, yyvsp[0].number));
          CALL(yylsp[-2], yylsp[0], declParameterEnd());
	}
    break;

  case 68:
#line 425 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_PARAMID));
	}
    break;

  case 69:
#line 431 "parser.yy"
    { 
          CALL(yylsp[-2], yylsp[0], declVarEnd());
	}
    break;

  case 70:
#line 434 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
          CALL(yylsp[-3], yylsp[0], declVarEnd());
	}
    break;

  case 71:
#line 438 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_VARID));
	  CALL(yylsp[-2], yylsp[0], declVarEnd());
	}
    break;

  case 74:
#line 450 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], declVar(yyvsp[-2].string, yyvsp[-1].number, yyvsp[0].flag));
	}
    break;

  case 75:
#line 456 "parser.yy"
    { yyval.flag = false; }
    break;

  case 76:
#line 457 "parser.yy"
    { yyval.flag = true; }
    break;

  case 78:
#line 462 "parser.yy"
    {	
	  CALL(yylsp[-2], yylsp[0], declInitialiserList(yyvsp[-1].number));
	}
    break;

  case 79:
#line 468 "parser.yy"
    { yyval.number = 1; }
    break;

  case 80:
#line 469 "parser.yy"
    { yyval.number = yyvsp[-2].number+1; }
    break;

  case 81:
#line 473 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], declFieldInit(yyvsp[-2].string));
	}
    break;

  case 82:
#line 476 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_INITIAL));
	}
    break;

  case 83:
#line 479 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], declFieldInit(NULL));
	}
    break;

  case 84:
#line 485 "parser.yy"
    { yyval.number=0; }
    break;

  case 85:
#line 486 "parser.yy"
    { yyval.number=yyvsp[-3].number+1; }
    break;

  case 86:
#line 487 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RSQBRACE));
	  yyval.number=yyvsp[-4].number+1; 
	}
    break;

  case 87:
#line 491 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RSQBRACE));
	  yyval.number=yyvsp[-3].number+1; 
	}
    break;

  case 88:
#line 495 "parser.yy"
    {
	  CALL(yylsp[-1], yylsp[-1], exprNat(1));
	  REPORT_ERROR(last_loc, TypeException(PE_CONST_EXP));
	  yyval.number=yyvsp[-3].number+1; 
	}
    break;

  case 89:
#line 500 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], exprNat(1));
	  REPORT_ERROR(last_loc, TypeException(PE_CONST_EXP));
	  yyval.number=yyvsp[-2].number+1; 
	}
    break;

  case 90:
#line 508 "parser.yy"
    {
	  CALL(yylsp[-3], yylsp[0], declTypeDefEnd());
	}
    break;

  case 91:
#line 511 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-4], yylsp[0], declTypeDefEnd());
	}
    break;

  case 92:
#line 515 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_TYPEID));
	  CALL(yylsp[-3], yylsp[0], declTypeDefEnd());  
	}
    break;

  case 93:
#line 519 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_TYPE_DEF));
	  CALL(yylsp[-2], yylsp[0], declTypeDefEnd());  
	}
    break;

  case 94:
#line 531 "parser.yy"
    { yyval.number = 1; }
    break;

  case 95:
#line 532 "parser.yy"
    { yyval.number = yyvsp[-2].number+1; }
    break;

  case 96:
#line 533 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_TYPEID_));
	  yyval.number = yyvsp[-2].number+1; 
	}
    break;

  case 97:
#line 540 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], declTypeDef(yyvsp[-1].string, yyvsp[0].number));
	}
    break;

  case 98:
#line 546 "parser.yy"
    { 
	    CALL((yyvsp[-2].number == ParserBuilder::PREFIX_NONE ? yylsp[-1] : yylsp[-2]), yylsp[0],
		 typeName(yyvsp[-2].number, yyvsp[-1].string, yyvsp[0].flag));
	}
    break;

  case 99:
#line 550 "parser.yy"
    { 
	    CALL((yyvsp[-4].number == ParserBuilder::PREFIX_NONE ? yylsp[-3] : yylsp[-4]), yylsp[0],
	       typeStruct(yyvsp[-4].number, yyvsp[-1].number));
	}
    break;

  case 100:
#line 554 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBER));
	  CALL((yyvsp[-4].number == ParserBuilder::PREFIX_NONE ? yylsp[-3] : yylsp[-4]), yylsp[0],
	       typeStruct(yyvsp[-4].number, 0));
	}
    break;

  case 101:
#line 559 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  CALL((yyvsp[-3].number == ParserBuilder::PREFIX_NONE ? yylsp[-2] : yylsp[-3]), yylsp[0],
	       typeStruct(yyvsp[-3].number, 0));
	}
    break;

  case 102:
#line 564 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	}
    break;

  case 103:
#line 570 "parser.yy"
    { strncpy(yyval.string, yyvsp[0].string, MAXLEN); }
    break;

  case 104:
#line 571 "parser.yy"
    { strncpy(yyval.string, yyvsp[0].string, MAXLEN); }
    break;

  case 105:
#line 575 "parser.yy"
    { yyval.number=yyvsp[0].number; }
    break;

  case 106:
#line 576 "parser.yy"
    { yyval.number=yyvsp[-1].number+yyvsp[0].number; }
    break;

  case 107:
#line 577 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBER));
	  yyval.number=yyvsp[-1].number; 
	}
    break;

  case 108:
#line 584 "parser.yy"
    {
	  yyval.number = yyvsp[-1].number; 
	  CALL(yylsp[-2], yylsp[0], structFieldEnd());
	}
    break;

  case 109:
#line 588 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));	  
	  yyval.number = yyvsp[-2].number; 
	  CALL(yylsp[-3], yylsp[0], structFieldEnd());
	}
    break;

  case 110:
#line 593 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBERID));	  
	}
    break;

  case 111:
#line 596 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBERID));	  
	}
    break;

  case 112:
#line 599 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBERTYPE));	  
	}
    break;

  case 113:
#line 605 "parser.yy"
    { yyval.number=1; }
    break;

  case 114:
#line 606 "parser.yy"
    { yyval.number=yyvsp[-2].number+1; }
    break;

  case 115:
#line 607 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBERID_));
	  yyval.number=yyvsp[-2].number+1; 
	}
    break;

  case 116:
#line 614 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], structField(yyvsp[-1].string, yyvsp[0].number));
	}
    break;

  case 117:
#line 620 "parser.yy"
    { yyval.number = ParserBuilder::PREFIX_NONE; }
    break;

  case 118:
#line 621 "parser.yy"
    { yyval.number = ParserBuilder::PREFIX_URGENT; }
    break;

  case 119:
#line 622 "parser.yy"
    { yyval.number = ParserBuilder::PREFIX_BROADCAST; }
    break;

  case 120:
#line 623 "parser.yy"
    { yyval.number = ParserBuilder::PREFIX_URGENT_BROADCAST; }
    break;

  case 121:
#line 624 "parser.yy"
    { yyval.number = ParserBuilder::PREFIX_CONST; }
    break;

  case 122:
#line 628 "parser.yy"
    { yyval.flag = false; }
    break;

  case 123:
#line 629 "parser.yy"
    { yyval.flag = true; }
    break;

  case 124:
#line 630 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RSQBRACE));
	  yyval.flag = true; 
	}
    break;

  case 125:
#line 634 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RSQBRACE));
	  yyval.flag = true; 
	}
    break;

  case 126:
#line 638 "parser.yy"
    {
	    yyval.flag = false;
        }
    break;

  case 127:
#line 648 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[0], procBegin(yyvsp[-2].string, yyvsp[-1].number));
	}
    break;

  case 128:
#line 651 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], procEnd());
	}
    break;

  case 129:
#line 654 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	}
    break;

  case 130:
#line 657 "parser.yy"
    {
	  utap_error(TypeException(PE_LPAREN), 
		     yylsp[0].first_line, yylsp[0].first_column, 
		     yylsp[0].last_line, yylsp[0].last_column);
	  CALL(yylsp[-2], yylsp[0], procBegin(yyvsp[-1].string, 0));
	}
    break;

  case 131:
#line 662 "parser.yy"
    {
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;

  case 132:
#line 665 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_PROCID));	  
	}
    break;

  case 139:
#line 687 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 140:
#line 690 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 141:
#line 693 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATE_DECL));
	}
    break;

  case 142:
#line 696 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATE_DECL));
	}
    break;

  case 143:
#line 699 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATE));
	}
    break;

  case 146:
#line 707 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATE_DECL_));
	}
    break;

  case 147:
#line 713 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], procState(yyvsp[0].string, false));
	}
    break;

  case 148:
#line 716 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[0], procState(yyvsp[-3].string, true));
	}
    break;

  case 149:
#line 719 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	  CALL(yylsp[-4], yylsp[0], procState(yyvsp[-4].string, true));
	}
    break;

  case 150:
#line 723 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	  CALL(yylsp[-3], yylsp[0], procState(yyvsp[-3].string, true));
	}
    break;

  case 151:
#line 727 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_INV));
	  CALL(yylsp[-3], yylsp[0], procState(yyvsp[-3].string, false));
	}
    break;

  case 152:
#line 731 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_INV));
	  CALL(yylsp[-2], yylsp[0], procState(yyvsp[-2].string, false));
	}
    break;

  case 153:
#line 738 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], procStateInit(yyvsp[-1].string));
	}
    break;

  case 154:
#line 741 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-3], yylsp[0], procStateInit(yyvsp[-2].string));
	}
    break;

  case 155:
#line 745 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-2], yylsp[0], procStateInit(yyvsp[-1].string));
	}
    break;

  case 156:
#line 749 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;

  case 157:
#line 752 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_INIT));
	}
    break;

  case 160:
#line 760 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 161:
#line 763 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 162:
#line 766 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS_DECL));
	}
    break;

  case 163:
#line 769 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS));
	}
    break;

  case 166:
#line 777 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS_DECL_));
	}
    break;

  case 167:
#line 783 "parser.yy"
    { 
	  strcpy(rootTransId, yyvsp[-7].string); 
	  CALL(yylsp[-7], yylsp[0], procTransition(yyvsp[-7].string, yyvsp[-5].string));
	}
    break;

  case 168:
#line 787 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  strcpy(rootTransId, yyvsp[-8].string); 
	  CALL(yylsp[-8], yylsp[0], procTransition(yyvsp[-8].string, yyvsp[-6].string));
	}
    break;

  case 169:
#line 792 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	}
    break;

  case 170:
#line 795 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;

  case 171:
#line 798 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_ARROW));
	}
    break;

  case 172:
#line 804 "parser.yy"
    { 
	  CALL(yylsp[-6], yylsp[0], procTransition(rootTransId, yyvsp[-5].string));
	}
    break;

  case 173:
#line 807 "parser.yy"
    { 
	  REPORT_ERROR(yylloc, TypeException(PE_RBRACE));
	  CALL(yylsp[-7], yylsp[0], procTransition(rootTransId, yyvsp[-6].string));
	}
    break;

  case 174:
#line 811 "parser.yy"
    { 
	  REPORT_ERROR(yylloc, TypeException(PE_LBRACE));
	}
    break;

  case 175:
#line 814 "parser.yy"
    { 
	  REPORT_ERROR(yylloc, TypeException(PE_STATEID));
	}
    break;

  case 178:
#line 823 "parser.yy"
    {
	  CALL(yylsp[-1], yylsp[-1], procGuard());
        }
    break;

  case 179:
#line 826 "parser.yy"
    {
	  REPORT_ERROR(yylloc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-2], yylsp[-1], procGuard());
	}
    break;

  case 180:
#line 830 "parser.yy"
    {
	  REPORT_ERROR(yylloc, TypeException(PE_GUARD_EXP));
	}
    break;

  case 183:
#line 838 "parser.yy"
    {
	  REPORT_ERROR(yylloc, TypeException(PE_SEMICOLON));
	}
    break;

  case 184:
#line 841 "parser.yy"
    {
	  REPORT_ERROR(yylloc, TypeException(PE_SEMICOLON));
	}
    break;

  case 185:
#line 844 "parser.yy"
    {
	  REPORT_ERROR(yylloc, TypeException(PE_SYNC_EXP));
	}
    break;

  case 186:
#line 850 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], procSync(SYNC_BANG));
	}
    break;

  case 187:
#line 853 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_BANG));
	  CALL(yylsp[-2], yylsp[-1], procSync(SYNC_QUE));
	}
    break;

  case 188:
#line 857 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], procSync(SYNC_QUE));
	}
    break;

  case 189:
#line 860 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_QUE));
	  CALL(yylsp[-2], yylsp[-1], procSync(SYNC_QUE));
	}
    break;

  case 190:
#line 864 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_BANGQUE));
	  CALL(yylsp[-1], yylsp[0], procSync(SYNC_QUE));
	}
    break;

  case 192:
#line 872 "parser.yy"
    {
	  CALL(yylsp[-1], yylsp[-1], procUpdate());	  
	}
    break;

  case 193:
#line 875 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_ASSIGN_EXP));
	}
    break;

  case 199:
#line 889 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 200:
#line 892 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 201:
#line 895 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;

  case 202:
#line 898 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;

  case 203:
#line 904 "parser.yy"
    {}
    break;

  case 204:
#line 905 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 205:
#line 908 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 206:
#line 911 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;

  case 207:
#line 914 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;

  case 208:
#line 920 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], procStateCommit(yyvsp[0].string));
	}
    break;

  case 209:
#line 923 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], procStateCommit(yyvsp[0].string));
	}
    break;

  case 210:
#line 926 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID_));
	}
    break;

  case 211:
#line 932 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], procStateUrgent(yyvsp[0].string));
	}
    break;

  case 212:
#line 935 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], procStateUrgent(yyvsp[0].string));
	}
    break;

  case 213:
#line 938 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID_));
	}
    break;

  case 214:
#line 949 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], blockBegin());
	}
    break;

  case 215:
#line 952 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[-1], blockEnd());
	}
    break;

  case 223:
#line 971 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], emptyStatement());
	}
    break;

  case 224:
#line 974 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], exprStatement());
	}
    break;

  case 225:
#line 977 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], forBegin());
	}
    break;

  case 226:
#line 980 "parser.yy"
    { 
	    CALL(yylsp[-7], yylsp[-1], forEnd());
	  }
    break;

  case 228:
#line 984 "parser.yy"
    {
	    CALL(yylsp[-1], yylsp[0], whileBegin());
	}
    break;

  case 229:
#line 987 "parser.yy"
    { 
	    CALL(yylsp[-3], yylsp[-2], whileEnd());
	  }
    break;

  case 231:
#line 991 "parser.yy"
    { 
	    CALL(yylsp[0], yylsp[0], doWhileBegin());
	}
    break;

  case 232:
#line 994 "parser.yy"
    { 
	    CALL(yylsp[-6], yylsp[-1], doWhileEnd());
	  }
    break;

  case 233:
#line 997 "parser.yy"
    { 
	    CALL(yylsp[-1], yylsp[0], ifBegin());
	}
    break;

  case 235:
#line 1001 "parser.yy"
    { 
	    CALL(yylsp[-1], yylsp[0], breakStatement());
	  }
    break;

  case 236:
#line 1004 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], continueStatement());
	}
    break;

  case 237:
#line 1007 "parser.yy"
    { 
	    CALL(yylsp[-3], yylsp[0], switchBegin());
	}
    break;

  case 238:
#line 1010 "parser.yy"
    { 
	       CALL(yylsp[-3], yylsp[-1], switchEnd());
	   }
    break;

  case 239:
#line 1013 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], returnStatement(true));
	}
    break;

  case 240:
#line 1016 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], returnStatement(false));
	}
    break;

  case 241:
#line 1022 "parser.yy"
    { 
	  CALL(position_t(), position_t(), ifEnd(false));
	}
    break;

  case 242:
#line 1025 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], ifElse());
	}
    break;

  case 243:
#line 1028 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[-1], ifEnd(true));
	  }
    break;

  case 244:
#line 1031 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], ifElse());
	}
    break;

  case 245:
#line 1034 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-1], yylsp[-1], ifEnd(true));
	  }
    break;

  case 248:
#line 1046 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], caseBegin());
	}
    break;

  case 249:
#line 1049 "parser.yy"
    { 
	    CALL(yylsp[-1], yylsp[-1], caseEnd());
	  }
    break;

  case 250:
#line 1052 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], caseBegin());
	}
    break;

  case 251:
#line 1055 "parser.yy"
    {
	    REPORT_ERROR(last_loc, TypeException(PE_EXPR)); 
	    CALL(yylsp[-1], yylsp[-1], caseEnd());
	  }
    break;

  case 252:
#line 1059 "parser.yy"
    { 
	    CALL(yylsp[-1], yylsp[0], defaultBegin());
	}
    break;

  case 253:
#line 1062 "parser.yy"
    { 
	    CALL(yylsp[-1], yylsp[-1], defaultEnd());
	  }
    break;

  case 254:
#line 1065 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_COLON)); 
	  CALL(yylsp[-2], yylsp[0], defaultBegin());
	}
    break;

  case 255:
#line 1069 "parser.yy"
    { 
	    CALL(yylsp[-1], yylsp[-1], defaultEnd());
	  }
    break;

  case 259:
#line 1081 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprComma());
	}
    break;

  case 260:
#line 1086 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], exprFalse());
	}
    break;

  case 261:
#line 1089 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], exprTrue());
	}
    break;

  case 262:
#line 1092 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], exprNat(yyvsp[0].number));
	}
    break;

  case 263:
#line 1095 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], exprId(yyvsp[0].string));
	}
    break;

  case 264:
#line 1098 "parser.yy"
    {
	    CALL(yylsp[-1], yylsp[0], exprCallBegin(yyvsp[-1].string));	    
	  }
    break;

  case 265:
#line 1100 "parser.yy"
    { 
	    CALL(yylsp[-4], yylsp[0], exprCallEnd(yyvsp[-1].number));
	}
    break;

  case 266:
#line 1103 "parser.yy"
    {
	    CALL(yylsp[-1], yylsp[0], exprCallBegin(yyvsp[-1].string));
	  }
    break;

  case 267:
#line 1105 "parser.yy"
    {   
	    REPORT_ERROR(last_loc, TypeException(PE_ARGLIST));
	    CALL(yylsp[-4], yylsp[0], exprCallEnd(0));
	}
    break;

  case 268:
#line 1109 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[0], exprArray());
	}
    break;

  case 269:
#line 1112 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-3], yylsp[0], exprFalse());
	}
    break;

  case 271:
#line 1117 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprFalse());
	}
    break;

  case 272:
#line 1121 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], exprPostIncrement());
	}
    break;

  case 273:
#line 1124 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], exprPreIncrement());
	}
    break;

  case 274:
#line 1127 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], exprPostDecrement());
	}
    break;

  case 275:
#line 1130 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], exprPreDecrement());
	}
    break;

  case 276:
#line 1133 "parser.yy"
    { 
	  CALL(yylsp[-1], yylsp[0], exprUnary(yyvsp[-1].kind));
	}
    break;

  case 277:
#line 1136 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(LT));
	}
    break;

  case 278:
#line 1139 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(LE));
	}
    break;

  case 279:
#line 1142 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(EQ));
	}
    break;

  case 280:
#line 1145 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(NEQ));
	}
    break;

  case 281:
#line 1148 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(GT));
	}
    break;

  case 282:
#line 1151 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(GE));
	}
    break;

  case 283:
#line 1154 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(PLUS));
	}
    break;

  case 284:
#line 1157 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(MINUS));
	}
    break;

  case 285:
#line 1160 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(MULT));
	}
    break;

  case 286:
#line 1163 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(DIV));
	}
    break;

  case 287:
#line 1166 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(MOD));
	}
    break;

  case 288:
#line 1169 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_AND));
	}
    break;

  case 289:
#line 1172 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_OR));
	}
    break;

  case 290:
#line 1175 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_XOR));
	}
    break;

  case 291:
#line 1178 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_LSHIFT));
	}
    break;

  case 292:
#line 1181 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_RSHIFT));
	}
    break;

  case 293:
#line 1184 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(AND));
	}
    break;

  case 294:
#line 1187 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(OR));
	}
    break;

  case 295:
#line 1190 "parser.yy"
    { 
	  CALL(yylsp[-4], yylsp[0], exprInlineIf());
	}
    break;

  case 296:
#line 1193 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprDot(yyvsp[0].string));
	}
    break;

  case 297:
#line 1196 "parser.yy"
    {
	  CALL(yylsp[0], yylsp[0], exprDeadlock());
	}
    break;

  case 298:
#line 1199 "parser.yy"
    {  
	  CALL(yylsp[-1], yylsp[-1], exprUnary(NOT));
	}
    break;

  case 299:
#line 1201 "parser.yy"
    {
	  CALL(yylsp[-1], yylsp[-1], exprBinary(OR));
	}
    break;

  case 300:
#line 1204 "parser.yy"
    {
	  CALL(yylsp[-2], yylsp[0], exprBinary(AND));
        }
    break;

  case 301:
#line 1207 "parser.yy"
    {
	  CALL(yylsp[-2], yylsp[0], exprBinary(OR));
        }
    break;

  case 302:
#line 1210 "parser.yy"
    {
	  CALL(yylsp[-1], yylsp[0], exprUnary(NOT));
        }
    break;

  case 303:
#line 1213 "parser.yy"
    {
	    CALL(yylsp[-2], yylsp[0], exprBinary(MIN));
        }
    break;

  case 304:
#line 1216 "parser.yy"
    {
	    CALL(yylsp[-2], yylsp[0], exprBinary(MAX));
        }
    break;

  case 306:
#line 1223 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprAssignment(yyvsp[-1].kind));
	}
    break;

  case 307:
#line 1229 "parser.yy"
    { yyval.kind = ASSIGN; }
    break;

  case 308:
#line 1230 "parser.yy"
    { yyval.kind = ASSPLUS; }
    break;

  case 309:
#line 1231 "parser.yy"
    { yyval.kind = ASSMINUS; }
    break;

  case 310:
#line 1232 "parser.yy"
    { yyval.kind = ASSDIV; }
    break;

  case 311:
#line 1233 "parser.yy"
    { yyval.kind = ASSMOD; }
    break;

  case 312:
#line 1234 "parser.yy"
    { yyval.kind = ASSMULT; }
    break;

  case 313:
#line 1235 "parser.yy"
    { yyval.kind = ASSAND; }
    break;

  case 314:
#line 1236 "parser.yy"
    { yyval.kind = ASSOR; }
    break;

  case 315:
#line 1237 "parser.yy"
    { yyval.kind = ASSXOR; }
    break;

  case 316:
#line 1238 "parser.yy"
    { yyval.kind = ASSLSHIFT; }
    break;

  case 317:
#line 1239 "parser.yy"
    { yyval.kind = ASSRSHIFT; }
    break;

  case 318:
#line 1244 "parser.yy"
    { yyval.kind = MINUS; }
    break;

  case 319:
#line 1245 "parser.yy"
    { yyval.kind = PLUS; }
    break;

  case 320:
#line 1246 "parser.yy"
    { yyval.kind = NOT; }
    break;

  case 321:
#line 1251 "parser.yy"
    { yyval.number=0; }
    break;

  case 322:
#line 1252 "parser.yy"
    { 
	    yyval.number=1; 
	    CALL(yylsp[0], yylsp[0], exprArg(yyval.number));
	}
    break;

  case 323:
#line 1256 "parser.yy"
    { 
	    yyval.number=yyvsp[-2].number+1; 
	    CALL(yylsp[0], yylsp[0], exprArg(yyval.number));
	}
    break;

  case 324:
#line 1260 "parser.yy"
    { 
	  yyval.number=yyvsp[-2].number+1; 
	  REPORT_ERROR(last_loc, TypeException(PE_ARGLIST_));
	  CALL(yylsp[0], yylsp[0], exprArg(yyval.number));
	}
    break;

  case 330:
#line 1283 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], typeName(ParserBuilder::PREFIX_CONST, "int", 0));
	}
    break;

  case 331:
#line 1285 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[-1], declVarEnd());
	}
    break;

  case 333:
#line 1291 "parser.yy"
    { yyval.number=1; }
    break;

  case 334:
#line 1292 "parser.yy"
    { yyval.number=yyvsp[-2].number+1; }
    break;

  case 335:
#line 1296 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], declVar(yyvsp[-2].string, yyvsp[-1].number, true));
	}
    break;

  case 336:
#line 1305 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[0], procBegin(yyvsp[-2].string, yyvsp[-1].number));
	}
    break;

  case 337:
#line 1308 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;

  case 338:
#line 1311 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	  CALL(yylsp[-4], yylsp[0], procBegin(yyvsp[-3].string, yyvsp[-2].number));
	}
    break;

  case 339:
#line 1315 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;

  case 340:
#line 1318 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACES));
	  CALL(yylsp[-3], yylsp[0], procBegin(yyvsp[-2].string, 0));
	}
    break;

  case 341:
#line 1322 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;

  case 342:
#line 1325 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_PROCID));
	  CALL(yylsp[-2], yylsp[0], procBegin("_", 0));
	}
    break;

  case 343:
#line 1329 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;

  case 344:
#line 1332 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], procBegin(yyvsp[-1].string, 0));
	}
    break;

  case 345:
#line 1335 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;

  case 346:
#line 1341 "parser.yy"
    { yyval.number = 0; }
    break;

  case 347:
#line 1342 "parser.yy"
    { yyval.number = yyvsp[-1].number; }
    break;

  case 348:
#line 1343 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));	  
	  yyval.number = yyvsp[-1].number; 
	}
    break;

  case 349:
#line 1347 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_PARAMETERS));	  
	  yyval.number = 0; 
	}
    break;

  case 350:
#line 1354 "parser.yy"
    { 
	  yyval.number = yyvsp[0].number; 
	  CALL(yylsp[0], yylsp[0], declParameterEnd());
	}
    break;

  case 351:
#line 1358 "parser.yy"
    { 
	  yyval.number = yyvsp[0].number; 
	  CALL(yylsp[0], yylsp[0], declParameterEnd());
	}
    break;

  case 352:
#line 1362 "parser.yy"
    { 
	  yyval.number = yyvsp[-2].number + yyvsp[0].number;
	  CALL(yylsp[-2], yylsp[0], declParameterEnd());
	}
    break;

  case 353:
#line 1366 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_PARAM_DECL_));
          yyval.number = yyvsp[-2].number; 
	}
    break;

  case 354:
#line 1373 "parser.yy"
    {
          CALL(yylsp[-2], yylsp[0], declParameter(yyvsp[-1].string, yyvsp[0].number == 0, yyvsp[0].number));
	  yyval.number = 1;
	}
    break;

  case 355:
#line 1377 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[0], declParameter(yyvsp[-1].string, yyvsp[0].number == 0, yyvsp[0].number));
	  yyval.number = yyvsp[-3].number + 1;
	}
    break;

  case 356:
#line 1384 "parser.yy"
    {
	  CALL(yylsp[-2], yylsp[-2], typeName(ParserBuilder::PREFIX_CONST, "int", false));
	  CALL(yylsp[-1], yylsp[0], declParameter(yyvsp[-1].string, false, yyvsp[0].number));
	  yyval.number = 1;
	}
    break;

  case 357:
#line 1389 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[0], declParameter(yyvsp[-1].string, false, yyvsp[0].number));
	  yyval.number = yyvsp[-3].number + 1;
	}
    break;

  case 362:
#line 1406 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 363:
#line 1409 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 364:
#line 1412 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATE_DECL));
	}
    break;

  case 365:
#line 1415 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATE_DECL));
	}
    break;

  case 366:
#line 1418 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_STATE));
	}
    break;

  case 369:
#line 1426 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_LOC_DECL));
	}
    break;

  case 370:
#line 1432 "parser.yy"
    { 
	  CALL(yylsp[0], yylsp[0], exprTrue(); ch->procState(yyvsp[0].string, false));
	}
    break;

  case 371:
#line 1435 "parser.yy"
    { 
	  CALL(yylsp[-3], yylsp[0], procState(yyvsp[-3].string, true));
	}
    break;

  case 373:
#line 1442 "parser.yy"
    {	  
	  REPORT_ERROR(last_loc, TypeException(PE_INV));
	}
    break;

  case 374:
#line 1445 "parser.yy"
    {	  
	  REPORT_ERROR(last_loc, TypeException(PE_INV));
	  CALL(yylsp[0], yylsp[0], exprTrue());
	}
    break;

  case 375:
#line 1449 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(AND));
	}
    break;

  case 378:
#line 1457 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 379:
#line 1460 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;

  case 380:
#line 1463 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS_DECL));
	}
    break;

  case 381:
#line 1466 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS_DECL));
	}
    break;

  case 382:
#line 1469 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS));
	}
    break;

  case 385:
#line 1477 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_ALT_TRANS));	  
	}
    break;

  case 386:
#line 1483 "parser.yy"
    { 
	  strcpy(rootTransId, yyvsp[-7].string);
	  CALL(yylsp[-7], yylsp[0], procTransition(yyvsp[-7].string, yyvsp[-5].string));
	}
    break;

  case 387:
#line 1487 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  strcpy(rootTransId, yyvsp[-8].string);
	  CALL(yylsp[-8], yylsp[0], procTransition(yyvsp[-8].string, yyvsp[-6].string));
	}
    break;

  case 388:
#line 1492 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  strcpy(rootTransId, yyvsp[-7].string); 
	  CALL(yylsp[-7], yylsp[0], procTransition(yyvsp[-7].string, yyvsp[-5].string));
	}
    break;

  case 389:
#line 1497 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	  strcpy(rootTransId, yyvsp[-8].string); 
	  CALL(yylsp[-8], yylsp[0], procTransition(yyvsp[-8].string, yyvsp[-6].string));
	}
    break;

  case 390:
#line 1502 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_ARROW));
	  strcpy(rootTransId, yyvsp[-8].string); 
	  CALL(yylsp[-8], yylsp[0], procTransition(yyvsp[-8].string, yyvsp[-5].string));
	}
    break;

  case 391:
#line 1511 "parser.yy"
    { 
	  CALL(yylsp[-6], yylsp[0], procTransition(rootTransId, yyvsp[-5].string));
	}
    break;

  case 392:
#line 1514 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  CALL(yylsp[-6], yylsp[0], procTransition(rootTransId, yyvsp[-5].string));
	}
    break;

  case 393:
#line 1518 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  CALL(yylsp[-7], yylsp[0], procTransition(rootTransId, yyvsp[-6].string));
	}
    break;

  case 394:
#line 1522 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	  CALL(yylsp[-7], yylsp[0], procTransition(rootTransId, yyvsp[-6].string));
	}
    break;

  case 395:
#line 1526 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	  CALL(yylsp[-7], yylsp[0], procTransition(rootTransId, yyvsp[-5].string));
	}
    break;

  case 396:
#line 1530 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	  CALL(yylsp[-6], yylsp[0], procTransition(rootTransId, "_"));
	}
    break;

  case 399:
#line 1539 "parser.yy"
    {
	  CALL(yylsp[-1], yylsp[-1], procGuard());
	}
    break;

  case 400:
#line 1542 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-2], yylsp[-1], procGuard());
	}
    break;

  case 401:
#line 1546 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-1], yylsp[0], procGuard());
	}
    break;

  case 402:
#line 1550 "parser.yy"
    {
	  REPORT_ERROR(last_loc, TypeException(PE_GUARD_EXP));
	}
    break;

  case 404:
#line 1557 "parser.yy"
    { 
	  CALL(yylsp[-2], yylsp[0], exprBinary(AND));
	}
    break;

  case 405:
#line 1560 "parser.yy"
    { 
	  REPORT_ERROR(last_loc, TypeException(PE_GUARD_EXP_));
	  CALL(yylsp[-2], yylsp[0], exprBinary(AND));
	}
    break;

  case 410:
#line 1575 "parser.yy"
    {
		ch->quit();	
	}
    break;

  case 411:
#line 1578 "parser.yy"
    {
		ch->property(yyvsp[-1].kind, yylsp[-1].first_line);
	}
    break;

  case 412:
#line 1581 "parser.yy"
    {
		ch->property(LEADSTO, yylsp[-2].first_line);
	}
    break;

  case 413:
#line 1586 "parser.yy"
    { yyval.kind = EF; }
    break;

  case 414:
#line 1587 "parser.yy"
    { yyval.kind = EG; }
    break;

  case 415:
#line 1588 "parser.yy"
    { yyval.kind = AF; }
    break;

  case 416:
#line 1589 "parser.yy"
    { yyval.kind = AG; }
    break;


    }

/* Line 999 of yacc.c.  */
#line 4794 "parser.tab.c"

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


#line 1591 "parser.yy"


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

  utap__scan_string(str);

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
  utap__delete_buffer(YY_CURRENT_BUFFER);

  ch = NULL;
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

  utap__switch_to_buffer(utap__create_buffer(file, YY_BUF_SIZE));
  
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

  utap__delete_buffer(YY_CURRENT_BUFFER);
  ch = NULL;

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

  utap__scan_string(str);

  int res = utap_parse();

  utap__delete_buffer(YY_CURRENT_BUFFER);
  ch = NULL;

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

  utap__switch_to_buffer(utap__create_buffer(file, YY_BUF_SIZE));

  int res = utap_parse();

  utap__delete_buffer(YY_CURRENT_BUFFER);
  ch = NULL;

  return (res ? -1 : 0);
}



