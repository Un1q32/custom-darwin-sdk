#include <inttypes.h>
#include <stddef.h>

uintmax_t strtoumax(const char *nptr, char **endptr, int base) {
  uintmax_t ret = 0;
  size_t i = 0;
  while (nptr[i] == ' ')
    i++;
  if (nptr[i] == '+')
    i++;
  if (base == 0) {
    if (nptr[i] == '0') {
      if (nptr[i + 1] == 'x' || nptr[i + 1] == 'X') {
        base = 16;
        i += 2;
      } else
        base = 8;
    } else
      base = 10;
  }
  if (base == 16 && nptr[i] == '0' &&
      (nptr[i + 1] == 'x' || nptr[i + 1] == 'X'))
    i += 2;
  while (1) {
    if (nptr[i] >= '0' && nptr[i] <= '9') {
      ret = ret * base + nptr[i] - '0';
    } else if (nptr[i] >= 'a' && nptr[i] <= 'z') {
      ret = ret * base + nptr[i] - 'a' + 10;
    } else if (nptr[i] >= 'A' && nptr[i] <= 'Z') {
      ret = ret * base + nptr[i] - 'A' + 10;
    } else
      break;
    i++;
  }
  if (endptr)
    *endptr = (char *)&nptr[i];
  return ret;
}
