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

namespace UTAP
{
    class StatementVisitor;

    class Statement 
    {
    protected:
	bool returnDefined;
    
    public:
	// frame id (from symbol table)
	int32_t frameId;    
    
	virtual ~Statement() {};
	virtual int32_t accept(StatementVisitor *visitor)=0;
	void setRetDefined(bool ret){ returnDefined = ret; }
	bool retDefined(){ return returnDefined; }
    
    protected:
	Statement(int32_t _fid): returnDefined(false), frameId(_fid) {}
    };

    class EmptyStatement: public Statement 
    {
    public:
	EmptyStatement(int32_t frameId);
	int32_t accept(StatementVisitor *visitor);
    };

    class ExprStatement: public Statement 
    {
    public:
	ExpressionProgram expr;
	ExprStatement(int32_t frameId, ExpressionProgram&);
	int32_t accept(StatementVisitor *visitor);
    };


    class ForStatement: public Statement 
    {
    public:
	ExpressionProgram init;
	ExpressionProgram cond;
	ExpressionProgram step;
	Statement *stat;
	ForStatement(int32_t frameId, ExpressionProgram&, 
		     ExpressionProgram&, ExpressionProgram&, Statement*);
	int32_t accept(StatementVisitor *visitor);
    };

    class WhileStatement: public Statement 
    {
    public:
	ExpressionProgram cond;
	Statement *stat;
	WhileStatement(int32_t frameId, ExpressionProgram&, Statement*);
	int32_t accept(StatementVisitor *visitor);
    };

    class DoWhileStatement: public Statement 
    {
    public:
	Statement *stat;
	ExpressionProgram cond;
	DoWhileStatement(int32_t frameId, Statement*, ExpressionProgram&);
	int32_t accept(StatementVisitor *visitor);
    };

    class BlockStatement: public Statement 
    {
    protected:
	std::vector<Statement*> stats;
    public:
	BlockStatement(int32_t frameId);
	int32_t getFrame(){ return frameId; }
	void push_stat(Statement* stat){ assert(stat!=NULL); stats.push_back(stat); }
	Statement* pop_stat() { 
	    assert(!stats.empty()); 
	    Statement* st = stats.back();
	    stats.pop_back();
	    return st;
	}
	std::vector<Statement*>::const_iterator begin() { return stats.begin(); }
	std::vector<Statement*>::const_iterator end() { return stats.end(); }
	virtual ~BlockStatement();
	virtual int32_t accept(StatementVisitor *visitor);
    };

    class SwitchStatement: public BlockStatement
    {
    public:
	ExpressionProgram cond;
	SwitchStatement(int32_t frameId, ExpressionProgram&);
	int32_t accept(StatementVisitor *visitor);  
    };

    class CaseStatement: public BlockStatement 
    {
    public:
	ExpressionProgram cond;
	CaseStatement(int32_t frameId, ExpressionProgram&);
	int32_t accept(StatementVisitor *visitor);
    };

    class DefaultStatement: public BlockStatement 
    {
    public:
	DefaultStatement(int32_t frameId);
	int32_t accept(StatementVisitor *visitor);
    };

    class IfStatement: public Statement 
    {
    public:
	ExpressionProgram cond;
	Statement *trueCase;
	Statement *falseCase;
	IfStatement(int32_t frameId, ExpressionProgram&, Statement*, 
		    Statement* falseStat=NULL);
	int32_t accept(StatementVisitor *visitor);
    };

    class BreakStatement: public Statement 
    {
    public:
	BreakStatement(int32_t frameId);
	int32_t accept(StatementVisitor *visitor);
    };

    class ContinueStatement: public Statement 
    {
    public:
	ContinueStatement(int32_t frameId);
	int32_t accept(StatementVisitor *visitor);
    };

    class ReturnStatement: public Statement 
    {
    public:
	ExpressionProgram value;
	ReturnStatement(int32_t frameId, ExpressionProgram&);
	int32_t accept(StatementVisitor *visitor);
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
