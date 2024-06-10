#include <sys/syscall.h>
#include <unistd.h>

int mkdir(const char *path, mode_t mode) {
  return syscall(SYS_mkdir, path, mode);
}
