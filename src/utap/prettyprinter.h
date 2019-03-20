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

#ifndef UTAP_PRETTYPRINTER_H
#define UTAP_PRETTYPRINTER_H

#include <string>
#include <vector>
#include <ostream>
#include <stack>
#include "utap/abstractbuilder.h"

namespace UTAP
{

    class PrettyPrinter : public AbstractBuilder
    {
    private:
	std::vector<std::string> st;	
	std::stack<std::ostream *> o;
	std::string urgent;
	std::string committed;
	std::string param;
	int guard, sync, update;
	
	bool first;
	uint32_t level;
	
	void indent();
	void indent(std::string &s);

    public:
	PrettyPrinter(std::ostream &stream);

	virtual void setErrorHandler(ErrorHandler *);
	virtual void setPosition(const position_t &);
    
	virtual bool isType(const char *id);
	virtual void typeName(int32_t prefix, const char *type, int range);
	virtual void declVar(const char *id, uint32_t dim, bool init);
	virtual void declVarEnd();
	virtual void declInitialiserList(uint32_t num);
	virtual void declFieldInit(const char* name);
	virtual void declParameter(const char* name, bool reference, uint32_t dim);
	virtual void declParameterEnd();
	virtual void declFuncBegin(const char* name, uint32_t n);
	virtual void declFuncEnd();
	virtual void blockBegin();
	virtual void blockEnd();
	virtual void emptyStatement();
	virtual void forBegin();
	virtual void forEnd();
	virtual void whileBegin();
	virtual void whileEnd();
	virtual void doWhileBegin();
	virtual void doWhileEnd();
	virtual void ifBegin();
	virtual void ifElse();
	virtual void ifEnd(bool);
	virtual void breakStatement();
	virtual void continueStatement();
	virtual void exprStatement();
	virtual void returnStatement(bool hasValue);
	virtual void procBegin(const char *id, uint32_t n);
	virtual void procState(const char *id, bool hasInvariant);
	virtual void procStateUrgent(const char *id);
	virtual void procStateCommit(const char *id);
	virtual void procStateInit(const char *id);
	virtual void procGuard();
	virtual void procSync(Constants::synchronisation_t type);
	virtual void procUpdate();
	virtual void procEdge(const char *source, const char *target);
	virtual void procEnd();
	virtual void exprId(const char *id);
	virtual void exprNat(int32_t n);
	virtual void exprTrue();
	virtual void exprFalse();
	virtual void exprCallBegin(const char *name);
	virtual void exprCallEnd(uint32_t n);
	virtual void exprArg(uint32_t n);
	virtual void exprArray();
	virtual void exprPostIncrement();
	virtual void exprPreIncrement();
	virtual void exprPostDecrement();
	virtual void exprPreDecrement();
	virtual void exprAssignment(Constants::kind_t op);
	virtual void exprUnary(Constants::kind_t op);
	virtual void exprBinary(Constants::kind_t op);
	virtual void exprInlineIf();
	virtual void exprComma();
	virtual void exprDot(const char *);
	virtual void exprDeadlock();
	virtual void beforeUpdate();
	virtual void afterUpdate();
	virtual void instantiationBegin(const char *id, const char *templ);
	virtual void instantiationEnd(const char* id, const char* templ, uint32_t n);
	virtual void process(const char *id);
	virtual void done();
    };
}

#endif
