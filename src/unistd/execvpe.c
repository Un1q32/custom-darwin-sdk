#include <paths.h>
#include <stdlib.h>
#include <unistd.h>

int execvpe(const char *filename, char *const argv[], char *const envp[]) {
  char *path = getenv("PATH");
  if (path == NULL)
    path = _PATH_DEFPATH;

  return execvPe(filename, path, argv, envp);
}
