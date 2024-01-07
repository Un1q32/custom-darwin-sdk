#ifndef _STDINT_H_
#define _STDINT_H_

#if __LP64__
#define __WORDSIZE 64
#else
#define __WORDSIZE 32
#endif

#define INT8_MAX  127
#define INT16_MAX 32767
#define INT32_MAX 2147483647
#define INT64_MAX 9223372036854775807LL

#define INT8_MIN  -128
#define INT16_MIN -32768
#define INT32_MIN (-INT32_MAX-1)
#define INT64_MIN (-INT64_MAX-1)

#if __WORDSIZE == 64
#define PTRDIFF_MIN INT64_MIN
#define PTRDIFF_MAX INT64_MAX
#else
#define PTRDIFF_MIN INT32_MIN
#define PTRDIFF_MAX INT32_MAX
#endif

#endif
