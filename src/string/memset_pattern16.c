#include <stddef.h>

void memset_pattern16(void *b, const void *pattern, size_t len) {
  unsigned long long *p = b;
  unsigned long long pat1 = *(unsigned long long *)pattern;
  unsigned long long pat2 = *((unsigned long long *)pattern + 1);
  while (len >= 16) {
    *p++ = pat1;
    *p++ = pat2;
    len -= 16;
  }
  unsigned char *q = (unsigned char *)p;
  while (len--)
    *q++ = *(unsigned char *)pattern;
}
