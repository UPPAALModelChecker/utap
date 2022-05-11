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

#include "utap/DocumentBuilder.hpp"

#include <stdexcept>
#include <vector>
#include <cassert>
#include <cstring>

using namespace UTAP;
using namespace Constants;

using std::vector;
using std::pair;
using std::make_pair;
using std::min;
using std::max;
using std::string;

DocumentBuilder::DocumentBuilder(Document& system, std::vector<std::filesystem::path> paths):
    StatementBuilder{system, std::move(paths)}
{}

/************************************************************
 * Variable and function declarations
 */
variable_t* DocumentBuilder::addVariable(type_t type, const std::string& name, expression_t init, position_t pos)
{
    if (currentFun) {
        return document.addVariableToFunction(currentFun, frames.top(), type, name, init, pos);
    } else {
        return document.addVariable(getCurrentDeclarationBlock(), type, name, init, pos);
    }
}

bool DocumentBuilder::addFunction(type_t type, const std::string& name, position_t pos)
{
    return getCurrentDeclarationBlock()->addFunction(type, name, pos, currentFun);
}

declarations_t* DocumentBuilder::getCurrentDeclarationBlock()
{
    return (currentTemplate ? currentTemplate : &document.getGlobals());
}

void DocumentBuilder::addSelectSymbolToFrame(const std::string& id, frame_t& frame, position_t pos)
{
    type_t type = typeFragments[0];
    typeFragments.pop();

    if (!type.is(CONSTANT)) {
        type = type.createPrefix(CONSTANT);
    }

    if (!type.isScalar() && !type.isInteger()) {
        handleError(TypeException{"$Scalar_set_or_integer_expected"});
    } else if (!type.is(RANGE)) {
        handleError(TypeException{"$Range_expected"});
    } else {
        symbol_t uid;
        if (resolve(id, uid)) {
            handleWarning(ShadowsAVariableWarning(id));
        }
        frame.addSymbol(id, type, pos);
    }
}

/************************************************************
 * Gantt chart
 */

void DocumentBuilder::ganttDeclStart(const char* name)
{
    currentGantt = std::make_unique<gantt_t>(name);
    pushFrame(frame_t::createFrame(frames.top()));
}

void DocumentBuilder::ganttDeclSelect(const char* id) { addSelectSymbolToFrame(id, frames.top(), position); }

void DocumentBuilder::ganttDeclEnd()
{
    currentGantt->parameters = frames.top();
    popFrame();
    document.addGantt(getCurrentDeclarationBlock(), std::move(*currentGantt));
    currentGantt.reset();
}

void DocumentBuilder::ganttEntryStart() { pushFrame(frame_t::createFrame(frames.top())); }

void DocumentBuilder::ganttEntrySelect(const char* id) { addSelectSymbolToFrame(id, frames.top(), position); }

void DocumentBuilder::ganttEntryEnd()
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
void DocumentBuilder::declProgress(bool hasGuard)
{
    expression_t guard, measure;
    measure = fragments[0];
    fragments.pop();
    if (hasGuard) {
        guard = fragments[0];
        fragments.pop();
    }
    document.addProgressMeasure(getCurrentDeclarationBlock(), guard, measure);
}

/********************************************************************
 * Process declarations
 */
void DocumentBuilder::procBegin(const char* name, const bool isTA, const string& type, const string& mode)
{
    currentTemplate = document.getDynamicTemplate(std::string(name));
    if (currentTemplate) {
        /* check if parameters match */
        if (currentTemplate->parameters.getSize() != params.getSize()) {
            handleError(TypeException{"Inconsistent parameters"});
        } else {
            for (size_t i = 0; i < params.getSize(); i++) {
                if (params[i].getName() != currentTemplate->parameters[i].getName() ||
                    params[i].getType().getKind() != currentTemplate->parameters[i].getType().getKind())
                    handleError(TypeException{"Inconsistent parameters"});
            }
        }
        currentTemplate->isDefined = true;
    } else {
        if (frames.top().getIndexOf(name) != -1) {
            handleError(DuplicateDefinitionError(name));
        }

        vector<string>::iterator result;

        // we search if the given name is a name of LSC
        result = find(lscTemplateNames.begin(), lscTemplateNames.end(), string(name));

        bool b = (!isTA) ? false : (result == lscTemplateNames.end());
        if (b)  // TA
        {
            currentTemplate = &document.addTemplate(name, params, position);
        } else  // LSC
        {
            currentTemplate = &document.addTemplate(name, params, position, b, type, mode);
        }
    }

    pushFrame(currentTemplate->frame);
    params = frame_t::createFrame();
}

void DocumentBuilder::procEnd()  // 1 ProcBody
{
    currentTemplate = NULL;
    popFrame();
}

/**
 * Add a state to the current template. An invariant expression is
 * expected on and popped from the expression stack if \a hasInvariant
 * is true.
 */
void DocumentBuilder::procState(const char* name, bool hasInvariant, bool hasER)  // 1 expr
{
    expression_t e, f;
    if (hasER) {
        f = fragments[0];
        fragments.pop();
    }
    if (hasInvariant) {
        e = fragments[0];
        fragments.pop();
    }
    currentTemplate->addLocation(name, e, f, position);
}

void DocumentBuilder::procStateCommit(const char* name)
{
    symbol_t uid;
    if (!resolve(name, uid) || !uid.getType().isLocation()) {
        handleError(TypeException{"$Location_expected"});
    } else if (uid.getType().is(URGENT)) {
        handleError(TypeException{"$States_cannot_be_committed_and_urgent_at_the_same_time"});
    } else {
        uid.setType(uid.getType().createPrefix(COMMITTED, position));
    }
}

void DocumentBuilder::procStateUrgent(const char* name)
{
    symbol_t uid;

    if (!resolve(name, uid) || !uid.getType().isLocation()) {
        handleError(TypeException{"$Location_expected"});
    } else if (uid.getType().is(COMMITTED)) {
        handleError(TypeException{"$States_cannot_be_committed_and_urgent_at_the_same_time"});
    } else {
        uid.setType(uid.getType().createPrefix(URGENT, position));
    }
}

void DocumentBuilder::procBranchpoint(const char* name) { currentTemplate->addBranchpoint(name, position); }

void DocumentBuilder::procStateInit(const char* name)
{
    symbol_t uid;
    if (!resolve(name, uid) || !uid.getType().isLocation()) {
        handleError(TypeException{"$Location_expected"});
    } else {
        currentTemplate->init = uid;
    }
}

void DocumentBuilder::procEdgeBegin(const char* from, const char* to, const bool control, const char* actname)
{
    symbol_t fid, tid;

    if (!resolve(from, fid) || (!fid.getType().isLocation() && !fid.getType().isBranchpoint())) {
        handleError(TypeException{"$No_such_location_or_branchpoint_(source)"});
        pushFrame(frame_t::createFrame(frames.top()));  // dummy frame for upcoming popFrame
    } else if (!resolve(to, tid) || (!tid.getType().isLocation() && !tid.getType().isBranchpoint())) {
        handleError(TypeException{"$No_such_location_or_branchpoint_(destination)"});
        pushFrame(frame_t::createFrame(frames.top()));  // dummy frame for upcoming popFrame
    } else {
        currentEdge = &currentTemplate->addEdge(fid, tid, control, actname);
        currentEdge->guard = makeConstant(1);
        currentEdge->assign = makeConstant(1);
        // default "probability" weight is 1.
        currentEdge->prob = makeConstant(1);
        pushFrame(currentEdge->select = frame_t::createFrame(frames.top()));
    }
}

void DocumentBuilder::procEdgeEnd(const char* from, const char* to) { popFrame(); }

void DocumentBuilder::procSelect(const char* id) { addSelectSymbolToFrame(id, currentEdge->select, position); }

void DocumentBuilder::procGuard()
{
    if (!currentEdge) {
        handleError(TypeException("Must be declared inside of an edge"));
        return;
    }

    currentEdge->guard = fragments[0];
    fragments.pop();
}

void DocumentBuilder::procSync(synchronisation_t type)
{
    if (!currentEdge) {
        handleError(TypeException("Must be declared inside of an edge"));
        return;
    }

    currentEdge->sync = expression_t::createSync(fragments[0], type, position);
    fragments.pop();
}

void DocumentBuilder::procUpdate()
{
    if (!currentEdge) {
        handleError(TypeException("Must be declared inside of an edge"));
        return;
    }

    currentEdge->assign = fragments[0];
    fragments.pop();
}

void DocumentBuilder::procProb()
{
    if (!currentEdge) {
        handleError(TypeException("Must be declared inside of an edge"));
        return;
    }

    currentEdge->prob = fragments[0];
    fragments.pop();
}

/********************************************************************
 * System declaration
 */

void DocumentBuilder::instantiationBegin(const char* name, size_t parameters, const char* templ_name)
{
    /* Make sure this identifier is new.
     */
    if (frames.top().getIndexOf(name) != -1) {
        handleError(DuplicateDefinitionError(name));
    }

    /* Lookup symbol.
     */
    symbol_t id;
    if (!resolve(templ_name, id) || (id.getType().getKind() != INSTANCE && id.getType().getKind() != LSCINSTANCE)) {
        handleError(TypeException{"$Not_a_template"});
    }

    /* Push parameters to frame stack.
     */
    frame_t frame = frame_t::createFrame(frames.top());
    frame.add(params);
    pushFrame(frame);
    params = frame_t::createFrame();
}

void DocumentBuilder::instantiationEnd(const char* name, size_t parameters, const char* templ_name, size_t arguments)
{
    /* Parameters are at the top of the frame stack.
     */
    frame_t params = frames.top();
    popFrame();
    assert(parameters == params.getSize());

    /* Lookup symbol. In case of failure, instantiationBegin already
     * reported the problem.
     */
    symbol_t id;
    if (resolve(templ_name, id) && (id.getType().getKind() == INSTANCE || id.getType().getKind() == LSCINSTANCE)) {
        instance_t* old_instance = static_cast<instance_t*>(id.getData());

        /* Check number of arguments. If too many arguments, pop the
         * rest.
         */
        size_t expected = id.getType().size();
        if (arguments < expected) {
            handleError(TypeException{"$Too_few_arguments"});
        } else if (arguments > expected) {
            handleError(TypeException{"$Too_many_arguments"});
        } else {
            /* Collect arguments from expression stack.
             */
            vector<expression_t> exprs(arguments);
            while (arguments) {
                arguments--;
                exprs[arguments] = fragments[0];
                fragments.pop();
            }

            /* Create template composition.
             */
            instance_t& new_instance = (id.getType().getKind() == INSTANCE)
                                           ? document.addInstance(name, *old_instance, params, exprs, position)
                                           : document.addLscInstance(name, *old_instance, params, exprs, position);

            /* Propagate information about restricted variables. The
             * variables used in arguments to restricted parameters of
             * old_instance are restricted in new_instance.
             *
             * REVISIT: Move to document.cpp?
             */
            std::set<symbol_t>& restricted = old_instance->restricted;
            for (size_t i = 0; i < expected; i++) {
                if (restricted.find(old_instance->parameters[i]) != restricted.end()) {
                    collectDependencies(new_instance.restricted, exprs[i]);
                }
            }
        }
    }
    fragments.pop(arguments);
}

// Adds process_t* pointer to system_line
// Checks for duplicate entries
void DocumentBuilder::process(const char* name)
{
    symbol_t symbol;
    if (!resolve(name, symbol)) {
        throw NoSuchProcessError(name);
    }
    type_t type = symbol.getType();
    if (type.getKind() != INSTANCE) {
        throw NotATemplateError(symbol.getName());
    }
    if (type.size() > 0) {
        // FIXME: Check type of unbound parameters
    }
    document.addProcess(*static_cast<instance_t*>(symbol.getData()), position);
    procPriority(name);
}

void DocumentBuilder::processListEnd() {}

void DocumentBuilder::done() {}

void DocumentBuilder::beforeUpdate()
{
    document.setBeforeUpdate(fragments[0]);
    fragments.pop();
}

void DocumentBuilder::afterUpdate()
{
    document.setAfterUpdate(fragments[0]);
    fragments.pop();
}

/********************************************************************
 * Priority
 */

void DocumentBuilder::beginChanPriority()
{
    document.beginChanPriority(fragments[0]);
    fragments.pop();
}

void DocumentBuilder::addChanPriority(char separator)
{
    document.addChanPriority(separator, fragments[0]);
    fragments.pop();
}

void DocumentBuilder::defaultChanPriority() { fragments.push(expression_t()); }

void DocumentBuilder::incProcPriority() { currentProcPriority++; }

void DocumentBuilder::procPriority(const string& name)
{
    symbol_t symbol;
    if (!resolve(name, symbol)) {
        handleError(NoSuchProcessError(name));
    } else {
        document.setProcPriority(name, currentProcPriority);
    }
}

/**
 * Adds an instance line to the current template.
 */
void DocumentBuilder::procInstanceLine() { currentInstanceLine = &currentTemplate->addInstanceLine(); }
/**
 * templ is true if the name of the instance contains parameters like
 * "Train(1)". Here, "Train" is the name of a template.
 *
 * Otherwise the name of the instance can be for example "Train1", where
 * "Train1" is a process that has been instantiated "Train1 = Train(1)".
 * In this case, we cannot check that "Train1" exists yet,
 * because the system declarations have not yet been parsed.
 */
void DocumentBuilder::instanceName(const char* name, bool templ)
{
    symbol_t uid;
    if (templ) {
        string instName = string(name);
        string templName = instName.substr(0, instName.find('('));  // std::cout << templName << std::endl;
        if (!resolve(templName, uid) || (uid.getType().getKind() != INSTANCE)) {
            handleError(NotATemplateError(templName));
        }
    } else {
        if (resolve(string(name), uid) && (uid.getType().getKind() == INSTANCE)) {
            template_t* t = static_cast<template_t*>(uid.getData());
            if (t->parameters.getSize() > 0) {
                handleError(TypeException{"$Wrong_number_of_arguments_in_instance_line_name"});
            }
        }
    }
    currentInstanceLine->uid =
        currentTemplate->frame.addSymbol(name, type_t::createPrimitive(INSTANCELINE), position, currentInstanceLine);
}

void DocumentBuilder::instanceNameBegin(const char* name)
{
    /* Push parameters to frame stack.
     */
    frame_t frame = frame_t::createFrame(frames.top());
    frame.add(params);
    pushFrame(frame);
    params = frame_t::createFrame();
}

void DocumentBuilder::instanceNameEnd(const char* name, size_t arguments)
{
    std::string i_name = std::string(name);
    vector<expression_t>::const_iterator itr;
    /* Parameters are at the top of the frame stack.
     */
    frame_t params = frames.top();
    popFrame();
    // assert(parameters == params.getSize());

    /* Lookup symbol. In case of failure, instanceNameBegin already
     * reported the problem.
     */
    symbol_t id;
    if (resolve(name, id) && id.getType().getKind() == INSTANCE) {
        instance_t* old_instance = static_cast<instance_t*>(id.getData());

        /* Check number of arguments. If too many arguments, pop the
         * rest.
         */
        size_t expected = id.getType().size();
        if (arguments < expected) {
            handleError(TypeException{"$Too_few_arguments"});
        } else if (arguments > expected) {
            handleError(TypeException{"$Too_many_arguments"});
        } else {
            /* Collect arguments from expression stack.
             */
            vector<expression_t> exprs(arguments);
            while (arguments) {
                arguments--;
                exprs[arguments] = fragments[0];
                fragments.pop();
            }
            i_name += '(';
            for (itr = exprs.begin(); itr != exprs.end(); ++itr) {
                if (itr != exprs.begin() && exprs.size() > 1) {
                    i_name += ',';
                }
                i_name += itr->toString();
            }
            i_name += ')';
            instanceName(i_name.c_str());  // std::cout << "instance line name: " << i_name << std::endl;
            /* Create template composition.
             */
            currentInstanceLine->addParameters(*old_instance, params, exprs);

            /* Propagate information about restricted variables. The
             * variables used in arguments to restricted parameters of
             * old_instance are restricted in new_instance.
             *
             * REVISIT: Move to document.cpp?
             */
            std::set<symbol_t>& restricted = old_instance->restricted;
            for (size_t i = 0; i < expected; i++) {
                if (restricted.find(old_instance->parameters[i]) != restricted.end()) {
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
void DocumentBuilder::procMessage(const char* from, const char* to, const int loc, const bool pch)
{
    symbol_t fid, tid;
    if (!resolve(from, fid) || !fid.getType().isInstanceLine()) {
        handleError(TypeException{"$No_such_instance_line_(source)"});
    } else if (!resolve(to, tid) || !tid.getType().isInstanceLine()) {
        handleError(TypeException{"$No_such_instance_line_(destination)"});
    } else {
        currentMessage = &currentTemplate->addMessage(fid, tid, loc, pch);
    }
}

void DocumentBuilder::procMessage(synchronisation_t type)  // Label
{
    if (currentMessage)
        currentMessage->label = expression_t::createSync(fragments[0], type, position);
    fragments.pop();
}

/**
 * Add a condition to the current template.
 */
void DocumentBuilder::procCondition(const vector<string>& anchors, const int loc, const bool pch, const bool hot)
{
    vector<symbol_t> v_anchorid;
    bool error = false;
    bool isHot = hot;

    for (const auto& anchor : anchors) {
        symbol_t anchorid;
        if (!resolve(anchor.c_str(), anchorid) || !anchorid.getType().isInstanceLine()) {
            handleError(TypeException{"$No_such_instance_line_(anchor)"});
            error = true;
        } else if (!error) {
            v_anchorid.push_back(anchorid);
        }
    }
    if (pch && hot) {
        handleWarning(TypeException{"$In_the_prechart_all_conditions_are_cold"});
        isHot = false;
    }
    if (!error) {
        currentCondition = &currentTemplate->addCondition(v_anchorid, loc, pch, isHot);
        currentCondition->label = makeConstant(1);
    }
}

void DocumentBuilder::procCondition()
{
    if (currentCondition)
        currentCondition->label = fragments[0];
    fragments.pop();
}

/**
 * Add an update to the current template.
 */
void DocumentBuilder::procLscUpdate(const char* anchor, const int loc, const bool pch)
{
    symbol_t anchorid;

    if (!resolve(anchor, anchorid) || !anchorid.getType().isInstanceLine()) {
        handleError(TypeException{"$No_such_instance_line_(anchor)"});
    } else {
        currentUpdate = &currentTemplate->addUpdate(anchorid, loc, pch);
        currentUpdate->label = makeConstant(1);
    }
}

void DocumentBuilder::procLscUpdate()  // Label
{
    if (currentUpdate)
        currentUpdate->label = fragments[0];
    fragments.pop();
}

void DocumentBuilder::hasPrechart(const bool pch) { currentTemplate->hasPrechart = pch; }

void DocumentBuilder::declDynamicTemplate(const std::string& name)
{
    // Should be null, but error recovery can result in procEnd not being called
    currentTemplate = nullptr;
    /* check if name already exists */
    if (frames.top().getIndexOf(name) != -1) {
        handleError(DuplicateDefinitionError(name));
    }

    for (size_t i = 0; i < params.getSize(); i++) {
        if (!params[i].getType().isInteger() && !params[i].getType().isBoolean() &&
            !(params[i].getType().is(REF) && params[i].getType()[0].is(BROADCAST)))
            handleError(TypeException{"Dynamic template parameters can either be boolean or integer and "
                                      "cannot be references"});
    }

    document.addDynamicTemplate(name, params, position);

    params = frame_t::createFrame();  // reset params
}

void DocumentBuilder::queryBegin() { currentQuery = std::make_unique<query_t>(); }
void DocumentBuilder::queryFormula(const char* formula, const char* location)
{
    if (formula) {
        currentQuery->formula = formula;
    }
    if (location) {
        currentQuery->location = location;
    }
}
void DocumentBuilder::queryComment(const char* comment)
{
    if (comment) {
        currentQuery->comment = comment;
    }
}
void DocumentBuilder::queryOptions(const char* key, const char* value)
{
    if (key == nullptr) {
        handleError(TypeException{"options tag found without attribute 'key'"});
    }
    currentQuery->options.push_back(option_t{key, value == nullptr ? "" : value});
}

void DocumentBuilder::expectationBegin() { currentExpectation = new expectation_t; }

void DocumentBuilder::expectationEnd()
{
    currentQuery->expectation = *currentExpectation;
    delete currentExpectation;
    currentExpectation = nullptr;
}

void DocumentBuilder::expectationValue(const char* res, const char* type, const char* value)
{
    expectation_type _type;
    if (!type) {
        _type = expectation_type::_ErrorValue;
    } else if (strcmp(type, "probability") == 0) {
        _type = expectation_type::Probability;
    } else if (strcmp(type, "symbolic")) {
        _type = expectation_type::Symbolic;
    } else if (strcmp(type, "value")) {
        _type = expectation_type::NumericValue;
    } else {
        _type = expectation_type::_ErrorValue;
    }
    if (res == nullptr) {
        currentExpectation->status = query_status_t::Unknown;
    } else if (strcmp(res, "success") == 0) {
        currentExpectation->status = query_status_t::True;
    } else if (strcmp(res, "failure")) {
        currentExpectation->status = query_status_t::False;
    } else if (strcmp(res, "maybe_true") == 0) {
        currentExpectation->status = query_status_t::MaybeTrue;
    } else if (strcmp(res, "maybe_false") == 0) {
        currentExpectation->status = query_status_t::MaybeFalse;
    } else {
        currentExpectation->status = query_status_t::Unknown;
    }
    currentExpectation->value_type = _type;
    currentExpectation->value = value;
}

void DocumentBuilder::expectResource(const char* type, const char* value, const char* unit)
{
    if (type == nullptr) {
        handleError(TypeException{"missing name of resource in expectation"});
        return;
    }
    if (value == nullptr) {
        handleError(TypeException{"missing value of resource in expectation"});
    }
    currentExpectation->resources.push_back(
        resource_t{type, value, unit == nullptr ? std::nullopt : std::make_optional(unit)});
}

void DocumentBuilder::queryResultsBegin() {}

void DocumentBuilder::queryResultsEnd() { currentResults = nullptr; }

void DocumentBuilder::queryEnd()
{
    document.addQuery(std::move(*currentQuery));
    currentQuery.reset();
}

void DocumentBuilder::modelOption(const char* key, const char* value)
{
    if (key == nullptr) {
        handleError(TypeException{"options tag found without attribute 'key'"});
    }
    document.getOptions().emplace_back(key, value == nullptr ? "" : value);
}
