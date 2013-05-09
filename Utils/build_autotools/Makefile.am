include $(top_srcdir)/TopLevelDist.am
include $(top_srcdir)/StandardCppFlags.am

#Told to do so by autgen.sh
ACLOCAL_AMFLAGS = -I m4

#To ensure "make distcheck"s call to configure employs the user's configure 
# flags.
DISTCHECK_CONFIGURE_FLAGS=$(SELECTED_CONFIG_FLAGS)

if ENABLED_GTEST
    TESTDIR = ./src/Tests/build_autotools
endif

SUBDIRS = \
    . \
    $(TESTDIR)

###########################
#Declare programs and libs.
###########################

lib_LTLIBRARIES = \
    libwgutils.la

########
#Sources
########

installheadersdir = $(includedir)/WG/Utils/
installheaders_HEADERS = \
    ./src/ClassMethodDisablers.hh \
    ./src/ScopeFunction.hh \
    ./src/ScopeStdStreamRedirector.hh

libwgutils_la_SOURCES = \
    ./src/Impl/ScopeStdStreamRedirector.cc

####################
#Preprocessor Flags.
####################

###############
#Compiler Flags
###############

##############
#Linker Flags.
##############