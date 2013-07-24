##################
# GTest Directives
##################

include GTestFlags.am

#*************************#
#Declare programs and libs.
#*************************#

noinst_LTLIBRARIES =

# Enclose only this snippet so that the relevant directories for gtest 
#  dependencies get built in the build directory.
if ENABLED_GTEST
noinst_LTLIBRARIES += libgtest.la
endif
    
#******#
#Sources
#******#

nodist_libgtest_la_SOURCES =\
    ../gtest/src/gtest-all.cc

#******************#
#Preprocessor Flags.
#******************#

libgtest_la_CPPFLAGS =\
    $(GTEST_CPPFLAGS)

#************#
#Linker Flags.
#************#
