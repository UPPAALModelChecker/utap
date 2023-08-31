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

TEST_SUITE("Quantifier sum")
{
    TEST_CASE("sum expression")
    {
        auto df = document_fixture{};
        df.add_system_decl("int x = sum (index : int[0, 5]) index;");
        auto doc = df.add_default_process().parse();
        auto warns = doc->get_warnings();
        CHECK(warns.size() == 0);
        auto errs = doc->get_errors();
        CHECK(errs.size() == 0);
    }

    TEST_CASE("sum over array")
    {
        auto df = document_fixture{};
        df.add_system_decl("int a[3] = {1,4,9};");
        df.add_system_decl("int x = sum(i : int[0, 2]) a[i];");
        auto doc = df.add_default_process().parse();
        auto warns = doc->get_warnings();
        CHECK(warns.size() == 0);
        auto errs = doc->get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Must_be_computable_at_compile_time");
    }

    TEST_CASE("sum over const array")
    {
        auto df = document_fixture{};
        df.add_system_decl("const int a[3] = {1,4,9};");
        df.add_system_decl("int x = sum(i : int[0, 2]) a[i];");
        auto doc = df.add_default_process().parse();
        auto warns = doc->get_warnings();
        CHECK(warns.size() == 0);
        auto errs = doc->get_errors();
        CHECK(errs.size() == 0);
    }
}

TEST_SUITE("Quantifier forall")
{
    TEST_CASE("forall expression")
    {
        auto df = document_fixture{};
        df.add_system_decl("bool x = forall(index : int[0, 5]) index > 3;");
        auto doc = df.add_default_process().parse();
        auto warns = doc->get_warnings();
        CHECK(warns.size() == 0);
        auto errs = doc->get_errors();
        CHECK(errs.size() == 0);
    }

    TEST_CASE("forall over array")
    {
        auto df = document_fixture{};
        df.add_system_decl("bool b[3] = {1,1,1};");
        df.add_system_decl("bool x = forall(i : int[0,2]) b[i];");
        auto doc = df.add_default_process().parse();
        CHECK_MESSAGE(doc->get_warnings().size() == 0, doc->get_warnings()[0].msg);
        const auto errors = doc->get_errors();
        REQUIRE(errors.size() == 1);
        CHECK(errors[0].msg == "$Must_be_computable_at_compile_time");
    }

    TEST_CASE("forall over const array")
    {
        auto df = document_fixture{};
        df.add_system_decl("const bool b[3]={1,1,1};");
        df.add_system_decl("bool x = forall(i : int[0,2]) b[i];");
        auto doc = df.add_default_process().parse();
        auto warns = doc->get_warnings();
        CHECK(warns.size() == 0);
        auto errs = doc->get_errors();
        CHECK(errs.size() == 0);
    }
}

TEST_SUITE("Quantifier exists")
{
    TEST_CASE("exists expression")
    {
        auto df = document_fixture{};
        df.add_system_decl("bool x = exists(index : int[0, 5]) index > 3;");
        auto doc = df.add_default_process().parse();
        auto warns = doc->get_warnings();
        CHECK(warns.size() == 0);
        auto errs = doc->get_errors();
        CHECK(errs.size() == 0);
    }
    TEST_CASE("exists over array")
    {
        auto df = document_fixture{};
        df.add_system_decl("bool b[3] = {0,0,1};");
        df.add_system_decl("bool x = exists(i : int[0,2]) b[i];");
        auto doc = df.add_default_process().parse();
        auto warns = doc->get_warnings();
        CHECK(warns.size() == 0);
        auto errs = doc->get_errors();
        REQUIRE(errs.size() == 1);
        CHECK(errs[0].msg == "$Must_be_computable_at_compile_time");
    }
    TEST_CASE("exists over const array")
    {
        auto df = document_fixture{};
        df.add_system_decl("const bool b[3]={0,0,1};");
        df.add_system_decl("bool x = exists(i : int[0,2]) b[i];");
        auto doc = df.add_default_process().parse();
        auto warns = doc->get_warnings();
        CHECK(warns.size() == 0);
        auto errs = doc->get_errors();
        CHECK(errs.size() == 0);
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
        auto warns = doc->get_warnings();
        CHECK(warns.size() == 0);
        auto errs = doc->get_errors();
        CHECK(errs.size() == 0);
    }

    TEST_CASE("Bounded int parameter")
    {
        auto df = document_fixture{};
        df.add_template(template_fixture{"T"}.add_parameter("int[1,4] test").str());
        df.add_process("T");
        auto text = df.str();
        auto doc = df.parse();
        auto warns = doc->get_warnings();
        CHECK(warns.size() == 0);
        auto errs = doc->get_errors();
        CHECK(errs.size() == 0);
    }

    TEST_CASE("Unbounded int parameter")
    {
        auto df = document_fixture{};
        df.add_template(template_fixture{"T"}.add_parameter("int test").str());
        df.add_process("T");
        auto text = df.str();
        auto doc = df.parse();
        auto warns = doc->get_warnings();
        CHECK(warns.size() == 0);
        auto errs = doc->get_errors();
        CHECK(errs.size() == 1);
        auto pos = errs.front().position;
        CHECK(pos.start != pos.unknown_pos);
        CHECK(pos.end != pos.unknown_pos);
    }

    TEST_CASE("Reference parameter")
    {
        auto df = document_fixture{};
        df.add_template(template_fixture{"T"}.add_parameter("int& test").str());
        df.add_process("T");
        auto text = df.str();
        auto doc = df.parse();
        auto warns = doc->get_warnings();
        CHECK(warns.size() == 0);
        auto errs = doc->get_errors();
        CHECK(errs.size() == 1);
        auto pos = errs.front().position;
        CHECK(pos.start != pos.unknown_pos);
        CHECK(pos.end != pos.unknown_pos);
    }
}

TEST_CASE("Ternary operator with clock and double")
{
    auto doc = document_fixture{}
                   .add_global_decl("clock c; double x; void f() { x = true? c : 1.0; }")
                   .add_default_process()
                   .parse();
    CHECK_MESSAGE(doc->get_errors().size() == 0, doc->get_errors()[0].msg);
    CHECK_MESSAGE(doc->get_warnings().size() == 0, doc->get_warnings()[0].msg);
}

TEST_CASE("Ternary operator with double and clock")
{
    auto doc = document_fixture{}
                   .add_global_decl("clock c; double x; void f() { x = true? 1.0 : c; }")
                   .add_default_process()
                   .parse();
    CHECK_MESSAGE(doc->get_errors().size() == 0, doc->get_errors()[0].msg);
    CHECK_MESSAGE(doc->get_warnings().size() == 0, doc->get_warnings()[0].msg);
}

TEST_CASE("Ternary operator with clock and integer")
{
    auto doc = document_fixture{}
                   .add_global_decl("clock c; double x; void f() { x = true? c : 1; }")
                   .add_default_process()
                   .parse();
    CHECK_MESSAGE(doc->get_errors().size() == 0, doc->get_errors()[0].msg);
    CHECK_MESSAGE(doc->get_warnings().size() == 0, doc->get_warnings()[0].msg);
}

TEST_CASE("Ternary operator with clock and bool")
{
    auto doc = document_fixture{}
                   .add_global_decl("clock c; double x; void f() { x = true? c : true; };")
                   .add_default_process()
                   .parse();
    CHECK(doc->get_errors().size() == 1);
    CHECK_MESSAGE(doc->get_warnings().size() == 0, doc->get_warnings()[0].msg);
}

TEST_CASE("Ternary operator with clock and clock")
{
    auto doc = document_fixture{}
                   .add_global_decl("clock c; double x; void f() { x = true? c : c; }")
                   .add_default_process()
                   .parse();
    CHECK_MESSAGE(doc->get_errors().size() == 0, doc->get_errors()[0].msg);
    CHECK_MESSAGE(doc->get_warnings().size() == 0, doc->get_warnings()[0].msg);
}

TEST_CASE("Ternary operator with constant double")
{
    auto doc = document_fixture{}
                   .add_global_decl("const double VAL = 2;")
                   .add_global_decl("double x; void f() { x = true? -VAL : VAL; }")
                   .add_default_process()
                   .parse();
    CHECK_MESSAGE(doc->get_errors().size() == 0, doc->get_errors()[0].msg);
    CHECK_MESSAGE(doc->get_warnings().size() == 0, doc->get_warnings()[0].msg);
}

TEST_CASE("Ternary operator with constant double and clock")
{
    auto doc = document_fixture{}
                   .add_global_decl("const double VAL = 2;")
                   .add_global_decl("clock c;")
                   .add_global_decl("double x; void f() { x = true? -VAL : c; }")
                   .add_default_process()
                   .parse();
    CHECK_MESSAGE(doc->get_errors().size() == 0, doc->get_errors()[0].msg);
    CHECK_MESSAGE(doc->get_warnings().size() == 0, doc->get_warnings()[0].msg);
}

TEST_CASE("Ternary operator with boolean and clock")
{
    auto doc = document_fixture{}
                   .add_global_decl("clock c;")
                   .add_global_decl("double x; void f() { x = true? true : c; }")
                   .add_default_process()
                   .parse();
    CHECK_MESSAGE(doc->get_errors().size() == 0, doc->get_errors()[0].msg);
    CHECK_MESSAGE(doc->get_warnings().size() == 0, doc->get_warnings()[0].msg);
}

TEST_CASE("Ternary operator with struct and double")
{
    auto doc = document_fixture{}
                   .add_global_decl("struct { int x; } s;")
                   .add_global_decl("double x; void f() { x = true? s : 0.5; }")
                   .add_default_process()
                   .parse();
    CHECK(doc->get_errors().size() == 1);
    CHECK_MESSAGE(doc->get_warnings().size() == 0, doc->get_warnings()[0].msg);
}

TEST_CASE("Ternary operator with struct and double")
{
    auto doc = document_fixture{}
                   .add_global_decl("struct { int x; } s;")
                   .add_global_decl("double x; void f() { x = true? s : 0.5; }")
                   .add_default_process()
                   .parse();
    CHECK(doc->get_errors().size() == 1);
    CHECK_MESSAGE(doc->get_warnings().size() == 0, doc->get_warnings()[0].msg);
}

TEST_CASE("Ternary operator with struct and struct")
{
    auto doc = document_fixture{}
                   .add_global_decl("typedef struct { int x; } S;")
                   .add_global_decl("S s; S x = {5}; S y = {2};")
                   .add_global_decl("void f() { s = true? x : y; }")
                   .add_default_process()
                   .parse();
    CHECK_MESSAGE(doc->get_errors().size() == 0, doc->get_errors()[0].msg);
    CHECK_MESSAGE(doc->get_warnings().size() == 0, doc->get_warnings()[0].msg);
}