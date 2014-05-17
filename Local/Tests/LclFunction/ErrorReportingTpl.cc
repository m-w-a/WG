#include <gtest/gtest.h>
#include <WG/Local/LclFunction.hh>
#include <boost/preprocessor/stringize.hpp>

TEST(wg_lclfunction_errorreporting_tpl, NotOkIfThisURefQualified)
{
  char const * const errMsg =
    BOOST_PP_STRINGIZE
    (
      WG_LCLFUNCTION_TPL(noop, varbind (ref this_) )
    );

  EXPECT_STREQ(
    errMsg,
    "WG_LCL_Error_ref_keyword_cannot_be_used_with_thisu_keyword");
}

TEST(wg_lclfunction_errorreporting_tpl, NotOkIfNamedParameterInvalid)
{
  char const * const errMsg1 =
    BOOST_PP_STRINGIZE
    (
      WG_LCLFUNCTION_TPL(noop, vrbind (this_) )
    );

  char const * const errMsg2 =
    BOOST_PP_STRINGIZE
    (
      WG_LCLFUNCTION_TPL(noop, varbind (this_) rAnDM (xyz) )
    );

  EXPECT_STREQ(
    errMsg1,
    "WG_LCLFUNCTION_Error_Invalid_named_parameter");

  EXPECT_STREQ(
    errMsg2,
    "WG_LCLFUNCTION_Error_Invalid_named_parameter");
}
