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

#include "utap/builder.hh"
#include "utap/system.hh"
#include "utap/statement.hh"
#include "libparser.hh"

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

static const char *const unsupported
= "Internal error: Feature not supported in this mode.";
static const char *const invalid_type = "Invalid type";

function_t::~function_t()
{
    delete body; 
}

TimedAutomataSystem::TimedAutomataSystem()
{
    setDeclarationBlock(&global);
    global.frame = frame_t::createFrame();
    global.frame.addSymbol("bool", type_t::createTypeName(type_t::BOOL));
    global.frame.addSymbol("int", type_t::createTypeName(type_t::INT));
    global.frame.addSymbol("chan", type_t::createTypeName(type_t::CHANNEL));
    global.frame.addSymbol("clock", type_t::createTypeName(type_t::CLOCK));
    addVariable(type_t::CLOCK, "t(0)", expression_t());
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

template_t &TimedAutomataSystem::getGlobals()
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
template_t &TimedAutomataSystem::addTemplate(const char *name, frame_t params)
{
    int nr = templates.empty() ? 0 : templates.back().nr + 1;
    type_t type = type_t::createTemplate(params);
    templates.push_back(template_t());
    template_t &templ = templates.back();
    templ.uid = global.frame.addSymbol(name, type, &templ);
    templ.frame = frame_t::createFrame(global.frame);
    templ.frame.add(params);
    templ.nr = nr;
    setDeclarationBlock(&templ);
    return templ;
}

state_t &TimedAutomataSystem::addLocation(const char *name, expression_t inv)
{
    bool duplicate = current->frame.getIndexOf(name) != -1;
    
    current->states.push_back(state_t());
    state_t &state = current->states.back();
    state.uid = current->frame.addSymbol(name, type_t::LOCATION, &state);
    state.locNr = current->states.size() - 1;
    state.invariant = inv;

    if (duplicate) {	
	throw TypeException("Duplicate definition of %s", name);
    }

    return state;
}

transition_t &TimedAutomataSystem::addTransition(symbol_t src, symbol_t dst)
{
    list<transition_t> &trans = current->transitions;
    int32_t nr = trans.empty() ? 0 : trans.back().nr + 1;
    trans.push_back(transition_t());
    trans.back().src = static_cast<state_t*>(src.getData());
    trans.back().dst = static_cast<state_t*>(dst.getData());
    trans.back().nr = nr;
    return trans.back();
}

instance_t &TimedAutomataSystem::addInstance(
    const char *name, const template_t *templ)
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
    if (base == type_t::INSTANCE) {
	instance_t *instance = static_cast<instance_t*>(uid.getData());
	processes.push_back(process_t());
	process = &processes.back();
	process->templ = instance->templ;
	process->mapping = instance->mapping;
    } else if (base == type_t::TEMPLATE) {
	if (type.getParameters().getSize() > 0) {
	    throw TypeException("Invalid use of parameterised template: %s", 
				uid.getName());
	}

	processes.push_back(process_t());
	process = &processes.back();
	process->templ = static_cast<template_t*>(uid.getData());
    } else {
	throw TypeException("Not a template: %s", uid.getName());
    }

    process->nr = nr;
    process->uid = uid;
    uid.setType(type_t::createProcess(process->templ->frame));
    uid.setData(process);
    return *process;
}

void TimedAutomataSystem::setDeclarationBlock(declarations_t *value)
{
    current = value;
}

// Add a regular variable
variable_t *TimedAutomataSystem::addVariable(
    type_t type, const char *name, expression_t initial)
{
    bool duplicate = current->frame.getIndexOf(name) != -1;
    variable_t *var;

    // Add variable
    current->variables.push_back(variable_t());
    var = &current->variables.back();
    var->expr = initial;
    var->global = (current == &global);

    // Add symbol
    var->uid = current->frame.addSymbol(name, type, var);

    if (type.hasPrefix(prefix::CONSTANT)) {
	constants.insert(var->uid);
	// TODO: This will not work for structures (the order
	// of the initialiser fields might not match the declaration
	// of the struct).
	constantValuation[var->uid] = var->expr;
    }

    if (duplicate)
	throw TypeException("Duplicate definition of identifier %s", name);

    return var;
}

// Add a function 
bool TimedAutomataSystem::addFunction(type_t type, const char *name, function_t *&fun)
{	
    bool duplicate = current->frame.getIndexOf(name) != -1;
    current->functions.push_back(function_t());
    fun = &current->functions.back();
    fun->global = (current == &global);
    fun->uid = current->frame.addSymbol(name, type, fun); // Add symbol
    return !duplicate;
}

void TimedAutomataSystem::accept(SystemVisitor &visitor)
{
    visitor.visitSystemBefore(this);

    for_each(global.variables.begin(), global.variables.end(),
	     other_mem_fun(&visitor, &SystemVisitor::visitVariable));
    for_each(global.functions.begin(), global.functions.end(),
	     other_mem_fun(&visitor, &SystemVisitor::visitFunction));

    list<template_t>::iterator i;
    for (i = templates.begin(); i != templates.end(); ++i) {
	if (!visitor.visitTemplateBefore(*i))
	    continue;
	for_each(i->variables.begin(), i->variables.end(),
		 other_mem_fun(&visitor, &SystemVisitor::visitVariable));
	for_each(i->functions.begin(), i->functions.end(),
		 other_mem_fun(&visitor, &SystemVisitor::visitFunction));
	for_each(i->states.begin(), i->states.end(),
		 other_mem_fun(&visitor, &SystemVisitor::visitState));
	for_each(i->transitions.begin(), i->transitions.end(),
		 other_mem_fun(&visitor, &SystemVisitor::visitTransition));
	visitor.visitTemplateAfter(*i);
    }

    for_each(instances.begin(), instances.end(),
	     other_mem_fun(&visitor, &SystemVisitor::visitInstance));
    for_each(processes.begin(), processes.end(),
	     other_mem_fun(&visitor, &SystemVisitor::visitProcess));
	
    visitor.visitSystemAfter(this);
}

const map<symbol_t, expression_t> TimedAutomataSystem::getConstantValuation() const
{
    return constantValuation;
}

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
    if (currentTemplate == -1) {
	strncpy(path, "/nta/declaration", 256);
    } else {
	snprintf(path, 256, "/nta/template[%d]/declaration", currentTemplate + 1);
    }
}

void ContextVisitor::setContextParameters()
{
    snprintf(path, 256, "/nta/template[%d]/parameter", currentTemplate + 1);
}

void ContextVisitor::setContextInvariant(state_t &state)
{
    snprintf(path, 256, "/nta/template[%d]/location[%d]/label[@kind=\"invariant\"]", currentTemplate + 1, state.locNr + 1);
}

void ContextVisitor::setContextGuard(transition_t &transition)
{
    snprintf(path, 256, "/nta/template[%d]/transition[%d]/label[@kind=\"guard\"]", currentTemplate + 1, transition.nr + 1);
}

void ContextVisitor::setContextSync(transition_t &transition)
{
    snprintf(path, 256, "/nta/template[%d]/transition[%d]/label[@kind=\"synchronisation\"]", currentTemplate + 1, transition.nr + 1);
}

void ContextVisitor::setContextAssignment(transition_t &transition)
{
    snprintf(path, 256, "/nta/template[%d]/transition[%d]/label[@kind=\"assignment\"]", currentTemplate + 1, transition.nr + 1);
}

void ContextVisitor::setContextInstantiation()
{
    strncpy(path, "/nta/instantiation", 256);
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

char *ContextVisitor::get() const
{
    return strcpy(new char[strlen(path) + 1], path);
}

void ContextVisitor::handleWarning(expression_t expr, const char *msg)
{
    if (errorHandler) {
	errorHandler->setCurrentPath(this);	
	errorHandler->setCurrentPosition(expr.getPosition());
	errorHandler->handleWarning(msg);
    }
}

void ContextVisitor::handleError(expression_t expr, const char *msg)
{
    if (errorHandler) {
	errorHandler->setCurrentPath(this);	
	errorHandler->setCurrentPosition(expr.getPosition());
	errorHandler->handleError(msg);
    }

}
