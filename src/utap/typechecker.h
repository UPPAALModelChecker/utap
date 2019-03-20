// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2002-2006 Uppsala University and Aalborg University.

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

#include "utap/system.h"
#include "utap/common.h"
#include "utap/expression.h"
#include "utap/statement.h"

#include <exception>
#include <set>

namespace UTAP
{
    /**
     * Visitor which collects all compile time computable
     * symbols. These are all global and template local constants and
     * all constant non-reference template parameters. Variables with
     * mixed storage are not considered compile time computable.
     */
    class CompileTimeComputableValues : public SystemVisitor
    {
    private:
        std::set<symbol_t> variables;
    public:
        void visitVariable(variable_t &) override;
        void visitInstance(instance_t &) override;
        bool contains(symbol_t) const;
    };

    /**
     * A visitor which type checks the system it visits.  The type
     * checker can only visit the system given in the constructor. The
     * type checker must not be constructed before the system has been
     * parsed.
     */
    class TypeChecker : public SystemVisitor, public AbstractStatementVisitor
    {
    private:
        TimedAutomataSystem *system;
        CompileTimeComputableValues compileTimeComputableValues;
        function_t *function{nullptr}; /**< Current function being type checked. */
        bool refinementWarnings;

        template<class T>
        void handleError(const T&, const std::string&);
        template<class T>
        void handleWarning(const T&, const std::string&);

        expression_t checkInitialiser(type_t type, expression_t init);
        bool areAssignmentCompatible(type_t lvalue, type_t rvalue, bool init = false) const;
        bool areInlineIfCompatible(type_t thenArg, type_t elseArg) const;
        bool areEqCompatible(type_t t1, type_t t2) const;
        bool areEquivalent(type_t, type_t) const;
        bool isLValue(expression_t) const;
        bool isModifiableLValue(expression_t) const;
        bool isUniqueReference(expression_t expr) const;
        bool isParameterCompatible(type_t param, expression_t arg);
        bool checkParameterCompatible(type_t param, expression_t arg);
        void checkIgnoredValue(expression_t expr);
        bool checkAssignmentExpression(expression_t);
        bool checkConditionalExpressionInFunction(expression_t);
        void checkObservationConstraints(expression_t);

        bool isCompileTimeComputable(expression_t expr) const;
        void checkType(type_t, bool initialisable = false, bool inStruct = false);

    public:
        TypeChecker(TimedAutomataSystem *system, bool refinement = false);
        ~TypeChecker() override {}
        void visitTemplateAfter (template_t& ) override;
        bool visitTemplateBefore(template_t& ) override;
        void visitSystemAfter(TimedAutomataSystem *) override;
        void visitVariable(variable_t &) override;
        void visitState(state_t &) override;
        void visitEdge(edge_t &) override;
        void visitInstance(instance_t &) override;
        virtual void visitProperty(expression_t); // FIXME: does not override?!
        void visitFunction(function_t &) override;
        void visitProgressMeasure(progress_t &) override;
        virtual void visitHybridClock(expression_t); // FIXME: does not override?!
        void visitIODecl(iodecl_t &) override;
        void visitGanttChart(gantt_t&) override;
        void visitProcess(instance_t &) override;
        void visitInstanceLine(instanceLine_t &) override;
        void visitMessage(message_t &) override;
        void visitCondition(condition_t &) override;
        void visitUpdate(update_t &) override;
        int32_t visitEmptyStatement(EmptyStatement *stat) override;
        int32_t visitExprStatement(ExprStatement *stat) override;
        int32_t visitAssertStatement(AssertStatement *stat) override;
        int32_t visitForStatement(ForStatement *stat) override;
        int32_t visitIterationStatement(IterationStatement *stat) override;
        int32_t visitWhileStatement(WhileStatement *stat) override;
        int32_t visitDoWhileStatement(DoWhileStatement *stat) override;
        int32_t visitBlockStatement(BlockStatement *stat) override;
        int32_t visitIfStatement(IfStatement *stat) override;
        int32_t visitReturnStatement(ReturnStatement *stat) override;

        bool checkDynamicExpressions (Statement* stat);
        /** Type check an expression */
        bool checkExpression(expression_t);
        bool checkSpawnParameterCompatible (type_t param, expression_t arg);
        bool checkSpawnAndExit (expression_t);

    private:
        sync_use_t syncUsed{sync_use_t::unused}; // tracks sync declarations
        bool syncError{false}; // true when sync usage is inconsistent (mix of io and csp)
        template_t* temp{nullptr};

        /** check expressions used in (SMC) properties, these functions provide:
            1) consistent semantic checks by code reuse,
            2) meaningful names to the otherwise anonymous expressions.
         */
        bool checkNrOfRuns(const expression_t& expr);
        bool checkBoundTypeOrBoundedExpr(const expression_t& expr);
        bool checkBound(const expression_t& expr);
        bool checkPredicate(const expression_t& expr);
        bool checkProbBound(const expression_t& expr);
        bool checkUntilCond(Constants::kind_t kind, const expression_t& expr);
        bool checkMonitoredExpr(const expression_t& expr);
        bool checkPathQuant(const expression_t& expr);
        bool checkAggregationOp(const expression_t& expr);
    };
}

#endif
