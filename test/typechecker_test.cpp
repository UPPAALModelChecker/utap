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
        CHECK(errs[0].msg == "$Wrong_number_of_arguments");
    }

    TEST_CASE("wrong number of arguments, too few")
    {
        auto doc = document_fixture{}
                       .add_default_process()
                       .add_global_decl("int f(int a, int b) { return a; } void g() { int x = f(1); }")
                       .parse();
        const auto& errs = doc.get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Wrong_number_of_arguments");
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
}
