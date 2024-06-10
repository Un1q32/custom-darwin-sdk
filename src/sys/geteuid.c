#include <sys/syscall.h>
#include <unistd.h>

uid_t geteuid(void) { return syscall(SYS_geteuid); }
