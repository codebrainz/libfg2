AM_CPPFLAGS = -I$(top_srcdir) -I$(top_builddir)
AM_CFLAGS = $(LIBV4L_CFLAGS) $(LIBJPEG_CFLAGS)
AM_LDFLAGS = $(LIBV4L_LIBS) $(LIBJPEG_LIBS)

lib_LTLIBRARIES = libfg2.la

libfg2_la_SOURCES = capture.c control.c frame.c version.c

libfg2includedir = $(includedir)/libfg2
libfg2include_HEADERS = libfg2.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libfg2.pc
