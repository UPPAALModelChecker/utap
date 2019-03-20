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

#include <vector>
#include "utap/utap.h"

using UTAP::TimedAutomataSystem;
using UTAP::ErrorHandler;
using std::endl;
using std::cout;
using std::cerr;
using std::vector;

int main(int argc, char *argv[])
{
    bool old = false;
  
    if (argc < 2 || argc > 3)
    {
	std::cerr << "Synopsis: check [-b] <filename>" << std::endl;
	exit(1);
    }

    old = (strcmp(argv[1], "-b") == 0);

    TimedAutomataSystem system;
    ErrorHandler handler;
    const char *name = argv[argc - 1];

    if (strlen(name) > 4 && strcasecmp(".xml", name + strlen(name) - 4) == 0) 
    {
	parseXMLFile(name, &handler, &system, !old);
    }
    else 
    {
	FILE *file = fopen(name, "r");
	if (!file) 
	{
	   perror("check");
           exit(1);
	}
	parseXTA(file, &handler, &system, !old);
	fclose(file);
    } 

    vector<ErrorHandler::error_t>::const_iterator it;
    const vector<ErrorHandler::error_t> &errors = handler.getErrors();
    const vector<ErrorHandler::error_t> &warns = handler.getWarnings();

    for (it = errors.begin(); it != errors.end(); it++)
    {
   	cerr << *it << endl;
    }
    for (it = warns.begin(); it != warns.end(); it++)
    {
   	cerr << *it << endl;
    }

    return 0;
}













