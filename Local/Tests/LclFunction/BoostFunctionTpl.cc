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

namespace
{
template <typename T>
struct OkIfCopyAssigned
{
  static void run()
  {
    WG_LCLFUNCTION_TPL(square, return (T) params (T x) )
    {
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T, x);

      return x * x;
    }WG_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
      WG_LCLFUNCTION_TYPENAME(square),
      square);
    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T, square(3));

    ::boost::function<T (T)> f = square;

    EXPECT_EQ(16, f(4));
  }
};
}
TEST(wg_lclfunction_boost_function_tpl, OkIfCopyAssigned)
{
  try
  {
    OkIfCopyAssigned<int>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct OkIfConstRefAssigned
{
  static void run()
  {
    WG_LCLFUNCTION_TPL(square, return (T) params (T x) )
    {
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T, x);

      return x * x;
    }WG_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
      WG_LCLFUNCTION_TYPENAME(square),
      square);
    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T, square(3));

    ::boost::function<T (T)> f = ::boost::cref(square);

    EXPECT_EQ(16, f(4));
  }
};
}
TEST(wg_lclfunction_boost_function_tpl, OkIfConstRefAssigned)
{
  try
  {
    OkIfConstRefAssigned<int>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct OkIfReturnedFromFunction
{
  typedef ::boost::function<T (T)> square_type;
  static square_type run()
  {
    WG_LCLFUNCTION_TPL(square, return(T) params(T x) )
    {
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T, x);

      return x * x;
    }WG_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
      WG_LCLFUNCTION_TYPENAME(square),
      square);
    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T, square(3));

    return square;
  }
};
}
TEST(wg_lclfunction_boost_function_tpl, OkIfReturnedFromFunction)
{
  try
  {
    OkIfReturnedFromFunction<int>::square_type square =
      OkIfReturnedFromFunction<int>::run();

    EXPECT_EQ(16, square(4));
  }
  WG_GTEST_CATCH
}
