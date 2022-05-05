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

#ifndef UTAP_COMMON_HH
#define UTAP_COMMON_HH

namespace UTAP
{
    namespace Constants
    {
        enum kind_t {
            PLUS,
            MINUS,
            MULT,
            DIV,
            MOD,
            BIT_AND,
            BIT_OR,
            BIT_XOR,
            BIT_LSHIFT,
            BIT_RSHIFT,
            AND,
            OR,
            XOR,
            MIN,
            MAX,
            RATE,
            FRACTION,

            /********************************************************
             * Relational operators
             */
            LT,
            LE,
            EQ,
            NEQ,
            GE,
            GT,

            /********************************************************
             * Unary operators
             */
            NOT,
            FORALL,
            EXISTS,
            SUM,

            /********************************************************
             * Built-in functions
             */
            ABS_F,
            FABS_F,
            FMOD_F,
            FMA_F,
            FMAX_F,
            FMIN_F,
            FDIM_F,
            EXP_F,
            EXP2_F,
            EXPM1_F,
            LN_F,
            LOG_F,
            LOG10_F,
            LOG2_F,
            LOG1P_F,
            POW_F,
            SQRT_F,
            CBRT_F,
            HYPOT_F,
            SIN_F,
            COS_F,
            TAN_F,
            ASIN_F,
            ACOS_F,
            ATAN_F,
            ATAN2_F,
            SINH_F,
            COSH_F,
            TANH_F,
            ASINH_F,
            ACOSH_F,
            ATANH_F,
            ERF_F,
            ERFC_F,
            TGAMMA_F,
            LGAMMA_F,
            CEIL_F,
            FLOOR_F,
            TRUNC_F,
            ROUND_F,
            FINT_F,
            LDEXP_F,
            ILOGB_F,
            LOGB_F,
            NEXTAFTER_F,
            COPYSIGN_F,
            FPCLASSIFY_F,
            ISFINITE_F,
            ISINF_F,
            ISNAN_F,
            ISNORMAL_F,
            SIGNBIT_F,
            ISUNORDERED_F,
            RANDOM_F,
            RANDOM_ARCSINE_F,
            RANDOM_BETA_F,
            RANDOM_GAMMA_F,
            RANDOM_NORMAL_F,
            RANDOM_POISSON_F,
            RANDOM_TRI_F,
            RANDOM_WEIBULL_F,

            /********************************************************
             * Assignment operators
             */
            ASSIGN,
            ASSPLUS,
            ASSMINUS,
            ASSDIV,
            ASSMOD,
            ASSMULT,
            ASSAND,
            ASSOR,
            ASSXOR,
            ASSLSHIFT,
            ASSRSHIFT,

            /*******************************************************
             * CTL Quantifiers
             */
            EF,
            EG,
            AF,
            AG,
            LEADSTO,
            A_UNTIL,
            A_WEAKUNTIL,
            A_BUCHI,
            PMAX,
            PROBAMINBOX,
            PROBAMINDIAMOND,
            PROBABOX,
            PROBADIAMOND,
            PROBACMP,
            PROBAEXP,
            SIMULATE,
            SIMULATEREACH,
            BOX,
            DIAMOND,

            /*******************************************************
             * Control Synthesis Operator
             */
            CONTROL,
            PO_CONTROL,
            EF_CONTROL,
            CONTROL_TOPT,
            CONTROL_TOPT_DEF1,
            CONTROL_TOPT_DEF2,
            SMC_CONTROL,
            MIN_EXP,
            MAX_EXP,
            SAVE_STRAT,
            LOAD_STRAT,

            /*******************************************************
             * Get supremum or infimum of variables/clocks
             */
            SUP_VAR,
            INF_VAR,

            /*******************************************************
             * Verify a LSC scenario
             */
            SCENARIO,   // identifier of the LSC instance
            SCENARIO2,  // scenario property of size 2 "obsTA.lmin --> obsTA.lmax"

            /*******************************************************
             * Additional constants used by ExpressionProgram's and
             * the TypeCheckBuilder (but not by the parser, although
             * some of then ought to be used, FIXME).
             */
            // VARINDEX is only used during compilation when creating processes.
            // this is the *only* type to be sent as a ref for shorthand process
            // initialization or a spawn.
            VARINDEX,
            IDENTIFIER,
            CONSTANT,
            ARRAY,
            POSTINCREMENT,
            PREINCREMENT,
            POSTDECREMENT,
            PREDECREMENT,
            UNARY_MINUS,
            LIST,
            DOT,
            INLINEIF,
            COMMA,
            SYNC,
            DEADLOCK,
            FUNCALL,
            EFUNCALL,

            /*******************************************************
             * Types
             */
            UNKNOWN,
            VOID_TYPE,
            CLOCK,
            INT,
            DOUBLE,
            STRING,
            BOOL,
            SCALAR,
            LOCATION,
            LOCATION_EXPR,
            CHANNEL,
            COST,
            INVARIANT,
            INVARIANT_WR,
            GUARD,
            DIFF,
            CONSTRAINT,
            FORMULA,
            BRANCHPOINT,
            PROBABILITY,
            // LSC
            INSTANCELINE,
            MESSAGE,
            CONDITION,
            UPDATE,

            RANGE,
            LABEL,
            RECORD,
            REF,
            URGENT,
            COMMITTED,
            BROADCAST,
            HYBRID,
            TYPEDEF,
            PROCESS,
            PROCESSSET,
            INSTANCE,  // TA template (instantiated or not)
            SYSTEM_META,
            FUNCTION,
            EXTERNAL_FUNCTION,
            LSCINSTANCE,  // LSC template (instantiated or not)

            /******************************************************
             * MITL Extension
             */
            MITLFORMULA,
            MITLRELEASE,
            MITLUNTIL,
            MITLCONJ,
            MITLDISJ,
            MITLNEXT,
            MITLATOM,
            MITLEXISTS,
            MITLFORALL,
            /*Dynamic */
            SPAWN,
            EXIT,
            NUMOF,
            FORALLDYNAMIC,
            EXISTSDYNAMIC,
            SUMDYNAMIC,
            FOREACHDYNAMIC,
            DYNAMICEVAL,
            PROCESSVAR,
            DOUBLEINVGUARD,

        };

        /**********************************************************
         * Synchronisations:
         */
        enum synchronisation_t { SYNC_QUE, SYNC_BANG, SYNC_CSP };
    }  // namespace Constants

    /** Type for specifying which XTA part to parse (syntax switch) */
    enum xta_part_t {
        S_XTA,  // entire document
        S_DECLARATION,
        S_LOCAL_DECL,
        S_INST,
        S_SYSTEM,
        S_PARAMETERS,
        S_INVARIANT,
        S_EXPONENTIALRATE,
        S_SELECT,
        S_GUARD,
        S_SYNC,
        S_ASSIGN,
        S_EXPRESSION,
        S_EXPRESSION_LIST,
        S_PROPERTY,
        S_XTA_PROCESS,
        S_PROBABILITY,
        /*LSC*/ S_INSTANCELINE,
        S_MESSAGE,
        S_UPDATE,
        S_CONDITION
    };

}  // namespace UTAP

#endif
