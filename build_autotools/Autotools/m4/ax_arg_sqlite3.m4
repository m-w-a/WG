#SYNOPSIS
#
#   AX_ARG_ONLY_SQLITE3(
#       SELECTED_CONFIG_FLAGS,
#       CONFIG_ARGS_REQUIRED | CONF_ARGS_OPTIONAL,
#       [MINIMUM-VERSION],
#       [ACTION-IF-FOUND],
#       [ACTION-IF-NOT-FOUND])
#
# DESCRIPTION
#
#   Adds the following configure arguments:
#
#       [REQUIRED | OPTIONAL] Arg: --with-sqlite3-headers
#       [REQUIRED | OPTIONAL] Arg: --with-sqile3-libs
#
#   Sets the following m4 script variables:
#
#       SELECTED_CONFIG_FLAGS=<see Macro parameters>
#       HAVE_SQLITE3=yes|no
#       SQLITE3_INCLUDES_PATH=DIR
#       SQLITE3_LIBS_PATH=DIR
#
#   Macro parameters:
#
#       SELECTED_CONFIG_FLAGS
#           White space delimited string of user selected config flags are
#           appended to this variable.
#
#       MINIMUM-VERSION :
#           Required minimum version of the Sqlite 3 library. If required 
#           version not passed in, 3.0.0 is used.
#
#       ACTION-IF-NOT-FOUND
#           If this parameter is specified then only warning messages
#           will be outputted if Sqlite with the required version is not
#           found, else error messages will be outputted.
#
#   Test for the SQLite 3 library of a particular version (or newer).
#
# LICENSE
#
#   Copyright (c) 2008 Mateusz Loskot <mateusz@loskot.net>
#   Copyright (c) 2010 Mostafa
#
#   Copying and distribution of this file, with or without modification, are
#   permitted in any medium without royalty provided the copyright notice
#   and this notice are preserved. This file is offered as-is, without any
#   warranty.

AC_DEFUN([AX_ARG_ONLY_SQLITE3],
[
    SELECTED_CONFIG_FLAGS="$1"
    args_required_param="$2"
    min_version_param="$3"

    HAVE_SQLITE3="no"
    SQLITE3_INCLUDES_PATH=""
    SQLITE3_LIBS_PATH=DIR=""

    if test "x$args_required_param" != "xCONFIG_ARGS_REQUIRED" &&
       test "x$args_required_param" != "xCONFIG_ARGS_OPTIONAL"
    then
        AC_MSG_ERROR([Invalid attendance argument to AX@&t@_ARG_ONLY_SQLITE3 macro.])
    fi

    AC_ARG_WITH(
        [sqlite3-headers],
        [AS_HELP_STRING(
            [--with-sqlite3-headers=DIR],
            [path denoting directory of sqlite3.h])
        ],
        [
            WANT_SQLITE3="yes"

            if test -d "$withval"
            then
                SQLITE3_INCLUDES_PATH="$withval"
                SELECTED_CONFIG_FLAGS="$SELECTED_CONFIG_FLAGS --with-sqlite3-headers=\"$withval\""
            else
                msg="--with-sqlite3-headers expected directory name."
                m4_ifval([$5], AC_MSG_WARN([$msg]), AC_MSG_ERROR([$msg]))
            fi
        ],
        [
            if test "x$WANT_SQLITE3" = "xyes" ||
               test "x$args_required_param" = "xCONFIG_ARGS_REQUIRED"
            then
                msg="--with-sqlite3-headers argument missing."
                m4_ifval([$5], AC_MSG_WARN([$msg]), AC_MSG_ERROR([$msg]))
            fi
        ]
    )

    AC_ARG_WITH(
        [sqlite3-libs],
        [AS_HELP_STRING(
            [--with-sqlite3-libs=DIR],
            [path denoting directory of sqlite3 binary lib(s).])
        ],
        [
            WANT_SQLITE3="yes"

            if test -d "$withval"
            then
                SQLITE3_LIBS_PATH="$withval"
                SELECTED_CONFIG_FLAGS="$SELECTED_CONFIG_FLAGS --with-sqlite3-libs=\"$withval\""
            else
                msg="--with-sqlite3-libs expected directory name."
                m4_ifval([$5], AC_MSG_WARN([$msg]), AC_MSG_ERROR([$msg]))
            fi
        ],
        [
            if test "x$WANT_SQLITE3" = "xyes" ||
               test "x$args_required_param" = "xCONFIG_ARGS_REQUIRED"
            then
                msg="--with-sqlite3-libs argument missing."
                m4_ifval([$5], AC_MSG_WARN([$msg]), AC_MSG_ERROR([$msg]))
            fi
        ]
    )

    if test "x$WANT_SQLITE3" = "xyes"; then

        ac_sqlite3_header="sqlite3.h"

        sqlite3_version_req=ifelse(
            [$min_version_param], 
            [], 
            [3.0.0], 
            [$min_version_param])
        sqlite3_version_req_shorten=`expr $sqlite3_version_req : '\([[0-9]]*\.[[0-9]]*\)'`
        sqlite3_version_req_major=`expr $sqlite3_version_req : '\([[0-9]]*\)'`
        sqlite3_version_req_minor=`expr $sqlite3_version_req : '[[0-9]]*\.\([[0-9]]*\)'`
        sqlite3_version_req_micro=`expr $sqlite3_version_req : '[[0-9]]*\.[[0-9]]*\.\([[0-9]]*\)'`
        if test "x$sqlite3_version_req_micro" = "x" ; then
            sqlite3_version_req_micro="0"
        fi

        sqlite3_version_req_number=`expr $sqlite3_version_req_major \* 1000000 \
                                   \+ $sqlite3_version_req_minor \* 1000 \
                                   \+ $sqlite3_version_req_micro`

        AC_MSG_CHECKING([for SQLite3 library >= $sqlite3_version_req])

        ac_sqlite3_cppflags="-I$SQLITE3_INCLUDES_PATH"

        saved_CPPFLAGS="$CPPFLAGS"
        CPPFLAGS="$CPPFLAGS $ac_sqlite3_cppflags"

        AC_LANG_PUSH([C++])
        AC_COMPILE_IFELSE(
            [
                AC_LANG_PROGRAM([[@%:@include <sqlite3.h>]], [[]])
            ],
            [
                have_sqlite_headers="yes"
            ],
            [
                AC_MSG_RESULT([no])
                have_sqlite_headers="no"
                msg="Sqlite headers could not be found."
                m4_ifval([$5], AC_MSG_WARN([$msg]), AC_MSG_ERROR([$msg]))
            ]
        )

        if test "x$have_sqlite_headers" = "xyes"
        then
            AC_COMPILE_IFELSE(
                [
                    AC_LANG_PROGRAM(
                        [[@%:@include <sqlite3.h>]],
                        [[
                            #if (SQLITE_VERSION_NUMBER >= $sqlite3_version_req_number)
                            // Everything is okay
                            #else
                            #  error SQLite version is too old
                            #endif
                        ]]
                    )
                ],
                [
                    AC_MSG_RESULT([yes])
                    HAVE_SQLITE3="yes"
                ],
                [
                    AC_MSG_RESULT([no])
                    msg="The Sqlite headers in $SQLITE_INCLUDES_PATH are too old. Required: version $min_version_param or higher. You can check your version number by looking in <sqlite.h>."
                    
                    m4_ifval([$5], AC_MSG_WARN([$msg]), AC_MSG_ERROR([$msg]))
                ]
            )
        fi
        AC_LANG_POP([C++])

        CPPFLAGS="$saved_CPPFLAGS"
    fi

    if test "x$HAVE_SQLITE3" = "xyes"
    then
        dummy_var="yes"
        m4_ifval([$4], [$4])
    else
        dummy_var="yes"
        m4_ifval([$5], [$5])
    fi
])

# ===========================================================================
#      http://www.gnu.org/software/autoconf-archive/ax_lib_sqlite3.html
# ===========================================================================
#
# SYNOPSIS
#
#   AX_ARG_SQLITE3(
#       SELECTED_CONFIG_FLAGS,
#       CONFIG_ARGS_REQUIRED | CONFIG_ARGS_OPTIONAL,
#       [MINIMUM-VERSION],
#       [ACTION-IF-FOUND],
#       [ACTION-IF-NOT-FOUND])
#
# DESCRIPTION
#
#   Sets the following m4 script variables:
#
#       SELECTED_CONFIG_FLAGS=<see Macro parameters>
#
#   Adds the following configure arguments:
#
#       See AX_ARG_ONLY_SQLITE3
#
#   Has the following side effects:
#
#       AC_SUBST(SQLITE3_INCLUDES_PATH)
#       AC_SUBST(SQLITE3_LIBS_PATH)
#       AC_DEFINE(HAVE_SQLITE3, ...)
#
#   Macro parameters:
#
#       See AX_ARG_ONLY_SQLITE3
#
#   Test for the SQLite 3 library of a particular version (or newer).
#
# LICENSE
#
#   Copyright (c) 2008 Mateusz Loskot <mateusz@loskot.net>
#   Copyright (c) 2010 Mostafa
#
#   Copying and distribution of this file, with or without modification, are
#   permitted in any medium without royalty provided the copyright notice
#   and this notice are preserved. This file is offered as-is, without any
#   warranty.

#sErIaL 9

AC_DEFUN([AX_ARG_SQLITE3],
[
    m4_ifval([$5], [have_if_not="yes"])
    if test "x$have_if_not" = "xyes"
    then
        AX_ARG_ONLY_SQLITE3(
            [$1], [$2], [$3], , [dummy_var_to_suppress_error_msgs="yes"])
    else
        AX_ARG_ONLY_SQLITE3([$1], [$2], [$3])
    fi

    AC_SUBST(SQLITE3_INCLUDES_PATH)
    AC_SUBST(SQLITE3_LIBS_PATH)
    if test "x$HAVE_SQLITE3" = "xyes"
    then
        AC_DEFINE([HAVE_SQLITE3], [], [Have the SQLITE3 library])
    fi

    if test "x$HAVE_SQLITE3" = "xyes"
    then
        dummy_var="yes"
        m4_ifval([$4], [$4])
    else
        dummy_var="yes"
        m4_ifval([$5], [$5])
    fi
])
