#include <stddef.h>

int strncmp(const char *str1, const char *str2, size_t n) {
  if (!n--)
    return 0;
  const unsigned char *s1 = (void *)str1, *s2 = (void *)str2;
  while (*s1 && *s2 && n && *s1 == *s2)
    s1++, s2++, n--;
  return *s1 - *s2;
}
