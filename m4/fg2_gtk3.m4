AC_DEFUN([FG2_CHECK_GTK3],
[
    AC_ARG_WITH([gtk3],
        [AS_HELP_STRING([--with-gtk3], [build the GtkCamera widget for GTK+ 3 @<:@default=auto@:>@])])
    AS_IF([test "x$with_gtk3" != "xno"], [
        AS_IF([test "x$with_gtk3" = "xyes"], [
            AS_IF([test "x$with_gdkpixbuf" = "xno"],
                [AC_MSG_ERROR([GTK+ 3 support enabled but GdkPixbuf support is not, use --with-gdkpixbuf to enable])])
        ])
        AS_IF([test "x$with_gdkpixbuf" != "xno"], [
            PKG_CHECK_MODULES(
                [GTK3],
                [gtk+-3.0],
                [
                    AC_DEFINE(WITH_GTK3,1,[Define to 1 to use Gtk+ 3])
                    have_gtk3=1
                    with_gtk3=yes
                ],
                [
                    AS_IF([test "x$with_gtk3" = "xyes"], [
                        AC_MSG_ERROR([GTK+ 3 support enabled but gtk+-3.0 package not found])])
                    have_gtk3=0
                    with_gtk3=no
                ]
            )
        ])
    ])
    AC_SUBST([have_gtk3])
    AM_CONDITIONAL([WITH_GTK3], [test "x$with_gtk3" != "xno"])
])
