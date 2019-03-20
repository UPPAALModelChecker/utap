/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

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

/* Copy the first part of user declarations.  */
#line 40 "parser.yy" /* yacc.c:339  */


 #include "libparser.h"
 #include "utap/position.h"
 #include <string.h>

 using namespace std;
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
	 int len = strlen(msg);
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


#line 201 "parser.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
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
    T_MOD = 276,
    T_OR = 277,
    T_XOR = 278,
    T_LSHIFT = 279,
    T_RSHIFT = 280,
    T_BOOL_AND = 281,
    T_BOOL_OR = 282,
    T_KW_AND = 283,
    T_KW_OR = 284,
    T_KW_XOR = 285,
    T_KW_IMPLY = 286,
    T_KW_NOT = 287,
    T_SUP = 288,
    T_INF = 289,
    T_COS = 290,
    T_SIN = 291,
    T_EXP = 292,
    T_LOG = 293,
    T_SQRT = 294,
    T_RANDOM = 295,
    T_LN = 296,
    T_FABS = 297,
    T_POW = 298,
    T_CEIL = 299,
    T_FLOOR = 300,
    T_FORALL = 301,
    T_EXISTS = 302,
    T_FOREACH = 303,
    T_SUM = 304,
    T_LT = 305,
    T_LEQ = 306,
    T_EQ = 307,
    T_NEQ = 308,
    T_GEQ = 309,
    T_GT = 310,
    T_FOR = 311,
    T_WHILE = 312,
    T_DO = 313,
    T_BREAK = 314,
    T_CONTINUE = 315,
    T_SWITCH = 316,
    T_IF = 317,
    T_ELSE = 318,
    T_CASE = 319,
    T_DEFAULT = 320,
    T_RETURN = 321,
    T_ASSERT = 322,
    T_PRIORITY = 323,
    T_TYPEDEF = 324,
    T_STRUCT = 325,
    T_CONST = 326,
    T_OLDCONST = 327,
    T_URGENT = 328,
    T_BROADCAST = 329,
    T_TRUE = 330,
    T_FALSE = 331,
    T_META = 332,
    T_SYSTEM = 333,
    T_PROCESS = 334,
    T_STATE = 335,
    T_BRANCH = 336,
    T_COMMIT = 337,
    T_INIT = 338,
    T_TRANS = 339,
    T_SELECT = 340,
    T_GUARD = 341,
    T_SYNC = 342,
    T_ASSIGN = 343,
    T_BEFORE = 344,
    T_AFTER = 345,
    T_PROGRESS = 346,
    T_ARROW = 347,
    T_UNCONTROL_ARROW = 348,
    T_IO = 349,
    T_DEADLOCK = 350,
    T_EF = 351,
    T_EG = 352,
    T_AF = 353,
    T_AG = 354,
    T_LEADSTO = 355,
    T_RESULTSET = 356,
    T_EF_PLUS = 357,
    T_AG_PLUS = 358,
    T_EF_MULT = 359,
    T_AG_MULT = 360,
    T_SCENARIO = 361,
    T_CONTROL = 362,
    T_CONTROL_T = 363,
    T_SIMULATION = 364,
    T_SIMULATE = 365,
    T_CONSISTENCY = 366,
    T_SPECIFICATION = 367,
    T_IMPLEMENTATION = 368,
    T_REFINEMENT = 369,
    T_GANTT = 370,
    T_PMAX = 371,
    T_PROBA = 372,
    T_DIAMOND = 373,
    T_BOX = 374,
    T_HASH = 375,
    T_ERROR = 376,
    T_ID = 377,
    T_TYPENAME = 378,
    T_NAT = 379,
    T_FLOATING = 380,
    T_POS_NEG_MAX = 381,
    T_BOOL = 382,
    T_INT = 383,
    T_CHAN = 384,
    T_CLOCK = 385,
    T_VOID = 386,
    T_SCALAR = 387,
    T_DOUBLE = 388,
    T_NEW = 389,
    T_NEW_DECLARATION = 390,
    T_NEW_LOCAL_DECL = 391,
    T_NEW_INST = 392,
    T_NEW_SYSTEM = 393,
    T_NEW_PARAMETERS = 394,
    T_NEW_INVARIANT = 395,
    T_NEW_GUARD = 396,
    T_NEW_SYNC = 397,
    T_NEW_ASSIGN = 398,
    T_NEW_SELECT = 399,
    T_EXPONENTIALRATE = 400,
    T_OLD = 401,
    T_OLD_DECLARATION = 402,
    T_OLD_LOCAL_DECL = 403,
    T_OLD_INST = 404,
    T_OLD_PARAMETERS = 405,
    T_OLD_INVARIANT = 406,
    T_OLD_GUARD = 407,
    T_OLD_ASSIGN = 408,
    T_PROPERTY = 409,
    T_EXPRESSION = 410,
    T_EXPRESSION_LIST = 411,
    T_XTA_PROCESS = 412,
    T_PROBABILITY = 413,
    T_INSTANCELINE = 414,
    T_MESSAGE = 415,
    T_UPDATE = 416,
    T_CONDITION = 417,
    T_MITL_AND = 418,
    T_MITL_OR = 419,
    T_MITL_NEXT = 420,
    T_DYNAMIC = 421,
    T_HYBRID = 422,
    T_SPAWN = 423,
    T_EXIT = 424,
    T_NUMOF = 425,
    T_MIN = 426,
    T_MAX = 427,
    UOPERATOR = 428
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
#define T_MOD 276
#define T_OR 277
#define T_XOR 278
#define T_LSHIFT 279
#define T_RSHIFT 280
#define T_BOOL_AND 281
#define T_BOOL_OR 282
#define T_KW_AND 283
#define T_KW_OR 284
#define T_KW_XOR 285
#define T_KW_IMPLY 286
#define T_KW_NOT 287
#define T_SUP 288
#define T_INF 289
#define T_COS 290
#define T_SIN 291
#define T_EXP 292
#define T_LOG 293
#define T_SQRT 294
#define T_RANDOM 295
#define T_LN 296
#define T_FABS 297
#define T_POW 298
#define T_CEIL 299
#define T_FLOOR 300
#define T_FORALL 301
#define T_EXISTS 302
#define T_FOREACH 303
#define T_SUM 304
#define T_LT 305
#define T_LEQ 306
#define T_EQ 307
#define T_NEQ 308
#define T_GEQ 309
#define T_GT 310
#define T_FOR 311
#define T_WHILE 312
#define T_DO 313
#define T_BREAK 314
#define T_CONTINUE 315
#define T_SWITCH 316
#define T_IF 317
#define T_ELSE 318
#define T_CASE 319
#define T_DEFAULT 320
#define T_RETURN 321
#define T_ASSERT 322
#define T_PRIORITY 323
#define T_TYPEDEF 324
#define T_STRUCT 325
#define T_CONST 326
#define T_OLDCONST 327
#define T_URGENT 328
#define T_BROADCAST 329
#define T_TRUE 330
#define T_FALSE 331
#define T_META 332
#define T_SYSTEM 333
#define T_PROCESS 334
#define T_STATE 335
#define T_BRANCH 336
#define T_COMMIT 337
#define T_INIT 338
#define T_TRANS 339
#define T_SELECT 340
#define T_GUARD 341
#define T_SYNC 342
#define T_ASSIGN 343
#define T_BEFORE 344
#define T_AFTER 345
#define T_PROGRESS 346
#define T_ARROW 347
#define T_UNCONTROL_ARROW 348
#define T_IO 349
#define T_DEADLOCK 350
#define T_EF 351
#define T_EG 352
#define T_AF 353
#define T_AG 354
#define T_LEADSTO 355
#define T_RESULTSET 356
#define T_EF_PLUS 357
#define T_AG_PLUS 358
#define T_EF_MULT 359
#define T_AG_MULT 360
#define T_SCENARIO 361
#define T_CONTROL 362
#define T_CONTROL_T 363
#define T_SIMULATION 364
#define T_SIMULATE 365
#define T_CONSISTENCY 366
#define T_SPECIFICATION 367
#define T_IMPLEMENTATION 368
#define T_REFINEMENT 369
#define T_GANTT 370
#define T_PMAX 371
#define T_PROBA 372
#define T_DIAMOND 373
#define T_BOX 374
#define T_HASH 375
#define T_ERROR 376
#define T_ID 377
#define T_TYPENAME 378
#define T_NAT 379
#define T_FLOATING 380
#define T_POS_NEG_MAX 381
#define T_BOOL 382
#define T_INT 383
#define T_CHAN 384
#define T_CLOCK 385
#define T_VOID 386
#define T_SCALAR 387
#define T_DOUBLE 388
#define T_NEW 389
#define T_NEW_DECLARATION 390
#define T_NEW_LOCAL_DECL 391
#define T_NEW_INST 392
#define T_NEW_SYSTEM 393
#define T_NEW_PARAMETERS 394
#define T_NEW_INVARIANT 395
#define T_NEW_GUARD 396
#define T_NEW_SYNC 397
#define T_NEW_ASSIGN 398
#define T_NEW_SELECT 399
#define T_EXPONENTIALRATE 400
#define T_OLD 401
#define T_OLD_DECLARATION 402
#define T_OLD_LOCAL_DECL 403
#define T_OLD_INST 404
#define T_OLD_PARAMETERS 405
#define T_OLD_INVARIANT 406
#define T_OLD_GUARD 407
#define T_OLD_ASSIGN 408
#define T_PROPERTY 409
#define T_EXPRESSION 410
#define T_EXPRESSION_LIST 411
#define T_XTA_PROCESS 412
#define T_PROBABILITY 413
#define T_INSTANCELINE 414
#define T_MESSAGE 415
#define T_UPDATE 416
#define T_CONDITION 417
#define T_MITL_AND 418
#define T_MITL_OR 419
#define T_MITL_NEXT 420
#define T_DYNAMIC 421
#define T_HYBRID 422
#define T_SPAWN 423
#define T_EXIT 424
#define T_NUMOF 425
#define T_MIN 426
#define T_MAX 427
#define UOPERATOR 428

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 290 "parser.yy" /* yacc.c:355  */

    bool flag;
    int number;
    ParserBuilder::PREFIX prefix;
    kind_t kind;
    char string[MAXLEN];
    double floating;

#line 593 "parser.tab.c" /* yacc.c:355  */
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



/* Copy the second part of user declarations.  */

#line 624 "parser.tab.c" /* yacc.c:358  */

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
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
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
#  define YYSIZE_T unsigned int
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

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
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
#define YYFINAL  148
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   9202

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  195
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  203
/* YYNRULES -- Number of rules.  */
#define YYNRULES  564
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1197

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   428

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     193,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   178,   187,
     182,   183,     2,     2,   189,     2,   186,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   177,   188,
       2,     2,     2,   176,     2,   171,     2,     2,     2,   192,
       2,     2,     2,     2,     2,     2,     2,   172,     2,     2,
       2,     2,   175,     2,     2,   173,     2,   174,     2,     2,
       2,   184,   194,   185,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   190,     2,   191,     2,     2,     2,     2,
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
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   179,   180,   181
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   306,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   327,   328,   329,   330,   332,   333,   334,
     335,   339,   342,   344,   345,   349,   349,   356,   359,   359,
     366,   367,   371,   376,   379,   380,   384,   385,   386,   391,
     392,   396,   397,   401,   402,   405,   407,   412,   413,   420,
     423,   426,   429,   432,   438,   439,   440,   444,   446,   448,
     450,   452,   455,   459,   461,   464,   466,   466,   471,   473,
     477,   480,   486,   487,   491,   495,   495,   500,   503,   508,
     510,   511,   512,   513,   514,   515,   516,   517,   518,   519,
     523,   523,   525,   527,   538,   538,   544,   544,   547,   548,
     549,   553,   554,   558,   561,   567,   573,   574,   578,   578,
     586,   587,   591,   592,   598,   599,   603,   606,   612,   612,
     614,   616,   617,   617,   618,   622,   625,   629,   630,   634,
     634,   642,   645,   648,   651,   654,   657,   660,   663,   666,
     669,   672,   675,   678,   682,   685,   688,   691,   694,   697,
     700,   704,   710,   711,   715,   716,   717,   718,   719,   720,
     721,   722,   723,   724,   725,   726,   727,   728,   732,   733,
     737,   744,   745,   749,   749,   757,   758,   759,   760,   761,
     769,   769,   778,   779,   779,   782,   784,   785,   786,   790,
     791,   795,   796,   800,   803,   806,   809,   815,   819,   820,
     824,   829,   832,   835,   837,   838,   842,   843,   847,   847,
     853,   853,   859,   859,   868,   868,   873,   873,   878,   881,
     883,   887,   890,   895,   897,   900,   903,   906,   908,   909,
     913,   916,   919,   922,   925,   931,   934,   939,   941,   944,
     947,   949,   950,   954,   955,   959,   960,   964,   967,   973,
     976,   982,   983,   992,   992,  1000,  1002,  1003,  1006,  1008,
    1009,  1013,  1014,  1017,  1020,  1020,  1026,  1026,  1032,  1033,
    1033,  1039,  1040,  1040,  1046,  1046,  1050,  1053,  1056,  1056,
    1062,  1065,  1068,  1074,  1077,  1077,  1086,  1087,  1091,  1091,
    1097,  1097,  1103,  1103,  1109,  1109,  1118,  1119,  1124,  1127,
    1130,  1133,  1136,  1139,  1142,  1145,  1145,  1150,  1150,  1155,
    1158,  1161,  1162,  1165,  1168,  1171,  1174,  1177,  1180,  1183,
    1186,  1189,  1192,  1195,  1198,  1201,  1204,  1207,  1210,  1213,
    1216,  1219,  1222,  1225,  1228,  1231,  1234,  1237,  1240,  1243,
    1246,  1249,  1249,  1254,  1257,  1260,  1263,  1266,  1269,  1269,
    1274,  1274,  1279,  1279,  1284,  1285,  1286,  1290,  1290,  1292,
    1294,  1294,  1296,  1296,  1298,  1298,  1300,  1300,  1302,  1302,
    1308,  1314,  1315,  1316,  1317,  1318,  1319,  1320,  1321,  1322,
    1323,  1324,  1329,  1330,  1331,  1332,  1336,  1337,  1338,  1339,
    1340,  1341,  1342,  1343,  1344,  1345,  1349,  1354,  1355,  1358,
    1368,  1371,  1373,  1374,  1378,  1379,  1379,  1384,  1387,  1388,
    1392,  1392,  1403,  1403,  1409,  1409,  1415,  1415,  1421,  1421,
    1427,  1427,  1436,  1437,  1438,  1442,  1445,  1446,  1449,  1453,
    1453,  1458,  1458,  1466,  1466,  1471,  1471,  1479,  1482,  1484,
    1488,  1489,  1493,  1494,  1498,  1501,  1507,  1508,  1510,  1515,
    1517,  1518,  1522,  1523,  1527,  1527,  1537,  1537,  1542,  1545,
    1547,  1550,  1556,  1557,  1563,  1565,  1567,  1570,  1570,  1573,
    1576,  1581,  1584,  1587,  1590,  1593,  1596,  1602,  1605,  1609,
    1613,  1618,  1622,  1626,  1630,  1634,  1638,  1642,  1646,  1650,
    1654,  1658,  1662,  1665,  1669,  1673,  1679,  1683,  1687,  1691,
    1696,  1700,  1705,  1710,  1714,  1726,  1729,  1739,  1743,  1746,
    1754,  1755,  1756,  1760,  1761,  1765,  1766,  1770,  1775,  1778,
    1781,  1784,  1787,  1793,  1799,  1805,  1811,  1817,  1823,  1824,
    1828,  1829,  1833,  1834,  1838,  1842,  1847,  1851,  1858,  1862,
    1867,  1871,  1877,  1886,  1887,  1891,  1892,  1896,  1899,  1903,
    1906,  1909,  1911,  1912,  1917
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
  "T_DECREMENT", "T_PLUS", "T_MINUS", "T_MULT", "T_DIV", "T_MOD", "T_OR",
  "T_XOR", "T_LSHIFT", "T_RSHIFT", "T_BOOL_AND", "T_BOOL_OR", "T_KW_AND",
  "T_KW_OR", "T_KW_XOR", "T_KW_IMPLY", "T_KW_NOT", "T_SUP", "T_INF",
  "T_COS", "T_SIN", "T_EXP", "T_LOG", "T_SQRT", "T_RANDOM", "T_LN",
  "T_FABS", "T_POW", "T_CEIL", "T_FLOOR", "T_FORALL", "T_EXISTS",
  "T_FOREACH", "T_SUM", "T_LT", "T_LEQ", "T_EQ", "T_NEQ", "T_GEQ", "T_GT",
  "T_FOR", "T_WHILE", "T_DO", "T_BREAK", "T_CONTINUE", "T_SWITCH", "T_IF",
  "T_ELSE", "T_CASE", "T_DEFAULT", "T_RETURN", "T_ASSERT", "T_PRIORITY",
  "T_TYPEDEF", "T_STRUCT", "T_CONST", "T_OLDCONST", "T_URGENT",
  "T_BROADCAST", "T_TRUE", "T_FALSE", "T_META", "T_SYSTEM", "T_PROCESS",
  "T_STATE", "T_BRANCH", "T_COMMIT", "T_INIT", "T_TRANS", "T_SELECT",
  "T_GUARD", "T_SYNC", "T_ASSIGN", "T_BEFORE", "T_AFTER", "T_PROGRESS",
  "T_ARROW", "T_UNCONTROL_ARROW", "T_IO", "T_DEADLOCK", "T_EF", "T_EG",
  "T_AF", "T_AG", "T_LEADSTO", "T_RESULTSET", "T_EF_PLUS", "T_AG_PLUS",
  "T_EF_MULT", "T_AG_MULT", "T_SCENARIO", "T_CONTROL", "T_CONTROL_T",
  "T_SIMULATION", "T_SIMULATE", "T_CONSISTENCY", "T_SPECIFICATION",
  "T_IMPLEMENTATION", "T_REFINEMENT", "T_GANTT", "T_PMAX", "T_PROBA",
  "T_DIAMOND", "T_BOX", "T_HASH", "T_ERROR", "T_ID", "T_TYPENAME", "T_NAT",
  "T_FLOATING", "T_POS_NEG_MAX", "T_BOOL", "T_INT", "T_CHAN", "T_CLOCK",
  "T_VOID", "T_SCALAR", "T_DOUBLE", "T_NEW", "T_NEW_DECLARATION",
  "T_NEW_LOCAL_DECL", "T_NEW_INST", "T_NEW_SYSTEM", "T_NEW_PARAMETERS",
  "T_NEW_INVARIANT", "T_NEW_GUARD", "T_NEW_SYNC", "T_NEW_ASSIGN",
  "T_NEW_SELECT", "T_EXPONENTIALRATE", "T_OLD", "T_OLD_DECLARATION",
  "T_OLD_LOCAL_DECL", "T_OLD_INST", "T_OLD_PARAMETERS", "T_OLD_INVARIANT",
  "T_OLD_GUARD", "T_OLD_ASSIGN", "T_PROPERTY", "T_EXPRESSION",
  "T_EXPRESSION_LIST", "T_XTA_PROCESS", "T_PROBABILITY", "T_INSTANCELINE",
  "T_MESSAGE", "T_UPDATE", "T_CONDITION", "T_MITL_AND", "T_MITL_OR",
  "T_MITL_NEXT", "T_DYNAMIC", "T_HYBRID", "T_SPAWN", "T_EXIT", "T_NUMOF",
  "'A'", "'M'", "'U'", "'W'", "'R'", "'?'", "':'", "'&'", "T_MIN", "T_MAX",
  "UOPERATOR", "'('", "')'", "'['", "']'", "'.'", "'\\''", "';'", "','",
  "'{'", "'}'", "'E'", "'\\n'", "'\\\\'", "$accept", "Uppaal", "XTA",
  "Instantiations", "Instantiation", "$@1", "InstanceLineExpression",
  "$@2", "OptionalInstanceParameterList", "System", "PriorityDecl",
  "ChannelList", "ChanElement", "ChanExpression", "SysDecl", "IODecl",
  "SyncExprList", "IOSyncExpr", "ProcessList", "ProcLessThan", "Progress",
  "ProgressMeasureList", "GanttDecl", "GanttDef", "$@3", "GanttArgs",
  "GanttDeclSelect", "GanttExprList", "GanttExpr", "$@4",
  "GanttEntrySelect", "Declarations", "DynamicDeclaration", "$@5",
  "BeforeUpdateDecl", "AfterUpdateDecl", "FunctionDecl", "$@6", "EndBlock",
  "OptionalParameterList", "ParameterList", "Parameter", "VariableDecl",
  "DeclIdList", "DeclId", "$@7", "VarInit", "Initializer", "FieldInitList",
  "FieldInit", "ArrayDecl", "$@8", "ArrayDecl2", "$@9", "TypeDecl",
  "TypeIdList", "TypeId", "$@10", "Type", "Id", "NonTypeId",
  "FieldDeclList", "FieldDecl", "FieldDeclIdList", "FieldDeclId", "$@11",
  "TypePrefix", "ProcDecl", "$@12", "ProcBody", "ProcLocalDeclList",
  "States", "StateDeclList", "StateDecl", "Branches", "BranchDeclList",
  "BranchDecl", "Init", "Transitions", "TransitionList", "Transition",
  "$@13", "$@14", "$@15", "TransitionOpt", "$@16", "$@17", "Select",
  "SelectList", "Guard", "Sync", "SyncExpr", "MessExpr", "Assign",
  "LocFlags", "Commit", "Urgent", "CStateList", "UStateList", "ExpRate",
  "Block", "$@18", "BlockLocalDeclList", "StatementList", "Statement",
  "$@19", "$@20", "$@21", "$@22", "$@23", "$@24", "ElsePart", "$@25",
  "SwitchCaseList", "SwitchCase", "$@26", "$@27", "$@28", "$@29",
  "ExprList", "Expression", "$@30", "$@31", "$@32", "$@33", "$@34", "$@35",
  "DynamicExpression", "$@36", "$@37", "$@38", "$@39", "$@40", "$@41",
  "Assignment", "AssignOp", "UnaryOp", "BuiltinFunction1",
  "BuiltinFunction2", "ArgList", "OldXTA", "OldDeclaration", "OldVarDecl",
  "$@42", "OldConstDeclIdList", "OldConstDeclId", "$@43", "OldProcDecl",
  "$@44", "$@45", "$@46", "$@47", "$@48", "OldProcParams",
  "OldProcParamList", "OldProcParam", "$@49", "$@50", "OldProcConstParam",
  "$@51", "$@52", "OldProcBody", "OldVarDeclList", "OldStates",
  "OldStateDeclList", "OldStateDecl", "OldInvariant", "OldTransitions",
  "OldTransitionList", "OldTransition", "$@53", "OldTransitionOpt", "$@54",
  "OldGuard", "OldGuardList", "PropertyList", "PropertyList2",
  "BoolOrKWAnd", "SubProperty", "PropertyExpr", "MITLExpression",
  "BoundType", "CmpGLE", "PathType", "TIOSystem", "IdExpr",
  "TIOStructComposition", "TIOComposition", "TIOConjunction",
  "TIOQuotient", "TIOStructCompositionList", "TIOCompositionList",
  "TIOConjunctionList", "TIOOptionalProperty", "RestrictionList",
  "SysComposition", "DeclComposition", "BracketExprList", "ExpressionList",
  "NonEmptyExpressionList", "SupPrefix", "InfPrefix", "Property", YY_NULLPTR
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
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,    65,    77,    85,    87,    82,    63,    58,    38,   426,
     427,   428,    40,    41,    91,    93,    46,    39,    59,    44,
     123,   125,    69,    10,    92
};
# endif

#define YYPACT_NINF -1073

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-1073)))

#define YYTABLE_NINF -523

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    2222,  1228,  1157, -1073,  1157,  1228,  3264,  8551,  8551,  8551,
    8551,  1406,  8551, -1073, -1073, -1073,    30,  3065,  8551,  8551,
    8551, -1073,  8551,  8551,   -35,  8551,  9010,  8551,  8551,  8551,
      80,   -52, -1073,  8780,  8896,  2885,  8896, -1073,   -42, -1073,
      82, -1073, -1073, -1073, -1073,   -11, -1073, -1073, -1073,     1,
   -1073,    31,   -24, -1073,  7225,   -25, -1073,  8551,  8551, -1073,
      72, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073, -1073, -1073,    69,    78,   105,   144, -1073,
   -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,
    9010,   155,   181, -1073, -1073, -1073, -1073, -1073,  2817, -1073,
   -1073,  7093, -1073, -1073,  8551,   185,   195, -1073,  7093, -1073,
    3764,    91,  7093, -1073,   135, -1073,   133, -1073,  4981, -1073,
     456,  1435,  3166,   199,  9010, -1073, -1073,   208,   229,   233,
    1446,   238,  7093,   240,    91, -1073,  7267,  7093,    91,  1406,
   -1073,  7093, -1073,   253, -1073,  4070,    91,  7093, -1073, -1073,
    1733,   660,   265,   266,   386,  9010, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073, -1073, -1073, -1073,  1406,   277, -1073, -1073,
   -1073, -1073,  1932, -1073,  8551,  8551, -1073,  3264,  9010, -1073,
     270, -1073, -1073,   280, -1073,   281, -1073,    66,    66, -1073,
    1406,  1406,  1406,  1406, -1073,   278,  9010,   284,   286,   287,
    8551,  4790, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073, -1073, -1073,  8551,  8551,  8551,  8551,  8551,
    8551,  8551,  8551,  8551,  8551,  8551,  8551,  8551,  8551, -1073,
    8551,  8551,  8551,  8551,  8551,  8551,  8551,  8551,  8551,  8551,
     467,  3032,  9010, -1073,  8551,    66,  8551,  8551,    15, -1073,
    8551,  8551,  3264,  1406,  8551,   729,   429,  7832, -1073,  1406,
   -1073, -1073, -1073, -1073, -1073,  9010,  9010,  3065,   283, -1073,
     285,  8551,  8551,  -105,   -89,  7945,  8551,  8551,  8652,  8551,
    8551,   296,  -108,   458,   298,   354,   303,   304,   305,   306,
    8551,  8046,   300,  8551,   301,  5034, -1073, -1073,   379,  8551,
    8551,   295,   311, -1073, -1073,   307,  1406,   308,    -2, -1073,
    8551,  8551,   605,   311,   -21,    18, -1073,   311,  3570,   488,
     315,  1406,  2746, -1073,  4265,  5120, -1073, -1073, -1073,   316,
    2574,  8551,  8551,   322,   325,   331,   332,   328, -1073,   330,
   -1073,   388,   391,  5173,   333,   334, -1073,   134,   134,    66,
      66,    66,  2149,  2295,   373,   373,  1972,  1705,  1972,  1705,
    1705,  8551,  1636,  1636,   868,   868,  1636,  1636,  5226,  2473,
     159,   159,  8551,   518,   337,  5311, -1073,  7093,  5364,  4352,
   -1073, -1073,  7093, -1073,   346,  7093,   344,  9010,   347,    85,
   -1073, -1073, -1073, -1073,   229,   233,  9010,  9010, -1073,  7093,
    7093, -1073,  8551, -1073,  8551,   367,  7093,  7093,  7093,  2817,
    7093,  7093,  7093,  9010,  7530,  7631,   -66,  8724,   361,  8968,
    8968,  8968,  8968,  7093,  7631,  7093,  8551,  7093,   355,   358,
    7631,  8551,   371,   358,   358, -1073,   930,   359,  8551, -1073,
      67, -1073, -1073, -1073, -1073, -1073,  9010,  9010,   -68,   -54,
     362, -1073,    90, -1073,   369, -1073, -1073,   364,  9010,   443,
   -1073,  1406,   374, -1073, -1073,   -93,  9010, -1073, -1073,   196,
   -1073, -1073, -1073,  8551, -1073, -1073,  1572, -1073,   370,  2961,
    4405,  5417,  8867,  8867,  9010,  8867,  8551, -1073,   377,   382,
   -1073,   438,   439,  1705,  8551,  7093,   -74,   389, -1073, -1073,
   -1073,  8551,  3264, -1073, -1073,   212, -1073, -1073,   383,   309,
   -1073,    45, -1073, -1073, -1073, -1073,  3828,  3881,  7530,  4843,
   -1073,  8551, -1073,  8551,   523,  7146,   390,  7530,  8551,  9010,
   -1073,   -12,  7631,  8968, -1073, -1073, -1073, -1073, -1073,   244,
     392,  4928, -1073,  8551,   394,  7093,  7530,   397, -1073,   -65,
   -1073,   -51, -1073,  1406, -1073, -1073, -1073, -1073, -1073, -1073,
    7417, -1073,  7417,  8551,   402, -1073,   277,   401, -1073, -1073,
   -1073,   589, -1073,   412, -1073, -1073,  1406,  5502,   410,   411,
    5555, -1073, -1073,  8551, -1073,   414, -1073,   415, -1073, -1073,
     416, -1073,   -26, -1073,   481,   483,   419,   420,  7093, -1073,
    8551, -1073,  5608, -1073, -1073, -1073,  9010, -1073, -1073,   427,
   -1073,   -19, -1073,   421, -1073, -1073, -1073,   435,   442, -1073,
    8551,  8551,   517,  7093,  8551,  8551,   447, -1073,  4212, -1073,
       5,  8724,   430,   574,   441,    68,   615,   457,   457,   457,
     457,   616,   608,   610,  8968,  8968,   455,  8551,  8551,  7093,
    8551, -1073, -1073, -1073,   451, -1073, -1073, -1073, -1073, -1073,
    5693, -1073,  8147,   454, -1073, -1073,  8248, -1073, -1073, -1073,
   -1073, -1073,   316, -1073,   316,  5746, -1073,   462, -1073,   463,
     464, -1073,   466, -1073,   465,   468,   527,   528,  7093, -1073,
    8248, -1073,   469,  1638, -1073, -1073, -1073,   471, -1073, -1073,
   -1073, -1073,  8551,  7093,  1359,  7530,   477,  8551,  9010, -1073,
     470,  8551,  8724,   473,  8968,  8968,  7530,  8968,   474,  9010,
     475,   482,   484,   485,  9010,  8968,  8968, -1073, -1073,  7732,
    5799,  5884,  5937,   478,  1706, -1073, -1073,  4458,  9010,  8980,
    2885,  7844, -1073,  7093,  8551, -1073,   316, -1073, -1073,  8551,
     489,  8551,   490,  8551,  8551,  8551,  8551,  8551,   491,   492,
   -1073, -1073,   486,  9010, -1073,   487, -1073, -1073,   493,  5990,
   -1073,  7530,  6075, -1073, -1073,   494, -1073,  8551, -1073, -1073,
   -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073,  6128,  8551, -1073, -1073,   497, -1073,   498,
    9010,   575,  8551, -1073,    70,   143, -1073, -1073, -1073, -1073,
   -1073,  2554, -1073,   162, -1073,   496,   503,   -23, -1073,  7093,
    8551,  7093,  8551, -1073,  7093, -1073,  6181,  6266,  8551,  8551,
   -1073,   476,   215, -1073,   289, -1073,   499, -1073, -1073, -1073,
     504, -1073,   166,  8551,  6319,  1406, -1073,    98,   217, -1073,
    9010, -1073,   289,  4545,    24, -1073, -1073,  9010, -1073,   500,
     501,   505,   506, -1073,   508,   509,   510,   519,  8349,  8551,
   -1073, -1073, -1073, -1073, -1073, -1073,  4598,  7844, -1073,  8248,
     511,  6372,  6457, -1073, -1073,  6510,  6563,  8551, -1073,  9010,
     522,   823,   845,  9010,   591, -1073, -1073, -1073,  7530,   514,
    6648,   263,   529,  8551,  3133, -1073,  9010, -1073,   221, -1073,
     289,   621, -1073, -1073, -1073, -1073,  1406,   534, -1073,  2931,
    3234,  7429, -1073, -1073,  8551, -1073, -1073,  4651,  4737, -1073,
   -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,   167, -1073,
   -1073,   524, -1073,   223,   533, -1073,   225,   535,  1066, -1073,
   -1073,  8753, -1073, -1073,   598,   599,  8551,   540,   537,  3970,
   -1073, -1073,  9010,   621,  1380, -1073,   108,   549,  8450,   546,
     554,   227,   550,  8551,   675,   111,  8551, -1073, -1073,  2885,
   -1073, -1073, -1073,  9010, -1073, -1073,  9010, -1073,   547,   644,
     232, -1073,   561,  7093,   555, -1073,  6701, -1073, -1073, -1073,
   -1073, -1073,   552,     7,   237, -1073, -1073,  1406,  3264, -1073,
     245, -1073,  6754,  7429,  3264,  8551,  7429,   119,   559, -1073,
     120,  2716, -1073, -1073, -1073,  9010, -1073,  9003,  8551,  7631,
   -1073, -1073,  9010,  9010, -1073,  3934,   566, -1073,   563, -1073,
    8450,  8551, -1073,   568,   255, -1073,  7429,  8551,   564,  7429,
     501, -1073,   565,  9010, -1073, -1073,  7093,   572,   569,   570,
    9010,  9010, -1073, -1073,  3264,  1406, -1073,  7093, -1073,  8551,
   -1073,   122,   381,   690, -1073,   571,   576, -1073,   581, -1073,
     577,   578, -1073,   130,   604,  7429,   140,   587,  3335,    20,
      94, -1073, -1073, -1073,   680, -1073,   329,   698,  8551,   698,
   -1073, -1073,  8551,  1406,  3264, -1073, -1073, -1073,   607,  6844,
     609, -1073, -1073, -1073,  7429,  8551,   701,   680,  8551,  1406,
     699,  6897,   699,   698,   698,  6950,   612, -1073,  7429, -1073,
   -1073, -1073, -1073, -1073,    88,  3436,   702,   701,  7040,   261,
    3537,   701, -1073,   701,   699,   699,  8551,  3264, -1073, -1073,
   -1073, -1073,  1906,   611, -1073,   613,   614,  3638,   601,   702,
   -1073, -1073,   617,  4159,   702,   702,   701,   701,  7093, -1073,
    2068,  2230,  2392, -1073, -1073, -1073,   618,   264, -1073,   602,
   -1073,   619, -1073,   620,   623,   702,   702, -1073, -1073, -1073,
   -1073, -1073, -1073,   625,   626, -1073, -1073
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     0,     0,   195,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   411,   411,   448,     0,     0,     0,     0,
       0,   475,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     2,     0,     3,     4,     5,     6,     0,   188,
     185,   186,   189,   141,   147,   151,   155,   157,   159,     0,
     149,     0,     7,   111,     0,     0,   394,     0,     0,   393,
     392,   395,   171,   172,   396,   397,   398,   399,   400,   401,
     402,   403,   406,   404,   405,     0,     0,     0,     0,   309,
     308,   350,   173,   175,   176,   177,   174,   164,   310,   311,
       0,     0,     0,   165,   170,   166,   167,   168,     0,   169,
     314,     8,   364,   366,     0,     0,     0,   365,    10,    11,
       0,    12,   306,   163,     0,   162,     9,    26,   261,    14,
       0,    15,    16,     0,    17,   443,   439,    18,   435,   436,
       0,    19,   472,    20,    21,    22,   561,    23,    24,     0,
      25,    13,    30,    37,    27,     0,    28,    29,     1,    99,
       0,     0,     0,     0,   155,     0,    96,    31,    97,    55,
      98,    94,    95,    90,    91,    92,     0,    40,    93,   196,
     197,   198,     0,   187,     0,     0,   158,     0,     0,   128,
       0,   142,   148,   152,   156,     0,   150,   324,   326,   327,
       0,     0,     0,     0,   367,     0,     0,     0,     0,     0,
       0,     0,   381,   382,   383,   386,   384,   385,   388,   387,
     389,   390,   391,   323,   325,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   351,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     315,     0,     0,   349,     0,   328,     0,     0,     0,   241,
     243,     0,     0,     0,     0,     0,     0,     0,   414,     0,
     412,   413,   449,    34,    33,     0,     0,     0,     0,   445,
       0,     0,     0,   171,   172,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   173,     0,   175,   176,   177,   174,
       0,     0,   165,   553,   169,     0,   487,   562,     0,     0,
       0,   474,     0,    38,   246,     0,     0,     0,     0,    64,
       0,     0,     0,     0,    68,     0,   116,   118,     0,     0,
       0,     0,     0,   178,     0,     0,   112,   128,   114,   130,
       0,     0,     0,     0,     0,     0,     0,     0,   369,     0,
     322,     0,     0,     0,     0,     0,   321,   335,   336,   337,
     338,   339,   341,   342,   343,   344,   345,   346,   353,   354,
     355,     0,   329,   330,   331,   332,   334,   333,     0,   340,
     356,   357,   407,     0,     0,     0,   348,   380,     0,     0,
     242,   244,   307,   231,     0,   262,     0,     0,     0,     0,
     410,   118,   128,   128,   437,   438,     0,     0,   457,   458,
     473,   557,     0,   559,     0,     0,   482,   483,   479,     0,
     481,   489,   488,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   490,     0,   514,     0,   555,     0,   554,
       0,     0,     0,   563,   564,   476,     0,     0,   407,   136,
       0,   137,   139,    54,    67,    53,     0,     0,     0,     0,
       0,    50,     0,    46,    49,    51,   100,     0,     0,    73,
     115,     0,     0,   128,    41,     0,     0,   145,   183,     0,
     181,   143,   179,     0,   160,   113,     0,   129,     0,     0,
       0,     0,     0,     0,     0,     0,   407,   370,     0,     0,
     517,     0,     0,   352,     0,   408,     0,     0,   320,   319,
     312,     0,     0,   417,   420,     0,   418,   428,     0,     0,
     430,     0,   444,   440,   128,   128,     0,     0,     0,     0,
     505,     0,   491,     0,     0,     0,     0,     0,     0,     0,
     548,   546,     0,     0,   533,   502,   527,   503,   504,     0,
       0,     0,   552,     0,     0,   484,     0,     0,   108,     0,
     190,     0,   135,     0,   128,    65,    66,   102,   103,    45,
       0,    44,     0,     0,     0,    70,    40,     0,    43,   117,
     104,   120,    42,     0,   128,   180,     0,     0,     0,     0,
       0,   146,   144,     0,   161,     0,   372,     0,   374,   378,
       0,   376,     0,   371,     0,     0,     0,     0,   347,   316,
       0,   318,     0,   232,   128,   416,     0,   448,   426,     0,
     432,     0,   448,     0,   422,   442,   446,     0,     0,   496,
     478,   477,     0,   520,     0,     0,     0,   495,     0,   550,
       0,     0,     0,     0,     0,   544,   527,   544,   544,   544,
     544,   534,   535,   536,     0,     0,     0,     0,     0,   556,
       0,   497,   110,   109,   195,    39,   138,   140,    48,    47,
       0,   101,     0,     0,    75,   265,     0,   119,    35,   184,
     182,   153,   130,   132,   130,     0,   360,     0,   362,     0,
       0,   358,     0,   368,     0,     0,     0,     0,   409,   313,
       0,   419,     0,     0,   448,   434,   433,     0,   424,   448,
     558,   560,     0,   521,   330,     0,     0,     0,     0,   549,
     546,   553,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   500,   501,     0,
       0,     0,     0,     0,     0,    52,    69,     0,     0,     0,
     268,     0,   121,   122,   407,   134,   130,   131,   154,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     421,   429,     0,     0,   250,     0,   431,   448,     0,     0,
     492,     0,     0,   551,   499,     0,   498,     0,   542,   540,
     545,   537,   528,   538,   529,   530,   531,   532,   539,   541,
     543,   526,   525,     0,     0,   485,   486,     0,   191,     0,
       0,   250,     0,    72,     0,     0,    57,    74,    76,   266,
     267,     0,   127,     0,   124,     0,   314,     0,   133,   361,
       0,   363,     0,   379,   359,   377,     0,     0,     0,     0,
     451,   454,     0,   452,     0,   427,     0,   423,   480,   494,
       0,   547,     0,     0,     0,     0,   200,   203,     0,   201,
       0,   250,     0,     0,     0,    60,    62,     0,    56,    78,
     107,     0,     0,   282,     0,     0,     0,     0,     0,     0,
     272,   263,   106,   105,   271,   269,     0,     0,   123,     0,
       0,     0,     0,   518,   519,     0,     0,     0,   450,     0,
       0,     0,     0,     0,   459,   251,   252,   425,     0,   510,
       0,   507,     0,     0,     0,   199,     0,   210,     0,   208,
       0,   213,    71,    61,    63,    58,     0,     0,   270,     0,
       0,     0,   286,   287,     0,   284,   291,     0,     0,   265,
     273,   125,   126,    36,   373,   375,   515,   516,     0,   453,
     212,     0,   259,     0,     0,   257,     0,     0,     0,   447,
     493,     0,   508,   524,   523,     0,     0,     0,     0,     0,
     202,   207,     0,   213,     0,   192,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   290,   292,   268,
     455,   256,   255,     0,   254,   253,     0,   211,     0,     0,
       0,   462,   310,   511,     0,   506,     0,   205,   206,   204,
     209,   193,     0,     0,     0,   216,    79,     0,     0,    85,
       0,    82,     0,     0,     0,     0,     0,     0,     0,   288,
       0,     0,   260,   258,   461,     0,   460,     0,     0,     0,
     513,   215,     0,     0,   214,     0,     0,    80,     0,    77,
       0,     0,   278,     0,     0,   281,     0,     0,     0,     0,
       0,   264,     0,     0,   468,   463,   512,     0,   222,     0,
       0,     0,   228,   217,     0,     0,    83,    84,   276,     0,
     280,     0,     0,   293,   464,     0,     0,   218,     0,   220,
       0,     0,    81,     0,     0,     0,     0,     0,     0,     0,
       0,   296,   294,   285,   469,   466,     0,   229,     0,   229,
     224,   226,     0,     0,     0,   277,   274,   283,     0,     0,
       0,   302,   289,   297,     0,     0,   237,   469,     0,     0,
     233,     0,   233,   229,   229,     0,     0,    87,     0,   300,
     298,   304,   268,   295,     0,     0,   247,   237,     0,     0,
       0,   237,   223,   237,   233,   233,     0,     0,   275,   268,
     268,   268,     0,     0,   470,     0,     0,     0,     0,   247,
     509,   230,     0,     0,   247,   247,   237,   237,    86,    88,
       0,     0,     0,   471,   239,   238,     0,     0,   465,     0,
     236,     0,   234,     0,     0,   247,   247,   249,   248,   467,
     235,   219,   221,     0,     0,   225,   227
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1073, -1073,   791,   678,   -87, -1073, -1073, -1073,   234,   551,
   -1073, -1073,  -194,  -695, -1073, -1073, -1073,   -48, -1073, -1073,
   -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,  -237, -1073,
   -1073,   372, -1073, -1073, -1073, -1073,   -31, -1073, -1073,  -166,
    -244,   633,   -27, -1073,   351, -1073, -1073,  -630, -1073,   -59,
    -273, -1073,  -613, -1073,   -32, -1073,   267, -1073,    22,  -125,
     951,   495,  -243, -1073,   243, -1073, -1073,   799, -1073, -1073,
     172, -1073, -1073,   -79, -1073, -1073,  -134,  -800,  -133, -1073,
    -206, -1073, -1073, -1073, -1073, -1073, -1073, -1046,  -282, -1039,
    -768,  -296, -1073, -1072,  -739, -1073, -1073, -1073, -1073,   -58,
   -1073, -1073,   -85,  -790,  -750, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073, -1073,  -242, -1073, -1073, -1073, -1073,    -4,
      -7, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073, -1073,  -411,
   -1073,   833,  -112, -1073, -1073,   247, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073, -1073,   340,   583, -1073, -1073,   588, -1073,
   -1073,  -572,   839, -1073, -1073,   -30,   -29, -1073, -1073,  -167,
   -1073, -1073, -1073,  -254,  -251, -1073, -1073, -1073,  -401, -1073,
   -1073,  -407, -1073,  -231,  -387,  -486, -1073, -1073, -1073, -1073,
   -1073, -1073, -1073,  -290,   156,  -582, -1073, -1073,   157,  -274,
   -1073, -1073, -1073
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    30,    32,   124,   156,   744,   142,   438,   319,   157,
     158,   452,   453,   454,   159,   314,   805,   806,   308,   447,
     459,   662,   568,   739,   859,   917,   966,  1010,  1011,  1038,
    1083,    33,   160,   564,   161,   162,   163,   665,   873,   437,
      52,    53,   258,   315,   316,   463,   667,   812,   813,   814,
     328,   329,   477,   746,   165,   440,   441,   554,   259,   114,
     100,   322,   323,   469,   470,   574,    55,   168,   654,   733,
      35,   801,   848,   849,   851,   908,   909,   894,   965,  1004,
    1005,  1097,  1099,  1078,  1063,  1123,  1124,  1120,   116,  1141,
    1136,   109,   144,  1158,   834,   895,   896,   946,   943,   117,
     874,   929,   740,   811,   875,  1128,  1085,   973,   921,   976,
    1048,  1093,  1114,  1090,  1091,  1150,  1149,  1132,  1151,   111,
     112,   372,   373,   361,   754,   749,   751,   102,   337,   593,
     677,   679,   682,   680,   103,   244,   104,   105,   106,   496,
     119,   120,   260,   387,   505,   506,   604,   261,   699,   767,
     694,   607,   612,   511,   127,   128,   266,   268,   129,   265,
     397,   692,   693,   764,   832,   833,   131,   949,   990,   991,
    1094,  1055,  1117,  1116,   133,   135,   136,   622,   296,   297,
     107,   526,   955,   794,   535,   536,   637,   638,   639,   640,
     641,   642,   643,   718,   633,   531,   630,   298,   428,   429,
     299,   300,   301
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     101,   108,   110,   171,   169,   118,   164,   164,   170,   164,
     262,   130,   132,   522,   302,   137,   134,   540,   141,   138,
     145,  1110,   147,   544,   146,   433,   434,   551,    54,   380,
     -32,   123,   708,   537,   538,   539,   742,   264,   913,   126,
     697,   317,   631,   804,   139,   180,   613,   636,   444,   710,
     187,   188,   911,  1122,   475,   166,   166,   166,   166,   745,
     760,   747,   852,   -32,   -32,   333,   334,   335,   336,   414,
     457,   854,   401,   458,   465,   592,   415,  1144,  1145,   472,
     148,   213,   214,  1143,   855,   402,   508,  1179,   403,  1153,
     572,   201,  1183,  1184,   714,   715,   177,   245,   181,  1032,
    1033,   404,   182,   183,   184,  1166,  1167,   185,   186,   599,
     963,   527,   910,  1193,  1194,   600,   528,   619,   653,   512,
     513,   251,   765,   557,   177,   634,   627,   768,   384,   295,
     776,   389,   655,   818,   391,   251,   149,   558,   600,   -32,
     560,   -32,   -32,   -32,   -32,   651,   635,   456,   172,   213,
     214,   462,   -32,   217,   218,   219,   173,   683,  1088,  1089,
     880,   176,   804,   600,   696,   177,   600,   324,   325,   267,
     264,   974,   306,   174,   213,   214,   215,   216,   217,   218,
     219,   442,   632,   222,   223,   175,   445,   446,   709,  1021,
     571,   381,   549,   343,   321,   836,   468,  1111,   189,    54,
     914,   -32,   -32,   -32,   -32,   -32,   460,   461,   347,   348,
     349,   350,   351,   352,   353,   354,   355,   356,   357,   358,
     359,   360,   -32,   362,   363,   364,   365,   366,   367,   368,
     369,   370,   371,   783,   375,   614,   472,   377,   788,   378,
     379,   615,   616,   368,   382,   716,   856,   385,   240,   932,
     241,   190,   242,   243,   563,   552,   553,   727,   728,   -59,
     191,   -59,   717,  1042,   399,   400,  1045,   509,   406,   407,
     408,   410,   411,   412,   383,   510,  1154,   272,   561,   562,
     251,   657,   903,   423,   425,  1112,   427,   192,   904,   126,
     890,  1006,   427,   427,  1019,   644,  1070,  1007,   645,  1073,
     251,   669,  1046,  1049,   770,  1087,   448,   449,   251,   251,
     609,   251,   252,  1102,   953,   780,   240,   954,   241,  1103,
     242,   243,   253,  1106,   480,   481,   193,   778,   779,   251,
     781,   690,   857,   817,   858,  1105,   391,   195,   789,   790,
      54,   240,  1152,   241,   321,   242,   243,   720,   721,   722,
     723,   877,   321,   878,   493,   543,   271,   899,   980,  1170,
    1171,  1172,   891,   196,  1133,   495,   658,   246,   659,  1159,
     839,   892,   893,  1164,    34,  1165,    36,   247,  1148,    38,
      39,   125,    40,    41,   575,   576,    42,   263,   213,   214,
     215,   216,   217,   218,   219,   516,   267,   517,  1185,  1186,
     605,   606,   519,   888,   889,   905,   906,   295,   525,   961,
     962,   982,   983,   985,   986,  1015,   251,   525,  -441,   541,
    1026,  1027,   269,   525,   545,  1034,  1035,   271,   442,   272,
     388,   495,    43,  1039,  1040,   303,    44,    45,    46,    47,
      48,    49,    50,  1069,   251,  1088,  1089,   791,   792,  1161,
     253,   468,  1188,   251,   312,   310,   311,   123,    54,   318,
     330,   338,    62,    63,   331,   332,   577,   340,  -317,   580,
     341,   342,   396,   413,   398,   417,    51,   416,   418,   495,
     419,   420,   421,   422,   426,   430,   432,   598,   435,   -32,
     -32,   466,   610,   436,   602,   439,   443,   950,   579,   482,
     476,   321,   483,   842,   585,   587,   467,   590,   484,   485,
     486,   295,   488,   487,   406,   489,   623,   491,   492,   497,
     295,   628,   498,   502,   603,   525,    38,    39,   255,    40,
      41,   126,   503,    42,   -32,   256,   649,   507,    82,   295,
      83,    84,    85,    86,   518,   532,   542,   543,   546,   550,
     559,    87,   113,   563,   565,   240,   660,   241,   567,   242,
     243,   581,   596,   597,   570,   -32,   594,   -32,   -32,   -32,
     -32,   595,   601,   608,   624,   626,   675,   646,   -32,    43,
     652,   262,   650,    44,    45,    46,    47,    48,    49,    50,
     661,   664,   666,   688,   668,   672,   673,   676,   678,   681,
      93,    94,    95,    96,    97,   684,   450,   685,   686,   687,
     695,   698,   700,   356,   358,   702,   815,   703,   704,   701,
     711,    99,  1057,    51,   705,   712,   713,   -32,   -32,   -32,
     -32,   -32,   719,   724,   716,   725,   726,   729,    62,    63,
     730,   731,  -194,   732,   738,   750,   752,   753,   -32,   755,
     756,   758,   759,   757,   771,   737,   850,   782,   784,   743,
     761,   307,   766,   777,   632,   785,   887,   786,   787,   798,
     451,   820,   822,   879,   830,   948,   828,   829,   835,   845,
    -162,   898,   916,   743,   837,   841,   846,   919,   920,   918,
     897,   951,   924,    62,    63,   769,   922,   923,   295,   933,
     772,   925,   171,   169,   427,   964,   956,   170,   810,   295,
     940,   968,   981,   809,    82,   994,    83,    84,    85,    86,
     902,   984,   793,   987,   995,   997,  1008,    87,   998,  1013,
     386,  1014,  1018,  1016,   743,  1024,  1025,   495,  1028,  1029,
    1031,  1047,   819,  1064,   821,  1065,   823,   824,   825,   826,
     827,  1068,   815,  1092,  1072,  1074,   166,  1076,  1096,  1077,
    1079,  1095,  -415,  -415,   295,  1098,  1115,  1100,  1101,    82,
     427,    83,    84,    85,    86,  1107,    93,    94,    95,    96,
      97,  1104,    87,  1119,  1129,  1140,  1131,   844,  1135,  1147,
    1157,   967,  1178,  1189,   970,   853,    37,    99,   257,  1173,
     663,  1174,  1175,  1066,   876,  1180,  1187,  1190,   390,   915,
     326,  1191,   569,   881,  1192,   882,  1195,  1196,   931,   670,
     656,   885,   886,   140,   941,   479,   734,   960,  1000,  1062,
    1001,    93,    94,    95,    96,    97,   900,  1139,  -415,  1156,
    -415,  -415,  -415,  -415,   979,   957,   944,   121,  1113,   611,
     394,  -415,    99,   691,   122,   395,    62,    63,   938,   939,
    1054,   927,   928,  1137,  1134,  1118,   774,     0,   775,     0,
     743,     0,   743,     0,     0,     0,     0,     0,    62,    63,
     130,     0,  1036,   213,   214,   215,   216,   217,   218,   219,
       0,   295,   222,   223,     0,     0,   118,   959,     0,     0,
    -415,  -415,  -415,  -415,  -415,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   876,   971,     0,     0,   230,   231,
     975,  -415,   234,   235,     0,     0,     0,     0,     0,     0,
       0,   547,    82,     0,    83,    84,    85,    86,     0,     0,
    1084,     0,     0,     0,   993,    87,     0,   810,     0,   996,
       0,     0,   809,     0,    82,     0,    83,    84,    85,    86,
       0,  1012,   115,     0,     0,     0,     0,    87,     0,  1017,
       0,     0,  1020,     0,     0,     0,     0,   143,  1126,     0,
       0,     0,     0,     0,   167,   167,     0,   167,     0,     0,
       0,     0,     0,     0,    93,    94,    95,    96,    97,     0,
      38,    39,     0,    40,    41,   179,   876,    42,     0,   876,
       0,  1044,     0,     0,   876,    99,    93,    94,    95,    96,
      97,  1056,   525,     0,     0,     0,     0,     0,     0,     0,
    1037,     0,     0,  1012,  1067,     0,  1043,    99,     0,   876,
       0,   194,   876,  1071,     0,     0,     0,   238,   239,     0,
     240,     0,   241,    43,   242,   243,     0,    44,    45,    46,
      47,    48,    49,    50,     0,  1086,     0,   988,     0,     0,
       0,     0,     0,     0,     0,   167,     0,     0,   876,     0,
       0,  1109,     0,     0,     0,     0,  1082,     0,     0,     0,
     115,  1121,     0,     0,     0,  1125,     0,    51,     0,    62,
      63,     0,   309,     0,     0,     0,   313,   876,   132,     0,
       0,  1138,     0,   548,     0,     0,     0,   115,     0,     0,
       0,   876,     0,     0,     0,     0,  1127,     0,   110,   327,
       0,     0,     0,  1163,     0,     0,     0,     0,     0,  1168,
       0,   115,   115,   115,   115,   876,     0,   339,     0,     0,
       0,     0,     0,  1177,     0,     0,     0,   -89,    31,     0,
       0,     0,     0,   876,   876,   876,     0,     0,     0,  1169,
       0,     0,     0,     0,     0,    82,     0,    83,    84,    85,
      86,     0,     0,     0,     0,     0,     0,     0,    87,     0,
     -89,   -89,     0,   376,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   115,     0,     0,   115,   167,     0,
     115,     0,     0,     0,     0,     0,   392,   393,     0,     0,
       0,     0,     0,     0,     0,     0,   -89,   -89,   -89,    31,
     -89,   -89,     0,     0,   -89,     0,   -89,    93,    94,    95,
      96,    97,     0,     0,     0,     0,   -89,   -89,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   115,    99,     0,
       0,   -89,   -89,   455,     0,     0,   -89,     0,   -89,   -89,
     -89,   -89,   115,     0,     0,     0,     0,     0,     0,   -89,
     -89,     0,     0,     0,   -89,   -89,   -89,   -89,   -89,   -89,
     -89,     0,     0,     0,     0,     0,     0,   -89,   -89,   -89,
       0,   -89,   -89,     0,     0,   -89,   -89,   -89,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -89,   -89,     0,
       0,     0,     0,   -89,   -89,     0,     0,     0,   -89,   -89,
     -89,   -89,   -89,     0,     0,     0,     0,   -89,   504,   -89,
     -89,   -89,   -89,     0,     0,     0,     0,   514,   515,   -89,
     -89,   -89,     0,     0,     0,   -89,   -89,   -89,   -89,   -89,
     -89,   -89,     0,     0,   520,     0,     0,     0,   530,     0,
     534,   534,   534,   534,   213,   214,   215,   216,   217,   218,
     219,  1002,     0,   222,   223,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -89,   -89,     0,   555,   556,   -89,
     -89,   -89,   -89,   -89,     0,     0,     0,     0,     0,   566,
       0,     0,   115,    62,    63,     0,     0,   573,     0,     0,
     -89,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   586,   588,   589,   591,     0,     0,    62,
      63,     0,     0,     0,     0,     0,  -456,   270,     0,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
       0,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,     0,     0,
     629,     0,     0,     0,   534,     0,     0,     0,     0,    82,
       0,    83,    84,    85,    86,     0,   230,   231,   232,   233,
     234,   235,    87,     0,   115,    38,    39,   255,    40,    41,
       0,   455,    42,   455,   256,    82,     0,    83,    84,    85,
      86,     0,     0,     0,     0,     0,     0,   115,    87,   113,
       0,     0,     0,     0,     0,     0,     0,     0,   238,   239,
       0,   240,     0,   241,  -522,   242,   243,  -522,     0,     0,
       0,    93,    94,    95,    96,    97,     0,   504,    43,     0,
       0,     0,    44,    45,    46,    47,    48,    49,    50,     0,
       0,     0,    99,   578,     0,     0,     0,    93,    94,    95,
      96,    97,   530,     0,     0,     0,    56,    57,    58,    59,
      60,     0,     0,     0,     0,   534,   534,     0,    99,     0,
       0,     0,    51,     0,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,   236,     0,   237,   238,   239,     0,   240,     0,
     241,     0,   242,   243,     0,  -456,     0,  -456,     0,   762,
       0,     0,    38,    39,     0,    40,    41,    79,    80,    42,
       0,   213,   214,   215,   216,   217,   218,   219,     0,   773,
     222,   223,     0,   530,     0,   534,   534,    81,   534,     0,
     534,     0,     0,     0,     0,   534,   534,   534,     0,     0,
       0,    82,     0,    83,    84,    85,    86,     0,     0,   455,
     808,     0,   816,     0,    87,    43,    88,    89,     0,    44,
      45,    46,    47,    48,    49,    50,     0,   799,    38,    39,
     255,    40,    41,     0,   831,    42,     0,     0,   763,     0,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,     0,   226,   305,     0,     0,     0,     0,    51,
      90,    91,    92,    93,    94,    95,    96,    97,     0,     0,
       0,   847,     0,     0,    98,   230,   231,   232,   233,   234,
     235,    43,     0,     0,    99,    44,    45,    46,    47,    48,
      49,    50,     0,     0,     0,   150,    38,    39,     0,    40,
      41,     0,     0,    42,     0,     0,   800,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   115,     0,     0,     0,
       0,   907,     0,    38,    39,    51,    40,    41,   455,     0,
      42,     0,     0,     0,     0,   238,   239,     0,   240,     0,
     241,     0,   242,   243,     0,     0,     0,     0,   816,    43,
       0,     0,     0,    44,    45,    46,    47,    48,    49,    50,
     831,     0,   942,   945,   947,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    43,   847,     0,     0,
      44,    45,    46,    47,    48,    49,    50,   115,     0,     0,
     816,     0,     0,    51,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   237,   238,   239,     0,   240,     0,   241,
       0,   242,   243,     0,     0,     0,     0,     0,     0,   989,
      51,     0,     0,     0,     0,     0,     0,  1050,     0,     0,
       0,     0,     0,   907,     0,  1003,     0,     0,     0,     0,
      56,    57,    58,    59,    60,     0,     0,     0,     0,     0,
       0,     0,     0,   320,  1022,     0,     0,  1023,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,     0,     0,   115,     0,
       0,     0,   861,   862,   863,   864,   865,   866,   867,     0,
    -303,  -303,   868,   869,     0,     0,  1052,     0,   989,     0,
       0,    79,    80,  1058,  1059,     0,  1003,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,     0,     0,
       0,    81,    38,    39,  1075,    40,    41,     0,     0,    42,
       0,  1080,  1081,     0,     0,    82,   115,    83,    84,    85,
      86,     0,   230,   231,   232,   233,   234,   235,    87,     0,
      88,    89,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   115,    43,     0,     0,     0,    44,
      45,    46,    47,    48,    49,    50,     0,     0,     0,  1050,
     115,     0,     0,     0,    90,    91,    92,    93,    94,    95,
      96,    97,    56,    57,    58,    59,    60,     0,    98,     0,
       0,     0,     0,     0,   870,     0,   871,  -303,    99,    51,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,     0,     0,
       0,     0,     0,     0,   861,   862,   863,   864,   865,   866,
     867,     0,  -301,  -301,   868,   869,     0,     0,     0,     0,
       0,     0,     0,    79,    80,     0,     0,     0,     0,     0,
     237,   238,   239,     0,   240,     0,   241,     0,   242,   243,
       0,     0,     0,    81,   213,   214,   215,   216,   217,   218,
     219,     0,   221,   222,   223,     0,     0,    82,     0,    83,
      84,    85,    86,     0,     0,     0,     0,     0,     0,     0,
      87,     0,    88,    89,     0,     0,     0,     0,     0,   230,
     231,   232,   233,   234,   235,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1050,     0,     0,     0,     0,    90,    91,    92,    93,
      94,    95,    96,    97,    56,    57,    58,    59,    60,     0,
      98,     0,     0,     0,     0,     0,   870,     0,   871,  -301,
      99,     0,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
       0,     0,     0,     0,     0,     0,   861,   862,   863,   864,
     865,   866,   867,     0,  -299,  -299,   868,   869,     0,     0,
       0,     0,     0,     0,     0,    79,    80,     0,     0,     0,
     213,   214,   215,   216,   217,   218,   219,     0,     0,   222,
     223,     0,     0,     0,     0,    81,     0,   237,   238,   239,
       0,   240,     0,   241,     0,   242,   243,     0,     0,    82,
       0,    83,    84,    85,    86,   230,   231,   232,   233,   234,
     235,     0,    87,     0,    88,    89,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,     0,     0,     0,     0,     0,
       0,     0,     0,  1050,     0,     0,     0,     0,    90,    91,
      92,    93,    94,    95,    96,    97,    56,    57,    58,    59,
      60,     0,    98,     0,     0,     0,     0,     0,   870,     0,
     871,  -299,    99,     0,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,     0,     0,     0,     0,     0,     0,   861,   862,
     863,   864,   865,   866,   867,     0,  -305,  -305,   868,   869,
       0,     0,     0,     0,     0,     0,     0,    79,    80,     0,
       0,     0,     0,   237,   238,   239,     0,   240,     0,   241,
       0,   242,   243,     0,     0,     0,     0,    81,   213,   214,
     215,   216,   217,   218,   219,     0,     0,   222,   223,     0,
       0,    82,     0,    83,    84,    85,    86,     0,     0,     0,
       0,     0,     0,     0,    87,     0,    88,    89,     0,     0,
       0,     0,     0,   230,   231,   232,   233,   234,   235,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   860,     0,     0,     0,     0,
      90,    91,    92,    93,    94,    95,    96,    97,    56,    57,
      58,    59,    60,     0,    98,   478,     0,     0,     0,     0,
     870,     0,   871,  -305,    99,     0,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,     0,     0,     0,     0,     0,     0,
     861,   862,   863,   864,   865,   866,   867,     0,     0,     0,
     868,   869,     0,     0,     0,     0,     0,     0,     0,    79,
      80,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    38,    39,     0,    40,    41,    81,
       0,    42,   238,   239,     0,   240,     0,   241,     0,   242,
     243,     0,     0,    82,     0,    83,    84,    85,    86,     0,
       0,     0,     0,     0,     0,     0,    87,     0,    88,    89,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    43,     0,     0,
       0,    44,    45,    46,    47,    48,    49,    50,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1050,     0,     0,
       0,     0,    90,    91,    92,    93,    94,    95,    96,    97,
      56,    57,    58,    59,    60,     0,    98,     0,     0,     0,
       0,    51,   870,     0,   871,   872,    99,     0,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,     0,     0,     0,     0,
       0,     0,   861,   862,   863,   864,   865,   866,   867,     0,
       0,     0,   868,   869,     0,     0,     0,     0,     0,     0,
       0,    79,    80,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    81,     0,     0,     0,     0,    38,    39,   197,    40,
      41,     0,     0,    42,     0,    82,     0,    83,    84,    85,
      86,    56,    57,    58,    59,    60,     0,     0,    87,     0,
      88,    89,     0,     0,     0,     0,     0,     0,     0,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,     0,     0,    43,
       0,     0,     0,    44,    45,    46,    47,    48,    49,    50,
       0,     0,     0,     0,    90,    91,    92,    93,    94,    95,
      96,    97,    79,    80,     0,     0,     0,     0,    98,     0,
       0,     0,     0,     0,   870,     0,   871,  1051,    99,     0,
       0,     0,    81,    51,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    82,     0,    83,    84,
      85,    86,   969,     0,     0,   198,   199,   471,     0,    87,
       0,    88,    89,     0,     0,    56,    57,    58,    59,    60,
       0,     0,     0,     0,   150,    38,    39,     0,    40,    41,
       0,     0,    42,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,     0,   200,     0,     0,    90,    91,    92,    93,    94,
      95,    96,    97,     0,     0,     0,     0,     0,     0,    98,
       0,     0,     0,     0,     0,     0,    79,    80,    43,    99,
       0,     0,    44,    45,    46,    47,    48,    49,    50,     0,
       0,     0,     0,     0,     0,     0,    81,     0,     0,     0,
       0,    38,    39,   374,    40,    41,     0,     0,    42,     0,
      82,     0,    83,    84,    85,    86,    56,    57,    58,    59,
      60,     0,    51,    87,   113,    88,    89,     0,     0,     0,
       0,     0,     0,     0,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,     0,     0,    43,     0,     0,     0,    44,    45,
      46,    47,    48,    49,    50,     0,     0,     0,     0,    90,
      91,    92,    93,    94,    95,    96,    97,    79,    80,     0,
       0,     0,     0,    98,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    99,     0,     0,     0,    81,    51,     0,
       0,     0,     0,     0,   958,    38,    39,   125,    40,    41,
       0,    82,    42,    83,    84,    85,    86,    56,    57,    58,
      59,    60,   582,     0,    87,     0,    88,    89,     0,     0,
       0,     0,     0,     0,     0,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,     0,     0,     0,     0,     0,    43,     0,
       0,     0,    44,    45,    46,    47,    48,    49,    50,     0,
      90,    91,    92,    93,    94,    95,    96,    97,    79,    80,
       0,     0,     0,     0,    98,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    99,     0,     0,     0,    81,     0,
       0,     0,    51,     0,     0,   972,    38,    39,   255,    40,
      41,     0,    82,    42,    83,    84,    85,    86,  -279,  -279,
    -279,  -279,  -279,     0,     0,    87,     0,    88,    89,     0,
       0,     0,     0,     0,     0,     0,  -279,  -279,  -279,  -279,
    -279,  -279,  -279,  -279,  -279,  -279,  -279,  -279,  -279,  -279,
    -279,  -279,  -279,  -279,     0,     0,     0,     0,     0,    43,
       0,     0,     0,    44,    45,    46,    47,    48,    49,    50,
       0,    90,    91,    92,    93,    94,    95,    96,    97,  -279,
    -279,     0,     0,     0,     0,    98,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    99,     0,     0,     0,  -279,
       0,     0,     0,    51,    38,    39,  1108,    40,    41,     0,
       0,    42,     0,  -279,     0,  -279,  -279,  -279,  -279,    56,
      57,    58,    59,    60,     0,     0,  -279,     0,  -279,  -279,
       0,     0,     0,     0,     0,     0,     0,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,     0,     0,    43,     0,     0,
       0,    44,    45,    46,    47,    48,    49,    50,     0,     0,
       0,     0,  -279,  -279,  -279,  -279,  -279,  -279,  -279,  -279,
      79,    80,     0,     0,     0,     0,  -279,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -279,     0,     0,     0,
      81,    51,     0,     0,     0,     0,     0,  1155,     0,     0,
       0,     0,     0,     0,    82,     0,    83,    84,    85,    86,
      56,    57,    58,    59,    60,     0,     0,    87,     0,    88,
      89,     0,     0,     0,     0,     0,     0,     0,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    90,    91,    92,    93,    94,    95,    96,
      97,    79,    80,     0,     0,     0,     0,    98,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    99,     0,     0,
       0,    81,     0,     0,     0,     0,     0,     0,  1162,     0,
       0,     0,     0,     0,     0,    82,     0,    83,    84,    85,
      86,    56,    57,    58,    59,    60,     0,     0,    87,     0,
      88,    89,     0,     0,     0,     0,     0,     0,     0,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    90,    91,    92,    93,    94,    95,
      96,    97,    79,    80,     0,     0,     0,     0,    98,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    99,     0,
       0,     0,    81,     0,     0,     0,     0,     0,     0,  1176,
      38,    39,     0,    40,    41,     0,    82,    42,    83,    84,
      85,    86,    56,    57,    58,    59,    60,     0,     0,    87,
       0,    88,    89,     0,     0,     0,     0,     0,     0,     0,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,     0,     0,
       0,     0,     0,    43,     0,     0,     0,    44,    45,    46,
      47,    48,    49,    50,     0,    90,    91,    92,    93,    94,
      95,    96,    97,    79,    80,     0,     0,     0,     0,    98,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    99,
       0,     0,     0,    81,     0,     0,     0,    51,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    82,     0,    83,
      84,    85,    86,   464,     0,     0,     0,     0,     0,     0,
      87,     0,    88,    89,  -240,   248,     0,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   249,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    90,    91,    92,    93,
      94,    95,    96,    97,   230,   231,   232,   233,   234,   235,
      98,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      99,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,     0,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   230,   231,
     232,   233,   234,   235,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,     0,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   230,   231,   232,   233,   234,   235,     0,     0,     0,
     250,     0,   237,   238,   239,     0,   240,     0,   241,     0,
     242,   243,  -240,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    62,    63,     0,
       0,     0,     0,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,     0,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,     0,     0,   236,     0,   237,   238,   239,     0,
     240,     0,   241,     0,   242,   243,     0,     0,     0,   617,
     230,   231,   232,   233,   234,   235,  1060,  1061,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    82,     0,    83,    84,    85,    86,     0,
       0,     0,     0,     0,     0,     0,    87,   236,     0,   237,
     238,   239,     0,   240,     0,   241,     0,   242,   243,     0,
    -245,   304,   618,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,     0,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,     0,     0,     0,    93,    94,    95,    96,    97,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     230,   231,   232,   233,   234,   235,    99,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   236,     0,   237,   238,
     239,     0,   240,     0,   241,     0,   242,   243,     0,     0,
    1181,   999,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,     0,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   230,
     231,   232,   233,   234,   235,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,     0,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,     0,     0,   236,     0,   237,   238,
     239,     0,   240,     0,   241,     0,   242,   243,     0,     0,
       0,     0,   230,   231,   232,   233,   234,   235,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,     0,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   230,   231,   232,   233,   234,
     235,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   236,     0,   237,   238,   239,
       0,   240,     0,   241,     0,   242,   243,  1182,     0,     0,
       0,     0,     0,     0,     0,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,     0,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,     0,     0,     0,     0,   236,     0,
     237,   238,   239,     0,   240,   706,   241,     0,   242,   243,
       0,   707,   230,   231,   232,   233,   234,   235,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,     0,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,     0,     0,     0,
       0,   236,     0,   237,   238,   239,     0,   240,     0,   241,
       0,   242,   243,     0,   473,   230,   231,   232,   233,   234,
     235,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,     0,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   230,   231,
     232,   233,   234,   235,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   236,     0,
     237,   238,   239,     0,   240,     0,   241,     0,   242,   243,
       0,   501,     0,     0,     0,     0,     0,     0,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,     0,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,     0,     0,     0,
       0,   236,     0,   237,   238,   239,     0,   240,     0,   241,
       0,   242,   243,     0,   583,   230,   231,   232,   233,   234,
     235,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,     0,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
       0,     0,     0,     0,   236,   802,   237,   238,   239,     0,
     240,     0,   241,     0,   242,   243,   803,     0,   230,   231,
     232,   233,   234,   235,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,     0,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   230,   231,   232,   233,   234,   235,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   236,     0,   237,   238,   239,     0,   240,     0,   241,
       0,   242,   243,   912,     0,     0,     0,     0,     0,     0,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,     0,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,     0,
       0,     0,     0,     0,   236,     0,   237,   238,   239,     0,
     240,     0,   241,     0,   242,   243,   930,   230,   231,   232,
     233,   234,   235,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,     0,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,     0,     0,     0,     0,     0,   236,     0,   237,
     238,   239,     0,   240,     0,   241,     0,   242,   243,   977,
     230,   231,   232,   233,   234,   235,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,     0,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   620,
     225,   621,   227,   228,   229,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   230,   231,   232,   233,   234,   235,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   236,     0,   237,   238,   239,     0,   240,
       0,   241,     0,   242,   243,   978,     0,     0,     0,     0,
       0,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,     0,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
       0,     0,     0,   344,     0,   345,   236,     0,   237,   238,
     239,     0,   240,   346,   241,     0,   242,   243,   230,   231,
     232,   233,   234,   235,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,     0,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,     0,     0,     0,   344,     0,   345,   236,
       0,   237,   238,   239,     0,   240,   346,   241,     0,   242,
     243,   230,   231,   232,   233,   234,   235,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,     0,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   230,   231,   232,   233,   234,   235,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   647,   648,     0,   236,     0,   237,   238,   239,     0,
     240,     0,   241,     0,   242,   243,     0,     0,     0,     0,
       0,     0,     0,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   431,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,     0,     0,     0,     0,     0,   236,   254,   237,
     238,   239,     0,   240,     0,   241,     0,   242,   243,     0,
     230,   231,   232,   233,   234,   235,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,     0,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,     0,     0,     0,     0,     0,
     236,     0,   237,   238,   239,     0,   240,     0,   241,     0,
     242,   243,     0,   230,   231,   232,   233,   234,   235,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
       0,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   230,   231,   232,   233,
     234,   235,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   236,     0,   237,   238,
     239,     0,   240,     0,   241,   474,   242,   243,     0,     0,
       0,     0,     0,     0,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,     0,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,     0,     0,     0,     0,     0,     0,   236,
       0,   237,   238,   239,     0,   240,   490,   241,     0,   242,
     243,   230,   231,   232,   233,   234,   235,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,     0,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,     0,     0,     0,     0,
       0,     0,   236,   494,   237,   238,   239,     0,   240,     0,
     241,     0,   242,   243,   230,   231,   232,   233,   234,   235,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,     0,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   230,   231,   232,
     233,   234,   235,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   236,     0,   237,
     238,   239,     0,   240,     0,   241,   499,   242,   243,     0,
       0,     0,     0,     0,     0,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,     0,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,     0,     0,     0,     0,     0,     0,
     236,     0,   237,   238,   239,     0,   240,   500,   241,     0,
     242,   243,   230,   231,   232,   233,   234,   235,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,     0,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,     0,     0,     0,
       0,     0,     0,   236,     0,   237,   238,   239,     0,   240,
       0,   241,   584,   242,   243,   230,   231,   232,   233,   234,
     235,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,     0,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   230,   231,
     232,   233,   234,   235,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   236,     0,
     237,   238,   239,     0,   240,     0,   241,   671,   242,   243,
       0,     0,     0,     0,     0,     0,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,     0,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,     0,     0,     0,     0,     0,
       0,   236,     0,   237,   238,   239,     0,   240,     0,   241,
     674,   242,   243,   230,   231,   232,   233,   234,   235,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
       0,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,     0,     0,
       0,     0,     0,     0,   236,     0,   237,   238,   239,     0,
     240,   689,   241,     0,   242,   243,   230,   231,   232,   233,
     234,   235,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,     0,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   230,
     231,   232,   233,   234,   235,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   236,
       0,   237,   238,   239,     0,   240,     0,   241,   735,   242,
     243,     0,     0,     0,     0,     0,     0,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,     0,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,     0,     0,     0,     0,
       0,     0,   236,     0,   237,   238,   239,     0,   240,     0,
     241,   748,   242,   243,   230,   231,   232,   233,   234,   235,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,     0,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,     0,
       0,     0,     0,     0,     0,   236,     0,   237,   238,   239,
       0,   240,     0,   241,   795,   242,   243,   230,   231,   232,
     233,   234,   235,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,     0,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     230,   231,   232,   233,   234,   235,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     236,     0,   237,   238,   239,     0,   240,     0,   241,   796,
     242,   243,     0,     0,     0,     0,     0,     0,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,     0,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,     0,     0,     0,
       0,     0,     0,   236,     0,   237,   238,   239,     0,   240,
       0,   241,   797,   242,   243,   230,   231,   232,   233,   234,
     235,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,     0,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
       0,     0,     0,     0,     0,     0,   236,     0,   237,   238,
     239,     0,   240,   838,   241,     0,   242,   243,   230,   231,
     232,   233,   234,   235,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,     0,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   230,   231,   232,   233,   234,   235,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   236,     0,   237,   238,   239,     0,   240,   840,   241,
       0,   242,   243,     0,     0,     0,     0,     0,     0,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
       0,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,     0,     0,
       0,   843,     0,     0,   236,     0,   237,   238,   239,     0,
     240,     0,   241,     0,   242,   243,   230,   231,   232,   233,
     234,   235,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,     0,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,     0,     0,     0,     0,     0,     0,   236,     0,   237,
     238,   239,     0,   240,   883,   241,     0,   242,   243,   230,
     231,   232,   233,   234,   235,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,     0,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   230,   231,   232,   233,   234,   235,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   236,     0,   237,   238,   239,     0,   240,   884,
     241,     0,   242,   243,     0,     0,     0,     0,     0,     0,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,     0,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,     0,
       0,     0,     0,     0,     0,   236,     0,   237,   238,   239,
       0,   240,   901,   241,     0,   242,   243,   230,   231,   232,
     233,   234,   235,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,     0,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,     0,     0,     0,     0,     0,     0,   236,     0,
     237,   238,   239,     0,   240,   934,   241,     0,   242,   243,
     230,   231,   232,   233,   234,   235,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,     0,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   230,   231,   232,   233,   234,   235,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   236,     0,   237,   238,   239,     0,   240,
     935,   241,     0,   242,   243,     0,     0,     0,     0,     0,
       0,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,     0,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
       0,     0,     0,     0,     0,     0,   236,     0,   237,   238,
     239,     0,   240,   936,   241,     0,   242,   243,   230,   231,
     232,   233,   234,   235,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,     0,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,     0,     0,     0,     0,     0,     0,   236,
       0,   237,   238,   239,     0,   240,   937,   241,     0,   242,
     243,   230,   231,   232,   233,   234,   235,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,     0,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   230,   231,   232,   233,   234,   235,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   236,     0,   237,   238,   239,     0,
     240,   952,   241,     0,   242,   243,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1041,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,     0,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,     0,   236,     0,   237,
     238,   239,     0,   240,  1030,   241,     0,   242,   243,     0,
       0,     0,     0,     0,   230,   231,   232,   233,   234,   235,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,     0,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,     0,
     236,     0,   237,   238,   239,     0,   240,     0,   241,     0,
     242,   243,     0,     0,     0,     0,     0,   230,   231,   232,
     233,   234,   235,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,     0,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     230,   231,   232,   233,   234,   235,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     236,  1130,   237,   238,   239,     0,   240,     0,   241,     0,
     242,   243,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1146,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,     0,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,     0,   236,     0,   237,   238,   239,     0,   240,
       0,   241,  1142,   242,   243,     0,     0,     0,     0,     0,
     230,   231,   232,   233,   234,   235,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,     0,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,     0,   236,     0,   237,   238,
     239,     0,   240,     0,   241,     0,   242,   243,     0,     0,
       0,     0,     0,   230,   231,   232,   233,   234,   235,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
       0,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   230,   625,   232,   233,
     234,   235,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   236,     0,   237,   238,
     239,     0,   240,  1160,   241,     0,   242,   243,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    62,    63,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   236,
       0,   237,   238,   239,     0,   240,     0,   241,     0,   242,
     243,    56,    57,    58,    59,    60,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    61,
     273,   274,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,     0,     0,     0,
       0,     0,   236,     0,   237,   238,   239,     0,   240,     0,
     241,     0,   242,   243,    82,     0,    83,    84,    85,    86,
       0,     0,    79,    80,     0,     0,     0,    87,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    81,   275,   276,   277,   278,     0,     0,     0,
       0,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,     0,   290,   291,     0,     0,     0,     0,    87,
       0,    88,    89,     0,     0,     0,    93,    94,    95,    96,
      97,     0,     0,   178,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    99,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    90,    91,    92,   292,    94,
      95,    96,    97,    56,    57,    58,    59,    60,     0,    98,
      62,    63,     0,     0,     0,     0,     0,   293,     0,   294,
       0,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,     0,
       0,     0,   451,     0,     0,   861,   862,   863,   864,   865,
     866,   867,     0,     0,     0,   868,   869,     0,     0,     0,
       0,     0,     0,     0,    79,    80,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    81,     0,    82,     0,    83,    84,
      85,    86,     0,     0,     0,     0,     0,     0,    82,    87,
      83,    84,    85,    86,    56,    57,    58,    59,    60,     0,
       0,    87,     0,    88,    89,     0,     0,     0,     0,     0,
       0,     0,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
       0,     0,     0,     0,     0,     0,     0,     0,    93,    94,
      95,    96,    97,     0,     0,     0,     0,    90,    91,    92,
      93,    94,    95,    96,    97,    79,    80,     0,     0,    99,
       0,    98,     0,     0,     0,     0,     0,   870,     0,   871,
       0,    99,     0,     0,     0,    81,   521,   276,   277,   278,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    82,
       0,    83,    84,    85,    86,    56,    57,    58,    59,    60,
       0,     0,    87,     0,    88,    89,     0,     0,     0,     0,
       0,     0,     0,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,     0,   523,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    90,    91,
      92,   292,    94,    95,    96,    97,    79,    80,     0,     0,
       0,     0,    98,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    99,     0,     0,     0,    81,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      82,     0,    83,    84,    85,    86,    56,    57,    58,    59,
      60,   524,     0,    87,     0,    88,    89,     0,     0,     0,
       0,     0,     0,     0,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    90,
      91,    92,    93,    94,    95,    96,    97,    79,    80,     0,
       0,     0,     0,    98,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    99,     0,     0,     0,    81,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    82,     0,    83,    84,    85,    86,     0,     0,     0,
     791,   792,     0,     0,    87,     0,    88,    89,    56,    57,
      58,    59,    60,     0,     0,    62,    63,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,     0,     0,     0,     0,     0,     0,
      90,    91,    92,    93,    94,    95,    96,    97,     0,     0,
     151,     0,     0,     0,    98,     0,     0,     0,     0,    79,
      80,     0,     0,     0,    99,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    81,
       0,    82,     0,    83,    84,    85,    86,     0,     0,     0,
       0,     0,     0,    82,    87,    83,    84,    85,    86,    56,
      57,    58,    59,    60,     0,     0,    87,   113,    88,    89,
       0,     0,     0,     0,     0,     0,     0,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,     0,     0,     0,     0,     0,
       0,     0,     0,    93,    94,    95,    96,    97,     0,     0,
       0,     0,    90,    91,    92,    93,    94,    95,    96,    97,
      79,    80,     0,     0,    99,     0,    98,     0,     0,     0,
       0,     0,     0,     0,   741,     0,    99,     0,     0,     0,
      81,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   405,     0,    82,     0,    83,    84,    85,    86,
      56,    57,    58,    59,    60,     0,     0,    87,     0,    88,
      89,     0,     0,     0,     0,     0,     0,     0,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    90,    91,    92,    93,    94,    95,    96,
      97,    79,    80,     0,     0,     0,     0,    98,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    99,     0,     0,
       0,    81,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    82,     0,    83,    84,    85,
      86,    56,    57,    58,    59,    60,     0,     0,    87,     0,
      88,    89,     0,     0,     0,     0,     0,     0,     0,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    90,    91,    92,    93,    94,    95,
      96,    97,    79,    80,     0,     0,     0,     0,    98,     0,
     424,     0,     0,     0,     0,     0,     0,     0,    99,     0,
       0,     0,    81,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    82,     0,    83,    84,
      85,    86,    56,    57,    58,    59,    60,     0,     0,    87,
       0,    88,    89,     0,     0,     0,     0,     0,     0,     0,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    90,    91,    92,    93,    94,
      95,    96,    97,    79,    80,     0,     0,     0,     0,    98,
       0,     0,     0,     0,     0,     0,     0,     0,   736,    99,
       0,     0,     0,    81,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    82,     0,    83,
      84,    85,    86,    56,    57,    58,    59,    60,     0,     0,
      87,     0,    88,    89,     0,     0,     0,     0,     0,     0,
       0,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    90,    91,    92,    93,
      94,    95,    96,    97,    79,    80,     0,     0,     0,     0,
      98,     0,     0,     0,     0,     0,     0,     0,   741,     0,
      99,     0,     0,     0,    81,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    82,     0,
      83,    84,    85,    86,    56,    57,    58,    59,    60,     0,
       0,    87,     0,    88,    89,     0,     0,     0,     0,     0,
       0,     0,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
       0,     0,     0,     0,     0,     0,  1009,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    90,    91,    92,
      93,    94,    95,    96,    97,    79,    80,     0,     0,     0,
       0,    98,     0,     0,     0,     0,     0,   926,     0,     0,
       0,    99,     0,     0,     0,    81,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    82,
       0,    83,    84,    85,    86,    56,    57,    58,    59,    60,
       0,     0,    87,     0,    88,    89,     0,     0,     0,     0,
       0,     0,     0,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    90,    91,
      92,    93,    94,    95,    96,    97,    79,    80,     0,     0,
       0,     0,    98,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    99,     0,     0,     0,    81,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      82,     0,    83,    84,    85,    86,    56,    57,    58,    59,
      60,     0,     0,    87,     0,    88,    89,     0,     0,     0,
       0,     0,     0,     0,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    90,
      91,    92,    93,    94,    95,    96,    97,    79,    80,     0,
       0,     0,     0,    98,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    99,     0,     0,     0,    81,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    62,    63,     0,
       0,    82,     0,    83,    84,    85,    86,    56,    57,    58,
      59,    60,     0,     0,    87,     0,    88,    89,     0,     0,
       0,     0,     0,     0,     0,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    62,    63,     0,     0,     0,     0,     0,
      90,    91,    92,    93,    94,    95,    96,    97,    79,    80,
       0,     0,     0,    82,   409,    83,    84,    85,    86,     0,
       0,     0,     0,     0,    99,     0,    87,     0,    81,   150,
      38,    39,     0,    40,    41,     0,     0,    42,   151,   139,
       0,     0,    82,     0,    83,    84,    85,    86,     0,   152,
     153,     0,     0,     0,     0,    87,     0,   992,    89,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    82,
       0,    83,    84,    85,    86,    93,    94,    95,    96,    97,
      62,    63,    87,    43,     0,     0,   529,    44,    45,   154,
      47,    48,    49,    50,     0,     0,    99,     0,     0,     0,
       0,    90,    91,    92,    93,    94,    95,    96,    97,    62,
      63,     0,     0,     0,     0,    98,     0,    38,    39,     0,
      40,    41,     0,     0,    42,    99,   155,    51,     0,     0,
       0,    93,    94,    95,    96,    97,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   150,    38,    39,     0,    40,
      41,     0,    99,    42,     0,   139,    82,     0,    83,    84,
      85,    86,     0,     0,     0,   152,   153,     0,     0,    87,
      43,     0,     0,     0,    44,    45,    46,    47,    48,    49,
      50,    62,    63,     0,     0,    82,     0,    83,    84,    85,
      86,     0,     0,    62,    63,     0,     0,     0,    87,    43,
       0,     0,     0,    44,    45,   154,    47,    48,    49,    50,
       0,     0,     0,     0,    51,     0,    62,    63,    93,    94,
      95,    96,    97,    62,    63,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    99,
       0,     0,   155,    51,     0,     0,     0,    93,    94,    95,
      96,    97,     0,     0,     0,     0,     0,    82,     0,    83,
      84,    85,    86,     0,     0,     0,     0,     0,    99,    82,
      87,    83,    84,    85,    86,  1053,     0,     0,     0,     0,
       0,     0,    87,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    82,     0,    83,    84,    85,    86,     0,    82,
       0,    83,    84,    85,    86,    87,     0,     0,     0,     0,
       0,     0,    87,     0,     0,     0,     0,     0,     0,    93,
      94,    95,    96,    97,     0,     0,     0,     0,     0,     0,
     533,    93,    94,    95,    96,    97,     0,     0,     0,     0,
      99,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   807,    99,     0,    93,    94,    95,    96,    97,     0,
       0,    93,    94,    95,    96,    97,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    99,     0,     0,     0,     0,
       0,     0,    99
};

static const yytype_int16 yycheck[] =
{
       7,     8,     9,    35,    35,    12,    33,    34,    35,    36,
     122,    18,    19,   414,   139,    22,    20,   424,    25,    23,
      27,     1,    29,   430,    28,   299,   300,   438,     6,    14,
       0,     1,    27,   420,   421,   422,   666,   124,    14,    17,
     612,   166,    54,   738,    79,    70,     1,   533,    50,   631,
      57,    58,   852,  1099,   327,    33,    34,    35,    36,   672,
     690,   674,   801,    33,    34,   190,   191,   192,   193,   177,
      91,     1,   177,    94,   318,   486,   184,  1123,  1124,   322,
       0,    15,    16,  1122,    14,   190,     1,  1159,   177,     1,
     183,    98,  1164,  1165,    26,    27,   189,   104,   123,    92,
      93,   190,   127,   128,   129,  1144,  1145,   132,   133,   183,
     910,   177,   851,  1185,  1186,   189,   182,   518,   183,   392,
     393,   189,   694,   191,   189,   532,   527,   699,   253,   136,
     712,   256,   183,   746,   259,   189,   188,   191,   189,   109,
      50,   111,   112,   113,   114,   546,   533,   313,   190,    15,
      16,   317,   122,    19,    20,    21,    74,   183,    64,    65,
     183,   130,   857,   189,   183,   189,   189,   174,   175,   188,
     257,   921,   150,   184,    15,    16,    17,    18,    19,    20,
      21,   306,   194,    24,    25,   184,   188,   189,   183,   979,
     463,   176,   436,   200,   172,   767,   321,   177,   126,   177,
     176,   171,   172,   173,   174,   175,   188,   189,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   192,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   719,   241,   190,   479,   244,   724,   246,
     247,   514,   515,   250,   251,   177,   176,   254,   182,   879,
     184,   182,   186,   187,   184,   188,   189,   644,   645,   189,
     182,   191,   194,  1013,   271,   272,  1016,   182,   275,   276,
     277,   278,   279,   280,   252,   190,   188,   189,   188,   189,
     189,   554,   184,   290,   291,   191,   293,   182,   190,   267,
       1,   183,   299,   300,   183,    51,  1046,   189,    54,  1049,
     189,   574,   183,   183,   705,   183,   310,   311,   189,   189,
       1,   189,   177,   183,    51,   716,   182,    54,   184,   189,
     186,   187,   189,   183,   331,   332,   182,   714,   715,   189,
     717,   604,   189,   744,   191,  1085,   461,   182,   725,   726,
     318,   182,  1132,   184,   322,   186,   187,   637,   638,   639,
     640,   189,   330,   191,   361,   189,   189,   191,   191,  1149,
    1150,  1151,    73,   182,  1114,   372,   560,   182,   562,  1137,
     771,    82,    83,  1141,     2,  1143,     4,   182,  1128,    70,
      71,    72,    73,    74,   188,   189,    77,   188,    15,    16,
      17,    18,    19,    20,    21,   402,   188,   404,  1166,  1167,
     188,   189,   409,   188,   189,   188,   189,   414,   415,   188,
     189,   188,   189,   188,   189,   188,   189,   424,   189,   426,
     188,   189,   189,   430,   431,   188,   189,   189,   553,   189,
       1,   438,   123,   188,   189,   182,   127,   128,   129,   130,
     131,   132,   133,   188,   189,    64,    65,   118,   119,   188,
     189,   576,   188,   189,    68,   190,   190,     1,   436,   182,
     190,   183,    33,    34,   184,   184,   473,   183,     1,   476,
     184,   184,   189,   177,   189,   177,   167,    19,   124,   486,
     177,   177,   177,   177,   184,   184,   107,   494,   193,    33,
      34,     3,   183,   182,   501,   188,   188,   898,   476,   177,
     184,   479,   177,   777,   482,   483,   191,   485,   177,   177,
     182,   518,   124,   183,   521,   124,   523,   184,   184,     1,
     527,   528,   185,   177,   502,   532,    70,    71,    72,    73,
      74,   509,   188,    77,    78,    79,   543,   190,   109,   546,
     111,   112,   113,   114,   177,   184,   191,   189,   177,   190,
     188,   122,   123,   184,   190,   182,   563,   184,   115,   186,
     187,   191,   124,   124,   190,   109,   189,   111,   112,   113,
     114,   189,   183,   190,    51,   185,   583,   185,   122,   123,
     183,   693,   188,   127,   128,   129,   130,   131,   132,   133,
     188,   190,     3,   600,   182,   185,   185,   183,   183,   183,
     171,   172,   173,   174,   175,   124,     1,   124,   189,   189,
     183,   190,   177,   620,   621,    98,   741,   624,   625,   177,
     190,   192,  1029,   167,   177,    51,   185,   171,   172,   173,
     174,   175,    17,    17,   177,    27,    26,   182,    33,    34,
     647,   648,   191,   650,   190,   183,   183,   183,   192,   183,
     185,   124,   124,   185,   177,   662,    81,   183,   183,   666,
     191,     1,   191,   190,   194,   183,   190,   183,   183,   191,
      65,   182,   182,   177,   188,    84,   185,   185,   191,   182,
     177,   177,   182,   690,   191,   191,   188,   182,   182,   188,
     191,   177,   182,    33,    34,   702,   188,   188,   705,   188,
     707,   182,   734,   734,   711,    84,   177,   734,   740,   716,
     188,   177,   188,   740,   109,   117,   111,   112,   113,   114,
     845,   188,   729,   188,   125,   185,   177,   122,   191,   183,
       1,   177,    57,   183,   741,   188,    92,   744,   177,   184,
     188,   182,   749,   177,   751,   182,   753,   754,   755,   756,
     757,   183,   877,    63,   190,   190,   734,   185,   182,   190,
     190,   190,    33,    34,   771,   184,    86,   190,   190,   109,
     777,   111,   112,   113,   114,   188,   171,   172,   173,   174,
     175,   177,   122,    85,   177,    86,   177,   794,    87,   177,
      88,   916,   191,   191,   919,   802,     5,   192,   120,   188,
     566,   188,   188,  1040,   811,   188,   188,   188,   257,   857,
     177,   191,   461,   820,   191,   822,   191,   191,   877,   576,
     553,   828,   829,    24,     1,   330,   654,   906,   962,  1035,
     963,   171,   172,   173,   174,   175,   843,  1119,   109,  1135,
     111,   112,   113,   114,   929,   903,     1,    14,  1090,   509,
     267,   122,   192,   606,    15,   267,    33,    34,   887,   889,
    1027,   868,   869,  1117,  1115,  1096,   710,    -1,   711,    -1,
     877,    -1,   879,    -1,    -1,    -1,    -1,    -1,    33,    34,
     887,    -1,  1007,    15,    16,    17,    18,    19,    20,    21,
      -1,   898,    24,    25,    -1,    -1,   903,   904,    -1,    -1,
     171,   172,   173,   174,   175,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   921,   919,    -1,    -1,    50,    51,
     924,   192,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     1,   109,    -1,   111,   112,   113,   114,    -1,    -1,
    1065,    -1,    -1,    -1,   951,   122,    -1,   979,    -1,   956,
      -1,    -1,   979,    -1,   109,    -1,   111,   112,   113,   114,
      -1,   968,    11,    -1,    -1,    -1,    -1,   122,    -1,   973,
      -1,    -1,   976,    -1,    -1,    -1,    -1,    26,  1103,    -1,
      -1,    -1,    -1,    -1,    33,    34,    -1,    36,    -1,    -1,
      -1,    -1,    -1,    -1,   171,   172,   173,   174,   175,    -1,
      70,    71,    -1,    73,    74,    54,  1013,    77,    -1,  1016,
      -1,  1015,    -1,    -1,  1021,   192,   171,   172,   173,   174,
     175,  1028,  1029,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1008,    -1,    -1,  1040,  1041,    -1,  1014,   192,    -1,  1046,
      -1,    90,  1049,  1047,    -1,    -1,    -1,   179,   180,    -1,
     182,    -1,   184,   123,   186,   187,    -1,   127,   128,   129,
     130,   131,   132,   133,    -1,  1069,    -1,     1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   124,    -1,    -1,  1085,    -1,
      -1,  1088,    -1,    -1,    -1,    -1,  1064,    -1,    -1,    -1,
     139,  1098,    -1,    -1,    -1,  1102,    -1,   167,    -1,    33,
      34,    -1,   151,    -1,    -1,    -1,   155,  1114,  1115,    -1,
      -1,  1118,    -1,   183,    -1,    -1,    -1,   166,    -1,    -1,
      -1,  1128,    -1,    -1,    -1,    -1,  1104,    -1,  1135,   178,
      -1,    -1,    -1,  1140,    -1,    -1,    -1,    -1,    -1,  1146,
      -1,   190,   191,   192,   193,  1152,    -1,   196,    -1,    -1,
      -1,    -1,    -1,  1157,    -1,    -1,    -1,     0,     1,    -1,
      -1,    -1,    -1,  1170,  1171,  1172,    -1,    -1,    -1,  1147,
      -1,    -1,    -1,    -1,    -1,   109,    -1,   111,   112,   113,
     114,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   122,    -1,
      33,    34,    -1,   242,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   253,    -1,    -1,   256,   257,    -1,
     259,    -1,    -1,    -1,    -1,    -1,   265,   266,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    69,    70,    71,     1,
      73,    74,    -1,    -1,    77,    -1,    79,   171,   172,   173,
     174,   175,    -1,    -1,    -1,    -1,    89,    90,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   306,   192,    -1,
      -1,    33,    34,   312,    -1,    -1,   109,    -1,   111,   112,
     113,   114,   321,    -1,    -1,    -1,    -1,    -1,    -1,   122,
     123,    -1,    -1,    -1,   127,   128,   129,   130,   131,   132,
     133,    -1,    -1,    -1,    -1,    -1,    -1,    69,    70,    71,
      -1,    73,    74,    -1,    -1,    77,    78,    79,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    90,    -1,
      -1,    -1,    -1,   166,   167,    -1,    -1,    -1,   171,   172,
     173,   174,   175,    -1,    -1,    -1,    -1,   109,   387,   111,
     112,   113,   114,    -1,    -1,    -1,    -1,   396,   397,   192,
     122,   123,    -1,    -1,    -1,   127,   128,   129,   130,   131,
     132,   133,    -1,    -1,   413,    -1,    -1,    -1,   417,    -1,
     419,   420,   421,   422,    15,    16,    17,    18,    19,    20,
      21,     1,    -1,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   166,   167,    -1,   446,   447,   171,
     172,   173,   174,   175,    -1,    -1,    -1,    -1,    -1,   458,
      -1,    -1,   461,    33,    34,    -1,    -1,   466,    -1,    -1,
     192,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   482,   483,   484,   485,    -1,    -1,    33,
      34,    -1,    -1,    -1,    -1,    -1,     0,     1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    -1,    -1,
     529,    -1,    -1,    -1,   533,    -1,    -1,    -1,    -1,   109,
      -1,   111,   112,   113,   114,    -1,    50,    51,    52,    53,
      54,    55,   122,    -1,   553,    70,    71,    72,    73,    74,
      -1,   560,    77,   562,    79,   109,    -1,   111,   112,   113,
     114,    -1,    -1,    -1,    -1,    -1,    -1,   576,   122,   123,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   179,   180,
      -1,   182,    -1,   184,   185,   186,   187,   188,    -1,    -1,
      -1,   171,   172,   173,   174,   175,    -1,   606,   123,    -1,
      -1,    -1,   127,   128,   129,   130,   131,   132,   133,    -1,
      -1,    -1,   192,     1,    -1,    -1,    -1,   171,   172,   173,
     174,   175,   631,    -1,    -1,    -1,    14,    15,    16,    17,
      18,    -1,    -1,    -1,    -1,   644,   645,    -1,   192,    -1,
      -1,    -1,   167,    -1,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,   176,    -1,   178,   179,   180,    -1,   182,    -1,
     184,    -1,   186,   187,    -1,   189,    -1,   191,    -1,     1,
      -1,    -1,    70,    71,    -1,    73,    74,    75,    76,    77,
      -1,    15,    16,    17,    18,    19,    20,    21,    -1,   708,
      24,    25,    -1,   712,    -1,   714,   715,    95,   717,    -1,
     719,    -1,    -1,    -1,    -1,   724,   725,   726,    -1,    -1,
      -1,   109,    -1,   111,   112,   113,   114,    -1,    -1,   738,
     739,    -1,   741,    -1,   122,   123,   124,   125,    -1,   127,
     128,   129,   130,   131,   132,   133,    -1,     1,    70,    71,
      72,    73,    74,    -1,   763,    77,    -1,    -1,    80,    -1,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    -1,    28,     1,    -1,    -1,    -1,    -1,   167,
     168,   169,   170,   171,   172,   173,   174,   175,    -1,    -1,
      -1,   800,    -1,    -1,   182,    50,    51,    52,    53,    54,
      55,   123,    -1,    -1,   192,   127,   128,   129,   130,   131,
     132,   133,    -1,    -1,    -1,    69,    70,    71,    -1,    73,
      74,    -1,    -1,    77,    -1,    -1,    80,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   845,    -1,    -1,    -1,
      -1,   850,    -1,    70,    71,   167,    73,    74,   857,    -1,
      77,    -1,    -1,    -1,    -1,   179,   180,    -1,   182,    -1,
     184,    -1,   186,   187,    -1,    -1,    -1,    -1,   877,   123,
      -1,    -1,    -1,   127,   128,   129,   130,   131,   132,   133,
     889,    -1,   891,   892,   893,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   123,   906,    -1,    -1,
     127,   128,   129,   130,   131,   132,   133,   916,    -1,    -1,
     919,    -1,    -1,   167,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   178,   179,   180,    -1,   182,    -1,   184,
      -1,   186,   187,    -1,    -1,    -1,    -1,    -1,    -1,   948,
     167,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,
      -1,    -1,    -1,   962,    -1,   964,    -1,    -1,    -1,    -1,
      14,    15,    16,    17,    18,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,   983,    -1,    -1,   986,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    -1,    -1,  1007,    -1,
      -1,    -1,    56,    57,    58,    59,    60,    61,    62,    -1,
      64,    65,    66,    67,    -1,    -1,  1025,    -1,  1027,    -1,
      -1,    75,    76,  1032,  1033,    -1,  1035,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    95,    70,    71,  1053,    73,    74,    -1,    -1,    77,
      -1,  1060,  1061,    -1,    -1,   109,  1065,   111,   112,   113,
     114,    -1,    50,    51,    52,    53,    54,    55,   122,    -1,
     124,   125,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1103,   123,    -1,    -1,    -1,   127,
     128,   129,   130,   131,   132,   133,    -1,    -1,    -1,     1,
    1119,    -1,    -1,    -1,   168,   169,   170,   171,   172,   173,
     174,   175,    14,    15,    16,    17,    18,    -1,   182,    -1,
      -1,    -1,    -1,    -1,   188,    -1,   190,   191,   192,   167,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    57,    58,    59,    60,    61,
      62,    -1,    64,    65,    66,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    75,    76,    -1,    -1,    -1,    -1,    -1,
     178,   179,   180,    -1,   182,    -1,   184,    -1,   186,   187,
      -1,    -1,    -1,    95,    15,    16,    17,    18,    19,    20,
      21,    -1,    23,    24,    25,    -1,    -1,   109,    -1,   111,
     112,   113,   114,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     122,    -1,   124,   125,    -1,    -1,    -1,    -1,    -1,    50,
      51,    52,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    -1,    -1,    -1,    -1,   168,   169,   170,   171,
     172,   173,   174,   175,    14,    15,    16,    17,    18,    -1,
     182,    -1,    -1,    -1,    -1,    -1,   188,    -1,   190,   191,
     192,    -1,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,    59,
      60,    61,    62,    -1,    64,    65,    66,    67,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    75,    76,    -1,    -1,    -1,
      15,    16,    17,    18,    19,    20,    21,    -1,    -1,    24,
      25,    -1,    -1,    -1,    -1,    95,    -1,   178,   179,   180,
      -1,   182,    -1,   184,    -1,   186,   187,    -1,    -1,   109,
      -1,   111,   112,   113,   114,    50,    51,    52,    53,    54,
      55,    -1,   122,    -1,   124,   125,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,   168,   169,
     170,   171,   172,   173,   174,   175,    14,    15,    16,    17,
      18,    -1,   182,    -1,    -1,    -1,    -1,    -1,   188,    -1,
     190,   191,   192,    -1,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    -1,    -1,    -1,    -1,    -1,    -1,    56,    57,
      58,    59,    60,    61,    62,    -1,    64,    65,    66,    67,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,    -1,
      -1,    -1,    -1,   178,   179,   180,    -1,   182,    -1,   184,
      -1,   186,   187,    -1,    -1,    -1,    -1,    95,    15,    16,
      17,    18,    19,    20,    21,    -1,    -1,    24,    25,    -1,
      -1,   109,    -1,   111,   112,   113,   114,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   122,    -1,   124,   125,    -1,    -1,
      -1,    -1,    -1,    50,    51,    52,    53,    54,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,
     168,   169,   170,   171,   172,   173,   174,   175,    14,    15,
      16,    17,    18,    -1,   182,     1,    -1,    -1,    -1,    -1,
     188,    -1,   190,   191,   192,    -1,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    57,    58,    59,    60,    61,    62,    -1,    -1,    -1,
      66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,
      76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    71,    -1,    73,    74,    95,
      -1,    77,   179,   180,    -1,   182,    -1,   184,    -1,   186,
     187,    -1,    -1,   109,    -1,   111,   112,   113,   114,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   122,    -1,   124,   125,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   123,    -1,    -1,
      -1,   127,   128,   129,   130,   131,   132,   133,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,
      -1,    -1,   168,   169,   170,   171,   172,   173,   174,   175,
      14,    15,    16,    17,    18,    -1,   182,    -1,    -1,    -1,
      -1,   167,   188,    -1,   190,   191,   192,    -1,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    -1,    -1,    -1,    -1,
      -1,    -1,    56,    57,    58,    59,    60,    61,    62,    -1,
      -1,    -1,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    75,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    95,    -1,    -1,    -1,    -1,    70,    71,     1,    73,
      74,    -1,    -1,    77,    -1,   109,    -1,   111,   112,   113,
     114,    14,    15,    16,    17,    18,    -1,    -1,   122,    -1,
     124,   125,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    -1,    -1,   123,
      -1,    -1,    -1,   127,   128,   129,   130,   131,   132,   133,
      -1,    -1,    -1,    -1,   168,   169,   170,   171,   172,   173,
     174,   175,    75,    76,    -1,    -1,    -1,    -1,   182,    -1,
      -1,    -1,    -1,    -1,   188,    -1,   190,   191,   192,    -1,
      -1,    -1,    95,   167,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   109,    -1,   111,   112,
     113,   114,     1,    -1,    -1,   118,   119,   191,    -1,   122,
      -1,   124,   125,    -1,    -1,    14,    15,    16,    17,    18,
      -1,    -1,    -1,    -1,    69,    70,    71,    -1,    73,    74,
      -1,    -1,    77,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    -1,   165,    -1,    -1,   168,   169,   170,   171,   172,
     173,   174,   175,    -1,    -1,    -1,    -1,    -1,    -1,   182,
      -1,    -1,    -1,    -1,    -1,    -1,    75,    76,   123,   192,
      -1,    -1,   127,   128,   129,   130,   131,   132,   133,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    95,    -1,    -1,    -1,
      -1,    70,    71,     1,    73,    74,    -1,    -1,    77,    -1,
     109,    -1,   111,   112,   113,   114,    14,    15,    16,    17,
      18,    -1,   167,   122,   123,   124,   125,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    -1,    -1,   123,    -1,    -1,    -1,   127,   128,
     129,   130,   131,   132,   133,    -1,    -1,    -1,    -1,   168,
     169,   170,   171,   172,   173,   174,   175,    75,    76,    -1,
      -1,    -1,    -1,   182,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   192,    -1,    -1,    -1,    95,   167,    -1,
      -1,    -1,    -1,    -1,     1,    70,    71,    72,    73,    74,
      -1,   109,    77,   111,   112,   113,   114,    14,    15,    16,
      17,    18,   191,    -1,   122,    -1,   124,   125,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    -1,    -1,    -1,    -1,    -1,   123,    -1,
      -1,    -1,   127,   128,   129,   130,   131,   132,   133,    -1,
     168,   169,   170,   171,   172,   173,   174,   175,    75,    76,
      -1,    -1,    -1,    -1,   182,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   192,    -1,    -1,    -1,    95,    -1,
      -1,    -1,   167,    -1,    -1,     1,    70,    71,    72,    73,
      74,    -1,   109,    77,   111,   112,   113,   114,    14,    15,
      16,    17,    18,    -1,    -1,   122,    -1,   124,   125,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    -1,    -1,    -1,    -1,    -1,   123,
      -1,    -1,    -1,   127,   128,   129,   130,   131,   132,   133,
      -1,   168,   169,   170,   171,   172,   173,   174,   175,    75,
      76,    -1,    -1,    -1,    -1,   182,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   192,    -1,    -1,    -1,    95,
      -1,    -1,    -1,   167,    70,    71,     1,    73,    74,    -1,
      -1,    77,    -1,   109,    -1,   111,   112,   113,   114,    14,
      15,    16,    17,    18,    -1,    -1,   122,    -1,   124,   125,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    -1,    -1,   123,    -1,    -1,
      -1,   127,   128,   129,   130,   131,   132,   133,    -1,    -1,
      -1,    -1,   168,   169,   170,   171,   172,   173,   174,   175,
      75,    76,    -1,    -1,    -1,    -1,   182,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   192,    -1,    -1,    -1,
      95,   167,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,
      -1,    -1,    -1,    -1,   109,    -1,   111,   112,   113,   114,
      14,    15,    16,    17,    18,    -1,    -1,   122,    -1,   124,
     125,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   168,   169,   170,   171,   172,   173,   174,
     175,    75,    76,    -1,    -1,    -1,    -1,   182,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   192,    -1,    -1,
      -1,    95,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,
      -1,    -1,    -1,    -1,    -1,   109,    -1,   111,   112,   113,
     114,    14,    15,    16,    17,    18,    -1,    -1,   122,    -1,
     124,   125,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   168,   169,   170,   171,   172,   173,
     174,   175,    75,    76,    -1,    -1,    -1,    -1,   182,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   192,    -1,
      -1,    -1,    95,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      70,    71,    -1,    73,    74,    -1,   109,    77,   111,   112,
     113,   114,    14,    15,    16,    17,    18,    -1,    -1,   122,
      -1,   124,   125,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    -1,    -1,
      -1,    -1,    -1,   123,    -1,    -1,    -1,   127,   128,   129,
     130,   131,   132,   133,    -1,   168,   169,   170,   171,   172,
     173,   174,   175,    75,    76,    -1,    -1,    -1,    -1,   182,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   192,
      -1,    -1,    -1,    95,    -1,    -1,    -1,   167,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   109,    -1,   111,
     112,   113,   114,   183,    -1,    -1,    -1,    -1,    -1,    -1,
     122,    -1,   124,   125,     0,     1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   168,   169,   170,   171,
     172,   173,   174,   175,    50,    51,    52,    53,    54,    55,
     182,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     192,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,
      52,    53,    54,    55,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    -1,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    50,    51,    52,    53,    54,    55,    -1,    -1,    -1,
     176,    -1,   178,   179,   180,    -1,   182,    -1,   184,    -1,
     186,   187,   188,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    -1,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    -1,    -1,   176,    -1,   178,   179,   180,    -1,
     182,    -1,   184,    -1,   186,   187,    -1,    -1,    -1,   191,
      50,    51,    52,    53,    54,    55,    92,    93,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   109,    -1,   111,   112,   113,   114,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   122,   176,    -1,   178,
     179,   180,    -1,   182,    -1,   184,    -1,   186,   187,    -1,
       0,     1,   191,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    -1,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    -1,    -1,    -1,   171,   172,   173,   174,   175,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      50,    51,    52,    53,    54,    55,   192,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   176,    -1,   178,   179,
     180,    -1,   182,    -1,   184,    -1,   186,   187,    -1,    -1,
       1,   191,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    -1,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,
      51,    52,    53,    54,    55,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    -1,   176,    -1,   178,   179,
     180,    -1,   182,    -1,   184,    -1,   186,   187,    -1,    -1,
      -1,    -1,    50,    51,    52,    53,    54,    55,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    50,    51,    52,    53,    54,
      55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   176,    -1,   178,   179,   180,
      -1,   182,    -1,   184,    -1,   186,   187,   188,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    -1,    -1,    -1,   176,    -1,
     178,   179,   180,    -1,   182,   183,   184,    -1,   186,   187,
      -1,   189,    50,    51,    52,    53,    54,    55,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    -1,    -1,
      -1,   176,    -1,   178,   179,   180,    -1,   182,    -1,   184,
      -1,   186,   187,    -1,   189,    50,    51,    52,    53,    54,
      55,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,
      52,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   176,    -1,
     178,   179,   180,    -1,   182,    -1,   184,    -1,   186,   187,
      -1,   189,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    -1,    -1,
      -1,   176,    -1,   178,   179,   180,    -1,   182,    -1,   184,
      -1,   186,   187,    -1,   189,    50,    51,    52,    53,    54,
      55,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      -1,    -1,    -1,    -1,   176,   177,   178,   179,   180,    -1,
     182,    -1,   184,    -1,   186,   187,   188,    -1,    50,    51,
      52,    53,    54,    55,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    -1,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    50,    51,    52,    53,    54,    55,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   176,    -1,   178,   179,   180,    -1,   182,    -1,   184,
      -1,   186,   187,   188,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    -1,
      -1,    -1,    -1,    -1,   176,    -1,   178,   179,   180,    -1,
     182,    -1,   184,    -1,   186,   187,   188,    50,    51,    52,
      53,    54,    55,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    -1,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    -1,    -1,    -1,    -1,    -1,   176,    -1,   178,
     179,   180,    -1,   182,    -1,   184,    -1,   186,   187,   188,
      50,    51,    52,    53,    54,    55,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    -1,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    50,    51,    52,    53,    54,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   176,    -1,   178,   179,   180,    -1,   182,
      -1,   184,    -1,   186,   187,   188,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      -1,    -1,    -1,   173,    -1,   175,   176,    -1,   178,   179,
     180,    -1,   182,   183,   184,    -1,   186,   187,    50,    51,
      52,    53,    54,    55,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    -1,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    -1,    -1,    -1,   173,    -1,   175,   176,
      -1,   178,   179,   180,    -1,   182,   183,   184,    -1,   186,
     187,    50,    51,    52,    53,    54,    55,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    50,    51,    52,    53,    54,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   173,   174,    -1,   176,    -1,   178,   179,   180,    -1,
     182,    -1,   184,    -1,   186,   187,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,   100,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    -1,    -1,    -1,    -1,    -1,   176,   177,   178,
     179,   180,    -1,   182,    -1,   184,    -1,   186,   187,    -1,
      50,    51,    52,    53,    54,    55,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    -1,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    -1,    -1,    -1,    -1,    -1,
     176,    -1,   178,   179,   180,    -1,   182,    -1,   184,    -1,
     186,   187,    -1,    50,    51,    52,    53,    54,    55,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   176,    -1,   178,   179,
     180,    -1,   182,    -1,   184,   185,   186,   187,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    -1,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,   176,
      -1,   178,   179,   180,    -1,   182,   183,   184,    -1,   186,
     187,    50,    51,    52,    53,    54,    55,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    -1,    -1,    -1,    -1,
      -1,    -1,   176,   177,   178,   179,   180,    -1,   182,    -1,
     184,    -1,   186,   187,    50,    51,    52,    53,    54,    55,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,
      53,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   176,    -1,   178,
     179,   180,    -1,   182,    -1,   184,   185,   186,   187,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,
     176,    -1,   178,   179,   180,    -1,   182,   183,   184,    -1,
     186,   187,    50,    51,    52,    53,    54,    55,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    -1,    -1,
      -1,    -1,    -1,   176,    -1,   178,   179,   180,    -1,   182,
      -1,   184,   185,   186,   187,    50,    51,    52,    53,    54,
      55,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,
      52,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   176,    -1,
     178,   179,   180,    -1,   182,    -1,   184,   185,   186,   187,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    -1,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    -1,    -1,    -1,    -1,    -1,
      -1,   176,    -1,   178,   179,   180,    -1,   182,    -1,   184,
     185,   186,   187,    50,    51,    52,    53,    54,    55,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    -1,    -1,
      -1,    -1,    -1,    -1,   176,    -1,   178,   179,   180,    -1,
     182,   183,   184,    -1,   186,   187,    50,    51,    52,    53,
      54,    55,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    -1,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,
      51,    52,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   176,
      -1,   178,   179,   180,    -1,   182,    -1,   184,   185,   186,
     187,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    -1,    -1,    -1,    -1,
      -1,    -1,   176,    -1,   178,   179,   180,    -1,   182,    -1,
     184,   185,   186,   187,    50,    51,    52,    53,    54,    55,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    -1,
      -1,    -1,    -1,    -1,    -1,   176,    -1,   178,   179,   180,
      -1,   182,    -1,   184,   185,   186,   187,    50,    51,    52,
      53,    54,    55,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    -1,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      50,    51,    52,    53,    54,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     176,    -1,   178,   179,   180,    -1,   182,    -1,   184,   185,
     186,   187,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    -1,    -1,
      -1,    -1,    -1,   176,    -1,   178,   179,   180,    -1,   182,
      -1,   184,   185,   186,   187,    50,    51,    52,    53,    54,
      55,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      -1,    -1,    -1,    -1,    -1,    -1,   176,    -1,   178,   179,
     180,    -1,   182,   183,   184,    -1,   186,   187,    50,    51,
      52,    53,    54,    55,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    -1,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    50,    51,    52,    53,    54,    55,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   176,    -1,   178,   179,   180,    -1,   182,   183,   184,
      -1,   186,   187,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    -1,    -1,
      -1,   173,    -1,    -1,   176,    -1,   178,   179,   180,    -1,
     182,    -1,   184,    -1,   186,   187,    50,    51,    52,    53,
      54,    55,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    -1,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    -1,    -1,    -1,    -1,    -1,    -1,   176,    -1,   178,
     179,   180,    -1,   182,   183,   184,    -1,   186,   187,    50,
      51,    52,    53,    54,    55,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    50,    51,    52,    53,    54,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   176,    -1,   178,   179,   180,    -1,   182,   183,
     184,    -1,   186,   187,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    -1,
      -1,    -1,    -1,    -1,    -1,   176,    -1,   178,   179,   180,
      -1,   182,   183,   184,    -1,   186,   187,    50,    51,    52,
      53,    54,    55,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    -1,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    -1,    -1,    -1,    -1,    -1,    -1,   176,    -1,
     178,   179,   180,    -1,   182,   183,   184,    -1,   186,   187,
      50,    51,    52,    53,    54,    55,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    -1,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    50,    51,    52,    53,    54,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   176,    -1,   178,   179,   180,    -1,   182,
     183,   184,    -1,   186,   187,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      -1,    -1,    -1,    -1,    -1,    -1,   176,    -1,   178,   179,
     180,    -1,   182,   183,   184,    -1,   186,   187,    50,    51,
      52,    53,    54,    55,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    -1,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,   176,
      -1,   178,   179,   180,    -1,   182,   183,   184,    -1,   186,
     187,    50,    51,    52,    53,    54,    55,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    50,    51,    52,    53,    54,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   176,    -1,   178,   179,   180,    -1,
     182,   183,   184,    -1,   186,   187,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    92,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    -1,   176,    -1,   178,
     179,   180,    -1,   182,   183,   184,    -1,   186,   187,    -1,
      -1,    -1,    -1,    -1,    50,    51,    52,    53,    54,    55,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    -1,
     176,    -1,   178,   179,   180,    -1,   182,    -1,   184,    -1,
     186,   187,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,
      53,    54,    55,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    -1,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      50,    51,    52,    53,    54,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     176,   177,   178,   179,   180,    -1,   182,    -1,   184,    -1,
     186,   187,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    92,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    -1,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    -1,   176,    -1,   178,   179,   180,    -1,   182,
      -1,   184,   185,   186,   187,    -1,    -1,    -1,    -1,    -1,
      50,    51,    52,    53,    54,    55,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    -1,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    -1,   176,    -1,   178,   179,
     180,    -1,   182,    -1,   184,    -1,   186,   187,    -1,    -1,
      -1,    -1,    -1,    50,    51,    52,    53,    54,    55,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   176,    -1,   178,   179,
     180,    -1,   182,   183,   184,    -1,   186,   187,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   176,
      -1,   178,   179,   180,    -1,   182,    -1,   184,    -1,   186,
     187,    14,    15,    16,    17,    18,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    -1,    -1,    -1,
      -1,    -1,   176,    -1,   178,   179,   180,    -1,   182,    -1,
     184,    -1,   186,   187,   109,    -1,   111,   112,   113,   114,
      -1,    -1,    75,    76,    -1,    -1,    -1,   122,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    95,    96,    97,    98,    99,    -1,    -1,    -1,
      -1,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,    -1,   116,   117,    -1,    -1,    -1,    -1,   122,
      -1,   124,   125,    -1,    -1,    -1,   171,   172,   173,   174,
     175,    -1,    -1,   178,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   192,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   168,   169,   170,   171,   172,
     173,   174,   175,    14,    15,    16,    17,    18,    -1,   182,
      33,    34,    -1,    -1,    -1,    -1,    -1,   190,    -1,   192,
      -1,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    -1,
      -1,    -1,    65,    -1,    -1,    56,    57,    58,    59,    60,
      61,    62,    -1,    -1,    -1,    66,    67,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    75,    76,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    95,    -1,   109,    -1,   111,   112,
     113,   114,    -1,    -1,    -1,    -1,    -1,    -1,   109,   122,
     111,   112,   113,   114,    14,    15,    16,    17,    18,    -1,
      -1,   122,    -1,   124,   125,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   171,   172,
     173,   174,   175,    -1,    -1,    -1,    -1,   168,   169,   170,
     171,   172,   173,   174,   175,    75,    76,    -1,    -1,   192,
      -1,   182,    -1,    -1,    -1,    -1,    -1,   188,    -1,   190,
      -1,   192,    -1,    -1,    -1,    95,    96,    97,    98,    99,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   109,
      -1,   111,   112,   113,   114,    14,    15,    16,    17,    18,
      -1,    -1,   122,    -1,   124,   125,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   168,   169,
     170,   171,   172,   173,   174,   175,    75,    76,    -1,    -1,
      -1,    -1,   182,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   192,    -1,    -1,    -1,    95,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     109,    -1,   111,   112,   113,   114,    14,    15,    16,    17,
      18,   120,    -1,   122,    -1,   124,   125,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   168,
     169,   170,   171,   172,   173,   174,   175,    75,    76,    -1,
      -1,    -1,    -1,   182,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   192,    -1,    -1,    -1,    95,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   109,    -1,   111,   112,   113,   114,    -1,    -1,    -1,
     118,   119,    -1,    -1,   122,    -1,   124,   125,    14,    15,
      16,    17,    18,    -1,    -1,    33,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    -1,    -1,    -1,    -1,    -1,    -1,
     168,   169,   170,   171,   172,   173,   174,   175,    -1,    -1,
      78,    -1,    -1,    -1,   182,    -1,    -1,    -1,    -1,    75,
      76,    -1,    -1,    -1,   192,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,
      -1,   109,    -1,   111,   112,   113,   114,    -1,    -1,    -1,
      -1,    -1,    -1,   109,   122,   111,   112,   113,   114,    14,
      15,    16,    17,    18,    -1,    -1,   122,   123,   124,   125,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   171,   172,   173,   174,   175,    -1,    -1,
      -1,    -1,   168,   169,   170,   171,   172,   173,   174,   175,
      75,    76,    -1,    -1,   192,    -1,   182,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   190,    -1,   192,    -1,    -1,    -1,
      95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   107,    -1,   109,    -1,   111,   112,   113,   114,
      14,    15,    16,    17,    18,    -1,    -1,   122,    -1,   124,
     125,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   168,   169,   170,   171,   172,   173,   174,
     175,    75,    76,    -1,    -1,    -1,    -1,   182,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   192,    -1,    -1,
      -1,    95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   109,    -1,   111,   112,   113,
     114,    14,    15,    16,    17,    18,    -1,    -1,   122,    -1,
     124,   125,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   168,   169,   170,   171,   172,   173,
     174,   175,    75,    76,    -1,    -1,    -1,    -1,   182,    -1,
     184,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   192,    -1,
      -1,    -1,    95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   109,    -1,   111,   112,
     113,   114,    14,    15,    16,    17,    18,    -1,    -1,   122,
      -1,   124,   125,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   168,   169,   170,   171,   172,
     173,   174,   175,    75,    76,    -1,    -1,    -1,    -1,   182,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   191,   192,
      -1,    -1,    -1,    95,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   109,    -1,   111,
     112,   113,   114,    14,    15,    16,    17,    18,    -1,    -1,
     122,    -1,   124,   125,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   168,   169,   170,   171,
     172,   173,   174,   175,    75,    76,    -1,    -1,    -1,    -1,
     182,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   190,    -1,
     192,    -1,    -1,    -1,    95,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   109,    -1,
     111,   112,   113,   114,    14,    15,    16,    17,    18,    -1,
      -1,   122,    -1,   124,   125,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      -1,    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   168,   169,   170,
     171,   172,   173,   174,   175,    75,    76,    -1,    -1,    -1,
      -1,   182,    -1,    -1,    -1,    -1,    -1,   188,    -1,    -1,
      -1,   192,    -1,    -1,    -1,    95,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   109,
      -1,   111,   112,   113,   114,    14,    15,    16,    17,    18,
      -1,    -1,   122,    -1,   124,   125,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   168,   169,
     170,   171,   172,   173,   174,   175,    75,    76,    -1,    -1,
      -1,    -1,   182,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   192,    -1,    -1,    -1,    95,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     109,    -1,   111,   112,   113,   114,    14,    15,    16,    17,
      18,    -1,    -1,   122,    -1,   124,   125,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   168,
     169,   170,   171,   172,   173,   174,   175,    75,    76,    -1,
      -1,    -1,    -1,   182,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   192,    -1,    -1,    -1,    95,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    -1,
      -1,   109,    -1,   111,   112,   113,   114,    14,    15,    16,
      17,    18,    -1,    -1,   122,    -1,   124,   125,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,
     168,   169,   170,   171,   172,   173,   174,   175,    75,    76,
      -1,    -1,    -1,   109,   182,   111,   112,   113,   114,    -1,
      -1,    -1,    -1,    -1,   192,    -1,   122,    -1,    95,    69,
      70,    71,    -1,    73,    74,    -1,    -1,    77,    78,    79,
      -1,    -1,   109,    -1,   111,   112,   113,   114,    -1,    89,
      90,    -1,    -1,    -1,    -1,   122,    -1,   124,   125,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   109,
      -1,   111,   112,   113,   114,   171,   172,   173,   174,   175,
      33,    34,   122,   123,    -1,    -1,   182,   127,   128,   129,
     130,   131,   132,   133,    -1,    -1,   192,    -1,    -1,    -1,
      -1,   168,   169,   170,   171,   172,   173,   174,   175,    33,
      34,    -1,    -1,    -1,    -1,   182,    -1,    70,    71,    -1,
      73,    74,    -1,    -1,    77,   192,   166,   167,    -1,    -1,
      -1,   171,   172,   173,   174,   175,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    69,    70,    71,    -1,    73,
      74,    -1,   192,    77,    -1,    79,   109,    -1,   111,   112,
     113,   114,    -1,    -1,    -1,    89,    90,    -1,    -1,   122,
     123,    -1,    -1,    -1,   127,   128,   129,   130,   131,   132,
     133,    33,    34,    -1,    -1,   109,    -1,   111,   112,   113,
     114,    -1,    -1,    33,    34,    -1,    -1,    -1,   122,   123,
      -1,    -1,    -1,   127,   128,   129,   130,   131,   132,   133,
      -1,    -1,    -1,    -1,   167,    -1,    33,    34,   171,   172,
     173,   174,   175,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   192,
      -1,    -1,   166,   167,    -1,    -1,    -1,   171,   172,   173,
     174,   175,    -1,    -1,    -1,    -1,    -1,   109,    -1,   111,
     112,   113,   114,    -1,    -1,    -1,    -1,    -1,   192,   109,
     122,   111,   112,   113,   114,    92,    -1,    -1,    -1,    -1,
      -1,    -1,   122,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   109,    -1,   111,   112,   113,   114,    -1,   109,
      -1,   111,   112,   113,   114,   122,    -1,    -1,    -1,    -1,
      -1,    -1,   122,    -1,    -1,    -1,    -1,    -1,    -1,   171,
     172,   173,   174,   175,    -1,    -1,    -1,    -1,    -1,    -1,
     182,   171,   172,   173,   174,   175,    -1,    -1,    -1,    -1,
     192,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   191,   192,    -1,   171,   172,   173,   174,   175,    -1,
      -1,   171,   172,   173,   174,   175,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   192,    -1,    -1,    -1,    -1,
      -1,    -1,   192
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     196,     1,   197,   226,   226,   265,   226,   197,    70,    71,
      73,    74,    77,   123,   127,   128,   129,   130,   131,   132,
     133,   167,   235,   236,   253,   261,    14,    15,    16,    17,
      18,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    75,
      76,    95,   109,   111,   112,   113,   114,   122,   124,   125,
     168,   169,   170,   171,   172,   173,   174,   175,   182,   192,
     255,   315,   322,   329,   331,   332,   333,   375,   315,   286,
     315,   314,   315,   123,   254,   255,   283,   294,   315,   335,
     336,   336,   357,     1,   198,    72,   253,   349,   350,   353,
     315,   361,   315,   369,   314,   370,   371,   315,   314,    79,
     262,   315,   201,   255,   287,   315,   314,   315,     0,   188,
      69,    78,    89,    90,   129,   166,   199,   204,   205,   209,
     227,   229,   230,   231,   237,   249,   253,   255,   262,   231,
     237,   249,   190,    74,   184,   184,   130,   189,   178,   255,
      70,   123,   127,   128,   129,   132,   133,   315,   315,   126,
     182,   182,   182,   182,   255,   182,   182,     1,   118,   119,
     165,   315,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      50,    51,    52,    53,    54,    55,   176,   178,   179,   180,
     182,   184,   186,   187,   330,   315,   182,   182,     1,    14,
     176,   189,   177,   189,   177,    72,    79,   198,   237,   253,
     337,   342,   337,   188,   199,   354,   351,   188,   352,   189,
       1,   189,   189,    33,    34,    96,    97,    98,    99,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     116,   117,   171,   190,   192,   315,   373,   374,   392,   395,
     396,   397,   254,   182,     1,     1,   253,     1,   213,   255,
     190,   190,    68,   255,   210,   238,   239,   254,   182,   203,
       1,   253,   256,   257,   315,   315,   236,   255,   245,   246,
     190,   184,   184,   254,   254,   254,   254,   323,   183,   255,
     183,   184,   184,   315,   173,   175,   183,   315,   315,   315,
     315,   315,   315,   315,   315,   315,   315,   315,   315,   315,
     315,   318,   315,   315,   315,   315,   315,   315,   315,   315,
     315,   315,   316,   317,     1,   315,   255,   315,   315,   315,
      14,   176,   315,   253,   254,   315,     1,   338,     1,   254,
     204,   254,   255,   255,   350,   353,   189,   355,   189,   315,
     315,   177,   190,   177,   190,   107,   315,   315,   315,   182,
     315,   315,   315,   177,   177,   184,    19,   177,   124,   177,
     177,   177,   177,   315,   184,   315,   184,   315,   393,   394,
     184,   100,   107,   394,   394,   193,   182,   234,   202,   188,
     250,   251,   254,   188,    50,   188,   189,   214,   314,   314,
       1,    65,   206,   207,   208,   255,   234,    91,    94,   215,
     188,   189,   234,   240,   183,   235,     3,   191,   254,   258,
     259,   191,   257,   189,   185,   245,   184,   247,     1,   256,
     315,   315,   177,   177,   177,   177,   182,   183,   124,   124,
     183,   184,   184,   315,   177,   315,   334,     1,   185,   185,
     183,   189,   177,   188,   255,   339,   340,   190,     1,   182,
     190,   348,   245,   245,   255,   255,   315,   315,   177,   315,
     255,    96,   373,    51,   120,   315,   376,   177,   182,   182,
     255,   390,   184,   182,   255,   379,   380,   379,   379,   379,
     376,   315,   191,   189,   376,   315,   177,     1,   183,   235,
     190,   334,   188,   189,   252,   255,   255,   191,   191,   188,
      50,   188,   189,   184,   228,   190,   255,   115,   217,   239,
     190,   245,   183,   255,   260,   188,   189,   315,     1,   253,
     315,   191,   191,   189,   185,   253,   255,   253,   255,   255,
     253,   255,   334,   324,   189,   189,   124,   124,   315,   183,
     189,   183,   315,   253,   341,   188,   189,   346,   190,     1,
     183,   349,   347,     1,   190,   245,   245,   191,   191,   373,
      26,    28,   372,   315,    51,    51,   185,   373,   315,   255,
     391,    54,   194,   389,   376,   379,   380,   381,   382,   383,
     384,   385,   386,   387,    51,    54,   185,   173,   174,   315,
     188,   373,   183,   183,   263,   183,   251,   245,   207,   207,
     315,   188,   216,   203,   190,   232,     3,   241,   182,   245,
     259,   185,   185,   185,   185,   315,   183,   325,   183,   326,
     328,   183,   327,   183,   124,   124,   189,   189,   315,   183,
     245,   340,   356,   357,   345,   183,   183,   356,   190,   343,
     177,   177,    98,   315,   315,   177,   183,   189,    27,   183,
     390,   190,    51,   185,    26,    27,   177,   194,   388,    17,
     388,   388,   388,   388,    17,    27,    26,   379,   379,   182,
     315,   315,   315,   264,   265,   185,   191,   315,   190,   218,
     297,   190,   242,   315,   200,   247,   248,   247,   185,   320,
     183,   321,   183,   183,   319,   183,   185,   185,   124,   124,
     242,   191,     1,    80,   358,   356,   191,   344,   356,   315,
     373,   177,   315,   255,   389,   393,   390,   190,   379,   379,
     373,   379,   183,   380,   183,   183,   183,   183,   380,   379,
     379,   118,   119,   315,   378,   185,   185,   185,   191,     1,
      80,   266,   177,   188,   208,   211,   212,   191,   255,   237,
     249,   298,   242,   243,   244,   254,   255,   334,   247,   315,
     182,   315,   182,   315,   315,   315,   315,   315,   185,   185,
     188,   255,   359,   360,   289,   191,   356,   191,   183,   373,
     183,   191,   394,   173,   315,   182,   188,   255,   267,   268,
      81,   269,   289,   315,     1,    14,   176,   189,   191,   219,
       1,    56,    57,    58,    59,    60,    61,    62,    66,    67,
     188,   190,   191,   233,   295,   299,   315,   189,   191,   177,
     183,   315,   315,   183,   183,   315,   315,   190,   188,   189,
       1,    73,    82,    83,   272,   290,   291,   191,   177,   191,
     315,   183,   254,   184,   190,   188,   189,   255,   270,   271,
     289,   272,   188,    14,   176,   212,   182,   220,   188,   182,
     182,   303,   188,   188,   182,   182,   188,   315,   315,   296,
     188,   244,   242,   188,   183,   183,   183,   183,   361,   360,
     188,     1,   255,   293,     1,   255,   292,   255,    84,   362,
     373,   177,   183,    51,    54,   377,   177,   294,     1,   315,
     268,   188,   189,   272,    84,   273,   221,   254,   177,     1,
     254,   314,     1,   302,   299,   314,   304,   188,   188,   297,
     191,   188,   188,   189,   188,   188,   189,   188,     1,   255,
     363,   364,   124,   315,   117,   125,   315,   185,   191,   191,
     271,   273,     1,   255,   274,   275,   183,   189,   177,    56,
     222,   223,   315,   183,   177,   188,   183,   314,    57,   183,
     314,   298,   255,   255,   188,    92,   188,   189,   177,   184,
     183,   188,    92,    93,   188,   189,   254,   253,   224,   188,
     189,    92,   299,   253,   314,   299,   183,   182,   305,   183,
       1,   191,   255,    92,   364,   366,   315,   376,   255,   255,
      92,    93,   275,   279,   177,   182,   223,   315,   183,   188,
     299,   314,   190,   299,   190,   255,   185,   190,   278,   190,
     255,   255,   253,   225,   254,   301,   314,   183,    64,    65,
     308,   309,    63,   306,   365,   190,   182,   276,   184,   277,
     190,   190,   183,   189,   177,   299,   183,   188,     1,   315,
       1,   177,   191,   309,   307,    86,   368,   367,   378,    85,
     282,   315,   282,   280,   281,   315,   254,   253,   300,   177,
     177,   177,   312,   299,   369,    87,   285,   368,   315,   283,
      86,   284,   185,   284,   282,   282,    92,   177,   299,   311,
     310,   313,   298,     1,   188,     1,   286,    88,   288,   285,
     183,   188,     1,   315,   285,   285,   284,   284,   315,   253,
     298,   298,   298,   188,   188,   188,     1,   314,   191,   288,
     188,     1,   188,   288,   288,   285,   285,   188,   188,   191,
     188,   191,   191,   288,   288,   191,   191
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   195,   196,   196,   196,   196,   196,   196,   196,   196,
     196,   196,   196,   196,   196,   196,   196,   196,   196,   196,
     196,   196,   196,   196,   196,   196,   196,   196,   196,   196,
     196,   197,   198,   198,   198,   200,   199,   201,   202,   201,
     203,   203,   203,   204,   205,   205,   206,   206,   206,   207,
     207,   208,   208,   209,   209,   210,   210,   211,   211,   212,
     212,   212,   212,   212,   213,   213,   213,   214,   215,   215,
     216,   216,   216,   217,   217,   218,   219,   218,   220,   220,
     221,   221,   222,   222,   223,   224,   223,   225,   225,   226,
     226,   226,   226,   226,   226,   226,   226,   226,   226,   226,
     228,   227,   229,   230,   232,   231,   233,   233,   234,   234,
     234,   235,   235,   236,   236,   237,   238,   238,   240,   239,
     241,   241,   242,   242,   243,   243,   244,   244,   246,   245,
     247,   247,   248,   247,   247,   249,   249,   250,   250,   252,
     251,   253,   253,   253,   253,   253,   253,   253,   253,   253,
     253,   253,   253,   253,   253,   253,   253,   253,   253,   253,
     253,   253,   254,   254,   255,   255,   255,   255,   255,   255,
     255,   255,   255,   255,   255,   255,   255,   255,   256,   256,
     257,   258,   258,   260,   259,   261,   261,   261,   261,   261,
     263,   262,   264,   264,   264,   265,   265,   265,   265,   266,
     266,   267,   267,   268,   268,   268,   268,   269,   270,   270,
     271,   272,   272,   273,   273,   273,   274,   274,   276,   275,
     277,   275,   278,   275,   280,   279,   281,   279,   279,   282,
     282,   283,   283,   284,   284,   284,   284,   285,   285,   285,
     286,   286,   286,   286,   286,   287,   287,   288,   288,   288,
     289,   289,   289,   290,   290,   291,   291,   292,   292,   293,
     293,   294,   294,   296,   295,   297,   297,   297,   298,   298,
     298,   299,   299,   299,   300,   299,   301,   299,   299,   302,
     299,   299,   303,   299,   304,   299,   299,   299,   305,   299,
     299,   299,   299,   306,   307,   306,   308,   308,   310,   309,
     311,   309,   312,   309,   313,   309,   314,   314,   315,   315,
     315,   315,   315,   315,   315,   316,   315,   317,   315,   315,
     315,   315,   315,   315,   315,   315,   315,   315,   315,   315,
     315,   315,   315,   315,   315,   315,   315,   315,   315,   315,
     315,   315,   315,   315,   315,   315,   315,   315,   315,   315,
     315,   318,   315,   315,   315,   315,   315,   315,   319,   315,
     320,   315,   321,   315,   315,   315,   315,   323,   322,   322,
     324,   322,   325,   322,   326,   322,   327,   322,   328,   322,
     329,   330,   330,   330,   330,   330,   330,   330,   330,   330,
     330,   330,   331,   331,   331,   331,   332,   332,   332,   332,
     332,   332,   332,   332,   332,   332,   333,   334,   334,   334,
     335,   336,   336,   336,   337,   338,   337,   337,   339,   339,
     341,   340,   343,   342,   344,   342,   345,   342,   346,   342,
     347,   342,   348,   348,   348,   349,   349,   349,   349,   351,
     350,   352,   350,   354,   353,   355,   353,   356,   357,   357,
     358,   358,   359,   359,   360,   360,   361,   361,   361,   362,
     362,   362,   363,   363,   365,   364,   367,   366,   366,   368,
     368,   368,   369,   369,   370,   371,   371,   372,   372,   373,
     373,   373,   373,   373,   373,   373,   373,   374,   374,   374,
     374,   374,   374,   374,   374,   374,   374,   374,   374,   374,
     374,   374,   374,   374,   374,   374,   374,   374,   374,   374,
     374,   374,   374,   374,   374,   375,   375,   375,   375,   375,
     376,   376,   376,   377,   377,   378,   378,   379,   379,   379,
     379,   379,   379,   380,   381,   382,   383,   384,   385,   385,
     386,   386,   387,   387,   388,   388,   389,   389,   390,   390,
     391,   391,   392,   393,   393,   394,   394,   395,   395,   396,
     396,   397,   397,   397,   397
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     0,     2,     2,     0,     9,     1,     0,     5,
       0,     2,     3,     4,     4,     4,     1,     3,     3,     1,
       1,     1,     4,     3,     3,     0,     7,     1,     3,     1,
       2,     3,     2,     3,     1,     3,     3,     1,     0,     4,
       0,     5,     3,     0,     4,     0,     0,     7,     0,     3,
       3,     5,     1,     3,     3,     0,     8,     3,     5,     0,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       0,     5,     4,     4,     0,     8,     1,     1,     2,     3,
       3,     1,     3,     4,     3,     3,     1,     3,     0,     4,
       0,     2,     1,     3,     1,     3,     3,     1,     0,     2,
       0,     4,     0,     5,     4,     4,     3,     1,     3,     0,
       3,     1,     2,     4,     5,     4,     5,     1,     2,     1,
       2,     1,     2,     6,     7,     1,     2,     1,     2,     1,
       4,     5,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       3,     1,     3,     0,     3,     1,     1,     2,     1,     1,
       0,     7,     5,     6,     0,     0,     2,     2,     2,     3,
       2,     1,     3,     1,     4,     4,     4,     3,     1,     3,
       1,     3,     2,     0,     3,     3,     1,     3,     0,    10,
       0,    10,     0,     7,     0,     9,     0,     9,     1,     0,
       3,     3,     5,     0,     3,     4,     3,     0,     3,     3,
       1,     2,     3,     2,     3,     1,     2,     0,     3,     3,
       0,     2,     2,     3,     3,     3,     3,     1,     3,     1,
       3,     1,     3,     0,     5,     0,     2,     2,     0,     2,
       3,     1,     1,     2,     0,    10,     0,     8,     5,     0,
       6,     5,     0,     8,     0,     7,     2,     2,     0,     8,
       3,     2,     3,     0,     0,     3,     1,     2,     0,     5,
       0,     5,     0,     4,     0,     5,     1,     3,     1,     1,
       1,     1,     4,     6,     1,     0,     5,     0,     5,     4,
       4,     3,     3,     2,     2,     2,     2,     2,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     5,     3,     2,
       1,     0,     4,     3,     3,     3,     3,     3,     0,     8,
       0,     8,     0,     8,     1,     1,     1,     0,     6,     3,
       0,     5,     0,    10,     0,    10,     0,     8,     0,     8,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     1,     3,
       3,     0,     2,     2,     1,     0,     4,     3,     1,     3,
       0,     4,     0,     7,     0,     8,     0,     7,     0,     6,
       0,     6,     2,     3,     3,     1,     1,     3,     3,     0,
       4,     0,     5,     0,     4,     0,     5,     5,     0,     2,
       3,     2,     1,     3,     1,     4,     1,     3,     3,     0,
       3,     3,     1,     3,     0,     9,     0,     8,     1,     0,
       3,     4,     1,     3,     2,     0,     3,     1,     1,     2,
       7,     2,     2,     2,     3,     6,     6,     1,     2,     2,
       2,     3,     6,     9,     7,     4,     4,     4,     6,     6,
       5,     5,     3,     3,     3,     3,    10,     8,     9,    17,
       8,    10,    12,    11,     2,    10,    10,     4,     9,     9,
       2,     3,     3,     1,     1,     1,     1,     1,     4,     4,
       4,     4,     4,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     0,     2,     0,     4,     1,     3,
       1,     3,     3,     0,     1,     1,     3,     2,     5,     2,
       5,     0,     1,     2,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
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


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
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
  unsigned long int yylno = yyrline[yyrule];
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
                       &(yyvsp[(yyi + 1) - (yynrhs)])
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
            /* Fall through.  */
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

  return yystpcpy (yyres, yystr) - yyres;
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
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
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

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
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
| yyreduce -- Do a reduction.  |
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 306 "parser.yy" /* yacc.c:1646  */
    { CALL((yylsp[0]), (yylsp[0]), done()); }
#line 4297 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 307 "parser.yy" /* yacc.c:1646  */
    { }
#line 4303 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 308 "parser.yy" /* yacc.c:1646  */
    { }
#line 4309 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 309 "parser.yy" /* yacc.c:1646  */
    { }
#line 4315 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 310 "parser.yy" /* yacc.c:1646  */
    { }
#line 4321 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 311 "parser.yy" /* yacc.c:1646  */
    { }
#line 4327 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 312 "parser.yy" /* yacc.c:1646  */
    { }
#line 4333 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 313 "parser.yy" /* yacc.c:1646  */
    { }
#line 4339 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 314 "parser.yy" /* yacc.c:1646  */
    { CALL((yylsp[0]), (yylsp[0]), procGuard()); }
#line 4345 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 315 "parser.yy" /* yacc.c:1646  */
    { }
#line 4351 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 316 "parser.yy" /* yacc.c:1646  */
    { CALL((yylsp[0]), (yylsp[0]), procUpdate()); }
#line 4357 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 317 "parser.yy" /* yacc.c:1646  */
    { CALL((yylsp[0]), (yylsp[0]), procProb()); }
#line 4363 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 318 "parser.yy" /* yacc.c:1646  */
    { CALL((yylsp[0]), (yylsp[0]), done()); }
#line 4369 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 319 "parser.yy" /* yacc.c:1646  */
    { }
#line 4375 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 320 "parser.yy" /* yacc.c:1646  */
    { }
#line 4381 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 321 "parser.yy" /* yacc.c:1646  */
    { }
#line 4387 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 322 "parser.yy" /* yacc.c:1646  */
    { }
#line 4393 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 323 "parser.yy" /* yacc.c:1646  */
    { }
#line 4399 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 324 "parser.yy" /* yacc.c:1646  */
    { CALL((yylsp[0]), (yylsp[0]), procGuard()); }
#line 4405 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 325 "parser.yy" /* yacc.c:1646  */
    { CALL((yylsp[0]), (yylsp[0]), procUpdate()); }
#line 4411 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 326 "parser.yy" /* yacc.c:1646  */
    {}
#line 4417 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 327 "parser.yy" /* yacc.c:1646  */
    {}
#line 4423 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 328 "parser.yy" /* yacc.c:1646  */
    {}
#line 4429 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 329 "parser.yy" /* yacc.c:1646  */
    {}
#line 4435 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 330 "parser.yy" /* yacc.c:1646  */
    {}
#line 4441 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 332 "parser.yy" /* yacc.c:1646  */
    { }
#line 4447 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 333 "parser.yy" /* yacc.c:1646  */
    { CALL((yylsp[0]), (yylsp[0]), procLscUpdate()); }
#line 4453 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 334 "parser.yy" /* yacc.c:1646  */
    { CALL((yylsp[0]), (yylsp[0]), procCondition()); }
#line 4459 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 335 "parser.yy" /* yacc.c:1646  */
    { }
#line 4465 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 349 "parser.yy" /* yacc.c:1646  */
    {
          CALL((yylsp[-4]), (yylsp[-1]), instantiationBegin((yyvsp[-4].string), (yyvsp[-3].number), (yyvsp[-1].string)));
        }
#line 4473 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 351 "parser.yy" /* yacc.c:1646  */
    {
          CALL((yylsp[-8]), (yylsp[0]), instantiationEnd((yyvsp[-8].string), (yyvsp[-7].number), (yyvsp[-5].string), (yyvsp[-2].number)));
        }
#line 4481 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 356 "parser.yy" /* yacc.c:1646  */
    {
          CALL((yylsp[0]), (yylsp[0]), instanceName((yyvsp[0].string), false));
        }
#line 4489 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 359 "parser.yy" /* yacc.c:1646  */
    {
          CALL((yylsp[-1]), (yylsp[-1]), instanceNameBegin((yyvsp[-1].string))); 
        }
#line 4497 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 361 "parser.yy" /* yacc.c:1646  */
    {
          CALL((yylsp[-4]), (yylsp[0]), instanceNameEnd((yyvsp[-4].string), (yyvsp[-1].number)));
        }
#line 4505 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 366 "parser.yy" /* yacc.c:1646  */
    { (yyval.number) = 0; }
#line 4511 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 368 "parser.yy" /* yacc.c:1646  */
    {
        	(yyval.number) = 0; 
          }
#line 4519 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 372 "parser.yy" /* yacc.c:1646  */
    {
        	(yyval.number) = (yyvsp[-1].number);
          }
#line 4527 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 384 "parser.yy" /* yacc.c:1646  */
    { CALL((yylsp[0]), (yylsp[0]), beginChanPriority()); }
#line 4533 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 385 "parser.yy" /* yacc.c:1646  */
    { CALL((yylsp[-2]), (yylsp[0]), addChanPriority(',')); }
#line 4539 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 386 "parser.yy" /* yacc.c:1646  */
    { CALL((yylsp[-2]), (yylsp[0]), addChanPriority('<')); }
#line 4545 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 392 "parser.yy" /* yacc.c:1646  */
    { CALL((yylsp[0]), (yylsp[0]), defaultChanPriority()); }
#line 4551 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 396 "parser.yy" /* yacc.c:1646  */
    { CALL((yylsp[0]), (yylsp[0]), exprId((yyvsp[0].string))); }
#line 4557 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 397 "parser.yy" /* yacc.c:1646  */
    { CALL((yylsp[-3]), (yylsp[0]), exprArray()); }
#line 4563 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 401 "parser.yy" /* yacc.c:1646  */
    { CALL((yylsp[-2]), (yylsp[-2]), processListEnd()); }
#line 4569 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 402 "parser.yy" /* yacc.c:1646  */
    { CALL((yylsp[-2]), (yylsp[-2]), processListEnd()); }
#line 4575 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 408 "parser.yy" /* yacc.c:1646  */
    { CALL((yylsp[-6]), (yylsp[0]), declIO((yyvsp[-4].string),(yyvsp[-3].number),(yyvsp[-1].number))); }
#line 4581 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 412 "parser.yy" /* yacc.c:1646  */
    { (yyval.number) = 1; }
#line 4587 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 413 "parser.yy" /* yacc.c:1646  */
    { (yyval.number) = (yyvsp[-2].number) + 1; }
#line 4593 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 420 "parser.yy" /* yacc.c:1646  */
    { 
	    CALL((yylsp[0]), (yylsp[0]), exprSync(SYNC_CSP));
        }
#line 4601 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 423 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-1]), (yylsp[0]), exprSync(SYNC_BANG));
        }
#line 4609 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 426 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[-1]), exprSync(SYNC_BANG));
        }
#line 4617 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 429 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-1]), (yylsp[0]), exprSync(SYNC_QUE));
        }
#line 4625 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 432 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[-1]), exprSync(SYNC_QUE));
        }
#line 4633 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 438 "parser.yy" /* yacc.c:1646  */
    { CALL((yylsp[0]), (yylsp[0]), process((yyvsp[0].string))); }
#line 4639 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 439 "parser.yy" /* yacc.c:1646  */
    { CALL((yylsp[0]), (yylsp[0]), process((yyvsp[0].string))); }
#line 4645 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 440 "parser.yy" /* yacc.c:1646  */
    { CALL((yylsp[0]), (yylsp[0]), process((yyvsp[0].string))); }
#line 4651 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 444 "parser.yy" /* yacc.c:1646  */
    { CALL((yylsp[0]), (yylsp[0]), incProcPriority()); }
#line 4657 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 452 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[-3]), (yylsp[-1]), declProgress(true));
        }
#line 4665 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 455 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[-1]), (yylsp[-1]), declProgress(false));
        }
#line 4673 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 466 "parser.yy" /* yacc.c:1646  */
    { CALL((yylsp[0]), (yylsp[0]), ganttDeclStart((yyvsp[0].string))); }
#line 4679 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 467 "parser.yy" /* yacc.c:1646  */
    { CALL((yylsp[-5]), (yylsp[-1]), ganttDeclEnd());
	}
#line 4686 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 477 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[-2]), (yylsp[0]), ganttDeclSelect((yyvsp[-2].string)));
        }
#line 4694 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 480 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[-2]), (yylsp[0]), ganttDeclSelect((yyvsp[-2].string)));
        }
#line 4702 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 491 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-2]), (yylsp[0]), ganttEntryStart());
	    CALL((yylsp[-2]), (yylsp[0]), ganttEntryEnd());
        }
#line 4711 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 495 "parser.yy" /* yacc.c:1646  */
    { CALL((yylsp[0]), (yylsp[0]), ganttEntryStart()); }
#line 4717 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 496 "parser.yy" /* yacc.c:1646  */
    { CALL((yylsp[-7]), (yylsp[-1]), ganttEntryEnd()); }
#line 4723 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 500 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[-2]), (yylsp[0]), ganttEntrySelect((yyvsp[-2].string)));
        }
#line 4731 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 503 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[-2]), (yylsp[0]), ganttEntrySelect((yyvsp[-2].string)));
        }
#line 4739 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 523 "parser.yy" /* yacc.c:1646  */
    {CALL((yylsp[-2]),(yylsp[0]),declDynamicTemplate((yyvsp[-1].string)));}
#line 4745 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 525 "parser.yy" /* yacc.c:1646  */
    { CALL((yylsp[-1]), (yylsp[-1]), beforeUpdate()); }
#line 4751 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 527 "parser.yy" /* yacc.c:1646  */
    { CALL((yylsp[-1]), (yylsp[-1]), afterUpdate()); }
#line 4757 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 538 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-3]), (yylsp[-2]), declFuncBegin((yyvsp[-2].string)));
        }
#line 4765 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 540 "parser.yy" /* yacc.c:1646  */
    {
          CALL((yylsp[0]), (yylsp[0]), declFuncEnd());
        }
#line 4773 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 553 "parser.yy" /* yacc.c:1646  */
    { (yyval.number) = 1; }
#line 4779 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 554 "parser.yy" /* yacc.c:1646  */
    { (yyval.number) = (yyvsp[-2].number)+1; }
#line 4785 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 558 "parser.yy" /* yacc.c:1646  */
    {
          CALL((yylsp[-3]), (yylsp[0]), declParameter((yyvsp[-1].string), true));
        }
#line 4793 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 561 "parser.yy" /* yacc.c:1646  */
    {
          CALL((yylsp[-2]), (yylsp[0]), declParameter((yyvsp[-1].string), false));
        }
#line 4801 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 567 "parser.yy" /* yacc.c:1646  */
    { 
            CALL((yylsp[-2]), (yylsp[0]), typePop());
        }
#line 4809 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 578 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[0]), (yylsp[0]), typeDuplicate());
        }
#line 4817 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 580 "parser.yy" /* yacc.c:1646  */
    { 
            CALL((yylsp[-3]), (yylsp[0]), declVar((yyvsp[-3].string), (yyvsp[0].flag)));
        }
#line 4825 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 586 "parser.yy" /* yacc.c:1646  */
    { (yyval.flag) = false; }
#line 4831 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 587 "parser.yy" /* yacc.c:1646  */
    { (yyval.flag) = true; }
#line 4837 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 592 "parser.yy" /* yacc.c:1646  */
    {	
          CALL((yylsp[-2]), (yylsp[0]), declInitialiserList((yyvsp[-1].number)));
        }
#line 4845 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 598 "parser.yy" /* yacc.c:1646  */
    { (yyval.number) = 1; }
#line 4851 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 599 "parser.yy" /* yacc.c:1646  */
    { (yyval.number) = (yyvsp[-2].number)+1; }
#line 4857 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 603 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[0]), declFieldInit((yyvsp[-2].string)));
        }
#line 4865 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 606 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[0]), (yylsp[0]), declFieldInit(""));
        }
#line 4873 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 612 "parser.yy" /* yacc.c:1646  */
    { types = 0; }
#line 4879 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 616 "parser.yy" /* yacc.c:1646  */
    { CALL((yylsp[-3]), (yylsp[-1]), typeArrayOfSize(types)); }
#line 4885 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 617 "parser.yy" /* yacc.c:1646  */
    { types++; }
#line 4891 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 617 "parser.yy" /* yacc.c:1646  */
    { CALL((yylsp[-4]), (yylsp[-2]), typeArrayOfType(types--)); }
#line 4897 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 622 "parser.yy" /* yacc.c:1646  */
    {
          CALL((yylsp[-3]), (yylsp[0]), typePop());
        }
#line 4905 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 634 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[0]), (yylsp[0]), typeDuplicate());
        }
#line 4913 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 636 "parser.yy" /* yacc.c:1646  */
    { 
            CALL((yylsp[-2]), (yylsp[0]), declTypeDef((yyvsp[-2].string)));
        }
#line 4921 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 642 "parser.yy" /* yacc.c:1646  */
    { 
            CALL((yylsp[0]), (yylsp[0]), typeName(ParserBuilder::PREFIX_NONE, (yyvsp[0].string)));
        }
#line 4929 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 645 "parser.yy" /* yacc.c:1646  */
    { 
            CALL((yylsp[-1]), (yylsp[0]), typeName((yyvsp[-1].prefix), (yyvsp[0].string)));
        }
#line 4937 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 648 "parser.yy" /* yacc.c:1646  */
    { 
            CALL((yylsp[-3]), (yylsp[0]), typeStruct(ParserBuilder::PREFIX_NONE, (yyvsp[-1].number)));
        }
#line 4945 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 651 "parser.yy" /* yacc.c:1646  */
    { 
            CALL((yylsp[-4]), (yylsp[0]), typeStruct((yyvsp[-4].prefix), (yyvsp[-1].number)));
        }
#line 4953 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 654 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-3]), (yylsp[0]), typeStruct(ParserBuilder::PREFIX_NONE, 0));
        }
#line 4961 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 657 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-4]), (yylsp[0]), typeStruct(ParserBuilder::PREFIX_NONE, 0));
        }
#line 4969 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 660 "parser.yy" /* yacc.c:1646  */
    {
          CALL((yylsp[0]), (yylsp[0]), typeBool(ParserBuilder::PREFIX_NONE));
        }
#line 4977 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 663 "parser.yy" /* yacc.c:1646  */
    {
          CALL((yylsp[-1]), (yylsp[0]), typeBool((yyvsp[-1].prefix)));
        }
#line 4985 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 666 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[0]), (yylsp[0]), typeDouble(ParserBuilder::PREFIX_NONE));
        }
#line 4993 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 669 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-1]), (yylsp[0]), typeDouble((yyvsp[-1].prefix)));
	}
#line 5001 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 672 "parser.yy" /* yacc.c:1646  */
    {
          CALL((yylsp[0]), (yylsp[0]), typeInt(ParserBuilder::PREFIX_NONE));
        }
#line 5009 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 675 "parser.yy" /* yacc.c:1646  */
    {
          CALL((yylsp[-1]), (yylsp[0]), typeInt((yyvsp[-1].prefix)));
        }
#line 5017 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 679 "parser.yy" /* yacc.c:1646  */
    {
          CALL((yylsp[-5]), (yylsp[0]), typeBoundedInt(ParserBuilder::PREFIX_NONE));
        }
#line 5025 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 682 "parser.yy" /* yacc.c:1646  */
    {
          CALL((yylsp[-6]), (yylsp[0]), typeBoundedInt((yyvsp[-6].prefix)));
        }
#line 5033 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 685 "parser.yy" /* yacc.c:1646  */
    {
          CALL((yylsp[0]), (yylsp[0]), typeChannel(ParserBuilder::PREFIX_NONE));
        }
#line 5041 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 688 "parser.yy" /* yacc.c:1646  */
    {
          CALL((yylsp[-1]), (yylsp[0]), typeChannel((yyvsp[-1].prefix)));
        }
#line 5049 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 691 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[0]), (yylsp[0]), typeClock(ParserBuilder::PREFIX_NONE));
        }
#line 5057 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 694 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-1]), (yylsp[-1]), typeClock(ParserBuilder::PREFIX_HYBRID));
	}
#line 5065 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 697 "parser.yy" /* yacc.c:1646  */
    {
          CALL((yylsp[0]), (yylsp[0]), typeVoid());
        }
#line 5073 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 701 "parser.yy" /* yacc.c:1646  */
    {
          CALL((yylsp[-3]), (yylsp[0]), typeScalar(ParserBuilder::PREFIX_NONE));
        }
#line 5081 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 704 "parser.yy" /* yacc.c:1646  */
    {
          CALL((yylsp[-4]), (yylsp[0]), typeScalar((yyvsp[-4].prefix)));
        }
#line 5089 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 710 "parser.yy" /* yacc.c:1646  */
    { strncpy((yyval.string), (yyvsp[0].string), MAXLEN); }
#line 5095 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 711 "parser.yy" /* yacc.c:1646  */
    { strncpy((yyval.string), (yyvsp[0].string), MAXLEN); }
#line 5101 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 715 "parser.yy" /* yacc.c:1646  */
    { strncpy((yyval.string), (yyvsp[0].string) , MAXLEN); }
#line 5107 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 716 "parser.yy" /* yacc.c:1646  */
    { strncpy((yyval.string), "A", MAXLEN); }
#line 5113 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 717 "parser.yy" /* yacc.c:1646  */
    { strncpy((yyval.string), "U", MAXLEN); }
#line 5119 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 718 "parser.yy" /* yacc.c:1646  */
    { strncpy((yyval.string), "W", MAXLEN); }
#line 5125 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 719 "parser.yy" /* yacc.c:1646  */
    { strncpy((yyval.string), "R", MAXLEN); }
#line 5131 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 720 "parser.yy" /* yacc.c:1646  */
    { strncpy((yyval.string), "E", MAXLEN); }
#line 5137 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 721 "parser.yy" /* yacc.c:1646  */
    { strncpy((yyval.string), "M", MAXLEN); }
#line 5143 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 722 "parser.yy" /* yacc.c:1646  */
    { strncpy((yyval.string), "sup", MAXLEN); }
#line 5149 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 723 "parser.yy" /* yacc.c:1646  */
    { strncpy((yyval.string), "inf", MAXLEN); }
#line 5155 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 724 "parser.yy" /* yacc.c:1646  */
    { strncpy((yyval.string), "simulation", MAXLEN); }
#line 5161 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 725 "parser.yy" /* yacc.c:1646  */
    { strncpy((yyval.string), "refinement", MAXLEN); }
#line 5167 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 726 "parser.yy" /* yacc.c:1646  */
    { strncpy((yyval.string), "consistency", MAXLEN); }
#line 5173 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 727 "parser.yy" /* yacc.c:1646  */
    { strncpy((yyval.string), "specification", MAXLEN); }
#line 5179 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 728 "parser.yy" /* yacc.c:1646  */
    { strncpy((yyval.string), "implementation", MAXLEN); }
#line 5185 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 732 "parser.yy" /* yacc.c:1646  */
    { (yyval.number)=(yyvsp[0].number); }
#line 5191 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 733 "parser.yy" /* yacc.c:1646  */
    { (yyval.number)=(yyvsp[-1].number)+(yyvsp[0].number); }
#line 5197 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 737 "parser.yy" /* yacc.c:1646  */
    {
          (yyval.number) = (yyvsp[-1].number); 
          CALL((yylsp[-2]), (yylsp[0]), typePop());
        }
#line 5206 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 744 "parser.yy" /* yacc.c:1646  */
    { (yyval.number)=1; }
#line 5212 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 745 "parser.yy" /* yacc.c:1646  */
    { (yyval.number)=(yyvsp[-2].number)+1; }
#line 5218 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 749 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[0]), (yylsp[0]), typeDuplicate());
        }
#line 5226 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 751 "parser.yy" /* yacc.c:1646  */
    { 
            CALL((yylsp[-2]), (yylsp[0]), structField((yyvsp[-2].string)));
        }
#line 5234 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 185:
#line 757 "parser.yy" /* yacc.c:1646  */
    { (yyval.prefix) = ParserBuilder::PREFIX_URGENT; }
#line 5240 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 758 "parser.yy" /* yacc.c:1646  */
    { (yyval.prefix) = ParserBuilder::PREFIX_BROADCAST; }
#line 5246 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 187:
#line 759 "parser.yy" /* yacc.c:1646  */
    { (yyval.prefix) = ParserBuilder::PREFIX_URGENT_BROADCAST; }
#line 5252 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 188:
#line 760 "parser.yy" /* yacc.c:1646  */
    { (yyval.prefix) = ParserBuilder::PREFIX_CONST; }
#line 5258 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 189:
#line 761 "parser.yy" /* yacc.c:1646  */
    { (yyval.prefix) = ParserBuilder::PREFIX_SYSTEM_META; }
#line 5264 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 190:
#line 769 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-3]), (yylsp[0]), procBegin((yyvsp[-2].string)));
        }
#line 5272 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 191:
#line 772 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-1]), (yylsp[0]), procEnd());
        }
#line 5280 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 203:
#line 800 "parser.yy" /* yacc.c:1646  */
    { 
	    CALL((yylsp[0]), (yylsp[0]), procState((yyvsp[0].string), false, false));
        }
#line 5288 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 204:
#line 803 "parser.yy" /* yacc.c:1646  */
    { 
	    CALL((yylsp[-3]), (yylsp[0]), procState((yyvsp[-3].string), true, false));
        }
#line 5296 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 205:
#line 806 "parser.yy" /* yacc.c:1646  */
    { 
	    CALL((yylsp[-3]), (yylsp[0]), procState((yyvsp[-3].string), false, true));
        }
#line 5304 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 206:
#line 809 "parser.yy" /* yacc.c:1646  */
    { 
	    CALL((yylsp[-3]), (yylsp[0]), procState((yyvsp[-3].string), false, false));
        }
#line 5312 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 210:
#line 824 "parser.yy" /* yacc.c:1646  */
    { 
	    CALL((yylsp[0]), (yylsp[0]), procBranchpoint((yyvsp[0].string))); // TODO
        }
#line 5320 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 211:
#line 829 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[0]), procStateInit((yyvsp[-1].string)));
        }
#line 5328 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 218:
#line 847 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[-3]), (yylsp[-1]), procEdgeBegin((yyvsp[-3].string), (yyvsp[-1].string), true));
        }
#line 5336 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 219:
#line 849 "parser.yy" /* yacc.c:1646  */
    { 
          strcpy(rootTransId, (yyvsp[-9].string)); 
          CALL((yylsp[-9]), (yylsp[-2]), procEdgeEnd((yyvsp[-9].string), (yyvsp[-7].string)));
        }
#line 5345 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 220:
#line 853 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[-3]), (yylsp[-1]), procEdgeBegin((yyvsp[-3].string), (yyvsp[-1].string), false));
        }
#line 5353 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 221:
#line 855 "parser.yy" /* yacc.c:1646  */
    { 
          strcpy(rootTransId, (yyvsp[-9].string)); 
          CALL((yylsp[-9]), (yylsp[-2]), procEdgeEnd((yyvsp[-9].string), (yyvsp[-7].string)));
        }
#line 5362 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 222:
#line 859 "parser.yy" /* yacc.c:1646  */
    { 
            CALL((yylsp[-2]), (yylsp[0]), procEdgeBegin((yyvsp[-2].string), (yyvsp[0].string), true)); }
#line 5369 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 223:
#line 861 "parser.yy" /* yacc.c:1646  */
    {
            CALL ((yylsp[-5]), (yylsp[-5]), procProb());
            CALL((yylsp[-6]), (yylsp[-1]), procEdgeEnd((yyvsp[-6].string), (yyvsp[-4].string)));
        }
#line 5378 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 224:
#line 868 "parser.yy" /* yacc.c:1646  */
    { 
            CALL((yylsp[-2]), (yylsp[-1]), procEdgeBegin(rootTransId, (yyvsp[-1].string), true)); 
        }
#line 5386 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 225:
#line 870 "parser.yy" /* yacc.c:1646  */
    { 
            CALL((yylsp[-8]), (yylsp[-2]), procEdgeEnd(rootTransId, (yyvsp[-7].string)));
        }
#line 5394 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 226:
#line 873 "parser.yy" /* yacc.c:1646  */
    { 
            CALL((yylsp[-2]), (yylsp[-1]), procEdgeBegin(rootTransId, (yyvsp[-1].string), false)); 
        }
#line 5402 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 227:
#line 875 "parser.yy" /* yacc.c:1646  */
    { 
            CALL((yylsp[-8]), (yylsp[-2]), procEdgeEnd(rootTransId, (yyvsp[-7].string)));
        }
#line 5410 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 231:
#line 887 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[-2]), (yylsp[0]), procSelect((yyvsp[-2].string)));
        }
#line 5418 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 232:
#line 890 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[-2]), (yylsp[0]), procSelect((yyvsp[-2].string)));
        }
#line 5426 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 234:
#line 897 "parser.yy" /* yacc.c:1646  */
    {
          CALL((yylsp[-1]), (yylsp[-1]), procGuard());
        }
#line 5434 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 235:
#line 900 "parser.yy" /* yacc.c:1646  */
    {
          CALL((yylsp[-2]), (yylsp[-1]), procGuard());
        }
#line 5442 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 240:
#line 913 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[0]), (yylsp[0]), procSync(SYNC_CSP));
        }
#line 5450 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 241:
#line 916 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-1]), (yylsp[0]), procSync(SYNC_BANG));
        }
#line 5458 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 242:
#line 919 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[-1]), procSync(SYNC_BANG));
        }
#line 5466 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 243:
#line 922 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-1]), (yylsp[0]), procSync(SYNC_QUE));
        }
#line 5474 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 244:
#line 925 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[-1]), procSync(SYNC_QUE));
        }
#line 5482 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 245:
#line 931 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[0]), (yylsp[0]), procMessage(SYNC_QUE));
        }
#line 5490 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 246:
#line 934 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-1]), (yylsp[-1]), procMessage(SYNC_QUE));
        }
#line 5498 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 248:
#line 941 "parser.yy" /* yacc.c:1646  */
    {
          CALL((yylsp[-1]), (yylsp[-1]), procUpdate());	  
        }
#line 5506 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 257:
#line 964 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[0]), (yylsp[0]), procStateCommit((yyvsp[0].string)));
        }
#line 5514 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 258:
#line 967 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[0]), procStateCommit((yyvsp[0].string)));
        }
#line 5522 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 259:
#line 973 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[0]), (yylsp[0]), procStateUrgent((yyvsp[0].string)));
        }
#line 5530 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 260:
#line 976 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[0]), procStateUrgent((yyvsp[0].string)));
        }
#line 5538 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 262:
#line 983 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-2]),(yylsp[0]), exprBinary(FRACTION));
	}
#line 5546 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 263:
#line 992 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[0]), (yylsp[0]), blockBegin());
        }
#line 5554 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 264:
#line 995 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-3]), (yylsp[-1]), blockEnd());
        }
#line 5562 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 272:
#line 1014 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[0]), (yylsp[0]), emptyStatement());
        }
#line 5570 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 273:
#line 1017 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-1]), (yylsp[0]), exprStatement());
        }
#line 5578 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 274:
#line 1020 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-7]), (yylsp[0]), forBegin());
        }
#line 5586 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 275:
#line 1023 "parser.yy" /* yacc.c:1646  */
    { 
            CALL((yylsp[-1]), (yylsp[-1]), forEnd());
        }
#line 5594 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 276:
#line 1026 "parser.yy" /* yacc.c:1646  */
    { 
            CALL((yylsp[-5]), (yylsp[0]), iterationBegin((yyvsp[-3].string)));
        }
#line 5602 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 277:
#line 1029 "parser.yy" /* yacc.c:1646  */
    { 
            CALL((yylsp[-1]), (yylsp[-1]), iterationEnd((yyvsp[-5].string)));
        }
#line 5610 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 279:
#line 1033 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[-1]), (yylsp[0]), whileBegin());
        }
#line 5618 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 280:
#line 1036 "parser.yy" /* yacc.c:1646  */
    { 
            CALL((yylsp[-3]), (yylsp[-2]), whileEnd());
          }
#line 5626 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 282:
#line 1040 "parser.yy" /* yacc.c:1646  */
    { 
            CALL((yylsp[0]), (yylsp[0]), doWhileBegin());
        }
#line 5634 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 283:
#line 1043 "parser.yy" /* yacc.c:1646  */
    { 
            CALL((yylsp[-6]), (yylsp[-1]), doWhileEnd());
          }
#line 5642 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 284:
#line 1046 "parser.yy" /* yacc.c:1646  */
    { 
            CALL((yylsp[-1]), (yylsp[0]), ifBegin());
        }
#line 5650 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 286:
#line 1050 "parser.yy" /* yacc.c:1646  */
    { 
            CALL((yylsp[-1]), (yylsp[0]), breakStatement());
          }
#line 5658 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 287:
#line 1053 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-1]), (yylsp[0]), continueStatement());
        }
#line 5666 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 288:
#line 1056 "parser.yy" /* yacc.c:1646  */
    { 
            CALL((yylsp[-3]), (yylsp[0]), switchBegin());
        }
#line 5674 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 289:
#line 1059 "parser.yy" /* yacc.c:1646  */
    { 
               CALL((yylsp[-3]), (yylsp[-1]), switchEnd());
           }
#line 5682 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 290:
#line 1062 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[0]), returnStatement(true));
        }
#line 5690 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 291:
#line 1065 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-1]), (yylsp[0]), returnStatement(false));
        }
#line 5698 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 292:
#line 1068 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-2]), (yylsp[-1]), assertStatement());
	}
#line 5706 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 293:
#line 1074 "parser.yy" /* yacc.c:1646  */
    { 
          CALL(position_t(), position_t(), ifEnd(false));
        }
#line 5714 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 294:
#line 1077 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[0]), (yylsp[0]), ifElse());
        }
#line 5722 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 295:
#line 1080 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-1]), (yylsp[-1]), ifEnd(true));
          }
#line 5730 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 298:
#line 1091 "parser.yy" /* yacc.c:1646  */
    { 
	    CALL((yylsp[-2]), (yylsp[0]), caseBegin());
        }
#line 5738 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 299:
#line 1094 "parser.yy" /* yacc.c:1646  */
    { 
            CALL((yylsp[-1]), (yylsp[-1]), caseEnd());
	}
#line 5746 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 300:
#line 1097 "parser.yy" /* yacc.c:1646  */
    { 
	    CALL((yylsp[-2]), (yylsp[0]), caseBegin());
        }
#line 5754 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 301:
#line 1100 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[-1]), (yylsp[-1]), caseEnd());
	}
#line 5762 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 302:
#line 1103 "parser.yy" /* yacc.c:1646  */
    { 
            CALL((yylsp[-1]), (yylsp[0]), defaultBegin());
        }
#line 5770 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 303:
#line 1106 "parser.yy" /* yacc.c:1646  */
    { 
            CALL((yylsp[-1]), (yylsp[-1]), defaultEnd());
        }
#line 5778 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 304:
#line 1109 "parser.yy" /* yacc.c:1646  */
    { 
	    CALL((yylsp[-2]), (yylsp[0]), defaultBegin());
        }
#line 5786 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 305:
#line 1112 "parser.yy" /* yacc.c:1646  */
    { 
            CALL((yylsp[-1]), (yylsp[-1]), defaultEnd());
        }
#line 5794 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 307:
#line 1119 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[0]), exprComma());
        }
#line 5802 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 308:
#line 1124 "parser.yy" /* yacc.c:1646  */
    { 
	    CALL((yylsp[0]), (yylsp[0]), exprFalse());
        }
#line 5810 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 309:
#line 1127 "parser.yy" /* yacc.c:1646  */
    { 
	    CALL((yylsp[0]), (yylsp[0]), exprTrue());
        }
#line 5818 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 310:
#line 1130 "parser.yy" /* yacc.c:1646  */
    { 
			CALL((yylsp[0]), (yylsp[0]), exprNat((yyvsp[0].number)));
        }
#line 5826 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 311:
#line 1133 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[0]), (yylsp[0]), exprDouble((yyvsp[0].floating)));
	}
#line 5834 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 312:
#line 1136 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-3]), (yylsp[0]), exprBuiltinFunction1((yyvsp[-3].kind)));
	}
#line 5842 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 313:
#line 1139 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-5]), (yylsp[-1]), exprBuiltinFunction2((yyvsp[-5].kind)));
	}
#line 5850 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 314:
#line 1142 "parser.yy" /* yacc.c:1646  */
    { 
	    CALL((yylsp[0]), (yylsp[0]), exprId((yyvsp[0].string)));
        }
#line 5858 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 315:
#line 1145 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[-1]), (yylsp[0]), exprCallBegin());	    
        }
#line 5866 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 316:
#line 1147 "parser.yy" /* yacc.c:1646  */
    { 
            CALL((yylsp[-4]), (yylsp[0]), exprCallEnd((yyvsp[-1].number)));
        }
#line 5874 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 317:
#line 1150 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[-1]), (yylsp[0]), exprCallBegin());
        }
#line 5882 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 318:
#line 1152 "parser.yy" /* yacc.c:1646  */
    {   
            CALL((yylsp[-4]), (yylsp[0]), exprCallEnd(0));
        }
#line 5890 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 319:
#line 1155 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-3]), (yylsp[0]), exprArray());
        }
#line 5898 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 320:
#line 1158 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-3]), (yylsp[0]), exprFalse());
        }
#line 5906 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 322:
#line 1162 "parser.yy" /* yacc.c:1646  */
    {
          CALL((yylsp[-2]), (yylsp[0]), exprFalse());
        }
#line 5914 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 323:
#line 1165 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-1]), (yylsp[0]), exprPostIncrement());
        }
#line 5922 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 324:
#line 1168 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-1]), (yylsp[0]), exprPreIncrement());
        }
#line 5930 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 325:
#line 1171 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-1]), (yylsp[0]), exprPostDecrement());
        }
#line 5938 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 326:
#line 1174 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-1]), (yylsp[0]), exprPreDecrement());
        }
#line 5946 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 327:
#line 1177 "parser.yy" /* yacc.c:1646  */
    {
          CALL((yylsp[-1]), (yylsp[0]), exprNat(INT_MIN));
	}
#line 5954 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 328:
#line 1180 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-1]), (yylsp[0]), exprUnary((yyvsp[-1].kind)));
        }
#line 5962 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 329:
#line 1183 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(LT));
        }
#line 5970 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 330:
#line 1186 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(LE));
        }
#line 5978 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 331:
#line 1189 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(EQ));
        }
#line 5986 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 332:
#line 1192 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(NEQ));
        }
#line 5994 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 333:
#line 1195 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(GT));
        }
#line 6002 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 334:
#line 1198 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(GE));
        }
#line 6010 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 335:
#line 1201 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(PLUS));
        }
#line 6018 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 336:
#line 1204 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(MINUS));
        }
#line 6026 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 337:
#line 1207 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(MULT));
        }
#line 6034 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 338:
#line 1210 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(DIV));
        }
#line 6042 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 339:
#line 1213 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(MOD));
        }
#line 6050 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 340:
#line 1216 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(BIT_AND));
        }
#line 6058 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 341:
#line 1219 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(BIT_OR));
        }
#line 6066 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 342:
#line 1222 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(BIT_XOR));
        }
#line 6074 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 343:
#line 1225 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(BIT_LSHIFT));
        }
#line 6082 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 344:
#line 1228 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(BIT_RSHIFT));
        }
#line 6090 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 345:
#line 1231 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(AND));
        }
#line 6098 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 346:
#line 1234 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(OR));
        }
#line 6106 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 347:
#line 1237 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-4]), (yylsp[0]), exprInlineIf());
        }
#line 6114 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 348:
#line 1240 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[0]), exprDot((yyvsp[0].string)));
        }
#line 6122 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 349:
#line 1243 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[-1]), (yylsp[0]), exprUnary(RATE));
        }
#line 6130 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 350:
#line 1246 "parser.yy" /* yacc.c:1646  */
    {
          CALL((yylsp[0]), (yylsp[0]), exprDeadlock());
        }
#line 6138 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 351:
#line 1249 "parser.yy" /* yacc.c:1646  */
    {  
          CALL((yylsp[-1]), (yylsp[-1]), exprUnary(NOT));
        }
#line 6146 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 352:
#line 1251 "parser.yy" /* yacc.c:1646  */
    {
          CALL((yylsp[-1]), (yylsp[-1]), exprBinary(OR));
        }
#line 6154 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 353:
#line 1254 "parser.yy" /* yacc.c:1646  */
    {
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(AND));
        }
#line 6162 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 354:
#line 1257 "parser.yy" /* yacc.c:1646  */
    {
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(OR));
        }
#line 6170 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 355:
#line 1260 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-2]), (yylsp[0]), exprBinary(XOR));
	}
#line 6178 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 356:
#line 1263 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[-2]), (yylsp[0]), exprBinary(MIN));
        }
#line 6186 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 357:
#line 1266 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[-2]), (yylsp[0]), exprBinary(MAX));
        }
#line 6194 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 358:
#line 1269 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[-5]), (yylsp[0]), exprSumBegin((yyvsp[-3].string)));
        }
#line 6202 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 359:
#line 1271 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[-7]), (yylsp[0]), exprSumEnd((yyvsp[-5].string)));
        }
#line 6210 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 360:
#line 1274 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[-5]), (yylsp[0]), exprForAllBegin((yyvsp[-3].string)));
        }
#line 6218 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 361:
#line 1276 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[-7]), (yylsp[0]), exprForAllEnd((yyvsp[-5].string)));
        }
#line 6226 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 362:
#line 1279 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[-5]), (yylsp[0]), exprExistsBegin((yyvsp[-3].string)));
        }
#line 6234 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 363:
#line 1281 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[-7]), (yylsp[0]), exprExistsEnd((yyvsp[-5].string)));
		  }
#line 6242 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 367:
#line 1290 "parser.yy" /* yacc.c:1646  */
    {CALL ((yylsp[-1]),(yylsp[0]),exprId ((yyvsp[0].string)));}
#line 6248 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 368:
#line 1290 "parser.yy" /* yacc.c:1646  */
    {CALL ((yylsp[-5]),(yylsp[0]),exprSpawn ((yyvsp[-1].number)));}
#line 6254 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 369:
#line 1292 "parser.yy" /* yacc.c:1646  */
    {CALL((yylsp[-2]),(yylsp[0]),exprExit());}
#line 6260 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 370:
#line 1294 "parser.yy" /* yacc.c:1646  */
    {CALL ((yylsp[-3]),(yylsp[-3]),exprId ((yyvsp[-1].string)));}
#line 6266 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 371:
#line 1294 "parser.yy" /* yacc.c:1646  */
    {CALL ((yylsp[-4]),(yylsp[0]),exprNumOf ());}
#line 6272 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 372:
#line 1296 "parser.yy" /* yacc.c:1646  */
    {CALL ((yylsp[-4]),(yylsp[0]),exprId ((yyvsp[0].string))); CALL ((yylsp[-4]),(yylsp[0]),exprForAllDynamicBegin ((yyvsp[-2].string),(yyvsp[0].string)));}
#line 6278 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 373:
#line 1296 "parser.yy" /* yacc.c:1646  */
    {CALL ((yylsp[-9]),(yylsp[-2]),exprForAllDynamicEnd ((yyvsp[-7].string)));;}
#line 6284 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 374:
#line 1298 "parser.yy" /* yacc.c:1646  */
    {CALL ((yylsp[-4]),(yylsp[0]),exprId ((yyvsp[0].string))); CALL ((yylsp[-4]),(yylsp[0]),exprExistsDynamicBegin ((yyvsp[-2].string),(yyvsp[0].string)));}
#line 6290 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 375:
#line 1298 "parser.yy" /* yacc.c:1646  */
    {CALL ((yylsp[-9]),(yylsp[-2]),exprExistsDynamicEnd ((yyvsp[-7].string)));}
#line 6296 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 376:
#line 1300 "parser.yy" /* yacc.c:1646  */
    {CALL ((yylsp[-4]),(yylsp[0]),exprId ((yyvsp[0].string))); CALL ((yylsp[-4]),(yylsp[0]),exprSumDynamicBegin ((yyvsp[-2].string),(yyvsp[0].string)));}
#line 6302 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 377:
#line 1300 "parser.yy" /* yacc.c:1646  */
    {CALL ((yylsp[-7]),(yylsp[0]),exprSumDynamicEnd ((yyvsp[-5].string)));}
#line 6308 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 378:
#line 1302 "parser.yy" /* yacc.c:1646  */
    {CALL ((yylsp[-4]),(yylsp[0]),exprId ((yyvsp[0].string))); CALL ((yylsp[-4]),(yylsp[0]),exprForeachDynamicBegin ((yyvsp[-2].string),(yyvsp[0].string)));}
#line 6314 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 379:
#line 1302 "parser.yy" /* yacc.c:1646  */
    {CALL ((yylsp[-7]),(yylsp[0]),exprForeachDynamicEnd ((yyvsp[-5].string)));}
#line 6320 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 380:
#line 1308 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[0]), exprAssignment((yyvsp[-1].kind)));
        }
#line 6328 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 381:
#line 1314 "parser.yy" /* yacc.c:1646  */
    { (yyval.kind) = ASSIGN; }
#line 6334 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 382:
#line 1315 "parser.yy" /* yacc.c:1646  */
    { (yyval.kind) = ASSPLUS; }
#line 6340 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 383:
#line 1316 "parser.yy" /* yacc.c:1646  */
    { (yyval.kind) = ASSMINUS; }
#line 6346 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 384:
#line 1317 "parser.yy" /* yacc.c:1646  */
    { (yyval.kind) = ASSDIV; }
#line 6352 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 385:
#line 1318 "parser.yy" /* yacc.c:1646  */
    { (yyval.kind) = ASSMOD; }
#line 6358 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 386:
#line 1319 "parser.yy" /* yacc.c:1646  */
    { (yyval.kind) = ASSMULT; }
#line 6364 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 387:
#line 1320 "parser.yy" /* yacc.c:1646  */
    { (yyval.kind) = ASSAND; }
#line 6370 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 388:
#line 1321 "parser.yy" /* yacc.c:1646  */
    { (yyval.kind) = ASSOR; }
#line 6376 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 389:
#line 1322 "parser.yy" /* yacc.c:1646  */
    { (yyval.kind) = ASSXOR; }
#line 6382 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 390:
#line 1323 "parser.yy" /* yacc.c:1646  */
    { (yyval.kind) = ASSLSHIFT; }
#line 6388 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 391:
#line 1324 "parser.yy" /* yacc.c:1646  */
    { (yyval.kind) = ASSRSHIFT; }
#line 6394 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 392:
#line 1329 "parser.yy" /* yacc.c:1646  */
    { (yyval.kind) = MINUS; }
#line 6400 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 393:
#line 1330 "parser.yy" /* yacc.c:1646  */
    { (yyval.kind) = PLUS; }
#line 6406 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 394:
#line 1331 "parser.yy" /* yacc.c:1646  */
    { (yyval.kind) = NOT; }
#line 6412 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 395:
#line 1332 "parser.yy" /* yacc.c:1646  */
    { (yyval.kind) = NOT; }
#line 6418 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 396:
#line 1336 "parser.yy" /* yacc.c:1646  */
    { (yyval.kind) = COS_F; }
#line 6424 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 397:
#line 1337 "parser.yy" /* yacc.c:1646  */
    { (yyval.kind) = SIN_F; }
#line 6430 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 398:
#line 1338 "parser.yy" /* yacc.c:1646  */
    { (yyval.kind) = EXP_F; }
#line 6436 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 399:
#line 1339 "parser.yy" /* yacc.c:1646  */
    { (yyval.kind) = LOG_F; }
#line 6442 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 400:
#line 1340 "parser.yy" /* yacc.c:1646  */
    { (yyval.kind) = SQRT_F; }
#line 6448 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 401:
#line 1341 "parser.yy" /* yacc.c:1646  */
    { (yyval.kind) = RANDOM_F; }
#line 6454 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 402:
#line 1342 "parser.yy" /* yacc.c:1646  */
    { (yyval.kind) = LN_F; }
#line 6460 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 403:
#line 1343 "parser.yy" /* yacc.c:1646  */
    { (yyval.kind) = FABS_F; }
#line 6466 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 404:
#line 1344 "parser.yy" /* yacc.c:1646  */
    { (yyval.kind) = CEIL_F; }
#line 6472 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 405:
#line 1345 "parser.yy" /* yacc.c:1646  */
    { (yyval.kind) = FLOOR_F; }
#line 6478 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 406:
#line 1349 "parser.yy" /* yacc.c:1646  */
    { (yyval.kind) = POW_F; }
#line 6484 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 407:
#line 1354 "parser.yy" /* yacc.c:1646  */
    { (yyval.number)=0; }
#line 6490 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 408:
#line 1355 "parser.yy" /* yacc.c:1646  */
    { 
            (yyval.number) = 1; 
        }
#line 6498 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 409:
#line 1358 "parser.yy" /* yacc.c:1646  */
    { 
            (yyval.number) = (yyvsp[-2].number) + 1; 
        }
#line 6506 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 415:
#line 1379 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[0]), (yylsp[0]), typeInt(ParserBuilder::PREFIX_CONST));
        }
#line 6514 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 416:
#line 1381 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-3]), (yylsp[-1]), typePop());
        }
#line 6522 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 420:
#line 1392 "parser.yy" /* yacc.c:1646  */
    {
          CALL((yylsp[0]), (yylsp[0]), typeDuplicate());
        }
#line 6530 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 421:
#line 1394 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-3]), (yylsp[0]), declVar((yyvsp[-3].string), true));
        }
#line 6538 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 422:
#line 1403 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-3]), (yylsp[0]), procBegin((yyvsp[-2].string)));
        }
#line 6546 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 423:
#line 1406 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[-1]), procEnd());
        }
#line 6554 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 424:
#line 1409 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-4]), (yylsp[0]), procBegin((yyvsp[-3].string)));
        }
#line 6562 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 425:
#line 1412 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[-1]), procEnd());
        }
#line 6570 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 426:
#line 1415 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-3]), (yylsp[0]), procBegin((yyvsp[-2].string)));
        }
#line 6578 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 427:
#line 1418 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[-1]), procEnd());
        }
#line 6586 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 428:
#line 1421 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[0]), procBegin("_"));
        }
#line 6594 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 429:
#line 1424 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[-1]), procEnd());
        }
#line 6602 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 430:
#line 1427 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[0]), procBegin((yyvsp[-1].string)));
        }
#line 6610 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 431:
#line 1430 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[-1]), procEnd());
        }
#line 6618 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 435:
#line 1442 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[0]), (yylsp[0]), typePop());
        }
#line 6626 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 437:
#line 1446 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[0]), typePop());
        }
#line 6634 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 439:
#line 1453 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[0]), (yylsp[0]), typeDuplicate());
        }
#line 6642 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 440:
#line 1455 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[-3]), (yylsp[0]), declParameter((yyvsp[-1].string), true));
        }
#line 6650 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 441:
#line 1458 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[0]), (yylsp[0]), typeDuplicate());
        }
#line 6658 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 442:
#line 1460 "parser.yy" /* yacc.c:1646  */
    { 
            CALL((yylsp[-4]), (yylsp[0]), declParameter((yyvsp[-1].string), true));
        }
#line 6666 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 443:
#line 1466 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[0]), (yylsp[0]), typeInt(ParserBuilder::PREFIX_CONST));
        }
#line 6674 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 444:
#line 1468 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[-1]), (yylsp[0]), declParameter((yyvsp[-1].string), false));
        }
#line 6682 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 445:
#line 1471 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[-1]), (yylsp[-1]), typeInt(ParserBuilder::PREFIX_CONST));
        }
#line 6690 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 446:
#line 1473 "parser.yy" /* yacc.c:1646  */
    { 
            CALL((yylsp[-1]), (yylsp[0]), declParameter((yyvsp[-1].string), false));
        }
#line 6698 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 454:
#line 1498 "parser.yy" /* yacc.c:1646  */
    { 
	    CALL((yylsp[0]), (yylsp[0]), procState((yyvsp[0].string), false, false));
        }
#line 6706 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 455:
#line 1501 "parser.yy" /* yacc.c:1646  */
    { 
	    CALL((yylsp[-3]), (yylsp[0]), procState((yyvsp[-3].string), true, false));
        }
#line 6714 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 457:
#line 1508 "parser.yy" /* yacc.c:1646  */
    {	  
        }
#line 6721 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 458:
#line 1510 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(AND));
        }
#line 6729 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 464:
#line 1527 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[-3]), (yylsp[-1]), procEdgeBegin((yyvsp[-3].string), (yyvsp[-1].string), true));
        }
#line 6737 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 465:
#line 1529 "parser.yy" /* yacc.c:1646  */
    { 
            strcpy(rootTransId, (yyvsp[-8].string));
            CALL((yylsp[-8]), (yylsp[-1]), procEdgeEnd((yyvsp[-8].string), (yyvsp[-6].string)));
        }
#line 6746 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 466:
#line 1537 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[-2]), (yylsp[-1]), procEdgeBegin(rootTransId, (yyvsp[-1].string), true));
        }
#line 6754 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 467:
#line 1539 "parser.yy" /* yacc.c:1646  */
    { 
            CALL((yylsp[-7]), (yylsp[-1]), procEdgeEnd(rootTransId, (yyvsp[-6].string)));
        }
#line 6762 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 470:
#line 1547 "parser.yy" /* yacc.c:1646  */
    {
          CALL((yylsp[-1]), (yylsp[-1]), procGuard());
        }
#line 6770 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 471:
#line 1550 "parser.yy" /* yacc.c:1646  */
    {
          CALL((yylsp[-2]), (yylsp[-1]), procGuard());
        }
#line 6778 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 473:
#line 1557 "parser.yy" /* yacc.c:1646  */
    { 
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(AND));
        }
#line 6786 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 479:
#line 1573 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-1]), (yylsp[0]), exprUnary(AF));
	}
#line 6794 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 480:
#line 1576 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[-2]), (yylsp[-1]), exprUnary(AF));
            CALL((yylsp[-4]), (yylsp[-1]), exprBinary(AND));
            CALL((yylsp[-6]), (yylsp[0]), exprUnary(AG));
        }
#line 6804 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 481:
#line 1581 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-1]), (yylsp[0]), exprUnary(AG));
        }
#line 6812 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 482:
#line 1584 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-1]), (yylsp[0]), exprUnary(EF));
        }
#line 6820 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 483:
#line 1587 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-1]), (yylsp[0]), exprUnary(EG));
        }
#line 6828 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 484:
#line 1590 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-2]), (yylsp[0]), exprBinary(LEADSTO));
        }
#line 6836 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 485:
#line 1593 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-5]), (yylsp[0]), exprBinary(A_UNTIL));
        }
#line 6844 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 486:
#line 1596 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-5]), (yylsp[0]), exprBinary(A_WEAKUNTIL));
        }
#line 6852 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 487:
#line 1602 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[0]), (yylsp[0]), property());
	}
#line 6860 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 488:
#line 1605 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-1]), (yylsp[0]), exprUnary(AG_R_Piotr));
            CALL((yylsp[-1]), (yylsp[0]), property());
        }
#line 6869 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 489:
#line 1609 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-1]), (yylsp[0]), exprUnary(EF_R_Piotr));
            CALL((yylsp[-1]), (yylsp[0]), property());
        }
#line 6878 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 490:
#line 1613 "parser.yy" /* yacc.c:1646  */
    {
            // Deprecated, comes from old uppaal-prob.
	    CALL((yylsp[-1]), (yylsp[0]), exprUnary(PMAX));
            CALL((yylsp[-1]), (yylsp[0]), property());
	}
#line 6888 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 491:
#line 1618 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[-2]), (yylsp[0]), exprUnary(CONTROL));
            CALL((yylsp[-2]), (yylsp[0]), property());
        }
#line 6897 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 492:
#line 1622 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-5]), (yylsp[0]), exprSMCControl((yyvsp[-3].number)));
	    CALL((yylsp[-5]), (yylsp[0]), property());
	}
#line 6906 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 493:
#line 1626 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-8]), (yylsp[0]), exprTernary(CONTROL_TOPT));
	    CALL((yylsp[-8]), (yylsp[0]), property());
	}
#line 6915 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 494:
#line 1630 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-6]), (yylsp[0]), exprBinary(CONTROL_TOPT_DEF1));
	    CALL((yylsp[-6]), (yylsp[0]), property());
	}
#line 6924 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 495:
#line 1634 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-3]), (yylsp[0]), exprUnary(CONTROL_TOPT_DEF2));
	    CALL((yylsp[-3]), (yylsp[0]), property());
	}
#line 6933 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 496:
#line 1638 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-3]), (yylsp[0]), exprUnary(EF_CONTROL));
	    CALL((yylsp[-3]), (yylsp[0]), property());
	}
#line 6942 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 497:
#line 1642 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[-3]), (yylsp[0]), exprBinary(PO_CONTROL));
	    CALL((yylsp[-3]), (yylsp[0]), property());
        }
#line 6951 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 498:
#line 1646 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-3]), (yylsp[0]), exprBinary(SIMULATION_LE));
	    CALL((yylsp[-5]), (yylsp[0]), property());
	}
#line 6960 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 499:
#line 1650 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-3]), (yylsp[0]), exprBinary(SIMULATION_GE));
	    CALL((yylsp[-5]), (yylsp[0]), property());
	}
#line 6969 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 500:
#line 1654 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-2]), (yylsp[0]), exprBinary(REFINEMENT_LE));
	    CALL((yylsp[-4]), (yylsp[0]), property());
	}
#line 6978 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 501:
#line 1658 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-2]), (yylsp[0]), exprBinary(REFINEMENT_GE));
	    CALL((yylsp[-4]), (yylsp[0]), property());
	}
#line 6987 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 502:
#line 1662 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-2]), (yylsp[0]), property());
	}
#line 6995 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 503:
#line 1665 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-2]), (yylsp[0]), exprUnary(SPECIFICATION));
	    CALL((yylsp[-2]), (yylsp[0]), property());
	}
#line 7004 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 504:
#line 1669 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-2]), (yylsp[0]), exprUnary(IMPLEMENTATION));
	    CALL((yylsp[-2]), (yylsp[0]), property());
	}
#line 7013 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 505:
#line 1673 "parser.yy" /* yacc.c:1646  */
    { 
            CALL((yylsp[-2]), (yylsp[0]), scenario((yyvsp[0].string))); //check if all instances in the scenario
                                        //correspond to TA processes in the system 
            CALL((yylsp[-2]), (yylsp[0]), exprScenario((yyvsp[0].string)));
            CALL((yylsp[-2]), (yylsp[0]), property());
        }
#line 7024 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 506:
#line 1679 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-9]), (yylsp[0]), exprProbaQualitative((yyvsp[-7].number), (yyvsp[-4].kind), (yyvsp[-1].kind), (yyvsp[0].floating)));
	    CALL((yylsp[-9]), (yylsp[0]), property());
	}
#line 7033 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 507:
#line 1683 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[-7]), (yylsp[0]), exprProbaQuantitative((yyvsp[-5].number), (yyvsp[-2].kind), false));
	    CALL((yylsp[-7]), (yylsp[0]), property());
	}
#line 7042 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 508:
#line 1687 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-8]), (yylsp[0]), exprProbaQuantitative((yyvsp[-6].number), DIAMOND, true));
	    CALL((yylsp[-8]), (yylsp[0]), property());
        }
#line 7051 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 509:
#line 1692 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-16]), (yylsp[0]), exprProbaCompare((yyvsp[-14].number), (yyvsp[-11].kind), (yyvsp[-5].number), (yyvsp[-2].kind)));
	    CALL((yylsp[-16]), (yylsp[0]), property());
	}
#line 7060 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 510:
#line 1696 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-7]), (yylsp[0]), exprSimulate((yyvsp[-6].number), (yyvsp[-4].number), (yyvsp[-1].number)));
	    CALL((yylsp[-7]), (yylsp[0]), property());
	}
#line 7069 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 511:
#line 1700 "parser.yy" /* yacc.c:1646  */
    {
	     CALL((yylsp[-9]),(yylsp[0]),exprSimulate((yyvsp[-8].number),(yyvsp[-6].number),(yyvsp[-3].number),true));
	     CALL((yylsp[-9]), (yylsp[0]), property());
	}
#line 7078 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 512:
#line 1705 "parser.yy" /* yacc.c:1646  */
    {
             CALL((yylsp[-11]),(yylsp[0]),exprSimulate((yyvsp[-10].number),(yyvsp[-8].number),(yyvsp[-5].number),true,(yyvsp[-2].number)));
	     CALL((yylsp[-11]), (yylsp[0]), property());
	}
#line 7087 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 513:
#line 1710 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-10]), (yylsp[0]), exprProbaExpected((yyvsp[-8].number), (yyvsp[-3].string)));
	    CALL((yylsp[-10]), (yylsp[0]), property());
        }
#line 7096 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 514:
#line 1714 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-1]),(yylsp[0]),exprMitlFormula ());
	    CALL((yylsp[-1]),(yylsp[0]),property ());
        }
#line 7105 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 515:
#line 1726 "parser.yy" /* yacc.c:1646  */
    {
	CALL((yylsp[-9]),(yylsp[0]),exprMitlUntil ((yyvsp[-5].number),(yyvsp[-3].number)));
  }
#line 7113 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 516:
#line 1729 "parser.yy" /* yacc.c:1646  */
    {
	CALL((yylsp[-9]),(yylsp[0]),exprMitlRelease ((yyvsp[-5].number),(yyvsp[-3].number)));
  }
#line 7121 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 517:
#line 1739 "parser.yy" /* yacc.c:1646  */
    {
	CALL((yylsp[-3]),(yylsp[0]),exprMitlNext ());
  }
#line 7129 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 518:
#line 1743 "parser.yy" /* yacc.c:1646  */
    {
	CALL ((yylsp[-8]),(yylsp[-5]),exprMitlDiamond ((yyvsp[-5].number),(yyvsp[-3].number)));
}
#line 7137 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 519:
#line 1746 "parser.yy" /* yacc.c:1646  */
    {
	CALL ((yylsp[-8]),(yylsp[-5]),exprMitlBox ((yyvsp[-5].number),(yyvsp[-3].number)));
  }
#line 7145 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 520:
#line 1754 "parser.yy" /* yacc.c:1646  */
    { (yyval.number) = 1; }
#line 7151 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 521:
#line 1755 "parser.yy" /* yacc.c:1646  */
    { (yyval.number) = 0; }
#line 7157 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 522:
#line 1756 "parser.yy" /* yacc.c:1646  */
    { (yyval.number) = 2; }
#line 7163 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 523:
#line 1760 "parser.yy" /* yacc.c:1646  */
    { (yyval.kind) = GE; }
#line 7169 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 524:
#line 1761 "parser.yy" /* yacc.c:1646  */
    { (yyval.kind) = LE; }
#line 7175 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 525:
#line 1765 "parser.yy" /* yacc.c:1646  */
    { (yyval.kind) = BOX; }
#line 7181 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 526:
#line 1766 "parser.yy" /* yacc.c:1646  */
    { (yyval.kind) = DIAMOND; }
#line 7187 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 527:
#line 1770 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[0]), (yylsp[0]), exprTrue());
	    CALL((yylsp[0]), (yylsp[0]), exprUnary(AG));
            CALL((yylsp[0]), (yylsp[0]), exprBinary(CONSISTENCY));
	}
#line 7197 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 528:
#line 1775 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-2]), (yylsp[-1]), exprBinary(CONSISTENCY));
	}
#line 7205 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 529:
#line 1778 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-2]), (yylsp[-2]), exprBinary(CONSISTENCY));
        }
#line 7213 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 530:
#line 1781 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-2]), (yylsp[-1]), exprBinary(CONSISTENCY));
	}
#line 7221 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 531:
#line 1784 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-2]), (yylsp[-1]), exprBinary(CONSISTENCY));
	}
#line 7229 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 532:
#line 1787 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-2]), (yylsp[-1]), exprBinary(CONSISTENCY));
	}
#line 7237 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 533:
#line 1793 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[0]), (yylsp[0]), exprId((yyvsp[0].string)));
	}
#line 7245 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 534:
#line 1799 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[0]), (yylsp[0]), exprNary(SYNTAX_COMPOSITION, (yyvsp[0].number)));
	}
#line 7253 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 535:
#line 1805 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[0]), (yylsp[0]), exprNary(TIOCOMPOSITION, (yyvsp[0].number)));
	}
#line 7261 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 536:
#line 1811 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[0]), (yylsp[0]), exprNary(TIOCONJUNCTION, (yyvsp[0].number)));
	}
#line 7269 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 537:
#line 1817 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-2]), (yylsp[0]), exprBinary(TIOQUOTIENT));
	}
#line 7277 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 538:
#line 1823 "parser.yy" /* yacc.c:1646  */
    { (yyval.number) = 2; }
#line 7283 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 539:
#line 1824 "parser.yy" /* yacc.c:1646  */
    { (yyval.number) = (yyvsp[-2].number) + 1; }
#line 7289 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 540:
#line 1828 "parser.yy" /* yacc.c:1646  */
    { (yyval.number) = 2; }
#line 7295 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 541:
#line 1829 "parser.yy" /* yacc.c:1646  */
    { (yyval.number) = (yyvsp[-2].number) + 1; }
#line 7301 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 542:
#line 1833 "parser.yy" /* yacc.c:1646  */
    { (yyval.number) = 2; }
#line 7307 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 543:
#line 1834 "parser.yy" /* yacc.c:1646  */
    { (yyval.number) = (yyvsp[-2].number) + 1; }
#line 7313 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 544:
#line 1838 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[0]), (yylsp[0]), exprTrue());
	    CALL((yylsp[0]), (yylsp[0]), exprUnary(AG));
        }
#line 7322 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 546:
#line 1847 "parser.yy" /* yacc.c:1646  */
    {
            CALL((yylsp[0]), (yylsp[0]), exprNary(LIST,0));
	    CALL((yylsp[0]), (yylsp[0]), exprBinary(RESTRICT));
        }
#line 7331 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 547:
#line 1851 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-3]), (yylsp[0]), exprNary(LIST,(yyvsp[-1].number)));
	    CALL((yylsp[-3]), (yylsp[0]), exprBinary(RESTRICT));
	}
#line 7340 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 548:
#line 1858 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[0]), (yylsp[0]), exprId((yyvsp[0].string)));
	    CALL((yylsp[0]), (yylsp[0]), exprNary(LIST,1));
	}
#line 7349 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 549:
#line 1862 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-2]), (yylsp[0]), exprNary(LIST,(yyvsp[-1].number)));
	}
#line 7357 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 550:
#line 1867 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[0]), (yylsp[0]), exprId((yyvsp[0].string)));
	    (yyval.number) = 1;
	}
#line 7366 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 551:
#line 1871 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-2]), (yylsp[0]), exprId((yyvsp[0].string)));
	    (yyval.number) = (yyvsp[-2].number) + 1;
	}
#line 7375 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 552:
#line 1877 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-2]), (yylsp[0]), exprNary(LIST,(yyvsp[-1].number)));
	}
#line 7383 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 553:
#line 1886 "parser.yy" /* yacc.c:1646  */
    { (yyval.number) = 0; }
#line 7389 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 555:
#line 1891 "parser.yy" /* yacc.c:1646  */
    { (yyval.number) = 1; }
#line 7395 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 556:
#line 1892 "parser.yy" /* yacc.c:1646  */
    { (yyval.number) = (yyvsp[-2].number)+1; }
#line 7401 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 557:
#line 1896 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-1]), (yylsp[0]), exprTrue());
	}
#line 7409 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 559:
#line 1903 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-1]), (yylsp[0]), exprTrue());
	}
#line 7417 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 563:
#line 1912 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-1]), (yylsp[0]), exprNary(LIST,(yyvsp[0].number)));
            CALL((yylsp[-1]), (yylsp[0]), exprBinary(SUP_VAR));
	    CALL((yylsp[-1]), (yylsp[0]), property());
        }
#line 7427 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 564:
#line 1917 "parser.yy" /* yacc.c:1646  */
    {
	    CALL((yylsp[-1]), (yylsp[0]), exprNary(LIST,(yyvsp[0].number)));
            CALL((yylsp[-1]), (yylsp[0]), exprBinary(INF_VAR));
	    CALL((yylsp[-1]), (yylsp[0]), property());
        }
#line 7437 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 7441 "parser.tab.c" /* yacc.c:1646  */
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

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
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
#line 1923 "parser.yy" /* yacc.c:1906  */



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

static int32_t parseProperty(ParserBuilder *aParserBuilder, const std::string& xpath)
{
    // Select syntax
    syntax = (syntax_t)(SYNTAX_PROPERTY);
    setStartToken(S_PROPERTY, false);

    // Set parser builder 
    ch = aParserBuilder;
    
    // Reset position tracking
    PositionTracker::setPath(ch, xpath);

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
