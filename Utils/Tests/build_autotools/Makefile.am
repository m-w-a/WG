include $(top_srcdir)/StandardCppFlags.am

###########################
#Declare programs and libs.
###########################

noinst_PROGRAMS = \
    test_scopefunction
    
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
          
#Custom finalize.
clean-local:
	rm -rf $(TEST_BIN_DIR)/$(TEST_WG_CLASSMETHODDISABLERS_APPNAME)
	rm -rf $(TEST_BIN_DIR)/$(TEST_WG_SCOPEFUNCTION_APPNAME)

##############################
#Automatically executed tests.
##############################
TESTS = \
    $(TEST_WG_CLASSMETHODDISABLERS_APPNAME) \
    $(TEST_WG_SCOPEFUNCTION_APPALTPATH)
    
########
#Sources
########

test_scopefunction_SOURCES = \
    ./src/ScopeFunction/tmp.cc