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

#include <cmath>
#include "utap/rangechecker.h"

using std::map;
using std::min;
using std::max;
using std::list;
using std::vector;
using std::pair;

using namespace UTAP;
using namespace Constants;

RangeChecker::RangeChecker(const std::map<symbol_t, expression_t> &valuation)
    : interpreter(valuation)
{

}

RangeChecker::RangeChecker(TimedAutomataSystem *system)
    : interpreter(system->getConstantValuation())
{
    
}

RangeChecker::RangeChecker(TimedAutomataSystem *system, const process_t &proc)
    : interpreter(system->getConstantValuation())
{
    interpreter.addValuation(proc.mapping);
}

/** Returns the range of a binary expression. */
range_t RangeChecker::rangeOfBinary(
    expression_t left, uint32_t op, expression_t right) const
{
    int32_t t1, t2, t3, t4;
    range_t lrange = getRange(left);
    range_t rrange = getRange(right);

    switch (op) 
    {
    case MINUS:
	return range_t(lrange.lower - rrange.upper,
		       lrange.upper - rrange.lower);
    case PLUS:
	return range_t(lrange.lower + rrange.lower,
		       lrange.upper + rrange.upper);
    case MULT:
	t1 = lrange.lower * rrange.lower;
	t2 = lrange.lower * rrange.upper;
	t3 = lrange.upper * rrange.lower;
	t4 = lrange.upper * rrange.upper;
	return range_t(min(min(t1, t2), min(t3, t4)), 
		       max(max(t1, t2), max(t3, t4)));
    case DIV:
	t1 = lrange.lower / (rrange.lower == 0 ? 1 : rrange.lower);
	t2 = lrange.lower / (rrange.upper == 0 ? -1 : rrange.upper);
	t3 = lrange.upper / (rrange.lower == 0 ? 1 : rrange.lower);
	t4 = lrange.upper / (rrange.upper == 0 ? -1 : rrange.upper);
	return range_t(min(min(t1, t2), min(t3, t4)),
		       max(max(t1, t2), max(t3, t4)));
    case MOD:
	t1 = max(abs(rrange.lower), abs(rrange.upper));
	return range_t(min(max(lrange.lower, -t1), 0),
		       max(min(lrange.upper, t1), 0));
    case MIN:
	return range_t(min(lrange.lower, rrange.lower),
		       min(lrange.upper, rrange.upper));
    case MAX:
	return range_t(max(lrange.lower, rrange.lower),
		       max(lrange.upper, rrange.upper));
    case BIT_AND:
	t1 = max(max(abs(lrange.lower), abs(lrange.upper)),
		 max(abs(rrange.lower), abs(rrange.upper)));
	t2 = (1 << (int32_t)ceil(log(t1) / log(2))) - 1;
	t3 = (lrange.lower < 0 && rrange.lower < 0 ? -t2 : 0);
	t4 = (lrange.lower >= 0 || rrange.lower >= 0 ? t2 : 0);
	return range_t(t3, t4);
    case BIT_OR:
	t1 = max(max(abs(lrange.lower), abs(lrange.upper)),
		 max(abs(rrange.lower), abs(rrange.upper)));
	t2 = (1 << (int32_t)ceil(log(t1) / log(2))) - 1;
	t3 = (lrange.lower < 0 || rrange.lower < 0 ? -t2 : 0);
	t4 = (lrange.lower >= 0 && rrange.lower >= 0 ? t2 : 0);
	return range_t(t3, t4);
    case BIT_XOR:
	t1 = max(max(abs(lrange.lower), abs(lrange.upper)),
		 max(abs(rrange.lower), abs(rrange.upper)));
	t2 = (1 << (int32_t)ceil(log(t1) / log(2))) - 1;
	t3 = (lrange.lower < 0 || rrange.lower < 0 ? -t2 : 0);
	t4 = (lrange.lower >= 0 || rrange.lower >= 0 ? t2 : 0);
	return range_t(t3, t4);
    case BIT_LSHIFT:
	return range_t(lrange.lower << rrange.lower,
			 lrange.upper << rrange.upper);
    case BIT_RSHIFT:
	return range_t(lrange.lower >> rrange.upper,
			 lrange.upper >> rrange.lower);
    }
    throw UndefinedRangeException();
}

bool RangeChecker::isInteger(expression_t expr) const
{
    return expr.getType().getBase() == type_t::INT
	|| expr.getType().getBase() == type_t::BOOL;
}

/**
   Returns the range of a variable. The argument must be an
   expression referring to a variable. 
*/
range_t RangeChecker::getDeclaredRange(expression_t expr) const
{
    symbol_t symbol = expr.getSymbol();
    if (symbol == symbol_t())
    {
	throw UndefinedRangeException();
    }
    return getDeclaredRange(symbol);
}

/**
 * Returns the range of a symbol. If the symbol is a constant value,
 * then this value is returned. Otherwise the declared range is
 * returned. The function substitutes formal parameters with actual
 * arguments before computing the range. In case of arrays, the range
 * of the base type is returned.
 */
range_t RangeChecker::getDeclaredRange(symbol_t symbol) const
{
    map<symbol_t, expression_t>::const_iterator i = 
	interpreter.getValuation().find(symbol);
    if (i != interpreter.getValuation().end()) 
    {
	if (symbol.getType().hasPrefix(prefix::REFERENCE)) 
	{
	    symbol_t symbol = i->second.getSymbol();
	    if (symbol != symbol_t())
	    {
		return getDeclaredRange(symbol);
	    }
	    
	    if (symbol.getType().hasPrefix(prefix::CONSTANT))
	    {
		return getRange(i->second);
	    }

	    throw UndefinedRangeException();
	}

	if (symbol.getType().hasPrefix(prefix::CONSTANT))
	    return getRange(i->second);
    }

    return getRange(symbol.getType());
}

range_t RangeChecker::getRange(type_t type) const
{
    type_t base = type.getBase();
    while (base == type_t::ARRAY) 
    {
	type = type.getSub();
 	base = type.getBase();
    }
    if (base == type_t::LOCATION)
    {
 	return range_t(0, 1);
    }
    if (base == type_t::BOOL)
    {
 	return range_t(0, 1);
    }
    if (base != type_t::INT) 
    {
 	throw UndefinedRangeException();}
    
    try 
    {
	return interpreter.evaluate(type.getRange());
    }
    catch (InterpreterException) 
    {
	throw UndefinedRangeException();
    }
}

/** Returns the range of an expression taking the current mapping
    into account.
*/
range_t RangeChecker::getRange(expression_t expr) const
{
    range_t range;

    switch (expr.getKind()) 
    {
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
    case MIN:
    case MAX:
	return rangeOfBinary(expr[0], expr.getKind(), expr[1]);

    case AND:
    case OR:
    case LT:
    case LE:
    case EQ:
    case NEQ:
    case GE:
    case GT:
    case NOT:
	try 
	{
	    return range_t(interpreter.evaluate(expr));
	}
	catch (InterpreterException) 
	{
	    return range_t(0,1);
	}

    case UNARY_MINUS:
	range = getRange(expr[0]);
	return range_t(-range.upper, -range.lower);

    case ASSIGN:
	return getDeclaredRange(expr[0]).intersect(getRange(expr[0]));
      
    case ASSPLUS:
	return getDeclaredRange(expr[0]).intersect(
	    rangeOfBinary(expr[0], PLUS, expr[1]));
	
    case ASSMINUS:
	return getDeclaredRange(expr[0]).intersect(
	    rangeOfBinary(expr[0], MINUS, expr[1]));

    case ASSDIV:
	return getDeclaredRange(expr[0]).intersect(
	    rangeOfBinary(expr[0], DIV, expr[1]));

    case ASSMOD:
	return getDeclaredRange(expr[0]).intersect(
	    rangeOfBinary(expr[0], MOD, expr[1]));

    case ASSMULT:
	return getDeclaredRange(expr[0]).intersect(
	    rangeOfBinary(expr[0], MULT, expr[1]));

    case ASSAND:
	return getDeclaredRange(expr[0]).intersect(
	    rangeOfBinary(expr[0], BIT_AND, expr[1]));
	
    case ASSOR:
	return getDeclaredRange(expr[0]).intersect(
	    rangeOfBinary(expr[0], BIT_OR, expr[1]));

    case ASSXOR:
	return getDeclaredRange(expr[0]).intersect(
	    rangeOfBinary(expr[0], BIT_XOR, expr[1]));

    case ASSLSHIFT:
	return getDeclaredRange(expr[0]).intersect(
	    rangeOfBinary(expr[0], BIT_LSHIFT, expr[1]));

    case ASSRSHIFT:
	return getDeclaredRange(expr[0]).intersect(
	    rangeOfBinary(expr[0], BIT_RSHIFT, expr[1]));
      
    case POSTINCREMENT:
    case POSTDECREMENT:
	return getRange(expr[0]);
	
    case PREINCREMENT:
	range = getRange(expr[0]);
	return range_t(range.lower + 1, range.upper);

    case PREDECREMENT:
	range = getRange(expr[0]);
	return range_t(range.lower, range.upper - 1);
    
    case INLINEIF:
	try 
	{
	    return range_t(interpreter.evaluate(expr));
	}
	catch (InterpreterException) 
	{
	    return getRange(expr[1]).join(getRange(expr[2]));
	}
      
    case COMMA:
	return getRange(expr[1]);
      
    case FUNCALL:
	return getRange(expr.getType());
      
    case ARRAY:
	if (!expr.getSymbol().getType().hasPrefix(prefix::CONSTANT)) 
	{
	    return getDeclaredRange(expr);
	}

	// First try to evaluate the expression.
	try 
	{
	    return range_t(interpreter.evaluate(expr));
	}
	catch (InterpreterException) 
	{
	    // In case evaluation fails, we must compute a range based
	    // on the initialiser of the array. This is because
	    // constant integers do not have a declared range.
	    vector<int32_t> result;
	    interpreter.evaluate(expression_t::createIdentifier(
				     position_t(), expr.getSymbol()),
				 result);
	    for (uint32_t i = 0; i < result.size(); i++)
		range = range.join(range_t(result[i]));
	    return range;
	}
	
    case IDENTIFIER:
    case DOT:
	try 
	{
	    return range_t(interpreter.evaluate(expr));
	}
	catch (InterpreterException) 
	{
	    return getDeclaredRange(expr);
	}

    case CONSTANT:
	return range_t(expr.getValue());

    default:
	throw UndefinedRangeException();
    }
    
}
