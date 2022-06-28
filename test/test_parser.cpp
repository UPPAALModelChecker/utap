// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-
///////////////////////////////////////////////////////////////////////////////
//
// This file is a part of UPPAAL.
// Copyright (c) 2021, Aalborg University.
// All right reserved.
//
///////////////////////////////////////////////////////////////////////////////

/**
 * File:   test_parser.cpp
 * Author: Rasmus R. Kjær
 *
 * Created on 20 August 2021, 09:47
 */

#include "utap/utap.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <fstream>

#include <doctest/doctest.h>

// Copied from SystemLoader.h. If we dependen on testutils, we would
// also have to depend on the verifier, which seems impure.

inline std::string read_content(const std::string& dir_path, const std::string& file_name)
{
    const std::string filename = dir_path + '/' + file_name;
    std::ifstream ifs(filename);
    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    return content;
}

TEST_CASE("Double Serialization Test")
{
    auto document = std::make_unique<UTAP::Document>();
    auto content = read_content(SYSTEMS_DIR, "ifstatement.xml");
    parseXMLBuffer(content.c_str(), document.get(), true);
}

TEST_CASE("Power expressions")
{
    auto document = std::make_unique<UTAP::Document>();
    auto content = read_content(SYSTEMS_DIR, "powers.xml");
    parseXMLBuffer(content.c_str(), document.get(), true);
}
