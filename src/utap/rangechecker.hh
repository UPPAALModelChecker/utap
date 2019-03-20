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
#include "utap/system.hh"
#include "utap/common.hh"

namespace UTAP
{
    /** A visitor which performs range checking. Warnings and errors
	are produced if assignments or array indices are out of
	range. */
    class RangeChecker : public ContextVisitor
    {
    public:
	class UndefinedRangeException : public std::exception {
	public:
	    const char *what() const throw() {
		return "UndefinedRangeException"; 
	    }
	};
    private:
	std::map<int, range_t> ranges;
	ErrorHandler *errorHandler;
    protected:
	range_t getRange(symbol_t symbol) const;
	range_t rangeOfBinary(SubExpression, uint32_t op, SubExpression) const;
	void checkRange(SubExpression expr);
	
    public:    
	RangeChecker(ErrorHandler *);
	RangeChecker(ErrorHandler *, process_t &);
	
	range_t getRange(SubExpression) const;
	static range_t getDeclaredRange(SubExpression expr);

	virtual void visitState(state_t &);
	virtual void visitTransition(transition_t &);
    };
}

#endif
