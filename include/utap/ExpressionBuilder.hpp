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

namespace UTAP {
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
    void push_frame(frame_t);

    /** Pop the topmost frame. */
    void popFrame();

    bool resolve(const std::string&, symbol_t&) const;

    expression_t make_constant(int value) const;
    expression_t make_constant(double value) const;

    /**
     * Given a prefix and a type, this method creates a new type
     * by applying the prefix. TypeExceptions might be thrown if
     * the combination of the prefix and the type is illegal.
     */
    type_t apply_prefix(PREFIX, type_t type);

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

    void add_position(uint32_t position, uint32_t offset, uint32_t line, std::shared_ptr<std::string> path) override;

    void handle_error(const TypeException&) override;
    void handle_warning(const TypeException&) override;
    void type_duplicate() override;
    void type_pop() override;
    void type_bool(PREFIX) override;
    void type_int(PREFIX) override;
    void type_string(PREFIX prefix) override;
    void type_double(PREFIX) override;
    void type_bounded_int(PREFIX) override;
    void type_channel(PREFIX) override;
    void type_clock(PREFIX) override;
    void type_void() override;
    void type_scalar(PREFIX) override;
    void type_name(PREFIX, const char* name) override;
    bool is_type(const char*) override;
    void expr_true() override;
    void expr_false() override;
    void expr_double(double) override;
    void expr_string(const char* name) override;
    void expr_identifier(const char* varName) override;
    void expr_location() override;
    void expr_nat(int32_t) override;
    void expr_call_begin() override;
    void expr_call_end(uint32_t n) override;
    void expr_array() override;
    void expr_post_increment() override;
    void expr_pre_increment() override;
    void expr_post_decrement() override;
    void expr_pre_decrement() override;
    void expr_assignment(Constants::kind_t op) override;
    void expr_unary(Constants::kind_t unaryop) override;
    void expr_binary(Constants::kind_t binaryop) override;
    void expr_nary(Constants::kind_t op, uint32_t num) override;
    void expr_scenario(const char* name) override;
    expression_t exprScenario();
    void expr_ternary(Constants::kind_t ternaryop, bool firstMissing) override;
    void expr_inline_if() override;
    void expr_comma() override;
    void expr_dot(const char*) override;
    void expr_deadlock() override;
    void expr_forall_begin(const char* name) override;
    void expr_forall_end(const char* name) override;
    void expr_exists_begin(const char* name) override;
    void expr_exists_end(const char* name) override;
    void expr_sum_begin(const char* name) override;
    void expr_sum_end(const char* name) override;

    void expr_proba_qualitative(Constants::kind_t, Constants::kind_t, double) override;
    void expr_proba_quantitative(Constants::kind_t) override;
    void expr_proba_compare(Constants::kind_t, Constants::kind_t) override;
    void expr_proba_expected(const char*) override;
    void expr_builtin_function1(Constants::kind_t) override;
    void expr_builtin_function2(Constants::kind_t) override;
    void expr_builtin_function3(Constants::kind_t) override;
    void expr_optimize_exp(Constants::kind_t, PRICETYPE, Constants::kind_t) override;
    void expr_save_strategy() override;
    void expr_load_strategy() override;

    void expr_simulate(int nb_of_exprs, bool filter_prop = false, int max_accepting_runs = 0) override;
    void expr_MITL_formula() override;
    void expr_MITL_until(int, int) override;
    void expr_MITL_release(int, int) override;
    void expr_MITL_disj() override;
    void expr_MITL_conj() override;
    void expr_MITL_next() override;
    void expr_MITL_atom() override;
    void expr_MITL_diamond(int, int) override;
    void expr_MITL_box(int, int) override;

    /* Dynamic process creation */
    void expr_spawn(int params) override;
    void expr_exit() override;
    void expr_numof() override;
    void expr_forall_dynamic_begin(const char*, const char*) override;
    void expr_forall_dynamic_end(const char* name) override;
    void expr_exists_dynamic_begin(const char*, const char*) override;
    void expr_exists_dynamic_end(const char*) override;
    void expr_sum_dynamic_begin(const char*, const char*) override;
    void expr_sum_dynamic_end(const char* name) override;
    void expr_foreach_dynamic_begin(const char*, const char*) override;
    void expr_foreach_dynamic_end(const char* name) override;
    void push_dynamic_frame_of(template_t* t, std::string name);  // no override
    void pop_dynamic_frame_of(std::string name);
};
}  // namespace UTAP

#endif
