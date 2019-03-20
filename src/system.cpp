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

#include "utap/builder.h"
#include "utap/system.h"
#include "utap/statement.h"
#include "libparser.h"

using namespace UTAP;
using namespace Constants;

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

edge_t &template_t::addEdge(symbol_t src, symbol_t dst)
{
    int32_t nr = edges.empty() ? 0 : edges.back().nr + 1;
    edges.push_back(edge_t());
    edges.back().src = static_cast<state_t*>(src.getData());
    edges.back().dst = static_cast<state_t*>(dst.getData());
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
#ifdef ENABLE_PRICD
    global.frame.addSymbol("cost", type_t::COST);
#endif
    global.frame.addSymbol("void", type_t::createTypeName(type_t::VOID_TYPE));
    addVariable(&global, type_t::CLOCK, "t(0)", expression_t());

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
template_t &TimedAutomataSystem::addTemplate(string name, frame_t params)
{
    int nr = templates.empty() ? 0 : templates.back().nr + 1;
    type_t type = type_t::createTemplate(params);
    templates.push_back(template_t());
    template_t &templ = templates.back();
    templ.uid = global.frame.addSymbol(name, type, &templ);
    templ.parameters = params;
    templ.frame = frame_t::createFrame(global.frame);
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

    uid = global.frame.addSymbol(
	uid.getName(), type_t::createProcess(process->templ->frame), process);

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

void TimedAutomataSystem::accept(SystemVisitor &visitor)
{
    visitor.visitSystemBefore(this);

    for_each(global.variables.begin(), global.variables.end(),
	     other_mem_fun(&visitor, &SystemVisitor::visitVariable));
    for_each(global.functions.begin(), global.functions.end(),
	     other_mem_fun(&visitor, &SystemVisitor::visitFunction));

    list<template_t>::iterator i;
    for (i = templates.begin(); i != templates.end(); ++i) 
    {
	if (!visitor.visitTemplateBefore(*i))
	{
	    continue;
	}
	for_each(i->variables.begin(), i->variables.end(),
		 other_mem_fun(&visitor, &SystemVisitor::visitVariable));
	for_each(i->functions.begin(), i->functions.end(),
		 other_mem_fun(&visitor, &SystemVisitor::visitFunction));
	for_each(i->states.begin(), i->states.end(),
		 other_mem_fun(&visitor, &SystemVisitor::visitState));
	for_each(i->edges.begin(), i->edges.end(),
		 other_mem_fun(&visitor, &SystemVisitor::visitEdge));
	visitor.visitTemplateAfter(*i);
    }

    for_each(instances.begin(), instances.end(),
	     other_mem_fun(&visitor, &SystemVisitor::visitInstance));
    for_each(processes.begin(), processes.end(),
	     other_mem_fun(&visitor, &SystemVisitor::visitProcess));
	
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
    path[0] = 0;
}

void ContextVisitor::setContextNone()
{
    path[0] = 0;
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
