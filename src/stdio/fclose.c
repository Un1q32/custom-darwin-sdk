#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int fclose(FILE *stream) {
  fflush(stream);
  int ret = close(stream->fd);
  if (stream->listpos > 0) {
    _open_stream_list[stream->listpos] = NULL;
    size_t nstreams = *(size_t *)_open_stream_list;
    if (stream->listpos == nstreams)
      while (nstreams > 0 && _open_stream_list[nstreams] == NULL)
        --nstreams;
    *(size_t *)_open_stream_list = nstreams;
  }

  if (stream != stdin && stream != stdout && stream != stderr) {
    free(stream->buf);
    free(stream);
  }

  return ret;
}
