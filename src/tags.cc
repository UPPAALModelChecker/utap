/* C++ code produced by gperf version 3.1 */
/* Command-line: gperf -C -E -t -L C++ -c -K str -Z Tags tags.gperf  */
/* Computed positions: -k'1,3' */

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

#line 1 "tags.gperf"
struct Tag { const char *str; tag_t tag; };
/* maximum key range = 48, duplicates = 0 */

class Tags
{
private:
  static inline unsigned int hash (const char *str, size_t len);
public:
  static const struct Tag *in_word_set (const char *str, size_t len);
};

inline unsigned int
Tags::hash (const char *str, size_t len)
{
  static const unsigned char asso_values[] =
    {
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 10, 15,  5,
      35, 10, 10,  5, 52,  0, 52, 52, 10,  5,
      20,  5, 20,  5, 20,  0, 15,  5, 52, 52,
      52,  0, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52
    };
  return len + asso_values[static_cast<unsigned char>(str[2])] + asso_values[static_cast<unsigned char>(str[0])];
}

const struct Tag *
Tags::in_word_set (const char *str, size_t len)
{
  enum
    {
      TOTAL_KEYWORDS = 36,
      MIN_WORD_LENGTH = 3,
      MAX_WORD_LENGTH = 13,
      MIN_HASH_VALUE = 4,
      MAX_HASH_VALUE = 51
    };

  static const struct Tag wordlist[] =
    {
      {""}, {""}, {""}, {""},
#line 12 "tags.gperf"
      {"init",		TAG_INIT},
      {""},
#line 8 "tags.gperf"
      {"system",		TAG_SYSTEM},
      {""},
#line 28 "tags.gperf"
      {"instance",       TAG_INSTANCE},
#line 34 "tags.gperf"
      {"sbml",           TAG_SBML},
      {""},
#line 17 "tags.gperf"
      {"source",		TAG_SOURCE},
#line 30 "tags.gperf"
      {"message",        TAG_MESSAGE},
#line 7 "tags.gperf"
      {"instantiation",	TAG_INSTANTIATION},
#line 25 "tags.gperf"
      {"yloccoord",      TAG_YLOCCOORD},
      {""},
#line 14 "tags.gperf"
      {"urgent",		TAG_URGENT},
#line 38 "tags.gperf"
      {"comment",        TAG_COMMENT},
#line 22 "tags.gperf"
      {"lsc",            TAG_LSC},
#line 15 "tags.gperf"
      {"committed",	TAG_COMMITTED},
#line 36 "tags.gperf"
      {"query",          TAG_QUERY},
#line 33 "tags.gperf"
      {"anchor",         TAG_ANCHOR},
#line 35 "tags.gperf"
      {"queries",        TAG_QUERIES},
#line 11 "tags.gperf"
      {"location",	TAG_LOCATION},
#line 20 "tags.gperf"
      {"nail",		TAG_NAIL},
      {""},
#line 26 "tags.gperf"
      {"lsclocation",    TAG_LSCLOCATION},
#line 4 "tags.gperf"
      {"imports",	TAG_IMPORTS},
#line 6 "tags.gperf"
      {"template",	TAG_TEMPLATE},
#line 9 "tags.gperf"
      {"name",		TAG_NAME},
#line 19 "tags.gperf"
      {"label",		TAG_LABEL},
#line 29 "tags.gperf"
      {"temperature",    TAG_TEMPERATURE},
#line 21 "tags.gperf"
      {"project",        TAG_PROJECT},
#line 3 "tags.gperf"
      {"nta",		TAG_NTA},
#line 31 "tags.gperf"
      {"condition",      TAG_CONDITION},
#line 13 "tags.gperf"
      {"transition",	TAG_TRANSITION},
#line 16 "tags.gperf"
      {"branchpoint",    TAG_BRANCHPOINT},
#line 37 "tags.gperf"
      {"formula",        TAG_FORMULA},
#line 27 "tags.gperf"
      {"prechart",       TAG_PRECHART},
#line 23 "tags.gperf"
      {"type",           TAG_TYPE},
      {""},
#line 18 "tags.gperf"
      {"target",		TAG_TARGET},
      {""}, {""},
#line 24 "tags.gperf"
      {"mode",           TAG_MODE},
      {""},
#line 32 "tags.gperf"
      {"update",         TAG_UPDATE},
      {""}, {""},
#line 10 "tags.gperf"
      {"parameter",	TAG_PARAMETER},
      {""},
#line 5 "tags.gperf"
      {"declaration",	TAG_DECLARATION}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      unsigned int key = hash (str, len);

      if (key <= MAX_HASH_VALUE)
        {
          const char *s = wordlist[key].str;

          if (*str == *s && !strncmp (str + 1, s + 1, len - 1) && s[len] == '\0')
            return &wordlist[key];
        }
    }
  return 0;
}
#line 39 "tags.gperf"

