#ifndef _NETDB_H_
#define _NETDB_H_

#include <sys/socket.h>

#define AI_PASSIVE 0x00000001

struct addrinfo {
  int ai_flags;
  int ai_family;
  int ai_socktype;
  int ai_protocol;
  unsigned int ai_addrlen;
  char *ai_canonname;
  struct sockaddr *ai_addr;
  struct addrinfo *ai_next;
};

#endif
