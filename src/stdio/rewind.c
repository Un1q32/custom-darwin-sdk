#include <stdio.h>
#include <unistd.h>

void rewind(FILE *stream) { fseek(stream, 0, SEEK_SET); }
