#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void fmttime(struct timeval *tv) {
  unsigned long year, month, day, hour, min, sec;
  year = tv->tv_sec / 31536000 + 1970;
  month = (tv->tv_sec % 31536000) / 2592000 + 1;
  day = ((tv->tv_sec % 31536000) % 2592000) / 86400 + 1;
  hour = (((tv->tv_sec % 31536000) % 2592000) % 86400) / 3600;
  min = ((((tv->tv_sec % 31536000) % 2592000) % 86400) % 3600) / 60;
  sec = (((((tv->tv_sec % 31536000) % 2592000) % 86400) % 3600) % 60);
  printf("%lu-%lu-%lu %lu:%lu:%lu\n", year, month, day, hour, min, sec);
}

int main(int argc, char *argv[]) {
  struct timeval tv;
  struct timezone tz = {
      .tz_minuteswest = ((argv[1] != NULL) ? atoi(argv[1]) : 0),
      .tz_dsttime = 0,
  };
  gettimeofday(&tv, &tz);
  fmttime(&tv);
  return 0;
}
