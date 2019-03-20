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

#ifndef UTAP_COMMON_HH
#define UTAP_COMMON_HH

#ifdef __MINGW32__
#include <stdint.h>
#else
#include <inttypes.h>
#endif
#include <string>
#include <iostream>
#include <vector>

namespace UTAP
{
    class XPath
    {
    public:
	virtual char *get() const = 0;
    };
    
    class ErrorHandler
    {
    public:
	struct error_t
	{
	    int32_t fline, fcolumn, lline, lcolumn;

	    char* xpath;
	    char* msg;

	    error_t(int32_t fl, int32_t fc, int32_t ll, int32_t lc)
		: fline(fl), fcolumn(fc), lline(ll), lcolumn(lc), 
		  xpath(NULL), msg(NULL){}

	    error_t(const error_t &err)
		: fline(err.fline), fcolumn(err.fcolumn),
		  lline(err.lline), lcolumn(err.lcolumn),
		  xpath(copy(err.xpath)), msg(copy(err.msg)) {}

	    ~error_t() { delete [] xpath; delete[] msg; }

	    char *copy(const char *s) {
		return (s ? strcpy(new char[strlen(s) + 1], s) : NULL);
	    }
	    
	    void setPath(char *path) {
		delete[] xpath;
		xpath = path;
	    };

	    void setMessage(const char *value) {
		delete[] msg;
		msg = copy(value);
	    }
	};
    private:
	std::vector<error_t> errors;
	std::vector<error_t> warnings;
	const XPath *currentPath;
	int first_line, first_column, last_line, last_column;
    public:
	ErrorHandler();

	// Sets the call back object for the current patch.
	// Clears the current position.
	void setCurrentPath(const XPath *path);

	// Sets the current position of the parser. Any errors or
	// warnings will be assumed to be at this position.
	void setCurrentPosition(int first_line, int first_column, int last_line, int last_column);

	// Called when an error is detected
	void handleError(const char *);

	// Called when a warning is issued
	void handleWarning(const char *);

	// Returns the errors
	const std::vector<error_t> &getErrors() const;

	// Returns the warnings
	const std::vector<error_t> &getWarnings() const;

	// True if there are one or more errors
	bool hasErrors() const;

	// True if there are one or more warnings
	bool hasWarnings() const;

	// Clears the list of errors and warnings
	void clear();
    };

    namespace Constants
    {
	enum kind_t {
	    PLUS = 0,
	    MINUS = 1,
	    MULT = 2,
	    DIV = 3,
	    MOD = 4,
	    BIT_AND = 5,
	    BIT_OR = 6,
	    BIT_XOR = 7,
	    BIT_LSHIFT = 8,
	    BIT_RSHIFT = 9,
	    AND = 10,
	    OR = 11,
	    MIN = 12,
	    MAX = 13,

	    /********************************************************
	     * Relational operators
	     */
	    LT = 20,
	    LE = 21,
	    EQ = 22,
	    NEQ = 23,
	    GE = 24,
	    GT = 25,

	    /********************************************************
	     * Unary operators
	     */
	    NOT = 30,

	    /********************************************************
	     * Assignment operators
	     */
	    ASSIGN = 40,
	    ASSPLUS = 41,
	    ASSMINUS = 42,
	    ASSDIV = 43,
	    ASSMOD = 44,
	    ASSMULT = 45,
	    ASSAND = 46,
	    ASSOR = 47,
	    ASSXOR = 48,
	    ASSLSHIFT = 49,
	    ASSRSHIFT = 50,

	    /*******************************************************
	     * CTL Quantifiers
	     */
	    EF = 60,
	    EG = 61,
	    AF = 62,
	    AG = 63,
	    LEADSTO = 64,

	    /*******************************************************
	     * Additional constants used by ExpressionProgram's and
	     * the TypeCheckBuilder (but not by the parser, although
	     * some of then ought to be used, FIXME).
	     */
	    IDENTIFIER = 512,
	    CONSTANT = 513,
	    ARRAY = 514,
	    POSTINCREMENT = 515,
	    PREINCREMENT = 516,
	    POSTDECREMENT = 517,
	    PREDECREMENT = 518,
	    UNARY_MINUS = 519,
	    LIST = 520,
	    DOT = 521,
	    INLINEIF = 522,
	    COMMA = 523,
	    CONSTRAINT = 524,
	    SYNC = 525,
	    DEADLOCK = 526,
	    FUNCALL = 527
	};

	/**********************************************************
	 * Synchronisations:
	 */
	enum synchronisation_t {
	    SYNC_QUE = 0,
	    SYNC_BANG = 1,
	    SYNC_TAU = 2
	};
    }
}

std::ostream &operator <<(std::ostream &out, const UTAP::ErrorHandler::error_t &e);

#endif
