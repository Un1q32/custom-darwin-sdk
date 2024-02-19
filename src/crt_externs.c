extern int NXArgc;
extern char **NXArgv;
extern char **environ;
extern char *__progname;

int *_NSGetArgc(void) { return &NXArgc; }
char ***_NSGetArgv(void) { return &NXArgv; }
char ***_NSGetEnviron(void) { return &environ; }
char **_NSGetProgname(void) { return &__progname; }
