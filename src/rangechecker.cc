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
#include "utap/rangechecker.hh"

using std::map;
using std::min;
using std::max;
using std::list;
using std::vector;
using std::pair;

using namespace UTAP;
using namespace Constants;

RangeChecker::RangeChecker(TimedAutomataSystem *system)
    : system(system), interpreter(system->getConstantValuation())
{
    
}

RangeChecker::RangeChecker(TimedAutomataSystem *system, const process_t &proc)
    : system(system), interpreter(system->getConstantValuation())
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

    switch (op) {
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

/**
   Returns the declared range of a variable. The argument must be an
   expression referring to a variable. The range returned is the
   declared range of that variable, which might depend on the current
   mapping.
*/
range_t RangeChecker::getDeclaredRange(expression_t expr) const
{
    return getDeclaredRange(expr.getSymbol());
}

/**
   Returns the declared range of a variable. The argument must be the
   symbol of a variable. The range returned is the declared range of
   that variable, which might depend on the current mapping.
*/
range_t RangeChecker::getDeclaredRange(symbol_t symbol) const
{
    type_t type = symbol.getType();
    while (type.getBase() == type_t::ARRAY)
	type = type.getSub();
    if (type.getBase() == type_t::LOCATION)
	return range_t(0, 1);
    if (type.getBase() != type_t::INT) 
	throw UndefinedRangeException();

    try {
	return interpreter.evaluate(type.getRange());
    } catch (InterpreterException) {
	throw UndefinedRangeException();
    }
}

/** Returns the range of a symbol taking the current mapping
    into account.
*/
range_t RangeChecker::getRange(symbol_t symbol) const
{
    map<symbol_t, expression_t>::const_iterator i = 
	interpreter.getValuation().find(symbol);
    if (i != interpreter.getValuation().end())
	return getRange(i->second);
    return getDeclaredRange(symbol);
}

/** Returns the range of an expression taking the current mapping
    into account.
*/
range_t RangeChecker::getRange(expression_t expr) const
{
    range_t range;
    int32_t value;

    // If the evaluation failed, we need to compute the range
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
	try {
	    return range_t(interpreter.evaluate(expr));
	} catch (InterpreterException) {
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
	try {
	    return range_t(interpreter.evaluate(expr));
	} catch (InterpreterException) {
	    return getRange(expr[1]).join(getRange(expr[2]));
	}
      
    case COMMA:
	return getRange(expr[1]);
      
    case FUNCALL:
	throw UndefinedRangeException();
	// TODO
      
    case ARRAY:
	if (!expr.getSymbol().getType().hasPrefix(prefix::CONSTANT)) {
	    return getDeclaredRange(expr);
	}

	// First try to evaluate the expression.
	try {
	    return range_t(interpreter.evaluate(expr));
	} catch (InterpreterException) {
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
	try {
	    return range_t(interpreter.evaluate(expr));
	} catch (InterpreterException) {
	    return getDeclaredRange(expr);
	}

    case CONSTANT:
	return range_t(expr.getValue());

    default:
	throw UndefinedRangeException();
    }
    
}
#if 0
/** Check the integer ranges in the given expression. Any warnings and
    errors regarding out of range array indices and assignments are
    produced. NOTE: The worst case complexity of the current
    implementation is very bad. If necessary, we need to reimplement
    it using dynamic programming (i.e. return the range of
    expression). However, I believe this will not be an issue.
*/
void RangeChecker::checkRange(expression_t expr) 
{
    for (uint32_t i = 0; i < expr.getSize(); i++) 
	checkRange(expr[i]);

    range_t drange, range;
    int size;
    switch (expr.getKind()) {
    case ASSIGN:
	if (expr[1].getType().getBase() == type_t::INT) {
	    if (expr[0].getType().getBase() == type_t::INT) {
		drange = getDeclaredRange(expr[0]);
		range = getRange(expr[1]);
		if (range.lower > drange.upper || range.upper < drange.lower)
		    handleError(expr, "Assignment outside range");
		else if (range.lower < drange.lower || range.upper > drange.upper)
		    handleWarning(expr, "Assignment possibly outside range");
	    } else if (expr[0].getType().getBase() == type_t::CLOCK) {
		range = getRange(expr[1]);
		if (range.upper < 0)
		    handleError(expr,"Negative assignment to clock");
		else if (range.lower < 0)
		    handleWarning(expr, "Possibly negative assignment to clock");
	    }
	}
	break;
      
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
	drange = getDeclaredRange(expr[0]);
	switch (expr.getKind()) {
	case ASSPLUS:
	    range = rangeOfBinary(expr[0], PLUS, expr[1]);
	    break;
	case ASSMINUS:
	    range = rangeOfBinary(expr[0], MINUS, expr[1]);
	    break;
	case ASSDIV:
	    range = rangeOfBinary(expr[0], DIV, expr[1]);
	    break;
	case ASSMOD:
	    range = rangeOfBinary(expr[0], MOD, expr[1]);
	    break;
	case ASSMULT:
	    range = rangeOfBinary(expr[0], MULT, expr[1]);
	    break;
	case ASSAND:
	    range = rangeOfBinary(expr[0], BIT_AND, expr[1]);
	    break;
	case ASSOR:
	    range = rangeOfBinary(expr[0], BIT_OR, expr[1]);
	    break;
	case ASSXOR:
	    range = rangeOfBinary(expr[0], BIT_XOR, expr[1]);
	    break;
	case ASSLSHIFT:
	    range = rangeOfBinary(expr[0], BIT_LSHIFT, expr[1]);
	    break;
	case ASSRSHIFT:
	    range = rangeOfBinary(expr[0], BIT_RSHIFT, expr[1]);
	    break;
	default:
	    assert(0);
	}

	if (range.lower > drange.upper || range.upper < drange.lower)
	    handleError(expr, "Assignment outside range");
	else if (range.lower < drange.lower || range.upper > drange.upper)
	    handleWarning(expr, "Assignment possibly outside range");
	break;

    case POSTINCREMENT:
    case PREINCREMENT:
	range = getRange(expr[0]);
	drange = getDeclaredRange(expr[0]);
	if (range.upper + 1 > drange.upper)
	    handleWarning(expr, "Expression potentially out of range");
	break;
	
    case POSTDECREMENT:
    case PREDECREMENT:
	range = getRange(expr[0]);
	drange = getDeclaredRange(expr[0]);	
	if (range.lower - 1 < drange.lower)
	    handleWarning(expr, "Expression potentially out of range");
	break;
    
    case ARRAY:
	range = getRange(expr[1]);
	size = expr[0].getSymbol().getType().getArraySize();
	if (range.upper < 0 || range.lower >= size)
	    handleError(expr, "Index out of range");
	else if (range.lower < 0 || range.upper >= size)
	    handleWarning(expr, "Index possibly out of range");
	break;

    default:
	;
	// do nothing
    }
}

void RangeChecker::visitState(state_t &state)
{
    setContextInvariant(state);
    checkRange(state.invariant);
}

void RangeChecker::visitTransition(transition_t &transition)
{
    setContextGuard(transition);	
    checkRange(transition.guard);
    
    if (!transition.sync.empty()) {
 	setContextSync(transition);		
 	checkRange(transition.sync);
    }

    setContextAssignment(transition);	
    checkRange(transition.assign);
}

#endif
