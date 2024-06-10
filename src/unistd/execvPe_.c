#include <errno.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>

int execvPe(const char *filename, const char *path, char *const argv[],
            char *const envp[]) {
  if (filename == NULL || path == NULL) {
    errno = ENOENT;
    return -1;
  }

  char buf[PATH_MAX];
  char *p = strtok((char *)path, ":");
  while (p != NULL) {
    strlcpy(buf, p, PATH_MAX);
    strlcat(buf, "/", PATH_MAX);
    strlcat(buf, filename, PATH_MAX);
    if (access(buf, F_OK) == 0)
      break;
    p = strtok(NULL, ":");
  }

  if (p == NULL) {
    errno = ENOENT;
    return -1;
  }

  return execve(buf, argv, envp);
}
