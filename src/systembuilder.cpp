// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-

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

#include <vector>
#include <climits>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <cassert>
#include <cinttypes>
#include <stdexcept>
#include <sstream>
#include <boost/tuple/tuple.hpp>

using namespace UTAP;
using namespace Constants;

using std::vector;
using std::pair;
using std::make_pair;
using std::min;
using std::max;
using std::string;

SystemBuilder::SystemBuilder(TimedAutomataSystem *_system)
    : StatementBuilder(_system)
{
    currentEdge = NULL;
    currentGantt = NULL;
    currentMessage = NULL;
    currentCondition = NULL;
    currentUpdate = NULL;
    currentInstanceLine = NULL;
    currentIODecl = NULL;
    currentProcPriority = 0;
    currentQuery = NULL;
};

/************************************************************
 * Variable and function declarations
 */
variable_t *SystemBuilder::addVariable(type_t type, const char*  name,
                                        expression_t init)
{
    if (currentFun)
    {
        return system->addVariableToFunction(currentFun, frames.top(), type, name, init);
    }
    else
    {
        return system->addVariable(getCurrentDeclarationBlock(), type, name, init);
    }
}

bool SystemBuilder::addFunction(type_t type, const char* name)
{
    return getCurrentDeclarationBlock()->addFunction(type, name, currentFun);
}

declarations_t *SystemBuilder::getCurrentDeclarationBlock()
{
    return (currentTemplate ? currentTemplate : &system->getGlobals());
}

void SystemBuilder::addSelectSymbolToFrame(const char *id, frame_t& frame)
{
    type_t type = typeFragments[0];
    typeFragments.pop();

    if (!type.is(CONSTANT))
    {
        type = type.createPrefix(CONSTANT);
    }

    if (!type.isScalar() && !type.isInteger())
    {
        handleError("$Scalar_set_or_integer_expected");
    }
    else if (!type.is(RANGE))
    {
        handleError("$Range_expected");
    }
    else
    {
        symbol_t uid;
        if (resolve(id, uid))
        {
            boost::format w = boost::format("%1% $shadows_a_variable") % id;
            handleWarning(w.str());
        }
        frame.addSymbol(id, type);
    }
}

/************************************************************
 * Gantt chart
 */

void SystemBuilder::ganttDeclStart(const char* name)
{
    currentGantt = new gantt_t(name);
    pushFrame(frame_t::createFrame(frames.top()));
}

void SystemBuilder::ganttDeclSelect(const char *id)
{
    addSelectSymbolToFrame(id, frames.top());
}

void SystemBuilder::ganttDeclEnd()
{
    currentGantt->parameters = frames.top();
    popFrame();
    system->addGantt(getCurrentDeclarationBlock(), *currentGantt);
    delete currentGantt;
    currentGantt = NULL;
}

void SystemBuilder::ganttEntryStart()
{
    pushFrame(frame_t::createFrame(frames.top()));
}

void SystemBuilder::ganttEntrySelect(const char *id)
{
    addSelectSymbolToFrame(id, frames.top());
}

void SystemBuilder::ganttEntryEnd()
{
    ganttmap_t gm;
    gm.parameters = frames.top();
    gm.predicate = fragments[1];
    gm.mapping = fragments[0];
    fragments.pop(2);
    popFrame();
    currentGantt->mapping.push_back(gm);
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
 * Process declarations
 */
void SystemBuilder::procBegin(const char* name, const bool isTA,
        const string type, const string mode)
{
    currentTemplate = system->getDynamicTemplate (std::string(name));
    if (currentTemplate) {
/* check if parameters match */
        if (currentTemplate->parameters.getSize () != params.getSize ()) {
            handleError("Inconsistent parameters");
        }
        else {
            for(size_t i=0;i<params.getSize ();i++) {
                if (params[i].getName () != currentTemplate->parameters[i].getName () || params[i].getType ().getKind() != currentTemplate->parameters[i].getType ().getKind ())
                    handleError("Inconsistent parameters");
            }

        }
        currentTemplate->isDefined = true;
    }
    else {

        if (frames.top().getIndexOf(name) != -1)
        {
            boost::format err = boost::format("$Duplicate_definition_of %1%") % name;
            handleError(err.str());
        }

        vector<string>::iterator result;

        //we search if the given name is a name of LSC
        result = find( lscTemplateNames.begin(), lscTemplateNames.end(), string(name));

        bool b = (!isTA)? false : (result == lscTemplateNames.end());
        if (b) //TA
        {
            currentTemplate = &system->addTemplate(name, params);
        }
        else //LSC
        {
            currentTemplate = &system->addTemplate(name, params, b, type, mode);
        }
    }

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
void SystemBuilder::procState(const char* name, bool hasInvariant, bool hasER) // 1 expr
{
    expression_t e,f;
    if (hasER)
    {
        f = fragments[0];
        fragments.pop();
    }
    if (hasInvariant)
    {
        e = fragments[0];
        fragments.pop();
    }
    currentTemplate->addLocation(name, e, f);
}

void SystemBuilder::procStateCommit(const char* name)
{
    symbol_t uid;
    if (!resolve(name, uid) || !uid.getType().isLocation())
    {
        handleError("$Location_expected");
    }
    else if (uid.getType().is(URGENT))
    {
        handleError("$States_cannot_be_committed_and_urgent_at_the_same_time");
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
        handleError("$Location_expected");
    }
    else if (uid.getType().is(COMMITTED))
    {
        handleError("$States_cannot_be_committed_and_urgent_at_the_same_time");
    }
    else
    {
        uid.setType(uid.getType().createPrefix(URGENT, position));
    }
}

void SystemBuilder::procBranchpoint(const char* name)
{
    currentTemplate->addBranchpoint(name);
}

void SystemBuilder::procStateInit(const char* name)
{
    symbol_t uid;
    if (!resolve(name, uid) || !uid.getType().isLocation())
    {
        handleError("$Location_expected");
    }
    else
    {
        currentTemplate->init = uid;
    }
}

void SystemBuilder::procEdgeBegin(const char* from, const char* to, const bool control, const char* actname)
{
    symbol_t fid, tid;

    if (!resolve(from, fid) || (!fid.getType().isLocation() && !fid.getType().isBranchpoint()))
    {
        handleError("$No_such_location_or_branchpoint_(source)");
        pushFrame(frame_t::createFrame(frames.top())); // dummy frame for upcoming popFrame
    }
    else if (!resolve(to, tid) || (!tid.getType().isLocation() && !tid.getType().isBranchpoint()))
    {
        handleError("$No_such_location_or_branchpoint_(destination)");
        pushFrame(frame_t::createFrame(frames.top())); // dummy frame for upcoming popFrame
    }
    else
    {
        currentEdge = &currentTemplate->addEdge(fid, tid, control, actname);
        currentEdge->guard = makeConstant(1);
        currentEdge->assign = makeConstant(1);
#ifdef ENABLE_PROB
        // default "probability" weight is 1.
        currentEdge->prob = makeConstant(1);
#endif
        pushFrame(currentEdge->select = frame_t::createFrame(frames.top()));
    }
}

void SystemBuilder::procEdgeEnd(const char* from, const char* to)
{
    popFrame();
}

void SystemBuilder::procSelect(const char *id)
{
    addSelectSymbolToFrame(id, currentEdge->select);
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


void SystemBuilder::procProb()
{
#ifdef ENABLE_PROB
    currentEdge->prob = fragments[0];
#endif
    fragments.pop();
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
        boost::format err = boost::format("$Duplicate_definition_of %1%") % name;
        handleError(err.str());
    }

    /* Lookup symbol.
     */
    symbol_t id;
    if (!resolve(templ_name, id) || (id.getType().getKind() != INSTANCE
            && id.getType().getKind() != LSCINSTANCE))
    {
        handleError("$Not_a_template");
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
    frame_t pars = frames.top();
    popFrame();
    assert(parameters == pars.getSize());

    /* Lookup symbol. In case of failure, instantiationBegin already
     * reported the problem.
     */
    symbol_t id;
    if (resolve(templ_name, id) &&
            (id.getType().getKind() == INSTANCE||id.getType().getKind() == LSCINSTANCE))
    {
        instance_t *old_instance = static_cast<instance_t*>(id.getData());

        /* Check number of arguments. If too many arguments, pop the
         * rest.
         */
        size_t expected = id.getType().size();
        if (arguments < expected)
        {
            handleError("$Too_few_arguments");
        }
        else if (arguments > expected)
        {
            handleError("$Too_many_arguments");
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
            instance_t &new_instance = (id.getType().getKind() == INSTANCE) ?
                    system->addInstance(name, *old_instance, pars, exprs) :
                    system->addLscInstance(name, *old_instance, pars, exprs);

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
// Checks for duplicate entries
void SystemBuilder::process(const char* name)
{
    symbol_t symbol;
    if (!resolve(name, symbol))
    {
        throw TypeException(boost::format("$No_such_process: %1%") % name);
    }
    type_t type = symbol.getType();
    if (type.getKind() != INSTANCE)
    {
        throw TypeException(boost::format("$Not_a_template: %1%") % symbol.getName());
    }
    if (type.size() > 0)
    {
        // FIXME: Check type of unbound parameters
    }
    system->addProcess(*static_cast<instance_t*>(symbol.getData()));
    procPriority(name);
}

void SystemBuilder::processListEnd()
{
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

void SystemBuilder::beginChanPriority()
{
    system->beginChanPriority(fragments[0]);
    fragments.pop();
}

void SystemBuilder::addChanPriority(char separator)
{
    system->addChanPriority(separator, fragments[0]);
    fragments.pop();
}

void SystemBuilder::defaultChanPriority()
{
    fragments.push(expression_t());
}

void SystemBuilder::incProcPriority()
{
    currentProcPriority++;
}

void SystemBuilder::procPriority(const char* name)
{
    symbol_t symbol;
    if (!resolve(name, symbol))
    {
        boost::format err = boost::format("$No_such_process: %1%") % name;
        handleError(err.str());
    }
    else
    {
        system->setProcPriority(name, currentProcPriority);
    }
}

/**
 * Adds an instance line to the current template.
 */
void SystemBuilder::procInstanceLine()
{
    currentInstanceLine = &currentTemplate->addInstanceLine();
}
/**
 * templ is true if the name of the instance contains parameters like
 * "Train(1)". Here, "Train" is the name of a template.
 *
 * Otherwise the name of the instance can be for example "Train1", where
 * "Train1" is a process that has been instantiated "Train1 = Train(1)".
 * In this case, we cannot check that "Train1" exists yet,
 * because the system declarations have not yet been parsed.
 */
void SystemBuilder::instanceName(const char* name, bool templ)
{
    symbol_t uid;
    if (templ)
    {
        string instName = string(name);
        string templName = instName.substr(0, instName.find('(')); // std::cout << templName << std::endl;
        if (!resolve(templName, uid) || (uid.getType().getKind() != INSTANCE))
        {
            handleError("$Not_a_template");
        }
    }
    else
    {
        if (resolve(string(name), uid) && (uid.getType().getKind() == INSTANCE))
        {
            template_t* t = static_cast<template_t*>(uid.getData());
            if (t->parameters.getSize() > 0)
            {
                handleError("$Wrong_number_of_arguments_in_instance_line_name");
            }
        }
    }
    currentInstanceLine->uid = currentTemplate->frame.addSymbol(
            name, type_t::createPrimitive(INSTANCELINE), currentInstanceLine);
}

void SystemBuilder::instanceNameBegin(const char* name)
{
    /* Push parameters to frame stack.
     */
    frame_t frame = frame_t::createFrame(frames.top());
    frame.add(params);
    pushFrame(frame);
    params = frame_t::createFrame();
}

void SystemBuilder::instanceNameEnd(const char *name, size_t arguments)
{
    std::string i_name = std::string(name);
    vector<expression_t>::const_iterator itr;
    /* Parameters are at the top of the frame stack.
     */
    frame_t pars = frames.top();
    popFrame();
    //assert(parameters == pars.getSize());

    /* Lookup symbol. In case of failure, instanceNameBegin already
     * reported the problem.
     */
    symbol_t id;
    if (resolve(name, id) && id.getType().getKind() == INSTANCE)
    {
        instance_t *old_instance = static_cast<instance_t*>(id.getData());

        /* Check number of arguments. If too many arguments, pop the
         * rest.
         */
        size_t expected = id.getType().size();
        if (arguments < expected)
        {
            handleError("$Too_few_arguments");
        }
        else if (arguments > expected)
        {
            handleError("$Too_many_arguments");
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
            i_name += '(';
            for (itr = exprs.begin(); itr != exprs.end(); ++itr)
            {
                if (itr != exprs.begin() && exprs.size() > 1)
                {
                    i_name += ',';
                }
                i_name += itr->toString();
            }
            i_name += ')';
            instanceName(i_name.c_str()); //std::cout << "instance line name: " << i_name << std::endl;
            /* Create template composition.
             */
            currentInstanceLine->addParameters(*old_instance, pars, exprs);

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
                    collectDependencies(currentInstanceLine->restricted, exprs[i]);
                }
            }
        }
    }
    fragments.pop(arguments);
}


/**
 * Add a message to the current template.
 */
void SystemBuilder::procMessage(const char* from, const char* to, const int loc, const bool pch){
    symbol_t fid, tid;
    if (!resolve(from, fid) || !fid.getType().isInstanceLine())
    {
        handleError("$No_such_instance_line_(source)");
    }
    else if (!resolve(to, tid) || !tid.getType().isInstanceLine())
    {
        handleError("$No_such_instance_line_(destination)");
    }
    else
    {
        currentMessage = &currentTemplate->addMessage(fid, tid, loc, pch);
    }
}

void SystemBuilder::procMessage(synchronisation_t type) //Label
{
    if (currentMessage)
        currentMessage->label = expression_t::createSync(fragments[0], type, position);
    fragments.pop();
}

/**
 * Add a condition to the current template.
 */
void SystemBuilder::procCondition(const vector<char*> anchors, const int loc,
        const bool pch, const bool hot){
    symbol_t anchorid;
    char* anchor;
    vector<symbol_t> v_anchorid;
    bool error=false;
    bool isHot = hot;

    for (unsigned int i(0);i<anchors.size();++i){
        anchor = anchors[i];
        if (!resolve(anchor, anchorid) || !anchorid.getType().isInstanceLine())
        {
            handleError("$No_such_instance_line_(anchor)");
            error = true;
        }
        else if (!error){
            v_anchorid.push_back(anchorid);
        }
    }
    if (pch && hot)
    {
        handleWarning("$In_the_prechart_all_conditions_are_cold");
        isHot = false;
    }
    if (!error)
    {
        currentCondition = &currentTemplate->addCondition(v_anchorid, loc, pch, isHot);
        currentCondition->label = makeConstant(1);
    }
}

void SystemBuilder::procCondition()
{
    if (currentCondition)
        currentCondition->label = fragments[0];
    fragments.pop();
}

/**
 * Add an update to the current template.
 */
void SystemBuilder::procLscUpdate(const char* anchor, const int loc, const bool pch)
{
    symbol_t anchorid;

    if (!resolve(anchor, anchorid) || !anchorid.getType().isInstanceLine())
    {
        handleError("$No_such_instance_line_(anchor)");
    }
    else
    {
        currentUpdate = &currentTemplate->addUpdate(anchorid, loc, pch);
        currentUpdate->label = makeConstant(1);
    }
}

void SystemBuilder::procLscUpdate() //Label
{
    if (currentUpdate)
        currentUpdate->label = fragments[0];
    fragments.pop();
}

void SystemBuilder::hasPrechart(const bool pch){
    currentTemplate->hasPrechart = pch;
}


void SystemBuilder::exprSync(Constants::synchronisation_t type)
{
    if (!currentIODecl)
    {
        currentIODecl = system->addIODecl();
    }

    switch(type)
    {
    case SYNC_BANG:
        currentIODecl->outputs.push_back(fragments[0]);
        break;
    case SYNC_QUE:
        currentIODecl->inputs.push_back(fragments[0]);
        break;
    case SYNC_CSP:
        currentIODecl->csp.push_back(fragments[0]);
        break;
    }

    fragments.pop();
}

void SystemBuilder::declIO(const char* name, int nbParam, int nbSync)
{
    assert(currentIODecl);

    currentIODecl->instanceName = name;
    currentIODecl->param.resize(nbParam);
    for(int i = 0; i < nbParam; ++i)
    {
        currentIODecl->param[i] = fragments[nbParam-i-1];
    }
    fragments.pop(nbParam);
    assert(currentIODecl->inputs.size() + currentIODecl->outputs.size() + currentIODecl->csp.size() == size_t(nbSync));
    currentIODecl = NULL;
}

void SystemBuilder::declDynamicTemplate(const std::string& name)
{
    assert(!currentTemplate);
    /* check if name already exists */
    if (frames.top().getIndexOf(name) != -1)
    {
        boost::format err = boost::format("$Duplicate_definition_of %1%") % name;
        handleError(err.str());
    }

    for (size_t i = 0; i<params.getSize(); ++i)
        if (!params[i].getType().isInteger() &&
            !params[i].getType().isBoolean() &&
            !(params[i].getType().is(REF) &&
              params[i].getType()[0].is(BROADCAST)))
            handleError("Parameters to a dynamic template must be either booleans or integers and cannot be references");

    system->addDynamicTemplate(name,params);

    params = frame_t::createFrame(); //reset params
}

void SystemBuilder::queryBegin() {
    currentQuery = new query_t;
}

void SystemBuilder::queryFormula(const char* formula, const char* location)
{
    if (formula) {
        currentQuery->formula = formula;
    }
    if (location) {
        currentQuery->location = location;
    }
}

void SystemBuilder::queryComment(const char* comment)
{
    if (comment) {
        currentQuery->comment = comment;
    }
}
void SystemBuilder::queryEnd()
{
    system->addQuery(*currentQuery);
    delete currentQuery;
    currentQuery = NULL;
}
