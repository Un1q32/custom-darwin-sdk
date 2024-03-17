#ifndef _SYS_STAT_H_
#define _SYS_STAT_H_

#include <sys/types.h>
#include <time.h>

#define S_IWUSR 0000200
#define S_IWGRP 0000020
#define S_IWOTH 0000002

#define _STRUCT_STAT                                                           \
  {                                                                            \
    dev_t st_dev;                                                              \
    mode_t st_mode;                                                            \
    nlink_t st_nlink;                                                          \
    ino_t st_ino;                                                              \
    uid_t st_uid;                                                              \
    gid_t st_gid;                                                              \
    dev_t st_rdev;                                                             \
    time_t st_atime;                                                           \
    long st_atimensec;                                                         \
    time_t st_mtime;                                                           \
    long st_mtimensec;                                                         \
    time_t st_ctime;                                                           \
    long st_ctimensec;                                                         \
    time_t st_birthtime;                                                       \
    long st_birthtimensec;                                                     \
    off_t st_size;                                                             \
    blkcnt_t st_blocks;                                                        \
    blksize_t st_blksize;                                                      \
    unsigned int st_flags;                                                     \
    unsigned int st_gen;                                                       \
    int st_lspare;                                                             \
    long long st_qspare[2];                                                    \
  }

typedef unsigned long long ino_t;
typedef unsigned short nlink_t;

struct stat _STRUCT_STAT;
struct stat64 _STRUCT_STAT;

extern int mkdir(const char *, mode_t);
extern int mkdirat(int, const char *, mode_t);
extern int stat(const char *, struct stat *);
extern int stat64(const char *, struct stat64 *);

#endif
