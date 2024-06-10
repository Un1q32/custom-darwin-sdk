#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

char *getcwd(char *buf, size_t size) {
  int fd = open(".", O_RDONLY);
  if (fd == -1)
    return NULL;

  char tmp[PATH_MAX];
  if (fcntl(fd, F_GETPATH, tmp) == -1)
    return NULL;

  size_t len = strlen(tmp);
  if (len >= size && buf != NULL) {
    errno = ERANGE;
    return NULL;
  }

  if (buf == NULL) {
    buf = malloc(len + 1);
    if (buf == NULL)
      return NULL;
  }

  strcpy(buf, tmp);
  return buf;
}
