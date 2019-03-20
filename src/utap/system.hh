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

#ifndef UTAP_INTERMEDIATE_HH
#define UTAP_INTERMEDIATE_HH

#include <list>
#include <vector>
#include <map>
#include <exception>

#include "symbols.hh"
#include "utap/expression.hh"
#include "statement.hh"

namespace UTAP
{

    /** Base type for variables, clocks, etc.  The user data of the
	corresponding symbol_t points to this structure,
	i.e. v.uid.getData() is a pointer to v.
    */
    struct variable_t {
	symbol_t uid;      /**< The symbol of the variables */
	bool global;	   /**< True if this is a global variable */
	expression_t expr; /**< The initialiser */
    };
	
    /** Information about a location.
	The symbol's user data points to this structure, i.e.
	s.uid.getData() is a pointer to s.
    */
    struct state_t {
	symbol_t uid;		/**< The symbol of the location */
	expression_t invariant; /**< The invariant */
	int32_t locNr;		/**< Location number in template */
    };

    /** Information about a transition.  Transitions have a source
	(src) and a destination (dst), which are actually the uid of
	the symbols in the symbol table. The guard, synchronisation
	and assignment are stored as expressions.
    */
    struct transition_t {
	int nr;			/**< Placement in in put file */
	state_t *src;		/**< Pointer to source location */
	state_t *dst;		/**< Pointer to destination location */
	expression_t guard;	        /**< The guard */
	expression_t assign;	/**< The assignment */
	expression_t sync;	        /**< The synchronisation */
    };

    /** Information about a function. The symbol's user data points to
	this structure, i.e. f.uid.getData() is a pointer to f.
    */
    struct function_t {
	symbol_t uid;		/**< The symbol of the function */
	bool global;		/**< True if this is a global function */
	BlockStatement *body;	/**< Pointer to the block */
	function_t() : body(NULL) {}
	~function_t() { delete body; }
    };
    
    struct template_t;
	
    struct instance_t {
	symbol_t uid;
	const template_t *templ;
	std::map<symbol_t, expression_t> mapping;
    };
	
    /** Information about a template. A template is either a
	parameterized automaton.
    */
    struct template_t
    {
	symbol_t uid;				/**< The symbol of the template */
	frame_t frame;				/**< The local variables */
	std::list<variable_t> variables;	/**< Local variables */
	std::list<function_t> functions;	/**< Local functions */
	std::list<instance_t> instances;	/**< The 'instances' */	
	int32_t nr;				/**< Placement in input file */
	std::list<state_t> states;		/**< The locations */
	std::list<transition_t> transitions;	/**< The transitions */
	symbol_t init;				/**< The initial location */
    };

    /** Information about a process. A process is something mentioned
	in the system line of the input file. It basically points to a
	template, but also contains information about offsets for
	local variables, clocks, etc.
    */
    struct process_t : public instance_t 
    {
	int32_t nr;		/**< Placement in the system line */
    };

    class TimedAutomataSystem;
    
    class SystemVisitor
    {
    public:
	virtual ~SystemVisitor() {}
	virtual void visitSystemBefore(TimedAutomataSystem *) {}
	virtual void visitSystemAfter(TimedAutomataSystem *) {}
	virtual void visitVariable(variable_t &) {}
	virtual bool visitTemplateBefore(template_t &) { return true; }
	virtual void visitTemplateAfter(template_t &) {}
	virtual void visitState(state_t &) {}
	virtual void visitTransition(transition_t &) {}
	virtual void visitInstance(instance_t &) {}
	virtual void visitProcess(process_t &) {}
	virtual void visitFunction(function_t &) {}
    };

    class TimedAutomataSystem
    {
    public:
	TimedAutomataSystem();
	virtual ~TimedAutomataSystem();

	std::list<template_t> &getTemplates();
	std::list<process_t> &getProcesses();
	template_t &getGlobals();
	template_t &getCurrentTemplate();
	void setCurrentTemplate(template_t &);

	void addVariable(type_t type, const char *name, 
			 expression_t initial);
	function_t &addFunction(type_t type, const char *name);

	template_t &addTemplate(const char *name, frame_t params);
	state_t &addLocation(const char *name, expression_t inv);
	transition_t &addTransition(symbol_t src, symbol_t dst);
	instance_t &addInstance(const char *name, const template_t *);
	process_t &addProcess(symbol_t uid);
	void accept(SystemVisitor &);

	const std::set<symbol_t> &getConstants() const;

	const std::map<symbol_t, expression_t> getConstantValuation() const;
	
    protected:
	// The list of templates.
	std::list<template_t> templates;

	// The list of template instances.
	std::list<instance_t> instances;
	
	// List of processes used in the system line
	std::list<process_t> processes;

	// The set of all constants
	std::set<symbol_t> constants;	

	// Maps constans to their values
	std::map<symbol_t, expression_t> constantValuation;
	
	// Not really a template, only used to keep track of global variables
	template_t global;

	// The current template: New variables will be added to this template
	template_t *current_template;
    };

    /** Extension of SystemVisitor which tracks the context. It can use
	this information when reporting errors and warnings to an
	ErrorHandler.
    */
    class ContextVisitor : public SystemVisitor, private XPath
    {
    private:
	int currentTemplate;
	char path[256];
	ErrorHandler *errorHandler;
	char *get() const;
    protected:
	void setContextNone();
	void setContextDeclaration();
	void setContextParameters();
	void setContextInvariant(state_t &);
	void setContextGuard(transition_t &);
	void setContextSync(transition_t &);
	void setContextAssignment(transition_t &);
	void setContextInstantiation();
	
	void handleError(expression_t, const char *);
	void handleWarning(expression_t, const char *);
    public:
	ContextVisitor(ErrorHandler *);
	virtual bool visitTemplateBefore(template_t &);
	virtual void visitTemplateAfter(template_t &);
    };

}
#endif
