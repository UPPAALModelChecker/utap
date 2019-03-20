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

#include <vector>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cassert>
#include <inttypes.h>

#include "utap/abstractbuilder.h"

using namespace UTAP;

AbstractBuilder::AbstractBuilder()
{
}

void AbstractBuilder::setErrorHandler(ErrorHandler *value)
{
    errorHandler = value;
}

void AbstractBuilder::setPosition(const position_t &pos)
{
    position = pos;
}

bool AbstractBuilder::isType(const char*)
{
  return false;
}

bool AbstractBuilder::isLocation(const char*)
{
  return false;
}

void AbstractBuilder::typeName(int32_t prefix, const char* name, int range)
{
  throw NotSupportedException("typeName is not supported");
}

void AbstractBuilder::typeStruct(int32_t prefix, uint32_t fields)
{
  throw NotSupportedException("typeStruct is not supported");
}

void AbstractBuilder::structField(const char* name, uint32_t dim)
{
  throw NotSupportedException("structField is not supported");
}

void AbstractBuilder::structFieldEnd()
{
  throw NotSupportedException("structFieldEnd is not supported");
}

void AbstractBuilder::declTypeDef(const char* name, uint32_t dim)
{
  throw NotSupportedException("declTypeDef is not supported");
}

void AbstractBuilder::declTypeDefEnd()
{
  throw NotSupportedException("declTypeDefEnd is not supported");
}

void AbstractBuilder::declVar(const char* name, uint32_t dim, bool init)
{
  throw NotSupportedException("declVar is not supported");
}

void AbstractBuilder::declVarEnd()
{
  throw NotSupportedException("declVarEnd is not supported");
}

void AbstractBuilder::declInitialiserList(uint32_t num)
{
  throw NotSupportedException("declInitialieserList is not supported");
}

void AbstractBuilder::declFieldInit(const char* name)
{
  throw NotSupportedException("declFieldInit is not supported");
}

void AbstractBuilder::declParameter(const char* name, bool reference, uint32_t dim)
{
  throw NotSupportedException("declParameter is not supported");
}

void AbstractBuilder::declParameterEnd()
{
  throw NotSupportedException("declParameterEnd is not supported");
}
    
void AbstractBuilder::declFuncBegin(const char* name, uint32_t n)
{
  throw NotSupportedException("declFuncBegin is not supported");
}

void AbstractBuilder::declFuncEnd()
{
  throw NotSupportedException("declFuncEnd is not supported");
}

void AbstractBuilder::procBegin(const char* name, uint32_t n)
{
  throw NotSupportedException("procBegin is not supported");
}

void AbstractBuilder::procEnd()
{
  throw NotSupportedException("procEnd is not supported");
}

void AbstractBuilder::procState(const char* name, bool hasInvariant)
{
  throw NotSupportedException("procState is not supported");
}

void AbstractBuilder::procStateCommit(const char* name)
{
  throw NotSupportedException("procStateCommit is not supported");
}

void AbstractBuilder::procStateUrgent(const char* name)
{
  throw NotSupportedException("procStateUrgent is not supported");
}

void AbstractBuilder::procStateInit(const char* name)
{
  throw NotSupportedException("procStateInit is not supported");
}

void AbstractBuilder::procTransition(const char* from, const char* to)
{
  throw NotSupportedException("procTransition is not supported");
}
 
void AbstractBuilder::procGuard()
{
  throw NotSupportedException("procGuard is not supported");
}

void AbstractBuilder::procSync(Constants::synchronisation_t type)
{
  throw NotSupportedException("procSync is not supported");
}

void AbstractBuilder::procUpdate()
{
  throw NotSupportedException("procUpdate is not supported");
}
    
void AbstractBuilder::blockBegin()
{
  throw NotSupportedException("procBegin is not supported");
}

void AbstractBuilder::blockEnd()
{
  throw NotSupportedException("procEnd is not supported");
}

void AbstractBuilder::emptyStatement()
{
  throw NotSupportedException("emptyStatement is not supported");
}

void AbstractBuilder::forBegin()
{
  throw NotSupportedException("forBegin is not supported");
}

void AbstractBuilder::forEnd()
{
  throw NotSupportedException("forEnd is not supported");
}

void AbstractBuilder::whileBegin()
{
  throw NotSupportedException("whileBegin is not supported");
}

void AbstractBuilder::whileEnd()
{
  throw NotSupportedException("whileEnd is not supported");
}

void AbstractBuilder::doWhileBegin()
{
  throw NotSupportedException("doWhileBegin is not supported");
}

void AbstractBuilder::doWhileEnd()
{
  throw NotSupportedException("doWhileEnd is not supported");
}

void AbstractBuilder::ifBegin()
{
  throw NotSupportedException("ifBegin is not supported");
}

void AbstractBuilder::ifElse()
{
  throw NotSupportedException("ifElse is not supported");
}

void AbstractBuilder::ifEnd(bool)
{
  throw NotSupportedException("ifEnd is not supported");
}

void AbstractBuilder::breakStatement()
{
  throw NotSupportedException("breakStatement is not supported");
}

void AbstractBuilder::continueStatement()
{
  throw NotSupportedException("continueStatement is not supported");
}

void AbstractBuilder::switchBegin()
{
  throw NotSupportedException("switchStatement is not supported");
}

void AbstractBuilder::switchEnd()
{
  throw NotSupportedException("switchEnd is not supported");
}

void AbstractBuilder::caseBegin()
{
  throw NotSupportedException("caseBegin is not supported");

}

void AbstractBuilder::caseEnd()
{
  throw NotSupportedException("caseEnd is not supported");
}

void AbstractBuilder::defaultBegin()
{
  throw NotSupportedException("defaultBegin is not supported");
}

void AbstractBuilder::defaultEnd()
{
  throw NotSupportedException("defaultEnd is not supported");
}

void AbstractBuilder::exprStatement()
{
  throw NotSupportedException("exprStatement is not supported");
}

void AbstractBuilder::returnStatement(bool)
{
  throw NotSupportedException("returnStatement is not supported");
}
    
void AbstractBuilder::exprTrue()
{
  throw NotSupportedException("exprTrue is not supported");
}

void AbstractBuilder::exprFalse()
{
  throw NotSupportedException("exprFalse is not supported");
}

void AbstractBuilder::exprId(const char * varName)
{
  throw NotSupportedException("exprId is not supported");
}

void AbstractBuilder::exprNat(int32_t)
{
  throw NotSupportedException("exprNar is not supported");
}

void AbstractBuilder::exprCallBegin(const char * functionName)
{
  throw NotSupportedException("exprCallBegin is not supported");
}

void AbstractBuilder::exprCallEnd(uint32_t n)
{
  throw NotSupportedException("exprCallEnd is not supported");
}

void AbstractBuilder::exprArg(uint32_t n)
{
  throw NotSupportedException("exprArg is not supported");
}

void AbstractBuilder::exprArray()
{
  throw NotSupportedException("exprArray is not supported");
}

void AbstractBuilder::exprPostIncrement()
{
  throw NotSupportedException("exprPostIncrement is not supported");
}

void AbstractBuilder::exprPreIncrement()
{
  throw NotSupportedException("exprPreIncrement is not supported");
}

void AbstractBuilder::exprPostDecrement()
{
  throw NotSupportedException("exprPostDecrement is not supported");
}

void AbstractBuilder::exprPreDecrement()
{
  throw NotSupportedException("exprPreDecrement is not supported");
}

void AbstractBuilder::exprAssignment(Constants::kind_t op)
{
  throw NotSupportedException("exprAssignment is not supported");
}

void AbstractBuilder::exprUnary(Constants::kind_t unaryop)
{
  throw NotSupportedException("exprUnary is not supported");
}

void AbstractBuilder::exprBinary(Constants::kind_t binaryop)
{
  throw NotSupportedException("exprBinary is not supported");
}

void AbstractBuilder::exprInlineIf()
{
  throw NotSupportedException("exprInlineIf is not supported");
}

void AbstractBuilder::exprComma()
{
  throw NotSupportedException("exprComma is not supported");
}

void AbstractBuilder::exprDot(const char *)
{
  throw NotSupportedException("exprDot is not supported");
}

void AbstractBuilder::exprDeadlock()
{
  throw NotSupportedException("exprDeadlock is not supported");
}
    
void AbstractBuilder::instantiationBegin(const char*, const char*)
{
  throw NotSupportedException("instantiationBegin is not supported");
}

void AbstractBuilder::instantiationEnd(const char *, const char *, uint32_t n)
{
  throw NotSupportedException("instantiationEnd is not supported");
}

void AbstractBuilder::process(const char*)
{
  throw NotSupportedException("process is not supported");
}

void AbstractBuilder::done()
{
}

void AbstractBuilder::property(Constants::kind_t, int line)
{
  throw NotSupportedException("property");
}

void AbstractBuilder::beforeUpdate()
{
  throw NotSupportedException("beforeUpdate");
}

void AbstractBuilder::afterUpdate()
{
  throw NotSupportedException("afterUpdate");
}

void AbstractBuilder::lowPriority(const char*)
{
  throw NotSupportedException("afterUpdate");
}

void AbstractBuilder::samePriority(const char*)
{
  throw NotSupportedException("afterUpdate");
}

void AbstractBuilder::higherPriority(const char*)
{
  throw NotSupportedException("afterUpdate");
}
