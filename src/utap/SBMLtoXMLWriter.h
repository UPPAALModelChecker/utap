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

#ifndef SBMLTOXMLWRITER_H
#define	SBMLTOXMLWRITER_H

#include "utap/xmlwriter.h"

class SBMLtoXMLWriter : public UTAP::XMLWriter {
public:
    SBMLtoXMLWriter(xmlTextWriterPtr writer);
    void declaration(const char *);
    void writeStateAttributes(const char *, int, int);
    void name(const char *, int, int);
    void writeLocation(const char *, int, int, const char *);
    void startLocation(const char *, int, int);
    void writeBranchpoint(const char *, int, int);
    void init(const char * id);
    void source(const char * id);
    void target(const char * id);
    void writeTransition(const char * idSRC, const char * idTRG);
    void startTransition(const char * idSRC, const char * idTRG);
    void writeLabel(const char *, const char *, int, int);
    virtual ~SBMLtoXMLWriter();
private:
    xmlTextWriterPtr writer;           /**< The underlying xmlTextWriter */

};

#endif	/* SBMLTOXMLWRITER_H */

