#include <fcntl.h>
#include <limits.h>
#include <unistd.h>

char *ttyname(int fd) {
  if (!isatty(fd))
    return NULL;
  static char buf[PATH_MAX];
  fcntl(fd, F_GETPATH, buf);
  return buf;
}
