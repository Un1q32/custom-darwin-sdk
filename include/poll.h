#ifndef _POLL_H_
#define _POLL_H_

#include <sys/cdefs.h>
#include <sys/poll.h>

__BEGIN_DECLS
extern int poll(struct pollfd[], nfds_t, int);
__END_DECLS

#endif
