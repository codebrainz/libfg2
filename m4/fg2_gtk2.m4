AC_DEFUN([FG2_CHECK_GTK2],
[
    AC_ARG_WITH([gtk2],
        [AS_HELP_STRING([--with-gtk2], [build the GtkCamera widget for GTK+ 2 @<:@default=auto@:>@])])
    AS_IF([test "x$with_gtk2" != "xno"], [
        AS_IF([test "x$with_gtk2" = "xyes"], [
            AS_IF([test "x$with_gdkpixbuf" = "xno"],
                [AC_MSG_ERROR([GTK+ 2 support enabled but GdkPixbuf support is not, use --with-gdkpixbuf to enable])])
        ])
        AS_IF([test "x$with_gdkpixbuf" != "xno"], [
            PKG_CHECK_MODULES(
                [GTK2],
                [gtk+-2.0],
                [
                    AC_DEFINE(WITH_GTK2,1,[Define to 1 to use Gtk+ 2])
                    have_gtk2=1
                    with_gtk2=yes
                ],
                [
                    AS_IF([test "x$with_gtk2" = "xyes"], [
                        AC_MSG_ERROR([GTK+ 2 support enabled but gtk+-2.0 package not found])])
                    have_gtk2=0
                    with_gtk2=no
                ]
            )
        ])
    ])
    AC_SUBST([have_gtk2])
    AM_CONDITIONAL([WITH_GTK2], [test "x$with_gtk2" != "xno"])
])
