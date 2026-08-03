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

#include "document_fixture.h"

#include <doctest/doctest.h>

TEST_SUITE_BEGIN("ExpressionBuilder");

using namespace UTAP;

TEST_CASE("Pre-decrement and built-in math functions")
{
    auto doc = document_fixture{}
                   .add_default_process()
                   .add_global_decl("void f() {"
                                    "  int i = 5;"
                                    "  double d1;"
                                    "  double d2;"
                                    "  double d3;"
                                    "  --i;"                              // expr_pre_decrement
                                    "  d1 = sqrt(2.0);"                   // expr_builtin_function1
                                    "  d2 = pow(2.0, 3.0);"               // expr_builtin_function2
                                    "  d3 = fma(1.0, 2.0, 3.0);"          // expr_builtin_function3
                                    "}")
                   .parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
}

TEST_CASE("Global scalar type declaration")
{
    // type_scalar() outside a template (currentTemplate == nullptr): the
    // dependency-tracking branch is skipped.
    auto doc = document_fixture{}.add_default_process().add_global_decl("scalar[3] s;").parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
}

TEST_CASE("Template-local scalar type declaration tracks free-parameter dependencies")
{
    // type_scalar() inside a template's local declarations exercises the
    // collect_dependencies() call that marks symbols used in the scalar
    // set's size as restricted (they may not depend on free parameters).
    auto doc = document_fixture{}
                   .add_template(R"XML(<template>
        <name>T</name>
        <declaration>scalar[3] s;</declaration>
        <location id="id0" x="0" y="0"/>
        <init ref="id0"/>
    </template>)XML")
                   .add_system_decl("Process = T();")
                   .add_process("Process")
                   .parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
}

TEST_CASE("control_t* time-optimal synthesis query exercises expr_ternary")
{
    auto f = document_fixture{}.add_global_decl("clock c;").add_default_process().build_query_fixture();
    const auto& info = f.parse_query("control_t*(1, c): A<> true");
    CHECK(info.type == quant_t::control_opt_AF);
}

TEST_CASE("numOf() exercises expr_numof before the later not-a-dynamic-template check")
{
    auto f = document_fixture{}.add_default_process().build_query_fixture();
    CHECK_THROWS_WITH_AS(f.parse_query("E<> numOf(Process) >= 0"), "$Not_a_dynamic_template", std::logic_error);
}

TEST_CASE("foreach() over a non-dynamic-template exercises expr_foreach_dynamic_begin/end")
{
    auto f = document_fixture{}.add_default_process().build_query_fixture();
    CHECK_THROWS_WITH_AS(f.parse_query("foreach (p : Process) (true)"), "Unknown dynamic template Process",
                        std::logic_error);
}

TEST_CASE("forall/exists/sum over a dynamic template")
{
    // Exercises expr_forall_dynamic_begin/end, expr_exists_dynamic_begin/end,
    // expr_sum_dynamic_begin/end, and (transitively) push_dynamic_frame_of/
    // pop_dynamic_frame_of. The dynamic template must already be fully
    // defined (Template::is_defined) by the time it's referenced, so Child
    // is declared and defined before Parent uses it on an edge.
    auto doc = document_fixture{}
                   .add_global_decl("dynamic Child(int p); int total;")
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
        <location id="id2" x="20" y="20"/>
        <location id="id3" x="30" y="30"/>
        <init ref="id0"/>
        <transition>
            <source ref="id0"/>
            <target ref="id1"/>
            <label kind="guard">forall (p : Child) (true)</label>
        </transition>
        <transition>
            <source ref="id1"/>
            <target ref="id2"/>
            <label kind="guard">exists (p : Child) (true)</label>
        </transition>
        <transition>
            <source ref="id2"/>
            <target ref="id3"/>
            <label kind="assignment">total = sum (p : Child) 1</label>
        </transition>
    </template>)XML")
                   .add_system_decl("Process = Parent();")
                   .add_process("Process")
                   .parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
}

TEST_CASE("MITL until/release/box/next forms")
{
    auto f = document_fixture{}
                 .add_global_decl("bool b;")
                 .add_default_process()
                 .build_query_fixture();

    SUBCASE("until")
    {
        const auto& info = f.parse_query("Pr (b U[0,5] b)");
        CHECK(info.type == quant_t::Mitl);
    }
    SUBCASE("release")
    {
        const auto& info = f.parse_query("Pr (b R[0,5] b)");
        CHECK(info.type == quant_t::Mitl);
    }
    SUBCASE("box")
    {
        const auto& info = f.parse_query("Pr ([][0,5] b)");
        CHECK(info.type == quant_t::Mitl);
    }
    SUBCASE("next")
    {
        const auto& info = f.parse_query("Pr (X b)");
        CHECK(info.type == quant_t::Mitl);
    }
}

TEST_SUITE_END();
