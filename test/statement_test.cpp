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
#include "utap/statement.hpp"

#include <doctest/doctest.h>

TEST_SUITE_BEGIN("Statements");

using namespace UTAP;
using namespace std::string_literals;

static const std::string indent = INDENT;  // one indentation to harden the tests

TEST_CASE("Empty")
{
    auto s = EmptyStatement{};
    CHECK(s.returns() == false);
    CHECK(s.to_string(indent) == indent + ";");
}

TEST_CASE("Composite")
{
    using UTAP::Kind;
    auto int_type = Type::create_primitive(Kind::INT);
    auto global = Frame::make();
    auto var_a = global.add_symbol("a", int_type, {});
    auto id_a = Expression::create_identifier(var_a);
    auto val0 = Expression::create_constant(0);
    auto val1 = Expression::create_constant(1);
    auto val5 = Expression::create_constant(5);
    SUBCASE("Trivial")
    {
        auto val2 = Expression::create_constant(2);
        auto plus = Expression::create_binary(Kind::PLUS, val1, val2);
        SUBCASE("Assignment")
        {
            auto assign = Expression::create_binary(Kind::ASSIGN, id_a, plus);
            auto s = ExprStatement{assign};
            CHECK(s.returns() == false);
            CHECK(s.to_string(indent) == indent + "a = 1 + 2;");
        }
        SUBCASE("Equality")
        {
            auto equal = Expression::create_binary(Kind::EQ, id_a, plus);
            auto s = ExprStatement{equal};
            CHECK(s.returns() == false);
            CHECK(s.to_string(indent) == indent + "a == 1 + 2;");
        }
        SUBCASE("Assertion")
        {
            auto equal = Expression::create_binary(Kind::EQ, id_a, plus);
            auto s = AssertStatement{equal};
            CHECK(s.returns() == false);
            CHECK(s.to_string(indent) == indent + "assert(a == 1 + 2);");
        }
    }
    SUBCASE("Conditional")
    {
        auto var_i = global.add_symbol("i", int_type);
        auto id_i = Expression::create_identifier(var_i);
        auto step_i = Expression::create_unary(Kind::PRE_INCREMENT, id_i);
        auto step_a = Expression::create_binary(Kind::ASS_PLUS, id_a, id_i);
        auto cond_i = Expression::create_binary(Kind::LT, id_i, val5);
        auto cond_a = Expression::create_binary(Kind::LT, id_a, val5);
        SUBCASE("If")
        {
            auto s =
                IfStatement{cond_i, std::make_unique<ExprStatement>(step_i), std::make_unique<ExprStatement>(step_a)};
            CHECK(s.returns() == false);
            CHECK(s.to_string(indent) == indent + "if (i < 5)\n" + indent + INDENT + "++i;\n" + indent + "else\n" +
                                             indent + INDENT + "a += i;\n");
        }
        SUBCASE("For loop")
        {
            auto init = Expression::create_binary(Kind::ASSIGN, id_i, val0);
            auto s = ForStatement{init, cond_i, step_i, std::make_unique<ExprStatement>(step_a)};
            CHECK(s.returns() == false);
            CHECK(s.to_string(indent) == indent + "for (i = 0; i < 5; ++i)\n"s + indent + INDENT + "a += i;\n");
        }
        SUBCASE("While loop")
        {
            auto s = WhileStatement{cond_i, std::make_unique<ExprStatement>(step_i)};
            CHECK(s.returns() == false);
            CHECK(s.to_string(indent) == indent + "while (i < 5)\n"s + indent + INDENT + "++i;\n");
        }
        SUBCASE("Do-While loop")
        {
            auto s = DoWhileStatement{std::make_unique<ExprStatement>(step_i), cond_i};
            CHECK(s.returns() == false);
            CHECK(s.to_string(indent) == indent + "do\n" + indent + INDENT + "++i;\n"s + indent + "while (i < 5);\n");
        }
    }
    SUBCASE("Ranged loop")
    {
        auto int_0_5 = Type::create_range(int_type, val0, val5);
        auto var_i = global.add_symbol("i", int_0_5);
        auto id_i = Expression::create_identifier(var_i);
        auto comp = Expression::create_binary(Kind::ASS_PLUS, id_a, id_i);
        auto s = RangeStatement{var_i, global, std::make_unique<ExprStatement>(comp)};
        CHECK(s.returns() == false);
        CHECK(s.to_string(indent) == indent + "for (i : int[0,5])\n"s + indent + INDENT + "a += i;\n");
    }
    SUBCASE("Block")
    {
        auto var_i = global.add_symbol("i", int_type);
        auto id_i = Expression::create_identifier(var_i);
        auto e1 = Expression::create_binary(Kind::ASS_PLUS, id_a, id_i);
        auto e2 = Expression::create_unary(Kind::PRE_INCREMENT, id_a);
        auto s = BlockStatement{global};
        CHECK(s.returns() == true);
        CHECK(s.to_string(indent) == "{\n" + indent + "}");
        s.push(std::make_unique<ExprStatement>(e1));
        CHECK(s.returns() == false);
        CHECK(s.to_string(indent) == "{\n" + indent + INDENT + "a += i;\n" + indent + "}");
        s.push(std::make_unique<ExprStatement>(e2));
        CHECK(s.returns() == false);
        CHECK(s.to_string(indent) == "{\n" + indent + INDENT + "a += i;\n" + indent + INDENT + "++a;\n" + indent + "}");
        s.push(std::make_unique<ReturnStatement>());
        CHECK(s.returns() == true);
        CHECK(s.to_string(indent) == "{\n" + indent + INDENT + "a += i;\n" + indent + INDENT + "++a;\n" + indent +
                                         INDENT + "return ;\n" + indent + "}");
    }
    SUBCASE("External block")
    {
        auto fn = [] { return true; };
        auto s = ExternalBlockStatement{global, (void*)+fn, true};
        CHECK(s.returns() == true);
        CHECK(s.to_string(indent) == "{\n" + indent + "}");
    }
    SUBCASE("Switch")
    {
        // switch/case/default/break/continue are unreachable from any real
        // parsed model: "switch", "case", "break" and "continue" are not
        // registered as keywords in keywords.cpp/lexer.l (only "default" is,
        // for the unrelated "chan priority default" syntax), even though
        // the grammar productions and builder callbacks (switch_begin(),
        // case_begin(), break_statement(), etc.) all exist. So these classes
        // are only exercisable via direct construction, as done here.
        auto s = SwitchStatement{id_a};
        CHECK(s.returns() == false);
        CHECK(s.to_string(indent) == indent + "switch (a) ;\n");
        auto case0 = std::make_unique<CaseStatement>(val0);
        case0->stat = std::make_unique<BreakStatement>();
        CHECK(case0->returns() == false);
        CHECK(case0->stat->returns() == false);
        s.push(std::move(case0));
        CHECK(s.to_string(indent) ==
              indent + "switch (a)\n" + indent + INDENT + "case 0:\n" + indent + INDENT + INDENT + "break;\n");
        auto case1 = std::make_unique<CaseStatement>(val1);
        case1->stat = std::make_unique<BreakStatement>();
        s.push(std::move(case1));
        CHECK(s.to_string(indent) == indent + "switch (a) {\n" + indent + INDENT + "case 0:\n" + indent + INDENT +
                                         INDENT + "break;\n" + indent + INDENT + "case 1:\n" + indent + INDENT +
                                         INDENT + "break;\n" + indent + "}\n");
        auto def = std::make_unique<DefaultStatement>();
        def->stat = std::make_unique<ContinueStatement>();
        CHECK(def->returns() == false);
        CHECK(def->stat->returns() == false);
        CHECK(def->stat->to_string(indent) == indent + "continue;");
        s.push(std::move(def));
        CHECK(s.to_string(indent) == indent + "switch (a) {\n" + indent + INDENT + "case 0:\n" + indent + INDENT +
                                         INDENT + "break;\n" + indent + INDENT + "case 1:\n" + indent + INDENT +
                                         INDENT + "break;\n" + indent + INDENT + "default:\n" + indent + INDENT +
                                         INDENT + "continue;\n" + indent + "}\n");

        // collect_changes()/collect_dependencies() walk into a switch's
        // cases/default via ExpressionVisitor, which in turn dispatch
        // through AbstractStatementVisitor::visit_composite_statement.
        auto assign_switch = SwitchStatement{id_a};
        auto assigning_case = std::make_unique<CaseStatement>(val0);
        assigning_case->stat = std::make_unique<ExprStatement>(Expression::create_binary(Kind::ASSIGN, id_a, val1));
        assign_switch.push(std::move(assigning_case));
        auto assigning_default = std::make_unique<DefaultStatement>();
        assigning_default->stat = std::make_unique<ExprStatement>(Expression::create_binary(Kind::ASSIGN, id_a, val0));
        assign_switch.push(std::move(assigning_default));
        auto changes = collect_changes(assign_switch);
        REQUIRE(changes.size() == 1);
        CHECK(changes.begin()->get_name() == "a");
        auto deps = collect_dependencies(assign_switch);
        REQUIRE(deps.size() == 1);
        CHECK(deps.begin()->get_name() == "a");
    }
    SUBCASE("Return")
    {
        auto s = ReturnStatement{id_a};
        CHECK(s.returns() == true);
        CHECK(s.to_string(indent) == indent + "return a;");
    }
}

namespace {
/// AbstractStatementVisitor's own visit_xxx_statement bodies are shadowed by
/// ExpressionVisitor's overrides for every statement kind ExpressionVisitor
/// itself overrides (i.e. every real user of AbstractStatementVisitor in
/// this codebase is an ExpressionVisitor subclass), so most of them are only
/// reachable by dispatching through a bare AbstractStatementVisitor.
struct MinimalStatementVisitor : AbstractStatementVisitor
{};
}  // namespace

TEST_CASE("AbstractStatementVisitor dispatches directly to each statement kind")
{
    using UTAP::Kind;
    auto int_type = Type::create_primitive(Kind::INT);
    auto global = Frame::make();
    auto var_a = global.add_symbol("a", int_type, {});
    auto val0 = Expression::create_constant(0);
    auto val1 = Expression::create_constant(1);

    auto v = MinimalStatementVisitor{};
    CHECK_NOTHROW(EmptyStatement{}.accept(v));
    CHECK_NOTHROW(ExprStatement{val0}.accept(v));
    CHECK_NOTHROW(AssertStatement{val0}.accept(v));
    CHECK_NOTHROW((IfStatement{val0, std::make_unique<ExprStatement>(val0), std::make_unique<ExprStatement>(val1)}
                       .accept(v)));
    CHECK_NOTHROW(IfStatement{val0, std::make_unique<ExprStatement>(val0)}.accept(v));
    CHECK_NOTHROW(ForStatement{val0, val0, val0, std::make_unique<ExprStatement>(val0)}.accept(v));
    CHECK_NOTHROW(RangeStatement{var_a, global, std::make_unique<ExprStatement>(val0)}.accept(v));
    CHECK_NOTHROW(WhileStatement{val0, std::make_unique<ExprStatement>(val0)}.accept(v));
    CHECK_NOTHROW(DoWhileStatement{std::make_unique<ExprStatement>(val0), val0}.accept(v));

    auto block = BlockStatement{global};
    block.push(std::make_unique<ExprStatement>(val0));
    CHECK_NOTHROW(block.accept(v));

    auto sw = SwitchStatement{val0};
    auto c = std::make_unique<CaseStatement>(val0);
    c->stat = std::make_unique<ExprStatement>(val0);
    sw.push(std::move(c));
    CHECK_NOTHROW(sw.accept(v));

    CHECK_NOTHROW(CaseStatement{val0}.accept(v));  // no inner statement
    CHECK_NOTHROW(DefaultStatement{}.accept(v));   // no inner statement
    auto def_with_stat = DefaultStatement{};
    def_with_stat.stat = std::make_unique<ExprStatement>(val0);
    CHECK_NOTHROW(def_with_stat.accept(v));
    CHECK_NOTHROW(BreakStatement{}.accept(v));
    CHECK_NOTHROW(ContinueStatement{}.accept(v));
    CHECK_NOTHROW(ReturnStatement{}.accept(v));
}

TEST_SUITE_END();
