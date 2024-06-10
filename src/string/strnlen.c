#include <string.h>

size_t strnlen(const char *str, size_t maxlen) {
  const char *end = memchr(str, '\0', maxlen);
  return end ? (size_t)(end - str) : maxlen;
}
