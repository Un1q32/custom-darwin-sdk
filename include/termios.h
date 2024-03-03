#ifndef __TERMIOS_H__
#define __TERMIOS_H__

#define TCSANOW 0

#define ICANON 0x00000100

#define ECHO 0x00000008

struct termios {
  unsigned long c_iflag;
  unsigned long c_oflag;
  unsigned long c_cflag;
  unsigned long c_lflag;
  unsigned char c_cc[20];
  unsigned long c_ispeed;
  unsigned long c_ospeed;
};

extern int tcgetattr(int, struct termios *);
extern int tcsetattr(int, int, const struct termios *);

#endif
