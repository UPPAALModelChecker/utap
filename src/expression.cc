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
#include <algorithm>

#include "utap/builder.hh"
#include "utap/expression.hh"

using namespace UTAP;
using namespace Constants;

using std::vector;
using std::set;
using std::min;
using std::max;
using std::pair;
using std::make_pair;
using std::map;
using Constants::kind_t;
using Constants::synchronisation_t;

struct expression_t::expression_data
{
    int count;                  /**< Reference counter */
    position_t position;        /**< The position of the expression */
    kind_t kind;                /**< The kind of the node */
    union {
	int32_t value;          /**< The value of the node */
	int32_t index;
	synchronisation_t sync; /**< The sync value of the node  */
    };
    symbol_t symbol;            /**< The symbol of the node */
    type_t type;                /**< The type of the expression */
    expression_t *sub;          /**< Subexpressions */
};

expression_t::expression_t()
{
    data = NULL;
}

expression_t::expression_t(kind_t kind, const position_t &pos)
{
    data = new expression_data;
    data->count = 1;
    data->kind = kind;
    data->position = pos;
    data->value = 0;
    data->sub = NULL;
}

expression_t::expression_t(const expression_t &e)
{
    data = e.data;
    if (data)
	data->count++;
}

expression_t::~expression_t()
{
    if (data) {
	data->count--;
	if (data->count == 0) {
	    delete[] data->sub;
	    delete data;
	}
    }
}

kind_t expression_t::getKind() const
{
    assert(data);
    return data->kind;
}

const position_t &expression_t::getPosition() const
{
    assert(data);
    return data->position;
}

uint32_t expression_t::getSize() const
{
    if (empty())
	return 0;

    switch (data->kind) {
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
      return data->value;
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
      return 1;
    case DEADLOCK:
      return 0;
    case PREINCREMENT:
    case POSTINCREMENT:
    case PREDECREMENT:
    case POSTDECREMENT:
	return 1;
    default:
	assert(0);
	return 0;
    }
}
	
type_t expression_t::getType() const
{
    assert(data);
    return data->type;
}

void expression_t::setType(type_t type)
{
    assert(data);
    data->type = type;
}

int32_t expression_t::getValue() const
{
    assert(data && data->kind == CONSTANT);
    return data->value;
}

int32_t expression_t::getIndex() const
{
    assert(data && data->kind == DOT);
    return data->index;
}

synchronisation_t expression_t::getSync() const
{
    assert(data && data->kind == SYNC);
    return data->sync;
}

expression_t &expression_t::operator[](uint32_t i)
{
    assert(data && 0 <= i && i < getSize());
    return data->sub[i];
}
	
const expression_t expression_t::operator[](uint32_t i) const
{
    assert(data && 0 <= i && i < getSize());
    return data->sub[i];
}

expression_t &expression_t::get(uint32_t i)
{
    assert(data && 0 <= i && i < getSize());
    return data->sub[i];
}

const expression_t &expression_t::get(uint32_t i) const
{
    assert(data && 0 <= i && i < getSize());
    return data->sub[i];
}

bool expression_t::empty() const
{
    return data == NULL;
}

/** Two expressions are identical iff all the sub expressions
    are identical and if the kind, value and symbol of the 
    root are identical. */
bool expression_t::equal(const expression_t &e) const
{
    if (data == NULL && e.data == NULL || data == e.data)
	return true;

    if (data->count != e.data->count
	|| data->kind != e.data->kind
	|| data->value != e.data->value
	|| data->symbol != e.data->symbol)
    {
	return false;
    }

    for (int i = 0; i < data->count; i++)
	if (data->sub[i].equal(e[i]))
	    return false;

    return true;
}

expression_t &expression_t::operator=(const expression_t &e)
{
    if (data) {
	data->count--;
	if (data->count == 0) {
	    delete[] data->sub;
	    delete data;
	}
    }
    data = e.data;
    if (data)
	data->count++;
    return *this;
}
	
/**
   Returns the symbol of a variable reference. The expression must be
   a left-hand side value. The symbol returned is the symbol of the
   variable the expression if resulting in a reference to. NOTE: In
   case of inline if, the symbol referenced by the 'true' part is
   returned.
*/
symbol_t expression_t::getSymbol() 
{
    return ((const expression_t*)this)->getSymbol();
}

/**
   Returns the symbol of a variable reference. The expression must be
   a left-hand side value. The symbol returned is the symbol of the
   variable the expression if resulting in a reference to. NOTE: In
   case of inline if, the symbol referenced by the 'true' part is
   returned.
*/
const symbol_t expression_t::getSymbol() const
{
    assert(data);

    switch (getKind()) {
    case IDENTIFIER:
	return data->symbol;
      
    case DOT:
	return get(0).getType().getFrame()[data->value];
      
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
	return get(0).getSymbol();
	
    case FUNCALL:
	//Functions cannot return references (yet!)

    default:
	return symbol_t();
    }
}

/** Returns true if expr might be a reference to a symbol in the
    set. NOTE: This method does not use the getSymbol() call, since
    that one always returns the 'true' result of an inline if.
 */
bool expression_t::isReferenceTo(const std::set<symbol_t> &symbols) const
{
    if (empty())
	return false;

    switch (getKind()) {
    case IDENTIFIER:
	return (symbols.find(data->symbol) != symbols.end());
    case ARRAY:
	return get(0).isReferenceTo(symbols);
    case PREINCREMENT:
    case PREDECREMENT:
	return get(0).isReferenceTo(symbols);
    case COMMA:
	return get(1).isReferenceTo(symbols);
    case DOT:
	return get(0).isReferenceTo(symbols) 
	    || symbols.find(getSymbol()) != symbols.end();

    case INLINEIF:
	return get(1).isReferenceTo(symbols) || get(2).isReferenceTo(symbols);

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
	return get(0).isReferenceTo(symbols);
    default:
	// This operation will not result in a reference
	return false;
    }
}

bool expression_t::changesVariable(const std::set<symbol_t> &symbols) const
{
    if (empty())
	return false;

    for (uint32_t i = 0; i < getSize(); i++) 
	if (get(i).changesVariable(symbols)) 
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
	return get(0).isReferenceTo(symbols);
      
    case FUNCALL:
	// TODO: The function must be side effect free
	return false;

    default:
	return false;
    }
}

bool expression_t::dependsOn(const std::set<symbol_t> &symbols) const
{
    if (empty())
	return false;

    for (uint32_t i = 0; i < getSize(); i++) 
	if (get(i).dependsOn(symbols)) 
	    return true;

    if (getKind() == IDENTIFIER) 
	return symbols.find(data->symbol) != symbols.end();
    
    return false;

}

int expression_t::getPrecedence() const
{
    switch (data->kind) {
    case PLUS:
    case MINUS:
	return 70;
	    
    case MULT:
    case DIV:
    case MOD:
	return 80;
	    
    case BIT_AND:
	return 37;
	    
    case BIT_OR:
	return 30;
	    
    case BIT_XOR:
	return 35;

    case BIT_LSHIFT:
    case BIT_RSHIFT:
	return 60;
	    
    case AND:
	return 25;
    case OR:
	return 20;

    case EQ:
    case NEQ:
	return 40;

    case MIN:
    case MAX:
	return 55;

    case LT:
    case LE:
    case GE:
    case GT:
	return 50;
	    
    case IDENTIFIER:
    case CONSTANT:
    case DEADLOCK:
	return 110;
	    
    case DOT:
    case ARRAY:
	return 100;

    case UNARY_MINUS:
    case NOT:
	return 90;
	    
    case INLINEIF:
	return 15;

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
	return 10;

    case COMMA:
	return 5;

    case SYNC:
	return 0;

    case PREDECREMENT:
    case POSTDECREMENT:
    case PREINCREMENT:
    case POSTINCREMENT:
	return 100;

    case EF:
    case EG:
    case AF:
    case AG:
    case LEADSTO:
    case LIST:
    case FUNCALL:
	return -1; // FIXME
    }
    assert(0);
    return 0;
}

pair<int, char *> expression_t::toString_(bool old) const
{
    pair<int, char *> left, right, expr;
    const char *name;
    char *s = NULL;
    int precedence = getPrecedence();
	
    switch (data->kind) {
    case PLUS:
    case MINUS:
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
    case MIN:
    case MAX:
	left = get(0).toString_(old);
	right = get(1).toString_(old);

	s = new char[strlen(left.second) + strlen(right.second) + 10];

	if (precedence > left.first)
	    sprintf(s, "(%s)", left.second);
	else
	    sprintf(s, "%s", left.second);
				  
	switch (data->kind) {
	case PLUS:
	    strcat(s, " + ");
	    break;
	case MINUS:
	    strcat(s, " - ");
	    break;
	case MULT:
	    strcat(s, " * ");
	    break;
	case DIV:
	    strcat(s, " / ");
	    break;
	case MOD:
	    strcat(s, " % ");
	    break;
	case BIT_AND:
	    strcat(s, " & ");
	    break;
	case BIT_OR:
	    strcat(s, " | ");
	    break;
	case BIT_XOR:
	    strcat(s, " ^ ");
	    break;
	case BIT_LSHIFT:
	    strcat(s, " << ");
	    break;
	case BIT_RSHIFT:
	    strcat(s, " >> ");
	    break;
	case AND:
	    strcat(s, " && ");
	    break;
	case OR:
	    strcat(s, " || ");
	    break;
	case LT:
	    strcat(s, " < ");
	    break;
	case LE:
	    strcat(s, " <= ");
	    break;
	case EQ:
	    strcat(s, " == ");
	    break;
	case NEQ:
	    strcat(s, " != ");
	    break;
	case GE:
	    strcat(s, " >= ");
	    break;
	case GT:
	    strcat(s, " > ");
	    break;
	case ASSIGN:
	    if (old)
		strcat(s, " := ");
	    else
		strcat(s, " = ");
	    break;
	case ASSPLUS:
	    strcat(s, " += ");
	    break;
	case ASSMINUS:
	    strcat(s, " -= ");
	    break;
	case ASSDIV:
	    strcat(s, " /= ");
	    break;
	case ASSMOD:
	    strcat(s, " %= ");
	    break;
	case ASSMULT:
	    strcat(s, " *= ");
	    break;
	case ASSAND:
	    strcat(s, " &= ");
	    break;
	case ASSOR:
	    strcat(s, " |= ");
	    break;
	case ASSXOR:
	    strcat(s, " ^= ");
	    break;
	case ASSLSHIFT:
	    strcat(s, " <<= ");
	    break;
	case ASSRSHIFT:
	    strcat(s, " >>= ");
	    break;
	case MIN:
	    strcat(s, " <? ");
	    break;
	case MAX:
	    strcat(s, " >? ");
	    break;
	default:
	    assert(0);
	}
	
	if (precedence >= right.first) 
	    sprintf(s + strlen(s), "(%s)", right.second);
	else
	    strcat(s, right.second);
	
	delete[] left.second;
	delete[] right.second;
	break;

    case IDENTIFIER:
	name = data->symbol.getName();
	s = strcpy(new char[strlen(name) + 1], name);
	break;
		
    case CONSTANT:
	s = new char[12];
	snprintf(s, 12, "%d", data->value);
	break;

    case ARRAY:
	left = get(0).toString_(old);
	right = get(1).toString_(old);
	s = new char[strlen(left.second) + strlen(right.second) + 5];
	if (precedence > left.first)
	    sprintf(s, "(%s)[%s]", left.second, right.second);
	else
	    sprintf(s, "%s[%s]", left.second, right.second);
	delete[] left.second;
	delete[] right.second;
	break;
	    
    case UNARY_MINUS:
	left = get(0).toString_(old);
	s = new char[strlen(left.second) + 4];
	if (precedence > left.first)
	    sprintf(s, "-(%s)", left.second);
	else
	    sprintf(s, "-%s", left.second);
	delete[] left.second;
	break;

    case POSTDECREMENT:
    case POSTINCREMENT:
	left = get(0).toString_(old);
	s = new char[strlen(left.second) + 5];
	if (precedence > left.first)
	    sprintf(s, "(%s)%s", left.second, 
		    getKind() == POSTDECREMENT ? "--" : "++");
	else
	    sprintf(s, "%s%s", left.second,
		    getKind() == POSTDECREMENT ? "--" : "++");
	delete[] left.second;
	break;
     
    case PREDECREMENT:
    case PREINCREMENT:
	left = get(0).toString_(old);
	s = new char[strlen(left.second) + 5];
	if (precedence > left.first)
	    sprintf(s, "%s(%s)", 
		    getKind() == PREDECREMENT ? "--" : "++", left.second);
	else
	    sprintf(s, "%s%s", 
		    getKind() == PREDECREMENT ? "--" : "++", left.second);
	delete[] left.second;
	break;

    case NOT:
	left = get(0).toString_(old);
	s = new char[strlen(left.second) + 4];
	if (precedence > left.first)
	    sprintf(s, "!(%s)", left.second);
	else
	    sprintf(s, "!%s", left.second);
	delete[] left.second;
	break;

    case DOT:
    {
	type_t base = get(0).getType().getBase();
	if (base == type_t::PROCESS || base == type_t::RECORD) {
	    left = get(0).toString_(old);
	    name = get(0).getType().getFrame()[data->value].getName();

	    s = new char[strlen(left.second) + 4 + strlen(name)];
	    if (precedence > left.first)
		sprintf(s, "(%s).%s", left.second, name);
	    else 
		sprintf(s, "%s.%s", left.second, name);
	    delete[] left.second;
	} else {
	    assert(0);
	}
	break;
    }	
	    
    case INLINEIF:	
	expr = get(0).toString_(old);
	left = get(1).toString_(old);
	right = get(2).toString_(old);

	s = new char[strlen(expr.second) + strlen(left.second)
		    + strlen(right.second) + 13];
	
	if (precedence >= expr.first)
	    sprintf(s, "(%s)", expr.second);
	else
	    strcpy(s, expr.second);
	
	strcat(s, " ? ");
	
	if (precedence >= left.first)
	    sprintf(s, "(%s)", left.second);
	else
	    strcat(s, left.second);

	strcat(s, " : ");

	if (precedence >= right.first)
	    sprintf(s, "(%s)", right.second);
	else
	    strcat(s, right.second);	    

	delete[] left.second;
	delete[] right.second;
	delete[] expr.second;
	break;

    case COMMA:
	left = get(0).toString_(old);
	right = get(1).toString_(old);
	s = new char[strlen(left.second) + strlen(right.second) + 3];
	sprintf(s, "%s, %s", left.second, right.second);
	break;
	    
    case SYNC:
	left = get(0).toString_(old);
	s = new char[strlen(left.second) + 2];
	switch (data->sync) {
	case SYNC_QUE:
	    sprintf(s, "%s?", left.second);
	    break;
	case SYNC_BANG:
	    sprintf(s, "%s!", left.second);
	    break;
	}
	delete[] left.second;
	break;

    case DEADLOCK:
	s = strcpy(new char[9], "deadlock");
	break;

    case LIST:
    {
	char *p[getSize()];
	int len = 0;
	for (uint32_t i = 0; i < getSize(); i++) {
	    p[i] = get(i).toString();
	    len += strlen(p[i]);
	}

	s = new char[len + getSize() * 2 + 2];
	sprintf(s, "{ %s", p[0]);
	delete[] p[0];
	for (uint32_t i = 1; i < getSize(); i++) {
	    strcat(s, ", ");
	    strcat(s, p[i]);
	    delete p[i];
	}
	strcat(s, " }");
	break;
    }

    case EF:
    case EG:
    case AF:
    case AG:
    case LEADSTO:
    case FUNCALL:
	assert(0); // FIXME
    }

    return make_pair(precedence, s);
}

/** Returns a string representation of the expression. The string
    returned must be deallocated with delete[]. Returns NULL is the
    expression is empty. */
char *expression_t::toString(bool old) const
{
    if (empty())
	return NULL;
    else
	return toString_(old).second;
}

expression_t expression_t::createConstant(
    const position_t &pos, int32_t value)
{
    expression_t expr(CONSTANT, pos);
    expr.data->value = value;
    expr.data->type = type_t::INT;
    return expr;
}

expression_t expression_t::createIdentifier(
    const position_t &pos, symbol_t symbol)
{
    expression_t expr(IDENTIFIER, pos);
    expr.data->symbol = symbol;
    if (symbol != symbol_t())
	expr.data->type = symbol.getType();
    else
	expr.data->type = type_t::UNKNOWN;
    return expr;
}

expression_t expression_t::createNary(
    const position_t &pos, kind_t kind,
    const vector<expression_t> &sub, type_t type)
{
    assert(kind == LIST || kind == FUNCALL);
    expression_t expr(kind, pos);
    expr.data->value = sub.size();
    expr.data->sub = new expression_t[sub.size()];
    expr.data->type = type;
    for (uint32_t i = 0; i < sub.size(); i++)
	expr.data->sub[i] = sub[i];
    return expr;
}

expression_t expression_t::createUnary(
    const position_t &pos, kind_t kind, expression_t sub, type_t type)
{
    expression_t expr(kind, pos);
    expr.data->sub = new expression_t[1];
    expr.data->sub[0] = sub;
    expr.data->type = type;
    return expr;
}

expression_t expression_t::createBinary(
    const position_t &pos, kind_t kind, 
    expression_t left, expression_t right, type_t type)
{
    expression_t expr(kind, pos);
    expr.data->sub = new expression_t[2];
    expr.data->sub[0] = left;
    expr.data->sub[1] = right;
    expr.data->type = type;
    return expr;
}

expression_t expression_t::createTernary(
    const position_t &pos, kind_t kind, 
    expression_t e1, expression_t e2, expression_t e3, type_t type)
{
    expression_t expr(kind, pos);
    expr.data->sub = new expression_t[3];
    expr.data->sub[0] = e1;
    expr.data->sub[1] = e2;
    expr.data->sub[2] = e3;
    expr.data->type = type;
    return expr;
}

expression_t expression_t::createDot(
    const position_t &pos, expression_t e, int32_t idx, type_t type)
{
    expression_t expr(DOT, pos);
    expr.data->index = idx;
    expr.data->sub = new expression_t[1];
    expr.data->sub[0] = e;
    expr.data->type = type;
    return expr;
}

expression_t expression_t::createSync(
    const position_t &pos, expression_t e, synchronisation_t s)
{
    expression_t expr(SYNC, pos);
    expr.data->sync = s;
    expr.data->sub = new expression_t[1];
    expr.data->sub[0] = e;
    return expr;
}

expression_t expression_t::createDeadlock(const position_t &pos)
{
    expression_t expr(DEADLOCK, pos);
    expr.data->type = type_t::CONSTRAINT;
    return expr;
}

Interpreter::Interpreter()
{

}

Interpreter::Interpreter(const std::map<symbol_t, expression_t> &valuation)
    : valuation(valuation)
{

}

void Interpreter::addValuation(const std::map<symbol_t, expression_t> &v)
{
    valuation.insert(v.begin(), v.end());
}
    
int32_t Interpreter::evaluate(const expression_t expr) const
    throw (InterpreterException)
{
    vector<int32_t> v;
    evaluate(expr, v);
    assert(v.size() == 1);
    return v[0];
}

int32_t Interpreter::evaluateBinary(int32_t left, kind_t op, int32_t right) const
{
    switch (op) {
    case PLUS:
	return left + right;
    case MINUS:
	return left - right;
    case MULT:
	return left * right;
    case DIV:
	return left / right;
    case MOD:
	return left % right;
    case BIT_AND:
	return left & right;
    case BIT_OR:
	return left | right;
    case BIT_XOR:
	return left ^ right;
    case BIT_LSHIFT:
	return left << right;
    case BIT_RSHIFT:
	return left >> right;
    case AND:
	return left && right;
    case OR:
	return left || right;
    case LT:
	return left < right;
    case LE:
	return left <= right;
    case EQ:
	return left == right;
    case NEQ:
	return left != right;
    case GE:
	return left >= right;
    case GT:
	return left > right;
    case MIN:
	return min(left, right);
    case MAX:
	return max(left, right);
    default:
	throw InterpreterException();
    }
}

void Interpreter::evaluate(
    const expression_t expr, std::vector<int32_t> &result) const
    throw (InterpreterException)
{
    int32_t left, right;
    
    switch (expr.getKind()) {
    case PLUS:
    case MINUS:
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
	evaluate(expr[0], result);
	evaluate(expr[1], result);
	right = result.back(); result.pop_back();
	left = result.back(); result.pop_back();
	result.push_back(evaluateBinary(left, expr.getKind(), right));
	break;

    case IDENTIFIER:
    {
	map<symbol_t, expression_t>::const_iterator i
	    = valuation.find(expr.getSymbol());
	if (i == valuation.end()) 
	    throw InterpreterException();

	evaluate(i->second, result);
	break;
    }
	
    case CONSTANT:
	result.push_back(expr.getValue());
	break;

    case LIST:
	for (uint32_t i = 0; i < expr.getSize(); i++)
	    evaluate(expr[i], result);
	break;
	    
    case ARRAY: {
	evaluate(expr[0], result);
	evaluate(expr[1], result);
	
	int index = result.back(); result.pop_back();
	type_t type = expr[0].getType();
	int32_t size = evaluate(type.getArraySize());
	int32_t subsize = sizeOfType(type.getSub());

	// Ensure that index is within range. REVISIT: This matches
	// the behaviour of the rest of UPPAAL, but it is not
	// nice. Once we fix this problem in UPPAAL we should also fix
	// it here.
	if (index < 0)
	    index = 0;
	if (index >= size)
	    index = size - 1;
	
	result.erase(result.end() - (size - index - 1) * subsize, result.end());
	result.erase(result.end() - (index + 1) * subsize, result.end() - subsize);
	break;
    }

    case UNARY_MINUS:
	evaluate(expr[0], result);
	result.back() = -result.back();
	break;

    case NOT:
	evaluate(expr[0], result);
	result.back() = !result.back();
	break;

    case DOT:
    {
	evaluate(expr[0], result);

	int index = expr.getIndex();
	frame_t frame = expr[0].getType().getRecordFields();
	int size = sizeOfType(frame[index].getType());
	
	// Delete data after index
	int space = 0;
	for (int i = frame.getSize() - 1; i > index; i--) 
	    space += sizeOfType(frame[i].getType());
	result.erase(result.end() - space, result.end());
	
	// Delete data before index
	space = 0;
	for (int i = index - 1; i >= 0; i--)
	    space += sizeOfType(frame[i].getType());
	result.erase(result.end() - space - size, result.end() - size);

	break;
    }	    
    
    case INLINEIF:
	evaluate(expr[0], result);
	evaluate(expr[1], result);
	evaluate(expr[2], result);
	right = result.back(); result.pop_back();
	left = result.back(); result.pop_back();
	result.back() = (result.back() ? left : right);
	break;
	    
    default:
	throw InterpreterException();
    }
}

range_t Interpreter::evaluate(
    std::pair<expression_t, expression_t> range) const
    throw (InterpreterException)
{
    return range_t(evaluate(range.first), evaluate(range.second));
}


/** Returns the number of integer elements needed to represent a
    variable of this type. */
int32_t Interpreter::sizeOfType(type_t type) const
{
    type_t base = type.getBase();
    if (base == type_t::CHANNEL || base == type_t::CLOCK || base == type_t::INT)
	return 1;
    if (base == type_t::ARRAY) {
	return evaluate(type.getArraySize()) * sizeOfType(type.getSub());
    }
    if (base == type_t::RECORD) {
	uint32_t sum = 0;
	frame_t frame = type.getRecordFields();
	for (uint32_t i = 0, size = frame.getSize(); i < size; i++)
	    sum += sizeOfType(frame[i].getType());
	return sum;
    }
    
    assert(0);
    return 0;
}

const map<symbol_t, expression_t> &Interpreter::getValuation() const
{
    return valuation;
}
