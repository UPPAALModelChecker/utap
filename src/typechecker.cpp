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
#include "utap/typechecker.h"

#include "utap/DocumentBuilder.hpp"
#include "utap/featurechecker.h"
#include "utap/utap.h"

#include <cassert>

using namespace UTAP;
using namespace Constants;

/* The following are simple helper functions for testing the type of
 * expressions.
 */
static bool isCost(expression_t expr) { return expr.get_type().is(COST); }

static bool is_void(expression_t expr) { return expr.get_type().is_void(); }

static bool is_double(expression_t expr) { return expr.get_type().is_double(); }

/*
static bool is_string(expression_t expr)
{
    return expr.get_type().is_string();
}
*/
// static bool is_scalar(expression_t expr)
// {
//     return expr.get_type().is_scalar();
// }

static bool is_integer(expression_t expr) { return expr.get_type().is_integer(); }

static bool isBound(expression_t expr) { return expr.get_type().is_integer() || expr.get_type().is_double(); }

static bool is_integral(expression_t expr) { return expr.get_type().is_integral(); }

static bool is_clock(expression_t expr) { return expr.get_type().is_clock(); }

static bool is_diff(expression_t expr) { return expr.get_type().is_diff(); }

static bool is_double_value(expression_t expr) { return is_double(expr) || is_clock(expr) || is_diff(expr); }

static bool is_number(expression_t expr) { return is_double_value(expr) || is_integral(expr); }

static bool is_const_integer(expression_t expr) { return expr.get_kind() == CONSTANT && is_integer(expr); }

static bool is_const_double(expression_t expr) { return expr.get_kind() == CONSTANT && is_double(expr); }

static bool is_invariant(expression_t expr) { return expr.get_type().is_invariant(); }

static bool is_guard(expression_t expr) { return expr.get_type().is_guard(); }

static bool is_probability(expression_t expr) { return expr.get_type().is_probability(); }

static bool is_constraint(expression_t expr) { return expr.get_type().is_constraint(); }

static bool is_formula(expression_t expr) { return expr.get_type().is_formula(); }

static bool is_formula_list(expression_t expr)
{
    if (expr.get_kind() != LIST) {
        return false;
    }

    for (uint32_t i = 0; i < expr.get_size(); ++i) {
        if (!expr[i].get_type().is_formula()) {
            return false;
        }
    }

    return true;
}

static bool hasStrictLowerBound(expression_t expr)
{
    for (size_t i = 0; i < expr.get_size(); ++i) {
        if (hasStrictLowerBound(expr[i])) {
            return true;
        }
    }

    switch (expr.get_kind()) {
    case LT:  // int < clock
        if (is_integral(expr[0]) && is_clock(expr[1])) {
            return true;
        }
        break;
    case GT:  // clock > int
        if (is_clock(expr[0]) && is_integral(expr[1])) {
            return true;
        }
        break;

    default:;
    }

    return false;
}

static bool hasStrictUpperBound(expression_t expr)
{
    for (size_t i = 0; i < expr.get_size(); ++i) {
        if (hasStrictUpperBound(expr[i])) {
            return true;
        }
    }

    switch (expr.get_kind()) {
    case GT:  // int > clock
        if (is_integral(expr[0]) && is_clock(expr[1])) {
            return true;
        }
        break;
    case LT:  // clock < int
        if (is_clock(expr[0]) && is_integral(expr[1])) {
            return true;
        }
        break;

    default:;
    }

    return false;
}

/**
 * Returns true iff type is a valid invariant. A valid invariant is
 * either an invariant expression or an integer expression.
 */
static bool isInvariantWR(expression_t expr) { return is_invariant(expr) || (expr.get_type().is(INVARIANT_WR)); }

/**
 * Returns true if values of this type can be assigned. This is the
 * case for integers, booleans, clocks, cost, scalars and arrays and
 * records of these. E.g. channels and processes are not assignable.
 */
static bool isAssignable(type_t type)
{
    switch (type.get_kind()) {
    case Constants::INT:
    case Constants::BOOL:
    case Constants::DOUBLE:
    case Constants::STRING:
    case Constants::CLOCK:
    case Constants::COST:
    case Constants::SCALAR: return true;

    case ARRAY: return isAssignable(type[0]);

    case RECORD:
        for (size_t i = 0; i < type.size(); i++) {
            if (!isAssignable(type[i])) {
                return false;
            }
        }
        return true;

    default: return type.size() > 0 && isAssignable(type[0]);
    }
}

///////////////////////////////////////////////////////////////////////////

void CompileTimeComputableValues::visitVariable(variable_t& variable)
{
    if (variable.uid.get_type().is_constant()) {
        variables.insert(variable.uid);
    }
}

void CompileTimeComputableValues::visitInstance(instance_t& temp)
{
    for (const auto& param : temp.parameters) {
        type_t type = param.get_type();
        if (!type.is(REF) && type.is_constant() && !type.is_double()) {
            variables.insert(param);
        }
    }
}

void CompileTimeComputableValues::add_symbol(symbol_t symbol) { variables.insert(symbol); }

bool CompileTimeComputableValues::contains(symbol_t symbol) const
{
    return (variables.find(symbol) != variables.end());
}

///////////////////////////////////////////////////////////////////////////

class RateDecomposer
{
public:
    RateDecomposer() = default;
    expression_t costRate;
    expression_t invariant{expression_t::create_constant(1)};
    bool hasStrictInvariant{false}, hasClockRates{false};
    size_t countCostRates{0};

    void decompose(expression_t, bool inforall = false);
};

void RateDecomposer::decompose(expression_t expr, bool inforall)
{
    assert(isInvariantWR(expr));

    if (is_invariant(expr)) {
        if (expr.get_kind() == Constants::LT) {
            hasStrictInvariant = true;  // Strict upper bounds only.
        }
        if (!inforall) {
            invariant = invariant.empty()
                            ? expr
                            : invariant = expression_t::create_binary(AND, invariant, expr, expr.get_position(),
                                                                      type_t::create_primitive(INVARIANT));
        }
    } else if (expr.get_kind() == AND) {
        decompose(expr[0], inforall);
        decompose(expr[1], inforall);
    } else if (expr.get_kind() == EQ) {
        expression_t left, right;
        assert((expr[0].get_type().get_kind() == RATE) ^ (expr[1].get_type().get_kind() == RATE));

        if (expr[0].get_type().get_kind() == RATE) {
            left = expr[0][0];
            right = expr[1];
        } else {
            left = expr[1][0];
            right = expr[0];
        }

        if (isCost(left)) {
            costRate = right;
            countCostRates++;
        } else {
            hasClockRates = true;
            if (!inforall) {
                invariant = invariant.empty() ? expr
                                              : expression_t::create_binary(AND, invariant, expr, expr.get_position(),
                                                                            type_t::create_primitive(INVARIANT_WR));
            }
        }
    } else {
        assert(expr.get_type().is(INVARIANT_WR));
        assert(expr.get_kind() == FORALL);
        // Enter the forall to look for clock rates but don't
        // record them, rather the forall expression.
        decompose(expr[1], true);
        invariant = invariant.empty()
                        ? expr
                        : invariant = expression_t::create_binary(AND, invariant, expr, expr.get_position(),
                                                                  type_t::create_primitive(INVARIANT_WR));
    }
}

///////////////////////////////////////////////////////////////////////////

TypeChecker::TypeChecker(Document& document, bool refinement): document{document}, syncUsed(0)
{
    document.accept(compileTimeComputableValues);

    checkExpression(document.get_before_update());
    checkExpression(document.get_after_update());

    function = nullptr;
    refinementWarnings = refinement;
    temp = nullptr;
}

template <class T>
void TypeChecker::handleWarning(T expr, const std::string& msg)
{
    document.add_warning(expr.get_position(), msg, "(typechecking)");
}

template <class T>
void TypeChecker::handleError(T expr, const std::string& msg)
{
    document.add_error(expr.get_position(), msg, "(typechecking)");
}

/**
 * This method issues warnings for expressions, which do not change
 * any variables. It is expected to be called for all expressions
 * whose value is ignored. Unless such an expression has some kind
 * of side-effect, it does not have any purpose.
 *
 * Notice that in contrast to the regular side-effect analysis,
 * this function accepts modifications of local variables as a
 * side-effect.
 */
void TypeChecker::checkIgnoredValue(expression_t expr)
{
    static const auto message = "$Expression_does_not_have_any_effect";
    if (!expr.changes_any_variable() && expr.get_kind() != FUN_CALL_EXT) {
        handleWarning(expr, message);
    } else if (expr.get_kind() == COMMA && !expr[1].changes_any_variable() && expr[1].get_kind() != FUN_CALL_EXT) {
        handleWarning(expr[1], message);
    }
}

bool TypeChecker::isCompileTimeComputable(expression_t expr) const
{
    /* An expression is compile time computable if all identifers it
     * could possibly access during an evaluation are compile time
     * computable (i.e. their value is known at compile time).
     *
     * FIXME: We could maybe refine this to actually include function
     * local variables with compile time computable initialisers. This
     * would increase the class of models we accept while also getting
     * rid of the compileTimeComputableValues object.
     */
    std::set<symbol_t> reads;
    expr.collect_possible_reads(reads, true);
    return std::all_of(reads.begin(), reads.end(), [this](const symbol_t& s) {
        return s != symbol_t{} && (s.get_type().is_function() || s.get_type().is_function_external() ||
                                   compileTimeComputableValues.contains(s));
    });
}

/**
 * Check that the type is valid, i.e.:
 *
 * - all expressions such as array sizes, integer ranges, etc. are
 *   type correct,
 *
 * - only allowed prefixes are used (e.g. no urgent integers).
 *
 * - array sizes and integer bounds are compile time computable.
 *
 * If \a initialisable is true, then this method also checks that \a
 * type is initialisable.
 */
void TypeChecker::checkType(type_t type, bool initialisable, bool inStruct)
{
    expression_t l, u;
    type_t size;
    frame_t frame;

    switch (type.get_kind()) {
    case LABEL: checkType(type[0], initialisable, inStruct); break;

    case URGENT:
        if (!type.is_location() && !type.is_channel()) {
            handleError(type, "$Prefix_urgent_only_allowed_for_locations_and_channels");
        }
        checkType(type[0], initialisable, inStruct);
        break;

    case BROADCAST:
        if (!type.is_channel()) {
            handleError(type, "$Prefix_broadcast_only_allowed_for_channels");
        }
        checkType(type[0], initialisable, inStruct);
        break;

    case COMMITTED:
        if (!type.is_location()) {
            handleError(type, "$Prefix_committed_only_allowed_for_locations");
        }
        checkType(type[0], initialisable, inStruct);
        break;

    case HYBRID:
        if (!type.is_clock() && !(type.is_array() && type.strip_array().is_clock())) {
            handleError(type, "$Prefix_hybrid_only_allowed_for_clocks");
        }
        checkType(type[0], initialisable, inStruct);
        break;

    case CONSTANT:
        if (type.is_clock()) {
            handleError(type, "$Prefix_const_not_allowed_for_clocks");
        }
        checkType(type[0], true, inStruct);
        break;

    case SYSTEM_META:
        if (type.is_clock()) {
            handleError(type, "$Prefix_meta_not_allowed_for_clocks");
        }
        checkType(type[0], true, inStruct);
        break;

    case REF:
        if (!type.is_integral() && !type.is_array() && !type.is_record() && !type.is_channel() && !type.is_clock() &&
            !type.is_scalar() && !type.is_double() && !type.is_string()) {
            handleError(type, "$Reference_to_this_type_not_allowed");
        }
        checkType(type[0], initialisable, inStruct);
        break;

    case RANGE:
        if (!type.is_integer() && !type.is_scalar()) {
            handleError(type, "$Range_over_this_type_not_allowed");
        }
        std::tie(l, u) = type.get_range();
        if (checkExpression(l)) {
            if (!is_integer(l)) {
                handleError(l, "$Integer_expected");
            }
            if (!isCompileTimeComputable(l)) {
                handleError(l, "$Must_be_computable_at_compile_time");
            }
        }
        if (checkExpression(u)) {
            if (!is_integer(u)) {
                handleError(u, "$Integer_expected");
            }
            if (!isCompileTimeComputable(u)) {
                handleError(u, "$Must_be_computable_at_compile_time");
            }
        }
        break;

    case ARRAY:
        size = type.get_array_size();
        if (!size.is(RANGE)) {
            handleError(type, "$Invalid_array_size");
        } else {
            checkType(size);
        }
        checkType(type[0], initialisable, inStruct);
        break;

    case RECORD:
        for (size_t i = 0; i < type.size(); i++) {
            checkType(type.get_sub(i), true, true);
        }
        break;
    case Constants::STRING:
        if (inStruct) {
            handleError(type, "$This_type_cannot_be_declared_inside_a_struct");
        }
    case Constants::CLOCK:
    case Constants::DOUBLE:
    case Constants::INT:
    case Constants::BOOL: break;

    default:
        if (initialisable) {
            handleError(type, "$This_type_cannot_be_declared_const_or_meta");
        }
    }
}

void TypeChecker::visitDocAfter(Document& doc)
{
    for (const chan_priority_t& i : doc.get_chan_priorities()) {
        bool i_default = (i.head == expression_t());
        if (!i_default && checkExpression(i.head)) {
            expression_t expr = i.head;
            type_t channel = expr.get_type();

            // Check that chanElement is a channel, or an array of channels.
            while (channel.is_array()) {
                channel = channel.get_sub();
            }
            if (!channel.is_channel()) {
                handleError(expr, "$Channel_expected");
            }

            // Check index expressions
            while (expr.get_kind() == ARRAY) {
                if (!isCompileTimeComputable(expr[1])) {
                    handleError(expr[1], "$Must_be_computable_at_compile_time");
                } else if (i.head.changes_any_variable()) {
                    handleError(expr[1], "$Index_must_be_side-effect_free");
                }
                expr = expr[0];
            }
        }

        for (const chan_priority_t::entry& j : i.tail) {
            bool j_default = (j.second == expression_t());
            if (!j_default && checkExpression(j.second)) {
                expression_t expr = j.second;
                type_t channel = expr.get_type();

                // Check that chanElement is a channel, or an array of channels.
                while (channel.is_array()) {
                    channel = channel.get_sub();
                }
                if (!channel.is_channel()) {
                    handleError(expr, "$Channel_expected");
                }

                // Check index expressions
                while (expr.get_kind() == ARRAY) {
                    if (!isCompileTimeComputable(expr[1])) {
                        handleError(expr[1], "$Must_be_computable_at_compile_time");
                    } else if (j.second.changes_any_variable()) {
                        handleError(expr[1], "$Index_must_be_side-effect_free");
                    }
                    expr = expr[0];
                }
            }
        }
    }
}

void TypeChecker::visitHybridClock(expression_t e)
{
    if (checkExpression(e)) {
        if (!is_clock(e)) {
            handleError(e, "$Clock_expected");
        } else if (e.changes_any_variable()) {
            handleError(e, "$Index_must_be_side-effect_free");
        }
        // Should be a check to identify the clock at compile time.
        // Problematic now. Same issue for inf & sup.
    }
}

void TypeChecker::visitIODecl(iodecl_t& iodecl)
{
    for (const auto& e : iodecl.param) {
        if (checkExpression(e)) {
            if (!is_integer(e)) {
                handleError(e, "$Integer_expected");
            } else if (!isCompileTimeComputable(e)) {
                handleError(e, "$Must_be_computable_at_compile_time");
            } else if (e.changes_any_variable()) {
                handleError(e, "$Index_must_be_side-effect_free");
            }
        }
    }

    if (syncUsed == 0) {
        if (!iodecl.inputs.empty() || !iodecl.outputs.empty()) {
            syncUsed = 1;
        } else if (!iodecl.csp.empty()) {
            syncUsed = 2;
        }
    }
    if (syncUsed == 1) {
        if (!iodecl.csp.empty()) {
            syncUsed = -1;
        }
    } else if (syncUsed == 2) {
        if (!iodecl.inputs.empty() || !iodecl.outputs.empty()) {
            syncUsed = -1;
        }
    }
    if (syncUsed == -1) {
        handleError(iodecl.csp.front(), "$CSP_and_IO_synchronisations_cannot_be_mixed");
    }

    document.set_sync_used(syncUsed);

    for (auto expr : iodecl.inputs) {  // intentional copy
        if (checkExpression(expr)) {
            type_t channel = expr.get_type();

            // Check that chanElement is a channel, or an array of channels.
            while (channel.is_array()) {
                channel = channel.get_sub();
            }
            if (!channel.is_channel()) {
                handleError(expr, "$Channel_expected");
            }

            // Check index expressions
            while (expr.get_kind() == ARRAY) {
                if (!isCompileTimeComputable(expr[1])) {
                    handleError(expr[1], "$Must_be_computable_at_compile_time");
                } else if (expr.changes_any_variable()) {
                    handleError(expr[1], "$Index_must_be_side-effect_free");
                }
                expr = expr[0];
            }
        }
    }

    for (auto expr : iodecl.outputs) {  // intentional copy
        if (checkExpression(expr)) {
            type_t channel = expr.get_type();

            // Check that chanElement is a channel, or an array of channels.
            while (channel.is_array()) {
                channel = channel.get_sub();
            }
            if (!channel.is_channel()) {
                handleError(expr, "$Channel_expected");
            }

            // Check index expressions
            while (expr.get_kind() == ARRAY) {
                if (!isCompileTimeComputable(expr[1])) {
                    handleError(expr[1], "$Must_be_computable_at_compile_time");
                } else if (expr.changes_any_variable()) {
                    handleError(expr[1], "$Index_must_be_side-effect_free");
                }
                expr = expr[0];
            }
        }
    }
}

bool isDefaultInt(type_t type)
{
    if (type.is_integral()) {
        auto range = type.get_range();
        return (is_const_integer(range.first) && is_const_integer(range.second)) &&
               range.first.get_value() == defaultIntMin && range.second.get_value() == defaultIntMax;
    }
    return false;
}

void TypeChecker::visitProcess(instance_t& process)
{
    for (size_t i = 0; i < process.unbound; i++) {
        // Unbound parameters of processes must be either scalars or bounded integers.
        symbol_t parameter = process.parameters[i];
        type_t type = parameter.get_type();
        if (!(type.is_scalar() || type.is_range()) || type.is(REF) || isDefaultInt(type)) {
            handleError(process.uid, "$Free_process_parameters_must_be_a_bounded_integer_or_a_scalar");
        }
        /* Unbound parameters must not be used either directly or indirectly in any array size declarations.
         * I.e. they must not be restricted. */
        if (process.restricted.find(parameter) != process.restricted.end()) {
            handleError(process.uid, "$Free_process_parameters_must_not_be_used_directly_or_indirectly_in_"
                                     "an_array_declaration_or_select_expression");
        }
    }
}

void TypeChecker::visitVariable(variable_t& variable)
{
    DocumentVisitor::visitVariable(variable);

    checkType(variable.uid.get_type());
    if (variable.init.is_dynamic() || variable.init.has_dynamic_sub()) {
        handleError(variable.init, "Dynamic constructions cannot be used as initialisers");
    } else if (!variable.init.empty() && checkExpression(variable.init)) {
        if (!isCompileTimeComputable(variable.init)) {
            handleError(variable.init, "$Must_be_computable_at_compile_time");
        } else if (variable.init.changes_any_variable()) {
            handleError(variable.init, "$Initialiser_must_be_side-effect_free");
        } else {
            variable.init = checkInitialiser(variable.uid.get_type(), variable.init);
        }
    }
}

void TypeChecker::visitLocation(location_t& loc)
{
    DocumentVisitor::visitLocation(loc);

    if (!loc.invariant.empty()) {
        auto& inv = loc.invariant;
        if (checkExpression(inv)) {
            if (!isInvariantWR(inv)) {
                std::string s = "$Expression_of_type ";
                s += inv.get_type().str();
                s += " $cannot_be_used_as_an_invariant";
                handleError(inv, s);
            } else if (inv.changes_any_variable()) {
                handleError(inv, "$Invariant_must_be_side-effect_free");
            } else {
                RateDecomposer decomposer;
                decomposer.decompose(inv);
                inv = decomposer.invariant;
                loc.cost_rate = decomposer.costRate;
                if (decomposer.countCostRates > 1) {
                    handleError(inv, "$Only_one_cost_rate_is_allowed");
                }
                if (decomposer.hasClockRates) {
                    document.record_stop_watch();
                }
                if (decomposer.hasStrictInvariant) {
                    document.record_strict_invariant();
                    handleWarning(inv, "$Strict_invariant");
                }
            }
        }
    }
    if (!loc.exp_rate.empty()) {
        const auto& expr = loc.exp_rate;
        if (checkExpression(expr)) {
            if (!is_integral(expr) && expr.get_kind() != FRACTION && !expr.get_type().is_double()) {
                handleError(expr, "$Number_expected");
            }
        }
    }
    if (loc.uid.get_name() == "__RESET__") {
        handleWarning(loc.uid,
                      "Deprecated __RESET__ annotation: use \"{ integers } -> { floats }\" in learning query.");
    }
}

void TypeChecker::visitEdge(edge_t& edge)
{
    DocumentVisitor::visitEdge(edge);

    // select
    frame_t select = edge.select;
    for (size_t i = 0; i < select.get_size(); i++) {
        checkType(select[i].get_type());
    }

    // guard
    bool strictBound = false;
    if (!edge.guard.empty()) {
        if (checkExpression(edge.guard)) {
            if (!is_guard(edge.guard)) {
                std::string s = "$Expression_of_type ";
                s += edge.guard.get_type().str();
                s += " $cannot_be_used_as_a_guard";
                handleError(edge.guard, s);
            } else if (edge.guard.changes_any_variable()) {
                handleError(edge.guard, "$Guard_must_be_side-effect_free");
            }
            if (hasStrictLowerBound(edge.guard)) {
                if (edge.control) {
                    document.record_strict_lower_bound_on_controllable_edges();
                }
                strictBound = true;
            }
            if (hasStrictUpperBound(edge.guard)) {
                strictBound = true;
            }
        }
    }

    // sync
    if (!edge.sync.empty()) {
        if (checkExpression(edge.sync)) {
            type_t channel = edge.sync.get(0).get_type();
            if (!channel.is_channel()) {
                handleError(edge.sync.get(0), "$Channel_expected");
            } else if (edge.sync.changes_any_variable()) {
                handleError(edge.sync, "$Synchronisation_must_be_side-effect_free");
            } else {
                bool hasClockGuard = !edge.guard.empty() && !is_integral(edge.guard);
                bool isUrgent = channel.is(URGENT);
                bool receivesBroadcast = channel.is(BROADCAST) && edge.sync.get_sync() == SYNC_QUE;

                if (isUrgent && hasClockGuard) {
                    document.set_urgent_transition();
                    handleWarning(edge.sync, "$Clock_guards_are_not_allowed_on_urgent_edges");
                } else if (receivesBroadcast && hasClockGuard) {
                    document.clock_guard_recv_broadcast();
                    /*
                      This is now allowed, though it is expensive.

                    handle_error(edge.sync,
                                "$Clock_guards_are_not_allowed_on_broadcast_receivers");
                    */
                }
                if (receivesBroadcast && edge.guard.is_true()) {
                    if (edge.dst == nullptr) {  // dst is null at least in a case of branchpoint
                        handleWarning(edge.sync, "SMC requires input edges to be deterministic");
                    }
#ifndef NDEBUG
                    else if (!edge.dst->invariant.is_true()) {
                        // This case is not handled correctly by the engine and it is expensive to
                        // fix.
                        handleWarning(edge.sync, "$It_may_be_needed_to_add_a_guard_involving_the_target_invariant");
                    }
                    /*
                      The warning above gives too many false alarms and is therefore disabled.
                      In particular it does not consider the common idiom of clock reset (i.e. guard
                      is irrelevant). Details: the above case may lead to violation of target
                      invariant if unchecked, however the invariant *is* being checked in the engine
                      and halts with "violates model sanity with transition" + proper diagnostics
                      about the transition and location.
                    */
#endif /* NDEBUG */
                }
                if (isUrgent && strictBound) {
                    handleWarning(edge.guard, "$Strict_bounds_on_urgent_edges_may_not_make_sense");
                }
            }

            switch (syncUsed) {
            case 0:
                switch (edge.sync.get_sync()) {
                case SYNC_BANG:
                case SYNC_QUE: syncUsed = 1; break;
                case SYNC_CSP: syncUsed = 2; break;
                }
                break;
            case 1:
                switch (edge.sync.get_sync()) {
                case SYNC_BANG:
                case SYNC_QUE:
                    // ok
                    break;
                case SYNC_CSP: syncUsed = -1; break;
                }
                break;
            case 2:
                switch (edge.sync.get_sync()) {
                case SYNC_BANG:
                case SYNC_QUE: syncUsed = -1; break;
                case SYNC_CSP:
                    // ok
                    break;
                }
                break;
            default:
                // nothing
                ;
            }
            if (syncUsed == -1) {
                handleError(edge.sync, "$CSP_and_IO_synchronisations_cannot_be_mixed");
            }

            if (refinementWarnings) {
                if (edge.sync.get_sync() == SYNC_BANG) {
                    if (edge.control) {
                        handleWarning(edge.sync, "$Outputs_should_be_uncontrollable_for_refinement_checking");
                    }
                } else if (edge.sync.get_sync() == SYNC_QUE) {
                    if (!edge.control) {
                        handleWarning(edge.sync, "$Inputs_should_be_controllable_for_refinement_checking");
                    }
                } else {
                    handleWarning(edge.sync, "$CSP_synchronisations_are_incompatible_with_refinement_checking");
                }
            }
        }
    }

    // assignment
    checkAssignmentExpression(edge.assign);

    // probability
    if (!edge.prob.empty()) {
        if (checkExpression(edge.prob)) {
            if (!is_probability(edge.prob)) {
                std::string s = "$Expression_of_type ";
                s += edge.prob.get_type().str();
                s += " $cannot_be_used_as_a_probability";
                handleError(edge.prob, s);
            } else if (edge.prob.changes_any_variable()) {
                handleError(edge.prob, "$Probability_must_be_side-effect_free");
            }
        }
    }
}

void TypeChecker::visitInstanceLine(instance_line_t& instance) { DocumentVisitor::visitInstanceLine(instance); }

void TypeChecker::visitMessage(message_t& message)
{
    DocumentVisitor::visitMessage(message);

    if (!message.label.empty()) {
        if (checkExpression(message.label)) {
            type_t channel = message.label.get(0).get_type();
            if (!channel.is_channel()) {
                handleError(message.label.get(0), "$Channel_expected");
            } else if (message.label.changes_any_variable()) {
                handleError(message.label, "$Message_must_be_side-effect_free");
            }
        }
    }
}
void TypeChecker::visitCondition(condition_t& condition)
{
    DocumentVisitor::visitCondition(condition);
    if (!condition.label.empty()) {
        if (checkExpression(condition.label)) {
            if (!is_guard(condition.label)) {
                std::string s = "$Expression_of_type ";
                s += condition.label.get_type().str();
                s += " $cannot_be_used_as_a_condition";
                handleError(condition.label, s);
            } else if (condition.label.changes_any_variable()) {
                handleError(condition.label, "$Condition_must_be_side-effect_free");
            }
        }
    }
}
void TypeChecker::visitUpdate(update_t& update)
{
    DocumentVisitor::visitUpdate(update);
    if (!update.label.empty()) {
        checkAssignmentExpression(update.label);
    }
}

void TypeChecker::visitProgressMeasure(progress_t& progress)
{
    checkExpression(progress.guard);
    checkExpression(progress.measure);

    if (!progress.guard.empty() && !is_integral(progress.guard)) {
        handleError(progress.guard, "$Progress_guard_must_evaluate_to_a_boolean");
    }

    if (!is_integral(progress.measure)) {
        handleError(progress.measure, "$Progress_measure_must_evaluate_to_a_value");
    }
}

void TypeChecker::visitGanttChart(gantt_t& gc)
{
    size_t n = gc.parameters.get_size();
    for (size_t i = 0; i < n; ++i) {
        checkType(gc.parameters[i].get_type());
    }

    std::list<ganttmap_t>::const_iterator first, end = gc.mapping.end();
    for (first = gc.mapping.begin(); first != end; ++first) {
        n = (*first).parameters.get_size();
        for (size_t i = 0; i < n; ++i) {
            checkType((*first).parameters[i].get_type());
        }

        const expression_t& p = (*first).predicate;
        checkExpression(p);
        if (!is_integral(p) && !is_constraint(p)) {
            handleError(p, "$Boolean_expected");
        }

        const expression_t& m = (*first).mapping;
        checkExpression(m);
        if (!is_integral(m)) {
            handleError(m, "$Integer_expected");
        }
    }
}

void TypeChecker::visitInstance(instance_t& instance)
{
    DocumentVisitor::visitInstance(instance);

    /* Check the parameters of the instance.
     */
    type_t type = instance.uid.get_type();
    for (size_t i = 0; i < type.size(); i++) {
        checkType(type[i]);
    }

    /* Check arguments.
     */
    for (size_t i = type.size(); i < type.size() + instance.arguments; i++) {
        symbol_t parameter = instance.parameters[i];
        expression_t argument = instance.mapping[parameter];

        if (!checkExpression(argument)) {
            continue;
        }

        // For template instantiation, the argument must be side-effect free
        if (argument.changes_any_variable()) {
            handleError(argument, "$Argument_must_be_side-effect_free");
            continue;
        }

        // We have three ok cases:
        // - Value parameter with computable argument
        // - Constant reference with computable argument
        // - Reference parameter with unique lhs argument
        // If non of the cases are true, then we generate an error
        bool ref = parameter.get_type().is(REF);
        bool constant = parameter.get_type().is_constant();
        bool computable = isCompileTimeComputable(argument);

        if ((!ref && !computable) || (ref && !constant && !isUniqueReference(argument)) ||
            (ref && constant && !computable)) {
            handleError(argument, "$Incompatible_argument");
            continue;
        }

        checkParameterCompatible(parameter.get_type(), argument);
    }
}

static bool isGameProperty(expression_t expr)
{
    switch (expr.get_kind()) {
    case ATL_ENFORCE_UNTIL:
    case ATL_DESPITE_UNTIL:
    case ATL_ENFORCE_F:
    case ATL_DESPITE_F:
    case ATL_ENFORCE_G:
    case ATL_DESPITE_G:
    case ATL_ENFORCE_NEXT:
    case ATL_DESPITE_NEXT:
    case CONTROL:
    case SMC_CONTROL:
    case EF_CONTROL:
    case CONTROL_TOPT:
    case PO_CONTROL:
    case CONTROL_TOPT_DEF1:
    case CONTROL_TOPT_DEF2: return true;
    default: return false;
    }
}

static bool hasMITLInQuantifiedSub(expression_t expr)
{
    bool hasIt = (expr.get_kind() == MITL_FORALL || expr.get_kind() == MITL_EXISTS);
    if (!hasIt) {
        for (uint32_t i = 0; i < expr.get_size(); i++) {
            hasIt |= hasMITLInQuantifiedSub(expr.get(i));
        }
    }
    return hasIt;
}

static bool hasSpawnOrExit(expression_t expr)
{
    bool hasIt = (expr.get_kind() == SPAWN || expr.get_kind() == EXIT);
    if (!hasIt) {
        for (uint32_t i = 0; i < expr.get_size(); i++) {
            hasIt |= hasSpawnOrExit(expr.get(i));
        }
    }
    return hasIt;
}

void TypeChecker::visitProperty(expression_t expr)
{
    if (checkExpression(expr)) {
        if (expr.changes_any_variable()) {
            handleError(expr, "$Property_must_be_side-effect_free");
        }
        if (expr.get_kind() == LOAD_STRAT || expr.get_kind() == SAVE_STRAT) {
            if (!expr.get(0).get_type().is_string()) {
                handleError(expr, "$loadStrategy_and_saveStrategy_expect_a_string");
            }
            return;
        }
        if (!is_formula(expr)) {
            handleError(expr, "$Property_must_be_a_valid_formula");
        }
        if (isGameProperty(expr)) {
            /*
            for (uint32_t i = 0; i < expr.get_size(); i++)
            {
                if (is_formula(expr[i]))
                {
                    for (uint32_t j = 0; j < expr[i].get_size(); j++)
                    {
                        if (!is_constraint(expr[i][j]))
                        {
                            handle_error(expr[i][j], "$Nesting_of_path_quantifiers_is_not_allowed");
                        }
                    }
                }
            }
            */
        } else if (auto k = expr.get_kind(); k != SUP_VAR && k != INF_VAR && k != BOUNDS_VAR && k != SCENARIO &&
                                             k != PROBA_MIN_BOX && k != PROBA_MIN_DIAMOND && k != PROBA_BOX &&
                                             k != PROBA_DIAMOND && k != PROBA_EXP && k != PROBA_CMP && k != SIMULATE &&
                                             k != SIMULATEREACH && k != MITL_FORMULA &&
                                             k != MIN_EXP &&  // ALREADY CHECKED IN PARSE
                                             k != MAX_EXP)    // ALREADY CHECKED IN PARSE
        {
            for (uint32_t i = 0; i < expr.get_size(); i++) {
                /* No nesting except for constraints */
                if (!is_constraint(expr[i])) {
                    handleError(expr[i], "$Nesting_of_path_quantifiers_is_not_allowed");
                }
            }
        }
        if (expr.get_kind() == PO_CONTROL) {
            /* Observations on clock constraints are limited to be
             * weak for lower bounds and strict for upper bounds.
             */
            checkObservationConstraints(expr);
        }
        if (hasMITLInQuantifiedSub(expr) && expr.get_kind() != MITL_FORMULA) {
            handleError(expr, "MITL inside forall or exists in non-MITL property");
        }
    }
}

/**
 * Checks that \a expr is a valid assignment expression. Errors or
 * warnings are issued via calls to handle_error() and
 * handle_warning(). Returns true if no errors were issued, false
 * otherwise.
 *
 * An assignment expression is any:
 *
 *  - expression of an expression statement,
 *
 *  - initialisation or step expression in a for-clause
 *
 *  - expression in the update field of an edge
 *
 *  - expression in the label field of an update (LSC)
 */
bool TypeChecker::checkAssignmentExpression(expression_t expr)
{
    if (!checkExpression(expr)) {
        return false;
    }

    if (!isAssignable(expr.get_type()) && !is_void(expr)) {
        handleError(expr, "$Invalid_assignment_expression");
        return false;
    }

    if (expr.get_kind() != FUN_CALL_EXT && (expr.get_kind() != CONSTANT || expr.get_value() != 1)) {
        checkIgnoredValue(expr);
    }

    return true;
}

/** Checks that the expression can be used as a condition (e.g. for if). */
bool TypeChecker::checkConditionalExpressionInFunction(expression_t expr)
{
    if (!(is_integral(expr) || is_constraint(expr))) {
        handleError(expr, "$Boolean_expected");
        return false;
    }
    return true;
}

void TypeChecker::checkObservationConstraints(expression_t expr)
{
    for (size_t i = 0; i < expr.get_size(); ++i) {
        checkObservationConstraints(expr[i]);
    }

    bool invalid = false;

    switch (expr.get_kind()) {
    case LT:  // int < clock
    case GE:  // int >= clock
        invalid = is_integral(expr[0]) && is_clock(expr[1]);
        break;

    case LE:  // clock <= int
    case GT:  // clock > int
        invalid = is_clock(expr[0]) && is_integral(expr[1]);
        break;

    case EQ:   // clock == int || int == clock
    case NEQ:  // clock != int || int != clock
        invalid = (is_clock(expr[0]) && is_integral(expr[1])) || (is_integral(expr[0]) && is_clock(expr[1]));
        break;

    default:;
    }

    if (invalid) {
        handleError(expr, "$Clock_lower_bound_must_be_weak_and_upper_bound_strict");
    } else {
        switch (expr.get_kind())  // No clock differences.
        {
        case LT:
        case LE:
        case GT:
        case GE:
        case EQ:
        case NEQ:
            if ((is_clock(expr[0]) && is_clock(expr[1])) || (is_diff(expr[0]) && is_integer(expr[1])) ||
                (is_integer(expr[0]) && is_diff(expr[1]))) {
                handleError(expr, "$Clock_differences_are_not_supported");
            }
            break;

        default:;
        }
    }
}

static bool validReturnType(type_t type)
{
    frame_t frame;

    switch (type.get_kind()) {
    case Constants::RECORD:
        for (size_t i = 0; i < type.size(); i++) {
            if (!validReturnType(type[i])) {
                return false;
            }
        }
        return true;

    case Constants::RANGE:
    case Constants::LABEL: return validReturnType(type[0]);

    case Constants::INT:
    case Constants::BOOL:
    case Constants::SCALAR:
    case Constants::DOUBLE: return true;

    default: return false;
    }
}

void TypeChecker::visitFunction(function_t& fun)
{
    DocumentVisitor::visitFunction(fun);
    /* Check that the return type is consistent and is a valid return
     * type.
     */
    type_t return_type = fun.uid.get_type()[0];
    checkType(return_type);
    if (!return_type.is_void() && !validReturnType(return_type)) {
        handleError(return_type, "$Invalid_return_type");
    }

    /* Type check the function body: Type checking return statements
     * requires access to the return type, hence we store a pointer to
     * the current function being type checked in the \a function
     * member.
     */
    function = &fun;
    fun.body->accept(this);
    function = nullptr;

    /* Check if there are dynamic expressions in the function body*/
    checkDynamicExpressions(fun.body.get());

    /* Collect identifiers of things external to the function accessed
     * or changed by the function. Notice that neither local variables
     * nor parameters are considered to be changed or accessed by a
     * function.
     */
    CollectChangesVisitor visitor(fun.changes);
    fun.body->accept(&visitor);

    CollectDependenciesVisitor visitor2(fun.depends);
    fun.body->accept(&visitor2);

    for (const auto& var : fun.variables) {
        fun.changes.erase(var.uid);
        fun.depends.erase(var.uid);
    }
    size_t parameters = fun.uid.get_type().size() - 1;
    for (uint32_t i = 0; i < parameters; i++) {
        fun.changes.erase(fun.body->get_frame()[i]);
        fun.depends.erase(fun.body->get_frame()[i]);
    }
}

int32_t TypeChecker::visitEmptyStatement(EmptyStatement* stat) { return 0; }

int32_t TypeChecker::visitExprStatement(ExprStatement* stat)
{
    checkAssignmentExpression(stat->expr);
    return 0;
}

int32_t TypeChecker::visitAssertStatement(AssertStatement* stat)
{
    if (checkExpression(stat->expr) && stat->expr.changes_any_variable()) {
        handleError(stat->expr, "$Assertion_must_be_side-effect_free");
    }
    return 0;
}

int32_t TypeChecker::visitForStatement(ForStatement* stat)
{
    checkAssignmentExpression(stat->init);

    if (checkExpression(stat->cond)) {
        checkConditionalExpressionInFunction(stat->cond);
    }

    checkAssignmentExpression(stat->step);

    return stat->stat->accept(this);
}

int32_t TypeChecker::visitIterationStatement(IterationStatement* stat)
{
    type_t type = stat->symbol.get_type();
    checkType(type);

    /* We only support iteration over scalars and integers.
     */
    if (!type.is_scalar() && !type.is_integer()) {
        handleError(type, "$Scalar_set_or_integer_expected");
    } else if (!type.is(RANGE)) {
        handleError(type, "$Range_expected");
    }

    return stat->stat->accept(this);
}

int32_t TypeChecker::visitWhileStatement(WhileStatement* stat)
{
    if (checkExpression(stat->cond)) {
        checkConditionalExpressionInFunction(stat->cond);
    }
    return stat->stat->accept(this);
}

int32_t TypeChecker::visitDoWhileStatement(DoWhileStatement* stat)
{
    if (checkExpression(stat->cond)) {
        checkConditionalExpressionInFunction(stat->cond);
    }
    return stat->stat->accept(this);
}

int32_t TypeChecker::visitBlockStatement(BlockStatement* stat)
{
    BlockStatement::iterator i;

    /* Check type and initialiser of local variables (parameters are
     * also considered local variables).
     */
    frame_t frame = stat->get_frame();
    for (uint32_t i = 0; i < frame.get_size(); ++i) {
        symbol_t symbol = frame[i];
        checkType(symbol.get_type());
        if (auto* d = symbol.get_data(); d) {
            variable_t* var = static_cast<variable_t*>(d);
            if (!var->init.empty() && checkExpression(var->init)) {
                if (var->init.changes_any_variable()) {
                    /* This is stronger than C. However side-effects in
                     * initialisers are nasty: For records, the evaluation
                     * order may be different from the order in the input
                     * file.
                     */
                    handleError(var->init, "$Initialiser_must_be_side-effect_free");
                } else {
                    var->init = checkInitialiser(symbol.get_type(), var->init);
                }
            }
        }
    }

    /* Check statements.
     */
    for (const auto& s : *stat)
        s->accept(this);
    return 0;
}

int32_t TypeChecker::visitIfStatement(IfStatement* stat)
{
    if (checkExpression(stat->cond)) {
        checkConditionalExpressionInFunction(stat->cond);
    }
    stat->trueCase->accept(this);
    if (stat->falseCase) {
        stat->falseCase->accept(this);
    }
    return 0;
}

int32_t TypeChecker::visitReturnStatement(ReturnStatement* stat)
{
    if (!stat->value.empty()) {
        checkExpression(stat->value);

        /* The only valid return types are integers and records. For these
         * two types, the type rules are the same as for parameters.
         */
        type_t return_type = function->uid.get_type()[0];
        checkParameterCompatible(return_type, stat->value);
    }
    return 0;
}

/**
 * Returns a value indicating the capabilities of a channel. For
 * urgent channels this is 0, for non-urgent broadcast channels this
 * is 1, and in all other cases 2. An argument to a channel parameter
 * must have at least the same capability as the parameter.
 */
static int channelCapability(type_t type)
{
    assert(type.is_channel());
    if (type.is(URGENT)) {
        return 0;
    }
    if (type.is(BROADCAST)) {
        return 1;
    }
    return 2;
}

/**
 * Returns true if two scalar types are name-equivalent.
 */
static bool isSameScalarType(type_t t1, type_t t2)
{
    if (t1.get_kind() == REF || t1.get_kind() == CONSTANT || t1.get_kind() == SYSTEM_META) {
        return isSameScalarType(t1[0], t2);
    } else if (t2.get_kind() == EF || t2.get_kind() == CONSTANT || t2.get_kind() == SYSTEM_META) {
        return isSameScalarType(t1, t2[0]);
    } else if (t1.get_kind() == LABEL && t2.get_kind() == LABEL) {
        return t1.get_label(0) == t2.get_label(0) && isSameScalarType(t1[0], t2[0]);
    } else if (t1.get_kind() == SCALAR && t2.get_kind() == SCALAR) {
        return true;
    } else if (t1.get_kind() == RANGE && t2.get_kind() == RANGE) {
        return isSameScalarType(t1[0], t2[0]) && t1.get_range().first.equal(t2.get_range().first) &&
               t1.get_range().second.equal(t2.get_range().second);
    } else {
        return false;
    }
}

/**
 * Returns true iff argument type is compatible with parameter type.
 */
bool TypeChecker::isParameterCompatible(type_t paramType, expression_t arg)
{
    bool ref = paramType.is(REF);
    bool constant = paramType.is_constant();
    bool lvalue = isModifiableLValue(arg);
    type_t argType = arg.get_type();
    // For non-const reference parameters, we require a modifiable
    // lvalue argument
    if (ref && !constant && !lvalue) {
        return false;
    }

    if (paramType.is_channel() && argType.is_channel()) {
        return channelCapability(argType) >= channelCapability(paramType);
    } else if (ref && lvalue) {
        return areEquivalent(argType, paramType);
    } else {
        return areAssignmentCompatible(paramType, argType);
    }
}

/**
 * Checks whether argument type is compatible with parameter type.
 */
bool TypeChecker::checkParameterCompatible(type_t paramType, expression_t arg)
{
    if (!isParameterCompatible(paramType, arg)) {
        handleError(arg, "$Incompatible_argument");
        return false;
    }
    return true;
}

/**
 * Checks whether init is a valid initialiser for a variable or
 * constant of the given type. For record types, the initialiser is
 * reordered to fit the order of the fields and the new initialiser is
 * returned. REVISIT: Can a record initialiser have side-effects? Then
 * such reordering is not valid.
 */
expression_t TypeChecker::checkInitialiser(type_t type, expression_t init)
{
    if (areAssignmentCompatible(type, init.get_type(), true)) {
        return init;
    } else if (type.is_array() && init.get_kind() == LIST) {
        type_t subtype = type.get_sub();
        std::vector<expression_t> result(init.get_size(), expression_t());
        for (uint32_t i = 0; i < init.get_type().size(); i++) {
            if (!init.get_type().get_label(i).empty()) {
                handleError(init[i], "$Field_name_not_allowed_in_array_initialiser");
            }
            result[i] = checkInitialiser(subtype, init[i]);
        }
        return expression_t::create_nary(LIST, result, init.get_position(), type);
    } else if (type.is_record() && init.get_kind() == LIST) {
        /* In order to access the record labels we have to strip any
         * prefixes and labels from the record type.
         */
        std::vector<expression_t> result(type.get_record_size(), expression_t());
        uint32_t current = 0;
        for (uint32_t i = 0; i < init.get_type().size(); ++i, ++current) {
            std::string label = init.get_type().get_label(i);
            if (!label.empty()) {
                auto index = type.find_index_of(label);
                if (!index) {
                    handleError(init[i], "$Unknown_field");
                    break;
                } else {
                    current = *index;
                }
            }

            if (current >= type.get_record_size()) {
                handleError(init[i], "$Too_many_elements_in_initialiser");
                break;
            }

            if (!result[current].empty()) {
                handleError(init[i], "$Multiple_initialisers_for_field");
                continue;
            }

            result[current] = checkInitialiser(type.get_sub(current), init[i]);
        }

        // Check that all fields do have an initialiser.
        for (size_t i = 0; i < result.size(); i++) {
            if (result[i].empty()) {
                handleError(init, "$Incomplete_initialiser");
                break;
            }
        }

        return expression_t::create_nary(LIST, result, init.get_position(), type);
    }
    handleError(init, "$Invalid_initialiser");
    return init;
}

/** Returns true if arguments of an inline if are compatible. The
    'then' and 'else' arguments are compatible if and only if they
    have the same base type. In case of arrays, they must have the
    same size and the subtypes must be compatible. In case of records,
    they must have the same type name.
*/
bool TypeChecker::areInlineIfCompatible(type_t result_type, type_t t1, type_t t2) const
{
    if (areAssignmentCompatible(result_type, t1) && areAssignmentCompatible(result_type, t1))
        return true;

    return areEquivalent(t1, t2);
}

type_t TypeChecker::getInlineIfCommonType(type_t t1, type_t t2) const
{
    if (t1.is_record())
        return t1;
    else if (t2.is_record())
        return t2;
    else if (t1.is_clock() && !t2.is_clock() || !t1.is_clock() && t2.is_clock())
        return type_t{DOUBLE, {}, 0};
    else if (TypeChecker::areAssignmentCompatible(t1, t2))
        return t1;
    else if (TypeChecker::areAssignmentCompatible(t2, t1))
        return t2;
    else if (TypeChecker::areEquivalent(t2, t1))
        return t1;
    else
        return type_t{};
}

/**
 * Returns true iff \a a and \a b are structurally
 * equivalent. However, CONST, SYSTEM_META, and REF are ignored. Scalar sets
 * are checked using named equivalence.
 */
bool TypeChecker::areEquivalent(type_t a, type_t b)
{
    if (a.is_integer() && b.is_integer()) {
        return !a.is(RANGE) || !b.is(RANGE) ||
               (a.get_range().first.equal(b.get_range().first) && a.get_range().second.equal(b.get_range().second));
    } else if (a.isBoolean() && b.isBoolean()) {
        return true;
    } else if (a.is_clock() && b.is_clock()) {
        return true;
    } else if (a.is_channel() && b.is_channel()) {
        return channelCapability(a) == channelCapability(b);
    } else if (a.is_record() && b.is_record()) {
        size_t aSize = a.get_record_size();
        size_t bSize = b.get_record_size();
        if (aSize == bSize) {
            for (size_t i = 0; i < aSize; i++) {
                if (a.get_record_label(i) != b.get_record_label(i) || !areEquivalent(a.get_sub(i), b.get_sub(i))) {
                    return false;
                }
            }
            return true;
        }
    } else if (a.is_array() && b.is_array()) {
        type_t asize = a.get_array_size();
        type_t bsize = b.get_array_size();

        if (asize.is_integer() && bsize.is_integer()) {
            return asize.get_range().first.equal(bsize.get_range().first) &&
                   asize.get_range().second.equal(bsize.get_range().second) && areEquivalent(a.get_sub(), b.get_sub());
        } else if (asize.is_scalar() && bsize.is_scalar()) {
            return isSameScalarType(asize, bsize) && areEquivalent(a.get_sub(), b.get_sub());
        }
        return false;
    } else if (a.is_scalar() && b.is_scalar()) {
        return isSameScalarType(a, b);
    } else if (a.is_double() && b.is_double()) {
        return true;
    } else if (a.is_string() && b.is_string()) {
        return true;
    }

    return false;
}

/** Returns true if lvalue and rvalue are assignment compatible.  This
    is the case when an expression of type rvalue can be assigned to
    an expression of type lvalue. It does not check whether lvalue is
    actually a left-hand side value. In case of integers, it does not
    check the range of the expressions.
*/
bool TypeChecker::areAssignmentCompatible(type_t lvalue, type_t rvalue, bool init) const
{
    if (init ? ((lvalue.is_clock() && (rvalue.is_double() || rvalue.is_integral())) ||
                (lvalue.is_double() && (rvalue.is_integral() || rvalue.is_double())))
             : ((lvalue.is_clock() || lvalue.is_double()) &&
                (rvalue.is_integral() || rvalue.is_double() || rvalue.is_clock()))) {
        return true;
    } else if (lvalue.is_integral() && rvalue.is_integral()) {
        return true;
    }
    return areEquivalent(lvalue, rvalue);
}

/**
 * Returns true if two types are compatible for comparison using the
 * equality operator.
 *
 * Two types are compatible if they are structurally
 * equivalent. However for scalar we use name equivalence.  Prefixes
 * like CONST, SYSTEM_META, URGENT, COMMITTED, BROADCAST, REF and TYPENAME
 * are ignored.
 *
 * Clocks are not handled by this method: If t1 or t2 are clock-types,
 * then false is returned.
 * REVISIT: This should be updated.
 */
bool TypeChecker::areEqCompatible(type_t t1, type_t t2) const
{
    if (t1.is_integral() && t2.is_integral()) {
        return true;
    } else if (t1.is(PROCESS_VAR) && t2.is(PROCESS_VAR)) {
        return true;
    } else {
        return areEquivalent(t1, t2);
    }
}

/** Type check and checkExpression the expression. This function performs
    basic type checking of the given expression and assigns a type to
    every subexpression of the expression. It checks that only
    left-hand side values are updated, checks that functions are
    called with the correct arguments, checks that operators are used
    with the correct operands and checks that operands to assignment
    operators are assignment compatible. Errors are reported by
    calling handle_error(). This function does not check/compute the
    range of integer expressions and thus does not produce
    out-of-range errors or warnings. Returns true if no type errors
    were found, false otherwise.
*/
bool TypeChecker::checkExpression(expression_t expr)
{
    /* Do not check empty expressions.
     */
    if (expr.empty())
        return true;

    /* CheckExpression sub-expressions.
     */
    bool ok = true;
    for (uint32_t i = 0; i < expr.get_size(); i++)
        ok &= checkExpression(expr[i]);

    /* Do not checkExpression the expression if any of the sub-expressions
     * contained errors.
     */
    if (!ok)
        return false;

    /* CheckExpression the expression. This depends on the kind of expression
     * we are dealing with.
     */
    type_t type, arg1, arg2, arg3;
    switch (expr.get_kind()) {
        // It is possible to have DOT expressions as data.x
        // with data being an array of struct. The type checker
        // is broken and trying
        // expr[0].get_type().is_record() or
        // expr[0].is_process() cannot detect this.
        // This should be fixed one day.
        /*
    case DOT:
        if (expr[0].get_type().is_process(Constants::PROCESS) ||
            expr[0].get_type().is(Constants::RECORD))
        {
            return true;
        }
        else
        {
            handle_error(expr, "$Invalid_type");
            return false;
        }
        */
    case SUM_DYNAMIC:
        if (is_integral(expr[2]) || is_double_value(expr[2])) {
            type = expr[2].get_type();
        } else if (is_invariant(expr[2]) || is_guard(expr[2])) {
            type = type_t::create_primitive(Constants::DOUBLE_INV_GUARD);
        } else {
            handleError(expr, "A sum can only  be made over integer, double, invariant or guard expressions.");
            return false;
        }
        break;
    case FRACTION:
        if (is_integral(expr[0]) && is_integral(expr[1])) {
            type = type_t::create_primitive(Constants::FRACTION);
        }
        break;

    case PLUS:
        if (is_integral(expr[0]) && is_integral(expr[1])) {
            type = type_t::create_primitive(Constants::INT);
        } else if ((is_integer(expr[0]) && is_clock(expr[1])) || (is_clock(expr[0]) && is_integer(expr[1]))) {
            type = type_t::create_primitive(CLOCK);
        } else if ((is_diff(expr[0]) && is_integer(expr[1])) || (is_integer(expr[0]) && is_diff(expr[1]))) {
            type = type_t::create_primitive(DIFF);
        } else if (is_number(expr[0]) && is_number(expr[1])) {
            // SMC extension.
            type = type_t::create_primitive(Constants::DOUBLE);
        }
        break;

    case MINUS:
        if (is_integral(expr[0]) && is_integral(expr[1])) {
            type = type_t::create_primitive(Constants::INT);
        } else if (is_clock(expr[0]) && is_integer(expr[1]))
        // removed  "|| is_integer(expr[0].type) && is_clock(expr[1].type)"
        // in order to be able to convert into ClockGuards
        {
            type = type_t::create_primitive(CLOCK);
        } else if ((is_diff(expr[0]) && is_integer(expr[1])) || (is_integer(expr[0]) && is_diff(expr[1])) ||
                   (is_clock(expr[0]) && is_clock(expr[1]))) {
            type = type_t::create_primitive(DIFF);
        } else if (is_number(expr[0]) && is_number(expr[1])) {
            // SMC extension.
            // x-y with that semantic should be written x+(-y)
            type = type_t::create_primitive(Constants::DOUBLE);
        }
        break;

    case AND:
        if (is_integral(expr[0]) && is_integral(expr[1])) {
            type = type_t::create_primitive(Constants::BOOL);
        } else if (is_invariant(expr[0]) && is_invariant(expr[1])) {
            type = type_t::create_primitive(INVARIANT);
        } else if (isInvariantWR(expr[0]) && isInvariantWR(expr[1])) {
            type = type_t::create_primitive(INVARIANT_WR);
        } else if (is_guard(expr[0]) && is_guard(expr[1])) {
            type = type_t::create_primitive(GUARD);
        } else if (is_constraint(expr[0]) && is_constraint(expr[1])) {
            type = type_t::create_primitive(CONSTRAINT);
        } else if (is_formula(expr[0]) && is_formula(expr[1])) {
            type = type_t::create_primitive(FORMULA);
        }
        break;

    case OR:
        if (is_integral(expr[0]) && is_integral(expr[1])) {
            type = type_t::create_primitive(Constants::BOOL);
        } else if (is_integral(expr[0]) && is_invariant(expr[1])) {
            type = type_t::create_primitive(INVARIANT);
        } else if (is_invariant(expr[0]) && is_integral(expr[1])) {
            type = type_t::create_primitive(INVARIANT);
        } else if (is_integral(expr[0]) && isInvariantWR(expr[1])) {
            type = type_t::create_primitive(INVARIANT_WR);
        } else if (isInvariantWR(expr[0]) && is_integral(expr[1])) {
            type = type_t::create_primitive(INVARIANT_WR);
        } else if (is_integral(expr[0]) && is_guard(expr[1])) {
            type = type_t::create_primitive(GUARD);
        } else if (is_guard(expr[0]) && is_integral(expr[1])) {
            type = type_t::create_primitive(GUARD);
        } else if (is_constraint(expr[0]) && is_constraint(expr[1])) {
            type = type_t::create_primitive(CONSTRAINT);
        }
        break;

    case XOR:
        if (is_integral(expr[0]) && is_integral(expr[1])) {
            type = type_t::create_primitive(Constants::BOOL);
        }
        break;

    case SPAWN: {
        template_t* temp = document.find_dynamic_template(expr[0].get_symbol().get_name());
        if (!temp) {
            handleError(expr, "It appears your trying to spawn a non-dynamic template");
            return false;
        }
        if (temp->parameters.get_size() != expr.get_size() - 1) {
            handleError(expr, "Wrong number of arguments");
            return false;
        }
        for (size_t i = 0; i < temp->parameters.get_size(); i++) {
            if (!checkSpawnParameterCompatible(temp->parameters[i].get_type(), expr[i + 1])) {
                return false;
            }
        }

        /* check that spawn is only made for templates with definitions*/
        if (!temp->is_defined) {
            handleError(expr, "Template is only declared - not defined");
            return false;
        }
        type = type_t::create_primitive(Constants::INT);
        break;
    }

    case NUMOF: {
        template_t* temp = document.find_dynamic_template(expr[0].get_symbol().get_name());
        if (temp) {
            type = type_t::create_primitive(Constants::INT);
        } else {
            handleError(expr, "Not a dynamic template");
            return false;
        }
        break;
    }

    case EXIT: {
        assert(temp);
        if (!temp->dynamic) {
            handleError(expr, "Exit can only be used in templates declared as dynamic");
            return false;
        }

        type = type_t::create_primitive(Constants::INT);

        break;
    }

    case LT:
    case LE:
        if (is_integral(expr[0]) && is_integral(expr[1])) {
            type = type_t::create_primitive(Constants::BOOL);
        } else if ((is_clock(expr[0]) && is_clock(expr[1])) || (is_clock(expr[0]) && isBound(expr[1])) ||
                   (is_clock(expr[1]) && isBound(expr[0])) || (is_diff(expr[0]) && isBound(expr[1])) ||
                   (isBound(expr[0]) && is_diff(expr[1]))) {
            type = type_t::create_primitive(INVARIANT);
        } else if (is_number(expr[0]) && is_clock(expr[1])) {
            type = type_t::create_primitive(GUARD);
        } else if (is_clock(expr[0]) && is_number(expr[1])) {
            type = type_t::create_primitive(GUARD);
        } else if (is_number(expr[0]) && is_number(expr[1])) {
            type = type_t::create_primitive(Constants::BOOL);
        }
        break;

    case EQ:
        // FIXME: Apparently the case cost == expr goes through, which is obviously not good.

        if ((is_clock(expr[0]) && is_clock(expr[1])) || (is_clock(expr[0]) && is_number(expr[1])) ||
            (is_number(expr[0]) && is_clock(expr[1])) || (is_diff(expr[0]) && is_number(expr[1])) ||
            (is_number(expr[0]) && is_diff(expr[1]))) {
            type = type_t::create_primitive(GUARD);
        } else if (areEqCompatible(expr[0].get_type(), expr[1].get_type())) {
            type = type_t::create_primitive(Constants::BOOL);
        } else if ((expr[0].get_type().is(RATE) && (is_integral(expr[1]) || is_double_value(expr[1]))) ||
                   ((is_integral(expr[0]) || is_double_value(expr[0])) && expr[1].get_type().is(RATE))) {
            type = type_t::create_primitive(INVARIANT_WR);
        } else if (is_number(expr[0]) && is_number(expr[1])) {
            type = type_t::create_primitive(Constants::BOOL);
        }
        break;

    case NEQ:
        if (areEqCompatible(expr[0].get_type(), expr[1].get_type())) {
            type = type_t::create_primitive(Constants::BOOL);
        } else if ((is_clock(expr[0]) && is_clock(expr[1])) || (is_clock(expr[0]) && is_integer(expr[1])) ||
                   (is_integer(expr[0]) && is_clock(expr[1])) || (is_diff(expr[0]) && is_integer(expr[1])) ||
                   (is_integer(expr[0]) && is_diff(expr[1]))) {
            type = type_t::create_primitive(CONSTRAINT);
        } else if (is_number(expr[0]) && is_number(expr[1])) {
            type = type_t::create_primitive(Constants::BOOL);
        }
        break;

    case GE:
    case GT:
        if (is_integral(expr[0]) && is_integral(expr[1])) {
            type = type_t::create_primitive(Constants::BOOL);
        } else if ((is_clock(expr[0]) && is_clock(expr[1])) || (is_integer(expr[0]) && is_clock(expr[1])) ||
                   (is_integer(expr[1]) && is_clock(expr[0])) || (is_diff(expr[0]) && is_integer(expr[1])) ||
                   (is_integer(expr[0]) && is_diff(expr[1]))) {
            type = type_t::create_primitive(INVARIANT);
        } else if (is_number(expr[0]) && is_clock(expr[1])) {
            type = type_t::create_primitive(GUARD);
        } else if (is_clock(expr[0]) && is_number(expr[1])) {
            type = type_t::create_primitive(GUARD);
        } else if (is_number(expr[0]) && is_number(expr[1])) {
            type = type_t::create_primitive(Constants::BOOL);
        }
        break;

    case MULT:
    case DIV:
    case POW:
    case MIN:
    case MAX:
        if (is_integral(expr[0]) && is_integral(expr[1])) {
            type = type_t::create_primitive(Constants::INT);
        } else if (is_number(expr[0]) && is_number(expr[1])) {
            type = type_t::create_primitive(Constants::DOUBLE);
        }
        break;

    case MOD:
    case BIT_AND:
    case BIT_OR:
    case BIT_XOR:
    case BIT_LSHIFT:
    case BIT_RSHIFT:
        if (is_integral(expr[0]) && is_integral(expr[1])) {
            type = type_t::create_primitive(Constants::INT);
        }
        break;

    case NOT:
        if (is_integral(expr[0])) {
            type = type_t::create_primitive(Constants::BOOL);
        } else if (is_constraint(expr[0])) {
            type = type_t::create_primitive(CONSTRAINT);
        }
        break;

    case UNARY_MINUS:
        if (is_integral(expr[0])) {
            type = type_t::create_primitive(Constants::INT);
        } else if (is_number(expr[0])) {
            type = type_t::create_primitive(Constants::DOUBLE);
        }
        break;

    case RATE:
        if (isCost(expr[0]) || is_clock(expr[0])) {
            type = type_t::create_primitive(RATE);
        }
        break;

    case ASSIGN:
        if (!areAssignmentCompatible(expr[0].get_type(), expr[1].get_type())) {
            handleError(expr, "$Incompatible_types");
            return false;
        } else if (!isModifiableLValue(expr[0])) {
            handleError(expr[0], "$Left_hand_side_value_expected");
            return false;
        }
        type = expr[0].get_type();
        break;

    case ASS_PLUS:
        if ((!is_integer(expr[0]) && !isCost(expr[0])) || !is_integral(expr[1])) {
            handleError(expr, "$Increment_operator_can_only_be_used_for_integers_and_cost_variables");
        } else if (!isModifiableLValue(expr[0])) {
            handleError(expr[0], "$Left_hand_side_value_expected");
        }
        type = expr[0].get_type();
        break;

    case ASS_MINUS:
    case ASS_DIV:
    case ASS_MOD:
    case ASS_MULT:
    case ASS_AND:
    case ASS_OR:
    case ASS_XOR:
    case ASS_LSHIFT:
    case ASS_RSHIFT:
        if (!is_integral(expr[0]) || !is_integral(expr[1])) {
            handleError(expr, "$Non-integer_types_must_use_regular_assignment_operator");
            return false;
        } else if (!isModifiableLValue(expr[0])) {
            handleError(expr[0], "$Left_hand_side_value_expected");
            return false;
        }
        type = expr[0].get_type();
        break;

    case POST_INCREMENT:
    case PRE_INCREMENT:
    case POST_DECREMENT:
    case PRE_DECREMENT:
        if (!isModifiableLValue(expr[0])) {
            handleError(expr[0], "$Left_hand_side_value_expected");
            return false;
        } else if (!is_integer(expr[0])) {
            handleError(expr, "$Integer_expected");
            return false;
        }
        type = type_t::create_primitive(Constants::INT);
        break;

    case FMA_F:
    case RANDOM_TRI_F:
        if (!is_number(expr[2])) {
            handleError(expr[2], "$Number_expected");
            return false;
        }  // fall-through to check the second argument:
        [[fallthrough]];
    case FMOD_F:
    case FMAX_F:
    case FMIN_F:
    case FDIM_F:
    case POW_F:
    case HYPOT_F:
    case ATAN2_F:
    case NEXT_AFTER_F:
    case COPY_SIGN_F:
    case RANDOM_ARCSINE_F:
    case RANDOM_BETA_F:
    case RANDOM_GAMMA_F:
    case RANDOM_NORMAL_F:
    case RANDOM_WEIBULL_F:
        if (!is_number(expr[1])) {
            handleError(expr[1], "$Number_expected");
            return false;
        }  // fall-through to check the first argument:
        [[fallthrough]];
    case FABS_F:
    case EXP_F:
    case EXP2_F:
    case EXPM1_F:
    case LN_F:
    case LOG_F:
    case LOG10_F:
    case LOG2_F:
    case LOG1P_F:
    case SQRT_F:
    case CBRT_F:
    case SIN_F:
    case COS_F:
    case TAN_F:
    case ASIN_F:
    case ACOS_F:
    case ATAN_F:
    case SINH_F:
    case COSH_F:
    case TANH_F:
    case ASINH_F:
    case ACOSH_F:
    case ATANH_F:
    case ERF_F:
    case ERFC_F:
    case TGAMMA_F:
    case LGAMMA_F:
    case CEIL_F:
    case FLOOR_F:
    case TRUNC_F:
    case ROUND_F:
    case LOGB_F:
    case RANDOM_F:
    case RANDOM_POISSON_F:
        if (!is_number(expr[0])) {
            handleError(expr[0], "$Number_expected");
            return false;
        }
        type = type_t::create_primitive(Constants::DOUBLE);
        break;

    case LDEXP_F:
        if (!is_integral(expr[1])) {
            handleError(expr[1], "$Integer_expected");
            return false;
        }
        if (!is_number(expr[0])) {
            handleError(expr[0], "$Number_expected");
            return false;
        }
        type = type_t::create_primitive(Constants::DOUBLE);
        break;

    case ABS_F:
    case FP_CLASSIFY_F:
        if (!is_integral(expr[0])) {
            handleError(expr[0], "$Integer_expected");
            return false;
        }
        type = type_t::create_primitive(Constants::INT);
        break;

    case ILOGB_F:
    case FINT_F:
        if (!is_number(expr[0])) {
            handleError(expr[0], "$Number_expected");
            return false;
        }
        type = type_t::create_primitive(Constants::INT);
        break;

    case IS_FINITE_F:
    case IS_INF_F:
    case IS_NAN_F:
    case IS_NORMAL_F:
    case SIGNBIT_F:
    case IS_UNORDERED_F:
        if (!is_number(expr[0])) {
            handleError(expr[0], "$Number_expected");
            return false;
        }
        type = type_t::create_primitive(Constants::BOOL);
        break;

    case INLINE_IF:
        if (!(is_integral(expr[0]) || is_guard(expr[0]))) {
            handleError(expr, "$First_argument_of_inline_if_must_be_an_integer");
            return false;
        }

        type = getInlineIfCommonType(expr[1].get_type(), expr[2].get_type());
        if (!areInlineIfCompatible(type, expr[1].get_type(), expr[2].get_type())) {
            handleError(expr, "$Incompatible_arguments_to_inline_if");
            return false;
        }
        break;

    case COMMA:
        if (!isAssignable(expr[0].get_type()) && !is_void(expr[0])) {
            handleError(expr[0], "$Incompatible_type_for_comma_expression");
            return false;
        }
        if (!isAssignable(expr[1].get_type()) && !is_void(expr[1])) {
            handleError(expr[1], "$Incompatible_type_for_comma_expression");
            return false;
        }
        checkIgnoredValue(expr[0]);
        type = expr[1].get_type();
        break;

    case FUN_CALL:
    case FUN_CALL_EXT: {
        checkExpression(expr[0]);

        bool result = true;
        type_t type = expr[0].get_type();
        size_t parameters = type.size() - 1;
        for (uint32_t i = 0; i < parameters; i++) {
            type_t parameter = type[i + 1];
            expression_t argument = expr[i + 1];
            result &= checkParameterCompatible(parameter, argument);
        }
        return result;
    }

    case ARRAY:
        arg1 = expr[0].get_type();
        arg2 = expr[1].get_type();

        /* The left side must be an array.
         */
        if (!arg1.is_array()) {
            handleError(expr[0], "$Array_expected");
            return false;
        }
        type = arg1.get_sub();

        /* Check the type of the index.
         */
        if (arg1.get_array_size().is_integer() && arg2.is_integral()) {
        } else if (arg1.get_array_size().is_scalar() && arg2.is_scalar()) {
            if (!isSameScalarType(arg1.get_array_size(), arg2)) {
                handleError(expr[1], "$Incompatible_type");
                return false;
            }
        } else {
            handleError(expr[1], "$Incompatible_type");
        }
        break;

    case FORALL:
        compileTimeComputableValues.add_symbol(expr[0].get_symbol());
        checkType(expr[0].get_symbol().get_type());

        if (is_integral(expr[1])) {
            type = type_t::create_primitive(Constants::BOOL);
        } else if (is_invariant(expr[1])) {
            type = type_t::create_primitive(INVARIANT);
        } else if (isInvariantWR(expr[1])) {
            type = type_t::create_primitive(INVARIANT_WR);
        } else if (is_guard(expr[1])) {
            type = type_t::create_primitive(GUARD);
        } else if (is_constraint(expr[1])) {
            type = type_t::create_primitive(CONSTRAINT);
        } else {
            handleError(expr[1], "$Boolean_expected");
        }

        if (expr[1].changes_any_variable()) {
            handleError(expr[1], "$Expression_must_be_side-effect_free");
        }
        break;

    case EXISTS:
        compileTimeComputableValues.add_symbol(expr[0].get_symbol());
        checkType(expr[0].get_symbol().get_type());

        if (is_integral(expr[1])) {
            type = type_t::create_primitive(Constants::BOOL);
        } else if (is_constraint(expr[1])) {
            type = type_t::create_primitive(CONSTRAINT);
        } else {
            handleError(expr[1], "$Boolean_expected");
        }

        if (expr[1].changes_any_variable()) {
            handleError(expr[1], "$Expression_must_be_side-effect_free");
        }
        break;

    case SUM:
        compileTimeComputableValues.add_symbol(expr[0].get_symbol());
        checkType(expr[0].get_symbol().get_type());

        if (is_integral(expr[1])) {
            type = type_t::create_primitive(Constants::INT);
        } else if (is_number(expr[1])) {
            type = type_t::create_primitive(Constants::DOUBLE);
        } else {
            handleError(expr[1], "$Number_expected");
        }

        if (expr[1].changes_any_variable()) {
            handleError(expr[1], "$Expression_must_be_side-effect_free");
        }
        break;

    case ATL_ENFORCE_UNTIL:
    case ATL_DESPITE_UNTIL:
    case ATL_ENFORCE_F:
    case ATL_DESPITE_F:
    case ATL_ENFORCE_G:
    case ATL_DESPITE_G:
    case ATL_ENFORCE_NEXT:
    case ATL_DESPITE_NEXT: {
        bool isUntil = expr.get_kind() == ATL_ENFORCE_UNTIL || expr.get_kind() == ATL_DESPITE_UNTIL;
        int numPlayer = expr.get_size() - (isUntil ? 2 : 1);
        for (int i = 0; i < numPlayer; ++i) {
        }
        if (is_formula(expr[numPlayer]) && (!isUntil || is_formula(expr[numPlayer + 1]))) {
            type = type_t::create_primitive(FORMULA);
        }
        break;
    }
    case AF:
    case AG:
    case EF:
    case EG:
    case EF_CONTROL:
    case CONTROL:
    case CONTROL_TOPT:
    case CONTROL_TOPT_DEF1:
    case CONTROL_TOPT_DEF2:
    case PMAX:
        if (is_formula(expr[0])) {
            type = type_t::create_primitive(FORMULA);
        }
        break;

    case PO_CONTROL:
        if (is_formula_list(expr[0]) && is_formula(expr[1])) {
            type = type_t::create_primitive(FORMULA);
        }
        break;

    case LEADS_TO:
    case SCENARIO2:
    case A_UNTIL:
    case A_WEAK_UNTIL:
    case A_BUCHI:
        if (is_formula(expr[0]) && is_formula(expr[1])) {
            type = type_t::create_primitive(FORMULA);
        }
        break;

    case SCENARIO: type = type_t::create_primitive(FORMULA); break;

    case SIMULATEREACH:
    case SIMULATE: {
        if (!is_const_integer(expr[0])) {
            handleError(expr[0], "$Integer_expected");
            return false;
        }
        if (!is_const_integer(expr[1]) && !is_clock(expr[1])) {
            handleError(expr[1], "$Clock_expected");
            return false;
        }
        if (!isCompileTimeComputable(expr[2])) {
            handleError(expr[1], "$Must_be_computable_at_compile_time");
            return false;
        }
        if (!is_integral(expr[2])) {
            handleError(expr[2], "$Integer_expected");
            return false;
        }
        int nb = expr.get_size();
        if (expr.get_kind() == SIMULATEREACH) {
            bool ok = true;
            nb -= 2;
            if (!is_const_integer(expr[nb + 1])) {  // check number of accepting runs is an integer
                handleError(expr[nb + 1], "$Integer_expected");
                return false;
            }
            if (!is_integral(expr[nb]) && !is_constraint(expr[nb + 1])) {  // check reachability expression is a boolean
                handleError(expr[nb], "$Boolean_expected");
                ok = false;
            }
            if (expr[nb].changes_any_variable()) {  // check reachability expression is side effect free
                handleError(expr[nb], "$Property_must_be_side-effect_free");
                ok = false;
            }
            if (!ok)
                return false;
        }
        for (int i = 3; i < nb; ++i) {
            if (!is_integral(expr[i]) && !is_clock(expr[i]) && !is_double_value(expr[i]) &&
                !expr[i].get_type().is(Constants::DOUBLE_INV_GUARD) && !is_constraint(expr[i]) &&
                !expr[i].get_type().is_record() && !expr[i].get_type().is_array()) {
                handleError(expr[i], "$Integer_or_clock_expected");
                return false;
            }
            if (expr[i].changes_any_variable()) {
                handleError(expr[i], "$Property_must_be_side-effect_free");
                return false;
            }
        }
        type = type_t::create_primitive(FORMULA);
        break;
    }

    case SUP_VAR:
    case INF_VAR:
    case BOUNDS_VAR:
        if (!is_integral(expr[0]) && !is_constraint(expr[0])) {
            handleError(expr[0], "$Boolean_expected");
            return false;
        }
        if (expr[1].get_kind() == LIST) {
            for (uint32_t i = 0; i < expr[1].get_size(); ++i) {
                if (is_integral(expr[1][i])) {
                    if (expr[1][i].changes_any_variable()) {
                        handleError(expr[1][i], "$Expression_must_be_side-effect_free");
                        return false;
                    }
                } else if (!is_clock(expr[1][i])) {
                    handleError(expr[1][i], "$Type_error");
                    return false;
                }
            }
            type = type_t::create_primitive(FORMULA);
        }
        break;

    case MITL_FORMULA:
    case MITL_CONJ:
    case MITL_DISJ:
    case MITL_NEXT:
    case MITL_UNTIL:
    case MITL_RELEASE:
    case MITL_ATOM:
        type = type_t::create_primitive(FORMULA);
        // TODO
        break;
    case MIN_EXP:
    case MAX_EXP:
        // 0 = bound clock, 1 = boundvar, 2 = goal, 3 = price
        if (!is_const_integer(expr[0]) && !is_clock(expr[0])) {
            handleError(expr[0], "$Clock_expected");
            ok = false;
        }
        if (!isCompileTimeComputable(expr[1])) {
            handleError(expr[1], "$Must_be_computable_at_compile_time");
            ok = false;
        }
        if (!ok)
            return false;

        if (is_formula(expr[2]))
            type = type_t::create_primitive(FORMULA);

        for (size_t i = 3; i < expr.get_size(); ++i) {
            if (expr[i].changes_any_variable()) {
                handleError(expr[i], "$Property_must_be_side-effect_free");
                return false;
            }
        }
        break;
    case SMC_CONTROL:
        if (expr.get_size() == 3) {
            ok &= checkBoundTypeOrBoundedExpr(expr[0]);
            ok &= checkBound(expr[1]);
            if (!ok)
                return false;
            if (is_formula(expr[2])) {
                type = type_t::create_primitive(FORMULA);
            }
        } else {
            handleError(expr, "Bug: wrong number of arguments");
            return false;
        }
        break;

    case PROBA_MIN_BOX:
    case PROBA_MIN_DIAMOND:
        if (expr.get_size() == 5) {
            bool ok = true;
            ok &= checkNrOfRuns(expr[0]);
            if (ok && expr[0].get_value() > 0) {
                handleError(expr[0], "Explicit number of runs is not supported here");
                ok = false;
            }
            ok &= checkBoundTypeOrBoundedExpr(expr[1]);
            ok &= checkBound(expr[2]);
            ok &= checkPredicate(expr[3]);
            ok &= checkProbBound(expr[4]);
            if (!ok)
                return false;
            type = type_t::create_primitive(FORMULA);
        } else {
            handleError(expr, "Bug: wrong number of arguments");
            return false;
        }
        break;

    case PROBA_BOX:
    case PROBA_DIAMOND:
        if (expr.get_size() == 5) {
            bool ok = true;
            ok &= checkNrOfRuns(expr[0]);
            ok &= checkBoundTypeOrBoundedExpr(expr[1]);
            ok &= checkBound(expr[2]);
            ok &= checkPredicate(expr[3]);
            ok &= checkUntilCond(expr.get_kind(), expr[4]);
            if (!ok)
                return false;
            type = type_t::create_primitive(FORMULA);
        } else {
            handleError(expr, "Bug: wrong number of arguments in Pr[](<>)");
            return false;
        }
        break;

    case PROBA_CMP:
        if (expr.get_size() == 8) {
            bool ok = true;
            // the first prob property:
            ok &= checkBoundTypeOrBoundedExpr(expr[0]);
            ok &= checkBound(expr[1]);
            ok &= checkPathQuant(expr[2]);
            ok &= checkPredicate(expr[3]);
            // the second prob property:
            ok &= checkBoundTypeOrBoundedExpr(expr[4]);
            ok &= checkBound(expr[5]);
            ok &= checkPathQuant(expr[6]);
            ok &= checkPredicate(expr[7]);
            if (!ok)
                return false;
            type = type_t::create_primitive(FORMULA);
        } else {
            handleError(expr, "Bug: wrong number of arguments in Pr[]() <=> Pr[]()");
            return false;
        }
        break;
    case PROBA_EXP:
        if (expr.get_size() == 5) {
            bool ok = true;
            ok &= checkNrOfRuns(expr[0]);
            ok &= checkBoundTypeOrBoundedExpr(expr[1]);
            ok &= checkBound(expr[2]);
            ok &= checkAggregationOp(expr[3]);
            ok &= checkMonitoredExpr(expr[4]);
            if (!ok)
                return false;
            type = type_t::create_primitive(FORMULA);
        } else {
            handleError(expr, "Bug: wrong number of arguments in E[...]()");
            return false;
        }
        break;
    default: return true;
    }

    if (type.unknown()) {
        handleError(expr, "$Type_error");
        return false;
    } else {
        expr.set_type(type);
        return true;
    }
}

/**
 * Returns true if expression evaluates to a modifiable l-value.
 */
bool TypeChecker::isModifiableLValue(expression_t expr) const
{
    type_t t, f;
    switch (expr.get_kind()) {
    case IDENTIFIER: return expr.get_type().is_mutable();

    case DOT:
        /* Processes can only be used in properties, which must be
         * side-effect anyway. Therefore returning false below is
         * acceptable for now (REVISIT).
         */
        if (expr[0].get_type().is_process()) {
            return false;
        }
        // REVISIT: Not correct if records contain constant fields.
        return isModifiableLValue(expr[0]);

    case ARRAY: return isModifiableLValue(expr[0]);

    case PRE_INCREMENT:
    case PRE_DECREMENT:
    case ASSIGN:
    case ASS_PLUS:
    case ASS_MINUS:
    case ASS_DIV:
    case ASS_MOD:
    case ASS_MULT:
    case ASS_AND:
    case ASS_OR:
    case ASS_XOR:
    case ASS_LSHIFT:
    case ASS_RSHIFT: return true;

    case INLINE_IF:
        return isModifiableLValue(expr[1]) && isModifiableLValue(expr[2]) &&
               areEquivalent(expr[1].get_type(), expr[2].get_type());

    case COMMA: return isModifiableLValue(expr[1]);

    case FUN_CALL:
    case FUN_CALL_EXT:
        // Functions cannot return references (yet!)

    default: return false;
    }
}

/**
 * Returns true iff \a expr evaluates to an lvalue.
 */
bool TypeChecker::isLValue(expression_t expr) const
{
    type_t t, f;
    switch (expr.get_kind()) {
    case IDENTIFIER:
    case PRE_INCREMENT:
    case PRE_DECREMENT:
    case ASSIGN:
    case ASS_PLUS:
    case ASS_MINUS:
    case ASS_DIV:
    case ASS_MOD:
    case ASS_MULT:
    case ASS_AND:
    case ASS_OR:
    case ASS_XOR:
    case ASS_LSHIFT:
    case ASS_RSHIFT: return true;

    case DOT:
    case ARRAY: return isLValue(expr[0]);

    case INLINE_IF:
        return isLValue(expr[1]) && isLValue(expr[2]) && areEquivalent(expr[1].get_type(), expr[2].get_type());

    case COMMA: return isLValue(expr[1]);

    case FUN_CALL:
    case FUN_CALL_EXT:
        // Functions cannot return references (yet!)

    default: return false;
    }
}

/** Returns true if expression is a reference to a unique variable.
    This is similar to expr being an l-value, but in addition we
    require that the reference does not depend on any non-computable
    expressions. Thus i[v] is a l-value, but if v is a non-constant
    variable, then it does not result in a unique reference.
*/
bool TypeChecker::isUniqueReference(expression_t expr) const
{
    switch (expr.get_kind()) {
    case IDENTIFIER: return true;

    case DOT: return isUniqueReference(expr[0]);

    case ARRAY: return isUniqueReference(expr[0]) && isCompileTimeComputable(expr[1]);

    case PRE_INCREMENT:
    case PRE_DECREMENT:
    case ASSIGN:
    case ASS_PLUS:
    case ASS_MINUS:
    case ASS_DIV:
    case ASS_MOD:
    case ASS_MULT:
    case ASS_AND:
    case ASS_OR:
    case ASS_XOR:
    case ASS_LSHIFT:
    case ASS_RSHIFT: return isUniqueReference(expr[0]);

    case INLINE_IF: return false;

    case COMMA: return isUniqueReference(expr[1]);

    case FUN_CALL:
    case FUN_CALL_EXT:
        // Functions cannot return references (yet!)

    default: return false;
    }
}

static void static_analysis(Document& doc)
{
    if (!doc.has_errors()) {
        auto checker = TypeChecker{doc};
        doc.accept(checker);
        auto fchecker = FeatureChecker{doc};
        doc.set_supported_methods(fchecker.get_supported_methods());
    }
}

bool parse_XTA(FILE* file, Document* doc, bool newxta)
{
    DocumentBuilder builder(*doc);
    parse_XTA(file, &builder, newxta);
    static_analysis(*doc);
    return !doc->has_errors();
}

bool parse_XTA(const char* buffer, Document* doc, bool newxta)
{
    DocumentBuilder builder(*doc);
    parse_XTA(buffer, &builder, newxta);
    static_analysis(*doc);
    return !doc->has_errors();
}

int32_t parse_XML_buffer(const char* buffer, Document* doc, bool newxta,
                         const std::vector<std::filesystem::path>& paths)
{
    auto builder = DocumentBuilder{*doc, paths};
    int err = parse_XML_buffer(buffer, &builder, newxta);

    if (err)
        return err;

    static_analysis(*doc);

    return 0;
}

int32_t parse_XML_file(const char* file, Document* doc, bool newxta, const std::vector<std::filesystem::path>& paths)
{
    auto builder = DocumentBuilder{*doc, paths};
    int err = parse_XML_file(file, &builder, newxta);
    if (err) {
        return err;
    }

    static_analysis(*doc);

    return 0;
}

int32_t parse_XML_fd(int fd, Document* doc, bool newxta, const std::vector<std::filesystem::path>& paths)
{
    auto builder = DocumentBuilder{*doc, paths};
    int err = parse_XML_fd(fd, &builder, newxta);
    if (err) {
        return err;
    }

    static_analysis(*doc);

    return 0;
}

expression_t parseExpression(const char* str, Document* doc, bool newxtr)
{
    ExpressionBuilder builder{*doc};
    parse_XTA(str, &builder, newxtr, S_EXPRESSION, "");
    expression_t expr = builder.getExpressions()[0];
    if (!doc->has_errors()) {
        TypeChecker checker{*doc};
        checker.checkExpression(expr);
    }
    return expr;
}

void TypeChecker::visitTemplateAfter(template_t& t)
{
    assert(&t == temp);
    temp = nullptr;
}

bool TypeChecker::visitTemplateBefore(template_t& t)
{
    assert(!temp);
    temp = &t;
    return true;
}

bool TypeChecker::checkSpawnParameterCompatible(type_t param, expression_t arg)
{
    return checkParameterCompatible(param, arg);
}

bool TypeChecker::checkDynamicExpressions(Statement* stat)
{
    std::list<expression_t> expr_list;
    CollectDynamicExpressions e(expr_list);
    stat->accept(&e);
    bool ok = true;
    for (const auto& expr : expr_list) {
        ok = false;
        handleError(expr, "Dynamic constructs are only allowed on edges!");
    }
    return ok;
}

bool TypeChecker::checkNrOfRuns(const expression_t& runs)
{
    if (!isCompileTimeComputable(runs)) {
        handleError(runs, "$Must_be_computable_at_compile_time");
        return false;
    }
    if (!is_const_integer(runs)) {
        handleError(runs, "$Integer_expected");
        return false;
    }
    return true;
}

bool TypeChecker::checkBoundTypeOrBoundedExpr(const expression_t& boundTypeOrExpr)
{
    if (!is_const_integer(boundTypeOrExpr) && !is_clock(boundTypeOrExpr)) {
        handleError(boundTypeOrExpr, "$Clock_expected");
        return false;
    }
    return true;
}

bool TypeChecker::checkBound(const expression_t& bound)
{
    if (!isCompileTimeComputable(bound)) {
        handleError(bound, "$Must_be_computable_at_compile_time");
        return false;
    }
    if (!is_integral(bound)) {
        handleError(bound, "$Integer_expected");
        return false;
    }
    return true;
}

bool TypeChecker::checkPredicate(const expression_t& predicate)
{
    if (!is_integral(predicate) && !is_constraint(predicate)) {  // check reachability expression is a boolean
        handleError(predicate, "$Boolean_expected");
        return false;
    }
    if (predicate.changes_any_variable()) {  // check reachability expression is side effect free
        handleError(predicate, "$Property_must_be_side-effect_free");
        return false;
    }
    return true;
}

bool TypeChecker::checkProbBound(const expression_t& probBound)
{
    if (!is_const_double(probBound)) {
        handleError(probBound, "Floating point number expected as probability bound");
        return false;
    }
    return true;
}

bool TypeChecker::checkUntilCond(kind_t kind, const expression_t& untilCond)
{
    bool ok = true;
    if (kind == PROBA_DIAMOND && !is_integral(untilCond) && !is_constraint(untilCond)) {
        handleError(untilCond, "$Boolean_expected");
        ok = false;
    }
    if (kind == PROBA_BOX && untilCond.get_kind() == Constants::BOOL && untilCond.get_value() != 0) {
        handleError(untilCond, "Must be false");  // TODO - error message
        ok = false;
    }
    return ok;
}

bool TypeChecker::checkMonitoredExpr(const expression_t& expr)
{
    if (!is_integral(expr) && !is_clock(expr) && !is_double_value(expr) &&
        !expr.get_type().is(Constants::DOUBLE_INV_GUARD) && !is_constraint(expr)) {
        handleError(expr, "$Integer_or_clock_expected");
        return false;
    }
    if (expr.changes_any_variable()) {
        handleError(expr, "$Property_must_be_side-effect_free");
        return false;
    }
    return true;
}

bool TypeChecker::checkPathQuant(const expression_t& expr)
{
    if (!is_const_integer(expr)) {
        handleError(expr, "Bug: bad path quantifier");
        return false;
    }
    return true;
}

bool TypeChecker::checkAggregationOp(const expression_t& expr)
{
    if (!is_const_integer(expr)) {
        handleError(expr, "Bug: bad aggregation operator expression");
        return false;
    }
    if (expr.get_value() > 1)  // 0="min", 1="max"
    {
        handleError(expr, "Bug: bad aggregation operator value");
        return false;
    }
    return true;
}
