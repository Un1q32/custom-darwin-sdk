#include <sys/syscall.h>
#include <unistd.h>

int symlink(const char *target, const char *linkpath) {
  return syscall(SYS_symlink, target, linkpath);
}
