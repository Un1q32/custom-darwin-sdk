#include <string.h>

char *strtok(char *str, const char *delim) {
  static char *next = NULL;
  if (str)
    next = str;
  else if (!next)
    return NULL;
  str = next + strspn(next, delim);
  next = str + strcspn(str, delim);
  if (next == str)
    return (next = NULL);
  next = *next ? *next = '\0', next + 1 : NULL;
  return str;
}
