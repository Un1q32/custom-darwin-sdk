#ifndef _SYSCALL_H_
#define _SYSCALL_H_

#define SYS_exit 1
#define SYS_fork 2
#define SYS_read 3
#define SYS_write 4
#define SYS_open 5
#define SYS_close 6
#define SYS_wait4 7
#define SYS_link 9
#define SYS_unlink 10
#define SYS_chdir 12
#define SYS_fchdir 13
#define SYS_mknod 14
#define SYS_chmod 15
#define SYS_chown 16
#define SYS_getfsstat 18
#define SYS_getpid 20
#define SYS_setuid 23
#define SYS_getuid 24
#define SYS_geteuid 25
#define SYS_recvmsg 27
#define SYS_sendmsg 28
#define SYS_recvfrom 29
#define SYS_accept 30
#define SYS_access 33
#define SYS_kill 37
#define SYS_dup 41
#define SYS_pipe 42
#define SYS_getegid 43
#define SYS_sigaction 46
#define SYS_getgid 47
#define SYS_ioctl 54
#define SYS_reboot 55
#define SYS_symlink 57
#define SYS_readlink 58
#define SYS_execve 59
#define SYS_munmap 73
#define SYS_getpgrp 81
#define SYS_dup2 90
#define SYS_fcntl 92
#define SYS_socket 97
#define SYS_connect 98
#define SYS_bind 104
#define SYS_setsockopt 105
#define SYS_listen 106
#define SYS_gettimeofday 116
#define SYS_getsockopt 118
#define SYS_settimeofday 122
#define SYS_shutdown 134
#define SYS_mkdir 136
#define SYS_rmdir 137
#define SYS_utimes 138
#define SYS_futimes 139
#define SYS_setgid 181
#define SYS_lstat 190
#define SYS_mmap 197
#define SYS_lseek 199
#define SYS_poll 230
#define SYS_issetugid 327
#define SYS_stat64 338

#endif
