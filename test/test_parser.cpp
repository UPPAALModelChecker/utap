// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-
///////////////////////////////////////////////////////////////////////////////
//
// This file is a part of UPPAAL.
// Copyright (c) 2021, Aalborg University.
// All right reserved.
//
///////////////////////////////////////////////////////////////////////////////

/*
 * File:   parsertests.cpp
 * Author: Rasmus R. Kjær
 *
 * Created on 20 August 2021, 09:47
 */

#include "utap/utap.h"

#define BOOST_TEST_MODULE utap parser
#include <boost/test/included/unit_test.hpp>

#include <fstream>

// Copied from SystemLoader.h. If we dependen on testutils, we would
// also have to depend on the verifier, which seems impure.

inline std::string read_content(const std::string& dir_path, const std::string& file_name)
{
    const std::string filename = dir_path + '/' + file_name;
    std::ifstream ifs(filename);
    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    return content;
}

BOOST_AUTO_TEST_SUITE(BasicIOTests)

BOOST_AUTO_TEST_CASE(DoubleSerializationTest)
{
    auto document = std::make_unique<UTAP::Document>();
    auto content = read_content(SYSTEMS_DIR, "ifstatement.xml");
    parseXMLBuffer(content.c_str(), document.get(), true);
}

BOOST_AUTO_TEST_SUITE_END()
