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

#ifndef UTAP_STATEMENTBUILDER_H
#define UTAP_STATEMENTBUILDER_H

#include "utap/ExpressionBuilder.hpp"
#include "utap/utap.h"

#include <filesystem>
#include <vector>
#include <cinttypes>

namespace UTAP
{
    /**
     * Partial implementation of the builder interface, useful
     * for building something with statements that is not a UTAP document.
     */
    class StatementBuilder : public ExpressionBuilder
    {
    protected:
        /**
         * The \a params frame is used temporarily during parameter
         * parsing.
         */
        frame_t params{frame_t::createFrame()};

        /** The function currently being parsed. */
        function_t* currentFun{nullptr};

        /** Stack of nested statement blocks. */
        std::vector<BlockStatement*> blocks;

        /** The types of a struct. */
        std::vector<type_t> fields;

        /** The labels of a struct. */
        std::vector<std::string> labels;

        /** path to libraries*/
        std::vector<std::filesystem::path> libpaths;

        virtual variable_t* addVariable(type_t type, const std::string& name, expression_t init, position_t pos) = 0;
        virtual bool addFunction(type_t type, const std::string& name, position_t pos) = 0;

        static void collectDependencies(std::set<symbol_t>&, expression_t);
        static void collectDependencies(std::set<symbol_t>&, type_t);

    public:
        explicit StatementBuilder(Document&, std::vector<std::filesystem::path> libpaths = {});
        StatementBuilder(const StatementBuilder&) = delete;
        ~StatementBuilder() noexcept override;

        void typeArrayOfSize(size_t) override;
        void typeArrayOfType(size_t) override;
        void typeStruct(PREFIX, uint32_t fields) override;
        void structField(const char* name) override;
        void declTypeDef(const char* name) override;
        void declVar(const char* name, bool init) override;
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
        void iterationBegin(const char* name) override;
        void iterationEnd(const char* name) override;
        void whileBegin() override;
        void whileEnd() override;
        void doWhileBegin() override;
        void doWhileEnd() override;
        void ifBegin() override{};
        void ifCondition() override{};
        void ifThen() override{};
        void ifEnd(bool) override;
        void exprStatement() override;
        void returnStatement(bool) override;
        void assertStatement() override;
        void exprCallBegin() override;
    };
}  // namespace UTAP
#endif
