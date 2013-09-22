#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
#include <utility>

TEST(wg_lclfunction_params, OkIf1ArgPassedByValue)
{
  try
  {
    int value = 10;

    WG_LCLFUNCTION(checkValue, params ((int) value) )
    {
      ++value;
      EXPECT_EQ(11, value);
    }WG_LCLFUNCTION_END;

    checkValue(value);

    EXPECT_EQ(10, value);
  }
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_params, OkIf1ArgPassedByRef)
{
  try
  {
    int value = 10;
    WG_LCLFUNCTION(checkValue, params ((int &) value) )
    {
      ++value;
      EXPECT_EQ(11, value);
    }WG_LCLFUNCTION_END;

    checkValue(value);

    EXPECT_EQ(11, value);
  }
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_params, OkIf1ArgPassedByConstRef)
{
  try
  {
    int value = 10;
    WG_LCLFUNCTION
    (checkValue,
      params ((int const &) value) )
    {
      EXPECT_EQ(10, value);
    }WG_LCLFUNCTION_END;

    checkValue(value);
  }
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_params, OkIfPPEscaped1ArgUsed)
{
  try
  {
    std::pair<bool, int> wasCalled = std::make_pair(false, 0);

    WG_LCLFUNCTION
    (checkValue,
      params (ppescape((std::pair<bool, int>)) wasCalled) )
    {
      EXPECT_FALSE(wasCalled.first);
      EXPECT_EQ(0, wasCalled.second);
    }WG_LCLFUNCTION_END;

    checkValue(wasCalled);
  }
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_params, OkIf3ArgsUsed)
{
  try
  {
    int force = 0;
    int const mass = 10;
    int const velocity = 2;

    WG_LCLFUNCTION
    (calculateForce,
      params ((int &) force) ((int const) mass) ((int const) velocity) )
    {
      force = mass * velocity;
    }WG_LCLFUNCTION_END;

    calculateForce(force, mass, velocity);

    EXPECT_EQ(20, force);
  }
  WG_GTEST_CATCH
}
