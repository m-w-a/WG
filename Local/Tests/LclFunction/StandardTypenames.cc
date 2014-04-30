#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
#include <boost/type_traits/is_same.hpp>

TEST(wg_lclfunction_standardtypenames, VoidResultType)
{
  try
  {
    WG_LCLFUNCTION(noop, void)
    {
      EXPECT_TRUE(( ::boost::is_same<void (), function_type>::value ));
      EXPECT_TRUE(( ::boost::is_same<void, result_type>::value ));
    }WG_LCLFUNCTION_END;
  }
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_standardtypenames, IntResultType)
{
  try
  {
    WG_LCLFUNCTION(noop, return (int) )
    {
      EXPECT_TRUE(( ::boost::is_same<int (), function_type>::value ));
      EXPECT_TRUE(( ::boost::is_same<int, result_type>::value ));
      return 0;
    }WG_LCLFUNCTION_END;
  }
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_standardtypenames, Arg1Type)
{
  try
  {
    WG_LCLFUNCTION(noop, params (char arg1) )
    {
      EXPECT_TRUE(( ::boost::is_same<void (char), function_type>::value ));
      EXPECT_TRUE(( ::boost::is_same<char, arg1_type>::value ));
    }WG_LCLFUNCTION_END;
}
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_standardtypenames, Arg3Type)
{
  try
  {
    WG_LCLFUNCTION(noop,
      params (char arg1) (int arg2) (long arg3) )
    {
      EXPECT_TRUE((
        ::boost::is_same<void (char, int, long), function_type>::value ));
      EXPECT_TRUE(( ::boost::is_same<char, arg1_type>::value ));
      EXPECT_TRUE(( ::boost::is_same<int, arg2_type>::value ));
      EXPECT_TRUE(( ::boost::is_same<long, arg3_type>::value ));
    }WG_LCLFUNCTION_END;
}
  WG_GTEST_CATCH
}
