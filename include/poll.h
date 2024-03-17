#ifndef _POLL_H_
#define _POLL_H_

#include <sys/poll.h>

extern int poll(struct pollfd[], nfds_t, int);

#endif
