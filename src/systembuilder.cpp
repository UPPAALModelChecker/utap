// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2002-2006 Uppsala University and Aalborg University.

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

#include "utap/systembuilder.h"

#include <boost/tuple/tuple.hpp>
#include <vector>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cassert>
#include <inttypes.h>
#include <stdexcept>
#include <sstream>

using namespace UTAP;
using namespace Constants;

using std::vector;
using std::pair;
using std::make_pair;
using std::min;
using std::max;
using std::string;

SystemBuilder::SystemBuilder(TimedAutomataSystem *system)
    : ExpressionBuilder(system)
{
    currentFun = NULL;
    currentTemplate = NULL;

    params = frame_t::createFrame();
    currentChanPriority = 0;
    currentProcPriority = 0;
};

static void collectDependencies(
    std::set<symbol_t> &dependencies, expression_t expr)
{
    std::set<symbol_t> symbols;
    expr.collectPossibleReads(symbols);
    while (!symbols.empty())
    {
		symbol_t s = *symbols.begin();
		symbols.erase(s);
		if (dependencies.find(s) == dependencies.end())
		{
			dependencies.insert(s);
			if (s.getData())
			{
				variable_t *v = static_cast<variable_t*>(s.getData());
				v->expr.collectPossibleReads(symbols);
			}
		}
    }
}

static void collectDependencies(
    std::set<symbol_t> &dependencies, type_t type)
{
    if (type.getKind() == RANGE)
    {
		expression_t lower, upper;
		boost::tie(lower, upper) = type.getRange();
		collectDependencies(dependencies, lower);
		collectDependencies(dependencies, upper);
		collectDependencies(dependencies, type[0]);
    }
    else
    {
		for (size_t i = 0; i < type.size(); i++)
		{
			collectDependencies(dependencies, type[i]);
		}
    }
}

declarations_t *SystemBuilder::getCurrentDeclarationBlock()
{
    return (currentTemplate ? currentTemplate : &system->getGlobals());
}

void SystemBuilder::typeArrayOfSize(size_t n)
{
    /* Pop array size of fragments stack.
     */
    expression_t expr = fragments[0];
    //position_t pos = expr.getPosition();
    fragments.pop();

    /* Create type.
     */
    exprNat(0);
    fragments.push(expr);
    exprNat(1);
    exprBinary(MINUS);
    typeBoundedInt(PREFIX_NONE);
    typeArrayOfType(n + 1);
}

void SystemBuilder::typeArrayOfType(size_t n)
{
    type_t size = typeFragments[0];
    typeFragments.pop();
    typeFragments[n - 1] =
		type_t::createArray(typeFragments[n - 1], size, position);

    /* If template local declaration, then mark all symbols in 'size'
     * and those that they depend on as restricted. Otherwise we would
     * not be able to compute the offset of a process in a set of
     * processes.
     */
    if (currentTemplate)
    {
		collectDependencies(currentTemplate->restricted, size);
    }

    if (!size.isInteger() && !size.isScalar() && !size.is(RANGE))
    {
		handleError("Array must be defined over an integer range or a scalar set");
    }
}

/**
 * Used to construct a new struct type, which is then pushed onto the
 * type stack. The type is based on n fields, which are expected to be
 * on and will be popped off the type stack.
 */
void SystemBuilder::typeStruct(PREFIX prefix, uint32_t n)
{
    vector<type_t> f(fields.end() - n, fields.end());
    vector<string> l(labels.end() - n, labels.end());

    fields.erase(fields.end() - n, fields.end());
    labels.erase(labels.end() - n, labels.end());

    typeFragments.push(
		applyPrefix(prefix, type_t::createRecord(f, l, position)));
}

/**
 * Used to declare the fields of a structure. The type of the field is
 * expected to be on the type fragment stack.
 */
void SystemBuilder::structField(const char* name)
{
    type_t type = typeFragments[0];
    typeFragments.pop();

    // Constant fields are not allowed
    if (type.is(CONSTANT))
    {
		handleError("Constant fields not allowed in struct");
    }

    fields.push_back(type);
    labels.push_back(name);

    /* Check the base type. We should check this in the type
     * checker. The problem is that we do not maintain the position of
     * types, hence we cannot place the error message if we wait until
     * the type check phase.
     */
    type_t base = type.stripArray();
    if (!base.isRecord() && !base.isScalar() && !base.isIntegral())
    {
		handleError("Invalid type in structure");
    }
}

/**
 * A type definition. Assign the name to the given type on the type
 * fragment stack. In case of array types, dim constant expressions
 * are expected on and popped from the expression stack.
 */
void SystemBuilder::declTypeDef(const char* name)
{
    type_t type = type_t::createTypeDef(name, typeFragments[0], position);
    typeFragments.pop();
    frames.top().addSymbol(name, type);
}

static bool initialisable(type_t type)
{
    type = type.strip();
    switch (type.getKind())
    {
    case RECORD:
		for (size_t i = 0; i < type.size(); i++)
		{
			if (!initialisable(type[i]))
			{
				return false;
			}
		}
		return true;

    case ARRAY:
		if (type.getArraySize().isScalar())
		{
			return false;
		}
		return initialisable(type.getSub());

    default:
		return type.isIntegral();
    }
}

static bool mustInitialise(type_t type)
{
    assert(type.getKind() != FUNCTION);
    assert(type.getKind() != PROCESS);
    assert(type.getKind() != INSTANCE);

    switch (type.getKind())
    {
    case CONSTANT:
		return true;
    case RECORD:
		for (size_t i = 0; i < type.size(); i++)
		{
			if (mustInitialise(type[i]))
			{
				return true;
			}
		}
		return false;
    default:
		return type.size() > 0 && mustInitialise(type[0]);
    }
}

/**
 * Declare a new variable of the given name. The type is expected to
 * be on the type stack. If the variable has an initialiser (the init
 * parameter is true), then a constant expression is expected at the
 * top of the expression stack.  The expressions will be popped of the
 * stack (the type is left untouched).
 */
void SystemBuilder::declVar(const char* name, bool hasInit)
{
    // Pop initial value
    expression_t init;
    if (hasInit)
    {
		init = fragments[0];
		fragments.pop();
    }

    // Construct type
    type_t type = typeFragments[0];
    typeFragments.pop();

    // Check whether initialiser is allowed/required
    if (hasInit && !initialisable(type))
    {
		handleError("Cannot have initialiser");
    }

    if (!hasInit && mustInitialise(type))
    {
		handleError("Constants must have an initialiser");
    }

    if (currentFun && !initialisable(type))
    {
		handleError("Type is not allowed in functions");
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
    type_t type = fragments[0].getType().createLabel(name, position);
    fragments[0].setType(type);
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

    // Compute new type (each field has a label type, see declFieldInit())
    vector<type_t> types;
    vector<string> labels;
    for (uint32_t i = 0; i < num; i++)
    {
		type_t type = fields[i].getType();
		types.push_back(type[0]);
		labels.push_back(type.getLabel(0));
		fields[i].setType(type[0]);
    }

    // Create list expression
    fragments.push(expression_t::createNary(
					   LIST, fields, position,
					   type_t::createRecord(types, labels, position)));
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
void SystemBuilder::declParameter(const char* name, bool ref)
{
    type_t type = typeFragments[0];
    typeFragments.pop();

    if (ref)
    {
		type = type.createPrefix(REF);
    }

    params.addSymbol(name, type);
}

void SystemBuilder::declFuncBegin(const char* name)
{
    assert(currentFun == NULL);

    type_t return_type = typeFragments[0];
    typeFragments.pop();

    vector<type_t> types;
    vector<string> labels;
    for (size_t i = 0; i < params.getSize(); i++)
    {
		types.push_back(params[i].getType());
		labels.push_back(params[i].getName());
    }
    type_t type = type_t::createFunction(return_type, types, labels, position);
    if (!getCurrentDeclarationBlock()->addFunction(type, name, currentFun))
    {
		handleError("Duplicate definition");
    }

    /* We maintain a stack of frames. As the function has a local
     * scope, we push a new frame and add the parameters to it.
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

    /* Recover from unterminated blocks - delete any excess blocks.
     */
    while (blocks.size() > 1)
    {
		delete blocks.back();
		blocks.pop_back();
    }

    /* If function has a non void return type, then check that last
     * statement is a return statement.
     */
    BlockStatement *body = currentFun->body;
    if (!currentFun->uid.getType()[0].isVoid() && !body->returns())
    {
		handleError("Return statement expected");
    }

    /* Pop outer function block.
     */
    blocks.pop_back();

    /* Restore global frame.
     */
    popFrame();

    /* Reset current function pointer to NULL.
     */
    currentFun = NULL;
}

/********************************************************************
 * Process declarations
 */
void SystemBuilder::procBegin(const char* name)
{
    if (frames.top().getIndexOf(name) != -1)
    {
		handleError("Identifier defined multiple times");
    }
    currentTemplate = &system->addTemplate(name, params);
    pushFrame(currentTemplate->frame);
    params = frame_t::createFrame();
}

void SystemBuilder::procEnd() // 1 ProcBody
{
    currentTemplate = NULL;
    popFrame();
}

/**
 * Add a state to the current template. An invariant expression is
 * expected on and popped from the expression stack if \a hasInvariant
 * is true.
 */
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
    if (!resolve(name, uid) || !uid.getType().isLocation())
    {
		handleError("Location expected");
    }
    else if (uid.getType().is(URGENT))
    {
		handleError("States cannot be committed and urgent at the same time");
    }
    else
    {
		uid.setType(uid.getType().createPrefix(COMMITTED, position));
    }
}

void SystemBuilder::procStateUrgent(const char* name)
{
    symbol_t uid;

    if (!resolve(name, uid) || !uid.getType().isLocation())
    {
		handleError("Location expected");
    }
    else if (uid.getType().is(COMMITTED))
    {
		handleError("States cannot be committed and urgent at the same time");
    }
    else
    {
		uid.setType(uid.getType().createPrefix(URGENT, position));
    }
}

void SystemBuilder::procStateWinning(const char* name)
{
    symbol_t uid;

    if (!resolve(name, uid) || !uid.getType().isLocation())
    {
		handleError("Location expected");
    }
    else if (uid.getType().is(LOSING))
    {
		handleError("States cannot be winning and losing at the same time");
    }
    else
    {
		uid.setType(uid.getType().createPrefix(WINNING));
    }
}

void SystemBuilder::procStateLosing(const char* name)
{
    symbol_t uid;

    if (!resolve(name, uid) || !uid.getType().isLocation())
    {
		handleError("Location expected");
    }
    else if (uid.getType().is(WINNING))
    {
		handleError("States cannot be winning and losing at the same time");
    }
    else
    {
		uid.setType(uid.getType().createPrefix(LOSING));
    }
}

void SystemBuilder::procStateInit(const char* name)
{
    symbol_t uid;
    if (!resolve(name, uid) || !uid.getType().isLocation())
    {
		handleError("Location expected");
    }
    else
    {
		currentTemplate->init = uid;
    }
}

void SystemBuilder::procEdgeBegin(const char* from, const char* to, const bool control)
{
    symbol_t fid, tid;

    if (!resolve(from, fid) || !fid.getType().isLocation())
    {
		handleError("No such location (source)");
    }
    else if (!resolve(to, tid) || !tid.getType().isLocation())
    {
		handleError("No such location (destination)");
    }
    else
    {
		currentEdge = &currentTemplate->addEdge(fid, tid, control);
		currentEdge->guard = makeConstant(1);
		currentEdge->assign = makeConstant(1);
		pushFrame(currentEdge->select = frame_t::createFrame(frames.top()));
    }
}

void SystemBuilder::procEdgeEnd(const char* from, const char* to)
{
    popFrame();
}

void SystemBuilder::procSelect(const char *id)
{
    type_t type = typeFragments[0];
    typeFragments.pop();

    if (!type.is(CONSTANT))
    {
		type = type.createPrefix(CONSTANT);
    }

    if (!type.isScalar() && !type.isInteger())
    {
		handleError("Scalar set or integer expected");
    }
    else if (!type.is(RANGE))
    {
		handleError("Range expected");
    }
    else
    {
		currentEdge->select.addSymbol(id, type);
    }
}

void SystemBuilder::procGuard()
{
    currentEdge->guard = fragments[0];
    fragments.pop();
}

void SystemBuilder::procSync(synchronisation_t type)
{
    currentEdge->sync = expression_t::createSync(fragments[0], type, position);
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
    type_t type = typeFragments[0];
    typeFragments.pop();

    /* The iterator cannot be modified.
     */
    if (!type.is(CONSTANT))
    {
		type = type.createPrefix(CONSTANT);
    }

    /* The iteration statement has a local scope for the iterator.
     */
    pushFrame(frame_t::createFrame(frames.top()));

    /* Add variable.
     */
    variable_t *variable = system->addVariableToFunction(
		currentFun, frames.top(), type, name, expression_t());

    /* Create a new statement for the loop. We need to already create
     * this here as the statement is the only thing that can keep the
     * reference to the frame.
     */
    blocks.back()->push_stat(
		new IterationStatement(variable->uid, frames.top(), NULL));
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

void SystemBuilder::exprStatement()
{ // 1 expr
    blocks.back()->push_stat(new ExprStatement(fragments[0]));
    fragments.pop();
}

void SystemBuilder::returnStatement(bool args)
{ // 1 expr if argument is true
    if (!currentFun)
    {
		handleError("Cannot return outside of function declaration");
    }
    else
    {
		/* Only functions with non-void return type are allowed to have
		 * arguments on return.
		 */
		type_t return_type = currentFun->uid.getType()[0];
		if (return_type.isVoid() && args)
		{
			handleError("'return' with a value, in function returning void");
		}
		else if (!return_type.isVoid() && !args)
		{
			handleError("`return' with no value, in function returning non-void");
		}

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
		handleError("recursion is not allowed");
    }
}

/********************************************************************
 * System declaration
 */

void SystemBuilder::instantiationBegin(
    const char* name, size_t parameters, const char* templ_name)
{
    /* Make sure this identifier is new.
     */
    if (frames.top().getIndexOf(name) != -1)
    {
        handleError("Identifier defined multiple times");
    }

    /* Lookup symbol.
     */
    symbol_t id;
    if (!resolve(templ_name, id) || id.getType().getKind() != INSTANCE)
    {
        handleError("Not a template");
    }

    /* Push parameters to frame stack.
     */
    frame_t frame = frame_t::createFrame(frames.top());
    frame.add(params);
    pushFrame(frame);
    params = frame_t::createFrame();
}

void SystemBuilder::instantiationEnd(
    const char *name, size_t parameters, const char *templ_name, size_t arguments)
{
    /* Parameters are at the top of the frame stack.
     */
    frame_t params = frames.top();
    popFrame();

    /* Lookup symbol. In case of failure, instantiationBegin already
     * reported the problem.
     */
    symbol_t id;
    if (resolve(templ_name, id) && id.getType().getKind() == INSTANCE)
    {
		instance_t *old_instance = static_cast<instance_t*>(id.getData());

		/* Check number of arguments. If too many arguments, pop the
		 * rest.
		 */
		size_t expected = id.getType().size();
		if (arguments < expected)
		{
			handleError("Too few arguments");
		}
		else if (arguments > expected)
		{
			handleError("Too many arguments");
		}
		else
		{
			/* Collect arguments from expression stack.
			 */
			vector<expression_t> exprs(arguments);
			while (arguments)
			{
				arguments--;
				exprs[arguments] = fragments[0];
				fragments.pop();
			}

			/* Create template composition.
			 */
			instance_t &new_instance =
				system->addInstance(name, *old_instance, params, exprs);

			/* Propagate information about restricted variables. The
			 * variables used in arguments to restricted parameters of
			 * old_instance are restricted in new_instance.
			 *
			 * REVISIT: Move to system.cpp?
			 */
			std::set<symbol_t> &restricted = old_instance->restricted;
			for (size_t i = 0; i < expected; i++)
			{
				if (restricted.find(old_instance->parameters[i]) != restricted.end())
				{
					collectDependencies(new_instance.restricted, exprs[i]);
				}
			}
		}
    }
    fragments.pop(arguments);
}

// Adds process_t* pointer to system_line
// Checks for dublicate entries
void SystemBuilder::process(const char* name)
{
    symbol_t symbol;
    if (!resolve(name, symbol))
    {
		throw TypeException(boost::format("No such process: %1%") % name);
    }
    type_t type = symbol.getType();
    if (type.getKind() != INSTANCE)
    {
		throw TypeException(boost::format("Not a template: %1%") % symbol.getName());
    }
    if (type.size() > 0)
    {
		// FIXME: Check type of unbound parameters
    }
    system->addProcess(*static_cast<instance_t*>(symbol.getData()));
    procPriority(name);
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

void SystemBuilder::incChanPriority()
{
    currentChanPriority++;
}

void SystemBuilder::incProcPriority()
{
    currentProcPriority++;
}

void SystemBuilder::defaultChanPriority()
{
    system->setDefaultChanPriority(currentChanPriority);
}

void SystemBuilder::procPriority(const char* name)
{
    symbol_t symbol;
    if (!resolve(name, symbol))
    {
        handleError((boost::format("No such process: %1%") % name).str());
    }
    else
    {
		system->setProcPriority(name, currentProcPriority);
    }
}

void SystemBuilder::chanPriority()
{
    system->setChanPriority(fragments[0], currentChanPriority);
    fragments.pop();
}
