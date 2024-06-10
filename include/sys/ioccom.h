#ifndef _SYS_IOCCOM_H_
#define _SYS_IOCCOM_H_

#define IOC_OUT (unsigned int)0x40000000
#define IOC_IN (unsigned int)0x80000000

#define _IOC(inout, group, num, len)                                           \
  (inout | ((len & IOCPARM_MASK) << 16) | ((group) << 8) | (num))

#define _IOR(g, n, t) _IOC(IOC_OUT, (g), (n), sizeof(t))
#define _IOW(g, n, t) _IOC(IOC_IN, (g), (n), sizeof(t))

#endif
