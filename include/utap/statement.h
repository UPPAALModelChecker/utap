// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-

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

#ifndef UTAP_STATEMENT_H
#define UTAP_STATEMENT_H

#include "utap/document.h"
#include "utap/expression.h"
#include "utap/symbols.h"

#define INDENT "\t"

namespace UTAP {
class StatementVisitor;

class Statement
{
public:
    virtual ~Statement() noexcept = default;
    virtual int32_t accept(StatementVisitor* visitor) = 0;
    virtual bool returns() = 0;
    virtual std::string str(const std::string& prefix) const = 0;

protected:
    Statement() = default;
};

class EmptyStatement : public Statement
{
public:
    EmptyStatement() = default;
    int32_t accept(StatementVisitor* visitor) override;
    bool returns() override;
    std::string str(const std::string& prefix) const override;
};

class ExprStatement : public Statement
{
public:
    expression_t expr;
    explicit ExprStatement(expression_t expr): expr{std::move(expr)} {}
    int32_t accept(StatementVisitor* visitor) override;
    bool returns() override;
    std::string str(const std::string& prefix) const override;
};

class AssertStatement : public Statement
{
public:
    expression_t expr;
    explicit AssertStatement(expression_t expr): expr{std::move(expr)} {}
    int32_t accept(StatementVisitor* visitor) override;
    bool returns() override;
    std::string str(const std::string& prefix) const override;
};

class ForStatement : public Statement
{
public:
    expression_t init;
    expression_t cond;
    expression_t step;
    std::unique_ptr<Statement> stat;
    ForStatement(expression_t, expression_t, expression_t, std::unique_ptr<Statement>);
    int32_t accept(StatementVisitor* visitor) override;
    bool returns() override;
    std::string str(const std::string& prefix) const override;
};

/**
 * Statement class for the iterator loop-construction.
 */
class IterationStatement : public Statement
{
protected:
    frame_t frame;

public:
    symbol_t symbol;
    std::unique_ptr<Statement> stat;
    IterationStatement(symbol_t symbol, frame_t frame, std::unique_ptr<Statement> statement):
        frame{std::move(frame)}, symbol{std::move(symbol)}, stat{std::move(statement)}
    {}
    frame_t get_frame() { return frame; }
    int32_t accept(StatementVisitor* visitor) override;
    bool returns() override;
    std::string str(const std::string& prefix) const override;
};

class WhileStatement : public Statement
{
public:
    expression_t cond;
    std::unique_ptr<Statement> stat;
    WhileStatement(expression_t, std::unique_ptr<Statement>);
    int32_t accept(StatementVisitor* visitor) override;
    bool returns() override;
    std::string str(const std::string& prefix) const override;
};

class DoWhileStatement : public Statement
{
public:
    std::unique_ptr<Statement> stat;
    expression_t cond;
    DoWhileStatement(std::unique_ptr<Statement>, expression_t);
    int32_t accept(StatementVisitor* visitor) override;
    bool returns() override;
    std::string str(const std::string& prefix) const override;
};

class BlockStatement : public Statement, public declarations_t
{
public:
    using const_iterator = std::vector<std::unique_ptr<Statement>>::const_iterator;
    using iterator = std::vector<std::unique_ptr<Statement>>::iterator;

protected:
    std::vector<std::unique_ptr<Statement>> stats;
    frame_t frame;

public:
    explicit BlockStatement(frame_t frame): frame{std::move(frame)} {}
    int32_t accept(StatementVisitor* visitor) override;
    bool returns() override;

    frame_t get_frame() { return frame; }
    void push(std::unique_ptr<Statement> stat);
    template <typename SomeStatement, typename... Args>
    void emplace(Args&&... args)
    {
        static_assert(std::is_base_of_v<Statement, SomeStatement>, "Should implement Statement");
        push(std::make_unique<SomeStatement>(std::forward<Args>(args)...));
    }
    std::unique_ptr<Statement> pop();
    Statement* back();
    const_iterator begin() const;
    const_iterator end() const;
    bool empty() const { return stats.empty(); }
    iterator begin();
    iterator end();
    std::string str(const std::string& prefix) const override;
};

class ExternalBlockStatement : public BlockStatement
{
public:
    ExternalBlockStatement(frame_t frame, void* fp, bool ret): BlockStatement{frame}, functionptr{fp}, doesReturn{ret}
    {}
    bool returns() override;
    void* getFP() { return functionptr; }

private:
    void* functionptr;
    bool doesReturn;
};

class SwitchStatement : public BlockStatement
{
public:
    expression_t cond;
    SwitchStatement(frame_t frame, expression_t expr): BlockStatement{std::move(frame)}, cond{std::move(expr)} {}
    int32_t accept(StatementVisitor* visitor) override;
    bool returns() override;
    std::string str(const std::string& prefix) const override;
};

class CaseStatement : public BlockStatement
{
public:
    expression_t cond;
    CaseStatement(frame_t frame, expression_t expr): BlockStatement{std::move(frame)}, cond{std::move(expr)} {}
    int32_t accept(StatementVisitor* visitor) override;
    bool returns() override;
    std::string str(const std::string& prefix) const override;
};

class DefaultStatement : public BlockStatement
{
public:
    explicit DefaultStatement(frame_t);
    int32_t accept(StatementVisitor* visitor) override;
    bool returns() override;
};

class IfStatement : public Statement
{
public:
    expression_t cond;
    std::unique_ptr<Statement> trueCase;
    std::unique_ptr<Statement> falseCase;
    IfStatement(expression_t, std::unique_ptr<Statement>, std::unique_ptr<Statement> falseStat = nullptr);
    int32_t accept(StatementVisitor* visitor) override;
    bool returns() override;
    std::string str(const std::string& prefix) const override;
};

class BreakStatement : public Statement
{
public:
    BreakStatement() = default;
    int32_t accept(StatementVisitor* visitor) override;
    bool returns() override;
    std::string str(const std::string& prefix) const override;
};

class ContinueStatement : public Statement
{
public:
    ContinueStatement() = default;
    int32_t accept(StatementVisitor* visitor) override;
    bool returns() override;
    std::string str(const std::string& prefix) const override;
};

class ReturnStatement : public Statement
{
public:
    expression_t value;
    ReturnStatement() = default;
    explicit ReturnStatement(expression_t expr): value{std::move(expr)} {}
    int32_t accept(StatementVisitor* visitor) override;
    bool returns() override;
    std::string str(const std::string& prefix) const override;
};

class StatementVisitor
{
public:
    virtual ~StatementVisitor() noexcept = default;
    virtual int32_t visitEmptyStatement(EmptyStatement* stat) = 0;
    virtual int32_t visitExprStatement(ExprStatement* stat) = 0;
    virtual int32_t visitAssertStatement(AssertStatement* stat) = 0;
    virtual int32_t visitForStatement(ForStatement* stat) = 0;
    virtual int32_t visitIterationStatement(IterationStatement* stat) = 0;
    virtual int32_t visitWhileStatement(WhileStatement* stat) = 0;
    virtual int32_t visitDoWhileStatement(DoWhileStatement* stat) = 0;
    virtual int32_t visitBlockStatement(BlockStatement* stat) = 0;
    virtual int32_t visitSwitchStatement(SwitchStatement* stat) = 0;
    virtual int32_t visitCaseStatement(CaseStatement* stat) = 0;
    virtual int32_t visitDefaultStatement(DefaultStatement* stat) = 0;
    virtual int32_t visitIfStatement(IfStatement* stat) = 0;
    virtual int32_t visitBreakStatement(BreakStatement* stat) = 0;
    virtual int32_t visitContinueStatement(ContinueStatement* stat) = 0;
    virtual int32_t visitReturnStatement(ReturnStatement* stat) = 0;
};

class AbstractStatementVisitor : public StatementVisitor
{
protected:
    virtual int32_t visitStatement(Statement* stat);

public:
    int32_t visitEmptyStatement(EmptyStatement* stat) override;
    int32_t visitExprStatement(ExprStatement* stat) override;
    int32_t visitAssertStatement(AssertStatement* stat) override;
    int32_t visitForStatement(ForStatement* stat) override;
    int32_t visitIterationStatement(IterationStatement* stat) override;
    int32_t visitWhileStatement(WhileStatement* stat) override;
    int32_t visitDoWhileStatement(DoWhileStatement* stat) override;
    int32_t visitBlockStatement(BlockStatement* stat) override;
    int32_t visitSwitchStatement(SwitchStatement* stat) override;
    int32_t visitCaseStatement(CaseStatement* stat) override;
    int32_t visitDefaultStatement(DefaultStatement* stat) override;
    int32_t visitIfStatement(IfStatement* stat) override;
    int32_t visitBreakStatement(BreakStatement* stat) override;
    int32_t visitContinueStatement(ContinueStatement* stat) override;
    int32_t visitReturnStatement(ReturnStatement* stat) override;
};

class ExpressionVisitor : public AbstractStatementVisitor
{
protected:
    virtual void visitExpression(expression_t&) = 0;

public:
    int32_t visitExprStatement(ExprStatement* stat) override;
    int32_t visitAssertStatement(AssertStatement* stat) override;
    int32_t visitIfStatement(IfStatement* stat) override;
    int32_t visitForStatement(ForStatement* stat) override;
    int32_t visitWhileStatement(WhileStatement* stat) override;
    int32_t visitDoWhileStatement(DoWhileStatement* stat) override;
    int32_t visitSwitchStatement(SwitchStatement* stat) override;
    int32_t visitBlockStatement(BlockStatement* stat) override;
    int32_t visitCaseStatement(CaseStatement* stat) override;
    int32_t visitDefaultStatement(DefaultStatement* stat) override;
    int32_t visitReturnStatement(ReturnStatement* stat) override;
};

/// Collects all symbols that the visited statement may be potentially depend on (for reading)
class PotentialDependencyCollector : public ExpressionVisitor
{
protected:
    void visitExpression(expression_t& expr) override { expr.collect_potential_reads(dependencies); }
    std::set<symbol_t>& dependencies;

public:
    explicit PotentialDependencyCollector(std::set<symbol_t>& deps): dependencies{deps} {}
};

inline std::set<symbol_t> collect_potential_dependencies(Statement& statement)
{
    auto res = std::set<symbol_t>{};
    auto visitor = PotentialDependencyCollector{res};
    statement.accept(&visitor);
    return res;
}

/// Collects all symbols that may be changed (written to) by the visited statement
class PotentialChangeCollector : public ExpressionVisitor
{
protected:
    void visitExpression(expression_t& expr) override { expr.collect_potential_writes(changes); }
    std::set<symbol_t>& changes;

public:
    explicit PotentialChangeCollector(std::set<symbol_t>& changes): changes{changes} {}
};

inline std::set<symbol_t> collect_potential_changes(Statement& statement)
{
    auto res = std::set<symbol_t>{};
    auto visitor = PotentialChangeCollector{res};
    statement.accept(&visitor);
    return res;
}

/// Collects symbols that the visited statement surely (always) depend on (for reading)
class SureDependencyCollector : public ExpressionVisitor
{
protected:
    void visitExpression(expression_t& expr) override { expr.collect_sure_reads(dependencies); }
    std::set<symbol_t>& dependencies;

public:
    explicit SureDependencyCollector(std::set<symbol_t>& deps): dependencies{deps} {}
};

inline std::set<symbol_t> collect_sure_dependencies(Statement& statement)
{
    auto res = std::set<symbol_t>{};
    auto visitor = SureDependencyCollector{res};
    statement.accept(&visitor);
    return res;
}

/// Collects symbols that are surely (always) changed by the visited statements
class SureChangeCollector : public ExpressionVisitor
{
protected:
    void visitExpression(expression_t& expr) override { expr.collect_sure_writes(changes); }
    std::set<symbol_t>& changes;

public:
    explicit SureChangeCollector(std::set<symbol_t>& changes): changes{changes} {}
    int32_t visitIfStatement(IfStatement* stat) override
    {
        visitExpression(stat->cond);
        // TODO: visit trueCase or falseCase if cond known at compile-time
        return 0;
    }
    int32_t visitForStatement(ForStatement* stat) override
    {
        visitExpression(stat->init);
        visitExpression(stat->cond);
        // TODO: visit step and block if cond is known at compile-time
        return 0;
    }
    int32_t visitWhileStatement(WhileStatement* stat) override
    {
        visitExpression(stat->cond);
        // TODO: visit step and block if cond is known at compile-time
        return 0;
    }
    int32_t visitDoWhileStatement(DoWhileStatement* stat) override
    {
        auto res = stat->stat->accept(this);
        visitExpression(stat->cond);
        return res;
    }
    int32_t visitSwitchStatement(SwitchStatement* stat) override
    {
        visitExpression(stat->cond);
        // TODO: visit specific case if cond is known at compile-time
        return 0;
    }
};

inline std::set<symbol_t> collect_sure_changes(Statement& statement)
{
    auto res = std::set<symbol_t>{};
    auto visitor = SureChangeCollector{res};
    statement.accept(&visitor);
    return res;
}

class DynamicExprCollector final : public ExpressionVisitor
{
protected:
    void visitExpression(expression_t& expr) override
    {
        if (expr.is_dynamic() || expr.has_dynamic_sub())
            expressions.push_back(expr);
    }
    std::vector<expression_t>& expressions;

public:
    explicit DynamicExprCollector(std::vector<expression_t>& expressions): expressions{expressions} {}
};

inline std::vector<expression_t> collect_dynamic_expressions(Statement& statement)
{
    auto res = std::vector<expression_t>{};
    auto visitor = DynamicExprCollector{res};
    statement.accept(&visitor);
    return res;
}

}  // namespace UTAP
#endif /* UTAP_STATEMENT_H */
