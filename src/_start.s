.global start
.align 2

#if defined(__arm__)

start:
  ldr r0, [sp]
  add r1, sp, #4
  add r4, r0, #8
  add r2, r1, r4, lsl #2
  bic sp, sp, #7
  bl __start
  bkpt 0

#else
#error architecture not supported
#endif

.subsections_via_symbols
