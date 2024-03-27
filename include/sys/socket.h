#ifndef _SYS_SOCKET_H_
#define _SYS_SOCKET_H_

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
extern int shutdown(int, int);

#endif
