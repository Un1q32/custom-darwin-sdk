#include <sys/syscall.h>
#include <unistd.h>

int reboot(int cmd) { return syscall(SYS_reboot, cmd); }
