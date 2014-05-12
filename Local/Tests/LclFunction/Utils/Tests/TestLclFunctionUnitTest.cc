#include <gtest/gtest.h>
#include <gtest/gtest-spi.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/LclFunction/Utils/TestLclFunction.hh>

TEST(wg_test_lclfunction, OkIfMarkedAndCalledAndVerified)
{
  try
  {
    WG_TEST_LCLFUNCTION(noop, void)
    {
      WG_TEST_LCLFUNCTION_MARKCALL(noop);
    }
    WG_TEST_LCLFUNCTION_END

    noop();
    WG_TEST_LCLFUNCTION_VERIFYCALL(noop);
  }
  WG_GTEST_CATCH
}

TEST(wg_test_lclfunction, NotOkIfUnmarkedButCalledAndVerified)
{
  try
  {
    WG_TEST_LCLFUNCTION(noop, void)
    {
      //WG_TEST_LCLFUNCTION_MARKCALL(noop);
    }
    WG_TEST_LCLFUNCTION_END

    noop();
    EXPECT_NONFATAL_FAILURE(
      WG_TEST_LCLFUNCTION_VERIFYCALL(noop),
      "uncalled or unmarked local function: ");
  }
  WG_GTEST_CATCH
}

TEST(wg_test_lclfunction, NotOkIfMarkedButNotcalledAndVerified)
{
  try
  {
    WG_TEST_LCLFUNCTION(noop, void)
    {
      WG_TEST_LCLFUNCTION_MARKCALL(noop);
    }
    WG_TEST_LCLFUNCTION_END

    //noop();
    EXPECT_NONFATAL_FAILURE(
      WG_TEST_LCLFUNCTION_VERIFYCALL(noop),
      "uncalled or unmarked local function: ");
  }
  WG_GTEST_CATCH
}

TEST(wg_test_lclfunction, NotOkIfMarkedAndCalledButUnverified)
{
  try
  {
    EXPECT_NONFATAL_FAILURE(
      WG_TEST_LCLFUNCTION(noop, void) \
      { \
        WG_TEST_LCLFUNCTION_MARKCALL(noop); \
      } \
      WG_TEST_LCLFUNCTION_END \
      \
      noop(); \
      /*WG_TEST_LCLFUNCTION_VERIFYCALL(noop); */ ,
      "unverified local function");
  }
  WG_GTEST_CATCH
}

