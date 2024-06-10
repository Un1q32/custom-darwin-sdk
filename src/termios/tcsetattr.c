#include <errno.h>
#include <sys/ioctl.h>
#include <termios.h>

int tcsetattr(int fd, int optional_actions, const struct termios *termios_p) {
  struct termios localterm;

  if (optional_actions & TCSASOFT) {
    localterm = *termios_p;
    localterm.c_cflag |= CIGNORE;
    termios_p = &localterm;
  }
  switch (optional_actions & ~TCSASOFT) {
  case TCSANOW:
    return ioctl(fd, TIOCSETA, termios_p);
  case TCSADRAIN:
    return ioctl(fd, TIOCSETAW, termios_p);
  case TCSAFLUSH:
    return ioctl(fd, TIOCSETAF, termios_p);
  default:
    errno = EINVAL;
    return -1;
  }
}
