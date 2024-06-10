#include <sys/socket.h>
#include <sys/syscall.h>
#include <unistd.h>

ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags) {
  return syscall(SYS_recvmsg, sockfd, msg, flags);
}
