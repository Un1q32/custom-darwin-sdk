#include <stddef.h>

void *memset(void *buf, int byte, size_t size) {
  unsigned char *p = buf;
  while (size--)
    *p++ = (unsigned char)byte;
  return buf;
}
