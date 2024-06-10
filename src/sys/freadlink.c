#include <fcntl.h>
#include <limits.h>
#include <unistd.h>

ssize_t freadlink(int fd, char *buf, size_t bufsize) {
  char fdpath[PATH_MAX];
  if (fcntl(fd, F_GETPATH, fdpath) == -1)
    return -1;
  return readlink(fdpath, buf, bufsize);
}
