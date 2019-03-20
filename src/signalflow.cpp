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

#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include <algorithm>
#include <functional>
#include <cassert>

using std::list;
using std::deque;
using std::map;
using std::set;
using std::ostream;
using std::istream;
using std::string;
using std::ostream_iterator;
using std::cerr;
using std::endl;
using UTAP::DistanceCalculator;
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
 * FIXME: it does not take care of autocompleted parameters, 
 *        unfolding is intricate and is done outside UTAP.
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

void SignalFlow::printProcsForDot(ostream &os, bool erd)
{
/* Enumerate processes with common look-attributes */
    os << "  subgraph procs {\n";
    if (erd)
    {
        os<<"    node [shape=rectangle,style=filled];\n";
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

void SignalFlow::printVarsForDot(ostream &os, bool ranked, bool erd)
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
        os << "    node [shape=rectangle,color=blue];\n    ";
    }
    for (strs_t::const_iterator i=variables.begin(), e=variables.end(); 
         i!=e; ++i)
    {
        if (transmitters.find(*i) == transmitters.end())
        {
            os << *i << "; "; // const variables are slim
            }
        else
        {
            os << *i << "[style=bold]; "; // others bold
        }
    }
    os << "\n  }\n";
}

void SignalFlow::printVarsWriteForDot(ostream &os)
{
    /* 'variable write' edges are bold */
    os<<"  edge [style=bold,color=blue,fontcolor=blue,weight=100];\n";
    /* draw variable write edges */
    for (procs_t::const_iterator a=procs.begin(), ae=procs.end(); a!=ae; ++a)
    {
        if (!(*a)->wtVars.empty())
        {
            for (str2strs_t::const_iterator v=(*a)->wtVars.begin(),
                     ve=(*a)->wtVars.end(); v!=ve; ++v)
            {
                os<<"  "<<(*a)->name<< " -> " << v->first << " [label=\"(";
                /* enumerate channels when variable is accessed */
                for_each(v->second.begin(), v->second.end(),
                         print<const char*>(os, ","));
                os<<")\"];\n";
            }
        }
    }
}

void SignalFlow::printVarsReadForDot(ostream &os)
{
    /* 'variable read' edges are slim  */
    os<<"  edge [style=solid,color=blue,fontcolor=blue,weight=1];\n";
    /* draw variable edges */
    for (procs_t::const_iterator a=procs.begin(),ae=procs.end(); a!=ae; ++a)
    {
        if (!(*a)->rdVars.empty())
        {
            for (str2strs_t::const_iterator v = (*a)->rdVars.begin(),
                     ve=(*a)->rdVars.end(); v!=ve; ++v)
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

void SignalFlow::printChansOnEdgesForDot(ostream &os)
{
    /* channels appear only on I/O edges */
    const char* src = "NO_SRC";
    const char* dst = "NO_DST";
    /* build an index of outgoing edges sorted by destination TA */
    for (procs_t::const_iterator a=procs.begin(),ae=procs.end(); a!=ae; ++a)
    {
        /* traverse all outgoing channels */
        for (strs_t::const_iterator i=(*a)->outChans.begin(), 
                 e=(*a)->outChans.end(); i!=e; ++i)
        {
            str2procs_t::const_iterator dests = receivers.find(*i);
            if (dests != receivers.end())
            { // there are destinations
                for (procs_t::const_iterator rec = dests->second.begin();
                     rec != dests->second.end(); ++rec)
                {
                    (*a)->outEdges[*rec].insert(*i);
                }
            }
            else
            { // no destination
                (*a)->outEdges[NULL].insert(*i);
            }
        }
    }
    bool noDst = false;
    /* display all edges: */
    os<<"  edge[style=solid,color=black,fontcolor=black,weight=50];\n";
    for (procs_t::const_iterator a=procs.begin(),ae=procs.end(); a!=ae; ++a)
    {
        /* display outgoing edges: */
        for (proc2strs_t::const_iterator edge = (*a)->outEdges.begin(),
                 edgeEnd=(*a)->outEdges.end(); edge!=edgeEnd; ++edge)
        {
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
        for (strs_t::const_iterator i=(*a)->inChans.begin(), 
                 e=(*a)->inChans.end(); i!=e; ++i)
        {
            str2procs_t::const_iterator trans = transmitters.find(*i);
            if (trans==transmitters.end())
            {
                if (!noSrc)
                {
                    os<<"  "<<src
                      <<" [style=filled,fillcolor=red];\n";
                    noSrc = true;
                }
                os<<"  "<<src<<" -> " << (*a)->name << " [label=\""
                  << *i << "\"];\n";
            }
        }
    }
}

void SignalFlow::printChansSeparateForDot(ostream &os, bool ranked, bool erd)
{
    /* channels displayed as separate nodes (like variables) */
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
        os<<"    node [shape=diamond,color=red];\n    ";
    }
    for_each(channels.begin(), channels.end(),
             print<const char*>(os, "; "));
    os<< "\n  }\n";
    
    for (procs_t::const_iterator a=procs.begin(),ae=procs.end(); a!=ae; ++a)
    {
        for (strs_t::const_iterator i=(*a)->inChans.begin(), 
                 e=(*a)->inChans.end(); i!=e; ++i)
        {
            os << "  " << *i << " -> " << (*a)->name << ";\n";
        }
        for (strs_t::const_iterator i=(*a)->outChans.begin(),
                 e=(*a)->outChans.end(); i!=e; ++i)
        {
            os << "  " << (*a)->name << " -> " << *i << " [style=bold];\n";
        }
    }
}

void SignalFlow::printForDot(ostream &os, bool ranked, bool erd, bool cEdge)
{
    char* name = strcpy(new char[strlen(title)+1], title);
    for (uint32_t i=0, len=strlen(name); i<len; ++i)
    {
        if (!isalpha((unsigned char)name[i])) // Cast to avoid undefined behavior.
        {
            name[i]='_';
        }
    }

    os << "digraph " << name << " {\n";
    os << "  model=subset; remincross=true;\n";
//    os << "  edge [decorate];\n"; // use 'dot -Edecorate' if you wish
    delete [] name;

    if (!procs.empty()) printProcsForDot(os, erd);

/* Enumerate variables, with common look-attributes */
    if (!variables.empty()) {
        printVarsForDot(os, ranked, erd);
        printVarsWriteForDot(os);
        printVarsReadForDot(os);
    }

/* enumerate draw channels */
    if (!channels.empty()) {
        if (cEdge) printChansOnEdgesForDot(os);
        else printChansSeparateForDot(os, ranked, erd);
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

void SignalFlow::addChan(const std::string &s, strs_t &ids, str2procs_t& index)
{
    const char* s2;
    strs_t::iterator it = channels.find(s.c_str());
    if (it == channels.end()) {
        s2 = strdup(s.c_str());
        channels.insert(s2);
    } else s2 = *it;
    ids.insert(s2);
    index[s2].insert(cTA);
    cChan = s2;
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
    deque<state_t>::const_iterator s = temp->states.begin();
    while (s != temp->states.end())
    {
        cChan = noChan; // invariants should not use shared
        visitExpression(s->invariant);
        ++s;
    }
    deque<edge_t>::const_iterator t; 
    for (t = temp->edges.begin(); t != temp->edges.end(); ++t)
    {
        cChan = noChan;// guards should not use shared
        visitExpression(t->guard);
        visitExpression(t->sync);
        visitExpression(t->assign);
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
    case FRACTION:
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
    case FORALL:
    case EXISTS:
    case SUM:
        // the first expression is an inline (local) declaration (don't care)
        // the second is side-effect-free, hence read-only expression
        assert(e.getSize()==2);
        inp = true; out = false;
        visitExpression(e[1]);
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
        if (sync) { // channel synchronization
            if (checkParams(e.getSymbol())) {
                chanString.append(e.getSymbol().getName());
            }
        } else { // variable access
            if (e.getType().getKind() == CONSTANT) { // constant
                assert(!out);
                break;
            } 
            symbol_t sym = e.getSymbol();
            if (sym.getFrame().hasParent()) { // local variable
                if (refparams.size()==0) break; // local process variable
                // else: local function variable
                exprref_t::const_iterator exi = refparams.top().find(sym);
                if (exi != refparams.top().end()) { // passed by reference
                    visitExpression(exi->second);
                    break;
                }
                exi = valparams.top().find(sym);
                if (exi != valparams.top().end()) { // passed by value
                    if (inp) {
                        pushIO();
                        out = false;// any writes to local copy are lost
                        visitExpression(exi->second);
                        popIO();
                    }
                    break;
                }
                // else: local function variable but not parameter, don't care
            } else { // global variable
                if (inp) addVar(sym, cTA->rdVars, receivers);
                if (out) addVar(sym, cTA->wtVars, transmitters);
            }
        }
        break;
    case CONSTANT:
        if (sync) {
            std::ostringstream os;
            os << e.getValue();
            chanString.append(os.str());
        }
        break; 
    case ARRAY:
        visitExpression(e[0]);
        if (sync) chanString.append("[");
        pushIO();
        for (uint32_t i=1; i<e.getSize(); ++i)
        {
            inp = true;
            out = false;
            visitExpression(e[i]);
        }
        popIO();
        if (sync) {
            chanString.append("]");
        }
        break;
    case RATE:
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
        switch(e.getSync())
        {
        case SYNC_QUE:
            inp = true;
            out = false;
            break;
        case SYNC_BANG:
            inp = false;
            out = true;
            break;
        case SYNC_CSP:
            // Marius may want to hack this differently.
            inp = false;
            out = false;
        }
        sync = true;
        chanString.clear();
        visitExpression(e[0]);
        if (inp) {
            addChan(chanString, cTA->inChans, receivers);
//            std::cerr << cTA->name << " receives on " << chanString << endl;
        }
        if (out) {
            addChan(chanString, cTA->outChans, transmitters);
//            std::cerr << cTA->name << " sends on " << chanString << endl;
        }
        sync = false;
        break;
    case FUNCALL:
    {// create a map of parameter symbol to argument expression
        const symbol_t& fnsym = e.getSymbol();// function symbol
        assert(fnsym.getType().getKind()==FUNCTION);
        const function_t* fn = static_cast<const function_t*>(fnsym.getData());
        BlockStatement* body = fn->body;
        const frame_t& frame = body->getFrame();
        refparams.push(exprref_t());
        valparams.push(exprref_t());
        for (size_t i=0; i<e.getSize()-1; ++i) {
            symbol_t param = frame[i];
            const type_t& ptype = param.getType();
            if (ptype.is(REF)) refparams.top()[param] = e[i+1];
            else valparams.top()[param] = e[i+1];
        }
        body->accept(this);// see which parameters are touched
        refparams.pop();
        valparams.pop();
    }
    break;

    default:
        cerr << "unsupported kind (" << e.getKind()
             << ") of expression, please report it to developers."<<endl;
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
    strs_t::const_iterator c;
    for (c = channels.begin(); c != channels.end(); ++c) delete *c;
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
        v2p=transmitters.find(*v);
        if (v2p != transmitters.end()) {
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
        if (isalnum((unsigned char)c) || c=='_' || c=='[' || c==']') buffer += c;
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
    if (token) {
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
        if (token != NULL) free(token);
    }
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
        addProcs(inputs, transmitters, procsEnv, procsIUT);
        rule="receivers on output channels belong to Env";
        addProcs(outputs, receivers, procsEnv, procsIUT);
        rule="receivers on input channels belong IUT";
        addProcs(inputs, receivers, procsIUT, procsEnv);
        rule="transmitters on output channels belong IUT";
        addProcs(outputs, transmitters, procsIUT, procsEnv);

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
        addProcs(chansIntEnv, transmitters, procsEnv, procsIUT);
        rule="process belongs to Env if it listens to internal Env channel";
        addProcs(chansIntEnv, receivers, procsEnv, procsIUT);
        rule="process belongs to IUT if it shouts on internal IUT channel";
        addProcs(chansIntIUT, transmitters, procsIUT, procsEnv);
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
#define MEDSTYLE "style=filled,fillcolor=\"#C0C0C0\""

inline void set_remove(SignalFlow::strs_t& from, 
                       const SignalFlow::strs_t& what) 
{
    for (SignalFlow::strs_t::const_iterator b=what.begin(), e=what.end(); 
         b!=e; ++b)
        from.erase(*b);
}

struct surround: public std::unary_function<const char*, void>
{
    ostream &out;
    const char* pre;
    const char* post;
    surround(ostream &os, const char* prefix, const char* postfix):
        out(os), pre(prefix), post(postfix) {}
    void operator()(const char* x) {
        out << pre << x << post;
    }
};


void Partitioner::printForDot(ostream &os, bool ranked, bool erd, bool cEdge)
{
    char* name = strcpy(new char[strlen(title)+1], title);
    for (uint32_t i=0; i<strlen(name); ++i)
    {
        if (!isalpha((unsigned char)name[i]))
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
        "// process[shape=ellipse]; int[shape=rectangle]; chan[shape=diamond];\n\n";

    procs_t::const_iterator p, pe;
    strs_t procsR(processes), chansR(channels), varsR(variables); // remaining
    
    ostream_iterator<const char*> osi(os, "; ");

    if (!procsBad.empty()) {
        os << "// processes in conflict:\n"
            "  node [shape=ellipse,peripheries=1," BADSTYLE "];\n  ";
        for (p = procsBad.begin(), pe = procsBad.end(); p!=pe; ++p) {
            os << (*p)->name << "; ";
            procsR.erase((*p)->name);
        }
        os << endl;
    }
    if (!chansBad.empty()) {
        os << "// channels in conflict:\n"
            "  node [shape=diamond,peripheries=1," BADSTYLE "];\n  ";
        for_each(chansBad.begin(), chansBad.end(), 
                 surround(os, "\"", "\"; "));
//        copy(chansBad.begin(), chansBad.end(), osi);
        set_remove(chansR, chansBad);
        os << endl;
    }
    if (!varsBad.empty()) {
        os << "// variables in conflict:\n"
            "  node [shape=diamond,peripheries=1," BADSTYLE "];\n  ";
        copy(varsBad.begin(), varsBad.end(), osi);
        set_remove(varsR, varsBad);
        os << endl;
    }

    if (!procsIUT.empty()) {
        os << "// IUT processes:\n";
        os << "  node [shape=ellipse,peripheries=1," IUTSTYLE "];\n  ";
        for (p = procsIUT.begin(), pe = procsIUT.end(); p!=pe; ++p) {
            os << (*p)->name << "; ";
            procsR.erase((*p)->name);
        }
        os << endl;
    }
    if (!chansIntIUT.empty()) {
        os << "// IUT channels:\n";
        os << "  node [shape=diamond,peripheries=1," IUTSTYLE "];\n  ";
        for_each(chansIntIUT.begin(), chansIntIUT.end(), 
                 surround(os, "\"", "\"; "));
//        copy(chansIntIUT.begin(), chansIntIUT.end(), osi);
        set_remove(chansR, chansIntIUT);
        os << endl;
    }
    if (!varsIUT.empty()) {
        os << "// IUT variables:\n";
        os << "  node [shape=rectangle,peripheries=1," IUTSTYLE "];\n  ";
        copy(varsIUT.begin(), varsIUT.end(), osi);
        set_remove(varsR, varsIUT);
        os << endl;
    }

    if (!chansOut.empty()) {
        os << "// observable output channels (controlled by IUT):\n"
            "  node [shape=diamond,peripheries=2," IUTSTYLE "];\n  ";
        for_each(chansOut.begin(), chansOut.end(), 
                 surround(os, "\"", "\"; "));
//        copy(chansOut.begin(), chansOut.end(), osi);
        set_remove(chansR, chansOut);
        os << endl;
    }
    if (!chansInp.empty()) {
        os << "// observable input channels (controlled by Env):\n"
            "  node [shape=diamond,peripheries=2," ENVSTYLE "];\n  ";
        for_each(chansInp.begin(), chansInp.end(), 
                 surround(os, "\"", "\"; "));
//        copy(chansInp.begin(), chansInp.end(), osi);
        set_remove(chansR, chansInp);
        os << endl;
    }

    if (!procsEnv.empty()) {
        os << "// Env processes:\n";
        os << "  node [shape=ellipse,peripheries=1," ENVSTYLE "];\n  ";
        for (p = procsEnv.begin(), pe = procsEnv.end(); p!=pe; ++p) {
            os << (*p)->name << "; ";
            procsR.erase((*p)->name);
        }
        os << endl;
    }
    if (!chansIntEnv.empty()) {
        os << "// Env channels:\n";
        os << "  node [shape=diamond,peripheries=1," ENVSTYLE "];\n  ";
        for_each(chansIntEnv.begin(), chansIntEnv.end(), 
                 surround(os, "\"", "\"; "));
//        copy(chansIntEnv.begin(), chansIntEnv.end(), osi);
        set_remove(chansR, chansIntEnv);
        os << endl;
    }
    if (!varsEnv.empty()) {
        os << "// Env variables:\n";
        os << "  node [shape=rectangle,peripheries=1," ENVSTYLE "];\n  ";
        copy(varsEnv.begin(), varsEnv.end(), osi);
        set_remove(varsR, varsEnv);
        os << endl;
    }
    os << "// set attributes for non-partitioned procs/chans/vars:\n";
    if (!procsR.empty()) {
        os << "  node [shape=ellipse,peripheries=1," MEDSTYLE "];\n";
        copy(procsR.begin(), procsR.end(), osi);
        os << endl;
    }
    if (!chansR.empty()) {
        os << "  node [shape=diamond,peripheries=1," MEDSTYLE "];\n";
        for_each(chansR.begin(), chansR.end(), 
                 surround(os, "\"", "\"; "));
//        copy(chansR.begin(), chansR.end(), osi);
        os << endl;
    }
    if (!varsR.empty()) {
        os << "  node [shape=rectangle,peripheries=1," MEDSTYLE "];\n";
        copy(varsR.begin(), varsR.end(), osi);
        os << endl;
    }


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
                    os << "  " << (*p)->name << " -> \"" << *c << "\";\n";
                }
            }
            os << "// channel receive edges:\n"
               << "  edge [style=solid];\n";
            for (p = procs.begin(), pe = procs.end(); p!=pe; ++p) {
                for (strs_t::const_iterator c=(*p)->inChans.begin(),
                         ce=(*p)->inChans.end(); c!=ce; ++c)
                {
                    os << "  \"" << *c << "\" -> " << (*p)->name << ";\n";
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
            bool noDst = false;
            os<<"  edge[style=solid];\n";
            for (p = procs.begin(), pe = procs.end(); p!=pe; ++p)
            {
                /* display outgoing edges: */
                for (proc2strs_t::const_iterator edge = (*p)->outEdges.begin();
                     edge != (*p)->outEdges.end(); ++edge)
                {
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
                        os<< "\"" << *ch << "\"";
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
                    str2procs_t::const_iterator trans = transmitters.find(*c);
                    if (trans==transmitters.end())
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


void DistanceCalculator::addVariableNeedle(const char* var) 
{
    /* FIXME: find global variable if the variable is local process parameter*/
    distancesUpToDate = false;
    const char* dot = strchr(var, '.');
    size_t length = dot == NULL ? strlen(var) : dot - var;
    char* name = strncpy(new char[length+1], var, length);
    name[length] = '\0';

    if (variables.find(name)==variables.end()) {
        cerr << "Variable not found: " << var << endl;
        delete [] name;
        return;
    }
    dist_t* distance = NULL;
    str2dist_t::iterator i = distances.find(name);
    if (i==distances.end()) {
        varNeedles.insert(name);
        distances[name] = dist_t(0, 1, 0);
        //distance = &distances[name]; // FIXME: work-in-progress.
    } else {
        distance = &(i->second);
        if (distance->hops==0 && distance->distance==0) {
            /* double the complexity if mentioned several times */
            distance->complexity = 2 * distance->complexity;
        } else {
            distance->hops = 0;
            distance->distance = 0;
        }
        delete [] name; // appearently a copy is in varNeedles
    }
}

void DistanceCalculator::addProcessNeedle(const char* proc)
{
    distancesUpToDate = false;
    const char* dot = strchr(proc, '.');
    size_t length = dot == NULL ? strlen(proc) : dot - proc;
    char* name = strncpy(new char[length+1], proc, length);
    name[length] = '\0';

    if (processes.find(name)==processes.end()) {
        cerr << "AddNeedle: Process not found: " << proc << endl;
        delete [] name;
        return;
    }

    dist_t* distance = NULL;
    str2dist_t::iterator i = distances.find(name);
    if (i==distances.end()) {
        procNeedles.insert(name);
        distances[name] = dist_t(0, calcComplexity(name), 0);
        //distance = &distances[name]; // FIXME: work-in-progress.
    } else {
        distance = &(i->second);
        if (distance->hops==0 && distance->distance==0) {
            /* double the complexity if mentioned several times */
            distance->complexity = 2 * distance->complexity;
        } else {
            distance->hops = 0;
            distance->distance = 0;
        }
        delete [] name; // appearently a copy is in procNeedles
    }
}

void DistanceCalculator::updateDistancesFromVariable(const char* name, 
                                                     const dist_t* d)
{
    // find all processes that transmit/write on this variable:
    str2procs_t::const_iterator t = transmitters.find(name);
    if (t == transmitters.end()) return;
    for (procs_t::const_iterator p=t->second.begin(),e=t->second.end(); 
         p!=e; ++p)
    {
        dist_t* distance = NULL;
        str2dist_t::iterator i = distances.find((*p)->name);
        if (i==distances.end()) {
            procNeedles.insert(strcpy(new char[strlen((*p)->name)+1], 
                                      (*p)->name));
            distances[(*p)->name] = dist_t(d->hops+1, 
                                           calcComplexity((*p)->name), 
                                           d->distance + d->complexity);
            distance = &distances[(*p)->name];
        } else {
            distance = &(i->second);
            if (distance->distance <= d->distance + d->complexity)
                continue; // old distance is shorter, no changes to propagate
            else {
                distance->hops = d->hops+1;
                distance->distance = d->distance + d->complexity;
            }
        }        
        updateDistancesFromProcess((*p)->name, distance);
    }
}

void DistanceCalculator::updateDistancesFromProcess(const char* name, 
                                                    const dist_t* d)
{
    /* find the process structure representing this process */
    procs_t::const_iterator s = procs.begin();
    while (s != procs.end()) 
        if (strcmp((*s)->name, name)==0) break;
        else ++s;
    if (s == procs.end()) {
        cerr << "UpdateDistancesFromProcess: Process not found: "<<name<<endl;
        return;
    }
    /* for each channel the process listens to: */
    for (strs_t::const_iterator c=(*s)->inChans.begin(),ce=(*s)->inChans.end();
         c!=ce; ++c) { 
        /* find all processes that send on this channel: */
        str2procs_t::const_iterator t = transmitters.find(*c);
        if (t == transmitters.end()) continue;
        /* update the distances for each transmitting process */
        for (procs_t::const_iterator p=t->second.begin(),e=t->second.end(); 
             p!=e; ++p)
        {
            dist_t* distance = NULL;
            str2dist_t::iterator i = distances.find((*p)->name);
            if (i==distances.end()) {
                procNeedles.insert(strcpy(new char[strlen((*p)->name)+1], 
                                          (*p)->name));
                distances[(*p)->name] = dist_t(d->hops+1, 
                                               calcComplexity((*p)->name), 
                                               d->distance + d->complexity);
                distance = &distances[(*p)->name];
            } else {
                distance = &(i->second);
                if (distance->distance <= d->distance + d->complexity)
                    continue; // old distance is shorter no changes to propagate
                else {
                    distance->hops = d->hops+1;
                    distance->distance = d->distance + d->complexity;
                }
            }        
            updateDistancesFromProcess((*p)->name, distance);
        }        
    }
    /* for each variable the process reads from: */
    for (str2strs_t::const_iterator v=(*s)->rdVars.begin(),
             ve=(*s)->rdVars.end(); v!=ve; ++v)
    {
        dist_t* distance = NULL;
        str2dist_t::iterator i = distances.find(v->first);
        if (i==distances.end()) {
            varNeedles.insert(strcpy(new char[strlen(v->first)+1], v->first));
            distances[v->first] = dist_t(d->hops+1, 1, 
                                         d->distance + d->complexity);
            distance = &distances[v->first];
        } else {
            distance = &(i->second);
            if (distance->distance <= d->distance + d->complexity)
               continue; // old distance is shorter, no changes to propagate
            else {
                distance->hops = d->hops+1;
                distance->distance = d->distance + d->complexity;
            }
        }        
        updateDistancesFromVariable(v->first, distance);        
    }
}

int DistanceCalculator::calcComplexity(const char* process)
{
    int result = 0;
    list<instance_t> &ps(taSystem.getProcesses());
    for (list<instance_t>::iterator i=ps.begin(), e=ps.end(); i!=e; ++i)
    {
        if (i->uid.getName()==process) {   
            const template_t* temp = i->templ;
            deque<edge_t>::const_iterator t = i->templ->edges.begin();
            while (t != temp->edges.end()) { result++; t++; }
        }
    }
    return result;
}

void DistanceCalculator::printProcsForDot(std::ostream &os, bool erd)
{
/* Enumerate processes with common look-attributes */
    os << "  subgraph procs {\n";
    if (erd)
    {
        os<<"    node [shape=rectangle,style=filled];\n";
    }
    else
    {
        os<<"    node [shape=ellipse,style=filled];\n";
    }
    os << "    ";
    
    for (procs_t::const_iterator p=procs.begin(), e=procs.end(); p!=e; ++p)
    {
        str2dist_t::const_iterator d = distances.find((*p)->name);
        if (d==distances.end()) {
            os << (*p)->name << "[label=\"\\N\\n(( ?, ?))\"]; ";
        } else {
            os << (*p)->name << "[label=\"\\N\\n((" << d->second.hops 
               <<", "<< d->second.distance <<"))\"]; ";
        }
    }
    os << "\n  }\n";
}

void DistanceCalculator::printVarsForDot(std::ostream &os, bool ranked, 
                                         bool erd)
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
        os << "    node [shape=rectangle,color=blue];\n    ";
    }
    for (strs_t::const_iterator i=variables.begin(), e=variables.end(); 
         i!=e; ++i)
    {
        str2dist_t::const_iterator d = distances.find(*i);
        if (d==distances.end()) {
            os << *i << "[label=\"\\N\\n(( ?, ?))\"";
        } else {
            os << *i << "[label=\"\\N\\n((" << d->second.hops 
               <<", "<< d->second.distance <<"))\"";
        }
        if (transmitters.find(*i) == transmitters.end()) os << "]; "; // const
        else os << ",style=bold]; "; // others bold
    }
    os << "\n  }\n";
}

DistanceCalculator::~DistanceCalculator()
{
    for(strs_t::iterator i=varNeedles.begin(),e=varNeedles.end(); i!=e; ++i)
        delete [] (*i);
    varNeedles.clear();

    for(strs_t::iterator i=procNeedles.begin(),e=procNeedles.end(); i!=e; ++i)
        delete [] (*i);
    procNeedles.clear();
}

uint32_t DistanceCalculator::getDistance(const char* element)
{
    if (!distancesUpToDate) updateDistances();

    str2dist_t::iterator f = distances.find(element);
    if (f == distances.end()) {
        //cerr << "GetDistance: Process not found: " << element << endl;
        return INT_MAX;
    }
    return f->second.distance;
}

void DistanceCalculator::printForDot(ostream &os, bool ranked, bool erd, 
                                     bool cEdged)
{
    if (!distancesUpToDate) updateDistances();

    SignalFlow::printForDot(os, ranked, erd, cEdged);
}

void DistanceCalculator::updateDistances()
{
    /* cleanup the old stuff: put all distances at infinity=INT_MAX: */
    for (str2dist_t::iterator i=distances.begin(), e=distances.end(); 
         i!=e; ++i)
    {
        if (i->second.hops>0) {
            i->second.hops = INT_MAX;
            i->second.distance = INT_MAX;
        }
    }
    /* calculate distances from variable needles: */
    for(strs_t::iterator i=varNeedles.begin(),e=varNeedles.end(); 
        i!=e; ++i) 
    {
        str2dist_t::iterator f = distances.find(*i);
        if (f == distances.end()) {
            cerr << "Variable not found: " << *i << endl;
            exit(EXIT_FAILURE);
        }
        updateDistancesFromVariable(*i, &(f->second));
    }
    /* calculate distances from process needles: */
    for(strs_t::iterator i=procNeedles.begin(),e=procNeedles.end(); 
        i!=e; ++i)
    {
        str2dist_t::iterator f = distances.find(*i);
        if (f == distances.end()) {
            cerr << "Process not found: " << *i << endl;
            exit(EXIT_FAILURE);
        }
        updateDistancesFromProcess(*i, &(f->second));
    }
    distancesUpToDate = true;
}

