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
using std::set;

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
    case MIN:
    case MAX:
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
    case LEADSTO:
    case COMMA:
    case ASSIGN:
    case ASSPLUS:
    case ASSMINUS:
    case ASSDIV:
    case ASSMOD:
    case ASSMULT:
    case ASSAND:
    case ASSOR:
    case ASSXOR:
    case ASSLSHIFT:
    case ASSRSHIFT:
      return 2;
    case SYNC:
      return ((uint32_t)expr.value == SYNC_TAU ? 0 : 1);
    case DEADLOCK:
      return 0;
    case PREINCREMENT:
    case POSTINCREMENT:
    case PREDECREMENT:
    case POSTDECREMENT:
	return 1;
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

SubExpression SubExpression::get(uint32_t idx)
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

const SubExpression SubExpression::get(uint32_t idx) const
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

/** Returns true if expr might be a reference to a symbol in the
    set. NOTE: This method does not use the getSymbol() call, since
    that one always returns the 'true' result of an inline if.
 */
bool SubExpression::isReferenceTo(const set<int> &identifiers) const
{
    switch (getKind()) {
    case IDENTIFIER:
	return (identifiers.find(getValue()) != identifiers.end());
    case ARRAY:
	return get(0).isReferenceTo(identifiers);
    case PREINCREMENT:
    case PREDECREMENT:
	return get(0).isReferenceTo(identifiers);
    case COMMA:
	return get(1).isReferenceTo(identifiers);
    case DOT:
	return get(0).isReferenceTo(identifiers) 
	    || identifiers.find(get(0).getSymbol().getId()) != identifiers.end();

    case INLINEIF:
	return get(1).isReferenceTo(identifiers) || get(2).isReferenceTo(identifiers);
    case ASSIGN:
    case ASSPLUS:
    case ASSMINUS:
    case ASSDIV:
    case ASSMOD:
    case ASSMULT:
    case ASSAND:
    case ASSOR:
    case ASSXOR:
    case ASSLSHIFT:
    case ASSRSHIFT:
	return get(0).isReferenceTo(identifiers);
    default:
	// This operation will not result in a reference
	return false;
    }
}

bool SubExpression::changesVariable(const set<int> &variables) const
{
    for (int i = 0; i < getSize(); i++) 
	if (get(i).changesVariable(variables)) 
	    return true;  

    switch (getKind()) {
    case ASSIGN:
    case ASSPLUS:
    case ASSMINUS:
    case ASSDIV:
    case ASSMOD:
    case ASSMULT:
    case ASSAND:
    case ASSOR:
    case ASSXOR:
    case ASSLSHIFT:
    case ASSRSHIFT:
    case POSTINCREMENT:
    case POSTDECREMENT:
    case PREINCREMENT:
    case PREDECREMENT:
	return get(0).isReferenceTo(variables);
      
    case FUNCALL:
	// TODO: The function must be side effect free
	return false;
    }

    return false; // Pessimistic default
}

/**
   Returns the symbol of a variable reference. The expression must be
   a left-hand side value. The symbol returned is the symbol of the
   variable the expression if resulting in a reference to. NOTE: In
   case of inline if, the symbol referenced by the 'true' part is
   returned.
*/
symbol_t SubExpression::getSymbol() const
{
    switch (getKind()) {
    case IDENTIFIER:
	return symbol_t(getValue());
      
    case DOT:
	return get(0).getType().getFrame()[getValue()];
      
    case ARRAY:
	return get(0).getSymbol();
      
    case PREINCREMENT:
    case PREDECREMENT:
	return get(0).getSymbol();
    
    case INLINEIF:
	return get(1).getSymbol();
      
    case COMMA:
	return get(1).getSymbol();

    case ASSIGN:
    case ASSPLUS:
    case ASSMINUS:
    case ASSDIV:
    case ASSMOD:
    case ASSMULT:
    case ASSAND:
    case ASSOR:
    case ASSXOR:
    case ASSLSHIFT:
    case ASSRSHIFT:
	return get(0).getSymbol();

    case SYNC:
	if (getValue() != SYNC_TAU)
	    return get(0).getSymbol();
	break;
	
    case FUNCALL:
	//Functions cannot return references (yet!)
	break;
    }
    return symbol_t();
}

bool SubExpression::dependsOn(const set<int> &variables) const
{
    for (int i = 0; i < getSize(); i++) 
	if (get(i).dependsOn(variables)) 
	    return true;

    if (getKind() == IDENTIFIER) 
	return variables.find(getValue()) != variables.end();
    
    return false;
}

const position_t &SubExpression::getPosition() const
{
    return pos->position;
}
