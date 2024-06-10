#include <ctype.h>

long double strtold(const char *nptr, char **endptr) {
  long double ret = 0;
  int sign = 1;
  while (isspace(*nptr))
    nptr++;
  if (*nptr == '-') {
    sign = -1;
    nptr++;
  } else if (*nptr == '+')
    nptr++;
  if (nptr[0] == '0' && (nptr[1] == 'x' || nptr[1] == 'X')) {
    nptr += 2;
    while (1) {
      int digit;
      if (*nptr >= '0' && *nptr <= '9')
        digit = *nptr - '0';
      else if (*nptr >= 'a' && *nptr <= 'z')
        digit = *nptr - 'a' + 10;
      else if (*nptr >= 'A' && *nptr <= 'Z')
        digit = *nptr - 'A' + 10;
      else
        break;
      ret = ret * 16 + digit;
      nptr++;
    }
  } else {
    while (1) {
      int digit;
      if (*nptr >= '0' && *nptr <= '9')
        digit = *nptr - '0';
      else
        break;
      ret = ret * 10 + digit;
      nptr++;
    }
  }
  if (*nptr == '.') {
    long double factor = 0.1;
    nptr++;
    while (1) {
      int digit;
      if (*nptr >= '0' && *nptr <= '9')
        digit = *nptr - '0';
      else
        break;
      ret += factor * digit;
      factor *= 0.1;
      nptr++;
    }
  }
  if (endptr)
    *endptr = (char *)nptr;
  return sign * ret;
}
