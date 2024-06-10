#include <sys/syscall.h>
#include <unistd.h>

int setuid(uid_t uid) { return syscall(SYS_setuid, uid); }
