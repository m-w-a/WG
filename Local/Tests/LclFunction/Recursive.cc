#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>

TEST(wg_lclfunction_recursive, Fibonacci)
{
  try
  {
    int fib = 0;

    WG_LCLFUNCTION
    (calculateFibonacci, return (int) params ((int const) input) )
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
  WG_GTEST_CATCH
}
