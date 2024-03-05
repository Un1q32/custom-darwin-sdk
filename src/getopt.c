#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
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

int getopt_long(int argc, char *const argv[], const char *optstring,
                const struct option *longopts, int *longindex) {
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
  if (opt[0] == '-' && opt[1] == '\0') {
    optind++;
    return -1;
  }

  if (opt[0] == '-' && opt[1] != '\0') {
    char *eq = strchr(opt, '=');
    if (eq != NULL) {
      *eq = '\0';
      optarg = eq + 1;
    } else
      optarg = NULL;

    for (int i = 0; longopts[i].name != NULL; i++) {
      if (strcmp(opt + 1, longopts[i].name) == 0) {
        if (longopts[i].has_arg) {
          if (optarg == NULL) {
            optind++;
            if (optind >= argc) {
              if (opterr)
                fprintf(stderr, "%s: option requires an argument -- %s\n",
                        argv[0], opt + 1);
              return '?';
            }
            optarg = argv[optind];
          }
        } else {
          if (optarg != NULL) {
            if (opterr)
              fprintf(stderr, "%s: option does not allow an argument -- %s\n",
                      argv[0], opt + 1);
            return '?';
          }
        }

        if (longindex != NULL)
          *longindex = i;
        optind++;
        return longopts[i].val;
      }
    }

    if (opterr)
      fprintf(stderr, "%s: invalid option -- %s\n", argv[0], opt + 1);
    return '?';
  }

  return getopt(argc, argv, optstring);
}
