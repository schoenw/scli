configdnl Process this file with autoconf to produce a configure script.

AC_INIT(scli, 0.4.0, scli@ibr.cs.tu-bs.de)
AC_REVISION([$Rev$])
AC_CONFIG_SRCDIR(scli/scli.c)
AM_INIT_AUTOMAKE([-Wall])

dnl create a config.h file (Automake will add -DHAVE_CONFIG_H)
AC_CONFIG_HEADERS(config.h)

ISODATE=`date +%Y-%m-%d`
AC_SUBST(ISODATE)

AC_CANONICAL_HOST

dnl Checks for programs.
AC_PROG_INSTALL
AC_PROG_CC
AC_PROG_RANLIB
AC_CHECK_PROG(SMIDUMP, smidump, smidump)
AC_SUBST(SMIDUMP)
AM_PROG_AR

AC_DEFINE_UNQUOTED(SCLI_PLUGIN_PATH, "${pkglibdir}",
     [The full pathname of the directory containing scli plugins.])

AC_MSG_CHECKING([whether to enable -Wall])
AC_ARG_ENABLE(warnings,
[  --enable-warnings       Enable -Wall if using gcc.],
[ if test -n "$GCC"; then 
    AC_MSG_RESULT(adding -Wall to CFLAGS.)
    CFLAGS="$CFLAGS -Wall"
  fi],AC_MSG_RESULT(no))


dnl Checks for libraries.

AM_PATH_GLIB_2_0(2.0.0, [], AC_MSG_ERROR(scli needs GLIB), gmodule)
AM_PATH_GNET_2_0(2.0.0, [], AC_MSG_ERROR(scli needs GNET))
dnl AM_PATH_GLIB(1.2.0, [], AC_MSG_ERROR(scli needs GLIB), gmodule)
dnl AM_PATH_GTK(1.2.0, [], AC_MSG_ERROR(scli needs GTK))
AM_PATH_XML2(2.0.0, [], AC_MSG_ERROR(scli needs libxml2))
PKG_CHECK_MODULES(GSNMP, gsnmp, have_gsnmp=true, have_gsnmp=false)
AC_SUBST(GSNMP_CFLAGS)
AC_SUBST(GSNMP_LIBS)
AC_CHECK_LIB(ncurses, initscr, [],
  AC_CHECK_LIB(curses, initscr, [],
    AC_MSG_ERROR([scli requires curses functions; install curses first])
  )
)
AC_CHECK_LIB(readline, readline, [],
  AC_MSG_ERROR([scli requires readline functions; install libreadline first])
)

dnl Checks for header files.

AC_HEADER_STDC

AC_CHECK_HEADERS(unistd.h sys/ioctl.h sys/time.h termios.h ncurses.h)

dnl Darwin needs sys/socket.h before net/if.h

AC_CHECK_HEADERS([sys/socket.h])
AC_CHECK_HEADERS([net/if.h], [], [AC_MSG_WARN(Problems including net/if.h)],
[
#include <stdio.h>
#if STDC_HEADERS
# include <stdlib.h>
# include <stddef.h>
#else
# if HAVE_STDLIB_H
#  include <stdlib.h>
# endif
#endif
#if HAVE_SYS_SOCKET_H
# include <sys/socket.h>
#endif
])

dnl as well as net/if.h, netbsd needs netinet/in.h if we're going to use netinet/if_ether.h

AC_CHECK_HEADERS([netinet/in.h])

AC_CHECK_HEADERS([netinet/if_ether.h], [], [AC_MSG_WARN(Problems including netinet/if_ether.h)],
[
#include <stdio.h>
#if STDC_HEADERS
# include <stdlib.h>
# include <stddef.h>
#else
# if HAVE_STDLIB_H
#  include <stdlib.h>
# endif
#endif
#if HAVE_SYS_SOCKET_H
# include <sys/socket.h>
#endif
#if HAVE_NET_IF_H
# include <net/if.h>
#endif
#if HAVE_NETINET_IN_H
# include <netinet/in.h>
#endif
])

dnl AC_EGREP_HEADER(TIOCGWINSZ,sys/ioctl.h,AC_DEFINE(HAVE_TIOCGWINSZ))

dnl Checks for typedefs, structures, and compiler characteristics.

dnl defines HAVE_TM_ZONE if struct tm has tm_zone
AC_STRUCT_TIMEZONE

dnl Checks for library functions.

AC_CHECK_FUNC(gethostbyname, [], AC_CHECK_LIB(nsl, gethostbyname))

AC_CHECK_FUNC(connect, [], AC_CHECK_LIB(socket, connect))

AC_CHECK_FUNCS(resizeterm getaddrinfo ether_ntohost)
AC_CHECK_FUNCS(rl_completion_matches)

dnl Check for configure options

AC_ARG_ENABLE(dmalloc,
[  --enable-dmalloc        enable dmalloc debugging (www.dmalloc.com)],
 [
  AC_CHECK_HEADERS(dmalloc.h)
  AC_CHECK_LIB(dmalloc, malloc) 
 ]
)

dnl Create all the Makefiles we need and we are done.

AC_CONFIG_FILES([Makefile stub/Makefile proc/Makefile scli/Makefile doc/Makefile])
AC_OUTPUT()
