#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/LclFunction/Utils/TestLclFunction.hh>
#include <WG/Local/Tests/Utils/Utils.hh>

TEST(wg_lclfunction_recursive, Fibonacci)
{
  try
  {
    int fib = 0;

    WG_TEST_LCLFUNCTION(calculateFibonacci,
      return (int) params (int const input) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(calculateFibonacci);

      if(input > 1)
      {
        WG_TEST_ASSERT_ISCONST(input);
        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, input);

        return calculateFibonacci(input - 1) + calculateFibonacci(input - 2);
      }
      else return input;
    }
    WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
      WG_LCLFUNCTION_TYPENAME(calculateFibonacci),
      calculateFibonacci);
    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
      int, calculateFibonacci(5));

    fib = calculateFibonacci(4);
    WG_TEST_LCLFUNCTION_VERIFYCALL(calculateFibonacci);

    EXPECT_EQ(fib, 3);
  }
  WG_GTEST_CATCH
}
