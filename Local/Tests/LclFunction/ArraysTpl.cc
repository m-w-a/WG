#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
#include <WG/Local/Tests/Utils/Utils.hh>
#include <boost/type_traits/is_array.hpp>
#include <boost/typeof/typeof.hpp>
#include <cstddef>
#include <cstring>

namespace
{

template <typename T>
struct Arr
{
  typedef T Type[2][3];
};

typedef int ElemType;
Arr<ElemType>::Type const arrPrototype =
  {
    {0, 1, 2},
    {3, 4, 5}
  };

}

namespace
{
template <typename T>
struct BindByValue
{
  static void run()
  {
    typedef typename Arr<T>::Type ArrType;
    ArrType arr;
    std::memcpy(arr, arrPrototype, sizeof(arr));

    T const origArr_1_1 = arr[1][1];
    WG_LCLFUNCTION_TPL(arrBindByValue, varbind (arr) )
    {
      WG_TEST_ASSERT_ISNOTCONST_TPL(arr);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(ArrType, arr);

      EXPECT_TRUE( ::wg::lcl::test::equal(arr, arrPrototype) );

      arr[1][1] += 10;
    }
    WG_LCLFUNCTION_END;

    arrBindByValue();

    EXPECT_EQ(origArr_1_1, arr[1][1]);
  }
};
}
TEST(wg_lclfunction_arrays_tpl, BindByValue)
{
  try
  {
    BindByValue<ElemType>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct BindByRef
{
  static void run()
  {
    typedef typename Arr<T>::Type ArrType;
    ArrType arr;
    std::memcpy(arr, arrPrototype, sizeof(arr));

    T const origArr_1_1 = arr[1][1];
    WG_LCLFUNCTION_TPL(arrBindByRef, varbind (ref arr) )
    {
      WG_TEST_ASSERT_ISNOTCONST_TPL(arr);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(ArrType, arr);

      EXPECT_TRUE( ::wg::lcl::test::equal(arr, arrPrototype) );

      arr[1][1] += 10;
    }
    WG_LCLFUNCTION_END;

    arrBindByRef();

    EXPECT_NE(origArr_1_1, arr[1][1]);
  }
};
}
TEST(wg_lclfunction_arrays_tpl, BindByRef)
{
  try
  {
    BindByRef<ElemType>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct SetByValue
{
  static void run()
  {
    typedef typename Arr<T>::Type ArrType;
    ArrType arr;
    std::memcpy(arr, arrPrototype, sizeof(arr));

    T const origArr_1_1 = arr[1][1];
    WG_LCLFUNCTION_TPL(arrSetByValue, varset (someArr, arr) )
    {
      WG_TEST_ASSERT_ISNOTCONST_TPL(arr);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(ArrType, arr);

      EXPECT_TRUE( ::wg::lcl::test::equal(someArr, arrPrototype) );

      someArr[1][1] += 10;
    }
    WG_LCLFUNCTION_END;

    arrSetByValue();

    EXPECT_EQ(origArr_1_1, arr[1][1]);
  }
};
}
TEST(wg_lclfunction_arrays_tpl, SetByValue)
{
  try
  {
    SetByValue<ElemType>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct SetByRef
{
  static void run()
  {
    typedef typename Arr<T>::Type ArrType;
    ArrType arr;
    std::memcpy(arr, arrPrototype, sizeof(arr));

    T const origArr_1_1 = arr[1][1];
    WG_LCLFUNCTION_TPL(arrSetByRef, varset (ref someArr, arr) )
    {
      WG_TEST_ASSERT_ISNOTCONST_TPL(arr);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(ArrType, arr);

      EXPECT_TRUE( ::wg::lcl::test::equal(someArr, arrPrototype) );

      someArr[1][1] += 10;
    }
    WG_LCLFUNCTION_END;

    arrSetByRef();

    EXPECT_NE(origArr_1_1, arr[1][1]);
  }
};
}
TEST(wg_lclfunction_arrays_tpl, SetByRef)
{
  try
  {
    SetByRef<ElemType>::run();
  }
  WG_GTEST_CATCH
}
