AC_DEFUN([FG2_CHECK_PYTHON],
[
    AC_ARG_WITH([python],
        AS_HELP_STRING([--with-python], [build Python bindings]),
        [with_python=yes],
        [with_python=no]
    )
    AS_IF([test "x$with_python" = "xyes"], [
        AX_PYTHON_DEVEL([>= '2.6'])
        have_python=1
    ], [
        have_python=0
    ])
    AC_SUBST([have_python])
    AM_CONDITIONAL([WITH_PYTHON], [test "x$with_python" = "xyes"])
])
