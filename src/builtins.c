unsigned long long __divmoddi4(unsigned long long a, unsigned long long b, unsigned long long *rem) {
    unsigned long long r = 0;
    while (a >= b) {
        a -= b;
        r++;
    }
    *rem = a;
    return r;
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
