// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; -*-

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

#include "utap/statement.hh"

using namespace UTAP;

EmptyStatement::EmptyStatement(int32_t frameId): Statement(frameId) {};

int32_t EmptyStatement::accept(StatementVisitor *visitor)
{
    return visitor->emptyStat(this); 
};

ExprStatement::ExprStatement(int32_t frameId, ExpressionProgram& _expr): 
    Statement(frameId), expr(_expr.begin(), _expr.end()) {};
int32_t ExprStatement::accept(StatementVisitor *visitor)
{ return visitor->exprStat(this); };

ForStatement::ForStatement(int32_t frameId, ExpressionProgram& _init,
   ExpressionProgram& _cond, ExpressionProgram& _step, Statement* _stat): 
    Statement(frameId), init(_init.begin(), _init.end()), 
    cond(_cond.begin(), _cond.end()), step(_step.begin(), _step.end()), 
    stat(_stat) 
{ 
    assert(_stat!=NULL); 
};
int32_t ForStatement::accept(StatementVisitor *visitor)
{ return visitor->forStat(this); };

WhileStatement::WhileStatement(int32_t frameId, ExpressionProgram& _cond,
			       Statement* _stat): 
    Statement(frameId), cond(_cond.begin(), _cond.end()), stat(_stat) 
{ 
    assert(_stat!=NULL); 
};
int32_t WhileStatement::accept(StatementVisitor *visitor)
{ return visitor->whileStat(this); };

DoWhileStatement::DoWhileStatement(int32_t frameId, Statement* _stat,
				   ExpressionProgram& _cond): 
    Statement(frameId), stat(_stat), cond(_cond) 
{
    assert(_stat!=NULL);
};
int32_t DoWhileStatement::accept(StatementVisitor *visitor)
{ return visitor->doWhileStat(this); };

BlockStatement::BlockStatement(int32_t frameId): 
    Statement(frameId) {};
BlockStatement::~BlockStatement() { while(!stats.empty()) delete pop_stat(); }
int32_t BlockStatement::accept(StatementVisitor *visitor)
{ return visitor->blockStat(this); };

SwitchStatement::SwitchStatement(int32_t frameId, ExpressionProgram& _cond): 
    BlockStatement(frameId), cond(_cond) {};
int32_t SwitchStatement::accept(StatementVisitor *visitor)
{ return visitor->switchStat(this); };

CaseStatement::CaseStatement(int32_t frameId, ExpressionProgram& _cond): 
    BlockStatement(frameId), cond(_cond) {};
int32_t CaseStatement::accept(StatementVisitor *visitor)
{ return visitor->caseStat(this); };

DefaultStatement::DefaultStatement(int32_t frameId): 
    BlockStatement(frameId) {};
int32_t DefaultStatement::accept(StatementVisitor *visitor)
{ return visitor->defaultStat(this); };

IfStatement::IfStatement(int32_t frameId, ExpressionProgram& _cond,
			 Statement* _true, Statement* _false): 
    Statement(frameId), cond(_cond), trueCase(_true), falseCase(_false) 
{
    assert(_true!=NULL);
};
int32_t IfStatement::accept(StatementVisitor *visitor)
{ return visitor->ifStat(this); };

BreakStatement::BreakStatement(int32_t frameId): Statement(frameId) {};
int32_t BreakStatement::accept(StatementVisitor *visitor)
{ return visitor->breakStat(this); };

ContinueStatement::ContinueStatement(int32_t frameId): Statement(frameId) {};
inline int32_t ContinueStatement::accept(StatementVisitor *visitor)
{ return visitor->continueStat(this); };

ReturnStatement::ReturnStatement(int32_t frameId, ExpressionProgram& _value): 
    Statement(frameId), value(_value) {};
inline int32_t ReturnStatement::accept(StatementVisitor *visitor)
{ return visitor->returnStat(this); };
