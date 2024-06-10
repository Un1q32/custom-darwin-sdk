#include <string.h>

extern char **environ;

int _findenv(const char *name) {
  int i;
  for (i = 0; environ[i] != NULL; i++) {
    const char *p = strchr(environ[i], '=');
    if (!strncmp(name, environ[i], p - environ[i]))
      return i;
  }
  return -1;
}
