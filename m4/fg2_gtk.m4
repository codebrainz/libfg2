AC_DEFUN([FG2_CHECK_GTK],
[
    AC_ARG_WITH([gtk],
        [AS_HELP_STRING([--with-gtk], [build the GtkCamera widget @<:@default=auto@:>@])])
    AS_IF([test "x$with_gtk" != "xno"], [
        AS_IF([test "x$with_gtk" = "xyes"], [
            AS_IF([test "x$with_gdkpixbuf" = "xno"],
                [AC_MSG_ERROR([GTK+ support enabled but GdkPixbuf support is not, use --with-gdkpixbuf to enable])])
        ])
        AS_IF([test "x$with_gdkpixbuf" != "xno"], [
            PKG_CHECK_MODULES(
                [gtk],
                [gtk+-2.0],
                [
                    AC_DEFINE(WITH_GTK,1,[Define to 1 to use Gtk+])
                    have_gtk=1
                    with_gtk=yes
                ],
                [
                    AS_IF([test "x$with_gtk" = "xyes"], [
                        AC_MSG_ERROR([GTK+ support enabled but gtk+-2.0 package not found])])
                    have_gtk=0
                    with_gtk=no
                ]
            )
        ])
    ])
    AC_SUBST([have_gtk])
    AM_CONDITIONAL([WITH_GTK], [test "x$with_gtk" != "xno"])
])
