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

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <stdexcept>

using namespace UTAP;

/// Checks text containment in unit testing
using doctest::Contains;

namespace {
/// Writes doc to a temp file via write_XML_file(), reads it back as text,
/// and cleans up. Used to inspect XMLWriter's output since it only writes
/// to a real file path (no in-memory buffer overload).
std::string write_and_read(Document& doc)
{
    auto path = std::filesystem::temp_directory_path() / "utap_xmlwriter_test.xml";
    auto res = write_XML_file(path.string().c_str(), doc);
    REQUIRE(res == 0);
    auto ifs = std::ifstream{path};
    auto content = std::string{std::istreambuf_iterator<char>{ifs}, std::istreambuf_iterator<char>{}};
    ifs.close();  // Windows locks open files, so close explicitly before removing.
    std::filesystem::remove(path);
    return content;
}
}  // namespace

TEST_SUITE_BEGIN("XMLWriter");

TEST_CASE("write_XML_file renders locations, channel priorities and a renamed process")
{
    auto doc = document_fixture{}
                   .add_global_decl("chan c1; chan c2; chan priority c1 < c2; clock c;")
                   .add_template(R"XML(<template>
        <name>T</name>
        <location id="id0" x="0" y="0"><name>Err</name></location>
        <location id="id1" x="10" y="10"><urgent/></location>
        <location id="id2" x="20" y="20"><label kind="exponentialrate">2</label></location>
        <init ref="id0"/>
        <transition><source ref="id0"/><target ref="id0"/></transition>
        <transition><source ref="id0"/><target ref="id1"/></transition>
        <transition><source ref="id1"/><target ref="id2"/></transition>
    </template>)XML")
                   .add_system_decl("MyProc = T();")
                   .add_process("MyProc")
                   .parse();
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    auto xml = write_and_read(doc);
    // "Err" location gets a distinguishing color.
    CHECK(xml == Contains{R"(color="#ff6666")"});
    CHECK(xml == Contains{"<urgent/>"});
    CHECK(xml == Contains{R"(<label kind="exponentialrate")"});
    CHECK(xml == Contains{"2</label>"});
    // A self-loop (source == target) is rendered as nails, not a straight edge.
    CHECK(xml == Contains{"<nail"});
    // Channel priorities are rendered as a declaration comment/statement.
    CHECK(xml == Contains{"channel priorities"});
    CHECK(xml == Contains{"chan priority c1"});
    // A process whose instance name differs from its template name gets an
    // explicit "Name = Template(...);" instantiation line.
    CHECK(xml == Contains{"MyProc = T();"});
    CHECK(xml == Contains{"system MyProc;"});
}

TEST_CASE("write_XML_file omits LSC templates but writes ordinary ones")
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
    const auto& errs = doc.get_errors();
    CHECK_MESSAGE(errs.empty(), errs.front().msg);
    auto out = write_and_read(doc);
    // taTempl() returns early for non-TA (LSC) templates.
    CHECK_FALSE(out == Contains{"LscTemplate"});
    CHECK(out == Contains{"<name>A</name>"});
}

TEST_CASE("write_XML_file throws when the output path cannot be opened")
{
    auto doc = document_fixture{}.add_default_process().parse();
    CHECK_THROWS_AS(write_XML_file("/nonexistent_dir_xyz/out.xml", doc), std::runtime_error);
}

TEST_SUITE_END();
