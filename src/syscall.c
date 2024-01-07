#include <stdarg.h>
#include <stddef.h>
#include <sys/syscall.h>
#include <sys/types.h>

long syscall(long number, ...) {
    long ret, arg1, arg2, arg3, arg4, arg5, arg6;
    va_list args;
    va_start(args, number);
    arg1 = va_arg(args, long);
    arg2 = va_arg(args, long);
    arg3 = va_arg(args, long);
    arg4 = va_arg(args, long);
    arg5 = va_arg(args, long);
    arg6 = va_arg(args, long);
    va_end(args);
    asm(
        "mov r12, %[number];"
        "mov r0, %[arg1];"
        "mov r1, %[arg2];"
        "mov r2, %[arg3];"
        "mov r3, %[arg4];"
        "mov r4, %[arg5];"
        "mov r5, %[arg6];"
        "svc #0x80;"
        "mov %[ret], r0;"
        : [ret] "=r"(ret)
        : [number] "r"(number), [arg1] "r"(arg1), [arg2] "r"(arg2), [arg3] "r"(arg3), [arg4] "r"(arg4), [arg5] "r"(arg5), [arg6] "r"(arg6)
    );
    return ret;
}

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset) {
    return (void *)syscall(SYS_mmap, addr, length, prot, flags, fd, offset);
}

int munmap(void *addr, size_t length) {
    return syscall(SYS_munmap, addr, length);
}

ssize_t write(int fd, const void *buf, size_t count) {
    return syscall(SYS_write, fd, buf, count);
}

[[noreturn]] void _exit(int status) {
    syscall(SYS_exit, status);
    while (1) {}
}
