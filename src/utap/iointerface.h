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

/**
 * Class IOInterface is for analysing UPPAAL specifications and extracting
 * the timed automata input/output "interface" information which can be
 * treated as a data flow or entity-relationship map of the system.
 *
 * The result can be processed by the dot (graphviz.org) to produce
 * a "human-readable" picture.
 * The other (tron) format is used in TRON project.
 * Feel free to add more "formats" and/or tune the dot output.
 *
 * Author: Marius Mikucionis <marius@cs.aau.dk>
 */

#ifndef UTAP_IOINTERFACE_HH
#define UTAP_IOINTERFACE_HH

#include "utap/system.h"
#include "utap/statement.h"

/* Usually already included in includes above: */
#include <list>
#include <set>
#include <map>

/* Header-specific includes: */
#include <stack>

namespace UTAP {
/**
 * The system must be built by TypeChecker/SystemBuilder before IOInterface.
 * Simply create using constructor and then use print* methods.
 * The rest of methods are used internally by visitor pattern.
 * Feel free to add new print* methods or inheriting classes.
 */
    class IOInterface: public StatementVisitor
    {
    protected:
	struct less_str { // must be somewhere in utilities, replace if found
	    bool operator()(const char* s1, const char* s2){
		return (strcmp(s1,s2)<0);
	    }
	};
	typedef std::set<const char*, less_str> strs_t;// string set
	struct iota_t; // info on TA process
	typedef std::map<const iota_t*, strs_t> iota2strs_t;//TA->string set
	typedef std::map<const char*, strs_t> str2strs_t;//string->string set

	typedef struct iota_t { // input/output info on timed automaton
	    const char* name; // name of the process (timed automaton)
	    strs_t inChans, outChans; // input/output channels used by TA
	    str2strs_t rdVars, wtVars; // variables with accessing channels
	    iota2strs_t outEdges; // index of outChans sorted by destination TA
	    iota_t(const char* _name): name(_name) {}
	};
	typedef std::map<const char*, std::set<iota_t*>, less_str> str2tas_t;
	const char* title; // title of the TA system
	std::list<iota_t> automata; // list of all automata in the system
	str2tas_t receivers, transmiters;// TAs by vars/chans they access
	strs_t procs, channels, variables;
	iota_t* cTA; // current automaton in traversal
	process_t* cP; // current process in traversal
	const char* cChan; // channel on current transition in traversal
	bool inp, out, sync, paramsExpanded;// current expression state
	std::stack<std::pair<bool, bool> > ioStack;// remember I/O state

	bool checkParams(const symbol_t &s);// maps parameter to global symbol
	void addChan(const symbol_t &, strs_t &, str2tas_t&);
	void addVar(const symbol_t &, str2strs_t&, str2tas_t&);
	void visitProcess(process_t &);
	void visitExpression(const expression_t &);
	void pushIO(){
	    ioStack.push(std::make_pair<bool, bool>(inp, out));
	}
	void popIO() {
	    inp = ioStack.top().first;
	    out = ioStack.top().second;
	    ioStack.pop();
	}

    public:
/**
 * Analyse the system and extract I/O information:
 */
	IOInterface(const char* _title, TimedAutomataSystem& ta);
/**
 * Nothing dynamic has been used, no string allocations, therefore no cleanup.
 * All strings are from TASystem (don't dispose TASystem before IOInterface).
 */
	virtual ~IOInterface() {}

/**
 * Print I/O information in TRON format into given output stream.
 */
	void printForTron(std::ostream &os);

/**
 * Print I/O information in DOT format into given output stream.
 * ranked -- puts oposite "ranks" on variables and channels
 * erd -- puts boxes and diamonds rather than (compact) ellipses.
 * cEdged -- channels are moved on edges rather than separate nodes.
 */
	void printForDot(std::ostream &os, bool ranked, bool erd, bool cEdged);

/**
 * System visitor pattern extracts read/write information from UCode.
 * This is actually "const" visitor and should contain "const Statement *stat".
 * Not tested (contains sample implementation but tested only on v3.4 specs).
 */
	int32_t visitEmptyStatement(EmptyStatement *stat);
	int32_t visitExprStatement(ExprStatement *stat);
	int32_t visitForStatement(ForStatement *stat);
	int32_t visitIterationStatement(IterationStatement *stat);
	int32_t visitWhileStatement(WhileStatement *stat);
	int32_t visitDoWhileStatement(DoWhileStatement *stat);
	int32_t visitBlockStatement(BlockStatement *stat);
	int32_t visitSwitchStatement(SwitchStatement *stat);
	int32_t visitCaseStatement(CaseStatement *stat);
	int32_t visitDefaultStatement(DefaultStatement *stat);
	int32_t visitIfStatement(IfStatement *stat);
	int32_t visitBreakStatement(BreakStatement *stat);
	int32_t visitContinueStatement(ContinueStatement *stat);
	int32_t visitReturnStatement(ReturnStatement *stat);
    };
}

#endif
