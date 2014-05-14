#include <gtest/gtest.h>
#include <gtest/gtest-spi.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/LclFunction/Utils/TestLclFunction.hh>

namespace
{
struct ignored;
};

namespace
{
template <typename T>
struct OkIfMarkedAndCalledAndVerified
{
  static void run()
  {
    WG_TEST_LCLFUNCTION_TPL(noop, void)
    {
      WG_TEST_LCLFUNCTION_MARKCALL(noop);
    }
    WG_TEST_LCLFUNCTION_END

    noop();
    WG_TEST_LCLFUNCTION_VERIFYCALL(noop);
  }
};
}
TEST(wg_test_lclfunction_tpl, OkIfMarkedAndCalledAndVerified)
{
  try
  {
    OkIfMarkedAndCalledAndVerified<ignored>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct NotOkIfUnmarkedButCalledAndVerified
{
  static void run()
  {
    WG_TEST_LCLFUNCTION_TPL(noop, void)
    {
      //WG_TEST_LCLFUNCTION_MARKCALL(noop);
    }
    WG_TEST_LCLFUNCTION_END

    noop();
    EXPECT_NONFATAL_FAILURE(
      WG_TEST_LCLFUNCTION_VERIFYCALL(noop),
      "uncalled or unmarked local function: ");
  }
};
}
TEST(wg_test_lclfunction_tpl, NotOkIfUnmarkedButCalledAndVerified)
{
  try
  {
    NotOkIfUnmarkedButCalledAndVerified<ignored>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct NotOkIfMarkedButNotcalledAndVerified
{
  static void run()
  {
    WG_TEST_LCLFUNCTION_TPL(noop, void)
    {
      WG_TEST_LCLFUNCTION_MARKCALL(noop);
    }
    WG_TEST_LCLFUNCTION_END

    //noop();
    EXPECT_NONFATAL_FAILURE(
      WG_TEST_LCLFUNCTION_VERIFYCALL(noop),
      "uncalled or unmarked local function: ");
  }
};
}
TEST(wg_test_lclfunction_tpl, NotOkIfMarkedButNotcalledAndVerified)
{
  try
  {
    NotOkIfMarkedButNotcalledAndVerified<ignored>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct NotOkIfMarkedAndCalledButUnverified
{
  static void run()
  {
    EXPECT_NONFATAL_FAILURE(
      WG_TEST_LCLFUNCTION_TPL(noop, void) \
      { \
        WG_TEST_LCLFUNCTION_MARKCALL(noop); \
      } \
      WG_TEST_LCLFUNCTION_END \
      \
      noop(); \
      /*WG_TEST_LCLFUNCTION_VERIFYCALL(noop); */ ,
      "unverified local function");
  }
};
}
TEST(wg_test_lclfunction_tpl, NotOkIfMarkedAndCalledButUnverified)
{
  try
  {
    NotOkIfMarkedAndCalledButUnverified<ignored>::run();
  }
  WG_GTEST_CATCH
}
