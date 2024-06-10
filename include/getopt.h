#ifndef _GETOPT_H_
#define _GETOPT_H_

#include <sys/cdefs.h>
#include <unistd.h>

struct option {
  const char *name;
  int has_arg;
  int *flag;
  int val;
};

__BEGIN_DECLS
extern int getopt_long(int, char *const[], const char *, const struct option *,
                       int *);
__END_DECLS

#endif
