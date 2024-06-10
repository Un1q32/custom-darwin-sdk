#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

FILE *fopen(const char *filename, const char *mode) {
  int flags = _fopen_mode_parse(mode);
  if (flags == -1) {
    errno = EINVAL;
    return NULL;
  }
  int fd = open(filename, flags, 0644);
  if (fd == -1)
    return NULL;
  return _fdopen(fd, flags);
}
