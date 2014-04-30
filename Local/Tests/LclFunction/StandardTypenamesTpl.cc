#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
#include <boost/type_traits/is_same.hpp>

namespace
{
template <typename T>
struct VoidResultType
{
  static void run()
  {
    WG_LCLFUNCTION_TPL(noop, return (T) )
    {
      EXPECT_TRUE(( boost::is_same<T, result_type>::value ));
    }WG_LCLFUNCTION_END;
  }
};
}
TEST(wg_lclfunction_standardtypenames_tpl, VoidResultType)
{
  try
  {
    VoidResultType<void>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct IntResultType
{
  static void run()
  {
    WG_LCLFUNCTION_TPL(noop, return (T) )
    {
      EXPECT_TRUE(( boost::is_same<T, result_type>::value ));

      return T();
    }WG_LCLFUNCTION_END;
  }
};
}
TEST(wg_lclfunction_standardtypenames_tpl, IntResultType)
{
  try
  {
    IntResultType<int>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct Arg1Type
{
  static void run()
  {
    WG_LCLFUNCTION_TPL(noop, params (T arg1) )
    {
      EXPECT_TRUE(( boost::is_same<T, arg1_type>::value ));
    }WG_LCLFUNCTION_END;
  }
};
}
TEST(wg_lclfunction_standardtypenames_tpl, Arg1Type)
{
  try
  {
    Arg1Type<char>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T1, typename T2, typename T3>
struct Arg3Type
{
  static void run()
  {
    WG_LCLFUNCTION_TPL(noop,
      params (T1 arg1) (T2 arg2) (T3 arg3) )
    {
      EXPECT_TRUE(( boost::is_same<T1, arg1_type>::value ));
      EXPECT_TRUE(( boost::is_same<T2, arg2_type>::value ));
      EXPECT_TRUE(( boost::is_same<T3, arg3_type>::value ));
    }WG_LCLFUNCTION_END;
  }
};
}
TEST(wg_lclfunction_standardtypenames_tpl, Arg3Type)
{
  try
  {
    Arg3Type<char, int, long>::run();
  }
  WG_GTEST_CATCH
}
