#include <ctype.h>

int toupper(int c) { return islower(c) ? c - 32 : c; }
