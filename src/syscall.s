#if defined(__arm__)

.align 2

.global _syscall

/*
 * XNU arm32 syscall convention:
 * r12: syscall number
 * r0-r6: arguements
 * r0-r1: return values
 */

_syscall:
  mov r12, sp
  push {r4,r5,r6,r8}
  ldm r12, {r4,r5,r6}
  mov r12, #0
  svc 0x80
  pop {r4,r5,r6,r8}
  bcc __syscall_success
  b __syscall_error

.subsections_via_symbols

#elif defined(__x86_64__)

.align 4

.global _syscall

_syscall:
  movl $0x2000000, %eax
  movq %rcx, %r10
  syscall
  jb __syscall_success
  jmp __syscall_error
  retq

.subsections_via_symbols

#else
#error architecture not supported
#endif
