#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/LclFunction/Utils/TestLclFunction.hh>
#include <WG/Local/Tests/Utils/Utils.hh>

TEST(wg_lclfunction_nested, OneLevel)
{
  try
  {
    int count = 0;

    WG_TEST_LCLFUNCTION(oneStep, varbind (ref count) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(oneStep);

      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, count);
      WG_TEST_ASSERT_ISNOTCONST(count);

      ++count;

      WG_TEST_LCLFUNCTION(twoStep, varbind (ref count) )
      {
        WG_TEST_LCLFUNCTION_MARKCALL(twoStep);

        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, count);
        WG_TEST_ASSERT_ISNOTCONST(count);

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
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_nested, TwoLevel)
{
  try
  {
    int count = 0;

    WG_TEST_LCLFUNCTION(oneStep, varbind (ref count) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(oneStep);

      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, count);
      WG_TEST_ASSERT_ISNOTCONST(count);

      ++count;

      WG_TEST_LCLFUNCTION(twoStep, params (int & count) )
      {
        WG_TEST_LCLFUNCTION_MARKCALL(twoStep);

        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, count);
        WG_TEST_ASSERT_ISNOTCONST(count);

        count += 2;

        WG_TEST_LCLFUNCTION(threeStep, varset (ref var, count) )
        {
          WG_TEST_LCLFUNCTION_MARKCALL(threeStep);

          WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, count);
          WG_TEST_ASSERT_ISNOTCONST(count);

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
  WG_GTEST_CATCH
}
