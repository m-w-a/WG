include $(top_srcdir)/StandardCppFlags.am
include $(top_srcdir)/WG/ExternalLibsNoInstall/build_autotools/GTestFlags.am

###########################
#Declare programs and libs.
###########################

noinst_PROGRAMS = \
    test_gtestutils

TEST_BIN_DIR = $(abs_top_builddir)/bin/

TEST_WG_GTEST_APPNAME = test_gtestutils$(EXEEXT)
TEST_WG_GTEST_APPALTPATH = \
    $(TEST_BIN_DIR)/$(TEST_WG_GTEST_APPNAME)
TEST_WG_GTEST_APPBUILDLOC = \
    $(abs_builddir)/$(TEST_WG_GTEST_APPNAME)

#Custom init.
all-local : \
    $(TEST_BIN_DIR) \
    $(TEST_WG_GTEST_APPALTPATH)

$(TEST_BIN_DIR) :
	$(MKDIR_P) $(TEST_BIN_DIR)

$(TEST_WG_GTEST_APPALTPATH) : $(TEST_WG_GTEST_APPBUILDLOC)
	( cd $(TEST_BIN_DIR); \
      $(LN_S) -f \
          $(TEST_WG_GTEST_APPBUILDLOC) \
          $(TEST_WG_GTEST_APPNAME); )

#Custom finalize.
clean-local:
	rm -rf $(TEST_BIN_DIR)/$(TEST_WG_GTEST_APPNAME)

##############################
#Automatically executed tests.
##############################
TESTS = \
    $(TEST_WG_GTEST_APPNAME)

test_gtestutils_SOURCES = \
	../TestMain.cc \
	../RedirectEventListener.cc \
    ../ExceptionsUnitTest.cc

####################
#Preprocessor Flags.
####################

AM_CPPFLAGS += \
    $(GTEST_CPPFLAGS)

##############
#Linker Flags.
##############

LDADD = \
    $(top_builddir)/WG/ExternalLibsNoInstall/build_autotools/libgtest.la \
    $(top_builddir)/WG/Utils/build_autotools/libwgutils.la