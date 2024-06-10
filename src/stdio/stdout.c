#include <stdio.h>
#include <unistd.h>

static char stdout_buf[BUFSIZ];

FILE _stdout = {STDOUT_FILENO, __SWR, stdout_buf, 0, 0};

FILE *stdout = &_stdout;
