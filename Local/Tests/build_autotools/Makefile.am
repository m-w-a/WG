include $(top_srcdir)/StandardCppFlags.am
include $(top_srcdir)/WG/ExternalLibsNoInstall/build_autotools/GTestFlags.am

###########################
#Declare programs and libs.
###########################

noinst_PROGRAMS = \
    test_autofunction.v1 \
    test_autofunction
    
TEST_BIN_DIR = $(abs_top_builddir)/bin/

TEST_WG_AUTOFUNCTIONV1_APPNAME = test_autofunction.v1$(EXEEXT)
TEST_WG_AUTOFUNCTIONV1_APPALTPATH = \
    $(TEST_BIN_DIR)/$(TEST_WG_AUTOFUNCTIONV1_APPNAME)
TEST_WG_AUTOFUNCTIONV1_APPBUILDLOC = \
    $(abs_builddir)/$(TEST_WG_AUTOFUNCTIONV1_APPNAME)

TEST_WG_AUTOFUNCTION_APPNAME = test_autofunction.v1$(EXEEXT)
TEST_WG_AUTOFUNCTION_APPALTPATH = \
    $(TEST_BIN_DIR)/$(TEST_WG_AUTOFUNCTION_APPNAME)
TEST_WG_AUTOFUNCTION_APPBUILDLOC = \
    $(abs_builddir)/$(TEST_WG_AUTOFUNCTION_APPNAME)

#Custom init.
all-local : \
    $(TEST_BIN_DIR) \
    $(TEST_WG_AUTOFUNCTIONV1_APPALTPATH) \
    $(TEST_WG_AUTOFUNCTION_APPALTPATH)
    
$(TEST_BIN_DIR) :
	$(MKDIR_P) $(TEST_BIN_DIR)

$(TEST_WG_AUTOFUNCTIONV1_APPALTPATH) : $(TEST_WG_AUTOFUNCTIONV1_APPBUILDLOC)
	( cd $(TEST_BIN_DIR); \
      $(LN_S) -f \
          $(TEST_WG_AUTOFUNCTIONV1_APPBUILDLOC) \
          $(TEST_WG_AUTOFUNCTIONV1_APPNAME); ) \
	( cd $(TEST_BIN_DIR); \
      $(LN_S) -f \
          $(TEST_WG_AUTOFUNCTION_APPBUILDLOC) \
          $(TEST_WG_AUTOFUNCTION_APPNAME); )

#Custom finalize.
clean-local : \
    rm -rf $(TEST_BIN_DIR)/$(TEST_WG_AUTOFUNCTIONV1_APPNAME) \
    rm -rf $(TEST_BIN_DIR)/$(TEST_WG_AUTOFUNCTION_APPNAME)

##############################
#Automatically executed tests.
##############################
TESTS = \
    $(TEST_WG_AUTOFUNCTIONV1_APPNAME) \
    $(TEST_WG_AUTOFUNCTION_APPNAME)
    
test_autofunction_v1_SOURCES = \
    ../AutoFunctionV1/TestMain.cc \
    ../AutoFunctionV1/UnitTest.cc

test_autofunction_SOURCES = \
    ../AutoFunction/TestMain.cc \
    ../AutoFunction/UnitTest.cc

EXTRA_DIST = 

####################
#Preprocessor Flags.
####################

AM_CPPFLAGS += \
    $(GTEST_CPPFLAGS)

################
#Compiler Flags.
################

test_autofunction_v1_CXXFLAGS = \
	-pedantic

test_autofunction_CXXFLAGS = \
	-pedantic

##############
#Linker Flags.
##############

LDADD = \
    $(top_builddir)/WG/ExternalLibsNoInstall/build_autotools/libgtest.la