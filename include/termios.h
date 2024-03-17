#ifndef _TERMIOS_H_
#define _TERMIOS_H_

#define VMIN 16
#define VTIME 17
#define INPCK 0x00000010
#define ISTRIP 0x00000020
#define ICRNL 0x00000100
#define IXON 0x00000200
#define OPOST 0x00000001
#define CS8 0x00000300
#define TCSANOW 0
#define TCSAFLUSH 2
#define IGNBRK 0x00000001
#define BRKINT 0x00000002
#define ISIG 0x00000080
#define ICANON 0x00000100
#define IEXTEN 0x00000400
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
