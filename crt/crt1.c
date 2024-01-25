#include <libgen.h>
#include <stdlib.h>
extern int main(int argc, char *argv[], char *envp[]);

extern int NXArgc;
extern char **NXArgv;
extern char **environ;
extern char *__progname;

void start(void) __asm__("start");
void start(void) {
  int argc = 0;
  char **argv = (char **)(&argc + 4);
  while (argv[argc] != NULL)
    argc++;
  char **envp = argv + argc + 1;
  NXArgc = argc;
  NXArgv = argv;
  environ = envp;
  __progname = ((argv[0] != NULL) ? basename((char *)argv[0]) : "");
  exit(main(argc, argv, envp));
}
