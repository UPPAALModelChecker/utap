// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2020 Aalborg University.
   Copyright (C) 2002-2006 Uppsala University and Aalborg University.

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

#ifndef UTAP_TYPE_HH
#define UTAP_TYPE_HH

#include "utap/common.h"
#include "utap/position.h"

#include <memory>  // shared_ptr
#include <optional>
#include <string>
#include <cstdint>

namespace UTAP {
class expression_t;
class frame_t;
class symbol_t;

/**
   A reference to a type.

   Types are represented as trees of types. The type cannot be
   access directly. You need to use an instance of type_t to
   access a type. Internally, types are reference counted and do
   not need to be deallocated manually. Types are immutable.

   Types are either primitive such as clocks or channels, or
   contructed types such as structs and array. Constructed types
   are created using one of the factory methods in the type_t
   class. Primitive types are leaves in the tree, constructed
   types are inner nodes.

   All types have a kind - a type for the type. The kind is a
   value of kind_t. In anticipation of a future homogeneous AST,
   this kind is defined in the same enumerable as the kind of
   expressions.

   Some constructed types are considered prefixes for other types:
   URGENT, COMMITTED, BROADCAST, CONSTANT and BROADCAST.

   LABEL types are references to named types. These are introduced
   by references to types defined with a typedef or by scalar set
   declarations. They have one child: The type which has been
   named.

   Constructed types are:

   - ARRAY; the first child is the element type, the second type
     is the array size (another type; either integer or scalarset).

   - RECORD; the children are the fields of the record.

   - FUNCTION; the first child is the return type. Remaining
     children are parameters.

   - INSTANCE; the parameters of an instance are the children.

   - PROCESS; the local variables of a process are the children.

   - PROCESSSET; process with unbound parameters. The unbound
     parameters are the children.

   - TYPEDEF; a type definition - it has one child.

   - RANGE; ranges have three children: the first is the type on
     which a range has been applied, the second is the lower bound
     and the third is the upper bound (the second and third
     children are really expression objects wrapped in a dummy
     type).

   - REF; a reference - the first child is the type from which the
     reference type is formed.
*/
class type_t
{
private:
    struct type_data;
    std::shared_ptr<type_data> data;

public:
    explicit type_t(Constants::kind_t kind, const position_t& pos, size_t size);
    /**
     * Default constructor. This creates a null-type.
     */
    type_t() = default;

    /** Equality operator. */
    bool operator==(const type_t&) const;

    /** Inequality operator. */
    bool operator!=(const type_t&) const;

    /** Returns the kind of type object. */
    Constants::kind_t get_kind() const;

    /**
     * Returns the position of the type in the input file. This
     * exposes the fact that the type is actually part of the AST.
     */
    position_t get_position() const;

    /**
     * Returns the number of children.
     */
    size_t size() const;

    /** Less-than operator. */
    bool operator<(const type_t&) const;

    /** Returns the \a i'th child. */
    type_t operator[](uint32_t) const;

    /** Returns the \a i'th child. */
    type_t get(uint32_t) const;

    /** Returns the \a i'th label. */
    const std::string& get_label(uint32_t) const;

    /** Returns the position of i'th field in struct */
    const position_t& get_field_position(uint32_t) const;

    /** Returns the expression associated with the type. */
    expression_t get_expression() const;

    /**
     * Returns the size of an array (this is itself a type). @pre
     * is_array().
     */
    type_t get_array_size() const;

    /**
     * Returns the element type of an array. Preserves any
     * prefixes. @pre is_array();
     */
    type_t get_sub() const;

    /**
     * Returns the \i'th field of a record or process. Preserves
     * any prefixes. @pre is_record() or is_process().
     */
    type_t get_sub(uint32_t) const;

    /**
     * Returns the number of fields of a record. @pre is_record().
     */
    uint32_t get_record_size() const;

    /**
     * Returns the label of the \i'th field of a record. @pre
     * is_record().
     */
    const std::string& get_record_label(size_t i) const;

    /**
     * Returns the index of the record or process field with the
     * given label. Returns -1 if such a field does not
     * exist. @pre is_record() or is_process().
     */
    std::optional<uint32_t> find_index_of(const std::string&) const;

    /**
     * Returns the range of a RANGE type. @pre is_range().
     */
    std::pair<expression_t, expression_t> get_range() const;

    /** Prints textual representation of the type. */
    std::ostream& print(std::ostream&) const;

    /** Generates string representation of the type. */
    std::string str() const;

    /** Pretty-prints the declaration. */
    std::ostream& print_declaration(std::ostream& os) const;

    /** Generates the declaration representation. */
    std::string declaration() const;

    /** Shortcut for is(RANGE). */
    bool is_range() const { return is(Constants::RANGE); }

    /** Shortcut for is(INT). */
    bool is_integer() const { return is(Constants::INT); }

    /** Shortcut for is(BOOL). */
    bool isBoolean() const { return is(Constants::BOOL); }

    /** Shortcut for is(FUNCTION). */
    bool is_function() const { return is(Constants::FUNCTION); }

    bool is_function_external() const { return is(Constants::FUNCTION_EXTERNAL); }

    /** Shortcut for is(PROCESS). */
    bool is_process() const { return is(Constants::PROCESS); }

    /** Shortcut for is(PROCESSSET). */
    bool is_process_set() const { return is(Constants::PROCESS_SET); }

    /** Shortcut for is(LOCATION). */
    bool is_location() const { return is(Constants::LOCATION); }

    /** Shortcut for is(LOCATION_EXPR). */
    bool is_location_expr() const { return is(Constants::LOCATION_EXPR); }

    /** Shortcut for is(INSTANCELINE). */
    bool is_instance_line() const { return is(Constants::INSTANCE_LINE); }

    /** Shortcut for is(BRANCHPOINT). */
    bool is_branchpoint() const { return is(Constants::BRANCHPOINT); }

    /** Shortcut for is(CHANNEL). */
    bool is_channel() const { return is(Constants::CHANNEL); }

    /** Shortcut for is(ARRAY). */
    bool is_array() const { return is(Constants::ARRAY); }

    /** Shortcut for is(SCALAR). */
    bool is_scalar() const { return is(Constants::SCALAR); }

    /** Shortcut for is(CLOCK). */
    bool is_clock() const { return is(Constants::CLOCK); }

    /** Shortcut for is(RECORD). */
    bool is_record() const { return is(Constants::RECORD); }

    /** Shortcut for is(DIFF). */
    bool is_diff() const { return is(Constants::DIFF); }

    /** Shortcut for is(VOID_TYPE). */
    bool is_void() const { return is(Constants::VOID_TYPE); }

    /** Shortcut for is(COST). */
    bool is_cost() const { return is(Constants::COST); }

    /** Shortcut for is(DOUBLE). */
    bool is_double() const { return is(Constants::DOUBLE); }

    /** Shortcut for is(STRING). */
    bool is_string() const { return is(Constants::STRING); }

    /**
     * Returns true if this is a boolean or integer. Shortcut for
     * isInt() || isBoolean().
     */
    bool is_integral() const
    {
        using namespace Constants;
        return is(INT) || is(BOOL) || is(PROCESS_VAR) || is(LOCATION) || is(LOCATION_EXPR);
    }

    /**
     * Returns true if this is an invariant, boolean or
     * integer. Shortcut for isIntegral() || is(INVARIANT).
     */
    bool is_invariant() const { return is(Constants::INVARIANT) || is_integral(); }

    /**
     * Returns true if this is a guard, invariant, boolean or
     * integer.  Shortcut for is(GUARD) || is_invariant().
     */
    bool is_guard() const { return is(Constants::GUARD) || is_invariant(); }

    /**
     * Returns true if this is a probability or integer.  Shortcut
     * for is(PROBABILITY) || isInteger().
     */
    bool is_probability() const { return is(Constants::PROBABILITY) || is_integer() || is_double() || is_clock(); }

    /**
     * Returns true if this is a constraint, guard, invariant,
     * boolean or integer. Shortcut for is(CONSTRAINT) ||
     * is_guard().
     */
    bool is_constraint() const { return is(Constants::CONSTRAINT) || is_guard(); }

    /**
     * Returns true if this is a formula, constraint, guard,
     * invariant, boolean or integer. Shortcut for is(FORMULA) ||
     * is_constraint().
     */
    bool is_formula() const { return is(Constants::FORMULA) || is_constraint(); }

    /**
     * Removes any leading prefixes, RANGE, REF and LABEL types
     * and returns the result.
     */
    type_t strip() const;

    /**
     * Removes any leading prefixes, RANGE, REF, LABEL and ARRAY
     * types and returns the result.
     */
    type_t strip_array() const;

    /**
     * Returns false for non-prefix types and true
     * otherwise. Non-prefix types are PRIMITIVE, ARRAY, RECORD,
     * PROCESS, TEMPLATE, FUNCTION, INSTANCE, LSCINSTANCE, RANGE, REF, TYPEDEF.
     */
    bool is_prefix() const;

    /** Returns true if and only if all elements of the type are constant. */
    bool is_constant() const;

    /** Returns true if and only if all elements of the type are mutable (not constant). */
    bool is_mutable() const;

    /**
     * Returns true if the type has kind \a kind or if type is a
     * prefix, RANGE or REF type and the getChild().is(kind)
     * returns true.
     */
    bool is(Constants::kind_t kind) const;

    /**
     * Returns true if this is null-type or of kind UNKNOWN.
     */
    bool unknown() const;

    /**
     * Replaces any LABEL labeled \a from occurring in the type
     * with a LABEL \a to. As always, a type is immutable, so a
     * copy of the type will be created.
     */
    type_t rename(const std::string& from, const std::string& to) const;

    /**
     * Substitutes any occurence of \a symbol in any expression in
     * the type (expressions that occur as ranges either on
     * array sizes, scalars or integers) with \a expr.
     */
    type_t subst(symbol_t symbol, expression_t expr) const;
    /**
     * Creates a new type by adding a prefix to it. The prefix
     * could be anything and it is the responsibility of the
     * caller to make sure that the given kind is a valid prefix.
     */
    type_t create_prefix(Constants::kind_t kind, position_t = position_t()) const;

    /** Creates a LABEL. */
    type_t create_label(std::string, position_t = position_t()) const;

    /**
     */
    static type_t create_range(type_t, expression_t, expression_t, position_t = position_t());

    /** Create a primitive type. */
    static type_t create_primitive(Constants::kind_t, position_t = position_t());

    /** Creates an array type. */
    static type_t create_array(type_t sub, type_t size, position_t = position_t());

    /** Creates a new type definition. */
    static type_t create_typedef(std::string, type_t, position_t = position_t());

    /** Creates a new process type. */
    static type_t create_process(frame_t, position_t = position_t());

    /** Creates a new processset type. */
    static type_t create_process_set(type_t instance, position_t = position_t());

    /** Creates a new record type */
    static type_t create_record(const std::vector<type_t>&, const std::vector<std::string>&,
                                const std::vector<position_t>&, position_t = position_t());

    /** Creates a new function type */
    static type_t create_function(type_t, const std::vector<type_t>&, const std::vector<std::string>&,
                                  position_t = position_t());

    static type_t create_external_function(type_t rt, const std::vector<type_t>&, const std::vector<std::string>&,
                                           position_t = position_t());

    /** Creates a new instance type */
    static type_t create_instance(frame_t, position_t = position_t());
    /** Creates a new lsc instance type */
    static type_t create_LSC_instance(frame_t, position_t = position_t());
};
}  // namespace UTAP

std::ostream& operator<<(std::ostream& o, const UTAP::type_t& t);

#endif
