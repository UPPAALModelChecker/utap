/* A Bison parser, made by GNU Bison 3.7.6.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30706

/* Bison version string.  */
#define YYBISON_VERSION "3.7.6"

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
#line 40 "parser.yy"


 #include "libparser.h"
 #include "utap/position.h"
 #include <cstring>

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


#line 205 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
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


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int utap_debug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    T_ASSIGNMENT = 258,            /* T_ASSIGNMENT  */
    T_ASSPLUS = 259,               /* T_ASSPLUS  */
    T_ASSMINUS = 260,              /* T_ASSMINUS  */
    T_ASSMULT = 261,               /* T_ASSMULT  */
    T_ASSDIV = 262,                /* T_ASSDIV  */
    T_ASSMOD = 263,                /* T_ASSMOD  */
    T_ASSOR = 264,                 /* T_ASSOR  */
    T_ASSAND = 265,                /* T_ASSAND  */
    T_ASSXOR = 266,                /* T_ASSXOR  */
    T_ASSLSHIFT = 267,             /* T_ASSLSHIFT  */
    T_ASSRSHIFT = 268,             /* T_ASSRSHIFT  */
    T_EXCLAM = 269,                /* T_EXCLAM  */
    T_INCREMENT = 270,             /* T_INCREMENT  */
    T_DECREMENT = 271,             /* T_DECREMENT  */
    T_PLUS = 272,                  /* T_PLUS  */
    T_MINUS = 273,                 /* T_MINUS  */
    T_MULT = 274,                  /* T_MULT  */
    T_DIV = 275,                   /* T_DIV  */
    T_MOD = 276,                   /* T_MOD  */
    T_OR = 277,                    /* T_OR  */
    T_XOR = 278,                   /* T_XOR  */
    T_LSHIFT = 279,                /* T_LSHIFT  */
    T_RSHIFT = 280,                /* T_RSHIFT  */
    T_BOOL_AND = 281,              /* T_BOOL_AND  */
    T_BOOL_OR = 282,               /* T_BOOL_OR  */
    T_KW_AND = 283,                /* T_KW_AND  */
    T_KW_OR = 284,                 /* T_KW_OR  */
    T_KW_XOR = 285,                /* T_KW_XOR  */
    T_KW_IMPLY = 286,              /* T_KW_IMPLY  */
    T_KW_NOT = 287,                /* T_KW_NOT  */
    T_SUP = 288,                   /* T_SUP  */
    T_INF = 289,                   /* T_INF  */
    T_ABS = 290,                   /* T_ABS  */
    T_FABS = 291,                  /* T_FABS  */
    T_FMOD = 292,                  /* T_FMOD  */
    T_FMA = 293,                   /* T_FMA  */
    T_FMAX = 294,                  /* T_FMAX  */
    T_FMIN = 295,                  /* T_FMIN  */
    T_FDIM = 296,                  /* T_FDIM  */
    T_EXP = 297,                   /* T_EXP  */
    T_EXP2 = 298,                  /* T_EXP2  */
    T_EXPM1 = 299,                 /* T_EXPM1  */
    T_LN = 300,                    /* T_LN  */
    T_LOG = 301,                   /* T_LOG  */
    T_LOG10 = 302,                 /* T_LOG10  */
    T_LOG2 = 303,                  /* T_LOG2  */
    T_LOG1P = 304,                 /* T_LOG1P  */
    T_POW = 305,                   /* T_POW  */
    T_SQRT = 306,                  /* T_SQRT  */
    T_CBRT = 307,                  /* T_CBRT  */
    T_HYPOT = 308,                 /* T_HYPOT  */
    T_SIN = 309,                   /* T_SIN  */
    T_COS = 310,                   /* T_COS  */
    T_TAN = 311,                   /* T_TAN  */
    T_ASIN = 312,                  /* T_ASIN  */
    T_ACOS = 313,                  /* T_ACOS  */
    T_ATAN = 314,                  /* T_ATAN  */
    T_ATAN2 = 315,                 /* T_ATAN2  */
    T_SINH = 316,                  /* T_SINH  */
    T_COSH = 317,                  /* T_COSH  */
    T_TANH = 318,                  /* T_TANH  */
    T_ASINH = 319,                 /* T_ASINH  */
    T_ACOSH = 320,                 /* T_ACOSH  */
    T_ATANH = 321,                 /* T_ATANH  */
    T_ERF = 322,                   /* T_ERF  */
    T_ERFC = 323,                  /* T_ERFC  */
    T_TGAMMA = 324,                /* T_TGAMMA  */
    T_LGAMMA = 325,                /* T_LGAMMA  */
    T_CEIL = 326,                  /* T_CEIL  */
    T_FLOOR = 327,                 /* T_FLOOR  */
    T_TRUNC = 328,                 /* T_TRUNC  */
    T_ROUND = 329,                 /* T_ROUND  */
    T_FINT = 330,                  /* T_FINT  */
    T_LDEXP = 331,                 /* T_LDEXP  */
    T_ILOGB = 332,                 /* T_ILOGB  */
    T_LOGB = 333,                  /* T_LOGB  */
    T_NEXTAFTER = 334,             /* T_NEXTAFTER  */
    T_NEXTTOWARD = 335,            /* T_NEXTTOWARD  */
    T_COPYSIGN = 336,              /* T_COPYSIGN  */
    T_FPCLASSIFY = 337,            /* T_FPCLASSIFY  */
    T_ISFINITE = 338,              /* T_ISFINITE  */
    T_ISINF = 339,                 /* T_ISINF  */
    T_ISNAN = 340,                 /* T_ISNAN  */
    T_ISNORMAL = 341,              /* T_ISNORMAL  */
    T_SIGNBIT = 342,               /* T_SIGNBIT  */
    T_ISUNORDERED = 343,           /* T_ISUNORDERED  */
    T_RANDOM = 344,                /* T_RANDOM  */
    T_RANDOM_ARCSINE = 345,        /* T_RANDOM_ARCSINE  */
    T_RANDOM_BETA = 346,           /* T_RANDOM_BETA  */
    T_RANDOM_GAMMA = 347,          /* T_RANDOM_GAMMA  */
    T_RANDOM_NORMAL = 348,         /* T_RANDOM_NORMAL  */
    T_RANDOM_POISSON = 349,        /* T_RANDOM_POISSON  */
    T_RANDOM_TRI = 350,            /* T_RANDOM_TRI  */
    T_RANDOM_WEIBULL = 351,        /* T_RANDOM_WEIBULL  */
    T_FORALL = 352,                /* T_FORALL  */
    T_EXISTS = 353,                /* T_EXISTS  */
    T_FOREACH = 354,               /* T_FOREACH  */
    T_SUM = 355,                   /* T_SUM  */
    T_LT = 356,                    /* T_LT  */
    T_LEQ = 357,                   /* T_LEQ  */
    T_EQ = 358,                    /* T_EQ  */
    T_NEQ = 359,                   /* T_NEQ  */
    T_GEQ = 360,                   /* T_GEQ  */
    T_GT = 361,                    /* T_GT  */
    T_FOR = 362,                   /* T_FOR  */
    T_WHILE = 363,                 /* T_WHILE  */
    T_DO = 364,                    /* T_DO  */
    T_BREAK = 365,                 /* T_BREAK  */
    T_CONTINUE = 366,              /* T_CONTINUE  */
    T_SWITCH = 367,                /* T_SWITCH  */
    T_IF = 368,                    /* T_IF  */
    T_ELSE = 369,                  /* T_ELSE  */
    T_CASE = 370,                  /* T_CASE  */
    T_DEFAULT = 371,               /* T_DEFAULT  */
    T_RETURN = 372,                /* T_RETURN  */
    T_ASSERT = 373,                /* T_ASSERT  */
    T_PRIORITY = 374,              /* T_PRIORITY  */
    T_TYPEDEF = 375,               /* T_TYPEDEF  */
    T_STRUCT = 376,                /* T_STRUCT  */
    T_CONST = 377,                 /* T_CONST  */
    T_OLDCONST = 378,              /* T_OLDCONST  */
    T_URGENT = 379,                /* T_URGENT  */
    T_BROADCAST = 380,             /* T_BROADCAST  */
    T_TRUE = 381,                  /* T_TRUE  */
    T_FALSE = 382,                 /* T_FALSE  */
    T_META = 383,                  /* T_META  */
    T_SYSTEM = 384,                /* T_SYSTEM  */
    T_PROCESS = 385,               /* T_PROCESS  */
    T_STATE = 386,                 /* T_STATE  */
    T_BRANCHPOINT = 387,           /* T_BRANCHPOINT  */
    T_COMMIT = 388,                /* T_COMMIT  */
    T_INIT = 389,                  /* T_INIT  */
    T_TRANS = 390,                 /* T_TRANS  */
    T_SELECT = 391,                /* T_SELECT  */
    T_GUARD = 392,                 /* T_GUARD  */
    T_SYNC = 393,                  /* T_SYNC  */
    T_ASSIGN = 394,                /* T_ASSIGN  */
    T_PROBABILITY = 395,           /* T_PROBABILITY  */
    T_BEFORE = 396,                /* T_BEFORE  */
    T_AFTER = 397,                 /* T_AFTER  */
    T_PROGRESS = 398,              /* T_PROGRESS  */
    T_ARROW = 399,                 /* T_ARROW  */
    T_UNCONTROL_ARROW = 400,       /* T_UNCONTROL_ARROW  */
    T_IO = 401,                    /* T_IO  */
    T_QUERY = 402,                 /* T_QUERY  */
    T_DEADLOCK = 403,              /* T_DEADLOCK  */
    T_EF = 404,                    /* T_EF  */
    T_EG = 405,                    /* T_EG  */
    T_AF = 406,                    /* T_AF  */
    T_AG = 407,                    /* T_AG  */
    T_LEADSTO = 408,               /* T_LEADSTO  */
    T_RESULTSET = 409,             /* T_RESULTSET  */
    T_EF_PLUS = 410,               /* T_EF_PLUS  */
    T_AG_PLUS = 411,               /* T_AG_PLUS  */
    T_EF_MULT = 412,               /* T_EF_MULT  */
    T_AG_MULT = 413,               /* T_AG_MULT  */
    T_SCENARIO = 414,              /* T_SCENARIO  */
    T_CONTROL = 415,               /* T_CONTROL  */
    T_CONTROL_T = 416,             /* T_CONTROL_T  */
    T_SIMULATION = 417,            /* T_SIMULATION  */
    T_SIMULATE = 418,              /* T_SIMULATE  */
    T_CONSISTENCY = 419,           /* T_CONSISTENCY  */
    T_SPECIFICATION = 420,         /* T_SPECIFICATION  */
    T_IMPLEMENTATION = 421,        /* T_IMPLEMENTATION  */
    T_REFINEMENT = 422,            /* T_REFINEMENT  */
    T_GANTT = 423,                 /* T_GANTT  */
    T_PMAX = 424,                  /* T_PMAX  */
    T_PROBA = 425,                 /* T_PROBA  */
    T_DIAMOND = 426,               /* T_DIAMOND  */
    T_BOX = 427,                   /* T_BOX  */
    T_HASH = 428,                  /* T_HASH  */
    T_ERROR = 429,                 /* T_ERROR  */
    T_ID = 430,                    /* T_ID  */
    T_TYPENAME = 431,              /* T_TYPENAME  */
    T_NAT = 432,                   /* T_NAT  */
    T_FLOATING = 433,              /* T_FLOATING  */
    T_POS_NEG_MAX = 434,           /* T_POS_NEG_MAX  */
    T_BOOL = 435,                  /* T_BOOL  */
    T_INT = 436,                   /* T_INT  */
    T_CHAN = 437,                  /* T_CHAN  */
    T_CLOCK = 438,                 /* T_CLOCK  */
    T_VOID = 439,                  /* T_VOID  */
    T_SCALAR = 440,                /* T_SCALAR  */
    T_DOUBLE = 441,                /* T_DOUBLE  */
    T_NEW = 442,                   /* T_NEW  */
    T_NEW_DECLARATION = 443,       /* T_NEW_DECLARATION  */
    T_NEW_LOCAL_DECL = 444,        /* T_NEW_LOCAL_DECL  */
    T_NEW_INST = 445,              /* T_NEW_INST  */
    T_NEW_SYSTEM = 446,            /* T_NEW_SYSTEM  */
    T_NEW_PARAMETERS = 447,        /* T_NEW_PARAMETERS  */
    T_NEW_INVARIANT = 448,         /* T_NEW_INVARIANT  */
    T_NEW_GUARD = 449,             /* T_NEW_GUARD  */
    T_NEW_SYNC = 450,              /* T_NEW_SYNC  */
    T_NEW_ASSIGN = 451,            /* T_NEW_ASSIGN  */
    T_NEW_SELECT = 452,            /* T_NEW_SELECT  */
    T_EXPONENTIALRATE = 453,       /* T_EXPONENTIALRATE  */
    T_OLD = 454,                   /* T_OLD  */
    T_OLD_DECLARATION = 455,       /* T_OLD_DECLARATION  */
    T_OLD_LOCAL_DECL = 456,        /* T_OLD_LOCAL_DECL  */
    T_OLD_INST = 457,              /* T_OLD_INST  */
    T_OLD_PARAMETERS = 458,        /* T_OLD_PARAMETERS  */
    T_OLD_INVARIANT = 459,         /* T_OLD_INVARIANT  */
    T_OLD_GUARD = 460,             /* T_OLD_GUARD  */
    T_OLD_ASSIGN = 461,            /* T_OLD_ASSIGN  */
    T_PROPERTY = 462,              /* T_PROPERTY  */
    T_EXPRESSION = 463,            /* T_EXPRESSION  */
    T_EXPRESSION_LIST = 464,       /* T_EXPRESSION_LIST  */
    T_XTA_PROCESS = 465,           /* T_XTA_PROCESS  */
    T_INSTANCELINE = 466,          /* T_INSTANCELINE  */
    T_MESSAGE = 467,               /* T_MESSAGE  */
    T_UPDATE = 468,                /* T_UPDATE  */
    T_CONDITION = 469,             /* T_CONDITION  */
    T_MITL_AND = 470,              /* T_MITL_AND  */
    T_MITL_OR = 471,               /* T_MITL_OR  */
    T_MITL_NEXT = 472,             /* T_MITL_NEXT  */
    T_DYNAMIC = 473,               /* T_DYNAMIC  */
    T_HYBRID = 474,                /* T_HYBRID  */
    T_SPAWN = 475,                 /* T_SPAWN  */
    T_EXIT = 476,                  /* T_EXIT  */
    T_NUMOF = 477,                 /* T_NUMOF  */
    T_MIN = 478,                   /* T_MIN  */
    T_MAX = 479,                   /* T_MAX  */
    UOPERATOR = 480                /* UOPERATOR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
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
#define T_ABS 290
#define T_FABS 291
#define T_FMOD 292
#define T_FMA 293
#define T_FMAX 294
#define T_FMIN 295
#define T_FDIM 296
#define T_EXP 297
#define T_EXP2 298
#define T_EXPM1 299
#define T_LN 300
#define T_LOG 301
#define T_LOG10 302
#define T_LOG2 303
#define T_LOG1P 304
#define T_POW 305
#define T_SQRT 306
#define T_CBRT 307
#define T_HYPOT 308
#define T_SIN 309
#define T_COS 310
#define T_TAN 311
#define T_ASIN 312
#define T_ACOS 313
#define T_ATAN 314
#define T_ATAN2 315
#define T_SINH 316
#define T_COSH 317
#define T_TANH 318
#define T_ASINH 319
#define T_ACOSH 320
#define T_ATANH 321
#define T_ERF 322
#define T_ERFC 323
#define T_TGAMMA 324
#define T_LGAMMA 325
#define T_CEIL 326
#define T_FLOOR 327
#define T_TRUNC 328
#define T_ROUND 329
#define T_FINT 330
#define T_LDEXP 331
#define T_ILOGB 332
#define T_LOGB 333
#define T_NEXTAFTER 334
#define T_NEXTTOWARD 335
#define T_COPYSIGN 336
#define T_FPCLASSIFY 337
#define T_ISFINITE 338
#define T_ISINF 339
#define T_ISNAN 340
#define T_ISNORMAL 341
#define T_SIGNBIT 342
#define T_ISUNORDERED 343
#define T_RANDOM 344
#define T_RANDOM_ARCSINE 345
#define T_RANDOM_BETA 346
#define T_RANDOM_GAMMA 347
#define T_RANDOM_NORMAL 348
#define T_RANDOM_POISSON 349
#define T_RANDOM_TRI 350
#define T_RANDOM_WEIBULL 351
#define T_FORALL 352
#define T_EXISTS 353
#define T_FOREACH 354
#define T_SUM 355
#define T_LT 356
#define T_LEQ 357
#define T_EQ 358
#define T_NEQ 359
#define T_GEQ 360
#define T_GT 361
#define T_FOR 362
#define T_WHILE 363
#define T_DO 364
#define T_BREAK 365
#define T_CONTINUE 366
#define T_SWITCH 367
#define T_IF 368
#define T_ELSE 369
#define T_CASE 370
#define T_DEFAULT 371
#define T_RETURN 372
#define T_ASSERT 373
#define T_PRIORITY 374
#define T_TYPEDEF 375
#define T_STRUCT 376
#define T_CONST 377
#define T_OLDCONST 378
#define T_URGENT 379
#define T_BROADCAST 380
#define T_TRUE 381
#define T_FALSE 382
#define T_META 383
#define T_SYSTEM 384
#define T_PROCESS 385
#define T_STATE 386
#define T_BRANCHPOINT 387
#define T_COMMIT 388
#define T_INIT 389
#define T_TRANS 390
#define T_SELECT 391
#define T_GUARD 392
#define T_SYNC 393
#define T_ASSIGN 394
#define T_PROBABILITY 395
#define T_BEFORE 396
#define T_AFTER 397
#define T_PROGRESS 398
#define T_ARROW 399
#define T_UNCONTROL_ARROW 400
#define T_IO 401
#define T_QUERY 402
#define T_DEADLOCK 403
#define T_EF 404
#define T_EG 405
#define T_AF 406
#define T_AG 407
#define T_LEADSTO 408
#define T_RESULTSET 409
#define T_EF_PLUS 410
#define T_AG_PLUS 411
#define T_EF_MULT 412
#define T_AG_MULT 413
#define T_SCENARIO 414
#define T_CONTROL 415
#define T_CONTROL_T 416
#define T_SIMULATION 417
#define T_SIMULATE 418
#define T_CONSISTENCY 419
#define T_SPECIFICATION 420
#define T_IMPLEMENTATION 421
#define T_REFINEMENT 422
#define T_GANTT 423
#define T_PMAX 424
#define T_PROBA 425
#define T_DIAMOND 426
#define T_BOX 427
#define T_HASH 428
#define T_ERROR 429
#define T_ID 430
#define T_TYPENAME 431
#define T_NAT 432
#define T_FLOATING 433
#define T_POS_NEG_MAX 434
#define T_BOOL 435
#define T_INT 436
#define T_CHAN 437
#define T_CLOCK 438
#define T_VOID 439
#define T_SCALAR 440
#define T_DOUBLE 441
#define T_NEW 442
#define T_NEW_DECLARATION 443
#define T_NEW_LOCAL_DECL 444
#define T_NEW_INST 445
#define T_NEW_SYSTEM 446
#define T_NEW_PARAMETERS 447
#define T_NEW_INVARIANT 448
#define T_NEW_GUARD 449
#define T_NEW_SYNC 450
#define T_NEW_ASSIGN 451
#define T_NEW_SELECT 452
#define T_EXPONENTIALRATE 453
#define T_OLD 454
#define T_OLD_DECLARATION 455
#define T_OLD_LOCAL_DECL 456
#define T_OLD_INST 457
#define T_OLD_PARAMETERS 458
#define T_OLD_INVARIANT 459
#define T_OLD_GUARD 460
#define T_OLD_ASSIGN 461
#define T_PROPERTY 462
#define T_EXPRESSION 463
#define T_EXPRESSION_LIST 464
#define T_XTA_PROCESS 465
#define T_INSTANCELINE 466
#define T_MESSAGE 467
#define T_UPDATE 468
#define T_CONDITION 469
#define T_MITL_AND 470
#define T_MITL_OR 471
#define T_MITL_NEXT 472
#define T_DYNAMIC 473
#define T_HYBRID 474
#define T_SPAWN 475
#define T_EXIT 476
#define T_NUMOF 477
#define T_MIN 478
#define T_MAX 479
#define UOPERATOR 480

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 302 "parser.yy"

    bool flag;
    int number;
    ParserBuilder::PREFIX prefix;
    kind_t kind;
    char string[MAXLEN];
    double floating;

#line 714 "parser.tab.c"

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


/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_T_ASSIGNMENT = 3,               /* T_ASSIGNMENT  */
  YYSYMBOL_T_ASSPLUS = 4,                  /* T_ASSPLUS  */
  YYSYMBOL_T_ASSMINUS = 5,                 /* T_ASSMINUS  */
  YYSYMBOL_T_ASSMULT = 6,                  /* T_ASSMULT  */
  YYSYMBOL_T_ASSDIV = 7,                   /* T_ASSDIV  */
  YYSYMBOL_T_ASSMOD = 8,                   /* T_ASSMOD  */
  YYSYMBOL_T_ASSOR = 9,                    /* T_ASSOR  */
  YYSYMBOL_T_ASSAND = 10,                  /* T_ASSAND  */
  YYSYMBOL_T_ASSXOR = 11,                  /* T_ASSXOR  */
  YYSYMBOL_T_ASSLSHIFT = 12,               /* T_ASSLSHIFT  */
  YYSYMBOL_T_ASSRSHIFT = 13,               /* T_ASSRSHIFT  */
  YYSYMBOL_T_EXCLAM = 14,                  /* T_EXCLAM  */
  YYSYMBOL_T_INCREMENT = 15,               /* T_INCREMENT  */
  YYSYMBOL_T_DECREMENT = 16,               /* T_DECREMENT  */
  YYSYMBOL_T_PLUS = 17,                    /* T_PLUS  */
  YYSYMBOL_T_MINUS = 18,                   /* T_MINUS  */
  YYSYMBOL_T_MULT = 19,                    /* T_MULT  */
  YYSYMBOL_T_DIV = 20,                     /* T_DIV  */
  YYSYMBOL_T_MOD = 21,                     /* T_MOD  */
  YYSYMBOL_T_OR = 22,                      /* T_OR  */
  YYSYMBOL_T_XOR = 23,                     /* T_XOR  */
  YYSYMBOL_T_LSHIFT = 24,                  /* T_LSHIFT  */
  YYSYMBOL_T_RSHIFT = 25,                  /* T_RSHIFT  */
  YYSYMBOL_T_BOOL_AND = 26,                /* T_BOOL_AND  */
  YYSYMBOL_T_BOOL_OR = 27,                 /* T_BOOL_OR  */
  YYSYMBOL_T_KW_AND = 28,                  /* T_KW_AND  */
  YYSYMBOL_T_KW_OR = 29,                   /* T_KW_OR  */
  YYSYMBOL_T_KW_XOR = 30,                  /* T_KW_XOR  */
  YYSYMBOL_T_KW_IMPLY = 31,                /* T_KW_IMPLY  */
  YYSYMBOL_T_KW_NOT = 32,                  /* T_KW_NOT  */
  YYSYMBOL_T_SUP = 33,                     /* T_SUP  */
  YYSYMBOL_T_INF = 34,                     /* T_INF  */
  YYSYMBOL_T_ABS = 35,                     /* T_ABS  */
  YYSYMBOL_T_FABS = 36,                    /* T_FABS  */
  YYSYMBOL_T_FMOD = 37,                    /* T_FMOD  */
  YYSYMBOL_T_FMA = 38,                     /* T_FMA  */
  YYSYMBOL_T_FMAX = 39,                    /* T_FMAX  */
  YYSYMBOL_T_FMIN = 40,                    /* T_FMIN  */
  YYSYMBOL_T_FDIM = 41,                    /* T_FDIM  */
  YYSYMBOL_T_EXP = 42,                     /* T_EXP  */
  YYSYMBOL_T_EXP2 = 43,                    /* T_EXP2  */
  YYSYMBOL_T_EXPM1 = 44,                   /* T_EXPM1  */
  YYSYMBOL_T_LN = 45,                      /* T_LN  */
  YYSYMBOL_T_LOG = 46,                     /* T_LOG  */
  YYSYMBOL_T_LOG10 = 47,                   /* T_LOG10  */
  YYSYMBOL_T_LOG2 = 48,                    /* T_LOG2  */
  YYSYMBOL_T_LOG1P = 49,                   /* T_LOG1P  */
  YYSYMBOL_T_POW = 50,                     /* T_POW  */
  YYSYMBOL_T_SQRT = 51,                    /* T_SQRT  */
  YYSYMBOL_T_CBRT = 52,                    /* T_CBRT  */
  YYSYMBOL_T_HYPOT = 53,                   /* T_HYPOT  */
  YYSYMBOL_T_SIN = 54,                     /* T_SIN  */
  YYSYMBOL_T_COS = 55,                     /* T_COS  */
  YYSYMBOL_T_TAN = 56,                     /* T_TAN  */
  YYSYMBOL_T_ASIN = 57,                    /* T_ASIN  */
  YYSYMBOL_T_ACOS = 58,                    /* T_ACOS  */
  YYSYMBOL_T_ATAN = 59,                    /* T_ATAN  */
  YYSYMBOL_T_ATAN2 = 60,                   /* T_ATAN2  */
  YYSYMBOL_T_SINH = 61,                    /* T_SINH  */
  YYSYMBOL_T_COSH = 62,                    /* T_COSH  */
  YYSYMBOL_T_TANH = 63,                    /* T_TANH  */
  YYSYMBOL_T_ASINH = 64,                   /* T_ASINH  */
  YYSYMBOL_T_ACOSH = 65,                   /* T_ACOSH  */
  YYSYMBOL_T_ATANH = 66,                   /* T_ATANH  */
  YYSYMBOL_T_ERF = 67,                     /* T_ERF  */
  YYSYMBOL_T_ERFC = 68,                    /* T_ERFC  */
  YYSYMBOL_T_TGAMMA = 69,                  /* T_TGAMMA  */
  YYSYMBOL_T_LGAMMA = 70,                  /* T_LGAMMA  */
  YYSYMBOL_T_CEIL = 71,                    /* T_CEIL  */
  YYSYMBOL_T_FLOOR = 72,                   /* T_FLOOR  */
  YYSYMBOL_T_TRUNC = 73,                   /* T_TRUNC  */
  YYSYMBOL_T_ROUND = 74,                   /* T_ROUND  */
  YYSYMBOL_T_FINT = 75,                    /* T_FINT  */
  YYSYMBOL_T_LDEXP = 76,                   /* T_LDEXP  */
  YYSYMBOL_T_ILOGB = 77,                   /* T_ILOGB  */
  YYSYMBOL_T_LOGB = 78,                    /* T_LOGB  */
  YYSYMBOL_T_NEXTAFTER = 79,               /* T_NEXTAFTER  */
  YYSYMBOL_T_NEXTTOWARD = 80,              /* T_NEXTTOWARD  */
  YYSYMBOL_T_COPYSIGN = 81,                /* T_COPYSIGN  */
  YYSYMBOL_T_FPCLASSIFY = 82,              /* T_FPCLASSIFY  */
  YYSYMBOL_T_ISFINITE = 83,                /* T_ISFINITE  */
  YYSYMBOL_T_ISINF = 84,                   /* T_ISINF  */
  YYSYMBOL_T_ISNAN = 85,                   /* T_ISNAN  */
  YYSYMBOL_T_ISNORMAL = 86,                /* T_ISNORMAL  */
  YYSYMBOL_T_SIGNBIT = 87,                 /* T_SIGNBIT  */
  YYSYMBOL_T_ISUNORDERED = 88,             /* T_ISUNORDERED  */
  YYSYMBOL_T_RANDOM = 89,                  /* T_RANDOM  */
  YYSYMBOL_T_RANDOM_ARCSINE = 90,          /* T_RANDOM_ARCSINE  */
  YYSYMBOL_T_RANDOM_BETA = 91,             /* T_RANDOM_BETA  */
  YYSYMBOL_T_RANDOM_GAMMA = 92,            /* T_RANDOM_GAMMA  */
  YYSYMBOL_T_RANDOM_NORMAL = 93,           /* T_RANDOM_NORMAL  */
  YYSYMBOL_T_RANDOM_POISSON = 94,          /* T_RANDOM_POISSON  */
  YYSYMBOL_T_RANDOM_TRI = 95,              /* T_RANDOM_TRI  */
  YYSYMBOL_T_RANDOM_WEIBULL = 96,          /* T_RANDOM_WEIBULL  */
  YYSYMBOL_T_FORALL = 97,                  /* T_FORALL  */
  YYSYMBOL_T_EXISTS = 98,                  /* T_EXISTS  */
  YYSYMBOL_T_FOREACH = 99,                 /* T_FOREACH  */
  YYSYMBOL_T_SUM = 100,                    /* T_SUM  */
  YYSYMBOL_T_LT = 101,                     /* T_LT  */
  YYSYMBOL_T_LEQ = 102,                    /* T_LEQ  */
  YYSYMBOL_T_EQ = 103,                     /* T_EQ  */
  YYSYMBOL_T_NEQ = 104,                    /* T_NEQ  */
  YYSYMBOL_T_GEQ = 105,                    /* T_GEQ  */
  YYSYMBOL_T_GT = 106,                     /* T_GT  */
  YYSYMBOL_T_FOR = 107,                    /* T_FOR  */
  YYSYMBOL_T_WHILE = 108,                  /* T_WHILE  */
  YYSYMBOL_T_DO = 109,                     /* T_DO  */
  YYSYMBOL_T_BREAK = 110,                  /* T_BREAK  */
  YYSYMBOL_T_CONTINUE = 111,               /* T_CONTINUE  */
  YYSYMBOL_T_SWITCH = 112,                 /* T_SWITCH  */
  YYSYMBOL_T_IF = 113,                     /* T_IF  */
  YYSYMBOL_T_ELSE = 114,                   /* T_ELSE  */
  YYSYMBOL_T_CASE = 115,                   /* T_CASE  */
  YYSYMBOL_T_DEFAULT = 116,                /* T_DEFAULT  */
  YYSYMBOL_T_RETURN = 117,                 /* T_RETURN  */
  YYSYMBOL_T_ASSERT = 118,                 /* T_ASSERT  */
  YYSYMBOL_T_PRIORITY = 119,               /* T_PRIORITY  */
  YYSYMBOL_T_TYPEDEF = 120,                /* T_TYPEDEF  */
  YYSYMBOL_T_STRUCT = 121,                 /* T_STRUCT  */
  YYSYMBOL_T_CONST = 122,                  /* T_CONST  */
  YYSYMBOL_T_OLDCONST = 123,               /* T_OLDCONST  */
  YYSYMBOL_T_URGENT = 124,                 /* T_URGENT  */
  YYSYMBOL_T_BROADCAST = 125,              /* T_BROADCAST  */
  YYSYMBOL_T_TRUE = 126,                   /* T_TRUE  */
  YYSYMBOL_T_FALSE = 127,                  /* T_FALSE  */
  YYSYMBOL_T_META = 128,                   /* T_META  */
  YYSYMBOL_T_SYSTEM = 129,                 /* T_SYSTEM  */
  YYSYMBOL_T_PROCESS = 130,                /* T_PROCESS  */
  YYSYMBOL_T_STATE = 131,                  /* T_STATE  */
  YYSYMBOL_T_BRANCHPOINT = 132,            /* T_BRANCHPOINT  */
  YYSYMBOL_T_COMMIT = 133,                 /* T_COMMIT  */
  YYSYMBOL_T_INIT = 134,                   /* T_INIT  */
  YYSYMBOL_T_TRANS = 135,                  /* T_TRANS  */
  YYSYMBOL_T_SELECT = 136,                 /* T_SELECT  */
  YYSYMBOL_T_GUARD = 137,                  /* T_GUARD  */
  YYSYMBOL_T_SYNC = 138,                   /* T_SYNC  */
  YYSYMBOL_T_ASSIGN = 139,                 /* T_ASSIGN  */
  YYSYMBOL_T_PROBABILITY = 140,            /* T_PROBABILITY  */
  YYSYMBOL_T_BEFORE = 141,                 /* T_BEFORE  */
  YYSYMBOL_T_AFTER = 142,                  /* T_AFTER  */
  YYSYMBOL_T_PROGRESS = 143,               /* T_PROGRESS  */
  YYSYMBOL_T_ARROW = 144,                  /* T_ARROW  */
  YYSYMBOL_T_UNCONTROL_ARROW = 145,        /* T_UNCONTROL_ARROW  */
  YYSYMBOL_T_IO = 146,                     /* T_IO  */
  YYSYMBOL_T_QUERY = 147,                  /* T_QUERY  */
  YYSYMBOL_T_DEADLOCK = 148,               /* T_DEADLOCK  */
  YYSYMBOL_T_EF = 149,                     /* T_EF  */
  YYSYMBOL_T_EG = 150,                     /* T_EG  */
  YYSYMBOL_T_AF = 151,                     /* T_AF  */
  YYSYMBOL_T_AG = 152,                     /* T_AG  */
  YYSYMBOL_T_LEADSTO = 153,                /* T_LEADSTO  */
  YYSYMBOL_T_RESULTSET = 154,              /* T_RESULTSET  */
  YYSYMBOL_T_EF_PLUS = 155,                /* T_EF_PLUS  */
  YYSYMBOL_T_AG_PLUS = 156,                /* T_AG_PLUS  */
  YYSYMBOL_T_EF_MULT = 157,                /* T_EF_MULT  */
  YYSYMBOL_T_AG_MULT = 158,                /* T_AG_MULT  */
  YYSYMBOL_T_SCENARIO = 159,               /* T_SCENARIO  */
  YYSYMBOL_T_CONTROL = 160,                /* T_CONTROL  */
  YYSYMBOL_T_CONTROL_T = 161,              /* T_CONTROL_T  */
  YYSYMBOL_T_SIMULATION = 162,             /* T_SIMULATION  */
  YYSYMBOL_T_SIMULATE = 163,               /* T_SIMULATE  */
  YYSYMBOL_T_CONSISTENCY = 164,            /* T_CONSISTENCY  */
  YYSYMBOL_T_SPECIFICATION = 165,          /* T_SPECIFICATION  */
  YYSYMBOL_T_IMPLEMENTATION = 166,         /* T_IMPLEMENTATION  */
  YYSYMBOL_T_REFINEMENT = 167,             /* T_REFINEMENT  */
  YYSYMBOL_T_GANTT = 168,                  /* T_GANTT  */
  YYSYMBOL_T_PMAX = 169,                   /* T_PMAX  */
  YYSYMBOL_T_PROBA = 170,                  /* T_PROBA  */
  YYSYMBOL_T_DIAMOND = 171,                /* T_DIAMOND  */
  YYSYMBOL_T_BOX = 172,                    /* T_BOX  */
  YYSYMBOL_T_HASH = 173,                   /* T_HASH  */
  YYSYMBOL_T_ERROR = 174,                  /* T_ERROR  */
  YYSYMBOL_T_ID = 175,                     /* T_ID  */
  YYSYMBOL_T_TYPENAME = 176,               /* T_TYPENAME  */
  YYSYMBOL_T_NAT = 177,                    /* T_NAT  */
  YYSYMBOL_T_FLOATING = 178,               /* T_FLOATING  */
  YYSYMBOL_T_POS_NEG_MAX = 179,            /* T_POS_NEG_MAX  */
  YYSYMBOL_T_BOOL = 180,                   /* T_BOOL  */
  YYSYMBOL_T_INT = 181,                    /* T_INT  */
  YYSYMBOL_T_CHAN = 182,                   /* T_CHAN  */
  YYSYMBOL_T_CLOCK = 183,                  /* T_CLOCK  */
  YYSYMBOL_T_VOID = 184,                   /* T_VOID  */
  YYSYMBOL_T_SCALAR = 185,                 /* T_SCALAR  */
  YYSYMBOL_T_DOUBLE = 186,                 /* T_DOUBLE  */
  YYSYMBOL_T_NEW = 187,                    /* T_NEW  */
  YYSYMBOL_T_NEW_DECLARATION = 188,        /* T_NEW_DECLARATION  */
  YYSYMBOL_T_NEW_LOCAL_DECL = 189,         /* T_NEW_LOCAL_DECL  */
  YYSYMBOL_T_NEW_INST = 190,               /* T_NEW_INST  */
  YYSYMBOL_T_NEW_SYSTEM = 191,             /* T_NEW_SYSTEM  */
  YYSYMBOL_T_NEW_PARAMETERS = 192,         /* T_NEW_PARAMETERS  */
  YYSYMBOL_T_NEW_INVARIANT = 193,          /* T_NEW_INVARIANT  */
  YYSYMBOL_T_NEW_GUARD = 194,              /* T_NEW_GUARD  */
  YYSYMBOL_T_NEW_SYNC = 195,               /* T_NEW_SYNC  */
  YYSYMBOL_T_NEW_ASSIGN = 196,             /* T_NEW_ASSIGN  */
  YYSYMBOL_T_NEW_SELECT = 197,             /* T_NEW_SELECT  */
  YYSYMBOL_T_EXPONENTIALRATE = 198,        /* T_EXPONENTIALRATE  */
  YYSYMBOL_T_OLD = 199,                    /* T_OLD  */
  YYSYMBOL_T_OLD_DECLARATION = 200,        /* T_OLD_DECLARATION  */
  YYSYMBOL_T_OLD_LOCAL_DECL = 201,         /* T_OLD_LOCAL_DECL  */
  YYSYMBOL_T_OLD_INST = 202,               /* T_OLD_INST  */
  YYSYMBOL_T_OLD_PARAMETERS = 203,         /* T_OLD_PARAMETERS  */
  YYSYMBOL_T_OLD_INVARIANT = 204,          /* T_OLD_INVARIANT  */
  YYSYMBOL_T_OLD_GUARD = 205,              /* T_OLD_GUARD  */
  YYSYMBOL_T_OLD_ASSIGN = 206,             /* T_OLD_ASSIGN  */
  YYSYMBOL_T_PROPERTY = 207,               /* T_PROPERTY  */
  YYSYMBOL_T_EXPRESSION = 208,             /* T_EXPRESSION  */
  YYSYMBOL_T_EXPRESSION_LIST = 209,        /* T_EXPRESSION_LIST  */
  YYSYMBOL_T_XTA_PROCESS = 210,            /* T_XTA_PROCESS  */
  YYSYMBOL_T_INSTANCELINE = 211,           /* T_INSTANCELINE  */
  YYSYMBOL_T_MESSAGE = 212,                /* T_MESSAGE  */
  YYSYMBOL_T_UPDATE = 213,                 /* T_UPDATE  */
  YYSYMBOL_T_CONDITION = 214,              /* T_CONDITION  */
  YYSYMBOL_T_MITL_AND = 215,               /* T_MITL_AND  */
  YYSYMBOL_T_MITL_OR = 216,                /* T_MITL_OR  */
  YYSYMBOL_T_MITL_NEXT = 217,              /* T_MITL_NEXT  */
  YYSYMBOL_T_DYNAMIC = 218,                /* T_DYNAMIC  */
  YYSYMBOL_T_HYBRID = 219,                 /* T_HYBRID  */
  YYSYMBOL_T_SPAWN = 220,                  /* T_SPAWN  */
  YYSYMBOL_T_EXIT = 221,                   /* T_EXIT  */
  YYSYMBOL_T_NUMOF = 222,                  /* T_NUMOF  */
  YYSYMBOL_223_A_ = 223,                   /* 'A'  */
  YYSYMBOL_224_M_ = 224,                   /* 'M'  */
  YYSYMBOL_225_U_ = 225,                   /* 'U'  */
  YYSYMBOL_226_W_ = 226,                   /* 'W'  */
  YYSYMBOL_227_R_ = 227,                   /* 'R'  */
  YYSYMBOL_228_ = 228,                     /* '?'  */
  YYSYMBOL_229_ = 229,                     /* ':'  */
  YYSYMBOL_230_ = 230,                     /* '&'  */
  YYSYMBOL_T_MIN = 231,                    /* T_MIN  */
  YYSYMBOL_T_MAX = 232,                    /* T_MAX  */
  YYSYMBOL_UOPERATOR = 233,                /* UOPERATOR  */
  YYSYMBOL_234_ = 234,                     /* '('  */
  YYSYMBOL_235_ = 235,                     /* ')'  */
  YYSYMBOL_236_ = 236,                     /* '['  */
  YYSYMBOL_237_ = 237,                     /* ']'  */
  YYSYMBOL_238_ = 238,                     /* '.'  */
  YYSYMBOL_239_ = 239,                     /* '\''  */
  YYSYMBOL_240_ = 240,                     /* ';'  */
  YYSYMBOL_241_ = 241,                     /* ','  */
  YYSYMBOL_242_ = 242,                     /* '{'  */
  YYSYMBOL_243_ = 243,                     /* '}'  */
  YYSYMBOL_244_E_ = 244,                   /* 'E'  */
  YYSYMBOL_245_n_ = 245,                   /* '\n'  */
  YYSYMBOL_246_ = 246,                     /* '\\'  */
  YYSYMBOL_YYACCEPT = 247,                 /* $accept  */
  YYSYMBOL_Uppaal = 248,                   /* Uppaal  */
  YYSYMBOL_XTA = 249,                      /* XTA  */
  YYSYMBOL_Instantiations = 250,           /* Instantiations  */
  YYSYMBOL_Instantiation = 251,            /* Instantiation  */
  YYSYMBOL_252_1 = 252,                    /* $@1  */
  YYSYMBOL_InstanceLineExpression = 253,   /* InstanceLineExpression  */
  YYSYMBOL_254_2 = 254,                    /* $@2  */
  YYSYMBOL_OptionalInstanceParameterList = 255, /* OptionalInstanceParameterList  */
  YYSYMBOL_System = 256,                   /* System  */
  YYSYMBOL_PriorityDecl = 257,             /* PriorityDecl  */
  YYSYMBOL_ChannelList = 258,              /* ChannelList  */
  YYSYMBOL_ChanElement = 259,              /* ChanElement  */
  YYSYMBOL_ChanExpression = 260,           /* ChanExpression  */
  YYSYMBOL_SysDecl = 261,                  /* SysDecl  */
  YYSYMBOL_IODecl = 262,                   /* IODecl  */
  YYSYMBOL_SyncExprList = 263,             /* SyncExprList  */
  YYSYMBOL_IOSyncExpr = 264,               /* IOSyncExpr  */
  YYSYMBOL_ProcessList = 265,              /* ProcessList  */
  YYSYMBOL_ProcLessThan = 266,             /* ProcLessThan  */
  YYSYMBOL_Progress = 267,                 /* Progress  */
  YYSYMBOL_ProgressMeasureList = 268,      /* ProgressMeasureList  */
  YYSYMBOL_GanttDecl = 269,                /* GanttDecl  */
  YYSYMBOL_GanttDef = 270,                 /* GanttDef  */
  YYSYMBOL_271_3 = 271,                    /* $@3  */
  YYSYMBOL_GanttArgs = 272,                /* GanttArgs  */
  YYSYMBOL_GanttDeclSelect = 273,          /* GanttDeclSelect  */
  YYSYMBOL_GanttExprList = 274,            /* GanttExprList  */
  YYSYMBOL_GanttExpr = 275,                /* GanttExpr  */
  YYSYMBOL_276_4 = 276,                    /* $@4  */
  YYSYMBOL_GanttEntrySelect = 277,         /* GanttEntrySelect  */
  YYSYMBOL_Declarations = 278,             /* Declarations  */
  YYSYMBOL_DynamicDeclaration = 279,       /* DynamicDeclaration  */
  YYSYMBOL_280_5 = 280,                    /* $@5  */
  YYSYMBOL_BeforeUpdateDecl = 281,         /* BeforeUpdateDecl  */
  YYSYMBOL_AfterUpdateDecl = 282,          /* AfterUpdateDecl  */
  YYSYMBOL_FunctionDecl = 283,             /* FunctionDecl  */
  YYSYMBOL_284_6 = 284,                    /* $@6  */
  YYSYMBOL_EndBlock = 285,                 /* EndBlock  */
  YYSYMBOL_OptionalParameterList = 286,    /* OptionalParameterList  */
  YYSYMBOL_ParameterList = 287,            /* ParameterList  */
  YYSYMBOL_Parameter = 288,                /* Parameter  */
  YYSYMBOL_VariableDecl = 289,             /* VariableDecl  */
  YYSYMBOL_DeclIdList = 290,               /* DeclIdList  */
  YYSYMBOL_DeclId = 291,                   /* DeclId  */
  YYSYMBOL_292_7 = 292,                    /* $@7  */
  YYSYMBOL_VarInit = 293,                  /* VarInit  */
  YYSYMBOL_Initializer = 294,              /* Initializer  */
  YYSYMBOL_FieldInitList = 295,            /* FieldInitList  */
  YYSYMBOL_FieldInit = 296,                /* FieldInit  */
  YYSYMBOL_ArrayDecl = 297,                /* ArrayDecl  */
  YYSYMBOL_298_8 = 298,                    /* $@8  */
  YYSYMBOL_ArrayDecl2 = 299,               /* ArrayDecl2  */
  YYSYMBOL_300_9 = 300,                    /* $@9  */
  YYSYMBOL_TypeDecl = 301,                 /* TypeDecl  */
  YYSYMBOL_TypeIdList = 302,               /* TypeIdList  */
  YYSYMBOL_TypeId = 303,                   /* TypeId  */
  YYSYMBOL_304_10 = 304,                   /* $@10  */
  YYSYMBOL_Type = 305,                     /* Type  */
  YYSYMBOL_Id = 306,                       /* Id  */
  YYSYMBOL_NonTypeId = 307,                /* NonTypeId  */
  YYSYMBOL_FieldDeclList = 308,            /* FieldDeclList  */
  YYSYMBOL_FieldDecl = 309,                /* FieldDecl  */
  YYSYMBOL_FieldDeclIdList = 310,          /* FieldDeclIdList  */
  YYSYMBOL_FieldDeclId = 311,              /* FieldDeclId  */
  YYSYMBOL_312_11 = 312,                   /* $@11  */
  YYSYMBOL_TypePrefix = 313,               /* TypePrefix  */
  YYSYMBOL_ProcDecl = 314,                 /* ProcDecl  */
  YYSYMBOL_315_12 = 315,                   /* $@12  */
  YYSYMBOL_ProcBody = 316,                 /* ProcBody  */
  YYSYMBOL_ProcLocalDeclList = 317,        /* ProcLocalDeclList  */
  YYSYMBOL_States = 318,                   /* States  */
  YYSYMBOL_StateDeclList = 319,            /* StateDeclList  */
  YYSYMBOL_StateDecl = 320,                /* StateDecl  */
  YYSYMBOL_Branchpoints = 321,             /* Branchpoints  */
  YYSYMBOL_BranchpointDeclList = 322,      /* BranchpointDeclList  */
  YYSYMBOL_BranchpointDecl = 323,          /* BranchpointDecl  */
  YYSYMBOL_Init = 324,                     /* Init  */
  YYSYMBOL_Transitions = 325,              /* Transitions  */
  YYSYMBOL_TransitionList = 326,           /* TransitionList  */
  YYSYMBOL_Transition = 327,               /* Transition  */
  YYSYMBOL_328_13 = 328,                   /* $@13  */
  YYSYMBOL_329_14 = 329,                   /* $@14  */
  YYSYMBOL_TransitionOpt = 330,            /* TransitionOpt  */
  YYSYMBOL_331_15 = 331,                   /* $@15  */
  YYSYMBOL_332_16 = 332,                   /* $@16  */
  YYSYMBOL_Select = 333,                   /* Select  */
  YYSYMBOL_SelectList = 334,               /* SelectList  */
  YYSYMBOL_Guard = 335,                    /* Guard  */
  YYSYMBOL_Sync = 336,                     /* Sync  */
  YYSYMBOL_SyncExpr = 337,                 /* SyncExpr  */
  YYSYMBOL_MessExpr = 338,                 /* MessExpr  */
  YYSYMBOL_Assign = 339,                   /* Assign  */
  YYSYMBOL_Probability = 340,              /* Probability  */
  YYSYMBOL_LocFlags = 341,                 /* LocFlags  */
  YYSYMBOL_Commit = 342,                   /* Commit  */
  YYSYMBOL_Urgent = 343,                   /* Urgent  */
  YYSYMBOL_CStateList = 344,               /* CStateList  */
  YYSYMBOL_UStateList = 345,               /* UStateList  */
  YYSYMBOL_ExpRate = 346,                  /* ExpRate  */
  YYSYMBOL_Block = 347,                    /* Block  */
  YYSYMBOL_348_17 = 348,                   /* $@17  */
  YYSYMBOL_BlockLocalDeclList = 349,       /* BlockLocalDeclList  */
  YYSYMBOL_StatementList = 350,            /* StatementList  */
  YYSYMBOL_Statement = 351,                /* Statement  */
  YYSYMBOL_IfCondition = 352,              /* IfCondition  */
  YYSYMBOL_353_18 = 353,                   /* $@18  */
  YYSYMBOL_IfConditionThenMatched = 354,   /* IfConditionThenMatched  */
  YYSYMBOL_MatchedStatement = 355,         /* MatchedStatement  */
  YYSYMBOL_UnmatchedStatement = 356,       /* UnmatchedStatement  */
  YYSYMBOL_OtherStatement = 357,           /* OtherStatement  */
  YYSYMBOL_358_19 = 358,                   /* $@19  */
  YYSYMBOL_ForStatement = 359,             /* ForStatement  */
  YYSYMBOL_360_20 = 360,                   /* $@20  */
  YYSYMBOL_361_21 = 361,                   /* $@21  */
  YYSYMBOL_WhileStatement = 362,           /* WhileStatement  */
  YYSYMBOL_363_22 = 363,                   /* $@22  */
  YYSYMBOL_364_23 = 364,                   /* $@23  */
  YYSYMBOL_SwitchCaseList = 365,           /* SwitchCaseList  */
  YYSYMBOL_SwitchCase = 366,               /* SwitchCase  */
  YYSYMBOL_367_24 = 367,                   /* $@24  */
  YYSYMBOL_368_25 = 368,                   /* $@25  */
  YYSYMBOL_ExprList = 369,                 /* ExprList  */
  YYSYMBOL_Expression = 370,               /* Expression  */
  YYSYMBOL_371_26 = 371,                   /* $@26  */
  YYSYMBOL_372_27 = 372,                   /* $@27  */
  YYSYMBOL_373_28 = 373,                   /* $@28  */
  YYSYMBOL_374_29 = 374,                   /* $@29  */
  YYSYMBOL_375_30 = 375,                   /* $@30  */
  YYSYMBOL_376_31 = 376,                   /* $@31  */
  YYSYMBOL_DynamicExpression = 377,        /* DynamicExpression  */
  YYSYMBOL_378_32 = 378,                   /* $@32  */
  YYSYMBOL_379_33 = 379,                   /* $@33  */
  YYSYMBOL_380_34 = 380,                   /* $@34  */
  YYSYMBOL_381_35 = 381,                   /* $@35  */
  YYSYMBOL_382_36 = 382,                   /* $@36  */
  YYSYMBOL_Assignment = 383,               /* Assignment  */
  YYSYMBOL_AssignOp = 384,                 /* AssignOp  */
  YYSYMBOL_UnaryOp = 385,                  /* UnaryOp  */
  YYSYMBOL_BuiltinFunction1 = 386,         /* BuiltinFunction1  */
  YYSYMBOL_BuiltinFunction2 = 387,         /* BuiltinFunction2  */
  YYSYMBOL_BuiltinFunction3 = 388,         /* BuiltinFunction3  */
  YYSYMBOL_ArgList = 389,                  /* ArgList  */
  YYSYMBOL_OldXTA = 390,                   /* OldXTA  */
  YYSYMBOL_OldDeclaration = 391,           /* OldDeclaration  */
  YYSYMBOL_OldVarDecl = 392,               /* OldVarDecl  */
  YYSYMBOL_393_37 = 393,                   /* $@37  */
  YYSYMBOL_OldConstDeclIdList = 394,       /* OldConstDeclIdList  */
  YYSYMBOL_OldConstDeclId = 395,           /* OldConstDeclId  */
  YYSYMBOL_396_38 = 396,                   /* $@38  */
  YYSYMBOL_OldProcDecl = 397,              /* OldProcDecl  */
  YYSYMBOL_398_39 = 398,                   /* $@39  */
  YYSYMBOL_399_40 = 399,                   /* $@40  */
  YYSYMBOL_400_41 = 400,                   /* $@41  */
  YYSYMBOL_401_42 = 401,                   /* $@42  */
  YYSYMBOL_402_43 = 402,                   /* $@43  */
  YYSYMBOL_OldProcParams = 403,            /* OldProcParams  */
  YYSYMBOL_OldProcParamList = 404,         /* OldProcParamList  */
  YYSYMBOL_OldProcParam = 405,             /* OldProcParam  */
  YYSYMBOL_406_44 = 406,                   /* $@44  */
  YYSYMBOL_407_45 = 407,                   /* $@45  */
  YYSYMBOL_OldProcConstParam = 408,        /* OldProcConstParam  */
  YYSYMBOL_409_46 = 409,                   /* $@46  */
  YYSYMBOL_410_47 = 410,                   /* $@47  */
  YYSYMBOL_OldProcBody = 411,              /* OldProcBody  */
  YYSYMBOL_OldVarDeclList = 412,           /* OldVarDeclList  */
  YYSYMBOL_OldStates = 413,                /* OldStates  */
  YYSYMBOL_OldStateDeclList = 414,         /* OldStateDeclList  */
  YYSYMBOL_OldStateDecl = 415,             /* OldStateDecl  */
  YYSYMBOL_OldInvariant = 416,             /* OldInvariant  */
  YYSYMBOL_OldTransitions = 417,           /* OldTransitions  */
  YYSYMBOL_OldTransitionList = 418,        /* OldTransitionList  */
  YYSYMBOL_OldTransition = 419,            /* OldTransition  */
  YYSYMBOL_420_48 = 420,                   /* $@48  */
  YYSYMBOL_OldTransitionOpt = 421,         /* OldTransitionOpt  */
  YYSYMBOL_422_49 = 422,                   /* $@49  */
  YYSYMBOL_OldGuard = 423,                 /* OldGuard  */
  YYSYMBOL_OldGuardList = 424,             /* OldGuardList  */
  YYSYMBOL_PropertyList = 425,             /* PropertyList  */
  YYSYMBOL_PropertyList2 = 426,            /* PropertyList2  */
  YYSYMBOL_QueryList = 427,                /* QueryList  */
  YYSYMBOL_Query = 428,                    /* Query  */
  YYSYMBOL_BoolOrKWAnd = 429,              /* BoolOrKWAnd  */
  YYSYMBOL_SubProperty = 430,              /* SubProperty  */
  YYSYMBOL_PropertyExpr = 431,             /* PropertyExpr  */
  YYSYMBOL_MITLExpression = 432,           /* MITLExpression  */
  YYSYMBOL_SMCBounds = 433,                /* SMCBounds  */
  YYSYMBOL_BoundType = 434,                /* BoundType  */
  YYSYMBOL_435_50 = 435,                   /* $@50  */
  YYSYMBOL_436_51 = 436,                   /* $@51  */
  YYSYMBOL_CmpGLE = 437,                   /* CmpGLE  */
  YYSYMBOL_PathType = 438,                 /* PathType  */
  YYSYMBOL_TIOSystem = 439,                /* TIOSystem  */
  YYSYMBOL_IdExpr = 440,                   /* IdExpr  */
  YYSYMBOL_TIOStructComposition = 441,     /* TIOStructComposition  */
  YYSYMBOL_TIOComposition = 442,           /* TIOComposition  */
  YYSYMBOL_TIOConjunction = 443,           /* TIOConjunction  */
  YYSYMBOL_TIOQuotient = 444,              /* TIOQuotient  */
  YYSYMBOL_TIOStructCompositionList = 445, /* TIOStructCompositionList  */
  YYSYMBOL_TIOCompositionList = 446,       /* TIOCompositionList  */
  YYSYMBOL_TIOConjunctionList = 447,       /* TIOConjunctionList  */
  YYSYMBOL_TIOOptionalProperty = 448,      /* TIOOptionalProperty  */
  YYSYMBOL_RestrictionList = 449,          /* RestrictionList  */
  YYSYMBOL_SysComposition = 450,           /* SysComposition  */
  YYSYMBOL_DeclComposition = 451,          /* DeclComposition  */
  YYSYMBOL_BracketExprList = 452,          /* BracketExprList  */
  YYSYMBOL_ExpressionList = 453,           /* ExpressionList  */
  YYSYMBOL_NonEmptyExpressionList = 454,   /* NonEmptyExpressionList  */
  YYSYMBOL_SupPrefix = 455,                /* SupPrefix  */
  YYSYMBOL_InfPrefix = 456,                /* InfPrefix  */
  YYSYMBOL_Property = 457                  /* Property  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  199
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   12460

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  247
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  211
/* YYNRULES -- Number of rules.  */
#define YYNRULES  627
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1266

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   480


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     245,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   230,   239,
     234,   235,     2,     2,   241,     2,   238,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   229,   240,
       2,     2,     2,   228,     2,   223,     2,     2,     2,   244,
       2,     2,     2,     2,     2,     2,     2,   224,     2,     2,
       2,     2,   227,     2,     2,   225,     2,   226,     2,     2,
       2,   236,   246,   237,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   242,     2,   243,     2,     2,     2,     2,
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
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   231,   232,
     233
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   318,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,   340,   341,   342,   344,   345,   346,
     347,   351,   354,   356,   357,   361,   361,   368,   371,   371,
     378,   379,   382,   386,   389,   390,   394,   395,   396,   401,
     402,   406,   407,   411,   412,   415,   417,   422,   423,   430,
     433,   436,   439,   442,   448,   449,   450,   454,   456,   458,
     460,   462,   465,   469,   471,   474,   476,   476,   481,   483,
     487,   490,   496,   497,   501,   505,   505,   510,   513,   518,
     520,   521,   522,   523,   524,   525,   526,   527,   528,   529,
     533,   533,   535,   537,   548,   548,   554,   554,   557,   558,
     559,   563,   564,   568,   571,   577,   583,   584,   588,   588,
     596,   597,   601,   602,   608,   609,   613,   616,   622,   622,
     624,   626,   627,   627,   628,   632,   635,   639,   640,   644,
     644,   652,   655,   658,   661,   664,   667,   670,   673,   676,
     679,   682,   685,   688,   692,   695,   698,   701,   704,   707,
     710,   714,   720,   721,   725,   726,   727,   728,   729,   730,
     731,   732,   733,   734,   735,   736,   737,   738,   742,   743,
     747,   754,   755,   759,   759,   767,   768,   769,   770,   771,
     779,   779,   788,   789,   790,   793,   795,   796,   797,   801,
     802,   806,   807,   811,   812,   815,   818,   821,   827,   828,
     832,   833,   837,   842,   845,   848,   850,   851,   855,   856,
     860,   860,   866,   866,   875,   875,   880,   880,   885,   888,
     890,   894,   897,   902,   904,   907,   910,   913,   915,   916,
     920,   923,   926,   929,   932,   938,   941,   946,   948,   951,
     954,   956,   959,   962,   964,   965,   969,   970,   974,   975,
     979,   982,   988,   991,   997,   998,  1007,  1007,  1015,  1017,
    1018,  1021,  1023,  1024,  1027,  1028,  1031,  1031,  1033,  1035,
    1038,  1041,  1045,  1051,  1052,  1055,  1058,  1059,  1060,  1063,
    1066,  1066,  1072,  1075,  1078,  1083,  1083,  1089,  1089,  1095,
    1098,  1098,  1104,  1105,  1105,  1113,  1114,  1118,  1118,  1124,
    1124,  1133,  1134,  1139,  1142,  1145,  1148,  1151,  1154,  1157,
    1160,  1163,  1163,  1168,  1168,  1173,  1176,  1179,  1180,  1183,
    1186,  1189,  1192,  1195,  1198,  1201,  1204,  1207,  1210,  1213,
    1216,  1219,  1222,  1225,  1228,  1231,  1234,  1237,  1240,  1243,
    1246,  1249,  1252,  1255,  1258,  1261,  1264,  1267,  1267,  1272,
    1275,  1278,  1281,  1284,  1287,  1287,  1292,  1292,  1297,  1297,
    1302,  1303,  1304,  1308,  1308,  1313,  1316,  1320,  1320,  1326,
    1326,  1332,  1332,  1338,  1338,  1348,  1354,  1355,  1356,  1357,
    1358,  1359,  1360,  1361,  1362,  1363,  1364,  1369,  1370,  1371,
    1372,  1376,  1377,  1378,  1379,  1380,  1381,  1382,  1383,  1384,
    1385,  1386,  1387,  1388,  1389,  1390,  1391,  1392,  1393,  1394,
    1395,  1396,  1397,  1398,  1399,  1400,  1401,  1402,  1403,  1404,
    1405,  1406,  1407,  1408,  1409,  1410,  1411,  1412,  1413,  1414,
    1415,  1416,  1417,  1418,  1419,  1423,  1424,  1425,  1426,  1427,
    1428,  1429,  1430,  1431,  1432,  1433,  1434,  1435,  1436,  1437,
    1441,  1442,  1447,  1448,  1451,  1461,  1464,  1466,  1467,  1471,
    1472,  1472,  1477,  1480,  1481,  1485,  1485,  1496,  1496,  1502,
    1502,  1508,  1508,  1514,  1514,  1520,  1520,  1529,  1530,  1531,
    1535,  1538,  1539,  1542,  1546,  1546,  1551,  1551,  1559,  1559,
    1564,  1564,  1572,  1575,  1577,  1581,  1582,  1586,  1587,  1591,
    1594,  1600,  1601,  1603,  1608,  1610,  1611,  1615,  1616,  1620,
    1620,  1630,  1630,  1635,  1638,  1640,  1643,  1649,  1650,  1656,
    1658,  1660,  1663,  1665,  1669,  1670,  1674,  1674,  1677,  1680,
    1685,  1688,  1691,  1694,  1697,  1700,  1706,  1709,  1713,  1717,
    1722,  1726,  1730,  1734,  1738,  1742,  1746,  1750,  1754,  1758,
    1762,  1766,  1769,  1773,  1777,  1783,  1787,  1792,  1796,  1801,
    1805,  1809,  1813,  1817,  1824,  1827,  1830,  1833,  1836,  1842,
    1845,  1850,  1850,  1851,  1851,  1852,  1856,  1857,  1861,  1862,
    1866,  1871,  1874,  1877,  1880,  1883,  1889,  1895,  1901,  1907,
    1913,  1919,  1920,  1924,  1925,  1929,  1930,  1934,  1938,  1943,
    1947,  1954,  1958,  1963,  1967,  1973,  1982,  1983,  1987,  1988,
    1992,  1995,  1999,  2002,  2005,  2007,  2008,  2013
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "T_ASSIGNMENT",
  "T_ASSPLUS", "T_ASSMINUS", "T_ASSMULT", "T_ASSDIV", "T_ASSMOD",
  "T_ASSOR", "T_ASSAND", "T_ASSXOR", "T_ASSLSHIFT", "T_ASSRSHIFT",
  "T_EXCLAM", "T_INCREMENT", "T_DECREMENT", "T_PLUS", "T_MINUS", "T_MULT",
  "T_DIV", "T_MOD", "T_OR", "T_XOR", "T_LSHIFT", "T_RSHIFT", "T_BOOL_AND",
  "T_BOOL_OR", "T_KW_AND", "T_KW_OR", "T_KW_XOR", "T_KW_IMPLY", "T_KW_NOT",
  "T_SUP", "T_INF", "T_ABS", "T_FABS", "T_FMOD", "T_FMA", "T_FMAX",
  "T_FMIN", "T_FDIM", "T_EXP", "T_EXP2", "T_EXPM1", "T_LN", "T_LOG",
  "T_LOG10", "T_LOG2", "T_LOG1P", "T_POW", "T_SQRT", "T_CBRT", "T_HYPOT",
  "T_SIN", "T_COS", "T_TAN", "T_ASIN", "T_ACOS", "T_ATAN", "T_ATAN2",
  "T_SINH", "T_COSH", "T_TANH", "T_ASINH", "T_ACOSH", "T_ATANH", "T_ERF",
  "T_ERFC", "T_TGAMMA", "T_LGAMMA", "T_CEIL", "T_FLOOR", "T_TRUNC",
  "T_ROUND", "T_FINT", "T_LDEXP", "T_ILOGB", "T_LOGB", "T_NEXTAFTER",
  "T_NEXTTOWARD", "T_COPYSIGN", "T_FPCLASSIFY", "T_ISFINITE", "T_ISINF",
  "T_ISNAN", "T_ISNORMAL", "T_SIGNBIT", "T_ISUNORDERED", "T_RANDOM",
  "T_RANDOM_ARCSINE", "T_RANDOM_BETA", "T_RANDOM_GAMMA", "T_RANDOM_NORMAL",
  "T_RANDOM_POISSON", "T_RANDOM_TRI", "T_RANDOM_WEIBULL", "T_FORALL",
  "T_EXISTS", "T_FOREACH", "T_SUM", "T_LT", "T_LEQ", "T_EQ", "T_NEQ",
  "T_GEQ", "T_GT", "T_FOR", "T_WHILE", "T_DO", "T_BREAK", "T_CONTINUE",
  "T_SWITCH", "T_IF", "T_ELSE", "T_CASE", "T_DEFAULT", "T_RETURN",
  "T_ASSERT", "T_PRIORITY", "T_TYPEDEF", "T_STRUCT", "T_CONST",
  "T_OLDCONST", "T_URGENT", "T_BROADCAST", "T_TRUE", "T_FALSE", "T_META",
  "T_SYSTEM", "T_PROCESS", "T_STATE", "T_BRANCHPOINT", "T_COMMIT",
  "T_INIT", "T_TRANS", "T_SELECT", "T_GUARD", "T_SYNC", "T_ASSIGN",
  "T_PROBABILITY", "T_BEFORE", "T_AFTER", "T_PROGRESS", "T_ARROW",
  "T_UNCONTROL_ARROW", "T_IO", "T_QUERY", "T_DEADLOCK", "T_EF", "T_EG",
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
  "T_EXPRESSION_LIST", "T_XTA_PROCESS", "T_INSTANCELINE", "T_MESSAGE",
  "T_UPDATE", "T_CONDITION", "T_MITL_AND", "T_MITL_OR", "T_MITL_NEXT",
  "T_DYNAMIC", "T_HYBRID", "T_SPAWN", "T_EXIT", "T_NUMOF", "'A'", "'M'",
  "'U'", "'W'", "'R'", "'?'", "':'", "'&'", "T_MIN", "T_MAX", "UOPERATOR",
  "'('", "')'", "'['", "']'", "'.'", "'\\''", "';'", "','", "'{'", "'}'",
  "'E'", "'\\n'", "'\\\\'", "$accept", "Uppaal", "XTA", "Instantiations",
  "Instantiation", "$@1", "InstanceLineExpression", "$@2",
  "OptionalInstanceParameterList", "System", "PriorityDecl", "ChannelList",
  "ChanElement", "ChanExpression", "SysDecl", "IODecl", "SyncExprList",
  "IOSyncExpr", "ProcessList", "ProcLessThan", "Progress",
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
  "States", "StateDeclList", "StateDecl", "Branchpoints",
  "BranchpointDeclList", "BranchpointDecl", "Init", "Transitions",
  "TransitionList", "Transition", "$@13", "$@14", "TransitionOpt", "$@15",
  "$@16", "Select", "SelectList", "Guard", "Sync", "SyncExpr", "MessExpr",
  "Assign", "Probability", "LocFlags", "Commit", "Urgent", "CStateList",
  "UStateList", "ExpRate", "Block", "$@17", "BlockLocalDeclList",
  "StatementList", "Statement", "IfCondition", "$@18",
  "IfConditionThenMatched", "MatchedStatement", "UnmatchedStatement",
  "OtherStatement", "$@19", "ForStatement", "$@20", "$@21",
  "WhileStatement", "$@22", "$@23", "SwitchCaseList", "SwitchCase", "$@24",
  "$@25", "ExprList", "Expression", "$@26", "$@27", "$@28", "$@29", "$@30",
  "$@31", "DynamicExpression", "$@32", "$@33", "$@34", "$@35", "$@36",
  "Assignment", "AssignOp", "UnaryOp", "BuiltinFunction1",
  "BuiltinFunction2", "BuiltinFunction3", "ArgList", "OldXTA",
  "OldDeclaration", "OldVarDecl", "$@37", "OldConstDeclIdList",
  "OldConstDeclId", "$@38", "OldProcDecl", "$@39", "$@40", "$@41", "$@42",
  "$@43", "OldProcParams", "OldProcParamList", "OldProcParam", "$@44",
  "$@45", "OldProcConstParam", "$@46", "$@47", "OldProcBody",
  "OldVarDeclList", "OldStates", "OldStateDeclList", "OldStateDecl",
  "OldInvariant", "OldTransitions", "OldTransitionList", "OldTransition",
  "$@48", "OldTransitionOpt", "$@49", "OldGuard", "OldGuardList",
  "PropertyList", "PropertyList2", "QueryList", "Query", "BoolOrKWAnd",
  "SubProperty", "PropertyExpr", "MITLExpression", "SMCBounds",
  "BoundType", "$@50", "$@51", "CmpGLE", "PathType", "TIOSystem", "IdExpr",
  "TIOStructComposition", "TIOComposition", "TIOConjunction",
  "TIOQuotient", "TIOStructCompositionList", "TIOCompositionList",
  "TIOConjunctionList", "TIOOptionalProperty", "RestrictionList",
  "SysComposition", "DeclComposition", "BracketExprList", "ExpressionList",
  "NonEmptyExpressionList", "SupPrefix", "InfPrefix", "Property", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
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
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   440,   441,   442,   443,   444,
     445,   446,   447,   448,   449,   450,   451,   452,   453,   454,
     455,   456,   457,   458,   459,   460,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   472,   473,   474,
     475,   476,   477,    65,    77,    85,    87,    82,    63,    58,
      38,   478,   479,   480,    40,    41,    91,    93,    46,    39,
      59,    44,   123,   125,    69,    10,    92
};
#endif

#define YYPACT_NINF (-1135)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-625)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    4124, 11545,  4882,  1191, -1135,  1191,  4882,  3932, 11545, 11545,
   11545, 11545,  2592, 11545, -1135, -1135, -1135,    49,  3504, 11545,
   11545, 11545, -1135, 11545, 11545,   -24,  3020, 11545, 11545, 11545,
     127, -1135, 11545, 11545, -1135,   -40, -1135, -1135, -1135, -1135,
   -1135, -1135, -1135, -1135, -1135, -1135, -1135, -1135, -1135, -1135,
   -1135, -1135, -1135, -1135, -1135, -1135, -1135, -1135, -1135, -1135,
   -1135, -1135, -1135, -1135, -1135, -1135, -1135, -1135, -1135, -1135,
   -1135, -1135, -1135, -1135, -1135, -1135, -1135, -1135, -1135, -1135,
   -1135, -1135, -1135, -1135, -1135, -1135, -1135, -1135, -1135, -1135,
   -1135, -1135, -1135, -1135, -1135, -1135, -1135, -1135, -1135, -1135,
     -58,   -12,     7,    21, -1135, -1135, -1135, -1135, -1135, -1135,
   -1135, -1135, -1135, -1135, -1135,  3020,    45,    57, -1135, -1135,
   -1135, -1135, -1135,  3062, -1135, -1135,  8751, -1135, -1135, 11545,
      65,   109,   120, -1135,   -82, -1135, 12044, 12111,  3290, 12111,
   -1135,   -42, -1135,   158, -1135, -1135, -1135, -1135,   178, -1135,
   -1135, -1135,   189, -1135,   247,   153, -1135,  1958,   211,  8751,
    8751, -1135,  5124,   195,  8751, -1135,   222, -1135,   199, -1135,
    6524, -1135,  1163,  2648,  3718,   207,  3020, -1135, -1135,   214,
     215,   220,  1506,   238,  8751,   240,   195, -1135,  8977,  8751,
     195,  2592, -1135, -1135,   248, -1135,  5371,   195,  8751, -1135,
     147,   147, -1135,  2592,  2592,  2592,  2592, -1135,   249,  3020,
     252,   250,   253, 11545,  6353, -1135, -1135, -1135, -1135, -1135,
   -1135, -1135, -1135, -1135, -1135, -1135, -1135, -1135, 11545, 11545,
   11545, 11545, 11545, 11545, 11545, 11545, 11545, 11545, 11545, 11545,
   11545, 11545, -1135, 11545, 11545, 11545, 11545, 11545, 11545, 11545,
   11545, 11545, 11545,   487,  3704,  3020, -1135, 11545,   147, 11545,
   11545, 11545, -1135,  1475,   344,   254,   256,   371,  3020, -1135,
   -1135, -1135, -1135, -1135, -1135, -1135, -1135, -1135, -1135,  2592,
     257, -1135, -1135, -1135, -1135,  2010, -1135, 11545, 11545, -1135,
    3932,  3020, -1135,   260, -1135, -1135,   258, -1135,   263, -1135,
      37, -1135, 11545, 11545,  3932,  2592, 11545,   482,   251, 12150,
   -1135,  2592, -1135, -1135, -1135, -1135, -1135,  3020,  3020,  3504,
     262, -1135,   266, 11545, 11545,  -149,  -130, 10261, 11545, 11545,
   11759, 11545, 11545,   264,   -81,   485,   285,   281,   289,   293,
     298,   300, 11545, 10475,   294, 11545,   281,  6631, -1135, -1135,
     365, 11545, 11545,   286,   301, -1135, -1135,   303,   305,   307,
     308,   304, -1135,   306, -1135,   362,   363,  6663,   309,   310,
   -1135,   125,   125,   147,   147,   147,  1685,  1697,   387,   387,
    1544,  1444,  1544,  1444,  1444, 11545,   771,   771,  3148,  3148,
     771,   771,  6770,  1864,   100,   100, 11545,   541,   312,  6802,
   -1135,  8751,  6909,  5542,  5651,   311,  2592,   314,   -66, -1135,
   11545, 11545,   146,   301,   396,    14,  -177, -1135,   301,  5084,
     544,   317,  2592,  1453, -1135,  5683,  6941, -1135, -1135, -1135,
     325,  2438, 11545, 11545, -1135, -1135,  8751, -1135,   315,  8751,
     323,  3020,   322,    56, -1135, -1135, -1135, -1135,   215,   220,
    3020,  3020, -1135,  8751,  8751, -1135, 11545, -1135, 11545,   336,
    8751,  8751,  8751,  3062,  8751,  8751,  8751,  3020,  9405,  9619,
    -138,  2805,  9619,   324,  2817,  2817,  2817,  2817,  8751,  8751,
     338, 11545,  8751,   339,   340,   345, 11545,   358,   340,   340,
   -1135,   452,   349, 11545, 12181, 12181,  3020, 12181, 11545, -1135,
     351,   352, -1135,   417,   418,  1444, 11545,  8751,  -156,   364,
   -1135, -1135, -1135, 11545, 11545, -1135,   -91, -1135, -1135, -1135,
   -1135, -1135,  3020,  3020,   -33,   -23,   357, -1135,   -59, -1135,
     367, -1135, -1135,   366, -1135,   369,  3020,   432, -1135,  2592,
     370, -1135, -1135,  -112,  3020, -1135, -1135,    77, -1135, -1135,
   -1135, 11545, -1135, -1135,  1778, -1135,   379,  4807,  5792,  7048,
    3932, -1135, -1135,    84, -1135, -1135,   385,   434, -1135,    22,
   -1135, -1135, -1135, -1135,  5066,  5228,  9405,  6385, -1135, 11545,
   -1135, -1135,   503,  8858,   372,  9405, 11545,  3020, -1135,   -76,
      66, 11545,  2817, -1135, -1135, -1135, -1135, -1135,   274,  9833,
    6492, -1135, 11545,  2592,  8751,  9405,   378, -1135,   -51, -1135,
     -47,   395, -1135,   405, -1135, -1135,   407, -1135,   -46,   429,
     430,   390,   404,  8751, -1135, 11545, -1135,  7080,  5824, -1135,
    2592, -1135, -1135, -1135, -1135, -1135, -1135, 12216, -1135, 12216,
   11545,   410,  1992, -1135,   257,   409, -1135, -1135, -1135,   651,
   -1135,   421, -1135, -1135,  2592,  7187,   419,   422,  7219, -1135,
   -1135, 11545, -1135, -1135, -1135, -1135,  3020, -1135, -1135,   423,
   -1135,    60, -1135,   420, -1135, -1135, -1135,   435,   436, -1135,
   11545, 11545,   510, 11545, -1135, 11545,   438, -1135,  5510, -1135,
      28,  2805,   426,   561, -1135,   497,    94,    32,   658,   447,
     447,   447,   447,   660,   654,   652,  2817,  2817, -1135, -1135,
    7326, 11545, 11545, 11545,  8751,   454, -1135, -1135, -1135,   442,
   -1135, -1135,   451, -1135,   453,   456, -1135,   458, -1135,   457,
     459,   512,   520,  8751, -1135, 11545, -1135, -1135, -1135, -1135,
    7358, -1135,   460,   461, 10689,   471, -1135, -1135, 10903, -1135,
   -1135, -1135, -1135, -1135,   325, -1135,   325,  7465, 10903, -1135,
     472,  2224, -1135, -1135, -1135,   473, -1135, -1135, -1135, -1135,
   11545,  8751, 11545,  1431,  9405,   488, 11545,  3020, -1135,   455,
   11545,  2805,   463,   489,  2817,  2817,  9405,  2817,   467,  3020,
     479,   484,   486,   490,  3020,  2817,  2817, -1135, -1135, 11545,
    7497,  7604,  7636, 11545,   477,   -50, 11545,   495, 11545,   496,
   11545, 11545, 11545, 11545, 11545,   494,   498,  7743, -1135, -1135,
   -1135, -1135,  5933,  3020,  2386,  3290, 10047, -1135,  8751, 11545,
   -1135,   325, -1135, -1135, -1135, -1135,   483,  3020, -1135,   493,
   -1135, -1135,   499,  7775,  8751, -1135,  9405,  7882, -1135, -1135,
     501, -1135, -1135, 11973, -1135, -1135, -1135, -1135, -1135, -1135,
   -1135, -1135, -1135, -1135, -1135, -1135, -1135,  7914,   296, -1135,
   -1135,  8021, -1135,   665,   590,  8751, 11545,  8751, 11545, -1135,
    8751, -1135,  8053,  8160, 11545, 11545, -1135, 11545, -1135,    53,
     112, -1135, -1135, -1135, -1135, -1135,  2634, -1135,   119, -1135,
     504,   508,   -44, -1135, -1135,   506,   134, -1135,    59, -1135,
     502, -1135, -1135, -1135,   509, -1135,   511,  8751, -1135, -1135,
     569,   563, -1135,   515,   516,   148, -1135,   694, -1135,    59,
    8192,  8299, -1135, -1135,  8331,  8438,  5965,    42, -1135, -1135,
    3020, -1135,   517,   519,   518,   526, -1135,   521,   522,   529,
     530, 11117, 11545, -1135, -1135, -1135, -1135, -1135, -1135,  9191,
    9191, -1135, -1135, -1135, -1135, -1135,  6073, 10047, -1135, 10903,
     525, 11545, -1135,  3020,   527,   748,   910,  3020,   611, -1135,
   -1135, -1135,  9405, 11545,   281, -1135, -1135,  3276, -1135,  3020,
     528, -1135,   179, -1135,    59,   615, -1135, -1135, -1135, -1135,
   -1135, -1135, -1135, -1135,  2592,   537, -1135,  3490,  3918,  9191,
   -1135, -1135, 11545, -1135, -1135,  6105,  6213, -1135, -1135,   656,
   -1135, -1135, -1135, -1135, -1135, -1135,   139, -1135, -1135,   532,
   -1135,   181,   536, -1135,   183,   538,  1015, -1135, -1135,  8751,
     543,   540, 11545,  4950, -1135, -1135, -1135,  3020,   615,  1261,
   -1135,   -39,   551, 11331,   549,   565,   188,   562, 11545,   691,
     -37, 11545, -1135, -1135,  3290, -1135, -1135, -1135, -1135,  3020,
   -1135, -1135,  3020, -1135,   560,   657,   193, -1135,   267, -1135,
     571, 11545, -1135, -1135, -1135,   564,   299,   205, -1135, -1135,
    2592,  3932, -1135,   209, -1135,  8470,  9191,  3932, 11545,  9191,
     -36,   572, -1135,   -34,  2848, -1135, -1135, -1135,  3020, -1135,
    3032, 11545, -1135,   573, -1135,  3020,  3020, -1135,  1329,   574,
   -1135,   581, -1135, 11331, 11545, -1135,   582,   218, -1135,  9191,
   11545,   576, -1135,   519, -1135,   577,  3020, -1135, -1135,  8577,
   -1135,   591,   593,  3020,  3020, -1135, -1135,  3932,  2592, -1135,
    8751, -1135, 11545, -1135,   -16,   348, -1135,   594, -1135, -1135,
   -1135,   595,   596, -1135,    36,   610,  9191,    47,   584, 11545,
     612,   -71, -1135,   705, -1135,   707,   707, -1135, -1135, 11545,
    2592,  3932, -1135, -1135, -1135,  8612, -1135, -1135, -1135, 11545,
     706,   705,  2592,   709,   709,   707,   707,  8716,   618, -1135,
    9191, -1135, -1135,    26,  4132,   710,   706,   225,  4346,   706,
     706,   709,   709, 11545,  3932, -1135, -1135,  2206,   608, -1135,
     613,   614,  4560,   607,   710, -1135,   622,  5402,   710,   710,
     706,   706,  8751, -1135,  2420, -1135, -1135, -1135,   623,   229,
   -1135,   621, -1135,   626, -1135,   711,   711,   710,   710, -1135,
   -1135, -1135, -1135,  4774,   624,   625,   627,   628,   633,  6245,
   -1135, -1135, -1135, -1135, -1135, -1135
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,     0,     0,     0,   195,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   466,   466,   503,     0,     0,     0,
       0,     0,   530,     0,     0,     0,     0,     0,     0,     0,
       0,   399,     0,     0,   398,   397,   400,   171,   172,   401,
     402,   445,   460,   446,   447,   448,   403,   404,   405,   406,
     407,   408,   409,   410,   449,   411,   412,   450,   413,   414,
     415,   416,   417,   418,   451,   419,   420,   421,   422,   423,
     424,   425,   426,   427,   428,   429,   430,   431,   432,   433,
     452,   434,   435,   453,   454,   436,   437,   438,   439,   440,
     441,   442,   443,   455,   456,   457,   458,   444,   461,   459,
       0,     0,     0,     0,   314,   313,   356,   173,   175,   176,
     177,   174,   164,   315,   316,     0,     0,     0,   165,   170,
     166,   167,   168,     0,   169,   320,    13,   370,   372,     0,
       0,     0,     0,   371,     0,     2,     0,     3,     4,     5,
       6,     0,   188,   185,   186,   189,   141,   147,   151,   155,
     157,   159,     0,   149,     0,     7,   111,     0,     0,     8,
      10,    11,     0,    12,   311,   163,     0,   162,     9,    26,
     264,    14,     0,    15,    16,     0,    17,   498,   494,    18,
     490,   491,     0,    19,   527,    20,    21,    22,   624,    23,
      24,     0,    25,    30,    37,    27,     0,    28,    29,     1,
     330,   332,   333,     0,     0,     0,     0,   373,     0,     0,
       0,     0,     0,     0,     0,   386,   387,   388,   391,   389,
     390,   393,   392,   394,   395,   396,   329,   331,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   357,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   321,     0,     0,   355,     0,   334,     0,
       0,     0,    99,     0,     0,     0,     0,   155,     0,    96,
     532,    97,    55,    98,    94,    95,    90,    91,    92,     0,
      40,    93,   196,   197,   198,     0,   187,     0,     0,   158,
       0,     0,   128,     0,   142,   148,   152,   156,     0,   150,
       0,   241,   243,     0,     0,     0,     0,     0,     0,     0,
     469,     0,   467,   468,   504,    34,    33,     0,     0,     0,
       0,   500,     0,     0,     0,   171,   172,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   173,     0,   175,   176,
     177,   174,     0,     0,   165,   616,   169,     0,   546,   625,
       0,     0,     0,   529,     0,    38,   246,     0,     0,     0,
       0,     0,   375,     0,   328,     0,     0,     0,     0,     0,
     327,   341,   342,   343,   344,   345,   347,   348,   349,   350,
     351,   352,   359,   360,   361,     0,   335,   336,   337,   338,
     340,   339,     0,   346,   362,   363,   462,     0,     0,     0,
     354,   385,     0,     0,     0,     0,     0,     0,     0,    64,
       0,     0,     0,     0,    31,    68,     0,   116,   118,     0,
       0,     0,     0,     0,   178,     0,     0,   112,   128,   114,
     130,     0,     0,     0,   242,   244,   312,   231,     0,   265,
       0,     0,     0,     0,   465,   118,   128,   128,   492,   493,
       0,     0,   512,   513,   528,   620,     0,   622,     0,     0,
     541,   542,   538,     0,   540,   548,   547,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   549,   573,
       0,     0,   618,     0,   617,     0,     0,     0,   626,   627,
     531,     0,     0,   462,     0,     0,     0,     0,   462,   376,
       0,     0,   576,     0,     0,   358,     0,   463,     0,     0,
     326,   325,   317,     0,     0,   136,     0,   137,   139,    54,
      67,    53,     0,     0,     0,     0,     0,    50,     0,    46,
      49,    51,   100,     0,   533,     0,     0,    73,   115,     0,
       0,   128,    41,     0,     0,   145,   183,     0,   181,   143,
     179,     0,   160,   113,     0,   129,     0,     0,     0,     0,
       0,   472,   475,     0,   473,   483,     0,     0,   485,     0,
     499,   495,   128,   128,     0,     0,     0,     0,   564,     0,
     550,   583,     0,     0,     0,     0,     0,     0,   611,   609,
       0,     0,     0,   596,   561,   590,   562,   563,     0,     0,
       0,   615,     0,     0,   543,     0,     0,   108,     0,   190,
       0,     0,   377,     0,   379,   383,     0,   381,     0,     0,
       0,     0,     0,   353,   322,     0,   324,     0,     0,   135,
       0,   128,    65,    66,   102,   103,    45,     0,    44,     0,
       0,     0,     0,    70,    40,     0,    43,   117,   104,   120,
      42,     0,   128,   180,     0,     0,     0,     0,     0,   146,
     144,     0,   161,   232,   128,   471,     0,   503,   481,     0,
     487,     0,   503,     0,   477,   497,   501,     0,     0,   555,
     537,   536,     0,     0,   581,     0,     0,   554,     0,   613,
       0,     0,     0,     0,   579,     0,     0,   607,   590,   607,
     607,   607,   607,   597,   598,   599,     0,     0,   589,   588,
       0,     0,     0,     0,   619,     0,   556,   110,   109,   195,
      39,   366,     0,   368,     0,     0,   364,     0,   374,     0,
       0,     0,     0,   464,   318,     0,   138,   140,    48,    47,
       0,   101,     0,     0,     0,     0,    75,   268,     0,   119,
      35,   184,   182,   153,   130,   132,   130,     0,     0,   474,
       0,     0,   503,   489,   488,     0,   479,   503,   621,   623,
       0,   584,     0,   336,     0,     0,     0,     0,   612,   609,
     616,     0,     0,   569,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   559,   560,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    52,   535,
     534,    69,     0,     0,     0,   271,     0,   121,   122,   462,
     134,   130,   131,   154,   476,   484,     0,     0,   253,     0,
     486,   503,     0,     0,   582,   551,     0,     0,   614,   558,
       0,   557,   580,     0,   605,   603,   608,   600,   591,   601,
     592,   593,   594,   595,   602,   604,   606,     0,   566,   544,
     545,     0,   191,     0,   253,   367,     0,   369,     0,   384,
     365,   382,     0,     0,     0,     0,   319,     0,    72,     0,
       0,    57,    74,    76,   269,   270,     0,   127,     0,   124,
       0,   320,     0,   133,   506,   509,     0,   507,     0,   482,
       0,   478,   539,   553,     0,   610,   315,   570,   567,   587,
     586,     0,   572,     0,   203,     0,   201,     0,   253,     0,
       0,     0,   577,   578,     0,     0,     0,     0,    60,    62,
       0,    56,    78,   107,     0,     0,   303,     0,     0,     0,
       0,     0,     0,   284,   266,   106,   105,   283,   272,     0,
       0,   274,   275,   280,   286,   287,     0,     0,   123,     0,
       0,     0,   505,     0,     0,     0,     0,     0,   514,   254,
     255,   480,     0,     0,     0,   565,   200,     0,   199,     0,
       0,   212,     0,   210,     0,   215,   378,   380,   574,   575,
      71,    61,    63,    58,     0,     0,   273,     0,     0,     0,
     288,   289,     0,   276,   293,     0,     0,   268,   281,   274,
     279,   282,   285,   125,   126,    36,     0,   508,   214,     0,
     262,     0,     0,   260,     0,     0,     0,   502,   552,   571,
       0,     0,     0,     0,   202,   209,   208,     0,   215,     0,
     192,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   292,   294,   271,   278,   510,   259,   258,     0,
     257,   256,     0,   213,     0,     0,     0,   517,     0,   207,
       0,     0,   205,   211,   193,     0,     0,     0,   218,    79,
       0,     0,    85,     0,    82,     0,     0,     0,     0,     0,
       0,     0,   290,     0,     0,   263,   261,   516,     0,   515,
       0,     0,   204,     0,   217,     0,     0,   216,     0,     0,
      80,     0,    77,     0,     0,   299,     0,     0,   302,     0,
       0,     0,   277,     0,   267,     0,     0,   523,   518,     0,
     206,     0,     0,     0,     0,   228,   219,     0,     0,    83,
      84,   297,     0,   301,     0,     0,   519,     0,   568,   220,
     222,     0,     0,    81,     0,     0,     0,     0,     0,     0,
       0,     0,   305,   524,   521,   229,   229,   224,   226,     0,
       0,     0,   298,   295,   304,     0,   309,   291,   306,     0,
     237,   524,     0,   233,   233,   229,   229,     0,     0,    87,
       0,   307,   271,     0,     0,   247,   237,     0,     0,   237,
     237,   233,   233,     0,     0,   296,   271,     0,     0,   525,
       0,     0,     0,     0,   247,   230,     0,     0,   247,   247,
     237,   237,    86,    88,     0,   526,   239,   238,     0,     0,
     520,     0,   236,     0,   234,   250,   250,   247,   247,   249,
     248,   522,   235,     0,     0,     0,     0,     0,     0,     0,
     221,   223,   225,   227,   252,   251
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1135, -1135,   849,   685,  -124, -1135, -1135, -1135,   230,   567,
   -1135, -1135,  -330,  -762, -1135, -1135, -1135,   -62, -1135, -1135,
   -1135, -1135, -1135, -1135, -1135, -1135, -1135, -1135,  -244, -1135,
   -1135,   406, -1135, -1135, -1135, -1135,  -132, -1135, -1135,  -313,
    -354,   592,  -135, -1135,   341, -1135, -1135,  -715, -1135,   -80,
    -131, -1135,  -670, -1135,  -133, -1135,   268, -1135,    29,  -102,
     617,   462,  -393, -1135,   243, -1135, -1135,   869, -1135, -1135,
     180, -1135, -1135,   -89, -1135, -1135,  -146,  -883,  -145, -1135,
    -214, -1135, -1135, -1135, -1135, -1135, -1108,  -286, -1102, -1133,
    -297, -1135, -1134,  -322,  -821, -1135, -1135, -1135, -1135,  -973,
   -1135, -1135,  -101, -1043,  -943, -1135, -1135, -1135,  -487,   -30,
   -1135, -1135, -1135, -1135, -1135, -1135, -1135, -1135, -1135,  -239,
   -1135, -1135,   -11,    -1, -1135, -1135, -1135, -1135, -1135, -1135,
   -1135, -1135, -1135, -1135, -1135, -1135, -1135, -1135, -1135, -1135,
   -1135, -1135,  -473, -1135,   912,  -159, -1135, -1135,   270, -1135,
   -1135, -1135, -1135, -1135, -1135, -1135, -1135,   373,   620, -1135,
   -1135,   629, -1135, -1135,  -624,   917, -1135, -1135,   -32,   -29,
   -1135, -1135,  -173, -1135, -1135, -1135,  -246,  -243, -1135, -1135,
   -1135, -1135, -1135,  -434, -1135, -1135,  -332,   475, -1135, -1135,
   -1135,  -129,  -438,  -568, -1135, -1135, -1135, -1135, -1135, -1135,
   -1135,  -334,   173,  -629, -1135, -1135,   174,  -311, -1135, -1135,
     313
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    30,   135,   176,   269,   829,   193,   493,   420,   270,
     271,   528,   529,   530,   272,   415,   890,   891,   408,   523,
     537,   744,   646,   824,   942,  1005,  1051,  1093,  1094,  1121,
    1164,   136,   273,   641,   274,   275,   276,   747,   956,   492,
     155,   156,   310,   416,   417,   541,   749,   897,   898,   899,
     429,   430,   555,   831,   278,   516,   517,   631,   311,   166,
     125,   423,   424,   547,   548,   652,   158,   281,   719,   804,
     138,   874,   925,   926,   928,   992,   993,   978,  1050,  1087,
    1088,  1175,  1176,  1146,  1195,  1196,  1193,   168,  1209,  1205,
     161,   195,  1223,  1254,   908,   979,   980,  1034,  1031,   169,
     957,  1017,   825,   896,   958,   959,  1061,   960,   961,   962,
     963,  1131,   964,  1200,  1166,   965,  1058,  1009,  1171,  1172,
    1216,  1202,   163,   164,   396,   397,   385,   811,   806,   808,
     127,   361,   722,   724,   727,   725,   128,   257,   129,   130,
     131,   132,   508,   171,   172,   312,   441,   563,   564,   664,
     313,   767,   841,   762,   667,   672,   569,   179,   180,   318,
     320,   181,   317,   451,   760,   761,   838,   906,   907,   183,
    1037,  1076,  1077,  1173,  1138,  1191,  1190,   185,   187,   188,
     414,   534,   682,   348,   349,   133,   473,   584,   772,   683,
     921,   711,   594,   595,   699,   700,   701,   702,   703,   704,
     705,   788,   693,   589,   690,   350,   483,   484,   351,   352,
     353
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     126,   277,   277,   283,   277,   284,   282,   159,   160,   162,
     186,   480,   170,   190,   485,   314,  1018,   197,   182,   184,
     610,  1104,   189,   673,   698,   618,   196,  1218,   198,   691,
     550,   200,   201,   827,   580,   520,   157,   596,   597,   598,
     488,   489,   637,   834,  1169,  1170,   995,   178,   765,   -32,
     175,   434,   316,   929,   937,   777,  1001,   566,   784,   785,
     974,   889,   779,   538,   539,   543,  1059,   938,  1194,  1080,
     263,   141,   142,  1224,   143,   144,  1228,  1229,   145,   624,
     455,   873,   -32,   -32,   830,   625,   832,  1211,  1212,   354,
    1241,   585,  1210,   456,  1245,  1246,   586,  1247,  1248,   457,
     532,   357,   358,   359,   360,   540,   191,   994,  1113,  1230,
    1231,  1048,   458,  1256,  1257,   226,   227,   228,   229,   230,
     231,   232,   214,   650,   235,   236,   146,   199,   258,   290,
     147,   148,   149,   150,   151,   152,   153,   608,   839,   202,
     226,   227,   679,   842,   230,   231,   232,   526,   468,   629,
     630,   687,   851,  1125,   697,   469,  1128,   535,   262,  1217,
     536,   903,   226,   227,   550,   279,   279,   279,   279,   154,
     692,   716,  1187,  1234,   521,   522,   203,   418,   889,    37,
      38,   638,   639,   975,   718,   316,  1153,   347,   720,   728,
     290,   970,   976,   977,   625,   625,  1089,   625,  1102,  1129,
     285,  1132,  1090,   438,   303,   303,   443,   303,   303,   445,
     634,   -32,   367,   -32,   -32,   -32,   -32,   910,   303,  1168,
     635,   859,   204,  1182,   -32,   303,   864,   371,   372,   373,
     374,   375,   376,   377,   378,   379,   380,   381,   382,   383,
     384,   205,   386,   387,   388,   389,   390,   391,   392,   393,
     394,   395,   442,   399,  1024,   206,   401,  1215,   402,   403,
     404,   786,   527,   778,   674,   435,  1219,   324,   797,   798,
    1002,  1179,   -32,   -32,   -32,   -32,   -32,  1180,   787,   208,
     696,   939,  1183,   286,    37,    38,   425,   426,   303,   640,
     567,   209,   406,   -32,   -59,   764,   -59,   553,   568,   259,
     319,   392,   436,   694,   518,   439,   695,   738,   107,   739,
     108,   109,   110,   111,   422,   570,   571,   653,   654,   157,
     546,   112,   453,   454,   665,   666,   460,   461,   462,   464,
     465,   466,   293,   437,   253,   602,   254,   783,   255,   256,
     845,   478,   479,   260,   482,   407,   854,   855,   178,   857,
     482,   482,   856,   940,   261,   941,   902,   865,   866,   253,
     967,   254,   968,   255,   256,   790,   791,   792,   793,   118,
     119,   120,   121,   122,   972,   973,   706,    37,    38,   707,
     323,   253,  1066,   254,   505,   255,   256,   294,   988,   989,
     124,   295,   296,   297,   290,   507,   298,   299,   919,   524,
     525,   920,   226,   227,   228,   229,   230,   231,   232,   137,
     649,   139,   913,   107,   287,   108,   109,   110,   111,  1046,
    1047,  1068,  1069,  1071,  1072,   288,   112,   165,  1098,   303,
     289,   558,   559,  1109,  1110,   669,   303,   445,   708,   709,
     305,   675,   676,  1115,  1116,  1117,  1118,   315,   157,  1122,
    1123,   304,   422,   606,   319,   574,  -496,   575,  1152,   303,
     422,   321,   577,  1169,  1170,  1225,   305,   347,   583,  1250,
     303,   583,  1019,  1020,   118,   119,   120,   121,   122,   323,
     600,   324,   355,   440,   362,   604,   365,   364,  -323,   366,
     412,   419,   507,   467,   432,   124,   410,   507,   411,   433,
     737,   715,   431,   450,   470,   623,   107,   452,   108,   109,
     110,   111,   627,   628,   471,  -470,  -470,   472,   474,   112,
     157,   751,   475,   611,   613,   487,   616,   476,   518,   477,
     481,   490,   494,   758,   495,   491,   496,   497,   498,   500,
     501,   499,   509,   533,   560,   503,   504,   544,  1038,   510,
     655,   515,   546,   658,   519,   141,   142,   177,   143,   144,
     545,   554,   145,   561,   565,   576,   591,   118,   119,   120,
     121,   122,   599,   141,   142,   347,   143,   144,   460,   603,
     145,   602,   601,   657,   347,   688,   422,   605,   124,   663,
     482,   609,   619,   620,   621,   622,   178,   636,   710,   626,
     645,   714,   314,   640,   347,   684,   729,   730,   642,   686,
     146,   643,   648,   717,   147,   148,   149,   150,   151,   152,
     153,   253,   659,   254,   733,   255,   256,   668,   146,   167,
     721,   731,   147,   148,   149,   150,   151,   152,   153,   740,
     723,   347,   726,   194,  -470,   732,  -470,  -470,  -470,  -470,
     741,   746,  1040,   154,   748,   750,   754,  -470,   763,   755,
     757,   770,   766,   781,   768,   769,   923,   774,   780,   670,
     283,   154,   284,   282,   782,   789,   786,   794,   796,   380,
     382,   795,   771,   803,   773,  -194,   807,   607,   809,   815,
     894,   810,   895,   812,   813,   990,   814,   816,    37,    38,
     852,   692,   858,   819,   820,  -470,  -470,  -470,  -470,  -470,
     800,   801,   802,   823,   860,   835,   840,   846,   853,   861,
     872,   862,   927,   904,   900,   863,  -470,    37,    38,   876,
     878,   884,   207,   969,   817,   885,   909,  -162,   982,   984,
     983,   985,   911,   822,   915,   981,  1036,   828,   971,  1029,
    1049,  1004,  1007,   280,   280,   986,   280,   828,   987,  1006,
    1008,  1010,  1011,  1012,  1013,  1025,  1053,  1028,  1045,   843,
    1065,   844,  1067,   347,   292,   847,  1070,  1078,  1073,   482,
    1091,    37,    38,  1079,  1096,   347,   226,   227,   228,   229,
     230,   231,   232,   280,  1097,   235,   236,  1099,   867,  1101,
    1107,  1108,   871,  1147,  1114,   875,  1130,   877,   167,   879,
     880,   881,   882,   883,  1112,  1148,  1140,  1151,  1155,  1156,
     167,   167,   167,   167,  1184,   828,   363,   107,   507,   108,
     109,   110,   111,  1159,   279,  1160,  1174,  1177,  1178,  1181,
     112,  1186,  1189,  1192,  1204,   347,  1208,  1214,  1235,  1222,
    1240,  1253,   917,  1236,  1237,   140,   107,   309,   108,   109,
     110,   111,  1242,  1249,  1251,   900,  1252,  1260,  1261,   112,
    1262,  1263,   400,  1264,   745,   930,   444,   931,  1003,  1149,
     647,   409,   427,   934,   935,   413,   936,  1023,   118,   119,
     120,   121,   122,   557,   192,   966,   167,   752,   736,   805,
    1044,  1083,  1052,  1084,  1145,  1055,  1207,  1221,   428,   124,
     107,  1032,   108,   109,   110,   111,  1064,   118,   119,   120,
     121,   122,   167,   112,  1255,   167,   280,   173,   167,   894,
    1021,   895,  1188,   174,   446,   447,   759,  1137,   124,   448,
     671,  1027,  1026,    37,    38,  1206,  1203,   590,   449,  1111,
    1015,  1016,   849,     0,   850,   743,     0,     0,   966,   966,
       0,     0,     0,     0,     0,     0,   828,     0,   828,     0,
     182,   118,   119,   120,   121,   122,     0,     0,     0,     0,
       0,   347,  1039,     0,     0,     0,  1043,     0,  1119,     0,
       0,     0,   124,     0,     0,     0,  1056,     0,     0,     0,
       0,  1060,   251,   252,     0,   253,     0,   254,   966,   255,
     256,     0,     0,     0,     0,     0,  1074,     0,     0,     0,
       0,     0,     0,   167,     0,     0,     0,     0,     0,   531,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   167,
       0,   170,     0,     0,     0,     0,  1165,  1100,    37,    38,
    1103,     0,  1095,     0,     0,     0,     0,     0,   562,     0,
       0,     0,     0,     0,     0,     0,     0,   572,   573,     0,
       0,     0,   107,     0,   108,   109,   110,   111,  1198,     0,
     170,     0,     0,     0,   578,   112,     0,  1127,   588,     0,
       0,   593,   593,   593,   593,   966,     0,     0,   966,     0,
       0,     0,     0,   966,     0,     0,     0,     0,     0,     0,
    1139,   612,   614,   615,   617,     0,     0,     0,     0,  1154,
    1120,     0,  1095,  1150,     0,     0,  1126,     0,   966,     0,
       0,     0,     0,   118,   119,   120,   121,   122,     0,   632,
     633,  1167,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   644,   124,     0,   167,     0,     0,     0,
       0,   651,     0,     0,   175,   966,     0,     0,  1185,     0,
       0,     0,     0,     0,     0,     0,  1163,   107,  1197,   108,
     109,   110,   111,     0,     0,     0,     0,     0,   184,     0,
     112,   -89,   134,     0,     0,     0,   -32,   -32,     0,   966,
       0,     0,     0,   162,   689,     0,     0,  1227,     0,   593,
    1199,  1239,  1232,     0,     0,     0,   966,     0,     0,     0,
     167,     0,     0,     0,   -89,   -89,     0,     0,     0,     0,
       0,     0,     0,   966,     0,     0,     0,     0,   118,   119,
     120,   121,   122,  1233,     0,     0,     0,   167,     0,     0,
       0,     0,  1259,     0,   531,     0,   531,     0,     0,   124,
       0,     0,  1085,     0,     0,     0,     0,     0,     0,     0,
       0,   167,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   562,   141,   142,   307,   143,   144,     0,
       0,   145,   -32,   308,    37,    38,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   588,     0,
       0,   -89,   -89,   -89,     0,   -89,   -89,     0,     0,   -89,
       0,   -89,     0,   593,   593,   -32,     0,   -32,   -32,   -32,
     -32,     0,   -89,   -89,     0,     0,     0,     0,   -32,   146,
       0,     0,     0,   147,   148,   149,   150,   151,   152,   153,
       0,     0,     0,   -89,     0,   -89,   -89,   -89,   -89,     0,
       0,     0,    37,    38,     0,     0,   -89,   -89,     0,     0,
       0,   -89,   -89,   -89,   -89,   -89,   -89,   -89,     0,     0,
       0,     0,   154,     0,     0,     0,   -32,   -32,   -32,   -32,
     -32,     0,     0,     0,   848,     0,     0,     0,   588,     0,
       0,   593,   593,     0,   593,     0,   593,   -32,     0,   -89,
     -89,   593,   593,   593,   -89,   -89,   -89,   -89,   -89,     0,
       0,     0,     0,   107,     0,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,   -89,   112,     0,     0,     0,
     531,   893,     0,   901,     0,     0,   226,   227,   228,   229,
     230,   231,   232,     0,   905,   235,   236,     0,     0,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,     0,   239,  1143,  1144,     0,   405,     0,     0,     0,
       0,     0,     0,     0,   118,   119,   120,   121,   122,     0,
     924,   107,     0,   108,   109,   110,   111,     0,     0,     0,
       0,     0,     0,     0,   112,   124,  -511,   322,     0,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
       0,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,     0,     0,
       0,     0,     0,     0,   991,   243,   244,   245,   246,   247,
     248,     0,   118,   119,   120,   121,   122,   531,     0,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
       0,     0,     0,   124,   141,   142,     0,   143,   144,     0,
       0,   145,     0,     0,   901,     0,     0,     0,     0,     0,
     905,     0,  1030,  1033,  1035,     0,   141,   142,     0,   143,
     144,     0,     0,   145,     0,     0,   924,   243,   244,   245,
     246,   247,   248,     0,     0,     0,     0,     0,     0,     0,
       0,   167,     0,     0,   901,     0,     0,     0,     0,   146,
       0,     0,     0,   147,   148,   149,   150,   151,   152,   153,
       0,     0,     0,     0,     0,   243,   244,   245,   246,   247,
     248,   146,     0,  1075,     0,   147,   148,   149,   150,   151,
     152,   153,   251,   252,   991,   253,  1086,   254,  -585,   255,
     256,  -585,   154,     0,   250,   251,   252,     0,   253,     0,
     254,     0,   255,   256,     0,     0,  1105,     0,     0,  1106,
       0,     0,     0,     0,   154,     0,   549,     0,     0,     0,
     226,   227,   228,   229,   230,   231,   232,   167,   234,   235,
     236,     0,   226,   227,   228,   229,   230,   231,   232,     0,
       0,   235,   236,     0,     0,  1135,     0,  1075,     0,     0,
       0,     0,  1141,  1142,   249,  1086,   250,   251,   252,     0,
     253,     0,   254,     0,   255,   256,     0,  -511,     0,  -511,
       0,     0,     0,  1157,     0,     0,     0,     0,     0,     0,
    1161,  1162,     0,     0,     0,   167,     0,     0,     0,     0,
       0,     0,     0,     0,   250,   251,   252,     0,   253,   656,
     254,     0,   255,   256,     0,     0,   243,   244,   245,   246,
     247,   248,    31,    32,    33,    34,    35,   167,   243,   244,
     245,   246,   247,   248,     0,     0,     0,     0,     0,   167,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,     0,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   226,
     227,   228,   229,   230,   231,   232,     0,     0,   235,   236,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   141,
     142,     0,   143,   144,   104,   105,   145,     0,     0,     0,
       0,     0,     0,     0,     0,   250,   251,   252,     0,   253,
       0,   254,     0,   255,   256,     0,   106,   250,   251,   252,
       0,   253,     0,   254,     0,   255,   256,     0,     0,     0,
     107,     0,   108,   109,   110,   111,     0,     0,     0,     0,
       0,     0,     0,   112,   146,   113,   114,     0,   147,   148,
     149,   150,   151,   152,   153,   243,   244,   245,   246,   247,
     248,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    37,    38,   742,     0,     0,     0,   154,   115,   116,
     117,   118,   119,   120,   121,   122,    31,    32,    33,    34,
      35,   421,   123,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   124,     0,    36,   325,   326,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,     0,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,     0,     0,   251,   252,     0,   253,     0,
     254,     0,   255,   256,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   104,   105,
     107,     0,   108,   109,   110,   111,     0,     0,     0,     0,
       0,   141,   142,   112,   143,   144,     0,     0,   145,     0,
     106,   327,   328,   329,   330,     0,     0,     0,     0,   331,
     332,   333,   334,   335,   336,   337,   338,   339,   340,   341,
       0,   342,   343,     0,     0,     0,     0,   112,     0,   113,
     114,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   118,   119,   120,   121,   122,   146,     0,   291,     0,
     147,   148,   149,   150,   151,   152,   153,     0,     0,     0,
       0,     0,   124,     0,     0,     0,     0,  1133,     0,     0,
       0,     0,   115,   116,   117,   344,   119,   120,   121,   122,
      31,    32,    33,    34,    35,   836,   123,     0,     0,   154,
       0,     0,     0,     0,   345,  -624,   346,     0,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,     0,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,     0,     0,     0,
       0,     0,     0,   944,   945,   946,   947,   948,   949,   950,
       0,  -310,  -310,   951,   952,     0,     0,     0,     0,     0,
       0,     0,   104,   105,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   141,   142,   307,   143,   144,
       0,     0,   145,     0,   106,   837,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   107,     0,
     108,   109,   110,   111,     0,     0,     0,     0,     0,     0,
       0,   112,     0,   113,   114,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     146,     0,     0,     0,   147,   148,   149,   150,   151,   152,
     153,     0,     0,     0,     0,     0,     0,     0,     0,    37,
      38,  1133,     0,     0,     0,     0,   115,   116,   117,   118,
     119,   120,   121,   122,    31,    32,    33,    34,    35,   556,
     123,     0,     0,   154,     0,     0,   953,     0,   954,  -310,
     124,     0,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
       0,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,     0,     0,     0,     0,     0,     0,   944,   945,   946,
     947,   948,   949,   950,     0,  -308,  -308,   951,   952,     0,
       0,     0,     0,     0,     0,     0,   104,   105,   107,     0,
     108,   109,   110,   111,     0,     0,     0,     0,     0,   141,
     142,   112,   143,   144,     0,     0,   145,     0,   106,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   107,     0,   108,   109,   110,   111,     0,     0,
       0,     0,     0,     0,     0,   112,     0,   113,   114,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   118,
     119,   120,   121,   122,   146,     0,     0,     0,   147,   148,
     149,   150,   151,   152,   153,    37,    38,     0,     0,   892,
     124,     0,     0,     0,     0,   943,     0,     0,     0,     0,
     115,   116,   117,   118,   119,   120,   121,   122,    31,    32,
      33,    34,    35,     0,   123,     0,     0,   154,     0,     0,
     953,     0,   954,  -308,   124,     0,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,     0,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,     0,     0,     0,     0,     0,
       0,   944,   945,   946,   947,   948,   949,   950,     0,     0,
       0,   951,   952,     0,   107,     0,   108,   109,   110,   111,
     104,   105,     0,     0,     0,     0,     0,   112,   165,   141,
     142,   307,   143,   144,     0,     0,   145,     0,   308,     0,
       0,     0,   106,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   107,     0,   108,   109,
     110,   111,     0,     0,     0,     0,     0,     0,     0,   112,
       0,   113,   114,     0,     0,   118,   119,   120,   121,   122,
       0,     0,     0,     0,   146,     0,     0,     0,   147,   148,
     149,   150,   151,   152,   153,     0,   124,     0,    37,    38,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1133,
      37,    38,     0,     0,   115,   116,   117,   118,   119,   120,
     121,   122,    31,    32,    33,    34,    35,   154,   123,     0,
       0,     0,     0,     0,   953,     0,   954,   955,   124,     0,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,     0,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,     0,
       0,     0,     0,     0,     0,   944,   945,   946,   947,   948,
     949,   950,     0,     0,     0,   951,   952,   107,     0,   108,
     109,   110,   111,     0,   104,   105,     0,     0,     0,   107,
     112,   108,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,   112,     0,     0,     0,   106,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     107,     0,   108,   109,   110,   111,     0,     0,     0,     0,
       0,     0,     0,   112,     0,   113,   114,     0,   118,   119,
     120,   121,   122,     0,     0,     0,     0,     0,     0,   587,
     118,   119,   120,   121,   122,     0,     0,     0,     0,   124,
       0,   592,     0,    37,    38,     0,     0,     0,     0,     0,
       0,   124,     0,   210,     0,    37,    38,     0,   115,   116,
     117,   118,   119,   120,   121,   122,    31,    32,    33,    34,
      35,     0,   123,     0,     0,     0,     0,     0,   953,     0,
     954,  1134,   124,     0,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,     0,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   226,   227,   228,   229,   230,   231,   232,
       0,     0,   235,   236,     0,     0,  1136,     0,     0,     0,
       0,     0,   107,     0,   108,   109,   110,   111,   104,   105,
       0,     0,     0,     0,   107,   112,   108,   109,   110,   111,
       0,     0,     0,     0,     0,     0,     0,   112,     0,     0,
     106,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   107,     0,   108,   109,   110,   111,
       0,     0,     0,   211,   212,     0,     0,   112,     0,   113,
     114,     0,     0,   118,   119,   120,   121,   122,     0,   243,
     244,     0,     0,   247,   248,   118,   119,   120,   121,   122,
       0,     0,     0,     0,   124,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   124,  1041,     0,   213,
       0,     0,   115,   116,   117,   118,   119,   120,   121,   122,
      31,    32,    33,    34,    35,     0,   123,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   124,     0,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,     0,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,     0,     0,   251,
     252,     0,   253,     0,   254,     0,   255,   256,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   104,   105,     0,     0,     0,     0,     0,     0,
     263,   141,   142,     0,   143,   144,     0,     0,   145,     0,
       0,     0,     0,     0,   106,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   107,     0,
     108,   109,   110,   111,     0,     0,     0,     0,     0,     0,
       0,   112,     0,   113,   114,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   146,     0,     0,     0,
     147,   148,   149,   150,   151,   152,   153,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1054,     0,     0,     0,     0,   115,   116,   117,   118,
     119,   120,   121,   122,    31,    32,    33,    34,    35,   154,
     123,     0,     0,     0,     0,     0,  1042,     0,     0,     0,
     124,     0,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
       0,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   104,   105,     0,     0,
       0,     0,     0,     0,     0,   141,   142,   177,   143,   144,
       0,     0,   145,     0,     0,     0,     0,     0,   106,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   107,     0,   108,   109,   110,   111,     0,     0,
       0,     0,     0,     0,     0,   112,   165,   113,   114,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     146,     0,     0,     0,   147,   148,   149,   150,   151,   152,
     153,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   398,     0,     0,     0,     0,
     115,   116,   117,   118,   119,   120,   121,   122,    31,    32,
      33,    34,    35,   154,   123,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   124,     0,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,     0,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     104,   105,     0,     0,     0,     0,     0,     0,     0,   141,
     142,   307,   143,   144,     0,     0,   145,     0,     0,     0,
       0,     0,   106,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   107,     0,   108,   109,
     110,   111,     0,     0,     0,     0,     0,     0,     0,   112,
       0,   113,   114,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   146,     0,     0,     0,   147,   148,
     149,   150,   151,   152,   153,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1057,
       0,     0,     0,     0,   115,   116,   117,   118,   119,   120,
     121,   122,  -300,  -300,  -300,  -300,  -300,   154,   123,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   124,     0,
    -300,  -300,  -300,  -300,  -300,  -300,  -300,  -300,  -300,  -300,
    -300,  -300,  -300,  -300,  -300,  -300,  -300,  -300,  -300,  -300,
    -300,  -300,  -300,  -300,  -300,  -300,  -300,  -300,  -300,  -300,
    -300,  -300,  -300,  -300,  -300,  -300,  -300,  -300,  -300,  -300,
    -300,  -300,  -300,  -300,  -300,  -300,  -300,  -300,     0,  -300,
    -300,  -300,  -300,  -300,  -300,  -300,  -300,  -300,  -300,  -300,
    -300,  -300,  -300,  -300,  -300,  -300,  -300,  -300,  -300,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -300,  -300,     0,     0,     0,     0,
       0,     0,     0,   141,   142,     0,   143,   144,     0,     0,
     145,     0,     0,     0,     0,     0,  -300,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -300,     0,  -300,  -300,  -300,  -300,     0,     0,     0,     0,
       0,     0,     0,  -300,     0,  -300,  -300,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   146,     0,
       0,     0,   147,   148,   149,   150,   151,   152,   153,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1220,     0,     0,     0,     0,  -300,  -300,
    -300,  -300,  -300,  -300,  -300,  -300,    31,    32,    33,    34,
      35,   154,  -300,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -300,     0,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,     0,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   104,   105,
       0,     0,     0,     0,     1,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     106,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   107,     0,   108,   109,   110,   111,
       0,     0,     0,     0,     0,     0,     0,   112,     0,   113,
     114,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,     0,
       0,     0,     0,     0,     0,     0,     0,  1226,     0,     0,
       0,     0,   115,   116,   117,   118,   119,   120,   121,   122,
      31,    32,    33,    34,    35,     0,   123,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   124,     0,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,     0,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   104,   105,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   106,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   107,     0,
     108,   109,   110,   111,     0,     0,     0,     0,     0,     0,
       0,   112,     0,   113,   114,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1238,     0,     0,     0,     0,   115,   116,   117,   118,
     119,   120,   121,   122,    31,    32,    33,    34,    35,     0,
     123,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     124,     0,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
       0,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   104,   105,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   106,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   107,     0,   108,   109,   110,   111,     0,     0,
       0,     0,     0,     0,     0,   112,     0,   113,   114,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1258,     0,     0,     0,     0,
     115,   116,   117,   118,   119,   120,   121,   122,    31,    32,
      33,    34,    35,     0,   123,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   124,     0,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,     0,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,     0,     0,     0,     0,     0,
       0,     0,     0,   134,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     104,   105,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -89,   -89,     0,     0,     0,
       0,     0,   106,     0,     0,     0,     0,     0,   141,   142,
       0,   143,   144,     0,     0,   145,   107,     0,   108,   109,
     110,   111,     0,     0,     0,     0,     0,     0,     0,   112,
       0,   113,   114,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,     0,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,     0,   146,     0,     0,     0,   147,   148,   149,
     150,   151,   152,   153,   115,   116,   117,   118,   119,   120,
     121,   122,   -89,   -89,   -89,     0,   -89,   -89,   123,     0,
     -89,   -89,   -89,     0,     0,     0,     0,     0,   124,     0,
       0,     0,     0,   -89,   -89,     0,   154,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -89,     0,   -89,   -89,   -89,   -89,
     660,   243,   244,   245,   246,   247,   248,   -89,   -89,     0,
       0,     0,   -89,   -89,   -89,   -89,   -89,   -89,   -89,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
       0,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,     0,     0,
     -89,   -89,     0,     0,     0,   -89,   -89,   -89,   -89,   -89,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -240,   300,   -89,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   301,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   243,   244,   245,
     246,   247,   248,     0,     0,     0,     0,     0,   249,     0,
     250,   251,   252,     0,   253,     0,   254,     0,   255,   256,
    1081,     0,     0,  1082,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   141,   142,     0,   143,   144,
       0,     0,   145,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   243,   244,   245,   246,   247,
     248,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,     0,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     146,     0,     0,     0,   147,   148,   149,   150,   151,   152,
     153,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   249,     0,   250,   251,   252,     0,
     253,     0,   254,   154,   255,   256,     0,     0,     0,   677,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   542,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   243,
     244,   245,   246,   247,   248,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   302,     0,   250,   251,   252,     0,   253,     0,
     254,     0,   255,   256,  -240,     0,     0,     0,     0,     0,
       0,  -245,   356,     0,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,     0,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,  1243,     0,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,     0,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   249,     0,   250,   251,
     252,     0,   253,     0,   254,     0,   255,   256,     0,     0,
       0,   678,   243,   244,   245,   246,   247,   248,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   243,   244,   245,   246,   247,   248,     0,
       0,     0,     0,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,     0,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,     0,     0,     0,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,     0,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   249,
       0,   250,   251,   252,     0,   253,     0,   254,     0,   255,
     256,   243,   244,   245,   246,   247,   248,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     249,     0,   250,   251,   252,     0,   253,     0,   254,     0,
     255,   256,  1244,   243,   244,   245,   246,   247,   248,     0,
       0,     0,     0,     0,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,     0,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,     0,     0,     0,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,     0,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   249,     0,
     250,   251,   252,     0,   253,   775,   254,     0,   255,   256,
       0,   776,   243,   244,   245,   246,   247,   248,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     249,     0,   250,   251,   252,     0,   253,     0,   254,     0,
     255,   256,     0,   513,   243,   244,   245,   246,   247,   248,
       0,     0,     0,     0,     0,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,     0,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,     0,     0,     0,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,     0,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   249,
       0,   250,   251,   252,     0,   253,     0,   254,     0,   255,
     256,     0,   514,   243,   244,   245,   246,   247,   248,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   249,     0,   250,   251,   252,     0,   253,     0,   254,
       0,   255,   256,     0,   551,   243,   244,   245,   246,   247,
     248,     0,     0,     0,     0,     0,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,     0,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,     0,     0,     0,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,     0,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     249,     0,   250,   251,   252,     0,   253,     0,   254,     0,
     255,   256,     0,   661,   243,   244,   245,   246,   247,   248,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   249,     0,   250,   251,   252,     0,   253,     0,
     254,     0,   255,   256,     0,   735,   243,   244,   245,   246,
     247,   248,     0,     0,     0,     0,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,     0,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,     0,     0,     0,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,     0,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   249,   887,   250,   251,   252,     0,   253,     0,   254,
       0,   255,   256,   888,   243,   244,   245,   246,   247,   248,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   249,     0,   250,   251,   252,     0,   253,
       0,   254,     0,   255,   256,  1000,   243,   244,   245,   246,
     247,   248,     0,     0,     0,     0,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,     0,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,     0,     0,     0,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,     0,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   249,     0,   250,   251,   252,     0,   253,     0,   254,
       0,   255,   256,  1022,   243,   244,   245,   246,   247,   248,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   249,     0,   250,   251,   252,     0,   253,
       0,   254,     0,   255,   256,  1062,   243,   244,   245,   246,
     247,   248,     0,     0,     0,     0,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,     0,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,     0,     0,     0,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,     0,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   680,   238,   681,   240,   241,   242,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   249,     0,   250,   251,   252,     0,   253,     0,   254,
       0,   255,   256,  1063,   243,   244,   245,   246,   247,   248,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   249,     0,   250,   251,   252,     0,   253,
       0,   254,     0,   255,   256,  1265,   243,   244,   245,   246,
     247,   248,     0,     0,     0,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,     0,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,     0,     0,     0,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,     0,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   368,     0,
     369,   249,     0,   250,   251,   252,     0,   253,   370,   254,
       0,   255,   256,   243,   244,   245,   246,   247,   248,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     368,     0,   369,   249,     0,   250,   251,   252,     0,   253,
     370,   254,     0,   255,   256,   243,   244,   245,   246,   247,
     248,     0,     0,     0,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,     0,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,     0,     0,     0,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,     0,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   712,   713,     0,
     249,     0,   250,   251,   252,     0,   253,     0,   254,     0,
     255,   256,   243,   244,   245,   246,   247,   248,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   249,   306,   250,   251,   252,     0,   253,     0,
     254,     0,   255,   256,   243,   244,   245,   246,   247,   248,
       0,     0,     0,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   486,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,     0,     0,     0,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,     0,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   249,
       0,   250,   251,   252,     0,   253,     0,   254,     0,   255,
     256,   243,   244,   245,   246,   247,   248,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   249,     0,   250,   251,   252,     0,   253,   502,   254,
       0,   255,   256,   243,   244,   245,   246,   247,   248,     0,
       0,     0,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,     0,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,     0,     0,     0,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,     0,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   249,   506,
     250,   251,   252,     0,   253,     0,   254,     0,   255,   256,
     243,   244,   245,   246,   247,   248,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     249,     0,   250,   251,   252,     0,   253,     0,   254,   511,
     255,   256,   243,   244,   245,   246,   247,   248,     0,     0,
       0,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,     0,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
       0,     0,     0,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,     0,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   249,     0,   250,
     251,   252,     0,   253,   512,   254,     0,   255,   256,   243,
     244,   245,   246,   247,   248,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   249,
       0,   250,   251,   252,     0,   253,     0,   254,   552,   255,
     256,   243,   244,   245,   246,   247,   248,     0,     0,     0,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,     0,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,     0,
       0,     0,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,     0,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   249,     0,   250,   251,
     252,     0,   253,     0,   254,   662,   255,   256,   243,   244,
     245,   246,   247,   248,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   249,     0,
     250,   251,   252,     0,   253,   734,   254,     0,   255,   256,
     243,   244,   245,   246,   247,   248,     0,     0,     0,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
       0,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,     0,     0,
       0,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,     0,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   249,     0,   250,   251,   252,
       0,   253,     0,   254,   753,   255,   256,   243,   244,   245,
     246,   247,   248,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   249,     0,   250,
     251,   252,     0,   253,     0,   254,   756,   255,   256,   243,
     244,   245,   246,   247,   248,     0,     0,     0,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,     0,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,     0,     0,     0,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,     0,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   799,     0,     0,   249,     0,   250,   251,   252,     0,
     253,     0,   254,     0,   255,   256,   243,   244,   245,   246,
     247,   248,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   249,     0,   250,   251,
     252,     0,   253,     0,   254,   818,   255,   256,   243,   244,
     245,   246,   247,   248,     0,     0,     0,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,     0,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,     0,     0,     0,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
       0,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   249,     0,   250,   251,   252,     0,   253,
       0,   254,   833,   255,   256,   243,   244,   245,   246,   247,
     248,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   249,     0,   250,   251,   252,
       0,   253,   868,   254,     0,   255,   256,   243,   244,   245,
     246,   247,   248,     0,     0,     0,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,     0,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,     0,     0,     0,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,     0,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   249,     0,   250,   251,   252,     0,   253,     0,
     254,   869,   255,   256,   243,   244,   245,   246,   247,   248,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   249,     0,   250,   251,   252,     0,
     253,     0,   254,   870,   255,   256,   243,   244,   245,   246,
     247,   248,     0,     0,     0,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,     0,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,     0,     0,     0,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,     0,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   249,     0,   250,   251,   252,     0,   253,   886,   254,
       0,   255,   256,   243,   244,   245,   246,   247,   248,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   249,     0,   250,   251,   252,     0,   253,
     912,   254,     0,   255,   256,   243,   244,   245,   246,   247,
     248,     0,     0,     0,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,     0,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,     0,     0,     0,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,     0,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     249,     0,   250,   251,   252,     0,   253,   914,   254,     0,
     255,   256,   243,   244,   245,   246,   247,   248,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   249,     0,   250,   251,   252,     0,   253,   918,
     254,     0,   255,   256,   243,   244,   245,   246,   247,   248,
       0,     0,     0,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,     0,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,     0,     0,     0,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,     0,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   249,
       0,   250,   251,   252,     0,   253,   922,   254,     0,   255,
     256,   243,   244,   245,   246,   247,   248,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   249,     0,   250,   251,   252,     0,   253,   932,   254,
       0,   255,   256,   243,   244,   245,   246,   247,   248,     0,
       0,     0,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,     0,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,     0,     0,     0,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,     0,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   249,     0,
     250,   251,   252,     0,   253,   933,   254,     0,   255,   256,
     243,   244,   245,   246,   247,   248,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     249,     0,   250,   251,   252,     0,   253,   996,   254,     0,
     255,   256,   243,   244,   245,   246,   247,   248,     0,     0,
       0,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,     0,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
       0,     0,     0,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,     0,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   249,     0,   250,
     251,   252,     0,   253,   997,   254,     0,   255,   256,   243,
     244,   245,   246,   247,   248,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   249,
       0,   250,   251,   252,     0,   253,   998,   254,     0,   255,
     256,   243,   244,   245,   246,   247,   248,     0,     0,     0,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,     0,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,     0,
       0,     0,     0,     0,  1124,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,     0,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   249,     0,   250,   251,
     252,     0,   253,   999,   254,     0,   255,   256,   243,   244,
     245,   246,   247,   248,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   249,     0,
     250,   251,   252,     0,   253,     0,   254,     0,   255,   256,
       0,     0,     0,   243,   244,   245,   246,   247,   248,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
       0,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,     0,     0,
       0,     0,     0,     0,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,     0,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   249,     0,   250,   251,   252,
       0,   253,  1158,   254,     0,   255,   256,   243,   244,   245,
     246,   247,   248,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     249,  1201,   250,   251,   252,     0,   253,     0,   254,     0,
     255,   256,   243,   244,   245,   246,   247,   248,     0,     0,
    1213,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,     0,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   249,     0,   250,   251,   252,     0,
     253,     0,   254,     0,   255,   256,     0,     0,     0,   243,
     685,   245,   246,   247,   248,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   249,
       0,   250,   251,   252,     0,   253,     0,   254,     0,   255,
     256,    31,    32,    33,    34,    35,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    36,
     325,   326,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,     0,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,     0,     0,
       0,     0,     0,     0,     0,     0,   249,     0,   250,   251,
     252,     0,   253,     0,   254,     0,   255,   256,     0,     0,
       0,     0,     0,   104,   105,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   106,   327,   328,   329,   330,
       0,     0,     0,     0,   331,   332,   333,   334,   335,   336,
     337,   338,   339,   340,   341,     0,   342,   343,     0,     0,
       0,     0,   112,     0,   113,   114,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   115,   116,   117,
     344,   119,   120,   121,   122,    31,    32,    33,    34,    35,
       0,   123,     0,     0,     0,     0,     0,     0,     0,   345,
       0,   346,     0,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,     0,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,     0,     0,     0,     0,     0,     0,   944,   945,
     946,   947,   948,   949,   950,     0,     0,     0,   951,   952,
       0,     0,     0,     0,     0,     0,     0,   104,   105,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   106,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   107,     0,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,   112,     0,   113,   114,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   115,   116,   117,   118,   119,   120,   121,   122,    31,
      32,    33,    34,    35,     0,   123,     0,     0,     0,     0,
       0,   953,     0,   954,     0,   124,     0,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,     0,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   104,   105,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   106,   579,   328,   329,   330,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   107,     0,   108,
     109,   110,   111,     0,     0,     0,     0,     0,     0,     0,
     112,     0,   113,   114,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   115,   116,   117,   344,   119,
     120,   121,   122,    31,    32,    33,    34,    35,     0,   123,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   124,
       0,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,     0,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
       0,   581,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   104,   105,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   106,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   107,     0,   108,   109,   110,   111,     0,     0,     0,
       0,     0,   582,     0,   112,     0,   113,   114,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   115,
     116,   117,   118,   119,   120,   121,   122,    31,    32,    33,
      34,    35,     0,   123,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   124,     0,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,     0,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   104,
     105,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   106,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   107,     0,   108,   109,   110,
     111,     0,     0,     0,   708,   709,     0,     0,   112,     0,
     113,   114,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   115,   116,   117,   118,   119,   120,   121,
     122,    31,    32,    33,    34,    35,     0,   123,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   124,     0,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,     0,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   104,   105,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   106,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   107,
       0,   108,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,   112,   165,   113,   114,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   115,   116,   117,
     118,   119,   120,   121,   122,    31,    32,    33,    34,    35,
       0,   123,     0,     0,     0,     0,     0,     0,     0,   826,
       0,   124,     0,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,     0,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   104,   105,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   106,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   459,     0,   107,     0,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,   112,     0,   113,   114,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   115,   116,   117,   118,   119,   120,   121,   122,    31,
      32,    33,    34,    35,     0,   123,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   124,     0,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,     0,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   104,   105,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   106,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   107,     0,   108,
     109,   110,   111,     0,     0,     0,     0,     0,     0,     0,
     112,     0,   113,   114,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   115,   116,   117,   118,   119,
     120,   121,   122,    31,    32,    33,    34,    35,     0,   123,
       0,   472,     0,     0,     0,     0,     0,     0,     0,   124,
       0,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,     0,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   104,   105,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   106,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   107,     0,   108,   109,   110,   111,     0,     0,     0,
       0,     0,     0,     0,   112,     0,   113,   114,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   115,
     116,   117,   118,   119,   120,   121,   122,    31,    32,    33,
      34,    35,     0,   123,     0,     0,     0,     0,     0,     0,
       0,     0,   821,   124,     0,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,     0,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   104,
     105,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   106,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   107,     0,   108,   109,   110,
     111,     0,     0,     0,     0,     0,     0,     0,   112,     0,
     113,   114,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   115,   116,   117,   118,   119,   120,   121,
     122,    31,    32,    33,    34,    35,     0,   123,     0,     0,
       0,     0,     0,     0,     0,   826,     0,   124,     0,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,     0,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   104,   105,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   106,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   107,
       0,   108,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,   112,     0,   113,   114,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   115,   116,   117,
     118,   119,   120,   121,   122,    31,    32,    33,    34,    35,
       0,   123,     0,     0,     0,     0,     0,  1014,     0,     0,
       0,   124,     0,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,     0,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,     0,     0,     0,     0,     0,     0,  1092,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   104,   105,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   106,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   107,     0,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,   112,     0,   113,   114,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   115,   116,   117,   118,   119,   120,   121,   122,    31,
      32,    33,    34,    35,     0,   123,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   124,     0,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,     0,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   104,   105,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   106,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   107,     0,   108,
     109,   110,   111,     0,     0,     0,     0,     0,     0,     0,
     112,     0,   113,   114,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   115,   116,   117,   118,   119,
     120,   121,   122,    31,    32,    33,    34,    35,     0,   123,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   124,
       0,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,     0,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   104,   105,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   106,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   107,     0,   108,   109,   110,   111,     0,     0,     0,
       0,     0,     0,     0,   112,     0,   113,   114,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   115,
     116,   117,   118,   119,   120,   121,   122,    31,    32,    33,
      34,    35,     0,   463,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   124,     0,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,     0,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,     0,     0,     0,    37,    38,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   104,
     105,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   106,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   107,     0,   108,   109,   110,
     111,     0,     0,     0,    37,    38,     0,     0,   112,     0,
     916,   114,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   263,   141,   142,     0,   143,   144,
       0,     0,   145,   264,   191,     0,     0,     0,     0,     0,
       0,     0,     0,    37,    38,   265,   266,     0,     0,     0,
       0,     0,     0,   115,   116,   117,   118,   119,   120,   121,
     122,     0,     0,     0,     0,     0,   107,   123,   108,   109,
     110,   111,     0,     0,    37,    38,     0,   124,     0,   112,
     146,     0,     0,     0,   147,   148,   267,   150,   151,   152,
     153,   263,   141,   142,     0,   143,   144,     0,     0,   145,
       0,   191,     0,     0,     0,     0,     0,     0,     0,    37,
      38,     0,   265,   266,     0,     0,     0,     0,     0,     0,
       0,     0,   268,   154,     0,     0,     0,   118,   119,   120,
     121,   122,     0,   107,     0,   108,   109,   110,   111,   264,
       0,     0,     0,     0,     0,     0,   112,   146,   124,     0,
       0,   147,   148,   267,   150,   151,   152,   153,     0,     0,
       0,     0,   141,   142,     0,   143,   144,     0,     0,   145,
       0,     0,   107,     0,   108,   109,   110,   111,     0,     0,
       0,     0,     0,     0,     0,   112,     0,     0,     0,   268,
     154,     0,   527,     0,   118,   119,   120,   121,   122,     0,
       0,     0,     0,   107,     0,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,   124,   112,   146,     0,     0,
       0,   147,   148,   149,   150,   151,   152,   153,     0,     0,
       0,     0,     0,   118,   119,   120,   121,   122,   107,     0,
     108,   109,   110,   111,     0,     0,     0,     0,     0,     0,
       0,   112,     0,     0,   124,     0,     0,     0,     0,     0,
     154,     0,     0,     0,   118,   119,   120,   121,   122,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   124,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   118,
     119,   120,   121,   122,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     124
};

static const yytype_int16 yycheck[] =
{
       1,   136,   137,   138,   139,   138,   138,     8,     9,    10,
      21,   343,    13,    24,   346,   174,   959,    28,    19,    20,
     493,  1064,    23,     1,   592,   498,    27,     1,    29,   105,
     423,    32,    33,   748,   468,   101,     7,   475,   476,   477,
     351,   352,   101,   758,   115,   116,   929,    18,   672,     0,
       1,    14,   176,   874,     1,    27,    14,     1,    26,    27,
       1,   823,   691,   240,   241,   419,  1009,    14,  1176,  1042,
     120,   121,   122,  1206,   124,   125,  1209,  1210,   128,   235,
     229,   131,    33,    34,   754,   241,   756,  1195,  1196,   191,
    1224,   229,  1194,   242,  1228,  1229,   234,  1230,  1231,   229,
     413,   203,   204,   205,   206,   418,   130,   928,  1081,  1211,
    1212,   994,   242,  1247,  1248,    15,    16,    17,    18,    19,
      20,    21,   123,   235,    24,    25,   176,     0,   129,   241,
     180,   181,   182,   183,   184,   185,   186,   491,   762,   179,
      15,    16,   576,   767,    19,    20,    21,     1,   229,   240,
     241,   585,   781,  1096,   592,   236,  1099,   143,   240,  1202,
     146,   831,    15,    16,   557,   136,   137,   138,   139,   219,
     246,   605,   243,  1216,   240,   241,   234,   279,   940,    33,
      34,   240,   241,   124,   235,   309,  1129,   188,   235,   235,
     241,   235,   133,   134,   241,   241,   235,   241,   235,   235,
     242,   235,   241,   305,   241,   241,   308,   241,   241,   311,
     243,   162,   213,   164,   165,   166,   167,   841,   241,   235,
     243,   789,   234,  1166,   175,   241,   794,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   234,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,     1,   254,   969,   234,   257,  1200,   259,   260,
     261,   229,   116,   235,   242,   228,   240,   241,   706,   707,
     228,   235,   223,   224,   225,   226,   227,   241,   246,   234,
     591,   228,   235,   125,    33,    34,   287,   288,   241,   236,
     234,   234,   263,   244,   241,   235,   243,   428,   242,   234,
     240,   302,   303,   237,   406,   306,   240,   637,   162,   639,
     164,   165,   166,   167,   285,   446,   447,   240,   241,   290,
     422,   175,   323,   324,   240,   241,   327,   328,   329,   330,
     331,   332,   121,   304,   234,   241,   236,   243,   238,   239,
     774,   342,   343,   234,   345,     1,   784,   785,   319,   787,
     351,   352,   786,   241,   234,   243,   829,   795,   796,   234,
     241,   236,   243,   238,   239,   699,   700,   701,   702,   223,
     224,   225,   226,   227,   240,   241,   102,    33,    34,   105,
     241,   234,   243,   236,   385,   238,   239,   176,   240,   241,
     244,   180,   181,   182,   241,   396,   185,   186,   102,   410,
     411,   105,    15,    16,    17,    18,    19,    20,    21,     3,
     541,     5,   846,   162,   236,   164,   165,   166,   167,   240,
     241,   240,   241,   240,   241,   236,   175,   176,   240,   241,
     183,   432,   433,   240,   241,     1,   241,   539,   171,   172,
     241,   572,   573,   144,   145,   240,   241,   240,   419,   240,
     241,   229,   423,     1,   240,   456,   241,   458,   240,   241,
     431,   241,   463,   115,   116,   240,   241,   468,   469,   240,
     241,   472,   959,   960,   223,   224,   225,   226,   227,   241,
     481,   241,   234,     1,   235,   486,   236,   235,     1,   236,
     119,   234,   493,   229,   236,   244,   242,   498,   242,   236,
     631,   603,   242,   241,    19,   506,   162,   241,   164,   165,
     166,   167,   513,   514,   229,    33,    34,   236,   229,   175,
     491,   652,   229,   494,   495,   160,   497,   229,   630,   229,
     236,   245,   229,   664,   229,   234,   229,   229,   234,   177,
     177,   235,     1,   147,   229,   236,   236,     3,   982,   237,
     551,   240,   654,   554,   240,   121,   122,   123,   124,   125,
     243,   236,   128,   240,   242,   229,   242,   223,   224,   225,
     226,   227,   234,   121,   122,   576,   124,   125,   579,   234,
     128,   241,   243,   554,   585,   586,   557,   229,   244,   560,
     591,   242,   241,   241,   177,   177,   567,   240,   599,   235,
     168,   602,   761,   236,   605,   102,   177,   177,   242,   237,
     176,   242,   242,   235,   180,   181,   182,   183,   184,   185,
     186,   234,   243,   236,   625,   238,   239,   242,   176,    12,
     235,   241,   180,   181,   182,   183,   184,   185,   186,   640,
     235,   642,   235,    26,   162,   241,   164,   165,   166,   167,
     240,   242,   984,   219,     3,   234,   237,   175,   235,   237,
     661,   151,   242,   102,   229,   229,     1,   229,   242,   235,
     805,   219,   805,   805,   177,    17,   229,    17,    26,   680,
     681,    27,   683,   229,   685,   243,   235,   235,   235,   177,
     825,   235,   825,   235,   237,     1,   237,   177,    33,    34,
     237,   246,   235,   243,   243,   223,   224,   225,   226,   227,
     711,   712,   713,   242,   235,   243,   243,   229,   229,   235,
     243,   235,   132,   240,   826,   235,   244,    33,    34,   234,
     234,   237,   115,   229,   735,   237,   243,   229,   229,   170,
     229,   178,   243,   744,   243,   243,   135,   748,   242,     1,
     135,   234,   234,   136,   137,   240,   139,   758,   242,   240,
     234,   240,   240,   234,   234,   240,   229,   240,   240,   770,
     114,   772,   240,   774,   157,   776,   240,   234,   240,   780,
     229,    33,    34,   243,   235,   786,    15,    16,    17,    18,
      19,    20,    21,   176,   229,    24,    25,   235,   799,   108,
     240,   144,   803,   229,   240,   806,   234,   808,   191,   810,
     811,   812,   813,   814,   243,   234,   243,   235,   242,   242,
     203,   204,   205,   206,   240,   826,   209,   162,   829,   164,
     165,   166,   167,   242,   805,   242,   242,   242,   242,   229,
     175,   229,   137,   136,   138,   846,   137,   229,   240,   139,
     243,   140,   853,   240,   240,     6,   162,   172,   164,   165,
     166,   167,   240,   240,   243,   967,   240,   243,   243,   175,
     243,   243,   255,   240,   644,   876,   309,   878,   940,  1123,
     539,   264,   290,   884,   885,   268,   887,   967,   223,   224,
     225,   226,   227,   431,    25,   896,   279,   654,   630,   719,
     989,  1047,  1004,  1048,  1118,  1007,  1192,  1204,   291,   244,
     162,     1,   164,   165,   166,   167,  1017,   223,   224,   225,
     226,   227,   305,   175,  1246,   308,   309,    15,   311,  1064,
     960,  1064,  1171,    16,   317,   318,   666,  1110,   244,   319,
     567,   973,   971,    33,    34,  1191,  1189,   472,   319,  1078,
     951,   952,   779,    -1,   780,   642,    -1,    -1,   959,   960,
      -1,    -1,    -1,    -1,    -1,    -1,   967,    -1,   969,    -1,
     971,   223,   224,   225,   226,   227,    -1,    -1,    -1,    -1,
      -1,   982,   983,    -1,    -1,    -1,   987,    -1,  1090,    -1,
      -1,    -1,   244,    -1,    -1,    -1,  1007,    -1,    -1,    -1,
      -1,  1012,   231,   232,    -1,   234,    -1,   236,  1009,   238,
     239,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,
      -1,    -1,    -1,   406,    -1,    -1,    -1,    -1,    -1,   412,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   422,
      -1,  1042,    -1,    -1,    -1,    -1,  1148,  1058,    33,    34,
    1061,    -1,  1053,    -1,    -1,    -1,    -1,    -1,   441,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   450,   451,    -1,
      -1,    -1,   162,    -1,   164,   165,   166,   167,  1180,    -1,
    1081,    -1,    -1,    -1,   467,   175,    -1,  1098,   471,    -1,
      -1,   474,   475,   476,   477,  1096,    -1,    -1,  1099,    -1,
      -1,    -1,    -1,  1104,    -1,    -1,    -1,    -1,    -1,    -1,
    1111,   494,   495,   496,   497,    -1,    -1,    -1,    -1,  1130,
    1091,    -1,  1123,  1124,    -1,    -1,  1097,    -1,  1129,    -1,
      -1,    -1,    -1,   223,   224,   225,   226,   227,    -1,   522,
     523,  1152,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   536,   244,    -1,   539,    -1,    -1,    -1,
      -1,   544,    -1,    -1,     1,  1166,    -1,    -1,  1169,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1147,   162,  1179,   164,
     165,   166,   167,    -1,    -1,    -1,    -1,    -1,  1189,    -1,
     175,     0,     1,    -1,    -1,    -1,    33,    34,    -1,  1200,
      -1,    -1,    -1,  1204,   587,    -1,    -1,  1208,    -1,   592,
    1181,  1222,  1213,    -1,    -1,    -1,  1217,    -1,    -1,    -1,
     603,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1234,    -1,    -1,    -1,    -1,   223,   224,
     225,   226,   227,  1214,    -1,    -1,    -1,   630,    -1,    -1,
      -1,    -1,  1253,    -1,   637,    -1,   639,    -1,    -1,   244,
      -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   654,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   666,   121,   122,   123,   124,   125,    -1,
      -1,   128,   129,   130,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   691,    -1,
      -1,   120,   121,   122,    -1,   124,   125,    -1,    -1,   128,
      -1,   130,    -1,   706,   707,   162,    -1,   164,   165,   166,
     167,    -1,   141,   142,    -1,    -1,    -1,    -1,   175,   176,
      -1,    -1,    -1,   180,   181,   182,   183,   184,   185,   186,
      -1,    -1,    -1,   162,    -1,   164,   165,   166,   167,    -1,
      -1,    -1,    33,    34,    -1,    -1,   175,   176,    -1,    -1,
      -1,   180,   181,   182,   183,   184,   185,   186,    -1,    -1,
      -1,    -1,   219,    -1,    -1,    -1,   223,   224,   225,   226,
     227,    -1,    -1,    -1,   777,    -1,    -1,    -1,   781,    -1,
      -1,   784,   785,    -1,   787,    -1,   789,   244,    -1,   218,
     219,   794,   795,   796,   223,   224,   225,   226,   227,    -1,
      -1,    -1,    -1,   162,    -1,   164,   165,   166,   167,    -1,
      -1,    -1,    -1,    -1,    -1,   244,   175,    -1,    -1,    -1,
     823,   824,    -1,   826,    -1,    -1,    15,    16,    17,    18,
      19,    20,    21,    -1,   837,    24,    25,    -1,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    -1,    28,   144,   145,    -1,     1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   223,   224,   225,   226,   227,    -1,
     873,   162,    -1,   164,   165,   166,   167,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   175,   244,     0,     1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    -1,    -1,
      -1,    -1,    -1,    -1,   927,   101,   102,   103,   104,   105,
     106,    -1,   223,   224,   225,   226,   227,   940,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      -1,    -1,    -1,   244,   121,   122,    -1,   124,   125,    -1,
      -1,   128,    -1,    -1,   967,    -1,    -1,    -1,    -1,    -1,
     973,    -1,   975,   976,   977,    -1,   121,   122,    -1,   124,
     125,    -1,    -1,   128,    -1,    -1,   989,   101,   102,   103,
     104,   105,   106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1004,    -1,    -1,  1007,    -1,    -1,    -1,    -1,   176,
      -1,    -1,    -1,   180,   181,   182,   183,   184,   185,   186,
      -1,    -1,    -1,    -1,    -1,   101,   102,   103,   104,   105,
     106,   176,    -1,  1036,    -1,   180,   181,   182,   183,   184,
     185,   186,   231,   232,  1047,   234,  1049,   236,   237,   238,
     239,   240,   219,    -1,   230,   231,   232,    -1,   234,    -1,
     236,    -1,   238,   239,    -1,    -1,  1069,    -1,    -1,  1072,
      -1,    -1,    -1,    -1,   219,    -1,   243,    -1,    -1,    -1,
      15,    16,    17,    18,    19,    20,    21,  1090,    23,    24,
      25,    -1,    15,    16,    17,    18,    19,    20,    21,    -1,
      -1,    24,    25,    -1,    -1,  1108,    -1,  1110,    -1,    -1,
      -1,    -1,  1115,  1116,   228,  1118,   230,   231,   232,    -1,
     234,    -1,   236,    -1,   238,   239,    -1,   241,    -1,   243,
      -1,    -1,    -1,  1136,    -1,    -1,    -1,    -1,    -1,    -1,
    1143,  1144,    -1,    -1,    -1,  1148,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   230,   231,   232,    -1,   234,     1,
     236,    -1,   238,   239,    -1,    -1,   101,   102,   103,   104,
     105,   106,    14,    15,    16,    17,    18,  1180,   101,   102,
     103,   104,   105,   106,    -1,    -1,    -1,    -1,    -1,  1192,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    -1,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,    15,
      16,    17,    18,    19,    20,    21,    -1,    -1,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   121,
     122,    -1,   124,   125,   126,   127,   128,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   230,   231,   232,    -1,   234,
      -1,   236,    -1,   238,   239,    -1,   148,   230,   231,   232,
      -1,   234,    -1,   236,    -1,   238,   239,    -1,    -1,    -1,
     162,    -1,   164,   165,   166,   167,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   175,   176,   177,   178,    -1,   180,   181,
     182,   183,   184,   185,   186,   101,   102,   103,   104,   105,
     106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    33,    34,     1,    -1,    -1,    -1,   219,   220,   221,
     222,   223,   224,   225,   226,   227,    14,    15,    16,    17,
      18,     1,   234,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   244,    -1,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    -1,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,    -1,    -1,   231,   232,    -1,   234,    -1,
     236,    -1,   238,   239,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   126,   127,
     162,    -1,   164,   165,   166,   167,    -1,    -1,    -1,    -1,
      -1,   121,   122,   175,   124,   125,    -1,    -1,   128,    -1,
     148,   149,   150,   151,   152,    -1,    -1,    -1,    -1,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
      -1,   169,   170,    -1,    -1,    -1,    -1,   175,    -1,   177,
     178,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   223,   224,   225,   226,   227,   176,    -1,   230,    -1,
     180,   181,   182,   183,   184,   185,   186,    -1,    -1,    -1,
      -1,    -1,   244,    -1,    -1,    -1,    -1,     1,    -1,    -1,
      -1,    -1,   220,   221,   222,   223,   224,   225,   226,   227,
      14,    15,    16,    17,    18,     1,   234,    -1,    -1,   219,
      -1,    -1,    -1,    -1,   242,   243,   244,    -1,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    -1,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,    -1,    -1,    -1,
      -1,    -1,    -1,   107,   108,   109,   110,   111,   112,   113,
      -1,   115,   116,   117,   118,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   126,   127,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   121,   122,   123,   124,   125,
      -1,    -1,   128,    -1,   148,   131,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,    -1,
     164,   165,   166,   167,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   175,    -1,   177,   178,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     176,    -1,    -1,    -1,   180,   181,   182,   183,   184,   185,
     186,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,
      34,     1,    -1,    -1,    -1,    -1,   220,   221,   222,   223,
     224,   225,   226,   227,    14,    15,    16,    17,    18,     1,
     234,    -1,    -1,   219,    -1,    -1,   240,    -1,   242,   243,
     244,    -1,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      -1,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,    -1,    -1,    -1,    -1,    -1,    -1,   107,   108,   109,
     110,   111,   112,   113,    -1,   115,   116,   117,   118,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   126,   127,   162,    -1,
     164,   165,   166,   167,    -1,    -1,    -1,    -1,    -1,   121,
     122,   175,   124,   125,    -1,    -1,   128,    -1,   148,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   162,    -1,   164,   165,   166,   167,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   175,    -1,   177,   178,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   223,
     224,   225,   226,   227,   176,    -1,    -1,    -1,   180,   181,
     182,   183,   184,   185,   186,    33,    34,    -1,    -1,   243,
     244,    -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,
     220,   221,   222,   223,   224,   225,   226,   227,    14,    15,
      16,    17,    18,    -1,   234,    -1,    -1,   219,    -1,    -1,
     240,    -1,   242,   243,   244,    -1,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    -1,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,    -1,    -1,    -1,    -1,    -1,
      -1,   107,   108,   109,   110,   111,   112,   113,    -1,    -1,
      -1,   117,   118,    -1,   162,    -1,   164,   165,   166,   167,
     126,   127,    -1,    -1,    -1,    -1,    -1,   175,   176,   121,
     122,   123,   124,   125,    -1,    -1,   128,    -1,   130,    -1,
      -1,    -1,   148,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   162,    -1,   164,   165,
     166,   167,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   175,
      -1,   177,   178,    -1,    -1,   223,   224,   225,   226,   227,
      -1,    -1,    -1,    -1,   176,    -1,    -1,    -1,   180,   181,
     182,   183,   184,   185,   186,    -1,   244,    -1,    33,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      33,    34,    -1,    -1,   220,   221,   222,   223,   224,   225,
     226,   227,    14,    15,    16,    17,    18,   219,   234,    -1,
      -1,    -1,    -1,    -1,   240,    -1,   242,   243,   244,    -1,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    -1,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,    -1,
      -1,    -1,    -1,    -1,    -1,   107,   108,   109,   110,   111,
     112,   113,    -1,    -1,    -1,   117,   118,   162,    -1,   164,
     165,   166,   167,    -1,   126,   127,    -1,    -1,    -1,   162,
     175,   164,   165,   166,   167,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   175,    -1,    -1,    -1,   148,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     162,    -1,   164,   165,   166,   167,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   175,    -1,   177,   178,    -1,   223,   224,
     225,   226,   227,    -1,    -1,    -1,    -1,    -1,    -1,   234,
     223,   224,   225,   226,   227,    -1,    -1,    -1,    -1,   244,
      -1,   234,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,   244,    -1,     1,    -1,    33,    34,    -1,   220,   221,
     222,   223,   224,   225,   226,   227,    14,    15,    16,    17,
      18,    -1,   234,    -1,    -1,    -1,    -1,    -1,   240,    -1,
     242,   243,   244,    -1,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    -1,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,    15,    16,    17,    18,    19,    20,    21,
      -1,    -1,    24,    25,    -1,    -1,   144,    -1,    -1,    -1,
      -1,    -1,   162,    -1,   164,   165,   166,   167,   126,   127,
      -1,    -1,    -1,    -1,   162,   175,   164,   165,   166,   167,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   175,    -1,    -1,
     148,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   162,    -1,   164,   165,   166,   167,
      -1,    -1,    -1,   171,   172,    -1,    -1,   175,    -1,   177,
     178,    -1,    -1,   223,   224,   225,   226,   227,    -1,   101,
     102,    -1,    -1,   105,   106,   223,   224,   225,   226,   227,
      -1,    -1,    -1,    -1,   244,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   244,     1,    -1,   217,
      -1,    -1,   220,   221,   222,   223,   224,   225,   226,   227,
      14,    15,    16,    17,    18,    -1,   234,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   244,    -1,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    -1,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,    -1,    -1,   231,
     232,    -1,   234,    -1,   236,    -1,   238,   239,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   126,   127,    -1,    -1,    -1,    -1,    -1,    -1,
     120,   121,   122,    -1,   124,   125,    -1,    -1,   128,    -1,
      -1,    -1,    -1,    -1,   148,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,    -1,
     164,   165,   166,   167,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   175,    -1,   177,   178,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   176,    -1,    -1,    -1,
     180,   181,   182,   183,   184,   185,   186,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    -1,    -1,    -1,    -1,   220,   221,   222,   223,
     224,   225,   226,   227,    14,    15,    16,    17,    18,   219,
     234,    -1,    -1,    -1,    -1,    -1,   240,    -1,    -1,    -1,
     244,    -1,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      -1,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   126,   127,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   121,   122,   123,   124,   125,
      -1,    -1,   128,    -1,    -1,    -1,    -1,    -1,   148,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   162,    -1,   164,   165,   166,   167,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   175,   176,   177,   178,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     176,    -1,    -1,    -1,   180,   181,   182,   183,   184,   185,
     186,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,
     220,   221,   222,   223,   224,   225,   226,   227,    14,    15,
      16,    17,    18,   219,   234,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   244,    -1,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    -1,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     126,   127,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   121,
     122,   123,   124,   125,    -1,    -1,   128,    -1,    -1,    -1,
      -1,    -1,   148,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   162,    -1,   164,   165,
     166,   167,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   175,
      -1,   177,   178,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   176,    -1,    -1,    -1,   180,   181,
     182,   183,   184,   185,   186,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      -1,    -1,    -1,    -1,   220,   221,   222,   223,   224,   225,
     226,   227,    14,    15,    16,    17,    18,   219,   234,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   244,    -1,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    -1,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   126,   127,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   121,   122,    -1,   124,   125,    -1,    -1,
     128,    -1,    -1,    -1,    -1,    -1,   148,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     162,    -1,   164,   165,   166,   167,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   175,    -1,   177,   178,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   176,    -1,
      -1,    -1,   180,   181,   182,   183,   184,   185,   186,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,   220,   221,
     222,   223,   224,   225,   226,   227,    14,    15,    16,    17,
      18,   219,   234,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   244,    -1,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    -1,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   126,   127,
      -1,    -1,    -1,    -1,   140,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     148,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   162,    -1,   164,   165,   166,   167,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   175,    -1,   177,
     178,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,
      -1,    -1,   220,   221,   222,   223,   224,   225,   226,   227,
      14,    15,    16,    17,    18,    -1,   234,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   244,    -1,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    -1,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   126,   127,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   148,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,    -1,
     164,   165,   166,   167,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   175,    -1,   177,   178,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    -1,    -1,    -1,    -1,   220,   221,   222,   223,
     224,   225,   226,   227,    14,    15,    16,    17,    18,    -1,
     234,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     244,    -1,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      -1,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   126,   127,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   148,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   162,    -1,   164,   165,   166,   167,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   175,    -1,   177,   178,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,
     220,   221,   222,   223,   224,   225,   226,   227,    14,    15,
      16,    17,    18,    -1,   234,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   244,    -1,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    -1,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     126,   127,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,
      -1,    -1,   148,    -1,    -1,    -1,    -1,    -1,   121,   122,
      -1,   124,   125,    -1,    -1,   128,   162,    -1,   164,   165,
     166,   167,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   175,
      -1,   177,   178,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    -1,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    -1,   176,    -1,    -1,    -1,   180,   181,   182,
     183,   184,   185,   186,   220,   221,   222,   223,   224,   225,
     226,   227,   120,   121,   122,    -1,   124,   125,   234,    -1,
     128,   129,   130,    -1,    -1,    -1,    -1,    -1,   244,    -1,
      -1,    -1,    -1,   141,   142,    -1,   219,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   162,    -1,   164,   165,   166,   167,
     243,   101,   102,   103,   104,   105,   106,   175,   176,    -1,
      -1,    -1,   180,   181,   182,   183,   184,   185,   186,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    -1,    -1,
     218,   219,    -1,    -1,    -1,   223,   224,   225,   226,   227,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     0,     1,   244,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,   102,   103,
     104,   105,   106,    -1,    -1,    -1,    -1,    -1,   228,    -1,
     230,   231,   232,    -1,   234,    -1,   236,    -1,   238,   239,
     240,    -1,    -1,   243,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   121,   122,    -1,   124,   125,
      -1,    -1,   128,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   101,   102,   103,   104,   105,
     106,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
     176,    -1,    -1,    -1,   180,   181,   182,   183,   184,   185,
     186,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   228,    -1,   230,   231,   232,    -1,
     234,    -1,   236,   219,   238,   239,    -1,    -1,    -1,   243,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   235,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,
     102,   103,   104,   105,   106,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   228,    -1,   230,   231,   232,    -1,   234,    -1,
     236,    -1,   238,   239,   240,    -1,    -1,    -1,    -1,    -1,
      -1,     0,     1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    -1,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,     1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   228,    -1,   230,   231,
     232,    -1,   234,    -1,   236,    -1,   238,   239,    -1,    -1,
      -1,   243,   101,   102,   103,   104,   105,   106,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   101,   102,   103,   104,   105,   106,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    -1,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    -1,    -1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   228,
      -1,   230,   231,   232,    -1,   234,    -1,   236,    -1,   238,
     239,   101,   102,   103,   104,   105,   106,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     228,    -1,   230,   231,   232,    -1,   234,    -1,   236,    -1,
     238,   239,   240,   101,   102,   103,   104,   105,   106,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    -1,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    -1,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    -1,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   228,    -1,
     230,   231,   232,    -1,   234,   235,   236,    -1,   238,   239,
      -1,   241,   101,   102,   103,   104,   105,   106,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     228,    -1,   230,   231,   232,    -1,   234,    -1,   236,    -1,
     238,   239,    -1,   241,   101,   102,   103,   104,   105,   106,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    -1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   228,
      -1,   230,   231,   232,    -1,   234,    -1,   236,    -1,   238,
     239,    -1,   241,   101,   102,   103,   104,   105,   106,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   228,    -1,   230,   231,   232,    -1,   234,    -1,   236,
      -1,   238,   239,    -1,   241,   101,   102,   103,   104,   105,
     106,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    -1,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     228,    -1,   230,   231,   232,    -1,   234,    -1,   236,    -1,
     238,   239,    -1,   241,   101,   102,   103,   104,   105,   106,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   228,    -1,   230,   231,   232,    -1,   234,    -1,
     236,    -1,   238,   239,    -1,   241,   101,   102,   103,   104,
     105,   106,    -1,    -1,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    -1,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   228,   229,   230,   231,   232,    -1,   234,    -1,   236,
      -1,   238,   239,   240,   101,   102,   103,   104,   105,   106,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   228,    -1,   230,   231,   232,    -1,   234,
      -1,   236,    -1,   238,   239,   240,   101,   102,   103,   104,
     105,   106,    -1,    -1,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    -1,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   228,    -1,   230,   231,   232,    -1,   234,    -1,   236,
      -1,   238,   239,   240,   101,   102,   103,   104,   105,   106,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   228,    -1,   230,   231,   232,    -1,   234,
      -1,   236,    -1,   238,   239,   240,   101,   102,   103,   104,
     105,   106,    -1,    -1,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    -1,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   228,    -1,   230,   231,   232,    -1,   234,    -1,   236,
      -1,   238,   239,   240,   101,   102,   103,   104,   105,   106,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   228,    -1,   230,   231,   232,    -1,   234,
      -1,   236,    -1,   238,   239,   240,   101,   102,   103,   104,
     105,   106,    -1,    -1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    -1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   225,    -1,
     227,   228,    -1,   230,   231,   232,    -1,   234,   235,   236,
      -1,   238,   239,   101,   102,   103,   104,   105,   106,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     225,    -1,   227,   228,    -1,   230,   231,   232,    -1,   234,
     235,   236,    -1,   238,   239,   101,   102,   103,   104,   105,
     106,    -1,    -1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    -1,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    -1,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    -1,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   225,   226,    -1,
     228,    -1,   230,   231,   232,    -1,   234,    -1,   236,    -1,
     238,   239,   101,   102,   103,   104,   105,   106,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   228,   229,   230,   231,   232,    -1,   234,    -1,
     236,    -1,   238,   239,   101,   102,   103,   104,   105,   106,
      -1,    -1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,   153,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    -1,    -1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   228,
      -1,   230,   231,   232,    -1,   234,    -1,   236,    -1,   238,
     239,   101,   102,   103,   104,   105,   106,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   228,    -1,   230,   231,   232,    -1,   234,   235,   236,
      -1,   238,   239,   101,   102,   103,   104,   105,   106,    -1,
      -1,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    -1,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    -1,    -1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    -1,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   228,   229,
     230,   231,   232,    -1,   234,    -1,   236,    -1,   238,   239,
     101,   102,   103,   104,   105,   106,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     228,    -1,   230,   231,   232,    -1,   234,    -1,   236,   237,
     238,   239,   101,   102,   103,   104,   105,   106,    -1,    -1,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      -1,    -1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    -1,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   228,    -1,   230,
     231,   232,    -1,   234,   235,   236,    -1,   238,   239,   101,
     102,   103,   104,   105,   106,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   228,
      -1,   230,   231,   232,    -1,   234,    -1,   236,   237,   238,
     239,   101,   102,   103,   104,   105,   106,    -1,    -1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    -1,
      -1,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    -1,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   228,    -1,   230,   231,
     232,    -1,   234,    -1,   236,   237,   238,   239,   101,   102,
     103,   104,   105,   106,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   228,    -1,
     230,   231,   232,    -1,   234,   235,   236,    -1,   238,   239,
     101,   102,   103,   104,   105,   106,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    -1,    -1,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   228,    -1,   230,   231,   232,
      -1,   234,    -1,   236,   237,   238,   239,   101,   102,   103,
     104,   105,   106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   228,    -1,   230,
     231,   232,    -1,   234,    -1,   236,   237,   238,   239,   101,
     102,   103,   104,   105,   106,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    -1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   225,    -1,    -1,   228,    -1,   230,   231,   232,    -1,
     234,    -1,   236,    -1,   238,   239,   101,   102,   103,   104,
     105,   106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   228,    -1,   230,   231,
     232,    -1,   234,    -1,   236,   237,   238,   239,   101,   102,
     103,   104,   105,   106,    -1,    -1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   228,    -1,   230,   231,   232,    -1,   234,
      -1,   236,   237,   238,   239,   101,   102,   103,   104,   105,
     106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   228,    -1,   230,   231,   232,
      -1,   234,   235,   236,    -1,   238,   239,   101,   102,   103,
     104,   105,   106,    -1,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    -1,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   228,    -1,   230,   231,   232,    -1,   234,    -1,
     236,   237,   238,   239,   101,   102,   103,   104,   105,   106,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   228,    -1,   230,   231,   232,    -1,
     234,    -1,   236,   237,   238,   239,   101,   102,   103,   104,
     105,   106,    -1,    -1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    -1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   228,    -1,   230,   231,   232,    -1,   234,   235,   236,
      -1,   238,   239,   101,   102,   103,   104,   105,   106,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   228,    -1,   230,   231,   232,    -1,   234,
     235,   236,    -1,   238,   239,   101,   102,   103,   104,   105,
     106,    -1,    -1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    -1,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    -1,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    -1,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     228,    -1,   230,   231,   232,    -1,   234,   235,   236,    -1,
     238,   239,   101,   102,   103,   104,   105,   106,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   228,    -1,   230,   231,   232,    -1,   234,   235,
     236,    -1,   238,   239,   101,   102,   103,   104,   105,   106,
      -1,    -1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    -1,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    -1,    -1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   228,
      -1,   230,   231,   232,    -1,   234,   235,   236,    -1,   238,
     239,   101,   102,   103,   104,   105,   106,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   228,    -1,   230,   231,   232,    -1,   234,   235,   236,
      -1,   238,   239,   101,   102,   103,   104,   105,   106,    -1,
      -1,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    -1,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    -1,    -1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    -1,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   228,    -1,
     230,   231,   232,    -1,   234,   235,   236,    -1,   238,   239,
     101,   102,   103,   104,   105,   106,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     228,    -1,   230,   231,   232,    -1,   234,   235,   236,    -1,
     238,   239,   101,   102,   103,   104,   105,   106,    -1,    -1,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      -1,    -1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    -1,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   228,    -1,   230,
     231,   232,    -1,   234,   235,   236,    -1,   238,   239,   101,
     102,   103,   104,   105,   106,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   228,
      -1,   230,   231,   232,    -1,   234,   235,   236,    -1,   238,
     239,   101,   102,   103,   104,   105,   106,    -1,    -1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    -1,
      -1,    -1,    -1,    -1,   144,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   228,    -1,   230,   231,
     232,    -1,   234,   235,   236,    -1,   238,   239,   101,   102,
     103,   104,   105,   106,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   228,    -1,
     230,   231,   232,    -1,   234,    -1,   236,    -1,   238,   239,
      -1,    -1,    -1,   101,   102,   103,   104,   105,   106,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    -1,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   228,    -1,   230,   231,   232,
      -1,   234,   235,   236,    -1,   238,   239,   101,   102,   103,
     104,   105,   106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     228,   229,   230,   231,   232,    -1,   234,    -1,   236,    -1,
     238,   239,   101,   102,   103,   104,   105,   106,    -1,    -1,
     144,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   228,    -1,   230,   231,   232,    -1,
     234,    -1,   236,    -1,   238,   239,    -1,    -1,    -1,   101,
     102,   103,   104,   105,   106,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   228,
      -1,   230,   231,   232,    -1,   234,    -1,   236,    -1,   238,
     239,    14,    15,    16,    17,    18,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    -1,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   228,    -1,   230,   231,
     232,    -1,   234,    -1,   236,    -1,   238,   239,    -1,    -1,
      -1,    -1,    -1,   126,   127,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   148,   149,   150,   151,   152,
      -1,    -1,    -1,    -1,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,    -1,   169,   170,    -1,    -1,
      -1,    -1,   175,    -1,   177,   178,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   220,   221,   222,
     223,   224,   225,   226,   227,    14,    15,    16,    17,    18,
      -1,   234,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   242,
      -1,   244,    -1,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    -1,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,    -1,    -1,    -1,    -1,    -1,    -1,   107,   108,
     109,   110,   111,   112,   113,    -1,    -1,    -1,   117,   118,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   126,   127,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   148,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   162,    -1,   164,   165,   166,   167,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   175,    -1,   177,   178,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   220,   221,   222,   223,   224,   225,   226,   227,    14,
      15,    16,    17,    18,    -1,   234,    -1,    -1,    -1,    -1,
      -1,   240,    -1,   242,    -1,   244,    -1,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    -1,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   126,   127,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   148,   149,   150,   151,   152,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,    -1,   164,
     165,   166,   167,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     175,    -1,   177,   178,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   220,   221,   222,   223,   224,
     225,   226,   227,    14,    15,    16,    17,    18,    -1,   234,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   244,
      -1,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    -1,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
      -1,   102,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   126,   127,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   148,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   162,    -1,   164,   165,   166,   167,    -1,    -1,    -1,
      -1,    -1,   173,    -1,   175,    -1,   177,   178,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   220,
     221,   222,   223,   224,   225,   226,   227,    14,    15,    16,
      17,    18,    -1,   234,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   244,    -1,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    -1,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   126,
     127,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   148,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   162,    -1,   164,   165,   166,
     167,    -1,    -1,    -1,   171,   172,    -1,    -1,   175,    -1,
     177,   178,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   220,   221,   222,   223,   224,   225,   226,
     227,    14,    15,    16,    17,    18,    -1,   234,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   244,    -1,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    -1,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   126,   127,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   148,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,
      -1,   164,   165,   166,   167,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   175,   176,   177,   178,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   220,   221,   222,
     223,   224,   225,   226,   227,    14,    15,    16,    17,    18,
      -1,   234,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   242,
      -1,   244,    -1,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    -1,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   126,   127,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   148,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   160,    -1,   162,    -1,   164,   165,   166,   167,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   175,    -1,   177,   178,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   220,   221,   222,   223,   224,   225,   226,   227,    14,
      15,    16,    17,    18,    -1,   234,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   244,    -1,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    -1,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   126,   127,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   148,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,    -1,   164,
     165,   166,   167,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     175,    -1,   177,   178,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   220,   221,   222,   223,   224,
     225,   226,   227,    14,    15,    16,    17,    18,    -1,   234,
      -1,   236,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   244,
      -1,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    -1,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   126,   127,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   148,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   162,    -1,   164,   165,   166,   167,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   175,    -1,   177,   178,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   220,
     221,   222,   223,   224,   225,   226,   227,    14,    15,    16,
      17,    18,    -1,   234,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   243,   244,    -1,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    -1,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   126,
     127,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   148,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   162,    -1,   164,   165,   166,
     167,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   175,    -1,
     177,   178,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   220,   221,   222,   223,   224,   225,   226,
     227,    14,    15,    16,    17,    18,    -1,   234,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   242,    -1,   244,    -1,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    -1,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   126,   127,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   148,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,
      -1,   164,   165,   166,   167,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   175,    -1,   177,   178,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   220,   221,   222,
     223,   224,   225,   226,   227,    14,    15,    16,    17,    18,
      -1,   234,    -1,    -1,    -1,    -1,    -1,   240,    -1,    -1,
      -1,   244,    -1,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    -1,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,    -1,    -1,    -1,    -1,    -1,    -1,   107,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   126,   127,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   148,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   162,    -1,   164,   165,   166,   167,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   175,    -1,   177,   178,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   220,   221,   222,   223,   224,   225,   226,   227,    14,
      15,    16,    17,    18,    -1,   234,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   244,    -1,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    -1,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   126,   127,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   148,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,    -1,   164,
     165,   166,   167,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     175,    -1,   177,   178,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   220,   221,   222,   223,   224,
     225,   226,   227,    14,    15,    16,    17,    18,    -1,   234,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   244,
      -1,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    -1,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   126,   127,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   148,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   162,    -1,   164,   165,   166,   167,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   175,    -1,   177,   178,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   220,
     221,   222,   223,   224,   225,   226,   227,    14,    15,    16,
      17,    18,    -1,   234,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   244,    -1,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    -1,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,    -1,    -1,    -1,    33,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   126,
     127,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   148,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   162,    -1,   164,   165,   166,
     167,    -1,    -1,    -1,    33,    34,    -1,    -1,   175,    -1,
     177,   178,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   120,   121,   122,    -1,   124,   125,
      -1,    -1,   128,   129,   130,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    33,    34,   141,   142,    -1,    -1,    -1,
      -1,    -1,    -1,   220,   221,   222,   223,   224,   225,   226,
     227,    -1,    -1,    -1,    -1,    -1,   162,   234,   164,   165,
     166,   167,    -1,    -1,    33,    34,    -1,   244,    -1,   175,
     176,    -1,    -1,    -1,   180,   181,   182,   183,   184,   185,
     186,   120,   121,   122,    -1,   124,   125,    -1,    -1,   128,
      -1,   130,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,
      34,    -1,   141,   142,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   218,   219,    -1,    -1,    -1,   223,   224,   225,
     226,   227,    -1,   162,    -1,   164,   165,   166,   167,   129,
      -1,    -1,    -1,    -1,    -1,    -1,   175,   176,   244,    -1,
      -1,   180,   181,   182,   183,   184,   185,   186,    -1,    -1,
      -1,    -1,   121,   122,    -1,   124,   125,    -1,    -1,   128,
      -1,    -1,   162,    -1,   164,   165,   166,   167,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   175,    -1,    -1,    -1,   218,
     219,    -1,   116,    -1,   223,   224,   225,   226,   227,    -1,
      -1,    -1,    -1,   162,    -1,   164,   165,   166,   167,    -1,
      -1,    -1,    -1,    -1,    -1,   244,   175,   176,    -1,    -1,
      -1,   180,   181,   182,   183,   184,   185,   186,    -1,    -1,
      -1,    -1,    -1,   223,   224,   225,   226,   227,   162,    -1,
     164,   165,   166,   167,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   175,    -1,    -1,   244,    -1,    -1,    -1,    -1,    -1,
     219,    -1,    -1,    -1,   223,   224,   225,   226,   227,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   244,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   223,
     224,   225,   226,   227,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     244
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,   140,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     248,    14,    15,    16,    17,    18,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   126,   127,   148,   162,   164,   165,
     166,   167,   175,   177,   178,   220,   221,   222,   223,   224,
     225,   226,   227,   234,   244,   307,   370,   377,   383,   385,
     386,   387,   388,   432,     1,   249,   278,   278,   317,   278,
     249,   121,   122,   124,   125,   128,   176,   180,   181,   182,
     183,   184,   185,   186,   219,   287,   288,   305,   313,   370,
     370,   337,   370,   369,   370,   176,   306,   307,   334,   346,
     370,   390,   391,   391,   412,     1,   250,   123,   305,   404,
     405,   408,   370,   416,   370,   424,   369,   425,   426,   370,
     369,   130,   314,   253,   307,   338,   370,   369,   370,     0,
     370,   370,   179,   234,   234,   234,   234,   307,   234,   234,
       1,   171,   172,   217,   370,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,   101,   102,   103,   104,   105,   106,   228,
     230,   231,   232,   234,   236,   238,   239,   384,   370,   234,
     234,   234,   240,   120,   129,   141,   142,   182,   218,   251,
     256,   257,   261,   279,   281,   282,   283,   289,   301,   305,
     307,   314,   283,   289,   301,   242,   125,   236,   236,   183,
     241,   230,   307,   121,   176,   180,   181,   182,   185,   186,
       1,    14,   228,   241,   229,   241,   229,   123,   130,   250,
     289,   305,   392,   397,   392,   240,   251,   409,   406,   240,
     407,   241,     1,   241,   241,    33,    34,   149,   150,   151,
     152,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   169,   170,   223,   242,   244,   370,   430,   431,
     452,   455,   456,   457,   306,   234,     1,   306,   306,   306,
     306,   378,   235,   307,   235,   236,   236,   370,   225,   227,
     235,   370,   370,   370,   370,   370,   370,   370,   370,   370,
     370,   370,   370,   370,   370,   373,   370,   370,   370,   370,
     370,   370,   370,   370,   370,   370,   371,   372,     1,   370,
     307,   370,   370,   370,   370,     1,   305,     1,   265,   307,
     242,   242,   119,   307,   427,   262,   290,   291,   306,   234,
     255,     1,   305,   308,   309,   370,   370,   288,   307,   297,
     298,   242,   236,   236,    14,   228,   370,   305,   306,   370,
       1,   393,     1,   306,   256,   306,   307,   307,   405,   408,
     241,   410,   241,   370,   370,   229,   242,   229,   242,   160,
     370,   370,   370,   234,   370,   370,   370,   229,   229,   236,
      19,   229,   236,   433,   229,   229,   229,   229,   370,   370,
     433,   236,   370,   453,   454,   433,   153,   160,   454,   454,
     245,   234,   286,   254,   229,   229,   229,   229,   234,   235,
     177,   177,   235,   236,   236,   370,   229,   370,   389,     1,
     237,   237,   235,   241,   241,   240,   302,   303,   306,   240,
     101,   240,   241,   266,   369,   369,     1,   116,   258,   259,
     260,   307,   286,   147,   428,   143,   146,   267,   240,   241,
     286,   292,   235,   287,     3,   243,   306,   310,   311,   243,
     309,   241,   237,   297,   236,   299,     1,   308,   370,   370,
     229,   240,   307,   394,   395,   242,     1,   234,   242,   403,
     297,   297,   307,   307,   370,   370,   229,   370,   307,   149,
     430,   102,   173,   370,   434,   229,   234,   234,   307,   450,
     434,   242,   234,   307,   439,   440,   439,   439,   439,   234,
     370,   243,   241,   234,   370,   229,     1,   235,   287,   242,
     389,   305,   307,   305,   307,   307,   305,   307,   389,   241,
     241,   177,   177,   370,   235,   241,   235,   370,   370,   240,
     241,   304,   307,   307,   243,   243,   240,   101,   240,   241,
     236,   280,   242,   242,   307,   168,   269,   291,   242,   297,
     235,   307,   312,   240,   241,   370,     1,   305,   370,   243,
     243,   241,   237,   305,   396,   240,   241,   401,   242,     1,
     235,   404,   402,     1,   242,   297,   297,   243,   243,   430,
      26,    28,   429,   436,   102,   102,   237,   430,   370,   307,
     451,   105,   246,   449,   237,   240,   454,   439,   440,   441,
     442,   443,   444,   445,   446,   447,   102,   105,   171,   172,
     370,   438,   225,   226,   370,   306,   430,   235,   235,   315,
     235,   235,   379,   235,   380,   382,   235,   381,   235,   177,
     177,   241,   241,   370,   235,   241,   303,   297,   259,   259,
     370,   240,     1,   457,   268,   255,   242,   284,     3,   293,
     234,   297,   311,   237,   237,   237,   237,   370,   297,   395,
     411,   412,   400,   235,   235,   411,   242,   398,   229,   229,
     151,   370,   435,   370,   229,   235,   241,    27,   235,   450,
     242,   102,   177,   243,    26,    27,   229,   246,   448,    17,
     448,   448,   448,   448,    17,    27,    26,   439,   439,   225,
     370,   370,   370,   229,   316,   317,   375,   235,   376,   235,
     235,   374,   235,   237,   237,   177,   177,   370,   237,   243,
     243,   243,   370,   242,   270,   349,   242,   294,   370,   252,
     299,   300,   299,   237,   294,   243,     1,   131,   413,   411,
     243,   399,   411,   370,   370,   430,   229,   370,   307,   449,
     453,   450,   237,   229,   439,   439,   430,   439,   235,   440,
     235,   235,   235,   235,   440,   439,   439,   370,   235,   237,
     237,   370,   243,   131,   318,   370,   234,   370,   234,   370,
     370,   370,   370,   370,   237,   237,   235,   229,   240,   260,
     263,   264,   243,   307,   289,   301,   350,   294,   295,   296,
     306,   307,   389,   299,   240,   307,   414,   415,   341,   243,
     411,   243,   235,   430,   235,   243,   177,   370,   235,   102,
     105,   437,   235,     1,   307,   319,   320,   132,   321,   341,
     370,   370,   235,   235,   370,   370,   370,     1,    14,   228,
     241,   243,   271,     1,   107,   108,   109,   110,   111,   112,
     113,   117,   118,   240,   242,   243,   285,   347,   351,   352,
     354,   355,   356,   357,   359,   362,   370,   241,   243,   229,
     235,   242,   240,   241,     1,   124,   133,   134,   324,   342,
     343,   243,   229,   229,   170,   178,   240,   242,   240,   241,
       1,   307,   322,   323,   341,   324,   235,   235,   235,   235,
     240,    14,   228,   264,   234,   272,   240,   234,   234,   364,
     240,   240,   234,   234,   240,   370,   370,   348,   351,   355,
     355,   356,   240,   296,   294,   240,   416,   415,   240,     1,
     307,   345,     1,   307,   344,   307,   135,   417,   430,   370,
     433,     1,   240,   370,   320,   240,   240,   241,   324,   135,
     325,   273,   306,   229,     1,   306,   369,     1,   363,   351,
     369,   353,   240,   240,   349,   114,   243,   240,   240,   241,
     240,   240,   241,   240,     1,   307,   418,   419,   234,   243,
     346,   240,   243,   323,   325,     1,   307,   326,   327,   235,
     241,   229,   107,   274,   275,   370,   235,   229,   240,   235,
     369,   108,   235,   369,   350,   307,   307,   240,   144,   240,
     241,   438,   243,   346,   240,   144,   145,   240,   241,   306,
     305,   276,   240,   241,   144,   351,   305,   369,   351,   235,
     234,   358,   235,     1,   243,   307,   144,   419,   421,   370,
     243,   307,   307,   144,   145,   327,   330,   229,   234,   275,
     370,   235,   240,   351,   369,   242,   242,   307,   235,   242,
     242,   307,   307,   305,   277,   306,   361,   369,   235,   115,
     116,   365,   366,   420,   242,   328,   329,   242,   242,   235,
     241,   229,   351,   235,   240,   370,   229,   243,   366,   137,
     423,   422,   136,   333,   333,   331,   332,   370,   306,   305,
     360,   229,   368,   424,   138,   336,   423,   334,   137,   335,
     335,   333,   333,   144,   229,   351,   367,   350,     1,   240,
       1,   337,   139,   339,   336,   240,     1,   370,   336,   336,
     335,   335,   370,   305,   350,   240,   240,   240,     1,   369,
     243,   339,   240,     1,   240,   339,   339,   336,   336,   240,
     240,   243,   240,   140,   340,   340,   339,   339,     1,   370,
     243,   243,   243,   243,   240,   240
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int16 yyr1[] =
{
       0,   247,   248,   248,   248,   248,   248,   248,   248,   248,
     248,   248,   248,   248,   248,   248,   248,   248,   248,   248,
     248,   248,   248,   248,   248,   248,   248,   248,   248,   248,
     248,   249,   250,   250,   250,   252,   251,   253,   254,   253,
     255,   255,   255,   256,   257,   257,   258,   258,   258,   259,
     259,   260,   260,   261,   261,   262,   262,   263,   263,   264,
     264,   264,   264,   264,   265,   265,   265,   266,   267,   267,
     268,   268,   268,   269,   269,   270,   271,   270,   272,   272,
     273,   273,   274,   274,   275,   276,   275,   277,   277,   278,
     278,   278,   278,   278,   278,   278,   278,   278,   278,   278,
     280,   279,   281,   282,   284,   283,   285,   285,   286,   286,
     286,   287,   287,   288,   288,   289,   290,   290,   292,   291,
     293,   293,   294,   294,   295,   295,   296,   296,   298,   297,
     299,   299,   300,   299,   299,   301,   301,   302,   302,   304,
     303,   305,   305,   305,   305,   305,   305,   305,   305,   305,
     305,   305,   305,   305,   305,   305,   305,   305,   305,   305,
     305,   305,   306,   306,   307,   307,   307,   307,   307,   307,
     307,   307,   307,   307,   307,   307,   307,   307,   308,   308,
     309,   310,   310,   312,   311,   313,   313,   313,   313,   313,
     315,   314,   316,   316,   316,   317,   317,   317,   317,   318,
     318,   319,   319,   320,   320,   320,   320,   320,   321,   321,
     322,   322,   323,   324,   324,   325,   325,   325,   326,   326,
     328,   327,   329,   327,   331,   330,   332,   330,   330,   333,
     333,   334,   334,   335,   335,   335,   335,   336,   336,   336,
     337,   337,   337,   337,   337,   338,   338,   339,   339,   339,
     340,   340,   340,   341,   341,   341,   342,   342,   343,   343,
     344,   344,   345,   345,   346,   346,   348,   347,   349,   349,
     349,   350,   350,   350,   351,   351,   353,   352,   354,   355,
     355,   356,   356,   357,   357,   357,   357,   357,   357,   357,
     358,   357,   357,   357,   357,   360,   359,   361,   359,   359,
     363,   362,   362,   364,   362,   365,   365,   367,   366,   368,
     366,   369,   369,   370,   370,   370,   370,   370,   370,   370,
     370,   371,   370,   372,   370,   370,   370,   370,   370,   370,
     370,   370,   370,   370,   370,   370,   370,   370,   370,   370,
     370,   370,   370,   370,   370,   370,   370,   370,   370,   370,
     370,   370,   370,   370,   370,   370,   370,   373,   370,   370,
     370,   370,   370,   370,   374,   370,   375,   370,   376,   370,
     370,   370,   370,   378,   377,   377,   377,   379,   377,   380,
     377,   381,   377,   382,   377,   383,   384,   384,   384,   384,
     384,   384,   384,   384,   384,   384,   384,   385,   385,   385,
     385,   386,   386,   386,   386,   386,   386,   386,   386,   386,
     386,   386,   386,   386,   386,   386,   386,   386,   386,   386,
     386,   386,   386,   386,   386,   386,   386,   386,   386,   386,
     386,   386,   386,   386,   386,   386,   386,   386,   386,   386,
     386,   386,   386,   386,   386,   387,   387,   387,   387,   387,
     387,   387,   387,   387,   387,   387,   387,   387,   387,   387,
     388,   388,   389,   389,   389,   390,   391,   391,   391,   392,
     393,   392,   392,   394,   394,   396,   395,   398,   397,   399,
     397,   400,   397,   401,   397,   402,   397,   403,   403,   403,
     404,   404,   404,   404,   406,   405,   407,   405,   409,   408,
     410,   408,   411,   412,   412,   413,   413,   414,   414,   415,
     415,   416,   416,   416,   417,   417,   417,   418,   418,   420,
     419,   422,   421,   421,   423,   423,   423,   424,   424,   425,
     426,   426,   427,   427,   428,   428,   429,   429,   430,   430,
     430,   430,   430,   430,   430,   430,   431,   431,   431,   431,
     431,   431,   431,   431,   431,   431,   431,   431,   431,   431,
     431,   431,   431,   431,   431,   431,   431,   431,   431,   431,
     431,   431,   431,   431,   432,   432,   432,   432,   432,   433,
     433,   435,   434,   436,   434,   434,   437,   437,   438,   438,
     439,   439,   439,   439,   439,   439,   440,   441,   442,   443,
     444,   445,   445,   446,   446,   447,   447,   448,   448,   449,
     449,   450,   450,   451,   451,   452,   453,   453,   454,   454,
     455,   455,   456,   456,   457,   457,   457,   457
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     3,     0,     2,     2,     0,     9,     1,     0,     5,
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
       3,     1,     3,     1,     5,     4,     6,     4,     3,     3,
       1,     3,     1,     3,     2,     0,     3,     3,     1,     3,
       0,    11,     0,    11,     0,     9,     0,     9,     1,     0,
       3,     3,     5,     0,     3,     4,     3,     0,     3,     3,
       1,     2,     3,     2,     3,     1,     2,     0,     3,     3,
       0,     3,     3,     0,     2,     2,     3,     3,     3,     3,
       1,     3,     1,     3,     1,     3,     0,     5,     0,     2,
       2,     0,     2,     3,     1,     1,     0,     5,     3,     2,
       1,     2,     2,     1,     1,     2,     1,     1,     2,     2,
       0,     8,     3,     2,     3,     0,    10,     0,     8,     5,
       0,     6,     5,     0,     8,     1,     2,     0,     5,     0,
       4,     1,     3,     1,     1,     1,     1,     4,     6,     8,
       1,     0,     5,     0,     5,     4,     4,     3,     3,     2,
       2,     2,     2,     2,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     5,     3,     2,     1,     0,     4,     3,
       3,     3,     3,     3,     0,     8,     0,     8,     0,     8,
       1,     1,     1,     0,     6,     3,     4,     0,    10,     0,
      10,     0,     8,     0,     8,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     1,     3,     3,     0,     2,     2,     1,
       0,     4,     3,     1,     3,     0,     4,     0,     7,     0,
       8,     0,     7,     0,     6,     0,     6,     2,     3,     3,
       1,     1,     3,     3,     0,     4,     0,     5,     0,     4,
       0,     5,     5,     0,     2,     3,     2,     1,     3,     1,
       4,     1,     3,     3,     0,     3,     3,     1,     3,     0,
       9,     0,     8,     1,     0,     3,     4,     1,     3,     2,
       0,     3,     0,     2,     4,     4,     1,     1,     2,     7,
       2,     2,     2,     3,     6,     6,     1,     2,     2,     2,
       3,     6,     9,     7,     4,     4,     4,     6,     6,     5,
       5,     3,     3,     3,     3,     8,     6,     7,    13,     5,
       7,     9,     7,     2,    10,    10,     4,     9,     9,     3,
       5,     0,     4,     0,     3,     3,     1,     1,     1,     1,
       1,     4,     4,     4,     4,     4,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     3,     0,     2,     0,
       4,     1,     3,     1,     3,     3,     0,     1,     1,     3,
       2,     5,     2,     5,     0,     1,     2,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

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

# ifndef YY_LOCATION_PRINT
#  if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

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

#   define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

#  else
#   define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#  endif
# endif /* !defined YY_LOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
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
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
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

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
  case 2: /* Uppaal: T_NEW XTA  */
#line 318 "parser.yy"
                    { CALL((yylsp[0]), (yylsp[0]), done()); }
#line 5483 "parser.tab.c"
    break;

  case 3: /* Uppaal: T_NEW_DECLARATION Declarations  */
#line 319 "parser.yy"
                                         { }
#line 5489 "parser.tab.c"
    break;

  case 4: /* Uppaal: T_NEW_LOCAL_DECL ProcLocalDeclList  */
#line 320 "parser.yy"
                                             { }
#line 5495 "parser.tab.c"
    break;

  case 5: /* Uppaal: T_NEW_INST Declarations  */
#line 321 "parser.yy"
                                  { }
#line 5501 "parser.tab.c"
    break;

  case 6: /* Uppaal: T_NEW_SYSTEM XTA  */
#line 322 "parser.yy"
                           { }
#line 5507 "parser.tab.c"
    break;

  case 7: /* Uppaal: T_NEW_PARAMETERS ParameterList  */
#line 323 "parser.yy"
                                         { }
#line 5513 "parser.tab.c"
    break;

  case 8: /* Uppaal: T_NEW_INVARIANT Expression  */
#line 324 "parser.yy"
                                     { }
#line 5519 "parser.tab.c"
    break;

  case 9: /* Uppaal: T_NEW_SELECT SelectList  */
#line 325 "parser.yy"
                                  { }
#line 5525 "parser.tab.c"
    break;

  case 10: /* Uppaal: T_NEW_GUARD Expression  */
#line 326 "parser.yy"
                                 { CALL((yylsp[0]), (yylsp[0]), procGuard()); }
#line 5531 "parser.tab.c"
    break;

  case 11: /* Uppaal: T_NEW_SYNC SyncExpr  */
#line 327 "parser.yy"
                              { }
#line 5537 "parser.tab.c"
    break;

  case 12: /* Uppaal: T_NEW_ASSIGN ExprList  */
#line 328 "parser.yy"
                                { CALL((yylsp[0]), (yylsp[0]), procUpdate()); }
#line 5543 "parser.tab.c"
    break;

  case 13: /* Uppaal: T_PROBABILITY Expression  */
#line 329 "parser.yy"
                                   { CALL((yylsp[0]), (yylsp[0]), procProb()); }
#line 5549 "parser.tab.c"
    break;

  case 14: /* Uppaal: T_OLD OldXTA  */
#line 330 "parser.yy"
                       { CALL((yylsp[0]), (yylsp[0]), done()); }
#line 5555 "parser.tab.c"
    break;

  case 15: /* Uppaal: T_OLD_DECLARATION OldDeclaration  */
#line 331 "parser.yy"
                                           { }
#line 5561 "parser.tab.c"
    break;

  case 16: /* Uppaal: T_OLD_LOCAL_DECL OldVarDeclList  */
#line 332 "parser.yy"
                                          { }
#line 5567 "parser.tab.c"
    break;

  case 17: /* Uppaal: T_OLD_INST Instantiations  */
#line 333 "parser.yy"
                                    { }
#line 5573 "parser.tab.c"
    break;

  case 18: /* Uppaal: T_OLD_PARAMETERS OldProcParamList  */
#line 334 "parser.yy"
                                            { }
#line 5579 "parser.tab.c"
    break;

  case 19: /* Uppaal: T_OLD_INVARIANT OldInvariant  */
#line 335 "parser.yy"
                                       { }
#line 5585 "parser.tab.c"
    break;

  case 20: /* Uppaal: T_OLD_GUARD OldGuardList  */
#line 336 "parser.yy"
                                   { CALL((yylsp[0]), (yylsp[0]), procGuard()); }
#line 5591 "parser.tab.c"
    break;

  case 21: /* Uppaal: T_OLD_ASSIGN ExprList  */
#line 337 "parser.yy"
                                { CALL((yylsp[0]), (yylsp[0]), procUpdate()); }
#line 5597 "parser.tab.c"
    break;

  case 22: /* Uppaal: T_PROPERTY PropertyList  */
#line 338 "parser.yy"
                                  {}
#line 5603 "parser.tab.c"
    break;

  case 23: /* Uppaal: T_EXPRESSION Expression  */
#line 339 "parser.yy"
                                  {}
#line 5609 "parser.tab.c"
    break;

  case 24: /* Uppaal: T_EXPRESSION_LIST ExprList  */
#line 340 "parser.yy"
                                     {}
#line 5615 "parser.tab.c"
    break;

  case 25: /* Uppaal: T_XTA_PROCESS ProcDecl  */
#line 341 "parser.yy"
                                 {}
#line 5621 "parser.tab.c"
    break;

  case 26: /* Uppaal: T_EXPONENTIALRATE ExpRate  */
#line 342 "parser.yy"
                                    {}
#line 5627 "parser.tab.c"
    break;

  case 27: /* Uppaal: T_MESSAGE MessExpr  */
#line 344 "parser.yy"
                             { }
#line 5633 "parser.tab.c"
    break;

  case 28: /* Uppaal: T_UPDATE ExprList  */
#line 345 "parser.yy"
                            { CALL((yylsp[0]), (yylsp[0]), procLscUpdate()); }
#line 5639 "parser.tab.c"
    break;

  case 29: /* Uppaal: T_CONDITION Expression  */
#line 346 "parser.yy"
                                 { CALL((yylsp[0]), (yylsp[0]), procCondition()); }
#line 5645 "parser.tab.c"
    break;

  case 30: /* Uppaal: T_INSTANCELINE InstanceLineExpression  */
#line 347 "parser.yy"
                                                { }
#line 5651 "parser.tab.c"
    break;

  case 35: /* $@1: %empty  */
#line 361 "parser.yy"
                                                                           {
          CALL((yylsp[-4]), (yylsp[-1]), instantiationBegin((yyvsp[-4].string), (yyvsp[-3].number), (yyvsp[-1].string)));
        }
#line 5659 "parser.tab.c"
    break;

  case 36: /* Instantiation: NonTypeId OptionalInstanceParameterList T_ASSIGNMENT NonTypeId '(' $@1 ArgList ')' ';'  */
#line 363 "parser.yy"
                          {
          CALL((yylsp[-8]), (yylsp[0]), instantiationEnd((yyvsp[-8].string), (yyvsp[-7].number), (yyvsp[-5].string), (yyvsp[-2].number)));
        }
#line 5667 "parser.tab.c"
    break;

  case 37: /* InstanceLineExpression: NonTypeId  */
#line 368 "parser.yy"
                  {
          CALL((yylsp[0]), (yylsp[0]), instanceName((yyvsp[0].string), false));
        }
#line 5675 "parser.tab.c"
    break;

  case 38: /* $@2: %empty  */
#line 371 "parser.yy"
                        {
          CALL((yylsp[-1]), (yylsp[-1]), instanceNameBegin((yyvsp[-1].string)));
        }
#line 5683 "parser.tab.c"
    break;

  case 39: /* InstanceLineExpression: NonTypeId '(' $@2 ArgList ')'  */
#line 373 "parser.yy"
                      {
          CALL((yylsp[-4]), (yylsp[0]), instanceNameEnd((yyvsp[-4].string), (yyvsp[-1].number)));
        }
#line 5691 "parser.tab.c"
    break;

  case 40: /* OptionalInstanceParameterList: %empty  */
#line 378 "parser.yy"
                    { (yyval.number) = 0; }
#line 5697 "parser.tab.c"
    break;

  case 41: /* OptionalInstanceParameterList: '(' ')'  */
#line 379 "parser.yy"
                  {
        	(yyval.number) = 0;
        }
#line 5705 "parser.tab.c"
    break;

  case 42: /* OptionalInstanceParameterList: '(' ParameterList ')'  */
#line 382 "parser.yy"
                                {
        	(yyval.number) = (yyvsp[-1].number);
        }
#line 5713 "parser.tab.c"
    break;

  case 46: /* ChannelList: ChanElement  */
#line 394 "parser.yy"
                    { CALL((yylsp[0]), (yylsp[0]), beginChanPriority()); }
#line 5719 "parser.tab.c"
    break;

  case 47: /* ChannelList: ChannelList ',' ChanElement  */
#line 395 "parser.yy"
                                       { CALL((yylsp[-2]), (yylsp[0]), addChanPriority(',')); }
#line 5725 "parser.tab.c"
    break;

  case 48: /* ChannelList: ChannelList T_LT ChanElement  */
#line 396 "parser.yy"
                                       { CALL((yylsp[-2]), (yylsp[0]), addChanPriority('<')); }
#line 5731 "parser.tab.c"
    break;

  case 50: /* ChanElement: T_DEFAULT  */
#line 402 "parser.yy"
                    { CALL((yylsp[0]), (yylsp[0]), defaultChanPriority()); }
#line 5737 "parser.tab.c"
    break;

  case 51: /* ChanExpression: NonTypeId  */
#line 406 "parser.yy"
                  { CALL((yylsp[0]), (yylsp[0]), exprId((yyvsp[0].string))); }
#line 5743 "parser.tab.c"
    break;

  case 52: /* ChanExpression: ChanExpression '[' Expression ']'  */
#line 407 "parser.yy"
                                            { CALL((yylsp[-3]), (yylsp[0]), exprArray()); }
#line 5749 "parser.tab.c"
    break;

  case 53: /* SysDecl: T_SYSTEM ProcessList ';'  */
#line 411 "parser.yy"
                                 { CALL((yylsp[-2]), (yylsp[-2]), processListEnd()); }
#line 5755 "parser.tab.c"
    break;

  case 54: /* SysDecl: T_SYSTEM error ';'  */
#line 412 "parser.yy"
                             { CALL((yylsp[-2]), (yylsp[-2]), processListEnd()); }
#line 5761 "parser.tab.c"
    break;

  case 56: /* IODecl: IODecl T_IO NonTypeId OptionalInstanceParameterList '{' SyncExprList '}'  */
#line 418 "parser.yy"
        { CALL((yylsp[-6]), (yylsp[0]), declIO((yyvsp[-4].string),(yyvsp[-3].number),(yyvsp[-1].number))); }
#line 5767 "parser.tab.c"
    break;

  case 57: /* SyncExprList: IOSyncExpr  */
#line 422 "parser.yy"
                   { (yyval.number) = 1; }
#line 5773 "parser.tab.c"
    break;

  case 58: /* SyncExprList: SyncExprList ',' IOSyncExpr  */
#line 423 "parser.yy"
                                      { (yyval.number) = (yyvsp[-2].number) + 1; }
#line 5779 "parser.tab.c"
    break;

  case 59: /* IOSyncExpr: ChanExpression  */
#line 430 "parser.yy"
                       {
	    CALL((yylsp[0]), (yylsp[0]), exprSync(SYNC_CSP));
        }
#line 5787 "parser.tab.c"
    break;

  case 60: /* IOSyncExpr: ChanExpression T_EXCLAM  */
#line 433 "parser.yy"
                                  {
          CALL((yylsp[-1]), (yylsp[0]), exprSync(SYNC_BANG));
        }
#line 5795 "parser.tab.c"
    break;

  case 61: /* IOSyncExpr: ChanExpression error T_EXCLAM  */
#line 436 "parser.yy"
                                        {
          CALL((yylsp[-2]), (yylsp[-1]), exprSync(SYNC_BANG));
        }
#line 5803 "parser.tab.c"
    break;

  case 62: /* IOSyncExpr: ChanExpression '?'  */
#line 439 "parser.yy"
                             {
          CALL((yylsp[-1]), (yylsp[0]), exprSync(SYNC_QUE));
        }
#line 5811 "parser.tab.c"
    break;

  case 63: /* IOSyncExpr: ChanExpression error '?'  */
#line 442 "parser.yy"
                                   {
          CALL((yylsp[-2]), (yylsp[-1]), exprSync(SYNC_QUE));
        }
#line 5819 "parser.tab.c"
    break;

  case 64: /* ProcessList: NonTypeId  */
#line 448 "parser.yy"
                  { CALL((yylsp[0]), (yylsp[0]), process((yyvsp[0].string))); }
#line 5825 "parser.tab.c"
    break;

  case 65: /* ProcessList: ProcessList ',' NonTypeId  */
#line 449 "parser.yy"
                                    { CALL((yylsp[0]), (yylsp[0]), process((yyvsp[0].string))); }
#line 5831 "parser.tab.c"
    break;

  case 66: /* ProcessList: ProcessList ProcLessThan NonTypeId  */
#line 450 "parser.yy"
                                             { CALL((yylsp[0]), (yylsp[0]), process((yyvsp[0].string))); }
#line 5837 "parser.tab.c"
    break;

  case 67: /* ProcLessThan: T_LT  */
#line 454 "parser.yy"
             { CALL((yylsp[0]), (yylsp[0]), incProcPriority()); }
#line 5843 "parser.tab.c"
    break;

  case 71: /* ProgressMeasureList: ProgressMeasureList Expression ':' Expression ';'  */
#line 462 "parser.yy"
                                                            {
            CALL((yylsp[-3]), (yylsp[-1]), declProgress(true));
        }
#line 5851 "parser.tab.c"
    break;

  case 72: /* ProgressMeasureList: ProgressMeasureList Expression ';'  */
#line 465 "parser.yy"
                                             {
            CALL((yylsp[-1]), (yylsp[-1]), declProgress(false));
        }
#line 5859 "parser.tab.c"
    break;

  case 76: /* $@3: %empty  */
#line 476 "parser.yy"
                                          { CALL((yylsp[0]), (yylsp[0]), ganttDeclStart((yyvsp[0].string))); }
#line 5865 "parser.tab.c"
    break;

  case 77: /* GanttDef: GanttDef NonTypeId $@3 GanttArgs ':' GanttExprList ';'  */
#line 477 "parser.yy"
                                          { CALL((yylsp[-5]), (yylsp[-1]), ganttDeclEnd());
	}
#line 5872 "parser.tab.c"
    break;

  case 80: /* GanttDeclSelect: Id ':' Type  */
#line 487 "parser.yy"
                    {
            CALL((yylsp[-2]), (yylsp[0]), ganttDeclSelect((yyvsp[-2].string)));
        }
#line 5880 "parser.tab.c"
    break;

  case 81: /* GanttDeclSelect: GanttDeclSelect ',' Id ':' Type  */
#line 490 "parser.yy"
                                          {
            CALL((yylsp[-2]), (yylsp[0]), ganttDeclSelect((yyvsp[-2].string)));
        }
#line 5888 "parser.tab.c"
    break;

  case 84: /* GanttExpr: Expression T_ARROW Expression  */
#line 501 "parser.yy"
                                      {
	    CALL((yylsp[-2]), (yylsp[0]), ganttEntryStart());
	    CALL((yylsp[-2]), (yylsp[0]), ganttEntryEnd());
        }
#line 5897 "parser.tab.c"
    break;

  case 85: /* $@4: %empty  */
#line 505 "parser.yy"
                                                                 { CALL((yylsp[0]), (yylsp[0]), ganttEntryStart()); }
#line 5903 "parser.tab.c"
    break;

  case 86: /* GanttExpr: T_FOR $@4 '(' GanttEntrySelect ')' Expression T_ARROW Expression  */
#line 506 "parser.yy"
                                                                 { CALL((yylsp[-7]), (yylsp[-1]), ganttEntryEnd()); }
#line 5909 "parser.tab.c"
    break;

  case 87: /* GanttEntrySelect: Id ':' Type  */
#line 510 "parser.yy"
                    {
            CALL((yylsp[-2]), (yylsp[0]), ganttEntrySelect((yyvsp[-2].string)));
        }
#line 5917 "parser.tab.c"
    break;

  case 88: /* GanttEntrySelect: GanttEntrySelect ',' Id ':' Type  */
#line 513 "parser.yy"
                                           {
            CALL((yylsp[-2]), (yylsp[0]), ganttEntrySelect((yyvsp[-2].string)));
        }
#line 5925 "parser.tab.c"
    break;

  case 100: /* $@5: %empty  */
#line 533 "parser.yy"
                                          {CALL((yylsp[-2]),(yylsp[0]),declDynamicTemplate((yyvsp[-1].string)));}
#line 5931 "parser.tab.c"
    break;

  case 102: /* BeforeUpdateDecl: T_BEFORE '{' ExprList '}'  */
#line 535 "parser.yy"
                                            { CALL((yylsp[-1]), (yylsp[-1]), beforeUpdate()); }
#line 5937 "parser.tab.c"
    break;

  case 103: /* AfterUpdateDecl: T_AFTER '{' ExprList '}'  */
#line 537 "parser.yy"
                                          { CALL((yylsp[-1]), (yylsp[-1]), afterUpdate()); }
#line 5943 "parser.tab.c"
    break;

  case 104: /* $@6: %empty  */
#line 548 "parser.yy"
                                          {
          CALL((yylsp[-3]), (yylsp[-2]), declFuncBegin((yyvsp[-2].string)));
        }
#line 5951 "parser.tab.c"
    break;

  case 105: /* FunctionDecl: Type Id OptionalParameterList '{' $@6 BlockLocalDeclList StatementList EndBlock  */
#line 550 "parser.yy"
                                                    {
          CALL((yylsp[0]), (yylsp[0]), declFuncEnd());
        }
#line 5959 "parser.tab.c"
    break;

  case 111: /* ParameterList: Parameter  */
#line 563 "parser.yy"
                    { (yyval.number) = 1; }
#line 5965 "parser.tab.c"
    break;

  case 112: /* ParameterList: ParameterList ',' Parameter  */
#line 564 "parser.yy"
                                      { (yyval.number) = (yyvsp[-2].number)+1; }
#line 5971 "parser.tab.c"
    break;

  case 113: /* Parameter: Type '&' NonTypeId ArrayDecl  */
#line 568 "parser.yy"
                                       {
          CALL((yylsp[-3]), (yylsp[0]), declParameter((yyvsp[-1].string), true));
        }
#line 5979 "parser.tab.c"
    break;

  case 114: /* Parameter: Type NonTypeId ArrayDecl  */
#line 571 "parser.yy"
                                   {
          CALL((yylsp[-2]), (yylsp[0]), declParameter((yyvsp[-1].string), false));
        }
#line 5987 "parser.tab.c"
    break;

  case 115: /* VariableDecl: Type DeclIdList ';'  */
#line 577 "parser.yy"
                            {
            CALL((yylsp[-2]), (yylsp[0]), typePop());
        }
#line 5995 "parser.tab.c"
    break;

  case 118: /* $@7: %empty  */
#line 588 "parser.yy"
           {
            CALL((yylsp[0]), (yylsp[0]), typeDuplicate());
        }
#line 6003 "parser.tab.c"
    break;

  case 119: /* DeclId: Id $@7 ArrayDecl VarInit  */
#line 590 "parser.yy"
                            {
            CALL((yylsp[-3]), (yylsp[0]), declVar((yyvsp[-3].string), (yyvsp[0].flag)));
        }
#line 6011 "parser.tab.c"
    break;

  case 120: /* VarInit: %empty  */
#line 596 "parser.yy"
                    { (yyval.flag) = false; }
#line 6017 "parser.tab.c"
    break;

  case 121: /* VarInit: T_ASSIGNMENT Initializer  */
#line 597 "parser.yy"
                                   { (yyval.flag) = true; }
#line 6023 "parser.tab.c"
    break;

  case 123: /* Initializer: '{' FieldInitList '}'  */
#line 602 "parser.yy"
                                {
          CALL((yylsp[-2]), (yylsp[0]), declInitialiserList((yyvsp[-1].number)));
        }
#line 6031 "parser.tab.c"
    break;

  case 124: /* FieldInitList: FieldInit  */
#line 608 "parser.yy"
                  { (yyval.number) = 1; }
#line 6037 "parser.tab.c"
    break;

  case 125: /* FieldInitList: FieldInitList ',' FieldInit  */
#line 609 "parser.yy"
                                      { (yyval.number) = (yyvsp[-2].number)+1; }
#line 6043 "parser.tab.c"
    break;

  case 126: /* FieldInit: Id ':' Initializer  */
#line 613 "parser.yy"
                           {
          CALL((yylsp[-2]), (yylsp[0]), declFieldInit((yyvsp[-2].string)));
        }
#line 6051 "parser.tab.c"
    break;

  case 127: /* FieldInit: Initializer  */
#line 616 "parser.yy"
                      {
          CALL((yylsp[0]), (yylsp[0]), declFieldInit(""));
        }
#line 6059 "parser.tab.c"
    break;

  case 128: /* $@8: %empty  */
#line 622 "parser.yy"
        { types = 0; }
#line 6065 "parser.tab.c"
    break;

  case 131: /* ArrayDecl2: '[' Expression ']' ArrayDecl2  */
#line 626 "parser.yy"
                                               { CALL((yylsp[-3]), (yylsp[-1]), typeArrayOfSize(types)); }
#line 6071 "parser.tab.c"
    break;

  case 132: /* $@9: %empty  */
#line 627 "parser.yy"
                       { types++; }
#line 6077 "parser.tab.c"
    break;

  case 133: /* ArrayDecl2: '[' Type ']' $@9 ArrayDecl2  */
#line 627 "parser.yy"
                                               { CALL((yylsp[-4]), (yylsp[-2]), typeArrayOfType(types--)); }
#line 6083 "parser.tab.c"
    break;

  case 135: /* TypeDecl: T_TYPEDEF Type TypeIdList ';'  */
#line 632 "parser.yy"
                                      {
          CALL((yylsp[-3]), (yylsp[0]), typePop());
        }
#line 6091 "parser.tab.c"
    break;

  case 139: /* $@10: %empty  */
#line 644 "parser.yy"
           {
            CALL((yylsp[0]), (yylsp[0]), typeDuplicate());
        }
#line 6099 "parser.tab.c"
    break;

  case 140: /* TypeId: Id $@10 ArrayDecl  */
#line 646 "parser.yy"
                    {
            CALL((yylsp[-2]), (yylsp[0]), declTypeDef((yyvsp[-2].string)));
        }
#line 6107 "parser.tab.c"
    break;

  case 141: /* Type: T_TYPENAME  */
#line 652 "parser.yy"
                   {
            CALL((yylsp[0]), (yylsp[0]), typeName(ParserBuilder::PREFIX_NONE, (yyvsp[0].string)));
        }
#line 6115 "parser.tab.c"
    break;

  case 142: /* Type: TypePrefix T_TYPENAME  */
#line 655 "parser.yy"
                                {
            CALL((yylsp[-1]), (yylsp[0]), typeName((yyvsp[-1].prefix), (yyvsp[0].string)));
        }
#line 6123 "parser.tab.c"
    break;

  case 143: /* Type: T_STRUCT '{' FieldDeclList '}'  */
#line 658 "parser.yy"
                                         {
            CALL((yylsp[-3]), (yylsp[0]), typeStruct(ParserBuilder::PREFIX_NONE, (yyvsp[-1].number)));
        }
#line 6131 "parser.tab.c"
    break;

  case 144: /* Type: TypePrefix T_STRUCT '{' FieldDeclList '}'  */
#line 661 "parser.yy"
                                                    {
            CALL((yylsp[-4]), (yylsp[0]), typeStruct((yyvsp[-4].prefix), (yyvsp[-1].number)));
        }
#line 6139 "parser.tab.c"
    break;

  case 145: /* Type: T_STRUCT '{' error '}'  */
#line 664 "parser.yy"
                                 {
          CALL((yylsp[-3]), (yylsp[0]), typeStruct(ParserBuilder::PREFIX_NONE, 0));
        }
#line 6147 "parser.tab.c"
    break;

  case 146: /* Type: TypePrefix T_STRUCT '{' error '}'  */
#line 667 "parser.yy"
                                            {
          CALL((yylsp[-4]), (yylsp[0]), typeStruct(ParserBuilder::PREFIX_NONE, 0));
        }
#line 6155 "parser.tab.c"
    break;

  case 147: /* Type: T_BOOL  */
#line 670 "parser.yy"
                 {
          CALL((yylsp[0]), (yylsp[0]), typeBool(ParserBuilder::PREFIX_NONE));
        }
#line 6163 "parser.tab.c"
    break;

  case 148: /* Type: TypePrefix T_BOOL  */
#line 673 "parser.yy"
                            {
          CALL((yylsp[-1]), (yylsp[0]), typeBool((yyvsp[-1].prefix)));
        }
#line 6171 "parser.tab.c"
    break;

  case 149: /* Type: T_DOUBLE  */
#line 676 "parser.yy"
                   {
	    CALL((yylsp[0]), (yylsp[0]), typeDouble(ParserBuilder::PREFIX_NONE));
        }
#line 6179 "parser.tab.c"
    break;

  case 150: /* Type: TypePrefix T_DOUBLE  */
#line 679 "parser.yy"
                              {
	    CALL((yylsp[-1]), (yylsp[0]), typeDouble((yyvsp[-1].prefix)));
	}
#line 6187 "parser.tab.c"
    break;

  case 151: /* Type: T_INT  */
#line 682 "parser.yy"
                {
          CALL((yylsp[0]), (yylsp[0]), typeInt(ParserBuilder::PREFIX_NONE));
        }
#line 6195 "parser.tab.c"
    break;

  case 152: /* Type: TypePrefix T_INT  */
#line 685 "parser.yy"
                           {
          CALL((yylsp[-1]), (yylsp[0]), typeInt((yyvsp[-1].prefix)));
        }
#line 6203 "parser.tab.c"
    break;

  case 153: /* Type: T_INT '[' Expression ',' Expression ']'  */
#line 689 "parser.yy"
        {
          CALL((yylsp[-5]), (yylsp[0]), typeBoundedInt(ParserBuilder::PREFIX_NONE));
        }
#line 6211 "parser.tab.c"
    break;

  case 154: /* Type: TypePrefix T_INT '[' Expression ',' Expression ']'  */
#line 692 "parser.yy"
                                                              {
          CALL((yylsp[-6]), (yylsp[0]), typeBoundedInt((yyvsp[-6].prefix)));
        }
#line 6219 "parser.tab.c"
    break;

  case 155: /* Type: T_CHAN  */
#line 695 "parser.yy"
                 {
          CALL((yylsp[0]), (yylsp[0]), typeChannel(ParserBuilder::PREFIX_NONE));
        }
#line 6227 "parser.tab.c"
    break;

  case 156: /* Type: TypePrefix T_CHAN  */
#line 698 "parser.yy"
                            {
          CALL((yylsp[-1]), (yylsp[0]), typeChannel((yyvsp[-1].prefix)));
        }
#line 6235 "parser.tab.c"
    break;

  case 157: /* Type: T_CLOCK  */
#line 701 "parser.yy"
                  {
	    CALL((yylsp[0]), (yylsp[0]), typeClock(ParserBuilder::PREFIX_NONE));
        }
#line 6243 "parser.tab.c"
    break;

  case 158: /* Type: T_HYBRID T_CLOCK  */
#line 704 "parser.yy"
                           {
	    CALL((yylsp[-1]), (yylsp[-1]), typeClock(ParserBuilder::PREFIX_HYBRID));
	}
#line 6251 "parser.tab.c"
    break;

  case 159: /* Type: T_VOID  */
#line 707 "parser.yy"
                 {
          CALL((yylsp[0]), (yylsp[0]), typeVoid());
        }
#line 6259 "parser.tab.c"
    break;

  case 160: /* Type: T_SCALAR '[' Expression ']'  */
#line 711 "parser.yy"
        {
          CALL((yylsp[-3]), (yylsp[0]), typeScalar(ParserBuilder::PREFIX_NONE));
        }
#line 6267 "parser.tab.c"
    break;

  case 161: /* Type: TypePrefix T_SCALAR '[' Expression ']'  */
#line 714 "parser.yy"
                                                  {
          CALL((yylsp[-4]), (yylsp[0]), typeScalar((yyvsp[-4].prefix)));
        }
#line 6275 "parser.tab.c"
    break;

  case 162: /* Id: NonTypeId  */
#line 720 "parser.yy"
                  { strncpy((yyval.string), (yyvsp[0].string), MAXLEN); }
#line 6281 "parser.tab.c"
    break;

  case 163: /* Id: T_TYPENAME  */
#line 721 "parser.yy"
                     { strncpy((yyval.string), (yyvsp[0].string), MAXLEN); }
#line 6287 "parser.tab.c"
    break;

  case 164: /* NonTypeId: T_ID  */
#line 725 "parser.yy"
              { strncpy((yyval.string), (yyvsp[0].string) , MAXLEN); }
#line 6293 "parser.tab.c"
    break;

  case 165: /* NonTypeId: 'A'  */
#line 726 "parser.yy"
              { strncpy((yyval.string), "A", MAXLEN); }
#line 6299 "parser.tab.c"
    break;

  case 166: /* NonTypeId: 'U'  */
#line 727 "parser.yy"
              { strncpy((yyval.string), "U", MAXLEN); }
#line 6305 "parser.tab.c"
    break;

  case 167: /* NonTypeId: 'W'  */
#line 728 "parser.yy"
              { strncpy((yyval.string), "W", MAXLEN); }
#line 6311 "parser.tab.c"
    break;

  case 168: /* NonTypeId: 'R'  */
#line 729 "parser.yy"
              { strncpy((yyval.string), "R", MAXLEN); }
#line 6317 "parser.tab.c"
    break;

  case 169: /* NonTypeId: 'E'  */
#line 730 "parser.yy"
              { strncpy((yyval.string), "E", MAXLEN); }
#line 6323 "parser.tab.c"
    break;

  case 170: /* NonTypeId: 'M'  */
#line 731 "parser.yy"
              { strncpy((yyval.string), "M", MAXLEN); }
#line 6329 "parser.tab.c"
    break;

  case 171: /* NonTypeId: T_SUP  */
#line 732 "parser.yy"
                { strncpy((yyval.string), "sup", MAXLEN); }
#line 6335 "parser.tab.c"
    break;

  case 172: /* NonTypeId: T_INF  */
#line 733 "parser.yy"
                { strncpy((yyval.string), "inf", MAXLEN); }
#line 6341 "parser.tab.c"
    break;

  case 173: /* NonTypeId: T_SIMULATION  */
#line 734 "parser.yy"
                       { strncpy((yyval.string), "simulation", MAXLEN); }
#line 6347 "parser.tab.c"
    break;

  case 174: /* NonTypeId: T_REFINEMENT  */
#line 735 "parser.yy"
                       { strncpy((yyval.string), "refinement", MAXLEN); }
#line 6353 "parser.tab.c"
    break;

  case 175: /* NonTypeId: T_CONSISTENCY  */
#line 736 "parser.yy"
                        { strncpy((yyval.string), "consistency", MAXLEN); }
#line 6359 "parser.tab.c"
    break;

  case 176: /* NonTypeId: T_SPECIFICATION  */
#line 737 "parser.yy"
                          { strncpy((yyval.string), "specification", MAXLEN); }
#line 6365 "parser.tab.c"
    break;

  case 177: /* NonTypeId: T_IMPLEMENTATION  */
#line 738 "parser.yy"
                           { strncpy((yyval.string), "implementation", MAXLEN); }
#line 6371 "parser.tab.c"
    break;

  case 178: /* FieldDeclList: FieldDecl  */
#line 742 "parser.yy"
                  { (yyval.number)=(yyvsp[0].number); }
#line 6377 "parser.tab.c"
    break;

  case 179: /* FieldDeclList: FieldDeclList FieldDecl  */
#line 743 "parser.yy"
                                  { (yyval.number)=(yyvsp[-1].number)+(yyvsp[0].number); }
#line 6383 "parser.tab.c"
    break;

  case 180: /* FieldDecl: Type FieldDeclIdList ';'  */
#line 747 "parser.yy"
                                 {
          (yyval.number) = (yyvsp[-1].number);
          CALL((yylsp[-2]), (yylsp[0]), typePop());
        }
#line 6392 "parser.tab.c"
    break;

  case 181: /* FieldDeclIdList: FieldDeclId  */
#line 754 "parser.yy"
                    { (yyval.number)=1; }
#line 6398 "parser.tab.c"
    break;

  case 182: /* FieldDeclIdList: FieldDeclIdList ',' FieldDeclId  */
#line 755 "parser.yy"
                                          { (yyval.number)=(yyvsp[-2].number)+1; }
#line 6404 "parser.tab.c"
    break;

  case 183: /* $@11: %empty  */
#line 759 "parser.yy"
           {
            CALL((yylsp[0]), (yylsp[0]), typeDuplicate());
        }
#line 6412 "parser.tab.c"
    break;

  case 184: /* FieldDeclId: Id $@11 ArrayDecl  */
#line 761 "parser.yy"
                    {
            CALL((yylsp[-2]), (yylsp[0]), structField((yyvsp[-2].string)));
        }
#line 6420 "parser.tab.c"
    break;

  case 185: /* TypePrefix: T_URGENT  */
#line 767 "parser.yy"
                      { (yyval.prefix) = ParserBuilder::PREFIX_URGENT; }
#line 6426 "parser.tab.c"
    break;

  case 186: /* TypePrefix: T_BROADCAST  */
#line 768 "parser.yy"
                      { (yyval.prefix) = ParserBuilder::PREFIX_BROADCAST; }
#line 6432 "parser.tab.c"
    break;

  case 187: /* TypePrefix: T_URGENT T_BROADCAST  */
#line 769 "parser.yy"
                               { (yyval.prefix) = ParserBuilder::PREFIX_URGENT_BROADCAST; }
#line 6438 "parser.tab.c"
    break;

  case 188: /* TypePrefix: T_CONST  */
#line 770 "parser.yy"
                   { (yyval.prefix) = ParserBuilder::PREFIX_CONST; }
#line 6444 "parser.tab.c"
    break;

  case 189: /* TypePrefix: T_META  */
#line 771 "parser.yy"
                 { (yyval.prefix) = ParserBuilder::PREFIX_SYSTEM_META; }
#line 6450 "parser.tab.c"
    break;

  case 190: /* $@12: %empty  */
#line 779 "parser.yy"
                                               {
          CALL((yylsp[-3]), (yylsp[0]), procBegin((yyvsp[-2].string)));
        }
#line 6458 "parser.tab.c"
    break;

  case 191: /* ProcDecl: T_PROCESS Id OptionalParameterList '{' $@12 ProcBody '}'  */
#line 782 "parser.yy"
                     {
          CALL((yylsp[-1]), (yylsp[0]), procEnd());
        }
#line 6466 "parser.tab.c"
    break;

  case 203: /* StateDecl: NonTypeId  */
#line 811 "parser.yy"
                    { CALL((yylsp[0]), (yylsp[0]), procState((yyvsp[0].string), false, false)); }
#line 6472 "parser.tab.c"
    break;

  case 204: /* StateDecl: NonTypeId '{' ';' ExpRate '}'  */
#line 812 "parser.yy"
                                        {
	    CALL((yylsp[-4]), (yylsp[0]), procState((yyvsp[-4].string), false, true));
	}
#line 6480 "parser.tab.c"
    break;

  case 205: /* StateDecl: NonTypeId '{' Expression '}'  */
#line 815 "parser.yy"
                                       {
	    CALL((yylsp[-3]), (yylsp[0]), procState((yyvsp[-3].string), true, false));
        }
#line 6488 "parser.tab.c"
    break;

  case 206: /* StateDecl: NonTypeId '{' Expression ';' ExpRate '}'  */
#line 818 "parser.yy"
                                                   {
	    CALL((yylsp[-5]), (yylsp[0]), procState((yyvsp[-5].string), true, true));
	}
#line 6496 "parser.tab.c"
    break;

  case 207: /* StateDecl: NonTypeId '{' error '}'  */
#line 821 "parser.yy"
                                  {
	    CALL((yylsp[-3]), (yylsp[0]), procState((yyvsp[-3].string), false, false));
	}
#line 6504 "parser.tab.c"
    break;

  case 212: /* BranchpointDecl: NonTypeId  */
#line 837 "parser.yy"
                  {
	    CALL((yylsp[0]), (yylsp[0]), procBranchpoint((yyvsp[0].string)));
        }
#line 6512 "parser.tab.c"
    break;

  case 213: /* Init: T_INIT NonTypeId ';'  */
#line 842 "parser.yy"
                             {
          CALL((yylsp[-2]), (yylsp[0]), procStateInit((yyvsp[-1].string)));
        }
#line 6520 "parser.tab.c"
    break;

  case 220: /* $@13: %empty  */
#line 860 "parser.yy"
                                        {
            CALL((yylsp[-3]), (yylsp[-1]), procEdgeBegin((yyvsp[-3].string), (yyvsp[-1].string), true));
        }
#line 6528 "parser.tab.c"
    break;

  case 221: /* Transition: NonTypeId T_ARROW NonTypeId '{' $@13 Select Guard Sync Assign Probability '}'  */
#line 862 "parser.yy"
                                                   {
          strcpy(rootTransId, (yyvsp[-10].string));
          CALL((yylsp[-10]), (yylsp[-2]), procEdgeEnd((yyvsp[-10].string), (yyvsp[-8].string)));
        }
#line 6537 "parser.tab.c"
    break;

  case 222: /* $@14: %empty  */
#line 866 "parser.yy"
                                                    {
            CALL((yylsp[-3]), (yylsp[-1]), procEdgeBegin((yyvsp[-3].string), (yyvsp[-1].string), false));
        }
#line 6545 "parser.tab.c"
    break;

  case 223: /* Transition: NonTypeId T_UNCONTROL_ARROW NonTypeId '{' $@14 Select Guard Sync Assign Probability '}'  */
#line 868 "parser.yy"
                                                   {
          strcpy(rootTransId, (yyvsp[-10].string));
          CALL((yylsp[-10]), (yylsp[-2]), procEdgeEnd((yyvsp[-10].string), (yyvsp[-8].string)));
        }
#line 6554 "parser.tab.c"
    break;

  case 224: /* $@15: %empty  */
#line 875 "parser.yy"
                              {
            CALL((yylsp[-2]), (yylsp[-1]), procEdgeBegin(rootTransId, (yyvsp[-1].string), true));
        }
#line 6562 "parser.tab.c"
    break;

  case 225: /* TransitionOpt: T_ARROW NonTypeId '{' $@15 Select Guard Sync Assign '}'  */
#line 877 "parser.yy"
                                       {
            CALL((yylsp[-8]), (yylsp[-2]), procEdgeEnd(rootTransId, (yyvsp[-7].string)));
        }
#line 6570 "parser.tab.c"
    break;

  case 226: /* $@16: %empty  */
#line 880 "parser.yy"
                                          {
            CALL((yylsp[-2]), (yylsp[-1]), procEdgeBegin(rootTransId, (yyvsp[-1].string), false));
        }
#line 6578 "parser.tab.c"
    break;

  case 227: /* TransitionOpt: T_UNCONTROL_ARROW NonTypeId '{' $@16 Select Guard Sync Assign '}'  */
#line 882 "parser.yy"
                                       {
            CALL((yylsp[-8]), (yylsp[-2]), procEdgeEnd(rootTransId, (yyvsp[-7].string)));
        }
#line 6586 "parser.tab.c"
    break;

  case 231: /* SelectList: Id ':' Type  */
#line 894 "parser.yy"
                    {
            CALL((yylsp[-2]), (yylsp[0]), procSelect((yyvsp[-2].string)));
        }
#line 6594 "parser.tab.c"
    break;

  case 232: /* SelectList: SelectList ',' Id ':' Type  */
#line 897 "parser.yy"
                                     {
            CALL((yylsp[-2]), (yylsp[0]), procSelect((yyvsp[-2].string)));
        }
#line 6602 "parser.tab.c"
    break;

  case 234: /* Guard: T_GUARD Expression ';'  */
#line 904 "parser.yy"
                                 {
          CALL((yylsp[-1]), (yylsp[-1]), procGuard());
        }
#line 6610 "parser.tab.c"
    break;

  case 235: /* Guard: T_GUARD Expression error ';'  */
#line 907 "parser.yy"
                                       {
          CALL((yylsp[-2]), (yylsp[-1]), procGuard());
        }
#line 6618 "parser.tab.c"
    break;

  case 240: /* SyncExpr: Expression  */
#line 920 "parser.yy"
                   {
	    CALL((yylsp[0]), (yylsp[0]), procSync(SYNC_CSP));
        }
#line 6626 "parser.tab.c"
    break;

  case 241: /* SyncExpr: Expression T_EXCLAM  */
#line 923 "parser.yy"
                              {
          CALL((yylsp[-1]), (yylsp[0]), procSync(SYNC_BANG));
        }
#line 6634 "parser.tab.c"
    break;

  case 242: /* SyncExpr: Expression error T_EXCLAM  */
#line 926 "parser.yy"
                                    {
          CALL((yylsp[-2]), (yylsp[-1]), procSync(SYNC_BANG));
        }
#line 6642 "parser.tab.c"
    break;

  case 243: /* SyncExpr: Expression '?'  */
#line 929 "parser.yy"
                         {
          CALL((yylsp[-1]), (yylsp[0]), procSync(SYNC_QUE));
        }
#line 6650 "parser.tab.c"
    break;

  case 244: /* SyncExpr: Expression error '?'  */
#line 932 "parser.yy"
                               {
          CALL((yylsp[-2]), (yylsp[-1]), procSync(SYNC_QUE));
        }
#line 6658 "parser.tab.c"
    break;

  case 245: /* MessExpr: Expression  */
#line 938 "parser.yy"
                   {
          CALL((yylsp[0]), (yylsp[0]), procMessage(SYNC_QUE));
        }
#line 6666 "parser.tab.c"
    break;

  case 246: /* MessExpr: Expression error  */
#line 941 "parser.yy"
                           {
          CALL((yylsp[-1]), (yylsp[-1]), procMessage(SYNC_QUE));
        }
#line 6674 "parser.tab.c"
    break;

  case 248: /* Assign: T_ASSIGN ExprList ';'  */
#line 948 "parser.yy"
                                {
          CALL((yylsp[-1]), (yylsp[-1]), procUpdate());
        }
#line 6682 "parser.tab.c"
    break;

  case 251: /* Probability: T_PROBABILITY Expression ';'  */
#line 956 "parser.yy"
                                       {
          CALL((yylsp[-1]), (yylsp[-1]), procProb());
        }
#line 6690 "parser.tab.c"
    break;

  case 260: /* CStateList: NonTypeId  */
#line 979 "parser.yy"
                  {
          CALL((yylsp[0]), (yylsp[0]), procStateCommit((yyvsp[0].string)));
        }
#line 6698 "parser.tab.c"
    break;

  case 261: /* CStateList: CStateList ',' NonTypeId  */
#line 982 "parser.yy"
                                   {
          CALL((yylsp[-2]), (yylsp[0]), procStateCommit((yyvsp[0].string)));
        }
#line 6706 "parser.tab.c"
    break;

  case 262: /* UStateList: NonTypeId  */
#line 988 "parser.yy"
                  {
          CALL((yylsp[0]), (yylsp[0]), procStateUrgent((yyvsp[0].string)));
        }
#line 6714 "parser.tab.c"
    break;

  case 263: /* UStateList: UStateList ',' NonTypeId  */
#line 991 "parser.yy"
                                   {
          CALL((yylsp[-2]), (yylsp[0]), procStateUrgent((yyvsp[0].string)));
        }
#line 6722 "parser.tab.c"
    break;

  case 265: /* ExpRate: Expression ':' Expression  */
#line 998 "parser.yy"
                                    {
	    CALL((yylsp[-2]),(yylsp[0]), exprBinary(FRACTION));
	}
#line 6730 "parser.tab.c"
    break;

  case 266: /* $@17: %empty  */
#line 1007 "parser.yy"
            {
          CALL((yylsp[0]), (yylsp[0]), blockBegin());
        }
#line 6738 "parser.tab.c"
    break;

  case 267: /* Block: '{' $@17 BlockLocalDeclList StatementList '}'  */
#line 1010 "parser.yy"
                                             {
          CALL((yylsp[-3]), (yylsp[-1]), blockEnd());
        }
#line 6746 "parser.tab.c"
    break;

  case 276: /* $@18: %empty  */
#line 1031 "parser.yy"
                      { CALL((yylsp[-1]), (yylsp[0]), ifBegin()); }
#line 6752 "parser.tab.c"
    break;

  case 277: /* IfCondition: T_IF '(' $@18 ExprList ')'  */
#line 1031 "parser.yy"
                                                                { CALL((yylsp[-2]), (yylsp[-2]), ifCondition()); }
#line 6758 "parser.tab.c"
    break;

  case 278: /* IfConditionThenMatched: IfCondition MatchedStatement T_ELSE  */
#line 1033 "parser.yy"
                                                            { CALL((yylsp[-2]), (yylsp[0]), ifThen()); }
#line 6764 "parser.tab.c"
    break;

  case 279: /* MatchedStatement: IfConditionThenMatched MatchedStatement  */
#line 1035 "parser.yy"
                                                          {
	    CALL((yylsp[-1]), (yylsp[0]), ifEnd(true));
	}
#line 6772 "parser.tab.c"
    break;

  case 281: /* UnmatchedStatement: IfCondition Statement  */
#line 1041 "parser.yy"
                                          {
            CALL((yylsp[0]), (yylsp[0]), ifThen());
            CALL((yylsp[-1]), (yylsp[0]), ifEnd(false));
	}
#line 6781 "parser.tab.c"
    break;

  case 282: /* UnmatchedStatement: IfConditionThenMatched UnmatchedStatement  */
#line 1045 "parser.yy"
                                                    {
	    CALL((yylsp[-1]), (yylsp[0]), ifEnd(true));
	}
#line 6789 "parser.tab.c"
    break;

  case 284: /* OtherStatement: ';'  */
#line 1052 "parser.yy"
              {
          CALL((yylsp[0]), (yylsp[0]), emptyStatement());
        }
#line 6797 "parser.tab.c"
    break;

  case 285: /* OtherStatement: Expression ';'  */
#line 1055 "parser.yy"
                         {
          CALL((yylsp[-1]), (yylsp[0]), exprStatement());
        }
#line 6805 "parser.tab.c"
    break;

  case 288: /* OtherStatement: T_BREAK ';'  */
#line 1060 "parser.yy"
                      {
            CALL((yylsp[-1]), (yylsp[0]), breakStatement());
          }
#line 6813 "parser.tab.c"
    break;

  case 289: /* OtherStatement: T_CONTINUE ';'  */
#line 1063 "parser.yy"
                         {
          CALL((yylsp[-1]), (yylsp[0]), continueStatement());
        }
#line 6821 "parser.tab.c"
    break;

  case 290: /* $@19: %empty  */
#line 1066 "parser.yy"
                                    {
            CALL((yylsp[-3]), (yylsp[0]), switchBegin());
        }
#line 6829 "parser.tab.c"
    break;

  case 291: /* OtherStatement: T_SWITCH '(' ExprList ')' $@19 '{' SwitchCaseList '}'  */
#line 1069 "parser.yy"
                                 {
               CALL((yylsp[-3]), (yylsp[-1]), switchEnd());
          }
#line 6837 "parser.tab.c"
    break;

  case 292: /* OtherStatement: T_RETURN Expression ';'  */
#line 1072 "parser.yy"
                                  {
          CALL((yylsp[-2]), (yylsp[0]), returnStatement(true));
        }
#line 6845 "parser.tab.c"
    break;

  case 293: /* OtherStatement: T_RETURN ';'  */
#line 1075 "parser.yy"
                       {
          CALL((yylsp[-1]), (yylsp[0]), returnStatement(false));
        }
#line 6853 "parser.tab.c"
    break;

  case 294: /* OtherStatement: T_ASSERT Expression ';'  */
#line 1078 "parser.yy"
                                  {
	    CALL((yylsp[-2]), (yylsp[-1]), assertStatement());
	}
#line 6861 "parser.tab.c"
    break;

  case 295: /* $@20: %empty  */
#line 1083 "parser.yy"
                                                               {
            CALL((yylsp[-7]), (yylsp[0]), forBegin());
        }
#line 6869 "parser.tab.c"
    break;

  case 296: /* ForStatement: T_FOR '(' ExprList ';' ExprList ';' ExprList ')' $@20 Statement  */
#line 1086 "parser.yy"
                  {
            CALL((yylsp[-1]), (yylsp[-1]), forEnd());
        }
#line 6877 "parser.tab.c"
    break;

  case 297: /* $@21: %empty  */
#line 1089 "parser.yy"
                                    {
            CALL((yylsp[-5]), (yylsp[0]), iterationBegin((yyvsp[-3].string)));
        }
#line 6885 "parser.tab.c"
    break;

  case 298: /* ForStatement: T_FOR '(' Id ':' Type ')' $@21 Statement  */
#line 1092 "parser.yy"
                  {
            CALL((yylsp[-1]), (yylsp[-1]), iterationEnd((yyvsp[-5].string)));
        }
#line 6893 "parser.tab.c"
    break;

  case 300: /* $@22: %empty  */
#line 1098 "parser.yy"
                            {
            CALL((yylsp[-1]), (yylsp[0]), whileBegin());
        }
#line 6901 "parser.tab.c"
    break;

  case 301: /* WhileStatement: T_WHILE '(' $@22 ExprList ')' Statement  */
#line 1101 "parser.yy"
                               {
            CALL((yylsp[-3]), (yylsp[-2]), whileEnd());
	}
#line 6909 "parser.tab.c"
    break;

  case 303: /* $@23: %empty  */
#line 1105 "parser.yy"
               {
            CALL((yylsp[0]), (yylsp[0]), doWhileBegin());
	}
#line 6917 "parser.tab.c"
    break;

  case 304: /* WhileStatement: T_DO $@23 Statement T_WHILE '(' ExprList ')' ';'  */
#line 1108 "parser.yy"
                                                 {
            CALL((yylsp[-6]), (yylsp[-1]), doWhileEnd());
        }
#line 6925 "parser.tab.c"
    break;

  case 307: /* $@24: %empty  */
#line 1118 "parser.yy"
                              {
	    CALL((yylsp[-2]), (yylsp[0]), caseBegin());
        }
#line 6933 "parser.tab.c"
    break;

  case 308: /* SwitchCase: T_CASE Expression ':' $@24 StatementList  */
#line 1121 "parser.yy"
                      {
            CALL((yylsp[-1]), (yylsp[-1]), caseEnd());
	}
#line 6941 "parser.tab.c"
    break;

  case 309: /* $@25: %empty  */
#line 1124 "parser.yy"
                        {
            CALL((yylsp[-1]), (yylsp[0]), defaultBegin());
        }
#line 6949 "parser.tab.c"
    break;

  case 310: /* SwitchCase: T_DEFAULT ':' $@25 StatementList  */
#line 1127 "parser.yy"
                      {
            CALL((yylsp[-1]), (yylsp[-1]), defaultEnd());
        }
#line 6957 "parser.tab.c"
    break;

  case 312: /* ExprList: ExprList ',' Expression  */
#line 1134 "parser.yy"
                                  {
          CALL((yylsp[-2]), (yylsp[0]), exprComma());
        }
#line 6965 "parser.tab.c"
    break;

  case 313: /* Expression: T_FALSE  */
#line 1139 "parser.yy"
                {
	    CALL((yylsp[0]), (yylsp[0]), exprFalse());
        }
#line 6973 "parser.tab.c"
    break;

  case 314: /* Expression: T_TRUE  */
#line 1142 "parser.yy"
                 {
	    CALL((yylsp[0]), (yylsp[0]), exprTrue());
        }
#line 6981 "parser.tab.c"
    break;

  case 315: /* Expression: T_NAT  */
#line 1145 "parser.yy"
                 {
	    CALL((yylsp[0]), (yylsp[0]), exprNat((yyvsp[0].number)));
        }
#line 6989 "parser.tab.c"
    break;

  case 316: /* Expression: T_FLOATING  */
#line 1148 "parser.yy"
                     {
	    CALL((yylsp[0]), (yylsp[0]), exprDouble((yyvsp[0].floating)));
	}
#line 6997 "parser.tab.c"
    break;

  case 317: /* Expression: BuiltinFunction1 '(' Expression ')'  */
#line 1151 "parser.yy"
                                              {
	    CALL((yylsp[-3]), (yylsp[0]), exprBuiltinFunction1((yyvsp[-3].kind)));
	}
#line 7005 "parser.tab.c"
    break;

  case 318: /* Expression: BuiltinFunction2 '(' Expression ',' Expression ')'  */
#line 1154 "parser.yy"
                                                             {
	    CALL((yylsp[-5]), (yylsp[0]), exprBuiltinFunction2((yyvsp[-5].kind)));
	}
#line 7013 "parser.tab.c"
    break;

  case 319: /* Expression: BuiltinFunction3 '(' Expression ',' Expression ',' Expression ')'  */
#line 1157 "parser.yy"
                                                                            {
	    CALL((yylsp[-7]), (yylsp[0]), exprBuiltinFunction3((yyvsp[-7].kind)));
	}
#line 7021 "parser.tab.c"
    break;

  case 320: /* Expression: NonTypeId  */
#line 1160 "parser.yy"
                    {
	    CALL((yylsp[0]), (yylsp[0]), exprId((yyvsp[0].string)));
        }
#line 7029 "parser.tab.c"
    break;

  case 321: /* $@26: %empty  */
#line 1163 "parser.yy"
                         {
            CALL((yylsp[-1]), (yylsp[0]), exprCallBegin());
        }
#line 7037 "parser.tab.c"
    break;

  case 322: /* Expression: Expression '(' $@26 ArgList ')'  */
#line 1165 "parser.yy"
                       {
            CALL((yylsp[-4]), (yylsp[0]), exprCallEnd((yyvsp[-1].number)));
        }
#line 7045 "parser.tab.c"
    break;

  case 323: /* $@27: %empty  */
#line 1168 "parser.yy"
                         {
            CALL((yylsp[-1]), (yylsp[0]), exprCallBegin());
        }
#line 7053 "parser.tab.c"
    break;

  case 324: /* Expression: Expression '(' $@27 error ')'  */
#line 1170 "parser.yy"
                    {
            CALL((yylsp[-4]), (yylsp[0]), exprCallEnd(0));
        }
#line 7061 "parser.tab.c"
    break;

  case 325: /* Expression: Expression '[' Expression ']'  */
#line 1173 "parser.yy"
                                        {
          CALL((yylsp[-3]), (yylsp[0]), exprArray());
        }
#line 7069 "parser.tab.c"
    break;

  case 326: /* Expression: Expression '[' error ']'  */
#line 1176 "parser.yy"
                                   {
          CALL((yylsp[-3]), (yylsp[0]), exprFalse());
        }
#line 7077 "parser.tab.c"
    break;

  case 328: /* Expression: '(' error ')'  */
#line 1180 "parser.yy"
                        {
          CALL((yylsp[-2]), (yylsp[0]), exprFalse());
        }
#line 7085 "parser.tab.c"
    break;

  case 329: /* Expression: Expression T_INCREMENT  */
#line 1183 "parser.yy"
                                 {
          CALL((yylsp[-1]), (yylsp[0]), exprPostIncrement());
        }
#line 7093 "parser.tab.c"
    break;

  case 330: /* Expression: T_INCREMENT Expression  */
#line 1186 "parser.yy"
                                 {
          CALL((yylsp[-1]), (yylsp[0]), exprPreIncrement());
        }
#line 7101 "parser.tab.c"
    break;

  case 331: /* Expression: Expression T_DECREMENT  */
#line 1189 "parser.yy"
                                 {
          CALL((yylsp[-1]), (yylsp[0]), exprPostDecrement());
        }
#line 7109 "parser.tab.c"
    break;

  case 332: /* Expression: T_DECREMENT Expression  */
#line 1192 "parser.yy"
                                 {
          CALL((yylsp[-1]), (yylsp[0]), exprPreDecrement());
        }
#line 7117 "parser.tab.c"
    break;

  case 333: /* Expression: T_MINUS T_POS_NEG_MAX  */
#line 1195 "parser.yy"
                                {
          CALL((yylsp[-1]), (yylsp[0]), exprNat(INT_MIN));
	}
#line 7125 "parser.tab.c"
    break;

  case 334: /* Expression: UnaryOp Expression  */
#line 1198 "parser.yy"
                             {
          CALL((yylsp[-1]), (yylsp[0]), exprUnary((yyvsp[-1].kind)));
        }
#line 7133 "parser.tab.c"
    break;

  case 335: /* Expression: Expression T_LT Expression  */
#line 1201 "parser.yy"
                                     {
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(LT));
        }
#line 7141 "parser.tab.c"
    break;

  case 336: /* Expression: Expression T_LEQ Expression  */
#line 1204 "parser.yy"
                                      {
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(LE));
        }
#line 7149 "parser.tab.c"
    break;

  case 337: /* Expression: Expression T_EQ Expression  */
#line 1207 "parser.yy"
                                     {
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(EQ));
        }
#line 7157 "parser.tab.c"
    break;

  case 338: /* Expression: Expression T_NEQ Expression  */
#line 1210 "parser.yy"
                                      {
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(NEQ));
        }
#line 7165 "parser.tab.c"
    break;

  case 339: /* Expression: Expression T_GT Expression  */
#line 1213 "parser.yy"
                                     {
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(GT));
        }
#line 7173 "parser.tab.c"
    break;

  case 340: /* Expression: Expression T_GEQ Expression  */
#line 1216 "parser.yy"
                                      {
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(GE));
        }
#line 7181 "parser.tab.c"
    break;

  case 341: /* Expression: Expression T_PLUS Expression  */
#line 1219 "parser.yy"
                                       {
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(PLUS));
        }
#line 7189 "parser.tab.c"
    break;

  case 342: /* Expression: Expression T_MINUS Expression  */
#line 1222 "parser.yy"
                                        {
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(MINUS));
        }
#line 7197 "parser.tab.c"
    break;

  case 343: /* Expression: Expression T_MULT Expression  */
#line 1225 "parser.yy"
                                       {
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(MULT));
        }
#line 7205 "parser.tab.c"
    break;

  case 344: /* Expression: Expression T_DIV Expression  */
#line 1228 "parser.yy"
                                      {
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(DIV));
        }
#line 7213 "parser.tab.c"
    break;

  case 345: /* Expression: Expression T_MOD Expression  */
#line 1231 "parser.yy"
                                      {
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(MOD));
        }
#line 7221 "parser.tab.c"
    break;

  case 346: /* Expression: Expression '&' Expression  */
#line 1234 "parser.yy"
                                    {
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(BIT_AND));
        }
#line 7229 "parser.tab.c"
    break;

  case 347: /* Expression: Expression T_OR Expression  */
#line 1237 "parser.yy"
                                     {
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(BIT_OR));
        }
#line 7237 "parser.tab.c"
    break;

  case 348: /* Expression: Expression T_XOR Expression  */
#line 1240 "parser.yy"
                                      {
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(BIT_XOR));
        }
#line 7245 "parser.tab.c"
    break;

  case 349: /* Expression: Expression T_LSHIFT Expression  */
#line 1243 "parser.yy"
                                         {
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(BIT_LSHIFT));
        }
#line 7253 "parser.tab.c"
    break;

  case 350: /* Expression: Expression T_RSHIFT Expression  */
#line 1246 "parser.yy"
                                         {
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(BIT_RSHIFT));
        }
#line 7261 "parser.tab.c"
    break;

  case 351: /* Expression: Expression T_BOOL_AND Expression  */
#line 1249 "parser.yy"
                                           {
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(AND));
        }
#line 7269 "parser.tab.c"
    break;

  case 352: /* Expression: Expression T_BOOL_OR Expression  */
#line 1252 "parser.yy"
                                          {
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(OR));
        }
#line 7277 "parser.tab.c"
    break;

  case 353: /* Expression: Expression '?' Expression ':' Expression  */
#line 1255 "parser.yy"
                                                   {
          CALL((yylsp[-4]), (yylsp[0]), exprInlineIf());
        }
#line 7285 "parser.tab.c"
    break;

  case 354: /* Expression: Expression '.' NonTypeId  */
#line 1258 "parser.yy"
                                   {
          CALL((yylsp[-2]), (yylsp[0]), exprDot((yyvsp[0].string)));
        }
#line 7293 "parser.tab.c"
    break;

  case 355: /* Expression: Expression '\''  */
#line 1261 "parser.yy"
                          {
            CALL((yylsp[-1]), (yylsp[0]), exprUnary(RATE));
        }
#line 7301 "parser.tab.c"
    break;

  case 356: /* Expression: T_DEADLOCK  */
#line 1264 "parser.yy"
                     {
          CALL((yylsp[0]), (yylsp[0]), exprDeadlock());
        }
#line 7309 "parser.tab.c"
    break;

  case 357: /* $@28: %empty  */
#line 1267 "parser.yy"
                                {
          CALL((yylsp[-1]), (yylsp[-1]), exprUnary(NOT));
        }
#line 7317 "parser.tab.c"
    break;

  case 358: /* Expression: Expression T_KW_IMPLY $@28 Expression  */
#line 1269 "parser.yy"
                     {
          CALL((yylsp[-1]), (yylsp[-1]), exprBinary(OR));
        }
#line 7325 "parser.tab.c"
    break;

  case 359: /* Expression: Expression T_KW_AND Expression  */
#line 1272 "parser.yy"
                                         {
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(AND));
        }
#line 7333 "parser.tab.c"
    break;

  case 360: /* Expression: Expression T_KW_OR Expression  */
#line 1275 "parser.yy"
                                        {
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(OR));
        }
#line 7341 "parser.tab.c"
    break;

  case 361: /* Expression: Expression T_KW_XOR Expression  */
#line 1278 "parser.yy"
                                         {
	    CALL((yylsp[-2]), (yylsp[0]), exprBinary(XOR));
	}
#line 7349 "parser.tab.c"
    break;

  case 362: /* Expression: Expression T_MIN Expression  */
#line 1281 "parser.yy"
                                      {
            CALL((yylsp[-2]), (yylsp[0]), exprBinary(MIN));
        }
#line 7357 "parser.tab.c"
    break;

  case 363: /* Expression: Expression T_MAX Expression  */
#line 1284 "parser.yy"
                                      {
            CALL((yylsp[-2]), (yylsp[0]), exprBinary(MAX));
        }
#line 7365 "parser.tab.c"
    break;

  case 364: /* $@29: %empty  */
#line 1287 "parser.yy"
                                    {
            CALL((yylsp[-5]), (yylsp[0]), exprSumBegin((yyvsp[-3].string)));
        }
#line 7373 "parser.tab.c"
    break;

  case 365: /* Expression: T_SUM '(' Id ':' Type ')' $@29 Expression  */
#line 1289 "parser.yy"
                     {
            CALL((yylsp[-7]), (yylsp[0]), exprSumEnd((yyvsp[-5].string)));
        }
#line 7381 "parser.tab.c"
    break;

  case 366: /* $@30: %empty  */
#line 1292 "parser.yy"
                                           {
            CALL((yylsp[-5]), (yylsp[0]), exprForAllBegin((yyvsp[-3].string)));
        }
#line 7389 "parser.tab.c"
    break;

  case 367: /* Expression: T_FORALL '(' Id ':' Type ')' $@30 Expression  */
#line 1294 "parser.yy"
                     {
            CALL((yylsp[-7]), (yylsp[0]), exprForAllEnd((yyvsp[-5].string)));
        }
#line 7397 "parser.tab.c"
    break;

  case 368: /* $@31: %empty  */
#line 1297 "parser.yy"
                                       {
            CALL((yylsp[-5]), (yylsp[0]), exprExistsBegin((yyvsp[-3].string)));
        }
#line 7405 "parser.tab.c"
    break;

  case 369: /* Expression: T_EXISTS '(' Id ':' Type ')' $@31 Expression  */
#line 1299 "parser.yy"
                     {
            CALL((yylsp[-7]), (yylsp[0]), exprExistsEnd((yyvsp[-5].string)));
        }
#line 7413 "parser.tab.c"
    break;

  case 373: /* $@32: %empty  */
#line 1308 "parser.yy"
                          {
	    CALL((yylsp[-1]),(yylsp[0]), exprId((yyvsp[0].string)));
	}
#line 7421 "parser.tab.c"
    break;

  case 374: /* DynamicExpression: T_SPAWN NonTypeId $@32 '(' ArgList ')'  */
#line 1310 "parser.yy"
                          {
	    CALL((yylsp[-5]),(yylsp[0]), exprSpawn((yyvsp[-1].number)));
	}
#line 7429 "parser.tab.c"
    break;

  case 375: /* DynamicExpression: T_EXIT '(' ')'  */
#line 1313 "parser.yy"
                         {
	    CALL((yylsp[-2]),(yylsp[0]), exprExit());
	}
#line 7437 "parser.tab.c"
    break;

  case 376: /* DynamicExpression: T_NUMOF '(' NonTypeId ')'  */
#line 1316 "parser.yy"
                                   {
	    CALL((yylsp[-1]),(yylsp[-1]), exprId((yyvsp[-1].string)));
	    CALL((yylsp[-3]),(yylsp[0]), exprNumOf());
	}
#line 7446 "parser.tab.c"
    break;

  case 377: /* $@33: %empty  */
#line 1320 "parser.yy"
                                    {
	    CALL((yylsp[-4]),(yylsp[0]), exprId((yyvsp[0].string)));
	    CALL((yylsp[-4]),(yylsp[0]), exprForAllDynamicBegin((yyvsp[-2].string),(yyvsp[0].string)));
	}
#line 7455 "parser.tab.c"
    break;

  case 378: /* DynamicExpression: T_FORALL '(' Id ':' NonTypeId $@33 ')' '(' Expression ')'  */
#line 1323 "parser.yy"
                                    {
	    CALL((yylsp[-9]),(yylsp[-2]), exprForAllDynamicEnd((yyvsp[-7].string)));
	}
#line 7463 "parser.tab.c"
    break;

  case 379: /* $@34: %empty  */
#line 1326 "parser.yy"
                                    {
	    CALL((yylsp[-4]),(yylsp[0]), exprId((yyvsp[0].string)));
	    CALL((yylsp[-4]),(yylsp[0]), exprExistsDynamicBegin((yyvsp[-2].string),(yyvsp[0].string)));
	}
#line 7472 "parser.tab.c"
    break;

  case 380: /* DynamicExpression: T_EXISTS '(' Id ':' NonTypeId $@34 ')' '(' Expression ')'  */
#line 1329 "parser.yy"
                                  {
	    CALL((yylsp[-9]),(yylsp[-2]), exprExistsDynamicEnd((yyvsp[-7].string)));
	}
#line 7480 "parser.tab.c"
    break;

  case 381: /* $@35: %empty  */
#line 1332 "parser.yy"
                                 {
	    CALL((yylsp[-4]),(yylsp[0]), exprId((yyvsp[0].string)));
	    CALL((yylsp[-4]),(yylsp[0]), exprSumDynamicBegin((yyvsp[-2].string),(yyvsp[0].string)));
	}
#line 7489 "parser.tab.c"
    break;

  case 382: /* DynamicExpression: T_SUM '(' Id ':' NonTypeId $@35 ')' Expression  */
#line 1335 "parser.yy"
                           {
	    CALL((yylsp[-7]),(yylsp[0]), exprSumDynamicEnd((yyvsp[-5].string)));
	}
#line 7497 "parser.tab.c"
    break;

  case 383: /* $@36: %empty  */
#line 1338 "parser.yy"
                                     {
	    CALL((yylsp[-4]),(yylsp[0]), exprId((yyvsp[0].string)));
	    CALL((yylsp[-4]),(yylsp[0]), exprForeachDynamicBegin((yyvsp[-2].string),(yyvsp[0].string)));
	}
#line 7506 "parser.tab.c"
    break;

  case 384: /* DynamicExpression: T_FOREACH '(' Id ':' NonTypeId $@36 ')' Expression  */
#line 1341 "parser.yy"
                           {
	    CALL((yylsp[-7]),(yylsp[0]), exprForeachDynamicEnd((yyvsp[-5].string)));
	}
#line 7514 "parser.tab.c"
    break;

  case 385: /* Assignment: Expression AssignOp Expression  */
#line 1348 "parser.yy"
                                       {
          CALL((yylsp[-2]), (yylsp[0]), exprAssignment((yyvsp[-1].kind)));
        }
#line 7522 "parser.tab.c"
    break;

  case 386: /* AssignOp: T_ASSIGNMENT  */
#line 1354 "parser.yy"
                       { (yyval.kind) = ASSIGN; }
#line 7528 "parser.tab.c"
    break;

  case 387: /* AssignOp: T_ASSPLUS  */
#line 1355 "parser.yy"
                      { (yyval.kind) = ASSPLUS; }
#line 7534 "parser.tab.c"
    break;

  case 388: /* AssignOp: T_ASSMINUS  */
#line 1356 "parser.yy"
                      { (yyval.kind) = ASSMINUS; }
#line 7540 "parser.tab.c"
    break;

  case 389: /* AssignOp: T_ASSDIV  */
#line 1357 "parser.yy"
                      { (yyval.kind) = ASSDIV; }
#line 7546 "parser.tab.c"
    break;

  case 390: /* AssignOp: T_ASSMOD  */
#line 1358 "parser.yy"
                      { (yyval.kind) = ASSMOD; }
#line 7552 "parser.tab.c"
    break;

  case 391: /* AssignOp: T_ASSMULT  */
#line 1359 "parser.yy"
                      { (yyval.kind) = ASSMULT; }
#line 7558 "parser.tab.c"
    break;

  case 392: /* AssignOp: T_ASSAND  */
#line 1360 "parser.yy"
                      { (yyval.kind) = ASSAND; }
#line 7564 "parser.tab.c"
    break;

  case 393: /* AssignOp: T_ASSOR  */
#line 1361 "parser.yy"
                      { (yyval.kind) = ASSOR; }
#line 7570 "parser.tab.c"
    break;

  case 394: /* AssignOp: T_ASSXOR  */
#line 1362 "parser.yy"
                      { (yyval.kind) = ASSXOR; }
#line 7576 "parser.tab.c"
    break;

  case 395: /* AssignOp: T_ASSLSHIFT  */
#line 1363 "parser.yy"
                      { (yyval.kind) = ASSLSHIFT; }
#line 7582 "parser.tab.c"
    break;

  case 396: /* AssignOp: T_ASSRSHIFT  */
#line 1364 "parser.yy"
                      { (yyval.kind) = ASSRSHIFT; }
#line 7588 "parser.tab.c"
    break;

  case 397: /* UnaryOp: T_MINUS  */
#line 1369 "parser.yy"
                      { (yyval.kind) = MINUS; }
#line 7594 "parser.tab.c"
    break;

  case 398: /* UnaryOp: T_PLUS  */
#line 1370 "parser.yy"
                      { (yyval.kind) = PLUS; }
#line 7600 "parser.tab.c"
    break;

  case 399: /* UnaryOp: T_EXCLAM  */
#line 1371 "parser.yy"
                      { (yyval.kind) = NOT; }
#line 7606 "parser.tab.c"
    break;

  case 400: /* UnaryOp: T_KW_NOT  */
#line 1372 "parser.yy"
                      { (yyval.kind) = NOT; }
#line 7612 "parser.tab.c"
    break;

  case 401: /* BuiltinFunction1: T_ABS  */
#line 1376 "parser.yy"
                  { (yyval.kind) = ABS_F; }
#line 7618 "parser.tab.c"
    break;

  case 402: /* BuiltinFunction1: T_FABS  */
#line 1377 "parser.yy"
                   { (yyval.kind) = FABS_F; }
#line 7624 "parser.tab.c"
    break;

  case 403: /* BuiltinFunction1: T_EXP  */
#line 1378 "parser.yy"
                   { (yyval.kind) = EXP_F; }
#line 7630 "parser.tab.c"
    break;

  case 404: /* BuiltinFunction1: T_EXP2  */
#line 1379 "parser.yy"
                   { (yyval.kind) = EXP2_F; }
#line 7636 "parser.tab.c"
    break;

  case 405: /* BuiltinFunction1: T_EXPM1  */
#line 1380 "parser.yy"
                   { (yyval.kind) = EXPM1_F; }
#line 7642 "parser.tab.c"
    break;

  case 406: /* BuiltinFunction1: T_LN  */
#line 1381 "parser.yy"
                   { (yyval.kind) = LN_F; }
#line 7648 "parser.tab.c"
    break;

  case 407: /* BuiltinFunction1: T_LOG  */
#line 1382 "parser.yy"
                   { (yyval.kind) = LOG_F; }
#line 7654 "parser.tab.c"
    break;

  case 408: /* BuiltinFunction1: T_LOG10  */
#line 1383 "parser.yy"
                   { (yyval.kind) = LOG10_F; }
#line 7660 "parser.tab.c"
    break;

  case 409: /* BuiltinFunction1: T_LOG2  */
#line 1384 "parser.yy"
                   { (yyval.kind) = LOG2_F; }
#line 7666 "parser.tab.c"
    break;

  case 410: /* BuiltinFunction1: T_LOG1P  */
#line 1385 "parser.yy"
                   { (yyval.kind) = LOG1P_F; }
#line 7672 "parser.tab.c"
    break;

  case 411: /* BuiltinFunction1: T_SQRT  */
#line 1386 "parser.yy"
                   { (yyval.kind) = SQRT_F; }
#line 7678 "parser.tab.c"
    break;

  case 412: /* BuiltinFunction1: T_CBRT  */
#line 1387 "parser.yy"
                   { (yyval.kind) = CBRT_F; }
#line 7684 "parser.tab.c"
    break;

  case 413: /* BuiltinFunction1: T_SIN  */
#line 1388 "parser.yy"
                   { (yyval.kind) = SIN_F; }
#line 7690 "parser.tab.c"
    break;

  case 414: /* BuiltinFunction1: T_COS  */
#line 1389 "parser.yy"
                   { (yyval.kind) = COS_F; }
#line 7696 "parser.tab.c"
    break;

  case 415: /* BuiltinFunction1: T_TAN  */
#line 1390 "parser.yy"
                   { (yyval.kind) = TAN_F; }
#line 7702 "parser.tab.c"
    break;

  case 416: /* BuiltinFunction1: T_ASIN  */
#line 1391 "parser.yy"
                   { (yyval.kind) = ASIN_F; }
#line 7708 "parser.tab.c"
    break;

  case 417: /* BuiltinFunction1: T_ACOS  */
#line 1392 "parser.yy"
                   { (yyval.kind) = ACOS_F; }
#line 7714 "parser.tab.c"
    break;

  case 418: /* BuiltinFunction1: T_ATAN  */
#line 1393 "parser.yy"
                   { (yyval.kind) = ATAN_F; }
#line 7720 "parser.tab.c"
    break;

  case 419: /* BuiltinFunction1: T_SINH  */
#line 1394 "parser.yy"
                   { (yyval.kind) = SINH_F; }
#line 7726 "parser.tab.c"
    break;

  case 420: /* BuiltinFunction1: T_COSH  */
#line 1395 "parser.yy"
                   { (yyval.kind) = COSH_F; }
#line 7732 "parser.tab.c"
    break;

  case 421: /* BuiltinFunction1: T_TANH  */
#line 1396 "parser.yy"
                   { (yyval.kind) = TANH_F; }
#line 7738 "parser.tab.c"
    break;

  case 422: /* BuiltinFunction1: T_ASINH  */
#line 1397 "parser.yy"
                   { (yyval.kind) = ASINH_F; }
#line 7744 "parser.tab.c"
    break;

  case 423: /* BuiltinFunction1: T_ACOSH  */
#line 1398 "parser.yy"
                   { (yyval.kind) = ACOSH_F; }
#line 7750 "parser.tab.c"
    break;

  case 424: /* BuiltinFunction1: T_ATANH  */
#line 1399 "parser.yy"
                   { (yyval.kind) = ATANH_F; }
#line 7756 "parser.tab.c"
    break;

  case 425: /* BuiltinFunction1: T_ERF  */
#line 1400 "parser.yy"
                   { (yyval.kind) = ERF_F; }
#line 7762 "parser.tab.c"
    break;

  case 426: /* BuiltinFunction1: T_ERFC  */
#line 1401 "parser.yy"
                   { (yyval.kind) = ERFC_F; }
#line 7768 "parser.tab.c"
    break;

  case 427: /* BuiltinFunction1: T_TGAMMA  */
#line 1402 "parser.yy"
                   { (yyval.kind) = TGAMMA_F; }
#line 7774 "parser.tab.c"
    break;

  case 428: /* BuiltinFunction1: T_LGAMMA  */
#line 1403 "parser.yy"
                   { (yyval.kind) = LGAMMA_F; }
#line 7780 "parser.tab.c"
    break;

  case 429: /* BuiltinFunction1: T_CEIL  */
#line 1404 "parser.yy"
                   { (yyval.kind) = CEIL_F; }
#line 7786 "parser.tab.c"
    break;

  case 430: /* BuiltinFunction1: T_FLOOR  */
#line 1405 "parser.yy"
                   { (yyval.kind) = FLOOR_F; }
#line 7792 "parser.tab.c"
    break;

  case 431: /* BuiltinFunction1: T_TRUNC  */
#line 1406 "parser.yy"
                   { (yyval.kind) = TRUNC_F; }
#line 7798 "parser.tab.c"
    break;

  case 432: /* BuiltinFunction1: T_ROUND  */
#line 1407 "parser.yy"
                   { (yyval.kind) = ROUND_F; }
#line 7804 "parser.tab.c"
    break;

  case 433: /* BuiltinFunction1: T_FINT  */
#line 1408 "parser.yy"
                   { (yyval.kind) = FINT_F; }
#line 7810 "parser.tab.c"
    break;

  case 434: /* BuiltinFunction1: T_ILOGB  */
#line 1409 "parser.yy"
                   { (yyval.kind) = ILOGB_F; }
#line 7816 "parser.tab.c"
    break;

  case 435: /* BuiltinFunction1: T_LOGB  */
#line 1410 "parser.yy"
                   { (yyval.kind) = LOGB_F; }
#line 7822 "parser.tab.c"
    break;

  case 436: /* BuiltinFunction1: T_FPCLASSIFY  */
#line 1411 "parser.yy"
                       { (yyval.kind) = FPCLASSIFY_F; }
#line 7828 "parser.tab.c"
    break;

  case 437: /* BuiltinFunction1: T_ISFINITE  */
#line 1412 "parser.yy"
                     { (yyval.kind) = ISFINITE_F; }
#line 7834 "parser.tab.c"
    break;

  case 438: /* BuiltinFunction1: T_ISINF  */
#line 1413 "parser.yy"
                   { (yyval.kind) = ISINF_F; }
#line 7840 "parser.tab.c"
    break;

  case 439: /* BuiltinFunction1: T_ISNAN  */
#line 1414 "parser.yy"
                   { (yyval.kind) = ISNAN_F; }
#line 7846 "parser.tab.c"
    break;

  case 440: /* BuiltinFunction1: T_ISNORMAL  */
#line 1415 "parser.yy"
                     { (yyval.kind) = ISNORMAL_F; }
#line 7852 "parser.tab.c"
    break;

  case 441: /* BuiltinFunction1: T_SIGNBIT  */
#line 1416 "parser.yy"
                    { (yyval.kind) = SIGNBIT_F; }
#line 7858 "parser.tab.c"
    break;

  case 442: /* BuiltinFunction1: T_ISUNORDERED  */
#line 1417 "parser.yy"
                        { (yyval.kind) = ISUNORDERED_F; }
#line 7864 "parser.tab.c"
    break;

  case 443: /* BuiltinFunction1: T_RANDOM  */
#line 1418 "parser.yy"
                          { (yyval.kind) = RANDOM_F; }
#line 7870 "parser.tab.c"
    break;

  case 444: /* BuiltinFunction1: T_RANDOM_POISSON  */
#line 1419 "parser.yy"
                           { (yyval.kind) = RANDOM_POISSON_F; }
#line 7876 "parser.tab.c"
    break;

  case 445: /* BuiltinFunction2: T_FMOD  */
#line 1423 "parser.yy"
                   { (yyval.kind) = FMOD_F; }
#line 7882 "parser.tab.c"
    break;

  case 446: /* BuiltinFunction2: T_FMAX  */
#line 1424 "parser.yy"
                   { (yyval.kind) = FMAX_F; }
#line 7888 "parser.tab.c"
    break;

  case 447: /* BuiltinFunction2: T_FMIN  */
#line 1425 "parser.yy"
                   { (yyval.kind) = FMIN_F; }
#line 7894 "parser.tab.c"
    break;

  case 448: /* BuiltinFunction2: T_FDIM  */
#line 1426 "parser.yy"
                   { (yyval.kind) = FDIM_F; }
#line 7900 "parser.tab.c"
    break;

  case 449: /* BuiltinFunction2: T_POW  */
#line 1427 "parser.yy"
                   { (yyval.kind) = POW_F; }
#line 7906 "parser.tab.c"
    break;

  case 450: /* BuiltinFunction2: T_HYPOT  */
#line 1428 "parser.yy"
                   { (yyval.kind) = HYPOT_F; }
#line 7912 "parser.tab.c"
    break;

  case 451: /* BuiltinFunction2: T_ATAN2  */
#line 1429 "parser.yy"
                   { (yyval.kind) = ATAN2_F; }
#line 7918 "parser.tab.c"
    break;

  case 452: /* BuiltinFunction2: T_LDEXP  */
#line 1430 "parser.yy"
                   { (yyval.kind) = LDEXP_F; }
#line 7924 "parser.tab.c"
    break;

  case 453: /* BuiltinFunction2: T_NEXTAFTER  */
#line 1431 "parser.yy"
                      { (yyval.kind) = NEXTAFTER_F; }
#line 7930 "parser.tab.c"
    break;

  case 454: /* BuiltinFunction2: T_COPYSIGN  */
#line 1432 "parser.yy"
                     { (yyval.kind) = COPYSIGN_F; }
#line 7936 "parser.tab.c"
    break;

  case 455: /* BuiltinFunction2: T_RANDOM_ARCSINE  */
#line 1433 "parser.yy"
                           { (yyval.kind) = RANDOM_ARCSINE_F; }
#line 7942 "parser.tab.c"
    break;

  case 456: /* BuiltinFunction2: T_RANDOM_BETA  */
#line 1434 "parser.yy"
                           { (yyval.kind) = RANDOM_BETA_F;    }
#line 7948 "parser.tab.c"
    break;

  case 457: /* BuiltinFunction2: T_RANDOM_GAMMA  */
#line 1435 "parser.yy"
                           { (yyval.kind) = RANDOM_GAMMA_F;   }
#line 7954 "parser.tab.c"
    break;

  case 458: /* BuiltinFunction2: T_RANDOM_NORMAL  */
#line 1436 "parser.yy"
                           { (yyval.kind) = RANDOM_NORMAL_F;  }
#line 7960 "parser.tab.c"
    break;

  case 459: /* BuiltinFunction2: T_RANDOM_WEIBULL  */
#line 1437 "parser.yy"
                           { (yyval.kind) = RANDOM_WEIBULL_F; }
#line 7966 "parser.tab.c"
    break;

  case 460: /* BuiltinFunction3: T_FMA  */
#line 1441 "parser.yy"
                   { (yyval.kind) = FMA_F; }
#line 7972 "parser.tab.c"
    break;

  case 461: /* BuiltinFunction3: T_RANDOM_TRI  */
#line 1442 "parser.yy"
                       { (yyval.kind) = RANDOM_TRI_F; }
#line 7978 "parser.tab.c"
    break;

  case 462: /* ArgList: %empty  */
#line 1447 "parser.yy"
                    { (yyval.number)=0; }
#line 7984 "parser.tab.c"
    break;

  case 463: /* ArgList: Expression  */
#line 1448 "parser.yy"
                     {
            (yyval.number) = 1;
        }
#line 7992 "parser.tab.c"
    break;

  case 464: /* ArgList: ArgList ',' Expression  */
#line 1451 "parser.yy"
                                 {
            (yyval.number) = (yyvsp[-2].number) + 1;
        }
#line 8000 "parser.tab.c"
    break;

  case 470: /* $@37: %empty  */
#line 1472 "parser.yy"
                     {
          CALL((yylsp[0]), (yylsp[0]), typeInt(ParserBuilder::PREFIX_CONST));
        }
#line 8008 "parser.tab.c"
    break;

  case 471: /* OldVarDecl: T_OLDCONST $@37 OldConstDeclIdList ';'  */
#line 1474 "parser.yy"
                                 {
          CALL((yylsp[-3]), (yylsp[-1]), typePop());
        }
#line 8016 "parser.tab.c"
    break;

  case 475: /* $@38: %empty  */
#line 1485 "parser.yy"
                  {
          CALL((yylsp[0]), (yylsp[0]), typeDuplicate());
        }
#line 8024 "parser.tab.c"
    break;

  case 476: /* OldConstDeclId: NonTypeId $@38 ArrayDecl Initializer  */
#line 1487 "parser.yy"
                                {
          CALL((yylsp[-3]), (yylsp[0]), declVar((yyvsp[-3].string), true));
        }
#line 8032 "parser.tab.c"
    break;

  case 477: /* $@39: %empty  */
#line 1496 "parser.yy"
                                       {
          CALL((yylsp[-3]), (yylsp[0]), procBegin((yyvsp[-2].string)));
        }
#line 8040 "parser.tab.c"
    break;

  case 478: /* OldProcDecl: T_PROCESS Id OldProcParams '{' $@39 OldProcBody '}'  */
#line 1499 "parser.yy"
                        {
          CALL((yylsp[-2]), (yylsp[-1]), procEnd());
        }
#line 8048 "parser.tab.c"
    break;

  case 479: /* $@40: %empty  */
#line 1502 "parser.yy"
                                               {
          CALL((yylsp[-4]), (yylsp[0]), procBegin((yyvsp[-3].string)));
        }
#line 8056 "parser.tab.c"
    break;

  case 480: /* OldProcDecl: T_PROCESS Id OldProcParams error '{' $@40 OldProcBody '}'  */
#line 1505 "parser.yy"
                        {
          CALL((yylsp[-2]), (yylsp[-1]), procEnd());
        }
#line 8064 "parser.tab.c"
    break;

  case 481: /* $@41: %empty  */
#line 1508 "parser.yy"
                                 {
          CALL((yylsp[-3]), (yylsp[0]), procBegin((yyvsp[-2].string)));
        }
#line 8072 "parser.tab.c"
    break;

  case 482: /* OldProcDecl: T_PROCESS Id error '{' $@41 OldProcBody '}'  */
#line 1511 "parser.yy"
                        {
          CALL((yylsp[-2]), (yylsp[-1]), procEnd());
        }
#line 8080 "parser.tab.c"
    break;

  case 483: /* $@42: %empty  */
#line 1514 "parser.yy"
                              {
          CALL((yylsp[-2]), (yylsp[0]), procBegin("_"));
        }
#line 8088 "parser.tab.c"
    break;

  case 484: /* OldProcDecl: T_PROCESS error '{' $@42 OldProcBody '}'  */
#line 1517 "parser.yy"
                        {
          CALL((yylsp[-2]), (yylsp[-1]), procEnd());
        }
#line 8096 "parser.tab.c"
    break;

  case 485: /* $@43: %empty  */
#line 1520 "parser.yy"
                           {
          CALL((yylsp[-2]), (yylsp[0]), procBegin((yyvsp[-1].string)));
        }
#line 8104 "parser.tab.c"
    break;

  case 486: /* OldProcDecl: T_PROCESS Id '{' $@43 OldProcBody '}'  */
#line 1523 "parser.yy"
                        {
          CALL((yylsp[-2]), (yylsp[-1]), procEnd());
        }
#line 8112 "parser.tab.c"
    break;

  case 490: /* OldProcParamList: OldProcParam  */
#line 1535 "parser.yy"
                     {
          CALL((yylsp[0]), (yylsp[0]), typePop());
        }
#line 8120 "parser.tab.c"
    break;

  case 492: /* OldProcParamList: OldProcParamList ';' OldProcParam  */
#line 1539 "parser.yy"
                                            {
          CALL((yylsp[-2]), (yylsp[0]), typePop());
        }
#line 8128 "parser.tab.c"
    break;

  case 494: /* $@44: %empty  */
#line 1546 "parser.yy"
             {
            CALL((yylsp[0]), (yylsp[0]), typeDuplicate());
        }
#line 8136 "parser.tab.c"
    break;

  case 495: /* OldProcParam: Type $@44 NonTypeId ArrayDecl  */
#line 1548 "parser.yy"
                              {
            CALL((yylsp[-3]), (yylsp[0]), declParameter((yyvsp[-1].string), true));
        }
#line 8144 "parser.tab.c"
    break;

  case 496: /* $@45: %empty  */
#line 1551 "parser.yy"
                       {
            CALL((yylsp[0]), (yylsp[0]), typeDuplicate());
        }
#line 8152 "parser.tab.c"
    break;

  case 497: /* OldProcParam: OldProcParam $@45 ',' NonTypeId ArrayDecl  */
#line 1553 "parser.yy"
                                  {
            CALL((yylsp[-4]), (yylsp[0]), declParameter((yyvsp[-1].string), true));
        }
#line 8160 "parser.tab.c"
    break;

  case 498: /* $@46: %empty  */
#line 1559 "parser.yy"
                   {
            CALL((yylsp[0]), (yylsp[0]), typeInt(ParserBuilder::PREFIX_CONST));
        }
#line 8168 "parser.tab.c"
    break;

  case 499: /* OldProcConstParam: T_OLDCONST $@46 NonTypeId ArrayDecl  */
#line 1561 "parser.yy"
                              {
            CALL((yylsp[-1]), (yylsp[0]), declParameter((yyvsp[-1].string), false));
        }
#line 8176 "parser.tab.c"
    break;

  case 500: /* $@47: %empty  */
#line 1564 "parser.yy"
                                {
            CALL((yylsp[-1]), (yylsp[-1]), typeInt(ParserBuilder::PREFIX_CONST));
        }
#line 8184 "parser.tab.c"
    break;

  case 501: /* OldProcConstParam: OldProcConstParam ',' $@47 NonTypeId ArrayDecl  */
#line 1566 "parser.yy"
                              {
            CALL((yylsp[-1]), (yylsp[0]), declParameter((yyvsp[-1].string), false));
        }
#line 8192 "parser.tab.c"
    break;

  case 509: /* OldStateDecl: NonTypeId  */
#line 1591 "parser.yy"
                  {
	    CALL((yylsp[0]), (yylsp[0]), procState((yyvsp[0].string), false, false));
        }
#line 8200 "parser.tab.c"
    break;

  case 510: /* OldStateDecl: NonTypeId '{' OldInvariant '}'  */
#line 1594 "parser.yy"
                                         {
	    CALL((yylsp[-3]), (yylsp[0]), procState((yyvsp[-3].string), true, false));
        }
#line 8208 "parser.tab.c"
    break;

  case 512: /* OldInvariant: Expression error ','  */
#line 1601 "parser.yy"
                               {
        }
#line 8215 "parser.tab.c"
    break;

  case 513: /* OldInvariant: OldInvariant ',' Expression  */
#line 1603 "parser.yy"
                                      {
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(AND));
        }
#line 8223 "parser.tab.c"
    break;

  case 519: /* $@48: %empty  */
#line 1620 "parser.yy"
                                        {
            CALL((yylsp[-3]), (yylsp[-1]), procEdgeBegin((yyvsp[-3].string), (yyvsp[-1].string), true));
        }
#line 8231 "parser.tab.c"
    break;

  case 520: /* OldTransition: NonTypeId T_ARROW NonTypeId '{' $@48 OldGuard Sync Assign '}'  */
#line 1622 "parser.yy"
                                   {
            strcpy(rootTransId, (yyvsp[-8].string));
            CALL((yylsp[-8]), (yylsp[-1]), procEdgeEnd((yyvsp[-8].string), (yyvsp[-6].string)));
        }
#line 8240 "parser.tab.c"
    break;

  case 521: /* $@49: %empty  */
#line 1630 "parser.yy"
                              {
            CALL((yylsp[-2]), (yylsp[-1]), procEdgeBegin(rootTransId, (yyvsp[-1].string), true));
        }
#line 8248 "parser.tab.c"
    break;

  case 522: /* OldTransitionOpt: T_ARROW NonTypeId '{' $@49 OldGuard Sync Assign '}'  */
#line 1632 "parser.yy"
                                   {
            CALL((yylsp[-7]), (yylsp[-1]), procEdgeEnd(rootTransId, (yyvsp[-6].string)));
        }
#line 8256 "parser.tab.c"
    break;

  case 525: /* OldGuard: T_GUARD OldGuardList ';'  */
#line 1640 "parser.yy"
                                   {
          CALL((yylsp[-1]), (yylsp[-1]), procGuard());
        }
#line 8264 "parser.tab.c"
    break;

  case 526: /* OldGuard: T_GUARD OldGuardList error ';'  */
#line 1643 "parser.yy"
                                         {
          CALL((yylsp[-2]), (yylsp[-1]), procGuard());
        }
#line 8272 "parser.tab.c"
    break;

  case 528: /* OldGuardList: OldGuardList ',' Expression  */
#line 1650 "parser.yy"
                                      {
          CALL((yylsp[-2]), (yylsp[0]), exprBinary(AND));
        }
#line 8280 "parser.tab.c"
    break;

  case 538: /* SubProperty: T_AF Expression  */
#line 1677 "parser.yy"
                        {
	    CALL((yylsp[-1]), (yylsp[0]), exprUnary(AF));
	}
#line 8288 "parser.tab.c"
    break;

  case 539: /* SubProperty: T_AG '(' Expression BoolOrKWAnd T_AF Expression ')'  */
#line 1680 "parser.yy"
                                                              {
            CALL((yylsp[-2]), (yylsp[-1]), exprUnary(AF));
            CALL((yylsp[-4]), (yylsp[-1]), exprBinary(AND));
            CALL((yylsp[-6]), (yylsp[0]), exprUnary(AG));
        }
#line 8298 "parser.tab.c"
    break;

  case 540: /* SubProperty: T_AG Expression  */
#line 1685 "parser.yy"
                          {
	    CALL((yylsp[-1]), (yylsp[0]), exprUnary(AG));
        }
#line 8306 "parser.tab.c"
    break;

  case 541: /* SubProperty: T_EF Expression  */
#line 1688 "parser.yy"
                          {
	    CALL((yylsp[-1]), (yylsp[0]), exprUnary(EF));
        }
#line 8314 "parser.tab.c"
    break;

  case 542: /* SubProperty: T_EG Expression  */
#line 1691 "parser.yy"
                          {
	    CALL((yylsp[-1]), (yylsp[0]), exprUnary(EG));
        }
#line 8322 "parser.tab.c"
    break;

  case 543: /* SubProperty: Expression T_LEADSTO Expression  */
#line 1694 "parser.yy"
                                          {
	    CALL((yylsp[-2]), (yylsp[0]), exprBinary(LEADSTO));
        }
#line 8330 "parser.tab.c"
    break;

  case 544: /* SubProperty: 'A' '[' Expression 'U' Expression ']'  */
#line 1697 "parser.yy"
                                                {
	    CALL((yylsp[-5]), (yylsp[0]), exprBinary(A_UNTIL));
        }
#line 8338 "parser.tab.c"
    break;

  case 545: /* SubProperty: 'A' '[' Expression 'W' Expression ']'  */
#line 1700 "parser.yy"
                                                {
	    CALL((yylsp[-5]), (yylsp[0]), exprBinary(A_WEAKUNTIL));
        }
#line 8346 "parser.tab.c"
    break;

  case 546: /* PropertyExpr: SubProperty  */
#line 1706 "parser.yy"
                {
        CALL((yylsp[0]), (yylsp[0]), property());
	}
#line 8354 "parser.tab.c"
    break;

  case 547: /* PropertyExpr: T_AG_MULT Expression  */
#line 1709 "parser.yy"
                           {
	    CALL((yylsp[-1]), (yylsp[0]), exprUnary(AG_R_Piotr));
            CALL((yylsp[-1]), (yylsp[0]), property());
    }
#line 8363 "parser.tab.c"
    break;

  case 548: /* PropertyExpr: T_EF_MULT Expression  */
#line 1713 "parser.yy"
                               {
	    CALL((yylsp[-1]), (yylsp[0]), exprUnary(EF_R_Piotr));
        CALL((yylsp[-1]), (yylsp[0]), property());
    }
#line 8372 "parser.tab.c"
    break;

  case 549: /* PropertyExpr: T_PMAX Expression  */
#line 1717 "parser.yy"
                            {
        // Deprecated, comes from old uppaal-prob.
	    CALL((yylsp[-1]), (yylsp[0]), exprUnary(PMAX));
        CALL((yylsp[-1]), (yylsp[0]), property());
	}
#line 8382 "parser.tab.c"
    break;

  case 550: /* PropertyExpr: T_CONTROL ':' SubProperty  */
#line 1722 "parser.yy"
                                {
        CALL((yylsp[-2]), (yylsp[0]), exprUnary(CONTROL));
        CALL((yylsp[-2]), (yylsp[0]), property());
    }
#line 8391 "parser.tab.c"
    break;

  case 551: /* PropertyExpr: T_CONTROL '[' BoundType ']' ':' SubProperty  */
#line 1726 "parser.yy"
                                                  {
	    CALL((yylsp[-5]), (yylsp[0]), exprSMCControl());
	    CALL((yylsp[-5]), (yylsp[0]), property());
	}
#line 8400 "parser.tab.c"
    break;

  case 552: /* PropertyExpr: T_CONTROL_T T_MULT '(' Expression ',' Expression ')' ':' SubProperty  */
#line 1730 "parser.yy"
                                                                           {
	    CALL((yylsp[-8]), (yylsp[0]), exprTernary(CONTROL_TOPT));
	    CALL((yylsp[-8]), (yylsp[0]), property());
	}
#line 8409 "parser.tab.c"
    break;

  case 553: /* PropertyExpr: T_CONTROL_T T_MULT '(' Expression ')' ':' SubProperty  */
#line 1734 "parser.yy"
                                                            {
	    CALL((yylsp[-6]), (yylsp[0]), exprBinary(CONTROL_TOPT_DEF1));
	    CALL((yylsp[-6]), (yylsp[0]), property());
	}
#line 8418 "parser.tab.c"
    break;

  case 554: /* PropertyExpr: T_CONTROL_T T_MULT ':' SubProperty  */
#line 1738 "parser.yy"
                                         {
	    CALL((yylsp[-3]), (yylsp[0]), exprUnary(CONTROL_TOPT_DEF2));
	    CALL((yylsp[-3]), (yylsp[0]), property());
	}
#line 8427 "parser.tab.c"
    break;

  case 555: /* PropertyExpr: T_EF T_CONTROL ':' SubProperty  */
#line 1742 "parser.yy"
                                     {
	    CALL((yylsp[-3]), (yylsp[0]), exprUnary(EF_CONTROL));
	    CALL((yylsp[-3]), (yylsp[0]), property());
	}
#line 8436 "parser.tab.c"
    break;

  case 556: /* PropertyExpr: BracketExprList T_CONTROL ':' SubProperty  */
#line 1746 "parser.yy"
                                                {
        CALL((yylsp[-3]), (yylsp[0]), exprBinary(PO_CONTROL));
	    CALL((yylsp[-3]), (yylsp[0]), property());
    }
#line 8445 "parser.tab.c"
    break;

  case 557: /* PropertyExpr: T_SIMULATION ':' SysComposition RestrictionList T_LEQ SysComposition  */
#line 1750 "parser.yy"
                                                                           {
	    CALL((yylsp[-3]), (yylsp[0]), exprBinary(SIMULATION_LE));
	    CALL((yylsp[-5]), (yylsp[0]), property());
	}
#line 8454 "parser.tab.c"
    break;

  case 558: /* PropertyExpr: T_SIMULATION ':' SysComposition T_GEQ SysComposition RestrictionList  */
#line 1754 "parser.yy"
                                                                           {
	    CALL((yylsp[-3]), (yylsp[0]), exprBinary(SIMULATION_GE));
	    CALL((yylsp[-5]), (yylsp[0]), property());
	}
#line 8463 "parser.tab.c"
    break;

  case 559: /* PropertyExpr: T_REFINEMENT ':' TIOSystem T_LEQ TIOSystem  */
#line 1758 "parser.yy"
                                                 {
	    CALL((yylsp[-2]), (yylsp[0]), exprBinary(REFINEMENT_LE));
	    CALL((yylsp[-4]), (yylsp[0]), property());
	}
#line 8472 "parser.tab.c"
    break;

  case 560: /* PropertyExpr: T_REFINEMENT ':' TIOSystem T_GEQ TIOSystem  */
#line 1762 "parser.yy"
                                                 {
	    CALL((yylsp[-2]), (yylsp[0]), exprBinary(REFINEMENT_GE));
	    CALL((yylsp[-4]), (yylsp[0]), property());
	}
#line 8481 "parser.tab.c"
    break;

  case 561: /* PropertyExpr: T_CONSISTENCY ':' TIOSystem  */
#line 1766 "parser.yy"
                                  {
	    CALL((yylsp[-2]), (yylsp[0]), property());
	}
#line 8489 "parser.tab.c"
    break;

  case 562: /* PropertyExpr: T_SPECIFICATION ':' TIOSystem  */
#line 1769 "parser.yy"
                                    {
	    CALL((yylsp[-2]), (yylsp[0]), exprUnary(SPECIFICATION));
	    CALL((yylsp[-2]), (yylsp[0]), property());
	}
#line 8498 "parser.tab.c"
    break;

  case 563: /* PropertyExpr: T_IMPLEMENTATION ':' TIOSystem  */
#line 1773 "parser.yy"
                                     {
	    CALL((yylsp[-2]), (yylsp[0]), exprUnary(IMPLEMENTATION));
	    CALL((yylsp[-2]), (yylsp[0]), property());
	}
#line 8507 "parser.tab.c"
    break;

  case 564: /* PropertyExpr: T_SCENARIO ':' NonTypeId  */
#line 1777 "parser.yy"
                                   {
        CALL((yylsp[-2]), (yylsp[0]), scenario((yyvsp[0].string))); //check if all instances in the scenario
                                        //correspond to TA processes in the system
        CALL((yylsp[-2]), (yylsp[0]), exprScenario((yyvsp[0].string)));
        CALL((yylsp[-2]), (yylsp[0]), property());
    }
#line 8518 "parser.tab.c"
    break;

  case 565: /* PropertyExpr: T_PROBA SMCBounds '(' PathType Expression ')' CmpGLE T_FLOATING  */
#line 1783 "parser.yy"
                                                                      {
	    CALL((yylsp[-7]), (yylsp[0]), exprProbaQualitative((yyvsp[-4].kind), (yyvsp[-1].kind), (yyvsp[0].floating)));
	    CALL((yylsp[-7]), (yylsp[0]), property());
	}
#line 8527 "parser.tab.c"
    break;

  case 566: /* PropertyExpr: T_PROBA SMCBounds '(' PathType Expression ')'  */
#line 1787 "parser.yy"
                                                    {
        CALL((yylsp[0]), (yylsp[0]), exprTrue()); // push a trivial stop-predicate (see next rule)
        CALL((yylsp[-5]), (yylsp[0]), exprProbaQuantitative((yyvsp[-2].kind)));
	    CALL((yylsp[-5]), (yylsp[0]), property());
	}
#line 8537 "parser.tab.c"
    break;

  case 567: /* PropertyExpr: T_PROBA SMCBounds '(' Expression 'U' Expression ')'  */
#line 1792 "parser.yy"
                                                          {
	    CALL((yylsp[-6]), (yylsp[0]), exprProbaQuantitative(DIAMOND));
	    CALL((yylsp[-6]), (yylsp[0]), property());
    }
#line 8546 "parser.tab.c"
    break;

  case 568: /* PropertyExpr: T_PROBA SMCBounds '(' PathType Expression ')' T_GEQ T_PROBA SMCBounds '(' PathType Expression ')'  */
#line 1797 "parser.yy"
                                                    {
	    CALL((yylsp[-12]), (yylsp[0]), exprProbaCompare((yyvsp[-9].kind), (yyvsp[-2].kind)));
	    CALL((yylsp[-12]), (yylsp[0]), property());
	}
#line 8555 "parser.tab.c"
    break;

  case 569: /* PropertyExpr: T_SIMULATE SMCBounds '{' NonEmptyExpressionList '}'  */
#line 1801 "parser.yy"
                                                          {
	    CALL((yylsp[-4]), (yylsp[0]), exprSimulate((yyvsp[-1].number)));
	    CALL((yylsp[-4]), (yylsp[0]), property());
	}
#line 8564 "parser.tab.c"
    break;

  case 570: /* PropertyExpr: T_SIMULATE SMCBounds '{' NonEmptyExpressionList '}' ':' Expression  */
#line 1805 "parser.yy"
                                                                         {
	    CALL((yylsp[-6]), (yylsp[0]), exprSimulate((yyvsp[-3].number), true));
	    CALL((yylsp[-6]), (yylsp[0]), property());
	}
#line 8573 "parser.tab.c"
    break;

  case 571: /* PropertyExpr: T_SIMULATE SMCBounds '{' NonEmptyExpressionList '}' ':' T_NAT ':' Expression  */
#line 1809 "parser.yy"
                                                                                   {
        CALL((yylsp[-8]), (yylsp[0]), exprSimulate((yyvsp[-5].number), true, (yyvsp[-2].number)));
	    CALL((yylsp[-8]), (yylsp[0]), property());
	}
#line 8582 "parser.tab.c"
    break;

  case 572: /* PropertyExpr: 'E' SMCBounds '(' Id ':' Expression ')'  */
#line 1813 "parser.yy"
                                              {
	    CALL((yylsp[-6]), (yylsp[0]), exprProbaExpected((yyvsp[-3].string)));
	    CALL((yylsp[-6]), (yylsp[0]), property());
    }
#line 8591 "parser.tab.c"
    break;

  case 573: /* PropertyExpr: T_PROBA Expression  */
#line 1817 "parser.yy"
                         {
	    CALL((yylsp[-1]),(yylsp[0]), exprMitlFormula());
	    CALL((yylsp[-1]),(yylsp[0]), property());
    }
#line 8600 "parser.tab.c"
    break;

  case 574: /* MITLExpression: '(' Expression 'U' '[' T_NAT ',' T_NAT ']' Expression ')'  */
#line 1824 "parser.yy"
                                                                   {
	    CALL((yylsp[-9]),(yylsp[0]), exprMitlUntil((yyvsp[-5].number),(yyvsp[-3].number)));
        }
#line 8608 "parser.tab.c"
    break;

  case 575: /* MITLExpression: '(' Expression 'R' '[' T_NAT ',' T_NAT ']' Expression ')'  */
#line 1827 "parser.yy"
                                                                     {
	    CALL((yylsp[-9]),(yylsp[0]), exprMitlRelease((yyvsp[-5].number),(yyvsp[-3].number)));
        }
#line 8616 "parser.tab.c"
    break;

  case 576: /* MITLExpression: '(' T_MITL_NEXT Expression ')'  */
#line 1830 "parser.yy"
                                         {
	    CALL((yylsp[-3]),(yylsp[0]), exprMitlNext());
        }
#line 8624 "parser.tab.c"
    break;

  case 577: /* MITLExpression: '(' T_DIAMOND '[' T_NAT ',' T_NAT ']' Expression ')'  */
#line 1833 "parser.yy"
                                                               {
	    CALL((yylsp[-8]),(yylsp[-5]), exprMitlDiamond((yyvsp[-5].number),(yyvsp[-3].number)));
        }
#line 8632 "parser.tab.c"
    break;

  case 578: /* MITLExpression: '(' T_BOX '[' T_NAT ',' T_NAT ']' Expression ')'  */
#line 1836 "parser.yy"
                                                           {
	    CALL((yylsp[-8]),(yylsp[-5]), exprMitlBox((yyvsp[-5].number),(yyvsp[-3].number)));
        }
#line 8640 "parser.tab.c"
    break;

  case 579: /* SMCBounds: '[' BoundType ']'  */
#line 1842 "parser.yy"
                          {
			CALL((yylsp[-2]), (yylsp[-2]), exprNat(-1));
		}
#line 8648 "parser.tab.c"
    break;

  case 580: /* SMCBounds: '[' BoundType ';' T_NAT ']'  */
#line 1845 "parser.yy"
                                      {
			CALL((yylsp[-4]), (yylsp[-2]), exprNat((yyvsp[-1].number)));
		}
#line 8656 "parser.tab.c"
    break;

  case 581: /* $@50: %empty  */
#line 1850 "parser.yy"
                       { CALL((yylsp[-1]), (yylsp[0]), exprNat(0)); }
#line 8662 "parser.tab.c"
    break;

  case 583: /* $@51: %empty  */
#line 1851 "parser.yy"
                { CALL((yylsp[0]), (yylsp[0]), exprNat(1)); }
#line 8668 "parser.tab.c"
    break;

  case 586: /* CmpGLE: T_GEQ  */
#line 1856 "parser.yy"
              { (yyval.kind) = GE; }
#line 8674 "parser.tab.c"
    break;

  case 587: /* CmpGLE: T_LEQ  */
#line 1857 "parser.yy"
                { (yyval.kind) = LE; }
#line 8680 "parser.tab.c"
    break;

  case 588: /* PathType: T_BOX  */
#line 1861 "parser.yy"
                  { (yyval.kind) = BOX; }
#line 8686 "parser.tab.c"
    break;

  case 589: /* PathType: T_DIAMOND  */
#line 1862 "parser.yy"
                        { (yyval.kind) = DIAMOND; }
#line 8692 "parser.tab.c"
    break;

  case 590: /* TIOSystem: IdExpr  */
#line 1866 "parser.yy"
               {
	    CALL((yylsp[0]), (yylsp[0]), exprTrue());
	    CALL((yylsp[0]), (yylsp[0]), exprUnary(AG));
            CALL((yylsp[0]), (yylsp[0]), exprBinary(CONSISTENCY));
	}
#line 8702 "parser.tab.c"
    break;

  case 591: /* TIOSystem: '(' TIOSystem TIOOptionalProperty ')'  */
#line 1871 "parser.yy"
                                                {
	    CALL((yylsp[-2]), (yylsp[-1]), exprBinary(CONSISTENCY));
	}
#line 8710 "parser.tab.c"
    break;

  case 592: /* TIOSystem: '(' TIOStructComposition TIOOptionalProperty ')'  */
#line 1874 "parser.yy"
                                                           {
	    CALL((yylsp[-2]), (yylsp[-2]), exprBinary(CONSISTENCY));
        }
#line 8718 "parser.tab.c"
    break;

  case 593: /* TIOSystem: '(' TIOComposition TIOOptionalProperty ')'  */
#line 1877 "parser.yy"
                                                     {
	    CALL((yylsp[-2]), (yylsp[-1]), exprBinary(CONSISTENCY));
	}
#line 8726 "parser.tab.c"
    break;

  case 594: /* TIOSystem: '(' TIOConjunction TIOOptionalProperty ')'  */
#line 1880 "parser.yy"
                                                      {
	    CALL((yylsp[-2]), (yylsp[-1]), exprBinary(CONSISTENCY));
	}
#line 8734 "parser.tab.c"
    break;

  case 595: /* TIOSystem: '(' TIOQuotient TIOOptionalProperty ')'  */
#line 1883 "parser.yy"
                                                   {
	    CALL((yylsp[-2]), (yylsp[-1]), exprBinary(CONSISTENCY));
	}
#line 8742 "parser.tab.c"
    break;

  case 596: /* IdExpr: NonTypeId  */
#line 1889 "parser.yy"
                  {
            CALL((yylsp[0]), (yylsp[0]), exprId((yyvsp[0].string)));
	}
#line 8750 "parser.tab.c"
    break;

  case 597: /* TIOStructComposition: TIOStructCompositionList  */
#line 1895 "parser.yy"
                                 {
	    CALL((yylsp[0]), (yylsp[0]), exprNary(SYNTAX_COMPOSITION, (yyvsp[0].number)));
	}
#line 8758 "parser.tab.c"
    break;

  case 598: /* TIOComposition: TIOCompositionList  */
#line 1901 "parser.yy"
                           {
	    CALL((yylsp[0]), (yylsp[0]), exprNary(TIOCOMPOSITION, (yyvsp[0].number)));
	}
#line 8766 "parser.tab.c"
    break;

  case 599: /* TIOConjunction: TIOConjunctionList  */
#line 1907 "parser.yy"
                           {
	    CALL((yylsp[0]), (yylsp[0]), exprNary(TIOCONJUNCTION, (yyvsp[0].number)));
	}
#line 8774 "parser.tab.c"
    break;

  case 600: /* TIOQuotient: TIOSystem '\\' TIOSystem  */
#line 1913 "parser.yy"
                                 {
	    CALL((yylsp[-2]), (yylsp[0]), exprBinary(TIOQUOTIENT));
	}
#line 8782 "parser.tab.c"
    break;

  case 601: /* TIOStructCompositionList: IdExpr T_PLUS IdExpr  */
#line 1919 "parser.yy"
                             { (yyval.number) = 2; }
#line 8788 "parser.tab.c"
    break;

  case 602: /* TIOStructCompositionList: TIOStructCompositionList T_PLUS IdExpr  */
#line 1920 "parser.yy"
                                                 { (yyval.number) = (yyvsp[-2].number) + 1; }
#line 8794 "parser.tab.c"
    break;

  case 603: /* TIOCompositionList: TIOSystem T_BOOL_OR TIOSystem  */
#line 1924 "parser.yy"
                                      { (yyval.number) = 2; }
#line 8800 "parser.tab.c"
    break;

  case 604: /* TIOCompositionList: TIOCompositionList T_BOOL_OR TIOSystem  */
#line 1925 "parser.yy"
                                                 { (yyval.number) = (yyvsp[-2].number) + 1; }
#line 8806 "parser.tab.c"
    break;

  case 605: /* TIOConjunctionList: TIOSystem T_BOOL_AND TIOSystem  */
#line 1929 "parser.yy"
                                       { (yyval.number) = 2; }
#line 8812 "parser.tab.c"
    break;

  case 606: /* TIOConjunctionList: TIOConjunctionList T_BOOL_AND TIOSystem  */
#line 1930 "parser.yy"
                                                  { (yyval.number) = (yyvsp[-2].number) + 1; }
#line 8818 "parser.tab.c"
    break;

  case 607: /* TIOOptionalProperty: %empty  */
#line 1934 "parser.yy"
                      {
            CALL((yylsp[0]), (yylsp[0]), exprTrue());
	    CALL((yylsp[0]), (yylsp[0]), exprUnary(AG));
        }
#line 8827 "parser.tab.c"
    break;

  case 609: /* RestrictionList: %empty  */
#line 1943 "parser.yy"
                      {
            CALL((yylsp[0]), (yylsp[0]), exprNary(LIST,0));
	    CALL((yylsp[0]), (yylsp[0]), exprBinary(RESTRICT));
        }
#line 8836 "parser.tab.c"
    break;

  case 610: /* RestrictionList: '\\' '{' ExpressionList '}'  */
#line 1947 "parser.yy"
                                      {
	    CALL((yylsp[-3]), (yylsp[0]), exprNary(LIST,(yyvsp[-1].number)));
	    CALL((yylsp[-3]), (yylsp[0]), exprBinary(RESTRICT));
	}
#line 8845 "parser.tab.c"
    break;

  case 611: /* SysComposition: NonTypeId  */
#line 1954 "parser.yy"
                  {
	    CALL((yylsp[0]), (yylsp[0]), exprId((yyvsp[0].string)));
	    CALL((yylsp[0]), (yylsp[0]), exprNary(LIST,1));
	}
#line 8854 "parser.tab.c"
    break;

  case 612: /* SysComposition: '(' DeclComposition ')'  */
#line 1958 "parser.yy"
                                  {
	    CALL((yylsp[-2]), (yylsp[0]), exprNary(LIST,(yyvsp[-1].number)));
	}
#line 8862 "parser.tab.c"
    break;

  case 613: /* DeclComposition: NonTypeId  */
#line 1963 "parser.yy"
                  {
	    CALL((yylsp[0]), (yylsp[0]), exprId((yyvsp[0].string)));
	    (yyval.number) = 1;
	}
#line 8871 "parser.tab.c"
    break;

  case 614: /* DeclComposition: DeclComposition T_BOOL_OR NonTypeId  */
#line 1967 "parser.yy"
                                              {
	    CALL((yylsp[-2]), (yylsp[0]), exprId((yyvsp[0].string)));
	    (yyval.number) = (yyvsp[-2].number) + 1;
	}
#line 8880 "parser.tab.c"
    break;

  case 615: /* BracketExprList: '{' ExpressionList '}'  */
#line 1973 "parser.yy"
                               {
	    CALL((yylsp[-2]), (yylsp[0]), exprNary(LIST,(yyvsp[-1].number)));
	}
#line 8888 "parser.tab.c"
    break;

  case 616: /* ExpressionList: %empty  */
#line 1982 "parser.yy"
                      { (yyval.number) = 0; }
#line 8894 "parser.tab.c"
    break;

  case 618: /* NonEmptyExpressionList: Expression  */
#line 1987 "parser.yy"
                   { (yyval.number) = 1; }
#line 8900 "parser.tab.c"
    break;

  case 619: /* NonEmptyExpressionList: NonEmptyExpressionList ',' Expression  */
#line 1988 "parser.yy"
                                                { (yyval.number) = (yyvsp[-2].number)+1; }
#line 8906 "parser.tab.c"
    break;

  case 620: /* SupPrefix: T_SUP ':'  */
#line 1992 "parser.yy"
                  {
	    CALL((yylsp[-1]), (yylsp[0]), exprTrue());
	}
#line 8914 "parser.tab.c"
    break;

  case 622: /* InfPrefix: T_INF ':'  */
#line 1999 "parser.yy"
                  {
	    CALL((yylsp[-1]), (yylsp[0]), exprTrue());
	}
#line 8922 "parser.tab.c"
    break;

  case 626: /* Property: SupPrefix NonEmptyExpressionList  */
#line 2008 "parser.yy"
                                           {
	    CALL((yylsp[-1]), (yylsp[0]), exprNary(LIST,(yyvsp[0].number)));
            CALL((yylsp[-1]), (yylsp[0]), exprBinary(SUP_VAR));
	    CALL((yylsp[-1]), (yylsp[0]), property());
        }
#line 8932 "parser.tab.c"
    break;

  case 627: /* Property: InfPrefix NonEmptyExpressionList  */
#line 2013 "parser.yy"
                                           {
	    CALL((yylsp[-1]), (yylsp[0]), exprNary(LIST,(yyvsp[0].number)));
            CALL((yylsp[-1]), (yylsp[0]), exprBinary(INF_VAR));
	    CALL((yylsp[-1]), (yylsp[0]), property());
        }
#line 8942 "parser.tab.c"
    break;


#line 8946 "parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

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


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 2019 "parser.yy"



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
        	 bool newxta, xta_part_t part, const std::string& xpath)
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

int32_t parseProperty(const char *str, ParserBuilder *aParserBuilder,
		      const std::string& xpath)
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
