AC_DEFUN([FG2_CHECK_EXAMPLES],
[
    AC_ARG_ENABLE([examples],
        [AS_HELP_STRING([--disable-examples], [build without examples and tests])])
    AM_CONDITIONAL([WITH_EXAMPLES], [test "x$enable_examples" != "xno"])
])
