AC_DEFUN([FG2_CHECK_OPENCV],
[
    AC_ARG_WITH([opencv],
        AS_HELP_STRING([--with-opencv], [build with support for IplImage format]),
        [with_opencv=yes],
        [with_opencv=no]
    )
    AS_IF([test "x$with_opencv" = "xyes"], [
            PKG_CHECK_MODULES(
                [opencv],
                [opencv],
                [
                    AC_DEFINE(WITH_OPENCV,1,[Define to 1 to use OpenCV])
                    have_opencv=1
                ],
                [
                    have_opencv=0
                ]
            )]
    )
    AC_SUBST([have_opencv])
    AM_CONDITIONAL([WITH_OPENCV], [test "x$with_opencv" = "xyes"])
])
