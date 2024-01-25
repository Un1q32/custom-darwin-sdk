#include <stdlib.h>

int NXArgc = 0;
char **NXArgv = NULL;
char **environ = NULL;
char *__progname = NULL;

int *_NSGetArgc(void) { return &NXArgc; }
char ***_NSGetArgv(void) { return &NXArgv; }
char ***_NSGetEnviron(void) { return &environ; }
char **_NSGetProgname(void) { return &__progname; }
