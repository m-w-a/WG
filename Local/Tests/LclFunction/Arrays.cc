#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
#include <WG/Local/Tests/TestHelper.hh>
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
    WG_LCLFUNCTION(arrBindByValue, varbind (arr) )
    {
      WG_TESTHELPER_ASSERT_ISNOTCONST(arr);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(Arr, arr);

      EXPECT_TRUE( ::wg::lcl::tests::equal(arr, arrPrototype) );

      arr[1][1] += 10;
    }
    WG_LCLFUNCTION_END;

    arrBindByValue();

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
    WG_LCLFUNCTION(arrBindByRef, varbind (ref arr) )
    {
      WG_TESTHELPER_ASSERT_ISNOTCONST(arr);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(Arr, arr);

      EXPECT_TRUE( ::wg::lcl::tests::equal(arr, arrPrototype) );

      arr[1][1] += 10;
    }
    WG_LCLFUNCTION_END;

    arrBindByRef();

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
    WG_LCLFUNCTION(arrSetByValue, varset (someArr, arr) )
    {
      WG_TESTHELPER_ASSERT_ISNOTCONST(arr);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(Arr, arr);

      EXPECT_TRUE( ::wg::lcl::tests::equal(someArr, arrPrototype) );

      someArr[1][1] += 10;
    }
    WG_LCLFUNCTION_END;

    arrSetByValue();

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
    WG_LCLFUNCTION(arrSetByRef, varset (ref someArr, arr) )
    {
      WG_TESTHELPER_ASSERT_ISNOTCONST(arr);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(Arr, arr);

      EXPECT_TRUE( ::wg::lcl::tests::equal(someArr, arrPrototype) );

      someArr[1][1] += 10;
    }
    WG_LCLFUNCTION_END;

    arrSetByRef();

    EXPECT_NE(origArr_1_1, arr[1][1]);
  }
  WG_GTEST_CATCH
}
