#include <stdlib.h>

double strtod(const char *nptr, char **endptr) {
  return (double)strtold(nptr, endptr);
}
