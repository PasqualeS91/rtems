## Process this file with autoconf to produce a configure script.
##
## $Id$

AC_PREREQ([2.68])
AC_INIT([rtems-c-src-lib-libbsp-bfin-eZKit533],[_RTEMS_VERSION],[http://www.rtems.org/bugzilla])
AC_CONFIG_SRCDIR([bsp_specs])
RTEMS_TOP(../../../../../..)

RTEMS_CANONICAL_TARGET_CPU
AM_INIT_AUTOMAKE([no-define nostdinc foreign 1.11.1])
RTEMS_BSP_CONFIGURE

RTEMS_PROG_CC_FOR_TARGET
RTEMS_CANONICALIZE_TOOLS
RTEMS_PROG_CCAS

## bsp-specific options
RTEMS_BSPOPTS_SET([CONSOLE_USE_INTERRUPTS],[*],[0])
RTEMS_BSPOPTS_HELP([CONSOLE_USE_INTERRUPTS],
[The console driver can operate in either polled or interrupt mode.])

RTEMS_BSPOPTS_SET([BFIN_ON_SKYEYE],[*],[0])
RTEMS_BSPOPTS_HELP([BFIN_ON_SKYEYE],
[(BSP--Skyeye)
 If defined, disable features which are not supported on Skyeye.])

RTEMS_BSP_CLEANUP_OPTIONS(0, 0)

# Explicitly list all Makefiles here
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
