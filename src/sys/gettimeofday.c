#include <stdlib.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <unistd.h>

int gettimeofday(struct timeval *tv, void *tz) {
  if (tv != NULL) {
    long ret = syscall(SYS_gettimeofday, tv, 0);
    if (ret == -1)
      return -1;
    else if (ret != 0) {
      tv->tv_sec = ret;
      tv->tv_usec = _syscallret2;
    }
  }
  if (tz != NULL) {
    struct timezone *tmp_tz = (struct timezone *)tz;
    tmp_tz->tz_minuteswest = 0;
    tmp_tz->tz_dsttime = 0;
  }
  return 0;
}
