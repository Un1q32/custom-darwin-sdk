#include <sys/syscall.h>
#include <unistd.h>

pid_t getpgrp(void) { return syscall(SYS_getpgrp); }
