#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

FILE *_fdopen(int fd, mode_t flags) {
  FILE *ret = malloc(sizeof(FILE));
  if (ret == NULL)
    return NULL;
  ret->buf = malloc(BUFSIZ);
  if (ret->buf == NULL) {
    free(ret);
    return NULL;
  }
  ret->fd = fd;
  ret->flags = 0;
  ret->bufcount = 0;
  size_t *nstreams = (size_t *)_open_stream_list;
  if (*nstreams > 65535) {
    free(ret->buf);
    free(ret);
    return NULL;
  }
  _open_stream_list[++*nstreams] = ret;
  ret->listpos = *nstreams;
  if (flags & O_CLOEXEC) {
    fcntl(fd, F_SETFD, FD_CLOEXEC);
    flags &= ~O_CLOEXEC;
  }
  if (isatty(fd))
    ret->flags |= __SLBF;
  return ret;
}
