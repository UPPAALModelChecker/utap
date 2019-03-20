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

// TODO: 
//      don't copy template when assigning one process to another
//      add support for functions

#include <list>
#include <stack>
#include <vector>
#include <climits>

#include <inttypes.h>
#include <math.h>
#include <stdio.h>

#include "utap/typechecker.hh"

using namespace UTAP;
using namespace Constants;

using std::vector;
using std::pair;
using std::make_pair;
using std::min;
using std::max;

const char *const TypeChecker::unsupported =
"Internal error: Feature not supported in this mode.";
const char *const TypeChecker::invalid_type = "Invalid type";

void TypeChecker::ExpressionFragments::pop(int32_t n)
{
    while (n--) pop();
}

// Merges 'number' topmost expression fragments by appending the
// topmost to the end of the lowest of the 'number' fragments. The
// number - 1 topmost fragments are popped from the expression stack.
void TypeChecker::ExpressionFragments::merge(uint32_t number) 
{
    for (uint32_t i = data.size() - number + 1; i < data.size(); i++)
	data[data.size() - number].insert(data[data.size() - number].end(),
					  data[i].begin(),
					  data[i].end());
    for (uint32_t i = 1; i < number; i++)
	pop();
}

TypeChecker::TypeChecker(TimedAutomataSystem *sys)
    : types(sys->getTypeSystem()), symbols(sys->getSymbolTable())
{
    system = sys;
    strict_range = false;
    currentFun = NULL;

    guard = sync = update = -1;

    BOOL = types.addInteger(0, 1);
};

void TypeChecker::setErrorHandler(ErrorHandler *value)
{
    errorHandler = value;
}

// Clears the given vector, the strings are deleted first
void TypeChecker::clear_params(vector<pair<char*, int32_t> > &params) 
{
    uint32_t i;
    for (i = 0; i < params.size(); i++) {
	delete [] params[i].first;
    }
    params.clear();
}
    
// checks whether parameter type is compatible to argument type
char* TypeChecker::isParameterCompatible(int32_t param, int32_t argument)
{
    if (!types.isConstant(param) && types.isConstant(argument)) {
	return "non-constant argument expected here";
    }

    if (!types.isReference(param) && !types.isConstant(argument)) {
	return "constant argument expected here";
    }
    
    if (types.isReference(param) && !types.isConstant(param) &&
	!types.isReference(argument))
    {
	return "reference argument expected here";
    }
    
    switch (types.getClass(param)) {
    case TypeSystem::CLOCK:
	if (types.getClass(argument) != TypeSystem::CLOCK)
	    return "clock argument expected";
	break;
    case TypeSystem::INT:
	if (types.getClass(argument) != TypeSystem::INT) {
	    return "integer argument expected";
	} else {
	    // Check the range of the argument: It must be within the
	    // range of the parameter. For non constant reference parameters
	    // the range must be an exact match, since the process/function
	    // might update the variable referenced in the argument.
	    pair<int32_t,int32_t> prange = types.getIntegerRange(param);
	    pair<int32_t,int32_t> arange = types.getIntegerRange(argument);
	    if (!(prange.first <= arange.first && 
		  arange.second <= prange.second)) {
		return "argument has incompatible range";
	    }
	    if (types.isReference(param) && !types.isConstant(param)) {
		if (prange != arange) {
		    return "argument has incompatible range";
		}
	    }
	}
	break;
    case TypeSystem::RECORD:
	if (types.getClass(argument) == TypeSystem::RECORD) {
	    if (types.clearFlags(param) != types.clearFlags(argument))
		    return "argument value type does not match "
			"parameter type";
	} else {
	    return "record argument expected";
	}
	break;
    case TypeSystem::ARRAY:
	do {
	    if (types.getClass(argument) != TypeSystem::ARRAY) {
		return "Incompatible argument to array parameter";
	    }

	    pair<int32_t,int32_t> asize =
		types.getIntegerRange(types.getFirstSubType(argument));
	    pair<int32_t,int32_t> psize = 
		types.getIntegerRange(types.getFirstSubType(param));
	    if (asize != psize)
		return "parameter array size does not match argument array size";
	    param = types.getSecondSubType(param);
	    argument = types.getSecondSubType(argument);	    
	} while (types.getClass(param) == TypeSystem::ARRAY);

	if (types.getClass(argument) != types.getClass(param)) 
	    return "Incompatible argument to array parameter";

	if (types.getClass(argument) == TypeSystem::INT) {
	    pair<int32_t, int32_t> prange = types.getIntegerRange(param);
	    pair<int32_t, int32_t> arange = types.getIntegerRange(argument);
	    if (prange != arange) {
		return "Argument has incompatible range";
	    }
	}   

	break;
    case TypeSystem::CHANNEL:
	if (types.getClass(argument) != TypeSystem::CHANNEL)
	    return "channel argument expected";
	break;
    case TypeSystem::UCHANNEL:
	    if (types.getClass(argument) != TypeSystem::UCHANNEL)
		return "urgent channel argument expected";
	    break;
    case TypeSystem::BCHANNEL:
	if (types.getClass(argument) != TypeSystem::BCHANNEL)
	    return "broadcast channel argument expected";
	break;
    case TypeSystem::UBCHANNEL:
	if (types.getClass(argument) != TypeSystem::UBCHANNEL)
	    return "urgent broadcast channel argument expected";
	break;
    case TypeSystem::VOID_TYPE:
    case TypeSystem::LOCATION:
    case TypeSystem::CLOCATION:
    case TypeSystem::ULOCATION:
    case TypeSystem::NTYPE:
    case TypeSystem::TEMPLATE:
    case TypeSystem::FUNCTION:
    default:
	throw TypeException(unsupported);
    }
    return NULL;
}

// Check whether an expression of type rvalue can be assigned to an
// expression of type lvalue. Throw an exception if this is not the
// case.
void TypeChecker::checkAssignmentCompatible(int32_t lvalue, int32_t rvalue) 
{
    checkLValue(lvalue, "Left side value is a constant or not a reference");
    
    switch (types.getClass(lvalue)) {
    case TypeSystem::VOID_TYPE:
	throw TypeException("Cannot assign type VOID");
    case TypeSystem::CLOCK:
    {
	if (types.getClass(rvalue) != TypeSystem::INT)
	    throw TypeException("Assignment of non integer expression to clock");
	const pair<int32_t,int32_t> range = types.getIntegerRange(rvalue);
	
	if (range.first < 0)
	    errorHandler->handleWarning("Possibly negative assignment to clock");
	
	if (range.second < 0)
	    throw TypeException("Negative assignment to clock");

	break;    
    }
    case TypeSystem::INT:
    {
	if (types.getClass(rvalue) != TypeSystem::INT) 
	    throw TypeException("Assignment non integer type to integer");
	
	const pair<int32_t,int32_t> lrange = types.getIntegerRange(lvalue);
	const pair<int32_t,int32_t> rrange = types.getIntegerRange(rvalue);

	
	// The range of the right side must be contained in the range of the left side
	if (rrange.first < lrange.first || rrange.second > lrange.second)
	{
	    errorHandler->handleWarning("Assignment possibly outside range");
	}
	
	// We just require overlap
	if (!(lrange.first <= rrange.second || rrange.first <= lrange.second)) {
	    throw TypeException("Assignment outside range");
	}
	break;
    }

    case TypeSystem::RECORD:
	if (types.getClass(rvalue) != TypeSystem::RECORD) 
	    throw TypeException("Assignment of non record to record");

	if ( !(types.clearFlags(rvalue) == types.clearFlags(lvalue) ) ) {
	    throw TypeException("Assignment of non matching record type");
	}
	break;
    case TypeSystem::ARRAY:
    case TypeSystem::CHANNEL:	       
    case TypeSystem::UCHANNEL:
    case TypeSystem::BCHANNEL:
    case TypeSystem::UBCHANNEL:
    case TypeSystem::LOCATION:
    case TypeSystem::CLOCATION:
    case TypeSystem::ULOCATION:
    case TypeSystem::NTYPE:
    case TypeSystem::TEMPLATE:
    case TypeSystem::FUNCTION:
	throw TypeException("Assignment to non assignable type");
	break;
    default:
	throw TypeException(unsupported);
    }
}
    
/********************************************************************
 * Utility functions
 */

// Ensure that uid is defined (not -1) and that it is a location.
// Otherwise throw an error with the given error message.
void TypeChecker::checkLocation(int32_t uid, const char *error)
{
    if (uid == -1 || types.getClass(symbols.getType(uid)) != TypeSystem::LOCATION)
	throw TypeException(error);
}

void TypeChecker::checkClass(int32_t type, int32_t expected, 
				  const char *err) 
{
    if (types.getClass(type) != expected)
	throw TypeException(err);
}

void TypeChecker::checkLValue(int32_t type, const char *err) 
{
    if (!types.isReference(type) || types.isConstant(type))
	throw TypeException(err);
}

int32_t TypeChecker::makeConstantIf(bool cond, int32_t type) 
{
    return (cond ? types.makeConstant(type) : type);
}

int32_t TypeChecker::makeSideEffectFreeIf(bool cond, int32_t type) 
{
    return (cond ? types.makeSideEffectFree(type) : type);
}

int32_t TypeChecker::makeReferenceIf(bool cond, int32_t type) 
{
    return (cond ? types.makeReference(type) : type);
}

bool TypeChecker::isInteger(int32_t type) 
{
    return types.getClass(type) == TypeSystem::INT;
}

bool TypeChecker::isClock(int32_t type) 
{
    return types.getClass(type) == TypeSystem::CLOCK;
}

bool TypeChecker::isDiff(int32_t type) 
{
    return types.getClass(type) == TypeSystem::DIFF;
}

// Returns true iff type is a valid invariant. A valid invariant is
// either an invariant expression or an integer expression.
bool TypeChecker::isInvariant(int32_t type) 
{
    return (types.getClass(type) == TypeSystem::INVARIANT)
	|| (types.getClass(type) == TypeSystem::INT);
}

// Returns true iff type is a valid guard. A valid guard is either
// a valid invariant or a guard expression.
bool TypeChecker::isGuard(int32_t type) 
{
    return (types.getClass(type) == TypeSystem::GUARD)
	|| isInvariant(type);
}

// Returns true iff type is a valid constraint. A valid constraint 
// is either a valid guard or a constraint expression.
bool TypeChecker::isConstraint(int32_t type) 
{
    return (types.getClass(type) == TypeSystem::CONSTRAINT)
	|| isGuard(type);
}

// Returns true if expr result is a reference to local variable
bool TypeChecker::isTemporary(ExpressionProgram &expr)
{
    if (currentFun==NULL) return false;
    else {
	bool res;
	vector<bool> results;
	int32_t frame, current = currentFun->body->frameId;
	ExpressionProgram::const_iterator first, last;
	for (first = expr.begin(), last = expr.end(); first != last; ++first) {
	    switch(first->kind) {
	    case IDENTIFIER:
		frame = symbols.getFrameOf(first->value);
		while (frame!=-1 && frame!=current)
		    frame = symbols.getParentFrame(frame);
		results.push_back(frame == current);
		break;
	    case CONSTANT:
		results.push_back(true);
		break;
	    case ARRAY:
		results.pop_back();
		break;
	    case POSTINCREMENT:
	    case PREINCREMENT:
	    case PREDECREMENT:
	    case POSTDECREMENT:
	    case UNARY_MINUS:
	    case CONSTRAINT:
	    case SYNC:
		break;
	    case COMMA:
		res = results.back();
		results.pop_back();
		results.back() = res;
		break;
	    case DOT:
		break;
	    case INLINEIF:
		res = results.back();
		results.pop_back();
		res = res || results.back();
		results.pop_back(); 
		results.pop_back();
		results.push_back(res);
	        break;
	    default:
		assert(false);
	    }
	}
	assert(results.size()==1);
	res = results.back();
	results.pop_back();
	return res;
    }
}

// Returns the size of an array
int TypeChecker::getArraySize(int32_t type)
{
    return types.getIntegerRange(types.getFirstSubType(type)).second + 1;
}

int32_t TypeChecker::getBaseType(int32_t type)
{
    while (types.getClass(type) == TypeSystem::ARRAY)
	type = types.getSecondSubType(type);
    return type;
}

/********************************************************************
 * Query functions (these are used by the lexical analyzer)
 */

// isType(name): true if name is registered in the symbol table as
// a named type (a.k.a. type name), e.g. "int" or "bool" or a user
// defined type. 
bool TypeChecker::isType(const char* name) 
{
    int32_t uid = symbols.resolve(name);
    return (uid > -1)
	&& (types.getClass(symbols.getType(uid)) == TypeSystem::NTYPE);
}

bool TypeChecker::isLocation(const char *name)
{
    int32_t uid = symbols.resolve(name);
    return (uid > -1)
	&& (types.getClass(symbols.getType(uid)) == TypeSystem::LOCATION);
}

/********************************************************************
 * Types
 */


// Given a type and dim constant expressions on the expression stack,
// this function constructs and returns an array type using the type
// as the base type and the expressions as the array size (or sizes in
// case it is a multidimensional array). The expressions are popped of
// the expression stack.
uint32_t TypeChecker::buildArrayType(uint32_t type, uint32_t dim)
{
    uint32_t i;
    try {
	for (i = 0; i < dim; i++) {
	    int32_t n = 1;
	    if (!system->evaluateConstantExpression(fragments[0], n))
		errorHandler->handleError("Array size incomputable at parse time.");
	    if (n < 1) {
		errorHandler->handleError("Invalid array size");
		n = 1;
	    }
	    type = makeConstantIf(
		types.isConstant(type),
		types.addArray(types.addInteger(0, n - 1), type));
	    fragments.pop();
	}
    } catch (const TypeException e) {
	// In case of an error, pop the remaining expression
	for (; i < dim; i++)
	    fragments.pop();
	throw e;
    } 
    return type;
}

// Given a prefix and a type, this method creates a new type by
// applying the prefix. TypeExceptions might be thrown if the
// combination of the prefix and the type is illegal.
int32_t TypeChecker::applyPrefix(uint32_t prefix, int32_t type)
{    
    switch (types.getClass(type)) {
    case TypeSystem::VOID_TYPE:
    case TypeSystem::CLOCK:
	if (prefix == PREFIX_NONE)
	    return type;
	break;

    case TypeSystem::INT:
    case TypeSystem::ARRAY:
    case TypeSystem::RECORD:
	switch (prefix) {
	case PREFIX_NONE:
	    return type;
	case PREFIX_CONST:
	    return types.makeConstant(type);
	}
	break;
	
    case TypeSystem::CHANNEL:
	switch (prefix) {
	case PREFIX_NONE:
	    return TypeSystem::CHANNEL;
	case PREFIX_URGENT:
	    return TypeSystem::UCHANNEL;
	case PREFIX_BROADCAST:
	    return TypeSystem::BCHANNEL;
	case PREFIX_URGENT_BROADCAST:
	    return TypeSystem::UBCHANNEL;
	}
	break;
	
    case TypeSystem::UCHANNEL:
	switch (prefix) {
	case PREFIX_NONE:
	case PREFIX_URGENT:
	    return TypeSystem::UCHANNEL;
	case PREFIX_BROADCAST:
	case PREFIX_URGENT_BROADCAST:
	    return TypeSystem::UBCHANNEL;
	}
	break;
	
    case TypeSystem::BCHANNEL:
	switch (prefix) {
	case PREFIX_NONE:
	case PREFIX_BROADCAST:
	    return TypeSystem::BCHANNEL;
	case PREFIX_URGENT:
	case PREFIX_URGENT_BROADCAST:
	    return TypeSystem::UBCHANNEL;
	}
	break;
	
    case TypeSystem::UBCHANNEL:
	switch (prefix) {
	case PREFIX_NONE:
	case PREFIX_BROADCAST:
	case PREFIX_URGENT:
	case PREFIX_URGENT_BROADCAST:
	    return TypeSystem::UBCHANNEL;
	}
	break;
    }

    errorHandler->handleError("Invalid prefix");
    return type;
}

// Push a new type onto the type stack. This type might subsequently
// be used to declare e.g. variables. If range is true, then we expect
// two constant expressions on the expression stack encoding the
// beginning and end of the range. These fragments will be popped from
// the expression stack.
void TypeChecker::declType(uint32_t prefix, const char* name, bool range)
{
    int32_t uid = symbols.resolve(name);
    type_t type = symbols.getType(uid);
    type_t stype = types.getFirstSubType(type);

    assert(types.getClass(type) == TypeSystem::NTYPE);

    if (range) {
	try {
	    if (types.getClass(stype) != TypeSystem::INT) 
		throw TypeException("Range is only valid with integer types");
	    
	    int32_t lower, upper;
	    if (!system->evaluateConstantExpression(fragments[1], lower)) 
		throw TypeException("Lower bound incomputable at parse time");
	    if (!system->evaluateConstantExpression(fragments[0], upper))
		throw TypeException("Upper bound incomputable at parse time");

	    // Check if this is a valid range. In fact, equality would
	    // also be rather useless, but it is semantically well
	    // defined.
	    if (lower > upper) {
		errorHandler->handleError("Invalid integer range");
		upper = lower;
	    }

	    stype = types.addInteger(lower, upper);
	    
	    fragments.pop(2);
	} catch (TypeException &e) {
	    fragments.pop(2);
	    typeFragments.push(stype);	
	    throw e;
	}
    } else if (prefix == PREFIX_CONST && types.getClass(stype) == TypeSystem::INT) {
	stype = types.addInteger(INT_MIN, INT_MAX);
    }

    // Apply prefix and push result on the fragment stack
    typeFragments.push(applyPrefix(prefix, stype));
}

// Used to construct a new struct type, which is then pushed onto
// the type stack. The type is based on n fields, which are expected
// to be on and will be popped off the type stack.
void TypeChecker::declStruct(uint32_t prefix, uint32_t n)
{
    // Compute new type (each field has a singular record type)
    vector<pair<char *, int> > record(n);
    for (int32_t i = n - 1; i >= 0; i--) {
	record[i] = types.getRecord(typeFragments[0])[0];
	typeFragments.pop();
    }

    typeFragments.push(applyPrefix(prefix, types.addRecord(record)));
}

// Used to declare the fields of a structure. The type of the field is
// expected to be on the type fragment stack, and dim constant
// expressions are expected on the expression stack (in case of an
// array field). These will be popped of the stack.
void TypeChecker::declField(const char* name, uint32_t dim) 
{
    // Construct array type for this field
    int32_t type = buildArrayType(typeFragments[0], dim);

    if (types.isConstant(type))
	throw TypeException("Constant fields not allowed in struct");

    // Get base type
    int32_t basetype = getBaseType(type);

    // Check base type
    switch (types.getClass(basetype)) {
    case TypeSystem::INT:
    case TypeSystem::RECORD:
	// These types are ok 
	break;
    default:
	throw TypeException("Invalid type in structure");
    }

    // Copy type for next field
    typeFragments.push(typeFragments[0]);

    // Construct record type to keep track of the field name (the type
    // system will make a copy of the string, so we don't have to do
    // it here).
    vector<pair<char *, int32_t> > record;
    record.push_back(make_pair((char*)name, type));

    typeFragments[1] = types.addRecord(record);
}

// The end of a number of field declarations of the same type. The
// type must be popped of the type fragment stack.
void TypeChecker::declFieldEnd() 
{
    typeFragments.pop();
}

// The type definition. Assign the name to the given type on the
// type fragment stack. In case of array types, dim constant expressions
// are expected on and popped from the expression stack.
void TypeChecker::declTypeDef(const char* name, uint32_t dim) 
{
    int32_t type = buildArrayType(typeFragments[0], dim);

    symbols.addSymbol(name, types.addNamedType(type));
}
    
// End of type definition. Pop type of type stack.
void TypeChecker::declTypeDefEnd() 
{
    typeFragments.pop();
}

/********************************************************************
 * Variable declarations
 */

// Declare a new variable of the given name. The type is expected to
// be on the type stack. In case of an array, dim constant expressions
// are expected on the expression stack. If the variable has an
// initialiser (the init parameter is true), then an additional
// constant expression is expected at the top of the expression stack.
// The expressions will be popped of the stack (the type is left
// untouched).
void TypeChecker::declVar(const char* name, uint32_t dim, bool init) 
{
    // Pop initial value
    ExpressionProgram init_expr;
    if (init) {
	init_expr = fragments[0];
	fragments.pop();
    }

    // Construct type
    int32_t type = buildArrayType(typeFragments[0], dim);

    if (types.isConstant(type) && !init)
	throw TypeException("Constants must have an initialiser");

    if (init) 
	checkInitialiser(type, init_expr, types.isConstant(type));

    // find base type
    int32_t basetype = getBaseType(type);

    // switch on base type
    switch (types.getClass(basetype)) {
    case TypeSystem::CLOCK:
	system->addClock(type, name);
	break;
    case TypeSystem::RECORD:
    case TypeSystem::INT:
	if (types.isConstant(type)) {
	    if (types.getClass(type) == TypeSystem::INT) {
		pair<int32_t, int32_t> range = types.getIntegerRange(init_expr.getType());
		type = types.makeConstant(types.addInteger(range.first, range.second));
	    }
	    system->addConstant(type, name, init_expr);
	} else {
	    if (!init)
		insertDefault(init_expr, init_expr.end(), type);
	    system->addVariable(type, name, init_expr);
	}
	break;
    case TypeSystem::CHANNEL:
    case TypeSystem::UCHANNEL:
    case TypeSystem::BCHANNEL:
    case TypeSystem::UBCHANNEL:
	system->addChannel(type, name);
	break;
    case TypeSystem::VOID_TYPE:
	throw TypeException("Cannot declare void variable");
    case TypeSystem::LOCATION:
    case TypeSystem::CLOCATION:
    case TypeSystem::ULOCATION:
    case TypeSystem::NTYPE:
    case TypeSystem::TEMPLATE:
    case TypeSystem::FUNCTION:
	throw TypeException(unsupported);
    case TypeSystem::ARRAY:
	throw TypeException("BUG: Have not found base type of array");
    default:
	throw TypeException(unsupported);
    }
} 

// At the end of a variable declaration, this method is called in
// order to pop the type from the type stack.
void TypeChecker::declVarEnd() 
{
    typeFragments.pop(); 
}

// Returns the index of a named field in a record (or -1 if no field
// of that name exists).
int32_t TypeChecker::findFieldInRecord(
    const vector<pair<char *, int> > &record, const char *name)
{   
    for (uint32_t i = 0, skip = 0; i + skip < record.size(); i++) 
	if (strcmp(record[i + skip].first, name) == 0) 
	    return i;
    return -1;
}

// Inserts the default initialiser for a variable of 'type' at
// position 'pos' in 'expr'.
void TypeChecker::insertDefault(ExpressionProgram &expr,
				     ExpressionProgram::iterator pos,
				     int32_t type)
{
    switch (types.getClass(type)) {
    case TypeSystem::INT:
    {
	const pair<int, int> &range = types.getIntegerRange(type);
	if (range.first <= 0 && 0 <= range.second)
	    expr.insert(pos, makeConstant(0));
	else
	    expr.insert(pos, makeConstant(range.first));
	break;
    }

    case TypeSystem::ARRAY:
    {
	int size = getArraySize(type);
	while (size--)
	    insertDefault(expr, pos, types.getSecondSubType(type));
	expr.insert(pos, ExpressionProgram::expression_t(
			LIST, getArraySize(type),
			types.makeConstant(type)));
	break;
    }

    case TypeSystem::RECORD:
    {
	const vector<pair<char *, int> > &record = types.getRecord(type);
	for (uint32_t i = 0; i < record.size(); i++)
	    insertDefault(expr, pos, record[i].second);
	expr.insert(pos, ExpressionProgram::expression_t(
			LIST, record.size(), types.makeConstant(type)));
	break;
    }
	
    default:
	throw TypeException("BUG: Cannot construct default initialiser for this type");
    }
}


// Given a type and an expression, this method checks that the
// expression is a valid initialiser for a variable or constant of the
// given type. If the expression is only a partial initialiser, it
// will (if possible) be completed such that the type of the
// expression matches the given type.
void TypeChecker::checkInitialiser(
    int32_t type, SubExpression init, bool required)
{
    int32_t dim, i;

    if (!types.isConstant(init.getType()))
	throw TypeException("Non constant initialiser");

    switch (types.getClass(type)) {
    case TypeSystem::ARRAY:
    {
        if (init.getKind() != LIST)
            throw TypeException("Invalid array initialiser");
        dim = getArraySize(type);
        if (init.getSize() > dim)
            throw TypeException("Excess elements in array initialiser");

	int32_t subtype = types.getSecondSubType(type);
        for (i = 0; i < init.getSize(); i++) {
            const pair<char *, int32_t> &field 
		= types.getRecord(init.getType())[i];
            if (field.first != NULL) 
                throw TypeException(
                    "Unknown field %s specified in initialiser", field.first);
            checkInitialiser(subtype, init[i], required);
        }
        
        for (; i < dim; i++) {
	    // TODO: This could be a warning
	    if (required)
		throw TypeException("Missing fields in initialiser");
	    insertDefault(init.getExpression(),
			  init[init.getSize() - 1].end(), subtype);
        }

        init.setType(types.makeSideEffectFree(
	    types.makeConstant(types.clearFlags(type))));
        break;
    }

    case TypeSystem::INT:
    {	
	if (types.getClass(init.getType()) != TypeSystem::INT)
	    throw TypeException("Invalid initialiser");
	pair<int32_t, int32_t> range = types.getIntegerRange(init.getType());

	// If possible, reduce range of integer to an exact value
	if (range.first != range.second) {
	    int n;
	    if (system->evaluateConstantExpression(init, n)) {
		range.first = range.second = n;
		init.setType(types.makeSideEffectFree(
				 types.makeConstant(types.addInteger(range.first, range.second))));
	    }
	}

	// Make sure the initialisers range is within that of the variable
	// being initialised.
	pair<int32_t, int32_t> target = types.getIntegerRange(type);
	if (!(target.first <= range.first && range.first <= target.second)) 
	    throw TypeException("Initialiser is out of range");
	break;
    }

    case TypeSystem::RECORD:
    {
	if (types.clearFlags(type) == types.clearFlags(init.getType())) 
	    return;  // Same type name, so we are happy

	if (init.getKind() != LIST)
	    throw TypeException("Invalid initialiser for struct");

	vector<pair<char *, int> > record = types.getRecord(init.getType());
	const vector<pair<char *, int> > &target = types.getRecord(type);
	
	// Complete field names
	for (uint32_t i = 0; i < record.size(); i++) {
	    if (record[i].first == NULL) {
		int32_t pos = 0;
		if (i > 0) {
		    pos = findFieldInRecord(target, record[i - 1].first) + 1;
		    if (pos <= 0)
			throw TypeException("Unknown field name '%s'",
					    record[i - 1].first);
		    if (pos >= (int32_t)target.size())
			throw TypeException("Excess elements in struct initialiser");
		}
		record[i].first = target[pos].first;
	    } else {
		findFieldInRecord(target, record[i].first);
	    }

	    for (uint32_t j = 0; j < i; j++)
		if (strcmp(record[i].first, record[j].first) == 0)
		    throw TypeException("Multiple initialisers for field '%s'", record[i].first);
	}

	// Construct new initialiser (with correct order and all
	// missing fields inserted).
	for (uint32_t i = 0; i < target.size(); i++) {
	    int32_t pos = findFieldInRecord(record, target[i].first);
	    if (pos == -1) {
		if (required)
		    throw TypeException("Missing initialiser for '%s'",
					target[i].first);
		insertDefault(init.getExpression(),
			      i == 0 ? init.begin() : init[i - 1].end(), 
			      target[i].second);
		init.setValue(init.getSize() + 1);
	    } else {
		checkInitialiser(target[i].second, init[pos + i], required);
		if (pos > 0)
		    init.move(pos + i, i);
		record.erase(record.begin() + pos);
	    }
	}

	init.setType(types.makeConstant(types.clearFlags(type)));

	break;
    }	

    default:
        throw TypeException("Variables of this type must not have initialisers");
    }
}


// Array and struct initialisers are represented as expressions having
// one or more values (i.e. if the stack machine program that the
// expression represent is evaluated, then one or more values will be
// left on the stack).
//
// An array or struct initialiser has the structure of a list of field
// initialisers. Each field initialiser is a named expression
// (although the name can be NULL, in which case the field is
// anonymous). The field is actually represented like any other
// expression on the expression stack, except that is has a singular
// record type (i.e. a record type with only one element) on the form
// (name,type), where name is the name of the field and type is the
// type of the expression. A list of field initialisers is then
// created by concatenating several singular recorcd types into one
// record.
//
// Example: The initialiser { 2, x: 3, 4 } is represented as an
// expression evaluating to [2,3,4] on the stack, and the type of
// expression is [(NULL, typeof(2)) x ("x", typeof(3)) x (NULL,
// typeof(4))].
//
// For struct's, care must be taken when the type of the initialiser
// is compared to that of the declared struct. If another constant
// struct is used as an initialiser, then this struct must have the
// same type name as the struct being declared. If a struct
// initialiser is used (i.e. a list of fields), then the type
// requirements are much less strict.


void TypeChecker::declFieldInit(const char *name)
{
    type_t type = fragments[0].getType();
    vector<pair<char *, int32_t> > record;
    record.push_back(make_pair((char*)name, type));
    fragments[0].back().type = 
	makeConstantIf(types.isConstant(type), types.addRecord(record));
}

void TypeChecker::declInitialiserList(uint32_t num)
{
    bool constant = true;

    // Compute new type (each fragment has a singular record type)
    vector<pair<char *, int> > record;
    for (int32_t i = num - 1; i >= 0; i--) {
	type_t type = fragments[i].getType(); // This is the sing. rec.
	record.push_back(types.getRecord(type)[0]);
	fragments[i].back().type = type = record.back().second; // Restore type of field
	constant &= types.isConstant(type);
    }

    // Merge num topmost fragments
    fragments.merge(num);

    // Add 'list composition' to the end of the expression
    fragments[0].append(ExpressionProgram::expression_t(
	LIST, num, makeConstantIf(constant, types.addRecord(record))));
}
  
/********************************************************************
 * Function declarations
 */
void TypeChecker::declParameter(const char* name, bool reference, uint32_t dim)
{
    int32_t type = buildArrayType(typeFragments[0], dim);

    // For compatibility with C and C++, array parameters are always
    // reference parameters. Putting an explicit ampersand in the
    // declaration is invalid (at least according to gcc).
    if (types.getClass(type) == TypeSystem::ARRAY) {
	if (reference)
	    errorHandler->handleError("declaration of array of references");
	reference = true;
    }

    // Append parameter to list of parameters
    type = makeReferenceIf(reference, type);
    params.push_back(make_pair(strcpy(new char[strlen(name)+1], name), type));

    // In case it is not a reference parameter, make sure we are not
    // dealing with channels or clocks (as these must be reference
    // parameters!).
    if (!reference) {
	int32_t basetype = getBaseType(type);
	switch (types.getClass(basetype)) {
	case TypeSystem::CHANNEL:
	case TypeSystem::UCHANNEL:
	case TypeSystem::BCHANNEL:
	case TypeSystem::UBCHANNEL:
	    throw TypeException("Channels must be reference parameters");
	case TypeSystem::CLOCK:
	    throw TypeException("Clocks must be reference parameters");
	}
    }
}

// 1 type, dim array sizes
void TypeChecker::declParameterEnd() 
{
    typeFragments.pop(); // pop parameter type
}

void TypeChecker::declFuncBegin(const char* name, uint32_t n) 
{
    assert(currentFun == NULL);
    int32_t domain = types.addRecord(params);
    clear_params(params);
    int32_t range = typeFragments[0];
    typeFragments.pop(); // pop function result type

    int32_t type = types.addFunction(domain, range);
    currentFun = &(system->addFunction(type, name));

    // Notice: This adds an extra nested block inside the function,
    // but this does not change the semantics so that is ok.
    blockBegin();
    currentFun->body = blocks.back();

    // Add function parameters to the frame
    const vector<pair<char *, int32_t> > &record = types.getRecord(domain);
    for (uint32_t i = 0; i < record.size(); i++) {
	symbols.addSymbol(record[i].first, record[i].second);
    }
}

void TypeChecker::declFuncEnd() 
{ 
    assert(!blocks.empty());

    if (blocks.size() > 1) { // we are recovering from unfinished blocks
	// normaly all block statements must be closed and removed from stack
	do {
	    BlockStatement *block = blocks.back();
	    blocks.pop_back();
	    if (blocks.size() > 1) blocks.back()->push_stat(block);
	    else break;
	} while (true);	
    }

    if (currentFun != NULL) {
	currentFun->body = blocks.back();
	blocks.pop_back();

	//bool retVal = currentFun->body->retDefined();
	type_t type = symbols.getType(currentFun->uid);
//	type_t range = types.getSecondSubType(type);
	StatementSideEffectFree check(types);
	
	symbols.setType(currentFun->uid, 
			makeSideEffectFreeIf(
			    1==currentFun->body->accept(&check), type));

	symbols.activateFrame(symbols.getParentFrame());	
	currentFun = NULL;
        //if (!retVal && types.getClass(range) != TypeSystem::VOID_TYPE) 
        //  errorHandler->handleWarning("the return value is not always defined");
    } else { // something was wrong with fn declaration, we ignore
	blocks.pop_back();
    }
}

/********************************************************************
 * Process declarations
 */
void TypeChecker::procBegin(const char* name, uint32_t n)
{ // n parameters      
    int32_t type = types.addTemplate(types.addRecord(params));
    template_t &current = system->addTemplate(type, name);
    system->setCurrentTemplate(current);
    symbols.activateFrame(current.frame);

    // Add parameters to the frame
    for (uint32_t i = 0; i < params.size(); i++) {
        symbols.addSymbol(params[i].first, params[i].second);
    }
    clear_params(params);
}
    
void TypeChecker::procEnd() // 1 ProcBody
{
    template_t &templ = system->getCurrentTemplate();
    system->setCurrentTemplate(system->getGlobals());
    symbols.activateFrame(SymbolTable::ROOT);
    if (templ.init == -1)
	throw TypeException("Missing initial state");
}

// Add a state to the current template. An invariant expression is
// expected on and popped from the expression stack.
void TypeChecker::procState(const char* name) // 1 expr
{
    ExpressionProgram inv = fragments[0];
    fragments.pop();

    if (!isInvariant(inv.getType()))
	throw TypeException("Invalid invariant");
    
    system->addLocation(name, inv);
}
    
void TypeChecker::procStateCommit(const char* name) 
{
    int32_t uid = symbols.resolve(name);

    if (symbols.getType(uid) != TypeSystem::LOCATION)
	throw TypeException("Location expected here");

    symbols.setType(uid, TypeSystem::CLOCATION);
}
    
void TypeChecker::procStateUrgent(const char* name) 
{
    int32_t uid = symbols.resolve(name);

    if (symbols.getType(uid) != TypeSystem::LOCATION)
	throw TypeException("Location expected here");

    symbols.setType(uid, TypeSystem::ULOCATION);
}

void TypeChecker::procStateInit(const char* name) 
{
    int32_t uid = symbols.resolve(name);

    checkClass(symbols.getType(uid), TypeSystem::LOCATION,
	       "Location expected here");
    system->getCurrentTemplate().init = uid;
}
    
void TypeChecker::procTransition(const char* from, const char* to)
{
    int32_t fid = symbols.resolve(from);
    int32_t tid = symbols.resolve(to);

    checkLocation(fid, "No such location (source)");
    checkLocation(tid, "No such location (destination)");

    // Complete labels
    if (update == -1) {
	exprTrue();
	procUpdate();
    }

    if (sync == -1) {
	procSync(SYNC_TAU);
    }

    if (guard == -1) {
	exprTrue();
	procGuard();
    }
    
    // Create transition
    transition_t &tran = system->addTransition(fid, tid);
    tran.assign = fragments[fragments.size() - update];
    tran.sync = fragments[fragments.size() - sync];
    tran.guard = fragments[fragments.size() - guard];
    fragments.pop(3);

    guard = sync = update = -1;
}

void TypeChecker::checkGuardSynchronisationConflict()
{
    assert(guard != -1 && sync != -1);
    
    type_t syncType = fragments[fragments.size() - sync].getType();
    type_t guardType = fragments[fragments.size() - guard].getType();
    if (types.getClass(guardType) != TypeSystem::INT) {
	switch (types.clearFlags(syncType)) {
	case TypeSystem::CHANNEL:
	    // This is ok
	    break;
	case TypeSystem::UCHANNEL:
	case TypeSystem::UBCHANNEL:
	    throw TypeException("Clock guards are not allowed on "
				"urgent transitions.");
	case TypeSystem::BCHANNEL:
	    if (fragments[fragments.size() - sync].back().value == SYNC_QUE) 
		throw TypeException("Clock guards are not allowed on broadcast receivers.");
	    break;
	default:
	    assert(0);
	}
    }
}

void TypeChecker::procGuard()
{
    guard = fragments.size();
    if (!isGuard(fragments[0].getType()))
	throw TypeException("Invalid guard");
    if (!types.isSideEffectFree(fragments[0].getType()))
	throw TypeException("Guard must be side effect free");
    if (sync != -1)
	checkGuardSynchronisationConflict();
}

void TypeChecker::procSync(uint32_t type)
{
    if (type != SYNC_TAU) {
	ExpressionProgram &expr = fragments[0];
	if (!types.isSideEffectFree(expr.getType()))
	    throw TypeException("Synchronisation must be side effect free");
	switch (types.getClass(expr.getType())) {
	case TypeSystem::CHANNEL:
	case TypeSystem::UCHANNEL:
	case TypeSystem::BCHANNEL:
	case TypeSystem::UBCHANNEL:
	    break;
	default:
	    throw TypeException("No such channel");
	}
	expr.append(SYNC, type, expr.getType());
    } else {
	fragments.push(ExpressionProgram(
	    SYNC, type,
	    types.makeSideEffectFree(
		types.makeConstant(TypeSystem::CHANNEL))));
						  
    };
    sync = fragments.size();
    if (guard != -1)
	checkGuardSynchronisationConflict();
}

void TypeChecker::procUpdate()
{
    update = fragments.size();

    switch (types.getClass(fragments[0].getType())) {
    case TypeSystem::INT:
    case TypeSystem::ARRAY:
    case TypeSystem::RECORD:
    case TypeSystem::CLOCK:
	break;
    default:
	throw TypeException("Invalid assignment expression");	
    }
}

/*********************************************************************
 * Statements
 */
void TypeChecker::blockBegin() 
{
    int32_t frame = symbols.addFrame();
    blocks.push_back(new BlockStatement(frame));
    symbols.activateFrame(frame);
/*
    if (blocks.size()==1 && currentFun) { // if this is the function body block
        // Add function parameters to the frame
	currentFun->body = blocks.back();
	int32_t fType = symbols.getType(currentFun->uid);
	int32_t domain = types.getFirstSubType(fType);
	const vector<pair<char *, int32_t> > &record = types.getRecord(domain);
	for (uint32_t i = 0; i < record.size(); i++) {
	    symbols.addSymbol(record[i].first, record[i].second);
	}
    }
*/
}

void TypeChecker::blockEnd() 
{
    BlockStatement *block = blocks.back();
    blocks.pop_back();
    if (!blocks.empty()) { // if this was inner block
	blocks.back()->setRetDefined(
	    blocks.back()->retDefined() || // mark dead code
	    block->retDefined());
	blocks.back()->push_stat(block);
    }
    symbols.activateFrame(symbols.getParentFrame());
}

void TypeChecker::emptyStatement() 
{
    blocks.back()->push_stat(new EmptyStatement(blocks.back()->frameId));
}

void TypeChecker::forBegin() 
{
//    addStatement(blocks.back(), new ForStatement(blocks.back()->frameId));
}

void TypeChecker::forEnd() 
{ // 3 expr, 1 stat
    Statement* substat = blocks.back()->pop_stat();
    ForStatement* forstat = new ForStatement(blocks.back()->frameId, 
					     fragments[2], fragments[1], 
					     fragments[0], substat);
    forstat->setRetDefined(substat->retDefined());
    blocks.back()->push_stat(forstat);

    fragments.pop();
    fragments.pop();
    fragments.pop();
}

void TypeChecker::whileBegin() 
{
}

void TypeChecker::whileEnd() 
{ // 1 expr, 1 stat
    Statement* substat = blocks.back()->pop_stat();
    WhileStatement* whilestat = new WhileStatement(blocks.back()->frameId, 
						   fragments[0], substat);
    whilestat->setRetDefined(substat->retDefined());
    blocks.back()->push_stat(whilestat);

    fragments.pop();
}

void TypeChecker::doWhileBegin()
{
}

void TypeChecker::doWhileEnd()
{ // 1 stat, 1 expr
    Statement* substat = blocks.back()->pop_stat();
    blocks.back()->push_stat(
	new DoWhileStatement(blocks.back()->frameId, substat, fragments[0]));
    fragments.pop();
}

void TypeChecker::ifBegin()
{
}

void TypeChecker::ifElse()
{
}

void TypeChecker::ifEnd(bool elsePart)
{ // 1 expr, 1 or 2 statements
    Statement *falseCase = NULL;
    if (elsePart) falseCase = blocks.back()->pop_stat();

    Statement *trueCase = blocks.back()->pop_stat();

    IfStatement *ifstat = new IfStatement(blocks.back()->frameId, 
					  fragments[0], trueCase, falseCase);

    if (elsePart) ifstat->setRetDefined(trueCase->retDefined() && 
					falseCase->retDefined());

    blocks.back()->push_stat(ifstat);

    fragments.pop();
}

void TypeChecker::breakStatement()
{
    blocks.back()->push_stat(new BreakStatement(blocks.back()->frameId));
}

void TypeChecker::continueStatement()
{
    blocks.back()->push_stat(new ContinueStatement(blocks.back()->frameId));
}
void TypeChecker::switchBegin()
{ // 1 expr
    int32_t frame = symbols.addFrame();
    blocks.push_back(
	new SwitchStatement(frame, fragments[0]));
    fragments.pop();
    symbols.activateFrame(frame);
}
void TypeChecker::switchEnd()
{ // 1+ case/default
    BlockStatement *block = blocks.back();
    blocks.pop_back();
    blocks.back()->push_stat(block);
    symbols.activateFrame(symbols.getParentFrame());
}

void TypeChecker::caseBegin() 
{ // 1 expr
    blocks.push_back(new CaseStatement(symbols.getActiveFrame(), 
				       fragments[0]));
    fragments.pop();
}

void TypeChecker::caseEnd()
{ // 0+ stat
    BlockStatement *block = blocks.back();
    blocks.pop_back();
    blocks.back()->push_stat(block);
}

void TypeChecker::defaultBegin() 
{    
    blocks.push_back(new DefaultStatement(symbols.getActiveFrame()));
}

void TypeChecker::defaultEnd() 
{ // 0+ statements
    BlockStatement *block = blocks.back();    
    blocks.pop_back();    
    blocks.back()->push_stat(block);
}

void TypeChecker::exprStatement() 
{ // 1 expr
    blocks.back()->push_stat(new ExprStatement(blocks.back()->frameId, 
					       fragments[0]));
    fragments.pop();
}

void TypeChecker::returnStatement(bool args) 
{ // 1 expr if argument is true
    assert(currentFun!=NULL);
    int range = types.getSecondSubType(symbols.getType(currentFun->uid));
    if (args) {
	type_t ret = fragments[0].getType();
	ReturnStatement* retstat = new ReturnStatement(blocks.back()->frameId, 
						       fragments[0]);
	fragments.pop();
	blocks.back()->push_stat(retstat);
	blocks.back()->setRetDefined(true);

	switch (types.getClass(range)) {
	case TypeSystem::VOID_TYPE:
	    throw TypeException("void function does not return any value");
	    break;
	case TypeSystem::CLOCK:
	    if (types.getClass(ret) != TypeSystem::CLOCK)
		throw TypeException("function must return a clock reference");
	    break;
	case TypeSystem::INT:
	    if ((types.getClass(ret) != TypeSystem::INT) && 
		(types.getClass(ret) != TypeSystem::CLOCK) &&
		(types.getClass(ret) != TypeSystem::DIFF) &&
		(types.getClass(ret) != TypeSystem::INVARIANT) &&
		(types.getClass(ret) != TypeSystem::GUARD))
		throw TypeException("function must return an integer");
	    else {
		const pair<int32_t,int32_t> lrange = types.getIntegerRange(range);
		const pair<int32_t,int32_t> rrange = types.getIntegerRange(ret);

		// The range of the right side must be contained in the range of the left side
		if (rrange.first < lrange.first || rrange.second > lrange.second)
		{
		    errorHandler->handleWarning("return value possibly outside range");
		}
		
		// We just require overlap
		if (!(lrange.first <= rrange.second || rrange.first <= lrange.second)) {
		    throw TypeException("Return value outside range");
		}
	    }
	    break;
	case TypeSystem::RECORD:
	    if (types.getClass(ret) == TypeSystem::RECORD) {
		if (types.clearFlags(range) != types.clearFlags(ret))
		    throw TypeException("return value type does not match "
					"function range type");
	    } else
		throw TypeException("function must return a record");
	    break;
	case TypeSystem::ARRAY:
	    if (types.getClass(ret) == TypeSystem::ARRAY) {		
		if (types.getFirstSubType(range)!=types.getFirstSubType(ret))
		    throw TypeException("return value array domain does not "
					"match function array domain");
		if (types.getSecondSubType(range)!=types.getSecondSubType(ret))
		    throw TypeException("return value array range does not "
					"match function array range");
	    } else
		throw TypeException("function must return an array");
	    break;
	case TypeSystem::CHANNEL:
	    if (types.getClass(ret) != TypeSystem::CHANNEL)
		throw TypeException("function must return a channel");
	    break;
	case TypeSystem::UCHANNEL:
	    if (types.getClass(ret) != TypeSystem::UCHANNEL)
		throw TypeException("function must return an urgent channel");
	    break;
	case TypeSystem::BCHANNEL:
	    if (types.getClass(ret) != TypeSystem::BCHANNEL)
		throw TypeException("function must return a broadcast "
				    "channel");
	    break;
	case TypeSystem::UBCHANNEL:
	    if (types.getClass(ret) != TypeSystem::UBCHANNEL)
		throw TypeException("function must return an urgent broadcast "
				    "channel");
	    break;
	case TypeSystem::LOCATION:
	case TypeSystem::CLOCATION:
	case TypeSystem::ULOCATION:
	case TypeSystem::NTYPE:
	case TypeSystem::TEMPLATE:
	case TypeSystem::FUNCTION:
	default:
	    throw TypeException(unsupported);	    
	}
	if (types.isReference(range) && isTemporary(fragments[0]))
	    throw TypeException("returns local variable reference");
    } else if (TypeSystem::VOID_TYPE != types.getClass(range))
	throw TypeException("non-void function must return a value");
}

/********************************************************************
 * Expressions
 */
void TypeChecker::exprTrue() 
{
    fragments.push(makeConstant(1));
}

void TypeChecker::exprFalse() 
{
    fragments.push(makeConstant(0));
}
    
void TypeChecker::exprId(const char * name) 
{
    int32_t uid = symbols.resolve(name);
    if (uid == -1) {
	fragments.push(ExpressionProgram(IDENTIFIER, -1, TypeSystem::VOID_TYPE));
	throw TypeException("%s: Unknown identifier", name);
    }

    type_t type = symbols.getType(uid);

    fragments.push(
	ExpressionProgram(
	    IDENTIFIER, uid, 
	    types.makeSideEffectFree(
		types.makeReference(type))));

    switch (types.getClass(type)) {
    case TypeSystem::INT:
    case TypeSystem::ARRAY:
    case TypeSystem::CLOCK:
    case TypeSystem::CHANNEL:
    case TypeSystem::UCHANNEL:
    case TypeSystem::BCHANNEL:
    case TypeSystem::UBCHANNEL:
    case TypeSystem::RECORD:
	break;
    case TypeSystem::PROCESS:
	if (!allowProcessReferences())
	    throw TypeException("Process references are not allowed");
	break;
    default:
	throw TypeException("Incorrect type for expression");
    }
}

ExpressionProgram::expression_t TypeChecker::makeConstant(int value)
{
    return ExpressionProgram::expression_t(
	CONSTANT, value, types.makeSideEffectFree(
	    types.makeConstant(types.addInteger(value, value))));
}
    
void TypeChecker::exprDeadlock()
{
    fragments.push(ExpressionProgram(
		       DEADLOCK, 0,
		       types.makeSideEffectFree(TypeSystem::CONSTRAINT)));
}

void TypeChecker::exprNat(int32_t n) 
{
    fragments.push(ExpressionProgram(makeConstant(n)));
}

void TypeChecker::exprCallBegin(const char *functionName) 
{
    int32_t id = symbols.resolve(functionName);
    identifierStack.push_back(id);

    expectedArguments.push_back(vector<type_t>());
    
    if (id < 0)
	throw TypeException("function '%s' not declared", functionName);

    if (types.getClass(symbols.getType(id)) != TypeSystem::FUNCTION)
	throw TypeException("Not a function: %s", functionName);
    
    if (currentFun != NULL && currentFun->uid <= id)
	throw TypeException("recursion is not allowed", functionName);

    type_t domain = types.getFirstSubType(symbols.getType(id));
    const vector<pair<char*, type_t> > &params = types.getRecord(domain);
    for (int i = params.size() - 1; i >= 0; i--)
	expectedArguments.back().push_back(params[i].second);
}

// expects n argument expressions on the stack
void TypeChecker::exprCallEnd(uint32_t n) 
{
    int32_t id = identifierStack.back();
    identifierStack.pop_back();

    if (!expectedArguments.back().empty())
	errorHandler->handleError("Too few arguments");

    expectedArguments.pop_back();
    
    if (id == -1)
	return;
    
    // Compute result type
    bool constant = true;
    bool sideEffectFree = true;
    int32_t type = types.getSecondSubType(symbols.getType(id));

    for (uint32_t i = 0; i < n; i++) {
	constant &= types.isConstant(fragments[i].getType());
	sideEffectFree &= types.isSideEffectFree(fragments[i].getType());
    }
    
    type = makeSideEffectFreeIf(sideEffectFree, types.clearFlags(type));
    type = makeConstantIf(constant, type);

    // Merge arguments and append function call instruction
    fragments.merge(n);
    fragments[0].append(FUNCALL, id, type);
}

// expects 1 expression on the stack
void TypeChecker::exprArg(uint32_t n) 
{
    if (expectedArguments.back().empty())
	throw TypeException("Too many arguments");
    
    type_t argument = fragments[0].getType();
    const char *error = isParameterCompatible(
	expectedArguments.back().back(), argument);
    expectedArguments.back().pop_back();
    if (error != NULL)
	errorHandler->handleError(error);
}

// 2 expr     // array[index]
void TypeChecker::exprArray() 
{
    type_t index = fragments[0].getType();
    type_t array = fragments[1].getType();

    fragments.merge(2);
	
    // Check types and ranges
    checkClass(array, TypeSystem::ARRAY, "Attempt to index a non-array type");
    checkClass(index, TypeSystem::INT, "The index is not an integer type");

    const pair<int32_t, int32_t> &arange = types.getIntegerRange(
	types.getFirstSubType(array));
    const pair<int32_t, int32_t> &irange = types.getIntegerRange(index);

    // Construct new type and expression
    int32_t type = types.getSecondSubType(array);
    type = makeReferenceIf(types.isReference(array), type);
    type = makeConstantIf(
	types.isConstant(array) && types.isConstant(index), type);
    type = makeSideEffectFreeIf(
	types.isSideEffectFree(array)
	&& types.isSideEffectFree(index), type);
    fragments[0].append(ARRAY, array, type);

    if (arange.second < irange.first || arange.first > irange.second)
	throw TypeException("The index is out of range");

    if (arange.first > irange.first || irange.second > arange.second)
    {
	errorHandler->handleWarning("Index potentially out of range");
    }   
}

// 1 expr
void TypeChecker::exprPostIncrement() 
{
    ExpressionProgram &expr = fragments[0];

    type_t type = expr.getType();

    checkClass(type, TypeSystem::INT, "Invalid type in increment");
    checkLValue(type, "Invalid left value in increment");
    
    pair<int32_t,int32_t> range = types.getIntegerRange(type);
    int32_t t = makeSideEffectFreeIf(
	isTemporary(expr) && types.isSideEffectFree(type),
	types.addInteger(range.first, range.second));
	
    expr.append(POSTINCREMENT, 0, t);

    errorHandler->handleWarning("Expression potentially out of range");
}
    
void TypeChecker::exprPreIncrement() 
{
    ExpressionProgram &expr = fragments[0];

    type_t type = expr.getType();

    checkClass(type, TypeSystem::INT, "Invalid type in increment");
    checkLValue(type, "Invalid left value in increment");

    pair<int32_t,int32_t> range = types.getIntegerRange(type);
    int32_t t = makeSideEffectFreeIf(
	isTemporary(expr) && types.isSideEffectFree(type),
	types.addInteger(range.first + 1, range.second));

    expr.append(PREINCREMENT, 0, t);
    errorHandler->handleWarning("Expression potentially out of range");
}
    
void TypeChecker::exprPostDecrement() // 1 expr
{
    ExpressionProgram &expr = fragments[0];

    type_t type = expr.getType();

    checkClass(type, TypeSystem::INT, "Invalid type in decrement");
    checkLValue(type, "Invalid left value in decrement");

    pair<int32_t,int32_t> range = types.getIntegerRange(type);
    int32_t t = makeSideEffectFreeIf(
	isTemporary(expr) && types.isSideEffectFree(type),
	types.addInteger(range.first, range.second));

    expr.append(POSTDECREMENT, 0, t);
    errorHandler->handleWarning("Expression potentially out of range");
}
    
void TypeChecker::exprPreDecrement() 
{
    ExpressionProgram &expr = fragments[0];

    type_t type = expr.getType();

    checkClass(type, TypeSystem::INT, "Invalid type in decrement");
    checkLValue(type, "Invalid left value in decrement");

    pair<int32_t,int32_t> range = types.getIntegerRange(type);
    int32_t t = makeSideEffectFreeIf(
	isTemporary(expr) && types.isSideEffectFree(type),
	types.addInteger(range.first, range.second - 1));
	
    expr.append(POSTDECREMENT, 0, t);
    errorHandler->handleWarning("Expression potentially out of range");
}
    
void TypeChecker::exprAssignment(uint32_t op) // 2 expr
{
    bool temp = isTemporary(fragments[1]);
    type_t rvalue = fragments[0].getType();
    type_t lvalue = fragments[1].getType();

    fragments.merge(2);

    checkAssignmentCompatible(lvalue, rvalue);

    int32_t type = makeSideEffectFreeIf(
	temp
	&& types.isSideEffectFree(lvalue)
	&& types.isSideEffectFree(rvalue),
	types.makeReference(types.clearFlags(lvalue)));

    switch (op) {
    case ASSIGN:
	fragments[0].append(ASSIGN, 0, type);
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
	if ( !(isInteger(lvalue) && isInteger(rvalue)) ) {
	    throw TypeException("Non-integer types must use regular assignment operator.");
	}
	fragments[0].append(op, 0, type);
	break;
    default:
	throw TypeException(unsupported);
    }
}

uint32_t TypeChecker::typeOfUnaryMinus(uint32_t type)
{
    uint32_t result;
    pair<int32_t, int32_t> range = types.getIntegerRange(type);
    result = types.addInteger(-range.second, -range.first);
    result = makeConstantIf(types.isConstant(type), result);
    result = makeSideEffectFreeIf(types.isSideEffectFree(type), result);
    return result;
}

void TypeChecker::exprUnary(uint32_t unaryop) // 1 expr
{
    type_t expr = fragments[0].getType();
    int32_t type;
	
	
    switch (unaryop) {
    case MINUS:
	checkClass(expr, TypeSystem::INT, "Invalid type");
	fragments[0].append(UNARY_MINUS, 0, typeOfUnaryMinus(expr));
	break;
    case NOT:
	if (types.getClass(expr) == TypeSystem::INT) {
	    type = BOOL;
	} else if (isConstraint(expr)) {
	    type = TypeSystem::CONSTRAINT;
	} else {
	    throw TypeException("Invalid type");
	}
	type = makeConstantIf(types.isConstant(expr), type);
	type = makeSideEffectFreeIf(types.isSideEffectFree(expr), type);
	fragments[0].append(NOT, 0, type);
	break;
    default:
	throw TypeException(unsupported);
    }
}

int32_t TypeChecker::typeOfBinaryIntExpression(
    int32_t left, uint32_t op, int32_t right)
{
    int32_t type, t1, t2, t3, t4;
    pair<int32_t, int32_t> lrange = types.getIntegerRange(left);
    pair<int32_t, int32_t> rrange = types.getIntegerRange(right);

    switch (op) {
    case MINUS:
	type = types.addInteger(lrange.first - rrange.second,
				lrange.second - rrange.first);
	break;
    case PLUS:
	type = types.addInteger(lrange.first + rrange.first,
				lrange.second + rrange.second);
	break;
    case MULT:
	t1 = lrange.first * rrange.first;
	t2 = lrange.first * rrange.second;
	t3 = lrange.second * rrange.first;
	t4 = lrange.second * rrange.second;
	type = types.addInteger(min(min(t1, t2), min(t3, t4)), 
				max(max(t1, t2), max(t3, t4)));
	break;
    case DIV:
	if (rrange.first == 0 && rrange.second == 0) 
	    throw TypeException("Denominator is zero");
	if (rrange.first <= 0 && 0 <= rrange.second)
	    errorHandler->handleWarning("Denominator can be zero");

	t1 = lrange.first / (rrange.first == 0 ? 1 : rrange.first);
	t2 = lrange.first / (rrange.second == 0 ? -1 : rrange.second);
	t3 = lrange.second / (rrange.first == 0 ? 1 : rrange.first);
	t4 = lrange.second / (rrange.second == 0 ? -1 : rrange.second);
	type = types.addInteger(min(min(t1, t2), min(t3, t4)),
				max(max(t1, t2), max(t3, t4)));
	break;
    case MOD:
	t1 = max(abs(rrange.first), abs(rrange.second));
	type = types.addInteger(min(max(lrange.first, -t1), 0),
				max(min(lrange.second, t1), 0));
	break;
    case MIN:
	type = types.addInteger(min(lrange.first, rrange.first),
				min(lrange.second, rrange.second));
	break;
    case MAX:
	type = types.addInteger(max(lrange.first, rrange.first),
				max(lrange.second, rrange.second));
	break;
    case BIT_AND:
	t1 = max(max(abs(lrange.first), abs(lrange.second)),
		 max(abs(rrange.first), abs(rrange.second)));
	t2 = (1 << (int32_t)ceil(log(t1) / log(2))) - 1;
	t3 = (lrange.first < 0 && rrange.first < 0 ? -t2 : 0);
	t4 = (lrange.first >= 0 || rrange.first >= 0 ? t2 : 0);
	type = types.addInteger(t3, t4);
	break;
    case BIT_OR:
	t1 = max(max(abs(lrange.first), abs(lrange.second)),
		 max(abs(rrange.first), abs(rrange.second)));
	t2 = (1 << (int32_t)ceil(log(t1) / log(2))) - 1;
	t3 = (lrange.first < 0 || rrange.first < 0 ? -t2 : 0);
	t4 = (lrange.first >= 0 && rrange.first >= 0 ? t2 : 0);
	type = types.addInteger(t3, t4);
	break;
    case BIT_XOR:
	t1 = max(max(abs(lrange.first), abs(lrange.second)),
		 max(abs(rrange.first), abs(rrange.second)));
	t2 = (1 << (int32_t)ceil(log(t1) / log(2))) - 1;
	t3 = (lrange.first < 0 || rrange.first < 0 ? -t2 : 0);
	t4 = (lrange.first >= 0 || rrange.first >= 0 ? t2 : 0);
	type = types.addInteger(t3, t4);
	break;
    case BIT_LSHIFT:
	if (rrange.first < 0) {
	    errorHandler->handleWarning("Left shift count is potentially negative");
	}
	
	if (rrange.second < 0) {
	    throw TypeException("Left shift count is negative");
	}
	type = types.addInteger(lrange.first << rrange.first,
				lrange.second << rrange.second);
	break;
    case BIT_RSHIFT:
	if (rrange.first < 0) {
	    errorHandler->handleWarning("Right shift count is potentially negative");
	}
	if (rrange.second < 0) {
	    throw TypeException("Right shift count is negative");
	}
	type = types.addInteger(lrange.first >> rrange.second,
				lrange.second >> rrange.first);
	break;
    case AND:
    case OR:
    case LT:
    case LE:
    case EQ:
    case NEQ:
    case GE:
    case GT:;
	type = BOOL;
	break;
    default:
	throw TypeException(unsupported);
    }
    type = makeConstantIf(
	types.isConstant(left) && types.isConstant(right), type);
    type = makeSideEffectFreeIf(
	types.isSideEffectFree(left)
	&& types.isSideEffectFree(right), type);
    return type;
}

void TypeChecker::exprBinaryInt(int left, uint32_t binaryop, int right)
{
    fragments[0].append(
	binaryop, 0,
	typeOfBinaryIntExpression(left, binaryop, right));
}

void TypeChecker::normaliseConstraint(
    normalisation_t &data, SubExpression op, bool left)
{
    if (types.getClass(op.getType()) == TypeSystem::INT) {
	type_t type = (data.first ? 0 : data.value.getType());
	data.value.append(op);
	if (left)
	    data.value.append(UNARY_MINUS, 0, 
			      typeOfUnaryMinus(data.value.getType()));
	if (data.first) {
	    data.first = false;
	} else {
	    data.value.append(PLUS, 0,
			      typeOfBinaryIntExpression(
				  type, PLUS, data.value.getType()));
	}
    } else {
	switch (op.getKind()) {
	case MINUS:
	    normaliseConstraint(data, op[0], left);
	    normaliseConstraint(data, op[1], !left);
	    break;
		
	case PLUS:
	    normaliseConstraint(data, op[0], left);
	    normaliseConstraint(data, op[1], left);
	    break;

	default:
	    if (left) {
		assert(data.clock1.begin() == data.clock1.end());
		data.clock1.append(op);
	    } else {
		assert(data.clock2.begin() == data.clock2.end());
		data.clock2.append(op);
	    }
	}
    }    
}

void TypeChecker::normaliseConstraint(ExpressionProgram &expr)
{
    normalisation_t data;
    SubExpression sub(expr);
    normaliseConstraint(data, sub[0], true);
    normaliseConstraint(data, sub[1], false);

    uint32_t op = sub.getKind();
    type_t type = sub.getType();

    expr.clear();

    if (data.clock1.begin() == data.clock1.end())
	data.clock1.append(IDENTIFIER, symbols.resolve("t(0)"),
			   types.makeSideEffectFree(TypeSystem::CLOCK));

    if (data.clock2.begin() == data.clock2.end())
	data.clock2.append(IDENTIFIER, symbols.resolve("t(0)"),
		      types.makeSideEffectFree(TypeSystem::CLOCK));

    if (data.value.begin() == data.value.end())
	data.value.append(makeConstant(0));

    switch (op) {
    case LT:
    case LE:
	expr.append(data.clock1);
	expr.append(data.clock2);
	expr.append(data.value);
	expr.append(CONSTRAINT, (op == LT), type);
	break;
	
    case GT:
    case GE:
	expr.append(data.clock2);
	expr.append(data.clock1);
	expr.append(data.value);
	expr.append(UNARY_MINUS, 0, typeOfUnaryMinus(data.value.getType()));
	expr.append(CONSTRAINT, (op == GT), type);
	break;

    case EQ:
	expr.append(data.clock1);
	expr.append(data.clock2);
	expr.append(data.value);
	expr.append(CONSTRAINT, false, type);

	expr.append(data.clock2);
	expr.append(data.clock1);
	expr.append(data.value);
	expr.append(UNARY_MINUS, 0, typeOfUnaryMinus(data.value.getType()));
	expr.append(CONSTRAINT, false, type);

	expr.append(AND, 0, type);
	break;

    case NEQ:
	expr.append(data.clock1);
	expr.append(data.clock2);
	expr.append(data.value);
	expr.append(CONSTRAINT, true, type);

	expr.append(data.clock2);
	expr.append(data.clock1);
	expr.append(data.value);
	expr.append(UNARY_MINUS, 0, typeOfUnaryMinus(data.value.getType()));
	expr.append(CONSTRAINT, true, type);

	expr.append(OR, 0, type);
	break;

    default:
	throw TypeException("BUG: Cannot normalise constraint of this kind");
    }
}

void TypeChecker::exprBinaryNonInt(int left, uint32_t binaryop, int right)
{
    int32_t type = TypeSystem::VOID_TYPE;
    bool normalise = false;
    
    switch (binaryop) {
    case PLUS:
	if (isInteger(left) && isClock(right)
	    || isClock(left) && isInteger(right))
	{
	    type = TypeSystem::CLOCK;
	} else if (isDiff(left) && isInteger(right) 
		   || isInteger(left) && isDiff(right))
	{
	    type = TypeSystem::DIFF;
	}
	break;
	    
    case MINUS:
	if (isClock(left) && isInteger(right)) 
        // removed  "|| isInteger(left.type) && isClock(right.type)" 
	// in order to be able to convert into ClockGuards
	{
	    type = TypeSystem::CLOCK;
	} 
	else if (isDiff(left) && isInteger(right)
		   || isInteger(left) && isDiff(right)
		   || isClock(left) && isClock(right)) 
	{
	    type = TypeSystem::DIFF;
	}
	break;

    case AND:
	if (isInvariant(left) && isInvariant(right)) {
	    type = TypeSystem::INVARIANT;
	} else if (isGuard(left) && isGuard(right)) {
	    type = TypeSystem::GUARD;
	} else if (isConstraint(left) && isConstraint(right)) {
	    type = TypeSystem::CONSTRAINT;
	}
	break;
	    
    case OR:
	if (isConstraint(left) && isConstraint(right)) {
	    type = TypeSystem::CONSTRAINT;
	}
	break;

    case LT:
    case LE:
	if (isClock(left) && isClock(right)
	    || isClock(left) && isInteger(right)
	    || isDiff(left) && isInteger(right)
	    || isInteger(left) && isDiff(right))
	{
	    type = TypeSystem::INVARIANT;
	} else if (isInteger(left) && isClock(right)) {
	    type = TypeSystem::GUARD;
	}
	normalise = true;
	break;

    case EQ:
	if (isClock(left) && isClock(right)
	    || isClock(left) && isInteger(right)
	    || isInteger(left) && isClock(right)
	    || isDiff(left) && isInteger(right)
	    || isInteger(left) && isDiff(right))
	{
	    type = TypeSystem::GUARD;
	}
	normalise = true;
	break;
	
    case NEQ:
	if (isClock(left) && isClock(right)
	    || isClock(left) && isInteger(right)
	    || isInteger(left) && isClock(right)
	    || isDiff(left) && isInteger(right)
	    || isInteger(left) && isDiff(right))
	{
	    type = TypeSystem::CONSTRAINT;
	}
	normalise = true;
	break;

    case GE:
    case GT:
	if (isClock(left) && isClock(right)
	    || isInteger(left) && isClock(right)
	    || isDiff(left) && isInteger(right)
	    || isInteger(left) && isDiff(right))
	{
	    type = TypeSystem::INVARIANT;
	} else if (isClock(left) && isGuard(right)) {
	    type = TypeSystem::GUARD;
	}
	normalise = true;
	break;
    }
    if (type == TypeSystem::VOID_TYPE)
	throw TypeException("Invalid operands to binary operator");	
    
    type = makeConstantIf(
	types.isConstant(left) && types.isConstant(right), type);
    type = makeSideEffectFreeIf(
	types.isSideEffectFree(left)
	&& types.isSideEffectFree(right), type);
    fragments[0].append(binaryop, 0, type);

    if (normalise) {
	normaliseConstraint(fragments[0]);
    }
}
    
void TypeChecker::exprBinary(uint32_t binaryop) // 2 expr
{
    type_t right = fragments[0].getType();
    type_t left = fragments[1].getType();

    fragments.merge(2);

    if (isInteger(left) && isInteger(right)) {
	exprBinaryInt(left, binaryop, right);
    } else {
	exprBinaryNonInt(left, binaryop, right);
    }
}

// Given the types of the two alternatives, this method computes the
// type of an inline if.
int32_t TypeChecker::combineInlineTypes(int32_t t, int32_t e)
{
    if (types.getClass(t) != types.getClass(e))
	throw TypeException("Incompatible types in inline if");
    
    switch (types.getClass(t)) {
    case TypeSystem::INT: {
	const pair<int, int> &trange = types.getIntegerRange(t);
	const pair<int, int> &erange = types.getIntegerRange(e);
	return types.addInteger(min(trange.first, erange.first),
				max(trange.second, erange.second));
    }

    case TypeSystem::ARRAY:
	if (types.getIntegerRange(types.getFirstSubType(t))
	    != types.getIntegerRange(types.getFirstSubType(e)))
	{
	    throw TypeException("Incompatible array types in inline if");
	}

	return types.addArray(types.getFirstSubType(t),
			      combineInlineTypes(types.getSecondSubType(t),
						 types.getSecondSubType(e)));

    case TypeSystem::RECORD:
	if (t != e)
	    throw TypeException("Incompatible structs in inline if");
	return types.clearFlags(t);

    case TypeSystem::CHANNEL:
    case TypeSystem::CLOCK:
	return types.clearFlags(t);
    }
    throw TypeException("Invalid types in inline if");
}

void TypeChecker::exprInlineIf()
{
    // Get size of three topmost expressions
    type_t c = fragments[2].getType();
    type_t t = fragments[1].getType();
    type_t e = fragments[0].getType();

    // Merge 3 expressions
    fragments.merge(3);

    checkClass(c, TypeSystem::INT, "Invalid condition in inline if");

    int32_t type = makeConstantIf(
	types.isConstant(c) && types.isConstant(t) && types.isConstant(e),
	combineInlineTypes(t, e));

    type = makeReferenceIf(
	types.isReference(t) && types.isReference(e), type);

    type = makeSideEffectFreeIf(
	types.isSideEffectFree(c) && types.isSideEffectFree(t) &&
	types.isSideEffectFree(e), type);
    
    fragments[0].append(INLINEIF, 0, type);
}

void TypeChecker::exprComma()
{
    fragments.merge(2);
    fragments[0].append(COMMA, 0, fragments[0].getType());
}

void TypeChecker::exprDot(const char *id)
{
    ExpressionProgram &expr = fragments[0];
    type_t type = expr.getType();
    switch (types.getClass(type)) {
    case TypeSystem::RECORD:
    {
	const vector<pair<char *, int> > &record = types.getRecord(type);
	for (uint32_t i = 0; i < record.size(); i++) {
	    if (strcmp(record[i].first, id) == 0) {
		int32_t subtype = record[i].second;

		subtype = makeConstantIf(types.isConstant(type), subtype);
		subtype = makeReferenceIf(types.isReference(type), subtype);
		subtype = makeSideEffectFreeIf(types.isSideEffectFree(type),
					       subtype);

		expr.append(DOT, i, subtype);
		return;		    
	    }
	}
	throw TypeException("Structure has no member named '%s'", id);
    }
    case TypeSystem::PROCESS:
    {
	assert(expr.back().kind == IDENTIFIER);
	int pid = expr.back().value;
	process_t *proc = (process_t *)symbols.getData(pid);
	int32_t uid = symbols.resolveLocal(id, proc->templ->frame);
	if (uid == -1)
	    throw TypeException("%s: Unknown identifier", id);

	type_t subtype = symbols.getType(uid);

	switch (types.getClass(subtype)) {
	case TypeSystem::INT:
	case TypeSystem::ARRAY:
	case TypeSystem::CLOCK:
	case TypeSystem::RECORD:
	    subtype = types.makeSideEffectFree(
		makeReferenceIf(!types.isConstant(subtype), subtype));
	    break;
	case TypeSystem::LOCATION:
	    subtype = types.makeSideEffectFree(types.makeConstant(BOOL));
	    break;
	default:
	    throw TypeException("Incorrect type for expression");
	}
	
	fragments[0].append(DOT, uid, subtype);
	break;
    }
    default:
	throw TypeException(
	    "Request for member '%s' in something not a structure", id);
    }
}
    
/********************************************************************
 * System declaration
 */

// Prepares for the instantiations of a process
void TypeChecker::instantiationBegin(const char* name, const char* templ_name)
{
    int32_t id = symbols.resolve(templ_name);
    identifierStack.push_back(id);

    expectedArguments.push_back(vector<int>());
    
    if (id == -1) 
	throw TypeException("No such template: %s", templ_name);
    
    if (types.getClass(symbols.getType(id)) != TypeSystem::TEMPLATE) 
	throw TypeException("Not a template: %s", templ_name);

    type_t domain = types.getFirstSubType(symbols.getType(id));
    const vector<pair<char*, type_t> > &params = types.getRecord(domain);
    for (int i = params.size() - 1; i >= 0; i--)
	expectedArguments.back().push_back(params[i].second);
}

void TypeChecker::instantiationEnd(const char *name, const char *templ_name, uint32_t n)
{
    int32_t id = identifierStack.back();
    identifierStack.pop_back();

    if (!expectedArguments.back().empty())
	errorHandler->handleError("Too few arguments");

    expectedArguments.pop_back();

    if (id == -1)
	return;
	
    try {
	// Copy template (the new template does not have parameters)
	type_t ttype = symbols.getType(id);
	const vector<pair<char *, int32_t> > &parameters =
	    types.getRecord(types.getFirstSubType(ttype));
	int32_t type = types.addTemplate(
	    types.addRecord(vector<pair<char*,int32_t> >()));
	template_t &templ = system->addTemplate(type, name);
	templ = *static_cast<template_t*>(symbols.getData(id));

	// If two many arguments, pop the rest
	if (n > parameters.size()) {
	    fragments.pop(n - parameters.size());
	    n = parameters.size();
	}
	
	// Check arguments and add to map
	int32_t frame = symbols.getActiveFrame();
	symbols.activateFrame(templ.frame);
	while (n--) {
	    int32_t param = symbols.resolve(parameters[n].first);
	    if (!types.isReference(symbols.getType(param))
		&& !types.isConstant(fragments[0].getType()))
	    {
		// Alternatively one could use the initial value of
		// the expression.
		errorHandler->handleError("Non-constant argument used where constant argument was expected.");
	    }

	    if (!types.isSideEffectFree(fragments[0].getType()))
		errorHandler->handleError("Arguments must be side effect free");

	    templ.mapping[param] = fragments[0];
	    fragments.pop();
	}
	symbols.activateFrame(frame);
    } catch (const TypeException e) {
	// remember to pop off the arguments if something is wrong
	fragments.pop(n);
	errorHandler->handleError(e.what());
    }
}
    
// Adds process_t* pointer to system_line
// Checks for dublicate entries
void TypeChecker::process(const char* name)
{
    // Check that such a process exists
    int32_t sym = symbols.resolve(name);
    if (sym == -1) {
	throw TypeException("No such template: %s", name);
    }    

    type_t type = symbols.getType(sym);
    if (types.getClass(type) != TypeSystem::TEMPLATE) {
	throw TypeException("Not a template: %s", name);
    } 

    const vector<pair<char *, int32_t> > &parameters =
	types.getRecord(types.getFirstSubType(type));
    
    if (parameters.size() > 0) {
	throw TypeException("Use of uninstantiated template in system line: %s", name);
    }

    process_t &proc =
	system->addProcess(sym, 
			   *static_cast<template_t *>(symbols.getData(sym)));
    symbols.setType(sym, TypeSystem::PROCESS);
    symbols.setData(sym, &proc);
}
    
void TypeChecker::done()
{

}

void TypeChecker::property(uint32_t kind, int line)
{
    // TODO: check type; must be side effect free constraint
    if (kind == LEADSTO) {
	fragments.merge(2);
	fragments[0].append(LEADSTO, 0, TypeSystem::VOID_TYPE);
    }
    property(kind, line, fragments[0]);
    fragments.pop();
}



/****************************************************************************
 * Side effect free algorithm implementation in visitor design pattern
 */

StatementSideEffectFree::~StatementSideEffectFree() {};

int32_t StatementSideEffectFree::emptyStat(EmptyStatement *stat)
{ return 1; };

int32_t StatementSideEffectFree::exprStat(ExprStatement *stat)
{
    ExpressionProgram::const_iterator first, last;

    for (first = stat->expr.begin(), last = stat->expr.end(); 
	 first != last; ++first)
	if (!types.isSideEffectFree(first->type)) return 0;
    return 1;
};

int32_t StatementSideEffectFree::forStat(ForStatement *stat)
{
    ExpressionProgram::const_iterator first, last;
    assert(stat->stat!=NULL);

    for (first = stat->init.begin(), last = stat->init.end(); 
	 first != last; ++first)
	if (!types.isSideEffectFree(first->type)) return 0;

    for (first = stat->cond.begin(), last = stat->cond.end(); 
	 first != last; ++first)
	if (!types.isSideEffectFree(first->type)) return 0;

    for (first = stat->step.begin(), last = stat->step.end(); 
	 first != last; ++first)
	if (!types.isSideEffectFree(first->type)) return 0;

    return stat->stat->accept(this);
};

int32_t StatementSideEffectFree::whileStat(WhileStatement *stat)
{
    ExpressionProgram::const_iterator first, last;
    assert(stat->stat!=NULL);

    for (first = stat->cond.begin(), last = stat->cond.end(); 
	 first != last; ++first)
	if (!types.isSideEffectFree(first->type)) return 0;

    return stat->stat->accept(this);
};

int32_t StatementSideEffectFree::doWhileStat(DoWhileStatement *stat)
{
    ExpressionProgram::const_iterator first, last;
    assert(stat->stat!=NULL);

    for (first = stat->cond.begin(), last = stat->cond.end(); 
	 first != last; ++first)
	if (!types.isSideEffectFree(first->type)) return 0;

    return stat->stat->accept(this);
};

int32_t StatementSideEffectFree::blockStat(BlockStatement *stat)
{
    vector<Statement*>::const_iterator first, last;
    for (first = stat->begin(), last = stat->end(); 
	 first != last; ++first)
	if (!(*first)->accept(this)) return 0;

    return 1;
};

int32_t StatementSideEffectFree::switchStat(SwitchStatement *stat)
{
    ExpressionProgram::const_iterator first, last;

    for (first = stat->cond.begin(), last = stat->cond.end(); 
	 first != last; ++first)
	if (!types.isSideEffectFree(first->type)) return 0;

    vector<Statement*>::const_iterator f, l;
    for (f = stat->begin(), l = stat->end(); f != l; ++f)
	if (!(*f)->accept(this)) return 0;

    return 1;
};

int32_t StatementSideEffectFree::caseStat(CaseStatement *stat)
{
    ExpressionProgram::const_iterator first, last;

    for (first = stat->cond.begin(), last = stat->cond.end(); 
	 first != last; ++first)
	if (!types.isSideEffectFree(first->type)) return 0;

    vector<Statement*>::const_iterator f, l;
    for (f = stat->begin(), l = stat->end(); f != l; ++f)
	if (!(*f)->accept(this)) return 0;

    return 1;
};

int32_t StatementSideEffectFree::defaultStat(DefaultStatement *stat)
{
    vector<Statement*>::const_iterator f, l;
    for (f = stat->begin(), l = stat->end(); f != l; ++f)
	if (!(*f)->accept(this)) return 0;

    return 1;
};

int32_t StatementSideEffectFree::ifStat(IfStatement *stat)
{
    ExpressionProgram::const_iterator first, last;
    assert(stat->trueCase!=NULL && stat->falseCase!=NULL);

    for (first = stat->cond.begin(), last = stat->cond.end(); 
	 first != last; ++first)
	if (!types.isSideEffectFree(first->type)) return 0;

    if (!stat->trueCase->accept(this)) return 0;
    if (!stat->falseCase->accept(this)) return 0;
    return 1;
};

int32_t StatementSideEffectFree::breakStat(BreakStatement *stat)
{
    return 1;
};

int32_t StatementSideEffectFree::continueStat(ContinueStatement *stat)
{
    return 1;
};

int32_t StatementSideEffectFree::returnStat(ReturnStatement *stat)
{
    ExpressionProgram::const_iterator first, last;

    for (first = stat->value.begin(), last = stat->value.end(); 
	 first != last; ++first)
	if (!types.isSideEffectFree(first->type)) return 0;

    return 1;
};

bool parseXTA(FILE *file, ErrorHandler *error, TimedAutomataSystem *system, bool newxta)
{
    TypeChecker builder(system);
    parseXTA(file, &builder, error, newxta);
    return !error->hasErrors();
}

bool parseXTA(const char *buffer, ErrorHandler *error, TimedAutomataSystem *system, bool newxta)
{
    TypeChecker builder(system);
    parseXTA(buffer, &builder, error, newxta);
    return !error->hasErrors();
}

bool parseXMLBuffer(const char *buffer, ErrorHandler *error, TimedAutomataSystem *system, bool newxta)
{
    TypeChecker builder(system);
    parseXMLBuffer(buffer, &builder, error, newxta);
    return !error->hasErrors();
}

bool parseXMLFile(const char *file, ErrorHandler *error, TimedAutomataSystem *system, bool newxta)
{
    TypeChecker builder(system);
    parseXMLFile(file, &builder, error, newxta);
    return !error->hasErrors();
}

