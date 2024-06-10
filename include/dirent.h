#ifndef _DIRENT_H_
#define _DIRENT_H_

#include <sys/cdefs.h>
#include <sys/dirent.h>
#include <sys/types.h>

struct _telldir;

typedef struct {
  int __dd_fd;
  long __dd_loc;
  long __dd_size;
  char *__dd_buf;
  int __dd_len;
  long __dd_seek;
  long __dd_rewind;
  int __dd_flags;
  pthread_mutex_t __dd_lock;
  struct _telldir *__dd_td;
} DIR;

__BEGIN_DECLS
extern DIR *opendir(const char *);
extern int closedir(DIR *);
extern struct dirent *readdir(DIR *);
__END_DECLS

#endif
