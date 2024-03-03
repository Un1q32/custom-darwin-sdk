#ifndef _SYS_TTYCOM_H_
#define _SYS_TTYCOM_H_

#include <sys/ioccom.h>

struct winsize {
  unsigned short ws_row;
  unsigned short ws_col;
  unsigned short ws_xpixel;
  unsigned short ws_ypixel;
};

#define IOCPARM_MASK 0x1FFF

#define TIOCGETA _IOR('t', 19, struct termios)
#define TIOCSETA _IOW('t', 20, struct termios)
#define TIOCGWINSZ _IOR('t', 104, struct winsize)

#endif
