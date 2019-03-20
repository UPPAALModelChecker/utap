/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2002-2017 Uppsala University and Aalborg University.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public License
   as published by the Free Software Foundation; either version 2.1 of
   the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
   USA
*/

%option nodefault
%option nounput
%option never-interactive
%{

#include <iostream>
#include "keywords.cc"
#include "libparser.h"

using std::ostream;

#define YY_DECL int lexer_flex(void)

uint32_t PositionTracker::line;
uint32_t PositionTracker::offset;
uint32_t PositionTracker::position = 0;
std::string PositionTracker::path;

namespace UTAP
{
  void PositionTracker::setPath(UTAP::ParserBuilder *parser, std::string s) {

    // Incrementing the position by one avoids the problem where the
    // end-position happens to bleed into a path. E.g. the range 5-10
    // contains 5 character (at positions 5, 6, 7, 8 and 9), thus
    // position 10 could have a new path). An alternative would be to
    // subtract 1 before calling Positions::find().

    position++;
    line = 1;
    offset = 0;
    path = s;
    parser->addPosition(position, offset, line, path);
  }

  int PositionTracker::increment(UTAP::ParserBuilder *parser, int n) {
    parser->setPosition(position, position + n);
    position += n;
    offset += n;
    return position - n;
  }

  void PositionTracker::newline(UTAP::ParserBuilder *parser, int n) {
    line += n;
    parser->addPosition(position, offset, line, path);
  }
}

#define YY_USER_ACTION yylloc.start = PositionTracker::position; PositionTracker::increment(ch, yyleng); yylloc.end = PositionTracker::position;

//#define YY_FATAL_ERROR(msg) { throw TypeException(msg); } // unused

%}

alpha        [a-zA-Z_]
num          [0-9]+
idchr        [a-zA-Z0-9_$#]

%x comment

%%

<comment>{
  \n           { PositionTracker::newline(ch, 1); }
  "*/"         { BEGIN(INITIAL); }
  <<EOF>>      { BEGIN(INITIAL); yyerror("$Comment_not_closed"); return 0; }
  "EXPECT:"[^\t \n]* { ch->handleExpect(utap_text+7); }
  .            /* ignore (multiline comments)*/
}

"\\"[\t ]*"\n"  { /* Use \ as continuation character */
                  PositionTracker::newline(ch, 1);
                }

"//"[^\n]*      /* ignore (singleline comment)*/;

[ \t]+

"/*"            { BEGIN(comment); }

\n+        	{
                  PositionTracker::newline(ch, yyleng);
        	  if ((syntax & SYNTAX_PROPERTY) != 0)
        	    return '\n';
                }

(\r\n)+         {
                  PositionTracker::newline(ch, yyleng / 2);
        	  if ((syntax & SYNTAX_PROPERTY) != 0)
        	    return '\n';
                }

"."        	{ return '.'; }
","        	{ return ','; }
";"        	{ return ';'; }
":"             { return ':'; }
"{"        	{ return '{'; }
"}"        	{ return '}'; }
"["        	{ return '['; }
"]"        	{ return ']'; }
"("             { return '('; }
")"             { return ')'; }
"?"        	{ return '?'; }
"'"        	{ return '\''; }
"!"        	{ return T_EXCLAM; }
"\\"            { return '\\'; }

"->"        	{ return T_ARROW; }
"-u->"        	{ return T_UNCONTROL_ARROW; }

"="        	{ return T_ASSIGNMENT; }
":="        	{ return T_ASSIGNMENT; }
"+="            { return T_ASSPLUS; }
"-="            { return T_ASSMINUS; }
"*="            { return T_ASSMULT; }
"/="            { return T_ASSDIV; }
"%="            { return T_ASSMOD; }
"|="            { return T_ASSOR; }
"&="            { return T_ASSAND; }
"^="            { return T_ASSXOR; }
"<<="           { return T_ASSLSHIFT; }
">>="           { return T_ASSRSHIFT; }
"<?"        	{ return T_MIN; }
">?"        	{ return T_MAX; }

"+"        	{ return T_PLUS; }
"-"        	{ return T_MINUS; }
"*"        	{ return T_MULT; }
"/"        	{ return T_DIV; }
"%"             { return T_MOD; }
"|"             { return T_OR; }
"&"             { return '&'; }
"^"             { return T_XOR; }
"<<"            { return T_LSHIFT; }
">>"            { return T_RSHIFT; }
"||"            { return T_BOOL_OR; }
"&&"            { return T_BOOL_AND; }
"/\\"           { return T_MITL_AND;}
"\\/"           { return T_MITL_OR;}

"<="        	{ return T_LEQ; }
">="        	{ return T_GEQ; }
"=<"        	{ if (syntax & SYNTAX_OLD)
                  {
                      return T_LEQ;
                  }
                  utap_error("$Unknown_symbol");
                  return T_ERROR;
                }
"=>"        	{ if (syntax & SYNTAX_OLD)
                  {
                      return T_GEQ;
                  }
                  utap_error("$Unknown_symbol");
                  return T_ERROR;
                }
"<"        	{ return T_LT; }
">"        	{ return T_GT; }
"=="        	{ return T_EQ; }
"!="        	{ return T_NEQ; }

"++"            { return T_INCREMENT; }
"--"            { return T_DECREMENT; }

"A"             { return 'A'; }
"U"             { return 'U'; }
"R"             { return 'R'; }
"W"             { return 'W'; }
"E"             { return 'E'; }

"A<>"           { return T_AF; }
"A[]"           { return T_AG; }
"E<>"           { return T_EF; }
"E[]"           { return T_EG; }
"-->"           { return T_LEADSTO; }
"A[]+"          { return T_AG_PLUS; }
"E<>+"          { return T_EF_PLUS; }
"A[]*"          { return T_AG_MULT; }
"E<>*"          { return T_EF_MULT; }
"[]"            { return T_BOX; }
"<>"            { return T_DIAMOND; }
"#"             { return T_HASH; }

{alpha}{idchr}* {
        	  const Keyword *keyword
        	    = Keywords::in_word_set(utap_text, strlen(utap_text));
		  if (keyword != NULL)
		  {
		      int32_t s = keyword->syntax;
#ifndef ENABLE_TIGA
		      /* Remove all TIGA keywords if tiga is not enabled. */
		      if (s & SYNTAX_TIGA)
		      {
			  s = 0;
		      }
#endif
#ifndef ENABLE_PROB
		      /* Remove all PROB keywords if pro is not enabled. */
		      if (s & SYNTAX_PROB)
		      {
			  s = 0;
		      }
#endif
		      if (syntax & s)
		      {
			  if (keyword->token == T_CONST && (syntax & SYNTAX_OLD))
			  {
			      return T_OLDCONST;
			  }
			  return keyword->token;
		      }
		  }
                  if (strlen(utap_text) > MAXLEN-1)
                  {
                      /* Don't keep the cut of strncpy silent. */
                      utap_error(ID_TOO_LONG);
                  }
		  if (ch->isType(utap_text))
		  {
		      strncpy(utap_lval.string, utap_text, MAXLEN);
		      utap_lval.string[MAXLEN - 1] = '\0';
		      return T_TYPENAME;
                  }
		  else
		  {
        	      strncpy(utap_lval.string, utap_text, MAXLEN);
        	      utap_lval.string[MAXLEN - 1] = '\0';
		      return T_ID;
        	  }
                }

{num}        	{
                  // Skip 0s.
                  const char *s = utap_text;
                  while(*s && *s == '0') s++;
                  if (!*s) { // We've skipped everything.
                      utap_lval.number = 0;
                      return T_NAT;
                  }

                  // Special case for INT_MIN
                  if (strcmp("2147483648", s) == 0)
                  {
                      return T_POS_NEG_MAX;
                  }

                  // Detect overflow.
                  utap_lval.number = atoi(s);
                  char check[16];
                  snprintf(check,sizeof(check),"%d",utap_lval.number);
                  if (strcmp(check,s) != 0)
                  {
                      yyerror("$Overflow");
                      return T_ERROR;
                  }

                  // Oh, it worked.
                  return T_NAT;
                }

{num}("."{num})?([eE]("+"|"-")?{num})? {
                  // Todo: have some check.
                  utap_lval.floating = atof(utap_text);
                  return T_FLOATING;
                }


.               {
        	  utap_error("$Unknown_symbol");
                  return T_ERROR;
                }

<<EOF>>        	{ return 0; }

%%

int utap_wrap() {
  return 1;
}
