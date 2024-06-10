#include <string.h>

size_t strcspn(const char *str, const char *reject) {
  size_t ret = 0;
  while (*str) {
    if (strchr(reject, *str))
      return ret;
    else
      str++, ret++;
  }
  return ret;
}
