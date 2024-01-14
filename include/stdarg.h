#ifndef _STDARG_H_
#define _STDARG_H_

#if __has_include_next(<stdarg.h>)
#include_next <stdarg.h>
#endif

#ifndef va_copy
#define va_copy __builtin_va_copy
#endif

#endif
