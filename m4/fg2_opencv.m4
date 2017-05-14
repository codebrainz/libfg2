AC_DEFUN([FG2_CHECK_OPENCV],
[
    AC_ARG_WITH([opencv],
        [AS_HELP_STRING([--with-opencv], [build with support for IplImage format @<:@default=auto@:>@])])
    AS_IF([test "x$with_opencv" != "xno"], [
        PKG_CHECK_MODULES(
            [OPENCV],
            [opencv],
            [
                AC_DEFINE(WITH_OPENCV,1,[Define to 1 to use OpenCV])
                have_opencv=1
                with_opencv=yes
            ],
            [
                AS_IF([test "x$with_opencv" = "xyes"], [
                    AC_MSG_ERROR([OpenCV support enabled but opencv package not found])])
                have_opencv=0
                with_opencv=no
            ]
        )]
    )
    AC_SUBST([have_opencv])
    AM_CONDITIONAL([WITH_OPENCV], [test "x$with_opencv" != "xno"])
])
