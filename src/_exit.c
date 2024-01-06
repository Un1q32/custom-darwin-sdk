#include <unistd.h>

[[noreturn]] void _exit(int status) {
    syscall(1, status);
    while (1) {}
}
