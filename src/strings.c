#include <string.h>

int bcmp(const void *s1, const void *s2, size_t n) { return memcmp(s1, s2, n); }

void __bzero(void *s, size_t n) {
  char *buf = s;
  size_t i;
  for (i = 0; i <= n; i++)
    *buf++ = 0;
}

void bzero(void *s, size_t n) { __bzero(s, n); }
