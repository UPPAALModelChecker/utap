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

#ifndef UTAP_INTERMEDIATE_HH
#define UTAP_INTERMEDIATE_HH

#include <list>

#include "utap/typesys.hh"
#include "utap/symtable.hh"
#include "utap/expression.hh"
#include "utap/statement.hh"

namespace UTAP
{
    class TimedAutomataStructures
    {
    public:
	struct varbase_t {
	    int32_t uid;
	    int32_t size;
	    int32_t offset;
	    int32_t global;
	};
	
	// This struct is used to keep information about a variable
	// when added to the symbol table. A pointer to such a struct
	// is given as the data element.
	struct variable_t : public varbase_t {
	    ExpressionProgram expr; // initialiser for variable
	};

	// This struct is used to keep information about a constant
	// when added to the symbol table. A pointer to such a struct
	// is given as the data element.
	struct constant_t : public varbase_t {
	    ExpressionProgram expr; // initialiser for constant
	};

	// This struct is used to keep information about a clock when
	// added to the symbol table. A pointer to such a struct is
	// given as the data element.
	struct clock_t : public varbase_t {};

	// This struct is used to keep information about a channel
	// when added to the symbol table. A pointer to such a struct
	// is given as the data element.
	struct channel_t : public varbase_t {};

	// A state is stored using the uid of the symbol, the
	// invariant (an expression) and a locNr indication which nr
	// state it is for the template it if contained in
	struct state_t {
	    int32_t uid;
	    ExpressionProgram invariant;
	    int32_t locNr;
	};

	// Transitions have a source (src) and a destination (dst),
	// which are actually the uid of the symbols in the symbol
	// table. The guard and assignments are stored as
	// expressions. The synchronisation is stored as an int.
	struct transition_t {
	    state_t *src;
	    state_t *dst;
	    ExpressionProgram guard;
	    ExpressionProgram assign;
	    ExpressionProgram sync;
	};

	// function structure has the uid in symbol table, 
	// its own frame of variables and flag of being global
	struct function_t {
	    int32_t uid;
	    bool global;
	    BlockStatement *body;
	    function_t(): body(NULL) {}
	};

	// A template is stored with information about its frame,
	// states (a.k.a. locations), the variables, the uid of the
	// initial state, and the transitions. Notice that the
	// expressions are *not* converted to, for instance, the
	// Uppaal Expression classes. This is because the template
	// must be instantiated before we know the index of local
	// variables and parameters in the IntegerTable.
	struct template_t {
	    int32_t frame;
	    std::list<state_t> states;
	    std::list<variable_t> variables;
	    std::list<constant_t> constants;  
	    std::list<channel_t> channels;    
	    std::list<clock_t> clocks;     
	    int32_t init;
	    std::list<transition_t> transitions;
	    std::list<function_t> functions;
	    std::map<int32_t, ExpressionProgram> mapping;
	};

	struct process_t {
	    int32_t uid;
	    int32_t nr;
	    template_t *templ;
	    int32_t stateOffset, variableOffset, clockOffset, channelOffset;
	};

    };

    class TimedAutomataSystem : public TimedAutomataStructures
    {
    public:
	TimedAutomataSystem();
	virtual ~TimedAutomataSystem();

	TypeSystem &getTypeSystem();
	SymbolTable &getSymbolTable();
	std::list<template_t> &getTemplates();
	std::list<process_t> &getProcesses();
	template_t &getGlobals();
	template_t &getCurrentTemplate();
	void setCurrentTemplate(template_t &);

	void addClock(int32_t type, const char *name);
	void addVariable(int32_t type, const char *name, 
			 const ExpressionProgram &initial);
	void addConstant(int32_t type, const char *name, 
			 const ExpressionProgram &initial);
	void addChannel(int32_t type, const char *name);
	function_t &addFunction(int32_t type, const char *name);

	template_t &addTemplate(int32_t frame);
	state_t &addState(int32_t uid, ExpressionProgram &inv);
	transition_t &addTransition(int32_t src, int32_t dst);
	process_t &addProcess(int32_t uid, template_t &);

	int getPrecedence(int kind);

	char *expressionToString(const ExpressionProgram &);
	char *expressionToString(const SubExpression &);

	int32_t evaluateConstantExpression(const SubExpression expr);
	void evaluateConstantExpression(
	    const SubExpression expr,
	    std::vector<int32_t> &s);

	int32_t sizeOfType(int32_t type);
  
    protected:
	TypeSystem types;
	SymbolTable symbols;

	// The list of templates. This is only used to keep track of the
	// memory used for the template_t structures. Normally, existing
	// template structures are located using the symbol table.
	std::list<template_t> templates;

	// List of processes used in the system line
	std::list<process_t> processes;

	// Not really a template, only used to keep track of global variables
	template_t global;

	// The current template: New variables will be added to this template
	template_t *current_template;

	char *expressionToString(
	    ExpressionProgram::const_iterator first,
	    ExpressionProgram::const_iterator last);

	int32_t evaluateConstantBinary(int32_t left, int32_t op, int32_t right);
    };
}
#endif
