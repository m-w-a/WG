AC_PRESERVE_HELP_ORDER

m4_divert_push([HELP_ENABLE])
*****************************************
            WG Arguments
*****************************************
REQUIRED args: --with-boost-headers.
OPTIONAL args: --with-dist,
               --enable-gtest

Boost min version: 1.33

gtest library is needed in order to run the unit tests.
*****************************************

m4_divert_pop([HELP_ENABLE])

m4_include([m4/arg_dist.m4])

if test x"$DIST_MODE" = "xno"
then

m4_include([m4/ax_arg_boost_headers.m4])
m4_include([m4/ax_arg_gtest_builtin.m4])

SELECTED_CONFIG_FLAGS=""

AX_ARG_BOOST_HEADERS(
    [$SELECTED_CONFIG_FLAGS],
    [CONFIG_ARGS_REQUIRED],
    [1.33],
    [MIN])

GTEST_BUILTINLIB_CHECK(
    [$SELECTED_CONFIG_FLAGS],
    [], 
    [AC_MSG_WARN([gtest library not found. You will be unable to build unit tests for this library.])])

AC_SUBST([SELECTED_CONFIG_FLAGS])

fi #DIST_MODE

#Fake vars for DIST_MODE to get configure to suppress configure errors.
if test "x$DIST_MODE" = "xyes"
then
    AM_CONDITIONAL([ENABLED_GTEST], [test "xno" = "xyes"])
    AM_CONDITIONAL([HAVE_BOOST], [test "xno" = "xyes"])
fi

# List of all possible variables set by this script.
#       AC_SUBST([BOOST_INCLUDES_PATH])
#       AM_CONDITIONAL([HAVE_BOOST], [])
#       AC_SUBST([ENABLED_GTEST])
#       AM_CONDITIONAL([ENABLED_GTEST], ...)
