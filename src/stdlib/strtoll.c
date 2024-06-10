#include <inttypes.h>

long long strtoll(const char *nptr, char **endptr, int base) {
  return strtoimax(nptr, endptr, base);
}
