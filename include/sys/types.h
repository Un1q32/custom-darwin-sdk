#ifndef _SYS_TYPES_H_
#define _SYS_TYPES_H_

#include <stddef.h>

#ifdef __LP64__
#define __PTHREAD_MUTEX_SIZE__ 56
#else
#define __PTHREAD_MUTEX_SIZE__ 40
#endif

struct _opaque_pthread_mutex_t {
  long __sig;
  char __opaque[__PTHREAD_MUTEX_SIZE__];
};

typedef long ssize_t;
typedef long long quad_t;
typedef unsigned long long u_quad_t;
typedef long long off_t;
typedef off_t fpos_t;
typedef unsigned short mode_t;
typedef int pid_t;
typedef int suseconds_t;
typedef unsigned int useconds_t;
typedef unsigned long clock_t;
typedef int dev_t;
typedef unsigned int uid_t;
typedef unsigned int gid_t;
typedef int blksize_t;
typedef long long blkcnt_t;
typedef int errno_t;
typedef size_t rsize_t;
typedef struct _opaque_pthread_mutex_t pthread_mutex_t;

#endif
