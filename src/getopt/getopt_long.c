#include <getopt.h>
#include <stdio.h>
#include <string.h>

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

  const char *opt = arg + 1;
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
