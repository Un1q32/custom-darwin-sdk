#ifndef _GETOPT_H_
#define _GETOPT_H_

extern char *optarg;
extern int optind, opterr, optopt, optreset;

struct option {
  const char *name;
  int has_arg;
  int *flag;
  int val;
};

extern int getopt(int, char *const[], const char *);
extern int getopt_long(int, char *const[], const char *, const struct option *,
                       int *);

#endif
