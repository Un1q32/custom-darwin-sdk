#include <sys/syscall.h>
#include <unistd.h>

uid_t getuid(void) { return syscall(SYS_getuid); }
