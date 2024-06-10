#include <unistd.h>

extern char **environ;

int execv(const char *filename, char *const argv[]) {
  return execve(filename, argv, environ);
}
