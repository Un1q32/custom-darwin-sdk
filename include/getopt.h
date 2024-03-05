#ifndef _GETOPT_H_
#define _GETOPT_H_

extern char *optarg;
extern int optind, opterr, optopt, optreset;

extern int getopt(int, char *const[], const char *);

#endif
