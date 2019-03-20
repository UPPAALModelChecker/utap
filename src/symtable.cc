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

#include "utap/builder.hh"
#include "utap/symtable.hh"

using namespace UTAP;

using std::map;
using std::vector;

SymbolTable::SymbolTable()
{ 
    frames.push_back(new frame_t(-1));
    current = ROOT;
}

SymbolTable::~SymbolTable()
{
    while (!frames.empty()) {
	delete frames.back();
	frames.pop_back();
    }
}

int SymbolTable::addSymbol(const char *name, int type, void *data) 
{  
    if (resolveLocal(name, current)==-1) { // localy unique name
	index.push_back(current); // remember that new symbol is in current frame
	frames[current]->nsymbols[index.size()-1] = new symbol_t(type, name, data);
	return index.size()-1;
    } else {
	throw TypeException("symbol '%s' is already declared", name);
    }
} 


int SymbolTable::resolve(const char *name) const 
{
    int frame = current;
    int id = -1;
    while (frame != -1) {
	id = resolveLocal(name, frame);
	if (id != -1) break;
	else frame = frames[frame]->parent;
    }
    /*  if (id == -1)
	throw TypeException("Symbol not found: resolve(%s)", name);
	else 
    */
    return id;
}

const char* SymbolTable::getName(int uid) const 
{
    if (static_cast<int>(index.size())>uid) {
	symbol_t *s = frames[index[uid]]->nsymbols.find(uid)->second;
	assert(s);
	return s->name;
    } else 
	return NULL;
    //  throw TypeException("Bad symbol id for getName(%d)", uid); 
}

void SymbolTable::setType(int uid, int type)
{
    if (static_cast<int>(index.size())>uid) {
	symbol_t *s = frames[index[uid]]->nsymbols.find(uid)->second;
	assert(s);
	s->type = type;
    } else
	throw TypeException("Bad symbol id for setType(%d, %d)", uid, type);
}

int SymbolTable::getType(int uid) const
{
    if (static_cast<int>(index.size())>uid) {
	symbol_t *s = frames[index[uid]]->nsymbols.find(uid)->second;
	assert(s);
	return s->type;
    } else
	return -1;
    //    throw TypeException("Bad symbol id for getType(%d)", uid);
}

void SymbolTable::setData(int uid, void* data)
{
    if (static_cast<int>(index.size())>uid) {
	symbol_t *s = frames[index[uid]]->nsymbols.find(uid)->second;
	assert(s);
	s->body = data;
    } else
	throw TypeException("Bad symbol id for setData(%d, %x)", uid, data);
}


void *SymbolTable::getData(int uid)
{
    if (static_cast<int>(index.size())>uid) {
	symbol_t *s = frames[index[uid]]->nsymbols.find(uid)->second;
	assert(s);
	return s->body;
    } else
	return NULL;
    //    throw TypeException("Bad symbol id for getData(%d)", uid);
}

int SymbolTable::addFrame() 
{
    frames.push_back(new frame_t(current));
    return frames.size()-1;
}

int SymbolTable::getActiveFrame() const 
{
    return current;
}

void SymbolTable::activateFrame(int uid) 
{
    assert(uid>=0 && uid<static_cast<int>(frames.size()));
    current = uid;
}

int SymbolTable::getParentFrame() const 
{
    return frames[current]->parent;
}

int SymbolTable::getParentFrame(int frameId) const 
{
    assert(frameId<frames.size() && frameId>=0);
    return frames[frameId]->parent;
}

int SymbolTable::resolveLocal(const char *name, int frame) const
{
    assert(frame>=0);
    map<int, symbol_t*>::iterator s = frames[frame]->nsymbols.begin(),
	f = frames[frame]->nsymbols.end();    
    while (s != f) {
	assert (s->second);
	if (strcmp(s->second->name, name) == 0) 
	    return s->first;
	s++;
    }
    return -1;
}

#ifdef SYMTABLE_TEST

/*****************************************************************************
 * SymbolTable & TypeSystem class test procedures
 */

#include <stdio.h>

int main()
{
    try {
	/* initialization */
	printf("Initializing...");
	TypeSystem types;
	SymbolTable st;
    
	int tbi = types.addInteger(5,10); // type of bounded int
	int bi = st.addSymbol("bi", tbi, NULL); // bounded int variable
    
	int size = types.addInteger(0, 15); // type of bounded int for array size
    
	int tbia = types.addArray(tbi, size); //type of bounded integer array
	int bia = st.addSymbol("bia", tbia, NULL); // bounded int array variable
    
	vector<pair<const char*, int> > rrec;
	rrec.push_back(make_pair(strdup("i"), tbi));
	rrec.push_back(make_pair(strdup("ia"), tbia));
	int trec = types.addRecord(rrec); // type of record (tbi,tbia)
	int rec = st.addSymbol("rec", trec, NULL); // record variable
    
	int tfunc = types.addFunction(trec,tbi); // type of function
	int func = st.addSymbol("func", tfunc, &func);
    
	int ttemp = types.addTemplate(trec); // type of template
	int temp = st.addSymbol("temp", ttemp, &temp);
    
	int tnrec = types.addNamedType(trec); // type of ntype to record(tbi,tbia)
	int nrec = st.addSymbol("nrec", tnrec, NULL); // named type variable
    
	int loc = st.addSymbol("loc", TypeSystem::CLOCATION, &loc);
    
	/* POSITIVE TESTS: queries and checks according to specification */
    
	/* TypeSystem tests */
	printf("\nTypeSystem TESTS:\n");
	printf("getType method:");
	if (types.getType(TypeSystem::VOID) == TypeSystem::VOID && 
	    types.getType(TypeSystem::CLOCK) == TypeSystem::CLOCK && 
	    types.getType(TypeSystem::INT) == TypeSystem::INT && 
	    types.getType(TypeSystem::LOCATION) == TypeSystem::LOCATION && 
	    types.getType(TypeSystem::CHANNEL) == TypeSystem::CHANNEL && 
	    types.getType(TypeSystem::TEMPLATE) == TypeSystem::TEMPLATE && 
	    types.getType(TypeSystem::FUNCTION) == TypeSystem::FUNCTION && 
	    types.getType(TypeSystem::ARRAY) == TypeSystem::ARRAY && 
	    types.getType(TypeSystem::RECORD) == TypeSystem::RECORD)
	    printf(" OK");
	else printf(" Fail\n");
	if (types.getType(TypeSystem::CLOCATION) == TypeSystem::LOCATION && 
	    types.getType(TypeSystem::ULOCATION) == TypeSystem::LOCATION)
	    printf(" OK");
	else printf(" Fail");
	if (types.getType(TypeSystem::UCHANNEL) == TypeSystem::CHANNEL && 
	    types.getType(TypeSystem::BCHANNEL) == TypeSystem::CHANNEL &&
	    types.getType(TypeSystem::UBCHANNEL) == TypeSystem::CHANNEL)
	    printf(" OK");
	else printf(" Fail");
	if (types.getType(tbi) == TypeSystem::INT &&
	    types.getType(tbia) == TypeSystem::ARRAY &&
	    types.getType(trec) == TypeSystem::RECORD &&
	    types.getType(tfunc) == TypeSystem::FUNCTION &&
	    types.getType(ttemp) == TypeSystem::TEMPLATE &&
	    types.getType(tnrec) == TypeSystem::NTYPE
	    )
	    printf(" OK\n");
	else printf(" Fail\n");
    
	printf("getIntegerRange method:");
	if (types.getIntegerRange(tbi).first == 5 &&
	    types.getIntegerRange(tbi).second == 10) 
	    printf(" OK\n");
	else printf(" Fail\n");
    
	printf("getRecord method:");
	if (types.getRecord(trec).size() == 2 &&
	    strcmp(types.getRecord(trec)[0].first, "i") == 0 &&
	    types.getRecord(trec)[0].second == tbi &&
	    strcmp(types.getRecord(trec)[1].first, "ia") == 0 &&
	    types.getRecord(trec)[1].second == tbia)
	    printf(" OK\n");
	else printf(" Fail\n");
    
	printf("getFirstSubType method:");
	if (types.getFirstSubType(tfunc) == trec &&
	    types.getFirstSubType(ttemp) == trec &&
	    types.getFirstSubType(tbia) == TypeSystem::INT &&
	    types.getFirstSubType(tnrec) == trec
	    ) 
	    printf(" OK\n");
	else printf(" Fail\n");
    
	printf("getSecondSubType method:");
	if (types.getSecondSubType(tfunc) == tbi &&
	    types.getSecondSubType(ttemp) == TypeSystem::VOID &&
	    types.getSecondSubType(tbia) == tbi &&
	    types.getSecondSubType(tnrec) == TypeSystem::VOID
	    ) 
	    printf(" OK\n");
	else printf(" Fail\n");
    
	printf("Reference and Const methods:");
	if (types.isReference(tbi) == false &&
	    types.isReference(types.makeReference(tbi)) == true &&
	    types.isConst(tbi) == false &&
	    types.isConst(types.makeConst(tbi)) == true &&
	    types.isReference(types.makeConst(tbi)) == false &&
	    types.isReference(types.makeConst(types.makeReference(tbi))) == true &&
	    types.isConst(types.makeReference(tbi)) == false &&
	    types.isConst(types.makeReference(types.makeConst(tbi))) == true
	    )
	    printf(" OK");
	else printf(" Fail");
    
	if (types.getType(types.makeConst(tbi)) == types.getType(tbi) &&
	    types.getType(types.makeReference(tbi)) == types.getType(tbi) &&
	    types.getType(types.makeConst(types.makeReference(tbi))) 
	    == types.getType(tbi))  
	    printf(" OK");
	else printf(" Fail");

	if (types.getType(types.clearReference(tbi)) == types.getType(tbi) &&
	    types.getType(types.clearReference(types.makeReference(tbi))) 
	    == types.getType(tbi) &&
	    types.getType(types.clearReference(types.makeConst(tbi))) 
	    == types.getType(tbi) &&
	    types.getType(types.clearReference(types.makeReference(types.makeConst(tbi)))) 
	    == types.getType(tbi))  
	    printf(" OK");
	else printf(" Fail");

    
	if (types.getIntegerRange(types.makeConst(tbi))
	    == types.getIntegerRange(tbi) &&
	    types.getIntegerRange(types.makeReference(tbi)) 
	    == types.getIntegerRange(tbi) &&
	    types.getIntegerRange(types.makeConst(types.makeReference(tbi))) 
	    == types.getIntegerRange(tbi))  
	    printf(" OK");
	else printf(" Fail");
    
	if (types.getRecord(types.makeConst(trec))
	    == types.getRecord(trec) &&
	    types.getRecord(types.makeReference(trec)) 
	    == types.getRecord(trec) &&
	    types.getRecord(types.makeConst(types.makeReference(trec))) 
	    == types.getRecord(trec))
	    printf(" OK");
	else printf(" Fail");
    
	if (types.getFirstSubType(types.makeConst(tfunc))
	    == types.getFirstSubType(tfunc) &&
	    types.getFirstSubType(types.makeReference(tfunc)) 
	    == types.getFirstSubType(tfunc) &&
	    types.getFirstSubType(types.makeConst(types.makeReference(tfunc))) 
	    == types.getFirstSubType(tfunc))
	    printf(" OK");
	else printf(" Fail");
    
	if (types.getSecondSubType(types.makeConst(tfunc))
	    == types.getSecondSubType(tfunc) &&
	    types.getSecondSubType(types.makeReference(tfunc)) 
	    == types.getSecondSubType(tfunc) &&
	    types.getSecondSubType(types.makeConst(types.makeReference(tfunc))) 
	    == types.getSecondSubType(tfunc))
	    printf(" OK\n");
	else printf(" Fail\n");  
    
	/* SymbolTable tests */
	printf("\nSymbolTable TESTS:\n");
    
	printf("getName method:");
	if (strcmp("bi", st.getName(bi)) == 0 &&
	    strcmp("bia", st.getName(bia)) == 0 &&
	    strcmp("rec", st.getName(rec)) == 0 &&
	    strcmp("func", st.getName(func)) == 0 &&
	    strcmp("temp", st.getName(temp)) == 0 &&
	    strcmp("nrec", st.getName(nrec)) == 0 &&
	    strcmp("loc", st.getName(loc)) == 0)
	    printf(" OK\n");
	else printf(" Fail\n");  
    
	printf("resolve method:");
	if (st.resolve("bi") == bi &&
	    st.resolve("bia") == bia &&
	    st.resolve("rec") == rec &&
	    st.resolve("func") == func &&
	    st.resolve("temp") == temp &&
	    st.resolve("nrec") == nrec &&
	    st.resolve("loc") == loc)
	    printf(" OK\n");
	else printf(" Fail\n");  

	printf("getType method:");
	if (st.getType(bi) == tbi &&
	    st.getType(bia) == tbia &&
	    st.getType(rec) == trec &&
	    st.getType(func) == tfunc &&
	    st.getType(temp) == ttemp &&
	    st.getType(nrec) == tnrec &&
	    st.getType(loc) == TypeSystem::CLOCATION)
	    printf(" OK\n");
	else printf(" Fail\n");  
    
	printf("getData method:");
	if (st.getData(bi) == NULL &&
	    st.getData(bia) == NULL &&
	    st.getData(rec) ==  NULL &&
	    st.getData(func) == &func &&
	    st.getData(temp) == &temp &&
	    st.getData(nrec) == NULL &&
	    st.getData(loc) == &loc)
	    printf(" OK\n");
	else printf(" Fail\n");  
    
	printf("Repeat SymbolTable tests within new frame:\n");
    
	int frame = st.addFrame();
	st.activateFrame(frame);
	int fbi = st.addSymbol("fbi", tbi, NULL);
	int fbia = st.addSymbol("fbia", tbia, NULL);
    
	printf("getName method:");
	if (strcmp("bi", st.getName(bi)) == 0 &&
	    strcmp("bia", st.getName(bia)) == 0 &&
	    strcmp("rec", st.getName(rec)) == 0 &&
	    strcmp("func", st.getName(func)) == 0 &&
	    strcmp("temp", st.getName(temp)) == 0 &&
	    strcmp("nrec", st.getName(nrec)) == 0 &&
	    strcmp("loc", st.getName(loc)) == 0 &&
	    strcmp("fbi", st.getName(fbi)) == 0)
	    printf(" OK\n");
	else printf(" Fail\n");  
    
	printf("getType method:");
	if (st.getType(bi) == tbi &&
	    st.getType(bia) == tbia &&
	    st.getType(rec) == trec &&
	    st.getType(func) == tfunc &&
	    st.getType(temp) == ttemp &&
	    st.getType(nrec) == tnrec &&
	    st.getType(loc) == TypeSystem::CLOCATION &&
	    st.getType(fbi) == tbi)
	    printf(" OK\n");
	else printf(" Fail\n");  
    
	printf("getData method:");
	if (st.getData(bi) == NULL &&
	    st.getData(bia) == NULL &&
	    st.getData(rec) ==  NULL &&
	    st.getData(func) == &func &&
	    st.getData(temp) == &temp &&
	    st.getData(nrec) == NULL &&
	    st.getData(loc) == &loc &&
	    st.getData(fbi) == NULL)
	    printf(" OK\n");
	else printf(" Fail\n");  

	printf("resolve method:");
	if (st.resolve("bi") == bi &&
	    st.resolve("bia") == bia &&
	    st.resolve("rec") == rec &&
	    st.resolve("func") == func &&
	    st.resolve("temp") == temp &&
	    st.resolve("nrec") == nrec &&
	    st.resolve("loc") == loc &&
	    st.resolve("fbi") == fbi)
	    printf(" OK\n");
	else printf(" Fail\n");  
    
	printf("Repeat tests within root frame:\n");
    
	st.activateFrame(SymbolTable::ROOT);
	printf("resolve method:");
	if (st.resolve("bi") == bi &&
	    st.resolve("bia") == bia &&
	    st.resolve("rec") == rec &&
	    st.resolve("func") == func &&
	    st.resolve("temp") == temp &&
	    st.resolve("nrec") == nrec &&
	    st.resolve("loc") == loc &&
	    st.resolve("fbi") == -1)
	    printf(" OK\n");
	else printf(" Fail\n");  
    
	printf("getName method:");
	if (strcmp("bi", st.getName(bi)) == 0 &&
	    strcmp("bia", st.getName(bia)) == 0 &&
	    strcmp("rec", st.getName(rec)) == 0 &&
	    strcmp("func", st.getName(func)) == 0 &&
	    strcmp("temp", st.getName(temp)) == 0 &&
	    strcmp("nrec", st.getName(nrec)) == 0 &&
	    strcmp("loc", st.getName(loc)) == 0 &&
	    strcmp("fbi", st.getName(fbi)) == 0)
	    printf(" OK\n");
	else printf(" Fail\n");  
    
	printf("getType method:");
	if (st.getType(bi) == tbi &&
	    st.getType(bia) == tbia &&
	    st.getType(rec) == trec &&
	    st.getType(func) == tfunc &&
	    st.getType(temp) == ttemp &&
	    st.getType(nrec) == tnrec &&
	    st.getType(loc) == TypeSystem::CLOCATION &&
	    st.getType(fbi) == tbi)
	    printf(" OK\n");
	else printf(" Fail\n");  
    
	printf("getData method:");
	if (st.getData(bi) == NULL &&
	    st.getData(bia) == NULL &&
	    st.getData(rec) ==  NULL &&
	    st.getData(func) == &func &&
	    st.getData(temp) == &temp &&
	    st.getData(nrec) == NULL &&
	    st.getData(loc) == &loc &&
	    st.getData(fbi) == NULL)
	    printf(" OK\n");
	else printf(" Fail\n");
	printf("The end of tests.\n");
    } catch(TypeException te) {
	printf("\nTypeException caught: %s\n", te.what());
    }
    return 0;
}

#endif
