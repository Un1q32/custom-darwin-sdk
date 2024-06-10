#include <stdarg.h>
#include <unistd.h>

int execlp(const char *filename, const char *arg, ...) {
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
  va_end(va_args);
  return execvp(filename, argv);
}
