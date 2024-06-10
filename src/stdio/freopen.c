#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

FILE *freopen(const char *path, const char *mode, FILE *stream) {
  fflush(stream);

  if (path) {
    FILE *new_stream = fopen(path, mode);
    if (!new_stream) {
      fclose(stream);
      return NULL;
    }

    if (dup2(fileno(new_stream), fileno(stream)) < 0) {
      fclose(new_stream);
      fclose(stream);
      return NULL;
    }

    stream->flags = new_stream->flags;

    fclose(new_stream);
  } else {
    int flags = _fopen_mode_parse(mode);
    if (flags == -1) {
      errno = EINVAL;
      return NULL;
    }

    if (flags & O_CLOEXEC)
      fcntl(stream->fd, F_SETFD, FD_CLOEXEC);

    flags &= ~(O_CREAT | O_EXCL | O_CLOEXEC);

    if (fcntl(stream->fd, F_SETFL, flags) < 0) {
      fclose(stream);
      return NULL;
    }
  }

  return stream;
}
