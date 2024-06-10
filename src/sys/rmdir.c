#include <sys/syscall.h>
#include <unistd.h>

int rmdir(const char *path) { return syscall(SYS_rmdir, path); }
