#include "document_fixture.h"

#include "utap/StatementBuilder.hpp"
#include "utap/expression.h"
#include "utap/utap.h"

#include <doctest/doctest.h>

using namespace UTAP;

TEST_CASE("Symbolic queries")
{
    auto doc = read_document("simpleSystem.xml");
    REQUIRE(doc->get_errors().empty());
    auto builder = std::make_unique<QueryBuilder>(*doc);
    auto* pb = builder.get();
    auto os = std::stringstream{};
    // the redundant white-space is there to stress the parser
    SUBCASE("Reachability")
    {
        auto res = parseProperty("E<> \t Process.L3", pb);
        REQUIRE(res == 0);
        pb->typecheck();
        REQUIRE(doc->get_errors().empty());
        pb->getQuery().print(os);
        CHECK(os.str() == "E<> Process.L3");
    }
    SUBCASE("Safety")
    {
        auto res = parseProperty("A[] \t Process.L3", pb);
        REQUIRE(res == 0);
        pb->typecheck();
        REQUIRE(doc->get_errors().empty());
        pb->getQuery().print(os);
        CHECK(os.str() == "A[] Process.L3");
    }
    SUBCASE("Liveness")
    {
        auto res = parseProperty("Process.L2 \t --> \t Process.L3", pb);
        REQUIRE(res == 0);
        pb->typecheck();
        REQUIRE(doc->get_errors().empty());
        pb->getQuery().print(os);
        CHECK(os.str() == "Process.L2 --> Process.L3");
    }
    SUBCASE("Infimum")
    {
        auto res = parseProperty("inf {  Process.L2  }  :  c", pb);
        REQUIRE(res == 0);
        pb->typecheck();
        REQUIRE(doc->get_errors().empty());
        pb->getQuery().print(os);
        CHECK(os.str() == "inf{Process.L2}: c");
    }
    SUBCASE("Supremum")
    {
        auto res = parseProperty("sup {  Process.L2  }  :  c", pb);
        REQUIRE(res == 0);
        pb->typecheck();
        REQUIRE(doc->get_errors().empty());
        pb->getQuery().print(os);
        CHECK(os.str() == "sup{Process.L2}: c");
    }
    SUBCASE("Bounds")
    {
        auto res = parseProperty("bounds {  Process.L2  }  :  c", pb);
        REQUIRE(res == 0);
        pb->typecheck();
        REQUIRE(doc->get_errors().empty());
        pb->getQuery().print(os);
        CHECK(os.str() == "bounds{Process.L2}: c");
    }
}

TEST_CASE("Minimization pretty printing")
{
    auto doc = read_document("simpleSystem.xml");
    REQUIRE(doc->get_errors().empty());
    auto builder = std::make_unique<QueryBuilder>(*doc);
    auto* pb = builder.get();
    auto os = std::ostringstream{};
    SUBCASE("global time bound")
    {
        auto res = parseProperty("minE(c)[<=20] {} -> {} : <> c >= 20", pb);
        REQUIRE(res == 0);
        builder->typecheck();
        REQUIRE(doc->get_errors().empty());
        builder->getQuery().print(os);
        CHECK(os.str() == "minE(c)[<=20] {} -> {} : <> c >= 20");
    }
    SUBCASE("step bound")
    {
        auto res = parseProperty("minE(c)[#<=20] {} -> {} : <> c >= 20", pb);
        REQUIRE(res == 0);
        builder->typecheck();
        REQUIRE(doc->get_errors().empty());
        builder->getQuery().print(os);
        CHECK(os.str() == "minE(c)[#<=20] {} -> {} : <> c >= 20");
    }
    SUBCASE("cost bound without features")
    {
        auto res = parseProperty("minE(c)[c<=20] : <> c >= 20", pb);
        REQUIRE(res == 0);
        builder->typecheck();
        REQUIRE(doc->get_errors().empty());
        builder->getQuery().print(os);
        CHECK(os.str() == "minE(c)[c<=20] : <> c >= 20");
    }
    SUBCASE("empty features")
    {
        auto res = parseProperty("minE(c)[c<=20] {} -> {} : <> c >= 20", pb);
        REQUIRE(res == 0);
        builder->typecheck();
        REQUIRE(doc->get_errors().empty());
        builder->getQuery().print(os);
        CHECK(os.str() == "minE(c)[c<=20] {} -> {} : <> c >= 20");
    }
    SUBCASE("one discrete feature")
    {
        auto res = parseProperty("minE(c)[c<=20] { Process.location } -> {} : <> c >= 20", pb);
        REQUIRE(res == 0);
        builder->typecheck();
        REQUIRE(doc->get_errors().empty());
        builder->getQuery().print(os);
        CHECK(os.str() == "minE(c)[c<=20] {Process.location} -> {} : <> c >= 20");
    }
    SUBCASE("one continuous feature")
    {
        auto res = parseProperty("minE(c)[c<=20] {} -> { c } : <> c >= 20", pb);
        REQUIRE(res == 0);
        builder->typecheck();
        REQUIRE(doc->get_errors().empty());
        builder->getQuery().print(os);
        CHECK(os.str() == "minE(c)[c<=20] {} -> {c} : <> c >= 20");
    }
    SUBCASE("discrete and continuous features")
    {
        auto res = parseProperty("minE(c)[c<=20] { Process.location } -> { c } : <> c >= 20", pb);
        REQUIRE(res == 0);
        builder->typecheck();
        REQUIRE(doc->get_errors().empty());
        builder->getQuery().print(os);
        CHECK(os.str() == "minE(c)[c<=20] {Process.location} -> {c} : <> c >= 20");
    }
}

TEST_CASE("Maximization pretty printing")
{
    auto doc = read_document("simpleSystem.xml");
    REQUIRE(doc->get_errors().empty());
    auto builder = std::make_unique<QueryBuilder>(*doc);
    auto* pb = builder.get();
    auto os = std::ostringstream{};
    SUBCASE("global time bound")
    {
        auto res = parseProperty("maxE(c)[<=20] {} -> {} : <> c >= 20", pb);
        REQUIRE(res == 0);
        builder->typecheck();
        REQUIRE(doc->get_errors().empty());
        builder->getQuery().print(os);
        CHECK(os.str() == "maxE(c)[<=20] {} -> {} : <> c >= 20");
    }
    SUBCASE("step bound")
    {
        auto res = parseProperty("maxE(c)[#<=20] {} -> {} : <> c >= 20", pb);
        REQUIRE(res == 0);
        builder->typecheck();
        REQUIRE(doc->get_errors().empty());
        builder->getQuery().print(os);
        CHECK(os.str() == "maxE(c)[#<=20] {} -> {} : <> c >= 20");
    }
    SUBCASE("cost bound without features")
    {
        auto res = parseProperty("maxE(c)[c<=20] : <> c >= 20", pb);
        REQUIRE(res == 0);
        builder->typecheck();
        REQUIRE(doc->get_errors().empty());
        builder->getQuery().print(os);
        CHECK(os.str() == "maxE(c)[c<=20] : <> c >= 20");
    }
    SUBCASE("empty features")
    {
        auto res = parseProperty("maxE(c)[c<=20] {} -> {} : <> c >= 20", pb);
        REQUIRE(res == 0);
        builder->typecheck();
        REQUIRE(doc->get_errors().empty());
        builder->getQuery().print(os);
        CHECK(os.str() == "maxE(c)[c<=20] {} -> {} : <> c >= 20");
    }
    SUBCASE("one discrete feature")
    {
        auto res = parseProperty("maxE(c)[c<=20] { Process.location } -> {} : <> c >= 20", pb);
        REQUIRE(res == 0);
        builder->typecheck();
        REQUIRE(doc->get_errors().empty());
        builder->getQuery().print(os);
        CHECK(os.str() == "maxE(c)[c<=20] {Process.location} -> {} : <> c >= 20");
    }
    SUBCASE("one continuous feature")
    {
        auto res = parseProperty("maxE(c)[c<=20] {} -> { c } : <> c >= 20", pb);
        REQUIRE(res == 0);
        builder->typecheck();
        REQUIRE(doc->get_errors().empty());
        builder->getQuery().print(os);
        CHECK(os.str() == "maxE(c)[c<=20] {} -> {c} : <> c >= 20");
    }
    SUBCASE("discrete and continuous features")
    {
        auto res = parseProperty("maxE(c)[c<=20] { Process.location } -> { c } : <> c >= 20", pb);
        REQUIRE(res == 0);
        builder->typecheck();
        REQUIRE(doc->get_errors().empty());
        builder->getQuery().print(os);
        CHECK(os.str() == "maxE(c)[c<=20] {Process.location} -> {c} : <> c >= 20");
    }
}

TEST_CASE("saveStrategy pretty printing")
{
    auto f = document_fixture{}.add_default_process().build_query_fixture();
    REQUIRE(f.get_errors().empty());
    const auto& strat = f.parse_query("strategy Name = control: A[] true");
    auto res = f.parse_query("saveStrategy(\"path\", Name)");
    CHECK(res.subjections.at(0) == &strat);
    CHECK(res.intermediate.str() == "saveStrategy(\"path\", Name)");
}

TEST_CASE("Probability compare pretty print")
{
    auto f = document_fixture{}.add_default_process().build_query_fixture();
    REQUIRE(f.get_errors().empty());

    auto query = f.parse_query("Pr[<=20] (<> true) >= Pr[<=5]([] false)").intermediate;
    REQUIRE(query.get_kind() == UTAP::Constants::PROBA_CMP);
    CHECK(query.str() == "Pr[<=20] (<> true) >= Pr[<=5] ([] false)");
}

TEST_CASE("Simulate pretty prints")
{
    auto f = document_fixture{}.add_default_process().build_query_fixture();
    REQUIRE(f.get_errors().empty());

    auto query1 = f.parse_query("simulate[<=20;1000] {5, true} : 100 : true").intermediate;
    REQUIRE(query1.get_kind() == UTAP::Constants::SIMULATEREACH);
    CHECK(query1.str() == "simulate[<=20; 1000] {5, true} : 100 : true");

    auto query2 = f.parse_query("simulate[#<=10;500] {25, false}").intermediate;
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

TEST_CASE("Array access pretty printing")
{
    auto f = document_fixture{}.add_global_decl("int arr[5];").add_default_process().build_query_fixture();
    REQUIRE(f.get_errors().empty());

    auto query1 = f.parse_query("E<> arr[2] == 5").intermediate;
    CHECK(query1.str() == "E<> arr[2] == 5");
}

TEST_CASE("Chaining conjunctions")
{
    auto f = document_fixture{}.add_default_process().build_query_fixture();
    REQUIRE(f.get_errors().empty());

    auto query1 = f.parse_query("E<> true && true && true").intermediate;
    CHECK(query1.str() == "E<> true && true && true");
}

TEST_CASE("Chaining disjunctive conjunctions")
{
    auto f = document_fixture{}.add_default_process().build_query_fixture();
    REQUIRE(f.get_errors().empty());

    auto query1 = f.parse_query("E<> true && true || true && true").intermediate;
    CHECK(query1.str() == "E<> true && true || true && true");
}

TEST_CASE("Chaining disjunctive conjunctions")
{
    auto f = document_fixture{}.add_default_process().build_query_fixture();
    REQUIRE(f.get_errors().empty());

    auto query1 = f.parse_query("E<> true || true && true || true").intermediate;
    CHECK(query1.str() == "E<> true || true && true || true");
}

TEST_CASE("Chaining disjunctive conjunctions with outer conjunction")
{
    auto f = document_fixture{}.add_default_process().build_query_fixture();
    REQUIRE(f.get_errors().empty());

    auto query1 = f.parse_query("E<> (true || true && true || true) && false").intermediate;
    CHECK(query1.str() == "E<> (true || true && true || true) && false");

    auto query2 = f.parse_query("E<> false && (true || true && true || true)").intermediate;
    CHECK(query2.str() == "E<> false && (true || true && true || true)");
}

TEST_CASE("Post incrementing an identifier should not require parenthesis")
{
    auto frame = frame_t::create();
    auto test_symbol = frame.add_symbol("foo", type_t::create_primitive(Constants::INT), {});
    auto id = expression_t::create_identifier(test_symbol);
    auto expr = expression_t::create_unary(Constants::POST_INCREMENT, id);

    CHECK(expr.str() == "foo++");
}

TEST_CASE("acontrol query")
{
    auto f = document_fixture{}
                 .add_default_process()
                 .add_system_decl("bool myBool;")
                 .add_system_decl("int myInt;")
                 .add_system_decl("int[1, 10] myConstrainedInt;")
                 .add_system_decl("double myDouble;")
                 .add_system_decl("clock myClock;")
                 .add_system_decl("chan MyChannel;")
                 .build_query_fixture();

    const auto foo = f.get_errors();
    REQUIRE(f.get_errors().empty());

    SUBCASE("Support of locations")
    {

        const std::string query_string = "acontrol: A[] Process.location != Process._id0 { Process.location, myClock[2, 10]:100 }";

        auto query = f.parse_query(query_string.data()).intermediate;

        REQUIRE(query.get_kind() == UTAP::Constants::ACONTROL);
        CHECK(query_string == query.str());
    }


    SUBCASE("Correct types")
    {
        // NB: Whitespace is significant since it must match the pretty-printer.
        const std::string query_string = "acontrol: A[] myDouble < 1 "
                                         "{ "
                                         "myInt[2 + 2, 10], "
                                         "myConstrainedInt[1, 2 * 5], "
                                         "myDouble[M_PI, 21 * 100]:100 "
                                         "}";

        auto query1 = f.parse_query(query_string.data()).intermediate;

        REQUIRE(query1.get_kind() == UTAP::Constants::ACONTROL);
        CHECK(query_string == query1.str());
    }

    SUBCASE("Mixing some clocks in there")
    {
        const std::string query_string = "acontrol: A[] myClock < 10 && myClock > 0 { myClock[-1, 10]:100 }";

        auto query1 = f.parse_query(query_string.data()).intermediate;

        REQUIRE(query1.get_kind() == UTAP::Constants::ACONTROL);
        CHECK(query_string == query1.str());
    }

    SUBCASE("Invalid condition to enforce")
    {
        const auto query_string = "acontrol: A[] (-2.2) { }";
        REQUIRE_THROWS_WITH(f.parse_query(query_string).intermediate, "$Type_error");

        const auto query_string2 = "acontrol: A[] myChannel { }";
        REQUIRE_THROWS_WITH(f.parse_query(query_string2).intermediate, "$Type_error");
    }

    SUBCASE("Invalid number of divisions")
    {
        const auto query_string = "acontrol: A[] myDouble < 1 {  myDouble[M_PI, 21 * 100]:1.5 }";
        REQUIRE_THROWS_WITH(f.parse_query(query_string), "$syntax_error: $unexpected T_FLOATING, $expecting T_NAT");

        // Don't know why it still says "T_FLOATING" here.
        const auto query_string2 = "acontrol: A[] myDouble < 1 { myDouble[M_PI, 21 * 100]:myChannel }";
        REQUIRE_THROWS_WITH(f.parse_query(query_string2), "$syntax_error: $unexpected T_FLOATING, $expecting T_NAT");

        const auto query_string3 = "acontrol: A[] myDouble < 1 { myDouble[M_PI, 21 * 100]:myClock }";
        REQUIRE_THROWS_WITH(f.parse_query(query_string3), "$syntax_error: $unexpected T_FLOATING, $expecting T_NAT");
    }
}