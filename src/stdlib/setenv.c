#include <stdlib.h>
#include <string.h>

int setenv(const char *name, const char *value, int overwrite) {
  char putenv_str[strlen(name) + strlen(value) + 2];
  strcpy(putenv_str, name);
  strcat(putenv_str, "=");
  strcat(putenv_str, value);
  return _putenv(putenv_str, overwrite);
}
