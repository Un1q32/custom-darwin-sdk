#include <stdarg.h>
#include <unistd.h>

int execle(const char *filename, const char *arg, ...) {
  va_list va_args;
  va_start(va_args, arg);
  char *argv[1024];
  argv[0] = (char *)arg;
  int i;
  for (i = 1; i < 1024; i++) {
    argv[i] = va_arg(va_args, char *);
    if (argv[i] == NULL)
      break;
  }
  char *envp[1024];
  for (i = 0; i < 1024; i++) {
    envp[i] = va_arg(va_args, char *);
    if (envp[i] == NULL)
      break;
  }
  va_end(va_args);
  return execve(filename, argv, envp);
}
