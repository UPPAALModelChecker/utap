// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2002-2003 Uppsala University and Aalborg University.
   
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

#include "utap/iointerface.h"
#include "utap/systembuilder.h"
#include "utap/typechecker.h"
#include "utap/system.h"

#include <iostream>

using UTAP::ParserBuilder;
using UTAP::SystemBuilder;
using UTAP::TypeException;
using UTAP::TypeChecker;
using UTAP::SystemVisitor;
using UTAP::TimedAutomataSystem;
using UTAP::IOInterface;

using std::vector;
using std::cerr;
using std::cout;
using std::endl;

void printHelp(const char* binary)
{
    cout <<
	"Utility for extracting I/O information from UPPAAL system spec.\n"
	"Usage:\n     " << binary << " [-bxrcef format] uppaal.spec\n"
	"Options:\n"
	"     -b  use old (v. <=3.4) syntax for system specification;\n"
	"     -f <dot|tron>\n"
	"         dot:  for DOT (graphviz.org) format (default),\n"
	"         tron: for UPPAAL TRON format;\n"
	"     -r  [DOT] rank symbols instead of plain map of system;\n"
	"     -c  [DOT] put channels on edges between processes;\n"
	"     -e  [DOT] use entity relationship notation.\n";
}

int main(int argc, char *argv[])
{
    bool old=false, ranked=false, erd=false, chanEdge=false;
    int format = 2;
    char c;

    while ((c = getopt(argc,argv,"bcef:hrx")) != -1) 
    {
	switch(c) {
	case 'b':
	    old = true;
	    break;
	case 'c':
	    chanEdge = true;
	    break;
	case 'e':
	    erd = true;
	    break;
	case 'f':
	    if (strcmp(optarg, "dot")==0) 
	    {
		format = 0;
	    }
	    else if (strcmp(optarg, "tron")==0) 
	    {
		format = 1;
	    }
	    else 
	    {
		cerr << "-f expects either 'gui' or 'dot' argument.\n";
		exit(EXIT_FAILURE);
	    }
	    break;
	case 'h':
	    printHelp(argv[0]); exit(EXIT_FAILURE);
	    break;
	case 'r':
	    ranked = true;
	    break;
	default:
	    cerr << "Unrecognized option: " << c << endl;
	    exit(EXIT_FAILURE);
	}
    }

    TimedAutomataSystem system;

//    ParserBuilder *b = new SystemBuilder(&system);

    try 
    {
	if (argc - optind != 1)
	{
	    printHelp(argv[0]); exit(EXIT_FAILURE); 
	}
	if (strcasecmp(".xml", argv[optind] + strlen(argv[optind]) - 4) == 0) 
	{
	    parseXMLFile(argv[optind], &system, !old);
	}
	else 
	{
	    parseXTA(argv[optind], &system, !old);
	}
    } 
    catch (TypeException e) 
    {
	cerr << e.what() << endl;
    }

    TypeChecker tc(&system);
    system.accept(tc);

    vector<UTAP::error_t>::const_iterator it;
    const vector<UTAP::error_t> &errors = system.getErrors();
    const vector<UTAP::error_t> &warns = system.getWarnings();

    for (it = errors.begin(); it != errors.end(); it++)
    {
   	cerr << *it << endl;
    }
    for (it = warns.begin(); it != warns.end(); it++)
    {
   	cerr << *it << endl;
    }

    IOInterface io(argv[optind], system);
    switch (format) 
    {
    case 0:
    default:
	io.printForDot(std::cout, ranked, erd, chanEdge);
	break;
    case 1:
	io.printForTron(std::cout);
	break;
    }
    return 0;
}
