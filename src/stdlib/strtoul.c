#include <stdlib.h>

unsigned long strtoul(const char *nptr, char **endptr, int base) {
  return strtoull(nptr, endptr, base);
}
