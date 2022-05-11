// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2002 Uppsala University and Aalborg University.

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

#include "utap/utap.h"

#include <iostream>
#include <string>
#include <vector>

using UTAP::Document;
using std::endl;
using std::cout;
using std::cerr;
using std::vector;

int main(int argc, char* argv[])
{
    using namespace std::literals::string_literals;
    try {
        if (argc < 2 || argc > 3) {
            std::cerr << "Synopsis: check [-b] <filename>" << std::endl;
            return 1;
        }
        auto old = ("-b"s == argv[1]);

        Document system;
        auto name = std::string{argv[argc - 1]};

        if (name.substr(name.length() - 4) == ".xml") {
            parseXMLFile(name.c_str(), &system, !old);
        } else {
            FILE* file = fopen(name.c_str(), "r");
            if (!file) {
                perror("check");
                return 1;
            }
            parseXTA(file, &system, !old);
            fclose(file);
        }
        for (const auto& err : system.getErrors())
            cerr << err << endl;
        for (const auto& warn : system.getWarnings())
            cerr << warn << endl;
        return system.getErrors().empty() && system.getWarnings().empty() ? 0 : 2;
    } catch (std::exception& e) {
        cerr << e.what() << endl;
        return 3;
    }
}
