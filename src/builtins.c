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
