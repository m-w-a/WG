include $(top_srcdir)/StandardCppFlags.am

if ENABLED_GTEST
    TESTDIR = ../Tests/build_autotools
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
    ../ClassMethodDisablers.hh \
    ../ScopeFunction.hh \
    ../ScopedStdStreamRedirector.hh

libwgutils_la_SOURCES = \
    ../Impl/ScopedStdStreamRedirector.cc

####################
#Preprocessor Flags.
####################

###############
#Compiler Flags
###############

##############
#Linker Flags.
##############