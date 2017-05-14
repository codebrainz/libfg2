AC_DEFUN([FG2_CHECK_LIBJPEG],
[
    AC_ARG_WITH([jpeg],
        [AS_HELP_STRING([--with-jpeg], [build with support for JPEG format @<:@default=auto@:>@])])
    AS_IF([test "x$with_jpeg" != "xno"], [
        PKG_CHECK_MODULES(
            [jpeg],
            [libjpeg],
            [
                AC_DEFINE(WITH_JPEG,1,[Define to 1 to use JPEG library])
                have_libjpeg=1
                with_jpeg=yes
            ],
            [
                AS_IF([test "x$with_jpeg" = "xyes"], [
                    AC_MSG_ERROR([JPEG support enabled but libjpeg package not found])])
                have_libjpeg=0
                with_jpeg=no
            ]
        )]
    )
    AC_SUBST([have_libjpeg])
    AM_CONDITIONAL([WITH_JPEG], [test "x$with_jpeg" != "xno"])
])
