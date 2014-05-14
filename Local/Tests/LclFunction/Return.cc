#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/LclFunction/Utils/TestLclFunction.hh>
#include <boost/tuple/tuple.hpp>
#include <WG/Local/Tests/Utils/Utils.hh>

TEST(wg_lclfunction_return, OkIfSpecified)
{
  try
  {
    bool retval = false;

    WG_TEST_LCLFUNCTION(rettest, return (int) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(rettest);
      return 1;
    }
    WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, rettest());

    retval = rettest();
    WG_TEST_LCLFUNCTION_VERIFYCALL(rettest);

    EXPECT_TRUE(retval);
  }
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_return, OkIfGloballyScoped)
{
  try
  {
    ::boost::tuple<bool> retval = ::boost::make_tuple(false);

    WG_TEST_LCLFUNCTION(rettest, return (::boost::tuple<bool>) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(rettest);
      return ::boost::make_tuple(true);
    }
    WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
      ::boost::tuple<bool>, rettest());

    retval = rettest();
    WG_TEST_LCLFUNCTION_VERIFYCALL(rettest);

    EXPECT_TRUE(retval.get<0>());
  }
  WG_GTEST_CATCH
}

