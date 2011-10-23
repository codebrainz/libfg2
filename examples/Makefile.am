noinst_PROGRAMS =
CLEANFILES =
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

#if WITH_JPEG
#noinst_PROGRAMS += camsnap
#camsnap_CPPFLAGS = $(pkg_cflags) -I$(top_srcdir)/src
#camsnap_LDADD = $(pkg_libs) $(top_builddir)/src/libfg2.la
#camsnap_SOURCES = camsnap.c
#endif

if WITH_GTK
noinst_PROGRAMS += camview-gtk
camview_gtk_CPPFLAGS = $(pkg_cflags) \
						-I$(top_srcdir)/src \
						-I$(top_srcdir)/gtk
camview_gtk_LDADD = $(pkg_libs) \
						$(top_builddir)/src/libfg2.la \
						$(top_builddir)/gtk/libgtkcamera.la
camview_gtk_SOURCES = camview-gtk.c
endif

if WITH_SDL
noinst_PROGRAMS += camview-sdl
camview_sdl_CPPFLAGS = $(pkg_cflags) -I$(top_srcdir)/src
camview_sdl_LDADD = $(pkg_libs) $(top_builddir)/src/libfg2.la
camview_sdl_SOURCES = camview-sdl.c
endif

if WITH_VALA
noinst_PROGRAMS += camsnap-vala
VALAFLAGS = --vapidir $(top_srcdir)/vala --pkg fg2
if WITH_SDL
VALAFLAGS += -DWITH_SDL
endif
if WITH_GDKPIXBUF
VALAFLAGS += -DWITH_GDKPIXBUF
endif
camsnap_vala_CPPFLAGS = $(pkg_cflags) -I$(top_srcdir)/src
camsnap_vala_LDADD = $(pkg_libs) $(top_builddir)/src/libfg2.la
camsnap_vala_SOURCES = camsnap-vala.vala
endif

noinst_PROGRAMS += test
test_CPPFLAGS = $(pkg_cflags) -I$(top_srcdir)/src
test_LDADD = $(pkg_libs) $(top_builddir)/src/libfg2.la
test_SOURCES = test.c

#noinst_PROGRAMS += fg-udev
#fg_udev_SOURCES = fg-udev.c

