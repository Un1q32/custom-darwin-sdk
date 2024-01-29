#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void fmttime(struct timeval *tv) {
  long year, month, day, hour, min, sec;
  year = tv->tv_sec / 31556926 + 1970;
  month = (tv->tv_sec % 31556926) / 2629743 + 1;
  day = ((tv->tv_sec % 31556926) % 2629743) / 86400 + 1;
  hour = (((tv->tv_sec % 31556926) % 2629743) % 86400) / 3600;
  min = ((((tv->tv_sec % 31556926) % 2629743) % 86400) % 3600) / 60;
  sec = ((((tv->tv_sec % 31556926) % 2629743) % 86400) % 3600) % 60;
  printf("%ld-%ld-%ld %ld:%ld:%ld:%d\n", year, month, day, hour, min, sec,
         tv->tv_usec);
}

int main(int argc, char *argv[]) {
  (void)argc;
  struct timeval tv;
  struct timezone tz = {.tz_minuteswest =
                            ((argv[1] != NULL) ? atoi(argv[1]) : 0),
                        .tz_dsttime = ((argv[2] != NULL) ? atoi(argv[2]) : 0)};
  gettimeofday(&tv, &tz);
  fmttime(&tv);
  return 0;
}
