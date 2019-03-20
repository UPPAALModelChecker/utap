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

// TODO:
//      add support for functions

#include <vector>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cassert>
#include <inttypes.h>

#include "utap/systembuilder.hh"

using namespace UTAP;
using namespace Constants;

using std::vector;
using std::pair;
using std::make_pair;
using std::min;
using std::max;

const char *const SystemBuilder::unsupported =
"Internal error: Feature not supported in this mode.";
const char *const SystemBuilder::invalid_type = "Invalid type";

#define defaultIntMin -0x7FFF
#define defaultIntMax 0x7FFF

void SystemBuilder::ExpressionFragments::pop(int32_t n)
{
    while (n--) pop();
}

SystemBuilder::SystemBuilder(TimedAutomataSystem *sys)
{
    system = sys;
    strict_range = false;
    currentFun = NULL;

    guard = sync = update = -1;
    params = frame_t::createFrame();
    frame = system->getGlobals().frame;
};

void SystemBuilder::setErrorHandler(ErrorHandler *value)
{
    errorHandler = value;
}

void SystemBuilder::setPosition(const position_t &pos)
{
    position = pos;
}

/********************************************************************
 * Utility functions
 */

type_t SystemBuilder::getElementTypeOfArray(type_t type)
{
    while (type.getBase() == type_t::ARRAY)
	type = type.getSub();    
    return type;
}

/********************************************************************
 * Query functions (these are used by the lexical analyzer)
 */

// isType(name): true if name is registered in the symbol table as
// a named type (a.k.a. type name), e.g. "int" or "bool" or a user
// defined type. 
bool SystemBuilder::isType(const char* name) 
{
    symbol_t uid;
    if (!frame.resolve(name, uid))
	return false;
    return uid.getType().getBase() == type_t::NTYPE;
}

bool SystemBuilder::isLocation(const char *name)
{
    symbol_t uid;
    if (!frame.resolve(name, uid))
	return false;
    return uid.getType() == type_t::LOCATION;
}

/********************************************************************
 * Types
 */


// Given a type and dim constant expressions on the expression stack,
// this function constructs and returns an array type using the type
// as the base type and the expressions as the array size (or sizes in
// case it is a multidimensional array). The expressions are popped of
// the expression stack.
type_t SystemBuilder::buildArrayType(type_t type, uint32_t dim)
{
    uint32_t i = 0;
    try {
	Interpreter interpreter(system->getConstantValuation());
	for (; i < dim; i++) {
	    try {
		if (interpreter.evaluate(fragments[0]) < 1) 
		    errorHandler->handleError("Invalid array size");
	    } catch (InterpreterException) {
		// Array dimension is not computable, i.e. it depends
		// on a parameter: We ignore it here.
	    }
	    type = type_t::createArray(fragments[0], type).setPrefix(
		type.hasPrefix(prefix::CONSTANT), prefix::CONSTANT);
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
type_t SystemBuilder::applyPrefix(uint32_t prefix, type_t type)
{    
    type_t base = type.getBase();
    if (base == type_t::VOID_TYPE || base == type_t::CLOCK) {
	if (prefix == PREFIX_NONE)
	    return type;
    } else if (base == type_t::INT || base == type_t::ARRAY || base == type_t::RECORD) {
	switch (prefix) {
	case PREFIX_NONE:
	    return type;
	case PREFIX_CONST:
	    return type.setPrefix(true, prefix::CONSTANT);
	}
    } else if (base == type_t::CHANNEL) {
	switch (prefix) {
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

// Push a new type onto the type stack. This type might subsequently
// be used to declare e.g. variables. If range is true, then we expect
// two constant expressions on the expression stack encoding the
// beginning and end of the range. These fragments will be popped from
// the expression stack.
void SystemBuilder::declType(uint32_t prefix, const char* name, bool range)
{
    symbol_t uid;
    assert(frame.resolve(name, uid));
    frame.resolve(name, uid);
    assert(uid.getType().getBase() == type_t::NTYPE);

    type_t type = uid.getType().getSub();
    if (range) {
	try {
	    expression_t lower = fragments[1];
	    expression_t upper = fragments[0];
	    fragments.pop(2);

	    if (type != type_t::INT)
		throw TypeException("Range is only valid with integer types");

	    try {
		Interpreter interpreter(system->getConstantValuation());
		int32_t l = interpreter.evaluate(lower);
		int32_t u = interpreter.evaluate(upper);
	    
		// Check if this is a valid range. In fact, equality
		// would also be rather useless, but it is
		// semantically well defined.
		if (l > u) 
		    errorHandler->handleError("Invalid integer range");
	    } catch (InterpreterException) {
		// Range depends on parameter: ignore it
	    }

	    type = type_t::createInteger(lower, upper);
	} catch (TypeException &e) {
	    errorHandler->handleError(e.what());
	}
    }
    typeFragments.push(applyPrefix(prefix, type));
}

// Used to construct a new struct type, which is then pushed onto
// the type stack. The type is based on n fields, which are expected
// to be on and will be popped off the type stack.
void SystemBuilder::declStruct(uint32_t prefix, uint32_t n)
{
    // Compute new type (each field has a singular record type)
    frame_t frame = frame_t::createFrame();
    for (int32_t i = n - 1; i >= 0; i--) {
	frame.addSymbol(typeFragments[i].second, typeFragments[0].first);
    }

    // Pop fragments
    while (n--) typeFragments.pop();

    typeFragments.push(applyPrefix(prefix, type_t::createRecord(frame)));
}

// Used to declare the fields of a structure. The type of the field is
// expected to be on the type fragment stack, and dim constant
// expressions are expected on the expression stack (in case of an
// array field). These will be popped of the stack.
void SystemBuilder::declField(const char* name, uint32_t dim) 
{
    type_t type = typeFragments[0].first;

    // Constant fields are not allowed
    if (type.hasPrefix(prefix::CONSTANT)) 
	throw TypeException("Constant fields not allowed in struct");

    // If no range was specified, use default range
    if (type.getBase() == type_t::INT && type.getRange().first.empty())
    {
	type = type_t::createInteger(
	    expression_t::createConstant(position_t(), defaultIntMin), 
	    expression_t::createConstant(position_t(), defaultIntMax));
    }

    // Construct array type
    type = buildArrayType(type, dim);

    // Check that all array sizes are computable and find base type
    type_t basetype = type;
    Interpreter interpreter(system->getConstantValuation());
    while (basetype.getBase() == type_t::ARRAY) {
	try {
	    interpreter.evaluate(basetype.getArraySize());
	} catch (InterpreterException) {
	    errorHandler->handleError("Parameterized array size is not allowed in structs");
	}
	basetype = basetype.getSub();
    }
    
    // Check base type
    if (basetype != type_t::INT && basetype != type_t::RECORD)
	throw TypeException("Invalid type in structure");

    // Copy type for next field
    typeFragments.push(typeFragments[0].first);

    // Set type and name of original type fragment 
    typeFragments[1].first = type;
    typeFragments[1].second = strdup(name);
}

// The end of a number of field declarations of the same type. The
// type must be popped of the type fragment stack.
void SystemBuilder::declFieldEnd() 
{
    typeFragments.pop();
}

// The type definition. Assign the name to the given type on the
// type fragment stack. In case of array types, dim constant expressions
// are expected on and popped from the expression stack.
void SystemBuilder::declTypeDef(const char* name, uint32_t dim) 
{
    type_t type = buildArrayType(typeFragments[0].first, dim);
    frame.addSymbol(name, type_t::createTypeName(type));
}

// End of type definition. Pop type of type stack.
void SystemBuilder::declTypeDefEnd() 
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
void SystemBuilder::declVar(const char* name, uint32_t dim, bool hasInit) 
{
    // Pop initial value
    expression_t init;
    if (hasInit) {
	init = fragments[0];
	fragments.pop();
    }

    // Construct type
    type_t type = typeFragments[0].first;
    if (!type.hasPrefix(prefix::CONSTANT)
	&& type.getBase() == type_t::INT
	&& type.getRange().first.empty())
    {
	type = type_t::createInteger(
	    expression_t::createConstant(position_t(), defaultIntMin), 
	    expression_t::createConstant(position_t(), defaultIntMax));
    }
    type = buildArrayType(type, dim);

    // Check whether initialiser is allowed/required
    type_t base = getElementTypeOfArray(type).getBase();
    if (base == type_t::CLOCK) {
	if (hasInit)
	    errorHandler->handleError("Clocks cannot have initialisers");
    } else if (base == type_t::RECORD || base == type_t::INT) {
	if (type.hasPrefix(prefix::CONSTANT) && !hasInit) {
		errorHandler->handleError("Constants must have an initialiser");
	}
    } else if (base == type_t::CHANNEL) {
	if (hasInit)
	    errorHandler->handleError("Channels cannot have initialisers");
    } else {
	errorHandler->handleError("Cannot declare variable of this type");
	return;
    }

    // Add variable to system
    system->addVariable(type, name, init);
} 

// At the end of a variable declaration, this method is called in
// order to pop the type from the type stack.
void SystemBuilder::declVarEnd() 
{
    typeFragments.pop(); 
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

void SystemBuilder::declFieldInit(const char *name)
{
    type_t type = fragments[0].getType();
    frame_t frame = frame_t::createFrame();
    frame.addSymbol(name, type);
    fragments[0].setType(type_t::createRecord(frame));
}

void SystemBuilder::declInitialiserList(uint32_t num)
{
    // Pop fields
    vector<expression_t> fields;
    for (int i = num - 1; i >= 0; i--)
	fields.push_back(fragments[i]);
    fragments.pop(num);
    
    // Compute new type (each fragment has a singular record type)
    frame_t frame = frame_t::createFrame();
    for (uint32_t i = 0; i < num; i++) {
	symbol_t field = fields[i].getType().getFrame()[0];
	frame.addSymbol(field.getName(), field.getType());
	fields[i].setType(field.getType()); // Restore type of field expr
    }

    // Create list expression
    fragments.push(expression_t::createNary(
	position, LIST, fields, type_t::createRecord(frame)));
}
  
/********************************************************************
 * Function declarations
 */
void SystemBuilder::declParameter(const char* name, bool ref, uint32_t dim)
{
    type_t type = typeFragments[0].first;

    // For compatibility with C and C++, array parameters are always
    // reference parameters. Putting an explicit ampersand in the
    // declaration is invalid (at least according to gcc).
    if (type.getBase() == type_t::ARRAY || dim > 0) {
	if (ref)
	    errorHandler->handleError("declaration of array of references");
	ref = true;
    }

    // Non-constant non-reference integer parameters without a range
    // use the default range of a 16 bit signed integer.
    if (!ref && !type.hasPrefix(prefix::CONSTANT)
	&& type.getBase() == type_t::INT
	&& type.getRange().first.empty())
    {
	type = type_t::createInteger(
	    expression_t::createConstant(position_t(), defaultIntMin), 
	    expression_t::createConstant(position_t(), defaultIntMax));
    }

    // Popup array dimensions of expression stack and construct array type
    type = buildArrayType(type, dim);

    // Append parameter to list of parameters
    params.addSymbol(name, type.setPrefix(ref, prefix::REFERENCE));
    
    // In case it is not a reference parameter, make sure we are not
    // dealing with channels or clocks (as these must be reference
    // parameters!).
    if (!ref) {
	type_t base = getElementTypeOfArray(type).getBase();
	if (base == type_t::CHANNEL || base == type_t::CLOCK) {
	    throw TypeException("Value parameters of this type are not allowed");
	}
    }
}

// 1 type, dim array sizes
void SystemBuilder::declParameterEnd() 
{
    typeFragments.pop(); // pop parameter type
}

void SystemBuilder::declFuncBegin(const char* name, uint32_t n) 
{
    try {
	assert(currentFun == NULL);
	type_t result = typeFragments[0].first;
	typeFragments.pop(); // pop function result type
    
	type_t type = type_t::createFunction(params, result);
	currentFun = &(system->addFunction(type, name));
	// TODO: What do we do in case of duplicate declarations?

	// Notice: This adds an extra nested block inside the function,
	// but this does not change the semantics so that is ok.
	frame = frame_t::createFrame(frame);
	currentFun->body = new BlockStatement(frame);
	blocks.push_back(currentFun->body);

	// Add function parameters to the frame
	frame.add(params);
    } catch (TypeException &e) {
	errorHandler->handleError(e.what());
    }

    // Clear parameter frame
    params = frame_t::createFrame();
}

void SystemBuilder::declFuncEnd() 
{ 
    assert(!blocks.empty());

    if (blocks.size() > 1) { // we are recovering from unfinished blocks
	// normaly all block statements must be closed and removed from stack
	do {
	    BlockStatement *block = blocks.back();
	    blocks.pop_back();
	    if (blocks.size() > 1)
		blocks.back()->push_stat(block);
	    else
		break;
	} while (true);	
    }

    if (currentFun != NULL) {
	currentFun->body = blocks.back();
	blocks.pop_back();

	frame = frame.getParent();
	currentFun = NULL;
    } else {
	// something was wrong with fn declaration, we ignore
	blocks.pop_back();
    }
}

/********************************************************************
 * Process declarations
 */
void SystemBuilder::procBegin(const char* name, uint32_t n)
{
    assert(params.getSize() == n);
    if (frame.getIndexOf(name) != -1) 
	errorHandler->handleError("Identifier defined multiple times");
    frame = system->addTemplate(name, params).frame;
    params = frame_t::createFrame();
}
    
void SystemBuilder::procEnd() // 1 ProcBody
{
    template_t &templ = system->getCurrentTemplate();
    system->setCurrentTemplate(system->getGlobals());
    frame = frame.getParent();
    if (templ.init == symbol_t())
	errorHandler->handleError("Missing initial state");
}

// Add a state to the current template. An invariant expression is
// expected on and popped from the expression stack.
void SystemBuilder::procState(const char* name, bool hasInvariant) // 1 expr
{
    expression_t e;
    if (hasInvariant) {
	e = fragments[0];
	fragments.pop();
    }
    system->addLocation(name, e);
}
    
void SystemBuilder::procStateCommit(const char* name) 
{
    symbol_t uid;
    if (!frame.resolve(name, uid)
	|| uid.getType().getBase() != type_t::LOCATION)
    {
	errorHandler->handleError("Location expected here");
    } else if (uid.getType().hasPrefix(prefix::URGENT)) {
	errorHandler->handleError("States cannot be committed and urgent at the same time.");
    } else {
	uid.setType(uid.getType().setPrefix(true, prefix::COMMITTED));
    }
}

void SystemBuilder::procStateUrgent(const char* name) 
{
    symbol_t uid;

    if (!frame.resolve(name, uid)
	|| uid.getType().getBase() != type_t::LOCATION)
    {
	errorHandler->handleError("Location expected here");
    } else if (uid.getType().hasPrefix(prefix::COMMITTED)) {
	errorHandler->handleError("States cannot be committed and urgent at the same time.");
    } else {
	uid.setType(uid.getType().setPrefix(true, prefix::URGENT));
    }
}

void SystemBuilder::procStateInit(const char* name) 
{
    symbol_t uid;
    if (!frame.resolve(name, uid)
	|| uid.getType().getBase() != type_t::LOCATION)
    {
	throw TypeException("Location expected here");
    }
    system->getCurrentTemplate().init = uid;
}
    
void SystemBuilder::procTransition(const char* from, const char* to)
{
    symbol_t fid, tid;

    if (!frame.resolve(from, fid)
	|| fid.getType().getBase() != type_t::LOCATION)
    {
	throw TypeException("No such location (source)");
    }

    if (!frame.resolve(to, tid)
	|| tid.getType().getBase() != type_t::LOCATION)
    {
	throw TypeException("No such location (destination)");
    }

    // Complete labels
    if (update == -1) {
	exprTrue();
	procUpdate();
    }

    if (guard == -1) {
	exprTrue();
	procGuard();
    }
    
    // Create transition
    transition_t &tran = system->addTransition(fid, tid);
    tran.assign = fragments[fragments.size() - update];
    if (sync != -1)
	tran.sync = fragments[fragments.size() - sync];
    tran.guard = fragments[fragments.size() - guard];
    fragments.pop(sync == -1 ? 2 : 3);

    guard = sync = update = -1;
}

void SystemBuilder::procGuard()
{
    guard = fragments.size();
}

void SystemBuilder::procSync(synchronisation_t type)
{
    expression_t expr = fragments[0];
    if (expr.getType().getBase() != type_t::CHANNEL)
	throw TypeException("No such channel");
    
    fragments[0] = expression_t::createSync(position, expr, type);
    sync = fragments.size();
}

void SystemBuilder::procUpdate()
{
    update = fragments.size();
}

/*********************************************************************
 * Statements
 */
void SystemBuilder::blockBegin() 
{
    frame = frame.createFrame(frame);
    blocks.push_back(new BlockStatement(frame));
}

void SystemBuilder::blockEnd() 
{
    BlockStatement *block = blocks.back();
    blocks.pop_back();
    if (!blocks.empty()) { // if this was inner block
	blocks.back()->setRetDefined(
	    blocks.back()->retDefined() || // mark dead code
	    block->retDefined());
	blocks.back()->push_stat(block);
    }
    frame = frame.getParent();
}

void SystemBuilder::emptyStatement() 
{
    blocks.back()->push_stat(new EmptyStatement(blocks.back()->getFrame()));
}

void SystemBuilder::forBegin() 
{
//    addStatement(blocks.back(), new ForStatement(blocks.back()->frameId));
}

void SystemBuilder::forEnd() 
{ // 3 expr, 1 stat
    Statement* substat = blocks.back()->pop_stat();
    ForStatement* forstat = new ForStatement(blocks.back()->getFrame(), 
					     fragments[2], fragments[1], 
					     fragments[0], substat);
    forstat->setRetDefined(substat->retDefined());
    blocks.back()->push_stat(forstat);

    fragments.pop();
    fragments.pop();
    fragments.pop();
}

void SystemBuilder::whileBegin() 
{
}

void SystemBuilder::whileEnd() 
{ // 1 expr, 1 stat
    Statement* substat = blocks.back()->pop_stat();
    WhileStatement* whilestat = new WhileStatement(blocks.back()->getFrame(),
						   fragments[0], substat);
    whilestat->setRetDefined(substat->retDefined());
    blocks.back()->push_stat(whilestat);

    fragments.pop();
}

void SystemBuilder::doWhileBegin()
{
}

void SystemBuilder::doWhileEnd()
{ // 1 stat, 1 expr
    Statement* substat = blocks.back()->pop_stat();
    blocks.back()->push_stat(
	new DoWhileStatement(blocks.back()->getFrame(), substat, fragments[0]));
    fragments.pop();
}

void SystemBuilder::ifBegin()
{
}

void SystemBuilder::ifElse()
{
}

void SystemBuilder::ifEnd(bool elsePart)
{ // 1 expr, 1 or 2 statements
    Statement *falseCase = NULL;
    if (elsePart) falseCase = blocks.back()->pop_stat();

    Statement *trueCase = blocks.back()->pop_stat();

    IfStatement *ifstat = new IfStatement(blocks.back()->getFrame(), 
					  fragments[0], trueCase, falseCase);

    if (elsePart) ifstat->setRetDefined(trueCase->retDefined() && 
					falseCase->retDefined());

    blocks.back()->push_stat(ifstat);

    fragments.pop();
}

void SystemBuilder::breakStatement()
{
    blocks.back()->push_stat(new BreakStatement(blocks.back()->getFrame()));
}

void SystemBuilder::continueStatement()
{
    blocks.back()->push_stat(new ContinueStatement(blocks.back()->getFrame()));
}

void SystemBuilder::switchBegin()
{ // 1 expr
    frame = frame_t::createFrame();
    blocks.push_back(new SwitchStatement(frame, fragments[0]));
    fragments.pop();
}
void SystemBuilder::switchEnd()
{ // 1+ case/default
    BlockStatement *block = blocks.back();
    blocks.pop_back();
    blocks.back()->push_stat(block);
    frame = frame.getParent();
}

void SystemBuilder::caseBegin() 
{ // 1 expr
    blocks.push_back(new CaseStatement(frame, fragments[0]));
    fragments.pop();
}

void SystemBuilder::caseEnd()
{ // 0+ stat
    BlockStatement *block = blocks.back();
    blocks.pop_back();
    blocks.back()->push_stat(block);
}

void SystemBuilder::defaultBegin() 
{    
    blocks.push_back(new DefaultStatement(frame));
}

void SystemBuilder::defaultEnd() 
{ // 0+ statements
    BlockStatement *block = blocks.back();
    blocks.pop_back();    
    blocks.back()->push_stat(block);
}

void SystemBuilder::exprStatement() 
{ // 1 expr
    blocks.back()->push_stat(new ExprStatement(blocks.back()->getFrame(), 
					       fragments[0]));
    fragments.pop();
}

void SystemBuilder::returnStatement(bool args) 
{ // 1 expr if argument is true
    assert(currentFun != NULL);
    type_t result = currentFun->uid.getType().getSub();
    type_t base = result.getBase();
    
    if (!args) {
	if (base != type_t::VOID_TYPE)
	    throw TypeException("non-void function must return a value");
	ReturnStatement* stat = new ReturnStatement(blocks.back()->getFrame());
	blocks.back()->push_stat(stat);
	blocks.back()->setRetDefined(true);
	return;
    }
    
    type_t type = fragments[0].getType();
    ReturnStatement* retstat = new ReturnStatement(blocks.back()->getFrame(), 
						   fragments[0]);
    fragments.pop();
    blocks.back()->push_stat(retstat);
    blocks.back()->setRetDefined(true);

    if (base == type_t::VOID_TYPE)
	throw TypeException("void function does not return any value");
}

/********************************************************************
 * Expressions
 */
void SystemBuilder::exprTrue() 
{
    fragments.push(makeConstant(1));
}

void SystemBuilder::exprFalse() 
{
    fragments.push(makeConstant(0));
}
    
void SystemBuilder::exprId(const char *name) 
{
    symbol_t uid;

    if (!frame.resolve(name, uid)) {
	fragments.push(expression_t::createIdentifier(position, symbol_t()));
	throw TypeException("%s: Unknown identifier", name);
    }

    fragments.push(expression_t::createIdentifier(position, uid));

    type_t base = uid.getType().getBase();

    if (base == type_t::PROCESS && !allowProcessReferences())
	throw TypeException("Process references are not allowed");

    if (base != type_t::INT
	&& base != type_t::ARRAY
	&& base != type_t::CLOCK
	&& base != type_t::CHANNEL
	&& base != type_t::RECORD
	&& base != type_t::PROCESS)
    {
	throw TypeException("Identifier of this type cannot be referenced in an expression");
    }    
}

expression_t SystemBuilder::makeConstant(int value)
{
    return expression_t::createConstant(position, value);
}
    
void SystemBuilder::exprDeadlock()
{
    fragments.push(expression_t::createDeadlock(position));
}

void SystemBuilder::exprNat(int32_t n) 
{
    fragments.push(makeConstant(n));
}

void SystemBuilder::exprCallBegin(const char *functionName) 
{
    expectedArguments.push_back(vector<type_t>());
    identifierStack.push_back(symbol_t());

    if (!frame.resolve(functionName, identifierStack.back())) 
	throw TypeException("function '%s' not declared", functionName);

    symbol_t id = identifierStack.back();
    
    if (id.getType().getBase() != type_t::FUNCTION)
	throw TypeException("Not a function: %s", functionName);
    
    if (currentFun != NULL && currentFun->uid == id)
	throw TypeException("recursion is not allowed", functionName);

    frame_t params = id.getType().getParameters();
    for (int i = params.getSize() - 1; i >= 0; i--)
	expectedArguments.back().push_back(params[i].getType());
}

// expects n argument expressions on the stack
void SystemBuilder::exprCallEnd(uint32_t n) 
{
    symbol_t id = identifierStack.back();
    identifierStack.pop_back();

    if (!expectedArguments.back().empty())
	errorHandler->handleError("Too few arguments");

    expectedArguments.pop_back();
    
    if (id == symbol_t())
	return;
    
    type_t result = id.getType().getSub();

    // Create vector of sub expressions: The first sub expression
    // evaluates to the function. The remaining sub expressions
    // are the arguments.
    vector<expression_t> sub;
    sub.push_back(expression_t::createIdentifier(position_t(), id));

    // Pop arguments
    for (int i = n - 1; i >= 0; i--)
	sub.push_back(fragments[i]);
    fragments.pop(n);

    // Push FUNCALL expression
    fragments.push(expression_t::createNary(position, FUNCALL, sub, result));
}

// expects 1 expression on the stack
void SystemBuilder::exprArg(uint32_t n) 
{
    if (expectedArguments.back().empty())
	throw TypeException("Too many arguments");
    expectedArguments.back().pop_back();
}

// 2 expr     // array[index]
void SystemBuilder::exprArray() 
{
    // Pop sub-expressions
    expression_t var = fragments[1];
    expression_t index = fragments[0];
    fragments.pop(2);

    type_t element;
    type_t type = var.getType();
    if (type.getBase() == type_t::ARRAY) {
	element = type.getSub();
    } else {
	element = type_t::UNKNOWN;
	errorHandler->handleError("Array expected here");
    }

    fragments.push(expression_t::createBinary(
	position, ARRAY, var, index, element));
}

// 1 expr
void SystemBuilder::exprPostIncrement() 
{
    fragments[0] = expression_t::createUnary(
	position, POSTINCREMENT, fragments[0], fragments[0].getType());
}
    
void SystemBuilder::exprPreIncrement() 
{
    fragments[0] = expression_t::createUnary(
	position, PREINCREMENT, fragments[0], fragments[0].getType());
}
    
void SystemBuilder::exprPostDecrement() // 1 expr
{
    fragments[0] = expression_t::createUnary(
	position, POSTDECREMENT, fragments[0], fragments[0].getType());
}
    
void SystemBuilder::exprPreDecrement() 
{
    fragments[0] = expression_t::createUnary(
	position, PREDECREMENT, fragments[0], fragments[0].getType());
}
    
void SystemBuilder::exprAssignment(kind_t op) // 2 expr
{
    expression_t lvalue = fragments[1];
    expression_t rvalue = fragments[0];
    fragments.pop(2);
    fragments.push(expression_t::createBinary(
	position, op, lvalue, rvalue, lvalue.getType()));
}

void SystemBuilder::exprUnary(kind_t unaryop) // 1 expr
{
    if (unaryop == MINUS)
	unaryop = UNARY_MINUS;
    fragments[0] = expression_t::createUnary(position, unaryop, fragments[0]);
}
    
void SystemBuilder::exprBinary(kind_t binaryop) // 2 expr
{
    expression_t left = fragments[1];
    expression_t right = fragments[0];
    fragments.pop(2);
    fragments.push(expression_t::createBinary(
	position, binaryop, left, right));
}

void SystemBuilder::exprInlineIf()
{
    expression_t c = fragments[2];
    expression_t t = fragments[1];
    expression_t e = fragments[0];
    fragments.pop(3);
    fragments.push(expression_t::createTernary(
	position, INLINEIF, c, t, e, t.getType()));    
}

void SystemBuilder::exprComma()
{
    expression_t e1 = fragments[1];
    expression_t e2 = fragments[0];
    fragments.pop(2);
    fragments.push(expression_t::createBinary(
	position, COMMA, e1, e2, e2.getType()));
}

void SystemBuilder::exprDot(const char *id)
{
    expression_t expr = fragments[0];
    type_t type = expr.getType();
    if (type.getBase() == type_t::RECORD || type.getBase() == type_t::PROCESS)
    {
	frame_t fields = type.getFrame();
	int i = fields.getIndexOf(id);
	if (i == -1) {
	    errorHandler->handleError("Structure has no such member");
	    expr = expression_t::createDot(position, expr);
	} else if (fields[i].getType().getBase() == type_t::LOCATION) {
	    expr = expression_t::createDot(position, expr, i, type_t::INT);
	} else {
	    expr = expression_t::createDot(position, expr,
					   i, fields[i].getType());
	}
    } else {
	expr = expression_t::createDot(position, expr);
	errorHandler->handleError("This is not a structure");
    }
    fragments[0] = expr;
}
    
/********************************************************************
 * System declaration
 */

// Prepares for the instantiations of a process
void SystemBuilder::instantiationBegin(const char* name, const char* templ_name)
{
    expectedArguments.push_back(vector<type_t>());
    identifierStack.push_back(symbol_t());

    if (!frame.resolve(templ_name, identifierStack.back()))
	throw TypeException("Unknown identifier");

    symbol_t id = identifierStack.back();
    
    if (id.getType().getBase() != type_t::TEMPLATE) 
	throw TypeException("Not a template: %s", templ_name);

    frame_t params = id.getType().getParameters();
    for (int i = params.getSize() - 1; i >= 0; i--)
	expectedArguments.back().push_back(params[i].getType());
}

void SystemBuilder::instantiationEnd(const char *name, const char *templ_name, uint32_t n)
{
    symbol_t id = identifierStack.back();
    identifierStack.pop_back();

    if (!expectedArguments.back().empty())
	errorHandler->handleError("Too few arguments");

    expectedArguments.pop_back();

    if (id == symbol_t())
	return;
	
    try {
	frame_t parameters = id.getType().getParameters();

	// If two many arguments, pop the rest
	if (n > parameters.getSize()) {
	    fragments.pop(n - parameters.getSize());
	    n = parameters.getSize();
	}

	// Create template composition
	template_t *templ = static_cast<template_t*>(id.getData());
	instance_t &instance = system->addInstance(name, templ);
	
	while (n--) {
	    symbol_t param = templ->frame[n];
	    instance.mapping[param] = fragments[0];
	    fragments.pop();
	}
    } catch (const TypeException e) {
	// remember to pop off the arguments if something is wrong
	fragments.pop(n);
	errorHandler->handleError(e.what());
    }
}
    
// Adds process_t* pointer to system_line
// Checks for dublicate entries
void SystemBuilder::process(const char* name)
{
    symbol_t sym;
    if (!frame.resolve(name, sym))
	throw TypeException("No such template: %s", name);
    system->addProcess(sym);
}
    
void SystemBuilder::done()
{

}

void SystemBuilder::property(kind_t kind, int line)
{
    if (kind == LEADSTO) {
	expression_t left = fragments[1];
	expression_t right = fragments[0];
	fragments.pop(2);
	fragments.push(expression_t::createBinary(
	    position, LEADSTO, left, right));
    }
    property(kind, line, fragments[0]);
    fragments.pop();
}

void SystemBuilder::beforeUpdate()
{

}

void SystemBuilder::afterUpdate()
{

}

// bool parseXTA(FILE *file, ErrorHandler *error, TimedAutomataSystem *system, bool newxta)
// {
//     SystemBuilder builder(system);
//     parseXTA(file, &builder, error, newxta);
//     return !error->hasErrors();
// }

// bool parseXTA(const char *buffer, ErrorHandler *error, TimedAutomataSystem *system, bool newxta)
// {
//     SystemBuilder builder(system);
//     parseXTA(buffer, &builder, error, newxta);
//     return !error->hasErrors();
// }

// bool parseXMLBuffer(const char *buffer, ErrorHandler *error, TimedAutomataSystem *system, bool newxta)
// {
//     SystemBuilder builder(system);
//     parseXMLBuffer(buffer, &builder, error, newxta);
//     return !error->hasErrors();
// }

// bool parseXMLFile(const char *file, ErrorHandler *error, TimedAutomataSystem *system, bool newxta)
// {
//     SystemBuilder builder(system);
//     parseXMLFile(file, &builder, error, newxta);
//     return !error->hasErrors();
// }
