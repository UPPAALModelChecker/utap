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

#ifndef UTAP_EXPRESSION_HH
#define UTAP_EXPRESSION_HH

#include <list>
#include <vector>

#include "utap/typesys.hh"

namespace UTAP
{
    class SubExpression;

    // Expressions are represented as a list of expression_t
    // structs. Each element contains information of the kind of
    // expression (identifier, number, binary operations, etc; for
    // this entry the constants defined in ParserBuilder in addition
    // to those defined in this class are used), a value (number, uid
    // of a symbol, etc), and the type (an entry in the
    // TypeSystem). To make sence, the different operations must be
    // "replayed" using a stack. In essence, the list simply stores
    // the sequence of calls of the corresponding methods in the
    // ParserBuilder interface. It is like a simple program for a
    // stack machine.
    class ExpressionProgram
    {
    public:
	struct expression_t {
	    uint32_t kind;
	    int32_t value;
	    type_t type;
	    expression_t(uint32_t k, int32_t v, int32_t t) 
		: kind(k), value(v), type(t) {}
	};
	typedef std::list<expression_t>::iterator iterator;
	typedef std::list<expression_t>::const_iterator const_iterator;

    private:
	std::list<expression_t> expr;

    public:
	ExpressionProgram() {}
	ExpressionProgram(const expression_t &e) { append(e); }
	ExpressionProgram(const_iterator first, const_iterator last)
	    : expr(first, last) {}
	ExpressionProgram(uint32_t kind, int32_t value, type_t type) {
	    append(kind, value, type);
	}
  
	iterator begin() { return expr.begin(); }
	iterator end()   { return expr.end(); }
	const_iterator begin() const { return expr.begin(); }
	const_iterator end() const   { return expr.end(); }

	void append(ExpressionProgram &e) { append(e.begin(), e.end()); }
	void append(iterator first, iterator last)   { insert(end(), first, last); }
	void append(const expression_t &e)           { insert(end(), e); }
	void append(uint32_t kind, int32_t value, type_t type) {
	    append(expression_t(kind, value, type));
	}
	void append(SubExpression op);

	void insert(iterator pos, const expression_t &e) { expr.insert(pos, e); }
	void insert(iterator pos, const_iterator first, const_iterator last) {
	    expr.insert(pos, first, last);
	}

	void erase(iterator pos)                     { expr.erase(pos); }
	void erase(iterator first, iterator last)    { expr.erase(first, last); }
	void clear()                                 { expr.clear(); }

	expression_t &back() { return expr.back(); }
	type_t getType() const { return expr.back().type; }

	// Decompose the operation at pos into its subexpressions. The first
	// position of each subexpression is stored in the sub vector. The number
	// of subexpression is returned.
	int decompose(const_iterator pos, std::vector<const_iterator> &sub) const;
	int decompose(iterator pos, std::vector<iterator> &sub);
	const_iterator findStartOf(const_iterator expr) const;
	iterator findStartOf(iterator expr);
	int getNumberOfSubExpressions(const expression_t &expr) const;
    };

    class SubExpression
    {
    public:
	SubExpression(ExpressionProgram &);

	uint32_t getKind() const;
	int32_t getValue() const;
	type_t getType() const;
	int32_t getSize() const;
	void setType(type_t);
	void setValue(int32_t);

	ExpressionProgram::const_iterator begin() const;
	ExpressionProgram::const_iterator end() const;
	ExpressionProgram::iterator begin();
	ExpressionProgram::iterator end();

	void move(int32_t, int32_t);

	ExpressionProgram &getExpression();

	SubExpression operator[] (uint32_t);
	SubExpression getSubExpression(uint32_t);
    private:
	friend class ExpressionProgram;
	SubExpression(ExpressionProgram &e, ExpressionProgram::iterator &o);
	ExpressionProgram &expr;
	ExpressionProgram::iterator pos;
    };

    inline SubExpression::SubExpression(ExpressionProgram &e, 
					ExpressionProgram::iterator &o)
	: expr(e), pos(o)
    {

    }

    inline SubExpression::SubExpression(ExpressionProgram &expr)
	: expr(expr), pos(--expr.end())
    {

    }

    inline uint32_t SubExpression::getKind() const
    {
	return pos->kind; 
    }

    inline int32_t SubExpression::getValue() const
    { 
	return pos->value; 
    }

    inline void SubExpression::setValue(int32_t value)
    {
	pos->value = value;
    }

    inline type_t SubExpression::getType() const
    {
	return pos->type; 
    }

    inline void SubExpression::setType(type_t value)
    {
	pos->type = value;
    }

    inline int32_t SubExpression::getSize() const
    {
	return expr.getNumberOfSubExpressions(*pos); 
    }

    inline ExpressionProgram::iterator SubExpression::begin()
    {
	return expr.findStartOf(pos);
    }

    inline ExpressionProgram::iterator SubExpression::end() 
    {
	ExpressionProgram::iterator result = pos;
	return ++result;
    }

    inline ExpressionProgram::const_iterator SubExpression::begin() const
    {
	return expr.findStartOf(pos);
    }

    inline ExpressionProgram::const_iterator SubExpression::end() const
    {
	ExpressionProgram::iterator result = pos;
	return ++result;
    }

    inline SubExpression SubExpression::operator[] (uint32_t idx)
    {
	return getSubExpression(idx);
    }

    inline void SubExpression::move(int src, int dst)
    {
	SubExpression d = getSubExpression(dst);
	SubExpression s = getSubExpression(src);
	expr.insert(d.begin(), s.begin(), s.end());
	expr.erase(s.begin(), s.end());
    }

    inline ExpressionProgram &SubExpression::getExpression()
    {
	return expr;
    }

}

#endif
