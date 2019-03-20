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

#ifndef UTAP_TYPECHECKER_HH
#define UTAP_TYPECHECKER_HH


#include <exception>
#include <set>
#include "utap/system.h"
#include "utap/common.h"
#include "utap/expression.h"
#include "utap/statement.h"

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

    /** 
     * A visitor which type checks the system it visits.  The type
     * checker can only visit the system given in the constructor. The
     * type checker must not be constructed before the system has been
     * parsed.
     */
    class TypeChecker : public ContextVisitor, public StatementVisitor
    {
    private:
	ErrorHandler *errorHandler;
	TimedAutomataSystem *system;
	PersistentVariables persistentVariables;
    
	void annotate(expression_t expr);
	void checkInitialiser(variable_t &var);
	expression_t checkInitialiser(type_t type, expression_t init);
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

	/** Checks that the expression is a valid 'statement expression' */
	void checkAssignmentExpressionInFunction(expression_t);

	/** Checks that the expression can be used as a condition (e.g. for if) */
	void checkConditionalExpressionInFunction(expression_t);

	/** Checks that the arguments of a function call expression are valid */
	void checkFunctionCallArguments(expression_t);

	void annotateAndExpectConstantInteger(expression_t);
	void checkType(type_t, bool inRecord = false);

	/** Check that a variable declaration is type correct. */
	void checkVariableDeclaration(variable_t &variable);

	expression_t makeConstant(int);
	type_t typeOfBinaryNonInt(expression_t, uint32_t binaryop, expression_t);
    
    public:
	TypeChecker(TimedAutomataSystem *system, ErrorHandler *handler);
	virtual ~TypeChecker() {}
	virtual void visitSystemBefore(TimedAutomataSystem *);
	virtual void visitVariable(variable_t &);
	virtual void visitState(state_t &);
	virtual void visitTransition(transition_t &);
	virtual void visitInstance(instance_t &);
	virtual void visitProperty(expression_t);
	virtual void visitFunction(function_t &);

	virtual int32_t visitEmptyStatement(EmptyStatement *stat);
	virtual int32_t visitExprStatement(ExprStatement *stat);
	virtual int32_t visitForStatement(ForStatement *stat);
	virtual int32_t visitWhileStatement(WhileStatement *stat);
	virtual int32_t visitDoWhileStatement(DoWhileStatement *stat);
	virtual int32_t visitBlockStatement(BlockStatement *stat);
	virtual int32_t visitSwitchStatement(SwitchStatement *stat);
	virtual int32_t visitCaseStatement(CaseStatement *stat);
	virtual int32_t visitDefaultStatement(DefaultStatement *stat);
	virtual int32_t visitIfStatement(IfStatement *stat);
	virtual int32_t visitBreakStatement(BreakStatement *stat);
	virtual int32_t visitContinueStatement(ContinueStatement *stat);
	virtual int32_t visitReturnStatement(ReturnStatement *stat);

	/** Type check an expression */
	void checkExpression(expression_t);
    };
}

#endif
