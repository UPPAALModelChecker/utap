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

#define INDENT "\t"

#include "utap/expression.h"
#include "utap/symbols.h"
#include "utap/system.h"

namespace UTAP
{
    class StatementVisitor;

    class Statement
    {
    public:
        virtual ~Statement() {};
        virtual int32_t accept(StatementVisitor *visitor) = 0;
        virtual bool returns() = 0;
        virtual std::string toString(const std::string& prefix) const = 0;
    protected:
        Statement();
    };

    class EmptyStatement: public Statement
    {
    public:
        EmptyStatement();
        int32_t accept(StatementVisitor *visitor) override;
        bool returns() override;
        std::string toString(const std::string& prefix) const override;
    };

    class ExprStatement: public Statement
    {
    public:
        expression_t expr;
        ExprStatement(expression_t);
        int32_t accept(StatementVisitor *visitor) override;
        bool returns() override;
        std::string toString(const std::string& prefix) const override;
    };

    class AssertStatement: public Statement
    {
    public:
        expression_t expr;
        AssertStatement(expression_t);
        int32_t accept(StatementVisitor *visitor) override;
        bool returns() override;
        std::string toString(const std::string& prefix) const override;
    };

    class ForStatement: public Statement
    {
    public:
        expression_t init;
        expression_t cond;
        expression_t step;
        Statement *stat;
        ForStatement(expression_t, expression_t, expression_t, Statement*);
        int32_t accept(StatementVisitor *visitor) override;
        bool returns() override;
        std::string toString(const std::string& prefix) const override;
    };

    /**
     * Statement class for the iterator loop-construction.
     */
    class IterationStatement: public Statement
    {
    protected:
        frame_t frame;
    public:
        symbol_t symbol;
        Statement *stat;
        IterationStatement(symbol_t, frame_t, Statement *);
        frame_t getFrame() { return frame; }
        int32_t accept(StatementVisitor *visitor) override;
        bool returns() override;
        std::string toString(const std::string& prefix) const override;
     };

    class WhileStatement: public Statement
    {
    public:
        expression_t cond;
        Statement *stat;
        WhileStatement(expression_t, Statement*);
        int32_t accept(StatementVisitor *visitor) override;
        bool returns() override;
        std::string toString(const std::string& prefix) const override;
    };

    class DoWhileStatement: public Statement
    {
    public:
        Statement *stat;
        expression_t cond;
        DoWhileStatement(Statement*, expression_t);
        int32_t accept(StatementVisitor *visitor) override;
        bool returns() override;
        std::string toString(const std::string& prefix) const override;
    };

    class BlockStatement: public Statement, public declarations_t
    {
    public:
        typedef std::vector<Statement *>::const_iterator const_iterator;
        typedef std::vector<Statement *>::iterator iterator;
    protected:
        std::vector<Statement*> stats;
        frame_t frame;
    public:
        BlockStatement(frame_t);
        ~BlockStatement() override;
        int32_t accept(StatementVisitor *visitor) override;
        bool returns() override;

        frame_t getFrame() { return frame; }
        void push_stat(Statement* stat);
        Statement* pop_stat();
        Statement* back();
        const_iterator begin() const;
        const_iterator end() const;
        iterator begin();
        iterator end();
        std::string toString(const std::string& prefix) const override;
    };

    class SwitchStatement: public BlockStatement
    {
    public:
        expression_t cond;
        SwitchStatement(frame_t, expression_t);
        int32_t accept(StatementVisitor *visitor) override;
        bool returns() override;
        std::string toString(const std::string& prefix) const override;
    };

    class CaseStatement: public BlockStatement
    {
    public:
        expression_t cond;
        CaseStatement(frame_t, expression_t);
        int32_t accept(StatementVisitor *visitor) override;
        bool returns() override;
        std::string toString(const std::string& prefix) const override;
    };

    class DefaultStatement: public BlockStatement
    {
    public:
        DefaultStatement(frame_t);
        int32_t accept(StatementVisitor *visitor) override;
        bool returns() override;
    };

    class IfStatement: public Statement
    {
    public:
        expression_t cond;
        Statement *trueCase;
        Statement *falseCase;
        IfStatement(expression_t, Statement*,
                    Statement* falseStat=nullptr);
        int32_t accept(StatementVisitor *visitor) override;
        bool returns() override;
        std::string toString(const std::string& prefix) const override;
    };

    class BreakStatement: public Statement
    {
    public:
        BreakStatement();
        int32_t accept(StatementVisitor *visitor) override;
        bool returns() override;
        std::string toString(const std::string& prefix) const override;
    };

    class ContinueStatement: public Statement
    {
    public:
        ContinueStatement();
        int32_t accept(StatementVisitor *visitor) override;
        bool returns() override;
        std::string toString(const std::string& prefix) const override;
    };

    class ReturnStatement: public Statement
    {
    public:
        expression_t value;
        ReturnStatement();
        ReturnStatement(expression_t);
        int32_t accept(StatementVisitor *visitor) override;
        bool returns() override;
        std::string toString(const std::string& prefix) const override;
    };

    class StatementVisitor
    {
    public:
        virtual ~StatementVisitor() {};
        virtual int32_t visitEmptyStatement(EmptyStatement *stat)=0;
        virtual int32_t visitExprStatement(ExprStatement *stat)=0;
        virtual int32_t visitAssertStatement(AssertStatement *stat)=0;
        virtual int32_t visitForStatement(ForStatement *stat)=0;
        virtual int32_t visitIterationStatement(IterationStatement *stat)=0;
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
    };

    class AbstractStatementVisitor : public StatementVisitor
    {
    protected:
        virtual int32_t visitStatement(Statement *stat);
    public:
        int32_t visitEmptyStatement(EmptyStatement *stat) override;
        int32_t visitExprStatement(ExprStatement *stat) override;
        int32_t visitAssertStatement(AssertStatement *stat) override;
        int32_t visitForStatement(ForStatement *stat) override;
        int32_t visitIterationStatement(IterationStatement *stat) override;
        int32_t visitWhileStatement(WhileStatement *stat) override;
        int32_t visitDoWhileStatement(DoWhileStatement *stat) override;
        int32_t visitBlockStatement(BlockStatement *stat) override;
        int32_t visitSwitchStatement(SwitchStatement *stat) override;
        int32_t visitCaseStatement(CaseStatement *stat) override;
        int32_t visitDefaultStatement(DefaultStatement *stat) override;
        int32_t visitIfStatement(IfStatement *stat) override;
        int32_t visitBreakStatement(BreakStatement *stat) override;
        int32_t visitContinueStatement(ContinueStatement *stat) override;
        int32_t visitReturnStatement(ReturnStatement *stat) override;
    };

    class ExpressionVisitor : public AbstractStatementVisitor
    {
    protected:
        virtual void visitExpression(expression_t) = 0;
    public:
        int32_t visitExprStatement(ExprStatement *stat) override;
        int32_t visitAssertStatement(AssertStatement *stat) override;
        int32_t visitForStatement(ForStatement *stat) override;
        int32_t visitWhileStatement(WhileStatement *stat) override;
        int32_t visitDoWhileStatement(DoWhileStatement *stat) override;
        int32_t visitBlockStatement(BlockStatement *stat) override;
        int32_t visitSwitchStatement(SwitchStatement *stat) override;
        int32_t visitCaseStatement(CaseStatement *stat) override;
        int32_t visitDefaultStatement(DefaultStatement *stat) override;
        int32_t visitIfStatement(IfStatement *stat) override;
        int32_t visitReturnStatement(ReturnStatement *stat) override;
    };

    class CollectChangesVisitor : public ExpressionVisitor
    {
    protected:
        void visitExpression(expression_t) override;
        std::set<symbol_t> &changes;
    public:
        CollectChangesVisitor(std::set<symbol_t> &);
    };

    class CollectDependenciesVisitor : public ExpressionVisitor
    {
    protected:
        void visitExpression(expression_t) override;
        std::set<symbol_t> &dependencies;
    public:
        CollectDependenciesVisitor(std::set<symbol_t> &);
    };

    class CollectDynamicExpressions : public ExpressionVisitor
    {
    protected:
        void visitExpression (expression_t) override;
        std::list<expression_t> &expressions;
    public:
        CollectDynamicExpressions (std::list<expression_t>& );
    };

}
#endif
