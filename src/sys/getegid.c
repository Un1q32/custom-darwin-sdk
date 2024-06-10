#include <sys/syscall.h>
#include <unistd.h>

gid_t getegid(void) { return syscall(SYS_getegid); }
