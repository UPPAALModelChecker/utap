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

#include "print.hpp"

#include <stdexcept>
#include <vector>
#include <cassert>
#include <cstring>

using namespace UTAP;
using namespace Constants;

using std::vector;
using std::string;

DocumentBuilder::DocumentBuilder(Document& doc, std::vector<std::filesystem::path> paths):
    StatementBuilder{doc, std::move(paths)}
{}

/************************************************************
 * Variable and function declarations
 */
variable_t* DocumentBuilder::addVariable(type_t type, const std::string& name, expression_t init, position_t pos)
{
    if (currentFun != nullptr) {
        return document.add_variable_to_function(currentFun, frames.top(), type, name, init, pos);
    } else {
        return document.add_variable(getCurrentDeclarationBlock(), type, name, init, pos);
    }
}

bool DocumentBuilder::addFunction(type_t type, const std::string& name, position_t pos)
{
    return getCurrentDeclarationBlock()->add_function(type, name, pos, currentFun);
}

declarations_t* DocumentBuilder::getCurrentDeclarationBlock()
{
    return (currentTemplate != nullptr ? currentTemplate : &document.get_globals());
}

void DocumentBuilder::addSelectSymbolToFrame(const std::string& id, frame_t& frame, position_t pos)
{
    type_t type = typeFragments[0];
    typeFragments.pop();

    if (!type.is(CONSTANT)) {
        type = type.create_prefix(CONSTANT);
    }

    if (!type.is_scalar() && !type.is_integer()) {
        handle_error(TypeException{"$Scalar_set_or_integer_expected"});
    } else if (!type.is(RANGE)) {
        handle_error(TypeException{"$Range_expected"});
    } else {
        symbol_t uid;
        if (resolve(id, uid)) {
            handle_warning(ShadowsAVariableWarning(id));
        }
        frame.add_symbol(id, type, pos);
    }
}

/************************************************************
 * Gantt chart
 */

void DocumentBuilder::gantt_decl_begin(const char* name)
{
    currentGantt = std::make_unique<gantt_t>(name);
    push_frame(frame_t::create(frames.top()));
}

void DocumentBuilder::gantt_decl_select(const char* id) { addSelectSymbolToFrame(id, frames.top(), position); }

void DocumentBuilder::gantt_decl_end()
{
    currentGantt->parameters = frames.top();
    popFrame();
    document.add_gantt(getCurrentDeclarationBlock(), std::move(*currentGantt));
    currentGantt.reset();
}

void DocumentBuilder::gantt_entry_begin() { push_frame(frame_t::create(frames.top())); }

void DocumentBuilder::gantt_entry_select(const char* id) { addSelectSymbolToFrame(id, frames.top(), position); }

void DocumentBuilder::gantt_entry_end()
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
void DocumentBuilder::decl_progress(bool hasGuard)
{
    expression_t guard, measure;
    measure = fragments[0];
    fragments.pop();
    if (hasGuard) {
        guard = fragments[0];
        fragments.pop();
    }
    document.add_progress_measure(getCurrentDeclarationBlock(), guard, measure);
}

/********************************************************************
 * Process declarations
 */
void DocumentBuilder::proc_begin(const char* name, const bool isTA, const string& type, const string& mode)
{
    currentTemplate = document.find_dynamic_template(name);
    if (currentTemplate != nullptr) {
        /* check if parameters match */
        if (currentTemplate->parameters.get_size() != params.get_size()) {
            handle_error(TypeException{"Inconsistent parameters"});
        } else {
            for (size_t i = 0; i < params.get_size(); i++) {
                if (params[i].get_name() != currentTemplate->parameters[i].get_name() ||
                    params[i].get_type().get_kind() != currentTemplate->parameters[i].get_type().get_kind())
                    handle_error(TypeException{"Inconsistent parameters"});
            }
        }
        currentTemplate->is_defined = true;
    } else {
        if (frames.top().contains(name)) {
            handle_error(DuplicateDefinitionError(name));
        }
        // search if the given name is a name of LSC
        auto lsc_name_it = find(lscTemplateNames.begin(), lscTemplateNames.end(), string(name));
        if (isTA && (lsc_name_it == lscTemplateNames.end())) {  // TA
            currentTemplate = &document.add_template(name, params, position);
        } else {  // LSC
            currentTemplate = &document.add_template(name, params, position, false, type, mode);
        }
    }

    push_frame(currentTemplate->frame);
    params = frame_t::create();
}

void DocumentBuilder::proc_end()  // 1 ProcBody
{
    currentTemplate = nullptr;
    popFrame();
}

/**
 * Add a state to the current template. An invariant expression is
 * expected on and popped from the expression stack if \a hasInvariant
 * is true.
 */
void DocumentBuilder::proc_location(const char* name, bool hasInvariant, bool hasER)  // 1 expr
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
    currentTemplate->add_location(name, e, f, position);
}

void DocumentBuilder::proc_location_commit(const char* name)
{
    symbol_t uid;
    if (!resolve(name, uid) || !uid.get_type().is_location()) {
        handle_error(TypeException{"$Location_expected"});
    } else if (uid.get_type().is(URGENT)) {
        handle_error(TypeException{"$States_cannot_be_committed_and_urgent_at_the_same_time"});
    } else {
        uid.set_type(uid.get_type().create_prefix(COMMITTED, position));
    }
}

void DocumentBuilder::proc_location_urgent(const char* name)
{
    symbol_t uid;

    if (!resolve(name, uid) || !uid.get_type().is_location()) {
        handle_error(TypeException{"$Location_expected"});
    } else if (uid.get_type().is(COMMITTED)) {
        handle_error(TypeException{"$States_cannot_be_committed_and_urgent_at_the_same_time"});
    } else {
        uid.set_type(uid.get_type().create_prefix(URGENT, position));
    }
}

void DocumentBuilder::proc_branchpoint(const char* name) { currentTemplate->add_branchpoint(name, position); }

void DocumentBuilder::proc_location_init(const char* name)
{
    symbol_t uid;
    if (!resolve(name, uid) || !uid.get_type().is_location()) {
        handle_error(TypeException{"$Location_expected"});
    } else {
        currentTemplate->init = uid;
    }
}

void DocumentBuilder::proc_edge_begin(const char* from, const char* to, const bool control, const char* actname)
{
    symbol_t fid, tid;

    if (!resolve(from, fid) || (!fid.get_type().is_location() && !fid.get_type().is_branchpoint())) {
        handle_error(TypeException{"$No_such_location_or_branchpoint_(source)"});
        push_frame(frame_t::create(frames.top()));  // dummy frame for upcoming popFrame
    } else if (!resolve(to, tid) || (!tid.get_type().is_location() && !tid.get_type().is_branchpoint())) {
        handle_error(TypeException{"$No_such_location_or_branchpoint_(destination)"});
        push_frame(frame_t::create(frames.top()));  // dummy frame for upcoming popFrame
    } else {
        currentEdge = &currentTemplate->add_edge(fid, tid, control, actname);
        currentEdge->guard = make_constant(1);
        currentEdge->assign = make_constant(1);
        // default "probability" weight is 1.
        currentEdge->prob = make_constant(1);
        push_frame(currentEdge->select = frame_t::create(frames.top()));
    }
}

void DocumentBuilder::proc_edge_end(const char* from, const char* to) { popFrame(); }

void DocumentBuilder::proc_select(const char* id) { addSelectSymbolToFrame(id, currentEdge->select, position); }

void DocumentBuilder::proc_guard()
{
    if (currentEdge == nullptr) {
        handle_error(TypeException("Must be declared inside of an edge"));
        return;
    }

    currentEdge->guard = fragments[0];
    fragments.pop();
}

void DocumentBuilder::proc_sync(synchronisation_t type)
{
    if (currentEdge == nullptr) {
        handle_error(TypeException("Must be declared inside of an edge"));
        return;
    }

    currentEdge->sync = expression_t::create_sync(fragments[0], type, position);
    fragments.pop();
}

void DocumentBuilder::proc_update()
{
    if (currentEdge == nullptr) {
        handle_error(TypeException("Must be declared inside of an edge"));
        return;
    }

    currentEdge->assign = fragments[0];
    fragments.pop();
}

void DocumentBuilder::proc_prob()
{
    if (currentEdge == nullptr) {
        handle_error(TypeException("Must be declared inside of an edge"));
        return;
    }

    currentEdge->prob = fragments[0];
    fragments.pop();
}

/********************************************************************
 * System declaration
 */

void DocumentBuilder::instantiation_begin(const char* name, size_t parameters, const char* templ_name)
{
    /* Make sure this identifier is new.
     */
    if (frames.top().contains(name)) {
        handle_error(DuplicateDefinitionError(name));
    }

    /* Lookup symbol.
     */
    symbol_t id;
    if (!resolve(templ_name, id) ||
        (id.get_type().get_kind() != INSTANCE && id.get_type().get_kind() != LSC_INSTANCE)) {
        handle_error(TypeException{"$Not_a_template"});
    }

    /* Push parameters to frame stack.
     */
    frame_t frame = frame_t::create(frames.top());
    frame.add(params);
    push_frame(frame);
    params = frame_t::create();
}

void DocumentBuilder::instantiation_end(const char* name, size_t parameters, const char* templ_name, size_t arguments)
{
    /* Parameters are at the top of the frame stack.
     */
    frame_t params = frames.top();
    popFrame();
    assert(parameters == params.get_size());

    /* Lookup symbol. In case of failure, instantiationBegin already
     * reported the problem.
     */
    symbol_t id;
    if (resolve(templ_name, id) && (id.get_type().get_kind() == INSTANCE || id.get_type().get_kind() == LSC_INSTANCE)) {
        auto* old_instance = static_cast<instance_t*>(id.get_data());

        /* Check number of arguments. If too many arguments, pop the
         * rest.
         */
        size_t expected = id.get_type().size();
        if (arguments < expected) {
            handle_error(TypeException{"$Too_few_arguments"});
        } else if (arguments > expected) {
            handle_error(TypeException{"$Too_many_arguments"});
        } else {
            // Collect arguments from expression stack.
            auto exprs = vector<expression_t>(arguments);
            while (arguments > 0) {
                arguments--;
                exprs[arguments] = std::move(fragments[0]);
                fragments.pop();
            }

            // Create template composition.
            instance_t& new_instance = (id.get_type().get_kind() == INSTANCE)
                                           ? document.add_instance(name, *old_instance, params, exprs, position)
                                           : document.add_LSC_instance(name, *old_instance, params, exprs, position);

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
    type_t type = symbol.get_type();
    if (type.get_kind() != INSTANCE) {
        throw NotATemplateError(symbol.get_name());
    }
    if (type.size() > 0) {
        // FIXME: Check type of unbound parameters
    }
    auto& instance = *static_cast<instance_t*>(symbol.get_data());
    instance.templ->is_instantiated = true;
    document.add_process(instance, position);
    proc_priority(name);
}

void DocumentBuilder::process_list_end() {}

void DocumentBuilder::done() {}

void DocumentBuilder::before_update()
{
    document.set_before_update(fragments[0]);
    fragments.pop();
}

void DocumentBuilder::after_update()
{
    document.set_after_update(fragments[0]);
    fragments.pop();
}

/********************************************************************
 * Priority
 */

void DocumentBuilder::chan_priority_begin()
{
    document.begin_chan_priority(fragments[0]);
    fragments.pop();
}

void DocumentBuilder::chan_priority_add(char separator)
{
    document.add_chan_priority(separator, fragments[0]);
    fragments.pop();
}

void DocumentBuilder::chan_priority_default() { fragments.push(expression_t()); }

void DocumentBuilder::proc_priority_inc() { currentProcPriority++; }

void DocumentBuilder::proc_priority(const string& name)
{
    symbol_t symbol;
    if (!resolve(name, symbol)) {
        handle_error(NoSuchProcessError(name));
    } else {
        document.set_proc_priority(name, currentProcPriority);
    }
}

/**
 * Adds an instance line to the current template.
 */
void DocumentBuilder::proc_instance_line() { currentInstanceLine = &currentTemplate->add_instance_line(); }
/**
 * templ is true if the name of the instance contains parameters like
 * "Train(1)". Here, "Train" is the name of a template.
 *
 * Otherwise the name of the instance can be for example "Train1", where
 * "Train1" is a process that has been instantiated "Train1 = Train(1)".
 * In this case, we cannot check that "Train1" exists yet,
 * because the system declarations have not yet been parsed.
 */
void DocumentBuilder::instance_name(const char* name, bool templ)
{
    symbol_t uid;
    if (templ) {
        string instName = string(name);
        string templName = instName.substr(0, instName.find('('));  // std::cout << templName << std::endl;
        if (!resolve(templName, uid) || (uid.get_type().get_kind() != INSTANCE)) {
            handle_error(NotATemplateError(templName));
        }
    } else {
        if (resolve(string(name), uid) && (uid.get_type().get_kind() == INSTANCE)) {
            auto* t = static_cast<template_t*>(uid.get_data());
            if (t->parameters.get_size() > 0) {
                handle_error(TypeException{"$Wrong_number_of_arguments_in_instance_line_name"});
            }
        }
    }
    currentInstanceLine->uid =
        currentTemplate->frame.add_symbol(name, type_t::create_primitive(INSTANCE_LINE), position, currentInstanceLine);
}

void DocumentBuilder::instance_name_begin(const char* name)
{
    /* Push parameters to frame stack.
     */
    frame_t frame = frame_t::create(frames.top());
    frame.add(params);
    push_frame(frame);
    params = frame_t::create();
}

void DocumentBuilder::instance_name_end(const char* name, size_t arguments)
{
    auto i_name = std::ostringstream{};
    i_name << name;
    /* Parameters are at the top of the frame stack.
     */
    frame_t params = frames.top();
    popFrame();
    // assert(parameters == params.get_size());

    /* Lookup symbol. In case of failure, instance_name_begin already
     * reported the problem.
     */
    symbol_t id;
    if (resolve(name, id) && id.get_type().get_kind() == INSTANCE) {
        auto* old_instance = static_cast<instance_t*>(id.get_data());

        /* Check number of arguments. If too many arguments, pop the
         * rest.
         */
        auto expected = id.get_type().size();
        if (arguments < expected) {
            handle_error(TypeException{"$Too_few_arguments"});
        } else if (arguments > expected) {
            handle_error(TypeException{"$Too_many_arguments"});
        } else {
            // Collect arguments from expression stack.
            auto exprs = vector<expression_t>(arguments);
            while (arguments-- > 0) {
                exprs[arguments] = std::move(fragments[0]);
                fragments.pop();
            }
            i_name << '(' << infix(exprs, ",") << ')';
            instance_name(i_name.str().c_str());
            // Create template composition.
            currentInstanceLine->add_parameters(*old_instance, params, exprs);

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
void DocumentBuilder::proc_message(const char* from, const char* to, const int loc, const bool pch)
{
    symbol_t fid, tid;
    if (!resolve(from, fid) || !fid.get_type().is_instance_line()) {
        handle_error(TypeException{"$No_such_instance_line_(source)"});
    } else if (!resolve(to, tid) || !tid.get_type().is_instance_line()) {
        handle_error(TypeException{"$No_such_instance_line_(destination)"});
    } else {
        currentMessage = &currentTemplate->add_message(fid, tid, loc, pch);
    }
}

void DocumentBuilder::proc_message(synchronisation_t type)  // Label
{
    if (currentMessage != nullptr)
        currentMessage->label = expression_t::create_sync(fragments[0], type, position);
    fragments.pop();
}

/**
 * Add a condition to the current template.
 */
void DocumentBuilder::proc_condition(const vector<string>& anchors, const int loc, const bool pch, const bool hot)
{
    vector<symbol_t> v_anchorid;
    bool error = false;
    bool isHot = hot;

    for (const auto& anchor : anchors) {
        symbol_t anchorid;
        if (!resolve(anchor.c_str(), anchorid) || !anchorid.get_type().is_instance_line()) {
            handle_error(TypeException{"$No_such_instance_line_(anchor)"});
            error = true;
        } else if (!error) {
            v_anchorid.push_back(anchorid);
        }
    }
    if (pch && hot) {
        handle_warning(TypeException{"$In_the_prechart_all_conditions_are_cold"});
        isHot = false;
    }
    if (!error) {
        currentCondition = &currentTemplate->add_condition(v_anchorid, loc, pch, isHot);
        currentCondition->label = make_constant(1);
    }
}

void DocumentBuilder::proc_condition()
{
    if (currentCondition != nullptr)
        currentCondition->label = fragments[0];
    fragments.pop();
}

/**
 * Add an update to the current template.
 */
void DocumentBuilder::proc_LSC_update(const char* anchor, const int loc, const bool pch)
{
    symbol_t anchorid;

    if (!resolve(anchor, anchorid) || !anchorid.get_type().is_instance_line()) {
        handle_error(TypeException{"$No_such_instance_line_(anchor)"});
    } else {
        currentUpdate = &currentTemplate->add_update(anchorid, loc, pch);
        currentUpdate->label = make_constant(1);
    }
}

void DocumentBuilder::proc_LSC_update()  // Label
{
    if (currentUpdate != nullptr)
        currentUpdate->label = fragments[0];
    fragments.pop();
}

void DocumentBuilder::prechart_set(const bool pch) { currentTemplate->has_prechart = pch; }

void DocumentBuilder::decl_dynamic_template(const std::string& name)
{
    // Should be null, but error recovery can result in proc_end not being called
    currentTemplate = nullptr;
    /* check if name already exists */
    if (frames.top().contains(name)) {
        handle_error(DuplicateDefinitionError(name));
    }

    for (size_t i = 0; i < params.get_size(); i++) {
        if (!params[i].get_type().is_integer() && !params[i].get_type().isBoolean() &&
            !(params[i].get_type().is(REF) && params[i].get_type()[0].is(BROADCAST)))
            handle_error(TypeException{"Dynamic template parameters can either be boolean or integer and "
                                       "cannot be references"});
    }

    document.add_dynamic_template(name, params, position);

    params = frame_t::create();  // reset params
}

void DocumentBuilder::query_begin() { currentQuery = std::make_unique<query_t>(); }
void DocumentBuilder::query_formula(const char* formula, const char* location)
{
    if (formula != nullptr) {
        currentQuery->formula = formula;
    }
    if (location != nullptr) {
        currentQuery->location = location;
    }
}
void DocumentBuilder::query_comment(const char* comment)
{
    if (comment != nullptr) {
        currentQuery->comment = comment;
    }
}
void DocumentBuilder::query_options(const char* key, const char* value)
{
    if (key == nullptr) {
        handle_error(TypeException{"options tag found without attribute 'key'"});
    }
    currentQuery->options.push_back(option_t{key, value == nullptr ? "" : value});
}

void DocumentBuilder::expectation_begin() { currentExpectation = new expectation_t; }

void DocumentBuilder::expectation_end()
{
    currentQuery->expectation = *currentExpectation;
    delete currentExpectation;
    currentExpectation = nullptr;
}

void DocumentBuilder::expectation_value(const char* res, const char* type, const char* value)
{
    using namespace std::string_view_literals;
    expectation_type _type;
    if (type == nullptr) {
        _type = expectation_type::_ErrorValue;
    } else if (type == "probability"sv) {
        _type = expectation_type::Probability;
    } else if (type == "symbolic"sv) {
        _type = expectation_type::Symbolic;
    } else if (type == "value"sv) {
        _type = expectation_type::NumericValue;
    } else {
        _type = expectation_type::_ErrorValue;
    }
    if (res == nullptr) {
        currentExpectation->status = query_status_t::Unknown;
    } else if (res == "success"sv) {
        currentExpectation->status = query_status_t::True;
    } else if (res == "failure"sv) {
        currentExpectation->status = query_status_t::False;
    } else if (res == "maybe_true"sv) {
        currentExpectation->status = query_status_t::MaybeTrue;
    } else if (res == "maybe_false"sv) {
        currentExpectation->status = query_status_t::MaybeFalse;
    } else {
        currentExpectation->status = query_status_t::Unknown;
    }
    currentExpectation->value_type = _type;
    currentExpectation->value = value;
}

void DocumentBuilder::expect_resource(const char* type, const char* value, const char* unit)
{
    if (type == nullptr) {
        handle_error(TypeException{"missing name of resource in expectation"});
        return;
    }
    if (value == nullptr) {
        handle_error(TypeException{"missing value of resource in expectation"});
    }
    currentExpectation->resources.push_back(
        resource_t{type, value, unit == nullptr ? std::nullopt : std::make_optional(unit)});
}

void DocumentBuilder::query_results_begin() {}

void DocumentBuilder::query_results_end() { currentResults = nullptr; }

void DocumentBuilder::query_end()
{
    document.add_query(std::move(*currentQuery));
    currentQuery.reset();
}

void DocumentBuilder::model_option(const char* key, const char* value)
{
    if (key == nullptr) {
        handle_error(TypeException{"options tag found without attribute 'key'"});
    }
    document.get_options().emplace_back(key, value == nullptr ? "" : value);
}
