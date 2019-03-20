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

namespace UTAP
{

    /** Visitor which collects the persistent variables of the system. A
	persistent variable is one which is stored in a state. I.e. all
	variables except function local variables are persistent.
    */
    class PersistentVariables : public SystemVisitor
    {
    private:
	std::set<int> variables;
    public:
	virtual void visitVariable(variable_t &);
	virtual void visitClock(clock_t &);
	virtual void visitTemplateAfter(template_t &);
	const std::set<int> &get() const;
    };

    /** A visitor which type checks the system it visits. */
    class TypeChecker : public ContextVisitor
    {
    private:
	ErrorHandler *errorHandler;
	TimedAutomataSystem *system;
	PersistentVariables persistentVariables;
    
	void annotate(SubExpression expr);
	void checkInitialiser(type_t type, SubExpression init);
	void insertDefault(ExpressionProgram &expr,
			   ExpressionProgram::iterator pos,
			   type_t type);
	bool areAssignmentCompatible(type_t lvalue, type_t rvalue);
	bool areInlineIfCompatible(type_t thenArg, type_t elseArg);
	bool isInteger(SubExpression) const;
	bool isClock(SubExpression) const;
	bool isRecord(SubExpression) const;
	bool isDiff(SubExpression) const;
	bool isInvariant(SubExpression) const;
	bool isGuard(SubExpression) const;
	bool isConstraint(SubExpression) const;
	bool isSideEffectFree(SubExpression) const;
	bool isLHSValue(SubExpression) const;
	bool isUniqueReference(SubExpression expr) const;
	void checkRange(SubExpression expr);
	void checkParameterCompatible(type_t param, SubExpression expr);
    
	ExpressionProgram::expression_t makeConstant(int);
	type_t typeOfBinaryNonInt(SubExpression, uint32_t binaryop, SubExpression);
    
    public:
	TypeChecker(ErrorHandler *errorHandler);
	virtual ~TypeChecker() {}
	virtual void visitSystemBefore(TimedAutomataSystem *);
	virtual void visitVariable(variable_t &);
	virtual void visitConstant(constant_t &);
	virtual void visitState(state_t &);
	virtual void visitTransition(transition_t &);
	virtual void visitInstance(instance_t &);
	virtual void visitProperty(SubExpression);
    };
}

#endif
