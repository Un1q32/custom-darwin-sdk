#include <stdlib.h>
#include <string.h>

extern char **environ;

char *getenv(const char *name) {
  int i = _findenv(name);
  if (i == -1)
    return NULL;
  return strchr(environ[i], '=') + 1;
}
