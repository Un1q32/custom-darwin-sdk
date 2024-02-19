#include <libgen.h>
#include <stdlib.h>

extern int main(int argc, const char *argv[], const char *envp[]);

int NXArgc = 0;
const char **NXArgv = NULL;
const char **environ = NULL;
const char *__progname = NULL;

void _start(int argc, const char **argv, const char **envp) {
  NXArgc = argc;
  NXArgv = argv;
  environ = envp;
  __progname = ((argv[0] != NULL) ? basename((char *)argv[0]) : "");
  exit(main(argc, argv, envp));
}
