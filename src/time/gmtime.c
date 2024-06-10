#include <sys/time.h>

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
