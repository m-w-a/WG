#                         -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.64])
AC_INIT([wg], [1.0], [BUG-REPORT-ADDRESS])
AC_CONFIG_SRCDIR([WG])
AC_CONFIG_HEADERS([config.h])

#Redirect misc. auto-generated build scripts here.
AC_CONFIG_AUX_DIR([build-aux])

#Redirect auto-generated m4 scripts here.
AC_CONFIG_MACRO_DIR([build-m4])

#Options to automake
AM_INIT_AUTOMAKE([-Wall -Werror -Woverride foreign subdir-objects])

#Automake: suggested as of version 1.12
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])

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

# To be used for programs that should not be default built.
AM_CONDITIONAL([DO_NOT_BUILD], [test "xno" = "xyes"])

###############################
# Checks for library functions.
###############################

AC_CONFIG_FILES([
    Makefile 
    WG/ExternalLibsPkg/build_autotools/Makefile
    WG/ExternalLibsNoInstall/build_autotools/Makefile
    WG/Local/build_autotools/Makefile
    WG/Local/Tests/build_autotools/Makefile
])

AC_OUTPUT
