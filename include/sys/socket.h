#ifndef _SYS_SOCKET_H_
#define _SYS_SOCKET_H_

typedef unsigned int socklen_t;

struct sockaddr {
  unsigned char sa_len;
  unsigned char sa_family;
  char data[14];
};

extern int bind(int, const struct sockaddr *, socklen_t);
extern int shutdown(int, int);

#endif
