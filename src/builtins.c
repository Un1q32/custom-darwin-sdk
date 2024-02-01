/*
 * These functions are adapted from the compiler-rt project and are therefore
 * licenced under the Apache License v2.0 with LLVM Exceptions.
 * See https://llvm.org/LICENSE.txt for license information.
 */

#include <limits.h>
#include <stdint.h>

#if UINT_MAX == 0xFFFFFFFF
#define clzsi __builtin_clz
#define ctzsi __builtin_ctz
#elif ULONG_MAX == 0xFFFFFFFF
#define clzsi __builtin_clzl
#define ctzsi __builtin_ctzl
#else
#error could not determine appropriate clzsi macro for this system
#endif

#define clz(a)                                                                 \
  (sizeof(a) == sizeof(unsigned long long) ? __builtin_clzll(a) : clzsi(a))

typedef union {
  unsigned long long all;
  struct {
    unsigned int low, high;
  } s;
} udwords;

unsigned long long __udivmoddi4(unsigned long long a, unsigned long long b,
                                unsigned long long *rem) {
  const unsigned n_uword_bits = sizeof(unsigned int) * __CHAR_BIT__;
  const unsigned n_udword_bits = sizeof(unsigned long long) * __CHAR_BIT__;
  udwords n;
  n.all = a;
  udwords d;
  d.all = b;
  udwords q;
  udwords r;
  unsigned sr;
  if (n.s.high == 0) {
    if (d.s.high == 0) {
      if (rem)
        *rem = n.s.low % d.s.low;
      return n.s.low / d.s.low;
    }
    if (rem)
      *rem = n.s.low;
    return 0;
  }
  if (d.s.low == 0) {
    if (d.s.high == 0) {
      if (rem)
        *rem = n.s.high % d.s.low;
      return n.s.high / d.s.low;
    }
    if (n.s.low == 0) {
      if (rem) {
        r.s.high = n.s.high % d.s.high;
        r.s.low = 0;
        *rem = r.all;
      }
      return n.s.high / d.s.high;
    }
    if ((d.s.high & (d.s.high - 1)) == 0) {
      if (rem) {
        r.s.low = n.s.low;
        r.s.high = n.s.high & (d.s.high - 1);
        *rem = r.all;
      }
      return n.s.high >> ctzsi(d.s.high);
    }
    sr = clzsi(d.s.high) - clzsi(n.s.high);
    if (sr > n_uword_bits - 2) {
      if (rem)
        *rem = n.all;
      return 0;
    }
    ++sr;
    q.s.low = 0;
    q.s.high = n.s.low << (n_uword_bits - sr);
    r.s.high = n.s.high >> sr;
    r.s.low = (n.s.high << (n_uword_bits - sr)) | (n.s.low >> sr);
  } else {
    if (d.s.high == 0) {
      if ((d.s.low & (d.s.low - 1)) == 0) {
        if (rem)
          *rem = n.s.low & (d.s.low - 1);
        if (d.s.low == 1)
          return n.all;
        sr = ctzsi(d.s.low);
        q.s.high = n.s.high >> sr;
        q.s.low = (n.s.high << (n_uword_bits - sr)) | (n.s.low >> sr);
        return q.all;
      }
      sr = 1 + n_uword_bits + clzsi(d.s.low) - clzsi(n.s.high);
      if (sr == n_uword_bits) {
        q.s.low = 0;
        q.s.high = n.s.low;
        r.s.high = 0;
        r.s.low = n.s.high;
      } else if (sr < n_uword_bits) {
        q.s.low = 0;
        q.s.high = n.s.low << (n_uword_bits - sr);
        r.s.high = n.s.high >> sr;
        r.s.low = (n.s.high << (n_uword_bits - sr)) | (n.s.low >> sr);
      } else {
        q.s.low = n.s.low << (n_udword_bits - sr);
        q.s.high = (n.s.high << (n_udword_bits - sr)) |
                   (n.s.low >> (sr - n_uword_bits));
        r.s.high = 0;
        r.s.low = n.s.high >> (sr - n_uword_bits);
      }
    } else {
      sr = clzsi(d.s.high) - clzsi(n.s.high);
      if (sr > n_uword_bits - 1) {
        if (rem)
          *rem = n.all;
        return 0;
      }
      ++sr;
      q.s.low = 0;
      if (sr == n_uword_bits) {
        q.s.high = n.s.low;
        r.s.high = 0;
        r.s.low = n.s.high;
      } else {
        q.s.high = n.s.low << (n_uword_bits - sr);
        r.s.high = n.s.high >> sr;
        r.s.low = (n.s.high << (n_uword_bits - sr)) | (n.s.low >> sr);
      }
    }
  }
  unsigned int carry = 0;
  for (; sr > 0; --sr) {
    r.s.high = (r.s.high << 1) | (r.s.low >> (n_uword_bits - 1));
    r.s.low = (r.s.low << 1) | (q.s.high >> (n_uword_bits - 1));
    q.s.high = (q.s.high << 1) | (q.s.low >> (n_uword_bits - 1));
    q.s.low = (q.s.low << 1) | carry;
    const long long s = (long long)(d.all - r.all - 1) >> (n_udword_bits - 1);
    carry = s & 1;
    r.all -= d.all & s;
  }
  q.all = (q.all << 1) | carry;
  if (rem)
    *rem = r.all;
  return q.all;
}

long long __divmoddi4(long long a, long long b, long long *rem) {
  const int bits_in_word_m1 = (int)(sizeof(long long) * __CHAR_BIT__) - 1;
  long long s_a = a >> bits_in_word_m1;
  long long s_b = b >> bits_in_word_m1;
  a = (unsigned long long)(a ^ s_a) - s_a;
  b = (unsigned long long)(b ^ s_b) - s_b;
  s_b ^= s_a;
  unsigned long long r;
  long long q = (__udivmoddi4(a, b, &r) ^ s_b) - s_b;
  *rem = (r ^ s_a) - s_a;
  return q;
}

static unsigned long long __udivXi3(unsigned long long n,
                                    unsigned long long d) {
  const unsigned N = sizeof(unsigned long long) * __CHAR_BIT__;
  unsigned sr = (d ? clz(d) : N) - (n ? clz(n) : N);
  if (sr > N - 1)
    return 0;
  if (sr == N - 1)
    return n;
  ++sr;
  unsigned long long r = n >> sr;
  n <<= N - sr;
  unsigned long long carry = 0;
  for (; sr > 0; --sr) {
    r = (r << 1) | (n >> (N - 1));
    n = (n << 1) | carry;
    const long long s = (long long)(d - r - 1) >> (N - 1);
    carry = s & 1;
    r -= d & s;
  }
  n = (n << 1) | carry;
  return n;
}

static unsigned long long __umodXi3(unsigned long long n,
                                    unsigned long long d) {
  const unsigned N = sizeof(unsigned long long) * __CHAR_BIT__;
  unsigned sr = (d ? clz(d) : N) - (n ? clz(n) : N);
  if (sr > N - 1)
    return n;
  if (sr == N - 1)
    return 0;
  ++sr;
  unsigned long long r = n >> sr;
  n <<= N - sr;
  unsigned long long carry = 0;
  for (; sr > 0; --sr) {
    r = (r << 1) | (n >> (N - 1));
    n = (n << 1) | carry;
    const long long s = (long long)(d - r - 1) >> (N - 1);
    carry = s & 1;
    r -= d & s;
  }
  return r;
}

unsigned long long __udivdi3(unsigned long long a, unsigned long long b) {
  return __udivXi3(a, b);
}

unsigned int __udivsi3(unsigned int n, unsigned int d) {
  const unsigned n_uword_bits = sizeof(unsigned int) * __CHAR_BIT__;
  unsigned int q;
  unsigned int r;
  unsigned sr;
  if (d == 0)
    return 0;
  if (n == 0)
    return 0;
  sr = __builtin_clz(d) - __builtin_clz(n);
  if (sr > n_uword_bits - 1)
    return 0;
  if (sr == n_uword_bits - 1)
    return n;
  ++sr;
  q = n << (n_uword_bits - sr);
  r = n >> sr;
  unsigned int carry = 0;
  for (; sr > 0; --sr) {
    r = (r << 1) | (q >> (n_uword_bits - 1));
    q = (q << 1) | carry;
    const int s = (int)(d - r - 1) >> (n_uword_bits - 1);
    carry = s & 1;
    r -= d & s;
  }
  q = (q << 1) | carry;
  return q;
}

unsigned long long __umoddi3(unsigned long long a, unsigned long long b) {
  return __umodXi3(a, b);
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

  union {
    long long x;
    double d;
  } low = {.d = twop52};

  const double high = (int)(a >> 32) * twop32;
  low.x |= a & INT64_C(0x00000000ffffffff);

  const double result = (high - twop52) + low.d;
  return result;
}

int __divsi3(int a, int b) {
  const int bits_in_word_m1 = (int)(sizeof(int) * __CHAR_BIT__) - 1;
  int s_a = a >> bits_in_word_m1;
  int s_b = b >> bits_in_word_m1;
  a = (a ^ s_a) - s_a;
  b = (b ^ s_b) - s_b;
  s_a ^= s_b;
  return ((unsigned int)a / (unsigned int)b ^ s_a) - s_a;
}

int __modsi3(int a, int b) { return a - __divsi3(a, b) * b; }

unsigned int __umodsi3(unsigned int a, unsigned int b) {
  return (unsigned int)__umodXi3(a, b);
}
