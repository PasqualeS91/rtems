##
## $Id$
##

MANAGERS = io semaphore

rtems_tests_PROGRAMS = tm08
tm08_SOURCES = task1.c system.h ../include/timesys.h \
    ../../support/src/tmtests_empty_function.c

dist_rtems_tests_DATA = tm08.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

tm08_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

OPERATION_COUNT = @OPERATION_COUNT@
AM_CPPFLAGS += -I$(top_srcdir)/include -DOPERATION_COUNT=$(OPERATION_COUNT)
AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(tm08_OBJECTS) $(tm08_LDADD)
LINK_LIBS = $(tm08_LDLIBS)

tm08$(EXEEXT): $(tm08_OBJECTS) $(tm08_DEPENDENCIES)
	@rm -f tm08$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
