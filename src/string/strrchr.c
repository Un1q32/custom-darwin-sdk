#include <stdlib.h>

char *strrchr(const char *str, int ch) {
  char *last = NULL;
  do {
    if (*str == (char)ch)
      last = (char *)str;
  } while (*str++);
  return last;
}
