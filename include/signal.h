#ifndef _SIGNAL_H_
#define _SIGNAL_H_

#include <sys/signal.h>

extern void (*signal(int, void (*)(int)))(int);
extern int kill(pid_t, int);

#endif
