#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
#include <utility>
#include <WG/Local/Tests/TestHelper.hh>

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

    WG_LCLFUNCTION_TPL
    (check,
      varset (type(T &) didAssign, proxy.didAssign) )
    {
      WG_TESTHELPER_ASSERT_ISNOTCONST_TPL(didAssign);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T, didAssign);

      didAssign = true;
    }WG_LCLFUNCTION_END;

    check();

    EXPECT_TRUE(proxy.didAssign);
  }
};
}
TEST(wg_lclfunction_varsetexplicit_tpl, OkIf1VarSet)
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

    WG_LCLFUNCTION_TPL
    (calculateVolume,
      varset (type(T1 const) radius, cylinder.radius)
        (type(T2 const) height, cylinder.height)
        (type(T3 &) volume, cylinder.volume) )
    {
      WG_TESTHELPER_ASSERT_ISCONST_TPL(radius);
      WG_TESTHELPER_ASSERT_ISCONST_TPL(height);
      WG_TESTHELPER_ASSERT_ISNOTCONST_TPL(volume);

      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T1, radius);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T2, height);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T3, volume);

      volume = radius * height;
    }
    WG_LCLFUNCTION_END;

    calculateVolume();

    EXPECT_EQ(cylinder.radius * cylinder.height, cylinder.volume);
  }
};
}
TEST(wg_lclfunction_varsetexplicit_tpl, OkIf3VarOfVaryingMutabilitySet)
{
  try
  {
    OkIf3VarOfVaryingMutabilitySet<int, int, int>::run();
  }
  WG_GTEST_CATCH
}
