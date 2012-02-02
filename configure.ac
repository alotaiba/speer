AC_INIT([Speer], [0.0.2])
AM_INIT_AUTOMAKE([1.10 no-define foreign])
AC_CONFIG_HEADERS([config.h])

AC_PROG_CC
AM_PROG_CC_C_O

AC_CHECK_LIB([speex], [speex_bits_init],,AC_MSG_ERROR([speer requires libspeex. Install libspeex first.]))
AC_CHECK_HEADER([stdio.h],,AC_MSG_WARN([STL classes missing ?]))
AC_CHECK_HEADER([stdlib.h],,AC_MSG_WARN([STL classes missing ?]))
AC_CHECK_HEADER([string.h],,AC_MSG_WARN([STL classes missing ?]))
AC_CHECK_HEADER([stdint.h],,AC_MSG_WARN([STL classes missing ?]))
AC_CHECK_HEADER([sys/types.h],,AC_MSG_WARN([STL classes missing ?]))
AC_CHECK_HEADER([sys/stat.h],,AC_MSG_WARN([STL classes missing ?]))
AC_CHECK_HEADER([regex.h],,AC_MSG_WARN([STL classes missing ?]))
AC_CHECK_HEADER([dirent.h],,AC_MSG_WARN([STL classes missing ?]))
AC_CHECK_FUNCS([regcomp])
AC_C_CONST
AC_FUNC_MALLOC
AC_HEADER_DIRENT

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
