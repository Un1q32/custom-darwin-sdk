#if defined(__x86_64__) || defined(__i386__)
.intel_syntax noprefix
#endif

.globl start
.align 2

start:
#if defined(__arm__)
  ldr r0, [sp]
  add r1, sp, #4
  add r4, r0, #1
  add r2, r1, r4, lsl #2
  bic sp, sp, #15
  bl __start
  .long 0xe1200070
#elif defined(__arm64__)
  mov x5, sp
  ldr x0, [x5]
  add x1, x5, #8
  add x4, x0, #1
  add x2, x1, x4, lsl #3
  and sp, x5, #~15
  bl __start
  brk #0
#elif defined(__x86_64__)
  push 0
  mov rbp, rsp
  and rsp, -16
  mov rdi, qword ptr [rbp + 8]
  lea rsi, [rbp + 16]
  mov edx, edi
  add edx, 1
  shl edx, 3
  add rdx, rsi
  call __start
  hlt
#elif defined(__i386__)
  push 0
  mov ebp, esp
  and esp, -16
  sub esp, 16
  mov ebx, dword ptr [ebp + 4]
  mov dword ptr [esp], ebx
  lea ecx, [ebp + 8]
  mov dword ptr [esp + 4], ecx
  add ebx, 1
  shl ebx, 2
  add ebx, ecx
  mov dword ptr [esp + 8], ebx
  call __start
  hlt
#else
#error architecture not supported
#endif

.subsections_via_symbols
