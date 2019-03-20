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

#include "utap/xmlwriter.h"
#include <cstring>

using std::vector;
using std::list;
using std::map;
using std::ostringstream;
using std::string;
using namespace UTAP;
using namespace UTAP::Constants;

#define MY_ENCODING "utf-8"
#define STEP 120
#define PINK "#ff6666" //error state color
#define PI 3.1416
#define RADIUS 80

string UTAP::concat(const string& s, int i) {
    std::ostringstream o;
    o << s << i;
    return o.str();
}

string UTAP::concatDouble(const string& s, double i) {
    std::ostringstream o;
    o << s << i;
    return o.str();
}

XMLWriter::XMLWriter(xmlTextWriterPtr writer, TimedAutomataSystem* taSystem)
: writer(writer), taSystem(taSystem) {
}

XMLWriter::~XMLWriter() {
    xmlFreeTextWriter(writer);
}

/* Starts an element named "element" with no content,
 * as child of the current element or
 * as root (if it's the first element)*/
void XMLWriter::startElement(const char* element) {
    if (xmlTextWriterStartElement(writer, xmlCharStrdup(element)) < 0) {
        throw std::runtime_error("Error at xmlTextWriterStartElement");
    }
}

/* Closes the current element. */
void XMLWriter::endElement() {
    if (xmlTextWriterEndElement(writer) < 0) {
        throw std::runtime_error("Error at xmlTextWriterEndElement");
    }
}

/* Writes an element named "name", with the content
 * "content" as child of the current element. */
void XMLWriter::writeElement(const char* name, const char* content) {
    if (xmlTextWriterWriteElement(writer, xmlCharStrdup(name),
            xmlCharStrdup(content)) < 0) {
        throw std::runtime_error("Error at xmlTextWriterWriteElement");
    }
}

/* Writes a String in the current element. */
void XMLWriter::writeString(const char* data) {
    if (xmlTextWriterWriteString(writer, xmlCharStrdup(data)) < 0) {
        throw std::runtime_error("Error at xmlTextWriterWriteString");
    }
}

/* Write a String in the current element. */
void XMLWriter::xmlwriteString(const xmlChar* data) {
    if (xmlTextWriterWriteString(writer, data) < 0) {
        throw std::runtime_error("Error at xmlTextWriterWriteString");
    }
}

/* Adds an attribute with name "name" and value "value"
 * to the current element. */
void XMLWriter::writeAttribute(const char* name, const char* value) {
    if (xmlTextWriterWriteAttribute(writer, xmlCharStrdup(name),
            xmlCharStrdup(value)) < 0) {
        throw std::runtime_error("Error at xmlTextWriterWriteAttribute");
    }
}

/** Parses optional declaration. */
void XMLWriter::declaration() {
    string globalDeclarations = taSystem->getGlobals().toString(true);
    globalDeclarations += "\n";
    globalDeclarations += getChanPriority();
    globalDeclarations += " ";
    writeElement("declaration", globalDeclarations.c_str());
}

string XMLWriter::getChanPriority() const {
    const list<chan_priority_t>* chanProc = &(taSystem->getChanPriorities());
    list<chan_priority_t>::const_iterator itr;
    string str = "";
    if (!chanProc->empty()) {
        str += "// channel priorities\n";
        for (itr = chanProc->begin(); itr != chanProc->end(); ++itr) {
            str += itr->toString() + ";";
            str += "\n";
        }
    }
    return str;
}

/* writes a "label" element with the "kind", "x" and "y" attributes
 * an with the "data" content. */
void XMLWriter::label(const char* kind, string data, int x, int y) {
    if (data == "1") {
        return;
    }
    if (data.substr(0, 5) == "1 && ") {
        data = data.substr(5, data.size() - 5);
    }
    xmlChar * tmp = ConvertInput(data.c_str(), MY_ENCODING);
    if (tmp == NULL) {
        return;
    }
    startElement("label");
    writeAttribute("kind", kind);
    writeAttribute("x", concat("", x).c_str());
    writeAttribute("y", concat("", y).c_str());
    xmlwriteString(tmp);
    xmlFree(tmp);
    endElement();
}

void XMLWriter::name(const state_t& state, int x, int y) {
    const char* name = state.uid.getName().c_str();
    startElement("name");
    writeAttribute("x", concat("", x).c_str());
    writeAttribute("y", concat("", y).c_str());
    writeString(name);
    endElement();
}

void XMLWriter::writeStateAttributes(const state_t& state, int x, int y) {
    int32_t id = state.locNr;
    writeAttribute("id", concat("id", id).c_str());
    writeAttribute("x", concat("", x).c_str());
    writeAttribute("y", concat("", y).c_str());
}

/* writes a location */
void XMLWriter::location(const state_t& state) {
    startElement("location");
    int x = STEP * state.locNr;
    int y = STEP * state.locNr;
    //identifier, x, y (attributes)
    writeStateAttributes(state, x, y);
    if (state.uid.getName() == "Err") {
        writeAttribute("color", PINK);
    }
    // name (element)
    name(state, x + 8, y + 8);
    // invariant
    if (!state.invariant.empty()) {
        const char* invariant = state.invariant.toString().c_str();
        label("invariant", invariant, x + 8, y + 24);
    }
    // "committed" or "urgent" element
    if (state.uid.getType().is(COMMITTED)) {
        startElement("committed");
        endElement();
    } else if (state.uid.getType().is(URGENT)) {
        startElement("urgent");
        endElement();
    }
    endElement(); //end of the "location" element
}

/* writes the init tag */
void XMLWriter::init(const template_t& templ) {
    int id = static_cast<const state_t*> (templ.init.getData())->locNr;
    startElement("init");
    writeAttribute("ref", concat("id", id).c_str());
    endElement();
}

/* writes the source of the given edge */
int XMLWriter::source(const edge_t& edge) {
    int loc = edge.src->locNr;
    const char* id = concat("id", loc).c_str();
    startElement("source");
    writeAttribute("ref", id);
    endElement();
    return loc;
}

/* writes the target of the given edge */
int XMLWriter::target(const edge_t& edge) {
    int loc = edge.dst->locNr;
    const char* id = concat("id", loc).c_str();
    startElement("target");
    writeAttribute("ref", id);
    endElement();
    return loc;
}

void XMLWriter::selfLoop(int loc, float initialAngle, const edge_t& edge) { // four loops in PI/2
    float begin = initialAngle + PI / 8 * selfLoops[loc] + 0.1;
    float end = begin + PI / 8 - 0.1;
    int l = loc*STEP;
    int x1 = l + (int) (RADIUS * cos(begin));
    int y1 = l + (int) (RADIUS * sin(begin));
    int x2 = l + (int) (RADIUS * cos(end));
    int y2 = l + (int) (RADIUS * sin(end));
    int x3 = l + (int) ((RADIUS + 10) * cos((begin + end) / 2));
    int y3 = l + (int) ((RADIUS + 10) * sin((begin + end) / 2));
    selfLoops[loc]++;

    labels(x3, y3, edge); //TODO
    nail(x1, y1);
    nail(x2, y2);
}

void XMLWriter::nail(int x, int y) {
    startElement("nail");
    writeAttribute("x", concat("", x).c_str());
    writeAttribute("y", concat("", y).c_str());
    endElement();
}

/* writes a transition */
void XMLWriter::transition(const edge_t& edge) {
    startElement("transition");
    // source and target
    int src = source(edge);
    int dst = target(edge);
    if (src == dst) {
        float angle = (edge.src->uid.getName() != "lpmin") ? 3 * PI / 2 : PI;
        selfLoop(src, angle, edge);
    } else {
        int x = STEP * src;
        int y = STEP * dst;
        // labels
        labels(x, y, edge);
        nail(x, y);
    }
    endElement(); // end of the "transition" element
}

void XMLWriter::labels(int x, int y, const edge_t& edge) {
    string str;
    if (edge.select.getSize() > 0) {
        str = edge.select[0].getName() + " : ";
        if (edge.select[0].getType().size() > 0
                && edge.select[0].getType()[0].size() > 0) {
            str += edge.select[0].getType()[0].getLabel(0);
        } //else ? should not happen
        label("select", str, x, y - 32);
    }
    if (!edge.guard.empty()) {
        label("guard", edge.guard.toString(), x, y - 16);
    }
    if (!edge.sync.empty()) {
        label("synchronisation", edge.sync.toString(), x, y);
    }
    if (!edge.assign.empty()) {
        label("assignment", edge.assign.toString(), x, y + 16);
    }
}

/** writes a template */
void XMLWriter::taTempl(const template_t& templ) {
    if (!templ.isTA) {
        return;
    }
    selfLoops.clear();
    string name = templ.uid.getName();
    string parameters = templ.writeParameters();
    string declarations = templ.toString(false);

    startElement("template");
    writeElement("name", name.c_str());
    writeElement("parameter", parameters.c_str());
    writeElement("declaration", declarations.c_str());

    //locations
    std::deque<state_t>::const_iterator s_itr;
    for (s_itr = templ.states.begin(); s_itr != templ.states.end(); ++s_itr) {
        location(*s_itr);
        selfLoops.insert(std::pair<int, int>(s_itr->locNr, 0));
    }
    // initial location
    init(templ);
    //transitions
    std::deque<edge_t>::const_iterator e_itr;
    for (e_itr = templ.edges.begin(); e_itr != templ.edges.end(); ++e_itr) {
        transition(*e_itr);
    }
    endElement(); // end of the "template" tag
}

void XMLWriter::system_instantiation() { // TODO proc priority
    const std::list<instance_t>* instances = &(taSystem->getProcesses());
    string str = "";
    string proc = "";
    std::list<instance_t>::const_iterator itr;
    for (itr = instances->begin(); itr != instances->end(); ++itr) {
        if (itr->uid.getName() != itr->templ->uid.getName()) {
            str += itr->uid.getName() + " = "
                    + itr->templ->uid.getName() + "("
                    + itr->writeArguments() + ");\n";
        }
        proc += itr->uid.getName() + ", ";
    }
    proc = proc.substr(0, proc.size() - 2);
    str += "system " + proc + "; ";
    writeElement("system", str.c_str());
}

/** Parse the project document. */
void XMLWriter::project() {
    startDocument();
    startElement("nta");
    declaration(); // global declarations

    const list<template_t>* templates = &(taSystem->getTemplates());
    std::list<template_t>::const_iterator itr; // = taSystem->getTemplates().begin();
    for (itr = templates->begin(); itr != templates->end(); ++itr) {
        taTempl(*itr);
    }
    system_instantiation();
    endElement(); // close the "nta" element
    endDocument();
}

void XMLWriter::startDocument() {
    /* Starts the document with the xml default for the version,
     * encoding UTF-8 and the default for the standalone
     * declaration. */
    if (xmlTextWriterStartDocument(writer, NULL, MY_ENCODING, NULL) < 0) {
        throw std::runtime_error("Error at xmlTextWriterStartDocument");
        return;
    }
    xmlTextWriterWriteDTD(writer, (xmlChar *) "nta",
            (xmlChar *) "-//Uppaal Team//DTD Flat System 1.1//EN",
            (xmlChar *) "http://www.it.uu.se/research/group/darts/uppaal/flat-1_1.dtd", NULL);
    xmlTextWriterSetIndent(writer, 1);
    xmlTextWriterSetIndentString(writer, (xmlChar *) "  ");
}

void XMLWriter::endDocument() {
    if (xmlTextWriterEndDocument(writer) < 0) {
        throw std::runtime_error("Error at xmlTextWriterEndDocument");
    }
}

/**
 * ConvertInput:
 * @in: string in a given encoding
 * @encoding: the encoding used
 *
 * Converts @in into UTF-8 for processing with libxml2 APIs
 *
 * Returns the converted UTF-8 string, or NULL in case of error.
 */
xmlChar * UTAP::ConvertInput(const char *in, const char *encoding) {
    xmlChar *out;
    int ret;
    int size;
    int out_size;
    int temp;
    xmlCharEncodingHandlerPtr handler;

    if (in == 0)
        return 0;

    handler = xmlFindCharEncodingHandler(encoding);
    if (!handler) {
        printf("ConvertInput: no encoding handler found for '%s'\n",
                encoding ? encoding : "");
        return 0;
    }

    size = (int) strlen(in) + 1;
    out_size = size * 2 - 1;
    out = (unsigned char *) xmlMalloc((size_t) out_size);

    if (out != 0) {
        temp = size - 1;
        ret = handler->input(out, &out_size, (const xmlChar *) in, &temp);
        if ((ret < 0) || (temp - size + 1)) {
            if (ret < 0) {
                printf("ConvertInput: conversion wasn't successful.\n");
            } else {
                printf
                        ("ConvertInput: conversion wasn't successful. converted: %i octets.\n",
                        temp);
            }

            xmlFree(out);
            out = 0;
        } else {
            out = (unsigned char *) xmlRealloc(out, out_size + 1);
            out[out_size] = 0; /*null terminating out */
        }
    } else {
        printf("ConvertInput: no mem\n");
    }
    return out;
}


using namespace UTAP;
//#if defined(LIBXML_WRITER_ENABLED) && defined(LIBXML_OUTPUT_ENABLED)

int32_t writeXMLFile(const char *filename, TimedAutomataSystem* taSystem) {
    xmlTextWriterPtr writer;

    /* Create a new XmlWriter for filename, with no compression. */
    writer = xmlNewTextWriterFilename(filename, 0);
    if (writer == NULL) {
        throw std::runtime_error("Error creating the xml writer");
    }
    XMLWriter(writer, taSystem).project();

    //xmlFreeTextWriter(writer);
    return 0;
}
