if WITH_EXAMPLES

AM_CPPFLAGS = -I$(top_srcdir)
AM_CFLAGS = $(GTK_CFLAGS) $(GDKPIXBUF_CFLAGS) $(SDL_CFLAGS)
AM_LDFLAGS = $(GTK_LIBS) $(GDKPIXBUF_LIBS) $(SDL_LIBS)

noinst_PROGRAMS =

if WITH_GTK
noinst_PROGRAMS += camview-gtk
camview_gtk_SOURCES = camview-gtk.c
camview_gtk_LDADD = \
	$(top_builddir)/libfg2/libfg2.la \
	$(top_builddir)/libfg2/libfg2-gdkpixbuf.la \
	$(top_builddir)/gtkcamera/libgtkcamera.la
endif

if WITH_SDL
noinst_PROGRAMS += camview-sdl
camview_sdl_SOURCES = camview-sdl.c
camview_sdl_LDADD = \
	$(top_builddir)/libfg2/libfg2.la \
	$(top_builddir)/libfg2/libfg2-sdl.la
endif

if WITH_VALA
noinst_PROGRAMS += camsnap-vala
camsnap_vala_SOURCES = camsnap-vala.vala
camsnap_vala_VALAFLAGS = --vapidir=$(abs_top_srcdir)/vapi --pkg fg2
if WITH_SDL
camsnap_vala_VALAFLAGS += --define=WITH_SDL --pkg sdl
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
