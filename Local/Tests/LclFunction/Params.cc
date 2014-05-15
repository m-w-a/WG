#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/LclFunction/Utils/TestLclFunction.hh>
#include <boost/tuple/tuple.hpp>
#include <WG/Local/Tests/Utils/Utils.hh>

TEST(wg_lclfunction_params, OkIf1ArgPassedByValue)
{
  try
  {
    int value = 10;

    WG_TEST_LCLFUNCTION(checkValue, params (int value) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(checkValue);

      WG_TEST_ASSERT_ISNOTCONST(value);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, value);

      ++value;
      EXPECT_EQ(11, value);
    }WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
      WG_LCLFUNCTION_TYPENAME(checkValue),
      checkValue);

    checkValue(value);
    WG_TEST_LCLFUNCTION_VERIFYCALL(checkValue);

    EXPECT_EQ(10, value);
  }
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_params, OkIf1ArgPassedByRef)
{
  try
  {
    int value = 10;
    WG_TEST_LCLFUNCTION(checkValue, params (int & value) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(checkValue);

      WG_TEST_ASSERT_ISNOTCONST(value);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, value);

      ++value;
      EXPECT_EQ(11, value);
    }WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
      WG_LCLFUNCTION_TYPENAME(checkValue),
      checkValue);

    checkValue(value);
    WG_TEST_LCLFUNCTION_VERIFYCALL(checkValue);

    EXPECT_EQ(11, value);
  }
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_params, OkIf1ArgPassedByConstRef)
{
  try
  {
    int value = 10;
    WG_TEST_LCLFUNCTION
    (checkValue,
      params (int const & value) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(checkValue);

      WG_TEST_ASSERT_ISCONST(value);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, value);

      EXPECT_EQ(11, value);
    }WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
      WG_LCLFUNCTION_TYPENAME(checkValue),
      checkValue);

    ++value;
    checkValue(value);
    WG_TEST_LCLFUNCTION_VERIFYCALL(checkValue);
  }
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_params, OkIfGloballyScoped1ArgUsed)
{
  try
  {
    ::boost::tuple<bool> wasCalled = ::boost::make_tuple(false);

    WG_TEST_LCLFUNCTION
    (checkValue,
      params (::boost::tuple<bool> wasCalled) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(checkValue);

      WG_TEST_ASSERT_ISNOTCONST(wasCalled);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
        ::boost::tuple<bool>, wasCalled);

      EXPECT_FALSE(wasCalled.get<0>());
    }WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
      WG_LCLFUNCTION_TYPENAME(checkValue),
      checkValue);

    checkValue(wasCalled);
    WG_TEST_LCLFUNCTION_VERIFYCALL(checkValue);
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

    WG_TEST_LCLFUNCTION
    (calculateForce,
      params (int & force) (int const mass) (int const velocity) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(calculateForce);

      WG_TEST_ASSERT_ISNOTCONST(force);
      WG_TEST_ASSERT_ISCONST(mass);
      WG_TEST_ASSERT_ISCONST(velocity);

      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, force);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, mass);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, velocity);

      force = mass * velocity;
    }WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
      WG_LCLFUNCTION_TYPENAME(calculateForce),
      calculateForce);

    calculateForce(force, mass, velocity);
    WG_TEST_LCLFUNCTION_VERIFYCALL(calculateForce);

    EXPECT_EQ(20, force);
  }
  WG_GTEST_CATCH
}
