// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2002 Uppsala University and Aalborg University.
   
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

#include <cstdlib>
#include <vector>
#include <map>

#include "utap/symbols.hh"

using std::vector;
using std::map;
using std::pair;
using std::make_pair;
using std::max;
using std::min;

// The base types

using namespace UTAP;

type_t type_t::UNKNOWN = type_t::createBase();
type_t type_t::VOID_TYPE = type_t::createBase();
type_t type_t::CLOCK = type_t::createBase();
type_t type_t::INT = type_t::createBase();
type_t type_t::LOCATION = type_t::createBase();
type_t type_t::CHANNEL = type_t::createBase();
type_t type_t::TEMPLATE = type_t::createBase();
type_t type_t::FUNCTION = type_t::createBase();
type_t type_t::ARRAY = type_t::createBase();
type_t type_t::RECORD = type_t::createBase();
type_t type_t::PROCESS = type_t::createBase();
type_t type_t::NTYPE = type_t::createBase();
type_t type_t::INVARIANT = type_t::createBase();
type_t type_t::GUARD = type_t::createBase();
type_t type_t::DIFF = type_t::createBase();
type_t type_t::CONSTRAINT = type_t::createBase();

//////////////////////////////////////////////////////////////////////////

range_t::range_t()
{

}

range_t::range_t(int l, int u) : lower(l), upper(u)
{

}

range_t::range_t(const pair<int,int> &r) : lower(r.first), upper(r.second)
{

}

bool range_t::operator == (const range_t &r) const
{
    return lower == r.lower && upper == r.upper;
}

bool range_t::operator != (const range_t &r) const
{
    return lower != r.lower || upper != r.upper;
}

range_t range_t::intersect(const range_t &r) const
{
    return range_t(max(lower, r.lower), min(upper, r.upper));
}

range_t range_t::join(const range_t &r) const
{
    return range_t(min(lower, r.lower), max(upper, r.upper));
}

bool range_t::contains(const range_t &r) const
{
    return lower <= r.lower && r.upper <= r.upper;
}

//////////////////////////////////////////////////////////////////////////

struct symbol_t::symbol_data
{
    int32_t count;	// Reference counter
    void *frame;	// Uncounted pointer to containing frame
    type_t type;	// The type of the symbol
    void *user;		// User data
    char *name;		// The name of the symbol
};

symbol_t::symbol_t()
{
    data = NULL;
}

symbol_t::symbol_t(void *frame, type_t &type, const char *name, void *user)
{
    data = new symbol_data;
    data->count = 1;
    data->frame = frame;
    data->user = user;
    data->type = type;
    data->name = (name ? strcpy(new char[strlen(name) + 1], name) : NULL);
}

/* Construct symbol from unique id */
symbol_t::symbol_t(int32_t id)
{
    data = (symbol_data*)id;
    if (data)
	data->count++;
}

/* Copy constructor */
symbol_t::symbol_t(const symbol_t &symbol)
{
    data = symbol.data;
    if (data)
	data->count++;
}

/* Destructor */
symbol_t::~symbol_t()
{
    if (data) {
	data->count--;
	if (data->count == 0) {
	    delete[] data->name;
	    delete data;
	}
    }
}

/* Assignment operator */
const symbol_t &symbol_t::operator = (const symbol_t &symbol)
{
    if (data) {
	data->count--;
	if (data->count == 0) {
	    delete[] data->name;
	    delete data;
	}
    }
    data = symbol.data;
    if (data)
	data->count++;
    return *this;
}

bool symbol_t::operator == (const symbol_t &symbol) const
{
    return data == symbol.data;
}

/* Inequality operator */
bool symbol_t::operator != (const symbol_t &symbol) const
{
    return data != symbol.data;
}

/* Get frame this symbol belongs to */
frame_t symbol_t::getFrame()
{
    return frame_t(data->frame);
}

/* Returns the type of this symbol. */
type_t symbol_t::getType() const
{
    return data->type;
}

void symbol_t::setType(type_t type)
{
    data->type = type;
}

/* Returns the user data of this symbol */
void *symbol_t::getData()
{
    return data->user;
}

/* Returns the name (identifier) of this symbol */
const char *symbol_t::getName() const
{
    return data->name;
}
	
/* Sets the user data of this symbol */
void symbol_t::setData(void *value)
{
    data->user = value;
}

int32_t symbol_t::getId()
{
    return (int32_t)data;
}

//////////////////////////////////////////////////////////////////////////

struct compare_str {
    bool operator()(const char* x, const char* y) const {
        return (strcmp(x,y)<0);
    }
};

struct frame_t::frame_data
{
    int32_t count;			// Reference count
    bool hasParent;			// True if there is a parent
    frame_t parent;			// The parent
    vector<symbol_t> symbols;		// The symbols in the frame
    map<const char *, int32_t, compare_str> mapping; // Mapping from names to indices
};

frame_t::frame_t()
{
    data = NULL;
}

frame_t::frame_t(void *p)
{
    data = (frame_data*)p;
    if (data)
	data->count++;
}

/* Copy constructor */
frame_t::frame_t(const frame_t &frame)
{
    data = frame.data;
    if (data)
	data->count++;
}

/* Destructor */
frame_t::~frame_t()
{
    if (data) {
	data->count--;
	if (data->count == 0)
	    delete data;
    }
}

const frame_t &frame_t::operator = (const frame_t &frame)
{	
    if (data) {
	data->count--;
	if (data->count == 0)
	    delete data;
    }
    data = frame.data;
    if (data)
	data->count++;
    return *this;
}

/* Equality operator */
bool frame_t::operator == (const frame_t &frame) const
{
    return data == frame.data;
}

/* Inequality operator */ 
bool frame_t::operator != (const frame_t &frame) const
{
    return data != frame.data;
}

/* Returns the number of symbols in this frame */
int32_t frame_t::getSize() const
{
    return data->symbols.size();
}

/* Returns the Nth symbol in this frame (counting from 0) */
symbol_t frame_t::getSymbol(int32_t n)
{
    return data->symbols[n];
}

/* Returns the Nth symbol in this frame (counting from 0) */
symbol_t frame_t::operator[](int32_t n)
{
    return data->symbols[n];
}

/* Adds a symbol of the given name and type to the frame */
symbol_t frame_t::addSymbol(const char *name, type_t type, void *user)
{
    symbol_t symbol(data, type, name, user);
    data->symbols.push_back(symbol);
    if (name)
	data->mapping[symbol.getName()] =  data->symbols.size() - 1;
    return symbol;
}

/** Add all symbols in the given frame. Notice that the symbols will
    be in two frames at the same time, but the symbol will only "point
    back" to the first frame it was added to.
*/
void frame_t::add(frame_t frame)
{
    for (int32_t i = 0; i < frame.getSize(); i++) {
	data->symbols.push_back(frame[i]);
	if (frame[i].getName())
	    data->mapping[frame[i].getName()] =  data->symbols.size() - 1;
    }
}

int32_t frame_t::getIndexOf(const char *name)
{
    if (name == NULL)
	return -1;
    map<const char *, int32_t>::iterator i = data->mapping.find(name);
    return (i == data->mapping.end() ? -1 : i->second);
}

/**
   Resolves the name in this frame or the parent frame and
   returns the corresponding symbol. 
*/
bool frame_t::resolve(const char *name, symbol_t &symbol)
{
    int32_t idx = getIndexOf(name);
    if (idx == -1)
	return (data->hasParent ? data->parent.resolve(name, symbol) : false);
    symbol = data->symbols[idx];
    return true;
}

/* Returns the parent frame */
frame_t frame_t::getParent()
{
    if (!data->hasParent)
	throw NoParentException();
    return data->parent;
}

/* Returns true if this frame has a parent */
bool frame_t::hasParent() const
{
    return data->hasParent;
}

/* Creates and returns a new frame without a parent */
frame_t frame_t::createFrame()
{
    frame_data *data = new frame_data;
    data->count = 0;
    data->hasParent = false;
    return frame_t(data);
}

/* Creates and returns new frame with the given parent */
frame_t frame_t::createFrame(const frame_t &parent)
{
    frame_data *data = new frame_data;
    data->count = 0;
    data->hasParent = true;
    data->parent = parent;
    return frame_t(data);  
}

//////////////////////////////////////////////////////////////////////////

struct type_t::type_data
{
    int32_t count;		// Reference count
    uint32_t prefix;		// Prefixes
    type_t base;		// Base type
    type_t sub;			// Sub type
    frame_t frame;		// Frame (fields or parameters)
    pair<int32_t,int32_t> range;// Range of integers

    type_data(const type_t &base, const frame_t &frame,
	      const type_t &sub, const pair<int32_t, int32_t> &range)
	: count(0), prefix(0), base(base), sub(sub), frame(frame), range(range)
	{

	}
};

/**
   Default constructor. This creates the equivalent of a NULL pointer.
*/
type_t::type_t()
{
    data = NULL;
}

/* Construct from pointer. */
type_t::type_t(void *p)
{
    data = (type_data*)p;
    if (data) 
	data->count++;
}

/**
   Construct from id. The id must have been generated by a previous
   call to getId(). The original type object must still be alive, i.e.
   it must be referenced by another type_t instance.
*/
type_t::type_t(int32_t id)
{
    data = (type_data*)id;
    if (data)
	data->count++;
}

/* Copy constructor */
type_t::type_t(const type_t &type)
{
    data = type.data;
    if (data)
	data->count++;
}

/* Destructor */
type_t::~type_t()
{
    if (data) {
	data->count--;
	if (data->count == 0)
	    delete data;
    }
}

/* Assignment operator */
const type_t &type_t::operator = (const type_t &type)
{
    if (data) {
	data->count--;
	if (data->count == 0)
	    delete data;
    }
    data = type.data;
    if (data) 
	data->count++;
    return *this;
}

/* Equality operator */
bool type_t::operator == (const type_t &type) const
{
    return data == type.data;
}

/* Inequality operator */
bool type_t::operator != (const type_t &type) const
{
    return data != type.data;
}

/* Returns the base type of this frame. */
type_t type_t::getBase() const
{
    return data->base;
}

/** Returns the fields of a record type. See also getFrame(). */
frame_t type_t::getRecordFields() const
{
    assert(data->base == RECORD);
    return data->frame;
}

/** Returns the arguments of a function or template type. See also
    getFrame(). 
*/
frame_t type_t::getParameters() const
{
    assert(data->base == FUNCTION || data->base == TEMPLATE);
    return data->frame;
}

/** Polymorphic version of getRecordFields() and getParameters(). The
    frame returned must not be modified (since type objects are supposed
    to be immutable).
*/
frame_t type_t::getFrame() const
{
    assert(data->base == FUNCTION || data->base == TEMPLATE || data->base == RECORD);
    return data->frame;
}

/**
   Returns the sub-type of this type. For functions, this is the
   return value. For arrays, this is type type of the array
   elements. 
*/
type_t type_t::getSub()
{
    assert(data->base == FUNCTION || data->base == ARRAY || data->base == NTYPE);
    return data->sub;
}

/* Returns the size of an array */
int32_t type_t::getArraySize() const
{
    assert(data->base == ARRAY);
    return data->range.first;
}

/* Returns the true if this type has the given prefix */
bool type_t::hasPrefix(prefix::prefix_t prefix) const
{
    return data->prefix & prefix;
}

/**
   If 'set' is true, the prefix is set; otherwise it is cleared.  The
   type itself is not altered, but a new type corresponding to the
   change is returned. 
*/
type_t type_t::setPrefix(bool set, prefix::prefix_t prefix) const
{
    type_data *result = new type_data(*data);
    result->count = 0;
    if (set)
	result->prefix |= prefix;
    else
	result->prefix &= ~prefix;
    return type_t(result);
}

/* Returns the range of an integer type. */
const pair<int32_t,int32_t> &type_t::getRange() const
{
    assert(data->base == INT);
    return data->range;
}

/** Get unique ID for this type. This ID is only unique as long as the
    underlying type object is referenced. The ID can be used to
    construct a new reference to the type object.
*/
int32_t type_t::getId() const
{
    return (int32_t)data;
}

/* Creates and returns a new integer type with the given range */
type_t type_t::createInteger(int32_t lower, int32_t upper)
{
    return type_t(new type_data(INT, frame_t(), type_t(),
				make_pair(lower, upper)));
}
	
/* Creates and returns a new record type */
type_t type_t::createRecord(frame_t frame)
{
    return type_t(new type_data(RECORD, frame, type_t(), make_pair(0, 0)));
}

/* Creates and returns a new function type */
type_t type_t::createFunction(frame_t arguments, type_t ret)
{
    return type_t(new type_data(FUNCTION, arguments, ret, make_pair(0, 0)));
}

/* Creates and returns a new array type */
type_t type_t::createArray(int32_t size, type_t type)
{
    return type_t(new type_data(ARRAY, frame_t(), type, make_pair(size, 0)));
}

/* Creates and returns a new named type */
type_t type_t::createTypeName(type_t type)
{
    return type_t(new type_data(NTYPE, frame_t(), type, make_pair(0, 0)));
}

type_t type_t::createTemplate(frame_t frame)
{
    return type_t(new type_data(TEMPLATE, frame, type_t(), make_pair(0,0)));
}

type_t type_t::createProcess(frame_t frame)
{
    return type_t(new type_data(PROCESS, frame, type_t(), make_pair(0,0)));
}

type_t type_t::createBase()
{
    type_data *data = new type_data(type_t(), frame_t(), type_t(), make_pair(0,0));
    data->base = type_t(data);
    return type_t(data);
}
