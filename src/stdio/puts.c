#include <stdio.h>
#include <string.h>

int puts(const char *str) {
  return fwrite(str, 1, strlen(str), stdout) + fwrite("\n", 1, 1, stdout);
}
