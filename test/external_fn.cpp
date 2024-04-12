// -*- mode: C++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-

/* libutap - Uppaal Timed Automata Parser.
   Copyright (C) 2020-2022 Aalborg University.

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

#include <cmath>    // sqrt
#include <cstring>  // strlen

#if defined(_WIN32)
#define C_PUBLIC extern "C" __declspec(dllexport)
#elif defined(__linux__)
#define C_PUBLIC extern "C"
#else
#define C_PUBLIC extern "C" __attribute__((visibility("default")))
#endif

C_PUBLIC int square(int a) { return a * a; }
C_PUBLIC int multiply(int a, int b) { return a * b; }
C_PUBLIC double square_root(double a) { return std::sqrt(a); }
C_PUBLIC double power(double a, int p)
{
    if (p == 0)
        return 1;
    auto n = (p > 0) ? p : -p;
    auto res = 1.0;
    while (n-- > 0)
        res *= a;
    if (p < 0)
        res = 1.0 / res;
    return res;
}
C_PUBLIC double calc_sum(int count, const double arr[])
{
    auto res = 0.0;
    while (count-- > 0)
        res += arr[count];
    return res;
}
C_PUBLIC unsigned int length(const char* str) { return std::strlen(str); }

C_PUBLIC bool fast_double(double arr[], int count)
{
    for (auto i = 0; i < count; ++i)
        arr[i] *= 2;
    return count % 2 == 0;
}

static int number = 42;
C_PUBLIC void set_number(int a) { number = a; }
C_PUBLIC int get_number() { return number; }
