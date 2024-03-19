#include <string.h>

int bcmp(const void *s1, const void *s2, size_t n) { return memcmp(s1, s2, n); }

void __bzero(void *buf, size_t n) {
  while (n--)
    *(char *)buf++ = 0;
}

void bzero(void *s, size_t n) { __bzero(s, n); }
