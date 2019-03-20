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
	SymbolTable(const SymbolTable &);
	~SymbolTable();

	int getFrameOf(int uid) const;

    protected:

	struct ltstr
	{
	    bool operator()(const char* s1, const char* s2) const {
		return strcmp(s1, s2) < 0;
	    }
	};

	typedef struct symbol_t
	{
	    int32_t type; // typeid registered in TypeSystem
	    char *name; // copy of the name
	    int32_t frame;
	    void *user_data; 
      
	    symbol_t(int type, int frame, const char *symbol, void *user_data);
	    symbol_t(const symbol_t &);
	    ~symbol_t();
	};

	typedef struct frame_t
	{
	    const int parent; // -1 for root frame
	    std::map<const char *, int, ltstr> symbols;
	    frame_t(const int parentFrame) : parent(parentFrame) { }
	};

	std::vector<symbol_t *> symbols;	
	std::vector<frame_t*> frames;
	int current;

	bool validUID(int uid) const {
	    return (0 <= uid && uid < static_cast<int>(symbols.size()));
	}
    };

}

#endif
