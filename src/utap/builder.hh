// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; -*-

/* libutap - Uppaal Timed Automata Parser.
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

#ifndef UTAP_BUILDER_HH
#define UTAP_BUILDER_HH

#include <cstdio>
#include <iostream>
#include <exception>

#include "utap/common.hh"

namespace UTAP
{
    /**
     * Exception indicating a type error. This is thrown by
     * implementations of the ParserBuilder interface to indicate that
     * a type error has occurred.
     */
    class TypeException : public std::exception 
    {
    private:
	char _what[256];
    public:
	TypeException(const char *fmt, ...);
	const char *what() const throw ();
    };

    std::ostream& operator <<(std::ostream& out, const TypeException& exc);

    /**
     * The ParserBuilder interface is used by the parser to output the
     * parsed system. The parser itself will only parse the system -
     * it will not actually store or otherwise process the
     * input. Instead, the parser is configured with an implementation
     * of the ParserBuilder interface. Productions in the BNF
     * implemented by the parser correspond to methods in the
     * ParserBuilder interface.
     * 
     * Errors (such as type errors) can be reported back to the parser
     * by either throwing a TypeException or by calling an error
     * method in the ErrorHandler that has been set by a call to
     * setErrorHandler().
     *
     * <h3>Expressions</h3>
     *
     * Expressions are reported in reverse polish notation using the
     * exprXXX methods.
     *
     * <h3>Declarations</h3>
     *
     * The proper protocol for declaring a new type name is to
     *
     * - report the type using the typeXXX methods
     * - report dim expressions indicating the array sizes
     * - call declTypeDef(name, dim) to declare the type-name
     * - Repeat item 2 & 3 for all type names
     * - call declTypeDefEnd() 
     *
     * The proper protocol for declaring a variable is to
     *
     * - report the type using the typeXXX methods
     * - report dim expressions indicating the array sizes
     * - optionally report an expression for the initialiser
     * - call declVar(name, dim, init), where init is true if and
     *   only if an initialiser has been reported
     * - repeat item 2, 3 & 4 for each variable
     * - call declVarEnd()
     */
    class ParserBuilder
    {
    public:
	/*********************************************************************
	 * Prefixes
	 */
	static const int32_t PREFIX_NONE = 0;
	static const int32_t PREFIX_CONST = 1;
	static const int32_t PREFIX_URGENT = 2;
	static const int32_t PREFIX_BROADCAST = 4;
	static const int32_t PREFIX_URGENT_BROADCAST = 
	PREFIX_URGENT | PREFIX_BROADCAST;

	virtual ~ParserBuilder() {}

	/**
	 * Set the error handler to the given handler. Errors are
	 * reported by calling this handler or by throwing a
	 * TypeException.
	 */
	virtual void setErrorHandler(ErrorHandler *) = 0;

	/**
	 * Sets the current position. The current position indicates
	 * where in the input file the current productions can be
	 * found.
	 */
	virtual void setPosition(const position_t &) = 0;
    
	/**
	 * Must return true if and only if name is registered in the
	 * symbol table as a named type, for instance, "int" or "bool" or
	 * a user defined type.
	 */
	virtual bool isType(const char*) = 0;

	/**
	 * Called when a type name has been parsed. Prefix indicates
	 * whether the type named was prefixed (e.g. with
	 * 'const'). The range argument indicates whether a range was
	 * given for the type (in that case two expressions were
	 * reported using the exprXXX methods).
	 */
	virtual void typeName(int32_t prefix, const char* name, bool range) = 0;

	/**
	 * Called when a struct-type has been parsed. Prior to the
	 * call 'fields' fields must have been declared using the
	 * structXXX methods.
	 */
	virtual void typeStruct(int32_t prefix, uint32_t fields) = 0;

	/**
	 * Called to declare a field of a structure. The type of the
	 * field has been reported using a typeXXX method prior to the
	 * call of structField(). In case of array fields, 'dim'
	 * expressions indicating the array sizes have been reported.
	 */
	virtual void structField(const char* name, uint32_t dim) = 0; 

	/** 
	 * Called at the end of a series of field declarations of the
	 * same type.
	 */
	virtual void structFieldEnd() = 0;

	/** 
	 * Used when a typedef declaration was parsed. name is the
	 * name of the new type, and dim is the dimension of array
	 * types.
	 */
	virtual void declTypeDef(const char* name, uint32_t dim) = 0; 

	/**
	 * Called at the end of a series of type name declarations of
	 * the same type.
	 */
	virtual void declTypeDefEnd() = 0;

	/**
	 * Called to when a variable declaration has been parsed. 
	 */
	virtual void declVar(const char* name, uint32_t dim, bool init) = 0; 

	/**
 	 * Called at the end of a series of variable declarations of
	 * the same type.
	 */
	virtual void declVarEnd() = 0;
	virtual void declInitialiserList(uint32_t num) = 0; // n initialisers
	virtual void declFieldInit(const char* name) = 0; // 1 initialiser
  
	/********************************************************************
	 * Function declarations
	 */
	virtual void declParameter(const char* name, bool reference, uint32_t dim) = 0;
	// 1 type, dim array sizes
	virtual void declParameterEnd() = 0; // pop parameter type
  
	virtual void declFuncBegin(const char* name, uint32_t n) = 0; // n paramaters
	virtual void declFuncEnd() = 0; // 1 block

	/********************************************************************
	 * Process declarations
	 */
	virtual void procBegin(const char* name, uint32_t n) = 0; // n parameters
	virtual void procEnd() = 0; // 1 ProcBody
	virtual void procState(const char* name, bool hasInvariant) = 0; // 1 expr
	virtual void procStateCommit(const char* name) = 0; // mark previously decl. state
	virtual void procStateUrgent(const char* name) = 0; // mark previously decl. state
	virtual void procStateInit(const char* name) = 0; // mark previously decl. state
	virtual void procTransition(const char* from, const char* to) = 0; 
	virtual void procGuard() = 0; // 1 expr
	virtual void procSync(Constants::synchronisation_t type) = 0; // 1 expr
	virtual void procUpdate() = 0; // 1 expr

	/*********************************************************************
	 * Statements
	 */
	virtual void blockBegin() = 0;
	virtual void blockEnd() = 0;
	virtual void emptyStatement() = 0;
	virtual void forBegin() = 0;
	virtual void forEnd() = 0; // 3 expr, 1 stat
	virtual void whileBegin() = 0;
	virtual void whileEnd() = 0; // 1 expr, 1 stat
	virtual void doWhileBegin() = 0;
	virtual void doWhileEnd() = 0; // 1 stat, 1 expr
	virtual void ifBegin() = 0;
	virtual void ifElse() = 0;
	virtual void ifEnd(bool) = 0; // 1 expr, 1 or 2 statements
	virtual void breakStatement() = 0;
	virtual void continueStatement() = 0;
	virtual void switchBegin() = 0;
	virtual void switchEnd() = 0; // 1 expr, 1+ case/default
	virtual void caseBegin() = 0;
	virtual void caseEnd() = 0;  // 1 expr, 0+ stat
	virtual void defaultBegin() = 0;
	virtual void defaultEnd() = 0; // 0+ statements
	virtual void exprStatement() = 0; // 1 expr
	virtual void returnStatement(bool) = 0; // 1 expr if argument is true

	/********************************************************************
	 * Expressions
	 */
	virtual void exprFalse() = 0;
	virtual void exprTrue() = 0;
	virtual void exprId(const char * varName) = 0;
	virtual void exprNat(int32_t) = 0; // natural number
	virtual void exprCallBegin(const char * functionName) = 0;
	virtual void exprCallEnd(uint32_t n) = 0; // n exprs as arguments
	virtual void exprArg(uint32_t n) = 0; // 1 expr for n-th fn call argument
	virtual void exprArray() = 0; // 2 expr 
	virtual void exprPostIncrement() = 0; // 1 expr
	virtual void exprPreIncrement() = 0; // 1 expr
	virtual void exprPostDecrement() = 0; // 1 expr
	virtual void exprPreDecrement() = 0; // 1 expr
	virtual void exprAssignment(Constants::kind_t op) = 0; // 2 expr
	virtual void exprUnary(Constants::kind_t unaryop) = 0; // 1 expr
	virtual void exprBinary(Constants::kind_t binaryop) = 0; // 2 expr
	virtual void exprInlineIf() = 0; // 3 expr
	virtual void exprComma() = 0; // 2 expr
	virtual void exprDot(const char *) = 0; // 1 expr
	virtual void exprDeadlock() = 0;

	/********************************************************************
	 * System declaration
	 */
	virtual void instantiationBegin(const char* id, const char* templ) = 0;
	virtual void instantiationEnd(const char* id, const char* templ, uint32_t n) = 0; // n arguments
	virtual void process(const char*) = 0;
	virtual void done() = 0; // marks the end of the file

	/********************************************************************
	 * Properties
	 */
	virtual void quit() {}
	virtual void property(Constants::kind_t kind, int line) {}

	/********************************************************************
	 * Guiding
	 */
	virtual void beforeUpdate() = 0;
	virtual void afterUpdate() = 0;
    };
}
    
/**
 * Parse a file in the XTA format, reporting the system to the given
 * implementation of the the ParserBuilder interface and reporting
 * errors to the ErrorHandler. If newxta is true, then the 4.x syntax
 * is used; otherwise the 3.x syntax is used. On success, this
 * function returns with a positive value.
 */
int32_t parseXTA(FILE *, UTAP::ParserBuilder *, UTAP::ErrorHandler *,
		 bool newxta);

/**
 * Parse a buffer in the XTA format, reporting the system to the given
 * implementation of the the ParserBuilder interface and reporting
 * errors to the ErrorHandler. If newxta is true, then the 4.x syntax
 * is used; otherwise the 3.x syntax is used. On success, this
 * function returns with a positive value.
 */
int32_t parseXTA(const char*, UTAP::ParserBuilder *, UTAP::ErrorHandler *,
		 bool newxta);

/**
 * Parse a buffer in the XML format, reporting the system to the given
 * implementation of the the ParserBuilder interface and reporting
 * errors to the ErrorHandler. If newxta is true, then the 4.x syntax
 * is used; otherwise the 3.x syntax is used. On success, this
 * function returns with a positive value.
 */
int32_t parseXMLBuffer(const char *buffer, UTAP::ParserBuilder *,
		       UTAP::ErrorHandler *, bool newxta);

/**
 * Parse the file with the given name assuming it is in the XML
 * format, reporting the system to the given implementation of the the
 * ParserBuilder interface and reporting errors to the
 * ErrorHandler. If newxta is true, then the 4.x syntax is used;
 * otherwise the 3.x syntax is used. On success, this function returns
 * with a positive value.
 */
int32_t parseXMLFile(const char *filename, UTAP::ParserBuilder *,
		     UTAP::ErrorHandler *, bool newxta);

/**
 * Parse properties from a buffer. The properties are reported using
 * the given ParserBuilder and errors are reported using the
 * ErrorHandler.
 */
int32_t parseProperty(const char *str,
		      UTAP::ParserBuilder *aParserBuilder, 
		      UTAP::ErrorHandler *);

/**
 * Parse properties from a file. The properties are reported using the
 * given ParserBuilder and errors are reported using the ErrorHandler.
 */
int32_t parseProperty(FILE *, UTAP::ParserBuilder *aParserBuilder,
		      UTAP::ErrorHandler *);


#endif
