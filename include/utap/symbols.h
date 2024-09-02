// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2011-2020 Aalborg University.
   Copyright (C) 2002-2011 Uppsala University and Aalborg University.

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

#ifndef UTAP_SYMBOLS_HH
#define UTAP_SYMBOLS_HH

#include "common.h"
#include "position.h"
#include "type.h"

#include <exception>
#include <optional>
#include <cstdint>

namespace UTAP {
class frame_t;
class expression_t;

class NoParentException : public std::exception
{};

/**
   A reference to a symbol.

   Symbols can only be accessed via instances of
   symbol_t. Internally, symbols are reference counted and do not
   need to be deallocated manually. Each symbol has a name (which
   might be NULL) a type and an uninterpreted optional void
   pointer.

   Symbols are members of a frame (see also frame_t). It is
   possible to access the frame of a symbol via the symbol (see
   get_frame()). However, a symbol does not contain a counted
   reference to its frame so you must maintain at least one
   reference to the frame to avoid to be deallocated.

   Notice that it is possible to add the same symbol to several
   frames. In this case, the symbol will only "point back" to the
   first frame it was added to.
*/
class symbol_t
{
private:
    struct symbol_data;
    std::shared_ptr<symbol_data> data{nullptr};  // pImpl pattern

protected:
    friend class frame_t;
    symbol_t(frame_t* frame, type_t type, std::string_view name, position_t position, void* user);

public:
    /// Default constructor
    symbol_t() = default;
    symbol_t(const symbol_t&) = default;
    symbol_t(symbol_t&&) = default;
    symbol_t& operator=(const symbol_t&) = default;
    symbol_t& operator=(symbol_t&&) = default;

    /// Destructor
    ~symbol_t() noexcept;

    /// Equality operator
    bool operator==(const symbol_t&) const;

    /// Inequality operator
    bool operator!=(const symbol_t&) const;

    /// Less-than operator
    bool operator<(const symbol_t&) const;

    /// Get frame this symbol belongs to
    frame_t get_frame() const;  // TODO: consider removing this method (mostly unused)

    /// Returns the type of this symbol.
    const type_t& get_type() const;

    /// Alters the type of this symbol
    void set_type(type_t);

    /// Returns the position of the symbol definition in the original source file
    position_t get_position() const;

    /// Returns the user data of this symbol
    void* get_data();

    /// Return the user data of this symbol
    const void* get_data() const;

    /// Returns the name (identifier) of this symbol
    const std::string& get_name() const;

    /// Alters the name of this symbol
    void set_name(std::string);
};

/**
   A reference to a frame.

   A frame is an ordered collection of symbols (see also
   symbol_t). Frames can only be accessed via an instance of
   frame_t. Internally, frames are reference counted and do not
   need to be deallocated manually.

   A frame can either be a root-frame or a sub-frame. Sub-frames
   have a parent frame; root frames do not. When a symbol name
   cannot be resolved in the current frame, it is resolved
   recursively in the parent frame.

   Frames are constructed using one of the static factory methods
   of frame_t.

   In order to avoid cyclic references no counted reference to the
   parent frame is maintained. Hence, the existence of the parent
   frame must be ensured by other means throughout the lifetime of
   the sub-frame.
*/
class frame_t
{
private:
    struct frame_data;
    std::shared_ptr<frame_data> data{nullptr};  // pImpl pattern

protected:
    friend class symbol_t;
    explicit frame_t(frame_data*);

public:
    using iterator = std::vector<symbol_t>::iterator;
    using const_iterator = std::vector<symbol_t>::const_iterator;
    /// Default constructors and operators due to pImpl
    frame_t() = default;
    frame_t(const frame_t&) = default;
    frame_t(frame_t&& other) noexcept = default;
    frame_t& operator=(const frame_t&) = default;
    frame_t& operator=(frame_t&&) noexcept = default;

    /// Destructor due to pImpl
    ~frame_t() noexcept;

    /// Equality operator
    bool operator==(const frame_t&) const;

    /// Inequality operator
    bool operator!=(const frame_t&) const;

    /// Returns the number of symbols in this frame
    uint32_t get_size() const;

    /// Returns the Nth symbol in this frame.
    symbol_t get_symbol(uint32_t) const;

    /// Checks whether the frame (already) contains the symbol with given name.
    bool contains(std::string_view name) const { return get_index_of(name).has_value(); }

    /// Checks whether the frame (already) contains the symbol with given name.
    bool contains(const symbol_t& symbol) const { return get_index_of(symbol).has_value(); }

    /// Returns the index of the symbol with the given name if it exists.
    std::optional<uint32_t> get_index_of(std::string_view name) const;

    /// Returns the index of a symbol if it exists.
    std::optional<uint32_t> get_index_of(const symbol_t&) const;

    /// Returns the Nth symbol in this frame.
    symbol_t& operator[](uint32_t);

    /// Returns the Nth symbol in this frame.
    const symbol_t& operator[](uint32_t) const;

    /// Iterates over the symbol declarations in the frame
    const_iterator begin() const;
    const_iterator end() const;
    iterator begin();
    iterator end();
    bool empty() const;

    /// Adds a symbol of the given name and type to the frame
    symbol_t add_symbol(std::string_view name, type_t, position_t position, void* user = nullptr);

    /// Add all symbols from the given frame
    void add(symbol_t);

    /// Add all symbols from the given frame
    void add(const frame_t&);

    /// Move all symbols from this to other (leaving this empty).
    void move_to(frame_t& other);

    /// removes the given symbol*/
    void remove(const symbol_t& s);

    /// Resolves a name in this frame or a parent frame.
    bool resolve(std::string_view name, symbol_t& symbol) const;

    /// Returns the parent frame
    frame_t get_parent() const;

    /// Returns true if this frame has a parent
    bool has_parent() const;

    /// Creates and returns a new root-frame.
    static frame_t create();

    /// Creates and returns a new sub-frame.
    static frame_t create(const frame_t& parent);
};
}  // namespace UTAP

std::ostream& operator<<(std::ostream& o, const UTAP::symbol_t& t);
std::ostream& operator<<(std::ostream& o, const UTAP::frame_t& t);

#endif /* UTAP_SYMBOLS_HH */
