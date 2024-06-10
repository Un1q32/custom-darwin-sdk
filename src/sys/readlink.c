#include <sys/syscall.h>
#include <unistd.h>

ssize_t readlink(const char *path, char *buf, size_t bufsiz) {
  return syscall(SYS_readlink, path, buf, bufsiz);
}
