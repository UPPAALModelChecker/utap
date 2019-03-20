// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2003 Uppsala University and Aalborg University.
   
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

#ifndef UTAP_RANGECHECKER_HH
#define UTAP_RANGECHECKER_HH

#include <exception>
#include <map>
#include <list>
#include "utap/system.hh"
#include "utap/common.hh"

namespace UTAP
{
    class UndefinedRangeException : public std::exception {
    public:
	const char *what() const throw() {
	    return "UndefinedRangeException"; 
	}
    };

    /** A RangeChecker object is an oracle for predicting ranges of
	integer expressions and declared ranges of symbols. For both
	situations the result might depend on the process context,
	e.g. a template parameter might be used in the expression or
	might have been used in the range declaration of an integer
	variable. So in these cases it is important to provide the
	process in which the expression should be evaluated.

	For constant expressions, the actual value of the expression
	is returned. If the expression cannot be evaluated (it is not
	constant), then a range is computed based on the declared
	ranges of variables used in the expression (and on the values
	of any constants used).
    */
    class RangeChecker
    {
    private:
	TimedAutomataSystem *system;
	Interpreter interpreter;
    protected:
	range_t getRange(symbol_t symbol) const;
	range_t rangeOfBinary(expression_t, uint32_t op, expression_t) const;
//	void checkRange(expression_t expr);
	bool evaluate(expression_t expr, int32_t &value) const;

    public:    
	RangeChecker(TimedAutomataSystem *);
	RangeChecker(TimedAutomataSystem *, const process_t &);
	
	range_t getRange(expression_t) const;
	
	range_t getDeclaredRange(expression_t expr) const;
	range_t getDeclaredRange(symbol_t symbol) const;
    };
}

#endif
