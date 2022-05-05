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
#include <stdexcept>
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
    union
    {
        int32_t value; /**< The value of the node */
        int32_t index;
        synchronisation_t sync; /**< The sync value of the node  */
        double doubleValue;
    };
    symbol_t symbol;                 /**< The symbol of the node */
    type_t type;                     /**< The type of the expression */
    std::vector<expression_t> sub{}; /**< Subexpressions */
    expression_data(const position_t& p, kind_t kind, int32_t value): position{p}, kind{kind}, value{value} {}
    ~expression_data() noexcept = default;
};

expression_t::expression_t(kind_t kind, const position_t& pos)
{
    data = std::make_shared<expression_data>(pos, kind, 0);
}

expression_t expression_t::clone() const
{
    expression_t expr(data->kind, data->position);
    expr.data->value = data->value;
    expr.data->type = data->type;
    expr.data->symbol = data->symbol;
    expr.data->sub.reserve(data->sub.size());
    expr.data->sub.assign(data->sub.begin(), data->sub.end());
    return expr;
}

expression_t expression_t::deeperClone() const
{
    expression_t expr(data->kind, data->position);
    expr.data->value = data->value;
    expr.data->type = data->type;
    expr.data->symbol = data->symbol;
    if (!data->sub.empty()) {
        expr.data->sub.reserve(data->sub.size());
        for (const auto& s : data->sub)
            expr.data->sub.push_back(s.deeperClone());
    }
    return expr;
}

expression_t expression_t::deeperClone(symbol_t from, symbol_t to) const
{
    expression_t expr(data->kind, data->position);
    expr.data->value = data->value;
    expr.data->type = data->type;
    expr.data->symbol = (data->symbol == from) ? to : data->symbol;

    if (!data->sub.empty()) {
        expr.data->sub.reserve(data->sub.size());
        for (const auto& s : data->sub)
            expr.data->sub.push_back(s.deeperClone(from, to));
    }
    return expr;
}

expression_t expression_t::deeperClone(frame_t frame, frame_t select) const
{
    expression_t expr(data->kind, data->position);
    expr.data->value = data->value;
    expr.data->type = data->type;
    symbol_t uid;
    if (data->symbol != symbol_t()) {
        bool res = frame.resolve(data->symbol.getName(), uid);
        if (!res && select != frame_t()) {
            res = select.resolve(data->symbol.getName(), uid);
        }
        assert(res);
        expr.data->symbol = uid;
    } else {
        expr.data->symbol = data->symbol;
    }

    if (!data->sub.empty()) {
        expr.data->sub.reserve(data->sub.size());
        for (const auto& s : data->sub)
            expr.data->sub.push_back(s.deeperClone(frame, select));
    }
    return expr;
}

expression_t expression_t::subst(symbol_t symbol, expression_t expr) const
{
    if (empty()) {
        return *this;
    } else if (getKind() == IDENTIFIER && getSymbol() == symbol) {
        return expr;
    } else if (getSize() == 0) {
        return *this;
    } else {
        expression_t e = clone();
        for (size_t i = 0; i < getSize(); i++) {
            e[i] = e[i].subst(symbol, expr);
        }
        return e;
    }
}

kind_t expression_t::getKind() const
{
    assert(data);
    return data->kind;
}

const position_t& expression_t::getPosition() const
{
    assert(data);
    return data->position;
}

bool expression_t::usesFP() const
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
    case NEXTAFTER_F:
    case COPYSIGN_F:
    case FPCLASSIFY_F:
    case ISFINITE_F:
    case ISINF_F:
    case ISNAN_F:
    case ISNORMAL_F:
    case SIGNBIT_F:
    case ISUNORDERED_F:
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

    size_t n = getSize();
    for (size_t i = 0; i < n; ++i) {
        if (get(i).usesFP()) {
            return true;
        }
    }

    return false;
}

bool expression_t::usesHybrid() const
{
    if (empty()) {
        return false;
    }
    if (getType().is(HYBRID)) {
        return true;
    }
    size_t n = getSize();
    for (size_t i = 0; i < n; ++i) {
        if (get(i).usesHybrid()) {
            return true;
        }
    }
    return false;
}

bool expression_t::usesClock() const
{
    if (empty()) {
        return false;
    }
    if (getType().isClock()) {
        return true;
    }
    size_t n = getSize();
    for (size_t i = 0; i < n; ++i) {
        if (get(i).usesClock()) {
            return true;
        }
    }
    return false;
}

bool expression_t::isDynamic() const
{
    if (empty()) {
        return false;
    } else {
        switch (data->kind) {
        case SPAWN:
        case NUMOF:
        case EXIT:
        case SUMDYNAMIC:
        case EXISTSDYNAMIC:
        case FORALLDYNAMIC: return true;
        default:;
        }
    }
    return false;
}

bool expression_t::hasDynamicSub() const
{
    bool hasIt = false;
    size_t n = getSize();
    if (n <= 0) {
        return false;
    } else {
        for (size_t i = 0; i < n; ++i) {
            if (get(i).isDynamic()) {
                return true;
            } else {
                hasIt |= get(i).hasDynamicSub();
            }
        }
    }

    return hasIt;
}

size_t expression_t::getSize() const
{
    if (empty())
        return 0;

    switch (data->kind) {
    case MINUS:
    case PLUS:
    case MULT:
    case DIV:
    case MOD:
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
    case ASSPLUS:
    case ASSMINUS:
    case ASSDIV:
    case ASSMOD:
    case ASSMULT:
    case ASSAND:
    case ASSOR:
    case ASSXOR:
    case ASSLSHIFT:
    case ASSRSHIFT:
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
    case NEXTAFTER_F:
    case COPYSIGN_F:
    case RANDOM_ARCSINE_F:
    case RANDOM_BETA_F:
    case RANDOM_GAMMA_F:
    case RANDOM_NORMAL_F:
    case RANDOM_WEIBULL_F: assert(data->sub.size() == 2); return 2;

    case UNARY_MINUS:
    case NOT:
    case DOT:
    case SYNC:
    case PREINCREMENT:
    case POSTINCREMENT:
    case PREDECREMENT:
    case POSTDECREMENT:
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
    case FPCLASSIFY_F:
    case ISFINITE_F:
    case ISINF_F:
    case ISNAN_F:
    case ISNORMAL_F:
    case SIGNBIT_F:
    case ISUNORDERED_F:
    case RANDOM_F:
    case RANDOM_POISSON_F: assert(data->sub.size() == 1); return 1;

    case IDENTIFIER:
    case CONSTANT:
    case DEADLOCK: assert(data->sub.size() == 0); return 0;

    case LOAD_STRAT:
    case INLINEIF:
    case FMA_F:
    case RANDOM_TRI_F: assert(data->sub.size() == 3); return 3;

    case FUNCALL:
    case EFUNCALL:
    case LIST:
    case SIMULATE:
    case SIMULATEREACH:
    case SPAWN: return data->value;

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

    case LEADSTO:
    case SCENARIO2:
    case A_UNTIL:
    case A_WEAKUNTIL:
    case A_BUCHI:
    case PO_CONTROL:
    case CONTROL_TOPT_DEF1: assert(data->sub.size() == 2); return 2;

    case CONTROL_TOPT:
    case SMC_CONTROL: assert(data->sub.size() == 3); return 3;
    case PROBABOX:
    case PROBADIAMOND:
    case PROBAMINBOX:
    case PROBAMINDIAMOND: assert(data->sub.size() == 5); return 5;

    case MIN_EXP:
    case MAX_EXP: return 7;

    case PROBAEXP: assert(data->sub.size() == 5); return 5;

    case PROBACMP: assert(data->sub.size() == 8); return 8;
    case MITLFORMULA:
    case MITLATOM:
    case MITLNEXT: assert(data->sub.size() == 1); return 1;
    case MITLDISJ:
    case MITLCONJ: assert(data->sub.size() == 2); return 2;
    case MITLUNTIL:
    case MITLRELEASE: assert(data->sub.size() == 4); return 4;
    case EXIT: assert(data->sub.size() == 0); return 0;
    case NUMOF: assert(data->sub.size() == 1); return 1;
    case EXISTSDYNAMIC:
    case FORALLDYNAMIC:
    case SUMDYNAMIC:
    case MITLEXISTS:
    case MITLFORALL:
    case FOREACHDYNAMIC: assert(data->sub.size() == 3); return 3;
    case DYNAMICEVAL: assert(data->sub.size() == 2); return 2;
    default: assert(0); return 0;
    }
}

type_t expression_t::getType() const
{
    assert(data);
    return data->type;
}

void expression_t::setType(type_t type)
{
    assert(data);
    data->type = type;
}

int32_t expression_t::getValue() const
{
    assert(data && data->kind == CONSTANT &&
           (data->type.isIntegral() || data->type.isString() || data->kind == VARINDEX));
    return data->type.isInteger() || data->type.isString() ? data->value : (data->value ? 1 : 0);
}

int32_t expression_t::getRecordLabelIndex() const
{
    assert(data && (get(0).getType().isProcess() || get(0).getType().isRecord()));
    return data->value;
}

double expression_t::getDoubleValue() const
{
    assert(data);
    assert(data->kind == CONSTANT);
    assert(data->type.is(Constants::DOUBLE));
    return data->doubleValue;
}

int32_t expression_t::getIndex() const
{
    assert(data);
    assert(data->kind == DOT);
    return data->index;
}

synchronisation_t expression_t::getSync() const
{
    assert(data);
    assert(data->kind == SYNC);
    return data->sync;
}

expression_t& expression_t::operator[](uint32_t i)
{
    assert(i < getSize());
    return data->sub[i];
}

const expression_t expression_t::operator[](uint32_t i) const
{
    assert(i < getSize());
    return data->sub[i];
}

expression_t& expression_t::get(uint32_t i)
{
    assert(i < getSize());
    return data->sub[i];
}

const expression_t& expression_t::get(uint32_t i) const
{
    assert(i < getSize());
    return data->sub[i];
}

bool expression_t::empty() const { return data == nullptr; }

bool expression_t::isTrue() const
{
    return data == nullptr || (getType().isIntegral() && data->kind == CONSTANT && getValue() == 1);
}

/** Two expressions are identical iff all the sub expressions
    are identical and if the kind, value and symbol of the
    root are identical. */
bool expression_t::equal(const expression_t& e) const
{
    if (data == e.data) {
        return true;
    }

    if (getSize() != e.getSize() || data->kind != e.data->kind || data->value != e.data->value ||
        data->symbol != e.data->symbol) {
        return false;
    }

    for (uint32_t i = 0; i < getSize(); i++) {
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
symbol_t expression_t::getSymbol() { return ((const expression_t*)this)->getSymbol(); }

const symbol_t expression_t::getSymbol() const
{
    assert(data);

    switch (getKind()) {
    case IDENTIFIER: return data->symbol;

    case DOT: return get(0).getSymbol();

    case ARRAY: return get(0).getSymbol();

    case PREINCREMENT:
    case PREDECREMENT: return get(0).getSymbol();

    case INLINEIF: return get(1).getSymbol();

    case COMMA: return get(1).getSymbol();

    case ASSIGN:
    case ASSPLUS:
    case ASSMINUS:
    case ASSDIV:
    case ASSMOD:
    case ASSMULT:
    case ASSAND:
    case ASSOR:
    case ASSXOR:
    case ASSLSHIFT:
    case ASSRSHIFT: return get(0).getSymbol();

    case SYNC: return get(0).getSymbol();

    case FUNCALL:
    case EFUNCALL: return get(0).getSymbol();

    case SCENARIO: return get(0).getSymbol();

    default: return symbol_t();
    }
}

void expression_t::getSymbols(std::set<symbol_t>& symbols) const
{
    if (empty()) {
        return;
    }

    switch (getKind()) {
    case IDENTIFIER: symbols.insert(data->symbol); break;

    case DOT: get(0).getSymbols(symbols); break;

    case ARRAY: get(0).getSymbols(symbols); break;

    case PREINCREMENT:
    case PREDECREMENT: get(0).getSymbols(symbols); break;

    case INLINEIF:
        get(1).getSymbols(symbols);
        get(2).getSymbols(symbols);
        break;

    case COMMA: get(1).getSymbols(symbols); break;

    case ASSIGN:
    case ASSPLUS:
    case ASSMINUS:
    case ASSDIV:
    case ASSMOD:
    case ASSMULT:
    case ASSAND:
    case ASSOR:
    case ASSXOR:
    case ASSLSHIFT:
    case ASSRSHIFT: get(0).getSymbols(symbols); break;

    case SYNC: get(0).getSymbols(symbols); break;

    default:
        // Do nothing
        break;
    }
}

/** Returns true if expr might be a reference to a symbol in the
    set. */
bool expression_t::isReferenceTo(const std::set<symbol_t>& symbols) const
{
    std::set<symbol_t> s;
    getSymbols(s);
    return find_first_of(symbols.begin(), symbols.end(), s.begin(), s.end()) != symbols.end();
}

bool expression_t::contains_deadlock() const
{
    if (getKind() == UTAP::Constants::DEADLOCK)
        return true;
    if (data)
        for (auto& subexp : data->sub)
            if (subexp.contains_deadlock())
                return true;
    return false;
}

bool expression_t::changesVariable(const std::set<symbol_t>& symbols) const
{
    std::set<symbol_t> changes;
    collectPossibleWrites(changes);
    return find_first_of(symbols.begin(), symbols.end(), changes.begin(), changes.end()) != symbols.end();
}

bool expression_t::changesAnyVariable() const
{
    std::set<symbol_t> changes;
    collectPossibleWrites(changes);
    return !changes.empty();
}

bool expression_t::dependsOn(const std::set<symbol_t>& symbols) const
{
    std::set<symbol_t> dependencies;
    collectPossibleReads(dependencies);
    return find_first_of(symbols.begin(), symbols.end(), dependencies.begin(), dependencies.end()) != symbols.end();
}

int expression_t::getPrecedence() const { return getPrecedence(data->kind); }

int expression_t::getPrecedence(kind_t kind)
{
    switch (kind) {
    case PLUS:
    case MINUS: return 70;

    case MULT:
    case DIV:
    case MOD: return 80;

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
    case VARINDEX:
    case DEADLOCK:
    case FUNCALL:
    case EFUNCALL: return 110;

    case DOT:
    case ARRAY:
    case RATE: return 100;

    case UNARY_MINUS:
    case NOT: return 90;

    case FRACTION: return 14;
    case INLINEIF: return 15;

    case ASSIGN:
    case ASSPLUS:
    case ASSMINUS:
    case ASSDIV:
    case ASSMOD:
    case ASSMULT:
    case ASSAND:
    case ASSOR:
    case ASSXOR:
    case ASSLSHIFT:
    case ASSRSHIFT: return 10;

    case FORALL:
    case EXISTS:
    case SUM: return 8;

    case A_UNTIL:
    case A_WEAKUNTIL:
    case A_BUCHI: return 7;

    case EF:
    case EG:
    case AF:
    case AG: return 6;

    case LEADSTO:
    case SCENARIO:
    case SCENARIO2: return 5;

    case COMMA: return 4;

    case PROBAMINBOX:
    case PROBAMINDIAMOND:
    case PROBABOX:
    case PROBADIAMOND:
    case PROBAEXP:
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

    case PREDECREMENT:
    case POSTDECREMENT:
    case PREINCREMENT:
    case POSTINCREMENT:
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
    case NEXTAFTER_F:
    case COPYSIGN_F:
    case FPCLASSIFY_F:
    case ISFINITE_F:
    case ISINF_F:
    case ISNAN_F:
    case ISNORMAL_F:
    case SIGNBIT_F:
    case ISUNORDERED_F:
    case RANDOM_F:
    case RANDOM_ARCSINE_F:
    case RANDOM_BETA_F:
    case RANDOM_GAMMA_F:
    case RANDOM_NORMAL_F:
    case RANDOM_POISSON_F:
    case RANDOM_WEIBULL_F:
    case RANDOM_TRI_F: return 100;

    case MITLFORMULA:
    case MITLUNTIL:
    case MITLRELEASE:
    case MITLDISJ:
    case MITLCONJ:
    case MITLATOM:
    case MITLNEXT:
    case LIST:
    case SPAWN:
    case EXIT:
    case NUMOF:
    case FORALLDYNAMIC:
    case EXISTSDYNAMIC:
    case FOREACHDYNAMIC:
    case SUMDYNAMIC:
    case PROCESSVAR:
    case DYNAMICEVAL: return -1;  // TODO

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

static void append(char*& str, char*& end, int& size, char c)
{
    if (size - (end - str) < 2) {
        ensure(str, end, size, size + 2);
    }
    *end = c;
    ++end;
    *end = 0;
}

void expression_t::appendBoundType(char*& str, char*& end, int& size, expression_t e) const
{
    if (e.getKind() == CONSTANT) {
        assert(e.getType().is(Constants::INT));  // Encoding used here.

        if (e.getValue() == 0) {
            append(str, end, size, "#");
        }
    } else {
        e.toString(false, str, end, size);
    }
    append(str, end, size, "<=");
}

static const char* getBuiltinFunName(kind_t kind)
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

void expression_t::toString(bool old, char*& str, char*& end, int& size) const
{
    char s[64];
    int precedence = getPrecedence();
    bool flag = false;
    int nb;

    switch (data->kind) {
    case PROBAMINBOX: flag = true; [[fallthrough]];
    case PROBAMINDIAMOND:
        append(str, end, size, "Pr[");
        appendBoundType(str, end, size, get(0));
        get(1).toString(old, str, end, size);
        append(str, end, size, flag ? "]([] " : "](<> ");
        get(2).toString(old, str, end, size);
        append(str, end, size, ") >= ");
        snprintf(s, sizeof(s), "%f", get(3).getDoubleValue());
        append(str, end, size, s);
        break;

    case PROBABOX: flag = true; [[fallthrough]];
    case PROBADIAMOND:
        append(str, end, size, "Pr[");
        appendBoundType(str, end, size, get(0));
        get(1).toString(old, str, end, size);
        append(str, end, size, flag ? "]([] " : "](<> ");
        get(2).toString(old, str, end, size);
        append(str, end, size, ") ?");
        break;

    case PROBAEXP:
        append(str, end, size, "E[");
        appendBoundType(str, end, size, get(0));
        get(1).toString(old, str, end, size);
        append(str, end, size, "; ");
        get(2).toString(old, str, end, size);
        append(str, end, size, "] (");
        append(str, end, size, get(4).getValue() ? "max: " : "min: ");
        get(3).toString(old, str, end, size);
        append(str, end, size, ")");
        break;

    case SIMULATE:
        append(str, end, size, "simulate[");
        get(0).toString(old, str, end, size);
        append(str, end, size, "x ");
        appendBoundType(str, end, size, get(1));
        get(2).toString(old, str, end, size);
        append(str, end, size, "]{");
        nb = getValue() - 3;
        for (int i = 0; i < nb; ++i) {
            if (i > 0)
                append(str, end, size, ", ");
            get(3 + i).toString(old, str, end, size);
        }
        append(str, end, size, "}");
        break;

    case PLUS:
    case MINUS:
    case MULT:
    case DIV:
    case MOD:
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
    case ASSPLUS:
    case ASSMINUS:
    case ASSDIV:
    case ASSMOD:
    case ASSMULT:
    case ASSAND:
    case ASSOR:
    case ASSXOR:
    case ASSLSHIFT:
    case ASSRSHIFT:
    case MIN:
    case MAX:
    case FRACTION:

        if (precedence > get(0).getPrecedence()) {
            append(str, end, size, '(');
        }
        get(0).toString(old, str, end, size);
        if (precedence > get(0).getPrecedence()) {
            append(str, end, size, ')');
        }

        switch (data->kind) {
        case FRACTION: append(str, end, size, " : "); break;
        case PLUS: append(str, end, size, " + "); break;
        case MINUS: append(str, end, size, " - "); break;
        case MULT: append(str, end, size, " * "); break;
        case DIV: append(str, end, size, " / "); break;
        case MOD: append(str, end, size, " % "); break;
        case BIT_AND: append(str, end, size, " & "); break;
        case BIT_OR: append(str, end, size, " | "); break;
        case BIT_XOR: append(str, end, size, " ^ "); break;
        case BIT_LSHIFT: append(str, end, size, " << "); break;
        case BIT_RSHIFT: append(str, end, size, " >> "); break;
        case AND: append(str, end, size, " && "); break;
        case OR: append(str, end, size, " || "); break;
        case LT: append(str, end, size, " < "); break;
        case LE: append(str, end, size, " <= "); break;
        case EQ: append(str, end, size, " == "); break;
        case NEQ: append(str, end, size, " != "); break;
        case GE: append(str, end, size, " >= "); break;
        case GT: append(str, end, size, " > "); break;
        case ASSIGN:
            if (old) {
                append(str, end, size, " := ");
            } else {
                append(str, end, size, " = ");
            }
            break;
        case ASSPLUS: append(str, end, size, " += "); break;
        case ASSMINUS: append(str, end, size, " -= "); break;
        case ASSDIV: append(str, end, size, " /= "); break;
        case ASSMOD: append(str, end, size, " %= "); break;
        case ASSMULT: append(str, end, size, " *= "); break;
        case ASSAND: append(str, end, size, " &= "); break;
        case ASSOR: append(str, end, size, " |= "); break;
        case ASSXOR: append(str, end, size, " ^= "); break;
        case ASSLSHIFT: append(str, end, size, " <<= "); break;
        case ASSRSHIFT: append(str, end, size, " >>= "); break;
        case MIN: append(str, end, size, " <? "); break;
        case MAX: append(str, end, size, " >? "); break;
        default: assert(0);
        }

        if (precedence >= get(1).getPrecedence()) {
            append(str, end, size, '(');
        }
        get(1).toString(old, str, end, size);
        if (precedence >= get(1).getPrecedence()) {
            append(str, end, size, ')');
        }
        break;

    case IDENTIFIER: append(str, end, size, data->symbol.getName().c_str()); break;

    case VARINDEX:
    case CONSTANT:
        if (getType().is(Constants::DOUBLE)) {
            snprintf(s, sizeof(s), "%f", getDoubleValue());
        } else if (getType().isString()) {
            snprintf(s, sizeof(s), "string#%d", data->value);
        } else if (getType().is(Constants::INT)) {
            snprintf(s, sizeof(s), "%d", data->value);
        } else {
            assert(getType().is(Constants::BOOL));
            snprintf(s, sizeof(s), "%s", data->value ? "true" : "false");
        }
        append(str, end, size, s);
        break;

    case ARRAY:
        if (precedence > get(0).getPrecedence()) {
            append(str, end, size, '(');
            get(0).toString(old, str, end, size);
            append(str, end, size, ')');
        } else {
            get(0).toString(old, str, end, size);
        }
        append(str, end, size, '[');
        get(1).toString(old, str, end, size);
        append(str, end, size, ']');
        break;

    case UNARY_MINUS:
        append(str, end, size, '-');
        if (precedence > get(0).getPrecedence()) {
            append(str, end, size, '(');
            get(0).toString(old, str, end, size);
            append(str, end, size, ')');
        } else {
            get(0).toString(old, str, end, size);
        }
        break;

    case POSTDECREMENT:
    case POSTINCREMENT:
        if (precedence > get(0).getPrecedence()) {
            append(str, end, size, '(');
            get(0).toString(old, str, end, size);
            append(str, end, size, ')');
        } else {
            get(0).toString(old, str, end, size);
        }
        append(str, end, size, getKind() == POSTDECREMENT ? "--" : "++");
        break;

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
    case FPCLASSIFY_F:
    case ISFINITE_F:
    case ISINF_F:
    case ISNAN_F:
    case ISNORMAL_F:
    case SIGNBIT_F:
    case ISUNORDERED_F:
    case RANDOM_F:
    case RANDOM_POISSON_F:
        append(str, end, size, getBuiltinFunName(data->kind));
        append(str, end, size, "(");
        get(0).toString(old, str, end, size);
        append(str, end, size, ')');
        break;

    case FMOD_F:
    case FMAX_F:
    case FMIN_F:
    case FDIM_F:
    case POW_F:
    case HYPOT_F:
    case ATAN2_F:
    case LDEXP_F:
    case NEXTAFTER_F:
    case COPYSIGN_F:
    case RANDOM_ARCSINE_F:
    case RANDOM_BETA_F:
    case RANDOM_GAMMA_F:
    case RANDOM_NORMAL_F:
    case RANDOM_WEIBULL_F:
        append(str, end, size, getBuiltinFunName(data->kind));
        append(str, end, size, "(");
        get(0).toString(old, str, end, size);
        append(str, end, size, ',');
        get(1).toString(old, str, end, size);
        append(str, end, size, ')');
        break;

    case FMA_F:
    case RANDOM_TRI_F:
        append(str, end, size, getBuiltinFunName(data->kind));
        append(str, end, size, "(");
        get(0).toString(old, str, end, size);
        append(str, end, size, ',');
        get(1).toString(old, str, end, size);
        append(str, end, size, ',');
        get(2).toString(old, str, end, size);
        append(str, end, size, ')');
        break;

    case XOR:
        append(str, end, size, '(');
        get(0).toString(old, str, end, size);
        append(str, end, size, ") xor (");
        get(1).toString(old, str, end, size);
        append(str, end, size, ')');
        break;

    case PREDECREMENT:
    case PREINCREMENT:
        append(str, end, size, getKind() == PREDECREMENT ? "--" : "++");
        if (precedence > get(0).getPrecedence()) {
            append(str, end, size, '(');
            get(0).toString(old, str, end, size);
            append(str, end, size, ')');
        } else {
            get(0).toString(old, str, end, size);
        }
        break;

    case NOT:
        append(str, end, size, '!');
        if (precedence > get(0).getPrecedence()) {
            append(str, end, size, '(');
            get(0).toString(old, str, end, size);
            append(str, end, size, ')');
        } else {
            get(0).toString(old, str, end, size);
        }
        break;

    case DOT: {
        type_t type = get(0).getType();
        if (type.isProcess() || type.isRecord()) {
            if (precedence > get(0).getPrecedence()) {
                append(str, end, size, '(');
                get(0).toString(old, str, end, size);
                append(str, end, size, ')');
            } else {
                get(0).toString(old, str, end, size);
            }
            append(str, end, size, '.');
            append(str, end, size, type.getRecordLabel(data->value).c_str());
        } else {
            assert(0);
        }
        break;
    }

    case INLINEIF:
        if (precedence >= get(0).getPrecedence()) {
            append(str, end, size, '(');
            get(0).toString(old, str, end, size);
            append(str, end, size, ')');
        } else {
            get(0).toString(old, str, end, size);
        }

        append(str, end, size, " ? ");

        if (precedence >= get(1).getPrecedence()) {
            append(str, end, size, '(');
            get(1).toString(old, str, end, size);
            append(str, end, size, ')');
        } else {
            get(1).toString(old, str, end, size);
        }

        append(str, end, size, " : ");

        if (precedence >= get(2).getPrecedence()) {
            append(str, end, size, '(');
            get(2).toString(old, str, end, size);
            append(str, end, size, ')');
        } else {
            get(2).toString(old, str, end, size);
        }

        break;

    case COMMA:
        get(0).toString(old, str, end, size);
        append(str, end, size, ", ");
        get(1).toString(old, str, end, size);
        break;

    case SYNC:
        get(0).toString(old, str, end, size);
        switch (data->sync) {
        case SYNC_QUE: append(str, end, size, '?'); break;
        case SYNC_BANG: append(str, end, size, '!'); break;
        case SYNC_CSP:
            // no append
            break;
        }
        break;

    case DEADLOCK: append(str, end, size, "deadlock"); break;

    case LIST:
        get(0).toString(old, str, end, size);
        for (uint32_t i = 1; i < getSize(); i++) {
            append(str, end, size, ", ");
            get(i).toString(old, str, end, size);
        }
        break;

    case FUNCALL:
    case EFUNCALL:
        get(0).toString(old, str, end, size);
        append(str, end, size, '(');
        if (getSize() > 1) {
            get(1).toString(old, str, end, size);
            for (uint32_t i = 2; i < getSize(); i++) {
                append(str, end, size, ", ");
                get(i).toString(old, str, end, size);
            }
        }
        append(str, end, size, ')');
        break;

    case RATE:
        get(0).toString(old, str, end, size);
        append(str, end, size, "'");
        break;

    case EF:
        append(str, end, size, "E<> ");
        get(0).toString(old, str, end, size);
        break;

    case EG:
        append(str, end, size, "E[] ");
        get(0).toString(old, str, end, size);
        break;

    case AF:
        append(str, end, size, "A<> ");
        get(0).toString(old, str, end, size);
        break;

    case AG:
        append(str, end, size, "A[] ");
        get(0).toString(old, str, end, size);
        break;

    case LEADSTO:
        get(0).toString(old, str, end, size);
        append(str, end, size, " --> ");
        get(1).toString(old, str, end, size);
        break;

    case A_UNTIL:
        append(str, end, size, "A[");
        get(0).toString(old, str, end, size);
        append(str, end, size, " U ");
        get(1).toString(old, str, end, size);
        append(str, end, size, "] ");
        break;

    case A_WEAKUNTIL:
        append(str, end, size, "A[");
        get(0).toString(old, str, end, size);
        append(str, end, size, " W ");
        get(1).toString(old, str, end, size);
        append(str, end, size, "] ");
        break;

    case A_BUCHI:
        append(str, end, size, "A[] ((");
        get(0).toString(old, str, end, size);
        append(str, end, size, ") and A<> ");
        get(1).toString(old, str, end, size);
        append(str, end, size, ") ");
        break;

    case FORALL:
        append(str, end, size, "forall (");
        append(str, end, size, get(0).getSymbol().getName().c_str());
        append(str, end, size, ":");
        append(str, end, size, get(0).getSymbol().getType().toString().c_str());
        append(str, end, size, ") ");
        get(1).toString(old, str, end, size);
        break;

    case EXISTS:
        append(str, end, size, "exists (");
        append(str, end, size, get(0).getSymbol().getName().c_str());
        append(str, end, size, ":");
        append(str, end, size, get(0).getSymbol().getType().toString().c_str());
        append(str, end, size, ") ");
        get(1).toString(old, str, end, size);
        break;

    case SUM:
        append(str, end, size, "sum (");
        append(str, end, size, get(0).getSymbol().getName().c_str());
        append(str, end, size, ":");
        append(str, end, size, get(0).getSymbol().getType().toString().c_str());
        append(str, end, size, ") ");
        get(1).toString(old, str, end, size);
        break;

    case SMC_CONTROL:
        assert(false);
        append(str, end, size, "control[");
        appendBoundType(str, end, size, get(0));
        get(1).toString(old, str, end, size);
        append(str, end, size, "]: ");
        get(2).toString(old, str, end, size);
        break;

    case PO_CONTROL:
        append(str, end, size, "{ ");
        get(0).toString(old, str, end, size);
        append(str, end, size, "} control: ");
        get(1).toString(old, str, end, size);
        break;

    case EF_CONTROL: append(str, end, size, "E<> "); [[fallthrough]];
    case CONTROL:
        append(str, end, size, "control: ");
        get(0).toString(old, str, end, size);
        break;

    case CONTROL_TOPT:
        append(str, end, size, "control_t*(");
        get(0).toString(old, str, end, size);
        append(str, end, size, ",");
        get(1).toString(old, str, end, size);
        append(str, end, size, "): ");
        get(2).toString(old, str, end, size);
        break;

    case CONTROL_TOPT_DEF1:
        append(str, end, size, "control_t*(");
        get(0).toString(old, str, end, size);
        append(str, end, size, "): ");
        get(1).toString(old, str, end, size);
        break;

    case CONTROL_TOPT_DEF2:
        append(str, end, size, "control_t*: ");
        get(0).toString(old, str, end, size);
        break;

    case SUP_VAR:
        append(str, end, size, "sup{");
        get(0).toString(old, str, end, size);
        append(str, end, size, "}: ");
        get(1).toString(old, str, end, size);
        break;

    case INF_VAR:
        append(str, end, size, "inf{");
        get(0).toString(old, str, end, size);
        append(str, end, size, "}: ");
        get(1).toString(old, str, end, size);
        break;

    case MITLFORMULA:
        append(str, end, size, "MITL: ");
        get(0).toString(old, str, end, size);
        break;
    case MITLRELEASE:
    case MITLUNTIL:
        get(0).toString(old, str, end, size);
        append(str, end, size, "U[");
        get(1).toString(old, str, end, size);
        append(str, end, size, ";");
        get(2).toString(old, str, end, size);
        append(str, end, size, "]");
        get(3).toString(old, str, end, size);
        break;

    case MITLDISJ:
        get(0).toString(old, str, end, size);
        append(str, end, size, "\\/");
        get(1).toString(old, str, end, size);
        break;
    case MITLCONJ:
        get(0).toString(old, str, end, size);
        append(str, end, size, "/\\");
        get(1).toString(old, str, end, size);
        break;
    case MITLATOM: get(0).toString(old, str, end, size); break;
    case MITLNEXT:
        append(str, end, size, "X(");
        get(0).toString(old, str, end, size);
        append(str, end, size, ")");
        break;
    case SPAWN: append(str, end, size, "SPAWN"); break;
    case EXIT: append(str, end, size, "EXIT"); break;
    case NUMOF:

        append(str, end, size, "numof(");
        get(0).toString(old, str, end, size);
        append(str, end, size, ")");
        break;
    case FORALLDYNAMIC:
        append(str, end, size, "forall (");
        get(0).toString(old, str, end, size);
        append(str, end, size, " : ");
        get(1).toString(old, str, end, size);
        append(str, end, size, " )( ");
        get(2).toString(old, str, end, size);
        append(str, end, size, ")");
        break;
    case SUMDYNAMIC:
        append(str, end, size, "sum (");
        get(0).toString(old, str, end, size);
        append(str, end, size, " : ");
        get(1).toString(old, str, end, size);
        append(str, end, size, " )( ");
        get(2).toString(old, str, end, size);
        append(str, end, size, ")");
        break;
    case FOREACHDYNAMIC:
        append(str, end, size, "foreach (");
        get(0).toString(old, str, end, size);
        append(str, end, size, " : ");
        get(1).toString(old, str, end, size);
        append(str, end, size, " )( ");
        get(2).toString(old, str, end, size);
        append(str, end, size, ")");
        break;
    case DYNAMICEVAL:
        get(1).toString(old, str, end, size);
        append(str, end, size, ".");
        get(0).toString(old, str, end, size);
        break;
    case PROCESSVAR: get(0).toString(old, str, end, size); break;
    case MITLEXISTS:
    case EXISTSDYNAMIC:
        append(str, end, size, "exists (");
        get(0).toString(old, str, end, size);
        append(str, end, size, " : ");
        get(1).toString(old, str, end, size);
        append(str, end, size, " )( ");
        get(2).toString(old, str, end, size);
        append(str, end, size, ")");
        break;
    case SAVE_STRAT: append(str, end, size, "saveStrategy (...)"); break;
    case LOAD_STRAT:
        append(str, end, size, "loadStrategy (");
        get(0).toString(old, str, end, size);
        if (!get(1).isTrue() && !get(2).isTrue()) {
            append(str, end, size, ", {");
            get(2).toString(old, str, end, size);
            append(str, end, size, "} -> {");
            get(3).toString(old, str, end, size);
            append(str, end, size, "}");
        }
        append(str, end, size, ")");
        break;
    default: throw std::logic_error("Support is not implemented for the given expression type");
    }
}

bool expression_t::operator<(const expression_t e) const
{
    return data != nullptr && e.data != nullptr && data < e.data;
}

bool expression_t::operator==(const expression_t e) const { return data == e.data; }

/** Returns a string representation of the expression. The string
    returned must be deallocated with delete[]. Returns NULL is the
    expression is empty. */
std::string expression_t::toString(bool old) const
{
    if (empty()) {
        return std::string();
    } else {
        int size = 16;
        char *s, *end;
        s = end = new char[size];
        *s = 0;
        toString(old, s, end, size);
        std::string result(s);
        delete[] s;
        return result;
    }
}

void expression_t::collectPossibleWrites(set<symbol_t>& symbols) const
{
    function_t* fun;
    symbol_t symbol;
    type_t type;

    if (empty()) {
        return;
    }

    for (uint32_t i = 0; i < getSize(); i++) {
        get(i).collectPossibleWrites(symbols);
    }

    switch (getKind()) {
    case ASSIGN:
    case ASSPLUS:
    case ASSMINUS:
    case ASSDIV:
    case ASSMOD:
    case ASSMULT:
    case ASSAND:
    case ASSOR:
    case ASSXOR:
    case ASSLSHIFT:
    case ASSRSHIFT:
    case POSTINCREMENT:
    case POSTDECREMENT:
    case PREINCREMENT:
    case PREDECREMENT: get(0).getSymbols(symbols); break;

    case EFUNCALL:
    case FUNCALL:
        // Add all symbols which are changed by the function
        symbol = get(0).getSymbol();
        if ((symbol.getType().isFunction() || symbol.getType().isExternalFunction()) && symbol.getData()) {
            fun = (function_t*)symbol.getData();

            symbols.insert(fun->changes.begin(), fun->changes.end());

            // Add arguments to non-constant reference parameters
            type = fun->uid.getType();
            for (uint32_t i = 1; i < min(getSize(), type.size()); i++) {
                if (type[i].is(REF) && !type[i].isConstant()) {
                    get(i).getSymbols(symbols);
                }
            }
        }
        break;

    default: break;
    }
}

void expression_t::collectPossibleReads(set<symbol_t>& symbols, bool collectRandom) const
{
    if (empty()) {
        return;
    }

    for (uint32_t i = 0; i < getSize(); i++) {
        get(i).collectPossibleReads(symbols);
    }

    switch (getKind()) {
    case IDENTIFIER: symbols.insert(getSymbol()); break;

    case FUNCALL: {
        // Add all symbols which are used by the function
        auto symbol = get(0).getSymbol();
        if (auto type = symbol.getType(); type.isFunction() || type.isExternalFunction()) {
            if (auto* data = symbol.getData(); data) {
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

expression_t expression_t::createConstant(int32_t value, position_t pos)
{
    expression_t expr(CONSTANT, pos);
    expr.data->value = value;
    expr.data->type = type_t::createPrimitive(Constants::INT);
    return expr;
}

expression_t expression_t::createVarIndex(int32_t value, position_t pos)
{
    expression_t expr(VARINDEX, pos);
    expr.data->value = value;
    expr.data->type = type_t::createPrimitive(Constants::INT);
    return expr;
}

expression_t expression_t::createExit(position_t pos)
{
    expression_t expr(EXIT, pos);
    expr.data->value = 0;
    expr.data->type = type_t::createPrimitive(Constants::VOID_TYPE);
    return expr;
}

expression_t expression_t::createDouble(double value, position_t pos)
{
    expression_t expr(CONSTANT, pos);
    expr.data->doubleValue = value;
    expr.data->type = type_t::createPrimitive(Constants::DOUBLE);
    return expr;
}

expression_t expression_t::createIdentifier(symbol_t symbol, position_t pos)
{
    expression_t expr(IDENTIFIER, pos);
    expr.data->symbol = symbol;
    if (symbol != symbol_t()) {
        expr.data->type = symbol.getType();
    } else {
        expr.data->type = type_t();
    }
    return expr;
}

expression_t expression_t::createNary(kind_t kind, vector<expression_t> sub, position_t pos, type_t type)
{
    expression_t expr(kind, pos);
    expr.data->value = sub.size();
    expr.data->sub = std::move(sub);
    expr.data->type = type;
    return expr;
}

expression_t expression_t::createUnary(kind_t kind, expression_t sub, position_t pos, type_t type)
{
    expression_t expr(kind, pos);
    expr.data->sub.push_back(sub);
    expr.data->type = type;
    return expr;
}

expression_t expression_t::createBinary(kind_t kind, expression_t left, expression_t right, position_t pos, type_t type)
{
    expression_t expr(kind, pos);
    expr.data->sub.reserve(2);
    expr.data->sub.push_back(left);
    expr.data->sub.push_back(right);
    expr.data->type = type;
    return expr;
}

expression_t expression_t::createTernary(kind_t kind, expression_t e1, expression_t e2, expression_t e3, position_t pos,
                                         type_t type)
{
    expression_t expr(kind, pos);
    expr.data->sub.reserve(3);
    expr.data->sub.push_back(e1);
    expr.data->sub.push_back(e2);
    expr.data->sub.push_back(e3);
    expr.data->type = type;
    return expr;
}

expression_t expression_t::createDot(expression_t e, int32_t idx, position_t pos, type_t type)
{
    expression_t expr(DOT, pos);
    expr.data->index = idx;
    expr.data->sub.push_back(e);
    expr.data->type = type;
    return expr;
}

expression_t expression_t::createSync(expression_t e, synchronisation_t s, position_t pos)
{
    expression_t expr(SYNC, pos);
    expr.data->sync = s;
    expr.data->sub.push_back(std::move(e));
    return expr;
}

expression_t expression_t::createDeadlock(position_t pos)
{
    expression_t expr(DEADLOCK, pos);
    expr.data->type = type_t::createPrimitive(CONSTRAINT);
    return expr;
}
