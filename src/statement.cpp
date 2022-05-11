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

int32_t EmptyStatement::accept(StatementVisitor* visitor) { return visitor->visitEmptyStatement(this); }

bool EmptyStatement::returns() { return false; }

string EmptyStatement::toString(const string& prefix) const { return ""; }

int32_t ExprStatement::accept(StatementVisitor* visitor) { return visitor->visitExprStatement(this); }

bool ExprStatement::returns() { return false; }

string ExprStatement::toString(const string& prefix) const { return prefix + expr.toString() + ";"; }

int32_t AssertStatement::accept(StatementVisitor* visitor) { return visitor->visitAssertStatement(this); }

bool AssertStatement::returns() { return false; }

string AssertStatement::toString(const string& prefix) const { return prefix + "assert(" + expr.toString() + ");"; }

ForStatement::ForStatement(expression_t init, expression_t cond, expression_t step, std::unique_ptr<Statement> stat):
    init{std::move(init)}, cond{std::move(cond)}, step{std::move(step)}, stat{std::move(stat)}
{
    assert(this->stat != nullptr);
}

int32_t ForStatement::accept(StatementVisitor* visitor) { return visitor->visitForStatement(this); }

bool ForStatement::returns() { return false; }

string ForStatement::toString(const string& prefix) const
{
    return prefix + "for (" + init.toString() + "; " + cond.toString() + "; " + step.toString() + ")\n{\n" +
           stat->toString(prefix + INDENT) + "}";
}

int32_t IterationStatement::accept(StatementVisitor* visitor) { return visitor->visitIterationStatement(this); }

bool IterationStatement::returns() { return false; }

string IterationStatement::toString(const string& prefix) const
{
    string type = symbol.getType()[0].getLabel(0);
    return prefix + "for (" + symbol.getName() + " : " + type  // TODO: to be tested
           + ")\n{\n" + stat->toString(prefix + INDENT) + "}";
}

WhileStatement::WhileStatement(expression_t cond, std::unique_ptr<Statement> stat):
    cond{std::move(cond)}, stat{std::move(stat)}
{
    assert(this->stat);
}

int32_t WhileStatement::accept(StatementVisitor* visitor) { return visitor->visitWhileStatement(this); }

bool WhileStatement::returns() { return false; }

string WhileStatement::toString(const string& prefix) const
{
    return prefix + "while(" + cond.toString() + ")\n" + prefix + "{\n" + stat->toString(prefix + INDENT) + prefix +
           "}";
}

DoWhileStatement::DoWhileStatement(std::unique_ptr<Statement> stat, expression_t cond):
    stat{std::move(stat)}, cond{std::move(cond)}
{
    assert(this->stat);
}

int32_t DoWhileStatement::accept(StatementVisitor* visitor) { return visitor->visitDoWhileStatement(this); }

bool DoWhileStatement::returns() { return stat->returns(); }

string DoWhileStatement::toString(const string& prefix) const
{
    return prefix + "do {\n" + stat->toString(prefix + INDENT) + prefix + "}";
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

Statement* BlockStatement::back()
{
    assert(!stats.empty());
    return stats.back().get();
}

std::unique_ptr<Statement> BlockStatement::pop_stat()
{
    std::unique_ptr<Statement> st = std::move(stats.back());
    stats.pop_back();
    return st;
}

int32_t BlockStatement::accept(StatementVisitor* visitor) { return visitor->visitBlockStatement(this); }

bool BlockStatement::returns() { return begin() != end() && back()->returns(); }

std::string BlockStatement::toString(const std::string& prefix) const
{
    std::string str{};
    for (const auto& st : stats) {
        str += st->toString(prefix) + "\n";
    }
    return str;
}

bool ExternalBlockStatement::returns() { return doesReturn; }

int32_t SwitchStatement::accept(StatementVisitor* visitor) { return visitor->visitSwitchStatement(this); }

bool SwitchStatement::returns() { return false; }

string SwitchStatement::toString(const string& prefix) const
{
    return prefix + "switch(" + cond.toString() + ")\n" + prefix + "{\n" + BlockStatement::toString(prefix + INDENT) +
           prefix + "}";
}

int32_t CaseStatement::accept(StatementVisitor* visitor) { return visitor->visitCaseStatement(this); }

bool CaseStatement::returns() { return false; }

string CaseStatement::toString(const string& prefix) const
{
    return prefix + "case " + cond.toString() + ":\n" + BlockStatement::toString(prefix + INDENT);
}

DefaultStatement::DefaultStatement(frame_t frame): BlockStatement{std::move(frame)} {}

int32_t DefaultStatement::accept(StatementVisitor* visitor) { return visitor->visitDefaultStatement(this); }

bool DefaultStatement::returns() { return false; }

IfStatement::IfStatement(expression_t cond, std::unique_ptr<Statement> trueCase, std::unique_ptr<Statement> falseCase):
    cond{std::move(cond)}, trueCase{std::move(trueCase)}, falseCase{std::move(falseCase)}
{
    assert(this->trueCase);
}

int32_t IfStatement::accept(StatementVisitor* visitor) { return visitor->visitIfStatement(this); }

bool IfStatement::returns()
{
    // This is wrong: An if statement returns *for sure* if both its
    // true and false branches return.
    // return trueCase->returns() && (falseCase == NULL || falseCase->returns());

    return trueCase->returns() && falseCase != nullptr && falseCase->returns();
}

string IfStatement::toString(const string& prefix) const
{
    std::string str =
        prefix + "if (" + cond.toString() + ")\n" + prefix + "{\n" + trueCase->toString(prefix + INDENT) + prefix + "}";
    if (falseCase)
        str += "else {\n" + falseCase->toString(prefix + INDENT) + prefix + "}";
    return str;
}

int32_t BreakStatement::accept(StatementVisitor* visitor) { return visitor->visitBreakStatement(this); }

bool BreakStatement::returns() { return false; }

string BreakStatement::toString(const string& prefix) const { return prefix + "break;"; }

int32_t ContinueStatement::accept(StatementVisitor* visitor) { return visitor->visitContinueStatement(this); }

bool ContinueStatement::returns() { return false; }

string ContinueStatement::toString(const string& prefix) const { return prefix + "continue;"; }

int32_t ReturnStatement::accept(StatementVisitor* visitor) { return visitor->visitReturnStatement(this); }

bool ReturnStatement::returns() { return true; }

string ReturnStatement::toString(const string& prefix) const { return prefix + "return " + value.toString() + ";"; }

int32_t AbstractStatementVisitor::visitStatement(Statement* stat) { return 0; }

int32_t AbstractStatementVisitor::visitEmptyStatement(EmptyStatement* stat) { return visitStatement(stat); }

int32_t AbstractStatementVisitor::visitExprStatement(ExprStatement* stat) { return visitStatement(stat); }

int32_t AbstractStatementVisitor::visitAssertStatement(AssertStatement* stat) { return visitStatement(stat); }

int32_t AbstractStatementVisitor::visitForStatement(ForStatement* stat) { return stat->stat->accept(this); }

int32_t AbstractStatementVisitor::visitIterationStatement(IterationStatement* stat) { return stat->stat->accept(this); }

int32_t AbstractStatementVisitor::visitWhileStatement(WhileStatement* stat) { return stat->stat->accept(this); }

int32_t AbstractStatementVisitor::visitDoWhileStatement(DoWhileStatement* stat) { return stat->stat->accept(this); }

int32_t AbstractStatementVisitor::visitBlockStatement(BlockStatement* stat)
{
    int result = 0;
    for (auto& statement : *stat) {
        result = statement->accept(this);
    }
    return result;
}

int32_t AbstractStatementVisitor::visitSwitchStatement(SwitchStatement* stat) { return visitBlockStatement(stat); }

int32_t AbstractStatementVisitor::visitCaseStatement(CaseStatement* stat) { return visitBlockStatement(stat); }

int32_t AbstractStatementVisitor::visitDefaultStatement(DefaultStatement* stat) { return visitBlockStatement(stat); }

int32_t AbstractStatementVisitor::visitIfStatement(IfStatement* stat)
{
    if (stat->falseCase) {
        stat->trueCase->accept(this);
        return stat->falseCase->accept(this);
    } else {
        return stat->trueCase->accept(this);
    }
}

int32_t AbstractStatementVisitor::visitBreakStatement(BreakStatement* stat) { return visitStatement(stat); }

int32_t AbstractStatementVisitor::visitContinueStatement(ContinueStatement* stat) { return visitStatement(stat); }

int32_t AbstractStatementVisitor::visitReturnStatement(ReturnStatement* stat) { return visitStatement(stat); }

int32_t ExpressionVisitor::visitExprStatement(ExprStatement* stat)
{
    visitExpression(stat->expr);
    return 0;
}

int32_t ExpressionVisitor::visitAssertStatement(AssertStatement* stat)
{
    visitExpression(stat->expr);
    return 0;
}

int32_t ExpressionVisitor::visitForStatement(ForStatement* stat)
{
    visitExpression(stat->init);
    visitExpression(stat->cond);
    visitExpression(stat->step);
    return stat->stat->accept(this);
}

int32_t ExpressionVisitor::visitWhileStatement(WhileStatement* stat)
{
    visitExpression(stat->cond);
    return stat->stat->accept(this);
}

int32_t ExpressionVisitor::visitDoWhileStatement(DoWhileStatement* stat)
{
    visitExpression(stat->cond);
    return stat->stat->accept(this);
}

int32_t ExpressionVisitor::visitBlockStatement(BlockStatement* stat)
{
    // Visit variable initialisers.
    for (symbol_t& symbol : stat->getFrame()) {
        if (auto* data = symbol.getData(); data) {
            // REVISIT: This will only work if vars[i] is a variable!
            visitExpression(static_cast<variable_t*>(data)->expr);
        }
    }

    // Visit statements.
    for (std::unique_ptr<Statement>& s : *stat) {
        s->accept(this);
    }
    return 0;
}

int32_t ExpressionVisitor::visitSwitchStatement(SwitchStatement* stat)
{
    visitExpression(stat->cond);
    return visitBlockStatement(stat);
}

int32_t ExpressionVisitor::visitCaseStatement(CaseStatement* stat)
{
    visitExpression(stat->cond);
    return visitBlockStatement(stat);
}

int32_t ExpressionVisitor::visitDefaultStatement(DefaultStatement* stat) { return visitBlockStatement(stat); }

int32_t ExpressionVisitor::visitIfStatement(IfStatement* stat)
{
    visitExpression(stat->cond);
    stat->trueCase->accept(this);
    if (stat->falseCase) {
        stat->falseCase->accept(this);
    }
    return 0;
}

int32_t ExpressionVisitor::visitReturnStatement(ReturnStatement* stat)
{
    visitExpression(stat->value);
    return 0;
}

void CollectChangesVisitor::visitExpression(expression_t expr) { expr.collectPossibleWrites(changes); }

CollectDependenciesVisitor::CollectDependenciesVisitor(std::set<symbol_t>& dependencies): dependencies(dependencies) {}

void CollectDependenciesVisitor::visitExpression(expression_t expr) { expr.collectPossibleReads(dependencies); }

void CollectDynamicExpressions::visitExpression(expression_t expr)
{
    if (expr.isDynamic() || expr.hasDynamicSub())
        expressions.push_back(expr);
}
