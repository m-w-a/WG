#SYNOPSIS
#
#   GTEST_BUILTINLIB_CHECK(
#       SELECTED_CONFIG_FLAGS,
#       [action_if_enabled],
#       [action_if_notenabled])
#
#Description
#   Sets the following m4 script variables:
#
#       SELECTED_CONFIG_FLAGS=<see Macro parameters>
#
#   Adds the following configure arguments:
#
#       Args: --enable-gtest
#
#   Sets the following m4 script variables:
#
#       SELECTED_CONFIG_FLAGS=<see Macro parameters>
#
#   Has the following side effects:
#
#       AC_SUBST([ENABLED_GTEST])
#       AM_CONDITIONAL([ENABLED_GTEST], ...)
#
#   Macro parameters:
#
#       SELECTED_CONFIG_FLAGS
#           White space delimited string of user selected config flags are
#           appended to this variable.
#
#   Enable or disable building the gtest library and any unit tests using it.
#
#LICENSE
#
#   Copyright (c) 2013 Mostafa

AC_DEFUN([GTEST_BUILTINLIB_CHECK],
[
    SELECTED_CONFIG_FLAGS="$1"
    AC_ARG_ENABLE(
        [gtest],
        [AS_HELP_STRING(
            [--enable-gtest=@<:@yes@:>@],
            [Enable tests using the Google C++ Testing Framework.
            Valid input is: yes, or no. No input defaults to the input value 'yes'.])
        ],
        [
            SELECTED_CONFIG_FLAGS="$SELECTED_CONFIG_FLAGS --enable-gtest=\"$enableval\""
            ENABLED_GTEST="$enableval"
        ],
        [
            ENABLED_GTEST="no"
        ])
    
    if test "x$ENABLED_GTEST" != "xyes" && test "x$ENABLED_GTEST" != "xno"
    then
        AC_MSG_ERROR([Invalid input to --enable-gtest])
    fi
    
    AC_SUBST([ENABLED_GTEST])
    AM_CONDITIONAL([ENABLED_GTEST],[test "x$ENABLED_GTEST" = "xyes"])
    AS_IF([test "x$ENABLED_GTEST" = "xyes"],
      [m4_ifval([$2], [$2])],
      [m4_ifval([$3], [$3])])
])
