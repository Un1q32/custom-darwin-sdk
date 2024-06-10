#include <sys/socket.h>
#include <sys/syscall.h>
#include <unistd.h>

int setsockopt(int sockfd, int level, int optname, const void *optval,
               socklen_t optlen) {
  return syscall(SYS_setsockopt, sockfd, level, optname, optval, optlen);
}
