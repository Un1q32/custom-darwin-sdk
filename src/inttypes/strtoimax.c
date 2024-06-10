#include <inttypes.h>
#include <stdbool.h>

intmax_t strtoimax(const char *nptr, char **endptr, int base) {
  intmax_t num = 0;
  bool neg = false;
  if (*nptr == '-') {
    neg = true;
    nptr++;
  }
  if (base == 0) {
    if (*nptr == '0') {
      nptr++;
      if (*nptr == 'x' || *nptr == 'X') {
        base = 16;
        nptr++;
      } else {
        base = 8;
      }
    } else {
      base = 10;
    }
  }
  while (true) {
    int digit;
    if (*nptr >= '0' && *nptr <= '9')
      digit = *nptr - '0';
    else if (*nptr >= 'a' && *nptr <= 'z')
      digit = *nptr - 'a' + 10;
    else if (*nptr >= 'A' && *nptr <= 'Z')
      digit = *nptr - 'A' + 10;
    else
      break;
    if (digit >= base)
      break;
    num = num * base + digit;
    nptr++;
  }
  if (neg)
    num = -num;
  if (endptr)
    *endptr = (char *)nptr;
  return num;
}
