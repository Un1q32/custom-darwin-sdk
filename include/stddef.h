#ifndef _STDDEF_H
#define _STDDEF_H

#define NULL ((void *)0)
#ifdef __SIZE_TYPE__
typedef __SIZE_TYPE__ size_t;
#else
typedef unsigned long size_t;
#endif

#ifdef __PTRDIFF_TYPE__
typedef __PTRDIFF_TYPE__ ptrdiff_t;
#else
typedef long ptrdiff_t;
#endif

#ifdef __WINT_TYPE__
typedef __WINT_TYPE__ wint_t;
#else
typedef int wint_t;
#endif

#endif
