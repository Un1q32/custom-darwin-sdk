#if defined(__arm__)

.align 4

.global __syscall
__syscall:
    mov r12, r0
    ldm r1, {r0-r5}
    svc 0x80
    bxcc lr
    b __syscall_error

.global __syscall_multiret
__syscall_multiret:
    mov r12, r0
    ldm r1, {r0-r5}
    svc 0x80
    bcc __syscall_multiret_helper
    b __syscall_error

.subsections_via_symbols

#else
#error architecture not supported
#endif
