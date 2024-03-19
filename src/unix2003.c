/* https://stackoverflow.com/a/26728795 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

FILE *fopen_UNIX2003(const char *filename,
                     const char *mode) __asm__("_fopen$UNIX2003");
FILE *fopen_UNIX2003(const char *filename, const char *mode) {
  return fopen(filename, mode);
}

int fputs_UNIX2003(const char *res1, FILE *res2) __asm__("_fputs$UNIX2003");
int fputs_UNIX2003(const char *res1, FILE *res2) { return fputs(res1, res2); }

int nanosleep_UNIX2003(int val) __asm__("_nanosleep$UNIX2003");
int nanosleep_UNIX2003(int val) { return usleep(val); }

char *strerror_UNIX2003(int errornum) __asm__("_strerror$UNIX2003");
char *strerror_UNIX2003(int errornum) { return strerror(errornum); }

double strtod_UNIX2003(const char *nptr,
                       char **endptr) __asm__("_strtod$UNIX2003");
double strtod_UNIX2003(const char *nptr, char **endptr) {
  return strtod(nptr, endptr);
}

size_t fwrite_UNIX2003(const void *a, size_t b, size_t c,
                       FILE *d) __asm__("_fwrite$UNIX2003");
size_t fwrite_UNIX2003(const void *a, size_t b, size_t c, FILE *d) {
  return fwrite(a, b, c, d);
}
