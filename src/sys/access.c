#include <sys/syscall.h>
#include <unistd.h>

int access(const char *path, int mode) {
  return syscall(SYS_access, path, mode);
}
