#ifndef _NETINET_IN_H_
#define _NETINET_IN_H_

struct in_addr {
  unsigned int s_addr;
};

struct sockaddr_in {
  unsigned char sin_len;
  unsigned char sin_family;
  unsigned short sin_port;
  struct in_addr sin_addr;
  char sin_zero[8];
};

#endif
