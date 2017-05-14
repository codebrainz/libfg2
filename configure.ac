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
AC_PROG_SED

AC_CHECK_HEADERS([asm/types.h assert.h dirent.h errno.h fcntl.h \
                    linux/videodev2.h stdarg.h stdint.h stdio.h stdlib.h \
                    string.h sys/ioctl.h sys/stat.h sys/time.h sys/types.h \
                    syslog.h time.h unistd.h])

FG2_CHECK_EXAMPLES
FG2_CHECK_GDKPIXBUF
FG2_CHECK_GTK
FG2_CHECK_IMLIB2
FG2_CHECK_LIBJPEG
FG2_CHECK_LIBV4L
FG2_CHECK_OPENCV
FG2_CHECK_PYTHON
FG2_CHECK_SDL
FG2_CHECK_VALA

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
