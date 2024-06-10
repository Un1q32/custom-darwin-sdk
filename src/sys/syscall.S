#if defined(__x86_64__) || defined(__i386__)
.intel_syntax noprefix
#endif

.globl _syscall
.align 2

_syscall:
#if defined(__arm__)
  mov r12, sp
  stmdb sp!, {r4,r5,r6,r8}
  ldmia r12, {r4,r5,r6}
  mov r12, #0
  swi 0x80
  ldmia sp!, {r4,r5,r6,r8}
  bcc __syscall_success
  b __syscall_error
#elif defined(__arm64__)
  ldp x1, x2, [sp]
  ldp x3, x4, [sp, #0x10]
  ldp x5, x6, [sp, #0x20]
  ldr x7, [sp, #0x30]
  mov x16, #0x0
  svc #0x80
  b.lo 2f
  b __syscall_error
2:
  b __syscall_success
#elif defined(__x86_64__)
  mov eax, 0x2000000
  mov r10, rcx
  syscall
  mov rdi, rax
  jb __syscall_error
  mov rsi, rdx
  jmp __syscall_success
#elif defined(__i386__)
  pop ecx
  pop eax
  push ecx
  int 128
  mov dword ptr [esp], eax
  mov dword ptr [esp + 4], edx
  push ecx
  jc __syscall_error
  jmp __syscall_success
#else
#error architecture not supported
#endif

.subsections_via_symbols
