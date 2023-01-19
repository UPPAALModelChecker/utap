#ifndef INCLUDE_UTAP_DOCUMENT_FIXTURE_HPP
#define INCLUDE_UTAP_DOCUMENT_FIXTURE_HPP

#include <memory>
#include <stdexcept>
#include <string>
#include <cstring>

#include <utap/utap.h>

template <typename... Args>
std::string string_format(const std::string& format, Args... args)
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

std::string replace_all(std::string text, const std::string& what, const std::string& with)
{
    for (auto pos = text.find(what); pos != std::string::npos; pos = text.find(what, pos + 1))
        text.replace(pos, what.length(), with);
    return std::move(text);
}

std::string escape_xml(std::string text)
{
    text = replace_all(std::move(text), "&", "&amp;");
    text = replace_all(std::move(text), "<", "&lt;");
    text = replace_all(std::move(text), ">", "&gt;");
    return std::move(text);
}

class template_fixture
{
    std::string name;
    std::string parameters{};
    std::string declarations{};

public:
    template_fixture(std::string name): name{std::move(name)} {}
    void set_name(std::string new_name) { name = std::move(new_name); }
    template_fixture& add_parameter(std::string param)
    {
        if (!parameters.empty())
            parameters += ", ";
        parameters += escape_xml(std::move(param));
        return *this;
    }
    template_fixture& add_declaration(std::string text)
    {
        if (!declarations.empty())
            declarations += '\n';
        declarations += escape_xml(std::move(text));
        return *this;
    }
    std::string str() const
    {
        static constexpr const char* simple_template = R"XML("<template>
        <name x="5" y="5">%s</name>
        <parameter>%s</parameter>
        <declaration>%s</declaration>
        <location id="id0" x="0" y="0"/>
        <init ref="id0"/>
    </template>")XML";
        return string_format(simple_template, name.c_str(), parameters.c_str(), declarations.c_str());
    }

private:
};

class document_fixture
{
    std::string global_decls{};
    std::string templates{};
    std::string system_decls{};
    std::string processes{};

public:
    /** Adds text at the global declarations section of the document */
    void add_global_decl(std::string text)
    {
        if (!global_decls.empty())
            global_decls += '\n';
        global_decls += escape_xml(std::move(text));
    }
    /** Adds a template text, @see template_fixture::str() */
    document_fixture& add_template(std::string text)
    {
        templates += '\n';
        templates += std::move(text);
        return *this;
    }
    /** Adds a default template and default process just like default initial document */
    document_fixture& add_default_process()
    {
        add_template(template_fixture("Template").str());
        add_system_decl("Process = Template();");
        add_process("Process");
        return *this;
    }
    /** Adds text to system declarations */
    document_fixture& add_system_decl(std::string text)
    {
        system_decls += '\n';
        system_decls += escape_xml(std::move(text));
        return *this;
    }
    /** Adds a process to the system */
    document_fixture& add_process(std::string name)
    {
        if (!processes.empty())
            processes += ", ";
        processes += std::move(name);
        return *this;
    }
    /** Compiles an XML string representation of a document */
    std::string str() const
    {
        static constexpr const char* document_template = R"XML(<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE nta PUBLIC '-//Uppaal Team//DTD Flat System 1.5//EN' 'http://www.it.uu.se/research/group/darts/uppaal/flat-1_5.dtd'>
<nta>
    <declaration>%s</declaration>%s
    <system>%s
system %s;
    </system>
</nta>
)XML";
        return string_format(document_template, global_decls.c_str(), templates.c_str(), system_decls.c_str(),
                             processes.c_str());
    }

    /** Derives a document from a document template and parses it */
    [[nodiscard]] std::unique_ptr<UTAP::Document> parse() const
    {
        auto document = std::make_unique<UTAP::Document>();
        auto data = str();
        parseXMLBuffer(data.c_str(), document.get(), true);
        return document;
    }
};

#endif  // INCLUDE_UTAP_DOCUMENT_FIXTURE_HPP
