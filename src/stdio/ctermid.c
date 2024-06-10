#include <stdio.h>
#include <string.h>

char *ctermid(char *buf) {
  static char staticbuf[L_ctermid];
  if (buf == NULL) {
    strcpy(staticbuf, "/dev/tty");
    return staticbuf;
  } else {
    strcpy(buf, "/dev/tty");
    return buf;
  }
}
