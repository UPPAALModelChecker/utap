// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2002-2004 Uppsala University and Aalborg University.
   
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

#ifndef UTAP_SYSTEMBUILDER_H
#define UTAP_SYSTEMBUILDER_H

#include <cassert>
#include <vector>
#include <inttypes.h>

#include "utap/expressionbuilder.h"
#include "utap/utap.h"

namespace UTAP
{
    /**
     * This class constructs a TimedAutomataSystem. It categorizes
     * declarations into clocks, constants, channels, functions,
     * processes, variables, type names, states and templates.
     *
     * It knows about arrays and structures. It does resolve the scope
     * of identifiers. It knows about named types.
     *
     * It checks that
     *  - states are not both committed and urgent 
     *  - the source and target of a edge is a state
     *  - the array operator is applied to an array
     *  - the dot operator is applied to a process or a structure.
     *  - functions are not recursive
     *  - only declared functions are called
     *  - functions are called with the correct number of arguments
     *  - the initial state of a template is actually declared as a state
     *  - templates in instantiations have been declared
     *  - identifiers are not declared twice in the same scope
     *  - type names do exist and are declared as types
     *  - processes in the system line have been declared
     *
     * It does not
     *  - compute or check the range of integers and integer expressions
     *  - check the correctness of variable initialisers, nor
     *    does it complete variable initialisers
     *  - type check expressions
     *  - check if arguments to functions or template match the
     *    formal parameters
     *  - check if something is a proper left hand side value
     *  - check if things are assignment compatible
     *  - check conflicting use of synchronisations and guards on edge
     *  - handle properties
     */
    class SystemBuilder : public ExpressionBuilder
    {
    protected:
	// Error message for unsupported features
	static const char *const unsupported;
	static const char *const invalid_type;

	/* Flag used to determine how strict we check for inclusion 
	   between ranges of integers. TODO: Replace this with a
	   system, which reports a warning if there is a potential
	   overflow. */
	bool strict_range;

	/* The current priority level, used when declaring process or
	 * channel priorities.
	 */
	int32_t currentPriority;
    private:


	// 
	// Support for handling template and function parameters
	//

	/* The templateset frame is used during template set declaration */
	frame_t templateset;

	/* The params frame is used temporarily during parameter parsing */
	frame_t params;

	/* current parsing function structure */
	function_t *currentFun;

	template_t *currentTemplate;

	edge_t *currentEdge;

	/* stack of function body statement blocks */
	std::vector<BlockStatement*> blocks; 

	//
	// Method for handling types
	//

	type_t buildArrayType(type_t type, uint32_t dim);
	type_t getElementTypeOfArray(type_t type);
	declarations_t *getCurrentDeclarationBlock();

    public:

	SystemBuilder(TimedAutomataSystem *);

	/************************************************************
	 * Types
	 */
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
	 * Guarded progress measure
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
	virtual void procTemplateSet(const char *name);
	virtual void procBegin(const char* name, uint32_t n, uint32_t m);
	virtual void procEnd(); // 1 ProcBody
	virtual void procState(const char* name, bool hasInvariant); // 1 expr
	virtual void procStateCommit(const char* name); // mark previously decl. state
	virtual void procStateUrgent(const char* name); // mark previously decl. state
	virtual void procStateWinning(const char* name); // mark previously decl. state
	virtual void procStateLosing(const char* name); // mark previously decl. state
	virtual void procStateInit(const char* name); // mark previously decl. state
        virtual void procEdgeBegin(const char* from, const char* to, const bool control);
	virtual void procEdgeEnd(const char* from, const char* to); 

	// 1 type
	virtual void procSelect(const char *id);

	// 1 epxr
	virtual void procGuard();

	// 1 expr
	virtual void procSync(Constants::synchronisation_t type); // 1 expr

	// 1 expr
	virtual void procUpdate();
    
	/************************************************************
	 * Statements
	 */
	virtual void blockBegin();
	virtual void blockEnd();
	virtual void emptyStatement();
	virtual void forBegin();
	virtual void forEnd(); // 3 expr, 1 stat
	virtual void iterationBegin(const char *name);
	virtual void iterationEnd(const char *name);
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
	virtual void exprCallBegin();
    
	/************************************************************
	 * System declaration
	 */
	virtual void instantiationBegin(const char*, const char*);
	virtual void instantiationEnd(const char *, const char *, uint32_t n); // n arguments
	virtual void process(const char*);

	virtual void done();    

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
