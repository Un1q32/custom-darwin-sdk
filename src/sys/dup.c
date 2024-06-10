#include <sys/syscall.h>
#include <unistd.h>

int dup(int oldfd) { return syscall(SYS_dup, oldfd); }
