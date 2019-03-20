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

#include <list>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <functional>

/**
 * print -- template for pretty printing lists.
 * similar to ostream_iterator except it does not print last delimiter.
 */
template <class T>
struct print: public std::unary_function<T, void>
{
    std::ostream& os;
    const char *infix;
    bool need;

    print(std::ostream& out, const char* sep):
	os(out), infix(sep), need(false) {}

    void operator()(const T& x) {
	if (need) os << infix;
	os << x; need = true;
    }
};

#include "utap/iointerface.h"
#include "utap/common.h"

using std::list;
using std::map;
using std::set;
using std::ostream;
using std::ostream_iterator;
using std::cerr;
using std::endl;

using UTAP::IOInterface;
using UTAP::TimedAutomataSystem;
using namespace UTAP::Constants;

IOInterface::IOInterface(const char* _title, TimedAutomataSystem& tas):
    title(_title), cTA(NULL), cP(NULL), inp(false), out(false), sync(false),
    paramsExpanded(false)
{
/**
 * Visit all processes in the system.
 */
    list<process_t> &ps(tas.getProcesses());
    list<process_t>::iterator it;
    for (it = ps.begin(); it != ps.end(); it++)
	visitProcess(*it);
}

void IOInterface::printForTron(ostream &os)
{
    list<iota_t>::const_iterator it;
    for (it = automata.begin(); it != automata.end(); it++) {
	os << it->name << ":\n  "; // automaton:
	// input channels,
	for_each(it->inChans.begin(), it->inChans.end(),
		 print<const char*>(os, " "));
	os << ",\n  ";
	// output channels,
	for_each(it->outChans.begin(), it->outChans.end(),
		 print<const char*>(os, " "));
	os << ",\n ";
	str2strs_t::const_iterator v;
	// input variables(channels),
	for (v = it->rdVars.begin(); v != it->rdVars.end(); v++) {
	    os << " " << v->first << "(";
	    for_each(v->second.begin(), v->second.end(),
		     print<const char*>(os, " "));
	    os << ")";
	}
	os << ",\n ";
	// output variables(channels);
	for (v = it->wtVars.begin(); v != it->wtVars.end(); v++) {
	    os << " " << v->first << "(";
	    for_each(v->second.begin(), v->second.end(),
		     print<const char*>(os, " "));
	    os << ")";
	}
	os << "\n;\n";
    }
}

void IOInterface::printForDot(ostream &os, bool ranked, bool erd, bool cEdge)
{
    char* name = strcpy(new char[strlen(title)+1], title);
    for (uint32_t i=0; i<strlen(name); i++)
	if (!isalpha(name[i])) name[i]='_';

    os << "digraph " << name << " {\n";
    os << "  model=subset; remincross=true;\n";
//    os << "  edge [decorate];\n"; // use 'dot -Edecorate' if you wish
    delete [] name;

    strs_t::const_iterator it;
    list<iota_t>::iterator a;

/** Enumerate processes with common look-attributes */
    if (!procs.empty()) {
	os << "  subgraph procs {\n";
	if (erd)
	    os<<"    node [shape=box,style=filled,fillcolor=lightgray];\n";
	else
	    os<<"    node [shape=ellipse,style=filled,fillcolor=lightgray];\n";
	os << "    ";
	for_each(procs.begin(), procs.end(),
		 print<const char*>(os, "; "));
	os << "\n  }\n";
    }

/** Enumerate variables, with common look-attributes */
    if (!variables.empty()) { // draw variables
	/* specify attributes for all nodes */
	os << "  subgraph cluste_vars {\n";
	os << "    style=invis;\n";
	if (ranked) os << "    rank=min;\n";
	if (erd) os << "    node [shape=diamond,color=blue];\n    ";
	else os << "    node [shape=ellipse,color=blue];\n    ";
	for (it=variables.begin(); it != variables.end(); it++) {
	    if (transmiters.find(*it) == transmiters.end())
		os << *it << "; "; // const variables are slim
	    else os << *it << "[style=bold]; "; // others bold
	}
	os << "\n  }\n";

/** draw variable edges */
	str2strs_t::const_iterator v;
/** first, 'variable write' edges are bold */
	os<<"  edge [style=bold,color=blue,fontcolor=blue,weight=100];\n";
	for (a=automata.begin(); a!=automata.end(); a++) {
	    if (!a->wtVars.empty()) {
		for (v = a->wtVars.begin(); v != a->wtVars.end(); v++) {
		    os<<"  " << a->name << " -> " << v->first << " [label=\"(";
		    /* enumerate channels when variable is accessed */
		    for_each(v->second.begin(), v->second.end(),
			     print<const char*>(os, ","));
		    os<<")\"];\n";
		}
	    }
	}
/** second, 'variable read' edges are slim  */
	os<<"  edge [style=solid,color=blue,fontcolor=blue,weight=1];\n";
	for (a=automata.begin(); a!=automata.end(); a++) {
	    if (!a->rdVars.empty()) {
		for (v = a->rdVars.begin(); v != a->rdVars.end(); v++) {
		    os<<"  " << v->first << " -> " << a->name << " [label=\"(";
		    /* enumerate channels when variable is accessed */
		    for_each(v->second.begin(), v->second.end(),
			     print<const char*>(os, ","));
		    os<<")\"];\n";
		}
	    }
	}
    }

/** enumerate draw channels */
    if (!channels.empty()) {
	if (cEdge) { /* channels are only on edges */
	    const char* src = "NO_SRC";
	    const char* dst = "NO_DST";
	    /** build an index of outgoing edges sorted by destination TA */
	    for (a=automata.begin(); a!=automata.end(); a++) {
		/* traverse all outgoing channels */
		for (it=a->outChans.begin(); it!=a->outChans.end(); it++) {
		    str2tas_t::const_iterator dests = receivers.find(*it);
		    if (dests != receivers.end()) { // there are destinations
			for (set<iota_t*>::const_iterator rec =
				 dests->second.begin();
			     rec != dests->second.end(); rec++)
			    a->outEdges[*rec].insert(*it);
		    } else // no destination
			a->outEdges[NULL].insert(*it);
		}
	    }
	    /** display all edges: */
	    os<<"  edge[style=solid,color=black,fontcolor=black,weight=50];\n";
	    for (a=automata.begin(); a!=automata.end(); a++) {
		/* display outgoing edges: */
		for (iota2strs_t::const_iterator edge = a->outEdges.begin();
		     edge != a->outEdges.end(); edge++) {
		    bool noDst = false;
		    // display edge:
		    if (edge->first != NULL) //normal destination TA
			os<<"  " << a->name << " -> " << edge->first->name
			  << " [label=\"[";
		    else { // there was no destination TA
			if (!noDst) {
			    os<<"  "<<dst
			      <<" [style=filled,fillcolor=red];\n";
			    noDst = true;
			}
			os<<"  " << a->name << " -> " << dst
			  << " [label=\"[";
		    }
		    // enumerate all channels on the edge:
		    strs_t::const_iterator ch=edge->second.begin();
		    while (true) {
			os<< *ch;
			ch++;
			if (ch != edge->second.end()) os << ",";
			else break;
		    }
		    os << "]\"];\n";
		}
		/* by now all inps with sources are displayed as outputs
		 * search and display inputs w/o sources */
		bool noSrc = false;
		for (it=a->inChans.begin(); it!=a->inChans.end(); it++) {
		    str2tas_t::const_iterator trans = transmiters.find(*it);
		    if (trans==transmiters.end()) {
			if (!noSrc) {
			    os<<"  "<<src
			      <<" [style=filled,fillcolor=red];\n";
			    noSrc = true;
			}
			os<<"  "<<src<<" -> " << a->name << " [label=\""
			  << *it << "\"];\n";
		    }
		}
	    }
	} else { /* channels displayed as separate nodes (like variables) */
	    os<< "  subgraph cluste_chans {\n";
	    os<< "    style=invis;\n";
	    if (ranked) os<<"    rank=max;\n";
	    if (erd) os<<"    node [shape=diamond,color=red];\n    ";
	    else os<<"    node [shape=ellipse,color=red];\n    ";
	    for_each(channels.begin(), channels.end(),
		     print<const char*>(os, "; "));
	    os<< "\n  }\n";

	    for (a=automata.begin(); a!=automata.end(); a++) {
		for (it=a->inChans.begin(); it!=a->inChans.end(); it++)
		    os << "  " << *it << " -> " << a->name << ";\n";
		for (it=a->outChans.begin(); it!=a->outChans.end(); it++)
		    os << "  " << a->name << " -> " << *it
		       << " [style=bold];\n";
	    }
	}
    }
    os << "}" << endl;
}

bool IOInterface::checkParams(const symbol_t &s)
{
    if (!paramsExpanded) {
	if (0<=cP->templ->parameters.getIndexOf(s.getName())) {
	    // is it parameter? find the corresponding global symbol(s)
	    map<symbol_t, expression_t>::iterator e = cP->mapping.find(s);
	    if (e != cP->mapping.end()) {
		paramsExpanded = true;
		visitExpression(e->second);
		paramsExpanded = false;
	    } else {
		cerr << "mapping param '"<< s.getName() << "' failed"<<endl;
		exit(EXIT_FAILURE);
	    }
	    return false;
	} else if (0<=cP->templ->frame.getIndexOf(s.getName())) {
	    // is it local symbol? discard, no observable I/O here
	    return false;
	}
    }
    // it must be global/shared
/*    if(s.getFrame().hasParent()) {// should not have a parent
	cerr << s.getName() <<" assumed to be global but it is not" << endl;
	exit(EXIT_FAILURE);
	}*/
    return true;
}

void IOInterface::addChan(const symbol_t &s, strs_t &ids, str2tas_t& index)
{
    if (checkParams(s)) {
	ids.insert(s.getName().c_str());
	channels.insert(s.getName().c_str());
	index[s.getName().c_str()].insert(cTA);
	cChan = s.getName().c_str();
    }
}

void IOInterface::addVar(const symbol_t &s, str2strs_t &ids, str2tas_t& index)
{
    if (checkParams(s)) {
	ids[s.getName().c_str()].insert(cChan);
	variables.insert(s.getName().c_str());
	index[s.getName().c_str()].insert(cTA);
    }
}

static const char* noChan = "-";

void IOInterface::visitProcess(process_t &p)
{
    automata.push_back(iota_t(p.uid.getName().c_str()));
    procs.insert(p.uid.getName().c_str());
    cTA = &automata.back();
    cP = &p;
    const template_t* temp = p.templ;
    list<state_t>::const_iterator s = temp->states.begin();
    while (s != temp->states.end()) {
	cChan = noChan; // invariants should not use shared
	visitExpression(s->invariant);
	++s;
    }
    list<edge_t>::const_iterator t = temp->edges.begin();
    while (t != temp->edges.end()) {
	cChan = noChan;// guards should not use shared
	visitExpression(t->guard);
	visitExpression(t->sync);
	visitExpression(t->assign);
	++t;
    }
}

void IOInterface::visitExpression(const expression_t &e)
{
    if (e.empty()) return;

    switch (e.getKind()) {
    case PLUS:
    case MINUS:
    case MULT:
    case DIV:
    case MOD:
    case BIT_AND:
    case BIT_OR:
    case BIT_XOR:
    case BIT_LSHIFT:
    case BIT_RSHIFT:
    case AND:
    case OR:
    case MIN:
    case MAX:
	    /********************************************************
	     * Relational operators
	     */
    case LT:
    case LE:
    case EQ:
    case NEQ:
    case GE:
    case GT:
	    /********************************************************
	     * Unary operators
	     */
    case NOT:
	    /********************************************************
	     * Assignment operators
	     */
	for (uint32_t i=0; i<e.getSize(); i++) {
	    inp = true; out = false;
	    visitExpression(e[i]);
	}
	break;
    case ASSIGN:
    case ASSPLUS:
    case ASSMINUS:
    case ASSDIV:
    case ASSMOD:
    case ASSMULT:
    case ASSAND:
    case ASSOR:
    case ASSXOR:
    case ASSLSHIFT:
    case ASSRSHIFT:
	inp = false; out = true;
	visitExpression(e[0]);
	for (uint32_t i=1; i<e.getSize(); i++) {
	    inp = true; out = false;
	    visitExpression(e[i]);
	}
	break;

	    /*******************************************************
	     * Additional constants used by ExpressionProgram's and
	     * the TypeCheckBuilder (but not by the parser, although
	     * some of then ought to be used, FIXME).
	     */
    case IDENTIFIER:
	if (sync) {
	    if (inp) addChan(e.getSymbol(), cTA->inChans, receivers);
	    if (out) addChan(e.getSymbol(), cTA->outChans, transmiters);
	} else {
	    if (inp) addVar(e.getSymbol(), cTA->rdVars, receivers);
	    if (out) addVar(e.getSymbol(), cTA->wtVars, transmiters);
	}
	break;
    case CONSTANT: break; // don't care
    case ARRAY:
	visitExpression(e[0]);
	for (uint32_t i=1; i<e.getSize(); i++) {
	    inp = true; out = false;
	    visitExpression(e[i]);
	}
	break;
    case POSTINCREMENT:
    case PREINCREMENT:
    case POSTDECREMENT:
    case PREDECREMENT:
	inp = true; out = true;
	visitExpression(e[0]);
	break;
    case UNARY_MINUS:
	inp = true; out = false;
	visitExpression(e[0]);
	break;
    case LIST:
	for (uint32_t i=0; i<e.getSize(); i++) {
	    inp = true; out = false;
	    visitExpression(e[i]);
	}
	break;
    case DOT:
	visitExpression(e[0]);
	visitExpression(e[1]);
	break;
    case INLINEIF:
	pushIO();
	inp = true; out = false;
	visitExpression(e[0]);
	for (uint32_t i=1; i<e.getSize(); i++) {
	    popIO(); pushIO();
	    visitExpression(e[i]);
	}
	popIO();
	break;
    case COMMA:
	pushIO();
	for (uint32_t i=0; i<e.getSize()-1; i++) {
	    inp = true; out = false;
	    visitExpression(e[i]);
	}
	popIO();
	visitExpression(e[e.getSize()-1]);
	break;
    case SYNC:
	if (e.getSync() == SYNC_QUE) { inp = true; out = false; }
	else { inp = false; out = true; }
	sync = true;
	visitExpression(e[0]);
	sync = false;
	break;
    case FUNCALL:
	// FIXME for UPPAAL >=3.5 UCode
	break;
    case DEADLOCK:
	    /*******************************************************
	     * CTL Quantifiers
	     */
    case EF:
    case EG:
    case AF:
    case AG:
    case LEADSTO:

    default:
	cerr << "unsupported expression kind" << endl;
	exit(1);
    }
}

int32_t IOInterface::visitEmptyStatement(EmptyStatement *stat)
{
    return 0;
}

int32_t IOInterface::visitExprStatement(ExprStatement *stat)
{
    visitExpression(stat->expr);
    return 0;
}

int32_t IOInterface::visitIterationStatement(IterationStatement *stat)
{
// FixMe: there is mysterious field called symbol, do smth about it.
    return stat->stat->accept(this);
}

int32_t IOInterface::visitForStatement(ForStatement *stat)
{
    visitExpression(stat->init);
    visitExpression(stat->cond);
    visitExpression(stat->step);
    return stat->stat->accept(this);
}

int32_t IOInterface::visitWhileStatement(WhileStatement *stat)
{
    visitExpression(stat->cond);
    return stat->stat->accept(this);
}

int32_t IOInterface::visitDoWhileStatement(DoWhileStatement *stat)
{
    int32_t res = stat->stat->accept(this);
    visitExpression(stat->cond);
    return res;
}

int32_t IOInterface::visitBlockStatement(BlockStatement *stat)
{
    int32_t res = 0;
    BlockStatement::iterator it = stat->begin();
    while (it != stat->end()) {
	res = (*it)->accept(this);
	++it;
    }
    return res;
}

int32_t IOInterface::visitSwitchStatement(SwitchStatement *stat)
{
    visitExpression(stat->cond);
    return visitBlockStatement(stat);
}

int32_t IOInterface::visitCaseStatement(CaseStatement *stat)
{
    visitExpression(stat->cond);
    return visitBlockStatement(stat);
}

int32_t IOInterface::visitDefaultStatement(DefaultStatement *stat)
{
    return visitBlockStatement(stat);
}

int32_t IOInterface::visitIfStatement(IfStatement *stat)
{
    visitExpression(stat->cond);
    int32_t res = stat->trueCase->accept(this);
    if (stat->falseCase) return stat->falseCase->accept(this);
    else return res;
}
int32_t IOInterface::visitBreakStatement(BreakStatement *stat)
{
    return 0;
}

int32_t IOInterface::visitContinueStatement(ContinueStatement *stat)
{
    return 0;
}

int32_t IOInterface::visitReturnStatement(ReturnStatement *stat)
{
    visitExpression(stat->value);
    return 0;
}
