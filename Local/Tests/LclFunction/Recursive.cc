#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
#include <WG/Local/Tests/Utils/Utils.hh>

TEST(wg_lclfunction_recursive, Fibonacci)
{
  try
  {
    int fib = 0;

    WG_LCLFUNCTION(calculateFibonacci,
      return (int) params (int const input) )
    {
      if(input > 1)
      {
        WG_TEST_ASSERT_ISCONST(input);
        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, input);

        return calculateFibonacci(input - 1) + calculateFibonacci(input - 2);
      }
      else return input;
    }
    WG_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
      int, calculateFibonacci(5));

    fib = calculateFibonacci(4);

    EXPECT_EQ(fib, 3);
  }
  WG_GTEST_CATCH
}
