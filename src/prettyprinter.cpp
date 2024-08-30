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

#include "utap/prettyprinter.h"

#include <array>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <cassert>
#include <charconv>
#include <cstring>

using namespace UTAP;
using namespace UTAP::Constants;
using namespace std::string_literals;
using namespace std::string_view_literals;

static const std::string prefix_labels[] = {"", "const ", "urgent ", "", "broadcast ", "", "urgent broadcast ",
                                            "", "meta "};

inline std::string pop_back(std::vector<std::string>& vs)
{
    auto res = std::move(vs.back());
    vs.pop_back();
    return res;
}

inline std::string pop_top(std::stack<std::string>& ss)
{
    auto res = std::move(ss.top());
    ss.pop();
    return res;
}

void PrettyPrinter::indent()
{
    for (uint32_t i = 0; i < level; i++) {
        *o.top() << '\t';
    }
}

void PrettyPrinter::indent(std::string& s)
{
    for (uint32_t i = 0; i < level; i++) {
        s += '\t';
    }
}

PrettyPrinter::PrettyPrinter(std::ostream& stream)
{
    o.push(&stream);

    first = true;
    level = 0;
    select = guard = sync = update = probability = -1;
}

void PrettyPrinter::add_position(uint32_t position, uint32_t offset, uint32_t line, std::shared_ptr<std::string> path)
{}

void PrettyPrinter::handle_error(const TypeException& msg) { throw msg; }

void PrettyPrinter::handle_warning(const TypeException& msg) { throw msg; }

// FIXME: Scoping of type names is not handled
bool PrettyPrinter::is_type(const char* name) { return types.find(name) != types.end(); }

void PrettyPrinter::type_duplicate() { type.push(type.top()); }

void PrettyPrinter::type_pop() { type.pop(); }

void PrettyPrinter::type_bool(PREFIX prefix) { type.push(prefix_labels[prefix] + "bool"); }

void PrettyPrinter::type_int(PREFIX prefix) { type.push(prefix_labels[prefix] + "int"); }

void PrettyPrinter::type_string(PREFIX prefix) { type.push(prefix_labels[prefix] + "string"); }

void PrettyPrinter::type_double(PREFIX prefix) { type.push(prefix_labels[prefix] + "double"); }

void PrettyPrinter::type_bounded_int(PREFIX prefix)
{
    const auto u = pop_back(st);
    const auto l = pop_back(st);
    type.push(prefix_labels[prefix] + "int[" + l + "," + u + "]");
}

void PrettyPrinter::type_channel(PREFIX prefix) { type.push(prefix_labels[prefix] + "chan"); }

void PrettyPrinter::type_clock(PREFIX prefix) { type.push(prefix_labels[prefix] + "clock"); }

void PrettyPrinter::type_void() { type.emplace("void"); }

void PrettyPrinter::type_scalar(PREFIX prefix)
{
    const auto size = pop_back(st);
    type.push(prefix_labels[prefix] + "scalar[" + size + "]");
}

void PrettyPrinter::type_name(PREFIX prefix, const char* name) { type.push(prefix_labels[prefix] + name); }

void PrettyPrinter::type_array_of_size(size_t n) { array.push(pop_back(st)); }

void PrettyPrinter::type_array_of_type(size_t n)
{
    array.push(type.top());
    type.pop();
}
void PrettyPrinter::type_struct(PREFIX prefix, uint32_t n)
{
    std::stringstream ss;
    ss << prefix_labels[prefix];
    ss << "struct {\n";
    assert(fields.size() >= n);
    for (auto i = std::next(fields.begin(), fields.size() - n), e = fields.end(); i != e; ++i)
        ss << "    " << (*i) << ";\n";
    ss << "}";
    fields.erase(fields.begin() + (fields.size() - n), fields.end());
    type.push(ss.str());
}

void PrettyPrinter::struct_field(const char* name)
{
    std::stringstream ss;
    ss << type.top() << " " << name;
    type.pop();
    while (!array.empty()) {
        ss << "[" << array.top() << "]";
        array.pop();
    }
    fields.push_back(ss.str());
}

void PrettyPrinter::decl_typedef(const char* name)
{
    indent();
    *o.top() << "typedef " << type.top() << " " << name;
    type.pop();

    while (!array.empty()) {
        *o.top() << '[' << array.top() << ']';
        array.pop();
    }

    *o.top() << ";\n";

    types.insert(name);
}

void PrettyPrinter::decl_var(const char* id, bool init)
{
    auto i = std::string{};

    if (init)
        i = pop_back(st);

    indent();
    *o.top() << type.top() << ' ' << id;
    type.pop();

    while (!array.empty()) {
        *o.top() << '[' << array.top() << ']';
        array.pop();
    }

    if (init)
        *o.top() << " = " << i;

    *o.top() << ";\n";
}

void PrettyPrinter::decl_init_list(uint32_t num)
{
    auto s = pop_back(st);
    while (--num > 0)
        s = pop_back(st) + ", " + s;
    st.push_back("{ " + s + " }");
}

void PrettyPrinter::expr_scenario(const char* name) { st.push_back("scenario:"s + name); }

void PrettyPrinter::expr_nary(kind_t kind, uint32_t num)
{
    const char* opString = nullptr;
    switch (kind) {
    case LIST: opString = ", "; break;
    default: throw TypeException{"Invalid operator"};
    }

    auto s = pop_back(st);
    while (--num > 0)
        s = pop_back(st) + opString + s;
    st.push_back("{ " + s + " }");
}

void PrettyPrinter::decl_field_init(const char* name)
{
    if (name != nullptr && std::strlen(name) > 0) {
        st.back() = name + ": "s + st.back();
    }
}

void PrettyPrinter::decl_parameter(const char* name, bool ref)
{
    if (!array.empty())
        throw TypeException{"Array parameters are not supported"};
    if (!param.empty())
        param += ", ";
    if (ref)
        param += pop_top(type) + " &" + name;
    else
        param += pop_top(type) + " " + name;
}

void PrettyPrinter::decl_func_begin(const char* name)
{
    indent();
    *o.top() << pop_top(type) << " " << name << "(" << param << ")\n";
    indent();
    *o.top() << "{\n";
    param.clear();
    level++;
}

void PrettyPrinter::decl_func_end()
{
    level--;
    indent();
    *o.top() << "}\n";
}

void PrettyPrinter::dynamic_load_lib(const char* name) {}

void PrettyPrinter::decl_external_func(const char* name, const char* alias) {}

void PrettyPrinter::block_begin()
{
    level--;
    indent();
    *o.top() << "{\n";
    level++;
}

void PrettyPrinter::block_end()
{
    level--;  // The level delimiters are indented one level less
    indent();
    level++;
    *o.top() << "}\n";
}

void PrettyPrinter::empty_statement()
{
    indent();
    *o.top() << ";\n";
}

void PrettyPrinter::iteration_begin(const char* id)
{
    indent();
    *o.top() << "for ( " << id << " : " << type.top() << " )\n";
    level++;
    type.pop();
}

void PrettyPrinter::iteration_end(const char* id)
{
    *o.top() << '\n';
    level--;
}

void PrettyPrinter::for_begin()
{
    level++;
    o.push(new std::ostringstream());
}

void PrettyPrinter::for_end()  // 3 expr, 1 stat
{
    std::string expr3 = st.back();
    st.pop_back();
    std::string expr2 = st.back();
    st.pop_back();
    std::string expr1 = st.back();
    st.pop_back();
    auto* s = dynamic_cast<std::ostringstream*>(o.top());
    o.pop();

    level--;
    indent();
    *o.top() << "for ( " << expr1 << "; " << expr2 << "; " << expr3 << ")\n" << s->str() << '\n';
    delete s;
}

void PrettyPrinter::while_begin()
{
    level++;
    o.push(new std::ostringstream());
}

void PrettyPrinter::while_end()  // 1 expr, 1 stat
{
    std::string expr = st.back();
    st.pop_back();
    auto* s = dynamic_cast<std::ostringstream*>(o.top());
    o.pop();

    level--;
    indent();

    *o.top() << "while (" << expr << ")\n" << s->str() << '\n';
    delete s;
}

void PrettyPrinter::do_while_begin() {}

void PrettyPrinter::do_while_end() {}

void PrettyPrinter::if_begin()
{
    level++;
    o.push(new std::ostringstream());  // prepare for THEN statement
}

void PrettyPrinter::if_condition() {}

void PrettyPrinter::if_then()
{
    o.push(new std::ostringstream());  // prepare for ELSE statement
}

void PrettyPrinter::if_end(bool hasElse)  // 1 expr, 1 or 2 statements
{
    auto* e = dynamic_cast<std::ostringstream*>(o.top());
    o.pop();  // ELSE
    auto* t = dynamic_cast<std::ostringstream*>(o.top());
    o.pop();  // THEN
    auto c = st.back();
    st.pop_back();  // COND

    level--;
    indent();
    *o.top() << "if (" << c << ")\n" << t->str();
    delete t;
    if (hasElse) {
        indent();
        *o.top() << "else\n";
        *o.top() << e->str();
    }
    delete e;
}

void PrettyPrinter::break_statement()
{
    indent();
    *o.top() << "break;\n";
}

void PrettyPrinter::continue_statement()
{
    indent();
    *o.top() << "continue;\n";
}

void PrettyPrinter::expr_statement()
{
    indent();
    *o.top() << st.back() << ";\n";
    st.pop_back();
}

void PrettyPrinter::return_statement(bool hasValue)
{
    indent();
    if (hasValue) {
        *o.top() << "return " << st.back() << ";\n";
        st.pop_back();
    } else {
        *o.top() << "return;\n";
    }
}

void PrettyPrinter::proc_begin(const char* id, const bool isTA, const std::string& type, const std::string& mode)
{
    *o.top() << "process " << (id != nullptr ? id : "") << templateset << '(' << param << ")\n{\n";
    param.clear();
    templateset = "";

    level += 1;
}

void PrettyPrinter::proc_location(const char* id, bool hasInvariant, bool hasExpRate)
{
    if (first) {
        first = false;
        indent();
        *o.top() << "state\n";
    } else {
        *o.top() << ",\n";
    }

    level++;
    indent();
    level--;

    *o.top() << id;
    std::string expRate;  // pop expressions from stack in reverse order
    if (hasExpRate) {
        expRate = st.back();
        st.pop_back();
    }
    if (hasInvariant) {
        *o.top() << " {" << st.back();
        st.pop_back();
        if (hasExpRate)
            *o.top() << " ; " << expRate;
        *o.top() << "}";
    } else if (hasExpRate) {
        *o.top() << " { ; " << expRate << "}";
    }
}

void PrettyPrinter::proc_branchpoint(const char* id)
{
    if (!branchpoints.empty())
        branchpoints += ", ";
    branchpoints += id;
}

void PrettyPrinter::proc_location_urgent(const char* id)
{
    if (!urgent.empty())
        urgent += ", ";
    urgent += id;
}

void PrettyPrinter::proc_location_commit(const char* id)
{
    if (!committed.empty())
        committed += ", ";
    committed += id;
}

void PrettyPrinter::proc_location_init(const char* id)
{
    first = true;
    *o.top() << ";\n";  // end of states

    if (!branchpoints.empty()) {
        indent();
        *o.top() << "branchpoint " << branchpoints << ";\n";
        branchpoints.clear();
    }

    if (!committed.empty()) {
        indent();
        *o.top() << "commit " << committed << ";\n";
        committed.clear();
    }

    if (!urgent.empty()) {
        indent();
        *o.top() << "urgent " << urgent << ";\n";
        urgent.clear();
    }

    indent();
    *o.top() << "init " << id << ";\n";
}

void PrettyPrinter::proc_select(const char* id)
{
    std::string t = type.top();
    type.pop();
    if (select == -1) {
        st.push_back(std::string{id} + ":" + t);
        select = st.size();
    } else {
        st.back() += std::string{", "} + id + ":" + t;
    }
}

void PrettyPrinter::proc_guard() { guard = st.size(); }

void PrettyPrinter::proc_sync(synchronisation_t type)
{
    switch (type) {
    case SYNC_QUE: st.back() += '?'; break;
    case SYNC_BANG: st.back() += '!'; break;
    case SYNC_CSP:
        // no append
        break;
    }
    sync = st.size();
}

void PrettyPrinter::proc_update() { update = st.size(); }

// void PrettyPrinter::proc_prob() { probability = st.size(); }

void PrettyPrinter::proc_edge_begin(const char* from, const char* to, const bool control)

{
    proc_edge_begin(from, to, control, nullptr);
}

void PrettyPrinter::proc_edge_begin(const char* source, const char* target, const bool control, const char* actname)
{
    if (first) {
        // this is the first transition
        first = false;

        indent();
        *o.top() << "trans\n";

        level++;
    } else {
        *o.top() << ",\n";
    }
    indent();

    *o.top() << source << (control ? " -> " : " -u-> ") << target << " {\n";
    if (actname != nullptr) {
        level++;
        indent();
        *o.top() << "action " << actname << ";\n";
        level--;
    }
}

void PrettyPrinter::proc_edge_end(const char* source, const char* target)
{
    level++;

    if (select > -1) {
        indent();
        *o.top() << "select " << st[select - 1] << ";\n";
    }

    if (guard > -1) {
        indent();
        *o.top() << "guard " << st[guard - 1] << ";\n";
    }

    if (sync > -1) {
        indent();
        *o.top() << "sync " << st[sync - 1] << ";\n";
    }

    if (update > -1) {
        indent();
        *o.top() << "assign " << st[update - 1] << ";\n";
    }

    if (probability > -1) {
        indent();
        *o.top() << "probability " << st[probability - 1] << ";\n";
    }

    level--;

    if (probability > -1)
        st.pop_back();
    if (update > -1)
        st.pop_back();
    if (sync > -1)
        st.pop_back();
    if (guard > -1)
        st.pop_back();
    if (select > -1)
        st.pop_back();

    probability = update = sync = guard = select = -1;

    indent();
    *o.top() << '}';
}

void PrettyPrinter::proc_end()
{
    if (!first) {
        *o.top() << ";\n";
        level--;
        first = true;
    }
    level--;
    *o.top() << "}\n\n";
}

void PrettyPrinter::expr_identifier(const char* id) { st.emplace_back(id); }

void PrettyPrinter::expr_nat(int32_t n)
{
    char s[20];
    if (20 <= snprintf(s, 20, "%d", n)) {
        fprintf(stderr, "Error: the integer number was truncated\n");
    }
    st.emplace_back(s);
}

void PrettyPrinter::expr_true() { st.emplace_back("true"); }

void PrettyPrinter::expr_false() { st.emplace_back("false"); }

void PrettyPrinter::expr_double(double d)
{
    auto s = std::array<char, 60>{};
#if defined(__GNUC__) && (__GNUC__ < 11)
    // g++-10 does not have std::to_char(It,It,float/double), hence temporary workaround:
    if (60 <= std::snprintf(s.data(), 60, "%.52g", d))
        std::cerr << "Floating point number was truncated\n";
#else
    if (auto [_, ec] = std::to_chars(s.begin(), s.end(), d, std::chars_format::general, 52); ec != std::errc{})
        throw std::runtime_error{std::make_error_code(ec).message()};
#endif
    st.emplace_back(s.data());
}

void PrettyPrinter::expr_string(const char* val) { st.emplace_back(val); }

void PrettyPrinter::expr_call_begin() { st.back() += "("; }

void PrettyPrinter::expr_call_end(uint32_t n)
{
    std::string s = ")";
    while (n-- > 0) {
        s = st.back() + s;
        st.pop_back();
        if (n > 0) {
            s = ", " + s;
        }
    }
    st.back() += s;
}

void PrettyPrinter::expr_array()
{
    std::string f = st.back();
    st.pop_back();
    st.back() += '[' + f + ']';
}

void PrettyPrinter::expr_post_increment() { st.back() += "++"; }

void PrettyPrinter::expr_pre_increment() { st.back() = "++" + st.back(); }

void PrettyPrinter::expr_post_decrement() { st.back() += "--"; }

void PrettyPrinter::expr_pre_decrement() { st.back() = "--" + st.back(); }

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

void PrettyPrinter::expr_builtin_function1(kind_t kind)
{
    st.back() = std::string(get_builtin_fun_name(kind)) + '(' + st.back() + ')';
}

void PrettyPrinter::expr_builtin_function2(kind_t kind)
{
    auto arg2 = st.back();
    st.pop_back();
    st.back() = std::string(get_builtin_fun_name(kind)) + '(' + st.back() + ',' + arg2 + ')';
}

void PrettyPrinter::expr_builtin_function3(kind_t kind)
{
    auto arg3 = st.back();
    st.pop_back();
    auto arg2 = st.back();
    st.pop_back();
    st.back() = std::string(get_builtin_fun_name(kind)) + '(' + st.back() + ',' + arg2 + ',' + arg3 + ')';
}

void PrettyPrinter::expr_assignment(kind_t op)
{
    auto rhs = std::move(st.back());
    st.pop_back();
    auto lhs = std::move(st.back());
    st.pop_back();

    st.emplace_back();
    switch (op) {
    case ASSIGN: st.back() = '(' + lhs + " = " + rhs + ')'; break;
    case ASS_PLUS: st.back() = '(' + lhs + " += " + rhs + ')'; break;
    case ASS_MINUS: st.back() = '(' + lhs + " -= " + rhs + ')'; break;
    case ASS_MULT: st.back() = '(' + lhs + " *= " + rhs + ')'; break;
    case ASS_DIV: st.back() = '(' + lhs + " /= " + rhs + ')'; break;
    case ASS_MOD: st.back() = '(' + lhs + " %= " + rhs + ')'; break;
    case ASS_OR: st.back() = '(' + lhs + " |= " + rhs + ')'; break;
    case ASS_AND: st.back() = '(' + lhs + " &= " + rhs + ')'; break;
    case ASS_XOR: st.back() = '(' + lhs + " ^= " + rhs + ')'; break;
    case ASS_LSHIFT: st.back() = '(' + lhs + " <<= " + rhs + ')'; break;
    case ASS_RSHIFT: st.back() = '(' + lhs + " >>= " + rhs + ')'; break;
    default: throw TypeException{"Invalid assignment operator"};
    }
}

void PrettyPrinter::expr_unary(kind_t op)
{
    auto exp = std::move(st.back());
    st.pop_back();

    st.emplace_back();
    switch (op) {
    case MINUS: st.back() = '-' + exp; break;
    case NOT: st.back() = '!' + exp; break;
    case PLUS: st.back() = '+' + exp; break;
    case RATE: st.back() = exp + '\''; break;
    case CONTROL_TOPT_DEF2: st.back() = "control_t*: " + exp; break;
    case CONTROL: st.back() = "control: " + exp; break;
    case EF_CONTROL: st.back() = "E<> control: " + exp; break;
    default: throw TypeException{"Invalid operator"};
    }
}

void PrettyPrinter::expr_binary(kind_t op)
{
    auto exp2 = std::move(st.back());
    st.pop_back();
    auto exp1 = std::move(st.back());
    st.pop_back();

    st.emplace_back();
    switch (op) {
    case PO_CONTROL: st.back() = exp1 + " control: " + exp2; break;
    case CONTROL_TOPT_DEF1: st.back() = "control_t*(" + exp1 + "): " + exp2; break;
    case PLUS: st.back() = '(' + exp1 + " + " + exp2 + ')'; break;
    case MINUS: st.back() = '(' + exp1 + " - " + exp2 + ')'; break;
    case MULT: st.back() = '(' + exp1 + " * " + exp2 + ')'; break;
    case DIV: st.back() = '(' + exp1 + " / " + exp2 + ')'; break;
    case MOD: st.back() = '(' + exp1 + " % " + exp2 + ')'; break;
    case POW: st.back() = '(' + exp1 + " ** " + exp2 + ')'; break;
    case FRACTION: st.back() = '(' + exp1 + " : " + exp2 + ')'; break;
    case MIN: st.back() = '(' + exp1 + " <? " + exp2 + ')'; break;
    case MAX: st.back() = '(' + exp1 + " >? " + exp2 + ')'; break;
    case LT: st.back() = '(' + exp1 + " < " + exp2 + ')'; break;
    case LE: st.back() = '(' + exp1 + " <= " + exp2 + ')'; break;
    case EQ: st.back() = '(' + exp1 + " == " + exp2 + ')'; break;
    case NEQ: st.back() = '(' + exp1 + " != " + exp2 + ')'; break;
    case GE: st.back() = '(' + exp1 + " >= " + exp2 + ')'; break;
    case GT: st.back() = '(' + exp1 + " > " + exp2 + ')'; break;
    case AND: st.back() = '(' + exp1 + " && " + exp2 + ')'; break;
    case OR: st.back() = '(' + exp1 + " || " + exp2 + ')'; break;
    case BIT_AND: st.back() = '(' + exp1 + " & " + exp2 + ')'; break;
    case BIT_OR: st.back() = '(' + exp1 + " | " + exp2 + ')'; break;
    case BIT_XOR: st.back() = '(' + exp1 + " ^ " + exp2 + ')'; break;
    case BIT_LSHIFT: st.back() = '(' + exp1 + " << " + exp2 + ')'; break;
    case BIT_RSHIFT: st.back() = '(' + exp1 + " >> " + exp2 + ')'; break;
    default: throw TypeException{"Invalid operator"};
    }
}

void PrettyPrinter::expr_ternary(kind_t op, bool firstMissing)
{
    auto exp3 = std::move(st.back());
    st.pop_back();
    auto exp2 = std::move(st.back());
    st.pop_back();
    std::string exp1;
    if (firstMissing)
        exp1 = "1";
    else {
        exp1 = st.back();
        st.pop_back();
    }

    st.emplace_back();
    switch (op) {
    case CONTROL_TOPT: st.back() = "control_t*(" + exp1 + "," + exp2 + "): " + exp3; break;
    case SMC_CONTROL: st.back() = "control[" + exp1 + "<=" + exp2 + "]: " + exp3; break;
    default: throw TypeException{"Invalid operator"};
    }
}

void PrettyPrinter::expr_inline_if()
{
    auto expr3 = std::move(st.back());
    st.pop_back();
    auto expr2 = std::move(st.back());
    st.pop_back();
    auto expr1 = std::move(st.back());
    st.pop_back();
    st.emplace_back();
    st.back() = expr1 + " ? " + expr2 + " : " + expr3;
}

void PrettyPrinter::expr_comma()
{
    auto expr2 = std::move(st.back());
    st.pop_back();
    auto expr1 = std::move(st.back());
    st.pop_back();
    st.emplace_back();
    st.back() = expr1 + ", " + expr2;
}

void PrettyPrinter::expr_dot(const char* field) { st.back() = st.back() + "." + field; }

void PrettyPrinter::expr_location() { st.back() = st.back() + ".location"; }

void PrettyPrinter::expr_deadlock() { st.emplace_back("deadlock"); }

void PrettyPrinter::expr_forall_begin(const char* name)
{
    st.push_back(std::string("forall (") + name + ":" + type.top() + ") ");
    type.pop();
}

void PrettyPrinter::expr_forall_end(const char* name)
{
    std::string expr = st.back();
    st.pop_back();
    st.back() += expr;
}

void PrettyPrinter::expr_exists_begin(const char* name)
{
    st.push_back(std::string("exists (") + name + ":" + type.top() + ") ");
    type.pop();
}

void PrettyPrinter::expr_exists_end(const char* name)
{
    std::string expr = st.back();
    st.pop_back();
    st.back() += expr;
}

void PrettyPrinter::expr_sum_begin(const char* name)
{
    st.push_back(std::string("sum (") + name + ":" + type.top() + ") ");
    type.pop();
}

void PrettyPrinter::expr_sum_end(const char* name)
{
    std::string expr = st.back();
    st.pop_back();
    st.back() += expr;
}

void PrettyPrinter::before_update()
{
    *o.top() << "{\n";
    level++;
    indent();
    level--;
    *o.top() << st.back() << '\n';
    *o.top() << "}\n";
}

void PrettyPrinter::after_update()
{
    *o.top() << "{\n";
    level++;
    indent();
    level--;
    *o.top() << st.back() << '\n';
    *o.top() << "}\n";
}

void PrettyPrinter::instantiation_begin(const char* id, size_t, const char* templ)
{
    // Ignore
}

void PrettyPrinter::instantiation_end(const char* id, size_t parameters, const char* templ, size_t arguments)
{
    auto s = std::stack<std::string>{};
    while (arguments-- > 0)
        s.push(pop_back(st));

    *o.top() << id << " = " << templ << '(';
    if (!s.empty()) {
        *o.top() << pop_top(s);
        while (!s.empty())
            *o.top() << ", " << pop_top(s);
    }
    *o.top() << ");\n";
}

void PrettyPrinter::process(const char* id)
{
    if (first) {
        *o.top() << "system " << id;
        first = false;
    } else {
        *o.top() << ", " << id;
    }
}

void PrettyPrinter::process_list_end() { *o.top() << ";\n"; }

void PrettyPrinter::done() {}

/*
void PrettyPrinter::exprProba(bool isTimedBound, int type, double proba, int ineq)
{
    const auto pred = pop_back(st);
    const auto bound = pop_back(st);
    auto ss = std::stringstream{};
    ss << "Pr[" << (isTimedBound ? "time" : "steps") << "<="
       << bound << "](" << (type == BOX ? "[] " : "<> ")
       << pred << ") " << (ineq == LE ? "<=" : ">=") << proba;
    st.push_back(ss.str());
}

void PrettyPrinter::exprProba2(bool isTimedBound, int type)
{
    const auto pred = pop_back(st);
    const auto bound = pop_back(st);
    auto ss = std::stringstream{};
    ss << "Pr[" << (isTimedBound ? "time" : "steps") << "<="
       << bound << "](" << (type == BOX ? "[] " : "<> ")
       << pred << ") ?";
    st.push_back(ss.str());
}
*/
void PrettyPrinter::expr_proba_quantitative(Constants::kind_t type)
{
    const auto pred2 = pop_back(st);
    const auto pred1 = pop_back(st);
    const auto bound = pop_back(st);
    const auto bounded = pop_back(st);
    auto ss = std::stringstream{};
    /* FIXME
        ss << "Pr[" << (isTimedBound ? "time" : "steps") << "<=" << bound << "](" << (type == BOX ? "[] " : "<> ");
        if (usesUntil)
            ss << pred1 << " U " << pred2;
        else
            ss << pred2;
        ss << ")";
        st.push_back(ss.str());
    */
}

void PrettyPrinter::expr_MITL_diamond(int low, int high)
{
    const auto expr = pop_back(st);
    auto ss = std::stringstream{};
    ss << "(<>[" << low << "," << high << "] " << expr << ")";
    st.push_back(ss.str());
}

void PrettyPrinter::expr_MITL_box(int low, int high)
{
    const auto expr = pop_back(st);
    auto ss = std::stringstream{};
    ss << "([][" << low << "," << high << "] " << expr << ")";
    st.push_back(ss.str());
}

void PrettyPrinter::expr_simulate(int nbExpr, bool hasReach, int nbOfAcceptingRuns)
{
    auto reachExpr = st.back();
    if (hasReach)
        st.pop_back();

    auto exprs = std::stack<std::string>{};
    for (auto i = 0; i < nbExpr; ++i)
        exprs.push(pop_back(st));
    const auto nbRuns = pop_back(st);
    const auto bound = pop_back(st);
    auto boundedExpr = pop_back(st);
    if (boundedExpr == "0")
        boundedExpr = "#";
    else if (boundedExpr == "1")
        boundedExpr = " ";

    auto ss = std::stringstream{};
    ss << "simulate"
       << " [" << boundedExpr << "<=" << bound << "; " << nbRuns << "] {";
    if (!exprs.empty()) {
        ss << pop_top(exprs);
        while (!exprs.empty())
            ss << ", " << pop_top(exprs);
    }
    ss << "}";
    if (hasReach) {
        if (nbOfAcceptingRuns > 0) {
            ss << " : " << nbOfAcceptingRuns;
        }
        ss << " : " << reachExpr;
    }
    st.push_back(ss.str());
}

/** Built-in verification queries if any */
void PrettyPrinter::query_begin() { *o.top() << "\n/** Query begin: */\n"; }
void PrettyPrinter::query_formula(const char* formula, const char* location)
{
    if (formula != nullptr)
        *o.top() << "/* Formula: " << formula << " */\n";
}
void PrettyPrinter::query_comment(const char* comment)
{
    if (comment != nullptr)
        *o.top() << "/* Comment: " << comment << " */\n";
}
void PrettyPrinter::query_end() { *o.top() << "/** Query end. */\n"; }
