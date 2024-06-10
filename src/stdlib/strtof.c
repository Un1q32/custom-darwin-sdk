#include <stdlib.h>

float strtof(const char *nptr, char **endptr) {
  return (float)strtold(nptr, endptr);
}
