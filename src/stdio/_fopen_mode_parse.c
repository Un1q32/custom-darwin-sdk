#include <fcntl.h>
#include <stdio.h>

int _fopen_mode_parse(const char *mode) {
  int ret = 0;
  if (!mode)
    return -1;
  if (*mode == 'b')
    mode++;
  if (*mode == 'r') {
    ret = O_RDONLY;
    mode++;
    if (*mode == '+') {
      ret = O_RDWR;
      mode++;
      if (*mode == 'b')
        mode++;
    }
  } else if (*mode == 'w') {
    ret = O_WRONLY | O_CREAT | O_TRUNC;
    mode++;
    if (*mode == '+') {
      ret = O_RDWR | O_CREAT | O_TRUNC;
      mode++;
      if (*mode == 'b')
        mode++;
    }
    if (*mode == 'x') {
      ret = O_WRONLY | O_CREAT | O_EXCL;
      mode++;
    }
  } else if (*mode == 'a') {
    ret = O_WRONLY | O_CREAT | O_APPEND;
    mode++;
    if (*mode == '+') {
      ret = O_RDWR | O_CREAT | O_APPEND;
      mode++;
      if (*mode == 'b')
        mode++;
    }
  } else
    return -1;
  if (*mode == 'e') {
    ret |= O_CLOEXEC;
    mode++;
  }
  return ret;
}
