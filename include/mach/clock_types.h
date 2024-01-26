#ifndef _MACH_CLOCK_TYPES_H_
#define _MACH_CLOCK_TYPES_H_

#define SYSTEM_CLOCK 0
#define CALENDAR_CLOCK 1
#define REALTIME_CLOCK 0

#define NSEC_PER_USEC 1000
#define USEC_PER_SEC 1000000
#define NSEC_PER_SEC 1000000000

typedef int clock_res_t;

struct mach_timespec {
  unsigned int tv_sec;
  clock_res_t tv_nsec;
};

typedef struct mach_timespec mach_timespec_t;

#endif
