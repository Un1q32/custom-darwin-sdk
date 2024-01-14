#ifndef _STDARG_H_
#define _STDARG_H_

#include_next <stdarg.h>

#ifndef va_copy
#define va_copy __builtin_va_copy
#endif

#endif
