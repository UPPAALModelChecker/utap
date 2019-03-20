/* C++ code produced by gperf version 2.7.2 */
/* Command-line: gperf -C -E -t -L C++ -c -Z Keywords keywords.gperf  */
struct Keyword { char *name; int token; int32_t syntax; };
/* maximum key range = 78, duplicates = 0 */

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
      82, 82, 82, 82, 82, 82, 82, 82, 82, 82,
      82, 82, 82, 82, 82, 82, 82, 82, 82, 82,
      82, 82, 82, 82, 82, 82, 82, 82, 82, 82,
      82, 82, 82, 82, 82, 82, 82, 82, 82, 82,
      82, 82, 82, 82, 82, 82, 82, 82, 82, 82,
      82, 82, 82, 82, 82, 82, 82, 82, 82, 82,
      82, 82, 82, 82, 82, 82, 82, 82, 82, 82,
      82, 82, 82, 82, 82, 82, 82, 82, 82, 82,
      82, 82, 82, 82, 82, 82, 82, 82, 82, 82,
      82, 82, 82, 82, 82, 82, 82, 20,  0, 10,
       0, 15,  5,  5, 25, 20, 82, 35, 82, 15,
      10, 20, 10,  0, 30, 50,  0,  5, 82, 15,
      82, 25, 82, 82, 82, 82, 82, 82, 82, 82,
      82, 82, 82, 82, 82, 82, 82, 82, 82, 82,
      82, 82, 82, 82, 82, 82, 82, 82, 82, 82,
      82, 82, 82, 82, 82, 82, 82, 82, 82, 82,
      82, 82, 82, 82, 82, 82, 82, 82, 82, 82,
      82, 82, 82, 82, 82, 82, 82, 82, 82, 82,
      82, 82, 82, 82, 82, 82, 82, 82, 82, 82,
      82, 82, 82, 82, 82, 82, 82, 82, 82, 82,
      82, 82, 82, 82, 82, 82, 82, 82, 82, 82,
      82, 82, 82, 82, 82, 82, 82, 82, 82, 82,
      82, 82, 82, 82, 82, 82, 82, 82, 82, 82,
      82, 82, 82, 82, 82, 82, 82, 82, 82, 82,
      82, 82, 82, 82, 82, 82, 82, 82, 82, 82,
      82, 82, 82, 82, 82, 82
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
      MIN_HASH_VALUE = 4,
      MAX_HASH_VALUE = 81
    };

  static const struct Keyword wordlist[] =
    {
      {""}, {""}, {""}, {""},
      {"quit",			T_QUIT,		SYNTAX_PROPERTY},
      {""}, {""},
      {"default", 		T_DEFAULT,	SYNTAX_NEW},
      {""},
      {"broadcast",       	T_BROADCAST,	SYNTAX_OLD | SYNTAX_NEW},
      {"guard",			T_GUARD,	SYNTAX_OLD | SYNTAX_NEW},
      {"urgent",			T_URGENT,	SYNTAX_OLD | SYNTAX_NEW},
      {"typedef",		T_TYPEDEF,	SYNTAX_NEW},
      {"not",			T_KW_NOT,	SYNTAX_OLD | SYNTAX_NEW | SYNTAX_PROPERTY},
      {"cost",			T_COST,		SYNTAX_GUIDING},
      {"const",			T_CONST,	SYNTAX_OLD | SYNTAX_NEW},
      {"commit",			T_COMMIT,	SYNTAX_OLD | SYNTAX_NEW},
      {""}, {""},
      {"true",			T_TRUE,		SYNTAX_OLD | SYNTAX_NEW | SYNTAX_PROPERTY},
      {""}, {""},
      {"do", 			T_DO,		SYNTAX_NEW},
      {"and",			T_KW_AND,	SYNTAX_OLD | SYNTAX_NEW | SYNTAX_PROPERTY},
      {"init",			T_INIT,		SYNTAX_OLD | SYNTAX_NEW},
      {"false",			T_FALSE,	SYNTAX_OLD | SYNTAX_NEW | SYNTAX_PROPERTY},
      {""},
      {"if", 			T_IF,		SYNTAX_NEW},
      {"before_update",		T_BEFORE,	SYNTAX_GUIDING},
      {"case", 			T_CASE,		SYNTAX_NEW},
      {""}, {""}, {""},
      {"continue", 		T_CONTINUE,	SYNTAX_NEW},
      {"else", 			T_ELSE,		SYNTAX_NEW},
      {"while",			T_WHILE,	SYNTAX_NEW},
      {"assign",			T_ASSIGN,	SYNTAX_OLD | SYNTAX_NEW},
      {""},
      {"for",			T_FOR,		SYNTAX_NEW},
      {""},
      {"break",			T_BREAK,	SYNTAX_NEW},
      {""}, {""},
      {"deadlock",		T_DEADLOCK,	SYNTAX_PROPERTY},
      {""}, {""},
      {"return", 		T_RETURN,	SYNTAX_NEW},
      {"after_update",		T_AFTER,	SYNTAX_GUIDING},
      {""},
      {"rate",			T_RATE,		SYNTAX_GUIDING},
      {"imply",			T_KW_IMPLY,	SYNTAX_OLD | SYNTAX_NEW | SYNTAX_PROPERTY},
      {""},
      {"or",			T_KW_OR,	SYNTAX_OLD | SYNTAX_NEW | SYNTAX_PROPERTY},
      {""}, {""},
      {"trans",			T_TRANS,	SYNTAX_OLD | SYNTAX_NEW},
      {"struct",			T_STRUCT,	SYNTAX_NEW},
      {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {"sync",			T_SYNC,		SYNTAX_OLD | SYNTAX_NEW},
      {""}, {""},
      {"process",		T_PROCESS,	SYNTAX_OLD | SYNTAX_NEW},
      {""}, {""},
      {"state",			T_STATE,	SYNTAX_OLD | SYNTAX_NEW},
      {"system",			T_SYSTEM,	SYNTAX_OLD | SYNTAX_NEW},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {"switch", 		T_SWITCH,	SYNTAX_NEW}
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
