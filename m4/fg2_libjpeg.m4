AC_DEFUN([FG2_CHECK_LIBJPEG],
[
    AC_ARG_WITH([jpeg],
        AS_HELP_STRING([--without-jpeg], [do not build with support for JPEG format]),
        [with_jpeg=no],
        [with_jpeg=yes]
    )
    AS_IF([test "x$with_jpeg" = "xyes"], [
            PKG_CHECK_MODULES(
                [jpeg],
                [libjpeg],
                [AC_DEFINE(WITH_JPEG,1,[Define to 1 to use JPEG library])]
            )]
    )
    AM_CONDITIONAL([WITH_JPEG], [test "x$with_jpeg" = "xyes"])
])
