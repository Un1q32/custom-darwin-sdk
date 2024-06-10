#include <sys/syscall.h>
#include <sys/time.h>
#include <unistd.h>

int utimes(const char *filename, const struct timeval times[2]) {
  return syscall(SYS_utimes, filename, times);
}
