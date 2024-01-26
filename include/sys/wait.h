#ifndef _SYS_WAIT_H_
#define _SYS_WAIT_H_

#include <sys/types.h>

extern pid_t wait(int *);
extern pid_t wait3(int *, int, struct rusage *);
extern pid_t wait4(pid_t, int *, int, struct rusage *);
extern pid_t waitpid(pid_t, int *, int);

#endif
