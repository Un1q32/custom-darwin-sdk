#ifndef _SYS_TIME_H_
#define _SYS_TIME_H_

#include <sys/types.h>
#include <time.h>

struct timeval {
  time_t tv_sec;
  suseconds_t tv_usec;
};

struct timezone {
  int tz_minuteswest;
  int tz_dsttime;
};

extern int gettimeofday(struct timeval *, struct timezone *);
extern int settimeofday(const struct timeval *, const struct timezone *);

#endif
