#ifndef _SYS_SOCKET_H_
#define _SYS_SOCKET_H_

#define SOCK_STREAM 1

#define SO_REUSEADDR 0x0004
#define SOL_SOCKET 0xFFFF

#define AF_INET 2

#define SHUT_WR 1
#define SHUT_RDWR 2

typedef unsigned int socklen_t;

struct sockaddr {
  unsigned char sa_len;
  unsigned char sa_family;
  char data[14];
};

extern int bind(int, const struct sockaddr *, socklen_t);
extern int listen(int, int);
extern int accept(int, struct sockaddr *, socklen_t *);
extern int shutdown(int, int);

#endif
