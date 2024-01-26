#ifndef _MACHINE_PARAM_H_
#define _MACHINE_PARAM_H_

#if defined(__arm__)
#include <machine/arm/param.h>
#else
#error architecture not supported
#endif

#endif
