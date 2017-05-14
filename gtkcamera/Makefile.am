if WITH_GTK

AM_CPPFLAGS = -I$(top_srcdir)
AM_CFLAGS = @GTK_CFLAGS@
AM_LDFLAGS = @GTK_LIBS@

lib_LTLIBRARIES = libgtkcamera.la

libgtkcamera_la_SOURCES = gtkcamera.c
libgtkcamera_la_LIBADD = \
	$(top_builddir)/libfg2/libfg2.la \
	$(top_builddir)/libfg2/libfg2-gdkpixbuf.la

gtkcameraincludedir = $(includedir)/gtkcamera
gtkcamerainclude_HEADERS = gtkcamera.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = gtkcamera.pc

endif
