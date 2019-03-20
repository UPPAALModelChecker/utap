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

#ifndef XMLWRITER_H
#define	XMLWRITER_H

#include "utap/system.h"
#include "utap/common.h"

#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include <libxml/xmlreader.h>

#include <cstdio>
#include <cstdarg>
#include <cctype>
#include <cmath>
#include <cassert>
#include <stdexcept>
#include <list>
#include <sstream>

namespace UTAP {

    xmlChar * ConvertInput(const char *in, const char *encoding);

    /**
     * concatenates a string and an int
     */
    std::string concat(const std::string& s, int i);
    /**
     * concatenates a string and a double
     */
    std::string concatDouble(const std::string& s, double i);

    class XMLWriter
    {
    public: // was private - needed for derived class SBMLtoXMLWriter
        xmlTextWriterPtr writer; /**< The underlying xmlTextWriter */
        TimedAutomataSystem* taSystem; /**< The system to write */
        std::map<int, int> selfLoops;

        void startDocument();
        void endDocument();
        void startElement(const char* element);
        void endElement();
        void writeElement(const char* name, const char* content);
        void writeAttribute(const char* name, const char* value);
        void writeString(const char* content);
        void xmlwriteString(const xmlChar* content);

        void taTempl(const template_t& templ);
        void location(const state_t& state);
        void init(const template_t& templ);
        void name(const state_t& state, int x, int y);
        void writeStateAttributes(const state_t& state, int x, int y);
        void transition(const edge_t& edge);
        void nail(int x, int y);

        void label(const char* kind, std::string data, int x, int y);
        int source(const edge_t& edge);
        int target(const edge_t& edge);
        void selfLoop(int loc, float initialAngle, const edge_t& edge);
        void labels(int x, int y, const edge_t& edge);

        void declaration();
        std::string getChanPriority() const;
        void parameter();
        void system_instantiation();

    //public:
        XMLWriter(xmlTextWriterPtr writer, TimedAutomataSystem* taSystem);
        virtual ~XMLWriter();
        void project();
    };
}


#endif	/* XMLWRITER_H */

