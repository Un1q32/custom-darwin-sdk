#include <stdio.h>
#include <unistd.h>

static char stderr_buf[BUFSIZ];

FILE _stderr = {STDERR_FILENO, __SWR | __SNBF, stderr_buf, 0, 0};

FILE *stderr = &_stderr;
