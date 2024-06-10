#include <string.h>

char *basename(char *path) {
  char *base = strrchr(path, '/');
  return base ? base + 1 : path;
}
