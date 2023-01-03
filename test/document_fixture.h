#ifndef INCLUDE_UTAP_DOCUMENT_FIXTURE_HPP
#define INCLUDE_UTAP_DOCUMENT_FIXTURE_HPP

#include "utap/utap.h"

#include <memory>
#include <stdexcept>
#include <string>
#include <cstring>

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

private:
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
};

#endif