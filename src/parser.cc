/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.3.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         utap_parse
#define yylex           utap_lex
#define yyerror         utap_error
#define yydebug         utap_debug
#define yynerrs         utap_nerrs

#define yylval          utap_lval
#define yychar          utap_char
#define yylloc          utap_lloc

/* First part of user prologue.  */
#line 40 "parser.yy" /* yacc.c:337  */


#include "libparser.h"
#include "utap/position.h"

#include <cstring>

using namespace std;
using namespace UTAP;
using namespace Constants;

#define YYLLOC_DEFAULT(Current, Rhs, N)			  	        \
    do									\
      if (N)								\
	{								\
	  (Current).start        = YYRHSLOC (Rhs, 1).start;	        \
	  (Current).end          = YYRHSLOC (Rhs, N).end;	        \
	}								\
      else								\
	{								\
	  (Current).start        = (Current).end   =		        \
	    YYRHSLOC (Rhs, 0).end;			  	        \
	}								\
    while (0)

#define YYLTYPE position_t

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

#define YYERROR_VERBOSE 1

#define CALL(first,last,call) do { ch->setPosition(first.start, last.end); try { ch->call; } catch (TypeException &te) { ch->handleError(te.what()); } } while (0)


#line 136 "parser.tab.c" /* yacc.c:337  */
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int utap_debug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
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
    T_EXISTS = 290,
    T_LT = 291,
    T_LEQ = 292,
    T_EQ = 293,
    T_NEQ = 294,
    T_GEQ = 295,
    T_GT = 296,
    T_FOR = 297,
    T_WHILE = 298,
    T_DO = 299,
    T_BREAK = 300,
    T_CONTINUE = 301,
    T_SWITCH = 302,
    T_IF = 303,
    T_ELSE = 304,
    T_CASE = 305,
    T_DEFAULT = 306,
    T_RETURN = 307,
    T_PRIORITY = 308,
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
    T_ERROR = 341,
    T_ID = 342,
    T_TYPENAME = 343,
    T_NAT = 344,
    T_BOOL = 345,
    T_INT = 346,
    T_CHAN = 347,
    T_CLOCK = 348,
    T_VOID = 349,
    T_SCALAR = 350,
    T_NEW = 351,
    T_NEW_DECLARATION = 352,
    T_NEW_LOCAL_DECL = 353,
    T_NEW_INST = 354,
    T_NEW_SYSTEM = 355,
    T_NEW_PARAMETERS = 356,
    T_NEW_INVARIANT = 357,
    T_NEW_GUARD = 358,
    T_NEW_SYNC = 359,
    T_NEW_ASSIGN = 360,
    T_NEW_SELECT = 361,
    T_OLD = 362,
    T_OLD_DECLARATION = 363,
    T_OLD_LOCAL_DECL = 364,
    T_OLD_INST = 365,
    T_OLD_PARAMETERS = 366,
    T_OLD_INVARIANT = 367,
    T_OLD_GUARD = 368,
    T_OLD_ASSIGN = 369,
    T_PROPERTY = 370,
    T_EXPRESSION = 371,
    UOPERATOR = 372
  };
#endif
/* Tokens.  */
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
#define T_EXISTS 290
#define T_LT 291
#define T_LEQ 292
#define T_EQ 293
#define T_NEQ 294
#define T_GEQ 295
#define T_GT 296
#define T_FOR 297
#define T_WHILE 298
#define T_DO 299
#define T_BREAK 300
#define T_CONTINUE 301
#define T_SWITCH 302
#define T_IF 303
#define T_ELSE 304
#define T_CASE 305
#define T_DEFAULT 306
#define T_RETURN 307
#define T_PRIORITY 308
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
#define T_ERROR 341
#define T_ID 342
#define T_TYPENAME 343
#define T_NAT 344
#define T_BOOL 345
#define T_INT 346
#define T_CHAN 347
#define T_CLOCK 348
#define T_VOID 349
#define T_SCALAR 350
#define T_NEW 351
#define T_NEW_DECLARATION 352
#define T_NEW_LOCAL_DECL 353
#define T_NEW_INST 354
#define T_NEW_SYSTEM 355
#define T_NEW_PARAMETERS 356
#define T_NEW_INVARIANT 357
#define T_NEW_GUARD 358
#define T_NEW_SYNC 359
#define T_NEW_ASSIGN 360
#define T_NEW_SELECT 361
#define T_OLD 362
#define T_OLD_DECLARATION 363
#define T_OLD_LOCAL_DECL 364
#define T_OLD_INST 365
#define T_OLD_PARAMETERS 366
#define T_OLD_INVARIANT 367
#define T_OLD_GUARD 368
#define T_OLD_ASSIGN 369
#define T_PROPERTY 370
#define T_EXPRESSION 371
#define UOPERATOR 372

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 183 "parser.yy" /* yacc.c:352  */

    bool flag;
    int number;
    ParserBuilder::PREFIX prefix;
    kind_t kind;
    char string[MAXLEN];

#line 418 "parser.tab.c" /* yacc.c:352  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE utap_lval;
extern YYLTYPE utap_lloc;
int utap_parse (void);





#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  91
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3692

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  132
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  150
/* YYNRULES -- Number of rules.  */
#define YYNRULES  388
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  762

#define YYUNDEFTOK  2
#define YYMAXUTOK   372

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     131,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   119,   126,
     121,   122,     2,     2,   128,     2,   125,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   118,   127,
       2,     2,     2,   117,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   123,     2,   124,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   129,     2,   130,     2,     2,     2,     2,
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
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   120
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   197,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   221,   224,   226,   227,   231,   231,   238,
     239,   243,   248,   251,   252,   256,   257,   258,   262,   266,
     267,   271,   272,   276,   277,   281,   282,   283,   287,   289,
     291,   293,   295,   298,   302,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   315,   317,   324,   324,   331,   332,
     333,   337,   338,   342,   345,   351,   357,   358,   362,   362,
     370,   371,   375,   376,   382,   383,   387,   390,   396,   396,
     398,   400,   401,   401,   402,   406,   409,   413,   414,   418,
     418,   426,   429,   432,   435,   438,   441,   444,   447,   450,
     453,   456,   460,   463,   466,   469,   472,   475,   479,   485,
     486,   490,   491,   495,   502,   503,   507,   507,   515,   516,
     517,   518,   519,   527,   527,   536,   539,   541,   542,   543,
     547,   548,   552,   553,   557,   560,   563,   569,   572,   575,
     577,   578,   582,   583,   587,   587,   593,   593,   602,   602,
     607,   607,   612,   615,   617,   621,   624,   628,   630,   633,
     636,   639,   641,   642,   646,   649,   652,   655,   660,   662,
     665,   668,   670,   671,   672,   673,   677,   678,   682,   683,
     687,   688,   692,   693,   697,   700,   706,   709,   715,   718,
     724,   727,   738,   738,   746,   748,   749,   752,   754,   755,
     759,   760,   763,   766,   766,   772,   772,   778,   779,   779,
     785,   786,   786,   792,   792,   796,   799,   802,   802,   808,
     811,   817,   820,   820,   829,   830,   834,   834,   840,   840,
     846,   846,   852,   852,   861,   862,   867,   870,   873,   876,
     879,   879,   884,   884,   889,   892,   895,   896,   899,   902,
     905,   908,   911,   914,   917,   920,   923,   926,   929,   932,
     935,   938,   941,   944,   947,   950,   953,   956,   959,   962,
     965,   968,   971,   974,   977,   980,   980,   985,   988,   991,
     994,   997,  1000,  1000,  1005,  1005,  1010,  1014,  1020,  1021,
    1022,  1023,  1024,  1025,  1026,  1027,  1028,  1029,  1030,  1035,
    1036,  1037,  1042,  1043,  1046,  1056,  1059,  1061,  1062,  1066,
    1067,  1067,  1072,  1075,  1076,  1080,  1080,  1091,  1091,  1097,
    1097,  1103,  1103,  1109,  1109,  1115,  1115,  1124,  1125,  1126,
    1130,  1133,  1134,  1137,  1141,  1141,  1146,  1146,  1154,  1154,
    1159,  1159,  1167,  1170,  1172,  1176,  1177,  1181,  1182,  1186,
    1189,  1195,  1196,  1198,  1203,  1205,  1206,  1210,  1211,  1215,
    1215,  1225,  1225,  1230,  1233,  1235,  1238,  1244,  1245,  1251,
    1253,  1255,  1257,  1259,  1262,  1267,  1268,  1269,  1270
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_ASSIGNMENT", "T_ASSPLUS",
  "T_ASSMINUS", "T_ASSMULT", "T_ASSDIV", "T_ASSMOD", "T_ASSOR", "T_ASSAND",
  "T_ASSXOR", "T_ASSLSHIFT", "T_ASSRSHIFT", "T_EXCLAM", "T_INCREMENT",
  "T_DECREMENT", "T_PLUS", "T_MINUS", "T_MULT", "T_DIV", "T_MIN", "T_MAX",
  "T_MOD", "T_OR", "T_XOR", "T_LSHIFT", "T_RSHIFT", "T_BOOL_AND",
  "T_BOOL_OR", "T_KW_AND", "T_KW_OR", "T_KW_IMPLY", "T_KW_NOT", "T_FORALL",
  "T_EXISTS", "T_LT", "T_LEQ", "T_EQ", "T_NEQ", "T_GEQ", "T_GT", "T_FOR",
  "T_WHILE", "T_DO", "T_BREAK", "T_CONTINUE", "T_SWITCH", "T_IF", "T_ELSE",
  "T_CASE", "T_DEFAULT", "T_RETURN", "T_PRIORITY", "T_TYPEDEF", "T_STRUCT",
  "T_CONST", "T_OLDCONST", "T_URGENT", "T_BROADCAST", "T_TRUE", "T_FALSE",
  "T_META", "T_SYSTEM", "T_PROCESS", "T_STATE", "T_COMMIT", "T_INIT",
  "T_TRANS", "T_SELECT", "T_GUARD", "T_SYNC", "T_ASSIGN", "T_BEFORE",
  "T_AFTER", "T_PROGRESS", "T_ARROW", "T_UNCONTROL_ARROW", "T_WINNING",
  "T_LOSING", "T_DEADLOCK", "T_EF", "T_EG", "T_AF", "T_AG", "T_LEADSTO",
  "T_ERROR", "T_ID", "T_TYPENAME", "T_NAT", "T_BOOL", "T_INT", "T_CHAN",
  "T_CLOCK", "T_VOID", "T_SCALAR", "T_NEW", "T_NEW_DECLARATION",
  "T_NEW_LOCAL_DECL", "T_NEW_INST", "T_NEW_SYSTEM", "T_NEW_PARAMETERS",
  "T_NEW_INVARIANT", "T_NEW_GUARD", "T_NEW_SYNC", "T_NEW_ASSIGN",
  "T_NEW_SELECT", "T_OLD", "T_OLD_DECLARATION", "T_OLD_LOCAL_DECL",
  "T_OLD_INST", "T_OLD_PARAMETERS", "T_OLD_INVARIANT", "T_OLD_GUARD",
  "T_OLD_ASSIGN", "T_PROPERTY", "T_EXPRESSION", "'?'", "':'", "'&'",
  "UOPERATOR", "'('", "')'", "'['", "']'", "'.'", "'\\''", "';'", "','",
  "'{'", "'}'", "'\\n'", "$accept", "Uppaal", "XTA", "Instantiations",
  "Instantiation", "$@1", "OptionalInstanceParameterList", "System",
  "PriorityDecl", "ChannelList", "ChanLessThan", "ChanElement",
  "ChanExpression", "SysDecl", "ProcessList", "ProcLessThan", "Progress",
  "ProgressMeasureList", "Declarations", "BeforeUpdateDecl",
  "AfterUpdateDecl", "FunctionDecl", "$@2", "OptionalParameterList",
  "ParameterList", "Parameter", "VariableDecl", "DeclIdList", "DeclId",
  "$@3", "VarInit", "Initializer", "FieldInitList", "FieldInit",
  "ArrayDecl", "$@4", "ArrayDecl2", "$@5", "TypeDecl", "TypeIdList",
  "TypeId", "$@6", "Type", "Id", "FieldDeclList", "FieldDecl",
  "FieldDeclIdList", "FieldDeclId", "$@7", "TypePrefix", "ProcDecl", "$@8",
  "ProcBody", "ProcLocalDeclList", "States", "StateDeclList", "StateDecl",
  "Init", "Transitions", "TransitionList", "Transition", "$@9", "$@10",
  "TransitionOpt", "$@11", "$@12", "Select", "SelectList", "Guard", "Sync",
  "SyncExpr", "Assign", "LocFlags", "Commit", "Urgent", "Winning",
  "Losing", "CStateList", "UStateList", "WStateList", "LStateList",
  "Block", "$@13", "BlockLocalDeclList", "StatementList", "Statement",
  "$@14", "$@15", "$@16", "$@17", "$@18", "$@19", "ElsePart", "$@20",
  "SwitchCaseList", "SwitchCase", "$@21", "$@22", "$@23", "$@24",
  "ExprList", "Expression", "$@25", "$@26", "$@27", "$@28", "$@29",
  "Assignment", "AssignOp", "UnaryOp", "ArgList", "OldXTA",
  "OldDeclaration", "OldVarDecl", "$@30", "OldConstDeclIdList",
  "OldConstDeclId", "$@31", "OldProcDecl", "$@32", "$@33", "$@34", "$@35",
  "$@36", "OldProcParams", "OldProcParamList", "OldProcParam", "$@37",
  "$@38", "OldProcConstParam", "$@39", "$@40", "OldProcBody",
  "OldVarDeclList", "OldStates", "OldStateDeclList", "OldStateDecl",
  "OldInvariant", "OldTransitions", "OldTransitionList", "OldTransition",
  "$@41", "OldTransitionOpt", "$@42", "OldGuard", "OldGuardList",
  "PropertyList", "PropertyList2", "Property", "Quantifier", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
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
     365,   366,   367,   368,   369,   370,   371,    63,    58,    38,
     372,    40,    41,    91,    93,    46,    39,    59,    44,   123,
     125,    10
};
# endif

#define YYPACT_NINF -651

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-651)))

#define YYTABLE_NINF -362

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1765,  3555,  3513,  -651,  3513,  3555,  1991,  3468,  3468,  3468,
    3468,   102,  -651,  -651,  -651,    32,  1836,  3468,  3468,  3468,
    -651,  3468,    58,   -88,  -651,  1329,  1494,  1656,  1494,  -651,
     -81,  -651,     4,  -651,  -651,  -651,  -651,   -51,  -651,  -651,
    -651,   -37,   -34,  -651,   -58,   263,  -651,  3468,  3468,  -651,
    -651,  3468,   -13,     7,  -651,  -651,  -651,  -651,  -651,   326,
    2758,  -651,  3468,  2758,  -651,  1287,   -30,  2758,  -651,  -651,
      60,    84,  -651,  1003,  1672,  1983,    88,   140,  -651,  -651,
     105,   136,   161,   716,   171,  2758,   186,   -30,  -651,  3290,
    2758,  -651,  -651,  1173,    30,   102,   192,   197,   229,   285,
    -651,  -651,  -651,   253,  -651,  -651,  -651,  -651,  -651,   102,
    -651,  -651,  -651,  -651,  1339,  -651,  3468,  3468,  1991,  -651,
     269,   255,  -651,  -651,   257,  -651,   267,    76,    76,  2921,
     102,   102,   280,  1819,  -651,  -651,  -651,  -651,  -651,  -651,
    -651,  -651,  -651,  -651,  -651,  -651,  -651,  3468,  3468,  3468,
    3468,  3468,  3468,  3468,  3468,  3468,  3468,  3468,  3468,  3468,
    3468,  3468,  -651,  3468,  3468,  3468,  3468,  3468,  3468,  3468,
    3468,   398,   348,   320,  -651,  3468,    76,     8,  -651,  3468,
    3468,  1991,   102,    44,    33,   -25,  -651,   102,  -651,  -651,
    -651,  -651,  -651,   323,   327,  1836,   290,  -651,   294,  3468,
    3468,  -651,  -651,  -651,  -651,  1943,   305,  3468,   298,   102,
     315,  -651,   -12,   329,  3468,  3468,  1162,   448,   134,   324,
    -651,   120,  -651,   329,   322,   102,  1664,  -651,  1326,  1982,
    -651,  -651,   331,  -651,  1504,  3468,  3468,   344,   347,  -651,
    -651,   947,   947,    76,    76,    61,    61,    76,  3322,  3369,
     275,   275,  3295,  3257,  2921,  2797,  3468,   467,   467,  3440,
    3440,   467,   467,  2106,  3413,  3468,   462,   342,  2145,  -651,
    2921,  -651,  -651,  2758,  -651,   349,   341,   383,   343,    48,
    -651,  -651,  -651,  -651,   136,   161,   384,   386,  -651,  2758,
    2758,  3468,  -651,  2758,  -651,   128,  -651,  -651,  -651,  -651,
    -651,   387,   388,   217,   350,   -29,   -17,  -651,   -62,   393,
     354,  -651,  -651,    39,  -651,   368,  -651,  -651,   102,   363,
    -651,  -651,  -651,   203,  -651,  -651,  -651,  3468,  -651,  2963,
    -651,  -651,   365,  1827,  1452,  2269,  1991,  1991,  2797,  3468,
    2758,   -39,   374,  -651,  -651,  1991,  -651,  -651,   207,  -651,
    -651,   369,    12,  -651,    35,  -651,  -651,  -651,  -651,  2758,
    -651,   102,  -651,  -651,  -651,   375,  -651,    97,  -651,  -651,
    -651,  -651,   378,  -651,  -651,  -651,   -14,   -14,  3468,  3052,
    -651,  -651,   497,  -651,  -651,   102,  2308,   377,   381,  2432,
    -651,  -651,  3468,  -651,   380,   385,   654,  -651,  3468,  -651,
    -651,  -651,  -651,   383,  -651,  -651,   389,  -651,   -71,  -651,
     379,  -651,  -651,  -651,  -651,  -651,  -651,  -651,  -651,  -651,
    -651,  -651,  2471,  -651,  1491,  -651,  3171,  -651,  -651,  -651,
    -651,   331,  -651,   331,  2595,  -651,  -651,  2758,  3171,  -651,
     390,  3488,  -651,  -651,  -651,   391,  -651,  -651,   392,  3597,
    3468,  -651,  3468,  -651,  1656,  3082,  -651,  2758,  -651,   331,
    -651,  -651,  3468,  3468,  -651,  -651,   382,   423,  -651,   394,
    -651,  -651,   405,  -651,   409,   427,  -651,   114,  1616,  -651,
    -651,   892,   399,  -651,   115,  -651,   400,  -651,  2758,  2758,
    -651,   410,   220,  -651,   345,  -651,   411,  -651,  -651,   414,
     240,  -651,   345,   413,  -651,   420,   428,   429,  -651,   421,
     424,   431,   439,  3182,  -651,  -651,  -651,  -651,  -651,  1655,
    3082,  -651,  3171,  3468,  -651,   423,   438,    49,    89,   432,
      96,   111,   498,  -651,  -651,  -651,  -651,  -651,   443,  -651,
     427,   500,  -651,  -651,   236,   568,  3132,  -651,  -651,  3468,
    -651,  -651,  1780,  -651,  -651,  -651,  -651,   137,  -651,  -651,
     447,  -651,   242,   451,  -651,   247,   452,   460,  -651,   249,
     468,  -651,   251,   126,  -651,   440,  1119,  -651,   154,  -651,
     453,   471,   261,   472,  3468,   553,   118,  3468,  -651,  1656,
    -651,  -651,  -651,   510,  -651,  -651,   517,  -651,  -651,  -651,
     519,  -651,  -651,   520,   481,   534,   265,  -651,  -651,  -651,
     484,   318,   277,  -651,  3132,  1991,  3468,  3132,   152,   491,
    -651,   159,   991,  -651,  -651,  -651,  -651,  -651,   526,  -651,
     -33,  -651,   527,   529,  -651,   146,  -651,   495,   289,  -651,
    3132,  3468,   489,  3132,  -651,   490,   533,  -651,  -651,   492,
     493,   537,   538,  -651,  -651,  -651,  3468,  -651,   178,   370,
     577,  -651,   502,  -651,  -651,   504,   506,  3132,   191,   509,
     968,    14,   155,  -651,  -651,  -651,   557,  -651,   570,   570,
    -651,  -651,  -651,  -651,  -651,   524,  2634,   525,  -651,  -651,
    -651,  3132,  3468,   566,   557,   102,   574,   574,   570,   570,
    3132,  -651,  -651,  -651,  -651,  -651,    52,  2830,   575,   566,
     302,  2952,   566,   566,   574,   574,  -651,  -651,  -651,  -651,
     511,   523,  -651,   531,   532,  3047,   516,   575,  -651,   535,
    1160,   575,   575,   566,   566,   749,   771,   870,  -651,  -651,
    -651,   539,   306,  -651,   521,  -651,   540,  -651,   522,   530,
     575,   575,  -651,  -651,  -651,  -651,  -651,  -651,   554,   556,
    -651,  -651
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     0,     0,   136,     0,     0,     0,     0,     0,     0,
       0,     0,   316,   316,   353,     0,     0,     0,     0,     0,
     380,     0,     0,     0,     2,     0,     3,     4,     5,     6,
       0,   131,   128,   129,   132,   101,   107,   109,   113,   115,
     116,     0,     7,    71,     0,     0,   311,     0,     0,   310,
     309,     0,     0,     0,   247,   246,   284,   249,   248,     0,
       8,   296,     0,    10,    11,     0,    12,   244,   119,   120,
       0,     9,    13,     0,    14,    15,     0,    16,   348,   344,
      17,   340,   341,     0,    18,   377,    19,    20,    21,   382,
      22,     1,    63,     0,     0,     0,     0,     0,    29,   113,
      61,    23,    62,    49,    59,    60,    55,    56,    57,     0,
      58,   137,   138,   139,     0,   130,     0,     0,     0,    88,
       0,     0,   102,   108,   110,   114,     0,   259,   261,   289,
       0,     0,     0,     0,   298,   299,   300,   303,   301,   302,
     305,   304,   306,   307,   308,   258,   260,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   285,     0,     0,     0,     0,     0,     0,     0,
       0,   250,     0,     0,   283,     0,   262,     0,   174,   176,
       0,     0,     0,     0,     0,     0,   319,     0,   317,   318,
     354,    26,    25,     0,     0,     0,     0,   350,     0,     0,
       0,   385,   386,   387,   388,     0,   379,     0,     0,     0,
       0,    45,     0,     0,     0,     0,     0,     0,     0,     0,
      32,     0,    76,    78,     0,     0,     0,   121,     0,     0,
      72,    74,    90,    88,     0,     0,     0,     0,     0,   257,
     256,   269,   270,   271,   272,   290,   291,   273,   275,   276,
     277,   278,   279,   280,   287,   288,     0,   263,   264,   265,
     266,   268,   267,     0,   274,   312,     0,     0,     0,   282,
     297,   175,   177,   245,   165,     0,     0,     0,     0,     0,
     315,    78,    88,    88,   342,   343,     0,     0,   362,   363,
     378,     0,   381,   383,    96,     0,    97,    99,    44,    48,
      43,     0,     0,     0,     0,     0,     0,    30,     0,     0,
       0,    40,    41,     0,    35,    39,    51,    75,     0,     0,
      88,   105,   126,     0,   124,   103,   122,     0,   117,     0,
      89,    73,     0,     0,     0,     0,     0,     0,   286,     0,
     313,     0,     0,   255,   254,     0,   322,   325,     0,   323,
     333,     0,     0,   335,     0,   349,   345,    88,    88,   384,
      95,     0,    88,    46,    47,     0,    68,     0,   133,    64,
      65,    31,     0,    34,    38,    33,     0,     0,     0,     0,
      77,    66,    80,    88,   123,     0,     0,     0,     0,     0,
     106,   104,     0,   118,     0,     0,   281,   251,     0,   253,
     166,    88,   321,     0,   353,   331,     0,   337,     0,   353,
       0,   327,   347,   351,    98,   100,    70,    69,   136,    27,
      36,    37,     0,    50,     0,   204,     0,    79,   127,   125,
     111,    90,    92,    90,     0,   292,   294,   314,     0,   324,
       0,     0,   353,   339,   338,     0,   329,   353,     0,     0,
     312,    42,     0,    53,   207,     0,    81,    82,    94,    90,
      91,   112,     0,     0,   326,   334,     0,     0,   181,     0,
     336,   353,     0,   134,     0,     0,   181,     0,     0,   205,
     206,     0,   249,    87,     0,    84,     0,    93,   293,   295,
     356,   359,     0,   357,     0,   332,     0,   328,   141,   144,
       0,   142,     0,     0,    52,     0,     0,     0,   221,     0,
       0,     0,     0,     0,   211,   202,    67,   210,   208,     0,
       0,    83,     0,     0,   355,     0,     0,     0,     0,     0,
       0,     0,   364,   182,   183,   184,   185,   330,     0,   140,
       0,   149,    28,   209,     0,     0,     0,   225,   226,     0,
     223,   230,     0,   204,   212,    85,    86,     0,   358,   148,
       0,   196,     0,     0,   194,     0,     0,     0,   198,     0,
       0,   200,     0,     0,   352,     0,     0,   143,     0,   135,
       0,     0,     0,     0,     0,     0,     0,     0,   229,   207,
     360,   189,   188,     0,   187,   186,     0,   147,   191,   190,
       0,   193,   192,     0,     0,     0,     0,   367,   146,   145,
       0,     0,     0,   152,     0,     0,     0,     0,     0,     0,
     227,     0,     0,   197,   195,   199,   201,   366,     0,   365,
       0,   151,     0,     0,   150,     0,   217,     0,     0,   220,
       0,     0,     0,     0,   203,     0,     0,   373,   368,     0,
       0,     0,     0,   162,   153,   215,     0,   219,     0,     0,
     231,   369,     0,   154,   156,     0,     0,     0,     0,     0,
       0,     0,     0,   234,   232,   224,   374,   371,   163,   163,
     158,   160,   216,   213,   222,     0,     0,     0,   240,   228,
     235,     0,     0,   171,   374,     0,   167,   167,   163,   163,
       0,   238,   236,   242,   207,   233,     0,     0,   178,   171,
       0,     0,   171,   171,   167,   167,   214,   207,   207,   207,
       0,     0,   375,     0,     0,     0,     0,   178,   164,     0,
       0,   178,   178,   171,   171,     0,     0,     0,   376,   173,
     172,     0,     0,   370,     0,   170,     0,   168,     0,     0,
     178,   178,   180,   179,   372,   169,   155,   157,     0,     0,
     159,   161
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -651,  -651,   648,   581,   -56,  -651,  -651,   476,  -651,  -651,
    -651,    62,  -651,  -651,  -651,  -651,  -651,  -651,   313,  -651,
    -651,   -23,  -651,   433,  -181,   546,    -8,  -651,   395,  -651,
    -651,  -396,  -651,   145,  -187,  -651,  -374,  -651,   -22,  -651,
     307,  -651,     0,    79,   454,  -203,  -651,   311,  -651,  -651,
    -651,  -651,  -651,   279,  -651,  -651,   147,   196,  -651,  -651,
      64,  -651,  -651,  -651,  -651,  -651,  -468,     6,  -650,  -474,
      -5,  -449,   227,  -651,  -651,  -651,  -651,  -651,  -651,  -651,
    -651,  -651,  -651,   153,  -580,  -423,  -651,  -651,  -651,  -651,
    -651,  -651,  -651,  -651,  -651,    36,  -651,  -651,  -651,  -651,
     -11,    -7,  -651,  -651,  -651,  -651,  -651,  -651,  -651,  -651,
     259,  -651,   692,   -68,  -651,  -651,   304,  -651,  -651,  -651,
    -651,  -651,  -651,  -651,  -651,   358,   563,  -651,  -651,   564,
    -651,  -651,  -185,   697,  -651,  -651,   187,   226,  -651,  -651,
      85,  -651,  -651,  -651,    57,    38,  -651,  -651,  -651,  -651
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    22,    24,    77,   100,   450,   217,   101,   102,   313,
     377,   314,   315,   103,   212,   302,   220,   379,    25,   104,
     105,   106,   425,   304,    42,    43,   186,   221,   222,   320,
     427,   483,   484,   485,   231,   232,   330,   459,   108,   295,
     296,   362,   187,    70,   226,   227,   323,   324,   383,    45,
     110,   418,   448,    27,   476,   500,   501,   532,   579,   612,
     613,   678,   679,   654,   698,   699,   696,    71,   712,   708,
      64,   726,   494,   533,   534,   535,   536,   565,   562,   569,
     572,   517,   553,   454,   481,   518,   700,   667,   584,   546,
     587,   642,   675,   691,   672,   673,   718,   717,   704,   719,
      66,   519,   265,   266,   256,   462,   463,    61,   175,    62,
     341,    72,    73,   188,   277,   348,   349,   401,   189,   447,
     471,   442,   404,   409,   354,    80,    81,   194,   196,    82,
     193,   287,   440,   441,   468,   492,   493,    84,   574,   606,
     607,   676,   648,   694,   693,    86,    88,    89,   206,   207
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      60,    63,    65,    67,   111,   113,    44,   190,    87,   622,
      83,    85,    67,   406,    90,   687,    79,   107,   107,   112,
     107,   192,   271,   326,   299,   109,   109,   109,   109,   119,
     456,   210,   -24,    76,   278,   308,   410,   311,    94,    92,
     127,   128,   464,   646,   129,   276,   331,   713,   114,   351,
     560,   444,   133,   721,   605,   176,   195,   458,    91,   460,
     371,   120,    98,   115,   733,   734,   118,    30,    31,    78,
      32,    33,   116,   312,    34,   374,   145,   146,   147,   148,
     149,   150,   205,   397,   153,   487,   117,   156,   157,   398,
     563,   145,   146,   209,   118,   355,   356,   567,   180,   180,
      35,   369,    36,    37,    38,    39,    40,    41,   130,   228,
     229,   180,   570,   370,   225,   300,   301,   211,    44,   -24,
      68,    69,   367,   585,   720,   272,   556,   604,   131,   192,
     326,  -320,   688,   382,   407,   310,   561,   735,   736,   737,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   610,   257,   258,   259,   260,
     261,   262,   263,   264,   411,   268,   375,   376,   270,   352,
     412,   413,   263,   273,   213,   415,   564,   353,   181,   722,
     200,   274,   171,   568,   172,   311,   173,   174,   223,    68,
      69,   636,   289,   290,   639,    79,   428,   171,   571,   172,
     293,   173,   174,   305,   306,   670,   671,    67,    67,   237,
     238,   697,   182,   605,   438,   191,    44,   657,   365,   417,
     660,   312,   651,   652,   445,   118,   225,    98,   334,   335,
     714,   715,   195,   611,   225,   727,   503,   580,   731,   732,
     620,   611,   398,   520,   682,   521,   180,   317,   318,   338,
      46,    47,    48,    49,    50,   360,   361,   469,   340,   750,
     751,   275,   472,   279,  -346,   199,   281,   590,   705,    51,
      52,    53,    30,    31,   640,    32,    33,   716,   744,    34,
     180,   643,   748,   749,   359,   689,   496,   180,   297,   197,
     145,   146,   147,   148,   149,   150,    54,    55,   153,   199,
     669,   758,   759,    44,   322,    35,   180,    36,    37,    38,
      39,    40,    41,   683,   200,    26,    56,    28,   121,   180,
     386,   214,   389,   482,    69,    58,   215,   132,   219,   388,
     384,   385,   396,   225,   402,   403,   394,   395,   218,   366,
      46,    47,    48,    49,    50,   400,   526,   524,   525,   267,
     216,   122,    79,   123,   124,   125,   233,    59,   126,    51,
      52,    53,    46,    47,    48,    49,    50,   539,   540,   592,
     593,   422,   424,   190,   595,   596,   599,   600,   602,   603,
     235,    51,    52,    53,   234,   434,    54,    55,   616,   180,
     236,   437,   629,   630,   632,   633,   171,   281,   172,  -252,
     173,   174,   239,   527,   634,   635,    56,   269,    54,    55,
     282,   528,   529,    57,   283,    58,   656,   180,   286,   457,
     670,   671,   288,   530,   531,   294,   111,   113,    56,   728,
     182,   457,   480,   753,   180,    57,   292,    58,   420,   421,
     297,   112,   298,   340,   575,   478,   479,    59,   457,   109,
     303,   309,   321,   316,   329,   488,   489,    46,    47,    48,
      49,    50,   336,   342,   322,   337,   343,   345,   346,    59,
     347,   357,   350,   358,   363,   364,    51,    52,    53,   368,
     372,   373,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   378,   381,   156,   157,   390,   399,   416,   405,   419,
     426,   431,   435,    54,    55,   432,   552,   436,   446,   490,
     491,   443,   505,   457,   499,   457,    83,  -119,   522,   566,
     465,   470,   473,    56,   495,    46,    47,    48,    49,    50,
      57,   576,    58,   582,   486,   497,   498,    67,   586,   523,
     542,   537,    67,   538,    51,    52,    53,   543,   547,   544,
     545,   548,   549,   506,   507,   508,   509,   510,   511,   512,
     550,  -241,  -241,   513,    59,   559,   573,   480,   578,   583,
     608,    54,    55,   618,   591,   614,   621,    67,   594,   597,
      67,   479,  -218,  -218,  -218,  -218,  -218,   598,   171,   615,
     172,    56,   173,   174,   617,   601,   619,   623,    57,   486,
      58,  -218,  -218,  -218,   624,   638,   625,   626,   627,    67,
     628,   631,   641,   645,   649,   637,   650,   655,   659,   661,
     662,   663,   664,   581,   665,   666,   674,   692,  -218,  -218,
     658,   677,    59,   680,    67,   681,   684,   707,   514,   695,
     515,  -241,   701,   703,   711,   668,   743,   725,  -218,    67,
     738,   754,   756,    29,   185,  -218,   319,  -218,   739,   740,
     757,   280,   745,   686,   230,   555,   752,   755,   414,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   760,    85,   761,   577,   333,  -218,
     163,   164,   165,   166,   167,   168,   429,   449,   541,   653,
      65,   710,   724,   502,   730,    74,   589,   439,   690,   477,
     408,    75,   558,   380,   742,   647,  -361,   198,    67,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     706,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   557,
     505,   709,   163,   164,   165,   166,   167,   168,   284,   285,
       0,     0,     0,    46,    47,    48,    49,    50,     0,     0,
       0,   169,   505,   170,     0,   171,     0,   172,     0,   173,
     174,     0,    51,    52,    53,    46,    47,    48,    49,    50,
       0,   506,   507,   508,   509,   510,   511,   512,     0,  -239,
    -239,   513,     0,     0,    51,    52,    53,     0,     0,    54,
      55,     0,     0,   506,   507,   508,   509,   510,   511,   512,
       0,  -237,  -237,   513,     0,     0,     0,     0,     0,    56,
       0,    54,    55,   169,     0,   170,    57,   171,    58,   172,
       0,   173,   174,     0,  -361,     0,  -361,     0,     0,     0,
       0,    56,     0,     0,     0,     0,     0,     0,    57,     0,
      58,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      59,   505,     0,     0,     0,     0,   514,     0,   515,  -239,
       0,     0,     0,     0,    46,    47,    48,    49,    50,     0,
       0,     0,    59,   505,     0,     0,     0,     0,   514,     0,
     515,  -237,     0,    51,    52,    53,    46,    47,    48,    49,
      50,     0,   506,   507,   508,   509,   510,   511,   512,     0,
    -243,  -243,   513,     0,     0,    51,    52,    53,     0,     0,
      54,    55,     0,     0,   506,   507,   508,   509,   510,   511,
     512,     0,     0,     0,   513,     0,     0,     0,     0,     0,
      56,     0,    54,    55,     0,     0,     0,    57,     0,    58,
       0,     0,   145,   146,     0,     0,   149,   150,     0,   685,
     153,     0,    56,     0,     0,     0,     0,     0,     0,    57,
       0,    58,    46,    47,    48,    49,    50,     0,     0,     0,
       0,    59,   505,     0,     0,     0,     0,   514,     0,   515,
    -243,    51,    52,    53,    76,    46,    47,    48,    49,    50,
       0,     0,     0,    59,     0,     0,     0,     0,     0,   514,
       0,   515,   516,     0,    51,    52,    53,     0,    54,    55,
       0,     0,     0,   506,   507,   508,   509,   510,   511,   512,
       0,     0,     0,   513,     0,     0,     0,     0,    56,     0,
       0,    54,    55,     0,     0,    57,     0,    58,    30,    31,
     183,    32,    33,     0,     0,    34,   -24,   184,   171,     0,
     172,    56,   173,   174,     0,     0,     0,     0,    57,     0,
      58,     0,     0,     0,     0,     0,     0,     0,     0,    59,
     -24,    35,     0,    36,    37,    38,    39,    40,    41,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    59,     0,     0,     0,     0,     0,   514,     0,
     515,   644,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,     0,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,     0,     0,     0,   163,   164,   165,   166,   167,
     168,   746,     0,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   208,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,     0,     0,     0,   163,   164,   165,   166,
     167,   168,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    30,    31,     0,
      32,    33,     0,     0,    34,     0,     0,     0,    30,    31,
       0,    32,    33,     0,     0,    34,   169,     0,   170,     0,
     171,     0,   172,     0,   173,   174,     0,     0,     0,   609,
      35,     0,    36,    37,    38,    39,    40,    41,     0,     0,
       0,    35,     0,    36,    37,    38,    39,    40,    41,     0,
       0,     0,     0,     0,     0,     0,     0,   169,     0,   170,
       0,   171,     0,   172,   307,   173,   174,   747,   177,     0,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   178,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
       0,     0,     0,   163,   164,   165,   166,   167,   168,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     224,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,     0,
       0,     0,   163,   164,   165,   166,   167,   168,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    93,    30,    31,     0,    32,    33,     0,
       0,    34,    94,    95,    30,    31,     0,    32,    33,     0,
       0,    34,    96,    97,   179,     0,   170,     0,   171,     0,
     172,     0,   173,   174,     0,     0,    98,    35,     0,    36,
      37,    99,    39,    40,    41,     0,     0,    35,     0,    36,
      37,    38,    39,    40,    41,     0,     0,     0,     0,     0,
       0,     0,     0,   169,     0,   170,     0,   171,     0,   172,
       0,   173,   174,     0,   327,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,     0,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,     0,     0,     0,   163,   164,
     165,   166,   167,   168,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   332,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,     0,     0,     0,   163,   164,   165,
     166,   167,   168,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    93,    30,
      31,     0,    32,    33,     0,     0,    34,     0,    95,    30,
      31,     0,    32,    33,     0,     0,    34,    96,    97,   169,
       0,   170,     0,   171,     0,   172,     0,   173,   174,     0,
     392,    98,    35,     0,    36,    37,    99,    39,    40,    41,
       0,     0,    35,     0,    36,    37,    38,    39,    40,    41,
       0,     0,     0,     0,     0,     0,     0,     0,   169,   452,
     170,     0,   171,     0,   172,     0,   173,   174,   453,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
       0,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,     0,
       0,     0,   163,   164,   165,   166,   167,   168,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,     0,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,     0,     0,
       0,   163,   164,   165,   166,   167,   168,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      93,    30,    31,     0,    32,    33,     0,     0,    34,    30,
      31,     0,    32,    33,     0,     0,    34,    30,    31,   183,
      32,    33,     0,   169,    34,   170,   184,   171,     0,   172,
       0,   173,   174,   504,    35,     0,    36,    37,    38,    39,
      40,    41,    35,     0,    36,    37,    38,    39,    40,    41,
      35,     0,    36,    37,    38,    39,    40,    41,     0,     0,
       0,     0,   169,     0,   170,     0,   171,     0,   172,     0,
     173,   174,   554,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   325,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,     0,     0,     0,   163,   164,   165,   166,
     167,   168,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,     0,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,     0,     0,     0,   163,   164,   165,   166,   167,
     168,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    30,    31,     0,    32,    33,     0,     0,    34,
       0,    30,    31,    78,    32,    33,     0,   169,    34,   170,
       0,   171,     0,   172,     0,   173,   174,   588,     0,     0,
       0,     0,     0,     0,     0,    35,     0,    36,    37,    38,
      39,    40,    41,     0,    35,     0,    36,    37,    38,    39,
      40,    41,     0,     0,     0,     0,   169,     0,   170,     0,
     171,   240,   172,     0,   173,   174,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   391,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,     0,     0,     0,   163,
     164,   165,   166,   167,   168,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,     0,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,     0,     0,     0,   163,   164,
     165,   166,   167,   168,     0,     0,     0,     0,   291,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    30,    31,
     183,    32,    33,     0,     0,    34,    30,    31,     0,    32,
      33,     0,     0,    34,     0,     0,     0,     0,     0,     0,
     169,     0,   170,     0,   171,     0,   172,     0,   173,   174,
       0,    35,     0,    36,    37,    38,    39,    40,    41,    35,
       0,    36,    37,    38,    39,    40,    41,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   169,
       0,   170,     0,   171,     0,   172,   328,   173,   174,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
       0,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,     0,
       0,     0,   163,   164,   165,   166,   167,   168,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,     0,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,     0,     0,
       0,   163,   164,   165,   166,   167,   168,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   169,   339,   170,     0,   171,     0,   172,
       0,   173,   174,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   169,     0,   170,     0,   171,     0,   172,   344,
     173,   174,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,     0,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,     0,     0,     0,   163,   164,   165,   166,   167,
     168,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,     0,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,     0,     0,     0,   163,   164,   165,   166,   167,   168,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   169,     0,   170,     0,
     171,     0,   172,   393,   173,   174,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   169,     0,   170,     0,   171,
       0,   172,   430,   173,   174,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,     0,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,     0,     0,     0,   163,   164,
     165,   166,   167,   168,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,     0,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,     0,     0,     0,   163,   164,   165,
     166,   167,   168,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   169,
       0,   170,     0,   171,     0,   172,   433,   173,   174,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   169,     0,
     170,     0,   171,     0,   172,   451,   173,   174,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,     0,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,     0,     0,
       0,   163,   164,   165,   166,   167,   168,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,     0,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,     0,     0,     0,
     163,   164,   165,   166,   167,   168,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   169,     0,   170,     0,   171,     0,   172,   461,
     173,   174,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   169,   702,   170,     0,   171,     0,   172,     0,   173,
     174,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,     0,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,     0,     0,     0,   163,   164,   165,   166,   167,   168,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,     0,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,     0,     0,
       0,   723,     0,   163,   164,   165,   166,   167,   168,     0,
       0,     0,     0,     0,    46,    47,    48,    49,    50,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    51,    52,    53,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   169,     0,   170,     0,   171,
       0,   172,     0,   173,   174,     0,     0,     0,     0,     0,
      54,    55,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      56,     0,     0,     0,   169,     0,   170,    57,   171,    58,
     172,     0,   173,   174,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,     0,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,    59,     0,   729,     0,     0,     0,   163,   164,   165,
     166,   167,   168,     0,   387,     0,    46,    47,    48,    49,
      50,     0,     0,     0,     0,     0,     0,    46,    47,    48,
      49,    50,     0,     0,     0,    51,    52,    53,     0,     0,
       0,     0,     0,     0,     0,     0,    51,    52,    53,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    54,    55,     0,     0,     0,     0,    30,    31,
       0,    32,    33,    54,    55,    34,     0,     0,     0,     0,
       0,     0,    56,     0,     0,     0,     0,     0,   169,    57,
     170,    58,   171,    56,   172,     0,   173,   174,   741,     0,
      57,    35,    58,    36,    37,    38,    39,    40,    41,     0,
       0,    46,    47,    48,    49,    50,    46,    47,    48,    49,
      50,     0,     0,    59,     0,     0,     0,     0,     0,     0,
      51,    52,    53,     0,    59,    51,    52,    53,     0,     0,
       0,     0,     0,     0,     0,     0,    46,    47,    48,    49,
      50,     0,     0,     0,     0,     0,     0,    54,    55,     0,
       0,     0,    54,    55,     0,    51,    52,    53,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    56,     0,     0,
       0,     0,    56,     0,    57,     0,    58,     0,     0,    57,
       0,    58,    54,    55,     0,     0,    46,    47,    48,    49,
      50,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    56,     0,     0,    51,    52,    53,    59,   482,
      69,    58,     0,    59,   506,   507,   508,   509,   510,   511,
     512,     0,   423,     0,   513,    46,    47,    48,    49,    50,
       0,     0,    54,    55,     0,     0,    46,    47,    48,    49,
      50,     0,     0,    59,    51,    52,    53,     0,     0,     0,
       0,   455,    56,     0,     0,    51,    52,    53,     0,    57,
       0,    58,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    54,    55,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    54,    55,     0,     0,     0,     0,     0,     0,
       0,    56,     0,    59,     0,     0,     0,     0,    57,   514,
      58,   515,    56,     0,     0,     0,     0,     0,     0,    57,
       0,    58,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,     0,     0,     0,     0,
       0,     0,    59,   163,   164,   165,   166,   167,   168,     0,
     455,     0,     0,    59,    46,    47,    48,    49,    50,   551,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,    51,    52,    53,     0,     0,     0,     0,
       0,   163,   164,   165,   166,   167,   168,   145,   146,   147,
     148,   149,   150,   151,   152,   153,     0,   155,   156,   157,
      54,    55,     0,     0,     0,     0,     0,     0,   163,   164,
     165,   166,   167,   168,     0,     0,     0,     0,     0,     0,
      56,   201,   202,   203,   204,     0,   170,    57,   171,    58,
     172,     0,   173,   174,   145,   146,   147,   148,   149,   150,
     151,   152,   153,     0,     0,   156,   157,     0,     0,     0,
       0,     0,     0,     0,     0,   163,   164,   165,   166,   167,
     168,    59,     0,     0,   170,     0,   171,     0,   172,     0,
     173,   174,     0,     0,     0,     0,     0,     0,   145,   146,
     147,   148,   149,   150,   151,   152,   153,     0,     0,   156,
     157,   170,     0,   171,     0,   172,     0,   173,   174,   163,
     164,   165,   166,   167,   168,   145,   146,   147,   148,   149,
     150,   151,   152,   153,     0,     0,   156,   157,     0,     0,
       0,     0,     0,     0,     0,     0,   163,   164,     0,     0,
     167,   168,    46,    47,    48,    49,    50,     0,   170,   466,
     171,     0,   172,     0,   173,   174,     0,     0,     0,     0,
       0,    51,    52,    53,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -54,    23,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    54,    55,
       0,     0,     0,     0,   171,     0,   172,     0,   173,   174,
       0,     0,     0,    30,    31,   183,    32,    33,    56,     0,
      34,     0,     0,   467,     0,    57,    23,    58,     0,     0,
       0,   171,     0,   172,     0,   173,   174,   -54,   -54,   -54,
       0,   -54,   -54,     0,     0,   -54,    35,   -54,    36,    37,
      38,    39,    40,    41,     0,     0,   -54,   -54,     0,    59,
       0,     0,     0,     0,     0,     0,     0,     0,   474,     0,
     -54,   -54,     0,   -54,   -54,   -54,   -54,   -54,   -54,   -54,
     -54,   -54,     0,   -54,   -54,     0,     0,   -54,   -54,   -54,
       0,     0,     0,     0,     0,     0,     0,     0,   -54,   -54,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -54,   -54,     0,   -54,   -54,   -54,   -54,   -54,
     -54,    93,    30,    31,     0,    32,    33,     0,     0,    34,
       0,     0,   475,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    35,     0,    36,    37,    38,
      39,    40,    41
};

static const yytype_int16 yycheck[] =
{
       7,     8,     9,    10,    27,    27,     6,    75,    19,   589,
      17,    18,    19,     1,    21,     1,    16,    25,    26,    27,
      28,    77,    14,   226,    36,    25,    26,    27,    28,    87,
     426,     1,     0,     1,     1,   216,     1,    51,    63,   127,
      47,    48,   438,    76,    51,     1,   233,   697,   129,     1,
       1,   122,    59,     1,    87,    62,   127,   431,     0,   433,
     122,   119,    87,    59,   714,   715,   128,    55,    56,    57,
      58,    59,   123,    87,    62,    36,    15,    16,    17,    18,
      19,    20,    89,   122,    23,   459,   123,    26,    27,   128,
       1,    15,    16,    93,   128,   282,   283,     1,   128,   128,
      88,   130,    90,    91,    92,    93,    94,    95,   121,   116,
     117,   128,     1,   130,   114,   127,   128,    87,   118,    87,
      87,    88,   303,   546,   704,   117,   522,     1,   121,   185,
     333,    87,   118,   320,   122,     1,    87,   717,   718,   719,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,     1,   163,   164,   165,   166,
     167,   168,   169,   170,   129,   172,   127,   128,   175,   121,
     357,   358,   179,   180,    95,   362,    87,   129,   118,   127,
     128,   181,   121,    87,   123,    51,   125,   126,   109,    87,
      88,   614,   199,   200,   617,   195,   383,   121,    87,   123,
     207,   125,   126,   214,   215,    50,    51,   214,   215,   130,
     131,   679,   128,    87,   401,   127,   216,   640,     1,   122,
     643,    87,    76,    77,   409,   128,   226,    87,   235,   236,
     698,   699,   127,    87,   234,   709,   122,     1,   712,   713,
     122,    87,   128,   128,   667,   130,   128,   127,   128,   256,
      14,    15,    16,    17,    18,   127,   128,   442,   265,   733,
     734,   182,   447,   184,   128,   128,   187,   130,   691,    33,
      34,    35,    55,    56,   122,    58,    59,   700,   727,    62,
     128,   122,   731,   732,   291,   130,   471,   128,   209,   128,
      15,    16,    17,    18,    19,    20,    60,    61,    23,   128,
     122,   750,   751,   303,   225,    88,   128,    90,    91,    92,
      93,    94,    95,   122,   128,     2,    80,     4,    55,   128,
     327,   129,   329,    87,    88,    89,   129,     1,    75,   329,
     127,   128,   339,   333,   127,   128,   336,   337,    53,   122,
      14,    15,    16,    17,    18,   345,     1,   127,   128,     1,
     121,    88,   352,    90,    91,    92,    87,   121,    95,    33,
      34,    35,    14,    15,    16,    17,    18,   127,   128,   127,
     128,   378,   379,   441,   127,   128,   127,   128,   127,   128,
     123,    33,    34,    35,   129,   392,    60,    61,   127,   128,
     123,   398,   127,   128,    76,    77,   121,   318,   123,     1,
     125,   126,   122,    58,   127,   128,    80,    87,    60,    61,
      87,    66,    67,    87,    87,    89,   127,   128,   128,   426,
      50,    51,   128,    78,    79,   127,   449,   449,    80,   127,
     128,   438,   454,   127,   128,    87,   131,    89,   376,   377,
     361,   449,   127,   450,     1,   452,   454,   121,   455,   449,
     121,     3,   130,   129,   123,   462,   463,    14,    15,    16,
      17,    18,   118,     1,   385,   118,   124,   118,   127,   121,
      87,    87,   129,    87,    87,    87,    33,    34,    35,   129,
      87,   127,    15,    16,    17,    18,    19,    20,    21,    22,
      23,   123,   129,    26,    27,   130,   122,   122,   129,   121,
       3,   124,   122,    60,    61,   124,   513,   122,   129,   127,
      87,   122,     1,   520,    87,   522,   523,   118,   118,    87,
     130,   130,   130,    80,   130,    14,    15,    16,    17,    18,
      87,   538,    89,   544,   455,   130,   127,   544,   549,   129,
     127,   130,   549,   129,    33,    34,    35,   127,   127,   121,
     121,   127,   121,    42,    43,    44,    45,    46,    47,    48,
     121,    50,    51,    52,   121,   127,    68,   589,    68,     1,
     130,    60,    61,   584,   127,   122,   587,   584,   127,   127,
     587,   589,    14,    15,    16,    17,    18,   127,   121,   118,
     123,    80,   125,   126,   122,   127,    43,    87,    87,   520,
      89,    33,    34,    35,    87,   616,    87,    87,   127,   616,
      76,   127,   121,    87,    87,   615,    87,   122,   129,   129,
      87,   129,   129,   544,    87,    87,    49,    70,    60,    61,
     641,   129,   121,   129,   641,   129,   127,    71,   127,    69,
     129,   130,   118,   118,    70,   656,   130,    72,    80,   656,
     127,   130,   130,     5,    73,    87,   223,    89,   127,   127,
     130,   185,   127,   670,   118,   520,   127,   127,   361,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,   130,   692,   130,   540,   234,   121,
      36,    37,    38,    39,    40,    41,   385,   418,   502,   635,
     707,   695,   707,   476,   711,    13,   553,   403,   672,   450,
     352,    14,   525,   318,   725,   630,     0,     1,   725,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
     692,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,   523,
       1,   694,    36,    37,    38,    39,    40,    41,   195,   195,
      -1,    -1,    -1,    14,    15,    16,    17,    18,    -1,    -1,
      -1,   117,     1,   119,    -1,   121,    -1,   123,    -1,   125,
     126,    -1,    33,    34,    35,    14,    15,    16,    17,    18,
      -1,    42,    43,    44,    45,    46,    47,    48,    -1,    50,
      51,    52,    -1,    -1,    33,    34,    35,    -1,    -1,    60,
      61,    -1,    -1,    42,    43,    44,    45,    46,    47,    48,
      -1,    50,    51,    52,    -1,    -1,    -1,    -1,    -1,    80,
      -1,    60,    61,   117,    -1,   119,    87,   121,    89,   123,
      -1,   125,   126,    -1,   128,    -1,   130,    -1,    -1,    -1,
      -1,    80,    -1,    -1,    -1,    -1,    -1,    -1,    87,    -1,
      89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     121,     1,    -1,    -1,    -1,    -1,   127,    -1,   129,   130,
      -1,    -1,    -1,    -1,    14,    15,    16,    17,    18,    -1,
      -1,    -1,   121,     1,    -1,    -1,    -1,    -1,   127,    -1,
     129,   130,    -1,    33,    34,    35,    14,    15,    16,    17,
      18,    -1,    42,    43,    44,    45,    46,    47,    48,    -1,
      50,    51,    52,    -1,    -1,    33,    34,    35,    -1,    -1,
      60,    61,    -1,    -1,    42,    43,    44,    45,    46,    47,
      48,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,
      80,    -1,    60,    61,    -1,    -1,    -1,    87,    -1,    89,
      -1,    -1,    15,    16,    -1,    -1,    19,    20,    -1,     1,
      23,    -1,    80,    -1,    -1,    -1,    -1,    -1,    -1,    87,
      -1,    89,    14,    15,    16,    17,    18,    -1,    -1,    -1,
      -1,   121,     1,    -1,    -1,    -1,    -1,   127,    -1,   129,
     130,    33,    34,    35,     1,    14,    15,    16,    17,    18,
      -1,    -1,    -1,   121,    -1,    -1,    -1,    -1,    -1,   127,
      -1,   129,   130,    -1,    33,    34,    35,    -1,    60,    61,
      -1,    -1,    -1,    42,    43,    44,    45,    46,    47,    48,
      -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    80,    -1,
      -1,    60,    61,    -1,    -1,    87,    -1,    89,    55,    56,
      57,    58,    59,    -1,    -1,    62,    63,    64,   121,    -1,
     123,    80,   125,   126,    -1,    -1,    -1,    -1,    87,    -1,
      89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   121,
      87,    88,    -1,    90,    91,    92,    93,    94,    95,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   121,    -1,    -1,    -1,    -1,    -1,   127,    -1,
     129,   130,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    -1,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    -1,    -1,    -1,    36,    37,    38,    39,    40,
      41,     1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,     1,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    -1,    -1,    -1,    36,    37,    38,    39,
      40,    41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,    -1,
      58,    59,    -1,    -1,    62,    -1,    -1,    -1,    55,    56,
      -1,    58,    59,    -1,    -1,    62,   117,    -1,   119,    -1,
     121,    -1,   123,    -1,   125,   126,    -1,    -1,    -1,   130,
      88,    -1,    90,    91,    92,    93,    94,    95,    -1,    -1,
      -1,    88,    -1,    90,    91,    92,    93,    94,    95,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,    -1,   119,
      -1,   121,    -1,   123,   122,   125,   126,   127,     1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      -1,    -1,    -1,    36,    37,    38,    39,    40,    41,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
       1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    -1,
      -1,    -1,    36,    37,    38,    39,    40,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    -1,    58,    59,    -1,
      -1,    62,    63,    64,    55,    56,    -1,    58,    59,    -1,
      -1,    62,    73,    74,   117,    -1,   119,    -1,   121,    -1,
     123,    -1,   125,   126,    -1,    -1,    87,    88,    -1,    90,
      91,    92,    93,    94,    95,    -1,    -1,    88,    -1,    90,
      91,    92,    93,    94,    95,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   117,    -1,   119,    -1,   121,    -1,   123,
      -1,   125,   126,    -1,   128,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    -1,    -1,    -1,    36,    37,
      38,    39,    40,    41,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,     1,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    -1,    -1,    -1,    36,    37,    38,
      39,    40,    41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    -1,    58,    59,    -1,    -1,    62,    -1,    64,    55,
      56,    -1,    58,    59,    -1,    -1,    62,    73,    74,   117,
      -1,   119,    -1,   121,    -1,   123,    -1,   125,   126,    -1,
     128,    87,    88,    -1,    90,    91,    92,    93,    94,    95,
      -1,    -1,    88,    -1,    90,    91,    92,    93,    94,    95,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,   118,
     119,    -1,   121,    -1,   123,    -1,   125,   126,   127,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    -1,
      -1,    -1,    36,    37,    38,    39,    40,    41,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    -1,
      -1,    36,    37,    38,    39,    40,    41,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    55,    56,    -1,    58,    59,    -1,    -1,    62,    55,
      56,    -1,    58,    59,    -1,    -1,    62,    55,    56,    57,
      58,    59,    -1,   117,    62,   119,    64,   121,    -1,   123,
      -1,   125,   126,   127,    88,    -1,    90,    91,    92,    93,
      94,    95,    88,    -1,    90,    91,    92,    93,    94,    95,
      88,    -1,    90,    91,    92,    93,    94,    95,    -1,    -1,
      -1,    -1,   117,    -1,   119,    -1,   121,    -1,   123,    -1,
     125,   126,   127,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,   130,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    -1,    -1,    -1,    36,    37,    38,    39,
      40,    41,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    -1,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    -1,    -1,    -1,    36,    37,    38,    39,    40,
      41,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,    55,    56,    -1,    58,    59,    -1,    -1,    62,
      -1,    55,    56,    57,    58,    59,    -1,   117,    62,   119,
      -1,   121,    -1,   123,    -1,   125,   126,   127,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    90,    91,    92,
      93,    94,    95,    -1,    88,    -1,    90,    91,    92,    93,
      94,    95,    -1,    -1,    -1,    -1,   117,    -1,   119,    -1,
     121,   122,   123,    -1,   125,   126,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,   130,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    -1,    -1,    -1,    36,
      37,    38,    39,    40,    41,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    -1,    -1,    -1,    36,    37,
      38,    39,    40,    41,    -1,    -1,    -1,    -1,    85,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,
      57,    58,    59,    -1,    -1,    62,    55,    56,    -1,    58,
      59,    -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,
     117,    -1,   119,    -1,   121,    -1,   123,    -1,   125,   126,
      -1,    88,    -1,    90,    91,    92,    93,    94,    95,    88,
      -1,    90,    91,    92,    93,    94,    95,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,
      -1,   119,    -1,   121,    -1,   123,   124,   125,   126,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    -1,
      -1,    -1,    36,    37,    38,    39,    40,    41,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    -1,
      -1,    36,    37,    38,    39,    40,    41,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   117,   118,   119,    -1,   121,    -1,   123,
      -1,   125,   126,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   117,    -1,   119,    -1,   121,    -1,   123,   124,
     125,   126,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    -1,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    -1,    -1,    -1,    36,    37,    38,    39,    40,
      41,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    -1,    -1,    -1,    36,    37,    38,    39,    40,    41,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   117,    -1,   119,    -1,
     121,    -1,   123,   124,   125,   126,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   117,    -1,   119,    -1,   121,
      -1,   123,   124,   125,   126,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    -1,    -1,    -1,    36,    37,
      38,    39,    40,    41,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    -1,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    -1,    -1,    -1,    36,    37,    38,
      39,    40,    41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,
      -1,   119,    -1,   121,    -1,   123,   124,   125,   126,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,    -1,
     119,    -1,   121,    -1,   123,   124,   125,   126,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    -1,
      -1,    36,    37,    38,    39,    40,    41,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    -1,    -1,    -1,
      36,    37,    38,    39,    40,    41,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   117,    -1,   119,    -1,   121,    -1,   123,   124,
     125,   126,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   117,   118,   119,    -1,   121,    -1,   123,    -1,   125,
     126,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    -1,    -1,    -1,    36,    37,    38,    39,    40,    41,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    -1,    -1,
      -1,     1,    -1,    36,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    14,    15,    16,    17,    18,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    33,    34,    35,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   117,    -1,   119,    -1,   121,
      -1,   123,    -1,   125,   126,    -1,    -1,    -1,    -1,    -1,
      60,    61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      80,    -1,    -1,    -1,   117,    -1,   119,    87,   121,    89,
     123,    -1,   125,   126,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    -1,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,   121,    -1,     1,    -1,    -1,    -1,    36,    37,    38,
      39,    40,    41,    -1,     1,    -1,    14,    15,    16,    17,
      18,    -1,    -1,    -1,    -1,    -1,    -1,    14,    15,    16,
      17,    18,    -1,    -1,    -1,    33,    34,    35,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    35,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    60,    61,    -1,    -1,    -1,    -1,    55,    56,
      -1,    58,    59,    60,    61,    62,    -1,    -1,    -1,    -1,
      -1,    -1,    80,    -1,    -1,    -1,    -1,    -1,   117,    87,
     119,    89,   121,    80,   123,    -1,   125,   126,     1,    -1,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    -1,
      -1,    14,    15,    16,    17,    18,    14,    15,    16,    17,
      18,    -1,    -1,   121,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    34,    35,    -1,   121,    33,    34,    35,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    14,    15,    16,    17,
      18,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    -1,
      -1,    -1,    60,    61,    -1,    33,    34,    35,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,    -1,    -1,
      -1,    -1,    80,    -1,    87,    -1,    89,    -1,    -1,    87,
      -1,    89,    60,    61,    -1,    -1,    14,    15,    16,    17,
      18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    80,    -1,    -1,    33,    34,    35,   121,    87,
      88,    89,    -1,   121,    42,    43,    44,    45,    46,    47,
      48,    -1,   130,    -1,    52,    14,    15,    16,    17,    18,
      -1,    -1,    60,    61,    -1,    -1,    14,    15,    16,    17,
      18,    -1,    -1,   121,    33,    34,    35,    -1,    -1,    -1,
      -1,   129,    80,    -1,    -1,    33,    34,    35,    -1,    87,
      -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    60,    61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    60,    61,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    80,    -1,   121,    -1,    -1,    -1,    -1,    87,   127,
      89,   129,    80,    -1,    -1,    -1,    -1,    -1,    -1,    87,
      -1,    89,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    -1,    -1,    -1,    -1,
      -1,    -1,   121,    36,    37,    38,    39,    40,    41,    -1,
     129,    -1,    -1,   121,    14,    15,    16,    17,    18,   127,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    33,    34,    35,    -1,    -1,    -1,    -1,
      -1,    36,    37,    38,    39,    40,    41,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    -1,    25,    26,    27,
      60,    61,    -1,    -1,    -1,    -1,    -1,    -1,    36,    37,
      38,    39,    40,    41,    -1,    -1,    -1,    -1,    -1,    -1,
      80,    81,    82,    83,    84,    -1,   119,    87,   121,    89,
     123,    -1,   125,   126,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    -1,    -1,    26,    27,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    37,    38,    39,    40,
      41,   121,    -1,    -1,   119,    -1,   121,    -1,   123,    -1,
     125,   126,    -1,    -1,    -1,    -1,    -1,    -1,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    -1,    -1,    26,
      27,   119,    -1,   121,    -1,   123,    -1,   125,   126,    36,
      37,    38,    39,    40,    41,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    -1,    -1,    26,    27,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    37,    -1,    -1,
      40,    41,    14,    15,    16,    17,    18,    -1,   119,     1,
     121,    -1,   123,    -1,   125,   126,    -1,    -1,    -1,    -1,
      -1,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     0,     1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,
      -1,    -1,    -1,    -1,   121,    -1,   123,    -1,   125,   126,
      -1,    -1,    -1,    55,    56,    57,    58,    59,    80,    -1,
      62,    -1,    -1,    65,    -1,    87,     1,    89,    -1,    -1,
      -1,   121,    -1,   123,    -1,   125,   126,    54,    55,    56,
      -1,    58,    59,    -1,    -1,    62,    88,    64,    90,    91,
      92,    93,    94,    95,    -1,    -1,    73,    74,    -1,   121,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,
      87,    88,    -1,    90,    91,    92,    93,    94,    95,    54,
      55,    56,    -1,    58,    59,    -1,    -1,    62,    63,    64,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    87,    88,    -1,    90,    91,    92,    93,    94,
      95,    54,    55,    56,    -1,    58,    59,    -1,    -1,    62,
      -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    90,    91,    92,
      93,    94,    95
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   133,     1,   134,   150,   150,   185,   150,   134,
      55,    56,    58,    59,    62,    88,    90,    91,    92,    93,
      94,    95,   156,   157,   174,   181,    14,    15,    16,    17,
      18,    33,    34,    35,    60,    61,    80,    87,    89,   121,
     233,   239,   241,   233,   202,   233,   232,   233,    87,    88,
     175,   199,   243,   244,   244,   265,     1,   135,    57,   174,
     257,   258,   261,   233,   269,   233,   277,   232,   278,   279,
     233,     0,   127,    54,    63,    64,    73,    74,    87,    92,
     136,   139,   140,   145,   151,   152,   153,   158,   170,   174,
     182,   153,   158,   170,   129,    59,   123,   123,   128,    87,
     119,    55,    88,    90,    91,    92,    95,   233,   233,   233,
     121,   121,     1,   233,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    36,    37,    38,    39,    40,    41,   117,
     119,   121,   123,   125,   126,   240,   233,     1,    14,   117,
     128,   118,   128,    57,    64,   135,   158,   174,   245,   250,
     245,   127,   136,   262,   259,   127,   260,   128,     1,   128,
     128,    81,    82,    83,    84,   233,   280,   281,     1,   174,
       1,    87,   146,   175,   129,   129,   121,   138,    53,    75,
     148,   159,   160,   175,     1,   174,   176,   177,   233,   233,
     157,   166,   167,    87,   129,   123,   123,   175,   175,   122,
     122,   233,   233,   233,   233,   233,   233,   233,   233,   233,
     233,   233,   233,   233,   233,   233,   236,   233,   233,   233,
     233,   233,   233,   233,   233,   234,   235,     1,   233,    87,
     233,    14,   117,   233,   174,   175,     1,   246,     1,   175,
     139,   175,    87,    87,   258,   261,   128,   263,   128,   233,
     233,    85,   131,   233,   127,   171,   172,   175,   127,    36,
     127,   128,   147,   121,   155,   232,   232,   122,   156,     3,
       1,    51,    87,   141,   143,   144,   129,   127,   128,   155,
     161,   130,   175,   178,   179,   130,   177,   128,   124,   123,
     168,   166,     1,   176,   233,   233,   118,   118,   233,   118,
     233,   242,     1,   124,   124,   118,   127,    87,   247,   248,
     129,     1,   121,   129,   256,   166,   166,    87,    87,   233,
     127,   128,   173,    87,    87,     1,   122,   156,   129,   130,
     130,   122,    87,   127,    36,   127,   128,   142,   123,   149,
     160,   129,   166,   180,   127,   128,   233,     1,   174,   233,
     130,   130,   128,   124,   174,   174,   233,   122,   128,   122,
     174,   249,   127,   128,   254,   129,     1,   122,   257,   255,
       1,   129,   166,   166,   172,   166,   122,   122,   183,   121,
     143,   143,   233,   130,   233,   154,     3,   162,   166,   179,
     124,   124,   124,   124,   233,   122,   122,   233,   166,   248,
     264,   265,   253,   122,   122,   264,   129,   251,   184,   185,
     137,   124,   118,   127,   215,   129,   163,   233,   168,   169,
     168,   124,   237,   238,   163,   130,     1,    65,   266,   264,
     130,   252,   264,   130,     1,    65,   186,   242,   233,   158,
     170,   216,    87,   163,   164,   165,   175,   168,   233,   233,
     127,    87,   267,   268,   204,   130,   264,   130,   127,    87,
     187,   188,   204,   122,   127,     1,    42,    43,    44,    45,
      46,    47,    48,    52,   127,   129,   130,   213,   217,   233,
     128,   130,   118,   129,   127,   128,     1,    58,    66,    67,
      78,    79,   189,   205,   206,   207,   208,   130,   129,   127,
     128,   189,   127,   127,   121,   121,   221,   127,   127,   121,
     121,   127,   233,   214,   127,   165,   163,   269,   268,   127,
       1,    87,   210,     1,    87,   209,    87,     1,    87,   211,
       1,    87,   212,    68,   270,     1,   233,   188,    68,   190,
       1,   175,   232,     1,   220,   217,   232,   222,   127,   215,
     130,   127,   127,   128,   127,   127,   128,   127,   127,   127,
     128,   127,   127,   128,     1,    87,   271,   272,   130,   130,
       1,    87,   191,   192,   122,   118,   127,   122,   232,    43,
     122,   232,   216,    87,    87,    87,    87,   127,    76,   127,
     128,   127,    76,    77,   127,   128,   217,   174,   232,   217,
     122,   121,   223,   122,   130,    87,    76,   272,   274,    87,
      87,    76,    77,   192,   195,   122,   127,   217,   232,   129,
     217,   129,    87,   129,   129,    87,    87,   219,   232,   122,
      50,    51,   226,   227,    49,   224,   273,   129,   193,   194,
     129,   129,   217,   122,   127,     1,   233,     1,   118,   130,
     227,   225,    70,   276,   275,    69,   198,   198,   196,   197,
     218,   118,   118,   118,   230,   217,   277,    71,   201,   276,
     199,    70,   200,   200,   198,   198,   217,   229,   228,   231,
     216,     1,   127,     1,   202,    72,   203,   201,   127,     1,
     233,   201,   201,   200,   200,   216,   216,   216,   127,   127,
     127,     1,   232,   130,   203,   127,     1,   127,   203,   203,
     201,   201,   127,   127,   130,   127,   130,   130,   203,   203,
     130,   130
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   132,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   134,   135,   135,   135,   137,   136,   138,
     138,   138,   139,   140,   140,   141,   141,   141,   142,   143,
     143,   144,   144,   145,   145,   146,   146,   146,   147,   148,
     148,   149,   149,   149,   150,   150,   150,   150,   150,   150,
     150,   150,   150,   150,   151,   152,   154,   153,   155,   155,
     155,   156,   156,   157,   157,   158,   159,   159,   161,   160,
     162,   162,   163,   163,   164,   164,   165,   165,   167,   166,
     168,   168,   169,   168,   168,   170,   170,   171,   171,   173,
     172,   174,   174,   174,   174,   174,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   174,   174,   174,   175,
     175,   176,   176,   177,   178,   178,   180,   179,   181,   181,
     181,   181,   181,   183,   182,   184,   185,   185,   185,   185,
     186,   186,   187,   187,   188,   188,   188,   189,   189,   190,
     190,   190,   191,   191,   193,   192,   194,   192,   196,   195,
     197,   195,   195,   198,   198,   199,   199,   200,   200,   200,
     200,   201,   201,   201,   202,   202,   202,   202,   203,   203,
     203,   204,   204,   204,   204,   204,   205,   205,   206,   206,
     207,   207,   208,   208,   209,   209,   210,   210,   211,   211,
     212,   212,   214,   213,   215,   215,   215,   216,   216,   216,
     217,   217,   217,   218,   217,   219,   217,   217,   220,   217,
     217,   221,   217,   222,   217,   217,   217,   223,   217,   217,
     217,   224,   225,   224,   226,   226,   228,   227,   229,   227,
     230,   227,   231,   227,   232,   232,   233,   233,   233,   233,
     234,   233,   235,   233,   233,   233,   233,   233,   233,   233,
     233,   233,   233,   233,   233,   233,   233,   233,   233,   233,
     233,   233,   233,   233,   233,   233,   233,   233,   233,   233,
     233,   233,   233,   233,   233,   236,   233,   233,   233,   233,
     233,   233,   237,   233,   238,   233,   233,   239,   240,   240,
     240,   240,   240,   240,   240,   240,   240,   240,   240,   241,
     241,   241,   242,   242,   242,   243,   244,   244,   244,   245,
     246,   245,   245,   247,   247,   249,   248,   251,   250,   252,
     250,   253,   250,   254,   250,   255,   250,   256,   256,   256,
     257,   257,   257,   257,   259,   258,   260,   258,   262,   261,
     263,   261,   264,   265,   265,   266,   266,   267,   267,   268,
     268,   269,   269,   269,   270,   270,   270,   271,   271,   273,
     272,   275,   274,   274,   276,   276,   276,   277,   277,   278,
     279,   279,   280,   280,   280,   281,   281,   281,   281
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     0,     2,     2,     0,     9,     0,
       2,     3,     2,     4,     4,     1,     3,     3,     1,     1,
       1,     1,     4,     3,     3,     1,     3,     3,     1,     0,
       4,     0,     5,     3,     0,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     4,     4,     0,     8,     2,     3,
       3,     1,     3,     4,     3,     3,     1,     3,     0,     4,
       0,     2,     1,     3,     1,     3,     3,     1,     0,     2,
       0,     4,     0,     5,     4,     4,     3,     1,     3,     0,
       3,     1,     2,     4,     5,     4,     5,     1,     2,     1,
       2,     6,     7,     1,     2,     1,     1,     4,     5,     1,
       1,     1,     2,     3,     1,     3,     0,     3,     1,     1,
       2,     1,     1,     0,     7,     5,     0,     2,     2,     2,
       3,     2,     1,     3,     1,     4,     4,     3,     2,     0,
       3,     3,     1,     3,     0,    10,     0,    10,     0,     9,
       0,     9,     1,     0,     3,     3,     5,     0,     3,     4,
       3,     0,     3,     3,     2,     3,     2,     3,     0,     3,
       3,     0,     2,     2,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     0,     5,     0,     2,     2,     0,     2,     3,
       1,     1,     2,     0,    10,     0,     8,     5,     0,     6,
       5,     0,     8,     0,     7,     2,     2,     0,     8,     3,
       2,     0,     0,     3,     1,     2,     0,     5,     0,     5,
       0,     4,     0,     5,     1,     3,     1,     1,     1,     1,
       0,     5,     0,     5,     4,     4,     3,     3,     2,     2,
       2,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     5,     3,     2,     1,     0,     4,     3,     3,     2,
       3,     3,     0,     8,     0,     8,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     1,     3,     3,     0,     2,     2,     1,
       0,     4,     3,     1,     3,     0,     4,     0,     7,     0,
       8,     0,     7,     0,     6,     0,     6,     2,     3,     3,
       1,     1,     3,     3,     0,     4,     0,     5,     0,     4,
       0,     5,     5,     0,     2,     3,     2,     1,     3,     1,
       4,     1,     3,     3,     0,     3,     3,     1,     3,     0,
       9,     0,     8,     1,     0,     3,     4,     1,     3,     2,
       0,     3,     0,     2,     3,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 197 "parser.yy" /* yacc.c:1652  */
    { CALL((yylsp[0]), (yylsp[0]), done()); }
#line 2790 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 3:
#line 198 "parser.yy" /* yacc.c:1652  */
    { }
#line 2796 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 4:
#line 199 "parser.yy" /* yacc.c:1652  */
    { }
#line 2802 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 5:
#line 200 "parser.yy" /* yacc.c:1652  */
    { }
#line 2808 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 6:
#line 201 "parser.yy" /* yacc.c:1652  */
    { }
#line 2814 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 7:
#line 202 "parser.yy" /* yacc.c:1652  */
    { }
#line 2820 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 8:
#line 203 "parser.yy" /* yacc.c:1652  */
    { }
#line 2826 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 9:
#line 204 "parser.yy" /* yacc.c:1652  */
    { }
#line 2832 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 10:
#line 205 "parser.yy" /* yacc.c:1652  */
    { CALL((yylsp[0]), (yylsp[0]), procGuard()); }
#line 2838 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 11:
#line 206 "parser.yy" /* yacc.c:1652  */
    { }
#line 2844 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 12:
#line 207 "parser.yy" /* yacc.c:1652  */
    { CALL((yylsp[0]), (yylsp[0]), procUpdate()); }
#line 2850 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 13:
#line 208 "parser.yy" /* yacc.c:1652  */
    { CALL((yylsp[0]), (yylsp[0]), done()); }
#line 2856 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 14:
#line 209 "parser.yy" /* yacc.c:1652  */
    { }
#line 2862 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 15:
#line 210 "parser.yy" /* yacc.c:1652  */
    { }
#line 2868 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 16:
#line 211 "parser.yy" /* yacc.c:1652  */
    { }
#line 2874 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 17:
#line 212 "parser.yy" /* yacc.c:1652  */
    { }
#line 2880 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 18:
#line 213 "parser.yy" /* yacc.c:1652  */
    { }
#line 2886 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 19:
#line 214 "parser.yy" /* yacc.c:1652  */
    { CALL((yylsp[0]), (yylsp[0]), procGuard()); }
#line 2892 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 20:
#line 215 "parser.yy" /* yacc.c:1652  */
    { CALL((yylsp[0]), (yylsp[0]), procUpdate()); }
#line 2898 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 21:
#line 216 "parser.yy" /* yacc.c:1652  */
    {}
#line 2904 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 22:
#line 217 "parser.yy" /* yacc.c:1652  */
    {}
#line 2910 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 27:
#line 231 "parser.yy" /* yacc.c:1652  */
    {
          CALL((yylsp[-4]), (yylsp[-1]), instantiationBegin((yyvsp[-4].string), (yyvsp[-3].number), (yyvsp[-1].string)));
	}
#line 2918 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 28:
#line 233 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-8]), (yylsp[0]), instantiationEnd((yyvsp[-8].string), (yyvsp[-7].number), (yyvsp[-5].string), (yyvsp[-2].number)));
	}
#line 2926 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 29:
#line 238 "parser.yy" /* yacc.c:1652  */
    { (yyval.number) = 0; }
#line 2932 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 30:
#line 240 "parser.yy" /* yacc.c:1652  */
    {
		(yyval.number) = 0;
	  }
#line 2940 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 31:
#line 244 "parser.yy" /* yacc.c:1652  */
    {
		(yyval.number) = (yyvsp[-1].number);
	  }
#line 2948 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 38:
#line 262 "parser.yy" /* yacc.c:1652  */
    { CALL((yylsp[0]), (yylsp[0]), incChanPriority()); }
#line 2954 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 39:
#line 266 "parser.yy" /* yacc.c:1652  */
    { CALL((yylsp[0]), (yylsp[0]), chanPriority()); }
#line 2960 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 40:
#line 267 "parser.yy" /* yacc.c:1652  */
    { CALL((yylsp[0]), (yylsp[0]), defaultChanPriority()); }
#line 2966 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 41:
#line 271 "parser.yy" /* yacc.c:1652  */
    { CALL((yylsp[0]), (yylsp[0]), exprId((yyvsp[0].string))); }
#line 2972 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 42:
#line 272 "parser.yy" /* yacc.c:1652  */
    { CALL((yylsp[-3]), (yylsp[0]), exprArray()); }
#line 2978 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 45:
#line 281 "parser.yy" /* yacc.c:1652  */
    { CALL((yylsp[0]), (yylsp[0]), process((yyvsp[0].string))); }
#line 2984 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 46:
#line 282 "parser.yy" /* yacc.c:1652  */
    { CALL((yylsp[0]), (yylsp[0]), process((yyvsp[0].string))); }
#line 2990 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 47:
#line 283 "parser.yy" /* yacc.c:1652  */
    { CALL((yylsp[0]), (yylsp[0]), process((yyvsp[0].string))); }
#line 2996 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 48:
#line 287 "parser.yy" /* yacc.c:1652  */
    { CALL((yylsp[0]), (yylsp[0]), incProcPriority()); }
#line 3002 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 52:
#line 295 "parser.yy" /* yacc.c:1652  */
    {
            CALL((yylsp[-3]), (yylsp[-1]), declProgress(true));
        }
#line 3010 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 53:
#line 298 "parser.yy" /* yacc.c:1652  */
    {
            CALL((yylsp[-1]), (yylsp[-1]), declProgress(false));
        }
#line 3018 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 64:
#line 315 "parser.yy" /* yacc.c:1652  */
    { CALL((yylsp[-1]), (yylsp[-1]), beforeUpdate()); }
#line 3024 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 65:
#line 317 "parser.yy" /* yacc.c:1652  */
    { CALL((yylsp[-1]), (yylsp[-1]), afterUpdate()); }
#line 3030 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 66:
#line 324 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-3]), (yylsp[-2]), declFuncBegin((yyvsp[-2].string)));
	}
#line 3038 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 67:
#line 326 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[0]), (yylsp[0]), declFuncEnd());
	}
#line 3046 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 71:
#line 337 "parser.yy" /* yacc.c:1652  */
    { (yyval.number) = 1; }
#line 3052 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 72:
#line 338 "parser.yy" /* yacc.c:1652  */
    { (yyval.number) = (yyvsp[-2].number)+1; }
#line 3058 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 73:
#line 342 "parser.yy" /* yacc.c:1652  */
    {
          CALL((yylsp[-3]), (yylsp[0]), declParameter((yyvsp[-1].string), true));
	}
#line 3066 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 74:
#line 345 "parser.yy" /* yacc.c:1652  */
    {
          CALL((yylsp[-2]), (yylsp[0]), declParameter((yyvsp[-1].string), false));
	}
#line 3074 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 75:
#line 351 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-2]), (yylsp[0]), typePop());
	}
#line 3082 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 78:
#line 362 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[0]), (yylsp[0]), typeDuplicate());
	}
#line 3090 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 79:
#line 364 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-3]), (yylsp[0]), declVar((yyvsp[-3].string), (yyvsp[0].flag)));
	}
#line 3098 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 80:
#line 370 "parser.yy" /* yacc.c:1652  */
    { (yyval.flag) = false; }
#line 3104 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 81:
#line 371 "parser.yy" /* yacc.c:1652  */
    { (yyval.flag) = true; }
#line 3110 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 83:
#line 376 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), declInitialiserList((yyvsp[-1].number)));
	}
#line 3118 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 84:
#line 382 "parser.yy" /* yacc.c:1652  */
    { (yyval.number) = 1; }
#line 3124 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 85:
#line 383 "parser.yy" /* yacc.c:1652  */
    { (yyval.number) = (yyvsp[-2].number)+1; }
#line 3130 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 86:
#line 387 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), declFieldInit((yyvsp[-2].string)));
	}
#line 3138 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 87:
#line 390 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[0]), (yylsp[0]), declFieldInit(""));
	}
#line 3146 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 88:
#line 396 "parser.yy" /* yacc.c:1652  */
    { types = 0; }
#line 3152 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 91:
#line 400 "parser.yy" /* yacc.c:1652  */
    { CALL((yylsp[-3]), (yylsp[-1]), typeArrayOfSize(types)); }
#line 3158 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 92:
#line 401 "parser.yy" /* yacc.c:1652  */
    { types++; }
#line 3164 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 93:
#line 401 "parser.yy" /* yacc.c:1652  */
    { CALL((yylsp[-4]), (yylsp[-2]), typeArrayOfType(types--)); }
#line 3170 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 95:
#line 406 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-3]), (yylsp[0]), typePop());
	}
#line 3178 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 99:
#line 418 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[0]), (yylsp[0]), typeDuplicate());
	}
#line 3186 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 100:
#line 420 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-2]), (yylsp[0]), declTypeDef((yyvsp[-2].string)));
	}
#line 3194 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 101:
#line 426 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[0]), (yylsp[0]), typeName(ParserBuilder::PREFIX_NONE, (yyvsp[0].string)));
	}
#line 3202 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 102:
#line 429 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-1]), (yylsp[0]), typeName((yyvsp[-1].prefix), (yyvsp[0].string)));
	}
#line 3210 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 103:
#line 432 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-3]), (yylsp[0]), typeStruct(ParserBuilder::PREFIX_NONE, (yyvsp[-1].number)));
	}
#line 3218 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 104:
#line 435 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-4]), (yylsp[0]), typeStruct((yyvsp[-4].prefix), (yyvsp[-1].number)));
	}
#line 3226 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 105:
#line 438 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-3]), (yylsp[0]), typeStruct(ParserBuilder::PREFIX_NONE, 0));
	}
#line 3234 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 106:
#line 441 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-4]), (yylsp[0]), typeStruct(ParserBuilder::PREFIX_NONE, 0));
	}
#line 3242 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 107:
#line 444 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[0]), (yylsp[0]), typeBool(ParserBuilder::PREFIX_NONE));
	}
#line 3250 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 108:
#line 447 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-1]), (yylsp[0]), typeBool((yyvsp[-1].prefix)));
	}
#line 3258 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 109:
#line 450 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[0]), (yylsp[0]), typeInt(ParserBuilder::PREFIX_NONE));
	}
#line 3266 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 110:
#line 453 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-1]), (yylsp[0]), typeInt((yyvsp[-1].prefix)));
	}
#line 3274 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 111:
#line 457 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-5]), (yylsp[0]), typeBoundedInt(ParserBuilder::PREFIX_NONE));
	}
#line 3282 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 112:
#line 460 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-6]), (yylsp[0]), typeBoundedInt((yyvsp[-6].prefix)));
	}
#line 3290 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 113:
#line 463 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[0]), (yylsp[0]), typeChannel(ParserBuilder::PREFIX_NONE));
	}
#line 3298 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 114:
#line 466 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-1]), (yylsp[0]), typeChannel((yyvsp[-1].prefix)));
	}
#line 3306 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 115:
#line 469 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[0]), (yylsp[0]), typeClock());
	}
#line 3314 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 116:
#line 472 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[0]), (yylsp[0]), typeVoid());
	}
#line 3322 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 117:
#line 476 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-3]), (yylsp[0]), typeScalar(ParserBuilder::PREFIX_NONE));
	}
#line 3330 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 118:
#line 479 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-4]), (yylsp[0]), typeScalar((yyvsp[-4].prefix)));
	}
#line 3338 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 119:
#line 485 "parser.yy" /* yacc.c:1652  */
    { strncpy((yyval.string), (yyvsp[0].string), MAXLEN); }
#line 3344 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 120:
#line 486 "parser.yy" /* yacc.c:1652  */
    { strncpy((yyval.string), (yyvsp[0].string), MAXLEN); }
#line 3350 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 121:
#line 490 "parser.yy" /* yacc.c:1652  */
    { (yyval.number)=(yyvsp[0].number); }
#line 3356 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 122:
#line 491 "parser.yy" /* yacc.c:1652  */
    { (yyval.number)=(yyvsp[-1].number)+(yyvsp[0].number); }
#line 3362 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 123:
#line 495 "parser.yy" /* yacc.c:1652  */
    {
	  (yyval.number) = (yyvsp[-1].number);
	  CALL((yylsp[-2]), (yylsp[0]), typePop());
	}
#line 3371 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 124:
#line 502 "parser.yy" /* yacc.c:1652  */
    { (yyval.number)=1; }
#line 3377 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 125:
#line 503 "parser.yy" /* yacc.c:1652  */
    { (yyval.number)=(yyvsp[-2].number)+1; }
#line 3383 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 126:
#line 507 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[0]), (yylsp[0]), typeDuplicate());
	}
#line 3391 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 127:
#line 509 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-2]), (yylsp[0]), structField((yyvsp[-2].string)));
	}
#line 3399 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 128:
#line 515 "parser.yy" /* yacc.c:1652  */
    { (yyval.prefix) = ParserBuilder::PREFIX_URGENT; }
#line 3405 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 129:
#line 516 "parser.yy" /* yacc.c:1652  */
    { (yyval.prefix) = ParserBuilder::PREFIX_BROADCAST; }
#line 3411 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 130:
#line 517 "parser.yy" /* yacc.c:1652  */
    { (yyval.prefix) = ParserBuilder::PREFIX_URGENT_BROADCAST; }
#line 3417 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 131:
#line 518 "parser.yy" /* yacc.c:1652  */
    { (yyval.prefix) = ParserBuilder::PREFIX_CONST; }
#line 3423 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 132:
#line 519 "parser.yy" /* yacc.c:1652  */
    { (yyval.prefix) = ParserBuilder::PREFIX_META; }
#line 3429 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 133:
#line 527 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-3]), (yylsp[0]), procBegin((yyvsp[-2].string)));
	}
#line 3437 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 134:
#line 530 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-1]), (yylsp[0]), procEnd());
	}
#line 3445 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 144:
#line 557 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[0]), (yylsp[0]), procState((yyvsp[0].string), false));
	}
#line 3453 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 145:
#line 560 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-3]), (yylsp[0]), procState((yyvsp[-3].string), true));
	}
#line 3461 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 146:
#line 563 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-3]), (yylsp[0]), procState((yyvsp[-3].string), false));
	}
#line 3469 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 147:
#line 569 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), procStateInit((yyvsp[-1].string)));
	}
#line 3477 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 154:
#line 587 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-3]), (yylsp[-1]), procEdgeBegin((yyvsp[-3].string), (yyvsp[-1].string), true));
	}
#line 3485 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 155:
#line 589 "parser.yy" /* yacc.c:1652  */
    {
	  strcpy(rootTransId, (yyvsp[-9].string));
	  CALL((yylsp[-9]), (yylsp[-2]), procEdgeEnd((yyvsp[-9].string), (yyvsp[-7].string)));
	}
#line 3494 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 156:
#line 593 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-3]), (yylsp[-1]), procEdgeBegin((yyvsp[-3].string), (yyvsp[-1].string), false));
	}
#line 3502 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 157:
#line 595 "parser.yy" /* yacc.c:1652  */
    {
	  strcpy(rootTransId, (yyvsp[-9].string));
	  CALL((yylsp[-9]), (yylsp[-2]), procEdgeEnd((yyvsp[-9].string), (yyvsp[-7].string)));
	}
#line 3511 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 158:
#line 602 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-2]), (yylsp[-1]), procEdgeBegin(rootTransId, (yyvsp[-1].string), true));
        }
#line 3519 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 159:
#line 604 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-8]), (yylsp[-2]), procEdgeEnd(rootTransId, (yyvsp[-7].string)));
	}
#line 3527 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 160:
#line 607 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-2]), (yylsp[-1]), procEdgeBegin(rootTransId, (yyvsp[-1].string), false));
        }
#line 3535 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 161:
#line 609 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-8]), (yylsp[-2]), procEdgeEnd(rootTransId, (yyvsp[-7].string)));
	}
#line 3543 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 165:
#line 621 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-2]), (yylsp[0]), procSelect((yyvsp[-2].string)));
	}
#line 3551 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 166:
#line 624 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-2]), (yylsp[0]), procSelect((yyvsp[-2].string)));
	}
#line 3559 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 168:
#line 630 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-1]), (yylsp[-1]), procGuard());
        }
#line 3567 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 169:
#line 633 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[-1]), procGuard());
	}
#line 3575 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 174:
#line 646 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-1]), (yylsp[0]), procSync(SYNC_BANG));
	}
#line 3583 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 175:
#line 649 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[-1]), procSync(SYNC_QUE));
	}
#line 3591 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 176:
#line 652 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-1]), (yylsp[0]), procSync(SYNC_QUE));
	}
#line 3599 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 177:
#line 655 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[-1]), procSync(SYNC_QUE));
	}
#line 3607 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 179:
#line 662 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-1]), (yylsp[-1]), procUpdate());
	}
#line 3615 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 194:
#line 697 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[0]), (yylsp[0]), procStateCommit((yyvsp[0].string)));
	}
#line 3623 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 195:
#line 700 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), procStateCommit((yyvsp[0].string)));
	}
#line 3631 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 196:
#line 706 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[0]), (yylsp[0]), procStateUrgent((yyvsp[0].string)));
	}
#line 3639 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 197:
#line 709 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), procStateUrgent((yyvsp[0].string)));
	}
#line 3647 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 198:
#line 715 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[0]), (yylsp[0]), procStateWinning((yyvsp[0].string)));
	}
#line 3655 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 199:
#line 718 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), procStateWinning((yyvsp[0].string)));
	}
#line 3663 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 200:
#line 724 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[0]), (yylsp[0]), procStateLosing((yyvsp[0].string)));
	}
#line 3671 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 201:
#line 727 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), procStateLosing((yyvsp[0].string)));
	}
#line 3679 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 202:
#line 738 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[0]), (yylsp[0]), blockBegin());
	}
#line 3687 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 203:
#line 741 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-3]), (yylsp[-1]), blockEnd());
	}
#line 3695 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 211:
#line 760 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[0]), (yylsp[0]), emptyStatement());
	}
#line 3703 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 212:
#line 763 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-1]), (yylsp[0]), exprStatement());
	}
#line 3711 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 213:
#line 766 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-7]), (yylsp[0]), forBegin());
	}
#line 3719 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 214:
#line 769 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-1]), (yylsp[-1]), forEnd());
	}
#line 3727 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 215:
#line 772 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-5]), (yylsp[0]), iterationBegin((yyvsp[-3].string)));
	}
#line 3735 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 216:
#line 775 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-1]), (yylsp[-1]), iterationEnd((yyvsp[-5].string)));
	}
#line 3743 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 218:
#line 779 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-1]), (yylsp[0]), whileBegin());
	}
#line 3751 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 219:
#line 782 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-3]), (yylsp[-2]), whileEnd());
	  }
#line 3759 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 221:
#line 786 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[0]), (yylsp[0]), doWhileBegin());
	}
#line 3767 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 222:
#line 789 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-6]), (yylsp[-1]), doWhileEnd());
	  }
#line 3775 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 223:
#line 792 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-1]), (yylsp[0]), ifBegin());
	}
#line 3783 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 225:
#line 796 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-1]), (yylsp[0]), breakStatement());
	  }
#line 3791 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 226:
#line 799 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-1]), (yylsp[0]), continueStatement());
	}
#line 3799 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 227:
#line 802 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-3]), (yylsp[0]), switchBegin());
	}
#line 3807 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 228:
#line 805 "parser.yy" /* yacc.c:1652  */
    {
	       CALL((yylsp[-3]), (yylsp[-1]), switchEnd());
	   }
#line 3815 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 229:
#line 808 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), returnStatement(true));
	}
#line 3823 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 230:
#line 811 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-1]), (yylsp[0]), returnStatement(false));
	}
#line 3831 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 231:
#line 817 "parser.yy" /* yacc.c:1652  */
    {
	  CALL(position_t(), position_t(), ifEnd(false));
	}
#line 3839 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 232:
#line 820 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[0]), (yylsp[0]), ifElse());
	}
#line 3847 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 233:
#line 823 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-1]), (yylsp[-1]), ifEnd(true));
	  }
#line 3855 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 236:
#line 834 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), caseBegin());
	}
#line 3863 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 237:
#line 837 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-1]), (yylsp[-1]), caseEnd());
	  }
#line 3871 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 238:
#line 840 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), caseBegin());
	}
#line 3879 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 239:
#line 843 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-1]), (yylsp[-1]), caseEnd());
	  }
#line 3887 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 240:
#line 846 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-1]), (yylsp[0]), defaultBegin());
	}
#line 3895 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 241:
#line 849 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-1]), (yylsp[-1]), defaultEnd());
	  }
#line 3903 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 242:
#line 852 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), defaultBegin());
	}
#line 3911 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 243:
#line 855 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-1]), (yylsp[-1]), defaultEnd());
	  }
#line 3919 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 245:
#line 862 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), exprComma());
	}
#line 3927 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 246:
#line 867 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[0]), (yylsp[0]), exprFalse());
	}
#line 3935 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 247:
#line 870 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[0]), (yylsp[0]), exprTrue());
	}
#line 3943 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 248:
#line 873 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[0]), (yylsp[0]), exprNat((yyvsp[0].number)));
	}
#line 3951 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 249:
#line 876 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[0]), (yylsp[0]), exprId((yyvsp[0].string)));
	}
#line 3959 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 250:
#line 879 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-1]), (yylsp[0]), exprCallBegin());
	  }
#line 3967 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 251:
#line 881 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-4]), (yylsp[0]), exprCallEnd((yyvsp[-1].number)));
	}
#line 3975 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 252:
#line 884 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-1]), (yylsp[0]), exprCallBegin());
	  }
#line 3983 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 253:
#line 886 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-4]), (yylsp[0]), exprCallEnd(0));
	}
#line 3991 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 254:
#line 889 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-3]), (yylsp[0]), exprArray());
	}
#line 3999 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 255:
#line 892 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-3]), (yylsp[0]), exprFalse());
	}
#line 4007 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 257:
#line 896 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), exprFalse());
	}
#line 4015 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 258:
#line 899 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-1]), (yylsp[0]), exprPostIncrement());
	}
#line 4023 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 259:
#line 902 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-1]), (yylsp[0]), exprPreIncrement());
	}
#line 4031 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 260:
#line 905 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-1]), (yylsp[0]), exprPostDecrement());
	}
#line 4039 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 261:
#line 908 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-1]), (yylsp[0]), exprPreDecrement());
	}
#line 4047 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 262:
#line 911 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-1]), (yylsp[0]), exprUnary((yyvsp[-1].kind)));
	}
#line 4055 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 263:
#line 914 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), exprBinary(LT));
	}
#line 4063 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 264:
#line 917 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), exprBinary(LE));
	}
#line 4071 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 265:
#line 920 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), exprBinary(EQ));
	}
#line 4079 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 266:
#line 923 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), exprBinary(NEQ));
	}
#line 4087 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 267:
#line 926 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), exprBinary(GT));
	}
#line 4095 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 268:
#line 929 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), exprBinary(GE));
	}
#line 4103 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 269:
#line 932 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), exprBinary(PLUS));
	}
#line 4111 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 270:
#line 935 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), exprBinary(MINUS));
	}
#line 4119 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 271:
#line 938 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), exprBinary(MULT));
	}
#line 4127 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 272:
#line 941 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), exprBinary(DIV));
	}
#line 4135 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 273:
#line 944 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), exprBinary(MOD));
	}
#line 4143 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 274:
#line 947 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), exprBinary(BIT_AND));
	}
#line 4151 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 275:
#line 950 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), exprBinary(BIT_OR));
	}
#line 4159 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 276:
#line 953 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), exprBinary(BIT_XOR));
	}
#line 4167 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 277:
#line 956 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), exprBinary(BIT_LSHIFT));
	}
#line 4175 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 278:
#line 959 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), exprBinary(BIT_RSHIFT));
	}
#line 4183 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 279:
#line 962 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), exprBinary(AND));
	}
#line 4191 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 280:
#line 965 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), exprBinary(OR));
	}
#line 4199 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 281:
#line 968 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-4]), (yylsp[0]), exprInlineIf());
	}
#line 4207 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 282:
#line 971 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), exprDot((yyvsp[0].string)));
	}
#line 4215 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 283:
#line 974 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-1]), (yylsp[0]), exprUnary(RATE));
        }
#line 4223 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 284:
#line 977 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[0]), (yylsp[0]), exprDeadlock());
	}
#line 4231 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 285:
#line 980 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-1]), (yylsp[-1]), exprUnary(NOT));
	}
#line 4239 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 286:
#line 982 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-1]), (yylsp[-1]), exprBinary(OR));
	}
#line 4247 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 287:
#line 985 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), exprBinary(AND));
        }
#line 4255 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 288:
#line 988 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), exprBinary(OR));
        }
#line 4263 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 289:
#line 991 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-1]), (yylsp[0]), exprUnary(NOT));
        }
#line 4271 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 290:
#line 994 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-2]), (yylsp[0]), exprBinary(MIN));
        }
#line 4279 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 291:
#line 997 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-2]), (yylsp[0]), exprBinary(MAX));
        }
#line 4287 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 292:
#line 1000 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-5]), (yylsp[0]), exprForAllBegin((yyvsp[-3].string)));
        }
#line 4295 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 293:
#line 1002 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-7]), (yylsp[0]), exprForAllEnd((yyvsp[-5].string)));
        }
#line 4303 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 294:
#line 1005 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-5]), (yylsp[0]), exprExistsBegin((yyvsp[-3].string)));
        }
#line 4311 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 295:
#line 1007 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-7]), (yylsp[0]), exprExistsEnd((yyvsp[-5].string)));
        }
#line 4319 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 297:
#line 1014 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), exprAssignment((yyvsp[-1].kind)));
	}
#line 4327 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 298:
#line 1020 "parser.yy" /* yacc.c:1652  */
    { (yyval.kind) = ASSIGN; }
#line 4333 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 299:
#line 1021 "parser.yy" /* yacc.c:1652  */
    { (yyval.kind) = ASSPLUS; }
#line 4339 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 300:
#line 1022 "parser.yy" /* yacc.c:1652  */
    { (yyval.kind) = ASSMINUS; }
#line 4345 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 301:
#line 1023 "parser.yy" /* yacc.c:1652  */
    { (yyval.kind) = ASSDIV; }
#line 4351 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 302:
#line 1024 "parser.yy" /* yacc.c:1652  */
    { (yyval.kind) = ASSMOD; }
#line 4357 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 303:
#line 1025 "parser.yy" /* yacc.c:1652  */
    { (yyval.kind) = ASSMULT; }
#line 4363 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 304:
#line 1026 "parser.yy" /* yacc.c:1652  */
    { (yyval.kind) = ASSAND; }
#line 4369 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 305:
#line 1027 "parser.yy" /* yacc.c:1652  */
    { (yyval.kind) = ASSOR; }
#line 4375 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 306:
#line 1028 "parser.yy" /* yacc.c:1652  */
    { (yyval.kind) = ASSXOR; }
#line 4381 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 307:
#line 1029 "parser.yy" /* yacc.c:1652  */
    { (yyval.kind) = ASSLSHIFT; }
#line 4387 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 308:
#line 1030 "parser.yy" /* yacc.c:1652  */
    { (yyval.kind) = ASSRSHIFT; }
#line 4393 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 309:
#line 1035 "parser.yy" /* yacc.c:1652  */
    { (yyval.kind) = MINUS; }
#line 4399 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 310:
#line 1036 "parser.yy" /* yacc.c:1652  */
    { (yyval.kind) = PLUS; }
#line 4405 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 311:
#line 1037 "parser.yy" /* yacc.c:1652  */
    { (yyval.kind) = NOT; }
#line 4411 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 312:
#line 1042 "parser.yy" /* yacc.c:1652  */
    { (yyval.number)=0; }
#line 4417 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 313:
#line 1043 "parser.yy" /* yacc.c:1652  */
    {
	    (yyval.number) = 1;
	}
#line 4425 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 314:
#line 1046 "parser.yy" /* yacc.c:1652  */
    {
	    (yyval.number) = (yyvsp[-2].number) + 1;
	}
#line 4433 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 320:
#line 1067 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[0]), (yylsp[0]), typeInt(ParserBuilder::PREFIX_CONST));
	}
#line 4441 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 321:
#line 1069 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-3]), (yylsp[-1]), typePop());
	}
#line 4449 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 325:
#line 1080 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[0]), (yylsp[0]), typeDuplicate());
	}
#line 4457 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 326:
#line 1082 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-3]), (yylsp[0]), declVar((yyvsp[-3].string), true));
	}
#line 4465 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 327:
#line 1091 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-3]), (yylsp[0]), procBegin((yyvsp[-2].string)));
	}
#line 4473 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 328:
#line 1094 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[-1]), procEnd());
	}
#line 4481 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 329:
#line 1097 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-4]), (yylsp[0]), procBegin((yyvsp[-3].string)));
	}
#line 4489 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 330:
#line 1100 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[-1]), procEnd());
	}
#line 4497 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 331:
#line 1103 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-3]), (yylsp[0]), procBegin((yyvsp[-2].string)));
	}
#line 4505 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 332:
#line 1106 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[-1]), procEnd());
	}
#line 4513 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 333:
#line 1109 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), procBegin("_"));
	}
#line 4521 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 334:
#line 1112 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[-1]), procEnd());
	}
#line 4529 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 335:
#line 1115 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), procBegin((yyvsp[-1].string)));
	}
#line 4537 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 336:
#line 1118 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[-1]), procEnd());
	}
#line 4545 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 340:
#line 1130 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[0]), (yylsp[0]), typePop());
	}
#line 4553 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 342:
#line 1134 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), typePop());
	}
#line 4561 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 344:
#line 1141 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[0]), (yylsp[0]), typeDuplicate());
	}
#line 4569 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 345:
#line 1143 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-3]), (yylsp[0]), declParameter((yyvsp[-1].string), true));
	}
#line 4577 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 346:
#line 1146 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[0]), (yylsp[0]), typeDuplicate());
	}
#line 4585 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 347:
#line 1148 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-4]), (yylsp[0]), declParameter((yyvsp[-1].string), true));
	}
#line 4593 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 348:
#line 1154 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[0]), (yylsp[0]), typeInt(ParserBuilder::PREFIX_CONST));
	}
#line 4601 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 349:
#line 1156 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-1]), (yylsp[0]), declParameter((yyvsp[-1].string), false));
	}
#line 4609 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 350:
#line 1159 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-1]), (yylsp[-1]), typeInt(ParserBuilder::PREFIX_CONST));
	}
#line 4617 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 351:
#line 1161 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-1]), (yylsp[0]), declParameter((yyvsp[-1].string), false));
	}
#line 4625 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 359:
#line 1186 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[0]), (yylsp[0]), exprTrue(); ch->procState((yyvsp[0].string), false));
	}
#line 4633 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 360:
#line 1189 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-3]), (yylsp[0]), procState((yyvsp[-3].string), true));
	}
#line 4641 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 362:
#line 1196 "parser.yy" /* yacc.c:1652  */
    {
	}
#line 4648 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 363:
#line 1198 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), exprBinary(AND));
	}
#line 4656 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 369:
#line 1215 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-3]), (yylsp[-1]), procEdgeBegin((yyvsp[-3].string), (yyvsp[-1].string), true));
	}
#line 4664 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 370:
#line 1217 "parser.yy" /* yacc.c:1652  */
    {
	    strcpy(rootTransId, (yyvsp[-8].string));
	    CALL((yylsp[-8]), (yylsp[-1]), procEdgeEnd((yyvsp[-8].string), (yyvsp[-6].string)));
	}
#line 4673 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 371:
#line 1225 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-2]), (yylsp[-1]), procEdgeBegin(rootTransId, (yyvsp[-1].string), true));
	}
#line 4681 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 372:
#line 1227 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-7]), (yylsp[-1]), procEdgeEnd(rootTransId, (yyvsp[-6].string)));
	}
#line 4689 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 375:
#line 1235 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-1]), (yylsp[-1]), procGuard());
	}
#line 4697 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 376:
#line 1238 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[-1]), procGuard());
	}
#line 4705 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 378:
#line 1245 "parser.yy" /* yacc.c:1652  */
    {
	  CALL((yylsp[-2]), (yylsp[0]), exprBinary(AND));
	}
#line 4713 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 383:
#line 1259 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-1]), (yylsp[0]), property((yyvsp[-1].kind)));
	}
#line 4721 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 384:
#line 1262 "parser.yy" /* yacc.c:1652  */
    {
	    CALL((yylsp[-2]), (yylsp[0]), property(LEADSTO));
	}
#line 4729 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 385:
#line 1267 "parser.yy" /* yacc.c:1652  */
    { (yyval.kind) = EF; }
#line 4735 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 386:
#line 1268 "parser.yy" /* yacc.c:1652  */
    { (yyval.kind) = EG; }
#line 4741 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 387:
#line 1269 "parser.yy" /* yacc.c:1652  */
    { (yyval.kind) = AF; }
#line 4747 "parser.tab.c" /* yacc.c:1652  */
    break;

  case 388:
#line 1270 "parser.yy" /* yacc.c:1652  */
    { (yyval.kind) = AG; }
#line 4753 "parser.tab.c" /* yacc.c:1652  */
    break;


#line 4757 "parser.tab.c" /* yacc.c:1652  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1272 "parser.yy" /* yacc.c:1918  */


#include "lexer.cc"

static void utap_error(const char* msg)
{
    ch->setPosition(yylloc.start, yylloc.end);
    ch->handleError(msg);
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
			bool newxta, xta_part_t part, std::string xpath)
{
    // Select syntax
    syntax = (syntax_t)((newxta ? SYNTAX_NEW : SYNTAX_OLD) | SYNTAX_GUIDING);
    setStartToken(part, newxta);

    // Set parser builder
    ch = aParserBuilder;

    // Reset position tracking
    PositionTracker::setPath(ch, xpath);

    // Parse string
    int res = 0;

    if (utap_parse())
    {
	res = -1;
    }

    ch = NULL;
    return res;
}

static int32_t parseProperty(ParserBuilder *aParserBuilder)
{
    // Select syntax
    syntax = SYNTAX_PROPERTY;
    setStartToken(S_PROPERTY, false);

    // Set parser builder
    ch = aParserBuilder;

    // Reset position tracking
    PositionTracker::setPath(ch, "");

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

int32_t parseXTA(const char *str, ParserBuilder *builder, bool newxta)
{
    return parseXTA(str, builder, newxta, S_XTA, "");
}

int32_t parseXTA(FILE *file, ParserBuilder *builder, bool newxta)
{
    utap__switch_to_buffer(utap__create_buffer(file, YY_BUF_SIZE));
    int res = parseXTA(builder, newxta, S_XTA, "");
    utap__delete_buffer(YY_CURRENT_BUFFER);
    return res;
}

int32_t parseProperty(const char *str, ParserBuilder *aParserBuilder)
{
    utap__scan_string(str);
    int32_t res = parseProperty(aParserBuilder);
    utap__delete_buffer(YY_CURRENT_BUFFER);
    return res;
}

int32_t parseProperty(FILE *file, ParserBuilder *aParserBuilder)
{
    utap__switch_to_buffer(utap__create_buffer(file, YY_BUF_SIZE));
    int32_t res = parseProperty(aParserBuilder);
    utap__delete_buffer(YY_CURRENT_BUFFER);
    return res;
}
