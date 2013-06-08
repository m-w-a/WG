include $(top_srcdir)/StandardCppFlags.am
include $(top_srcdir)/WG/ExternalLibsNoInstall/build_autotools/GTestFlags.am

###########################
#Declare programs and libs.
###########################

noinst_PROGRAMS = \
    test_autofunctor.v1 \
    test_autofunctor
    
TEST_BIN_DIR = $(abs_top_builddir)/bin/

TEST_WG_AUTOFUNCTORV1_APPNAME = test_autofunctor.v1$(EXEEXT)
TEST_WG_AUTOFUNCTORV1_APPALTPATH = \
    $(TEST_BIN_DIR)/$(TEST_WG_AUTOFUNCTORV1_APPNAME)
TEST_WG_AUTOFUNCTORV1_APPBUILDLOC = \
    $(abs_builddir)/$(TEST_WG_AUTOFUNCTORV1_APPNAME)

TEST_WG_AUTOFUNCTOR_APPNAME = test_autofunctor$(EXEEXT)
TEST_WG_AUTOFUNCTOR_APPALTPATH = \
    $(TEST_BIN_DIR)/$(TEST_WG_AUTOFUNCTOR_APPNAME)
TEST_WG_AUTOFUNCTOR_APPBUILDLOC = \
    $(abs_builddir)/$(TEST_WG_AUTOFUNCTOR_APPNAME)

#Custom init.
all-local : \
    $(TEST_BIN_DIR) \
    $(TEST_WG_AUTOFUNCTORV1_APPALTPATH) \
    $(TEST_WG_AUTOFUNCTOR_APPALTPATH)
    
$(TEST_BIN_DIR) :
	$(MKDIR_P) $(TEST_BIN_DIR)

$(TEST_WG_AUTOFUNCTORV1_APPALTPATH) : $(TEST_WG_AUTOFUNCTORV1_APPBUILDLOC)
	( cd $(TEST_BIN_DIR); \
      $(LN_S) -f \
          $(TEST_WG_AUTOFUNCTORV1_APPBUILDLOC) \
          $(TEST_WG_AUTOFUNCTORV1_APPNAME); )

$(TEST_WG_AUTOFUNCTOR_APPALTPATH) : $(TEST_WG_AUTOFUNCTOR_APPBUILDLOC)
	( cd $(TEST_BIN_DIR); \
      $(LN_S) -f \
          $(TEST_WG_AUTOFUNCTOR_APPBUILDLOC) \
          $(TEST_WG_AUTOFUNCTOR_APPNAME); )

#Custom finalize.
clean-local : \
    rm -rf $(TEST_BIN_DIR)/$(TEST_WG_AUTOFUNCTORV1_APPNAME) \
    rm -rf $(TEST_BIN_DIR)/$(TEST_WG_AUTOFUNCTOR_APPNAME)

##############################
#Automatically executed tests.
##############################
TESTS = \
    $(TEST_WG_AUTOFUNCTORV1_APPNAME) \
    $(TEST_WG_AUTOFUNCTOR_APPNAME)
    
test_autofunctor_v1_SOURCES = \
    ../AutoFunctorV1/TestMain.cc \
    ../AutoFunctorV1/UnitTest.cc

test_autofunctor_SOURCES = \
    ../AutoFunctor/TestMain.cc \
    ../AutoFunctor/AssignTo.cc \
    ../AutoFunctor/ParamBindExplicit.cc \
    ../AutoFunctor/ParamBindImplicit.cc \
    ../AutoFunctor/ParamBindExplicitAndImplicit.cc \
    ../AutoFunctor/ParamSetExplicit.cc \
    ../AutoFunctor/ParamBindExplicitAndParamSetExplicit.cc \
    ../AutoFunctor/ParamBindImplicitAndParamSetExplicit.cc \
    ../AutoFunctor/NoSpec.cc \
    ../AutoFunctor/Nested.cc \
    ../AutoFunctor/Recursive.cc

EXTRA_DIST = 

####################
#Preprocessor Flags.
####################

AM_CPPFLAGS += \
    $(GTEST_CPPFLAGS)

################
#Compiler Flags.
################

test_autofunctor_v1_CXXFLAGS = \
	-pedantic

test_autofunctor_CXXFLAGS = \
	-pedantic

##############
#Linker Flags.
##############

LDADD = \
    $(top_builddir)/WG/ExternalLibsNoInstall/build_autotools/libgtest.la