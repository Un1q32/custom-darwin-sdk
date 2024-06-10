#include <sys/stat.h>
#include <sys/syscall.h>
#include <unistd.h>

int stat64(const char *path, struct stat64 *buf) {
  return syscall(SYS_stat64, path, buf);
}
