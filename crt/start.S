/*
 * Copyright (c) 1999-2009 Apple Inc. All rights reserved.
 *
 * Portions Copyright (c) 1999 Apple Computer, Inc.  All Rights
 * Reserved.  This file contains Original Code and/or Modifications of
 * Original Code as defined in and that are subject to the Apple Public
 * Source License Version 1.1 (the "License").  You may not use this file
 * except in compliance with the License.  Please obtain a copy of the
 * License at http://www.apple.com/publicsource and read it before using
 * this file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON- INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 */

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
