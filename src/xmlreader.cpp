// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2010-2020 Aalborg University.
   Copyright (C) 2002-2006 Uppsala University and Aalborg University.

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

#include "keywords.hpp"
#include "libparser.hpp"

#include "utap/utap.hpp"

#include <libxml/parser.h>
#include <libxml/xmlreader.h>
#include <libxml/xmlstring.h>
#include <libxml/xpath.h>

#include <algorithm>
#include <cassert>
#include <charconv>
#include <cstring>  // strncmp
#include <list>
#include <map>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace UTAP {
enum class Tag {
    NTA,
    PROJECT,
    IMPORTS,
    DECLARATION,
    TEMPLATE,
    INSTANTIATION,
    SYSTEM,
    NAME,
    PARAMETER,
    LOCATION,
    INIT,
    TRANSITION,
    URGENT,
    COMMITTED,
    BRANCHPOINT,
    SOURCE,
    TARGET,
    LABEL,
    NAIL,
    LSC,
    TYPE,
    MODE,
    YLOCCOORD,
    LSCLOCATION,
    PRECHART,
    INSTANCE,
    TEMPERATURE,
    MESSAGE,
    CONDITION,
    UPDATE,
    ANCHOR,
    QUERIES,
    QUERY,
    FORMULA,
    COMMENT,
    OPTION,
    RESOURCE,
    EXPECT,
    RESULT,
    DETAILS,
    SAMPLES,
    PLOT,
    TITLE,
    SERIES,
    POINT,
    NONE
};

// clang-format off
    static const auto tag_map = std::unordered_map<std::string_view, const Tag>{
            {"nta",           Tag::NTA},
            {"project",       Tag::PROJECT},
            {"imports",       Tag::IMPORTS},
            {"declaration",   Tag::DECLARATION},
            {"template",      Tag::TEMPLATE},
            {"instantiation", Tag::INSTANTIATION},
            {"system",        Tag::SYSTEM},
            {"name",          Tag::NAME},
            {"parameter",     Tag::PARAMETER},
            {"location",      Tag::LOCATION},
            {"init",          Tag::INIT},
            {"transition",    Tag::TRANSITION},
            {"urgent",        Tag::URGENT},
            {"committed",     Tag::COMMITTED},
            {"branchpoint",   Tag::BRANCHPOINT},
            {"source",        Tag::SOURCE},
            {"target",        Tag::TARGET},
            {"label",         Tag::LABEL},
            {"nail",          Tag::NAIL},
            {"lsc",           Tag::LSC},
            {"type",          Tag::TYPE},
            {"mode",          Tag::MODE},
            {"yloccoord",     Tag::YLOCCOORD},
            {"lsclocation",   Tag::LSCLOCATION},
            {"prechart",      Tag::PRECHART},
            {"instance",      Tag::INSTANCE},
            {"temperature",   Tag::TEMPERATURE},
            {"message",       Tag::MESSAGE},
            {"condition",     Tag::CONDITION},
            {"update",        Tag::UPDATE},
            {"anchor",        Tag::ANCHOR},
            {"queries",       Tag::QUERIES},
            {"query",         Tag::QUERY},
            {"formula",       Tag::FORMULA},
            {"comment",       Tag::COMMENT},
            {"option",        Tag::OPTION},
            {"resource",      Tag::RESOURCE},
            {"expect",        Tag::EXPECT},
            {"result",        Tag::RESULT},
            {"details",       Tag::DETAILS},
            {"samples",       Tag::SAMPLES},
            {"plot",          Tag::PLOT},
            {"series",        Tag::SERIES}
    };
// clang-format on

/**
 * Returns true if string is zero length or contains only white spaces
 * otherwise false.
 */
static bool is_blank(std::string_view str) { return std::all_of(str.cbegin(), str.cend(), ::isspace); }

static bool is_blank(const xmlChar* str) { return is_blank((const char*)str); }

static bool is_alpha(char c) { return std::isalpha(c) != 0 || c == '_'; }

static bool is_id_char(char c) { return std::isalnum(c) != 0 || c == '_' || c == '$' || c == '#'; }

struct IdExpectedError : std::logic_error
{
    IdExpectedError(): std::logic_error{"Identifier expected"} {}
};

struct InvalidIdError : std::logic_error
{
    InvalidIdError(): std::logic_error{"Invalid identifier"} {}
};

struct XPathCorruptError : std::logic_error
{
    XPathCorruptError(): std::logic_error{"XPath is corrupted"} {}
};

std::string_view trim(std::string_view text)
{
    static constexpr auto ws = "\t\n\v\f\r ";
    auto res = text.substr(0, 0);
    if (auto b = text.find_first_not_of(ws); b != std::string_view::npos) {
        auto e = text.find_last_not_of(ws);
        res = text.substr(b, e - b + 1);
    }
    return res;
}

/**
 * Extracts the alpha-numerical symbol used for variable/type
 * identifiers.  Identifier starts with alpha and further might
 * contain digits, white spaces are ignored.
 * @param text a potential identifier as a character string.
 * @return valid identifier trimmed
 * @throws std::logic_error if identifier is invalid.
 */
static std::string_view symbol(std::string_view text)
{
    text = trim(text);
    if (text.empty())
        throw IdExpectedError{};
    if (!is_alpha(text[0]))
        throw IdExpectedError{};
    for (const auto& c : text)
        if (!is_id_char(c))
            throw InvalidIdError{};
    return text;
}

/**
 * Path to current node. This path also contains information about
 * the left siblings of the nodes. This information is used to
 * generated an XPath expression.
 *
 * @see get()
 */
class Path
{
    std::list<std::vector<Tag>> path;

public:
    Path() { path.emplace_back(); };
    void push(Tag tag)
    {
        path.back().push_back(tag);
        path.emplace_back();
    }
    Tag pop()
    {
        path.pop_back();
        return path.back().back();
    }
    [[nodiscard]] std::string str(Tag tag = Tag::NONE) const;
};

static size_t count(const std::vector<Tag>& level, Tag tag)
{
    return static_cast<size_t>(std::count(std::begin(level), std::end(level), tag));
}

/** Returns the XPath encoding of the current path. */
[[nodiscard]] std::string Path::str(Tag tag) const
{
    std::ostringstream str;
    for (auto&& level : path) {
        if (level.empty())
            break;
        switch (level.back()) {
        case Tag::NTA: str << "/nta"; break;
        case Tag::PROJECT: str << "/project"; break;
        case Tag::IMPORTS: str << "/imports"; break;
        case Tag::DECLARATION: str << "/declaration"; break;
        case Tag::TEMPLATE: str << "/template[" << count(level, Tag::TEMPLATE) << "]"; break;
        case Tag::INSTANTIATION: str << "/instantiation"; break;
        case Tag::SYSTEM: str << "/system"; break;
        case Tag::NAME: str << "/name"; break;
        case Tag::PARAMETER: str << "/parameter"; break;
        case Tag::LOCATION: str << "/location[" << count(level, Tag::LOCATION) << "]"; break;
        case Tag::BRANCHPOINT: str << "/branchpoint[" << count(level, Tag::BRANCHPOINT) << "]"; break;
        case Tag::INIT: str << "/init"; break;
        case Tag::TRANSITION: str << "/transition[" << count(level, Tag::TRANSITION) << "]"; break;
        case Tag::LABEL: str << "/label[" << count(level, Tag::LABEL) << "]"; break;
        case Tag::URGENT: str << "/urgent"; break;
        case Tag::COMMITTED: str << "/committed"; break;
        case Tag::SOURCE: str << "/source"; break;
        case Tag::TARGET: str << "/target"; break;
        case Tag::NAIL: str << "/nail[" << count(level, Tag::NAIL) << "]"; break;
        case Tag::LSC: str << "/lscTemplate[" << count(level, Tag::LSC) << "]"; break;
        case Tag::TYPE: str << "/type"; break;
        case Tag::MODE: str << "/mode"; break;
        case Tag::YLOCCOORD: str << "/ylocoord[" << count(level, Tag::YLOCCOORD) << "]"; break;
        case Tag::LSCLOCATION: str << "/lsclocation"; break;
        case Tag::PRECHART: str << "/prechart"; break;
        case Tag::INSTANCE: str << "/instance[" << count(level, Tag::INSTANCE) << "]"; break;
        case Tag::TEMPERATURE: str << "/temperature[" << count(level, Tag::TEMPERATURE) << "]"; break;
        case Tag::MESSAGE: str << "/message[" << count(level, Tag::MESSAGE) << "]"; break;
        case Tag::CONDITION: str << "/condition[" << count(level, Tag::CONDITION) << "]"; break;
        case Tag::UPDATE: str << "/update[" << count(level, Tag::UPDATE) << "]"; break;
        case Tag::ANCHOR: str << "/anchor[" << count(level, Tag::ANCHOR) << "]"; break;
        case Tag::QUERIES: str << "/queries"; break;
        case Tag::QUERY: str << "/query[" << count(level, Tag::QUERY) << "]"; break;
        case Tag::FORMULA: str << "/formula"; break;
        case Tag::COMMENT: str << "/comment"; break;
        case Tag::OPTION: str << "/option"; break;
        case Tag::RESOURCE: str << "/resource"; break;
        case Tag::EXPECT: str << "/expect"; break;
        case Tag::RESULT: str << "/result"; break;
        case Tag::DETAILS: str << "/details"; break;
        case Tag::SAMPLES: str << "/samples"; break;
        default:
            /* Strange tag on stack */
            throw XPathCorruptError{};
        }
        if (level.back() == tag) {
            break;
        }
    }
    return str.str();
}

/**
 * Implements a recursive descent parser for UPPAAL XML documents.
 * Uses the xmlTextReader API from libxml2.
 */
class XMLReader
{
    using ElementMap = std::map<std::string, std::string>;
    using xmlTextReader_ptr = std::unique_ptr<xmlTextReader, decltype(&xmlFreeTextReader)>;
    xmlTextReader_ptr reader; /**< The underlying xmlTextReader */
    ElementMap names;       /**< Map from id to name */
    ParserBuilder& parser;    /**< The parser builder to which to push the model. */
    bool newxta;              /**< True if we should use new syntax. */
    Path path;
    bool nta;                /**< True if the enclosing tag is "nta" (false if it is "project") */
    int bottomPrechart;      /**< y location of the prechart bottom */
    std::string currentType; /**< type of the current LSC template */
    std::string currentMode; /**< mode of the current LSC template */

    [[nodiscard]] Tag getElement() const;
    /** Reads an attribute value of the currently parsed tag with manual deallocation.
     * @param name the name of the XML tag attribute
     * @return the value of the attribute, remember to xmlFree() it!
     */
    char* getAttribute(const char* name) const;
    /** Reads an attribute value of the currently parsed tag with automatic deallocation.
     * @param name the name of the XML tag attribute
     * @return the value of the attribute.
     */
    std::string getAttributeStr(std::string_view name) const;

    bool isEmpty() const;
    int getNodeType() const;
    void read();
    bool begin(Tag, bool skipEmpty = true);
    bool end(Tag);
    /** skips the content until tag is closed and then looks ahead */
    void close(Tag tag)
    {
        if (!isEmpty()) {
            while (!end(tag))
                read();
        }
        read();
    }
    /** calls fn zero or one times unless closing tag is found */
    template <typename Fn>
    void zero_or_one(Tag closing_tag, Fn&& fn)
    {
        if (!end(closing_tag))
            fn();
    }
    /** calls fn zero or more times unless closing tag is found */
    template <typename Fn>
    void zero_or_more(Tag closing_tag, Fn&& fn)
    {
        while (!end(closing_tag) && fn())
            ;
    }
    /** Returns the name of a location. */
    const std::string& get_name(const char* id) const;
    /** Invokes the bison generated parser to parse the given string. */
    int parse(const xmlChar*, XTAPart syntax);
    /** Parse optional declaration. */
    bool declaration();
    /** Parse optional label. */
    bool label(bool required = false, const std::string& kind = "");
    int invariant();
    /** Parse optional committed tag. */
    bool committed();
    /** Parse optional urgent tag. */
    bool urgent();
    /** Parse optional location. */
    bool location();
    /** Parse optional branchpoint. */
    bool branchpoint();
    /** Parse optional init tag. The caller must define a position to
     * which any error messages are attached.
     */
    bool init();
    /** Parse optional name tag. */
    std::string name(bool instanceLine = false);
    std::string readString(Tag tag, bool instanceLine = false);
    std::string readText(bool instanceLine = false);
    int readNumber();
    /** Parse obligatory source tag. */
    std::string source();
    /** Parse obligatory target tag. */
    std::string target();
    /** Parse optional transition. */
    bool transition();
    /** Parse optional template. */
    bool templ();
    /** Parses an optional parameter tag and returns the number of parameters. */
    int parameter();
    /** Parse optional instantiation tag. */
    bool instantiation();
    /** Parse required system tag. */
    void system();
    std::string reference(const std::string& attributeName);

    // LSC elements:
    /** Parse optional LSC template. */
    bool lscTempl();
    /** Parse obligatory anchor tag for update. */
    std::string anchor();
    /** Parse obligatory anchor tag for condition. */
    std::vector<std::string> anchors();
    /** Parse optional type tag. */
    std::string type();
    /** Parse optional mode tag. */
    std::string mode();
    /** Parse required lsclocation tag for the prechart (bottom location or the messages) */
    int lscLocation();
    std::string temperature();
    bool yloccoord();
    bool instance();
    bool prechart();
    bool message();
    bool condition();
    bool update();

    // integrated query elements:
    /** Parse optional enclosed queries inside the model file. */
    bool queries();
    bool model_options();
    bool query();
    bool formula();
    bool comment();
    bool option();
    bool expectation();
    bool result();

public:
    XMLReader(xmlTextReaderPtr reader, ParserBuilder& parser, bool newxta):
        reader(reader, xmlFreeTextReader), parser{parser}, newxta{newxta}
    {
        read();
    }
    /** Parse the project document (either NTA or PROJECT tag). */
    void project();
};

static const auto non_unique_id = std::string{"$Non-unique_id_attribute_value: "};

/** Returns the type of the current node. */
int XMLReader::getNodeType() const { return xmlTextReaderNodeType(reader.get()); }

/**
 * Returns the tag of the current element. Throws an exception if
 * the tag is not known.
 */
Tag XMLReader::getElement() const
{
    const char* element = (const char*)xmlTextReaderConstLocalName(reader.get());
    const auto tag = tag_map.find(element);
    if (tag == std::end(tag_map)) {
        /* Unknown element. */
        return Tag::NONE;
    }
    return tag->second;
}

char* XMLReader::getAttribute(const char* name) const
{
    return (char*)xmlTextReaderGetAttribute(reader.get(), (xmlChar*)name);
}

std::string XMLReader::getAttributeStr(std::string_view name) const
{
    char* value = getAttribute(name.data());
    auto res = std::string{value};
    xmlFree(value);
    return res;
}

/** Returns true if the current element is an empty element. */
bool XMLReader::isEmpty() const
{
    int res = xmlTextReaderIsEmptyElement(reader.get());
    assert(0 <= res);
    assert(res <= 1);
    return res == 1;
}

/**
 * Read until start element. Returns true if that element has the
 * given tag. If skipEmpty is true, empty elements with the given
 * tag are ignored.
 */
bool XMLReader::begin(Tag tag, bool skipEmpty)
{
    for (;;) {
        int node_type = getNodeType();
        while (node_type != XML_READER_TYPE_ELEMENT) {
            read();
            node_type = getNodeType();
        }
        Tag elem = getElement();
        if (elem != tag) {
            // if the tag was not recognized, try skipping over it until
            // an end element is found with unknown tag.
            if (elem == Tag::NONE) {
                end(Tag::NONE);
                read();
                continue;
            }
            return false;
        }
        if (!skipEmpty || !isEmpty())
            return true;
        read();
    }
}
/**
 * Is end of the tag in xml ?
 * @param tag - XML tag
 * @return True - if </...> tag found
 * Ignores whitespace
 */
bool XMLReader::end(Tag tag)
{
    int node_type = getNodeType();
    // Ignore whitespace
    while (node_type == XML_READER_TYPE_WHITESPACE || node_type == XML_READER_TYPE_SIGNIFICANT_WHITESPACE) {
        read();
        node_type = getNodeType();
    }
    // </...> tag found
    return node_type == XML_READER_TYPE_END_ELEMENT && getElement() == tag;
}

/**
 * Advances the reader. It maintains the path to the current node.
 */
void XMLReader::read()
{
    if ((getNodeType() == XML_READER_TYPE_END_ELEMENT) || (getNodeType() == XML_READER_TYPE_ELEMENT && isEmpty())) {
        if (path.pop() != getElement()) {
            /* Path is corrupted */
            throw XMLDocError("Invalid nesting");
        }
    }
    if (xmlTextReaderRead(reader.get()) != 1) {
        /* Premature end of document. */
        throw XMLReaderError(errno, std::system_category(), "$unexpected $end");
    }

    if (getNodeType() == XML_READER_TYPE_ELEMENT) {
        path.push(getElement());
    }
}

const std::string& XMLReader::get_name(const char* id) const
{
    if (id != nullptr) {
        if (auto l = names.find(id); l != names.end())
            return l->second;
    }
    throw XMLDocError("Missing reference");
}

int XMLReader::parse(const xmlChar* text, XTAPart syntax)
{
    return parse_XTA((const char*)text, parser, newxta, syntax, path.str());
}

bool XMLReader::declaration()
{
    if (begin(Tag::DECLARATION)) {
        read();
        if (getNodeType() == XML_READER_TYPE_TEXT) {
            parse(xmlTextReaderConstValue(reader.get()), XTAPart::DECLARATION);
        }
        return true;
    }
    return false;
}

bool XMLReader::label(bool required, const std::string& s_kind)
{
    static const auto xta_map = std::map<std::string_view, XTAPart>{
        {"invariant", XTAPart::INVARIANT},
        {"select", XTAPart::SELECT},
        {"guard", XTAPart::GUARD},
        {"synchronisation", XTAPart::SYNC},
        {"assignment", XTAPart::ASSIGN},
        {"probability", XTAPart::PROBABILITY},
        {"message", XTAPart::MESSAGE},
        {"update", XTAPart::UPDATE},
        {"condition", XTAPart::CONDITION},
    };
    if (begin(Tag::LABEL)) {
        /* Get kind attribute. */
        char* kind = getAttribute("kind");
        if (kind == nullptr)
            throw TypeException("A label must have a \"kind\" attribute");
        read();
        /* Read the text and push it to the parser. */
        if (getNodeType() == XML_READER_TYPE_TEXT) {
            const xmlChar* text = xmlTextReaderConstValue(reader.get());
            if (auto part = xta_map.find(kind); part != xta_map.end())
                parse(text, part->second);
        }
        xmlFree(kind);
        return true;
    }
    if (required) {
        tracker.setPath(&parser, path.str());
        if (s_kind == "message")  // LSC
            parser.handle_error(TypeException{"$Message_label_is_required"});
        else if (s_kind == "update")  // LSC
            parser.handle_error(TypeException{"$Update_label_is_required"});
        else if (s_kind == "condition")  // LSC
            parser.handle_error(TypeException{"$Condition_label_is_required"});
    }
    return false;
}

int XMLReader::invariant()
{
    int result = -1;
    if (begin(Tag::LABEL)) {
        /* Get kind attribute. */
        char* kind = getAttribute("kind");
        if (kind == nullptr)
            throw TypeException{"A label must have a \"kind\" attribute"};
        read();
        /* Read the text and push it to the parser. */
        if (getNodeType() == XML_READER_TYPE_TEXT) {
            const xmlChar* text = xmlTextReaderConstValue(reader.get());
            auto kind_sv = std::string_view{kind};
            // This is a terrible mess but it's too badly designed
            // to fix at this moment.
            if (kind_sv == "invariant") {
                if (parse(text, XTAPart::INVARIANT) == 0)
                    result = 0;
            } else if (kind_sv == "exponentialrate") {
                if (parse(text, XTAPart::EXPONENTIAL_RATE) == 0)
                    result = 1;
            }
        }
        xmlFree(kind);
    }
    return result;
}

std::string XMLReader::name(bool instanceLine)
{
    std::string text = readString(Tag::NAME, instanceLine);
    if (instanceLine && text.empty())
        parser.handle_error(TypeException{"$Instance_name_is_required"});
    return text;
}

std::string XMLReader::readText(bool instanceLine)
{
    if (getNodeType() == XML_READER_TYPE_TEXT) {  // text content of a node
        xmlChar* text = xmlTextReaderValue(reader.get());
        auto text_sv = std::string_view{text != nullptr ? (const char*)text : ""};
        tracker.setPath(&parser, path.str());
        tracker.increment(&parser, static_cast<uint32_t>(text_sv.size()));
        try {
            auto id = (instanceLine) ? text_sv : symbol(text_sv);
            if (!is_keyword(id, Syntax::OLD_PROPERTY)) {
                auto res = std::string{id};
                xmlFree(text);
                return res;
            }
            parser.handle_error(TypeException{"$Keywords_are_not_allowed_here"});
        } catch (std::logic_error& str) {
            parser.handle_error(TypeException{str.what()});
        }
        xmlFree(text);
    }
    return "";
}

int XMLReader::readNumber()
{
    read();
    if (getNodeType() == XML_READER_TYPE_TEXT) {  // text content of a node
        tracker.setPath(&parser, path.str());
        xmlChar* text = xmlTextReaderValue(reader.get());
        const char* pc = (const char*)text;
        const auto len = static_cast<uint32_t>(std::strlen(pc));
        tracker.increment(&parser, len);
        try {
            int value;
            if (auto [p, ec] = std::from_chars(pc, pc + len, value); ec != std::errc{})
                throw std::logic_error{std::make_error_code(ec).category().name()};
            xmlFree(text);
            return value;
        } catch (const char* str) {
            parser.handle_error(TypeException{str});
        }
        xmlFree(text);
    }
    return -1;
}

std::string XMLReader::readString(Tag tag, bool instanceLine)
{
    if (begin(tag)) {
        read();
        return readText(instanceLine);
    }
    return "";
}

std::string XMLReader::type() { return readString(Tag::TYPE); }

std::string XMLReader::mode() { return readString(Tag::MODE); }

int XMLReader::lscLocation()
{
    int n = -1;
    if (begin(Tag::LSCLOCATION)) {
        n = readNumber();
    }
    if (n == -1)
        throw XMLDocError("Missing LSC location");
    return n;
}

bool XMLReader::committed()
{
    if (begin(Tag::COMMITTED, false)) {
        read();
        return true;
    }
    return false;
}

bool XMLReader::urgent()
{
    if (begin(Tag::URGENT, false)) {
        read();
        return true;
    }
    return false;
}

bool XMLReader::location()
{
    bool l_invariant = false;
    bool l_exponentialRate = false;

    if (begin(Tag::LOCATION, false)) {
        try {
            std::string l_path = path.str(Tag::LOCATION);
            /* Extract ID attribute. */
            auto l_id = getAttributeStr("id");
            if (is_blank(l_id))
                throw TypeException{"Every location must have a unique id attribute value"};
            read();
            /* Get name of the location. */
            std::string l_name = name();
            /* Read the invariant. */
            while (begin(Tag::LABEL)) {
                int res = invariant();
                l_invariant |= res == 0;
                l_exponentialRate |= res == 1;
            }
            /* Is the location urgent or committed? */
            bool l_urgent = urgent();
            bool l_committed = committed();

            // anonymous locations get an internal name based on the ID
            if (is_blank(l_name))
                l_name = "_" + l_id;
            /* Remember the mapping from id to name */
            if (auto [_, ins] = names.insert_or_assign(l_id, l_name); !ins)
                parser.handle_warning(TypeException{non_unique_id + l_id});

            /* Any error messages generated by any of the
             * procStateXXX calls must be attributed to the state
             * element. To do this, we add a dummy position of
             * length 1.
             */
            tracker.setPath(&parser, l_path);
            tracker.increment(&parser, 1);

            /* Push location to parser builder. */
            parser.proc_location(l_name, l_invariant, l_exponentialRate);
            if (l_committed)
                parser.proc_location_commit(l_name);
            if (l_urgent)
                parser.proc_location_urgent(l_name);
        } catch (TypeException& e) {
            parser.handle_error(e);
        }
        return true;
    }
    return false;
}

/** Parse optional instance. */
bool XMLReader::instance()
{
    if (begin(Tag::INSTANCE, false)) {
        try {
            auto i_path = path.str(Tag::INSTANCE);
            /* Extract ID attribute. */
            auto i_id = getAttributeStr("id");
            read();
            if (is_blank(i_id))
                throw TypeException{"Instance tag must have a unique \"id\" attribute"};

            /* Get name of the instance. */
            tracker.setPath(&parser, i_path);
            tracker.increment(&parser, 1);
            auto i_name = name(true);

            /* Remember the mapping from id to name */
            if (auto [_, ins] = names.insert_or_assign(i_id, i_name); !ins)
                parser.handle_warning(TypeException{non_unique_id + i_id});

            /* Any error messages generated by the
             * proc_instance_line call must be attributed to the
             * instance line element. To do this, we add a dummy
             * position of length 1.
             */
            tracker.setPath(&parser, i_path);
            tracker.increment(&parser, 1);
            /* Push instance to parser builder. */
            parser.proc_instance_line();
            parse((xmlChar*)i_name.c_str(), XTAPart::INSTANCE_LINE);
        } catch (TypeException& e) {
            parser.handle_error(e);
        }
        return true;
    }
    return false;
}

/** Parse optional yloccoord */
bool XMLReader::yloccoord()
{
    if (begin(Tag::YLOCCOORD, false)) {
        read();  // used only for the GUI
        return true;
    }
    return false;
}

std::string XMLReader::temperature()
{
    if (begin(Tag::TEMPERATURE, false)) {
        read();
        /* Get the temperature of the condition */
        return readText();
    }
    throw TypeException{"Missing temperature"};
}

bool XMLReader::prechart()
{
    if (begin(Tag::PRECHART, false)) {
        try {
            std::string p_path = path.str(Tag::PRECHART);
            /* Get the bottom location number */
            read();
            bottomPrechart = lscLocation();
            if (strcasecmp(currentType.c_str(), "existential") == 0) {
                tracker.setPath(&parser, p_path);
                tracker.increment(&parser, 1);
                parser.handle_error(TypeException{"$Existential_charts_must_not_have_prechart"});
            }
            parser.prechart_set(true);
        } catch (TypeException& e) {
            parser.handle_error(e);
        }
        return true;
    }
    bottomPrechart = -1;
    parser.prechart_set(false);
    return false;
}

bool XMLReader::message()
{
    if (begin(Tag::MESSAGE)) {
        /* Add dummy position mapping to the message element. */
        try {
            std::string m_path = path.str(Tag::MESSAGE);
            read();
            std::string from = source();
            std::string to = target();
            int location = lscLocation();
            bool pch = (location < bottomPrechart);
            tracker.setPath(&parser, m_path);
            tracker.increment(&parser, 1);
            parser.proc_message(from.c_str(), to.c_str(), location, pch);
            tracker.setPath(&parser, m_path);
            tracker.increment(&parser, 1);
            label(true, "message");
        } catch (TypeException& e) {
            parser.handle_error(e);
        }
        return true;
    }
    return false;
}

bool XMLReader::condition()
{
    if (begin(Tag::CONDITION)) {
        try {
            std::string c_path = path.str(Tag::CONDITION);
            read();

            std::vector<std::string> instance_anchors = anchors();
            int location = lscLocation();
            bool pch = (location < bottomPrechart);

            tracker.setPath(&parser, c_path);
            tracker.increment(&parser, 1);
            std::string temp = temperature();
            bool hot = (temp == "hot");
            parser.proc_condition(instance_anchors, location, pch, hot);

            label(true, "condition");
        } catch (TypeException& e) {
            parser.handle_error(e);
        }
        return true;
    }
    return false;
}

bool XMLReader::update()
{
    if (begin(Tag::UPDATE)) {
        try {
            std::string u_path = path.str(Tag::UPDATE);
            // location = atoi((char*)xmlTextReaderGetAttribute(reader, (const xmlChar*)"y"));
            // pch = (location < bottomPrechart);
            read();
            std::string instance_anchor = anchor();
            int location = lscLocation();
            bool pch = (location < bottomPrechart);

            tracker.setPath(&parser, u_path);
            tracker.increment(&parser, 1);
            parser.proc_LSC_update(instance_anchor.c_str(), location, pch);
            label(true, "update");
        } catch (TypeException& e) {
            parser.handle_error(e);
        }
        return true;
    }
    return false;
}

bool XMLReader::branchpoint()
{
    if (begin(Tag::BRANCHPOINT, false)) {
        try {
            std::string b_path = path.str(Tag::BRANCHPOINT);
            auto b_id = getAttributeStr("id");
            if (is_blank(b_id)) {
                throw TypeException{"Branchpoint must have a unique \"id\" attribute"};
            }
            /* assign an internal name based on the ID of the branchpoint. */
            std::string b_name = "_" + b_id;
            /* Remember the mapping from id to name */
            if (auto [_, ins] = names.insert_or_assign(b_id, b_name); !ins)
                parser.handle_warning(TypeException{non_unique_id + b_id});
            // FIXME: probably not necessary
            /* Any error messages generated by any of the
             * procStateXXX calls must be attributed to the state
             * element. To do this, we add a dummy position of
             * length 1.
             */
            tracker.setPath(&parser, b_path);
            tracker.increment(&parser, 1);
            /* Push branchpoint to parser builder. */
            parser.proc_branchpoint(b_name.c_str());
        } catch (TypeException& e) {
            parser.handle_error(e);
        }
        read();  // ignore any content and read next tag
        return true;
    }
    return false;
}

bool XMLReader::init()
{
    if (begin(Tag::INIT, false)) {
        /* Get reference attribute. */
        char* ref = getAttribute("ref");
        /* Find location name for the reference. */
        if (ref != nullptr) {
            const auto name = get_name(ref);
            try {
                parser.proc_location_init(name.c_str());
            } catch (TypeException& te) {
                parser.handle_error(te);
            }
        } else {
            parser.handle_error(TypeException{"$Missing_initial_location"});
        }
        xmlFree(ref);
        read();
        return true;
    }
    parser.handle_error(TypeException{"$Missing_initial_location"});
    return false;
}

std::string XMLReader::reference(const std::string& attributeName)
{
    char* id = getAttribute(attributeName.c_str());
    std::string name = get_name(id);
    xmlFree(id);
    read();
    return name;
}

std::string XMLReader::source()
{
    if (begin(Tag::SOURCE, false))
        return reference("ref");
    throw TypeException{"Missing source element"};
}

std::string XMLReader::target()
{
    if (begin(Tag::TARGET, false))
        return reference("ref");
    throw TypeException{"Missing target element"};
}

std::string XMLReader::anchor()
{
    if (begin(Tag::ANCHOR, false))
        return reference("instanceid");
    throw TypeException{"Missing anchor element"};
}

std::vector<std::string> XMLReader::anchors()
{
    auto res = std::vector<std::string>{};
    while (begin(Tag::ANCHOR, false))
        res.push_back(reference("instanceid"));
    if (res.empty())
        throw TypeException{"Missing anchor element"};
    return res;
}

bool XMLReader::transition()
{
    if (begin(Tag::TRANSITION)) {
        /* Add dummy position mapping to the transition element. */
        try {
            char* type = getAttribute("controllable");
            bool control = (type == nullptr || (strcmp(type, "true") == 0));
            xmlFree(type);

            char* id = getAttribute("action");
            auto actname = std::string{id != nullptr ? id : "SKIP"};
            xmlFree(id);

            read();
            auto from = source();
            auto to = target();

            parser.proc_edge_begin(from.c_str(), to.c_str(), control, actname.c_str());
            while (label())
                ;
            while (begin(Tag::NAIL))
                read();
            parser.proc_edge_end(from.c_str(), to.c_str());
        } catch (TypeException& e) {
            parser.handle_error(e);
        }
        return true;
    }
    return false;
}

int XMLReader::parameter()
{
    int count = 0;
    if (begin(Tag::PARAMETER)) {
        read();
        if (getNodeType() == XML_READER_TYPE_TEXT) {
            count = parse(xmlTextReaderConstValue(reader.get()), XTAPart::PARAMETERS);
        }
    }
    return count;
}

bool XMLReader::templ()
{
    if (begin(Tag::TEMPLATE)) {
        auto t_path = std::make_shared<std::string>(path.str(Tag::TEMPLATE));
        read();
        try {
            /* Get the name and the parameters of the template. */
            std::string t_name = name();
            parameter();

            /* Push template start to parser builder. This might
             * throw a TypeException. */
            tracker.setPath(&parser, t_path);
            tracker.increment(&parser, 1);
            parser.proc_begin(t_name.c_str());

            /* Parse declarations, locations, branchpoints,
             * the init tag and the transitions of the template. */
            declaration();
            while (location())
                ;
            while (branchpoint())
                ;
            tracker.setPath(&parser, t_path);
            tracker.increment(&parser, 1);
            init();
            while (transition())
                ;

            /* Push template end to parser builder. */
            tracker.setPath(&parser, t_path);
            tracker.increment(&parser, 1);
            parser.proc_end();
        } catch (TypeException& e) {
            parser.handle_error(e);
        }

        return true;
    }
    return false;
}

bool XMLReader::lscTempl()
{
    if (begin(Tag::LSC)) {
        std::string t_path = path.str(Tag::LSC);
        read();
        try {
            /* Get the name and the parameters of the template. */
            std::string t_name = name();
            parser.lscTemplateNames.push_back(t_name);
            parameter();
            currentType = type();
            currentMode = mode();
            /* Push template start to parser builder. This might
             * throw a TypeException. */
            tracker.setPath(&parser, t_path);
            tracker.increment(&parser, 1);
            parser.proc_begin(t_name.c_str(), false, currentType, currentMode);

            /* Parse declarations, locations, instances, prechart
             * messages, conditions and updates */
            declaration();
            while (yloccoord())
                ;
            while (instance())
                ;
            prechart();
            while (message())
                ;
            while (condition())
                ;
            while (update())
                ;

            /* Push template end to parser builder. */
            tracker.setPath(&parser, t_path);
            tracker.increment(&parser, 1);
            parser.proc_end();
        } catch (TypeException& e) {
            parser.handle_error(e);
        }
        return true;
    }
    return false;
}

bool XMLReader::instantiation()
{
    if (begin(Tag::INSTANTIATION, false)) {
        const auto* text = (const xmlChar*)"";
        read();
        if (getNodeType() == XML_READER_TYPE_TEXT)
            text = xmlTextReaderConstValue(reader.get());
        parse(text, XTAPart::INST);
        return true;
    }
    return false;
}

void XMLReader::system()
{
    if (begin(Tag::SYSTEM, false)) {
        const auto* text = (const xmlChar*)"";
        read();
        auto nodeType = getNodeType();
        if (nodeType == XML_READER_TYPE_TEXT)
            text = xmlTextReaderConstValue(reader.get());
        // if there are no non-space characters in the text (or the text is empty),
        // bison doesn't manage to properly set the position of errors,
        // leading to nonsense error placements.
        if (nodeType == XML_READER_TYPE_END_ELEMENT || is_blank(text)) {
            tracker.setPath(&parser, path.str(Tag::SYSTEM));
            tracker.increment(&parser, 1);
            parser.handle_error(TypeException{"$syntax_error: $unexpected $end"});
            close(Tag::SYSTEM);
            return;
        }
        parse(text, XTAPart::SYSTEM);
        close(Tag::SYSTEM);
    } else {
        std::string s = (nta) ? path.str(Tag::NTA) : path.str(Tag::PROJECT);
        tracker.setPath(&parser, s);
        tracker.increment(&parser, 1);
        parser.handle_error(TypeException{"$Missing_system_tag"});
    }
}

bool XMLReader::queries()
{
    if (begin(Tag::QUERIES, false)) {
        read();
        zero_or_one(Tag::QUERIES, [this] { return model_options(); });
        zero_or_more(Tag::QUERIES, [this] { return query(); });
        close(Tag::QUERIES);
        return true;
    }
    return false;
}
bool XMLReader::query()
{
    if (begin(Tag::QUERY, false)) {
        if (!isEmpty()) {
            read();
            parser.query_begin();
            zero_or_one(Tag::QUERY, [this] { return formula(); });
            zero_or_one(Tag::QUERY, [this] { return comment(); });
            zero_or_more(Tag::QUERY, [this] { return option(); });
            zero_or_one(Tag::QUERY, [this] { return expectation(); });
            zero_or_more(Tag::QUERY, [this] { return result(); });
            parser.query_end();
            close(Tag::QUERY);
        } else
            read();  // look ahead next tag
        return true;
    }
    return false;
}
bool XMLReader::formula()
{
    if (begin(Tag::FORMULA, false)) {
        if (!isEmpty()) {
            read();
            const auto* text = xmlTextReaderConstValue(reader.get());
            if (text != nullptr)
                parser.query_formula((const char*)text, path.str(Tag::FORMULA));
            close(Tag::FORMULA);
        } else
            read();
        return true;
    }
    return false;
}
bool XMLReader::comment()
{
    if (begin(Tag::COMMENT, false)) {
        if (!isEmpty()) {
            read();
            const auto* text = xmlTextReaderConstValue(reader.get());
            if (text != nullptr)
                parser.query_comment((const char*)text);
            close(Tag::COMMENT);
        } else
            read();
        return true;
    }
    return false;
}

bool XMLReader::option()
{
    if (begin(Tag::OPTION, false)) {
        char* key = getAttribute("key");
        char* value = getAttribute("value");
        parser.query_options(key, value);
        xmlFree(key);
        xmlFree(value);
        close(Tag::OPTION);
        return true;
    }
    return false;
}

bool XMLReader::expectation()
{
    if (begin(Tag::EXPECT, false)) {
        if (!isEmpty()) {
            parser.expectation_begin();
            char* outcome = getAttribute("outcome");
            char* type = getAttribute("type");
            char* value = getAttribute("value");
            parser.expectation_value(outcome, type, value);
            zero_or_more(Tag::EXPECT, [this] {
                if (begin(Tag::RESOURCE, false)) {
                    auto type = getAttributeStr("type");
                    auto value = getAttributeStr("value");
                    auto unit = getAttributeStr("unit");
                    parser.expect_resource(type.c_str(), value.c_str(), unit.c_str());
                    close(Tag::RESOURCE);
                    return true;
                }
                return false;
            });
            parser.expectation_end();
            close(Tag::EXPECT);
        } else
            read();
        return true;
    }
    return false;
}
bool XMLReader::result()
{
    if (begin(Tag::RESULT, false)) {
        close(Tag::RESULT);
        return true;
    }
    return false;
}

void XMLReader::project()
{
    if (!begin(Tag::NTA) && !begin(Tag::PROJECT))
        throw TypeException{"$Missing_nta_or_project_tag"};
    nta = begin(Tag::NTA);  // "nta" or "project"?
    if (newxta)
        parse((const xmlChar*)utap_builtin_declarations(), XTAPart::DECLARATION);
    read();
    declaration();
    while (templ())
        ;
    while (lscTempl())
        ;
    instantiation();
    system();
    if ((nta && !end(Tag::NTA)) || (!nta && !end(Tag::PROJECT)))
        queries();
    parser.done();
}

bool XMLReader::model_options()
{
    while (begin(Tag::OPTION)) {
        read();
        char* key = getAttribute("key");
        char* value = getAttribute("value");
        parser.model_option(key, value);
        close(Tag::OPTION);
    }
    return true;
}

int32_t parse_XML_fd(int fd, ParserBuilder& pb, bool newxta)
{
    xmlTextReaderPtr reader =
        xmlReaderForFd(fd, "", "", XML_PARSE_NOCDATA | XML_PARSE_NOBLANKS | XML_PARSE_HUGE | XML_PARSE_RECOVER);
    if (reader == nullptr)
        return -1;
    XMLReader(reader, pb, newxta).project();
    return 0;
}

int32_t parse_XML_file(const std::filesystem::path& path, ParserBuilder& pb, bool newxta)
{
    auto filename = path.string();
    xmlTextReaderPtr reader = xmlReaderForFile(
        filename.c_str(), "", XML_PARSE_NOCDATA | XML_PARSE_NOBLANKS | XML_PARSE_HUGE | XML_PARSE_RECOVER);
    if (reader == nullptr)
        return -1;
    XMLReader(reader, pb, newxta).project();
    return 0;
}

int32_t parse_XML_buffer(const char* buffer, ParserBuilder& pb, bool newxta)
{
    const auto length = static_cast<int>(strlen(buffer));
    xmlTextReaderPtr reader =
        xmlReaderForMemory(buffer, length, "", "", XML_PARSE_NOCDATA | XML_PARSE_HUGE | XML_PARSE_RECOVER);
    if (reader == nullptr)
        return -1;
    XMLReader(reader, pb, newxta).project();
    return 0;
}

/**
 * Get the contents of the XML element with the specified path
 * @param xmlDocPtr - The XML document.
 * @param pos - The position path
 * @return res - The contents
 */
std::string getXMLElement(xmlDocPtr docPtr, const std::string& path)  // used in verifyta.cpp
{
    std::string res;
    // Get the context
    xmlXPathContextPtr context = xmlXPathNewContext(docPtr);
    if (context == nullptr) {
        xmlFreeDoc(docPtr);
        return res;
    }
    xmlXPathObjectPtr result = xmlXPathEvalExpression((xmlChar*)path.c_str(), context);
    if (result != nullptr) {
        xmlNodeSetPtr nodeset = result->nodesetval;
        if (!xmlXPathNodeSetIsEmpty(nodeset) && nodeset->nodeNr > 0) {
            // The first point of the xml node
            xmlNodePtr node = nodeset->nodeTab[0];
            xmlChar* s = xmlNodeListGetString(docPtr, node->xmlChildrenNode, 1);
            if (s != nullptr)
                res = (char*)s;
            xmlFree(s);
        }
        xmlXPathFreeObject(result);
    }
    xmlXPathFreeContext(context);
    return res;
}

/**
 * Get the contents of the XML element with the specified path
 * @param xmlBuffer - The data in the xml buffer
 * @param pos - The position path
 * @return res - The contents
 */
/* // unused
static std::string getXMLElement(const char *xmlBuffer, const std::string &path)
{
    xmlDocPtr docPtr = xmlParseMemory(xmlBuffer, strlen(xmlBuffer));
    if(docPtr) {
        std::string res = getXMLElement(docPtr,path);
        xmlFreeDoc(docPtr);
        return res;
    }
    else {
        return "";
    }
}
*/

}  // namespace UTAP
