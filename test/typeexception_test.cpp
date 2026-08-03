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

#include "utap/builder.hpp"

#include <doctest/doctest.h>

#include <string>

using namespace UTAP;

TEST_SUITE_BEGIN("TypeException factory functions");

TEST_CASE("unknown_identifier_error")
{
    CHECK(std::string{unknown_identifier_error("foo").what()} == "$Unknown_identifier: foo");
}

TEST_CASE("has_no_such_member_error")
{
    CHECK(std::string{has_no_such_member_error("foo").what()} == "$has_no_member_named foo");
}

TEST_CASE("is_not_a_struct_error")
{
    CHECK(std::string{is_not_a_struct_error("foo").what()} == "foo $is_not_a_structure");
}

TEST_CASE("duplicate_definition_error")
{
    CHECK(std::string{duplicate_definition_error("foo").what()} == "$Duplicate_definition_of foo");
}

TEST_CASE("invalid_type_error")
{
    CHECK(std::string{invalid_type_error("foo").what()} == "$Invalid_type foo");
}

TEST_CASE("no_such_process_error")
{
    CHECK(std::string{no_such_process_error("foo").what()} == "$No_such_process: foo");
}

TEST_CASE("not_a_template_error")
{
    CHECK(std::string{not_a_template_error("foo").what()} == "$Not_a_template: foo");
}

TEST_CASE("not_a_process_error")
{
    CHECK(std::string{not_a_process_error("foo").what()} == "foo $is_not_a_process");
}

TEST_CASE("strategy_not_declared_error")
{
    CHECK(std::string{strategy_not_declared_error("foo").what()} == "$strategy_not_declared: foo");
}

TEST_CASE("unknown_dynamic_template_error")
{
    CHECK(std::string{unknown_dynamic_template_error("foo").what()} == "Unknown dynamic template foo");
}

TEST_CASE("shadows_a_variable_warning")
{
    CHECK(std::string{shadows_a_variable_warning("foo").what()} == "foo $shadows_a_variable");
}

TEST_SUITE_END();
