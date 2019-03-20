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

#include <iostream>
#include <vector>

#include "utap/utap.hh"
#include "utap/builder.hh"
#include <stdio.h>

using UTAP::ParserBuilder;
using UTAP::TypeSystem;
using UTAP::SymbolTable;
using UTAP::ErrorHandler;

using std::vector;
using std::cout;
using std::endl;

using namespace UTAP::Constants;

class MyParserBuilder : public ParserBuilder
{
  TypeSystem ts;
  SymbolTable st;


public:
    virtual void setErrorHandler(ErrorHandler *) {}

  virtual bool isType(const char*);

  /********************************************************************
   * Types
   */
  virtual void declArray(uint32_t);
  virtual void declType(uint32_t prefix, const char* name, bool range);
  				// 2 expr if range==true
  virtual void declStruct(uint32_t prefix, uint32_t n);
 				// n fields
  virtual void declField(const char* name, uint32_t dim); 
				// 1 type and dim array sizes
  virtual void declFieldEnd();
  virtual void declTypeDef(const char* name, uint32_t dim); 
				// 1 type and dim array sizes
  virtual void declTypeDefEnd();

  /********************************************************************
   * Variable declarations
   */
  virtual void declVar(const char* name, uint32_t dim, bool init); 
		// 1 type, dims, initializer if init==true
  virtual void declVarEnd();
  virtual void declInitialiserList(uint32_t num); // n initialisers
  virtual void declFieldInit(const char* name); // 1 initialiser
  
  /********************************************************************
   * Function declarations
   */
  virtual void declParameter(const char* name, bool reference, uint32_t dim);
		  // 1 type, dim array sizes
  virtual void declParameterEnd(); // pop 1 param type
  
  virtual void declFuncBegin(const char* name, uint32_t n); // n paramaters
  virtual void declFuncEnd(); // 1 block

  /********************************************************************
   * Process declarations
   */
  virtual void procBegin(const char* name, uint32_t n); // n parameters
  virtual void procEnd(); // 1 ProcBody
  virtual void procState(const char* name);
  virtual void procStateCommit(const char* name); // mark previously decl. state
  virtual void procStateUrgent(const char* name); // mark previously decl. state
  virtual void procStateInit(const char* name); // mark previously decl. state
  virtual void procTransition(const char* from, const char* to); 
					// 1 epxr,1sync,1expr
  virtual void procGuard() {}
  virtual void procSync(uint32_t type); // 1 expr
  virtual void procUpdate() {}

  /*********************************************************************
   * Statements
   */
  virtual void blockBegin();
  virtual void blockEnd();
  virtual void emptyStatement();
  virtual void forBegin();
  virtual void forEnd(); // 3 expr, 1 stat
  virtual void whileBegin();
  virtual void whileEnd(); // 1 expr, 1 stat
  virtual void doWhileBegin();
  virtual void doWhileEnd(); // 1 stat, 1 expr
  virtual void ifBegin();
  virtual void ifElse();
  virtual void ifEnd(bool); // 1 expr, n statements
  virtual void breakStatement();
  virtual void continueStatement();
  virtual void switchBegin();
  virtual void switchEnd(); // 1 expr, 1+ case/default
  virtual void caseBegin();
  virtual void caseEnd();  // 1 expr, 0+ stat
  virtual void defaultBegin();
  virtual void defaultEnd(); // 0+ statements
  virtual void exprStatement(); // 1 expr
  virtual void returnStatement(bool);

  /********************************************************************
   * Expressions
   */
  virtual void exprFalse();
  virtual void exprTrue();
  virtual void exprId(const char * varName);
  virtual void exprTypeName(const char* typeName);
  virtual void exprNat(int32_t); // natural number
  virtual void exprCall(const char * functionName, uint32_t n); // n exprs as arguments
  virtual void exprArray(); // 2 expr 
  virtual void exprPostIncrement(); // 1 expr
  virtual void exprPreIncrement(); // 1 expr
  virtual void exprPostDecrement(); // 1 expr
  virtual void exprPreDecrement(); // 1 expr
  virtual void exprAssignment(uint32_t op); // 2 expr
  virtual void exprUnary(uint32_t unaryop); // 1 expr
  virtual void exprBinary(uint32_t binaryop); // 2 expr
  virtual void exprInlineIf(); // 3 expr
  virtual void exprComma(); // 2 expr
  virtual void exprDot(const char *); // 1 expr
  virtual void exprDeadlock();

  /********************************************************************
   * System declaration
   */
  virtual void instantiation(const char* id, const char* templ, uint32_t n);
    // n expr
  virtual void process(const char*);
  virtual void done(); // marks the end of the file

  MyParserBuilder()
  {
    if (st.resolve("void")<0) 
      st.addSymbol("void", TypeSystem::NTYPE, NULL);
    if (st.resolve("clock")<0) 
      st.addSymbol("clock", TypeSystem::NTYPE, NULL);
    if (st.resolve("int")<0) 
      st.addSymbol("int", TypeSystem::NTYPE, NULL);
    if (st.resolve("chan")<0) 
      st.addSymbol("chan", TypeSystem::NTYPE, NULL);
  };
  ~MyParserBuilder() {}
};

/********************************************************************
 * Query functions
 */
bool MyParserBuilder::isType(const char* name)
{
  int s = st.resolve(name);
  if (s<0) return false;
  else return (st.getType(s) == TypeSystem::NTYPE);
};

/********************************************************************
 * Types
 */
void MyParserBuilder::declArray(uint32_t n)
{
  cout << "dim^" << n << " ";
}
void MyParserBuilder::declType(uint32_t prefix, const char* name, bool range)
{ // 2 expr if range==true
  cout << "type " << name;
  if (range) cout << "[]";
  cout << " ";
}

void MyParserBuilder::declStruct(uint32_t prefix, uint32_t fields)
{
  cout << "struct " << prefix << "(" << fields << " fields) ";
}

void MyParserBuilder::declField(const char* name, uint32_t dim)
{ // 1 type and dim array sizes
  cout << "field " << name << "^" << dim << " ";
}
void MyParserBuilder::declFieldEnd()
{
  cout << "fieldend" << endl;
}
void MyParserBuilder::declTypeDef(const char* name, uint32_t dim)
{ // 1 type and dim array sizes
  cout << "typedef " << name << "^" << dim << " ";
}
void MyParserBuilder::declTypeDefEnd()
{
  cout << "typedefend" << endl;
}

/********************************************************************
 * Variable declarations
 */
void MyParserBuilder::declVar(const char* name, uint32_t dim, bool init)
{ // 1 type, dims, initializer if init==true
  cout << "var " << name << "^" << dim << " ";
}
void MyParserBuilder::declVarEnd()
{
  cout << "varend" << endl;
}
void MyParserBuilder::declInitialiserList(uint32_t num)
{ // n initialisers
  cout << "initializer^" << num << " ";
}
void MyParserBuilder::declFieldInit(const char* name)
{ // 1 initialiser
  cout << "fieldinit " << name << " ";
}

/********************************************************************
 * Function declarations
 */
void MyParserBuilder::declParameter(const char* name, bool ref, uint32_t dim)
{ // 1 type + dim array sizes
  cout << "param " << name << "^" << dim << " ";
}
void MyParserBuilder::declParameterEnd()
{ // pop 1 parameter type
  cout << "paramEnd" << endl;
}

void MyParserBuilder::declFuncBegin(const char* name, uint32_t n)
{ // n paramaters
  cout << "func " << name << "(" << n << " params) ";
}
void MyParserBuilder::declFuncEnd()
{ // 1 block
  cout << "funcEnd" << endl;
}

/********************************************************************
 * Process declarations
 */
void MyParserBuilder::procBegin(const char* name, uint32_t n)
{ // n parameters
  cout << "process " << name << "(" << n << " params) {" << endl;
}
void MyParserBuilder::procEnd()
{ // 1 ProcBody
  cout << "}" << endl << endl;
}
void MyParserBuilder::procState(const char* name)
{ // 1 expr (invariant)
  cout << "state " << name << endl;
}
void MyParserBuilder::procStateCommit(const char* name)
{ // mark previously decl. state
  cout << "commit " << name << endl;
}
void MyParserBuilder::procStateUrgent(const char* name)
{ // mark previously decl. state
  cout << "urgent " << name << endl;
}
void MyParserBuilder::procStateInit(const char* name)
{ // mark previously decl. state
  cout << "init " << name << endl;
}
void MyParserBuilder::procTransition(const char* from, const char* to)
{ // 1 epxr,1sync,1expr
  cout << "trans " << from << "->" << to << endl;
}
void MyParserBuilder::procSync(uint32_t type)
{ // 1 expr
  cout << "{sync";
  if (type == SYNC_BANG) cout << "!";
  else if (type == SYNC_QUE) cout << "?";
  else cout << "*";
  cout << "} ";
}

/*********************************************************************
 * Statements
 */
void MyParserBuilder::blockBegin()
{
  cout << "{" << endl;
}
void MyParserBuilder::blockEnd()
{
  cout << "}" << endl;
}
void MyParserBuilder::emptyStatement()
{
  cout << "; ";
}

void MyParserBuilder::forBegin()
{
  cout << "for( ";
}

void MyParserBuilder::forEnd()
{ // 3 expr + 1 stat
  cout << "for)" << endl;
}

void MyParserBuilder::whileBegin()
{
  cout << "while( ";
}

void MyParserBuilder::whileEnd()
{ // 1 expr + 1 stat
  cout << "while)" << endl;
}
void MyParserBuilder::doWhileBegin()
{
  cout << "do( ";
}

void MyParserBuilder::doWhileEnd()
{ // 1 stat + 1 expr
  cout << "do) ";
}

void MyParserBuilder::ifBegin()
{
  cout << "if( ";
}

void MyParserBuilder::ifElse()
{
  cout << "else";
}

void MyParserBuilder::ifEnd(bool)
{ // 1 expr, n stat
  cout << "if) ";
}

void MyParserBuilder::breakStatement()
{
  cout << "break; ";
}
void MyParserBuilder::continueStatement()
{
  cout << "continue; ";
}
void MyParserBuilder::switchBegin()
{
  cout << "switch( ";
}

void MyParserBuilder::switchEnd()
{ // 1 expr + 1+ case/default
  cout << "switch) ";
}

void MyParserBuilder::caseBegin()
{
  cout << "case( ";
}

void MyParserBuilder::caseEnd()
{  // 1 expr + stat+
  cout << "case) ";
}

void MyParserBuilder::defaultBegin()
{
  cout << "default( ";
}

void MyParserBuilder::defaultEnd()
{ // 0+ statements
  cout << "default) ";
}

void MyParserBuilder::exprStatement()
{ // 1 expr
  cout << "expr ";
}

void MyParserBuilder::returnStatement(bool hasArgument)
{
  cout << "return(args=" << hasArgument << ") ";
}

/*********************************************************************
 * Expressions
 */

void MyParserBuilder::exprFalse()
{
  cout << "FALSE";
}

void MyParserBuilder::exprTrue()
{
  cout << "TRUE ";
}

void MyParserBuilder::exprId(const char* varName)
{
  cout << "exprId(" << varName << ") ";
}
void MyParserBuilder::exprTypeName(const char* typeName)
{
  cout << "type(" << typeName << ") ";
}

void MyParserBuilder::exprNat(int32_t n)
{ // natural number
  cout << "nat(" << n << ") ";
}

void MyParserBuilder::exprCall(const char* functionName, uint32_t n)
{ // n exprs as arguments
  cout << "fc(" << functionName << ","<< n << ") ";
}

void MyParserBuilder::exprArray()
{ // 2 expr 
  cout << "array ";
}

void MyParserBuilder::exprPostIncrement()
{ // 1 expr
  cout << "e++ ";
}

void MyParserBuilder::exprPreIncrement()
{ // 1 expr
  cout << "++e ";
}

void MyParserBuilder::exprPostDecrement()
{ // 1 expr
  cout << "e-- ";
}

void MyParserBuilder::exprPreDecrement()
{ // 1 expr
  cout << "--e ";
}

void MyParserBuilder::exprAssignment(uint32_t op)
{ // 2 expr
  cout << "e=e ";
}

void MyParserBuilder::exprUnary(uint32_t unaryop)
{ // 1 expr
  cout << "#e ";
}

void MyParserBuilder::exprBinary(uint32_t binaryop)
{ // 2 expr
  cout << "e#e ";
}

void MyParserBuilder::exprInlineIf()
{ // 3 expr
  cout << "?: ";
}

void MyParserBuilder::exprComma()
{ // 2 expr
  cout << "e, e ";
}

void MyParserBuilder::exprDot(const char *)
{ // 1 expr + 1 ID
  cout << "e.e ";
}

void MyParserBuilder::exprDeadlock()
{
    cout << "deadlock";
}

/*****************************************************************************
 *
 */
void MyParserBuilder::done()
{
}

void MyParserBuilder::process(const char *name)
{
  cout << "process(" << name << ")" << endl;
}

void MyParserBuilder::instantiation(const char *p, const char *t, uint32_t n)
{ // n parameters
  cout << p << " = " << t << "(" << n << " params);" << endl;
}

uint32_t filelength(FILE *file)
{
  uint32_t pos = ftell(file);
  fseek(file, 0, SEEK_END);
  uint32_t size = ftell(file);
  fseek(file, pos, SEEK_SET);
  return size;
}

int main(int argc, char**argv)
{
  MyParserBuilder pb;
  ErrorHandler handler;
  
  if (argc>=2) {
    if (strstr(argv[1], ".xml")) {
      FILE *file = fopen(argv[1],"r");
      if (file) {
	uint32_t size = filelength(file);
	char *buf = new char[size+1];
	if (buf) {
	  if (1 == fread(buf, size, 1, file)) {
	    buf[size] = 0;
	    int r = parseXMLBuffer(buf, &pb, &handler, false);
	    const vector<ErrorHandler::error_t> &errors = handler.getErrors();
	    vector<ErrorHandler::error_t>::const_iterator it;
	    for (it = errors.begin(); it != errors.end(); it++)
		cout << *it << endl;
	    return r;
	  } else {
	    printf("File read error\n");
	    return -1;
	  }
	} else {
	  printf("Not enough momory: %d needed to read file %s\n", size, argv[1]);
	  return -1;
	}
      } else { 
	printf("Could not open file: %s\n", argv[1]); 
	return -1; 
      }
    } else {
      FILE *file = fopen(argv[1], "r");
      parseXTA(file, &pb, &handler, true);
      fclose(file);
      const vector<ErrorHandler::error_t> &errors = handler.getErrors();
      vector<ErrorHandler::error_t>::const_iterator it;
      for (it = errors.begin(); it != errors.end(); it++)
	  cout << *it << endl;
      return 0;
    }
  } else {
    printf("Uppaal XML/XTA parser usage: %s file.ext\n", argv[0]);
    return 0;
  }
}
