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

#include "utap/symbols.h"

#include "utap/expression.h"
#include "utap/range.h"

#include <algorithm>
#include <map>
#include <stdexcept>
#include <vector>
#include <cstdlib>

using std::vector;
using std::map;
using std::ostream;
using std::string;

// The base types

using namespace UTAP;
using namespace Constants;

//////////////////////////////////////////////////////////////////////////

struct symbol_t::symbol_data : public std::enable_shared_from_this<symbol_t::symbol_data>
{
    frame_t::frame_data* frame = nullptr;  // Uncounted pointer to containing frame // TODO: consider removing
    type_t type;                           // The type of the symbol
    void* user = nullptr;                  // User data
    string name;                           // The name of the symbol
    position_t position;                   // the position of the symbol definition in the original document
    symbol_data(frame_t::frame_data* frame, type_t type, void* user, string name, position_t position):
        frame{frame}, type{std::move(type)}, user{user}, name{std::move(name)}, position{position}
    {}
};

symbol_t::symbol_t(frame_t* frame, type_t type, string name, position_t position, void* user)
{
    data = std::make_shared<symbol_data>(frame->data.get(), std::move(type), user, std::move(name), position);
}

/* Destructor */
symbol_t::~symbol_t() noexcept = default;

bool symbol_t::operator==(const symbol_t& symbol) const { return data == symbol.data; }

/* Inequality operator */
bool symbol_t::operator!=(const symbol_t& symbol) const { return data != symbol.data; }

bool symbol_t::operator<(const symbol_t& symbol) const { return data < symbol.data; }

/* Get frame this symbol belongs to */
frame_t symbol_t::get_frame() { return frame_t(data->frame); }

/* Returns the type of this symbol. */
type_t symbol_t::get_type() const { return data->type; }

void symbol_t::set_type(type_t type) { data->type = type; }

position_t symbol_t::get_position() const { return data->position; }

/* Returns the user data of this symbol */
void* symbol_t::get_data() { return data->user; }

/* Returns the user data of this symbol */
const void* symbol_t::get_data() const { return data->user; }

/* Returns the name (identifier) of this symbol */
const string& symbol_t::get_name() const { return data->name; }

void symbol_t::set_name(string name) { data->name = std::move(name); }

std::ostream& operator<<(std::ostream& o, const UTAP::symbol_t& t) { return o << t.get_type() << " " << t.get_name(); }

//////////////////////////////////////////////////////////////////////////

struct frame_t::frame_data : public std::enable_shared_from_this<frame_t::frame_data>
{
    std::shared_ptr<frame_data> parent;  // The parent frame data
    vector<symbol_t> symbols;            // The symbols in the frame
    map<string, int32_t> mapping;        // Mapping from names to indices
    explicit frame_data(std::shared_ptr<frame_data> p): parent{p} {}
    bool has_parent() const { return parent != nullptr; }
};

frame_t::frame_t(frame_data* frame) { data = frame->shared_from_this(); }

/* Destructor */
frame_t::~frame_t() noexcept = default;

/* Equality operator */
bool frame_t::operator==(const frame_t& frame) const { return data == frame.data; }

/* Inequality operator */
bool frame_t::operator!=(const frame_t& frame) const { return data != frame.data; }

/* Returns the number of symbols in this frame */
uint32_t frame_t::get_size() const { return data->symbols.size(); }
bool frame_t::empty() const { return data->symbols.empty(); }

/* Returns the Nth symbol in this frame (counting from 0) */
symbol_t frame_t::get_symbol(uint32_t n) const { return data->symbols[n]; }

/* Returns the Nth symbol in this frame (counting from 0) */
symbol_t& frame_t::operator[](uint32_t n) { return data->symbols[n]; }

/* Returns the Nth symbol in this frame (counting from 0) */
const symbol_t& frame_t::operator[](uint32_t n) const { return data->symbols[n]; }

frame_t::const_iterator frame_t::begin() const { return std::begin(data->symbols); }
frame_t::const_iterator frame_t::end() const { return std::end(data->symbols); }
frame_t::iterator frame_t::begin() { return std::begin(data->symbols); }
frame_t::iterator frame_t::end() { return std::end(data->symbols); }

/* Adds a symbol of the given name and type to the frame */
symbol_t frame_t::add_symbol(const string& name, type_t type, position_t position, void* user)
{
    auto symbol = symbol_t{this, type, name, position, user};
    data->symbols.push_back(symbol);
    if (!name.empty()) {
        data->mapping[symbol.get_name()] = data->symbols.size() - 1;
    }
    return symbol;
}

/** Add symbol. Notice that the symbol will be in two frames at the
    same time, but the symbol will only "point back" to the first
    frame it was added to.
*/
void frame_t::add(symbol_t symbol)
{
    data->symbols.push_back(symbol);
    if (!symbol.get_name().empty()) {
        data->mapping[symbol.get_name()] = data->symbols.size() - 1;
    }
}

/** Add all symbols in the given frame. Notice that the symbols will
    be in two frames at the same time, but the symbol will only "point
    back" to the first frame it was added to.
*/
void frame_t::add(frame_t frame)
{
    for (auto& symbol : frame)
        add(symbol);
}

/** Move all symbols from this to the given frame.
    Notice that the symbols will be updated to point to the given frame,
    while this frame will be emptied and ready for recycling.
*/
void frame_t::move_to(frame_t frame)
{
    for (uint32_t i = 0; i < data->symbols.size(); i++) {
        symbol_t symbol = data->symbols[i];
        frame.add(symbol);
        symbol.data->frame = frame.data.get();
    }
    data->symbols.clear();
    data->mapping.clear();
}

/** removes the given symbol*/
void frame_t::remove(symbol_t s)
{
    vector<symbol_t> symbols = data->symbols;
    data->symbols.clear();
    data->mapping.clear();
    for (uint32_t i = 0; i < symbols.size(); i++) {
        symbol_t symbol = symbols[i];
        if (symbol != s) {
            add(symbol);
            symbol.data->frame = data.get();
        }
    }
}

std::optional<uint32_t> frame_t::get_index_of(const string& name) const
{
    auto res = std::optional<uint32_t>{};
    if (auto it = data->mapping.find(name); it != data->mapping.end())
        res = it->second;
    return res;
}

std::optional<uint32_t> frame_t::get_index_of(const symbol_t& symbol) const
{
    auto res = std::optional<uint32_t>{};
    auto it = std::find(std::begin(data->symbols), std::end(data->symbols), symbol);
    if (it != std::end(data->symbols))
        res = std::distance(std::begin(data->symbols), it);
    return res;
}

/**
   Resolves the name in this frame or the parent frame and
   returns the corresponding symbol.
*/
bool frame_t::resolve(const string& name, symbol_t& symbol) const
{
    auto idx = get_index_of(name);
    if (!idx)
        return (data->has_parent() ? get_parent().resolve(name, symbol) : false);
    symbol = data->symbols[*idx];
    return true;
}

/* Returns the parent frame */
frame_t frame_t::get_parent() const
{
    if (!data->has_parent())
        throw NoParentException();
    return frame_t{data->parent.get()};
}

/* Returns true if this frame has a parent */
bool frame_t::has_parent() const { return data->has_parent(); }

/* Creates and returns a new frame without a parent */
frame_t frame_t::create()
{
    auto data = std::make_shared<frame_data>(nullptr);
    return frame_t{data.get()};
}

/* Creates and returns new frame with the given parent */
frame_t frame_t::create(const frame_t& parent)
{
    auto data = std::make_shared<frame_data>(parent.data);
    return frame_t{data.get()};
}

std::ostream& operator<<(std::ostream& os, const UTAP::frame_t& t)
{
    os << "{";
    auto b = std::begin(t), e = std::end(t);
    if (b != e) {
        os << *b;
        while (++b != e)
            os << ", " << *b;
    }
    return os << "}";
}
