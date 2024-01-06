#include <stdarg.h>

long syscall(long number, ...) {
    long ret;
    va_list args;
    va_start(args, number);
    long arg1 = va_arg(args, long);
    long arg2 = va_arg(args, long);
    long arg3 = va_arg(args, long);
    long arg4 = va_arg(args, long);
    long arg5 = va_arg(args, long);
    va_end(args);
    asm(
        "mov r12, %[number];"
        "mov r0, %[arg1];"
        "mov r1, %[arg2];"
        "mov r2, %[arg3];"
        "mov r3, %[arg4];"
        "mov r4, %[arg5];"
        "svc #0x80;"
        "mov %[ret], r0;"
        : [ret] "=r"(ret)
        : [number] "r"(number), [arg1] "r"(arg1), [arg2] "r"(arg2), [arg3] "r"(arg3), [arg4] "r"(arg4), [arg5] "r"(arg5)
    );
    return ret;
}
