include $(top_srcdir)/StandardCppFlags.am
include $(top_srcdir)/WG/ExternalLibsNoInstall/build_autotools/GTestFlags.am

###########################
#Declare programs and libs.
###########################

noinst_PROGRAMS = \
    test_autofunction
    
TEST_BIN_DIR = $(abs_top_builddir)/bin/

TEST_WG_AUTOFUNCTION_APPNAME = test_autofunction$(EXEEXT)
TEST_WG_AUTOFUNCTION_APPALTPATH = \
    $(TEST_BIN_DIR)/$(TEST_WG_AUTOFUNCTION_APPNAME)
TEST_WG_AUTOFUNCTION_APPBUILDLOC = \
    $(abs_builddir)/$(TEST_WG_AUTOFUNCTION_APPNAME)

#Custom init.
all-local : \
    $(TEST_BIN_DIR) \
    $(TEST_WG_AUTOFUNCTION_APPALTPATH)
    
$(TEST_BIN_DIR) :
	$(MKDIR_P) $(TEST_BIN_DIR)

$(TEST_WG_AUTOFUNCTION_APPALTPATH) : $(TEST_WG_AUTOFUNCTION_APPBUILDLOC)
	( cd $(TEST_BIN_DIR); \
      $(LN_S) -f \
          $(TEST_WG_AUTOFUNCTION_APPBUILDLOC) \
          $(TEST_WG_AUTOFUNCTION_APPNAME); )

#Custom finalize.
clean-local : \
    rm -rf $(TEST_BIN_DIR)/$(TEST_WG_AUTOFUNCTION_APPNAME)

##############################
#Automatically executed tests.
##############################
TESTS = \
    $(TEST_WG_AUTOFUNCTION_APPNAME)
    
test_autofunction_SOURCES = \
    ../AutoFunction/TestMain.cc \
    ../AutoFunction/AutoFunctionUnitTest.cc

EXTRA_DIST = \
    ../AutoFunction/AutoFunctionPPTest.cc

####################
#Preprocessor Flags.
####################

AM_CPPFLAGS += \
    $(GTEST_CPPFLAGS)

################
#Compiler Flags.
################

test_autofunction_CXXFLAGS = \
	-pedantic

##############
#Linker Flags.
##############

LDADD = \
    $(top_builddir)/WG/ExternalLibsNoInstall/build_autotools/libgtest.la