#include <sys/syscall.h>
#include <unistd.h>

int socket(int domain, int type, int protocol) {
  return syscall(SYS_socket, domain, type, protocol);
}
