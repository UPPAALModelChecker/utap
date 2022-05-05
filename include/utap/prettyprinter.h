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

#ifndef UTAP_PRETTYPRINTER_H
#define UTAP_PRETTYPRINTER_H

#include "utap/AbstractBuilder.hpp"

#include <iosfwd>
#include <stack>
#include <string>
#include <vector>

namespace UTAP
{
    class PrettyPrinter : public AbstractBuilder
    {
    private:
        std::vector<std::string> st;
        std::stack<std::string> type;
        std::stack<std::string> array;
        std::vector<std::string> fields;
        std::stack<std::ostream*> o;
        std::set<std::string> types;
        std::string branchpoints;
        std::string urgent;
        std::string committed;
        std::string param;
        std::string templateset;
        int select, guard, sync, update, probability;

        bool first;
        uint32_t level;

        void indent();
        void indent(std::string& s);

    public:
        PrettyPrinter(std::ostream& stream);

        void addPosition(uint32_t position, uint32_t offset, uint32_t line, const std::string& path) override;

        void handleError(const TypeException&) override;
        void handleWarning(const TypeException&) override;

        bool isType(const char*) override;
        void typeBool(PREFIX) override;
        void typeInt(PREFIX) override;
        void typeString(PREFIX) override;
        void typeDouble(PREFIX) override;
        void typeBoundedInt(PREFIX) override;
        void typeChannel(PREFIX) override;
        void typeClock(PREFIX) override;
        void typeVoid() override;
        void typeScalar(PREFIX) override;
        void typeName(PREFIX, const char* type) override;
        void typePop() override;
        void typeDuplicate() override;
        void typeArrayOfSize(size_t n) override;
        void typeArrayOfType(size_t n) override;
        void typeStruct(PREFIX prefix, uint32_t n) override;
        void structField(const char* name) override;
        void declTypeDef(const char* name) override;
        void declVar(const char* id, bool init) override;
        void declInitialiserList(uint32_t num) override;
        void declFieldInit(const char* name) override;
        void declParameter(const char* name, bool) override;
        void declFuncBegin(const char* name) override;
        void declFuncEnd() override;
        void dynamicLoadLib(const char* name) override;
        void declExternalFunc(const char* name, const char* alias) override;
        void blockBegin() override;
        void blockEnd() override;
        void emptyStatement() override;
        void forBegin() override;
        void forEnd() override;
        void iterationBegin(const char* name) override;  // 1 id, 1 type
        void iterationEnd(const char* name) override;    // 1 stat
        void whileBegin() override;
        void whileEnd() override;
        void doWhileBegin() override;
        void doWhileEnd() override;
        void ifBegin() override;
        void ifCondition() override;
        void ifThen() override;
        void ifEnd(bool) override;
        void breakStatement() override;
        void continueStatement() override;
        void exprStatement() override;
        void returnStatement(bool hasValue) override;
        void procBegin(const char* name, const bool isTA = true, const std::string& type = "",
                       const std::string& mode = "") override;
        void procState(const char* id, bool hasInvariant, bool hasExpRate) override;
        void procBranchpoint(const char* id) override;
        void procStateUrgent(const char* id) override;
        void procStateCommit(const char* id) override;
        void procStateInit(const char* id) override;
        void procSelect(const char* id) override;
        void procGuard() override;
        void procSync(Constants::synchronisation_t type) override;
        void procUpdate() override;
        void procEdgeBegin(const char* source, const char* target, const bool control);
        void procEdgeBegin(const char* source, const char* target, const bool control, const char* actname) override;
        void procEdgeEnd(const char* source, const char* target) override;
        void procEnd() override;
        void exprId(const char* id) override;
        void exprLocation() override;
        void exprNat(int32_t n) override;
        void exprTrue() override;
        void exprFalse() override;
        void exprCallBegin() override;
        void exprCallEnd(uint32_t n) override;
        void exprArray() override;
        void exprPostIncrement() override;
        void exprPreIncrement() override;
        void exprPostDecrement() override;
        void exprPreDecrement() override;
        void exprAssignment(Constants::kind_t op) override;
        void exprUnary(Constants::kind_t op) override;
        void exprBinary(Constants::kind_t op) override;
        void exprNary(Constants::kind_t op, uint32_t num) override;
        void exprScenario(const char* name) override;
        void exprTernary(Constants::kind_t op, bool firstMissing) override;
        void exprInlineIf() override;
        void exprComma() override;
        void exprDot(const char*) override;
        void exprDeadlock() override;
        void exprForAllBegin(const char* name) override;
        void exprForAllEnd(const char* name) override;
        void exprExistsBegin(const char* name) override;
        void exprExistsEnd(const char* name) override;
        void exprSumBegin(const char* name) override;
        void exprSumEnd(const char* name) override;
        void exprProbaQuantitative(Constants::kind_t) override;
        void exprMitlDiamond(int, int) override;
        void exprMitlBox(int, int) override;
        void exprSimulate(int no_of_expr, bool filter_prop, int max_accept_runs) override;
        void exprBuiltinFunction1(Constants::kind_t kind) override;
        void exprBuiltinFunction2(Constants::kind_t kind) override;
        void exprBuiltinFunction3(Constants::kind_t kind) override;
        void beforeUpdate() override;
        void afterUpdate() override;
        void instantiationBegin(const char*, size_t, const char*) override;
        void instantiationEnd(const char*, size_t, const char*, size_t) override;
        void process(const char* id) override;
        void processListEnd() override;
        void done() override;

        /** Verification queries */
        void queryBegin() override;
        void queryFormula(const char* formula, const char* location) override;
        void queryComment(const char* comment) override;
        void queryEnd() override;
    };
}  // namespace UTAP

#endif
