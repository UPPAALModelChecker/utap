// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2020-2021 Aalborg University.

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

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <filesystem>
#include <fstream>

inline std::string read_content(const std::string& file_name)
{
    const auto path = std::filesystem::path{MODELS_DIR} / file_name;
    auto ifs = std::ifstream{path};
    auto content = std::string{std::istreambuf_iterator<char>{ifs}, std::istreambuf_iterator<char>{}};
    return content;
}

TEST_CASE("Simple system")
{
    auto document = std::make_unique<UTAP::Document>();
    parseXMLBuffer(read_content("simpleSystem.xml").c_str(), document.get(), true);
    UTAP::FeatureChecker checker(*document);
    CHECK(checker.getSupportedMethods().symbolic);
    CHECK(checker.getSupportedMethods().stochastic);
}

TEST_CASE("Simple SMC system")
{
    auto document = std::make_unique<UTAP::Document>();
    parseXMLBuffer(read_content("simpleSMCSystem.xml").c_str(), document.get(), true);
    UTAP::FeatureChecker checker(*document);
    CHECK(!checker.getSupportedMethods().symbolic);
    CHECK(checker.getSupportedMethods().stochastic);
}

TEST_CASE("Simple handshake system")
{
    auto document = std::make_unique<UTAP::Document>();
    parseXMLBuffer(read_content("simpleHandshakeSystem.xml").c_str(), document.get(), true);
    UTAP::FeatureChecker checker(*document);
    CHECK(checker.getSupportedMethods().symbolic);
    CHECK(!checker.getSupportedMethods().stochastic);
}

TEST_CASE("Simply dynamic system")
{
    auto document = std::make_unique<UTAP::Document>();
    parseXMLBuffer(read_content("dynamic.xml").c_str(), document.get(), true);
    UTAP::FeatureChecker checker(*document);
    CHECK(!checker.getSupportedMethods().symbolic);
    CHECK(checker.getSupportedMethods().stochastic);
}

TEST_CASE("Clock rate")
{
    auto document = std::make_unique<UTAP::Document>();
    parseXMLBuffer(read_content("clockrate2.xml").c_str(), document.get(), true);
    UTAP::FeatureChecker checker(*document);
    CHECK(!checker.getSupportedMethods().symbolic);
    CHECK(checker.getSupportedMethods().stochastic);
}

TEST_CASE("Clock rate expression")
{
    auto document = std::make_unique<UTAP::Document>();
    parseXMLBuffer(read_content("rateExpression.xml").c_str(), document.get(), true);
    UTAP::FeatureChecker checker(*document);
    CHECK(checker.getSupportedMethods().symbolic);
    CHECK(checker.getSupportedMethods().stochastic);
}

TEST_CASE("Hybrid clock rate")
{
    auto document = std::make_unique<UTAP::Document>();
    parseXMLBuffer(read_content("rateExpressionHybrid.xml").c_str(), document.get(), true);
    UTAP::FeatureChecker checker(*document);
    CHECK(checker.getSupportedMethods().symbolic);
    CHECK(checker.getSupportedMethods().stochastic);
}

TEST_CASE("Limited range clock rate")
{
    auto document = std::make_unique<UTAP::Document>();
    parseXMLBuffer(read_content("legalSymbolicRates.xml").c_str(), document.get(), true);
    UTAP::FeatureChecker checker(*document);
    CHECK(checker.getSupportedMethods().symbolic);
    CHECK(checker.getSupportedMethods().stochastic);
}

TEST_CASE("Integer Invariant")
{
    auto document = std::make_unique<UTAP::Document>();
    parseXMLBuffer(read_content("int_invariant.xml").c_str(), document.get(), true);
    UTAP::FeatureChecker checker(*document);
    CHECK(checker.getSupportedMethods().symbolic);
    CHECK(checker.getSupportedMethods().stochastic);
}

TEST_CASE("Hybrid clock update")
{
    auto document = std::make_unique<UTAP::Document>();
    parseXMLBuffer(read_content("updateHybridClock.xml").c_str(), document.get(), true);
    UTAP::FeatureChecker checker(*document);
    CHECK(checker.getSupportedMethods().symbolic);
    CHECK(checker.getSupportedMethods().stochastic);
}

TEST_CASE("Hybrid and normal clock update")
{
    auto document = std::make_unique<UTAP::Document>();
    parseXMLBuffer(read_content("updateHybridAndNormalClock.xml").c_str(), document.get(), true);
    UTAP::FeatureChecker checker(*document);
    CHECK(!checker.getSupportedMethods().symbolic);
    CHECK(checker.getSupportedMethods().stochastic);
}

TEST_CASE("Double comparision")
{
    auto document = std::make_unique<UTAP::Document>();
    parseXMLBuffer(read_content("double_compare.xml").c_str(), document.get(), true);
    UTAP::FeatureChecker checker(*document);
    CHECK(!checker.getSupportedMethods().symbolic);
    CHECK(checker.getSupportedMethods().stochastic);
}
