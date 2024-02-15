#include <unistd.h>

int main() {
    write(STDOUT_FILENO, "Hello, world!\n", 14);
    return 0;
}
