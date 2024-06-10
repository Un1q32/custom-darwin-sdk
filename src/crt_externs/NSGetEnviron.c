extern char **environ;

char ***_NSGetEnviron(void) { return &environ; }
