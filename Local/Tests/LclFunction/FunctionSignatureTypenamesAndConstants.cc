#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
#include <boost/type_traits/is_same.hpp>

TEST(wg_lclfunction_signaturetypenamesandconstants, VoidResultType)
{
  try
  {
    WG_LCLFUNCTION(noop, void)
    {
      EXPECT_TRUE(( ::boost::is_same<void (), function_type>::value ));
      EXPECT_EQ(0, arity);
      EXPECT_TRUE(( ::boost::is_same<void, result_type>::value ));
    }WG_LCLFUNCTION_END;

    noop();
  }
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_signaturetypenamesandconstants, IntResultType)
{
  try
  {
    WG_LCLFUNCTION(noop, return (int) )
    {
      EXPECT_TRUE(( ::boost::is_same<int (), function_type>::value ));
      EXPECT_EQ(0, arity);
      EXPECT_TRUE(( ::boost::is_same<int, result_type>::value ));

      return 0;
    }WG_LCLFUNCTION_END;

    (void)noop();
  }
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_signaturetypenamesandconstants, OneArg)
{
  try
  {
    WG_LCLFUNCTION(noop, params (char arg1) )
    {
      EXPECT_TRUE(( ::boost::is_same<void (char), function_type>::value ));
      EXPECT_EQ(1, arity);
      EXPECT_TRUE(( ::boost::is_same<void, result_type>::value ));
      EXPECT_TRUE(( ::boost::is_same<char, arg1_type>::value ));
    }WG_LCLFUNCTION_END;

    noop('c');
}
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_signaturetypenamesandconstants, ThreeArgs)
{
  try
  {
    WG_LCLFUNCTION(noop,
      params (char arg1) (int const arg2) (long const & arg3) )
    {
      EXPECT_TRUE((
        ::boost::is_same<void (char, int, long const &), function_type>::value ));
      EXPECT_EQ(3, arity);
      EXPECT_TRUE(( ::boost::is_same<void, result_type>::value ));
      EXPECT_TRUE(( ::boost::is_same<char, arg1_type>::value ));
      EXPECT_TRUE(( ::boost::is_same<int, arg2_type>::value ));
      EXPECT_TRUE(( ::boost::is_same<long const &, arg3_type>::value ));
    }WG_LCLFUNCTION_END;

    noop('a', 0, 1);
}
  WG_GTEST_CATCH
}
