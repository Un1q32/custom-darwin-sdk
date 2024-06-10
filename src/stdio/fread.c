#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream) {
  static bool stdin_initialized = false;
  if (!stdin_initialized) {
    if (isatty(STDIN_FILENO))
      stdin->flags |= __SLBF;
    stdin_initialized = true;
  }

  fflush(stream);
  ssize_t readeret = read(stream->fd, ptr, size * nmemb);
  if (readeret < 0) {
    stream->flags |= __SERR;
    return 0;
  } else if (readeret == 0) {
    stream->flags |= __SEOF;
    return 0;
  }
  return readeret / size;
}
