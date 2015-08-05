#SYNOPSIS
#   AX_ARG_ONLY_REQUIRED_ICU(
#       SELECTED_CONFIG_FLAGS,
#       min_version, 
#       [action-if-found], 
#       [action-if-not-found])
#
#DESCRIPTION
#
#   Adds the following configure arguments:
#
#       REQUIRED Arg: --with-icu
#
#   Sets the following m4 script variables:
#
#       SELECTED_CONFIG_FLAGS=<see Macro parameters>
#       For the rest see AX_CHECK_ICU
#
#   Macro parameters:
#
#       SELECTED_CONFIG_FLAGS
#           White space delimited string of user selected config flags are
#           appended to this variable.
#
#       action-if-not-found
#           If this is specified then only warning messages
#           will be displayed, else error messages will be displayed.
#
#   Test for the ICU library of a particular version (or newer).
#
#LICENSE
#
#   Copyright (c) 2011 Mostafa

AC_DEFUN([AX_ARG_ONLY_REQUIRED_ICU],
[
    SELECTED_CONFIG_FLAGS="$1"
    min_version_param="$2"

    AC_ARG_WITH(
        [icu],
        [AS_HELP_STRING(
            [--with-icu=DIR],
            [parent path of desired icu-config script.])
        ],
        [
            if test -d "$withval"
            then
                icu_config_parent_path="$withval"
                SELECTED_CONFIG_FLAGS="$SELECTED_CONFIG_FLAGS --with-icu=\"$withval\""
            else
                msg="--with-icu expected directory name."
                m4_ifval([$4], AC_MSG_WARN([$msg], AC_MSG_ERROR([$msg]))
            fi
        ]
        [
            msg="--with-icu expected directory name."
            m4_ifval([$4], AC_MSG_WARN([$msg], AC_MSG_ERROR([$msg]))
        ]
    )

    m4_ifval([$4], error_handling="WARN", error_handling="ERROR")
    AX_CHECK_ICU([$min_version_param], [$icu_config_parent_path], [$error_handling])

    if test "x$HAVE_ICU" = "xyes"
    then
        dummy_var="yes"
        m4_ifval([$3], [$3])
    else
        dummy_var="yes"
        m4_ifval([$4], [$4])
    fi
])

#SYNOPSIS
#   AX_ARG_REQUIRED_ICU(
#       SELECTED_CONFIG_FLAGS,
#       min_version,
#       [action-if-found],
#       [action-if-not-found])
#
#DESCRIPTION
#
#   Adds the following configure arguments:
#
#       See AX_ARG_ONLY_REQUIRED_ICU
#
#   Sets the following m4 script variables:
#
#       SELECTED_CONFIG_FLAGS=<see Macro parameters>
#
#   Has the following side effects:
#
#       See AX_SET_ICU
#
#   Macro parameters:
#
#       See AX_ARG_ONLY_REQUIRED_ICU
#
#   Test for the ICU library of a particular version (or newer).
#
#LICENSE
#
#   Copyright (c) 2011 Mostafa

AC_DEFUN([AX_ARG_REQUIRED_ICU],
[
    SELECTED_CONFIG_FLAGS="$1"
    min_version_param="$2"

    m4_ifval([$4], [have_if_not="yes"])
    if test "x$have_if_not" = "xyes"
    then
        AX_ARG_ONLY_REQUIRED_ICU(
            [$SELECTED_CONFIG_FLAGS],
            [$min_version_param], 
            [],
            [dummy_var_to_suppress_error_msgs="yes"])
    else
        AX_ARG_ONLY_REQUIRED_ICU([$SELECTED_CONFIG_FLAGS], [$min_version_param])
    fi

    AX_SET_ICU([$HAVE_ICU], [$ICU_CONFIG])

    if test "x$HAVE_ICU" = "xyes"
    then
        dummy_var="yes"
        m4_ifval([$3], [$3])
    else
        dummy_var="yes"
        m4_ifval([$4], [$4])
    fi
])

#SYNOPSIS
#   AX_ARG_ONLY_OPTIONAL_ICU(
#       SELECTED_CONFIG_FLAGS,
#       min_version, 
#       [action-if-found], 
#       [action-if-not-found])
#
#DESCRIPTION
#
#   Sets the following m4 script variables:
#
#       SELECTED_CONFIG_FLAGS=<see Macro parameters>
#       See AX_CHECK_ICU
#
#   Adds the following configure arguments:
#
#       OPTIONAL Arg: --with-icu
#
#   Macro parameters:
#
#       SELECTED_CONFIG_FLAGS
#           White space delimited string of user selected config flags are
#           appended to this variable.
#
#       action-if-not-found
#           If this is specified then only warning messages
#           will be displayed, else error messages will be displayed.
#
#   Test for the ICU library of a particular version (or newer).
#
#LICENSE
#
#   Copyright (c) 2011 Mostafa

AC_DEFUN([AX_ARG_ONLY_OPTIONAL_ICU],
[
    SELECTED_CONFIG_FLAGS="$1"
    min_version_param="$2"

    AC_ARG_WITH(
        [icu],
        [AS_HELP_STRING(
            [--with-icu=@<:@yes@:>@],
            [yes, no, or parent path of desired icu-config script. If yes then the $PATH environment variable is searched for an icu-config script.])
        ],
        [
            config_arg_is_valid=no

            if test "x$withval" = "xyes"
            then
                config_arg_is_valid=yes
                icu_config_parent_path="yes"
            elif test "x$withval" = "xno"
            then
                config_arg_is_valid=yes
                icu_config_parent_path="no"
            elif test -d "$withval"
            then
                config_arg_is_valid=yes
                icu_config_parent_path="$withval"
            else
                msg="--with-icu expected directory name."
                m4_ifval([$4], AC_MSG_WARN([$4]), AC_MSG_ERROR([$4]))
            fi

            if test "x$config_arg_is_valid" = "xyes"
            then
                SELECTED_CONFIG_FLAGS="$SELECTED_CONFIG_FLAGS --with-icu=\"$withval\""
            fi
        ],
        [
            icu_config_parent_path="no"
        ]
    )

    m4_ifval([$4], [error_handling="WARN"], [error_handling="ERROR"])
    AX_CHECK_ICU([$min_version_param], [$icu_config_parent_path], [$error_handling])

    if test "x$HAVE_ICU" = "xyes"
    then
        dummy_var="yes"
        m4_ifval([$3], [$3])
    else
        dummy_var="yes"
        m4_ifval([$4], [$4])
    fi
])

#SYNOPSIS
#   AX_ARG_OPTIONAL_ICU(
#       SELECTED_CONFIG_FLAGS,
#       min_version, 
#       [action-if-found], 
#       [action-if-not-found])
#
#DESCRIPTION
#
#   Sets the following m4 script variables:
#
#       SELECTED_CONFIG_FLAGS=<see Macro parameters>
#
#   Adds the following configure arguments:
#
#       See AX_ARG_ONLY_OPTIONAL_ICU
#
#   Has the following side effects:
#
#       See AX_SET_ICU
#
#   Macro parameters:
#
#       See AX_ARG_ONLY_OPTIONAL_ICU
#
#   Test for the ICU library of a particular version (or newer).
#
#LICENSE
#
#   Copyright (c) 2011 Mostafa

AC_DEFUN([AX_ARG_OPTIONAL_ICU],
[
    SELECTED_CONFIG_FLAGS="$1"
    min_version_param="$2"

    m4_ifval([$4], [have_if_not="yes"])
    if test "x$have_if_not" = "xyes"
    then
        AX_ARG_ONLY_OPTIONAL_ICU(
            [$SELECTED_CONFIG_FLAGS],
            [$min_version_param], 
            [], 
            [dummy_var_to_suppress_error_msgs="yes"])
    else
        AX_ARG_ONLY_OPTIONAL_ICU([$SELECTED_CONFIG_FLAGS], [$min_version_param])
    fi

    AX_SET_ICU([$HAVE_ICU], [$ICU_CONFIG])

    if test "x$HAVE_ICU" = "xyes"
    then
        dummy_var="yes"
        m4_ifval([$3], [$3])
    else
        dummy_var="yes"
        m4_ifval([$4], [$4])
    fi
])

# ===========================================================================
#       http://www.gnu.org/software/autoconf-archive/ax_check_icu.html
# ===========================================================================
#
# SYNOPSIS
#
#   AX_CHECK_ICU(
#       min_version, 
#       icu_config_parent_path, 
#       WARN | ERROR)
#
# DESCRIPTION
#
#   Sets the following m4 script variables:
#
#       HAVE_ICU=yes|no
#       ICU_CONFIG="absolute filepath of icu-config" | "empty string"
#
#   Macro parameters:
#
#       icu_config_parent_path
#           Yes, no, or path to icu-config script. If "yes", then $PATH is searched
#           for said script, else if "no", then all side effects are either negative
#           or empty, with the former having precedence.
#
#       WARN | ERROR
#           Whether to error or warn if this check fails.
#
#   Searches for icu-config script with min_version in icu_config_path.
#
# LICENSE
#
#   Copyright (c) 2008 Akos Maroy <darkeye@tyrell.hu>
#   Copyright (c) 2011 Mostafa
#
#   Copying and distribution of this file, with or without modification, are
#   permitted in any medium without royalty provided the copyright notice
#   and this notice are preserved. This file is offered as-is, without any
#   warranty.

AC_DEFUN([AX_CHECK_ICU],
[
  if_found=no
  version=$1
  icu_config_parent_path=$2
  error_handling=$3

  if test "x$error_handling" != "xERROR" &&
     test "x$error_handling" != "xWARN"
  then
    AC_MSG_ERROR([Invalid error-handling argument to AX@&t@_CHECK_ICU macro.])
  fi

  if test "x$icu_config_parent_path" != "xno"
  then
    if test -z "$icu_config_parent_path" ||
       test "x$icu_config_parent_path" = "xyes"
    then
        AC_PATH_PROG(ICU_CONFIG, icu-config, no)
    else
        if test -d "$icu_config_parent_path"; then
            AC_PATH_PROG(ICU_CONFIG, icu-config, no, $icu_config_parent_path)
        else
            msg="--with-icu-config expected directory name"
            ICU_CONFIG="no"

            if test "x$error_handling" = "xWARN"
            then
                dummy_var="yes"
                AC_MSG_WARN([$msg])
            else
                dummy_var="yes"
                AC_MSG_ERROR([$msg])
            fi
        fi
    fi
    
    if test "$ICU_CONFIG" = "no"
    then
        msg="
*** The icu-config script could not be found. Make sure it is
*** in your path, and that taglib is properly installed.
*** Or see http://ibm.com/software/globalization/icu/"

        if test "x$error_handling" = "xWARN"
        then
            dummy_var="yes"
            AC_MSG_WARN([$msg])
        else
            dummy_var="yes"
            AC_MSG_ERROR([$msg])
        fi
    else
        ICU_VERSION=`$ICU_CONFIG --version`
        AC_MSG_CHECKING(for ICU >= $1)
        VERSION_CHECK=`expr $ICU_VERSION \>\= $1`
    
        if test "$VERSION_CHECK" = "1" ; then
            AC_MSG_RESULT(yes)
            if_found="yes"
        else
            AC_MSG_RESULT(no)
            if_found=no
            msg="Can't find ICU >= $1."

            if test "x$error_handling" = "xWARN"
            then
                dummy_var="yes"
                AC_MSG_WARN([$msg])
            else
                dummy_var="yes"
                AC_MSG_ERROR([$msg])
            fi
        fi
    fi
  else
    if_found="no"
  fi

  if test "x$if_found" = "xyes"
  then
    HAVE_ICU="yes"
  else
    HAVE_ICU="no"
    ICU_CONFIG=""
  fi

])

#SYNOPSIS
#
#   AX_SET_ICU(HAVE_ICU, ICU_CONFIG_FILEPATH)
#
#DESCRIPTION
#
#   Has the following side effects:
#
#       AC_SUBST(ICU_CPPFLAGS)
#       AC_SUBST(ICU_CFLAGS)
#       AC_SUBST(ICU_CXXFLAGS)
#       AC_SUBST(ICU_LDFLAGS)
#       if test "x$HAVE_ICU" = "xyes"
#       then
#           AC_DEFINE([HAVE_ICU], [1], [ICU is available.])
#       fi
#       AM_CONDITIONAL([HAVE_ICU], [test "x$HAVE_ICU" = "xyes"])
#
#       See icu-config(1) man page.
#
#   Macro parameters:
#
#       HAVE_ICU=yes|no
#
#LICENSE
#
#   Copyright (c) 2011 Mostafa

AC_DEFUN([AX_SET_ICU],
[
  ICU_CONFIG_PATH=$2

  HAVE_ICU=$1

  if test "x$HAVE_ICU" = "xyes"
  then
    ICU_CPPFLAGS=`$ICU_CONFIG --cppflags`
    ICU_CFLAGS=`$ICU_CONFIG --cflags`
    ICU_CXXFLAGS=`$ICU_CONFIG --cxxflags`
    ICU_LDFLAGS=`$ICU_CONFIG --ldflags`
  else
    ICU_CPPFLAGS=""
    ICU_CFLAGS=""
    ICU_CXXFLAGS=""
    ICU_LDFLAGS=""
  fi

  AC_SUBST(ICU_CPPFLAGS)
  AC_SUBST(ICU_CFLAGS)
  AC_SUBST(ICU_CXXFLAGS)
  AC_SUBST(ICU_LDFLAGS)
  if test "x$HAVE_ICU" = "xyes"
  then
    AC_DEFINE([HAVE_ICU], [1], [ICU is available.])
  fi
  AM_CONDITIONAL([HAVE_ICU], [test "x$HAVE_ICU" = "xyes"])
])
