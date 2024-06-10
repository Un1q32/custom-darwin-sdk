#include <stddef.h>

void *memchr(const void *buf, int ch, size_t size) {
  const unsigned char *ptr = buf;
  while (size--) {
    if (*ptr == (unsigned char)ch)
      return (void *)ptr;
    ptr++;
  }
  return NULL;
}
