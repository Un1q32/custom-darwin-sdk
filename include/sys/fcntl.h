#ifndef _SYS_FCNTL_H_
#define _SYS_FCNTL_H_

#define O_RDONLY   0x0000
#define O_WRONLY   0x0001
#define O_RDWR     0x0002
#define O_APPEND   0x0008
#define O_CREAT    0x0200
#define O_EXCL     0x0800
#define O_NOFOLLOW 0x0100

extern int open(const char *, int, ...);

#endif
