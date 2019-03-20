// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2002 Uppsala University and Aalborg University.
   
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

#include <cstdio>

#include "utap/common.hh"
#include "utap/symbols.hh"
#include "utap/expression.hh"
#include "utap/system.hh"
#include "utap/statement.hh"

/*********************************************************************
 * Parse system definition.
 * Returns an intermediate system.
 */
bool parseXTA(FILE *, UTAP::ErrorHandler *, UTAP::TimedAutomataSystem *, bool newxta);
bool parseXTA(const char *, UTAP::ErrorHandler *, UTAP::TimedAutomataSystem *, bool newxta);
bool parseXMLBuffer(const char *, UTAP::ErrorHandler *, UTAP::TimedAutomataSystem *, bool newxta);
bool parseXMLFile(const char *, UTAP::ErrorHandler *, UTAP::TimedAutomataSystem *, bool newxta);

#endif
