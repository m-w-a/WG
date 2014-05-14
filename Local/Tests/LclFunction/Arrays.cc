#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/LclFunction/Utils/TestLclFunction.hh>
#include <WG/Local/Tests/Utils/Utils.hh>
#include <boost/type_traits/is_array.hpp>
#include <boost/typeof/typeof.hpp>
#include <cstddef>
#include <cstring>

namespace
{

typedef int Arr[2][3];

Arr const arrPrototype =
  {
    {0, 1, 2},
    {3, 4, 5}
  };

}

TEST(wg_lclfunction_arrays, BindByValue)
{
  try
  {
    Arr arr;
    std::memcpy(arr, arrPrototype, sizeof(arr));

    int const origArr_1_1 = arr[1][1];
    WG_TEST_LCLFUNCTION(arrBindByValue, varbind (arr) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(arrBindByValue);

      WG_TEST_ASSERT_ISNOTCONST(arr);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(Arr, arr);

      EXPECT_TRUE( ::wg::lcl::test::equal(arr, arrPrototype) );

      arr[1][1] += 10;
    }
    WG_TEST_LCLFUNCTION_END;

    arrBindByValue();
    WG_TEST_LCLFUNCTION_VERIFYCALL(arrBindByValue);

    EXPECT_EQ(origArr_1_1, arr[1][1]);
  }
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_arrays, BindByRef)
{
  try
  {
    Arr arr;
    std::memcpy(arr, arrPrototype, sizeof(arr));

    int const origArr_1_1 = arr[1][1];
    WG_TEST_LCLFUNCTION(arrBindByRef, varbind (ref arr) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(arrBindByRef);

      WG_TEST_ASSERT_ISNOTCONST(arr);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(Arr, arr);

      EXPECT_TRUE( ::wg::lcl::test::equal(arr, arrPrototype) );

      arr[1][1] += 10;
    }
    WG_TEST_LCLFUNCTION_END;

    arrBindByRef();
    WG_TEST_LCLFUNCTION_VERIFYCALL(arrBindByRef);

    EXPECT_NE(origArr_1_1, arr[1][1]);
  }
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_arrays, SetByValue)
{
  try
  {
    Arr arr;
    std::memcpy(arr, arrPrototype, sizeof(arr));

    int const origArr_1_1 = arr[1][1];
    WG_TEST_LCLFUNCTION(arrSetByValue, varset (someArr, arr) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(arrSetByValue);

      WG_TEST_ASSERT_ISNOTCONST(arr);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(Arr, arr);

      EXPECT_TRUE( ::wg::lcl::test::equal(someArr, arrPrototype) );

      someArr[1][1] += 10;
    }
    WG_TEST_LCLFUNCTION_END;

    arrSetByValue();
    WG_TEST_LCLFUNCTION_VERIFYCALL(arrSetByValue);

    EXPECT_EQ(origArr_1_1, arr[1][1]);
  }
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_arrays, SetByRef)
{
  try
  {
    Arr arr;
    std::memcpy(arr, arrPrototype, sizeof(arr));

    int const origArr_1_1 = arr[1][1];
    WG_TEST_LCLFUNCTION(arrSetByRef, varset (ref someArr, arr) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(arrSetByRef);

      WG_TEST_ASSERT_ISNOTCONST(arr);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(Arr, arr);

      EXPECT_TRUE( ::wg::lcl::test::equal(someArr, arrPrototype) );

      someArr[1][1] += 10;
    }
    WG_TEST_LCLFUNCTION_END;

    arrSetByRef();
    WG_TEST_LCLFUNCTION_VERIFYCALL(arrSetByRef);

    EXPECT_NE(origArr_1_1, arr[1][1]);
  }
  WG_GTEST_CATCH
}
