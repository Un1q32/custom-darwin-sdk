#include <sys/socket.h>
#include <sys/syscall.h>
#include <unistd.h>

int getsockopt(int sockfd, int level, int optname, void *optval,
               socklen_t *optlen) {
  return syscall(SYS_getsockopt, sockfd, level, optname, optval, optlen);
}
