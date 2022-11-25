// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2020 Aalborg University.
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

#include "utap/featurechecker.h"

#include "utap/utap.h"

#include <fstream>
#include <iostream>

int main(int argc, char** argv)
{
    const auto& command = argv[0];  // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic) Pretty hard to avoid
    if (argc != 2) {
        std::cout
            << "UPPAAL feature checker - Check which features are supported by the UPPAAL Model Checker for a given TA"
            << std::endl;
        std::cout << "Usage: " << command << " [filename]" << std::endl;
        return 1;
    }
    const auto& filename = argv[1];  // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic) Pretty hard to avoid
    std::ifstream ifs(filename);
    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

    auto document = std::make_unique<UTAP::Document>();
    parse_XML_buffer(content.c_str(), document.get(), true);
    UTAP::FeatureChecker checker(*document);
    const auto& type = checker.get_supported_methods();

    std::cout << "UTAP feature checker" << std::endl;
    std::cout << "Checking file: " << filename << std::endl;

    std::cout << "Supports symbolic: " << type.symbolic << std::endl;
    std::cout << "Supports concrete: " << type.concrete << std::endl;
    std::cout << "Supports stochastic: " << type.stochastic << std::endl;
}
