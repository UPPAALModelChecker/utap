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

#include <algorithm>

TEST_SUITE_BEGIN("Document");

using namespace UTAP;

TEST_CASE("find_template finds an existing template and returns nullptr otherwise")
{
    auto doc = document_fixture{}.add_default_process().parse();
    CHECK(doc.find_template("Template") != nullptr);
    CHECK(doc.find_template("NoSuchTemplate") == nullptr);
}

TEST_CASE("get_dynamic_templates lists declared-and-defined dynamic templates")
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
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    REQUIRE(doc.get_dynamic_templates().size() == 1);
    CHECK(doc.get_dynamic_templates().front()->uid.get_name() == "Child");
}

TEST_CASE("queries_empty reflects whether any query has been parsed")
{
    auto doc = document_fixture{}.add_default_process().parse();
    CHECK(doc.queries_empty());
}

TEST_CASE("get_options/set_options round-trip")
{
    auto doc = document_fixture{}.add_default_process().parse();
    CHECK(doc.get_options().empty());
    doc.get_options().emplace_back("Key", "Value");
    REQUIRE(doc.get_options().size() == 1);
    auto opts = doc.get_options();
    opts.emplace_back("Other", "2");
    doc.set_options(opts);
    CHECK(doc.get_options().size() == 2);
}

TEST_CASE("get_proc_priority reflects a system-level priority ordering")
{
    static constexpr auto xta = R"XTA(
process T() { state L0; init L0; }
P1 = T();
P2 = T();
system P1 < P2;
)XTA";
    auto doc = Document{};
    REQUIRE(parse_XTA(xta, doc, true));
    CHECK(doc.get_proc_priority("P1") < doc.get_proc_priority("P2"));
}

TEST_CASE("remove_process removes an instance from the process list")
{
    auto doc = document_fixture{}.add_default_process().parse();
    auto& processes = doc.get_processes();
    const auto before = processes.size();
    REQUIRE(before > 0);
    doc.remove_process(processes.front());
    CHECK(doc.get_processes().size() == before - 1);
}

TEST_CASE("copy_variables_from_to copies a template's local variables")
{
    auto doc = document_fixture{}
                   .add_template(R"XML(<template>
        <name>T1</name>
        <declaration>int x;</declaration>
        <location id="id0" x="0" y="0"/>
        <init ref="id0"/>
    </template>)XML")
                   .add_template(R"XML(<template>
        <name>T2</name>
        <location id="id0" x="0" y="0"/>
        <init ref="id0"/>
    </template>)XML")
                   .add_system_decl("Process = T1();")
                   .add_process("Process")
                   .parse();
    auto& templates = doc.get_templates();
    auto t1 = std::find_if(templates.begin(), templates.end(), [](auto& t) { return t.uid.get_name() == "T1"; });
    auto t2 = std::find_if(templates.begin(), templates.end(), [](auto& t) { return t.uid.get_name() == "T2"; });
    REQUIRE(t1 != templates.end());
    REQUIRE(t2 != templates.end());
    CHECK(t2->variables.empty());
    doc.copy_variables_from_to(&*t1, &*t2);
    REQUIRE(t2->variables.size() == 1);
    CHECK(t2->variables.front().uid.get_name() == "x");
    // copy_functions_from_to is currently an intentional no-op (see its
    // comment: "to be implemented"); call it so it's still exercised.
    doc.copy_functions_from_to(&*t1, &*t2);
}

TEST_CASE("add_gantt registers a gantt chart entry, parsed after the system declaration")
{
    // The gantt block follows `system ...;` per the grammar
    // (System: SysDecl Progress GanttDecl), which document_fixture's
    // add_system_decl() cannot express since it inserts text before that
    // line -- build the document manually.
    static constexpr auto xml = R"XML(<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE nta PUBLIC '-//Uppaal Team//DTD Flat System 1.6//EN' 'https://www.it.uu.se/research/group/darts/uppaal/flat-1_6.dtd'>
<nta>
    <declaration>bool b;</declaration>
    <template>
        <name x="5" y="5">Template</name>
        <location id="id0" x="0" y="0"/>
        <init ref="id0"/>
    </template>
    <system>
Process = Template();
system Process;
gantt { G : b -> b; }
    </system>
</nta>
)XML";
    auto doc = UTAP::Document{};
    parse_XML_buffer(xml, doc, true);
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    CHECK(doc.get_globals().ganttChart.size() == 1);
}

TEST_CASE("add_io_decl appends a new IODecl to the global declarations")
{
    auto doc = document_fixture{}.add_default_process().parse();
    const auto before = doc.get_globals().iodecl.size();
    auto* decl = doc.add_io_decl();
    REQUIRE(decl != nullptr);
    CHECK(doc.get_globals().iodecl.size() == before + 1);
}

TEST_CASE("ChanPriority::print/str renders a channel priority declaration")
{
    auto doc = document_fixture{}
                   .add_global_decl("chan c1; chan c2; chan priority c1 < c2;")
                   .add_default_process()
                   .parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    REQUIRE(doc.get_chan_priorities().size() == 1);
    CHECK(doc.get_chan_priorities().front().str() == "chan priority c1 < c2");
}

TEST_CASE("Location::print/str handles locations with and without an invariant")
{
    // Regression test: Location::print() used to call .print() on its
    // (possibly empty) invariant/exp_rate Expression members
    // unconditionally, crashing with a null-pointer dereference for the
    // very common case of a location with no invariant.
    auto doc = document_fixture{}
                   .add_global_decl("clock c;")
                   .add_template(R"XML(<template>
        <name>T</name>
        <location id="id0" x="0" y="0"/>
        <location id="id1" x="10" y="10"><label kind="invariant">c &lt; 5</label></location>
        <init ref="id0"/>
    </template>)XML")
                   .add_system_decl("Process = T();")
                   .add_process("Process")
                   .parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    const auto& t = doc.get_templates().front();
    REQUIRE(t.locations.size() == 2);
    CHECK(t.locations[0].str() == "LOCATION (_id0, , )");
    // TypeChecker's RateDecomposer folds invariants into an "1 && ..."
    // conjunction (it seeds the accumulator with a constant true), hence
    // the "1 &&" prefix below rather than a bare "(c < 5)".
    CHECK(t.locations[1].str() == "LOCATION (_id1, 1 && c < 5, )");
}

TEST_CASE("Edge::print/str handles edges with and without a guard/sync/assignment")
{
    // Regression test, same root cause as the Location one above: Edge::print()
    // unconditionally called .print() on its (possibly empty) guard/sync/assign.
    auto doc = document_fixture{}
                   .add_global_decl("bool b;")
                   .add_template(R"XML(<template>
        <name>T</name>
        <location id="id0" x="0" y="0"/>
        <location id="id1" x="10" y="10"/>
        <location id="id2" x="20" y="20"/>
        <init ref="id0"/>
        <transition><source ref="id0"/><target ref="id1"/></transition>
        <transition><source ref="id1"/><target ref="id2"/><label kind="guard">b</label></transition>
    </template>)XML")
                   .add_system_decl("Process = T();")
                   .add_process("Process")
                   .parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    const auto& t = doc.get_templates().front();
    REQUIRE(t.edges.size() == 2);
    // TypeChecker defaults a missing guard/assignment to the constant 1
    // (true / no-op), but leaves a missing synchronisation genuinely empty
    // -- which is what Edge::print() used to crash on.
    CHECK(t.edges[0].str() == "EDGE (LOCATION (_id0, , ) LOCATION (_id1, , ))\n\t1, , 1");
    CHECK(t.edges[1].str() == "EDGE (LOCATION (_id1, , ) LOCATION (_id2, , ))\n\tb, , 1");
}

TEST_CASE("Variable::str, Function::str and Declarations::str")
{
    auto doc = document_fixture{}
                   .add_default_process()
                   .add_global_decl("int g = 1; int f(int x) { return x; }")
                   .parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    auto& globals = doc.get_globals();
    auto g = std::find_if(globals.variables.begin(), globals.variables.end(),
                          [](auto& v) { return v.uid.get_name() == "g"; });
    REQUIRE(g != globals.variables.end());
    CHECK(g->str() == "int g = 1");
    REQUIRE(!globals.functions.empty());
    CHECK(globals.functions.front().str() == Contains{"f(int x)"});
    // Declarations::str(bool) hides the Stringify<Declarations>::str() base
    // overload for ordinary lookup; call it explicitly.
    CHECK(static_cast<const Stringify<Declarations>&>(globals).str() == Contains{"int g = 1;"});
}

TEST_CASE("Template::is_invariant reflects an LSC template's declared mode")
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
    auto doc = UTAP::Document{};
    parse_XML_buffer(xml, doc, true);
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    const auto* t = doc.find_template("LscTemplate");
    REQUIRE(t != nullptr);
    CHECK(t->is_invariant());
}

TEST_CASE("Instance::arguments_str/mapping_str/print_arguments/print_mapping")
{
    auto doc = document_fixture{}
                   .add_template(template_fixture{"T"}.add_parameter("int p").str())
                   .add_system_decl("Process = T(5);")
                   .add_process("Process")
                   .parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    REQUIRE(!doc.get_processes().empty());
    const auto& process = doc.get_processes().front();
    CHECK(process.arguments_str() == "5");
    CHECK(process.mapping_str() == "p = 5\n");
}

TEST_SUITE_END();
