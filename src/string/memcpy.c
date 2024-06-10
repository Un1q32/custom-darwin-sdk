#include <stddef.h>

void *memcpy(void *dst, const void *src, size_t size) {
  char *d = dst;
  const char *s = src;
  while (size--)
    *d++ = *s++;
  return dst;
}
