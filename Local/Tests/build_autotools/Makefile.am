include $(top_srcdir)/StandardCppFlags.am
include $(top_srcdir)/WG/ExternalLibsNoInstall/build_autotools/GTestFlags.am

###########################
#Declare programs and libs.
###########################

noinst_PROGRAMS = \
    test_pp_pp \
    test_pp_wgseq \
    test_pp_tokenmatch \
    test_pp_vardcln \
    test_pp_vardcln_implicit \
    test_pp_vardcln_explicit \
    test_pp_parsedtype \
    test_autofunctor

TEST_BIN_DIR = $(abs_top_builddir)/bin/

TEST_WG_AUTOFUNCTOR_APPNAME = test_autofunctor$(EXEEXT)
TEST_WG_AUTOFUNCTOR_APPALTPATH = \
    $(TEST_BIN_DIR)/$(TEST_WG_AUTOFUNCTOR_APPNAME)
TEST_WG_AUTOFUNCTOR_APPBUILDLOC = \
    $(abs_builddir)/$(TEST_WG_AUTOFUNCTOR_APPNAME)

#Custom init.
all-local : \
    $(TEST_BIN_DIR) \
    $(TEST_WG_AUTOFUNCTOR_APPALTPATH)
    
$(TEST_BIN_DIR) :
	$(MKDIR_P) $(TEST_BIN_DIR)

$(TEST_WG_AUTOFUNCTOR_APPALTPATH) : $(TEST_WG_AUTOFUNCTOR_APPBUILDLOC)
	( cd $(TEST_BIN_DIR); \
      $(LN_S) -f \
          $(TEST_WG_AUTOFUNCTOR_APPBUILDLOC) \
          $(TEST_WG_AUTOFUNCTOR_APPNAME); )

#Custom finalize.
clean-local : \
    rm -rf $(TEST_BIN_DIR)/$(TEST_WG_AUTOFUNCTOR_APPNAME)

##############################
#Automatically executed tests.
##############################
# Don't add test_pp_* to TESTS since they're compile-only tests.
TESTS = \
    $(TEST_WG_AUTOFUNCTOR_APPNAME)

test_pp_pp_SOURCES = ../../Detail/Tests/PPUnitTest.cc
test_pp_wgseq_SOURCES = ../../Detail/Tests/SeqUnitTest.cc
test_pp_tokenmatch_SOURCES = ../../Detail/Tests/TokenMatchUnitTest.cc
test_pp_vardcln_SOURCES = ../../Detail/FrontEnd/Tests/VarDclnUnitTest.cc
test_pp_vardcln_implicit_SOURCES = ../../Detail/FrontEnd/Tests/VarDclnImplicitUnitTest.cc
test_pp_vardcln_explicit_SOURCES = ../../Detail/FrontEnd/Tests/VarDclnExplicitUnitTest.cc
test_pp_parsedtype_SOURCES = ../../Detail/BackEnd/Tests/TypeExtractorUnitTest.cc

test_autofunctor_SOURCES = \
    ../AutoFunctor/TestMain.cc \
    ../AutoFunctor/AssignTo.cc \
    ../AutoFunctor/ParamBindExplicit.cc \
    ../AutoFunctor/ParamBindImplicit.cc \
    ../AutoFunctor/ParamBindExplicitAndImplicit.cc \
    ../AutoFunctor/ParamSetExplicit.cc \
    ../AutoFunctor/ParamSetImplicit.cc \
    ../AutoFunctor/ParamBindExplicitAndParamSetExplicit.cc \
    ../AutoFunctor/ParamBindImplicitAndParamSetExplicit.cc \
    ../AutoFunctor/ParamBindImplicitAndParamSetImplicit.cc \
    ../AutoFunctor/MemBindExplicit.cc \
    ../AutoFunctor/MemBindImplicit.cc \
    ../AutoFunctor/MemBindExplicitAndImplicit.cc \
    ../AutoFunctor/MemSetExplicit.cc \
    ../AutoFunctor/MemSetImplicit.cc \
    ../AutoFunctor/NoSpec.cc \
    ../AutoFunctor/Nested.cc \
    ../AutoFunctor/Recursive.cc

EXTRA_DIST = 

####################
#Preprocessor Flags.
####################

test_autofunctor_CPPFLAGS = \
    $(AM_CPPFLAGS) \
    $(GTEST_CPPFLAGS)

################
#Compiler Flags.
################

AM_CXXFLAGS += \
    -pedantic

test_autofunctor_CXXFLAGS = \
    -pedantic

##############
#Linker Flags.
##############

GTEST_LTLIB = \
    $(top_builddir)/WG/ExternalLibsNoInstall/build_autotools/libgtest.la

test_autofunctor_LDADD = $(GTEST_LTLIB)
    