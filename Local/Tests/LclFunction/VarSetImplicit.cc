#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/LclFunction/Utils/TestLclFunction.hh>
#include <WG/Local/Tests/Utils/Utils.hh>

TEST(wg_lclfunction_varsetimplicit, OkIf1VarSet)
{
  try
  {
    struct
    {
      bool didAssign;
    } proxy = {false};

    WG_TEST_LCLFUNCTION(check, varset (ref didAssign, proxy.didAssign) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(check);

      WG_TEST_ASSERT_ISNOTCONST_TPL(didAssign);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(bool, didAssign);

      didAssign = true;
    }WG_TEST_LCLFUNCTION_END;

    check();
    WG_TEST_LCLFUNCTION_VERIFYCALL(check);

    EXPECT_TRUE(proxy.didAssign);
  }
  WG_GTEST_CATCH
}

TEST(wg_lclfunction_varsetimplicit, OkIf3VarsOfVaryingMutabilitySet)
{
  try
  {
    struct
    {
      int radius;
      int height;
      int volume;
    } cylinder = {2, 10, -1};

    WG_TEST_LCLFUNCTION
    (calculateVolume,
      varset (const radius, cylinder.radius)
        (const height, cylinder.height)
        (ref volume, cylinder.volume) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(calculateVolume);

      WG_TEST_ASSERT_ISCONST(radius);
      WG_TEST_ASSERT_ISCONST(height);
      WG_TEST_ASSERT_ISNOTCONST(volume);

      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, radius);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, height);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, volume);

      volume = radius * height;
    }WG_TEST_LCLFUNCTION_END;

    calculateVolume();
    WG_TEST_LCLFUNCTION_VERIFYCALL(calculateVolume);

    EXPECT_EQ(cylinder.radius * cylinder.height, cylinder.volume);
  }
  WG_GTEST_CATCH
}
