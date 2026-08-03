// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2026 Aalborg University.

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

#include "print.hpp"

#include <doctest/doctest.h>

#include <sstream>
#include <vector>

TEST_SUITE_BEGIN("print.hpp");

TEST_CASE("print_infix with default delimiter")
{
    auto os = std::ostringstream{};
    auto v = std::vector<int>{1, 2, 3};
    print_infix(os, v);
    CHECK(os.str() == "1,2,3");
}

TEST_CASE("print_infix with custom delimiter")
{
    auto os = std::ostringstream{};
    auto v = std::vector<int>{1, 2, 3};
    print_infix(os, v, "; ");
    CHECK(os.str() == "1; 2; 3");
}

TEST_CASE("print_infix on an empty view prints nothing")
{
    auto os = std::ostringstream{};
    auto v = std::vector<int>{};
    print_infix(os, v);
    CHECK(os.str().empty());
}

TEST_CASE("print_infix on a single-element view prints no delimiter")
{
    auto os = std::ostringstream{};
    auto v = std::vector<int>{42};
    print_infix(os, v);
    CHECK(os.str() == "42");
}

TEST_CASE("print_infix_p with a custom element printer")
{
    auto os = std::ostringstream{};
    auto v = std::vector<int>{1, 2, 3};
    print_infix_p(os, v, [](std::ostream& out, int x) { out << '<' << x << '>'; });
    CHECK(os.str() == "<1>,<2>,<3>");
}

TEST_CASE("print_infix_p with a custom element printer and delimiter")
{
    auto os = std::ostringstream{};
    auto v = std::vector<int>{1, 2, 3};
    print_infix_p(
        os, v, [](std::ostream& out, int x) { out << '<' << x << '>'; }, "");
    CHECK(os.str() == "<1><2><3>");
}

TEST_CASE("infix helper with default delimiter")
{
    auto os = std::ostringstream{};
    auto v = std::vector<int>{1, 2, 3};
    os << infix(v);
    CHECK(os.str() == "1,2,3");
}

TEST_CASE("infix helper with custom delimiter")
{
    auto os = std::ostringstream{};
    auto v = std::vector<int>{1, 2, 3};
    os << infix(v, " - ");
    CHECK(os.str() == "1 - 2 - 3");
}

TEST_CASE("infix helper with an initializer_list")
{
    auto os = std::ostringstream{};
    os << infix{{1, 2, 3}};
    CHECK(os.str() == "1,2,3");
}

TEST_SUITE_END();
