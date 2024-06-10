#include <sys/stat.h>
#include <sys/syscall.h>
#include <unistd.h>

int lstat(const char *path, struct stat *buf) {
  return syscall(SYS_lstat, path, buf);
}
