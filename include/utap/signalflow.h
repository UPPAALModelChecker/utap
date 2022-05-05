// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2020 Aalborg University.
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

#ifndef UTAP_SIGNALFLOW_HH
#define UTAP_SIGNALFLOW_HH

#include "utap/document.h"
#include "utap/statement.h"

#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <stack>

namespace UTAP
{
    /**
     * Class SignalFlow is for analysing UPPAAL specifications and
     * extracting the timed automata input/output "interface"
     * information which can be treated as a data flow or
     * entity-relationship map of the system model.
     *
     * The result can be processed by the dot (graphviz.org) to
     * produce a "human-readable" picture.  The other (tron) format is
     * used in TRON project.  Feel free to add more "formats" and/or
     * tune the dot output.
     *
     * The document must be built by TypeChecker/DocumentBuilder before
     * SignalFlow.  Simply create using constructor and then use
     * print* methods.  The rest of methods are used internally by
     * visitor pattern.  Feel free to add new print* methods or
     * inheriting classes.
     *
     * Author: Marius Mikucionis <marius@cs.aau.dk>
     */
    class SignalFlow : public StatementVisitor
    {
    public:
        using strset_t = std::set<std::string>;                // string set
        struct proc_t;                                         // info on process input/output
        using proc2strset_t = std::map<proc_t*, strset_t>;     // proc->string set
        using str2strset_t = std::map<std::string, strset_t>;  // string->string set

        struct proc_t
        {                                 // info about process input/output
            const std::string name;       // name of the process
            strset_t inChans, outChans;   // input/output channels used by process
            str2strset_t rdVars, wtVars;  // read/written variables with channels
            proc2strset_t outEdges;       // outChans indexed by destination process
            proc_t(const std::string& name): name{name} {}
        };
        using procset_t = std::set<proc_t*>;
        using str2procset_t = std::map<const std::string, procset_t>;
        using exprref_t = std::map<const symbol_t, expression_t>;  // fn-params

    protected:
        int verbosity{0};                       // 0 - silent, 1 - errors, 2 - warnings, 3 - diagnostics
        const std::string title;                // title of the Uppaal TA document
        procset_t procs;                        // list of all processes in the system
        str2procset_t receivers, transmitters;  // processes sorted by vars/chans
        strset_t processes, channels, variables;
        proc_t* cTA{nullptr};     // current automaton in traversal
        instance_t* cP{nullptr};  // current process in traversal
        std::string cChan;        // channel on current transition in traversal
        std::string chanString;
        bool inp{false}, out{false}, sync{false}, paramsExpanded{false};  // current expression state
        std::stack<std::pair<bool, bool> > ioStack;                       // remember I/O state
        std::stack<exprref_t> refparams;                                  // parameter passed by reference
        std::stack<exprref_t> valparams;                                  // parameter passed by value

        bool checkParams(const symbol_t& s);  // maps parameter to global symbol
        void addChan(const std::string&, strset_t&, str2procset_t&);
        void addVar(const symbol_t&, str2strset_t&, str2procset_t&);
        void visitProcess(instance_t&);
        void visitExpression(const expression_t&);
        void pushIO() { ioStack.push(std::make_pair(inp, out)); }
        void popIO()
        {
            inp = ioStack.top().first;
            out = ioStack.top().second;
            ioStack.pop();
        }

        /* prints list of processes with their look-attributes */
        virtual void printProcsForDot(std::ostream& os, bool erd);
        /* prints list of variables with their look-attributes */
        virtual void printVarsForDot(std::ostream& os, bool ranked, bool erd);
        /* prints edges representing writes to variables */
        virtual void printVarsWriteForDot(std::ostream& os);
        /* prints edges representing reads from variables */
        virtual void printVarsReadForDot(std::ostream& os);
        /* prints channel communication as labels on I/O edges */
        virtual void printChansOnEdgesForDot(std::ostream& os);
        /* prints channels as separate nodes (similar to variables) */
        virtual void printChansSeparateForDot(std::ostream& os, bool ranked, bool erd);

    public:
        /**
         * Analyse the document and extract I/O information:
         */
        SignalFlow(const std::string& title, Document& doc);

        void setVerbose(int verbose) { verbosity = verbose; }
        /**
         * All strings are from TASystem (don't dispose TASystem before SignalFlow).
         */
        virtual ~SignalFlow();

        /**
         * Print I/O information in TRON format into given output stream.
         */
        void printForTron(std::ostream& os);

        /**
         * Print I/O information in DOT format into given output stream.
         * ranked -- puts oposite "ranks" on variables and channels
         * erd -- puts boxes and diamonds rather than (compact) ellipses.
         * cEdged -- channels are printed on edges rather than separate nodes.
         */
        virtual void printForDot(std::ostream& os, bool ranked, bool erd, bool cEdged);

        /**
         * System visitor pattern extracts read/write information from UCode.
         * This is actually "const" visitor and should contain "const Statement *stat".
         */
        int32_t visitEmptyStatement(EmptyStatement* stat) override;
        int32_t visitExprStatement(ExprStatement* stat) override;
        int32_t visitForStatement(ForStatement* stat) override;
        int32_t visitIterationStatement(IterationStatement* stat) override;
        int32_t visitWhileStatement(WhileStatement* stat) override;
        int32_t visitDoWhileStatement(DoWhileStatement* stat) override;
        int32_t visitBlockStatement(BlockStatement* stat) override;
        int32_t visitSwitchStatement(SwitchStatement* stat) override;
        int32_t visitCaseStatement(CaseStatement* stat) override;
        int32_t visitDefaultStatement(DefaultStatement* stat) override;
        int32_t visitIfStatement(IfStatement* stat) override;
        int32_t visitBreakStatement(BreakStatement* stat) override;
        int32_t visitContinueStatement(ContinueStatement* stat) override;
        int32_t visitReturnStatement(ReturnStatement* stat) override;
        int32_t visitAssertStatement(UTAP::AssertStatement* stat) override;
    };

    /**
     * print -- template for pretty printing lists.
     * similar to ostream_iterator except it does not print last delimiter.
     */
    template <class T>
    struct print : public std::unary_function<T, void>
    {
        std::ostream& os;
        const std::string& infix;
        bool need;
        print(std::ostream& out, const std::string& sep): os{out}, infix{sep}, need(false) {}
        void operator()(const T& x)
        {
            if (need)
                os << infix;
            os << x;
            need = true;
        }
    };

    template <class Container>
    struct infix_print
    {
        Container&& items;
        std::string_view infix;
    };
    template <class Container>
    infix_print(Container&&, std::string_view) -> infix_print<Container>;

    template <class Container>
    std::ostream& operator<<(std::ostream& os, const infix_print<Container>& p)
    {
        auto b = std::begin(p.items), e = std::end(p.items);
        if (b != e) {
            os << *b;
            while (++b != e)
                os << p.infix << *b;
        }
        return os;
    }

    inline std::ostream& operator<<(std::ostream& os, const SignalFlow::procset_t& ps)
    {
        auto b = ps.begin(), e = ps.end();
        if (b != e) {
            os << (*b)->name;
            while (++b != e)
                os << ", " << (*b)->name;
        }
        return os;
    }

    /**
     * Partitions the system into environment and IUT according to TRON
     * assumptions. inputs/outputs are channel names. Environment processes shout
     * on inputs and listens to outputs, while IUT processes shout on outputs and
     * listen to inputs. There are additional rules to complete the partitioning
     * (to cathegorize the internal processes):
     * 1) channels, that are not declared as inputs/outputs, are non-observable,
     *    called internal.
     * 2) internal channel belongs to environment (IUT) if it is used by
     *    environment (IUT) process (respectively). Model is inconsistent and
     *    cannot be partitioned if the internal channel is used by both environment
     *    and IUT.
     * 3) process belongs to environment (IUT) if it uses the internal environment
     *    (IUT) channel (respectively).
     * 4) variable belongs to environment (IUT) if it is accessed by environment
     *    (IUT) process without observable input/output channel synchronization.
     *    Variable is not cathegorized (can be either) if accessed consistently
     *    only during observable input/output channel synchronization.
     * 5) process belongs to environment (IUT) if accesses environment (IUT)
     *    variable (respectively) without observable channel synchronization.
     * Returns:
     *  0 if partitioning was consistent and complete,
     *  1 if partitioning was consistent but incomplete (some proc/chan is free)
     *  2 if partitioning was inconsistent (some proc/chan/var is both Env and IUT)
     */
    class Partitioner : public SignalFlow
    {
    protected:
        procset_t procsEnv, procsIUT, procsBad;
        strset_t chansIntEnv, chansIntIUT, observable, chansBad;
        strset_t varsEnv, varsIUT, varsBad;
        strset_t chansInp, chansOut;
        std::string rule;

        void addProcs(const strset_t& chans, const str2procset_t& index, procset_t& result, procset_t& exclude);
        void addIntChans(const procset_t& procs, strset_t& result, strset_t& exclude);
        void addIntVars(const procset_t& procs, strset_t& result, strset_t& exclude);
        void addProcsByVars(const strset_t& vars, procset_t& procs, procset_t& exclude);

    public:
        Partitioner(const std::string& title, Document& doc): SignalFlow{title, doc} {}

        int partition(const strset_t& inputs, const strset_t& outputs);
        int partition(std::istream& ioinfo);
        void printForDot(std::ostream& os, bool ranked, bool erd, bool cEdged) override;
        void printViolation(const proc_t* process, const std::string& variable);
        void fillWithEnvProcs(strset_t& procs);
        void fillWithIUTProcs(strset_t& procs);
    };

    /**
     * DistanceCalculator is used in TargetFirst heuristic search order of Uppaal.
     * Current implementation calculates complexity distances from a process to
     * the given set of "needles"  (e.g. variables or process location mentioned
     * in query). In the future this can be refined to take the process-local
     * information into account (e.g. calculate distance for individual edges
     * within the process rather than just process).
     */
    class DistanceCalculator : public SignalFlow
    {
        strset_t varNeedles;   // set of variables of interest
        strset_t procNeedles;  // set of processes of interest
        bool distancesUpToDate;

        struct dist_t  // distance structure
        {
            static constexpr auto maximum = std::numeric_limits<int32_t>::max();
            uint32_t hops{0};        // number of hops to closest needle
            uint32_t complexity{1};  // complexity of this entity
            uint32_t distance{0};    // accumulated complexity|hops to closest needle
        };

        using str2dist_t = std::map<std::string, dist_t>;

        str2dist_t distances;

        void updateDistancesFromVariable(const std::string& name, const dist_t* distance);
        void updateDistancesFromProcess(const std::string& name, const dist_t* distance);
        uint32_t calcComplexity(const std::string& process);

    protected:
        Document& doc;
        /* overwrite how processes appear */
        void printProcsForDot(std::ostream& os, bool erd) override;
        /* overwrite how variables appear */
        void printVarsForDot(std::ostream& os, bool ranked, bool erd) override;

    public:
        DistanceCalculator(const std::string& title, Document& doc):
            SignalFlow{title, doc}, distancesUpToDate{false}, doc{doc}
        {}
        /** adds a variable needle to I/O map */
        void addVariableNeedle(const std::string& var);
        /** adds a variable needle to I/O map */
        void addProcessNeedle(const std::string& proc);
        /** Recalculates the distances to needles */
        void updateDistances();
        /** Finds a distance measure for given element */
        uint32_t getDistance(const std::string& element);

        /* overwritten to update the distances on demand. */
        void printForDot(std::ostream& os, bool ranked, bool erd, bool cEdged) override;
    };
}  // namespace UTAP

#endif
