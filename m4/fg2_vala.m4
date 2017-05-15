AC_DEFUN([FG2_CHECK_VALA],
[
    AC_ARG_WITH([vala],
        [AS_HELP_STRING([--with-vala], [build Vala vapi bindings])])
    AS_IF([test "x$with_vala" != "xno"], [
        AM_PROG_VALAC([0.10], [
            with_vala=yes
            have_vala=1
        ], [
            AS_IF([test "x$with_vala" = "xyes"],[
                AC_MSG_ERROR([Vala support enabled but valac compiler not found])])
            with_vala=no
            have_vala=0
        ])],
    [
        with_vala=no
        have_vala=0
    ])
    AC_SUBST([have_vala])
    AM_CONDITIONAL([WITH_VALA], [test "x$with_vala" != "xno"])
])
