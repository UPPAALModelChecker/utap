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

#ifndef UTAP_FEATURECHECKER_HH
#define UTAP_FEATURECHECKER_HH

#include "utap/document.h"
#include "utap/expression.h"
#include "utap/statement.h"

namespace UTAP
{
    class FeatureChecker : public SystemVisitor, public AbstractStatementVisitor
    {
    private:
        SupportedMethods supportedMethods{};

    public:
        explicit FeatureChecker(Document& document);
        SupportedMethods getSupportedMethods() { return supportedMethods; }

        void visitEdge(edge_t& edge) override;
        void visitAssignment(expression_t& ass);
        void visitGuard(expression_t& guard);
        void visitState(state_t& state) override;

        void visitFrame(const frame_t& frame);
        bool isRateDisallowedInSymbolic(const expression_t& e);
    };

};  // namespace UTAP

#endif /* UTAP_FEATURECHECKER_HH */
