/*
 * netread.c
 *
 * Copyright 1987, 1988 by the Massachusetts Institute of Technology.
 *
 * For copying and distribution information, please see the file
 * <mit-copyright.h>.
 */

#include "mit-copyright.h"
#include <errno.h>
#define	DEFINE_SOCKADDR
#include "krb.h"
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#ifndef _WINDOWS
extern int errno;
#endif
#include "port-sockets.h"

/*
 * krb_net_read() reads from the file descriptor "fd" to the buffer
 * "buf", until either 1) "len" bytes have been read or 2) cannot
 * read anymore from "fd".  It returns the number of bytes read
 * or a read() error.  (The calling interface is identical to
 * read(2).)
 *
 * XXX must not use non-blocking I/O
 */
int
krb_net_read(fd, buf, len)
int fd;
register char *buf;
register int len;
{
    int cc, len2 = 0;

    do {
	cc = SOCKET_READ(fd, buf, len);
	if (cc < 0)
	  {
	    if (SOCKET_ERRNO == SOCKET_EINTR)
	      continue;
	    return(cc);		 /* errno is already set */
	  }
	else if (cc == 0) {
	    return(len2);
	} else {
	    buf += cc;
	    len2 += cc;
	    len -= cc;
	}
    } while (len > 0);
    return(len2);
}
