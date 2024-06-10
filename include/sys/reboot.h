#ifndef _SYS_REBOOT_H_
#define _SYS_REBOOT_H_

#include <sys/cdefs.h>

#define RB_AUTOBOOT 0
#define RB_ASKNAME 0x01
#define RB_SINGLE 0x02
#define RB_NOSYNC 0x04
#define RB_HALT 0x08
#define RB_INITNAME 0x10
#define RB_DFLTROOT 0x20
#define RB_ALTBOOT 0x40
#define RB_UNIPROC 0x80
#define RB_SAFEBOOT 0x100
#define RB_UPSDELAY 0x200
#define RB_QUICK 0x400
#define RB_PANIC 0x800
#define RB_PANIC_ZPRINT 0x1000
#define RB_PANIC_FORCERESET 0x2000

__BEGIN_DECLS
extern int reboot(int);
__END_DECLS

#endif
