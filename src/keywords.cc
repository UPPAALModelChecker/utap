/* C++ code produced by gperf version 2.7.2 */
/* Command-line: gperf -C -E -t -L C++ -c -Z Keywords keywords.gperf  */
struct Keyword { char *name; int token; int32_t syntax; };
/* maximum key range = 75, duplicates = 0 */

class Keywords
{
private:
  static inline unsigned int hash (const char *str, unsigned int len);
public:
  static const struct Keyword *in_word_set (const char *str, unsigned int len);
};

inline unsigned int
Keywords::hash (register const char *str, register unsigned int len)
{
  static const unsigned char asso_values[] =
    {
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 45, 30, 10,
       0, 15,  5,  5, 20, 20, 77, 30, 77, 15,
      25,  0, 10,  0, 35, 30,  0,  5, 77, 10,
      77, 15, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77, 77, 77, 77, 77,
      77, 77, 77, 77, 77, 77
    };
  return len + asso_values[(unsigned char)str[len - 1]] + asso_values[(unsigned char)str[0]];
}

const struct Keyword *
Keywords::in_word_set (register const char *str, register unsigned int len)
{
  enum
    {
      TOTAL_KEYWORDS = 37,
      MIN_WORD_LENGTH = 2,
      MAX_WORD_LENGTH = 13,
      MIN_HASH_VALUE = 2,
      MAX_HASH_VALUE = 76
    };

  static const struct Keyword wordlist[] =
    {
      {""}, {""},
      {"do", 			T_DO,		SYNTAX_NEW},
      {""},
      {"quit",			T_QUIT,		SYNTAX_PROPERTY},
      {""}, {""},
      {"default", 		T_DEFAULT,	SYNTAX_NEW},
      {""}, {""},
      {"guard",			T_GUARD,	SYNTAX_OLD | SYNTAX_NEW},
      {"urgent",			T_URGENT,	SYNTAX_OLD | SYNTAX_NEW},
      {"typedef",		T_TYPEDEF,	SYNTAX_NEW},
      {""},
      {"cost",			T_COST,		SYNTAX_GUIDING},
      {"const",			T_CONST,	SYNTAX_OLD | SYNTAX_NEW},
      {"commit",			T_COMMIT,	SYNTAX_OLD | SYNTAX_NEW},
      {""}, {""},
      {"true",			T_TRUE,		SYNTAX_NEW | SYNTAX_PROPERTY},
      {""}, {""}, {""}, {""},
      {"init",			T_INIT,		SYNTAX_OLD | SYNTAX_NEW},
      {"false",			T_FALSE,	SYNTAX_NEW | SYNTAX_PROPERTY},
      {""},
      {"if", 			T_IF,		SYNTAX_NEW},
      {"not",			T_BOOL_NOT,	SYNTAX_PROPERTY},
      {"case", 			T_CASE,		SYNTAX_NEW},
      {"while",			T_WHILE,	SYNTAX_NEW},
      {""}, {""},
      {"continue", 		T_CONTINUE,	SYNTAX_NEW},
      {"else", 			T_ELSE,		SYNTAX_NEW},
      {"trans",			T_TRANS,	SYNTAX_OLD | SYNTAX_NEW},
      {"struct",			T_STRUCT,	SYNTAX_NEW},
      {"or",			T_BOOL_OR,	SYNTAX_PROPERTY},
      {"deadlock",		T_DEADLOCK,	SYNTAX_PROPERTY},
      {"broadcast",       	T_BROADCAST,	SYNTAX_OLD | SYNTAX_NEW},
      {"imply",			T_IMPLY,	SYNTAX_PROPERTY},
      {""}, {""},
      {"for",			T_FOR,		SYNTAX_NEW},
      {"sync",			T_SYNC,		SYNTAX_OLD | SYNTAX_NEW},
      {""}, {""},
      {"process",		T_PROCESS,	SYNTAX_OLD | SYNTAX_NEW},
      {"and",			T_BOOL_AND,	SYNTAX_PROPERTY},
      {""},
      {"state",			T_STATE,	SYNTAX_OLD | SYNTAX_NEW},
      {"system",			T_SYSTEM,	SYNTAX_OLD | SYNTAX_NEW},
      {""}, {""},
      {"rate",			T_RATE,		SYNTAX_GUIDING},
      {""},
      {"switch", 		T_SWITCH,	SYNTAX_NEW},
      {""},
      {"before_update",		T_BEFORE,	SYNTAX_GUIDING},
      {""}, {""}, {""}, {""}, {""}, {""},
      {"break",			T_BREAK,	SYNTAX_NEW},
      {"return", 		T_RETURN,	SYNTAX_NEW},
      {""}, {""}, {""}, {""}, {""},
      {"after_update",		T_AFTER,	SYNTAX_GUIDING},
      {""}, {""}, {""},
      {"assign",			T_ASSIGN,	SYNTAX_OLD | SYNTAX_NEW}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register const char *s = wordlist[key].name;

          if (*str == *s && !strncmp (str + 1, s + 1, len - 1) && s[len] == '\0')
            return &wordlist[key];
        }
    }
  return 0;
}

bool isKeyword(const char *id, uint32_t syntax)
{
    const Keyword *keyword = Keywords::in_word_set(id, strlen(id));
    return (keyword != NULL && (keyword->syntax & syntax));
}
