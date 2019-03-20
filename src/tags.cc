/* C++ code produced by gperf version 2.7.2 */
/* Command-line: gperf -C -E -t -L C++ -c -K str -Z Tags tags.gperf  */
struct Tag { char *str; tag_t tag; };
/* maximum key range = 31, duplicates = 0 */

class Tags
{
private:
  static inline unsigned int hash (const char *str, unsigned int len);
public:
  static const struct Tag *in_word_set (const char *str, unsigned int len);
};

inline unsigned int
Tags::hash (register const char *str, register unsigned int len)
{
  static const unsigned char asso_values[] =
    {
      34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
      34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
      34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
      34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
      34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
      34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
      34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
      34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
      34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
      34, 34, 34, 34, 34, 34, 34,  0, 34, 10,
       0, 10, 34, 34, 34, 20, 34, 34,  0, 15,
       0, 34,  0, 34,  0,  0,  0, 20, 34, 34,
      34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
      34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
      34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
      34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
      34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
      34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
      34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
      34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
      34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
      34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
      34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
      34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
      34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
      34, 34, 34, 34, 34, 34
    };
  return len + asso_values[(unsigned char)str[len - 1]] + asso_values[(unsigned char)str[0]];
}

const struct Tag *
Tags::in_word_set (register const char *str, register unsigned int len)
{
  enum
    {
      TOTAL_KEYWORDS = 17,
      MIN_WORD_LENGTH = 3,
      MAX_WORD_LENGTH = 13,
      MIN_HASH_VALUE = 3,
      MAX_HASH_VALUE = 33
    };

  static const struct Tag wordlist[] =
    {
      {""}, {""}, {""},
      {"nta",		TAG_NTA},
      {"nail",		TAG_NAIL},
      {"label",		TAG_LABEL},
      {"target",		TAG_TARGET},
      {""},
      {"location",	TAG_LOCATION},
      {"parameter",	TAG_PARAMETER},
      {"transition",	TAG_TRANSITION},
      {"declaration",	TAG_DECLARATION},
      {""}, {""},
      {"name",		TAG_NAME},
      {""},
      {"source",		TAG_SOURCE},
      {""},
      {"template",	TAG_TEMPLATE},
      {"committed",	TAG_COMMITTED},
      {""},
      {"system",		TAG_SYSTEM},
      {""}, {""},
      {"init",		TAG_INIT},
      {""},
      {"urgent",		TAG_URGENT},
      {"imports",	TAG_IMPORTS},
      {""}, {""}, {""}, {""}, {""},
      {"instantiation",	TAG_INSTANTIATION}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register const char *s = wordlist[key].str;

          if (*str == *s && !strncmp (str + 1, s + 1, len - 1) && s[len] == '\0')
            return &wordlist[key];
        }
    }
  return 0;
}
