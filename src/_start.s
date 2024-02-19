#if defined(__arm__)

.align 4

.global start

start:
  ldr r0, [sp]
  add r1, sp, #4
  add r4, r0, #8
  add r2, r1, r4, lsl #2
  bic sp, sp, #7
  bl __start
  bkpt 0

.subsections_via_symbols

#else
#error architecture not supported
#endif
