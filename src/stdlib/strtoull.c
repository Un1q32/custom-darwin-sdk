#include <inttypes.h>

unsigned long long strtoull(const char *nptr, char **endptr, int base) {
  return strtoumax(nptr, endptr, base);
}
