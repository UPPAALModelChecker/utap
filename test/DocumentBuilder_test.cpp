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

#include "utap/DocumentBuilder.hpp"

#include <doctest/doctest.h>

TEST_SUITE_BEGIN("DocumentBuilder");

using namespace UTAP;

TEST_CASE("before_update/after_update declarations")
{
    auto doc =
        document_fixture{}
            .add_default_process()
            .add_global_decl("bool b; before_update { b = true } after_update { b = false }")
            .parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
}

TEST_CASE("gantt chart with a declaration-level select")
{
    // Exercises gantt_decl_select() via the "G(i:int[0,2])" select clause.
    // The gantt block must follow `system ...;` per the grammar (System:
    // SysDecl Progress GanttDecl), which document_fixture's
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
gantt { G(i:int[0,2]) : b -> b; }
    </system>
</nta>
)XML";
    auto doc = UTAP::Document{};
    parse_XML_buffer(xml, doc, true);
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    CHECK(doc.get_globals().ganttChart.size() == 1);
}

TEST_CASE("gantt chart entry with a for-select")
{
    // Exercises gantt_entry_select() via "for (j:int[0,2])".
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
gantt { H : for (j:int[0,2]) b -> b; }
    </system>
</nta>
)XML";
    auto doc = UTAP::Document{};
    parse_XML_buffer(xml, doc, true);
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    CHECK(doc.get_globals().ganttChart.size() == 1);
}

TEST_CASE("edge probability label")
{
    auto doc = document_fixture{}
                   .add_template(R"XML(<template>
        <name>T</name>
        <location id="id0" x="0" y="0"/>
        <location id="id1" x="10" y="10"/>
        <init ref="id0"/>
        <transition>
            <source ref="id0"/>
            <target ref="id1"/>
            <label kind="probability">1</label>
        </transition>
    </template>)XML")
                   .add_system_decl("Process = T();")
                   .add_process("Process")
                   .parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
}

TEST_CASE("queries-level option registers a model option")
{
    // Regression test: model_options() used to call begin(Tag::OPTION) with
    // the default skipEmpty=true, which silently skips self-closing
    // <option key="..." value="..."/> tags (the normal way to write an
    // attribute-only element) -- so a top-level <queries><option .../>
    // was dropped even though the identical tag inside a <query> worked
    // fine (query_options()'s XMLReader::option() correctly passes false).
    // model_options() also leaked the key/value strings returned by
    // getAttribute() (an xmlChar* the caller must xmlFree()).
    static constexpr auto xml = R"XML(<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE nta PUBLIC '-//Uppaal Team//DTD Flat System 1.6//EN' 'https://www.it.uu.se/research/group/darts/uppaal/flat-1_6.dtd'>
<nta>
    <declaration></declaration>
    <template>
        <name>T</name>
        <location id="id0" x="0" y="0"/>
        <init ref="id0"/>
    </template>
    <system>
Process = T();
system Process;
    </system>
    <queries>
        <option key="Global" value="1"/>
        <query><formula/><comment/></query>
    </queries>
</nta>
)XML";
    auto doc = UTAP::Document{};
    parse_XML_buffer(xml, doc, true);
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    REQUIRE(doc.get_options().size() == 1);
    CHECK(doc.get_options().front().name == "Global");
    CHECK(doc.get_options().front().value == "1");
}

TEST_CASE("per-query option, expectation and resource")
{
    // Regression test: expectation() read the <expect> tag's own attributes
    // but never called read() to descend into its children before scanning
    // for nested <resource> tags, so begin(Tag::RESOURCE, false) always saw
    // the still-current <expect> element and returned false immediately --
    // any <resource> children were silently dropped. It also leaked the
    // outcome/type/value attribute strings returned by getAttribute().
    static constexpr auto xml = R"XML(<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE nta PUBLIC '-//Uppaal Team//DTD Flat System 1.6//EN' 'https://www.it.uu.se/research/group/darts/uppaal/flat-1_6.dtd'>
<nta>
    <declaration></declaration>
    <template>
        <name>T</name>
        <location id="id0" x="0" y="0"/>
        <init ref="id0"/>
    </template>
    <system>
Process = T();
system Process;
    </system>
    <queries>
        <query>
            <formula>A[] not deadlock</formula>
            <comment>test</comment>
            <option key="Local" value="2"/>
            <expect outcome="success" type="value" value="42">
                <resource type="memory" value="100" unit="KB"/>
            </expect>
        </query>
    </queries>
</nta>
)XML";
    auto doc = UTAP::Document{};
    parse_XML_buffer(xml, doc, true);
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    REQUIRE(doc.get_queries().size() == 1);
    const auto& q = doc.get_queries().front();
    REQUIRE(q.options.size() == 1);
    CHECK(q.options.front().name == "Local");
    CHECK(q.expectation.status == QueryStatus::True);
    CHECK(q.expectation.value_type == ExpectationKind::NumericValue);
    CHECK(q.expectation.value == "42");
    REQUIRE(q.expectation.resources.size() == 1);
    CHECK(q.expectation.resources.front().name == "memory");
    CHECK(q.expectation.resources.front().value == "100");
}

TEST_CASE("query_results_begin/end")
{
    // Declared in the ParserBuilder interface and implemented by
    // DocumentBuilder, but never actually invoked from xmlreader.cpp or
    // parser.y (no XML tag or grammar rule calls them) -- call them
    // directly to exercise their (trivial) bodies.
    auto doc = document_fixture{}.add_default_process().parse();
    auto builder = DocumentBuilder{doc};
    CHECK_NOTHROW(builder.query_results_begin());
    CHECK_NOTHROW(builder.query_results_end());
}

TEST_SUITE_END();
