#include <stdio.h>
#include <unistd.h>

int fputc(int c, FILE *stream) {
    char ch = c;
    write(stream->_file, &ch, 1);
    return c;
}
