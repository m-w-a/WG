include $(top_srcdir)/StandardCppFlags.am
include $(top_srcdir)/WG/ExternalLibsNoInstall/build_autotools/GTestFlags.am

###########################
#Declare programs and libs.
###########################

noinst_PROGRAMS = \
    test_pp_pp \
    test_pp_wgseq \
    test_pp_tokenmatch \
    test_pp_trnsltr_markers \
    test_pp_trnsltr_vardcln \
    test_pp_trnsltr_vardcln_implicit \
    test_pp_trnsltr_vardcln_explicit \
    test_pp_trnsltr_parsedtype \
    test_autofunctor \
    test_autofunctor_errorreporting_invalidnamedparameters \
    test_autofunctor_errorreporting_refthisu \
    test_lclfunction_cpp03 \
    test_lclfunction_cpp11 \
    test_lclfunction_codegenspec_cpp03 \
    test_lclfunction_codegenspec_cpp11

# Don't auto build test_autofunctor_cf_* since they're compile-failure tests.
if DO_NOT_BUILD
    noinst_PROGRAMS += \
        test_autofunctor_cf_localoperandssyntax_ref \
        test_autofunctor_cf_localoperandssyntax_const \
        test_autofunctor_cf_localoperandssyntax_const_ref
endif

TEST_BIN_DIR = $(abs_top_builddir)/bin/

TEST_WG_AUTOFUNCTOR_APPNAME = test_autofunctor$(EXEEXT)
TEST_WG_AUTOFUNCTOR_APPALTPATH = \
    $(TEST_BIN_DIR)/$(TEST_WG_AUTOFUNCTOR_APPNAME)
TEST_WG_AUTOFUNCTOR_APPBUILDLOC = \
    $(abs_builddir)/$(TEST_WG_AUTOFUNCTOR_APPNAME)

TEST_WG_LCLFUNCTION_CODEGENSPEC_CPP03_APPNAME = \
    test_lclfunction_codegenspec_cpp03$(EXEEXT)
TEST_WG_LCLFUNCTION_CODEGENSPEC_CPP03_APPALTPATH = \
    $(TEST_BIN_DIR)/$(TEST_WG_LCLFUNCTION_CODEGENSPEC_CPP03_APPNAME)
TEST_WG_LCLFUNCTION_CODEGENSPEC_CPP03_APPBUILDLOC = \
    $(abs_builddir)/$(TEST_WG_LCLFUNCTION_CODEGENSPEC_CPP03_APPNAME)

TEST_WG_LCLFUNCTION_CODEGENSPEC_CPP11_APPNAME = \
    test_lclfunction_codegenspec_cpp11$(EXEEXT)
TEST_WG_LCLFUNCTION_CODEGENSPEC_CPP11_APPALTPATH = \
    $(TEST_BIN_DIR)/$(TEST_WG_LCLFUNCTION_CODEGENSPEC_CPP11_APPNAME)
TEST_WG_LCLFUNCTION_CODEGENSPEC_CPP11_APPBUILDLOC = \
    $(abs_builddir)/$(TEST_WG_LCLFUNCTION_CODEGENSPEC_CPP11_APPNAME)

TEST_WG_LCLFUNCTION_CPP03_APPNAME = \
    test_lclfunction_cpp03$(EXEEXT)
TEST_WG_LCLFUNCTION_CPP03_APPALTPATH = \
    $(TEST_BIN_DIR)/$(TEST_WG_LCLFUNCTION_CPP03_APPNAME)
TEST_WG_LCLFUNCTION_CPP03_APPBUILDLOC = \
    $(abs_builddir)/$(TEST_WG_LCLFUNCTION_CPP03_APPNAME)

TEST_WG_LCLFUNCTION_CPP11_APPNAME = \
    test_lclfunction_cpp11$(EXEEXT)
TEST_WG_LCLFUNCTION_CPP11_APPALTPATH = \
    $(TEST_BIN_DIR)/$(TEST_WG_LCLFUNCTION_CPP11_APPNAME)
TEST_WG_LCLFUNCTION_CPP11_APPBUILDLOC = \
    $(abs_builddir)/$(TEST_WG_LCLFUNCTION_CPP11_APPNAME)

#Custom init.
all-local : \
    $(TEST_BIN_DIR) \
    $(TEST_WG_AUTOFUNCTOR_APPALTPATH) \
    $(TEST_WG_LCLFUNCTION_CODEGENSPEC_CPP03_APPALTPATH) \
    $(TEST_WG_LCLFUNCTION_CODEGENSPEC_CPP11_APPALTPATH) \
    $(TEST_WG_LCLFUNCTION_CPP03_APPNAME) \
    $(TEST_WG_LCLFUNCTION_CPP11_APPNAME)
    
$(TEST_BIN_DIR) :
	$(MKDIR_P) $(TEST_BIN_DIR)

$(TEST_WG_AUTOFUNCTOR_APPALTPATH) : $(TEST_WG_AUTOFUNCTOR_APPBUILDLOC)
	( cd $(TEST_BIN_DIR); \
      $(LN_S) -f \
          $(TEST_WG_AUTOFUNCTOR_APPBUILDLOC) \
          $(TEST_WG_AUTOFUNCTOR_APPNAME); )

$(TEST_WG_LCLFUNCTION_CODEGENSPEC_CPP03_APPALTPATH) : $(TEST_WG_LCLFUNCTION_CODEGENSPEC_CPP03_APPBUILDLOC)
	( cd $(TEST_BIN_DIR); \
      $(LN_S) -f \
          $(TEST_WG_LCLFUNCTION_CODEGENSPEC_CPP03_APPBUILDLOC) \
          $(TEST_WG_LCLFUNCTION_CODEGENSPEC_CPP03_APPNAME); )

$(TEST_WG_LCLFUNCTION_CODEGENSPEC_CPP11_APPALTPATH) : $(TEST_WG_LCLFUNCTION_CODEGENSPEC_CPP11_APPBUILDLOC)
	( cd $(TEST_BIN_DIR); \
      $(LN_S) -f \
          $(TEST_WG_LCLFUNCTION_CODEGENSPEC_CPP11_APPBUILDLOC) \
          $(TEST_WG_LCLFUNCTION_CODEGENSPEC_CPP11_APPNAME); )

$(TEST_WG_LCLFUNCTION_CPP03_APPALTPATH) : $(TEST_WG_LCLFUNCTION_CPP03_APPBUILDLOC)
	( cd $(TEST_BIN_DIR); \
	  $(LN_S) -f \
	      $(TEST_WG_LCLFUNCTION_CPP03_APPBUILDLOC) \
	      $(TEST_WG_LCLFUNCTION_CPP03_APPNAME); )

$(TEST_WG_LCLFUNCTION_CPP11_APPALTPATH) : $(TEST_WG_LCLFUNCTION_CPP11_APPBUILDLOC)
	( cd $(TEST_BIN_DIR); \
	  $(LN_S) -f \
	      $(TEST_WG_LCLFUNCTION_CPP11_APPBUILDLOC) \
	      $(TEST_WG_LCLFUNCTION_CPP11_APPNAME); )

#Custom finalize.
clean-local : \
    rm -rf $(TEST_BIN_DIR)/$(TEST_WG_AUTOFUNCTOR_APPNAME) \
    rm -rf $(TEST_WG_LCLFUNCTION_CODEGENSPEC_CPP03_APPNAME) \
    rm -rf $(TEST_WG_LCLFUNCTION_CODEGENSPEC_CPP11_APPNAME) \
    rm -rf $(TEST_WG_LCLFUNCTION_CPP03_APPNAME) \
    rm -rf $(TEST_WG_LCLFUNCTION_CPP11_APPNAME)

##############################
#Automatically executed tests.
##############################
# Don't add test_pp_* to TESTS since they're preprocessor compile-only tests.
# Don't add test_autofunctor_cf_* to TESTS since they're compile-failure tests.
TESTS = \
    $(TEST_WG_AUTOFUNCTOR_APPNAME) \
    $(TEST_WG_LCLFUNCTION_CPP03_APPNAME) \
    $(TEST_WG_LCLFUNCTION_CPP11_APPNAME)

test_pp_pp_SOURCES = ../../Detail/PP/Tests/PPUnitTest.cc
test_pp_wgseq_SOURCES = ../../Detail/PP/Tests/SeqUnitTest.cc
test_pp_tokenmatch_SOURCES = ../../Detail/PP/Tests/TokenMatchUnitTest.cc
test_pp_trnsltr_markers_SOURCES = ../../Detail/PP/Translator/Tests/MarkersUnitTest.cc
test_pp_trnsltr_vardcln_SOURCES = ../../Detail/PP/Translator/FrontEnd/VarDclns/Tests/VarDclnUnitTest.cc
test_pp_trnsltr_vardcln_implicit_SOURCES = ../../Detail/PP/Translator/FrontEnd/VarDclns/Tests/VarDclnImplicitUnitTest.cc
test_pp_trnsltr_vardcln_explicit_SOURCES = ../../Detail/PP/Translator/FrontEnd/VarDclns/Tests/VarDclnExplicitUnitTest.cc
test_pp_trnsltr_parsedtype_SOURCES = ../../Detail/PP/Translator/BackEnd/Tests/TypeExtractorUnitTest.cc
test_autofunctor_errorreporting_invalidnamedparameters_SOURCES = \
    ../../Tests/AutoFunctor/ErrorReporting/InvalidNamedParameters.cc
test_autofunctor_errorreporting_refthisu_SOURCES = \
    ../../Tests/AutoFunctor/ErrorReporting/RefThisU.cc

test_autofunctor_cf_localoperandssyntax_ref_SOURCES = \
    ../../Tests/AutoFunctor/LocalOperandsSyntaxCheck/RefQualifiedLocalType.cc
test_autofunctor_cf_localoperandssyntax_const_SOURCES = \
    ../../Tests/AutoFunctor/LocalOperandsSyntaxCheck/ConstQualifiedLocalType.cc
test_autofunctor_cf_localoperandssyntax_const_ref_SOURCES = \
    ../../Tests/AutoFunctor/LocalOperandsSyntaxCheck/ConstRefQualifiedLocalType.cc

test_autofunctor_SOURCES = \
    ../AutoFunctor/TestMain.cc \
    ../AutoFunctor/AllCombo.cc \
    ../AutoFunctor/AllComboTpl.cc \
    ../AutoFunctor/AssignTo.cc \
    ../AutoFunctor/AssignToTpl.cc \
    ../AutoFunctor/Qualifiers.cc \
    ../AutoFunctor/QualifiersTpl.cc \
    ../AutoFunctor/ParamBindExplicit.cc \
    ../AutoFunctor/ParamBindExplicitTpl.cc \
    ../AutoFunctor/ParamBindImplicit.cc \
    ../AutoFunctor/ParamBindImplicitTpl.cc \
    ../AutoFunctor/ParamBindExplicitAndImplicit.cc \
    ../AutoFunctor/ParamBindExplicitAndImplicitTpl.cc \
    ../AutoFunctor/ParamSetExplicit.cc \
    ../AutoFunctor/ParamSetExplicitTpl.cc \
    ../AutoFunctor/ParamSetImplicit.cc \
    ../AutoFunctor/ParamSetImplicitTpl.cc \
    ../AutoFunctor/ParamSetExplicitAndImplicit.cc \
    ../AutoFunctor/ParamSetExplicitAndImplicitTpl.cc \
    ../AutoFunctor/ParamBindExplicitAndParamSetExplicit.cc \
    ../AutoFunctor/ParamBindExplicitAndParamSetExplicitTpl.cc \
    ../AutoFunctor/ParamBindExplicitAndParamSetImplicit.cc \
    ../AutoFunctor/ParamBindExplicitAndParamSetImplicitTpl.cc \
    ../AutoFunctor/ParamBindImplicitAndParamSetExplicit.cc \
    ../AutoFunctor/ParamBindImplicitAndParamSetExplicitTpl.cc \
    ../AutoFunctor/ParamBindImplicitAndParamSetImplicit.cc \
    ../AutoFunctor/ParamBindImplicitAndParamSetImplicitTpl.cc \
    ../AutoFunctor/MemBindExplicit.cc \
    ../AutoFunctor/MemBindExplicitTpl.cc \
    ../AutoFunctor/MemBindImplicit.cc \
    ../AutoFunctor/MemBindImplicitTpl.cc \
    ../AutoFunctor/MemBindExplicitAndImplicit.cc \
    ../AutoFunctor/MemBindExplicitAndImplicitTpl.cc \
    ../AutoFunctor/MemSetExplicit.cc \
    ../AutoFunctor/MemSetExplicitTpl.cc \
    ../AutoFunctor/MemSetImplicit.cc \
    ../AutoFunctor/MemSetImplicitTpl.cc \
    ../AutoFunctor/MemSetExplicitAndImplicit.cc \
    ../AutoFunctor/MemSetExplicitAndImplicitTpl.cc \
    ../AutoFunctor/MemBindExplicitAndMemSetExplicit.cc \
    ../AutoFunctor/MemBindExplicitAndMemSetExplicitTpl.cc \
    ../AutoFunctor/MemBindExplicitAndMemSetImplicit.cc \
    ../AutoFunctor/MemBindExplicitAndMemSetImplicitTpl.cc \
    ../AutoFunctor/MemBindImplicitAndMemSetExplicit.cc \
    ../AutoFunctor/MemBindImplicitAndMemSetExplicitTpl.cc \
    ../AutoFunctor/MemBindImplicitAndMemSetImplicit.cc \
    ../AutoFunctor/MemBindImplicitAndMemSetImplicitTpl.cc \
    ../AutoFunctor/NoSpec.cc \
    ../AutoFunctor/NoSpecTpl.cc \
    ../AutoFunctor/Nested.cc \
    ../AutoFunctor/NestedTpl.cc \
    ../AutoFunctor/Recursive.cc \
    ../AutoFunctor/RecursiveTpl.cc \
    ../AutoFunctor/Return.cc \
    ../AutoFunctor/ReturnTpl.cc \
    ../AutoFunctor/SelfType.cc \
    ../AutoFunctor/SelfTypeTpl.cc

LCLFUNCTION_SRC = \
    ../LclFunction/TestMain.cc \
    ../LclFunction/NoSpec.cc \
    ../LclFunction/NoSpecTpl.cc \
    ../LclFunction/Params.cc \
    ../LclFunction/ParamsTpl.cc \
    ../LclFunction/VarBindExplicit.cc

test_lclfunction_cpp03_SOURCES = $(LCLFUNCTION_SRC)
test_lclfunction_cpp11_SOURCES = $(LCLFUNCTION_SRC)

test_lclfunction_codegenspec_cpp03_SOURCES = \
    ../../Detail/PP/Translator/BackEnd/LclFunction/Specs/C++03Spec.cc

test_lclfunction_codegenspec_cpp11_SOURCES = \
    ../../Detail/PP/Translator/BackEnd/LclFunction/Specs/C++11Spec.cc

EXTRA_DIST = 

####################
#Preprocessor Flags.
####################

test_autofunctor_CPPFLAGS = \
    $(AM_CPPFLAGS) \
    $(GTEST_CPPFLAGS)

test_lclfunction_cpp03_CPPFLAGS = \
    $(AM_CPPFLAGS) \
    $(GTEST_CPPFLAGS)

test_lclfunction_cpp11_CPPFLAGS = \
    $(AM_CPPFLAGS) \
    $(GTEST_CPPFLAGS)

test_lclfunction_codegenspec_cpp03_CPPFLAGS = \
    $(AM_CPPFLAGS) \
    $(GTEST_CPPFLAGS)

test_lclfunction_codegenspec_cpp11_CPPFLAGS = \
    $(AM_CPPFLAGS) \
    $(GTEST_CPPFLAGS)

################
#Compiler Flags.
################

AM_CXXFLAGS += \
    -pedantic

test_autofunctor_CXXFLAGS = \
    -pedantic

test_lclfunction_cpp03_CXXFLAGS = \
    $(AM_CXXFLAGS) \
    -std=gnu++98

test_lclfunction_cpp11_CXXFLAGS = \
    $(AM_CXXFLAGS) \
    -std=gnu++11

test_lclfunction_codegenspec_cpp03_CXXFLAGS = \
    $(AM_CXXFLAGS) \
    -std=gnu++98

test_lclfunction_codegenspec_cpp11_CXXFLAGS = \
    $(AM_CXXFLAGS) \
    -std=gnu++11

##############
#Linker Flags.
##############

GTEST_LTLIB = \
    $(top_builddir)/WG/ExternalLibsNoInstall/build_autotools/libgtest.la

test_autofunctor_LDADD = $(GTEST_LTLIB)
test_lclfunction_cpp03_LDADD = $(GTEST_LTLIB)
test_lclfunction_cpp11_LDADD = $(GTEST_LTLIB)
test_lclfunction_codegenspec_cpp03_LDADD = $(GTEST_LTLIB)
test_lclfunction_codegenspec_cpp11_LDADD = $(GTEST_LTLIB)
