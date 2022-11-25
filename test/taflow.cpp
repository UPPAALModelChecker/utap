// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2020 Aalborg University.
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

#include "utap/DocumentBuilder.hpp"
#include "utap/document.h"
#include "utap/signalflow.h"
#include "utap/typechecker.h"

#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>
#include <cstring>

using UTAP::TypeException;
using UTAP::TypeChecker;
using UTAP::Document;
using UTAP::SignalFlow;
using UTAP::Partitioner;
using UTAP::DistanceCalculator;

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::istream;
using std::string;

static void printHelp(const char* binary)
{
    cout << "Utility for extracting I/O information from UPPAAL system spec.\n"
            "Usage:\n "
         << binary
         << " [-bxrce -f format -i iofile] model.xml\n"
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
            "              Process.Location1 Proc.localVariable globalVariable\n"
            "     -r  [DOT] rank symbols instead of plain map of system;\n"
            "     -c  [DOT] put channels on edges between processes;\n"
            "     -e  [DOT] use entity relationship notation;\n"
            "     -v  increment output verbosity level.\n";
}

int main(int argc, char* argv[])
{
    bool old = false;
    bool ranked = false;
    bool erd = false;
    bool chanEdge = false;
    bool distances = false;
    int format = 2;
    int verbosity = 0;
    const char* iofile = nullptr;
    int c;

    while ((c = getopt(argc, argv, "bcdef:hi:rxv")) != -1) {
        switch (c) {
        case 'b': old = true; break;
        case 'c': chanEdge = true; break;
        case 'd': distances = true; break;
        case 'e': erd = true; break;
        case 'f':
            if (strcmp(optarg, "dot") == 0) {
                format = 0;
            } else if (strcmp(optarg, "tron") == 0) {
                format = 1;
            } else {
                cerr << "-f expects either 'gui' or 'dot' argument.\n";
                exit(EXIT_FAILURE);
            }
            break;
        case 'i': iofile = optarg; break;
        case 'r': ranked = true; break;
        case 'v': ++verbosity; break;
        case 'h': printHelp(argv[0]); exit(EXIT_FAILURE);
        default: cerr << "Unrecognized option: " << c << endl; exit(EXIT_FAILURE);
        }
    }

    Document document;

    try {
        if (argc - optind != 1) {
            printHelp(argv[0]);
            exit(EXIT_FAILURE);
        }
        if (strcasecmp(".xml", argv[optind] + strlen(argv[optind]) - 4) == 0) {
            parse_XML_file(argv[optind], &document, !old);
        } else {
            parse_XTA(argv[optind], &document, !old);
        }
    } catch (TypeException& e) {
        cerr << e.what() << endl;
    }

    TypeChecker tc(document);
    document.accept(tc);

    for (const auto& error : document.get_errors()) {
        cerr << error << endl;
    }
    for (const auto& warning : document.get_warnings()) {
        cerr << warning << endl;
    }

    if (iofile != nullptr) {
        SignalFlow* flow;
        if (!distances) {
            auto* partitioner = new Partitioner(argv[optind], document);
            partitioner->setVerbose(verbosity);
            ifstream f(iofile);
            if (partitioner->partition(f) > 1)
                cerr << "Partitioning is inconsistent" << endl;
            f.close();
            flow = partitioner;
        } else {
            auto* dcalc = new DistanceCalculator(argv[optind], document);
            auto f = ifstream{iofile};
            string needle;
            while (f >> needle) {
                dcalc->addProcessNeedle(needle);
            }
            flow = dcalc;
        }
        switch (format) {
        case 0:
        default: flow->printForDot(std::cout, ranked, erd, chanEdge); break;
        case 1: flow->printForTron(std::cout); break;
        }
        delete flow;
        exit(EXIT_SUCCESS);
    }

    SignalFlow flow(argv[optind], document);
    switch (format) {
    case 0:
    default: flow.printForDot(std::cout, ranked, erd, chanEdge); break;
    case 1: flow.printForTron(std::cout); break;
    }
    return 0;
}
