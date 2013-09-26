#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
#include <boost/function.hpp>

namespace
{
template <typename T>
struct CopyAssignment
{
  static void run()
  {
    WG_LCLFUNCTION_TPL(square, return (T) params ((T) x) )
    {
      return x * x;
    }WG_LCLFUNCTION_END;

    boost::function<T (T)> f = square;

    EXPECT_EQ(16, f(4));
  }
};
}
TEST(wg_lclfunction_boost_function_tpl, CopyAssignment)
{
  try
  {
    CopyAssignment<int>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct ConstRefAssignment
{
  static void run()
  {
    WG_LCLFUNCTION_TPL(square, return (T) params ((T) x) )
    {
      return x * x;
    }WG_LCLFUNCTION_END;

    boost::function<T (T)> f = boost::cref(square);

    EXPECT_EQ(16, f(4));
  }
};
}
TEST(wg_lclfunction_boost_function_tpl, ConstRefAssignment)
{
  try
  {
    ConstRefAssignment<int>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct ReturnFromFunction
{
  typedef boost::function<T (T)> square_type;
  static square_type run()
  {
    WG_LCLFUNCTION_TPL(square, return(T) params((T) x) )
    {
      return x * x;
    }WG_LCLFUNCTION_END;

    return square;
  }
};
}
TEST(wg_lclfunction_boost_function_tpl, ReturnFromFunction)
{
  try
  {
    ReturnFromFunction<int>::square_type square =
      ReturnFromFunction<int>::run();

    EXPECT_EQ(16, square(4));
  }
  WG_GTEST_CATCH
}
