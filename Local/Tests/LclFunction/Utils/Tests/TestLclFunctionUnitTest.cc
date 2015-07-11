#include <gtest/gtest.h>
#include <gtest/gtest-spi.h>
#include <WG/Local/Tests/LclFunction/Utils/TestLclFunction.hh>

TEST(wg_test_lclfunction, OkIfMarkedAndCalledAndVerified)
{
  WG_TEST_LCLFUNCTION(noop, void)
  {
    WG_TEST_LCLFUNCTION_MARKCALL(noop);
  }
  WG_TEST_LCLFUNCTION_END

  noop();
  WG_TEST_LCLFUNCTION_VERIFYCALL(noop);
}

TEST(wg_test_lclfunction, NotOkIfUnmarkedButCalledAndVerified)
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

TEST(wg_test_lclfunction, NotOkIfMarkedButNotcalledAndVerified)
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

TEST(wg_test_lclfunction, NotOkIfMarkedAndCalledButUnverified)
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

