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

#include "document_fixture.h"

#include <doctest/doctest.h>

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <cstdio>

TEST_SUITE("Quantifier sum")
{
    TEST_CASE("sum expression")
    {
        auto df = document_fixture{};
        df.add_system_decl("int x = sum (index : int[0, 5]) index;");
        auto doc = df.add_default_process().parse();
        const auto& errs = doc.get_errors();
        CHECK_MESSAGE(errs.empty(), errs.front().msg);
        const auto& warns = doc.get_warnings();
        CHECK_MESSAGE(warns.empty(), warns.front().msg);
    }

    TEST_CASE("sum over array")
    {
        auto df = document_fixture{};
        df.add_system_decl("int a[3] = {1,4,9};");
        df.add_system_decl("int x = sum(i : int[0, 2]) a[i];");
        auto doc = df.add_default_process().parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Must_be_computable_at_compile_time");
        const auto& warns = doc.get_warnings();
        CHECK_MESSAGE(warns.empty(), warns.front().msg);
    }

    TEST_CASE("sum over const array")
    {
        auto df = document_fixture{};
        df.add_system_decl("const int a[3] = {1,4,9};");
        df.add_system_decl("int x = sum(i : int[0, 2]) a[i];");
        auto doc = df.add_default_process().parse();
        const auto& errs = doc.get_errors();
        CHECK_MESSAGE(errs.empty(), errs.front().msg);
        const auto& warns = doc.get_warnings();
        CHECK_MESSAGE(warns.empty(), warns.front().msg);
    }
}

TEST_SUITE("Quantifier forall")
{
    TEST_CASE("forall expression")
    {
        auto df = document_fixture{};
        df.add_system_decl("bool x = forall(index : int[0, 5]) index > 3;");
        auto doc = df.add_default_process().parse();
        const auto& warns = doc.get_warnings();
        CHECK_MESSAGE(warns.empty(), warns.front().msg);
        const auto& errs = doc.get_errors();
        CHECK_MESSAGE(errs.empty(), errs.front().msg);
    }

    TEST_CASE("forall over array")
    {
        auto df = document_fixture{};
        df.add_system_decl("bool b[3] = {1,1,1};");
        df.add_system_decl("bool x = forall(i : int[0,2]) b[i];");
        auto doc = df.add_default_process().parse();
        const auto& warns = doc.get_warnings();
        CHECK_MESSAGE(warns.empty(), warns.front().msg);
        const auto& errors = doc.get_errors();
        REQUIRE(errors.size() == 1);
        CHECK(errors[0].msg == "$Must_be_computable_at_compile_time");
    }

    TEST_CASE("forall over const array")
    {
        auto df = document_fixture{};
        df.add_system_decl("const bool b[3]={1,1,1};");
        df.add_system_decl("bool x = forall(i : int[0,2]) b[i];");
        auto doc = df.add_default_process().parse();
        const auto& errs = doc.get_errors();
        CHECK_MESSAGE(errs.empty(), errs.front().msg);
        const auto& warns = doc.get_warnings();
        CHECK_MESSAGE(warns.empty(), warns.front().msg);
    }
}

TEST_SUITE("Quantifier exists")
{
    TEST_CASE("exists expression")
    {
        auto df = document_fixture{};
        df.add_system_decl("bool x = exists(index : int[0, 5]) index > 3;");
        auto doc = df.add_default_process().parse();
        const auto& errs = doc.get_errors();
        CHECK_MESSAGE(errs.empty(), errs.front().msg);
        const auto& warns = doc.get_warnings();
        CHECK_MESSAGE(warns.empty(), warns.front().msg);
    }
    TEST_CASE("exists over array")
    {
        auto df = document_fixture{};
        df.add_system_decl("bool b[3] = {0,0,1};");
        df.add_system_decl("bool x = exists(i : int[0,2]) b[i];");
        auto doc = df.add_default_process().parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Must_be_computable_at_compile_time");
        const auto& warns = doc.get_warnings();
        CHECK_MESSAGE(warns.empty(), warns.front().msg);
    }
    TEST_CASE("exists over const array")
    {
        auto df = document_fixture{};
        df.add_system_decl("const bool b[3]={0,0,1};");
        df.add_system_decl("bool x = exists(i : int[0,2]) b[i];");
        auto doc = df.add_default_process().parse();
        const auto& errs = doc.get_errors();
        CHECK_MESSAGE(errs.empty(), errs.front().msg);
        const auto& warns = doc.get_warnings();
        CHECK_MESSAGE(warns.empty(), warns.front().msg);
    }
}

TEST_SUITE("Error positions for unbound parameters")
{
    TEST_CASE("Bounded const int parameter")
    {
        auto df = document_fixture{};
        df.add_template(template_fixture{"T"}.add_parameter("const int[1,4] test").str());
        df.add_process("T");
        auto text = df.str();
        auto doc = df.parse();
        const auto& errs = doc.get_errors();
        CHECK_MESSAGE(errs.empty(), errs.front().msg);
        const auto& warns = doc.get_warnings();
        CHECK_MESSAGE(warns.empty(), warns.front().msg);
    }

    TEST_CASE("Bounded int parameter")
    {
        auto df = document_fixture{};
        df.add_template(template_fixture{"T"}.add_parameter("int[1,4] test").str());
        df.add_process("T");
        auto text = df.str();
        auto doc = df.parse();
        const auto& errs = doc.get_errors();
        CHECK_MESSAGE(errs.empty(), errs.front().msg);
        const auto& warns = doc.get_warnings();
        CHECK_MESSAGE(warns.empty(), warns.front().msg);
    }

    TEST_CASE("Unbounded int parameter")
    {
        auto df = document_fixture{};
        df.add_template(template_fixture{"T"}.add_parameter("int test").str());
        df.add_process("T");
        auto text = df.str();
        auto doc = df.parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Free_process_parameters_must_be_a_bounded_integer_or_a_scalar");
        const auto& pos = errs.front().position;
        CHECK(pos.start != pos.unknown_pos);
        CHECK(pos.end != pos.unknown_pos);
        const auto& warns = doc.get_warnings();
        CHECK_MESSAGE(warns.empty(), warns.front().msg);
    }

    TEST_CASE("Reference parameter")
    {
        auto df = document_fixture{};
        df.add_template(template_fixture{"T"}.add_parameter("int& test").str());
        df.add_process("T");
        auto text = df.str();
        auto doc = df.parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Free_process_parameters_must_be_a_bounded_integer_or_a_scalar");
        const auto& pos = errs.front().position;
        CHECK(pos.start != pos.unknown_pos);
        CHECK(pos.end != pos.unknown_pos);
        const auto& warns = doc.get_warnings();
        CHECK_MESSAGE(warns.empty(), warns.front().msg);
    }
}

TEST_CASE("Ternary operator with clock and double")
{
    auto doc = document_fixture{}
                   .add_global_decl("clock c; double x; void f(bool b) { x = b ? c : 1.0; }")
                   .add_default_process()
                   .parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    const auto& warns = doc.get_warnings();
    CHECK_MESSAGE(warns.empty(), warns.front().msg);
}

TEST_CASE("Ternary operator with double and clock")
{
    auto doc = document_fixture{}
                   .add_global_decl("clock c; double x; void f(bool b) { x = b ? 1.0 : c; }")
                   .add_default_process()
                   .parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    const auto& warns = doc.get_warnings();
    CHECK_MESSAGE(warns.empty(), warns.front().msg);
}

TEST_CASE("Ternary operator with clock and integer")
{
    auto doc = document_fixture{}
                   .add_global_decl("clock c; double x; void f(bool b) { x = b ? c : 1; }")
                   .add_default_process()
                   .parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    const auto& warns = doc.get_warnings();
    CHECK_MESSAGE(warns.empty(), warns.front().msg);
}

TEST_CASE("Ternary operator with clock and bool")
{
    auto doc = document_fixture{}
                   .add_global_decl("clock c; double x; void f(bool b) { x = b ? c : true; }")
                   .add_default_process()
                   .parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs[0].msg);
    const auto& warns = doc.get_warnings();
    CHECK_MESSAGE(warns.empty(), warns.front().msg);
}

TEST_CASE("Ternary operator with clock and clock")
{
    auto doc = document_fixture{}
                   .add_global_decl("clock c; double x; void f(bool b) { x = b ? c : c; }")
                   .add_default_process()
                   .parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    const auto& warns = doc.get_warnings();
    CHECK_MESSAGE(warns.empty(), warns.front().msg);
}

TEST_CASE("Ternary operator with constant double")
{
    auto doc = document_fixture{}
                   .add_global_decl("const double VAL = 2;")
                   .add_global_decl("double x; void f(bool b) { x = b ? -VAL : VAL; }")
                   .add_default_process()
                   .parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    const auto& warns = doc.get_warnings();
    CHECK_MESSAGE(warns.empty(), warns.front().msg);
}

TEST_CASE("Ternary operator with constant double and clock")
{
    auto doc = document_fixture{}
                   .add_global_decl("const double VAL = 2;")
                   .add_global_decl("clock c;")
                   .add_global_decl("double x; void f(bool b) { x = b ? -VAL : c; }")
                   .add_default_process()
                   .parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    const auto& warns = doc.get_warnings();
    CHECK_MESSAGE(warns.empty(), warns.front().msg);
}

TEST_CASE("Ternary operator with boolean and clock")
{
    auto doc = document_fixture{}
                   .add_global_decl("clock c;")
                   .add_global_decl("double x; void f(bool b) { x = b? true : c; }")
                   .add_default_process()
                   .parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    const auto& warns = doc.get_warnings();
    CHECK_MESSAGE(warns.empty(), warns.front().msg);
}

TEST_CASE("Ternary operator with struct and double")
{
    auto doc = document_fixture{}
                   .add_global_decl("struct { int x; } s;")
                   .add_global_decl("double x; void f(bool b) { x = b? s : 0.5; }")
                   .add_default_process()
                   .parse();
    const auto& errs = doc.get_errors();
    REQUIRE(errs.size() == 1);
    CHECK(errs[0].msg == "$Incompatible_arguments_to_inline_if");
    const auto& warns = doc.get_warnings();
    CHECK_MESSAGE(warns.empty(), warns.front().msg);
}

TEST_CASE("Ternary operator with struct and double")
{
    auto doc = document_fixture{}
                   .add_global_decl("struct { int x; } s;")
                   .add_global_decl("double x; void f(bool b) { x = b? s : 0.5; }")
                   .add_default_process()
                   .parse();
    const auto& errs = doc.get_errors();
    REQUIRE(errs.size() == 1);
    CHECK(errs[0].msg == "$Incompatible_arguments_to_inline_if");
    const auto& warns = doc.get_warnings();
    CHECK_MESSAGE(warns.empty(), warns.front().msg);
}

TEST_CASE("Ternary operator with struct and struct")
{
    auto doc = document_fixture{}
                   .add_global_decl("typedef struct { int x; } S;")
                   .add_global_decl("S s; S x = {5}; S y = {2};")
                   .add_global_decl("void f(bool b) { s = b? x : y; }")
                   .add_default_process()
                   .parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    const auto& warns = doc.get_warnings();
    CHECK_MESSAGE(warns.empty(), warns.front().msg);
}

TEST_CASE("Ternary operator with reference to integer array")
{
    auto doc = document_fixture{}
                   .add_global_decl("int x[2]; int y[2]; int z[2];")
                   .add_global_decl("void f(bool b) { z = (b?x:y); }")
                   .add_default_process()
                   .parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    const auto& warns = doc.get_warnings();
    CHECK_MESSAGE(warns.empty(), warns.front().msg);
}

TEST_CASE("Ternary operator with arrays clock and double")
{
    auto doc = document_fixture{}
                   .add_global_decl("clock c; double x[2]; void f(bool b) { x[0] = b ? c : x[1]; }")
                   .add_default_process()
                   .parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    const auto& warns = doc.get_warnings();
    CHECK_MESSAGE(warns.empty(), warns.front().msg);
}

TEST_CASE("Ternary operator with int and int expression 1")
{
    auto doc =
        document_fixture{}.add_global_decl("int x; void f(bool b) { x = b ? 0 : 1+1; }").add_default_process().parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    const auto& warns = doc.get_warnings();
    CHECK_MESSAGE(warns.empty(), warns.front().msg);
}

TEST_CASE("Ternary operator with int and int expression 2")
{
    auto doc =
        document_fixture{}.add_global_decl("int x; void f(bool b) { x = b ? 1+1 : 0; }").add_default_process().parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    const auto& warns = doc.get_warnings();
    CHECK_MESSAGE(warns.empty(), warns.front().msg);
}

TEST_CASE("Ternary operator with int expressions")
{
    auto doc = document_fixture{}
                   .add_global_decl("int x; void f(bool b) { x = b ? 1+1 : 1+1; }")
                   .add_default_process()
                   .parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    const auto& warns = doc.get_warnings();
    CHECK_MESSAGE(warns.empty(), warns.front().msg);
}

TEST_CASE("Ternary operator with int expressions")
{
    auto doc = document_fixture{}
                   .add_global_decl("int x; void f(bool b) { x = b ? 1+1 : 1.0+1.0; }")
                   .add_default_process()
                   .parse();
    const auto& errs = doc.get_errors();
    REQUIRE(errs.size() == 1);
    CHECK(errs[0].msg == "$Incompatible_types");
    const auto& warns = doc.get_warnings();
    CHECK_MESSAGE(warns.empty(), warns.front().msg);
}

TEST_CASE("Ternary operator with int expressions and clocks")
{
    auto doc = document_fixture{}
                   .add_global_decl("int x; clock c; void f(bool b) { x = b ? 1+1 : c; }")
                   .add_default_process()
                   .parse();
    const auto& errs = doc.get_errors();
    REQUIRE(errs.size() == 1);
    CHECK(errs[0].msg == "$Incompatible_types");
    const auto& warns = doc.get_warnings();
    CHECK_MESSAGE(warns.empty(), warns.front().msg);
}

TEST_CASE("Ternary operator with double expressions and clocks")
{
    auto doc = document_fixture{}
                   .add_global_decl("clock x; clock c; void f(bool b) { x = b ? 1+1 : c; }")
                   .add_default_process()
                   .parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    const auto& warns = doc.get_warnings();
    CHECK_MESSAGE(warns.empty(), warns.front().msg);
}

TEST_CASE("Ternary operator with struct clock and double")
{
    auto doc = document_fixture{}
                   .add_global_decl("struct{ clock c; double x; }z; void f(bool b) { z.x = b ? z.c : 1.0; }")
                   .add_default_process()
                   .parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    const auto& warns = doc.get_warnings();
    CHECK_MESSAGE(warns.empty(), warns.front().msg);
}

TEST_CASE("Ternary operator returning c++ reference to doubles with assignment")
{
    auto doc = document_fixture{}
                   .add_global_decl("clock c; double x[2]; void f(bool b) { (b?x[0]:x[1]) = c; }")
                   .add_default_process()
                   .parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    const auto& warns = doc.get_warnings();
    CHECK_MESSAGE(warns.empty(), warns.front().msg);
}

TEST_CASE("Ternary operator with two conversions into clock")
{
    auto doc = document_fixture{}
                   .add_global_decl("clock c; double x; void f(bool b) { c = b ? 1 : x+2.0; }")
                   .add_default_process()
                   .parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    const auto& warns = doc.get_warnings();
    CHECK_MESSAGE(warns.empty(), warns.front().msg);
}

TEST_CASE("Ternary operator with two conversions into double")
{
    auto doc = document_fixture{}
                   .add_global_decl("clock c; double x; void f(bool b) { x = b ? 1 : c+2.0; }")
                   .add_default_process()
                   .parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    const auto& warns = doc.get_warnings();
    CHECK_MESSAGE(warns.empty(), warns.front().msg);
}

TEST_CASE("Double in struct")
{
    auto doc = document_fixture{}.add_default_process().add_global_decl("struct { double x; } my_struct;").parse();
    auto errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    auto warns = doc.get_warnings();
    CHECK_MESSAGE(warns.empty(), warns.front().msg);
}

TEST_CASE("Clock in struct")
{
    auto doc = document_fixture{}.add_default_process().add_global_decl("struct { clock x; } my_struct;").parse();
    auto errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    auto warns = doc.get_warnings();
    CHECK_MESSAGE(warns.empty(), warns.front().msg);
}

TEST_CASE("Nested structs")
{
    auto doc = document_fixture{}
                   .add_default_process()
                   .add_global_decl("struct { struct { clock x; } nested; } my_struct;")
                   .parse();
    auto errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    auto warns = doc.get_warnings();
    CHECK_MESSAGE(warns.empty(), warns.front().msg);
}

TEST_CASE("Nested structs")
{
    auto doc = document_fixture{}
                   .add_default_process()
                   .add_global_decl("struct { int x; double y; } my_struct = {1.0, 1.0};")
                   .parse();
    const auto& errs = doc.get_errors();
    REQUIRE(errs.size() == 1);
    CHECK(errs[0].msg == "$Invalid_initialiser");
    const auto& warns = doc.get_warnings();
    CHECK_MESSAGE(warns.empty(), warns.front().msg);
}

TEST_SUITE("Statement forms")
{
    TEST_CASE("assert, empty, for, iteration and do-while statements")
    {
        auto doc = document_fixture{}
                       .add_default_process()
                       .add_global_decl("void f() {"
                                        "  int i;"
                                        "  int total = 0;"
                                        "  ;"  // empty statement
                                        "  assert(true);"
                                        "  for (i = 0; i < 3; i++) { total += i; }"
                                        "  for (i : int[0,2]) { total += i; }"
                                        "  do { total--; } while (total > 0);"
                                        "}")
                       .parse();
        const auto& errs = doc.get_errors();
        CHECK_MESSAGE(errs.empty(), errs.front().msg);
        const auto& warns = doc.get_warnings();
        CHECK_MESSAGE(warns.empty(), warns.front().msg);
    }
}

TEST_SUITE("Type prefix errors")
{
    TEST_CASE("meta not allowed for clocks")
    {
        auto doc = document_fixture{}
                       .add_default_process()
                       .add_global_decl("typedef clock ClockT; meta ClockT c;")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Prefix_meta_not_allowed_for_clocks");
    }

    TEST_CASE("const not allowed for clocks")
    {
        auto doc = document_fixture{}
                       .add_default_process()
                       .add_global_decl("typedef clock ClockT; const ClockT c = 0;")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Prefix_const_not_allowed_for_clocks");
    }

    TEST_CASE("urgent only allowed for locations and channels")
    {
        auto doc = document_fixture{}
                       .add_default_process()
                       .add_global_decl("typedef clock ClockT; urgent ClockT c;")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Prefix_urgent_only_allowed_for_locations_and_channels");
    }

    TEST_CASE("broadcast only allowed for channels")
    {
        auto doc = document_fixture{}
                       .add_default_process()
                       .add_global_decl("typedef clock ClockT; broadcast ClockT c;")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Prefix_broadcast_only_allowed_for_channels");
    }

    TEST_CASE("type cannot be declared const or meta")
    {
        auto doc = document_fixture{}.add_default_process().add_global_decl("meta chan c;").parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Type_cannot_be_declared_const_or_meta");
    }
}

TEST_SUITE("Expression type errors")
{
    TEST_CASE("invalid assignment expression")
    {
        auto doc = document_fixture{}
                       .add_default_process()
                       .add_global_decl("chan c; void f() { c; }")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Invalid_assignment_expression");
    }

    TEST_CASE("boolean expected in if-condition")
    {
        auto doc = document_fixture{}
                       .add_default_process()
                       .add_global_decl("clock c; void f() { if (c) {} }")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Boolean_expected");
    }

    TEST_CASE("invalid return type")
    {
        auto doc = document_fixture{}
                       .add_default_process()
                       .add_global_decl("clock clock_returning_function() { clock c; return c; }")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Invalid_return_type");
    }

    TEST_CASE("increment only integers and cost")
    {
        auto doc = document_fixture{}
                       .add_default_process()
                       .add_global_decl("void f() { double d; d += 1; }")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Increment_can_only_be_used_for_integers_and_cost_variables");
    }

    TEST_CASE("non-integer types must use regular assignment")
    {
        auto doc = document_fixture{}
                       .add_default_process()
                       .add_global_decl("void f() { double d; d -= 1; }")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Non-integer_types_must_use_regular_assignment_operator");
    }

    TEST_CASE("integer expected for increment/decrement")
    {
        auto doc = document_fixture{}
                       .add_default_process()
                       .add_global_decl("void f() { double d; d++; }")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Integer_expected");
    }

    TEST_CASE("array expected")
    {
        auto doc = document_fixture{}
                       .add_default_process()
                       .add_global_decl("void f() { int x; x[0] = 1; }")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Array_expected");
    }

    TEST_CASE("wrong number of arguments, too many")
    {
        auto doc = document_fixture{}
                       .add_default_process()
                       .add_global_decl("int f(int a) { return a; } void g() { f(1,2); }")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Too_many_arguments_for_function_call");
    }

    TEST_CASE("wrong number of arguments, too few")
    {
        auto doc = document_fixture{}
                       .add_default_process()
                       .add_global_decl("int f(int a, int b) { return a; } void g() { int x = f(1); }")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Too_few_arguments_for_function_call");
    }

    TEST_CASE("unknown field name and incomplete initialiser")
    {
        auto doc =
            document_fixture{}.add_default_process().add_global_decl("struct { int x; } s = {y: 1};").parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 2);
        CHECK(errs[0].msg == "$Unknown_field_name");
        CHECK(errs[1].msg == "$Incomplete_initialiser");
    }

    TEST_CASE("first argument of inline if must be an integer")
    {
        auto doc = document_fixture{}
                       .add_default_process()
                       .add_global_decl("int x = (1.5) ? 1 : 2;")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$First_argument_of_inline_if_must_be_an_integer");
    }

    TEST_CASE("multiple initialisers for the same field")
    {
        auto doc = document_fixture{}
                       .add_default_process()
                       .add_global_decl("struct { int x; } s = {x: 1, x: 2};")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Multiple_initialisers_for_field");
    }

    TEST_CASE("too many elements in initialiser")
    {
        auto doc =
            document_fixture{}.add_default_process().add_global_decl("struct { int x; } s = {1, 2};").parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Too_many_elements_in_initialiser");
    }

    TEST_CASE("spawn outside an edge, on a declared-but-undefined dynamic template")
    {
        // Exercises both template_only_declared_and_undefined (the
        // template has no body) and dynamic_constructs_supported_only_on_edges
        // (spawn is used in a function body, not on an edge update).
        auto doc = document_fixture{}
                       .add_default_process()
                       .add_global_decl("dynamic Child(); void f() { int x = spawn Child(); }")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 2);
        CHECK(errs[0].msg == "$Template_is_only_declared_and_not_defined");
        CHECK(errs[1].msg == "$Dynamic_constructs_supported_only_on_edges");
    }
}

TEST_SUITE("Document-based parse entry points")
{
    TEST_CASE("parse_XTA from a buffer")
    {
        static constexpr auto xta = R"XTA(
clock c;
process Template()
{
    state L0;
    init L0;
}
Process = Template();
system Process;
)XTA";
        auto doc = UTAP::Document{};
        CHECK(parse_XTA(xta, doc, true));
        const auto& errs = doc.get_errors();
        CHECK_MESSAGE(errs.empty(), errs.front().msg);
    }

    TEST_CASE("parse_XTA from a FILE*")
    {
        static constexpr auto xta = R"XTA(
clock c;
process Template()
{
    state L0;
    init L0;
}
Process = Template();
system Process;
)XTA";
        auto path = std::filesystem::temp_directory_path() / "utap_typechecker_test.xta";
        {
            auto ofs = std::ofstream{path};
            ofs << xta;
        }
        auto* file = std::fopen(path.string().c_str(), "r");
        REQUIRE(file != nullptr);
        auto doc = UTAP::Document{};
        auto ok = parse_XTA(file, doc, true);
        std::fclose(file);
        std::filesystem::remove(path);
        CHECK(ok);
        const auto& errs = doc.get_errors();
        CHECK_MESSAGE(errs.empty(), errs.front().msg);
    }

    TEST_CASE("parse_XML_fd from a file descriptor")
    {
        auto path = std::filesystem::temp_directory_path() / "utap_typechecker_test.xml";
        {
            auto ofs = std::ofstream{path};
            ofs << document_fixture{}.add_default_process().str();
        }
        auto* file = std::fopen(path.string().c_str(), "r");
        REQUIRE(file != nullptr);
        auto doc = UTAP::Document{};
        auto res = parse_XML_fd(fileno(file), doc, true);
        std::fclose(file);
        std::filesystem::remove(path);
        CHECK(res == 0);
        const auto& errs = doc.get_errors();
        CHECK_MESSAGE(errs.empty(), errs.front().msg);
    }

    TEST_CASE("parse_expression parses and type-checks a bare expression")
    {
        auto doc = UTAP::Document{};
        auto expr = parse_expression("1+1", doc, true);
        const auto& errs = doc.get_errors();
        CHECK_MESSAGE(errs.empty(), errs.front().msg);
        CHECK(expr.get_kind() == UTAP::Kind::PLUS);
    }
}

TEST_SUITE("SMC/probability property checks")
{
    // These SMC query forms exercise TypeChecker's PROBA_EXP/PROBA_BOX/
    // PROBA_DIAMOND/PROBA_CMP handling (checkNrOfRuns, checkBoundTypeOrBoundedExpr,
    // checkBound, checkAggregationOp, checkMonitoredExpr, checkPredicate,
    // checkUntilCond, checkPathQuant, checkProbBound), none of which any
    // existing test reached.
    static UTAP::Document make_doc()
    {
        return document_fixture{}.add_default_process().add_global_decl("clock c; bool b;").parse();
    }

    TEST_CASE("expected value query (min aggregation)")
    {
        auto doc = make_doc();
        auto qb = QueryBuilder{doc};
        auto res = parse_property("E[<=10;100] (min: c)", qb);
        REQUIRE(res == 0);
        qb.typecheck();
        const auto& errs = doc.get_errors();
        CHECK_MESSAGE(errs.empty(), errs.front().msg);
    }

    TEST_CASE("probability of eventually reaching a predicate")
    {
        auto doc = make_doc();
        auto qb = QueryBuilder{doc};
        auto res = parse_property("Pr[<=10;100](<> b)", qb);
        REQUIRE(res == 0);
        qb.typecheck();
        const auto& errs = doc.get_errors();
        CHECK_MESSAGE(errs.empty(), errs.front().msg);
    }

    TEST_CASE("probability comparison between two runs")
    {
        auto doc = make_doc();
        auto qb = QueryBuilder{doc};
        auto res = parse_property("Pr[<=10](<> b) >= Pr[<=10](<> b)", qb);
        REQUIRE(res == 0);
        qb.typecheck();
        const auto& errs = doc.get_errors();
        CHECK_MESSAGE(errs.empty(), errs.front().msg);
    }

    TEST_CASE("probability quantitative comparison against a threshold")
    {
        auto doc = make_doc();
        auto qb = QueryBuilder{doc};
        auto res = parse_property("Pr[<=10;100](<> b) <= 0.5", qb);
        REQUIRE(res == 0);
        qb.typecheck();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Explicit_number_of_runs_is_not_supported_here");
    }

    TEST_CASE("simulate query")
    {
        auto doc = make_doc();
        auto qb = QueryBuilder{doc};
        auto res = parse_property("simulate[<=10;100] {b}", qb);
        REQUIRE(res == 0);
        qb.typecheck();
        const auto& errs = doc.get_errors();
        CHECK_MESSAGE(errs.empty(), errs.front().msg);
    }
}

TEST_SUITE("More expression and edge errors")
{
    TEST_CASE("edge guard must be side-effect free")
    {
        auto doc = document_fixture{}
                       .add_global_decl("int i;")
                       .add_template(R"XML(<template>
        <name>T</name>
        <location id="id0" x="0" y="0"/>
        <location id="id1" x="10" y="10"/>
        <init ref="id0"/>
        <transition>
            <source ref="id0"/>
            <target ref="id1"/>
            <label kind="guard">(i++ &gt; 0)</label>
        </transition>
    </template>)XML")
                       .add_system_decl("Process = T();")
                       .add_process("Process")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Expression_must_be_side-effect_free");
    }

    TEST_CASE("channel expected for edge synchronisation")
    {
        auto doc = document_fixture{}
                       .add_global_decl("chan c[2];")
                       .add_template(R"XML(<template>
        <name>T</name>
        <location id="id0" x="0" y="0"/>
        <location id="id1" x="10" y="10"/>
        <init ref="id0"/>
        <transition>
            <source ref="id0"/>
            <target ref="id1"/>
            <label kind="synchronisation">c</label>
        </transition>
    </template>)XML")
                       .add_system_decl("Process = T();")
                       .add_process("Process")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Channel_expected");
    }

    TEST_CASE("scalar set or integer expected for iteration variable")
    {
        auto doc = document_fixture{}
                       .add_default_process()
                       .add_global_decl("void f() { for (i : bool) {} }")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Scalar_set_or_integer_expected");
    }

    TEST_CASE("field name not allowed in array initialiser")
    {
        auto doc =
            document_fixture{}.add_default_process().add_global_decl("int a[2] = {x: 1, 2};").parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Field_name_not_allowed_in_array_initialiser");
    }

    TEST_CASE("global struct initialiser with out-of-order named fields is reordered to match field declaration order")
    {
        // Regression test: TypeChecker::visit_variable used to discard the
        // Expression returned by checkInitialiser() for global/const variables,
        // so field reordering performed by checkInitialiser (for out-of-order
        // named initialisers) never made it back into variable.init.
        auto doc = document_fixture{}
                       .add_default_process()
                       .add_global_decl("struct { int x; int y; } s = {y: 2, x: 1};")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE_MESSAGE(errs.empty(), (errs.empty() ? "" : errs.front().msg));
        const auto& vars = doc.get_globals().variables;
        auto it = std::find_if(vars.begin(), vars.end(), [](const auto& v) { return v.uid.get_name() == "s"; });
        REQUIRE(it != vars.end());
        REQUIRE(it->init.get_size() == 2);
        CHECK(it->init[0].get_value() == 1);  // x, declared first
        CHECK(it->init[1].get_value() == 2);  // y, declared second
    }

    TEST_CASE("local array-of-struct initialiser with out-of-order named fields is reordered, not corrupted")
    {
        // Regression test: checkInitialiser's array branch called
        // checkInitialiser(subtype, init[i]) recursively but discarded the
        // result instead of storing it in result[i], leaving the returned
        // LIST full of empty (default-constructed) sub-expressions whenever
        // per-element coercion/reordering was needed (e.g. array of structs
        // with out-of-order named fields). Only reachable for local
        // variables, since visit_block_statement (unlike visit_variable)
        // does use checkInitialiser's return value.
        auto doc = document_fixture{}
                       .add_default_process()
                       .add_global_decl("typedef struct { int x; int y; } Point;"
                                        "void f() { Point arr[2] = {{y: 2, x: 1}, {y: 4, x: 3}}; }")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE_MESSAGE(errs.empty(), (errs.empty() ? "" : errs.front().msg));
        const auto& functions = doc.get_globals().functions;
        auto fit = std::find_if(functions.begin(), functions.end(), [](const auto& fn) { return fn.uid.get_name() == "f"; });
        REQUIRE(fit != functions.end());
        auto vit = std::find_if(fit->variables.begin(), fit->variables.end(),
                                [](const auto& v) { return v.uid.get_name() == "arr"; });
        REQUIRE(vit != fit->variables.end());
        REQUIRE(vit->init.get_size() == 2);
        REQUIRE(!vit->init[0].empty());
        REQUIRE(!vit->init[1].empty());
        REQUIRE(vit->init[0].get_size() == 2);
        CHECK(vit->init[0][0].get_value() == 1);  // x, declared first
        CHECK(vit->init[0][1].get_value() == 2);  // y, declared second
        CHECK(vit->init[1][0].get_value() == 3);
        CHECK(vit->init[1][1].get_value() == 4);
    }

    TEST_CASE("number expected and unknown type in sum body")
    {
        auto doc = document_fixture{}
                       .add_default_process()
                       .add_global_decl("chan carr[3]; void f() { int x = sum(i:int[0,2]) carr[i]; }")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 2);
        CHECK(errs[0].msg == "$Number_expected");
        CHECK(errs[1].msg == "$Unknown_type_of_the_expression");
    }

    static UTAP::Document parse_with_progress(const std::string& progress_decl)
    {
        // The `progress { ... }` block must follow the `system ...;` line
        // (grammar: System: SysDecl Progress GanttDecl), which
        // document_fixture::add_system_decl() cannot express since it
        // inserts text before that line -- build the document manually.
        auto doc = UTAP::Document{};
        auto xml = std::string{R"XML(<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE nta PUBLIC '-//Uppaal Team//DTD Flat System 1.6//EN' 'https://www.it.uu.se/research/group/darts/uppaal/flat-1_6.dtd'>
<nta>
    <declaration>clock c;</declaration>
    <template>
        <name x="5" y="5">Template</name>
        <location id="id0" x="0" y="0"/>
        <init ref="id0"/>
    </template>
    <system>
Process = Template();
system Process;
)XML"} + progress_decl + "\n    </system>\n</nta>\n";
        parse_XML_buffer(xml.c_str(), doc, true);
        return doc;
    }

    TEST_CASE("progress guard must evaluate to a boolean value")
    {
        auto doc = parse_with_progress("progress { c : 1; }");
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Progress_guard_must_evaluate_to_a_boolean_value");
    }

    TEST_CASE("progress measure must evaluate to an integer value")
    {
        auto doc = parse_with_progress("progress { true : c; }");
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Progress_measure_must_evaluate_to_a_integer_value");
    }

    TEST_CASE("incompatible type for array index")
    {
        auto doc = document_fixture{}
                       .add_default_process()
                       .add_global_decl("int a[3]; void f() { clock c; int x = a[c]; }")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Incompatible_type");
    }

    TEST_CASE("incompatible type for comma expression")
    {
        auto doc = document_fixture{}
                       .add_default_process()
                       .add_global_decl("chan c; void f() { int i; for (i = 0, c; i < 1; i++) {} }")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Incompatible_type_for_comma_expression");
    }

    TEST_CASE("incompatible argument: reference parameter given a non-unique-reference argument")
    {
        // Also exercises isUniqueReference(), which returns false for a
        // literal passed where a non-const reference parameter is expected.
        auto doc = document_fixture{}
                       .add_template(template_fixture{"T"}.add_parameter("int& x").str())
                       .add_system_decl("Process = T(5);")
                       .add_process("Process")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Incompatible_argument");
    }

    TEST_CASE("spawning a fully-defined dynamic template with matching arguments on an edge")
    {
        // Exercises checkSpawnParameterCompatible() on the success path.
        auto doc = document_fixture{}
                       .add_global_decl("dynamic Child(int p);")
                       .add_template(R"XML(<template>
        <name>Child</name>
        <parameter>int p</parameter>
        <location id="id0" x="0" y="0"/>
        <init ref="id0"/>
    </template>)XML")
                       .add_template(R"XML(<template>
        <name>Parent</name>
        <location id="id0" x="0" y="0"/>
        <location id="id1" x="10" y="10"/>
        <init ref="id0"/>
        <transition>
            <source ref="id0"/>
            <target ref="id1"/>
            <label kind="assignment">spawn Child(1)</label>
        </transition>
    </template>)XML")
                       .add_system_decl("Process = Parent();")
                       .add_process("Process")
                       .parse();
        const auto& errs = doc.get_errors();
        CHECK_MESSAGE(errs.empty(), errs.front().msg);
    }
}

TEST_SUITE("CSP/refinement and urgent/deterministic edge checks")
{
    TEST_CASE("urgent edge with a clock guard and a strict bound")
    {
        // Exercises both clock_guards_not_allowed_on_urgent_edges and
        // strict_bounds_on_urgent_edges, since an urgent channel with a
        // strict clock upper bound guard hits both independent checks.
        auto doc = document_fixture{}
                       .add_global_decl("urgent chan c; clock x;")
                       .add_template(R"XML(<template>
        <name>T</name>
        <location id="id0" x="0" y="0"/>
        <location id="id1" x="10" y="10"/>
        <init ref="id0"/>
        <transition>
            <source ref="id0"/>
            <target ref="id1"/>
            <label kind="guard">x &lt; 5</label>
            <label kind="synchronisation">c!</label>
        </transition>
    </template>)XML")
                       .add_system_decl("Process = T();")
                       .add_process("Process")
                       .parse();
        const auto& errs = doc.get_errors();
        CHECK_MESSAGE(errs.empty(), errs.front().msg);
        const auto& warns = doc.get_warnings();
        REQUIRE(warns.size() == 2);
        CHECK(warns[0].msg == "$Clock_guards_are_not_allowed_on_urgent_edges");
        CHECK(warns[1].msg == "$Strict_bounds_on_urgent_edges_may_not_make_sense");
    }

    TEST_CASE("broadcast input edge into a branchpoint must be deterministic")
    {
        auto doc = document_fixture{}
                       .add_global_decl("broadcast chan c;")
                       .add_template(R"XML(<template>
        <name>T</name>
        <location id="id0" x="0" y="0"/>
        <branchpoint id="id1" x="10" y="10"/>
        <init ref="id0"/>
        <transition>
            <source ref="id0"/>
            <target ref="id1"/>
            <label kind="synchronisation">c?</label>
        </transition>
    </template>)XML")
                       .add_system_decl("Process = T();")
                       .add_process("Process")
                       .parse();
        const auto& errs = doc.get_errors();
        CHECK_MESSAGE(errs.empty(), errs.front().msg);
        const auto& warns = doc.get_warnings();
        REQUIRE(warns.size() == 1);
        CHECK(warns[0].msg == "SMC requires input edges to be deterministic");
    }

    TEST_CASE("broadcast input edge into a location with a non-true invariant")
    {
        auto doc = document_fixture{}
                       .add_global_decl("broadcast chan c; clock x;")
                       .add_template(R"XML(<template>
        <name>T</name>
        <location id="id0" x="0" y="0"/>
        <location id="id1" x="10" y="10">
            <label kind="invariant">x &lt; 5</label>
        </location>
        <init ref="id0"/>
        <transition>
            <source ref="id0"/>
            <target ref="id1"/>
            <label kind="synchronisation">c?</label>
        </transition>
    </template>)XML")
                       .add_system_decl("Process = T();")
                       .add_process("Process")
                       .parse();
        const auto& errs = doc.get_errors();
        CHECK_MESSAGE(errs.empty(), errs.front().msg);
#ifndef NDEBUG
        // This warning is only compiled in debug builds (see visit_edge in TypeChecker.cpp).
        const auto& warns = doc.get_warnings();
        bool found = false;
        for (const auto& w : warns)
            found |= (w.msg == "$It_may_be_needed_to_add_a_guard_involving_the_target_invariant");
        CHECK(found);
#endif
    }

    TEST_CASE("mixing CSP-style and IO-style synchronisation is not allowed")
    {
        auto doc = document_fixture{}
                       .add_global_decl("chan c;")
                       .add_template(R"XML(<template>
        <name>T</name>
        <location id="id0" x="0" y="0"/>
        <location id="id1" x="10" y="10"/>
        <location id="id2" x="20" y="20"/>
        <init ref="id0"/>
        <transition>
            <source ref="id0"/>
            <target ref="id1"/>
            <label kind="synchronisation">c!</label>
        </transition>
        <transition>
            <source ref="id1"/>
            <target ref="id2"/>
            <label kind="synchronisation">c</label>
        </transition>
    </template>)XML")
                       .add_system_decl("Process = T();")
                       .add_process("Process")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$CSP_and_IO_synchronisations_cannot_be_mixed");
    }

    // The remaining refinement-only checks (outputs_should_be_uncontrollable,
    // inputs_should_be_controllable, csp_sync_is_incompatible_with_refinement_checking)
    // only run when TypeChecker is constructed with refinement=true, which
    // static_analysis() (used by every parse_XTA/parse_XML_* overload) never
    // does -- so a document must be re-visited manually with a
    // refinement-enabled checker to reach them.
    TEST_CASE("refinement warnings: uncontrollable output, controllable input, CSP incompatibility")
    {
        auto doc = document_fixture{}
                       .add_global_decl("chan c;")
                       .add_template(R"XML(<template>
        <name>T</name>
        <location id="id0" x="0" y="0"/>
        <location id="id1" x="10" y="10"/>
        <location id="id2" x="20" y="20"/>
        <init ref="id0"/>
        <transition>
            <source ref="id0"/>
            <target ref="id1"/>
            <label kind="synchronisation">c!</label>
        </transition>
        <transition>
            <source ref="id1"/>
            <target ref="id2"/>
            <label kind="synchronisation">c</label>
        </transition>
    </template>)XML")
                       .add_system_decl("Process = T();")
                       .add_process("Process")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$CSP_and_IO_synchronisations_cannot_be_mixed");

        auto checker = UTAP::TypeChecker{doc, true};
        doc.accept(checker);

        const auto& warns = doc.get_warnings();
        bool has_output_warning = false;
        bool has_csp_refinement_warning = false;
        for (const auto& w : warns) {
            has_output_warning |= (w.msg == "$Outputs_should_be_uncontrollable_for_refinement_checking");
            has_csp_refinement_warning |= (w.msg == "$CSP_synchronisations_are_incompatible_with_refinement_checking");
        }
        CHECK(has_output_warning);
        CHECK(has_csp_refinement_warning);
    }

    TEST_CASE("refinement warning: input edge should be controllable")
    {
        auto doc = document_fixture{}
                       .add_global_decl("chan c;")
                       .add_template(R"XML(<template>
        <name>T</name>
        <location id="id0" x="0" y="0"/>
        <location id="id1" x="10" y="10"/>
        <init ref="id0"/>
        <transition controllable="false">
            <source ref="id0"/>
            <target ref="id1"/>
            <label kind="synchronisation">c?</label>
        </transition>
    </template>)XML")
                       .add_system_decl("Process = T();")
                       .add_process("Process")
                       .parse();
        const auto& errs = doc.get_errors();
        CHECK_MESSAGE(errs.empty(), errs.front().msg);

        auto checker = UTAP::TypeChecker{doc, true};
        doc.accept(checker);

        const auto& warns = doc.get_warnings();
        bool found = false;
        for (const auto& w : warns)
            found |= (w.msg == "$Inputs_should_be_controllable_for_refinement_checking");
        CHECK(found);
    }
}

TEST_SUITE("checkType coverage")
{
    TEST_CASE("reference to a disallowed type (void) is rejected")
    {
        auto doc = document_fixture{}.add_global_decl("void f(void &x) {}").add_default_process().parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Reference_to_this_type_is_not_allowed");
    }

    TEST_CASE("bounded-int range with a non-integer bound")
    {
        auto doc =
            document_fixture{}.add_global_decl("double d = 1.5; int[0,d] x;").add_default_process().parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 2);
        CHECK(errs[0].msg == "$Integer_expected");
        CHECK(errs[1].msg == "$Must_be_computable_at_compile_time");
    }

    TEST_CASE("bounded-int range with a non-const bound")
    {
        auto doc = document_fixture{}.add_global_decl("int g(int p){ int[0,p] a; return 0; }")
                       .add_default_process()
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Must_be_computable_at_compile_time");
    }

    TEST_CASE("a const string declaration is accepted at top level but not inside a struct")
    {
        // Strings must always be const (StatementBuilder::type_string rejects
        // a non-const string before checkType is even reached), so a plain
        // "string s;" never reaches checkType's STRING case at all.
        auto doc =
            document_fixture{}.add_global_decl("const string s = \"abc\";").add_default_process().parse();
        CHECK(doc.get_errors().empty());

        // Inside a struct, const-qualified fields are separately rejected
        // (constant_fields_not_allowed_in_struct), in addition to the
        // STRING-specific cannot_be_inside_struct check we're targeting.
        auto doc2 = document_fixture{}
                        .add_global_decl("typedef struct { const string s; } Rec;")
                        .add_default_process()
                        .parse();
        const auto& errs = doc2.get_errors();
        REQUIRE(errs.size() == 2);
        bool found = false;
        for (const auto& e : errs)
            found |= (e.msg == "$Invalid_type_in_structure");
        CHECK(found);
    }

    TEST_CASE("a committed location type-checks without error")
    {
        auto doc = document_fixture{}
                       .add_template(R"XML(<template>
        <name>T</name>
        <location id="id0" x="0" y="0"><committed/></location>
        <init ref="id0"/>
    </template>)XML")
                       .add_system_decl("Process = T();")
                       .add_process("Process")
                       .parse();
        CHECK(doc.get_errors().empty());
    }
}

TEST_SUITE("Priority declarations: arrays and errors")
{
    TEST_CASE("priority declarations accept array-of-channel and indexed-channel elements")
    {
        auto doc = document_fixture{}
                       .add_global_decl("chan a[2]; chan b; chan priority a < b;")
                       .add_default_process()
                       .parse();
        CHECK(doc.get_errors().empty());

        auto doc2 = document_fixture{}
                        .add_global_decl("chan a[2]; chan b; chan priority a[0] < b;")
                        .add_default_process()
                        .parse();
        CHECK(doc2.get_errors().empty());
    }

    TEST_CASE("a priority element that is not a channel is rejected")
    {
        auto doc = document_fixture{}
                       .add_global_decl("int x; chan b; chan priority x < b;")
                       .add_default_process()
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Channel_expected");
    }
}

TEST_SUITE("visit_process/visit_variable/visit_location gaps")
{
    TEST_CASE("unbound process parameters must be a bounded integer or scalar")
    {
        // "process P(...) { ... } system P;" (using the template directly in
        // the system list without instantiating it) leaves P's parameter
        // unbound -- the only way to reach TypeChecker::visit_process's
        // per-parameter checks.
        auto doc = UTAP::Document{};
        REQUIRE(parse_XTA(R"XTA(
process P(bool x) {
    state s0;
    init s0;
}
system P;
)XTA",
                          doc, true) == false);
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Free_process_parameters_must_be_a_bounded_integer_or_a_scalar");
    }

    TEST_CASE("unbound process parameters must not be used in an array size or select expression")
    {
        auto doc = UTAP::Document{};
        REQUIRE(parse_XTA(R"XTA(
process P(int[0,2] x) {
    int a[x];
    state s0;
    init s0;
}
system P;
)XTA",
                          doc, true) == false);
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 2);
        bool found = false;
        for (const auto& e : errs)
            found |= (e.msg == "$Free_process_parameters_must_not_be_used_directly_or_indirectly_in_an_array_"
                                "declaration_or_select_expression");
        CHECK(found);
    }

    TEST_CASE("a variable initialiser using a dynamic construct is rejected")
    {
        auto doc = document_fixture{}
                       .add_global_decl("dynamic Child();")
                       .add_template(R"XML(<template>
        <name>Child</name>
        <location id="id0" x="0" y="0"/>
        <init ref="id0"/>
    </template>)XML")
                       .add_global_decl("int x = spawn Child();")
                       .add_default_process()
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "Dynamic constructions cannot be used as initialisers");
    }

    TEST_CASE("a location invariant of an incompatible type is rejected")
    {
        auto doc = document_fixture{}
                       .add_global_decl("chan ch;")
                       .add_template(R"XML(<template>
        <name>T</name>
        <location id="id0" x="0" y="0"><label kind="invariant">ch</label></location>
        <init ref="id0"/>
    </template>)XML")
                       .add_system_decl("Process = T();")
                       .add_process("Process")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Expression_of_type (channel) $cannot_be_used_as_an_invariant");
    }

    TEST_CASE("a side-effecting location invariant is rejected")
    {
        auto doc = document_fixture{}
                       .add_global_decl("clock c; bool b;")
                       .add_template(R"XML(<template>
        <name>T</name>
        <location id="id0" x="0" y="0"><label kind="invariant">c&lt;5 &amp;&amp; (b=true)</label></location>
        <init ref="id0"/>
    </template>)XML")
                       .add_system_decl("Process = T();")
                       .add_process("Process")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Expression_must_be_side-effect_free");
    }

    TEST_CASE("an exponential rate of an incompatible type is rejected")
    {
        auto doc = document_fixture{}
                       .add_global_decl("chan ch;")
                       .add_template(R"XML(<template>
        <name>T</name>
        <location id="id0" x="0" y="0"><label kind="exponentialrate">ch</label></location>
        <init ref="id0"/>
    </template>)XML")
                       .add_system_decl("Process = T();")
                       .add_process("Process")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Number_expected");
    }
}

TEST_SUITE("visit_io_decl (IODecl) coverage")
{
    // The "IO" keyword is registered in keywords.cpp/lexer.l (Syntax::NEW),
    // but no grammar production in parser.y ever consumes the T_IO token,
    // so IODecl can only ever be populated and checked by constructing it
    // directly via Document::add_io_decl() and TypeChecker::visit_io_decl(),
    // as done throughout this suite.
    static UTAP::Document make_doc()
    {
        auto doc = document_fixture{}
                       .add_global_decl("const int p = 1; chan ch; chan ch_arr[2]; int nonconst; bool b;")
                       .add_default_process()
                       .parse();
        REQUIRE(doc.get_errors().empty());
        return doc;
    }

    TEST_CASE("a well-formed param, channel input and array-indexed output type-check without error")
    {
        auto doc = make_doc();
        UTAP::Symbol p_sym, ch_sym, arr_sym;
        REQUIRE(doc.get_globals().frame.resolve("p", p_sym));
        REQUIRE(doc.get_globals().frame.resolve("ch", ch_sym));
        REQUIRE(doc.get_globals().frame.resolve("ch_arr", arr_sym));

        auto* iodecl = doc.add_io_decl();
        iodecl->param.push_back(UTAP::Expression::create_identifier(p_sym));
        iodecl->inputs.push_back(UTAP::Expression::create_identifier(ch_sym));
        iodecl->outputs.push_back(UTAP::Expression::create_binary(
            UTAP::Kind::ARRAY, UTAP::Expression::create_identifier(arr_sym), UTAP::Expression::create_constant(0)));

        auto checker = UTAP::TypeChecker{doc};
        checker.visit_io_decl(*iodecl);
        CHECK(doc.get_errors().empty());
    }

    TEST_CASE("a non-integer param is rejected")
    {
        auto doc = make_doc();
        UTAP::Symbol b_sym;
        REQUIRE(doc.get_globals().frame.resolve("b", b_sym));
        auto* iodecl = doc.add_io_decl();
        iodecl->param.push_back(UTAP::Expression::create_identifier(b_sym));

        auto checker = UTAP::TypeChecker{doc};
        checker.visit_io_decl(*iodecl);
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Integer_expected");
    }

    TEST_CASE("a non-channel input is rejected")
    {
        auto doc = make_doc();
        UTAP::Symbol nc_sym;
        REQUIRE(doc.get_globals().frame.resolve("nonconst", nc_sym));
        auto* iodecl = doc.add_io_decl();
        iodecl->inputs.push_back(UTAP::Expression::create_identifier(nc_sym));

        auto checker = UTAP::TypeChecker{doc};
        checker.visit_io_decl(*iodecl);
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Channel_expected");
    }

    TEST_CASE("a non-compile-time-computable output array index is rejected")
    {
        auto doc = make_doc();
        UTAP::Symbol arr_sym, nc_sym;
        REQUIRE(doc.get_globals().frame.resolve("ch_arr", arr_sym));
        REQUIRE(doc.get_globals().frame.resolve("nonconst", nc_sym));
        auto* iodecl = doc.add_io_decl();
        iodecl->outputs.push_back(UTAP::Expression::create_binary(
            UTAP::Kind::ARRAY, UTAP::Expression::create_identifier(arr_sym), UTAP::Expression::create_identifier(nc_sym)));

        auto checker = UTAP::TypeChecker{doc};
        checker.visit_io_decl(*iodecl);
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Must_be_computable_at_compile_time");
    }

    TEST_CASE("a CSP-style iodecl followed by an IO-style one is rejected")
    {
        // Regression test: visit_io_decl's mismatch handler used to
        // unconditionally reference iodecl.csp.front(), but when the
        // mismatch is triggered by *this* iodecl's inputs/outputs (having
        // followed a previous CSP-style iodecl), its own csp list is empty
        // -- .front() on that empty std::list was undefined behaviour
        // (observed as an assertion failure / crash in practice).
        auto doc = make_doc();
        UTAP::Symbol ch_sym;
        REQUIRE(doc.get_globals().frame.resolve("ch", ch_sym));

        auto* iodecl1 = doc.add_io_decl();
        iodecl1->csp.push_back(UTAP::Expression::create_identifier(ch_sym));
        auto* iodecl2 = doc.add_io_decl();
        iodecl2->inputs.push_back(UTAP::Expression::create_identifier(ch_sym));

        auto checker = UTAP::TypeChecker{doc};
        CHECK_NOTHROW(checker.visit_io_decl(*iodecl1));
        CHECK_NOTHROW(checker.visit_io_decl(*iodecl2));
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$CSP_and_IO_synchronisations_cannot_be_mixed");
    }
}

TEST_SUITE("visit_edge gaps")
{
    TEST_CASE("a guard of an incompatible type is rejected")
    {
        auto doc = document_fixture{}
                       .add_global_decl("chan ch;")
                       .add_template(R"XML(<template>
        <name>T</name>
        <location id="id0" x="0" y="0"/>
        <location id="id1" x="10" y="10"/>
        <init ref="id0"/>
        <transition><source ref="id0"/><target ref="id1"/><label kind="guard">ch</label></transition>
    </template>)XML")
                       .add_system_decl("Process = T();")
                       .add_process("Process")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Expression_of_type (channel) $cannot_be_used_as_a_guard");
    }

    TEST_CASE("a side-effecting guard is rejected")
    {
        auto doc = document_fixture{}
                       .add_global_decl("bool b;")
                       .add_template(R"XML(<template>
        <name>T</name>
        <location id="id0" x="0" y="0"/>
        <location id="id1" x="10" y="10"/>
        <init ref="id0"/>
        <transition><source ref="id0"/><target ref="id1"/><label kind="guard">b=true</label></transition>
    </template>)XML")
                       .add_system_decl("Process = T();")
                       .add_process("Process")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Expression_must_be_side-effect_free");
    }

    TEST_CASE("a probability of an incompatible type is rejected")
    {
        auto doc = document_fixture{}
                       .add_global_decl("chan ch;")
                       .add_template(R"XML(<template>
        <name>T</name>
        <location id="id0" x="0" y="0"/>
        <location id="id1" x="10" y="10"/>
        <init ref="id0"/>
        <transition><source ref="id0"/><target ref="id1"/><label kind="probability">ch</label></transition>
    </template>)XML")
                       .add_system_decl("Process = T();")
                       .add_process("Process")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Expression_of_type (channel) $cannot_be_used_as_a_probability");
    }

    TEST_CASE("a side-effecting probability is rejected")
    {
        auto doc = document_fixture{}
                       .add_global_decl("int x;")
                       .add_template(R"XML(<template>
        <name>T</name>
        <location id="id0" x="0" y="0"/>
        <location id="id1" x="10" y="10"/>
        <init ref="id0"/>
        <transition><source ref="id0"/><target ref="id1"/><label kind="probability">(x=1)</label></transition>
    </template>)XML")
                       .add_system_decl("Process = T();")
                       .add_process("Process")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Expression_must_be_side-effect_free");
    }

    TEST_CASE("CSP-style synchronisation followed by IO-style is also rejected (reverse of the IO-then-CSP order)")
    {
        auto doc = document_fixture{}
                       .add_global_decl("chan c;")
                       .add_template(R"XML(<template>
        <name>T</name>
        <location id="id0" x="0" y="0"/>
        <location id="id1" x="10" y="10"/>
        <location id="id2" x="20" y="20"/>
        <init ref="id0"/>
        <transition><source ref="id0"/><target ref="id1"/><label kind="synchronisation">c</label></transition>
        <transition><source ref="id1"/><target ref="id2"/><label kind="synchronisation">c!</label></transition>
    </template>)XML")
                       .add_system_decl("Process = T();")
                       .add_process("Process")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$CSP_and_IO_synchronisations_cannot_be_mixed");
    }
}

TEST_SUITE("LSC message/condition error branches")
{
    TEST_CASE("an LSC message label that is not a channel is rejected")
    {
        auto doc = document_fixture{}
                       .add_global_decl("int notchan;")
                       .add_template(R"XML(<template>
        <name>A</name>
        <location id="id0" x="0" y="0"/>
        <init ref="id0"/>
    </template>)XML")
                       .add_template(R"XML(<lsc>
        <name>LscTemplate</name>
        <type>Universal</type>
        <mode>invariant</mode>
        <instance id="id1" x="0" y="0"><name x="0" y="0">A</name></instance>
        <instance id="id2" x="100" y="0"><name x="0" y="0">A</name></instance>
        <prechart x="0" y="0"><lsclocation>0</lsclocation></prechart>
        <message x="0" y="20">
            <source ref="id1"/><target ref="id2"/><lsclocation>1</lsclocation>
            <label kind="message">notchan</label>
        </message>
    </lsc>)XML")
                       .add_system_decl("P1 = A(); P2 = A();")
                       .add_process("P1")
                       .add_process("P2")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Channel_expected");
    }

    TEST_CASE("a side-effecting LSC message label is rejected")
    {
        auto doc = document_fixture{}
                       .add_global_decl("chan ch_arr[2]; int x;")
                       .add_template(R"XML(<template>
        <name>A</name>
        <location id="id0" x="0" y="0"/>
        <init ref="id0"/>
    </template>)XML")
                       .add_template(R"XML(<lsc>
        <name>LscTemplate</name>
        <type>Universal</type>
        <mode>invariant</mode>
        <instance id="id1" x="0" y="0"><name x="0" y="0">A</name></instance>
        <instance id="id2" x="100" y="0"><name x="0" y="0">A</name></instance>
        <prechart x="0" y="0"><lsclocation>0</lsclocation></prechart>
        <message x="0" y="20">
            <source ref="id1"/><target ref="id2"/><lsclocation>1</lsclocation>
            <label kind="message">ch_arr[x=1]</label>
        </message>
    </lsc>)XML")
                       .add_system_decl("P1 = A(); P2 = A();")
                       .add_process("P1")
                       .add_process("P2")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Expression_must_be_side-effect_free");
    }

    TEST_CASE("an LSC condition label that cannot be used as a condition is rejected")
    {
        auto doc = document_fixture{}
                       .add_global_decl("chan ch;")
                       .add_template(R"XML(<template>
        <name>A</name>
        <location id="id0" x="0" y="0"/>
        <init ref="id0"/>
    </template>)XML")
                       .add_template(R"XML(<lsc>
        <name>LscTemplate</name>
        <type>Universal</type>
        <mode>invariant</mode>
        <instance id="id1" x="0" y="0"><name x="0" y="0">A</name></instance>
        <prechart x="0" y="0"><lsclocation>0</lsclocation></prechart>
        <condition x="0" y="20">
            <anchor instanceid="id1"/><lsclocation>1</lsclocation><temperature>cold</temperature>
            <label kind="condition">ch</label>
        </condition>
    </lsc>)XML")
                       .add_system_decl("P1 = A();")
                       .add_process("P1")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Expression_of_type (channel) $cannot_be_used_as_a_condition");
    }

    TEST_CASE("a side-effecting LSC condition label is rejected")
    {
        auto doc = document_fixture{}
                       .add_global_decl("bool b;")
                       .add_template(R"XML(<template>
        <name>A</name>
        <location id="id0" x="0" y="0"/>
        <init ref="id0"/>
    </template>)XML")
                       .add_template(R"XML(<lsc>
        <name>LscTemplate</name>
        <type>Universal</type>
        <mode>invariant</mode>
        <instance id="id1" x="0" y="0"><name x="0" y="0">A</name></instance>
        <prechart x="0" y="0"><lsclocation>0</lsclocation></prechart>
        <condition x="0" y="20">
            <anchor instanceid="id1"/><lsclocation>1</lsclocation><temperature>cold</temperature>
            <label kind="condition">b=true</label>
        </condition>
    </lsc>)XML")
                       .add_system_decl("P1 = A();")
                       .add_process("P1")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Expression_must_be_side-effect_free");
    }
}

TEST_SUITE("visit_instance argument compatibility")
{
    TEST_CASE("a side-effecting instantiation argument is rejected")
    {
        auto doc = document_fixture{}
                       .add_global_decl("int x; process T(int p) { state s0; init s0; }")
                       .add_system_decl("Process = T(x=1);")
                       .add_process("Process")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Expression_must_be_side-effect_free");
    }

    TEST_CASE("a value-parameter argument that is not compile-time computable is rejected")
    {
        auto doc = document_fixture{}
                       .add_global_decl("int g; process T(int p) { state s0; init s0; }")
                       .add_system_decl("Process = T(g);")
                       .add_process("Process")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Incompatible_argument");
    }

    TEST_CASE("a const-reference argument that is not compile-time computable is rejected")
    {
        auto doc = document_fixture{}
                       .add_global_decl("int g; process T(const int &p) { state s0; init s0; }")
                       .add_system_decl("Process = T(g);")
                       .add_process("Process")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Incompatible_argument");
    }

    TEST_CASE("a non-const-reference argument accepts an identifier, a struct field and an array element")
    {
        auto doc1 = document_fixture{}
                        .add_global_decl("int x; process T(int &p) { state s0; init s0; }")
                        .add_system_decl("Process2 = T(x);")
                        .add_process("Process2")
                        .parse();
        CHECK(doc1.get_errors().empty());

        auto doc2 = document_fixture{}
                        .add_global_decl("typedef struct { int f; } Rec; Rec r; process T(int &p) { state s0; init s0; }")
                        .add_system_decl("Process2 = T(r.f);")
                        .add_process("Process2")
                        .parse();
        CHECK(doc2.get_errors().empty());

        auto doc3 = document_fixture{}
                        .add_global_decl("int arr[3]; process T(int &p) { state s0; init s0; }")
                        .add_system_decl("Process2 = T(arr[0]);")
                        .add_process("Process2")
                        .parse();
        CHECK(doc3.get_errors().empty());
    }
}

TEST_SUITE("visitProperty error branches")
{
    TEST_CASE("a side-effecting property is rejected")
    {
        auto doc = document_fixture{}.add_global_decl("bool b;").add_default_process().parse();
        auto pb = UTAP::TigaPropertyBuilder{doc};
        parse_property("A[] (b=true)", pb);
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Expression_must_be_side-effect_free");
    }

    TEST_CASE("loadStrategy with a non-string argument is rejected")
    {
        auto doc = document_fixture{}.add_default_process().parse();
        auto pb = UTAP::TigaPropertyBuilder{doc};
        parse_property("loadStrategy(5)", pb);
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$loadStrategy_and_saveStrategy_expect_a_string");
    }

    TEST_CASE("nested path quantifiers outside of a constraint are rejected")
    {
        auto doc = document_fixture{}.add_global_decl("bool b;").add_default_process().parse();
        auto pb = UTAP::TigaPropertyBuilder{doc};
        parse_property("A[] (b && A<> b)", pb);
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Nested_path_quantifiers_are_not_supported");
    }
}

TEST_SUITE("checkObservationConstraints (PO_CONTROL)")
{
    TEST_CASE("an int/clock lower-or-upper bound comparison in an observation set is rejected")
    {
        auto doc = document_fixture{}.add_global_decl("clock c; int x;").add_default_process().parse();
        auto pb = UTAP::TigaPropertyBuilder{doc};
        parse_property("{x < c} control: A<> true", pb);
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Clock_lower_bound_must_be_weak_and_upper_bound_strict");
    }

    TEST_CASE("a clock-difference comparison in an observation set is rejected")
    {
        auto doc = document_fixture{}.add_global_decl("clock c1; clock c2;").add_default_process().parse();
        auto pb = UTAP::TigaPropertyBuilder{doc};
        parse_property("{c1==c2} control: A<> true", pb);
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Clock_differences_are_not_supported");
    }
}

TEST_SUITE("Statement visitor side-effect/range checks")
{
    TEST_CASE("a side-effecting assert expression is rejected")
    {
        auto doc = document_fixture{}
                       .add_global_decl("int y; void f() { assert(y=1==1); }")
                       .add_default_process()
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Expression_must_be_side-effect_free");
    }

    TEST_CASE("iterating over a non-range type is rejected")
    {
        auto doc = document_fixture{}
                       .add_global_decl("typedef const int MyInt; int f() { int s=0; for (i : MyInt) { s+=1; } return s; }")
                       .add_default_process()
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Range_expected");
    }

    TEST_CASE("a side-effecting local variable initialiser in a block is rejected")
    {
        auto doc = document_fixture{}
                       .add_global_decl("int f() { int y; int x = (y=1); return x; }")
                       .add_default_process()
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Expression_must_be_side-effect_free");
    }
}

TEST_SUITE("Parameter compatibility gaps")
{
    TEST_CASE("a non-const-reference function parameter requires a modifiable lvalue argument")
    {
        auto doc = document_fixture{}
                       .add_global_decl("void f(int &p) { } void g() { f(5); }")
                       .add_default_process()
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Incompatible_argument");
    }

    TEST_CASE("a channel argument with insufficient capability is rejected")
    {
        auto doc = document_fixture{}
                       .add_global_decl("void f(chan &c) { } urgent chan mychan; void g() { f(mychan); }")
                       .add_default_process()
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Incompatible_argument");
    }

    TEST_CASE("checkParameterCompatible rejects an incompatible return type")
    {
        auto doc = document_fixture{}
                       .add_global_decl("double f() { return 1; } int g() { return f(); }")
                       .add_default_process()
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Incompatible_argument");
    }
}

TEST_SUITE("getInlineIfCommonType gaps")
{
    TEST_CASE("ternary with the second operand a record type")
    {
        auto doc = document_fixture{}
                       .add_global_decl("struct { int x; } s; double x; void f(bool b) { x = b? 0.5 : s; }")
                       .add_default_process()
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Incompatible_arguments_to_inline_if");
    }

    TEST_CASE("ternary between two distinct (structurally equivalent but not assignment-compatible) scalar sets")
    {
        auto doc = document_fixture{}
                       .add_global_decl("scalar[3] a; scalar[3] c; void f(bool b) { b ? a : c; }")
                       .add_default_process()
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Incompatible_arguments_to_inline_if");
    }
}

TEST_SUITE("SPAWN/NUMOF/EXIT")
{
    TEST_CASE("spawning a non-dynamic template is rejected")
    {
        auto doc = document_fixture{}
                       .add_global_decl("process NotDyn() { state s0; init s0; }")
                       .add_template(R"XML(<template>
        <name>T</name>
        <location id="id0" x="0" y="0"/>
        <location id="id1" x="10" y="10"/>
        <init ref="id0"/>
        <transition><source ref="id0"/><target ref="id1"/><label kind="assignment">spawn NotDyn()</label></transition>
    </template>)XML")
                       .add_system_decl("Process = T();")
                       .add_process("Process")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Cannot_spawn_a_non-dynamic_template");
    }

    TEST_CASE("spawn with the wrong number of arguments is rejected")
    {
        auto doc = document_fixture{}
                       .add_global_decl("dynamic Child();")
                       .add_template(R"XML(<template>
        <name>Child</name>
        <location id="id0" x="0" y="0"/>
        <init ref="id0"/>
    </template>)XML")
                       .add_template(R"XML(<template>
        <name>T</name>
        <location id="id0" x="0" y="0"/>
        <location id="id1" x="10" y="10"/>
        <init ref="id0"/>
        <transition><source ref="id0"/><target ref="id1"/><label kind="assignment">spawn Child(1)</label></transition>
    </template>)XML")
                       .add_system_decl("Process = T();")
                       .add_process("Process")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Wrong_number_of_arguments");
    }

    TEST_CASE("exit() is only valid inside a dynamic template")
    {
        auto doc = document_fixture{}
                       .add_global_decl("dynamic Child();")
                       .add_template(R"XML(<template>
        <name>Child</name>
        <location id="id0" x="0" y="0"/>
        <location id="id1" x="10" y="10"/>
        <init ref="id0"/>
        <transition><source ref="id0"/><target ref="id1"/><label kind="assignment">exit()</label></transition>
    </template>)XML")
                       .add_default_process()
                       .add_system_decl("ChildProc = Child();")
                       .parse();
        CHECK(doc.get_errors().empty());

        auto doc2 = document_fixture{}
                        .add_template(R"XML(<template>
        <name>T</name>
        <location id="id0" x="0" y="0"/>
        <location id="id1" x="10" y="10"/>
        <init ref="id0"/>
        <transition><source ref="id0"/><target ref="id1"/><label kind="assignment">exit()</label></transition>
    </template>)XML")
                        .add_system_decl("Process = T();")
                        .add_process("Process")
                        .parse();
        const auto& errs2 = doc2.get_errors();
        REQUIRE(errs2.size() == 1);
        CHECK(errs2[0].msg == "$Exit_can_only_be_used_in_dynamic_templates");
    }

    TEST_CASE("numOf() succeeds for a dynamic template and fails for a non-dynamic one")
    {
        auto doc = document_fixture{}
                       .add_global_decl("dynamic Child();")
                       .add_template(R"XML(<template>
        <name>Child</name>
        <location id="id0" x="0" y="0"/>
        <init ref="id0"/>
    </template>)XML")
                       .add_default_process()
                       .add_system_decl("ChildProc = Child();")
                       .parse();
        REQUIRE(doc.get_errors().empty());
        auto pb = UTAP::TigaPropertyBuilder{doc};
        parse_property("Pr[<=10](<> numOf(Child) >= 1)", pb);
        CHECK(doc.get_errors().empty());

        auto doc2 = document_fixture{}
                        .add_global_decl("process NotDyn() { state s0; init s0; }")
                        .add_default_process()
                        .parse();
        auto pb2 = UTAP::TigaPropertyBuilder{doc2};
        parse_property("A[] numOf(NotDyn) >= 0", pb2);
        const auto& errs2 = doc2.get_errors();
        REQUIRE(errs2.size() == 1);
        CHECK(errs2[0].msg == "$Not_a_dynamic_template");
    }
}

TEST_SUITE("FORALL/EXISTS/SUM alternate result types")
{
    TEST_CASE("forall over a clock comparison (guard-typed body) and its side-effect check")
    {
        auto doc = document_fixture{}.add_global_decl("clock c[3]; int x;").add_default_process().parse();
        auto expr = parse_expression("forall (i:int[0,2]) c[i] < 5", doc, true);
        CHECK(doc.get_errors().empty());

        auto doc2 = document_fixture{}.add_global_decl("int x;").add_default_process().parse();
        parse_expression("forall (i:int[0,2]) (x=1)", doc2, true);
        const auto& errs2 = doc2.get_errors();
        REQUIRE(errs2.size() == 1);
        CHECK(errs2[0].msg == "$Expression_must_be_side-effect_free");
    }

    TEST_CASE("exists' side-effect check")
    {
        auto doc = document_fixture{}.add_global_decl("int x;").add_default_process().parse();
        parse_expression("exists (i:int[0,2]) (x=1)", doc, true);
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Expression_must_be_side-effect_free");
    }

    TEST_CASE("sum over a double-typed body and its side-effect check")
    {
        auto doc = document_fixture{}.add_global_decl("double d[3];").add_default_process().parse();
        auto expr = parse_expression("sum (i:int[0,2]) d[i]", doc, true);
        CHECK(doc.get_errors().empty());

        auto doc2 = document_fixture{}.add_global_decl("int x;").add_default_process().parse();
        parse_expression("sum (i:int[0,2]) (x=1)", doc2, true);
        const auto& errs2 = doc2.get_errors();
        REQUIRE(errs2.size() == 1);
        CHECK(errs2[0].msg == "$Expression_must_be_side-effect_free");
    }
}

TEST_SUITE("COMMA/ARRAY index edge cases")
{
    TEST_CASE("a comma expression with an incompatible left operand is rejected")
    {
        auto doc = document_fixture{}
                       .add_global_decl("chan ch; int f() { int i=0; for (ch, i=0; i<5; i=i+1) {} return i; }")
                       .add_default_process()
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(!errs.empty());
        CHECK(errs[0].msg == "$Incompatible_type_for_comma_expression");
    }

    TEST_CASE("indexing an array by a mismatched scalar set is rejected")
    {
        auto doc = document_fixture{}
                       .add_global_decl("scalar[3] a; scalar[4] b; int arr[a]; void f() { arr[b]; }")
                       .add_default_process()
                       .parse();
        const auto& errs = doc.get_errors();
        bool found = false;
        for (const auto& e : errs)
            found |= (e.msg == "$Incompatible_type");
        CHECK(found);
    }
}
