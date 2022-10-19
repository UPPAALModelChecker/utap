#include "utap/typechecker.h"
#include "utap/utap.h"

#include <memory>
#include <stdexcept>
#include <string>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

static constexpr const char* system_template = R""""(<?xml version="1.0" encoding="utf-8"?>
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
)"""";

class document_fixture
{
    std::string decls{};
    std::string template_decls{};
    std::string sys_decls{};

    template <typename... Args>
    std::string string_format(const std::string& format, Args... args)
    {
        int size_s = std::snprintf(nullptr, 0, format.c_str(), args...) + 1;  // Extra space for '\0'
        if (size_s <= 0) {
            throw std::runtime_error("Error during formatting.");
        }
        auto size = static_cast<size_t>(size_s);
        std::unique_ptr<char[]> buf(new char[size]);
        std::snprintf(buf.get(), size, format.c_str(), args...);
        return std::string(buf.get(), buf.get() + size - 1);  // We don't want the '\0' inside
    }

public:
    void set_decls(std::string decls) { this->decls = std::move(decls); }
    void set_template_decls(std::string template_decls) { this->template_decls = std::move(template_decls); }
    void set_system_decls(std::string sys_decls) { this->sys_decls = std::move(sys_decls); }

    std::shared_ptr<UTAP::Document> parse()
    {
        std::string data = string_format(system_template, decls.c_str(), template_decls.c_str(), sys_decls.c_str());
        auto document = std::make_unique<UTAP::Document>();
        parseXMLBuffer(data.c_str(), document.get(), true);
        return document;
    }
};

TEST_CASE("SUM expression")
{
    document_fixture f;
    f.set_system_decls("int x = sum (index : int[0, 5]) index;");
    auto document = f.parse();

    CHECK(document->getErrors().size() == 0);
    CHECK(document->getWarnings().size() == 0);
}

TEST_CASE("forall expression")
{
    document_fixture f;
    f.set_system_decls("bool x = forall (index : int[0, 5]) index > 3;");
    auto document = f.parse();

    CHECK(document->getErrors().size() == 0);
    CHECK(document->getWarnings().size() == 0);
}

TEST_CASE("exists expression")
{
    document_fixture f;
    f.set_system_decls("bool x = exists (index : int[0, 5]) index > 3;");
    auto document = f.parse();

    CHECK(document->getErrors().size() == 0);
    CHECK(document->getWarnings().size() == 0);
}