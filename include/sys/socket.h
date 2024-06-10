#ifndef _SYS_SOCKET_H_
#define _SYS_SOCKET_H_

#include <stddef.h>
#include <sys/cdefs.h>
#include <sys/types.h>
#include <sys/uio.h>

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

struct msghdr {
  void *msg_name;
  socklen_t msg_namelen;
  struct iovec *msg_iov;
  int msg_iovlen;
  void *msg_control;
  socklen_t msg_controllen;
  int msg_flags;
};

__BEGIN_DECLS
extern int socket(int, int, int);
extern int bind(int, const struct sockaddr *, socklen_t);
extern int connect(int, const struct sockaddr *, socklen_t);
extern int listen(int, int);
extern int accept(int, struct sockaddr *, socklen_t *);
extern int shutdown(int, int);
extern int getsockopt(int, int, int, void *, socklen_t *);
extern int setsockopt(int, int, int, const void *, socklen_t);
extern ssize_t recv(int, void *, size_t, int);
extern ssize_t recvfrom(int, void *, size_t, int, struct sockaddr *,
                        socklen_t *);
extern ssize_t recvmsg(int, struct msghdr *, int);
__END_DECLS

#endif
