#ifndef _SYS_TIME_H_
#define _SYS_TIME_H_

#include <sys/cdefs.h>
#include <sys/types.h>
#include <time.h>

#define DST_NONE 0
#define DST_USA 1
#define DST_AUST 2
#define DST_WET 3
#define DST_MET 4
#define DST_EET 5
#define DST_CAN 6

struct timeval {
  time_t tv_sec;
  suseconds_t tv_usec;
};

struct timezone {
  int tz_minuteswest;
  int tz_dsttime;
};

__BEGIN_DECLS
extern int gettimeofday(struct timeval *, void *);
__END_DECLS

#endif
