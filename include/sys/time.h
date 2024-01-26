#ifndef _SYS_TIME_H_
#define _SYS_TIME_H_

#include <sys/types.h>
#include <time.h>

struct timeval {
  time_t tv_sec;
  suseconds_t tv_usec;
};

#endif
