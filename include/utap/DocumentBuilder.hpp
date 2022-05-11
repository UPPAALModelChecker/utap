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

#include "utap/StatementBuilder.hpp"
#include "utap/utap.h"

#include <vector>
#include <cinttypes>

namespace UTAP
{
    /**
     * This class constructs a Document. It avoids as much
     * type checking as possible - type checking should be done with
     * the TypeChecker class. However some checks are more convenient
     * to do in DocumentBuilder:
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
     * DocumentBuilder; if not it would be difficult to represent
     * dot-expressions.
     *
     * DocumentBuilder does not
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
    class DocumentBuilder : public StatementBuilder
    {
    protected:
        /** The current process priority level. */
        int32_t currentProcPriority{0};

        /** The edge under construction. */
        edge_t* currentEdge{nullptr};

        /** The gantt map under construction. */
        std::unique_ptr<gantt_t> currentGantt{nullptr};

        /** The condition under construction. */
        condition_t* currentCondition{nullptr};

        /** The update under construction. */
        update_t* currentUpdate{nullptr};

        /** The message under construction. */
        message_t* currentMessage{nullptr};

        /** The instance line under construction. */
        instanceLine_t* currentInstanceLine{nullptr};

        iodecl_t* currentIODecl{nullptr};

        std::unique_ptr<query_t> currentQuery{nullptr};

        results_t* currentResults{nullptr};

        expectation_t* currentExpectation{nullptr};
        //
        // Method for handling types
        //

        declarations_t* getCurrentDeclarationBlock();

        variable_t* addVariable(type_t type, const std::string& name, expression_t init, position_t pos) override;
        bool addFunction(type_t type, const std::string& name, position_t pos) override;

        void addSelectSymbolToFrame(const std::string& name, frame_t&, position_t pos);

    public:
        DocumentBuilder(Document&, std::vector<std::filesystem::path> paths = {});

        void ganttDeclStart(const char* name) override;
        void ganttDeclSelect(const char* id) override;
        void ganttDeclEnd() override;
        void ganttEntryStart() override;
        void ganttEntrySelect(const char* id) override;
        void ganttEntryEnd() override;
        void declProgress(bool) override;
        void procBegin(const char* name, const bool isTA = true, const std::string& type = "",
                       const std::string& mode = "") override;
        void procEnd() override;
        void procState(const char* name, bool hasInvariant, bool hasER) override;
        void procStateCommit(const char* name) override;
        void procStateUrgent(const char* name) override;
        void procStateInit(const char* name) override;
        void procBranchpoint(const char* name) override;
        void procEdgeBegin(const char* from, const char* to, const bool control, const char* actname) override;
        void procEdgeEnd(const char* from = 0, const char* to = 0) override;
        void procSelect(const char* id) override;
        void procGuard() override;
        void procSync(Constants::synchronisation_t type) override;
        void procUpdate() override;
        void procProb() override;
        void instantiationBegin(const char*, size_t, const char*) override;
        void instantiationEnd(const char*, size_t, const char*, size_t) override;
        void process(const char*) override;
        void processListEnd() override;
        void done() override;
        void beforeUpdate() override;
        void afterUpdate() override;
        void beginChanPriority() override;
        void addChanPriority(char separator) override;
        void defaultChanPriority() override;
        void incProcPriority() override;
        void procPriority(const std::string&) override;
        void procInstanceLine() override;
        void instanceName(const char* name, bool templ = true) override;
        void instanceNameBegin(const char* name) override;
        void instanceNameEnd(const char* name, size_t arguments) override;
        void procMessage(const char* from, const char* to, const int loc, const bool pch) override;
        void procMessage(Constants::synchronisation_t type) override;
        void procCondition(const std::vector<std::string>& anchors, const int loc, const bool pch,
                           const bool hot) override;
        void procCondition() override;  // Label
        void procLscUpdate(const char* anchor, const int loc, const bool pch) override;
        void procLscUpdate() override;  // Label
        void hasPrechart(const bool pch) override;

        void declDynamicTemplate(const std::string& name) override;

        void modelOption(const char* key, const char* value) override;
        void queryBegin() override;
        void queryFormula(const char* formula, const char* location) override;
        void queryComment(const char* comment) override;
        void queryOptions(const char* key, const char* value) override;
        void expectationBegin() override;
        void expectationEnd() override;
        void expectationValue(const char* res, const char* type, const char* value) override;
        void expectResource(const char* type, const char* value, const char* unit) override;
        void queryResultsBegin() override;
        void queryResultsEnd() override;
        void queryEnd() override;
    };
}  // namespace UTAP
#endif
