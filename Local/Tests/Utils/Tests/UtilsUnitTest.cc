#include <gtest/gtest.h>
#include <WG/Local/Tests/Utils/Utils.hh>

TEST(wg_tests_utils_equal, OkIfEqual)
{
  typedef int Arr2x3[2][3];

  Arr2x3 arr1 = { {0, 1, 2}, {3, 4, 5} };

  EXPECT_TRUE( ::wg::lcl::test::equal(arr1, arr1) );
}

TEST(wg_tests_utils_equal, OkIfNotEqual)
{
  typedef int Arr2x3[2][3];

  Arr2x3 arr1 = { {0, 1, 2}, {3, 4, 5} };
  Arr2x3 arr2 = { {0, 1, 2}, {3, 45, 5} };

  EXPECT_FALSE( ::wg::lcl::test::equal(arr1, arr2) );
}
