#include <stdio.h>
#include <unistd.h>

int fflush(FILE *stream) {
  write(stream->fd, stream->buf, stream->bufcount);
  stream->bufcount = 0;
  return 0;
}
