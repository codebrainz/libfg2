if WITH_EXAMPLES

AM_CPPFLAGS = -I$(top_srcdir)
AM_CFLAGS = $(GDKPIXBUF_CFLAGS)
AM_LDFLAGS = $(GDKPIXBUF_LIBS)

noinst_PROGRAMS =

if WITH_GTK2
noinst_PROGRAMS += camview-gtk2
camview_gtk2_SOURCES = camview-gtk.c
camview_gtk2_CFLAGS = $(AM_CFLAGS) $(GTK2_CFLAGS)
camview_gtk2_LDFLAGS = $(AM_LDFLAGS) $(GTK2_LIBS)
camview_gtk2_LDADD = \
	$(top_builddir)/libfg2/libfg2.la \
	$(top_builddir)/libfg2/libfg2-gdkpixbuf.la \
	$(top_builddir)/gtkcamera/libgtkcamera.la
endif

if WITH_GTK3
noinst_PROGRAMS += camview-gtk3
camview_gtk3_SOURCES = camview-gtk.c
camview_gtk3_CFLAGS = $(AM_CFLAGS) $(GTK3_CFLAGS)
camview_gtk3_LDFLAGS = $(AM_LDFLAGS) $(GTK3_LIBS)
camview_gtk3_LDADD = \
	$(top_builddir)/libfg2/libfg2.la \
	$(top_builddir)/libfg2/libfg2-gdkpixbuf.la \
	$(top_builddir)/gtkcamera/libgtk3camera.la
endif

if WITH_SDL1
noinst_PROGRAMS += camview-sdl1
camview_sdl1_SOURCES = camview-sdl.c
camview_sdl1_CFLAGS = $(AM_CFLAGS) $(SDL1_CFLAGS)
camview_sdl1_LDFLAGS = $(AM_LDFLAGS) $(SDL1_LIBS)
camview_sdl1_LDADD = \
	$(top_builddir)/libfg2/libfg2.la \
	$(top_builddir)/libfg2/libfg2-sdl.la
endif

if WITH_SDL2
noinst_PROGRAMS += camview-sdl2
camview_sdl2_SOURCES = camview-sdl2.c
camview_sdl2_CFLAGS = $(AM_CFLAGS) $(SDL2_CFLAGS)
camview_sdl2_LDFLAGS = $(AM_LDFLAGS) $(SDL2_LIBS)
camview_sdl2_LDADD = \
	$(top_builddir)/libfg2/libfg2.la \
	$(top_builddir)/libfg2/libfg2-sdl2.la
endif

if WITH_VALA
noinst_PROGRAMS += camsnap-vala
camsnap_vala_SOURCES = camsnap-vala.vala
camsnap_vala_VALAFLAGS = --vapidir=$(abs_top_srcdir)/vapi --pkg fg2
camsnap_vala_CFLAGS = $(AM_CFLAGS) -w
if WITH_SDL1
camsnap_vala_VALAFLAGS += --define=WITH_SDL --pkg sdl
else
if WITH_SDL2
camsnap_vala_VALAFLAGS += --define=WITH_SDL --pkg sdl
endif
endif
if WITH_GDKPIXBUF
camsnap_vala_VALAFLAGS += --define=WITH_GDKPIXBUF --pkg gdk-pixbuf-2.0
endif
camsnap_vala_LDADD = $(top_builddir)/libfg2/libfg2.la
endif

noinst_PROGRAMS += test
test_SOURCES = test.c
test_LDADD = $(pkg_libs) $(top_builddir)/libfg2/libfg2.la

endif
