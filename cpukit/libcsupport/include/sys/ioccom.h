/*-
 * Copyright (c) 1982, 1986, 1990, 1993, 1994
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)ioccom.h	8.2 (Berkeley) 3/28/94
 * $FreeBSD: src/sys/sys/ioccom.h,v 1.15 2004/04/07 04:19:49 imp Exp $
 */
/*
 * $Id$
 */

#ifndef	_SYS_IOCCOM_H_
#define	_SYS_IOCCOM_H_

#include <sys/types.h>

/*
 * Ioctl's have the command encoded in the lower word, and the size of
 * any in or out parameters in the upper word.  The high 3 bits of the
 * upper word are used to encode the in/out status of the parameter.
 */
#define	IOCPARM_MASK	0x1fff		/* parameter length, at most 13 bits */
#define	IOCPARM_LEN(x)	(((x) >> 16) & IOCPARM_MASK)
#define	IOCBASECMD(x)	((x) & ~(IOCPARM_MASK << 16))
#define	IOCGROUP(x)	(((x) >> 8) & 0xff)

#define	IOCPARM_MAX	PAGE_SIZE		/* max size of ioctl, mult. of PAGE_SIZE */
#define	IOC_VOID	0x20000000	/* no parameters */
#define	IOC_OUT		0x40000000	/* copy out parameters */
#define	IOC_IN		0x80000000	/* copy in parameters */
#define	IOC_INOUT	(IOC_IN|IOC_OUT)
#define	IOC_DIRMASK	0xe0000000	/* mask for IN/OUT/VOID */

#define	_IOC(inout,group,num,len) \
	(u_int32_t) ((u_int32_t)inout | \
         (u_int32_t) ((u_int32_t)((u_int32_t)len & IOCPARM_MASK) << 16) | \
         (u_int32_t)((group) << 8) | \
         (u_int32_t)(num))
#define	_IO(g,n)	_IOC(IOC_VOID,	(g), (n), 0)
#define	_IOR(g,n,t)	_IOC(IOC_OUT,	(g), (n), sizeof(t))
#define	_IOW(g,n,t)	_IOC(IOC_IN,	(g), (n), sizeof(t))
/* this should be _IORW, but stdio got there first */
#define	_IOWR(g,n,t)	_IOC(IOC_INOUT,	(g), (n), sizeof(t))

/*
 *  IOCTL values
 */

#define       RTEMS_IO_GET_ATTRIBUTES 1
#define       RTEMS_IO_SET_ATTRIBUTES 2
#define       RTEMS_IO_TCDRAIN        3
#define       RTEMS_IO_RCVWAKEUP      4
#define       RTEMS_IO_SNDWAKEUP      5

/* copied from libnetworking/sys/filio.h and commented out there */
/* Generic file-descriptor ioctl's. */
#define FIOCLEX          _IO('f', 1)            /* set close on exec on fd */
#define FIONCLEX         _IO('f', 2)            /* remove close on exec */
#define FIONREAD        _IOR('f', 127, int)     /* get # bytes to read */
#define FIONBIO         _IOW('f', 126, int)     /* set/clear non-blocking i/o */
#define FIOASYNC        _IOW('f', 125, int)     /* set/clear async i/o */
#define FIOSETOWN       _IOW('f', 124, int)     /* set owner */
#define FIOGETOWN       _IOR('f', 123, int)     /* get owner */

#ifndef _KERNEL

#include <rtems/bsd/sys/cdefs.h>

#ifndef __ioctl_command_defined
typedef u_int32_t ioctl_command_t;
#define __ioctl_command_defined
#endif

__BEGIN_DECLS
int	ioctl(int, ioctl_command_t, ...);
__END_DECLS

#endif /* !KERNEL */

#endif /* !_SYS_IOCCOM_H_ */
