.global _syscall
.align 2

#if defined(__arm__)

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

#elif defined(__x86_64__)

_syscall:
  movl $0x2000000, %eax
  movq %rcx, %r10
  syscall
  jb __syscall_success
  jmp __syscall_error
  retq

#else
#error architecture not supported
#endif

.subsections_via_symbols
