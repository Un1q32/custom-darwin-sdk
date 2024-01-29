#include <errno.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

int nanosleep(const struct timespec *req, struct timespec *rem) {
  if (req->tv_nsec < 0 || req->tv_nsec >= 1000000000) {
    errno = EINVAL;
    return -1;
  }

  long long nsec = req->tv_sec * 1000000000ULL + req->tv_nsec;

  struct timeval tv;
  gettimeofday(&tv, NULL);
  unsigned long long start = tv.tv_sec * 1000000000ULL + tv.tv_usec * 1000ULL;
  unsigned long long end = start + nsec;
  while (start < end) {
    gettimeofday(&tv, NULL);
    start = tv.tv_sec * 1000000000ULL + tv.tv_usec * 1000ULL;
  }
  if (rem != NULL) {
    rem->tv_sec = (end - start) / 1000000000ULL;
    rem->tv_nsec = (end - start) % 1000000000ULL;
  }
  return 0;
}

time_t time(time_t *tloc) {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  if (tloc != NULL) {
    *tloc = tv.tv_sec;
  }
  return tv.tv_sec;
}
