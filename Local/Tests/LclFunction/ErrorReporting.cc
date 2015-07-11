#include <gtest/gtest.h>
#include <WG/Local/LclFunction.hh>
#include <boost/preprocessor/stringize.hpp>

TEST(wg_lclfunction_errorreporting, NotOkIfThisURefQualified)
{
  char const * const errMsg =
    BOOST_PP_STRINGIZE
    (
      WG_LCLFUNCTION(noop, varbind (ref this_) )
    );

  EXPECT_STREQ(
    errMsg,
    "WG_LCL_Error_ref_keyword_cannot_be_used_with_thisu_keyword");
}

TEST(wg_lclfunction_errorreporting, NotOkIfNamedParameterInvalid)
{
  // MisspelledNamedParameter
  {
    char const * const errMsg =
      BOOST_PP_STRINGIZE
      (
        WG_LCLFUNCTION(noop, vrbind (this_) )
      );

    EXPECT_STREQ(
      errMsg,
      "WG_LCLFUNCTION_Error_Invalid_named_parameter");
  }

  // UnknownNamedParameter
  {
    char const * const errMsg =
      BOOST_PP_STRINGIZE
      (
        WG_LCLFUNCTION(noop, varbind (this_) rAnDM (xyz) )
      );

    EXPECT_STREQ(
      errMsg,
      "WG_LCLFUNCTION_Error_Invalid_named_parameter");
  }
}

TEST(wg_lclfunction_errorreporting, NotOkIfExplicitlyTypedAndMissingVarName)
{
  // VarBind
  {
    char const * const errMsg =
      BOOST_PP_STRINGIZE
      (
        WG_LCLFUNCTION(noop, varbind (type(int) ) )
      );

    EXPECT_STREQ(
      errMsg,
      "WG_LCL_Error_missing_variable_name");
  }

  // VarBind
  {
    char const * const errMsg =
      BOOST_PP_STRINGIZE
      (
        WG_LCLFUNCTION(noop, varset (type(int) , 5) )
      );

    EXPECT_STREQ(
      errMsg,
      "WG_LCL_Error_missing_variable_name");
  }
}

TEST(wg_lclfunction_errorreporting, NotOkIfImplicitlyTypedAndMissingVarName)
{
  // VarBindConst
  {
    char const * const errMsg =
      BOOST_PP_STRINGIZE
      (
        WG_LCLFUNCTION(noop, varbind (const ) )
      );

    EXPECT_STREQ(
      errMsg,
      "WG_LCL_Error_missing_variable_name");
  }

  // VarBindRef
  {
    char const * const errMsg =
      BOOST_PP_STRINGIZE
      (
        WG_LCLFUNCTION(noop, varbind (ref ) )
      );

    EXPECT_STREQ(
      errMsg,
      "WG_LCL_Error_missing_variable_name");
  }

  // VarBindConstRef
  {
    char const * const errMsg =
      BOOST_PP_STRINGIZE
      (
        WG_LCLFUNCTION(noop, varbind (const ref ) )
      );

    EXPECT_STREQ(
      errMsg,
      "WG_LCL_Error_missing_variable_name");
  }

  // VarSetConst
  {
    char const * const errMsg =
      BOOST_PP_STRINGIZE
      (
        WG_LCLFUNCTION(noop, varset (const , abc) )
      );

    EXPECT_STREQ(
      errMsg,
      "WG_LCL_Error_missing_variable_name");
  }

  // VarSetRef
  {
    char const * const errMsg =
      BOOST_PP_STRINGIZE
      (
        WG_LCLFUNCTION(noop, varset (ref , xyz) )
      );

    EXPECT_STREQ(
      errMsg,
      "WG_LCL_Error_missing_variable_name");
  }

  // VarSetConstRef
  {
    char const * const errMsg =
      BOOST_PP_STRINGIZE
      (
        WG_LCLFUNCTION(noop, varset (const ref , 123) )
      );

    EXPECT_STREQ(
      errMsg,
      "WG_LCL_Error_missing_variable_name");
  }
}
