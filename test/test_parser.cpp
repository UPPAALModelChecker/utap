// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-
///////////////////////////////////////////////////////////////////////////////
//
// This file is a part of UPPAAL.
// Copyright (c) 2021-2022, Aalborg University.
// All right reserved.
//
///////////////////////////////////////////////////////////////////////////////

/**
 * File:   test_parser.cpp
 * Author: Rasmus R. Kjær
 *
 * Created on 20 August 2021, 09:47
 */

#include "document_fixture.h"

#include "utap/StatementBuilder.hpp"
#include "utap/typechecker.h"
#include "utap/utap.h"

#include <doctest/doctest.h>

TEST_CASE("Double Serialization Test")
{
    auto doc = read_document("if_statement.xml");
    REQUIRE(doc);
    auto& errors = doc->get_errors();
    CHECK(errors.size() == 0);
    auto& warnings = doc->get_warnings();
    CHECK(warnings.size() == 0);
}

TEST_CASE("Power expressions")
{
    auto doc = read_document("powers.xml");
    REQUIRE(doc);
    auto& errors = doc->get_errors();
    CHECK(errors.size() == 0);
    auto& warnings = doc->get_warnings();
    CHECK(warnings.size() == 0);
}

TEST_CASE("External functions")
{
    auto doc = read_document("external_fn.xml");
    REQUIRE(doc);
    auto& errs = doc->get_errors();
    auto& warns = doc->get_warnings();
    REQUIRE(errs.size() == 3);  // "libbad" not found (x2), "absent" undefined.
    CHECK(warns.size() == 0);
}

TEST_CASE("Error location")
{
    auto doc = read_document("smc_non-deterministic_input2.xml");
    REQUIRE(doc);
    auto& errs = doc->get_errors();
    auto& warns = doc->get_warnings();
    REQUIRE(errs.size() == 0);
    CHECK(warns.size() == 0);
    const auto& templates = doc->get_templates();
    REQUIRE(templates.size() > 0);
    const auto& edges = templates.front().edges;
    REQUIRE(edges.size() > 0);
    const auto& pos = edges.front().sync.get_position();
    doc->add_error(pos, "Non-deterministic input", "c?");
    REQUIRE(errs.size() == 1);
    const auto& error = errs.front();
    REQUIRE(error.start.path != nullptr);
    CHECK(*error.start.path == "/nta/template[1]/transition[1]/label[1]");
}

TEST_CASE("SMC bounds in queries")
{
    auto doc = std::make_unique<UTAP::Document>();
    auto builder = std::make_unique<QueryBuilder>(*doc);
    SUBCASE("Probability estimation query with 7 runs")
    {
        auto res = parseProperty("Pr[<=1;7](<> true)", builder.get());
        REQUIRE(res == 0);
        auto expr = builder->getQuery();
        REQUIRE(expr.get_size() == 5);
        CHECK(expr.get(0).get_value() == 7);  // number of runs
    }
    SUBCASE("Probability estimation query without runs")
    {
        auto res = parseProperty("Pr[<=1](<> true)", builder.get());
        REQUIRE(res == 0);
        auto expr = builder->getQuery();
        REQUIRE(expr.get_size() == 5);
        CHECK(expr.get(0).get_value() == -1);  // number of runs
    }
    SUBCASE("Value estimation query with 7 runs")
    {
        auto res = parseProperty("E[<=1;7](max: 1)", builder.get());
        REQUIRE(res == 0);
        auto expr = builder->getQuery();
        REQUIRE(expr.get_size() == 5);
        CHECK(expr.get(0).get_value() == 7);  // number of runs
    }
    SUBCASE("Value estimation query without runs")
    {
        auto res = parseProperty("E[<=1](max: 1)", builder.get());
        REQUIRE(res == 0);
        auto expr = builder->getQuery();
        REQUIRE(expr.get_size() == 5);
        CHECK(expr.get(0).get_value() == -1);  // number of runs
    }
}

TEST_CASE("Parsing implicit goals for learning queries")
{
    using UTAP::Constants::kind_t;
    auto doc = read_document("simpleSystem.xml");
    auto builder = std::make_unique<QueryBuilder>(*doc);

    SUBCASE("Implicit time goal time priced")
    {
        auto res = parseProperty("minPr[<=20]", builder.get());
        CHECK(res == -1);
    }

    SUBCASE("Implicit step goal time priced")
    {
        REQUIRE(doc->get_errors().size() == 0);
        auto res = parseProperty("minE(c)[#<=20]", builder.get());
        CHECK(res == -1);
    }

    SUBCASE("Implicit constraint goal expr priced")
    {
        auto res = parseProperty("minE(c)[c<=25]", builder.get());
        CHECK(res == -1);
    }

    SUBCASE("Implicit time goal expr priced")
    {
        auto res = parseProperty("minE(c)[<=20]", builder.get());
        CHECK(res == -1);
    }

    SUBCASE("Implicit step goal expr priced")
    {
        auto res = parseProperty("minE(c)[#<=20]", builder.get());
        CHECK(res == -1);
    }

    SUBCASE("Explicit goal expr priced")
    {
        REQUIRE(doc->get_errors().size() == 0);
        auto res = parseProperty("minE(c)[<=20] :<> true", builder.get());
        REQUIRE(res == 0);
        builder->typecheck();
        REQUIRE(doc->get_errors().size() == 0);
    }

    SUBCASE("Explicit constraint goal expr priced")
    {
        REQUIRE(doc->get_errors().size() == 0);
        auto res = parseProperty("minE(c)[<=20] :<> c>=5", builder.get());
        REQUIRE(res == 0);
        builder->typecheck();
        REQUIRE(doc->get_errors().size() == 0);
    }
}

TEST_CASE("Function body is recovered after syntax error")
{
    auto f = document_fixture{};
    f.add_global_decl("void f(){ int x = }");

    auto doc = f.parse();
    CHECK(doc->get_globals().functions.size() == 1);
    CHECK(doc->get_globals().functions.back().body != nullptr);
}

TEST_CASE("Multiple functions despite early failure variable decl")
{
    auto f = document_fixture{};
    f.add_global_decl("void failing(){ int x = } void working(){ int x = 5;}");

    auto doc = f.parse();
    CHECK(doc->get_globals().functions.size() == 2);
    for (const UTAP::function_t& func : doc->get_globals().functions)
        CHECK(func.body != nullptr);
}

TEST_CASE("Multiple functions despite early failure type def")
{
    auto f = document_fixture{};
    f.add_global_decl("void failing(){ typedef int } void working(){ typedef int x;}");

    auto doc = f.parse();
    CHECK(doc->get_globals().functions.size() == 2);
    for (const UTAP::function_t& func : doc->get_globals().functions)
        CHECK(func.body != nullptr);
}

TEST_CASE("variable declaration failure shoulnt shadow declarations")
{
    auto f = document_fixture{};
    f.add_global_decl("int x = 0;int asdf\nint z = 0;");

    auto doc = f.parse();
    UTAP::symbol_t sym;
    CHECK(doc->get_globals().frame.resolve("x", sym));
    CHECK(doc->get_globals().frame.resolve("z", sym));
}

TEST_CASE("variable declaration failure shoulnt shadow declarations")
{
    auto f = document_fixture{};
    f.add_global_decl("typedef int x;\ntypedef int y\ntypedef int z;");

    auto doc = f.parse();
    UTAP::symbol_t sym;
    CHECK(doc->get_globals().frame.resolve("x", sym));
    CHECK(doc->get_globals().frame.resolve("z", sym));
}

TEST_CASE("variable declaration failure shoulnt shadow function")
{
    auto f = document_fixture{};
    f.add_global_decl("typedef int y\nvoid func(){}");

    auto doc = f.parse();
    CHECK(doc->get_globals().functions.size() == 1);
}

TEST_CASE("Missing closing curlybrace for function")
{
    auto f = document_fixture{};
    f.add_global_decl("void func(){ ");

    auto doc = f.parse();
    CHECK(doc->get_globals().functions.size() == 1);
    CHECK(doc->get_errors().size() > 0);
}

TEST_CASE("Missing closing curlybrace shouldnt shadow function")
{
    auto f = document_fixture{};
    f.add_global_decl("void func() {} void func2(){ ");

    auto doc = f.parse();
    CHECK(doc->get_globals().functions.size() == 2);
    CHECK(doc->get_errors().size() > 0);
}

TEST_CASE("Test leads to token is parsed correctly")
{
    auto f = document_fixture{}.add_default_process().build_query_fixture();
    CHECK_NOTHROW(f.parse_query("true --> true"));
}

TEST_CASE("Sim region cleanup causes memory errors (run with ASAN)")
{
    auto doc = read_document("lsc_example.xml");
    REQUIRE(doc);
    auto& errors = doc->get_errors();
    CHECK(errors.size() == 0);

    auto& templ = doc->get_templates().back();
    auto sims = templ.get_simregions();
    CHECK(sims.size() == 3);
}

TEST_CASE("Struct int,int initialization")
{
    auto doc =
        document_fixture{}.add_default_process().add_global_decl("const struct { int x; int y; } s = {1, 1};").parse();
    REQUIRE(doc);
    auto& errors = doc->get_errors();
    CHECK(errors.size() == 0);
    CHECK(doc->get_warnings().size() == 0);
}

TEST_CASE("Struct int,double initialization")
{
    auto doc = document_fixture{}
                   .add_default_process()
                   .add_global_decl("const struct { int x; double y; } s = {1, 1.0};")
                   .parse();
    REQUIRE(doc);
    auto& errors = doc->get_errors();
    CHECK(errors.size() == 0);
    CHECK(doc->get_warnings().size() == 0);
}

TEST_CASE("Struct double,double initialization")
{
    auto doc = document_fixture{}
                   .add_default_process()
                   .add_global_decl("const struct { double x; double y; } s = {1.0, 1};")
                   .parse();
    REQUIRE(doc);
    auto& errors = doc->get_errors();
    CHECK(errors.size() == 0);
    CHECK(doc->get_warnings().size() == 0);
}

TEST_CASE("Nested struct int,double initialization")
{
    auto doc =
        document_fixture{}
            .add_default_process()
            .add_global_decl("typedef struct { int x; double y; } S; struct { S s1; S s2; } s = {{5,5.5},{2,2.25}};")
            .parse();
    REQUIRE(doc);
    auto& errors = doc->get_errors();
    CHECK(errors.size() == 0);
    CHECK(doc->get_warnings().size() == 0);
}

TEST_CASE("Meta struct")
{
    auto doc = document_fixture{}
                   .add_default_process()
                   .add_global_decl("meta struct { int x; double y; } s = {1, 1.0};")
                   .parse();
    REQUIRE(doc);
    auto& errors = doc->get_errors();
    CHECK(errors.size() == 0);
    CHECK(doc->get_warnings().size() == 0);
}

TEST_CASE("Struct meta field")
{
    auto doc = document_fixture{}
                   .add_default_process()
                   .add_global_decl("meta struct { int x; meta double y; } s = {1, 1.0};")
                   .parse();
    REQUIRE(doc);
    auto& errors = doc->get_errors();
    CHECK(errors.size() == 0);
    CHECK(doc->get_warnings().size() == 0);
}