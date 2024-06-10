#include <string.h>

size_t strlcat(char *dst, const char *src, size_t n) {
  const char *odst = dst;
  const char *osrc = src;
  size_t nleft = n;
  while (nleft-- != 0 && *dst != '\0')
    dst++;
  size_t dlen = dst - odst;
  nleft = n - dlen;
  if (nleft-- == 0)
    return dlen + strlen(src);
  while (*src != '\0') {
    if (nleft != 0) {
      *dst++ = *src;
      nleft--;
    }
    src++;
  }
  *dst = '\0';
  return dlen + (src - osrc);
}
