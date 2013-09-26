#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
#include <boost/function.hpp>

TEST(wg_lclfunction_boost_function, CopyAssignment)
{
  try
  {
    WG_LCLFUNCTION(square, return (int) params ((int) x) )
    {
      return x * x;
    }WG_LCLFUNCTION_END;

    boost::function<int(int)> f = square;

    EXPECT_EQ(16, f(4));
  }
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_boost_function, ConstRefAssignment)
{
  try
  {
    WG_LCLFUNCTION(square, return (int) params ((int) x) )
    {
      return x * x;
    }WG_LCLFUNCTION_END;

    boost::function<int(int)> f = boost::cref(square);

    EXPECT_EQ(16, f(4));
  }
  WG_GTEST_CATCH
}

namespace
{
struct ReturnFromFunction
{
  typedef boost::function<int(int)> square_type;
  static square_type run()
  {
    WG_LCLFUNCTION(square, return(int) params((int) x) )
    {
      return x * x;
    }WG_LCLFUNCTION_END;

    return square;
  }
};
}
TEST(wg_lclfunction_boost_function, ReturnFromFunction)
{
  try
  {
    ReturnFromFunction::square_type square = ReturnFromFunction::run();

    EXPECT_EQ(16, square(4));
  }
  WG_GTEST_CATCH
}
