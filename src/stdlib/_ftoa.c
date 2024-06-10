#include <stdlib.h>
#include <string.h>

char *_ftoa(long double num, int percision) {
  char buf[32];
  char *p = buf;
  if (num < 0) {
    *p++ = '-';
    num = -num;
  }
  unsigned long long integer = num;
  num -= integer;
  char *int_str = _utoa(integer);
  strcpy(p, int_str);
  p += strlen(int_str);
  free(int_str);
  *p++ = '.';
  while (percision--) {
    num *= 10;
    *p++ = '0' + (int)num;
    num -= (int)num;
  }
  *p = '\0';
  return strdup(buf);
}
