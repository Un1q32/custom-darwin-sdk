#include <string.h>

char *strncat(char *dst, const char *src, size_t n) {
  char *ret = dst;
  dst += strlen(dst);
  while (n && *src)
    n--, *dst++ = *src++;
  *dst++ = 0;
  return ret;
}
