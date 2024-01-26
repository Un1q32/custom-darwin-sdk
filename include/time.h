#ifndef _TIME_H_
#define _TIME_H_

typedef long time_t;

struct timespec {
  time_t tv_sec;
  long tv_nsec;
};

#endif
