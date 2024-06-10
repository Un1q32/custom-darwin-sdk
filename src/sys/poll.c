#include <poll.h>
#include <sys/syscall.h>
#include <unistd.h>

int poll(struct pollfd *fds, nfds_t nfds, int timeout) {
  return syscall(SYS_poll, fds, nfds, timeout);
}
