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

#define TIOCGWINSZ _IOR('t', 104, struct winsize)

#endif
