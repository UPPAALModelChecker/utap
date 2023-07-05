#include "document_fixture.h"

#include "utap/StatementBuilder.hpp"
#include "utap/utap.h"

#include <doctest/doctest.h>

TEST_CASE("Minimization pretty printing")
{
    auto doc = read_document("simpleSystem.xml");
    auto builder = std::make_unique<QueryBuilder>(*doc);
    SUBCASE("global time bound")
    {
        auto res = parseProperty("minE(c)[<=20] {} -> {} : <> c >= 20", builder.get());
        REQUIRE(res == 0);
        builder->typecheck();
        REQUIRE(doc->get_errors().empty());
        auto os = std::ostringstream{};
        builder->getQuery().print(os);
        CHECK(os.str() == "minE(c)[<=20] {} -> {} : <> c >= 20");
    }
    SUBCASE("step bound")
    {
        auto res = parseProperty("minE(c)[#<=20] {} -> {} : <> c >= 20", builder.get());
        REQUIRE(res == 0);
        builder->typecheck();
        REQUIRE(doc->get_errors().empty());
        auto os = std::ostringstream{};
        builder->getQuery().print(os);
        CHECK(os.str() == "minE(c)[#<=20] {} -> {} : <> c >= 20");
    }
    SUBCASE("cost bound without features")
    {
        auto res = parseProperty("minE(c)[c<=20] : <> c >= 20", builder.get());
        REQUIRE(res == 0);
        builder->typecheck();
        REQUIRE(doc->get_errors().empty());
        auto os = std::ostringstream{};
        builder->getQuery().print(os);
        CHECK(os.str() == "minE(c)[c<=20] : <> c >= 20");
    }
    SUBCASE("empty features")
    {
        auto res = parseProperty("minE(c)[c<=20] {} -> {} : <> c >= 20", builder.get());
        REQUIRE(res == 0);
        builder->typecheck();
        REQUIRE(doc->get_errors().empty());
        auto os = std::ostringstream{};
        builder->getQuery().print(os);
        CHECK(os.str() == "minE(c)[c<=20] {} -> {} : <> c >= 20");
    }
    SUBCASE("one discrete feature")
    {
        auto res = parseProperty("minE(c)[c<=20] { Process.location } -> {} : <> c >= 20", builder.get());
        REQUIRE(res == 0);
        builder->typecheck();
        REQUIRE(doc->get_errors().empty());
        auto os = std::ostringstream{};
        builder->getQuery().print(os);
        CHECK(os.str() == "minE(c)[c<=20] {Process.location} -> {} : <> c >= 20");
    }
    SUBCASE("one continuous feature")
    {
        auto res = parseProperty("minE(c)[c<=20] {} -> { c } : <> c >= 20", builder.get());
        REQUIRE(res == 0);
        builder->typecheck();
        REQUIRE(doc->get_errors().empty());
        auto os = std::ostringstream{};
        builder->getQuery().print(os);
        CHECK(os.str() == "minE(c)[c<=20] {} -> {c} : <> c >= 20");
    }
    SUBCASE("discrete and continuous features")
    {
        auto res = parseProperty("minE(c)[c<=20] { Process.location } -> { c } : <> c >= 20", builder.get());
        REQUIRE(res == 0);
        builder->typecheck();
        REQUIRE(doc->get_errors().empty());
        auto os = std::ostringstream{};
        builder->getQuery().print(os);
        CHECK(os.str() == "minE(c)[c<=20] {Process.location} -> {c} : <> c >= 20");
    }
}

TEST_CASE("Maximization pretty printing")
{
    auto doc = read_document("simpleSystem.xml");
    auto builder = std::make_unique<QueryBuilder>(*doc);
    SUBCASE("global time bound")
    {
        auto res = parseProperty("maxE(c)[<=20] {} -> {} : <> c >= 20", builder.get());
        REQUIRE(res == 0);
        builder->typecheck();
        REQUIRE(doc->get_errors().empty());
        auto os = std::ostringstream{};
        builder->getQuery().print(os);
        CHECK(os.str() == "maxE(c)[<=20] {} -> {} : <> c >= 20");
    }
    SUBCASE("step bound")
    {
        auto res = parseProperty("maxE(c)[#<=20] {} -> {} : <> c >= 20", builder.get());
        REQUIRE(res == 0);
        builder->typecheck();
        REQUIRE(doc->get_errors().empty());
        auto os = std::ostringstream{};
        builder->getQuery().print(os);
        CHECK(os.str() == "maxE(c)[#<=20] {} -> {} : <> c >= 20");
    }
    SUBCASE("cost bound without features")
    {
        auto res = parseProperty("maxE(c)[c<=20] : <> c >= 20", builder.get());
        REQUIRE(res == 0);
        builder->typecheck();
        REQUIRE(doc->get_errors().empty());
        auto os = std::ostringstream{};
        builder->getQuery().print(os);
        CHECK(os.str() == "maxE(c)[c<=20] : <> c >= 20");
    }
    SUBCASE("empty features")
    {
        auto res = parseProperty("maxE(c)[c<=20] {} -> {} : <> c >= 20", builder.get());
        REQUIRE(res == 0);
        builder->typecheck();
        REQUIRE(doc->get_errors().empty());
        auto os = std::ostringstream{};
        builder->getQuery().print(os);
        CHECK(os.str() == "maxE(c)[c<=20] {} -> {} : <> c >= 20");
    }
    SUBCASE("one discrete feature")
    {
        auto res = parseProperty("maxE(c)[c<=20] { Process.location } -> {} : <> c >= 20", builder.get());
        REQUIRE(res == 0);
        builder->typecheck();
        REQUIRE(doc->get_errors().empty());
        auto os = std::ostringstream{};
        builder->getQuery().print(os);
        CHECK(os.str() == "maxE(c)[c<=20] {Process.location} -> {} : <> c >= 20");
    }
    SUBCASE("one continuous feature")
    {
        auto res = parseProperty("maxE(c)[c<=20] {} -> { c } : <> c >= 20", builder.get());
        REQUIRE(res == 0);
        builder->typecheck();
        REQUIRE(doc->get_errors().empty());
        auto os = std::ostringstream{};
        builder->getQuery().print(os);
        CHECK(os.str() == "maxE(c)[c<=20] {} -> {c} : <> c >= 20");
    }
    SUBCASE("discrete and continuous features")
    {
        auto res = parseProperty("maxE(c)[c<=20] { Process.location } -> { c } : <> c >= 20", builder.get());
        REQUIRE(res == 0);
        builder->typecheck();
        REQUIRE(doc->get_errors().empty());
        auto os = std::ostringstream{};
        builder->getQuery().print(os);
        CHECK(os.str() == "maxE(c)[c<=20] {Process.location} -> {c} : <> c >= 20");
    }
}

TEST_CASE("saveStrategy pretty printing")
{
    auto doc = read_document("simpleSystem.xml");
    auto builder = std::make_unique<QueryBuilder>(*doc);
    auto res = parseProperty("saveStrategy(\"path\", Name)", builder.get());
    REQUIRE(res == 0);
    builder->typecheck();
    REQUIRE(doc->get_errors().empty());
    auto os = std::ostringstream{};
    builder->getQuery().print(os);
    CHECK(os.str() == "saveStrategy(\"path\", Name)");
}

TEST_CASE("Probability compare pretty print")
{
    auto f = document_fixture{}.add_default_process().build_query_fixture();
    REQUIRE(f.get_errors().empty());

    auto query = f.parse_query("Pr[<=20] (<> true) >= Pr[<=5]([] false)");
    REQUIRE(query.get_kind() == UTAP::Constants::PROBA_CMP);
    CHECK(query.str() == "Pr[<=20] (<> true) >= Pr[<=5] ([] false)");
}

TEST_CASE("Simulate pretty prints")
{
    auto f = document_fixture{}.add_default_process().build_query_fixture();
    REQUIRE(f.get_errors().empty());

    auto query1 = f.parse_query("simulate[<=20;1000] {5, true} : 100 : true");
    REQUIRE(query1.get_kind() == UTAP::Constants::SIMULATEREACH);
    CHECK(query1.str() == "simulate[<=20; 1000] {5, true} : 100 : true");

    auto query2 = f.parse_query("simulate[#<=10;500] {25, false}");
    REQUIRE(query2.get_kind() == UTAP::Constants::SIMULATE);
    CHECK(query2.str() == "simulate[#<=10; 500] {25, false}");
}

TEST_CASE("loadStrategy pretty printing")
{
    auto doc = read_document("simpleSystem.xml");
    auto builder = std::make_unique<QueryBuilder>(*doc);
    auto res = parseProperty("strategy Name = loadStrategy{Process.location}->{c}(\"path\")", builder.get());
    CHECK(res == 0);
    builder->typecheck();
    for (auto&& err : doc->get_errors())
        std::cerr << err << std::endl;
    CHECK(doc->get_errors().empty());
    auto os = std::ostringstream{};
    builder->getQuery().print(os);
    CHECK(os.str() == "loadStrategy{Process.location} -> {c}(\"path\")");
}
