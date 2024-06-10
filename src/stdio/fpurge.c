#include <stdio.h>

int fpurge(FILE *stream) {
  stream->bufcount = 0;
  return 0;
}
