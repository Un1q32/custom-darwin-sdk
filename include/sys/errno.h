#ifndef _SYS_ERRNO_H_
#define _SYS_ERRNO_H_

#define EPERM         1
#define ENOENT        2
#define ENOMEM       12
#define EACCES       13
#define EFAULT       14
#define EBUSY        16
#define EEXIST       17
#define ENOTDIR      20
#define EISDIR       21
#define ENOTTY       25
#define EROFS        30
#define ERANGE       34
#define ELOOP        62
#define ENAMETOOLONG 63
#define ENOSYS       78
#define EOVERFLOW    84
#define EBADEXEC     85
#define EBADARCH     86
#define ESHLIBVERS   87
#define EBADMACHO    88

extern int errno;

#endif
