#include <unistd.h>

extern char **environ;

int execvp(const char *filename, char *const argv[]) {
  return execvpe(filename, argv, environ);
}
