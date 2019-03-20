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

#include <cassert>

#include "utap/statement.h"

using namespace UTAP;

Statement::Statement()
{

}


EmptyStatement::EmptyStatement() : Statement()
{

}

int32_t EmptyStatement::accept(StatementVisitor *visitor)
{
    return visitor->visitEmptyStatement(this); 
}

ExprStatement::ExprStatement(expression_t expr)
    : Statement(), expr(expr)
{

}

int32_t ExprStatement::accept(StatementVisitor *visitor)
{
    return visitor->visitExprStatement(this);
}

ForStatement::ForStatement(expression_t init,
   expression_t cond, expression_t step, Statement* _stat)
    : Statement(), init(init), cond(cond), step(step), stat(_stat) 
{ 
    assert(_stat!=NULL); 
}

int32_t ForStatement::accept(StatementVisitor *visitor)
{
    return visitor->visitForStatement(this);
}

WhileStatement::WhileStatement(expression_t cond,
			       Statement* _stat)
    : Statement(), cond(cond), stat(_stat) 
{ 
    assert(_stat!=NULL); 
}

int32_t WhileStatement::accept(StatementVisitor *visitor)
{
    return visitor->visitWhileStatement(this);
}

DoWhileStatement::DoWhileStatement(Statement* _stat,
				   expression_t cond)
    : Statement(), stat(_stat), cond(cond) 
{
    assert(_stat!=NULL);
}

int32_t DoWhileStatement::accept(StatementVisitor *visitor)
{
    return visitor->visitDoWhileStatement(this);
}

BlockStatement::BlockStatement(frame_t frame)
    : Statement()
{
    this->frame = frame;
}

BlockStatement::~BlockStatement()
{
    while(!stats.empty()) delete pop_stat();
}

void BlockStatement::push_stat(Statement* stat)
{
    assert(stat!=NULL);
    stats.push_back(stat);
}

BlockStatement::const_iterator BlockStatement::begin() const
{
    return stats.begin();
}

BlockStatement::const_iterator BlockStatement::end() const
{
    return stats.end();
}

BlockStatement::iterator BlockStatement::begin()
{
    return stats.begin();
}

BlockStatement::iterator BlockStatement::end() 
{
    return stats.end();
}

Statement* BlockStatement::pop_stat()
{ 
    assert(!stats.empty()); 
    Statement* st = stats.back();
    stats.pop_back();
    return st;
}

int32_t BlockStatement::accept(StatementVisitor *visitor)
{
    return visitor->visitBlockStatement(this);
}

SwitchStatement::SwitchStatement(frame_t frame, expression_t cond)
    : BlockStatement(frame), cond(cond)
{

}

int32_t SwitchStatement::accept(StatementVisitor *visitor)
{
    return visitor->visitSwitchStatement(this);
}

CaseStatement::CaseStatement(frame_t frame, expression_t cond)
    : BlockStatement(frame), cond(cond)
{

}

int32_t CaseStatement::accept(StatementVisitor *visitor)
{
    return visitor->visitCaseStatement(this);
}

DefaultStatement::DefaultStatement(frame_t frame)
    : BlockStatement(frame)
{

};

int32_t DefaultStatement::accept(StatementVisitor *visitor)
{
    return visitor->visitDefaultStatement(this);
}

IfStatement::IfStatement(expression_t cond,
			 Statement* _true, Statement* _false)
    : Statement(), cond(cond), trueCase(_true), falseCase(_false) 
{
    assert(_true!=NULL);
}

int32_t IfStatement::accept(StatementVisitor *visitor)
{
    return visitor->visitIfStatement(this);
}

BreakStatement::BreakStatement() : Statement()
{

}

int32_t BreakStatement::accept(StatementVisitor *visitor)
{
    return visitor->visitBreakStatement(this);
}

ContinueStatement::ContinueStatement() : Statement()
{

}

int32_t ContinueStatement::accept(StatementVisitor *visitor)
{
    return visitor->visitContinueStatement(this);
}

ReturnStatement::ReturnStatement()
    : Statement()
{

}

ReturnStatement::ReturnStatement(expression_t value)
    : Statement(), value(value)
{

}

int32_t ReturnStatement::accept(StatementVisitor *visitor)
{
    return visitor->visitReturnStatement(this);
};
