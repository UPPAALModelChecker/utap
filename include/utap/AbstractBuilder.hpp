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

namespace UTAP {
class NotSupportedException : public std::exception
{
private:
    std::string error;

public:
    NotSupportedException(const std::string& fun) { error = fun + " is not supported"; }
    const char* what() const noexcept override { return error.c_str(); }
};

class AbstractBuilder : public ParserBuilder
{
protected:
    position_t position;

public:
    AbstractBuilder() = default;

    void set_position(uint32_t, uint32_t) override;

    /************************************************************
     * Query functions
     */
    bool is_type(const char*) override;

    /************************************************************
     * Types
     */
    void type_duplicate() override;
    void type_pop() override;
    void type_bool(PREFIX) override;
    void type_int(PREFIX) override;
    void type_string(PREFIX) override;
    void type_double(PREFIX) override;
    void type_bounded_int(PREFIX) override;
    void type_channel(PREFIX) override;
    void type_clock(PREFIX) override;
    void type_void() override;
    void type_scalar(PREFIX) override;
    void type_name(PREFIX, const char* name) override;
    void type_struct(PREFIX, uint32_t fields) override;
    void type_array_of_size(size_t) override;
    void type_array_of_type(size_t) override;
    void struct_field(const char* name) override;
    void decl_typedef(const char* name) override;

    /************************************************************
     * Variable declarations
     */
    void decl_var(const char* name, bool init) override;
    void decl_init_list(uint32_t num) override;       // n initialisers
    void decl_field_init(const char* name) override;  // 1 initialiser

    /********************************************************************
     * Gantt chart declaration
     */
    void gantt_decl_begin(const char* name) override;
    void gantt_decl_select(const char* id) override;
    void gantt_decl_end() override;
    void gantt_entry_begin() override;
    void gantt_entry_select(const char* id) override;
    void gantt_entry_end() override;

    /************************************************************
     * Progress measure declarations
     */
    void decl_progress(bool) override;

    /************************************************************
     * Function declarations
     */
    void decl_parameter(const char* name, bool) override;
    void decl_func_begin(const char* name) override;  // n paramaters
    void decl_func_end() override;                    // 1 block
    void dynamic_load_lib(const char* name) override;
    void decl_external_func(const char* name, const char* alias) override;

    /************************************************************
     * Process declarations
     */
    void proc_begin(const char* name, const bool isTA = true, const std::string& type = "",
                    const std::string& mode = "") override;
    void proc_end() override;                                                      // 1 ProcBody
    void proc_location(const char* name, bool hasInvariant, bool hasER) override;  // 1 expr
    void proc_location_commit(const char* name) override;                          // mark previously decl. state
    void proc_location_urgent(const char* name) override;                          // mark previously decl. state
    void proc_location_init(const char* name) override;                            // mark previously decl. state
    void proc_branchpoint(const char* name) override;
    void proc_edge_begin(const char* from, const char* to, const bool control, const char* actname) override;
    void proc_edge_end(const char* from, const char* to) override;
    // 1 epxr,1sync,1expr
    void proc_select(const char* id) override;
    void proc_guard() override;
    void proc_sync(Constants::synchronisation_t type) override;  // 1 expr
    void proc_update() override;
    void proc_prob() override;
    /************************************************************
     * Process declarations for LSC
     */
    void proc_instance_line() override;
    void instance_name(const char* name, bool templ = true) override;
    void instance_name_begin(const char* name) override;
    void instance_name_end(const char* name, size_t arguments) override;
    void proc_message(const char* from, const char* to, const int loc, const bool pch) override;
    void proc_message(Constants::synchronisation_t type) override;  // 1 expr
    void proc_condition(const std::vector<std::string>& anchors, const int loc, const bool pch,
                        const bool hot) override;
    void proc_condition() override;  // Label
    void proc_LSC_update(const char* anchor, const int loc, const bool pch) override;
    void proc_LSC_update() override;  // Label
    void prechart_set(const bool pch) override;

    /************************************************************
     * Statements
     */
    void block_begin() override;
    void block_end() override;
    void empty_statement() override;
    void for_begin() override;                        // 3 expr
    void for_end() override;                          // 1 stat
    void iteration_begin(const char* name) override;  // 1 id, 1 type
    void iteration_end(const char* name) override;    // 1 stat
    void while_begin() override;
    void while_end() override;  // 1 expr, 1 stat
    void do_while_begin() override;
    void do_while_end() override;  // 1 stat, 1 expr
    void if_begin() override;
    void if_condition() override;  // 1 expr
    void if_then() override;       // 1 statement
    void if_end(bool) override;    // 1 expr, 1 or 2 statements
    void break_statement() override;
    void continue_statement() override;
    void switch_begin() override;
    void switch_end() override;  // 1 expr, 1+ case/default
    void case_begin() override;
    void case_end() override;  // 1 expr, 0+ stat
    void default_begin() override;
    void default_end() override;           // 0+ statements
    void expr_statement() override;        // 1 expr
    void return_statement(bool) override;  // 1 expr if argument is true
    void assert_statement() override;

    /************************************************************
     * Expressions
     */
    void expr_true() override;
    void expr_false() override;
    void expr_double(double) override;
    void expr_string(const char*) override;
    void expr_location(const char* name) override;
    void expr_location() override;
    void expr_identifier(const char* varName) override;
    void expr_nat(int32_t) override;  // natural number
    void expr_call_begin() override;
    void expr_call_end(uint32_t n) override;                // n exprs as arguments
    void expr_array() override;                             // 2 expr
    void expr_post_increment() override;                    // 1 expr
    void expr_pre_increment() override;                     // 1 expr
    void expr_post_decrement() override;                    // 1 expr
    void expr_pre_decrement() override;                     // 1 expr
    void expr_assignment(Constants::kind_t op) override;    // 2 expr
    void expr_unary(Constants::kind_t unaryop) override;    // 1 expr
    void expr_binary(Constants::kind_t binaryop) override;  // 2 expr
    void expr_nary(Constants::kind_t, uint32_t num) override;
    void expr_scenario(const char* name) override;
    void expr_ternary(Constants::kind_t ternaryop, bool firstMissing) override;  // 3 expr
    void expr_inline_if() override;                                              // 3 expr
    void expr_comma() override;                                                  // 2 expr
    void expr_dot(const char*) override;                                         // 1 expr
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
    void expr_proba_expected(const char* identifier) override;
    void expr_simulate(int no_of_exprs, bool = false, int = 0) override;
    void expr_builtin_function1(Constants::kind_t) override;
    void expr_builtin_function2(Constants::kind_t) override;
    void expr_builtin_function3(Constants::kind_t) override;
    void expr_optimize_exp(Constants::kind_t, PRICETYPE, Constants::kind_t) override;
    void expr_load_strategy() override;
    void expr_save_strategy(const char* strategy_name) override;

    // MITL
    void expr_MITL_formula() override;
    void expr_MITL_until(int, int) override;
    void expr_MITL_release(int, int) override;
    void expr_MITL_disj() override;
    void expr_MITL_conj() override;
    void expr_MITL_next() override;
    void expr_MITL_atom() override;
    void expr_optimize(int, int, int, int) override;

    /************************************************************
     * System declaration
     */
    void instantiation_begin(const char*, size_t, const char*) override;
    void instantiation_end(const char*, size_t, const char*, size_t) override;
    void process(const char*) override;
    void process_list_end() override;
    void done() override;

    void handle_expect(const char* text) override;

    /************************************************************
     * Properties
     */
    void property() override;
    void scenario(const char*) override;              // LSC
    void parse(const char*) override;                 // LSC
    void strategy_declaration(const char*) override;  // tiga-smc
    void subjection(const char*) override;
    void imitation(const char*) override;

    /********************************************************************
     * Guiding
     */
    void before_update() override;
    void after_update() override;

    /********************************************************************
     * Priority
     */
    void chan_priority_begin() override;
    void chan_priority_add(char separator) override;
    void chan_priority_default() override;
    void proc_priority_inc() override;
    void proc_priority(const std::string&) override;

    void decl_dynamic_template(const std::string& name) override;
    void expr_spawn(int) override;
    void expr_exit() override;
    void expr_numof() override;

    void expr_forall_dynamic_begin(const char*, const char*) override;
    void expr_forall_dynamic_end(const char* name) override;
    void expr_exists_dynamic_begin(const char*, const char*) override;
    void expr_exists_dynamic_end(const char* name) override;
    void expr_sum_dynamic_begin(const char*, const char*) override;
    void expr_sum_dynamic_end(const char*) override;
    void expr_foreach_dynamic_begin(const char*, const char*) override;
    void expr_foreach_dynamic_end(const char* name) override;
    void expr_dynamic_process_expr(const char*) override;
    void expr_MITL_forall_dynamic_begin(const char*, const char*) override;
    void expr_MITL_forall_dynamic_end(const char* name) override;
    void expr_MITL_exists_dynamic_begin(const char*, const char*) override;
    void expr_MITL_exists_dynamic_end(const char* name) override;

    void expr_enforce() override;
    void expr_discrete_interval() override;
    void expr_interval(int32_t divisions) override;

    /** Verification queries */
    void model_option(const char* key, const char* value) override;
    void query_begin() override;
    void query_formula(const char* formula, const char* location) override;
    void query_comment(const char* comment) override;
    void query_options(const char* options, const char*) override;
    void expectation_begin() override;
    void expectation_end() override;
    void expectation_value(const char* res, const char* type, const char* value) override;
    void expect_resource(const char* type, const char* value, const char* unit) override;
    void query_results_begin() override;
    void query_results_end() override;
    void query_end() override;
};
}  // namespace UTAP
#endif
