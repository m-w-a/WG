#include <gtest/gtest.h>
#include <WG/Local/Tests/LclFunction/Utils/TestLclFunction.hh>
#include <WG/Local/Tests/Utils/Utils.hh>

TEST(wg_lclfunction_varsetimplicit, OkIf1VarSet)
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

  WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
    WG_LCLFUNCTION_TYPENAME(check),
    check);

  check();
  WG_TEST_LCLFUNCTION_VERIFYCALL(check);

  EXPECT_TRUE(proxy.didAssign);
}

TEST(wg_lclfunction_varsetimplicit, OkIf3VarsOfVaryingMutabilitySet)
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

  WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
    WG_LCLFUNCTION_TYPENAME(calculateVolume),
    calculateVolume);

  calculateVolume();
  WG_TEST_LCLFUNCTION_VERIFYCALL(calculateVolume);

  EXPECT_EQ(cylinder.radius * cylinder.height, cylinder.volume);
}
