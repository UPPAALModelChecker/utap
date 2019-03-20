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

#ifndef UTAP_STATEMENT_H
#define UTAP_STATEMENT_H

#include "utap/expression.hh"
#include "utap/symbols.hh"
#include "utap/system.hh"

namespace UTAP
{
    class StatementVisitor;

    class Statement 
    {
    public:
	virtual ~Statement() {};
	virtual int32_t accept(StatementVisitor *visitor) = 0;
    protected:
	Statement(frame_t);
    };

    class EmptyStatement: public Statement 
    {
    public:
	EmptyStatement(frame_t frame);
	int32_t accept(StatementVisitor *visitor);
    };

    class ExprStatement: public Statement 
    {
    public:
	expression_t expr;
	ExprStatement(frame_t frame, expression_t);
	int32_t accept(StatementVisitor *visitor);
    };

    class ForStatement: public Statement 
    {
    public:
	expression_t init;
	expression_t cond;
	expression_t step;
	Statement *stat;
	ForStatement(frame_t frame, expression_t, 
		     expression_t, expression_t, Statement*);
	int32_t accept(StatementVisitor *visitor);
    };

    class WhileStatement: public Statement 
    {
    public:
	expression_t cond;
	Statement *stat;
	WhileStatement(frame_t frame, expression_t, Statement*);
	int32_t accept(StatementVisitor *visitor);
    };

    class DoWhileStatement: public Statement 
    {
    public:
	Statement *stat;
	expression_t cond;
	DoWhileStatement(frame_t frameId, Statement*, expression_t);
	int32_t accept(StatementVisitor *visitor);
    };

    class BlockStatement: public Statement, public declarations_t 
    {
    public:
	typedef std::vector<Statement *>::const_iterator const_iterator;
	typedef std::vector<Statement *>::iterator iterator;
    protected:
	std::vector<Statement*> stats;
    public:
	BlockStatement(frame_t frame);
	virtual ~BlockStatement();
	virtual int32_t accept(StatementVisitor *visitor);

	void push_stat(Statement* stat);
	Statement* pop_stat();
	const_iterator begin() const;
	const_iterator end() const;
	iterator begin();
	iterator end();
    };

    class SwitchStatement: public BlockStatement
    {
    public:
	expression_t cond;
	SwitchStatement(frame_t frame, expression_t);
	virtual int32_t accept(StatementVisitor *visitor);  
    };

    class CaseStatement: public BlockStatement 
    {
    public:
	expression_t cond;
	CaseStatement(frame_t frame, expression_t);
	virtual int32_t accept(StatementVisitor *visitor);
    };

    class DefaultStatement: public BlockStatement 
    {
    public:
	DefaultStatement(frame_t frame);
	virtual int32_t accept(StatementVisitor *visitor);
    };

    class IfStatement: public Statement 
    {
    public:
	expression_t cond;
	Statement *trueCase;
	Statement *falseCase;
	IfStatement(frame_t frame, expression_t, Statement*, 
		    Statement* falseStat=NULL);
	virtual int32_t accept(StatementVisitor *visitor);
    };

    class BreakStatement: public Statement 
    {
    public:
	BreakStatement(frame_t frame);
	virtual int32_t accept(StatementVisitor *visitor);
    };

    class ContinueStatement: public Statement 
    {
    public:
	ContinueStatement(frame_t frame);
	virtual int32_t accept(StatementVisitor *visitor);
    };

    class ReturnStatement: public Statement 
    {
    public:
	expression_t value;
	ReturnStatement(frame_t frame);
	ReturnStatement(frame_t frame, expression_t);
	virtual int32_t accept(StatementVisitor *visitor);
    };

    class StatementVisitor
    {
    public:
	virtual ~StatementVisitor() {};
	virtual int32_t visitEmptyStatement(EmptyStatement *stat)=0;
	virtual int32_t visitExprStatement(ExprStatement *stat)=0;
	virtual int32_t visitForStatement(ForStatement *stat)=0;
	virtual int32_t visitWhileStatement(WhileStatement *stat)=0;
	virtual int32_t visitDoWhileStatement(DoWhileStatement *stat)=0;
	virtual int32_t visitBlockStatement(BlockStatement *stat)=0;
	virtual int32_t visitSwitchStatement(SwitchStatement *stat)=0;
	virtual int32_t visitCaseStatement(CaseStatement *stat)=0;
	virtual int32_t visitDefaultStatement(DefaultStatement *stat)=0;
	virtual int32_t visitIfStatement(IfStatement *stat)=0;
	virtual int32_t visitBreakStatement(BreakStatement *stat)=0;
	virtual int32_t visitContinueStatement(ContinueStatement *stat)=0;
	virtual int32_t visitReturnStatement(ReturnStatement *stat)=0;
    
    protected:
	StatementVisitor(){};
    };

}
#endif
