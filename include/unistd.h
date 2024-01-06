#ifndef _UNISTD_H
#define _UNISTD_H 1

#include <stddef.h>
#include <sys/types.h>

extern void _exit(int);
extern ssize_t write(int, const void *, size_t);
extern long syscall(long number, ...);

#endif
