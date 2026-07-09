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

/**
 * PropertyBuilder/TigaPropertyBuilder::typeProperty() classifies a parsed
 * property expression into a quant_t and populates a PropInfo. Existing
 * tests that use document_fixture's local (lightweight) QueryBuilder class
 * never reach this code -- only the QueryFixture/TigaPropertyBuilder path
 * (parse_query) does, and only a handful of query forms (E<>, Pr[...]
 * comparisons, simulate, saveStrategy) were exercised that way before.
 */

#include "document_fixture.h"

#include "utap/property.hpp"

#include <doctest/doctest.h>

TEST_SUITE_BEGIN("PropertyBuilder/TigaPropertyBuilder");

using namespace UTAP;

namespace {
/// A document with a template with three named, linearly-connected
/// locations (L1 -> L2 -> L3), for tests needing leads-to/location
/// references, plus a clock and bool for guards/predicates.
document_fixture named_locations_fixture()
{
    return document_fixture{}
        .add_global_decl("clock c; bool b;")
        .add_template(R"XML(<template>
        <name>T</name>
        <location id="id0" x="0" y="0"><name>L1</name></location>
        <location id="id1" x="10" y="10"><name>L2</name></location>
        <location id="id2" x="20" y="20"><name>L3</name></location>
        <init ref="id0"/>
        <transition><source ref="id0"/><target ref="id1"/></transition>
        <transition><source ref="id1"/><target ref="id2"/></transition>
    </template>)XML")
        .add_system_decl("Process = T();")
        .add_process("Process");
}
}  // namespace

TEST_CASE("A[] classifies as quant_t::AG")
{
    auto f = named_locations_fixture().build_query_fixture();
    const auto& info = f.parse_query("A[] true");
    CHECK(info.type == quant_t::AG);
}

TEST_CASE("E[] classifies as quant_t::EG")
{
    auto f = named_locations_fixture().build_query_fixture();
    const auto& info = f.parse_query("E[] true");
    CHECK(info.type == quant_t::EG);
}

TEST_CASE("A<> classifies as quant_t::AE")
{
    auto f = named_locations_fixture().build_query_fixture();
    const auto& info = f.parse_query("A<> true");
    CHECK(info.type == quant_t::AE);
}

TEST_CASE("--> classifies as quant_t::leads_to")
{
    auto f = named_locations_fixture().build_query_fixture();
    const auto& info = f.parse_query("Process.L2 --> Process.L3");
    CHECK(info.type == quant_t::leads_to);
}

TEST_CASE("sup{}: classifies as quant_t::supremum")
{
    auto f = named_locations_fixture().build_query_fixture();
    const auto& info = f.parse_query("sup{true}: c");
    CHECK(info.type == quant_t::supremum);
}

TEST_CASE("inf{}: classifies as quant_t::infimum")
{
    auto f = named_locations_fixture().build_query_fixture();
    const auto& info = f.parse_query("inf{true}: c");
    CHECK(info.type == quant_t::infimum);
}

TEST_CASE("bounds{}: classifies as quant_t::bounds")
{
    auto f = named_locations_fixture().build_query_fixture();
    const auto& info = f.parse_query("bounds{true}: c");
    CHECK(info.type == quant_t::bounds);
}

TEST_CASE("Pr[...](<> ...) >= p classifies as quant_t::probaMinDiamond")
{
    auto f = named_locations_fixture().build_query_fixture();
    const auto& info = f.parse_query("Pr[<=10](<> b) >= 0.5");
    CHECK(info.type == quant_t::probaMinDiamond);
}

TEST_CASE("Pr[...]([] ...) >= p classifies as quant_t::probaMinBox")
{
    auto f = named_locations_fixture().build_query_fixture();
    const auto& info = f.parse_query("Pr[<=10]([] b) >= 0.5");
    CHECK(info.type == quant_t::probaMinBox);
}

TEST_CASE("Pr[...]([] ...) classifies as quant_t::probaBox")
{
    auto f = named_locations_fixture().build_query_fixture();
    const auto& info = f.parse_query("Pr[<=10]([] b)");
    CHECK(info.type == quant_t::probaBox);
}

TEST_CASE("Pr (MITL) classifies as quant_t::Mitl")
{
    auto f = named_locations_fixture().build_query_fixture();
    const auto& info = f.parse_query("Pr (<>[0,5] b)");
    CHECK(info.type == quant_t::Mitl);
}

TEST_CASE("control: A<> classifies as quant_t::control_AF with a ZoneStrategy result")
{
    auto f = named_locations_fixture().build_query_fixture();
    const auto& info = f.parse_query("control: A<> true");
    CHECK(info.type == quant_t::control_AF);
    CHECK(info.result_type == ZoneStrategy);
}

TEST_CASE("control: A[] classifies as quant_t::control_AG")
{
    auto f = named_locations_fixture().build_query_fixture();
    const auto& info = f.parse_query("control: A[] true");
    CHECK(info.type == quant_t::control_AG);
}

TEST_CASE("control: A[] (p && A<> q) classifies as quant_t::control_ABuchi")
{
    auto f = named_locations_fixture().build_query_fixture();
    const auto& info = f.parse_query("control: A[] (true && A<> true)");
    CHECK(info.type == quant_t::control_ABuchi);
}

TEST_CASE("E<> control: A<> classifies as quant_t::EF_control_AF")
{
    auto f = named_locations_fixture().build_query_fixture();
    const auto& info = f.parse_query("E<> control: A<> true");
    CHECK(info.type == quant_t::EF_control_AF);
}

TEST_CASE("E<> control: A[] classifies as quant_t::EF_control_AG")
{
    auto f = named_locations_fixture().build_query_fixture();
    const auto& info = f.parse_query("E<> control: A[] true");
    CHECK(info.type == quant_t::EF_control_AG);
}

TEST_CASE("minE(...)[...] classifies as quant_t::control_MinExp with a NonZoneStrategy result")
{
    auto f = named_locations_fixture().build_query_fixture();
    const auto& info = f.parse_query("minE(c)[<=20]: <> b");
    CHECK(info.type == quant_t::control_MinExp);
    CHECK(info.result_type == NonZoneStrategy);
}

TEST_CASE("maxE(...)[...] classifies as quant_t::control_MaxExp")
{
    auto f = named_locations_fixture().build_query_fixture();
    const auto& info = f.parse_query("maxE(c)[<=20]: <> b");
    CHECK(info.type == quant_t::control_MaxExp);
}

TEST_CASE("A deadlock predicate is only supported for E<>/A[]")
{
    // property()'s `throw TypeException` is caught by the bison-generated
    // CALL() wrapper and turned into a recorded document error (see
    // parser.y: "catch (TypeException &te) { ch->handle_error(te); }"),
    // not a propagating C++ exception -- so check doc.get_errors()
    // directly instead of expecting a throw.
    auto doc = named_locations_fixture().parse();
    REQUIRE(doc.get_errors().empty());
    auto pb = TigaPropertyBuilder{doc};
    parse_property("E[] deadlock", pb);
    const auto& errs = doc.get_errors();
    REQUIRE(errs.size() == 1);
    CHECK(errs[0].msg == "$Cannot_handle_this_deadlock_predicate");
}

TEST_CASE("A dynamic template restricts non-SMC queries")
{
    auto doc = document_fixture{}
                   .add_global_decl("dynamic Child();")
                   .add_template(R"XML(<template>
        <name>Child</name>
        <location id="id0" x="0" y="0"/>
        <init ref="id0"/>
    </template>)XML")
                   .add_default_process()
                   .parse();
    REQUIRE(doc.get_errors().empty());
    auto pb = TigaPropertyBuilder{doc};
    parse_property("A[] true", pb);
    const auto& errs = doc.get_errors();
    REQUIRE(errs.size() == 1);
    CHECK(errs[0].msg == "Dynamic templates are only supported for SMC queries");
}

TEST_CASE("handle_expect parses status/time/memory tokens")
{
    auto doc = document_fixture{}.add_default_process().parse();
    auto pb = TigaPropertyBuilder{doc};
    REQUIRE(parse_property("A[] true", pb) == 0);
    pb.handle_expect("T, 5S, 100KB");
    const auto& info = pb.getProperties().back();
    REQUIRE(info.expect != nullptr);
    CHECK(std::get<status_t>(info.expect->result) == status_t::DONE_TRUE);
    CHECK(info.expect->time_ms == 5000);
    CHECK(info.expect->mem_kib == 100);
}

TEST_CASE("declaring the same strategy name twice warns about a duplicate definition")
{
    auto doc = document_fixture{}.add_default_process().parse();
    auto pb = TigaPropertyBuilder{doc};
    REQUIRE(parse_property("strategy S = control: A[] true", pb) == 0);
    REQUIRE(parse_property("strategy S = control: A<> true", pb) == 0);
    const auto& warns = doc.get_warnings();
    REQUIRE(warns.size() == 1);
    CHECK(warns[0].msg == "$Duplicate_definition_of S");
}

TEST_CASE("subjection referring to an undeclared strategy is an error")
{
    auto doc = document_fixture{}.add_default_process().parse();
    auto pb = TigaPropertyBuilder{doc};
    parse_property("Pr[<=10](<> true) under NoSuchStrategy", pb);
    const auto& errs = doc.get_errors();
    REQUIRE(errs.size() == 1);
    CHECK(errs[0].msg == "$strategy_not_declared: NoSuchStrategy");
}

TEST_CASE("sat: over a non-LSC-template is rejected by PropertyBuilder::scenario()")
{
    // Unlike most PropertyBuilder checks, scenario() throws a raw
    // std::runtime_error rather than TypeException, so it is *not* caught
    // by the CALL() macro in parser.y (which only catches TypeException) --
    // it propagates straight out of parse_property(), bypassing
    // QueryFixture's own doc.get_errors() check entirely.
    auto f = document_fixture{}.add_default_process().build_query_fixture();
    CHECK_THROWS_WITH_AS(f.parse_query("sat: Process"), "$Not_a_LSC_template: Process", std::runtime_error);
}

TEST_SUITE_END();
