AC_DEFUN([FG2_CHECK_GTK],
[
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
])
