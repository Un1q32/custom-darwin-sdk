#include <stdbool.h>
#include <stdlib.h>

extern char **environ;

int clearenv(void) {
  if (_environ_allocated) {
    int i = 0;
    for (i = 0; environ[i] != NULL; i++)
      free(environ[i]);
    free(environ);
  }
  environ = malloc(sizeof(char *));
  if (environ == NULL)
    return -1;
  environ[0] = NULL;
  _environ_allocated = true;
  return 0;
}
