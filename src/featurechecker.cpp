// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2020-2022 Aalborg University.
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
    visitFrame(document.get_globals().frame);
    if (document.has_dynamic_templates())
        supported_methods.symbolic = false;
    if (document.has_priority_declaration()){
        supported_methods.stochastic = false;
        supported_methods.concrete = false;
    }
}

bool FeatureChecker::visitTemplateBefore(template_t& templ)
{
    // Only check features if template is actually used in the system
    return templ.is_instantiated;
}

void FeatureChecker::visitVariable(variable_t& var)
{
    if (var.uid.get_type().is_clock() && !var.init.empty() && var.init.uses_fp())
        supported_methods.symbolic = false;
}

void FeatureChecker::visitEdge(edge_t& edge)
{
    visitAssignment(edge.assign);
    visitGuard(edge.guard);
}

void FeatureChecker::visitGuard(expression_t& guard)
{
    switch (guard.get_kind()) {
    case Constants::LT:
    case Constants::LE:
    case Constants::EQ:
        for (size_t i = 0; i < guard.get_size(); ++i) {
            if (guard.get(i).uses_fp())
                supported_methods.symbolic = false;
        }
    default: break;
    }
}

void FeatureChecker::visitAssignment(expression_t& ass)
{
    switch (ass.get_kind()) {
    case Constants::ASSIGN:
        if (ass.uses_fp() && !ass.uses_hybrid())
            supported_methods.symbolic = false;
        break;
    case Constants::COMMA:
        for (size_t i = 0; i < ass.get_size(); ++i)
            visitAssignment(ass.get(i));
        break;
    default: break;
    }
}

void FeatureChecker::visitLocation(location_t& location)
{
    const auto& invariant = location.invariant;
    if (invariant.empty())
        return;
    if (isRateDisallowedInSymbolic(invariant))
        supported_methods.symbolic = false;
}

/**
 * Checks whether an expression sets the rate of a clock
 * to something that is different from one or zero
 */
bool FeatureChecker::isRateDisallowedInSymbolic(const expression_t& e)
{
    if (e.get_kind() == Constants::EQ) {
        assert(e.get_size() >= 2);

        expression_t rate;
        expression_t clock;

        if (e.get(0).get_kind() == Constants::RATE) {
            clock = e.get(0);
            rate = e.get(1);
        } else if (e.get(1).get_kind() == Constants::RATE) {
            clock = e.get(1);
            rate = e.get(0);
        } else {
            return false;
        }

        // rates over hybrid clocks are allowed, because they are ignored/abstracted in symbolic analysis
        if (clock.get(0).get_symbol().get_type().is(Constants::HYBRID))
            return false;

        if (rate.get_kind() != Constants::CONSTANT)
            return false;
        if (rate.get_value() != 0 && rate.get_value() != 1)
            return true;  // NOLINT(readability-simplify-boolean-expr)

        return false;
    }

    if (e.get_kind() == Constants::AND) {
        for (size_t i = 0; i < e.get_size(); ++i) {
            if (isRateDisallowedInSymbolic(e.get(i)))
                return true;
        }
        return false;
    }
    return false;
}

void FeatureChecker::visitFrame(const frame_t& frame)
{
    for (size_t i = 0; i < frame.get_size(); ++i) {
        type_t t = frame.get_symbol(i).get_type();
        if (t.is_channel() && !t.is(Constants::BROADCAST))
            supported_methods.stochastic = false;
    }
}
