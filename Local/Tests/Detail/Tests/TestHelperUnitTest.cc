#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/TestHelper.hh>

TEST(wg_tests_testhelper_equal, OkIfEqual)
{
  try
  {
    typedef int Arr2x3[2][3];

    Arr2x3 arr1 = { {0, 1, 2}, {3, 4, 5} };

    EXPECT_TRUE( ::wg::local::tests::equal(arr1, arr1) );
  }
  WG_GTEST_CATCH
}

TEST(wg_tests_testhelper_equal, OkIfNotEqual)
{
  try
  {
    typedef int Arr2x3[2][3];

    Arr2x3 arr1 = { {0, 1, 2}, {3, 4, 5} };
    Arr2x3 arr2 = { {0, 1, 2}, {3, 45, 5} };

    EXPECT_FALSE( ::wg::local::tests::equal(arr1, arr2) );
  }
  WG_GTEST_CATCH
}
