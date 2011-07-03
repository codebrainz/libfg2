AM_CFLAGS = -g -Wall
AM_LDFLAGS =

lib_LTLIBRARIES = libfg2.la

libfg2_la_CFLAGS =
libfg2_la_LIBADD =
pkgconfig_requires_private =
pkgconfig_libs_private =

if WITH_LIBV4L
libfg2_la_CFLAGS += @libv4l_CFLAGS@
libfg2_la_LIBADD += @libv4l_LIBS@
pkgconfig_requires_private += libv4l1 libv4l2 libv4lconvert
endif

if WITH_GDKPIXBUF
libfg2_la_CFLAGS += @gdkpixbuf_CFLAGS@
libfg2_la_LIBADD += @gdkpixbuf_LIBS@
pkgconfig_requires_private += gdk-pixbuf-2.0
endif

if WITH_GTK
libfg2_la_CFLAGS += @gtk_CFLAGS@
libfg2_la_LIBADD += @gtk_LIBS@
pkgconfig_requires_private += gtk+-2.0
endif

if WITH_IMLIB2
libfg2_la_CFLAGS += @imlib2_CFLAGS@
libfg2_la_LIBADD += @imlib2_LIBS@
pkgconfig_requires_private += imlib2
endif

if WITH_OPENCV
libfg2_la_CFLAGS += @opencv_CFLAGS@
libfg2_la_LIBADD += @opencv_LIBS@
pkgconfig_requires_private += opencv
endif

if WITH_SDL
libfg2_la_CFLAGS += @sdl_CFLAGS@
libfg2_la_LIBADD += @sdl_LIBS@
pkgconfig_requires_private += sdl
endif

if WITH_JPEG
libfg2_la_LIBADD += -ljpeg
pkgconfig_libs_private += -ljpeg
endif

if WITH_PYTHON
libfg2_la_CFLAGS += @PYTHON_CPPFLAGS@
libfg2_la_LIBADD += @PYTHON_LDFLAGS@ @PYTHON_EXTRA_LIBS@ @PYTHON_EXTRA_LDFLAGS@
pkgconfig_libs_private += @PYTHON_LDFLAGS@ @PYTHON_EXTRA_LIBS@ @PYTHON_EXTRA_LDFLAGS@
endif

if WITH_VALA
libfg2_la_CFLAGS += @vala_CFLAGS@
libfg2_la_LIBADD += @vala_LIBS@
pkgconfig_requires_private += vala-0.10
endif

libfg2_la_SOURCES = capture.c frame.c control.c

if WITH_GDKPIXBUF
libfg2_la_SOURCES += convert.c
else
if WITH_IMLIB2
libfg2_la_SOURCES += convert.c
else
if WITH_OPENCV
libfg2_la_SOURCES += convert.c
else
if WITH_SDL
libfg2_la_SOURCES += convert.c
endif
endif
endif
endif

include_HEADERS = libfg2.h libfg2-config.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libfg2.pc

libfg2.pc: $(top_srcdir)/src/libfg2.pc.in
	$(AM_V_GEN)sed -e s'|@prefix[@]|$(prefix)|g' \
	    -e s'|@exec_prefix[@]|$(exec_prefix)|g' \
	    -e s'|@includedir[@]|$(includedir)|g' \
	    -e s'|@libdir[@]|$(libdir)|g' \
	    -e s'|@PACKAGE_NAME[@]|$(PACKAGE_NAME)|g' \
	    -e s'|@PACKAGE_VERSION[@]|$(PACKAGE_VERSION)|g' \
	    -e s'|@PKGCONFIG_REQUIRES_PRIVATE[@]|$(pkgconfig_requires_private)|g' \
	    -e s'|@PKGCONFIG_LIBS_PRIVATE[@]|$(pkgconfig_libs_private)|g' \
	    $< > $@

CLEANFILES = libfg2-config.h libfg2.pc
