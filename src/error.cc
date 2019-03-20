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

#include "utap/common.hh"

using namespace UTAP;

using std::vector;
using std::ostream;

ErrorHandler::ErrorHandler()
{
  currentPath = NULL;
  first_line = first_column = last_line = last_column = -1;
}

// Sets the call back object for the current patch.
// Clears the current position.
void ErrorHandler::setCurrentPath(const XPath *path)
{
  currentPath = path;
  first_line = first_column = last_line = last_column = -1;  
}

// Sets the current position of the parser. Any errors or
// warnings will be assumed to be at this position.
void ErrorHandler::setCurrentPosition(int first_line, int first_column, int last_line, int last_column)
{
  this->first_line = first_line;
  this->first_column = first_column;
  this->last_line = last_line;
  this->last_column = last_column;
}

// Called when an error is detected
void ErrorHandler::handleError(const char *msg)
{
  errors.push_back(error_t(first_line, first_column, last_line, last_column));
  errors.back().setMessage(msg);
  if (currentPath)
    errors.back().setPath(currentPath->get());
}

// Called when a warning is issued
void ErrorHandler::handleWarning(const char *msg)
{
  warnings.push_back(error_t(first_line, first_column, last_line, last_column));
  warnings.back().setMessage(msg);
  if (currentPath)
    warnings.back().setPath(currentPath->get());
}

// Returns the errors
const vector<ErrorHandler::error_t> &ErrorHandler::getErrors() const
{
  return errors;
}

// Returns the warnings
const vector<ErrorHandler::error_t> &ErrorHandler::getWarnings() const
{
  return warnings;
}

// True if there are one or more errors
bool ErrorHandler::hasErrors() const
{
  return !errors.empty();
}

// True if there are one or more warnings
bool ErrorHandler::hasWarnings() const
{
  return !warnings.empty();
}

// Clears the list of errors and warnings
void ErrorHandler::clear()
{
  errors.clear();
  warnings.clear();
};

ostream &operator <<(ostream &out, const ErrorHandler::error_t &e) 
{
  out << e.msg << " at ";
  if (e.fline != e.lline)                      
    out << e.fline << "." << e.fcolumn << "-" 
        << e.lline << "." << (e.lcolumn-1);
  else if (e.fcolumn < e.lcolumn-1)
    out << e.fline << "." << e.fcolumn << "-" << (e.lcolumn-1);
  else                                                          
    out << e.fline << "." << e.fcolumn;
  //  out << " (" << e.fchar << "-" << e.lchar << ")";
  return out;
};

