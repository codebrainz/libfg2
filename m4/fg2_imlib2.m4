AC_DEFUN([FG2_CHECK_IMLIB2],
[
    AC_ARG_WITH([imlib2],
        AS_HELP_STRING([--with-imlib2], [build with support for Imlib_Image format]),
        [with_imlib2=yes],
        [with_imlib2=no]
    )
    AS_IF([test "x$with_imlib2" = "xyes"], [
            PKG_CHECK_MODULES(
                [imlib2],
                [imlib2],
                [AC_DEFINE(WITH_IMLIB2,1,[Define to 1 to use Imlib2])]
            )]
    )
    AM_CONDITIONAL([WITH_IMLIB2], [test "x$with_imlib2" = "xyes"])
])
