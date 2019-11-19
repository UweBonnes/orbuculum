/*
 * Generic Routines
 * ================
 *
 * Copyright (C) 2017, 2019  Dave Marples  <dave@marples.net>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * * Neither the names Orbtrace, Orbuculum nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef _GENERICS_
#define _GENERICS_
#include <stdbool.h>
#include <limits.h>
#include <stdint.h>

#if defined(_WIN32) || defined(__CYGWIN__)
#   include <winsock2.h>
#   include <windows.h>
#   include <ws2tcpip.h>
#   include <libiberty/demangle.h>
#   include <libusb-1.0/libusb.h>
#else
#   include <sys/socket.h>
#   include <netinet/in.h>
#   include <netdb.h>
#   include <demangle.h>
#   include <arpa/inet.h>
#endif

#if defined(__APPLE__) && defined(__MACH__)
    #include <sys/ioctl.h>
    #include <termios.h>
    #include <libusb.h>
#else
     #if defined(__linux__)
         #include <libusb-1.0/libusb.h>
         #include <asm/ioctls.h>
         #if defined TCGETS2
             #include <asm/termios.h>
             /* Manual declaration to avoid conflict. */
             extern int ioctl ( int __fd, unsigned long int __request, ... ) __THROW;
         #endif
     #endif
#endif

#if !defined(_POSIX_ARG_MAX)
# define _POSIX_ARG_MAX 4096
#endif

#if defined(__linux__)
    #define EOL "\n"
#else
    #define EOL "\n\r"
#endif
#ifdef __cplusplus
extern "C" {
#endif
// ====================================================================================================
enum verbLevel {V_ERROR, V_WARN, V_INFO, V_DEBUG};


char *GenericsEscape( char *str );
char *GenericsUnescape( char *str );

void genericsSetReportLevel( enum verbLevel lset );
void genericsReport( enum verbLevel l, const char *fmt, ... );
void genericsExit( int status, const char *fmt, ... );
// ====================================================================================================
#ifdef __cplusplus
}
#endif

#endif
