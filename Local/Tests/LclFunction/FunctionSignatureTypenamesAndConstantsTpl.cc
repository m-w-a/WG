#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/LclFunction/Utils/TestLclFunction.hh>
#include <boost/type_traits/is_same.hpp>

namespace
{
template <typename T>
struct ResultType;

template <typename R>
struct ResultType<R ()>
{
  static void run()
  {
    WG_TEST_LCLFUNCTION_TPL(noop, return (R) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(noop);

      EXPECT_TRUE(( ::boost::is_same<R (), function_type>::value ));
      EXPECT_EQ(0, arity);
      EXPECT_TRUE(( ::boost::is_same<R, result_type>::value ));

      return R();
    }WG_TEST_LCLFUNCTION_END;

    (void)noop();
    WG_TEST_LCLFUNCTION_VERIFYCALL(noop);
  }
};
}

TEST(wg_lclfunction_signaturetypenamesandconstants_tpl, VoidResultType)
{
  try
  {
    ResultType<void ()>::run();
  }
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_signaturetypenamesandconstants_tpl, IntResultType)
{
  try
  {
    ResultType<int ()>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct Arg1Type;

template <typename R, typename T1>
struct Arg1Type<R (T1)>
{
  static void run()
  {
    WG_TEST_LCLFUNCTION_TPL(noop, params (T1 arg1) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(noop);

      EXPECT_TRUE(( ::boost::is_same<R (T1), function_type>::value ));
      EXPECT_EQ(1, arity);
      EXPECT_TRUE(( ::boost::is_same<R, result_type>::value ));
      EXPECT_TRUE(( ::boost::is_same<T1, arg1_type>::value ));
    }WG_TEST_LCLFUNCTION_END;

    noop('c');
    WG_TEST_LCLFUNCTION_VERIFYCALL(noop);
  }
};
}
TEST(wg_lclfunction_signaturetypenamesandconstants_tpl, Arg1Type)
{
  try
  {
    Arg1Type<void (char)>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct Arg3Type;

template <typename R, typename T1, typename T2, typename T3>
struct Arg3Type<R (T1, T2, T3)>
{
  static void run()
  {
    WG_TEST_LCLFUNCTION_TPL(noop,
      params (T1 arg1) (T2 arg2) (T3 arg3) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(noop);

      EXPECT_TRUE((
        ::boost::is_same<R (T1, T2, T3), function_type>::value ));
      EXPECT_EQ(3, arity);
      EXPECT_TRUE(( ::boost::is_same<R, result_type>::value ));
      EXPECT_TRUE(( ::boost::is_same<T1, arg1_type>::value ));
      EXPECT_TRUE(( ::boost::is_same<T2, arg2_type>::value ));
      EXPECT_TRUE(( ::boost::is_same<T3, arg3_type>::value ));
    }WG_TEST_LCLFUNCTION_END;

    noop('a', 0, 1);
    WG_TEST_LCLFUNCTION_VERIFYCALL(noop);
  }
};
}
TEST(wg_lclfunction_signaturetypenamesandconstants_tpl, Arg3Type)
{
  try
  {
    Arg3Type<void (char, int const, long const &)>::run();
  }
  WG_GTEST_CATCH
}
