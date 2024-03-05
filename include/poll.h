#ifndef _POLL_H_
#define _POLL_H_

#define POLLIN 0x0001
#define POLLOUT 0x0004

typedef unsigned int nfds_t;

struct pollfd {
  int fd;
  short events;
  short revents;
};

extern int poll(struct pollfd[], nfds_t, int);

#endif
