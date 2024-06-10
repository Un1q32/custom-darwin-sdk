#include <stddef.h>

void memset_pattern4(void *b, const void *pattern, size_t len) {
  unsigned int *p = b;
  unsigned int pat = *(unsigned int *)pattern;
  while (len >= 4) {
    *p++ = pat;
    len -= 4;
  }
  unsigned char *q = (unsigned char *)p;
  while (len--)
    *q++ = *(unsigned char *)pattern;
}
