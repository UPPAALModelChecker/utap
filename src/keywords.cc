/* C++ code produced by gperf version 3.1 */
/* Command-line: gperf -C -E -t -L C++ -c -Z Keywords keywords.gperf  */
/* Computed positions: -k'1-2,$' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gperf@gnu.org>."
#endif

#line 1 "keywords.gperf"
struct Keyword { const char *name; int token; int32_t syntax; };
/* maximum key range = 300, duplicates = 0 */

class Keywords
{
private:
  static inline unsigned int hash (const char *str, size_t len);
public:
  static const struct Keyword *in_word_set (const char *str, size_t len);
};

inline unsigned int
Keywords::hash (const char *str, size_t len)
{
  static const unsigned short asso_values[] =
    {
      301, 301, 301, 301, 301, 301, 301, 301, 301, 301,
      301, 301, 301, 301, 301, 301, 301, 301, 301, 301,
      301, 301, 301, 301, 301, 301, 301, 301, 301, 301,
      301, 301, 301, 301, 301, 301, 301, 301, 301, 301,
      301, 301, 301, 301, 301, 301, 301, 301,   0,   0,
       95, 301, 301, 301, 301, 301, 301, 301, 301, 301,
      301, 301, 301, 301, 301, 301, 301, 301, 301, 301,
      301, 301, 301, 301,   0, 301, 301, 301, 301,   0,
      301,  25,   0, 301, 301, 301, 301, 301,   0,   0,
      301, 301, 301, 301, 301, 301, 301,  90,  10, 140,
        5,  45,  45,  30,   0,  80,  35, 155,   5,  60,
       25, 135,  70,  55,  10,   5,   0,  50,  40, 145,
       35,  45, 301,  65,  35, 301, 301, 301, 301, 301,
      301, 301, 301, 301, 301, 301, 301, 301, 301, 301,
      301, 301, 301, 301, 301, 301, 301, 301, 301, 301,
      301, 301, 301, 301, 301, 301, 301, 301, 301, 301,
      301, 301, 301, 301, 301, 301, 301, 301, 301, 301,
      301, 301, 301, 301, 301, 301, 301, 301, 301, 301,
      301, 301, 301, 301, 301, 301, 301, 301, 301, 301,
      301, 301, 301, 301, 301, 301, 301, 301, 301, 301,
      301, 301, 301, 301, 301, 301, 301, 301, 301, 301,
      301, 301, 301, 301, 301, 301, 301, 301, 301, 301,
      301, 301, 301, 301, 301, 301, 301, 301, 301, 301,
      301, 301, 301, 301, 301, 301, 301, 301, 301, 301,
      301, 301, 301, 301, 301, 301, 301, 301, 301, 301,
      301, 301, 301, 301, 301, 301, 301, 301, 301
    };
  unsigned int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[static_cast<unsigned char>(str[1]+3)];
      /*FALLTHROUGH*/
      case 1:
        hval += asso_values[static_cast<unsigned char>(str[0]+1)];
        break;
    }
  return hval + asso_values[static_cast<unsigned char>(str[len - 1])];
}

const struct Keyword *
Keywords::in_word_set (const char *str, size_t len)
{
  enum
    {
      TOTAL_KEYWORDS = 132,
      MIN_WORD_LENGTH = 1,
      MAX_WORD_LENGTH = 14,
      MIN_HASH_VALUE = 1,
      MAX_HASH_VALUE = 300
    };

  static const struct Keyword wordlist[] =
    {
      {""},
#line 66 "keywords.gperf"
      {"X",                      T_MITL_NEXT,    SYNTAX_PROPERTY},
#line 40 "keywords.gperf"
      {"IO",			T_IO,		SYNTAX_NEW},
      {""},
#line 83 "keywords.gperf"
      {"sqrt",                   T_SQRT,         SYNTAX_PROPERTY | SYNTAX_NEW},
      {""},
#line 4 "keywords.gperf"
      {"select",			T_SELECT,	SYNTAX_NEW},
      {""},
#line 61 "keywords.gperf"
      {"sat",                    T_SCENARIO,     SYNTAX_PROPERTY},
#line 93 "keywords.gperf"
      {"sinh",                   T_SINH,         SYNTAX_PROPERTY | SYNTAX_NEW},
#line 38 "keywords.gperf"
      {"gantt",                  T_GANTT,        SYNTAX_NEW},
      {""},
#line 118 "keywords.gperf"
      {"signbit",                T_SIGNBIT,      SYNTAX_PROPERTY | SYNTAX_NEW},
      {""},
#line 103 "keywords.gperf"
      {"ceil",                   T_CEIL,         SYNTAX_PROPERTY | SYNTAX_NEW},
#line 57 "keywords.gperf"
      {"refinement",             T_REFINEMENT,   SYNTAX_PROPERTY | SYNTAX_TIGA},
      {""}, {""}, {""},
#line 94 "keywords.gperf"
      {"cosh",                   T_COSH,         SYNTAX_PROPERTY | SYNTAX_NEW},
#line 3 "keywords.gperf"
      {"const",			T_CONST,	SYNTAX_OLD | SYNTAX_NEW},
#line 15 "keywords.gperf"
      {"commit",			T_COMMIT,	SYNTAX_OLD | SYNTAX_NEW},
      {""},
#line 87 "keywords.gperf"
      {"cos",                    T_COS,          SYNTAX_PROPERTY | SYNTAX_NEW},
#line 54 "keywords.gperf"
      {"control_t",              T_CONTROL_T,    SYNTAX_PROPERTY | SYNTAX_TIGA},
#line 106 "keywords.gperf"
      {"round",                  T_ROUND,        SYNTAX_PROPERTY | SYNTAX_NEW},
      {""},
#line 53 "keywords.gperf"
      {"control",                T_CONTROL,      SYNTAX_PROPERTY | SYNTAX_TIGA},
#line 124 "keywords.gperf"
      {"random_normal",          T_RANDOM_NORMAL, SYNTAX_PROPERTY | SYNTAX_NEW},
#line 127 "keywords.gperf"
      {"random_weibull",        	T_RANDOM_WEIBULL,SYNTAX_PROPERTY | SYNTAX_NEW},
      {""}, {""}, {""},
#line 86 "keywords.gperf"
      {"sin",                    T_SIN,          SYNTAX_PROPERTY | SYNTAX_NEW},
      {""},
#line 130 "keywords.gperf"
      {"spawn",                  T_SPAWN,        SYNTAX_NEW},
#line 31 "keywords.gperf"
      {"return", 		T_RETURN,	SYNTAX_NEW},
      {""}, {""},
#line 107 "keywords.gperf"
      {"fint",                   T_FINT,         SYNTAX_PROPERTY | SYNTAX_NEW},
#line 55 "keywords.gperf"
      {"simulation",             T_SIMULATION,   SYNTAX_PROPERTY | SYNTAX_TIGA},
      {""}, {""},
#line 59 "keywords.gperf"
      {"specification",          T_SPECIFICATION,SYNTAX_PROPERTY | SYNTAX_TIGA},
#line 68 "keywords.gperf"
      {"fabs",                   T_FABS,         SYNTAX_PROPERTY | SYNTAX_NEW},
#line 5 "keywords.gperf"
      {"guard",			T_GUARD,	SYNTAX_OLD | SYNTAX_NEW},
      {""},
#line 133 "keywords.gperf"
      {"foreach",                T_FOREACH,      SYNTAX_PROPERTY},
#line 112 "keywords.gperf"
      {"copysign",               T_COPYSIGN,     SYNTAX_PROPERTY | SYNTAX_NEW},
#line 125 "keywords.gperf"
      {"random_poisson",        	T_RANDOM_POISSON,SYNTAX_PROPERTY | SYNTAX_NEW},
      {""},
#line 41 "keywords.gperf"
      {"forall", 		T_FORALL,	SYNTAX_NEW | SYNTAX_PROPERTY},
#line 30 "keywords.gperf"
      {"default", 		T_DEFAULT,	SYNTAX_NEW},
#line 25 "keywords.gperf"
      {"for",			T_FOR,		SYNTAX_NEW},
#line 84 "keywords.gperf"
      {"cbrt",                   T_CBRT,         SYNTAX_PROPERTY | SYNTAX_NEW},
#line 96 "keywords.gperf"
      {"asinh",                  T_ASINH,        SYNTAX_PROPERTY | SYNTAX_NEW},
#line 39 "keywords.gperf"
      {"assert",			T_ASSERT,	SYNTAX_NEW},
      {""},
#line 56 "keywords.gperf"
      {"simulate",               T_SIMULATE,     SYNTAX_PROPERTY},
#line 95 "keywords.gperf"
      {"tanh",                   T_TANH,         SYNTAX_PROPERTY | SYNTAX_NEW},
#line 97 "keywords.gperf"
      {"acosh",                  T_ACOSH,        SYNTAX_PROPERTY | SYNTAX_NEW},
#line 52 "keywords.gperf"
      {"scalar",			T_SCALAR,	SYNTAX_OLD | SYNTAX_NEW | SYNTAX_PROPERTY},
      {""},
#line 67 "keywords.gperf"
      {"abs",                    T_ABS,          SYNTAX_PROPERTY | SYNTAX_NEW},
#line 90 "keywords.gperf"
      {"acos",                   T_ACOS,         SYNTAX_PROPERTY | SYNTAX_NEW},
      {""}, {""}, {""},
#line 22 "keywords.gperf"
      {"xor",                    T_KW_XOR,       SYNTAX_NEW},
#line 121 "keywords.gperf"
      {"random_arcsine",         T_RANDOM_ARCSINE,SYNTAX_PROPERTY | SYNTAX_NEW},
      {""},
#line 58 "keywords.gperf"
      {"consistency",            T_CONSISTENCY,  SYNTAX_PROPERTY | SYNTAX_TIGA},
      {""},
#line 20 "keywords.gperf"
      {"and",			T_KW_AND,	SYNTAX_OLD | SYNTAX_NEW | SYNTAX_PROPERTY},
      {""},
#line 79 "keywords.gperf"
      {"log10",                  T_LOG10,        SYNTAX_PROPERTY | SYNTAX_NEW},
#line 120 "keywords.gperf"
      {"random",                 T_RANDOM,       SYNTAX_PROPERTY | SYNTAX_NEW},
      {""}, {""},
#line 89 "keywords.gperf"
      {"asin",                   T_ASIN,         SYNTAX_PROPERTY | SYNTAX_NEW},
      {""},
#line 7 "keywords.gperf"
      {"assign",			T_ASSIGN,	SYNTAX_OLD | SYNTAX_NEW},
      {""},
#line 88 "keywords.gperf"
      {"tan",                    T_TAN,          SYNTAX_PROPERTY | SYNTAX_NEW},
#line 110 "keywords.gperf"
      {"logb",                   T_LOGB,         SYNTAX_PROPERTY | SYNTAX_NEW},
#line 19 "keywords.gperf"
      {"false",			T_FALSE,	SYNTAX_OLD | SYNTAX_NEW | SYNTAX_PROPERTY},
      {""},
#line 65 "keywords.gperf"
      {"Pr",                     T_PROBA,        SYNTAX_PROPERTY},
#line 117 "keywords.gperf"
      {"isnormal",               T_ISNORMAL,     SYNTAX_PROPERTY | SYNTAX_NEW},
      {""},
#line 113 "keywords.gperf"
      {"fpclassify",             T_FPCLASSIFY,   SYNTAX_PROPERTY | SYNTAX_NEW},
#line 119 "keywords.gperf"
      {"isunordered",            T_ISUNORDERED,  SYNTAX_PROPERTY | SYNTAX_NEW},
      {""},
#line 47 "keywords.gperf"
      {"int",			T_INT,		SYNTAX_OLD | SYNTAX_NEW | SYNTAX_PROPERTY},
#line 12 "keywords.gperf"
      {"init",			T_INIT,		SYNTAX_OLD | SYNTAX_NEW},
#line 134 "keywords.gperf"
      {"query",                  T_QUERY,        SYNTAX_NEW},
#line 14 "keywords.gperf"
      {"urgent",			T_URGENT,	SYNTAX_OLD | SYNTAX_NEW},
      {""},
#line 43 "keywords.gperf"
      {"sum",			T_SUM,		SYNTAX_NEW | SYNTAX_PROPERTY},
      {""},
#line 126 "keywords.gperf"
      {"random_tri",				T_RANDOM_TRI,	SYNTAX_PROPERTY | SYNTAX_NEW},
#line 17 "keywords.gperf"
      {"system",			T_SYSTEM,	SYNTAX_OLD | SYNTAX_NEW | SYNTAX_PROPERTY},
      {""},
#line 78 "keywords.gperf"
      {"log",                    T_LOG,          SYNTAX_PROPERTY | SYNTAX_NEW},
      {""},
#line 116 "keywords.gperf"
      {"isnan",                  T_ISNAN,        SYNTAX_PROPERTY | SYNTAX_NEW},
#line 48 "keywords.gperf"
      {"double",                 T_DOUBLE,       SYNTAX_OLD | SYNTAX_NEW},
      {""},
#line 63 "keywords.gperf"
      {"sup",                    T_SUP,          SYNTAX_PROPERTY},
#line 69 "keywords.gperf"
      {"fmod",                   T_FMOD,         SYNTAX_PROPERTY | SYNTAX_NEW},
#line 13 "keywords.gperf"
      {"trans",			T_TRANS,	SYNTAX_OLD | SYNTAX_NEW},
#line 122 "keywords.gperf"
      {"random_beta",          	T_RANDOM_BETA, 	 SYNTAX_PROPERTY | SYNTAX_NEW},
#line 123 "keywords.gperf"
      {"random_gamma",          	T_RANDOM_GAMMA,  SYNTAX_PROPERTY | SYNTAX_NEW},
      {""},
#line 131 "keywords.gperf"
      {"exit",                   T_EXIT,         SYNTAX_NEW},
#line 76 "keywords.gperf"
      {"expm1",                  T_EXPM1,        SYNTAX_PROPERTY | SYNTAX_NEW},
      {""},
#line 9 "keywords.gperf"
      {"process",		T_PROCESS,	SYNTAX_OLD | SYNTAX_NEW},
#line 37 "keywords.gperf"
      {"progress",		T_PROGRESS,	SYNTAX_NEW},
#line 34 "keywords.gperf"
      {"meta",			T_META,		SYNTAX_NEW},
#line 85 "keywords.gperf"
      {"hypot",                  T_HYPOT,        SYNTAX_PROPERTY | SYNTAX_NEW},
#line 42 "keywords.gperf"
      {"exists", 		T_EXISTS,	SYNTAX_NEW | SYNTAX_PROPERTY},
      {""}, {""},
#line 73 "keywords.gperf"
      {"fdim",                   T_FDIM,         SYNTAX_PROPERTY | SYNTAX_NEW},
#line 115 "keywords.gperf"
      {"isinf",                  T_ISINF,        SYNTAX_PROPERTY | SYNTAX_NEW},
#line 128 "keywords.gperf"
      {"hybrid",                 T_HYBRID,	SYNTAX_NEW},
      {""},
#line 114 "keywords.gperf"
      {"isfinite",               T_ISFINITE,     SYNTAX_PROPERTY | SYNTAX_NEW},
#line 72 "keywords.gperf"
      {"fmin",                   T_FMIN,         SYNTAX_PROPERTY | SYNTAX_NEW},
      {""}, {""},
#line 21 "keywords.gperf"
      {"or",			T_KW_OR,	SYNTAX_OLD | SYNTAX_NEW | SYNTAX_PROPERTY},
      {""},
#line 64 "keywords.gperf"
      {"Pmax",			T_PMAX,		SYNTAX_PROPERTY | SYNTAX_PROB},
      {""}, {""},
#line 32 "keywords.gperf"
      {"typedef",		T_TYPEDEF,	SYNTAX_NEW},
#line 62 "keywords.gperf"
      {"inf",                    T_INF,          SYNTAX_PROPERTY},
#line 71 "keywords.gperf"
      {"fmax",                   T_FMAX,         SYNTAX_PROPERTY | SYNTAX_NEW},
      {""}, {""},
#line 77 "keywords.gperf"
      {"ln",                     T_LN,           SYNTAX_PROPERTY | SYNTAX_NEW},
#line 99 "keywords.gperf"
      {"erf",                    T_ERF,          SYNTAX_PROPERTY | SYNTAX_NEW},
#line 60 "keywords.gperf"
      {"implementation",         T_IMPLEMENTATION,SYNTAX_PROPERTY | SYNTAX_TIGA},
#line 81 "keywords.gperf"
      {"log1p",                  T_LOG1P,        SYNTAX_PROPERTY | SYNTAX_NEW},
      {""},
#line 36 "keywords.gperf"
      {"after_update",	        T_AFTER,	SYNTAX_NEW},
#line 23 "keywords.gperf"
      {"not",			T_KW_NOT,	SYNTAX_OLD | SYNTAX_NEW | SYNTAX_PROPERTY},
#line 18 "keywords.gperf"
      {"true",			T_TRUE,		SYNTAX_OLD | SYNTAX_NEW | SYNTAX_PROPERTY},
      {""},
#line 33 "keywords.gperf"
      {"struct",			T_STRUCT,	SYNTAX_NEW},
      {""}, {""},
#line 111 "keywords.gperf"
      {"nextafter",              T_NEXTAFTER,    SYNTAX_PROPERTY | SYNTAX_NEW},
#line 24 "keywords.gperf"
      {"imply",			T_KW_IMPLY,	SYNTAX_OLD | SYNTAX_NEW | SYNTAX_PROPERTY},
      {""}, {""},
#line 45 "keywords.gperf"
      {"priority",		T_PRIORITY,	SYNTAX_OLD | SYNTAX_NEW},
#line 46 "keywords.gperf"
      {"bool",			T_BOOL,		SYNTAX_OLD | SYNTAX_NEW},
#line 98 "keywords.gperf"
      {"atanh",                  T_ATANH,        SYNTAX_PROPERTY | SYNTAX_NEW},
#line 8 "keywords.gperf"
      {"probability",		T_PROBABILITY,	SYNTAX_OLD | SYNTAX_NEW},
#line 28 "keywords.gperf"
      {"if", 			T_IF,		SYNTAX_NEW},
      {""},
#line 51 "keywords.gperf"
      {"void",			T_VOID,		SYNTAX_OLD | SYNTAX_NEW},
#line 108 "keywords.gperf"
      {"ldexp",                  T_LDEXP,        SYNTAX_PROPERTY | SYNTAX_NEW},
      {""}, {""}, {""},
#line 80 "keywords.gperf"
      {"log2",                   T_LOG2,         SYNTAX_PROPERTY | SYNTAX_NEW},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 6 "keywords.gperf"
      {"sync",			T_SYNC,		SYNTAX_OLD | SYNTAX_NEW},
#line 104 "keywords.gperf"
      {"floor",                  T_FLOOR,        SYNTAX_PROPERTY | SYNTAX_NEW},
#line 101 "keywords.gperf"
      {"tgamma",                 T_TGAMMA,       SYNTAX_PROPERTY | SYNTAX_NEW},
      {""},
#line 74 "keywords.gperf"
      {"exp",                    T_EXP,          SYNTAX_PROPERTY | SYNTAX_NEW},
#line 91 "keywords.gperf"
      {"atan",                   T_ATAN,         SYNTAX_PROPERTY | SYNTAX_NEW},
#line 109 "keywords.gperf"
      {"ilogb",                  T_ILOGB,        SYNTAX_PROPERTY | SYNTAX_NEW},
      {""}, {""}, {""},
#line 49 "keywords.gperf"
      {"chan",			T_CHAN,		SYNTAX_OLD | SYNTAX_NEW},
      {""},
#line 102 "keywords.gperf"
      {"lgamma",                 T_LGAMMA,       SYNTAX_PROPERTY | SYNTAX_NEW},
#line 27 "keywords.gperf"
      {"do", 			T_DO,		SYNTAX_NEW},
#line 70 "keywords.gperf"
      {"fma",                    T_FMA,          SYNTAX_PROPERTY | SYNTAX_NEW},
      {""},
#line 10 "keywords.gperf"
      {"state",			T_STATE,	SYNTAX_OLD | SYNTAX_NEW},
      {""}, {""},
#line 35 "keywords.gperf"
      {"before_update",	        T_BEFORE,	SYNTAX_NEW},
#line 16 "keywords.gperf"
      {"broadcast",              T_BROADCAST,    SYNTAX_OLD | SYNTAX_NEW},
      {""},
#line 11 "keywords.gperf"
      {"branchpoint",		T_BRANCHPOINT,	SYNTAX_OLD | SYNTAX_NEW},
      {""}, {""}, {""}, {""}, {""}, {""},
#line 44 "keywords.gperf"
      {"deadlock",		T_DEADLOCK,	SYNTAX_PROPERTY},
#line 75 "keywords.gperf"
      {"exp2",                   T_EXP2,         SYNTAX_PROPERTY | SYNTAX_NEW},
      {""}, {""}, {""},
#line 82 "keywords.gperf"
      {"pow",                    T_POW,          SYNTAX_PROPERTY | SYNTAX_NEW},
      {""}, {""}, {""}, {""}, {""}, {""},
#line 132 "keywords.gperf"
      {"numOf",                  T_NUMOF,        SYNTAX_PROPERTY},
      {""}, {""}, {""}, {""}, {""}, {""},
#line 129 "keywords.gperf"
      {"dynamic",                T_DYNAMIC,      SYNTAX_NEW},
      {""},
#line 29 "keywords.gperf"
      {"else", 			T_ELSE,		SYNTAX_NEW},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 100 "keywords.gperf"
      {"erfc",                   T_ERFC,         SYNTAX_PROPERTY | SYNTAX_NEW},
#line 26 "keywords.gperf"
      {"while",			T_WHILE,	SYNTAX_NEW},
      {""}, {""}, {""}, {""},
#line 105 "keywords.gperf"
      {"trunc",                  T_TRUNC,        SYNTAX_PROPERTY | SYNTAX_NEW},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 92 "keywords.gperf"
      {"atan2",                  T_ATAN2,        SYNTAX_PROPERTY | SYNTAX_NEW},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 50 "keywords.gperf"
      {"clock",			T_CLOCK,	SYNTAX_OLD | SYNTAX_NEW}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      unsigned int key = hash (str, len);

      if (key <= MAX_HASH_VALUE)
        {
          const char *s = wordlist[key].name;

          if (*str == *s && !strncmp (str + 1, s + 1, len - 1) && s[len] == '\0')
            return &wordlist[key];
        }
    }
  return 0;
}
#line 135 "keywords.gperf"


bool isKeyword(const char *id, uint32_t syntax)
{
    const Keyword *keyword = Keywords::in_word_set(id, strlen(id));
    return (keyword != NULL && (keyword->syntax & syntax));
}
