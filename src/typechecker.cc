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
#include <cassert>

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

std::map<symbol_t, expression_t> TypeChecker::empty;

class InitialiserException : public std::exception
{
private:
    expression_t expr;
    char msg[256];
public:
    InitialiserException(expression_t expr, const char *m):
	expr(expr) { strncpy(msg, m, 256); }
    ~InitialiserException() throw() {}
    expression_t getExpression() { return expr; }
    const char *what() const throw() { return msg; }
};

void PersistentVariables::visitVariable(variable_t &variable)
{
    if (!variable.uid.getType().hasPrefix(prefix::CONSTANT))
	variables.insert(variable.uid);
}

void PersistentVariables::visitTemplateAfter(template_t &temp)
{
    frame_t parameters = temp.uid.getType().getFrame();
    for (uint32_t i = 0; i < parameters.getSize(); i++) 
	if (parameters[i].getType().hasPrefix(prefix::REFERENCE)
	    || !parameters[i].getType().hasPrefix(prefix::CONSTANT))
	{
	    variables.insert(parameters[i]);
	}
}

const set<symbol_t> &PersistentVariables::get() const
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

/** Checks that the range of an integer (if it has one) is type correct. */
void TypeChecker::checkIntegerType(type_t type)
{
    assert(type.getBase() == type_t::INT);

    expression_t lower = type.getRange().first;
    expression_t upper = type.getRange().second;

    // Check if there is a range; if not then return
    if (lower.empty())
	return;

    annotate(lower);
    annotate(upper);

    if (!isInteger(lower))
	handleError(lower, "Integer expression expected");
    else if (lower.dependsOn(persistentVariables.get()))
	handleError(lower, "Constant expression expected");

    if (!isInteger(upper))
	handleError(upper, "Integer expression expected");
    else if (upper.dependsOn(persistentVariables.get()))
	handleError(upper, "Constant expression expected");
}

void TypeChecker::visitConstant(variable_t &constant)
{
    setContextDeclaration();
    type_t type = constant.uid.getType();
    if (type.getBase() == type_t::INT) 
	checkIntegerType(type);
    checkInitialiser(constant);
}

void TypeChecker::visitVariable(variable_t &variable)
{
    setContextDeclaration();
    type_t type = variable.uid.getType();
    if (type.getBase() == type_t::INT) 
	checkIntegerType(type);

    checkInitialiser(variable);
}

void TypeChecker::visitState(state_t &state)
{
    if (!state.invariant.empty()) {
	setContextInvariant(state);
	annotate(state.invariant);
    
	if (!isInvariant(state.invariant))
	    handleError(state.invariant, "Invalid invariant expression");
	if (!isSideEffectFree(state.invariant))
	    handleError(state.invariant, "Invariant must be side effect free");
    }
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
    if (!transition.sync.empty()) {
	setContextSync(transition);
	annotate(transition.sync);    

	if (!isSideEffectFree(transition.sync))
	    handleError(transition.sync,
			"Synchronisation must be side effect free");

	type_t channel = transition.sync.get(0).getType();
	assert(channel.getBase() == type_t::CHANNEL);

	bool hasClockGuard = !transition.guard.empty()
	    && transition.guard.getType().getBase() != type_t::INT;
	bool hasInvariant = !transition.dst->invariant.empty();
	bool isUrgent = channel.hasPrefix(prefix::URGENT);
	bool receivesBroadcast = channel.hasPrefix(prefix::BROADCAST) 
	    && transition.sync.getSync() == SYNC_QUE;
	
	if (isUrgent && hasClockGuard) {
	    handleError(transition.sync,
			"Clock guards are not allowed on urgent transitions.");
	}
	
	if (receivesBroadcast && hasClockGuard) {
	    handleError(transition.sync,
			"Clock guards are not allowed on broadcast receivers.");
	}
#if 0
	if (receivesBroadcast && hasInvariant) {
	    handleError(transition.sync,
			"Broadcast receiption is not supported when the target location has invariants.");
	}

	if (isUrgent && hasInvariant) {
	    handleError(transition.sync,
			"Urgent synchronisations are not supported when the target location has invariants.");
	}
#endif	
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

    if (!(transition.assign.getKind() == CONSTANT &&
	  transition.assign.getValue() == 1)
	&& isSideEffectFree(transition.assign))
    {
 	handleWarning(transition.assign, "Expression does not have any effect");
    }
}

void TypeChecker::visitInstance(instance_t &instance)
{
    Interpreter interpreter(system->getConstantValuation());
    interpreter.addValuation(instance.mapping);

    setContextInstantiation();

    map<symbol_t, expression_t>::iterator i = instance.mapping.begin();
    while (i != instance.mapping.end()) {
	annotate(i->second);
	checkParameterCompatible(interpreter,
				 i->first.getType(), i->second);
	++i;
    }
}

void TypeChecker::visitProperty(expression_t expr)
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

bool TypeChecker::isInteger(expression_t expr) const
{
    return expr.getType().getBase() == type_t::INT;
}

bool TypeChecker::isClock(expression_t expr) const
{
    return expr.getType().getBase() == type_t::CLOCK;
}

bool TypeChecker::isRecord(expression_t expr) const
{
    return expr.getType().getBase() == type_t::RECORD;
}

bool TypeChecker::isDiff(expression_t expr) const
{
    return expr.getType().getBase() == type_t::DIFF;
}

/**
   Returns true iff type is a valid invariant. A valid invariant is
   either an invariant expression or an integer expression.
*/
bool TypeChecker::isInvariant(expression_t expr) const
{
    return expr.empty()
	|| (expr.getType().getBase() == type_t::INVARIANT)
	|| (expr.getType().getBase() == type_t::INT);
}

/**
   Returns true iff type is a valid guard. A valid guard is either a
   valid invariant or a guard expression.
*/
bool TypeChecker::isGuard(expression_t expr) const
{
    return (expr.getType().getBase() == type_t::GUARD) || isInvariant(expr);
}

/**
   Returns true iff type is a valid constraint. A valid constraint is
   either a valid guard or a constraint expression.
*/
bool TypeChecker::isConstraint(expression_t expr) const
{
    return (expr.getType().getBase() == type_t::CONSTRAINT) || isGuard(expr);
}

expression_t TypeChecker::makeConstant(int n)
{
    return expression_t::createConstant(position_t(), n);
}

/** Returns a value indicating the capabilities of a channel. For
    urgent channels this is 0, for non-urgent broadcast channels this
    is 1, and in all other cases 2. An argument to a channel parameter
    must have at least the same capability as the parameter. */
static int channelCapability(type_t type)
{
    assert(type.getBase() == type_t::CHANNEL);
    if (type.hasPrefix(prefix::URGENT))
	return 0;
    if (type.hasPrefix(prefix::BROADCAST))
	return 1;
    return 2;
}

// checks whether parameter type is compatible to argument type.
// REVISIT: This is not correct for function calls.
void TypeChecker::checkParameterCompatible(
    const Interpreter &interpreter, type_t param, expression_t arg)
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

    assert(isLHSValue(arg) || computable);  /* This is a consequence */

    // Resolve base type of arrays
    type_t argType = arg.getType();
    while (param.getBase() == type_t::ARRAY) {
	if (argType.getBase() != type_t::ARRAY) {
	    handleError(arg, "Incompatible argument to array parameter");
	    return;
	}

	try {
	    int32_t argSize = interpreter.evaluate(argType.getArraySize());
	    int32_t paramSize = interpreter.evaluate(param.getArraySize());
	
	    if (argSize != paramSize)
		handleError(arg, "Parameter array size does not match argument array size");
	} catch (InterpreterException) {
	    assert(0);
	}
	    
	param = param.getSub();
	argType = argType.getSub();
    }

    // The parameter and the argument must have the same base type
    if (param.getBase() != argType.getBase()) {
	handleError(arg, "Incompatible argument");
	return;
    }

    // For clocks there is no more to check
    type_t base = param.getBase();
    if (base == type_t::CLOCK)
	return;

    // For integers we need to consider the range
    if (base == type_t::INT) {
	// Special case; if parameter has no range, then everything
	// is accepted - this ensures compatibility with 3.2
	if (param.getRange().first.empty())
	    return;
	
	// Compute range of the argument. We have two cases; if the
	// argument is computable then we simply compute
	// it. Otherwise, we know we deal with a LHS argument, thus we
	// compute the symbol and use its declared range.
	range_t argRange, paramRange;
	try {
	    if (computable) {
		vector<int32_t> value;
		interpreter.evaluate(arg, value);
		for (uint32_t i = 0; i < value.size(); i++) {
		    argRange = argRange.join(range_t(value[i]));
		}
	    } else {
		// In this case we know that arg is a lhs and thus the
		// range refers to the declared range 
		argRange = interpreter.evaluate(argType.getRange());
	    }

	    // Compute range of parameter
	    paramRange = interpreter.evaluate(param.getRange());
	} catch (InterpreterException) {
	    // We couldn't compute the ranges; we can assume that we 
	    // have already reported an error, so we simply ignore it 
	    // here.
	    return;
	}
	
	if (ref && !constant) {
	    // For non-constant reference parameters, the range of the
	    // argument and the range of the parameter must be the
	    // same.
	    if (argRange != paramRange)
		handleError(arg, "Range of argument does not match range of formal parameter");
	} else {
	    // Otherwise the range of the argument must be within the
	    // range of the parameter: 
	    if (!paramRange.contains(argRange)) 
	    {
		handleError(arg, "Range of argument is outside of the range of the formal parameter");
	    }
	}
    } else if (base == type_t::RECORD) {
	if (param.getRecordFields() != argType.getRecordFields()) 
	    handleError(arg, "Argument has incompatible type");
    } else if (base == type_t::CHANNEL) {
	if (channelCapability(argType) < channelCapability(param))
	    handleError(arg, "Incompatible channel type");
    } else {
	assert(false);
    }
}

/** Checks whether init is a valid initialiser for a variable or
    constant of the given type. */
void TypeChecker::checkInitialiser(type_t type, expression_t init)
{
    Interpreter interpreter(system->getConstantValuation());
    type_t base = type.getBase();
    if (base == type_t::ARRAY) {
        if (init.getKind() != LIST)
            throw InitialiserException(init, "Invalid array initialiser");
	
	int32_t dim;
	try {
	    dim = interpreter.evaluate(type.getArraySize());
	} catch (InterpreterException) {
	    throw InitialiserException(
		init, "Arrays with parameterized size cannot have an initialiser");
	}

        if (init.getSize() > (uint32_t)dim)
            throw InitialiserException(init,
				       "Excess elements in array initialiser");

	type_t subtype = type.getSub();
	frame_t fields = init.getType().getRecordFields();
        for (uint32_t i = 0; i < fields.getSize(); i++) {
            if (fields[i].getName() != NULL) 
		throw InitialiserException(
		    init[i], "Unknown field specified in initialiser");
            checkInitialiser(subtype, init[i]);
        }
        
        if (fields.getSize() < (uint32_t)dim) 
	    throw InitialiserException(init, "Missing fields in initialiser");
    } else if (base == type_t::INT) {
	if (init.getType().getBase() != type_t::INT)
	    throw InitialiserException(init, "Invalid initialiser");

	// If there is no range (this might be the case when the
	// variable is a constant), then we cannot do anymore.
	if (type.getRange().first.empty())
	    return;

	// In general we cannot assure that the initialiser is within
	// the range of the variable - what we can do is to check that
	// if both the range of the variable and the initialiser are
	// computable, then the initialiser should be within the
	// range.

	try {
	    // If possible, compute value and range
	    int n = interpreter.evaluate(init);
	    range_t range = interpreter.evaluate(type.getRange());
	
	    // YES! Everything was computable, so make sure that initialiser
	    // is within range.
	    if (!range.contains(n))
		throw InitialiserException(init, "Initialiser is out of range");
	} catch (InterpreterException) {
	    // NO! We cannot check more.
	    return;
	}
    } else if (base == type_t::RECORD) {
	if (type.getRecordFields() == init.getType().getRecordFields())
	    return;

	if (init.getKind() != LIST) 
	    throw InitialiserException(init, "Invalid initialiser for struct");

	frame_t fields = type.getRecordFields();
	frame_t initialisers = init.getType().getRecordFields();
	vector<bool> hasInitialiser(fields.getSize(), false);

	int32_t current = 0;
	for (uint32_t i = 0; i < initialisers.getSize(); i++, current++) {
	    if (initialisers[i].getName() != NULL) {
		current = fields.getIndexOf(initialisers[i].getName());
		if (current == -1) {
		    handleError(init[i], "Unknown field");
		    break;
		}
	    }

	    if (current >= (int32_t)fields.getSize()) {
		handleError(init[i], "Excess elements in intialiser");
		break;
	    }
	    
	    if (hasInitialiser[current]) {
		handleError(init[i], "Multiple initialisers for field");
		continue;
	    }
	    
	    hasInitialiser[current] = true;
	    checkInitialiser(fields[current].getType(), init[i]);
	}

	// Check the type of each initialiser and that all fields do
	// have an initialiser.
	for (uint32_t i = 0; i < fields.getSize(); i++) {
	    if (!hasInitialiser[i]) {
		throw InitialiserException(init, "Incomplete initialiser");
	    }	
	}
    }
    return;
}

/** Checks the initialiser of a constant or a variable */
void TypeChecker::checkInitialiser(variable_t &var)
{
    try {
	if (!var.expr.empty()) {
	    annotate(var.expr);
	    if (!isSideEffectFree(var.expr)) {
		handleError(var.expr, "Initialiser must not have side effects");
	    } else {
		checkInitialiser(var.uid.getType(), var.expr);
	    }
	}
    } catch (InitialiserException &e) {
	handleError(e.getExpression(), e.what());
    }
}

/** Returns the type of a binary operation with non-integer operands. */
type_t TypeChecker::typeOfBinaryNonInt(
    expression_t left, uint32_t binaryop, expression_t right)
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
	return (thenArg.getArraySize().equal(elseArg.getArraySize()))
	    && areInlineIfCompatible(thenArg.getSub(), elseArg.getSub());
    }

    if (base == type_t::RECORD) {
	return (thenArg.getRecordFields() == elseArg.getRecordFields());
    }

    if (base == type_t::CHANNEL) {
	return (thenArg.hasPrefix(prefix::URGENT) == elseArg.hasPrefix(prefix::URGENT))
	    && (thenArg.hasPrefix(prefix::BROADCAST) == elseArg.hasPrefix(prefix::BROADCAST));
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
    basic type checking of the given expression and assigns a type to
    every subexpression of the expression. It checks that only
    left-hand side values are updated, checks that functions are
    called with the correct arguments, checks that operators are used
    with the correct operands and checks that operands to assignment
    operators are assignment compatible. Errors are reported by
    calling handleError(). This function does not check/compute the
    range of integer expressions and thus does not produce
    out-of-range errors or warnings.
*/
void TypeChecker::annotate(expression_t expr)
{
    if (expr.empty())
	return;

    for (uint32_t i = 0; i < expr.getSize(); i++) 
	annotate(expr[i]);

    type_t type, arg1, arg2, arg3;
    switch (expr.getKind()) {
    case EQ:
    case NEQ:
	if (isInteger(expr[0]) && isInteger(expr[1])) {
	    type = type_t::INT;
	} else if (expr[0].getType().getBase() == type_t::RECORD
		   && expr[0].getType().getRecordFields() 
		   == expr[1].getType().getRecordFields())
	{
	    type = type_t::INT;
	} else {
	    type = typeOfBinaryNonInt(expr[0], expr.getKind(), expr[1]);
	    if (type == type_t()) {
		handleError(expr, "Invalid operands to binary operator");
		type = type_t::CONSTRAINT;
	    }
	}
	break;

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
bool TypeChecker::isSideEffectFree(expression_t expr) const
{
    return !expr.changesVariable(persistentVariables.get());
}

/** Returns true if expression is a left-hand-side value.
    Left-hand-side values are expressions that result in references to
    variables. Note: An inline if over integers is only a LHS value if
    both results have the same declared range.
*/
bool TypeChecker::isLHSValue(expression_t expr) const
{
    type_t t, f;
    switch (expr.getKind()) {
    case IDENTIFIER:
	return !expr.getSymbol().getType().hasPrefix(prefix::CONSTANT);

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
	
	// The annotate() method ensures that the value of the two
	// result arguments are compatible; for integers we
	// additionally require them to have the same (syntactic)
	// range declaration for them to be usable as LHS values.

	t = expr[1].getSymbol().getType();
	f = expr[2].getSymbol().getType();

	while (t.getBase() == type_t::ARRAY) t = t.getSub();
	while (f.getBase() == type_t::ARRAY) f = f.getSub();

	return (t.getBase() != type_t::INT 
		|| (t.getRange().first.equal(f.getRange().first)
		    && t.getRange().second.equal(f.getRange().second)));
      
    case COMMA:
	return isLHSValue(expr[1]);

    case FUNCALL:
	// Functions cannot return references (yet!)

    default:
	return false;
    }
}

/** Returns true if expression is a reference to a unique variable.
    Thus is similar to expr being an LHS value, but in addition we
    require that the reference does not depend on any non-computable
    expressions. Thus i[v] is a LHS value, but if v is a non-constant
    variable, then it does not result in a unique reference.
*/
bool TypeChecker::isUniqueReference(expression_t expr) const
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

    default:
	return false;
    }
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

