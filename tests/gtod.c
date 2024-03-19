#include <stdio.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;
  struct timeval tv;
  gettimeofday(&tv, NULL);
  printf("Unix Epoch: %ld.%06d\n", tv.tv_sec, tv.tv_usec);
  return 0;
}
