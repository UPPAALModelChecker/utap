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

#ifndef UTAP_BUILDER_HH
#define UTAP_BUILDER_HH

#include <cstdio>
#include <iostream>
#include <exception>

#include "utap/common.hh"

namespace UTAP
{
  class TypeException : public std::exception 
  {
  private:
    char _what[256];
  public:
    TypeException(const char *fmt, ...);
    const char *what() const throw ();
  };

  std::ostream& operator <<(std::ostream& out, const TypeException& exc);

  class ParserBuilder
  {
  public:
    /*********************************************************************
     * Prefixes
     */
    static const uint32_t PREFIX_NONE = 0;
    static const uint32_t PREFIX_CONST = 1;
    static const uint32_t PREFIX_URGENT = 2;
    static const uint32_t PREFIX_BROADCAST = 4;
    static const uint32_t PREFIX_URGENT_BROADCAST = 
    PREFIX_URGENT | PREFIX_BROADCAST;

    virtual ~ParserBuilder() {}

    virtual void setErrorHandler(ErrorHandler *) = 0;
    virtual void setPosition(const position_t &) = 0;
    
    /********************************************************************
     * Query functions
     */
    virtual bool isType(const char*) = 0;

    /********************************************************************
     * Types
     */
    virtual void declType(uint32_t prefix, const char* name, bool range) = 0;
    // 2 expr if range==true
    virtual void declStruct(uint32_t prefix, uint32_t fields) = 0;
    virtual void declField(const char* name, uint32_t dim) = 0; 
    // 1 type and dim array sizes
    virtual void declFieldEnd() = 0;
    virtual void declTypeDef(const char* name, uint32_t dim) = 0; 
    // 1 type and dim array sizes
    virtual void declTypeDefEnd() = 0;

    /********************************************************************
     * Variable declarations
     */
    virtual void declVar(const char* name, uint32_t dim, bool init) = 0; 
    // 1 type, dims, initializer if init==true
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

/*************************************************************************
 * Parse system definition.
 * Returns >=0 (success, ended with data specific code). 
 * Returns -1 (failure). 
 */
int32_t parseXTA(FILE *, UTAP::ParserBuilder *, UTAP::ErrorHandler *,
		 bool newxta);
int32_t parseXTA(const char*, UTAP::ParserBuilder *, UTAP::ErrorHandler *,
		 bool newxta);
int32_t parseXMLBuffer(const char *buffer, UTAP::ParserBuilder *,
		       UTAP::ErrorHandler *, bool newxta);
int32_t parseXMLFile(const char *filename, UTAP::ParserBuilder *,
		     UTAP::ErrorHandler *, bool newxta);
int32_t parseProperty(const char *str,
		      UTAP::ParserBuilder *aParserBuilder, 
		      UTAP::ErrorHandler *);
int32_t parseProperty(FILE *, UTAP::ParserBuilder *aParserBuilder,
		      UTAP::ErrorHandler *);

#endif
