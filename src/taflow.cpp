// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2002-2015 Uppsala University and Aalborg University.
   
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

#include "utap/signalflow.h"
#include "utap/systembuilder.h"
#include "utap/typechecker.h"
#include "utap/system.h"

#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>

using UTAP::ParserBuilder;
using UTAP::SystemBuilder;
using UTAP::TypeException;
using UTAP::TypeChecker;
using UTAP::SystemVisitor;
using UTAP::TimedAutomataSystem;
using UTAP::SignalFlow;
using UTAP::Partitioner;
using UTAP::DistanceCalculator;

using std::vector;
using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::istream;
using std::string;

void printHelp(const char* binary)
{
    cout <<
        "Utility for extracting I/O information from UPPAAL system spec.\n"
        "Usage:\n " << binary << " [-bxrce -f format -i iofile] model.xml\n"
        "Options:\n"
        "     -b  use old (v. <=3.4) syntax for system specification;\n"
        "     -d  calculate distances from needles rather than partition;\n"
        "     -f <dot|tron>\n"
        "         dot:  for DOT (graphviz.org) format (default),\n"
        "         tron: for UPPAAL TRON format;\n"
        "     -i <filename>\n"
        "         for partitioning provide input and output channels:\n"
        "              \"input\" (chan)* \"output\" (chan)*\n"
        "         for calculating distances provide a list of needles, e.g.:\n"
        "              Process.Location1 Proc.localVariable globalVariable"
        "     -r  [DOT] rank symbols instead of plain map of system;\n"
        "     -c  [DOT] put channels on edges between processes;\n"
        "     -e  [DOT] use entity relationship notation;\n"
        "     -v  increment output verbosity level.\n";
}

int main(int argc, char *argv[])
{
    bool old=false, ranked=false, erd=false, chanEdge=false, distances=false;
    int format = 2, verbosity=0;
    char c;
    const char* iofile = NULL;

    while ((c = getopt(argc,argv,"bcdef:hi:rxv")) != -1)
    {
        switch(c) {
        case 'b':
            old = true;
            break;
        case 'c':
            chanEdge = true;
            break;
        case 'd':
            distances = true;
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
        case 'i':
            iofile = optarg;
            break;
        case 'r':
            ranked = true;
            break;
        case 'v':
            ++verbosity;
            break;
        default:
            cerr << "Unrecognized option: " << c << endl;
            exit(EXIT_FAILURE);
        }
    }

    TimedAutomataSystem system;

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
    catch (TypeException& e)
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

    if (iofile!=NULL) {
        SignalFlow *flow = NULL;
        if (!distances) {
            Partitioner *partitioner = new Partitioner(argv[optind], system);
            partitioner->setVerbose(verbosity);
            ifstream f(iofile);
            if (partitioner->partition(f)>1)
                cerr << "Partitioning is inconsistent" << endl;
            f.close();
            flow = partitioner;
        } else {
            DistanceCalculator *dcalc = 
                new DistanceCalculator(argv[optind], system);
            ifstream f(iofile);
            string needle;
            while (f) {
                f >> needle;
                dcalc->addProcessNeedle(needle.c_str());
            }
            flow = dcalc;
        }
        switch (format)
        {
        case 0:
        default:
            flow->printForDot(std::cout, ranked, erd, chanEdge);
            break;
        case 1:
            flow->printForTron(std::cout);
            break;
        }
        delete flow;
        exit(EXIT_SUCCESS);
    }

    SignalFlow flow(argv[optind], system);
    switch (format)
    {
    case 0:
    default:
        flow.printForDot(std::cout, ranked, erd, chanEdge);
        break;
    case 1:
        flow.printForTron(std::cout);
        break;
    }
    return 0;
}
