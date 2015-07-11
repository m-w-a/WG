include $(top_srcdir)/StandardCppFlags.am
include $(top_srcdir)/WG/ExternalLibsNoInstall/build_autotools/GTestFlags.am

###########################
#Declare programs and libs.
###########################

noinst_PROGRAMS = \
	test_testutils \
    test_pp_pp \
    test_pp_wgseq \
    test_pp_tokenmatch \
    test_pp_keywords \
    test_pp_trnsltr_markers \
    test_pp_trnsltr_vardcln \
    test_pp_trnsltr_vardcln_implicit \
    test_pp_trnsltr_vardcln_explicit \
    test_pp_trnsltr_parsedtype_cpp03 \
    test_pp_trnsltr_parsedtype_cpp11 \
    test_pp_lclfunction_keywords \
    test_lclfunction_testutils \
    test_lclfunction_cpp03 \
    test_lclfunction_cpp11 \
    test_lclfunction_codegenspec_cpp03 \
    test_lclfunction_codegenspec_cpp11 \
    test_pp_lclclass_keywords \
    test_lclclass_cpp03 \
    test_lclclass_cpp11 \
    test_pp_lclcontext_keywords \
    test_autosimulator_cpp03 \
    test_autosimulator_cpp11 \
    test_lclcontext_testutils \
    test_lclcontext_cpp03 \
    test_lclcontext_cpp11 \
    test_lclcontext_cpp03_noex \
    test_lclcontext_cpp11_noex

TEST_BIN_DIR = $(abs_top_builddir)/bin/

TEST_WG_TESTUTILS_APPNAME = test_testutils$(EXEEXT)
TEST_WG_TESTUTILS_APPALTPATH = \
    $(TEST_BIN_DIR)/$(TEST_WG_TESTUTILS_APPNAME)
TEST_WG_TESTUTILS_APPBUILDLOC = \
    $(abs_builddir)/$(TEST_WG_TESTUTILS_APPNAME)

TEST_WG_LCLCLASS_CPP03_APPNAME = test_lclclass_cpp03$(EXEEXT)
TEST_WG_LCLCLASS_CPP03_APPALTPATH = \
    $(TEST_BIN_DIR)/$(TEST_WG_LCLCLASS_CPP03_APPNAME)
TEST_WG_LCLCLASS_CPP03_APPBUILDLOC = \
    $(abs_builddir)/$(TEST_WG_LCLCLASS_CPP03_APPNAME)

TEST_WG_LCLCLASS_CPP11_APPNAME = test_lclclass_cpp11$(EXEEXT)
TEST_WG_LCLCLASS_CPP11_APPALTPATH = \
    $(TEST_BIN_DIR)/$(TEST_WG_LCLCLASS_CPP11_APPNAME)
TEST_WG_LCLCLASS_CPP11_APPBUILDLOC = \
    $(abs_builddir)/$(TEST_WG_LCLCLASS_CPP11_APPNAME)

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

TEST_WG_LCLFUNCTION_TESTUTILS_APPNAME = test_lclfunction_testutils$(EXEEXT)
TEST_WG_LCLFUNCTION_TESTUTILS_APPALTPATH = \
    $(TEST_BIN_DIR)\$(TEST_WG_LCLFUNCTION_TESTUTILS_APPNAME)
TEST_WG_LCLFUNCTION_TESTUTILS_APPBUILDLOC = \
    $(abs_builddir)/$(TEST_WG_LCLFUNCTION_TESTUTILS_APPNAME)

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

TEST_WG_AUTOSIMULATOR_CPP03_APPNAME = \
    test_autosimulator_cpp03$(EXEEXT)
TEST_WG_AUTOSIMULATOR_CPP03_APPALTPATH = \
    $(TEST_BIN_DIR)/$(TEST_WG_AUTOSIMULATOR_CPP03_APPNAME)
TEST_WG_AUTOSIMULATOR_CPP03_APPBUILDLOC = \
    $(abs_builddir)/$(TEST_WG_AUTOSIMULATOR_CPP03_APPNAME)

TEST_WG_AUTOSIMULATOR_CPP11_APPNAME = \
    test_autosimulator_cpp11$(EXEEXT)
TEST_WG_AUTOSIMULATOR_CPP11_APPALTPATH = \
    $(TEST_BIN_DIR)/$(TEST_WG_AUTOSIMULATOR_CPP11_APPNAME)
TEST_WG_AUTOSIMULATOR_CPP11_APPBUILDLOC = \
    $(abs_builddir)/$(TEST_WG_AUTOSIMULATOR_CPP11_APPNAME)

TEST_WG_LCLCONTEXT_TESTUTILS_APPNAME = \
    test_lclcontext_testutils$(EXEEXT)
TEST_WG_LCLCONTEXT_TESTUTILS_APPALTPATH = \
    $(TEST_BIN_DIR)/$(TEST_WG_LCLCONTEXT_TESTUTILS_APPNAME)
TEST_WG_LCLCONTEXT_TESTUTILS_APPBUILDLOC = \
    $(abs_builddir)/$(TEST_WG_LCLCONTEXT_TESTUTILS_APPNAME)

TEST_WG_LCLCONTEXT_CPP03_APPNAME = \
    test_lclcontext_cpp03$(EXEEXT)
TEST_WG_LCLCONTEXT_CPP03_APPALTPATH = \
    $(TEST_BIN_DIR)/$(TEST_WG_LCLCONTEXT_CPP03_APPNAME)
TEST_WG_LCLCONTEXT_CPP03_APPBUILDLOC = \
    $(abs_builddir)/$(TEST_WG_LCLCONTEXT_CPP03_APPNAME)

TEST_WG_LCLCONTEXT_CPP03_NOEX_APPNAME = \
    test_LCLCONTEXT_CPP03_NOEX$(EXEEXT)
TEST_WG_LCLCONTEXT_CPP03_NOEX_APPALTPATH = \
    $(TEST_BIN_DIR)/$(TEST_WG_LCLCONTEXT_CPP03_NOEX_APPNAME)
TEST_WG_LCLCONTEXT_CPP03_NOEX_APPBUILDLOC = \
    $(abs_builddir)/$(TEST_WG_LCLCONTEXT_CPP03_NOEX_APPNAME)

TEST_WG_LCLCONTEXT_CPP11_APPNAME = \
    test_lclcontext_cpp11$(EXEEXT)
TEST_WG_LCLCONTEXT_CPP11_APPALTPATH = \
    $(TEST_BIN_DIR)/$(TEST_WG_LCLCONTEXT_CPP11_APPNAME)
TEST_WG_LCLCONTEXT_CPP11_APPBUILDLOC = \
    $(abs_builddir)/$(TEST_WG_LCLCONTEXT_CPP11_APPNAME)

TEST_WG_LCLCONTEXT_CPP11_NOEX_APPNAME = \
    test_LCLCONTEXT_CPP11_NOEX$(EXEEXT)
TEST_WG_LCLCONTEXT_CPP11_NOEX_APPALTPATH = \
    $(TEST_BIN_DIR)/$(TEST_WG_LCLCONTEXT_CPP11_NOEX_APPNAME)
TEST_WG_LCLCONTEXT_CPP11_NOEX_APPBUILDLOC = \
    $(abs_builddir)/$(TEST_WG_LCLCONTEXT_CPP11_NOEX_APPNAME)

#Custom init.
all-local : \
    $(TEST_BIN_DIR) \
    $(TEST_WG_TESTUTILS_APPALTPATH) \
    $(TEST_WG_LCLCLASS_CPP03_APPALTPATH) \
    $(TEST_WG_LCLCLASS_CPP11_APPALTPATH) \
    $(TEST_WG_LCLFUNCTION_TESTUTILS_APPALTPATH) \
    $(TEST_WG_LCLFUNCTION_CODEGENSPEC_CPP03_APPALTPATH) \
    $(TEST_WG_LCLFUNCTION_CODEGENSPEC_CPP11_APPALTPATH) \
    $(TEST_WG_LCLFUNCTION_CPP03_APPALTPATH) \
    $(TEST_WG_LCLFUNCTION_CPP11_APPALTPATH) \
    $(TEST_WG_AUTOSIMULATOR_CPP03_APPALTPATH) \
    $(TEST_WG_AUTOSIMULATOR_CPP11_APPALTPATH) \
    $(TEST_WG_LCLCONTEXT_TESTUTILS_APPALTPATH) \
    $(TEST_WG_LCLCONTEXT_CPP03_APPALTPATH) \
    $(TEST_WG_LCLCONTEXT_CPP11_APPALTPATH) \
    $(TEST_WG_LCLCONTEXT_CPP03_NOEX_APPALTPATH) \
    $(TEST_WG_LCLCONTEXT_CPP11_NOEX_APPALTPATH)
    
$(TEST_BIN_DIR) :
	$(MKDIR_P) $(TEST_BIN_DIR)

$(TEST_WG_TESTUTILS_APPALTPATH) : $(TEST_WG_TESTUTILS_APPBUILDLOC)
	( cd $(TEST_BIN_DIR); \
      $(LN_S) -f \
          $(TEST_WG_TESTUTILS_APPBUILDLOC) \
          $(TEST_WG_TESTUTILS_APPNAME); )

$(TEST_WG_LCLCLASS_CPP03_APPALTPATH) : $(TEST_WG_LCLCLASS_CPP03_APPBUILDLOC)
	( cd $(TEST_BIN_DIR); \
      $(LN_S) -f \
          $(TEST_WG_LCLCLASS_CPP03_APPBUILDLOC) \
          $(TEST_WG_LCLCLASS_CPP03_APPNAME); )

$(TEST_WG_LCLCLASS_CPP11_APPALTPATH) : $(TEST_WG_LCLCLASS_CPP11_APPBUILDLOC)
	( cd $(TEST_BIN_DIR); \
      $(LN_S) -f \
          $(TEST_WG_LCLCLASS_CPP11_APPBUILDLOC) \
          $(TEST_WG_LCLCLASS_CPP11_APPNAME); )

$(TEST_WG_LCLFUNCTION_TESTUTILS_APPALTPATH) : $(TEST_WG_LCLFUNCTION_TESTUTILS_APPBUILDLOC)
	( cd $(TEST_BIN_DIR); \
      $(LN_S) -f \
          $(TEST_WG_LCLFUNCTION_TESTUTILS_APPBUILDLOC) \
          $(TEST_WG_LCLFUNCTION_TESTUTILS_APPNAME); )

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

$(TEST_WG_AUTOSIMULATOR_CPP03_APPALTPATH) : $(TEST_WG_AUTOSIMULATOR_CPP03_APPBUILDLOC)
	( cd $(TEST_BIN_DIR); \
	  $(LN_S) -f \
	      $(TEST_WG_AUTOSIMULATOR_CPP03_APPBUILDLOC) \
	      $(TEST_WG_AUTOSIMULATOR_CPP03_APPNAME); )

$(TEST_WG_AUTOSIMULATOR_CPP11_APPALTPATH) : $(TEST_WG_AUTOSIMULATOR_CPP11_APPBUILDLOC)
	( cd $(TEST_BIN_DIR); \
	  $(LN_S) -f \
	      $(TEST_WG_AUTOSIMULATOR_CPP11_APPBUILDLOC) \
	      $(TEST_WG_AUTOSIMULATOR_CPP11_APPNAME); )

$(TEST_WG_LCLCONTEXT_TESTUTILS_APPALTPATH) : $(TEST_WG_LCLCONTEXT_TESTUTILS_APPBUILDLOC)
	( cd $(TEST_BIN_DIR); \
	  $(LN_S) -f \
	      $(TEST_WG_LCLCONTEXT_TESTUTILS_APPBUILDLOC) \
	      $(TEST_WG_LCLCONTEXT_TESTUTILS_APPNAME); )

$(TEST_WG_LCLCONTEXT_CPP03_APPALTPATH) : $(TEST_WG_LCLCONTEXT_CPP03_APPBUILDLOC)
	( cd $(TEST_BIN_DIR); \
	  $(LN_S) -f \
	      $(TEST_WG_LCLCONTEXT_CPP03_APPBUILDLOC) \
	      $(TEST_WG_LCLCONTEXT_CPP03_APPNAME); )

$(TEST_WG_LCLCONTEXT_CPP03_NOEX_APPALTPATH) : $(TEST_WG_LCLCONTEXT_CPP03_NOEX_APPBUILDLOC)
	( cd $(TEST_BIN_DIR); \
	  $(LN_S) -f \
	      $(TEST_WG_LCLCONTEXT_CPP03_NOEX_APPBUILDLOC) \
	      $(TEST_WG_LCLCONTEXT_CPP03_NOEX_APPNAME); )

$(TEST_WG_LCLCONTEXT_CPP11_APPALTPATH) : $(TEST_WG_LCLCONTEXT_CPP11_APPBUILDLOC)
	( cd $(TEST_BIN_DIR); \
	  $(LN_S) -f \
	      $(TEST_WG_LCLCONTEXT_CPP11_APPBUILDLOC) \
	      $(TEST_WG_LCLCONTEXT_CPP11_APPNAME); )

$(TEST_WG_LCLCONTEXT_CPP11_NOEX_APPALTPATH) : $(TEST_WG_LCLCONTEXT_CPP11_NOEX_APPBUILDLOC)
	( cd $(TEST_BIN_DIR); \
	  $(LN_S) -f \
	      $(TEST_WG_LCLCONTEXT_CPP11_NOEX_APPBUILDLOC) \
	      $(TEST_WG_LCLCONTEXT_CPP11_NOEX_APPNAME); )

#Custom finalize.
clean-local : \
    rm -rf $(TEST_BIN_DIR)$(TEST_WG_TESTUTILS_APPNAME) \
    rm -rf $(TEST_BIN_DIR)/$(TEST_WG_LCLCLASS_CPP03_APPNAME) \
    rm -rf $(TEST_BIN_DIR)/$(TEST_WG_LCLCLASS_CPP11_APPNAME) \
    rm -rf $(TEST_WG_LCLFUNCTION_CODEGENSPEC_CPP03_APPNAME) \
    rm -rf $(TEST_WG_LCLFUNCTION_CODEGENSPEC_CPP11_APPNAME) \
    rm -rf $(TEST_WG_LCLFUNCTION_TESTUTILS_APPNAME) \
    rm -rf $(TEST_WG_LCLFUNCTION_CPP03_APPNAME) \
    rm -rf $(TEST_WG_LCLFUNCTION_CPP11_APPNAME) \
    rm -rf $(TEST_WG_AUTOSIMULATOR_CPP03_APPNAME) \
    rm -rf $(TEST_WG_AUTOSIMULATOR_CPP11_APPNAME) \
    rm -rf $(TEST_WG_LCLCONTEXT_TESTUTILS_APPNAME) \
    rm -rf $(TEST_WG_LCLCONTEXT_CPP03_APPNAME) \
    rm -rf $(TEST_WG_LCLCONTEXT_CPP11_APPNAME) \
    rm -rf $(TEST_WG_LCLCONTEXT_CPP03_NOEX_APPNAME) \
    rm -rf $(TEST_WG_LCLCONTEXT_CPP11_NOEX_APPNAME)

##############################
#Automatically executed tests.
##############################
# Don't add test_pp_* to TESTS since they're preprocessor compile-only tests.
TESTS = \
    $(TEST_WG_TESTUTILS_APPNAME) \
    $(TEST_WG_LCLCLASS_CPP03_APPNAME) \
    $(TEST_WG_LCLCLASS_CPP11_APPNAME) \
    $(TEST_WG_LCLFUNCTION_TESTUTILS_APPNAME) \
    $(TEST_WG_LCLFUNCTION_CPP03_APPNAME) \
    $(TEST_WG_LCLFUNCTION_CPP11_APPNAME) \
    $(TEST_WG_AUTOSIMULATOR_CPP03_APPNAME) \
    $(TEST_WG_AUTOSIMULATOR_CPP11_APPNAME) \
    $(TEST_WG_LCLCONTEXT_TESTUTILS_APPNAME) \
    $(TEST_WG_LCLCONTEXT_CPP03_APPNAME) \
    $(TEST_WG_LCLCONTEXT_CPP11_APPNAME) \
    $(TEST_WG_LCLCONTEXT_CPP03_NOEX_APPNAME) \
    $(TEST_WG_LCLCONTEXT_CPP11_NOEX_APPNAME)

test_testutils_SOURCES = \
    ../Utils/Tests/TestMain.cc \
    ../Utils/Tests/UtilsUnitTest.cc \
    ../Utils/Tests/TrileanUnitTest.cc

test_pp_pp_SOURCES = ../../Detail/PP/Tests/PPUnitTest.cc
test_pp_wgseq_SOURCES = ../../Detail/PP/Tests/SeqUnitTest.cc
test_pp_tokenmatch_SOURCES = ../../Detail/PP/Tests/TokenMatchUnitTest.cc
test_pp_keywords_SOURCES = ../../Detail/PP/Translator/Tests/KeywordsUnitTest.cc
test_pp_trnsltr_markers_SOURCES = ../../Detail/PP/Translator/Tests/MarkersUnitTest.cc
test_pp_trnsltr_vardcln_SOURCES = ../../Detail/PP/Translator/FrontEnd/VarDclns/Tests/VarDclnUnitTest.cc
test_pp_trnsltr_vardcln_implicit_SOURCES = ../../Detail/PP/Translator/FrontEnd/VarDclns/Tests/VarDclnImplicitUnitTest.cc
test_pp_trnsltr_vardcln_explicit_SOURCES = ../../Detail/PP/Translator/FrontEnd/VarDclns/Tests/VarDclnExplicitUnitTest.cc
test_pp_trnsltr_parsedtype_cpp03_SOURCES = ../../Detail/PP/Translator/BackEnd/Tests/TypeExtractorUnitTest.cc
test_pp_trnsltr_parsedtype_cpp11_SOURCES = ../../Detail/PP/Translator/BackEnd/Tests/TypeExtractorUnitTest.cc

test_pp_lclfunction_keywords_SOURCES = \
    ../../Detail/PP/Translator/FrontEnd/LclFunction/Tests/KeywordsUnitTest.cc

test_pp_lclclass_keywords_SOURCES = \
    ../../Detail/PP/Translator/FrontEnd/LclClass/Tests/KeywordsUnitTest.cc

test_pp_lclcontext_keywords_SOURCES = \
    ../../Detail/PP/Translator/FrontEnd/LclContext/Tests/KeywordsUnitTest.cc

LCLCLASS_SRC = \
    ../LclClass/TestMain.cc \
    ../LclClass/ErrorReporting.cc \
    ../LclClass/ErrorReportingTpl.cc \
    ../LclClass/Derives.cc \
    ../LclClass/DerivesTpl.cc \
    ../LclClass/BaseInit.cc \
    ../LclClass/BaseInitTpl.cc \
    ../LclClass/MacroParamNamesAsVarNames.cc \
    ../LclClass/MemExtExplicit.cc \
    ../LclClass/MemExtExplicitTpl.cc \
    ../LclClass/MemExtImplicit.cc \
    ../LclClass/MemExtImplicitTpl.cc \
    ../LclClass/MemExtExplicitAndImplicit.cc \
    ../LclClass/MemExtExplicitAndImplicitTpl.cc \
    ../LclClass/MemIntExplicit.cc \
    ../LclClass/MemIntExplicitTpl.cc \
    ../LclClass/MemIntImplicit.cc \
    ../LclClass/MemIntImplicitTpl.cc \
    ../LclClass/MemIntExplicitAndImplicit.cc \
    ../LclClass/MemIntExplicitAndImplicitTpl.cc \
    ../LclClass/MemExtAndMemInt.cc \
    ../LclClass/MemExtAndMemIntTpl.cc \
    ../LclClass/AllCombo.cc \
    ../LclClass/AllComboTpl.cc \
    ../LclClass/InitHook.cc \
    ../LclClass/InitHookTpl.cc \
    ../LclClass/Nested.cc \
    ../LclClass/NestedTpl.cc \
    ../LclClass/MultipleUseInSameMacro.cc \
    ../LclClass/MultipleUseInSameMacroTpl.cc

test_lclclass_cpp03_SOURCES = $(LCLCLASS_SRC)
test_lclclass_cpp11_SOURCES = $(LCLCLASS_SRC)

test_lclfunction_testutils_SOURCES = \
    ../LclFunction/Utils/Detail/Source/LclFunctionCallRegistrar.cc \
    ../LclFunction/Utils/Detail/Source/LclFunctionCallVerifier.cc \
    ../LclFunction/Utils/Tests/TestMain.cc \
    ../LclFunction/Utils/Tests/TestLclFunctionUnitTest.cc \
    ../LclFunction/Utils/Tests/TestLclFunctionTplUnitTest.cc

LCLFUNCTION_SRC = \
    ../LclFunction/TestMain.cc \
    ../LclFunction/Utils/Detail/Source/LclFunctionCallRegistrar.cc \
    ../LclFunction/Utils/Detail/Source/LclFunctionCallVerifier.cc \
    ../LclFunction/ErrorReporting.cc \
    ../LclFunction/ErrorReportingTpl.cc \
    ../LclFunction/Arrays.cc \
    ../LclFunction/ArraysTpl.cc \
    ../LclFunction/AllCombo.cc \
    ../LclFunction/AllComboTpl.cc \
    ../LclFunction/AsTemplateParameterArg.cc \
    ../LclFunction/AsTemplateParameterArgTpl.cc \
    ../LclFunction/BoostFunction.cc \
    ../LclFunction/BoostFunctionTpl.cc \
    ../LclFunction/Nested.cc \
    ../LclFunction/NestedTpl.cc \
    ../LclFunction/NoSpec.cc \
    ../LclFunction/NoSpecTpl.cc \
    ../LclFunction/Params.cc \
    ../LclFunction/ParamsTpl.cc \
    ../LclFunction/VarBindExplicit.cc \
    ../LclFunction/VarBindExplicitTpl.cc \
    ../LclFunction/VarBindImplicit.cc \
    ../LclFunction/VarBindImplicitTpl.cc \
    ../LclFunction/VarSetExplicit.cc \
    ../LclFunction/VarSetExplicitTpl.cc \
    ../LclFunction/VarSetImplicit.cc \
    ../LclFunction/VarSetImplicitTpl.cc \
    ../LclFunction/VarBindExplicitAndImplicit.cc \
    ../LclFunction/VarBindExplicitAndImplicitTpl.cc \
    ../LclFunction/VarSetExplicitAndImplicit.cc \
    ../LclFunction/VarSetExplicitAndImplicitTpl.cc \
    ../LclFunction/VarBindExplicitAndVarSetExplicit.cc \
    ../LclFunction/VarBindExplicitAndVarSetExplicitTpl.cc \
    ../LclFunction/VarBindExplicitAndVarSetImplicit.cc \
    ../LclFunction/VarBindExplicitAndVarSetImplicitTpl.cc \
    ../LclFunction/VarBindImplicitAndVarSetExplicit.cc \
    ../LclFunction/VarBindImplicitAndVarSetExplicitTpl.cc \
    ../LclFunction/VarBindImplicitAndVarSetImplicit.cc \
    ../LclFunction/VarBindImplicitAndVarSetImplicitTpl.cc \
    ../LclFunction/Return.cc \
    ../LclFunction/ReturnTpl.cc \
    ../LclFunction/Recursive.cc \
    ../LclFunction/RecursiveTpl.cc \
    ../LclFunction/MultipleUseInSameMacro.cc \
    ../LclFunction/MultipleUseInSameMacroTpl.cc \
    ../LclFunction/FunctionSignatureTypenamesAndConstants.cc \
    ../LclFunction/FunctionSignatureTypenamesAndConstantsTpl.cc \
    ../LclFunction/LclFunctionTypeOf.cc \
    ../LclFunction/LclFunctionTypeOfTpl.cc \
    ../LclFunction/MacroParamNamesAsVarNames.cc \
    ../LclFunction/MacroParamNamesAsVarNamesTpl.cc \
    ../LclFunction/LclFunctionConfigParamsMaxArityDefault.cc \
    ../LclFunction/LclFunctionConfigParamsMaxArityCustom.cc

test_lclfunction_cpp03_SOURCES = \
    $(LCLFUNCTION_SRC)

test_lclfunction_cpp11_SOURCES = \
    $(LCLFUNCTION_SRC) \
    ../LclFunction/ParamsVariadic.cc \
    ../LclFunction/VarBindVariadic.cc

test_lclfunction_codegenspec_cpp03_SOURCES = \
    ../../Detail/PP/Translator/BackEnd/LclFunction/Specs/C++03Spec.cc

test_lclfunction_codegenspec_cpp11_SOURCES = \
    ../../Detail/PP/Translator/BackEnd/LclFunction/Specs/C++11Spec.cc

AUTOSIMULATOR_SRC = \
    ../../Detail/AutoSimulator/Tests/TestMain.cc \
    ../../Detail/AutoSimulator/Tests/UtilsUnitTest.cc \
    ../../Detail/AutoSimulator/Detail/Tests/TypeTraitsUnitTest.cc \
    ../../Detail/AutoSimulator/Tests/AutoAnyNonArrayExpr.cc \
    ../../Detail/AutoSimulator/Tests/AutoAnyArrayExpr.cc

test_autosimulator_cpp03_SOURCES = \
    $(AUTOSIMULATOR_SRC) \
    ../../Detail/AutoSimulator/Detail/Tests/AutoAnyUnitTest03.cc

test_autosimulator_cpp11_SOURCES = \
    $(AUTOSIMULATOR_SRC) \
    ../../Detail/AutoSimulator/Detail/Tests/AutoAnyUnitTest11.cc

test_lclcontext_testutils_SOURCES = \
    ../LclContext/Utils/Source/Utils.cc \
    ../LclContext/Utils/Source/Records.cc \
    ../LclContext/Utils/Detail/Source/IRecorder.cc \
    ../LclContext/Utils/Tests/TestMain.cc \
    ../LclContext/Utils/Tests/UtilsUnitTest.cc \
    ../LclContext/Utils/Tests/RecordsUnitTest.cc \
    ../LclContext/Utils/Tests/ScopeMngrTemplateUnitTest.cc

LCLCONTEXT_SRC = \
    ../LclContext/Utils/Source/Utils.cc \
    ../LclContext/Utils/Source/Records.cc \
    ../LclContext/Utils/Detail/Source/IRecorder.cc \
    ../LclContext/TestMain.cc \
    ../LclContext/ExtantUncapturedEntry.cc \
    ../LclContext/ExtantCapturedEntry.cc \
    ../LclContext/AdhocImplicitBoundVar.cc \
    ../LclContext/AdhocExplicitBoundVar.cc \
    ../LclContext/AdhocEnterSpecified.cc \
    ../LclContext/AdhocExitSpecified.cc \
    ../LclContext/AdhocEnterAndExitSpecified.cc \
    ../LclContext/ExtantAndAdhoc.cc \
    ../LclContext/Nested.cc \
    ../LclContext/MultipleUseInSameMacro.cc \
    ../LclContext/RaiiAdaptor.cc

LCLCONTEXT_SRC_CPP11 = \
    $(LCLCONTEXT_SRC) \
	../LclContext/AdhocVariadic.cc

test_lclcontext_cpp03_SOURCES = $(LCLCONTEXT_SRC)
test_lclcontext_cpp11_SOURCES = $(LCLCONTEXT_SRC_CPP11)
test_lclcontext_cpp03_noex_SOURCES = $(LCLCONTEXT_SRC)
test_lclcontext_cpp11_noex_SOURCES = $(LCLCONTEXT_SRC_CPP11)

EXTRA_DIST = 

####################
#Preprocessor Flags.
####################

AM_CPPFLAGS += \
    -ftrack-macro-expansion=0

test_testutils_CPPFLAGS = \
    $(AM_CPPFLAGS) \
    $(GTEST_CPPFLAGS)

test_lclclass_cpp03_CPPFLAGS = \
    $(AM_CPPFLAGS) \
    $(GTEST_CPPFLAGS)

test_lclclass_cpp11_CPPFLAGS = \
    $(AM_CPPFLAGS) \
    $(GTEST_CPPFLAGS)

test_lclfunction_testutils_CPPFLAGS = \
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

test_autosimulator_cpp03_CPPFLAGS = \
    $(AM_CPPFLAGS) \
    $(GTEST_CPPFLAGS)

test_autosimulator_cpp11_CPPFLAGS = \
    $(AM_CPPFLAGS) \
    $(GTEST_CPPFLAGS)

test_lclcontext_testutils_CPPFLAGS = \
    $(AM_CPPFLAGS) \
    $(GTEST_CPPFLAGS)

test_lclcontext_cpp03_CPPFLAGS = \
    $(AM_CPPFLAGS) \
    $(GTEST_CPPFLAGS)

test_lclcontext_cpp11_CPPFLAGS = \
    $(AM_CPPFLAGS) \
    $(GTEST_CPPFLAGS)

test_lclcontext_cpp03_noex_CPPFLAGS = \
    $(AM_CPPFLAGS) \
    $(GTEST_CPPFLAGS) \
    -DBOOST_NO_EXCEPTIONS

test_lclcontext_cpp11_noex_CPPFLAGS = \
    $(AM_CPPFLAGS) \
    $(GTEST_CPPFLAGS) \
    -DBOOST_NO_EXCEPTIONS

################
#Compiler Flags.
################

test_pp_trnsltr_parsedtype_cpp11_CXXFLAGS = \
    -std=gnu++11

AM_CXXFLAGS += \
    -pedantic \
    -Wno-unused-local-typedefs

test_testutils_CXXFLAGS = \
    $(AM_CXXFLAGS)

test_lclclass_cpp03_CXXFLAGS = \
    $(AM_CXXFLAGS) \
    -std=gnu++98

test_lclclass_cpp11_CXXFLAGS = \
    $(AM_CXXFLAGS) \
    -std=gnu++11

test_lclfunction_testutils_CXXFLAGS = \
    $(AM_CXXFLAGS)

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

test_autosimulator_cpp03_CXXFLAGS = \
    $(AM_CXXFLAGS) \
    -std=gnu++98

test_autosimulator_cpp11_CXXFLAGS = \
    $(AM_CXXFLAGS) \
    -std=gnu++11

test_lclcontext_testutils_CXXFLAGS = \
    $(AM_CXXFLAGS)

test_lclcontext_cpp03_CXXFLAGS = \
    $(AM_CXXFLAGS) \
    -std=gnu++98
    
test_lclcontext_cpp11_CXXFLAGS = \
    $(AM_CXXFLAGS) \
    -std=gnu++11

test_lclcontext_cpp03_noex_CXXFLAGS = \
    $(AM_CXXFLAGS) \
    -std=gnu++98 \
    -fno-exceptions
    
test_lclcontext_cpp11_noex_CXXFLAGS = \
    $(AM_CXXFLAGS) \
    -std=gnu++11 \
    -fno-exceptions

##############
#Linker Flags.
##############

GTEST_LTLIB = \
    $(top_builddir)/WG/ExternalLibsNoInstall/build_autotools/libgtest.la

test_testutils_LDADD = $(GTEST_LTLIB)
test_lclclass_cpp03_LDADD = $(GTEST_LTLIB)
test_lclclass_cpp11_LDADD = $(GTEST_LTLIB)
test_lclfunction_testutils_LDADD = $(GTEST_LTLIB)
test_lclfunction_cpp03_LDADD = $(GTEST_LTLIB)
test_lclfunction_cpp11_LDADD = $(GTEST_LTLIB)
test_lclfunction_codegenspec_cpp03_LDADD = $(GTEST_LTLIB)
test_lclfunction_codegenspec_cpp11_LDADD = $(GTEST_LTLIB)
test_autosimulator_cpp03_LDADD = $(GTEST_LTLIB)
test_autosimulator_cpp11_LDADD = $(GTEST_LTLIB)
test_lclcontext_testutils_LDADD = $(GTEST_LTLIB)
test_lclcontext_cpp03_LDADD = $(GTEST_LTLIB)
test_lclcontext_cpp11_LDADD = $(GTEST_LTLIB)
test_lclcontext_cpp03_noex_LDADD = $(GTEST_LTLIB)
test_lclcontext_cpp11_noex_LDADD = $(GTEST_LTLIB)
