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

#include "utap/systembuilder.h"
#include "utap/collectchangesvisitor.h"

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

SystemBuilder::SystemBuilder(TimedAutomataSystem *system)
    : ExpressionBuilder(system)
{
    strict_range = false;
    currentFun = NULL;
    currentTemplate = NULL;

    guard = sync = update = -1;
    params = frame_t::createFrame();
};

/********************************************************************
 * Utility functions
 */

type_t SystemBuilder::getElementTypeOfArray(type_t type)
{
    while (type.getBase() == type_t::ARRAY)
	type = type.getSub();    
    return type;
}

/**
 * Given a type and dim constant expressions on the expression stack,
 * this function constructs and returns an array type using the type
 * as the base type and the expressions as the array size (or sizes in
 * case it is a multidimensional array). The expressions are popped of
 * the expression stack.
 */
type_t SystemBuilder::buildArrayType(type_t type, uint32_t dim)
{
    for (uint32_t i = 0; i < dim; i++) 
    {
	type = type_t::createArray(fragments[0], type).setPrefix(
	    type.hasPrefix(prefix::CONSTANT), prefix::CONSTANT);
	fragments.pop();
    }
    return type;
}

/**
 * Given a prefix and a type, this method creates a new type by
 * applying the prefix. TypeExceptions might be thrown if the
 * combination of the prefix and the type is illegal.
 */
type_t SystemBuilder::applyPrefix(int32_t prefix, type_t type)
{    
    type_t base = type.getBase();
    if (base == type_t::VOID_TYPE || base == type_t::CLOCK) 
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
void SystemBuilder::typeName(int32_t prefix, const char* name, int range)
{
    symbol_t uid;
    assert(frame.resolve(name, uid));

    if (!frame.resolve(name, uid) || uid.getType().getBase() != type_t::NTYPE)
    {
	typeFragments.push(type_t::VOID_TYPE);
	throw TypeException("Identifier is undeclared or not a type name");
    }

    type_t type = uid.getType().getSub();
    if (range) 
    {
	if (type == type_t::INT && range == 2)
	{
	    type = type_t::createInteger(fragments[1], fragments[0]);
	}
	else
	{
	    errorHandler->handleError("Invalid number of arguments for this type.");
	}
	fragments.pop(range);
    }
    typeFragments.push(applyPrefix(prefix, type));
}

/**
 * Used to construct a new struct type, which is then pushed onto the
 * type stack. The type is based on n fields, which are expected to be
 * on and will be popped off the type stack.
 */
void SystemBuilder::typeStruct(int32_t prefix, uint32_t n)
{
    // Compute new type (each field has a singular record type)
    frame_t frame = frame_t::createFrame();
    for (int32_t i = n - 1; i >= 0; i--) 
    {
	frame.addSymbol(typeFragments[i].second, typeFragments[0].first);
    }

    // Pop fragments
    while (n--) typeFragments.pop();

    typeFragments.push(applyPrefix(prefix, type_t::createRecord(frame)));
}

/**
 * Used to declare the fields of a structure. The type of the field is
 * expected to be on the type fragment stack, and dim constant
 * expressions are expected on the expression stack (in case of an
 * array field). These will be popped of the stack.
 */
void SystemBuilder::structField(const char* name, uint32_t dim) 
{
    type_t type = typeFragments[0].first;

    // Constant fields are not allowed
    if (type.hasPrefix(prefix::CONSTANT)) 
    {
	throw TypeException("Constant fields not allowed in struct");
    }

    // If no range was specified, use default range
    if (type.getBase() == type_t::INT && type.getRange().first.empty())
    {
	type = type_t::createInteger(
	    expression_t::createConstant(position_t(), defaultIntMin), 
	    expression_t::createConstant(position_t(), defaultIntMax));
    }

    // Construct array type
    type = buildArrayType(type, dim);

    // Copy type for next field
    typeFragments.push(typeFragments[0].first);

    // Set type and name of original type fragment 
    typeFragments[1].first = type;
    typeFragments[1].second = strdup(name);

    /* Check the base type. We should check this in the type
     * checker. The problem is that we do not maintain the position of
     * types, hence we cannot place the error message if we wait until
     * the type check phase.
     */
    type_t base = type.getBase();
    while (base == type_t::ARRAY)
    {
	type = type.getSub();
	base = type.getBase();
    }
    if (base != type_t::BOOL && base != type_t::INT && base != type_t::RECORD)
    {
	throw TypeException("Invalid type in structure");
    }
}

/**
 * The end of a number of field declarations of the same type. The
 * type must be popped of the type fragment stack.
 */
void SystemBuilder::structFieldEnd() 
{
    typeFragments.pop();
}

/**
 * A type definition. Assign the name to the given type on the type
 * fragment stack. In case of array types, dim constant expressions
 * are expected on and popped from the expression stack.
 */
void SystemBuilder::declTypeDef(const char* name, uint32_t dim) 
{
    type_t type = buildArrayType(typeFragments[0].first, dim);
    frame.addSymbol(name, type_t::createTypeName(type));
}

/**
 * End of type definition. Pop type of type stack.
 */
void SystemBuilder::declTypeDefEnd() 
{
    typeFragments.pop();
}

/**
 * Declare a new variable of the given name. The type is expected to
 * be on the type stack. In case of an array, dim constant expressions
 * are expected on the expression stack. If the variable has an
 * initialiser (the init parameter is true), then an additional
 * constant expression is expected at the top of the expression stack.
 * The expressions will be popped of the stack (the type is left
 * untouched).
 */
void SystemBuilder::declVar(const char* name, uint32_t dim, bool hasInit) 
{
    // Pop initial value
    expression_t init;
    if (hasInit) 
    {
	init = fragments[0];
	fragments.pop();
    }

    // Construct type
    type_t type = typeFragments[0].first;
    if (type.getBase() == type_t::INT)
    {
	if (!type.hasPrefix(prefix::CONSTANT) && type.getRange().first.empty())
	{
	    type = type_t::createInteger(
		expression_t::createConstant(position_t(), defaultIntMin), 
		expression_t::createConstant(position_t(), defaultIntMax));
	}
	else if (type.hasPrefix(prefix::CONSTANT) 
		 && !type.getRange().first.empty())
	{
	    errorHandler->handleError("Constant must not have a range specification");
	    type = type_t::INT.setPrefix(true, prefix::CONSTANT);
	}
    }
    type = buildArrayType(type, dim);

    // Check whether initialiser is allowed/required
    type_t base = getElementTypeOfArray(type).getBase();
    if (base == type_t::CLOCK) 
    {
	if (currentFun)
	{
	    errorHandler->handleError("Clock declarations are not allowed inside functions");
	}
	if (hasInit)
	{
	    errorHandler->handleError("Clocks cannot have initialisers");
	}
    } 
    else if (base == type_t::RECORD || base == type_t::INT
	       || base == type_t::BOOL)
    {
	if (type.hasPrefix(prefix::CONSTANT) && !hasInit) 
	{
		errorHandler->handleError("Constants must have an initialiser");
	}
    } 
    else if (base == type_t::CHANNEL) 
    {
	if (hasInit)
	{
	    errorHandler->handleError("Channels cannot have initialisers");
	}
    } 
    else 
    {
	errorHandler->handleError("Cannot declare variable of this type");
	return;
    }

    // Add variable to system
    system->addVariable(type, name, init);
} 

/**
 * At the end of a variable declaration, this method is called in
 * order to pop the type from the type stack.
 */
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
    vector<expression_t> fields(num);
    for (uint32_t i = 0; i < num; i++)
    {
	fields[i] = fragments[num - 1 - i];
    }
    fragments.pop(num);
    
    // Compute new type (each fragment has a singular record type)
    frame_t frame = frame_t::createFrame();
    for (uint32_t i = 0; i < num; i++) 
    {
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
    if (type.getBase() == type_t::ARRAY || dim > 0) 
    {
	if (ref)
	{
	    errorHandler->handleError("declaration of array of references");
	}
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
    if (!ref) 
    {
	type_t base = getElementTypeOfArray(type).getBase();
	if (base == type_t::CHANNEL || base == type_t::CLOCK) 
	{
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
    assert(currentFun == NULL);
    type_t result = typeFragments[0].first;
    typeFragments.pop(); // pop function result type
    
    type_t type = type_t::createFunction(params, result);
    if (!system->addFunction(type, name, currentFun))
    {
	errorHandler->handleError("Duplicate definition");
    }

    // Create new frame and add parameters; the new frame will
    // be made the current frame
    frame = frame_t::createFrame(frame);
    frame.add(params);
    params = frame_t::createFrame();

    // Create function block
    currentFun->body = new BlockStatement(frame);
    blocks.push_back(currentFun->body);

    system->setDeclarationBlock(currentFun->body);
}

void SystemBuilder::declFuncEnd() 
{ 
    assert(!blocks.empty());

    // Recover from unterminated blocks - delete any excess blocks 
    while (blocks.size() > 1) {
	delete blocks.back();
	blocks.pop_back();
    }

    // Pop outer function block
    blocks.pop_back();

    // Collect symbols which are changes by the function
    CollectChangesVisitor visitor(currentFun->changes);
    currentFun->body->accept(&visitor);    

    // Restore global frame
    frame = frame.getParent();

    // Reset current function pointer to NULL
    currentFun = NULL;

    // Restore current declaration block
    if (currentTemplate) 
    {
	system->setDeclarationBlock(currentTemplate);
    }
    else 
    {
	system->setDeclarationBlock(&system->getGlobals());
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
    currentTemplate = &system->addTemplate(name, params);
    frame = currentTemplate->frame;
    params = frame_t::createFrame();
}
    
void SystemBuilder::procEnd() // 1 ProcBody
{
    if (currentTemplate->init == symbol_t())
    {
	errorHandler->handleError("Missing initial state");
    }

    currentTemplate = NULL;
    system->setDeclarationBlock(&system->getGlobals());
    frame = frame.getParent();
}

// Add a state to the current template. An invariant expression is
// expected on and popped from the expression stack.
void SystemBuilder::procState(const char* name, bool hasInvariant) // 1 expr
{
    expression_t e;
    if (hasInvariant) 
    {
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
    } 
    else if (uid.getType().hasPrefix(prefix::URGENT)) 
    {
	errorHandler->handleError("States cannot be committed and urgent at the same time.");
    } 
    else 
    {
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
    } 
    else if (uid.getType().hasPrefix(prefix::COMMITTED)) 
    {
	errorHandler->handleError("States cannot be committed and urgent at the same time.");
    }
    else 
    {
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
    currentTemplate->init = uid;
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
    if (update == -1) 
    {
	exprTrue();
	procUpdate();
    }

    if (guard == -1) 
    {
	exprTrue();
	procGuard();
    }
    
    // Create transition
    transition_t &tran = system->addTransition(fid, tid);
    tran.assign = fragments[fragments.size() - update];
    if (sync != -1)
    {
	tran.sync = fragments[fragments.size() - sync];
    }
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
    {
	throw TypeException("No such channel");
    }
    
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
    // Append the block which is being terminated as a statement to
    // the containing block.
    BlockStatement *block = blocks.back();
    blocks.pop_back();
    blocks.back()->push_stat(block);

    // Restore containing frame
    frame = frame.getParent();
}

void SystemBuilder::emptyStatement() 
{
    blocks.back()->push_stat(new EmptyStatement());
}

void SystemBuilder::forBegin() 
{
//    addStatement(blocks.back(), new ForStatement(blocks.back()->frameId));
}

void SystemBuilder::forEnd() 
{ // 3 expr, 1 stat
    Statement* substat = blocks.back()->pop_stat();
    ForStatement* forstat = new ForStatement(fragments[2], fragments[1], 
					     fragments[0], substat);
    blocks.back()->push_stat(forstat);

    fragments.pop(3);
}

void SystemBuilder::whileBegin() 
{
}

void SystemBuilder::whileEnd() 
{ // 1 expr, 1 stat
    Statement* substat = blocks.back()->pop_stat();
    WhileStatement* whilestat = new WhileStatement(fragments[0], substat);
    blocks.back()->push_stat(whilestat);

    fragments.pop();
}

void SystemBuilder::doWhileBegin()
{
}

void SystemBuilder::doWhileEnd()
{ // 1 stat, 1 expr
    Statement* substat = blocks.back()->pop_stat();
    blocks.back()->push_stat(new DoWhileStatement(substat, fragments[0]));
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
    Statement *falseCase = (elsePart ? blocks.back()->pop_stat() : NULL);
    Statement *trueCase = blocks.back()->pop_stat();
    IfStatement *ifstat = new IfStatement(fragments[0], trueCase, falseCase);

    blocks.back()->push_stat(ifstat);

    fragments.pop();
}

void SystemBuilder::breakStatement()
{
    blocks.back()->push_stat(new BreakStatement());
}

void SystemBuilder::continueStatement()
{
    blocks.back()->push_stat(new ContinueStatement());
}

void SystemBuilder::switchBegin()
{ // 1 expr
    blocks.push_back(new SwitchStatement(frame, fragments[0]));
    fragments.pop();
}
void SystemBuilder::switchEnd()
{ // 1+ case/default
    BlockStatement *block = blocks.back();
    blocks.pop_back();
    blocks.back()->push_stat(block);
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
    blocks.back()->push_stat(new ExprStatement(fragments[0]));
    fragments.pop();
}

void SystemBuilder::returnStatement(bool args) 
{ // 1 expr if argument is true
    ReturnStatement* stat;
    if (args) 
    {
	stat = new ReturnStatement(fragments[0]);
	fragments.pop();
    }
    else 
    {
	stat = new ReturnStatement();
    }
    blocks.back()->push_stat(stat);
}

/********************************************************************
 * Expressions
 */

void SystemBuilder::exprCallBegin(const char *functionName) 
{
    ExpressionBuilder::exprCallBegin(functionName);

    /* Check for recursive function calls. We could move this to
     * the type checker.
     */
    symbol_t id;
    frame.resolve(functionName, id);
    if (currentFun != NULL && currentFun->uid == id)
    {
	throw TypeException("recursion is not allowed", functionName);
    }
}

/********************************************************************
 * System declaration
 */

// Prepares for the instantiations of a process
void SystemBuilder::instantiationBegin(const char* name, const char* templ_name)
{
    expectedArguments.push_back(0);
    identifierStack.push_back(symbol_t());

    symbol_t id;
    if (!frame.resolve(templ_name, id))
    {
	throw TypeException("Unknown identifier");
    }

    if (id.getType().getBase() != type_t::TEMPLATE) 
    {
	throw TypeException("Not a template: %s", templ_name);
    }

    identifierStack.back() = id;

    (expectedArguments.back() = id.getType().getParameters().getSize());
}

void SystemBuilder::instantiationEnd(const char *name, const char *templ_name, uint32_t n)
{
    symbol_t id = identifierStack.back();
    identifierStack.pop_back();

    if (n < expectedArguments.back())
    {
	errorHandler->handleError("Too few arguments");
    }

    expectedArguments.pop_back();

    if (id == symbol_t())
    {
 	// Push dummy expression to avoid stack corruption
 	fragments.push(expression_t::createConstant(position_t(), 0));
	return;
    }
	
    try 
    {
	frame_t parameters = id.getType().getParameters();

	// If two many arguments, pop the rest
	if (n > parameters.getSize()) 
	{
	    fragments.pop(n - parameters.getSize());
	    n = parameters.getSize();
	}

	// Create template composition
	template_t *templ = static_cast<template_t*>(id.getData());
	instance_t &instance = system->addInstance(name, templ);
	
	while (n--) 
	{
	    symbol_t param = templ->frame[n];
	    instance.mapping[param] = fragments[0];
	    fragments.pop();
	}
    } 
    catch (const TypeException e) 
    {
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
    {
	throw TypeException("No such template: %s", name);
    }
    system->addProcess(sym);
}
    
void SystemBuilder::done()
{

}

void SystemBuilder::property(kind_t kind, int line)
{
    if (kind == LEADSTO) 
    {
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

/********************************************************************
 * Priority
 */

void SystemBuilder::lowPriority(const char* name)
{
#ifdef ENABLE_PRIORITY
    currentPriority = 1;
    samePriority(name);
#else
    throw TypeException("Priority syntax disabled");
#endif
}

void SystemBuilder::samePriority(const char* name)
{
#ifdef ENABLE_PRIORITY
    symbol_t symbol;
    if (!frame.resolve(name, symbol))
    {
        throw TypeException("No such template: %s", name);
    }

    if (symbol.getType().getBase() == type_t::CHANNEL)
    {
        system->setChanPriority(symbol, currentPriority);
    }
    else
    {
        system->setProcPriority(symbol, currentPriority);
    }
#else
    throw TypeException("Priority syntax disabled");
#endif
}

void SystemBuilder::higherPriority(const char* name)
{
#ifdef ENABLE_PRIORITY
    ++currentPriority;
    samePriority(name);
#else
    throw TypeException("Priority syntax disabled");
#endif
}
