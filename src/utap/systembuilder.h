// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2002-2004 Uppsala University and Aalborg University.

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

#ifndef UTAP_SYSTEMBUILDER_H
#define UTAP_SYSTEMBUILDER_H

#include <cassert>
#include <vector>
#include <inttypes.h>

#include "utap/statementbuilder.h"
#include "utap/utap.h"

namespace UTAP
{
    /**
     * This class constructs a TimedAutomataSystem. It avoids as much
     * type checking as possible - type checking should be done with
     * the TypeChecker class. However some checks are more convenient
     * to do in SystemBuilder:
     *
     *  - states are not both committed and urgent
     *  - the source and target of an edge is a state
     *  - the dot operator is applied to a process or a structure (StatementBuilder)
     *  - functions are not recursive (StatementBuilder)
     *  - only declared functions are called (ExpressionBuilder)
     *  - functions are called with the correct number of arguments (StatementBuilder)
     *  - the initial state of a template is actually declared as a state
     *  - templates in instantiations have been declared
     *  - identifiers are not declared twice in the same scope (StatementBuilder)
     *  - type names do exist and are declared as types (StatementBuilder)
     *  - processes in the system line have been declared
     *
     * Left hand side expressions are assigned the correct type by
     * SystemBuilder; if not it would be difficult to represent
     * dot-expressions.
     *
     * SystemBuilder does not
     *  - check the correctness of variable initialisers, nor
     *    does it complete variable initialisers
     *  - type check expressions
     *  - check if arguments to functions or templates match the
     *    formal parameters
     *  - check if something is a proper left hand side value
     *  - check if things are assignment compatible
     *  - check conflicting use of synchronisations and guards on edge
     *  - handle properties
     *
     * Use TypeChecker for these things.
     */
    class SystemBuilder : public StatementBuilder
    {
    protected:
        /** The current process priority level. */
        int32_t currentProcPriority;

        /** The edge under construction. */
        edge_t *currentEdge;

        /** The gantt map under construction. */
        gantt_t *currentGantt;

        /** The condition under construction. */
        condition_t *currentCondition;

        /** The update under construction. */
        update_t *currentUpdate;

        /** The message under construction. */
        message_t *currentMessage;

        /** The instance line under construction. */
        instanceLine_t* currentInstanceLine;

        iodecl_t *currentIODecl;

        query_t* currentQuery;

        //
        // Method for handling types
        //

        declarations_t *getCurrentDeclarationBlock();

        virtual variable_t *addVariable(type_t type, const char*  name,
                                        expression_t init);
        virtual bool addFunction(type_t type, const char* name);

        void addSelectSymbolToFrame(const char* name, frame_t&);
        void declHybridRec(expression_t);

    public:
        SystemBuilder(TimedAutomataSystem *);

        virtual void ganttDeclStart(const char* name);
        virtual void ganttDeclSelect(const char *id);
        virtual void ganttDeclEnd();
        virtual void ganttEntryStart();
        virtual void ganttEntrySelect(const char *id);
        virtual void ganttEntryEnd();
        virtual void declProgress(bool);
        virtual void procBegin(const char* name, const bool isTA = true,
                const std::string type = "", const std::string mode = "");
        virtual void procEnd();
        virtual void procState(const char* name, bool hasInvariant, bool hasER);
        virtual void procStateCommit(const char* name);
        virtual void procStateUrgent(const char* name);
        virtual void procStateInit(const char* name);
        virtual void procBranchpoint(const char* name);
        virtual void procEdgeBegin(const char* from, const char* to, const bool control, const char* actname);
        virtual void procEdgeEnd(const char* from = 0, const char* to = 0);
        virtual void procSelect(const char *id);
        virtual void procGuard();
        virtual void procSync(Constants::synchronisation_t type);
        virtual void procUpdate();
        virtual void procProb();
        virtual void instantiationBegin(const char*, size_t, const char*);
        virtual void instantiationEnd(
            const char *, size_t, const char *, size_t);
        virtual void process(const char*);
        virtual void processListEnd();
        virtual void done();
        virtual void beforeUpdate();
        virtual void afterUpdate();
        virtual void beginChanPriority();
        virtual void addChanPriority(char separator);
        virtual void defaultChanPriority();
        virtual void incProcPriority();
        virtual void procPriority(const char*);
        virtual void procInstanceLine();
        virtual void instanceName(const char* name, bool templ=true);
        virtual void instanceNameBegin(const char *name);
        virtual void instanceNameEnd(const char *name, size_t arguments);
        virtual void procMessage(const char* from, const char* to, const int loc, const bool pch);
        virtual void procMessage(Constants::synchronisation_t type);
        virtual void procCondition(const std::vector<char*> anchors, const int loc,
        		const bool pch, const bool hot);
        virtual void procCondition(); // Label
        virtual void procLscUpdate(const char* anchor, const int loc, const bool pch);
        virtual void procLscUpdate(); // Label
        virtual void hasPrechart(const bool pch);

        virtual void exprSync(Constants::synchronisation_t type);
        virtual void declIO(const char*,int,int);
        virtual void declDynamicTemplate (std::string);

        virtual void queryBegin();
        virtual void queryFormula(const char* formula, const char* location);
        virtual void queryComment(const char* comment);
        virtual void queryEnd();
    };
}
#endif
