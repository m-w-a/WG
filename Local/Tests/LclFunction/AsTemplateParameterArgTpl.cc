#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
#include <algorithm>
#include <vector>
#include <WG/Local/Tests/TestHelper.hh>

namespace
{
template <typename T>
struct StdForEach
{
  static void run()
  {
    T sum = 0;

    WG_LCLFUNCTION_TPL
    (accumulate,
      params (T const datum)
      varbind (ref sum)
      varset (runningOffset, 0) )
    {
      WG_TESTHELPER_ASSERT_ISCONST_TPL(datum);
      WG_TESTHELPER_ASSERT_ISNOTCONST_TPL(sum);
      WG_TESTHELPER_ASSERT_ISNOTCONST_TPL(runningOffset);

      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T, datum);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T, sum);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(int, runningOffset);

      sum += runningOffset + datum;
      ++runningOffset;
    }WG_LCLFUNCTION_END;

    T const dataCount = 5;
    T data[dataCount] = { 0, 1, 2, 3, 4 };

    std::for_each(data, data + dataCount, accumulate);

    EXPECT_EQ(20, sum);
  }
};
}
TEST(wg_lclfunction_astemplateparameterarg_tpl, StdForEach)
{
  try
  {
    StdForEach<int>::run();
  }
  WG_GTEST_CATCH
}
