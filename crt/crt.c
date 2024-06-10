#include <stdlib.h>

extern int main(int, const char *[], const char *[], const char *[]);

int NXArgc = 0;
const char **NXArgv = NULL;
const char **environ = NULL;
const char *__progname = NULL;

void _start(int argc, const char *argv[], const char *envp[]) {
  NXArgc = argc;
  NXArgv = argv;
  environ = envp;

  if (argv[0] != NULL) {
    __progname = argv[0];
    const char *p;
    for (p = argv[0]; *p; p++)
      if (*p == '/')
        __progname = p + 1;
  } else
    __progname = "";

  const char **apple = envp;
  while (*apple != NULL)
    apple++;
  apple++;

  exit(main(argc, argv, envp, apple));
}
