#include <gtest/gtest.h>
#include <WG/Local/LclClass.hh>
#include <boost/preprocessor/stringize.hpp>

TEST(wg_lclclass_errorreporting_tpl, NotOkIfThisURefQualified)
{
  char const * const errMsg =
    BOOST_PP_STRINGIZE
    (
      WG_LCLCLASS_TPL(noop, memext (ref this_) )
    );

  EXPECT_STREQ(
    errMsg,
    "WG_LCL_Error_ref_keyword_cannot_be_used_with_thisu_keyword");
}

TEST(wg_lclclass_errorreporting_tpl, NotOkIfNamedParameterInvalid)
{
  // MisspelledNamedParameter
  {
    char const * const errMsg =
      BOOST_PP_STRINGIZE
      (
        WG_LCLCLASS_TPL(noop, mmext (this_) )
      );

    EXPECT_STREQ(
      errMsg,
      "WG_LCLCLASS_Error_Invalid_named_parameter");
  }

  // UnknownNamedParameter
  {
    char const * const errMsg =
      BOOST_PP_STRINGIZE
      (
        WG_LCLCLASS_TPL(noop, memext (this_) rAnDM (xyz) )
      );

    EXPECT_STREQ(
      errMsg,
      "WG_LCLCLASS_Error_Invalid_named_parameter");
  }
}

TEST(wg_lclclass_errorreporting_tpl, NotOkIfExplicitlyTypedAndMissingVarName)
{
  // MemExtNonLocalType
  {
    char const * const errMsg =
      BOOST_PP_STRINGIZE
      (
        WG_LCLCLASS_TPL(noop, memext (type(int) ) )
      );

    EXPECT_STREQ(
      errMsg,
      "WG_LCL_Error_missing_variable_name");
  }

  // MemExtLocalType
  {
    char const * const errMsg =
      BOOST_PP_STRINGIZE
      (
        WG_LCLCLASS_TPL(noop, memext (lcltype(Foo) ) )
      );

    EXPECT_STREQ(
      errMsg,
      "WG_LCL_Error_missing_variable_name");
  }

  // MemIntNonLocalType
  {
    char const * const errMsg =
      BOOST_PP_STRINGIZE
      (
        WG_LCLCLASS_TPL(noop, memint (type(int) , 5) )
      );

    EXPECT_STREQ(
      errMsg,
      "WG_LCL_Error_missing_variable_name");
  }

  // MemIntLocalType
  {
    char const * const errMsg =
      BOOST_PP_STRINGIZE
      (
        WG_LCLCLASS_TPL(noop, memint (lcltype(Foo) , 5) )
      );

    EXPECT_STREQ(
      errMsg,
      "WG_LCL_Error_missing_variable_name");
  }
}

TEST(wg_lclclass_errorreporting_tpl, NotOkIfImplicitlyTypedAndMissingVarName)
{
  // MemExtConst
  {
    char const * const errMsg =
      BOOST_PP_STRINGIZE
      (
        WG_LCLCLASS_TPL(noop, memext (const ) )
      );

    EXPECT_STREQ(
      errMsg,
      "WG_LCL_Error_missing_variable_name");
  }

  // MemExtRef
  {
    char const * const errMsg =
      BOOST_PP_STRINGIZE
      (
        WG_LCLCLASS_TPL(noop, memext (ref ) )
      );

    EXPECT_STREQ(
      errMsg,
      "WG_LCL_Error_missing_variable_name");
  }

  // MemExtConstRef
  {
    char const * const errMsg =
      BOOST_PP_STRINGIZE
      (
        WG_LCLCLASS_TPL(noop, memext (const ref ) )
      );

    EXPECT_STREQ(
      errMsg,
      "WG_LCL_Error_missing_variable_name");
  }

  // MemIntConst
  {
    char const * const errMsg =
      BOOST_PP_STRINGIZE
      (
        WG_LCLCLASS_TPL(noop, memint (const , 5) )
      );

    EXPECT_STREQ(
      errMsg,
      "WG_LCL_Error_missing_variable_name");
  }

  // MemIntRef
  {
    char const * const errMsg =
      BOOST_PP_STRINGIZE
      (
        WG_LCLCLASS_TPL(noop, memint (ref , someVar) )
      );

    EXPECT_STREQ(
      errMsg,
      "WG_LCL_Error_missing_variable_name");
  }

  // MemIntConstRef
  {
    char const * const errMsg =
      BOOST_PP_STRINGIZE
      (
        WG_LCLCLASS_TPL(noop, memint (const ref , xyz) )
      );

    EXPECT_STREQ(
      errMsg,
      "WG_LCL_Error_missing_variable_name");
  }
}
