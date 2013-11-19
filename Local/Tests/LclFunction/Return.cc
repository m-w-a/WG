#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
#include <boost/tuple/tuple.hpp>

TEST(wg_lclfunction_return, OkIfSpecified)
{
  try
  {
    bool retval = false;

    WG_LCLFUNCTION(rettest, return (int) )
    {
      return 1;
    }
    WG_LCLFUNCTION_END;

    retval = rettest();

    EXPECT_TRUE(retval);
  }
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_return, OkIfGloballyScoped)
{
  try
  {
    ::boost::tuple<bool> retval = ::boost::make_tuple(false);

    WG_LCLFUNCTION
    (rettest, return (::boost::tuple<bool>) )
    {
      return ::boost::make_tuple(true);
    }
    WG_LCLFUNCTION_END;

    retval = rettest();

    EXPECT_TRUE(retval.get<0>());
  }
  WG_GTEST_CATCH
}

