AC_DEFUN([FG2_CHECK_VALA],
[
    AC_ARG_WITH([vala],
        AS_HELP_STRING([--with-vala], [build Vala vapi bindings]),
        [with_vala=yes],
        [with_vala=no]
    )
    AS_IF([test "x$with_vala" = "xyes"], [
        AM_PROG_VALAC([0.10])
        have_vala=1
    ], [
        have_vala=0
    ])
    AC_SUBST([have_vala])
    AM_CONDITIONAL([WITH_VALA], [test "x$with_vala" = "xyes"])
])
