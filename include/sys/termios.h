#ifndef _SYS_TERMIOS_H_
#define _SYS_TERMIOS_H_

#define VEOF 0
#define VEOL 1
#define VERASE 3
#define VKILL 5
#define VINTR 8
#define VQUIT 9
#define VMIN 16
#define VTIME 17
#define NCCS 20
#define IGNBRK 0x00000001
#define BRKINT 0x00000002
#define IGNPAR 0x00000004
#define PARMRK 0x00000008
#define INPCK 0x00000010
#define ISTRIP 0x00000020
#define INLCR 0x00000040
#define IGNCR 0x00000080
#define ICRNL 0x00000100
#define IXON 0x00000200
#define IXOFF 0x00000400
#define OPOST 0x00000001
#define CIGNORE 0x00000001
#define CSIZE 0x00000300
#define CS8 0x00000300
#define CSTOPB 0x00000400
#define CREAD 0x00000800
#define PARENB 0x00001000
#define PARODD 0x00002000
#define HUPCL 0x00004000
#define CLOCAL 0x00008000
#define ECHOE 0x00000002
#define ECHOK 0x00000004
#define ECHO 0x00000008
#define ECHONL 0x00000010
#define ISIG 0x00000080
#define ICANON 0x00000100
#define IEXTEN 0x00000400

#define NOFLSH 0x80000000

#define TCSANOW 0
#define TCSADRAIN 1
#define TCSAFLUSH 2
#define TCSASOFT 0x10

#define TCIFLUSH 1

#define B0 0
#define B50 50
#define B75 75
#define B110 110
#define B134 134
#define B150 150
#define B200 200
#define B300 300
#define B600 600
#define B1200 1200
#define B1800 1800
#define B2400 2400
#define B4800 4800
#define B9600 9600
#define B19200 19200
#define B38400 38400

typedef unsigned long tcflag_t;
typedef unsigned char cc_t;
typedef unsigned long speed_t;

struct termios {
  tcflag_t c_iflag;
  tcflag_t c_oflag;
  tcflag_t c_cflag;
  tcflag_t c_lflag;
  cc_t c_cc[NCCS];
  speed_t c_ispeed;
  speed_t c_ospeed;
};

#endif
