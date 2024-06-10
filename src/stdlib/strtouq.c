#include <stdlib.h>

u_quad_t strtouq(const char *nptr, char **endptr, int base) {
  return strtoull(nptr, endptr, base);
}
