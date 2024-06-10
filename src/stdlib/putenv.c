#include <stdlib.h>

int putenv(char *string) { return _putenv(string, 1); }
