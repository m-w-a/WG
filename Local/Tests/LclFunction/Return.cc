#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
#include <utility>

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

TEST(wg_lclfunction_return, OkIfPPEscaped)
{
  try
  {
    std::pair<bool, int> retval = std::make_pair(false, 0);

    WG_LCLFUNCTION
    (rettest, return (ppescape((std::pair<bool, int>))) )
    {
      return std::make_pair(true, 1);
    }
    WG_LCLFUNCTION_END;

    retval = rettest();

    EXPECT_TRUE(retval.first);
  }
  WG_GTEST_CATCH
}

