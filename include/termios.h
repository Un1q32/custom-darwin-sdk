#ifndef _TERMIOS_H_
#define _TERMIOS_H_

#include <sys/termios.h>

extern int tcgetattr(int, struct termios *);
extern int tcsetattr(int, int, const struct termios *);

#endif
