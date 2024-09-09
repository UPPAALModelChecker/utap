// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2020-2022 Aalborg University.

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

#include "utap/expression.h"
#include "utap/statement.h"

#include <doctest/doctest.h>

TEST_CASE("Expression")
{
    using UTAP::type_t;
    using exp_t = UTAP::expression_t;
    const auto i_prim_type = type_t::create_primitive(UTAP::Constants::INT);
    REQUIRE(i_prim_type.get_kind() == UTAP::Constants::INT);
    const auto d_prim_type = type_t::create_primitive(UTAP::Constants::DOUBLE);
    REQUIRE(d_prim_type.get_kind() == UTAP::Constants::DOUBLE);

    const auto i0 = exp_t::create_constant(0);
    REQUIRE(i0.get_kind() == UTAP::Constants::CONSTANT);
    const auto i2 = exp_t::create_constant(2);
    REQUIRE(i2.get_kind() == UTAP::Constants::CONSTANT);
    CHECK(i2.get_type().get_kind() == UTAP::Constants::INT);
    CHECK(i2.get_value() == 2);
    const auto i5 = exp_t::create_constant(5);
    REQUIRE(i5.get_kind() == UTAP::Constants::CONSTANT);
    CHECK(i5.get_type().get_kind() == UTAP::Constants::INT);
    CHECK(i5.get_value() == 5);
    const auto d3 = exp_t::create_double(3.0);
    REQUIRE(d3.get_kind() == UTAP::Constants::CONSTANT);
    CHECK(d3.get_type().get_kind() == UTAP::Constants::DOUBLE);
    CHECK(d3.get_double_value() == 3.0);
    const auto d1_2 = exp_t::create_double(0.5);
    REQUIRE(d1_2.get_kind() == UTAP::Constants::CONSTANT);
    CHECK(d1_2.get_type().get_kind() == UTAP::Constants::DOUBLE);
    CHECK(d1_2.get_double_value() == 0.5);

    SUBCASE("Types")
    {
        const auto i02 = type_t::create_range(i_prim_type, i0, i2);
        REQUIRE(i02.get_kind() == UTAP::Constants::RANGE);
        const auto i02_range = i02.get_range();
        CHECK(i02_range.first == i0);
        CHECK(i02_range.second == i2);
        const auto i25 = type_t::create_range(i_prim_type, i2, i5);
        REQUIRE(i25.get_kind() == UTAP::Constants::RANGE);
        const auto i25_range = i25.get_range();
        CHECK(i25_range.first == i2);
        CHECK(i25_range.second == i5);
        const auto i52 = type_t::create_range(i_prim_type, i5, i2);  // no checks
    }

    SUBCASE("Operator precedence")
    {
        using namespace UTAP::Constants;
        // Follow table at https://en.cppreference.com/w/cpp/language/operator_precedence
        REQUIRE(exp_t::get_precedence(POST_INCREMENT) == exp_t::get_precedence(POST_DECREMENT));
        REQUIRE(exp_t::get_precedence(POST_INCREMENT) >= exp_t::get_precedence(FUN_CALL));
        REQUIRE(exp_t::get_precedence(FUN_CALL) == exp_t::get_precedence(FUN_CALL_EXT));
        REQUIRE(exp_t::get_precedence(FUN_CALL) >= exp_t::get_precedence(SUBSCRIPT));
        REQUIRE(exp_t::get_precedence(SUBSCRIPT) >= exp_t::get_precedence(DOT));
        REQUIRE(exp_t::get_precedence(SUBSCRIPT) > exp_t::get_precedence(NOT));
        REQUIRE(exp_t::get_precedence(DOT) >= exp_t::get_precedence(RATE));
        REQUIRE(exp_t::get_precedence(PRE_INCREMENT) == exp_t::get_precedence(NOT));
        REQUIRE(exp_t::get_precedence(PRE_INCREMENT) == exp_t::get_precedence(PRE_DECREMENT));
        REQUIRE(exp_t::get_precedence(PRE_INCREMENT) >= exp_t::get_precedence(UNARY_MINUS));
        REQUIRE(exp_t::get_precedence(UNARY_MINUS) >= exp_t::get_precedence(NOT));
        REQUIRE(exp_t::get_precedence(NOT) > exp_t::get_precedence(POW));
        REQUIRE(exp_t::get_precedence(POW) > exp_t::get_precedence(MULT));
        REQUIRE(exp_t::get_precedence(MULT) == exp_t::get_precedence(DIV));
        REQUIRE(exp_t::get_precedence(MULT) == exp_t::get_precedence(MOD));
        REQUIRE(exp_t::get_precedence(MULT) > exp_t::get_precedence(PLUS));
        REQUIRE(exp_t::get_precedence(PLUS) == exp_t::get_precedence(MINUS));
        REQUIRE(exp_t::get_precedence(PLUS) > exp_t::get_precedence(BIT_LSHIFT));
        REQUIRE(exp_t::get_precedence(BIT_LSHIFT) == exp_t::get_precedence(BIT_RSHIFT));
        REQUIRE(exp_t::get_precedence(BIT_LSHIFT) > exp_t::get_precedence(LT));
        REQUIRE(exp_t::get_precedence(LT) == exp_t::get_precedence(LE));
        REQUIRE(exp_t::get_precedence(LT) == exp_t::get_precedence(GT));
        REQUIRE(exp_t::get_precedence(LT) == exp_t::get_precedence(GE));
        REQUIRE(exp_t::get_precedence(LT) > exp_t::get_precedence(EQ));
        REQUIRE(exp_t::get_precedence(EQ) == exp_t::get_precedence(NEQ));
        REQUIRE(exp_t::get_precedence(NEQ) > exp_t::get_precedence(BIT_AND));
        REQUIRE(exp_t::get_precedence(BIT_AND) > exp_t::get_precedence(BIT_XOR));
        REQUIRE(exp_t::get_precedence(BIT_XOR) > exp_t::get_precedence(BIT_OR));
        REQUIRE(exp_t::get_precedence(BIT_OR) > exp_t::get_precedence(AND));
        REQUIRE(exp_t::get_precedence(AND) > exp_t::get_precedence(OR));
        REQUIRE(exp_t::get_precedence(AND) > exp_t::get_precedence(ASSIGN));
        REQUIRE(exp_t::get_precedence(ASSIGN) == exp_t::get_precedence(ASS_PLUS));
        REQUIRE(exp_t::get_precedence(ASSIGN) == exp_t::get_precedence(ASS_MINUS));
        REQUIRE(exp_t::get_precedence(ASSIGN) == exp_t::get_precedence(ASS_MULT));
        REQUIRE(exp_t::get_precedence(ASSIGN) == exp_t::get_precedence(ASS_DIV));
        REQUIRE(exp_t::get_precedence(ASSIGN) == exp_t::get_precedence(ASS_MOD));
        REQUIRE(exp_t::get_precedence(ASSIGN) == exp_t::get_precedence(ASS_LSHIFT));
        REQUIRE(exp_t::get_precedence(ASSIGN) == exp_t::get_precedence(ASS_RSHIFT));
        REQUIRE(exp_t::get_precedence(ASSIGN) == exp_t::get_precedence(ASS_AND));
        REQUIRE(exp_t::get_precedence(ASSIGN) == exp_t::get_precedence(ASS_OR));
        REQUIRE(exp_t::get_precedence(ASSIGN) == exp_t::get_precedence(ASS_XOR));
        REQUIRE(exp_t::get_precedence(ASSIGN) > exp_t::get_precedence(COMMA));
    }

    SUBCASE("Unary")
    {
        using namespace UTAP::Constants;
        const auto ops = {// clang-format off
            UNARY_MINUS, NOT, DOT, /*SYNC,*/ PRE_INCREMENT, POST_INCREMENT, PRE_DECREMENT, POST_DECREMENT,
            RATE, ABS_F, FABS_F, EXP_F, EXP2_F, EXPM1_F, LN_F, LOG_F, LOG10_F, LOG2_F, LOG1P_F, SQRT_F,
            CBRT_F, SIN_F, COS_F, TAN_F, ASIN_F, ACOS_F, ATAN_F, SINH_F, COSH_F, TANH_F, ASINH_F,
            ACOSH_F, ATANH_F, ERF_F, ERFC_F, TGAMMA_F, LGAMMA_F, CEIL_F, FLOOR_F, TRUNC_F, ROUND_F,
            FINT_F, ILOGB_F, LOGB_F, FP_CLASSIFY_F, IS_FINITE_F, IS_INF_F, IS_NAN_F, IS_NORMAL_F,
            SIGNBIT_F, IS_UNORDERED_F, RANDOM_F, RANDOM_POISSON_F
        };  // clang-format on
        for (const auto& op : ops) {
            REQUIRE(exp_t::get_precedence(op) > 0);
            const auto op_i0 = exp_t::create_unary(op, i0);
            CHECK(op_i0.get_kind() == op);
            REQUIRE(op_i0.get_size() == 1);
            CHECK(op_i0.get(0) == i0);
            const auto op_i2 = exp_t::create_unary(op, i2);
            CHECK(op_i2.get_kind() == op);
            REQUIRE(op_i2.get_size() == 1);
            CHECK(op_i2.get(0) == i2);
            const auto op_d3 = exp_t::create_unary(op, d3);
            CHECK(op_d3.get_kind() == op);
            REQUIRE(op_d3.get_size() == 1);
            CHECK(op_d3.get(0) == d3);
            const auto op_d1_2 = exp_t::create_unary(op, d1_2);
            CHECK(op_d1_2.get_kind() == op);
            REQUIRE(op_d1_2.get_size() == 1);
            CHECK(op_d1_2.get(0) == d1_2);
        }
    }
    SUBCASE("Binary")
    {
        using namespace UTAP::Constants;
        const auto ops = {
            // clang-format off
            MINUS, PLUS, MULT, DIV, MOD, BIT_AND, BIT_OR, BIT_XOR, BIT_LSHIFT, BIT_RSHIFT,
            AND, OR, XOR, POW, LT, LE, EQ, NEQ, GE, GT, MIN, MAX, SUBSCRIPT, COMMA,
            ASSIGN, ASS_PLUS, ASS_MINUS, ASS_DIV, ASS_MOD, ASS_MULT, ASS_AND, ASS_OR, ASS_XOR,
            ASS_LSHIFT, ASS_RSHIFT, FORALL, EXISTS, SUM, SUP_VAR, INF_VAR, BOUNDS_VAR, FRACTION,
            FMOD_F, FMAX_F, FMIN_F, FDIM_F, POW_F, HYPOT_F, ATAN2_F, LDEXP_F, NEXT_AFTER_F, COPY_SIGN_F,
            RANDOM_ARCSINE_F, RANDOM_BETA_F, RANDOM_GAMMA_F, RANDOM_NORMAL_F, RANDOM_WEIBULL_F,
        };  // clang-format on
        for (const auto& op : ops) {
            REQUIRE(exp_t::get_precedence(op) > 0);
            const auto op_i25 = exp_t::create_binary(op, i2, i5);
            CHECK(op_i25.get_kind() == op);
            REQUIRE(op_i25.get_size() == 2);
            CHECK(op_i25.get(0) == i2);
            CHECK(op_i25.get(1) == i5);
            const auto op_d3_2 = exp_t::create_binary(op, d3, d1_2);
            CHECK(op_d3_2.get_kind() == op);
            REQUIRE(op_d3_2.get_size() == 2);
            CHECK(op_d3_2.get(0) == d3);
            CHECK(op_d3_2.get(1) == d1_2);
        }
    }
}

TEST_CASE("Expression to string conversion")
{
    using exp_t = UTAP::expression_t;
    const auto i2 = exp_t::create_constant(2);
    const auto i3 = exp_t::create_constant(3);
    const auto i5 = exp_t::create_constant(5);
    const auto i7 = exp_t::create_constant(7);
    SUBCASE("Addition and multiplication")
    {
        const auto add1 = exp_t::create_binary(UTAP::Constants::PLUS, i2, i3);
        CHECK(add1.str() == "2 + 3");
        const auto add2 = exp_t::create_binary(UTAP::Constants::PLUS, i5, i7);
        CHECK(add2.str() == "5 + 7");
        const auto mult = exp_t::create_binary(UTAP::Constants::MULT, add1, add2);
        CHECK(mult.str() == "(2 + 3) * (5 + 7)");
    }
    SUBCASE("Multiplication and power")
    {
        const auto m1 = exp_t::create_binary(UTAP::Constants::MULT, i2, i3);
        CHECK(m1.str() == "2 * 3");
        const auto m2 = exp_t::create_binary(UTAP::Constants::MULT, i5, i7);
        CHECK(m2.str() == "5 * 7");
        const auto p = exp_t::create_binary(UTAP::Constants::POW, m1, m2);
        CHECK(p.str() == "(2 * 3) ** (5 * 7)");
    }
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& s)
{
    os << '{';
    auto it = s.begin();
    if (it != s.end()) {
        os << *it;
        while (++it != s.end())
            os << ',' << *it;
    }
    return os << '}';
}

TEST_CASE("Expression dependencies and effects")
{
    using namespace UTAP;
    // Analyse a small program:
    // int i;
    // int j;
    // int a[int[0,2]];
    // if (j == 0)
    //     i = 0;
    // j = i;
    // a[2] = 2;
    auto exp_0 = UTAP::expression_t::create_constant(0);
    CHECK(exp_0.str() == "0");
    auto exp_2 = UTAP::expression_t::create_constant(2);
    CHECK(exp_2.str() == "2");
    auto global = frame_t::create();
    auto type_int = type_t::create_primitive(Constants::INT);
    auto type_int_0_2 = type_t::create_range(type_int, exp_0, exp_2);
    auto type_arr = type_t::create_array(type_int, type_int_0_2);
    auto symb_i = global.add_symbol("i", type_int);
    auto symb_j = global.add_symbol("j", type_int);
    auto symb_k = global.add_symbol("k", type_int);
    auto symb_a = global.add_symbol("a", type_arr);
    auto exp_i = expression_t::create_identifier(symb_i);
    CHECK(exp_i.str() == "i");
    auto exp_j = expression_t::create_identifier(symb_j);
    CHECK(exp_j.str() == "j");
    auto exp_k = expression_t::create_identifier(symb_k);
    CHECK(exp_k.str() == "k");
    auto exp_a = expression_t::create_identifier(symb_a);
    CHECK(exp_a.str() == "a");
    auto eq_j_0 = expression_t::create_binary(Constants::EQ, exp_j, exp_0);
    CHECK(eq_j_0.str() == "j == 0");
    auto ass_i_0 = expression_t::create_binary(Constants::ASSIGN, exp_i, exp_0);
    CHECK(ass_i_0.str() == "i = 0");
    auto ass_j_i = expression_t::create_binary(Constants::ASSIGN, exp_j, exp_i);
    CHECK(ass_j_i.str() == "j = i");
    auto exp_a2 = expression_t::create_binary(Constants::SUBSCRIPT, exp_a, exp_2);
    CHECK(exp_a2.str() == "a[2]");
    auto ass_a2_2 = expression_t::create_binary(Constants::ASSIGN, exp_a2, exp_2);
    CHECK(ass_a2_2.str() == "a[2] = 2");
    auto block = BlockStatement{global};
    block.emplace<IfStatement>(eq_j_0, std::make_unique<ExprStatement>(ass_i_0));
    block.emplace<ExprStatement>(ass_j_i);
    block.emplace<ExprStatement>(ass_a2_2);

    auto potential_reads = collect_potential_dependencies(block);
    CHECK(potential_reads == std::set{symb_i, symb_j, symb_a});

    auto potential_writes = collect_potential_changes(block);
    CHECK(potential_writes.size() == 3);
    CHECK(potential_writes.find(symb_i) != potential_writes.end());
    CHECK(potential_writes.find(symb_j) != potential_writes.end());

    auto sure_writes = collect_sure_changes(block);
    CHECK(sure_writes.size() == 1);
    CHECK(sure_writes.find(symb_i) == sure_writes.end());
    CHECK(sure_writes.find(symb_j) != sure_writes.end());

    // inline-if
    auto iif_eq_j_0_i_k = expression_t::create_nary(Constants::INLINE_IF, {eq_j_0, exp_i, exp_k});
    CHECK(iif_eq_j_0_i_k.str() == "j == 0 ? i : k");
    auto stat_iif1 = ExprStatement{iif_eq_j_0_i_k};
    potential_reads = collect_potential_dependencies(stat_iif1);
    CHECK(potential_reads == std::set{symb_i, symb_j, symb_k});
    potential_writes = collect_potential_changes(stat_iif1);
    CHECK(potential_writes.empty());
    sure_writes = collect_sure_changes(stat_iif1);
    CHECK(sure_writes.empty());

    // inline-if with assignment
    auto iif_j_i_k_a2 = expression_t::create_binary(Constants::ASSIGN, iif_eq_j_0_i_k, exp_a2);
    CHECK(iif_j_i_k_a2.str() == "(j == 0 ? i : k) = a[2]");

    potential_reads.clear();
    iif_j_i_k_a2.collect_potential_reads(potential_reads);
    CHECK(potential_reads == std::set{symb_i, symb_j, symb_k, symb_a});

    potential_writes.clear();
    iif_j_i_k_a2.collect_potential_writes(potential_writes);
    CHECK(potential_writes == std::set{symb_i, symb_k});

    sure_writes.clear();
    iif_j_i_k_a2.collect_sure_writes(sure_writes);
    CHECK(sure_writes.empty());
}