// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; -*-

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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stack>
#include <sstream>
#include <string>

#include "utap/builder.hh"
#include "utap/typechecker.hh"
#include "utap/systembuilder.hh"
#include "utap/rangechecker.hh"

#if defined(__MINGW32__) || defined(__CYGWIN32__) || !defined(HAVE_UNISTD_H) 
extern "C" {
    extern int getopt(int argc, char * const argv[], const char *optstring);
    extern char *optarg;
    extern int optind, opterr, optopt;
}
#endif

using UTAP::ParserBuilder;
using UTAP::TypeChecker;
using UTAP::TypeException;
using UTAP::TimedAutomataSystem;
using UTAP::ErrorHandler;
using UTAP::SystemBuilder;
using UTAP::RangeChecker;
using UTAP::position_t;
using std::vector;
using std::string;
using std::stack;
using std::ostream;
using std::ostringstream;
using std::endl;
using std::cout;
using std::cerr;

using namespace UTAP::Constants;

static const char *const prefix_label[] = {
    "", "const ", "urgent ", "", "broadcast ", "", "urgent broadcast ", ""
};

class PrettyPrinter : public ParserBuilder
{
private:
    vector<string> st;

    stack<ostream *> o;

    bool first;
    uint32_t level;

    void indent() {
	for (uint32_t i = 0; i < level; i++) 
	    *o.top() << "    ";
    }

    void indent(string &s) {
	for (uint32_t i = 0; i < level; i++)
	    s += "    ";
    }

    string urgent;
    string committed;

    int guard, sync, update;

public:
    PrettyPrinter(ostream &stream) {
	o.push(&stream);
    
	first = true;
	level = 0;
	guard = sync = update = -1;
    }

    virtual void setErrorHandler(ErrorHandler *) {}
    virtual void setPosition(const position_t &) {}
    
    virtual bool isType(const char *id) {
	return strcmp(id, "int") == 0
	    || strcmp(id, "clock") == 0
	    || strcmp(id, "chan") == 0;
    }

    virtual void declType(uint32_t prefix, const char *type, bool range) {
	string res;
	
	res += prefix_label[prefix];
	res += type;

	if (range) {
	    string r2 = st.back(); st.pop_back(); 
	    string r1 = st.back(); st.pop_back();
	    res += '[' + r1 + ',' + r2 + ']';
	}

	st.push_back(res);
    }

    virtual void declVar(const char *id, uint32_t dim, bool init) {
	stack<string> array;
	string i;
	
	if (init) {
	    i = st.back();
	    st.pop_back();
	}
    
	for (uint32_t i = 0; i < dim; i++) {
	    array.push(st.back());
	    st.pop_back();
	}

	if (first) {
	    first = false;
	    indent();
	    *o.top() << st.back() << ' ' << id;
	    st.pop_back();
	} else {
	    *o.top() << ", " << id;
	}
    
	while (!array.empty()) {
	    *o.top() << '[' << array.top() << ']';
	    array.pop();
	}
	
	if (init) {
	    *o.top() << " = " << i;
	}
    }

    virtual void declVarEnd() {
	*o.top() << ';' << endl;
	first = true;
    }
  
    virtual void declStruct(uint32_t prefix, uint32_t n) {}
    virtual void declField(const char* name, uint32_t dim) {}
    virtual void declFieldEnd() {}
    
    virtual void declTypeDef(const char* name, uint32_t dim) {}
    virtual void declTypeDefEnd() {}

    virtual void declInitialiserList(uint32_t num) {
	string s = st.back();
	st.pop_back();
	while (--num) {
	    s = st.back() + ", " + s;
	    st.pop_back();
	}
	st.push_back("{ " + s + " }");
    }

    virtual void declFieldInit(const char* name) {
	if (name) 
	    st.back() = string(name) + ": " + st.back();
    }

private:    
    string param;

public:
    virtual void declParameter(const char* name, bool reference, uint32_t dim) {
	if (dim) 
	    throw TypeException("Array parameters are not supported");

	if (!param.empty())
	    param += ", ";
	param += st.back() + (reference ? " &" : " ") + name;
    }

    virtual void declParameterEnd() {
  	st.pop_back();
    }

    virtual void declFuncBegin(const char* name, uint32_t n) {
	*o.top() << st.back() << " " << name << "(" << param << ")" << endl;
	param = "";
	level++;
    }

    virtual void declFuncEnd() {
	level--;
    }

    virtual void blockBegin()  {
	level--;
	indent();
	*o.top() << "{" << endl;    
	level++;
    }

    virtual void blockEnd()  {
	level--;  // The level delimiters are indented one level less
	indent();
	level++;
	*o.top() << "}" << endl;
    }
  
    virtual void emptyStatement() {
	indent();
	*o.top() << ';' << endl;
    }
  
    virtual void forBegin() {
	level++;
	o.push(new ostringstream());
    }
  
    virtual void forEnd() { // 3 expr, 1 stat
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
  
    virtual void whileBegin()
	{
	    level++;
	    o.push(new ostringstream());
	}
  
    virtual void whileEnd()  { // 1 expr, 1 stat
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
  
    virtual void doWhileBegin()  {}
    virtual void doWhileEnd()  {} // 1 stat, 1 expr

    virtual void ifBegin() {
	level++;
	o.push(new ostringstream());
    }

    virtual void ifElse() {
	o.push(new ostringstream());
    }
  
    virtual void ifEnd(bool hasElse)  { // 1 expr, n statements 
	ostringstream *t, *e = NULL;
	if (hasElse) {
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
	if (hasElse) {
	    indent();
	    *o.top() << "else" << endl
		     << e->str() << endl;
	    delete e;
	}
    }
  
    virtual void breakStatement() {
	indent();
	*o.top() << "break;" << endl;
    }
  
    virtual void continueStatement() {
	indent();
	*o.top() << "continue;" << endl;
    }
  
    virtual void switchBegin()  {}
    virtual void switchEnd()  {} // 1 expr, 1+ case/default
    virtual void caseBegin()  {}
    virtual void caseEnd()  {}  // 1 expr, 0+ stat
    virtual void defaultBegin()  {}
    virtual void defaultEnd()  {} // 0+ statements

    virtual void exprStatement() {
	indent();
	*o.top() << st.back() << ';' << endl;
	st.pop_back();
    }

    virtual void returnStatement(bool hasValue) {
	string f;
	indent(f);
    
	if (hasValue) {
	    f += "return " + st.back() + ";\n";
	    st.pop_back();
	} else {
	    f += "return;\n";
	}
	st.push_back(f);
    }
  
    virtual void procBegin(const char *id, uint32_t n) {
	*o.top() << "process " << (id ? id : "") << '(' << param << ")" << endl
		 << "{" << endl;
	param = "";
	
	level += 1;
    }

    virtual void procState(const char *id, bool hasInvariant) {
	if (first) {
	    first = false;
	    indent();
	    *o.top() << "state\n";
	} else {
	    *o.top() << ",\n";
	}

	level++;
	indent();
	level--;

	*o.top() << id;
	if (hasInvariant) {
	    *o.top() << '{' << st.back() << '}';
	    st.pop_back();
	}
    }

    virtual void procStateUrgent(const char *id) {
	if (urgent.empty()) {
	    urgent = id;
	} else {
	    urgent += ", ";
	    urgent += id;
	}
    }

    virtual void procStateCommit(const char *id) {
  	if (committed.empty()) {
  	    committed = id;
  	} else {
  	    committed += ", ";
	    committed += id;
  	}
    }

    virtual void procStateInit(const char *id) {
	first = true;
	*o.top() << ";" << endl; // end of states
    
  	if (!committed.empty()) {
  	    indent();
  	    *o.top() << "commit " << committed << ';' << endl;
	    committed = "";
  	}

	if (!urgent.empty()) {
	    indent();
	    *o.top() << "urgent " << urgent << ';' << endl;
	    urgent = "";
	}

	indent();
	*o.top() << "init " << id << ';' << endl;
    }

    
    virtual void procGuard() {
	guard = st.size();
    }
    
    virtual void procSync(synchronisation_t type) {
	switch (type) {
	case SYNC_QUE:
	    st.back() += '?';
	    break;
	case SYNC_BANG:
	    st.back() += '!';
	    break;
	}
	sync = st.size();
    }

    virtual void procUpdate() {
	update = st.size();
    }

    virtual void procTransition(const char *source, const char *target) {
	if (first) { // this is the first transition
	    first = false;
      
	    indent();
	    *o.top() << "trans" << endl;

	    level++;
	} else { 
	    *o.top() << ',' << endl;
	}

	indent();
	*o.top() << source << " -> " << target << " {" << endl;

	level++;
      
	if (guard != -1) {
	    string guard  = st[this->guard - 1];
	    indent();
	    *o.top() << "guard " << guard << ';' << endl;
	}

	if (sync != -1) {
	    string sync = st[this->sync - 1];
	    indent();
	    *o.top() << "sync " << sync << ';' << endl;
	}

	if (update != -1) {
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

    virtual void procEnd() {
	if (!first) {
	    *o.top() << ';' << endl;
	    level--;
	    first = true;
	}
	level--;
	*o.top() << '}' << endl << endl;
    }

    virtual void exprId(const char *id) {
	st.push_back(string());
	st.back() = id;
    }
  
    virtual void exprNat(int32_t n) {
	char s[20];
	snprintf(s, 20, "%d", n);
	st.push_back(string());
	st.back() += s;
    }
  
    virtual void exprTrue() {
	st.push_back(string());
	st.back() = "true";
    }

    virtual void exprFalse() {
	st.push_back(string());
	st.back() = "false";
    }

    virtual void exprCallBegin(const char *) {
	throw TypeException("Function calls are not allowed");
    }

    virtual void exprCallEnd(uint32_t n) {
	throw TypeException("Function calls are not allowed");
    }

    virtual void exprArg(uint32_t n) {
	// Don't do anything
    }

    virtual void exprArray() {
	string f = st.back();
	st.pop_back();
	st.back() += '[' + f + ']';
    }

    virtual void exprPostIncrement() {
	st.back() += "++";
    }

    virtual void exprPreIncrement() {
	st.back() = "++" + st.back();
    }

    virtual void exprPostDecrement() {
	st.back() += "--";
    }

    virtual void exprPreDecrement() {
	st.back() = "--" + st.back();
    }

    virtual void exprAssignment(kind_t op) {
	string rhs = st.back(); st.pop_back();
	string lhs = st.back(); st.pop_back();

	st.push_back(string());
	switch (op) {
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

    virtual void exprUnary(kind_t op) {
	string exp = st.back(); st.pop_back();

	st.push_back(string());
	switch (op) {
	case MINUS:
	    st.back() = '-' + exp;
	    break;
	case NOT:
	    st.back() = '!' + exp;
	    break;
	default:
	    throw TypeException("Invalid operator");
	}
    }

    virtual void exprBinary(kind_t op) {
	string exp2 = st.back(); st.pop_back();
	string exp1 = st.back(); st.pop_back();
    
	st.push_back(string());
	switch (op) {
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

    virtual void exprInlineIf() {  
	string expr3 = st.back(); st.pop_back();
	string expr2 = st.back(); st.pop_back();
	string expr1 = st.back(); st.pop_back();

	st.push_back(string());
	st.back() = expr1 + " ? " + expr2 + " : " + expr3;
    }

    virtual void exprComma() {
	string expr2 = st.back(); st.pop_back();
	string expr1 = st.back(); st.pop_back();

	st.push_back(string());
	st.back() = expr1 + ", " + expr2;
    }

    virtual void exprDot(const char *) {
	throw TypeException("Invalid expression");
    }

    virtual void exprDeadlock() {
	throw TypeException("Invalid expression");	
    }

    virtual void instantiationBegin(const char *id, const char *templ) {
	// Ignore
    }
    
    virtual void instantiationEnd(const char* id, const char* templ, uint32_t n) {
	stack<string> s;
	while (n--) {
	    s.push(st.back());
	    st.pop_back();
	}

	*o.top() << id << " = " << templ << '(';
	while (!s.empty()) {
	    *o.top() << s.top();
	    s.pop();
	    if (!s.empty())
		*o.top() << ", ";
	}
	*o.top() << ");" << endl;
    }

    virtual void process(const char *id) {
	if (first) {
	    *o.top() << "system " << id;
	    first = false;
	} else {
	    *o.top() << ", " << id;
	}
    }

    virtual void done() {
	*o.top() << ';' << endl;
    }

    virtual void beforeUpdate() {

    }

    virtual void afterUpdate() {

    }
};

/**
 * Test for pretty printer
 */
int main(int argc, char *argv[])
{
    bool old = false;
    bool xml = false;
    bool check = false;
    char c;
  
    while ((c = getopt(argc,argv,"bxts")) != -1) {
	switch(c) {
	case 'b':
	    old = true;
	    break;
	case 'x':
	    xml = true;
	    break;
	case 't':
	    check = true;
	    break;
	}
    }

    TimedAutomataSystem system;

    ParserBuilder *b = NULL;
    if (check) {
  	b = new SystemBuilder(&system);
    } else {
  	b = new PrettyPrinter(cout);
    }
    
    ErrorHandler errorHandler;
    try {
  	if (xml) {
  	    if (argc - optind != 1)
  		exit(1);
  	    parseXMLFile(argv[optind], b, &errorHandler, !old);
  	} else {
  	    parseXTA(stdin, b, &errorHandler, !old);
  	}
    } catch (TypeException e) {
  	cerr << e.what() << endl;
    }

    if (check) {
    	TypeChecker tc(&errorHandler);
    	system.accept(tc);
    }
    
    vector<ErrorHandler::error_t>::const_iterator it;
    const vector<ErrorHandler::error_t> &errors = errorHandler.getErrors();
    const vector<ErrorHandler::error_t> &warns = errorHandler.getWarnings();

    for (it = errors.begin(); it != errors.end(); it++)
   	cerr << *it << endl;
    for (it = warns.begin(); it != warns.end(); it++)
   	cerr << *it << endl;

    delete b;

    return 0;
}













