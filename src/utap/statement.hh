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

#include "expression.hh"
#include "symbols.hh"

namespace UTAP
{
    class StatementVisitor;

    class Statement 
    {
    protected:
	bool returnDefined;
	frame_t frame;    
    public:
	virtual ~Statement() {};
	virtual int32_t accept(StatementVisitor *visitor) = 0;

	frame_t getFrame() { return frame; }
	void setRetDefined(bool ret) { returnDefined = ret; }
	bool retDefined() const { return returnDefined; }    
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

    class BlockStatement: public Statement 
    {
    public:
	typedef std::vector<Statement *>::const_iterator const_iterator;
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
	virtual int32_t emptyStat(EmptyStatement *stat)=0;
	virtual int32_t exprStat(ExprStatement *stat)=0;
	virtual int32_t forStat(ForStatement *stat)=0;
	virtual int32_t whileStat(WhileStatement *stat)=0;
	virtual int32_t doWhileStat(DoWhileStatement *stat)=0;
	virtual int32_t blockStat(BlockStatement *stat)=0;
	virtual int32_t switchStat(SwitchStatement *stat)=0;
	virtual int32_t caseStat(CaseStatement *stat)=0;
	virtual int32_t defaultStat(DefaultStatement *stat)=0;
	virtual int32_t ifStat(IfStatement *stat)=0;
	virtual int32_t breakStat(BreakStatement *stat)=0;
	virtual int32_t continueStat(ContinueStatement *stat)=0;
	virtual int32_t returnStat(ReturnStatement *stat)=0;
    
    protected:
	StatementVisitor(){};
    };

}
#endif
