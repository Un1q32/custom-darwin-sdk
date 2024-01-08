#include <stdarg.h>
#include <stddef.h>
#include <sys/syscall.h>
#include <sys/types.h>

long syscall(long number, ...) {
    long ret;
    long args[6];
    va_list va_args;
    va_start(va_args, number);
    for (int i = 0; i < 6; i++)
        args[i] = va_arg(va_args, long);
    va_end(va_args);
    asm(
        "mov r12, %[number];"
        "ldm %[args], {r0-r5};"
        "svc #0x80;"
        "mov %[ret], r0;"
        : [ret] "=r"(ret)
        : [number] "r"(number), [args] "r"(args)
        : "r12", "r0", "r1", "r2", "r3", "r4", "r5"
    );
    return ret;
}

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset) {
    return (void *)syscall(SYS_mmap, addr, length, prot, flags, fd, offset);
}

int munmap(void *addr, size_t length) {
    return syscall(SYS_munmap, addr, length);
}

ssize_t read(int fd, void *buf, size_t count) {
    return syscall(SYS_read, fd, buf, count);
}

ssize_t write(int fd, const void *buf, size_t count) {
    return syscall(SYS_write, fd, buf, count);
}

[[noreturn]] void _exit(int status) {
    syscall(SYS_exit, status);
    while (1) {}
}
