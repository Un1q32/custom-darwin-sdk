extern char **NXArgv;

char ***_NSGetArgv(void) { return &NXArgv; }
