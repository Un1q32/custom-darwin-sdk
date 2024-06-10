#include <sys/socket.h>
#include <sys/syscall.h>
#include <unistd.h>

int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
  return syscall(SYS_bind, sockfd, addr, addrlen);
}
