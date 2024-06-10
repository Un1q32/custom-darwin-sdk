#include <sys/ioctl.h>
#include <sys/types.h>

int tcsetpgrp(int fd, pid_t pgrp_id) { return ioctl(fd, TIOCSPGRP, &pgrp_id); }
