#include <stdlib.h>
#include <sys/wait.h>

pid_t wait(int *status) { return wait3(status, 0, NULL); }
