/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** error.h
*/

#pragma once

#include <errno.h>
#include <unistd.h>

#define SIGNAL_ENTRY(code) [code] = #code

const char *errno_names[] = {
    [0] = NULL,
    SIGNAL_ENTRY(ENOTCONN),
    SIGNAL_ENTRY(EPERM),
    SIGNAL_ENTRY(ENOENT),
    SIGNAL_ENTRY(ESRCH),
    SIGNAL_ENTRY(EINTR),
    SIGNAL_ENTRY(EIO),
    SIGNAL_ENTRY(ENXIO),
    SIGNAL_ENTRY(E2BIG),
    SIGNAL_ENTRY(ENOEXEC),
    SIGNAL_ENTRY(EBADF),
    SIGNAL_ENTRY(ECHILD),
    SIGNAL_ENTRY(ENOMEM),
    SIGNAL_ENTRY(EACCES),
    SIGNAL_ENTRY(EFAULT),
    SIGNAL_ENTRY(ENOTBLK),
    SIGNAL_ENTRY(EBUSY),
    SIGNAL_ENTRY(EEXIST),
    SIGNAL_ENTRY(EXDEV),
    SIGNAL_ENTRY(ENODEV),
    SIGNAL_ENTRY(ENOTDIR),
    SIGNAL_ENTRY(EISDIR),
    SIGNAL_ENTRY(EINVAL),
    SIGNAL_ENTRY(ENFILE),
    SIGNAL_ENTRY(ENOTTY),
    SIGNAL_ENTRY(ETXTBSY),
    SIGNAL_ENTRY(EFBIG),
    SIGNAL_ENTRY(ENOSPC),
    SIGNAL_ENTRY(ESPIPE),
    SIGNAL_ENTRY(EROFS),
    SIGNAL_ENTRY(EMLINK),
    SIGNAL_ENTRY(EPIPE),
    SIGNAL_ENTRY(EDOM),
    SIGNAL_ENTRY(ERANGE),
    SIGNAL_ENTRY(ENAMETOOLONG),
    SIGNAL_ENTRY(ENOLCK),
    SIGNAL_ENTRY(ENOSYS),
    SIGNAL_ENTRY(ENOTEMPTY),
    SIGNAL_ENTRY(ELOOP),
    SIGNAL_ENTRY(EWOULDBLOCK),
    SIGNAL_ENTRY(ENOMSG),
    SIGNAL_ENTRY(EIDRM),
    SIGNAL_ENTRY(ECHRNG),
    SIGNAL_ENTRY(EL2NSYNC),
    SIGNAL_ENTRY(EL3HLT),
    SIGNAL_ENTRY(EL3RST),
    SIGNAL_ENTRY(ELNRNG),
    SIGNAL_ENTRY(EUNATCH),
    SIGNAL_ENTRY(ENOCSI),
    SIGNAL_ENTRY(EL2HLT),
    SIGNAL_ENTRY(EBADE),
    SIGNAL_ENTRY(EBADR),
    SIGNAL_ENTRY(EXFULL),
    SIGNAL_ENTRY(ENOANO),
    SIGNAL_ENTRY(EBADRQC),
    SIGNAL_ENTRY(EBADSLT),
    SIGNAL_ENTRY(EDEADLOCK),
    SIGNAL_ENTRY(EBFONT),
    SIGNAL_ENTRY(ENOSTR),
    SIGNAL_ENTRY(ENODATA),
    SIGNAL_ENTRY(ETIME),
    SIGNAL_ENTRY(ENOSR),
    SIGNAL_ENTRY(ENONET),
    SIGNAL_ENTRY(ENOPKG),
    SIGNAL_ENTRY(EREMOTE),
    SIGNAL_ENTRY(ENOLINK),
    SIGNAL_ENTRY(EADV),
    SIGNAL_ENTRY(ESRMNT),
    SIGNAL_ENTRY(ECOMM),
    SIGNAL_ENTRY(EPROTO),
    SIGNAL_ENTRY(EMULTIHOP),
    SIGNAL_ENTRY(EDOTDOT),
    SIGNAL_ENTRY(EBADMSG),
    SIGNAL_ENTRY(ENOTUNIQ),
    SIGNAL_ENTRY(EBADFD),
    SIGNAL_ENTRY(EREMCHG),
    SIGNAL_ENTRY(ELIBACC),
    SIGNAL_ENTRY(ELIBBAD),
    SIGNAL_ENTRY(ELIBSCN),
    SIGNAL_ENTRY(ELIBMAX),
    SIGNAL_ENTRY(ELIBEXEC),
    SIGNAL_ENTRY(EHOSTUNREACH),
    SIGNAL_ENTRY(EHOSTDOWN),
    SIGNAL_ENTRY(EADDRINUSE),
    SIGNAL_ENTRY(EMFILE),
    SIGNAL_ENTRY(EOVERFLOW),
    SIGNAL_ENTRY(ENOTSOCK),
    SIGNAL_ENTRY(EDESTADDRREQ),
    SIGNAL_ENTRY(EMSGSIZE),
    SIGNAL_ENTRY(EPROTOTYPE),
    SIGNAL_ENTRY(ENOPROTOOPT),
    SIGNAL_ENTRY(EPROTONOSUPPORT),
    SIGNAL_ENTRY(ESOCKTNOSUPPORT),
    SIGNAL_ENTRY(EOPNOTSUPP),
    SIGNAL_ENTRY(EPFNOSUPPORT),
    SIGNAL_ENTRY(EAFNOSUPPORT),
    SIGNAL_ENTRY(EADDRNOTAVAIL),
    SIGNAL_ENTRY(ENETDOWN),
    SIGNAL_ENTRY(ENETUNREACH),
    SIGNAL_ENTRY(ENETRESET),
    SIGNAL_ENTRY(ECONNABORTED),
    SIGNAL_ENTRY(ECONNRESET),
    SIGNAL_ENTRY(ENOBUFS),
    SIGNAL_ENTRY(EISCONN),
    SIGNAL_ENTRY(ETIMEDOUT),
    SIGNAL_ENTRY(ECONNREFUSED),
    SIGNAL_ENTRY(EALREADY),
    SIGNAL_ENTRY(EINPROGRESS),
    SIGNAL_ENTRY(EDQUOT),
    SIGNAL_ENTRY(ESTALE),
    SIGNAL_ENTRY(EREMOTEIO),
    SIGNAL_ENTRY(ECANCELED),
    SIGNAL_ENTRY(EILSEQ),
    SIGNAL_ENTRY(EOWNERDEAD),
    SIGNAL_ENTRY(ESHUTDOWN),
};

#define ERRNO_NB (sizeof(errno_names) / sizeof(char *))
