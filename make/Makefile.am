##
## $Id: Makefile.am,v 1.00 2013/06/14 15:17:12 André Rocha $
##

rtems_makedir = $(prefix)/make

dist_rtems_make_DATA = main.cfg leaf.cfg

EXTRA_DIST = host.cfg.in

rtems_make_Templatesdir = $(rtems_makedir)/Templates

dist_rtems_make_Templates_DATA = Templates/Makefile.dir \
    Templates/Makefile.leaf Templates/Makefile.lib

EXTRA_DIST += compilers/gcc-no_bsp.cfg \
    compilers/gcc-target-default.cfg compilers/patmos-clang.cfg 

rtems_make_customdir = $(rtems_makedir)/custom

dist_rtems_make_custom_DATA = custom/default.cfg

include $(top_srcdir)/automake/host.am
