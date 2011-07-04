lib_LTLIBRARIES = libgtkcamera.la


pkg_cflags =
pkg_libs =

if WITH_LIBV4L
pkg_cflags += @libv4l_CFLAGS@
pkg_libs += @libv4l_LIBS@
endif

if WITH_GDKPIXBUF
pkg_cflags += @gdkpixbuf_CFLAGS@
pkg_libs += @gdkpixbuf_LIBS@
endif

if WITH_GTK
pkg_cflags += @gtk_CFLAGS@
pkg_libs += @gtk_LIBS@
endif

if WITH_IMLIB2
pkg_cflags += @imlib2_CFLAGS@
pkg_libs += @imlib2_LIBS@
endif

if WITH_OPENCV
pkg_cflags += @opencv_CFLAGS@
pkg_libs += @opencv_LIBS@
endif

if WITH_SDL
pkg_cflags += @sdl_CFLAGS@
pkg_libs += @sdl_LIBS@
endif

if WITH_JPEG
pkg_libs += -ljpeg
endif

if WITH_PYTHON
pkg_cflags += @PYTHON_CPPFLAGS@
pkg_libs += @PYTHON_LDFLAGS@ @PYTHON_EXTRA_LIBS@ @PYTHON_EXTRA_LDFLAGS@
endif

if WITH_VALA
pkg_cflags += @vala_CFLAGS@
pkg_libs += @vala_LIBS@
endif


libgtkcamera_la_LIBADD = @gtk_LIBS@ $(pkg_libs) $(top_builddir)/src/libfg2.la
libgtkcamera_la_CFLAGS = @gtk_CFLAGS@ $(pkg_cflags) -I$(top_srcdir)/src
libgtkcamera_la_SOURCES = gtkcamera.c


gtkcamera_includedir = $(includedir)/gtkcamera
gtkcamera_include_HEADERS = gtkcamera.h
