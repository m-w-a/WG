#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <algorithm>
#include <vector>
#include <WG/Local/Tests/Utils/Utils.hh>

// Use release macros since:
//   1) these tests aren't intended to exercise the declared lclfunction obj,
//      rather they are intended to exercise the std::for_each copies.
//   2) all the tested lclfunctions have verifiable side-effects that when
//      not invoked will result in test failure.
#include <WG/Local/LclFunction.hh>

TEST(wg_lclfunction_astemplateparameterarg, StdForEach)
{
  try
  {
    int sum = 0;

    WG_LCLFUNCTION
    (accumulate,
      params (int const datum)
      varbind (ref sum)
      varset (runningOffset, 0) )
    {
      WG_TEST_ASSERT_ISCONST(datum);
      WG_TEST_ASSERT_ISNOTCONST(sum);
      WG_TEST_ASSERT_ISNOTCONST(runningOffset);

      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, datum);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, sum);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, runningOffset);

      sum += runningOffset + datum;
      ++runningOffset;
    }WG_LCLFUNCTION_END;

    int const dataCount = 5;
    int data[dataCount] = { 0, 1, 2, 3, 4 };

    std::for_each(data, data + dataCount, accumulate);

    EXPECT_EQ(20, sum);
  }
  WG_GTEST_CATCH
}
