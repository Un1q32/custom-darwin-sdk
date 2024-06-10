#include <stdio.h>
#include <string.h>

char *optarg = NULL;
int optind = 1;
int opterr = 1;
int optopt = '?';
int optreset = 0;

int getopt(int argc, char *const argv[], const char *optstring) {
  if (optreset) {
    optind = 1;
    optarg = NULL;
    optreset = 0;
  }

  if (optind >= argc)
    return -1;

  char *arg = argv[optind];
  if (arg[0] != '-')
    return -1;

  char *opt = arg + 1;
  char *p = strchr(optstring, *opt);
  if (p == NULL) {
    if (opterr)
      fprintf(stderr, "%s: invalid option -- %c\n", argv[0], *opt);
    optopt = *opt;
    return '?';
  }

  if (p[1] == ':') {
    optind++;
    if (optind >= argc) {
      if (opterr)
        fprintf(stderr, "%s: option requires an argument -- %c\n", argv[0],
                *opt);
      optopt = *opt;
      return '?';
    }
    optarg = argv[optind];
    optind++;
  } else {
    opt++;
    if (*opt == '\0')
      optind++;
  }

  return *p;
}
