#include <sys/socket.h>
#include <sys/syscall.h>
#include <unistd.h>

int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
  return syscall(SYS_accept, sockfd, addr, addrlen);
}
