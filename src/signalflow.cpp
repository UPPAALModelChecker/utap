// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2005-2006 Uppsala University and Aalborg University.
   
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

#include "utap/signalflow.h"
#include "utap/common.h"

#include <list>
#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <functional>
#include <assert.h>

using std::list;
using std::map;
using std::set;
using std::ostream;
using std::istream;
using std::string;
using std::ostream_iterator;
using std::cerr;
using std::endl;

using UTAP::SignalFlow;
using UTAP::Partitioner;
using UTAP::TimedAutomataSystem;
using namespace UTAP::Constants;


SignalFlow::SignalFlow(const char* _title, TimedAutomataSystem& tas):
    verbosity(0), title(_title), cTA(NULL), cP(NULL), inp(false), out(false),
    sync(false), paramsExpanded(false)
{
/*
 * Visit all processes in the system.
 */
    list<instance_t> &ps(tas.getProcesses());
    for (list<instance_t>::iterator it=ps.begin(), e=ps.end(); it!=e; ++it)
    {
        visitProcess(*it);
    }
}

void SignalFlow::printForTron(ostream &os)
{
    for (procs_t::const_iterator p=procs.begin(), e=procs.end(); p!=e; ++p)
    {
        os << (*p)->name << ":\n  "; // automaton:
        // input channels,
        for_each((*p)->inChans.begin(), (*p)->inChans.end(),
                 print<const char*>(os, " "));
        os << ",\n  ";
        // output channels,
        for_each((*p)->outChans.begin(), (*p)->outChans.end(),
                 print<const char*>(os, " "));
        os << ",\n ";
        str2strs_t::const_iterator v;
        // input variables(channels),
        for (v = (*p)->rdVars.begin(); v != (*p)->rdVars.end(); ++v)
        {
            os << " " << v->first << "(";
            for_each(v->second.begin(), v->second.end(),
                     print<const char*>(os, " "));
            os << ")";
        }
        os << ",\n ";
        // output variables(channels);
        for (v = (*p)->wtVars.begin(); v != (*p)->wtVars.end(); ++v)
        {
            os << " " << v->first << "(";
            for_each(v->second.begin(), v->second.end(),
                     print<const char*>(os, " "));
            os << ")";
        }
        os << "\n;\n";
    }
}

void SignalFlow::printForDot(ostream &os, bool ranked, bool erd, bool cEdge)
{
    char* name = strcpy(new char[strlen(title)+1], title);
    for (uint32_t i=0, len=strlen(name); i<len; ++i)
    {
        if (!isalpha(name[i]))
        {
            name[i]='_';
        }
    }

    os << "digraph " << name << " {\n";
    os << "  model=subset; remincross=true;\n";
//    os << "  edge [decorate];\n"; // use 'dot -Edecorate' if you wish
    delete [] name;

    strs_t::const_iterator it;
    procs_t::const_iterator a;

/* Enumerate processes with common look-attributes */
    if (!procs.empty())
    {
        os << "  subgraph procs {\n";
        if (erd)
        {
            os<<"    node [shape=box,style=filled];\n";
        }
        else
        {
            os<<"    node [shape=ellipse,style=filled];\n";
        }
        os << "    ";
	
        for (procs_t::const_iterator p=procs.begin(), e=procs.end(); p!=e; ++p)
            os << (*p)->name << "; ";
        os << "\n  }\n";
    }

/* Enumerate variables, with common look-attributes */
    if (!variables.empty())
    {
        // draw variables
        /* specify attributes for all nodes */
        os << "  subgraph cluste_vars {\n";
        os << "    style=invis;\n";
        if (ranked)
        {
            os << "    rank=min;\n";
        }
        if (erd)
        {
            os << "    node [shape=diamond,color=blue];\n    ";
        }
        else
        {
            os << "    node [shape=ellipse,color=blue];\n    ";
        }
        for (it=variables.begin(); it != variables.end(); ++it)
        {
            if (transmiters.find(*it) == transmiters.end())
            {
                os << *it << "; "; // const variables are slim
            }
            else
            {
                os << *it << "[style=bold]; "; // others bold
            }
        }
        os << "\n  }\n";

/* draw variable edges */
        str2strs_t::const_iterator v;
/* first, 'variable write' edges are bold */
        os<<"  edge [style=bold,color=blue,fontcolor=blue,weight=100];\n";
        for (a = procs.begin(); a != procs.end(); ++a)
        {
            if (!(*a)->wtVars.empty())
            {
                for (v = (*a)->wtVars.begin(); v != (*a)->wtVars.end(); ++v)
                {
                    os<<"  "<<(*a)->name<< " -> " << v->first << " [label=\"(";
                    /* enumerate channels when variable is accessed */
                    for_each(v->second.begin(), v->second.end(),
                             print<const char*>(os, ","));
                    os<<")\"];\n";
                }
            }
        }
/* second, 'variable read' edges are slim  */
        os<<"  edge [style=solid,color=blue,fontcolor=blue,weight=1];\n";
        for (a = procs.begin(); a != procs.end(); ++a)
        {
            if (!(*a)->rdVars.empty())
            {
                for (v = (*a)->rdVars.begin(); v != (*a)->rdVars.end(); ++v)
                {
                    os<<"  " << v->first << " -> " <<(*a)->name<<" [label=\"(";
                    /* enumerate channels when variable is accessed */
                    for_each(v->second.begin(), v->second.end(),
                             print<const char*>(os, ","));
                    os<<")\"];\n";
                }
            }
        }
    }

/* enumerate draw channels */
    if (!channels.empty())
    {
        if (cEdge)
        { /* channels are only on edges */
            const char* src = "NO_SRC";
            const char* dst = "NO_DST";
            /* build an index of outgoing edges sorted by destination TA */
            for (a = procs.begin(); a != procs.end(); ++a)
            {
                /* traverse all outgoing channels */
                for (it=(*a)->outChans.begin(); it!=(*a)->outChans.end(); ++it)
                {
                    str2procs_t::const_iterator dests = receivers.find(*it);
                    if (dests != receivers.end())
                    { // there are destinations
                        for (procs_t::const_iterator rec =
                                 dests->second.begin();
                             rec != dests->second.end(); ++rec)
                        {
                            (*a)->outEdges[*rec].insert(*it);
                        }
                    }
                    else
                    { // no destination
                        (*a)->outEdges[NULL].insert(*it);
                    }
                }
            }
            /* display all edges: */
            os<<"  edge[style=solid,color=black,fontcolor=black,weight=50];\n";
            for (a = procs.begin(); a != procs.end(); ++a)
            {
                /* display outgoing edges: */
                for (proc2strs_t::const_iterator edge = (*a)->outEdges.begin();
                     edge != (*a)->outEdges.end(); ++edge)
                {
                    bool noDst = false;
                    // display edge:
                    if (edge->first != NULL)
                    {
                        //normal destination TA
                        os<<"  " <<(*a)->name << " -> " << edge->first->name
                          << " [label=\"[";
                    }
                    else
                    { // there was no destination TA
                        if (!noDst)
                        {
                            os<<"  "<<dst
                              <<" [style=filled,fillcolor=red];\n";
                            noDst = true;
                        }
                        os<<"  " <<(*a)->name << " -> " << dst
                          << " [label=\"[";
                    }
                    // enumerate all channels on the edge:
                    strs_t::const_iterator ch=edge->second.begin();
                    while (true)
                    {
                        os<< *ch;
                        ++ch;
                        if (ch != edge->second.end())
                        {
                            os << ",";
                        }
                        else
                        {
                            break;
                        }
                    }
                    os << "]\"];\n";
                }
                /* by now all inps with sources are displayed as outputs
                 * search and display inputs w/o sources */
                bool noSrc = false;
                for (it=(*a)->inChans.begin(); it!=(*a)->inChans.end(); ++it)
                {
                    str2procs_t::const_iterator trans = transmiters.find(*it);
                    if (trans==transmiters.end())
                    {
                        if (!noSrc)
                        {
                            os<<"  "<<src
                              <<" [style=filled,fillcolor=red];\n";
                            noSrc = true;
                        }
                        os<<"  "<<src<<" -> " << (*a)->name << " [label=\""
                          << *it << "\"];\n";
                    }
                }
            }
        }
        else
        { /* channels displayed as separate nodes (like variables) */
            os<< "  subgraph cluste_chans {\n";
            os<< "    style=invis;\n";
            if (ranked)
            {
                os<<"    rank=max;\n";
            }
            if (erd)
            {
                os<<"    node [shape=diamond,color=red];\n    ";
            }
            else
            {
                os<<"    node [shape=ellipse,color=red];\n    ";
            }
            for_each(channels.begin(), channels.end(),
                     print<const char*>(os, "; "));
            os<< "\n  }\n";

            for (a = procs.begin(); a != procs.end(); ++a)
            {
                for (it=(*a)->inChans.begin(); it!=(*a)->inChans.end(); ++it)
                {
                    os << "  " << *it << " -> " << (*a)->name << ";\n";
                }
                for (it=(*a)->outChans.begin(); it!=(*a)->outChans.end(); ++it)
                {
                    os << "  " << (*a)->name << " -> " << *it
                       << " [style=bold];\n";
                }
            }
        }
    }
    os << "}" << endl;
}

bool SignalFlow::checkParams(const symbol_t &s)
{
    if (!paramsExpanded)
    {
        if (0<=cP->templ->parameters.getIndexOf(s.getName()))
        {
            // is it parameter? find the corresponding global symbol(s)
            map<symbol_t, expression_t>::iterator e = cP->mapping.find(s);
            if (e != cP->mapping.end())
            {
                paramsExpanded = true;
                visitExpression(e->second);
                paramsExpanded = false;
            }
            else
            {
                cerr << "mapping param '"<< s.getName() << "' failed"<<endl;
                exit(EXIT_FAILURE);
            }
            return false;
        }
        else if (0<=cP->templ->frame.getIndexOf(s.getName()))
        {
            // is it local symbol? discard, no observable I/O here
            return false;
        }
    }
    // it must be global/shared
/*    if(s.getFrame().hasParent()) {// should not have a parent
        cerr << s.getName() <<" assumed to be global but it is not" << endl;
        exit(EXIT_FAILURE);
        }*/
    return true;
}

void SignalFlow::addChan(const symbol_t &s, strs_t &ids, str2procs_t& index)
{
    if (checkParams(s))
    {
        ids.insert(s.getName().c_str());
        channels.insert(s.getName().c_str());
        index[s.getName().c_str()].insert(cTA);
        cChan = s.getName().c_str();
    }
}

void SignalFlow::addVar(const symbol_t &s, str2strs_t &ids,
                         str2procs_t& index)
{
    if (checkParams(s))
    {
        ids[s.getName().c_str()].insert(cChan);
        variables.insert(s.getName().c_str());
        index[s.getName().c_str()].insert(cTA);
    }
}

static const char* noChan = "-";

void SignalFlow::visitProcess(instance_t &p)
{
    cP = &p;
    procs.insert(cTA = new proc_t(p.uid.getName().c_str()));
    processes.insert(p.uid.getName().c_str());

    const template_t* temp = p.templ;
    list<state_t>::const_iterator s = temp->states.begin();
    while (s != temp->states.end())
    {
        cChan = noChan; // invariants should not use shared
        visitExpression(s->invariant);
        ++s;
    }
    list<edge_t>::const_iterator t = temp->edges.begin();
    while (t != temp->edges.end())
    {
        cChan = noChan;// guards should not use shared
        visitExpression(t->guard);
        visitExpression(t->sync);
        visitExpression(t->assign);
        ++t;
    }
}

void SignalFlow::visitExpression(const expression_t &e)
{
    if (e.empty())
    {
        return;
    }

    switch (e.getKind())
    {
    case PLUS:
    case MINUS:
    case MULT:
    case DIV:
    case MOD:
    case BIT_AND:
    case BIT_OR:
    case BIT_XOR:
    case BIT_LSHIFT:
    case BIT_RSHIFT:
    case AND:
    case OR:
    case MIN:
    case MAX:
            /*******************************************************
             * Relational operators
             */
    case LT:
    case LE:
    case EQ:
    case NEQ:
    case GE:
    case GT:
            /*******************************************************
             * Unary operators
             */
    case NOT:
        for (uint32_t i=0; i<e.getSize(); ++i)
        {
            inp = true; out = false;
            visitExpression(e[i]);
        }
        break;
            /*******************************************************
             * Assignment operators
             */
    case ASSIGN:
    case ASSPLUS:
    case ASSMINUS:
    case ASSDIV:
    case ASSMOD:
    case ASSMULT:
    case ASSAND:
    case ASSOR:
    case ASSXOR:
    case ASSLSHIFT:
    case ASSRSHIFT:
        inp = false; out = true;
        visitExpression(e[0]);
        for (uint32_t i=1; i<e.getSize(); ++i)
        {
            inp = true;
            out = false;
            visitExpression(e[i]);
        }
        break;

            /******************************************************
             * Additional constants used by ExpressionProgram's and
             * the TypeCheckBuilder (but not by the parser, although
             * some of then ought to be used, FIXME).
             */
    case IDENTIFIER:
        if (sync) {
            if (inp) {
                addChan(e.getSymbol(), cTA->inChans, receivers);
            }
            if (out) {
                addChan(e.getSymbol(), cTA->outChans, transmiters);
            }
        } else {
            if (e.getType().getKind() == CONSTANT) {
                assert(!out);
                break;
            }
            if (inp) {
                addVar(e.getSymbol(), cTA->rdVars, receivers);
            }
            if (out) {
                addVar(e.getSymbol(), cTA->wtVars, transmiters);
            }
        }
        break;
    case CONSTANT: break; // don't care
    case ARRAY:
        visitExpression(e[0]);
        for (uint32_t i=1; i<e.getSize(); ++i)
        {
            inp = true;
            out = false;
            visitExpression(e[i]);
        }
        break;
    case POSTINCREMENT:
    case PREINCREMENT:
    case POSTDECREMENT:
    case PREDECREMENT:
        inp = true;
        out = true;
        visitExpression(e[0]);
        break;
    case UNARY_MINUS:
        inp = true;
        out = false;
        visitExpression(e[0]);
        break;
    case LIST:
        for (uint32_t i=0; i<e.getSize(); ++i)
        {
            inp = true;
            out = false;
            visitExpression(e[i]);
        }
        break;
    case DOT:// dot expression has only one subexpression?
        for (uint32_t i=0; i<e.getSize(); ++i)
            visitExpression(e[i]);
        break;
    case INLINEIF:
        pushIO();
        inp = true;
        out = false;
        visitExpression(e[0]);
        for (uint32_t i=1; i<e.getSize(); ++i)
        {
            popIO();
            pushIO();
            visitExpression(e[i]);
        }
        popIO();
        break;
    case COMMA:
        pushIO();
        for (uint32_t i=0; i<e.getSize()-1; ++i)
        {
            inp = true;
            out = false;
            visitExpression(e[i]);
        }
        popIO();
        visitExpression(e[e.getSize()-1]);
        break;
    case SYNC:
        if (e.getSync() == SYNC_QUE)
        {
            inp = true;
            out = false;
        }
        else
        {
            inp = false;
            out = true;
        }
        sync = true;
        visitExpression(e[0]);
        sync = false;
        break;
    case FUNCALL:
        // FIXME for UPPAAL >=3.5 UCode
        break;
    case DEADLOCK:
            /******************************************************
             * CTL Quantifiers
             */
    case EF:
    case EG:
    case AF:
    case AG:
    case LEADSTO:

    default:
        cerr << "unsupported expression kind" << endl;
        exit(1);
    }
}

int32_t SignalFlow::visitEmptyStatement(EmptyStatement *stat)
{
    return 0;
}

int32_t SignalFlow::visitExprStatement(ExprStatement *stat)
{
    visitExpression(stat->expr);
    return 0;
}

int32_t SignalFlow::visitIterationStatement(IterationStatement *stat)
{
// FixMe: there is mysterious field called symbol, do smth about it.
    return stat->stat->accept(this);
}

int32_t SignalFlow::visitForStatement(ForStatement *stat)
{
    visitExpression(stat->init);
    visitExpression(stat->cond);
    visitExpression(stat->step);
    return stat->stat->accept(this);
}

int32_t SignalFlow::visitWhileStatement(WhileStatement *stat)
{
    visitExpression(stat->cond);
    return stat->stat->accept(this);
}

int32_t SignalFlow::visitDoWhileStatement(DoWhileStatement *stat)
{
    int32_t res = stat->stat->accept(this);
    visitExpression(stat->cond);
    return res;
}

int32_t SignalFlow::visitBlockStatement(BlockStatement *stat)
{
    int32_t res = 0;
    BlockStatement::iterator it = stat->begin();
    while (it != stat->end())
    {
        res = (*it)->accept(this);
        ++it;
    }
    return res;
}

int32_t SignalFlow::visitSwitchStatement(SwitchStatement *stat)
{
    visitExpression(stat->cond);
    return visitBlockStatement(stat);
}

int32_t SignalFlow::visitCaseStatement(CaseStatement *stat)
{
    visitExpression(stat->cond);
    return visitBlockStatement(stat);
}

int32_t SignalFlow::visitDefaultStatement(DefaultStatement *stat)
{
    return visitBlockStatement(stat);
}

int32_t SignalFlow::visitIfStatement(IfStatement *stat)
{
    visitExpression(stat->cond);
    int32_t res = stat->trueCase->accept(this);
    if (stat->falseCase)
    {
        return stat->falseCase->accept(this);
    }
    else return res;
}
int32_t SignalFlow::visitBreakStatement(BreakStatement *stat)
{
    return 0;
}

int32_t SignalFlow::visitContinueStatement(ContinueStatement *stat)
{
    return 0;
}

int32_t SignalFlow::visitAssertStatement(UTAP::AssertStatement *stat)
{
    return 0;
}

int32_t SignalFlow::visitReturnStatement(ReturnStatement *stat)
{
    visitExpression(stat->value);
    return 0;
}

SignalFlow::~SignalFlow()
{
    procs_t::const_iterator p;
    for (p = procs.begin(); p != procs.end(); ++p) delete *p;
}

Partitioner::~Partitioner()
{
    strs_t::const_iterator s;
    for (s=chansInp.begin(); s!=chansInp.end(); ++s) free((char*)*s);
    for (s=chansOut.begin(); s!=chansOut.end(); ++s) free((char*)*s);
    chansInp.clear(); chansOut.clear();
}

inline void Partitioner::printViolation(const proc_t* proc, const char* var)
{
    if (verbosity>=1)
        cerr << "Violated rule \"" << rule << "\" for process \""
             << proc->name << "\" accessing \"" << var << "\"" << endl;
}

/**
 * Adds processes to the result which use the channels from chans list
 * according to index. Reports inconsistency if some process happens to be
 * in exclude list.
 */
void Partitioner::addProcs(const strs_t& chans, const str2procs_t& index,
                           procs_t& result, procs_t& exclude)
{

    for (strs_t::const_iterator c=chans.begin(), ce=chans.end(); c!=ce; ++c)
    {    // take each channel from the given set
        str2procs_t::const_iterator c2p;
        c2p = index.find(*c);//find processes that use the channel
        if (c2p != index.end()) {
            for (procs_t::const_iterator p=c2p->second.begin(),
                     pe=c2p->second.end(); p!=pe; ++p)
            {
                if (exclude.erase(*p) > 0) {// if process was excluded
                    procsBad.insert(*p);// report as inconsistent process
                    printViolation(*p, *c);
                } else if (result.find(*p) == result.end() &&
                           procsBad.find(*p) == procsBad.end()) {
                    // if process has not been added nor excluded, then add it:
                    if (verbosity>=3)
                        cerr << "Adding \""<<(*p)->name <<"\" using \""<<(*c)
                             <<"\" by rule \""<<rule<<"\""<<endl;
                    result.insert(*p);
                }
            }
        }
    }
}

/**
 * Takes the internal channels of each process from procs list and adds
 * them to the result list. Reports inconcistency if channel is in the
 * exclude list.
 */
void Partitioner::addIntChans(const procs_t& procs,
                              strs_t& result, strs_t& exclude)
{
    for (procs_t::const_iterator p=procs.begin(), pe=procs.end(); p!=pe; ++p)
    {// take each process from the list
        for (strs_t::const_iterator c=(*p)->inChans.begin(),
                 ce=(*p)->inChans.end(); c!=ce; ++c)
        { // consider the input channels used by the process
            if (observable.find(*c) == observable.end()) {// if not observed
                if (exclude.erase(*c) > 0) {// if it's excluded
                    chansBad.insert(*c); // report inconsistency
                    printViolation(*p, *c);
                } else if (result.find(*c) == result.end() &&
                           chansBad.find(*c) == chansBad.end()) {
                    if (verbosity>=3)
                        cerr << "Adding \""<<(*c)<<"\" because of \""
                             <<(*p)->name <<"\" by rule \""<<rule
                             <<"\""<<endl;
                    result.insert(*c);
                }
            }
        }
        for (strs_t::const_iterator c=(*p)->outChans.begin(),
                 ce=(*p)->outChans.end(); c!=ce; ++c)
        { // conside the output channels used by p
            if (observable.find(*c) == observable.end()) {// if not observed
                if (exclude.erase(*c) > 0) {// if it's excluded
                    chansBad.insert(*c);// report inconsistency
                    printViolation(*p, *c);
                } else if (result.find(*c) == result.end() &&
                           chansBad.find(*c) == chansBad.end()) {
                    if (verbosity>=3)
                        cerr << "Adding \""<<(*c)<<"\" because of \""
                             <<(*p)->name <<"\" by rule \""<<rule
                             <<"\""<<endl;
                    result.insert(*c);
                }
            }
        }
    }
}

/**
 * Takes the variables of each process from procs list and adds them to
 * the result list. Reports inconcistency if variable is in the exclude list.
 */
void Partitioner::addIntVars(const procs_t& procs, strs_t& result,
                             strs_t& exclude)
{
    for (procs_t::const_iterator p=procs.begin(), pe=procs.end(); p!=pe; ++p)
    { // take each process p
        assert(*p);
        for (str2strs_t::const_iterator v2c=(*p)->rdVars.begin(),
                 v2ce=(*p)->rdVars.end(); v2c!=v2ce; ++v2c)
        { // consider the variables being read
            if (!includes(observable.begin(), observable.end(),
                          v2c->second.begin(), v2c->second.end(), less_str()))
            {// contains non-observable channels
                if (exclude.erase(v2c->first) > 0) {
                    varsBad.insert(v2c->first);
                    printViolation(*p, v2c->first);
                } else if (result.find(v2c->first) == result.end() &&
                           varsBad.find(v2c->first) == varsBad.end()) {
                    if (verbosity>=3)
                        cerr << "Adding \""<<(v2c->first)<<"\" because of \""
                             <<(*p)->name <<"\" by rule \""<<rule<<"\""<<endl;
                    result.insert(v2c->first);
                }
            }// else used only observably
        }
        for (str2strs_t::const_iterator v2c=(*p)->wtVars.begin(),
                 v2ce=(*p)->wtVars.end(); v2c!=v2ce; ++v2c)
        { // consider the variables being written to by p
            if (!includes(observable.begin(), observable.end(),
                          v2c->second.begin(), v2c->second.end(), less_str()))
            {// contains non-observable channels
                if (exclude.erase(v2c->first) > 0) {
                    varsBad.insert(v2c->first);
                    printViolation(*p, v2c->first);
                } else if (result.find(v2c->first) == result.end() &&
                           varsBad.find(v2c->first) == varsBad.end()) {
                    if (verbosity>=3)
                        cerr << "Adding \""<<(v2c->first)<<"\" because of \""
                             <<(*p)->name <<"\" by rule \""<<rule<<"\""<<endl;
                    result.insert(v2c->first);
                }
            }// else used only observably
        }
    }
}

/**
 * Take all variables and add all accessing processes to the list.
 * Report inconcistencies if process happens to be in exclude list.
 */
void Partitioner::addProcsByVars(const strs_t& vars, procs_t& procs,
                                 procs_t& exclude)
{
    str2procs_t::const_iterator v2p;
    str2strs_t::const_iterator v2c;
    for (strs_t::const_iterator v=vars.begin(), ve=vars.end(); v!=ve; ++v)
    { // take every variable v from the vars list
        v2p=receivers.find(*v); // find list of processes that read from v
        if (v2p != receivers.end()) {
            for(procs_t::const_iterator p=v2p->second.begin(),
                    pe=v2p->second.end(); p!=pe; ++p)
            {// take each process reading the value of v
                v2c = (*p)->rdVars.find(*v);
                if (v2c != (*p)->rdVars.end()) {
                    if (!includes(observable.begin(), observable.end(),
                                  v2c->second.begin(), v2c->second.end(),
                                  less_str()))
                    {// has unobservable synchronizations
                        if (exclude.erase(*p) > 0) {
                            procsBad.insert(*p);
                            printViolation(*p, *v);
                        } else if (procs.find(*p) == procs.end() &&
                                   procsBad.find(*p) == procsBad.end()) {
                            if (verbosity>=3)
                                cerr << "Adding \""<<(*p)->name
                                     <<"\" using \""<<(*v)
                                     <<"\" by rule \""<<rule<<"\""<<endl;
                            procs.insert(*p);
                        }
                    }// else used observably
                } else {
                    if (verbosity>=1)
                        cerr<<"addProcsByVars could not find in rdVars"<<endl;
                }
            }
        } else {
            if (verbosity>=1)
                cerr << "addProcsByVars could not find readers"<<endl;
        }
        v2p=transmiters.find(*v);
        if (v2p != transmiters.end()) {
            for(procs_t::const_iterator p=v2p->second.begin(),
                    pe=v2p->second.end(); p!=pe; ++p)
            { // consider the process p which writes to v
                v2c = (*p)->wtVars.find(*v);
                if (v2c != (*p)->wtVars.end()) {
                    if (!includes(observable.begin(), observable.end(),
                                  v2c->second.begin(), v2c->second.end(),
                                  less_str()))
                    {// has unobservable synchronizations
                        if (exclude.erase(*p) > 0) {
                            procsBad.insert(*p);
                            printViolation(*p, *v);
                        } else if (procs.find(*p) == procs.end() &&
                                   procsBad.find(*p) == procsBad.end()) {
                            if (verbosity>=3)
                                cerr << "Adding \""<<(*p)->name
                                     <<"\" using \""<<(*v)
                                     <<"\" by rule \""<<rule<<"\""<<endl;
                            procs.insert(*p);
                        }
                    }// else used observably
                } else {
                    if (verbosity>=1)
                        cerr<<"addProcsByVars could not find in wtVars"<<endl;
                }
            }
        } else {
            if (verbosity>=1)
                cerr<<"addProcsByVars could not find writers for "<<(*v)<<endl;
        }
    }
}

char* get_token(istream& in)
{
    string buffer="";
    char c;
    while (in.get(c)) {
        if (isalnum(c) || c=='_') buffer += c;
        else {
            if (c=='(') while (in.get(c) && c!=')') ; // ignore "(...)"
            if (buffer.length()>0)
            return strdup(buffer.c_str());
        }
    }
    if (buffer.length()>0) return strdup(buffer.c_str());
    else return NULL;
}

int Partitioner::partition(istream& ioinfo)
{
    char* token;
    strs_t inputs, outputs;
    std::ios::fmtflags flags = ioinfo.flags();
    ioinfo.unsetf(std::ios::skipws);
    token = get_token(ioinfo);
    if (strcmp(token, "input")!=0) {
        cerr << "\"input\" is expected instead of \""<<token<<"\"" << endl;
        free(token); // get rid of "input"
        exit(EXIT_FAILURE);
    }
    free(token); // get rid of "input"
    while ((token = get_token(ioinfo)) != NULL &&
           strcmp(token, "output") != 0)
        inputs.insert(token);

    if (token == NULL) {
        cerr << "\"output\" expected, but EOF found" << endl;
        exit(EXIT_FAILURE);
    }
    free(token);// get rid of "output"
    while ((token = get_token(ioinfo)) != NULL &&
           strcmp(token, "precision")!=0 && strcmp(token, "timeout")!=0)
        outputs.insert(token);

    ioinfo.flags(flags);
    int res = partition(inputs, outputs);
    strs_t::const_iterator s;
    for (s=inputs.begin(); s!=inputs.end(); ++s) free((char*)*s);
    for (s=outputs.begin(); s!=outputs.end(); ++s) free((char*)*s);
    return res;
}

int Partitioner::partition(const strs_t& inputs, const strs_t& outputs)
{
    procsEnv.clear(); procsIUT.clear();
    chansIntEnv.clear(); chansIntIUT.clear();
    varsEnv.clear(); varsIUT.clear();
    strs_t::const_iterator s;
    for (s=chansInp.begin(); s!=chansInp.end(); ++s) free((char*)*s);
    for (s=chansOut.begin(); s!=chansOut.end(); ++s) free((char*)*s);
    chansInp.clear(); chansOut.clear();

    for (s=inputs.begin(); s!=inputs.end(); ++s)
        chansInp.insert(strdup(*s));
    for (s=outputs.begin(); s!=outputs.end(); ++s)
        chansOut.insert(strdup(*s));

    observable.clear();
    observable.insert(chansInp.begin(), chansInp.end());
    observable.insert(chansOut.begin(), chansOut.end());

    if (verbosity>=3) {
        cerr << "Inputs:  " << chansInp << endl;
        cerr << "Outputs: " << chansOut << endl;
    }

    size_t oldProgress=0, progress=0;
    do {
        oldProgress = progress;
/* Environment processes shout on inputs and listens to outputs, while IUT
 * processes shout on outputs and listen to inputs. */
        rule="transmitters on input channels belong to Env";
        addProcs(inputs, transmiters, procsEnv, procsIUT);
        rule="receivers on output channels belong to Env";
        addProcs(outputs, receivers, procsEnv, procsIUT);
        rule="receivers on input channels belong IUT";
        addProcs(inputs, receivers, procsIUT, procsEnv);
        rule="transmitters on output channels belong IUT";
        addProcs(outputs, transmiters, procsIUT, procsEnv);

/* 1) channels, that are not declared as inputs/outputs, are non-observable,
 *    called internal.*/

/* 2) internal channel belongs to environment (IUT) if it is used by
 *    environment (IUT) process (respectively). Model is inconsistent and
 *    cannot be partitioned if the internal channel is used by both environment
 *    and IUT. */
        rule="internal channel belongs to Env if it is used by Env";
        addIntChans(procsEnv, chansIntEnv, chansIntIUT);
        rule="internal channel belongs to IUT if it is used by IUT";
        addIntChans(procsIUT, chansIntIUT, chansIntEnv);

/* 3) process belongs to environment (IUT) if it uses the internal environment
 *    (IUT) channel (respectively). */
        rule="process belongs to Env if it shouts on internal Env channel";
        addProcs(chansIntEnv, transmiters, procsEnv, procsIUT);
        rule="process belongs to Env if it listens to internal Env channel";
        addProcs(chansIntEnv, receivers, procsEnv, procsIUT);
        rule="process belongs to IUT if it shouts on internal IUT channel";
        addProcs(chansIntIUT, transmiters, procsIUT, procsEnv);
        rule="process belongs to IUT if it listens to internal IUT channel";
        addProcs(chansIntIUT, receivers, procsIUT, procsEnv);

/* 4) variable belongs to environment (IUT) if it is accessed by environment
 *    (IUT) process without observable input/output channel synchronization.
 *    Variable is not cathegorized (can be either) if accessed consistently
 *    only during observable input/output channel synchronization. */
        rule="variable belongs to Env if accessed by Env without observable sync";
        addIntVars(procsEnv, varsEnv, varsIUT);
        rule="variable belongs to IUT if accessed by IUT without observable sync";
        addIntVars(procsIUT, varsIUT, varsEnv);

/* 5) process belongs to environment (IUT) if it accesses environment (IUT)
 *    variable (respectively) without observable channel synchronization. */
        rule="process belongs to Env if it access Env variable without observable synchronization";
        addProcsByVars(varsEnv, procsEnv, procsIUT);
        rule="process belongs to IUT if it access IUT variable without observable synchronization";
        addProcsByVars(varsIUT, procsIUT, procsEnv);
        progress = procsEnv.size() + procsIUT.size() + procsBad.size();
    } while (progress>oldProgress);
    procs_t::const_iterator p;

    if (verbosity>=3) {
        cerr << "==== Partitioned =========================================\n";
        cerr << "Env procs: " << procsEnv << endl;
        cerr << "Env chans: " << chansIntEnv << endl;
        cerr << "Env vars:  " << varsEnv << endl;
        cerr << "----------------------------------------------------------\n";
        cerr << "IUT procs: " << procsIUT << endl;
        cerr << "IUT chans: " << chansIntIUT << endl;
        cerr << "IUT vars:  " << varsIUT << endl;
        cerr << "==========================================================\n";
    }
    if (verbosity>=1) {
        if (!procsBad.empty())
            cerr << "Inconsistent procs: " << procsBad << endl;
        if (!chansBad.empty())
            cerr << "Inconsistent chans: " << chansBad << endl;
        if (!varsBad.empty())
            cerr << "Inconsistent vars:  " << varsBad << endl;
    }
    if (verbosity>=2) {
        procs_t leftovers;
        for (p=procs.begin(); p!=procs.end(); ++p)
            if (procsEnv.find(*p) == procsEnv.end() &&
                procsIUT.find(*p) == procsIUT.end())
                leftovers.insert(*p);
        if (!leftovers.empty()) {
            cerr << "==== Not partitioned: ====================================\n";
            cerr << "procs: " << leftovers << endl;
        }
    }

    if (!procsBad.empty() || !chansBad.empty() || !varsBad.empty()) return 2;
    if (progress==procs.size()) return 0; // all procs are partitioned
    else return 1;// some left unpartitioned
}

#define BADSTYLE "style=filled,fillcolor=\"#FF8080\""
#define IUTSTYLE "style=filled,fillcolor=\"#B8C0FF\""
#define ENVSTYLE "style=filled,fillcolor=\"#C8FFC8\""
#define MEDSTYLE "style=filled,fillcolor=\"#A0A0A0\""

void Partitioner::printForDot(ostream &os, bool ranked, bool erd, bool cEdge)
{
    char* name = strcpy(new char[strlen(title)+1], title);
    for (uint32_t i=0; i<strlen(name); ++i)
    {
        if (!isalpha(name[i]))
        {
            name[i]='_';
        }
    }

    os << "digraph " << name << " {\n";
    delete [] name;
    os << "// printer friendly options, fill A4 landscape:\n"
        "  size=\"10.2,7.8\"; ratio=fill; margin=0.2;\n"
        "  nodesep=0.3; // separation of labelled edges\n\n"
        "// fdp options:\n"
        "  K=1.25;\n\n"
        "// neato options:\n"
        "  epsilon=0.0001;\n\n"
        "  node[fontname=\"Helvetica-Bold\"];\n"
        "  edge[fontname=\"Helvetica\",fontsize=10];\n\n"
        "// legend:\n"
        "//  process[shape=ellipse]; int[shape=rectangle]; chan[shape=diamond];\n\n";

    procs_t::const_iterator p, pe;
    ostream_iterator<const char*> osi(os, "; ");

    if (!procsBad.empty()) {
        os << "// processes in conflict:\n"
            "  node [shape=ellipse,peripheries=1," BADSTYLE "];\n  ";
        for (p = procsBad.begin(), pe = procsBad.end(); p!=pe; ++p)
            os << (*p)->name << "; ";
        os << endl;
    }
    if (!chansBad.empty()) {
        os << "// channels in conflict:\n"
            "  node [shape=diamond,peripheries=1," BADSTYLE "];\n  ";
        copy(chansBad.begin(), chansBad.end(), osi);
        os << endl;
    }
    if (!varsBad.empty()) {
        os << "// variables in conflict:\n"
            "  node [shape=diamond,peripheries=1," BADSTYLE "];\n  ";
        copy(varsBad.begin(), varsBad.end(), osi);
        os << endl;
    }

    os << "// IUT processes:\n";
    if (!procsIUT.empty()) {
        os<<"  node [shape=ellipse,peripheries=1," IUTSTYLE "];\n  ";
        for (p = procsIUT.begin(), pe = procsIUT.end(); p!=pe; ++p)
            os << (*p)->name << "; ";
        os << endl;
    }
    os << "// IUT channels:\n";
    if (!chansIntIUT.empty()) {
        os<<"  node [shape=diamond,peripheries=1," IUTSTYLE "];\n  ";
        copy(chansIntIUT.begin(), chansIntIUT.end(), osi);
        os << endl;
    }
    os << "// IUT variables:\n";
    if (!varsIUT.empty()) {
        os<<"  node [shape=rectangle,peripheries=1," IUTSTYLE "];\n  ";
        copy(varsIUT.begin(), varsIUT.end(), osi);
        os << endl;
    }

    if (!chansOut.empty()) {
        os << "// observable output channels (controlled by IUT):\n"
            "  node [shape=diamond,peripheries=2," IUTSTYLE "];\n  ";
        copy(chansOut.begin(), chansOut.end(), osi);
        os << endl;
    }
    if (!chansInp.empty()) {
        os << "// observable input channels (controlled by Env):\n"
            "  node [shape=diamond,peripheries=2," ENVSTYLE "];\n  ";
        copy(chansInp.begin(), chansInp.end(), osi);
        os << endl;
    }

    os << "// Env processes:\n";
    if (!procsEnv.empty()) {
        os<<"  node [shape=ellipse,peripheries=1," ENVSTYLE "];\n  ";
        for (p = procsEnv.begin(), pe = procsEnv.end(); p!=pe; ++p)
            os << (*p)->name << "; ";
        os << endl;
    }
    os << "// Env channels:\n";
    if (!chansIntEnv.empty()) {
        os<<"  node [shape=diamond,peripheries=1," ENVSTYLE "];\n  ";
        copy(chansIntEnv.begin(), chansIntEnv.end(), osi);
        os << endl;
    }
    os << "// Env variables:\n";
    if (!varsEnv.empty()) {
        os<<"  node [shape=rectangle,peripheries=1," ENVSTYLE "];\n  ";
        copy(varsEnv.begin(), varsEnv.end(), osi);
        os << endl;
    }
    os << "// set attributes for non-partitioned procs/chans/vars:\n"
       << "  node [shape=rectangle,peripheries=1," MEDSTYLE "];\n\n";

/* draw variable edges */
    str2strs_t::const_iterator v2c;
    os << "// edges for write to variable:\n"
       << "  edge [style=bold];\n";
    for (p = procs.begin(), pe = procs.end(); p!=pe; ++p) {
        if (!(*p)->wtVars.empty()) {
            for (v2c = (*p)->wtVars.begin(); v2c != (*p)->wtVars.end(); ++v2c){
                os<<"  "<<(*p)->name<< " -> " << v2c->first << " [label=\"(";
/* enumerate channels when variable is accessed */
                for_each(v2c->second.begin(), v2c->second.end(),
                         print<const char*>(os, ","));
                os<<")\"];\n";
            }
        }
    }
    os << "// edges for read of variable:\n"
       << "  edge [style=solid];\n";
    for (p = procs.begin(), pe = procs.end(); p!=pe; ++p) {
        if (!(*p)->rdVars.empty()) {
            for (v2c = (*p)->rdVars.begin(); v2c != (*p)->rdVars.end(); ++v2c){
                os<<"  " << v2c->first << " -> " <<(*p)->name<<" [label=\"(";
/* enumerate channels when variable is accessed */
                for_each(v2c->second.begin(), v2c->second.end(),
                         print<const char*>(os, ","));
                os<<")\"];\n";
            }
        }
    }

/* enumerate draw channels */
    if (!channels.empty())
    {
        ;
        if (!cEdge)
        { /* channels displayed as separate nodes (like variables) */
            os << "// channel transmit edges:\n"
               << "  edge [style=bold];\n";
            for (p = procs.begin(), pe = procs.end(); p!=pe; ++p) {
                for (strs_t::const_iterator c=(*p)->outChans.begin(),
                         ce=(*p)->outChans.end(); c!=ce; ++c)
                {
                    os << "  " << (*p)->name << " -> " << *c << ";\n";
                }
            }
            os << "// channel receive edges:\n"
               << "  edge [style=solid];\n";
            for (p = procs.begin(), pe = procs.end(); p!=pe; ++p) {
                for (strs_t::const_iterator c=(*p)->inChans.begin(),
                         ce=(*p)->inChans.end(); c!=ce; ++c)
                {
                    os << "  " << *c << " -> " << (*p)->name << ";\n";
                }
            }
        } else { /* channels are only on edges */
            const char* src = "NO_SRC";
            const char* dst = "NO_DST";
            /* build an index of outgoing edges sorted by destination TA */
            for (p = procs.begin(), pe = procs.end(); p!=pe; ++p)
            {
                /* traverse all outgoing channels */
                for (strs_t::const_iterator c=(*p)->outChans.begin(),
                         ce=(*p)->outChans.end(); c!=ce; ++c)
                {
                    str2procs_t::const_iterator dests = receivers.find(*c);
                    if (dests != receivers.end())
                    { // there are destinations
                        for (procs_t::const_iterator rec =
                                 dests->second.begin();
                             rec != dests->second.end(); ++rec)
                        {
                            (*p)->outEdges[*rec].insert(*c);
                        }
                    }
                    else
                    { // no destination
                        (*p)->outEdges[NULL].insert(*c);
                    }
                }
            }
            /* display all edges: */
            os<<"  edge[style=solid];\n";
            for (p = procs.begin(), pe = procs.end(); p!=pe; ++p)
            {
                /* display outgoing edges: */
                for (proc2strs_t::const_iterator edge = (*p)->outEdges.begin();
                     edge != (*p)->outEdges.end(); ++edge)
                {
                    bool noDst = false;
                    // display edge:
                    if (edge->first != NULL)
                    {
                        //normal destination TA
                        os<<"  " <<(*p)->name << " -> " << edge->first->name
                          << " [label=\"[";
                    }
                    else
                    { // there was no destination TA
                        if (!noDst)
                        {
                            os<<"  "<<dst
                              <<" [style=filled,fillcolor=red];\n";
                            noDst = true;
                        }
                        os<<"  " <<(*p)->name << " -> " << dst
                          << " [label=\"[";
                    }
                    // enumerate all channels on the edge:
                    strs_t::const_iterator ch=edge->second.begin();
                    while (true)
                    {
                        os<< *ch;
                        ++ch;
                        if (ch != edge->second.end())
                        {
                            os << ",";
                        }
                        else
                        {
                            break;
                        }
                    }
                    os << "]\"];\n";
                }
                /* by now all inps with sources are displayed as outputs
                 * search and display inputs w/o sources */
                bool noSrc = false;
                for (strs_t::const_iterator c=(*p)->inChans.begin(),
                         ce=(*p)->inChans.end(); c!=ce; ++c)
                {
                    str2procs_t::const_iterator trans = transmiters.find(*c);
                    if (trans==transmiters.end())
                    {
                        if (!noSrc)
                        {
                            os<<"  "<<src
                              <<" [style=filled,fillcolor=red];\n";
                            noSrc = true;
                        }
                        os<<"  "<<src<<" -> " << (*p)->name << " [label=\""
                          << *c << "\"];\n";
                    }
                }
            }
        }
    }
    os << "}" << endl;
}

void Partitioner::fillWithEnvProcs(strs_t& procs)
{
    for (procs_t::const_iterator p=procsEnv.begin(); p!=procsEnv.end(); ++p)
        procs.insert((*p)->name);
}

void Partitioner::fillWithIUTProcs(strs_t& procs)
{
    for (procs_t::const_iterator p=procsIUT.begin(); p!=procsIUT.end(); ++p)
        procs.insert((*p)->name);
}

