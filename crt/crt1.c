#include <libgen.h>
#include <stdlib.h>
extern int main(int argc, const char *argv[], const char *envp[]);

extern int NXArgc;
extern const char **NXArgv;
extern const char **environ;
extern const char *__progname;

static const char *crt_basename(const char *path) {
  const char *base = path;
  while (*path != '\0') {
    if (*path == '/')
      base = path + 1;
    path++;
  }
  return base;
}

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
  __progname = ((argv[0] != NULL) ? crt_basename(argv[0]) : "");
  exit(main(argc, argv, envp));
}
