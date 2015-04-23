#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([skall], [0.1])
AC_CONFIG_SRCDIR([src/skall.c])
AC_CONFIG_HEADERS([include/config.h])
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([readline], [readline])

# Checks for header files.
AC_CHECK_HEADERS([inttypes.h stddef.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_TYPE_UINT32_T

# Checks for library functions.
AC_FUNC_FORK
AC_FUNC_MALLOC
AC_CHECK_FUNCS([getcwd setenv strchr strdup strndup])

AC_CONFIG_FILES([
  Makefile
  src/Makefile
])
AC_OUTPUT
