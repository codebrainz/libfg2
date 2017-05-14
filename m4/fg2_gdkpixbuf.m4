AC_DEFUN([FG2_CHECK_GDKPIXBUF],
[
    AC_ARG_WITH([gdkpixbuf],
        [AS_HELP_STRING([--with-gdkpixbuf], [build with support for GdkPixbuf format @<:@default=auto@:>@])])
    AS_IF([test "x$with_gdkpixbuf" != "xno"], [
            PKG_CHECK_MODULES(
                [gdkpixbuf],
                [gdk-pixbuf-2.0],
                [
                    AC_DEFINE(WITH_GDKPIXBUF,1,[Define to 1 to use GdkPixbuf])
                    have_gdkpixbuf=1
                    with_gdkpixbuf=yes
                ],
                [
                    AS_IF([test "x$with_gdkpixbuf" = "xyes"], [
                        AC_MSG_ERROR([GdkPixbuf support enabled but gdk-pixbuf-2.0 package not found])])
                    have_gdkpixbuf=0
                    with_gdkpixbuf=no
                ]
            )]
    )
    AC_SUBST([have_gdkpixbuf])
    AM_CONDITIONAL([WITH_GDKPIXBUF], [test "x$with_gdkpixbuf" != "xno"])
])
