// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2020 Aalborg University.
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

#include "utap/common.h"

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace UTAP {
/**
 * Exception indicating a type error. This is thrown by
 * implementations of the ParserBuilder interface to indicate that
 * a type error has occurred.
 */
class TypeException : public std::logic_error
{
public:
    using std::logic_error::logic_error;
};

/**
 * The ParserBuilder interface is used by the parser to output the
 * parsed document. The parser itself will only parse the document -
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
 * - call decl_typedef(name) to declare the type-name
 *
 * The proper protocol for declaring a variable is to
 *
 * - report the type using the typeXXX methods
 * - optionally report an expression for the initialiser
 * - call decl_var(name, init), where init is true if and
 *   only if an initialiser has been reported
 */
class ParserBuilder
{
public:
    /*********************************************************************
     * Prefixes
     */
    enum PREFIX {
        PREFIX_NONE = 0,
        PREFIX_CONST = 1,
        PREFIX_URGENT = 2,
        PREFIX_BROADCAST = 4,
        PREFIX_URGENT_BROADCAST = 6,
        PREFIX_SYSTEM_META = 8,
        PREFIX_HYBRID = 16
    };

    std::vector<std::string> lscTemplateNames;

    virtual ~ParserBuilder() noexcept = default;

    /**
     * Add mapping from an absolute position to a relative XML
     * element.
     */
    virtual void add_position(uint32_t position, uint32_t offset, uint32_t line, std::shared_ptr<std::string> path) = 0;

    /**
     * Sets the current position. The current position indicates
     * where in the input file the current productions can be
     * found.
     */
    virtual void set_position(uint32_t a, uint32_t b) = 0;

    // Called when an error is detected
    virtual void handle_error(const TypeException&) = 0;

    // Called when a warning is issued
    virtual void handle_warning(const TypeException&) = 0;

    /**
     * Must return true if and only if name is registered in the
     * symbol table as a named type, for instance, "int" or "bool" or
     * a user defined type.
     */
    virtual bool is_type(const char*) = 0;

    /** Duplicate type at the top of the type stack. */
    virtual void type_duplicate() = 0;

    /** Pop type at the top of the type stack. */
    virtual void type_pop() = 0;

    /**
     * Called whenever a boolean type is parsed.
     */
    virtual void type_bool(PREFIX) = 0;

    /**
     * Called whenever an integer type is parsed.
     */
    virtual void type_int(PREFIX) = 0;

    /**
     * Called whenever a string type is parsed.
     */
    virtual void type_string(PREFIX) = 0;

    /**
     * Called whenever a double type is parsed.
     */
    virtual void type_double(PREFIX) = 0;

    /**
     * Called whenever an integer type with a range is
     * parsed. Expressions for the lower and upper have been
     * pushed before.
     */
    virtual void type_bounded_int(PREFIX) = 0;

    /**
     * Called whenever a channel type is parsed.
     */
    virtual void type_channel(PREFIX) = 0;

    /**
     * Called whenever a clock type is parsed.
     */
    virtual void type_clock(PREFIX) = 0;

    /**
     * Called whenever a void type is parsed.
     */
    virtual void type_void() = 0;

    /**
     * Called to create an array type. The size of the array was
     * previously pushed as an expression.
     */
    virtual void type_array_of_size(size_t) = 0;

    /**
     * Called to create an array type. The size of the array was
     * previously pushed as a type.
     */
    virtual void type_array_of_type(size_t) = 0;

    /**
     * Called whenever a scalar type is parsed. The size of the
     * scalar set was pushed as an expression before.
     */
    virtual void type_scalar(PREFIX) = 0;

    /**
     * Called when a type name has been parsed. Prefix indicates
     * whether the type named was prefixed (e.g. with 'const').
     */
    virtual void type_name(PREFIX, const char* name) = 0;

    /**
     * Called when a struct-type has been parsed. Prior to the
     * call 'fields' fields must have been declared using the
     * structXXX methods.
     */
    virtual void type_struct(PREFIX, uint32_t fields) = 0;

    /**
     * Called to declare a field of a structure. The type of the
     * field has been reported using a typeXXX method prior to the
     * call of struct_field(). In case of array fields, 'dim'
     * expressions indicating the array sizes have been reported.
     */
    virtual void struct_field(const char* name) = 0;

    /**
     * Used when a typedef declaration was parsed. name is the
     * name of the new type.
     */
    virtual void decl_typedef(const char* name) = 0;

    /**
     * Called to when a variable declaration has been parsed.
     */
    virtual void decl_var(const char* name, bool init) = 0;

    virtual void decl_init_list(uint32_t num) = 0;       // n initialisers
    virtual void decl_field_init(const char* name) = 0;  // 1 initialiser

    /**
     * Guard progress measure declaration. Requires two
     * expressions if \a hasGuard is true, otherwise one.
     */
    virtual void decl_progress(bool hasGuard) = 0;

    /********************************************************************
     * Function declarations
     */
    virtual void decl_parameter(const char* name, bool ref) = 0;
    virtual void decl_func_begin(const char* name) = 0;
    virtual void decl_func_end() = 0;  // 1 block
    virtual void dynamic_load_lib(const char* name) = 0;
    virtual void decl_external_func(const char* name, const char* alias) = 0;

    /********************************************************************
     * Process declarations
     */
    virtual void proc_begin(const char* name, const bool isTA = true, const std::string& type = "",
                            const std::string& mode = "") = 0;                        // m parameters
    virtual void proc_end() = 0;                                                      // 1 ProcBody
    virtual void proc_location(const char* name, bool hasInvariant, bool hasER) = 0;  // 1 expr
    virtual void proc_location_commit(const char* name) = 0;                          // mark previously decl. state
    virtual void proc_location_urgent(const char* name) = 0;                          // mark previously decl. state
    virtual void proc_location_init(const char* name) = 0;                            // mark previously decl. state
    virtual void proc_edge_begin(const char* from, const char* to, const bool control, const char* color = "#000000", const char* actname = "") = 0;
    virtual void proc_edge_end(const char* from, const char* to) = 0;
    virtual void proc_select(const char* id) = 0;                   // 1 expr
    virtual void proc_guard() = 0;                                  // 1 expr
    virtual void proc_sync(Constants::synchronisation_t type) = 0;  // 1 expr
    virtual void proc_update() = 0;                                 // 1 expr
    virtual void proc_prob() = 0;
    virtual void proc_branchpoint(const char* name) = 0;
    /************************************************************
     * Process declarations for LSC
     */
    virtual void proc_instance_line() = 0;
    virtual void instance_name(const char* name, bool templ = true) = 0;
    virtual void instance_name_begin(const char* name) = 0;
    virtual void instance_name_end(const char* name, size_t arguments) = 0;
    virtual void proc_message(const char* from, const char* to, const int loc, const bool pch) = 0;
    virtual void proc_message(Constants::synchronisation_t type) = 0;
    virtual void proc_condition(const std::vector<std::string>& anchors, const int loc, const bool pch,
                                const bool hot) = 0;
    virtual void proc_condition() = 0;  // 1 expr
    virtual void proc_LSC_update(const char* anchor, const int loc, const bool pch) = 0;
    virtual void proc_LSC_update() = 0;  // 1 expr
    virtual void prechart_set(const bool pch) = 0;

    /********************************************************************
     * Gantt chart declarations
     */
    virtual void gantt_decl_begin(const char* name) = 0;
    virtual void gantt_decl_select(const char* id) = 0;
    virtual void gantt_decl_end() = 0;
    virtual void gantt_entry_begin() = 0;
    virtual void gantt_entry_select(const char* id) = 0;
    virtual void gantt_entry_end() = 0;

    /*********************************************************************
     * Statements
     */
    virtual void block_begin() = 0;
    virtual void block_end() = 0;
    virtual void empty_statement() = 0;
    virtual void for_begin() = 0;                        // 3 expr
    virtual void for_end() = 0;                          // 1 stat
    virtual void iteration_begin(const char* name) = 0;  // 1 id, 1 type
    virtual void iteration_end(const char* name) = 0;    // 1 stat
    virtual void while_begin() = 0;
    virtual void while_end() = 0;  // 1 expr, 1 stat
    virtual void do_while_begin() = 0;
    virtual void do_while_end() = 0;  // 1 stat, 1 expr
    virtual void if_begin() = 0;
    virtual void if_condition() = 0;         // 1 expr
    virtual void if_then() = 0;              // 1 expr, 1 (then)
    virtual void if_end(bool elsePart) = 0;  // 1 expr, 1 or 2 statements
    virtual void break_statement() = 0;
    virtual void continue_statement() = 0;
    virtual void switch_begin() = 0;
    virtual void switch_end() = 0;  // 1 expr, 1+ case/default
    virtual void case_begin() = 0;
    virtual void case_end() = 0;  // 1 expr, 0+ stat
    virtual void default_begin() = 0;
    virtual void default_end() = 0;           // 0+ statements
    virtual void expr_statement() = 0;        // 1 expr
    virtual void return_statement(bool) = 0;  // 1 expr if argument is true
    virtual void assert_statement() = 0;      // 1 expr

    /********************************************************************
     * Expressions
     */
    virtual void expr_false() = 0;
    virtual void expr_true() = 0;
    virtual void expr_double(double) = 0;
    virtual void expr_string(const char* name) = 0;
    virtual void expr_identifier(const char* varName) = 0;
    virtual void expr_location() = 0;
    virtual void expr_nat(int32_t) = 0;  // natural number
    virtual void expr_call_begin() = 0;
    virtual void expr_call_end(uint32_t n) = 0;                   // n exprs as arguments
    virtual void expr_array() = 0;                                // 2 expr
    virtual void expr_post_increment() = 0;                       // 1 expr
    virtual void expr_pre_increment() = 0;                        // 1 expr
    virtual void expr_post_decrement() = 0;                       // 1 expr
    virtual void expr_pre_decrement() = 0;                        // 1 expr
    virtual void expr_assignment(Constants::kind_t op) = 0;       // 2 expr
    virtual void expr_unary(Constants::kind_t unaryop) = 0;       // 1 expr
    virtual void expr_binary(Constants::kind_t binaryop) = 0;     // 2 expr
    virtual void expr_nary(Constants::kind_t, uint32_t num) = 0;  // n expr
    virtual void expr_scenario(const char* name) = 0;             // LSC
    virtual void expr_ternary(Constants::kind_t ternaryop,
                              bool firstMissing = false) = 0;  // 3 expr
    virtual void expr_inline_if() = 0;                         // 3 expr
    virtual void expr_comma() = 0;                             // 2 expr
    virtual void expr_dot(const char*) = 0;                    // 1 expr
    virtual void expr_deadlock() = 0;
    virtual void expr_forall_begin(const char* name) = 0;
    virtual void expr_forall_end(const char* name) = 0;
    virtual void expr_exists_begin(const char* name) = 0;
    virtual void expr_exists_end(const char* name) = 0;
    virtual void expr_sum_begin(const char* name) = 0;
    virtual void expr_sum_end(const char* name) = 0;

    // Extensions for SMC:
    virtual void expr_proba_qualitative(Constants::kind_t, Constants::kind_t, double) = 0;  ///< estimate Pr
    virtual void expr_proba_quantitative(Constants::kind_t) = 0;                            ///< evaluate if Pr >= value
    virtual void expr_proba_compare(Constants::kind_t, Constants::kind_t) = 0;              ///< compare two Prs
    virtual void expr_proba_expected(const char* identifier) = 0;                           ///< estimate mean value
    virtual void expr_simulate(int nb_of_exprs, bool filter_prop = false, int max_accepting_runs = 0) = 0;
    virtual void expr_builtin_function1(Constants::kind_t) = 0;
    virtual void expr_builtin_function2(Constants::kind_t) = 0;
    virtual void expr_builtin_function3(Constants::kind_t) = 0;

    // Extensions for learning:
    enum PRICETYPE { TIMEPRICE, EXPRPRICE, PROBAPRICE };
    virtual void expr_optimize_exp(Constants::kind_t, PRICETYPE,
                                   Constants::kind_t) = 0;  ///< minimize/maximize expected value query
    virtual void expr_load_strategy() = 0;
    virtual void expr_save_strategy(const char* strategy_name) = 0;

    virtual void expr_atl(int, Constants::kind_t) = 0;

    // MITL Extensions
    virtual void expr_MITL_formula() = 0;
    virtual void expr_MITL_until(int, int) = 0;
    virtual void expr_MITL_release(int, int) = 0;
    virtual void expr_MITL_disj() = 0;
    virtual void expr_MITL_conj() = 0;
    virtual void expr_MITL_next() = 0;
    virtual void expr_MITL_atom() = 0;
    virtual void expr_MITL_diamond(int, int) = 0;
    virtual void expr_MITL_box(int, int) = 0;

    virtual void expr_optimize(int, int, int, int) = 0;

    /********************************************************************
     * System declaration
     */
    virtual void instantiation_begin(const char* id, size_t parameters, const char* templ) = 0;
    virtual void instantiation_end(const char* id, size_t parameters, const char* templ, size_t arguments) = 0;
    virtual void process(const char*) = 0;
    virtual void process_list_end() = 0;
    virtual void done() = 0;  // marks the end of the file

    virtual void handle_expect(const char* text) = 0;

    /********************************************************************
     * Properties
     */
    virtual void property() = 0;
    virtual void scenario(const char*) = 0;              // LSC
    virtual void parse(const char*) = 0;                 // LSC
    virtual void strategy_declaration(const char*) = 0;  // tiga-smc
    virtual void subjection(const char*) = 0;
    virtual void imitation(const char*) = 0;

    /********************************************************************
     * Guiding
     */
    virtual void before_update() = 0;
    virtual void after_update() = 0;

    /********************************************************************
     * Priority
     */
    virtual void chan_priority_begin() = 0;
    virtual void chan_priority_add(char separator) = 0;
    virtual void chan_priority_default() = 0;
    virtual void proc_priority_inc() = 0;
    virtual void proc_priority(const std::string&) = 0;
    /** Dynamic */
    virtual void decl_dynamic_template(const std::string& name) = 0;
    virtual void expr_spawn(int) = 0;
    virtual void expr_exit() = 0;
    virtual void expr_numof() = 0;
    virtual void expr_forall_dynamic_begin(const char*, const char*) = 0;
    virtual void expr_forall_dynamic_end(const char* name) = 0;
    virtual void expr_exists_dynamic_begin(const char*, const char*) = 0;
    virtual void expr_exists_dynamic_end(const char* name) = 0;
    virtual void expr_sum_dynamic_begin(const char*, const char*) = 0;
    virtual void expr_sum_dynamic_end(const char* name) = 0;
    virtual void expr_foreach_dynamic_begin(const char*, const char*) = 0;
    virtual void expr_foreach_dynamic_end(const char* name) = 0;
    virtual void expr_MITL_forall_dynamic_begin(const char*, const char*) = 0;
    virtual void expr_MITL_forall_dynamic_end(const char* name) = 0;
    virtual void expr_MITL_exists_dynamic_begin(const char*, const char*) = 0;
    virtual void expr_MITL_exists_dynamic_end(const char* name) = 0;
    virtual void expr_dynamic_process_expr(const char*) = 0;

    /** Verification queries */
    virtual void model_option(const char* key, const char* value) = 0;
    virtual void query_begin() = 0;
    virtual void query_formula(const char* formula, const char* location) = 0;
    virtual void query_comment(const char* comment) = 0;
    virtual void query_options(const char* option, const char*) = 0;
    virtual void expectation_begin() = 0;
    virtual void expectation_end() = 0;
    virtual void expectation_value(const char* res, const char* type, const char* value) = 0;
    virtual void expect_resource(const char* type, const char* value, const char* unit) = 0;
    virtual void query_results_begin() = 0;
    virtual void query_results_end() = 0;
    virtual void query_end() = 0;
};

/** Error/warning messages with some arguments */
TypeException UnknownIdentifierError(const std::string& name);
TypeException HasNoMemberError(const std::string& name);
TypeException IsNotAStructError(const std::string& name);
TypeException DuplicateDefinitionError(const std::string& name);
TypeException InvalidTypeError(const std::string& name);
TypeException NoSuchProcessError(const std::string& name);
TypeException NotATemplateError(const std::string& name);
TypeException NotAProcessError(const std::string& name);
TypeException StrategyNotDeclaredError(const std::string& name);
TypeException UnknownDynamicTemplateError(const std::string& name);
TypeException ShadowsAVariableWarning(const std::string& name);

}  // namespace UTAP

/**
 * Parse a file in the XTA format, reporting the document to the given
 * implementation of the the ParserBuilder interface and reporting
 * errors to the ErrorHandler. If newxta is true, then the 4.x syntax
 * is used; otherwise the 3.x syntax is used. On success, this
 * function returns with a positive value.
 */
int32_t parse_XTA(FILE*, UTAP::ParserBuilder*, bool newxta);

int32_t parse_XTA(const char*, UTAP::ParserBuilder*, bool newxta);

/**
 * Parse a buffer in the XTA format, reporting the document to the given
 * implementation of the the ParserBuilder interface and reporting
 * errors to the ErrorHandler. If newxta is true, then the 4.x syntax
 * is used; otherwise the 3.x syntax is used. On success, this
 * function returns with a positive value.
 */
int32_t parse_XTA(const char*, UTAP::ParserBuilder*, bool newxta, UTAP::xta_part_t part, std::string xpath);

/**
 * Parse a buffer in the XML format, reporting the document to the given
 * implementation of the the ParserBuilder interface and reporting
 * errors to the ErrorHandler. If newxta is true, then the 4.x syntax
 * is used; otherwise the 3.x syntax is used. On success, this
 * function returns with a positive value.
 */
int32_t parse_XML_buffer(const char* buffer, UTAP::ParserBuilder*, bool newxta);

/**
 * Parse the file with the given name assuming it is in the XML
 * format, reporting the document to the given implementation of the the
 * ParserBuilder interface and reporting errors to the
 * ErrorHandler. If newxta is true, then the 4.x syntax is used;
 * otherwise the 3.x syntax is used. On success, this function returns
 * with a positive value.
 */
int32_t parse_XML_file(const char* filename, UTAP::ParserBuilder*, bool newxta);

int32_t parse_XML_fd(int fd, UTAP::ParserBuilder* pb, bool newxta);

/**
 * Parse properties from a buffer. The properties are reported using
 * the given ParserBuilder and errors are reported using the
 * ErrorHandler.
 */
int32_t parseProperty(const char* str, UTAP::ParserBuilder* aParserBuilder, const std::string& xpath = "");

/**
 * Parse properties from a file. The properties are reported using the
 * given ParserBuilder and errors are reported using the ErrorHandler.
 */
int32_t parseProperty(FILE*, UTAP::ParserBuilder* aParserBuilder);

#endif /* UTAP_BUILDER_HH */
