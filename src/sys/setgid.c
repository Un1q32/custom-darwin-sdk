#include <sys/syscall.h>
#include <unistd.h>

int setgid(gid_t gid) { return syscall(SYS_setgid, gid); }
