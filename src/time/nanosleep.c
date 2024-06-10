#include <errno.h>
#include <stdlib.h>
#include <sys/time.h>

/* TODO: this works, but it pins the CPU at 100% usage, find out how apple does
 * it */

int nanosleep(const struct timespec *req, struct timespec *rem) {
  if (req->tv_nsec < 0 || req->tv_nsec >= 1000000000) {
    errno = EINVAL;
    return -1;
  }

  struct timeval tv;
  gettimeofday(&tv, NULL);
  unsigned long long now = tv.tv_sec * 1000000000ULL + tv.tv_usec * 1000ULL;
  unsigned long long end = req->tv_sec * 1000000000ULL + req->tv_nsec + now;

  while (now < end) {
    gettimeofday(&tv, NULL);
    now = tv.tv_sec * 1000000000ULL + tv.tv_usec * 1000ULL;
  }

  if (rem != NULL) {
    rem->tv_sec = (end - now) / 1000000000ULL;
    rem->tv_nsec = (end - now) % 1000000000ULL;
  }
  return 0;
}
