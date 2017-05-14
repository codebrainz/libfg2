AC_DEFUN([FG2_CHECK_LIBV4L],
[
    AC_ARG_WITH([libv4l],
        [AS_HELP_STRING([--with-libv4l], [build with support for libv4l @<:@default=auto@:>@])])
    AS_IF([test "x$with_libv4l" != "xno"], [
        PKG_CHECK_MODULES(
            [libv4l],
            [libv4l1 libv4l2 libv4lconvert],
            [
                AC_DEFINE(WITH_LIBV4L,1,[Define to 1 to use libv4l2])
                with_libv4l=yes
                have_libv4l=1
            ],
            [                
                AS_IF([test "x$with_libv4l" = "xyes"], [
                    AC_MSG_ERROR([libv4l support enabled but libv4l1, libv4l2 or libv4lconvert package not found])])
                with_libv4l=yes
                have_libv4l=0
            ]
        )]
    )
    AC_SUBST([have_libv4l])
    AM_CONDITIONAL([WITH_LIBV4L], [test "x$with_libv4l" != "xno"])
])
