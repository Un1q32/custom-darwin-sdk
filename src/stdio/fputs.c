#include <stdio.h>
#include <string.h>

int fputs(const char *str, FILE *stream) {
  return fwrite(str, 1, strlen(str), stream);
}
