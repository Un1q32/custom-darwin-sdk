#include <sys/socket.h>
#include <sys/syscall.h>
#include <unistd.h>

int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
  return syscall(SYS_connect, sockfd, addr, addrlen);
}
