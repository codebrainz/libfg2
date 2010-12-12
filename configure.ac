AC_PREREQ([2.68])

AC_INIT([libfg2], [0.1], [https://github.com/codebrainz/libfg2/issues])
AM_INIT_AUTOMAKE([libfg2], [0.1])
LT_INIT

AC_CONFIG_SRCDIR([include/libfg2.h])
AC_CONFIG_HEADERS([config.h])

AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S

AC_CHECK_LIB([m], [main])
AC_CHECK_LIB([pthread], [main])
AC_CHECK_LIB([rt], [main])

AC_CHECK_HEADERS([fcntl.h stddef.h stdint.h stdlib.h string.h sys/ioctl.h \
                    sys/time.h syslog.h unistd.h assert.h dirent.h errno.h \
                    fcntl.h math.h pwd.h signal.h stdarg.h stddef.h stdint.h \
                    stdio.h stdlib.h string.h time.h unistd.h asm/types.h \
                    linux/videodev2.h linux/videodev.h sys/ioctl.h syslog.h \
                    sys/mman.h sys/stat.h sys/time.h sys/types.h sys/wait.h])

AC_DEFINE([WITH_GDKPIXBUF], [], [Support GdkPixbuf])
AC_DEFINE([WITH_GTK], [], [Build GTK widget])
AC_DEFINE([WITH_IMLIB2], [], [Support Imlib_Image])
AC_DEFINE([WITH_JPEGLIB], [], [Support JPEG format])
AC_DEFINE([WITH_OPENCV], [], [Support IplImage])
AC_DEFINE([WITH_SDL], [], [Support SDL_Surface])

AC_ARG_WITH([gdkpixbuf], AS_HELP_STRING([--with-gdkpixbuf], [
        build with support for GdkPixbuf format]))   
AS_IF([test "x$with_gdkpixbuf" = "xyes"], [
        PKG_CHECK_MODULES([GDKPIXBUF], [gdk-pixbuf-2.0], [
            AC_DEFINE(WITH_GDKPIXBUF)])])

AC_ARG_WITH([gtk], AS_HELP_STRING([--with-gtk], [
        build the GtkCamera widget]))
AS_IF([test "x$with_gtk" = "xyes"],[
        PKG_CHECK_MODULES([GTK], [gtk+-2.0], [AC_DEFINE(WITH_GTK)])])
   
AC_ARG_WITH([imlib2], AS_HELP_STRING([--with-imlib2], [
        build with support for Imlib_Image format])) 
AS_IF([test "x$with_imlib2" = "xyes"], [
        PKG_CHECK_MODULES([IMLIB2], [imlib2], [AC_DEFINE(WITH_IMLIB2)])])
             
AC_ARG_WITH([jpeglib], AS_HELP_STRING([--without-jpeglib], [
        do not build with support for JPEG format]), [], [with_jpeglib=no])     
AS_IF([test "x$with_jpeglib" = "xyes"], [
        AC_CHECK_LIB([libjpeg], [jpeg_create_compress], [
            AC_DEFINE(WITH_JPEGLIB)])])
            
AC_ARG_WITH([libv4l], AS_HELP_STRING([--without-libv4l], [
        do not build libv4l]), [], [with_libv4l=no])
AS_IF([test "x$with_libv4l" = "xno"], [
        PKG_CHECK_MODULES([LIBV4L], [libv4l1 libv4l2 libv4lconvert])])
 
AC_ARG_WITH([opencv], AS_HELP_STRING([--with-opencv], [
        build with support for IplImage format]))           
AS_IF([test "x$with_opencv" = "xyes"], [
        PKG_CHECK_MODULES([OPENCV], [opencv], [AC_DEFINE(WITH_OPENCV)])])

AC_ARG_WITH([python], AS_HELP_STRING([--with-python], [build Python bindings]))
AS_IF([test "x$with_python" = "xyes"], [AC_CHECK_HEADER(Python)])

AC_ARG_WITH([sdl], AS_HELP_STRING([--with-sdl], [
        build with support for SDL_Surface format]))      
AS_IF([test "x$with_sdl" = "xyes"], [
        PKG_CHECK_MODULES([SDL], [sdl], [AC_DEFINE(WITH_SDL)])])

AC_ARG_WITH([vala], AS_HELP_STRING([--with-vala], [ build Vala vapi bindings]))
AS_IF([test "x$with_vala" = "xyes"], [PKG_CHECK_MODULES([VALA], [vala-1.0])])

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

AC_FUNC_ERROR_AT_LINE
AC_FUNC_FORK
AC_HEADER_MAJOR
AC_FUNC_MALLOC
AC_FUNC_MMAP
AC_FUNC_REALLOC
AC_CHECK_FUNCS([dup2 ftruncate gettimeofday memset munmap select strdup \
                    strerror strpbrk strstr strtol])

AC_OUTPUT(Makefile src/Makefile)
