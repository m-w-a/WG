#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
#include <algorithm>
#include <vector>
#include <WG/Local/Tests/TestHelper.hh>

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
      WG_TESTHELPER_ASSERT_ISCONST(datum);
      WG_TESTHELPER_ASSERT_ISNOTCONST(sum);
      WG_TESTHELPER_ASSERT_ISNOTCONST(runningOffset);

      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, datum);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, sum);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, runningOffset);

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
