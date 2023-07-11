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

#include "utap/expression.h"

#include "utap/document.h"

#include <algorithm>
#include <functional>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <variant>
#include <cassert>
#include <cstring>

using namespace UTAP;
using namespace Constants;

using std::make_pair;
using std::map;
using std::max;
using std::min;
using std::ostream;
using std::pair;
using std::set;
using std::vector;

struct expression_t::expression_data : public std::enable_shared_from_this<expression_t::expression_data>
{
    position_t position; /**< The position of the expression */
    kind_t kind;         /**< The kind of the node */

    std::variant<int32_t, synchronisation_t, double, StringIndex> value;

    symbol_t symbol;                 /**< The symbol of the node */
    type_t type;                     /**< The type of the expression */
    std::vector<expression_t> sub{}; /**< Subexpressions */
    expression_data(const position_t& p, kind_t kind, int32_t value): position{p}, kind{kind}, value{value} {}
};

expression_t::expression_t(kind_t kind, const position_t& pos)
{
    data = std::make_shared<expression_data>(pos, kind, 0);
}

expression_t expression_t::clone() const
{
    auto expr = expression_t{data->kind, data->position};
    expr.data->value = data->value;
    expr.data->type = data->type;
    expr.data->symbol = data->symbol;
    expr.data->sub.reserve(data->sub.size());
    expr.data->sub.assign(data->sub.begin(), data->sub.end());
    return expr;
}

expression_t expression_t::clone_deeper() const
{
    auto expr = expression_t{data->kind, data->position};
    expr.data->value = data->value;
    expr.data->type = data->type;
    expr.data->symbol = data->symbol;
    if (!data->sub.empty()) {
        expr.data->sub.reserve(data->sub.size());
        for (const auto& s : data->sub)
            expr.data->sub.push_back(s.clone_deeper());
    }
    return expr;
}

expression_t expression_t::clone_deeper(symbol_t from, symbol_t to) const
{
    auto expr = expression_t{data->kind, data->position};
    expr.data->value = data->value;
    expr.data->type = data->type;
    expr.data->symbol = (data->symbol == from) ? to : data->symbol;

    if (!data->sub.empty()) {
        expr.data->sub.reserve(data->sub.size());
        for (const auto& s : data->sub)
            expr.data->sub.push_back(s.clone_deeper(from, to));
    }
    return expr;
}

expression_t expression_t::clone_deeper(frame_t frame, frame_t select) const
{
    auto expr = expression_t{data->kind, data->position};
    expr.data->value = data->value;
    expr.data->type = data->type;
    symbol_t uid;
    if (data->symbol != symbol_t()) {
        bool res = frame.resolve(data->symbol.get_name(), uid);
        if (!res && select != frame_t()) {
            res = select.resolve(data->symbol.get_name(), uid);
        }
        assert(res);
        expr.data->symbol = uid;
    } else {
        expr.data->symbol = data->symbol;
    }

    if (!data->sub.empty()) {
        expr.data->sub.reserve(data->sub.size());
        for (const auto& s : data->sub)
            expr.data->sub.push_back(s.clone_deeper(frame, select));
    }
    return expr;
}

expression_t expression_t::subst(symbol_t symbol, expression_t expr) const
{
    if (empty()) {
        return *this;
    } else if (get_kind() == IDENTIFIER && get_symbol() == symbol) {
        return expr;
    } else if (get_size() == 0) {
        return *this;
    } else {
        expression_t e = clone();
        for (size_t i = 0; i < get_size(); i++) {
            e[i] = e[i].subst(symbol, expr);
        }
        return e;
    }
}

kind_t expression_t::get_kind() const
{
    assert(data);
    return data->kind;
}

const position_t& expression_t::get_position() const
{
    assert(data);
    return data->position;
}

bool expression_t::uses_fp() const
{
    if (empty()) {
        return false;
    }
    if (data->type.is(Constants::DOUBLE)) {
        return true;
    }
    switch (data->kind) {
    case FABS_F:
    case FMOD_F:
    case FMA_F:
    case FMAX_F:
    case FMIN_F:
    case FDIM_F:
    case EXP_F:
    case EXP2_F:
    case EXPM1_F:
    case LN_F:
    case LOG_F:
    case LOG10_F:
    case LOG2_F:
    case LOG1P_F:
    case POW_F:
    case SQRT_F:
    case CBRT_F:
    case HYPOT_F:
    case SIN_F:
    case COS_F:
    case TAN_F:
    case ASIN_F:
    case ACOS_F:
    case ATAN_F:
    case ATAN2_F:
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
    case FINT_F:
    case LDEXP_F:
    case ILOGB_F:
    case LOGB_F:
    case NEXT_AFTER_F:
    case COPY_SIGN_F:
    case FP_CLASSIFY_F:
    case IS_FINITE_F:
    case IS_INF_F:
    case IS_NAN_F:
    case IS_NORMAL_F:
    case SIGNBIT_F:
    case IS_UNORDERED_F:
    case RANDOM_F:
    case RANDOM_ARCSINE_F:
    case RANDOM_BETA_F:
    case RANDOM_GAMMA_F:
    case RANDOM_NORMAL_F:
    case RANDOM_POISSON_F:
    case RANDOM_TRI_F:
    case RANDOM_WEIBULL_F: return true;

    default:;
    }

    size_t n = get_size();
    for (size_t i = 0; i < n; ++i) {
        if (get(i).uses_fp()) {
            return true;
        }
    }

    return false;
}

bool expression_t::uses_hybrid() const
{
    if (empty()) {
        return false;
    }
    if (get_type().is(HYBRID)) {
        return true;
    }
    size_t n = get_size();
    for (size_t i = 0; i < n; ++i) {
        if (get(i).uses_hybrid()) {
            return true;
        }
    }
    return false;
}

bool expression_t::uses_clock() const
{
    if (empty()) {
        return false;
    }
    if (get_type().is_clock()) {
        return true;
    }
    size_t n = get_size();
    for (size_t i = 0; i < n; ++i) {
        if (get(i).uses_clock()) {
            return true;
        }
    }
    return false;
}

bool expression_t::is_dynamic() const
{
    if (empty()) {
        return false;
    } else {
        switch (data->kind) {
        case SPAWN:
        case NUMOF:
        case EXIT:
        case SUM_DYNAMIC:
        case EXISTS_DYNAMIC:
        case FORALL_DYNAMIC: return true;
        default:;
        }
    }
    return false;
}

bool expression_t::has_dynamic_sub() const
{
    bool hasIt = false;
    size_t n = get_size();
    if (n <= 0) {
        return false;
    } else {
        for (size_t i = 0; i < n; ++i) {
            if (get(i).is_dynamic()) {
                return true;
            } else {
                hasIt |= get(i).has_dynamic_sub();
            }
        }
    }

    return hasIt;
}

size_t expression_t::get_size() const
{
    if (empty())
        return 0;

    switch (data->kind) {
    case MINUS:
    case PLUS:
    case MULT:
    case DIV:
    case MOD:
    case POW:
    case BIT_AND:
    case BIT_OR:
    case BIT_XOR:
    case BIT_LSHIFT:
    case BIT_RSHIFT:
    case AND:
    case OR:
    case XOR:
    case LT:
    case LE:
    case EQ:
    case NEQ:
    case GE:
    case GT:
    case MIN:
    case MAX:
    case ARRAY:
    case COMMA:
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
    case ASS_RSHIFT:
    case FORALL:
    case EXISTS:
    case SUM:
    case SUP_VAR:
    case INF_VAR:
    case FRACTION:
    case FMOD_F:
    case FMAX_F:
    case FMIN_F:
    case FDIM_F:
    case POW_F:
    case HYPOT_F:
    case ATAN2_F:
    case LDEXP_F:
    case NEXT_AFTER_F:
    case COPY_SIGN_F:
    case RANDOM_ARCSINE_F:
    case RANDOM_BETA_F:
    case RANDOM_GAMMA_F:
    case RANDOM_NORMAL_F:
    case RANDOM_WEIBULL_F: assert(data->sub.size() == 2); return 2;

    case UNARY_MINUS:
    case NOT:
    case DOT:
    case SYNC:
    case PRE_INCREMENT:
    case POST_INCREMENT:
    case PRE_DECREMENT:
    case POST_DECREMENT:
    case RATE:
    case ABS_F:
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
    case FINT_F:
    case ILOGB_F:
    case LOGB_F:
    case FP_CLASSIFY_F:
    case IS_FINITE_F:
    case IS_INF_F:
    case IS_NAN_F:
    case IS_NORMAL_F:
    case SIGNBIT_F:
    case IS_UNORDERED_F:
    case RANDOM_F:
    case RANDOM_POISSON_F: assert(data->sub.size() == 1); return 1;

    case IDENTIFIER:
    case CONSTANT:
    case DEADLOCK: assert(data->sub.size() == 0); return 0;

    case LOAD_STRAT:
    case INLINE_IF:
    case FMA_F:
    case RANDOM_TRI_F: assert(data->sub.size() == 3); return 3;

    case FUN_CALL:
    case FUN_CALL_EXT:
    case LIST:
    case SIMULATE:
    case SIMULATEREACH:
    case SPAWN: return std::get<int32_t>(data->value);

    case EG:
    case AG:
    case EF:
    case AF:
    case CONTROL:
    case EF_CONTROL:
    case CONTROL_TOPT_DEF2:
    case PMAX:
    case SCENARIO:
    case SAVE_STRAT: assert(data->sub.size() == 1); return 1;

    case LEADS_TO:
    case SCENARIO2:
    case A_UNTIL:
    case A_WEAK_UNTIL:
    case A_BUCHI:
    case PO_CONTROL:
    case CONTROL_TOPT_DEF1: assert(data->sub.size() == 2); return 2;

    case CONTROL_TOPT:
    case SMC_CONTROL: assert(data->sub.size() == 3); return 3;
    case PROBA_BOX:
    case PROBA_DIAMOND:
    case PROBA_MIN_BOX:
    case PROBA_MIN_DIAMOND: assert(data->sub.size() == 5); return 5;

    case MIN_EXP:
    case MAX_EXP: assert(data->sub.size() == 7); return 7;

    case PROBA_EXP: assert(data->sub.size() == 5); return 5;

    case PROBA_CMP: assert(data->sub.size() == 8); return 8;
    case MITL_FORMULA:
    case MITL_ATOM:
    case MITL_NEXT: assert(data->sub.size() == 1); return 1;
    case MITL_DISJ:
    case MITL_CONJ: assert(data->sub.size() == 2); return 2;
    case MITL_UNTIL:
    case MITL_RELEASE: assert(data->sub.size() == 4); return 4;
    case EXIT: assert(data->sub.size() == 0); return 0;
    case NUMOF: assert(data->sub.size() == 1); return 1;
    case EXISTS_DYNAMIC:
    case FORALL_DYNAMIC:
    case SUM_DYNAMIC:
    case MITL_EXISTS:
    case MITL_FORALL:
    case FOREACH_DYNAMIC: assert(data->sub.size() == 3); return 3;
    case DYNAMIC_EVAL: assert(data->sub.size() == 2); return 2;
    default: assert(0); return 0;
    }
}

type_t expression_t::get_type() const
{
    assert(data);
    return data->type;
}

void expression_t::set_type(type_t type)
{
    assert(data);
    data->type = type;
}

int32_t expression_t::get_value() const
{
    assert(data && data->kind == CONSTANT && (data->type.is_integral() || data->kind == VAR_INDEX));
    int32_t value = std::get<int32_t>(data->value);
    return data->type.is_integer() ? value : (value ? 1 : 0);
}

int32_t expression_t::get_record_label_index() const
{
    assert(data && (get(0).get_type().is_process() || get(0).get_type().is_record()));
    return std::get<int32_t>(data->value);
}

double expression_t::get_double_value() const
{
    assert(data);
    assert(data->kind == CONSTANT);
    assert(data->type.is(Constants::DOUBLE));
    return std::get<double>(data->value);
}

int32_t expression_t::get_index() const
{
    assert(data);
    assert(data->kind == DOT);
    return std::get<int32_t>(data->value);
}

synchronisation_t expression_t::get_sync() const
{
    assert(data);
    assert(data->kind == SYNC);
    return std::get<synchronisation_t>(data->value);
}

std::string_view expression_t::get_string_value() const
{
    assert(data);
    assert(data->kind == CONSTANT);
    assert(data->type.is_string());
    return std::get<StringIndex>(data->value).str();
}

int expression_t::get_string_index() const
{
    assert(data);
    assert(data->kind == CONSTANT);
    assert(data->type.is_string());
    return std::get<StringIndex>(data->value).index();
}

expression_t& expression_t::operator[](uint32_t i)
{
    assert(i < get_size());
    return data->sub[i];
}

const expression_t expression_t::operator[](uint32_t i) const
{
    assert(i < get_size());
    return data->sub[i];
}

expression_t& expression_t::get(uint32_t i)
{
    assert(i < get_size());
    return data->sub[i];
}

const expression_t& expression_t::get(uint32_t i) const
{
    assert(i < get_size());
    return data->sub[i];
}

bool expression_t::empty() const { return data == nullptr; }

bool expression_t::is_true() const
{
    return data == nullptr || (get_type().is_integral() && data->kind == CONSTANT && get_value() == 1);
}

/**
 * Compares two variants if they have the same type they'll be compared otherwise return false
 */
struct ValueTypeEquality
{
    template <typename T1, typename T2>
    bool operator()(const T1& a, const T2& b) const
    {
        if constexpr (std::is_same_v<T1, T2>)
            return a == b;
        else
            return false;
    }
};

/** Two expressions are identical iff all the sub expressions
    are identical and if the kind, value and symbol of the
    root are identical. */
bool expression_t::equal(const expression_t& e) const
{
    if (data == e.data) {
        return true;
    }

    if (get_size() != e.get_size() || data->kind != e.data->kind ||
        !std::visit(ValueTypeEquality{}, data->value, e.data->value) || data->symbol != e.data->symbol) {
        return false;
    }

    for (uint32_t i = 0; i < get_size(); i++) {
        if (!data->sub[i].equal(e[i])) {
            return false;
        }
    }

    return true;
}

/**
   Returns the symbol of a variable reference. The expression must be
   a left-hand side value. The symbol returned is the symbol of the
   variable the expression if resulting in a reference to. NOTE: In
   case of inline if, the symbol referenced by the 'true' part is
   returned.
*/
symbol_t expression_t::get_symbol() { return ((const expression_t*)this)->get_symbol(); }

const symbol_t expression_t::get_symbol() const
{
    assert(data);

    switch (get_kind()) {
    case IDENTIFIER: return data->symbol;

    case DOT: return get(0).get_symbol();

    case ARRAY: return get(0).get_symbol();

    case PRE_INCREMENT:
    case PRE_DECREMENT: return get(0).get_symbol();

    case INLINE_IF: return get(1).get_symbol();

    case COMMA: return get(1).get_symbol();

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
    case ASS_RSHIFT: return get(0).get_symbol();

    case SYNC: return get(0).get_symbol();

    case FUN_CALL:
    case FUN_CALL_EXT: return get(0).get_symbol();

    case SCENARIO: return get(0).get_symbol();

    default: return symbol_t();
    }
}

void expression_t::get_symbols(std::set<symbol_t>& symbols) const
{
    if (empty()) {
        return;
    }

    switch (get_kind()) {
    case IDENTIFIER: symbols.insert(data->symbol); break;

    case DOT: get(0).get_symbols(symbols); break;

    case ARRAY: get(0).get_symbols(symbols); break;

    case PRE_INCREMENT:
    case PRE_DECREMENT: get(0).get_symbols(symbols); break;

    case INLINE_IF:
        get(1).get_symbols(symbols);
        get(2).get_symbols(symbols);
        break;

    case COMMA: get(1).get_symbols(symbols); break;

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
    case ASS_RSHIFT: get(0).get_symbols(symbols); break;

    case SYNC: get(0).get_symbols(symbols); break;

    default:
        // Do nothing
        break;
    }
}

/** Returns true if expr might be a reference to a symbol in the
    set. */
bool expression_t::is_reference_to(const std::set<symbol_t>& symbols) const
{
    std::set<symbol_t> s;
    get_symbols(s);
    return find_first_of(symbols.begin(), symbols.end(), s.begin(), s.end()) != symbols.end();
}

bool expression_t::contains_deadlock() const
{
    if (get_kind() == UTAP::Constants::DEADLOCK)
        return true;
    if (data)
        for (auto& subexp : data->sub)
            if (subexp.contains_deadlock())
                return true;
    return false;
}

bool expression_t::changes_variable(const std::set<symbol_t>& symbols) const
{
    auto changes = std::set<symbol_t>{};
    collect_possible_writes(changes);
    return find_first_of(symbols.begin(), symbols.end(), changes.begin(), changes.end()) != symbols.end();
}

bool expression_t::changes_any_variable() const
{
    auto changes = std::set<symbol_t>{};
    collect_possible_writes(changes);
    return !changes.empty();
}

bool expression_t::depends_on(const std::set<symbol_t>& symbols) const
{
    std::set<symbol_t> dependencies;
    collect_possible_reads(dependencies);
    return find_first_of(symbols.begin(), symbols.end(), dependencies.begin(), dependencies.end()) != symbols.end();
}

int expression_t::get_precedence() const { return get_precedence(data->kind); }

int expression_t::get_precedence(kind_t kind)
{
    switch (kind) {
    case PLUS:
    case MINUS: return 70;

    case MULT:
    case DIV:
    case MOD: return 80;

    case POW: return 85;  // greater than MULT and less than NOT

    case BIT_AND: return 37;

    case BIT_OR: return 30;

    case BIT_XOR: return 35;

    case BIT_LSHIFT:
    case BIT_RSHIFT: return 60;

    case AND: return 25;
    case OR: return 22;
    case XOR: return 20;

    case EQ:
    case NEQ: return 40;

    case MIN:
    case MAX: return 55;

    case LT:
    case LE:
    case GE:
    case GT:
    case SIMULATE: return 50;

    case IDENTIFIER:
    case CONSTANT:
    case VAR_INDEX:
    case DEADLOCK:
    case FUN_CALL:
    case FUN_CALL_EXT: return 110;

    case ARRAY: return 105;
    case DOT:
    case RATE: return 100;

    case PRE_INCREMENT:
    case PRE_DECREMENT:
    case UNARY_MINUS:
    case NOT: return 90;

    case FRACTION: return 14;
    case INLINE_IF: return 15;

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
    case ASS_RSHIFT: return 10;

    case FORALL:
    case EXISTS:
    case SUM: return 8;

    case A_UNTIL:
    case A_WEAK_UNTIL:
    case A_BUCHI: return 7;

    case EF:
    case EG:
    case AF:
    case AG: return 6;

    case LEADS_TO:
    case SCENARIO:
    case SCENARIO2: return 5;

    case COMMA: return 4;

    case PROBA_MIN_BOX:
    case PROBA_MIN_DIAMOND:
    case PROBA_BOX:
    case PROBA_DIAMOND:
    case PROBA_EXP:
    case PO_CONTROL:
    case CONTROL:
    case SMC_CONTROL:
    case MIN_EXP:
    case MAX_EXP:
    case LOAD_STRAT:
    case SAVE_STRAT:
    case EF_CONTROL:
    case CONTROL_TOPT:
    case CONTROL_TOPT_DEF1:
    case CONTROL_TOPT_DEF2:
    case SUP_VAR:
    case INF_VAR: return 3;

    case SYNC: return 0;

    case POST_DECREMENT:
    case POST_INCREMENT:
    case ABS_F:
    case FABS_F:
    case FMOD_F:
    case FMA_F:
    case FMAX_F:
    case FMIN_F:
    case FDIM_F:
    case EXP_F:
    case EXP2_F:
    case EXPM1_F:
    case LN_F:
    case LOG_F:
    case LOG10_F:
    case LOG2_F:
    case LOG1P_F:
    case POW_F:
    case SQRT_F:
    case CBRT_F:
    case HYPOT_F:
    case SIN_F:
    case COS_F:
    case TAN_F:
    case ASIN_F:
    case ACOS_F:
    case ATAN_F:
    case ATAN2_F:
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
    case FINT_F:
    case LDEXP_F:
    case ILOGB_F:
    case LOGB_F:
    case NEXT_AFTER_F:
    case COPY_SIGN_F:
    case FP_CLASSIFY_F:
    case IS_FINITE_F:
    case IS_INF_F:
    case IS_NAN_F:
    case IS_NORMAL_F:
    case SIGNBIT_F:
    case IS_UNORDERED_F:
    case RANDOM_F:
    case RANDOM_ARCSINE_F:
    case RANDOM_BETA_F:
    case RANDOM_GAMMA_F:
    case RANDOM_NORMAL_F:
    case RANDOM_POISSON_F:
    case RANDOM_WEIBULL_F:
    case RANDOM_TRI_F: return 110;

    case MITL_FORMULA:
    case MITL_UNTIL:
    case MITL_RELEASE:
    case MITL_DISJ:
    case MITL_CONJ:
    case MITL_ATOM:
    case MITL_NEXT:
    case LIST:
    case SPAWN:
    case EXIT:
    case NUMOF:
    case FORALL_DYNAMIC:
    case EXISTS_DYNAMIC:
    case FOREACH_DYNAMIC:
    case SUM_DYNAMIC:
    case PROCESS_VAR:
    case PROBA_CMP:
    case BOX:
    case DIAMOND:
    case SIMULATEREACH:
    case DYNAMIC_EVAL: return -1;  // TODO

    default: throw std::logic_error("Unknown precedence of the expression");
    }
    assert(0);
    return 0;
}

static void ensure(char*& str, char*& end, int& size, int len)
{
    while (size <= len) {
        size *= 2;
    }

    char* nstr = new char[size];
    strncpy(nstr, str, end - str);
    end = nstr + (end - str);
    *end = 0;
    delete[] str;
    str = nstr;
}

static void append(char*& str, char*& end, int& size, const char* s)
{
    while (end < str + size && *s) {
        *(end++) = *(s++);
    }

    if (end == str + size) {
        ensure(str, end, size, 2 * size);
        append(str, end, size, s);
    } else {
        *end = 0;
    }
}

std::ostream& expression_t::print_bound_type(std::ostream& os, expression_t e) const
{
    if (e.get_kind() == CONSTANT) {
        assert(e.get_type().is(Constants::INT));  // Encoding used here.

        if (e.get_value() == 0) {
            os << "#";
        }
    } else {
        e.print(os, false);
    }
    os << "<=";
    return os;
}

static const char* get_builtin_fun_name(kind_t kind)
{
    // the order must match declarations in include/utap/common.h
    static const char* funNames[] = {"abs",
                                     "fabs",
                                     "fmod",
                                     "fma",
                                     "fmax",
                                     "fmin",
                                     "fdim",
                                     "exp",
                                     "exp2",
                                     "expm1",
                                     "ln",
                                     "log",
                                     "log10",
                                     "log2",
                                     "log1p",
                                     "pow",
                                     "sqrt",
                                     "cbrt",
                                     "hypot",
                                     "sin",
                                     "cos",
                                     "tan",
                                     "asin",
                                     "acos",
                                     "atan",
                                     "atan2",
                                     "sinh",
                                     "cosh",
                                     "tanh",
                                     "asinh",
                                     "acosh",
                                     "atanh",
                                     "erf",
                                     "erfc",
                                     "tgamma",
                                     "lgamma",
                                     "ceil",
                                     "floor",
                                     "trunc",
                                     "round",
                                     "fint",
                                     "ldexp",
                                     "ilogb",
                                     "logb",
                                     "nextafter",
                                     "copysign",
                                     "fpclassify",
                                     "isfinite",
                                     "isinf",
                                     "isnan",
                                     "isnormal",
                                     "signbit",
                                     "isunordered",
                                     "random",
                                     "random_arcsine",
                                     "random_beta",
                                     "random_gamma",
                                     "random_normal",
                                     "random_poisson",
                                     "random_tri",
                                     "random_weibull"};
    static_assert(RANDOM_WEIBULL_F - ABS_F + 1 == sizeof(funNames) / sizeof(funNames[0]),
                  "Builtin function name list is wrong");
    assert(ABS_F <= kind && kind <= RANDOM_WEIBULL_F);
    return funNames[kind - ABS_F];
}

static inline std::ostream& embrace_strict(std::ostream& os, bool old, const expression_t& expr, int precedence)
{
    if (precedence > expr.get_precedence())
        return expr.print(os << '(', old) << ')';
    else
        return expr.print(os, old);
}

static inline std::ostream& embrace(std::ostream& os, bool old, const expression_t& expr, int precedence)
{
    if (precedence > expr.get_precedence())
        return expr.print(os << '(', old) << ')';
    else
        return expr.print(os, old);
}

int get_precedence_or_default(const expression_t& expr)
{
    try {
        return expr.get_precedence();
    } catch (const std::logic_error&) {
        return -1;
    }
}

std::ostream& expression_t::print(std::ostream& os, bool old) const
{
    const int precedence = get_precedence_or_default(*this);

    bool flag = false;
    int nb;

    switch (data->kind) {
    case PROBA_MIN_BOX: flag = true; [[fallthrough]];
    case PROBA_MIN_DIAMOND:
        os << "Pr[";
        print_bound_type(os, get(0));
        get(1).print(os, old);
        os << (flag ? "]([] " : "](<> ");
        get(2).print(os, old) << ") >= " << get(3).get_double_value();
        break;

    case PROBA_BOX: flag = true; [[fallthrough]];
    case PROBA_DIAMOND:
        os << "Pr[";
        print_bound_type(os, get(0));
        get(1).print(os, old) << (flag ? "]([] " : "](<> ");
        get(2).print(os, old) << ")";
        break;

    case PROBA_EXP:
        os << "E[";
        print_bound_type(os, get(0));
        get(1).print(os, old) << "; ";
        get(2).print(os, old) << "] (" << (get(4).get_value() ? "max: " : "min: ");
        get(3).print(os, old) << ")";
        break;

    case PROBA_CMP:
        os << "Pr[";
        print_bound_type(os, get(0));
        get(1).print(os, old) << "] (";
        os << (get(2).get_value() == kind_t::BOX ? "[] " : "<> ");
        get(3).print(os, old) << ") >= ";

        os << "Pr[";
        print_bound_type(os, get(4));
        get(5).print(os, old) << "] (";
        os << (get(6).get_value() == kind_t::BOX ? "[] " : "<> ");
        get(7).print(os, old) << ")";
        break;
    case BOX: os << "[]"; break;
    case DIAMOND: os << "<>"; break;
    case SIMULATEREACH:
        os << "simulate[";
        print_bound_type(os, get(1));
        get(2).print(os, old) << "; ";
        get(0).print(os, old) << "] {";
        nb = get_size() - 5;
        if (nb > 0) {
            get(3).print(os, old);
            for (int i = 1; i < nb; ++i)
                get(3 + i).print(os << ", ", old);
        }
        os << "} : ";
        get(4 + nb).print(os, old) << " : ";
        get(3 + nb).print(os, old);
        break;
    case SIMULATE:
        os << "simulate[";
        print_bound_type(os, get(1));
        get(2).print(os, old) << "; ";
        get(0).print(os, old) << "] {";
        nb = get_size() - 3;
        if (nb > 0) {
            get(3).print(os, old);
            for (int i = 1; i < nb; ++i)
                get(3 + i).print(os << ", ", old);
        }
        os << "}";
        break;

    case PLUS:
    case MINUS:
    case MULT:
    case DIV:
    case MOD:
    case POW:
    case BIT_AND:
    case BIT_OR:
    case BIT_XOR:
    case BIT_LSHIFT:
    case BIT_RSHIFT:
    case AND:
    case OR:
    case LT:
    case LE:
    case EQ:
    case NEQ:
    case GE:
    case GT:
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
    case ASS_RSHIFT:
    case MIN:
    case MAX:
    case FRACTION:
        embrace(os, old, get(0), precedence);
        switch (data->kind) {
        case FRACTION: os << " : "; break;
        case PLUS: os << " + "; break;
        case MINUS: os << " - "; break;
        case MULT: os << " * "; break;
        case DIV: os << " / "; break;
        case MOD: os << " % "; break;
        case POW: os << " ** "; break;
        case BIT_AND: os << " & "; break;
        case BIT_OR: os << " | "; break;
        case BIT_XOR: os << " ^ "; break;
        case BIT_LSHIFT: os << " << "; break;
        case BIT_RSHIFT: os << " >> "; break;
        case AND: os << " && "; break;
        case OR: os << " || "; break;
        case LT: os << " < "; break;
        case LE: os << " <= "; break;
        case EQ: os << " == "; break;
        case NEQ: os << " != "; break;
        case GE: os << " >= "; break;
        case GT: os << " > "; break;
        case ASSIGN: os << (old ? " := " : " = "); break;
        case ASS_PLUS: os << " += "; break;
        case ASS_MINUS: os << " -= "; break;
        case ASS_DIV: os << " /= "; break;
        case ASS_MOD: os << " %= "; break;
        case ASS_MULT: os << " *= "; break;
        case ASS_AND: os << " &= "; break;
        case ASS_OR: os << " |= "; break;
        case ASS_XOR: os << " ^= "; break;
        case ASS_LSHIFT: os << " <<= "; break;
        case ASS_RSHIFT: os << " >>= "; break;
        case MIN: os << " <? "; break;
        case MAX: os << " >? "; break;
        default: assert(0);
        }
        embrace(os, old, get(1), precedence);
        break;

    case IDENTIFIER: os << data->symbol.get_name(); break;

    case VAR_INDEX:
    case CONSTANT:

        if (get_type().is(Constants::DOUBLE)) {
            os << get_double_value();
        } else if (get_type().is_string()) {
            os << get_string_value();
        } else if (get_type().is_integer()) {
            os << std::get<int32_t>(data->value);
        } else {
            assert(get_type().is(Constants::BOOL));
            os << (std::get<int32_t>(data->value) ? "true" : "false");
        }
        break;

    case ARRAY:
        embrace_strict(os << '-', old, get(0), precedence);
        get(1).print(os << '[', old) << ']';
        break;

    case UNARY_MINUS: embrace(os << '-', old, get(0), precedence); break;

    case POST_DECREMENT:
    case POST_INCREMENT: embrace(os, old, get(0), precedence) << (get_kind() == POST_DECREMENT ? "--" : "++"); break;

    case ABS_F:
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
    case FINT_F:
    case ILOGB_F:
    case LOGB_F:
    case FP_CLASSIFY_F:
    case IS_FINITE_F:
    case IS_INF_F:
    case IS_NAN_F:
    case IS_NORMAL_F:
    case SIGNBIT_F:
    case IS_UNORDERED_F:
    case RANDOM_F:
    case RANDOM_POISSON_F:
        os << get_builtin_fun_name(data->kind);
        get(0).print(os << '(', old) << ')';
        break;

    case FMOD_F:
    case FMAX_F:
    case FMIN_F:
    case FDIM_F:
    case POW_F:
    case HYPOT_F:
    case ATAN2_F:
    case LDEXP_F:
    case NEXT_AFTER_F:
    case COPY_SIGN_F:
    case RANDOM_ARCSINE_F:
    case RANDOM_BETA_F:
    case RANDOM_GAMMA_F:
    case RANDOM_NORMAL_F:
    case RANDOM_WEIBULL_F:
        os << get_builtin_fun_name(data->kind) << '(';
        get(0).print(os, old) << ',';
        get(1).print(os, old) << ')';
        break;

    case FMA_F:
    case RANDOM_TRI_F:
        os << get_builtin_fun_name(data->kind) << '(';
        get(0).print(os, old) << ',';
        get(1).print(os, old) << ',';
        get(2).print(os, old) << ')';
        break;

    case XOR:
        os << '(';
        get(0).print(os, old) << ") xor (";
        get(1).print(os, old) << ')';
        break;

    case PRE_DECREMENT:
    case PRE_INCREMENT:
        os << (get_kind() == PRE_DECREMENT ? "--" : "++");
        embrace(os, old, get(0), precedence);
        break;

    case NOT: embrace(os << '!', old, get(0), precedence); break;

    case DOT: {
        type_t type = get(0).get_type();
        if (type.is_process() || type.is_record())
            embrace(os, old, get(0), precedence) << '.' << type.get_record_label(std::get<int32_t>(data->value));
        else
            assert(0);
        break;
    }

    case INLINE_IF:
        embrace(os, old, get(0), precedence) << " ? ";
        embrace(os, old, get(1), precedence) << " : ";
        embrace(os, old, get(2), precedence);
        break;

    case COMMA:
        get(0).print(os, old) << ", ";
        get(1).print(os, old);
        break;

    case SYNC:
        get(0).print(os, old);
        switch (get_sync()) {
        case SYNC_QUE: os << '?'; break;
        case SYNC_BANG: os << '!'; break;
        case SYNC_CSP:
            // no append
            break;
        }
        break;

    case DEADLOCK: os << "deadlock"; break;

    case LIST:
        if (get_size() > 0) {
            get(0).print(os, old);
            for (uint32_t i = 1; i < get_size(); i++)
                get(i).print(os << ", ", old);
        }
        break;

    case FUN_CALL:
    case FUN_CALL_EXT:
        get(0).print(os, old) << '(';
        if (get_size() > 1) {
            get(1).print(os, old);
            for (uint32_t i = 2; i < get_size(); i++)
                get(i).print(os << ", ", old);
        }
        os << ')';
        break;

    case RATE: get(0).print(os, old) << '\''; break;

    case EF:
        os << "E<> ";
        get(0).print(os, old);
        break;

    case EG:
        os << "E[] ";
        get(0).print(os, old);
        break;

    case AF:
        os << "A<> ";
        get(0).print(os, old);
        break;

    case AG:
        os << "A[] ";
        get(0).print(os, old);
        break;

    case LEADS_TO:
        get(0).print(os, old) << " --> ";
        get(1).print(os, old);
        break;

    case A_UNTIL:
        os << "A[";
        get(0).print(os, old) << " U ";
        get(1).print(os, old) << "] ";
        break;

    case A_WEAK_UNTIL:
        get(0).print(os << "A[", old) << " W ";
        get(1).print(os, old) << "] ";
        break;

    case A_BUCHI:
        os << "A[] ((";
        get(0).print(os, old) << ") and A<> ";
        get(1).print(os, old) << ") ";
        break;

    case FORALL:
        os << "forall(" << get(0).get_symbol().get_name() << ':' << get(0).get_symbol().get_type().str() << ") ";
        get(1).print(os, old);
        break;

    case EXISTS:
        os << "exists(" << get(0).get_symbol().get_name() << ':' << get(0).get_symbol().get_type().str() << ") ";
        get(1).print(os, old);
        break;

    case SUM:
        os << "sum(" << get(0).get_symbol().get_name() << ':' << get(0).get_symbol().get_type().str() << ") ";
        get(1).print(os, old);
        break;

    case SMC_CONTROL:
        assert(false);
        os << "control[";
        print_bound_type(os, get(0));
        get(1).print(os, old) << "]: ";
        get(2).print(os, old);
        break;

    case MIN_EXP:
        assert(get_size() == 7);
        os << "minE(";
        get(3).print(os, old);
        os << ")[";
        if (get(0).get_kind() == Constants::CONSTANT) {
            if (bool is_step_bound = (get(0).get_value() == 0))
                os << "#";
        } else {
            get(0).print(os, old);
        }
        os << "<=";
        get(1).print(os, old);
        os << "]";
        if (auto features1 = get(5); features1.get_kind() == Constants::LIST) {
            features1.print(os << " {", old);
            os << "} -> {";
            if (auto features2 = get(6); features2.get_kind() == Constants::LIST)
                features2.print(os, old);
            os << "}";
        }
        os << " : <> ";
        get(2).print(os, old);
        break;
    case MAX_EXP:
        assert(get_size() == 7);
        os << "maxE(";
        get(3).print(os, old);
        os << ")[";
        if (get(0).get_kind() == Constants::CONSTANT) {
            if (bool is_step_bound = (get(0).get_value() == 0))
                os << "#";
        } else {
            get(0).print(os, old);
        }
        os << "<=";
        get(1).print(os, old);
        os << "]";
        if (auto features1 = get(5); features1.get_kind() == Constants::LIST) {
            features1.print(os << " {", old);
            os << "} -> {";
            if (auto features2 = get(6); features2.get_kind() == Constants::LIST)
                features2.print(os, old);
            os << "}";
        }
        os << " : <> ";
        get(2).print(os, old);
        break;
    case SAVE_STRAT: os << "saveStrategy(" << std::quoted(get(0).get_string_value()) << ", ...)"; break;
    case LOAD_STRAT:
        os << "loadStrategy";
        if (get(1).get_type().is(LIST) && get(2).get_type().is(LIST)) {
            get(1).print(os << "{", old) << "} -> {";
            get(2).print(os, old) << "}";
        }
        get(0).print(os << "(\"", old) << "\")";
        break;

    case PO_CONTROL:
        os << "{ ";
        get(0).print(os, old) << "} control: ";
        get(1).print(os, old);
        break;

    case EF_CONTROL: os << "E<> "; [[fallthrough]];
    case CONTROL:
        os << "control: ";
        get(0).print(os, old);
        break;

    case CONTROL_TOPT:
        os << "control_t*(";
        get(0).print(os, old) << ',';
        get(1).print(os, old) << "): ";
        get(2).print(os, old);
        break;

    case CONTROL_TOPT_DEF1:
        os << "control_t*(";
        get(0).print(os, old) << "): ";
        get(1).print(os, old);
        break;

    case CONTROL_TOPT_DEF2:
        os << "control_t*: ";
        get(0).print(os, old);
        break;

    case SUP_VAR:
        os << "sup{";
        get(0).print(os, old) << "}: ";
        get(1).print(os, old);
        break;

    case INF_VAR:
        os << "inf{";
        get(0).print(os, old) << "}: ";
        get(1).print(os, old);
        break;

    case MITL_FORMULA:
        os << "MITL: ";
        get(0).print(os, old);
        break;
    case MITL_RELEASE:
    case MITL_UNTIL:
        get(0).print(os, old) << "U[";
        get(1).print(os, old) << ";";
        get(2).print(os, old) << "]";
        get(3).print(os, old);
        break;

    case MITL_DISJ:
        get(0).print(os, old) << "\\/";
        get(1).print(os, old);
        break;
    case MITL_CONJ:
        get(0).print(os, old) << "/\\";
        get(1).print(os, old);
        break;
    case MITL_ATOM: get(0).print(os, old); break;
    case MITL_NEXT:
        os << "X(";
        get(0).print(os, old) << ")";
        break;
    case SPAWN: os << "SPAWN"; break;
    case EXIT: os << "EXIT"; break;
    case NUMOF:
        os << "numof(";
        get(0).print(os, old) << ")";
        break;
    case MITL_FORALL:
    case FORALL_DYNAMIC:
        os << "forall(";
        get(0).print(os, old) << " : ";
        get(1).print(os, old) << " )( ";
        get(2).print(os, old) << ")";
        break;
    case SUM_DYNAMIC:
        os << "sum(";
        get(0).print(os, old) << " : ";
        get(1).print(os, old) << " )( ";
        get(2).print(os, old) << ")";
        break;
    case FOREACH_DYNAMIC:
        os << "foreach (";
        get(0).print(os, old) << " : ";
        get(1).print(os, old) << " )( ";
        get(2).print(os, old) << ")";
        break;
    case DYNAMIC_EVAL:
        get(1).print(os, old) << ".";
        get(0).print(os, old);
        break;
    case PROCESS_VAR: get(0).print(os, old); break;
    case MITL_EXISTS:
    case EXISTS_DYNAMIC:
        os << "exists(";
        get(0).print(os, old) << " : ";
        get(1).print(os, old) << " )( ";
        get(2).print(os, old) << ")";
        break;
    case TYPEDEF: os << "typedef"; break;

    // Types - Not applicable in expression printing
    case RANGE:
    case RECORD:
    case REF:
    case URGENT:
    case COMMITTED:
    case BROADCAST:
    case VOID_TYPE:
    case CLOCK:
    case INT:
    case DOUBLE:
    case STRING:
    case BOOL:
    case SCALAR:
    case CHANNEL:
    case INVARIANT:
    case INVARIANT_WR:
    case HYBRID:
    case PROCESS_SET:
    case SYSTEM_META:
    case GUARD:
    case DIFF:
    case CONSTRAINT:
    case FORMULA:
    case COST:
    case PROCESS:
    case INSTANCE:
    case LABEL:
    case FUNCTION_EXTERNAL:
    case FUNCTION:
    case LOCATION_EXPR:
    case LOCATION:
    case BRANCHPOINT:
    case DOUBLE_INV_GUARD:
    // Deprecated LSC features
    case SCENARIO:
    case SCENARIO2:
    case INSTANCE_LINE:
    case MESSAGE:
    case CONDITION:
    case UPDATE:
    case LSC_INSTANCE:
    // Deprecated probability feature
    case PMAX:

    case UNKNOWN: break;
    }
    return os;
}

bool expression_t::operator<(const expression_t e) const
{
    return data != nullptr && e.data != nullptr && data < e.data;
}

bool expression_t::operator==(const expression_t e) const { return data == e.data; }

/** Returns a string representation of the expression. The string
    returned must be deallocated with delete[]. Returns empty is the
    expression is empty. */
std::string expression_t::str(bool old) const
{
    auto os = std::ostringstream{};
    print(os, old);
    return os.str();
}

void expression_t::collect_possible_writes(set<symbol_t>& symbols) const
{
    function_t* fun;
    symbol_t symbol;
    type_t type;

    if (empty())
        return;

    for (uint32_t i = 0; i < get_size(); i++) {
        get(i).collect_possible_writes(symbols);
    }

    switch (get_kind()) {
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
    case ASS_RSHIFT:
    case POST_INCREMENT:
    case POST_DECREMENT:
    case PRE_INCREMENT:
    case PRE_DECREMENT: get(0).get_symbols(symbols); break;

    case FUN_CALL:
    case FUN_CALL_EXT:
        // Add all symbols which are changed by the function
        symbol = get(0).get_symbol();
        if ((symbol.get_type().is_function() || symbol.get_type().is_function_external()) && symbol.get_data()) {
            fun = (function_t*)symbol.get_data();

            symbols.insert(fun->changes.begin(), fun->changes.end());

            // Add arguments to non-constant reference parameters
            type = fun->uid.get_type();
            for (uint32_t i = 1; i < min(get_size(), type.size()); i++) {
                if (type[i].is(REF) && !type[i].is_constant()) {
                    get(i).get_symbols(symbols);
                }
            }
        }
        break;

    default: break;
    }
}

void expression_t::collect_possible_reads(set<symbol_t>& symbols, bool collectRandom) const
{
    if (empty())
        return;

    for (uint32_t i = 0; i < get_size(); i++)
        get(i).collect_possible_reads(symbols);

    switch (get_kind()) {
    case IDENTIFIER: symbols.insert(get_symbol()); break;

    case FUN_CALL: {
        // Add all symbols which are used by the function
        auto symbol = get(0).get_symbol();
        if (auto type = symbol.get_type(); type.is_function() || type.is_function_external()) {
            if (auto* data = symbol.get_data(); data) {
                auto fun = static_cast<function_t*>(data);
                symbols.insert(fun->depends.begin(), fun->depends.end());
            }
        }
        break;
    }
    case RANDOM_F:
    case RANDOM_POISSON_F:
        if (collectRandom) {
            symbols.insert(symbol_t());  // TODO: revisit, should register the argument?
        }
        break;
    case RANDOM_ARCSINE_F:
    case RANDOM_BETA_F:
    case RANDOM_GAMMA_F:
    case RANDOM_NORMAL_F:
    case RANDOM_WEIBULL_F:
        if (collectRandom) {
            symbols.insert(symbol_t());  // TODO: revisit, should register the arguments?
            symbols.insert(symbol_t());
        }
        break;

    case RANDOM_TRI_F:
        if (collectRandom) {
            symbols.insert(symbol_t());  // TODO: revisit, should register the argument?
            symbols.insert(symbol_t());
            symbols.insert(symbol_t());
        }
        break;
    default: break;
    }
}

expression_t expression_t::create_constant(int32_t value, position_t pos)
{
    auto expr = expression_t{CONSTANT, pos};
    expr.data->value = value;
    expr.data->type = type_t::create_primitive(Constants::INT);
    return expr;
}

expression_t expression_t::create_var_index(int32_t value, position_t pos)
{
    auto expr = expression_t{VAR_INDEX, pos};
    expr.data->value = value;
    expr.data->type = type_t::create_primitive(Constants::INT);
    return expr;
}

expression_t expression_t::create_exit(position_t pos)
{
    auto expr = expression_t{EXIT, pos};
    expr.data->value = 0;
    expr.data->type = type_t::create_primitive(Constants::VOID_TYPE);
    return expr;
}

expression_t expression_t::create_double(double value, position_t pos)
{
    auto expr = expression_t{CONSTANT, pos};
    expr.data->value = value;
    expr.data->type = type_t::create_primitive(Constants::DOUBLE);
    return expr;
}

expression_t expression_t::create_string(StringIndex str, position_t pos)
{
    auto expr = expression_t{CONSTANT, pos};
    expr.data->value = str;
    expr.data->type = type_t::create_primitive(Constants::STRING);
    return expr;
}

expression_t expression_t::create_identifier(symbol_t symbol, position_t pos)
{
    auto expr = expression_t{IDENTIFIER, pos};
    expr.data->symbol = symbol;
    if (symbol != symbol_t()) {
        expr.data->type = symbol.get_type();
    } else {
        expr.data->type = type_t();
    }
    return expr;
}

expression_t expression_t::create_nary(kind_t kind, vector<expression_t> sub, position_t pos, type_t type)
{
    auto expr = expression_t{kind, pos};
    expr.data->value = static_cast<int32_t>(sub.size());
    expr.data->sub = std::move(sub);
    expr.data->type = type;
    return expr;
}

expression_t expression_t::create_unary(kind_t kind, expression_t sub, position_t pos, type_t type)
{
    auto expr = expression_t{kind, pos};
    expr.data->sub.push_back(sub);
    expr.data->type = type;
    return expr;
}

expression_t expression_t::create_binary(kind_t kind, expression_t left, expression_t right, position_t pos,
                                         type_t type)
{
    auto expr = expression_t{kind, pos};
    expr.data->sub.reserve(2);
    expr.data->sub.push_back(left);
    expr.data->sub.push_back(right);
    expr.data->type = type;
    return expr;
}

expression_t expression_t::create_ternary(kind_t kind, expression_t e1, expression_t e2, expression_t e3,
                                          position_t pos, type_t type)
{
    auto expr = expression_t{kind, pos};
    expr.data->sub.reserve(3);
    expr.data->sub.push_back(e1);
    expr.data->sub.push_back(e2);
    expr.data->sub.push_back(e3);
    expr.data->type = type;
    return expr;
}

expression_t expression_t::create_dot(expression_t e, int32_t idx, position_t pos, type_t type)
{
    auto expr = expression_t{DOT, pos};
    expr.data->value = idx;
    expr.data->sub.push_back(e);
    expr.data->type = type;
    return expr;
}

expression_t expression_t::create_sync(expression_t e, synchronisation_t s, position_t pos)
{
    auto expr = expression_t{SYNC, pos};
    expr.data->value = s;
    expr.data->sub.push_back(std::move(e));
    return expr;
}

expression_t expression_t::create_deadlock(position_t pos)
{
    auto expr = expression_t{DEADLOCK, pos};
    expr.data->type = type_t::create_primitive(CONSTRAINT);
    return expr;
}
