#include <gtest/gtest.h>
#include <WG/Local/LclClass.hh>
#include <boost/preprocessor/stringize.hpp>

TEST(wg_lclclass_errorreporting, NotOkIfThisURefQualified)
{
  char const * const errMsg =
    BOOST_PP_STRINGIZE
    (
      WG_LCLCLASS(noop, memext (ref this_) )
    );

  EXPECT_STREQ(
    errMsg,
    "WG_LCL_Error_ref_keyword_cannot_be_used_with_thisu_keyword");
}

TEST(wg_lclclass_errorreporting, NotOkIfNamedParameterInvalid)
{
  char const * const errMsg1 =
    BOOST_PP_STRINGIZE
    (
      WG_LCLCLASS(noop, mmext (this_) )
    );

  char const * const errMsg2 =
    BOOST_PP_STRINGIZE
    (
      WG_LCLCLASS(noop, memext (this_) rAnDM (xyz) )
    );

  EXPECT_STREQ(
    errMsg1,
    "WG_LCLCLASS_Error_Invalid_named_parameter");

  EXPECT_STREQ(
    errMsg2,
    "WG_LCLCLASS_Error_Invalid_named_parameter");
}
