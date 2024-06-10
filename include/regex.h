#ifndef _REGEX_H_
#define _REGEX_H_

#include <stddef.h>
#include <sys/types.h>

typedef off_t regoff_t;

typedef struct {
  int re_magic;
  size_t re_nsub;
  const char *re_endp;
  struct re_guts *re_g;
} regex_t;

typedef struct {
  regoff_t rm_so;
  regoff_t rm_eo;
} regmatch_t;

#endif
