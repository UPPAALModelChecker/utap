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
# define	T_KW_AND	284
# define	T_KW_OR	285
# define	T_KW_IMPLY	286
# define	T_KW_NOT	287
# define	T_LT	288
# define	T_LEQ	289
# define	T_EQ	290
# define	T_NEQ	291
# define	T_GEQ	292
# define	T_GT	293
# define	T_FOR	294
# define	T_WHILE	295
# define	T_DO	296
# define	T_BREAK	297
# define	T_CONTINUE	298
# define	T_SWITCH	299
# define	T_IF	300
# define	T_ELSE	301
# define	T_CASE	302
# define	T_DEFAULT	303
# define	T_RETURN	304
# define	T_TYPEDEF	305
# define	T_STRUCT	306
# define	T_CONST	307
# define	T_OLDCONST	308
# define	T_URGENT	309
# define	T_BROADCAST	310
# define	T_TRUE	311
# define	T_FALSE	312
# define	T_SYSTEM	313
# define	T_PROCESS	314
# define	T_STATE	315
# define	T_COMMIT	316
# define	T_INIT	317
# define	T_TRANS	318
# define	T_ARROW	319
# define	T_GUARD	320
# define	T_SYNC	321
# define	T_ASSIGN	322
# define	T_RATE	323
# define	T_BEFORE	324
# define	T_AFTER	325
# define	T_COST	326
# define	T_DEADLOCK	327
# define	T_EF	328
# define	T_EG	329
# define	T_AF	330
# define	T_AG	331
# define	T_LEADSTO	332
# define	T_QUIT	333
# define	T_ERROR	334
# define	T_ID	335
# define	T_TYPENAME	336
# define	T_NAT	337
# define	T_NEW	338
# define	T_NEW_DECLARATION	339
# define	T_NEW_LOCAL_DECL	340
# define	T_NEW_INST	341
# define	T_NEW_SYSTEM	342
# define	T_NEW_PARAMETERS	343
# define	T_NEW_INVARIANT	344
# define	T_NEW_GUARD	345
# define	T_NEW_SYNC	346
# define	T_NEW_ASSIGN	347
# define	T_OLD	348
# define	T_OLD_DECLARATION	349
# define	T_OLD_LOCAL_DECL	350
# define	T_OLD_INST	351
# define	T_OLD_PARAMETERS	352
# define	T_OLD_INVARIANT	353
# define	T_OLD_GUARD	354
# define	T_OLD_ASSIGN	355
# define	T_PROPERTY	356
# define	UOPERATOR	357

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



#line 261 "parser.yy"
#ifndef YYSTYPE
typedef union {
    bool flag;
    int number;
    kind_t kind;
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



#define	YYFINAL		812
#define	YYFLAG		-32768
#define	YYNTBASE	117

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 357 ? yytranslate[x] : 246)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
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
      96,    97,    98,    99,   100,   101,   102,   106
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
    1233,  1236,  1240,  1244,  1246,  1250,  1252,  1254,  1256,  1258,
    1260,  1262,  1264,  1266,  1268,  1270,  1272,  1274,  1276,  1277,
    1279,  1283,  1287,  1291,  1292,  1295,  1298,  1300,  1301,  1306,
    1310,  1312,  1316,  1320,  1321,  1329,  1330,  1339,  1340,  1348,
    1349,  1356,  1357,  1364,  1367,  1371,  1375,  1379,  1381,  1385,
    1389,  1393,  1397,  1402,  1408,  1409,  1412,  1416,  1421,  1425,
    1429,  1432,  1434,  1436,  1440,  1444,  1446,  1451,  1453,  1457,
    1459,  1463,  1464,  1468,  1473,  1477,  1481,  1484,  1486,  1488,
    1492,  1496,  1505,  1515,  1524,  1534,  1544,  1552,  1560,  1569,
    1578,  1587,  1595,  1597,  1598,  1602,  1607,  1611,  1614,  1616,
    1620,  1624,  1627,  1628,  1632,  1633,  1635,  1638,  1642,  1644,
    1646,  1648
};
static const short yyrhs[] =
{
      84,   118,     0,    85,   123,     0,    86,   161,     0,    87,
     119,     0,    88,   121,     0,    88,     1,     0,    89,   134,
       0,    90,   207,     0,    91,   207,     0,    92,   172,     0,
      93,   206,     0,    94,   215,     0,    95,   216,     0,    96,
     231,     0,    97,   119,     0,    98,   228,     0,    99,   235,
       0,   100,   241,     0,   101,   206,     0,   102,   242,     0,
     123,   119,   121,     0,     0,     0,   119,    81,     3,    81,
     107,   120,   214,   108,   112,     0,   119,    81,     3,    81,
     107,     1,   108,   112,     0,   119,    81,     3,    81,   107,
       1,   112,     0,   119,    81,     3,    81,     1,   112,     0,
     119,    81,     1,   112,     0,    59,   122,   112,     0,    59,
     122,     1,   112,     0,    59,     1,   112,     0,    81,     0,
     122,   113,    81,     0,   122,   113,     1,     0,     0,   123,
     131,     0,   123,   136,     0,   123,   144,     0,   123,   157,
       0,   123,   124,     0,   123,   127,     0,   123,   128,     0,
      69,   114,   125,   115,     0,     0,   125,   126,   112,     0,
      72,   104,   207,     0,    70,   114,   129,   115,     0,    71,
     114,   130,   115,     0,     0,   129,   211,   112,     0,     0,
     130,   211,   112,     0,     0,   147,   148,   133,   132,   179,
       0,   107,   108,     0,   107,   134,   108,     0,   107,   134,
       1,   108,     0,   107,   134,     1,     0,   107,     1,   108,
       0,   107,     1,     0,   135,     0,   134,   113,   135,     0,
     134,   113,     1,     0,   147,   105,    81,   143,     0,   147,
      81,   143,     0,   147,     1,     0,   147,   137,   112,     0,
     147,   137,     1,   112,     0,   147,     1,   112,     0,   138,
       0,   137,   113,   138,     0,   137,   113,     1,     0,   148,
     143,   139,     0,     0,     3,   140,     0,     3,     1,     0,
     207,     0,   114,   141,   115,     0,   114,   141,     1,   115,
       0,   114,     1,   115,     0,   142,     0,   141,   113,   142,
       0,   141,   113,     1,     0,   148,   104,   140,     0,   148,
     104,     1,     0,   140,     0,     0,   143,   109,   207,   110,
       0,   143,   109,   207,     1,   110,     0,   143,   109,   207,
       1,     0,   143,   109,     1,   110,     0,   143,   109,     1,
       0,    51,   147,   145,   112,     0,    51,   147,   145,     1,
     112,     0,    51,   147,     1,   112,     0,    51,     1,   112,
       0,   146,     0,   145,   113,   146,     0,   145,   113,     1,
       0,   148,   143,     0,   153,    82,   154,     0,   153,    52,
     114,   149,   115,     0,   153,    52,   114,     1,   115,     0,
     153,    52,   114,     1,     0,   153,    52,     1,     0,    81,
       0,    82,     0,   150,     0,   149,   150,     0,   149,     1,
       0,   147,   151,   112,     0,   147,   151,     1,   112,     0,
     147,     1,   112,     0,   147,     1,     0,     1,   112,     0,
     152,     0,   151,   113,   152,     0,   151,   113,     1,     0,
     148,   143,     0,     0,    55,     0,    56,     0,    55,    56,
       0,    53,     0,     0,   109,   207,   113,   207,   110,     0,
     109,   207,   113,   207,     1,   110,     0,   109,   207,   113,
     207,     1,     0,   109,   207,   113,     1,   110,     0,   109,
       1,   113,   207,   110,     0,     0,   109,     1,   113,   155,
       1,   110,     0,     0,   109,   207,     1,   113,   156,   207,
     110,     0,   109,   207,     1,   110,     0,   109,   207,     1,
       0,   109,     1,     0,     0,    60,   148,   133,   114,   158,
     160,   115,     0,    60,   148,   133,     1,   114,   160,   115,
       0,     0,    60,   148,   114,   159,   160,   115,     0,    60,
       1,   114,   160,   115,     0,   161,   162,   174,   165,   166,
       0,     0,   161,   131,     0,   161,   136,     0,   161,   144,
       0,    61,   163,   112,     0,    61,   163,     1,   112,     0,
      61,   163,     1,     0,    61,     1,   112,     0,    61,     1,
       0,     1,   112,     0,   164,     0,   163,   113,   164,     0,
     163,   113,     1,     0,    81,     0,    81,   114,   207,   115,
       0,    81,   114,   207,     1,   115,     0,    81,   114,   207,
       1,     0,    81,   114,     1,   115,     0,    81,   114,     1,
       0,    63,    81,   112,     0,    63,    81,     1,   112,     0,
      63,    81,     1,     0,    63,     1,     0,     1,     0,     0,
      64,   167,   112,     0,    64,   167,     1,   112,     0,    64,
     167,     1,     0,    64,     1,     0,     1,     0,   168,     0,
     167,   113,   169,     0,   167,   113,     1,     0,    81,    65,
      81,   114,   170,   171,   173,   115,     0,    81,    65,    81,
     114,   170,   171,   173,     1,   112,     0,    81,    65,    81,
       1,   115,     0,    81,    65,     1,   115,     0,    81,     1,
     115,     0,    65,    81,   114,   170,   171,   173,   115,     0,
      65,    81,   114,   170,   171,   173,     1,   115,     0,    65,
      81,     1,   115,     0,    65,     1,   115,     0,   168,     0,
       0,    66,   207,   112,     0,    66,   207,     1,   112,     0,
      66,     1,   112,     0,     0,    67,   172,   112,     0,    67,
     172,     1,   112,     0,    67,   172,     1,     0,    67,     1,
     112,     0,   207,    14,     0,   207,     1,    14,     0,   207,
     103,     0,   207,     1,   103,     0,   207,     1,     0,     0,
      68,   206,   112,     0,    68,     1,   112,     0,     0,   175,
       0,   176,     0,   175,   176,     0,    62,   177,   112,     0,
      62,   177,     1,   112,     0,    62,   177,     1,     0,    62,
       1,   112,     0,    62,     1,     0,    55,   178,   112,     0,
      55,   178,     1,   112,     0,    55,   178,     1,     0,    55,
       1,   112,     0,    55,     1,     0,    81,     0,   177,   113,
      81,     0,   177,   113,     1,     0,    81,     0,   178,   113,
      81,     0,   178,   113,     1,     0,     0,   114,   180,   182,
     183,   115,     0,     0,   114,   181,     1,   115,     0,     0,
     182,   136,     0,   182,   144,     0,     0,   183,   184,     0,
     179,     0,   112,     0,   207,   112,     0,   207,     1,   112,
       0,     0,    40,   107,   185,   206,   112,   206,   112,   206,
     108,   184,     0,     0,    40,   107,     1,   186,   205,   112,
     205,   112,   205,   108,   184,     0,     0,    40,     1,   107,
     187,   205,   112,   205,   112,   205,   108,   184,     0,     0,
      41,   107,   188,   206,   108,   184,     0,     0,    41,     1,
     107,   189,   206,   108,   184,     0,     0,    41,   107,     1,
     190,   206,   108,   184,     0,     0,    42,   191,   184,    41,
     107,   206,   108,   112,     0,     0,    46,   107,   192,   206,
     108,   184,   196,     0,    43,   112,     0,    43,     1,   112,
       0,    44,   112,     0,    44,     1,   112,     0,     0,    45,
     107,   206,   108,   193,   114,   199,   115,     0,     0,    45,
       1,   107,   206,   108,   194,   114,   199,   115,     0,     0,
      45,   107,     1,   206,   108,   195,   114,   199,   115,     0,
      50,   207,   112,     0,    50,   207,     1,     0,    50,   112,
       0,    50,     1,     0,     0,     0,    47,   197,   184,     0,
       0,    47,   198,     1,     0,   200,     0,   199,   200,     0,
       0,    48,   207,   104,   201,   183,     0,     0,    48,     1,
     104,   202,   183,     0,     0,    49,   104,   203,   183,     0,
       0,    49,     1,   104,   204,   183,     0,     0,   206,     0,
     207,     0,   206,   113,   207,     0,   206,   113,     1,     0,
      58,     0,    57,     0,    83,     0,    81,     0,     0,    81,
     107,   208,   214,   108,     0,     0,    81,   107,   209,     1,
     108,     0,   207,   109,   207,   110,     0,   207,   109,     1,
     110,     0,   107,   207,   108,     0,   107,     1,   108,     0,
     207,    15,     0,    15,   207,     0,   207,    16,     0,    16,
     207,     0,   213,   207,     0,   207,    34,   207,     0,   207,
      35,   207,     0,   207,    36,   207,     0,   207,    37,   207,
       0,   207,    39,   207,     0,   207,    38,   207,     0,   207,
      17,   207,     0,   207,    18,   207,     0,   207,    19,   207,
       0,   207,    20,   207,     0,   207,    23,   207,     0,   207,
     105,   207,     0,   207,    24,   207,     0,   207,    25,   207,
       0,   207,    26,   207,     0,   207,    27,   207,     0,   207,
      28,   207,     0,   207,    29,   207,     0,   207,   103,   207,
     104,   207,     0,   207,   111,    81,     0,    73,     0,     0,
     207,    32,   210,   207,     0,   207,    30,   207,     0,   207,
      31,   207,     0,    33,   207,     0,   207,    21,   207,     0,
     207,    22,   207,     0,   211,     0,   207,   212,   207,     0,
       3,     0,     4,     0,     5,     0,     7,     0,     8,     0,
       6,     0,    10,     0,     9,     0,    11,     0,    12,     0,
      13,     0,    18,     0,    14,     0,     0,   207,     0,   214,
     113,   207,     0,   214,   113,     1,     0,   216,   119,   121,
       0,     0,   216,   217,     0,   216,   221,     0,   136,     0,
       0,    54,   218,   219,   112,     0,    54,     1,   112,     0,
     220,     0,   219,   113,   220,     0,    81,   143,   140,     0,
       0,    60,   148,   227,   114,   222,   230,   115,     0,     0,
      60,   148,   227,     1,   114,   223,   230,   115,     0,     0,
      60,   148,     1,   114,   224,   230,   115,     0,     0,    60,
       1,   114,   225,   230,   115,     0,     0,    60,   148,   114,
     226,   230,   115,     0,   107,   108,     0,   107,   228,   108,
       0,   107,   228,     1,     0,   107,     1,   108,     0,   229,
       0,   228,   112,   229,     0,   228,   112,     1,     0,   147,
      81,   143,     0,    54,    81,   143,     0,   229,   113,    81,
     143,     0,   231,   232,   174,   165,   236,     0,     0,   231,
     217,     0,    61,   233,   112,     0,    61,   233,     1,   112,
       0,    61,   233,     1,     0,    61,     1,   112,     0,    61,
       1,     0,     1,     0,   234,     0,   233,   113,   234,     0,
     233,   113,     1,     0,    81,     0,    81,   114,   235,   115,
       0,   207,     0,   207,     1,   113,     0,     1,     0,   235,
     113,   207,     0,     0,    64,   237,   112,     0,    64,   237,
       1,   112,     0,    64,   237,     1,     0,    64,     1,   112,
       0,    64,     1,     0,     1,     0,   238,     0,   237,   113,
     239,     0,   237,   113,     1,     0,    81,    65,    81,   114,
     240,   171,   173,   115,     0,    81,    65,    81,   114,   240,
     171,   173,     1,   115,     0,    81,    65,    81,   114,   240,
     171,   173,     1,     0,    81,    65,    81,     1,   114,   240,
     171,   173,   115,     0,    81,     1,    65,    81,   114,   240,
     171,   173,   115,     0,    65,    81,   114,   240,   171,   173,
     115,     0,    65,    81,   114,   240,   171,   173,     1,     0,
      65,    81,   114,   240,   171,   173,     1,   115,     0,    65,
      81,     1,   114,   240,   171,   173,   115,     0,    65,     1,
      81,   114,   240,   171,   173,   115,     0,    65,     1,   114,
     240,   171,   173,   115,     0,   238,     0,     0,    66,   241,
     112,     0,    66,   241,     1,   112,     0,    66,   241,     1,
       0,    66,     1,     0,   207,     0,   241,   113,   207,     0,
     241,   113,     1,     0,   243,   244,     0,     0,   243,   244,
     116,     0,     0,    79,     0,   245,   207,     0,   207,    78,
     207,     0,    74,     0,    75,     0,    76,     0,    77,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   273,   275,   276,   277,   278,   279,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   298,   302,   304,   304,   309,   312,   315,   318,   323,
     325,   328,   333,   335,   336,   341,   343,   344,   345,   346,
     347,   348,   349,   352,   354,   356,   358,   361,   363,   365,
     367,   371,   373,   377,   377,   386,   388,   389,   393,   397,
     401,   412,   414,   415,   421,   426,   430,   435,   439,   443,
     449,   451,   452,   457,   463,   465,   466,   472,   474,   477,
     481,   487,   489,   490,   496,   500,   503,   508,   510,   511,
     515,   519,   523,   529,   533,   537,   541,   552,   554,   555,
     561,   567,   571,   574,   578,   582,   587,   589,   592,   594,
     595,   601,   606,   611,   614,   617,   622,   624,   625,   631,
     637,   639,   640,   641,   642,   645,   647,   648,   652,   656,
     661,   666,   666,   676,   676,   683,   689,   695,   707,   707,
     714,   717,   717,   725,   734,   738,   740,   741,   742,   745,
     747,   750,   753,   756,   759,   764,   766,   767,   772,   776,
     779,   783,   787,   791,   797,   801,   805,   809,   812,   817,
     819,   820,   823,   826,   829,   834,   836,   837,   842,   847,
     852,   855,   858,   863,   867,   871,   874,   877,   881,   883,
     886,   890,   895,   897,   898,   901,   904,   909,   913,   917,
     920,   924,   930,   932,   935,   940,   942,   943,   944,   947,
     949,   952,   955,   958,   963,   965,   968,   971,   974,   979,
     983,   986,   991,   995,   998,  1008,  1008,  1015,  1015,  1024,
    1026,  1027,  1030,  1032,  1035,  1037,  1040,  1043,  1047,  1047,
    1053,  1053,  1061,  1061,  1069,  1069,  1075,  1075,  1082,  1082,
    1089,  1089,  1095,  1095,  1099,  1102,  1106,  1109,  1113,  1113,
    1119,  1119,  1126,  1126,  1133,  1136,  1140,  1143,  1149,  1153,
    1153,  1159,  1159,  1168,  1170,  1173,  1173,  1180,  1180,  1187,
    1187,  1193,  1193,  1202,  1204,  1207,  1209,  1212,  1217,  1221,
    1224,  1227,  1230,  1230,  1235,  1235,  1241,  1244,  1248,  1249,
    1253,  1256,  1259,  1262,  1265,  1268,  1271,  1274,  1277,  1280,
    1283,  1286,  1289,  1292,  1295,  1298,  1301,  1304,  1307,  1310,
    1313,  1316,  1319,  1322,  1325,  1328,  1331,  1331,  1336,  1339,
    1342,  1345,  1348,  1351,  1354,  1359,  1362,  1363,  1364,  1365,
    1366,  1367,  1368,  1369,  1370,  1371,  1374,  1377,  1380,  1383,
    1387,  1391,  1402,  1406,  1408,  1409,  1412,  1414,  1414,  1419,
    1421,  1423,  1426,  1435,  1435,  1442,  1442,  1449,  1449,  1456,
    1456,  1463,  1463,  1471,  1473,  1474,  1478,  1484,  1489,  1493,
    1499,  1504,  1509,  1515,  1519,  1521,  1524,  1526,  1529,  1532,
    1535,  1538,  1543,  1545,  1546,  1551,  1555,  1560,  1562,  1565,
    1569,  1574,  1576,  1577,  1580,  1583,  1586,  1589,  1594,  1596,
    1597,  1602,  1607,  1612,  1617,  1622,  1630,  1634,  1638,  1642,
    1646,  1650,  1654,  1657,  1659,  1662,  1666,  1670,  1675,  1677,
    1680,  1686,  1689,  1691,  1693,  1695,  1698,  1701,  1705,  1707,
    1708,  1709
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
  "']'", "'.'", "';'", "','", "'{'", "'}'", "'\\n'", "Uppaal", "XTA", 
  "Inst", "@1", "System", "ProcessList", "Declaration", "RateDecl", 
  "RateList", "Rate", "BeforeUpdateDecl", "AfterUpdateDecl", 
  "BeforeAssignmentList", "AfterAssignmentList", "FunctionDecl", "@2", 
  "OptionalParameterList", "ParameterList", "Parameter", "VariableDecl", 
  "DeclIdList", "DeclId", "VarInit", "Initializer", "FieldInitList", 
  "FieldInit", "ArrayDecl", "TypeDecl", "TypeIdList", "TypeId", "Type", 
  "Id", "FieldDeclList", "FieldDecl", "FieldDeclIdList", "FieldDeclId", 
  "TypePrefix", "Range", "@3", "@4", "ProcDecl", "@5", "@6", "ProcBody", 
  "ProcLocalDeclList", "States", "StateDeclList", "StateDecl", "Init", 
  "Transitions", "TransitionList", "Transition", "TransitionOpt", "Guard", 
  "Sync", "SyncExpr", "Assign", "LocFlags", "Commit", "Urgent", 
  "CStateList", "UStateList", "Block", "@7", "@8", "BlockLocalDeclList", 
  "StatementList", "Statement", "@9", "@10", "@11", "@12", "@13", "@14", 
  "@15", "@16", "@17", "@18", "@19", "ElsePart", "@20", "@21", 
  "SwitchCaseList", "SwitchCase", "@22", "@23", "@24", "@25", "ExprList0", 
  "ExprList", "Expression", "@26", "@27", "@28", "Assignment", "AssignOp", 
  "UnaryOp", "ArgList", "OldXTA", "OldDeclaration", "OldVarDecl", "@29", 
  "OldConstDeclIdList", "OldConstDeclId", "OldProcDecl", "@30", "@31", 
  "@32", "@33", "@34", "OldProcParams", "OldProcParamList", 
  "OldProcParam", "OldProcBody", "OldVarDeclList", "OldStates", 
  "OldStateDeclList", "OldStateDecl", "OldInvariant", "OldTransitions", 
  "OldTransitionList", "OldTransition", "OldTransitionOpt", "OldGuard", 
  "OldGuardList", "PropertyList", "PropertyList2", "Property", 
  "Quantifier", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   118,   119,   120,   119,   119,   119,   119,   119,   121,
     121,   121,   122,   122,   122,   123,   123,   123,   123,   123,
     123,   123,   123,   124,   125,   125,   126,   127,   128,   129,
     129,   130,   130,   132,   131,   133,   133,   133,   133,   133,
     133,   134,   134,   134,   135,   135,   135,   136,   136,   136,
     137,   137,   137,   138,   139,   139,   139,   140,   140,   140,
     140,   141,   141,   141,   142,   142,   142,   143,   143,   143,
     143,   143,   143,   144,   144,   144,   144,   145,   145,   145,
     146,   147,   147,   147,   147,   147,   148,   148,   149,   149,
     149,   150,   150,   150,   150,   150,   151,   151,   151,   152,
     153,   153,   153,   153,   153,   154,   154,   154,   154,   154,
     154,   155,   154,   156,   154,   154,   154,   154,   158,   157,
     157,   159,   157,   157,   160,   161,   161,   161,   161,   162,
     162,   162,   162,   162,   162,   163,   163,   163,   164,   164,
     164,   164,   164,   164,   165,   165,   165,   165,   165,   166,
     166,   166,   166,   166,   166,   167,   167,   167,   168,   168,
     168,   168,   168,   169,   169,   169,   169,   169,   170,   170,
     170,   170,   171,   171,   171,   171,   171,   172,   172,   172,
     172,   172,   173,   173,   173,   174,   174,   174,   174,   175,
     175,   175,   175,   175,   176,   176,   176,   176,   176,   177,
     177,   177,   178,   178,   178,   180,   179,   181,   179,   182,
     182,   182,   183,   183,   184,   184,   184,   184,   185,   184,
     186,   184,   187,   184,   188,   184,   189,   184,   190,   184,
     191,   184,   192,   184,   184,   184,   184,   184,   193,   184,
     194,   184,   195,   184,   184,   184,   184,   184,   196,   197,
     196,   198,   196,   199,   199,   201,   200,   202,   200,   203,
     200,   204,   200,   205,   205,   206,   206,   206,   207,   207,
     207,   207,   208,   207,   209,   207,   207,   207,   207,   207,
     207,   207,   207,   207,   207,   207,   207,   207,   207,   207,
     207,   207,   207,   207,   207,   207,   207,   207,   207,   207,
     207,   207,   207,   207,   207,   207,   210,   207,   207,   207,
     207,   207,   207,   207,   211,   212,   212,   212,   212,   212,
     212,   212,   212,   212,   212,   212,   213,   213,   214,   214,
     214,   214,   215,   216,   216,   216,   217,   218,   217,   217,
     219,   219,   220,   222,   221,   223,   221,   224,   221,   225,
     221,   226,   221,   227,   227,   227,   227,   228,   228,   228,
     229,   229,   229,   230,   231,   231,   232,   232,   232,   232,
     232,   232,   233,   233,   233,   234,   234,   235,   235,   235,
     235,   236,   236,   236,   236,   236,   236,   236,   237,   237,
     237,   238,   238,   238,   238,   238,   239,   239,   239,   239,
     239,   239,   239,   240,   240,   240,   240,   240,   241,   241,
     241,   242,   243,   243,   244,   244,   244,   244,   245,   245,
     245,   245
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
       2,     3,     3,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     1,
       3,     3,     3,     0,     2,     2,     1,     0,     4,     3,
       1,     3,     3,     0,     7,     0,     8,     0,     7,     0,
       6,     0,     6,     2,     3,     3,     3,     1,     3,     3,
       3,     3,     4,     5,     0,     2,     3,     4,     3,     3,
       2,     1,     1,     3,     3,     1,     4,     1,     3,     1,
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
       0,    35,    35,   145,    22,     0,   120,     0,     0,     0,
       0,   353,   353,   384,    22,   120,     0,     0,     0,   432,
       1,    22,   120,   120,     4,     6,     0,     5,   124,   121,
     122,     7,    61,     0,     0,   347,     0,     0,   346,     0,
     289,   288,   325,   291,   290,     0,     8,   333,     0,     9,
      10,     0,    11,   285,    12,    22,   120,   120,    15,     0,
       0,    16,   377,   399,     0,    17,   428,    18,    19,    20,
     434,     0,     0,     0,     0,     0,     0,    40,    41,    42,
      36,    37,    38,     0,    39,   146,   147,   148,     0,     0,
      32,     0,   123,     0,    66,    87,     0,     0,   125,   301,
     303,   330,   292,     0,     0,   335,   336,   337,   340,   338,
     339,   342,   341,   343,   344,   345,   300,   302,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   326,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   304,   201,   197,   199,     0,
       0,     0,     0,   356,     0,   354,   355,   385,    87,    87,
       0,     0,     0,     0,     0,   438,   439,   440,   441,   435,
       0,   431,     0,     0,     0,     0,   106,   107,     0,    44,
      49,    51,    21,     0,     0,    70,    87,     0,     0,    31,
       0,    29,     0,    63,    62,    65,    87,   105,     0,     0,
     101,   348,     0,   299,   298,   311,   312,   313,   314,   331,
     332,   315,   317,   318,   319,   320,   321,   322,   328,   329,
       0,   305,   306,   307,   308,   310,   309,     0,   316,     0,
       0,   324,   334,   198,   200,   287,   286,     0,     0,     0,
       0,   352,    87,   381,   380,   379,   378,    87,   398,   400,
     430,   429,     0,   433,   436,    96,     0,     0,    97,    87,
     145,     0,   141,     0,     0,     0,     0,    69,     0,    67,
       0,    53,    74,    28,     0,    30,    34,    33,     0,    64,
     104,     0,     0,   108,   137,     0,   349,     0,     0,   327,
       0,   297,   296,   359,    87,     0,   360,   369,     0,     0,
     371,     0,   382,   437,    95,     0,    93,     0,   100,     0,
       0,    60,    55,     0,   145,     0,   138,     0,    43,     0,
      47,     0,   333,    48,   333,    68,    72,    71,     0,     0,
      73,     0,     0,    92,     0,   115,   103,   114,    87,     0,
     116,   110,   102,   109,   131,   136,     0,   293,     0,   295,
     323,     0,   358,     0,   384,   367,     0,   373,     0,   384,
       0,   363,    94,    99,    98,   143,     0,     0,   205,    59,
      58,    56,     0,   145,   145,     0,    45,    50,    52,   225,
      54,    76,     0,    75,    77,    27,     0,   348,    91,    90,
      88,   113,   119,     0,   111,     0,     0,     0,   135,   133,
       0,     0,   351,   350,   362,   361,     0,     0,   384,   376,
     375,   374,     0,   365,   384,   154,   153,   158,     0,   155,
       0,     0,     0,   206,   207,    57,   142,     0,     0,    46,
     229,     0,     0,   291,    86,     0,    81,     0,     0,    26,
       0,    89,   112,   118,   117,     0,   130,     0,   129,   128,
     126,   370,   391,     0,   205,     0,   372,   384,     0,   152,
       0,   151,   149,     0,   218,   222,     0,   213,   219,     0,
     168,     0,     0,   208,   140,   139,   232,     0,    80,     0,
       0,    78,     0,    25,     0,   132,     0,   127,   390,   395,
       0,   392,     0,   368,     0,   364,   163,     0,   150,   157,
     156,   217,   216,   214,     0,   212,   211,   209,     0,   167,
       0,   174,     0,   144,   230,   231,     0,   228,    79,    83,
      82,    85,    84,    24,   134,   389,     0,   388,   386,     0,
       0,   366,   162,   161,   159,   215,   224,   223,   210,   221,
     220,   166,   164,   173,     0,     0,   175,     0,     0,   250,
       0,     0,     0,     0,     0,   235,   226,   234,   233,     0,
       0,   387,   394,   393,   407,     0,   383,   160,   165,     0,
       0,   172,   170,     0,     0,     0,     0,     0,     0,     0,
     254,     0,   256,     0,     0,   252,   267,   266,     0,     0,
     236,   396,   406,     0,     0,   408,   182,     0,     0,   171,
     177,     0,   187,   176,   242,   240,     0,   246,   248,     0,
       0,   255,   257,     0,     0,     0,     0,   265,   264,   237,
     405,     0,     0,   404,   402,     0,   181,     0,   188,     0,
       0,   283,   283,     0,     0,     0,     0,     0,     0,     0,
     258,     0,     0,     0,   403,   410,     0,   422,   409,   180,
       0,   192,   186,     0,   188,     0,   284,     0,     0,     0,
       0,     0,     0,   260,   262,     0,     0,     0,     0,   423,
       0,     0,     0,     0,     0,   202,   185,   192,   283,   283,
       0,     0,     0,   245,     0,     0,     0,     0,   268,   423,
     423,     0,   192,     0,   423,     0,   423,   191,     0,   189,
       0,     0,     0,     0,   202,     0,     0,     0,   247,   249,
       0,     0,     0,     0,     0,     0,   273,   269,   253,   192,
     192,   427,     0,   202,   423,   192,   423,   192,   190,   196,
     195,   193,     0,     0,     0,   178,     0,   283,   283,     0,
     251,     0,     0,     0,     0,     0,   279,   259,   274,     0,
       0,   202,   202,   426,   424,     0,   192,   202,   192,   202,
     194,   204,   203,   179,     0,   183,     0,     0,     0,   261,
     263,   277,   275,   281,   232,   270,   272,     0,     0,   425,
     413,   411,   202,     0,   202,     0,   184,     0,     0,   239,
     232,   232,   232,   280,   415,   414,   412,     0,   421,     0,
     417,   416,   243,   241,   278,   276,   282,   420,   419,   418,
       0,     0,     0
};

static const short yydefgoto[] =
{
     810,    20,    24,   387,    27,    91,    21,    77,   264,   319,
      78,    79,   265,   266,    80,   328,   263,    31,    32,   153,
     184,   185,   330,   434,   435,   436,   272,    82,   257,   258,
     154,   242,   282,   283,   339,   340,    34,   200,   396,   447,
      84,   374,   314,   309,   310,   368,   418,   419,   472,   513,
     545,   546,   603,   651,   675,    50,   703,   422,   423,   424,
     469,   466,   557,   430,   431,   476,   516,   558,   606,   632,
     631,   609,   634,   635,   578,   616,   665,   685,   686,   718,
     749,   750,   715,   716,   791,   790,   774,   792,   655,   656,
      53,   201,   202,   220,    47,   144,    48,   287,    54,    55,
     155,   238,   295,   296,   156,   414,   457,   408,   354,   359,
     301,    61,    62,   406,   407,   454,   490,   491,    65,   566,
     594,   595,   648,   692,    67,    69,    70,   171,   172
};

static const short yypact[] =
{
     968,-32768,-32768,-32768,-32768,   275,   704,  2836,  2836,  2836,
    2836,-32768,-32768,-32768,-32768,   699,   290,  2836,  2836,-32768,
  -32768,   850,  1926,   749,   -28,-32768,    15,-32768,-32768,   145,
  -32768,   -42,-32768,   187,   -31,-32768,  2836,  2836,-32768,  2836,
  -32768,-32768,-32768,   125,-32768,   580,  1858,-32768,  2836,  1858,
  -32768,  1124,   154,  1858,-32768,   885,   649,   635,   -28,   201,
     212,   191,   266,-32768,   383,   321,  1858,   350,   154,-32768,
    2808,   260,   229,   352,   357,   363,    -9,-32768,-32768,-32768,
  -32768,-32768,-32768,   272,-32768,-32768,-32768,-32768,    51,   368,
  -32768,    61,-32768,   578,-32768,-32768,   410,    30,   384,   210,
     210,  2004,   494,   389,  1311,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,  2836,  2836,
    2836,  2836,  2836,  2836,  2836,  2836,  2836,  2836,  2836,  2836,
    2836,  2836,  2836,-32768,  2836,  2836,  2836,  2836,  2836,  2836,
    2836,  2836,  2033,   418,  2836,   210,   132,-32768,  2836,  2044,
     183,   276,    -9,-32768,   272,-32768,-32768,-32768,-32768,-32768,
     710,   429,   421,  2836,  2053,-32768,-32768,-32768,-32768,-32768,
    1420,   425,  2836,   426,   288,   431,-32768,-32768,   135,-32768,
  -32768,-32768,-32768,   437,    63,-32768,   469,   471,   485,-32768,
     473,-32768,   236,-32768,-32768,   484,-32768,-32768,   617,  2064,
  -32768,  2836,   596,-32768,-32768,   586,   586,   210,   210,   536,
     536,   210,  2701,  2726,   513,   513,  2645,  2620,  2004,  1895,
    2836,   409,   409,  2781,  2781,   409,   409,  1457,  2751,   509,
    1566,-32768,  2004,-32768,-32768,-32768,  1858,   511,   540,   534,
      48,-32768,-32768,   484,   484,-32768,   266,-32768,-32768,  1858,
  -32768,  1858,  2836,-32768,  1858,-32768,   515,    65,-32768,-32768,
  -32768,   232,-32768,    47,   -50,  2368,  2415,-32768,   543,-32768,
     300,-32768,    40,-32768,    45,-32768,-32768,-32768,  2117,   484,
     240,   361,    24,-32768,   512,   822,  1858,   128,   557,  1895,
    2836,-32768,-32768,-32768,-32768,   -89,-32768,-32768,   554,   199,
  -32768,    54,   484,  1858,-32768,   564,-32768,   422,   484,   570,
     274,   585,-32768,    77,-32768,   584,-32768,   665,-32768,   588,
  -32768,  1858,   661,-32768,   664,-32768,-32768,-32768,   670,   443,
  -32768,   667,   507,   675,  1163,-32768,-32768,   676,-32768,    83,
  -32768,   678,-32768,-32768,  2836,   254,  2128,-32768,  2148,-32768,
    2595,  2495,-32768,   540,-32768,-32768,   683,-32768,    74,-32768,
     679,-32768,-32768,-32768,-32768,-32768,   682,   243,   323,-32768,
     687,-32768,   681,-32768,-32768,  2836,-32768,-32768,-32768,   802,
  -32768,-32768,   165,-32768,  1858,-32768,   -38,  2836,-32768,   696,
  -32768,-32768,   484,   695,-32768,   461,   807,  1603,-32768,-32768,
     700,  1274,-32768,  1858,-32768,-32768,   694,   625,-32768,-32768,
  -32768,-32768,   698,-32768,-32768,-32768,   703,   697,    90,-32768,
     262,   279,   223,   761,-32768,-32768,-32768,   702,   706,  1858,
  -32768,   818,   707,   334,-32768,    32,-32768,   732,   743,-32768,
     149,-32768,-32768,-32768,-32768,   753,-32768,  2836,-32768,   794,
  -32768,-32768,-32768,   295,   323,   792,-32768,-32768,   793,-32768,
    2179,   797,-32768,   358,   799,-32768,    92,   800,-32768,    94,
  -32768,   364,    36,-32768,-32768,-32768,   719,   798,-32768,   801,
     432,-32768,   454,-32768,   803,-32768,  1712,-32768,   805,   804,
      96,-32768,   223,-32768,   809,-32768,   811,   709,-32768,-32768,
  -32768,-32768,   817,-32768,   371,-32768,   824,-32768,   373,-32768,
      14,-32768,   436,-32768,-32768,-32768,  2424,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,   290,   830,-32768,   463,
      38,-32768,-32768,   819,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,   831,-32768,-32768,    16,   102,-32768,    82,    84,-32768,
      85,   100,   103,   837,   559,-32768,-32768,-32768,-32768,   861,
     336,-32768,-32768,-32768,-32768,   477,-32768,-32768,-32768,   832,
     501,   834,-32768,    27,   841,  2201,   842,  2212,  2475,   838,
  -32768,   839,-32768,   845,  2232,-32768,-32768,-32768,   973,   844,
  -32768,-32768,   846,   273,   106,-32768,-32768,   847,    55,-32768,
  -32768,   505,-32768,-32768,-32768,-32768,  2836,-32768,-32768,  2836,
     873,-32768,-32768,  2836,  2836,   189,  2836,-32768,-32768,-32768,
  -32768,   889,   876,   848,-32768,   255,-32768,   853,   893,   854,
      56,  2836,  2836,   220,  2836,  2836,   237,   856,   238,   366,
  -32768,   459,   880,    57,-32768,-32768,   506,-32768,-32768,-32768,
    2263,   898,-32768,   860,   893,   859,   154,   875,  2836,   476,
     491,  2475,  2836,-32768,-32768,   892,  2475,   900,   912,   979,
     -47,    58,   959,  1012,  2296,  1004,-32768,   898,  2836,  2836,
     499,  2475,  2475,-32768,   531,   960,   961,   634,  1026,   979,
     979,  2308,   898,   963,   979,   965,   979,-32768,   969,-32768,
     971,   104,  2317,    25,  1004,   974,   975,  2836,-32768,-32768,
     976,   634,   634,  2379,    46,   180,-32768,  1079,-32768,   898,
     898,-32768,   108,  1004,   979,   898,   979,   898,-32768,-32768,
     977,-32768,   978,   655,   980,-32768,    39,  2836,  2836,   533,
  -32768,   433,   521,   987,  1749,   989,-32768,-32768,-32768,  2475,
    1093,  1004,  1004,   983,-32768,    43,   898,  1004,   898,  1004,
  -32768,-32768,-32768,-32768,   981,-32768,   990,   991,  2475,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,   982,   985,-32768,
     986,-32768,  1004,   988,  1004,    44,-32768,  2475,  2475,-32768,
  -32768,-32768,-32768,  2475,-32768,-32768,-32768,   992,-32768,   993,
     994,-32768,-32768,-32768,  2475,  2475,  2475,-32768,-32768,-32768,
    1102,  1104,-32768
};

static const short yypgoto[] =
{
  -32768,-32768,     6,-32768,   -58,-32768,  1103,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,   -10,-32768,   920,   849,  1018,   -16,
  -32768,   843,-32768,  -315,-32768,   632,   -60,   -20,-32768,   812,
      67,   -64,-32768,   836,-32768,   721,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,   277,  1111,-32768,-32768,   657,   630,-32768,
  -32768,   553,-32768,   503,    31,   522,   171,   711,-32768,   754,
  -32768,-32768,   877,-32768,-32768,-32768,  -307,  -518,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,    66,  -673,-32768,-32768,-32768,-32768,  -439,    -6,
      -7,-32768,-32768,-32768,   517,-32768,-32768,   816,-32768,  1192,
     -46,-32768,-32768,   855,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,   907,  1047,  -148,  1196,-32768,-32768,   684,   685,-32768,
  -32768,   587,-32768,   -32,   519,-32768,-32768,-32768,-32768
};


#define	YYLAST		2943


static const short yytable[] =
{
      46,    49,    51,    87,    52,    81,    81,    86,   178,    64,
      66,   157,    68,    85,   383,   541,    89,   569,   182,   186,
      58,    97,   317,   352,   353,   341,   734,    76,   600,    99,
     100,   197,   101,   479,   693,   195,   404,   511,   104,   564,
     764,   145,   748,   329,   780,   800,   331,   745,   315,   298,
      26,    98,   187,    88,   188,   360,   627,   653,   668,   695,
     610,   152,   190,   170,   268,   318,   305,   694,   748,   748,
     438,    93,    88,    33,   439,   410,  -120,    28,   370,    29,
      30,   570,    60,   574,   393,   576,   579,   240,    83,    83,
      83,   461,   601,   502,   241,   506,    90,   527,   243,   244,
     512,   581,   565,   571,   583,   730,  -120,   623,   544,   753,
     259,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   542,   221,   222,   223,
     224,   225,   226,   227,   228,   230,   279,   232,   174,   342,
     735,   227,   236,   683,   198,   480,   233,   481,   688,   278,
     746,  -169,   332,  -401,   765,   299,   249,   251,   781,   801,
      33,   316,   300,   708,   709,   254,   432,   522,   361,   628,
     654,   669,   696,   191,   192,   269,   270,   306,   307,    35,
      36,    37,   411,    38,   237,   371,   160,   302,    94,   575,
      93,   577,   285,   657,   286,   394,   395,   580,    39,   308,
     356,    92,   462,   463,   503,   504,   507,   508,   528,   529,
     584,   412,   582,   289,   572,   573,   731,   338,   624,   625,
     754,   164,    40,    41,   470,   116,   117,    60,   713,   714,
     175,   775,   102,   311,   351,   234,   347,   276,    42,   705,
     706,   348,   261,   259,   416,   303,   433,   177,    44,   262,
     789,  -120,    28,    59,    29,    30,   645,   484,   321,   321,
     455,   173,   348,   464,  -357,   281,   458,   149,    95,   802,
     803,   334,    45,   183,   621,   366,    25,   239,   392,   382,
     467,  -120,   158,   350,  -120,    28,   471,    29,    30,   256,
      87,    63,    96,   159,    86,   747,   488,   640,   766,   767,
      85,   326,   149,   160,    35,    36,    37,   357,    38,   494,
     176,   177,  -120,    28,  -120,    29,    30,   277,   437,   142,
     646,   143,   384,    39,   417,    71,  -120,    28,    33,    29,
      30,   338,   658,   149,    26,   367,   593,   397,   622,   401,
     312,   403,  -120,   465,   384,   661,   663,    40,    41,   281,
     149,   149,   335,   176,   177,   336,  -120,   176,   177,   499,
     468,   157,   337,    42,   398,   509,    60,   399,   429,   176,
     177,    43,   536,    44,   539,   384,   489,    83,   420,   161,
     286,   176,   177,  -397,   162,   421,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,    45,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   437,   134,   135,   136,
     137,   138,   139,   363,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   519,   163,   127,   128,   543,  -106,   417,
     486,   102,   176,   177,   381,   510,    35,    36,    37,   163,
      38,   591,   537,   497,   540,   521,   515,    35,    36,    37,
     514,    38,   443,   164,   562,    39,   179,   793,    35,    36,
      37,   180,    38,   384,   664,   384,    39,   181,   592,   149,
     189,   713,   714,   804,   805,   806,   140,    39,   141,    40,
      41,   196,   142,   199,   143,  -294,  -397,   203,  -397,   231,
      40,    41,   597,   176,   177,    42,   629,   670,   386,   559,
     247,    40,    41,   433,   177,    44,    42,   544,   142,    64,
     143,   -23,   -23,   -23,    43,   -23,    44,    42,   116,   117,
     118,   119,   120,   121,   248,    43,   124,    44,   255,    45,
     -23,   253,   176,   177,   489,   260,   382,   588,   769,   267,
      45,   116,   117,   118,   119,   120,   121,   382,   593,   124,
     586,    45,   127,   128,   -23,   -23,   274,   666,   382,   713,
     714,   559,   149,    35,    36,    37,   261,    38,   615,   193,
     -23,   103,   598,   273,   681,   275,   630,   671,   -23,   149,
     -23,   372,    39,   278,    35,    36,    37,   288,    38,   682,
     633,   116,   117,   636,   149,   120,   121,   638,   639,   124,
     641,   707,   149,    39,   -23,   -23,    40,    41,   280,   291,
     -23,   294,   142,   293,   143,   344,   452,   304,   659,   660,
    -120,    28,    42,    29,    30,   -14,   770,    40,    41,   710,
      43,   768,    44,   673,   149,   142,   149,   143,   297,   -13,
     427,   428,   680,    42,   559,   325,   684,   719,   720,   559,
    -120,    43,   725,    44,   727,   349,    45,    51,   355,  -120,
      28,   587,    29,    30,   559,   559,   362,  -120,    28,   150,
      29,    30,   713,   714,    66,   365,   453,    45,    28,   150,
      29,    30,   756,   369,   758,   142,   733,   143,   373,  -120,
     376,   739,    28,   150,    29,    30,   744,  -120,   704,   151,
     533,   245,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   723,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   559,   134,   135,   136,   137,   138,   139,    -3,
     751,   752,    28,    59,    29,    30,   757,    28,   759,    29,
      30,   559,  -120,    28,    59,    29,    30,   762,   149,   375,
      71,  -120,    28,   377,    29,    30,   378,   741,   742,   385,
     559,   559,   322,   324,   379,   388,   559,   782,   391,   784,
     335,   409,  -120,   413,   415,   425,   426,   559,   559,   559,
      71,  -120,    28,  -227,    29,    30,   441,   442,   445,   451,
     448,   460,   140,   456,   141,   459,   420,   474,   142,   477,
     143,   475,   478,   345,   534,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   482,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   483,   134,   135,   136,   137,
     138,   139,   589,   485,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   736,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   755,   134,   135,   136,   137,   138,
     139,    71,  -120,    28,   487,    29,    30,   493,   495,   498,
      72,   501,   505,   517,   637,   523,   518,   525,   526,    73,
      74,    75,   777,   778,   531,   140,   532,   141,   783,   535,
     785,   142,  -120,   143,   567,   346,   538,  -120,    28,   150,
      29,    30,   561,   568,   585,   151,   599,   596,   604,   607,
     611,   612,   613,   797,   642,   799,   619,   643,   620,   650,
     644,   667,   626,   662,   140,   674,   141,  -120,   649,   652,
     142,   678,   143,   590,   617,   676,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   679,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   687,   134,   135,   136,
     137,   138,   139,   698,   689,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   690,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   691,   134,   135,   136,   137,
     138,   139,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,   697,   702,   717,   711,   712,   140,   724,   141,   726,
    -271,   728,   142,   729,   143,   618,   737,   738,   740,   760,
     761,   771,   763,   773,   776,   779,   786,   794,   787,   788,
     795,   796,   811,   798,   812,    22,   271,   807,   808,   809,
     313,   194,   520,   327,    23,   140,   444,   141,   343,   364,
     500,   142,   530,   143,   699,   146,   602,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   147,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   677,   134,   135,
     136,   137,   138,   139,   389,   492,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   473,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   701,   134,   135,   136,
     137,   138,   139,   440,    56,   380,   358,   246,   405,    57,
     722,   560,   647,   563,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   148,     0,   141,
       0,     0,     0,   142,     0,   143,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   140,     0,   141,     0,
       0,     0,   142,   390,   143,   449,     0,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,     0,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,     0,   134,   135,
     136,   137,   138,   139,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,     0,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,     0,   134,   135,   136,   137,   138,
     139,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   140,     0,   141,
       0,     0,     0,   142,   450,   143,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   140,     0,   141,     0,     0,   204,
     142,     0,   143,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,     0,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,     0,   134,   135,   136,   137,   138,   139,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,     0,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
       0,   134,   135,   136,   137,   138,   139,     0,   252,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   140,     0,   141,     0,     0,     0,   142,
       0,   143,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     140,   290,   141,     0,     0,     0,   142,     0,   143,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
       0,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,     0,
     134,   135,   136,   137,   138,   139,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,     0,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,     0,   134,   135,   136,
     137,   138,   139,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   140,
       0,   141,     0,     0,     0,   142,   292,   143,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   140,     0,   141,     0,
       0,     0,   142,   446,   143,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,     0,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,     0,   134,   135,   136,   137,
     138,   139,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,     0,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,     0,   134,   135,   136,   137,   138,   139,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   140,     0,   141,     0,     0,
       0,   142,   524,   143,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   140,   772,   141,     0,     0,     0,   142,     0,
     143,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,     0,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,     0,   134,   135,   136,   137,   138,   139,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,     0,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,    -2,     0,     0,   134,
     135,   136,   137,   138,   139,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   140,     0,   141,     0,     0,     0,   142,     0,   143,
       0,     0,     0,     0,     0,     0,     0,    71,     0,    28,
       0,    29,    30,     0,     0,     0,    72,     0,     0,     0,
       0,     0,     0,     0,     0,    73,    74,    75,   140,     0,
     141,     0,     0,     0,   142,     0,   143,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,     0,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   229,     0,     0,     0,   134,   135,
     136,   137,   138,   139,     0,   235,     0,    35,    36,    37,
       0,    38,     0,     0,   250,     0,     0,     0,    35,    36,
      37,     0,    38,     0,     0,   284,    39,    35,    36,    37,
       0,    38,     0,     0,     0,     0,     0,    39,    35,    36,
      37,     0,    38,     0,     0,     0,    39,     0,     0,     0,
      40,    41,     0,     0,     0,     0,     0,    39,     0,     0,
       0,    40,    41,     0,     0,     0,    42,   140,     0,   141,
      40,    41,     0,   142,    43,   143,    44,    42,   333,     0,
       0,    40,    41,     0,     0,    43,    42,    44,     0,   400,
       0,    35,    36,    37,    43,    38,    44,    42,     0,     0,
      45,     0,    35,    36,    37,    43,    38,    44,     0,   402,
      39,    45,     0,     0,     0,     0,     0,     0,     0,     0,
      45,    39,    35,    36,    37,     0,    38,     0,     0,     0,
       0,    45,     0,     0,    40,    41,     0,     0,     0,     0,
     496,    39,     0,     0,     0,    40,    41,     0,     0,     0,
      42,     0,     0,    35,    36,    37,     0,    38,    43,     0,
      44,    42,   605,     0,     0,    40,    41,     0,     0,    43,
       0,    44,    39,   608,     0,  -238,  -238,  -238,     0,  -238,
       0,    42,     0,     0,    45,     0,  -244,  -244,  -244,    43,
    -244,    44,     0,   614,  -238,    45,    40,    41,     0,     0,
       0,     0,     0,     0,     0,  -244,    35,    36,    37,     0,
      38,     0,    42,     0,     0,    45,     0,     0,  -238,  -238,
      43,     0,    44,     0,   672,    39,     0,     0,     0,  -244,
    -244,     0,     0,     0,  -238,     0,     0,    35,    36,    37,
       0,    38,  -238,     0,  -238,  -244,    45,     0,     0,    40,
      41,     0,     0,  -244,     0,  -244,    39,   700,     0,     0,
       0,     0,     0,     0,     0,    42,     0,     0,  -238,   721,
      35,    36,    37,    43,    38,    44,     0,     0,   732,  -244,
      40,    41,    35,    36,    37,     0,    38,     0,     0,    39,
       0,    35,    36,    37,     0,    38,    42,     0,     0,    45,
       0,    39,     0,     0,    43,     0,    44,     0,     0,     0,
      39,     0,     0,    40,    41,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    40,    41,     0,     0,    42,
      45,     0,     0,     0,    40,    41,     0,    43,     0,    44,
     743,    42,    35,    36,    37,     0,    38,     0,     0,    43,
      42,    44,     0,    35,    36,    37,     0,    38,    43,     0,
      44,    39,     0,    45,     0,     0,     0,     0,     0,     0,
       0,     0,    39,     0,     0,    45,     0,     0,     0,     0,
       0,     0,     0,     0,    45,    40,    41,     0,     0,    35,
      36,    37,     0,    38,     0,     0,    40,    41,    35,    36,
      37,    42,    38,     0,     0,     0,     0,     0,    39,    43,
       0,    44,    42,     0,     0,     0,     0,    39,     0,     0,
      43,     0,    44,     0,   547,   548,   549,   550,   551,   552,
     553,     0,    40,    41,   554,    45,     0,     0,     0,     0,
       0,    40,    41,   320,     0,     0,    45,     0,    42,    35,
      36,    37,     0,    38,     0,     0,    43,    42,    44,     0,
       0,     0,     0,     0,     0,    43,     0,    44,    39,    35,
      36,    37,     0,    38,     0,   547,   548,   549,   550,   551,
     552,   553,    45,     0,     0,   554,     0,     0,    39,     0,
     323,    45,    40,    41,     0,     0,   555,     0,   379,   556,
       0,     0,     0,     0,     0,     0,     0,     0,    42,     0,
       0,     0,    40,    41,     0,     0,    43,     0,    44,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    42,     0,
       0,     0,     0,     0,     0,     0,    43,     0,    44,     0,
       0,     0,    45,     0,     0,     0,     0,   555,     0,   379,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    45,     0,   278,     0,     0,     0,     0,   382,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,     0,     0,     0,     0,   134,
     135,   136,   137,   138,   139,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,     0,
       0,     0,     0,     0,   134,   135,   136,   137,   138,   139,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,     0,     0,     0,     0,     0,     0,   134,
     135,   136,   137,   138,   139,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   140,     0,
     141,     0,     0,     0,   142,     0,   143,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   141,   126,   127,   128,   142,
       0,   143,     0,     0,     0,   134,   135,   136,   137,   138,
     139,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     141,     0,   127,   128,   142,     0,   143,     0,     0,     0,
     134,   135,   136,   137,   138,   139,   116,   117,   118,   119,
     120,   121,   122,   123,   124,     0,     0,   127,   128,     0,
       0,     0,     0,     0,     0,   134,   135,   136,   137,   138,
     139,     0,     0,     0,     0,     0,   116,   117,   118,   119,
     120,   121,   122,   123,   124,     0,   141,   127,   128,     0,
     142,     0,   143,     0,     0,   134,   135,     0,     0,   138,
     139,     0,    35,    36,    37,     0,    38,     0,     0,     0,
       0,   141,     0,     0,     0,   142,     0,   143,     0,     0,
       0,    39,     0,     0,     0,     0,     0,     0,     0,     0,
      35,    36,    37,     0,    38,     0,     0,     0,     0,     0,
     142,     0,   143,     0,     0,    40,    41,     0,     0,    39,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    42,   165,   166,   167,   168,     0,   169,     0,    43,
     142,    44,   143,    40,    41,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    42,
       0,     0,     0,     0,     0,    45,     0,    43,     0,    44,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    45
};

static const short yycheck[] =
{
       7,     8,     9,    23,    10,    21,    22,    23,    72,    16,
      17,    57,    18,    23,   329,     1,     1,     1,    76,    83,
      14,    52,    72,   112,   113,     1,     1,    21,     1,    36,
      37,     1,    39,     1,    81,    95,   351,     1,    45,     1,
       1,    48,   715,     3,     1,     1,     1,     1,     1,     1,
      59,    82,     1,    81,     3,     1,     1,     1,     1,     1,
     578,    55,     1,    70,     1,   115,     1,   114,   741,   742,
     108,   113,    81,     6,   112,     1,    52,    53,     1,    55,
      56,    65,    15,     1,     1,     1,     1,   151,    21,    22,
      23,     1,    65,     1,   152,     1,    81,     1,   158,   159,
      64,     1,    64,     1,     1,     1,    82,     1,    81,     1,
     174,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   112,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   196,   144,    71,   115,
     115,   148,   149,   661,   114,   113,    14,   115,   666,   109,
     104,   115,   107,   115,   115,   107,   163,   164,   115,   115,
      93,   114,   114,   681,   682,   172,     1,   482,   114,   114,
     114,   114,   114,   112,   113,   112,   113,   112,   113,    14,
      15,    16,   108,    18,     1,   108,   112,   247,     1,   107,
     113,   107,   199,   632,   201,   112,   113,   112,    33,   259,
       1,    56,   112,   113,   112,   113,   112,   113,   112,   113,
     107,   359,   112,   220,   112,   113,   112,   281,   112,   113,
     112,   113,    57,    58,     1,    15,    16,   160,    48,    49,
       1,   749,   107,     1,   294,   103,   108,     1,    73,   678,
     679,   113,   107,   307,     1,   252,    81,    82,    83,   114,
     768,    52,    53,    54,    55,    56,     1,   108,   265,   266,
     408,     1,   113,     1,    81,   198,   414,   113,    81,   787,
     788,   278,   107,     1,     1,     1,     1,     1,   338,   114,
       1,    82,    81,   290,    52,    53,    63,    55,    56,     1,
     310,     1,   105,    81,   310,   115,     1,   108,   737,   738,
     310,     1,   113,   112,    14,    15,    16,   108,    18,   457,
      81,    82,    52,    53,    82,    55,    56,    81,   382,   109,
      65,   111,   329,    33,    81,    51,    52,    53,   261,    55,
      56,   395,   112,   113,    59,    61,    81,   344,    65,   346,
     108,   348,    82,    81,   351,   108,   108,    57,    58,   282,
     113,   113,   112,    81,    82,   115,    82,    81,    82,     1,
      81,   407,     1,    73,   110,     1,   299,   113,   375,    81,
      82,    81,     1,    83,     1,   382,    81,   310,    55,   113,
     387,    81,    82,     0,     1,    62,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,   107,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,   480,    34,    35,    36,
      37,    38,    39,     1,    15,    16,    17,    18,    19,    20,
      21,    22,    23,     1,   113,    26,    27,     1,   104,    81,
     447,   107,    81,    82,     1,    81,    14,    15,    16,   113,
      18,   115,    81,   460,    81,     1,   476,    14,    15,    16,
     476,    18,     1,   113,     1,    33,   114,   774,    14,    15,
      16,   114,    18,   480,   108,   482,    33,   114,     1,   113,
     112,    48,    49,   790,   791,   792,   103,    33,   105,    57,
      58,    81,   109,   109,   111,     1,   113,   108,   115,    81,
      57,    58,     1,    81,    82,    73,     1,     1,     1,   516,
      81,    57,    58,    81,    82,    83,    73,    81,   109,   526,
     111,    14,    15,    16,    81,    18,    83,    73,    15,    16,
      17,    18,    19,    20,   113,    81,    23,    83,   112,   107,
      33,   116,    81,    82,    81,   114,   114,   554,   115,   112,
     107,    15,    16,    17,    18,    19,    20,   114,    81,    23,
       1,   107,    26,    27,    57,    58,    81,   108,   114,    48,
      49,   578,   113,    14,    15,    16,   107,    18,   584,     1,
      73,     1,    81,   112,   108,   112,    81,    81,    81,   113,
      83,   314,    33,   109,    14,    15,    16,     1,    18,   108,
     606,    15,    16,   609,   113,    19,    20,   613,   614,    23,
     616,   112,   113,    33,   107,   108,    57,    58,     1,   110,
     113,    81,   109,   112,   111,   113,     1,   112,   634,   635,
      52,    53,    73,    55,    56,     0,   115,    57,    58,   108,
      81,   108,    83,   650,   113,   109,   113,   111,   114,     0,
     373,   374,   658,    73,   661,   112,   662,   689,   690,   666,
      82,    81,   694,    83,   696,   108,   107,   674,   114,    52,
      53,   112,    55,    56,   681,   682,   112,    52,    53,    54,
      55,    56,    48,    49,   691,   115,    61,   107,    53,    54,
      55,    56,   724,   108,   726,   109,   702,   111,   114,    82,
     112,   707,    53,    54,    55,    56,   713,    82,   677,    60,
       1,     1,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,   692,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,   749,    34,    35,    36,    37,    38,    39,     0,
     719,   720,    53,    54,    55,    56,   725,    53,   727,    55,
      56,   768,    52,    53,    54,    55,    56,   112,   113,   104,
      51,    52,    53,   112,    55,    56,   112,   711,   712,   112,
     787,   788,   265,   266,   114,   110,   793,   756,   112,   758,
     112,   108,    82,   114,   112,   108,   115,   804,   805,   806,
      51,    82,    53,     1,    55,    56,   110,   112,     1,   115,
     110,   114,   103,   115,   105,   112,    55,   115,   109,     1,
     111,   115,   115,     1,   115,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,   104,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,   112,    34,    35,    36,    37,
      38,    39,     1,   110,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,   704,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,   723,    34,    35,    36,    37,    38,
      39,    51,    52,    53,   110,    55,    56,   115,   115,   112,
      60,   112,   112,   115,    41,   112,   115,   112,   114,    69,
      70,    71,   751,   752,   115,   103,   115,   105,   757,   112,
     759,   109,    82,   111,   115,   113,   112,    52,    53,    54,
      55,    56,   112,   112,   107,    60,   112,   115,   107,   107,
     112,   112,   107,   782,    65,   784,   112,    81,   112,    66,
     112,    81,   115,   107,   103,    67,   105,    82,   115,   115,
     109,   112,   111,   112,     1,   115,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,   112,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,   114,    34,    35,    36,
      37,    38,    39,     1,   114,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,   114,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    66,    34,    35,    36,    37,
      38,    39,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   112,    68,    47,   114,   114,   103,   114,   105,   114,
       1,   112,   109,   112,   111,   112,   112,   112,   112,   112,
     112,   104,   112,   104,     1,   112,   115,   115,   108,   108,
     115,   115,     0,   115,     0,     2,   186,   115,   115,   115,
     261,    93,   480,   270,     3,   103,   395,   105,   282,   307,
     463,   109,   492,   111,   112,     1,   573,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,   654,    34,    35,
      36,    37,    38,    39,     1,   454,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,   423,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,   674,    34,    35,    36,
      37,    38,    39,   387,    12,   328,   299,   160,   353,    13,
     691,   526,   625,   529,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   103,    -1,   105,
      -1,    -1,    -1,   109,    -1,   111,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   103,    -1,   105,    -1,
      -1,    -1,   109,   110,   111,     1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      36,    37,    38,    39,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    -1,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    -1,    34,    35,    36,    37,    38,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   103,    -1,   105,
      -1,    -1,    -1,   109,   110,   111,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   103,    -1,   105,    -1,    -1,   108,
     109,    -1,   111,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    -1,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    -1,    34,    35,    36,    37,    38,    39,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      -1,    34,    35,    36,    37,    38,    39,    -1,    78,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   103,    -1,   105,    -1,    -1,    -1,   109,
      -1,   111,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     103,   104,   105,    -1,    -1,    -1,   109,    -1,   111,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    -1,
      34,    35,    36,    37,    38,    39,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    -1,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    35,    36,
      37,    38,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   103,
      -1,   105,    -1,    -1,    -1,   109,   110,   111,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   103,    -1,   105,    -1,
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
      -1,   109,   110,   111,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   103,   104,   105,    -1,    -1,    -1,   109,    -1,
     111,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    -1,    34,    35,    36,    37,    38,    39,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,     0,    -1,    -1,    34,
      35,    36,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   103,    -1,   105,    -1,    -1,    -1,   109,    -1,   111,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,    -1,    53,
      -1,    55,    56,    -1,    -1,    -1,    60,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    69,    70,    71,   103,    -1,
     105,    -1,    -1,    -1,   109,    -1,   111,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,     1,    -1,    -1,    -1,    34,    35,
      36,    37,    38,    39,    -1,     1,    -1,    14,    15,    16,
      -1,    18,    -1,    -1,     1,    -1,    -1,    -1,    14,    15,
      16,    -1,    18,    -1,    -1,     1,    33,    14,    15,    16,
      -1,    18,    -1,    -1,    -1,    -1,    -1,    33,    14,    15,
      16,    -1,    18,    -1,    -1,    -1,    33,    -1,    -1,    -1,
      57,    58,    -1,    -1,    -1,    -1,    -1,    33,    -1,    -1,
      -1,    57,    58,    -1,    -1,    -1,    73,   103,    -1,   105,
      57,    58,    -1,   109,    81,   111,    83,    73,     1,    -1,
      -1,    57,    58,    -1,    -1,    81,    73,    83,    -1,     1,
      -1,    14,    15,    16,    81,    18,    83,    73,    -1,    -1,
     107,    -1,    14,    15,    16,    81,    18,    83,    -1,     1,
      33,   107,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     107,    33,    14,    15,    16,    -1,    18,    -1,    -1,    -1,
      -1,   107,    -1,    -1,    57,    58,    -1,    -1,    -1,    -1,
       1,    33,    -1,    -1,    -1,    57,    58,    -1,    -1,    -1,
      73,    -1,    -1,    14,    15,    16,    -1,    18,    81,    -1,
      83,    73,     1,    -1,    -1,    57,    58,    -1,    -1,    81,
      -1,    83,    33,     1,    -1,    14,    15,    16,    -1,    18,
      -1,    73,    -1,    -1,   107,    -1,    14,    15,    16,    81,
      18,    83,    -1,     1,    33,   107,    57,    58,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    14,    15,    16,    -1,
      18,    -1,    73,    -1,    -1,   107,    -1,    -1,    57,    58,
      81,    -1,    83,    -1,     1,    33,    -1,    -1,    -1,    57,
      58,    -1,    -1,    -1,    73,    -1,    -1,    14,    15,    16,
      -1,    18,    81,    -1,    83,    73,   107,    -1,    -1,    57,
      58,    -1,    -1,    81,    -1,    83,    33,     1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    73,    -1,    -1,   107,     1,
      14,    15,    16,    81,    18,    83,    -1,    -1,     1,   107,
      57,    58,    14,    15,    16,    -1,    18,    -1,    -1,    33,
      -1,    14,    15,    16,    -1,    18,    73,    -1,    -1,   107,
      -1,    33,    -1,    -1,    81,    -1,    83,    -1,    -1,    -1,
      33,    -1,    -1,    57,    58,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    57,    58,    -1,    -1,    73,
     107,    -1,    -1,    -1,    57,    58,    -1,    81,    -1,    83,
       1,    73,    14,    15,    16,    -1,    18,    -1,    -1,    81,
      73,    83,    -1,    14,    15,    16,    -1,    18,    81,    -1,
      83,    33,    -1,   107,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    -1,    -1,   107,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   107,    57,    58,    -1,    -1,    14,
      15,    16,    -1,    18,    -1,    -1,    57,    58,    14,    15,
      16,    73,    18,    -1,    -1,    -1,    -1,    -1,    33,    81,
      -1,    83,    73,    -1,    -1,    -1,    -1,    33,    -1,    -1,
      81,    -1,    83,    -1,    40,    41,    42,    43,    44,    45,
      46,    -1,    57,    58,    50,   107,    -1,    -1,    -1,    -1,
      -1,    57,    58,   115,    -1,    -1,   107,    -1,    73,    14,
      15,    16,    -1,    18,    -1,    -1,    81,    73,    83,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    -1,    83,    33,    14,
      15,    16,    -1,    18,    -1,    40,    41,    42,    43,    44,
      45,    46,   107,    -1,    -1,    50,    -1,    -1,    33,    -1,
     115,   107,    57,    58,    -1,    -1,   112,    -1,   114,   115,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    -1,
      -1,    -1,    57,    58,    -1,    -1,    81,    -1,    83,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,    83,    -1,
      -1,    -1,   107,    -1,    -1,    -1,    -1,   112,    -1,   114,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   107,    -1,   109,    -1,    -1,    -1,    -1,   114,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    -1,    -1,    -1,    -1,    34,
      35,    36,    37,    38,    39,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    -1,
      -1,    -1,    -1,    -1,    34,    35,    36,    37,    38,    39,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    -1,    -1,    -1,    -1,    -1,    -1,    34,
      35,    36,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   103,    -1,
     105,    -1,    -1,    -1,   109,    -1,   111,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    15,    16,    17,    18,
      19,    20,    21,    22,    23,   105,    25,    26,    27,   109,
      -1,   111,    -1,    -1,    -1,    34,    35,    36,    37,    38,
      39,    15,    16,    17,    18,    19,    20,    21,    22,    23,
     105,    -1,    26,    27,   109,    -1,   111,    -1,    -1,    -1,
      34,    35,    36,    37,    38,    39,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    -1,    -1,    26,    27,    -1,
      -1,    -1,    -1,    -1,    -1,    34,    35,    36,    37,    38,
      39,    -1,    -1,    -1,    -1,    -1,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    -1,   105,    26,    27,    -1,
     109,    -1,   111,    -1,    -1,    34,    35,    -1,    -1,    38,
      39,    -1,    14,    15,    16,    -1,    18,    -1,    -1,    -1,
      -1,   105,    -1,    -1,    -1,   109,    -1,   111,    -1,    -1,
      -1,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      14,    15,    16,    -1,    18,    -1,    -1,    -1,    -1,    -1,
     109,    -1,   111,    -1,    -1,    57,    58,    -1,    -1,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    73,    74,    75,    76,    77,    -1,    79,    -1,    81,
     109,    83,   111,    57,    58,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,
      -1,    -1,    -1,    -1,    -1,   107,    -1,    81,    -1,    83,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   107
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/pack/bison-1.35/share/bison/bison.simple"

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

#line 315 "/pack/bison-1.35/share/bison/bison.simple"


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
#line 274 "parser.yy"
{ CALL(yylsp[0], yylsp[0], done()); }
    break;
case 2:
#line 275 "parser.yy"
{ }
    break;
case 3:
#line 276 "parser.yy"
{ }
    break;
case 4:
#line 277 "parser.yy"
{ }
    break;
case 5:
#line 278 "parser.yy"
{ }
    break;
case 6:
#line 279 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SYSTEM));
	}
    break;
case 7:
#line 282 "parser.yy"
{ g_parameter_count = yyvsp[0].number; }
    break;
case 8:
#line 283 "parser.yy"
{ }
    break;
case 9:
#line 284 "parser.yy"
{ CALL(yylsp[0], yylsp[0], procGuard()); }
    break;
case 10:
#line 285 "parser.yy"
{ }
    break;
case 11:
#line 286 "parser.yy"
{ CALL(yylsp[0], yylsp[0], procUpdate()); }
    break;
case 12:
#line 287 "parser.yy"
{ CALL(yylsp[0], yylsp[0], done()); }
    break;
case 13:
#line 288 "parser.yy"
{ }
    break;
case 14:
#line 289 "parser.yy"
{ }
    break;
case 15:
#line 290 "parser.yy"
{ }
    break;
case 16:
#line 291 "parser.yy"
{ g_parameter_count = yyvsp[0].number; }
    break;
case 17:
#line 292 "parser.yy"
{ }
    break;
case 18:
#line 293 "parser.yy"
{ CALL(yylsp[0], yylsp[0], procGuard()); }
    break;
case 19:
#line 294 "parser.yy"
{ CALL(yylsp[0], yylsp[0], procUpdate()); }
    break;
case 20:
#line 295 "parser.yy"
{}
    break;
case 23:
#line 304 "parser.yy"
{
          CALL(yylsp[-3], yylsp[-1], instantiationBegin(yyvsp[-3].string, yyvsp[-1].string));
	}
    break;
case 24:
#line 306 "parser.yy"
{
	  CALL(yylsp[-7], yylsp[0], instantiationEnd(yyvsp[-7].string, yyvsp[-5].string, yyvsp[-2].number));
	}
    break;
case 25:
#line 309 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_ARGLIST));
	}
    break;
case 26:
#line 312 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));
	}
    break;
case 27:
#line 315 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_LPAREN));
	}
    break;
case 28:
#line 318 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_ASSIGN));
	}
    break;
case 30:
#line 325 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;
case 31:
#line 328 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_PROCID));
	}
    break;
case 32:
#line 334 "parser.yy"
{ CALL(yylsp[0], yylsp[0], process(yyvsp[0].string)); }
    break;
case 33:
#line 335 "parser.yy"
{ CALL(yylsp[0], yylsp[0], process(yyvsp[0].string)); }
    break;
case 34:
#line 336 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_PROCID_));
	}
    break;
case 50:
#line 367 "parser.yy"
{
	  CALL(yylsp[-1], yylsp[-1], beforeUpdate());
        }
    break;
case 52:
#line 373 "parser.yy"
{
	  CALL(yylsp[-1], yylsp[-1], afterUpdate());
        }
    break;
case 53:
#line 378 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], declFuncBegin(yyvsp[-1].string, yyvsp[0].number));
	}
    break;
case 54:
#line 381 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[-1], declFuncEnd());
	}
    break;
case 55:
#line 387 "parser.yy"
{ yyval.number = 0; }
    break;
case 56:
#line 388 "parser.yy"
{ yyval.number = yyvsp[-1].number; }
    break;
case 57:
#line 389 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));
	  yyval.number = yyvsp[-2].number; 
	}
    break;
case 58:
#line 393 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));
	  yyval.number = yyvsp[-1].number; 
	}
    break;
case 59:
#line 397 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_PARAMETERS));
	  yyval.number = 0; 
	}
    break;
case 60:
#line 401 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));
	  yyval.number = 0; 
	}
    break;
case 61:
#line 413 "parser.yy"
{ yyval.number = 1; }
    break;
case 62:
#line 414 "parser.yy"
{ yyval.number = yyvsp[-2].number+1; }
    break;
case 63:
#line 415 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_PARAMETERS_));
	  yyval.number = yyvsp[-2].number;
	}
    break;
case 64:
#line 422 "parser.yy"
{
          CALL(yylsp[-3], yylsp[0], declParameter(yyvsp[-1].string, true, yyvsp[0].number));
          CALL(yylsp[-3], yylsp[0], declParameterEnd());
	}
    break;
case 65:
#line 426 "parser.yy"
{
          CALL(yylsp[-2], yylsp[0], declParameter(yyvsp[-1].string, false, yyvsp[0].number));
          CALL(yylsp[-2], yylsp[0], declParameterEnd());
	}
    break;
case 66:
#line 430 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_PARAMID));
	}
    break;
case 67:
#line 436 "parser.yy"
{ 
          CALL(yylsp[-2], yylsp[0], declVarEnd());
	}
    break;
case 68:
#line 439 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
          CALL(yylsp[-3], yylsp[0], declVarEnd());
	}
    break;
case 69:
#line 443 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_VARID));
	  CALL(yylsp[-2], yylsp[0], declVarEnd());
	}
    break;
case 72:
#line 452 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_VARID_));
	}
    break;
case 73:
#line 458 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], declVar(yyvsp[-2].string, yyvsp[-1].number, yyvsp[0].flag));
	}
    break;
case 74:
#line 464 "parser.yy"
{ yyval.flag = false; }
    break;
case 75:
#line 465 "parser.yy"
{ yyval.flag = true; }
    break;
case 76:
#line 466 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_INITIAL));
	  yyval.flag = false; 
	}
    break;
case 78:
#line 474 "parser.yy"
{	
	  CALL(yylsp[-2], yylsp[0], declInitialiserList(yyvsp[-1].number));
	}
    break;
case 79:
#line 477 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  CALL(yylsp[-3], yylsp[0], declInitialiserList(yyvsp[-2].number));
	}
    break;
case 80:
#line 481 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_INITIAL));
	  CALL(yylsp[-2], yylsp[0], declInitialiserList(0));
	}
    break;
case 81:
#line 488 "parser.yy"
{ yyval.number = 1; }
    break;
case 82:
#line 489 "parser.yy"
{ yyval.number = yyvsp[-2].number+1; }
    break;
case 83:
#line 490 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_INITIAL_));
	  yyval.number = yyvsp[-2].number+1; 
	}
    break;
case 84:
#line 497 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], declFieldInit(yyvsp[-2].string));
	}
    break;
case 85:
#line 500 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_INITIAL));
	}
    break;
case 86:
#line 503 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], declFieldInit(NULL));
	}
    break;
case 87:
#line 509 "parser.yy"
{ yyval.number=0; }
    break;
case 88:
#line 510 "parser.yy"
{ yyval.number=yyvsp[-3].number+1; }
    break;
case 89:
#line 511 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RSQBRACE));
	  yyval.number=yyvsp[-4].number+1; 
	}
    break;
case 90:
#line 515 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RSQBRACE));
	  yyval.number=yyvsp[-3].number+1; 
	}
    break;
case 91:
#line 519 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_CONST_EXP));
	  yyval.number=yyvsp[-3].number+1; 
	}
    break;
case 92:
#line 523 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_CONST_EXP));
	  yyval.number=yyvsp[-2].number+1; 
	}
    break;
case 93:
#line 530 "parser.yy"
{
	  CALL(yylsp[-3], yylsp[0], declTypeDefEnd());
	}
    break;
case 94:
#line 533 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-4], yylsp[0], declTypeDefEnd());
	}
    break;
case 95:
#line 537 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_TYPEID));
	  CALL(yylsp[-3], yylsp[0], declTypeDefEnd());  
	}
    break;
case 96:
#line 541 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_TYPE_DEF));
	  CALL(yylsp[-2], yylsp[0], declTypeDefEnd());  
	}
    break;
case 97:
#line 553 "parser.yy"
{ yyval.number = 1; }
    break;
case 98:
#line 554 "parser.yy"
{ yyval.number = yyvsp[-2].number+1; }
    break;
case 99:
#line 555 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_TYPEID_));
	  yyval.number = yyvsp[-2].number+1; 
	}
    break;
case 100:
#line 562 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], declTypeDef(yyvsp[-1].string, yyvsp[0].number));
	}
    break;
case 101:
#line 568 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], declType(yyvsp[-2].number, yyvsp[-1].string, yyvsp[0].flag));
	}
    break;
case 102:
#line 571 "parser.yy"
{ 
	  CALL(yylsp[-4], yylsp[0], declStruct(yyvsp[-4].number, yyvsp[-1].number));
	}
    break;
case 103:
#line 574 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBER));
	  CALL(yylsp[-4], yylsp[0], declStruct(yyvsp[-4].number, 0));
	}
    break;
case 104:
#line 578 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  CALL(yylsp[-3], yylsp[0], declStruct(yyvsp[-3].number, 0));
	}
    break;
case 105:
#line 582 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	}
    break;
case 106:
#line 588 "parser.yy"
{ strncpy(yyval.string, yyvsp[0].string, MAXLEN); }
    break;
case 107:
#line 589 "parser.yy"
{ strncpy(yyval.string, yyvsp[0].string, MAXLEN); }
    break;
case 108:
#line 593 "parser.yy"
{ yyval.number=yyvsp[0].number; }
    break;
case 109:
#line 594 "parser.yy"
{ yyval.number=yyvsp[-1].number+yyvsp[0].number; }
    break;
case 110:
#line 595 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBER));
	  yyval.number=yyvsp[-1].number; 
	}
    break;
case 111:
#line 602 "parser.yy"
{
	  yyval.number = yyvsp[-1].number; 
	  CALL(yylsp[-2], yylsp[0], declFieldEnd());
	}
    break;
case 112:
#line 606 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));	  
	  yyval.number = yyvsp[-2].number; 
	  CALL(yylsp[-3], yylsp[0], declFieldEnd());
	}
    break;
case 113:
#line 611 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBERID));	  
	}
    break;
case 114:
#line 614 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBERID));	  
	}
    break;
case 115:
#line 617 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBERTYPE));	  
	}
    break;
case 116:
#line 623 "parser.yy"
{ yyval.number=1; }
    break;
case 117:
#line 624 "parser.yy"
{ yyval.number=yyvsp[-2].number+1; }
    break;
case 118:
#line 625 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_MEMBERID_));
	  yyval.number=yyvsp[-2].number+1; 
	}
    break;
case 119:
#line 632 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], declField(yyvsp[-1].string, yyvsp[0].number));
	}
    break;
case 120:
#line 638 "parser.yy"
{ yyval.number = ParserBuilder::PREFIX_NONE; }
    break;
case 121:
#line 639 "parser.yy"
{ yyval.number = ParserBuilder::PREFIX_URGENT; }
    break;
case 122:
#line 640 "parser.yy"
{ yyval.number = ParserBuilder::PREFIX_BROADCAST; }
    break;
case 123:
#line 641 "parser.yy"
{ yyval.number = ParserBuilder::PREFIX_URGENT_BROADCAST; }
    break;
case 124:
#line 642 "parser.yy"
{ yyval.number = ParserBuilder::PREFIX_CONST; }
    break;
case 125:
#line 646 "parser.yy"
{ yyval.flag = false; }
    break;
case 126:
#line 647 "parser.yy"
{ yyval.flag = true; }
    break;
case 127:
#line 648 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RSQBRACE));
	  yyval.flag = true; 
	}
    break;
case 128:
#line 652 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RSQBRACE));
	  yyval.flag = true; 
	}
    break;
case 129:
#line 656 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_CONST_EXP));
	  yyval.flag = true;
	  CALL(yylsp[-4], yylsp[0], exprTrue());
	}
    break;
case 130:
#line 661 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_CONST_EXP));
	  yyval.flag = true;
	  CALL(yylsp[-4], yylsp[0], exprTrue());
	}
    break;
case 131:
#line 666 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_CONST_EXP));
	  yyval.flag = true;
	  CALL(yylsp[-2], yylsp[0], exprTrue());
	}
    break;
case 132:
#line 671 "parser.yy"
{
	    REPORT_ERROR(last_loc, TypeException(PE_CONST_EXP));
	    yyval.flag = true;
	    CALL(yylsp[-2], yylsp[-1], exprTrue());
	  }
    break;
case 133:
#line 676 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_COMMA)); 
	  yyclearin; yyerrok;
	}
    break;
case 134:
#line 680 "parser.yy"
{
	    yyval.flag = true;
	  }
    break;
case 135:
#line 683 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_COMMA)); 
	  yyclearin; yyerrok;
	  yyval.flag = true;
	  CALL(yylsp[-3], yylsp[0], exprTrue());
	}
    break;
case 136:
#line 689 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_COMMA)); 
	  yyclearin; yyerrok;
	  yyval.flag = true;
	  CALL(yylsp[-2], yylsp[0], exprTrue());
	}
    break;
case 137:
#line 695 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_CONST_EXP)); 
	  yyclearin; yyerrok;
	  yyval.flag = true;
	  CALL(yylsp[-1], yylsp[0], exprTrue());
	}
    break;
case 138:
#line 708 "parser.yy"
{ 
	  CALL(yylsp[-3], yylsp[0], procBegin(yyvsp[-2].string, yyvsp[-1].number));
	}
    break;
case 139:
#line 711 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], procEnd());
	}
    break;
case 140:
#line 714 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	}
    break;
case 141:
#line 717 "parser.yy"
{
	  utap_error(TypeException(PE_LPAREN), 
		     yylsp[0].first_line, yylsp[0].first_column, 
		     yylsp[0].last_line, yylsp[0].last_column);
	  CALL(yylsp[-2], yylsp[0], procBegin(yyvsp[-1].string, 0));
	}
    break;
case 142:
#line 722 "parser.yy"
{
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;
case 143:
#line 725 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_PROCID));	  
	}
    break;
case 150:
#line 747 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;
case 151:
#line 750 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;
case 152:
#line 753 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_STATE_DECL));
	}
    break;
case 153:
#line 756 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_STATE_DECL));
	}
    break;
case 154:
#line 759 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_STATE));
	}
    break;
case 157:
#line 767 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_STATE_DECL_));
	}
    break;
case 158:
#line 773 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], procState(yyvsp[0].string, false));
	}
    break;
case 159:
#line 776 "parser.yy"
{ 
	  CALL(yylsp[-3], yylsp[0], procState(yyvsp[-3].string, true));
	}
    break;
case 160:
#line 779 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	  CALL(yylsp[-4], yylsp[0], procState(yyvsp[-4].string, true));
	}
    break;
case 161:
#line 783 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	  CALL(yylsp[-3], yylsp[0], procState(yyvsp[-3].string, true));
	}
    break;
case 162:
#line 787 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_INV));
	  CALL(yylsp[-3], yylsp[0], procState(yyvsp[-3].string, false));
	}
    break;
case 163:
#line 791 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_INV));
	  CALL(yylsp[-2], yylsp[0], procState(yyvsp[-2].string, false));
	}
    break;
case 164:
#line 798 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], procStateInit(yyvsp[-1].string));
	}
    break;
case 165:
#line 801 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-3], yylsp[0], procStateInit(yyvsp[-2].string));
	}
    break;
case 166:
#line 805 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-2], yylsp[0], procStateInit(yyvsp[-1].string));
	}
    break;
case 167:
#line 809 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;
case 168:
#line 812 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_INIT));
	}
    break;
case 171:
#line 820 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;
case 172:
#line 823 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;
case 173:
#line 826 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS_DECL));
	}
    break;
case 174:
#line 829 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS));
	}
    break;
case 177:
#line 837 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS_DECL_));
	}
    break;
case 178:
#line 843 "parser.yy"
{ 
	  strcpy(rootTransId, yyvsp[-7].string); 
	  CALL(yylsp[-7], yylsp[0], procTransition(yyvsp[-7].string, yyvsp[-5].string));
	}
    break;
case 179:
#line 847 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  strcpy(rootTransId, yyvsp[-8].string); 
	  CALL(yylsp[-8], yylsp[0], procTransition(yyvsp[-8].string, yyvsp[-6].string));
	}
    break;
case 180:
#line 852 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	}
    break;
case 181:
#line 855 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;
case 182:
#line 858 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_ARROW));
	}
    break;
case 183:
#line 864 "parser.yy"
{ 
	  CALL(yylsp[-6], yylsp[0], procTransition(rootTransId, yyvsp[-5].string));
	}
    break;
case 184:
#line 867 "parser.yy"
{ 
	  REPORT_ERROR(yylloc, TypeException(PE_RBRACE));
	  CALL(yylsp[-7], yylsp[0], procTransition(rootTransId, yyvsp[-6].string));
	}
    break;
case 185:
#line 871 "parser.yy"
{ 
	  REPORT_ERROR(yylloc, TypeException(PE_LBRACE));
	}
    break;
case 186:
#line 874 "parser.yy"
{ 
	  REPORT_ERROR(yylloc, TypeException(PE_STATEID));
	}
    break;
case 189:
#line 883 "parser.yy"
{
	  CALL(yyloc, yyloc, procGuard());
        }
    break;
case 190:
#line 886 "parser.yy"
{
	  REPORT_ERROR(yylloc, TypeException(PE_SEMICOLON));
	  CALL(yyloc, yyloc, procGuard());
	}
    break;
case 191:
#line 890 "parser.yy"
{
	  REPORT_ERROR(yylloc, TypeException(PE_GUARD_EXP));
	}
    break;
case 194:
#line 898 "parser.yy"
{
	  REPORT_ERROR(yylloc, TypeException(PE_SEMICOLON));
	}
    break;
case 195:
#line 901 "parser.yy"
{
	  REPORT_ERROR(yylloc, TypeException(PE_SEMICOLON));
	}
    break;
case 196:
#line 904 "parser.yy"
{
	  REPORT_ERROR(yylloc, TypeException(PE_SYNC_EXP));
	}
    break;
case 197:
#line 910 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], procSync(SYNC_BANG));
	}
    break;
case 198:
#line 913 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_BANG));
	  CALL(yylsp[-2], yylsp[-1], procSync(SYNC_QUE));
	}
    break;
case 199:
#line 917 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], procSync(SYNC_QUE));
	}
    break;
case 200:
#line 920 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_QUE));
	  CALL(yylsp[-2], yylsp[-1], procSync(SYNC_QUE));
	}
    break;
case 201:
#line 924 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_BANGQUE));
	  CALL(yylsp[-1], yylsp[0], procSync(SYNC_QUE));
	}
    break;
case 203:
#line 932 "parser.yy"
{
	  CALL(yyloc, yyloc, procUpdate());	  
	}
    break;
case 204:
#line 935 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_ASSIGN_EXP));
	}
    break;
case 210:
#line 949 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;
case 211:
#line 952 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;
case 212:
#line 955 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;
case 213:
#line 958 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;
case 214:
#line 964 "parser.yy"
{}
    break;
case 215:
#line 965 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;
case 216:
#line 968 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;
case 217:
#line 971 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;
case 218:
#line 974 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	}
    break;
case 219:
#line 980 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], procStateCommit(yyvsp[0].string));
	}
    break;
case 220:
#line 983 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], procStateCommit(yyvsp[0].string));
	}
    break;
case 221:
#line 986 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID_));
	}
    break;
case 222:
#line 992 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], procStateUrgent(yyvsp[0].string));
	}
    break;
case 223:
#line 995 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], procStateUrgent(yyvsp[0].string));
	}
    break;
case 224:
#line 998 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID_));
	}
    break;
case 225:
#line 1009 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], blockBegin());
	}
    break;
case 226:
#line 1012 "parser.yy"
{ 
	  CALL(yylsp[-3], yylsp[-1], blockEnd());
	}
    break;
case 227:
#line 1015 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], blockBegin());
	}
    break;
case 228:
#line 1018 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_DECL_STAT));
	  CALL(yylsp[-2], yylsp[-1], blockEnd());
	}
    break;
case 235:
#line 1037 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], emptyStatement());
	}
    break;
case 236:
#line 1040 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], exprStatement());
	}
    break;
case 237:
#line 1043 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-2], yylsp[0], exprStatement());
	}
    break;
case 238:
#line 1047 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], forBegin());
	}
    break;
case 239:
#line 1050 "parser.yy"
{ 
	    CALL(yylsp[-7], yylsp[-1], forEnd());
	  }
    break;
case 240:
#line 1053 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], forBegin());
	}
    break;
case 241:
#line 1058 "parser.yy"
{ 
	    CALL(yylsp[-7], yylsp[-10], forEnd());
	  }
    break;
case 242:
#line 1061 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_LPAREN));
	  CALL(yylsp[-2], yylsp[0], forBegin());
	}
    break;
case 243:
#line 1066 "parser.yy"
{ 
	    CALL(yylsp[-7], yylsp[-10], forEnd());
	  }
    break;
case 244:
#line 1069 "parser.yy"
{
	    CALL(yylsp[-1], yylsp[0], whileBegin());
	}
    break;
case 245:
#line 1072 "parser.yy"
{ 
	    CALL(yylsp[-3], yylsp[-2], whileEnd());
	  }
    break;
case 246:
#line 1075 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));
	  CALL(yylsp[-2], yylsp[0], whileBegin());
	}
    break;
case 247:
#line 1079 "parser.yy"
{ 
	    CALL(yylsp[-3], yylsp[-1], whileEnd());
	  }
    break;
case 248:
#line 1082 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], whileBegin());
	}
    break;
case 249:
#line 1086 "parser.yy"
{ 
	    CALL(yylsp[-6], yylsp[-4], whileEnd());
	  }
    break;
case 250:
#line 1089 "parser.yy"
{ 
	    CALL(yylsp[0], yylsp[0], doWhileBegin());
	}
    break;
case 251:
#line 1092 "parser.yy"
{ 
	    CALL(yylsp[-6], yylsp[-1], doWhileEnd());
	  }
    break;
case 252:
#line 1095 "parser.yy"
{ 
	    CALL(yylsp[-1], yylsp[0], ifBegin());
	}
    break;
case 254:
#line 1099 "parser.yy"
{ 
	    CALL(yylsp[-1], yylsp[0], breakStatement());
	  }
    break;
case 255:
#line 1102 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-2], yylsp[0], breakStatement());
	}
    break;
case 256:
#line 1106 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], continueStatement());
	}
    break;
case 257:
#line 1109 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-2], yylsp[0], continueStatement());
	}
    break;
case 258:
#line 1113 "parser.yy"
{ 
	    CALL(yylsp[-3], yylsp[0], switchBegin());
	}
    break;
case 259:
#line 1116 "parser.yy"
{ 
	       CALL(yylsp[-3], yylsp[-1], switchEnd());
	   }
    break;
case 260:
#line 1119 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));
	  CALL(yylsp[-4], yylsp[0], switchBegin());
	}
    break;
case 261:
#line 1123 "parser.yy"
{ 
	    CALL(yylsp[-3], yylsp[-1], switchEnd());
	  }
    break;
case 262:
#line 1126 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-4], yylsp[0], switchBegin());
	}
    break;
case 263:
#line 1130 "parser.yy"
{ 
	    CALL(yylsp[-3], yylsp[-1], switchEnd());
	  }
    break;
case 264:
#line 1133 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], returnStatement(true));
	}
    break;
case 265:
#line 1136 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-2], yylsp[0], returnStatement(true));
	}
    break;
case 266:
#line 1140 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], returnStatement(false));
	}
    break;
case 267:
#line 1143 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR_SEMI));
	  CALL(yylsp[-1], yylsp[0], returnStatement(false));
	}
    break;
case 268:
#line 1150 "parser.yy"
{ 
	  CALL(yyloc, yyloc, ifEnd(false));
	}
    break;
case 269:
#line 1153 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], ifElse());
	}
    break;
case 270:
#line 1156 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[-1], ifEnd(true));
	  }
    break;
case 271:
#line 1159 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], ifElse());
	}
    break;
case 272:
#line 1162 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yylsp[-1], yylsp[-1], ifEnd(true));
	  }
    break;
case 275:
#line 1174 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], caseBegin());
	}
    break;
case 276:
#line 1177 "parser.yy"
{ 
	    CALL(yylsp[-1], yylsp[-1], caseEnd());
	  }
    break;
case 277:
#line 1180 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], caseBegin());
	}
    break;
case 278:
#line 1183 "parser.yy"
{
	    REPORT_ERROR(last_loc, TypeException(PE_EXPR)); 
	    CALL(yylsp[-1], yylsp[-1], caseEnd());
	  }
    break;
case 279:
#line 1187 "parser.yy"
{ 
	    CALL(yylsp[-1], yylsp[0], defaultBegin());
	}
    break;
case 280:
#line 1190 "parser.yy"
{ 
	    CALL(yylsp[-1], yylsp[-1], defaultEnd());
	  }
    break;
case 281:
#line 1193 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_COLON)); 
	  CALL(yylsp[-2], yylsp[0], defaultBegin());
	}
    break;
case 282:
#line 1197 "parser.yy"
{ 
	    CALL(yylsp[-1], yylsp[-1], defaultEnd());
	  }
    break;
case 286:
#line 1209 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprComma());
	}
    break;
case 287:
#line 1212 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR_));
	}
    break;
case 288:
#line 1218 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], exprFalse());
	}
    break;
case 289:
#line 1221 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], exprTrue());
	}
    break;
case 290:
#line 1224 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], exprNat(yyvsp[0].number));
	}
    break;
case 291:
#line 1227 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], exprId(yyvsp[0].string));
	}
    break;
case 292:
#line 1230 "parser.yy"
{
	    CALL(yylsp[-1], yylsp[0], exprCallBegin(yyvsp[-1].string));	    
	  }
    break;
case 293:
#line 1232 "parser.yy"
{ 
	    CALL(yylsp[-4], yylsp[0], exprCallEnd(yyvsp[-1].number));
	}
    break;
case 294:
#line 1235 "parser.yy"
{
	    CALL(yylsp[-1], yylsp[0], exprCallBegin(yyvsp[-1].string));
	  }
    break;
case 295:
#line 1237 "parser.yy"
{   
	    REPORT_ERROR(last_loc, TypeException(PE_ARGLIST));
	    CALL(yylsp[-4], yylsp[0], exprCallEnd(0));
	}
    break;
case 296:
#line 1241 "parser.yy"
{ 
	  CALL(yylsp[-3], yylsp[0], exprArray());
	}
    break;
case 297:
#line 1244 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-3], yylsp[0], exprFalse());
	}
    break;
case 299:
#line 1249 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_EXPR));
	  CALL(yylsp[-2], yylsp[0], exprFalse());
	}
    break;
case 300:
#line 1253 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], exprPostIncrement());
	}
    break;
case 301:
#line 1256 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], exprPreIncrement());
	}
    break;
case 302:
#line 1259 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], exprPostDecrement());
	}
    break;
case 303:
#line 1262 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], exprPreDecrement());
	}
    break;
case 304:
#line 1265 "parser.yy"
{ 
	  CALL(yylsp[-1], yylsp[0], exprUnary(yyvsp[-1].kind));
	}
    break;
case 305:
#line 1268 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(LT));
	}
    break;
case 306:
#line 1271 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(LE));
	}
    break;
case 307:
#line 1274 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(EQ));
	}
    break;
case 308:
#line 1277 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(NEQ));
	}
    break;
case 309:
#line 1280 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(GT));
	}
    break;
case 310:
#line 1283 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(GE));
	}
    break;
case 311:
#line 1286 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(PLUS));
	}
    break;
case 312:
#line 1289 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(MINUS));
	}
    break;
case 313:
#line 1292 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(MULT));
	}
    break;
case 314:
#line 1295 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(DIV));
	}
    break;
case 315:
#line 1298 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(MOD));
	}
    break;
case 316:
#line 1301 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_AND));
	}
    break;
case 317:
#line 1304 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_OR));
	}
    break;
case 318:
#line 1307 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_XOR));
	}
    break;
case 319:
#line 1310 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_LSHIFT));
	}
    break;
case 320:
#line 1313 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(BIT_RSHIFT));
	}
    break;
case 321:
#line 1316 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(AND));
	}
    break;
case 322:
#line 1319 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(OR));
	}
    break;
case 323:
#line 1322 "parser.yy"
{ 
	  CALL(yylsp[-4], yylsp[-2], exprInlineIf());
	}
    break;
case 324:
#line 1325 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprDot(yyvsp[0].string));
	}
    break;
case 325:
#line 1328 "parser.yy"
{
	  CALL(yyloc, yyloc, exprDeadlock());
	}
    break;
case 326:
#line 1331 "parser.yy"
{  
	  CALL(yylsp[-1], yylsp[-1], exprUnary(NOT));
	}
    break;
case 327:
#line 1333 "parser.yy"
{
	  CALL(yylsp[-1], yylsp[-1], exprBinary(OR));
	}
    break;
case 328:
#line 1336 "parser.yy"
{
	  CALL(yylsp[-2], yylsp[0], exprBinary(AND));
        }
    break;
case 329:
#line 1339 "parser.yy"
{
	  CALL(yylsp[-2], yylsp[0], exprBinary(OR));
        }
    break;
case 330:
#line 1342 "parser.yy"
{
	  CALL(yylsp[-1], yylsp[0], exprUnary(NOT));
        }
    break;
case 331:
#line 1345 "parser.yy"
{
	    CALL(yylsp[-2], yylsp[0], exprBinary(MIN));
        }
    break;
case 332:
#line 1348 "parser.yy"
{
	    CALL(yylsp[-2], yylsp[0], exprBinary(MAX));
        }
    break;
case 334:
#line 1355 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprAssignment(yyvsp[-1].kind));
	}
    break;
case 335:
#line 1361 "parser.yy"
{ yyval.kind = ASSIGN; }
    break;
case 336:
#line 1362 "parser.yy"
{ yyval.kind = ASSPLUS; }
    break;
case 337:
#line 1363 "parser.yy"
{ yyval.kind = ASSMINUS; }
    break;
case 338:
#line 1364 "parser.yy"
{ yyval.kind = ASSDIV; }
    break;
case 339:
#line 1365 "parser.yy"
{ yyval.kind = ASSMOD; }
    break;
case 340:
#line 1366 "parser.yy"
{ yyval.kind = ASSMULT; }
    break;
case 341:
#line 1367 "parser.yy"
{ yyval.kind = ASSAND; }
    break;
case 342:
#line 1368 "parser.yy"
{ yyval.kind = ASSOR; }
    break;
case 343:
#line 1369 "parser.yy"
{ yyval.kind = ASSXOR; }
    break;
case 344:
#line 1370 "parser.yy"
{ yyval.kind = ASSLSHIFT; }
    break;
case 345:
#line 1371 "parser.yy"
{ yyval.kind = ASSRSHIFT; }
    break;
case 346:
#line 1376 "parser.yy"
{ yyval.kind = MINUS; }
    break;
case 347:
#line 1377 "parser.yy"
{ yyval.kind = NOT; }
    break;
case 348:
#line 1382 "parser.yy"
{ yyval.number=0; }
    break;
case 349:
#line 1383 "parser.yy"
{ 
	    yyval.number=1; 
	    CALL(yylsp[0], yylsp[0], exprArg(yyval.number));
	}
    break;
case 350:
#line 1387 "parser.yy"
{ 
	    yyval.number=yyvsp[-2].number+1; 
	    CALL(yylsp[0], yylsp[0], exprArg(yyval.number));
	}
    break;
case 351:
#line 1391 "parser.yy"
{ 
	  yyval.number=yyvsp[-2].number+1; 
	  REPORT_ERROR(last_loc, TypeException(PE_ARGLIST_));
	  CALL(yylsp[0], yylsp[0], exprArg(yyval.number));
	}
    break;
case 357:
#line 1414 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], declType(ParserBuilder::PREFIX_CONST, "int", 0));
	}
    break;
case 358:
#line 1416 "parser.yy"
{ 
	  CALL(yylsp[-3], yylsp[-1], declVarEnd());
	}
    break;
case 360:
#line 1422 "parser.yy"
{ yyval.number=1; }
    break;
case 361:
#line 1423 "parser.yy"
{ yyval.number=yyvsp[-2].number+1; }
    break;
case 362:
#line 1427 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], declVar(yyvsp[-2].string, yyvsp[-1].number, true));
	}
    break;
case 363:
#line 1436 "parser.yy"
{ 
	  CALL(yylsp[-3], yylsp[0], procBegin(yyvsp[-2].string, yyvsp[-1].number));
	}
    break;
case 364:
#line 1439 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;
case 365:
#line 1442 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	  CALL(yylsp[-4], yylsp[0], procBegin(yyvsp[-3].string, yyvsp[-2].number));
	}
    break;
case 366:
#line 1446 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;
case 367:
#line 1449 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACES));
	  CALL(yylsp[-3], yylsp[0], procBegin(yyvsp[-2].string, 0));
	}
    break;
case 368:
#line 1453 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;
case 369:
#line 1456 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_PROCID));
	  CALL(yylsp[-2], yylsp[0], procBegin("_", 0));
	}
    break;
case 370:
#line 1460 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;
case 371:
#line 1463 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], procBegin(yyvsp[-1].string, 0));
	}
    break;
case 372:
#line 1466 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[-1], procEnd());
	}
    break;
case 373:
#line 1472 "parser.yy"
{ yyval.number = 0; }
    break;
case 374:
#line 1473 "parser.yy"
{ yyval.number = yyvsp[-1].number; }
    break;
case 375:
#line 1474 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RPAREN));	  
	  yyval.number = yyvsp[-1].number; 
	}
    break;
case 376:
#line 1478 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_PARAMETERS));	  
	  yyval.number = 0; 
	}
    break;
case 377:
#line 1485 "parser.yy"
{ 
	  yyval.number = yyvsp[0].number; 
	  CALL(yylsp[0], yylsp[0], declParameterEnd());
	}
    break;
case 378:
#line 1489 "parser.yy"
{ 
	  yyval.number = yyvsp[-2].number + yyvsp[0].number;
	  CALL(yylsp[-2], yylsp[0], declParameterEnd());
	}
    break;
case 379:
#line 1493 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_PARAM_DECL_));
          yyval.number = yyvsp[-2].number; 
	}
    break;
case 380:
#line 1500 "parser.yy"
{
          CALL(yylsp[-2], yylsp[0], declParameter(yyvsp[-1].string, yyvsp[0].number == 0, yyvsp[0].number));
	  yyval.number = 1;
	}
    break;
case 381:
#line 1504 "parser.yy"
{
	  CALL(yylsp[-2], yylsp[-2], declType(ParserBuilder::PREFIX_CONST, "int", false));
	  CALL(yylsp[-1], yylsp[0], declParameter(yyvsp[-1].string, false, yyvsp[0].number));
	  yyval.number = 1;
	}
    break;
case 382:
#line 1509 "parser.yy"
{ 
	  CALL(yylsp[-3], yylsp[0], declParameter(yyvsp[-1].string, yyvsp[0].number == 0, yyvsp[0].number));
	  yyval.number = yyvsp[-3].number + 1;
	}
    break;
case 387:
#line 1526 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;
case 388:
#line 1529 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;
case 389:
#line 1532 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_STATE_DECL));
	}
    break;
case 390:
#line 1535 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_STATE_DECL));
	}
    break;
case 391:
#line 1538 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_STATE));
	}
    break;
case 394:
#line 1546 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_LOC_DECL));
	}
    break;
case 395:
#line 1552 "parser.yy"
{ 
	  CALL(yylsp[0], yylsp[0], exprTrue(); ch->procState(yyvsp[0].string, false));
	}
    break;
case 396:
#line 1555 "parser.yy"
{ 
	  CALL(yylsp[-3], yylsp[0], procState(yyvsp[-3].string, true));
	}
    break;
case 398:
#line 1562 "parser.yy"
{	  
	  REPORT_ERROR(last_loc, TypeException(PE_INV));
	}
    break;
case 399:
#line 1565 "parser.yy"
{	  
	  REPORT_ERROR(last_loc, TypeException(PE_INV));
	  CALL(yylsp[0], yylsp[0], exprTrue());
	}
    break;
case 400:
#line 1569 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(AND));
	}
    break;
case 403:
#line 1577 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;
case 404:
#line 1580 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	}
    break;
case 405:
#line 1583 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS_DECL));
	}
    break;
case 406:
#line 1586 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS_DECL));
	}
    break;
case 407:
#line 1589 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_TRANS));
	}
    break;
case 410:
#line 1597 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_ALT_TRANS));	  
	}
    break;
case 411:
#line 1603 "parser.yy"
{ 
	  strcpy(rootTransId, yyvsp[-7].string);
	  CALL(yylsp[-7], yylsp[0], procTransition(yyvsp[-7].string, yyvsp[-5].string));
	}
    break;
case 412:
#line 1607 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  strcpy(rootTransId, yyvsp[-8].string);
	  CALL(yylsp[-8], yylsp[0], procTransition(yyvsp[-8].string, yyvsp[-6].string));
	}
    break;
case 413:
#line 1612 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  strcpy(rootTransId, yyvsp[-7].string); 
	  CALL(yylsp[-7], yylsp[0], procTransition(yyvsp[-7].string, yyvsp[-5].string));
	}
    break;
case 414:
#line 1617 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	  strcpy(rootTransId, yyvsp[-8].string); 
	  CALL(yylsp[-8], yylsp[0], procTransition(yyvsp[-8].string, yyvsp[-6].string));
	}
    break;
case 415:
#line 1622 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_ARROW));
	  strcpy(rootTransId, yyvsp[-8].string); 
	  CALL(yylsp[-8], yylsp[0], procTransition(yyvsp[-8].string, yyvsp[-5].string));
	}
    break;
case 416:
#line 1631 "parser.yy"
{ 
	  CALL(yylsp[-6], yylsp[0], procTransition(rootTransId, yyvsp[-5].string));
	}
    break;
case 417:
#line 1634 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  CALL(yylsp[-6], yylsp[0], procTransition(rootTransId, yyvsp[-5].string));
	}
    break;
case 418:
#line 1638 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_RBRACE));
	  CALL(yylsp[-7], yylsp[0], procTransition(rootTransId, yyvsp[-6].string));
	}
    break;
case 419:
#line 1642 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_LBRACE));
	  CALL(yylsp[-7], yylsp[0], procTransition(rootTransId, yyvsp[-6].string));
	}
    break;
case 420:
#line 1646 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	  CALL(yylsp[-7], yylsp[0], procTransition(rootTransId, yyvsp[-5].string));
	}
    break;
case 421:
#line 1650 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_STATEID));
	  CALL(yylsp[-6], yylsp[0], procTransition(rootTransId, "_"));
	}
    break;
case 424:
#line 1659 "parser.yy"
{
	  CALL(yyloc, yyloc, procGuard());
	}
    break;
case 425:
#line 1662 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yyloc, yyloc, procGuard());
	}
    break;
case 426:
#line 1666 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_SEMICOLON));
	  CALL(yyloc, yyloc, procGuard());
	}
    break;
case 427:
#line 1670 "parser.yy"
{
	  REPORT_ERROR(last_loc, TypeException(PE_GUARD_EXP));
	}
    break;
case 429:
#line 1677 "parser.yy"
{ 
	  CALL(yylsp[-2], yylsp[0], exprBinary(AND));
	}
    break;
case 430:
#line 1680 "parser.yy"
{ 
	  REPORT_ERROR(last_loc, TypeException(PE_GUARD_EXP_));
	  CALL(yylsp[-2], yylsp[0], exprBinary(AND));
	}
    break;
case 435:
#line 1695 "parser.yy"
{
		ch->quit();	
	}
    break;
case 436:
#line 1698 "parser.yy"
{
		ch->property(yyvsp[-1].kind, yylsp[-1].first_line);
	}
    break;
case 437:
#line 1701 "parser.yy"
{
		ch->property(LEADSTO, yylsp[-2].first_line);
	}
    break;
case 438:
#line 1706 "parser.yy"
{ yyval.kind = EF; }
    break;
case 439:
#line 1707 "parser.yy"
{ yyval.kind = EG; }
    break;
case 440:
#line 1708 "parser.yy"
{ yyval.kind = AF; }
    break;
case 441:
#line 1709 "parser.yy"
{ yyval.kind = AG; }
    break;
}

#line 705 "/pack/bison-1.35/share/bison/bison.simple"


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
#line 1711 "parser.yy"


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

