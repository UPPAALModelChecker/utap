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

#ifndef UTAP_TYPECHECKER_HH
#define UTAP_TYPECHECKER_HH

#include <vector>
#include <inttypes.h>

#include "utap/builder.hh"
#include "utap/utap.hh"

// The TypeChecker is a ParserBuilder, which can
//
//  a) construct an IntermediateSystem
//  b) ensure that the system is type correct
//  c) ensure that properties are type correct
// 
// It might be operated in one of two modes depending on whether
// strict ranging checking is turned on or not. If it is on,
// one might only assign use expression which are guaranteed to
// be within the range of the variable it is assigned to.
//
// Properties are checked, but the TypeChecker class must be
// subtyped in order actually get access to the properties as they are
// not stored by the type check builder.
//
// Internally, two stacks are used to keep track of fragments of 
// the system:
//
//   - Expressions are kept on the stack with 
//     expression fragments.
//   - Types are kept on the stack with type fragments.
//
// These stacks are used while building more complex expressions
// and types. Each stack is indexed from the top, i.e. the top
// element is indexed as 0.
//

namespace UTAP
{
    
    class TypeChecker : public ParserBuilder, 
			protected TimedAutomataStructures
    {
    protected:
	// Error message for unsupported features
	static const char *const unsupported;
	static const char *const invalid_type;

	// Flag used to determine how strict we check for inclusion 
	// between ranges of integers. TODO: Replace this with a
	// system, which reports a warning if there is a potential
	// overflow.
	bool strict_range;

	// Type used for booleans
	int32_t BOOL;

	// Pointerto the intermediate system under construction
	TimedAutomataSystem *system;

	// Reference to the type system in the intermediate system
	TypeSystem &types;

	// Reference to the symbol table in the intermediate system
	SymbolTable &symbols;

	ErrorHandler *errorHandler;

    private:
	//
	// The stack of expression fragments.
	//
	class ExpressionFragments 
	{
	private:
	    std::vector<ExpressionProgram> data;
	public:
	    ExpressionProgram &operator[] (int idx)
		{ return data[data.size() - idx - 1]; }
	    void push(const ExpressionProgram &e)
		{ data.push_back(e); }
	    void pop()
		{ data.pop_back(); }
	    void pop(int n);
	    void merge(uint32_t number);
	    uint32_t size() { return data.size(); }
	} fragments;

	//
	// The stack of type fragments.
	//
	class TypeFragments 
	{
	private:
	    std::vector<type_t> data;
	public:
	    type_t &operator[] (int idx)
		{ return data[data.size() - idx - 1]; }
	    void push(type_t value)
		{ data.push_back(value); }
	    void pop()
		{ data.pop_back(); }
	} typeFragments;

	// 
	// Support for handling template and function parameters
	//

	// The params vector is used temporarily during parameter parsing
	std::vector<std::pair<char*, type_t> > params; 

	// Clears the given vector of parameters by first deleting
	// the names and then emptying the vector.
	void clear_params(std::vector<std::pair<char*, type_t> > &params);

	function_t *currentFun; // current parsing function structure
	std::vector<BlockStatement*> blocks; // stack of function body statement blocks

	//
	// Fields for handling transition labels
	//
	int32_t guard;
	int32_t sync;
	int32_t update;
	
        // stack of <function id, expr type> for function call handling
	std::vector<std::pair<int32_t, int32_t> > fnCalls; 

	//
	// Private functions
	// 

	// Data structure used in recursive normalisationConstraint() 
	// method.
	struct normalisation_t
	{
	    bool first;
	    ExpressionProgram clock1, clock2, value;
	    normalisation_t() : first(true) {}
	};
	void normaliseConstraint(normalisation_t &, SubExpression, bool);
	void normaliseConstraint(ExpressionProgram &expr);

	//
	// Method for handling types
	//

	int32_t applyPrefix(uint32_t, int32_t);
	void checkClass(int32_t type, int32_t expected, const char *err);
	void checkLValue(int32_t type, const char *err);
	void checkAssignmentCompatible(int32_t lvalue, int32_t rvalue);
	void checkLocation(int32_t uid, const char *err);
	// isParameterCompatible returns static error message or NULL if ok.
	char* isParameterCompatible(int32_t argType, int32_t paramValue);
	uint32_t buildArrayType(uint32_t type, uint32_t dim);
	int32_t makeConstantIf(bool cond, int32_t type);
	int32_t makeSideEffectFreeIf(bool cond, int32_t type);
	int32_t makeReferenceIf(bool cond, int32_t type);
	bool isInteger(int32_t type);
	bool isClock(int32_t type);
	bool isDiff(int32_t type);
	bool isInvariant(int32_t type);
	bool isGuard(int32_t type);
	bool isConstraint(int32_t type);
	bool isTemporary(ExpressionProgram &expr);
	int32_t typeOfBinaryIntExpression(
	    int32_t left, uint32_t op, int32_t right);    
	uint32_t typeOfUnaryMinus(uint32_t type);
	int getArraySize(int32_t type);
	int32_t findFieldInRecord(const std::vector<std::pair<char *, int> > &, const char *);

	//
	// Methods for handling expressions
	//

	void exprBinaryInt(int left, uint32_t binaryop, int right);
	void exprBinaryNonInt(int left, uint32_t binaryop, int right);
	void checkInitialiser(int32_t type, SubExpression init, bool required);
	int32_t combineInlineTypes(int32_t t, int32_t e);
	void insertDefault(ExpressionProgram &expr,
			   ExpressionProgram::iterator pos,
			   int32_t type);
	ExpressionProgram::expression_t makeConstant(int value);    

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
	virtual void property(int kind, int line, ExpressionProgram &) {};

    public:

	TypeChecker(TimedAutomataSystem *);

	virtual void setErrorHandler(ErrorHandler *);

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
	virtual void procState(const char* name); // 1 expr
	virtual void procStateCommit(const char* name); // mark previously decl. state
	virtual void procStateUrgent(const char* name); // mark previously decl. state
	virtual void procStateInit(const char* name); // mark previously decl. state
	virtual void procTransition(const char* from, const char* to); 
	// 1 epxr,1sync,1expr
	virtual void procGuard();
	virtual void procSync(uint32_t type); // 1 expr
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
	virtual void exprAssignment(uint32_t op); // 2 expr
	virtual void exprUnary(uint32_t unaryop); // 1 expr
	virtual void exprBinary(uint32_t binaryop); // 2 expr
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

	virtual void property(uint32_t kind, int line);
    };

    class StatementSideEffectFree: public StatementVisitor 
    {
	TypeSystem &types;

    public:
	StatementSideEffectFree(TypeSystem &_types): 
	    StatementVisitor(), types(_types) { }

	~StatementSideEffectFree();
	int32_t emptyStat(EmptyStatement *stat);
	int32_t exprStat(ExprStatement *stat);
	int32_t forStat(ForStatement *stat);
	int32_t whileStat(WhileStatement *stat);
	int32_t doWhileStat(DoWhileStatement *stat);
	int32_t blockStat(BlockStatement *stat);
	int32_t switchStat(SwitchStatement *stat);
	int32_t caseStat(CaseStatement *stat);
	int32_t defaultStat(DefaultStatement *stat);
	int32_t ifStat(IfStatement *stat);
	int32_t breakStat(BreakStatement *stat);
	int32_t continueStat(ContinueStatement *stat);
	int32_t returnStat(ReturnStatement *stat);
    };

}
#endif
