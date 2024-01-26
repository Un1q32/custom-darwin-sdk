#ifndef _MACHINE_LIMITS_H_
#define _MACHINE_LIMITS_H_

#if defined(__arm__)
#include <machine/arm/limits.h>
#else
#error architecture not supported
#endif

#endif
