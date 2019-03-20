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

#ifndef UTAP_ABSTRACTBUILDER_HH
#define UTAP_ABSTRACTBUILDER_HH

#include <stdexcept>

#include "utap/builder.h"
#include "utap/utap.h"

namespace UTAP
{
    class NotSupportedException : public std::logic_error
    {
    public:
	NotSupportedException(const char *msg) : std::logic_error(msg) {}

    };

    class AbstractBuilder : public ParserBuilder
    {
    protected:
	/* A pointer to the error handler */
	ErrorHandler *errorHandler;

	position_t position;
    public:
        AbstractBuilder();

	virtual void setErrorHandler(ErrorHandler *);
	virtual void setPosition(const position_t &);

	/************************************************************
	 * Query functions
	 */
	virtual bool isType(const char*);
	virtual bool isLocation(const char*);

	/************************************************************
	 * Types
	 */
	virtual void typeName(int32_t prefix, const char* name, int range);
	// 2 expr if range==true
	virtual void typeStruct(int32_t prefix, uint32_t fields);

	virtual void structField(const char* name, uint32_t dim); 
	// 1 type and dim array sizes
	virtual void structFieldEnd();

	virtual void declTypeDef(const char* name, uint32_t dim); 
	// 1 type and dim array sizes
	virtual void declTypeDefEnd();

	/************************************************************
	 * Variable declarations
	 */
	virtual void declVar(const char* name, uint32_t dim, bool init); 
	// 1 type, dims, initializer if init==true
	virtual void declVarEnd();
	virtual void declInitialiserList(uint32_t num); // n initialisers
	virtual void declFieldInit(const char* name); // 1 initialiser

	/************************************************************
	 * Progress measure declarations
	 */
	virtual void declProgress(bool);
	
	/************************************************************
	 * Function declarations
	 */
	virtual void declParameter(const char* name, bool reference, uint32_t dim);
	// 1 type, dim array sizes
	virtual void declParameterEnd(); // pop parameter type
    
	virtual void declFuncBegin(const char* name, uint32_t n); // n paramaters
	virtual void declFuncEnd(); // 1 block

	/************************************************************
	 * Process declarations
	 */
	virtual void procBegin(const char* name, uint32_t n); // n parameters
	virtual void procEnd(); // 1 ProcBody
	virtual void procState(const char* name, bool hasInvariant); // 1 expr
	virtual void procStateCommit(const char* name); // mark previously decl. state
	virtual void procStateUrgent(const char* name); // mark previously decl. state
	virtual void procStateInit(const char* name); // mark previously decl. state
	virtual void procEdge(const char* from, const char* to); 
	// 1 epxr,1sync,1expr
	virtual void procGuard();
	virtual void procSync(Constants::synchronisation_t type); // 1 expr
	virtual void procUpdate();
    
	/************************************************************
	 * Statements
	 */
	virtual void blockBegin();
	virtual void blockEnd();
	virtual void emptyStatement();
	virtual void forBegin();
	virtual void forEnd(); // 3 expr, 1 stat
	virtual void whileBegin();
	virtual void whileEnd(); // 1 expr, 1 stat
	virtual void doWhileBegin();
	virtual void doWhileEnd(); // 1 stat, 1 expr
	virtual void ifBegin();
	virtual void ifElse();
	virtual void ifEnd(bool); // 1 expr, 1 or 2 statements
	virtual void breakStatement();
	virtual void continueStatement();
	virtual void switchBegin();
	virtual void switchEnd(); // 1 expr, 1+ case/default
	virtual void caseBegin();
	virtual void caseEnd();  // 1 expr, 0+ stat
	virtual void defaultBegin();
	virtual void defaultEnd(); // 0+ statements
	virtual void exprStatement(); // 1 expr
	virtual void returnStatement(bool); // 1 expr if argument is true
    
	/************************************************************
	 * Expressions
	 */
	virtual void exprTrue();
	virtual void exprFalse();
	virtual void exprId(const char * varName);
	virtual void exprNat(int32_t); // natural number
	virtual void exprCallBegin(const char * functionName);
	virtual void exprCallEnd(uint32_t n); // n exprs as arguments
	virtual void exprArg(uint32_t n); // 1 exprs as n-th argument for fn-call
	virtual void exprArray(); // 2 expr 
	virtual void exprPostIncrement(); // 1 expr
	virtual void exprPreIncrement(); // 1 expr
	virtual void exprPostDecrement(); // 1 expr
	virtual void exprPreDecrement(); // 1 expr
	virtual void exprAssignment(Constants::kind_t op); // 2 expr
	virtual void exprUnary(Constants::kind_t unaryop); // 1 expr
	virtual void exprBinary(Constants::kind_t binaryop); // 2 expr
	virtual void exprInlineIf(); // 3 expr
	virtual void exprComma(); // 2 expr
	virtual void exprDot(const char *); // 1 expr
	virtual void exprDeadlock();
    
	/************************************************************
	 * System declaration
	 */
	virtual void instantiationBegin(const char*, const char*);
	virtual void instantiationEnd(const char *, const char *, uint32_t n); // n arguments
	virtual void process(const char*);

	virtual void done();    

	virtual void property(Constants::kind_t, int line);

	/********************************************************************
	 * Guiding
	 */

	virtual void beforeUpdate();
	virtual void afterUpdate();


	/********************************************************************
	 * Priority
	 */

	virtual void lowPriority(const char*);
	virtual void samePriority(const char*);
	virtual void higherPriority(const char*);
    };
}
#endif
