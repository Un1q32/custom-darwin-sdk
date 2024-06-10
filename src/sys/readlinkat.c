#include <fcntl.h>
#include <limits.h>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>

ssize_t readlinkat(int fd, const char *path, char *buf, size_t bufsize) {
  if (fd == AT_FDCWD || path[0] == '/')
    return readlink(path, buf, bufsize);

  char fdpath[PATH_MAX];
  if (fcntl(fd, F_GETPATH, fdpath) == -1)
    return -1;

  char new_path[strlen(fdpath) + strlen(path) + 2];
  strcpy(new_path, fdpath);
  strcat(new_path, "/");
  strcat(new_path, path);
  return readlink(new_path, buf, bufsize);
}
