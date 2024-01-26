#ifndef _SYS_WAIT_H_
#define _SYS_WAIT_H_

#include <sys/types.h>

extern pid_t wait4(pid_t, int *, int, struct rusage *);

#endif
