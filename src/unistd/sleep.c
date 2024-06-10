#include <stdlib.h>
#include <time.h>

unsigned int sleep(unsigned int seconds) {
  struct timespec ts;
  ts.tv_sec = seconds;
  ts.tv_nsec = 0;
  return nanosleep(&ts, NULL);
}
