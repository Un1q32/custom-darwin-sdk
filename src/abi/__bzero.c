#include <strings.h>

void __bzero(void *buf, size_t n) {
  bzero(buf, n);
}
