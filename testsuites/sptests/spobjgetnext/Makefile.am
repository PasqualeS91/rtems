##
## $Id$
##

MANAGERS = all

rtems_tests_PROGRAMS = spobjgetnext
spobjgetnext_SOURCES = init.c system.h

dist_rtems_tests_DATA = spobjgetnext.scn
dist_rtems_tests_DATA += spobjgetnext.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

spobjgetnext_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(spobjgetnext_OBJECTS) $(spobjgetnext_LDADD)
LINK_LIBS = $(spobjgetnext_LDLIBS)

spobjgetnext$(EXEEXT): $(spobjgetnext_OBJECTS) $(spobjgetnext_DEPENDENCIES)
	@rm -f spobjgetnext$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
