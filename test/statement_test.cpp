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

#include "utap/expression.h"
#include "utap/statement.h"

#include <doctest/doctest.h>

TEST_SUITE_BEGIN("Statements");

using namespace UTAP;
using namespace std::string_literals;

constexpr auto indent = "";

TEST_CASE("Empty")
{
    auto s = EmptyStatement{};
    CHECK(s.to_string(indent) == "");
}

expression_t make_assignment(const expression_t& id)
{
    auto i1 = expression_t::create_constant(1);
    auto i2 = expression_t::create_constant(2);
    auto i1_plus_i2 = expression_t::create_binary(Constants::PLUS, i1, i2);
    auto var_a_assign = expression_t::create_binary(UTAP::Constants::ASSIGN, id, i1_plus_i2);
    return var_a_assign;
}

expression_t make_equality(const expression_t& id)
{
    auto i1 = expression_t::create_constant(1);
    auto i2 = expression_t::create_constant(2);
    auto i1_plus_i2 = expression_t::create_binary(Constants::PLUS, i1, i2);
    auto var_a_assign = expression_t::create_binary(UTAP::Constants::EQ, id, i1_plus_i2);
    return var_a_assign;
}

TEST_CASE("Composite")
{
    auto int_type = type_t::create_primitive(UTAP::Constants::INT);
    auto global = frame_t::create();
    auto var_a = global.add_symbol("a", int_type, {});
    auto id_a = expression_t::create_identifier(var_a);
    SUBCASE("Assignment")
    {
        auto s = ExprStatement{make_assignment(id_a)};
        CHECK(s.to_string(indent) == "a = 1 + 2;");
    }
    SUBCASE("Equality")
    {
        auto s = ExprStatement{make_equality(id_a)};
        CHECK(s.to_string(indent) == "a == 1 + 2;");
    }
    SUBCASE("Assertion")
    {
        auto s = AssertStatement{make_equality(id_a)};
        CHECK(s.to_string(indent) == "assert(a == 1 + 2);");
    }
    SUBCASE("For-loop")
    {
        auto var_i = global.add_symbol("i", int_type);
        auto id_i = expression_t::create_identifier(var_i);
        auto val0 = expression_t::create_constant(0);
        auto init = expression_t::create_binary(UTAP::Constants::ASSIGN, id_i, val0);
        auto val5 = expression_t::create_constant(5);
        auto cond = expression_t::create_binary(UTAP::Constants::LT, id_i, val5);
        auto step = expression_t::create_unary(UTAP::Constants::PRE_INCREMENT, id_i);
        auto comp = expression_t::create_binary(UTAP::Constants::ASS_PLUS, id_a, id_i);
        auto stat = std::make_unique<ExprStatement>(comp);
        auto s = ForStatement{init, cond, step, std::move(stat)};
        CHECK(s.to_string(indent) == "for (i = 0; i < 5; ++i)\n"s + INDENT + "a += i;\n");
    }
    SUBCASE("Ranged-loop")
    {
        auto val0 = expression_t::create_constant(0);
        auto val2b = expression_t::create_constant((1u << 31) - 1);
        auto uint32_type = type_t::create_range(int_type, val0, val2b);
        auto val5 = expression_t::create_constant(5);
        auto int_0_5 = type_t::create_range(uint32_type, val0, val5);
        auto var_i = global.add_symbol("i", int_0_5);
        auto id_i = expression_t::create_identifier(var_i);
        auto comp = expression_t::create_binary(UTAP::Constants::ASS_PLUS, id_a, id_i);
        auto stat = std::make_unique<ExprStatement>(comp);
        auto s = RangeStatement{var_i, global, std::move(stat)};
        CHECK(s.to_string(indent) == "for (i : int[0,5])\n"s + INDENT + "a += i;\n");
    }
}

TEST_SUITE_END();
