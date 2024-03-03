#include <sys/ioctl.h>
#include <termios.h>

int tcgetattr(int fd, struct termios *termios_p) {
  return ioctl(fd, TIOCGETA, termios_p);
}

int tcsetattr(int fd, int optional_actions, const struct termios *termios_p) {
  (void)optional_actions;
  return ioctl(fd, TIOCSETA, termios_p);
}
