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

        void add_position(uint32_t position, uint32_t offset, uint32_t line, const std::string& path) override;

        void handle_error(const TypeException&) override;
        void handle_warning(const TypeException&) override;

        bool is_type(const char*) override;
        void type_bool(PREFIX) override;
        void type_int(PREFIX) override;
        void type_string(PREFIX) override;
        void type_double(PREFIX) override;
        void type_bounded_int(PREFIX) override;
        void type_channel(PREFIX) override;
        void type_clock(PREFIX) override;
        void type_void() override;
        void type_scalar(PREFIX) override;
        void type_name(PREFIX, const char* type) override;
        void type_pop() override;
        void type_duplicate() override;
        void type_array_of_size(size_t n) override;
        void type_array_of_type(size_t n) override;
        void type_struct(PREFIX prefix, uint32_t n) override;
        void struct_field(const char* name) override;
        void decl_typedef(const char* name) override;
        void decl_var(const char* id, bool init) override;
        void decl_init_list(uint32_t num) override;
        void decl_field_init(const char* name) override;
        void decl_parameter(const char* name, bool) override;
        void decl_func_begin(const char* name) override;
        void decl_func_end() override;
        void dynamic_load_lib(const char* name) override;
        void decl_external_func(const char* name, const char* alias) override;
        void block_begin() override;
        void block_end() override;
        void empty_statement() override;
        void for_begin() override;
        void for_end() override;
        void iteration_begin(const char* name) override;  // 1 id, 1 type
        void iteration_end(const char* name) override;    // 1 stat
        void while_begin() override;
        void while_end() override;
        void do_while_begin() override;
        void do_while_end() override;
        void if_begin() override;
        void if_condition() override;
        void if_then() override;
        void if_end(bool) override;
        void break_statement() override;
        void continue_statement() override;
        void expr_statement() override;
        void return_statement(bool hasValue) override;
        void proc_begin(const char* name, const bool isTA = true, const std::string& type = "",
                        const std::string& mode = "") override;
        void proc_location(const char* id, bool hasInvariant, bool hasExpRate) override;
        void proc_branchpoint(const char* id) override;
        void proc_location_urgent(const char* id) override;
        void proc_location_commit(const char* id) override;
        void proc_location_init(const char* id) override;
        void proc_select(const char* id) override;
        void proc_guard() override;
        void proc_sync(Constants::synchronisation_t type) override;
        void proc_update() override;
        void proc_edge_begin(const char* source, const char* target, const bool control);
        void proc_edge_begin(const char* source, const char* target, const bool control, const char* actname) override;
        void proc_edge_end(const char* source, const char* target) override;
        void proc_end() override;
        void expr_identifier(const char* id) override;
        void expr_location() override;
        void expr_nat(int32_t n) override;
        void expr_true() override;
        void expr_false() override;
        void expr_double(double) override;
        void expr_string(const char*) override;
        void expr_call_begin() override;
        void expr_call_end(uint32_t n) override;
        void expr_array() override;
        void expr_post_increment() override;
        void expr_pre_increment() override;
        void expr_post_decrement() override;
        void expr_pre_decrement() override;
        void expr_assignment(Constants::kind_t op) override;
        void expr_unary(Constants::kind_t op) override;
        void expr_binary(Constants::kind_t op) override;
        void expr_nary(Constants::kind_t op, uint32_t num) override;
        void expr_scenario(const char* name) override;
        void expr_ternary(Constants::kind_t op, bool firstMissing) override;
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
        void expr_proba_quantitative(Constants::kind_t) override;
        void expr_MITL_diamond(int, int) override;
        void expr_MITL_box(int, int) override;
        void expr_simulate(int no_of_expr, bool filter_prop, int max_accept_runs) override;
        void expr_builtin_function1(Constants::kind_t kind) override;
        void expr_builtin_function2(Constants::kind_t kind) override;
        void expr_builtin_function3(Constants::kind_t kind) override;
        void before_update() override;
        void after_update() override;
        void instantiation_begin(const char*, size_t, const char*) override;
        void instantiation_end(const char*, size_t, const char*, size_t) override;
        void process(const char* id) override;
        void process_list_end() override;
        void done() override;

        /** Verification queries */
        void query_begin() override;
        void query_formula(const char* formula, const char* location) override;
        void query_comment(const char* comment) override;
        void query_end() override;
    };
}  // namespace UTAP

#endif
