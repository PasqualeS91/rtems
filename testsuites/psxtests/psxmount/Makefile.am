##
## $Id$
##

MANAGERS = all

rtems_tests_PROGRAMS = psxmount
psxmount_SOURCES = main.c test.c ../include/pmacros.h

dist_rtems_tests_DATA = psxmount.scn

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

psxmount_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/include
AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(psxmount_OBJECTS) $(psxmount_LDADD)
LINK_LIBS = $(psxmount_LDLIBS)

psxmount$(EXEEXT): $(psxmount_OBJECTS) $(psxmount_DEPENDENCIES)
	@rm -f psxmount$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
