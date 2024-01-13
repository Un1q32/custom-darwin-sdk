#include <stdint.h>

#define INT64_C(x) ((x) + (INT64_MAX - INT64_MAX))

unsigned long long __divmoddi4(unsigned long long a, unsigned long long b, unsigned long long *rem) {
    unsigned long long r = 0;
    unsigned long long q = 0;
    unsigned long long i = 64;
    while (i--) {
        r <<= 1;
        r |= (a >> 63) & 1;
        a <<= 1;
        q <<= 1;
        if (r >= b) {
            r -= b;
            q |= 1;
        }
    }
    *rem = r;
    return q;
}

unsigned long long __udivdi3(unsigned long long a, unsigned long long b) {
    unsigned long long r;
    return __divmoddi4(a, b, &r);
}

unsigned long long __umoddi3(unsigned long long a, unsigned long long b) {
    unsigned long long r;
    __divmoddi4(a, b, &r);
    return r;
}

unsigned long long __fixunsdfdi(double a) {
    if (a <= 0.0)
        return 0;
    unsigned int high = a / 4294967296.f;
    unsigned int low = a - (double)high * 4294967296.f;
    return ((unsigned long long)high << 32) | low;
}

double __floatundidf(long long a) {
    static const double twop52 = 0x1.0p52;
    static const double twop32 = 0x1.0p32;

    union { long long x; double d; } low = { .d = twop52 };

    const double high = (int)(a >> 32) * twop32;
    low.x |= a & INT64_C(0x00000000ffffffff);

    const double result = (high - twop52) + low.d;
    return result;
}
