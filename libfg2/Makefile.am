AM_CPPFLAGS = -I$(top_srcdir)
AM_CFLAGS = @libv4l_CFLAGS@ @jpeg_CFLAGS@
AM_LDFLAGS = @libv4l_LIBS@ @jpeg_LIBS@

lib_LTLIBRARIES = libfg2.la

libfg2_la_SOURCES = capture.c frame.c control.c convert.h

libfg2includedir = $(includedir)/libfg2
libfg2include_HEADERS = libfg2.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libfg2.pc

pkgconfig_requires_private =
if WITH_LIBV4L
pkgconfig_requires_private += libv4l1 libv4l2 libv4lconvert
endif
if WITH_JPEG
pkgconfig_requires_private += libjpeg
endif

libfg2.pc: $(top_srcdir)/libfg2/libfg2.pc.in
	$(AM_V_GEN)sed -e s'|@prefix[@]|$(prefix)|g' \
	    -e s'|@exec_prefix[@]|$(exec_prefix)|g' \
	    -e s'|@includedir[@]|$(includedir)|g' \
	    -e s'|@libdir[@]|$(libdir)|g' \
	    -e s'|@PACKAGE_NAME[@]|$(PACKAGE_NAME)|g' \
	    -e s'|@PACKAGE_VERSION[@]|$(PACKAGE_VERSION)|g' \
	    -e s'|@PKGCONFIG_REQUIRES_PRIVATE[@]|$(pkgconfig_requires_private)|g' \
	    $< > $@

EXTRA_DIST = libfg2.pc.in
CLEANFILES = libfg2.pc

if WITH_GDKPIXBUF
lib_LTLIBRARIES += libfg2-gdkpixbuf.la
libfg2_gdkpixbuf_la_SOURCES = frame-gdkpixbuf.c
libfg2_gdkpixbuf_la_CFLAGS = $(AM_CFLAGS) @gdkpixbuf_CFLAGS@
libfg2_gdkpixbuf_la_LDFLAGS = $(AM_LDFLAGS) @gdkpixbuf_LIBS@
libfg2include_HEADERS += libfg2-gdkpixbuf.h
pkgconfig_DATA += libfg2-gdkpixbuf.pc
endif

if WITH_IMLIB2
lib_LTLIBRARIES += libfg2-imlib2.la
libfg2_imlib2_la_SOURCES = frame-imlib2.c
libfg2_imlib2_la_CFLAGS = $(AM_CFLAGS) @imlib2_CFLAGS@
libfg2_imlib2_la_LDFLAGS = $(AM_LDFLAGS) @imlib2_LIBS@
libfg2include_HEADERS += libfg2-imlib2.h
pkgconfig_DATA += libfg2-imlib2.pc
endif

if WITH_OPENCV
lib_LTLIBRARIES += libfg2-opencv.la
libfg2_opencv_la_SOURCES = frame-opencv.c
libfg2_opencv_la_CFLAGS = $(AM_CFLAGS) @opencv_CFLAGS@
libfg2_opencv_la_LDFLAGS = $(AM_LDFLAGS) @opencv_LIBS@
libfg2include_HEADERS += libfg2-opencv.h
pkgconfig_DATA += libfg2-opencv.pc
endif

if WITH_SDL
lib_LTLIBRARIES += libfg2-sdl.la
libfg2_sdl_la_SOURCES = frame-sdl.c
libfg2_sdl_la_CFLAGS = $(AM_CFLAGS) @sdl_CFLAGS@
libfg2_sdl_la_LDFLAGS = $(AM_LDFLAGS) @sdl_LIBS@
libfg2include_HEADERS += libfg2-sdl.h
pkgconfig_DATA += libfg2-sdl.pc
endif
