#include <sys/syscall.h>
#include <unistd.h>

int issetugid(void) { return syscall(SYS_issetugid); }
