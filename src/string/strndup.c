#include <stdlib.h>
#include <string.h>

char *strndup(const char *str, size_t maxlen) {
  size_t len = strnlen(str, maxlen);
  char *newstr = malloc(len + 1);
  if (!newstr)
    return NULL;
  memcpy(newstr, str, len);
  newstr[len] = '\0';
  return newstr;
}
