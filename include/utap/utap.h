// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2010-2021 Aalborg University.
   Copyright (C) 2002-2003 Uppsala University and Aalborg University.

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

#ifndef UTAP_HH
#define UTAP_HH

#include "utap/common.h"
#include "utap/document.h"
#include "utap/expression.h"
#include "utap/statement.h"
#include "utap/symbols.h"

#include <filesystem>
#include <vector>
#include <cstdio>

bool parseXTA(FILE*, UTAP::Document*, bool newxta);
bool parseXTA(const char* buffer, UTAP::Document*, bool newxta);
int32_t parseXMLBuffer(const char* buffer, UTAP::Document*, bool newxta,
                       const std::vector<std::filesystem::path>& libpaths = {});
int32_t parseXMLFile(const char* buffer, UTAP::Document*, bool newxta,
                     const std::vector<std::filesystem::path>& libpaths = {});
int32_t parseXMLFd(int fd, UTAP::Document*, bool newxta, const std::vector<std::filesystem::path>& libpaths = {});
UTAP::expression_t parseExpression(const char* buffer, UTAP::Document*, bool);
int32_t writeXMLFile(const char* filename, UTAP::Document* doc);

/** returns a string representation of built-in types and constants (see parser.y) */
const char* utap_builtin_declarations();

#endif /* UTAP_HH */
