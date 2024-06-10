#ifndef _SYS_IOCTL_H_
#define _SYS_IOCTL_H_

#include <sys/cdefs.h>
#include <sys/ttycom.h>

__BEGIN_DECLS
extern int ioctl(int, unsigned long, ...);
__END_DECLS

#endif
