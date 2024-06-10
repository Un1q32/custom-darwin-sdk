#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

FILE *fdopen(int fd, const char *mode) {
  int flags = _fopen_mode_parse(mode);
  if (flags == -1) {
    errno = EINVAL;
    return NULL;
  }
  return _fdopen(fd, flags);
}
