/*
 * These functions are adapted from the compiler-rt project and are therefore
 * licenced under the Apache License v2.0 with LLVM Exceptions.
 * See https://llvm.org/LICENSE.txt for license information.
 */

#include <stdint.h>

unsigned long long __divmoddi4(unsigned long long a, unsigned long long b,
                               unsigned long long *rem) {
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
