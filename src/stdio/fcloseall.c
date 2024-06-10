#include <stdio.h>

void fcloseall(void) {
  size_t nstreams = *(size_t *)_open_stream_list;
  while (nstreams) {
    if (_open_stream_list[nstreams] != NULL)
      fclose(_open_stream_list[nstreams]);
    nstreams--;
  }
  *_open_stream_list = NULL;
  fclose(stdin);
  fclose(stdout);
  fclose(stderr);
}
