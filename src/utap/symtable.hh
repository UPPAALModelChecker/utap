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

#ifndef UTAP_NSYMTABLE_H
#define UTAP_NSYMTABLE_H

#include <map>
#include <vector>

namespace UTAP
{
    class SymbolTable 
    {
    public:
	static const int ROOT = 0;

	int addSymbol(const char *name, int type, void *data); // -1 if already added
	int addSymbol(const char *name, int type) {
	    return addSymbol(name, type, NULL);
	};
	int resolve(const char *name) const; // -1 if no such name
	int resolveLocal(const char *name, int frame) const; // -1 if not found

	const char* getName(int uid) const;
	void setType(int uid, int type);
	int getType(int uid) const;
	void setData(int uid, void*);
	void *getData(int uid);


	int addFrame();
	int getActiveFrame() const;  
	int getParentFrame() const;
	int getParentFrame(int frameId) const;
	void activateFrame(int uid);

	SymbolTable();
	~SymbolTable();

	int getFrameOf(int uid) {
	    assert(uid >= 0 && uid < (int32_t)index.size());
	    return index[uid];
	}

    protected:

	typedef struct symbol_t
	{
	    int type; // typeid registered in TypeSystem
	    const char *name; // copy of the name
	    /* getType(type)==TypeSystem::LOCATION => Expression
	       getType(type)==TypeSystem::FUNCTION => Statement
	       getType(type)==TypeSystem::TEMPLATE => TransitionList */
	    void *body; // just a pointer, no copy
      
	    symbol_t(const int t, const char *symbol, void *data):
		type(t), name(strdup(symbol)), body(data)
		{};
	    ~symbol_t() 
		{
		    assert (name);
		    free((char*)name);
		}
	};

	typedef struct frame_t
	{
	    const int parent; // -1 for root frame
	    std::map<const int, symbol_t*> nsymbols;
	    frame_t(const int parentFrame): parent(parentFrame) 
		{ };
	    ~frame_t()
		{
		    while (!nsymbols.empty()) {
			symbol_t *s = nsymbols.begin()->second;
			assert(s);
			delete s;
			nsymbols.erase(nsymbols.begin());
		    }
		}
	};

	std::vector<frame_t*> frames;
	std::vector<int> index; // [symbol uid] => frameid, size is uid generator
	int current;
    };

}

#endif
