.globl start
.align 2

#if defined(__arm__)

start:
  ldr r0, [sp]
  add r1, sp, #4
  add r4, r0, #1
  add r2, r1, r4, lsl #2
  bic sp, sp, #15
  bl __start
  .long 0xe1200070

#elif defined(__x86_64__)

start:
  pushq $0
  movq %rsp, %rbp
  andq $-16, %rsp
  movq 8(%rbp), %rdi
  leaq 16(%rbp), %rsi
  movl %edi, %edx
  addl $1, %edx
  sall $3, %edx
  addq %rsi, %rdx
  call __start
  hlt

#else
#error architecture not supported
#endif

.subsections_via_symbols
