#include <sys/syscall.h>
#include <unistd.h>

off_t lseek(int fd, off_t offset, int whence) {
  return syscall(SYS_lseek, fd, offset, whence);
}
