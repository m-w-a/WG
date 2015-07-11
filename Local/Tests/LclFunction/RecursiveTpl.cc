#include <gtest/gtest.h>
#include <WG/Local/Tests/LclFunction/Utils/TestLclFunction.hh>
#include <WG/Local/Tests/Utils/Utils.hh>

namespace
{
template <typename T>
struct Fibonacci
{
  static void run()
  {
    T fib = 0;

    WG_TEST_LCLFUNCTION_TPL(calculateFibonacci,
      return (T) params (T const input) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(calculateFibonacci);

      if(input > 1)
      {
        WG_TEST_ASSERT_ISCONST_TPL(input);
        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T, input);

        return calculateFibonacci(input - 1) + calculateFibonacci(input - 2);
      }
      else return input;
    }
    WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
      WG_LCLFUNCTION_TYPENAME(calculateFibonacci),
      calculateFibonacci);
    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
      T, calculateFibonacci(5));

    fib = calculateFibonacci(4);
    WG_TEST_LCLFUNCTION_VERIFYCALL(calculateFibonacci);

    EXPECT_EQ(fib, 3);
  }
};
}
TEST(wg_lclfunction_recursive_tpl, Fibonacci)
{
  Fibonacci<int>::run();
}
