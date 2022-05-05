// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2002-2006 Uppsala University and Aalborg University.

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

#include "utap/AbstractBuilder.hpp"

#include <vector>
#include <cinttypes>
#include <cstdarg>
#include <cstdio>

using namespace UTAP;

/*
void ParserBuilder::handleWarning(const char* msg, ...)
{
    char str[256];
    va_list ap;
    va_start(ap, msg);
    vsnprintf(str, 256, msg, ap);
    va_end(ap);

    handleWarning(std::string(str));
}

void ParserBuilder::handleError(const char* msg, ...)
{
    char str[256];
    va_list ap;
    va_start(ap, msg);
    vsnprintf(str, 256, msg, ap);
    va_end(ap);

    handleError(std::string(str));
}
*/

void AbstractBuilder::setPosition(uint32_t start, uint32_t end)
{
    position.start = start;
    position.end = end;
}

bool AbstractBuilder::isType(const char*) { return false; }

void AbstractBuilder::typeDuplicate() { throw NotSupportedException("typeDuplicate is not supported"); }

void AbstractBuilder::typePop() { throw NotSupportedException("typePop is not supported"); }

void AbstractBuilder::typeBool(PREFIX) { throw NotSupportedException("typeBool is not supported"); }

void AbstractBuilder::typeInt(PREFIX) { throw NotSupportedException("typeInt is not supported"); }

void AbstractBuilder::typeString(PREFIX) { throw NotSupportedException("typeString is not supported"); }

void AbstractBuilder::typeDouble(PREFIX) { throw NotSupportedException("typeDouble is not supported"); }

void AbstractBuilder::typeBoundedInt(PREFIX) { throw NotSupportedException("typeBoundedInt is not supported"); }

void AbstractBuilder::typeChannel(PREFIX) { throw NotSupportedException("typeChannel is not supported"); }

void AbstractBuilder::typeClock(PREFIX) { throw NotSupportedException("typeClock is not supported"); }

void AbstractBuilder::typeVoid() { throw NotSupportedException("typeVoid is not supported"); }

void AbstractBuilder::typeScalar(PREFIX) { throw NotSupportedException("typeScalar is not supported"); }

void AbstractBuilder::typeName(PREFIX, const char* name) { throw NotSupportedException("typeName is not supported"); }

void AbstractBuilder::typeStruct(PREFIX, uint32_t fields)
{
    throw NotSupportedException("typeStruct is not supported");
}

void AbstractBuilder::typeArrayOfSize(size_t) { throw NotSupportedException("typeArrayOfSize is not supported"); }

void AbstractBuilder::typeArrayOfType(size_t) { throw NotSupportedException("typeArrayOfType is not supported"); }

void AbstractBuilder::structField(const char* name) { throw NotSupportedException("structField is not supported"); }

void AbstractBuilder::declTypeDef(const char* name) { throw NotSupportedException("declTypeDef is not supported"); }

void AbstractBuilder::declVar(const char* name, bool init) { throw NotSupportedException("declVar is not supported"); }

void AbstractBuilder::declInitialiserList(uint32_t num)
{
    throw NotSupportedException("declInitialieserList is not supported");
}

void AbstractBuilder::declFieldInit(const char* name) { throw NotSupportedException("declFieldInit is not supported"); }

void AbstractBuilder::ganttDeclStart(const char* name)
{
    throw NotSupportedException("ganttDeclStart is not supported");
}

void AbstractBuilder::ganttDeclSelect(const char* id)
{
    throw NotSupportedException("ganttDeclSelect is not supported");
}

void AbstractBuilder::ganttDeclEnd() { throw NotSupportedException("ganttDeclEnd is not supported"); }

void AbstractBuilder::ganttEntryStart() { throw NotSupportedException("ganttStart is not supported"); }

void AbstractBuilder::ganttEntrySelect(const char* id)
{
    throw NotSupportedException("ganttEntrySelect is not supported");
}

void AbstractBuilder::ganttEntryEnd() { throw NotSupportedException("ganttEntryEnd is not supported"); }

void AbstractBuilder::declProgress(bool) { throw NotSupportedException("declProgress is not supported"); }

void AbstractBuilder::declParameter(const char* name, bool)
{
    throw NotSupportedException("declParameter is not supported");
}

void AbstractBuilder::declFuncBegin(const char* name) { throw NotSupportedException("declFuncBegin is not supported"); }

void AbstractBuilder::declFuncEnd() { throw NotSupportedException("declFuncEnd is not supported"); }

void AbstractBuilder::dynamicLoadLib(const char* name) { throw NotSupportedException("dynamicLoad is not supported"); }

void AbstractBuilder::declExternalFunc(const char* name, const char* alias)
{
    throw NotSupportedException("declExternalFunc is not supported");
}

void AbstractBuilder::procBegin(const char* name, const bool isTA, const std::string& type, const std::string& mode)
{
    throw NotSupportedException("lscProcBegin is not supported");
}

void AbstractBuilder::procEnd() { throw NotSupportedException("procEnd is not supported"); }

void AbstractBuilder::procState(const char* name, bool hasInvariant, bool hasER)
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

void AbstractBuilder::procStateInit(const char* name) { throw NotSupportedException("procStateInit is not supported"); }

void AbstractBuilder::procBranchpoint(const char* name)
{
    throw NotSupportedException("procBranchpoint is not supported");
}

void AbstractBuilder::procEdgeBegin(const char* from, const char* to, const bool control, const char* actname)

{
    throw NotSupportedException("procEdgeBegin is not supported");
}

void AbstractBuilder::procEdgeEnd(const char* from, const char* to)
{
    throw NotSupportedException("procEdgeEnd is not supported");
}

void AbstractBuilder::procSelect(const char* id) { throw NotSupportedException("procSelect is not supported"); }

void AbstractBuilder::procGuard() { throw NotSupportedException("procGuard is not supported"); }

void AbstractBuilder::procSync(Constants::synchronisation_t type)
{
    throw NotSupportedException("procSync is not supported");
}

void AbstractBuilder::procUpdate() { throw NotSupportedException("procUpdate is not supported"); }
void AbstractBuilder::procProb() { throw NotSupportedException("procProb is not supported"); }

// LSC
void AbstractBuilder::procMessage(Constants::synchronisation_t type)
{
    throw NotSupportedException("procMessage is not supported");
}

void AbstractBuilder::procInstanceLine() { throw NotSupportedException("procInstanceLine is not supported"); }

void AbstractBuilder::instanceNameBegin(const char* name)
{
    throw NotSupportedException("instanceNameBegin is not supported");
}

void AbstractBuilder::instanceNameEnd(const char* name, size_t arguments)
{
    throw NotSupportedException("instancNameEnd is not supported");
}

void AbstractBuilder::instanceName(const char* name, bool templ)
{
    throw NotSupportedException("instanceName is not supported");
}

void AbstractBuilder::procMessage(const char* from, const char* to, const int loc, const bool pch)
{
    throw NotSupportedException("procMessage is not supported");
}
void AbstractBuilder::procCondition(const std::vector<std::string>& anchors, const int loc, const bool pch,
                                    const bool hot)
{
    throw NotSupportedException("procCondition is not supported");
}
void AbstractBuilder::procCondition() { throw NotSupportedException("procCondition is not supported"); }
void AbstractBuilder::procLscUpdate(const char* anchor, const int loc, const bool pch)
{
    throw NotSupportedException("procLscUpdate is not supported");
}
void AbstractBuilder::procLscUpdate() { throw NotSupportedException("procLscUpdate is not supported"); }
void AbstractBuilder::hasPrechart(const bool pch) { throw NotSupportedException("hasPrechart is not supported"); }
// end LSC

void AbstractBuilder::blockBegin() { throw NotSupportedException("lscProcBegin is not supported"); }

void AbstractBuilder::blockEnd() { throw NotSupportedException("procEnd is not supported"); }

void AbstractBuilder::emptyStatement() { throw NotSupportedException("emptyStatement is not supported"); }

void AbstractBuilder::forBegin() { throw NotSupportedException("forBegin is not supported"); }

void AbstractBuilder::forEnd() { throw NotSupportedException("forEnd is not supported"); }

void AbstractBuilder::iterationBegin(const char* name)
{
    throw NotSupportedException("iterationBegin is not supported");
}

void AbstractBuilder::iterationEnd(const char* name) { throw NotSupportedException("iterationEnd is not supported"); }

void AbstractBuilder::whileBegin() { throw NotSupportedException("whileBegin is not supported"); }

void AbstractBuilder::whileEnd() { throw NotSupportedException("whileEnd is not supported"); }

void AbstractBuilder::doWhileBegin() { throw NotSupportedException("doWhileBegin is not supported"); }

void AbstractBuilder::doWhileEnd() { throw NotSupportedException("doWhileEnd is not supported"); }

void AbstractBuilder::ifBegin() { throw NotSupportedException("ifBegin is not supported"); }

void AbstractBuilder::ifCondition() { throw NotSupportedException("ifCondition is not supported"); }

void AbstractBuilder::ifThen() { throw NotSupportedException("ifThen is not supported"); }

void AbstractBuilder::ifEnd(bool) { throw NotSupportedException("ifThenElse is not supported"); }

void AbstractBuilder::breakStatement() { throw NotSupportedException("breakStatement is not supported"); }

void AbstractBuilder::continueStatement() { throw NotSupportedException("continueStatement is not supported"); }

void AbstractBuilder::switchBegin() { throw NotSupportedException("switchStatement is not supported"); }

void AbstractBuilder::switchEnd() { throw NotSupportedException("switchEnd is not supported"); }

void AbstractBuilder::caseBegin() { throw NotSupportedException("caseBegin is not supported"); }

void AbstractBuilder::caseEnd() { throw NotSupportedException("caseEnd is not supported"); }

void AbstractBuilder::defaultBegin() { throw NotSupportedException("defaultBegin is not supported"); }

void AbstractBuilder::defaultEnd() { throw NotSupportedException("defaultEnd is not supported"); }

void AbstractBuilder::exprStatement() { throw NotSupportedException("exprStatement is not supported"); }

void AbstractBuilder::returnStatement(bool) { throw NotSupportedException("returnStatement is not supported"); }

void AbstractBuilder::assertStatement() { throw NotSupportedException("assertStatement is not supported"); }

void AbstractBuilder::exprTrue() { throw NotSupportedException("exprTrue is not supported"); }

void AbstractBuilder::exprFalse() { throw NotSupportedException("exprFalse is not supported"); }

void AbstractBuilder::exprDouble(double) { throw NotSupportedException("exprDouble is not supported"); }

void AbstractBuilder::exprString(const char* name) { throw NotSupportedException("exprString is not supported"); }

void AbstractBuilder::exprId(const char* varName) { throw NotSupportedException("exprId is not supported"); }

void AbstractBuilder::exprNat(int32_t) { throw NotSupportedException("exprNar is not supported"); }

void AbstractBuilder::exprCallBegin() { throw NotSupportedException("exprCallBegin is not supported"); }

void AbstractBuilder::exprCallEnd(uint32_t n) { throw NotSupportedException("exprCallEnd is not supported"); }

void AbstractBuilder::exprArray() { throw NotSupportedException("exprArray is not supported"); }

void AbstractBuilder::exprPostIncrement() { throw NotSupportedException("exprPostIncrement is not supported"); }

void AbstractBuilder::exprPreIncrement() { throw NotSupportedException("exprPreIncrement is not supported"); }

void AbstractBuilder::exprPostDecrement() { throw NotSupportedException("exprPostDecrement is not supported"); }

void AbstractBuilder::exprPreDecrement() { throw NotSupportedException("exprPreDecrement is not supported"); }

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

void AbstractBuilder::exprNary(Constants::kind_t kind, uint32_t num)
{
    throw NotSupportedException("exprNary is not supported");
}

// LSC
void AbstractBuilder::exprScenario(const char* name) { throw NotSupportedException("exprScenario is not supported"); }
// end LSC

void AbstractBuilder::exprTernary(Constants::kind_t ternaryop, bool firstMissing)
{
    throw NotSupportedException("exprTernary is not supported");
}

void AbstractBuilder::exprInlineIf() { throw NotSupportedException("exprInlineIf is not supported"); }

void AbstractBuilder::exprComma() { throw NotSupportedException("exprComma is not supported"); }

void AbstractBuilder::exprLocation() { throw NotSupportedException("exprLocation is not supported"); }

void AbstractBuilder::exprDot(const char*) { throw NotSupportedException("exprDot is not supported"); }

void AbstractBuilder::exprDeadlock() { throw NotSupportedException("exprDeadlock is not supported"); }

void AbstractBuilder::exprForAllBegin(const char* name)
{
    throw NotSupportedException("exprForAllBegin is not supported");
}

void AbstractBuilder::exprForAllEnd(const char* name) { throw NotSupportedException("exprForAllEnd is not supported"); }

void AbstractBuilder::exprSumBegin(const char* name) { throw NotSupportedException("exprSumBegin is not supported"); }

void AbstractBuilder::exprSumEnd(const char* name) { throw NotSupportedException("exprSumEnd is not supported"); }

void AbstractBuilder::exprSimulate(int no_of_exprs, bool, int)
{
    throw NotSupportedException("exprSimulate is not supported");
}

void AbstractBuilder::exprBuiltinFunction1(Constants::kind_t)
{
    throw NotSupportedException("exprBuiltinFunction1 is not supported");
}

void AbstractBuilder::exprBuiltinFunction2(Constants::kind_t)
{
    throw NotSupportedException("exprBuiltinFunction2 is not supported");
}

void AbstractBuilder::exprBuiltinFunction3(Constants::kind_t)
{
    throw NotSupportedException("exprBuiltinFunction3 is not supported");
}

void AbstractBuilder::exprMinMaxExp(Constants::kind_t, PRICETYPE, Constants::kind_t)
{
    throw NotSupportedException("exprMinMaxExp is not supported");
}

void AbstractBuilder::exprLoadStrategy() { throw NotSupportedException("exprLoadStrategy is not supported"); }

void AbstractBuilder::exprSaveStrategy() { throw NotSupportedException("exprSaveStrategy is not supported"); }

void AbstractBuilder::exprMitlFormula() { throw NotSupportedException("exprMitlUntil is not supported"); }

void AbstractBuilder::exprMitlUntil(int, int) { throw NotSupportedException("exprMitlUntil is not supported"); }

void AbstractBuilder::exprMitlRelease(int, int) { throw NotSupportedException("exprMitlRelease is not supported"); }

void AbstractBuilder::exprMitlDisj() { throw NotSupportedException("exprMitlDisj is not supported"); }

void AbstractBuilder::exprMitlConj() { throw NotSupportedException("exprMitlConj is not supported"); }

void AbstractBuilder::exprMitlNext() { throw NotSupportedException("exprMitlNext is not supported"); }

void AbstractBuilder::exprMitlAtom() { throw NotSupportedException("exprMitlAtom is not supported"); }

void AbstractBuilder::exprOptimize(int, int, int, int) { throw NotSupportedException("exprOptimize is not supported"); }

void AbstractBuilder::exprProbaQualitative(Constants::kind_t, Constants::kind_t, double)
{
    throw NotSupportedException("exprProbaQualitative is not supported");
}

void AbstractBuilder::exprProbaQuantitative(Constants::kind_t)
{
    throw NotSupportedException("exprProbaQuantitative is not supported");
}

void AbstractBuilder::exprProbaCompare(Constants::kind_t, Constants::kind_t)
{
    throw NotSupportedException("exprProbaCompare is not supported");
}

void AbstractBuilder::exprProbaExpected(const char*)
{
    throw NotSupportedException("exprProbaExpected is not supported");
}

void AbstractBuilder::exprExistsBegin(const char* name)
{
    throw NotSupportedException("exprExistsBegin is not supported");
}

void AbstractBuilder::exprExistsEnd(const char* name) { throw NotSupportedException("exprExistsEnd is not supported"); }

void AbstractBuilder::instantiationBegin(const char*, size_t, const char*)
{
    throw NotSupportedException("instantiationBegin is not supported");
}

void AbstractBuilder::instantiationEnd(const char*, size_t, const char*, size_t)
{
    throw NotSupportedException("instantiationEnd is not supported");
}

void AbstractBuilder::process(const char*) { throw NotSupportedException("process is not supported"); }
void AbstractBuilder::processListEnd() { throw NotSupportedException("processListEnd is not supported"); }

// LSC
void AbstractBuilder::scenario(const char*) { throw NotSupportedException("scenario is not supported"); }

void AbstractBuilder::parse(const char*) { throw NotSupportedException("parse is not supported"); }
// end LSC

void AbstractBuilder::done() {}

void AbstractBuilder::handleExpect(const char* text){};

void AbstractBuilder::property() { throw NotSupportedException("property is not supported"); }

void AbstractBuilder::strategyDeclaration(const char*)
{
    throw NotSupportedException("strategyDeclaration is not supported");
}

void AbstractBuilder::subjection(const char*) { throw NotSupportedException("subjection is not supported"); }

void AbstractBuilder::imitation(const char*) { throw NotSupportedException("imitation is not supported"); }

void AbstractBuilder::beforeUpdate() { throw NotSupportedException("beforeUpdate is not supported"); }

void AbstractBuilder::afterUpdate() { throw NotSupportedException("afterUpdate is not supported"); }

void AbstractBuilder::beginChanPriority() { throw NotSupportedException("beginChanPriority is not supported"); }

void AbstractBuilder::addChanPriority(char separator)
{
    throw NotSupportedException("addChanPriority is not supported");
}

void AbstractBuilder::defaultChanPriority() { throw NotSupportedException("defaultChanPriority is not supported"); }

void AbstractBuilder::incProcPriority() { throw NotSupportedException("incProcPriority is not supported"); }

void AbstractBuilder::procPriority(const std::string&) { throw NotSupportedException("procPriority is not supported"); }

void AbstractBuilder::declDynamicTemplate(const std::string& name)
{
    throw NotSupportedException("declDynamicTemplate is not supported");
}

void AbstractBuilder::exprSpawn(int) { throw NotSupportedException("exprSpawn is not supported"); }

void AbstractBuilder::exprExit() { throw NotSupportedException("exprExit is not supported"); }

void AbstractBuilder::exprNumOf() { throw NotSupportedException("exprNumOf is not supported"); }

void AbstractBuilder::exprForAllDynamicBegin(const char*, const char*)
{
    throw NotSupportedException("exprForAllDynamicBegin is not supported");
}
void AbstractBuilder::exprForAllDynamicEnd(const char* name)
{
    throw NotSupportedException("exprForAllDynamicEnd is not supported");
}
void AbstractBuilder::exprExistsDynamicBegin(const char*, const char*)
{
    throw NotSupportedException("exprExistsAllDynamicBegin is not supported");
}

void AbstractBuilder::exprExistsDynamicEnd(const char* name)
{
    throw NotSupportedException("exprExistsAllDynamicEnd is not supported");
}
void AbstractBuilder::exprSumDynamicBegin(const char*, const char*)
{
    throw NotSupportedException("exprSumDynamicBegin is not supported");
}

void AbstractBuilder::exprSumDynamicEnd(const char* name)
{
    throw NotSupportedException("exprSumDynamicEnd is not supported");
}
void AbstractBuilder::exprForeachDynamicBegin(const char*, const char*)
{
    throw NotSupportedException("exprForeachDynamicBegin is not supported");
}

void AbstractBuilder::exprForeachDynamicEnd(const char* name)
{
    throw NotSupportedException("exprForeachDynamicEnd is not supported");
}
void AbstractBuilder::exprDynamicProcessExpr(const char*)
{
    throw NotSupportedException("exprDynamicProcessExpr is not supported");
}

void AbstractBuilder::exprMITLForAllDynamicBegin(const char*, const char*)
{
    throw NotSupportedException("exprMITLDynamicForAllBegin is not supported");
}

void AbstractBuilder::exprMITLForAllDynamicEnd(const char* name)
{
    throw NotSupportedException("exprMITLDynamicForAllEnd is not supported");
}
void AbstractBuilder::exprMITLExistsDynamicBegin(const char*, const char*)
{
    throw NotSupportedException("exprMITLDynamicExistsBegin is not supported");
}
void AbstractBuilder::exprMITLExistsDynamicEnd(const char* name)
{
    throw NotSupportedException("exprMITLDynamicExistsEnd is not supported");
}
void AbstractBuilder::queryBegin() { throw NotSupportedException("queryBegin not implemented is not supported"); }
void AbstractBuilder::queryEnd() { throw NotSupportedException("queryEnd is not supported"); }
void AbstractBuilder::queryFormula(const char*, const char*)
{
    throw NotSupportedException("queryFormula is not supported");
}
void AbstractBuilder::queryComment(const char*) { throw NotSupportedException("queryComment is not supported"); }
void AbstractBuilder::queryOptions(const char*, const char*)
{
    throw NotSupportedException("queryOption is not supported");
}
void AbstractBuilder::expectationBegin() { throw NotSupportedException("expectationBegin is not supported"); }
void AbstractBuilder::expectationEnd() { throw NotSupportedException("expectationEnd is not supported"); }
void AbstractBuilder::expectationValue(const char* type, const char* res, const char* value)
{
    throw NotSupportedException("expectationValue is not supported");
}
void AbstractBuilder::expectResource(const char*, const char*, const char*)
{
    throw NotSupportedException("expectResource is not supported");
}
void AbstractBuilder::queryResultsBegin() { throw NotSupportedException("queryResultsBegin is not supported"); }
void AbstractBuilder::queryResultsEnd() { throw NotSupportedException("queryResultsEnd is not supported"); }

void AbstractBuilder::modelOption(const char*, const char*)
{
    throw NotSupportedException("modelOption is not supported");
}
