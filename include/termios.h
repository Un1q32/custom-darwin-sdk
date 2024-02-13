#ifndef __TERMIOS_H__
#define __TERMIOS_H__

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

#endif
