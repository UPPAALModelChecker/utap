// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-

/* libutap - Uppaal Timed Automata Parser.
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

#ifndef UTAP_EXPRESSION_HH
#define UTAP_EXPRESSION_HH

#include "utap/common.h"
#include "utap/position.h"
#include "utap/string_interning.h"
#include "utap/symbols.h"

#include <memory>  // shared_ptr
#include <set>
#include <string_view>
#include <vector>

namespace UTAP {
/**
    A reference to an expression.

    An expression is a tree of operations and is identified by the
    root of the tree. There are many kinds of operations (see kind_t),
    some are leafs in the tree (identifers, constants), some are
    unary operations (unary minus, negation), some are binary (plus,
    minus, etc.), and some are n-ary (lists, function calls).

    Expressions can be annotated with types. The type of an
    expression should never contain information about whether the
    expression is a variable reference, a constant value or about
    the range of the result value. Use the TypeChecker and
    RangeChecker classes to determine these informations.

    All nodes have the following attributes:

    kind     indicates the kind of operation
    position indicates the position of the expression in the input file.
    type     the type of the result of evaluating the expression
    size     the number of subexpressions
    sub      the subexpressions

    Some nodes have extra attributes (depending on the kind):

    value    the value of a CONSTANT node
    sync     the synchronisation of a SYNC node
    index    the index of a DOT node
    symbol   the symbol of an IDENTIFIER node

    Expressions are created by using the static factory methods.
*/

class expression_t
{
private:
    struct expression_data;
    std::shared_ptr<expression_data> data = nullptr;  // PIMPL pattern with cheap/shallow copying
    expression_t(Constants::kind_t, const position_t&);

public:
    /** Default constructor. Creates an empty expression. */
    expression_t() = default;

    bool uses_fp() const;
    bool uses_clock() const;
    bool uses_hybrid() const;
    bool is_dynamic() const;
    bool has_dynamic_sub() const;
    /** Make a shallow clone of the expression. */
    expression_t clone() const;

    /** Makes a deep clone of the expression. */
    expression_t clone_deeper() const;

    /** Makes a deep clone of the expression and replaces the symbol
     * "from" with the symbol "to". */
    expression_t clone_deeper(symbol_t from, symbol_t to) const;

    /** Makes a deep clone of the expression and replaces each symbol
     * with a symbol from the given frame(s), with the same name */
    expression_t clone_deeper(frame_t frame, frame_t select = {}) const;

    /** Returns the kind of the expression. */
    Constants::kind_t get_kind() const;

    /** Returns the number of subexpression. */
    size_t get_size() const;

    /** Returns the position of this expression. */
    const position_t& get_position() const;

    /** Returns the type of the expression. */
    type_t get_type() const;

    /** Sets the type of the expression. */
    void set_type(type_t);

    /** Returns the value field of this expression. This
        call is not valid for all expressions. */
    int32_t get_value() const;
    std::string_view get_string_value() const;
    size_t get_string_index() const;

    /** Returns an index into the record-labels
        Assumes that .get_type().is_process() or
                     .get_type().is_record()*/
    int32_t get_record_label_index() const;

    /** Returns the index field of this expression. */
    int32_t get_index() const;

    /** Returns the value field of this expression. This
        call is not valid for all expressions. */
    double get_double_value() const;

    /** Returns true if this is an empty expression. */
    bool empty() const;

    /** Returns the synchronisation type of SYNC operations. */
    Constants::synchronisation_t get_sync() const;

    /** Outputs a textual representation of the expression. */
    std::ostream& print(std::ostream& os, bool old = false) const;

    /** Returns a string representation of the expression. */
    std::string str(bool old = false) const;

    /** Returns the ith subexpression. */
    expression_t& operator[](uint32_t);

    /** Returns the ith subexpression. */
    const expression_t operator[](uint32_t) const;

    /** Returns the ith subexpression. */
    expression_t& get(uint32_t);

    /** Returns the ith subexpression. */
    const expression_t& get(uint32_t) const;

    /** Equality operator */
    bool equal(const expression_t&) const;

    /**
     *  Returns the symbol of a variable reference. The expression
     *  must be a left-hand side value. In case of
     *  dot-expressions, the record/process symbol is returned. In
     *  case of an inline if, the 'true' branch is returned.
     *
     *  (a=1).get_symbol() returns 'a'
     *  (s.f).get_symbol() returns 's'
     *  (i<1?j:k).get_symbol() returns 'j'
     */
    symbol_t get_symbol();

    /**
     * Returns the set of symbols this expression might resolve
     * into. In case of inline if, both the 'true' and 'false'
     * branch is added. In case of dot-expressions, both the left
     * hand reference and the member field are returned.
     *
     * (a=1).get_symbol() returns 'a'
     * (s.f).get_symbol() returns 's,f'
     * (i<1?j:k).get_symbol() returns 'j,k'
     */
    void get_symbols(std::set<symbol_t>& symbols) const;

    /** Returns the symbol this expression evaluates to. Notice
        that not all expression evaluate to a symbol. */
    const symbol_t get_symbol() const;

    /** Returns true if this expression is a reference to a
        symbol in the given set. */
    bool is_reference_to(const std::set<symbol_t>&) const;

    /** Returns true if the expression contains deadlock expression */
    bool contains_deadlock() const;
    /** True if this expression can change any of the variables
            identified by the given symbols. */
    bool changes_variable(const std::set<symbol_t>&) const;

    /** True if this expression can change any variable at all. */
    bool changes_any_variable() const;

    /** True if the evaluation of this expression depends on
        any of the symbols in the given set. */
    bool depends_on(const std::set<symbol_t>&) const;

    void collect_possible_writes(std::set<symbol_t>&) const;
    void collect_possible_reads(std::set<symbol_t>&, bool collectRandom = false) const;

    /** Less-than operator. Makes it possible to put expression_t
        objects into an STL set. */
    bool operator<(const expression_t) const;

    /** Equality operator. Returns true if the two references point
        to the same expression object. */
    bool operator==(const expression_t) const;

    expression_t subst(symbol_t, expression_t) const;

    /**
     * Precedence of expression type, higher precedence goes before low precedence
     */
    static int get_precedence(Constants::kind_t);

    /** Create a CONSTANT expression. */
    static expression_t create_constant(int32_t, position_t = {});
    static expression_t create_var_index(int32_t, position_t = {});

    static expression_t create_double(double, position_t = {});
    /** Life time of string reference must outlive expression */
    static expression_t create_string(StringIndex, position_t = {});

    /** Create an IDENTIFIER expression */
    static expression_t create_identifier(symbol_t, position_t = {});

    /** Create a unary expression */
    static expression_t create_unary(Constants::kind_t, expression_t, position_t = {}, type_t = {});

    /** Create a binary expression */
    static expression_t create_binary(Constants::kind_t, expression_t, expression_t, position_t = {}, type_t = {});

    /** Create a ternary expression */
    static expression_t create_ternary(Constants::kind_t, expression_t, expression_t, expression_t, position_t = {},
                                       type_t = {});

    /** Create an n-ary expression */
    static expression_t create_nary(Constants::kind_t, std::vector<expression_t> sub, position_t = {}, type_t = {});

    /** Create a DOT expression */
    static expression_t create_dot(expression_t, int32_t index, position_t = {}, type_t = {});

    /** Create a SYNC expression */
    static expression_t create_sync(expression_t, Constants::synchronisation_t, position_t = {});

    /** Create a DEADLOCK expression */
    static expression_t create_deadlock(position_t = {});

    static expression_t create_exit(position_t = {});

    // true if empty or equal to 1.
    bool is_true() const;
    int get_precedence() const;
    friend std::ostream& operator<<(std::ostream& o, const UTAP::expression_t& e) { return o << e.str(); }

private:
    std::ostream& print_bound_type(std::ostream& os, expression_t e) const;
};

}  // namespace UTAP

#endif
