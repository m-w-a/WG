#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
#include <algorithm>
#include <vector>

TEST(wg_lclfunction_astemplateparameterarg, StdForEach)
{
  try
  {
    int sum = 0;

    WG_LCLFUNCTION
    (accumulate,
      params ((int const) datum)
      varbind (ref sum)
      varset (runningOffset, 0) )
    {
      sum += runningOffset + datum;
      ++runningOffset;
    }WG_LCLFUNCTION_END;

    int const dataCount = 5;
    int data[dataCount] = { 0, 1, 2, 3, 4 };

    EXPECT_EQ(20, sum);
  }
  WG_GTEST_CATCH
}
