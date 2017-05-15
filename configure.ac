AC_PREREQ([2.67])

AC_INIT([libfg2], [0.1], [https://github.com/codebrainz/libfg2/issues])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AM_SILENT_RULES([yes])

AM_PROG_AR
LT_INIT

AC_PROG_CC
AC_PROG_CC_C99
AC_PROG_SED

AC_CHECK_HEADERS([asm/types.h dirent.h fcntl.h linux/videodev2.h \
                  sys/ioctl.h sys/stat.h sys/time.h sys/types.h \
                  syslog.h unistd.h])

FG2_CHECK_EXAMPLES
FG2_CHECK_GDKPIXBUF
FG2_CHECK_GTK2
FG2_CHECK_GTK3
FG2_CHECK_IMLIB2
FG2_CHECK_LIBJPEG
FG2_CHECK_LIBV4L
FG2_CHECK_OPENCV
FG2_CHECK_PYTHON
FG2_CHECK_SDL1
FG2_CHECK_SDL2
FG2_CHECK_VALA

AC_TYPE_MODE_T
AC_TYPE_SSIZE_T
AC_HEADER_MAJOR
AC_CHECK_MEMBERS([struct stat.st_rdev])
AC_CHECK_FUNCS([gettimeofday select strdup strpbrk])

AC_OUTPUT([
    libfg2.h
    Makefile
    gtkcamera/Makefile
    gtkcamera/gtkcamera.pc
    gtkcamera/gtk3camera.pc
    libfg2/Makefile
    libfg2/libfg2-gdkpixbuf.pc
    libfg2/libfg2-imlib2.pc
    libfg2/libfg2-opencv.pc
    libfg2/libfg2-sdl.pc
    libfg2/libfg2-sdl2.pc
    vapi/Makefile
    examples/Makefile
])
