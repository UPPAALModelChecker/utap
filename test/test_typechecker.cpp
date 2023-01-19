// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2020-2022 Aalborg University.

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

#include "document_fixture.h"

#include "utap/typechecker.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

TEST_SUITE("Quantifier sum")
{
    TEST_CASE("sum expression")
    {
        document_fixture f;
        f.set_system_decls("int x = sum (index : int[0, 5]) index;");
        auto document = f.parse();

        CHECK(document->getErrors().size() == 0);
        CHECK(document->getWarnings().size() == 0);
    }

    TEST_CASE("sum over array")
    {
        document_fixture f;
        f.set_system_decls("int a[3] = {1,4,9};\nint x = sum(i : int[0, 2]) a[i];");
        auto document = f.parse();
        CHECK(document->getWarnings().size() == 0);
        const auto errors = document->getErrors();
        REQUIRE(errors.size() == 1);
        CHECK(errors[0].msg == "$Must_be_computable_at_compile_time");
    }

    TEST_CASE("sum over const array")
    {
        document_fixture f;
        f.set_system_decls("const int a[3] = {1,4,9};\nint x = sum(i : int[0, 2]) a[i];");
        auto document = f.parse();
        CHECK(document->getWarnings().size() == 0);
        CHECK(document->getErrors().size() == 0);
    }
}

TEST_SUITE("Quantifier forall")
{
    TEST_CASE("forall expression")
    {
        document_fixture f;
        f.set_system_decls("bool x = forall (index : int[0, 5]) index > 3;");
        auto document = f.parse();

        CHECK(document->getErrors().size() == 0);
        CHECK(document->getWarnings().size() == 0);
    }

    TEST_CASE("forall over array")
    {
        document_fixture f;
        f.set_system_decls("bool b[3]={1,1,1};\nbool x = forall(i : int[0,2]) b[i];");
        auto document = f.parse();
        CHECK(document->getWarnings().size() == 0);
        const auto errors = document->getErrors();
        REQUIRE(errors.size() == 1);
        CHECK(errors[0].msg == "$Must_be_computable_at_compile_time");
    }

    TEST_CASE("forall over const array")
    {
        document_fixture f;
        f.set_system_decls("const bool b[3]={1,1,1};\nbool x = forall(i : int[0,2]) b[i];");
        auto document = f.parse();
        CHECK(document->getWarnings().size() == 0);
        CHECK(document->getErrors().size() == 0);
    }
}

TEST_SUITE("Quantifier exists")
{
    TEST_CASE("exists expression")
    {
        document_fixture f;
        f.set_system_decls("bool x = exists (index : int[0, 5]) index > 3;");
        auto document = f.parse();
        CHECK(document->getErrors().size() == 0);
        CHECK(document->getWarnings().size() == 0);
    }
    TEST_CASE("exists over array")
    {
        document_fixture f;
        f.set_system_decls("bool b[3]={0,0,1};\nbool x = exists(i : int[0,2]) b[i];");
        auto document = f.parse();
        CHECK(document->getWarnings().size() == 0);
        const auto errors = document->getErrors();
        REQUIRE(errors.size() == 1);
        CHECK(errors[0].msg == "$Must_be_computable_at_compile_time");
    }
    TEST_CASE("exists over const array")
    {
        document_fixture f;
        f.set_system_decls("const bool b[3]={0,0,1};\nbool x = exists(i : int[0,2]) b[i];");
        auto document = f.parse();
        CHECK(document->getWarnings().size() == 0);
        CHECK(document->getErrors().size() == 0);
    }
}