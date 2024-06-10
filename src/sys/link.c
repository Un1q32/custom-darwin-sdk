#include <sys/syscall.h>
#include <unistd.h>

int link(const char *oldpath, const char *newpath) {
  return syscall(SYS_link, oldpath, newpath);
}
