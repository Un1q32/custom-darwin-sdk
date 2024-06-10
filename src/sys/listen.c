#include <sys/syscall.h>
#include <unistd.h>

int listen(int sockfd, int backlog) {
  return syscall(SYS_listen, sockfd, backlog);
}
