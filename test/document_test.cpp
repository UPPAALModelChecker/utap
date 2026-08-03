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

/// Checks text containment in unit testing
using doctest::Contains;

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

TEST_CASE("Location::print includes the exponential rate when present")
{
    auto doc = document_fixture{}
                   .add_template(R"XML(<template>
        <name>T</name>
        <location id="id0" x="0" y="0"><label kind="exponentialrate">2</label></location>
        <init ref="id0"/>
    </template>)XML")
                   .add_system_decl("Process = T();")
                   .add_process("Process")
                   .parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    CHECK(doc.get_templates().front().locations.front().str() == "LOCATION (_id0, , 2)");
}

TEST_CASE("Edge::print includes the synchronisation label when present")
{
    auto doc = document_fixture{}
                   .add_global_decl("chan ch;")
                   .add_template(R"XML(<template>
        <name>T</name>
        <location id="id0" x="0" y="0"/>
        <location id="id1" x="10" y="10"/>
        <init ref="id0"/>
        <transition><source ref="id0"/><target ref="id1"/><label kind="synchronisation">ch!</label></transition>
    </template>)XML")
                   .add_system_decl("Process = T();")
                   .add_process("Process")
                   .parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    CHECK(doc.get_templates().front().edges.front().str() ==
          "EDGE (LOCATION (_id0, , ) LOCATION (_id1, , ))\n\t1, ch!, 1");
}

TEST_CASE("Function::print handles more than one parameter")
{
    auto doc = document_fixture{}.add_global_decl("int f(int x, int y) { return x+y; }").add_default_process().parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    CHECK(doc.get_globals().functions.front().str() == Contains{"f(int x, int y)"});
}

TEST_CASE("Instance::print_parameters/print_arguments handle more than one parameter")
{
    auto doc = document_fixture{}
                   .add_template(template_fixture{"T"}.add_parameter("int p").add_parameter("int q").str())
                   .add_system_decl("Process = T(5, 6);")
                   .add_process("Process")
                   .parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    const auto& process = doc.get_processes().front();
    CHECK(process.parameters_str() == "int p, int q");
    CHECK(process.arguments_str() == "5, 6");
}

TEST_CASE("add_location throws on a duplicate location name")
{
    auto doc = document_fixture{}
                   .add_template(R"XML(<template>
        <name>T</name>
        <location id="id0" x="0" y="0"><name>L</name></location>
        <location id="id1" x="10" y="10"><name>L</name></location>
        <init ref="id0"/>
    </template>)XML")
                   .add_system_decl("Process = T();")
                   .add_process("Process")
                   .parse();
    const auto& errs = doc.get_errors();
    REQUIRE(errs.size() == 1);
    CHECK(errs.front().msg == "$Duplicate_definition_of L");
}

TEST_CASE("add_branchpoint throws on a duplicate branchpoint id")
{
    // Unlike locations, branchpoints have no <name> element in the XML
    // schema -- their internal name is derived from the (supposedly
    // unique) "id" attribute, so a duplicate id is what triggers this.
    auto doc = document_fixture{}
                   .add_template(R"XML(<template>
        <name>T</name>
        <location id="id0" x="0" y="0"/>
        <branchpoint id="id1" x="10" y="10"/>
        <branchpoint id="id1" x="20" y="20"/>
        <init ref="id0"/>
    </template>)XML")
                   .add_system_decl("Process = T();")
                   .add_process("Process")
                   .parse();
    const auto& errs = doc.get_errors();
    REQUIRE(errs.size() == 1);
    CHECK(errs.front().msg == "$Duplicate_definition_of _id1");
    const auto& warns = doc.get_warnings();
    REQUIRE(warns.size() == 1);
    CHECK(warns.front().msg == "$Non-unique_id_attribute_value: id1");
}

TEST_CASE("add_edge supports a branchpoint as the edge source")
{
    // The XML schema requires all <location> elements before any
    // <branchpoint>, which must come before <init>/<transition>.
    auto doc = document_fixture{}
                   .add_template(R"XML(<template>
        <name>T</name>
        <location id="id0" x="0" y="0"/>
        <location id="id2" x="20" y="20"/>
        <branchpoint id="id1" x="10" y="10"/>
        <init ref="id0"/>
        <transition><source ref="id0"/><target ref="id1"/></transition>
        <transition><source ref="id1"/><target ref="id2"/></transition>
    </template>)XML")
                   .add_system_decl("Process = T();")
                   .add_process("Process")
                   .parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    REQUIRE(doc.get_templates().front().edges.size() == 2);
    CHECK(doc.get_templates().front().edges[1].src == nullptr);
    CHECK(doc.get_templates().front().edges[1].srcb != nullptr);
}

TEST_CASE("ChanPriority::print renders the default keyword")
{
    auto doc = document_fixture{}
                   .add_global_decl("chan c1; chan priority default;")
                   .add_default_process()
                   .parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    REQUIRE(doc.get_chan_priorities().size() == 1);
    CHECK(doc.get_chan_priorities().front().str() == "chan priority default");
}

TEST_CASE("LSC scenario: simregion construction, instance filtering and cuts")
{
    // Based on models/lsc_example.xml (3 messages, 2 conditions across 4
    // instance lines), with an extra unpaired condition+update (at a fresh
    // location, anchored to instance "id8") and a second, fully unpaired
    // update, to exercise the otherwise-untested LSC machinery:
    // Template::add_instance_line/add_message/add_condition/add_update,
    // LSCInstanceLine::add_parameters (via the "LscTemplate(2,3)"
    // instantiation), Template::get_simregions's "remaining conditions" and
    // "remaining updates" passes, both get_update() overloads,
    // LSCInstanceLine::get_simregions, LSCSimRegion, and LSCCut. None of
    // this is called from within UTAP itself -- it exists for the Uppaal
    // engine to consume after parsing an LSC scenario.
    static constexpr auto xml = R"XML(<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE nta PUBLIC '-//Uppaal Team//DTD Flat System 1.1//EN' 'http://www.it.uu.se/research/group/darts/uppaal/flat-1_2.dtd'>
<nta>
    <declaration>chan m1, m3, m4, m2;
clock x;</declaration>
    <template>
        <name x="5" y="5">A</name>
        <location id="id0" x="16" y="-40"></location>
        <init ref="id0"/>
        <transition><source ref="id0"/><target ref="id0"/><label kind="synchronisation" x="0" y="32">m2?</label></transition>
        <transition><source ref="id0"/><target ref="id0"/><label kind="synchronisation" x="0" y="-136">m4?</label></transition>
    </template>
    <template>
        <name>B</name>
        <location id="id1" x="0" y="96"><name x="-8" y="128">loc2</name><label kind="invariant" x="-10" y="111">x&lt;=5</label></location>
        <location id="id2" x="0" y="-48"><name x="-16" y="-96">loc1</name><label kind="invariant" x="-16" y="-80">x&lt;=5</label></location>
        <init ref="id2"/>
        <transition><source ref="id1"/><target ref="id2"/><label kind="synchronisation" x="32" y="0">m2!</label></transition>
        <transition><source ref="id2"/><target ref="id1"/><label kind="guard" x="-64" y="0">x&gt;=3</label><label kind="synchronisation" x="-64" y="15">m1!</label></transition>
    </template>
    <template>
        <name>C</name>
        <location id="id3" x="96" y="96"><name x="80" y="112">loc5</name><committed/></location>
        <location id="id4" x="0" y="96"><name x="-16" y="112">loc4</name></location>
        <location id="id5" x="0" y="0"><name x="-10" y="-30">loc3</name></location>
        <init ref="id5"/>
        <transition><source ref="id3"/><target ref="id5"/><label kind="synchronisation" x="96" y="24">m4!</label></transition>
        <transition><source ref="id5"/><target ref="id4"/><label kind="synchronisation" x="-32" y="40">m1?</label></transition>
        <transition><source ref="id4"/><target ref="id3"/><label kind="synchronisation" x="32" y="96">m3!</label></transition>
    </template>
    <template>
        <name>D</name>
        <location id="id6" x="0" y="104"></location>
        <location id="id7" x="0" y="0"></location>
        <init ref="id7"/>
        <transition><source ref="id6"/><target ref="id7"/></transition>
        <transition><source ref="id6"/><target ref="id6"/><label kind="synchronisation" x="-8" y="152">m4?</label></transition>
        <transition><source ref="id7"/><target ref="id6"/><label kind="synchronisation" x="8" y="32">m3?</label></transition>
    </template>
    <lsc>
        <name>LscTemplate</name>
        <parameter>int a, int b</parameter>
        <type>Universal</type>
        <mode>Invariant</mode>
        <declaration></declaration>
        <yloccoord number="0" y="0"/>
        <yloccoord number="1" y="56"/>
        <yloccoord number="2" y="104"/>
        <yloccoord number="3" y="144"/>
        <yloccoord number="4" y="168"/>
        <yloccoord number="5" y="220"/>
        <yloccoord number="6" y="260"/>
        <instance id="id8" x="432" y="0"><name x="0" y="0">D</name></instance>
        <instance id="id9" x="288" y="0"><name x="0" y="0">C</name></instance>
        <instance id="id10" x="144" y="0"><name x="0" y="0">B</name></instance>
        <instance id="id11" x="0" y="0"><name x="0" y="0">A</name></instance>
        <prechart x="0" y="104"><lsclocation>2</lsclocation></prechart>
        <message x="0" y="144">
            <source ref="id10"/><target ref="id11"/><lsclocation>3</lsclocation>
            <label kind="message" x="61" y="-18">m2</label>
        </message>
        <message x="0" y="168">
            <source ref="id9"/><target ref="id8"/><lsclocation>4</lsclocation>
            <label kind="message" x="357" y="-18">m3</label>
        </message>
        <message x="0" y="56">
            <source ref="id10"/><target ref="id9"/><lsclocation>1</lsclocation>
            <label kind="message" x="205" y="-18">m1</label>
        </message>
        <condition x="0" y="56">
            <anchor instanceid="id9"/><lsclocation>1</lsclocation><temperature>cold</temperature>
            <label kind="condition">x &gt;=b</label>
        </condition>
        <condition x="0" y="144">
            <anchor instanceid="id11"/><lsclocation>3</lsclocation><temperature>hot</temperature>
            <label kind="condition">x &gt;= a</label>
        </condition>
        <condition x="0" y="220">
            <anchor instanceid="id8"/><lsclocation>5</lsclocation><temperature>cold</temperature>
            <label kind="condition">x &gt;= 0</label>
        </condition>
        <update x="0" y="220">
            <anchor instanceid="id8"/><lsclocation>5</lsclocation>
            <label kind="update">x = 0</label>
        </update>
        <update x="0" y="260">
            <anchor instanceid="id9"/><lsclocation>6</lsclocation>
            <label kind="update">x = 0</label>
        </update>
    </lsc>
    <system>
Scenario = LscTemplate(2,3);
system A, B, C, D;
</system>
    <queries><query><formula>sat: Scenario</formula><comment></comment></query></queries>
</nta>
)XML";
    auto doc = Document{};
    parse_XML_buffer(xml, doc, true);
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    auto& templates = doc.get_templates();
    auto it = std::find_if(templates.begin(), templates.end(),
                           [](auto& t) { return t.uid.get_name() == "LscTemplate"; });
    REQUIRE(it != templates.end());
    auto& t = *it;
    // is_invariant() compares case-sensitively against "invariant", but this
    // model's <mode> is "Invariant" -- so it correctly reports false here.
    CHECK_FALSE(t.is_invariant());
    REQUIRE(t.messages.size() == 3);
    REQUIRE(t.conditions.size() == 3);
    REQUIRE(t.updates.size() == 2);
    REQUIRE(t.instances.size() == 4);

    auto simregions = t.get_simregions();
    // 3 message-anchored (2 with a paired condition), 1 condition+update
    // pair (from the "remaining conditions" pass matching an update via the
    // vector<LSCInstanceLine*> get_update() overload), and 1 lone update
    // (from the "remaining updates" pass).
    REQUIRE(simregions.size() == 5);
    // Regression test: LSCInstanceLine::get_simregions() used to
    // dereference reg.message/reg.update/reg.condition unconditionally,
    // crashing on the routine case where a simregion has 1 or 0 of each
    // (e.g. a message-only simregion has a null .update and .condition).
    auto with_condition =
        std::count_if(simregions.begin(), simregions.end(), [](auto& s) { return s.has_condition(); });
    auto with_update = std::count_if(simregions.begin(), simregions.end(), [](auto& s) { return s.has_update(); });
    auto with_message = std::count_if(simregions.begin(), simregions.end(), [](auto& s) { return s.has_message(); });
    CHECK(with_condition == 3);
    CHECK(with_update == 2);
    CHECK(with_message == 3);
    for (auto& s : simregions) {
        CHECK_NOTHROW((void)s.get_loc());
        CHECK_NOTHROW((void)s.is_in_prechart());
        CHECK_NOTHROW((void)s.str());
    }

    size_t total_anchored = 0;
    for (auto& inst : t.instances)
        total_anchored += inst.get_simregions(simregions).size();
    CHECK(total_anchored > 0);

    REQUIRE(simregions.size() >= 2);
    auto cut = LSCCut{0};
    cut.simregions.push_back(simregions[0]);
    cut.simregions.push_back(simregions[1]);
    CHECK(cut.contains(simregions[0]));
    CHECK(cut.str() == Contains{"CUT("});
    auto other = LSCCut{1};
    other.simregions.push_back(simregions[0]);
    other.simregions.push_back(simregions[1]);
    CHECK(cut.equals(other));
    cut.erase(simregions[0]);
    CHECK_FALSE(cut.contains(simregions[0]));
    CHECK_FALSE(cut.equals(other));
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
