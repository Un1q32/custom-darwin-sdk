#include <unistd.h>

extern char **environ;

int execvP(const char *filename, const char *path, char *const argv[]) {
  return execvPe(filename, path, argv, environ);
}
