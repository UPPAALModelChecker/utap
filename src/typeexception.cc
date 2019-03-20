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

#include <cstdarg>
#include <cstdio>

#include "utap/builder.hh"

using namespace UTAP;

using std::ostream;

TypeException::TypeException(const char *fmt, ...) {
  va_list ap;
#if defined(__MINGW32__) || defined(__CYGWIN32__)
  va_start((void *)ap, fmt);
  vsprintf(_what, fmt, ap);
#else
  va_start(ap, fmt);
  vsnprintf(_what, 256, fmt, ap);
#endif
  va_end(ap);
}
  
const char *TypeException::what() const throw () {
  return _what;
}

ostream& operator <<(ostream& out, const TypeException& exc) 
{
    out << "TypeException: " << exc.what();
    return out;
}
