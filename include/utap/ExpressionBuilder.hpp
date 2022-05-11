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

#ifndef UTAP_EXPRESSIONBUILDER_HH
#define UTAP_EXPRESSIONBUILDER_HH

#include "AbstractBuilder.hpp"
#include "utap.h"

#include <stack>
#include <vector>
#include <cassert>

#define defaultIntMin -0x8000
#define defaultIntMax 0x7FFF

namespace UTAP
{
    /**
     * Partial implementation of the builder interface: The
     * ExpressionBuilder implements all expression related
     * methods.
     *
     * In order to support quantifier expressions, this class also
     * handles the type related methods.
     *
     * This class does not implement any declaration related methods.
     *
     * Internally, three stacks are maintained: One for expressions,
     * one for types and for frames (scopes).
     */
    class ExpressionBuilder : public AbstractBuilder
    {
    public:
        class ExpressionFragments
        {
        private:
            std::vector<expression_t> data;

        public:
            expression_t& operator[](int idx) { return data[data.size() - idx - 1]; }
            void push(expression_t e) { data.push_back(e); }
            void pop() { data.pop_back(); }
            void pop(uint32_t n);
            uint32_t size() { return data.size(); }
        };

        class TypeFragments
        {
        private:
            std::vector<type_t> data;

        public:
            type_t& operator[](int idx) { return data[data.size() - idx - 1]; }
            void push(type_t value) { data.push_back(value); }
            void pop()
            {
                assert(!data.empty());
                data.pop_back();
            }
            void duplicate()
            {
                assert(!data.empty());
                data.push_back(data.back());
            }
        };

    protected:
        /** Expression stack. */
        ExpressionFragments fragments;

        /** Type stack. */
        TypeFragments typeFragments;

        /** Frame stack. */
        std::stack<frame_t> frames;

        /** Pointer to the document under construction. */
        Document& document;

        /** The template currently being parsed. */
        template_t* currentTemplate{nullptr};

        /** Counter for creating unique scalarset names. */
        int32_t scalar_count;

        /** Push a new frame. */
        void pushFrame(frame_t);

        /** Pop the topmost frame. */
        void popFrame();

        bool resolve(const std::string&, symbol_t&) const;

        expression_t makeConstant(int value) const;
        expression_t makeConstant(double value) const;

        /**
         * Given a prefix and a type, this method creates a new type
         * by applying the prefix. TypeExceptions might be thrown if
         * the combination of the prefix and the type is illegal.
         */
        type_t applyPrefix(PREFIX, type_t type);

        /**
         * If this method returns true, it is allowed to access the
         * private identifiers of a process by prefixing the
         * identifier with the process name.
         *
         * This is only interesting when parsing properties. In this
         * case the method should be overridden by a sub class.
         */
        virtual bool allowProcessReferences() { return false; }
        std::map<std::string, frame_t> dynamicFrames;

    public:
        explicit ExpressionBuilder(Document& doc);
        ExpressionFragments& getExpressions();

        void addPosition(uint32_t position, uint32_t offset, uint32_t line, const std::string& path) override;

        void handleError(const TypeException&) override;
        void handleWarning(const TypeException&) override;
        void typeDuplicate() override;
        void typePop() override;
        void typeBool(PREFIX) override;
        void typeInt(PREFIX) override;
        void typeString(PREFIX prefix) override;
        void typeDouble(PREFIX) override;
        void typeBoundedInt(PREFIX) override;
        void typeChannel(PREFIX) override;
        void typeClock(PREFIX) override;
        void typeVoid() override;
        void typeScalar(PREFIX) override;
        void typeName(PREFIX, const char* name) override;
        bool isType(const char*) override;
        void exprTrue() override;
        void exprFalse() override;
        void exprDouble(double) override;
        void exprString(const char* name) override;
        void exprId(const char* varName) override;
        void exprLocation() override;
        void exprNat(int32_t) override;
        void exprCallBegin() override;
        void exprCallEnd(uint32_t n) override;
        void exprArray() override;
        void exprPostIncrement() override;
        void exprPreIncrement() override;
        void exprPostDecrement() override;
        void exprPreDecrement() override;
        void exprAssignment(Constants::kind_t op) override;
        void exprUnary(Constants::kind_t unaryop) override;
        void exprBinary(Constants::kind_t binaryop) override;
        void exprNary(Constants::kind_t op, uint32_t num) override;
        void exprScenario(const char* name) override;
        expression_t exprScenario();
        void exprTernary(Constants::kind_t ternaryop, bool firstMissing) override;
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

        void exprProbaQualitative(Constants::kind_t, Constants::kind_t, double) override;
        void exprProbaQuantitative(Constants::kind_t) override;
        void exprProbaCompare(Constants::kind_t, Constants::kind_t) override;
        void exprProbaExpected(const char*) override;
        void exprBuiltinFunction1(Constants::kind_t) override;
        void exprBuiltinFunction2(Constants::kind_t) override;
        void exprBuiltinFunction3(Constants::kind_t) override;
        void exprMinMaxExp(Constants::kind_t, PRICETYPE, Constants::kind_t) override;
        void exprSaveStrategy() override;
        void exprLoadStrategy() override;

        void exprSimulate(int nb_of_exprs, bool filter_prop = false, int max_accepting_runs = 0) override;
        void exprMitlFormula() override;
        void exprMitlUntil(int, int) override;
        void exprMitlRelease(int, int) override;
        void exprMitlDisj() override;
        void exprMitlConj() override;
        void exprMitlNext() override;
        void exprMitlAtom() override;
        void exprMitlDiamond(int, int) override;
        void exprMitlBox(int, int) override;

        /* Dynamic process creation */
        void exprSpawn(int params) override;
        void exprExit() override;
        void exprNumOf() override;
        void exprForAllDynamicBegin(const char*, const char*) override;
        void exprForAllDynamicEnd(const char* name) override;
        void exprExistsDynamicBegin(const char*, const char*) override;
        void exprExistsDynamicEnd(const char*) override;
        void exprSumDynamicBegin(const char*, const char*) override;
        void exprSumDynamicEnd(const char* name) override;
        void exprForeachDynamicBegin(const char*, const char*) override;
        void exprForeachDynamicEnd(const char* name) override;
        void pushDynamicFrameOf(template_t* t, std::string name);  // no override
        void popDynamicFrameOf(std::string name);
    };
}  // namespace UTAP

#endif
