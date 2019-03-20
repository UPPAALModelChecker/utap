// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2002,2003 Uppsala University and Aalborg University.
   
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
#include <cstdio>
#include "utap/typechecker.hh"
#include "utap/systembuilder.hh"

using std::exception;
using std::set;
using std::pair;
using std::make_pair;
using std::max;
using std::min;
using std::map;
using std::vector;

using namespace UTAP;
using namespace Constants;

class InitialiserException : public std::exception
{
private:
    SubExpression expr;
    char msg[256];
public:
    InitialiserException(const SubExpression &expr, const char *m):
	expr(expr) { strncpy(msg, m, 256); }
    SubExpression getExpression() { return expr; }
    const char *what() const throw() { return msg; }
};

void PersistentVariables::visitVariable(variable_t &variable)
{
    variables.insert(variable.uid.getId());
}

void PersistentVariables::visitClock(clock_t &clock)
{
    variables.insert(clock.uid.getId());
}

void PersistentVariables::visitTemplateAfter(template_t &temp)
{
    frame_t parameters = temp.uid.getType().getFrame();
    for (int i = 0; i < parameters.getSize(); i++) 
	variables.insert(parameters[i].getId());
}

const set<int> &PersistentVariables::get() const
{
    return variables;
}

TypeChecker::TypeChecker(ErrorHandler *handler) : ContextVisitor(handler)
{

}

void TypeChecker::visitSystemBefore(TimedAutomataSystem *value)
{
    system = value;
    system->accept(persistentVariables);
}

void TypeChecker::visitConstant(constant_t &constant)
{
    setContextDeclaration();
    type_t type = constant.uid.getType();
    try {
	annotate(constant.expr);
	if (!isSideEffectFree(constant.expr)) {
	    handleError(constant.expr,
			"Initialiser must not have side effects");
	} else {
	    checkInitialiser(type, constant.expr);
	}
    } catch (InitialiserException &e) {
	handleError(e.getExpression(), e.what());
    }
    if (type.getBase() == type_t::INT) {
	pair<int32_t, int32_t> range = constant.expr.getType().getRange();
	constant.uid.setType(type_t::createInteger(range.first, range.second)
			     .setPrefix(true, prefix::CONSTANT));
    }
}

void TypeChecker::visitVariable(variable_t &variable)
{
    setContextDeclaration();
    try {
	if (variable.expr.empty()) {
	    insertDefault(variable.expr, variable.expr.begin(),
			  variable.uid.getType());
	} else {
	    annotate(variable.expr);
	    if (!isSideEffectFree(variable.expr)) {
		handleError(variable.expr,
			    "Initialiser must not have side effects");
	    } else {
		checkInitialiser(variable.uid.getType(), variable.expr);
	    }
	}
    } catch (InitialiserException &e) {
	handleError(e.getExpression(), e.what());
    }
}

void TypeChecker::visitState(state_t &state)
{
    setContextInvariant(state);
    annotate(state.invariant);

    if (!isInvariant(state.invariant))
	handleError(state.invariant, "Invalid invariant expression");
    if (!isSideEffectFree(state.invariant))
	handleError(state.invariant, "Invariant must be side effect free");
}

void TypeChecker::visitTransition(transition_t &transition)
{
    // guard
    setContextGuard(transition);
    annotate(transition.guard);
    
    if (!isGuard(transition.guard))
	handleError(transition.guard, "Invalid guard");
    else if (!isSideEffectFree(transition.guard))
	handleError(transition.guard, "Guard must be side effect free");

    // sync
    setContextSync(transition);
    annotate(transition.sync);    
    if (!isSideEffectFree(transition.sync))
	handleError(transition.sync,
		    "Synchronisation must be side effect free");

    if (!transition.guard.empty()
	&& transition.guard.getType().getBase() != type_t::INT)
    {
	assert(transition.sync.getType() == type_t::CHANNEL);
	if (transition.sync.getType().hasPrefix(prefix::URGENT))
	    handleError(transition.sync,
			"Clock guards are not allowed on urgent transitions.");

	if (transition.sync.getType().hasPrefix(prefix::BROADCAST)
	    && transition.sync.back().value == SYNC_QUE)
	{
	    handleError(transition.sync,
			"Clock guards are not allowed on broadcast receivers.");
	}
    }    
    
    // assignment
    setContextAssignment(transition);
    annotate(transition.assign);    
    if (!isInteger(transition.assign)
	&& !isClock(transition.assign)
	&& !isRecord(transition.assign))
    {
	handleError(transition.assign, "Invalid assignment expression");
    }

    if (!(transition.assign.back().kind == CONSTANT &&
	  transition.assign.back().value == 1)
	&& isSideEffectFree(transition.assign))
    {
 	handleWarning(transition.assign, "Expression does not have any effect");
    }
}

void TypeChecker::visitInstance(instance_t &instance)
{
    map<int32_t, ExpressionProgram>::iterator i;
    setContextInstantiation();
    i = instance.mapping.begin();
    while (i != instance.mapping.end()) {
	checkParameterCompatible(symbol_t(i->first).getType(), i->second);
	++i;
    }
}

void TypeChecker::visitProperty(SubExpression expr)
{
    setContextNone();
    annotate(expr);
    if (!isSideEffectFree(expr)) 
	handleError(expr, "Property must be side effect free");

    if ((expr.getKind() == LEADSTO &&
	 !(isConstraint(expr[0]) && isConstraint(expr[1])))
	|| (expr.getKind() != LEADSTO && !isConstraint(expr)))
    {
	handleError(expr, "Property must be a constraint");
    }
}

bool TypeChecker::isInteger(SubExpression expr) const
{
    return expr.getType().getBase() == type_t::INT;
}

bool TypeChecker::isClock(SubExpression expr) const
{
    return expr.getType().getBase() == type_t::CLOCK;
}

bool TypeChecker::isRecord(SubExpression expr) const
{
    return expr.getType().getBase() == type_t::RECORD;
}

bool TypeChecker::isDiff(SubExpression expr) const
{
    return expr.getType().getBase() == type_t::DIFF;
}

/**
   Returns true iff type is a valid invariant. A valid invariant is
   either an invariant expression or an integer expression.
*/
bool TypeChecker::isInvariant(SubExpression expr) const
{
    return (expr.getType().getBase() == type_t::INVARIANT)
	|| (expr.getType().getBase() == type_t::INT);
}

/**
   Returns true iff type is a valid guard. A valid guard is either a
   valid invariant or a guard expression.
*/
bool TypeChecker::isGuard(SubExpression expr) const
{
    return (expr.getType().getBase() == type_t::GUARD) || isInvariant(expr);
}

/**
   Returns true iff type is a valid constraint. A valid constraint is
   either a valid guard or a constraint expression.
*/
bool TypeChecker::isConstraint(SubExpression expr) const
{
    return (expr.getType().getBase() == type_t::CONSTRAINT) || isGuard(expr);
}

ExpressionProgram::expression_t TypeChecker::makeConstant(int n)
{
    return ExpressionProgram::expression_t(
	position_t(0, 0, 0, 0), CONSTANT, n, type_t::INT);
}

// checks whether parameter type is compatible to argument type.
// REVISIT: This is not correct for function calls.
void TypeChecker::checkParameterCompatible(type_t param, SubExpression arg)
{
    bool ref = param.hasPrefix(prefix::REFERENCE);
    bool constant = param.hasPrefix(prefix::CONSTANT);
    bool computable = !arg.dependsOn(persistentVariables.get());
    
    // Argument must be side effect free
    if (!isSideEffectFree(arg)) {
	handleError(arg, "Argument must be side effect free");
	return;
    }

    // We have three ok cases:
    // - Constant reference with computable argument
    // - Reference parameter with lhs argument
    // - Value parameter with computable argument
    // If non of the cases is true, then we generate an error
    if (!(ref && constant && computable)
	&& !(ref ? isUniqueReference(arg) : computable))
    {
	handleError(arg, "Incompatible argument");
	return;
    }

    assert(lhs || computable);  /* This is a consequence */

    //
    // The rest depends on the type of the parameters
    //

    // The parameter and the type must have the same base type
    if (param.getBase() != arg.getType().getBase()) {
	handleError(arg, "Incompatible argument");
	return;
    }

    type_t base = param.getBase();
    if (base == type_t::CLOCK)
	return;

    if (base == type_t::INT) {
	// Compute range of argument
	range_t range;
	if (computable) {
	    int value;
	    system->evaluateConstantExpression(arg, value);
	    range = range_t(value, value);
	} else {
	    // in this case we know that arg is a lhs and thus the 
	    // range refers to the declared range (which is exact).
	    range = range_t(arg.getType().getRange());
	}
	
	if (ref && !constant) {
	    // For non-constant reference parameters, the range of the
	    // argument and the range of the parameter must be the
	    // same.
	    if (range != range_t(param.getRange()))
		handleError(arg, "Range of argument does not match range of formal parameter");
	} else {
	    // Otherwise the range of the argument must be within the
	    // range of the parameter: We have two cases; if the
	    // argument is computable then we simply compute
	    // it. Otherwise, we know we deal with a constant
	    // reference paramter and a LHS argument, thus we compute
	    // the symbol and use its declared range.
	    if (!range_t(param.getRange()).contains(range)) 
	    {
		handleError(arg, "Range of argument is outside of the range of the formal parameter");
	    }
	}
    } else if (base == type_t::RECORD) {
	if (param.getRecordFields() != arg.getType().getRecordFields()) 
	    handleError(arg, "Argument has incompatible type");
    } else if (base == type_t::ARRAY) {
	type_t a = arg.getType();
	type_t p = param;
	do {
	    if (a.getBase() != type_t::ARRAY) {
		handleError(arg, "Incompatible argument to array parameter");
		return;
	    }

	    int asize = a.getArraySize();
	    int psize = p.getArraySize();
	    if (asize != psize)
		handleError(arg, "Parameter array size does not match argument array size");
	    
	    p = p.getSub();
	    a = a.getSub();
	} while (p.getBase() == type_t::ARRAY);

	if (a.getBase() != p.getBase())
	    handleError(arg, "Incompatible argument to array parameter");

	if (a.getBase() == type_t::INT && p.getRange() != a.getRange())
	{
	    handleError(arg, "Argument has incompatible range");
	}   
    } else if (base == type_t::CHANNEL) {
	if (param.hasPrefix(prefix::URGENT) ^ arg.getType().hasPrefix(prefix::URGENT)
	    || param.hasPrefix(prefix::BROADCAST) ^ arg.getType().hasPrefix(prefix::BROADCAST))
	    handleError(arg, "Incompatible channel type");
    } else {
	assert(false);
    }
    
#if 0
    if (!param.hasPrefix(prefix::CONSTANT) && argument.hasPrefix(prefix::CONSTANT)) {
	return "non-constant argument expected here";
    }

    if (!param.hasPrefix(prefix::REFERENCE) && !argument.hasPrefix(prefix::CONSTANT)) {
	return "constant argument expected here";
    }
    
    if (param.hasPrefix(prefix::REFERENCE)
	&& !param.hasPrefix(prefix::CONSTANT)
	&& !argument.hasPrefix(prefix::REFERENCE)) 
    {
	return "reference argument expected here";
    }

    if (param.getBase() != argument.getBase())
	return "argument has incompatible type";
    
    if (param.getBase() == type_t::CLOCK) {
	return NULL;
    } else if (param.getBase() == type_t::INT) {
	// Check the range of the argument: It must be within the
	// range of the parameter. For non constant reference parameters
	// the range must be an exact match, since the process/function
	// might update the variable referenced in the argument.
	pair<int32_t,int32_t> prange = param.getRange();
	pair<int32_t,int32_t> arange = argument.getRange();
	if (!(prange.first <= arange.first && 
	      arange.second <= prange.second)) {
	    return "argument has incompatible range";
	}
	if (param.hasPrefix(prefix::REFERENCE) && !param.hasPrefix(prefix::CONSTANT)) {
	    if (prange != arange) {
		return "argument has incompatible range";
	    }
	}
    } else if (param.getBase() == type_t::RECORD) {
	if (param.getRecordFields() != argument.getRecordFields()) 
	    return "argument value type does not match parameter type";
    } else if (param.getBase() == type_t::ARRAY) {
	do {
	    if (argument.getBase() != type_t::ARRAY) {
		return "Incompatible argument to array parameter";
	    }

	    int asize = argument.getArraySize();
	    int psize = param.getArraySize();
	    if (asize != psize)
		return "parameter array size does not match argument array size";
	    param = param.getSub();
	    argument = argument.getSub();
	} while (param.getBase() == type_t::ARRAY);

	if (argument.getBase() != param.getBase())
	    return "Incompatible argument to array parameter";

	if (argument.getBase() == type_t::INT) {
	    pair<int32_t, int32_t> prange = param.getRange();
	    pair<int32_t, int32_t> arange = argument.getRange();
	    if (prange != arange) {
		return "Argument has incompatible range";
	    }
	}   
    } else if (param.getBase() == type_t::CHANNEL) {
	if (param.hasPrefix(prefix::URGENT) ^ argument.hasPrefix(prefix::URGENT)
	    || param.hasPrefix(prefix::BROADCAST) ^ argument.hasPrefix(prefix::BROADCAST))
	    return "incompatible channel type";
    } else {
	throw TypeException(unsupported);
    }
#endif    
}

void TypeChecker::insertDefault(ExpressionProgram &expr,
				ExpressionProgram::iterator pos,
				type_t type)
{
    type_t base = type.getBase();
    if (base == type_t::INT) {
        const pair<int, int> &range = type.getRange();
        if (range.first <= 0 && 0 <= range.second)
            expr.insert(pos, makeConstant(0));
        else
            expr.insert(pos, makeConstant(range.first));
    } else if (base == type_t::ARRAY) {
        int size = type.getArraySize();
        while (size--)
            insertDefault(expr, pos, type.getSub());
        expr.insert(pos, ExpressionProgram::expression_t(
			position_t(0, 0, 0, 0),
                        LIST, type.getArraySize(),
                        type.setPrefix(true, prefix::CONSTANT)));
    } else if (base == type_t::RECORD) {
	frame_t fields = type.getRecordFields();
        for (int32_t i = 0; i < fields.getSize(); i++)
            insertDefault(expr, pos, fields[i].getType());
        expr.insert(pos,
		    ExpressionProgram::expression_t(
			position_t(0, 0, 0, 0), LIST, fields.getSize(),
			type.setPrefix(true, prefix::CONSTANT)));
    } else {
	assert(false);
    }
}

// Inserts the default initialiser for a variable of 'type' at
// position 'pos' in 'expr'.
void TypeChecker::checkInitialiser(type_t type, SubExpression init)
{
    type_t base = type.getBase();
    if (base == type_t::ARRAY) {
        if (init.getKind() != LIST)
            throw InitialiserException(init, "Invalid array initialiser");
        int dim = type.getArraySize();
        if (init.getSize() > dim)
            throw InitialiserException(init,
				       "Excess elements in array initialiser");

	type_t subtype = type.getSub();
	frame_t fields = init.getType().getRecordFields();
	int i;
        for (i = 0; i < fields.getSize(); i++) {
            if (fields[i].getName() != NULL) 
		throw InitialiserException(
		    init[i], "Unknown field specified in initialiser");
            checkInitialiser(subtype, init[i]);
        }
        
        if (i < dim) 
	    throw InitialiserException(init, "Missing fields in initialiser");

        init.setType(type);
    } else if (base == type_t::INT) {
	if (init.getType().getBase() != type_t::INT)
	    throw InitialiserException(init, "Invalid initialiser");
	pair<int32_t, int32_t> range = init.getType().getRange();

	// If possible, reduce range of integer to an exact value
	if (range.first != range.second) {
	    int n;
	    if (system->evaluateConstantExpression(init, n)) {
		range.first = range.second = n;
		init.setType(type_t::createInteger(range.first, range.second).setPrefix(true, prefix::SIDE_EFFECT_FREE).setPrefix(true, prefix::CONSTANT));
	    }
	}

	// Make sure the initialisers range is within that of the variable
	// being initialised.
	pair<int32_t, int32_t> target = type.getRange();
	if (!(target.first <= range.first && range.first <= target.second)) 
	    throw InitialiserException(init, "Initialiser is out of range");
    } else if (base == type_t::RECORD) {
	if (type.getRecordFields() == init.getType().getRecordFields())
	    return;  // Same type name, so we are happy

	if (init.getKind() != LIST) {
	    handleError(init, "Invalid initialiser for struct");
	    return;
	}

	frame_t fields = type.getRecordFields();
	frame_t initialisers = init.getType().getRecordFields();
	vector<int> indices(fields.getSize(), -1);

	// Populate the vector st. indices[i] contains the index of
	// the initialiser for the ith field.
	int current = 0;
	for (int32_t i = 0; i < initialisers.getSize(); i++) {
	    if (initialisers[i].getName() != NULL) {
		current = fields.getIndexOf(initialisers[i].getName());
		if (current == -1) {
		    handleError(init[i], "Unknown field");
		    break;
		}
	    }

	    if (current >= fields.getSize()) {
		handleError(init[i], "Excess elements in intialiser");
		break;
	    }
	    
	    if (indices[current] != -1) {
		handleError(init[i], "Multiple initialisers for field");
		continue;
	    }
	    
	    indices[current] = i;
	    ++current;
	}

	// Check the type of each initialiser and that all fields do
	// have an initialiser.
	for (int32_t i = 0; i < fields.getSize(); i++) {
	    if (indices[i] == -1) {
		handleError(init, "Incomplete initialiser");
		return;
	    }
	    checkInitialiser(fields[i].getType(), init[indices[i]]);
	}

	// Construct new initialiser
	ExpressionProgram e;
	for (int32_t i = 0; i < fields.getSize(); i++) 
	    e.append(init[indices[i]]);
	e.append(init.getPosition(), LIST, fields.getSize(), type);
	init.replace(e);
#if 0	
	frame_t fields = init.getType().getRecordFields();
	frame_t target = type.getRecordFields();
	frame_t frame = frame_t::createFrame();
	
	// Complete field names
	for (uint32_t i = 0; i < fields.getSize(); i++) {
	    if (fields[i].getName() == NULL) {
		int32_t pos = 0;
		if (i > 0) {
		    pos = target.getIndexOf(fields[i - 1].getName()) + 1;
		    assert(pos > 0);
		    if (pos >= target.getSize())
			throw TypeException("Excess elements in struct initialiser");
		}
		frame.addSymbol(target[pos].getName(), fields[i].getType());
	    } else {
		int idx = target.getIndexOf(fields[i].getName());
		if (idx == -1)
		    throw TypeException("Unknown field type");
		frame.addSymbol(target[i].getName(), target[i].getType());
	    }
	}

	// Check for duplicates
	for (uint32_t i = 1; i < frame.getSize(); i++) {
	    for (uint32_t j = 0; j < i; j++)
		if (strcmp(frame[i].getName(), frame[j].getName()) == 0)
		    throw TypeException("Multiple initialisers for field '%s'", frame[i].getName());
	}

	// Construct new initialiser (with correct order and all
	// missing fields inserted).
	for (uint32_t i = 0; i < target.getSize(); i++) {
	    int32_t pos = frame.getIndexOf(target[i].getName());
	    if (pos == -1) {
		if (required)
		    throw TypeException("Missing initialiser for '%s'",
					target[i].getName());
		insertDefault(init.getExpression(),
			      i == 0 ? init.begin() : init[i - 1].end(), 
			      target[i].getType());
		init.setValue(init.getSize() + 1);
	    } else {
		checkInitialiser(target[i].getType(), init[pos + i]);
		if (pos > 0)
		    init.move(pos + i, i);
		record.erase(record.begin() + pos);
	    }
	}

	init.setType(type.setPrefix(true, prefix::CONSTANT)
		     .setPrefix(false, prefix::REFERENCE)
		     .setPrefix(true, prefix::SIDE_EFFECT_FREE));
#endif	
    }
}

/** Returns the type of a binary operation with non-integer operands. */
type_t TypeChecker::typeOfBinaryNonInt(
    SubExpression left, uint32_t binaryop, SubExpression right)
{
    type_t type;
    
    switch (binaryop) {
    case PLUS:
	if (isInteger(left) && isClock(right)
	    || isClock(left) && isInteger(right))
	{
	    type = type_t::CLOCK;
	} else if (isDiff(left) && isInteger(right) 
		   || isInteger(left) && isDiff(right))
	{
	    type = type_t::DIFF;
	}
	break;
	    
    case MINUS:
	if (isClock(left) && isInteger(right)) 
	    // removed  "|| isInteger(left.type) && isClock(right.type)" 
	    // in order to be able to convert into ClockGuards
	{
	    type = type_t::CLOCK;
	} 
	else if (isDiff(left) && isInteger(right)
		 || isInteger(left) && isDiff(right)
		 || isClock(left) && isClock(right)) 
	{
	    type = type_t::DIFF;
	}
	break;

    case AND:
	if (isInvariant(left) && isInvariant(right)) {
	    type = type_t::INVARIANT;
	} else if (isGuard(left) && isGuard(right)) {
	    type = type_t::GUARD;
	} else if (isConstraint(left) && isConstraint(right)) {
	    type = type_t::CONSTRAINT;
	}
	break;
	    
    case OR:
	if (isConstraint(left) && isConstraint(right)) {
	    type = type_t::CONSTRAINT;
	}
	break;

    case LT:
    case LE:
	if (isClock(left) && isClock(right)
	    || isClock(left) && isInteger(right)
	    || isDiff(left) && isInteger(right)
	    || isInteger(left) && isDiff(right))
	{
	    type = type_t::INVARIANT;
	} else if (isInteger(left) && isClock(right)) {
	    type = type_t::GUARD;
	}
	break;

    case EQ:
	if (isClock(left) && isClock(right)
	    || isClock(left) && isInteger(right)
	    || isInteger(left) && isClock(right)
	    || isDiff(left) && isInteger(right)
	    || isInteger(left) && isDiff(right))
	{
	    type = type_t::GUARD;
	}
	break;
	
    case NEQ:
	if (isClock(left) && isClock(right)
	    || isClock(left) && isInteger(right)
	    || isInteger(left) && isClock(right)
	    || isDiff(left) && isInteger(right)
	    || isInteger(left) && isDiff(right))
	{
	    type = type_t::CONSTRAINT;
	}
	break;

    case GE:
    case GT:
	if (isClock(left) && isClock(right)
	    || isInteger(left) && isClock(right)
	    || isDiff(left) && isInteger(right)
	    || isInteger(left) && isDiff(right))
	{
	    type = type_t::INVARIANT;
	} else if (isClock(left) && isGuard(right)) {
	    type = type_t::GUARD;
	}
	break;
    }

    return type;
}

/** Returns true if arguments of an inline if are compatible. The
    'then' and 'else' arguments are compatible if and only if they
    have the same base type. In case of arrays, they must have the
    same size and the subtypes must be compatible. In case of records,
    they must have the same type name.
*/
bool TypeChecker::areInlineIfCompatible(type_t thenArg, type_t elseArg)
{
    type_t base = thenArg.getBase();

    if (base != elseArg.getBase()) {
	return false;
    }

    if (base == type_t::ARRAY) {
	return (thenArg.getArraySize() == elseArg.getArraySize())
	    && areInlineIfCompatible(thenArg.getSub(), elseArg.getSub());
    }

    if (base == type_t::RECORD) {
	return (thenArg.getRecordFields() != elseArg.getRecordFields());
    }

    return true;
}

/** Returns true if lvalue and rvalue are assignment compatible.  This
    is the case when an expression of type rvalue can be assigned to
    an expression of type lvalue. It does not check whether lvalue is
    actually a left-hand side value. In case of integers, it does not
    check the range of the expressions.
*/
bool TypeChecker::areAssignmentCompatible(type_t lvalue, type_t rvalue) 
{
    type_t lbase = lvalue.getBase();
    if (lbase == type_t::VOID_TYPE) {
	return false;
    }

    if (lbase == type_t::CLOCK || lbase == type_t::INT) {
	return (rvalue.getBase() == type_t::INT);
    }

    if (lbase == type_t::RECORD) {
	return (rvalue.getBase() == type_t::RECORD
		&& lvalue.getRecordFields() != rvalue.getRecordFields());
    }

    return false;
}
    
/** Type check and annotate the expression. This function performs
    basic type checking of the expression given and assigns a type to
    every subexpression of the expression. It checks that only
    left-hand side values are updated, checks that functions are
    called with the correct arguments, checks that operators are used
    with the correct operands and checks that operands to assignment
    operators are assignment compatible. Errors are reported by
    calling handleError(). This function does not check/compute the
    range of integer expressions and thus it does not produce
    out-of-range errors or warnings.
*/
void TypeChecker::annotate(SubExpression expr)
{
    for (int i = 0; i < expr.getSize(); i++) 
	annotate(expr[i]);

    type_t type, arg1, arg2, arg3;
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
    case MIN:
    case MAX:
    case LT:
    case LE:
    case EQ:
    case NEQ:
    case GE:
    case GT:
	if (isInteger(expr[0]) && isInteger(expr[1])) {
	    type = type_t::INT;
	} else {
	    type = typeOfBinaryNonInt(expr[0], expr.getKind(), expr[1]);
	    if (type == type_t()) {
		handleError(expr, "Invalid operands to binary operator");
		type = type_t::CONSTRAINT;
	    }
	}
	break;

    case NOT:
	if (isInteger(expr[0])) {
	    type = type_t::INT;
	} else if (isConstraint(expr[0])) {
	    type = type_t::CONSTRAINT;
	} else {
	    handleError(expr, "Invalid operation for type");
	    type = type_t::INT;
	}
	break;
	
    case UNARY_MINUS:
	if (!isInteger(expr[0])) {
	    handleError(expr, "Invalid operation for type");
	}
	type = type_t::INT;
	break;

    case ASSIGN:
	if (!areAssignmentCompatible(expr[0].getType(), expr[1].getType())) {
	    handleError(expr, "Incompatible types");
	} else if (!isLHSValue(expr[0])) {
	    handleError(expr[0], "Left hand side value expected");
	}
	type = expr[0].getType();
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
	if (!isInteger(expr[0]) || !isInteger(expr[1])) {
	    handleError(expr, "Non-integer types must use regular assignment operator.");
	} else if (!isLHSValue(expr[0])) {
	    handleError(expr[0], "Left hand side value expected");	    
	}
	type = expr[0].getType();
	break;
      
    case POSTINCREMENT:
    case PREINCREMENT:
    case POSTDECREMENT:
    case PREDECREMENT:
	if (!isInteger(expr[0])) {
	    handleError(expr, "Argument must be an integer value");
	} else if (!isLHSValue(expr[0])) {
	    handleError(expr[0], "Left hand side value expected");	    
	}
	type = type_t::INT;
	break;
    
    case INLINEIF:
	if (!isInteger(expr[0])) {
	    handleError(expr, "First argument of inline if must be an integer");
	}
	if (!areInlineIfCompatible(expr[1].getType(), expr[2].getType())) {
	    handleError(expr, "Incompatible argument to inline if");
	}
	type = expr[1].getType();
	break;
      
    case COMMA:
	if (!isInteger(expr[0]) && !isClock(expr[0]) && !isRecord(expr[0])
	    || !isInteger(expr[1]) && !isClock(expr[1]) && !isRecord(expr[1]))
	{
	    handleError(expr, "Arguments must be of integer, clock or record type");
	}
	type = expr[1].getType();
	break;
      
    case FUNCALL:
	// TODO: Check arguments
	break;
      
    default:
	return;
    }
    expr.setType(type);
}

/** Returns true if the expression is side effect free. An expression
    is side effect free if it does not modify any variables except
    variables local to functions (and thus not part of the variable
    vector).
*/
bool TypeChecker::isSideEffectFree(SubExpression expr) const
{
    return !expr.changesVariable(persistentVariables.get());
}

/** Returns true if expression is a left-hand-side value.
    Left-hand-side values are expressions that result in references to
    variables. Note: An inline if over integers is only a LHS value if
    both results have the same declared range.
*/
bool TypeChecker::isLHSValue(SubExpression expr) const
{
    type_t t, f;
    switch (expr.getKind()) {
    case IDENTIFIER:
	return !symbol_t(expr.getValue()).getType().hasPrefix(prefix::CONSTANT);

    case DOT:
    case ARRAY:
	// REVISIT: What if expr[0] is a process?
	return isLHSValue(expr[0]);
	
    case PREINCREMENT:
    case PREDECREMENT:
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
	return isLHSValue(expr[0]);	    // REVISIT: Maybe skip this
	
    case INLINEIF:
	if (!isLHSValue(expr[1]) || !isLHSValue(expr[2]))
	    return false;
	
	t = expr[1].getSymbol().getType();
	f = expr[2].getSymbol().getType();
	return (t.getBase() != type_t::INT || t.getRange() == f.getRange());
      
    case COMMA:
	return isLHSValue(expr[1]);

    case FUNCALL:
	// Functions cannot return references (yet!)
	break;
    }
    return false;
}

/** Returns true if expression is a reference to a unique variable.
    Thus is similar to expr being an LHS value, but in addition we
    require that the reference does not depend on any non-computable
    (at parse time) expressions. Thus i[v] is a LHS value, but if v is
    a non-constant variable, then it does not result in a unique
    reference.
*/
bool TypeChecker::isUniqueReference(SubExpression expr) const
{
    switch (expr.getKind()) {
    case IDENTIFIER:
	return !expr.getType().hasPrefix(prefix::CONSTANT);
    case DOT:
	return isUniqueReference(expr[0]);

    case ARRAY:
	return isUniqueReference(expr[0])
	    && !expr[1].dependsOn(persistentVariables.get());
	
    case PREINCREMENT:
    case PREDECREMENT:
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
	return isUniqueReference(expr[0]);
	
    case INLINEIF:
	return false;
      
    case COMMA:
	return isUniqueReference(expr[1]);

    case FUNCALL:
	// Functions cannot return references (yet!)
	break;
    }
    return false;
}


bool parseXTA(FILE *file, ErrorHandler *error, TimedAutomataSystem *system, bool newxta)
{
    SystemBuilder builder(system);
    TypeChecker checker(error);
    parseXTA(file, &builder, error, newxta);
    system->accept(checker);
    return !error->hasErrors();
}

bool parseXTA(const char *buffer, ErrorHandler *error, TimedAutomataSystem *system, bool newxta)
{
    SystemBuilder builder(system);
    TypeChecker checker(error);
    parseXTA(buffer, &builder, error, newxta);
    system->accept(checker);
    return !error->hasErrors();
}

bool parseXMLBuffer(const char *buffer, ErrorHandler *error, TimedAutomataSystem *system, bool newxta)
{
    SystemBuilder builder(system);
    TypeChecker checker(error);
    parseXMLBuffer(buffer, &builder, error, newxta);
    system->accept(checker);
    return !error->hasErrors();
}

bool parseXMLFile(const char *file, ErrorHandler *error, TimedAutomataSystem *system, bool newxta)
{
    SystemBuilder builder(system);
    TypeChecker checker(error);
    parseXMLFile(file, &builder, error, newxta);
    system->accept(checker);
    return !error->hasErrors();
}

