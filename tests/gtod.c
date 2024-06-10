#include <stdio.h>
#include <sys/time.h>

int main(void) {
  struct timeval tv;
  while (1) {
    gettimeofday(&tv, NULL);
    printf("Unix Epoch: %ld.%06d", tv.tv_sec, tv.tv_usec);
    putchar('\r');
    fflush(stdout);
  }
  return 0;
}
