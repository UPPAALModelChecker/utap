// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2020 Aalborg University.
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

#include <iomanip>  // std::quoted
#include <iostream>
#include <iterator>  // ostream_iterator
#include <string>
#include <cassert>

using std::cerr;
using std::endl;
using UTAP::DistanceCalculator;
using UTAP::SignalFlow;
using UTAP::Partitioner;
using UTAP::Document;
using namespace UTAP::Constants;

SignalFlow::SignalFlow(const std::string& title, Document& doc): title{title}
{
    /*
     * Visit all processes in the document.
     * FIXME: it does not take care of autocompleted parameters,
     *        unfolding is intricate and is done outside UTAP.
     */
    for (auto& proc : doc.getProcesses())
        visitProcess(proc);
}

void SignalFlow::printForTron(std::ostream& os)
{
    for (const auto* p : procs) {
        os << p->name << ":\n  ";                       // automaton:
        os << infix_print{p->inChans, " "} << ",\n  ";  // input channels,
        os << infix_print{p->outChans, " "} << ",\n ";  // output channels,

        for (const auto& v : p->rdVars)  // input variables(channels),
            os << " " << v.first << "(" << infix_print{v.second, " "} << ")";
        os << ",\n ";
        for (const auto& v : p->wtVars)  // output variables(channels);
            os << " " << v.first << "(" << infix_print{v.second, " "} << ")";
        os << "\n;\n";
    }
}

void SignalFlow::printProcsForDot(std::ostream& os, bool erd)
{
    /* Enumerate processes with common look-attributes */
    os << "  subgraph procs {\n";
    if (erd)
        os << "    node [shape=rectangle,style=filled];\n";
    else
        os << "    node [shape=ellipse,style=filled];\n";
    os << "    ";

    for (const auto* p : procs)
        os << p->name << "; ";
    os << "\n  }\n";
}

void SignalFlow::printVarsForDot(std::ostream& os, bool ranked, bool erd)
{
    // draw variables
    /* specify attributes for all nodes */
    os << "  subgraph cluste_vars {\n";
    os << "    style=invis;\n";
    if (ranked)
        os << "    rank=min;\n";
    if (erd)
        os << "    node [shape=diamond,color=blue];\n    ";
    else
        os << "    node [shape=rectangle,color=blue];\n    ";
    for (const auto& i : variables) {
        if (transmitters.find(i) == transmitters.end())
            os << i << "; ";  // const variables are slim
        else
            os << i << "[style=bold]; ";  // others bold
    }
    os << "\n  }\n";
}

void SignalFlow::printVarsWriteForDot(std::ostream& os)
{
    /* 'variable write' edges are bold */
    os << "  edge [style=bold,color=blue,fontcolor=blue,weight=100];\n";
    /* draw variable write edges */
    for (const auto& a : procs) {
        if (!a->wtVars.empty()) {
            for (const auto& v : a->wtVars) {
                os << "  " << a->name << " -> " << v.first << " [label=\"(";
                /* enumerate channels when variable is accessed */
                os << infix_print{v.second, ","} << ")\"];\n";
            }
        }
    }
}

void SignalFlow::printVarsReadForDot(std::ostream& os)
{
    /* 'variable read' edges are slim  */
    os << "  edge [style=solid,color=blue,fontcolor=blue,weight=1];\n";
    /* draw variable edges */
    for (const auto* a : procs) {
        if (!a->rdVars.empty()) {
            for (const auto& v : a->rdVars) {
                os << "  " << v.first << " -> " << a->name << " [label=\"(";
                /* enumerate channels when variable is accessed */
                os << infix_print{v.second, ","} << ")\"];\n";
            }
        }
    }
}

void SignalFlow::printChansOnEdgesForDot(std::ostream& os)
{
    /* channels appear only on I/O edges */
    const char* src = "NO_SRC";
    const char* dst = "NO_DST";
    /* build an index of outgoing edges sorted by destination TA */
    for (auto* a : procs) {
        /* traverse all outgoing channels */
        for (auto& i : a->outChans) {
            auto dests = receivers.find(i);
            if (dests != receivers.end()) {  // there are destinations
                for (auto* rec : dests->second)
                    a->outEdges[rec].insert(i);
            } else {  // no destination
                a->outEdges[nullptr].insert(i);
            }
        }
    }
    bool noDst = false;
    /* display all edges: */
    os << "  edge[style=solid,color=black,fontcolor=black,weight=50];\n";
    for (const auto* a : procs) {
        /* display outgoing edges: */
        for (const auto& edge : a->outEdges) {
            // display edge:
            if (edge.first != nullptr) {
                // normal destination TA
                os << "  " << a->name << " -> " << edge.first->name << " [label=\"[";
            } else {  // there was no destination TA
                if (!noDst) {
                    os << "  " << dst << " [style=filled,fillcolor=red];\n";
                    noDst = true;
                }
                os << "  " << a->name << " -> " << dst << " [label=\"[";
            }
            // enumerate all channels on the edge:
            os << infix_print{edge.second, ","} << "]\"];\n";
        }
        /* by now all inps with sources are displayed as outputs
         * search and display inputs w/o sources */
        bool noSrc = false;
        for (const auto& i : a->inChans) {
            auto trans = transmitters.find(i);
            if (trans == transmitters.end()) {
                if (!noSrc) {
                    os << "  " << src << " [style=filled,fillcolor=red];\n";
                    noSrc = true;
                }
                os << "  " << src << " -> " << a->name << " [label=\"" << i << "\"];\n";
            }
        }
    }
}

void SignalFlow::printChansSeparateForDot(std::ostream& os, bool ranked, bool erd)
{
    /* channels displayed as separate nodes (like variables) */
    os << "  subgraph cluste_chans {\n";
    os << "    style=invis;\n";
    if (ranked)
        os << "    rank=max;\n";
    os << "    node [shape=diamond,color=red];\n    ";
    os << infix_print{channels, "; "} << "\n  }\n";
    for (const auto* a : procs) {
        for (const auto& i : a->inChans)
            os << "  " << i << " -> " << a->name << ";\n";
        for (const auto& i : a->outChans)
            os << "  " << a->name << " -> " << i << " [style=bold];\n";
    }
}

void SignalFlow::printForDot(std::ostream& os, bool ranked, bool erd, bool cEdge)
{
    std::string name = title;
    for (auto& c : name)
        if (!std::isalpha(c))
            c = '_';

    os << "digraph " << name << " {\n";
    os << "  model=subset; remincross=true;\n";
    // os << "  edge [decorate];\n"; // use 'dot -Edecorate' if you wish

    if (!procs.empty())
        printProcsForDot(os, erd);

    /* Enumerate variables, with common look-attributes */
    if (!variables.empty()) {
        printVarsForDot(os, ranked, erd);
        printVarsWriteForDot(os);
        printVarsReadForDot(os);
    }

    /* enumerate draw channels */
    if (!channels.empty()) {
        if (cEdge)
            printChansOnEdgesForDot(os);
        else
            printChansSeparateForDot(os, ranked, erd);
    }
    os << "}" << endl;
}

bool SignalFlow::checkParams(const symbol_t& s)
{
    if (!paramsExpanded) {
        if (0 <= cP->templ->parameters.getIndexOf(s.getName())) {
            // is it parameter? find the corresponding global symbol(s)
            auto e = cP->mapping.find(s);
            if (e != cP->mapping.end()) {
                paramsExpanded = true;
                visitExpression(e->second);
                paramsExpanded = false;
            } else {
                cerr << "mapping param '" << s.getName() << "' failed" << endl;
                exit(EXIT_FAILURE);
            }
            return false;
        } else if (0 <= cP->templ->frame.getIndexOf(s.getName())) {
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

void SignalFlow::addChan(const std::string& s, strset_t& ids, str2procset_t& index)
{
    std::string s2;
    auto it = channels.find(s.c_str());
    if (it == channels.end()) {
        s2 = s;
        channels.insert(s2);
    } else
        s2 = *it;
    ids.insert(s2);
    index[s2].insert(cTA);
    cChan = s2;
}

void SignalFlow::addVar(const symbol_t& s, str2strset_t& ids, str2procset_t& index)
{
    if (checkParams(s)) {
        ids[s.getName()].insert(cChan);
        variables.insert(s.getName());
        index[s.getName()].insert(cTA);
    }
}

static const char* noChan = "-";

void SignalFlow::visitProcess(instance_t& p)
{
    cP = &p;
    procs.insert(cTA = new proc_t(p.uid.getName().c_str()));
    processes.insert(p.uid.getName().c_str());

    for (const auto& s : p.templ->states) {
        cChan = noChan;  // invariants should not use shared
        visitExpression(s.invariant);
    }
    for (const auto& t : p.templ->edges) {
        cChan = noChan;  // guards should not use shared
        visitExpression(t.guard);
        visitExpression(t.sync);
        visitExpression(t.assign);
    }
}

void SignalFlow::visitExpression(const expression_t& e)
{
    if (e.empty()) {
        return;
    }

    switch (e.getKind()) {
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
        for (uint32_t i = 0; i < e.getSize(); ++i) {
            inp = true;
            out = false;
            visitExpression(e[i]);
        }
        break;
    case FORALL:
    case EXISTS:
    case SUM:
        // the first expression is an inline (local) declaration (don't care)
        // the second is side-effect-free, hence read-only expression
        assert(e.getSize() == 2);
        inp = true;
        out = false;
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
        inp = false;
        out = true;
        visitExpression(e[0]);
        for (uint32_t i = 1; i < e.getSize(); ++i) {
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
        if (sync) {  // channel synchronization
            if (checkParams(e.getSymbol())) {
                chanString.append(e.getSymbol().getName());
            }
        } else {                                      // variable access
            if (e.getType().getKind() == CONSTANT) {  // constant
                assert(!out);
                break;
            }
            symbol_t sym = e.getSymbol();
            if (sym.getFrame().hasParent()) {  // local variable
                if (refparams.size() == 0)
                    break;  // local process variable
                // else: local function variable
                exprref_t::const_iterator exi = refparams.top().find(sym);
                if (exi != refparams.top().end()) {  // passed by reference
                    visitExpression(exi->second);
                    break;
                }
                exi = valparams.top().find(sym);
                if (exi != valparams.top().end()) {  // passed by value
                    if (inp) {
                        pushIO();
                        out = false;  // any writes to local copy are lost
                        visitExpression(exi->second);
                        popIO();
                    }
                    break;
                }
                // else: local function variable but not parameter, don't care
            } else {  // global variable
                if (inp)
                    addVar(sym, cTA->rdVars, receivers);
                if (out)
                    addVar(sym, cTA->wtVars, transmitters);
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
        if (sync)
            chanString.append("[");
        pushIO();
        for (uint32_t i = 1; i < e.getSize(); ++i) {
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
        for (uint32_t i = 0; i < e.getSize(); ++i) {
            inp = true;
            out = false;
            visitExpression(e[i]);
        }
        break;
    case DOT:  // dot expression has only one subexpression?
        for (uint32_t i = 0; i < e.getSize(); ++i)
            visitExpression(e[i]);
        break;
    case INLINEIF:
        pushIO();
        inp = true;
        out = false;
        visitExpression(e[0]);
        for (uint32_t i = 1; i < e.getSize(); ++i) {
            popIO();
            pushIO();
            visitExpression(e[i]);
        }
        popIO();
        break;
    case COMMA:
        pushIO();
        for (uint32_t i = 0; i < e.getSize() - 1; ++i) {
            inp = true;
            out = false;
            visitExpression(e[i]);
        }
        popIO();
        visitExpression(e[e.getSize() - 1]);
        break;
    case SYNC:
        switch (e.getSync()) {
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
    case EFUNCALL:
    case FUNCALL: {                             // create a map of parameter symbol to argument expression
        const symbol_t& fnsym = e.getSymbol();  // function symbol
        assert(fnsym.getType().getKind() == FUNCTION || fnsym.getType().isExternalFunction());
        const function_t* fn = static_cast<const function_t*>(fnsym.getData());
        BlockStatement* body = fn->body.get();
        const frame_t& frame = body->getFrame();
        refparams.push(exprref_t());
        valparams.push(exprref_t());
        for (size_t i = 0; i < e.getSize() - 1; ++i) {
            symbol_t param = frame[i];
            const type_t& ptype = param.getType();
            if (ptype.is(REF))
                refparams.top()[param] = e[i + 1];
            else
                valparams.top()[param] = e[i + 1];
        }
        if (e.getKind() != EFUNCALL)
            body->accept(this);  // see which parameters are touched
        refparams.pop();
        valparams.pop();
    } break;

    default:
        cerr << "unsupported kind (" << e.getKind() << ") of expression, please report it to developers." << endl;
        exit(1);
    }
}

int32_t SignalFlow::visitEmptyStatement(EmptyStatement* stat) { return 0; }

int32_t SignalFlow::visitExprStatement(ExprStatement* stat)
{
    visitExpression(stat->expr);
    return 0;
}

int32_t SignalFlow::visitIterationStatement(IterationStatement* stat)
{
    // FixMe: there is mysterious field called symbol, do smth about it.
    return stat->stat->accept(this);
}

int32_t SignalFlow::visitForStatement(ForStatement* stat)
{
    visitExpression(stat->init);
    visitExpression(stat->cond);
    visitExpression(stat->step);
    return stat->stat->accept(this);
}

int32_t SignalFlow::visitWhileStatement(WhileStatement* stat)
{
    visitExpression(stat->cond);
    return stat->stat->accept(this);
}

int32_t SignalFlow::visitDoWhileStatement(DoWhileStatement* stat)
{
    int32_t res = stat->stat->accept(this);
    visitExpression(stat->cond);
    return res;
}

int32_t SignalFlow::visitBlockStatement(BlockStatement* stat)
{
    int32_t res = 0;
    BlockStatement::iterator it = stat->begin();
    while (it != stat->end()) {
        res = (*it)->accept(this);
        ++it;
    }
    return res;
}

int32_t SignalFlow::visitSwitchStatement(SwitchStatement* stat)
{
    visitExpression(stat->cond);
    return visitBlockStatement(stat);
}

int32_t SignalFlow::visitCaseStatement(CaseStatement* stat)
{
    visitExpression(stat->cond);
    return visitBlockStatement(stat);
}

int32_t SignalFlow::visitDefaultStatement(DefaultStatement* stat) { return visitBlockStatement(stat); }

int32_t SignalFlow::visitIfStatement(IfStatement* stat)
{
    visitExpression(stat->cond);
    int32_t res = stat->trueCase->accept(this);
    if (stat->falseCase) {
        return stat->falseCase->accept(this);
    } else
        return res;
}
int32_t SignalFlow::visitBreakStatement(BreakStatement* stat) { return 0; }

int32_t SignalFlow::visitContinueStatement(ContinueStatement* stat) { return 0; }

int32_t SignalFlow::visitAssertStatement(UTAP::AssertStatement* stat) { return 0; }

int32_t SignalFlow::visitReturnStatement(ReturnStatement* stat)
{
    visitExpression(stat->value);
    return 0;
}

SignalFlow::~SignalFlow()
{
    for (auto* p : procs)
        delete p;
}

inline void Partitioner::printViolation(const proc_t* proc, const std::string& var)
{
    if (verbosity >= 1)
        cerr << "Violated rule \"" << rule << "\" for process \"" << proc->name << "\" accessing \"" << var << "\""
             << endl;
}

/**
 * Adds processes to the result which use the channels from chans list
 * according to index. Reports inconsistency if some process happens to be
 * in exclude list.
 */
void Partitioner::addProcs(const strset_t& chans, const str2procset_t& index, procset_t& result, procset_t& exclude)
{
    for (const auto& c : chans) {  // take each channel from the given set
        auto c2p = index.find(c);  // find processes that use the channel
        if (c2p != index.end()) {
            for (auto* p : c2p->second) {
                if (exclude.erase(p) > 0) {  // if process was excluded
                    procsBad.insert(p);      // report as inconsistent process
                    printViolation(p, c);
                } else if (result.find(p) == result.end() && procsBad.find(p) == procsBad.end()) {
                    // if process has not been added nor excluded, then add it:
                    if (verbosity >= 3)
                        cerr << "Adding \"" << p->name << "\" using \"" << c << "\" by rule \"" << rule << "\"" << endl;
                    result.insert(p);
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
void Partitioner::addIntChans(const procset_t& procs, strset_t& result, strset_t& exclude)
{
    for (const auto* p : procs) {                          // take each process from the list
        for (const auto& c : p->inChans) {                 // consider the input channels used by the process
            if (observable.find(c) == observable.end()) {  // if not observed
                if (exclude.erase(c) > 0) {                // if it's excluded
                    chansBad.insert(c);                    // report inconsistency
                    printViolation(p, c);
                } else if (result.find(c) == result.end() && chansBad.find(c) == chansBad.end()) {
                    if (verbosity >= 3)
                        cerr << "Adding \"" << c << "\" because of \"" << p->name << "\" by rule \"" << rule << "\""
                             << endl;
                    result.insert(c);
                }
            }
        }
        for (const auto& c : p->outChans) {                // conside the output channels used by p
            if (observable.find(c) == observable.end()) {  // if not observed
                if (exclude.erase(c) > 0) {                // if it's excluded
                    chansBad.insert(c);                    // report inconsistency
                    printViolation(p, c);
                } else if (result.find(c) == result.end() && chansBad.find(c) == chansBad.end()) {
                    if (verbosity >= 3)
                        cerr << "Adding \"" << c << "\" because of \"" << p->name << "\" by rule \"" << rule << "\""
                             << endl;
                    result.insert(c);
                }
            }
        }
    }
}

/**
 * Takes the variables of each process from procs list and adds them to
 * the result list. Reports inconcistency if variable is in the exclude list.
 */
void Partitioner::addIntVars(const procset_t& procs, strset_t& result, strset_t& exclude)
{
    for (const auto* p : procs) {  // take each process p
        assert(p);
        for (const auto& v2c : p->rdVars) {  // consider the variables being read
            if (!includes(observable.begin(), observable.end(), v2c.second.begin(),
                          v2c.second.end())) {  // contains non-observable channels
                if (exclude.erase(v2c.first) > 0) {
                    varsBad.insert(v2c.first);
                    printViolation(p, v2c.first);
                } else if (result.find(v2c.first) == result.end() && varsBad.find(v2c.first) == varsBad.end()) {
                    if (verbosity >= 3)
                        cerr << "Adding \"" << v2c.first << "\" because of \"" << p->name << "\" by rule \"" << rule
                             << "\"" << endl;
                    result.insert(v2c.first);
                }
            }  // else used only observably
        }
        for (const auto& v2c : p->wtVars) {  // consider the variables being written to by p
            if (!includes(observable.begin(), observable.end(), v2c.second.begin(),
                          v2c.second.end())) {  // contains non-observable channels
                if (exclude.erase(v2c.first) > 0) {
                    varsBad.insert(v2c.first);
                    printViolation(p, v2c.first);
                } else if (result.find(v2c.first) == result.end() && varsBad.find(v2c.first) == varsBad.end()) {
                    if (verbosity >= 3)
                        cerr << "Adding \"" << v2c.first << "\" because of \"" << p->name << "\" by rule \"" << rule
                             << "\"" << endl;
                    result.insert(v2c.first);
                }
            }  // else used only observably
        }
    }
}

/**
 * Take all variables and add all accessing processes to the list.
 * Report inconcistencies if process happens to be in exclude list.
 */
void Partitioner::addProcsByVars(const strset_t& vars, procset_t& procs, procset_t& exclude)
{
    for (const auto& v : vars) {       // take every variable v from the vars list
        auto v2p = receivers.find(v);  // find list of processes that read from v
        if (v2p != receivers.end()) {
            for (auto* p : v2p->second) {  // take each process reading the value of v
                auto v2c = p->rdVars.find(v);
                if (v2c != p->rdVars.end()) {
                    if (!includes(observable.begin(), observable.end(), v2c->second.begin(),
                                  v2c->second.end())) {  // has unobservable synchronizations
                        if (exclude.erase(p) > 0) {
                            procsBad.insert(p);
                            printViolation(p, v);
                        } else if (procs.find(p) == procs.end() && procsBad.find(p) == procsBad.end()) {
                            if (verbosity >= 3)
                                cerr << "Adding \"" << p->name << "\" using \"" << v << "\" by rule \"" << rule << "\""
                                     << endl;
                            procs.insert(p);
                        }
                    }  // else used observably
                } else {
                    if (verbosity >= 1)
                        cerr << "addProcsByVars could not find in rdVars" << endl;
                }
            }
        } else {
            if (verbosity >= 1)
                cerr << "addProcsByVars could not find readers" << endl;
        }
        v2p = transmitters.find(v);
        if (v2p != transmitters.end()) {
            for (auto* p : v2p->second) {  // consider the process p which writes to v
                auto v2c = p->wtVars.find(v);
                if (v2c != p->wtVars.end()) {
                    if (!includes(observable.begin(), observable.end(), v2c->second.begin(),
                                  v2c->second.end())) {  // has unobservable synchronizations
                        if (exclude.erase(p) > 0) {
                            procsBad.insert(p);
                            printViolation(p, v);
                        } else if (procs.find(p) == procs.end() && procsBad.find(p) == procsBad.end()) {
                            if (verbosity >= 3)
                                cerr << "Adding \"" << p->name << "\" using \"" << v << "\" by rule \"" << rule << "\""
                                     << endl;
                            procs.insert(p);
                        }
                    }  // else used observably
                } else {
                    if (verbosity >= 1)
                        cerr << "addProcsByVars could not find in wtVars" << endl;
                }
            }
        } else {
            if (verbosity >= 1)
                cerr << "addProcsByVars could not find writers for " << v << endl;
        }
    }
}

static std::istream& get_token(std::istream& in, std::string& token)
{
    token.clear();
    char c;
    while (in.get(c)) {
        if (isalnum((unsigned char)c) || c == '_' || c == '[' || c == ']')
            token += c;
        else {
            if (c == '(')
                while (in.get(c) && c != ')')
                    ;  // ignore "(...)"
            if (token.length() > 0)
                return in;
        }
    }
    return in;
}

int Partitioner::partition(std::istream& ioinfo)
{
    std::string token;
    strset_t inputs, outputs;
    std::ios::fmtflags flags = ioinfo.flags();
    ioinfo.unsetf(std::ios::skipws);
    if (get_token(ioinfo, token) && token.empty()) {
        if (token != "input") {
            cerr << "\"input\" is expected instead of \"" << token << "\"" << endl;
            exit(EXIT_FAILURE);
        }
        while (get_token(ioinfo, token) && !token.empty() && token != "output")
            inputs.insert(token);
        if (token.empty()) {
            cerr << "\"output\" expected, but EOF found" << endl;
            exit(EXIT_FAILURE);
        }
        while (get_token(ioinfo, token) && !token.empty() && token != "precision" && token != "timeout")
            outputs.insert(token);
    }
    ioinfo.flags(flags);
    return partition(inputs, outputs);
}

int Partitioner::partition(const strset_t& inputs, const strset_t& outputs)
{
    procsEnv.clear();
    procsIUT.clear();
    chansIntEnv.clear();
    chansIntIUT.clear();
    varsEnv.clear();
    varsIUT.clear();
    chansInp.clear();
    chansOut.clear();

    chansInp.insert(inputs.begin(), inputs.end());
    chansOut.insert(outputs.begin(), outputs.end());

    observable.clear();
    observable.insert(chansInp.begin(), chansInp.end());
    observable.insert(chansOut.begin(), chansOut.end());

    if (verbosity >= 3) {
        cerr << "Inputs:  " << infix_print{chansInp, ","} << endl;
        cerr << "Outputs: " << infix_print{chansOut, ","} << endl;
    }

    size_t oldProgress = 0, progress = 0;
    do {
        oldProgress = progress;
        /* Environment processes shout on inputs and listens to outputs, while IUT
         * processes shout on outputs and listen to inputs. */
        rule = "transmitters on input channels belong to Env";
        addProcs(inputs, transmitters, procsEnv, procsIUT);
        rule = "receivers on output channels belong to Env";
        addProcs(outputs, receivers, procsEnv, procsIUT);
        rule = "receivers on input channels belong IUT";
        addProcs(inputs, receivers, procsIUT, procsEnv);
        rule = "transmitters on output channels belong IUT";
        addProcs(outputs, transmitters, procsIUT, procsEnv);

        /* 1) channels, that are not declared as inputs/outputs, are non-observable,
         *    called internal.*/

        /* 2) internal channel belongs to environment (IUT) if it is used by
         *    environment (IUT) process (respectively). Model is inconsistent and
         *    cannot be partitioned if the internal channel is used by both environment
         *    and IUT. */
        rule = "internal channel belongs to Env if it is used by Env";
        addIntChans(procsEnv, chansIntEnv, chansIntIUT);
        rule = "internal channel belongs to IUT if it is used by IUT";
        addIntChans(procsIUT, chansIntIUT, chansIntEnv);

        /* 3) process belongs to environment (IUT) if it uses the internal environment
         *    (IUT) channel (respectively). */
        rule = "process belongs to Env if it shouts on internal Env channel";
        addProcs(chansIntEnv, transmitters, procsEnv, procsIUT);
        rule = "process belongs to Env if it listens to internal Env channel";
        addProcs(chansIntEnv, receivers, procsEnv, procsIUT);
        rule = "process belongs to IUT if it shouts on internal IUT channel";
        addProcs(chansIntIUT, transmitters, procsIUT, procsEnv);
        rule = "process belongs to IUT if it listens to internal IUT channel";
        addProcs(chansIntIUT, receivers, procsIUT, procsEnv);

        /* 4) variable belongs to environment (IUT) if it is accessed by environment
         *    (IUT) process without observable input/output channel synchronization.
         *    Variable is not cathegorized (can be either) if accessed consistently
         *    only during observable input/output channel synchronization. */
        rule = "variable belongs to Env if accessed by Env without observable sync";
        addIntVars(procsEnv, varsEnv, varsIUT);
        rule = "variable belongs to IUT if accessed by IUT without observable sync";
        addIntVars(procsIUT, varsIUT, varsEnv);

        /* 5) process belongs to environment (IUT) if it accesses environment (IUT)
         *    variable (respectively) without observable channel synchronization. */
        rule = "process belongs to Env if it access Env variable without observable synchronization";
        addProcsByVars(varsEnv, procsEnv, procsIUT);
        rule = "process belongs to IUT if it access IUT variable without observable synchronization";
        addProcsByVars(varsIUT, procsIUT, procsEnv);
        progress = procsEnv.size() + procsIUT.size() + procsBad.size();
    } while (progress > oldProgress);

    if (verbosity >= 3) {
        cerr << "==== Partitioned =========================================\n";
        cerr << "Env procs: " << procsEnv << endl;
        cerr << "Env chans: " << infix_print{chansIntEnv, ","} << endl;
        cerr << "Env vars:  " << infix_print{varsEnv, ","} << endl;
        cerr << "----------------------------------------------------------\n";
        cerr << "IUT procs: " << procsIUT << endl;
        cerr << "IUT chans: " << infix_print{chansIntIUT, ","} << endl;
        cerr << "IUT vars:  " << infix_print{varsIUT, ","} << endl;
        cerr << "==========================================================\n";
    }
    if (verbosity >= 1) {
        if (!procsBad.empty())
            cerr << "Inconsistent procs: " << procsBad << endl;
        if (!chansBad.empty())
            cerr << "Inconsistent chans: " << infix_print{chansBad, ","} << endl;
        if (!varsBad.empty())
            cerr << "Inconsistent vars:  " << infix_print{varsBad, ","} << endl;
    }
    if (verbosity >= 2) {
        procset_t leftovers;
        for (auto* p : procs)
            if (procsEnv.find(p) == procsEnv.end() && procsIUT.find(p) == procsIUT.end())
                leftovers.insert(p);
        if (!leftovers.empty()) {
            cerr << "==== Not partitioned: ====================================\n";
            cerr << "procs: " << leftovers << endl;
        }
    }

    if (!procsBad.empty() || !chansBad.empty() || !varsBad.empty())
        return 2;
    if (progress == procs.size())
        return 0;  // all procs are partitioned
    else
        return 1;  // some left unpartitioned
}

#define BADSTYLE "style=filled,fillcolor=\"#FF8080\""
#define IUTSTYLE "style=filled,fillcolor=\"#B8C0FF\""
#define ENVSTYLE "style=filled,fillcolor=\"#C8FFC8\""
#define MEDSTYLE "style=filled,fillcolor=\"#C0C0C0\""

inline void set_remove(SignalFlow::strset_t& from, const SignalFlow::strset_t& what)
{
    for (const auto& b : what)
        from.erase(b);
}

struct surround : public std::unary_function<const char*, void>
{
    std::ostream& out;
    std::string_view pre;
    std::string_view post;
    surround(std::ostream& os, std::string_view prefix, std::string_view postfix): out{os}, pre{prefix}, post{postfix}
    {}
    void operator()(const char* x) { out << pre << x << post; }
};

void Partitioner::printForDot(std::ostream& os, bool ranked, bool erd, bool cEdge)
{
    std::string name = title;
    for (auto& c : name)
        if (!std::isalpha(c))
            c = '_';

    os << "digraph " << name << " {\n";
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

    auto procsR = processes, chansR = channels, varsR = variables;  // remaining

    auto osi = std::ostream_iterator<const std::string>{os, "; "};

    if (!procsBad.empty()) {
        os << "// processes in conflict:\n"
              "  node [shape=ellipse,peripheries=1," BADSTYLE "];\n  ";
        for (const auto& p : procsBad) {
            os << p->name << "; ";
            procsR.erase(p->name);
        }
        os << endl;
    }
    if (!chansBad.empty()) {
        os << "// channels in conflict:\n"
              "  node [shape=diamond,peripheries=1," BADSTYLE "];\n  ";
        for (const auto& c : chansBad)
            os << std::quoted(c) << "; ";
        os << endl;
        set_remove(chansR, chansBad);
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
        for (auto* p : procsIUT) {
            os << p->name << "; ";
            procsR.erase(p->name);
        }
        os << endl;
    }
    if (!chansIntIUT.empty()) {
        os << "// IUT channels:\n";
        os << "  node [shape=diamond,peripheries=1," IUTSTYLE "];\n  ";
        for (const auto& c : chansIntIUT)
            os << std::quoted(c) << "; ";
        os << endl;
        set_remove(chansR, chansIntIUT);
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
        for (const auto& c : chansOut)
            os << std::quoted(c) << "; ";
        os << endl;
        set_remove(chansR, chansOut);
    }
    if (!chansInp.empty()) {
        os << "// observable input channels (controlled by Env):\n"
              "  node [shape=diamond,peripheries=2," ENVSTYLE "];\n  ";
        for (const auto& c : chansInp)
            os << std::quoted(c) << "; ";
        os << endl;
        set_remove(chansR, chansInp);
    }

    if (!procsEnv.empty()) {
        os << "// Env processes:\n";
        os << "  node [shape=ellipse,peripheries=1," ENVSTYLE "];\n  ";
        for (auto* p : procsEnv) {
            os << p->name << "; ";
            procsR.erase(p->name);
        }
        os << endl;
    }
    if (!chansIntEnv.empty()) {
        os << "// Env channels:\n";
        os << "  node [shape=diamond,peripheries=1," ENVSTYLE "];\n  ";
        for (const auto& c : chansIntEnv)
            os << std::quoted(c) << "; ";
        os << endl;
        set_remove(chansR, chansIntEnv);
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
        for (const auto& c : chansR)
            os << std::quoted(c) << "; ";
        os << endl;
    }
    if (!varsR.empty()) {
        os << "  node [shape=rectangle,peripheries=1," MEDSTYLE "];\n";
        copy(varsR.begin(), varsR.end(), osi);
        os << endl;
    }

    /* draw variable edges */
    os << "// edges for write to variable:\n"
       << "  edge [style=bold];\n";
    for (auto* p : procs) {
        if (!p->wtVars.empty()) {
            for (const auto& v2c : p->wtVars) {
                os << "  " << p->name << " -> " << v2c.first << " [label=\"(";
                /* enumerate channels when variable is accessed */
                os << infix_print{v2c.second, ","} << ")\"];\n";
            }
        }
    }
    os << "// edges for read of variable:\n"
       << "  edge [style=solid];\n";
    for (auto* p : procs) {
        if (!p->rdVars.empty()) {
            for (const auto& v2c : p->rdVars) {
                os << "  " << v2c.first << " -> " << p->name << " [label=\"(";
                /* enumerate channels when variable is accessed */
                os << infix_print{v2c.second, ","} << ")\"];\n";
            }
        }
    }

    /* enumerate draw channels */
    if (!channels.empty()) {
        if (!cEdge) { /* channels displayed as separate nodes (like variables) */
            os << "// channel transmit edges:\n"
               << "  edge [style=bold];\n";
            for (auto* p : procs)
                for (const auto& c : p->outChans)
                    os << "  " << p->name << " -> \"" << c << "\";\n";
            os << "// channel receive edges:\n"
               << "  edge [style=solid];\n";
            for (auto* p : procs)
                for (const auto& c : p->inChans)
                    os << "  \"" << c << "\" -> " << p->name << ";\n";
        } else { /* channels are only on edges */
            const char* src = "NO_SRC";
            const char* dst = "NO_DST";
            /* build an index of outgoing edges sorted by destination TA */
            for (auto* p : procs) {
                /* traverse all outgoing channels */
                for (const auto& c : p->outChans) {
                    auto dests = receivers.find(c);
                    if (dests != receivers.end()) {  // there are destinations
                        for (const auto& rec : dests->second)
                            p->outEdges[rec].insert(c);
                    } else  // no destination
                        p->outEdges[nullptr].insert(c);
                }
            }
            /* display all edges: */
            bool noDst = false;
            os << "  edge[style=solid];\n";
            for (auto* p : procs) {
                /* display outgoing edges: */
                for (const auto& edge : p->outEdges) {
                    // display edge:
                    if (edge.first != nullptr) {
                        // normal destination TA
                        os << "  " << p->name << " -> " << edge.first->name << " [label=\"[";
                    } else {  // there was no destination TA
                        if (!noDst) {
                            os << "  " << dst << " [style=filled,fillcolor=red];\n";
                            noDst = true;
                        }
                        os << "  " << p->name << " -> " << dst << " [label=\"[";
                    }
                    // enumerate all channels on the edge:
                    auto b = edge.second.begin(), e = edge.second.end();
                    if (b != e) {
                        os << std::quoted(*b);
                        while (++b != e)
                            os << "," << std::quoted(*b);
                    }
                    os << "]\"];\n";
                }
                /* by now all inps with sources are displayed as outputs
                 * search and display inputs w/o sources */
                bool noSrc = false;
                for (const auto& c : p->inChans) {
                    auto trans = transmitters.find(c);
                    if (trans == transmitters.end()) {
                        if (!noSrc) {
                            os << "  " << src << " [style=filled,fillcolor=red];\n";
                            noSrc = true;
                        }
                        os << "  " << src << " -> " << p->name << " [label=\"" << c << "\"];\n";
                    }
                }
            }
        }
    }
    os << "}" << endl;
}

void Partitioner::fillWithEnvProcs(strset_t& procs)
{
    for (const auto* p : procsEnv)
        procs.insert(p->name);
}

void Partitioner::fillWithIUTProcs(strset_t& procs)
{
    for (const auto* p : procsIUT)
        procs.insert(p->name);
}

void DistanceCalculator::addVariableNeedle(const std::string& var)
{
    /* FIXME: find global variable if the variable is local process parameter*/
    distancesUpToDate = false;
    auto name = var.substr(0, var.find('.'));

    if (variables.find(name) == variables.end()) {
        cerr << "Variable not found: " << var << endl;
        return;
    }
    dist_t* distance = nullptr;
    str2dist_t::iterator i = distances.find(name);
    if (i == distances.end()) {
        varNeedles.insert(name);
        distances[name] = dist_t{0, 1, 0};
        // distance = &distances[name]; // FIXME: work-in-progress.
    } else {
        distance = &(i->second);
        if (distance->hops == 0 && distance->distance == 0) {
            /* double the complexity if mentioned several times */
            distance->complexity = 2 * distance->complexity;
        } else {
            distance->hops = 0;
            distance->distance = 0;
        }
    }
}

void DistanceCalculator::addProcessNeedle(const std::string& proc)
{
    distancesUpToDate = false;
    auto name = proc.substr(0, proc.find('.'));

    if (processes.find(name) == processes.end()) {
        cerr << "AddNeedle: Process not found: " << proc << endl;
        return;
    }

    dist_t* distance = nullptr;
    str2dist_t::iterator i = distances.find(name);
    if (i == distances.end()) {
        procNeedles.insert(name);
        distances[name] = dist_t{0u, calcComplexity(name), 0u};
        // distance = &distances[name]; // FIXME: work-in-progress.
    } else {
        distance = &(i->second);
        if (distance->hops == 0 && distance->distance == 0) {
            /* double the complexity if mentioned several times */
            distance->complexity = 2 * distance->complexity;
        } else {
            distance->hops = 0;
            distance->distance = 0;
        }
    }
}

void DistanceCalculator::updateDistancesFromVariable(const std::string& name, const dist_t* d)
{
    // find all processes that transmit/write on this variable:
    str2procset_t::const_iterator t = transmitters.find(name);
    if (t == transmitters.end())
        return;
    for (const auto* p : t->second) {
        dist_t* distance = nullptr;
        str2dist_t::iterator i = distances.find(p->name);
        if (i == distances.end()) {
            procNeedles.insert(p->name);
            distances[p->name] = dist_t{d->hops + 1, calcComplexity(p->name), d->distance + d->complexity};
            distance = &distances[p->name];
        } else {
            distance = &(i->second);
            if (distance->distance <= d->distance + d->complexity)
                continue;  // old distance is shorter, no changes to propagate
            else {
                distance->hops = d->hops + 1;
                distance->distance = d->distance + d->complexity;
            }
        }
        updateDistancesFromProcess(p->name, distance);
    }
}

void DistanceCalculator::updateDistancesFromProcess(const std::string& name, const dist_t* d)
{
    /* find the process structure representing this process */
    auto s = std::find_if(procs.begin(), procs.end(), [&name](proc_t* p) { return p->name == name; });
    if (s == procs.end()) {
        cerr << "UpdateDistancesFromProcess: Process not found: " << name << endl;
        return;
    }
    /* for each channel the process listens to: */
    for (const auto& c : (*s)->inChans) {
        /* find all processes that send on this channel: */
        str2procset_t::const_iterator t = transmitters.find(c);
        if (t == transmitters.end())
            continue;
        /* update the distances for each transmitting process */
        for (const auto* p : t->second) {
            dist_t* distance = nullptr;
            str2dist_t::iterator i = distances.find(p->name);
            if (i == distances.end()) {
                procNeedles.insert(p->name);
                distances[p->name] = dist_t{d->hops + 1, calcComplexity(p->name), d->distance + d->complexity};
                distance = &distances[p->name];
            } else {
                distance = &(i->second);
                if (distance->distance <= d->distance + d->complexity)
                    continue;  // old distance is shorter no changes to propagate
                else {
                    distance->hops = d->hops + 1;
                    distance->distance = d->distance + d->complexity;
                }
            }
            updateDistancesFromProcess(p->name, distance);
        }
    }
    /* for each variable the process reads from: */
    for (const auto& v : (*s)->rdVars) {
        dist_t* distance = nullptr;
        str2dist_t::iterator i = distances.find(v.first);
        if (i == distances.end()) {
            varNeedles.insert(v.first);
            distances[v.first] = dist_t{d->hops + 1, 1, d->distance + d->complexity};
            distance = &distances[v.first];
        } else {
            distance = &(i->second);
            if (distance->distance <= d->distance + d->complexity)
                continue;  // old distance is shorter, no changes to propagate
            else {
                distance->hops = d->hops + 1;
                distance->distance = d->distance + d->complexity;
            }
        }
        updateDistancesFromVariable(v.first, distance);
    }
}

uint32_t DistanceCalculator::calcComplexity(const std::string& process)
{
    uint32_t result = 0;
    for (const auto& i : doc.getProcesses())
        if (i.uid.getName() == process)
            result += i.templ->edges.size();
    return result;
}

void DistanceCalculator::printProcsForDot(std::ostream& os, bool erd)
{
    /* Enumerate processes with common look-attributes */
    os << "  subgraph procs {\n";
    if (erd) {
        os << "    node [shape=rectangle,style=filled];\n";
    } else {
        os << "    node [shape=ellipse,style=filled];\n";
    }
    os << "    ";

    for (const auto* p : procs) {
        str2dist_t::const_iterator d = distances.find(p->name);
        if (d == distances.end()) {
            os << p->name << "[label=\"\\N\\n(( ?, ?))\"]; ";
        } else {
            os << p->name << "[label=\"\\N\\n((" << d->second.hops << ", " << d->second.distance << "))\"]; ";
        }
    }
    os << "\n  }\n";
}

void DistanceCalculator::printVarsForDot(std::ostream& os, bool ranked, bool erd)
{
    // draw variables
    /* specify attributes for all nodes */
    os << "  subgraph cluste_vars {\n";
    os << "    style=invis;\n";
    if (ranked) {
        os << "    rank=min;\n";
    }
    if (erd) {
        os << "    node [shape=diamond,color=blue];\n    ";
    } else {
        os << "    node [shape=rectangle,color=blue];\n    ";
    }
    for (const auto& i : variables) {
        str2dist_t::const_iterator d = distances.find(i);
        if (d == distances.end())
            os << i << "[label=\"\\N\\n(( ?, ?))\"";
        else
            os << i << "[label=\"\\N\\n((" << d->second.hops << ", " << d->second.distance << "))\"";
        if (transmitters.find(i) == transmitters.end())
            os << "]; ";  // const
        else
            os << ",style=bold]; ";  // others bold
    }
    os << "\n  }\n";
}

uint32_t DistanceCalculator::getDistance(const std::string& element)
{
    if (!distancesUpToDate)
        updateDistances();

    str2dist_t::iterator f = distances.find(element);
    if (f == distances.end()) {
        // cerr << "GetDistance: Process not found: " << element << endl;
        return dist_t::maximum;
    }
    return f->second.distance;
}

void DistanceCalculator::printForDot(std::ostream& os, bool ranked, bool erd, bool cEdged)
{
    if (!distancesUpToDate)
        updateDistances();

    SignalFlow::printForDot(os, ranked, erd, cEdged);
}

void DistanceCalculator::updateDistances()
{
    /* cleanup the old stuff: put all distances at infinity=INT_MAX: */
    for (auto& i : distances)
        if (i.second.hops > 0) {
            i.second.hops = dist_t::maximum;
            i.second.distance = dist_t::maximum;
        }
    /* calculate distances from variable needles: */
    for (const auto& i : varNeedles) {
        str2dist_t::iterator f = distances.find(i);
        if (f == distances.end()) {
            cerr << "Variable not found: " << i << endl;
            exit(EXIT_FAILURE);
        }
        updateDistancesFromVariable(i, &(f->second));
    }
    /* calculate distances from process needles: */
    for (const auto& i : procNeedles) {
        str2dist_t::iterator f = distances.find(i);
        if (f == distances.end()) {
            cerr << "Process not found: " << i << endl;
            exit(EXIT_FAILURE);
        }
        updateDistancesFromProcess(i, &(f->second));
    }
    distancesUpToDate = true;
}
