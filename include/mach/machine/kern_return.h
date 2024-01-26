#ifndef _MACH_MACHINE_KERN_RETURN_H_
#define _MACH_MACHINE_KERN_RETURN_H_

#if defined(__arm__)
#include <mach/arm/kern_return.h>
#else
#error architecture not supported
#endif

#endif
