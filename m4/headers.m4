# -*- Autoconf -*-
# headers.m4 - Better location of system headers.

# Check for a header and print an error if not found
AC_DEFUN([AC_ENSURE_HEADER],
[AC_CHECK_HEADER($1,,AC_MSG_FAILURE([Cannot find header $1]))])
