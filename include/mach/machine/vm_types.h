#ifndef _MACH_MACHINE_VM_TYPES_H_
#define _MACH_MACHINE_VM_TYPES_H_

#if defined(__arm__)
#include <mach/arm/vm_types.h>
#else
#error architecture not supported
#endif

#endif
