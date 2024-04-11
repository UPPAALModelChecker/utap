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

struct Contains
{
    std::string_view text;
};

bool operator==(std::string_view text, const Contains& sub) { return text.find(sub.text) != std::string_view::npos; }
bool operator!=(std::string_view text, const Contains& sub) { return !(text == sub); }
std::ostream& operator<<(std::ostream& os, const Contains& sub) { return os << sub.text; }

enum class OS { Windows, macOS, Linux };
#ifdef _WIN32
constexpr auto target_os = OS::Windows;
#elif __linux__
constexpr auto target_os = OS::Linux;
#elif __APPLE__
constexpr auto target_os = OS::macOS;
#else
#error "Unsupported target operating system"
#endif

TEST_CASE("External functions")
{
    auto doc = read_document("external_fn.xml");
    REQUIRE(doc);
    auto& errs = doc->get_errors();
    REQUIRE(errs.size() == 3);
    if constexpr (target_os == OS::Linux) {
        CHECK(errs[0].msg == Contains{"libbad.so: cannot open shared object file: No such file or directory"});
        CHECK(errs[0].msg == Contains{"libbad.so: cannot open shared object file: No such file or directory"});
        CHECK(errs[2].msg == Contains{"undefined symbol: absent"});
    } else if constexpr (target_os == OS::Windows) {
        CHECK(errs[0].msg == Contains{"Failed to open dynamic library libbad.dll: error 126: Module not found."});
        CHECK(errs[0].msg == Contains{"Failed to open dynamic library libbad.dll: error 126: Module not found."});
        CHECK(errs[2].msg == Contains{"Failed to find symbol: error 127: Procedure not found."});
    } else if constexpr (target_os == OS::macOS) {
        CHECK(errs[0].msg == Contains{"libbad.dylib: cannot open shared object file: No such file or directory"});
        CHECK(errs[0].msg == Contains{"libbad.dylib: cannot open shared object file: No such file or directory"});
        CHECK(errs[2].msg == Contains{"undefined symbol: absent"});
    } else {
        REQUIRE_MESSAGE(false, "OS is not supported");
    }
    auto& warns = doc->get_warnings();
    CHECK(warns.size() == 0);
    // TypeChecker is not run when errors are present, so we do it on our own:
    auto checker = UTAP::TypeChecker{*doc};
    doc->accept(checker);
    REQUIRE(errs.size() == 3);  // no new errors
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

TEST_CASE("Initializing doubles in struct with ints")
{
    auto doc = document_fixture{}
                   .add_default_process()
                   .add_global_decl("meta struct { double x; meta double y; } s = {1, 1};")
                   .parse();
    REQUIRE(doc);
    auto& errors = doc->get_errors();
    CHECK(errors.size() == 0);
    CHECK(doc->get_warnings().size() == 0);
}

TEST_CASE("Initializing ints with double value")
{
    auto doc =
        document_fixture{}.add_default_process().add_global_decl("struct { int x; int y; } s = {1.1, 1.2};").parse();
    REQUIRE(doc);
    auto& errors = doc->get_errors();
    CHECK(errors.size() == 2);
    CHECK(doc->get_warnings().size() == 0);
}

TEST_CASE("Meta field in non meta struct")
{
    auto doc = document_fixture{}
                   .add_default_process()
                   .add_global_decl("struct { int x; meta double y; } s = {1, 1.0};")
                   .parse();
    REQUIRE(doc);
    auto& errors = doc->get_errors();
    CHECK(errors.size() == 0);
    CHECK(doc->get_warnings().size() == 0);
}

TEST_CASE("Meta field in non meta struct")
{
    auto doc = document_fixture{}
                   .add_default_process()
                   .add_global_decl("struct { int x; meta double y; } s = {1, 1.0};")
                   .parse();
    REQUIRE(doc);
    auto& errors = doc->get_errors();
    CHECK(errors.size() == 0);
    CHECK(doc->get_warnings().size() == 0);
}

TEST_CASE("Nested structs")
{
    auto doc = document_fixture{}
                   .add_default_process()
                   .add_global_decl("struct { int x; struct { int y; double d;} data; } s = {1, {5, 5.0}};")
                   .parse();
    REQUIRE(doc);
    auto& errors = doc->get_errors();
    CHECK(errors.size() == 0);
    CHECK(doc->get_warnings().size() == 0);
}

TEST_CASE("Structs with arrays")
{
    auto doc = document_fixture{}
                   .add_default_process()
                   .add_global_decl("struct { int x[2]; double y[2]; } s = {{1,1}, {5.0, 5.0}};")
                   .parse();
    REQUIRE(doc);
    auto& errors = doc->get_errors();
    CHECK(errors.size() == 0);
    CHECK(doc->get_warnings().size() == 0);
}

TEST_CASE("Array of structs")
{
    auto doc = document_fixture{}
                   .add_default_process()
                   .add_global_decl("struct { int x; double y;} s[2] = {{1,5.0}, {1,2.5}};")
                   .parse();
    REQUIRE(doc);
    auto& errors = doc->get_errors();
    CHECK_MESSAGE(errors.size() == 0, errors.at(0).msg);
    CHECK(doc->get_warnings().size() == 0);
}

TEST_CASE("Pre increment precedence bug")
{
    auto doc = document_fixture{}
                   .add_global_decl("int i[2];")
                   .add_global_decl("void f(){ ++i[0]; }")
                   .add_default_process()
                   .parse();

    CHECK_MESSAGE(doc->get_errors().size() == 0, doc->get_errors().at(0).msg);
}

TEST_CASE("Post increment precedence bug")
{
    auto doc = document_fixture{}
                   .add_global_decl("int i[2];")
                   .add_global_decl("void f(){ i[0]++; }")
                   .add_default_process()
                   .parse();

    CHECK_MESSAGE(doc->get_errors().size() == 0, doc->get_errors().at(0).msg);
}

TEST_CASE("Double post increment precedence")
{
    auto doc = document_fixture{}
                   .add_global_decl("int i = 0;")
                   .add_global_decl("void f(){ i++++; }")
                   .add_default_process()
                   .parse();

    CHECK(doc->get_errors().size() == 1);
}

TEST_CASE("pre post increment precedence")
{
    auto doc = document_fixture{}
                   .add_global_decl("int i = 0;")
                   .add_global_decl("void f(){ ++i++; }")
                   .add_default_process()
                   .parse();

    CHECK(doc->get_errors().size() == 1);
}

TEST_CASE("Double pre increment with forced precedence")
{
    auto doc = document_fixture{}
                   .add_global_decl("int i = 0;")
                   .add_global_decl("void f(){ (++i)++; }")
                   .add_default_process()
                   .parse();

    CHECK_MESSAGE(doc->get_errors().size() == 0, doc->get_errors().at(0).msg);
}

TEST_CASE("Double pre increment precedence")
{
    auto doc = document_fixture{}
                   .add_global_decl("int i = 0;")
                   .add_global_decl("void f(){ ++++i; }")
                   .add_default_process()
                   .parse();

    CHECK_MESSAGE(doc->get_errors().size() == 0, doc->get_errors().at(0).msg);
}

TEST_CASE("Increment with array subscripting and dot accessing")
{
    auto doc = document_fixture{}
                   .add_global_decl("struct { int x, y; } axy[2];")
                   .add_global_decl("void f(){ ++axy[0].x; axy[0].x++; }")
                   .add_default_process()
                   .parse();

    CHECK_MESSAGE(doc->get_errors().size() == 0, doc->get_errors().at(0).msg);
}

TEST_CASE("Increment with multiple array subscripting and dot accessing")
{
    auto doc = document_fixture{}
                   .add_global_decl("struct { int ai[2]; } aai[2];")
                   .add_global_decl("void f(){ ++aai[0].ai[0]; aai[0].ai[0]++; }")
                   .add_default_process()
                   .parse();

    CHECK_MESSAGE(doc->get_errors().size() == 0, doc->get_errors().at(0).msg);
}