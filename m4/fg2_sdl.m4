AC_DEFUN([FG2_CHECK_SDL],
[
    AC_ARG_WITH([sdl],
        [AS_HELP_STRING([--with-sdl], [build with support for SDL_Surface format @<:@default=auto@:>@])])
    AS_IF([test "x$with_sdl" != "xno"], [
        PKG_CHECK_MODULES(
            [SDL],
            [sdl],
            [
                AC_DEFINE(WITH_SDL,1,[Define to 1 to use SDL])
                have_sdl=1
                with_sdl=yes
            ],
            [
                AS_IF([test "x$with_sdl" = "xyes"], [
                    AC_MSG_ERROR([SDL support enabled but sdl package not found])])
                have_sdl=0
                with_sdl=no
            ]
        )]
    )
    AC_SUBST([have_sdl])
    AM_CONDITIONAL([WITH_SDL], [test "x$with_sdl" != "xno"])
])
