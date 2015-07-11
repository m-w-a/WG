#include <gtest/gtest.h>
#include <WG/Local/Tests/LclFunction/Utils/TestLclFunction.hh>
#include <WG/Local/Tests/Utils/Utils.hh>

TEST(wg_lclfunction_nested, OneLevel)
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

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
      WG_LCLFUNCTION_TYPENAME(twoStep),
      twoStep);

    twoStep();
    WG_TEST_LCLFUNCTION_VERIFYCALL(twoStep);
  }
  WG_TEST_LCLFUNCTION_END;

  WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
    WG_LCLFUNCTION_TYPENAME(oneStep),
    oneStep);

  oneStep();
  WG_TEST_LCLFUNCTION_VERIFYCALL(oneStep);

  EXPECT_EQ(count, 3);
}

TEST(wg_lclfunction_nested, TwoLevel)
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

      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
        WG_LCLFUNCTION_TYPENAME(threeStep),
        threeStep);

      threeStep();
      WG_TEST_LCLFUNCTION_VERIFYCALL(threeStep);
    }
    WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
      WG_LCLFUNCTION_TYPENAME(twoStep),
      twoStep);

    twoStep(count);
    WG_TEST_LCLFUNCTION_VERIFYCALL(twoStep);
  }
  WG_TEST_LCLFUNCTION_END;

  WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
    WG_LCLFUNCTION_TYPENAME(oneStep),
    oneStep);

  oneStep();
  WG_TEST_LCLFUNCTION_VERIFYCALL(oneStep);

  EXPECT_EQ(count, 6);
}
