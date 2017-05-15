AC_DEFUN([FG2_CHECK_SDL1],
[
    AC_ARG_WITH([sdl1],
        [AS_HELP_STRING([--with-sdl1], [build with support for SDL_Surface format for SDL 1 @<:@default=auto@:>@])])
    AS_IF([test "x$with_sdl1" != "xno"], [
        PKG_CHECK_MODULES(
            [SDL1],
            [sdl],
            [
                AC_DEFINE(WITH_SDL1,1,[Define to 1 to use SDL])
                have_sdl1=1
                with_sdl1=yes
            ],
            [
                AS_IF([test "x$with_sdl1" = "xyes"], [
                    AC_MSG_ERROR([SDL 1 support enabled but sdl package not found])])
                have_sdl1=0
                with_sdl1=no
            ]
        )]
    )
    AC_SUBST([have_sdl1])
    AM_CONDITIONAL([WITH_SDL1], [test "x$with_sdl1" != "xno"])
])
