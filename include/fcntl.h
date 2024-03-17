#ifndef _FCNTL_H_
#define _FCNTL_H_

#include <sys/fcntl.h>

extern int open(const char *, int, ...);
extern int openat(int, const char *, int, ...);
extern int fcntl(int, int, ...);

#endif
