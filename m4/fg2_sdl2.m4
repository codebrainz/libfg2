AC_DEFUN([FG2_CHECK_SDL2],
[
    AC_ARG_WITH([sdl2],
        [AS_HELP_STRING([--with-sdl2], [build with support for SDL_Surface format for SDL 2 @<:@default=auto@:>@])])
    AS_IF([test "x$with_sdl2" != "xno"], [
        PKG_CHECK_MODULES(
            [SDL2],
            [sdl2],
            [
                AC_DEFINE(WITH_SDL2,1,[Define to 1 to use SDL 2])
                have_sdl2=1
                with_sdl2=yes
            ],
            [
                AS_IF([test "x$with_sdl2" = "xyes"], [
                    AC_MSG_ERROR([SDL 2 support enabled but sdl2 package not found])])
                have_sdl2=0
                with_sdl2=no
            ]
        )]
    )
    AC_SUBST([have_sdl2])
    AM_CONDITIONAL([WITH_SDL2], [test "x$with_sdl2" != "xno"])
])
