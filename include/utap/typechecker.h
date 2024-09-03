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
    std::set<Symbol> variables;

public:
    void visit_variable(Variable&) override;
    void visit_instance(instance_t&) override;
    void add_symbol(Symbol);
    bool contains(const Symbol&) const;
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
        TypeError(const Type& type, std::string message): TypeError{type.get_position(), std::move(message), type.str()}
        {}
        TypeError(const Expression& expr, std::string message):
            TypeError{expr.get_position(), std::move(message), expr.str()}
        {}
        TypeError(const Symbol& symbol, std::string message, std::string context):
            TypeError{symbol.get_position(), std::move(message), std::move(context)}
        {}
    };

    explicit TypeChecker(Document& doc, bool refinement = false);
    void visit_doc_after(Document&) override;
    void visit_template_after(template_t&) override;
    bool visit_template_before(template_t&) override;
    void visit_variable(Variable&) override;
    void visit_location(location_t&) override;
    void visit_edge(edge_t&) override;
    void visit_instance(instance_t&) override;
    virtual void visitProperty(Expression&);  // FIXME: does not override?!
    void visit_function(function_t&) override;
    void visit_progress(progress_t&) override;
    virtual void visitHybridClock(Expression&);  // FIXME: does not override?!
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
    int32_t visit_iteration_statement(RangeStatement& stat) override;
    int32_t visit_while_statement(WhileStatement& stat) override;
    int32_t visit_do_while_statement(DoWhileStatement& stat) override;
    int32_t visit_block_statement(BlockStatement& stat) override;
    int32_t visit_if_statement(IfStatement& stat) override;
    int32_t visit_return_statement(ReturnStatement& stat) override;

    bool checkDynamicExpressions(Statement& stat);
    /** Type check an expression */
    bool checkExpression(Expression&);
    bool checkSpawnParameterCompatible(const Type& param, const Expression& arg);

private:
    int syncUsed{0};  // Keep track of sync declarations, 0->nothing, 1->IO, 2->CSP, -1->error.
    const template_t* temp{nullptr};
    Document& document;
    mutable CompileTimeComputableValues compileTimeComputableValues;
    function_t* function{nullptr}; /**< Current function being type checked. */
    bool refinementWarnings;

    void handleError(TypeError error);
    void handleWarning(TypeError error);

    Expression checkInitialiser(const Type& type, const Expression& init);
    Type getInlineIfCommonType(const Type& t1, const Type& t2) const;
    bool isLValue(const Expression&) const;
    bool isModifiableLValue(const Expression&) const;
    bool isUniqueReference(const Expression& expr) const;
    bool isParameterCompatible(const Type& param, const Expression& arg) const;
    bool checkParameterCompatible(const Type& param, const Expression& arg);
    void checkIgnoredValue(const Expression& expr);
    bool checkAssignmentExpression(Expression&);
    bool checkConditionalExpressionInFunction(const Expression&);
    void checkObservationConstraints(const Expression&);

    bool isCompileTimeComputable(const Expression& expr) const;
    void checkType(const Type&, bool initialisable = false, bool inStruct = false);

    /** check expressions used in (SMC) properties, these functions provide:
        1) consistent semantic checks by code reuse,
        2) meaningful names to the otherwise anonymous expressions.
     */
    bool checkNrOfRuns(const Expression& expr);
    bool checkBoundTypeOrBoundedExpr(const Expression& expr);
    bool checkBound(const Expression& expr);
    bool checkPredicate(const Expression& expr);
    bool checkProbBound(const Expression& expr);
    bool checkUntilCond(Constants::kind_t kind, const Expression& expr);
    bool checkMonitoredExpr(const Expression& expr);
    bool checkPathQuant(const Expression& expr);
    bool checkAggregationOp(const Expression& expr);
};
}  // namespace UTAP

#endif /* UTAP_TYPECHECKER_HH */
