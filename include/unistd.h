#ifndef _UNISTD_H_
#define _UNISTD_H_

#include <stddef.h>
#include <sys/types.h>

#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

extern void _exit(int);
extern ssize_t write(int, const void *, size_t);
extern long syscall(long, ...);

#endif
