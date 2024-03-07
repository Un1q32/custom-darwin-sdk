#include <libgen.h>
#include <stdlib.h>

extern int main(int argc, char *argv[], char *envp[]);

int NXArgc = 0;
char **NXArgv = NULL;
char **environ = NULL;
char *__progname = NULL;

int *_NSGetArgc(void) { return &NXArgc; }
char ***_NSGetArgv(void) { return &NXArgv; }
char ***_NSGetEnviron(void) { return &environ; }
char **_NSGetProgname(void) { return &__progname; }

void _start(int argc, char *argv[], char *envp[]) {
  NXArgc = argc;
  NXArgv = argv;
  environ = envp;
  __progname = ((argv[0] != NULL) ? basename((char *)argv[0]) : "");
  exit(main(argc, argv, envp));
}
