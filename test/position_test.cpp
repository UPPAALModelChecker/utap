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

#include "utap/position.hpp"
#include "utap/utap.hpp"

#include <doctest/doctest.h>

#include <sstream>
#include <stdexcept>

TEST_SUITE_BEGIN("Position");

using namespace UTAP;

TEST_CASE("add_position throws on non-monotonically increasing positions")
{
    auto doc = Document{};
    doc.add_position(10, 0, 1, nullptr);
    CHECK_THROWS_WITH_AS(doc.add_position(5, 0, 2, nullptr), "Positions must be monotonically increasing",
                         std::logic_error);
}

TEST_CASE("find_position throws when no positions have been added")
{
    auto doc = Document{};
    CHECK_THROWS_WITH_AS(doc.find_position(0), "No positions have been added", std::logic_error);
}

TEST_CASE("Error::str and operator<< without a path")
{
    auto doc = Document{};
    doc.add_position(0, 0, 1, nullptr);
    doc.add_position(20, 0, 2, nullptr);
    doc.add_error(position_t{2, 5}, "Test message", "context");
    const auto& err = doc.get_errors().front();
    CHECK(err.str() == "Test message at line 1 column 2 to line 1 column 5");
    auto oss = std::ostringstream{};
    oss << err;
    CHECK(oss.str() == err.str());
}

TEST_CASE("Error::str and operator<< with a path agree on the path text")
{
    // Regression test: operator<<(ostream&, const Error&) used to stream
    // e.start.path (a shared_ptr<string>) directly, which invokes
    // std::shared_ptr's own operator<< and prints the raw pointer address
    // instead of the path text -- unlike Error::str(), which correctly
    // dereferences it. Both should report the same, human-readable path.
    auto doc = Document{};
    auto path = std::make_shared<std::string>("foo.xml");
    doc.add_position(0, 0, 1, path);
    doc.add_position(20, 0, 2, path);
    doc.add_warning(position_t{2, 5}, "Warn message");
    const auto& warn = doc.get_warnings().front();
    CHECK(warn.str() == "Warn message in foo.xml at line 1 column 2 to line 1 column 5");
    auto oss = std::ostringstream{};
    oss << warn;
    CHECK(oss.str() == warn.str());
}

TEST_CASE("Error::str reports an unknown position outside the recorded range")
{
    auto doc = Document{};
    doc.add_position(10, 0, 1, nullptr);
    doc.add_error(position_t{0, 5}, "Unknown pos test");
    CHECK(doc.get_errors().front().str() == "Unknown pos test (Unknown position in document)");
}

TEST_CASE("find_position binary-searches across more than two lines")
{
    auto doc = Document{};
    doc.add_position(0, 0, 1, nullptr);
    doc.add_position(10, 0, 2, nullptr);
    doc.add_position(20, 0, 3, nullptr);
    doc.add_position(30, 0, 4, nullptr);
    CHECK(doc.find_position(25).line == 3);
    CHECK(doc.find_position(5).line == 1);
}

TEST_CASE("PositionIndex::print dumps the table")
{
    auto doc = Document{};
    doc.add_position(0, 0, 1, nullptr);
    doc.add_position(20, 5, 2, nullptr);
    auto oss = std::ostringstream{};
    doc.get_positions().print(oss);
    CHECK(oss.str() == "0 0 1 0\n20 5 2 0\n");
}

TEST_SUITE_END();
