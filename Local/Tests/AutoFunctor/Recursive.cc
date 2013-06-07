#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>

TEST(wg_autofunctor_recursive, fibonacci)
{
  try
  {
    int fib = 0;

    WG_AUTOFUNCTOR
    (calculateFibonacci,
      assignto ((int) fib)
      return (int)
      paramset ((int) input, 4) )
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
  WG_GTEST_CATCH
}

//TODO: ...
