#include <sys/syscall.h>
#include <unistd.h>

int unlink(const char *path) { return syscall(SYS_unlink, path); }
