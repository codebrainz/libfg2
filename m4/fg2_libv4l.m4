AC_DEFUN([FG2_CHECK_LIBV4L],
[
    AC_ARG_WITH([libv4l],
        AS_HELP_STRING([--without-libv4l], [do not build with support for libv4l]),
        [with_libv4l=no],
        [with_libv4l=yes]
    )
    AS_IF([test "x$with_libv4l" = "xyes"], [
            PKG_CHECK_MODULES(
                [libv4l],
                [libv4l1 libv4l2 libv4lconvert],
                [
                    AC_DEFINE(WITH_LIBV4L,1,[Define to 1 to use libv4l2])
                    have_libv4l=1
                ],
                [
                    have_libv4l=0
                ]
            )]
    )
    AC_SUBST([have_libv4l])
    AM_CONDITIONAL([WITH_LIBV4L], [test "x$with_libv4l" = "xyes"])
])
