AC_PREREQ([2.67])

AC_INIT([libfg2], [0.1], [https://github.com/codebrainz/libfg2/issues])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AM_SILENT_RULES([yes])

AM_PROG_AR
LT_INIT

AC_PROG_CC
AC_PROG_SED

AC_CHECK_HEADERS([asm/types.h assert.h dirent.h errno.h fcntl.h \
                    linux/videodev2.h stdarg.h stdint.h stdio.h stdlib.h \
                    string.h sys/ioctl.h sys/stat.h sys/time.h sys/types.h \
                    syslog.h time.h unistd.h])

#-------------------------------------------------------------------------------
# libv4l
AC_ARG_WITH([libv4l],
    AS_HELP_STRING([--without-libv4l], [do not build with support for libv4l]),
    [with_libv4l=no],
    [with_libv4l=yes]
)
AS_IF([test "x$with_libv4l" = "xyes"], [
        PKG_CHECK_MODULES(
            [libv4l],
            [libv4l1 libv4l2 libv4lconvert],
            [AC_DEFINE(WITH_LIBV4L,1,[Define to 1 to use libv4l2])]
        )]
)
AM_CONDITIONAL([WITH_LIBV4L], [test "x$with_libv4l" = "xyes"])
#-------------------------------------------------------------------------------
# JPEG Library
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
#-------------------------------------------------------------------------------
# GdkPixbuf
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
#-------------------------------------------------------------------------------
# Gtk+
AC_ARG_WITH([gtk],
    AS_HELP_STRING([--with-gtk], [build the GtkCamera widget]),
    [with_gtk=yes],
    [with_gtk=no]
)
AS_IF([test "x$with_gtk" = "xyes"], [
        PKG_CHECK_MODULES(
            [gtk],
            [gtk+-2.0],
            [AC_DEFINE(WITH_GTK,1,[Define to 1 to use Gtk+])]
        )]
)
AM_CONDITIONAL([WITH_GTK], [test "x$with_gtk" = "xyes"])
#-------------------------------------------------------------------------------
# Imlib2
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
#-------------------------------------------------------------------------------
# OpenCV
AC_ARG_WITH([opencv],
    AS_HELP_STRING([--with-opencv], [build with support for IplImage format]),
    [with_opencv=yes],
    [with_opencv=no]
)
AS_IF([test "x$with_opencv" = "xyes"], [
        PKG_CHECK_MODULES(
            [opencv],
            [opencv],
            [AC_DEFINE(WITH_OPENCV,1,[Define to 1 to use OpenCV])]
        )]
)
AM_CONDITIONAL([WITH_OPENCV], [test "x$with_opencv" = "xyes"])
#-------------------------------------------------------------------------------
# SDL
AC_ARG_WITH([sdl],
    AS_HELP_STRING([--with-sdl], [build with support for SDL_Surface format]),
    [with_sdl=yes],
    [with_sdl=no]
)
AS_IF([test "x$with_sdl" = "xyes"], [
        PKG_CHECK_MODULES(
            [sdl],
            [sdl],
            [AC_DEFINE(WITH_SDL,1,[Define to 1 to use SDL])]
        )]
)
AM_CONDITIONAL([WITH_SDL], [test "x$with_sdl" = "xyes"])
#-------------------------------------------------------------------------------
# Python
AC_ARG_WITH([python],
    AS_HELP_STRING([--with-python], [build Python bindings]),
    [with_python=yes],
    [with_python=no]
)
AS_IF([test "x$with_python" = "xyes"], [AX_PYTHON_DEVEL([>= '2.6'])])
AM_CONDITIONAL([WITH_PYTHON], [test "x$with_python" = "xyes"])
#-------------------------------------------------------------------------------
# Vala
AC_ARG_WITH([vala],
    AS_HELP_STRING([--with-vala], [build Vala vapi bindings]),
    [with_vala=yes],
    [with_vala=no]
)
AS_IF([test "x$with_vala" = "xyes"], [AM_PROG_VALAC([0.10])])
AM_CONDITIONAL([WITH_VALA], [test "x$with_vala" = "xyes"])
#-------------------------------------------------------------------------------
# Examples and Tests
AC_ARG_WITH([examples],
    AS_HELP_STRING([--with-examples], [build examples and tests]),
    [with_examples=yes],
    [with_examples=no]
)
AM_CONDITIONAL([WITH_EXAMPLES], [test "x$with_examples" = "xyes"])
#-------------------------------------------------------------------------------

# TODO: check these
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT64_T
AC_TYPE_MODE_T
AC_TYPE_OFF_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_CHECK_MEMBERS([struct stat.st_rdev])
AC_TYPE_UINT16_T
AC_TYPE_UINT8_T

# TODO: check these too
AC_FUNC_ERROR_AT_LINE
AC_FUNC_FORK
AC_HEADER_MAJOR
AC_FUNC_MALLOC
AC_FUNC_MMAP
AC_FUNC_REALLOC
AC_CHECK_FUNCS([dup2 ftruncate gettimeofday memset munmap select strdup \
                    strerror strpbrk strstr strtol])

AC_OUTPUT([
    Makefile
    gtkcamera/Makefile
    gtkcamera/gtkcamera.pc
    libfg2/Makefile
    libfg2/libfg2-gdkpixbuf.pc
    libfg2/libfg2-imlib2.pc
    libfg2/libfg2-opencv.pc
    libfg2/libfg2-sdl.pc
    vapi/Makefile
    examples/Makefile
])
