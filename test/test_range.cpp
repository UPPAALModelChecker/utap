#include "utap/range.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(RangeTests)

constexpr auto d_eps = std::numeric_limits<double>::epsilon();
constexpr auto d_inf = std::numeric_limits<double>::infinity();
constexpr auto d_ninf = -d_inf;
constexpr auto d_max = std::numeric_limits<double>::max();
constexpr auto d_min = std::numeric_limits<double>::lowest();

constexpr auto f_eps = std::numeric_limits<float>::epsilon();
constexpr auto f_inf = std::numeric_limits<float>::infinity();
constexpr auto f_ninf = -d_inf;
constexpr auto f_min = std::numeric_limits<float>::lowest();

constexpr auto i_max = std::numeric_limits<int>::max();
constexpr auto i_min = std::numeric_limits<int>::min();

BOOST_AUTO_TEST_CASE(NextAferDoubleOne)
{
    // Tests the definition of epsilon:
    auto d = 1.0;
    auto next_d = UTAP::next_value(d);
    BOOST_CHECK_EQUAL(next_d, 1.0 + d_eps);
}

BOOST_AUTO_TEST_CASE(NextAferFloatOne)
{
    // Tests the definition of epsilon:
    auto f = 1.0f;
    auto next_f = UTAP::next_value(f);
    BOOST_CHECK_EQUAL(next_f, 1.0f + f_eps);
}

BOOST_AUTO_TEST_CASE(NextAferDoubleMax)
{
    // Tests that all values converge at the infinity
    auto d = std::numeric_limits<double>::max();
    auto next_d = UTAP::next_value(d);
    BOOST_CHECK_EQUAL(next_d, d_inf);
}

BOOST_AUTO_TEST_CASE(NextAferFloatMax)
{
    auto f = std::numeric_limits<float>::max();
    auto next_f = UTAP::next_value(f);
    BOOST_CHECK_EQUAL(next_f, f_inf);
}

BOOST_AUTO_TEST_CASE(PrevBeforeDoubleLowest)
{
    auto d = d_min;
    auto prev_d = UTAP::prev_value(d);
    BOOST_CHECK_EQUAL(prev_d, d_ninf);
}

BOOST_AUTO_TEST_CASE(PrevBeforeFloatLowest)
{
    auto f = f_min;
    auto prev_f = UTAP::prev_value(f);
    BOOST_CHECK_EQUAL(prev_f, f_ninf);
}

BOOST_AUTO_TEST_CASE(NextAferIntMax)
{
    // Tests that all values converge at the infinity
    auto i = i_max - 1;
    auto next_i = UTAP::next_value(i);
    BOOST_CHECK_EQUAL(next_i, i_max);
}

BOOST_AUTO_TEST_CASE(PrevBeforeIntMin)
{
    auto i = i_min + 1;
    auto prev_i = UTAP::prev_value(i);
    BOOST_CHECK_EQUAL(prev_i, i_min);
}

BOOST_AUTO_TEST_CASE(NextAferDoubleNegInf)
{
    auto d = -d_inf;
    auto next_d = UTAP::next_value(d);
    BOOST_CHECK_EQUAL(next_d, d_min);
}

BOOST_AUTO_TEST_CASE(PrevBeforeDoubleInf)
{
    auto d = d_inf;
    auto prev_d = UTAP::prev_value(d);
    BOOST_CHECK_EQUAL(prev_d, d_max);
}

BOOST_AUTO_TEST_CASE(GreaterThanInfinity)
{
    auto r1 = UTAP::range_t<double>(0, d_inf);
    r1 = r1.gt(d_inf);
    BOOST_CHECK(r1.empty());
}

BOOST_AUTO_TEST_CASE(LessThanNegativeInfinity)
{
    auto r1 = UTAP::range_t<double>(d_ninf, 0);
    r1 = r1.lt(d_ninf);
    BOOST_CHECK(r1.empty());
}

BOOST_AUTO_TEST_SUITE_END()
