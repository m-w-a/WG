dnl GTEST_LIB_CHECK(
dnl     SELECTED_CONFIG_FLAGS,
dnl     [minimum_version],
dnl     [action_if_found],
dnl     [action_if_not_found])
dnl
dnl Sets the following m4 script variables:
dnl
dnl     SELECTED_CONFIG_FLAGS=<see Macro parameters>
dnl
dnl Has the following side effects:
dnl 
dnl  AC_ARG_VAR([GTEST_CONFIG], ...)
dnl  AC_ARG_VAR([GTEST_CPPFLAGS], ...)
dnl  AC_DEFINE([HAVE_GTEST], ...)
dnl  AC_ARG_VAR([GTEST_CXXFLAGS], ...)
dnl  AC_ARG_VAR([GTEST_LDFLAGS], ...)
dnl  AC_ARG_VAR([GTEST_LIBS], ...)
dnl  AC_ARG_VAR([GTEST_VERSION], ...)
dnl  AC_SUBST([HAVE_GTEST])
dnl  AM_CONDITIONAL([HAVE_GTEST], ...)
dnl
dnl Macro parameters:
dnl
dnl     SELECTED_CONFIG_FLAGS
dnl         White space delimited string of user selected config flags are
dnl         appended to this variable.
dnl
dnl Check for the presence of the Google Test library, optionally at a minimum
dnl version, and indicate a viable version with the HAVE_GTEST flag. It defines
dnl standard variables for substitution including GTEST_CPPFLAGS,
dnl GTEST_CXXFLAGS, GTEST_LDFLAGS, and GTEST_LIBS. It also defines
dnl GTEST_VERSION as the version of Google Test found. Finally, it provides
dnl optional custom action slots in the event GTEST is found or not.
dnl If action_if_not_found is specified then only warning messages will be 
dnl displayed in the case of failure, else error messages will be displayed.
AC_DEFUN([GTEST_LIB_CHECK],
[
SELECTED_CONFIG_FLAGS="$1"
dnl Provide a flag to enable or disable Google Test usage.
AC_ARG_ENABLE([gtest],
  [AS_HELP_STRING([--enable-gtest],
                  [Enable tests using the Google C++ Testing Framework.
                  Valid input is: yes, no, or grandparent path of gtest-config script (i.e., /opt/local). If input is yes, then gtest-config is searched for in $PATH environment variable. Required minimum version: $2.])],
  [
    SELECTED_CONFIG_FLAGS="$SELECTED_CONFIG_FLAGS --enable-gtest=\"$enableval\""
    enable_gtest="$enableval"
  ],
  [enable_gtest=])
AC_ARG_VAR([GTEST_CONFIG],
           [The exact path of Google Test's 'gtest-config' script.])
AC_ARG_VAR([GTEST_CPPFLAGS],
           [C-like preprocessor flags for Google Test.])
AC_ARG_VAR([GTEST_CXXFLAGS],
           [C++ compile flags for Google Test.])
AC_ARG_VAR([GTEST_LDFLAGS],
           [Linker path and option flags for Google Test.])
AC_ARG_VAR([GTEST_LIBS],
           [Library linking flags for Google Test.])
AC_ARG_VAR([GTEST_VERSION],
           [The version of Google Test available.])
HAVE_GTEST="no"
AS_IF([test "x${enable_gtest}" != "xno"],
  [AC_MSG_CHECKING([for 'gtest-config'])
   AS_IF([test "x${enable_gtest}" != "xyes"],
     [AS_IF([test -x "${enable_gtest}/scripts/gtest-config"],
        [GTEST_CONFIG="${enable_gtest}/scripts/gtest-config"],
        [GTEST_CONFIG="${enable_gtest}/bin/gtest-config"])
      AS_IF([test -x "${GTEST_CONFIG}"], [],
        [AC_MSG_RESULT([no])
         msg="Unable to locate either a built or installed Google Test. The specific location '${enable_gtest}' was provided for a built or installed Google Test, but no 'gtest-config' script could be found at this location."
         m4_if([$4], [], AC_MSG_ERROR([$msg]), AC_MSG_WARN([$msg]))
         ])],
     [AC_PATH_PROG([GTEST_CONFIG], [gtest-config])])
   AS_IF([test -x "${GTEST_CONFIG}"],
     [AC_MSG_RESULT([${GTEST_CONFIG}])
      m4_ifval([$2],
        [_gtest_min_version="--min-version=$2"
         AC_MSG_CHECKING([for Google Test at least version >= $2])],
        [_gtest_min_version="--min-version=0"
         AC_MSG_CHECKING([for Google Test])])
      AS_IF([${GTEST_CONFIG} ${_gtest_min_version}],
        [AC_MSG_RESULT([yes])
         HAVE_GTEST='yes'],
        [AC_MSG_RESULT([no])])],
     [AC_MSG_RESULT([no])])
   AS_IF([test "x${HAVE_GTEST}" = "xyes"],
     [GTEST_CPPFLAGS=`${GTEST_CONFIG} --cppflags`
      GTEST_CXXFLAGS=`${GTEST_CONFIG} --cxxflags`
      GTEST_LDFLAGS=`${GTEST_CONFIG} --ldflags`
      GTEST_LIBS=`${GTEST_CONFIG} --libs`
      GTEST_VERSION=`${GTEST_CONFIG} --version`
      AC_DEFINE([HAVE_GTEST],[1],[Defined when Google Test is available.])],
     [AS_IF([test "x${enable_gtest}" = "xyes"],
        [
            msg="Google Test was enabled, but no viable version could be found."
            m4_if([$4], [], AC_MSG_ERROR([$msg]), AC_MSG_WARN([$msg]))
        ])])])
AC_SUBST([HAVE_GTEST])
AM_CONDITIONAL([HAVE_GTEST],[test "x$HAVE_GTEST" = "xyes"])
AS_IF([test "x$HAVE_GTEST" = "xyes"],
  [m4_ifval([$3], [$3])],
  [m4_ifval([$4], [$4])])
])
