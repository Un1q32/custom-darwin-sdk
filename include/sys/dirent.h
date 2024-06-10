#ifndef _SYS_DIRENT_H_
#define _SYS_DIRENT_H_

#include <sys/stat.h>

#define __DARWIN_MAXNAMLEN 255

struct dirent {
  ino_t d_ino;
  unsigned short d_reclen;
  unsigned char d_type;
  unsigned char d_namlen;
  char d_name[__DARWIN_MAXNAMLEN + 1];
};

#endif
