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

#include <vector>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cassert>
#include <inttypes.h>

#include "utap/expressionbuilder.h"

using namespace UTAP;
using namespace Constants;

using std::vector;

#define defaultIntMin -0x7FFF
#define defaultIntMax 0x7FFF

void ExpressionBuilder::ExpressionFragments::pop(uint32_t n)
{
    assert(n <= size());
    while (n--) pop();
}

ExpressionBuilder::ExpressionBuilder(TimedAutomataSystem *system)
  : system(system)
{
    pushFrame(system->getGlobals().frame);
}

void ExpressionBuilder::pushFrame(frame_t frame)
{
    frames.push(frame);
}

void ExpressionBuilder::popFrame()
{
    frames.pop();
}

bool ExpressionBuilder::resolve(std::string name, symbol_t &uid)
{
    assert(!frames.empty());
    return frames.top().resolve(name, uid);
}

ExpressionBuilder::ExpressionFragments &ExpressionBuilder::getExpressions()
{
    return fragments;
}

bool ExpressionBuilder::isType(const char* name) 
{
    symbol_t uid;
    if (!resolve(name, uid))
    {
	return false;
    }
    return uid.getType().getBase() == type_t::NTYPE;
}

bool ExpressionBuilder::isLocation(const char *name)
{
    symbol_t uid;
    if (!resolve(name, uid))
    {
	return false;
    }
    return uid.getType() == type_t::LOCATION;
}

expression_t ExpressionBuilder::makeConstant(int value)
{
    return expression_t::createConstant(position, value);
}

type_t ExpressionBuilder::applyPrefix(int32_t prefix, type_t type)
{    
    type_t base = type.getBase();
    if (base == type_t::VOID_TYPE || base == type_t::CLOCK || base == type_t::SCALAR || base == type_t::COST) 
    {
	if (prefix == PREFIX_NONE)
	{
	    return type;
	}
    } 
    else if (base == type_t::INT || base == type_t::BOOL
	     || base == type_t::ARRAY || base == type_t::RECORD)
    {
	switch (prefix) 
	{
	case PREFIX_NONE:
	    return type;
	case PREFIX_CONST:
	    return type.setPrefix(true, prefix::CONSTANT);
	case PREFIX_META:
	    return type.setPrefix(true, prefix::META);
	}
    } 
    else if (base == type_t::CHANNEL) 
    {
	switch (prefix) 
	{
	case PREFIX_NONE:
	    return type;
	case PREFIX_URGENT:
	    return type.setPrefix(true, prefix::URGENT);
	case PREFIX_BROADCAST:
	    return type.setPrefix(true, prefix::BROADCAST);
	case PREFIX_URGENT_BROADCAST:
	    return type.setPrefix(true, prefix::URGENT).setPrefix(true, prefix::BROADCAST);
	}
    }
    errorHandler->handleError("Invalid prefix");
    return type;
}

/**
 * Push a new type onto the type stack. This type might subsequently
 * be used to declare e.g. variables. Range indicates the number range
 * or rate expressions (currently, it might be 0, 1 or 2). The
 * corresponding number of fragments will be popped from the
 * expression stack.
 */
void ExpressionBuilder::typeName(int32_t prefix, const char* name, int range)
{
    symbol_t uid;
    assert(resolve(name, uid));

    if (!resolve(name, uid) || uid.getType().getBase() != type_t::NTYPE)
    {
	typeFragments.push(type_t::VOID_TYPE);
	throw TypeException("Identifier is undeclared or not a type name");
    }

    type_t type = uid.getType().getSub();
    if (type == type_t::SCALAR)
    {
	if (range == 1)
	{
	    type = type_t::createScalarSet(
		makeConstant(0), 
		expression_t::createBinary(fragments[0].getPosition(),
					   MINUS, fragments[0], makeConstant(1)));
	}
	else
	{
	    errorHandler->handleError("Scalarset must have a size");
	}
    }
    else if (type == type_t::INT && range == 2)
    {
	type = type_t::createInteger(fragments[1], fragments[0]);
    }
    else if (range)
    {
	errorHandler->handleError("Invalid number of arguments for this type");
    }
    else if (type == type_t::INT && prefix != PREFIX_CONST)
    {
	type = type_t::createInteger(makeConstant(defaultIntMin),
				     makeConstant(defaultIntMax));
    }

    fragments.pop(range);
    typeFragments.push(applyPrefix(prefix, type));
}

void ExpressionBuilder::exprTrue() 
{
    fragments.push(makeConstant(1));
}

void ExpressionBuilder::exprFalse() 
{
    fragments.push(makeConstant(0));
}
    
void ExpressionBuilder::exprId(const char *name) 
{
    symbol_t uid;
    
    if (!resolve(name, uid)) 
    {
	exprFalse();
	throw TypeException("Unknown identifier: %s", name);
    }

    fragments.push(expression_t::createIdentifier(position, uid));

    type_t base = uid.getType().getBase();

    if (base != type_t::INT
	&& base != type_t::BOOL
	&& base != type_t::ARRAY
	&& base != type_t::CLOCK
	&& base != type_t::CHANNEL
	&& base != type_t::RECORD
	&& base != type_t::PROCESS
	&& base != type_t::COST
	&& base != type_t::VOID_TYPE
	&& base != type_t::FUNCTION
	&& base != type_t::SCALAR)
    {
	throw TypeException("Identifier of this type cannot be referenced in an expression");
    }    
}

void ExpressionBuilder::exprDeadlock()
{
    fragments.push(expression_t::createDeadlock(position));
}

void ExpressionBuilder::exprNat(int32_t n) 
{
    fragments.push(makeConstant(n));
}

void ExpressionBuilder::exprCallBegin() 
{
}

// expects n argument expressions on the stack
void ExpressionBuilder::exprCallEnd(uint32_t n) 
{
    /* exprCallBegin() pushes symbol_t() if and only if the identifier
     * is undeclared: In that case we pop the fragments and push a
     * dummy expression to recover from the error.
     */
    symbol_t id = fragments[n].getSymbol();
    if (id == symbol_t())
    {
	fragments.pop(n + 1);
	exprFalse();
	return;
    }

    /* If id is a function call, then retrieve the type.
     */
    type_t result = type_t::VOID_TYPE;
    if (id.getType().getBase() == type_t::FUNCTION)
    {
	result = id.getType().getSub();
    }

    /* Create vector of sub expressions: The first expression
     * evaluates to the function. The remaining expressions are the
     * arguments.
     */
    vector<expression_t> expr;
    for (int i = n; i >= 0; i--)
    {
	expr.push_back(fragments[i]);
    }
    fragments.pop(n + 1);

    /* Create the function call expression.
     */
    fragments.push(expression_t::createNary(position, FUNCALL, expr, result));
}

// expects 1 expression on the stack
void ExpressionBuilder::exprArg(uint32_t n) 
{

}

// 2 expr     // array[index]
void ExpressionBuilder::exprArray() 
{
    // Pop sub-expressions
    expression_t var = fragments[1];
    expression_t index = fragments[0];
    fragments.pop(2);

    type_t element;
    type_t type = var.getType();
    if (type.getBase() == type_t::ARRAY) 
    {
	element = type.getSub();
    }
    else 
    {
	element = type_t::UNKNOWN;
    }

    fragments.push(expression_t::createBinary(
	position, ARRAY, var, index, element));
}

// 1 expr
void ExpressionBuilder::exprPostIncrement() 
{
    fragments[0] = expression_t::createUnary(
	position, POSTINCREMENT, fragments[0], fragments[0].getType());
}
    
void ExpressionBuilder::exprPreIncrement() 
{
    fragments[0] = expression_t::createUnary(
	position, PREINCREMENT, fragments[0], fragments[0].getType());
}
    
void ExpressionBuilder::exprPostDecrement() // 1 expr
{
    fragments[0] = expression_t::createUnary(
	position, POSTDECREMENT, fragments[0], fragments[0].getType());
}
    
void ExpressionBuilder::exprPreDecrement() 
{
    fragments[0] = expression_t::createUnary(
	position, PREDECREMENT, fragments[0], fragments[0].getType());
}
    
void ExpressionBuilder::exprAssignment(kind_t op) // 2 expr
{
    expression_t lvalue = fragments[1];
    expression_t rvalue = fragments[0];
    fragments.pop(2);
    fragments.push(expression_t::createBinary(
	position, op, lvalue, rvalue, lvalue.getType()));
}

void ExpressionBuilder::exprUnary(kind_t unaryop) // 1 expr
{
    switch (unaryop)
    {
    case PLUS:
	/* Unary plus can be ignored */
	break;
    case MINUS:
	unaryop = UNARY_MINUS;
	/* Fall through! */
    default:
	fragments[0] = expression_t::createUnary(position, unaryop, fragments[0]);
    }
}
    
void ExpressionBuilder::exprBinary(kind_t binaryop) // 2 expr
{
    expression_t left = fragments[1];
    expression_t right = fragments[0];
    fragments.pop(2);
    fragments.push(expression_t::createBinary(
	position, binaryop, left, right));
}

void ExpressionBuilder::exprInlineIf()
{
    expression_t c = fragments[2];
    expression_t t = fragments[1];
    expression_t e = fragments[0];
    fragments.pop(3);
    fragments.push(expression_t::createTernary(
	position, INLINEIF, c, t, e, t.getType()));    
}

void ExpressionBuilder::exprComma()
{
    expression_t e1 = fragments[1];
    expression_t e2 = fragments[0];
    fragments.pop(2);
    fragments.push(expression_t::createBinary(
	position, COMMA, e1, e2, e2.getType()));
}

void ExpressionBuilder::exprDot(const char *id)
{
    expression_t expr = fragments[0];
    type_t type = expr.getType();
    if (type.getBase() == type_t::RECORD || type.getBase() == type_t::PROCESS)
    {
	frame_t fields = type.getFrame();
	int i = fields.getIndexOf(id);
	if (i == -1) 
	{
	    std::string s = expr.toString(true);
	    errorHandler->handleError("%s has no member named %s",
				      s.c_str(), id);
	    expr = expression_t::createDot(position, expr);
	} 
	else if (fields[i].getType().getBase() == type_t::LOCATION) 
	{
	    expr = expression_t::createDot(position, expr, i, type_t::INT);
	}
	else 
	{
	    expr = expression_t::createDot(position, expr,
					   i, fields[i].getType());
	}
    } 
    else 
    {
	expr = expression_t::createDot(position, expr);
	errorHandler->handleError("This is not a structure");
    }
    fragments[0] = expr;
}

void ExpressionBuilder::exprForAllBegin(const char *name)
{
    type_t type = typeFragments[0].first;
    typeFragments.pop();
    
    pushFrame(frame_t::createFrame(frames.top()));
    symbol_t symbol = frames.top().addSymbol(name, type);

    if (type.getBase() != type_t::INT && type.getBase() != type_t::SCALAR)
    {
	errorHandler->handleError("Quantifier must range over scalar type");
    }
}

void ExpressionBuilder::exprForAllEnd(const char *name)
{
    /* Create the forall expression. The symbol is added as an identifier
     * expression as the first child. Notice that the frame is discarded
     * but the identifier expression will maintain a reference to the
     * symbol so it will not be deallocated.
     */
    fragments[0] = expression_t::createBinary(
	position, FORALL, 
	expression_t::createIdentifier(position, frames.top()[0]), fragments[0]);
    popFrame();
}
