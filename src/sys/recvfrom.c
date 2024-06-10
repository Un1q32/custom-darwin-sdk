#include <sys/socket.h>
#include <sys/syscall.h>
#include <unistd.h>

ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
                 struct sockaddr *src_addr, socklen_t *addrlen) {
  return syscall(SYS_recvfrom, sockfd, buf, len, flags, src_addr, addrlen);
}
