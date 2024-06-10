#include <string.h>

char *strpbrk(const char *str, const char *accept) {
  while (*str) {
    if (strchr(accept, *str))
      return (char *)str;
    else
      str++;
  }
  return NULL;
}
