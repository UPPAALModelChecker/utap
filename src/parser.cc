/* A Bison parser, made from parser.yy
   by GNU bison 1.35.  */

#define YYBISON 1  /* Identify Bison output.  */

#define yyparse utap_parse
#define yylex utap_lex
#define yyerror utap_error
#define yylval utap_lval
#define yychar utap_char
#define yydebug utap_debug
#define yynerrs utap_nerrs
#define YYLSP_NEEDED 1

# define	T_ASSIGNMENT	257
# define	T_ASSPLUS	258
# define	T_ASSMINUS	259
# define	T_ASSMULT	260
# define	T_ASSDIV	261
# define	T_ASSMOD	262
# define	T_ASSOR	263
# define	T_ASSAND	264
# define	T_ASSXOR	265
# define	T_ASSLSHIFT	266
# define	T_ASSRSHIFT	267
# define	T_EXCLAM	268
# define	T_INCREMENT	269
# define	T_DECREMENT	270
# define	T_PLUS	271
# define	T_MINUS	272
# define	T_MULT	273
# define	T_DIV	274
# define	T_MIN	275
# define	T_MAX	276
# define	T_MOD	277
# define	T_OR	278
# define	T_XOR	279
# define	T_LSHIFT	280
# define	T_RSHIFT	281
# define	T_BOOL_AND	282
# define	T_BOOL_OR	283
# define	T_BOOL_NOT	284
# define	T_IMPLY	285
# define	T_LT	286
# define	T_LEQ	287
# define	T_EQ	288
# define	T_NEQ	289
# define	T_GEQ	290
# define	T_GT	291
# define	T_FOR	292
# define	T_WHILE	293
# define	T_DO	294
# define	T_BREAK	295
# define	T_CONTINUE	296
# define	T_SWITCH	297
# define	T_IF	298
# define	T_ELSE	299
# define	T_CASE	300
# define	T_DEFAULT	301
# define	T_RETURN	302
# define	T_TYPEDEF	303
# define	T_STRUCT	304
# define	T_CONST	305
# define	T_OLDCONST	306
# define	T_URGENT	307
# define	T_BROADCAST	308
# define	T_TRUE	309
# define	T_FALSE	310
# define	T_SYSTEM	311
# define	T_PROCESS	312
# define	T_STATE	313
# define	T_COMMIT	314
# define	T_INIT	315
# define	T_TRANS	316
# define	T_ARROW	317
# define	T_GUARD	318
# define	T_SYNC	319
# define	T_ASSIGN	320
# define	T_DEADLOCK	321
# define	T_EF	322
# define	T_EG	323
# define	T_AF	324
# define	T_AG	325
# define	T_LEADSTO	326
# define	T_QUIT	327
# define	T_ERROR	328
# define	T_ID	329
# define	T_TYPENAME	330
# define	T_NAT	331
# define	T_NEW	332
# define	T_NEW_DECLARATION	333
# define	T_NEW_LOCAL_DECL	334
# define	T_NEW_INST	335
# define	T_NEW_SYSTEM	336
# define	T_NEW_PARAMETERS	337
# define	T_NEW_INVARIANT	338
# define	T_NEW_GUARD	339
# define	T_NEW_SYNC	340
# define	T_NEW_ASSIGN	341
# define	T_OLD	342
# define	T_OLD_DECLARATION	343
# define	T_OLD_LOCAL_DECL	344
# define	T_OLD_INST	345
# define	T_OLD_PARAMETERS	346
# define	T_OLD_INVARIANT	347
# define	T_OLD_GUARD	348
# define	T_OLD_ASSIGN	349
# define	T_PROPERTY	350
# define	UOPERATOR	351

#line 53 "parser.yy"


#include "libparser.hh"

using namespace std;
using namespace UTAP;
using namespace Constants;

typedef struct position_t 
{
    int32_t first_line, first_column, last_line, last_column;
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
static const char* PE_BANG = "'!' expected";
static const char* PE_BANGQUE = "'!' or '?' expected";
static const char* PE_COLON = "':' expected";
static const char* PE_COMMA = "',' expected";
static const char* PE_CONST_EXP = "constant expression expected";
static const char* PE_CONSTID_ = "one more constant identifier expected";
static const char* PE_DECL_STAT = "variable declaration or statement expected";
static const char* PE_EXPR = "expression expected";
static const char* PE_EXPR_ = "one more expression expected";
static const char* PE_EXPR_SEMI = "expression or ';' expected";
static const char* PE_GUARD_EXP = "guard expression expected";
static const char* PE_GUARD_EXP_ = "one more guard expression expected";
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



#line 257 "parser.yy"
#ifndef YYSTYPE
typedef union {
  bool flag;
  int number;
  char string[MAXLEN];
} yystype;
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

#ifndef YYDEBUG
# define YYDEBUG 0
#endif



#define	YYFINAL		809
#define	YYFLAG		-32768
#define	YYNTBASE	111

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 351 ? yytranslate[x] : 233)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     110,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    99,     2,
     101,   102,     2,     2,   107,     2,   105,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    98,   106,
       2,     2,     2,    97,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   103,     2,   104,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   108,     2,   109,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,   100
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     3,     6,     9,    12,    15,    18,    21,    24,
      27,    30,    33,    36,    39,    42,    45,    48,    51,    54,
      57,    60,    64,    65,    66,    76,    85,    93,   100,   105,
     109,   114,   118,   120,   124,   128,   129,   132,   135,   138,
     141,   142,   148,   151,   155,   160,   164,   168,   171,   173,
     177,   181,   186,   190,   193,   197,   202,   206,   208,   212,
     216,   220,   221,   224,   227,   229,   233,   238,   242,   244,
     248,   252,   256,   260,   262,   263,   268,   274,   279,   284,
     288,   293,   299,   304,   308,   310,   314,   318,   321,   325,
     331,   337,   342,   346,   348,   350,   352,   355,   358,   362,
     367,   371,   374,   377,   379,   383,   387,   390,   391,   393,
     395,   398,   400,   401,   407,   414,   420,   426,   432,   433,
     440,   441,   449,   454,   458,   461,   462,   470,   478,   479,
     486,   492,   498,   499,   502,   505,   508,   512,   517,   521,
     525,   528,   531,   533,   537,   541,   543,   548,   554,   559,
     564,   568,   572,   577,   581,   584,   586,   587,   591,   596,
     600,   603,   605,   607,   611,   615,   624,   634,   640,   645,
     649,   657,   666,   671,   675,   677,   678,   682,   687,   691,
     692,   696,   701,   705,   709,   712,   716,   719,   723,   726,
     727,   731,   735,   736,   738,   740,   743,   747,   752,   756,
     760,   763,   767,   772,   776,   780,   783,   785,   789,   793,
     795,   799,   803,   804,   810,   811,   816,   817,   820,   823,
     824,   827,   829,   831,   834,   838,   839,   850,   851,   863,
     864,   876,   877,   884,   885,   893,   894,   902,   903,   912,
     913,   921,   924,   928,   931,   935,   936,   945,   946,   956,
     957,   967,   971,   975,   978,   981,   982,   983,   987,   988,
     992,   994,   997,   998,  1004,  1005,  1011,  1012,  1017,  1018,
    1024,  1025,  1027,  1029,  1033,  1037,  1039,  1041,  1043,  1045,
    1046,  1052,  1053,  1059,  1064,  1069,  1073,  1077,  1080,  1083,
    1086,  1089,  1093,  1097,  1100,  1104,  1108,  1112,  1116,  1120,
    1124,  1128,  1132,  1136,  1140,  1144,  1148,  1152,  1156,  1160,
    1164,  1168,  1172,  1176,  1180,  1184,  1188,  1192,  1196,  1200,
    1204,  1208,  1212,  1216,  1220,  1224,  1228,  1232,  1236,  1240,
    1244,  1250,  1256,  1261,  1265,  1269,  1271,  1272,  1277,  1281,
    1285,  1287,  1289,  1291,  1293,  1295,  1297,  1299,  1301,  1303,
    1305,  1307,  1309,  1311,  1313,  1314,  1316,  1320,  1324,  1328,
    1329,  1332,  1335,  1337,  1338,  1343,  1345,  1349,  1353,  1357,
    1360,  1361,  1369,  1370,  1379,  1380,  1388,  1389,  1396,  1397,
    1403,  1404,  1411,  1414,  1418,  1422,  1426,  1428,  1432,  1436,
    1440,  1444,  1449,  1455,  1456,  1459,  1463,  1468,  1472,  1476,
    1479,  1481,  1483,  1487,  1491,  1493,  1498,  1500,  1504,  1506,
    1510,  1514,  1515,  1519,  1524,  1528,  1532,  1535,  1537,  1539,
    1543,  1547,  1556,  1566,  1575,  1585,  1595,  1603,  1611,  1620,
    1629,  1638,  1646,  1648,  1649,  1653,  1658,  1662,  1665,  1667,
    1671,  1675,  1678,  1679,  1683,  1684,  1686,  1689,  1693,  1695,
    1697,  1699
};
static const short yyrhs[] =
{
      78,   112,     0,    79,   117,     0,    80,   148,     0,    81,
     113,     0,    82,   115,     0,    82,     1,     0,    83,   121,
       0,    84,   194,     0,    85,   194,     0,    86,   159,     0,
      87,   193,     0,    88,   201,     0,    89,   202,     0,    90,
     218,     0,    91,   113,     0,    92,   215,     0,    93,   222,
       0,    94,   228,     0,    95,   193,     0,    96,   229,     0,
     117,   113,   115,     0,     0,     0,   113,    75,     3,    75,
     101,   114,   200,   102,   106,     0,   113,    75,     3,    75,
     101,     1,   102,   106,     0,   113,    75,     3,    75,   101,
       1,   106,     0,   113,    75,     3,    75,     1,   106,     0,
     113,    75,     1,   106,     0,    57,   116,   106,     0,    57,
     116,     1,   106,     0,    57,     1,   106,     0,    75,     0,
     116,   107,    75,     0,   116,   107,     1,     0,     0,   117,
     118,     0,   117,   123,     0,   117,   131,     0,   117,   144,
       0,     0,   134,   135,   120,   119,   166,     0,   101,   102,
       0,   101,   121,   102,     0,   101,   121,     1,   102,     0,
     101,   121,     1,     0,   101,     1,   102,     0,   101,     1,
       0,   122,     0,   121,   107,   122,     0,   121,   107,     1,
       0,   134,    99,    75,   130,     0,   134,    75,   130,     0,
     134,     1,     0,   134,   124,   106,     0,   134,   124,     1,
     106,     0,   134,     1,   106,     0,   125,     0,   124,   107,
     125,     0,   124,   107,     1,     0,   135,   130,   126,     0,
       0,     3,   127,     0,     3,     1,     0,   194,     0,   108,
     128,   109,     0,   108,   128,     1,   109,     0,   108,     1,
     109,     0,   129,     0,   128,   107,   129,     0,   128,   107,
       1,     0,   135,    98,   127,     0,   135,    98,     1,     0,
     127,     0,     0,   130,   103,   194,   104,     0,   130,   103,
     194,     1,   104,     0,   130,   103,   194,     1,     0,   130,
     103,     1,   104,     0,   130,   103,     1,     0,    49,   134,
     132,   106,     0,    49,   134,   132,     1,   106,     0,    49,
     134,     1,   106,     0,    49,     1,   106,     0,   133,     0,
     132,   107,   133,     0,   132,   107,     1,     0,   135,   130,
       0,   140,    76,   141,     0,   140,    50,   108,   136,   109,
       0,   140,    50,   108,     1,   109,     0,   140,    50,   108,
       1,     0,   140,    50,     1,     0,    75,     0,    76,     0,
     137,     0,   136,   137,     0,   136,     1,     0,   134,   138,
     106,     0,   134,   138,     1,   106,     0,   134,     1,   106,
       0,   134,     1,     0,     1,   106,     0,   139,     0,   138,
     107,   139,     0,   138,   107,     1,     0,   135,   130,     0,
       0,    53,     0,    54,     0,    53,    54,     0,    51,     0,
       0,   103,   194,   107,   194,   104,     0,   103,   194,   107,
     194,     1,   104,     0,   103,   194,   107,   194,     1,     0,
     103,   194,   107,     1,   104,     0,   103,     1,   107,   194,
     104,     0,     0,   103,     1,   107,   142,     1,   104,     0,
       0,   103,   194,     1,   107,   143,   194,   104,     0,   103,
     194,     1,   104,     0,   103,   194,     1,     0,   103,     1,
       0,     0,    58,   135,   120,   108,   145,   147,   109,     0,
      58,   135,   120,     1,   108,   147,   109,     0,     0,    58,
     135,   108,   146,   147,   109,     0,    58,     1,   108,   147,
     109,     0,   148,   149,   161,   152,   153,     0,     0,   148,
     118,     0,   148,   123,     0,   148,   131,     0,    59,   150,
     106,     0,    59,   150,     1,   106,     0,    59,   150,     1,
       0,    59,     1,   106,     0,    59,     1,     0,     1,   106,
       0,   151,     0,   150,   107,   151,     0,   150,   107,     1,
       0,    75,     0,    75,   108,   194,   109,     0,    75,   108,
     194,     1,   109,     0,    75,   108,   194,     1,     0,    75,
     108,     1,   109,     0,    75,   108,     1,     0,    61,    75,
     106,     0,    61,    75,     1,   106,     0,    61,    75,     1,
       0,    61,     1,     0,     1,     0,     0,    62,   154,   106,
       0,    62,   154,     1,   106,     0,    62,   154,     1,     0,
      62,     1,     0,     1,     0,   155,     0,   154,   107,   156,
       0,   154,   107,     1,     0,    75,    63,    75,   108,   157,
     158,   160,   109,     0,    75,    63,    75,   108,   157,   158,
     160,     1,   106,     0,    75,    63,    75,     1,   109,     0,
      75,    63,     1,   109,     0,    75,     1,   109,     0,    63,
      75,   108,   157,   158,   160,   109,     0,    63,    75,   108,
     157,   158,   160,     1,   109,     0,    63,    75,     1,   109,
       0,    63,     1,   109,     0,   155,     0,     0,    64,   194,
     106,     0,    64,   194,     1,   106,     0,    64,     1,   106,
       0,     0,    65,   159,   106,     0,    65,   159,     1,   106,
       0,    65,   159,     1,     0,    65,     1,   106,     0,   194,
      14,     0,   194,     1,    14,     0,   194,    97,     0,   194,
       1,    97,     0,   194,     1,     0,     0,    66,   193,   106,
       0,    66,     1,   106,     0,     0,   162,     0,   163,     0,
     162,   163,     0,    60,   164,   106,     0,    60,   164,     1,
     106,     0,    60,   164,     1,     0,    60,     1,   106,     0,
      60,     1,     0,    53,   165,   106,     0,    53,   165,     1,
     106,     0,    53,   165,     1,     0,    53,     1,   106,     0,
      53,     1,     0,    75,     0,   164,   107,    75,     0,   164,
     107,     1,     0,    75,     0,   165,   107,    75,     0,   165,
     107,     1,     0,     0,   108,   167,   169,   170,   109,     0,
       0,   108,   168,     1,   109,     0,     0,   169,   123,     0,
     169,   131,     0,     0,   170,   171,     0,   166,     0,   106,
       0,   194,   106,     0,   194,     1,   106,     0,     0,    38,
     101,   172,   193,   106,   193,   106,   193,   102,   171,     0,
       0,    38,   101,     1,   173,   192,   106,   192,   106,   192,
     102,   171,     0,     0,    38,     1,   101,   174,   192,   106,
     192,   106,   192,   102,   171,     0,     0,    39,   101,   175,
     193,   102,   171,     0,     0,    39,     1,   101,   176,   193,
     102,   171,     0,     0,    39,   101,     1,   177,   193,   102,
     171,     0,     0,    40,   178,   171,    39,   101,   193,   102,
     106,     0,     0,    44,   101,   179,   193,   102,   171,   183,
       0,    41,   106,     0,    41,     1,   106,     0,    42,   106,
       0,    42,     1,   106,     0,     0,    43,   101,   193,   102,
     180,   108,   186,   109,     0,     0,    43,     1,   101,   193,
     102,   181,   108,   186,   109,     0,     0,    43,   101,     1,
     193,   102,   182,   108,   186,   109,     0,    48,   194,   106,
       0,    48,   194,     1,     0,    48,   106,     0,    48,     1,
       0,     0,     0,    45,   184,   171,     0,     0,    45,   185,
       1,     0,   187,     0,   186,   187,     0,     0,    46,   194,
      98,   188,   170,     0,     0,    46,     1,    98,   189,   170,
       0,     0,    47,    98,   190,   170,     0,     0,    47,     1,
      98,   191,   170,     0,     0,   193,     0,   194,     0,   193,
     107,   194,     0,   193,   107,     1,     0,    56,     0,    55,
       0,    77,     0,    75,     0,     0,    75,   101,   195,   200,
     102,     0,     0,    75,   101,   196,     1,   102,     0,   194,
     103,   194,   104,     0,   194,   103,     1,   104,     0,   101,
     194,   102,     0,   101,     1,   102,     0,   194,    15,     0,
      15,   194,     0,   194,    16,     0,    16,   194,     0,   194,
     198,   194,     0,   194,   198,     1,     0,   199,   194,     0,
     194,    32,   194,     0,   194,    32,     1,     0,   194,    33,
     194,     0,   194,    33,     1,     0,   194,    34,   194,     0,
     194,    34,     1,     0,   194,    35,   194,     0,   194,    35,
       1,     0,   194,    37,   194,     0,   194,    37,     1,     0,
     194,    36,   194,     0,   194,    36,     1,     0,   194,    17,
     194,     0,   194,    17,     1,     0,   194,    18,   194,     0,
     194,    18,     1,     0,   194,    19,   194,     0,   194,    19,
       1,     0,   194,    20,   194,     0,   194,    20,     1,     0,
     194,    23,   194,     0,   194,    23,     1,     0,   194,    99,
     194,     0,   194,    99,     1,     0,   194,    24,   194,     0,
     194,    24,     1,     0,   194,    25,   194,     0,   194,    25,
       1,     0,   194,    26,   194,     0,   194,    26,     1,     0,
     194,    27,   194,     0,   194,    27,     1,     0,   194,    28,
     194,     0,   194,    28,     1,     0,   194,    29,   194,     0,
     194,    29,     1,     0,   194,    97,   194,    98,   194,     0,
     194,    97,   194,    98,     1,     0,   194,    97,   194,     1,
       0,   194,   105,    75,     0,   194,   105,     1,     0,    67,
       0,     0,   194,    31,   197,   194,     0,   194,    21,   194,
       0,   194,    22,   194,     0,     3,     0,     4,     0,     5,
       0,     7,     0,     8,     0,     6,     0,    10,     0,     9,
       0,    11,     0,    12,     0,    13,     0,    18,     0,    14,
       0,    30,     0,     0,   194,     0,   200,   107,   194,     0,
     200,   107,     1,     0,   202,   113,   115,     0,     0,   202,
     203,     0,   202,   207,     0,   123,     0,     0,    52,   204,
     205,   106,     0,   206,     0,   205,   107,   206,     0,   205,
     107,     1,     0,    75,   130,   127,     0,    75,     1,     0,
       0,    58,   135,   214,   108,   208,   217,   109,     0,     0,
      58,   135,   214,     1,   108,   209,   217,   109,     0,     0,
      58,   135,     1,   108,   210,   217,   109,     0,     0,    58,
       1,   108,   211,   217,   109,     0,     0,     1,   108,   212,
     217,   109,     0,     0,    58,   135,   108,   213,   217,   109,
       0,   101,   102,     0,   101,   215,   102,     0,   101,   215,
       1,     0,   101,     1,   102,     0,   216,     0,   215,   106,
     216,     0,   215,   106,     1,     0,   134,    75,   130,     0,
      52,    75,   130,     0,   216,   107,    75,   130,     0,   218,
     219,   161,   152,   223,     0,     0,   218,   203,     0,    59,
     220,   106,     0,    59,   220,     1,   106,     0,    59,   220,
       1,     0,    59,     1,   106,     0,    59,     1,     0,     1,
       0,   221,     0,   220,   107,   221,     0,   220,   107,     1,
       0,    75,     0,    75,   108,   222,   109,     0,   194,     0,
     194,     1,   107,     0,     1,     0,   222,   107,   194,     0,
     222,   107,     1,     0,     0,    62,   224,   106,     0,    62,
     224,     1,   106,     0,    62,   224,     1,     0,    62,     1,
     106,     0,    62,     1,     0,     1,     0,   225,     0,   224,
     107,   226,     0,   224,   107,     1,     0,    75,    63,    75,
     108,   227,   158,   160,   109,     0,    75,    63,    75,   108,
     227,   158,   160,     1,   109,     0,    75,    63,    75,   108,
     227,   158,   160,     1,     0,    75,    63,    75,     1,   108,
     227,   158,   160,   109,     0,    75,     1,    63,    75,   108,
     227,   158,   160,   109,     0,    63,    75,   108,   227,   158,
     160,   109,     0,    63,    75,   108,   227,   158,   160,     1,
       0,    63,    75,   108,   227,   158,   160,     1,   109,     0,
      63,    75,     1,   108,   227,   158,   160,   109,     0,    63,
       1,    75,   108,   227,   158,   160,   109,     0,    63,     1,
     108,   227,   158,   160,   109,     0,   225,     0,     0,    64,
     228,   106,     0,    64,   228,     1,   106,     0,    64,   228,
       1,     0,    64,     1,     0,   194,     0,   228,   107,   194,
       0,   228,   107,     1,     0,   230,   231,     0,     0,   230,
     231,   110,     0,     0,    73,     0,   232,   194,     0,   194,
      72,   194,     0,    68,     0,    69,     0,    70,     0,    71,
       0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   268,   270,   271,   272,   273,   274,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   293,   297,   299,   299,   304,   307,   310,   313,   318,
     320,   323,   328,   330,   331,   336,   338,   339,   340,   341,
     344,   344,   353,   355,   356,   360,   364,   368,   379,   381,
     382,   388,   393,   397,   402,   406,   410,   416,   418,   419,
     424,   430,   432,   433,   439,   441,   444,   448,   454,   456,
     457,   463,   467,   470,   475,   477,   478,   482,   486,   490,
     496,   500,   504,   508,   519,   521,   522,   528,   534,   538,
     541,   545,   549,   554,   556,   559,   561,   562,   568,   573,
     578,   581,   584,   589,   591,   592,   598,   604,   606,   607,
     608,   609,   612,   614,   615,   619,   623,   628,   633,   633,
     643,   643,   650,   656,   662,   674,   674,   681,   684,   684,
     692,   701,   705,   707,   708,   709,   712,   714,   717,   720,
     723,   726,   731,   733,   734,   739,   744,   747,   751,   755,
     759,   765,   769,   773,   777,   780,   785,   787,   788,   791,
     794,   797,   802,   804,   805,   810,   815,   820,   823,   826,
     831,   835,   839,   842,   845,   849,   851,   854,   858,   863,
     865,   866,   869,   872,   877,   881,   885,   888,   892,   898,
     900,   903,   908,   910,   911,   912,   915,   917,   920,   923,
     926,   931,   933,   936,   939,   942,   947,   951,   954,   959,
     963,   966,   976,   976,   983,   983,   992,   994,   995,   998,
    1000,  1003,  1005,  1008,  1011,  1015,  1015,  1021,  1021,  1029,
    1029,  1037,  1037,  1043,  1043,  1050,  1050,  1057,  1057,  1063,
    1063,  1067,  1070,  1074,  1077,  1081,  1081,  1087,  1087,  1094,
    1094,  1101,  1104,  1108,  1111,  1117,  1121,  1121,  1127,  1127,
    1136,  1138,  1141,  1141,  1148,  1148,  1155,  1155,  1161,  1161,
    1170,  1172,  1175,  1177,  1180,  1185,  1189,  1192,  1195,  1198,
    1198,  1203,  1203,  1209,  1212,  1216,  1217,  1220,  1223,  1226,
    1229,  1232,  1235,  1239,  1242,  1245,  1249,  1252,  1256,  1259,
    1263,  1266,  1270,  1273,  1277,  1280,  1284,  1287,  1291,  1294,
    1298,  1301,  1305,  1308,  1312,  1315,  1319,  1322,  1326,  1329,
    1333,  1336,  1340,  1343,  1347,  1350,  1354,  1357,  1361,  1364,
    1368,  1371,  1375,  1379,  1382,  1385,  1388,  1388,  1393,  1396,
    1402,  1405,  1406,  1407,  1408,  1409,  1410,  1411,  1412,  1413,
    1414,  1417,  1420,  1421,  1424,  1427,  1431,  1435,  1446,  1450,
    1452,  1453,  1456,  1458,  1458,  1464,  1466,  1467,  1473,  1477,
    1487,  1487,  1494,  1494,  1501,  1501,  1508,  1508,  1515,  1515,
    1522,  1522,  1530,  1532,  1533,  1537,  1543,  1548,  1552,  1559,
    1563,  1567,  1572,  1576,  1578,  1581,  1583,  1586,  1589,  1592,
    1595,  1600,  1602,  1603,  1608,  1612,  1617,  1619,  1622,  1626,
    1629,  1635,  1637,  1638,  1641,  1644,  1647,  1650,  1655,  1657,
    1658,  1663,  1668,  1673,  1678,  1683,  1691,  1695,  1699,  1703,
    1707,  1711,  1715,  1718,  1720,  1723,  1727,  1731,  1736,  1738,
    1741,  1747,  1750,  1752,  1754,  1756,  1759,  1762,  1766,  1768,
    1769,  1770
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "T_ASSIGNMENT", "T_ASSPLUS", "T_ASSMINUS", 
  "T_ASSMULT", "T_ASSDIV", "T_ASSMOD", "T_ASSOR", "T_ASSAND", "T_ASSXOR", 
  "T_ASSLSHIFT", "T_ASSRSHIFT", "T_EXCLAM", "T_INCREMENT", "T_DECREMENT", 
  "T_PLUS", "T_MINUS", "T_MULT", "T_DIV", "T_MIN", "T_MAX", "T_MOD", 
  "T_OR", "T_XOR", "T_LSHIFT", "T_RSHIFT", "T_BOOL_AND", "T_BOOL_OR", 
  "T_BOOL_NOT", "T_IMPLY", "T_LT", "T_LEQ", "T_EQ", "T_NEQ", "T_GEQ", 
  "T_GT", "T_FOR", "T_WHILE", "T_DO", "T_BREAK", "T_CONTINUE", "T_SWITCH", 
  "T_IF", "T_ELSE", "T_CASE", "T_DEFAULT", "T_RETURN", "T_TYPEDEF", 
  "T_STRUCT", "T_CONST", "T_OLDCONST", "T_URGENT", "T_BROADCAST", 
  "T_TRUE", "T_FALSE", "T_SYSTEM", "T_PROCESS", "T_STATE", "T_COMMIT", 
  "T_INIT", "T_TRANS", "T_ARROW", "T_GUARD", "T_SYNC", "T_ASSIGN", 
  "T_DEADLOCK", "T_EF", "T_EG", "T_AF", "T_AG", "T_LEADSTO", "T_QUIT", 
  "T_ERROR", "T_ID", "T_TYPENAME", "T_NAT", "T_NEW", "T_NEW_DECLARATION", 
  "T_NEW_LOCAL_DECL", "T_NEW_INST", "T_NEW_SYSTEM", "T_NEW_PARAMETERS", 
  "T_NEW_INVARIANT", "T_NEW_GUARD", "T_NEW_SYNC", "T_NEW_ASSIGN", "T_OLD", 
  "T_OLD_DECLARATION", "T_OLD_LOCAL_DECL", "T_OLD_INST", 
  "T_OLD_PARAMETERS", "T_OLD_INVARIANT", "T_OLD_GUARD", "T_OLD_ASSIGN", 
  "T_PROPERTY", "'?'", "':'", "'&'", "UOPERATOR", "'('", "')'", "'['", 
  "']'", "'.'", "';'", "','", "'{'", "'}'", "'\\n'", "Uppaal", "XTA", 
  "Inst", "@1", "System", "ProcessList", "Declaration", "FunctionDecl", 
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
  "AssignOp", "UnaryOp", "ArgList", "OldXTA", "OldDeclaration", 
  "OldVarDecl", "@29", "OldConstDeclIdList", "OldConstDeclId", 
  "OldProcDecl", "@30", "@31", "@32", "@33", "@34", "@35", 
  "OldProcParams", "OldProcParamList", "OldProcParam", "OldProcBody", 
  "OldVarDeclList", "OldStates", "OldStateDeclList", "OldStateDecl", 
  "OldInvariant", "OldTransitions", "OldTransitionList", "OldTransition", 
  "OldTransitionOpt", "OldGuard", "OldGuardList", "PropertyList", 
  "PropertyList2", "Property", "Quantifier", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   112,   113,   114,   113,   113,   113,   113,   113,   115,
     115,   115,   116,   116,   116,   117,   117,   117,   117,   117,
     119,   118,   120,   120,   120,   120,   120,   120,   121,   121,
     121,   122,   122,   122,   123,   123,   123,   124,   124,   124,
     125,   126,   126,   126,   127,   127,   127,   127,   128,   128,
     128,   129,   129,   129,   130,   130,   130,   130,   130,   130,
     131,   131,   131,   131,   132,   132,   132,   133,   134,   134,
     134,   134,   134,   135,   135,   136,   136,   136,   137,   137,
     137,   137,   137,   138,   138,   138,   139,   140,   140,   140,
     140,   140,   141,   141,   141,   141,   141,   141,   142,   141,
     143,   141,   141,   141,   141,   145,   144,   144,   146,   144,
     144,   147,   148,   148,   148,   148,   149,   149,   149,   149,
     149,   149,   150,   150,   150,   151,   151,   151,   151,   151,
     151,   152,   152,   152,   152,   152,   153,   153,   153,   153,
     153,   153,   154,   154,   154,   155,   155,   155,   155,   155,
     156,   156,   156,   156,   156,   157,   157,   157,   157,   158,
     158,   158,   158,   158,   159,   159,   159,   159,   159,   160,
     160,   160,   161,   161,   161,   161,   162,   162,   162,   162,
     162,   163,   163,   163,   163,   163,   164,   164,   164,   165,
     165,   165,   167,   166,   168,   166,   169,   169,   169,   170,
     170,   171,   171,   171,   171,   172,   171,   173,   171,   174,
     171,   175,   171,   176,   171,   177,   171,   178,   171,   179,
     171,   171,   171,   171,   171,   180,   171,   181,   171,   182,
     171,   171,   171,   171,   171,   183,   184,   183,   185,   183,
     186,   186,   188,   187,   189,   187,   190,   187,   191,   187,
     192,   192,   193,   193,   193,   194,   194,   194,   194,   195,
     194,   196,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   194,   197,   194,   194,   194,
     198,   198,   198,   198,   198,   198,   198,   198,   198,   198,
     198,   199,   199,   199,   200,   200,   200,   200,   201,   202,
     202,   202,   203,   204,   203,   205,   205,   205,   206,   206,
     208,   207,   209,   207,   210,   207,   211,   207,   212,   207,
     213,   207,   214,   214,   214,   214,   215,   215,   215,   216,
     216,   216,   217,   218,   218,   219,   219,   219,   219,   219,
     219,   220,   220,   220,   221,   221,   222,   222,   222,   222,
     222,   223,   223,   223,   223,   223,   223,   223,   224,   224,
     224,   225,   225,   225,   225,   225,   226,   226,   226,   226,
     226,   226,   226,   227,   227,   227,   227,   227,   228,   228,
     228,   229,   230,   230,   231,   231,   231,   231,   232,   232,
     232,   232
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     3,     0,     0,     9,     8,     7,     6,     4,     3,
       4,     3,     1,     3,     3,     0,     2,     2,     2,     2,
       0,     5,     2,     3,     4,     3,     3,     2,     1,     3,
       3,     4,     3,     2,     3,     4,     3,     1,     3,     3,
       3,     0,     2,     2,     1,     3,     4,     3,     1,     3,
       3,     3,     3,     1,     0,     4,     5,     4,     4,     3,
       4,     5,     4,     3,     1,     3,     3,     2,     3,     5,
       5,     4,     3,     1,     1,     1,     2,     2,     3,     4,
       3,     2,     2,     1,     3,     3,     2,     0,     1,     1,
       2,     1,     0,     5,     6,     5,     5,     5,     0,     6,
       0,     7,     4,     3,     2,     0,     7,     7,     0,     6,
       5,     5,     0,     2,     2,     2,     3,     4,     3,     3,
       2,     2,     1,     3,     3,     1,     4,     5,     4,     4,
       3,     3,     4,     3,     2,     1,     0,     3,     4,     3,
       2,     1,     1,     3,     3,     8,     9,     5,     4,     3,
       7,     8,     4,     3,     1,     0,     3,     4,     3,     0,
       3,     4,     3,     3,     2,     3,     2,     3,     2,     0,
       3,     3,     0,     1,     1,     2,     3,     4,     3,     3,
       2,     3,     4,     3,     3,     2,     1,     3,     3,     1,
       3,     3,     0,     5,     0,     4,     0,     2,     2,     0,
       2,     1,     1,     2,     3,     0,    10,     0,    11,     0,
      11,     0,     6,     0,     7,     0,     7,     0,     8,     0,
       7,     2,     3,     2,     3,     0,     8,     0,     9,     0,
       9,     3,     3,     2,     2,     0,     0,     3,     0,     3,
       1,     2,     0,     5,     0,     5,     0,     4,     0,     5,
       0,     1,     1,     3,     3,     1,     1,     1,     1,     0,
       5,     0,     5,     4,     4,     3,     3,     2,     2,     2,
       2,     3,     3,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       5,     5,     4,     3,     3,     1,     0,     4,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     1,     3,     3,     3,     0,
       2,     2,     1,     0,     4,     1,     3,     3,     3,     2,
       0,     7,     0,     8,     0,     7,     0,     6,     0,     5,
       0,     6,     2,     3,     3,     3,     1,     3,     3,     3,
       3,     4,     5,     0,     2,     3,     4,     3,     3,     2,
       1,     1,     3,     3,     1,     4,     1,     3,     1,     3,
       3,     0,     3,     4,     3,     3,     2,     1,     1,     3,
       3,     8,     9,     8,     9,     9,     7,     7,     8,     8,
       8,     7,     1,     0,     3,     4,     3,     2,     1,     3,
       3,     2,     0,     3,     0,     1,     2,     3,     1,     1,
       1,     1
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       0,    35,    35,   132,    22,     0,   107,     0,     0,     0,
       0,   359,   359,   393,    22,   107,     0,     0,     0,   442,
       1,    22,   107,   107,     4,     6,     0,     5,   111,   108,
     109,     7,    48,     0,     0,   352,     0,     0,   351,   353,
     276,   275,   335,   278,   277,     0,     8,     0,     9,    10,
       0,    11,   272,    12,     0,     0,   107,    15,     0,     0,
      16,   386,   408,     0,    17,   438,    18,    19,    20,   444,
       0,     0,     0,    36,    37,    38,     0,    39,   133,   134,
     135,     0,     0,    32,     0,   110,     0,    53,    74,     0,
       0,   112,   288,   290,   279,     0,     0,   340,   341,   342,
     345,   343,   344,   347,   346,   348,   349,   350,   287,   289,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   336,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   293,   188,   184,   186,     0,
       0,   363,     0,     0,   362,     0,   360,   361,   394,    74,
      74,     0,     0,     0,     0,     0,   448,   449,   450,   451,
     445,     0,   441,     0,     0,     0,     0,    93,    94,     0,
      21,     0,     0,    57,    74,     0,     0,    31,     0,    29,
       0,    50,    49,    52,    74,    92,     0,     0,    88,   354,
       0,   286,   285,   307,   306,   309,   308,   311,   310,   313,
     312,   338,   339,   315,   314,   319,   318,   321,   320,   323,
     322,   325,   324,   327,   326,   329,   328,     0,   295,   294,
     297,   296,   299,   298,   301,   300,   305,   304,   303,   302,
       0,   317,   316,     0,     0,   334,   333,   292,   291,   185,
     187,   274,   273,   378,     0,     0,     0,   358,    74,   390,
     389,   388,   387,    74,   407,   410,   409,   440,   439,     0,
     443,   446,    83,     0,     0,    84,    74,   132,     0,   128,
       0,    56,     0,    54,     0,    40,    61,    28,     0,    30,
      34,    33,     0,    51,    91,     0,     0,    95,   124,     0,
     355,     0,     0,   337,   332,     0,   284,   283,   393,     0,
       0,   365,   376,     0,     0,   380,     0,   391,   447,    82,
       0,    80,     0,    87,     0,     0,    47,    42,     0,   132,
       0,   125,    55,    59,    58,     0,     0,    60,     0,     0,
      79,     0,   102,    90,   101,    74,     0,   103,    97,    89,
      96,   118,   123,     0,   280,     0,   282,   331,   330,     0,
       0,   369,     0,   364,     0,   393,   374,     0,   382,     0,
     393,     0,   370,    81,    86,    85,   130,     0,     0,   192,
      46,    45,    43,     0,   132,   132,   212,    41,    63,     0,
      62,    64,    27,     0,   354,    78,    77,    75,   100,   106,
       0,    98,     0,     0,     0,   122,   120,     0,     0,   357,
     356,   379,   400,     0,   192,   368,   367,   366,     0,   393,
     385,   384,   383,     0,   372,   393,   141,   140,   145,     0,
     142,     0,     0,     0,   193,   194,    44,   129,     0,     0,
     216,     0,     0,   278,    73,     0,    68,     0,     0,    26,
       0,    76,    99,   105,   104,     0,   117,     0,   116,   115,
     113,   399,   404,     0,   401,     0,   377,     0,   381,   393,
       0,   139,     0,   138,   136,     0,   205,   209,     0,   200,
     206,     0,   155,     0,     0,   195,   127,   126,   219,     0,
      67,     0,     0,    65,     0,    25,     0,   119,     0,   114,
     398,     0,   397,   395,     0,     0,   375,     0,   371,   150,
       0,   137,   144,   143,   204,   203,   201,     0,   199,   198,
     196,     0,   154,     0,   161,     0,   131,   217,   218,     0,
     215,    66,    70,    69,    72,    71,    24,   121,     0,   396,
     403,   402,   417,     0,   392,   373,   149,   148,   146,   202,
     211,   210,   197,   208,   207,   153,   151,   160,     0,     0,
     162,     0,     0,   237,     0,     0,     0,     0,     0,   222,
     213,   221,   220,     0,   405,   416,     0,     0,   418,   147,
     152,     0,     0,   159,   157,     0,     0,     0,     0,     0,
       0,     0,   241,     0,   243,     0,     0,   239,   254,   253,
       0,     0,   223,   415,     0,     0,   414,   412,     0,   169,
       0,     0,   158,   164,     0,   174,   163,   229,   227,     0,
     233,   235,     0,     0,   242,   244,     0,     0,     0,     0,
     252,   251,   224,     0,     0,   413,   420,     0,   432,   419,
     168,     0,   175,     0,     0,   270,   270,     0,     0,     0,
       0,     0,     0,     0,   245,     0,     0,     0,   433,     0,
       0,   167,     0,   179,   173,     0,   175,     0,   271,     0,
       0,     0,     0,     0,     0,   247,   249,     0,     0,   433,
     433,     0,   179,     0,   433,     0,   433,     0,     0,     0,
     189,   172,   179,   270,   270,     0,     0,     0,   232,     0,
       0,     0,     0,   255,   179,   179,   437,     0,   189,   433,
     179,   433,   179,   178,     0,   176,     0,     0,     0,     0,
     189,     0,     0,     0,   234,   236,     0,     0,     0,     0,
       0,     0,   260,   256,   240,   189,   189,   436,   434,     0,
     179,   189,   179,   189,   177,   183,   182,   180,     0,     0,
       0,   165,     0,   270,   270,     0,   238,     0,     0,     0,
       0,     0,   266,   246,   261,     0,     0,     0,     0,   435,
     423,   421,   189,     0,   189,     0,   181,   191,   190,   166,
       0,   170,     0,     0,     0,   248,   250,   264,   262,   268,
     219,   257,   259,   425,   424,   422,     0,   431,     0,   427,
     426,   171,     0,     0,   226,   219,   219,   219,   267,   430,
     429,   428,   230,   228,   265,   263,   269,     0,     0,     0
};

static const short yydefgoto[] =
{
     807,    20,    24,   384,    27,    84,    21,    73,   325,   270,
      31,    32,   144,   172,   173,   327,   434,   435,   436,   276,
      75,   264,   265,   145,   248,   286,   287,   336,   337,    34,
     188,   393,   447,    77,   375,   319,   314,   315,   369,   419,
     420,   474,   516,   549,   550,   606,   653,   680,    49,   709,
     423,   424,   425,   471,   468,   561,   430,   431,   478,   519,
     562,   609,   636,   635,   612,   638,   639,   580,   619,   667,
     690,   691,   724,   755,   756,   721,   722,   796,   795,   780,
     797,   657,   658,    52,   189,   190,   217,   134,    47,   291,
      53,    54,   146,   244,   300,   301,   147,   415,   459,   409,
     355,   298,   360,   306,    60,    61,   349,   350,   404,   453,
     454,    64,   534,   567,   568,   629,   672,    66,    68,    69,
     162,   163
};

static const short yypact[] =
{
    1395,-32768,-32768,-32768,-32768,   220,   406,  3223,  3223,  3223,
    3223,-32768,-32768,-32768,-32768,   643,   434,  3223,  3223,-32768,
  -32768,   868,   427,   657,   -22,-32768,   242,-32768,-32768,     7,
  -32768,    80,-32768,   214,    19,-32768,  3223,  3223,-32768,-32768,
  -32768,-32768,-32768,   -10,-32768,  1843,  1814,  3223,  1814,-32768,
    1120,   111,  1814,-32768,   703,   665,   681,   -22,   150,   160,
     140,   159,-32768,   389,   166,  1814,   236,   111,-32768,  3196,
    1158,   137,   154,-32768,-32768,-32768,   185,-32768,-32768,-32768,
  -32768,   569,   255,-32768,    53,-32768,  1298,-32768,-32768,   295,
      41,   273,   217,   217,   387,   301,  1400,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
    1866,  1871,  1935,  1941,  3223,  3223,  1968,  1991,  2047,  2056,
    2079,  2112,  2135,-32768,  2144,  2200,  2223,  2228,  2256,  2292,
    3223,  2320,  2325,   246,  2348,   217,     3,-32768,  3223,  2398,
     323,-32768,   222,   154,-32768,   185,-32768,-32768,-32768,-32768,
  -32768,   837,   378,   376,  2404,  2454,-32768,-32768,-32768,-32768,
  -32768,  1435,   353,  3223,   393,   264,   385,-32768,-32768,   -52,
  -32768,   402,    57,-32768,   477,   411,   511,-32768,   493,-32768,
     262,-32768,-32768,   505,-32768,-32768,  1338,  2477,-32768,  3223,
     611,-32768,-32768,-32768,   544,-32768,   544,-32768,   217,-32768,
     217,   487,   487,-32768,   217,-32768,  3081,-32768,  3118,-32768,
     363,-32768,   363,-32768,  3044,-32768,  3021,  3223,-32768,  1092,
  -32768,  1092,-32768,  3172,-32768,  3172,-32768,  1092,-32768,  1092,
    1157,-32768,  3141,   515,  1538,-32768,-32768,-32768,  1814,-32768,
  -32768,-32768,  1814,-32768,   540,   513,    38,-32768,-32768,   505,
     505,-32768,   159,-32768,-32768,-32768,  1814,-32768,  1814,  3223,
  -32768,  1814,-32768,   523,    59,-32768,-32768,-32768,   200,-32768,
      42,-32768,   525,-32768,   299,-32768,    85,-32768,   136,-32768,
  -32768,-32768,  2482,   505,   -54,   309,    17,-32768,   528,   799,
    1814,   -30,   537,  2990,-32768,  2510,-32768,-32768,-32768,   161,
     184,-32768,-32768,   517,   233,-32768,    45,   505,  1814,-32768,
     545,-32768,   368,   505,   543,  1198,   557,-32768,    65,-32768,
     563,-32768,-32768,-32768,-32768,   566,   669,-32768,   571,   226,
     574,  1260,-32768,-32768,   576,-32768,    62,-32768,   580,-32768,
  -32768,  3223,   141,  2546,-32768,  2574,-32768,-32768,   331,   564,
     712,-32768,  2927,-32768,   269,-32768,-32768,   586,-32768,    72,
  -32768,   584,-32768,-32768,-32768,-32768,-32768,   592,   372,     4,
  -32768,   598,-32768,   594,-32768,-32768,   626,-32768,-32768,   561,
  -32768,  1814,-32768,   327,  3223,-32768,   597,-32768,-32768,   505,
     603,-32768,   370,   713,  1573,-32768,-32768,   616,  1297,-32768,
    1814,-32768,-32768,   386,     4,-32768,-32768,-32768,   612,-32768,
  -32768,-32768,-32768,   613,-32768,-32768,-32768,   620,   619,    64,
  -32768,   390,   440,   271,   676,-32768,-32768,-32768,   628,   629,
  -32768,   727,   630,   381,-32768,    33,-32768,   642,   637,-32768,
     330,-32768,-32768,-32768,-32768,   641,-32768,  3223,-32768,   645,
  -32768,   652,   639,    77,-32768,   271,-32768,   650,-32768,-32768,
     659,-32768,  2579,   663,-32768,   441,   666,-32768,    83,   667,
  -32768,    86,-32768,   486,    21,-32768,-32768,-32768,   973,   671,
  -32768,   672,   567,-32768,   675,-32768,   668,-32768,  1676,-32768,
  -32768,   434,   678,-32768,   490,    27,-32768,   673,-32768,   680,
     521,-32768,-32768,-32768,-32768,   684,-32768,   494,-32768,   686,
  -32768,   496,-32768,    75,-32768,   499,-32768,-32768,-32768,  2830,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   489,-32768,
  -32768,-32768,-32768,   518,-32768,-32768,-32768,   685,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,   687,-32768,-32768,    22,    93,
  -32768,   193,   206,-32768,    89,    91,   207,   674,  1016,-32768,
  -32768,-32768,-32768,   836,-32768,   689,   208,    96,-32768,-32768,
  -32768,   692,   519,   690,-32768,    23,   728,  2602,   749,  2652,
    2873,   707,-32768,   768,-32768,   774,  2658,-32768,-32768,-32768,
     942,   770,-32768,-32768,   688,   802,   775,-32768,   229,-32768,
     773,    46,-32768,-32768,   520,-32768,-32768,-32768,-32768,  3223,
  -32768,-32768,  3223,   748,-32768,-32768,  3223,  3223,   349,  3223,
  -32768,-32768,-32768,   808,    47,-32768,-32768,   565,-32768,-32768,
  -32768,   776,   828,   786,    49,  3223,  3223,   205,  3223,  3223,
     365,   796,   416,   482,-32768,   500,   792,   795,   841,   151,
      50,-32768,  2708,   842,-32768,   801,   828,   806,   111,   809,
    3223,   507,   539,  2873,  3223,-32768,-32768,   800,  2873,   841,
     841,  2731,   842,   812,   841,   815,   841,   810,   979,  2736,
     848,-32768,   842,  3223,  3223,   224,  2873,  2873,-32768,   546,
     816,   817,   277,   882,   842,   842,-32768,    98,   848,   841,
     842,   841,   842,-32768,   822,-32768,   823,   100,  2764,    20,
     848,   825,   830,  3223,-32768,-32768,   831,   277,   277,  2800,
      43,   541,-32768,   933,-32768,   848,   848,   832,-32768,    34,
     842,   848,   842,   848,-32768,-32768,   834,-32768,   850,   332,
     866,-32768,    35,  3223,  3223,   553,-32768,   554,   558,   883,
    1711,   895,-32768,-32768,-32768,  2873,  1008,   909,   910,-32768,
     911,-32768,   848,   912,   848,    36,-32768,-32768,-32768,-32768,
     916,-32768,   927,   931,  2873,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,   926,-32768,   928,   934,
  -32768,-32768,  2873,  2873,-32768,-32768,-32768,-32768,  2873,-32768,
  -32768,-32768,-32768,-32768,  2873,  2873,  2873,  1036,  1040,-32768
};

static const short yypgoto[] =
{
  -32768,-32768,     5,-32768,   183,-32768,  1042,    -9,-32768,   878,
     785,   956,   -16,-32768,   780,-32768,  -311,-32768,   573,   -68,
     -20,-32768,   745,    10,   -63,-32768,   777,-32768,   670,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,   -95,  1056,-32768,-32768,
     595,   606,-32768,-32768,   491,-32768,   408,   356,   388,   168,
     661,-32768,   644,-32768,-32768,   744,-32768,-32768,-32768,  -326,
    -535,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,  -244,  -406,-32768,-32768,-32768,
  -32768,  -609,    -6,    -7,-32768,-32768,-32768,-32768,-32768,   691,
  -32768,  1058,   -45,-32768,-32768,   719,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,   783,   923,  -141,  1064,-32768,-32768,
     585,   589,-32768,-32768,   483,-32768,   210,   418,-32768,-32768,
  -32768,-32768
};


#define	YYLAST		3324


static const short yytable[] =
{
      46,    48,    50,    80,    51,    74,    74,    79,   169,    63,
      65,   148,    67,   174,    78,   380,    33,   239,   338,    57,
     183,   740,   514,   571,   603,    59,    72,   659,   532,    92,
      93,    76,    76,    76,   481,   760,   770,   789,    96,   303,
     135,   405,   185,   320,   751,   613,   361,   631,   647,   268,
     655,   675,   332,    81,   178,   333,   269,   421,   272,   143,
     310,    85,   161,   390,   422,   463,   371,  -107,    28,    90,
      29,    30,   344,   411,   711,   712,   545,   345,   492,   246,
     165,   249,   250,   515,   505,   572,   604,   509,   326,   533,
     581,    94,   583,  -107,   573,    91,    33,   596,   548,   727,
     240,   736,   266,   194,   196,   198,   200,   201,   202,   204,
     206,   208,   210,   212,   214,   216,   283,   219,   221,   223,
     225,   227,   229,   230,   232,   234,   339,   238,   688,   741,
    -156,   230,   242,   693,   772,   773,  -411,   328,   166,   304,
     482,   752,   483,   761,   771,   790,   305,   256,   258,   186,
     321,   714,   715,   362,   632,   648,   261,   656,   676,   179,
     180,    59,   351,   273,   274,   311,   312,   372,   391,   392,
     464,   465,    86,   525,   412,   -74,   -74,   -74,   151,   -74,
     289,   546,   290,   493,   494,   307,   171,    86,   282,   506,
     507,   -74,   510,   511,   576,   582,   285,   584,   313,   574,
     575,   316,   597,   598,   728,   155,   737,   578,   585,   594,
     293,    26,   167,   168,   408,    87,   -74,   -74,   139,   413,
     781,    25,   335,   245,   373,   149,   673,   383,   -74,    81,
     626,   352,   108,   109,   357,   150,   -74,   329,   -74,   794,
     -23,   -23,   -23,    82,   -23,   395,   151,   235,   396,   266,
    -107,    28,   308,    29,    30,   170,   -23,   802,   803,   674,
     167,   168,   -74,   280,   -74,   263,   152,   389,   457,   -74,
     406,   595,   472,   154,   460,   331,  -107,    26,    33,   428,
     429,   -23,   -23,  -107,    28,    58,    29,    30,   348,    88,
     353,   354,   627,   -23,   577,    80,   285,   167,   168,    79,
     323,   -23,   317,   -23,   566,   148,    78,   579,   586,  -107,
     334,   660,   139,    89,    59,   754,   437,    83,   497,   381,
     132,   236,   133,   719,   720,    76,   247,   -23,   -23,   335,
     713,   139,   473,   -23,   394,   358,   398,   281,   400,   167,
     168,   754,   754,   155,   299,   381,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   177,   123,   124,   125,   126,   127,   128,   129,   364,
     184,   443,   381,   417,   167,   168,   187,   290,   108,   109,
     110,   111,   112,   113,   167,   168,   116,   451,  -281,  -406,
     153,   466,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   191,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   437,
     123,   124,   125,   126,   127,   128,   129,    -2,   130,   438,
     131,   243,   486,   439,   132,    62,   133,   345,   768,   139,
     488,   469,   502,   167,   168,   167,   168,   418,    35,    36,
      37,   644,    38,   253,   798,   500,   139,    28,   518,    29,
      30,   452,   517,   260,    39,   467,   132,   663,   133,   804,
     805,   806,   139,   747,   748,   381,    70,   381,    28,   -93,
      29,    30,    94,   254,    63,    71,   130,   512,   131,    40,
      41,   530,   132,   267,   133,   540,  -406,   543,  -406,   262,
     547,    42,   108,   109,   110,   111,   112,   113,   271,    43,
     116,    44,   563,   119,   120,   470,   418,   277,   665,   565,
     600,   633,   537,   139,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,    45,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   590,   123,   124,   125,   126,   127,   128,   129,   108,
     109,   513,   432,   112,   113,   452,   649,   116,   522,   541,
     175,   544,   176,   563,   548,    35,    36,    37,   268,    38,
     618,    35,    36,    37,   666,    38,   278,   719,   720,   139,
     132,    39,   133,   566,   601,   634,   154,    39,   564,   279,
     719,   720,   668,   637,   719,   720,   640,   139,   282,   686,
     642,   643,   292,   645,   139,   299,    40,    41,   130,   296,
     131,   302,    40,    41,   132,   356,   133,  -214,    42,   309,
     538,   322,   661,   662,    42,   341,   433,   168,    44,   346,
     650,   687,   433,   168,    44,   678,   139,   132,   716,   133,
     753,   363,   366,   139,   685,   774,   563,    -3,   689,   370,
     139,   563,    45,   775,    65,   -13,   140,   776,    45,   379,
     378,   374,    50,   401,   376,   379,   524,   382,   385,   563,
     563,   -14,   388,    35,    36,    37,   332,    38,   410,    35,
      36,    37,   414,    38,    28,    58,    29,    30,   416,    39,
     426,   441,   739,   427,   140,    39,    70,   745,    28,   442,
      29,    30,   750,   402,   445,  -107,    28,   141,    29,    30,
     448,   456,   458,   142,    40,    41,   461,   462,   479,   421,
      40,    41,    28,   141,    29,    30,    42,   476,   477,   480,
     484,  -107,    42,   485,    43,   487,    44,   491,   563,   489,
      43,   623,    44,  -107,    28,   141,    29,    30,   490,   496,
     -22,   142,  -107,    28,   141,    29,    30,   563,   498,   501,
      45,   403,   504,   508,   526,   587,    45,   379,   -22,  -107,
     520,   521,   535,   379,   529,   563,   563,   641,  -107,   536,
     539,   563,   542,   570,   569,   593,   602,   563,   563,   563,
     342,   599,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   614,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   607,
     123,   124,   125,   126,   127,   128,   129,   591,   251,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     610,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   729,   123,   124,   125,
     126,   127,   128,   129,   615,   616,   622,   624,   742,   694,
     695,   625,   630,   646,   700,   651,   702,  -107,    28,    58,
      29,    30,   652,   757,   758,   654,   130,   664,   131,   763,
     669,   765,   132,   670,   133,   671,   343,   679,   692,   730,
     681,   732,   683,  -107,   708,   684,   703,    70,  -107,    28,
     699,    29,    30,   701,   717,   718,    71,   723,   734,   735,
     786,   743,   788,   130,  -258,   131,   744,   746,   759,   132,
     766,   133,   592,   620,  -107,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   767,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   769,   123,   124,   125,   126,   127,   128,   129,
     704,   777,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   779,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   782,
     123,   124,   125,   126,   127,   128,   129,   588,   783,   784,
     785,   787,    70,  -107,    28,   791,    29,    30,   698,   792,
      35,    36,    37,   793,    38,   799,   808,   800,   710,   130,
     809,   131,   182,   801,    22,   132,    39,   133,   621,  -107,
     725,   726,   275,   318,   324,   523,   731,   365,   733,    23,
     503,   495,   444,   340,   682,   455,   605,   707,   475,   377,
      55,    40,    41,   407,   252,   440,   130,    56,   131,   531,
     528,   628,   132,    42,   133,   705,   762,   359,   764,   697,
       0,    43,     0,    44,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   108,   109,   110,
     111,   112,   113,   114,   115,   116,     0,    45,   119,   120,
       0,   136,   589,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   137,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
       0,   123,   124,   125,   126,   127,   128,   129,   294,   164,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,     0,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,     0,   123,   124,
     125,   126,   127,   128,   129,   132,     0,   133,     0,   367,
       0,     0,     0,     0,     0,     0,     0,     0,  -107,    28,
       0,    29,    30,     0,     0,     0,     0,   138,     0,   131,
       0,     0,     0,   132,     0,   133,     0,     0,     0,     0,
       0,     0,     0,     0,  -107,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    70,  -107,    28,
       0,    29,    30,     0,   130,   295,   131,   368,     0,     0,
     132,   386,   133,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,  -107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
       0,   123,   124,   125,   126,   127,   128,   129,   449,   181,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,     0,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,     0,   123,   124,
     125,   126,   127,   128,   129,     0,     0,     0,     0,   284,
       0,     0,     0,     0,     0,     0,     0,     0,  -107,    28,
       0,    29,    30,     0,     0,     0,     0,   130,     0,   131,
       0,     0,     0,   132,   387,   133,     0,     0,     0,     0,
       0,     0,     0,     0,  -107,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -107,    28,
       0,    29,    30,     0,   130,     0,   131,     0,     0,     0,
     132,   450,   133,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,  -107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
       0,   123,   124,   125,   126,   127,   128,   129,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,     0,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,     0,   123,   124,   125,   126,
     127,   128,   129,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,     0,     0,     0,     0,     0,   130,     0,   131,
       0,     0,   192,   132,     0,   133,     0,   259,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   130,     0,   131,     0,     0,     0,   132,     0,
     133,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,     0,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,     0,   123,
     124,   125,   126,   127,   128,   129,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,     0,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,     0,   123,   124,   125,   126,   127,   128,
     129,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   130,     0,   131,     0,     0,
       0,   132,   297,   133,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     130,     0,   131,     0,     0,     0,   132,   446,   133,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
       0,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,     0,   123,   124,   125,
     126,   127,   128,   129,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,     0,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,     0,   123,   124,   125,   126,   127,   128,   129,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   130,     0,   131,     0,     0,     0,   132,
     527,   133,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   130,   778,
     131,     0,     0,     0,   132,     0,   133,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,     0,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,    95,   123,   124,   125,   126,   127,
     128,   129,     0,     0,     0,     0,     0,    35,    36,    37,
       0,    38,     0,     0,     0,     0,     0,   193,     0,     0,
       0,     0,   195,    39,     0,     0,     0,     0,     0,     0,
      35,    36,    37,     0,    38,    35,    36,    37,     0,    38,
       0,     0,     0,     0,     0,     0,    39,     0,    40,    41,
       0,    39,     0,     0,     0,     0,     0,     0,     0,     0,
      42,   130,     0,   131,     0,     0,     0,   132,    43,   133,
      44,    40,    41,     0,     0,     0,    40,    41,     0,     0,
       0,     0,     0,    42,     0,     0,   197,     0,    42,     0,
       0,    43,   199,    44,    45,     0,    43,     0,    44,    35,
      36,    37,     0,    38,     0,    35,    36,    37,     0,    38,
       0,     0,     0,     0,     0,    39,     0,    45,     0,   203,
       0,    39,    45,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    35,    36,    37,     0,    38,     0,     0,     0,
      40,    41,   205,     0,     0,     0,    40,    41,    39,     0,
       0,     0,    42,     0,     0,    35,    36,    37,    42,    38,
      43,     0,    44,     0,     0,     0,    43,     0,    44,     0,
       0,    39,     0,    40,    41,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    42,    45,     0,     0,     0,
       0,     0,    45,    43,     0,    44,    40,    41,   207,     0,
       0,     0,     0,     0,     0,     0,     0,   209,    42,     0,
       0,    35,    36,    37,     0,    38,    43,     0,    44,    45,
      35,    36,    37,     0,    38,     0,     0,    39,     0,     0,
     211,     0,     0,     0,     0,     0,    39,     0,     0,     0,
       0,     0,    45,    35,    36,    37,     0,    38,     0,     0,
       0,     0,    40,    41,     0,     0,     0,     0,     0,    39,
       0,    40,    41,   213,    42,     0,     0,     0,     0,     0,
       0,     0,    43,    42,    44,     0,    35,    36,    37,     0,
      38,    43,     0,    44,    40,    41,   215,     0,     0,     0,
       0,     0,    39,     0,     0,   218,    42,     0,    45,    35,
      36,    37,     0,    38,    43,     0,    44,    45,    35,    36,
      37,     0,    38,     0,     0,    39,     0,    40,    41,     0,
       0,     0,     0,     0,    39,     0,     0,     0,     0,    42,
      45,     0,     0,     0,     0,     0,     0,    43,     0,    44,
      40,    41,     0,     0,     0,     0,     0,     0,     0,    40,
      41,   220,    42,     0,     0,     0,     0,     0,     0,     0,
      43,    42,    44,    45,    35,    36,    37,     0,    38,    43,
       0,    44,     0,     0,   222,     0,     0,     0,     0,   224,
      39,     0,     0,     0,     0,     0,    45,    35,    36,    37,
       0,    38,    35,    36,    37,    45,    38,     0,     0,     0,
       0,     0,     0,    39,     0,    40,    41,   226,    39,     0,
       0,     0,     0,     0,     0,     0,     0,    42,     0,     0,
      35,    36,    37,     0,    38,    43,     0,    44,    40,    41,
       0,     0,     0,    40,    41,     0,    39,     0,     0,     0,
      42,     0,     0,   228,     0,    42,     0,     0,    43,     0,
      44,    45,     0,    43,     0,    44,    35,    36,    37,     0,
      38,    40,    41,     0,     0,     0,     0,     0,     0,     0,
       0,   231,    39,    42,    45,     0,   233,     0,     0,    45,
       0,    43,     0,    44,    35,    36,    37,     0,    38,    35,
      36,    37,     0,    38,     0,     0,     0,    40,    41,   237,
      39,     0,     0,     0,     0,    39,     0,    45,     0,    42,
       0,     0,    35,    36,    37,     0,    38,    43,     0,    44,
       0,     0,     0,     0,     0,    40,    41,     0,    39,     0,
      40,    41,     0,     0,     0,     0,     0,    42,     0,     0,
       0,     0,    42,    45,     0,    43,     0,    44,     0,   241,
      43,     0,    44,    40,    41,   255,     0,     0,     0,     0,
       0,     0,    35,    36,    37,    42,    38,     0,    35,    36,
      37,    45,    38,    43,     0,    44,    45,     0,    39,     0,
       0,     0,     0,     0,    39,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    45,
       0,     0,     0,    40,    41,   257,     0,     0,     0,    40,
      41,     0,     0,     0,     0,    42,     0,     0,    35,    36,
      37,    42,    38,    43,     0,    44,     0,     0,   288,    43,
       0,    44,     0,   330,    39,     0,     0,     0,     0,     0,
       0,    35,    36,    37,     0,    38,    35,    36,    37,    45,
      38,     0,     0,     0,     0,    45,     0,    39,     0,    40,
      41,   347,    39,     0,     0,     0,     0,     0,     0,     0,
       0,    42,     0,     0,    35,    36,    37,     0,    38,    43,
       0,    44,    40,    41,     0,     0,     0,    40,    41,     0,
      39,     0,     0,     0,    42,     0,     0,   397,     0,    42,
       0,     0,    43,     0,    44,    45,     0,    43,     0,    44,
      35,    36,    37,     0,    38,    40,    41,     0,     0,     0,
       0,     0,     0,     0,     0,   399,    39,    42,    45,     0,
     499,     0,     0,    45,     0,    43,     0,    44,    35,    36,
      37,     0,    38,    35,    36,    37,     0,    38,     0,     0,
       0,    40,    41,   608,    39,     0,     0,     0,     0,    39,
       0,    45,     0,    42,     0,     0,  -225,  -225,  -225,     0,
    -225,    43,     0,    44,     0,     0,     0,     0,     0,    40,
      41,     0,  -225,     0,    40,    41,     0,     0,     0,     0,
       0,    42,     0,     0,     0,     0,    42,    45,     0,    43,
       0,    44,     0,   611,    43,     0,    44,  -225,  -225,   617,
       0,     0,     0,     0,     0,     0,  -231,  -231,  -231,  -225,
    -231,     0,    35,    36,    37,    45,    38,  -225,     0,  -225,
      45,     0,  -231,     0,     0,     0,     0,     0,    39,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -225,     0,     0,     0,  -231,  -231,   677,
       0,     0,     0,    40,    41,     0,     0,     0,     0,  -231,
       0,     0,    35,    36,    37,    42,    38,  -231,     0,  -231,
       0,     0,   696,    43,     0,    44,     0,   706,    39,     0,
       0,     0,     0,     0,     0,    35,    36,    37,     0,    38,
      35,    36,    37,  -231,    38,     0,     0,     0,     0,    45,
       0,    39,     0,    40,    41,   738,    39,     0,     0,     0,
       0,     0,     0,     0,     0,    42,     0,     0,    35,    36,
      37,     0,    38,    43,     0,    44,    40,    41,     0,     0,
       0,    40,    41,     0,    39,     0,     0,     0,    42,     0,
       0,   749,     0,    42,     0,     0,    43,     0,    44,    45,
       0,    43,     0,    44,    35,    36,    37,     0,    38,    40,
      41,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      39,    42,    45,     0,     0,     0,     0,    45,     0,    43,
       0,    44,     0,     0,    35,    36,    37,     0,    38,     0,
       0,     0,     0,     0,     0,    40,    41,     0,     0,     0,
      39,     0,     0,     0,     0,    45,     0,    42,   551,   552,
     553,   554,   555,   556,   557,    43,     0,    44,   558,     0,
       0,     0,     0,     0,     0,    40,    41,    35,    36,    37,
       0,    38,     0,     0,     0,     0,     0,    42,     0,     0,
       0,    45,     0,    39,     0,    43,     0,    44,     0,     0,
       0,   551,   552,   553,   554,   555,   556,   557,     0,     0,
       0,   558,     0,     0,     0,     0,     0,     0,    40,    41,
       0,    45,     0,     0,     0,     0,   559,     0,   376,   560,
      42,    35,    36,    37,     0,    38,     0,     0,    43,     0,
      44,     0,     0,     0,     0,     0,     0,    39,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    45,     0,     0,     0,     0,   559,
       0,   376,    40,    41,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    42,     0,     0,     0,     0,     0,
       0,     0,    43,     0,    44,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
       0,     0,   124,   125,   126,   127,   128,   129,    45,     0,
     282,     0,     0,     0,     0,   379,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
       0,     0,     0,   124,   125,   126,   127,   128,   129,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,     0,     0,     0,     0,   124,   125,   126,   127,
     128,   129,     0,     0,     0,     0,     0,     0,     0,   131,
       0,     0,     0,   132,     0,   133,   108,   109,   110,   111,
     112,   113,   114,   115,   116,     0,   118,   119,   120,     0,
       0,     0,     0,   124,   125,   126,   127,   128,   129,     0,
     131,     0,     0,     0,   132,     0,   133,     0,     0,     0,
       0,     0,     0,   108,   109,   110,   111,   112,   113,   114,
     115,   116,     0,   131,   119,   120,     0,   132,     0,   133,
     124,   125,   126,   127,   128,   129,   108,   109,   110,   111,
     112,   113,   114,   115,   116,     0,     0,   119,   120,     0,
       0,     0,     0,   124,   125,   126,   127,   128,   129,     0,
     131,     0,     0,     0,   132,     0,   133,   108,   109,   110,
     111,   112,   113,   114,   115,   116,     0,     0,   119,   120,
       0,     0,     0,     0,   124,   125,     0,     0,   128,   129,
      35,    36,    37,     0,    38,     0,     0,   131,     0,     0,
       0,   132,     0,   133,     0,     0,    39,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    35,    36,    37,
       0,    38,     0,     0,   132,     0,   133,     0,     0,     0,
       0,    40,    41,    39,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    42,   156,   157,   158,   159,     0,   160,
       0,    43,     0,    44,     0,   132,     0,   133,    40,    41,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      42,     0,     0,     0,     0,     0,     0,    45,    43,     0,
      44,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    45
};

static const short yycheck[] =
{
       7,     8,     9,    23,    10,    21,    22,    23,    71,    16,
      17,    56,    18,    76,    23,   326,     6,    14,     1,    14,
      88,     1,     1,     1,     1,    15,    21,   636,     1,    36,
      37,    21,    22,    23,     1,     1,     1,     1,    45,     1,
      47,   352,     1,     1,     1,   580,     1,     1,     1,   101,
       1,     1,   106,    75,     1,   109,   108,    53,     1,    54,
       1,    54,    69,     1,    60,     1,     1,    50,    51,    50,
      53,    54,   102,     1,   683,   684,     1,   107,     1,   142,
      70,   149,   150,    62,     1,    63,    63,     1,     3,    62,
       1,   101,     1,    76,     1,    76,    86,     1,    75,     1,
      97,     1,   165,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   184,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   109,   134,   663,   109,
     109,   138,   139,   668,   743,   744,   109,     1,     1,   101,
     107,    98,   109,   109,   109,   109,   108,   154,   155,   108,
     108,   686,   687,   108,   108,   108,   163,   108,   108,   106,
     107,   151,     1,   106,   107,   106,   107,   102,   106,   107,
     106,   107,   107,   484,   102,    14,    15,    16,   106,    18,
     187,   106,   189,   106,   107,   253,     1,   107,   103,   106,
     107,    30,   106,   107,     1,   106,   186,   106,   266,   106,
     107,     1,   106,   107,   106,   107,   106,     1,     1,     1,
     217,    57,    75,    76,   355,     1,    55,    56,   107,   360,
     755,     1,   285,     1,   319,    75,    75,     1,    67,    75,
       1,   299,    15,    16,     1,    75,    75,   101,    77,   774,
      14,    15,    16,     1,    18,   104,   106,     1,   107,   312,
      50,    51,   259,    53,    54,    72,    30,   792,   793,   108,
      75,    76,   101,     1,   103,     1,   107,   335,   409,   108,
       1,    63,     1,   107,   415,   282,    76,    57,   268,   374,
     375,    55,    56,    50,    51,    52,    53,    54,   295,    75,
     106,   107,    63,    67,   101,   315,   286,    75,    76,   315,
       1,    75,   102,    77,    75,   350,   315,   101,   101,    76,
       1,   106,   107,    99,   304,   721,   379,    75,   459,   326,
     103,    75,   105,    46,    47,   315,   143,   101,   102,   392,
     106,   107,    61,   107,   341,   102,   343,    75,   345,    75,
      76,   747,   748,   107,    75,   352,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,   106,    31,    32,    33,    34,    35,    36,    37,     1,
      75,     1,   379,     1,    75,    76,   103,   384,    15,    16,
      17,    18,    19,    20,    75,    76,    23,     1,     1,     0,
       1,     1,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,   102,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,   482,
      31,    32,    33,    34,    35,    36,    37,     0,    97,   102,
      99,   108,   102,   106,   103,     1,   105,   107,   106,   107,
     447,     1,     1,    75,    76,    75,    76,    75,    14,    15,
      16,   102,    18,    75,   780,   462,   107,    51,   478,    53,
      54,    75,   478,   110,    30,    75,   103,   102,   105,   795,
     796,   797,   107,   717,   718,   482,    49,   484,    51,    98,
      53,    54,   101,   107,   491,    58,    97,     1,    99,    55,
      56,     1,   103,   108,   105,     1,   107,     1,   109,   106,
       1,    67,    15,    16,    17,    18,    19,    20,   106,    75,
      23,    77,   519,    26,    27,    75,    75,   106,   102,     1,
       1,     1,     1,   107,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,   101,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,   558,    31,    32,    33,    34,    35,    36,    37,    15,
      16,    75,     1,    19,    20,    75,     1,    23,     1,    75,
       1,    75,     3,   580,    75,    14,    15,    16,   101,    18,
     586,    14,    15,    16,   102,    18,    75,    46,    47,   107,
     103,    30,   105,    75,    75,    75,   107,    30,   109,   106,
      46,    47,   102,   609,    46,    47,   612,   107,   103,   102,
     616,   617,     1,   619,   107,    75,    55,    56,    97,   104,
      99,   108,    55,    56,   103,   108,   105,     1,    67,   106,
     109,   106,   638,   639,    67,   107,    75,    76,    77,   102,
      75,   102,    75,    76,    77,   652,   107,   103,   102,   105,
     109,   106,   109,   107,   660,   102,   663,     0,   664,   102,
     107,   668,   101,   109,   671,     0,     1,   109,   101,   108,
       1,   108,   679,   109,   108,   108,     1,   106,   104,   686,
     687,     0,   106,    14,    15,    16,   106,    18,   102,    14,
      15,    16,   108,    18,    51,    52,    53,    54,   106,    30,
     102,   104,   708,   109,     1,    30,    49,   713,    51,   106,
      53,    54,   719,     1,     1,    50,    51,    52,    53,    54,
     104,   109,   109,    58,    55,    56,   106,   108,     1,    53,
      55,    56,    51,    52,    53,    54,    67,   109,   109,   109,
      98,    76,    67,   106,    75,   104,    77,   108,   755,   104,
      75,    63,    77,    50,    51,    52,    53,    54,   106,   109,
      57,    58,    50,    51,    52,    53,    54,   774,   109,   106,
     101,    59,   106,   106,   106,   101,   101,   108,    75,    76,
     109,   109,   109,   108,   106,   792,   793,    39,    76,   109,
     106,   798,   106,   106,   109,   106,   106,   804,   805,   806,
       1,   109,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,   106,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,   101,
      31,    32,    33,    34,    35,    36,    37,     1,     1,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
     101,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,   698,    31,    32,    33,
      34,    35,    36,    37,   106,   101,   106,    75,   710,   669,
     670,   106,   109,    75,   674,   109,   676,    50,    51,    52,
      53,    54,    64,   725,   726,   109,    97,   101,    99,   731,
     108,   733,   103,   108,   105,    64,   107,    65,   108,   699,
     109,   701,   106,    76,    66,   106,   106,    49,    50,    51,
     108,    53,    54,   108,   108,   108,    58,    45,   106,   106,
     762,   106,   764,    97,     1,    99,   106,   106,   106,   103,
     106,   105,   106,     1,    76,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,   106,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,   106,    31,    32,    33,    34,    35,    36,    37,
       1,    98,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    98,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,     1,
      31,    32,    33,    34,    35,    36,    37,     1,   109,   109,
     109,   109,    49,    50,    51,   109,    53,    54,   672,   102,
      14,    15,    16,   102,    18,   109,     0,   109,   682,    97,
       0,    99,    86,   109,     2,   103,    30,   105,   106,    76,
     694,   695,   174,   268,   274,   482,   700,   312,   702,     3,
     465,   455,   392,   286,   656,   404,   575,   679,   424,   325,
      12,    55,    56,   354,   151,   384,    97,    13,    99,   494,
     491,   598,   103,    67,   105,   106,   730,   304,   732,   671,
      -1,    75,    -1,    77,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    -1,   101,    26,    27,
      -1,     1,   106,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      -1,    31,    32,    33,    34,    35,    36,    37,     1,     1,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    -1,    31,    32,
      33,    34,    35,    36,    37,   103,    -1,   105,    -1,     1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,
      -1,    53,    54,    -1,    -1,    -1,    -1,    97,    -1,    99,
      -1,    -1,    -1,   103,    -1,   105,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    49,    50,    51,
      -1,    53,    54,    -1,    97,    98,    99,    59,    -1,    -1,
     103,     1,   105,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    76,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      -1,    31,    32,    33,    34,    35,    36,    37,     1,     1,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    -1,    31,    32,
      33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,     1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,
      -1,    53,    54,    -1,    -1,    -1,    -1,    97,    -1,    99,
      -1,    -1,    -1,   103,   104,   105,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,
      -1,    53,    54,    -1,    97,    -1,    99,    -1,    -1,    -1,
     103,   104,   105,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    76,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      -1,    31,    32,    33,    34,    35,    36,    37,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    -1,    31,    32,    33,    34,
      35,    36,    37,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    -1,    -1,    -1,    -1,    -1,    97,    -1,    99,
      -1,    -1,   102,   103,    -1,   105,    -1,    72,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    97,    -1,    99,    -1,    -1,    -1,   103,    -1,
     105,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    -1,    31,
      32,    33,    34,    35,    36,    37,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    -1,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    -1,    31,    32,    33,    34,    35,    36,
      37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    97,    -1,    99,    -1,    -1,
      -1,   103,   104,   105,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      97,    -1,    99,    -1,    -1,    -1,   103,   104,   105,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    -1,    31,    32,    33,
      34,    35,    36,    37,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    -1,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    -1,    31,    32,    33,    34,    35,    36,    37,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    97,    -1,    99,    -1,    -1,    -1,   103,
     104,   105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    97,    98,
      99,    -1,    -1,    -1,   103,    -1,   105,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,     1,    31,    32,    33,    34,    35,
      36,    37,    -1,    -1,    -1,    -1,    -1,    14,    15,    16,
      -1,    18,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,
      -1,    -1,     1,    30,    -1,    -1,    -1,    -1,    -1,    -1,
      14,    15,    16,    -1,    18,    14,    15,    16,    -1,    18,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    55,    56,
      -1,    30,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      67,    97,    -1,    99,    -1,    -1,    -1,   103,    75,   105,
      77,    55,    56,    -1,    -1,    -1,    55,    56,    -1,    -1,
      -1,    -1,    -1,    67,    -1,    -1,     1,    -1,    67,    -1,
      -1,    75,     1,    77,   101,    -1,    75,    -1,    77,    14,
      15,    16,    -1,    18,    -1,    14,    15,    16,    -1,    18,
      -1,    -1,    -1,    -1,    -1,    30,    -1,   101,    -1,     1,
      -1,    30,   101,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    14,    15,    16,    -1,    18,    -1,    -1,    -1,
      55,    56,     1,    -1,    -1,    -1,    55,    56,    30,    -1,
      -1,    -1,    67,    -1,    -1,    14,    15,    16,    67,    18,
      75,    -1,    77,    -1,    -1,    -1,    75,    -1,    77,    -1,
      -1,    30,    -1,    55,    56,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    67,   101,    -1,    -1,    -1,
      -1,    -1,   101,    75,    -1,    77,    55,    56,     1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    67,    -1,
      -1,    14,    15,    16,    -1,    18,    75,    -1,    77,   101,
      14,    15,    16,    -1,    18,    -1,    -1,    30,    -1,    -1,
       1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,
      -1,    -1,   101,    14,    15,    16,    -1,    18,    -1,    -1,
      -1,    -1,    55,    56,    -1,    -1,    -1,    -1,    -1,    30,
      -1,    55,    56,     1,    67,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    67,    77,    -1,    14,    15,    16,    -1,
      18,    75,    -1,    77,    55,    56,     1,    -1,    -1,    -1,
      -1,    -1,    30,    -1,    -1,     1,    67,    -1,   101,    14,
      15,    16,    -1,    18,    75,    -1,    77,   101,    14,    15,
      16,    -1,    18,    -1,    -1,    30,    -1,    55,    56,    -1,
      -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,    -1,    67,
     101,    -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,    77,
      55,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,
      56,     1,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      75,    67,    77,   101,    14,    15,    16,    -1,    18,    75,
      -1,    77,    -1,    -1,     1,    -1,    -1,    -1,    -1,     1,
      30,    -1,    -1,    -1,    -1,    -1,   101,    14,    15,    16,
      -1,    18,    14,    15,    16,   101,    18,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    -1,    55,    56,     1,    30,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,
      14,    15,    16,    -1,    18,    75,    -1,    77,    55,    56,
      -1,    -1,    -1,    55,    56,    -1,    30,    -1,    -1,    -1,
      67,    -1,    -1,     1,    -1,    67,    -1,    -1,    75,    -1,
      77,   101,    -1,    75,    -1,    77,    14,    15,    16,    -1,
      18,    55,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    30,    67,   101,    -1,     1,    -1,    -1,   101,
      -1,    75,    -1,    77,    14,    15,    16,    -1,    18,    14,
      15,    16,    -1,    18,    -1,    -1,    -1,    55,    56,     1,
      30,    -1,    -1,    -1,    -1,    30,    -1,   101,    -1,    67,
      -1,    -1,    14,    15,    16,    -1,    18,    75,    -1,    77,
      -1,    -1,    -1,    -1,    -1,    55,    56,    -1,    30,    -1,
      55,    56,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,
      -1,    -1,    67,   101,    -1,    75,    -1,    77,    -1,     1,
      75,    -1,    77,    55,    56,     1,    -1,    -1,    -1,    -1,
      -1,    -1,    14,    15,    16,    67,    18,    -1,    14,    15,
      16,   101,    18,    75,    -1,    77,   101,    -1,    30,    -1,
      -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,
      -1,    -1,    -1,    55,    56,     1,    -1,    -1,    -1,    55,
      56,    -1,    -1,    -1,    -1,    67,    -1,    -1,    14,    15,
      16,    67,    18,    75,    -1,    77,    -1,    -1,     1,    75,
      -1,    77,    -1,     1,    30,    -1,    -1,    -1,    -1,    -1,
      -1,    14,    15,    16,    -1,    18,    14,    15,    16,   101,
      18,    -1,    -1,    -1,    -1,   101,    -1,    30,    -1,    55,
      56,     1,    30,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    67,    -1,    -1,    14,    15,    16,    -1,    18,    75,
      -1,    77,    55,    56,    -1,    -1,    -1,    55,    56,    -1,
      30,    -1,    -1,    -1,    67,    -1,    -1,     1,    -1,    67,
      -1,    -1,    75,    -1,    77,   101,    -1,    75,    -1,    77,
      14,    15,    16,    -1,    18,    55,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    30,    67,   101,    -1,
       1,    -1,    -1,   101,    -1,    75,    -1,    77,    14,    15,
      16,    -1,    18,    14,    15,    16,    -1,    18,    -1,    -1,
      -1,    55,    56,     1,    30,    -1,    -1,    -1,    -1,    30,
      -1,   101,    -1,    67,    -1,    -1,    14,    15,    16,    -1,
      18,    75,    -1,    77,    -1,    -1,    -1,    -1,    -1,    55,
      56,    -1,    30,    -1,    55,    56,    -1,    -1,    -1,    -1,
      -1,    67,    -1,    -1,    -1,    -1,    67,   101,    -1,    75,
      -1,    77,    -1,     1,    75,    -1,    77,    55,    56,     1,
      -1,    -1,    -1,    -1,    -1,    -1,    14,    15,    16,    67,
      18,    -1,    14,    15,    16,   101,    18,    75,    -1,    77,
     101,    -1,    30,    -1,    -1,    -1,    -1,    -1,    30,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   101,    -1,    -1,    -1,    55,    56,     1,
      -1,    -1,    -1,    55,    56,    -1,    -1,    -1,    -1,    67,
      -1,    -1,    14,    15,    16,    67,    18,    75,    -1,    77,
      -1,    -1,     1,    75,    -1,    77,    -1,     1,    30,    -1,
      -1,    -1,    -1,    -1,    -1,    14,    15,    16,    -1,    18,
      14,    15,    16,   101,    18,    -1,    -1,    -1,    -1,   101,
      -1,    30,    -1,    55,    56,     1,    30,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,    14,    15,
      16,    -1,    18,    75,    -1,    77,    55,    56,    -1,    -1,
      -1,    55,    56,    -1,    30,    -1,    -1,    -1,    67,    -1,
      -1,     1,    -1,    67,    -1,    -1,    75,    -1,    77,   101,
      -1,    75,    -1,    77,    14,    15,    16,    -1,    18,    55,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    67,   101,    -1,    -1,    -1,    -1,   101,    -1,    75,
      -1,    77,    -1,    -1,    14,    15,    16,    -1,    18,    -1,
      -1,    -1,    -1,    -1,    -1,    55,    56,    -1,    -1,    -1,
      30,    -1,    -1,    -1,    -1,   101,    -1,    67,    38,    39,
      40,    41,    42,    43,    44,    75,    -1,    77,    48,    -1,
      -1,    -1,    -1,    -1,    -1,    55,    56,    14,    15,    16,
      -1,    18,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,
      -1,   101,    -1,    30,    -1,    75,    -1,    77,    -1,    -1,
      -1,    38,    39,    40,    41,    42,    43,    44,    -1,    -1,
      -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,
      -1,   101,    -1,    -1,    -1,    -1,   106,    -1,   108,   109,
      67,    14,    15,    16,    -1,    18,    -1,    -1,    75,    -1,
      77,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   101,    -1,    -1,    -1,    -1,   106,
      -1,   108,    55,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    -1,    77,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      -1,    -1,    32,    33,    34,    35,    36,    37,   101,    -1,
     103,    -1,    -1,    -1,    -1,   108,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      -1,    -1,    -1,    32,    33,    34,    35,    36,    37,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    -1,    -1,    -1,    -1,    32,    33,    34,    35,
      36,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    99,
      -1,    -1,    -1,   103,    -1,   105,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    -1,    25,    26,    27,    -1,
      -1,    -1,    -1,    32,    33,    34,    35,    36,    37,    -1,
      99,    -1,    -1,    -1,   103,    -1,   105,    -1,    -1,    -1,
      -1,    -1,    -1,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    -1,    99,    26,    27,    -1,   103,    -1,   105,
      32,    33,    34,    35,    36,    37,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    -1,    -1,    26,    27,    -1,
      -1,    -1,    -1,    32,    33,    34,    35,    36,    37,    -1,
      99,    -1,    -1,    -1,   103,    -1,   105,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    -1,    -1,    26,    27,
      -1,    -1,    -1,    -1,    32,    33,    -1,    -1,    36,    37,
      14,    15,    16,    -1,    18,    -1,    -1,    99,    -1,    -1,
      -1,   103,    -1,   105,    -1,    -1,    30,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    14,    15,    16,
      -1,    18,    -1,    -1,   103,    -1,   105,    -1,    -1,    -1,
      -1,    55,    56,    30,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    68,    69,    70,    71,    -1,    73,
      -1,    75,    -1,    77,    -1,   103,    -1,   105,    55,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      67,    -1,    -1,    -1,    -1,    -1,    -1,   101,    75,    -1,
      77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   101
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/share/bison-1.35/bison.simple"

/* Skeleton output parser for bison,

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software
   Foundation, Inc.

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

/* This is the parser code that is written into each bison parser when
   the %semantic_parser declaration is not specified in the grammar.
   It was written by Richard Stallman by simplifying the hairy parser
   used when %semantic_parser is specified.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

#if ! defined (yyoverflow) || defined (YYERROR_VERBOSE)

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
#endif /* ! defined (yyoverflow) || defined (YYERROR_VERBOSE) */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYLTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
# if YYLSP_NEEDED
  YYLTYPE yyls;
# endif
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAX (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# if YYLSP_NEEDED
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
      + 2 * YYSTACK_GAP_MAX)
# else
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAX)
# endif

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
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAX;	\
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif


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
#define YYABORT 	goto yyabortlab
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
   are run).

   When YYLLOC_DEFAULT is run, CURRENT is set the location of the
   first token.  By default, to implement support for ranges, extend
   its range to the last symbol.  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)       	\
   Current.last_line   = Rhs[N].last_line;	\
   Current.last_column = Rhs[N].last_column;
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#if YYPURE
# if YYLSP_NEEDED
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, &yylloc, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval, &yylloc)
#  endif
# else /* !YYLSP_NEEDED */
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval)
#  endif
# endif /* !YYLSP_NEEDED */
#else /* !YYPURE */
# define YYLEX			yylex ()
#endif /* !YYPURE */


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
/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
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

#ifdef YYERROR_VERBOSE

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
#endif

#line 315 "/usr/share/bison-1.35/bison.simple"


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

/* YY_DECL_VARIABLES -- depending whether we use a pure parser,
   variables are global, or local to YYPARSE.  */

#define YY_DECL_NON_LSP_VARIABLES			\
/* The lookahead symbol.  */				\
int yychar;						\
							\
/* The semantic value of the lookahead symbol. */	\
YYSTYPE yylval;						\
							\
/* Number of parse errors so far.  */			\
int yynerrs;

#if YYLSP_NEEDED
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES			\
						\
/* Location data for the lookahead symbol.  */	\
YYLTYPE yylloc;
#else
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES
#endif


/* If nonreentrant, generate the variables here. */

#if !YYPURE
YY_DECL_VARIABLES
#endif  /* !YYPURE */

int
yyparse (YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  /* If reentrant, generate the variables here. */
#if YYPURE
  YY_DECL_VARIABLES
#endif  /* !YYPURE */

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

  /* The state stack. */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;

#if YYLSP_NEEDED
  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
#endif

#if YYLSP_NEEDED
# define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
# define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  YYSIZE_T yystacksize = YYINITDEPTH;


  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
#if YYLSP_NEEDED
  YYLTYPE yyloc;
#endif

  /* When reducing, the number of symbols on the RHS of the reduced
     rule. */
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
#if YYLSP_NEEDED
  yylsp = yyls;
#endif
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

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  */
# if YYLSP_NEEDED
	YYLTYPE *yyls1 = yyls;
	/* This used to be a conditional around just the two extra args,
	   but that might be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
# else
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);
# endif
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
# if YYLSP_NEEDED
	YYSTACK_RELOCATE (yyls);
# endif
# undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
#if YYLSP_NEEDED
      yylsp = yyls + yysize - 1;
#endif

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
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yychar1 = YYTRANSLATE (yychar);

#if YYDEBUG
     /* We have to keep this `#if YYDEBUG', since we use variables
	which are defined only if `YYDEBUG' is set.  */
      if (yydebug)
	{
	  YYFPRINTF (stderr, "Next token is %d (%s",
		     yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise
	     meaning of a token, for further debugging info.  */
# ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
# endif
	  YYFPRINTF (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %d (%s), ",
	      yychar, yytname[yychar1]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

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

     Otherwise, the following line sets YYVAL to the semantic value of
     the lookahead token.  This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

#if YYLSP_NEEDED
  /* Similarly for the default location.  Let the user run additional
     commands if for instance locations are ranges.  */
  yyloc = yylsp[1-yylen];
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
#endif

#if YYDEBUG
  /* We have to keep this `#if YYDEBUG', since we use variables which
     are defined only if `YYDEBUG' is set.  */
  if (yydebug)
    {
      int yyi;

      YYFPRINTF (stderr, "Reducing via rule %d (line %d), ",
		 yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (yyi = yyprhs[yyn]; yyrhs[yyi] > 0; yyi++)
	YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
      YYFPRINTF (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif

  switch (yyn) {

case 1:
#line 269 "parser.yy"
{ CALL(yylsp[0], yylsp[0], done()); }
    break;
case 2:
#line 270 "parser.yy"
{ }
    break;
case 3:
#line 271 "parser.yy"
{ }
    break;
case 4:
#line 272 "parser.yy"
{ }
    break;
case 5:
#line 273 "parser.yy"
{ }
    break;
case 6:
#line 274 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SYSTEM));
	}
    break;
case 7:
#line 277 "parser.yy"
{ g_parameter_count = yyvsp[0].number; }
    break;
case 8:
#line 278 "parser.yy"
{ }
    break;
case 9:
#line 279 "parser.yy"
{ CALL(yylsp[0], yylsp[0], procGuard()); }
    break;
case 10:
#line 280 "parser.yy"
{ }
    break;
case 11:
#line 281 "parser.yy"
{ CALL(yylsp[0], yylsp[0], procUpdate()); }
    break;
case 12:
#line 282 "parser.yy"
{ CALL(yylsp[0], yylsp[0], done()); }
    break;
case 13:
#line 283 "parser.yy"
{ }
    break;
case 14:
#line 284 "parser.yy"
{ }
    break;
case 15:
#line 285 "parser.yy"
{ }
    break;
case 16:
#line 286 "parser.yy"
{ g_parameter_count = yyvsp[0].number; }
    break;
case 17:
#line 287 "parser.yy"
{ }
    break;
case 18:
#line 288 "parser.yy"
{ CALL(yylsp[0], yylsp[0], procGuard()); }
    break;
case 19:
#line 289 "parser.yy"
{ CALL(yylsp[0], yylsp[0], procUpdate()); }
    break;
case 20:
#line 290 "parser.yy"
{}
    break;
case 23:
#line 299 "parser.yy"
{
          CALL(yylsp[-3], yylsp[-1], instantiationBegin(yyvsp[-3].string, yyvsp[-1].string));
	}
    break;
case 24:
#line 301 "parser.yy"
{
	  CALL(yylsp[-7], yylsp[0], instantiationEnd(yyvsp[-7].string, yyvsp[-5].string, yyvsp[-2].number));
	}
    break;
case 25:
#line 304 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_ARGLIST));
	}
    break;
case 26:
#line 307 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));
	}
    break;
case 27:
#line 310 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_LPAREN));
	}
    break;
case 28:
#line 313 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_ASSIGN));
	}
    break;
case 30:
#line 320 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;
case 31:
#line 323 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_PROCID));
	}
    break;
case 32:
#line 329 "parser.yy"
{ CALL(yylsp[0], yylsp[0], process(yyvsp[0].string)); }
    break;
case 33:
#line 330 "parser.yy"
{ CALL(yylsp[0], yylsp[0], process(yyvsp[0].string)); }
    break;
case 34:
#line 331 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_PROCID_));
	}
    break;
case 40:
#line 345 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], declFuncBegin(yyvsp[-1].string, yyvsp[0].number));
	}
    break;
case 41:
#line 348 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[-1], declFuncEnd());
	}
    break;
case 42:
#line 354 "parser.yy"
{ yyval.number = 0; }
    break;
case 43:
#line 355 "parser.yy"
{ yyval.number = yyvsp[-1].number; }
    break;
case 44:
#line 356 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));
	  yyval.number = yyvsp[-2].number; 
	}
    break;
case 45:
#line 360 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));
	  yyval.number = yyvsp[-1].number; 
	}
    break;
case 46:
#line 364 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_PARAMETERS));
	  yyval.number = 0; 
	}
    break;
case 47:
#line 368 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));
	  yyval.number = 0; 
	}
    break;
case 48:
#line 380 "parser.yy"
{ yyval.number = 1; }
    break;
case 49:
#line 381 "parser.yy"
{ yyval.number = yyvsp[-2].number+1; }
    break;
case 50:
#line 382 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_PARAMETERS_));
	  yyval.number = yyvsp[-2].number;
	}
    break;
case 51:
#line 389 "parser.yy"
{
          CALL(yylsp[-3], yylsp[0], declParameter(yyvsp[-1].string, true, yyvsp[0].number));
          CALL(yylsp[-3], yylsp[0], declParameterEnd());
	}
    break;
case 52:
#line 393 "parser.yy"
{
          CALL(yylsp[-2], yylsp[0], declParameter(yyvsp[-1].string, false, yyvsp[0].number));
          CALL(yylsp[-2], yylsp[0], declParameterEnd());
	}
    break;
case 53:
#line 397 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_PARAMID));
	}
    break;
case 54:
#line 403 "parser.yy"
{ 
          CALL(yylsp[-2], yylsp[0], declVarEnd());
	}
    break;
case 55:
#line 406 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
          CALL(yylsp[-3], yylsp[0], declVarEnd());
	}
    break;
case 56:
#line 410 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_VARID));
	  CALL(yylsp[-2], yylsp[0], declVarEnd());
	}
    break;
case 59:
#line 419 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_VARID_));
	}
    break;
case 60:
#line 425 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], declVar(yyvsp[-2].string, yyvsp[-1].number, yyvsp[0].flag));
	}
    break;
case 61:
#line 431 "parser.yy"
{ yyval.flag = false; }
    break;
case 62:
#line 432 "parser.yy"
{ yyval.flag = true; }
    break;
case 63:
#line 433 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_INITIAL));
	  yyval.flag = false; 
	}
    break;
case 65:
#line 441 "parser.yy"
{	
	  CALL(yylsp[-2], yylsp[0], declInitialiserList(yyvsp[-1].number));
	}
    break;
case 66:
#line 444 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  CALL(yylsp[-3], yylsp[0], declInitialiserList(yyvsp[-2].number));
	}
    break;
case 67:
#line 448 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_INITIAL));
	  CALL(yylsp[-2], yylsp[0], declInitialiserList(0));
	}
    break;
case 68:
#line 455 "parser.yy"
{ yyval.number = 1; }
    break;
case 69:
#line 456 "parser.yy"
{ yyval.number = yyvsp[-2].number+1; }
    break;
case 70:
#line 457 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_INITIAL_));
	  yyval.number = yyvsp[-2].number+1; 
	}
    break;
case 71:
#line 464 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], declFieldInit(yyvsp[-2].string));
	}
    break;
case 72:
#line 467 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_INITIAL));
	}
    break;
case 73:
#line 470 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], declFieldInit(NULL));
	}
    break;
case 74:
#line 476 "parser.yy"
{ yyval.number=0; }
    break;
case 75:
#line 477 "parser.yy"
{ yyval.number=yyvsp[-3].number+1; }
    break;
case 76:
#line 478 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RSQBRACE));
	  yyval.number=yyvsp[-4].number+1; 
	}
    break;
case 77:
#line 482 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RSQBRACE));
	  yyval.number=yyvsp[-3].number+1; 
	}
    break;
case 78:
#line 486 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_CONST_EXP));
	  yyval.number=yyvsp[-3].number+1; 
	}
    break;
case 79:
#line 490 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_CONST_EXP));
	  yyval.number=yyvsp[-2].number+1; 
	}
    break;
case 80:
#line 497 "parser.yy"
{
	  CALL(yylsp[-3], yylsp[0], declTypeDefEnd());
	}
    break;
case 81:
#line 500 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-4], yylsp[0], declTypeDefEnd());
	}
    break;
case 82:
#line 504 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_TYPEID));
	  CALL(yylsp[-3], yylsp[0], declTypeDefEnd());  
	}
    break;
case 83:
#line 508 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_TYPE_DEF));
	  CALL(yylsp[-2], yylsp[0], declTypeDefEnd());  
	}
    break;
case 84:
#line 520 "parser.yy"
{ yyval.number = 1; }
    break;
case 85:
#line 521 "parser.yy"
{ yyval.number = yyvsp[-2].number+1; }
    break;
case 86:
#line 522 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_TYPEID_));
	  yyval.number = yyvsp[-2].number+1; 
	}
    break;
case 87:
#line 529 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], declTypeDef(yyvsp[-1].string, yyvsp[0].number));
	}
    break;
case 88:
#line 535 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], declType(yyvsp[-2].number, yyvsp[-1].string, yyvsp[0].flag));
	}
    break;
case 89:
#line 538 "parser.yy"
{ 
	  CALL(yylsp[-4], yylsp[0], declStruct(yyvsp[-4].number, yyvsp[-1].number));
	}
    break;
case 90:
#line 541 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBER));
	  CALL(yylsp[-4], yylsp[0], declStruct(yyvsp[-4].number, 0));
	}
    break;
case 91:
#line 545 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  CALL(yylsp[-3], yylsp[0], declStruct(yyvsp[-3].number, 0));
	}
    break;
case 92:
#line 549 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	}
    break;
case 93:
#line 555 "parser.yy"
{ strncpy(yyval.string, yyvsp[0].string, MAXLEN); }
    break;
case 94:
#line 556 "parser.yy"
{ strncpy(yyval.string, yyvsp[0].string, MAXLEN); }
    break;
case 95:
#line 560 "parser.yy"
{ yyval.number=yyvsp[0].number; }
    break;
case 96:
#line 561 "parser.yy"
{ yyval.number=yyvsp[-1].number+yyvsp[0].number; }
    break;
case 97:
#line 562 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBER));
	  yyval.number=yyvsp[-1].number; 
	}
    break;
case 98:
#line 569 "parser.yy"
{
	  yyval.number = yyvsp[-1].number; 
	  CALL(yylsp[-2], yylsp[0], declFieldEnd());
	}
    break;
case 99:
#line 573 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));	  
	  yyval.number = yyvsp[-2].number; 
	  CALL(yylsp[-3], yylsp[0], declFieldEnd());
	}
    break;
case 100:
#line 578 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBERID));	  
	}
    break;
case 101:
#line 581 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBERID));	  
	}
    break;
case 102:
#line 584 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBERTYPE));	  
	}
    break;
case 103:
#line 590 "parser.yy"
{ yyval.number=1; }
    break;
case 104:
#line 591 "parser.yy"
{ yyval.number=yyvsp[-2].number+1; }
    break;
case 105:
#line 592 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBERID_));
	  yyval.number=yyvsp[-2].number+1; 
	}
    break;
case 106:
#line 599 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], declField(yyvsp[-1].string, yyvsp[0].number));
	}
    break;
case 107:
#line 605 "parser.yy"
{ yyval.number = ParserBuilder::PREFIX_NONE; }
    break;
case 108:
#line 606 "parser.yy"
{ yyval.number = ParserBuilder::PREFIX_URGENT; }
    break;
case 109:
#line 607 "parser.yy"
{ yyval.number = ParserBuilder::PREFIX_BROADCAST; }
    break;
case 110:
#line 608 "parser.yy"
{ yyval.number = ParserBuilder::PREFIX_URGENT_BROADCAST; }
    break;
case 111:
#line 609 "parser.yy"
{ yyval.number = ParserBuilder::PREFIX_CONST; }
    break;
case 112:
#line 613 "parser.yy"
{ yyval.flag = false; }
    break;
case 113:
#line 614 "parser.yy"
{ yyval.flag = true; }
    break;
case 114:
#line 615 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RSQBRACE));
	  yyval.flag = true; 
	}
    break;
case 115:
#line 619 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RSQBRACE));
	  yyval.flag = true; 
	}
    break;
case 116:
#line 623 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_CONST_EXP));
	  yyval.flag = true;
	  CALL(yylsp[-4], yylsp[0], exprTrue());
	}
    break;
case 117:
#line 628 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_CONST_EXP));
	  yyval.flag = true;
	  CALL(yylsp[-4], yylsp[0], exprTrue());
	}
    break;
case 118:
#line 633 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_CONST_EXP));
	  yyval.flag = true;
	  CALL(yylsp[-2], yylsp[0], exprTrue());
	}
    break;
case 119:
#line 638 "parser.yy"
{
	    REPORT_ERROR(last_loc, TypeException(PE_CONST_EXP));
	    yyval.flag = true;
	    CALL(yylsp[-2], yylsp[-1], exprTrue());
	  }
    break;
case 120:
#line 643 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_COMMA)); 
	  yyclearin; yyerrok;
	}
    break;
case 121:
#line 647 "parser.yy"
{
	    yyval.flag = true;
	  }
    break;
case 122:
#line 650 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_COMMA)); 
	  yyclearin; yyerrok;
	  yyval.flag = true;
	  CALL(yylsp[-3], yylsp[0], exprTrue());
	}
    break;
case 123:
#line 656 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_COMMA)); 
	  yyclearin; yyerrok;
	  yyval.flag = true;
	  CALL(yylsp[-2], yylsp[0], exprTrue());
	}
    break;
case 124:
#line 662 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_CONST_EXP)); 
	  yyclearin; yyerrok;
	  yyval.flag = true;
	  CALL(yylsp[-1], yylsp[0], exprTrue());
	}
    break;
case 125:
#line 675 "parser.yy"
{ 
	  CALL(yylsp[-3], yylsp[0], procBegin(yyvsp[-2].string, yyvsp[-1].number));
	}
    break;
case 126:
#line 678 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], procEnd());
	}
    break;
case 127:
#line 681 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	}
    break;
case 128:
#line 684 "parser.yy"
{
	  utap_error(TypeException(PE_LPAREN), 
		     yylsp[0].first_line, yylsp[0].first_column, 
		     yylsp[0].last_line, yylsp[0].last_column);
	  CALL(yylsp[-2], yylsp[0], procBegin(yyvsp[-1].string, 0));
	}
    break;
case 129:
#line 689 "parser.yy"
{
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;
case 130:
#line 692 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_PROCID));	  
	}
    break;
case 137:
#line 714 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;
case 138:
#line 717 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;
case 139:
#line 720 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_STATE_DECL));
	}
    break;
case 140:
#line 723 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_STATE_DECL));
	}
    break;
case 141:
#line 726 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_STATE));
	}
    break;
case 144:
#line 734 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_STATE_DECL_));
	}
    break;
case 145:
#line 740 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], exprTrue());
	  CALL(yylsp[0], yylsp[0], procState(yyvsp[0].string));
	}
    break;
case 146:
#line 744 "parser.yy"
{ 
	  CALL(yylsp[-3], yylsp[0], procState(yyvsp[-3].string));
	}
    break;
case 147:
#line 747 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	  CALL(yylsp[-4], yylsp[0], procState(yyvsp[-4].string));
	}
    break;
case 148:
#line 751 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	  CALL(yylsp[-3], yylsp[0], procState(yyvsp[-3].string));
	}
    break;
case 149:
#line 755 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_INV));
	  CALL(yylsp[-3], yylsp[0], procState(yyvsp[-3].string));
	}
    break;
case 150:
#line 759 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_INV));
	  CALL(yylsp[-2], yylsp[0], procState(yyvsp[-2].string));
	}
    break;
case 151:
#line 766 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], procStateInit(yyvsp[-1].string));
	}
    break;
case 152:
#line 769 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-3], yylsp[0], procStateInit(yyvsp[-2].string));
	}
    break;
case 153:
#line 773 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-2], yylsp[0], procStateInit(yyvsp[-1].string));
	}
    break;
case 154:
#line 777 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;
case 155:
#line 780 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_INIT));
	}
    break;
case 158:
#line 788 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;
case 159:
#line 791 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;
case 160:
#line 794 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS_DECL));
	}
    break;
case 161:
#line 797 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS));
	}
    break;
case 164:
#line 805 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS_DECL_));
	}
    break;
case 165:
#line 811 "parser.yy"
{ 
	  strcpy(rootTransId, yyvsp[-7].string); 
	  CALL(yylsp[-7], yylsp[0], procTransition(yyvsp[-7].string, yyvsp[-5].string));
	}
    break;
case 166:
#line 815 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  strcpy(rootTransId, yyvsp[-8].string); 
	  CALL(yylsp[-8], yylsp[0], procTransition(yyvsp[-8].string, yyvsp[-6].string));
	}
    break;
case 167:
#line 820 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	}
    break;
case 168:
#line 823 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;
case 169:
#line 826 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_ARROW));
	}
    break;
case 170:
#line 832 "parser.yy"
{ 
	  CALL(yylsp[-6], yylsp[0], procTransition(rootTransId, yyvsp[-5].string));
	}
    break;
case 171:
#line 835 "parser.yy"
{ 
	  REPORT_ERROR(yylloc, TypeException(PE_RBRACE));
	  CALL(yylsp[-7], yylsp[0], procTransition(rootTransId, yyvsp[-6].string));
	}
    break;
case 172:
#line 839 "parser.yy"
{ 
	  REPORT_ERROR(yylloc, TypeException(PE_LBRACE));
	}
    break;
case 173:
#line 842 "parser.yy"
{ 
	  REPORT_ERROR(yylloc, TypeException(PE_STATEID));
	}
    break;
case 176:
#line 851 "parser.yy"
{
	  CALL(yyloc, yyloc, procGuard());
        }
    break;
case 177:
#line 854 "parser.yy"
{
	  REPORT_ERROR(yylloc, TypeException(PE_SEMICOLON));
	  CALL(yyloc, yyloc, procGuard());
	}
    break;
case 178:
#line 858 "parser.yy"
{
	  REPORT_ERROR(yylloc, TypeException(PE_GUARD_EXP));
	}
    break;
case 181:
#line 866 "parser.yy"
{
	  REPORT_ERROR(yylloc, TypeException(PE_SEMICOLON));
	}
    break;
case 182:
#line 869 "parser.yy"
{
	  REPORT_ERROR(yylloc, TypeException(PE_SEMICOLON));
	}
    break;
case 183:
#line 872 "parser.yy"
{
	  REPORT_ERROR(yylloc, TypeException(PE_SYNC_EXP));
	}
    break;
case 184:
#line 878 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], procSync(SYNC_BANG));
	}
    break;
case 185:
#line 881 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_BANG));
	  CALL(yylsp[-2], yylsp[-1], procSync(SYNC_QUE));
	}
    break;
case 186:
#line 885 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], procSync(SYNC_QUE));
	}
    break;
case 187:
#line 888 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_QUE));
	  CALL(yylsp[-2], yylsp[-1], procSync(SYNC_QUE));
	}
    break;
case 188:
#line 892 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_BANGQUE));
	  CALL(yylsp[-1], yylsp[0], procSync(SYNC_QUE));
	}
    break;
case 190:
#line 900 "parser.yy"
{
	  CALL(yyloc, yyloc, procUpdate());	  
	}
    break;
case 191:
#line 903 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_ASSIGN_EXP));
	}
    break;
case 197:
#line 917 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;
case 198:
#line 920 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;
case 199:
#line 923 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;
case 200:
#line 926 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;
case 201:
#line 932 "parser.yy"
{}
    break;
case 202:
#line 933 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;
case 203:
#line 936 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;
case 204:
#line 939 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;
case 205:
#line 942 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;
case 206:
#line 948 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], procStateCommit(yyvsp[0].string));
	}
    break;
case 207:
#line 951 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], procStateCommit(yyvsp[0].string));
	}
    break;
case 208:
#line 954 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID_));
	}
    break;
case 209:
#line 960 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], procStateUrgent(yyvsp[0].string));
	}
    break;
case 210:
#line 963 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], procStateUrgent(yyvsp[0].string));
	}
    break;
case 211:
#line 966 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID_));
	}
    break;
case 212:
#line 977 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], blockBegin());
	}
    break;
case 213:
#line 980 "parser.yy"
{ 
	  CALL(yylsp[-3], yylsp[-1], blockEnd());
	}
    break;
case 214:
#line 983 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], blockBegin());
	}
    break;
case 215:
#line 986 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_DECL_STAT));
	  CALL(yylsp[-2], yylsp[-1], blockEnd());
	}
    break;
case 222:
#line 1005 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], emptyStatement());
	}
    break;
case 223:
#line 1008 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], exprStatement());
	}
    break;
case 224:
#line 1011 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-2], yylsp[0], exprStatement());
	}
    break;
case 225:
#line 1015 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], forBegin());
	}
    break;
case 226:
#line 1018 "parser.yy"
{ 
	    CALL(yylsp[-7], yylsp[-1], forEnd());
	  }
    break;
case 227:
#line 1021 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], forBegin());
	}
    break;
case 228:
#line 1026 "parser.yy"
{ 
	    CALL(yylsp[-7], yylsp[-10], forEnd());
	  }
    break;
case 229:
#line 1029 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_LPAREN));
	  CALL(yylsp[-2], yylsp[0], forBegin());
	}
    break;
case 230:
#line 1034 "parser.yy"
{ 
	    CALL(yylsp[-7], yylsp[-10], forEnd());
	  }
    break;
case 231:
#line 1037 "parser.yy"
{
	    CALL(yylsp[-1], yylsp[0], whileBegin());
	}
    break;
case 232:
#line 1040 "parser.yy"
{ 
	    CALL(yylsp[-3], yylsp[-2], whileEnd());
	  }
    break;
case 233:
#line 1043 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));
	  CALL(yylsp[-2], yylsp[0], whileBegin());
	}
    break;
case 234:
#line 1047 "parser.yy"
{ 
	    CALL(yylsp[-3], yylsp[-1], whileEnd());
	  }
    break;
case 235:
#line 1050 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], whileBegin());
	}
    break;
case 236:
#line 1054 "parser.yy"
{ 
	    CALL(yylsp[-6], yylsp[-4], whileEnd());
	  }
    break;
case 237:
#line 1057 "parser.yy"
{ 
	    CALL(yylsp[0], yylsp[0], doWhileBegin());
	}
    break;
case 238:
#line 1060 "parser.yy"
{ 
	    CALL(yylsp[-6], yylsp[-1], doWhileEnd());
	  }
    break;
case 239:
#line 1063 "parser.yy"
{ 
	    CALL(yylsp[-1], yylsp[0], ifBegin());
	}
    break;
case 241:
#line 1067 "parser.yy"
{ 
	    CALL(yylsp[-1], yylsp[0], breakStatement());
	  }
    break;
case 242:
#line 1070 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-2], yylsp[0], breakStatement());
	}
    break;
case 243:
#line 1074 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], continueStatement());
	}
    break;
case 244:
#line 1077 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-2], yylsp[0], continueStatement());
	}
    break;
case 245:
#line 1081 "parser.yy"
{ 
	    CALL(yylsp[-3], yylsp[0], switchBegin());
	}
    break;
case 246:
#line 1084 "parser.yy"
{ 
	       CALL(yylsp[-3], yylsp[-1], switchEnd());
	   }
    break;
case 247:
#line 1087 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));
	  CALL(yylsp[-4], yylsp[0], switchBegin());
	}
    break;
case 248:
#line 1091 "parser.yy"
{ 
	    CALL(yylsp[-3], yylsp[-1], switchEnd());
	  }
    break;
case 249:
#line 1094 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-4], yylsp[0], switchBegin());
	}
    break;
case 250:
#line 1098 "parser.yy"
{ 
	    CALL(yylsp[-3], yylsp[-1], switchEnd());
	  }
    break;
case 251:
#line 1101 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], returnStatement(true));
	}
    break;
case 252:
#line 1104 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-2], yylsp[0], returnStatement(true));
	}
    break;
case 253:
#line 1108 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], returnStatement(false));
	}
    break;
case 254:
#line 1111 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR_SEMI));
	  CALL(yylsp[-1], yylsp[0], returnStatement(false));
	}
    break;
case 255:
#line 1118 "parser.yy"
{ 
	  CALL(yyloc, yyloc, ifEnd(false));
	}
    break;
case 256:
#line 1121 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], ifElse());
	}
    break;
case 257:
#line 1124 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[-1], ifEnd(true));
	  }
    break;
case 258:
#line 1127 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], ifElse());
	}
    break;
case 259:
#line 1130 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-1], yylsp[-1], ifEnd(true));
	  }
    break;
case 262:
#line 1142 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], caseBegin());
	}
    break;
case 263:
#line 1145 "parser.yy"
{ 
	    CALL(yylsp[-1], yylsp[-1], caseEnd());
	  }
    break;
case 264:
#line 1148 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], caseBegin());
	}
    break;
case 265:
#line 1151 "parser.yy"
{
	    REPORT_ERROR(last_loc, TypeException(PE_EXPR)); 
	    CALL(yylsp[-1], yylsp[-1], caseEnd());
	  }
    break;
case 266:
#line 1155 "parser.yy"
{ 
	    CALL(yylsp[-1], yylsp[0], defaultBegin());
	}
    break;
case 267:
#line 1158 "parser.yy"
{ 
	    CALL(yylsp[-1], yylsp[-1], defaultEnd());
	  }
    break;
case 268:
#line 1161 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_COLON)); 
	  CALL(yylsp[-2], yylsp[0], defaultBegin());
	}
    break;
case 269:
#line 1165 "parser.yy"
{ 
	    CALL(yylsp[-1], yylsp[-1], defaultEnd());
	  }
    break;
case 273:
#line 1177 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprComma());
	}
    break;
case 274:
#line 1180 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR_));
	}
    break;
case 275:
#line 1186 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], exprFalse());
	}
    break;
case 276:
#line 1189 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], exprTrue());
	}
    break;
case 277:
#line 1192 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], exprNat(yyvsp[0].number));
	}
    break;
case 278:
#line 1195 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], exprId(yyvsp[0].string));
	}
    break;
case 279:
#line 1198 "parser.yy"
{
	    CALL(yylsp[-1], yylsp[0], exprCallBegin(yyvsp[-1].string));	    
	  }
    break;
case 280:
#line 1200 "parser.yy"
{ 
	    CALL(yylsp[-4], yylsp[0], exprCallEnd(yyvsp[-1].number));
	}
    break;
case 281:
#line 1203 "parser.yy"
{
	    CALL(yylsp[-1], yylsp[0], exprCallBegin(yyvsp[-1].string));
	  }
    break;
case 282:
#line 1205 "parser.yy"
{   
	    REPORT_ERROR(last_loc, TypeException(PE_ARGLIST));
	    CALL(yylsp[-4], yylsp[0], exprCallEnd(0));
	}
    break;
case 283:
#line 1209 "parser.yy"
{ 
	  CALL(yylsp[-3], yylsp[0], exprArray());
	}
    break;
case 284:
#line 1212 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-3], yylsp[0], exprArray());
	}
    break;
case 286:
#line 1217 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	}
    break;
case 287:
#line 1220 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], exprPostIncrement());
	}
    break;
case 288:
#line 1223 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], exprPreIncrement());
	}
    break;
case 289:
#line 1226 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], exprPostDecrement());
	}
    break;
case 290:
#line 1229 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], exprPreDecrement());
	}
    break;
case 291:
#line 1232 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprAssignment(yyvsp[-1].number));
	}
    break;
case 292:
#line 1235 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprAssignment(yyvsp[-1].number));
	}
    break;
case 293:
#line 1239 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], exprUnary(yyvsp[-1].number));
	}
    break;
case 294:
#line 1242 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(LT));
	}
    break;
case 295:
#line 1245 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprBinary(LT));
	}
    break;
case 296:
#line 1249 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(LE));
	}
    break;
case 297:
#line 1252 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprBinary(LE));
	}
    break;
case 298:
#line 1256 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(EQ));
	}
    break;
case 299:
#line 1259 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprBinary(EQ));
	}
    break;
case 300:
#line 1263 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(NEQ));
	}
    break;
case 301:
#line 1266 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprBinary(NEQ));
	}
    break;
case 302:
#line 1270 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(GT));
	}
    break;
case 303:
#line 1273 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprBinary(GT));
	}
    break;
case 304:
#line 1277 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(GE));
	}
    break;
case 305:
#line 1280 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprTrue(); ch->exprBinary(GE));
	}
    break;
case 306:
#line 1284 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(PLUS));
	}
    break;
case 307:
#line 1287 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprTrue(); ch->exprBinary(PLUS));
	}
    break;
case 308:
#line 1291 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(MINUS));
	}
    break;
case 309:
#line 1294 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprTrue(); ch->exprBinary(MINUS));
	}
    break;
case 310:
#line 1298 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(MULT));
	}
    break;
case 311:
#line 1301 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprTrue(); ch->exprBinary(MULT));
	}
    break;
case 312:
#line 1305 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(DIV));
	}
    break;
case 313:
#line 1308 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprTrue(); ch->exprBinary(DIV));
	}
    break;
case 314:
#line 1312 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(MOD));
	}
    break;
case 315:
#line 1315 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprTrue(); ch->exprBinary(MOD));
	}
    break;
case 316:
#line 1319 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_AND));
	}
    break;
case 317:
#line 1322 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprTrue(); ch->exprBinary(BIT_AND));
	}
    break;
case 318:
#line 1326 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_OR));
	}
    break;
case 319:
#line 1329 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprTrue(); ch->exprBinary(BIT_OR));
	}
    break;
case 320:
#line 1333 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_XOR));
	}
    break;
case 321:
#line 1336 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprTrue(); ch->exprBinary(BIT_XOR));
	}
    break;
case 322:
#line 1340 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_LSHIFT));
	}
    break;
case 323:
#line 1343 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprTrue(); ch->exprBinary(BIT_LSHIFT));
	}
    break;
case 324:
#line 1347 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_RSHIFT));
	}
    break;
case 325:
#line 1350 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprTrue(); ch->exprBinary(BIT_RSHIFT));
	}
    break;
case 326:
#line 1354 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(AND));
	}
    break;
case 327:
#line 1357 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprTrue(); ch->exprBinary(AND));
	}
    break;
case 328:
#line 1361 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(OR));
	}
    break;
case 329:
#line 1364 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprTrue(); ch->exprBinary(OR));
	}
    break;
case 330:
#line 1368 "parser.yy"
{ 
	  CALL(yylsp[-4], yylsp[-2], exprInlineIf());
	}
    break;
case 331:
#line 1371 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-4], yylsp[-2], exprTrue(); ch->exprInlineIf());
	}
    break;
case 332:
#line 1375 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_COLON));
	  CALL(yylsp[-3], yylsp[0], exprTrue(); ch->exprInlineIf());
	}
    break;
case 333:
#line 1379 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprDot(yyvsp[0].string));
	}
    break;
case 334:
#line 1382 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBERID));
	}
    break;
case 335:
#line 1385 "parser.yy"
{
	  CALL(yyloc, yyloc, exprDeadlock());
	}
    break;
case 336:
#line 1388 "parser.yy"
{  
	  CALL(yylsp[-1], yylsp[-1], exprUnary(NOT));
	}
    break;
case 337:
#line 1390 "parser.yy"
{
	  CALL(yylsp[-1], yylsp[-1], exprBinary(OR));
	}
    break;
case 338:
#line 1393 "parser.yy"
{
	    CALL(yylsp[-2], yylsp[0], exprBinary(MIN));
        }
    break;
case 339:
#line 1396 "parser.yy"
{
	    CALL(yylsp[-2], yylsp[0], exprBinary(MAX));
        }
    break;
case 340:
#line 1404 "parser.yy"
{ yyval.number = ASSIGN; }
    break;
case 341:
#line 1405 "parser.yy"
{ yyval.number = ASSPLUS; }
    break;
case 342:
#line 1406 "parser.yy"
{ yyval.number = ASSMINUS; }
    break;
case 343:
#line 1407 "parser.yy"
{ yyval.number = ASSDIV; }
    break;
case 344:
#line 1408 "parser.yy"
{ yyval.number = ASSMOD; }
    break;
case 345:
#line 1409 "parser.yy"
{ yyval.number = ASSMULT; }
    break;
case 346:
#line 1410 "parser.yy"
{ yyval.number = ASSAND; }
    break;
case 347:
#line 1411 "parser.yy"
{ yyval.number = ASSOR; }
    break;
case 348:
#line 1412 "parser.yy"
{ yyval.number = ASSXOR; }
    break;
case 349:
#line 1413 "parser.yy"
{ yyval.number = ASSLSHIFT; }
    break;
case 350:
#line 1414 "parser.yy"
{ yyval.number = ASSRSHIFT; }
    break;
case 351:
#line 1419 "parser.yy"
{ yyval.number = MINUS; }
    break;
case 352:
#line 1420 "parser.yy"
{ yyval.number = NOT; }
    break;
case 353:
#line 1421 "parser.yy"
{ yyval.number = NOT; }
    break;
case 354:
#line 1426 "parser.yy"
{ yyval.number=0; }
    break;
case 355:
#line 1427 "parser.yy"
{ 
	    yyval.number=1; 
	    CALL(yylsp[0], yylsp[0], exprArg(yyval.number));
	}
    break;
case 356:
#line 1431 "parser.yy"
{ 
	    yyval.number=yyvsp[-2].number+1; 
	    CALL(yylsp[0], yylsp[0], exprArg(yyval.number));
	}
    break;
case 357:
#line 1435 "parser.yy"
{ 
	  yyval.number=yyvsp[-2].number+1; 
	  REPORT_ERROR(last_loc, TypeException(PE_ARGLIST_));
	  CALL(yylsp[0], yylsp[0], exprArg(yyval.number));
	}
    break;
case 363:
#line 1458 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], declType(ParserBuilder::PREFIX_CONST, "int", 0));
	}
    break;
case 364:
#line 1460 "parser.yy"
{ 
	  CALL(yylsp[-3], yylsp[-1], declVarEnd());
	}
    break;
case 365:
#line 1465 "parser.yy"
{ yyval.number=1; }
    break;
case 366:
#line 1466 "parser.yy"
{ yyval.number=yyvsp[-2].number+1; }
    break;
case 367:
#line 1467 "parser.yy"
{ 
	  yyval.number=yyvsp[-2].number+1; 
	  REPORT_ERROR(last_loc, TypeException(PE_CONSTID_));
	}
    break;
case 368:
#line 1474 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], declVar(yyvsp[-2].string, yyvsp[-1].number, true));
	}
    break;
case 369:
#line 1477 "parser.yy"
{
	  ch->exprTrue();
	  REPORT_ERROR(last_loc, TypeException(PE_CONST_EXP));	  
	  CALL(yylsp[-1], yylsp[0], declVar(yyvsp[-1].string, 0, true));
	}
    break;
case 370:
#line 1488 "parser.yy"
{ 
	  CALL(yylsp[-3], yylsp[0], procBegin(yyvsp[-2].string, yyvsp[-1].number));
	}
    break;
case 371:
#line 1491 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;
case 372:
#line 1494 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	  CALL(yylsp[-4], yylsp[0], procBegin(yyvsp[-3].string, yyvsp[-2].number));
	}
    break;
case 373:
#line 1498 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;
case 374:
#line 1501 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACES));
	  CALL(yylsp[-3], yylsp[0], procBegin(yyvsp[-2].string, 0));
	}
    break;
case 375:
#line 1505 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;
case 376:
#line 1508 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_PROCID));
	  CALL(yylsp[-2], yylsp[0], procBegin("_", 0));
	}
    break;
case 377:
#line 1512 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;
case 378:
#line 1515 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_PROC));
	  CALL(yylsp[-1], yylsp[0], procBegin("_", 0));
	}
    break;
case 379:
#line 1519 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;
case 380:
#line 1522 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], procBegin(yyvsp[-1].string, 0));
	}
    break;
case 381:
#line 1525 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;
case 382:
#line 1531 "parser.yy"
{ yyval.number = 0; }
    break;
case 383:
#line 1532 "parser.yy"
{ yyval.number = yyvsp[-1].number; }
    break;
case 384:
#line 1533 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));	  
	  yyval.number = yyvsp[-1].number; 
	}
    break;
case 385:
#line 1537 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_PARAMETERS));	  
	  yyval.number = 0; 
	}
    break;
case 386:
#line 1544 "parser.yy"
{ 
	  yyval.number = 1; 
	  CALL(yylsp[0], yylsp[0], declParameterEnd());
	}
    break;
case 387:
#line 1548 "parser.yy"
{ 
	  yyval.number = yyvsp[-2].number+1;
	  CALL(yylsp[-2], yylsp[0], declParameterEnd());
	}
    break;
case 388:
#line 1552 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_PARAM_DECL_));
          yyval.number = yyvsp[-2].number+1; 
	  CALL(yylsp[-2], yylsp[0], declParameterEnd());
	}
    break;
case 389:
#line 1560 "parser.yy"
{
          CALL(yylsp[-2], yylsp[0], declParameter(yyvsp[-1].string, yyvsp[0].number == 0, yyvsp[0].number));
	}
    break;
case 390:
#line 1563 "parser.yy"
{
	  CALL(yylsp[-2], yylsp[-2], declType(ParserBuilder::PREFIX_CONST, "int", false));
	  CALL(yylsp[-1], yylsp[0], declParameter(yyvsp[-1].string, false, yyvsp[0].number));
	}
    break;
case 391:
#line 1567 "parser.yy"
{ 
	  CALL(yylsp[-3], yylsp[0], declParameter(yyvsp[-1].string, yyvsp[0].number == 0, yyvsp[0].number));
	}
    break;
case 396:
#line 1583 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;
case 397:
#line 1586 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;
case 398:
#line 1589 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_STATE_DECL));
	}
    break;
case 399:
#line 1592 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_STATE_DECL));
	}
    break;
case 400:
#line 1595 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_STATE));
	}
    break;
case 403:
#line 1603 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_LOC_DECL));
	}
    break;
case 404:
#line 1609 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], exprTrue(); ch->procState(yyvsp[0].string));
	}
    break;
case 405:
#line 1612 "parser.yy"
{ 
	  CALL(yylsp[-3], yylsp[0], procState(yyvsp[-3].string));
	}
    break;
case 407:
#line 1619 "parser.yy"
{	  
	  REPORT_ERROR(last_loc, TypeException(PE_INV));
	}
    break;
case 408:
#line 1622 "parser.yy"
{	  
	  REPORT_ERROR(last_loc, TypeException(PE_INV));
	  CALL(yylsp[0], yylsp[0], exprTrue());
	}
    break;
case 409:
#line 1626 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(T_BOOL_AND));
	}
    break;
case 410:
#line 1629 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_INV_));	  
	  CALL(yylsp[-2], yylsp[0], exprTrue(); ch->exprBinary(T_BOOL_AND));
	}
    break;
case 413:
#line 1638 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;
case 414:
#line 1641 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;
case 415:
#line 1644 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS_DECL));
	}
    break;
case 416:
#line 1647 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS_DECL));
	}
    break;
case 417:
#line 1650 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS));
	}
    break;
case 420:
#line 1658 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_ALT_TRANS));	  
	}
    break;
case 421:
#line 1664 "parser.yy"
{ 
	  strcpy(rootTransId, yyvsp[-7].string);
	  CALL(yylsp[-7], yylsp[0], procTransition(yyvsp[-7].string, yyvsp[-5].string));
	}
    break;
case 422:
#line 1668 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  strcpy(rootTransId, yyvsp[-8].string);
	  CALL(yylsp[-8], yylsp[0], procTransition(yyvsp[-8].string, yyvsp[-6].string));
	}
    break;
case 423:
#line 1673 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  strcpy(rootTransId, yyvsp[-7].string); 
	  CALL(yylsp[-7], yylsp[0], procTransition(yyvsp[-7].string, yyvsp[-5].string));
	}
    break;
case 424:
#line 1678 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	  strcpy(rootTransId, yyvsp[-8].string); 
	  CALL(yylsp[-8], yylsp[0], procTransition(yyvsp[-8].string, yyvsp[-6].string));
	}
    break;
case 425:
#line 1683 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_ARROW));
	  strcpy(rootTransId, yyvsp[-8].string); 
	  CALL(yylsp[-8], yylsp[0], procTransition(yyvsp[-8].string, yyvsp[-5].string));
	}
    break;
case 426:
#line 1692 "parser.yy"
{ 
	  CALL(yylsp[-6], yylsp[0], procTransition(rootTransId, yyvsp[-5].string));
	}
    break;
case 427:
#line 1695 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  CALL(yylsp[-6], yylsp[0], procTransition(rootTransId, yyvsp[-5].string));
	}
    break;
case 428:
#line 1699 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  CALL(yylsp[-7], yylsp[0], procTransition(rootTransId, yyvsp[-6].string));
	}
    break;
case 429:
#line 1703 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	  CALL(yylsp[-7], yylsp[0], procTransition(rootTransId, yyvsp[-6].string));
	}
    break;
case 430:
#line 1707 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	  CALL(yylsp[-7], yylsp[0], procTransition(rootTransId, yyvsp[-5].string));
	}
    break;
case 431:
#line 1711 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	  CALL(yylsp[-6], yylsp[0], procTransition(rootTransId, "_"));
	}
    break;
case 434:
#line 1720 "parser.yy"
{
	  CALL(yyloc, yyloc, procGuard());
	}
    break;
case 435:
#line 1723 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yyloc, yyloc, procGuard());
	}
    break;
case 436:
#line 1727 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yyloc, yyloc, procGuard());
	}
    break;
case 437:
#line 1731 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_GUARD_EXP));
	}
    break;
case 439:
#line 1738 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(AND));
	}
    break;
case 440:
#line 1741 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_GUARD_EXP_));
	  CALL(yylsp[-2], yylsp[0], exprBinary(AND));
	}
    break;
case 445:
#line 1756 "parser.yy"
{
		ch->quit();	
	}
    break;
case 446:
#line 1759 "parser.yy"
{
		ch->property(yyvsp[-1].number, yylsp[-1].first_line);
	}
    break;
case 447:
#line 1762 "parser.yy"
{
		ch->property(LEADSTO, yylsp[-2].first_line);
	}
    break;
case 448:
#line 1767 "parser.yy"
{ yyval.number = EF; }
    break;
case 449:
#line 1768 "parser.yy"
{ yyval.number = EG; }
    break;
case 450:
#line 1769 "parser.yy"
{ yyval.number = AF; }
    break;
case 451:
#line 1770 "parser.yy"
{ yyval.number = AG; }
    break;
}

#line 705 "/usr/share/bison-1.35/bison.simple"


  yyvsp -= yylen;
  yyssp -= yylen;
#if YYLSP_NEEDED
  yylsp -= yylen;
#endif

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
#if YYLSP_NEEDED
  *++yylsp = yyloc;
#endif

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("parse error, unexpected ") + 1;
	  yysize += yystrlen (yytname[YYTRANSLATE (yychar)]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "parse error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[YYTRANSLATE (yychar)]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx)
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
#endif /* defined (YYERROR_VERBOSE) */
	yyerror ("parse error");
    }
  goto yyerrlab1;


/*--------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action |
`--------------------------------------------------*/
yyerrlab1:
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;
      YYDPRINTF ((stderr, "Discarding token %d (%s).\n",
		  yychar, yytname[yychar1]));
      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;


/*-------------------------------------------------------------------.
| yyerrdefault -- current state does not do anything special for the |
| error token.                                                       |
`-------------------------------------------------------------------*/
yyerrdefault:
#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */

  /* If its default is to accept any token, ok.  Otherwise pop it.  */
  yyn = yydefact[yystate];
  if (yyn)
    goto yydefault;
#endif


/*---------------------------------------------------------------.
| yyerrpop -- pop the current state because it cannot handle the |
| error token                                                    |
`---------------------------------------------------------------*/
yyerrpop:
  if (yyssp == yyss)
    YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#if YYLSP_NEEDED
  yylsp--;
#endif

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

/*--------------.
| yyerrhandle.  |
`--------------*/
yyerrhandle:
  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

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

/*---------------------------------------------.
| yyoverflowab -- parser overflow comes here.  |
`---------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}
#line 1772 "parser.yy"


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

