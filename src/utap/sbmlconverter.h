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

#ifndef SBMLREADER_H
#define	SBMLREADER_H

#include "utap/builder.h"
#include "utap/systembuilder.h"
#include "utap/SBMLtoXMLWriter.h"
#include <sbml/SBMLTypes.h>
#include <sbml/Model.h>
#include <sbml/math/ASTNode.h>
#include <libxml/xmlwriter.h>
#include <libxml/xmlreader.h>

#include <vector>
#include <boost/unordered_map.hpp>

#define x0 -256
#define y0 -320
#define x1 -192
#define y1 -128

namespace UTAP
{
    
class SBMLConverter {
public:
    SBMLConverter(xmlTextReaderPtr reader);
    void convertIntoXML();
    virtual ~SBMLConverter();
private:
    // infrastructure
    Model * model;
    xmlTextReaderPtr reader; /**< The underlying xmlTextReader */
    const char * filename;
    SBMLtoXMLWriter * bigWriter; /**< The writer derived from XMLWriter */
    
    // model information
    boost::unordered_map<int,boost::unordered_map<std::string,int> > change;
    boost::unordered_map<std::string,double> params;
    
    // declaration content to be written
    std::string paramsToWrite;
    std::string arrayOfSpecies;
    std::string arrayOfRates;
    std::string arrayOfChange;
    std::string functions;
    
    void initDocument();
    void declare();
    void build();
    void endDocument();
    void writeDeclarations();
    void getParams();
    double computeParam(const ASTNode *);
    void declareSpecies();
    void declareReactions();
    void declareChange();
    void propensity();
    void createUpdateFunction();
    void createReactionState(int);
    void createReactionTransition(int);
    bool listContains(ListOf *, std::string);
};

}
#endif	/* SBMLREADER_H */