#ifndef _MACHINE_ARM_LIMITS_H_
#define _MACHINE_ARM_LIMITS_H_

#define CHAR_BIT 8

#define UINT_MAX 0xFFFFFFFF
#define INT_MAX (UINT_MAX >> 1)
#define INT_MIN (-INT_MAX - 1)

#ifdef __LP64__
#define ULONG_MAX 0xFFFFFFFFFFFFFFFFUL
#else
#define ULONG_MAX 0xFFFFFFFFUL
#endif
#define LONG_MAX (ULONG_MAX >> 1)
#define LONG_MIN (-LONG_MAX - 1)

#define ULLONG_MAX 0xFFFFFFFFFFFFFFFFULL
#define LLONG_MAX (ULLONG_MAX >> 1)
#define LLONG_MIN (-LLONG_MAX - 1)

#endif
