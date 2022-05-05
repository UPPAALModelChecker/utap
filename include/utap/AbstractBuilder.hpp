// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-

/* libutap - Uppaal Timed Automata Parser.
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

#ifndef UTAP_ABSTRACTBUILDER_HH
#define UTAP_ABSTRACTBUILDER_HH

#include "utap/builder.h"
#include "utap/position.h"
#include "utap/utap.h"

#include <exception>
#include <string>
#include <vector>

namespace UTAP
{
    class NotSupportedException : public std::exception
    {
    private:
        std::string error;

    public:
        NotSupportedException(const char* err) { error = err; }
        virtual ~NotSupportedException() {}
        const char* what() const noexcept override { return error.c_str(); }
    };

    class AbstractBuilder : public ParserBuilder
    {
    protected:
        position_t position;

    public:
        AbstractBuilder() = default;

        void setPosition(uint32_t, uint32_t) override;

        /************************************************************
         * Query functions
         */
        bool isType(const char*) override;

        /************************************************************
         * Types
         */
        void typeDuplicate() override;
        void typePop() override;
        void typeBool(PREFIX) override;
        void typeInt(PREFIX) override;
        void typeString(PREFIX) override;
        void typeDouble(PREFIX) override;
        void typeBoundedInt(PREFIX) override;
        void typeChannel(PREFIX) override;
        void typeClock(PREFIX) override;
        void typeVoid() override;
        void typeScalar(PREFIX) override;
        void typeName(PREFIX, const char* name) override;
        void typeStruct(PREFIX, uint32_t fields) override;
        void typeArrayOfSize(size_t) override;
        void typeArrayOfType(size_t) override;
        void structField(const char* name) override;
        void declTypeDef(const char* name) override;

        /************************************************************
         * Variable declarations
         */
        void declVar(const char* name, bool init) override;
        void declInitialiserList(uint32_t num) override;  // n initialisers
        void declFieldInit(const char* name) override;    // 1 initialiser

        /********************************************************************
         * Gantt chart declaration
         */
        void ganttDeclStart(const char* name) override;
        void ganttDeclSelect(const char* id) override;
        void ganttDeclEnd() override;
        void ganttEntryStart() override;
        void ganttEntrySelect(const char* id) override;
        void ganttEntryEnd() override;

        /************************************************************
         * Progress measure declarations
         */
        void declProgress(bool) override;

        /************************************************************
         * Function declarations
         */
        void declParameter(const char* name, bool) override;
        void declFuncBegin(const char* name) override;  // n paramaters
        void declFuncEnd() override;                    // 1 block
        void dynamicLoadLib(const char* name) override;
        void declExternalFunc(const char* name, const char* alias) override;

        /************************************************************
         * Process declarations
         */
        void procBegin(const char* name, const bool isTA = true, const std::string& type = "",
                       const std::string& mode = "") override;
        void procEnd() override;                                                   // 1 ProcBody
        void procState(const char* name, bool hasInvariant, bool hasER) override;  // 1 expr
        void procStateCommit(const char* name) override;                           // mark previously decl. state
        void procStateUrgent(const char* name) override;                           // mark previously decl. state
        void procStateInit(const char* name) override;                             // mark previously decl. state
        void procBranchpoint(const char* name) override;
        void procEdgeBegin(const char* from, const char* to, const bool control, const char* actname) override;
        void procEdgeEnd(const char* from, const char* to) override;
        // 1 epxr,1sync,1expr
        void procSelect(const char* id) override;
        void procGuard() override;
        void procSync(Constants::synchronisation_t type) override;  // 1 expr
        void procUpdate() override;
        void procProb() override;
        /************************************************************
         * Process declarations for LSC
         */
        void procInstanceLine() override;
        void instanceName(const char* name, bool templ = true) override;
        void instanceNameBegin(const char* name) override;
        void instanceNameEnd(const char* name, size_t arguments) override;
        void procMessage(const char* from, const char* to, const int loc, const bool pch) override;
        void procMessage(Constants::synchronisation_t type) override;  // 1 expr
        void procCondition(const std::vector<std::string>& anchors, const int loc, const bool pch,
                           const bool hot) override;
        void procCondition() override;  // Label
        void procLscUpdate(const char* anchor, const int loc, const bool pch) override;
        void procLscUpdate() override;  // Label
        void hasPrechart(const bool pch) override;

        /************************************************************
         * Statements
         */
        void blockBegin() override;
        void blockEnd() override;
        void emptyStatement() override;
        void forBegin() override;                        // 3 expr
        void forEnd() override;                          // 1 stat
        void iterationBegin(const char* name) override;  // 1 id, 1 type
        void iterationEnd(const char* name) override;    // 1 stat
        void whileBegin() override;
        void whileEnd() override;  // 1 expr, 1 stat
        void doWhileBegin() override;
        void doWhileEnd() override;  // 1 stat, 1 expr
        void ifBegin() override;
        void ifCondition() override;  // 1 expr
        void ifThen() override;       // 1 statement
        void ifEnd(bool) override;    // 1 expr, 1 or 2 statements
        void breakStatement() override;
        void continueStatement() override;
        void switchBegin() override;
        void switchEnd() override;  // 1 expr, 1+ case/default
        void caseBegin() override;
        void caseEnd() override;  // 1 expr, 0+ stat
        void defaultBegin() override;
        void defaultEnd() override;           // 0+ statements
        void exprStatement() override;        // 1 expr
        void returnStatement(bool) override;  // 1 expr if argument is true
        void assertStatement() override;

        /************************************************************
         * Expressions
         */
        void exprTrue() override;
        void exprFalse() override;
        void exprDouble(double) override;
        void exprString(const char*) override;
        void exprLocation() override;
        void exprId(const char* varName) override;
        void exprNat(int32_t) override;  // natural number
        void exprCallBegin() override;
        void exprCallEnd(uint32_t n) override;                 // n exprs as arguments
        void exprArray() override;                             // 2 expr
        void exprPostIncrement() override;                     // 1 expr
        void exprPreIncrement() override;                      // 1 expr
        void exprPostDecrement() override;                     // 1 expr
        void exprPreDecrement() override;                      // 1 expr
        void exprAssignment(Constants::kind_t op) override;    // 2 expr
        void exprUnary(Constants::kind_t unaryop) override;    // 1 expr
        void exprBinary(Constants::kind_t binaryop) override;  // 2 expr
        void exprNary(Constants::kind_t, uint32_t num) override;
        void exprScenario(const char* name) override;
        void exprTernary(Constants::kind_t ternaryop, bool firstMissing) override;  // 3 expr
        void exprInlineIf() override;                                               // 3 expr
        void exprComma() override;                                                  // 2 expr
        void exprDot(const char*) override;                                         // 1 expr
        void exprDeadlock() override;
        void exprForAllBegin(const char* name) override;
        void exprForAllEnd(const char* name) override;
        void exprExistsBegin(const char* name) override;
        void exprExistsEnd(const char* name) override;
        void exprSumBegin(const char* name) override;
        void exprSumEnd(const char* name) override;

        void exprProbaQualitative(Constants::kind_t, Constants::kind_t, double) override;
        void exprProbaQuantitative(Constants::kind_t) override;
        void exprProbaCompare(Constants::kind_t, Constants::kind_t) override;
        void exprProbaExpected(const char* identifier) override;
        void exprSimulate(int no_of_exprs, bool = false, int = 0) override;
        void exprBuiltinFunction1(Constants::kind_t) override;
        void exprBuiltinFunction2(Constants::kind_t) override;
        void exprBuiltinFunction3(Constants::kind_t) override;
        void exprMinMaxExp(Constants::kind_t, PRICETYPE, Constants::kind_t) override;
        void exprLoadStrategy() override;
        void exprSaveStrategy() override;

        // MITL
        void exprMitlFormula() override;
        void exprMitlUntil(int, int) override;
        void exprMitlRelease(int, int) override;
        void exprMitlDisj() override;
        void exprMitlConj() override;
        void exprMitlNext() override;
        void exprMitlAtom() override;
        void exprOptimize(int, int, int, int) override;

        /************************************************************
         * System declaration
         */
        void instantiationBegin(const char*, size_t, const char*) override;
        void instantiationEnd(const char*, size_t, const char*, size_t) override;
        void process(const char*) override;
        void processListEnd() override;
        void done() override;

        void handleExpect(const char* text) override;

        /************************************************************
         * Properties
         */
        void property() override;
        void scenario(const char*) override;             // LSC
        void parse(const char*) override;                // LSC
        void strategyDeclaration(const char*) override;  // tiga-smc
        void subjection(const char*) override;
        void imitation(const char*) override;

        /********************************************************************
         * Guiding
         */
        void beforeUpdate() override;
        void afterUpdate() override;

        /********************************************************************
         * Priority
         */
        void beginChanPriority() override;
        void addChanPriority(char separator) override;
        void defaultChanPriority() override;
        void incProcPriority() override;
        void procPriority(const std::string&) override;

        void declDynamicTemplate(const std::string& name) override;
        void exprSpawn(int) override;
        void exprExit() override;
        void exprNumOf() override;

        void exprForAllDynamicBegin(const char*, const char*) override;
        void exprForAllDynamicEnd(const char* name) override;
        void exprExistsDynamicBegin(const char*, const char*) override;
        void exprExistsDynamicEnd(const char* name) override;
        void exprSumDynamicBegin(const char*, const char*) override;
        void exprSumDynamicEnd(const char*) override;
        void exprForeachDynamicBegin(const char*, const char*) override;
        void exprForeachDynamicEnd(const char* name) override;
        void exprDynamicProcessExpr(const char*) override;
        void exprMITLForAllDynamicBegin(const char*, const char*) override;
        void exprMITLForAllDynamicEnd(const char* name) override;
        void exprMITLExistsDynamicBegin(const char*, const char*) override;
        void exprMITLExistsDynamicEnd(const char* name) override;

        /** Verification queries */
        void modelOption(const char* key, const char* value) override;
        void queryBegin() override;
        void queryFormula(const char* formula, const char* location) override;
        void queryComment(const char* comment) override;
        void queryOptions(const char* options, const char*) override;
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
