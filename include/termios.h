#ifndef _TERMIOS_H_
#define _TERMIOS_H_

#include <sys/cdefs.h>
#include <sys/termios.h>

__BEGIN_DECLS
extern int tcgetattr(int, struct termios *);
extern int tcsetattr(int, int, const struct termios *);
extern speed_t cfgetospeed(const struct termios *);
extern speed_t cfgetispeed(const struct termios *);
__END_DECLS

#endif
