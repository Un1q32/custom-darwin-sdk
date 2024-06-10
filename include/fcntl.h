#ifndef _FCNTL_H_
#define _FCNTL_H_

#include <sys/fcntl.h>
#include <sys/cdefs.h>

__BEGIN_DECLS
extern int open(const char *, int, ...);
extern int openat(int, const char *, int, ...);
extern int fcntl(int, int, ...);
__END_DECLS

#endif
