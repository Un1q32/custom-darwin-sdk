#include <stdlib.h>

char *strchr(const char *str, int ch) {
  while (*str != (char)ch) {
    if (*str == '\0')
      return NULL;
    str++;
  }
  return (char *)str;
}
