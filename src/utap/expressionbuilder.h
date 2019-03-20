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

#ifndef UTAP_EXPRESSIONBUILDER_HH
#define UTAP_EXPRESSIONBUILDER_HH

#include <stack>
#include <vector>
#include <cassert>

#include "abstractbuilder.h"
#include "utap.h"

namespace UTAP
{
    class ExpressionBuilder : public AbstractBuilder 
    {
    public:
	class ExpressionFragments 
	{
	private:
	    std::vector<expression_t> data;
	public:
	    expression_t &operator[] (int idx)
		{ return data[data.size() - idx - 1]; }
	    void push(expression_t e)
		{ data.push_back(e); }
	    void pop()
		{ data.pop_back(); }
	    void pop(uint32_t n);
	    uint32_t size() { return data.size(); }
	};

    protected:
	/* Expression stack */
	ExpressionFragments fragments;

	/* Pointer to the intermediate system under construction */
	TimedAutomataSystem *system;

	/* The stack of type fragments. A type fragment is a pair
	 * consiting of a type and an optional name (the name is used
	 * for fields of a structure).
	 */
	class TypeFragments 
	{
	private:
	    std::vector<std::pair<type_t, char *> > data;
	public:
	    ~TypeFragments() 
                { while (!data.empty()) pop(); }
	    std::pair<type_t, char *> &operator[] (int idx)
		{ return data[data.size() - idx - 1]; }
	    void push(type_t value)
		{ data.push_back(std::make_pair(value, (char*)NULL)); }
	    void pop()
		{ assert(!data.empty()); free(data.back().second); data.pop_back(); }
	} typeFragments;

	/* Current frame */
	std::stack<frame_t> frames;

	/* Push a new frame. */
	void pushFrame(frame_t);
	
	/* Pop the topmost frame. */
	void popFrame();

	bool resolve(std::string, symbol_t &);

	expression_t makeConstant(int value);

	/**
	 * Given a prefix and a type, this method creates a new type
	 * by applying the prefix. TypeExceptions might be thrown if
	 * the combination of the prefix and the type is illegal.
	 */
	type_t applyPrefix(int32_t prefix, type_t type);

	/**
	 * If this method returns true, it is allowed to access the
	 * private identifiers of a process by prefixing the
	 * identifier with the process name.
	 *
	 * This is only interesting when parsing properties. In this
	 * case the method should be overridden by a sub class.
	 */
	virtual bool allowProcessReferences() { return false; }

    public:
	ExpressionBuilder(TimedAutomataSystem *);
	ExpressionFragments &getExpressions();

	/************************************************************
	 * Types
	 */
	virtual void typeName(int32_t prefix, const char* name, int range);

	/************************************************************
	 * Query functions
	 */
	virtual bool isType(const char*);
	virtual bool isLocation(const char*);

	/************************************************************
	 * Expressions
	 */
	virtual void exprTrue();
	virtual void exprFalse();
	virtual void exprId(const char * varName);
	virtual void exprNat(int32_t); // natural number
	virtual void exprCallBegin();
	virtual void exprCallEnd(uint32_t n); // n exprs as arguments
	virtual void exprArg(uint32_t n); // 1 exprs as n-th argument for fn-call
	virtual void exprArray(); // 2 expr 
	virtual void exprPostIncrement(); // 1 expr
	virtual void exprPreIncrement(); // 1 expr
	virtual void exprPostDecrement(); // 1 expr
	virtual void exprPreDecrement(); // 1 expr
	virtual void exprAssignment(Constants::kind_t op); // 2 expr
	virtual void exprUnary(Constants::kind_t unaryop); // 1 expr
	virtual void exprBinary(Constants::kind_t binaryop); // 2 expr
	virtual void exprInlineIf(); // 3 expr
	virtual void exprComma(); // 2 expr
	virtual void exprDot(const char *); // 1 expr
	virtual void exprDeadlock();
	virtual void exprForAllBegin(const char *name);
	virtual void exprForAllEnd(const char *name);

    };
}

#endif
