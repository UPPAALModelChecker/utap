// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2020-2024 Aalborg University.

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

#include "utap/expression.hpp"

#include "document_fixture.h"

#include <doctest/doctest.h>

#include <set>
#include <sstream>
#include <stdexcept>

TEST_SUITE_BEGIN("Expressions");

TEST_CASE("Expression")
{
    using UTAP::Type;
    using UTAP::Kind;
    using Exp = UTAP::Expression;
    const auto i_prim_type = Type::create_primitive(Kind::INT);
    REQUIRE(i_prim_type.get_kind() == Kind::INT);
    const auto d_prim_type = Type::create_primitive(Kind::DOUBLE);
    REQUIRE(d_prim_type.get_kind() == Kind::DOUBLE);

    const auto i0 = Exp::create_constant(0);
    REQUIRE(i0.get_kind() == Kind::CONSTANT);
    const auto i2 = Exp::create_constant(2);
    REQUIRE(i2.get_kind() == Kind::CONSTANT);
    CHECK(i2.get_type().get_kind() == Kind::INT);
    CHECK(i2.get_value() == 2);
    const auto i5 = Exp::create_constant(5);
    REQUIRE(i5.get_kind() == Kind::CONSTANT);
    CHECK(i5.get_type().get_kind() == Kind::INT);
    CHECK(i5.get_value() == 5);
    const auto d3 = Exp::create_double(3.0);
    REQUIRE(d3.get_kind() == Kind::CONSTANT);
    CHECK(d3.get_type().get_kind() == Kind::DOUBLE);
    CHECK(d3.get_double_value() == 3.0);
    const auto d1_2 = Exp::create_double(0.5);
    REQUIRE(d1_2.get_kind() == Kind::CONSTANT);
    CHECK(d1_2.get_type().get_kind() == Kind::DOUBLE);
    CHECK(d1_2.get_double_value() == 0.5);

    SUBCASE("Types")
    {
        const auto i02 = Type::create_range(i_prim_type, i0, i2);
        REQUIRE(i02.get_kind() == Kind::RANGE);
        const auto i02_range = i02.get_range();
        CHECK(i02_range.first == i0);
        CHECK(i02_range.second == i2);
        const auto i25 = Type::create_range(i_prim_type, i2, i5);
        REQUIRE(i25.get_kind() == Kind::RANGE);
        const auto i25_range = i25.get_range();
        CHECK(i25_range.first == i2);
        CHECK(i25_range.second == i5);
        const auto i52 = Type::create_range(i_prim_type, i5, i2);  // no checks
    }

    SUBCASE("Operator precedence")
    {
        using namespace UTAP::KindNames;
        // Follow table at https://en.cppreference.com/w/cpp/language/operator_precedence
        REQUIRE(Exp::get_precedence(POST_INCREMENT) == Exp::get_precedence(POST_DECREMENT));
        REQUIRE(Exp::get_precedence(POST_INCREMENT) >= Exp::get_precedence(FUN_CALL));
        REQUIRE(Exp::get_precedence(FUN_CALL) == Exp::get_precedence(FUN_CALL_EXT));
        REQUIRE(Exp::get_precedence(FUN_CALL) >= Exp::get_precedence(ARRAY));
        REQUIRE(Exp::get_precedence(ARRAY) >= Exp::get_precedence(DOT));
        REQUIRE(Exp::get_precedence(ARRAY) > Exp::get_precedence(NOT));
        REQUIRE(Exp::get_precedence(DOT) >= Exp::get_precedence(RATE));
        REQUIRE(Exp::get_precedence(PRE_INCREMENT) == Exp::get_precedence(NOT));
        REQUIRE(Exp::get_precedence(PRE_INCREMENT) == Exp::get_precedence(PRE_DECREMENT));
        REQUIRE(Exp::get_precedence(PRE_INCREMENT) >= Exp::get_precedence(UNARY_MINUS));
        REQUIRE(Exp::get_precedence(UNARY_MINUS) >= Exp::get_precedence(NOT));
        REQUIRE(Exp::get_precedence(NOT) > Exp::get_precedence(POW));
        REQUIRE(Exp::get_precedence(POW) > Exp::get_precedence(MULT));
        REQUIRE(Exp::get_precedence(MULT) == Exp::get_precedence(DIV));
        REQUIRE(Exp::get_precedence(MULT) == Exp::get_precedence(MOD));
        REQUIRE(Exp::get_precedence(MULT) > Exp::get_precedence(PLUS));
        REQUIRE(Exp::get_precedence(PLUS) == Exp::get_precedence(MINUS));
        REQUIRE(Exp::get_precedence(PLUS) > Exp::get_precedence(BIT_LSHIFT));
        REQUIRE(Exp::get_precedence(BIT_LSHIFT) == Exp::get_precedence(BIT_RSHIFT));
        REQUIRE(Exp::get_precedence(BIT_LSHIFT) > Exp::get_precedence(LT));
        REQUIRE(Exp::get_precedence(LT) == Exp::get_precedence(LE));
        REQUIRE(Exp::get_precedence(LT) == Exp::get_precedence(GT));
        REQUIRE(Exp::get_precedence(LT) == Exp::get_precedence(GE));
        REQUIRE(Exp::get_precedence(LT) > Exp::get_precedence(EQ));
        REQUIRE(Exp::get_precedence(EQ) == Exp::get_precedence(NEQ));
        REQUIRE(Exp::get_precedence(NEQ) > Exp::get_precedence(BIT_AND));
        REQUIRE(Exp::get_precedence(BIT_AND) > Exp::get_precedence(BIT_XOR));
        REQUIRE(Exp::get_precedence(BIT_XOR) > Exp::get_precedence(BIT_OR));
        REQUIRE(Exp::get_precedence(BIT_OR) > Exp::get_precedence(AND));
        REQUIRE(Exp::get_precedence(AND) > Exp::get_precedence(OR));
        REQUIRE(Exp::get_precedence(AND) > Exp::get_precedence(ASSIGN));
        REQUIRE(Exp::get_precedence(ASSIGN) == Exp::get_precedence(ASS_PLUS));
        REQUIRE(Exp::get_precedence(ASSIGN) == Exp::get_precedence(ASS_MINUS));
        REQUIRE(Exp::get_precedence(ASSIGN) == Exp::get_precedence(ASS_MULT));
        REQUIRE(Exp::get_precedence(ASSIGN) == Exp::get_precedence(ASS_DIV));
        REQUIRE(Exp::get_precedence(ASSIGN) == Exp::get_precedence(ASS_MOD));
        REQUIRE(Exp::get_precedence(ASSIGN) == Exp::get_precedence(ASS_LSHIFT));
        REQUIRE(Exp::get_precedence(ASSIGN) == Exp::get_precedence(ASS_RSHIFT));
        REQUIRE(Exp::get_precedence(ASSIGN) == Exp::get_precedence(ASS_AND));
        REQUIRE(Exp::get_precedence(ASSIGN) == Exp::get_precedence(ASS_OR));
        REQUIRE(Exp::get_precedence(ASSIGN) == Exp::get_precedence(ASS_XOR));
        REQUIRE(Exp::get_precedence(ASSIGN) > Exp::get_precedence(COMMA));
    }

    SUBCASE("Unary")
    {
        using namespace UTAP::KindNames;
        const auto ops = {// clang-format off
            UNARY_MINUS, NOT, DOT, /*SYNC,*/ PRE_INCREMENT, POST_INCREMENT, PRE_DECREMENT, POST_DECREMENT,
            RATE, ABS_F, FABS_F, EXP_F, EXP2_F, EXPM1_F, LN_F, LOG_F, LOG10_F, LOG2_F, LOG1P_F, SQRT_F,
            CBRT_F, SIN_F, COS_F, TAN_F, ASIN_F, ACOS_F, ATAN_F, SINH_F, COSH_F, TANH_F, ASINH_F,
            ACOSH_F, ATANH_F, ERF_F, ERFC_F, TGAMMA_F, LGAMMA_F, CEIL_F, FLOOR_F, TRUNC_F, ROUND_F,
            FINT_F, ILOGB_F, LOGB_F, FP_CLASSIFY_F, IS_FINITE_F, IS_INF_F, IS_NAN_F, IS_NORMAL_F,
            SIGNBIT_F, IS_UNORDERED_F, RANDOM_F, RANDOM_POISSON_F
        };  // clang-format on
        for (const auto& op : ops) {
            REQUIRE(Exp::get_precedence(op) > 0);
            const auto op_i0 = Exp::create_unary(op, i0);
            CHECK(op_i0.get_kind() == op);
            REQUIRE(op_i0.get_size() == 1);
            CHECK(op_i0.get(0) == i0);
            const auto op_i2 = Exp::create_unary(op, i2);
            CHECK(op_i2.get_kind() == op);
            REQUIRE(op_i2.get_size() == 1);
            CHECK(op_i2.get(0) == i2);
            const auto op_d3 = Exp::create_unary(op, d3);
            CHECK(op_d3.get_kind() == op);
            REQUIRE(op_d3.get_size() == 1);
            CHECK(op_d3.get(0) == d3);
            const auto op_d1_2 = Exp::create_unary(op, d1_2);
            CHECK(op_d1_2.get_kind() == op);
            REQUIRE(op_d1_2.get_size() == 1);
            CHECK(op_d1_2.get(0) == d1_2);
        }
    }
    SUBCASE("Binary")
    {
        using namespace UTAP::KindNames;
        const auto ops = {
            // clang-format off
            MINUS, PLUS, MULT, DIV, MOD, BIT_AND, BIT_OR, BIT_XOR, BIT_LSHIFT, BIT_RSHIFT,
            AND, OR, XOR, POW, LT, LE, EQ, NEQ, GE, GT, MIN, MAX, ARRAY, COMMA,
            ASSIGN, ASS_PLUS, ASS_MINUS, ASS_DIV, ASS_MOD, ASS_MULT, ASS_AND, ASS_OR, ASS_XOR,
            ASS_LSHIFT, ASS_RSHIFT, FORALL, EXISTS, SUM, SUP_VAR, INF_VAR, BOUNDS_VAR, FRACTION,
            FMOD_F, FMAX_F, FMIN_F, FDIM_F, POW_F, HYPOT_F, ATAN2_F, LDEXP_F, NEXT_AFTER_F, COPY_SIGN_F,
            RANDOM_ARCSINE_F, RANDOM_BETA_F, RANDOM_GAMMA_F, RANDOM_NORMAL_F, RANDOM_WEIBULL_F,
        };  // clang-format on
        for (const auto& op : ops) {
            REQUIRE(Exp::get_precedence(op) > 0);
            const auto op_i25 = Exp::create_binary(op, i2, i5);
            CHECK(op_i25.get_kind() == op);
            REQUIRE(op_i25.get_size() == 2);
            CHECK(op_i25.get(0) == i2);
            CHECK(op_i25.get(1) == i5);
            const auto op_d3_2 = Exp::create_binary(op, d3, d1_2);
            CHECK(op_d3_2.get_kind() == op);
            REQUIRE(op_d3_2.get_size() == 2);
            CHECK(op_d3_2.get(0) == d3);
            CHECK(op_d3_2.get(1) == d1_2);
        }
    }
}

TEST_CASE("Expression to string conversion")
{
    using UTAP::Kind;
    using Exp = UTAP::Expression;
    const auto i2 = Exp::create_constant(2);
    const auto i3 = Exp::create_constant(3);
    const auto i5 = Exp::create_constant(5);
    const auto i7 = Exp::create_constant(7);
    SUBCASE("Addition and multiplication")
    {
        const auto add1 = Exp::create_binary(Kind::PLUS, i2, i3);
        CHECK(add1.str() == "2 + 3");
        const auto add2 = Exp::create_binary(Kind::PLUS, i5, i7);
        CHECK(add2.str() == "5 + 7");
        const auto mult = Exp::create_binary(Kind::MULT, add1, add2);
        CHECK(mult.str() == "(2 + 3) * (5 + 7)");
    }
    SUBCASE("Multiplication and power")
    {
        const auto m1 = Exp::create_binary(Kind::MULT, i2, i3);
        CHECK(m1.str() == "2 * 3");
        const auto m2 = Exp::create_binary(Kind::MULT, i5, i7);
        CHECK(m2.str() == "5 * 7");
        const auto p = Exp::create_binary(Kind::POW, m1, m2);
        CHECK(p.str() == "(2 * 3) ** (5 * 7)");
    }
}

TEST_CASE("Empty expression is safe to print, str and compare")
{
    // Regression test: Expression::print()/str() used to dereference the
    // internal (shared_ptr) data unconditionally, crashing on a default-
    // constructed (empty) expression -- even though str()'s own doc comment
    // says it "Returns empty [string] if the expression is empty".
    auto e = UTAP::Expression{};
    CHECK(e.empty());
    CHECK(e.str() == "");
    auto oss = std::ostringstream{};
    e.print(oss);
    CHECK(oss.str() == "");
    CHECK(e == UTAP::Expression{});
    CHECK_FALSE(e < UTAP::Expression{});
}

TEST_CASE("Cloning and substitution")
{
    using UTAP::Expression;
    using UTAP::Frame;
    using UTAP::Kind;
    using UTAP::Type;

    auto frame = Frame::make();
    auto sym_a = frame.add_symbol("a", Type::create_primitive(Kind::INT));
    auto sym_b = frame.add_symbol("b", Type::create_primitive(Kind::INT));
    auto ea = Expression::create_identifier(sym_a);
    auto eb = Expression::create_identifier(sym_b);
    auto plus = Expression::create_binary(Kind::PLUS, ea, eb);

    SUBCASE("clone() makes a shallow copy sharing subexpressions")
    {
        auto shallow = plus.clone();
        CHECK(shallow.equal(plus));
        CHECK_FALSE(shallow == plus);           // distinct expression node
        CHECK(shallow[0] == plus[0]);           // but subexpressions are shared
        CHECK(shallow.str() == "a + b");
    }

    SUBCASE("clone_deeper() recursively copies subexpressions")
    {
        auto deep = plus.clone_deeper();
        CHECK(deep.equal(plus));
        CHECK_FALSE(deep[0] == plus[0]);  // subexpressions are independent copies
        CHECK(deep.str() == "a + b");
    }

    SUBCASE("clone_deeper(from, to) replaces one symbol")
    {
        auto sym_a2 = frame.add_symbol("a2", Type::create_primitive(Kind::INT));
        auto replaced = plus.clone_deeper(sym_a, sym_a2);
        CHECK(replaced.str() == "a2 + b");
    }

    SUBCASE("clone_deeper(frame) re-resolves symbols by name in another frame")
    {
        auto other = Frame::make();
        other.add_symbol("a", Type::create_primitive(Kind::INT));
        other.add_symbol("b", Type::create_primitive(Kind::INT));
        auto rebound = plus.clone_deeper(other);
        CHECK(rebound.str() == "a + b");
    }

    SUBCASE("subst() replaces a symbol with an expression throughout the tree")
    {
        auto five = Expression::create_constant(5);
        auto substituted = plus.subst(sym_a, five);
        CHECK(substituted.str() == "5 + b");
        // subst() on an empty expression is a no-op returning itself
        CHECK(Expression{}.subst(sym_a, five).empty());
        // subst() on a leaf with no children returns itself unchanged
        CHECK(five.subst(sym_a, ea).equal(five));
    }
}

TEST_CASE("get_precedence throws for kinds without a defined precedence")
{
    using UTAP::Expression;
    using UTAP::Frame;
    using UTAP::Kind;
    using UTAP::Type;
    auto frame = Frame::make();
    auto sym_a = frame.add_symbol("a", Type::create_primitive(Kind::INT));
    auto range_expr = Expression::create_unary(Kind::RANGE, Expression::create_identifier(sym_a));
    CHECK_THROWS_WITH_AS(range_expr.get_precedence(), "Unknown precedence of the expression", std::logic_error);
    // print() tolerates the throw internally (falls back to precedence -1)
    // and simply emits nothing for a type-only kind like RANGE.
    CHECK(range_expr.str() == "");
}

TEST_CASE("Deadlock and exit expressions")
{
    using UTAP::Expression;
    using UTAP::Kind;
    auto dl = Expression::create_deadlock();
    CHECK(dl.get_kind() == Kind::DEADLOCK);
    CHECK(dl.str() == "deadlock");
    CHECK(dl.contains_deadlock());

    auto exit_expr = Expression::create_exit();
    CHECK(exit_expr.get_kind() == Kind::EXIT);
    CHECK(exit_expr.str() == "EXIT");
    CHECK(exit_expr.is_dynamic());

    auto five = Expression::create_constant(5);
    CHECK_FALSE(Expression::create_binary(Kind::PLUS, five, five).contains_deadlock());
    CHECK(Expression::create_binary(Kind::PLUS, dl, five).contains_deadlock());
    CHECK_FALSE(Expression::create_binary(Kind::PLUS, five, five).has_dynamic_sub());
    CHECK(Expression::create_binary(Kind::PLUS, exit_expr, five).has_dynamic_sub());
}

TEST_CASE("get_symbol and get_symbols across expression kinds")
{
    using UTAP::Expression;
    using UTAP::Frame;
    using UTAP::Kind;
    using UTAP::Sync;
    using UTAP::Type;

    auto frame = Frame::make();
    auto sym_a = frame.add_symbol("a", Type::create_primitive(Kind::INT));
    auto ea = Expression::create_identifier(sym_a);
    auto zero = Expression::create_constant(0);

    auto check_single_symbol = [&](const Expression& e) {
        CHECK(e.get_symbol().get_name() == "a");
        auto syms = std::set<UTAP::Symbol>{};
        e.get_symbols(syms);
        REQUIRE(syms.size() == 1);
        CHECK(syms.begin()->get_name() == "a");
    };

    check_single_symbol(Expression::create_dot(ea, 0));
    check_single_symbol(Expression::create_binary(Kind::ARRAY, ea, zero));
    check_single_symbol(Expression::create_unary(Kind::PRE_INCREMENT, ea));
    check_single_symbol(Expression::create_ternary(Kind::INLINE_IF, zero, ea, zero));
    check_single_symbol(Expression::create_binary(Kind::COMMA, zero, ea));
    check_single_symbol(Expression::create_sync(ea, Sync::BANG));

    // FUN_CALL/SCENARIO resolve get_symbol() but are not handled by get_symbols()
    auto fun_call = Expression::create_nary(Kind::FUN_CALL, {ea, zero});
    CHECK(fun_call.get_symbol().get_name() == "a");
    auto syms = std::set<UTAP::Symbol>{};
    fun_call.get_symbols(syms);
    CHECK(syms.empty());

    // Kinds not in get_symbol()'s switch return a blank symbol. Symbol's
    // getters (like the Expression pImpl they mirror) assume a valid,
    // non-default instance, so compare by identity rather than calling
    // get_name() on it.
    CHECK(Expression::create_binary(Kind::PLUS, ea, zero).get_symbol() == UTAP::Symbol{});
}

TEST_CASE("Bare expression printing covers arithmetic, logic, comparison and ternary forms")
{
    using UTAP::Document;
    struct Case
    {
        const char* src;
        const char* expected;
    };
    // clang-format off
    const auto cases = {
        Case{"1+1", "1 + 1"}, Case{"3-1", "3 - 1"}, Case{"2*3", "2 * 3"}, Case{"4/2", "4 / 2"},
        Case{"5%2", "5 % 2"}, Case{"2**3", "2 ** 3"}, Case{"1&2", "1 & 2"}, Case{"1|2", "1 | 2"},
        Case{"1^2", "1 ^ 2"}, Case{"1<<2", "1 << 2"}, Case{"8>>2", "8 >> 2"},
        Case{"true&&false", "true && false"}, Case{"true||false", "true || false"},
        Case{"1<2", "1 < 2"}, Case{"1<=2", "1 <= 2"}, Case{"1==2", "1 == 2"}, Case{"1!=2", "1 != 2"},
        Case{"1>=2", "1 >= 2"}, Case{"1>2", "1 > 2"}, Case{"1<?2", "1 <? 2"}, Case{"1>?2", "1 >? 2"},
        Case{"!true", "!true"}, Case{"true?1:2", "true ? 1 : 2"}, Case{"1 xor 0", "(1) xor (0)"},
        Case{"\"hi\"", "hi"},
    };  // clang-format on
    for (const auto& c : cases) {
        auto doc = Document{};
        auto expr = UTAP::parse_expression(c.src, doc, true);
        CHECK_MESSAGE(doc.get_errors().empty(), c.src);
        CHECK_MESSAGE(expr.str() == c.expected, c.src);
    }
}

TEST_CASE("Bare expression printing covers builtin math functions and quantifiers")
{
    using UTAP::Document;
    struct Case
    {
        const char* src;
        const char* expected;
    };
    // clang-format off
    const auto cases = {
        Case{"sqrt(4.0)", "sqrt(4)"}, Case{"abs(1)", "abs(1)"}, Case{"pow(2.0,3.0)", "pow(2,3)"},
        Case{"fma(1.0,2.0,3.0)", "fma(1,2,3)"}, Case{"random(1.0)", "random(1)"},
        Case{"random_arcsine(1.0,2.0)", "random_arcsine(1,2)"},
        Case{"random_tri(1.0,2.0,3.0)", "random_tri(1,2,3)"},
        Case{"forall (i:int[0,2]) i>=0", "forall(i:(const (range (int) \"0\" \"2\"))) i >= 0"},
        Case{"exists (i:int[0,2]) i>=2", "exists(i:(const (range (int) \"0\" \"2\"))) i >= 2"},
        Case{"sum (i:int[0,2]) i", "sum(i:(const (range (int) \"0\" \"2\"))) i"},
    };  // clang-format on
    for (const auto& c : cases) {
        auto doc = Document{};
        auto expr = UTAP::parse_expression(c.src, doc, true);
        CHECK_MESSAGE(doc.get_errors().empty(), c.src);
        CHECK_MESSAGE(expr.str() == c.expected, c.src);
    }
}

TEST_CASE("uses_fp/uses_hybrid/uses_clock reflect the resolved type")
{
    auto doc = document_fixture{}.add_global_decl("double d; hybrid clock hc; clock c; int a;").add_default_process().parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);

    auto d = UTAP::parse_expression("d", doc, true);
    CHECK(d.uses_fp());
    CHECK_FALSE(d.uses_hybrid());
    CHECK_FALSE(d.uses_clock());

    auto hc = UTAP::parse_expression("hc", doc, true);
    CHECK_FALSE(hc.uses_fp());
    CHECK(hc.uses_hybrid());
    CHECK(hc.uses_clock());

    auto c = UTAP::parse_expression("c", doc, true);
    CHECK_FALSE(c.uses_fp());
    CHECK_FALSE(c.uses_hybrid());
    CHECK(c.uses_clock());

    auto a = UTAP::parse_expression("a", doc, true);
    CHECK_FALSE(a.uses_fp());
    CHECK_FALSE(a.uses_hybrid());
    CHECK_FALSE(a.uses_clock());
}

TEST_CASE("Assignment, increment/decrement, array and record access print correctly")
{
    static constexpr auto xml = R"XML(<template>
        <name>T</name>
        <location id="id0" x="0" y="0"/>
        <location id="id1" x="10" y="10"/>
        <init ref="id0"/>
        <transition><source ref="id0"/><target ref="id1"/><label kind="assignment">a = 1</label></transition>
        <transition><source ref="id1"/><target ref="id0"/><label kind="assignment">a += 1, a -= 1</label></transition>
        <transition><source ref="id0"/><target ref="id1"/><label kind="assignment">a++, ++a, a--, --a, arr[0] = 1</label></transition>
        <transition><source ref="id1"/><target ref="id0"/><label kind="assignment">p.x = f(1)</label></transition>
    </template>)XML";
    auto doc = document_fixture{}
                   .add_global_decl("int a; int arr[3]; typedef struct { int x; int y; } Pt; Pt p = {1,2};\n"
                                     "int f(int x) { return x+1; }")
                   .add_template(xml)
                   .add_system_decl("Process = T();")
                   .add_process("Process")
                   .parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    auto it = doc.get_templates().front().edges.begin();
    CHECK((it++)->assign.str() == "a = 1");
    CHECK((it++)->assign.str() == "a += 1, a -= 1");
    CHECK((it++)->assign.str() == "a++, ++a, a--, --a, arr[0] = 1");
    CHECK((it++)->assign.str() == "p.x = f(1)");
}

TEST_CASE("Synchronisation and clock rate expressions print correctly")
{
    static constexpr auto xml = R"XML(<template>
        <name>T</name>
        <location id="id0" x="0" y="0"><label kind="invariant">c' == 2</label></location>
        <location id="id1" x="10" y="10"/>
        <init ref="id0"/>
        <transition><source ref="id0"/><target ref="id1"/><label kind="synchronisation">ch!</label></transition>
        <transition><source ref="id1"/><target ref="id0"/><label kind="synchronisation">ch?</label></transition>
    </template>)XML";
    auto doc = document_fixture{}
                   .add_global_decl("clock c; chan ch;")
                   .add_template(xml)
                   .add_system_decl("Process = T();")
                   .add_process("Process")
                   .parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    auto it = doc.get_templates().front().edges.begin();
    CHECK((it++)->sync.str() == "ch!");
    CHECK((it++)->sync.str() == "ch?");
    CHECK(doc.get_templates().front().locations.front().invariant.str() == "1 && c' == 2");
}

TEST_CASE("changes_variable/changes_any_variable/depends_on/is_reference_to")
{
    static constexpr auto xml = R"XML(<template>
        <name>T</name>
        <location id="id0" x="0" y="0"/>
        <location id="id1" x="10" y="10"/>
        <init ref="id0"/>
        <transition><source ref="id0"/><target ref="id1"/>
            <label kind="guard">b &gt; 0</label>
            <label kind="assignment">a = a + 1</label>
        </transition>
    </template>)XML";
    auto doc = document_fixture{}
                   .add_global_decl("int a; int b;")
                   .add_template(xml)
                   .add_system_decl("Process = T();")
                   .add_process("Process")
                   .parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);

    auto sym_a = UTAP::Symbol{};
    auto sym_b = UTAP::Symbol{};
    REQUIRE(doc.get_globals().frame.resolve("a", sym_a));
    REQUIRE(doc.get_globals().frame.resolve("b", sym_b));

    const auto& edge = doc.get_templates().front().edges.front();
    auto only_a = std::set<UTAP::Symbol>{sym_a};
    auto only_b = std::set<UTAP::Symbol>{sym_b};

    CHECK(edge.assign.changes_variable(only_a));
    CHECK_FALSE(edge.assign.changes_variable(only_b));
    CHECK(edge.assign.changes_any_variable());
    CHECK(edge.assign.depends_on(only_a));
    CHECK(edge.assign.is_reference_to(only_a));

    CHECK(edge.guard.depends_on(only_b));
    CHECK_FALSE(edge.guard.changes_any_variable());
}

TEST_SUITE_END();
