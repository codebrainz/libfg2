AC_DEFUN([FG2_CHECK_EXAMPLES],
[
    AC_ARG_WITH([examples],
        AS_HELP_STRING([--with-examples], [build examples and tests]),
        [with_examples=yes],
        [with_examples=no]
    )
    AM_CONDITIONAL([WITH_EXAMPLES], [test "x$with_examples" = "xyes"])
])
