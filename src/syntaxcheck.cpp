// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-

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
#include <string.h>

using UTAP::TimedAutomataSystem;
using std::endl;
using std::cout;
using std::cerr;
using std::vector;

int main(int argc, char *argv[])
{
    try 
    {
        bool old = false;
        
        if (argc < 2 || argc > 3)
        {
            std::cerr << "Synopsis: check [-b] <filename>" << std::endl;
            return 1;
        }
        
        old = (strcmp(argv[1], "-b") == 0);
        
        TimedAutomataSystem system;
        const char *name = argv[argc - 1];
        
        if (strlen(name) > 4 && strcasecmp(".xml", name + strlen(name) - 4) == 0) 
        {
            parseXMLFile(name, &system, !old);
        }
        else 
        {
            FILE *file = fopen(name, "r");
            if (!file) 
            {
                perror("check");
                return 1;
            }
            parseXTA(file, &system, !old);
            fclose(file);
        } 
        
        vector<UTAP::error_t>::const_iterator it;
        const vector<UTAP::error_t> &errors = system.getErrors();
        const vector<UTAP::error_t> &warns = system.getWarnings();
        
        for (it = errors.begin(); it != errors.end(); it++)
        {
            cerr << *it << endl;
        }
        for (it = warns.begin(); it != warns.end(); it++)
        {
            cerr << *it << endl;
        }
        
        return errors.empty() && warns.empty() ? 0 : 2;
    }
    catch (std::exception &e)
    {
        cerr << e.what() << endl;
        return 3;
    }
}













