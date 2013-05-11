include $(top_srcdir)/StandardCppFlags.am
include $(top_srcdir)/WG/ExternalLibsNoInstall/build_autotools/GTestFlags.am

###########################
#Declare programs and libs.
###########################

noinst_PROGRAMS = \
    test_autofunction \
    test_scopedstdstreamredirector
    
TEST_BIN_DIR = $(abs_top_builddir)/bin/

TEST_WG_CLASSMETHODDISABLERS_APPNAME = test_classmethoddisablers.sh
TEST_WG_CLASSMETHODDISABLERS_APPALTPATH = \
    $(TEST_BIN_DIR)/$(TEST_WG_CLASSMETHODDISABLERS_APPNAME)
TEST_WG_CLASSMETHODDISABLERS_APPBUILDLOC = \
    $(abs_builddir)/../ClassMethodDisablers/$(TEST_WG_CLASSMETHODDISABLERS_APPNAME)

TEST_WG_AUTOFUNCTION_APPNAME = test_autofunction$(EXEEXT)
TEST_WG_AUTOFUNCTION_APPALTPATH = \
    $(TEST_BIN_DIR)/$(TEST_WG_AUTOFUNCTION_APPNAME)
TEST_WG_AUTOFUNCTION_APPBUILDLOC = \
    $(abs_builddir)/$(TEST_WG_AUTOFUNCTION_APPNAME)

TEST_WG_SCOPESTDSTRMREDIRECTOR_APPNAME = test_scopedstdstreamredirector$(EXEEXT)
TEST_WG_SCOPESTDSTRMREDIRECTOR_APPALTPATH = \
    $(TEST_BIN_DIR)/$(TEST_WG_SCOPESTDSTRMREDIRECTOR_APPNAME)
TEST_WG_SCOPESTDSTRMREDIRECTOR_APPBUILDLOC = \
    $(abs_builddir)/$(TEST_WG_SCOPESTDSTRMREDIRECTOR_APPNAME)

#Custom init.
all-local : \
    $(TEST_BIN_DIR) \
    $(TEST_WG_CLASSMETHODDISABLERS_APPALTPATH) \
    $(TEST_WG_SCOPESTDSTRMREDIRECTOR_APPALTPATH) \
    $(TEST_WG_AUTOFUNCTION_APPALTPATH)

$(TEST_BIN_DIR) :
	$(MKDIR_P) $(TEST_BIN_DIR)
    
$(TEST_WG_CLASSMETHODDISABLERS_APPALTPATH) : $(TEST_WG_CLASSMETHODDISABLERS_APPBUILDLOC)
	( cd $(TEST_BIN_DIR); \
      $(LN_S) -f \
      $(TEST_WG_CLASSMETHODDISABLERS_APPBUILDLOC) \
      $(TEST_WG_CLASSMETHODDISABLERS_APPNAME); )
    
$(TEST_WG_AUTOFUNCTION_APPALTPATH) : $(TEST_WG_AUTOFUNCTION_APPBUILDLOC)
	( cd $(TEST_BIN_DIR); \
      $(LN_S) -f \
          $(TEST_WG_AUTOFUNCTION_APPBUILDLOC) \
          $(TEST_WG_AUTOFUNCTION_APPNAME); )

$(TEST_WG_SCOPESTDSTRMREDIRECTOR_APPALTPATH) : $(TEST_WG_SCOPESTDSTRMREDIRECTOR_APPBUILDLOC)
	( cd $(TEST_BIN_DIR); \
      $(LN_S) -f \
          $(TEST_WG_SCOPESTDSTRMREDIRECTOR_APPBUILDLOC) \
          $(TEST_WG_SCOPESTDSTRMREDIRECTOR_APPNAME); )

#Custom finalize.
clean-local:
	rm -rf $(TEST_BIN_DIR)/$(TEST_WG_CLASSMETHODDISABLERS_APPNAME)
	rm -rf $(TEST_BIN_DIR)/$(TEST_WG_AUTOFUNCTION_APPNAME)
	rm -rf $(TEST_BIN_DIR)/$(TEST_WG_SCOPESTDSTRMREDIRECTOR_APPNAME)

##############################
#Automatically executed tests.
##############################
TESTS = \
    $(TEST_WG_CLASSMETHODDISABLERS_APPNAME) \
    $(TEST_WG_AUTOFUNCTION_APPALTPATH) \
    $(TEST_WG_SCOPESTDSTRMREDIRECTOR_APPNAME)

########
#Sources
########

test_autofunction_SOURCES = \
    ../AutoFunction/tmp.cc

test_scopedstdstreamredirector_SOURCES = \
    ../ScopedStdStreamRedirector/TestMain.cc \
    ../ScopedStdStreamRedirector/ScopedStdStreamRedirectUnitTest.cc

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
    