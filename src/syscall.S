.globl _syscall
.align 2

#if defined(__arm__)

_syscall:
  mov r12, sp
  stmdb sp!, {r4,r5,r6,r8}
  ldmia r12, {r4,r5,r6}
  mov r12, #0
  swi 0x80
  ldmia sp!, {r4,r5,r6,r8}
  bcc __syscall_success
  b __syscall_error

#elif defined(__x86_64__)

_syscall:
  movl $0x2000000, %eax
  movq %rcx, %r10
  syscall
  movq %rax, %rdi
  jb __syscall_error
  movq %rdx, %rsi
  jmp __syscall_success

#elif defined(__i386__)

_syscall:
  popl %ecx
  popl %eax
  pushl %ecx
  int $0x80
  movl %eax, (%esp)
  pushl %ecx
  jc __syscall_error
  retl

#else
#error architecture not supported
#endif

.subsections_via_symbols
