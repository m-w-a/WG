#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
#include <WG/Local/Tests/TestHelper.hh>
#include <boost/type_traits/is_array.hpp>
#include <boost/typeof/typeof.hpp>
#include <cstddef>
#include <cstring>
#include <algorithm>

namespace
{

typedef int Arr[2][3];

Arr const arrPrototype =
  {
    {0, 1, 2},
    {3, 4, 5}
  };

bool isEqualToPrototype(Arr const & rhs)
{
  using namespace wg::local::tests;

  std::size_t const arrPrototypeCount =
    sizeof(arrPrototype) /
    sizeof(boost::remove_all_extents<BOOST_TYPEOF(arrPrototype)>::type);

  return std::equal(
    address_of_first_nonarray_elem(arrPrototype),
    address_of_first_nonarray_elem(arrPrototype) + arrPrototypeCount,
    address_of_first_nonarray_elem(rhs));
}

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
      EXPECT_TRUE(boost::is_array<BOOST_TYPEOF(arr)>::value);
      EXPECT_TRUE(isEqualToPrototype(arr));

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
      EXPECT_TRUE(boost::is_array<BOOST_TYPEOF(arr)>::value);
      EXPECT_TRUE(isEqualToPrototype(arr));

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
      EXPECT_TRUE(boost::is_array<BOOST_TYPEOF(someArr)>::value);
      EXPECT_TRUE(isEqualToPrototype(someArr));

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
      EXPECT_TRUE(boost::is_array<BOOST_TYPEOF(someArr)>::value);
      EXPECT_TRUE(isEqualToPrototype(someArr));

      someArr[1][1] += 10;
    }
    WG_LCLFUNCTION_END;

    arrSetByRef();

    EXPECT_NE(origArr_1_1, arr[1][1]);
  }
  WG_GTEST_CATCH
}
