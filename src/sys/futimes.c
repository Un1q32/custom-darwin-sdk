#include <sys/syscall.h>
#include <sys/time.h>
#include <unistd.h>

int futimes(int fd, const struct timeval times[2]) {
  return syscall(SYS_futimes, fd, times);
}
