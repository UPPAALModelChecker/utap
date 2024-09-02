// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2002-2006 Uppsala University and Aalborg University.
   Copyright (C) 2011-2021 Aalborg University.

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

#include <cassert>

using namespace UTAP;
using std::string;

int32_t EmptyStatement::accept(StatementVisitor& v) { return v.visit_empty_statement(*this); }

bool EmptyStatement::returns() const { return false; }

string EmptyStatement::str(const string&) const { return ""; }

int32_t ExprStatement::accept(StatementVisitor& v) { return v.visit_expr_statement(*this); }

bool ExprStatement::returns() const { return false; }

string ExprStatement::str(const string& prefix) const { return prefix + expr.str() + ";"; }

int32_t AssertStatement::accept(StatementVisitor& v) { return v.visit_assert_statement(*this); }

bool AssertStatement::returns() const { return false; }

string AssertStatement::str(const string& prefix) const { return prefix + "assert(" + expr.str() + ");"; }

ForStatement::ForStatement(expression_t init, expression_t cond, expression_t step, std::unique_ptr<Statement> stat):
    init{std::move(init)}, cond{std::move(cond)}, step{std::move(step)}, stat{std::move(stat)}
{
    assert(this->stat != nullptr);
}

int32_t ForStatement::accept(StatementVisitor& v) { return v.visit_for_statement(*this); }

bool ForStatement::returns() const { return false; }

string ForStatement::str(const string& prefix) const
{
    return prefix + "for (" + init.str() + "; " + cond.str() + "; " + step.str() + ")\n{\n" +
           stat->str(prefix + INDENT) + "}";
}

int32_t IterationStatement::accept(StatementVisitor& v) { return v.visit_iteration_statement(*this); }

bool IterationStatement::returns() const { return false; }

string IterationStatement::str(const string& prefix) const
{
    string type = symbol.get_type()[0].get_label(0);
    return prefix + "for (" + symbol.get_name() + " : " + type  // TODO: to be tested
           + ")\n{\n" + stat->str(prefix + INDENT) + "}";
}

WhileStatement::WhileStatement(expression_t cond, std::unique_ptr<Statement> stat):
    cond{std::move(cond)}, stat{std::move(stat)}
{
    assert(this->stat);
}

int32_t WhileStatement::accept(StatementVisitor& v) { return v.visit_while_statement(*this); }

bool WhileStatement::returns() const { return false; }

string WhileStatement::str(const string& prefix) const
{
    return prefix + "while(" + cond.str() + ")\n" + prefix + "{\n" + stat->str(prefix + INDENT) + prefix + "}";
}

DoWhileStatement::DoWhileStatement(std::unique_ptr<Statement> stat, expression_t cond):
    stat{std::move(stat)}, cond{std::move(cond)}
{
    assert(this->stat);
}

int32_t DoWhileStatement::accept(StatementVisitor& v) { return v.visit_do_while_statement(*this); }

bool DoWhileStatement::returns() const { return stat->returns(); }

string DoWhileStatement::str(const string& prefix) const
{
    return prefix + "do {\n" + stat->str(prefix + INDENT) + prefix + "}";
}

void BlockStatement::push_stat(std::unique_ptr<Statement> stat)
{
    assert(stat != nullptr);
    stats.push_back(std::move(stat));
}

BlockStatement::const_iterator BlockStatement::begin() const { return stats.begin(); }

BlockStatement::const_iterator BlockStatement::end() const { return stats.end(); }

BlockStatement::iterator BlockStatement::begin() { return stats.begin(); }

BlockStatement::iterator BlockStatement::end() { return stats.end(); }

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

int32_t BlockStatement::accept(StatementVisitor& v) { return v.visit_block_statement(*this); }

bool BlockStatement::returns() const { return begin() != end() && back().returns(); }

std::string BlockStatement::str(const std::string& prefix) const
{
    std::string str{};
    for (const auto& st : stats) {
        str += st->str(prefix) + "\n";
    }
    return str;
}

bool ExternalBlockStatement::returns() const { return doesReturn; }

int32_t SwitchStatement::accept(StatementVisitor& v) { return v.visit_switch_statement(*this); }

bool SwitchStatement::returns() const { return false; }

string SwitchStatement::str(const string& prefix) const
{
    return prefix + "switch(" + cond.str() + ")\n" + prefix + "{\n" + BlockStatement::str(prefix + INDENT) + prefix +
           "}";
}

int32_t CaseStatement::accept(StatementVisitor& v) { return v.visit_case_statement(*this); }

bool CaseStatement::returns() const { return false; }

string CaseStatement::str(const string& prefix) const
{
    return prefix + "case " + cond.str() + ":\n" + BlockStatement::str(prefix + INDENT);
}

DefaultStatement::DefaultStatement(const frame_t& frame): BlockStatement{frame} {}

int32_t DefaultStatement::accept(StatementVisitor& v) { return v.visit_default_statement(*this); }

bool DefaultStatement::returns() const { return false; }

IfStatement::IfStatement(expression_t cond, std::unique_ptr<Statement> trueCase, std::unique_ptr<Statement> falseCase):
    cond{std::move(cond)}, trueCase{std::move(trueCase)}, falseCase{std::move(falseCase)}
{
    assert(this->trueCase);
}

int32_t IfStatement::accept(StatementVisitor& v) { return v.visit_if_statement(*this); }

bool IfStatement::returns() const
{
    // This is wrong: An if statement returns *for sure* if both its
    // true and false branches return.
    // return trueCase->returns() && (falseCase == NULL || falseCase->returns());

    return trueCase->returns() && falseCase != nullptr && falseCase->returns();
}

string IfStatement::str(const string& prefix) const
{
    std::string str =
        prefix + "if (" + cond.str() + ")\n" + prefix + "{\n" + trueCase->str(prefix + INDENT) + prefix + "}";
    if (falseCase)
        str += "else {\n" + falseCase->str(prefix + INDENT) + prefix + "}";
    return str;
}

int32_t BreakStatement::accept(StatementVisitor& v) { return v.visit_break_statement(*this); }

bool BreakStatement::returns() const { return false; }

string BreakStatement::str(const string& prefix) const { return prefix + "break;"; }

int32_t ContinueStatement::accept(StatementVisitor& v) { return v.visit_continue_statement(*this); }

bool ContinueStatement::returns() const { return false; }

string ContinueStatement::str(const string& prefix) const { return prefix + "continue;"; }

int32_t ReturnStatement::accept(StatementVisitor& v) { return v.visit_return_statement(*this); }

bool ReturnStatement::returns() const { return true; }

string ReturnStatement::str(const string& prefix) const { return prefix + "return " + value.str() + ";"; }

int32_t AbstractStatementVisitor::visit_statement(Statement&) { return 0; }

int32_t AbstractStatementVisitor::visit_empty_statement(EmptyStatement& stat) { return visit_statement(stat); }

int32_t AbstractStatementVisitor::visit_expr_statement(ExprStatement& stat) { return visit_statement(stat); }

int32_t AbstractStatementVisitor::visit_assert_statement(AssertStatement& stat) { return visit_statement(stat); }

int32_t AbstractStatementVisitor::visit_for_statement(ForStatement& stat) { return stat.stat->accept(*this); }

int32_t AbstractStatementVisitor::visit_iteration_statement(IterationStatement& stat)
{
    return stat.stat->accept(*this);
}

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

void CollectChangesVisitor::visit_expression(expression_t& expr) { expr.collect_possible_writes(changes); }

CollectDependenciesVisitor::CollectDependenciesVisitor(std::set<symbol_t>& dependencies): dependencies(dependencies) {}

void CollectDependenciesVisitor::visit_expression(expression_t& expr) { expr.collect_possible_reads(dependencies); }

void CollectDynamicExpressions::visit_expression(expression_t& expr)
{
    if (expr.is_dynamic() || expr.has_dynamic_sub())
        expressions.push_back(expr);
}
