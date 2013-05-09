include $(top_srcdir)/StandardCppFlags.am
include $(top_srcdir)/WG/ExternalLibsNoInstall/build_autotools/GTestFlags.am

###########################
#Declare programs and libs.
###########################

noinst_PROGRAMS = \
    test_scopefunction \
    test_scopestdstreamredirector
    
TEST_BIN_DIR = $(abs_top_builddir)/bin/

TEST_WG_CLASSMETHODDISABLERS_APPNAME = test_classmethoddisablers.sh
TEST_WG_CLASSMETHODDISABLERS_APPALTPATH = \
    $(TEST_BIN_DIR)/$(TEST_WG_CLASSMETHODDISABLERS_APPNAME)
TEST_WG_CLASSMETHODDISABLERS_APPBUILDLOC = \
    $(abs_builddir)/src/ClassMethodDisablers/$(TEST_WG_CLASSMETHODDISABLERS_APPNAME)

TEST_WG_SCOPEFUNCTION_APPNAME = test_scopefunction$(EXEEXT)
TEST_WG_SCOPEFUNCTION_APPALTPATH = \
    $(TEST_BIN_DIR)/$(TEST_WG_SCOPEFUNCTION_APPNAME)
TEST_WG_SCOPEFUNCTION_APPBUILDLOC = \
    $(abs_builddir)/$(TEST_WG_SCOPEFUNCTION_APPNAME)

TEST_WG_SCOPESTDSTRMREDIRECTOR_APPNAME = test_scopestdstreamredirector$(EXEEXT)
TEST_WG_SCOPESTDSTRMREDIRECTOR_APPALTPATH = \
    $(TEST_BIN_DIR)/$(TEST_WG_SCOPESTDSTRMREDIRECTOR_APPNAME)
TEST_WG_SCOPESTDSTRMREDIRECTOR_APPBUILDLOC = \
    $(abs_builddir)/$(TEST_WG_SCOPESTDSTRMREDIRECTOR_APPNAME)

#Custom init.
all-local : \
    $(TEST_BIN_DIR) \
    $(TEST_WG_SCOPEFUNCTION_APPALTPATH) \
    $(TEST_WG_CLASSMETHODDISABLERS_APPALTPATH)

$(TEST_BIN_DIR) :
	$(MKDIR_P) $(TEST_BIN_DIR)
    
$(TEST_WG_CLASSMETHODDISABLERS_APPALTPATH) : $(TEST_WG_CLASSMETHODDISABLERS_APPBUILDLOC)
	( cd $(TEST_BIN_DIR); \
      $(LN_S) -f \
      $(TEST_WG_CLASSMETHODDISABLERS_APPBUILDLOC) \
      $(TEST_WG_CLASSMETHODDISABLERS_APPNAME); )
    
$(TEST_WG_SCOPEFUNCTION_APPALTPATH) : $(TEST_WG_SCOPEFUNCTION_APPBUILDLOC)
	( cd $(TEST_BIN_DIR); \
      $(LN_S) -f \
          $(TEST_WG_SCOPEFUNCTION_APPBUILDLOC) \
          $(TEST_WG_SCOPEFUNCTION_APPNAME); )

$(TEST_WG_SCOPESTDSTRMREDIRECTOR_APPALTPATH) : $(TEST_WG_SCOPESTDSTRMREDIRECTOR_APPBUILDLOC)
	( cd $(TEST_BIN_DIR); \
      $(LN_S) -f \
          $(TEST_WG_SCOPESTDSTRMREDIRECTOR_APPBUILDLOC) \
          $(TEST_WG_SCOPESTDSTRMREDIRECTOR_APPNAME); )

#Custom finalize.
clean-local:
	rm -rf $(TEST_BIN_DIR)/$(TEST_WG_CLASSMETHODDISABLERS_APPNAME)
	rm -rf $(TEST_BIN_DIR)/$(TEST_WG_SCOPEFUNCTION_APPNAME)
	rm -rf $(TEST_BIN_DIR)/$(TEST_WG_SCOPESTDSTRMREDIRECTOR_APPNAME)

##############################
#Automatically executed tests.
##############################
TESTS = \
    $(TEST_WG_CLASSMETHODDISABLERS_APPNAME) \
    $(TEST_WG_SCOPEFUNCTION_APPALTPATH) \
    $(TEST_WG_SCOPESTDSTRMREDIRECTOR_APPNAME)
    
########
#Sources
########

test_scopefunction_SOURCES = \
    ./src/ScopeFunction/tmp.cc

test_scopestdstreamredirector_SOURCES = \
    $(top_srcdir)/WG/ExternalLibsNoInstall/build_autotools/src/gtest/src/gtest-all.cc \
    ./src/ScopeStdStreamRedirector/ScopeStdStreamRedirectorUnitTest.cc

####################
#Preprocessor Flags.
####################

AM_CPPFLAGS += $(GTEST_CPPFLAGS)

##############
#Linker Flags.
##############

AM_LDFLAGS += \
    -ldl