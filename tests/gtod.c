#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  printf("Unix Epoch: %ld.%d\n", tv.tv_sec, tv.tv_usec);
  return 0;
}
