#include <errno.h>
#include <stdlib.h>
#include <sys/time.h>

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
  if (tloc != NULL)
    *tloc = tv.tv_sec;
  return tv.tv_sec;
}

struct tm *gmtime(const time_t *timep) {
  static struct tm tm;
  tm.tm_sec = *timep % 60;
  tm.tm_min = (*timep / 60) % 60;
  tm.tm_hour = (*timep / 3600) % 24;
  tm.tm_mday = (*timep / 86400) % 31 + 1;
  tm.tm_mon = (*timep / 2678400) % 12;
  tm.tm_year = *timep / 32140800;
  tm.tm_wday = (*timep / 86400) % 7;
  tm.tm_yday = (*timep / 86400) % 365;
  tm.tm_isdst = 0;
  tm.tm_gmtoff = 0;
  tm.tm_zone = "UTC";
  return &tm;
}
