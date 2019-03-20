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

#include "libxml/parser.h"
#include "libxml/parserInternals.h"
#include "libparser.hh"

#include <stdarg.h>
#include <ctype.h>

#include <vector>
#include <map>
#include <sstream>

using namespace UTAP;

using std::ostringstream;
using std::make_pair;
using std::map;
using std::vector;
using std::pair;

/**
 * Enumeration type for tags. We use gperf to generate a perfect hash
 * function to map tag strings to one of these tags.
 */

enum tag_t
{
    TAG_NTA, TAG_IMPORTS, TAG_DECLARATION, TAG_TEMPLATE, TAG_INSTANTIATION,
    TAG_SYSTEM, TAG_NAME, TAG_PARAMETER, TAG_LOCATION, TAG_INIT,
    TAG_TRANSITION, TAG_URGENT, TAG_COMMITTED, TAG_SOURCE, TAG_TARGET,
    TAG_LABEL, TAG_NAIL
};

#include "tags.cc"

/**
 * SAX specific type for strings. 
 * xmlChar is treated as char, as written in documentation.
 * Please review the code when multibyte encodings are introduced!
 */
#define CHAR xmlChar

/**
 * We enumerate all possible states of state machine that listens to
 * SAX.
 */
typedef enum 
{
    ERR, // unrecoverable error state (something is realy wrong here)
    UNKNOWN, // state for tracking the unknown tags which are allowed by DTD
    INITIAL, // the initial state before reading the document
    NTA, IMPORTS, DECLARATION, TEMPLATE, INSTANTIATION, SYSTEM, 
    NAME, PARAMETER, LOCATION, INIT, TRANSITION,
    LABEL, URGENT, COMMITTED, SOURCE, TARGET, NAIL
} state_t;

/**
 * Returns the source appended to dest keeping track of allocated
 * memory.
 *
 * dest - the destination string, a new page will be allocated if NULL
 * dlen - memory of bytes allocated for dest
 * source - the source string, not necessary ended with '\0'
 * slen - the byte number to be appended from source.
 * returns the dest if there were enough memory,
 *         a new allocated string if not enough memory (the old is
 *         deleted!)
 */
static char* append(
    char *dest, int32_t& dlen, const CHAR *source, int32_t slen) 
{
    char *res = NULL;
    int32_t len = dest ? strlen(dest) : 0;

    if (dest) {
	if (len + slen + 1 > dlen) {
	    while (len + slen + 1 > dlen) dlen *= 2;
	    res = new char[dlen];
	    res = strncpy(res, dest, dlen);
	    delete [] dest;
	} else {
	    res = dest;
	}
	res = strncat(res, (const char*)source, slen);
    } else {
	dlen = 1024;
	while (slen + 1 > dlen) dlen *= 2;
	res = new char[dlen];
	strncpy(res, (const char*)source, slen);
	res[slen] = 0;
    }
    return res;
}

/**
 * returns TRUE if string is NULL, zero length or contains only white
 * spaces otherwise FALSE
 */
static bool isempty(const char *p)
{
    if (p) {
	while (*p) {
	    if (!isspace(*p))
		return false;
	    p++;
	}
    }
    return true;
}

static bool isAlpha(char c)
{
    return isalpha(c) || c == '_';
}

static bool isIdChr(char c)
{
    return isalnum(c) || c == '_' || c == '$' || c == '#';
}

/**
 * Extracts the alpha-numerical symbol used for variable/type
 * identifiers.  Identifier starts with alpha and further might
 * contain digits, white spaces are ignored.
 *
 * Throws a TypeException is identifier is invalid or a newly
 * allocated string to be destroyed with delete [].
 */
static char* symbol(const char *str)
{
    if (str == NULL)
	throw TypeException("Identifier expected");
    while (isspace(*str)) str++;
    if (*str == 0)
	throw TypeException("Identifier expected");
    if (!isAlpha(*str))
	throw TypeException("Invalid identifier");
    const char *end = str;
    while (isIdChr(*end)) end++;
    const char *p = end;
    while (isspace(*p)) p++;
    if (*p)
	throw TypeException("Invalid identifier");
    int32_t len = end - str;
    char *res = strncpy(new char[len + 1], str, len);
    res[len] = 0;
    return res;    
}

/**
 * Retrieves an attribute value from list of attributes given the name
 * of attribute.
 *
 * attrs - the list of strings terminated with NULL, even members are
 * attribute names, odd members are attribute values.  name - the name
 * of attribute
 *
 * Returns NULL if attribute not found, or the value of the attribute
 * (not a copy of the string!).
 */
static const char* retrieve(const char **attrs, const char *name)
{
    if (attrs)
	for (int i = 0; attrs[i]; i += 2)
	    if (strcmp(attrs[i], name) == 0) 
		return attrs[i+1];
    return NULL;
}

/**
 * Copies the string into a newly allocated memory area. The new
 * string is allocated with new[].
 */
static char *mystrdup(const char *str)
{
    return strcpy(new char[strlen(str) + 1], str);
}

/**
 * Comparator structure for map<char*,char*> of locations mapping id
 * -> name
 */
struct compare_str {
    bool operator()(const char* x, const char* y) const {
	return (strcmp(x,y)<0);
    }
};

/**
 * The map of locations for quick lookup id -> name
 */
typedef map<char*,char*,compare_str> locationmap_t;

/**
 * We enumerate all possible label kinds to get rid of strings and
 * save the memory
 */
typedef enum {
    L_NONE, L_INV, L_GUARD, L_SYNC, L_ASSIGN
} labelkind_t;

/**
 * We need many additional things to save temporary into the parsing
 * state.  The ParserState is the only connection to SAX (no static
 * variables).  Only errormsg is static buffer used to pass error
 * message descriptions.
 */
class ParserState : public XPath
{
public:
    int32_t result; // the resulting (object) of parsing
    state_t state; // the current state (tag) of parsing
    vector<pair<state_t, tag_t> > history; // the route from current state to root
    vector<vector<state_t> > siblings; // tracks the order and amount of siblings

    int32_t unknown; // the unknown tag level count
    state_t errorpos; // erronious tag if state = ERR
    char *errormsg; // error message if state = ERR
    ErrorHandler *errorHandler;

    ParserBuilder *parser;
    bool newxta;  // tells whether to use the new grammar insterad of old

    char *body; // holds tag contents
    int32_t len;    // the body length

    char* invariant; // holds the content of invariant
    int32_t ilen;        // the invariant length

    char *tname; // the name tag (inside template) - destroy with delete []
    char *lname; // the name tag (inside location) - destroy with delete []
    const char *id;    // current location id
    locationmap_t locations;  // map<id,name> - destroy both id and name with delete []
    labelkind_t labelkind;    // the last label kind until the end of tag
    bool urgent, committed;   // true if location is urgent/committed
    bool guard, sync, assign; // whether there already was an expression for guard,...
  
    int32_t parameter_count; // holds the count of template parameters parsed

    const char *sourceRef; // source idref inside transition
    const char *targetRef; // target idref inside transition

    int32_t lasterror;

    ParserState(ParserBuilder *, ErrorHandler *, bool newxta_);
    virtual ~ParserState();    

    char *get() const;

    char *getName();
protected:
    // counts current state appearances in siblings:
    int32_t count_states(const vector<state_t> &, const state_t) const; 
};

ParserState::ParserState(
    ParserBuilder *pb, ErrorHandler *handler, bool newxta_)
    : errorHandler(handler), parser(pb), newxta(newxta_), lasterror(0)
{
    assert(parser);
    errormsg = NULL;
    tname = lname = NULL;
    errorHandler->setCurrentPath(this);
    labelkind = L_NONE;
    id = NULL;
    sourceRef = targetRef = NULL;
    guard = sync = assign = false;

    // Initialize invariant buffer
    ilen = 1024;
    invariant = new char[ilen];
    invariant[0] = 0;

    // Initialise body buffer
    len = 1024;
    body = new char[len];
    body[0] = 0;    
}

ParserState::~ParserState()
{
    delete [] body;
    delete [] invariant;
    delete [] tname;
    delete [] errormsg;

    locationmap_t::iterator it;
    for (it = locations.begin(); it!=locations.end(); ++it) {
	delete [] it->first;
	delete [] it->second;
    }
}

int32_t ParserState::count_states(const vector<state_t> &states, const state_t state) const
{
    int32_t res = 0;
    for (vector<state_t>::const_iterator it = states.begin(); it != states.end(); it++)
	if (*it == state) res++;
    return res;
}

char *ParserState::getName()
{
    try {
	char *id = symbol(body);
	if (!isKeyword(id, SYNTAX_OLD | SYNTAX_PROPERTY))
	    return id;
	delete[] id;
	throw TypeException("Keywords are not allowed here");
    } catch (TypeException &te) {
	int line = 1, col = 1;
	if (body) {
	    char *c = body;
	    while (*c) {
		if (*c == '\n') {
		    line++;
		    col = 1;
		} else {
		    col++;
		}
		c++;
	    }
	}
	errorHandler->setCurrentPosition(1, 1, line, col);
	errorHandler->handleError(te.what());
    }
    return NULL;
}

char *ParserState::get() const
{
    ostringstream path;
    vector<vector<state_t> >::const_iterator sit = siblings.begin();
    vector<pair<state_t, tag_t> >::const_iterator hit;
    for (hit=history.begin(); hit!=history.end(); hit++, sit++)
	switch (hit->second) {
	case TAG_NTA:           path << "/nta"; break; 
	case TAG_IMPORTS:       path << "/imports"; break;
	case TAG_DECLARATION:   path << "/declaration"; break;
	case TAG_TEMPLATE:      path << "/template[" <<
				(count_states(*sit, TEMPLATE)+1) << "]"; break;
	case TAG_INSTANTIATION: path << "/instantiation"; break;
	case TAG_SYSTEM:        path << "/system"; break;
	case TAG_NAME:          path << "/name"; break;
	case TAG_PARAMETER:     path << "/parameter"; break;
	case TAG_LOCATION:      path << "/location[" << 
				(count_states(*sit, LOCATION)+1) << "]"; break;
	case TAG_INIT:          path << "/init"; break;
	case TAG_TRANSITION:    path << "/transition[" <<
				(count_states(*sit, TRANSITION)+1) << "]"; break;
	case TAG_LABEL:         path << "/label[" <<
				(count_states(*sit, LABEL)+1) << "]"; break;
	case TAG_URGENT:        path << "/urgent"; break;
	case TAG_COMMITTED:     path << "/committed"; break;
	case TAG_SOURCE:        path << "/source"; break;
	case TAG_TARGET:        path << "/target"; break;
	case TAG_NAIL:          path << "/nail[" <<
				(count_states(*sit, NAIL)+1) << "]"; break;
	default: path << "/???"; break;
	}
    path << '\0'; // avoids garbage in the stream

    const char *s = path.str().c_str();
    return strcpy(new char[strlen(s) + 1], s);
}

/**
 * SAX calls before reading the document.
 * Used to initialize state before actual parse.
 */
static void NTA_startDocument(void *user_data)
{
    ParserState* s = (ParserState*) user_data;
    s->state = INITIAL;
    s->history.clear();
    s->unknown = 0;
    s->errorpos = INITIAL;
    s->siblings.push_back(vector<state_t>());
}

/**
 * Final checks just before parsing quits.
 */
static void NTA_endDocument(void *user_data)
{    
    ParserState* s = (ParserState*) user_data;
    s->siblings.pop_back();
    if (s->state != INITIAL) s->state = ERR;
    try { s->parser->done(); } 
    catch(TypeException &te) {
	s->errorHandler->handleError(te.what());
    }
}

/**
 * SAX passes tag content here, the content is broken by inner tags
 * and XML entities
 */
static void NTA_characters(void *user_data, const CHAR *ch, int32_t len)
{
    ParserState* s = (ParserState*) user_data;
    switch (s->state) {
    case DECLARATION:
    case INSTANTIATION:
    case SYSTEM:
    case PARAMETER:
    case NAME:
    case LABEL:
	s->body = append(s->body, s->len, ch, len);
	break;
    case ERR:
	printf("ERROR!\n");

    case NTA:
    case TEMPLATE:
    case LOCATION:
    case TRANSITION:
	break;
    default:
	break;
    }
}

static char errormsg[256];

static bool checkSiblings(ParserState *s, bool cond)
{
    if (!cond) {
	s->errorpos = s->state;
	s->state = ERR;
	s->errormsg = mystrdup("sibling ordering or quantity incorrect"); 
    }
    return cond;
}

/**
 * SAX notifies when the tag start is found (e.g. input:<tag> => n="tag")
 */
static void NTA_startElement(void *user_data, const CHAR *n, const CHAR **attrs)
{
    ParserState* s = (ParserState*) user_data;
    const Tag *name = Tags::in_word_set((const char *)n,
				       strlen((const char *)n));
    if (name == NULL) {
	s->errorpos = s->state;
	s->state = ERR;
	sprintf(errormsg, "unknown tag %s", (const char *)n);
	s->errormsg = mystrdup(errormsg);
	return;
    }
	
    s->history.push_back(make_pair(s->state, name->tag));

    switch (s->state) {
    case INITIAL:
	if (name->tag == TAG_NTA) {
	    s->state = NTA;
	} else {
	    s->state = ERR;
	    s->errorpos = INITIAL;
	    sprintf(errormsg, "nta tag expected but %s found", name->str);
	    s->errormsg = mystrdup(errormsg); 
	}
	break;
    case NTA:
	switch (name->tag) {
	case TAG_IMPORTS:
	    if (checkSiblings(s, s->siblings.back().empty()))
		s->state = IMPORTS;
	    break;
	case TAG_DECLARATION:
	    if (checkSiblings(s, s->siblings.back().empty()
			      || s->siblings.back().back() == IMPORTS)) {
		s->state = DECLARATION;     
	    }
	    break;
	case TAG_TEMPLATE:
	    if (checkSiblings(s, (s->siblings.back().empty() || 
				  s->siblings.back().back() == IMPORTS ||
				  s->siblings.back().back() == DECLARATION ||
				  s->siblings.back().back() == TEMPLATE)))
	    {
		s->state = TEMPLATE;
	    }
	    break;
	case TAG_INSTANTIATION:
	    if (checkSiblings(s, !s->siblings.back().empty() && 
			      s->siblings.back().back() == TEMPLATE))
	    {
		s->state = INSTANTIATION;
	    }
	    break;
	case TAG_SYSTEM:
	    if (checkSiblings(s, !s->siblings.back().empty() && 
			      (s->siblings.back().back() == TEMPLATE || 
			       s->siblings.back().back() == INSTANTIATION)))
	    {
		s->state = SYSTEM;
	    }
	    break;
	default:
	    checkSiblings(s, false);
	}
	break;
    case TEMPLATE:
	switch (name->tag) {
	case TAG_NAME:
	    if (checkSiblings(s, s->siblings.back().empty())) {
		s->state = NAME;
	    }
	    break;
	case TAG_PARAMETER:
	    if (checkSiblings(s, !s->siblings.back().empty() &&
			      s->siblings.back().back() == NAME))
	    {
		s->state = PARAMETER;
	    }
	    break;
	case TAG_DECLARATION:
	    if (checkSiblings(s, !s->siblings.back().empty() &&
			      (s->siblings.back().back() == NAME ||
			       s->siblings.back().back() == PARAMETER)))
	    {
		s->state = DECLARATION;
	    }
	    break;
	case TAG_LOCATION:
	    if (checkSiblings(s, !s->siblings.back().empty() &&
			      (s->siblings.back().back() == NAME ||
			       s->siblings.back().back() == PARAMETER ||
			       s->siblings.back().back() == DECLARATION ||
			       s->siblings.back().back() == LOCATION)))
	    {
		char *p = mystrdup(retrieve((const char**) attrs, "id"));
		s->locations[p] = NULL;
		s->labelkind = L_NONE;
		s->id = p;
		s->lname = NULL;
		s->state = LOCATION;
		s->committed = false;
		s->urgent = false;
	    }
	    break;
	case TAG_INIT:
	    if (checkSiblings(s, !s->siblings.back().empty() &&
			      (s->siblings.back().back() == NAME ||
			       s->siblings.back().back() == PARAMETER ||
			       s->siblings.back().back() == DECLARATION ||
			       s->siblings.back().back() == LOCATION)))
	    {
		const char *initRef = retrieve((const char**) attrs, "ref");
		if (initRef) {
		    locationmap_t::iterator l =
			s->locations.find((char*)initRef);
		    if (l != s->locations.end()) 
			try {
			    s->parser->procStateInit(l->second);
			} catch(TypeException te) {
			    s->errorHandler->handleError(te.what());
			}
		}
		s->state = INIT;
	    }
	    break;
	case TAG_TRANSITION:
	    if (checkSiblings(s, !s->siblings.back().empty() &&
			      (s->siblings.back().back() == NAME ||
			       s->siblings.back().back() == PARAMETER ||
			       s->siblings.back().back() == DECLARATION ||
			       s->siblings.back().back() == LOCATION ||
			       s->siblings.back().back() == INIT ||
			       s->siblings.back().back() == TRANSITION)))
	    {
		s->guard = s->sync = s->assign = false;
		s->state = TRANSITION;
	    }
	    break;
	default:
	    checkSiblings(s, false);
	}
	break;
    case LOCATION:
	switch (name->tag) {
	case TAG_NAME:
	    if (checkSiblings(s, s->siblings.back().empty())) {
		s->state = NAME;
	    }
	    break;
	case TAG_LABEL:
	    if (checkSiblings(s, (s->siblings.back().empty() || 
				  s->siblings.back().back() == NAME ||
				  s->siblings.back().back() == LABEL)))
	    {
		const char* kind = retrieve((const char**) attrs, "kind");
		if (strcmp(kind, "invariant")==0) s->labelkind = L_INV;
		else if (strcmp(kind, "guard")==0) s->labelkind = L_GUARD;
		else if (strcmp(kind, "synchronisation")==0) s->labelkind = L_SYNC;
		else if (strcmp(kind, "assignment")==0) s->labelkind = L_ASSIGN;
		else s->labelkind = L_NONE;
		s->state = LABEL;
	    }
	    break;
	case TAG_URGENT:
	    s->urgent = true;
	    s->state = URGENT;
	    break;
	case TAG_COMMITTED:
	    s->committed = true;
	    s->state = COMMITTED;
	    break;
	default:
	    checkSiblings(s, false);
	}
	break;
    case TRANSITION:
	switch (name->tag) {
	case TAG_SOURCE:
	    if (checkSiblings(s, s->siblings.back().empty())) {
		const char *ref = retrieve((const char**) attrs, "ref");
		s->sourceRef = s->locations.find((char*)ref)->second;
		s->state = SOURCE;
	    }
	    break;
	case TAG_TARGET:
	    if (checkSiblings(s, !s->siblings.back().empty() &&
			      s->siblings.back().back() == SOURCE))
	    {
		const char *ref = retrieve((const char**) attrs, "ref");
		s->targetRef = s->locations.find((char*)ref)->second;
		s->state = TARGET;
	    }
	    break;
	case TAG_LABEL:
	    if (checkSiblings(s, !s->siblings.back().empty() &&
			      (s->siblings.back().back() == TARGET ||
			       s->siblings.back().back() == LABEL)))
	    {
		const char* kind = retrieve((const char**) attrs, "kind");
		if (strcmp(kind, "invariant")==0) s->labelkind = L_INV;
		else if (strcmp(kind, "guard")==0) s->labelkind = L_GUARD;
		else if (strcmp(kind, "synchronisation")==0) s->labelkind = L_SYNC;
		else if (strcmp(kind, "assignment")==0) s->labelkind = L_ASSIGN;
		else s->labelkind = L_NONE;
		s->state = LABEL;
	    }
	    break;
	case TAG_NAIL:
	    if (checkSiblings(s, !s->siblings.back().empty() &&
			      (s->siblings.back().back() == TARGET ||
			       s->siblings.back().back() == LABEL ||
			       s->siblings.back().back() == NAIL)))
	    {
		s->state = NAIL;
	    }
	    break;
	default:
	    checkSiblings(s, false);
	}
	break;
    case ERR:
	printf("ERROR!\n");
	break;
    default:
	s->errorpos = s->state;
	s->state = ERR;
	sprintf(errormsg, "invalid tag %s at this position", name->str);
	s->errormsg = mystrdup(errormsg); 
	break;
    }
    s->siblings.push_back(vector<state_t>());
}

/**
 * SAX notifies when it encounters the end of tag (e.g. input:</tag>
 * => n="tag")
 */
static void NTA_endElement(void *user_data, const CHAR *n)
{
    ParserState* s = (ParserState*) user_data;
    const Tag *name = Tags::in_word_set((const char *)n,
					strlen((const char *)n));
    if (name == NULL) {
	s->errorpos = s->state;
	s->state = ERR;
	sprintf(errormsg, "unknown tag %s", (const char *)n);
	s->errormsg = mystrdup(errormsg);
	return;
    }

    if (s->history.empty() || name->tag != s->history.back().second) {
	s->errorpos = s->state;
	s->state = ERR;
	sprintf(errormsg, "cannot use %s end tag", name->str);
	s->errormsg = mystrdup(errormsg);
    } else {
	switch (s->state) {
	case DECLARATION:
	    switch (s->history.back().first) {
	    case NTA:
		if (!isempty(s->body)) {
		    parseXTA(s->body, s->parser, s->errorHandler, s->newxta, S_DECLARATION);
		}
		break;
	    case TEMPLATE:
		if (!isempty(s->body)) {
		    parseXTA(s->body, s->parser, s->errorHandler, s->newxta, S_LOCAL_DECL);
		}
		break;
	    default:
		// This should be unreachable!
		s->errorpos = s->state;
		s->state = ERR;
		sprintf(errormsg, "declaration tag is not allowed here");
		s->errormsg = mystrdup(errormsg);
	    }
	    break;
	case TEMPLATE:
	    try { s->parser->procEnd(); }
	    catch(TypeException te) { 
		s->errorHandler->handleError(te.what());
	    }
	    delete [] s->tname;
	    s->tname=NULL;
	    break;
	case INSTANTIATION: {
	    if (!isempty(s->body)) {
		parseXTA(s->body, s->parser, s->errorHandler, s->newxta, S_INST);
	    }
	    break;
	}
	case SYSTEM: {
	    if (!isempty(s->body)) {
		parseXTA(s->body, s->parser, s->errorHandler, s->newxta, S_SYSTEM);
	    }
	    break;
	}
	case NAME:
	    if (s->history.back().first == TEMPLATE) {
		s->tname = s->getName();
	    } else if (s->history.back().first == LOCATION) {
		s->lname = s->getName();
	    } 
	    break;
	case PARAMETER:
	    if (!isempty(s->body)) {
		s->parameter_count = parseXTA(s->body, s->parser, s->errorHandler, s->newxta, S_PARAMETERS);
	    } else s->parameter_count = 0;
	    try { s->parser->procBegin(s->tname, s->parameter_count); }
	    catch(TypeException &e) { 
		s->errorHandler->handleError(e.what());
	    }
	    break;
	case LOCATION: 
	    if (isempty(s->lname)) { // noname/anonymous location
		delete [] s->lname;
		s->lname = new char[strlen(s->id)+2];
		s->lname[0] = '_';
		strcpy(s->lname+1, s->id);
	    }
	    s->locations[(char*)s->id] = s->lname;
	    if (isempty(s->invariant)) {
		try { s->parser->exprTrue(); }
		catch(TypeException te) { 
		    s->errorHandler->handleError(te.what());
		}
		try { s->parser->procState(s->lname); }
		catch(TypeException te) { 
		    s->errorHandler->handleError(te.what());
		}
	    } else {
		parseXTA(s->invariant, s->parser, s->errorHandler, s->newxta, S_INVARIANT);
		try { s->parser->procState(s->lname); }
		catch(TypeException te) { 
		    s->errorHandler->handleError(te.what());
		}
	    }
	    if (s->committed)
		try { s->parser->procStateCommit(s->lname); }
		catch(TypeException te) { 
		    s->errorHandler->handleError(te.what());
		}
	    if (s->urgent)
		try { s->parser->procStateUrgent(s->lname); }
		catch(TypeException te) { 
		    s->errorHandler->handleError(te.what());
		}
	    s->invariant[0] = 0;
	    s->lname = NULL;
	    s->id = NULL;
	    break;
	case TRANSITION:
	    try { s->parser->procTransition(s->sourceRef, s->targetRef); }
	    catch(TypeException te) { 
		s->errorHandler->handleError(te.what());
	    }
	    break;
	case LABEL: {
	    switch (s->labelkind) {
	    case L_INV:
		if (s->body)
		    s->invariant = append(s->invariant, s->ilen, (const CHAR*)s->body, strlen(s->body));
		break;
	    case L_GUARD:
		if (isempty(s->body)) {
		    try { s->parser->exprTrue(); }
		    catch(TypeException te) { 
			s->errorHandler->handleError(te.what());
		    }
		} else {
		    parseXTA(s->body, s->parser, s->errorHandler, s->newxta, S_GUARD);
		}
		s->guard = true;
		break;
	    case L_SYNC:
		if (isempty(s->body)) 
		    try { s->parser->exprTrue(); }
		    catch(TypeException te) { 
			s->errorHandler->handleError(te.what());
		    }
		else {
		    parseXTA(s->body, s->parser, s->errorHandler, s->newxta, S_SYNC);
		}
		s->sync = true;
		break;
	    case L_ASSIGN: 
		if (isempty(s->body)) 
		    try { s->parser->exprTrue(); }
		    catch(TypeException te) { 
			s->errorHandler->handleError(te.what());
		    }
		else {
		    parseXTA(s->body, s->parser, s->errorHandler, s->newxta, S_ASSIGN);
		}
		s->assign = true;
		break;
	    default:
		// Unknown label => ignore it
		;
	    }
	    break;
	}
	case ERR:
	    printf("ERROR!\n");
	    break;
	default:
	    break;
	}
    }

    // We are done with this tag, so remove the siblings record
    s->siblings.pop_back();
    s->siblings.back().push_back(s->state);

    // Go back to previous state
    s->state = s->history.back().first;
    s->history.pop_back();

    // Delete any textual body
    s->body[0] = 0;
}

/**
 * SAX uses to interpret the XML entities (e.g. input:&lt; => "<")
 */
static xmlEntityPtr NTA_getEntity(void *user_data, const CHAR *name) 
{
    return xmlGetPredefinedEntity((xmlChar*)name);
}

/**
 * SAX passes its warnings here
 */
static void NTA_warning(void *user_data, const char *msg, ...) 
{
    ((ParserState*) user_data)->errorHandler->handleWarning(msg);
}

/**
 * SAX passes its errors here
 */
static void NTA_error(void *user_data, const char *msg, ...) 
{
    ((ParserState*) user_data)->errorHandler->handleError(msg);
    ((ParserState*) user_data)->result = -1;
}

/**
 * SAX passes its fatal errors here
 */
static void NTA_fatalError(void *user_data, const char *msg, ...) 
{
    ((ParserState*) user_data)->errorHandler->handleError(msg);
    ((ParserState*) user_data)->result = -1;
}

/**
 * Function addresses passed to SAX.
 * SAX validates only the XML welformedness if all members a NULL.
 * (NULL members are ignored).
 */
static xmlSAXHandler handler =
{
    NULL, // internalSubsetSAXFunc internalSubset;
    NULL, // isStandaloneSAXFunc isStandalone;
    NULL, // hasInternalSubsetSAXFunc hasInternalSubset;
    NULL, // hasExternalSubsetSAXFunc hasExternalSubset;
    NULL, // resolveEntitySAXFunc resolveEntity;
    NTA_getEntity, // getEntitySAXFunc getEntity; // transform &lt; into < etc.
    NULL, // entityDeclSAXFunc entityDecl;
    NULL, // notationDeclSAXFunc notationDecl;
    NULL, // attributeDeclSAXFunc attributeDecl;
    NULL, // elementDeclSAXFunc elementDecl;
    NULL, // unparsedEntityDeclSAXFunc unparsedEntityDecl;
    NULL, // setDocumentLocatorSAXFunc setDocumentLocator;
    NTA_startDocument, // startDocumentSAXFunc startDocument;
    NTA_endDocument, // endDocumentSAXFunc endDocument;
    NTA_startElement, // startElementSAXFunc startElement;
    NTA_endElement, // endElementSAXFunc endElement;
    NULL, // referenceSAXFunc reference;
    NTA_characters, // charactersSAXFunc characters;
    NULL, // ignorableWhitespaceSAXFunc ignorableWhitespace;
    NULL, // processingInstructionSAXFunc processingInstruction;
    NULL, // commentSAXFunc comment;
    NTA_warning, // warningSAXFunc warning;
    NTA_error, // errorSAXFunc error;
    NTA_fatalError //fatalErrorSAXFunc fatalError;
};

/**
 * The actual parsing interface function
 */
int32_t parseXMLBuffer(const char *buffer, ParserBuilder *pb,
		       ErrorHandler *errHandler, bool newxta)
{
    ParserState state(pb, errHandler, newxta);
    state.state = INITIAL;
    state.history.clear();
    state.unknown = 0;
    state.errorpos = INITIAL;
    state.result = 0;

    int32_t ret = 0;
    xmlParserCtxtPtr ctxt;

    ctxt = xmlCreateMemoryParserCtxt(buffer, strlen(buffer));
    if (ctxt == NULL) return -1;
    ctxt->sax = &handler;
    ctxt->userData = &state;

    if (xmlParseDocument(ctxt) != 0) {
	ret = -1;
    } else if (!ctxt->wellFormed) {
        ret = -1;
    } else {
	ret = state.result;
    }

    if (ctxt->sax != NULL)
	ctxt->sax = NULL;
    xmlFreeParserCtxt(ctxt);
    
    return ret;
}

/**
 * The actual parsing interface function
 */
int32_t parseXMLFile(const char *filename, ParserBuilder *pb,
		     ErrorHandler *errHandler, bool newxta) {
    ParserState state(pb, errHandler, newxta);
    state.state = INITIAL;
    state.history.clear();
    state.unknown = 0;
    state.errorpos = INITIAL;
    state.result = 0;

    int32_t ret = 0;
    xmlParserCtxtPtr ctxt;

    ctxt = xmlCreateFileParserCtxt(filename);
    if (ctxt == NULL) return -1;
    ctxt->sax = &handler;
    ctxt->userData = &state;

    xmlParseDocument(ctxt);

    if (ctxt->wellFormed) 
        ret = state.result;
    else {
	if (state.errormsg) {
	    printf(errormsg);
	    free(state.errormsg);
	}
        ret = -1;
    }
    if (ctxt->sax != NULL) ctxt->sax = NULL;
    xmlFreeParserCtxt(ctxt);
    
    return ret;
}

#ifdef TEST_XMLREADER

int main(int argc, char* argv[])
{
    printf("Symbol parse function test: ");
    if (strcmp("A",symbol("A")) == 0 &&
	strcmp("Aa",symbol(" Aa ")) == 0 &&
	symbol(" Aa= ") == NULL &&
	strcmp("Aa8",symbol(" Aa8 ")) == 0 &&
	symbol(" Aa8= ") == NULL &&
	symbol(" 8Aa= ") == NULL)
	printf("OK\n");
    else printf("Fail\n");

    printf("isempty function test: ");
    if (isempty(NULL) == true &&
	isempty("") == true &&
	isempty(" ") == true &&
	isempty(" \t\n \t") == true &&
	isempty(" \t\n-\t") == false &&
	isempty(" \t\nA\t") == false &&
	isempty("A") == false &&
	isempty(" \t\n8 \t") == false)
	printf("OK\n");
    else printf("Fail\n");

    printf("append function test: ");
    int32_t c=0;
    char *test = NULL;
    the_size_of_the_page = 4;
    if (strcmp(test=append(test, c, (const CHAR*) "012", 1), "0") == 0 &&
	strcmp(test=append(test, c, (const CHAR*) "12345", 2), "012") == 0 &&
	strcmp(test=append(test, c, (const CHAR*) "34567", 3), "012345") == 0 &&
	strcmp(test=append(test, c, (const CHAR*) "67890", 6), "01234567890") == 0)
	printf("OK\n");
    else printf("Fail\n");

    the_size_of_the_page = 1024;

    return 0;
}
#endif
