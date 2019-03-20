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

#include <stack>
#include <algorithm>
#include <cstdio>
#include <climits>
#include <cassert>
#include <sstream>

#include <boost/bind.hpp>

#include "utap/builder.h"
#include "utap/system.h"
#include "utap/statement.h"
#include "libparser.h"

using namespace UTAP;
using namespace Constants;

using boost::bind;
using std::list;
using std::stack;
using std::vector;
using std::map;
using std::pair;
using std::make_pair;
using std::min;
using std::max;
using std::set;
using std::string;

static const char *const unsupported
= "Internal error: Feature not supported in this mode.";
static const char *const invalid_type = "Invalid type";

function_t::~function_t()
{
    delete body; 
}

bool declarations_t::addFunction(type_t type, string name, function_t *&fun)
{	
    bool duplicate = frame.getIndexOf(name) != -1;
    functions.push_back(function_t());
    fun = &functions.back();
    fun->uid = frame.addSymbol(name, type, fun); // Add symbol
    return !duplicate;
}

state_t &template_t::addLocation(string name, expression_t inv)
{
    bool duplicate = frame.getIndexOf(name) != -1;
    
    states.push_back(state_t());
    state_t &state = states.back();
    state.uid = frame.addSymbol(name, type_t::LOCATION, &state);
    state.locNr = states.size() - 1;
    state.invariant = inv;

    if (duplicate) 
    {
	throw TypeException("Duplicate definition of %s", name.c_str());
    }

    return state;
}

edge_t &template_t::addEdge(symbol_t src, symbol_t dst, bool control)
{
    int32_t nr = edges.empty() ? 0 : edges.back().nr + 1;
    edges.push_back(edge_t());
    edges.back().src = static_cast<state_t*>(src.getData());
    edges.back().dst = static_cast<state_t*>(dst.getData());
    edges.back().control = control;
    edges.back().nr = nr;
    return edges.back();
}

TimedAutomataSystem::TimedAutomataSystem()
{
    global.frame = frame_t::createFrame();
    global.frame.addSymbol("bool", type_t::createTypeName(type_t::BOOL));
    global.frame.addSymbol("int", type_t::createTypeName(type_t::INT));
    global.frame.addSymbol("chan", type_t::createTypeName(type_t::CHANNEL));
    global.frame.addSymbol("clock", type_t::createTypeName(type_t::CLOCK));
    global.frame.addSymbol("void", type_t::createTypeName(type_t::VOID_TYPE));
    global.frame.addSymbol("scalar", type_t::createTypeName(type_t::SCALAR));
    addVariable(&global, type_t::CLOCK, "t(0)", expression_t());
#ifdef ENABLE_PRICED
    addVariable(&global, type_t::COST, "cost", expression_t());
#endif

#ifdef ENABLE_PRIORITY
    /* Initially false: set by priority declarations. */
    hasPriority = false;
#endif
}

TimedAutomataSystem::~TimedAutomataSystem()
{

}

list<template_t> &TimedAutomataSystem::getTemplates()
{
    return templates;
}

list<process_t> &TimedAutomataSystem::getProcesses()
{
    return processes;
}

declarations_t &TimedAutomataSystem::getGlobals()
{
    return global;
}

const set<symbol_t> &TimedAutomataSystem::getConstants() const
{
    return constants;
}

/** Creates and returns a new template. The template is created with
 *  the given name and parameters and added to the global frame. The
 *  new template is set to be the current template. The method does
 *  not check for duplicate declarations.
 */
template_t &TimedAutomataSystem::addTemplate(
    string name, frame_t templateset, frame_t params)
{
    int nr = templates.empty() ? 0 : templates.back().nr + 1;
    type_t type = type_t::createTemplate(params);
    templates.push_back(template_t());
    template_t &templ = templates.back();
    templ.uid = global.frame.addSymbol(name, type, &templ);
    templ.templateset = templateset;
    templ.parameters = params;
    templ.frame = frame_t::createFrame(global.frame);
    templ.frame.add(templateset);
    templ.frame.add(params);
    templ.nr = nr;
    return templ;
}

instance_t &TimedAutomataSystem::addInstance(
    string name, const template_t *templ)
{
    instances.push_back(instance_t());
    instance_t *instance = &instances.back();
    instance->uid = global.frame.addSymbol(name, type_t::INSTANCE, instance);
    instance->templ = templ;
    return *instance;
}

process_t &TimedAutomataSystem::addProcess(symbol_t uid)
{
    process_t *process;
    int32_t nr = processes.empty() ? 0 : processes.back().nr + 1;
    type_t type = uid.getType();
    type_t base = type.getBase();
    if (base == type_t::INSTANCE) 
    {
	instance_t *instance = static_cast<instance_t*>(uid.getData());
	processes.push_back(process_t());
	process = &processes.back();
	process->templ = instance->templ;
	process->mapping = instance->mapping;
    }
    else if (base == type_t::TEMPLATE) 
    {
	if (type.getParameters().getSize() > 0) 
	{
	    throw TypeException("Invalid use of parameterised template: %s", 
				uid.getName().c_str());
	}

	processes.push_back(process_t());
	process = &processes.back();
	process->templ = static_cast<template_t*>(uid.getData());
    } 
    else 
    {
	throw TypeException("Not a template: %s", uid.getName().c_str());
    }

    type = type_t::createProcess(process->templ->frame);
    for (int i = process->templ->templateset.getSize() - 1; i >= 0; i--)
    {
	type = type_t::createArray(process->templ->templateset[i].getType(), type);
    }

    uid = global.frame.addSymbol(uid.getName(), type, process);

    process->nr = nr;
    process->uid = uid;

    return *process;
}

// Add a regular variable
variable_t *TimedAutomataSystem::addVariable(
    declarations_t *context, type_t type, string name, expression_t initial)
{
    variable_t *var;
    var = addVariable(context->variables, context->frame, type, name);
    var->expr = initial;

    if (type.hasPrefix(prefix::CONSTANT)) 
    {
	constants.insert(var->uid);
	constantValuation[var->uid] = initial;
    }

    return var;
}

variable_t *TimedAutomataSystem::addVariableToFunction(
    function_t *function, frame_t frame, type_t type, string name,
    expression_t initial)
{
    variable_t *var;
    var = addVariable(function->variables, frame, type, name);
    var->expr = initial;
    return var;
}

// Add a regular variable
variable_t *TimedAutomataSystem::addVariable(
    list<variable_t> &variables, frame_t frame, type_t type, string name)
{
    bool duplicate = frame.getIndexOf(name) != -1;
    variable_t *var;

    // Add variable
    variables.push_back(variable_t());
    var = &variables.back();

    // Add symbol
    var->uid = frame.addSymbol(name, type, var);

    if (duplicate)
    {
	throw TypeException("Duplicate definition of identifier %s", 
			    name.c_str());
    }

    return var;
}

void TimedAutomataSystem::addProgressMeasure(
    declarations_t *context, expression_t guard, expression_t measure)
{
    progress_t p;
    p.guard = guard;
    p.measure = measure;
    context->progress.push_back(p);
}

static void visit(SystemVisitor &visitor, frame_t frame)
{
    for (size_t i = 0; i < frame.getSize(); i++)
    {
	void *data = frame[i].getData();

	if (data == NULL)
	{
	    /* Parameters have no data field and we do not visit them.
	     */
	    continue;
	}

	type_t type = frame[i].getType();
	type_t base = type.getBase();
	while (base == type_t::ARRAY)
	{
	    type = type.getSub();
	    base = type.getBase();
	}

	if (base == type_t::INT
	    || base == type_t::BOOL
	    || base == type_t::CLOCK
	    || base == type_t::CHANNEL
	    || base == type_t::SCALAR
	    || base == type_t::RECORD)
	{
	    visitor.visitVariable(*static_cast<variable_t*>(data));
	} 
	else if (base == type_t::LOCATION) 
	{
	    visitor.visitState(*static_cast<state_t*>(data));
	}
	else if (base == type_t::PROCESS) 
	{
	    visitor.visitProcess(*static_cast<process_t*>(data));
	}
	else if (base == type_t::FUNCTION)
	{
	    visitor.visitFunction(*static_cast<function_t*>(data));
	}
	else if (base == type_t::INSTANCE)
	{
	    visitor.visitInstance(*static_cast<instance_t*>(data));
	}
	else if (base == type_t::TEMPLATE)
	{
	    template_t *temp = static_cast<template_t*>(data);
	    if (visitor.visitTemplateBefore(*temp))
	    {
		visit(visitor, temp->frame);

		for_each(temp->edges.begin(), temp->edges.end(),
			 bind(&SystemVisitor::visitEdge, &visitor, _1));

		visitor.visitTemplateAfter(*temp);
	    }
	}
	else if (base == type_t::NTYPE)
	{
	    // Ignored
	}
    }
}

void TimedAutomataSystem::accept(SystemVisitor &visitor)
{
    visitor.visitSystemBefore(this);
    visit(visitor, global.frame);
    visitor.visitSystemAfter(this);
}

map<symbol_t, expression_t> &TimedAutomataSystem::getConstantValuation() 
{
    return constantValuation;
}

const map<symbol_t, expression_t> &TimedAutomataSystem::getConstantValuation() const
{
    return constantValuation;
}

void TimedAutomataSystem::setBeforeUpdate(expression_t e)
{
    beforeUpdate = e;
}

expression_t TimedAutomataSystem::getBeforeUpdate()
{
    return beforeUpdate;
}

void TimedAutomataSystem::setAfterUpdate(expression_t e)
{
    afterUpdate = e;
}

expression_t TimedAutomataSystem::getAfterUpdate()
{
    return afterUpdate;
}

#ifdef ENABLE_PRIORITY
void TimedAutomataSystem::setChanPriority(symbol_t uid, int32_t prio)
{
    hasPriority = true;
    chanPriority[uid] = prio;
}

void TimedAutomataSystem::setProcPriority(symbol_t uid, int32_t prio)
{
    hasPriority = true;
    procPriority[uid] = prio;
}

int32_t TimedAutomataSystem::getChanPriority(symbol_t uid)
{
    if (chanPriority.count(uid) == 0)
    {
        return 0;
    }
    else
    {
        return chanPriority[uid];
    }
}

int32_t TimedAutomataSystem::getProcPriority(symbol_t uid)
{
    if (procPriority.count(uid) == 0)
    {
        return 0;
    }
    else
    {
        return procPriority[uid];
    }
}

bool TimedAutomataSystem::hasPriorityDeclaration() const
{
    return hasPriority;
}
#endif /* ENABLE_PRIORITY */

ContextVisitor::ContextVisitor(ErrorHandler *handler)
{
    errorHandler = handler;
    currentTemplate = -1;
}

void ContextVisitor::setContextNone()
{
    path = "";
}

void ContextVisitor::setContextDeclaration()
{
    if (currentTemplate == -1) 
    {
	path = "/nta/declaration";
    }
    else 
    {
	std::ostringstream str;
	str << "/nta/template[" << currentTemplate + 1 << "]/declaration";
	path = str.str();
    }
}

void ContextVisitor::setContextParameters()
{
    std::ostringstream str;
    str << "/nta/template[" << currentTemplate + 1 << "]/parameter";
    path = str.str();
}

void ContextVisitor::setContextInvariant(state_t &state)
{
    std::ostringstream str;
    str << "/nta/template[" << currentTemplate + 1 << "]/location["
	<< state.locNr + 1 << "]/label[@kind=\"invariant\"]";
    path = str.str();
}

void ContextVisitor::setContextSelect(edge_t &edge)
{
    std::ostringstream str;
    str << "/nta/template[" << currentTemplate + 1
	<< "]/transition[" << edge.nr + 1
	<< "]/label[@kind=\"select\"]";
    path = str.str();
}

void ContextVisitor::setContextGuard(edge_t &edge)
{
    std::ostringstream str;
    str << "/nta/template[" << currentTemplate + 1
	<< "]/transition[" << edge.nr + 1
	<< "]/label[@kind=\"guard\"]";
    path = str.str();
}

void ContextVisitor::setContextSync(edge_t &edge)
{
    std::ostringstream str;
    str << "/nta/template[" << currentTemplate + 1
	<< "]/transition[" << edge.nr + 1
	<< "]/label[@kind=\"synchronisation\"]";
    path = str.str();
}

void ContextVisitor::setContextAssignment(edge_t &edge)
{
    std::ostringstream str;
    str << "/nta/template[" << currentTemplate + 1
	<< "]/transition[" << edge.nr + 1
	<< "]/label[@kind=\"assignment\"]";
    path = str.str();
}

void ContextVisitor::setContextInstantiation()
{
    path = "/nta/instantiation";
}

bool ContextVisitor::visitTemplateBefore(template_t &templ)
{
    currentTemplate = templ.nr;
    return true;
}

void ContextVisitor::visitTemplateAfter(template_t &templ)
{
    currentTemplate = -1;
}

void ContextVisitor::handleWarning(expression_t expr, string msg)
{
    if (errorHandler) 
    {
	errorHandler->setCurrentPath(this);	
	errorHandler->setCurrentPosition(expr.getPosition());
	errorHandler->handleWarning(msg.c_str());
    }
}

void ContextVisitor::handleError(expression_t expr, string msg)
{
    if (errorHandler) 
    {
	errorHandler->setCurrentPath(this);	
	errorHandler->setCurrentPosition(expr.getPosition());
	errorHandler->handleError(msg.c_str());
    }
}

string ContextVisitor::get() const
{
    return path;
}
