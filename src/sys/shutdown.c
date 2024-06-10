#include <sys/syscall.h>
#include <unistd.h>

int shutdown(int sockfd, int how) { return syscall(SYS_shutdown, sockfd, how); }
