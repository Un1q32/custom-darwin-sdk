#include <sys/syscall.h>
#include <unistd.h>

int fchdir(int fd) { return syscall(SYS_fchdir, fd); }
