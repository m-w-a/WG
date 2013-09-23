#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>

namespace
{
template <typename T>
struct Fibonacci
{
  static void run()
  {
    T fib = 0;

    WG_LCLFUNCTION_TPL
    (calculateFibonacci, return (T) params ((int const) input) )
    {
      if(input > 1)
      {
        return calculateFibonacci(input - 1) + calculateFibonacci(input - 2);
      }
      else return input;
    }
    WG_LCLFUNCTION_END;

    fib = calculateFibonacci(4);

    EXPECT_EQ(fib, 3);
  }
};
}
TEST(wg_lclfunction_recursive_tpl, Fibonacci)
{
  try
  {
    Fibonacci<int>::run();
  }
  WG_GTEST_CATCH
}
