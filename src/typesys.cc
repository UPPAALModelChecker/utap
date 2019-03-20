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

#include "utap/typesys.hh"
#include "utap/builder.hh"

using namespace UTAP;

using std::pair;
using std::make_pair;
using std::vector;
using std::make_pair;

TypeSystem::TypeSystem()
{
    for (int i = 0; i < NO_PREDEFINED; i++)
	types.push_back(new typeinfo_t(i));
}

TypeSystem::~TypeSystem()
{
    while (!types.empty()) {
	delete types.back();
	types.pop_back();
    }
}

TypeSystem::TypeSystem(const TypeSystem &ts)
{
    for (uint32_t i = 0; i < ts.types.size(); i++) {
	types.push_back(new typeinfo_t(*ts.types[i]));
    }
}

TypeSystem::typeinfo_t::typeinfo_t(const typeinfo_t &t) : type(t.type)
{
    range = t.range;
    subtype = t.subtype;
    if (t.record) {
	record = new vector<pair<char *, type_t> >;
	for (uint32_t i = 0; i < t.record->size(); i++) {
	    pair<char *, type_t> &p = (*t.record)[i];
	    record->push_back(make_pair(strcpy(new char[strlen(p.first) + 1],
					       p.first), p.second));
	}
    }
}

type_t TypeSystem::addInteger(int min, int max)
{
    typeinfo_t* type = new typeinfo_t(INT);
    type->range = make_pair(min, max);
    types.push_back(type);
    return types.size() - 1;
}

type_t TypeSystem::addArray(type_t domain, type_t subtype) 
{
    typeinfo_t* type = new typeinfo_t(ARRAY, domain, subtype);
    types.push_back(type);
    return types.size() - 1;
}

type_t TypeSystem::addRecord(const vector<pair<char*, type_t> >& rec)
{
    vector<pair<char*, type_t> > *record = new vector<pair<char*, type_t> >;
    for (uint32_t i = 0; i < rec.size(); i++) {
	char *name = (rec[i].first ? strdup(rec[i].first) : NULL);
	record->push_back(make_pair(name, rec[i].second));
    }
    typeinfo_t* type = new typeinfo_t(RECORD, record);
    types.push_back(type);
    return types.size() - 1;
}

// Function: domain (parameters as record type) -> range (return type)
type_t TypeSystem::addFunction(type_t domain, type_t range)
{ 
    // check validity of arguments
    if (clearFlags(domain) >= (int32_t)types.size() 
	|| clearFlags(range) >= (int32_t)types.size() 
	|| getClass(domain) != RECORD)
    {
	throw TypeException("Bad types for addFunction(%d, %d)",
			    domain, range);
    }

    typeinfo_t* type = new typeinfo_t(FUNCTION, domain, range);
    types.push_back(type);
    return types.size()-1;
}

type_t TypeSystem::addTemplate(type_t arg)
{
    if (clearFlags(arg) >= (int32_t)types.size() || getClass(arg) != RECORD)
	throw TypeException("Bad type for addTemplate(%d)",arg);

    typeinfo_t* type = new typeinfo_t(TEMPLATE, arg, VOID_TYPE);
    types.push_back(type);
    return types.size() - 1;
}

type_t TypeSystem::addNamedType(type_t id)
{
    typeinfo_t* type = new typeinfo_t(NTYPE, id, VOID_TYPE);
    types.push_back(type);
    return types.size() - 1;
}

type_t TypeSystem::makeReference(type_t type)
{
    return (type | FLAG_REF);
}

type_t TypeSystem::makeConstant(type_t type)
{
    return (type | FLAG_CONST);
}

type_t TypeSystem::makeSideEffectFree(type_t type)
{
    return (type | FLAG_SEFREE);
}

bool TypeSystem::isReference(type_t type) const 
{
    return ((type & FLAG_REF) == FLAG_REF);
}
bool TypeSystem::isConstant(type_t type) const 
{
    return ((type & FLAG_CONST) == FLAG_CONST);
}

bool TypeSystem::isSideEffectFree(type_t type) const 
{
    return ((type & FLAG_SEFREE) == FLAG_SEFREE);
}

type_t TypeSystem::getClass(type_t type) const 
{
    uint32_t id = clearFlags(type);
    if (id < 0 || id >= types.size()) {
	return -1;
    }
    switch (id) {
    case CLOCATION:
    case ULOCATION:
	return LOCATION;
    case UCHANNEL:
    case BCHANNEL:
    case UBCHANNEL:
	return CHANNEL;
    default:
	return types[id]->type;
    }
}

const pair<int,int> &TypeSystem::getIntegerRange(type_t type) const 
{
    uint32_t id = clearFlags(type);
    if (id >= types.size() || types[id]->type != INT)
	throw TypeException("Bad type id: getIntegerRange(%d)", type); 
    return types[id]->range;
}

const vector<pair<char*, type_t> > &TypeSystem::getRecord(type_t type)
{
    uint32_t id = clearFlags(type);
    if (id >= types.size() || types[id]->type != RECORD)
	throw TypeException("Bad type id: getRecord(%d)", type); 
    return *(types[id]->record);
}

type_t TypeSystem::getFirstSubType(type_t type) const
{
    uint32_t id = clearFlags(type);
    if (id >= types.size()) 
	throw TypeException("Bad type id: getFirstSubType(%d)", type);  

    switch (getClass(id)) {
    case FUNCTION: 
    case TEMPLATE: 
    case NTYPE: 
    case ARRAY:
	return types[id]->subtype.first; 
    default:
	return VOID_TYPE;    
    }
}

type_t TypeSystem::getSecondSubType(type_t type) const
{
    uint32_t id = clearFlags(type);
    if (id >= types.size())
	throw TypeException("Bad type id: getSecondSubType(%d)", type);  

    switch(getClass(id)){
    case FUNCTION: 
    case ARRAY:
	return types[id]->subtype.second; 
    default:
	return VOID_TYPE;    
    }
}

