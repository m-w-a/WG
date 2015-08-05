#SYNOPSIS
#
#   m4_include(this-file)
#
#Description
#
#   Sets the following m4 script variables:
#
#       DIST_MODE=yes|no
#
#   Adds the following configure arguments:
#
#       OPTIONAL Args: --with-only-dist
#
# LICENSE
#
#   Copyright (c) 2011 Mostafa

AC_ARG_WITH(
    [only-dist],
    [AS_HELP_STRING(
        [--with-only-dist=@<:@yes@:>@],
        [if set, or set to yes, this option only creates a distributable])
    ],
    [
        if test "x$withval" != "xyes" &&
           test "x$withval" != "xno"
        then
            AC_MSG_ERROR(["--with-only-dist expected 'yes' or 'no'"])
        fi
    
        DIST_MODE="$withval"
        AC_MSG_WARN([This configuration is only good for creating distributables.])
    ],
    [
        DIST_MODE="no"
    ]
)