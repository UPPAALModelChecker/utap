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

#include <set>

#include "utap/statement.h"

namespace UTAP
{

    class CollectChangesVisitor : public StatementVisitor
    {
    public:
	CollectChangesVisitor(std::set<symbol_t> &changes);
	virtual ~CollectChangesVisitor();

	virtual int32_t visitEmptyStatement(EmptyStatement *stat);
	virtual int32_t visitExprStatement(ExprStatement *stat);
	virtual int32_t visitForStatement(ForStatement *stat);
	virtual int32_t visitWhileStatement(WhileStatement *stat);
	virtual int32_t visitDoWhileStatement(DoWhileStatement *stat);
	virtual int32_t visitBlockStatement(BlockStatement *stat);
	virtual int32_t visitSwitchStatement(SwitchStatement *stat);
	virtual int32_t visitCaseStatement(CaseStatement *stat);
	virtual int32_t visitDefaultStatement(DefaultStatement *stat);
	virtual int32_t visitIfStatement(IfStatement *stat);
	virtual int32_t visitBreakStatement(BreakStatement *stat);
	virtual int32_t visitContinueStatement(ContinueStatement *stat);
	virtual int32_t visitReturnStatement(ReturnStatement *stat);
    protected:
	std::set<symbol_t> &changes;
	
	void collectFromExpression(expression_t);
    };

}
