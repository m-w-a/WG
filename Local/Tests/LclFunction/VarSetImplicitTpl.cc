#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/LclFunction/Utils/TestLclFunction.hh>
#include <WG/Local/Tests/Utils/Utils.hh>

namespace
{
template <typename T>
struct OkIf1VarSet
{
  static void run()
  {
    struct
    {
      T didAssign;
    } proxy = {false};

    WG_TEST_LCLFUNCTION_TPL(check, varset (ref didAssign, proxy.didAssign) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(check);

      WG_TEST_ASSERT_ISNOTCONST_TPL(didAssign);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
        BOOST_TYPEOF(proxy.didAssign), didAssign);

      didAssign = true;
    }WG_TEST_LCLFUNCTION_END;

    check();
    WG_TEST_LCLFUNCTION_VERIFYCALL(check);

    EXPECT_TRUE(proxy.didAssign);
  }
};
}
TEST(wg_lclfunction_varsetimplicit_tpl, OkIf1VarSet)
{
  try
  {
    OkIf1VarSet<bool>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T1, typename T2, typename T3>
struct OkIf3VarOfVaryingMutabilitySet
{
  static void run()
  {
    struct
    {
      T1 radius;
      T2 height;
      T3 volume;
    } cylinder = {2, 10, -1};

    WG_TEST_LCLFUNCTION_TPL
    (calculateVolume,
      varset (const radius, cylinder.radius)
        (const height, cylinder.height)
        (ref volume, cylinder.volume) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(calculateVolume);

      WG_TEST_ASSERT_ISCONST_TPL(radius);
      WG_TEST_ASSERT_ISCONST_TPL(height);
      WG_TEST_ASSERT_ISNOTCONST_TPL(volume);

      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T1, radius);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T2, height);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T3, volume);

      volume = radius * height;
    }
    WG_TEST_LCLFUNCTION_END;

    calculateVolume();
    WG_TEST_LCLFUNCTION_VERIFYCALL(calculateVolume);

    EXPECT_EQ(cylinder.radius * cylinder.height, cylinder.volume);
  }
};
}
TEST(wg_lclfunction_varsetimplicit_tpl, OkIf3VarOfVaryingMutabilitySet)
{
  try
  {
    OkIf3VarOfVaryingMutabilitySet<int, int, int>::run();
  }
  WG_GTEST_CATCH
}
