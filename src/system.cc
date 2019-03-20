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

#include <stack>
#include <stdio.h>

#include "utap/builder.hh"
#include "utap/system.hh"

using namespace UTAP;
using namespace Constants;

using std::list;
using std::stack;
using std::vector;
using std::map;
using std::pair;
using std::make_pair;
using std::min;
using std::max;

#define defaultIntMin -0x7FFF
#define defaultIntMax 0x7FFF

static const char *const unsupported
= "Internal error: Feature not supported in this mode.";
static const char *const invalid_type = "Invalid type";

TimedAutomataSystem::TimedAutomataSystem()
{
    current_template = &global;
    global.frame = SymbolTable::ROOT;
    symbols.addSymbol("bool", types.addNamedType(types.addInteger(0, 1)));
    symbols.addSymbol("int",
		       types.addNamedType(
			   types.addInteger(defaultIntMin, defaultIntMax)));
    symbols.addSymbol("chan", types.addNamedType(TypeSystem::CHANNEL));
    symbols.addSymbol("clock", types.addNamedType(TypeSystem::CLOCK));
    addClock(TypeSystem::CLOCK, "t(0)");
}

TimedAutomataSystem::~TimedAutomataSystem()
{

}

TypeSystem &TimedAutomataSystem::getTypeSystem()
{
    return types;
}

SymbolTable &TimedAutomataSystem::getSymbolTable()
{
    return symbols;
}

const char *TimedAutomataSystem::getName(int32_t uid) const
{
    return symbols.getName(uid);
}

list<TimedAutomataSystem::template_t> &TimedAutomataSystem::getTemplates()
{
    return templates;
}

list<TimedAutomataSystem::process_t> &TimedAutomataSystem::getProcesses()
{
    return processes;
}

TimedAutomataSystem::template_t &TimedAutomataSystem::getGlobals()
{
    return global;
}

TimedAutomataStructures::template_t &
TimedAutomataSystem::addTemplate(type_t type, const char *name)
{
    templates.push_back(template_t());
    template_t &templ = templates.back();
    templ.uid = symbols.addSymbol(name, type, &templ);
    templ.frame = symbols.addFrame();
    templ.init = -1;

    if (templ.uid == -1) {
        throw TypeException("Duplicate definition of %s", name);
    } 

    return templ;
}

TimedAutomataStructures::state_t &
TimedAutomataSystem::addLocation(const char *name, ExpressionProgram &inv)
{
    current_template->states.push_back(state_t());
    state_t &state = current_template->states.back();
    state.uid = symbols.addSymbol(name, TypeSystem::LOCATION, &state);
    state.locNr = current_template->states.size() - 1;
    state.invariant = inv;

    if (state.uid == -1) {
	throw TypeException("Duplicate definition of %s", name);
    }

    return state;
}

TimedAutomataStructures::transition_t &
TimedAutomataSystem::addTransition(int32_t src, int32_t dst)
{
    current_template->transitions.push_back(transition_t());
    current_template->transitions.back().src = 
	static_cast<state_t*>(symbols.getData(src));
    current_template->transitions.back().dst =
	static_cast<state_t*>(symbols.getData(dst));
    return current_template->transitions.back();
}

TimedAutomataStructures::process_t &
TimedAutomataSystem::addProcess(int32_t uid, template_t &templ)
{
    processes.push_back(process_t());
    processes.back().uid = uid;
    processes.back().nr = processes.size() - 1;
    processes.back().templ = &templ;
    return processes.back();
}

TimedAutomataSystem::template_t &TimedAutomataSystem::getCurrentTemplate()
{
    return *current_template;
}

void TimedAutomataSystem::setCurrentTemplate(template_t &value)
{
    current_template = &value;
}

int32_t TimedAutomataSystem::sizeOfType(int32_t type)
{
    switch (types.getClass(type)) {
    case TypeSystem::CHANNEL:
    case TypeSystem::CLOCK:
    case TypeSystem::INT:
	return 1;
    case TypeSystem::ARRAY:
	return (types.getIntegerRange(types.getFirstSubType(type)).second + 1)
	    * sizeOfType(types.getSecondSubType(type));
    case TypeSystem::RECORD: {
	uint32_t sum = 0;
	const vector<pair<char *, int> > &record = types.getRecord(type);
	for (uint32_t i = 0, size = record.size(); i < size; i++)
	    sum += sizeOfType(record[i].second);
	return sum;
    }
    default:
	throw TypeException("BUG: Cannot compute size of this type %d",
			    types.getClass(type));
    }
}

int32_t TimedAutomataSystem::evaluateBinary(int32_t left, int32_t op, int32_t right) {
    switch (op) {
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
	throw TypeException(unsupported);
    }
}

bool TimedAutomataSystem::evaluateConstantExpression(
    const SubExpression &expr, int32_t &result)
{
    map<int32_t, ExpressionProgram> emptyMap;
    vector<int32_t> s;
    if (types.getClass(expr.getType()) != TypeSystem::INT)
	throw TypeException("Integer expression expected");
    if (!types.isConstant(expr.getType()))
	return false;
    if (!evaluateExpression(expr, emptyMap, s))
	return false;
    if (s.size() == 0)
	return false;
    result = s.back();
    return true;
}

// Evaluate the expression. Use the mapping to assign meaning to
// identifiers. Identifiers not mapped by the given mapping are mapped
// using the build-in constantMapping. The result will be stored in
// the vector (the result cave have size bigger than one).
bool TimedAutomataSystem::evaluateExpression(
    const SubExpression &expr, map<int32_t, ExpressionProgram> &mapping,
    vector<int32_t> &s)
{
    ExpressionProgram::const_iterator first, last;
    int32_t left, right;

    first = expr.begin();
    last = expr.end();

    while (first != last) {
	switch (first->kind) {
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
	    right = s.back(); s.pop_back();
	    left = s.back(); s.pop_back();
	    s.push_back(evaluateBinary(left, first->kind, right));
	    break;

	case IDENTIFIER:
	    switch (types.getClass(first->type)) {
	    case TypeSystem::ARRAY:
	    case TypeSystem::INT:
	    case TypeSystem::RECORD:
	    {
		map<int32_t, ExpressionProgram>::iterator i
		    = mapping.find(first->value);
		if (i == mapping.end()) {
		    i = constantMapping.find(first->value);
		    if (i == constantMapping.end())
			return false;
		}
		if (!evaluateExpression(i->second, mapping, s))
		    return false;
		break;
	    }
	    default:
		throw TypeException(unsupported);
	    }
	    break;
		
	case CONSTANT:
	    s.push_back(first->value);
	    break;

	case LIST:
	    // Nothing to do
	    break;
	    
	case ARRAY: {
	    int type = first->value; // Array type is in the value field
	    int index = s.back(); s.pop_back();
	    int size = types.getIntegerRange(types.getFirstSubType(type)).second + 1;
	    int subsize = sizeOfType(types.getSecondSubType(type));
	    s.erase(s.end() - (size - index - 1) * subsize, s.end());
	    s.erase(s.end() - (index + 1) * subsize, s.end() - subsize);
	    break;
	}

	case UNARY_MINUS:
	    s.back() = -s.back();
	    break;

	case NOT:
	    s.back() = !s.back();
	    break;

	case DOT:
	{
	    int index = first->value;
	    ExpressionProgram::const_iterator str = first;
	    --str;
	    const vector<pair<char *, int> > &record =
		types.getRecord(str->type);
	    int size = sizeOfType(record[index].second);
	    
	    // Delete data after index
	    int space = 0;
	    for (int i = record.size() - 1; i > index; i--) 
		space += sizeOfType(record[i].second);
	    s.erase(s.end() - space, s.end());

	    // Delete data before index
	    space = 0;
	    for (int i = index - 1; i >= 0; i--)
		space += sizeOfType(record[i].second);
	    s.erase(s.end() - space - size, s.end() - size);

	    break;
	}	    
	case INLINEIF:
	    right = s.back(); s.pop_back();
	    left = s.back(); s.pop_back();
	    s.back() = (s.back() ? left : right);
	    break;
	    
	default:
	    throw TypeException(unsupported);
	}

	++first;
    }
    return true;
}

// Add clock to current_template (which might be the "global"
// template)
void TimedAutomataSystem::addClock(int32_t type, const char *name)
{
    int32_t offset;
    if (current_template->clocks.empty()) {
	offset = 0;
    } else {
	offset =
	    current_template->clocks.back().offset
	    + current_template->clocks.back().size;
    }
    current_template->clocks.push_back(clock_t());
    clock_t *clock = &current_template->clocks.back();
    clock->uid = symbols.addSymbol(name, type, clock);
    clock->size = sizeOfType(type);
    clock->offset = offset;
    clock->global = (current_template == &global);

    if (clock->uid == -1) 
	throw TypeException("Duplicate definition of identifier %s", name);
}

// Add an integer to current_template (which might be the "global"
// template)
void TimedAutomataSystem::addVariable(
    int32_t type, const char *name, const ExpressionProgram &initial)
{	
    variable_t *var;
    int32_t offset;

    // Compute offset
    if (current_template->variables.empty()) {
	offset = 0;
    } else {
	offset =
	    current_template->variables.back().offset
	    + current_template->variables.back().size;
    }

    // Add variable
    current_template->variables.push_back(variable_t());
    var = &current_template->variables.back();
    var->expr = initial;
    var->size = sizeOfType(type);
    var->offset = offset;
    var->global = (current_template == &global);

    // Add symbol
    var->uid = symbols.addSymbol(name, type, var);
    if (var->uid == -1) 
	throw TypeException("Duplicate definition of identifier %s", name);
}

void TimedAutomataSystem::addConstant(
    int32_t type, const char *name, const ExpressionProgram &initial)
{	
    constant_t *constant;

    int32_t offset;
    if (current_template->constants.empty()) {
	offset = 0;
    } else {
	offset =
	    current_template->constants.back().offset
	    + current_template->constants.back().size;
    }

    // Add variable
    current_template->constants.push_back(constant_t());
    constant = &current_template->constants.back();
    constant->expr = initial;
    constant->size = sizeOfType(type);
    constant->global = (current_template == &global);
    constant->offset = offset;

    // Add symbol
    constant->uid = symbols.addSymbol(name, type, constant);
    if (constant->uid == -1) 
	throw TypeException("Duplicate definition of identifier %s", name);

    constantMapping[constant->uid] = initial;
}

// Add a channel to current_template (which might be the "global"
// template)
void TimedAutomataSystem::addChannel(int32_t type, const char *name)
{
    int32_t offset;
    if (current_template->channels.empty()) {
	offset = 0;
    } else {
	offset =
	    current_template->channels.back().offset
	    + current_template->channels.back().size;
    }

    current_template->channels.push_back(channel_t());
    channel_t *channel = &current_template->channels.back();
    channel->uid = symbols.addSymbol(name, type, channel);
    channel->size = sizeOfType(type);
    channel->offset = offset;
    channel->global = (current_template == &global);

    if (channel->uid == -1) 
	throw TypeException("Duplicate definition of identifier %s", name);
}

// Add a function to current_template (which might be the "global" template)
TimedAutomataSystem::function_t &
TimedAutomataSystem::addFunction(int32_t type, const char *name)
{	
    // Add function
    current_template->functions.push_back(function_t());
    function_t &fun = current_template->functions.back();
    fun.global = (current_template == &global);
    // Add symbol
    fun.uid = symbols.addSymbol(name, type, &fun);
    if (fun.uid == -1) 
	throw TypeException("Duplicate definition of identifier %s", name);
    return fun;
}

int TimedAutomataSystem::getPrecedence(int kind)
{
    switch (kind) {
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
    case CONSTRAINT:
	return 50;
	    
    case IDENTIFIER:
    case CONSTANT:
    case DEADLOCK:
	return 110;
	    
    case DOT:
    case ARRAY:
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
	    
    default:
	throw TypeException(unsupported);
    }
}

char *TimedAutomataSystem::expressionToString(const ExpressionProgram& expr)
{
    return expressionToString(expr.begin(), expr.end());
}

char *TimedAutomataSystem::expressionToString(const SubExpression& sub)
{
    return expressionToString(sub.begin(), sub.end());
}

char *TimedAutomataSystem::expressionToString(
    ExpressionProgram::const_iterator first,
    ExpressionProgram::const_iterator last)
{
    typedef pair<int, char *> element_t;
    stack<element_t> st;

    while (first != last) {
	element_t left, right;
	char *s;
	int precedence = getPrecedence(first->kind);
	
	switch (first->kind) {
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
	    right = st.top(); st.pop();
	    left = st.top(); st.pop();

	    s = new char[strlen(left.second) + strlen(right.second) + 10];
	    st.push(make_pair(precedence, s));

	    if (precedence > left.first)
		sprintf(s, "(%s)", left.second);
	    else
		sprintf(s, "%s", left.second);
				  
	    switch (first->kind) {
	    case PLUS:
		strcat(s, " + ");
		break;
	    case MINUS:
		strcat(s, " - ");
		break;
	    case MULT:
		strcat(s, " * ");
		break;
	    case DIV:
		strcat(s, " / ");
		break;
	    case MOD:
		strcat(s, " % ");
		break;
	    case BIT_AND:
		strcat(s, " & ");
		break;
	    case BIT_OR:
		strcat(s, " | ");
		break;
	    case BIT_XOR:
		strcat(s, " ^ ");
		break;
	    case BIT_LSHIFT:
		strcat(s, " << ");
		break;
	    case BIT_RSHIFT:
		strcat(s, " >> ");
		break;
	    case AND:
		strcat(s, " && ");
		break;
	    case OR:
		strcat(s, " || ");
		break;
	    case LT:
		strcat(s, " < ");
		break;
	    case LE:
		strcat(s, " <= ");
		break;
	    case EQ:
		strcat(s, " == ");
		break;
	    case NEQ:
		strcat(s, " != ");
		break;
	    case GE:
		strcat(s, " >= ");
		break;
	    case GT:
		strcat(s, " > ");
		break;
	    case ASSIGN:
		strcat(s, " = ");
		break;
	    case ASSPLUS:
		strcat(s, " += ");
		break;
	    case ASSMINUS:
		strcat(s, " -= ");
		break;
	    case ASSDIV:
		strcat(s, " /= ");
		break;
	    case ASSMOD:
		strcat(s, " %= ");
		break;
	    case ASSMULT:
		strcat(s, " *= ");
		break;
	    case ASSAND:
		strcat(s, " &= ");
		break;
	    case ASSOR:
		strcat(s, " |= ");
		break;
	    case ASSXOR:
		strcat(s, " ^= ");
		break;
	    case ASSLSHIFT:
		strcat(s, " <<= ");
		break;
	    case ASSRSHIFT:
		strcat(s, " >>= ");
		break;
	    case MIN:
		strcat(s, " <? ");
		break;
	    case MAX:
		strcat(s, " >? ");
		break;
	    default:
		throw TypeException(unsupported);
	    }

	    if (precedence >= right.first) 
		sprintf(s + strlen(s), "(%s)", right.second);
	    else
		strcat(s, right.second);

	    delete[] left.second;
	    delete[] right.second;
	    break;

	case IDENTIFIER:
	    s = (char*)symbols.getName(first->value);
	    st.push(make_pair(
			precedence, strcpy(new char[strlen(s) + 1], s)));
	    break;
		
	case CONSTANT:
	    s = new char[12];
	    snprintf(s, 12, "%d", first->value);
	    st.push(make_pair(precedence, s));
	    break;

	case ARRAY:
	    right = st.top(); st.pop();
	    left = st.top(); st.pop();
	    s = new char[strlen(left.second) + strlen(right.second) + 5];
	    if (precedence > left.first)
		sprintf(s, "(%s)[%s]", left.second, right.second);
	    else
		sprintf(s, "%s[%s]", left.second, right.second);
	    st.push(make_pair(precedence, s));
	    delete[] left.second;
	    delete[] right.second;
	    break;
	    
	case UNARY_MINUS:
	    s = new char[strlen(st.top().second) + 4];
	    if (precedence > st.top().first)
		sprintf(s, "-(%s)", st.top().second);
	    else
		sprintf(s, "-%s", st.top().second);
	    delete[] st.top().second;
	    st.top() = make_pair(precedence, s);
	    break;

	case POSTDECREMENT:
	    s = new char[strlen(st.top().second) + 5];
	    if (precedence > st.top().first)
		sprintf(s, "(%s)--", st.top().second);
	    else
		sprintf(s, "%s--", st.top().second);
	    delete[] st.top().second;
	    st.top() = make_pair(precedence, s);
	    break;

	case POSTINCREMENT:
	    s = new char[strlen(st.top().second) + 5];
	    if (precedence > st.top().first)
		sprintf(s, "(%s)++", st.top().second);
	    else
		sprintf(s, "%s++", st.top().second);
	    delete[] st.top().second;
	    st.top() = make_pair(precedence, s);
	    break;
	    
	case PREDECREMENT:
	    s = new char[strlen(st.top().second) + 5];
	    if (precedence > st.top().first)
		sprintf(s, "--(%s)", st.top().second);
	    else
		sprintf(s, "--%s", st.top().second);
	    delete[] st.top().second;
	    st.top() = make_pair(precedence, s);
	    break;

	case PREINCREMENT:
	    s = new char[strlen(st.top().second) + 5];
	    if (precedence > st.top().first)
		sprintf(s, "++(%s)", st.top().second);
	    else
		sprintf(s, "++%s", st.top().second);
	    delete[] st.top().second;
	    st.top() = make_pair(precedence, s);
	    break;

	case NOT:
	    s = new char[strlen(st.top().second) + 4];
	    if (precedence > st.top().first)
		sprintf(s, "!(%s)", st.top().second);
	    else
		sprintf(s, "!%s", st.top().second);
	    delete[] st.top().second;
	    st.top() = make_pair(precedence, s);
	    break;

	case DOT:
	{
	    const char *sub;
	    ExpressionProgram::const_iterator i = first;
	    --i;

	    switch (types.getClass(i->type)) {
	    case TypeSystem::PROCESS:
		sub = symbols.getName(first->value);
		break;
	    case TypeSystem::RECORD:	
		sub = types.getRecord(i->type)[first->value].first;
		break;
	    default:
		throw TypeException("BUG: Unexpected type here");
	    }

	    s = new char[strlen(st.top().second) + 4 + strlen(sub)];
	    if (precedence > st.top().first)
		sprintf(s, "(%s).%s", st.top().second, sub);
	    else 
		sprintf(s, "%s.%s", st.top().second, sub);
	    delete[] st.top().second;
	    st.top() = make_pair(precedence, s);
	    break;
	}	
	    
	case INLINEIF:	
	    right = st.top(); st.pop(); // else
	    left = st.top(); st.pop();  // then
	    s = new char[strlen(st.top().second) + strlen(left.second)
			 + strlen(right.second) + 13];

	    if (precedence >= st.top().first)
		sprintf(s, "(%s)", st.top().second);
	    else
		strcpy(s, st.top().second);

	    strcat(s, " ? ");

	    if (precedence >= left.first)
		sprintf(s, "(%s)", left.second);
	    else
		strcat(s, left.second);

	    strcat(s, " : ");

	    if (precedence >= right.first)
		sprintf(s, "(%s)", right.second);
	    else
		strcat(s, right.second);	    

	    delete[] left.second;
	    delete[] right.second;
	    delete[] st.top().second;
	    st.top() = make_pair(precedence, s);
	    break;

	case CONSTRAINT:
	    right = st.top(); st.pop(); // value
	    left = st.top(); st.pop();  // clock2
	    s = new char[strlen(st.top().second) + strlen(left.second)
			 + strlen(right.second) + 8];
	    sprintf(s, "%s - %s", st.top().second, left.second);

	    if (first->value) {
		strcat(s, " < ");
	    } else {
		strcat(s, " <= ");
	    }

	    strcat(s, right.second);
	    delete[] left.second;
	    delete[] right.second;
	    delete[] st.top().second;
	    st.top() = make_pair(precedence, s);
	    break;

	case COMMA:
	    right = st.top(); st.pop();
	    left = st.top(); st.pop();
	    s = new char[strlen(left.second) + strlen(right.second) + 3];
	    sprintf(s, "%s, %s", left.second, right.second);
	    st.push(make_pair(precedence, s));
	    break;

	case SYNC:
	    switch (first->value) {
	    case SYNC_QUE:
		s = new char[strlen(st.top().second) + 2];
		sprintf(s, "%s?", st.top().second);
		st.top().second = s;
		break;
	    case SYNC_BANG:
		s = new char[strlen(st.top().second) + 2];
		sprintf(s, "%s!", st.top().second);
		st.top().second = s;
		break;
	    case SYNC_TAU:
		s = new char[4];
		sprintf(s, "tau");
		st.push(make_pair(precedence, s));
		break;
	    }
	    break;

	case DEADLOCK:
	    st.push(make_pair(precedence, strcpy(new char[9], "deadlock")));
	    break;
	    
	default:
	    throw TypeException(unsupported);
	}

	++first;
    }
    return st.top().second;
}
