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
# define	T_RATE	321
# define	T_BEFORE	322
# define	T_AFTER	323
# define	T_COST	324
# define	T_DEADLOCK	325
# define	T_EF	326
# define	T_EG	327
# define	T_AF	328
# define	T_AG	329
# define	T_LEADSTO	330
# define	T_QUIT	331
# define	T_ERROR	332
# define	T_ID	333
# define	T_TYPENAME	334
# define	T_NAT	335
# define	T_NEW	336
# define	T_NEW_DECLARATION	337
# define	T_NEW_LOCAL_DECL	338
# define	T_NEW_INST	339
# define	T_NEW_SYSTEM	340
# define	T_NEW_PARAMETERS	341
# define	T_NEW_INVARIANT	342
# define	T_NEW_GUARD	343
# define	T_NEW_SYNC	344
# define	T_NEW_ASSIGN	345
# define	T_OLD	346
# define	T_OLD_DECLARATION	347
# define	T_OLD_LOCAL_DECL	348
# define	T_OLD_INST	349
# define	T_OLD_PARAMETERS	350
# define	T_OLD_INVARIANT	351
# define	T_OLD_GUARD	352
# define	T_OLD_ASSIGN	353
# define	T_PROPERTY	354
# define	UOPERATOR	355

#line 53 "parser.yy"


#include "libparser.hh"

using namespace std;
using namespace UTAP;
using namespace Constants;

struct Position
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

#define CALL(first,last,call) do { errorHandler->setCurrentPosition(first.first_line, first.first_column, last.last_line, last.last_column); ch->setPosition(position_t(first.first_line, first.first_column, last.last_line, last.last_column)); try { ch->call; } catch (TypeException &te) { errorHandler->handleError(te.what()); } } while (0)
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



#define	YYFINAL		807
#define	YYFLAG		-32768
#define	YYNTBASE	115

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 355 ? yytranslate[x] : 244)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     114,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   103,     2,
     105,   106,     2,     2,   111,     2,   109,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   102,   110,
       2,     2,     2,   101,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   107,     2,   108,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   112,     2,   113,     2,     2,     2,     2,
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
      96,    97,    98,    99,   100,   104
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     3,     6,     9,    12,    15,    18,    21,    24,
      27,    30,    33,    36,    39,    42,    45,    48,    51,    54,
      57,    60,    64,    65,    66,    76,    85,    93,   100,   105,
     109,   114,   118,   120,   124,   128,   129,   132,   135,   138,
     141,   144,   147,   150,   155,   156,   160,   164,   169,   174,
     175,   179,   180,   184,   185,   191,   194,   198,   203,   207,
     211,   214,   216,   220,   224,   229,   233,   236,   240,   245,
     249,   251,   255,   259,   263,   264,   267,   270,   272,   276,
     281,   285,   287,   291,   295,   299,   303,   305,   306,   311,
     317,   322,   327,   331,   336,   342,   347,   351,   353,   357,
     361,   364,   368,   374,   380,   385,   389,   391,   393,   395,
     398,   401,   405,   410,   414,   417,   420,   422,   426,   430,
     433,   434,   436,   438,   441,   443,   444,   450,   457,   463,
     469,   475,   476,   483,   484,   492,   497,   501,   504,   505,
     513,   521,   522,   529,   535,   541,   542,   545,   548,   551,
     555,   560,   564,   568,   571,   574,   576,   580,   584,   586,
     591,   597,   602,   607,   611,   615,   620,   624,   627,   629,
     630,   634,   639,   643,   646,   648,   650,   654,   658,   667,
     677,   683,   688,   692,   700,   709,   714,   718,   720,   721,
     725,   730,   734,   735,   739,   744,   748,   752,   755,   759,
     762,   766,   769,   770,   774,   778,   779,   781,   783,   786,
     790,   795,   799,   803,   806,   810,   815,   819,   823,   826,
     828,   832,   836,   838,   842,   846,   847,   853,   854,   859,
     860,   863,   866,   867,   870,   872,   874,   877,   881,   882,
     893,   894,   906,   907,   919,   920,   927,   928,   936,   937,
     945,   946,   955,   956,   964,   967,   971,   974,   978,   979,
     988,   989,   999,  1000,  1010,  1014,  1018,  1021,  1024,  1025,
    1026,  1030,  1031,  1035,  1037,  1040,  1041,  1047,  1048,  1054,
    1055,  1060,  1061,  1067,  1068,  1070,  1072,  1076,  1080,  1082,
    1084,  1086,  1088,  1089,  1095,  1096,  1102,  1107,  1112,  1116,
    1120,  1123,  1126,  1129,  1132,  1135,  1139,  1143,  1147,  1151,
    1155,  1159,  1163,  1167,  1171,  1175,  1179,  1183,  1187,  1191,
    1195,  1199,  1203,  1207,  1213,  1217,  1219,  1220,  1225,  1229,
    1233,  1235,  1239,  1241,  1243,  1245,  1247,  1249,  1251,  1253,
    1255,  1257,  1259,  1261,  1263,  1265,  1267,  1268,  1270,  1274,
    1278,  1282,  1283,  1286,  1289,  1291,  1292,  1297,  1301,  1303,
    1307,  1311,  1312,  1320,  1321,  1330,  1331,  1339,  1340,  1347,
    1348,  1355,  1358,  1362,  1366,  1370,  1372,  1376,  1380,  1384,
    1388,  1393,  1399,  1400,  1403,  1407,  1412,  1416,  1420,  1423,
    1425,  1427,  1431,  1435,  1437,  1442,  1444,  1448,  1450,  1454,
    1455,  1459,  1464,  1468,  1472,  1475,  1477,  1479,  1483,  1487,
    1496,  1506,  1515,  1525,  1535,  1543,  1551,  1560,  1569,  1578,
    1586,  1588,  1589,  1593,  1598,  1602,  1605,  1607,  1611,  1615,
    1618,  1619,  1623,  1624,  1626,  1629,  1633,  1635,  1637,  1639
};
static const short yyrhs[] =
{
      82,   116,     0,    83,   121,     0,    84,   159,     0,    85,
     117,     0,    86,   119,     0,    86,     1,     0,    87,   132,
       0,    88,   205,     0,    89,   205,     0,    90,   170,     0,
      91,   204,     0,    92,   213,     0,    93,   214,     0,    94,
     229,     0,    95,   117,     0,    96,   226,     0,    97,   233,
       0,    98,   239,     0,    99,   204,     0,   100,   240,     0,
     121,   117,   119,     0,     0,     0,   117,    79,     3,    79,
     105,   118,   212,   106,   110,     0,   117,    79,     3,    79,
     105,     1,   106,   110,     0,   117,    79,     3,    79,   105,
       1,   110,     0,   117,    79,     3,    79,     1,   110,     0,
     117,    79,     1,   110,     0,    57,   120,   110,     0,    57,
     120,     1,   110,     0,    57,     1,   110,     0,    79,     0,
     120,   111,    79,     0,   120,   111,     1,     0,     0,   121,
     129,     0,   121,   134,     0,   121,   142,     0,   121,   155,
       0,   121,   122,     0,   121,   125,     0,   121,   126,     0,
      67,   112,   123,   113,     0,     0,   123,   124,   110,     0,
      70,   102,   205,     0,    68,   112,   127,   113,     0,    69,
     112,   128,   113,     0,     0,   127,   209,   110,     0,     0,
     128,   209,   110,     0,     0,   145,   146,   131,   130,   177,
       0,   105,   106,     0,   105,   132,   106,     0,   105,   132,
       1,   106,     0,   105,   132,     1,     0,   105,     1,   106,
       0,   105,     1,     0,   133,     0,   132,   111,   133,     0,
     132,   111,     1,     0,   145,   103,    79,   141,     0,   145,
      79,   141,     0,   145,     1,     0,   145,   135,   110,     0,
     145,   135,     1,   110,     0,   145,     1,   110,     0,   136,
       0,   135,   111,   136,     0,   135,   111,     1,     0,   146,
     141,   137,     0,     0,     3,   138,     0,     3,     1,     0,
     205,     0,   112,   139,   113,     0,   112,   139,     1,   113,
       0,   112,     1,   113,     0,   140,     0,   139,   111,   140,
       0,   139,   111,     1,     0,   146,   102,   138,     0,   146,
     102,     1,     0,   138,     0,     0,   141,   107,   205,   108,
       0,   141,   107,   205,     1,   108,     0,   141,   107,   205,
       1,     0,   141,   107,     1,   108,     0,   141,   107,     1,
       0,    49,   145,   143,   110,     0,    49,   145,   143,     1,
     110,     0,    49,   145,     1,   110,     0,    49,     1,   110,
       0,   144,     0,   143,   111,   144,     0,   143,   111,     1,
       0,   146,   141,     0,   151,    80,   152,     0,   151,    50,
     112,   147,   113,     0,   151,    50,   112,     1,   113,     0,
     151,    50,   112,     1,     0,   151,    50,     1,     0,    79,
       0,    80,     0,   148,     0,   147,   148,     0,   147,     1,
       0,   145,   149,   110,     0,   145,   149,     1,   110,     0,
     145,     1,   110,     0,   145,     1,     0,     1,   110,     0,
     150,     0,   149,   111,   150,     0,   149,   111,     1,     0,
     146,   141,     0,     0,    53,     0,    54,     0,    53,    54,
       0,    51,     0,     0,   107,   205,   111,   205,   108,     0,
     107,   205,   111,   205,     1,   108,     0,   107,   205,   111,
     205,     1,     0,   107,   205,   111,     1,   108,     0,   107,
       1,   111,   205,   108,     0,     0,   107,     1,   111,   153,
       1,   108,     0,     0,   107,   205,     1,   111,   154,   205,
     108,     0,   107,   205,     1,   108,     0,   107,   205,     1,
       0,   107,     1,     0,     0,    58,   146,   131,   112,   156,
     158,   113,     0,    58,   146,   131,     1,   112,   158,   113,
       0,     0,    58,   146,   112,   157,   158,   113,     0,    58,
       1,   112,   158,   113,     0,   159,   160,   172,   163,   164,
       0,     0,   159,   129,     0,   159,   134,     0,   159,   142,
       0,    59,   161,   110,     0,    59,   161,     1,   110,     0,
      59,   161,     1,     0,    59,     1,   110,     0,    59,     1,
       0,     1,   110,     0,   162,     0,   161,   111,   162,     0,
     161,   111,     1,     0,    79,     0,    79,   112,   205,   113,
       0,    79,   112,   205,     1,   113,     0,    79,   112,   205,
       1,     0,    79,   112,     1,   113,     0,    79,   112,     1,
       0,    61,    79,   110,     0,    61,    79,     1,   110,     0,
      61,    79,     1,     0,    61,     1,     0,     1,     0,     0,
      62,   165,   110,     0,    62,   165,     1,   110,     0,    62,
     165,     1,     0,    62,     1,     0,     1,     0,   166,     0,
     165,   111,   167,     0,   165,   111,     1,     0,    79,    63,
      79,   112,   168,   169,   171,   113,     0,    79,    63,    79,
     112,   168,   169,   171,     1,   110,     0,    79,    63,    79,
       1,   113,     0,    79,    63,     1,   113,     0,    79,     1,
     113,     0,    63,    79,   112,   168,   169,   171,   113,     0,
      63,    79,   112,   168,   169,   171,     1,   113,     0,    63,
      79,     1,   113,     0,    63,     1,   113,     0,   166,     0,
       0,    64,   205,   110,     0,    64,   205,     1,   110,     0,
      64,     1,   110,     0,     0,    65,   170,   110,     0,    65,
     170,     1,   110,     0,    65,   170,     1,     0,    65,     1,
     110,     0,   205,    14,     0,   205,     1,    14,     0,   205,
     101,     0,   205,     1,   101,     0,   205,     1,     0,     0,
      66,   204,   110,     0,    66,     1,   110,     0,     0,   173,
       0,   174,     0,   173,   174,     0,    60,   175,   110,     0,
      60,   175,     1,   110,     0,    60,   175,     1,     0,    60,
       1,   110,     0,    60,     1,     0,    53,   176,   110,     0,
      53,   176,     1,   110,     0,    53,   176,     1,     0,    53,
       1,   110,     0,    53,     1,     0,    79,     0,   175,   111,
      79,     0,   175,   111,     1,     0,    79,     0,   176,   111,
      79,     0,   176,   111,     1,     0,     0,   112,   178,   180,
     181,   113,     0,     0,   112,   179,     1,   113,     0,     0,
     180,   134,     0,   180,   142,     0,     0,   181,   182,     0,
     177,     0,   110,     0,   205,   110,     0,   205,     1,   110,
       0,     0,    38,   105,   183,   204,   110,   204,   110,   204,
     106,   182,     0,     0,    38,   105,     1,   184,   203,   110,
     203,   110,   203,   106,   182,     0,     0,    38,     1,   105,
     185,   203,   110,   203,   110,   203,   106,   182,     0,     0,
      39,   105,   186,   204,   106,   182,     0,     0,    39,     1,
     105,   187,   204,   106,   182,     0,     0,    39,   105,     1,
     188,   204,   106,   182,     0,     0,    40,   189,   182,    39,
     105,   204,   106,   110,     0,     0,    44,   105,   190,   204,
     106,   182,   194,     0,    41,   110,     0,    41,     1,   110,
       0,    42,   110,     0,    42,     1,   110,     0,     0,    43,
     105,   204,   106,   191,   112,   197,   113,     0,     0,    43,
       1,   105,   204,   106,   192,   112,   197,   113,     0,     0,
      43,   105,     1,   204,   106,   193,   112,   197,   113,     0,
      48,   205,   110,     0,    48,   205,     1,     0,    48,   110,
       0,    48,     1,     0,     0,     0,    45,   195,   182,     0,
       0,    45,   196,     1,     0,   198,     0,   197,   198,     0,
       0,    46,   205,   102,   199,   181,     0,     0,    46,     1,
     102,   200,   181,     0,     0,    47,   102,   201,   181,     0,
       0,    47,     1,   102,   202,   181,     0,     0,   204,     0,
     205,     0,   204,   111,   205,     0,   204,   111,     1,     0,
      56,     0,    55,     0,    81,     0,    79,     0,     0,    79,
     105,   206,   212,   106,     0,     0,    79,   105,   207,     1,
     106,     0,   205,   107,   205,   108,     0,   205,   107,     1,
     108,     0,   105,   205,   106,     0,   105,     1,   106,     0,
     205,    15,     0,    15,   205,     0,   205,    16,     0,    16,
     205,     0,   211,   205,     0,   205,    32,   205,     0,   205,
      33,   205,     0,   205,    34,   205,     0,   205,    35,   205,
       0,   205,    37,   205,     0,   205,    36,   205,     0,   205,
      17,   205,     0,   205,    18,   205,     0,   205,    19,   205,
       0,   205,    20,   205,     0,   205,    23,   205,     0,   205,
     103,   205,     0,   205,    24,   205,     0,   205,    25,   205,
       0,   205,    26,   205,     0,   205,    27,   205,     0,   205,
      28,   205,     0,   205,    29,   205,     0,   205,   101,   205,
     102,   205,     0,   205,   109,    79,     0,    71,     0,     0,
     205,    31,   208,   205,     0,   205,    21,   205,     0,   205,
      22,   205,     0,   209,     0,   205,   210,   205,     0,     3,
       0,     4,     0,     5,     0,     7,     0,     8,     0,     6,
       0,    10,     0,     9,     0,    11,     0,    12,     0,    13,
       0,    18,     0,    14,     0,    30,     0,     0,   205,     0,
     212,   111,   205,     0,   212,   111,     1,     0,   214,   117,
     119,     0,     0,   214,   215,     0,   214,   219,     0,   134,
       0,     0,    52,   216,   217,   110,     0,    52,     1,   110,
       0,   218,     0,   217,   111,   218,     0,    79,   141,   138,
       0,     0,    58,   146,   225,   112,   220,   228,   113,     0,
       0,    58,   146,   225,     1,   112,   221,   228,   113,     0,
       0,    58,   146,     1,   112,   222,   228,   113,     0,     0,
      58,     1,   112,   223,   228,   113,     0,     0,    58,   146,
     112,   224,   228,   113,     0,   105,   106,     0,   105,   226,
     106,     0,   105,   226,     1,     0,   105,     1,   106,     0,
     227,     0,   226,   110,   227,     0,   226,   110,     1,     0,
     145,    79,   141,     0,    52,    79,   141,     0,   227,   111,
      79,   141,     0,   229,   230,   172,   163,   234,     0,     0,
     229,   215,     0,    59,   231,   110,     0,    59,   231,     1,
     110,     0,    59,   231,     1,     0,    59,     1,   110,     0,
      59,     1,     0,     1,     0,   232,     0,   231,   111,   232,
       0,   231,   111,     1,     0,    79,     0,    79,   112,   233,
     113,     0,   205,     0,   205,     1,   111,     0,     1,     0,
     233,   111,   205,     0,     0,    62,   235,   110,     0,    62,
     235,     1,   110,     0,    62,   235,     1,     0,    62,     1,
     110,     0,    62,     1,     0,     1,     0,   236,     0,   235,
     111,   237,     0,   235,   111,     1,     0,    79,    63,    79,
     112,   238,   169,   171,   113,     0,    79,    63,    79,   112,
     238,   169,   171,     1,   113,     0,    79,    63,    79,   112,
     238,   169,   171,     1,     0,    79,    63,    79,     1,   112,
     238,   169,   171,   113,     0,    79,     1,    63,    79,   112,
     238,   169,   171,   113,     0,    63,    79,   112,   238,   169,
     171,   113,     0,    63,    79,   112,   238,   169,   171,     1,
       0,    63,    79,   112,   238,   169,   171,     1,   113,     0,
      63,    79,     1,   112,   238,   169,   171,   113,     0,    63,
       1,    79,   112,   238,   169,   171,   113,     0,    63,     1,
     112,   238,   169,   171,   113,     0,   236,     0,     0,    64,
     239,   110,     0,    64,   239,     1,   110,     0,    64,   239,
       1,     0,    64,     1,     0,   205,     0,   239,   111,   205,
       0,   239,   111,     1,     0,   241,   242,     0,     0,   241,
     242,   114,     0,     0,    77,     0,   243,   205,     0,   205,
      76,   205,     0,    72,     0,    73,     0,    74,     0,    75,
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
     342,   343,   344,   347,   349,   351,   353,   356,   358,   360,
     362,   366,   368,   372,   372,   381,   383,   384,   388,   392,
     396,   407,   409,   410,   416,   421,   425,   430,   434,   438,
     444,   446,   447,   452,   458,   460,   461,   467,   469,   472,
     476,   482,   484,   485,   491,   495,   498,   503,   505,   506,
     510,   514,   518,   524,   528,   532,   536,   547,   549,   550,
     556,   562,   566,   569,   573,   577,   582,   584,   587,   589,
     590,   596,   601,   606,   609,   612,   617,   619,   620,   626,
     632,   634,   635,   636,   637,   640,   642,   643,   647,   651,
     656,   661,   661,   671,   671,   678,   684,   690,   702,   702,
     709,   712,   712,   720,   729,   733,   735,   736,   737,   740,
     742,   745,   748,   751,   754,   759,   761,   762,   767,   772,
     775,   779,   783,   787,   793,   797,   801,   805,   808,   813,
     815,   816,   819,   822,   825,   830,   832,   833,   838,   843,
     848,   851,   854,   859,   863,   867,   870,   873,   877,   879,
     882,   886,   891,   893,   894,   897,   900,   905,   909,   913,
     916,   920,   926,   928,   931,   936,   938,   939,   940,   943,
     945,   948,   951,   954,   959,   961,   964,   967,   970,   975,
     979,   982,   987,   991,   994,  1004,  1004,  1011,  1011,  1020,
    1022,  1023,  1026,  1028,  1031,  1033,  1036,  1039,  1043,  1043,
    1049,  1049,  1057,  1057,  1065,  1065,  1071,  1071,  1078,  1078,
    1085,  1085,  1091,  1091,  1095,  1098,  1102,  1105,  1109,  1109,
    1115,  1115,  1122,  1122,  1129,  1132,  1136,  1139,  1145,  1149,
    1149,  1155,  1155,  1164,  1166,  1169,  1169,  1176,  1176,  1183,
    1183,  1189,  1189,  1198,  1200,  1203,  1205,  1208,  1213,  1217,
    1220,  1223,  1226,  1226,  1231,  1231,  1237,  1240,  1244,  1245,
    1248,  1251,  1254,  1257,  1260,  1263,  1266,  1269,  1272,  1275,
    1278,  1281,  1284,  1287,  1290,  1293,  1296,  1299,  1302,  1305,
    1308,  1311,  1314,  1317,  1320,  1323,  1326,  1326,  1331,  1334,
    1337,  1340,  1345,  1348,  1349,  1350,  1351,  1352,  1353,  1354,
    1355,  1356,  1357,  1360,  1363,  1364,  1367,  1370,  1374,  1378,
    1389,  1393,  1395,  1396,  1399,  1401,  1401,  1406,  1408,  1410,
    1413,  1422,  1422,  1429,  1429,  1436,  1436,  1443,  1443,  1450,
    1450,  1458,  1460,  1461,  1465,  1471,  1476,  1480,  1486,  1491,
    1496,  1502,  1506,  1508,  1511,  1513,  1516,  1519,  1522,  1525,
    1530,  1532,  1533,  1538,  1542,  1547,  1549,  1552,  1556,  1561,
    1563,  1564,  1567,  1570,  1573,  1576,  1581,  1583,  1584,  1589,
    1594,  1599,  1604,  1609,  1617,  1621,  1625,  1629,  1633,  1637,
    1641,  1644,  1646,  1649,  1653,  1657,  1662,  1664,  1667,  1673,
    1676,  1678,  1680,  1682,  1685,  1688,  1692,  1694,  1695,  1696
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
  "T_RATE", "T_BEFORE", "T_AFTER", "T_COST", "T_DEADLOCK", "T_EF", "T_EG", 
  "T_AF", "T_AG", "T_LEADSTO", "T_QUIT", "T_ERROR", "T_ID", "T_TYPENAME", 
  "T_NAT", "T_NEW", "T_NEW_DECLARATION", "T_NEW_LOCAL_DECL", "T_NEW_INST", 
  "T_NEW_SYSTEM", "T_NEW_PARAMETERS", "T_NEW_INVARIANT", "T_NEW_GUARD", 
  "T_NEW_SYNC", "T_NEW_ASSIGN", "T_OLD", "T_OLD_DECLARATION", 
  "T_OLD_LOCAL_DECL", "T_OLD_INST", "T_OLD_PARAMETERS", "T_OLD_INVARIANT", 
  "T_OLD_GUARD", "T_OLD_ASSIGN", "T_PROPERTY", "'?'", "':'", "'&'", 
  "UOPERATOR", "'('", "')'", "'['", "']'", "'.'", "';'", "','", "'{'", 
  "'}'", "'\\n'", "Uppaal", "XTA", "Inst", "@1", "System", "ProcessList", 
  "Declaration", "RateDecl", "RateList", "Rate", "BeforeUpdateDecl", 
  "AfterUpdateDecl", "BeforeAssignmentList", "AfterAssignmentList", 
  "FunctionDecl", "@2", "OptionalParameterList", "ParameterList", 
  "Parameter", "VariableDecl", "DeclIdList", "DeclId", "VarInit", 
  "Initializer", "FieldInitList", "FieldInit", "ArrayDecl", "TypeDecl", 
  "TypeIdList", "TypeId", "Type", "Id", "FieldDeclList", "FieldDecl", 
  "FieldDeclIdList", "FieldDeclId", "TypePrefix", "Range", "@3", "@4", 
  "ProcDecl", "@5", "@6", "ProcBody", "ProcLocalDeclList", "States", 
  "StateDeclList", "StateDecl", "Init", "Transitions", "TransitionList", 
  "Transition", "TransitionOpt", "Guard", "Sync", "SyncExpr", "Assign", 
  "LocFlags", "Commit", "Urgent", "CStateList", "UStateList", "Block", 
  "@7", "@8", "BlockLocalDeclList", "StatementList", "Statement", "@9", 
  "@10", "@11", "@12", "@13", "@14", "@15", "@16", "@17", "@18", "@19", 
  "ElsePart", "@20", "@21", "SwitchCaseList", "SwitchCase", "@22", "@23", 
  "@24", "@25", "ExprList0", "ExprList", "Expression", "@26", "@27", 
  "@28", "Assignment", "AssignOp", "UnaryOp", "ArgList", "OldXTA", 
  "OldDeclaration", "OldVarDecl", "@29", "OldConstDeclIdList", 
  "OldConstDeclId", "OldProcDecl", "@30", "@31", "@32", "@33", "@34", 
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
       0,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   116,   117,   118,   117,   117,   117,   117,   117,   119,
     119,   119,   120,   120,   120,   121,   121,   121,   121,   121,
     121,   121,   121,   122,   123,   123,   124,   125,   126,   127,
     127,   128,   128,   130,   129,   131,   131,   131,   131,   131,
     131,   132,   132,   132,   133,   133,   133,   134,   134,   134,
     135,   135,   135,   136,   137,   137,   137,   138,   138,   138,
     138,   139,   139,   139,   140,   140,   140,   141,   141,   141,
     141,   141,   141,   142,   142,   142,   142,   143,   143,   143,
     144,   145,   145,   145,   145,   145,   146,   146,   147,   147,
     147,   148,   148,   148,   148,   148,   149,   149,   149,   150,
     151,   151,   151,   151,   151,   152,   152,   152,   152,   152,
     152,   153,   152,   154,   152,   152,   152,   152,   156,   155,
     155,   157,   155,   155,   158,   159,   159,   159,   159,   160,
     160,   160,   160,   160,   160,   161,   161,   161,   162,   162,
     162,   162,   162,   162,   163,   163,   163,   163,   163,   164,
     164,   164,   164,   164,   164,   165,   165,   165,   166,   166,
     166,   166,   166,   167,   167,   167,   167,   167,   168,   168,
     168,   168,   169,   169,   169,   169,   169,   170,   170,   170,
     170,   170,   171,   171,   171,   172,   172,   172,   172,   173,
     173,   173,   173,   173,   174,   174,   174,   174,   174,   175,
     175,   175,   176,   176,   176,   178,   177,   179,   177,   180,
     180,   180,   181,   181,   182,   182,   182,   182,   183,   182,
     184,   182,   185,   182,   186,   182,   187,   182,   188,   182,
     189,   182,   190,   182,   182,   182,   182,   182,   191,   182,
     192,   182,   193,   182,   182,   182,   182,   182,   194,   195,
     194,   196,   194,   197,   197,   199,   198,   200,   198,   201,
     198,   202,   198,   203,   203,   204,   204,   204,   205,   205,
     205,   205,   206,   205,   207,   205,   205,   205,   205,   205,
     205,   205,   205,   205,   205,   205,   205,   205,   205,   205,
     205,   205,   205,   205,   205,   205,   205,   205,   205,   205,
     205,   205,   205,   205,   205,   205,   208,   205,   205,   205,
     205,   209,   210,   210,   210,   210,   210,   210,   210,   210,
     210,   210,   210,   211,   211,   211,   212,   212,   212,   212,
     213,   214,   214,   214,   215,   216,   215,   215,   217,   217,
     218,   220,   219,   221,   219,   222,   219,   223,   219,   224,
     219,   225,   225,   225,   225,   226,   226,   226,   227,   227,
     227,   228,   229,   229,   230,   230,   230,   230,   230,   230,
     231,   231,   231,   232,   232,   233,   233,   233,   233,   234,
     234,   234,   234,   234,   234,   234,   235,   235,   235,   236,
     236,   236,   236,   236,   237,   237,   237,   237,   237,   237,
     237,   238,   238,   238,   238,   238,   239,   239,   239,   240,
     241,   241,   242,   242,   242,   242,   243,   243,   243,   243
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     3,     0,     0,     9,     8,     7,     6,     4,     3,
       4,     3,     1,     3,     3,     0,     2,     2,     2,     2,
       2,     2,     2,     4,     0,     3,     3,     4,     4,     0,
       3,     0,     3,     0,     5,     2,     3,     4,     3,     3,
       2,     1,     3,     3,     4,     3,     2,     3,     4,     3,
       1,     3,     3,     3,     0,     2,     2,     1,     3,     4,
       3,     1,     3,     3,     3,     3,     1,     0,     4,     5,
       4,     4,     3,     4,     5,     4,     3,     1,     3,     3,
       2,     3,     5,     5,     4,     3,     1,     1,     1,     2,
       2,     3,     4,     3,     2,     2,     1,     3,     3,     2,
       0,     1,     1,     2,     1,     0,     5,     6,     5,     5,
       5,     0,     6,     0,     7,     4,     3,     2,     0,     7,
       7,     0,     6,     5,     5,     0,     2,     2,     2,     3,
       4,     3,     3,     2,     2,     1,     3,     3,     1,     4,
       5,     4,     4,     3,     3,     4,     3,     2,     1,     0,
       3,     4,     3,     2,     1,     1,     3,     3,     8,     9,
       5,     4,     3,     7,     8,     4,     3,     1,     0,     3,
       4,     3,     0,     3,     4,     3,     3,     2,     3,     2,
       3,     2,     0,     3,     3,     0,     1,     1,     2,     3,
       4,     3,     3,     2,     3,     4,     3,     3,     2,     1,
       3,     3,     1,     3,     3,     0,     5,     0,     4,     0,
       2,     2,     0,     2,     1,     1,     2,     3,     0,    10,
       0,    11,     0,    11,     0,     6,     0,     7,     0,     7,
       0,     8,     0,     7,     2,     3,     2,     3,     0,     8,
       0,     9,     0,     9,     3,     3,     2,     2,     0,     0,
       3,     0,     3,     1,     2,     0,     5,     0,     5,     0,
       4,     0,     5,     0,     1,     1,     3,     3,     1,     1,
       1,     1,     0,     5,     0,     5,     4,     4,     3,     3,
       2,     2,     2,     2,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     5,     3,     1,     0,     4,     3,     3,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     1,     3,     3,
       3,     0,     2,     2,     1,     0,     4,     3,     1,     3,
       3,     0,     7,     0,     8,     0,     7,     0,     6,     0,
       6,     2,     3,     3,     3,     1,     3,     3,     3,     3,
       4,     5,     0,     2,     3,     4,     3,     3,     2,     1,
       1,     3,     3,     1,     4,     1,     3,     1,     3,     0,
       3,     4,     3,     3,     2,     1,     1,     3,     3,     8,
       9,     8,     9,     9,     7,     7,     8,     8,     8,     7,
       1,     0,     3,     4,     3,     2,     1,     3,     3,     2,
       0,     3,     0,     1,     2,     3,     1,     1,     1,     1
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       0,    35,    35,   145,    22,     0,   120,     0,     0,     0,
       0,   351,   351,   382,    22,   120,     0,     0,     0,   430,
       1,    22,   120,   120,     4,     6,     0,     5,   124,   121,
     122,     7,    61,     0,     0,   344,     0,     0,   343,   345,
     289,   288,   325,   291,   290,     0,     8,   330,     0,     9,
      10,     0,    11,   285,    12,    22,   120,   120,    15,     0,
       0,    16,   375,   397,     0,    17,   426,    18,    19,    20,
     432,     0,     0,     0,     0,     0,     0,    40,    41,    42,
      36,    37,    38,     0,    39,   146,   147,   148,     0,     0,
      32,     0,   123,     0,    66,    87,     0,     0,   125,   301,
     303,   292,     0,     0,   332,   333,   334,   337,   335,   336,
     339,   338,   340,   341,   342,   300,   302,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     326,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   304,   201,   197,   199,     0,     0,     0,     0,
     354,     0,   352,   353,   383,    87,    87,     0,     0,     0,
       0,     0,   436,   437,   438,   439,   433,     0,   429,     0,
       0,     0,     0,   106,   107,     0,    44,    49,    51,    21,
       0,     0,    70,    87,     0,     0,    31,     0,    29,     0,
      63,    62,    65,    87,   105,     0,     0,   101,   346,     0,
     299,   298,   311,   312,   313,   314,   328,   329,   315,   317,
     318,   319,   320,   321,   322,     0,   305,   306,   307,   308,
     310,   309,     0,   316,     0,     0,   324,   331,   198,   200,
     287,   286,     0,     0,     0,     0,   350,    87,   379,   378,
     377,   376,    87,   396,   398,   428,   427,     0,   431,   434,
      96,     0,     0,    97,    87,   145,     0,   141,     0,     0,
       0,     0,    69,     0,    67,     0,    53,    74,    28,     0,
      30,    34,    33,     0,    64,   104,     0,     0,   108,   137,
       0,   347,     0,     0,   327,     0,   297,   296,   357,    87,
       0,   358,   367,     0,     0,   369,     0,   380,   435,    95,
       0,    93,     0,   100,     0,     0,    60,    55,     0,   145,
       0,   138,     0,    43,     0,    47,     0,   330,    48,   330,
      68,    72,    71,     0,     0,    73,     0,     0,    92,     0,
     115,   103,   114,    87,     0,   116,   110,   102,   109,   131,
     136,     0,   293,     0,   295,   323,     0,   356,     0,   382,
     365,     0,   371,     0,   382,     0,   361,    94,    99,    98,
     143,     0,     0,   205,    59,    58,    56,     0,   145,   145,
       0,    45,    50,    52,   225,    54,    76,     0,    75,    77,
      27,     0,   346,    91,    90,    88,   113,   119,     0,   111,
       0,     0,     0,   135,   133,     0,     0,   349,   348,   360,
     359,     0,     0,   382,   374,   373,   372,     0,   363,   382,
     154,   153,   158,     0,   155,     0,     0,     0,   206,   207,
      57,   142,     0,     0,    46,   229,     0,     0,   291,    86,
       0,    81,     0,     0,    26,     0,    89,   112,   118,   117,
       0,   130,     0,   129,   128,   126,   368,   389,     0,   205,
       0,   370,   382,     0,   152,     0,   151,   149,     0,   218,
     222,     0,   213,   219,     0,   168,     0,     0,   208,   140,
     139,   232,     0,    80,     0,     0,    78,     0,    25,     0,
     132,     0,   127,   388,   393,     0,   390,     0,   366,     0,
     362,   163,     0,   150,   157,   156,   217,   216,   214,     0,
     212,   211,   209,     0,   167,     0,   174,     0,   144,   230,
     231,     0,   228,    79,    83,    82,    85,    84,    24,   134,
     387,     0,   386,   384,     0,     0,   364,   162,   161,   159,
     215,   224,   223,   210,   221,   220,   166,   164,   173,     0,
       0,   175,     0,     0,   250,     0,     0,     0,     0,     0,
     235,   226,   234,   233,     0,     0,   385,   392,   391,   405,
       0,   381,   160,   165,     0,     0,   172,   170,     0,     0,
       0,     0,     0,     0,     0,   254,     0,   256,     0,     0,
     252,   267,   266,     0,     0,   236,   394,   404,     0,     0,
     406,   182,     0,     0,   171,   177,     0,   187,   176,   242,
     240,     0,   246,   248,     0,     0,   255,   257,     0,     0,
       0,     0,   265,   264,   237,   403,     0,     0,   402,   400,
       0,   181,     0,   188,     0,     0,   283,   283,     0,     0,
       0,     0,     0,     0,     0,   258,     0,     0,     0,   401,
     408,     0,   420,   407,   180,     0,   192,   186,     0,   188,
       0,   284,     0,     0,     0,     0,     0,     0,   260,   262,
       0,     0,     0,     0,   421,     0,     0,     0,     0,     0,
     202,   185,   192,   283,   283,     0,     0,     0,   245,     0,
       0,     0,     0,   268,   421,   421,     0,   192,     0,   421,
       0,   421,   191,     0,   189,     0,     0,     0,     0,   202,
       0,     0,     0,   247,   249,     0,     0,     0,     0,     0,
       0,   273,   269,   253,   192,   192,   425,     0,   202,   421,
     192,   421,   192,   190,   196,   195,   193,     0,     0,     0,
     178,     0,   283,   283,     0,   251,     0,     0,     0,     0,
       0,   279,   259,   274,     0,     0,   202,   202,   424,   422,
       0,   192,   202,   192,   202,   194,   204,   203,   179,     0,
     183,     0,     0,     0,   261,   263,   277,   275,   281,   232,
     270,   272,     0,     0,   423,   411,   409,   202,     0,   202,
       0,   184,     0,     0,   239,   232,   232,   232,   280,   413,
     412,   410,     0,   419,     0,   415,   414,   243,   241,   278,
     276,   282,   418,   417,   416,     0,     0,     0
};

static const short yydefgoto[] =
{
     805,    20,    24,   382,    27,    91,    21,    77,   259,   314,
      78,    79,   260,   261,    80,   323,   258,    31,    32,   150,
     181,   182,   325,   429,   430,   431,   267,    82,   252,   253,
     151,   237,   277,   278,   334,   335,    34,   197,   391,   442,
      84,   369,   309,   304,   305,   363,   413,   414,   467,   508,
     540,   541,   598,   646,   670,    50,   698,   417,   418,   419,
     464,   461,   552,   425,   426,   471,   511,   553,   601,   627,
     626,   604,   629,   630,   573,   611,   660,   680,   681,   713,
     744,   745,   710,   711,   786,   785,   769,   787,   650,   651,
      53,   198,   199,   215,    47,   141,    48,   282,    54,    55,
     152,   233,   290,   291,   153,   409,   452,   403,   349,   354,
     296,    61,    62,   401,   402,   449,   485,   486,    65,   561,
     589,   590,   643,   687,    67,    69,    70,   168,   169
};

static const short yypact[] =
{
    1237,-32768,-32768,-32768,-32768,   233,   698,  2560,  2560,  2560,
    2560,-32768,-32768,-32768,-32768,   277,  1733,  2560,  2560,-32768,
  -32768,   999,   729,   750,   -52,-32768,    15,-32768,-32768,     7,
  -32768,   -63,-32768,   240,    -8,-32768,  2560,  2560,-32768,-32768,
  -32768,-32768,-32768,   -38,-32768,  1744,  1704,-32768,  2560,  1704,
  -32768,   992,   -12,  1704,-32768,   869,  1038,  1129,   -52,   179,
     186,   166,   187,-32768,   373,   302,  1704,   316,   -12,-32768,
    2555,   580,   232,   319,   342,   344,   -11,-32768,-32768,-32768,
  -32768,-32768,-32768,   292,-32768,-32768,-32768,-32768,    74,   369,
  -32768,    75,-32768,   993,-32768,-32768,   392,    52,   362,   305,
     305,   484,   446,  1243,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,  2560,  2560,  2560,
    2560,  2560,  2560,  2560,  2560,  2560,  2560,  2560,  2560,  2560,
  -32768,  2560,  2560,  2560,  2560,  2560,  2560,  2560,  2560,  1765,
     475,  2560,   305,     1,-32768,  2560,  1776,   263,   343,   -11,
  -32768,   292,-32768,-32768,-32768,-32768,-32768,   889,   506,   496,
    2560,  1836,-32768,-32768,-32768,-32768,-32768,  1278,   504,  2560,
     477,   345,   514,-32768,-32768,   -48,-32768,-32768,-32768,-32768,
     518,    77,-32768,   517,   529,   562,-32768,   549,-32768,   336,
  -32768,-32768,   582,-32768,-32768,  1033,  1847,-32768,  2560,   694,
  -32768,-32768,   573,   573,   305,   305,   658,   658,   305,  2454,
    2516,   444,   444,  2493,  2398,  2560,  1209,  1209,   473,   473,
    1209,  1209,  1385,   332,   589,  1420,-32768,  1704,-32768,-32768,
  -32768,  1704,   635,   620,   652,    53,-32768,-32768,   582,   582,
  -32768,   187,-32768,-32768,  1704,-32768,  1704,  2560,-32768,  1704,
  -32768,   637,    82,-32768,-32768,-32768,   229,-32768,    57,   -23,
    2135,  2206,-32768,   656,-32768,   386,-32768,    41,-32768,   102,
  -32768,-32768,-32768,  1858,   582,   365,   418,    20,-32768,   657,
     699,  1704,   -55,   664,  2375,  2560,-32768,-32768,-32768,-32768,
     176,-32768,-32768,   661,   221,-32768,    58,   582,  1704,-32768,
     659,-32768,   476,   582,   672,   510,   668,-32768,    88,-32768,
     674,-32768,   686,-32768,   679,-32768,  1704,   680,-32768,   681,
  -32768,-32768,-32768,   683,   213,-32768,   695,   561,   714,  1099,
  -32768,-32768,   697,-32768,    86,-32768,   728,-32768,-32768,  2560,
     489,  1879,-32768,  1931,-32768,  2352,  2235,-32768,   620,-32768,
  -32768,   753,-32768,    68,-32768,   763,-32768,-32768,-32768,-32768,
  -32768,   775,   359,    28,-32768,   780,-32768,   774,-32768,-32768,
    2560,-32768,-32768,-32768,   887,-32768,-32768,   145,-32768,  1704,
  -32768,   251,  2560,-32768,   781,-32768,-32768,   582,   782,-32768,
     564,   890,  1527,-32768,-32768,   785,  1136,-32768,  1704,-32768,
  -32768,   788,   846,-32768,-32768,-32768,-32768,   789,-32768,-32768,
  -32768,   784,   783,    92,-32768,   361,   429,   280,   850,-32768,
  -32768,-32768,   791,   793,  1704,-32768,   906,   795,   550,-32768,
      30,-32768,   810,   800,-32768,   -14,-32768,-32768,-32768,-32768,
     805,-32768,  2560,-32768,   806,-32768,-32768,-32768,   471,    28,
     803,-32768,-32768,   811,-32768,  1950,   815,-32768,   525,   818,
  -32768,    94,   819,-32768,   100,-32768,   566,    34,-32768,-32768,
  -32768,   704,   817,-32768,   820,   165,-32768,   556,-32768,   821,
  -32768,  1562,-32768,   822,   823,   107,-32768,   280,-32768,   824,
  -32768,   825,   512,-32768,-32768,-32768,-32768,   826,-32768,   567,
  -32768,   834,-32768,   577,-32768,    27,-32768,   607,-32768,-32768,
  -32768,  2154,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,  1733,   835,-32768,   613,    36,-32768,-32768,   838,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,   843,-32768,-32768,    42,
     141,-32768,   108,   143,-32768,   105,   181,   144,   829,   402,
  -32768,-32768,-32768,-32768,   808,   126,-32768,-32768,-32768,-32768,
     663,-32768,-32768,-32768,   844,   682,   875,-32768,   557,   842,
    1961,   917,  1993,  2254,   920,-32768,   921,-32768,   927,  2023,
  -32768,-32768,-32768,   845,   923,-32768,-32768,   925,   234,   149,
  -32768,-32768,   924,    59,-32768,-32768,   692,-32768,-32768,-32768,
  -32768,  2560,-32768,-32768,  2560,   997,-32768,-32768,  2560,  2560,
     315,  2560,-32768,-32768,-32768,-32768,   976,   961,   931,-32768,
     608,-32768,   929,   981,   938,    61,  2560,  2560,   391,  2560,
    2560,   322,   949,   323,   338,-32768,   339,   980,    64,-32768,
  -32768,   693,-32768,-32768,-32768,  2029,   990,-32768,   947,   981,
     951,   -12,   953,  2560,   341,   488,  2254,  2560,-32768,-32768,
     957,  2254,   958,   959,  1008,   -57,    65,   964,   955,  2075,
    1009,-32768,   990,  2560,  2560,   628,  2254,  2254,-32768,   495,
     965,   966,   396,  1031,  1008,  1008,  2081,   990,   968,  1008,
     969,  1008,-32768,   972,-32768,   975,   197,  2102,    23,  1009,
     978,   984,  2560,-32768,-32768,   987,   396,   396,  2108,   231,
     390,-32768,  1097,-32768,   990,   990,-32768,   189,  1009,  1008,
     990,  1008,   990,-32768,-32768,  1028,-32768,  1040,   633,  1056,
  -32768,    38,  2560,  2560,   542,-32768,   537,   837,  1072,  1669,
    1073,-32768,-32768,-32768,  2254,  1175,  1009,  1009,  1067,-32768,
      39,   990,  1009,   990,  1009,-32768,-32768,-32768,-32768,  1065,
  -32768,  1078,  1079,  2254,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,  1066,  1074,-32768,  1075,-32768,  1009,  1076,  1009,
      44,-32768,  2254,  2254,-32768,-32768,-32768,-32768,  2254,-32768,
  -32768,-32768,  1077,-32768,  1080,  1081,-32768,-32768,-32768,  2254,
    2254,  2254,-32768,-32768,-32768,  1186,  1191,-32768
};

static const short yypgoto[] =
{
  -32768,-32768,   432,-32768,   -58,-32768,  1190,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,   -10,-32768,  1012,   940,  1104,   -16,
  -32768,   933,-32768,  -310,-32768,   724,   -70,   -20,-32768,   899,
      11,   -64,-32768,   926,-32768,   814,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,  -289,  1202,-32768,-32768,   751,   723,-32768,
  -32768,   643,-32768,   563,    26,   544,   -89,   765,-32768,   797,
  -32768,-32768,   893,-32768,-32768,-32768,  -463,  -521,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,    56,  -687,-32768,-32768,-32768,-32768,  -418,    -6,
      -7,-32768,-32768,-32768,   499,-32768,-32768,   836,-32768,  1205,
     -46,-32768,-32768,   871,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,   928,  1063,  -107,  1208,-32768,-32768,   709,   702,-32768,
  -32768,   614,-32768,  -381,   552,-32768,-32768,-32768,-32768
};


#define	YYLAST		2665


static const short yytable[] =
{
      46,    49,    51,    87,    52,    81,    81,    86,   175,    64,
      66,   154,    68,    85,   378,   228,    89,    33,   179,   183,
     367,   336,   688,   743,   729,   192,    60,    88,   536,    99,
     100,   474,    83,    83,    83,   506,   399,   559,   103,   759,
     775,   142,    97,   564,   324,   795,    26,   312,    93,   743,
     743,   342,   605,   194,   293,   689,   343,   256,   310,   355,
     622,    92,   648,   167,   257,   663,   690,   101,    88,   405,
    -120,    28,    98,    29,    30,   184,   187,   185,   263,   422,
     423,   415,   171,   300,   235,   238,   239,   388,   416,   365,
     313,   236,   479,   456,    90,   497,   507,   343,   560,   146,
    -120,   501,   229,   326,    33,   565,   574,   254,   522,   569,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   274,   216,   217,   218,   219,   220,   221,
     222,   223,   225,   337,   227,   678,   730,   537,   222,   231,
     683,   475,   566,   476,   571,   578,   427,  -169,   273,  -399,
     618,   760,   776,   244,   246,   703,   704,   796,   294,    35,
      36,    37,   249,    38,   195,   295,   514,   517,    60,   311,
     356,   623,   297,   649,   406,    39,   664,   691,   157,    35,
      36,    37,   576,    38,   303,   188,   189,   264,   265,   280,
     748,   281,   301,   302,   366,    39,   389,   390,   725,    93,
      40,    41,   457,   458,   498,   499,   276,   327,   284,   652,
     502,   503,   333,   570,   376,   575,    42,   523,   524,   346,
      40,    41,   351,   770,   428,   174,    44,    35,    36,    37,
     306,    38,   740,   172,    25,   616,    42,   160,   254,   586,
     298,    94,   784,    39,   428,   174,    44,   407,   572,   579,
      45,   567,   568,   316,   316,   700,   701,   377,   155,   619,
     620,   797,   798,   387,   232,   156,   329,    33,    40,    41,
      45,  -120,    28,    59,    29,    30,   157,   377,   345,  -120,
      28,   465,    29,    30,    42,    87,   347,   348,   276,    86,
      26,   577,    43,   180,    44,    85,   450,   617,   158,   749,
     161,  -120,   453,   714,   715,    60,   788,   726,   720,  -120,
     722,   173,   174,   432,   761,   762,    83,   379,    45,    95,
     115,   116,   799,   800,   801,   377,   333,   352,    28,    59,
      29,    30,   392,   741,   396,   307,   398,   271,   751,   379,
     753,   466,  -355,    96,   234,   489,   251,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   154,   433,   126,   127,
     411,   434,   459,   424,   131,   132,   133,   134,   135,   136,
     379,   173,   174,  -395,   159,   281,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   321,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   581,   130,   131,   132,   133,   134,   135,
     136,   432,   139,   160,   140,   272,    35,    36,    37,   332,
      38,   635,   173,   174,   173,   174,   146,   161,   656,   658,
     462,   176,    39,   146,   146,   481,   708,   709,   412,   139,
     460,   140,   708,   709,   659,   661,    58,   676,   492,   146,
     146,   510,   146,    76,   177,   509,   178,    40,    41,   115,
     116,   117,   118,   119,   120,   173,   174,   123,   379,   196,
     379,   193,   483,    42,   137,   330,   138,   358,   331,   186,
     139,    43,   140,    44,  -395,  -294,  -395,   149,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   173,   174,   126,
     127,   653,   146,   742,   554,   131,   132,    45,   463,   135,
     136,   361,   582,   528,    64,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   494,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   583,   130,   131,   132,   133,   134,   135,   136,
     484,   139,   200,   140,   226,   173,   174,   516,   595,    71,
    -120,    28,   381,    29,    30,   438,   554,   504,   531,   362,
      35,    36,    37,   610,    38,   -23,   -23,   -23,   534,   -23,
     139,   170,   140,   708,   709,   242,    39,   250,   115,   116,
    -120,   -23,   119,   120,   677,   628,   123,   393,   631,   146,
     394,   705,   633,   634,   412,   636,   146,   243,   538,   640,
     731,    40,    41,   137,   557,   138,   -23,   -23,   248,   139,
     596,   140,   256,   654,   655,   529,   255,    42,   262,   750,
    -120,    28,   -23,    29,    30,    43,   539,    44,   668,   268,
     -23,   269,   -23,   173,   174,   505,   532,   675,   763,   554,
     764,   679,  -106,   146,   554,   101,   535,   772,   773,   270,
    -120,    45,    51,   778,   587,   780,   -23,   -23,   377,   554,
     554,   641,   -23,   115,   116,   117,   118,   119,   120,    66,
     139,   123,   140,   592,   126,   127,   539,   588,   792,   273,
     794,   728,   484,   624,   665,   283,   734,   286,   699,   289,
     340,   739,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   718,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,    -2,
     130,   131,   132,   133,   134,   135,   136,   554,   702,   146,
     746,   747,   588,   757,   146,   288,   752,   299,   754,    28,
      -3,    29,    30,    71,  -120,    28,   554,    29,    30,   317,
     319,   593,   736,   737,   292,   139,   320,   140,   339,   357,
     344,   625,   666,   350,   364,   554,   554,   777,    71,   779,
      28,   554,    29,    30,  -120,   360,   368,    72,   370,   371,
     372,   373,   554,   554,   554,   374,    73,    74,    75,    71,
     137,    28,   138,    29,    30,   380,   139,   386,   140,   584,
     341,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   383,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   330,   130,
     131,   132,   133,   134,   135,   136,   612,   447,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   404,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   408,   130,   131,   132,   133,
     134,   135,   136,   708,   709,   410,   420,   421,  -227,   436,
     240,   440,   437,   443,   454,   455,  -120,    28,   147,    29,
      30,   446,   451,   415,   469,   448,   470,   472,   473,   137,
     478,   138,   477,   480,   482,   139,   488,   140,   585,  -120,
      28,   147,    29,    30,   490,   493,  -120,   148,   496,   500,
     512,   518,   520,   513,   580,   521,   530,   526,   527,  -120,
      28,    59,    29,    30,   533,   556,   137,   599,   138,  -120,
     765,   562,   139,   563,   140,   613,   693,   591,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,  -120,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   594,   130,   131,   132,   133,
     134,   135,   136,   143,   190,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   144,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   602,   130,   131,   132,   133,   134,   135,   136,
     606,   607,   608,   614,   275,   615,   632,   621,   -13,   637,
     638,   639,   644,  -120,    28,   645,    29,    30,    71,  -120,
      28,   647,    29,    30,   657,   669,   137,    72,   138,   662,
     671,   673,   139,   674,   140,   694,    73,    74,    75,   682,
     684,   685,   686,  -120,   692,   697,   712,   706,   707,  -120,
     719,   721,   723,  -120,    28,   724,    29,    30,   732,    28,
     147,    29,    30,   145,   733,   138,   148,   735,  -271,   139,
     384,   140,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,  -120,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   -14,
     130,   131,   132,   133,   134,   135,   136,   444,   755,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     756,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   758,   130,   131,   132,
     133,   134,   135,   136,   766,   768,   771,   774,   781,   789,
      28,   147,    29,    30,   782,   783,   806,   790,   791,   793,
     802,   807,    22,   803,   804,   266,   308,   191,   322,   515,
     137,   359,   138,   338,   439,    23,   139,   385,   140,   495,
     525,   597,   672,   696,   487,   468,   375,    56,   435,   400,
     241,    57,   353,   555,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   558,   642,   126,   127,   137,   717,   138,
       0,     0,     0,   139,   445,   140,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,     0,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,     0,   130,   131,   132,   133,   134,   135,
     136,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,     0,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,     0,   130,
     131,   132,   133,   134,   135,   136,   139,     0,   140,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,     0,
       0,     0,     0,     0,   137,     0,   138,     0,     0,   201,
     139,     0,   140,     0,   247,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   137,
       0,   138,     0,     0,     0,   139,     0,   140,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,     0,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,     0,   130,   131,   132,   133,
     134,   135,   136,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,     0,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
       0,   130,   131,   132,   133,   134,   135,   136,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   137,   285,   138,     0,
       0,     0,   139,     0,   140,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   137,     0,   138,     0,     0,     0,   139,   287,   140,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,     0,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,     0,   130,   131,
     132,   133,   134,   135,   136,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,     0,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,     0,   130,   131,   132,   133,   134,   135,   136,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   137,     0,
     138,     0,     0,     0,   139,   441,   140,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   137,     0,   138,     0,     0,     0,   139,
     519,   140,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,     0,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,     0,
     130,   131,   132,   133,   134,   135,   136,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,     0,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,    63,   130,   131,   132,   133,   134,
     135,   136,     0,     0,     0,   102,     0,    35,    36,    37,
       0,    38,     0,     0,     0,     0,     0,     0,    35,    36,
      37,     0,    38,    39,     0,     0,   224,     0,     0,     0,
     137,   767,   138,     0,    39,     0,   139,   230,   140,    35,
      36,    37,     0,    38,     0,     0,     0,     0,    40,    41,
      35,    36,    37,     0,    38,    39,     0,     0,     0,    40,
      41,     0,     0,     0,    42,   137,    39,   138,     0,     0,
       0,   139,    43,   140,    44,    42,     0,     0,     0,     0,
      40,    41,     0,    43,     0,    44,     0,     0,     0,     0,
       0,    40,    41,     0,     0,     0,    42,   245,    45,     0,
       0,     0,     0,     0,    43,     0,    44,    42,   279,    45,
      35,    36,    37,     0,    38,    43,     0,    44,     0,   328,
       0,    35,    36,    37,     0,    38,    39,     0,     0,     0,
      45,     0,    35,    36,    37,     0,    38,    39,     0,     0,
     395,    45,     0,     0,     0,     0,     0,     0,    39,     0,
       0,    40,    41,    35,    36,    37,     0,    38,     0,     0,
       0,     0,    40,    41,     0,     0,     0,    42,     0,    39,
       0,     0,     0,    40,    41,    43,     0,    44,    42,     0,
       0,     0,     0,     0,     0,     0,    43,     0,    44,    42,
       0,     0,   397,     0,    40,    41,     0,    43,     0,    44,
       0,    45,     0,     0,     0,    35,    36,    37,     0,    38,
      42,   491,    45,     0,     0,     0,     0,     0,    43,     0,
      44,    39,   600,    45,    35,    36,    37,     0,    38,     0,
       0,     0,     0,     0,     0,  -238,  -238,  -238,     0,  -238,
      39,     0,     0,     0,    45,     0,    40,    41,     0,     0,
       0,  -238,     0,     0,   603,     0,     0,     0,     0,     0,
       0,     0,    42,     0,     0,    40,    41,  -244,  -244,  -244,
      43,  -244,    44,     0,     0,     0,  -238,  -238,     0,     0,
       0,    42,     0,  -244,   609,     0,     0,     0,     0,    43,
     667,    44,  -238,     0,     0,     0,    45,    35,    36,    37,
    -238,    38,  -238,    35,    36,    37,     0,    38,  -244,  -244,
       0,     0,     0,    39,     0,    45,     0,     0,     0,    39,
       0,     0,     0,     0,  -244,     0,  -238,     0,     0,     0,
       0,     0,  -244,     0,  -244,     0,   695,     0,    40,    41,
       0,     0,   716,     0,    40,    41,     0,     0,     0,    35,
      36,    37,     0,    38,    42,    35,    36,    37,  -244,    38,
      42,     0,    43,   727,    44,    39,     0,     0,    43,   738,
      44,    39,     0,     0,     0,     0,    35,    36,    37,     0,
      38,     0,    35,    36,    37,     0,    38,     0,    45,     0,
      40,    41,    39,     0,    45,     0,    40,    41,    39,     0,
       0,     0,     0,     0,     0,     0,    42,     0,     0,    35,
      36,    37,    42,    38,    43,     0,    44,    40,    41,     0,
      43,     0,    44,    40,    41,    39,     0,     0,    35,    36,
      37,     0,    38,    42,     0,     0,     0,     0,     0,    42,
      45,    43,     0,    44,    39,     0,    45,    43,     0,    44,
      40,    41,   542,   543,   544,   545,   546,   547,   548,     0,
       0,     0,   549,     0,     0,     0,    42,    45,     0,    40,
      41,     0,     0,    45,    43,     0,    44,     0,     0,     0,
      35,    36,    37,     0,    38,    42,     0,     0,     0,     0,
       0,     0,     0,    43,     0,    44,    39,     0,     0,     0,
      45,     0,     0,     0,     0,     0,     0,     0,   315,    35,
      36,    37,     0,    38,     0,     0,     0,     0,     0,    45,
       0,    40,    41,     0,   550,    39,   374,   551,    35,    36,
      37,     0,    38,     0,     0,     0,     0,    42,     0,     0,
       0,     0,     0,     0,    39,    43,     0,    44,     0,     0,
      40,    41,   542,   543,   544,   545,   546,   547,   548,     0,
       0,     0,   549,     0,     0,     0,    42,     0,     0,    40,
      41,    45,     0,     0,    43,     0,    44,     0,     0,   318,
       0,     0,     0,     0,     0,    42,     0,     0,     0,     0,
       0,     0,     0,    43,     0,    44,     0,     0,     0,     0,
      45,     0,   273,     0,     0,     0,     0,   377,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    45,
       0,     0,     0,     0,   550,     0,   374,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,     0,   130,   131,   132,   133,   134,   135,   136,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,     0,     0,   131,   132,   133,
     134,   135,   136,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,     0,     0,     0,
     131,   132,   133,   134,   135,   136,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   137,     0,   138,     0,     0,     0,   139,
       0,   140,     0,     0,     0,     0,     0,     0,     0,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   138,   125,
     126,   127,   139,     0,   140,     0,   131,   132,   133,   134,
     135,   136,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   138,     0,     0,     0,   139,     0,   140,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,     0,     0,     0,     0,   131,   132,   133,   134,   135,
     136,   115,   116,   117,   118,   119,   120,   121,   122,   123,
       0,     0,   126,   127,     0,     0,     0,     0,   131,   132,
     133,   134,   135,   136,     0,     0,     0,   138,     0,     0,
       0,   139,     0,   140,     0,     0,     0,     0,     0,    35,
      36,    37,     0,    38,    35,    36,    37,     0,    38,     0,
       0,     0,     0,     0,     0,    39,     0,     0,     0,     0,
      39,     0,     0,     0,     0,     0,   138,     0,     0,     0,
     139,     0,   140,     0,     0,     0,     0,     0,     0,     0,
      40,    41,     0,     0,     0,    40,    41,     0,     0,   138,
       0,     0,     0,   139,     0,   140,    42,   162,   163,   164,
     165,    42,   166,     0,    43,     0,    44,     0,     0,    43,
       0,    44,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      45,     0,     0,     0,     0,    45
};

static const short yycheck[] =
{
       7,     8,     9,    23,    10,    21,    22,    23,    72,    16,
      17,    57,    18,    23,   324,    14,     1,     6,    76,    83,
     309,     1,    79,   710,     1,    95,    15,    79,     1,    36,
      37,     1,    21,    22,    23,     1,   346,     1,    45,     1,
       1,    48,    50,     1,     3,     1,    57,    70,   111,   736,
     737,   106,   573,     1,     1,   112,   111,   105,     1,     1,
       1,    54,     1,    70,   112,     1,     1,   105,    79,     1,
      50,    51,    80,    53,    54,     1,     1,     3,     1,   368,
     369,    53,    71,     1,   148,   155,   156,     1,    60,     1,
     113,   149,   106,     1,    79,     1,    62,   111,    62,   111,
      80,     1,   101,     1,    93,    63,     1,   171,     1,     1,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   193,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   113,   141,   656,   113,   110,   145,   146,
     661,   111,     1,   113,     1,     1,     1,   113,   107,   113,
       1,   113,   113,   160,   161,   676,   677,   113,   105,    14,
      15,    16,   169,    18,   112,   112,     1,   477,   157,   112,
     112,   112,   242,   112,   106,    30,   112,   112,   110,    14,
      15,    16,     1,    18,   254,   110,   111,   110,   111,   196,
       1,   198,   110,   111,   106,    30,   110,   111,     1,   111,
      55,    56,   110,   111,   110,   111,   195,   105,   215,   627,
     110,   111,   276,   105,     1,   110,    71,   110,   111,   289,
      55,    56,     1,   744,    79,    80,    81,    14,    15,    16,
       1,    18,     1,     1,     1,     1,    71,   111,   302,   113,
     247,     1,   763,    30,    79,    80,    81,   354,   105,   105,
     105,   110,   111,   260,   261,   673,   674,   112,    79,   110,
     111,   782,   783,   333,     1,    79,   273,   256,    55,    56,
     105,    50,    51,    52,    53,    54,   110,   112,   285,    50,
      51,     1,    53,    54,    71,   305,   110,   111,   277,   305,
      57,   110,    79,     1,    81,   305,   403,    63,   111,   110,
     111,    80,   409,   684,   685,   294,   769,   110,   689,    80,
     691,    79,    80,   377,   732,   733,   305,   324,   105,    79,
      15,    16,   785,   786,   787,   112,   390,   106,    51,    52,
      53,    54,   339,   102,   341,   106,   343,     1,   719,   346,
     721,    61,    79,   103,     1,   452,     1,    15,    16,    17,
      18,    19,    20,    21,    22,    23,   402,   106,    26,    27,
       1,   110,     1,   370,    32,    33,    34,    35,    36,    37,
     377,    79,    80,     0,     1,   382,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,     1,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,     1,    31,    32,    33,    34,    35,    36,
      37,   475,   107,   111,   109,    79,    14,    15,    16,     1,
      18,   106,    79,    80,    79,    80,   111,   111,   106,   106,
       1,   112,    30,   111,   111,   442,    46,    47,    79,   107,
      79,   109,    46,    47,   106,   106,    14,   106,   455,   111,
     111,   471,   111,    21,   112,   471,   112,    55,    56,    15,
      16,    17,    18,    19,    20,    79,    80,    23,   475,   107,
     477,    79,     1,    71,   101,   110,   103,     1,   113,   110,
     107,    79,   109,    81,   111,     1,   113,    55,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    79,    80,    26,
      27,   110,   111,   113,   511,    32,    33,   105,    79,    36,
      37,     1,   110,     1,   521,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,     1,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,   549,    31,    32,    33,    34,    35,    36,    37,
      79,   107,   106,   109,    79,    79,    80,     1,     1,    49,
      50,    51,     1,    53,    54,     1,   573,     1,     1,    59,
      14,    15,    16,   579,    18,    14,    15,    16,     1,    18,
     107,     1,   109,    46,    47,    79,    30,   110,    15,    16,
      80,    30,    19,    20,   106,   601,    23,   108,   604,   111,
     111,   106,   608,   609,    79,   611,   111,   111,     1,     1,
     699,    55,    56,   101,     1,   103,    55,    56,   114,   107,
      63,   109,   105,   629,   630,   113,   112,    71,   110,   718,
      50,    51,    71,    53,    54,    79,    79,    81,   645,   110,
      79,    79,    81,    79,    80,    79,    79,   653,   106,   656,
     113,   657,   102,   111,   661,   105,    79,   746,   747,   110,
      80,   105,   669,   752,     1,   754,   105,   106,   112,   676,
     677,    63,   111,    15,    16,    17,    18,    19,    20,   686,
     107,    23,   109,     1,    26,    27,    79,    79,   777,   107,
     779,   697,    79,     1,     1,     1,   702,   108,   672,    79,
       1,   708,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,   687,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,     0,
      31,    32,    33,    34,    35,    36,    37,   744,   110,   111,
     714,   715,    79,   110,   111,   110,   720,   110,   722,    51,
       0,    53,    54,    49,    50,    51,   763,    53,    54,   260,
     261,    79,   706,   707,   112,   107,   110,   109,   111,   110,
     106,    79,    79,   112,   106,   782,   783,   751,    49,   753,
      51,   788,    53,    54,    80,   113,   112,    58,   102,   110,
     110,   110,   799,   800,   801,   112,    67,    68,    69,    49,
     101,    51,   103,    53,    54,   110,   107,   110,   109,     1,
     111,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,   108,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,   110,    31,
      32,    33,    34,    35,    36,    37,     1,     1,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,   106,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,   112,    31,    32,    33,    34,
      35,    36,    37,    46,    47,   110,   106,   113,     1,   108,
       1,     1,   110,   108,   110,   112,    50,    51,    52,    53,
      54,   113,   113,    53,   113,    59,   113,     1,   113,   101,
     110,   103,   102,   108,   108,   107,   113,   109,   110,    50,
      51,    52,    53,    54,   113,   110,    80,    58,   110,   110,
     113,   110,   110,   113,   105,   112,   110,   113,   113,    50,
      51,    52,    53,    54,   110,   110,   101,   105,   103,    80,
     113,   113,   107,   110,   109,   110,     1,   113,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    80,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,   110,    31,    32,    33,    34,
      35,    36,    37,     1,     1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,   105,    31,    32,    33,    34,    35,    36,    37,
     110,   110,   105,   110,     1,   110,    39,   113,     0,    63,
      79,   110,   113,    50,    51,    64,    53,    54,    49,    50,
      51,   113,    53,    54,   105,    65,   101,    58,   103,    79,
     113,   110,   107,   110,   109,   110,    67,    68,    69,   112,
     112,   112,    64,    80,   110,    66,    45,   112,   112,    80,
     112,   112,   110,    50,    51,   110,    53,    54,   110,    51,
      52,    53,    54,   101,   110,   103,    58,   110,     1,   107,
       1,   109,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    80,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,     0,
      31,    32,    33,    34,    35,    36,    37,     1,   110,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
     110,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,   110,    31,    32,    33,
      34,    35,    36,    37,   102,   102,     1,   110,   113,   113,
      51,    52,    53,    54,   106,   106,     0,   113,   113,   113,
     113,     0,     2,   113,   113,   183,   256,    93,   265,   475,
     101,   302,   103,   277,   390,     3,   107,   108,   109,   458,
     487,   568,   649,   669,   449,   418,   323,    12,   382,   348,
     157,    13,   294,   521,    15,    16,    17,    18,    19,    20,
      21,    22,    23,   524,   620,    26,    27,   101,   686,   103,
      -1,    -1,    -1,   107,   108,   109,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    -1,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    -1,    31,    32,    33,    34,    35,    36,
      37,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    -1,    31,
      32,    33,    34,    35,    36,    37,   107,    -1,   109,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,    -1,    -1,
      -1,    -1,    -1,    -1,   101,    -1,   103,    -1,    -1,   106,
     107,    -1,   109,    -1,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,
      -1,   103,    -1,    -1,    -1,   107,    -1,   109,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    -1,    31,    32,    33,    34,
      35,    36,    37,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    -1,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      -1,    31,    32,    33,    34,    35,    36,    37,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   101,   102,   103,    -1,
      -1,    -1,   107,    -1,   109,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   101,    -1,   103,    -1,    -1,    -1,   107,   108,   109,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    -1,    31,    32,
      33,    34,    35,    36,    37,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    -1,    31,    32,    33,    34,    35,    36,    37,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,    -1,
     103,    -1,    -1,    -1,   107,   108,   109,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   101,    -1,   103,    -1,    -1,    -1,   107,
     108,   109,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    -1,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    -1,
      31,    32,    33,    34,    35,    36,    37,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,     1,    31,    32,    33,    34,    35,
      36,    37,    -1,    -1,    -1,     1,    -1,    14,    15,    16,
      -1,    18,    -1,    -1,    -1,    -1,    -1,    -1,    14,    15,
      16,    -1,    18,    30,    -1,    -1,     1,    -1,    -1,    -1,
     101,   102,   103,    -1,    30,    -1,   107,     1,   109,    14,
      15,    16,    -1,    18,    -1,    -1,    -1,    -1,    55,    56,
      14,    15,    16,    -1,    18,    30,    -1,    -1,    -1,    55,
      56,    -1,    -1,    -1,    71,   101,    30,   103,    -1,    -1,
      -1,   107,    79,   109,    81,    71,    -1,    -1,    -1,    -1,
      55,    56,    -1,    79,    -1,    81,    -1,    -1,    -1,    -1,
      -1,    55,    56,    -1,    -1,    -1,    71,     1,   105,    -1,
      -1,    -1,    -1,    -1,    79,    -1,    81,    71,     1,   105,
      14,    15,    16,    -1,    18,    79,    -1,    81,    -1,     1,
      -1,    14,    15,    16,    -1,    18,    30,    -1,    -1,    -1,
     105,    -1,    14,    15,    16,    -1,    18,    30,    -1,    -1,
       1,   105,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,
      -1,    55,    56,    14,    15,    16,    -1,    18,    -1,    -1,
      -1,    -1,    55,    56,    -1,    -1,    -1,    71,    -1,    30,
      -1,    -1,    -1,    55,    56,    79,    -1,    81,    71,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,    81,    71,
      -1,    -1,     1,    -1,    55,    56,    -1,    79,    -1,    81,
      -1,   105,    -1,    -1,    -1,    14,    15,    16,    -1,    18,
      71,     1,   105,    -1,    -1,    -1,    -1,    -1,    79,    -1,
      81,    30,     1,   105,    14,    15,    16,    -1,    18,    -1,
      -1,    -1,    -1,    -1,    -1,    14,    15,    16,    -1,    18,
      30,    -1,    -1,    -1,   105,    -1,    55,    56,    -1,    -1,
      -1,    30,    -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    71,    -1,    -1,    55,    56,    14,    15,    16,
      79,    18,    81,    -1,    -1,    -1,    55,    56,    -1,    -1,
      -1,    71,    -1,    30,     1,    -1,    -1,    -1,    -1,    79,
       1,    81,    71,    -1,    -1,    -1,   105,    14,    15,    16,
      79,    18,    81,    14,    15,    16,    -1,    18,    55,    56,
      -1,    -1,    -1,    30,    -1,   105,    -1,    -1,    -1,    30,
      -1,    -1,    -1,    -1,    71,    -1,   105,    -1,    -1,    -1,
      -1,    -1,    79,    -1,    81,    -1,     1,    -1,    55,    56,
      -1,    -1,     1,    -1,    55,    56,    -1,    -1,    -1,    14,
      15,    16,    -1,    18,    71,    14,    15,    16,   105,    18,
      71,    -1,    79,     1,    81,    30,    -1,    -1,    79,     1,
      81,    30,    -1,    -1,    -1,    -1,    14,    15,    16,    -1,
      18,    -1,    14,    15,    16,    -1,    18,    -1,   105,    -1,
      55,    56,    30,    -1,   105,    -1,    55,    56,    30,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    71,    -1,    -1,    14,
      15,    16,    71,    18,    79,    -1,    81,    55,    56,    -1,
      79,    -1,    81,    55,    56,    30,    -1,    -1,    14,    15,
      16,    -1,    18,    71,    -1,    -1,    -1,    -1,    -1,    71,
     105,    79,    -1,    81,    30,    -1,   105,    79,    -1,    81,
      55,    56,    38,    39,    40,    41,    42,    43,    44,    -1,
      -1,    -1,    48,    -1,    -1,    -1,    71,   105,    -1,    55,
      56,    -1,    -1,   105,    79,    -1,    81,    -1,    -1,    -1,
      14,    15,    16,    -1,    18,    71,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    79,    -1,    81,    30,    -1,    -1,    -1,
     105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   113,    14,
      15,    16,    -1,    18,    -1,    -1,    -1,    -1,    -1,   105,
      -1,    55,    56,    -1,   110,    30,   112,   113,    14,    15,
      16,    -1,    18,    -1,    -1,    -1,    -1,    71,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    79,    -1,    81,    -1,    -1,
      55,    56,    38,    39,    40,    41,    42,    43,    44,    -1,
      -1,    -1,    48,    -1,    -1,    -1,    71,    -1,    -1,    55,
      56,   105,    -1,    -1,    79,    -1,    81,    -1,    -1,   113,
      -1,    -1,    -1,    -1,    -1,    71,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    79,    -1,    81,    -1,    -1,    -1,    -1,
     105,    -1,   107,    -1,    -1,    -1,    -1,   112,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,
      -1,    -1,    -1,    -1,   110,    -1,   112,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    -1,    31,    32,    33,    34,    35,    36,    37,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    -1,    -1,    32,    33,    34,
      35,    36,    37,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    -1,    -1,    -1,
      32,    33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   101,    -1,   103,    -1,    -1,    -1,   107,
      -1,   109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    23,   103,    25,
      26,    27,   107,    -1,   109,    -1,    32,    33,    34,    35,
      36,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   103,    -1,    -1,    -1,   107,    -1,   109,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    -1,    -1,    -1,    -1,    32,    33,    34,    35,    36,
      37,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      -1,    -1,    26,    27,    -1,    -1,    -1,    -1,    32,    33,
      34,    35,    36,    37,    -1,    -1,    -1,   103,    -1,    -1,
      -1,   107,    -1,   109,    -1,    -1,    -1,    -1,    -1,    14,
      15,    16,    -1,    18,    14,    15,    16,    -1,    18,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,    -1,
      30,    -1,    -1,    -1,    -1,    -1,   103,    -1,    -1,    -1,
     107,    -1,   109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      55,    56,    -1,    -1,    -1,    55,    56,    -1,    -1,   103,
      -1,    -1,    -1,   107,    -1,   109,    71,    72,    73,    74,
      75,    71,    77,    -1,    79,    -1,    81,    -1,    -1,    79,
      -1,    81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     105,    -1,    -1,    -1,    -1,   105
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
case 50:
#line 362 "parser.yy"
{
	  CALL(yylsp[-1], yylsp[-1], beforeUpdate());
        }
    break;
case 52:
#line 368 "parser.yy"
{
	  CALL(yylsp[-1], yylsp[-1], afterUpdate());
        }
    break;
case 53:
#line 373 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], declFuncBegin(yyvsp[-1].string, yyvsp[0].number));
	}
    break;
case 54:
#line 376 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[-1], declFuncEnd());
	}
    break;
case 55:
#line 382 "parser.yy"
{ yyval.number = 0; }
    break;
case 56:
#line 383 "parser.yy"
{ yyval.number = yyvsp[-1].number; }
    break;
case 57:
#line 384 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));
	  yyval.number = yyvsp[-2].number; 
	}
    break;
case 58:
#line 388 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));
	  yyval.number = yyvsp[-1].number; 
	}
    break;
case 59:
#line 392 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_PARAMETERS));
	  yyval.number = 0; 
	}
    break;
case 60:
#line 396 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));
	  yyval.number = 0; 
	}
    break;
case 61:
#line 408 "parser.yy"
{ yyval.number = 1; }
    break;
case 62:
#line 409 "parser.yy"
{ yyval.number = yyvsp[-2].number+1; }
    break;
case 63:
#line 410 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_PARAMETERS_));
	  yyval.number = yyvsp[-2].number;
	}
    break;
case 64:
#line 417 "parser.yy"
{
          CALL(yylsp[-3], yylsp[0], declParameter(yyvsp[-1].string, true, yyvsp[0].number));
          CALL(yylsp[-3], yylsp[0], declParameterEnd());
	}
    break;
case 65:
#line 421 "parser.yy"
{
          CALL(yylsp[-2], yylsp[0], declParameter(yyvsp[-1].string, false, yyvsp[0].number));
          CALL(yylsp[-2], yylsp[0], declParameterEnd());
	}
    break;
case 66:
#line 425 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_PARAMID));
	}
    break;
case 67:
#line 431 "parser.yy"
{ 
          CALL(yylsp[-2], yylsp[0], declVarEnd());
	}
    break;
case 68:
#line 434 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
          CALL(yylsp[-3], yylsp[0], declVarEnd());
	}
    break;
case 69:
#line 438 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_VARID));
	  CALL(yylsp[-2], yylsp[0], declVarEnd());
	}
    break;
case 72:
#line 447 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_VARID_));
	}
    break;
case 73:
#line 453 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], declVar(yyvsp[-2].string, yyvsp[-1].number, yyvsp[0].flag));
	}
    break;
case 74:
#line 459 "parser.yy"
{ yyval.flag = false; }
    break;
case 75:
#line 460 "parser.yy"
{ yyval.flag = true; }
    break;
case 76:
#line 461 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_INITIAL));
	  yyval.flag = false; 
	}
    break;
case 78:
#line 469 "parser.yy"
{	
	  CALL(yylsp[-2], yylsp[0], declInitialiserList(yyvsp[-1].number));
	}
    break;
case 79:
#line 472 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  CALL(yylsp[-3], yylsp[0], declInitialiserList(yyvsp[-2].number));
	}
    break;
case 80:
#line 476 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_INITIAL));
	  CALL(yylsp[-2], yylsp[0], declInitialiserList(0));
	}
    break;
case 81:
#line 483 "parser.yy"
{ yyval.number = 1; }
    break;
case 82:
#line 484 "parser.yy"
{ yyval.number = yyvsp[-2].number+1; }
    break;
case 83:
#line 485 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_INITIAL_));
	  yyval.number = yyvsp[-2].number+1; 
	}
    break;
case 84:
#line 492 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], declFieldInit(yyvsp[-2].string));
	}
    break;
case 85:
#line 495 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_INITIAL));
	}
    break;
case 86:
#line 498 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], declFieldInit(NULL));
	}
    break;
case 87:
#line 504 "parser.yy"
{ yyval.number=0; }
    break;
case 88:
#line 505 "parser.yy"
{ yyval.number=yyvsp[-3].number+1; }
    break;
case 89:
#line 506 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RSQBRACE));
	  yyval.number=yyvsp[-4].number+1; 
	}
    break;
case 90:
#line 510 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RSQBRACE));
	  yyval.number=yyvsp[-3].number+1; 
	}
    break;
case 91:
#line 514 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_CONST_EXP));
	  yyval.number=yyvsp[-3].number+1; 
	}
    break;
case 92:
#line 518 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_CONST_EXP));
	  yyval.number=yyvsp[-2].number+1; 
	}
    break;
case 93:
#line 525 "parser.yy"
{
	  CALL(yylsp[-3], yylsp[0], declTypeDefEnd());
	}
    break;
case 94:
#line 528 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-4], yylsp[0], declTypeDefEnd());
	}
    break;
case 95:
#line 532 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_TYPEID));
	  CALL(yylsp[-3], yylsp[0], declTypeDefEnd());  
	}
    break;
case 96:
#line 536 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_TYPE_DEF));
	  CALL(yylsp[-2], yylsp[0], declTypeDefEnd());  
	}
    break;
case 97:
#line 548 "parser.yy"
{ yyval.number = 1; }
    break;
case 98:
#line 549 "parser.yy"
{ yyval.number = yyvsp[-2].number+1; }
    break;
case 99:
#line 550 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_TYPEID_));
	  yyval.number = yyvsp[-2].number+1; 
	}
    break;
case 100:
#line 557 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], declTypeDef(yyvsp[-1].string, yyvsp[0].number));
	}
    break;
case 101:
#line 563 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], declType(yyvsp[-2].number, yyvsp[-1].string, yyvsp[0].flag));
	}
    break;
case 102:
#line 566 "parser.yy"
{ 
	  CALL(yylsp[-4], yylsp[0], declStruct(yyvsp[-4].number, yyvsp[-1].number));
	}
    break;
case 103:
#line 569 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBER));
	  CALL(yylsp[-4], yylsp[0], declStruct(yyvsp[-4].number, 0));
	}
    break;
case 104:
#line 573 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  CALL(yylsp[-3], yylsp[0], declStruct(yyvsp[-3].number, 0));
	}
    break;
case 105:
#line 577 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	}
    break;
case 106:
#line 583 "parser.yy"
{ strncpy(yyval.string, yyvsp[0].string, MAXLEN); }
    break;
case 107:
#line 584 "parser.yy"
{ strncpy(yyval.string, yyvsp[0].string, MAXLEN); }
    break;
case 108:
#line 588 "parser.yy"
{ yyval.number=yyvsp[0].number; }
    break;
case 109:
#line 589 "parser.yy"
{ yyval.number=yyvsp[-1].number+yyvsp[0].number; }
    break;
case 110:
#line 590 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBER));
	  yyval.number=yyvsp[-1].number; 
	}
    break;
case 111:
#line 597 "parser.yy"
{
	  yyval.number = yyvsp[-1].number; 
	  CALL(yylsp[-2], yylsp[0], declFieldEnd());
	}
    break;
case 112:
#line 601 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));	  
	  yyval.number = yyvsp[-2].number; 
	  CALL(yylsp[-3], yylsp[0], declFieldEnd());
	}
    break;
case 113:
#line 606 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBERID));	  
	}
    break;
case 114:
#line 609 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBERID));	  
	}
    break;
case 115:
#line 612 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBERTYPE));	  
	}
    break;
case 116:
#line 618 "parser.yy"
{ yyval.number=1; }
    break;
case 117:
#line 619 "parser.yy"
{ yyval.number=yyvsp[-2].number+1; }
    break;
case 118:
#line 620 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBERID_));
	  yyval.number=yyvsp[-2].number+1; 
	}
    break;
case 119:
#line 627 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], declField(yyvsp[-1].string, yyvsp[0].number));
	}
    break;
case 120:
#line 633 "parser.yy"
{ yyval.number = ParserBuilder::PREFIX_NONE; }
    break;
case 121:
#line 634 "parser.yy"
{ yyval.number = ParserBuilder::PREFIX_URGENT; }
    break;
case 122:
#line 635 "parser.yy"
{ yyval.number = ParserBuilder::PREFIX_BROADCAST; }
    break;
case 123:
#line 636 "parser.yy"
{ yyval.number = ParserBuilder::PREFIX_URGENT_BROADCAST; }
    break;
case 124:
#line 637 "parser.yy"
{ yyval.number = ParserBuilder::PREFIX_CONST; }
    break;
case 125:
#line 641 "parser.yy"
{ yyval.flag = false; }
    break;
case 126:
#line 642 "parser.yy"
{ yyval.flag = true; }
    break;
case 127:
#line 643 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RSQBRACE));
	  yyval.flag = true; 
	}
    break;
case 128:
#line 647 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RSQBRACE));
	  yyval.flag = true; 
	}
    break;
case 129:
#line 651 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_CONST_EXP));
	  yyval.flag = true;
	  CALL(yylsp[-4], yylsp[0], exprTrue());
	}
    break;
case 130:
#line 656 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_CONST_EXP));
	  yyval.flag = true;
	  CALL(yylsp[-4], yylsp[0], exprTrue());
	}
    break;
case 131:
#line 661 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_CONST_EXP));
	  yyval.flag = true;
	  CALL(yylsp[-2], yylsp[0], exprTrue());
	}
    break;
case 132:
#line 666 "parser.yy"
{
	    REPORT_ERROR(last_loc, TypeException(PE_CONST_EXP));
	    yyval.flag = true;
	    CALL(yylsp[-2], yylsp[-1], exprTrue());
	  }
    break;
case 133:
#line 671 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_COMMA)); 
	  yyclearin; yyerrok;
	}
    break;
case 134:
#line 675 "parser.yy"
{
	    yyval.flag = true;
	  }
    break;
case 135:
#line 678 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_COMMA)); 
	  yyclearin; yyerrok;
	  yyval.flag = true;
	  CALL(yylsp[-3], yylsp[0], exprTrue());
	}
    break;
case 136:
#line 684 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_COMMA)); 
	  yyclearin; yyerrok;
	  yyval.flag = true;
	  CALL(yylsp[-2], yylsp[0], exprTrue());
	}
    break;
case 137:
#line 690 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_CONST_EXP)); 
	  yyclearin; yyerrok;
	  yyval.flag = true;
	  CALL(yylsp[-1], yylsp[0], exprTrue());
	}
    break;
case 138:
#line 703 "parser.yy"
{ 
	  CALL(yylsp[-3], yylsp[0], procBegin(yyvsp[-2].string, yyvsp[-1].number));
	}
    break;
case 139:
#line 706 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], procEnd());
	}
    break;
case 140:
#line 709 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	}
    break;
case 141:
#line 712 "parser.yy"
{
	  utap_error(TypeException(PE_LPAREN), 
		     yylsp[0].first_line, yylsp[0].first_column, 
		     yylsp[0].last_line, yylsp[0].last_column);
	  CALL(yylsp[-2], yylsp[0], procBegin(yyvsp[-1].string, 0));
	}
    break;
case 142:
#line 717 "parser.yy"
{
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;
case 143:
#line 720 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_PROCID));	  
	}
    break;
case 150:
#line 742 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;
case 151:
#line 745 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;
case 152:
#line 748 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_STATE_DECL));
	}
    break;
case 153:
#line 751 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_STATE_DECL));
	}
    break;
case 154:
#line 754 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_STATE));
	}
    break;
case 157:
#line 762 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_STATE_DECL_));
	}
    break;
case 158:
#line 768 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], exprTrue());
	  CALL(yylsp[0], yylsp[0], procState(yyvsp[0].string));
	}
    break;
case 159:
#line 772 "parser.yy"
{ 
	  CALL(yylsp[-3], yylsp[0], procState(yyvsp[-3].string));
	}
    break;
case 160:
#line 775 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	  CALL(yylsp[-4], yylsp[0], procState(yyvsp[-4].string));
	}
    break;
case 161:
#line 779 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	  CALL(yylsp[-3], yylsp[0], procState(yyvsp[-3].string));
	}
    break;
case 162:
#line 783 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_INV));
	  CALL(yylsp[-3], yylsp[0], procState(yyvsp[-3].string));
	}
    break;
case 163:
#line 787 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_INV));
	  CALL(yylsp[-2], yylsp[0], procState(yyvsp[-2].string));
	}
    break;
case 164:
#line 794 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], procStateInit(yyvsp[-1].string));
	}
    break;
case 165:
#line 797 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-3], yylsp[0], procStateInit(yyvsp[-2].string));
	}
    break;
case 166:
#line 801 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-2], yylsp[0], procStateInit(yyvsp[-1].string));
	}
    break;
case 167:
#line 805 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;
case 168:
#line 808 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_INIT));
	}
    break;
case 171:
#line 816 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;
case 172:
#line 819 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;
case 173:
#line 822 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS_DECL));
	}
    break;
case 174:
#line 825 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS));
	}
    break;
case 177:
#line 833 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS_DECL_));
	}
    break;
case 178:
#line 839 "parser.yy"
{ 
	  strcpy(rootTransId, yyvsp[-7].string); 
	  CALL(yylsp[-7], yylsp[0], procTransition(yyvsp[-7].string, yyvsp[-5].string));
	}
    break;
case 179:
#line 843 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  strcpy(rootTransId, yyvsp[-8].string); 
	  CALL(yylsp[-8], yylsp[0], procTransition(yyvsp[-8].string, yyvsp[-6].string));
	}
    break;
case 180:
#line 848 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	}
    break;
case 181:
#line 851 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;
case 182:
#line 854 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_ARROW));
	}
    break;
case 183:
#line 860 "parser.yy"
{ 
	  CALL(yylsp[-6], yylsp[0], procTransition(rootTransId, yyvsp[-5].string));
	}
    break;
case 184:
#line 863 "parser.yy"
{ 
	  REPORT_ERROR(yylloc, TypeException(PE_RBRACE));
	  CALL(yylsp[-7], yylsp[0], procTransition(rootTransId, yyvsp[-6].string));
	}
    break;
case 185:
#line 867 "parser.yy"
{ 
	  REPORT_ERROR(yylloc, TypeException(PE_LBRACE));
	}
    break;
case 186:
#line 870 "parser.yy"
{ 
	  REPORT_ERROR(yylloc, TypeException(PE_STATEID));
	}
    break;
case 189:
#line 879 "parser.yy"
{
	  CALL(yyloc, yyloc, procGuard());
        }
    break;
case 190:
#line 882 "parser.yy"
{
	  REPORT_ERROR(yylloc, TypeException(PE_SEMICOLON));
	  CALL(yyloc, yyloc, procGuard());
	}
    break;
case 191:
#line 886 "parser.yy"
{
	  REPORT_ERROR(yylloc, TypeException(PE_GUARD_EXP));
	}
    break;
case 194:
#line 894 "parser.yy"
{
	  REPORT_ERROR(yylloc, TypeException(PE_SEMICOLON));
	}
    break;
case 195:
#line 897 "parser.yy"
{
	  REPORT_ERROR(yylloc, TypeException(PE_SEMICOLON));
	}
    break;
case 196:
#line 900 "parser.yy"
{
	  REPORT_ERROR(yylloc, TypeException(PE_SYNC_EXP));
	}
    break;
case 197:
#line 906 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], procSync(SYNC_BANG));
	}
    break;
case 198:
#line 909 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_BANG));
	  CALL(yylsp[-2], yylsp[-1], procSync(SYNC_QUE));
	}
    break;
case 199:
#line 913 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], procSync(SYNC_QUE));
	}
    break;
case 200:
#line 916 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_QUE));
	  CALL(yylsp[-2], yylsp[-1], procSync(SYNC_QUE));
	}
    break;
case 201:
#line 920 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_BANGQUE));
	  CALL(yylsp[-1], yylsp[0], procSync(SYNC_QUE));
	}
    break;
case 203:
#line 928 "parser.yy"
{
	  CALL(yyloc, yyloc, procUpdate());	  
	}
    break;
case 204:
#line 931 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_ASSIGN_EXP));
	}
    break;
case 210:
#line 945 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;
case 211:
#line 948 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;
case 212:
#line 951 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;
case 213:
#line 954 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;
case 214:
#line 960 "parser.yy"
{}
    break;
case 215:
#line 961 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;
case 216:
#line 964 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;
case 217:
#line 967 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;
case 218:
#line 970 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;
case 219:
#line 976 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], procStateCommit(yyvsp[0].string));
	}
    break;
case 220:
#line 979 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], procStateCommit(yyvsp[0].string));
	}
    break;
case 221:
#line 982 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID_));
	}
    break;
case 222:
#line 988 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], procStateUrgent(yyvsp[0].string));
	}
    break;
case 223:
#line 991 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], procStateUrgent(yyvsp[0].string));
	}
    break;
case 224:
#line 994 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID_));
	}
    break;
case 225:
#line 1005 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], blockBegin());
	}
    break;
case 226:
#line 1008 "parser.yy"
{ 
	  CALL(yylsp[-3], yylsp[-1], blockEnd());
	}
    break;
case 227:
#line 1011 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], blockBegin());
	}
    break;
case 228:
#line 1014 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_DECL_STAT));
	  CALL(yylsp[-2], yylsp[-1], blockEnd());
	}
    break;
case 235:
#line 1033 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], emptyStatement());
	}
    break;
case 236:
#line 1036 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], exprStatement());
	}
    break;
case 237:
#line 1039 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-2], yylsp[0], exprStatement());
	}
    break;
case 238:
#line 1043 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], forBegin());
	}
    break;
case 239:
#line 1046 "parser.yy"
{ 
	    CALL(yylsp[-7], yylsp[-1], forEnd());
	  }
    break;
case 240:
#line 1049 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], forBegin());
	}
    break;
case 241:
#line 1054 "parser.yy"
{ 
	    CALL(yylsp[-7], yylsp[-10], forEnd());
	  }
    break;
case 242:
#line 1057 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_LPAREN));
	  CALL(yylsp[-2], yylsp[0], forBegin());
	}
    break;
case 243:
#line 1062 "parser.yy"
{ 
	    CALL(yylsp[-7], yylsp[-10], forEnd());
	  }
    break;
case 244:
#line 1065 "parser.yy"
{
	    CALL(yylsp[-1], yylsp[0], whileBegin());
	}
    break;
case 245:
#line 1068 "parser.yy"
{ 
	    CALL(yylsp[-3], yylsp[-2], whileEnd());
	  }
    break;
case 246:
#line 1071 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));
	  CALL(yylsp[-2], yylsp[0], whileBegin());
	}
    break;
case 247:
#line 1075 "parser.yy"
{ 
	    CALL(yylsp[-3], yylsp[-1], whileEnd());
	  }
    break;
case 248:
#line 1078 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], whileBegin());
	}
    break;
case 249:
#line 1082 "parser.yy"
{ 
	    CALL(yylsp[-6], yylsp[-4], whileEnd());
	  }
    break;
case 250:
#line 1085 "parser.yy"
{ 
	    CALL(yylsp[0], yylsp[0], doWhileBegin());
	}
    break;
case 251:
#line 1088 "parser.yy"
{ 
	    CALL(yylsp[-6], yylsp[-1], doWhileEnd());
	  }
    break;
case 252:
#line 1091 "parser.yy"
{ 
	    CALL(yylsp[-1], yylsp[0], ifBegin());
	}
    break;
case 254:
#line 1095 "parser.yy"
{ 
	    CALL(yylsp[-1], yylsp[0], breakStatement());
	  }
    break;
case 255:
#line 1098 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-2], yylsp[0], breakStatement());
	}
    break;
case 256:
#line 1102 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], continueStatement());
	}
    break;
case 257:
#line 1105 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-2], yylsp[0], continueStatement());
	}
    break;
case 258:
#line 1109 "parser.yy"
{ 
	    CALL(yylsp[-3], yylsp[0], switchBegin());
	}
    break;
case 259:
#line 1112 "parser.yy"
{ 
	       CALL(yylsp[-3], yylsp[-1], switchEnd());
	   }
    break;
case 260:
#line 1115 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));
	  CALL(yylsp[-4], yylsp[0], switchBegin());
	}
    break;
case 261:
#line 1119 "parser.yy"
{ 
	    CALL(yylsp[-3], yylsp[-1], switchEnd());
	  }
    break;
case 262:
#line 1122 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-4], yylsp[0], switchBegin());
	}
    break;
case 263:
#line 1126 "parser.yy"
{ 
	    CALL(yylsp[-3], yylsp[-1], switchEnd());
	  }
    break;
case 264:
#line 1129 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], returnStatement(true));
	}
    break;
case 265:
#line 1132 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-2], yylsp[0], returnStatement(true));
	}
    break;
case 266:
#line 1136 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], returnStatement(false));
	}
    break;
case 267:
#line 1139 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR_SEMI));
	  CALL(yylsp[-1], yylsp[0], returnStatement(false));
	}
    break;
case 268:
#line 1146 "parser.yy"
{ 
	  CALL(yyloc, yyloc, ifEnd(false));
	}
    break;
case 269:
#line 1149 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], ifElse());
	}
    break;
case 270:
#line 1152 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[-1], ifEnd(true));
	  }
    break;
case 271:
#line 1155 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], ifElse());
	}
    break;
case 272:
#line 1158 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-1], yylsp[-1], ifEnd(true));
	  }
    break;
case 275:
#line 1170 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], caseBegin());
	}
    break;
case 276:
#line 1173 "parser.yy"
{ 
	    CALL(yylsp[-1], yylsp[-1], caseEnd());
	  }
    break;
case 277:
#line 1176 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], caseBegin());
	}
    break;
case 278:
#line 1179 "parser.yy"
{
	    REPORT_ERROR(last_loc, TypeException(PE_EXPR)); 
	    CALL(yylsp[-1], yylsp[-1], caseEnd());
	  }
    break;
case 279:
#line 1183 "parser.yy"
{ 
	    CALL(yylsp[-1], yylsp[0], defaultBegin());
	}
    break;
case 280:
#line 1186 "parser.yy"
{ 
	    CALL(yylsp[-1], yylsp[-1], defaultEnd());
	  }
    break;
case 281:
#line 1189 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_COLON)); 
	  CALL(yylsp[-2], yylsp[0], defaultBegin());
	}
    break;
case 282:
#line 1193 "parser.yy"
{ 
	    CALL(yylsp[-1], yylsp[-1], defaultEnd());
	  }
    break;
case 286:
#line 1205 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprComma());
	}
    break;
case 287:
#line 1208 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR_));
	}
    break;
case 288:
#line 1214 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], exprFalse());
	}
    break;
case 289:
#line 1217 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], exprTrue());
	}
    break;
case 290:
#line 1220 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], exprNat(yyvsp[0].number));
	}
    break;
case 291:
#line 1223 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], exprId(yyvsp[0].string));
	}
    break;
case 292:
#line 1226 "parser.yy"
{
	    CALL(yylsp[-1], yylsp[0], exprCallBegin(yyvsp[-1].string));	    
	  }
    break;
case 293:
#line 1228 "parser.yy"
{ 
	    CALL(yylsp[-4], yylsp[0], exprCallEnd(yyvsp[-1].number));
	}
    break;
case 294:
#line 1231 "parser.yy"
{
	    CALL(yylsp[-1], yylsp[0], exprCallBegin(yyvsp[-1].string));
	  }
    break;
case 295:
#line 1233 "parser.yy"
{   
	    REPORT_ERROR(last_loc, TypeException(PE_ARGLIST));
	    CALL(yylsp[-4], yylsp[0], exprCallEnd(0));
	}
    break;
case 296:
#line 1237 "parser.yy"
{ 
	  CALL(yylsp[-3], yylsp[0], exprArray());
	}
    break;
case 297:
#line 1240 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-3], yylsp[0], exprArray());
	}
    break;
case 299:
#line 1245 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	}
    break;
case 300:
#line 1248 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], exprPostIncrement());
	}
    break;
case 301:
#line 1251 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], exprPreIncrement());
	}
    break;
case 302:
#line 1254 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], exprPostDecrement());
	}
    break;
case 303:
#line 1257 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], exprPreDecrement());
	}
    break;
case 304:
#line 1260 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], exprUnary(yyvsp[-1].number));
	}
    break;
case 305:
#line 1263 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(LT));
	}
    break;
case 306:
#line 1266 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(LE));
	}
    break;
case 307:
#line 1269 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(EQ));
	}
    break;
case 308:
#line 1272 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(NEQ));
	}
    break;
case 309:
#line 1275 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(GT));
	}
    break;
case 310:
#line 1278 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(GE));
	}
    break;
case 311:
#line 1281 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(PLUS));
	}
    break;
case 312:
#line 1284 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(MINUS));
	}
    break;
case 313:
#line 1287 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(MULT));
	}
    break;
case 314:
#line 1290 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(DIV));
	}
    break;
case 315:
#line 1293 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(MOD));
	}
    break;
case 316:
#line 1296 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_AND));
	}
    break;
case 317:
#line 1299 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_OR));
	}
    break;
case 318:
#line 1302 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_XOR));
	}
    break;
case 319:
#line 1305 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_LSHIFT));
	}
    break;
case 320:
#line 1308 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_RSHIFT));
	}
    break;
case 321:
#line 1311 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(AND));
	}
    break;
case 322:
#line 1314 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(OR));
	}
    break;
case 323:
#line 1317 "parser.yy"
{ 
	  CALL(yylsp[-4], yylsp[-2], exprInlineIf());
	}
    break;
case 324:
#line 1320 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprDot(yyvsp[0].string));
	}
    break;
case 325:
#line 1323 "parser.yy"
{
	  CALL(yyloc, yyloc, exprDeadlock());
	}
    break;
case 326:
#line 1326 "parser.yy"
{  
	  CALL(yylsp[-1], yylsp[-1], exprUnary(NOT));
	}
    break;
case 327:
#line 1328 "parser.yy"
{
	  CALL(yylsp[-1], yylsp[-1], exprBinary(OR));
	}
    break;
case 328:
#line 1331 "parser.yy"
{
	    CALL(yylsp[-2], yylsp[0], exprBinary(MIN));
        }
    break;
case 329:
#line 1334 "parser.yy"
{
	    CALL(yylsp[-2], yylsp[0], exprBinary(MAX));
        }
    break;
case 331:
#line 1341 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprAssignment(yyvsp[-1].number));
	}
    break;
case 332:
#line 1347 "parser.yy"
{ yyval.number = ASSIGN; }
    break;
case 333:
#line 1348 "parser.yy"
{ yyval.number = ASSPLUS; }
    break;
case 334:
#line 1349 "parser.yy"
{ yyval.number = ASSMINUS; }
    break;
case 335:
#line 1350 "parser.yy"
{ yyval.number = ASSDIV; }
    break;
case 336:
#line 1351 "parser.yy"
{ yyval.number = ASSMOD; }
    break;
case 337:
#line 1352 "parser.yy"
{ yyval.number = ASSMULT; }
    break;
case 338:
#line 1353 "parser.yy"
{ yyval.number = ASSAND; }
    break;
case 339:
#line 1354 "parser.yy"
{ yyval.number = ASSOR; }
    break;
case 340:
#line 1355 "parser.yy"
{ yyval.number = ASSXOR; }
    break;
case 341:
#line 1356 "parser.yy"
{ yyval.number = ASSLSHIFT; }
    break;
case 342:
#line 1357 "parser.yy"
{ yyval.number = ASSRSHIFT; }
    break;
case 343:
#line 1362 "parser.yy"
{ yyval.number = MINUS; }
    break;
case 344:
#line 1363 "parser.yy"
{ yyval.number = NOT; }
    break;
case 345:
#line 1364 "parser.yy"
{ yyval.number = NOT; }
    break;
case 346:
#line 1369 "parser.yy"
{ yyval.number=0; }
    break;
case 347:
#line 1370 "parser.yy"
{ 
	    yyval.number=1; 
	    CALL(yylsp[0], yylsp[0], exprArg(yyval.number));
	}
    break;
case 348:
#line 1374 "parser.yy"
{ 
	    yyval.number=yyvsp[-2].number+1; 
	    CALL(yylsp[0], yylsp[0], exprArg(yyval.number));
	}
    break;
case 349:
#line 1378 "parser.yy"
{ 
	  yyval.number=yyvsp[-2].number+1; 
	  REPORT_ERROR(last_loc, TypeException(PE_ARGLIST_));
	  CALL(yylsp[0], yylsp[0], exprArg(yyval.number));
	}
    break;
case 355:
#line 1401 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], declType(ParserBuilder::PREFIX_CONST, "int", 0));
	}
    break;
case 356:
#line 1403 "parser.yy"
{ 
	  CALL(yylsp[-3], yylsp[-1], declVarEnd());
	}
    break;
case 358:
#line 1409 "parser.yy"
{ yyval.number=1; }
    break;
case 359:
#line 1410 "parser.yy"
{ yyval.number=yyvsp[-2].number+1; }
    break;
case 360:
#line 1414 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], declVar(yyvsp[-2].string, yyvsp[-1].number, true));
	}
    break;
case 361:
#line 1423 "parser.yy"
{ 
	  CALL(yylsp[-3], yylsp[0], procBegin(yyvsp[-2].string, yyvsp[-1].number));
	}
    break;
case 362:
#line 1426 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;
case 363:
#line 1429 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	  CALL(yylsp[-4], yylsp[0], procBegin(yyvsp[-3].string, yyvsp[-2].number));
	}
    break;
case 364:
#line 1433 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;
case 365:
#line 1436 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACES));
	  CALL(yylsp[-3], yylsp[0], procBegin(yyvsp[-2].string, 0));
	}
    break;
case 366:
#line 1440 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;
case 367:
#line 1443 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_PROCID));
	  CALL(yylsp[-2], yylsp[0], procBegin("_", 0));
	}
    break;
case 368:
#line 1447 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;
case 369:
#line 1450 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], procBegin(yyvsp[-1].string, 0));
	}
    break;
case 370:
#line 1453 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;
case 371:
#line 1459 "parser.yy"
{ yyval.number = 0; }
    break;
case 372:
#line 1460 "parser.yy"
{ yyval.number = yyvsp[-1].number; }
    break;
case 373:
#line 1461 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));	  
	  yyval.number = yyvsp[-1].number; 
	}
    break;
case 374:
#line 1465 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_PARAMETERS));	  
	  yyval.number = 0; 
	}
    break;
case 375:
#line 1472 "parser.yy"
{ 
	  yyval.number = yyvsp[0].number; 
	  CALL(yylsp[0], yylsp[0], declParameterEnd());
	}
    break;
case 376:
#line 1476 "parser.yy"
{ 
	  yyval.number = yyvsp[-2].number + yyvsp[0].number;
	  CALL(yylsp[-2], yylsp[0], declParameterEnd());
	}
    break;
case 377:
#line 1480 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_PARAM_DECL_));
          yyval.number = yyvsp[-2].number; 
	}
    break;
case 378:
#line 1487 "parser.yy"
{
          CALL(yylsp[-2], yylsp[0], declParameter(yyvsp[-1].string, yyvsp[0].number == 0, yyvsp[0].number));
	  yyval.number = 1;
	}
    break;
case 379:
#line 1491 "parser.yy"
{
	  CALL(yylsp[-2], yylsp[-2], declType(ParserBuilder::PREFIX_CONST, "int", false));
	  CALL(yylsp[-1], yylsp[0], declParameter(yyvsp[-1].string, false, yyvsp[0].number));
	  yyval.number = 1;
	}
    break;
case 380:
#line 1496 "parser.yy"
{ 
	  CALL(yylsp[-3], yylsp[0], declParameter(yyvsp[-1].string, yyvsp[0].number == 0, yyvsp[0].number));
	  yyval.number = yyvsp[-3].number + 1;
	}
    break;
case 385:
#line 1513 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;
case 386:
#line 1516 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;
case 387:
#line 1519 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_STATE_DECL));
	}
    break;
case 388:
#line 1522 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_STATE_DECL));
	}
    break;
case 389:
#line 1525 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_STATE));
	}
    break;
case 392:
#line 1533 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_LOC_DECL));
	}
    break;
case 393:
#line 1539 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], exprTrue(); ch->procState(yyvsp[0].string));
	}
    break;
case 394:
#line 1542 "parser.yy"
{ 
	  CALL(yylsp[-3], yylsp[0], procState(yyvsp[-3].string));
	}
    break;
case 396:
#line 1549 "parser.yy"
{	  
	  REPORT_ERROR(last_loc, TypeException(PE_INV));
	}
    break;
case 397:
#line 1552 "parser.yy"
{	  
	  REPORT_ERROR(last_loc, TypeException(PE_INV));
	  CALL(yylsp[0], yylsp[0], exprTrue());
	}
    break;
case 398:
#line 1556 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(AND));
	}
    break;
case 401:
#line 1564 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;
case 402:
#line 1567 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;
case 403:
#line 1570 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS_DECL));
	}
    break;
case 404:
#line 1573 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS_DECL));
	}
    break;
case 405:
#line 1576 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS));
	}
    break;
case 408:
#line 1584 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_ALT_TRANS));	  
	}
    break;
case 409:
#line 1590 "parser.yy"
{ 
	  strcpy(rootTransId, yyvsp[-7].string);
	  CALL(yylsp[-7], yylsp[0], procTransition(yyvsp[-7].string, yyvsp[-5].string));
	}
    break;
case 410:
#line 1594 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  strcpy(rootTransId, yyvsp[-8].string);
	  CALL(yylsp[-8], yylsp[0], procTransition(yyvsp[-8].string, yyvsp[-6].string));
	}
    break;
case 411:
#line 1599 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  strcpy(rootTransId, yyvsp[-7].string); 
	  CALL(yylsp[-7], yylsp[0], procTransition(yyvsp[-7].string, yyvsp[-5].string));
	}
    break;
case 412:
#line 1604 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	  strcpy(rootTransId, yyvsp[-8].string); 
	  CALL(yylsp[-8], yylsp[0], procTransition(yyvsp[-8].string, yyvsp[-6].string));
	}
    break;
case 413:
#line 1609 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_ARROW));
	  strcpy(rootTransId, yyvsp[-8].string); 
	  CALL(yylsp[-8], yylsp[0], procTransition(yyvsp[-8].string, yyvsp[-5].string));
	}
    break;
case 414:
#line 1618 "parser.yy"
{ 
	  CALL(yylsp[-6], yylsp[0], procTransition(rootTransId, yyvsp[-5].string));
	}
    break;
case 415:
#line 1621 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  CALL(yylsp[-6], yylsp[0], procTransition(rootTransId, yyvsp[-5].string));
	}
    break;
case 416:
#line 1625 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  CALL(yylsp[-7], yylsp[0], procTransition(rootTransId, yyvsp[-6].string));
	}
    break;
case 417:
#line 1629 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	  CALL(yylsp[-7], yylsp[0], procTransition(rootTransId, yyvsp[-6].string));
	}
    break;
case 418:
#line 1633 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	  CALL(yylsp[-7], yylsp[0], procTransition(rootTransId, yyvsp[-5].string));
	}
    break;
case 419:
#line 1637 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	  CALL(yylsp[-6], yylsp[0], procTransition(rootTransId, "_"));
	}
    break;
case 422:
#line 1646 "parser.yy"
{
	  CALL(yyloc, yyloc, procGuard());
	}
    break;
case 423:
#line 1649 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yyloc, yyloc, procGuard());
	}
    break;
case 424:
#line 1653 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yyloc, yyloc, procGuard());
	}
    break;
case 425:
#line 1657 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_GUARD_EXP));
	}
    break;
case 427:
#line 1664 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(AND));
	}
    break;
case 428:
#line 1667 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_GUARD_EXP_));
	  CALL(yylsp[-2], yylsp[0], exprBinary(AND));
	}
    break;
case 433:
#line 1682 "parser.yy"
{
		ch->quit();	
	}
    break;
case 434:
#line 1685 "parser.yy"
{
		ch->property(yyvsp[-1].number, yylsp[-1].first_line);
	}
    break;
case 435:
#line 1688 "parser.yy"
{
		ch->property(LEADSTO, yylsp[-2].first_line);
	}
    break;
case 436:
#line 1693 "parser.yy"
{ yyval.number = EF; }
    break;
case 437:
#line 1694 "parser.yy"
{ yyval.number = EG; }
    break;
case 438:
#line 1695 "parser.yy"
{ yyval.number = AF; }
    break;
case 439:
#line 1696 "parser.yy"
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
#line 1698 "parser.yy"


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

