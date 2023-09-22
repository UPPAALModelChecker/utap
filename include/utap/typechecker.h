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

#include "utap/common.h"
#include "utap/document.h"
#include "utap/expression.h"
#include "utap/statement.h"

#include <set>

namespace UTAP {
/**
 * Visitor which collects all compile time computable
 * symbols. These are all global and template local constants and
 * all constant non-reference template parameters. Variables with
 * mixed storage are not considered compile time computable.
 */
class CompileTimeComputableValues : public DocumentVisitor
{
private:
    std::set<symbol_t> variables;

public:
    void visitVariable(variable_t&) override;
    void visitInstance(instance_t&) override;
    void add_symbol(symbol_t);
    bool contains(const symbol_t&) const;
};

/**
 * A visitor which type checks the document it visits.  The type
 * checker can only visit the document given in the constructor. The
 * type checker must not be constructed before the document has been
 * parsed.
 */
class TypeChecker : public DocumentVisitor, public AbstractStatementVisitor
{
private:
    Document& document;
    mutable CompileTimeComputableValues compileTimeComputableValues;
    function_t* function; /**< Current function being type checked. */
    bool refinementWarnings;

    template <class T>
    void handleError(T, const std::string&) const;
    template <class T>
    void handleWarning(T, const std::string&) const;

    expression_t checkInitialiser(const type_t& type, const expression_t& init);
    bool areAssignmentCompatible(const type_t& lvalue, const type_t& rvalue, bool init = false) const;
    bool areInlineIfCompatible(const type_t& result_type, const type_t& thenArg, const type_t& elseArg) const;
    type_t getInlineIfCommonType(type_t t1, type_t t2) const;
    bool areEqCompatible(const type_t& t1, const type_t& t2) const;
    bool isLValue(const expression_t&) const;
    bool isModifiableLValue(const expression_t&) const;
    bool isUniqueReference(const expression_t& expr) const;
    bool isParameterCompatible(const type_t& param, const expression_t& arg) const;
    bool checkParameterCompatible(const type_t& param, const expression_t& arg) const;
    void checkIgnoredValue(const expression_t& expr) const;
    bool checkAssignmentExpression(expression_t&);
    bool checkConditionalExpressionInFunction(const expression_t&);
    void checkObservationConstraints(const expression_t&);

    bool isCompileTimeComputable(const expression_t& expr) const;
    void checkType(const type_t&, bool initialisable = false, bool inStruct = false) const;

public:
    static bool areEquivalent(const type_t&, const type_t&);
    explicit TypeChecker(Document& doc, bool refinement = false);
    void visitTemplateAfter(template_t&) override;
    bool visitTemplateBefore(template_t&) override;
    void visitDocAfter(Document&) override;
    void visitVariable(variable_t&) override;
    void visitLocation(location_t&) override;
    void visitEdge(edge_t&) override;
    void visitInstance(instance_t&) override;
    virtual void visitProperty(expression_t&);  // FIXME: does not override?!
    void visitFunction(function_t&) override;
    void visitProgressMeasure(progress_t&) override;
    virtual void visitHybridClock(expression_t&);  // FIXME: does not override?!
    void visitIODecl(iodecl_t&) override;
    void visitGanttChart(gantt_t&) override;
    void visitProcess(instance_t&) override;
    void visitInstanceLine(instance_line_t&) override;
    void visitMessage(message_t&) override;
    void visitCondition(condition_t&) override;
    void visitUpdate(update_t&) override;
    int32_t visitEmptyStatement(EmptyStatement* stat) override;
    int32_t visitExprStatement(ExprStatement* stat) override;
    int32_t visitAssertStatement(AssertStatement* stat) override;
    int32_t visitForStatement(ForStatement* stat) override;
    int32_t visitIterationStatement(IterationStatement* stat) override;
    int32_t visitWhileStatement(WhileStatement* stat) override;
    int32_t visitDoWhileStatement(DoWhileStatement* stat) override;
    int32_t visitBlockStatement(BlockStatement* stat) override;
    int32_t visitIfStatement(IfStatement* stat) override;
    int32_t visitReturnStatement(ReturnStatement* stat) override;

    bool checkDynamicExpressions(Statement* stat);
    /** Type check an expression */
    bool checkExpression(expression_t&) const;
    bool checkSpawnParameterCompatible(const type_t& param, const expression_t& arg) const;

private:
    int syncUsed;  // Keep track of sync declarations, 0->nothing, 1->IO, 2->CSP, -1->error.
    template_t* temp;

    /** check expressions used in (SMC) properties, these functions provide:
        1) consistent semantic checks by code reuse,
        2) meaningful names to the otherwise anonymous expressions.
     */
    bool checkNrOfRuns(const expression_t& expr) const;
    bool checkBoundTypeOrBoundedExpr(const expression_t& expr) const;
    bool checkBound(const expression_t& expr) const;
    bool checkPredicate(const expression_t& expr) const;
    bool checkProbBound(const expression_t& expr) const;
    bool checkUntilCond(Constants::kind_t kind, const expression_t& expr) const;
    bool checkMonitoredExpr(const expression_t& expr) const;
    bool checkPathQuant(const expression_t& expr) const;
    bool checkAggregationOp(const expression_t& expr) const;
};
}  // namespace UTAP

#endif /* UTAP_TYPECHECKER_HH */
