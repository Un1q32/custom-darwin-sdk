#include <string.h>

char *_utoa(unsigned long long num) {
  char buf[32];
  char *p = buf + 31;
  *p = '\0';
  do {
    *--p = '0' + num % 10;
    num /= 10;
  } while (num);
  return strdup(p);
}
