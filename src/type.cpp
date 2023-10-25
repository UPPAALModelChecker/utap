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

#include "utap/type.h"

#include "utap/expression.h"

#include <algorithm>
#include <sstream>
#include <cassert>

using std::string;
using std::vector;

using namespace UTAP;
using namespace Constants;

struct child_t
{
    string label;
    type_t child;
    position_t position;
};

struct type_t::type_data
{
    kind_t kind;          // Kind of type object
    position_t position;  // Position in the input file
    expression_t expr;    //
    std::vector<child_t> children;
    type_data(kind_t kind, position_t position): kind{kind}, position{position} {}
};

type_t::type_t(kind_t kind, const position_t& pos, size_t size)
{
    data = std::make_shared<type_data>(kind, pos);
    data->children.resize(size);
}

bool type_t::operator==(const type_t& type) const { return data == type.data; }

bool type_t::operator!=(const type_t& type) const { return data != type.data; }

bool type_t::operator<(const type_t& type) const { return data < type.data; }

size_t type_t::size() const
{
    assert(data);
    return data->children.size();
}

type_t type_t::operator[](uint32_t i) const
{
    assert(i < size());
    return data->children[i].child;
}

type_t type_t::get(uint32_t i) const
{
    assert(i < size());
    return data->children[i].child;
}

const std::string& type_t::get_label(uint32_t i) const
{
    assert(i < size());
    return data->children[i].label;
}

const position_t& type_t::get_field_position(uint32_t i) const
{
    assert(i < size());
    return data->children[i].position;
}

std::optional<uint32_t> type_t::find_index_of(const std::string& label) const
{
    assert(is_record() || is_process());
    type_t type = strip();
    size_t n = type.size();
    for (size_t i = 0; i < n; ++i) {
        if (type.get_label(i) == label) {
            return i;
        }
    }
    return {};
}

kind_t type_t::get_kind() const { return unknown() ? UNKNOWN : data->kind; }

bool type_t::is_prefix() const
{
    switch (get_kind()) {
    case Constants::FRACTION:
    case Constants::UNKNOWN:
    case Constants::VOID_TYPE:
    case Constants::CLOCK:
    case Constants::INT:
    case Constants::DOUBLE:
    case Constants::BOOL:
    case Constants::STRING:
    case Constants::SCALAR:
    case Constants::LOCATION:
    case Constants::LOCATION_EXPR:
    case Constants::BRANCHPOINT:
    case Constants::CHANNEL:
    case Constants::COST:
    case Constants::INVARIANT:
    case Constants::INVARIANT_WR:
    case Constants::GUARD:
    case Constants::DIFF:
    case Constants::CONSTRAINT:
    case Constants::FORMULA:
    case Constants::ARRAY:
    case Constants::RECORD:
    case Constants::PROCESS:
    case Constants::PROCESS_SET:
    case Constants::FUNCTION:
    case Constants::FUNCTION_EXTERNAL:
    case Constants::INSTANCE:
    case Constants::RANGE:
    case Constants::REF:
    case Constants::TYPEDEF:
    case Constants::LABEL:
    case Constants::RATE:
    case Constants::INSTANCE_LINE:  // LSC
    case Constants::MESSAGE:        // LSC
    case Constants::CONDITION:      // LSC
    case Constants::UPDATE:         // LSC
    case Constants::LSC_INSTANCE:   // LSC
        return false;

    default: return true;
    }
}

bool type_t::unknown() const { return data == nullptr || data->kind == UNKNOWN; }

bool type_t::is(kind_t kind) const
{
    using namespace Constants;
    const auto k = get_kind();
    if (k == PROCESS_VAR) {
        return kind == PROCESS_VAR;
    }
    if (k == DOUBLE_INV_GUARD) {
        return kind == DOUBLE_INV_GUARD;
    }
    return (k == kind) || (is_prefix() && get(0).is(kind)) || (k == RANGE && get(0).is(kind)) ||
           (k == REF && get(0).is(kind)) || (k == LABEL && get(0).is(kind));
}

type_t type_t::get_sub() const
{
    assert(is_array());
    const auto k = get_kind();
    if (k == REF || get_kind() == LABEL) {
        return get(0).get_sub();
    } else if (is_prefix()) {
        return get(0).get_sub().create_prefix(k);
    } else {
        return get(0);
    }
}

type_t type_t::get_sub(uint32_t i) const
{
    assert(is_record() || is_process());
    const auto k = get_kind();
    if (k == REF || k == LABEL) {
        return get(0).get_sub(i);
    } else if (is_prefix()) {
        return get(0).get_sub(i).create_prefix(k);
    } else {
        return get(i);
    }
}

type_t type_t::get_array_size() const
{
    const auto k = get_kind();
    if (is_prefix() || k == REF || k == LABEL) {
        return get(0).get_array_size();
    } else {
        assert(k == ARRAY);
        return get(1);
    }
}

uint32_t type_t::get_record_size() const
{
    const auto k = get_kind();
    if (is_prefix() || k == REF || k == LABEL) {
        return get(0).get_record_size();
    } else {
        assert(k == RECORD);
        return size();
    }
}

const string& type_t::get_record_label(size_t i) const
{
    static const auto location = std::string{"location"};
    const auto k = get_kind();
    if (is_prefix() || k == REF || k == LABEL) {
        return get(0).get_record_label(i);
    } else if (i == static_cast<size_t>(std::numeric_limits<int32_t>::max())) {  // TODO: create a separate type for
                                                                                 // location expressions and get rid
                                                                                 // of magical constants
        return location;
    } else {
        assert(k == RECORD || k == PROCESS);
        return get_label(i);
    }
}

std::pair<expression_t, expression_t> type_t::get_range() const
{
    assert(is(RANGE));
    if (get_kind() == RANGE) {
        return std::make_pair(get(1).get_expression(), get(2).get_expression());
    } else {
        return get(0).get_range();
    }
}

expression_t type_t::get_expression() const
{
    assert(data);
    return data->expr;
}

type_t type_t::strip() const
{
    const auto k = get_kind();
    if (is_prefix() || k == RANGE || k == REF || k == LABEL) {
        return get(0).strip();
    } else {
        return *this;
    }
}

type_t type_t::strip_array() const
{
    type_t type = strip();
    while (type.get_kind() == ARRAY) {
        type = type.get(0).strip();
    }
    return type;
}

type_t type_t::rename(const std::string& from, const std::string& to) const
{
    auto type = type_t{get_kind(), get_position(), size()};
    type.data->expr = get_expression();
    for (size_t i = 0; i < size(); ++i) {
        type.data->children[i].child = get(i).rename(from, to);
        type.data->children[i].label = get_label(i);
    }
    if (get_kind() == LABEL && get_label(0) == from) {
        type.data->children[0].label = to;
    }
    return type;
}

type_t type_t::subst(symbol_t symbol, expression_t expr) const
{
    auto type = type_t{get_kind(), get_position(), size()};
    for (size_t i = 0; i < size(); i++) {
        type.data->children[i].label = get_label(i);
        type.data->children[i].child = get(i).subst(symbol, expr);
    }
    if (!data->expr.empty()) {
        type.data->expr = data->expr.subst(symbol, expr);
    }
    return type;
}

position_t type_t::get_position() const { return data->position; }

bool type_t::is_constant() const
{
    switch (get_kind()) {
    case FUNCTION:
    case FUNCTION_EXTERNAL:
    case PROCESS:
    case INSTANCE:
    case LSC_INSTANCE: return false;
    case CONSTANT: return true;
    case RECORD:
        return std::all_of(data->children.begin(), data->children.end(),
                           [](const child_t& c) { return c.child.is_constant(); });
    default: return size() > 0 && get(0).is_constant();
    }
}

bool type_t::is_mutable() const
{
    switch (get_kind()) {
    case FUNCTION:
    case FUNCTION_EXTERNAL:
    case PROCESS:
    case INSTANCE:
    case LSC_INSTANCE:
    case CONSTANT: return false;
    case RECORD:
        return std::all_of(data->children.begin(), data->children.end(),
                           [](const child_t& c) { return c.child.is_mutable(); });
    default: return size() == 0 || get(0).is_mutable();
    }
}

type_t type_t::create_range(type_t type, expression_t lower, expression_t upper, position_t pos)
{
    auto t = type_t{RANGE, pos, 3};
    t.data->children[0].child = std::move(type);
    t.data->children[1].child = type_t{UNKNOWN, pos, 0};
    t.data->children[2].child = type_t{UNKNOWN, pos, 0};
    t[1].data->expr = lower;
    t[2].data->expr = upper;
    return t;
}

type_t type_t::create_record(const vector<type_t>& types, const vector<string>& labels,
                             const std::vector<position_t>& positions, position_t pos)
{
    assert(types.size() == labels.size());
    auto type = type_t{RECORD, pos, types.size()};
    for (size_t i = 0; i < types.size(); i++) {
        type.data->children[i].child = types[i];
        type.data->children[i].label = labels[i];
        type.data->children[i].position = positions[i];
    }
    return type;
}

type_t type_t::create_function(type_t ret, const std::vector<type_t>& parameters,
                               const std::vector<std::string>& labels, position_t pos)
{
    assert(parameters.size() == labels.size());
    auto type = type_t{FUNCTION, pos, parameters.size() + 1};
    type.data->children[0].child = ret;
    for (size_t i = 0; i < parameters.size(); i++) {
        type.data->children[i + 1].child = parameters[i];
        type.data->children[i + 1].label = labels[i];
    }
    return type;
}

type_t type_t::create_external_function(type_t ret, const std::vector<type_t>& parameters,
                                        const std::vector<std::string>& labels, position_t pos)
{
    assert(parameters.size() == labels.size());
    auto type = type_t{FUNCTION_EXTERNAL, pos, parameters.size() + 1};
    type.data->children[0].child = ret;
    for (size_t i = 0; i < parameters.size(); i++) {
        type.data->children[i + 1].child = parameters[i];
        type.data->children[i + 1].label = labels[i];
    }
    return type;
}

type_t type_t::create_array(type_t sub, type_t size, position_t pos)
{
    auto type = type_t{ARRAY, pos, 2};
    type.data->children[0].child = sub;
    type.data->children[1].child = size;
    return type;
}

type_t type_t::create_typedef(std::string label, type_t type, position_t pos)
{
    auto t = type_t{TYPEDEF, pos, 1};
    t.data->children[0].label = label;
    t.data->children[0].child = type;
    return t;
}

type_t type_t::create_instance(frame_t parameters, position_t pos)
{
    auto type = type_t{INSTANCE, pos, parameters.get_size()};
    for (size_t i = 0; i < parameters.get_size(); ++i) {
        type.data->children[i].child = parameters[i].get_type();
        type.data->children[i].label = parameters[i].get_name();
    }
    return type;
}

type_t type_t::create_LSC_instance(frame_t parameters, position_t pos)
{
    auto type = type_t{LSC_INSTANCE, pos, parameters.get_size()};
    for (size_t i = 0; i < parameters.get_size(); ++i) {
        type.data->children[i].child = parameters[i].get_type();
        type.data->children[i].label = parameters[i].get_name();
    }
    return type;
}

type_t type_t::create_process(frame_t frame, position_t pos)
{
    auto type = type_t{PROCESS, pos, frame.get_size()};
    for (size_t i = 0; i < frame.get_size(); ++i) {
        type.data->children[i].child = frame[i].get_type();
        type.data->children[i].label = frame[i].get_name();
    }
    return type;
}

type_t type_t::create_process_set(type_t instance, position_t pos)
{
    auto type = type_t{PROCESS_SET, pos, instance.size()};
    for (size_t i = 0; i < instance.size(); ++i) {
        type.data->children[i].child = instance[i];
        type.data->children[i].label = instance.get_label(i);
    }
    return type;
}

type_t type_t::create_primitive(kind_t kind, position_t pos) { return type_t(kind, pos, 0); }

type_t type_t::create_prefix(kind_t kind, position_t pos) const
{
    type_t type(kind, pos, 1);
    type.data->children[0].child = *this;
    return type;
}

type_t type_t::create_label(string label, position_t pos) const
{
    type_t type(LABEL, pos, 1);
    type.data->children[0].child = *this;
    type.data->children[0].label = label;
    return type;
}

std::ostream& type_t::print(std::ostream& os) const
{
    if (data == nullptr)
        return os << "unknown";

    if (!data->expr.empty())
        return data->expr.print(os << '"') << '"';

    os << "(";
    switch (get_kind()) {
    case UNKNOWN: os << "unknown"; break;
    case RANGE: os << "range"; break;
    case ARRAY: os << "array"; break;
    case RECORD: os << "struct"; break;
    case CONSTANT: os << "const"; break;
    case REF: os << "ref"; break;
    case URGENT: os << "urgent"; break;
    case COMMITTED: os << "committed"; break;
    case BROADCAST: os << "broadcast"; break;
    case VOID_TYPE: os << "void"; break;
    case CLOCK: os << "clock"; break;
    case FRACTION: os << "fraction"; break;
    case INT: os << "int"; break;
    case DOUBLE: os << "double"; break;
    case STRING: os << "string"; break;
    case BOOL: os << "bool"; break;
    case SCALAR: os << "scalar"; break;
    case CHANNEL: os << "channel"; break;
    case INVARIANT: os << "invariant"; break;
    case GUARD: os << "guard"; break;
    case DIFF: os << "diff"; break;
    case CONSTRAINT: os << "constraint"; break;
    case FORMULA: os << "formula"; break;
    case COST: os << "cost"; break;
    case RATE: os << "rate"; break;
    case TYPEDEF: os << "def"; break;
    case PROCESS: os << "process"; break;
    case INSTANCE: os << "instance"; break;
    case LABEL: os << "label"; break;
    case FUNCTION_EXTERNAL: os << "external_function"; break;
    case FUNCTION: os << "function"; break;
    case LOCATION_EXPR:
    case LOCATION: os << "location"; break;
    case BRANCHPOINT: os << "branchpoint"; break;
    // LSC
    case INSTANCE_LINE: os << "instance line"; break;
    case MESSAGE: os << "message"; break;
    case CONDITION: os << "condition"; break;
    case UPDATE: os << "update"; break;
    case LSC_INSTANCE: os << "LSC_instance"; break;
    case PROCESS_VAR: os << "process_var"; break;
    default: os << "type(" + std::to_string(get_kind()) + ")"; break;
    }

    for (uint32_t i = 0; i < size(); i++) {
        os << " ";
        if (!get_label(i).empty())
            os << get_label(i) << ':';
        get(i).print(os);
    }
    return os << ')';
}

std::ostream& type_t::print_declaration(std::ostream& os) const
{
    if (data == nullptr)
        os << "unknown";

    if (!data->expr.empty())
        return os;

    auto kind = std::string{};
    auto range = false;
    auto array = false;
    auto label = false;
    auto typeDef = false;

    switch (get_kind()) {
    case UNKNOWN: kind = "unknown"; break;
    case RANGE: range = true; break;
    case ARRAY: array = true; break;
    case RECORD: kind = "struct"; break;
    case CONSTANT: kind = "const"; break;
    case REF: kind = "ref"; break;
    case URGENT: kind = "urgent"; break;
    case COMMITTED: kind = "committed"; break;
    case BROADCAST: kind = "broadcast"; break;
    case VOID_TYPE: kind = "void"; break;
    case CLOCK: kind = "clock"; break;
    case INT: kind = "int"; break;
    case DOUBLE: kind = "double"; break;
    case STRING: kind = "string"; break;
    case BOOL: kind = "bool"; break;
    case SCALAR: kind = "scalar"; break;
    case CHANNEL: kind = "chan"; break;
    case INVARIANT: kind = "invariant"; break;
    case GUARD: kind = "guard"; break;
    case DIFF: kind = "diff"; break;
    case CONSTRAINT: kind = "constraint"; break;
    case FORMULA: kind = "formula"; break;
    case COST: kind = "cost"; break;
    case RATE: kind = "rate"; break;
    case TYPEDEF:
        kind = "typedef";
        typeDef = true;
        break;
    case PROCESS: kind = "process"; break;
    case INSTANCE: kind = "instance"; break;
    case LABEL: label = true; break;
    case FUNCTION_EXTERNAL: kind = "external_function"; break;
    case FUNCTION: kind = "function"; break;
    default: kind = "type(" + std::to_string(get_kind()) + ")"; break;
    }

    if (range) {
        get(0).print_declaration(os);
        if (get_range().first.get_value() != INT16_MIN || get_range().second.get_value() != INT16_MAX) {
            os << "[";
            get_range().first.print(os) << ",";
            get_range().second.print(os) << "]";
            get(1).print_declaration(os);
        }
    } else if (array) {
        get(0).print_declaration(os) << '[';
        get_array_size().get_range().second.get(0).print(os) << ']';
    } else if (label) {
        os << get_label(0);
    } else if (typeDef) {
        os << kind << " ";
        get(0).print_declaration(os) << ' ' << get_label(0);
    } else {
        os << kind;
        for (uint32_t i = 0; i < size(); i++) {
            os << ' ';
            if (!get_label(i).empty())
                os << get_label(i) << ":";
            get(i).print_declaration(os);
        }
    }
    return os;
}

std::string type_t::str() const
{
    auto os = std::ostringstream{};
    print(os);
    return os.str();
}

std::string type_t::declaration() const
{
    auto os = std::ostringstream{};
    print_declaration(os);
    return os.str();
}

std::ostream& operator<<(std::ostream& os, const type_t& t) { return t.print(os); }
