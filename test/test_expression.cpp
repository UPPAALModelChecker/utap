#include "utap/expression.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

TEST_CASE("Expression")
{
    using UTAP::type_t;
    using exp_t = UTAP::expression_t;
    const auto i_prim_type = type_t::createPrimitive(UTAP::Constants::INT);
    REQUIRE(i_prim_type.getKind() == UTAP::Constants::INT);
    const auto d_prim_type = type_t::createPrimitive(UTAP::Constants::DOUBLE);
    REQUIRE(d_prim_type.getKind() == UTAP::Constants::DOUBLE);

    const auto i0 = exp_t::createConstant(0);
    REQUIRE(i0.getKind() == UTAP::Constants::CONSTANT);
    const auto i2 = exp_t::createConstant(2);
    REQUIRE(i2.getKind() == UTAP::Constants::CONSTANT);
    CHECK(i2.getType().getKind() == UTAP::Constants::INT);
    CHECK(i2.getValue() == 2);
    const auto i5 = exp_t::createConstant(5);
    REQUIRE(i5.getKind() == UTAP::Constants::CONSTANT);
    CHECK(i5.getType().getKind() == UTAP::Constants::INT);
    CHECK(i5.getValue() == 5);
    const auto d3 = exp_t::createDouble(3.0);
    REQUIRE(d3.getKind() == UTAP::Constants::CONSTANT);
    CHECK(d3.getType().getKind() == UTAP::Constants::DOUBLE);
    CHECK(d3.getDoubleValue() == 3.0);
    const auto d1_2 = exp_t::createDouble(0.5);
    REQUIRE(d1_2.getKind() == UTAP::Constants::CONSTANT);
    CHECK(d1_2.getType().getKind() == UTAP::Constants::DOUBLE);
    CHECK(d1_2.getDoubleValue() == 0.5);

    SUBCASE("Types")
    {
        const auto i02 = type_t::createRange(i_prim_type, i0, i2);
        REQUIRE(i02.getKind() == UTAP::Constants::RANGE);
        const auto i02_range = i02.getRange();
        CHECK(i02_range.first == i0);
        CHECK(i02_range.second == i2);
        const auto i25 = type_t::createRange(i_prim_type, i2, i5);
        REQUIRE(i25.getKind() == UTAP::Constants::RANGE);
        const auto i25_range = i25.getRange();
        CHECK(i25_range.first == i2);
        CHECK(i25_range.second == i5);
        const auto i52 = type_t::createRange(i_prim_type, i5, i2);  // no checks
    }

    SUBCASE("Operator precedence")
    {
        using namespace UTAP::Constants;
        // Follow table at https://en.cppreference.com/w/cpp/language/operator_precedence
        REQUIRE(exp_t::getPrecedence(POSTINCREMENT) == exp_t::getPrecedence(POSTDECREMENT));
        REQUIRE(exp_t::getPrecedence(POSTINCREMENT) >= exp_t::getPrecedence(FUNCALL));
        REQUIRE(exp_t::getPrecedence(FUNCALL) >= exp_t::getPrecedence(ARRAY));
        REQUIRE(exp_t::getPrecedence(ARRAY) >= exp_t::getPrecedence(DOT));
        REQUIRE(exp_t::getPrecedence(DOT) >= exp_t::getPrecedence(RATE));
        REQUIRE(exp_t::getPrecedence(RATE) > exp_t::getPrecedence(PREINCREMENT));
        REQUIRE(exp_t::getPrecedence(PREINCREMENT) == exp_t::getPrecedence(PREDECREMENT));
        REQUIRE(exp_t::getPrecedence(PREINCREMENT) >= exp_t::getPrecedence(UNARY_MINUS));
        REQUIRE(exp_t::getPrecedence(UNARY_MINUS) >= exp_t::getPrecedence(NOT));
        REQUIRE(exp_t::getPrecedence(NOT) > exp_t::getPrecedence(POW));
        REQUIRE(exp_t::getPrecedence(POW) > exp_t::getPrecedence(MULT));
        REQUIRE(exp_t::getPrecedence(MULT) == exp_t::getPrecedence(DIV));
        REQUIRE(exp_t::getPrecedence(MULT) == exp_t::getPrecedence(MOD));
        REQUIRE(exp_t::getPrecedence(MULT) > exp_t::getPrecedence(PLUS));
        REQUIRE(exp_t::getPrecedence(PLUS) == exp_t::getPrecedence(MINUS));
        REQUIRE(exp_t::getPrecedence(PLUS) > exp_t::getPrecedence(BIT_LSHIFT));
        REQUIRE(exp_t::getPrecedence(BIT_LSHIFT) == exp_t::getPrecedence(BIT_RSHIFT));
        REQUIRE(exp_t::getPrecedence(BIT_LSHIFT) > exp_t::getPrecedence(LT));
        REQUIRE(exp_t::getPrecedence(LT) == exp_t::getPrecedence(LE));
        REQUIRE(exp_t::getPrecedence(LT) == exp_t::getPrecedence(GT));
        REQUIRE(exp_t::getPrecedence(LT) == exp_t::getPrecedence(GE));
        REQUIRE(exp_t::getPrecedence(LT) > exp_t::getPrecedence(EQ));
        REQUIRE(exp_t::getPrecedence(EQ) == exp_t::getPrecedence(NEQ));
        REQUIRE(exp_t::getPrecedence(NEQ) > exp_t::getPrecedence(BIT_AND));
        REQUIRE(exp_t::getPrecedence(BIT_AND) > exp_t::getPrecedence(BIT_XOR));
        REQUIRE(exp_t::getPrecedence(BIT_XOR) > exp_t::getPrecedence(BIT_OR));
        REQUIRE(exp_t::getPrecedence(BIT_OR) > exp_t::getPrecedence(AND));
        REQUIRE(exp_t::getPrecedence(AND) > exp_t::getPrecedence(OR));
        REQUIRE(exp_t::getPrecedence(AND) > exp_t::getPrecedence(ASSIGN));
        REQUIRE(exp_t::getPrecedence(ASSIGN) == exp_t::getPrecedence(ASSPLUS));
        REQUIRE(exp_t::getPrecedence(ASSIGN) == exp_t::getPrecedence(ASSMINUS));
        REQUIRE(exp_t::getPrecedence(ASSIGN) == exp_t::getPrecedence(ASSMULT));
        REQUIRE(exp_t::getPrecedence(ASSIGN) == exp_t::getPrecedence(ASSDIV));
        REQUIRE(exp_t::getPrecedence(ASSIGN) == exp_t::getPrecedence(ASSMOD));
        REQUIRE(exp_t::getPrecedence(ASSIGN) == exp_t::getPrecedence(ASSLSHIFT));
        REQUIRE(exp_t::getPrecedence(ASSIGN) == exp_t::getPrecedence(ASSRSHIFT));
        REQUIRE(exp_t::getPrecedence(ASSIGN) == exp_t::getPrecedence(ASSAND));
        REQUIRE(exp_t::getPrecedence(ASSIGN) == exp_t::getPrecedence(ASSOR));
        REQUIRE(exp_t::getPrecedence(ASSIGN) == exp_t::getPrecedence(ASSXOR));
        REQUIRE(exp_t::getPrecedence(ASSIGN) > exp_t::getPrecedence(COMMA));
    }

    SUBCASE("Unary")
    {
        using namespace UTAP::Constants;
        const auto ops = {// clang-format off
            UNARY_MINUS, NOT, DOT, /*SYNC,*/ PREINCREMENT, POSTINCREMENT, PREDECREMENT, POSTDECREMENT,
            RATE, ABS_F, FABS_F, EXP_F, EXP2_F, EXPM1_F, LN_F, LOG_F, LOG10_F, LOG2_F, LOG1P_F, SQRT_F,
            CBRT_F, SIN_F, COS_F, TAN_F, ASIN_F, ACOS_F, ATAN_F, SINH_F, COSH_F, TANH_F, ASINH_F,
            ACOSH_F, ATANH_F, ERF_F, ERFC_F, TGAMMA_F, LGAMMA_F, CEIL_F, FLOOR_F, TRUNC_F, ROUND_F,
            FINT_F, ILOGB_F, LOGB_F, FPCLASSIFY_F, ISFINITE_F, ISINF_F, ISNAN_F, ISNORMAL_F,
            SIGNBIT_F, ISUNORDERED_F, RANDOM_F, RANDOM_POISSON_F
        };  // clang-format on
        for (const auto& op : ops) {
            REQUIRE(exp_t::getPrecedence(op) > 0);
            const auto op_i0 = exp_t::createUnary(op, i0);
            CHECK(op_i0.getKind() == op);
            REQUIRE(op_i0.getSize() == 1);
            CHECK(op_i0.get(0) == i0);
            const auto op_i2 = exp_t::createUnary(op, i2);
            CHECK(op_i2.getKind() == op);
            REQUIRE(op_i2.getSize() == 1);
            CHECK(op_i2.get(0) == i2);
            const auto op_d3 = exp_t::createUnary(op, d3);
            CHECK(op_d3.getKind() == op);
            REQUIRE(op_d3.getSize() == 1);
            CHECK(op_d3.get(0) == d3);
            const auto op_d1_2 = exp_t::createUnary(op, d1_2);
            CHECK(op_d1_2.getKind() == op);
            REQUIRE(op_d1_2.getSize() == 1);
            CHECK(op_d1_2.get(0) == d1_2);
        }
    }
    SUBCASE("Binary")
    {
        using namespace UTAP::Constants;
        const auto ops = {
            // clang-format off
            MINUS, PLUS, MULT, DIV, MOD, BIT_AND, BIT_OR, BIT_XOR, BIT_LSHIFT, BIT_RSHIFT,
            AND, OR, XOR, POW, LT, LE, EQ, NEQ, GE, GT, MIN, MAX, ARRAY, COMMA,
            ASSIGN, ASSPLUS, ASSMINUS, ASSDIV, ASSMOD, ASSMULT, ASSAND, ASSOR, ASSXOR,
            ASSLSHIFT, ASSRSHIFT, FORALL, EXISTS, SUM, SUP_VAR, INF_VAR, FRACTION,
            FMOD_F, FMAX_F, FMIN_F, FDIM_F, POW_F, HYPOT_F, ATAN2_F, LDEXP_F, NEXTAFTER_F, COPYSIGN_F,
            RANDOM_ARCSINE_F, RANDOM_BETA_F, RANDOM_GAMMA_F, RANDOM_NORMAL_F, RANDOM_WEIBULL_F,
        };  // clang-format on
        for (const auto& op : ops) {
            REQUIRE(exp_t::getPrecedence(op) > 0);
            const auto op_i25 = exp_t::createBinary(op, i2, i5);
            CHECK(op_i25.getKind() == op);
            REQUIRE(op_i25.getSize() == 2);
            CHECK(op_i25.get(0) == i2);
            CHECK(op_i25.get(1) == i5);
            const auto op_d3_2 = exp_t::createBinary(op, d3, d1_2);
            CHECK(op_d3_2.getKind() == op);
            REQUIRE(op_d3_2.getSize() == 2);
            CHECK(op_d3_2.get(0) == d3);
            CHECK(op_d3_2.get(1) == d1_2);
        }
    }
}