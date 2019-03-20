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

#ifndef UTAP_SYSTEMBUILDER_HH
#define UTAP_SYSTEMBUILDER_HH

#include <cassert>
#include <vector>
#include <inttypes.h>

#include "utap/builder.hh"
#include "utap/utap.hh"

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
     *  - the source and target of a transition is a state
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
     *  - check conflicting use of synchronisations and guards on transitions
     *
     *
     * Property expressions are constructed, but the SystemBuilder
     * class must be subtyped in order actually get access to the
     * properties as they are not stored otherwise.
     */
    class SystemBuilder : public ParserBuilder
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

	/* Pointer to the intermediate system under construction */
	TimedAutomataSystem *system;

	/* A pointer to the error handler */
	ErrorHandler *errorHandler;

	position_t position;
	
    private:
	//
	// The stack of expression fragments.
	//
	class ExpressionFragments 
	{
	private:
	    std::vector<expression_t> data;
	public:
	    expression_t &operator[] (int idx)
		{ return data[data.size() - idx - 1]; }
	    void push(expression_t e)
		{ data.push_back(e); }
	    void pop()
		{ data.pop_back(); }
	    void pop(int n);
	    uint32_t size() { return data.size(); }
	} fragments;

	//
	// The stack of type fragments. A type fragment is a pair
	// consiting of a type and an optional name (the name is 
	// used for fields of a structure).
	//
	class TypeFragments 
	{
	private:
	    std::vector<std::pair<type_t, char *> > data;
	public:
	    ~TypeFragments() 
                { while (!data.empty()) pop(); }
	    std::pair<type_t, char *> &operator[] (int idx)
		{ return data[data.size() - idx - 1]; }
	    void push(type_t value)
		{ data.push_back(std::make_pair(value, (char*)NULL)); }
	    void pop()
		{ assert(!data.empty()); free(data.back().second); data.pop_back(); }
	} typeFragments;

	// 
	// Support for handling template and function parameters
	//

	/* The params vector is used temporarily during parameter parsing */
	frame_t params;

	/* Current frame */
	frame_t frame;

	/* current parsing function structure */
	function_t *currentFun;

	/* stack of function body statement blocks */
	std::vector<BlockStatement*> blocks; 

	//
	// Fields for handling transition labels
	//
	int32_t guard;
	int32_t sync;
	int32_t update;

	//
	// Fields for function call and template instantiation handling
	//
	
	/* list of expected arguments */
	std::list<std::vector<type_t> > expectedArguments;

        /* stack of function or template symbols */
	std::vector<symbol_t> identifierStack;

	//
	// Method for handling types
	//

	type_t buildArrayType(type_t type, uint32_t dim);
	type_t getElementTypeOfArray(type_t type);
	type_t applyPrefix(uint32_t prefix, type_t type);

	//
	// Methods for handling expressions
	//

	expression_t makeConstant(int value);

    protected:

	///////////////////////////////////////////////////////////////////
	// allowProcessReferences()
	///////////////////////////////////////////////////////////////////
	// If this method returns true, it is allowed to access the 
	// private identifiers of a process by prefixing the identifier
	// with the process name. 
	//
	// This is only interesting when parsing properties. In this case
	// the method should be overridden by a sub class.
	virtual bool allowProcessReferences() { return false; }

	//////////////////////////////////////////////////////////////
	// property()
	//////////////////////////////////////////////////////////////
	// This method is called once for each property, which has
	// been parsed. The default implementation does nothing, so
	// you need to override this in a subclass.
	virtual void property(Constants::kind_t, int line, expression_t) {};

    public:

	SystemBuilder(TimedAutomataSystem *);

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
	virtual void declType(uint32_t prefix, const char* name, bool range);
	// 2 expr if range==true
	virtual void declStruct(uint32_t prefix, uint32_t fields);
	virtual void declField(const char* name, uint32_t dim); 
	// 1 type and dim array sizes
	virtual void declFieldEnd();
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
	virtual void procTransition(const char* from, const char* to); 
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
    };
}
#endif
