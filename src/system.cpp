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

#include "utap/builder.h"
#include "utap/system.h"
#include "utap/statement.h"
#include "libparser.h"

#include <stack>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <climits>
#include <cassert>
#include <sstream>

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
using std::ostream;
using std::deque;

static const char *const unsupported
= "Internal error: Feature not supported in this mode.";
static const char *const invalid_type = "$Invalid_type";

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

function_t::~function_t()
{
    delete body;
}

string function_t::toString() const
{
    string str = "";
    string type = uid.getType().get(0).toDeclarationString(); //return type
    str += type + " " + uid.getName();
    str += "(";
    for (uint32_t i = 1; i < uid.getType().size(); ++i) // parameters
    {
        if (!uid.getType().getLabel(i).empty())
        {
            str += uid.getType().get(i).toDeclarationString();
            str += " ";
            str += uid.getType().getLabel(i);
            str += ", ";
        }
    }
    if (uid.getType().size()>1)
        str = str.substr(0, str.size()-2);
    str += ")\n{\n";

    std::list<variable_t>::const_iterator itr;
    for (itr = variables.begin(); itr != variables.end(); ++itr) // variables
    {
        str += "    " + itr->toString();
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
    if (uid.getType().isArray())
    {
        type = uid.getType().toDeclarationString();
        size_t i = type.find('[');
        str += type.substr(0, (int)i);
        str += " ";
        str += uid.getName();
        str += type.substr((int)i , type.size() - (int)i);
    }
    else
    {
    str += uid.getType().toDeclarationString() + " "
        + uid.getName();
    }
    if (!expr.empty())
    {
        str += " = " + expr.toString();
    }
    return str;
}

bool declarations_t::addFunction(type_t type, const string& name, function_t *&fun)
{
    bool duplicate = frame.getIndexOf(name) != -1;
    functions.push_back(function_t());
    fun = &functions.back();
    fun->uid = frame.addSymbol(name, type, fun); // Add symbol
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
    list<variable_t>::const_iterator v_itr = variables.begin();
    string str = "";
    int i = 0;
    // constants
    if (!variables.empty()){
        while (v_itr != variables.end())
        {
            if (i == 0)
            {
                str += "// constants\n";
                i++;
            }
            if (v_itr->uid.getType().getKind() == CONSTANT)
            {
                str += v_itr->toString();
                str += ";\n";
            }
            ++v_itr;
        }
    }
    return str;
}

string declarations_t::getTypeDefinitions() const
{
    string str = "";
    // type definitions
    int j = 0;
    for (uint32_t i = 0; i < frame.getSize(); ++i)
    {
        if (frame[i].getType().getKind() == TYPEDEF)
        {
            if (j==0)
            {
                str += "// type definitions\n";
                j++;
            }
            str += frame[i].getType().toDeclarationString() + ";\n";
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
    if (!variables.empty()){
        if (global) ++v_itr; // the first variable is "t(0)"
        while (v_itr != variables.end())
        {
            if (i == 0)
            {
                str += "// variables\n";
                i++;
            }
            if (v_itr->uid.getType().getKind() != CONSTANT)
            {
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
    if (!functions.empty()){
        str += "// functions\n";
        for (f_itr = functions.begin(); f_itr != functions.end(); ++f_itr)
        {
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
    for (itr = mapping.begin(); itr != mapping.end(); ++itr)
    {
        str += itr->first.getName() + " = " + itr->second.toString() + "\n";
    }
    return str;
}

std::string instance_t::writeParameters() const
{
    std::string str = "";
    for (uint32_t i = 0; i < parameters.getSize(); ++i)
    {
        str += parameters[i].getType().toDeclarationString()
            + " " + parameters[i].getName() + ", ";
    }
    if (parameters.getSize() > 0)
    {
        str = str.substr(0, str.size() -2);
    }
    return str;
}

std::string instance_t::writeArguments() const
{
    std::string str = "";
    std::map<symbol_t, expression_t>::const_iterator itr;
    for (uint32_t i = 0; i < parameters.getSize(); ++i)
    {
        for (itr = mapping.begin(); itr != mapping.end(); ++ itr)
        {
            if ( itr->first == parameters[i])
            {
                str += itr->second.toString();
                str += ", ";
            }
        }
    }
    if (parameters.getSize() > 0)
    {
        str = str.substr(0, str.size() -2);
    }
    return str;
}

state_t &template_t::addLocation(const string& name, expression_t inv, expression_t er)
{
    bool duplicate = frame.getIndexOf(name) != -1;

    states.push_back(state_t());
    state_t &state = states.back();
    state.uid = frame.addSymbol(name, type_t::createPrimitive(LOCATION), &state);
    state.locNr = states.size() - 1;
    state.invariant = inv;
    state.exponentialRate = er;

    if (duplicate)
    {
        throw TypeException(boost::format("$Duplicate_definition_of %1%") % name);
    }

    return state;
}

// FIXME: like for unnamed locations, a name is autegenerated
// this name may conflict with user-defined names
branchpoint_t &template_t::addBranchpoint(const string& name)
{
    bool duplicate = frame.getIndexOf(name) != -1;

    branchpoints.push_back(branchpoint_t());
    branchpoint_t &branchpoint = branchpoints.back();
    branchpoint.uid = frame.addSymbol(name, type_t::createPrimitive(BRANCHPOINT), &branchpoint);
    branchpoint.bpNr = branchpoints.size() - 1;

    if (duplicate)
    {
        throw TypeException(boost::format("$Duplicate_definition_of %1%") % name);
    }

    return branchpoint;
}

edge_t &template_t::addEdge(symbol_t src, symbol_t dst, bool control, const string& actname)
{
    int32_t nr = edges.empty() ? 0 : edges.back().nr + 1;
    edges.push_back(edge_t());
    if (src.getType().isLocation())
    {
        edges.back().src = static_cast<state_t*>(src.getData());
        edges.back().srcb = 0;
    }
    else
    {
        edges.back().src = 0;
        edges.back().srcb = static_cast<branchpoint_t*>(src.getData());
    }
    if (dst.getType().isLocation())
    {
        edges.back().dst = static_cast<state_t*>(dst.getData());
        edges.back().dstb = 0;
    }
    else
    {
        edges.back().dst = 0;
        edges.back().dstb = static_cast<branchpoint_t*>(dst.getData());
    }

    edges.back().control = control;
    edges.back().actname = actname;
    edges.back().nr = nr;
    return edges.back();
}

//LSC
instanceLine_t &template_t::addInstanceLine()
{
    //bool duplicate = frame.getIndexOf(name) != -1;

    instances.push_back(instanceLine_t());
    instanceLine_t &instance = instances.back();
    //instance.uid = frame.addSymbol(name, type_t::createPrimitive(INSTANCELINE), &instance);
    instance.instanceNr = instances.size() - 1;

//    if (duplicate)
//    {
//        throw TypeException(boost::format("$Duplicate_definition_of %1%") % name);
//    }

    return instance;
}

message_t &template_t::addMessage(symbol_t src, symbol_t dst,
        int loc, bool pch)
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

update_t &template_t::addUpdate(symbol_t anchor, int loc, bool pch)
{
    int32_t nr = updates.empty() ? 0 : updates.back().nr + 1;
    updates.push_back(update_t());
    updates.back().anchor = static_cast<instanceLine_t*>(anchor.getData());
    updates.back().location = loc;
    updates.back().isInPrechart = pch;
    updates.back().nr = nr;
    return updates.back();
}

condition_t &template_t::addCondition(vector<symbol_t> anchors, int loc,
        bool pch, bool isHot)
{
    int32_t nr = conditions.empty() ? 0 : conditions.back().nr + 1;
    conditions.push_back(condition_t());

    for (unsigned int i(0); i<anchors.size(); ++i){
        conditions.back().anchors.push_back(static_cast<instanceLine_t*>(anchors[i].getData()));//TODO
    }
    conditions.back().location = loc;
    conditions.back().isInPrechart = pch;
    conditions.back().nr = nr;
    conditions.back().isHot = isHot;
    return conditions.back();
}


static deque<int> messages_nr(deque<message_t> messages)
{
    deque<message_t>::iterator itr;
    deque<int> d;

    for (itr = messages.begin(); itr != messages.end(); ++itr)
    {
        d.push_back(itr->nr);
    }
    return d;
}

static deque<int> conditions_nr(deque<condition_t> conditions)
{
    deque<condition_t>::iterator itr;
    deque<int> d;

    for (itr = conditions.begin(); itr != conditions.end(); ++itr)
    {
        d.push_back(itr->nr);
    }
    return d;
}

static deque<int> updates_nr(deque<update_t> updates)
{
    deque<update_t>::iterator itr;
    deque<int> d;

    for (itr = updates.begin(); itr != updates.end(); ++itr)
    {
        d.push_back(itr->nr);
    }
    return d;
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
    /**
     * we copy the messages, conditions and updates from the scenario
     */
    deque<int> m_nr = messages_nr(messages);
    deque<int> c_nr = conditions_nr(conditions);
    deque<int> u_nr = updates_nr(updates);

    deque<int>::iterator m_itr;
    deque<int>::iterator c_itr;
    deque<int>::iterator u_itr;

    vector<simregion_t> simregions;
    simregion_t s;
    instanceLine_t *source;
    instanceLine_t *target;
    int y;
    int nr = 0;

    /**
     * iterates over messages
     */
    for (m_itr = m_nr.begin(); m_itr!=m_nr.end(); ++m_itr)
    {
        simregion_t s = simregion_t();
        s.setMessage(messages, *m_itr);

        source = s.message->src;
        target = s.message->dst;
        y = s.message->location;
        /**
         * we give priority to the condition on the target, if there is also one
         * in the source, it must be part of another simregion
         */
        if (getCondition(target, y, s.condition))
        {
            for (c_itr = c_nr.begin(); c_itr != c_nr.end(); ++c_itr)
            {
                if (*c_itr == s.condition->nr)
                {
                    c_nr.erase(c_itr);
                    break;
                }
            }
        }
        else if (getCondition(source, y, s.condition))
        {
            for (c_itr = c_nr.begin(); c_itr != c_nr.end(); ++c_itr)
            {
                if (*c_itr == s.condition->nr)
                {
                    c_nr.erase(c_itr);
                    break;
                }
            }
        }
        if (getUpdate(target, y, s.update))
        {
            for (u_itr = u_nr.begin(); u_itr != u_nr.end(); ++u_itr)
            {
                if (*u_itr == s.update->nr)
                {
                    u_nr.erase(u_itr);
                    break;
                }
            }
        }
        else if (getUpdate(source, y, s.update))
        {
            for (u_itr = u_nr.begin(); u_itr != u_nr.end(); ++u_itr)
            {
                if (*u_itr == s.update->nr)
                {
                    u_nr.erase(u_itr);
                    break;
                }
            }
        }
        s.nr = nr;
        simregions.push_back(s);
        nr++;
    }

    /**
     * iterates over remaining conditions
     */
    for (c_itr = c_nr.begin(); c_itr != c_nr.end(); ++c_itr)
    {
        s = simregion_t();
        s.setCondition(conditions, *c_itr);

        y = s.condition->location;
        if (getUpdate(s.condition->anchors, y, s.update))
        {
            for (u_itr = u_nr.begin(); u_itr != u_nr.end(); ++u_itr)
            {
                if (*u_itr == s.update->nr)
                {
                    u_nr.erase(u_itr);
                    break;
                }
            }
        }
        s.nr = nr;
        simregions.push_back(s);
        nr++;
    }

    /**
     * iterates over remaining updates
     */
    for (u_itr = u_nr.begin(); u_itr != u_nr.end(); ++u_itr)
    {
        s = simregion_t();
        s.setUpdate(updates, *u_itr);
        s.nr = nr;
        simregions.push_back(s);
        nr++;
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
bool template_t::getCondition(instanceLine_t* instance, int y, condition_t*& simCondition)
{
    deque<condition_t>::iterator i;
    vector<instanceLine_t*>::iterator j;

    for (i = conditions.begin(); i != conditions.end(); ++i)
    {
        condition_t& condition = *i;
        if (condition.location == y)
        {
            vector<instanceLine_t*>& anchors = condition.anchors;
            for (j = anchors.begin(); j != anchors.end(); ++j)
            {
                instanceLine_t* instancej = *j;
                if (instancej->instanceNr == instance->instanceNr)
                {
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
bool template_t::getUpdate(instanceLine_t* instance, int y, update_t*& simUpdate)
{
    deque<update_t>::iterator i;
    for (i = updates.begin(); i != updates.end(); ++i)
    {
        update_t& update = *i;
        if (update.location == y)
        {
            if (update.anchor->instanceNr == instance->instanceNr)
            {
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
bool template_t::getUpdate(const vector<instanceLine_t*>& instances, int y, update_t*& simUpdate)
{
    vector<instanceLine_t*>::const_iterator j;
    update_t update;

    for (j = instances.begin(); j != instances.end(); ++j)
    {
        if (getUpdate(*j, y, simUpdate))
            return true;
    }
    return false;
}

void instanceLine_t::addParameters(instance_t &inst, frame_t params,
    const vector<expression_t> &arguments1)
{
    unbound = params.getSize();
    parameters = params;
    parameters.add(inst.parameters);
    mapping = inst.mapping;
    arguments = arguments1.size();
    templ = inst.templ;

    for (size_t i = 0; i < arguments1.size(); i++)
    {
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
    //get the simregions anchored to this instance
    for (itr = simregions.begin(); itr != simregions.end(); ++itr) {
        message_t* m = itr->message;
        if (m->nr != -1 && (m->src->instanceNr == this->instanceNr
                || m->dst->instanceNr == this->instanceNr) ) {
            i_simregions.push_back(*itr);
            continue;
        }

        update_t* u = itr->update;
        if ( u->nr != -1 && u->anchor->instanceNr == this->instanceNr ) {
            i_simregions.push_back(*itr);
            continue;
        }

        condition_t* c = itr->condition;
        if (c->nr != -1) {
            for (it = c->anchors.begin(); it !=c->anchors.end(); ++it) {
                instance = *it;
                if (instance->instanceNr == this->instanceNr) {
                    i_simregions.push_back(*itr);
                    break;
                }
            }
        }
    }
    //ordering the simregions by location number
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
    if (this->message->nr != -1)
    {
        return this->message->location;
    }
    if (this->condition->nr != -1)
    {
        return this->condition->location;
    }
    if (this->update->nr != -1)
    {
        return this->update->location;
    }
    return -1;//should not happen
}

bool simregion_t::isInPrechart() const
{
    if (this->message && this->message->nr != -1)
    {
        return this->message->isInPrechart;
    }
    if (this->condition && this->condition->nr != -1)
    {
        return this->condition->isInPrechart;
    }
    if (this->update && this->update->nr != -1)
    {
        return this->update->isInPrechart;
    }
    return false;//should not happen
}

void simregion_t::setMessage(std::deque<message_t>& messages, int nr) {
    std::deque<message_t>::iterator i;
    for (i = messages.begin(); i != messages.end(); ++i) {
        if (i->nr == nr){
            this->message = &(*i);
            return;
        }
    }
}

void simregion_t::setCondition(std::deque<condition_t>& conditions, int nr) {
    std::deque<condition_t>::iterator i;
    for (i = conditions.begin(); i != conditions.end(); ++i) {
        if (i->nr == nr){
            this->condition = &(*i);
            return;
        }
    }
}

void simregion_t::setUpdate(std::deque<update_t>& updates, int nr) {
    std::deque<update_t>::iterator i;
    for (i = updates.begin(); i != updates.end(); ++i) {
        if (i->nr == nr){
            this->update = &(*i);
            return;
        }
    }
}

std::string simregion_t::toString() const {
    std::string s="s(";
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
    s = s.substr(0, s.size()-1);
    s += ")";
    return s;
}


void cut_t::erase(simregion_t s) {
    std::vector<simregion_t>::iterator sim;
    for (sim = simregions.begin(); sim != simregions.end(); ++sim) {
        if (sim->nr == s.nr) {
            simregions.erase(sim);
            return;
        }
    }
}
bool cut_t::contains(simregion_t s) {
    std::vector<simregion_t>::iterator sim;
    for (sim = simregions.begin(); sim != simregions.end(); ++sim) {
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
bool cut_t::isInPrechart(const simregion_t& fSimregion) const {
    std::vector<simregion_t>::const_iterator sim;
    std::vector<simregion_t>::const_iterator fsim;
    for (sim = simregions.begin(); sim != simregions.end(); ++sim)
    {
        if (! sim->isInPrechart())
        {
            return false;
        }
    }
    if (!fSimregion.isInPrechart())
    {
        return false;
    }
    return true;
}

bool cut_t::isInPrechart() const
{
    std::vector<simregion_t>::const_iterator sim;
    for (sim = simregions.begin(); sim != simregions.end(); ++sim)
    {
        if (! sim->isInPrechart())
        {
            return false;
        }
    }
    return true;
}

bool cut_t::equals(const cut_t& y) const {
    std::vector<simregion_t>::const_iterator s;
    std::vector<simregion_t>::iterator sim;
    int xsize = simregions.size();
    int ysize = y.simregions.size();
    if ( xsize != ysize)
        return false;
    std::vector<simregion_t> ycopy = std::vector<simregion_t>(y.simregions);
    for (s = simregions.begin(); s != simregions.end(); ++s)
    {
        for (sim = ycopy.begin(); sim != ycopy.end(); ++sim)
        {
            if (sim->nr == s->nr)
            {
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
    if (this->isTA)
    {
        return false;
    }
    return (strcasecmp(this->mode.c_str(), "invariant") == 0);
}

string chan_priority_t::toString() const
{
    std::ostringstream stream;
    stream << "chan priority ";
    string head_s = head.toString();
    if (head_s.size() == 0) head_s = "default";

    stream << head_s;
    std::list<entry>::const_iterator itr;
    for (itr = tail.begin(); itr != tail.end(); ++itr)
    {
        if (itr->first == '<') stream << " ";
        stream << itr->first << " ";
        stream << itr->second.toString();
    }
    return stream.str();
}

TimedAutomataSystem::TimedAutomataSystem(): syncUsed(UTAP::sync_use_t::unused)
{
    global.frame = frame_t::createFrame();
    addVariable(&global, type_t::createPrimitive(CLOCK), "t(0)", expression_t());
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

TimedAutomataSystem::TimedAutomataSystem(const TimedAutomataSystem& ta)

{
    // TODO
    // clone ref (functions)
    // redirect pointers (edges)
    // clone frame_t - can be problematic

    throw TypeException("TODO");
}

TimedAutomataSystem::~TimedAutomataSystem()
{

}

list<template_t> &TimedAutomataSystem::getTemplates()
{
    return templates;
}

list<instance_t> &TimedAutomataSystem::getProcesses()
{
    return processes;
}

declarations_t &TimedAutomataSystem::getGlobals()
{
    return global;
}

/** Creates and returns a new template. The template is created with
 *  the given name and parameters and added to the global frame. The
 *  method does not check for duplicate declarations. An instance with
 *  the same name and parameters is added as well.
 */
template_t &TimedAutomataSystem::addTemplate(const string& name, frame_t params,
        const bool isTA, const string& typeLSC, const string& mode)
{
    type_t type = (isTA) ? type_t::createInstance(params) :
        type_t::createLscInstance(params);

    templates.push_back(template_t());
    template_t &templ = templates.back();
    templ.parameters = params;
    templ.frame = frame_t::createFrame(global.frame);
    templ.frame.add(params);
    templ.templ = &templ;
    templ.uid = global.frame.addSymbol(name, type, (instance_t*)&templ);
    templ.arguments = 0;
    templ.unbound = params.getSize();
    templ.isTA = isTA;
    templ.dynamic = false;
    //LSC
    templ.type = typeLSC;
    templ.mode = mode;
    return templ;
}

template_t& TimedAutomataSystem::addDynamicTemplate(const string& name,
                                                    frame_t params)
{
    type_t type = type_t::createInstance (params);
    dynamicTemplates.push_back(template_t());
    template_t &templ = dynamicTemplates.back();
    templ.parameters = params;
    templ.frame = frame_t::createFrame(global.frame);
    templ.frame.add (params);
    templ.templ = &templ;
    templ.uid = global.frame.addSymbol(name,type,(instance_t*)&templ);
    templ.arguments = 0;
    templ.unbound = params.getSize();
    templ.isTA = true;
    templ.dynamic = true;
    templ.dynindex = dynamicTemplates.size()-1;
    templ.isDefined = false;
    return templ;
}

std::vector<template_t*> & TimedAutomataSystem::getDynamicTemplates()
{
    if (dynamicTemplatesVec.size () != dynamicTemplates.size()) {
        dynamicTemplatesVec.clear ();
        std::list<template_t>::iterator it;
        for (it = dynamicTemplates.begin(); it!=dynamicTemplates.end(); ++it) {
            dynamicTemplatesVec.push_back(&(*it));
        }
    }
    return dynamicTemplatesVec;
}

template_t* TimedAutomataSystem::getDynamicTemplate(const std::string& name)
{
    std::list<template_t>::iterator it;
    for (it = dynamicTemplates.begin(); it!=dynamicTemplates.end(); ++it) {
        if (it->uid.getName() == name)
            return &(*it);
    }
    return NULL;

}

instance_t &TimedAutomataSystem::addInstance(
    const string& name, instance_t &inst, frame_t params,
    const vector<expression_t> &arguments)
{
    type_t type = type_t::createInstance(params);

    instances.push_back(instance_t());
    instance_t &instance = instances.back();
    instance.uid = global.frame.addSymbol(name, type, &instance);
    instance.unbound = params.getSize();
    instance.parameters = params;
    instance.parameters.add(inst.parameters);
    instance.mapping = inst.mapping;
    instance.arguments = arguments.size();
    instance.templ = inst.templ;

    for (size_t i = 0; i < arguments.size(); i++)
    {
        instance.mapping[inst.parameters[i]] = arguments[i];
    }

    return instance;
}

instance_t &TimedAutomataSystem::addLscInstance(
    const string& name, instance_t &inst, frame_t params,
    const vector<expression_t> &arguments)
{
    type_t type = type_t::createLscInstance(params);

    lscInstances.push_back(instance_t());
    instance_t &instance = lscInstances.back();
    instance.uid = global.frame.addSymbol(name, type, &instance);
    instance.unbound = params.getSize();
    instance.parameters = params;
    instance.parameters.add(inst.parameters);
    instance.mapping = inst.mapping;
    instance.arguments = arguments.size();
    instance.templ = inst.templ;

    for (size_t i = 0; i < arguments.size(); i++)
    {
        instance.mapping[inst.parameters[i]] = arguments[i];
    }

    return instance;
}

void TimedAutomataSystem::removeProcess(instance_t &instance)
{
    getGlobals().frame.remove(instance.uid);
    std::list<instance_t>::iterator itr;
    for (itr = processes.begin(); itr != processes.end(); ++itr)
    {
        if (itr->uid == instance.uid) {
            processes.erase(itr);
            break;
        }
    }
}

void TimedAutomataSystem::addProcess(instance_t &instance)
{
    type_t type;
    processes.push_back(instance);
    instance_t &process = processes.back();
    if (process.unbound == 0)
    {
        type = type_t::createProcess(process.templ->frame);
    }
    else
    {
        type = type_t::createProcessSet(instance.uid.getType());
    }
    process.uid = global.frame.addSymbol(
        instance.uid.getName(), type, &process);
}

void TimedAutomataSystem::addGantt(declarations_t *context, gantt_t& g)
{
    context->ganttChart.push_back(g);
}

void TimedAutomataSystem::addQuery(const query_t &query){
    queries.push_back(query);
}

bool TimedAutomataSystem::queriesEmpty(){
    return queries.empty();
}

queries_t & TimedAutomataSystem::getQueries(){
    return queries;
}

// Add a regular variable
variable_t *TimedAutomataSystem::addVariable(
    declarations_t *context, type_t type, const string& name, expression_t initial)
{
    variable_t *var;
    var = addVariable(context->variables, context->frame, type, name);
    var->expr = initial;
    return var;
}

variable_t *TimedAutomataSystem::addVariableToFunction(
    function_t *function, frame_t frame, type_t type, const string& name,
    expression_t initial)
{
    variable_t *var;
    var = addVariable(function->variables, frame, type, name);
    var->expr = initial;
    return var;
}

// Add a regular variable
variable_t *TimedAutomataSystem::addVariable(
    list<variable_t> &variables, frame_t frame, type_t type, const string& name)
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
        throw TypeException(boost::format("$Duplicate_definition_of %1%") % name);
    }

    return var;
}

void TimedAutomataSystem::copyVariablesFromTo(template_t* from, template_t* to) const
{
    std::list<UTAP::variable_t>::iterator v_itr;
    for (v_itr = from->variables.begin(); v_itr != from->variables.end(); ++v_itr)
    {
        to->variables.push_back(*v_itr);
        to->frame.add(v_itr->uid);
    }
}

void TimedAutomataSystem::copyFunctionsFromTo(template_t* from, template_t* to) const
{
//TODO to be implemented and to be used in Translator::procBegin (see Translator.cpp)
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
        type_t type = frame[i].getType();

        if (type.getKind() == TYPEDEF)
        {
            visitor.visitTypeDef(frame[i]);
            continue;
        }

        void *data = frame[i].getData();
        type = type.stripArray();

        if ((type.is(Constants::INT)
             || type.is(Constants::DOUBLE)
             || type.is(Constants::BOOL)
             || type.is(CLOCK)
             || type.is(CHANNEL)
             || type.is(SCALAR)
             || type.getKind() == RECORD)
            && data != NULL) // <--- ignore parameters
        {
            visitor.visitVariable(*static_cast<variable_t*>(data));
        }
        else if (type.is(LOCATION))
        {
            visitor.visitState(*static_cast<state_t*>(data));
        }
        else if (type.is(FUNCTION))
        {
            visitor.visitFunction(*static_cast<function_t*>(data));
        }
        else if (type.is(INSTANCELINE))
        {
            visitor.visitInstanceLine(*static_cast<instanceLine_t*>(data));
        }
    }
}

void TimedAutomataSystem::accept(SystemVisitor &visitor)
{
    visitor.visitSystemBefore(this);
    visit(visitor, global.frame);

    auto visit_template = [&visitor](template_t& t) {
        if (visitor.visitTemplateBefore(t))
        {
            visit(visitor, t.frame);
            for (auto& edge: t.edges)
                visitor.visitEdge(edge);
            for (auto& message: t.messages)
                visitor.visitMessage(message);
            for (auto& update: t.updates)
                visitor.visitUpdate(update);
            for (auto& condition: t.conditions)
                visitor.visitCondition(condition);
            visitor.visitTemplateAfter(t);
        }
    };

    for (auto& t: templates)
        visit_template(t);

    for (auto& t: dynamicTemplates)
        visit_template(t);

    for (size_t i = 0; i < global.frame.getSize(); i++)
    {
        auto frame = global.frame[i];
        type_t type = frame.getType();
        void *data = frame.getData();
        type = type.stripArray();

        if (type.is(PROCESS) || type.is(PROCESSSET))
        {
            visitor.visitProcess(*static_cast<instance_t*>(data));
        }
        else if (type.is(INSTANCE))
        {
            visitor.visitInstance(*static_cast<instance_t*>(data));
        }
        else if (type.is(LSCINSTANCE))
        {
            visitor.visitInstance(*static_cast<instance_t*>(data));
        }
    }

    for (auto& iodecl: global.iodecl)
        visitor.visitIODecl(iodecl);

    // Maybe not ideal place for this:
    for (auto& progress: global.progress)
        visitor.visitProgressMeasure(progress);

    for (auto& gantt: global.ganttChart)
        visitor.visitGanttChart(gantt);

    visitor.visitSystemAfter(this);
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

void TimedAutomataSystem::beginChanPriority(expression_t chan)
{
    hasPriorities |= true;
    chan_priority_t priorities;
    priorities.head = chan;
    chanPriorities.push_back(priorities);
}

void TimedAutomataSystem::addChanPriority(char separator, expression_t chan)
{
    assert(separator == ',' || separator == '<');
    chan_priority_t::tail_t& tail = chanPriorities.back().tail;
    tail.push_back(chan_priority_t::entry(separator, chan));
}

const std::list<chan_priority_t>& TimedAutomataSystem::getChanPriorities() const
{
    return chanPriorities;
}

std::list<chan_priority_t>& TimedAutomataSystem::getMutableChanPriorities()
{
    return chanPriorities;
}

void TimedAutomataSystem::setProcPriority(const char* name, int priority)
{
    hasPriorities |= (priority != 0);
    procPriority[name] = priority;
}

int TimedAutomataSystem::getProcPriority(const char* name) const
{
    assert(procPriority.find(name) != procPriority.end());
    return procPriority.find(name)->second;
}

bool TimedAutomataSystem::hasPriorityDeclaration() const
{
    return hasPriorities;
}

void TimedAutomataSystem::recordStrictInvariant()
{
    hasStrictInv = true;
}

bool TimedAutomataSystem::hasStrictInvariants() const
{
    return hasStrictInv;
}

void TimedAutomataSystem::recordStopWatch()
{
    stopsClock = true;
}

bool TimedAutomataSystem::hasStopWatch() const
{
    return stopsClock;
}

bool TimedAutomataSystem::hasStrictLowerBoundOnControllableEdges() const
{
    return hasStrictLowControlledGuards;
}

void TimedAutomataSystem::recordStrictLowerBoundOnControllableEdges()
{
    hasStrictLowControlledGuards = true;
}

void TimedAutomataSystem::addPosition(
    uint32_t position, uint32_t offset, uint32_t line, const std::string& path)
{
    positions.add(position, offset, line, path);
}

const Positions::line_t &TimedAutomataSystem::findPosition(uint32_t position) const
{
    return positions.find(position);
}

void TimedAutomataSystem::addError(position_t position, const std::string& msg,
                                   const std::string& context)
{
    errors.emplace_back(positions.find(position.start),
                        positions.find(position.end),
                        position, msg, context);
}

void TimedAutomataSystem::addWarning(position_t position, const std::string& msg,
                                     const std::string& context)
{
    warnings.emplace_back(positions.find(position.start),
                          positions.find(position.end),
                          position, msg, context);
}

// Returns the errors
const vector<UTAP::error_t> &TimedAutomataSystem::getErrors() const
{
    return errors;
}

// Returns the warnings
const vector<UTAP::error_t> &TimedAutomataSystem::getWarnings() const
{
    return warnings;
}

bool TimedAutomataSystem::hasErrors() const
{
    return !errors.empty();
}

bool TimedAutomataSystem::hasWarnings() const
{
    return !warnings.empty();
}

void TimedAutomataSystem::clearErrors()
{
    errors.clear();
}

void TimedAutomataSystem::clearWarnings()
{
    warnings.clear();
}

bool TimedAutomataSystem::isModified() const
{
    return modified;
}

void TimedAutomataSystem::setModified(bool mod)
{
    modified = mod;
}

iodecl_t* TimedAutomataSystem::addIODecl()
{
    global.iodecl.push_back(iodecl_t());
    return &global.iodecl.back();
}
