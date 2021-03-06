dnl
dnl $Id: prog-cc.m4,v 1.00 2013/06/14 15:17:12 André Rocha $
dnl 
dnl Check for target gcc
dnl

AC_DEFUN([RTEMS_PROG_CC],
[
AC_BEFORE([$0], [AC_PROG_CPP])dnl
AC_BEFORE([$0], [AC_PROG_CC])dnl
AC_BEFORE([$0], [RTEMS_CANONICALIZE_TOOLS])dnl

RTEMS_CHECK_TOOL(CC,clang)
RTEMS_CHECK_TOOL(CC,gcc)
test -z "$CC" && \
  AC_MSG_ERROR([no acceptable cc found in \$PATH])
AC_PROG_CC
AC_PROG_CPP
])

AC_DEFUN([RTEMS_PROG_CC_FOR_TARGET],
[
# Was CFLAGS set?
rtems_cv_CFLAGS_set="${CFLAGS+set}"
dnl check target cc
RTEMS_PROG_CC
dnl check if the target compiler may use --pipe
RTEMS_GCC_PIPE
test "$rtems_cv_gcc_pipe" = "yes" && CC="$CC --pipe"

# Append warning flags if CFLAGS wasn't set.
AS_IF([test "$GCC" = yes && test "$rtems_cv_CFLAGS_set" != set],
[CFLAGS="$CFLAGS -Wall"])

RTEMS_CPPFLAGS="-I\$(top_builddir) -I\$(PROJECT_INCLUDE)"
AC_SUBST(RTEMS_CPPFLAGS)

AS_IF([test "$GCC" = yes],[
AS_IF([ test "$CC" = "patmos-unknown-rtems-clang --pipe"], [
RTEMS_RELLDFLAGS="-fpatmos-link-object"
], [RTEMS_RELLDFLAGS="-qnolinkcmds -nostdlib -Wl,-r"])])
AC_SUBST(RTEMS_RELLDFLAGS)
])
