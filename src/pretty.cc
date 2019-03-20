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

using UTAP::ParserBuilder;
using UTAP::TypeChecker;
using UTAP::TypeException;
using UTAP::TimedAutomataSystem;
using UTAP::ErrorHandler;
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
    typedef struct  {
	string s;
    } Fragment;

    vector<Fragment> st;

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
    
    virtual bool isType(const char *id) {
	return strcmp(id, "int") == 0
	    || strcmp(id, "clock") == 0
	    || strcmp(id, "chan") == 0;
    }

    virtual void declType(uint32_t prefix, const char *type, bool range) {
	Fragment res;
	
	res.s += prefix_label[prefix];
	res.s += type;

	if (range) {
	    Fragment r2 = st.back(); st.pop_back(); 
	    Fragment r1 = st.back(); st.pop_back();
	    res.s += '[' + r1.s + ',' + r2.s + ']';
	}

	st.push_back(res);
    }

    virtual void declVar(const char *id, uint32_t dim, bool init) {
	stack<Fragment> array;
	Fragment i;
	
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
	    *o.top() << st.back().s << ' ' << id;
	    st.pop_back();
	} else {
	    *o.top() << ", " << id;
	}
    
	while (!array.empty()) {
	    *o.top() << '[' << array.top().s << ']';
	    array.pop();
	}
	
	if (init) {
	    *o.top() << " = " << i.s;
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
    virtual void declInitialiserList(uint32_t num) {}
    virtual void declFieldInit(const char* name) {}

private:    
    string param;

public:
    virtual void declParameter(const char* name, bool reference, uint32_t dim) {
	if (dim) 
	    throw TypeException("Array parameters are not supported");

	if (!param.empty())
	    param += ", ";
	param += st.back().s + (reference ? " &" : " ") + name;
    }

    virtual void declParameterEnd() {
  	st.pop_back();
    }

    virtual void declFuncBegin(const char* name, uint32_t n) {
	*o.top() << st.back().s << " " << name << "(" << param << ")" << endl;
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
	Fragment expr3 = st.back(); st.pop_back();
	Fragment expr2 = st.back(); st.pop_back();
	Fragment expr1 = st.back(); st.pop_back();
	ostringstream *s = (ostringstream*)o.top();
	o.pop();
    
	level--;
	indent();
	*s << '\0';
	*o.top() << "for ( " << expr1.s << "; " << expr2.s << "; "
		 << expr3.s << ")" << endl
		 << s->str() << endl;
	delete s;
    }
  
    virtual void whileBegin()
	{
	    level++;
	    o.push(new ostringstream());
	}
  
    virtual void whileEnd()  { // 1 expr, 1 stat
	Fragment expr = st.back(); st.pop_back();
	ostringstream *s = (ostringstream*)o.top();
	o.pop();

	level--;
	indent();
    
	*s << '\0';
	*o.top() << "while (" << expr.s << ")" << endl
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
	*o.top() << "if (" << st.back().s << ")" << endl
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
	*o.top() << st.back().s << ';' << endl;
	st.pop_back();
    }

    virtual void returnStatement(bool hasValue) {
	Fragment f;
	indent(f.s);
    
	if (hasValue) {
	    f.s += "return " + st.back().s + ";\n";
	    st.pop_back();
	} else {
	    f.s += "return;\n";
	}
	st.push_back(f);
    }
  
    virtual void procBegin(const char *id, uint32_t n) {
	*o.top() << "process " << id << '(' << param << ")" << endl
		 << "{" << endl;
	param = "";
	
	level += 1;
    }

    virtual void procState(const char *id) {
	if (first) {
	    first = false;
	    indent();
	    *o.top() << "state " << id;
	} else {
	    *o.top() << ", " << id;
	}

	if (st.back().s != "true")
	    *o.top() << '{' << st.back().s << '}';
	st.pop_back();
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
    
    virtual void procSync(uint32_t type) {
	switch (type) {
	case SYNC_QUE:
	    st.back().s += '?';
	    break;
	case SYNC_BANG:
	    st.back().s += '!';
	    break;
	case SYNC_TAU:
	    st.push_back(Fragment());
	    break;
	default:
	    throw TypeException("Invalid synchronisation");
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

	// Complete labels
	if (update == -1) {
	    exprTrue();
	    procUpdate();
	}

	if (sync == -1) {
	    procSync(SYNC_TAU);
	}

	if (guard == -1) {
	    exprTrue();
	    procGuard();
	}

	Fragment assign = st[this->update - 1];
	Fragment sync   = st[this->sync - 1];
	Fragment guard  = st[this->guard - 1];

	st.pop_back(); st.pop_back(); st.pop_back();

	this->update = this->sync = this->guard = -1;

	level++;
      
	if (guard.s != "true") {
	    indent();
	    *o.top() << "guard " << guard.s << ';' << endl;
	}

	if (!sync.s.empty()) {
	    indent();
	    *o.top() << "sync " << sync.s << ';' << endl;
	}

	if (assign.s != "true") {
	    indent();
	    *o.top() << "assign " << assign.s << ';' << endl;
	}

	level--;
    
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
	st.push_back(Fragment());
	st.back().s = id;
    }
  
    virtual void exprNat(int32_t n) {
	char s[20];
	snprintf(s, 20, "%d", n);
	st.push_back(Fragment());
	st.back().s += s;
    }
  
    virtual void exprTrue() {
	st.push_back(Fragment());
	st.back().s = "true";
    }

    virtual void exprFalse() {
	st.push_back(Fragment());
	st.back().s = "false";
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
	Fragment f = st.back();
	st.pop_back();
	st.back().s += '[' + f.s + ']';
    }

    virtual void exprPostIncrement() {
	st.back().s += "++";
    }

    virtual void exprPreIncrement() {
	st.back().s = "++" + st.back().s;
    }

    virtual void exprPostDecrement() {
	st.back().s += "--";
    }

    virtual void exprPreDecrement() {
	st.back().s = "--" + st.back().s;
    }

    virtual void exprAssignment(uint32_t op) {
	Fragment rhs = st.back(); st.pop_back();
	Fragment lhs = st.back(); st.pop_back();

	st.push_back(Fragment());
	switch (op) {
	case ASSIGN:
	    st.back().s = '(' + lhs.s + " = " + rhs.s + ')';
	    break;
	case ASSPLUS:
	    st.back().s = '(' + lhs.s + " += " + rhs.s + ')';
	    break;
	case ASSMINUS:
	    st.back().s = '(' + lhs.s + " -= " + rhs.s + ')';
	    break;
	case ASSMULT:
	    st.back().s = '(' + lhs.s + " *= " + rhs.s + ')';
	    break;
	case ASSDIV:
	    st.back().s = '(' + lhs.s + " /= " + rhs.s + ')';
	    break;
	case ASSMOD:
	    st.back().s = '(' + lhs.s + " %= " + rhs.s + ')';
	    break;
	case ASSOR:
	    st.back().s = '(' + lhs.s + " |= " + rhs.s + ')';
	    break;
	case ASSAND:
	    st.back().s = '(' + lhs.s + " &= " + rhs.s + ')';
	    break;
	case ASSXOR:
	    st.back().s = '(' + lhs.s + " ^= " + rhs.s + ')';
	    break;
	case ASSLSHIFT:
	    st.back().s = '(' + lhs.s + " <<= " + rhs.s + ')';
	    break;
	case ASSRSHIFT:
	    st.back().s = '(' + lhs.s + " >>= " + rhs.s + ')';
	    break;
	default:
	    throw TypeException("Invalid assignment operator");
	}
    }

    virtual void exprUnary(uint32_t op) {
	Fragment exp = st.back(); st.pop_back();

	st.push_back(Fragment());
	switch (op) {
	case MINUS:
	    st.back().s = '-' + exp.s;
	    break;
	case NOT:
	    st.back().s = '!' + exp.s;
	    break;
	default:
	    throw TypeException("Invalid operator");
	}
    }

    virtual void exprBinary(uint32_t op) {
	Fragment exp2 = st.back(); st.pop_back();
	Fragment exp1 = st.back(); st.pop_back();
    
	st.push_back(Fragment());
	switch (op) {
	case PLUS:
	    st.back().s = '(' + exp1.s + " + " + exp2.s + ')';
	    break;
	case MINUS:
	    st.back().s = '(' + exp1.s + " - " + exp2.s + ')';
	    break;
	case MULT:
	    st.back().s = '(' + exp1.s + " * " + exp2.s + ')';
	    break;
	case DIV:
	    st.back().s = '(' + exp1.s + " / " + exp2.s + ')';
	    break;
	case MOD:
	    st.back().s = '(' + exp1.s + " % " + exp2.s + ')';
	    break;
	case LT:
	    st.back().s = '(' + exp1.s + " < " + exp2.s + ')';
	    break;      
	case LE:
	    st.back().s = '(' + exp1.s + " <= " + exp2.s + ')';
	    break;      
	case EQ:
	    st.back().s = '(' + exp1.s + " == " + exp2.s + ')';
	    break;      
	case NEQ:
	    st.back().s = '(' + exp1.s + " != " + exp2.s + ')';
	    break;      
	case GE:
	    st.back().s = '(' + exp1.s + " >= " + exp2.s + ')';
	    break;      
	case GT:
	    st.back().s = '(' + exp1.s + " > " + exp2.s + ')';
	    break;
	case AND:
	    st.back().s = '(' + exp1.s + " && " + exp2.s + ')';
	    break;
	case OR:
	    st.back().s = '(' + exp1.s + " || " + exp2.s + ')';
	    break;
	case BIT_AND:
	    st.back().s = '(' + exp1.s + " & " + exp2.s + ')';
	    break;
	case BIT_OR:      
	    st.back().s = '(' + exp1.s + " | " + exp2.s + ')';
	    break;
	case BIT_XOR:
	    st.back().s = '(' + exp1.s + " ^ " + exp2.s + ')';
	    break;
	case BIT_LSHIFT:
	    st.back().s = '(' + exp1.s + " << " + exp2.s + ')';
	    break;
	case BIT_RSHIFT:
	    st.back().s = '(' + exp1.s + " >> " + exp2.s + ')';
	    break;
	default:
	    throw TypeException("Invalid operator");
	}
    }

    virtual void exprInlineIf() {  
	Fragment expr3 = st.back(); st.pop_back();
	Fragment expr2 = st.back(); st.pop_back();
	Fragment expr1 = st.back(); st.pop_back();

	st.push_back(Fragment());
	st.back().s = expr1.s + " ? " + expr2.s + " : " + expr3.s;
    }

    virtual void exprComma() {
	Fragment expr2 = st.back(); st.pop_back();
	Fragment expr1 = st.back(); st.pop_back();

	st.push_back(Fragment());
	st.back().s = expr1.s + ", " + expr2.s;
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
	stack<Fragment> s;
	while (n--) {
	    s.push(st.back());
	    st.pop_back();
	}

	*o.top() << id << " = " << templ << '(';
	while (!s.empty()) {
	    *o.top() << s.top().s;
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

    ParserBuilder *b;
    if (check) {
	b = new TypeChecker(&system);
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
    vector<ErrorHandler::error_t>::const_iterator it;
    const vector<ErrorHandler::error_t> &errors = errorHandler.getErrors();
    const vector<ErrorHandler::error_t> &warns = errorHandler.getWarnings();
    for (it = errors.begin(); it != errors.end(); it++)
	cerr << *it << endl;
    for (it = warns.begin(); it != warns.end(); it++)
	cerr << *it << endl;
    return 0;
}




