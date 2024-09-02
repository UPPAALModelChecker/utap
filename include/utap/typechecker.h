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
    void visit_variable(variable_t&) override;
    void visit_instance(instance_t&) override;
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
public:
    struct TypeError
    {
        position_t position;
        std::string message, context;
        TypeError(const position_t& position, std::string message, std::string context):
            position{position}, message{std::move(message)}, context{std::move(context)}
        {}
        TypeError(const type_t& type, std::string message):
            TypeError{type.get_position(), std::move(message), type.str()}
        {}
        TypeError(const expression_t& expr, std::string message):
            TypeError{expr.get_position(), std::move(message), expr.str()}
        {}
        TypeError(const symbol_t& symbol, std::string message, std::string context):
            TypeError{symbol.get_position(), std::move(message), std::move(context)}
        {}
    };

    explicit TypeChecker(Document& doc, bool refinement = false);
    void visit_doc_after(Document&) override;
    void visit_template_after(template_t&) override;
    bool visit_template_before(template_t&) override;
    void visit_variable(variable_t&) override;
    void visit_location(location_t&) override;
    void visit_edge(edge_t&) override;
    void visit_instance(instance_t&) override;
    virtual void visitProperty(expression_t&);  // FIXME: does not override?!
    void visit_function(function_t&) override;
    void visit_progress(progress_t&) override;
    virtual void visitHybridClock(expression_t&);  // FIXME: does not override?!
    void visit_io_decl(iodecl_t&) override;
    void visit_gantt(gantt_t&) override;
    void visit_process(instance_t&) override;
    void visit_instance_line(instance_line_t&) override;
    void visit_message(message_t&) override;
    void visit_condition(condition_t&) override;
    void visit_update(update_t&) override;
    int32_t visit_empty_statement(EmptyStatement& stat) override;
    int32_t visit_expr_statement(ExprStatement& stat) override;
    int32_t visit_assert_statement(AssertStatement& stat) override;
    int32_t visit_for_statement(ForStatement& stat) override;
    int32_t visit_iteration_statement(IterationStatement& stat) override;
    int32_t visit_while_statement(WhileStatement& stat) override;
    int32_t visit_do_while_statement(DoWhileStatement& stat) override;
    int32_t visit_block_statement(BlockStatement& stat) override;
    int32_t visit_if_statement(IfStatement& stat) override;
    int32_t visit_return_statement(ReturnStatement& stat) override;

    bool checkDynamicExpressions(Statement& stat);
    /** Type check an expression */
    bool checkExpression(expression_t&);
    bool checkSpawnParameterCompatible(const type_t& param, const expression_t& arg);

private:
    int syncUsed{0};  // Keep track of sync declarations, 0->nothing, 1->IO, 2->CSP, -1->error.
    const template_t* temp{nullptr};
    Document& document;
    mutable CompileTimeComputableValues compileTimeComputableValues;
    function_t* function{nullptr}; /**< Current function being type checked. */
    bool refinementWarnings;

    void handleError(TypeError error);
    void handleWarning(TypeError error);

    expression_t checkInitialiser(const type_t& type, const expression_t& init);
    type_t getInlineIfCommonType(const type_t& t1, const type_t& t2) const;
    bool isLValue(const expression_t&) const;
    bool isModifiableLValue(const expression_t&) const;
    bool isUniqueReference(const expression_t& expr) const;
    bool isParameterCompatible(const type_t& param, const expression_t& arg) const;
    bool checkParameterCompatible(const type_t& param, const expression_t& arg);
    void checkIgnoredValue(const expression_t& expr);
    bool checkAssignmentExpression(expression_t&);
    bool checkConditionalExpressionInFunction(const expression_t&);
    void checkObservationConstraints(const expression_t&);

    bool isCompileTimeComputable(const expression_t& expr) const;
    void checkType(const type_t&, bool initialisable = false, bool inStruct = false);

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
}  // namespace UTAP

#endif /* UTAP_TYPECHECKER_HH */
