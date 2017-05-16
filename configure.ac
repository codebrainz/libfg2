AC_PREREQ([2.67])

AC_INIT([libfg2], [0.3], [https://github.com/codebrainz/libfg2/issues])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AM_SILENT_RULES([yes])

#
# Check for tools, compilers, libtool
#
AM_PROG_AR
LT_INIT
AC_PROG_CC
AC_PROG_CC_C99
AC_PROG_SED

#
# Check for non-standard headers, types, members, functions
#
AC_CHECK_HEADERS([asm/types.h dirent.h fcntl.h linux/videodev2.h \
                  sys/ioctl.h sys/stat.h sys/time.h sys/types.h \
                  syslog.h unistd.h])
AC_TYPE_MODE_T
AC_TYPE_SSIZE_T
AC_HEADER_MAJOR
AC_CHECK_MEMBERS([struct stat.st_rdev])
AC_CHECK_FUNCS([gettimeofday select strdup])

#
# Check for libv4l
#
PKG_CHECK_MODULES([LIBV4L], [libv4l2 libv4lconvert])

#
# Check for libjpeg, used for saving frames to file
#
AC_ARG_WITH([jpeg],
    [AS_HELP_STRING([--with-jpeg], [build with support for JPEG format @<:@default=auto@:>@])])
AS_IF([test "x$with_jpeg" != "xno"], [
    PKG_CHECK_MODULES(
        [LIBJPEG],
        [libjpeg],
        [
            AC_DEFINE(WITH_JPEG,1,[Define to 1 to use JPEG library])
            with_jpeg=1
        ],
        [
            AS_IF([test "x$with_jpeg" = "xyes"], [
                AC_MSG_ERROR([JPEG support enabled but libjpeg package not found])])
            with_jpeg=0
        ]
    )]
)
AM_CONDITIONAL([WITH_JPEG], [test $with_jpeg -ne 0])

#
# Check whether to compile examples/tests
#
AC_ARG_ENABLE([examples],
    [AS_HELP_STRING([--disable-examples], [build without examples and tests])])
AM_CONDITIONAL([WITH_EXAMPLES], [test "x$enable_examples" != "xno"])

#
# Substitute version info to output files
#
AC_SUBST([major_version], [0])
AC_SUBST([minor_version], [3])
AC_SUBST([micro_version], [0])

#
# Substitute package dependencies to output files
#
AC_SUBST([with_jpeg])
AS_IF([test $with_jpeg -ne 0],
    [AC_SUBST([package_requires_private], [libjpeg])])

AC_OUTPUT([
    Makefile
    libfg2/libfg2.h
    libfg2/libfg2.pc
    libfg2/Makefile
    examples/Makefile
])
