#include <termios.h>

int isatty(int fd) {
  struct termios dummy;
  return tcgetattr(fd, &dummy) == 0;
}
