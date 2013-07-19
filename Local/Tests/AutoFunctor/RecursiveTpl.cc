#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>

namespace
{
template <typename T>
struct Fibonacci
{
  static void run()
  {
    T fib = 0;

    WG_AUTOFUNCTOR_TPL
    (calculateFibonacci,
      assignto (fib)
      return (T)
      paramset ((T) input, 4) )
    {
      if(input > 1)
      {
        return calculateFibonacci(input - 1) + calculateFibonacci(input - 2);
      }
      else return input;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(fib, 3);
  }
};
}
TEST(wg_autofunctor_recursivetpl, Fibonacci)
{
  try
  {
    Fibonacci<int>::run();
  }
  WG_GTEST_CATCH
}
