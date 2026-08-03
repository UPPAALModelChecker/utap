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

#include <cstdio>
#include <filesystem>
#include <fstream>

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

TEST_CASE("A deadlock predicate is rejected for models with priority declarations")
{
    auto doc = document_fixture{}
                   .add_global_decl("chan a; chan bb; chan priority a < bb;")
                   .add_default_process()
                   .parse();
    REQUIRE(doc.get_errors().empty());
    REQUIRE(doc.has_priority_declaration());
    auto pb = TigaPropertyBuilder{doc};
    parse_property("E[] deadlock", pb);
    const auto& errs = doc.get_errors();
    REQUIRE(errs.size() == 1);
    CHECK(errs[0].msg ==
          "$Cannot_handle_deadlock_predicate_for_models_with_priorities_or_guarded_broadcast_receivers");
}

TEST_CASE("A symbolic query is rejected when it uses a double variable")
{
    auto doc = document_fixture{}.add_global_decl("double d;").add_default_process().parse();
    REQUIRE(doc.get_errors().empty());
    auto pb = TigaPropertyBuilder{doc};
    parse_property("A[] d < 5.0", pb);
    const auto& errs = doc.get_errors();
    REQUIRE(errs.size() == 1);
    CHECK(errs[0].msg == "Symbolic verification and synthesis exclude usage of doubles and hybrid clocks in properties.");
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

TEST_CASE("sat: over an unresolvable name reports no such scenario")
{
    auto f = document_fixture{}.add_default_process().build_query_fixture();
    CHECK_THROWS_WITH_AS(f.parse_query("sat: NoSuchProcess"), "$No_such_scenario: NoSuchProcess", std::runtime_error);
}

namespace {
/// A document with a template plus an LSC template instantiating it, so that
/// "sat: LscTemplate" resolves to a real Kind::LSC_INSTANCE symbol.
UTAP::Document lsc_document()
{
    static constexpr auto xml = R"XML(<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE nta PUBLIC '-//Uppaal Team//DTD Flat System 1.1//EN' 'http://www.it.uu.se/research/group/darts/uppaal/flat-1_2.dtd'>
<nta>
    <declaration></declaration>
    <template>
        <name>A</name>
        <location id="id0" x="0" y="0"/>
        <init ref="id0"/>
    </template>
    <lsc>
        <name>LscTemplate</name>
        <type>Universal</type>
        <mode>invariant</mode>
        <instance id="id1" x="0" y="0"><name x="0" y="0">A</name></instance>
    </lsc>
    <system>
Process = A();
system Process;
    </system>
</nta>
)XML";
    auto doc = Document{};
    parse_XML_buffer(xml, doc, true);
    return doc;
}
}  // namespace

TEST_CASE("sat: over a valid LSC template classifies as quant_t::scenario")
{
    auto doc = lsc_document();
    REQUIRE(doc.get_errors().empty());
    auto pb = TigaPropertyBuilder{doc};
    REQUIRE(parse_property("sat: LscTemplate", pb) == 0);
    REQUIRE(doc.get_errors().empty());
    CHECK(pb.getProperties().back().type == quant_t::scenario);
}

TEST_CASE("A scenario query is rejected for models with priority declarations")
{
    static constexpr auto xml = R"XML(<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE nta PUBLIC '-//Uppaal Team//DTD Flat System 1.1//EN' 'http://www.it.uu.se/research/group/darts/uppaal/flat-1_2.dtd'>
<nta>
    <declaration>chan a; chan bb; chan priority a &lt; bb;</declaration>
    <template>
        <name>A</name>
        <location id="id0" x="0" y="0"/>
        <init ref="id0"/>
    </template>
    <lsc>
        <name>LscTemplate</name>
        <type>Universal</type>
        <mode>invariant</mode>
        <instance id="id1" x="0" y="0"><name x="0" y="0">A</name></instance>
    </lsc>
    <system>
Process = A();
system Process;
    </system>
</nta>
)XML";
    auto doc = Document{};
    parse_XML_buffer(xml, doc, true);
    REQUIRE(doc.get_errors().empty());
    REQUIRE(doc.has_priority_declaration());
    auto pb = TigaPropertyBuilder{doc};
    parse_property("sat: LscTemplate", pb);
    const auto& errs = doc.get_errors();
    REQUIRE(errs.size() == 1);
    CHECK(errs[0].msg ==
          "$Cannot_handle_this_formula_for_models_with_priorities_or_guarded_broadcast_receivers");
}

TEST_CASE("A probability query is rejected for models with priority declarations")
{
    auto doc = document_fixture{}
                   .add_global_decl("bool b; chan a; chan bb; chan priority a < bb;")
                   .add_default_process()
                   .parse();
    REQUIRE(doc.get_errors().empty());
    REQUIRE(doc.has_priority_declaration());
    auto pb = TigaPropertyBuilder{doc};
    parse_property("Pr[<=10](<> b)", pb);
    const auto& errs = doc.get_errors();
    REQUIRE(errs.size() == 1);
    CHECK(errs[0].msg == "Priorities are not supported");
}

TEST_CASE("A probability query is rejected when a non-broadcast channel is declared")
{
    auto doc = document_fixture{}.add_global_decl("bool b; chan ch;").add_default_process().parse();
    REQUIRE(doc.get_errors().empty());
    REQUIRE_FALSE(doc.all_broadcast());
    auto pb = TigaPropertyBuilder{doc};
    parse_property("Pr[<=10](<> b)", pb);
    const auto& errs = doc.get_errors();
    REQUIRE(errs.size() == 1);
    CHECK(errs[0].msg == "All channels must be broadcast");
}

TEST_CASE("A control query is rejected for systems with strict invariants")
{
    static constexpr auto xml = R"XML(<template>
        <name>T</name>
        <location id="id0" x="0" y="0"><label kind="invariant">x &lt; 5</label></location>
        <init ref="id0"/>
    </template>)XML";
    auto doc = document_fixture{}
                   .add_global_decl("clock x;")
                   .add_template(xml)
                   .add_system_decl("Process = T();")
                   .add_process("Process")
                   .parse();
    REQUIRE(doc.get_errors().empty());
    REQUIRE(doc.has_strict_invariants());
    auto pb = TigaPropertyBuilder{doc};
    parse_property("control: A<> true", pb);
    const auto& errs = doc.get_errors();
    REQUIRE(errs.size() == 1);
    CHECK(errs[0].msg == "$TIGA_properties_cannot_be_checked_for_systems_with_strict_invariants");
}

TEST_CASE("Pr[...](<> ...) without a comparison classifies as quant_t::probaDiamond")
{
    auto f = named_locations_fixture().build_query_fixture();
    const auto& info = f.parse_query("Pr[<=10](<> b)");
    CHECK(info.type == quant_t::probaDiamond);
}

TEST_CASE("E[...](max: ...) classifies as quant_t::probaExpected")
{
    auto f = named_locations_fixture().build_query_fixture();
    const auto& info = f.parse_query("E[<=10](max: c)");
    CHECK(info.type == quant_t::probaExpected);
}

TEST_CASE("control_t*(lo,hi): classifies as quant_t::control_opt_AF/AUntil with a ZoneStrategy result")
{
    auto f = named_locations_fixture();
    auto af = f.build_query_fixture().parse_query("control_t*(0,10): A<> true");
    CHECK(af.type == quant_t::control_opt_AF);
    CHECK(af.result_type == ZoneStrategy);
    CHECK(f.build_query_fixture().parse_query("control_t*(0,10): A[true U true]").type ==
          quant_t::control_opt_AUntil);
}

TEST_CASE("control_t*(bound): classifies as quant_t::control_opt_Def1_AF/AUntil")
{
    auto f = named_locations_fixture();
    CHECK(f.build_query_fixture().parse_query("control_t*(10): A<> true").type == quant_t::control_opt_Def1_AF);
    CHECK(f.build_query_fixture().parse_query("control_t*(10): A[true U true]").type ==
          quant_t::control_opt_Def1_AUntil);
}

TEST_CASE("control_t*: classifies as quant_t::control_opt_Def2_AF/AUntil")
{
    auto f = named_locations_fixture();
    CHECK(f.build_query_fixture().parse_query("control_t*: A<> true").type == quant_t::control_opt_Def2_AF);
    CHECK(f.build_query_fixture().parse_query("control_t*: A[true U true]").type ==
          quant_t::control_opt_Def2_AUntil);
}

TEST_CASE("{...} control: classifies as a PO_control_* quant_t")
{
    auto f = named_locations_fixture();
    CHECK(f.build_query_fixture().parse_query("{true} control: A<> true").type == quant_t::PO_control_AF);
    CHECK(f.build_query_fixture().parse_query("{true} control: A[] true").type == quant_t::PO_control_AG);
    CHECK(f.build_query_fixture().parse_query("{true} control: A[true U true]").type == quant_t::PO_control_AUntil);
    CHECK(f.build_query_fixture().parse_query("{true} control: A[true W true]").type ==
          quant_t::PO_control_AWeakUntil);
}

TEST_CASE("control: A[phi U psi]/A[phi W psi] classify as control_AUntil/control_AWeakUntil")
{
    auto f = named_locations_fixture();
    CHECK(f.build_query_fixture().parse_query("control: A[true U true]").type == quant_t::control_AUntil);
    CHECK(f.build_query_fixture().parse_query("control: A[true W true]").type == quant_t::control_AWeakUntil);
}

TEST_CASE("E<> control: A[phi U psi]/A[phi W psi] classify as EF_control_AUntil/EF_control_AWeakUntil")
{
    auto f = named_locations_fixture();
    CHECK(f.build_query_fixture().parse_query("E<> control: A[true U true]").type == quant_t::EF_control_AUntil);
    CHECK(f.build_query_fixture().parse_query("E<> control: A[true W true]").type ==
          quant_t::EF_control_AWeakUntil);
}

TEST_CASE("An unsupported control synthesis sub-formula is rejected across all control forms")
{
    auto f = named_locations_fixture();
    // clang-format off
    const auto queries = {
        "control: E<> true", "E<> control: E<> true", "{true} control: E<> true",
        "control_t*(0,10): E<> true", "control_t*(10): E<> true", "control_t*: E<> true",
    };
    // clang-format on
    for (const auto* q : queries)
        CHECK_THROWS_AS(f.build_query_fixture().parse_query(q), std::logic_error);
}

TEST_CASE("loadStrategy(...) classifies as quant_t::strategy_load with a NonZoneStrategy result")
{
    auto f = named_locations_fixture().build_query_fixture();
    const auto& info = f.parse_query("loadStrategy(\"foo.strategy\")");
    CHECK(info.type == quant_t::strategy_load);
    CHECK(info.result_type == NonZoneStrategy);
}

TEST_CASE("saveStrategy(..., S) classifies as quant_t::strategy_save and requires a declared strategy S")
{
    auto doc = named_locations_fixture().parse();
    REQUIRE(doc.get_errors().empty());
    auto pb = TigaPropertyBuilder{doc};
    REQUIRE(parse_property("strategy S = control: A[] true", pb) == 0);
    REQUIRE(parse_property("saveStrategy(\"foo.strategy\", S)", pb) == 0);
    REQUIRE(doc.get_errors().empty());
    CHECK(pb.getProperties().back().type == quant_t::strategy_save);
}

TEST_CASE("subjection (under) and imitation (imitate) attach a previously declared strategy")
{
    auto doc = document_fixture{}.add_global_decl("bool b;").add_default_process().parse();
    REQUIRE(doc.get_errors().empty());
    auto pb = TigaPropertyBuilder{doc};
    REQUIRE(parse_property("strategy S = control: A[] true", pb) == 0);
    REQUIRE(parse_property("Pr[<=10](<> b) under S", pb) == 0);
    REQUIRE(doc.get_errors().empty());
    REQUIRE(pb.getProperties().back().subjections.size() == 1);

    REQUIRE(parse_property("minE(b)[<=20]: <> b imitate S", pb) == 0);
    REQUIRE(doc.get_errors().empty());
    CHECK(pb.getProperties().back().imitation != nullptr);
}

TEST_CASE("imitate referring to an undeclared strategy is an error")
{
    auto doc = document_fixture{}.add_default_process().parse();
    auto pb = TigaPropertyBuilder{doc};
    parse_property("minE(0)[<=20]: <> true imitate NoSuchStrategy", pb);
    const auto& errs = doc.get_errors();
    REQUIRE(errs.size() == 1);
    CHECK(errs[0].msg == "$strategy_not_declared: NoSuchStrategy");
}

TEST_CASE("A MinExp/MaxExp query is rejected when a non-broadcast channel is declared")
{
    auto doc = document_fixture{}.add_global_decl("clock c; chan ch;").add_default_process().parse();
    REQUIRE(doc.get_errors().empty());
    REQUIRE_FALSE(doc.all_broadcast());
    auto pb = TigaPropertyBuilder{doc};
    parse_property("minE(c)[<=20]: <> true", pb);
    const auto& errs = doc.get_errors();
    REQUIRE(errs.size() == 1);
    CHECK(errs[0].msg == "All channels must be broadcast");
}

TEST_CASE("PropertyBuilder::parse(buf)/clear()/begin()/end() are directly usable")
{
    // Every other test in this file drives parsing via the free
    // parse_property() function; PropertyBuilder::parse(const char*) is its
    // own public one-argument member overload, never exercised that way.
    auto doc = document_fixture{}.add_default_process().parse();
    auto pb = PropertyBuilder{doc};
    pb.parse("A[] true");
    REQUIRE(doc.get_errors().empty());
    CHECK(pb.begin() != pb.end());
    pb.clear();
    CHECK(pb.begin() == pb.end());
}

TEST_CASE("PropertyBuilder::parse(FILE*) parses queries from a file stream")
{
    auto doc = document_fixture{}.add_default_process().parse();
    auto path = std::filesystem::temp_directory_path() / "utap_property_test.q";
    {
        auto ofs = std::ofstream{path};
        ofs << "A[] true\n";
    }
    auto* file = std::fopen(path.string().c_str(), "r");
    REQUIRE(file != nullptr);
    auto pb = PropertyBuilder{doc};
    pb.parse(file);
    std::fclose(file);
    std::filesystem::remove(path);
    CHECK(doc.get_errors().empty());
    REQUIRE(pb.getProperties().size() == 1);
}

TEST_CASE("PropertyBuilder::parse(buf, xpath, options) attaches options to the parsed query")
{
    auto doc = document_fixture{}.add_default_process().parse();
    auto pb = PropertyBuilder{doc};
    auto opts = Options{};
    opts.emplace_back("Key", "Value");
    pb.parse("A[] true", "some/xpath", opts);
    REQUIRE(doc.get_errors().empty());
    REQUIRE(pb.getProperties().size() == 1);
    REQUIRE(pb.getProperties().back().options.size() == 1);
    CHECK(pb.getProperties().back().options.front().name == "Key");
}

namespace {
/// Exposes PropertyBuilder's protected members (from the ParserBuilder
/// interface and its own typeCheck/allowProcessReferences) for direct
/// testing -- add_variable/add_function/typeCheck/allowProcessReferences are
/// never called by the grammar since queries cannot declare variables or
/// functions, and typeCheck()/allowProcessReferences() are only meant to be
/// called by (or overridden for) library consumers.
struct ExposedPropertyBuilder : PropertyBuilder
{
    using PropertyBuilder::PropertyBuilder;
    using PropertyBuilder::add_function;
    using PropertyBuilder::add_variable;
    using PropertyBuilder::allowProcessReferences;
    using PropertyBuilder::typeCheck;
};
}  // namespace

TEST_CASE("add_variable/add_function are not supported by PropertyBuilder")
{
    auto doc = document_fixture{}.add_default_process().parse();
    auto pb = ExposedPropertyBuilder{doc};
    CHECK_THROWS_WITH_AS(pb.add_variable(Type{}, "x", Expression{}, position_t{}), "add_variable is not supported",
                         NotSupportedException);
    CHECK_THROWS_WITH_AS(pb.add_function(Type{}, "f", position_t{}), "add_function is not supported",
                         NotSupportedException);
}

TEST_CASE("allowProcessReferences and typeCheck are directly usable")
{
    auto doc = document_fixture{}.add_default_process().parse();
    auto pb = ExposedPropertyBuilder{doc};
    CHECK(pb.allowProcessReferences());
    auto expr = parse_expression("1+1", doc, false);
    CHECK_NOTHROW(pb.typeCheck(expr));
}

TEST_CASE("handle_expect covers every status/unit token")
{
    struct Case
    {
        const char* token;
        const char* label;
    };
    // clang-format off
    const auto cases = {
        Case{"F", "status"}, Case{"MT", "status"}, Case{"MF", "status"}, Case{"E", "status"},
        Case{"1B", "unit"}, Case{"1MB", "unit"}, Case{"1GB", "unit"}, Case{"1TB", "unit"},
        Case{"1MS", "unit"}, Case{"1M", "unit"}, Case{"1H", "unit"}, Case{"1D", "unit"},
        Case{"1", "bare-number"}, Case{"1XY", "invalid-unit"}, Case{"not_a_token", "invalid-token"},
    };  // clang-format on
    for (const auto& c : cases) {
        auto doc = document_fixture{}.add_default_process().parse();
        auto pb = TigaPropertyBuilder{doc};
        REQUIRE(parse_property("A[] true", pb) == 0);
        CHECK_NOTHROW(pb.handle_expect(c.token));
    }
}

TEST_SUITE_END();
