# RTEMS_CHECK_BSPDIR(RTEMS_BSP_FAMILY)
AC_DEFUN([RTEMS_CHECK_BSPDIR],
[
  case "$1" in
  pasim )
    AC_CONFIG_SUBDIRS([pasim]);;
  tcrest )
    AC_CONFIG_SUBDIRS([tcrest]);;
  tcrestmp )
    AC_CONFIG_SUBDIRS([tcrestmp]);;
  *)
    AC_MSG_ERROR([Invalid BSP]);;
  esac
])
