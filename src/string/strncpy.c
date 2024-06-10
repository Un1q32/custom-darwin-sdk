#include <stddef.h>

char *strncpy(char *dst, const char *src, size_t size) {
  char *ret = dst;
  while (size && (*dst++ = *src++))
    size--;
  while (size--)
    *dst++ = '\0';
  return ret;
}
