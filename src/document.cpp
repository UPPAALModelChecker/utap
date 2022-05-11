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

#include "utap/document.h"

#include "utap/builder.h"
#include "utap/statement.h"

#include <functional>  // std::bind
#include <sstream>
#include <stack>
#include <cassert>
#include <cstring>

#ifdef __MINGW32__
#include <windows.h>
#elif defined(__linux__) || defined(__APPLE__)
#include <dlfcn.h>
#endif

using namespace UTAP;
using namespace Constants;

using std::bind;
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
using std::ostream;
using std::deque;

using namespace std::placeholders;  // _1, _2, etc for std::bind

static const char* const unsupported = "Internal error: Feature not supported in this mode.";
static const char* const invalid_type = "$Invalid_type";

string state_t::toString() const
{
    std::string str = "LOCATION (";
    str += uid.getName() + ", " + invariant.toString() + ")";
    return str;
}

string edge_t::toString() const
{
    std::string str = "EDGE (" + src->toString() + " " + dst->toString() + ")\n";
    str += "\t" + guard.toString() + ", " + sync.toString() + ", " + assign.toString();
    return str;
}

string function_t::toString() const
{
    string str = "";
    string type = uid.getType().get(0).toDeclarationString();  // return type
    str += type + " " + uid.getName();
    str += "(";
    for (uint32_t i = 1; i < uid.getType().size(); ++i)  // parameters
    {
        if (!uid.getType().getLabel(i).empty()) {
            str += uid.getType().get(i).toDeclarationString();
            str += " ";
            str += uid.getType().getLabel(i);
            str += ", ";
        }
    }
    if (uid.getType().size() > 1)
        str = str.substr(0, str.size() - 2);
    str += ")\n{\n";

    for (auto& variable : variables) {
        str += "    " + variable.toString();
        str += ";\n";
    }
    str += body->toString(INDENT);
    str += "}";
    return str;
}

string variable_t::toString() const
{
    string str = "";
    string type = "";
    if (uid.getType().isArray()) {
        type = uid.getType().toDeclarationString();
        size_t i = type.find('[');
        str += type.substr(0, (int)i);
        str += " ";
        str += uid.getName();
        str += type.substr((int)i, type.size() - (int)i);
    } else {
        str += uid.getType().toDeclarationString() + " " + uid.getName();
    }
    if (!expr.empty()) {
        str += " = " + expr.toString();
    }
    return str;
}

bool declarations_t::addFunction(type_t type, string name, position_t pos, function_t*& fun)
{
    bool duplicate = frame.getIndexOf(name) != -1;
    fun = &functions.emplace_back();
    fun->uid = frame.addSymbol(name, type, pos, fun);  // Add symbol
    return !duplicate;
}

string declarations_t::toString(bool global) const
{
    string str = "";
    str += getConstants();
    str += "\n";
    str += getTypeDefinitions();
    str += "\n";
    str += getVariables(global);
    str += "\n";
    str += getFunctions();
    return str;
}

string declarations_t::getConstants() const
{
    auto str = string{};
    if (!variables.empty()) {
        bool first = true;
        for (auto& variable : variables) {
            if (variable.uid.getType().getKind() == CONSTANT) {
                if (first) {
                    str = "// constants\n";
                    first = false;
                }
                str += variable.toString();
                str += ";\n";
            }
        }
    }
    return str;
}

string declarations_t::getTypeDefinitions() const
{
    string str = "";
    // type definitions
    bool first = true;
    for (auto& symbol : frame) {
        if (symbol.getType().getKind() == TYPEDEF) {
            if (first) {
                str += "// type definitions\n";
                first = false;
            }
            str += symbol.getType().toDeclarationString() + ";\n";
        }
    }
    return str;
}

string declarations_t::getVariables(bool global) const
{
    list<variable_t>::const_iterator v_itr = variables.begin();
    string str = "";
    int i = 0;
    // variables
    if (!variables.empty()) {
        while (v_itr != variables.end()) {
            if (i == 0) {
                str += "// variables\n";
                i++;
            }
            if (v_itr->uid.getType().getKind() != CONSTANT) {
                str += v_itr->toString();
                str += ";\n";
            }
            ++v_itr;
        }
    }
    return str;
}

string declarations_t::getFunctions() const
{
    list<function_t>::const_iterator f_itr;
    string str = "";
    // functions
    if (!functions.empty()) {
        str += "// functions\n";
        for (f_itr = functions.begin(); f_itr != functions.end(); ++f_itr) {
            str += f_itr->toString();
            str += "\n\n";
        }
    }
    return str;
}

std::string instance_t::writeMapping() const
{
    std::string str = "";
    std::map<symbol_t, expression_t>::const_iterator itr;
    for (itr = mapping.begin(); itr != mapping.end(); ++itr) {
        str += itr->first.getName() + " = " + itr->second.toString() + "\n";
    }
    return str;
}

std::string instance_t::writeParameters() const
{
    std::string str = "";
    auto b = std::begin(parameters), e = std::end(parameters);
    if (b != e) {
        str += b->getType().toDeclarationString() + " " + b->getName();
        while (++b != e)
            str += ", " + b->getType().toDeclarationString() + " " + b->getName();
    }
    return str;
}

std::string instance_t::writeArguments() const
{
    std::string str = "";
    auto b = std::begin(parameters), e = std::end(parameters);
    if (b != e) {
        auto itr = mapping.find(*b);
        assert(itr != std::end(mapping));
        str += itr->second.toString();
        while (++b != e) {
            itr = mapping.find(*b);
            assert(itr != std::end(mapping));
            str += ", " + itr->second.toString();
        }
    }
    return str;
}

state_t& template_t::addLocation(const string& name, expression_t inv, expression_t er, position_t pos)
{
    bool duplicate = frame.getIndexOf(name) != -1;
    state_t& state = states.emplace_back();
    state.uid = frame.addSymbol(name, type_t::createPrimitive(LOCATION), pos, &state);
    state.locNr = states.size() - 1;
    state.invariant = inv;
    state.exponentialRate = er;
    if (duplicate) {
        throw DuplicateDefinitionError(name);
    }
    return state;
}

// FIXME: like for unnamed locations, a name is autegenerated
// this name may conflict with user-defined names
branchpoint_t& template_t::addBranchpoint(const string& name, position_t pos)
{
    bool duplicate = frame.getIndexOf(name) != -1;
    auto& branchpoint = branchpoints.emplace_back();
    branchpoint.uid = frame.addSymbol(name, type_t::createPrimitive(BRANCHPOINT), pos, &branchpoint);
    branchpoint.bpNr = branchpoints.size() - 1;
    if (duplicate) {
        throw DuplicateDefinitionError(name);
    }
    return branchpoint;
}

edge_t& template_t::addEdge(symbol_t src, symbol_t dst, bool control, string actname)
{
    int32_t nr = edges.empty() ? 0 : edges.back().nr + 1;
    edges.push_back(edge_t());
    if (src.getType().isLocation()) {
        edges.back().src = static_cast<state_t*>(src.getData());
        edges.back().srcb = 0;
    } else {
        edges.back().src = 0;
        edges.back().srcb = static_cast<branchpoint_t*>(src.getData());
    }
    if (dst.getType().isLocation()) {
        edges.back().dst = static_cast<state_t*>(dst.getData());
        edges.back().dstb = 0;
    } else {
        edges.back().dst = 0;
        edges.back().dstb = static_cast<branchpoint_t*>(dst.getData());
    }

    edges.back().control = control;
    edges.back().actname = std::move(actname);
    edges.back().nr = nr;
    return edges.back();
}

// LSC
instanceLine_t& template_t::addInstanceLine()
{
    // bool duplicate = frame.getIndexOf(name) != -1;

    instances.push_back(instanceLine_t());
    instanceLine_t& instance = instances.back();
    // instance.uid = frame.addSymbol(name, type_t::createPrimitive(INSTANCELINE), &instance);
    instance.instanceNr = instances.size() - 1;

    //    if (duplicate)
    //    {
    //        throw TypeException(boost::format("$Duplicate_definition_of %1%") % name);
    //    }

    return instance;
}

message_t& template_t::addMessage(symbol_t src, symbol_t dst, int loc, bool pch)
{
    int32_t nr = messages.empty() ? 0 : messages.back().nr + 1;
    messages.push_back(message_t());
    messages.back().src = static_cast<instanceLine_t*>(src.getData());
    messages.back().dst = static_cast<instanceLine_t*>(dst.getData());
    messages.back().location = loc;
    messages.back().isInPrechart = pch;
    messages.back().nr = nr;
    return messages.back();
}

update_t& template_t::addUpdate(symbol_t anchor, int loc, bool pch)
{
    int32_t nr = updates.empty() ? 0 : updates.back().nr + 1;
    updates.push_back(update_t());
    updates.back().anchor = static_cast<instanceLine_t*>(anchor.getData());
    updates.back().location = loc;
    updates.back().isInPrechart = pch;
    updates.back().nr = nr;
    return updates.back();
}

condition_t& template_t::addCondition(vector<symbol_t> anchors, int loc, bool pch, bool isHot)
{
    int32_t nr = conditions.empty() ? 0 : conditions.back().nr + 1;
    auto& condition = conditions.emplace_back();

    for (auto& anchor : anchors) {
        condition.anchors.push_back(static_cast<instanceLine_t*>(anchor.getData()));  // TODO
    }
    condition.location = loc;
    condition.isInPrechart = pch;
    condition.nr = nr;
    condition.isHot = isHot;
    return condition;
}

template <typename Fn, typename Element, typename Res = std::invoke_result_t<Fn, Element>>
deque<Res> collect(Fn&& fn, const deque<Element>& elements)
{
    auto res = std::deque<Res>{};
    std::transform(std::begin(elements), std::end(elements), std::back_inserter(res), std::forward<Fn>(fn));
    return res;
}

/**
 * returns the simregions of an LSC scenario.
 * A simregion is a simultaneous region containing
 * 1 or 0 message,
 * 1 or 0 update and
 * 1 or 0 condition,
 * at the same location.
 * a message, update or condition must be in only one simregion.
 */
const vector<simregion_t> template_t::getSimregions()
{
    // cout <<"=======LSC: getSimregions=======\n";
    // Copy the numbers of messages, conditions and updates from the scenario
    deque<int> m_nr = collect(std::mem_fn(&message_t::get_nr), messages);
    deque<int> c_nr = collect(std::mem_fn(&condition_t::get_nr), conditions);
    deque<int> u_nr = collect(std::mem_fn(&update_t::get_nr), updates);

    vector<simregion_t> simregions;
    simregions.reserve(m_nr.size());

    /**
     * iterates over messages
     */
    for (auto& message_nr : m_nr) {
        simregion_t s = simregion_t();
        s.setMessage(messages, message_nr);

        instanceLine_t* source = s.message->src;
        instanceLine_t* target = s.message->dst;
        int y = s.message->location;
        /**
         * we give priority to the condition on the target, if there is also one
         * in the source, it must be part of another simregion
         */
        if (getCondition(*target, y, s.condition)) {
            for (auto c_itr = c_nr.begin(); c_itr != c_nr.end(); ++c_itr) {
                if (*c_itr == s.condition->nr) {
                    c_nr.erase(c_itr);
                    break;
                }
            }
        } else if (getCondition(*source, y, s.condition)) {
            for (auto c_itr = c_nr.begin(); c_itr != c_nr.end(); ++c_itr) {
                if (*c_itr == s.condition->nr) {
                    c_nr.erase(c_itr);
                    break;
                }
            }
        }
        if (getUpdate(*target, y, s.update)) {
            for (auto u_itr = u_nr.begin(); u_itr != u_nr.end(); ++u_itr) {
                if (*u_itr == s.update->nr) {
                    u_nr.erase(u_itr);
                    break;
                }
            }
        } else if (getUpdate(*source, y, s.update)) {
            for (auto u_itr = u_nr.begin(); u_itr != u_nr.end(); ++u_itr) {
                if (*u_itr == s.update->nr) {
                    u_nr.erase(u_itr);
                    break;
                }
            }
        }
        s.nr = simregions.size();
        simregions.push_back(std::move(s));
    }

    /**
     * iterates over remaining conditions
     */
    for (auto c_itr = c_nr.begin(); c_itr != c_nr.end(); ++c_itr) {
        auto s = simregion_t();
        s.setCondition(conditions, *c_itr);

        int y = s.condition->location;
        if (getUpdate(s.condition->anchors, y, s.update)) {
            for (auto u_itr = u_nr.begin(); u_itr != u_nr.end(); ++u_itr) {
                if (*u_itr == s.update->nr) {
                    u_nr.erase(u_itr);
                    break;
                }
            }
        }
        s.nr = simregions.size();
        simregions.push_back(s);
    }

    /**
     * iterates over remaining updates
     */
    for (auto u_itr = u_nr.begin(); u_itr != u_nr.end(); ++u_itr) {
        auto s = simregion_t();
        s.setUpdate(updates, *u_itr);
        s.nr = simregions.size();
        simregions.push_back(s);
    }

    /*// cout << "-----unordered simregions-----\n";
    for (unsigned int i = 0; i < simregions.size(); ++i){
        // cout << simregions[i].toString() << " " << simregions[i].nr<< "\n";
    } //test OK*/

    return simregions;
}

/**
 * gets the condition on the given instance, at y location,
 * returns false if there isn't any
 */
bool template_t::getCondition(instanceLine_t& instance, int y, condition_t*& simCondition)
{
    for (auto& condition : conditions) {
        if (condition.location == y) {
            for (auto& anchor : condition.anchors) {
                instanceLine_t* instancej = anchor;
                if (instancej->instanceNr == instance.instanceNr) {
                    simCondition = &condition;
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * gets the update on the given instance at y location,
 * returns false if there isn't any
 */
bool template_t::getUpdate(instanceLine_t& instance, int y, update_t*& simUpdate)
{
    for (auto& update : updates) {
        if (update.location == y) {
            if (update.anchor->instanceNr == instance.instanceNr) {
                simUpdate = &update;
                return true;
            }
        }
    }
    return false;
}

/**
 * gets the first update on one of the given instances, at y location
 * (in simUpdate), returns false if there isn't any
 */
bool template_t::getUpdate(vector<instanceLine_t*>& instances, int y, update_t*& simUpdate)
{
    update_t update;
    for (auto& instance : instances) {
        if (getUpdate(*instance, y, simUpdate))
            return true;
    }
    return false;
}

void instanceLine_t::addParameters(instance_t& inst, frame_t params, const vector<expression_t>& arguments1)
{
    unbound = params.getSize();
    parameters = params;
    parameters.add(inst.parameters);
    mapping = inst.mapping;
    arguments = arguments1.size();
    templ = inst.templ;

    for (size_t i = 0; i < arguments1.size(); i++) {
        mapping[inst.parameters[i]] = arguments1[i];
    }
}
/**
 * return the simregions anchored to this instance,
 * ordered by location number
 */
vector<simregion_t> instanceLine_t::getSimregions(const vector<simregion_t>& simregions)
{
    vector<simregion_t> i_simregions;
    vector<simregion_t>::const_iterator itr;
    vector<simregion_t>::iterator itr1;
    vector<instanceLine_t*>::const_iterator it;
    instanceLine_t* instance;
    // get the simregions anchored to this instance
    for (itr = simregions.begin(); itr != simregions.end(); ++itr) {
        message_t* m = itr->message;
        if (m->nr != -1 && (m->src->instanceNr == this->instanceNr || m->dst->instanceNr == this->instanceNr)) {
            i_simregions.push_back(*itr);
            continue;
        }

        update_t* u = itr->update;
        if (u->nr != -1 && u->anchor->instanceNr == this->instanceNr) {
            i_simregions.push_back(*itr);
            continue;
        }

        condition_t* c = itr->condition;
        if (c->nr != -1) {
            for (it = c->anchors.begin(); it != c->anchors.end(); ++it) {
                instance = *it;
                if (instance->instanceNr == this->instanceNr) {
                    i_simregions.push_back(*itr);
                    break;
                }
            }
        }
    }
    // ordering the simregions by location number
    sort(i_simregions.begin(), i_simregions.end(), compare_simregion());

    //    std::cout << "--------instance--------\n";
    //    for (unsigned int i=0; i< i_simregions.size(); ++i) {
    //        std::cout << i_simregions[i].toString() << " " << i_simregions[i].getLoc()
    //        << " " << i_simregions[i].isInPrechart()<<"\n";
    //    } //test OK

    return i_simregions;
}

int simregion_t::getLoc() const
{
    if (this->message->nr != -1) {
        return this->message->location;
    }
    if (this->condition->nr != -1) {
        return this->condition->location;
    }
    if (this->update->nr != -1) {
        return this->update->location;
    }
    return -1;  // should not happen
}

bool simregion_t::isInPrechart() const
{
    if (this->message && this->message->nr != -1) {
        return this->message->isInPrechart;
    }
    if (this->condition && this->condition->nr != -1) {
        return this->condition->isInPrechart;
    }
    if (this->update && this->update->nr != -1) {
        return this->update->isInPrechart;
    }
    return false;  // should not happen
}

void simregion_t::setMessage(std::deque<message_t>& messages, int nr)
{
    for (auto& message : messages) {
        if (message.nr == nr) {
            this->message = &message;
            return;
        }
    }
}

void simregion_t::setCondition(std::deque<condition_t>& conditions, int nr)
{
    for (auto& condition : conditions) {
        if (condition.nr == nr) {
            this->condition = &condition;
            return;
        }
    }
}

void simregion_t::setUpdate(std::deque<update_t>& updates, int nr)
{
    for (auto& update : updates) {
        if (update.nr == nr) {
            this->update = &update;
            return;
        }
    }
}

std::string simregion_t::toString() const
{
    std::string s = "s(";
    if (message->nr != -1) {
        s += ("m:" + message->label.toString() + " ");
    }
    if (condition->nr != -1) {
        std::string b = (condition->isHot) ? " HOT " : "";
        s += ("c:" + b + (condition->label.toString()) + " ");
    }
    if (update->nr != -1) {
        s += ("u:" + update->label.toString() + " ");
    }
    s = s.substr(0, s.size() - 1);
    s += ")";
    return s;
}

void cut_t::erase(const simregion_t& s)
{
    for (auto sim = simregions.begin(); sim != simregions.end(); ++sim) {
        if (sim->nr == s.nr) {
            simregions.erase(sim);
            return;
        }
    }
}
bool cut_t::contains(const simregion_t& s) const
{
    for (auto sim = simregions.begin(); sim != simregions.end(); ++sim) {
        if (sim->nr == s.nr) {
            return true;
        }
    }
    return false;
}

/**
 * returns true if the cut is in the prechart,
 * given one of the following simregions.
 * if one of the following simregions is not in the prechart,
 * then all following simregions aren't in the prechart (because of the
 * construction of the partial order),
 * and the cut is not in the prechart (but can contain only simregions
 * that are in the prechart, if it is the limit between the prechart
 * and the mainchart)
 */
bool cut_t::isInPrechart(const simregion_t& fSimregion) const
{
    for (auto sim = simregions.begin(); sim != simregions.end(); ++sim) {
        if (!sim->isInPrechart()) {
            return false;
        }
    }
    if (!fSimregion.isInPrechart()) {
        return false;
    }
    return true;
}

bool cut_t::isInPrechart() const
{
    for (auto sim = simregions.begin(); sim != simregions.end(); ++sim) {
        if (!sim->isInPrechart()) {
            return false;
        }
    }
    return true;
}

bool cut_t::equals(const cut_t& y) const
{
    std::vector<simregion_t>::const_iterator s;
    std::vector<simregion_t>::iterator sim;
    int xsize = simregions.size();
    int ysize = y.simregions.size();
    if (xsize != ysize)
        return false;
    std::vector<simregion_t> ycopy = std::vector<simregion_t>(y.simregions);
    for (s = simregions.begin(); s != simregions.end(); ++s) {
        for (sim = ycopy.begin(); sim != ycopy.end(); ++sim) {
            if (sim->nr == s->nr) {
                ycopy.erase(sim);
                break;
            }
        }
    }
    return (ycopy.empty()) ? true : false;
}

/**
 * return true if the LSC is of invariant mode
 */
bool template_t::isInvariant()
{
    if (this->isTA) {
        return false;
    }
    return (strcasecmp(this->mode.c_str(), "invariant") == 0);
}

string chan_priority_t::toString() const
{
    std::ostringstream stream;
    stream << "chan priority ";
    string head_s = head.toString();
    if (head_s.size() == 0)
        head_s = "default";

    stream << head_s;
    std::list<entry>::const_iterator itr;
    for (itr = tail.begin(); itr != tail.end(); ++itr) {
        if (itr->first == '<')
            stream << " ";
        stream << itr->first << " ";
        stream << itr->second.toString();
    }
    return stream.str();
}

Document::Document(): syncUsed(0)
{
    global.frame = frame_t::createFrame();
#ifdef ENABLE_CORA
    addVariable(&global, type_t::createPrimitive(COST), "cost", expression_t());
#endif

    hasUrgentTrans = false;
    hasPriorities = false;
    hasStrictInv = false;
    stopsClock = false;
    hasStrictLowControlledGuards = false;
    hasGuardOnRecvBroadcast = false;
    defaultChanPriority = 0;
    modified = false;
}

Document::Document(const Document& ta)

{
    // TODO
    // clone ref (functions)
    // redirect pointers (edges)
    // clone frame_t - can be problematic

    throw TypeException("TODO");
}

Document::~Document() noexcept
{
    for (auto lib : libraries) {
#if defined(__MINGW32__)  // Microsoft compiler
        FreeLibrary((HINSTANCE)lib);
#elif defined(__linux__) || defined(__APPLE__)
        dlclose(lib);
#endif
    }
}

list<template_t>& Document::getTemplates() { return templates; }

list<instance_t>& Document::getProcesses() { return processes; }

declarations_t& Document::getGlobals() { return global; }

void Document::addLibrary(void* lib) { libraries.push_back(lib); }

void* Document::lastLibrary() { return libraries.back(); }
/** Creates and returns a new template. The template is created with
 *  the given name and parameters and added to the global frame. The
 *  method does not check for duplicate declarations. An instance with
 *  the same name and parameters is added as well.
 */
template_t& Document::addTemplate(const string& name, frame_t params, position_t position, const bool isTA,
                                  const string& typeLSC, const string& mode)
{
    type_t type = (isTA) ? type_t::createInstance(params) : type_t::createLscInstance(params);
    template_t& templ = templates.emplace_back();
    templ.parameters = params;
    templ.frame = frame_t::createFrame(global.frame);
    templ.frame.add(params);
    templ.templ = &templ;
    templ.uid = global.frame.addSymbol(name, type, position, (instance_t*)&templ);
    templ.arguments = 0;
    templ.unbound = params.getSize();
    templ.isTA = isTA;
    templ.dynamic = false;
    // LSC
    templ.type = typeLSC;
    templ.mode = mode;
    return templ;
}

template_t& Document::addDynamicTemplate(const std::string& name, frame_t params, position_t pos)
{
    type_t type = type_t::createInstance(params);
    dynamicTemplates.emplace_back();
    template_t& templ = dynamicTemplates.back();
    templ.parameters = params;
    templ.frame = frame_t::createFrame(global.frame);
    templ.frame.add(params);
    templ.templ = &templ;
    templ.uid = global.frame.addSymbol(name, type, pos, (instance_t*)&templ);
    templ.arguments = 0;
    templ.unbound = params.getSize();
    templ.isTA = true;
    templ.dynamic = true;
    templ.dynindex = dynamicTemplates.size() - 1;
    templ.isDefined = false;
    return templ;
}

std::vector<template_t*>& Document::getDynamicTemplates()
{
    if (dynamicTemplatesVec.size() != dynamicTemplates.size()) {
        dynamicTemplatesVec.clear();
        dynamicTemplatesVec.reserve(dynamicTemplates.size());
        for (auto&& t : dynamicTemplates)
            dynamicTemplatesVec.push_back(&t);
    }
    return dynamicTemplatesVec;
}

auto equal_name(const std::string& name)
{
    return [&name](const auto& e) { return (e.uid.getName() == name); };
}

const template_t* Document::findTemplate(const std::string& name) const
{
    auto has_name = equal_name(name);
    auto it = std::find_if(std::begin(templates), std::end(templates), has_name);
    if (it == std::end(templates)) {
        it = std::find_if(std::begin(dynamicTemplates), std::end(dynamicTemplates), has_name);
        if (it == std::end(dynamicTemplates))
            return nullptr;
    }
    return &(*it);
}

template_t* Document::getDynamicTemplate(const std::string& name)
{
    auto it = std::find_if(std::begin(dynamicTemplates), std::end(dynamicTemplates), equal_name(name));
    if (it == std::end(dynamicTemplates))
        return nullptr;
    return &(*it);
}

instance_t& Document::addInstance(const string& name, instance_t& inst, frame_t params,
                                  const vector<expression_t>& arguments, position_t pos)
{
    type_t type = type_t::createInstance(params);
    instance_t& instance = instances.emplace_back();
    instance.uid = global.frame.addSymbol(name, type, pos, &instance);
    instance.unbound = params.getSize();
    instance.parameters = params;
    instance.parameters.add(inst.parameters);
    instance.mapping = inst.mapping;
    instance.arguments = arguments.size();
    instance.templ = inst.templ;
    for (size_t i = 0; i < arguments.size(); ++i)
        instance.mapping[inst.parameters[i]] = arguments[i];
    return instance;
}

instance_t& Document::addLscInstance(const string& name, instance_t& inst, frame_t params,
                                     const vector<expression_t>& arguments, position_t pos)
{
    type_t type = type_t::createLscInstance(params);
    instance_t& instance = lscInstances.emplace_back();
    instance.uid = global.frame.addSymbol(name, type, pos, &instance);
    instance.unbound = params.getSize();
    instance.parameters = params;
    instance.parameters.add(inst.parameters);
    instance.mapping = inst.mapping;
    instance.arguments = arguments.size();
    instance.templ = inst.templ;
    for (size_t i = 0; i < arguments.size(); ++i)
        instance.mapping[inst.parameters[i]] = arguments[i];
    return instance;
}

void Document::removeProcess(instance_t& instance)
{
    getGlobals().frame.remove(instance.uid);
    for (auto itr = processes.cbegin(); itr != processes.cend(); ++itr) {
        if (itr->uid == instance.uid) {
            processes.erase(itr);
            break;
        }
    }
}

void Document::addProcess(instance_t& instance, position_t pos)
{
    type_t type;
    instance_t& process = processes.emplace_back(instance);
    if (process.unbound == 0)
        type = type_t::createProcess(process.templ->frame);
    else
        type = type_t::createProcessSet(instance.uid.getType());
    process.uid = global.frame.addSymbol(instance.uid.getName(), type, pos, &process);
}

void Document::addGantt(declarations_t* context, gantt_t g) { context->ganttChart.push_back(std::move(g)); }

void Document::addQuery(query_t query) { queries.push_back(std::move(query)); }

bool Document::queriesEmpty() const { return queries.empty(); }

options_t& Document::getOptions() { return modelOptions; }

void Document::setOptions(const options_t& options) { modelOptions = options; }

queries_t& Document::getQueries() { return queries; }

// Add a regular variable
variable_t* Document::addVariable(declarations_t* context, type_t type, const string& name, expression_t initial,
                                  position_t pos)
{
    variable_t* var = addVariable(context->variables, context->frame, type, name, pos);
    var->expr = initial;
    return var;
}

variable_t* Document::addVariableToFunction(function_t* function, frame_t frame, type_t type, const string& name,
                                            expression_t initial, position_t pos)
{
    variable_t* var = addVariable(function->variables, frame, type, name, pos);
    var->expr = initial;
    return var;
}

// Add a regular variable
variable_t* Document::addVariable(list<variable_t>& variables, frame_t frame, type_t type, const string& name,
                                  position_t pos)
{
    bool duplicate = frame.getIndexOf(name) != -1;
    // Add variable
    variable_t& var = variables.emplace_back();
    // Add symbol
    var.uid = frame.addSymbol(name, type, pos, &var);
    if (duplicate)
        throw DuplicateDefinitionError(name);
    return &var;
}

void Document::copyVariablesFromTo(const template_t* from, template_t* to) const
{
    for (auto&& var : from->variables) {
        to->variables.push_back(var);
        to->frame.add(var.uid);
    }
}

void Document::copyFunctionsFromTo(const template_t* from, template_t* to) const
{
    // TODO to be implemented and to be used in Translator::lscProcBegin (see Translator.cpp)
}

void Document::addProgressMeasure(declarations_t* context, expression_t guard, expression_t measure)
{
    context->progress.emplace_back(guard, measure);
}

static void visit(SystemVisitor& visitor, frame_t frame)
{
    for (size_t i = 0; i < frame.getSize(); ++i) {
        type_t type = frame[i].getType();

        if (type.getKind() == TYPEDEF) {
            visitor.visitTypeDef(frame[i]);
            continue;
        }

        void* data = frame[i].getData();
        type = type.stripArray();

        if ((type.is(Constants::INT) || type.is(Constants::STRING) || type.is(Constants::DOUBLE) ||
             type.is(Constants::BOOL) || type.is(CLOCK) || type.is(CHANNEL) || type.is(SCALAR) ||
             type.getKind() == RECORD) &&
            data != nullptr)  // <--- ignore parameters
        {
            visitor.visitVariable(*static_cast<variable_t*>(data));
        } else if (type.is(LOCATION)) {
            visitor.visitState(*static_cast<state_t*>(data));
        } else if (type.is(LOCATION_EXPR)) {
            visitor.visitState(*static_cast<state_t*>(data));
        } else if (type.is(FUNCTION)) {
            visitor.visitFunction(*static_cast<function_t*>(data));
        } else if (type.is(EXTERNAL_FUNCTION)) {
            // we cannot look inside a external function, skip.
        } else if (type.is(INSTANCELINE)) {
            visitor.visitInstanceLine(*static_cast<instanceLine_t*>(data));
        }
    }
}

void Document::accept(SystemVisitor& visitor)
{
    visitor.visitSystemBefore(this);
    visit(visitor, global.frame);
    for (auto t = templates.begin(); t != templates.end(); ++t) {
        if (visitor.visitTemplateBefore(*t)) {
            visit(visitor, t->frame);
            for_each(t->edges.begin(), t->edges.end(), bind(&SystemVisitor::visitEdge, &visitor, _1));
            for_each(t->messages.begin(), t->messages.end(), bind(&SystemVisitor::visitMessage, &visitor, _1));
            for_each(t->updates.begin(), t->updates.end(), bind(&SystemVisitor::visitUpdate, &visitor, _1));
            for_each(t->conditions.begin(), t->conditions.end(), bind(&SystemVisitor::visitCondition, &visitor, _1));
            visitor.visitTemplateAfter(*t);
        }
    }

    for (auto t = dynamicTemplates.begin(); t != dynamicTemplates.end(); ++t) {
        if (visitor.visitTemplateBefore(*t)) {
            visit(visitor, t->frame);
            for_each(t->edges.begin(), t->edges.end(), bind(&SystemVisitor::visitEdge, &visitor, _1));
            for_each(t->messages.begin(), t->messages.end(), bind(&SystemVisitor::visitMessage, &visitor, _1));
            for_each(t->updates.begin(), t->updates.end(), bind(&SystemVisitor::visitUpdate, &visitor, _1));
            for_each(t->conditions.begin(), t->conditions.end(), bind(&SystemVisitor::visitCondition, &visitor, _1));
            visitor.visitTemplateAfter(*t);
        }
    }

    for (size_t i = 0; i < global.frame.getSize(); ++i) {
        type_t type = global.frame[i].getType();
        void* data = global.frame[i].getData();
        type = type.stripArray();
        if (type.is(PROCESS) || type.is(PROCESSSET)) {
            visitor.visitProcess(*static_cast<instance_t*>(data));
        } else if (type.is(INSTANCE)) {
            visitor.visitInstance(*static_cast<instance_t*>(data));
        } else if (type.is(LSCINSTANCE)) {
            visitor.visitInstance(*static_cast<instance_t*>(data));
        }
    }

    for (auto&& decl : global.iodecl)
        visitor.visitIODecl(decl);

    // Maybe not ideal place for this:
    for (auto&& progress : global.progress)
        visitor.visitProgressMeasure(progress);

    for (auto&& gantt : global.ganttChart)
        visitor.visitGanttChart(gantt);

    visitor.visitSystemAfter(this);
}

void Document::setBeforeUpdate(expression_t e) { beforeUpdate = e; }

expression_t Document::getBeforeUpdate() { return beforeUpdate; }

void Document::setAfterUpdate(expression_t e) { afterUpdate = e; }

expression_t Document::getAfterUpdate() { return afterUpdate; }

void Document::beginChanPriority(expression_t chan)
{
    hasPriorities |= true;
    chan_priority_t priorities;
    priorities.head = chan;
    chanPriorities.push_back(priorities);
}

void Document::addChanPriority(char separator, expression_t chan)
{
    assert(separator == ',' || separator == '<');
    chan_priority_t::tail_t& tail = chanPriorities.back().tail;
    tail.push_back(chan_priority_t::entry(separator, chan));
}

const std::list<chan_priority_t>& Document::getChanPriorities() const { return chanPriorities; }

std::list<chan_priority_t>& Document::getMutableChanPriorities() { return chanPriorities; }

void Document::setProcPriority(const string& name, int priority)
{
    hasPriorities |= (priority != 0);
    procPriority[name] = priority;
}

int Document::getProcPriority(const char* name) const
{
    assert(procPriority.find(name) != procPriority.end());
    return procPriority.find(name)->second;
}

bool Document::hasPriorityDeclaration() const { return hasPriorities; }

void Document::recordStrictInvariant() { hasStrictInv = true; }

bool Document::hasStrictInvariants() const { return hasStrictInv; }

void Document::recordStopWatch() { stopsClock = true; }

bool Document::hasStopWatch() const { return stopsClock; }

bool Document::hasStrictLowerBoundOnControllableEdges() const { return hasStrictLowControlledGuards; }

void Document::recordStrictLowerBoundOnControllableEdges() { hasStrictLowControlledGuards = true; }

void Document::addPosition(uint32_t position, uint32_t offset, uint32_t line, const std::string& path)
{
    positions.add(position, offset, line, path);
}

const Positions::line_t& Document::findPosition(uint32_t position) const { return positions.find(position); }

void Document::addError(position_t position, std::string msg, std::string context)
{
    errors.emplace_back(positions.find(position.start), positions.find(position.end), position, std::move(msg),
                        std::move(context));
}

void Document::addWarning(position_t position, const std::string& msg, const std::string& context)
{
    warnings.emplace_back(positions.find(position.start), positions.find(position.end), position, msg, context);
}

void Document::clearErrors() const { errors.clear(); }

void Document::clearWarnings() const { warnings.clear(); }

bool Document::isModified() const { return modified; }

void Document::setModified(bool mod) { modified = mod; }

iodecl_t* Document::addIODecl()
{
    global.iodecl.emplace_back();
    return &global.iodecl.back();
}

void Document::setSupportedMethods(const SupportedMethods& supportedMethods)
{
    this->supportedMethods = supportedMethods;
}

const SupportedMethods& Document::getSupportedMethods() const { return supportedMethods; }
