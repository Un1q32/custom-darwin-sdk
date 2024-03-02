#ifndef _MACHINE_LIMITS_H_
#define _MACHINE_LIMITS_H_

#if defined(__arm__)
#include <machine/arm/limits.h>
#elif defined(__i386__) || defined(__x86_64__)
#include <machine/x86/limits.h>
#elif defined(__ppc__)
#include <machine/ppc/limits.h>
#else
#error architecture not supported
#endif

#endif
