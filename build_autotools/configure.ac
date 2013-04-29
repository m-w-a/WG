#                         -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.64])
AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])
AC_CONFIG_SRCDIR([WG/Core])
AC_CONFIG_HEADERS([config.h])

#Options to automake
AM_INIT_AUTOMAKE([-Wall -Werror -Woverride foreign subdir-objects])

#Was recommended by autoreconf
AC_CONFIG_MACRO_DIR([m4])

#Libtool support
LT_INIT
AC_SUBST([LIBTOOL_DEPS])

######################
# Checks for programs.
######################

AC_PROG_CXX
AC_PROG_CC
AM_PROG_CC_C_O

#If you make a link in a directory other than the current directory,
#then cd to that directory and create the link there.
#Bad: $(LN_S) ../foo /usr/bin/foo
#Good: (cd ../; $(LN_S) foo /usr/bin/foo;)
AC_PROG_LN_S  #To use $(LN_S)

#######################
# Checks for libraries.
#######################

##########################
# Checks for header files.
##########################

################################################################
# Checks for typedefs, structures, and compiler characteristics.
################################################################

################################
#configure command line options.
################################

m4_include([m4/wg.m4])

###############################
# Checks for library functions.
###############################

#WG/Tests/build_autotools/Makefile
AC_CONFIG_FILES([
    Makefile
    WG/Utils/Tests/ClassMethodDisablers/test_runner.sh
    ])

AC_OUTPUT
