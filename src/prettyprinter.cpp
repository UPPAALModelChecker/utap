// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2002-2003 Uppsala University and Aalborg University.
   
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

#include <stack>
#include <sstream>

#include "utap/prettyprinter.h"

using namespace UTAP;
using namespace UTAP::Constants;

using std::stack;
using std::string;
using std::ostream;
using std::endl;
using std::ostringstream;

static const char *const prefix_label[] = 
{
    "", "const ", "urgent ", "", "broadcast ", "", "urgent broadcast ", "",
    "meta "
};

void PrettyPrinter::indent() 
{
    for (uint32_t i = 0; i < level; i++) 
    {
	*o.top() << "    ";
    }
}

void PrettyPrinter::indent(string &s) 
{
    for (uint32_t i = 0; i < level; i++)
    {
	s += "    ";
    }
}

PrettyPrinter::PrettyPrinter(ostream &stream) 
{
    o.push(&stream);
    
    first = true;
    level = 0;
    guard = sync = update = -1;
}

void PrettyPrinter::setErrorHandler(ErrorHandler *)
{

}

void PrettyPrinter::setPosition(const position_t &)
{

}
    
bool PrettyPrinter::isType(const char *id) 
{
    return strcmp(id, "int") == 0
	|| strcmp(id, "clock") == 0
	|| strcmp(id, "chan") == 0
	|| strcmp(id, "bool") == 0
	|| strcmp(id, "void") == 0;
}

void PrettyPrinter::typeName(int32_t prefix, const char *type, int range) 
{
    string res;
    
    res += prefix_label[prefix];
    res += type;
    
    if (range) 
    {
	res += '[';
	while (range--) 
	{
	    res += st.back();
	    if (range)
		res += ',';
	}
	res += ']';
    }
    
    st.push_back(res);
}

void PrettyPrinter::declVar(const char *id, uint32_t dim, bool init) 
{
    stack<string> array;
    string i;
    
    if (init) 
    {
	i = st.back();
	st.pop_back();
    }
    
    for (uint32_t i = 0; i < dim; i++) 
    {
	array.push(st.back());
	st.pop_back();
    }
    
    if (first) 
    {
	first = false;
	indent();
	*o.top() << st.back() << ' ' << id;
	st.pop_back();
    }
    else 
    {
	*o.top() << ", " << id;
    }
    
    while (!array.empty()) 
    {
	*o.top() << '[' << array.top() << ']';
	array.pop();
    }
    
    if (init) 
    {
	*o.top() << " = " << i;
    }
}

void PrettyPrinter::declVarEnd() 
{
    if (!first) 
    {
	*o.top() << ';' << endl;
	first = true;
    }
}

void PrettyPrinter::declInitialiserList(uint32_t num) 
{
    string s = st.back();
    st.pop_back();
    while (--num) 
    {
	s = st.back() + ", " + s;
	st.pop_back();
    }
    st.push_back("{ " + s + " }");
}

void PrettyPrinter::declFieldInit(const char* name) 
{
    if (name) 
    {
	st.back() = string(name) + ": " + st.back();
    }
}

void PrettyPrinter::declParameter(const char* name, bool reference, uint32_t dim) 
{
    if (dim) 
    {
	throw TypeException("Array parameters are not supported");
    }
    
    if (!param.empty())
    {
	param += ", ";
    }
    param += st.back() + (reference ? " &" : " ") + name;
}

void PrettyPrinter::declParameterEnd() 
{
    st.pop_back();
}

void PrettyPrinter::declFuncBegin(const char* name, uint32_t n) 
{
    *o.top() << st.back() << " " << name << "(" << param << ")" << endl;
    param = "";
    level++;
}

void PrettyPrinter::declFuncEnd() 
{
    level--;
}

void PrettyPrinter::blockBegin()  
{
    level--;
    indent();
    *o.top() << "{" << endl;    
    level++;
}

void PrettyPrinter::blockEnd()  
{
    level--;  // The level delimiters are indented one level less
    indent();
    level++;
    *o.top() << "}" << endl;
}

void PrettyPrinter::emptyStatement() 
{
    indent();
    *o.top() << ';' << endl;
}

void PrettyPrinter::forBegin()  
{
    level++;
    o.push(new ostringstream());
}
  
void PrettyPrinter::forEnd()  // 3 expr, 1 stat
{
    string expr3 = st.back(); st.pop_back();
    string expr2 = st.back(); st.pop_back();
    string expr1 = st.back(); st.pop_back();
    ostringstream *s = (ostringstream*)o.top();
    o.pop();
    
    level--;
    indent();
    *s << '\0';
    *o.top() << "for ( " << expr1 << "; " << expr2 << "; "
	     << expr3 << ")" << endl
	     << s->str() << endl;
    delete s;
}
  
void PrettyPrinter::whileBegin()
{
    level++;
    o.push(new ostringstream());
}
  
void PrettyPrinter::whileEnd()  // 1 expr, 1 stat
{ 
    string expr = st.back(); st.pop_back();
    ostringstream *s = (ostringstream*)o.top();
    o.pop();
    
    level--;
    indent();
    
    *s << '\0';
    *o.top() << "while (" << expr << ")" << endl
	     << s->str() << endl;
    delete s;
}

void PrettyPrinter::doWhileBegin()  
{

}

void PrettyPrinter::doWhileEnd()  
{

}

void PrettyPrinter::ifBegin() 
{
    level++;
    o.push(new ostringstream());
}

void PrettyPrinter::ifElse() 
{
    o.push(new ostringstream());
}

void PrettyPrinter::ifEnd(bool hasElse)  // 1 expr, n statements 
{ 
    ostringstream *t, *e = NULL;
    if (hasElse) 
    {
	e = (ostringstream*)o.top();
	o.pop();
    }
    t = (ostringstream*)o.top();
    o.pop();
    
    indent();
    *t << '\0';
    *e << '\0';
    *o.top() << "if (" << st.back() << ")" << endl
	     << t->str() << endl;
    delete t;
    if (hasElse) 
    {
	indent();
	*o.top() << "else" << endl
		 << e->str() << endl;
	delete e;
    }
}

void PrettyPrinter::breakStatement() 
{
    indent();
    *o.top() << "break;" << endl;
}

void PrettyPrinter::continueStatement() 
{
    indent();
    *o.top() << "continue;" << endl;
}

void PrettyPrinter::exprStatement() 
{
    indent();
    *o.top() << st.back() << ';' << endl;
    st.pop_back();
}

void PrettyPrinter::returnStatement(bool hasValue) 
{
    string f;
    indent(f);
    
    if (hasValue) 
    {
	f += "return " + st.back() + ";\n";
	st.pop_back();
    }
    else 
    {
	f += "return;\n";
    }
    st.push_back(f);
}

void PrettyPrinter::procBegin(const char *id, uint32_t n) 
{
    *o.top() << "process " << (id ? id : "") << '(' << param << ")" << endl
	     << "{" << endl;
    param = "";
    
    level += 1;
}

void PrettyPrinter::procState(const char *id, bool hasInvariant) 
{
    if (first) 
    {
	first = false;
	indent();
	*o.top() << "state\n";
    }
    else 
    {
	*o.top() << ",\n";
    }
    
    level++;
    indent();
    level--;
    
    *o.top() << id;
    if (hasInvariant) 
    {
	*o.top() << '{' << st.back() << '}';
	st.pop_back();
    }
}

void PrettyPrinter::procStateUrgent(const char *id) 
{
    if (urgent.empty()) 
    {
	urgent = id;
    }
    else 
    {
	urgent += ", ";
	urgent += id;
    }
}

void PrettyPrinter::procStateCommit(const char *id) 
{
    if (committed.empty()) 
    {
	committed = id;
    }
    else 
    {
	committed += ", ";
	committed += id;
    }
}

void PrettyPrinter::procStateInit(const char *id) 
{
    first = true;
    *o.top() << ";" << endl; // end of states
    
    if (!committed.empty()) 
    {
	indent();
	*o.top() << "commit " << committed << ';' << endl;
	committed = "";
    }
    
    if (!urgent.empty()) 
    {
	indent();
	*o.top() << "urgent " << urgent << ';' << endl;
	urgent = "";
    }
    
    indent();
    *o.top() << "init " << id << ';' << endl;
}

void PrettyPrinter::procGuard() 
{
    guard = st.size();
}

void PrettyPrinter::procSync(synchronisation_t type) 
{
    switch (type) 
    {
    case SYNC_QUE:
	st.back() += '?';
	break;
    case SYNC_BANG:
	st.back() += '!';
	break;
    }
    sync = st.size();
}

void PrettyPrinter::procUpdate() 
{
    update = st.size();
}

void PrettyPrinter::procEdge(const char *source, const char *target) 
{
    if (first)
    {
	// this is the first transition
	first = false;
	
	indent();
	*o.top() << "trans" << endl;
	
	level++;
    } 
    else 
    { 
	*o.top() << ',' << endl;
    }
    
    indent();
    *o.top() << source << " -> " << target << " {" << endl;
    
    level++;
    
    if (guard != -1) 
    {
	string guard  = st[this->guard - 1];
	indent();
	*o.top() << "guard " << guard << ';' << endl;
    }
    
    if (sync != -1) 
    {
	string sync = st[this->sync - 1];
	indent();
	*o.top() << "sync " << sync << ';' << endl;
    }
    
    if (update != -1) 
    {
	string assign = st[this->update - 1];
	indent();
	*o.top() << "assign " << assign << ';' << endl;
    }
    
    level--;
    
    if (guard != -1) st.pop_back(); 
    if (sync != -1) st.pop_back();
    if (update != -1) st.pop_back(); 
    
    this->update = this->sync = this->guard = -1;
    
    indent();
    *o.top() << '}';
}

void PrettyPrinter::procEnd() 
{
    if (!first) 
    {
	*o.top() << ';' << endl;
	level--;
	first = true;
    }
    level--;
    *o.top() << '}' << endl << endl;
}

void PrettyPrinter::exprId(const char *id) 
{
    st.push_back(string());
    st.back() = id;
}

void PrettyPrinter::exprNat(int32_t n) 
{
    char s[20];
    snprintf(s, 20, "%d", n);
    st.push_back(string());
    st.back() += s;
}

void PrettyPrinter::exprTrue() 
{
    st.push_back(string());
    st.back() = "true";
}

void PrettyPrinter::exprFalse() 
{
    st.push_back(string());
    st.back() = "false";
}

void PrettyPrinter::exprCallBegin(const char *name) 
{
    char s[64];
    snprintf(s, 20, "%s(", name);
    st.push_back(s);
}

void PrettyPrinter::exprCallEnd(uint32_t n) 
{
    string s = ")";
    while (n--) 
    {
	s = st.back() + s;
	st.pop_back();
	if (n > 0)
	{
	    s = ", " + s;
	}
    }
    st.back() += s;
}

void PrettyPrinter::exprArg(uint32_t n) 
{
    // Don't do anything
}

void PrettyPrinter::exprArray() 
{
    string f = st.back();
    st.pop_back();
    st.back() += '[' + f + ']';
}

void PrettyPrinter::exprPostIncrement() 
{
    st.back() += "++";
}

void PrettyPrinter::exprPreIncrement() 
{
    st.back() = "++" + st.back();
}

void PrettyPrinter::exprPostDecrement() 
{
    st.back() += "--";
}

void PrettyPrinter::exprPreDecrement() 
{
    st.back() = "--" + st.back();
}

void PrettyPrinter::exprAssignment(kind_t op) 
{
    string rhs = st.back(); st.pop_back();
    string lhs = st.back(); st.pop_back();
    
    st.push_back(string());
    switch (op) 
    {
    case ASSIGN:
	st.back() = '(' + lhs + " = " + rhs + ')';
	break;
    case ASSPLUS:
	st.back() = '(' + lhs + " += " + rhs + ')';
	break;
    case ASSMINUS:
	st.back() = '(' + lhs + " -= " + rhs + ')';
	break;
    case ASSMULT:
	st.back() = '(' + lhs + " *= " + rhs + ')';
	break;
    case ASSDIV:
	st.back() = '(' + lhs + " /= " + rhs + ')';
	break;
    case ASSMOD:
	st.back() = '(' + lhs + " %= " + rhs + ')';
	break;
    case ASSOR:
	st.back() = '(' + lhs + " |= " + rhs + ')';
	break;
    case ASSAND:
	st.back() = '(' + lhs + " &= " + rhs + ')';
	break;
    case ASSXOR:
	st.back() = '(' + lhs + " ^= " + rhs + ')';
	break;
    case ASSLSHIFT:
	st.back() = '(' + lhs + " <<= " + rhs + ')';
	break;
    case ASSRSHIFT:
	st.back() = '(' + lhs + " >>= " + rhs + ')';
	break;
    default:
	throw TypeException("Invalid assignment operator");
    }
}

void PrettyPrinter::exprUnary(kind_t op) 
{
    string exp = st.back(); st.pop_back();

    st.push_back(string());
    switch (op) 
    {
    case MINUS:
	st.back() = '-' + exp;
	break;
    case NOT:
	st.back() = '!' + exp;
	break;
    case PLUS:
	st.back() = '+' + exp;
	break;
    case RATE:
	st.back() = exp + '\'';
	break;
    default:
	throw TypeException("Invalid operator");
    }
}

void PrettyPrinter::exprBinary(kind_t op) 
{
    string exp2 = st.back(); st.pop_back();
    string exp1 = st.back(); st.pop_back();
    
    st.push_back(string());
    switch (op) 
    {
    case PLUS:
	st.back() = '(' + exp1 + " + " + exp2 + ')';
	break;
    case MINUS:
	st.back() = '(' + exp1 + " - " + exp2 + ')';
	break;
    case MULT:
	st.back() = '(' + exp1 + " * " + exp2 + ')';
	break;
    case DIV:
	st.back() = '(' + exp1 + " / " + exp2 + ')';
	break;
    case MOD:
	st.back() = '(' + exp1 + " % " + exp2 + ')';
	break;
    case MIN:
	st.back() = '(' + exp1 + " <? " + exp2 + ')';
	break;
    case MAX:
	st.back() = '(' + exp1 + " >? " + exp2 + ')';
	break;
    case LT:
	st.back() = '(' + exp1 + " < " + exp2 + ')';
	break;      
    case LE:
	st.back() = '(' + exp1 + " <= " + exp2 + ')';
	break;      
    case EQ:
	st.back() = '(' + exp1 + " == " + exp2 + ')';
	break;      
    case NEQ:
	st.back() = '(' + exp1 + " != " + exp2 + ')';
	break;      
    case GE:
	st.back() = '(' + exp1 + " >= " + exp2 + ')';
	break;      
    case GT:
	st.back() = '(' + exp1 + " > " + exp2 + ')';
	break;
    case AND:
	st.back() = '(' + exp1 + " && " + exp2 + ')';
	break;
    case OR:
	st.back() = '(' + exp1 + " || " + exp2 + ')';
	break;
    case BIT_AND:
	st.back() = '(' + exp1 + " & " + exp2 + ')';
	break;
    case BIT_OR:      
	st.back() = '(' + exp1 + " | " + exp2 + ')';
	break;
    case BIT_XOR:
	st.back() = '(' + exp1 + " ^ " + exp2 + ')';
	break;
    case BIT_LSHIFT:
	st.back() = '(' + exp1 + " << " + exp2 + ')';
	break;
    case BIT_RSHIFT:
	st.back() = '(' + exp1 + " >> " + exp2 + ')';
	break;
    default:
	throw TypeException("Invalid operator");
    }
}

void PrettyPrinter::exprInlineIf() 
{  
    string expr3 = st.back(); st.pop_back();
    string expr2 = st.back(); st.pop_back();
    string expr1 = st.back(); st.pop_back();

    st.push_back(string());
    st.back() = expr1 + " ? " + expr2 + " : " + expr3;
}

void PrettyPrinter::exprComma() 
{
    string expr2 = st.back(); st.pop_back();
    string expr1 = st.back(); st.pop_back();

    st.push_back(string());
    st.back() = expr1 + ", " + expr2;
}

void PrettyPrinter::exprDot(const char *) 
{
    throw TypeException("Invalid expression");
}

void PrettyPrinter::exprDeadlock() 
{
    throw TypeException("Invalid expression");	
}

void PrettyPrinter::beforeUpdate()
{
    *o.top() << "{" << endl;
    level++;
    indent();
    level--;
    *o.top() << st.back() << endl;
    *o.top() << "}" << endl;	    
}

void PrettyPrinter::afterUpdate()
{
    *o.top() << "{" << endl;
    level++;
    indent();
    level--;
    *o.top() << st.back() << endl;
    *o.top() << "}" << endl;	    
}

void PrettyPrinter::instantiationBegin(const char *id, const char *templ) 
{
    // Ignore
}

void PrettyPrinter::instantiationEnd(const char* id, const char* templ, uint32_t n)
{
    stack<string> s;
    while (n--) 
    {
	s.push(st.back());
	st.pop_back();
    }

    *o.top() << id << " = " << templ << '(';
    while (!s.empty()) 
    {
	*o.top() << s.top();
	s.pop();
	if (!s.empty())
	{
	    *o.top() << ", ";
	}
    }
    *o.top() << ");" << endl;
}

void PrettyPrinter::process(const char *id) 
{
    if (first) 
    {
	*o.top() << "system " << id;
	first = false;
    }
    else 
    {
	*o.top() << ", " << id;
    }
}

void PrettyPrinter::done() 
{
    *o.top() << ';' << endl;
}
