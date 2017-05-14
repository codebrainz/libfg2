AC_DEFUN([FG2_CHECK_IMLIB2],
[
    AC_ARG_WITH([imlib2],
        [AS_HELP_STRING([--with-imlib2], [build with support for Imlib_Image format @<:@default=auto@:>@])])
    AS_IF([test "x$with_imlib2" != "xno"], [
        PKG_CHECK_MODULES(
            [IMLIB2],
            [imlib2],
            [
                AC_DEFINE(WITH_IMLIB2,1,[Define to 1 to use Imlib2])
                have_imlib2=1
                with_imlib2=yes
            ],
            [
                AS_IF([test "x$with_imlib2" = "xyes"], [
                    AC_MSG_ERROR([ImLib2 support enabled but imlib2 package not found])])
                have_imlib2=0
                with_imlib2=no
            ]
        )]
    )
    AC_SUBST([have_imlib2])
    AM_CONDITIONAL([WITH_IMLIB2], [test "x$with_imlib2" != "xno"])
])
