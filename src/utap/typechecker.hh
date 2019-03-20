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

#ifndef UTAP_TYPECHECKER_HH
#define UTAP_TYPECHECKER_HH


#include <exception>
#include <set>
#include "utap/system.hh"
#include "utap/common.hh"
#include "utap/expression.hh"

namespace UTAP
{

    /** Visitor which collects the persistent variables of the
	system. A persistent variable is one which is stored in a
	state. I.e. all non-constant variables except function local
	variables are persistent. Non-constant template parameters and
	reference template parameters are also collected.
    */
    class PersistentVariables : public SystemVisitor
    {
    private:
	std::set<symbol_t> variables;
    public:
	virtual void visitVariable(variable_t &);
	virtual void visitTemplateAfter(template_t &);
	const std::set<symbol_t> &get() const;
    };

    /** A visitor which type checks the system it visits. */
    class TypeChecker : public ContextVisitor
    {
    private:
	ErrorHandler *errorHandler;
	TimedAutomataSystem *system;
	PersistentVariables persistentVariables;
	static std::map<symbol_t, expression_t> empty;
    
	void annotate(expression_t expr);
	void checkInitialiser(variable_t &var);
	void checkInitialiser(type_t type, expression_t init);
	bool areAssignmentCompatible(type_t lvalue, type_t rvalue);
	bool areInlineIfCompatible(type_t thenArg, type_t elseArg);
	bool isInteger(expression_t) const;
	bool isClock(expression_t) const;
	bool isRecord(expression_t) const;
	bool isDiff(expression_t) const;
	bool isInvariant(expression_t) const;
	bool isGuard(expression_t) const;
	bool isConstraint(expression_t) const;
	bool isSideEffectFree(expression_t) const;
	bool isLHSValue(expression_t) const;
	bool isUniqueReference(expression_t expr) const;
	void checkRange(expression_t expr);
	void checkParameterCompatible(const Interpreter &,
				      type_t param, expression_t expr);

	/** Checks that the range of an integer is type correct. */
	void checkIntegerType(type_t type);
    
	expression_t makeConstant(int);
	type_t typeOfBinaryNonInt(expression_t, uint32_t binaryop, expression_t);
    
    public:
	TypeChecker(ErrorHandler *errorHandler);
	virtual ~TypeChecker() {}
	virtual void visitSystemBefore(TimedAutomataSystem *);
	virtual void visitVariable(variable_t &);
	virtual void visitConstant(variable_t &);
	virtual void visitState(state_t &);
	virtual void visitTransition(transition_t &);
	virtual void visitInstance(instance_t &);
	virtual void visitProperty(expression_t);
    };
}

#endif
