AC_DEFUN([FG2_CHECK_GDKPIXBUF],
[
    AC_ARG_WITH([gdkpixbuf],
        AS_HELP_STRING([--with-gdkpixbuf], [build with support for GdkPixbuf format]),
        [with_gdkpixbuf=yes],
        [with_gdkpixbuf=no]
    )
    AS_IF([test "x$with_gdkpixbuf" = "xyes"], [
            PKG_CHECK_MODULES(
                [gdkpixbuf],
                [gdk-pixbuf-2.0],
                [AC_DEFINE(WITH_GDKPIXBUF,1,[Define to 1 to use GdkPixbuf])]
            )]
    )
    AM_CONDITIONAL([WITH_GDKPIXBUF], [test "x$with_gdkpixbuf" = "xyes"])
])
