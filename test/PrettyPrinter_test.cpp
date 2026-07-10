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
 * PrettyPrinter is a ParserBuilder that reconstructs UPPAAL source text
 * straight from the parser's callback stream (types, declarations,
 * statements, expressions, templates, system declaration and queries),
 * as used by the `pretty` command-line tool. This is a different code
 * path from Expression::str()/Document printing (see prettyprint_test.cpp),
 * so it needs its own model-driven tests.
 */

#include "document_fixture.h"

#include "utap/AbstractBuilder.hpp"
#include "utap/PrettyPrinter.hpp"
#include "utap/utap.hpp"

#include <doctest/doctest.h>

#include <sstream>

using namespace UTAP;

/// Checks text containment in unit testing
using doctest::Contains;

TEST_SUITE_BEGIN("PrettyPrinter");

TEST_CASE("Template with locations, rates, invariants and guarded edges")
{
    auto os = std::ostringstream{};
    auto pretty = PrettyPrinter{os};
    parse_XML_buffer(read_content("simpleSystem.xml").c_str(), pretty, true);
    const auto text = os.str();
    CHECK(text == Contains{"clock c;"});
    CHECK(text == Contains{"process Template()"});
    CHECK(text == Contains{"L3 { ; 1},"});
    CHECK(text == Contains{"First {(c < 2) ; 1};"});
    CHECK(text == Contains{"init First;"});
    CHECK(text == Contains{"First -> L2 {"});
    CHECK(text == Contains{"guard (c > 1);"});
    CHECK(text == Contains{"Process = Template();"});
    CHECK(text == Contains{"Process2 = Template();"});
    CHECK(text == Contains{"system Process, Process2;"});
    CHECK(text == Contains{"/** Query begin: */"});
    CHECK(text == Contains{"/** Query end. */"});
}

TEST_CASE("Function declaration with if/else and return statements")
{
    auto os = std::ostringstream{};
    auto pretty = PrettyPrinter{os};
    parse_XML_buffer(read_content("if_statement.xml").c_str(), pretty, true);
    const auto text = os.str();
    CHECK(text == Contains{"int some_fun(bool x)"});
    CHECK(text == Contains{"if (x)"});
    CHECK(text == Contains{"return 1;"});
    CHECK(text == Contains{"else"});
}

TEST_CASE("Const/typedef declarations, arithmetic and non-empty query text")
{
    auto os = std::ostringstream{};
    auto pretty = PrettyPrinter{os};
    parse_XML_buffer(read_content("powers.xml").c_str(), pretty, true);
    const auto text = os.str();
    CHECK(text == Contains{"const int C = (A + B);"});
    CHECK(text == Contains{"const int ISIZE = (IBASE ** IPOWER);"});
    CHECK(text == Contains{"typedef int[0,(ISIZE - 1)] range_t;"});
    CHECK(text == Contains{"range_t ii = (3 ** 3);"});
    CHECK(text == Contains{"/* Formula: A[] not deadlock */"});
    CHECK(text == Contains{"/* Comment: Simple query */"});
}

TEST_CASE("Struct, array, string, loops and expression operators in a function body")
{
    static constexpr auto model = R"xml(<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE nta PUBLIC '-//Uppaal Team//DTD Flat System 1.5//EN' 'http://www.it.uu.se/research/group/darts/uppaal/flat-1_5.dtd'>
<nta>
	<declaration>struct { int x; int y; } point = {1, 2};
int arr[3] = {1, 2, 3};
string label = "hello";

int compute2(int v) { return v; }

int compute(int a, int b) {
    int total = 0;
    int i;
    int result;
    int x2, y2;
    for (i = 0, x2 = 0; i &lt; 3; i++) {
        total += arr[i];
    }
    for (i : int[0,2]) {
        if (i == 1) {
            continue;
        }
        total = total + i;
    }
    while (total &gt; 1000) {
        total--;
        break;
    }
    result = (a &gt; b) ? a : b;
    y2 = b;
    point.x = a;
    if (forall (k : int[0,2]) arr[k] &gt;= 0) {
        result = result + compute2(result);
    }
    ++total;
    --x2;
    return result + point.y;
}</declaration>
	<template>
		<name>T</name>
		<location id="id0" x="0" y="0">
		</location>
		<init ref="id0"/>
	</template>
	<system>system T;
    </system>
	<queries>
		<query>
			<formula/>
			<comment/>
		</query>
	</queries>
</nta>
)xml";
    auto os = std::ostringstream{};
    auto pretty = PrettyPrinter{os};
    parse_XML_buffer(model, pretty, true);
    const auto text = os.str();
    CHECK(text == Contains{"struct {"});
    CHECK(text == Contains{"} point = { 1, 2 };"});
    CHECK(text == Contains{"int arr[3] = { 1, 2, 3 };"});
    CHECK(text == Contains{"string label = \"hello\";"});
    CHECK(text == Contains{"for ( (i = 0), (x2 = 0); (i < 3); i++)"});
    CHECK(text == Contains{"for ( i : int[0,2] )"});
    CHECK(text == Contains{"continue;"});
    CHECK(text == Contains{"while ((total > 1000))"});
    CHECK(text == Contains{"break;"});
    CHECK(text == Contains{"(total += arr[i]);"});
    CHECK(text == Contains{"total--;"});
    CHECK(text == Contains{"(result = (a > b) ? a : b);"});
    CHECK(text == Contains{"(point.x = a);"});
    CHECK(text == Contains{"if (forall (k:int[0,2]) (arr[k] >= 0))"});
    CHECK(text == Contains{"(result = (result + compute2(result)));"});
    CHECK(text == Contains{"++total;"});
    CHECK(text == Contains{"--x2;"});
}

TEST_CASE("Urgent/committed locations, branchpoints, select and channel sync")
{
    static constexpr auto model = R"xml(<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE nta PUBLIC '-//Uppaal Team//DTD Flat System 1.5//EN' 'http://www.it.uu.se/research/group/darts/uppaal/flat-1_5.dtd'>
<nta>
	<declaration>urgent chan a;
broadcast chan b;
clock c;</declaration>
	<template>
		<name>T</name>
		<location id="id0" x="0" y="0">
			<name>Idle</name>
		</location>
		<location id="id1" x="10" y="10">
			<name>Urg</name>
			<urgent/>
		</location>
		<location id="id2" x="20" y="20">
			<name>Comm</name>
			<committed/>
		</location>
		<branchpoint id="id3" x="30" y="30"/>
		<init ref="id0"/>
		<transition>
			<source ref="id0"/>
			<target ref="id1"/>
			<label kind="select">i:int[0,2]</label>
			<label kind="guard">c &gt;= i</label>
			<label kind="synchronisation">a!</label>
			<label kind="assignment">c := 0</label>
		</transition>
		<transition>
			<source ref="id1"/>
			<target ref="id2"/>
			<label kind="synchronisation">b?</label>
		</transition>
		<transition>
			<source ref="id2"/>
			<target ref="id3"/>
		</transition>
		<transition>
			<source ref="id3"/>
			<target ref="id0"/>
		</transition>
	</template>
	<system>system T;
    </system>
	<queries>
		<query>
			<formula/>
			<comment/>
		</query>
	</queries>
</nta>
)xml";
    auto os = std::ostringstream{};
    auto pretty = PrettyPrinter{os};
    parse_XML_buffer(model, pretty, true);
    const auto text = os.str();
    CHECK(text == Contains{"urgent chan a;"});
    CHECK(text == Contains{"broadcast chan b;"});
    CHECK(text == Contains{"branchpoint _id3;"});
    CHECK(text == Contains{"commit Comm;"});
    CHECK(text == Contains{"urgent Urg;"});
    CHECK(text == Contains{"select i:int[0,2];"});
    CHECK(text == Contains{"guard (c >= i);"});
    CHECK(text == Contains{"sync a!;"});
    CHECK(text == Contains{"assign (c = 0);"});
    CHECK(text == Contains{"sync b?;"});
}

TEST_CASE("External function import does not leak its parameters into the next process")
{
    // Regression test: decl_external_func() used to be a no-op, leaving the
    // `param` string accumulated by decl_parameter() (and the return type
    // pushed for the import) to leak into the next proc_begin()/decl_func_begin().
    static constexpr auto model = R"xml(<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE nta PUBLIC '-//Uppaal Team//DTD Flat System 1.5//EN' 'http://www.it.uu.se/research/group/darts/uppaal/flat-1_5.dtd'>
<nta>
	<declaration>import "libexternal.so" {
    int extfun(int v);
};</declaration>
	<template>
		<name>T</name>
		<location id="id0" x="0" y="0">
		</location>
		<init ref="id0"/>
	</template>
	<system>system T;
    </system>
	<queries>
		<query>
			<formula/>
			<comment/>
		</query>
	</queries>
</nta>
)xml";
    auto os = std::ostringstream{};
    auto pretty = PrettyPrinter{os};
    parse_XML_buffer(model, pretty, true);
    const auto text = os.str();
    CHECK(text == Contains{"process T()\n"});
    CHECK_FALSE(text == Contains{"extfun"});
    CHECK_FALSE(text == Contains{"process T(int v)"});
}

TEST_CASE("do-while loop prints its body and condition")
{
    // Regression test: do_while_begin()/do_while_end() used to be no-ops,
    // silently dropping the loop body and condition from the output.
    static constexpr auto model = R"xml(<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE nta PUBLIC '-//Uppaal Team//DTD Flat System 1.5//EN' 'http://www.it.uu.se/research/group/darts/uppaal/flat-1_5.dtd'>
<nta>
	<declaration>int compute(int total) {
    do {
        total--;
    } while (total &gt; 0);
    return total;
}</declaration>
	<template>
		<name>T</name>
		<location id="id0" x="0" y="0">
		</location>
		<init ref="id0"/>
	</template>
	<system>system T;
    </system>
	<queries>
		<query>
			<formula/>
			<comment/>
		</query>
	</queries>
</nta>
)xml";
    auto os = std::ostringstream{};
    auto pretty = PrettyPrinter{os};
    parse_XML_buffer(model, pretty, true);
    const auto text = os.str();
    CHECK(text == Contains{"do\n"});
    CHECK(text == Contains{"total--;"});
    CHECK(text == Contains{"while ((total > 0));"});
}

TEST_CASE("SMC probability and simulate query expressions execute before the unsupported property() call")
{
    // PrettyPrinter never overrides property(), so any parsed property
    // ultimately throws NotSupportedException there -- but the SMC-specific
    // expression callbacks (expr_proba_quantitative, expr_simulate,
    // expr_MITL_diamond/box) run to completion first, since the grammar
    // reduces them before the enclosing PropertyExpr rule calls property().
    auto os = std::ostringstream{};
    auto pretty = PrettyPrinter{os};
    CHECK_THROWS_AS(parse_property("Pr[<=10](<> true)", pretty), NotSupportedException);
    CHECK_THROWS_AS(parse_property("simulate[<=10;100]{true}", pretty), NotSupportedException);
    // expr_MITL_diamond/box run before the outer expr_MITL_formula() call,
    // which PrettyPrinter also does not implement.
    CHECK_THROWS_AS(parse_property("Pr (<>[0,5] true)", pretty), NotSupportedException);
    CHECK_THROWS_AS(parse_property("Pr ([][0,5] true)", pretty), NotSupportedException);
}

TEST_CASE("Deadlock and process.location expressions execute before an unsupported CTL operator")
{
    // PrettyPrinter's expr_unary() only handles a handful of operators and
    // throws TypeException{"Invalid operator"} for CTL quantifiers such as
    // EF, but the inner expression is fully evaluated first.
    auto os = std::ostringstream{};
    auto pretty = PrettyPrinter{os};
    CHECK_THROWS_AS(parse_property("E<> deadlock", pretty), TypeException);
    CHECK_THROWS_AS(parse_property("E<> Process.location", pretty), TypeException);
}

TEST_SUITE_END();
