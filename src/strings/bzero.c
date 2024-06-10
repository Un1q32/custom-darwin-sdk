#include <stddef.h>

void bzero(void *buf, size_t n) {
  char *p = buf;
  while (n-- > 0)
    *p++ = 0;
}
