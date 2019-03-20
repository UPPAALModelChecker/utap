// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2002-2004 Uppsala University and Aalborg University.
   
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
#include <stdexcept>

#include "utap/systembuilder.h"

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

SystemBuilder::SystemBuilder(TimedAutomataSystem *system)
    : ExpressionBuilder(system)
{
    strict_range = false;
    currentFun = NULL;
    currentTemplate = NULL;

    params = frame_t::createFrame();
    templateset = frame_t::createFrame();
};

/********************************************************************
 * Utility functions
 */

type_t SystemBuilder::getElementTypeOfArray(type_t type)
{
    while (type.getBase() == type_t::ARRAY)
    {
	type = type.getSub(); 
    }
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
	type_t array = type_t::createArray(
	    type_t::createInteger(
		makeConstant(0), 
		expression_t::createBinary(fragments[0].getPosition(),
					   MINUS, fragments[0], 
					   makeConstant(1))), type);
	type = array.setPrefix(
	    type.hasPrefix(prefix::CONSTANT), prefix::CONSTANT).setPrefix(
		type.hasPrefix(prefix::META), prefix::META);
	fragments.pop();
    }
    return type;
}

declarations_t *SystemBuilder::getCurrentDeclarationBlock()
{
    return (currentTemplate ? currentTemplate : &system->getGlobals());
}

/**
 * Used to construct a new struct type, which is then pushed onto the
 * type stack. The type is based on n fields, which are expected to be
 * on and will be popped off the type stack.
 */
void SystemBuilder::typeStruct(int32_t prefix, uint32_t n)
{
    frame_t frame = frame_t::createFrame();
    for (int32_t i = n - 1; i >= 0; i--) 
    {
	frame.addSymbol(typeFragments[i].second, typeFragments[i].first);
    }

    // Pop fragments
    while (n--) 
    {
	typeFragments.pop();
    }

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
    if (!base.isRecord() && !base.isScalar() && !base.isValue())
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
    frames.top().addSymbol(name, type_t::createTypeName(type));
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
	if (type.hasPrefix(prefix::CONSTANT) 
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
    else if (base.isRecord() || base.isValue())
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
    else if (base == type_t::COST) 
    {
	if (hasInit)
	{
	    errorHandler->handleError("Costs cannot have initialisers");
	}
    } 
    else if (base == type_t::SCALAR)
    {
	if (hasInit)
	{
	    errorHandler->handleError("Scalars cannot yet have initialisers");
	}
    }
    else 
    {
	errorHandler->handleError("Cannot declare variable of this type");
	return;
    }

    // Add variable to system
    if (currentFun)
    {
	system->addVariableToFunction(currentFun, frames.top(), type, name, init);
    }
    else
    {
	system->addVariable(getCurrentDeclarationBlock(), type, name, init);
    }
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

/************************************************************
 * Guarded progress measure
 */
void SystemBuilder::declProgress(bool hasGuard)
{
    expression_t guard, measure;
    measure = fragments[0];
    fragments.pop();
    if (hasGuard)
    {
	guard = fragments[0];
	fragments.pop();
    }
    system->addProgressMeasure(getCurrentDeclarationBlock(), guard, measure);
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

    // Pop array dimensions from expression stack and construct array
    // type.
    type = buildArrayType(type, dim);

    // Append parameter to list of parameters.
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
    if (!getCurrentDeclarationBlock()->addFunction(type, name, currentFun))
    {
	errorHandler->handleError("Duplicate definition");
    }

    /* Push new frame and add parameters.
     */
    pushFrame(frame_t::createFrame(frames.top()));
    frames.top().add(params);
    params = frame_t::createFrame();

    /* Create function block.
     */
    currentFun->body = new BlockStatement(frames.top());
    blocks.push_back(currentFun->body);
}

void SystemBuilder::declFuncEnd() 
{ 
    assert(!blocks.empty());

    // Recover from unterminated blocks - delete any excess blocks 
    while (blocks.size() > 1) 
    {
	delete blocks.back();
	blocks.pop_back();
    }

    // Pop outer function block
    blocks.pop_back();

    // Restore global frame
    popFrame();

    // Reset current function pointer to NULL
    currentFun = NULL;
}

/********************************************************************
 * Process declarations
 */
void SystemBuilder::procTemplateSet(const char *name)
{
    type_t type = typeFragments[0].first;
    typeFragments.pop();

    if (!type.isScalar())
    {
	throw TypeException("Scalar type expected");
    }
    if (type.getRange().first.empty())
    {
	throw TypeException("Range expected");
    }

    templateset.addSymbol(name, type);
}

void SystemBuilder::procBegin(const char* name, uint32_t m, uint32_t n)
{
    if (frames.top().getIndexOf(name) != -1) 
    {
	errorHandler->handleError("Identifier defined multiple times");
    }
    currentTemplate = &system->addTemplate(name, templateset, params);
    pushFrame(currentTemplate->frame);
    params = frame_t::createFrame();
    templateset = frame_t::createFrame();
}
    
void SystemBuilder::procEnd() // 1 ProcBody
{
    currentTemplate = NULL;
    popFrame();
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
    currentTemplate->addLocation(name, e);
}
    
void SystemBuilder::procStateCommit(const char* name) 
{
    symbol_t uid;
    if (!resolve(name, uid)
	|| uid.getType().getBase() != type_t::LOCATION)
    {
	errorHandler->handleError("Location expected");
    } 
    else if (uid.getType().hasPrefix(prefix::URGENT)) 
    {
	errorHandler->handleError("States cannot be committed and urgent at the same time");
    } 
    else 
    {
	uid.setType(uid.getType().setPrefix(true, prefix::COMMITTED));
    }
}

void SystemBuilder::procStateUrgent(const char* name) 
{
    symbol_t uid;

    if (!resolve(name, uid)
	|| uid.getType().getBase() != type_t::LOCATION)
    {
	errorHandler->handleError("Location expected");
    } 
    else if (uid.getType().hasPrefix(prefix::COMMITTED)) 
    {
	errorHandler->handleError("States cannot be committed and urgent at the same time");
    }
    else 
    {
	uid.setType(uid.getType().setPrefix(true, prefix::URGENT));
    }
}

void SystemBuilder::procStateWinning(const char* name) 
{
    symbol_t uid;

    if (!resolve(name, uid)
	|| uid.getType().getBase() != type_t::LOCATION)
    {
	errorHandler->handleError("Location expected");
    } 
    else if (uid.getType().hasPrefix(prefix::LOSING)) 
    {
	errorHandler->handleError("States cannot be winning and losing at the same time");
    }
    else 
    {
	uid.setType(uid.getType().setPrefix(true, prefix::WINNING));
    }
}

void SystemBuilder::procStateLosing(const char* name) 
{
    symbol_t uid;

    if (!resolve(name, uid)
	|| uid.getType().getBase() != type_t::LOCATION)
    {
	errorHandler->handleError("Location expected");
    } 
    else if (uid.getType().hasPrefix(prefix::WINNING)) 
    {
	errorHandler->handleError("States cannot be winning and losing at the same time");
    }
    else 
    {
	uid.setType(uid.getType().setPrefix(true, prefix::LOSING));
    }
}

void SystemBuilder::procStateInit(const char* name) 
{
    symbol_t uid;
    if (!resolve(name, uid)
	|| uid.getType().getBase() != type_t::LOCATION)
    {
	throw TypeException("Location expected");
    }
    currentTemplate->init = uid;
}

void SystemBuilder::procEdgeBegin(const char* from, const char* to, const bool control)
{
    symbol_t fid, tid;

    if (!resolve(from, fid)
	|| fid.getType().getBase() != type_t::LOCATION)
    {
	throw TypeException("No such location (source)");
    }

    if (!resolve(to, tid)
	|| tid.getType().getBase() != type_t::LOCATION)
    {
	throw TypeException("No such location (destination)");
    }

    currentEdge = &currentTemplate->addEdge(fid, tid, control);
    currentEdge->guard = makeConstant(1);
    currentEdge->assign = makeConstant(1);
    pushFrame(currentEdge->select = frame_t::createFrame(frames.top()));
}
    
void SystemBuilder::procEdgeEnd(const char* from, const char* to)
{
    popFrame();
}

void SystemBuilder::procSelect(const char *id)
{
    type_t type = typeFragments[0].first;
    typeFragments.pop();
    if (!type.isScalar())
    {
	throw TypeException("Scalar type expected");
    } 
    if (type.getRange().first.empty()) 
    {
	throw TypeException("Range expected");
    }
    currentEdge->select.addSymbol(id, type);
}

void SystemBuilder::procGuard()
{
    currentEdge->guard = fragments[0];
    fragments.pop();
}

void SystemBuilder::procSync(synchronisation_t type)
{
    currentEdge->sync = expression_t::createSync(position, fragments[0], type);
    fragments.pop();
}

void SystemBuilder::procUpdate()
{
    currentEdge->assign = fragments[0];
    fragments.pop();
}

/*********************************************************************
 * Statements
 */
void SystemBuilder::blockBegin() 
{
    pushFrame(frame_t::createFrame(frames.top()));
    blocks.push_back(new BlockStatement(frames.top()));
}

void SystemBuilder::blockEnd() 
{
    // Append the block which is being terminated as a statement to
    // the containing block.
    BlockStatement *block = blocks.back();
    blocks.pop_back();
    blocks.back()->push_stat(block);

    // Restore containing frame
    popFrame();
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

void SystemBuilder::iterationBegin (const char *name)
{
    /* At this point, the type that we iterate over is on the type
     * stack. What we need to do is to add a new symbol to a new frame
     * with the given name and the type on the type stack. 
     *
     * In case of functions, declVar() adds variables to the current
     * frame and expects the type on the type stack. Since an
     * iteration statement is always used from within functions, it
     * should be safe to call declVar() from here.
     */
    pushFrame(frame_t::createFrame(frames.top()));
    declVar(name, 0, false);
    declVarEnd();

    /* Lookup the symbol. REVISIT: This could be provided by declVar().
     */
    symbol_t symbol;
    if (!resolve(name,symbol))
    {
	/* This should never happen.
	 */
	throw std::logic_error("SystemBuilder::iterationEnd(const char *): Could not resolve symbol!");
    }

    /* Create a new statement for the loop. We need to already create
     * this here as the statement is the only thing that can keep the
     * reference to the frame.
     */
    blocks.back()->push_stat(new IterationStatement(symbol, frames.top(), NULL));


    /* Finally, we only support iteration over scalars. This ought to
     * be checked by the type checker, but at that point we do not
     * have any information about the position in the input file, so
     * we check it here.
     */
    if (!symbol.getType().isScalar())
    {
	throw TypeException("Scalar type expected");
    }
    if (symbol.getType().getRange().first.empty())
    {
	throw TypeException("Range expected");
    }
}

void SystemBuilder::iterationEnd (const char *name)
{
    /* Retrieve the statement that we iterate over.
     */
    Statement* statement = blocks.back()->pop_stat();

    /* Add statement to loop construction.
     */
    static_cast<IterationStatement *>(blocks.back()->back())->stat = statement;

    /* Restore the frame pointer.
     */
    popFrame();
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
    blocks.push_back(new SwitchStatement(frames.top(), fragments[0]));
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
    blocks.push_back(new CaseStatement(frames.top(), fragments[0]));
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
    blocks.push_back(new DefaultStatement(frames.top()));
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

void SystemBuilder::exprCallBegin() 
{
    ExpressionBuilder::exprCallBegin();

    /* Check for recursive function calls. We could move this to
     * the type checker.
     */    
    if (currentFun != NULL && currentFun->uid == fragments[0].getSymbol())
    {
	throw TypeException("recursion is not allowed");
    }
}

/********************************************************************
 * System declaration
 */

void SystemBuilder::instantiationBegin(const char* name, const char* templ_name)
{
    /* Nothing to do here.
     */
}

void SystemBuilder::instantiationEnd(const char *name, const char *templ_name, uint32_t n)
{
    try
    {
	/* Lookup symbol.
	 */
	symbol_t id;
	if (!resolve(templ_name, id))
	{
	    throw TypeException("Unknown identifier");
	}	

	/* Check that the symbol is a template.
	 */
	if (id.getType().getBase() != type_t::TEMPLATE) 
	{
	    throw TypeException("Not a template: %s", templ_name);
	}

	/* Check number of arguments. If two many arguments, pop the
	 * rest.
	 */
	frame_t parameters = id.getType().getParameters();
	size_t expected = parameters.getSize();
	if (n < expected)
	{
	    errorHandler->handleError("Too few arguments");
	}
	else if (n > expected)
	{
	    errorHandler->handleError("Too many arguments");
	    fragments.pop(n - expected);
	    n = expected;
	}	

	/* Create template composition.
	 */
	template_t *templ = static_cast<template_t*>(id.getData());
	instance_t &instance = system->addInstance(name, templ);	
	while (n--) 
	{
	    symbol_t param = templ->frame[n];
	    instance.mapping[param] = fragments[0];
	    fragments.pop();
	}
    } 
    catch (const TypeException &e) 
    {
	/* Remember to pop arguments if something is wrong.
	 */
	fragments.pop(n);
	errorHandler->handleError(e.what());
    }
}
    
// Adds process_t* pointer to system_line
// Checks for dublicate entries
void SystemBuilder::process(const char* name)
{
    symbol_t sym;
    if (!resolve(name, sym))
    {
	throw TypeException("No such template: %s", name);
    }
    system->addProcess(sym);
}
    
void SystemBuilder::done()
{

}

void SystemBuilder::beforeUpdate()
{
    system->setBeforeUpdate(fragments[0]);
    fragments.pop();
}

void SystemBuilder::afterUpdate()
{
    system->setAfterUpdate(fragments[0]);
    fragments.pop();
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
    if (!resolve(name, symbol))
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
