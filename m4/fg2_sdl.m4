AC_DEFUN([FG2_CHECK_SDL],
[
    AC_ARG_WITH([sdl],
        AS_HELP_STRING([--with-sdl], [build with support for SDL_Surface format]),
        [with_sdl=yes],
        [with_sdl=no]
    )
    AS_IF([test "x$with_sdl" = "xyes"], [
            PKG_CHECK_MODULES(
                [sdl],
                [sdl],
                [
                    AC_DEFINE(WITH_SDL,1,[Define to 1 to use SDL])
                    have_sdl=1
                ],
                [
                    have_sdl=0
                ]
            )]
    )
    AC_SUBST([have_sdl])
    AM_CONDITIONAL([WITH_SDL], [test "x$with_sdl" = "xyes"])
])
