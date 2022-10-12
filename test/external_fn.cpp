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
