#include <sys/syscall.h>
#include <unistd.h>

gid_t getgid(void) {
    return syscall(SYS_getgid);
}
