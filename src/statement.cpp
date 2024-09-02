// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2002-2006 Uppsala University and Aalborg University.
   Copyright (C) 2011-2024 Aalborg University.

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

#include "utap/statement.h"

#include <iostream>
#include <sstream>
#include <cassert>

using namespace UTAP;

std::string Statement::to_string(const std::string& indent) const
{
    auto os = std::ostringstream{};
    print(os, indent);
    return os.str();
}

std::ostream& EmptyStatement::print(std::ostream& os, const std::string&) const { return os; }

std::ostream& ExprStatement::print(std::ostream& os, const std::string& indent) const
{
    return expr.print(os << indent) << ";";
}

std::ostream& AssertStatement::print(std::ostream& os, const std::string& indent) const
{
    return expr.print(os << indent << "assert(") << ");";
}

ForStatement::ForStatement(expression_t init, expression_t cond, expression_t step, std::unique_ptr<Statement> stat):
    init{std::move(init)}, cond{std::move(cond)}, step{std::move(step)}, stat{std::move(stat)}
{
    assert(this->stat != nullptr);
}

std::ostream& ForStatement::print(std::ostream& os, const std::string& indent) const
{
    init.print(os << indent << "for (") << "; ";
    cond.print(os) << "; ";
    step.print(os) << ")\n";
    return stat->print(os, indent + INDENT) << "\n";
}

std::ostream& RangeStatement::print(std::ostream& os, const std::string& indent) const
{
    auto t = symbol.get_type();
    auto [l, u] = t.get_range();
    os << indent << "for (" << symbol.get_name() << " : int[" << l.get_value() << "," << u.get_value() << "])\n";
    return stat->print(os, indent + INDENT) << "\n";
}

WhileStatement::WhileStatement(expression_t cond, std::unique_ptr<Statement> stat):
    cond{std::move(cond)}, stat{std::move(stat)}
{
    assert(this->stat != nullptr);
}

std::ostream& WhileStatement::print(std::ostream& os, const std::string& indent) const
{
    cond.print(os << indent << "while(") << ") {\n";
    return stat->print(os, indent + INDENT) << indent << "}";
}

DoWhileStatement::DoWhileStatement(std::unique_ptr<Statement> stat, expression_t cond):
    stat{std::move(stat)}, cond{std::move(cond)}
{
    assert(this->stat != nullptr);
}

std::ostream& DoWhileStatement::print(std::ostream& os, const std::string& indent) const
{
    os << indent << "do {\n";
    return stat->print(os, indent + INDENT) << indent << "}";
}

void BlockStatement::push_stat(std::unique_ptr<Statement> stat)
{
    assert(stat != nullptr);
    stats.push_back(std::move(stat));
}

Statement& BlockStatement::back()
{
    assert(!stats.empty());
    return *stats.back();
}

const Statement& BlockStatement::back() const
{
    assert(!stats.empty());
    return *stats.back();
}

std::unique_ptr<Statement> BlockStatement::pop_stat()
{
    std::unique_ptr<Statement> st = std::move(stats.back());
    stats.pop_back();
    return st;
}

std::ostream& BlockStatement::print(std::ostream& os, const std::string& indent) const
{
    os << indent << "{\n";
    for (const auto& st : stats)
        st->print(os, indent + INDENT) << "\n";
    return os << indent << "}\n";
}

std::ostream& SwitchStatement::print(std::ostream& os, const std::string& indent) const
{
    os << indent << "switch(";
    cond.print(os) << ") {\n";
    return BlockStatement::print(os, indent + INDENT) << indent << "}";
}

std::ostream& CaseStatement::print(std::ostream& os, const std::string& indent) const
{
    os << indent << "case ";
    cond.print(os) << ":\n";
    return BlockStatement::print(os, indent + INDENT);
}

std::ostream& DefaultStatement::print(std::ostream& os, const std::string& indent) const
{
    os << indent << "default:\n";
    return BlockStatement::print(os, indent + INDENT);
}

IfStatement::IfStatement(expression_t cond, std::unique_ptr<Statement> trueCase, std::unique_ptr<Statement> falseCase):
    cond{std::move(cond)}, trueCase{std::move(trueCase)}, falseCase{std::move(falseCase)}
{
    assert(this->trueCase);
}

std::ostream& IfStatement::print(std::ostream& os, const std::string& indent) const
{
    os << indent << "if (";
    cond.print(os) << ") {\n";
    trueCase->print(os, indent + INDENT) << indent << "}";
    if (falseCase) {
        os << " else {\n";
        falseCase->print(os, indent + INDENT) << indent << "}";
    }
    return os;
}

std::ostream& BreakStatement::print(std::ostream& os, const std::string& indent) const
{
    return os << indent << "break;";
}

std::ostream& ContinueStatement::print(std::ostream& os, const std::string& indent) const
{
    return os << indent << "continue;";
}

std::ostream& ReturnStatement::print(std::ostream& os, const std::string& prefix) const
{
    return value.print(os << "return ") << ";";
}

int32_t AbstractStatementVisitor::visit_statement(Statement&) { return 0; }

int32_t AbstractStatementVisitor::visit_empty_statement(EmptyStatement& stat) { return visit_statement(stat); }

int32_t AbstractStatementVisitor::visit_expr_statement(ExprStatement& stat) { return visit_statement(stat); }

int32_t AbstractStatementVisitor::visit_assert_statement(AssertStatement& stat) { return visit_statement(stat); }

int32_t AbstractStatementVisitor::visit_for_statement(ForStatement& stat) { return stat.stat->accept(*this); }

int32_t AbstractStatementVisitor::visit_iteration_statement(RangeStatement& stat) { return stat.stat->accept(*this); }

int32_t AbstractStatementVisitor::visit_while_statement(WhileStatement& stat) { return stat.stat->accept(*this); }

int32_t AbstractStatementVisitor::visit_do_while_statement(DoWhileStatement& stat) { return stat.stat->accept(*this); }

int32_t AbstractStatementVisitor::visit_block_statement(BlockStatement& stat)
{
    int result = 0;
    for (const auto& statement : stat)
        result = statement->accept(*this);
    return result;
}

int32_t AbstractStatementVisitor::visit_switch_statement(SwitchStatement& stat) { return visit_block_statement(stat); }

int32_t AbstractStatementVisitor::visit_case_statement(CaseStatement& stat) { return visit_block_statement(stat); }

int32_t AbstractStatementVisitor::visit_default_statement(DefaultStatement& stat)
{
    return visit_block_statement(stat);
}

int32_t AbstractStatementVisitor::visit_if_statement(IfStatement& stat)
{
    if (stat.falseCase) {
        stat.trueCase->accept(*this);
        return stat.falseCase->accept(*this);
    } else {
        return stat.trueCase->accept(*this);
    }
}

int32_t AbstractStatementVisitor::visit_break_statement(BreakStatement& stat) { return visit_statement(stat); }

int32_t AbstractStatementVisitor::visit_continue_statement(ContinueStatement& stat) { return visit_statement(stat); }

int32_t AbstractStatementVisitor::visit_return_statement(ReturnStatement& stat) { return visit_statement(stat); }

int32_t ExpressionVisitor::visit_expr_statement(ExprStatement& stat)
{
    visit_expression(stat.expr);
    return 0;
}

int32_t ExpressionVisitor::visit_assert_statement(AssertStatement& stat)
{
    visit_expression(stat.expr);
    return 0;
}

int32_t ExpressionVisitor::visit_for_statement(ForStatement& stat)
{
    visit_expression(stat.init);
    visit_expression(stat.cond);
    visit_expression(stat.step);
    return stat.stat->accept(*this);
}

int32_t ExpressionVisitor::visit_while_statement(WhileStatement& stat)
{
    visit_expression(stat.cond);
    return stat.stat->accept(*this);
}

int32_t ExpressionVisitor::visit_do_while_statement(DoWhileStatement& stat)
{
    visit_expression(stat.cond);
    return stat.stat->accept(*this);
}

int32_t ExpressionVisitor::visit_block_statement(BlockStatement& stat)
{
    // Visit variable initialisers.
    for (symbol_t& symbol : stat.get_frame()) {
        if (auto* data = symbol.get_data(); data) {
            // REVISIT: This will only work if vars[i] is a variable!
            visit_expression(static_cast<variable_t*>(data)->init);
        }
    }
    // Visit statements.
    for (const auto& s : stat)
        s->accept(*this);
    return 0;
}

int32_t ExpressionVisitor::visit_switch_statement(SwitchStatement& stat)
{
    visit_expression(stat.cond);
    return visit_block_statement(stat);
}

int32_t ExpressionVisitor::visit_case_statement(CaseStatement& stat)
{
    visit_expression(stat.cond);
    return visit_block_statement(stat);
}

int32_t ExpressionVisitor::visit_default_statement(DefaultStatement& stat) { return visit_block_statement(stat); }

int32_t ExpressionVisitor::visit_if_statement(IfStatement& stat)
{
    visit_expression(stat.cond);
    stat.trueCase->accept(*this);
    if (stat.falseCase) {
        stat.falseCase->accept(*this);
    }
    return 0;
}

int32_t ExpressionVisitor::visit_return_statement(ReturnStatement& stat)
{
    visit_expression(stat.value);
    return 0;
}

class CollectChangesVisitor final : public ExpressionVisitor
{
protected:
    void visit_expression(expression_t& expr) override { expr.collect_possible_writes(changes); }

public:
    std::set<symbol_t> changes;
    CollectChangesVisitor() = default;
};

std::set<symbol_t> UTAP::collect_changes(Statement& stat)
{
    auto visitor = CollectChangesVisitor{};
    stat.accept(visitor);
    return std::move(visitor.changes);
}

class CollectDependenciesVisitor final : public ExpressionVisitor
{
protected:
    void visit_expression(expression_t& expr) override { expr.collect_possible_reads(dependencies); }

public:
    std::set<symbol_t> dependencies;
    CollectDependenciesVisitor() = default;
};

std::set<symbol_t> UTAP::collect_dependencies(Statement& stat)
{
    auto visitor = CollectDependenciesVisitor{};
    stat.accept(visitor);
    return std::move(visitor.dependencies);
}

class CollectDynamicExpressions final : public ExpressionVisitor
{
protected:
    void visit_expression(expression_t& expr) override
    {
        if (expr.is_dynamic() || expr.has_dynamic_sub())
            expressions.push_back(expr);
    }

public:
    std::vector<expression_t> expressions;
    CollectDynamicExpressions() = default;
};

std::vector<expression_t> UTAP::collect_dynamic_expressions(Statement& stat)
{
    auto visitor = CollectDynamicExpressions{};
    stat.accept(visitor);
    return std::move(visitor.expressions);
}
