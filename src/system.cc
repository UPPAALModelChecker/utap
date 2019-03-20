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
#include <algorithm>
#include <stdio.h>

#include "utap/builder.hh"
#include "utap/system.hh"
#include "libparser.hh"

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
using std::set;

#define defaultIntMin -0x7FFF
#define defaultIntMax 0x7FFF

static const char *const unsupported
= "Internal error: Feature not supported in this mode.";
static const char *const invalid_type = "Invalid type";

TimedAutomataSystem::TimedAutomataSystem()
{
    current_template = &global;
    global.frame = frame_t::createFrame();
    global.frame.addSymbol("bool", type_t::createTypeName(type_t::createInteger(0, 1)));
    global.frame.addSymbol("int", type_t::createTypeName(type_t::INT));
    global.frame.addSymbol("chan", type_t::createTypeName(type_t::CHANNEL));
    global.frame.addSymbol("clock", type_t::createTypeName(type_t::CLOCK));
    addClock(type_t::CLOCK, "t(0)");
}

TimedAutomataSystem::~TimedAutomataSystem()
{

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

const set<int> &TimedAutomataSystem::getConstants() const
{
    return constants;
}

/** Creates and returns a new template. The template is created with
 *  the given name and parameters and added to the global frame. The
 *  new template is set to be the current template. The method does
 *  not check for duplicate declarations.
 */
TimedAutomataSystem::template_t &
TimedAutomataSystem::addTemplate(const char *name, frame_t params)
{
    int nr = templates.empty() ? 0 : templates.back().nr + 1;
    type_t type = type_t::createTemplate(params);
    templates.push_back(template_t());
    template_t &templ = templates.back();
    templ.uid = global.frame.addSymbol(name, type, &templ);
    templ.frame = frame_t::createFrame(global.frame);
    templ.frame.add(params);
    templ.nr = nr;
    setCurrentTemplate(templ);
    return templ;
}

TimedAutomataStructures::state_t &
TimedAutomataSystem::addLocation(const char *name, ExpressionProgram &inv)
{
    bool duplicate = current_template->frame.getIndexOf(name) != -1;
    
    current_template->states.push_back(state_t());
    state_t &state = current_template->states.back();
    state.uid = current_template->frame.addSymbol(name, type_t::LOCATION, &state);
    state.locNr = current_template->states.size() - 1;
    state.invariant = inv;

    if (duplicate) {	
	throw TypeException("Duplicate definition of %s", name);
    }

    return state;
}

TimedAutomataStructures::transition_t &
TimedAutomataSystem::addTransition(symbol_t src, symbol_t dst)
{
    list<transition_t> &trans = current_template->transitions;
    int nr = trans.empty() ? 0 : trans.back().nr + 1;
    trans.push_back(transition_t());
    trans.back().src = static_cast<state_t*>(src.getData());
    trans.back().dst = static_cast<state_t*>(dst.getData());
    trans.back().nr = nr;
    return trans.back();
}

TimedAutomataStructures::process_t &
TimedAutomataSystem::addInstance(symbol_t uid, template_t &templ)
{
    instances.push_back(process_t());
    instances.back().uid = uid;
    instances.back().templ = &templ;
    instances.back().nr = -1;
    uid.setData(&instances.back());
    uid.setType(type_t::createProcess(templ.frame));
    return instances.back();
}

void TimedAutomataSystem::addProcess(process_t &process)
{
    if (process.nr != -1)
	throw TypeException("Process appearing several times in system line");
    
    process.nr = processes.empty() ? 0 : processes.back().nr + 1;
    processes.push_back(process);
    process.uid.setData(&processes.back());
}

TimedAutomataSystem::template_t &TimedAutomataSystem::getCurrentTemplate()
{
    return *current_template;
}

void TimedAutomataSystem::setCurrentTemplate(template_t &value)
{
    current_template = &value;
}

int32_t TimedAutomataSystem::sizeOfType(type_t type)
{
    type_t base = type.getBase();
    if (base == type_t::CHANNEL || base == type_t::CLOCK || base == type_t::INT)
	return 1;
    if (base == type_t::ARRAY)
	return (type.getArraySize() * sizeOfType(type.getSub()));
    if (base == type_t::RECORD) {
	uint32_t sum = 0;
	frame_t frame = type.getRecordFields();
	for (uint32_t i = 0, size = frame.getSize(); i < size; i++)
	    sum += sizeOfType(frame[i].getType());
	return sum;
    }
    
    throw TypeException("BUG: Cannot compute size of this type");
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
    if (!evaluateExpression(expr, emptyMap, s))
	return false;
    if (s.size() != 1)
	return false;
    result = s.back();
    return true;
}

// Evaluate the expression. Use the mapping to assign meaning to
// identifiers. Constants not mapped by the given mapping are mapped
// to the value given by the initialiser. The result will be stored in
// the vector (the result cave have size bigger than one).
bool TimedAutomataSystem::evaluateExpression(
    const SubExpression &expr, map<int32_t, ExpressionProgram> &mapping,
    vector<int32_t> &s)
{
    type_t base;
    map<int32_t, ExpressionProgram>::iterator i;
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
	case MIN:
	case MAX:
	    right = s.back(); s.pop_back();
	    left = s.back(); s.pop_back();
	    s.push_back(evaluateBinary(left, first->kind, right));
	    break;

	case IDENTIFIER:
	    base = first->type.getBase();
	    if (base != type_t::ARRAY && base != type_t::INT
		&& base != type_t::RECORD)
	    {
		throw TypeException(unsupported);
	    }

	    i = mapping.find(first->value);
	    if (i == mapping.end()) {
		set<int32_t>::const_iterator j = constants.find(first->value);
		if (j == constants.end())
		    return false;
		constant_t *var = (constant_t *)symbol_t(*j).getData();
		if (!evaluateExpression(var->expr, mapping, s))
		    return false;
	    } else if (!evaluateExpression(i->second, mapping, s)) {
		return false;
	    }
	    break;
		
	case CONSTANT:
	    s.push_back(first->value);
	    break;

	case LIST:
	    // Nothing to do
	    break;
	    
	case ARRAY: {
	    type_t type = type_t(first->value); 
	    int index = s.back(); s.pop_back();
	    int size = type.getArraySize();
	    int subsize = sizeOfType(type.getSub());
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
	    // FIXME
	    int index = first->value;
	    ExpressionProgram::const_iterator str = first;
	    --str;
	    frame_t frame = str->type.getRecordFields();
	    int size = sizeOfType(frame[index].getType());
	    
	    // Delete data after index
	    int space = 0;
	    for (int i = frame.getSize() - 1; i > index; i--) 
		space += sizeOfType(frame[i].getType());
	    s.erase(s.end() - space, s.end());

	    // Delete data before index
	    space = 0;
	    for (int i = index - 1; i >= 0; i--)
		space += sizeOfType(frame[i].getType());
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
void TimedAutomataSystem::addClock(type_t type, const char *name)
{
    bool duplicate = current_template->frame.getIndexOf(name) != -1;
    
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
    clock->uid = current_template->frame.addSymbol(name, type, clock);
    clock->size = sizeOfType(type);
    clock->offset = offset;
    clock->global = (current_template == &global);

    if (duplicate)
	throw TypeException("Duplicate definition of identifier %s", name);
}

// Add an integer to current_template (which might be the "global"
// template)
void TimedAutomataSystem::addVariable(
    type_t type, const char *name, const ExpressionProgram &initial)
{
    bool duplicate = current_template->frame.getIndexOf(name) != -1;
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
    var->uid = current_template->frame.addSymbol(name, type, var);
    if (duplicate)
	throw TypeException("Duplicate definition of identifier %s", name);
}

void TimedAutomataSystem::addConstant(
    type_t type, const char *name, const ExpressionProgram &initial)
{
    bool duplicate = current_template->frame.getIndexOf(name) != -1;
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
    constant->uid = current_template->frame.addSymbol(name, type, constant);
    if (duplicate) 
	throw TypeException("Duplicate definition of identifier %s", name);

    constants.insert(constant->uid.getId());
}

// Add a channel to current_template (which might be the "global"
// template)
void TimedAutomataSystem::addChannel(type_t type, const char *name)
{
    bool duplicate = current_template->frame.getIndexOf(name) != -1;
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
    channel->uid = current_template->frame.addSymbol(name, type, channel);
    channel->size = sizeOfType(type);
    channel->offset = offset;
    channel->global = (current_template == &global);

    if (duplicate) 
	throw TypeException("Duplicate definition of identifier %s", name);
}

// Add a function to current_template (which might be the "global" template)
TimedAutomataSystem::function_t &
TimedAutomataSystem::addFunction(type_t type, const char *name)
{	
    bool duplicate = current_template->frame.getIndexOf(name) != -1;
    // Add function
    current_template->functions.push_back(function_t());
    function_t &fun = current_template->functions.back();
    fun.global = (current_template == &global);
    // Add symbol
    fun.uid = current_template->frame.addSymbol(name, type, &fun);
    if (duplicate) 
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

char *TimedAutomataSystem::expressionToString(const ExpressionProgram& expr,
					      bool old)
{
    return expressionToString(expr.begin(), expr.end(), old);
}

char *TimedAutomataSystem::expressionToString(const SubExpression& sub, 
					      bool old)
{
    return expressionToString(sub.begin(), sub.end(), old);
}

char *TimedAutomataSystem::expressionToString(
    ExpressionProgram::const_iterator first,
    ExpressionProgram::const_iterator last, bool old)
{
    typedef pair<int, char *> element_t;
    stack<element_t> st;

    while (first != last) {
	element_t left, right;
	const char *name;
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
		if (old)
		    strcat(s, " := ");
		else
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
	    name = symbol_t(first->value).getName();
	    s = strcpy(new char[strlen(name) + 1], name);
	    st.push(make_pair(precedence, s));
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
	    ExpressionProgram::const_iterator i = first;
	    --i;

	    if (i->type.getBase() == type_t::PROCESS) {
		name = symbol_t(first->value).getName();
	    } else if (i->type.getBase() == type_t::RECORD) {
		name = i->type.getRecordFields()[first->value].getName();
	    } else {
		throw TypeException("BUG: Unexpected type here");
	    }

	    s = new char[strlen(st.top().second) + 4 + strlen(name)];
	    if (precedence > st.top().first)
		sprintf(s, "(%s).%s", st.top().second, name);
	    else 
		sprintf(s, "%s.%s", st.top().second, name);
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

void TimedAutomataSystem::accept(SystemVisitor &visitor)
{
    visitor.visitSystemBefore(this);

    for_each(global.constants.begin(), global.constants.end(),
	     other_mem_fun(&visitor, &SystemVisitor::visitConstant));
    for_each(global.variables.begin(), global.variables.end(),
	     other_mem_fun(&visitor, &SystemVisitor::visitVariable));
    for_each(global.clocks.begin(), global.clocks.end(),
	     other_mem_fun(&visitor, &SystemVisitor::visitClock));
    for_each(global.channels.begin(), global.channels.end(),
	     other_mem_fun(&visitor, &SystemVisitor::visitChannel));
    for_each(global.functions.begin(), global.functions.end(),
	     other_mem_fun(&visitor, &SystemVisitor::visitFunction));

    list<template_t>::iterator i;
    for (i = templates.begin(); i != templates.end(); ++i) {
	if (!visitor.visitTemplateBefore(*i))
	    continue;
	for_each(i->constants.begin(), i->constants.end(),
		 other_mem_fun(&visitor, &SystemVisitor::visitConstant));
	for_each(i->variables.begin(), i->variables.end(),
		 other_mem_fun(&visitor, &SystemVisitor::visitVariable));
	for_each(i->clocks.begin(), i->clocks.end(),
		 other_mem_fun(&visitor, &SystemVisitor::visitClock));
	for_each(i->channels.begin(), i->channels.end(),
		 other_mem_fun(&visitor, &SystemVisitor::visitChannel));
	for_each(i->functions.begin(), i->functions.end(),
		 other_mem_fun(&visitor, &SystemVisitor::visitFunction));
	for_each(i->states.begin(), i->states.end(),
		 other_mem_fun(&visitor, &SystemVisitor::visitState));
	for_each(i->transitions.begin(), i->transitions.end(),
		 other_mem_fun(&visitor, &SystemVisitor::visitTransition));
	visitor.visitTemplateAfter(*i);
    }

    for_each(instances.begin(), instances.end(),
	     other_mem_fun(&visitor, &SystemVisitor::visitInstance));
    for_each(processes.begin(), processes.end(),
	     other_mem_fun(&visitor, &SystemVisitor::visitProcess));
	
    visitor.visitSystemAfter(this);
}

    
ContextVisitor::ContextVisitor(ErrorHandler *handler)
{
    errorHandler = handler;
    currentTemplate = -1;
    path[0] = 0;
}

void ContextVisitor::setContextNone()
{
    path[0] = 0;
}

void ContextVisitor::setContextDeclaration()
{
    if (currentTemplate == -1) {
	strncpy(path, "/nta/declaration", 256);
    } else {
	snprintf(path, 256, "/nta/template[%d]/declaration", currentTemplate + 1);
    }
}

void ContextVisitor::setContextParameters()
{
    snprintf(path, 256, "/nta/template[%d]/parameter", currentTemplate + 1);
}

void ContextVisitor::setContextInvariant(state_t &state)
{
    snprintf(path, 256, "/nta/template[%d]/location[%d]/label[@kind=\"invariant\"]", currentTemplate + 1, state.locNr + 1);
}

void ContextVisitor::setContextGuard(transition_t &transition)
{
    snprintf(path, 256, "/nta/template[%d]/transition[%d]/label[@kind=\"guard\"]", currentTemplate + 1, transition.nr + 1);
}

void ContextVisitor::setContextSync(transition_t &transition)
{
    snprintf(path, 256, "/nta/template[%d]/transition[%d]/label[@kind=\"synchronisation\"]", currentTemplate + 1, transition.nr + 1);
}

void ContextVisitor::setContextAssignment(transition_t &transition)
{
    snprintf(path, 256, "/nta/template[%d]/transition[%d]/label[@kind=\"assignment\"]", currentTemplate + 1, transition.nr + 1);
}

void ContextVisitor::setContextInstantiation()
{
    strncpy(path, "/nta/instantiation", 256);
}

bool ContextVisitor::visitTemplateBefore(template_t &templ)
{
    currentTemplate = templ.nr;
    return true;
}

void ContextVisitor::visitTemplateAfter(template_t &templ)
{
    currentTemplate = -1;
}

char *ContextVisitor::get() const
{
    return strcpy(new char[strlen(path) + 1], path);
}

void ContextVisitor::handleWarning(SubExpression expr, const char *msg)
{
    if (errorHandler) {
	errorHandler->setCurrentPath(this);	
	errorHandler->setCurrentPosition(expr.getPosition());
	errorHandler->handleWarning(msg);
    }
}

void ContextVisitor::handleError(SubExpression expr, const char *msg)
{
    if (errorHandler) {
	errorHandler->setCurrentPath(this);	
	errorHandler->setCurrentPosition(expr.getPosition());
	errorHandler->handleError(msg);
    }

}
