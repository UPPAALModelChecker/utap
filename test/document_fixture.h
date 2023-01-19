#ifndef INCLUDE_UTAP_DOCUMENT_FIXTURE_HPP
#define INCLUDE_UTAP_DOCUMENT_FIXTURE_HPP

#include <memory>
#include <stdexcept>
#include <string>
#include <cstring>

#include <utap/utap.h>

class document_fixture
{
    std::string document_template;
    std::string global_decls{};
    std::string template_decls{};
    std::string templates{};
    std::string system_decls{};
    std::string system_procs{};

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
    /** Uses custom document template to construct a fixture */
    document_fixture(std::string document_template): document_template{std::move(document_template)} {}
    /** Uses simple document template to construct a fixture */
    document_fixture(): document_fixture{simple_template} {}

    /** Adds text at the global declarations section of the document */
    void add_global_decl(std::string text)
    {
        global_decls += std::move(text);
        global_decls += '\n';
    }
    /** Adds text to the declarations section of the "Template" template */
    void add_template_decl(std::string text)
    {
        template_decls += std::move(text);
        template_decls += '\n';
    }
    /** Adds extra templates */
    void add_template(std::string text) { templates += std::move(text); }
    /** Adds text to system declarations */
    void add_system_decl(std::string text)
    {
        system_decls += std::move(text);
        system_decls += '\n';
    }
    /** Adds a process declaration to the system */
    void add_system_process(std::string name)
    {
        system_procs += ", ";
        system_procs += std::move(name);
    }

    /** Derives a document from a document template and parses it */
    [[nodiscard]] std::unique_ptr<UTAP::Document> parse() const
    {
        std::string data = string_format(document_template, global_decls.c_str(), template_decls.c_str(),
                                         templates.c_str(), system_decls.c_str(), system_procs.c_str());
        auto document = std::make_unique<UTAP::Document>();
        parseXMLBuffer(data.c_str(), document.get(), true);
        return document;
    }

private:
    static constexpr const char* simple_template = R"XML(<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE nta PUBLIC '-//Uppaal Team//DTD Flat System 1.5//EN' 'http://www.it.uu.se/research/group/darts/uppaal/flat-1_5.dtd'>
<nta>
    <declaration>%s</declaration>
    <template>
        <name x="5" y="5">Template</name>
        <declaration>%s</declaration>
        <location id="id0" x="0" y="0"/>
        <init ref="id0"/>
    </template>
%s
    <system>
%s
Process = Template();
system Process%s;
    </system>
</nta>
)XML";
};

#endif  // INCLUDE_UTAP_DOCUMENT_FIXTURE_HPP
