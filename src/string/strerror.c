#include <errno.h>

char *strerror(int errnum) {
  switch (errnum) {
  case 0:
    return "No error";
  case EPERM:
    return "Operation not permitted";
  case ENOENT:
    return "No such file or directory";
  case ESRCH:
    return "No such process";
  case EINTR:
    return "Interrupted system call";
  case EIO:
    return "I/O error";
  case ENXIO:
    return "No such device or address";
  case E2BIG:
    return "Argument list too long";
  case ENOEXEC:
    return "Exec format error";
  case EBADF:
    return "Bad file number";
  case ECHILD:
    return "No child processes";
  case EDEADLK:
    return "Resource deadlock would occur";
  case ENOMEM:
    return "Out of memory";
  case EACCES:
    return "Permission denied";
  case EFAULT:
    return "Bad address";
  case ENOTBLK:
    return "Block device required";
  case EBUSY:
    return "Device or resource busy";
  case EEXIST:
    return "File exists";
  case EXDEV:
    return "Cross-device link";
  case ENODEV:
    return "No such device";
  case ENOTDIR:
    return "Not a directory";
  case EISDIR:
    return "Is a directory";
  case EINVAL:
    return "Invalid argument";
  case ENFILE:
    return "File table overflow";
  case EMFILE:
    return "Too many open files";
  case ENOTTY:
    return "Not a tty";
  case ETXTBSY:
    return "Text file busy";
  case EFBIG:
    return "File too large";
  case ENOSPC:
    return "No space left on device";
  case ESPIPE:
    return "Illegal seek";
  case EROFS:
    return "Read-only file system";
  case EMLINK:
    return "Too many links";
  case EPIPE:
    return "Broken pipe";
  case EDOM:
    return "Math argument out of domain of func";
  case ERANGE:
    return "Math result not representable";
  case EAGAIN:
    return "Resource temporarily unavailable";
  case EINPROGRESS:
    return "Operation now in progress";
  case EALREADY:
    return "Operation already in progress";
  case ENOTSOCK:
    return "Socket operation on non-socket";
  case EDESTADDRREQ:
    return "Destination address required";
  case EMSGSIZE:
    return "Message too long";
  case EPROTOTYPE:
    return "Protocol wrong type for socket";
  case ENOPROTOOPT:
    return "Protocol not available";
  case EPROTONOSUPPORT:
    return "Protocol not supported";
  case ESOCKTNOSUPPORT:
    return "Socket type not supported";
  case ENOTSUP:
    return "Operation not supported";
  case EPFNOSUPPORT:
    return "Protocol family not supported";
  case EAFNOSUPPORT:
    return "Address family not supported by protocol";
  case EADDRINUSE:
    return "Address already in use";
  case EADDRNOTAVAIL:
    return "Cannot assign requested address";
  case ENETDOWN:
    return "Network is down";
  case ENETUNREACH:
    return "Network is unreachable";
  case ENETRESET:
    return "Network dropped connection on reset";
  case ECONNABORTED:
    return "Software caused connection abort";
  case ECONNRESET:
    return "Connection reset by peer";
  case ENOBUFS:
    return "No buffer space available";
  case EISCONN:
    return "Socket is already connected";
  case ENOTCONN:
    return "Socket is not connected";
  case ESHUTDOWN:
    return "Cannot send after socket shutdown";
  case ETOOMANYREFS:
    return "Too many references: cannot splice";
  case ETIMEDOUT:
    return "Connection timed out";
  case ECONNREFUSED:
    return "Connection refused";
  case ELOOP:
    return "Too many levels of symbolic links";
  case ENAMETOOLONG:
    return "File name too long";
  case EHOSTDOWN:
    return "Host is down";
  case EHOSTUNREACH:
    return "No route to host";
  case ENOTEMPTY:
    return "Directory not empty";
  case EPROCLIM:
    return "Too many processes";
  case EUSERS:
    return "Too many users";
  case EDQUOT:
    return "Disc quota exceeded";
  case ESTALE:
    return "Stale NFS file handle";
  case EREMOTE:
    return "Too many levels of remote in path";
  case EBADRPC:
    return "RPC struct is bad";
  case ERPCMISMATCH:
    return "RPC version wrong";
  case EPROGUNAVAIL:
    return "RPC prog. not avail";
  case EPROGMISMATCH:
    return "Program version wrong";
  case EPROCUNAVAIL:
    return "Bad procedure for program";
  case ENOLCK:
    return "No locks available";
  case ENOSYS:
    return "Function not implemented";
  case EFTYPE:
    return "Inappropriate file type or format";
  case EAUTH:
    return "Authentication error";
  case ENEEDAUTH:
    return "Need authenticator";
  case EPWROFF:
    return "Device power is off";
  case EDEVERR:
    return "Device error";
  case EOVERFLOW:
    return "Value too large to be stored in data type";
  case EBADEXEC:
    return "Bad executable";
  case EBADARCH:
    return "Bad CPU type in executable";
  case ESHLIBVERS:
    return "Shared library version mismatch";
  case EBADMACHO:
    return "Malformed Macho file";
  case ECANCELED:
    return "Operation canceled";
  case EIDRM:
    return "Identifier removed";
  case ENOMSG:
    return "No message of desired type";
  case EILSEQ:
    return "Illegal byte sequence";
  case ENOATTR:
    return "Attribute not found";
  case EBADMSG:
    return "Bad message";
  case EMULTIHOP:
    return "Reserved";
  case ENODATA:
    return "No message available on STREAM";
  case ENOLINK:
    return "Reserved";
  case ENOSR:
    return "No STREAM resources";
  case ENOSTR:
    return "Not a STREAM";
  case EPROTO:
    return "Protocol error";
  case ETIME:
    return "STREAM ioctl timeout";
  case EOPNOTSUPP:
    return "Operation not supported on socket";
  case ENOPOLICY:
    return "No such policy registered";
  case ENOTRECOVERABLE:
    return "State not recoverable";
  case EOWNERDEAD:
    return "Previous owner died";
  case EQFULL:
    return "Interface output queue is full";
  default:
    return "Unknown error";
  }
}
