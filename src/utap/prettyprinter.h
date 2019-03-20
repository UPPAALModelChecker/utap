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
	std::string winning;
	std::string losing;
	std::string param;
	std::string templateset;
	int select, guard, sync, update;
	
	bool first;
	uint32_t level;
	
	void indent();
	void indent(std::string &s);

    public:
	PrettyPrinter(std::ostream &stream);

	virtual void addPosition(
	    uint32_t position, uint32_t offset, uint32_t line, std::string path);

	virtual void handleError(std::string);
	virtual void handleWarning(std::string);

	virtual void typeBool(PREFIX);
	virtual void typeInt(PREFIX);
	virtual void typeBoundedInt(PREFIX);
	virtual void typeChannel(PREFIX);
	virtual void typeClock();
	virtual void typeVoid();
	virtual void typeScalar(PREFIX);
	virtual void typeName(PREFIX, const char *type);
	virtual void declTypeDef(const char* name); 
	virtual void declVar(const char *id, bool init);
	virtual void declInitialiserList(uint32_t num);
	virtual void declFieldInit(const char* name);
	virtual void declParameter(const char* name, bool);
	virtual void declFuncBegin(const char* name);
	virtual void declFuncEnd();
	virtual void blockBegin();
	virtual void blockEnd();
	virtual void emptyStatement();
	virtual void forBegin();
	virtual void forEnd();
	virtual void iterationBegin(const char *name); // 1 id, 1 type
	virtual void iterationEnd(const char *name); // 1 stat
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
	virtual void procBegin(const char* name);
	virtual void procState(const char *id, bool hasInvariant);
	virtual void procStateUrgent(const char *id);
	virtual void procStateCommit(const char *id);
	virtual void procStateWinning(const char *id);
	virtual void procStateLosing(const char *id);
	virtual void procStateInit(const char *id);
	virtual void procSelect(const char *id);
	virtual void procGuard();
	virtual void procSync(Constants::synchronisation_t type);
	virtual void procUpdate();
	virtual void procEdgeBegin(const char *source, const char *target, const bool control);
        virtual void procEdgeEnd(const char *source, const char *target);
	virtual void procEnd();
	virtual void exprId(const char *id);
	virtual void exprNat(int32_t n);
	virtual void exprTrue();
	virtual void exprFalse();
	virtual void exprCallBegin();
	virtual void exprCallEnd(uint32_t n);
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
	virtual void exprForAllBegin(const char *name);
	virtual void exprForAllEnd(const char *name);
	virtual void exprExistsBegin(const char *name);
	virtual void exprExistsEnd(const char *name);
	virtual void beforeUpdate();
	virtual void afterUpdate();
	virtual void instantiationBegin(const char *, size_t, const char *);
	virtual void instantiationEnd(
	    const char *, size_t, const char *, size_t);
	virtual void process(const char *id);
	virtual void done();
    };
}

#endif