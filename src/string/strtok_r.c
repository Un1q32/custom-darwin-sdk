#include <string.h>

char *strtok_r(char *str, const char *delim, char **saveptr) {
  char *token;
  if (!str)
    str = *saveptr;
  str += strspn(str, delim);
  if (!*str)
    return *saveptr = str, NULL;
  token = str;
  str = strpbrk(str, delim);
  if (str)
    *str++ = '\0';
  return *saveptr = str, token;
}
