// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-

/* libutap - Uppaal Timed Automata Parser.
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

#include "libparser.h"
#ifdef ENABLE_SBML
#include "utap/sbmlconverter.h"
#endif

#include "utap/position.h"

#include <libxml/xmlreader.h>
#include <libxml/xpath.h>
#include <libxml/parser.h>
#include <libxml/xmlstring.h>
#include <stdexcept>
#include <cstdarg>
#include <cctype>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <list>
#include <vector>
#include <map>
#include <sstream>

using std::map;
using std::vector;
using std::list;
using std::ostringstream;
using std::string;

namespace UTAP {

    /**
     * Enumeration type for tags. We use gperf to generate a perfect
     * hash function to map tag strings to one of these tags.
     */

    enum tag_t {
        TAG_NTA, TAG_IMPORTS, TAG_DECLARATION, TAG_TEMPLATE,
        TAG_INSTANTIATION, TAG_SYSTEM, TAG_NAME, TAG_PARAMETER,
        TAG_LOCATION, TAG_INIT, TAG_TRANSITION, TAG_URGENT,
        TAG_COMMITTED, TAG_BRANCHPOINT, TAG_SOURCE, TAG_TARGET,
        TAG_LABEL, TAG_NAIL, TAG_NONE
        // LSC
        , TAG_PROJECT, TAG_LSC, TAG_TYPE, TAG_MODE, TAG_ROLE,
        TAG_YLOCCOORD, TAG_LSCLOCATION, TAG_PRECHART,
        TAG_INSTANCE, TAG_TEMPERATURE, TAG_MESSAGE, TAG_CONDITION,
        TAG_UPDATE, TAG_ANCHOR
        // SBML
        , TAG_SBML
        // QUERIES
        , TAG_QUERIES, TAG_QUERY, TAG_FORMULA, TAG_COMMENT
    };

#include "tags.cc"

    /**
     * Returns TRUE if string is zero length or contains only white
     * spaces otherwise FALSE.
     */
    static bool isempty(string str) {
        const char *p = str.c_str();
        while (*p) {
            if (!isspace((unsigned char)*p)) {
                return false;
            }
            p++;
        }
        return true;
    }

    static bool isAlpha(unsigned char c) {
        return isalpha(c) || c == '_';
    }

    static bool isIdChr(unsigned char c) {
        return isalnum(c) || c == '_' || c == '$' || c == '#';
    }

    /**
     * Extracts the alpha-numerical symbol used for variable/type
     * identifiers.  Identifier starts with alpha and further might
     * contain digits, white spaces are ignored.
     *
     * Throws a TypeException is identifier is invalid or a newly
     * allocated string to be destroyed with delete [].
     */
    static string symbol(const char *str) {
        if (str == NULL) {
            throw "Identifier expected";
        }
        while (isspace((unsigned char)*str)) {
            str++;
        }
        if (*str == 0) {
            throw "Identifier expected";
        }
        if (!isAlpha(*str)) {
            throw "Invalid identifier";
        }
        const char *end = str;
        while (isIdChr(*end)) end++;
        const char *p = end;
        while (isspace((unsigned char)*p)) {
            p++;
        }
        if (*p) {
            throw "Invalid identifier";
        }
        return string(str, end - str);
    }

    /**
     * Comparator structure for comparing two xmlChar* strings.
     */
    struct compare_str {

        bool operator()(const xmlChar* x, const xmlChar * y) const {
            return (strcmp((const char*) x, (const char*) y) < 0);
        }
    };

    /**
     * Path to current node. This path also contains information about
     * the left siblings of the nodes. This information is used to
     * generated an XPath expression.
     *
     * @see get()
     */
    class Path {
    private:
        list<vector<tag_t> > path;
    public:
        Path();
        void push(tag_t);
        tag_t pop();
        string get(tag_t tag = TAG_NONE) const;
    };

    Path::Path() {
        path.push_back(vector<tag_t > ());
    }

    void Path::push(tag_t tag) {
        path.back().push_back(tag);
        path.push_back(vector<tag_t > ());
    }

    tag_t Path::pop() {
        path.pop_back();
        return path.back().back();
    }

    /** Returns the XPath encoding of the current path. */
    string Path::get(tag_t tag) const {
        ostringstream str;
        list<vector<tag_t> >::const_iterator i;
        for (i = path.begin(); !i->empty() && i != path.end(); i++) {
            switch (i->back()) {
                case TAG_NTA:
                    str << "/nta";
                    break;
                case TAG_IMPORTS:
                    str << "/imports";
                    break;
                case TAG_DECLARATION:
                    str << "/declaration";
                    break;
                case TAG_TEMPLATE:
                    str << "/template[" <<
                            std::count(i->begin(), i->end(), TAG_TEMPLATE) << "]";
                    break;
                case TAG_INSTANTIATION:
                    str << "/instantiation";
                    break;
                case TAG_SYSTEM:
                    str << "/system";
                    break;
                case TAG_NAME:
                    str << "/name";
                    break;
                case TAG_PARAMETER:
                    str << "/parameter";
                    break;
                case TAG_LOCATION:
                    str << "/location["
                            << std::count(i->begin(), i->end(), TAG_LOCATION) << "]";
                    break;
                case TAG_BRANCHPOINT:
                    str << "/branchpoint["
                            << std::count(i->begin(), i->end(), TAG_BRANCHPOINT) << "]";
                    break;
                case TAG_INIT:
                    str << "/init";
                    break;
                case TAG_TRANSITION:
                    str << "/transition[" <<
                            std::count(i->begin(), i->end(), TAG_TRANSITION) << "]";
                    break;
                case TAG_LABEL:
                    str << "/label[" <<
                            std::count(i->begin(), i->end(), TAG_LABEL) << "]";
                    break;
                case TAG_URGENT:
                    str << "/urgent";
                    break;
                case TAG_COMMITTED:
                    str << "/committed";
                    break;
                case TAG_SOURCE:
                    str << "/source";
                    break;
                case TAG_TARGET:
                    str << "/target";
                    break;
                case TAG_NAIL:
                    str << "/nail["
                            << std::count(i->begin(), i->end(), TAG_NAIL) << "]";
                    break;
                case TAG_PROJECT:
                    str << "/project";
                    break;
                case TAG_LSC:
                    str << "/lscTemplate[" <<
                            std::count(i->begin(), i->end(), TAG_LSC) << "]";
                    break;
                case TAG_TYPE:
                    str << "/type";
                    break;
                case TAG_MODE:
                    str << "/mode";
                    break;
                case TAG_YLOCCOORD:
                    str << "/ylocoord[" <<
                            std::count(i->begin(), i->end(), TAG_YLOCCOORD) << "]";
                    break;
                case TAG_LSCLOCATION:
                    str << "/lsclocation";
                    break;
                case TAG_PRECHART:
                    str << "/prechart";
                    break;
                case TAG_INSTANCE:
                    str << "/instance["
                            << std::count(i->begin(), i->end(), TAG_INSTANCE) << "]";
                    break;
                case TAG_TEMPERATURE:
                    str << "/temperature["
                            << std::count(i->begin(), i->end(), TAG_TEMPERATURE) << "]";
                    break;
                case TAG_MESSAGE:
                    str << "/message["
                            << std::count(i->begin(), i->end(), TAG_MESSAGE) << "]";
                    break;
                case TAG_CONDITION:
                    str << "/condition["
                            << std::count(i->begin(), i->end(), TAG_CONDITION) << "]";
                    break;
                case TAG_UPDATE:
                    str << "/update["
                            << std::count(i->begin(), i->end(), TAG_UPDATE) << "]";
                    break;
                case TAG_ANCHOR:
                    str << "/anchor["
                            << std::count(i->begin(), i->end(), TAG_ANCHOR) << "]";
                    break;
                case TAG_SBML:
                    str << "/sbml["
                            << std::count(i->begin(), i->end(), TAG_SBML) << "]";
                    break;
                case TAG_QUERIES:
                    str << "/queries";
                    break;
                case TAG_QUERY:
                    str << "/query["
                            << std::count(i->begin(), i->end(), TAG_QUERY) << "]";
                    break;
                case TAG_FORMULA:
                    str << "/formula";
                    break;                
                default:
                    /* Strange tag on stack */
                    throw std::logic_error("XPath is corrupted");
            }
            if (i->back() == tag) {
                break;
            }
        }
        return str.str();
    }

    /**
     * Implements a recursive descent parser for UPPAAL XML documents.
     * Uses the xmlTextReader API from libxml2.
     */
    class XMLReader {
    private:
        typedef map<xmlChar*, string, compare_str> elementmap_t;

        xmlTextReaderPtr reader; /**< The underlying xmlTextReader */
        elementmap_t names; /**< Map from location (or instance line) id's to location (or instance line) names. */
        ParserBuilder *parser; /**< The parser builder to which to push the model. */
        bool newxta; /**< True if we should use new syntax. */
        Path path;
        bool nta; /**< True if the enclosing tag is "nta" (false if it is "project") */
        int bottomPrechart; /**< y location of the prechart bottom */
        string currentType; /**< type of the current LSC template */
        string currentMode; /**< mode of the current LSC template */

        tag_t getElement();
        bool isEmpty();
        int getNodeType();
        void read();
        bool begin(tag_t, bool skipEmpty = true);
        bool end(tag_t);

        const string getName(const xmlChar *id);
        int parse(const xmlChar *, xta_part_t syntax);

        bool declaration();
        bool label(bool required = false, string kind = "");
        int invariant();
        bool committed();
        bool urgent();
        bool location();
        bool branchpoint();
        bool init();
        string name(bool instanceLine = false);
        string readString(tag_t tag, bool instanceLine = false);
        string readText(bool instanceLine = false);
        int readNumber();
        string source();
        string target();
        bool transition();
        bool templ();
        int parameter();
        bool instantiation();
        void system();
        string reference(string attributeName);

        // LSC elements:
        bool lscTempl();
        string anchor();
        vector<char*> anchors();
        string type();
        string mode();
        int lscLocation();
        string temperature();
        bool yloccoord();
        bool instance();
        bool prechart();
        bool message();
        bool condition();
        bool update();

        // integrated query elements:
        bool queries();
        bool query();
        bool formula();
        bool comment();

    public:
        XMLReader(
                xmlTextReaderPtr reader, ParserBuilder *parser, bool newxta);
        virtual ~XMLReader();
        void project();
    };

    XMLReader::XMLReader(
            xmlTextReaderPtr reader, ParserBuilder *parser, bool newxta)
    : reader(reader), parser(parser), newxta(newxta) {
        read();
    }

    XMLReader::~XMLReader() {
        elementmap_t::iterator i;
        for (i = names.begin(); i != names.end(); ++i) {
            xmlFree(i->first);
        }
        xmlFreeTextReader(reader);
    }

    /** Returns the type of the current node. */
    int XMLReader::getNodeType() {
        return xmlTextReaderNodeType(reader);
    }

    /**
     * Returns the tag of the current element. Throws an exception if
     * the tag is not known.
     */
    tag_t XMLReader::getElement() {
        const char *element = (const char *) xmlTextReaderConstLocalName(reader);
        const Tag *tag = Tags::in_word_set(element, strlen(element));
        if (tag == NULL) {
            /* Unknown element. */
            throw std::runtime_error("Unknown tag in XML file");
        }
        return tag->tag;
    }

    /** Returns true if the current element is an empty element. */
    bool XMLReader::isEmpty() {
        return xmlTextReaderIsEmptyElement(reader);
    }

    /**
     * Read until start element. Returns true if that element has the
     * given tag. If skipEmpty is true, empty elements with the given
     * tag are ignored.
     */
    bool XMLReader::begin(tag_t tag, bool skipEmpty) {
        for (;;) {
            while (getNodeType() != XML_READER_TYPE_ELEMENT) {
                read();
            }
            if (getElement() != tag) {
                return false;
            }

            if (!skipEmpty || !isEmpty()) {
                return true;
            }
            read();
        }
    }
    /**
     * Is end of the tag in xml ?
     * @param tag - XML tag
     * @return True - if </...> tag found
     * Ignores whitespace
     */
    bool UTAP::XMLReader::end(UTAP::tag_t tag) {
        //Ignore whitespace
        while (getNodeType() == XML_READER_TYPE_WHITESPACE
               || getNodeType() == XML_READER_TYPE_SIGNIFICANT_WHITESPACE) {
            read();
        }
        // </...> tag found
        return getNodeType() == XML_READER_TYPE_END_ELEMENT && getElement() == tag;
    }
    /**
     * Advances the reader. It maintains the path to the current node.
     */
    void XMLReader::read() {
        if ((getNodeType() == XML_READER_TYPE_END_ELEMENT)
                || (getNodeType() == XML_READER_TYPE_ELEMENT && isEmpty())) {
            if (path.pop() != getElement()) {
                /* Path is corrupted */
                throw std::runtime_error("Invalid nesting in XML document");
            }
        }
        if (xmlTextReaderRead(reader) != 1) {
            /* Premature end of document. */
            throw std::runtime_error("Unexpected end of XML document");
        }

        if (getNodeType() == XML_READER_TYPE_ELEMENT) {
            path.push(getElement());
        }
    }

    /** Returns the name of a location. */
    const string XMLReader::getName(const xmlChar *id) {
        if (id) {
            elementmap_t::iterator l = names.find((xmlChar*) id);
            if (l != names.end()) {
                return l->second;
            }
        }
        throw std::runtime_error("Missing reference");
    }

    /** Invokes the bison generated parser to parse the given string. */
    int XMLReader::parse(const xmlChar *text, xta_part_t syntax) {
        return parseXTA((const char*) text, parser, newxta, syntax, path.get());
    }

    /** Parse optional declaration. */
    bool XMLReader::declaration() {
        if (begin(TAG_DECLARATION)) {
            read();
            if (getNodeType() == XML_READER_TYPE_TEXT) {
                parse(xmlTextReaderConstValue(reader), S_DECLARATION);
            }
            return true;
        }
        return false;
    }

    /** Parse optional label. */
    bool XMLReader::label(bool required, string s_kind) {
        xmlChar *kind;

        if (begin(TAG_LABEL)) {
            /* Get kind attribute. */
            kind = xmlTextReaderGetAttribute(reader, (const xmlChar *) "kind");
            read();

            /* Read the text and push it to the parser. */
            if (getNodeType() == XML_READER_TYPE_TEXT) {
                const xmlChar *text = xmlTextReaderConstValue(reader);

                if (strcmp((char*) kind, "invariant") == 0) {
                    parse(text, S_INVARIANT);
                } else if (strcmp((char*) kind, "select") == 0) {
                    parse(text, S_SELECT);
                } else if (strcmp((char*) kind, "guard") == 0) {
                    parse(text, S_GUARD);
                } else if (strcmp((char*) kind, "synchronisation") == 0) {
                    parse(text, S_SYNC);
                } else if (strcmp((char*) kind, "assignment") == 0) {
                    parse(text, S_ASSIGN);
                } else if (strcmp((char*) kind, "probability") == 0) {
                    parse(text, S_PROBABILITY);
                } else if (strcmp((char*) kind, "message") == 0)//LSC
                {
                    parse(text, S_MESSAGE);
                } else if (strcmp((char*) kind, "update") == 0)//LSC
                {
                    parse(text, S_UPDATE);
                } else if (strcmp((char*) kind, "condition") == 0)//LSC
                {
                    parse(text, S_CONDITION);
                }
            }
            xmlFree(kind);
            return true;
        } else if (required) {
            PositionTracker::setPath(parser, path.get());
            if (strcmp(s_kind.c_str(), "message") == 0)
                parser->handleError("$Message_label_is_required");
            else if (strcmp(s_kind.c_str(), "update") == 0)
                parser->handleError("$Update_label_is_required");
            else if (strcmp(s_kind.c_str(), "condition") == 0)
                parser->handleError("$Condition_label_is_required");
        }
        return false;
    }

    int XMLReader::invariant() {
        int result = -1;
        xmlChar *kind;

        if (begin(TAG_LABEL)) {
            /* Get kind attribute. */
            kind = xmlTextReaderGetAttribute(reader, (const xmlChar *) "kind");
            read();

            /* Read the text and push it to the parser. */
            if (getNodeType() == XML_READER_TYPE_TEXT) {
                const xmlChar *text = xmlTextReaderConstValue(reader);

                // This is a terrible mess but it's too badly designed
                // to fix at this moment.

                if (strcmp((char*) kind, "invariant") == 0) {
                    if (parse(text, S_INVARIANT) == 0) {
                        result = 0;
                    }
                } else if (strcmp((char*) kind, "exponentialrate") == 0) {
                    if (parse(text, S_EXPONENTIALRATE) == 0) {
                        result = 1;
                    }
                }
            }
            xmlFree(kind);
        }
        return result;
    }

    /** Parse optional name tag. */
    string XMLReader::name(bool instanceLine) {
        string text = readString(TAG_NAME, instanceLine);
        if (instanceLine && strcmp(text.c_str(), "") == 0)
            parser->handleError("$Instance_name_is_required");
        return text;
    }

    string XMLReader::readText(bool instanceLine) {
        if (getNodeType() == XML_READER_TYPE_TEXT)//text content of a node
        {
            xmlChar *text = xmlTextReaderValue(reader);
            PositionTracker::setPath(parser, path.get());
            PositionTracker::increment(parser, strlen((char*) text));
            try {
                string id = (instanceLine) ? (char*) text : symbol((char*) text);
                if (!isKeyword(id.c_str(), SYNTAX_OLD | SYNTAX_PROPERTY)) {
                    xmlFree(text);
                    return id;
                }
                parser->handleError("$Keywords_are_not_allowed_here");
            } catch (const char *str) {
                parser->handleError(str);
            }
            xmlFree(text);
        }
        return "";
    }

    int XMLReader::readNumber() {
        read();
        if (getNodeType() == XML_READER_TYPE_TEXT)//text content of a node
        {
            xmlChar *text = xmlTextReaderValue(reader);
            PositionTracker::setPath(parser, path.get());
            PositionTracker::increment(parser, strlen((char*) text));
            try {
                string id = (char*) text;
                xmlFree(text);
                return atoi(id.c_str());
            } catch (const char *str) {
                parser->handleError(str);
            }
            xmlFree(text);
        }
        return -1;
    }

    string XMLReader::readString(tag_t tag, bool instanceLine) {
        if (begin(tag)) {
            read();
            return readText(instanceLine);
        }
        return "";
    }

    /** Parse optional type tag. */
    string XMLReader::type() {
        return readString(TAG_TYPE);
    }

    /** Parse optional mode tag. */
    string XMLReader::mode() {
        return readString(TAG_MODE);
    }

    /** Parse required lsclocation tag for the prechart (bottom location
     * or the messages
     */
    int XMLReader::lscLocation() {
        int n = -1;
        if (begin(TAG_LSCLOCATION)) {
            n = readNumber();
        }
        if (n == -1)
            throw std::runtime_error("Missing LSC location");
        return n;
    }

    /** Parse optional committed tag. */
    bool XMLReader::committed() {
        if (begin(TAG_COMMITTED, false)) {
            read();
            return true;
        }
        return false;
    }

    /** Parse optional urgent tag. */
    bool XMLReader::urgent() {
        if (begin(TAG_URGENT, false)) {
            read();
            return true;
        }
        return false;
    }

    /** Parse optional location. */
    bool XMLReader::location() {
        string l_name;
        xmlChar *l_id = NULL;
        bool l_committed = false;
        bool l_urgent = false;
        bool l_invariant = false;
        bool l_exponentialRate = false;

        if (begin(TAG_LOCATION, false)) {
            try {
                string l_path = path.get(TAG_LOCATION);

                /* Extract ID attribute.
                 */
                l_id = xmlTextReaderGetAttribute(reader, (const xmlChar*) "id");

                read();

                /* Get name of the location.
                 */
                l_name = name();

                /* Read the invariant.
                 */
                while (begin(TAG_LABEL)) {
                    int res = invariant();
                    l_invariant |= res == 0;
                    l_exponentialRate |= res == 1;
                }

                /* Is the location urgent or committed?
                 */
                l_urgent = urgent();
                l_committed = committed();

                /* In case of anonymous locations we assign an
                 * internal name based on the ID of the
                 * location. FIXME: Is it ok to use an underscore
                 * here?
                 */
                if (isempty(l_name)) {
                    l_name = string("_") + (char*) l_id;
                }

                /* Remember the mapping from id to name
                 */
                names[l_id] = l_name;

                /* Any error messages generated by any of the
                 * procStateXXX calls must be attributed to the state
                 * element. To do this, we add a dummy position of
                 * length 1.
                 */
                PositionTracker::setPath(parser, l_path);
                PositionTracker::increment(parser, 1);

                /* Push location to parser builder.
                 */
                parser->procState(l_name.c_str(), l_invariant, l_exponentialRate);
                if (l_committed) {
                    parser->procStateCommit(l_name.c_str());
                }
                if (l_urgent) {
                    parser->procStateUrgent(l_name.c_str());
                }
            } catch (TypeException &e) {
                parser->handleError(e.what());
            }
            return true;
        }
        return false;
    }

    /** Parse optional instance. */
    bool XMLReader::instance() {
        string i_name;
        xmlChar *i_id = NULL;

        if (begin(TAG_INSTANCE, false)) {
            try {
                string i_path = path.get(TAG_INSTANCE);

                /* Extract ID attribute.
                 */
                i_id = xmlTextReaderGetAttribute(reader, (const xmlChar*) "id");
                read();

                /* Get name of the instance.
                 */
                PositionTracker::setPath(parser, i_path);
                PositionTracker::increment(parser, 1);

                i_name = name(true);

                /* Remember the mapping from id to name
                 */
                names[i_id] = i_name;

                /* Any error messages generated by the
                 * procInstanceLine call must be attributed to the
                 * instance line element. To do this, we add a dummy
                 * position of length 1.
                 */
                PositionTracker::setPath(parser, i_path);
                PositionTracker::increment(parser, 1);
                /* Push instance to parser builder.
                 */
                parser->procInstanceLine();
                parse((xmlChar*) i_name.c_str(), S_INSTANCELINE);

            } catch (TypeException &e) {
                parser->handleError(e.what());
            }
            return true;
        }
        return false;
    }

    /** Parse optional yloccoord */
    bool XMLReader::yloccoord() {
        if (begin(TAG_YLOCCOORD, false)) {
            read(); //used only for the GUI
            return true;
        }
        return false;
    }

    string XMLReader::temperature() {
        if (begin(TAG_TEMPERATURE, false)) {
            read();
            /* Get the temperature of the condition
             */
            return readText();
        }
        throw std::runtime_error("Missing temperature");
    }

    bool XMLReader::prechart() {
        if (begin(TAG_PRECHART, false)) {
            try {
                string p_path = path.get(TAG_PRECHART);

                /* Get the bottom location number
                 */
                read();
                bottomPrechart = lscLocation();
                if (strcasecmp(currentType.c_str(), "existential") == 0) {
                    PositionTracker::setPath(parser, p_path);
                    PositionTracker::increment(parser, 1);
                    parser->handleError("$Existential_charts_must_not_have_prechart");
                }
                parser->hasPrechart(true);
            } catch (TypeException &e) {
                parser->handleError(e.what());
            }
            return true;
        } else {
            bottomPrechart = -1;
            parser->hasPrechart(false);
        }
        return false;
    }

    bool XMLReader::message() {
        if (begin(TAG_MESSAGE)) {
            string from;
            string to;
            int location;

            /* Add dummy position mapping to the message element.
             */
            try {
                string m_path = path.get(TAG_MESSAGE);
                read();
                from = source();
                to = target();
                location = lscLocation();
                bool pch = (location < bottomPrechart);
                PositionTracker::setPath(parser, m_path);
                PositionTracker::increment(parser, 1);
                parser->procMessage(from.c_str(), to.c_str(), location, pch);
                PositionTracker::setPath(parser, m_path);
                PositionTracker::increment(parser, 1);
                label(true, "message");
            } catch (TypeException &e) {
                parser->handleError(e.what());
            }

            return true;
        }
        return false;
    }

    bool XMLReader::condition() {
        if (begin(TAG_CONDITION)) {
            vector<char*> instance_anchors;
            int location;
            string temp;
            bool pch, hot;

            try {
                string c_path = path.get(TAG_CONDITION);
                read();

                instance_anchors = anchors();
                location = lscLocation();
                pch = (location < bottomPrechart);

                PositionTracker::setPath(parser, c_path);
                PositionTracker::increment(parser, 1);
                temp = temperature();
                hot = (temp == "hot");
                parser->procCondition(instance_anchors, location, pch, hot);

                label(true, "condition");
            } catch (TypeException &e) {
                parser->handleError(e.what());
            }

            return true;
        }
        return false;
    }

    bool XMLReader::update() {
        if (begin(TAG_UPDATE)) {
            string instance_anchor;
            int location;
            bool pch;

            try {
                string u_path = path.get(TAG_UPDATE);
                //location = atoi((char*)xmlTextReaderGetAttribute(reader, (const xmlChar*)"y"));
                //pch = (location < bottomPrechart);
                read();

                instance_anchor = anchor();
                location = lscLocation();
                pch = (location < bottomPrechart);

                PositionTracker::setPath(parser, u_path);
                PositionTracker::increment(parser, 1);
                parser->procLscUpdate(instance_anchor.c_str(), location, pch);
                label(true, "update");
            } catch (TypeException &e) {
                parser->handleError(e.what());
            }

            return true;
        }
        return false;
    }

    /** Parse optional branchpoint. */
    bool XMLReader::branchpoint() {
        string b_name;
        xmlChar *b_id = NULL;

        if (begin(TAG_BRANCHPOINT, false)) {
            try {
                string b_path = path.get(TAG_BRANCHPOINT);


                /* Extract ID attribute.
                 */
                b_id = xmlTextReaderGetAttribute(reader, (const xmlChar*) "id");

                read();

                /* We assign an internal name based on the ID of the
                 * branchpoint.
                 */
                b_name = string("_") + (char*) b_id;

                /* Remember the mapping from id to name
                 */
                names[b_id] = b_name;


                //FIXME: probably not necessary
                /* Any error messages generated by any of the
                 * procStateXXX calls must be attributed to the state
                 * element. To do this, we add a dummy position of
                 * length 1.
                 */
                PositionTracker::setPath(parser, b_path);
                PositionTracker::increment(parser, 1);

                /* Push branchpoint to parser builder.
                 */
                parser->procBranchpoint(b_name.c_str());
            } catch (TypeException &e) {
                parser->handleError(e.what());
            }
            return true;
        }
        return false;
    }

    /** Parse optional init tag. The caller must define a position to
     * which any error messages are attached.
     */
    bool XMLReader::init() {
        if (begin(TAG_INIT, false)) {
            /* Get reference attribute.
             */
            xmlChar *ref = xmlTextReaderGetAttribute(reader, (const xmlChar*) "ref");

            /* Find location name for the reference.
             */
            if (ref) {
                string name = getName(ref);
                try {
                    parser->procStateInit(name.c_str());
                } catch (TypeException& te) {
                    parser->handleError(te.what());
                }
            } else {
                parser->handleError("$Missing_initial_location");
            }
            xmlFree(ref);
            read();
            return true;
        } else {
            parser->handleError("$Missing_initial_location");
        }
        return false;
    }

    string XMLReader::reference(string attributeName) {
        string name;
        xmlChar *id = xmlTextReaderGetAttribute(reader, (const xmlChar*) attributeName.c_str());
        name = getName(id);
        xmlFree(id);
        read();
        return name;
    }

    /** Parse obligatory source tag. */
    string XMLReader::source() {
        if (begin(TAG_SOURCE, false))
            return reference("ref");
        throw std::runtime_error("Missing source element");
    }

    /** Parse obligatory target tag. */
    string XMLReader::target() {
        if (begin(TAG_TARGET, false))
            return reference("ref");
        throw std::runtime_error("Missing target element");
    }

    /** Parse obligatory anchor tag for update. */
    string XMLReader::anchor() {
        if (begin(TAG_ANCHOR, false))
            return reference("instanceid");
        throw std::runtime_error("Missing anchor element");
    }

    /** Parse obligatory anchor tag for condition. */
    vector<char*> XMLReader::anchors() {
        vector<char*> names;
        while (begin(TAG_ANCHOR, false)) {
            string name = reference("instanceid");
            names.push_back(const_cast<char*> (name.c_str()));
        }

        if (names.size() == 0)
            throw std::runtime_error("Missing anchor element");
        return names;
    }

    /** Parse optional transition. */
    bool XMLReader::transition() {
        if (begin(TAG_TRANSITION)) {
            string from;
            string to;
            bool control = true;
            string actname;

            /* Add dummy position mapping to the transition element.
             */
            try {
                xmlChar *type =
                        xmlTextReaderGetAttribute(reader, (const xmlChar*) "controllable");
                control = (type == NULL || !(strcmp((char*) type, "true")));
                xmlFree(type);

                xmlChar *id = xmlTextReaderGetAttribute(reader, (const xmlChar*) "action");
                if (id) {
                    actname = (char *) id;
                } else {
                    actname = "SKIP";
                }
                xmlFree(id);

                read();
                from = source();
                to = target();

                parser->procEdgeBegin(from.c_str(), to.c_str(), control, actname.c_str());
                while (label());
                while (begin(TAG_NAIL)) {
                    read();
                }
                parser->procEdgeEnd(from.c_str(), to.c_str());
            } catch (TypeException &e) {
                parser->handleError(e.what());
            }

            return true;
        }
        return false;
    }

    /**
     * Parses an optional parameter tag and returns the number of
     * parameters.
     */
    int XMLReader::parameter() {
        int count = 0;
        if (begin(TAG_PARAMETER)) {
            read();
            if (getNodeType() == XML_READER_TYPE_TEXT) {
                count = parse(xmlTextReaderConstValue(reader), S_PARAMETERS);
            }
        }
        return count;
    }

    /** Parse optional template. */
    bool XMLReader::templ() {
        string t_name;

        if (begin(TAG_TEMPLATE)) {
            string t_path = path.get(TAG_TEMPLATE);
            read();
            try {
                /* Get the name and the parameters of the template.
                 */
                t_name = name();
                parameter();

                /* Push template start to parser builder. This might
                 * throw a TypeException.
                 */
                PositionTracker::setPath(parser, t_path);
                PositionTracker::increment(parser, 1);
                parser->procBegin(t_name.c_str());

                /* Parse declarations, locations, branchpoints,
                 * the init tag and the transitions of the template.
                 */
                declaration();
                while (location());
                while (branchpoint());
                PositionTracker::setPath(parser, t_path);
                PositionTracker::increment(parser, 1);
                init();
                while (transition());

                /* Push template end to parser builder.
                 */
                PositionTracker::setPath(parser, t_path);
                PositionTracker::increment(parser, 1);
                parser->procEnd();
            } catch (TypeException &e) {
                parser->handleError(e.what());
            }

            return true;
        }
        return false;
    }

    /** Parse optional LSC template. */
    bool XMLReader::lscTempl() {
        string t_name;

        if (begin(TAG_LSC)) {
            string t_path = path.get(TAG_LSC);
            read();
            try {
                /* Get the name and the parameters of the template.
                 */
                t_name = name();
                parser->lscTemplateNames.push_back(t_name);
                parameter();

                currentType = type();

                currentMode = mode();

                /* Push template start to parser builder. This might
                 * throw a TypeException.
                 */
                PositionTracker::setPath(parser, t_path);
                PositionTracker::increment(parser, 1);
                parser->procBegin(t_name.c_str(), false, currentType, currentMode);

                /* Parse declarations, locations, instances, prechart
                 * messages, conditions and updates
                 */
                declaration();

                while (yloccoord());

                while (instance());

                prechart();

                while (message());

                while (condition());

                while (update());

                /* Push template end to parser builder.
                 */
                PositionTracker::setPath(parser, t_path);
                PositionTracker::increment(parser, 1);
                parser->procEnd();
            } catch (TypeException &e) {
                parser->handleError(e.what());
            }
            return true;
        }
        return false;
    }

    /** Parse optional instantiation tag. */
    bool XMLReader::instantiation() {
        if (begin(TAG_INSTANTIATION, false)) {
            const xmlChar *text = (const xmlChar*) "";
            read();
            if (getNodeType() == XML_READER_TYPE_TEXT) {
                text = xmlTextReaderConstValue(reader);
            }
            parse(text, S_INST);
            return true;
        }
        return false;
    }

    /** Parse optional system tag. */
    void XMLReader::system() {
        if (begin(TAG_SYSTEM, false)) {
            const xmlChar *text = (const xmlChar*) "";
            read();
            if (getNodeType() == XML_READER_TYPE_TEXT) {
                text = xmlTextReaderConstValue(reader);
            }
            parse(text, S_SYSTEM);
            while (!end(TAG_SYSTEM)) read();
        } else {
            string s = (nta) ? path.get(TAG_NTA) : path.get(TAG_PROJECT);
            PositionTracker::setPath(parser, s);
            PositionTracker::increment(parser, 1);
            parser->handleError("$Missing_system_tag");
        }
    }

    /** Parse optional enclosed queries inside the model file. */
    bool XMLReader::queries() {
        if (begin(TAG_QUERIES, false)) {
            read();
            while (!end(TAG_QUERIES) && query()) read();
            return true;
        } else {
            return false;
        }
    }
    bool XMLReader::query() {
        if (begin(TAG_QUERY, false)) {
            read();
            parser->queryBegin();
            formula();
            comment();
            parser->queryEnd();
            while (!end(TAG_QUERY)) read();
            return true;
        }
        return false;
    }
    bool XMLReader::formula(){
        if (begin(TAG_FORMULA, false)){
            read();
            string xpath = path.get(TAG_FORMULA);
            parser->queryFormula((const char*)xmlTextReaderConstValue(reader),
                                 xpath.c_str());
            return true;
        }
        return false;
    }
    bool XMLReader::comment(){
        if (begin(TAG_COMMENT, false)){
            read();
            parser->queryComment((const char*)xmlTextReaderConstValue(reader));
            return true;
        }
        return false;
    }

    /** Parse the project document. */
    void XMLReader::project() {
        if (!begin(TAG_NTA) && !begin(TAG_PROJECT)) {
#ifdef ENABLE_SBML
            if (begin(TAG_SBML)) {
                // launch SBML converter
                UTAP::SBMLConverter * sbmlc = new SBMLConverter(reader);
                sbmlc->convertIntoXML();
            } else {
#endif
                throw std::runtime_error("Missing nta or project element");
#ifdef ENABLE_SBML
            }
#endif
        } else {
            nta = (begin(TAG_NTA)) ? true : false;
            read();
            declaration();
            while (templ());
            while (lscTempl());
            instantiation();
            system();
            read(); // look ahead one tag
            if ((nta && !end(TAG_NTA)) || (!nta && !end(TAG_PROJECT)))
                queries();
            parser->done();
        }
    }

}

using namespace UTAP;

int32_t parseXMLFile(const char *filename, ParserBuilder *pb, bool newxta)
{
    xmlTextReaderPtr reader = xmlReaderForFile(filename, "", 
            XML_PARSE_NOCDATA | XML_PARSE_NOBLANKS | XML_PARSE_HUGE | XML_PARSE_RECOVER);
    if (reader == NULL) {
        return -1;
    }
    XMLReader(reader, pb, newxta).project();
    return 0;
}

int32_t parseXMLBuffer(const char *buffer, ParserBuilder *pb, bool newxta) {
    size_t length = strlen(buffer);
    xmlTextReaderPtr reader = xmlReaderForMemory(buffer, length, "", "", 
            XML_PARSE_NOCDATA | XML_PARSE_HUGE | XML_PARSE_RECOVER);
    if (reader == NULL) {
        return -1;
    }
    XMLReader(reader, pb, newxta).project();
    return 0;
}

/**
 * Get the contents of the XML element with the specified path
 * @param xmlDocPtr - The XML document.
 * @param pos - The position path
 * @return res - The contents 
 */    
string getXMLElement(xmlDocPtr docPtr, const string &path) {    
   
    string res;
    
    // Get the context 
    xmlXPathContextPtr context = xmlXPathNewContext(docPtr);
    if(context == NULL) {
        xmlFreeDoc(docPtr);
        return res;
    }
    
    xmlXPathObjectPtr result = xmlXPathEvalExpression((xmlChar*)path.c_str(), context);
    if(result!=NULL) {
        xmlNodeSetPtr nodeset = result->nodesetval;
        if(!xmlXPathNodeSetIsEmpty(nodeset) && nodeset->nodeNr>0) {
            //The first point of the xml node
            xmlNodePtr node = nodeset->nodeTab[0];            
            xmlChar *s = xmlNodeListGetString(docPtr, node->xmlChildrenNode, 1);
            if(s) {
                res = (char*)s;
            }
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
string getXMLElement(const char *xmlBuffer, const string &path) {
    xmlDocPtr docPtr = xmlParseMemory(xmlBuffer, strlen(xmlBuffer));
    if(docPtr) {    
        string res = getXMLElement(docPtr,path);
        xmlFreeDoc(docPtr);
        return res;
    }
    else {
        return "";
    }
}
