#include <libgen.h>
#include <stdlib.h>
extern int main(int argc, const char *argv[], const char *envp[]);

extern int NXArgc;
extern const char **NXArgv;
extern const char **environ;
extern const char *__progname;

void start(void) __asm__("start");
void start(void) {
  int argc = 0;
  const char **argv = (const char **)(&argc + 4);
  while (argv[argc] != NULL)
    argc++;
  const char **envp = argv + argc + 1;
  NXArgc = argc;
  NXArgv = argv;
  environ = envp;
  __progname = ((argv[0] != NULL) ? basename((char *)argv[0]) : "");
  exit(main(argc, argv, envp));
}
