// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2026 Aalborg University.

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

#include "utap/AbstractBuilder.hpp"

#include <doctest/doctest.h>

#include <string>
#include <vector>

using namespace UTAP;

namespace {
/// Concrete builder implementing only the members that AbstractBuilder itself
/// leaves pure virtual (inherited straight from ParserBuilder), so that every
/// other method exercises AbstractBuilder's own "not supported" default.
struct MinimalBuilder : AbstractBuilder
{
    void add_position(uint32_t, uint32_t, uint32_t, std::shared_ptr<std::string>) override {}
    void handle_error(const TypeException&) override {}
    void handle_warning(const TypeException&) override {}
};
}  // namespace

TEST_SUITE_BEGIN("AbstractBuilder");

TEST_CASE("Default query and no-op methods")
{
    auto b = MinimalBuilder{};
    CHECK_NOTHROW(b.set_position(0, 1));
    CHECK_FALSE(b.is_type("int"));
    CHECK_FALSE(b.is_type(""));
    CHECK_NOTHROW(b.done());
    CHECK_NOTHROW(b.handle_expect("anything"));
}

TEST_CASE("Exception carries the throwing function's name")
{
    auto b = MinimalBuilder{};
    try {
        b.type_duplicate();
        FAIL("expected NotSupportedException");
    } catch (const NotSupportedException& e) {
        CHECK(std::string{e.what()}.find("type_duplicate") != std::string::npos);
    }
}

TEST_CASE("Types")
{
    auto b = MinimalBuilder{};
    CHECK_THROWS_AS(b.type_duplicate(), NotSupportedException);
    CHECK_THROWS_AS(b.type_pop(), NotSupportedException);
    CHECK_THROWS_AS(b.type_bool(TypePrefix::NONE), NotSupportedException);
    CHECK_THROWS_AS(b.type_int(TypePrefix::NONE), NotSupportedException);
    CHECK_THROWS_AS(b.type_string(TypePrefix::NONE), NotSupportedException);
    CHECK_THROWS_AS(b.type_double(TypePrefix::NONE), NotSupportedException);
    CHECK_THROWS_AS(b.type_bounded_int(TypePrefix::NONE), NotSupportedException);
    CHECK_THROWS_AS(b.type_channel(TypePrefix::NONE), NotSupportedException);
    CHECK_THROWS_AS(b.type_clock(TypePrefix::NONE), NotSupportedException);
    CHECK_THROWS_AS(b.type_void(), NotSupportedException);
    CHECK_THROWS_AS(b.type_scalar(TypePrefix::NONE), NotSupportedException);
    CHECK_THROWS_AS(b.type_name(TypePrefix::NONE, "T"), NotSupportedException);
    CHECK_THROWS_AS(b.type_struct(TypePrefix::NONE, 0u), NotSupportedException);
    CHECK_THROWS_AS(b.type_array_of_size(0u), NotSupportedException);
    CHECK_THROWS_AS(b.type_array_of_type(0u), NotSupportedException);
    CHECK_THROWS_AS(b.struct_field("f"), NotSupportedException);
    CHECK_THROWS_AS(b.decl_typedef("T"), NotSupportedException);
}

TEST_CASE("Variable declarations")
{
    auto b = MinimalBuilder{};
    CHECK_THROWS_AS(b.decl_var("x", false), NotSupportedException);
    CHECK_THROWS_AS(b.decl_init_list(0u), NotSupportedException);
    CHECK_THROWS_AS(b.decl_field_init("f"), NotSupportedException);
}

TEST_CASE("Gantt chart declarations")
{
    auto b = MinimalBuilder{};
    CHECK_THROWS_AS(b.gantt_decl_begin("g"), NotSupportedException);
    CHECK_THROWS_AS(b.gantt_decl_select("id"), NotSupportedException);
    CHECK_THROWS_AS(b.gantt_decl_end(), NotSupportedException);
    CHECK_THROWS_AS(b.gantt_entry_begin(), NotSupportedException);
    CHECK_THROWS_AS(b.gantt_entry_select("id"), NotSupportedException);
    CHECK_THROWS_AS(b.gantt_entry_end(), NotSupportedException);
}

TEST_CASE("Progress measure declarations")
{
    auto b = MinimalBuilder{};
    CHECK_THROWS_AS(b.decl_progress(false), NotSupportedException);
}

TEST_CASE("Function declarations")
{
    auto b = MinimalBuilder{};
    CHECK_THROWS_AS(b.decl_parameter("p", false), NotSupportedException);
    CHECK_THROWS_AS(b.decl_func_begin("f"), NotSupportedException);
    CHECK_THROWS_AS(b.decl_func_end(), NotSupportedException);
    CHECK_THROWS_AS(b.dynamic_load_lib("lib"), NotSupportedException);
    CHECK_THROWS_AS(b.decl_external_func("f", "a"), NotSupportedException);
}

TEST_CASE("Process declarations")
{
    auto b = MinimalBuilder{};
    CHECK_THROWS_AS(b.proc_begin("P", true, "", ""), NotSupportedException);
    CHECK_THROWS_AS(b.proc_end(), NotSupportedException);
    CHECK_THROWS_AS(b.proc_location("L", false, false), NotSupportedException);
    CHECK_THROWS_AS(b.proc_location_commit("L"), NotSupportedException);
    CHECK_THROWS_AS(b.proc_location_urgent("L"), NotSupportedException);
    CHECK_THROWS_AS(b.proc_location_init("L"), NotSupportedException);
    CHECK_THROWS_AS(b.proc_branchpoint("B"), NotSupportedException);
    CHECK_THROWS_AS(b.proc_edge_begin("L1", "L2", true, ""), NotSupportedException);
    CHECK_THROWS_AS(b.proc_edge_end("L1", "L2"), NotSupportedException);
    CHECK_THROWS_AS(b.proc_select("id"), NotSupportedException);
    CHECK_THROWS_AS(b.proc_guard(), NotSupportedException);
    CHECK_THROWS_AS(b.proc_sync(Sync::QUE), NotSupportedException);
    CHECK_THROWS_AS(b.proc_update(), NotSupportedException);
    CHECK_THROWS_AS(b.proc_prob(), NotSupportedException);
}

TEST_CASE("Process declarations for LSC")
{
    auto b = MinimalBuilder{};
    CHECK_THROWS_AS(b.proc_instance_line(), NotSupportedException);
    CHECK_THROWS_AS(b.instance_name("I", true), NotSupportedException);
    CHECK_THROWS_AS(b.instance_name_begin("I"), NotSupportedException);
    CHECK_THROWS_AS(b.instance_name_end("I", 0u), NotSupportedException);
    CHECK_THROWS_AS(b.proc_message("A", "B", 0, false), NotSupportedException);
    CHECK_THROWS_AS(b.proc_message(Sync::QUE), NotSupportedException);
    CHECK_THROWS_AS(b.proc_condition(std::vector<std::string>{}, 0, false, false), NotSupportedException);
    CHECK_THROWS_AS(b.proc_condition(), NotSupportedException);
    CHECK_THROWS_AS(b.proc_LSC_update("a", 0, false), NotSupportedException);
    CHECK_THROWS_AS(b.proc_LSC_update(), NotSupportedException);
    CHECK_THROWS_AS(b.prechart_set(false), NotSupportedException);
}

TEST_CASE("Statements")
{
    auto b = MinimalBuilder{};
    CHECK_THROWS_AS(b.block_begin(), NotSupportedException);
    CHECK_THROWS_AS(b.block_end(), NotSupportedException);
    CHECK_THROWS_AS(b.empty_statement(), NotSupportedException);
    CHECK_THROWS_AS(b.for_begin(), NotSupportedException);
    CHECK_THROWS_AS(b.for_end(), NotSupportedException);
    CHECK_THROWS_AS(b.iteration_begin("i"), NotSupportedException);
    CHECK_THROWS_AS(b.iteration_end("i"), NotSupportedException);
    CHECK_THROWS_AS(b.while_begin(), NotSupportedException);
    CHECK_THROWS_AS(b.while_end(), NotSupportedException);
    CHECK_THROWS_AS(b.do_while_begin(), NotSupportedException);
    CHECK_THROWS_AS(b.do_while_end(), NotSupportedException);
    CHECK_THROWS_AS(b.if_begin(), NotSupportedException);
    CHECK_THROWS_AS(b.if_condition(), NotSupportedException);
    CHECK_THROWS_AS(b.if_then(), NotSupportedException);
    CHECK_THROWS_AS(b.if_end(false), NotSupportedException);
    CHECK_THROWS_AS(b.break_statement(), NotSupportedException);
    CHECK_THROWS_AS(b.continue_statement(), NotSupportedException);
    CHECK_THROWS_AS(b.switch_begin(), NotSupportedException);
    CHECK_THROWS_AS(b.switch_end(), NotSupportedException);
    CHECK_THROWS_AS(b.case_begin(), NotSupportedException);
    CHECK_THROWS_AS(b.case_end(), NotSupportedException);
    CHECK_THROWS_AS(b.default_begin(), NotSupportedException);
    CHECK_THROWS_AS(b.default_end(), NotSupportedException);
    CHECK_THROWS_AS(b.expr_statement(), NotSupportedException);
    CHECK_THROWS_AS(b.return_statement(false), NotSupportedException);
    CHECK_THROWS_AS(b.assert_statement(), NotSupportedException);
}

TEST_CASE("Expressions")
{
    auto b = MinimalBuilder{};
    CHECK_THROWS_AS(b.expr_true(), NotSupportedException);
    CHECK_THROWS_AS(b.expr_false(), NotSupportedException);
    CHECK_THROWS_AS(b.expr_double(0.0), NotSupportedException);
    CHECK_THROWS_AS(b.expr_string("s"), NotSupportedException);
    CHECK_THROWS_AS(b.expr_location(), NotSupportedException);
    CHECK_THROWS_AS(b.expr_identifier("x"), NotSupportedException);
    CHECK_THROWS_AS(b.expr_nat(0), NotSupportedException);
    CHECK_THROWS_AS(b.expr_call_begin(), NotSupportedException);
    CHECK_THROWS_AS(b.expr_call_end(0u), NotSupportedException);
    CHECK_THROWS_AS(b.expr_array(), NotSupportedException);
    CHECK_THROWS_AS(b.expr_post_increment(), NotSupportedException);
    CHECK_THROWS_AS(b.expr_pre_increment(), NotSupportedException);
    CHECK_THROWS_AS(b.expr_post_decrement(), NotSupportedException);
    CHECK_THROWS_AS(b.expr_pre_decrement(), NotSupportedException);
    CHECK_THROWS_AS(b.expr_assignment(Kind::ASSIGN), NotSupportedException);
    CHECK_THROWS_AS(b.expr_unary(Kind::NOT), NotSupportedException);
    CHECK_THROWS_AS(b.expr_binary(Kind::PLUS), NotSupportedException);
    CHECK_THROWS_AS(b.expr_nary(Kind::LIST, 0u), NotSupportedException);
    CHECK_THROWS_AS(b.expr_scenario("S"), NotSupportedException);
    CHECK_THROWS_AS(b.expr_ternary(Kind::INLINE_IF, false), NotSupportedException);
    CHECK_THROWS_AS(b.expr_inline_if(), NotSupportedException);
    CHECK_THROWS_AS(b.expr_comma(), NotSupportedException);
    CHECK_THROWS_AS(b.expr_dot("f"), NotSupportedException);
    CHECK_THROWS_AS(b.expr_deadlock(), NotSupportedException);
    CHECK_THROWS_AS(b.expr_forall_begin("i"), NotSupportedException);
    CHECK_THROWS_AS(b.expr_forall_end("i"), NotSupportedException);
    CHECK_THROWS_AS(b.expr_exists_begin("i"), NotSupportedException);
    CHECK_THROWS_AS(b.expr_exists_end("i"), NotSupportedException);
    CHECK_THROWS_AS(b.expr_sum_begin("i"), NotSupportedException);
    CHECK_THROWS_AS(b.expr_sum_end("i"), NotSupportedException);
}

TEST_CASE("SMC and learning extensions")
{
    auto b = MinimalBuilder{};
    CHECK_THROWS_AS(b.expr_proba_qualitative(Kind::PROBA_BOX, Kind::LE, 0.5), NotSupportedException);
    CHECK_THROWS_AS(b.expr_proba_quantitative(Kind::PROBA_CMP), NotSupportedException);
    CHECK_THROWS_AS(b.expr_proba_compare(Kind::PROBA_BOX, Kind::PROBA_DIAMOND), NotSupportedException);
    CHECK_THROWS_AS(b.expr_proba_expected("x"), NotSupportedException);
    CHECK_THROWS_AS(b.expr_simulate(1, false, 0), NotSupportedException);
    CHECK_THROWS_AS(b.expr_builtin_function1(Kind::SQRT_F), NotSupportedException);
    CHECK_THROWS_AS(b.expr_builtin_function2(Kind::POW_F), NotSupportedException);
    CHECK_THROWS_AS(b.expr_builtin_function3(Kind::FMA_F), NotSupportedException);
    CHECK_THROWS_AS(b.expr_optimize_exp(Kind::MIN_EXP, PriceType::TIME, Kind::LE), NotSupportedException);
    CHECK_THROWS_AS(b.expr_load_strategy(), NotSupportedException);
    CHECK_THROWS_AS(b.expr_save_strategy("strat"), NotSupportedException);
}

TEST_CASE("MITL extensions")
{
    auto b = MinimalBuilder{};
    CHECK_THROWS_AS(b.expr_MITL_formula(), NotSupportedException);
    CHECK_THROWS_AS(b.expr_MITL_until(0, 1), NotSupportedException);
    CHECK_THROWS_AS(b.expr_MITL_release(0, 1), NotSupportedException);
    CHECK_THROWS_AS(b.expr_MITL_disj(), NotSupportedException);
    CHECK_THROWS_AS(b.expr_MITL_conj(), NotSupportedException);
    CHECK_THROWS_AS(b.expr_MITL_next(), NotSupportedException);
    CHECK_THROWS_AS(b.expr_MITL_atom(), NotSupportedException);
    CHECK_THROWS_AS(b.expr_MITL_diamond(0, 1), NotSupportedException);
    CHECK_THROWS_AS(b.expr_MITL_box(0, 1), NotSupportedException);
    CHECK_THROWS_AS(b.expr_optimize(0, 0, 0, 0), NotSupportedException);
}

TEST_CASE("System declaration")
{
    auto b = MinimalBuilder{};
    CHECK_THROWS_AS(b.instantiation_begin("P", 0u, "T"), NotSupportedException);
    CHECK_THROWS_AS(b.instantiation_end("P", 0u, "T", 0u), NotSupportedException);
    CHECK_THROWS_AS(b.process("P"), NotSupportedException);
    CHECK_THROWS_AS(b.process_list_end(), NotSupportedException);
}

TEST_CASE("Properties")
{
    auto b = MinimalBuilder{};
    CHECK_THROWS_AS(b.property(), NotSupportedException);
    CHECK_THROWS_AS(b.scenario("S"), NotSupportedException);
    CHECK_THROWS_AS(b.parse(""), NotSupportedException);
    CHECK_THROWS_AS(b.strategy_declaration("strat"), NotSupportedException);
    CHECK_THROWS_AS(b.subjection("s"), NotSupportedException);
    CHECK_THROWS_AS(b.imitation("s"), NotSupportedException);
}

TEST_CASE("Guiding")
{
    auto b = MinimalBuilder{};
    CHECK_THROWS_AS(b.before_update(), NotSupportedException);
    CHECK_THROWS_AS(b.after_update(), NotSupportedException);
}

TEST_CASE("Priority")
{
    auto b = MinimalBuilder{};
    CHECK_THROWS_AS(b.chan_priority_begin(), NotSupportedException);
    CHECK_THROWS_AS(b.chan_priority_add('<'), NotSupportedException);
    CHECK_THROWS_AS(b.chan_priority_default(), NotSupportedException);
    CHECK_THROWS_AS(b.proc_priority_inc(), NotSupportedException);
    CHECK_THROWS_AS(b.proc_priority("P"), NotSupportedException);
}

TEST_CASE("Dynamic templates")
{
    auto b = MinimalBuilder{};
    CHECK_THROWS_AS(b.decl_dynamic_template("T"), NotSupportedException);
    CHECK_THROWS_AS(b.expr_spawn(0), NotSupportedException);
    CHECK_THROWS_AS(b.expr_exit(), NotSupportedException);
    CHECK_THROWS_AS(b.expr_numof(), NotSupportedException);
    CHECK_THROWS_AS(b.expr_forall_dynamic_begin("i", "T"), NotSupportedException);
    CHECK_THROWS_AS(b.expr_forall_dynamic_end("i"), NotSupportedException);
    CHECK_THROWS_AS(b.expr_exists_dynamic_begin("i", "T"), NotSupportedException);
    CHECK_THROWS_AS(b.expr_exists_dynamic_end("i"), NotSupportedException);
    CHECK_THROWS_AS(b.expr_sum_dynamic_begin("i", "T"), NotSupportedException);
    CHECK_THROWS_AS(b.expr_sum_dynamic_end("i"), NotSupportedException);
    CHECK_THROWS_AS(b.expr_foreach_dynamic_begin("i", "T"), NotSupportedException);
    CHECK_THROWS_AS(b.expr_foreach_dynamic_end("i"), NotSupportedException);
    CHECK_THROWS_AS(b.expr_dynamic_process_expr("P"), NotSupportedException);
    CHECK_THROWS_AS(b.expr_MITL_forall_dynamic_begin("i", "T"), NotSupportedException);
    CHECK_THROWS_AS(b.expr_MITL_forall_dynamic_end("i"), NotSupportedException);
    CHECK_THROWS_AS(b.expr_MITL_exists_dynamic_begin("i", "T"), NotSupportedException);
    CHECK_THROWS_AS(b.expr_MITL_exists_dynamic_end("i"), NotSupportedException);
}

TEST_CASE("Verification queries")
{
    auto b = MinimalBuilder{};
    CHECK_THROWS_AS(b.model_option("k", "v"), NotSupportedException);
    CHECK_THROWS_AS(b.query_begin(), NotSupportedException);
    CHECK_THROWS_AS(b.query_formula("A[] true", ""), NotSupportedException);
    CHECK_THROWS_AS(b.query_comment("c"), NotSupportedException);
    CHECK_THROWS_AS(b.query_options("o", ""), NotSupportedException);
    CHECK_THROWS_AS(b.expectation_begin(), NotSupportedException);
    CHECK_THROWS_AS(b.expectation_end(), NotSupportedException);
    CHECK_THROWS_AS(b.expectation_value("r", "t", "v"), NotSupportedException);
    CHECK_THROWS_AS(b.expect_resource("t", "v", "u"), NotSupportedException);
    CHECK_THROWS_AS(b.query_results_begin(), NotSupportedException);
    CHECK_THROWS_AS(b.query_results_end(), NotSupportedException);
    CHECK_THROWS_AS(b.query_end(), NotSupportedException);
}

TEST_SUITE_END();
