#SYNOPSIS
#
#   AX_ARG_ONLY_BOOST_HEADERS(
#       SELECTED_CONFIG_FLAGS,
#       CONFIG_ARGS_REQUIRED | CONFIG_ARGS_OPTIONAL,
#       VERSION,
#       EXACT | MIN,
#       [ACTION-IF-FOUND],
#       [ACTION-IF-NOT-FOUND])
#
#Description
#
#   Sets the following m4 script variables:
#
#       SELECTED_CONFIG_FLAGS=<see Macro parameters>
#       HAVE_BOOST=yes|no
#       BOOST_INCLUDES_PATH=DIR
#
#   Adds the following configure arguments:
#
#       Args: --with-boost-headers
#
#   Macro parameters:
#
#       SELECTED_CONFIG_FLAGS
#           White space delimited string of user selected config flags are
#           appended to this variable.
#
#       CONFIG_ARGS_REQUIRED | CONFIG_ARGS_OPTIONAL
#           Whether the added configure arguments must be specified
#           by the user (CONFIG_ARGS_REQUIRED), or not (CONFIG_ARGS_OPTIONAL).
#
#       EXACT | MIN :
#           Whether the version number to check for should be the 
#           exact match or a minimum match.
#
#       ACTION-IF-NOT-FOUND :
#           If this parameter is specified then only warning messages
#           will be outputted if Boost with the required version is not
#           found, else error messages will be outputted.
#
#   Tests for Boost C++ header-only libraries of a particular version or newer,
#   and adds arg to the configure script.
#
# LICENSE
#
#   Copyright (c) 2011 Mostafa

AC_DEFUN([AX_ARG_ONLY_BOOST_HEADERS],
[
    SELECTED_CONFIG_FLAGS="$1"
    boost_headers_arg_required="$2"
    version="$3"
    version_condition="$4"
    if_found=no

    if test x"$boost_headers_arg_required" != "xCONFIG_ARGS_REQUIRED" &&
       test x"$boost_headers_arg_required" != "xCONFIG_ARGS_OPTIONAL"
    then
        AC_MSG_ERROR([Invalid attendance argument to AX@&t@_ARG_ONLY_BOOST_HEADERS macro.])
    fi
    
    if test "x$version" = "x"
    then
        AC_MSG_ERROR([Invalid version argument to AX@&t@_ARG_ONLY_BOOST_HEADERS macro.])
    fi

    if test "x$version_condition" != "xEXACT" &&
       test "x$version_condition" != "xMIN"
    then
        AC_MSG_ERROR([Invalid version condition argument to AX@&t@_ARG_ONLY_BOOST_HEADERS macro.])
    fi

    AC_ARG_WITH(
        [boost-headers],
        [AS_HELP_STRING(
            [--with-boost-headers=DIR], 
            [path denoting parent directory of a boost headers-only library directory (i.e., /usr/local/include). Required $4 version: $3. ])
        ],
        [
            want_boost="yes"

            if test -d "$withval"
            then
                BOOST_INCLUDES_PATH="$withval"
                SELECTED_CONFIG_FLAGS="$SELECTED_CONFIG_FLAGS --with-boost-headers=\"$withval\""
            else
                msg="--with-boost-headers expected directory name."
                m4_ifval([$6], AC_MSG_WARN([$msg]), AC_MSG_ERROR([$msg]))
            fi
        ],
        [
            if test x"$boost_headers_arg_required" = "xCONFIG_ARGS_REQUIRED"
            then
                msg="--with-boost-headers argument missing."
                m4_ifval([$6], AC_MSG_WARN([$msg]), AC_MSG_ERROR([$msg]))
            fi
        ]
    )

    if test "x$version_condition" = "xEXACT"
    then
        boost_version_operand="="
    else
        boost_version_operand=">="
    fi

    if test "x$want_boost" = "xyes"
    then
        boost_lib_version_req=$version

        boost_lib_version_req_shorten=`expr $boost_lib_version_req : '\([[0-9]]*\.[[0-9]]*\)'`
        boost_lib_version_req_major=`expr $boost_lib_version_req : '\([[0-9]]*\)'`
        boost_lib_version_req_minor=`expr $boost_lib_version_req : '[[0-9]]*\.\([[0-9]]*\)'`
        boost_lib_version_req_sub_minor=`expr $boost_lib_version_req : '[[0-9]]*\.[[0-9]]*\.\([[0-9]]*\)'`
        if test "x$boost_lib_version_req_sub_minor" = "x" ; then
            boost_lib_version_req_sub_minor="0"
        fi
        WANT_BOOST_VERSION=`expr $boost_lib_version_req_major \* 100000 \+  $boost_lib_version_req_minor \* 100 \+ $boost_lib_version_req_sub_minor`
        
        AC_MSG_CHECKING(for boostlib >= $boost_lib_version_req)

        CPPFLAGS_SAVED="$CPPFLAGS"
        CPPFLAGS="$CPPFLAGS -I$BOOST_INCLUDES_PATH"
        export CPPFLAGS

        AC_REQUIRE([AC_PROG_CXX])
        AC_LANG_PUSH(C++)
        
        AC_COMPILE_IFELSE(
            [AC_LANG_PROGRAM(
                [[@%:@include <boost/version.hpp>]],
                [[]]
            )],
            [
                have_boost_headers=yes
            ],
            [
                have_boost_headers=no
            ]
        )

        if test "x$have_boost_headers" = "xyes"
        then
            AC_COMPILE_IFELSE(
                [AC_LANG_PROGRAM(
                    [[@%:@include <boost/version.hpp>]],
                    [[
                        #if BOOST_VERSION $boost_version_operand $WANT_BOOST_VERSION
                        // Everything is okay
                        #else
                        #  error Boost version is too old
                        #endif
                    ]]
                )],
                [
                    if_found=yes
                ],
                [
                ]
            )
        fi

        AC_LANG_POP([C++])

        CPPFLAGS="$CPPFLAGS_SAVED"

        if test "x$if_found" = "xno"
        then
            if test "x$have_boost_headers" = "xyes" ; then
                msg="The Boost libraries in $BOOST_INCLUDES_PATH are too old. Required: version $boost_lib_version_req_shorten or higher. You can check your version number by looking in <boost/version.hpp>."
                
                AC_MSG_RESULT(no)
                m4_ifval([$6], [AC_MSG_WARN([$msg])], [AC_MSG_ERROR([$msg])])
            else
                msg="Boost header libraries could not be found."

                AC_MSG_RESULT(no)
                m4_ifval([$6], [AC_MSG_WARN([$msg])], [AC_MSG_ERROR([$msg])])
            fi
        else
            AC_MSG_RESULT(yes)
            HAVE_BOOST="yes"
        fi
    fi

    if test "x$if_found" = "xyes"
    then
        dummy_var=yes
        m4_ifval([$5], [$5])
    else
        dummy_var=yes
        m4_ifval([$6], [$6])
    fi
])

#SYNOPSIS
#
#   AX_ARG_BOOST_HEADERS(
#       SELECTED_CONFIG_FLAGS,
#       CONFIG_ARGS_REQUIRED | CONFIG_ARGS_OPTIONAL,
#       VERSION,
#       EXACT | MIN,
#       [ACTION-IF-FOUND],
#       [ACTION-IF-NOT-FOUND])
#
#Description
#
#   Sets the following m4 script variables:
#
#       SELECTED_CONFIG_FLAGS=<see Macro parameters>
#
#   Adds the following configure arguments:
#
#       See AX_ARG_ONLY_BOOST_HEADERS
#
#   Has the following side effects:
#
#       AC_SUBST(BOOST_INCLUDES_PATH)
#       AC_DEFINE(HAVE_BOOST, ...)
#       AM_CONDITIONAL([HAVE_BOOST], ...)
#
#   Macro parameters:
#
#       See AX_ARG_ONLY_BOOST_HEADERS
#
#   Tests for Boost C++ header-only libraries of a particular version or newer,
#   adds arg to the configure script, and sets autoconf/automake vars.
#   Side effects default to negative or empty values if boost with the required
#   version is not found, with the former taking precedence.
#
# LICENSE
#
#   Copyright (c) 2011 Mostafa

AC_DEFUN([AX_ARG_BOOST_HEADERS],
[
    m4_ifval([$6], [if_have_not="yes"])

    if test "x$if_have_not" = "xyes"
    then
        AX_ARG_ONLY_BOOST_HEADERS(
            [$1], [$2], [$3], [$4], , [dummy_var_to_suppress_error_msgs=""])
    else
        AX_ARG_ONLY_BOOST_HEADERS(
            [$1], [$2], [$3], [$4])
    fi

    if test "x$HAVE_BOOST" = "xyes"
    then
        AC_SUBST(BOOST_INCLUDES_PATH)
        AC_DEFINE(HAVE_BOOST,[1],[define if Boost headers are available])
    fi
    AM_CONDITIONAL([HAVE_BOOST],[test x"$HAVE_BOOST" = "xyes"])

    if test "x$HAVE_BOOST" = "xyes"
    then
        dummy_var=yes
        m4_ifval([$5], [$5])
    else
        dummy_var=yes
        m4_ifval([$6], [$6])
    fi
])
