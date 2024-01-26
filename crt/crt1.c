#include <libgen.h>
#include <stdlib.h>
extern int main(int argc, const char *argv[], const char *envp[]);

extern int NXArgc;
extern const char **NXArgv;
extern const char **environ;

void start(void) __asm__("start");
void start(void) {
  int argc = 0;
  const char **argv = (const char **)(&argc + 4);
  int argc2 = 0;
  while (argv[argc2] != NULL)
    argc2++;
  argc = argc2;
  const char **envp = argv + argc + 1;
  NXArgc = argc;
  NXArgv = argv;
  environ = envp;
  exit(main(argc, argv, envp));
}
