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
      WG_TEST_ASSERT_ISCONST_TPL(datum);
      WG_TEST_ASSERT_ISNOTCONST_TPL(sum);
      WG_TEST_ASSERT_ISNOTCONST_TPL(runningOffset);

      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T, datum);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T, sum);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(int, runningOffset);

      sum += runningOffset + datum;
      ++runningOffset;
    }WG_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
      WG_LCLFUNCTION_TYPENAME(accumulate),
      accumulate);

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
