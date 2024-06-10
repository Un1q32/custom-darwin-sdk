#include <stdarg.h>
#include <sys/syscall.h>
#include <unistd.h>

int ioctl(int fd, unsigned long request, ...) {
  va_list va_args;
  va_start(va_args, request);
  void *arg = va_arg(va_args, void *);
  va_end(va_args);
  return syscall(SYS_ioctl, fd, request, arg);
}
