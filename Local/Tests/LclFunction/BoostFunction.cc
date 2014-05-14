#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <boost/function.hpp>
#include <WG/Local/Tests/Utils/Utils.hh>

// Use release macros since:
//   1) these tests aren't intended to exercise the declared lclfunction,
//      rather they are intended to exercise their Boost.Function copies.
//   2) all the tested lclfunctions have verifiable side-effects that when
//      not invoked will result in test failure.
#include <WG/Local/LclFunction.hh>

TEST(wg_lclfunction_boost_function, OkIfCopyAssigned)
{
  try
  {
    WG_LCLFUNCTION(square, return (int) params (int x) )
    {
      WG_TEST_ASSERT_ISNOTCONST(x);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, x);

      return x * x;
    }WG_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, square(3));

    ::boost::function<int(int)> f = square;

    EXPECT_EQ(16, f(4));
  }
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_boost_function, OkayIfConstRefAssigned)
{
  try
  {
    WG_LCLFUNCTION(square, return (int) params (int x) )
    {
      WG_TEST_ASSERT_ISNOTCONST(x);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, x);

      return x * x;
    }WG_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, square(3));

    ::boost::function<int(int)> f = ::boost::cref(square);

    EXPECT_EQ(16, f(4));
  }
  WG_GTEST_CATCH
}

namespace
{
struct OkIfReturnedFromFunction
{
  typedef ::boost::function<int(int)> square_type;
  static square_type run()
  {
    WG_LCLFUNCTION(square, return(int) params(int x) )
    {
      WG_TEST_ASSERT_ISNOTCONST(x);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, x);

      return x * x;
    }WG_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, square(3));

    return square;
  }
};
}
TEST(wg_lclfunction_boost_function, OkIfReturnedFromFunction)
{
  try
  {
    OkIfReturnedFromFunction::square_type square = OkIfReturnedFromFunction::run();

    EXPECT_EQ(16, square(4));
  }
  WG_GTEST_CATCH
}
