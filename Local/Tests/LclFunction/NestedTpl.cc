#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/LclFunction/Utils/TestLclFunction.hh>
#include <WG/Local/Tests/Utils/Utils.hh>

namespace
{
template <typename T>
struct OneLevel
{
  static void run()
  {
    T count = 0;

    WG_TEST_LCLFUNCTION_TPL(oneStep, varbind (ref count) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(oneStep);

      WG_TEST_ASSERT_ISNOTCONST_TPL(count);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T, count);

      ++count;

      WG_TEST_LCLFUNCTION_TPL(twoStep, varbind (ref count) )
      {
        WG_TEST_LCLFUNCTION_MARKCALL(twoStep);

        WG_TEST_ASSERT_ISNOTCONST_TPL(count);
        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T, count);

        count += 2;
      }
      WG_TEST_LCLFUNCTION_END;

      twoStep();
      WG_TEST_LCLFUNCTION_VERIFYCALL(twoStep);
    }
    WG_TEST_LCLFUNCTION_END;

    oneStep();
    WG_TEST_LCLFUNCTION_VERIFYCALL(oneStep);

    EXPECT_EQ(count, 3);
  }
};
}
TEST(wg_lclfunction_nested_tpl, OneLevel)
{
  try
  {
    OneLevel<int>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct TwoLevel
{
  static void run()
  {
    T count = 0;

    WG_TEST_LCLFUNCTION_TPL(oneStep, varbind (ref count) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(oneStep);

      WG_TEST_ASSERT_ISNOTCONST_TPL(count);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T, count);

      ++count;

      WG_TEST_LCLFUNCTION_TPL(twoStep, params (int & count) )
      {
        WG_TEST_LCLFUNCTION_MARKCALL(twoStep);

        WG_TEST_ASSERT_ISNOTCONST_TPL(count);
        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(int, count);

        count += 2;

        WG_TEST_LCLFUNCTION_TPL(threeStep, varset (ref var, count) )
        {
          WG_TEST_LCLFUNCTION_MARKCALL(threeStep);

          WG_TEST_ASSERT_ISNOTCONST_TPL(count);
          WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(int, count);

          var += 3;
        }
        WG_TEST_LCLFUNCTION_END;

        threeStep();
        WG_TEST_LCLFUNCTION_VERIFYCALL(threeStep);
      }
      WG_TEST_LCLFUNCTION_END;

      twoStep(count);
      WG_TEST_LCLFUNCTION_VERIFYCALL(twoStep);
    }
    WG_TEST_LCLFUNCTION_END;

    oneStep();
    WG_TEST_LCLFUNCTION_VERIFYCALL(oneStep);

    EXPECT_EQ(count, 6);
  }
};
}
TEST(wg_lclfunction_nested_tpl, TwoLevel)
{
  try
  {
    TwoLevel<int>::run();
  }
  WG_GTEST_CATCH
}
