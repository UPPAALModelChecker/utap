// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2020 Aalborg University.
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

#include "utap/featurechecker.h"

#include "utap/common.h"
#include "utap/document.h"

#include <cassert>

using namespace UTAP;

FeatureChecker::FeatureChecker(Document& document)
{
    document.accept(*this);
    visitFrame(document.getGlobals().frame);
    if (document.hasDynamicTemplates())
        supportedMethods.symbolic = false;
}

void FeatureChecker::visitEdge(edge_t& edge)
{
    visitAssignment(edge.assign);
    visitGuard(edge.guard);
}

void FeatureChecker::visitGuard(expression_t& guard)
{
    switch (guard.getKind()) {
    case Constants::LT:
    case Constants::LE:
    case Constants::EQ:
        for (size_t i = 0; i < guard.getSize(); ++i) {
            if (guard.get(i).usesFP())
                supportedMethods.symbolic = false;
        }
    default: break;
    }
}

void FeatureChecker::visitAssignment(expression_t& ass)
{
    switch (ass.getKind()) {
    case Constants::ASSIGN:
        if (ass.usesFP() && !ass.usesHybrid())
            supportedMethods.symbolic = false;
        break;
    case Constants::COMMA:
        for (size_t i = 0; i < ass.getSize(); ++i)
            visitAssignment(ass.get(i));
        break;
    default: break;
    }
}

void FeatureChecker::visitState(state_t& state)
{
    const auto& invariant = state.invariant;
    if (invariant.empty())
        return;
    if (isRateDisallowedInSymbolic(invariant))
        supportedMethods.symbolic = false;
}

/**
 * Checks whether an expression sets the rate of a clock
 * to something that is different from one or zero
 */
bool FeatureChecker::isRateDisallowedInSymbolic(const expression_t& e)
{
    if (e.getKind() == Constants::EQ) {
        assert(e.getSize() >= 2);

        expression_t rate;
        expression_t clock;

        if (e.get(0).getKind() == Constants::RATE) {
            clock = e.get(0);
            rate = e.get(1);
        } else if (e.get(1).getKind() == Constants::RATE) {
            clock = e.get(1);
            rate = e.get(0);
        } else {
            return false;
        }

        // rates over hybrid clocks are allowed, because they are ignored/abstracted in symbolic analysis
        if (clock.get(0).getSymbol().getType().is(Constants::HYBRID))
            return false;

        if (rate.getKind() != Constants::CONSTANT)
            return false;
        if (rate.getValue() != 0 && rate.getValue() != 1)
            return true;  // NOLINT(readability-simplify-boolean-expr)

        return false;
    }

    if (e.getKind() == Constants::AND) {
        for (size_t i = 0; i < e.getSize(); ++i) {
            if (isRateDisallowedInSymbolic(e.get(i)))
                return true;
        }
        return false;
    }
    return false;
}

void FeatureChecker::visitFrame(const frame_t& frame)
{
    for (size_t i = 0; i < frame.getSize(); ++i) {
        const type_t& t = frame.getSymbol(i).getType();
        if (t.isChannel() && !t.is(Constants::BROADCAST))
            supportedMethods.stochastic = false;
    }
}
