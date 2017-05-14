AM_CPPFLAGS = -I$(top_srcdir)

lib_LTLIBRARIES =

if WITH_GTK2

lib_LTLIBRARIES += libgtkcamera.la

libgtkcamera_la_SOURCES = gtkcamera.c
libgtkcamera_la_CFLAGS = $(GTK2_CFLAGS)
libgtkcamera_la_LDFLAGS = $(GTK2_LIBS)
libgtkcamera_la_LIBADD = \
	$(top_builddir)/libfg2/libfg2.la \
	$(top_builddir)/libfg2/libfg2-gdkpixbuf.la

pkgconfig2dir = $(libdir)/pkgconfig
pkgconfig2_DATA = gtkcamera.pc

endif

if WITH_GTK3

lib_LTLIBRARIES += libgtk3camera.la

libgtk3camera_la_SOURCES = gtkcamera.c
libgtk3camera_la_CFLAGS = $(GTK3_CFLAGS)
libgtk3camera_la_LDFLAGS = $(GTK3_LIBS)
libgtk3camera_la_LIBADD = \
	$(top_builddir)/libfg2/libfg2.la \
	$(top_builddir)/libfg2/libfg2-gdkpixbuf.la

pkgconfig3dir = $(libdir)/pkgconfig
pkgconfig3_DATA = gtk3camera.pc

endif

if WITH_GTK2
gtkcameraincludedir = $(includedir)/gtkcamera
gtkcamerainclude_HEADERS = gtkcamera.h
else
if WITH_GTK3
gtkcameraincludedir = $(includedir)/gtkcamera
gtkcamerainclude_HEADERS = gtkcamera.h
endif
endif
