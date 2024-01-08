#include <unistd.h>

void exit(int status) {
    _exit(status);
    while (1) {}
}
