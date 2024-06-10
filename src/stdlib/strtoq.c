#include <stdlib.h>

quad_t strtoq(const char *nptr, char **endptr, int base) {
  return strtoll(nptr, endptr, base);
}
