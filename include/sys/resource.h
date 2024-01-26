#ifndef _SYS_RESOURCE_H_
#define _SYS_RESOURCE_H_

#include <sys/time.h>

struct rusage {
  struct timeval ru_utime;
  struct timeval ru_stime;
};

#endif
