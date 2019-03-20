/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2002 Uppsala University and Aalborg University.
   
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

using std::ostream;
  
#define YY_DECL int lexer_flex(void)

/**
 * Location tracking inside scanner, taken from 
 * http://www.lrde.epita.fr/people/akim/compil/gnuprog2/Advanced-Use-of-Flex.html
 */

#define YY_USER_INIT yylloc.reset();
#define YY_USER_ACTION yylloc.step(); yylloc.last_column+=yyleng; 
#define YY_FATAL_ERROR(msg) { throw TypeException(msg); }

%}

alpha	[a-zA-Z_]
num	[0-9]+
idchr	[a-zA-Z0-9_$#]

%x comment

%%

<comment>{
  \n           { yylloc.lines(1); }
  "*/"         { BEGIN(INITIAL); }
  "//"[^\n]*   /* Single line comments take precedence over multilines */;
  <<EOF>>      { BEGIN(INITIAL); yyerror("Unclosed comment."); return 0; }
  .            /* ignore (multiline comments)*/
}

"\\"[\t ]*"\n"  { /* Use \ as continuation character */ 
                  yylloc.lines(1); 
                } 

"//"[^\n]*      /* ignore (singleline comment)*/;

[ \t]+		

"/*"            { BEGIN(comment); }

\n+		{
                  yylloc.lines(yyleng); 
		  if (syntax == SYNTAX_PROPERTY)
		    return '\n';
                }

(\r\n)+         {
                  yylloc.lines(yyleng / 2);
		  if (syntax == SYNTAX_PROPERTY)
		    return '\n';
                }

"."		{ return '.'; }
","		{ return ','; }
";"		{ return ';'; }
":"             { return ':'; }
"{"		{ return '{'; }
"}"		{ return '}'; }
"["		{ return '['; }
"]"		{ return ']'; }
"("             { return '('; }
")"             { return ')'; }
"?"		{ return '?'; }
"'"		{ return '\''; }
"!"		{ return T_EXCLAM; }

"->"		{ return T_ARROW; }
"-u->"		{ return T_UNCONTROL_ARROW; }

"="		{ return T_ASSIGNMENT; }
":="		{ return T_ASSIGNMENT; }
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
"<?"		{ return T_MIN; }
">?"		{ return T_MAX; }

"+"		{ return T_PLUS; }
"-"		{ return T_MINUS; }
"*"		{ return T_MULT; }
"/"		{ return T_DIV; }
"%"             { return T_MOD; }
"|"             { return T_OR; }
"&"             { return '&'; }
"^"             { return T_XOR; }
"<<"            { return T_LSHIFT; }
">>"            { return T_RSHIFT; }
"||"            { return T_BOOL_OR; }
"&&"            { return T_BOOL_AND; }

"<="		{ return T_LEQ; }
">="		{ return T_GEQ; }
"=<"		{ if (syntax & SYNTAX_OLD)
                  {
                      return T_LEQ;
                  }
                  utap_error("Unknown symbol");
                  return T_ERROR;
                }
"=>"		{ if (syntax & SYNTAX_OLD)
                  {
                      return T_GEQ;
                  }
                  utap_error("Unknown symbol");
                  return T_ERROR;
                }
"<"		{ return T_LT; }
">"		{ return T_GT; }
"=="		{ return T_EQ; }
"!="		{ return T_NEQ; }

"++"            { return T_INCREMENT; }
"--"            { return T_DECREMENT; }

"A<>"           { return T_AF; }
"A[]"           { return T_AG; }
"E<>"           { return T_EF; }
"E[]"           { return T_EG; }
"-->"           { return T_LEADSTO; }

{alpha}{idchr}* {
/*  		if (strlen(decl_text) >= MaxIdLen ) */
/*  			declError << "Identifier too long. Only " << MaxIdLen  */
/*  				 << " characters are significant.\n"; */
		  const Keyword *keyword
		    = Keywords::in_word_set(utap_text, strlen(utap_text));
		  if (keyword != NULL && (syntax & keyword->syntax)) {
		    if (keyword->token == T_CONST && (syntax & SYNTAX_OLD))
		      return T_OLDCONST;
		    return keyword->token;	  
	          } else if (ch->isType(utap_text)) {
		    strncpy(utap_lval.string, utap_text, MAXLEN);
		    utap_lval.string[MAXLEN - 1] = '\0';
		    return T_TYPENAME;
                  } else {
		    if (keyword != NULL && !(syntax & keyword->syntax)) {
		      utap_lval.string[0] = '_';
		      strncpy(utap_lval.string + 1, utap_text, MAXLEN - 1);
		      utap_lval.string[MAXLEN - 1] = '\0';		      
		    } else {
		      strncpy(utap_lval.string, utap_text, MAXLEN);
		      utap_lval.string[MAXLEN - 1] = '\0';
		    }
		    return T_ID;
		  }
                }

{num}		{ 
                  utap_lval.number = atoi(utap_text); 
                  return T_NAT; 
                }

.               { 
		  utap_error("Unknown symbol");
                  return T_ERROR; 
                }

<<EOF>>		{ return 0; }

%%

ostream &operator <<(ostream &out, const YYLTYPE &l) 
{
  if (l.first_line != l.last_line)                      
    out << l.first_line << "." << l.first_column << "-" 
	<< l.last_line << "." << (l.last_column-1);
  else if (l.first_column < l.last_column-1)
    out << l.first_line << "." << l.first_column << "-" << (l.last_column-1);
  else                                                          
    out << l.first_line << "." << l.first_column;
  //  out << " (" << l.first_char << "-" << l.last_char << ")";
  return out;
};

int utap_wrap() {
  return 1;
}


