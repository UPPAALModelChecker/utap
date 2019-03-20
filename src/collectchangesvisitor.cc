// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2003 Uppsala University and Aalborg University.
   
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

#include "utap/collectchangesvisitor.hh"

using std::set;

using namespace UTAP;

CollectChangesVisitor::CollectChangesVisitor(set<symbol_t> &changes)
    : changes(changes)
{

}

CollectChangesVisitor::~CollectChangesVisitor()
{

}

int32_t CollectChangesVisitor::visitEmptyStatement(EmptyStatement *stat)
{
    // do nothing
    return 0;
}

int32_t CollectChangesVisitor::visitExprStatement(ExprStatement *stat)
{
    collectFromExpression(stat->expr);
    return 0;
}

int32_t CollectChangesVisitor::visitForStatement(ForStatement *stat)
{
    collectFromExpression(stat->init); 
    collectFromExpression(stat->cond);
    collectFromExpression(stat->step);
    return stat->stat->accept(this);
}

int32_t CollectChangesVisitor::visitWhileStatement(WhileStatement *stat)
{
    collectFromExpression(stat->cond);
    return stat->stat->accept(this);
}

int32_t CollectChangesVisitor::visitDoWhileStatement(DoWhileStatement *stat)
{
    collectFromExpression(stat->cond);
    return stat->stat->accept(this);
}

int32_t CollectChangesVisitor::visitBlockStatement(BlockStatement *stat)
{
    BlockStatement::iterator s;
    for (s = stat->begin(); s != stat->end(); ++s) {
	(*s)->accept(this);
    }
    return 0;
}

int32_t CollectChangesVisitor::visitSwitchStatement(SwitchStatement *stat)
{
    collectFromExpression(stat->cond);
    return visitBlockStatement(stat);
}

int32_t CollectChangesVisitor::visitCaseStatement(CaseStatement *stat)
{
    collectFromExpression(stat->cond);
    return visitBlockStatement(stat);
}

int32_t CollectChangesVisitor::visitDefaultStatement(DefaultStatement *stat)
{
    return visitBlockStatement(stat);
}

int32_t CollectChangesVisitor::visitIfStatement(IfStatement *stat)
{
    collectFromExpression(stat->cond);
    stat->trueCase->accept(this);
    if (stat->falseCase) {
	stat->falseCase->accept(this);
    }
    return 0;
}

int32_t CollectChangesVisitor::visitBreakStatement(BreakStatement *stat)
{
    // nothing
    return 0;
}

int32_t CollectChangesVisitor::visitContinueStatement(ContinueStatement *stat)
{  
    // nothing
    return 0;
}

int32_t CollectChangesVisitor::visitReturnStatement(ReturnStatement *stat)
{
    collectFromExpression(stat->value);
    return 0;
}

void CollectChangesVisitor::collectFromExpression(expression_t expr)
{
    expr.collectPossibleWrites(changes);
}
