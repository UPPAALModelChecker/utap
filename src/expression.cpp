// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2002-2003 Uppsala University and Aalborg University.
   
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

#include <cassert>
#include <algorithm>

#include "utap/builder.h"
#include "utap/system.h"
#include "utap/expression.h"

using namespace UTAP;
using namespace Constants;

using std::vector;
using std::set;
using std::min;
using std::max;
using std::pair;
using std::make_pair;
using std::map;
using std::ostream;
using Constants::kind_t;
using Constants::synchronisation_t;

struct expression_t::expression_data
{
    int count;                  /**< Reference counter */
    position_t position;        /**< The position of the expression */
    kind_t kind;                /**< The kind of the node */
    union 
    {
	int32_t value;          /**< The value of the node */
	int32_t index;
	synchronisation_t sync; /**< The sync value of the node  */
    };
    symbol_t symbol;            /**< The symbol of the node */
    type_t type;                /**< The type of the expression */
    expression_t *sub;          /**< Subexpressions */
};

expression_t::expression_t()
{
    data = NULL;
}

expression_t::expression_t(kind_t kind, const position_t &pos)
{
    data = new expression_data;
    data->count = 1;
    data->kind = kind;
    data->position = pos;
    data->value = 0;
    data->sub = NULL;
}

expression_t::expression_t(const expression_t &e)
{
    data = e.data;
    if (data)
    {
	data->count++;
    }
}

expression_t::~expression_t()
{
    if (data) 
    {
	data->count--;
	if (data->count == 0) 
	{
	    delete[] data->sub;
	    delete data;
	}
    }
}

kind_t expression_t::getKind() const
{
    assert(data);
    return data->kind;
}

const position_t &expression_t::getPosition() const
{
    assert(data);
    return data->position;
}

uint32_t expression_t::getSize() const
{
    if (empty())
    {
	return 0;
    }

    switch (data->kind) 
    {
    case MINUS:
    case PLUS:
    case MULT:
    case DIV:
    case MOD:
    case BIT_AND:
    case BIT_OR:
    case BIT_XOR:
    case BIT_LSHIFT:
    case BIT_RSHIFT:
    case AND:
    case OR:
    case LT:
    case LE:
    case EQ:
    case NEQ:
    case GE:
    case GT:
    case MIN:
    case MAX:
	return 2;
    case UNARY_MINUS:
    case NOT:
	return 1;
	break;
    case IDENTIFIER:
    case CONSTANT:
	return 0;
	break;
    case LIST:
	return data->value;
	break;
    case ARRAY:
	return 2;
	break;
    case INLINEIF:
	return 3;
	break;
    case DOT:
	return 1;
    case LEADSTO:
    case COMMA:
    case ASSIGN:
    case ASSPLUS:
    case ASSMINUS:
    case ASSDIV:
    case ASSMOD:
    case ASSMULT:
    case ASSAND:
    case ASSOR:
    case ASSXOR:
    case ASSLSHIFT:
    case ASSRSHIFT:
	return 2;
    case SYNC:
	return 1;
    case DEADLOCK:
	return 0;
    case PREINCREMENT:
    case POSTINCREMENT:
    case PREDECREMENT:
    case POSTDECREMENT:
	return 1;
    case RATE:
	return 1;
    case FUNCALL:
	return data->value;
    default:
	assert(0);
	return 0;
    }
}
	
type_t expression_t::getType() const
{
    assert(data);
    return data->type;
}

void expression_t::setType(type_t type)
{
    assert(data);
    data->type = type;
}

int32_t expression_t::getValue() const
{
    assert(data && data->kind == CONSTANT);
    return data->value;
}

int32_t expression_t::getIndex() const
{
    assert(data && data->kind == DOT);
    return data->index;
}

synchronisation_t expression_t::getSync() const
{
    assert(data && data->kind == SYNC);
    return data->sync;
}

expression_t &expression_t::operator[](uint32_t i)
{
    assert(data && 0 <= i && i < getSize());
    return data->sub[i];
}
	
const expression_t expression_t::operator[](uint32_t i) const
{
    assert(data && 0 <= i && i < getSize());
    return data->sub[i];
}

expression_t &expression_t::get(uint32_t i)
{
    assert(data && 0 <= i && i < getSize());
    return data->sub[i];
}

const expression_t &expression_t::get(uint32_t i) const
{
    assert(data && 0 <= i && i < getSize());
    return data->sub[i];
}

bool expression_t::empty() const
{
    return data == NULL;
}

/** Two expressions are identical iff all the sub expressions
    are identical and if the kind, value and symbol of the 
    root are identical. */
bool expression_t::equal(const expression_t &e) const
{
    if (data == e.data)
    {
	return true;
    }

    if (getSize() != e.getSize()
	|| data->kind != e.data->kind
	|| data->value != e.data->value
	|| data->symbol != e.data->symbol)
    {
	return false;
    }

    for (uint32_t i = 0; i < getSize(); i++)
    {
	if (data->sub[i].equal(e[i]))
	{
	    return false;
	}
    }

    return true;
}

expression_t &expression_t::operator=(const expression_t &e)
{
    if (data) 
    {
	data->count--;
	if (data->count == 0) 
	{
	    delete[] data->sub;
	    delete data;
	}
    }
    data = e.data;
    if (data)
    {
	data->count++;
    }
    return *this;
}
	
/**
   Returns the symbol of a variable reference. The expression must be
   a left-hand side value. The symbol returned is the symbol of the
   variable the expression if resulting in a reference to. NOTE: In
   case of inline if, the symbol referenced by the 'true' part is
   returned.
*/
symbol_t expression_t::getSymbol() 
{
    return ((const expression_t*)this)->getSymbol();
}

/**
   Returns the symbol of a variable reference. The expression must be
   a left-hand side value. The symbol returned is the symbol of the
   variable the expression if resulting in a reference to. NOTE: In
   case of inline if, the symbol referenced by the 'true' part is
   returned.
*/
const symbol_t expression_t::getSymbol() const
{
    assert(data);

    switch (getKind()) 
    {
    case IDENTIFIER:
	return data->symbol;
      
    case DOT:
	return get(0).getType().getFrame()[data->value];
      
    case ARRAY:
	return get(0).getSymbol();
      
    case PREINCREMENT:
    case PREDECREMENT:
	return get(0).getSymbol();
    
    case INLINEIF:
	return get(1).getSymbol();
      
    case COMMA:
	return get(1).getSymbol();

    case ASSIGN:
    case ASSPLUS:
    case ASSMINUS:
    case ASSDIV:
    case ASSMOD:
    case ASSMULT:
    case ASSAND:
    case ASSOR:
    case ASSXOR:
    case ASSLSHIFT:
    case ASSRSHIFT:
	return get(0).getSymbol();

    case SYNC:
	return get(0).getSymbol();
	
    case FUNCALL:
	//Functions cannot return references (yet!)

    default:
	return symbol_t();
    }
}

/** Returns true if expr might be a reference to a symbol in the
    set. NOTE: This method does not use the getSymbol() call, since
    that one always returns the 'true' result of an inline if.
 */
bool expression_t::isReferenceTo(const std::set<symbol_t> &symbols) const
{
    if (empty())
    {
	return false;
    }

    switch (getKind()) 
    {
    case IDENTIFIER:
	return (symbols.find(data->symbol) != symbols.end());
    case ARRAY:
	return get(0).isReferenceTo(symbols);
    case PREINCREMENT:
    case PREDECREMENT:
	return get(0).isReferenceTo(symbols);
    case COMMA:
	return get(1).isReferenceTo(symbols);
    case DOT:
	return get(0).isReferenceTo(symbols) 
	    || symbols.find(getSymbol()) != symbols.end();

    case INLINEIF:
	return get(1).isReferenceTo(symbols) || get(2).isReferenceTo(symbols);

    case ASSIGN:
    case ASSPLUS:
    case ASSMINUS:
    case ASSDIV:
    case ASSMOD:
    case ASSMULT:
    case ASSAND:
    case ASSOR:
    case ASSXOR:
    case ASSLSHIFT:
    case ASSRSHIFT:
	return get(0).isReferenceTo(symbols);
    default:
	// This operation will not result in a reference
	return false;
    }
}

/** Returns true if \a fun changes any of the variables in \a variables. */
static bool changes(function_t *fun, const std::set<symbol_t> &variables)
{
    set<symbol_t>::const_iterator first1, first2, last1, last2;
    first1 = fun->changes.begin();
    last1 = fun->changes.end();
    first2 = variables.begin();
    last2 = variables.end();

    while (first1 != last1 && first2 != last2)
    {
	if (*first1 < *first2)
	{
	    ++first1;
	}
	else if (*first2 < *first1)
	{
	    ++first2;
	}
	else
	{
	    return true;
	}
    }
    return false;
}

bool expression_t::changesVariable(const std::set<symbol_t> &symbols) const
{
    function_t *fun;
    frame_t parameters;

    if (empty())
    {
	return false;
    }

    for (uint32_t i = 0; i < getSize(); i++) 
    {
	if (get(i).changesVariable(symbols)) 
	{
	    return true;  
	}
    }

    switch (getKind()) 
    {
    case ASSIGN:
    case ASSPLUS:
    case ASSMINUS:
    case ASSDIV:
    case ASSMOD:
    case ASSMULT:
    case ASSAND:
    case ASSOR:
    case ASSXOR:
    case ASSLSHIFT:
    case ASSRSHIFT:
    case POSTINCREMENT:
    case POSTDECREMENT:
    case PREINCREMENT:
    case PREDECREMENT:
	return get(0).isReferenceTo(symbols);
      
    case FUNCALL:
	fun = (function_t*)get(0).getSymbol().getData();
	
	// Check if symbols contains arguments to non-constant reference params
	parameters = fun->uid.getType().getParameters();
	for (uint32_t i = 0; i < min(getSize() - 1, parameters.getSize()); i++)
	{
	    type_t type = parameters[i].getType();
	    if (type.hasPrefix(prefix::REFERENCE)
		&& !type.hasPrefix(prefix::CONSTANT)
		&& get(i + 1).isReferenceTo(symbols))
	    {
		return true;
	    }
	}

	return changes(fun, symbols);

    default:
	return false;
    }
}

bool expression_t::dependsOn(const std::set<symbol_t> &symbols) const
{
    if (empty())
    {
	return false;
    }

    for (uint32_t i = 0; i < getSize(); i++) 
    {
	if (get(i).dependsOn(symbols)) 
	{
	    return true;
	}
    }

    if (getKind() == IDENTIFIER) 
    {
	return symbols.find(data->symbol) != symbols.end();
    }    

    return false;

}

int expression_t::getPrecedence() const
{
    return getPrecedence(data->kind);
}

int expression_t::getPrecedence(kind_t kind) 
{
    switch (kind) 
    {
    case PLUS:
    case MINUS:
	return 70;
	    
    case MULT:
    case DIV:
    case MOD:
	return 80;
	    
    case BIT_AND:
	return 37;
	    
    case BIT_OR:
	return 30;
	    
    case BIT_XOR:
	return 35;

    case BIT_LSHIFT:
    case BIT_RSHIFT:
	return 60;
	    
    case AND:
	return 25;
    case OR:
	return 20;

    case EQ:
    case NEQ:
	return 40;

    case MIN:
    case MAX:
	return 55;

    case LT:
    case LE:
    case GE:
    case GT:
	return 50;
	    
    case IDENTIFIER:
    case CONSTANT:
    case DEADLOCK:
    case FUNCALL:
	return 110;
	    
    case DOT:
    case ARRAY:
    case RATE:
	return 100;

    case UNARY_MINUS:
    case NOT:
	return 90;
	    
    case INLINEIF:
	return 15;

    case ASSIGN:
    case ASSPLUS:
    case ASSMINUS:
    case ASSDIV:
    case ASSMOD:
    case ASSMULT:
    case ASSAND:
    case ASSOR:
    case ASSXOR:
    case ASSLSHIFT:
    case ASSRSHIFT:
	return 10;

    case COMMA:
	return 5;

    case SYNC:
	return 0;

    case PREDECREMENT:
    case POSTDECREMENT:
    case PREINCREMENT:
    case POSTINCREMENT:
	return 100;

    case EF:
    case EG:
    case AF:
    case AG:
    case LEADSTO:
    case LIST:
	return -1; // TODO
    }
    assert(0);
    return 0;
}

static void ensure(char *&str, char *&end, int &size, int len)
{
    while (size <= len)
    {
	size *= 2;
    }
	
    char *nstr = new char[size];
    strncpy(nstr, str, end - str);
    end = nstr + (end - str);
    *end = 0;
    delete[] str;
    str = nstr;
}

static void append(char *&str, char *&end, int &size, const char *s)
{
    while (end < str + size && *s)
    {
	*(end++) = *(s++);
    }

    if (end == str + size) 
    {
	ensure(str, end, size, 2 * size);
	append(str, end, size, s);
    } 
    else 
    {
	*end = 0;
    }
    
//     int strlen = end - str;
//     int space = size - strlen;
//     int slen = strlcpy(end, s, space);
//     if (slen >= space) {
// 	ensure(str, end, size, strlen + slen + 1);
// 	append(str, end, size, s);
//     } else {
// 	end += slen;
//     }
}

static void append(char *&str, char *&end, int &size, char c)
{
    if (size - (end - str) < 2) 
    {
	ensure(str, end, size, size + 2);
    }
    *end = c;
    ++end;
    *end = 0;
}

void expression_t::toString(bool old, char *&str, char *&end, int &size) const
{
    char s[12];
    int precedence = getPrecedence();

    switch (data->kind) 
    {
    case PLUS:
    case MINUS:
    case MULT:
    case DIV:
    case MOD:
    case BIT_AND:
    case BIT_OR:
    case BIT_XOR:
    case BIT_LSHIFT:
    case BIT_RSHIFT:
    case AND:
    case OR:
    case LT:
    case LE:
    case EQ:
    case NEQ:
    case GE:
    case GT:
    case ASSIGN:
    case ASSPLUS:
    case ASSMINUS:
    case ASSDIV:
    case ASSMOD:
    case ASSMULT:
    case ASSAND:
    case ASSOR:
    case ASSXOR:
    case ASSLSHIFT:
    case ASSRSHIFT:
    case MIN:
    case MAX:

	if (precedence > get(0).getPrecedence())
	{
	    append(str, end, size, '(');
	}
	get(0).toString(old, str, end, size);
	if (precedence > get(0).getPrecedence())
	{
	    append(str, end, size, ')');
	}
	
	switch (data->kind) 
	{
	case PLUS:
	    append(str, end, size, " + ");
	    break;
	case MINUS:
	    append(str, end, size, " - ");
	    break;
	case MULT:
	    append(str, end, size, " * ");
	    break;
	case DIV:
	    append(str, end, size, " / ");
	    break;
	case MOD:
	    append(str, end, size, " % ");
	    break;
	case BIT_AND:
	    append(str, end, size, " & ");
	    break;
	case BIT_OR:
	    append(str, end, size, " | ");
	    break;
	case BIT_XOR:
	    append(str, end, size, " ^ ");
	    break;
	case BIT_LSHIFT:
	    append(str, end, size, " << ");
	    break;
	case BIT_RSHIFT:
	    append(str, end, size, " >> ");
	    break;
	case AND:
	    append(str, end, size, " && ");
	    break;
	case OR:
	    append(str, end, size, " || ");
	    break;
	case LT:
	    append(str, end, size, " < ");
	    break;
	case LE:
	    append(str, end, size, " <= ");
	    break;
	case EQ:
	    append(str, end, size, " == ");
	    break;
	case NEQ:
	    append(str, end, size, " != ");
	    break;
	case GE:
	    append(str, end, size, " >= ");
	    break;
	case GT:
	    append(str, end, size, " > ");
	    break;
	case ASSIGN:
	    if (old)
	    {
		append(str, end, size, " := ");
	    }
	    else
	    {
		append(str, end, size, " = ");
	    }
	    break;
	case ASSPLUS:
	    append(str, end, size, " += ");
	    break;
	case ASSMINUS:
	    append(str, end, size, " -= ");
	    break;
	case ASSDIV:
	    append(str, end, size, " /= ");
	    break;
	case ASSMOD:
	    append(str, end, size, " %= ");
	    break;
	case ASSMULT:
	    append(str, end, size, " *= ");
	    break;
	case ASSAND:
	    append(str, end, size, " &= ");
	    break;
	case ASSOR:
	    append(str, end, size, " |= ");
	    break;
	case ASSXOR:
	    append(str, end, size, " ^= ");
	    break;
	case ASSLSHIFT:
	    append(str, end, size, " <<= ");
	    break;
	case ASSRSHIFT:
	    append(str, end, size, " >>= ");
	    break;
	case MIN:
	    append(str, end, size, " <? ");
	    break;
	case MAX:
	    append(str, end, size, " >? ");
	    break;
	default:
	    assert(0);
	}
	
	if (precedence >= get(1).getPrecedence())
	{
	    append(str, end, size, '(');
	}
	get(1).toString(old, str, end, size);
	if (precedence >= get(1).getPrecedence())
	{
	    append(str, end, size, ')');
	}
	break;

    case IDENTIFIER:
	append(str, end, size, data->symbol.getName().c_str());
	break;
		
    case CONSTANT:
	snprintf(s, 12, "%d", data->value);
	append(str, end, size, s);
	break;

    case ARRAY:
	if (precedence > get(0).getPrecedence()) 
	{
	    append(str, end, size, '(');
	    get(0).toString(old, str, end, size);
	    append(str, end, size, ')');
	}
	else 
	{
	    get(0).toString(old, str, end, size);
	}
	append(str, end, size, '[');
	get(1).toString(old, str, end, size);
	append(str, end, size, ']');
	break;
	    
    case UNARY_MINUS:
	append(str, end, size, '-');
	if (precedence > get(0).getPrecedence()) 
	{
	    append(str, end, size, '(');
	    get(0).toString(old, str, end, size);
	    append(str, end, size, ')');
	}
	else 
	{
	    get(0).toString(old, str, end, size);
	}
	break;

    case POSTDECREMENT:
    case POSTINCREMENT:
	if (precedence > get(0).getPrecedence()) 
	{
	    append(str, end, size, '(');
	    get(0).toString(old, str, end, size);
	    append(str, end, size, ')');
	} 
	else 
	{
	    get(0).toString(old, str, end, size);
	}
	append(str, end, size, getKind() == POSTDECREMENT ? "--" : "++");
	break;
     
    case PREDECREMENT:
    case PREINCREMENT:
	append(str, end, size, getKind() == PREDECREMENT ? "--" : "++");
	if (precedence > get(0).getPrecedence()) 
	{
	    append(str, end, size, '(');
	    get(0).toString(old, str, end, size);
	    append(str, end, size, ')');
	} 
	else 
	{
	    get(0).toString(old, str, end, size);
	}
	break;

    case NOT:
	append(str, end, size, '!');
	if (precedence > get(0).getPrecedence()) 
	{
	    append(str, end, size, '(');
	    get(0).toString(old, str, end, size);
	    append(str, end, size, ')');
	}
	else 
	{
	    get(0).toString(old, str, end, size);
	}
	break;

    case DOT:
    {
	type_t base = get(0).getType().getBase();
	if (base == type_t::PROCESS || base == type_t::RECORD) 
	{
	    if (precedence > get(0).getPrecedence()) 
	    {
		append(str, end, size, '(');
		get(0).toString(old, str, end, size);
		append(str, end, size, ')');
	    } 
	    else 
	    {
		get(0).toString(old, str, end, size);
	    }
	    append(str, end, size, '.');
	    append(str, end, size, get(0).getType().getFrame()[data->value].getName().c_str());
	} 
	else 
	{
	    assert(0);
	}
	break;
    }	
	    
    case INLINEIF:
	if (precedence >= get(0).getPrecedence()) 
	{
	    append(str, end, size, '(');
	    get(0).toString(old, str, end, size);
	    append(str, end, size, ')');
	}
	else 
	{
	    get(0).toString(old, str, end, size);
	}

	append(str, end, size, " ? ");

	if (precedence >= get(1).getPrecedence()) 
	{
	    append(str, end, size, '(');
	    get(1).toString(old, str, end, size);
	    append(str, end, size, ')');
	}
	else 
	{
	    get(1).toString(old, str, end, size);
	}

	append(str, end, size, " : ");

	if (precedence >= get(2).getPrecedence()) 
	{
	    append(str, end, size, '(');
	    get(2).toString(old, str, end, size);
	    append(str, end, size, ')');
	}
	else 
	{
	    get(2).toString(old, str, end, size);
	}
	
	break;

    case COMMA:
	get(0).toString(old, str, end, size);
	append(str, end, size, ", ");
	get(1).toString(old, str, end, size);
	break;
	    
    case SYNC:
	get(0).toString(old, str, end, size);
	switch (data->sync) 
	{
	case SYNC_QUE:
	    append(str, end, size, '?');
	    break;
	case SYNC_BANG:
	    append(str, end, size, '!');
	    break;
	}
	break;

    case DEADLOCK:
	append(str, end, size, "deadlock");
	break;

    case LIST:
	append(str, end, size, "{ ");
	get(0).toString(old, str, end, size);
	for (uint32_t i = 1; i < getSize(); i++) 
	{
	    append(str, end, size, ", ");
	    get(i).toString(old, str, end, size);
	}
	append(str, end, size, " }");
	break;

    case FUNCALL:
 	append(str, end, size, get(0).getSymbol().getName().c_str());
 	append(str, end, size, '(');
 	if (getSize() > 1) 
	{
 	    get(1).toString(old, str, end, size);
 	    for (uint32_t i = 2; i < getSize(); i++) 
	    {
 		append(str, end, size, ", ");
 		get(i).toString(old, str, end, size);
 	    }
 	}
 	append(str, end, size, ')');
 	break;

    case RATE:
	get(0).toString(old, str, end, size);
	append(str, end, size, "'");
	break;
	
    case EF:
    case EG:
    case AF:
    case AG:
    case LEADSTO:
	assert(0); // TODO
    }
}

bool expression_t::operator < (const expression_t e) const
{
    return data != NULL && e.data != NULL && data < e.data;
}
 
bool expression_t::operator == (const expression_t e) const
{
    return data == e.data;
}


/** Returns a string representation of the expression. The string
    returned must be deallocated with delete[]. Returns NULL is the
    expression is empty. */
std::string expression_t::toString(bool old) const
{
    if (empty()) 
    {
	return std::string();
    } 
    else 
    {
 	int size = 16;
 	char *s, *end;
 	s = end = new char[size];
 	toString(old, s, end, size);
	std::string result = s;
	delete[] s;
 	return result;
    }
}

void expression_t::collectPossibleWrites(set<symbol_t> &symbols) const
{
    function_t *fun;
    frame_t parameters;

    if (empty())
    {
	return;
    }

    for (uint32_t i = 0; i < getSize(); i++) 
    {
	get(i).collectPossibleWrites(symbols);
    }

    switch (getKind()) 
    {
    case ASSIGN:
    case ASSPLUS:
    case ASSMINUS:
    case ASSDIV:
    case ASSMOD:
    case ASSMULT:
    case ASSAND:
    case ASSOR:
    case ASSXOR:
    case ASSLSHIFT:
    case ASSRSHIFT:
    case POSTINCREMENT:
    case POSTDECREMENT:
    case PREINCREMENT:
    case PREDECREMENT:
	symbols.insert(get(0).getSymbol());
	break;
      
    case FUNCALL:
	// Add all symbols which are changed by the function
	fun = (function_t*)get(0).getSymbol().getData();
	symbols.insert(fun->changes.begin(), fun->changes.end());

	// Add arguments to non-constant reference parameters
	parameters = fun->uid.getType().getParameters();
	for (uint32_t i = 0; i < min(getSize() - 1, parameters.getSize()); i++)
	{
	    type_t type = parameters[i].getType();
	    if (type.hasPrefix(prefix::REFERENCE)
		&& !type.hasPrefix(prefix::CONSTANT))
	    {
		symbols.insert(get(i + 1).getSymbol());
	    }
	}
	break;

    default:
	break;
    }
}

expression_t expression_t::createConstant(
    const position_t &pos, int32_t value)
{
    expression_t expr(CONSTANT, pos);
    expr.data->value = value;
    expr.data->type = type_t::INT;
    return expr;
}

expression_t expression_t::createIdentifier(
    const position_t &pos, symbol_t symbol)
{
    expression_t expr(IDENTIFIER, pos);
    expr.data->symbol = symbol;
    if (symbol != symbol_t())
    {
	expr.data->type = symbol.getType();
    }
    else
    {
	expr.data->type = type_t::UNKNOWN;
    }
    return expr;
}

expression_t expression_t::createNary(
    const position_t &pos, kind_t kind,
    const vector<expression_t> &sub, type_t type)
{
    assert(kind == LIST || kind == FUNCALL);
    expression_t expr(kind, pos);
    expr.data->value = sub.size();
    expr.data->sub = new expression_t[sub.size()];
    expr.data->type = type;
    for (uint32_t i = 0; i < sub.size(); i++)
    {
	expr.data->sub[i] = sub[i];
    }
    return expr;
}

expression_t expression_t::createUnary(
    const position_t &pos, kind_t kind, expression_t sub, type_t type)
{
    expression_t expr(kind, pos);
    expr.data->sub = new expression_t[1];
    expr.data->sub[0] = sub;
    expr.data->type = type;
    return expr;
}

expression_t expression_t::createBinary(
    const position_t &pos, kind_t kind, 
    expression_t left, expression_t right, type_t type)
{
    expression_t expr(kind, pos);
    expr.data->sub = new expression_t[2];
    expr.data->sub[0] = left;
    expr.data->sub[1] = right;
    expr.data->type = type;
    return expr;
}

expression_t expression_t::createTernary(
    const position_t &pos, kind_t kind, 
    expression_t e1, expression_t e2, expression_t e3, type_t type)
{
    expression_t expr(kind, pos);
    expr.data->sub = new expression_t[3];
    expr.data->sub[0] = e1;
    expr.data->sub[1] = e2;
    expr.data->sub[2] = e3;
    expr.data->type = type;
    return expr;
}

expression_t expression_t::createDot(
    const position_t &pos, expression_t e, int32_t idx, type_t type)
{
    expression_t expr(DOT, pos);
    expr.data->index = idx;
    expr.data->sub = new expression_t[1];
    expr.data->sub[0] = e;
    expr.data->type = type;
    return expr;
}

expression_t expression_t::createSync(
    const position_t &pos, expression_t e, synchronisation_t s)
{
    expression_t expr(SYNC, pos);
    expr.data->sync = s;
    expr.data->sub = new expression_t[1];
    expr.data->sub[0] = e;
    return expr;
}

expression_t expression_t::createDeadlock(const position_t &pos)
{
    expression_t expr(DEADLOCK, pos);
    expr.data->type = type_t::CONSTRAINT;
    return expr;
}

Interpreter::Interpreter()
{

}

Interpreter::Interpreter(const std::map<symbol_t, expression_t> &valuation)
    : valuation(valuation)
{

}

void Interpreter::addValuation(const std::map<symbol_t, expression_t> &v)
{
    valuation.insert(v.begin(), v.end());
}
    
int32_t Interpreter::evaluate(const expression_t expr) const
    throw (InterpreterException)
{
    vector<int32_t> v;
    evaluate(expr, v);
    assert(v.size() == 1);
    return v[0];
}

int32_t Interpreter::evaluateBinary(int32_t left, kind_t op, int32_t right) const
{
    switch (op) 
    {
    case PLUS:
	return left + right;
    case MINUS:
	return left - right;
    case MULT:
	return left * right;
    case DIV:
	return left / right;
    case MOD:
	return left % right;
    case BIT_AND:
	return left & right;
    case BIT_OR:
	return left | right;
    case BIT_XOR:
	return left ^ right;
    case BIT_LSHIFT:
	return left << right;
    case BIT_RSHIFT:
	return left >> right;
    case AND:
	return left && right;
    case OR:
	return left || right;
    case LT:
	return left < right;
    case LE:
	return left <= right;
    case EQ:
	return left == right;
    case NEQ:
	return left != right;
    case GE:
	return left >= right;
    case GT:
	return left > right;
    case MIN:
	return min(left, right);
    case MAX:
	return max(left, right);
    default:
	throw InterpreterException();
    }
}

void Interpreter::evaluate(
    const expression_t expr, std::vector<int32_t> &result) const
    throw (InterpreterException)
{
    int32_t left, right;
    size_t size;

    if (expr.empty())
    {
	throw InterpreterException();
    }
    
    switch (expr.getKind()) 
    {
    case PLUS:
    case MINUS:
    case MULT:
    case DIV:
    case MOD:
    case BIT_AND:
    case BIT_OR:
    case BIT_XOR:
    case BIT_LSHIFT:
    case BIT_RSHIFT:
    case AND:
    case OR:
    case LT:
    case LE:
    case EQ:
    case NEQ:
    case GE:
    case GT:
    case MIN:
    case MAX:
	size = result.size();

	/* Evaluate left side.
	 */
	evaluate(expr[0], result);
	if (size + 1!= result.size())
	{
	    throw InterpreterException();
	}
	left = result.back(); result.pop_back();

	/* Evaluate right side.
	 */
	evaluate(expr[1], result);
	if (size + 1 != result.size())
	{
	    throw InterpreterException();
	}
	right = result.back(); result.pop_back();

	result.push_back(evaluateBinary(left, expr.getKind(), right));
	break;

    case IDENTIFIER:
    {
	map<symbol_t, expression_t>::const_iterator i
	    = valuation.find(expr.getSymbol());
	if (i == valuation.end()) 
	{
	    throw InterpreterException();
	}

	evaluate(i->second, result);
	break;
    }
	
    case CONSTANT:
	result.push_back(expr.getValue());
	break;

    case LIST:
	for (uint32_t i = 0; i < expr.getSize(); i++)
	{
	    evaluate(expr[i], result);
	}
	break;
	    
    case ARRAY: 
    {
	type_t type = expr[0].getType();
	int32_t dsize = evaluate(type.getArraySize());
	size_t esize = sizeOfType(type.getSub());

	/* Evaluate array.
	 */
	size = result.size();
	evaluate(expr[0], result);

	if (result.size() - size != dsize * esize)
	{
	    throw InterpreterException();
	}

	/* Evaluate index. 
	 */
	size = result.size();
	evaluate(expr[1], result);
	
	if (size + 1 != result.size())
	{
	    throw InterpreterException();
	}

	int32_t index = result.back(); 
	result.pop_back();
	
	if (index < 0 || index >= dsize)
	{
	    throw InterpreterException();
	}

	/* Remove the things we do not want.
	 */
	result.erase(result.end() - (dsize - index - 1) * esize, result.end());
	result.erase(result.end() - (index + 1) * esize, result.end() - esize);
	break;
    }

    case UNARY_MINUS:
	size = result.size();
	evaluate(expr[0], result);
	if (size + 1 != result.size())
	{
	    throw InterpreterException();
	}
	result.back() = -result.back();
	break;

    case NOT:
	size = result.size();
	evaluate(expr[0], result);
	if (size + 1 != result.size())
	{
	    throw InterpreterException();
	}
	result.back() = !result.back();
	break;

    case DOT:
    {
	/* Evaluate record.
	 */
	size = result.size();
	evaluate(expr[0], result);
	if (result.size() - size != sizeOfType(expr[0].getType()))
	{
	    throw InterpreterException();
	}

	int32_t index = expr.getIndex();
	frame_t frame = expr[0].getType().getRecordFields();
	size_t esize = sizeOfType(frame[index].getType());

	if (index < 0 || index >= (int32_t)frame.getSize())
	{
	    throw InterpreterException();
	}
	
	/* Delete data after index.
	 */
	size_t space = 0;
	for (size_t i = index + 1; i < frame.getSize(); i++) 
	{
	    space += sizeOfType(frame[i].getType());
	}
	result.erase(result.end() - space, result.end());
	
	/* Delete data before index.
	 */
	space = 0;
	for (int32_t i = 0; i < index; i++)
	{
	    space += sizeOfType(frame[i].getType());
	}
	result.erase(result.end() - space - esize, result.end() - esize);

	break;
    }	    
    
    case INLINEIF:
    {
	/* Evaluate condition.
	 */
	size = result.size();
	evaluate(expr[0], result);
	if (size + 1 != result.size())
	{
	    throw InterpreterException();
	}
	int condition = result.back(); result.pop_back();

	/* Evaluate proper operand. 
	 */
	if (condition)
	{
	    evaluate(expr[1], result);
	}
	else
	{
	    evaluate(expr[2], result);
	}	
	break;
    }
	    
    default:
	throw InterpreterException();
    }
}

range_t Interpreter::evaluate(
    std::pair<expression_t, expression_t> range) const
    throw (InterpreterException)
{
    return range_t(evaluate(range.first), evaluate(range.second));
}


/** Returns the number of integer elements needed to represent a
    variable of this type. */
size_t Interpreter::sizeOfType(type_t type) const
{
    type_t base = type.getBase();
    if (base == type_t::CHANNEL || base == type_t::CLOCK || base == type_t::INT || base == type_t::BOOL || base == type_t::LOCATION)
    {
	return 1;
    }
    if (base == type_t::ARRAY) 
    {
	int32_t size = evaluate(type.getArraySize());
	if (size <= 0)
	{
	    throw InterpreterException();
	}
	return size * sizeOfType(type.getSub());
    }
    if (base == type_t::RECORD || base == type_t::PROCESS) 
    {
	size_t sum = 0;
	frame_t frame = type.getFrame();
	for (size_t i = 0; i < frame.getSize(); i++)
	{
	    sum += sizeOfType(frame[i].getType());
	}
	return sum;
    }
    
    return 0;
}

const map<symbol_t, expression_t> &Interpreter::getValuation() const
{
    return valuation;
}

ostream &operator<< (ostream &o, const expression_t &e) 
{
    o << e.toString();
    return o;
}
