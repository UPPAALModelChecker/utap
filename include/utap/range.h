// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (c) 2018 Aalborg University.

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

#ifndef INCLUDE_UTAP_RANGE_H
#define INCLUDE_UTAP_RANGE_H

#include <iostream>
#include <limits>
#include <stdexcept>
#include <cassert>
#include <cmath>
#include <cstdint>  // int32_t

namespace UTAP
{
    template <typename T>
    struct UnsupportedType;  // the absence of definition triggers a compile-time error exposing the type

    template <typename T>
    constexpr T prev_value(T value)
    {
        if constexpr (std::is_floating_point_v<T>) {
            static_assert(std::numeric_limits<T>::has_infinity, "Requires infinity support");
            assert(value > -std::numeric_limits<T>::infinity());  // below -inf
            return std::nexttoward(value, -std::numeric_limits<T>::infinity());
        } else if constexpr (std::is_integral_v<T>) {
            assert(value > std::numeric_limits<T>::min());  // below min
            return value - 1;
        } else {
            UnsupportedType<T> the_type_T_is_not_supported;
        }
    }

    template <typename T>
    constexpr T next_value(T value)
    {
        if constexpr (std::is_floating_point_v<T>) {
            static_assert(std::numeric_limits<T>::has_infinity, "Requires infinity support");
            assert(value < std::numeric_limits<T>::infinity());  // beyond infinity
            return std::nexttoward(value, std::numeric_limits<T>::infinity());
        } else if constexpr (std::is_integral_v<T>) {
            assert(value < std::numeric_limits<T>::max());  // beyond max
            return value + 1;
        } else {
            UnsupportedType<T> the_type_T_is_not_supported;
        }
    }

    /** \brief range_t is a continuous set of inhabitants of the type T.
     * This means that any range defined by range_t is nonstrict.
     * It can still be used as an interval, and this interpretation is
     * consistent, and many operations for ranges are supported.
     */
    template <typename T = int32_t>
    class range_t
    {
        /** the first element in the range */
        T start{};
        /** the last element in the range */
        T finish{};

    public:
        using value_type = T;
        range_t() = default;
        range_t(const range_t&) = default;
        static range_t make_empty() { return range_t(1, 0); }

        /** construct a range of [first,last] */
        range_t(const T& first, const T& last): start{first}, finish{last} {}
        /** construct a range of singleton {e} */
        explicit range_t(const T& e): range_t{e, e} {}

        /** the range is strictly below the other */
        bool operator<(const range_t& o) const
        {
            assert(!o.empty());
            return finish < o.start;
        }
        /** the range is below the other, may also overlap */
        bool operator<=(const range_t& o) const { return !(*this > o); }
        /** the range is strictly above the other */
        bool operator>(const range_t& o) const { return o < *this; }
        /** the range is above the other, may also overlap */
        bool operator>=(const range_t& o) const { return !(*this < o); }

        /** lowers the lower bound */
        range_t& lower(const T& b)
        {
            start = std::min(start, b);
            return *this;
        }
        /** raises the upper bound */
        range_t& raise(const T& b)
        {
            finish = std::max(finish, b);
            return *this;
        }
        /** inserts an element into a range by computing convex union: */
        range_t& operator|=(const T& e) { return lower(e).raise(e); }
        /** computes a convex union of ranges */
        range_t& operator|=(const range_t& o) { return lower(o.start).raise(o.finish); }
        /** computes convex union of ranges */
        range_t operator|(const range_t& o) const { return range_t(*this) |= o; }
        /** inserts an element into a range by computing a convex union: */
        range_t operator|(const T& e) const { return range_t(*this) |= e; }

        /** Constrain to greater than the lower bound */
        range_t& gt(const T& lower)
        {
            if constexpr (std::numeric_limits<T>::has_infinity) {
                if (std::isinf(lower) && lower > std::numeric_limits<T>::max()) {
                    start = 1;
                    finish = 0;
                    return *this;
                }
            }
            start = std::max(next_value(lower), start);
            return *this;
        }

        /** Constrain to lower than the upper bound */
        range_t& lt(const T& upper)
        {
            if constexpr (std::numeric_limits<T>::has_infinity) {
                if (std::isinf(upper) && upper < std::numeric_limits<T>::lowest()) {
                    start = 1;
                    finish = 0;
                    return *this;
                }
            }
            finish = std::min(finish, upper);
            return *this;
        }

        /** constrain to greater-than-or-equal-to lower bound */
        range_t& geq(const T& lower)
        {
            start = std::max(start, lower);
            return *this;
        }
        /** constrain to less-than-or-equal-to upper bound */
        range_t& leq(const T& upper)
        {
            finish = std::min(finish, upper);
            return *this;
        }
        /** computes an intersection of two ranges (may become empty) */
        range_t& operator&=(const range_t& o) { return geq(o.start).leq(o.finish); }
        /** computes an intersection with an element (may become empty) */
        range_t& operator&=(const T& e) { return geq(e).leq(e); }
        /** computes an intersection of ranges */
        range_t operator&(const range_t& o) const { return range_t(*this) &= o; }
        /** computes an intersection of ranges */
        range_t operator&(const T& e) const { return range_t(*this) &= e; }

        /* computes the symbolic plus */
        range_t& operator+=(const range_t& o)
        {
            assert(!o.empty());
            start += o.first();
            finish += o.last();
            return *this;
        }

        /* computes the symbolic plus */
        range_t& operator+=(const T& e)
        {
            start += e;
            finish += e;
            return *this;
        }

        /* computes the symbolic minus */
        range_t& operator-=(const range_t& o)
        {
            assert(!o.empty());
            start -= o.last();
            finish -= o.first();
            return *this;
        }

        /* computes the symbolic minus */
        range_t& operator-=(const T& e)
        {
            start -= e;
            finish -= e;
            return *this;
        }

        /* computes the symbolic multiplication */
        range_t& operator*=(const range_t& o)
        {
            assert(!o.empty());
            auto t1 = first() * o.first();
            auto t2 = first() * o.last();
            auto t3 = last() * o.first();
            auto t4 = last() * o.last();
            start = std::min(std::min(t1, t2), std::min(t3, t4));
            finish = std::max(std::max(t1, t2), std::max(t3, t4));
            return *this;
        }
        /* computes the symbolic multiplication */
        range_t& operator*=(const T& e)
        {
            start *= e;
            finish *= e;
            if (finish < start)  // e.g. e=-1
                std::swap(start, finish);
            return *this;
        }
        /* Computes the symbolic sum over the ranges*/
        range_t operator+(const range_t& o) const { return range_t(*this) += o; }
        /* Computes the symbolic sum with an element (offset)*/
        range_t operator+(const T& e) const { return range_t(*this) += e; }
        /* Computes the symbolic subtraction over the ranges*/
        range_t operator-(const range_t& o) const { return range_t(*this) -= o; }
        /* Computes the symbolic subtraction with an element (offset)*/
        range_t operator-(const T& e) const { return range_t(*this) -= e; }
        /* Computes the symbolic product over the ranges*/
        range_t operator*(const range_t& o) const { return range_t(*this) *= o; }
        /* Computes the symbolic product with an element (offset)*/
        range_t operator*(const T& e) const { return range_t(*this) *= e; }

        /** returns true if ranges overlap */
        bool operator&&(const range_t& o) const
        {
            if (start <= o.start)  // o.start is inside [start,finish)
                return (o.start <= finish);
            else  // start is inside [o.start,o.finish)
                return (start <= o.finish);
        }

        /** returns true if the range includes an element */
        bool operator&&(const T& e) const { return (start <= e) && (e <= finish); }

        /** checks for equality between ranges */
        bool operator==(const range_t& o) const
        {
            if (empty() || o.empty())
                return empty() == o.empty();
            return finish == o.finish && start == o.start;
        }

        /** checks if range is singleton of exactly e*/
        bool operator==(const T& e) const { return (*this) == range_t(e); }

        /** inserts an element into a range by computing convex union: */
        range_t& add(const T& e) { return *this |= e; }

        /** merges two ranges by computing convex union: */
        range_t& add(const range_t& r) { return *this |= r; }

        /** computes convex union of a range and an element: */
        range_t unite(const T& e) const { return *this | e; }

        /** computes convex union of two ranges: */
        range_t unite(const range_t& r) const { return (*this | r); }

        /** intersects the range with an element: */
        range_t& intersect(const T& e) { return *this &= e; }

        /** intersects the range with another: */
        range_t& intersect(const range_t& r) { return *this &= r; }

        /** computes intersection with an element: */
        range_t intersection(const T& e) const { return (*this & e); }

        /** computes intersection of two ranges: */
        range_t intersection(const range_t& r) const { return (*this & r); }

        /** checks if the range contains an element */
        bool contains(const T& e) const { return (*this && e); }

        /** checks if the range intersects with another */
        bool intersects(const range_t& r) const { return (*this && r); }

        /** checks if the range is empty */
        bool empty() const { return start > finish; }
        void clear() { *this = range_t{}; }

        friend std::ostream& operator<<(std::ostream& os, const range_t& range)
        {
            return os << '[' << range.start << ',' << range.finish << ']';
        }

        /** outputs number of discrete elements of T in range*/
        uint32_t size() const { return empty() ? 0 : 1 + (finish - start); }

        T first() const { return start; }
        T last() const { return finish; }

    }; /* range_t */

    template <typename T>
    range_t(const T& first, const T& last) -> range_t<T>;

    template <typename T>
    range_t(const T& value) -> range_t<T>;

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const range_t<T>& range)
    {
        return range.print(os);
    }

    template <typename T>
    range_t(T&& b, T&& e) -> range_t<T>;

}  // namespace UTAP

namespace std
{
    template <typename T>
    UTAP::range_t<T> min(const UTAP::range_t<T>& a, const UTAP::range_t<T>& b)
    {
        return UTAP::range_t<T>(std::min(a.first(), b.first()), std::min(a.last(), b.last()));
    }

    template <typename T>
    UTAP::range_t<T> max(const UTAP::range_t<T>& a, const UTAP::range_t<T>& b)
    {
        return UTAP::range_t<T>(std::max(a.first(), b.first()), std::max(a.last(), b.last()));
    }
}  // namespace std

#endif /* INCLUDE_UTAP_RANGE_H */
