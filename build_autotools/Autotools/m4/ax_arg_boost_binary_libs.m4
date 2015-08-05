#SYNOPSIS
#
#   AX_ARG_ONLY_BOOST_FILESYSTEM(
#       SELECTED_CONFIG_FLAGS,
#       CONFIG_ARGS_REQUIRED | CONFIG_ARGS_OPTIONAL,
#       [action-if-have],
#       [action-if-have-not])
#
# DESCRIPTION
#
#   Adds the following configure args:
#
#       [REQUIRED | OPTIONAL] Arg: --with-boost-filesystem
#
#   Sets the following m4 script variables:
#
#       SELECTED_CONFIG_FLAGS=<see Macro parameters>
#       HAVE_BOOST_FILESYSTEM=yes|no
#       BOOST_FILESYSTEM_LIBS_PATH=DIR
#
#   Macro parameters:
#
#       SELECTED_CONFIG_FLAGS
#           White space delimited string of user selected config flags are
#           appended to this variable.
#
# LICENSE
#
#   Copyright (c) 2011 Mostafa

AC_DEFUN([AX_ARG_ONLY_BOOST_FILESYSTEM],
[
    SELECTED_CONFIG_FLAGS="$1"
    args_required_param="$2"

    if test "x$args_required_param" != "xCONFIG_ARGS_REQUIRED" &&
       test "x$args_required_param" != "xCONFIG_ARGS_OPTIONAL"
    then
        AC_MSG_ERROR([Invalid attendance argument to AX@&t@_ARG_ONLY_BOOST_FILESYSTEM macro.])
    fi

    HAVE_BOOST_FILESYSTEM="no"
    BOOST_FILESYSTEM_LIBS_PATH=""

    AC_ARG_WITH(
        [boost-filesystem],
        [AS_HELP_STRING(
            [--with-boost-filesystem=DIR],
            [path denoting directory containing a boost filesystem binary library])
        ],
        [
            if test -d "$withval"
            then
                HAVE_BOOST_FILESYSTEM="yes"
                BOOST_FILESYSTEM_LIBS_PATH="$withval"
                SELECTED_CONFIG_FLAGS="$SELECTED_CONFIG_FLAGS --with-boost-filesystem=\"$withval\""
            else
                HAVE_BOOST_FILESYSTEM="no"
                msg="--with-boost-filesystem expected directory name."
                m4_ifval([$4], AC_MSG_WARN([$msg]), AC_MSG_ERROR([$msg]))
            fi
        ],
        [
            HAVE_BOOST_FILESYSTEM="no"

            if test "x$args_required_param" = "xCONFIG_ARGS_REQUIRED"
            then
                msg="--with-boost-filesystem argument missing."
                m4_ifval([$4], AC_MSG_WARN([$msg]), AC_MSG_ERROR([$msg]))
            fi
        ]
    )

    if test "x$HAVE_BOOST_FILESYSTEM" = "xyes"
    then
        dummy_var="yes"
        m4_ifval([$3], [$3])
    else
        dummy_var="yes"
        m4_ifval([$4], [$4])
    fi
])

#SYNOPSIS
#
#   AX_ARG_BOOST_FILESYSTEM(
#       SELECTED_CONFIG_FLAGS,
#       CONFIG_ARGS_REQUIRED | CONFIG_ARGS_OPTIONAL,
#       [action-if-have],
#       [action-if-have-not])
#
# DESCRIPTION
#
#   Adds the following configure args:
#
#       See AX_ARG_ONLY_BOOST_FILESYSTEM
#
#   Sets the following m4 script variables:
#
#       SELECTED_CONFIG_FLAGS=<see Macro parameters>
#
#   Has the following side effects:
#
#       AC_SUBST(BOOST_FILESYSTEM_LIBS_PATH)
#       AM_CONDITIONAL([HAVE_BOOST_FILESYSTEM], ...)
#
#   Macro parameters:
#
#       See AX_ARG_ONLY_BOOST_FILESYSTEM
#
# LICENSE
#
#   Copyright (c) 2011 Mostafa

AC_DEFUN([AX_ARG_BOOST_FILESYSTEM],
[
    m4_ifval([$4], [if_have_not="yes"])
    if test "x$if_have_not" = "xyes"
    then
        AX_ARG_ONLY_BOOST_FILESYSTEM(
            [$1], [$2], [], [dummy_var_to_suppress_error_msgs=""])
    else
        AX_ARG_ONLY_BOOST_FILESYSTEM([$1], [$2])
    fi

    AC_SUBST(BOOST_FILESYSTEM_LIBS_PATH)
    AM_CONDITIONAL(
        [HAVE_BOOST_FILESYSTEM],
        [test "x$HAVE_BOOST_FILESYSTEM" = "xyes"])

    if test "x$HAVE_BOOST_FILESYSTEM" = "xyes"
    then
        dummy_var="yes"
        m4_ifval([$3], [$3])
    else
        dummy_var="yes"
        m4_ifval([$4], [$4])
    fi
])
