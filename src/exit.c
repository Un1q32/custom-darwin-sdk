#include <unistd.h>

[[noreturn]] void exit(int status) {
    _exit(status);
}
