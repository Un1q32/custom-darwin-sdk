#include <errno.h>
#include <stdio.h>
#include <string.h>

void perror(const char *str) {
  const char *errstr = strerror(errno);
  size_t len;
  if (str != NULL)
    len = strlen(str) + strlen(errstr) + 3;
  else
    len = strlen(errstr) + 1;
  char buf[len];
  buf[0] = '\0';
  if (str != NULL) {
    strcpy(buf, str);
    strcat(buf, ": ");
  }
  strcat(buf, errstr);
  buf[len - 1] = '\n';
  fwrite(buf, 1, len, stderr);
}
