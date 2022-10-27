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

#include "utap/typechecker.h"
#include "utap/utap.h"

#include <memory>
#include <stdexcept>
#include <string>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

static constexpr const char* system_template = R"XML(<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE nta PUBLIC '-//Uppaal Team//DTD Flat System 1.5//EN' 'http://www.it.uu.se/research/group/darts/uppaal/flat-1_5.dtd'>
<nta>
	<declaration>%s</declaration>
	<template>
		<name x="5" y="5">Template</name>
		<declaration>%s</declaration>
		<location id="id0" x="0" y="0">
		</location>
		<init ref="id0"/>
	</template>
	<system>
%s
Process = Template();
system Process;
    </system>
	<queries>
		<query>
			<formula/>
			<comment/>
		</query>
	</queries>
</nta>
)XML";

class document_fixture
{
    std::string decls{};
    std::string template_decls{};
    std::string sys_decls{};

    template <typename... Args>
    std::string string_format(const std::string& format, Args... args) const
    {
        using namespace std::string_literals;
        auto size = std::snprintf(nullptr, 0, format.c_str(), args...);
        if (size <= 0)
            throw std::logic_error("Failed to format: "s + std::strerror(errno));
        auto res = std::string(size, ' ');
        if (auto s = std::snprintf(&res[0], size + 1, format.c_str(), args...); s != size)
            throw std::logic_error("Failed to format: "s + std::strerror(errno));
        return res;
    }

public:
    void set_decls(std::string text) { decls = std::move(text); }
    void set_template_decls(std::string text) { template_decls = std::move(text); }
    void set_system_decls(std::string text) { sys_decls = std::move(text); }

    [[nodiscard]] std::unique_ptr<UTAP::Document> parse() const
    {
        std::string data = string_format(system_template, decls.c_str(), template_decls.c_str(), sys_decls.c_str());
        auto document = std::make_unique<UTAP::Document>();
        parseXMLBuffer(data.c_str(), document.get(), true);
        return document;
    }
};

TEST_SUITE("Quantifier sum")
{
    TEST_CASE("sum expression")
    {
        document_fixture f;
        f.set_system_decls("int x = sum (index : int[0, 5]) index;");
        auto document = f.parse();

        CHECK(document->getErrors().size() == 0);
        CHECK(document->getWarnings().size() == 0);
    }

    TEST_CASE("sum over array")
    {
        document_fixture f;
        f.set_system_decls("int a[3] = {1,4,9};\nint x = sum(i : int[0, 2]) a[i];");
        auto document = f.parse();
        CHECK(document->getWarnings().size() == 0);
        const auto errors = document->getErrors();
        REQUIRE(errors.size() == 1);
        CHECK(errors[0].msg == "$Must_be_computable_at_compile_time");
    }

    TEST_CASE("sum over const array")
    {
        document_fixture f;
        f.set_system_decls("const int a[3] = {1,4,9};\nint x = sum(i : int[0, 2]) a[i];");
        auto document = f.parse();
        CHECK(document->getWarnings().size() == 0);
        CHECK(document->getErrors().size() == 0);
    }
}

TEST_SUITE("Quantifier forall")
{
    TEST_CASE("forall expression")
    {
        document_fixture f;
        f.set_system_decls("bool x = forall (index : int[0, 5]) index > 3;");
        auto document = f.parse();

        CHECK(document->getErrors().size() == 0);
        CHECK(document->getWarnings().size() == 0);
    }

    TEST_CASE("forall over array")
    {
        document_fixture f;
        f.set_system_decls("bool b[3]={1,1,1};\nbool x = forall(i : int[0,2]) b[i];");
        auto document = f.parse();
        CHECK(document->getWarnings().size() == 0);
        const auto errors = document->getErrors();
        REQUIRE(errors.size() == 1);
        CHECK(errors[0].msg == "$Must_be_computable_at_compile_time");
    }

    TEST_CASE("forall over const array")
    {
        document_fixture f;
        f.set_system_decls("const bool b[3]={1,1,1};\nbool x = forall(i : int[0,2]) b[i];");
        auto document = f.parse();
        CHECK(document->getWarnings().size() == 0);
        CHECK(document->getErrors().size() == 0);
    }
}

TEST_SUITE("Quantifier exists")
{
    TEST_CASE("exists expression")
    {
        document_fixture f;
        f.set_system_decls("bool x = exists (index : int[0, 5]) index > 3;");
        auto document = f.parse();
        CHECK(document->getErrors().size() == 0);
        CHECK(document->getWarnings().size() == 0);
    }
    TEST_CASE("exists over array")
    {
        document_fixture f;
        f.set_system_decls("bool b[3]={0,0,1};\nbool x = exists(i : int[0,2]) b[i];");
        auto document = f.parse();
        CHECK(document->getWarnings().size() == 0);
        const auto errors = document->getErrors();
        REQUIRE(errors.size() == 1);
        CHECK(errors[0].msg == "$Must_be_computable_at_compile_time");
    }
    TEST_CASE("exists over const array")
    {
        document_fixture f;
        f.set_system_decls("const bool b[3]={0,0,1};\nbool x = exists(i : int[0,2]) b[i];");
        auto document = f.parse();
        CHECK(document->getWarnings().size() == 0);
        CHECK(document->getErrors().size() == 0);
    }
}