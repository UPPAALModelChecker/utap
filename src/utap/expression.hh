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
#include <set>

#include "utap/common.hh"
#include "utap/symbols.hh"

namespace UTAP
{
    class SubExpression;

    /** Representation of an expression in reverse polish notation.
	Expressions are represented in revere polish notation as a
	list of expression_t structures. For instance, the expression
	3 + (4 * 2) is represented by the instruction sequence [3] [4]
	[2] [*] [+].

	You can also think of this a program for a simple stack
	machine and each element is an instruction. To make any sence,
	the instructions must be executed/evaluated.

	Each 'instruction' contains information of the 'operation'
        (identifier, number, binary operations, etc; for this entry
        the constants defined in ParserBuilder are used), a value
        (number, ID of a symbol or type, etc), and the type of the
        result of the operation.

	In many ways, an ExpressionProgram simply stores the sequence
	of calls of the exprXXX methods in the abstract ParserBuilder
	class.

	See also SubExpression.
    */
    class ExpressionProgram
    {
    public:
	struct expression_t {
	    uint32_t kind;	/**< The kind of operation */
	    int32_t value;	/**< A value; interpretation depends on kind */
	    type_t type;	/**< The type of the result */
	    position_t position;/**< Textual position (for error reporting) */
	    expression_t(position_t p, uint32_t k, int32_t v, type_t t) 
		: kind(k), value(v), type(t), position(p) {}
	};
	typedef std::list<expression_t>::iterator iterator;
	typedef std::list<expression_t>::const_iterator const_iterator;

    private:
	std::list<expression_t> expr;

    public:
	/** Create empty expression program */
	ExpressionProgram() {}

	/** Create expression program containing one operation */
	ExpressionProgram(const expression_t &e) { append(e); }

	/** Create expression program. Insert operations between first
	    and last.
	*/
	ExpressionProgram(const_iterator first, const_iterator last)
	    : expr(first, last) {}

	/** Create expression program containing one operation */
	ExpressionProgram(const position_t &pos, uint32_t kind, int32_t value, type_t type) {
	    append(pos, kind, value, type);
	}

	/** Returns iterator to the beginning of the program */
	iterator begin() { return expr.begin(); }

	/** Returns iterator to the end of the program */
	iterator end()   { return expr.end(); }

	/** Returns iterator to the beginning of the program */
	const_iterator begin() const { return expr.begin(); }

	/** Returns iterator to the end of the program */
	const_iterator end() const   { return expr.end(); }

	/** Appends operations of another expression program */
	void append(ExpressionProgram &e) { append(e.begin(), e.end()); }

	/** Appends operations between first and last */
	void append(iterator first, iterator last)   { insert(end(), first, last); }

	/** Appends an operation */
	void append(const expression_t &e)           { insert(end(), e); }

	/** Appends an operation */
	void append(const position_t &pos, uint32_t kind,
		    int32_t value, type_t type) {
	    append(expression_t(pos, kind, value, type));
	}

	/** Appends another expression */
	void append(SubExpression op);

	/** Insert operation at position */
	void insert(iterator pos, const expression_t &e) { expr.insert(pos, e); }
	/** Insert operations between first and last at position */
	void insert(iterator pos, const_iterator first, const_iterator last) {
	    expr.insert(pos, first, last);
	}

	/** Erase operation at position */
	void erase(iterator pos)                     { expr.erase(pos); }

	/** Erase operations between first and last */
	void erase(iterator first, iterator last)    { expr.erase(first, last); }

	/** Erase all operations */
	void clear()                                 { expr.clear(); }

	/** Returns last operation */
	expression_t &back() { return expr.back(); }

	/** Returns the result type of the expression */
	type_t getType() const { return expr.back().type; }

	/** Decompose operation at position into subexpressions.  The
	    first position of each subexpression is stored in the sub
	    vector. The number of subexpressions is returned.
	*/
	int decompose(const_iterator pos, std::vector<const_iterator> &sub) const;

	/** Decompose operation at position into subexpressions.  The
	    first position of each subexpression is stored in the sub
	    vector. The number of subexpressions is returned.
	*/
	int decompose(iterator pos, std::vector<iterator> &sub);

	const_iterator findStartOf(const_iterator expr) const;
	iterator findStartOf(iterator expr);

	/** Returns the arity of an operation */
	int getNumberOfSubExpressions(const expression_t &expr) const;

	/** Returns true if this is an empty expression */
	bool empty() const { return expr.empty(); }
    };

    /** A tree-view of an ExpressionProgram. */
    class SubExpression
    {
    public:
	SubExpression(ExpressionProgram &);

	uint32_t getKind() const;
	int32_t getValue() const;
	type_t getType() const;
	int32_t getSize() const;
	const position_t &getPosition() const;
	void setType(type_t);
	void setValue(int32_t);

	ExpressionProgram::const_iterator begin() const;
	ExpressionProgram::const_iterator end() const;
	ExpressionProgram::iterator begin();
	ExpressionProgram::iterator end();

	void move(int32_t, int32_t);
	void replace(ExpressionProgram &);

	ExpressionProgram &getExpression();

	SubExpression operator[] (uint32_t);
	const SubExpression operator[] (uint32_t) const;
	SubExpression get(uint32_t);
	const SubExpression get(uint32_t) const;

	symbol_t getSymbol() const;
	bool isReferenceTo(const std::set<int> &) const;
	bool changesVariable(const std::set<int> &) const;
	bool dependsOn(const std::set<int> &) const;
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
	return get(idx);
    }

    inline const SubExpression SubExpression::operator[] (uint32_t idx) const
    {
	return get(idx);
    }

    inline void SubExpression::move(int src, int dst)
    {
	SubExpression d = get(dst);
	SubExpression s = get(src);
	expr.insert(d.begin(), s.begin(), s.end());
	expr.erase(s.begin(), s.end());
    }

    inline void SubExpression::replace(ExpressionProgram &e)
    {
	ExpressionProgram::iterator first = begin();
	ExpressionProgram::iterator last = end();
        expr.insert(first, e.begin(), e.end());
	pos = first;
	--pos;
	expr.erase(first, last);
    }
   
    inline ExpressionProgram &SubExpression::getExpression()
    {
	return expr;
    }

}

#endif
