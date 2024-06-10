#include <stddef.h>

void memset_pattern8(void *b, const void *pattern, size_t len) {
  unsigned long long *p = b;
  unsigned long long pat = *(unsigned long long *)pattern;
  while (len >= 8) {
    *p++ = pat;
    len -= 8;
  }
  unsigned char *q = (unsigned char *)p;
  while (len--)
    *q++ = *(unsigned char *)pattern;
}
