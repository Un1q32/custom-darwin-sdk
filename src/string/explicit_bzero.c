#include <strings.h>

void explicit_bzero(void *s, size_t n) {
  bzero(s, n);
  __asm__ volatile("" : : "r"(s) : "memory");
}
