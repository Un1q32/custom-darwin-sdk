#include <stdlib.h>
#include <string.h>

char *strdup(const char *str) {
  if (str == NULL)
    return NULL;
  char *dup = malloc(strlen(str) + 1);
  if (dup != NULL)
    strcpy(dup, str);
  return dup;
}
