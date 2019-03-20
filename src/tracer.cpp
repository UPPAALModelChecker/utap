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

#include <cstdio>
#include <climits>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <functional>

#include "utap/utap.h"

using namespace std;
using namespace UTAP;

/* The TA system.
 */
static TimedAutomataSystem ta;

/* For convenience we keep the size of the system here.
 */
static int processCount;
static int variableCount;
static int clockCount;

/* These are mappings from variable and clock indicies to
 * the names of these variables and clocks.
 */
static vector<string> clocks;
static vector<string> variables;

/* A bound for a clock constraint. A bound consists of a value and a
 * bit indicating whether the bound is strict or not.
 */
struct bound_t
{
    int value   : 31; // The value of the bound
    bool strict : 1;  // True if the bound is strict
};

/* The bound (infinity, <).
 */
static bound_t infinity = { INT_MAX >> 1, 1 };

/* The bound (0, <=).
 */
static bound_t zero = { 0, 0 };

/* Returns the ith element of a list. 
 */
template<class T>
const T &ith(const list<T> &collection, int i)
{
    typename list<T>::const_iterator element = collection.begin();
    while (i--) 
    {
	element++;
    }
    return *element;
}

/* Adds another variable to a vector of variable names.  The final
 * variable name is composed of a prefix and a name. In case of arrays
 * a list containing the size of each dimension can be provided.
 */
void addVariable(vector<string> &variables, 
		 string prefix, string name, 
		 list<int> &dimensions)
{
    char buf[128];
    switch (dimensions.size()) 
    {
    case 0:
	variables.push_back(prefix + name);
	break;
    case 1:
	for (int i = 0; i < dimensions.front(); i++) 
	{
	    snprintf(buf, 128, "%s%s[%d]", prefix.c_str(), name.c_str(), i);
	    variables.push_back(buf);
	}
	break;
    default:
	snprintf(buf, 128, "%s[%d]", name.c_str(), dimensions.front());
	dimensions.pop_front();
	addVariable(variables, prefix, buf, dimensions);
	break;
    }
}

/* Adds a variable to either the global variables or the global clocks
 * arrays, depending on the type of the variable.  The variable name
 * will be prefixed with the given string.
 */
void analyzeVariable(process_t *process, const variable_t variable)
{
    type_t type = variable.uid.getType();
    type_t base = type.getBase();
    if (!type.hasPrefix(UTAP::prefix::CONSTANT)) 
    {
	int size = 1;
	list<int> dimensions;
	string prefix;

	/* Process local variables are prefixed with the process name.
	 */
	if (process)
	{
	    prefix = string(process->uid.getName()) + ".";
	}

	/* If the variable is an array we need to find the dimensions
	 * and the base type.
	 */
	if (base == type_t::ARRAY) 
	{
	    /* An interpreter is needed to evaluate the array size of
	     * each dimension.  If the variable is a process local
	     * variable, then we also need to take the arguments to
	     * that process into account.
	     */
	    Interpreter interpreter(ta.getConstantValuation());
	    if (process)
	    {
		interpreter.addValuation(process->mapping);
	    }

	    /* Evaluate the size of each dimension and append it
	     * to the dimension list.
	     */
	    do {
		int value = interpreter.evaluate(type.getArraySize());
		size *= value;
		dimensions.push_back(value);
		type = type.getSub();
		base = type.getBase();
	    } while (base == type_t::ARRAY);
	} 
    
	if (base == type_t::CLOCK) 
	{
	    clockCount += size;
	    addVariable(clocks, prefix, variable.uid.getName(), dimensions);
	}
	else if (base == type_t::INT || base == type_t::BOOL) 
	{
	    variableCount += size;
	    addVariable(variables, prefix, variable.uid.getName(), dimensions);
	}
    }
}


/* A symbolic state. A symbolic state consists of a location vector, a
 * variable vector and a zone describing the possible values of the
 * clocks in a symbolic manner.
 */
class State
{
public:
    State();
    State(FILE *);
    ~State();
    
    int &getLocation(int i)              { return locations[i]; }
    int &getVariable(int i)              { return integers[i]; }
    bound_t &getConstraint(int i, int j) { return dbm[i * clockCount + j]; }

    int getLocation(int i) const              { return locations[i]; }
    int getVariable(int i) const              { return integers[i]; }
    bound_t getConstraint(int i, int j) const { return dbm[i * clockCount + j]; }
private:
    int *locations;
    int *integers;
    bound_t *dbm;
    void allocate();
};

State::~State()
{
    delete[] dbm;
    delete[] integers;
    delete[] locations;
}

State::State(FILE *file)
{
    allocate();

    /* Read locations.
     */
    for (int i = 0; i < processCount; i++)
    {
	fscanf(file, "%d\n", &getLocation(i));
    }
    fscanf(file, ".\n");

    /* Read DBM.
     */
    int i, j, bnd;
    while (fscanf(file, "%d\n%d\n%d\n.\n", &i, &j, &bnd) == 3)
    {
	getConstraint(i, j).value = bnd >> 1;
	getConstraint(i, j).strict = bnd & 1;
    }
    fscanf(file, ".\n");    

    /* Read integers.
     */
    for (int i = 0; i < variableCount; i++) 
    {
	fscanf(file, "%d\n", &getVariable(i));
    }
    fscanf(file, ".\n");
}

void State::allocate()
{
    /* Allocate/
     */
    locations = new int[processCount];
    integers = new int[variableCount];
    dbm = new bound_t[clockCount * clockCount];
    
    /* Fill with default values.
     */
    fill(locations, locations + processCount, 0);
    fill(integers, integers + variableCount, 0);
    fill(dbm, dbm + clockCount * clockCount, infinity);

    /* Set diagonal and lower bounds to zero.
     */
    for (int i = 0; i < clockCount; i++) 
    {
	getConstraint(0, i) = zero;
	getConstraint(i, i) = zero;
    }
}

/* A transtion consists of one or more edges. Edges are indexes
 * from 0 in the order they appear in the input file.
 */
class Transition
{
public:
    Transition(FILE *);
    ~Transition();

    int getEdge(int32_t process) const { return edges[process]; }
private:
    int *edges;
};

Transition::Transition(FILE *file)
{
    edges = new int[processCount];
    fill(edges, edges + processCount, -1);

    int process, edge;
    while (fscanf(file, "%d %d.\n", &process, &edge) == 2) 
    {
	edges[process] = edge - 1;
    }
    fscanf(file, ".\n");
}

Transition::~Transition()
{
    delete[] edges;
}

/* Output operator for a symbolic state. Prints the location vector,
 * the variables and the zone of the symbolic state.
 */
ostream &operator << (ostream &o, const State &state)
{
    int i, j;

    /* Print location vector.
     */
    const list<process_t> &processes = ta.getProcesses();
    list<process_t>::const_iterator process = processes.begin();
    i = 0;
    while (process != processes.end()) 
    {
	cout << process->uid.getName() << '.'
	     << ith(process->templ->states, state.getLocation(i)).uid.getName() 
	     << " ";
	process++;
	i++;
    }

    /* Print variables.
     */
    for (i = 0; i < variableCount; i++) 
    {
	cout << variables[i] << " = " << state.getVariable(i) << ' ';
    }
  
    /* Print clocks.
     */
    for (i = 0; i < clockCount; i++) 
    {
	for (j = 0; j < clockCount; j++) 
	{
	    if (i != j) 
	    {
		bound_t bnd = state.getConstraint(i, j);

		if (bnd.value != infinity.value) 
		{
		    cout << clocks[i] << "-" << clocks[j] 
			 << (bnd.strict ? "<" : "<=") << bnd.value << " ";
		}
	    }
	}
    }
  
    return o;
}

/* Output operator for a transition. Prints all edges in the
 * transition including the source, destination, guard,
 * synchronisation and assignment.
 */
ostream &operator << (ostream &o, const Transition &t)
{
    for (int i = 0; i < processCount; i++) 
    {
	int idx = t.getEdge(i);
	if (idx > -1) 
	{
	    const process_t &process = ith(ta.getProcesses(), i);
	    const edge_t &edge = ith(process.templ->edges, idx);
      
	    cout << process.uid.getName() << '.' << edge.src->uid.getName() 
		 << " -> "
		 << process.uid.getName() << '.' << edge.dst->uid.getName() 
		 << " {"
		 << edge.guard << "; " << edge.sync << "; " << edge.assign
		 << ";} ";
	}
    }

    return o;
}

/* Read and print a trace file.
 */
void loadTrace(const char *trace)
{
    /* Open file.
     */
    FILE *file = fopen(trace, "r");

    /* Read and print trace.
     */
    cout << "State: " << State(file) << endl;
    for (;;) 
    {
	int c;
	/* Skip white space.
	 */
	do {
	    c = fgetc(file);
	} while (isspace(c));

	/* A dot terminates the trace.
	 */
	if (c == '.') 
	{
	    break;
	}

	/* Put the character back into the stream.
	 */
	ungetc(c, file);

	/* Read a state and a transition.
	 */
	State state(file);
	Transition transition(file);

	/* Print transition and state.
	 */
	cout << endl << "Transition: " << transition << endl
	     << endl << "State: " << state << endl;
    }

    /* Close the file.
     */
    fclose(file);
}

/* Read model (in XML format) into global variables (see the top of
 * this file for a description of those variables).
 */
void loadModel(const char *model)
{
    UTAP::ErrorHandler errors;

    /* Parse file.
     */
    parseXMLFile(model, &errors, &ta, false);

    /* Abort in case of errors.
     */
    if (errors.hasErrors()) 
    {
	cerr << "Syntax errors in model" << endl;
	exit(1);
    }

    /* Add the variables of the model to the clocks and variables
     * vectors and set the processCount, variableCount and clockCount
     * variables (all defined globally).
     */
    const list<process_t> &processes = ta.getProcesses();
    processCount = processes.size();

    /* First the global variables and clocks.
     */
    for_each(ta.getGlobals().variables.begin(),
	     ta.getGlobals().variables.end(),
	     bind1st(ptr_fun(analyzeVariable), (process_t*)NULL));

    /* Then the local variables and clocks.
     */
    list<process_t>::const_iterator process;
    for (process = processes.begin(); process != processes.end(); ++process) 
    {
	for_each(process->templ->variables.begin(),
		 process->templ->variables.end(),
		 bind1st(ptr_fun(analyzeVariable), &*process));
    }
}

int main(int argc, char *argv[])
{
    try 
    {
	if (argc < 3) 
	{
	    printf("Synopsis: %s <model> <trace>\n", argv[0]);
	    exit(1);
	}
	loadModel(argv[1]);
	loadTrace(argv[2]);
    }
    catch (exception &e)
    {
	cerr << "Catched exception: " << e.what() << endl;
    }
}
