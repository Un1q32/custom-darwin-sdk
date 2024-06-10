#include <string.h>

size_t strspn(const char *str, const char *accept) {
  size_t ret = 0;
  while (*str && strchr(accept, *str++))
    ret++;
  return ret;
}
