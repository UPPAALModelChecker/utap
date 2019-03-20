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

#include "utap/builder.hh"
#include "utap/expression.hh"

using namespace UTAP;
using namespace Constants;

using std::list;
using std::vector;

int ExpressionProgram::getNumberOfSubExpressions(const expression_t &expr) const
{
    switch (expr.kind) {
    case MINUS:
    case PLUS:
    case MULT:
    case DIV:
    case MOD:
    case BIT_AND:
    case BIT_OR:
    case BIT_XOR:
    case BIT_LSHIFT:
    case BIT_RSHIFT:
    case AND:
    case OR:
    case LT:
    case LE:
    case EQ:
    case NEQ:
    case GE:
    case GT:
      return 2;
    case UNARY_MINUS:
    case NOT:
      return 1;
      break;
    case IDENTIFIER:
    case CONSTANT:
      return 0;
      break;
    case LIST:
      return expr.value;
      break;
    case ARRAY:
      return 2;
      break;
    case INLINEIF:
      return 3;
      break;
    case DOT:
      return 1;
    case CONSTRAINT:
      return 3;
    case LEADSTO:
    case COMMA:
    case ASSIGN:
      return 2;
    case SYNC:
      return ((uint32_t)expr.value == SYNC_TAU ? 0 : 1);
    case DEADLOCK:
      return 0;
    default:
      throw TypeException("BUG: Unknown expression kind (%d)", expr.kind);
    }
}

int ExpressionProgram::decompose(const_iterator expr,
				 vector<const_iterator> &sub) const
{
  int32_t count = getNumberOfSubExpressions(*expr);

  if (count == 0) {
    sub.clear();
    return 0;
  }
  
  int32_t pos = count;
  sub = vector<list<expression_t>::const_iterator>(pos);
  while (--pos > 0) {
    expr = sub[pos] = findStartOf(--expr);
  }
  sub[0] = findStartOf(--expr);
  return count;
}

int ExpressionProgram::decompose(iterator expr, vector<iterator> &sub) 
{
  int32_t count = getNumberOfSubExpressions(*expr);

  if (count == 0) {
    sub.clear();
    return 0;
  }
  
  int32_t pos = count;
  sub = vector<list<expression_t>::iterator>(pos);
  while (--pos > 0) {
    expr = sub[pos] = findStartOf(--expr);
  }
  sub[0] = findStartOf(--expr);
  return count;
}

ExpressionProgram::const_iterator ExpressionProgram::findStartOf(const_iterator expr) const
{
    int32_t count = 1;
    for (;;) {
      count += getNumberOfSubExpressions(*expr);
      count -= 1;
      if (count == 0)
	return expr;
      --expr;
    }
}

ExpressionProgram::iterator ExpressionProgram::findStartOf(iterator expr) 
{
    int32_t count = 1;
    for (;;) {
      count += getNumberOfSubExpressions(*expr);
      count -= 1;
      if (count == 0)
	return expr;
      --expr;
    }
}

void ExpressionProgram::append(SubExpression sub)
{
  ExpressionProgram::iterator first = sub.expr.findStartOf(sub.pos);
  ExpressionProgram::iterator last = ++sub.pos;
  append(first, last);
}

SubExpression SubExpression::getSubExpression(uint32_t idx)
{
  vector<ExpressionProgram::iterator> sub;
  expr.decompose(pos, sub);
  assert(idx < sub.size());
  ExpressionProgram::iterator result = pos;
  if (idx + 1 == sub.size())
    --result;
  else
    result = --sub[idx + 1];
  return SubExpression(expr, result);
}
