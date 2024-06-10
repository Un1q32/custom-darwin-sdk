#ifndef _TIME_H_
#define _TIME_H_

#include <sys/cdefs.h>

typedef long time_t;

struct tm {
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;
  long tm_gmtoff;
  char *tm_zone;
};

struct timespec {
  time_t tv_sec;
  long tv_nsec;
};

__BEGIN_DECLS
extern int nanosleep(const struct timespec *, struct timespec *);
extern time_t time(time_t *);
extern struct tm *gmtime(const time_t *);
__END_DECLS

#endif
